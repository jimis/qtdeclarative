load(qttest_p4)
contains(QT_CONFIG,declarative): QT += declarative-private gui network qtquick1-private
macx:CONFIG -= app_bundle

HEADERS +=  ../../shared/util.h

SOURCES  += tst_qdeclarativeaccessibility.cpp \
            ../../shared/util.cpp


OTHER_FILES += data/pushbutton.qml
OTHER_FILES += data/statictext.qml

symbian: {
    importFiles.files = data
    importFiles.path = .
    DEPLOYMENT += importFiles
} else {
    DEFINES += SRCDIR=\\\"$$PWD\\\"
}

CONFIG += parallel_test

wince*: {
    accessneeded.files = $$QT_BUILD_TREE\\plugins\\accessible\\*.dll
    accessneeded.path = accessible
    DEPLOYMENT += accessneeded
}




