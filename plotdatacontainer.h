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
#ifndef PLOTDATACONTAINER_H
#define PLOTDATACONTAINER_H
//------------------------------------------------------------------------------
#include <QVector>
#include "datamatrix.h"
#include <qcustomplot.h>
//------------------------------------------------------------------------------
enum GRAPHTYPES {COLOR,SHAPE,SIZE,GRAPHTYPES_LENGTH};
const int COLORTYPES[]={
  7,8,9,2,10,11,3,12,4,13,14,5,15,6,16,17,18
  };
//------------------------------------------------------------------------------
class PlotDataContainer {
  public:
    QVector< QVector<double> > xdata,ydata;
    QVector< QVector<int> > plotTypes;
    QVector<QString> valueText;
    DataMatrix *dmy,*dmx,*dmcolor,*dmshape,*dmsize;


  PlotDataContainer();
  void addDistributedTicks(QSharedPointer<QCPAxisTickerText> ticker,QList<QString> *values);
  };
//------------------------------------------------------------------------------
#endif // PLOTDATACONTAINER_H
