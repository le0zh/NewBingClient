#include "main_window.h"
#include "utils.h"
#include "widgets.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

// define bing base url
#define BING_BASE_URL \
  "https://edgeservices.bing.com/edgediscover/query?&%1schemeovr=1&FORM=SHORUN&udscs=1&udsnav=1&setlang=${locale}&features=udssydinternal&clientscopes=windowheader,coauthor,chat,&udsframed=1"

// define normal style for menu item
#define MENU_ITEM_STYLE_NORMAL \
  "#ItemButton{font-size: 14px;color: #808080;} #ItemButton::hover { border-radius: 6px; background-color: #3C3C3E;}"

// define selected style for menu item
#define MENU_ITEM_STYLE_SELECTED \
  "#ItemButton{font-size: 14px;color: #ffffff; font-weight:bold; background-color: #3C3C3E; border-radius: 6px; } #ItemButton::hover { border-radius: 6px; background-color: #3C3C3E;}"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  setupWindow();
  setupUI();
  newTopic();
}

MainWindow::~MainWindow() {}

void MainWindow::newTopic() {
  topic_index_++;

  if (topics.size() >= 10) {
    // show message box
    QMessageBox::warning(this, "Warning", "You have reached the maximum number of topics.");
    return;
  }

  // foreach topics and set each one to normal style
  for (auto it = topics.begin(); it != topics.end(); ++it) {
    it.value().menu->setStyleSheet(MENU_ITEM_STYLE_NORMAL);
  }

  auto bing_url = QString(BING_BASE_URL).arg(is_dark_mode_ ? "dark" : "light");
  CefViewWidget* view = new CefViewWidget(bing_url, nullptr, this);

  connect(view, &QCefView::addressChanged, this,
          [view, bing_url](qint64 frameId, const QString& url) {
            Q_UNUSED(frameId);
            if (url.startsWith("https://edgeservices.bing.com/edgesvc/urlredirect")) {
              view->navigateToUrl(bing_url);
            }
          });

  connect(view, &QCefView::loadEnd, this,
          [view](int browserId, qint64 frameId, bool isMainFrame, int httpStatusCode) {
            Q_UNUSED(browserId);
            Q_UNUSED(isMainFrame);
            Q_UNUSED(httpStatusCode);

            QString js = utils::loadJsFile(":/js/preload.js");
            view->executeJavascript(frameId, js, "preload.js");
          });

  QString title = "topic " + QString::number(topic_index_);

  // create menu for this topic
  DLabel* menu = new DLabel(this);
  menu->setObjectName("ItemButton");
  menu->setFixedSize(220, 30);
  menu->setText("# " + title);
  menu->setContentsMargins(10, 5, 10, 5);
  menu->setAlignment(Qt::AlignVCenter | Qt::AlignLeading);
  menu->setStyleSheet(MENU_ITEM_STYLE_SELECTED);

  auto current_topic_index = topic_index_;
  connect(menu, &DLabel::onClick, this,
          [this, current_topic_index]() { this->switchTopic(current_topic_index); });

  side_bar_layout_->insertWidget(2, menu);

  TopicEntity topic_entity;
  topic_entity.title = title;
  topic_entity.view = view;
  topic_entity.menu = menu;

  this->topics.insert(topic_index_, topic_entity);

  topic_selected_ = topic_index_;

  stacked_widget_->addWidget(view);
  stacked_widget_->setCurrentWidget(view);

  if (topics.size() > 1) {
    remove_topic_btn_->setEnabled(true);
  }
}

void MainWindow::switchTopic(int key) {
  if (key == topic_selected_) {
    return;
  }

  topic_selected_ = key;

  // foreach topics, check if it's the one we want to switch to
  for (auto it = topics.begin(); it != topics.end(); ++it) {
    if (it.key() == topic_selected_) {
      it.value().menu->setStyleSheet(MENU_ITEM_STYLE_SELECTED);
      stacked_widget_->setCurrentWidget(it.value().view);
    }
    else {
      it.value().menu->setStyleSheet(MENU_ITEM_STYLE_NORMAL);
    }
  }
}

