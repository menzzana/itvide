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
#ifndef IMPORTWINDOW_H
#define IMPORTWINDOW_H
//------------------------------------------------------------------------------
#include <stdio.h>
#include <QFile>
#include <QTextStream>
#include <QDialog>
#include <QComboBox>
#include <QSignalMapper>
#include <QString>
#include "datatable.h"
#include "datamatrix.h"
#include "global.h"
//------------------------------------------------------------------------------
namespace Ui {
  class ImportWindow;
  }
//------------------------------------------------------------------------------
class ImportWindow : public QDialog {
  Q_OBJECT
  
  public:
    explicit ImportWindow(QWidget *parent = 0);
    ~ImportWindow();
    bool ImportData(QString fileName);
    void SetDataType(QString stringValue, int *dataType);
    QStringList decodeFileRow(QString rowData);
    DataTable *setImportedData();
  
  private:
    Ui::ImportWindow *ui;
  };
//------------------------------------------------------------------------------
#endif // IMPORTWINDOW_H
