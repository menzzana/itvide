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
#include <stdio.h>
#include <iostream>
#include <QString>
#include <QCheckBox>
#include "global.h"
//------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------
#ifndef DATAMATRIX_H
#define DATAMATRIX_H
//------------------------------------------------------------------------------
class DataMatrix {
  private:
    const double RATIO_BUFFER=0.05;
  public:
    QString name;
    int valueType,intervals;
    QVector<int> uniqueIndex;
    QString *value;
    bool *Visible;
    QList<QString> *uniqueValue;
    double maxValue,minValue;
    class DataMatrix *Next;

    DataMatrix();
    double getValuePerInterval();
    double getAxisBuffer();
    double getMinAxis();
    double getMaxAxis();
    double getActualValue(int position);
    void setMinMaxValues();
    void setUniqueStringList(int index);
    void setUniqueIndex(int size);
    void setIntervals();
    void SortUniqueValues();
    ~DataMatrix();
  };
//------------------------------------------------------------------------------
template<typename T> static bool compareValue(const QString &s1,const QString &s2) {
  if (is_same<T,QString>::value)
    return QString::compare(s1,s2,Qt::CaseInsensitive)<0;
  else
    return s1.toDouble()<s2.toDouble();
  }
//------------------------------------------------------------------------------
#endif // DATAMATRIX_H
