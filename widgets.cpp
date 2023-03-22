#include "widgets.h"

DLabel::DLabel(QWidget* parent) : QLabel(parent) {
  this->setCursor(Qt::PointingHandCursor);
  this->setObjectName("DLabel");
}

void DLabel::setEnabled(bool enable) {
  enable_ = enable;

  if (enable) {
    this->setCursor(Qt::PointingHandCursor);
  }
  else {
    this->setCursor(Qt::ForbiddenCursor);
  }
}

void DLabel::mousePressEvent(QMouseEvent* event) {
  if (!enable_) {
    return;
  }

  Q_UNUSED(event);

  emit onClick();
}
