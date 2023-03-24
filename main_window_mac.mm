#include "main_window.h"
#include <Cocoa/Cocoa.h>

void MainWindow::setupWindow() {
    id hwnd = (id)this->winId();
    NSWindow* window = [hwnd window];
    [window setTitlebarHeight:40.0];
    window.titlebarAppearsTransparent = true;
    [window setTitle: @""];
    window.movableByWindowBackground = true;
    window.styleMask |= NSWindowStyleMaskFullSizeContentView;

    if (@available(macOS 10.14, *)) {
        NSAppearance *appearance = [NSApp effectiveAppearance];
        NSAppearanceName appearanceName = appearance.name;
        is_dark_mode_ = appearanceName == NSAppearanceNameDarkAqua || appearanceName == NSAppearanceNameAccessibilityHighContrastDarkAqua;
    }
}
