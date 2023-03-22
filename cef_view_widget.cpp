#include "cef_view_widget.h"

#include <QColor>
#include <QPainterPath>
#include <QRandomGenerator>
#include <QResizeEvent>
#include <QWindow>
#include <QDebug>
#include <QUrl>
#include <QDesktopServices>

CefViewWidget::CefViewWidget(const QString url,
                             const QCefSetting* setting,
                             QWidget* parent /* = 0*/)
    : QCefView(url, setting, parent) {}

CefViewWidget::~CefViewWidget() {}

bool CefViewWidget::onBeforePopup(qint64 frameId,
                                  const QString& targetUrl,
                                  const QString& targetFrameName,
                                  QCefView::CefWindowOpenDisposition targetDisposition,
                                  QCefSetting& settings,
                                  bool& DisableJavascriptAccess) {
  if (targetUrl.startsWith("https://www.bing.com/rewards/authcheck")) {
    this->navigateToUrl(targetUrl);
    return true;
  }

  QUrl target(targetUrl);
  QDesktopServices::openUrl(target);

  // return false to allow the popup browser
  return true;
}
