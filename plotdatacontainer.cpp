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
#include "plotdatacontainer.h"
//------------------------------------------------------------------------------
PlotDataContainer::PlotDataContainer() {
  dmy=dmx=dmcolor=dmshape=dmsize=nullptr;
  }
//------------------------------------------------------------------------------
void PlotDataContainer::addDistributedTicks(QSharedPointer<QCPAxisTickerText> ticker,QList<QString> *values) {
  int dist;

  dist=values->size()/global::PREFERRED_TICK_COUNT;
  for (int i1=0; i1<values->size(); i1+=dist)
    ticker->addTick(i1,values->at(i1));
  }
//------------------------------------------------------------------------------
