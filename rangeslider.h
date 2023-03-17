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
#ifndef RANGESLIDER_H
#define RANGESLIDER_H
//------------------------------------------------------------------------------
#include <QWidget>
//------------------------------------------------------------------------------
class RangeSlider : public QWidget {
  Q_OBJECT

  public:
    RangeSlider(QWidget *parent = nullptr);
    int lowerValue() const;
    void setLowerValue(int value);
    int upperValue() const;
    void setUpperValue(int value);
    int minimumValue() const;
    int maximumValue() const;
    void setRange(int minValue, int maxValue);

  signals:
    void rangeChanged(int lower, int upper);

  protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

  private:
    void drawHandle(QPainter *painter, const QRect &rect, bool pressed);
    QRect grooveRect() const;
    QRect lowerHandleRect() const;
    QRect upperHandleRect() const;
    int valueFromPosition(int position) const;
    int valueToPosition(int value) const;

    QRect m_trackRect;
    int m_lowerValue;
    int m_upperValue;
    int m_minValue;
    int m_maxValue;
    bool m_lowerPressed;
    bool m_upperPressed;
  };
//------------------------------------------------------------------------------
#endif // RANGESLIDER_H
