#include "main_window.h"

#include <QApplication>
#include <QCefContext.h>
#include <QDebug>
#include <QDir>
#include <QStandardPaths>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  // build QCefConfig
  QCefConfig config;
  config.setLogLevel(QCefConfig::LOGSEVERITY_DEFAULT);
  config.setBridgeObjectName("ShellAPI");
  config.setRemoteDebuggingPort(9000);
  config.setBackgroundColor(Qt::lightGray);
  config.setUserAgent(
      "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/111.0.0.0 Safari/537.36 Edg/111.0.1660.12");

  // WindowlessRenderingEnabled is set to true by default, set to false to disable the OSR mode
  config.setWindowlessRenderingEnabled(false);
  // config.addCommandLineSwitch("disable-gpu");

  // add command line args
  // config.addCommandLineSwitch("allow-universal-access-from-files");
  config.addCommandLineSwitch("enable-media-stream");
  config.addCommandLineSwitch("use-mock-keychain");
  config.addCommandLineSwitch("allow-file-access-from-files");
  config.addCommandLineSwitch("disable-spell-checking");
  config.addCommandLineSwitch("disable-site-isolation-trials");
  config.addCommandLineSwitch("enable-aggressive-domstorage-flushing");
  config.addCommandLineSwitchWithValue("renderer-process-limit", "1");
  config.addCommandLineSwitchWithValue("disable-features",
                                       "BlinkGenPropertyTrees,TranslateUI,site-per-process");

  QStringList caches = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
  if (caches.size() > 0) {
    QDir dir_temp = caches.at(0);
    config.setCachePath(dir_temp.absolutePath());
  }

  // initialize QCefContext instance with config
  QCefContext cefContext(&a, argc, argv, &config);

  MainWindow w;
  w.show();
  return a.exec();
}