void MainWindow::removeTopic(int key) {
  qDebug() << "remove topic: " << key;
  if (!topics.contains(key)) {
    return;
  }

  auto it = topics.value(key);

  qDebug() << "it menu" << it.menu->text();

  // clean widgets
  side_bar_layout_->removeWidget(it.menu);
  stacked_widget_->removeWidget(it.view);
  it.menu->deleteLater();
  it.view->close();
  it.view->deleteLater();

  // remove topic
  topics.remove(key);

  // update selected_topic_key
  if (key > 1) {
    // find the next topic in
    auto next_key = key - 1;
    while (!topics.contains(next_key)) {
      next_key--;
    }

    if (next_key >= 1) {
      switchTopic(next_key);
    }
  }

  if (topics.size() == 1) {
    remove_topic_btn_->setEnabled(false);
  }
}

void MainWindow::setupWindow() {
  setWindowIcon(QIcon(":/images/assets/icon.ico"));
}

void MainWindow::setupUI() {
  QWidget* central_widget = new QWidget(this);

  QWidget* side_bar = new QWidget(this);
  side_bar->setObjectName("SideBar");
  side_bar->setFixedWidth(240);
  if (is_dark_mode_) {
    side_bar->setStyleSheet("#SideBar{background-color:#22252A; border-right: 1px solid #5b5b5b;}");
  }
  else {
    side_bar->setStyleSheet("#SideBar{background-color:#1A2B3C; border-right: 1px solid #5b5b5b;}");
  }

  DLabel* new_topic_btn = new DLabel(this);
  new_topic_btn->setObjectName("NewButton");
  new_topic_btn->setFixedSize(200, 48);
  new_topic_btn->setText("New topic");
  new_topic_btn->setAlignment(Qt::AlignCenter);
  new_topic_btn->setStyleSheet(
      "#NewButton{margin-left: 10px;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(40, 112, 234, 255), stop:1 rgba(27, 74, 239, 200)); color: #ffffff; border-radius: 24px;} #NewButton::hover { background-color: #6887CA;}");

  connect(new_topic_btn, &DLabel::onClick, this, &MainWindow::newTopic);

  remove_topic_btn_ = new DLabel(this);
  remove_topic_btn_->setObjectName("RemoveButton");
  remove_topic_btn_->setFixedSize(200, 28);
  remove_topic_btn_->setText("Remove topic");
  remove_topic_btn_->setAlignment(Qt::AlignCenter);
  remove_topic_btn_->setStyleSheet(
      "#RemoveButton{margin-left: 10px;color: #808080;} #RemoveButton::hover { color: #ffffff;}");
  remove_topic_btn_->setEnabled(false);
  connect(remove_topic_btn_, &DLabel::onClick, this, [this]() { removeTopic(topic_selected_); });

  QLabel* history_tip = new QLabel(this);
  history_tip->setObjectName("HistoryTip");
  history_tip->setFixedSize(220, 20);
  history_tip->setText("Topics");
  history_tip->setContentsMargins(10, 0, 10, 0);
  history_tip->setAlignment(Qt::AlignVCenter | Qt::AlignLeading);
  history_tip->setStyleSheet("#HistoryTip{font-size: 14px;color: #929292;font-weight: bold;}");

  side_bar_layout_ = new QVBoxLayout(this);
  side_bar_layout_->setContentsMargins(10, 0, 10, 0);
  side_bar_layout_->addSpacing(40);
  side_bar_layout_->addWidget(history_tip);

  side_bar_layout_->addStretch(0);
  side_bar_layout_->addWidget(new_topic_btn);
  side_bar_layout_->addWidget(remove_topic_btn_);
  side_bar_layout_->addSpacing(28);

  side_bar->setLayout(side_bar_layout_);

  stacked_widget_ = new QStackedWidget(this);

  QHBoxLayout* main_layout = new QHBoxLayout();

#ifdef Q_OS_WINDOWS
  main_layout->setContentsMargins(0, 1, 0, 0);
#else
  main_layout->setContentsMargins(0, 0, 0, 0);
#endif

  main_layout->setSpacing(0);

  main_layout->addWidget(side_bar);
  main_layout->addWidget(stacked_widget_);

  central_widget->setLayout(main_layout);

  // set min size
  this->setMinimumSize(900, 600);

  // set window size
  resize(900, 600);

  setCentralWidget(central_widget);
}
