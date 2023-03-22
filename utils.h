#ifndef UTILS_H
#define UTILS_H

#include <QFile>

namespace utils {
QString loadJsFile(const QString& jsName) {
  QString js;
  QFile jsFile(jsName);
  jsFile.open(QFile::ReadOnly);

  if (jsFile.isOpen()) {
    js = QString::fromUtf8(jsFile.readAll());
    jsFile.close();
  }

  return js;
}
}  // namespace utils

#endif  // UTILS_H
