#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cef_view_widget.h"
#include "widgets.h"
#include <QStackedWidget>
#include <QMainWindow>

struct TopicEntity {
  QString title;
  CefViewWidget* view;
  DLabel* menu;
};

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 protected:
  void setupUI();
  void setupWindow();

  void newTopic();
  void switchTopic(int index);
  void removeTopic(int index);

 private:
  int topic_selected_ = 0;
  int topic_index_ = 0;

  bool is_dark_mode_ = false;

  DLabel* remove_topic_btn_;
  QVBoxLayout* side_bar_layout_;
  QMap<int, TopicEntity> topics;
  CefViewWidget* cef_view_ = nullptr;
  QStackedWidget* stacked_widget_ = nullptr;
};
#endif  // MAINWINDOW_H
