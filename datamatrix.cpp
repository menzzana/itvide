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
#include "datamatrix.h"
//------------------------------------------------------------------------------
DataMatrix::DataMatrix() {
  name="";
  id=global::getUniqueIdentifier();
  value=NULL;
  Visible=NULL;
  uniqueValue=NULL;
  uniqueIndex=NULL;
  valueType=global::INT_TYPE;
  intervals=0;
  minValue=maxValue=0;
  Next=NULL;
  }
//------------------------------------------------------------------------------
DataMatrix::~DataMatrix() {
  delete uniqueValue;
  delete uniqueIndex;
  delete value;
  delete Visible;
  delete Next;
  }
//------------------------------------------------------------------------------
double DataMatrix::getValuePerInterval() {
  if (intervals==0)
    return 0;
  return (maxValue-minValue)/(double)(intervals-1);
  }
//------------------------------------------------------------------------------
double DataMatrix::getAxisBuffer() {
  return (maxValue-minValue)*RATIO_BUFFER;
  }
//------------------------------------------------------------------------------
double DataMatrix::getMinAxis() {
  return minValue-getAxisBuffer();
  }
//------------------------------------------------------------------------------
double DataMatrix::getMaxAxis() {
  return maxValue+getAxisBuffer();
  }
//------------------------------------------------------------------------------
double DataMatrix::getActualValue(int position) {
  return getValuePerInterval()*(double)position+minValue;
  }
//------------------------------------------------------------------------------
int DataMatrix::getInt(int index) {
  if (valueType!=global::INT_TYPE)
    throw ERROR_TEXT::DATAMATRIX_NO_INTEGER;
  return value[index].toInt();
  }
//------------------------------------------------------------------------------
void DataMatrix::setMinMaxValues() {
  if (valueType==global::STRING_TYPE)
    return;
  maxValue=minValue=uniqueValue->first().toDouble();
  if (uniqueValue->size()>0)
    maxValue=uniqueValue->last().toDouble();
  }
//------------------------------------------------------------------------------
void DataMatrix::setIntervals() {
  intervals=uniqueValue->size();
  }
//------------------------------------------------------------------------------
void DataMatrix::setUniqueStringList(int index) {
  if (uniqueValue->contains(value[index]))
    return;
  uniqueValue->append(value[index]);
  }
//------------------------------------------------------------------------------
void DataMatrix::setUniqueIndex(int size) {
  uniqueIndex=new int[size];
  for (int idx=0; idx<size; idx++)
    uniqueIndex[idx]=uniqueValue->indexOf(value[idx]);
  }
//------------------------------------------------------------------------------
void DataMatrix::SortUniqueValues() {
  if (valueType==global::STRING_TYPE)
    sort(uniqueValue->begin(),uniqueValue->end(),compareValue<QString>);
  else
    sort(uniqueValue->begin(),uniqueValue->end(),compareValue<double>);
 }
//------------------------------------------------------------------------------
