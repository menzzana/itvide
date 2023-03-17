/********************************************************************************
ItVide
Copyright (C) 2017  Henric Zazzi <henric@zazzi.se>

ItVide is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/
#include "rangeslider.h"
#include <QPainter>
#include <QMouseEvent>
//------------------------------------------------------------------------------
RangeSlider::RangeSlider(QWidget *parent) : QWidget(parent) {
  m_lowerValue=m_minValue=0;
  m_upperValue=m_maxValue=100;
  m_upperPressed=m_lowerPressed=false;
  setMinimumSize(QSize(100, 20));
  setMaximumSize(QSize(16777215, 20));
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  }
//------------------------------------------------------------------------------
void RangeSlider::setRange(int minValue, int maxValue) {
  m_minValue = m_lowerValue = minValue;
  m_maxValue = m_upperValue = maxValue;
  setLowerValue(m_lowerValue);
  setUpperValue(m_upperValue);
  }
//------------------------------------------------------------------------------
void RangeSlider::setLowerValue(int value) {
  if (m_lowerValue != value) {
    m_lowerValue = value;
    emit rangeChanged(m_lowerValue, m_upperValue);
    update();
    }
  }
//------------------------------------------------------------------------------
void RangeSlider::setUpperValue(int value) {
  if (m_upperValue != value) {
    m_upperValue = value;
    emit rangeChanged(m_lowerValue, m_upperValue);
    update();
    }
  }
//------------------------------------------------------------------------------
int RangeSlider::lowerValue() const {
  return m_lowerValue;
  }
//------------------------------------------------------------------------------
int RangeSlider::upperValue() const {
  return m_upperValue;
  }
//------------------------------------------------------------------------------
void RangeSlider::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    if (lowerHandleRect().contains(event->pos())) {
      m_lowerPressed = true;
      m_upperPressed = false;
      }
    else if (upperHandleRect().contains(event->pos())) {
      m_upperPressed = true;
      m_lowerPressed = false;
      }
    else {
      int newPosition = valueFromPosition(event->pos().x());
      if (newPosition < m_lowerValue) {
        setLowerValue(newPosition);
        m_lowerPressed = true;
        m_upperPressed = false;
        }
      else if (newPosition < m_upperValue) {
        m_lowerPressed = false;
        m_upperPressed = false;
        }
      else {
        setUpperValue(newPosition);
        m_upperPressed = true;
        m_lowerPressed = false;
        }
      }
    }
  }
//------------------------------------------------------------------------------
void RangeSlider::mouseMoveEvent(QMouseEvent *event) {
  if (m_lowerPressed || m_upperPressed) {
    int newPosition = valueFromPosition(event->pos().x());
    if (m_lowerPressed)
      setLowerValue(newPosition);
    else
      setUpperValue(newPosition);
    }
}
//------------------------------------------------------------------------------
void RangeSlider::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    m_lowerPressed = false;
    m_upperPressed = false;
    }
  }
//------------------------------------------------------------------------------
void RangeSlider::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  QRect grooveRect = this->grooveRect();
  QRect lowerHandleRect = this->lowerHandleRect();
  QRect upperHandleRect = this->upperHandleRect();
  painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
  painter.setBrush(Qt::gray);
  painter.drawRect(grooveRect);
  QRect filledRect = QRect(lowerHandleRect.center().x(), grooveRect.y(), upperHandleRect.center().x() - lowerHandleRect.center().x(), grooveRect.height());
  painter.fillRect(filledRect, Qt::green);
  drawHandle(&painter, lowerHandleRect, m_lowerPressed);
  drawHandle(&painter, upperHandleRect, m_upperPressed);
  }
//------------------------------------------------------------------------------
void RangeSlider::drawHandle(QPainter *painter, const QRect &rect, bool pressed) {
  painter->save();
  painter->setRenderHint(QPainter::Antialiasing);
  QRadialGradient gradient(rect.center(), rect.width());
  gradient.setColorAt(0, pressed ? QColor(255, 255, 255) : QColor(245, 245, 245));
  gradient.setColorAt(1, pressed ? QColor(200, 200, 200) : QColor(190, 190, 190));
  painter->setBrush(gradient);
  painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
  painter->drawRect(rect);
  painter->restore();
  }
//------------------------------------------------------------------------------
QRect RangeSlider::grooveRect() const {
  QRect groove = rect().adjusted(10, height() / 2 - 2, -10, -height() / 2 + 2);
  groove.setHeight(4);
  return groove;
  }
//------------------------------------------------------------------------------
QRect RangeSlider::lowerHandleRect() const {
  QRect handle = QRect(QPoint(valueToPosition(m_lowerValue), 0), QSize(10, 10));
  handle.moveCenter(QPoint(handle.center().x(), height() / 2));
  return handle;
  }
//------------------------------------------------------------------------------
QRect RangeSlider::upperHandleRect() const {
  QRect handle = QRect(QPoint(valueToPosition(m_upperValue) - 10, 0), QSize(10, 10));
  handle.moveCenter(QPoint(handle.center().x(), height() / 2));
  return handle;
  }
//------------------------------------------------------------------------------
int RangeSlider::valueFromPosition(int position) const {
  double ratio = (double)(position - 10) / (double)(width() - 20);
  int value = (int)(ratio * (m_maxValue - m_minValue) + 0.5);
  return qBound(m_minValue, value, m_maxValue);
  }
//------------------------------------------------------------------------------
int RangeSlider::valueToPosition(int value) const {
  double ratio = (double)(value - m_minValue) / (double)(m_maxValue - m_minValue);
  return (int)(ratio * (width() - 20) + 0.5) + 10;
  }
//------------------------------------------------------------------------------
