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
#include "importwindow.h"
#include "ui_importwindow.h"
//------------------------------------------------------------------------------
ImportWindow::ImportWindow(QWidget *parent) :
    QDialog(parent), ui(new Ui::ImportWindow) {
  ui->setupUi(this);
  }
//------------------------------------------------------------------------------
ImportWindow::~ImportWindow() {
  delete ui;
  }
//------------------------------------------------------------------------------
bool ImportWindow::ImportData(QString fileName) {
  int tableRows,i1;
  int *valueTypes;
  QComboBox *comboBox;
  QStringList tableHeader,tableValues;
  QString qs1;
  QFile file;
  QTextStream stream;

  file.setFileName(fileName);
  if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
    return false;
  stream.setDevice(&file);
  tableHeader=decodeFileRow(stream.readLine().remove(QRegularExpression(global::PATTERN)));
  valueTypes=new int[tableHeader.count()];
  for (i1=0; i1<tableHeader.count(); i1++)
    valueTypes[i1]=global::INT_TYPE;
  tableRows=0;
  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->tableWidget->setColumnCount(tableHeader.count());
  ui->tableWidget->setRowCount(tableRows);
  ui->tableWidget->verticalHeader()->setVisible(false);
  ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
  while (!stream.atEnd()) {
      qs1=stream.readLine().remove(QRegularExpression(global::PATTERN));
    if (qs1.isEmpty())
      continue;
    tableRows++;
    ui->tableWidget->setRowCount(tableRows+1);
    tableValues=decodeFileRow(qs1);
    for (i1=0; i1<tableValues.count(); i1++) {
      ui->tableWidget->setItem(tableRows,i1,new QTableWidgetItem(tableValues[i1]));
      SetDataType(tableValues[i1],&valueTypes[i1]);
      }
    }
  for (i1=0; i1<tableHeader.count(); i1++) {
    comboBox=new QComboBox();
    comboBox->addItems(global::comboList);
    ui->tableWidget->setCellWidget(0,i1,comboBox);
    comboBox->setCurrentIndex(valueTypes[i1]);
    }
  file.close();
  delete valueTypes;
  ui->tableWidget->show();
  return true;
  }
//------------------------------------------------------------------------------
void ImportWindow::SetDataType(QString stringValue, int *dataType) {
  bool ok,value;

  if (*dataType==global::STRING_TYPE)
    return;
  value=(stringValue.toDouble(&ok)==stringValue.toInt());
  *dataType=ok?!value?global::DOUBLE_TYPE:global::INT_TYPE:global::STRING_TYPE;
  }
//------------------------------------------------------------------------------
QStringList ImportWindow::decodeFileRow(QString rowData) {
  int i1;
  QString rowEntry;
  QStringList rowResult;
  bool dataEntry;

  dataEntry=false;
  rowEntry="";
  for (i1=0; i1<rowData.length(); i1++) {
    if (rowData[i1]==global::SEPARATOR) {
      dataEntry=!dataEntry;
      continue;
      }
    if (!dataEntry && (rowData[i1]==global::DELIMITERS[0] || rowData[i1]==global::DELIMITERS[1])) {
      rowResult.append(rowEntry);
      rowEntry="";
      continue;
      }
    rowEntry=rowEntry+rowData[i1];
    }
  rowResult.append(rowEntry);
  return rowResult;
  }
//------------------------------------------------------------------------------
DataTable *ImportWindow::setImportedData() {
  DataTable *dataTable;
  DataMatrix *dataMatrix,*lastDataMatrix;
  QTableWidgetItem *item;
  QComboBox *comboBox;
  int i1,i2;

  dataTable=new DataTable();
  dataTable->size=ui->tableWidget->rowCount()-1;
  lastDataMatrix=nullptr;
  for (i1=0; i1<ui->tableWidget->columnCount(); i1++) {
    dataMatrix=new DataMatrix();
    dataMatrix->intervals=global::DEFAULT_INTERVAL;
    dataMatrix->name=global::SetDataName(dataTable->dataMatrix,ui->tableWidget->horizontalHeaderItem(i1)->text());
    comboBox=(QComboBox *)ui->tableWidget->cellWidget(0,i1);
    dataMatrix->valueType=comboBox->currentIndex();
    dataMatrix->value=new QString[dataTable->size];
    dataMatrix->Visible=new bool[dataTable->size];
    dataMatrix->uniqueValue=new QList<QString>();
    for (i2=1; i2<ui->tableWidget->rowCount(); i2++) {
      item=ui->tableWidget->item(i2,i1);
      dataMatrix->value[i2-1]=(item==nullptr?nullptr:(QString)item->text().trimmed());
      dataMatrix->setUniqueStringList(i2-1);
      dataMatrix->Visible[i2-1]=true;
      }
    dataMatrix->setIntervals();
    dataMatrix->SortUniqueValues();
    dataMatrix->setMinMaxValues();
    dataMatrix->setUniqueIndex(dataTable->size);
    if (lastDataMatrix==nullptr)
      lastDataMatrix=dataTable->dataMatrix=dataMatrix;
    else {
      lastDataMatrix->Next=dataMatrix;
      lastDataMatrix=dataMatrix;
      }
    }
  return dataTable;
  }
//------------------------------------------------------------------------------
