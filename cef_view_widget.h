#ifndef CEF_VIEW_WIDGET_H
#define CEF_VIEW_WIDGET_H

#include <QScreen>
#include <QCefView.h>

/// <summary>
/// Represents the customized QCefView
/// </summary>
class CefViewWidget : public QCefView {
  Q_OBJECT

 public:
  CefViewWidget(const QString url, const QCefSetting* setting, QWidget* parent = 0);

  ~CefViewWidget();

 private:
  virtual bool onBeforePopup(qint64 frameId,
                             const QString& targetUrl,
                             const QString& targetFrameName,
                             QCefView::CefWindowOpenDisposition targetDisposition,
                             QCefSetting& settings,
                             bool& DisableJavascriptAccess);

 private:
  void updateMask();

 private:
  int m_cornerRadius = 50;
};

#endif  // CEF_VIEW_WIDGET_H
