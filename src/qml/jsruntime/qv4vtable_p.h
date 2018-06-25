/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtQml module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef QV4VTABLE_P_H
#define QV4VTABLE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qv4global_p.h"

QT_BEGIN_NAMESPACE

namespace QV4 {

struct VTable
{
    typedef void (*Destroy)(Heap::Base *);
    typedef void (*MarkObjects)(Heap::Base *, MarkStack *markStack);
    typedef bool (*IsEqualTo)(Managed *m, Managed *other);

    typedef ReturnedValue (*Get)(const Managed *, PropertyKey id, const Value *receiver, bool *hasProperty);
    typedef bool (*Put)(Managed *, PropertyKey id, const Value &value, Value *receiver);
    typedef bool (*DeleteProperty)(Managed *m, PropertyKey id);
    typedef bool (*HasProperty)(const Managed *m, PropertyKey id);
    typedef PropertyAttributes (*GetOwnProperty)(Managed *m, PropertyKey id, Property *p);
    typedef bool (*DefineOwnProperty)(Managed *m, PropertyKey id, const Property *p, PropertyAttributes attrs);
    typedef bool (*IsExtensible)(const Managed *);
    typedef bool (*PreventExtensions)(Managed *);
    typedef Heap::Object *(*GetPrototypeOf)(const Managed *);
    typedef bool (*SetPrototypeOf)(Managed *, const Object *);
    typedef qint64 (*GetLength)(const Managed *m);
    typedef void (*AdvanceIterator)(Managed *m, ObjectIterator *it, Value *name, uint *index, Property *p, PropertyAttributes *attributes);
    typedef ReturnedValue (*InstanceOf)(const Object *typeObject, const Value &var);

    typedef ReturnedValue (*Call)(const FunctionObject *, const Value *thisObject, const Value *argv, int argc);
    typedef ReturnedValue (*CallAsConstructor)(const FunctionObject *, const Value *argv, int argc);

    const VTable * const parent;
    quint32 inlinePropertyOffset : 16;
    quint32 nInlineProperties : 16;
    quint8 isExecutionContext;
    quint8 isString;
    quint8 isObject;
    quint8 isFunctionObject;
    quint8 isErrorObject;
    quint8 isArrayData;
    quint8 isStringOrSymbol;
    quint8 type;
    quint8 unused[4];
    const char *className;

    Destroy destroy;
    MarkObjects markObjects;
    IsEqualTo isEqualTo;

    Get get;
    Put put;
    DeleteProperty deleteProperty;
    HasProperty hasProperty;
    GetOwnProperty getOwnProperty;
    DefineOwnProperty defineOwnProperty;
    IsExtensible isExtensible;
    PreventExtensions preventExtensions;
    GetPrototypeOf getPrototypeOf;
    SetPrototypeOf setPrototypeOf;
    GetLength getLength;
    AdvanceIterator advanceIterator;
    InstanceOf instanceOf;

    Call call;
    CallAsConstructor callAsConstructor;
};


struct VTableBase {
protected:
    static constexpr VTable::Destroy destroy = nullptr;
    static constexpr VTable::IsEqualTo isEqualTo = nullptr;

    static constexpr VTable::Get get = nullptr;
    static constexpr VTable::Put put = nullptr;
    static constexpr VTable::DeleteProperty deleteProperty = nullptr;
    static constexpr VTable::HasProperty hasProperty = nullptr;
    static constexpr VTable::GetOwnProperty getOwnProperty = nullptr;
    static constexpr VTable::DefineOwnProperty defineOwnProperty = nullptr;
    static constexpr VTable::IsExtensible isExtensible = nullptr;
    static constexpr VTable::PreventExtensions preventExtensions = nullptr;
    static constexpr VTable::GetPrototypeOf getPrototypeOf = nullptr;
    static constexpr VTable::SetPrototypeOf setPrototypeOf = nullptr;
    static constexpr VTable::GetLength getLength = nullptr;
    static constexpr VTable::AdvanceIterator advanceIterator = nullptr;
    static constexpr VTable::InstanceOf instanceOf = nullptr;

    static constexpr VTable::Call call = nullptr;
    static constexpr VTable::CallAsConstructor callAsConstructor = nullptr;
};

#define DEFINE_MANAGED_VTABLE_INT(classname, parentVTable) \
{     \
    parentVTable, \
    (sizeof(classname::Data) + sizeof(QV4::Value) - 1)/sizeof(QV4::Value), \
    (sizeof(classname::Data) + (classname::NInlineProperties*sizeof(QV4::Value)) + QV4::Chunk::SlotSize - 1)/QV4::Chunk::SlotSize*QV4::Chunk::SlotSize/sizeof(QV4::Value) \
        - (sizeof(classname::Data) + sizeof(QV4::Value) - 1)/sizeof(QV4::Value), \
    classname::IsExecutionContext,          \
    classname::IsString,                    \
    classname::IsObject,                    \
    classname::IsFunctionObject,            \
    classname::IsErrorObject,               \
    classname::IsArrayData,                 \
    classname::IsStringOrSymbol,            \
    classname::MyType,                      \
    { 0, 0, 0, 0 },                         \
    #classname, \
    \
    classname::destroy,                     \
    classname::Data::markObjects,           \
    classname::isEqualTo,                   \
    \
    classname::get,                         \
    classname::put,                         \
    classname::deleteProperty,              \
    classname::hasProperty,                 \
    classname::getOwnProperty,              \
    classname::defineOwnProperty,           \
    classname::isExtensible,                \
    classname::preventExtensions,           \
    classname::getPrototypeOf,              \
    classname::setPrototypeOf,              \
    classname::getLength,                   \
    classname::advanceIterator,             \
    classname::instanceOf,                  \
    \
    classname::call,                        \
    classname::callAsConstructor,           \
}

#define DEFINE_MANAGED_VTABLE(classname) \
const QV4::VTable classname::static_vtbl = DEFINE_MANAGED_VTABLE_INT(classname, 0)

#define V4_OBJECT2(DataClass, superClass) \
    private: \
        DataClass() Q_DECL_EQ_DELETE; \
        Q_DISABLE_COPY(DataClass) \
    public: \
        Q_MANAGED_CHECK \
        typedef QV4::Heap::DataClass Data; \
        typedef superClass SuperClass; \
        static const QV4::VTable static_vtbl; \
        static inline const QV4::VTable *staticVTable() { return &static_vtbl; } \
        V4_MANAGED_SIZE_TEST \
        QV4::Heap::DataClass *d_unchecked() const { return static_cast<QV4::Heap::DataClass *>(m()); } \
        QV4::Heap::DataClass *d() const { \
            QV4::Heap::DataClass *dptr = d_unchecked(); \
            dptr->_checkIsInitialized(); \
            return dptr; \
        } \
        Q_STATIC_ASSERT(std::is_trivial< QV4::Heap::DataClass >::value);

#define V4_PROTOTYPE(p) \
    static QV4::Object *defaultPrototype(QV4::ExecutionEngine *e) \
    { return e->p(); }


#define DEFINE_OBJECT_VTABLE_BASE(classname) \
    const QV4::VTable classname::static_vtbl = DEFINE_MANAGED_VTABLE_INT(classname, (std::is_same<classname::SuperClass, Object>::value) ? nullptr : &classname::SuperClass::static_vtbl)

#define DEFINE_OBJECT_VTABLE(classname) \
DEFINE_OBJECT_VTABLE_BASE(classname)

#define DEFINE_OBJECT_TEMPLATE_VTABLE(classname) \
template<> DEFINE_OBJECT_VTABLE_BASE(classname)

}

QT_END_NAMESPACE

#endif