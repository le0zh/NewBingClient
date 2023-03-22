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
}
