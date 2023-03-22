#ifndef WIDGETS_H
#define WIDGETS_H

#include <QtWidgets>

class DLabel : public QLabel {
  Q_OBJECT

 public:
  explicit DLabel(QWidget* parent = nullptr);
  void setEnabled(bool enable);

 signals:
  void onClick();

 protected:
  void mousePressEvent(QMouseEvent* event) override;

 private:
  bool enable_ = true;
};

#endif  // WIDGETS_H
