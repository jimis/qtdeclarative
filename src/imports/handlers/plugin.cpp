/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the plugins of the Qt Toolkit.
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

#include <QtQml/qqmlextensionplugin.h>

#include <private/qquickhandlersmodule_p.h>

static void initResources()
{
#ifdef QT_STATIC
    Q_INIT_RESOURCE(qmake_Qt_labs_handlers_1);
#endif
}

QT_BEGIN_NAMESPACE

/*!
    \qmlmodule Qt.labs.handlers 1.0
    \title Qt Quick Pointer Handlers
    \ingroup qmlmodules
    \brief Provides QML types for handling pointer events.

    This QML module contains types for handling pointer events, which are an abstraction
    of mouse, touch and tablet events.

    To use the types in this module, import the module with the following line:

    \code
    import Qt.labs.handlers 1.0
    \endcode
*/


//![class decl]
class QtQuickHandlersPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
    QtQuickHandlersPlugin(QObject *parent = 0) : QQmlExtensionPlugin(parent) { initResources(); }
    void registerTypes(const char *uri) Q_DECL_OVERRIDE
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("Qt.labs.handlers"));
        Q_UNUSED(uri);
        QQuickHandlersModule::defineModule();
    }
};
//![class decl]

QT_END_NAMESPACE

#include "plugin.moc"
