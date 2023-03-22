TEMPLATE = app

QT += widgets

CONFIG += c++11

SOURCES += \
    cef_view_widget.cpp \
    main.cpp \
    main_window.cpp \
    main_window_mac.mm \
    widgets.cpp

HEADERS += \
    cef_view_widget.h \
    main_window.h \
    utils.h \
    widgets.h


INCLUDEPATH *= "$$PWD/include/QCefView"
DEPENDPATH *= "$$PWD/include/QCefView"

mac {
    QMAKE_INFO_PLIST = $$PWD/assets/info.plist

    APP_BUNDLE_FRAMEWORKS.path = Contents/Frameworks
    APP_BUNDLE_RESOURCES.path = Contents/MacOS/

    LIBS += -F$$PWD/lib/mac_x86_64/
    APP_BUNDLE_FRAMEWORKS.files = $$files($$PWD/lib/mac_x86_64/*.framework, false) $$files($$PWD/lib/mac_x86_64/*.dylib, false)

    LIBS += -framework QCefView
    LIBS += -framework AVFoundation

    QMAKE_BUNDLE_DATA += APP_BUNDLE_RESOURCES APP_BUNDLE_FRAMEWORKS
    
    ICON = $$PWD/assets/icon.icns

    RESOURCE_FILES.files = $$ICON
    RESOURCE_FILES.path = Contents/Resources
    QMAKE_BUNDLE_DATA += RESOURCE_FILES
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
  assets.qrc
