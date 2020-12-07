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
#ifndef GLOBAL_H
#define GLOBAL_H
//------------------------------------------------------------------------------
#include <stdio.h>
#include <QString>
#include <QDialog>
#include "messages.h"
//------------------------------------------------------------------------------
namespace global {
//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------
  const int MAX_STRING_LENGTH=10000;
  const int DEFAULT_INTERVAL=100;
  const int DEFAULT_SCATTER_SIZE=2;
  const int STRING_LENGTH=80;
  const int SPANSLIDER_SIZE=1000;
  const int SCATTERSHAPES_LENGTH=17;
  const int PREFERRED_TICK_COUNT=10;
  const QStringList comboList=QStringList()<<"Integer"<<"Double"<<"String";
  const char DELIMITERS[]=",\t";
  const char SEPARATOR='\"';
  const char PATTERN[]="\\s+$";
  enum VARIABLE_TYPES {INT_TYPE,DOUBLE_TYPE,STRING_TYPE};
//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------
  #define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
  int getUniqueIdentifier();
//------------------------------------------------------------------------------
  template <class T> QString SetDataName(T data,QString name) {
    int i1;
    QString newName;
    T itData;

    i1=0;
    do {
      newName=name;
      if (i1>0)
        newName+=" ("+QString::number(i1)+")";
      for (itData=data; itData!=NULL; itData=itData->Next)
        if (QString::compare(itData->name,newName)==0)
          break;
      i1++;
      } while (itData!=NULL);
    return newName;
    }
//------------------------------------------------------------------------------
  template <class T> T GetLastClass(T data) {
    T itData;

    for (itData=data; itData->Next!=NULL; itData=itData->Next);
    return itData;
    }
//------------------------------------------------------------------------------
  template <class T> T GetClass(T data, int id) {
    T itData;

    for (itData=data; itData!=NULL; itData=itData->Next)
      if (itData->id==id)
        return itData;
    return NULL;
    }
//------------------------------------------------------------------------------
  }
//------------------------------------------------------------------------------
#endif // GLOBAL_H
