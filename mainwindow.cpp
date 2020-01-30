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
#include "mainwindow.h"
#include "ui_mainwindow.h"
//------------------------------------------------------------------------------
// MainWindow Class
//------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->tabWidget->setTabsClosable(true);
  setWindowTitle(QString(MYSOFTWARE)+" "+QString(MYVERSION)+"-"+QString(GIT_VERSION));
  mainDataTable=nullptr;
  mainWidgetList=nullptr;
  setScatterShapes();
  }
//------------------------------------------------------------------------------
MainWindow::~MainWindow() {
  delete mainDataTable;
  delete mainWidgetList;
  delete ui;
  }
//------------------------------------------------------------------------------
// Triggered Actions
//------------------------------------------------------------------------------
void MainWindow::ShowContextMenu() {
  QMenu *menu;
  QAction *action;

  menu=new QMenu();
  action=new QAction("Set Colour",this);
  menu->addAction(action);
  connect(action,&QAction::triggered,this,&MainWindow::setChartColor);
  action=new QAction("Set shape",this);
  menu->addAction(action);
  connect(action,&QAction::triggered,this,&MainWindow::setChartShapes);
  action=new QAction("Set size",this);
  menu->addAction(action);
  connect(action,&QAction::triggered,this,&MainWindow::setChartSizes);
  menu->exec(this->mapToGlobal(this->mapFromGlobal(QCursor::pos())));
  menu->close();
  }
//------------------------------------------------------------------------------
void MainWindow::setChartColor() {
  QPalette pal=palette();

  SetChartColor setChartColor(this);
  populateColumnBox(activeWidgetList->datatable,setChartColor.ui->comboBox,activeWidgetList->combo[WidgetList::COMBO::COLOR]->currentIndex());
  pal.setColor(QPalette::Background,activeWidgetList->color1);
  setChartColor.ui->widget->setPalette(pal);
  pal.setColor(QPalette::Background,activeWidgetList->color2);
  setChartColor.ui->widget_2->setPalette(pal);
  switch(activeWidgetList->colortype) {
    case WidgetList::SINGLE:
      setChartColor.ui->radioButton->setChecked(true);
      break;
    case WidgetList::CONTINUOUS:
      setChartColor.ui->radioButton_2->setChecked(true);
      break;
    case WidgetList::CATEGORICAL:
      setChartColor.ui->radioButton_3->setChecked(true);
      break;
    }
  if (setChartColor.exec()==QDialog::Accepted) {
    activeWidgetList->color1=setChartColor.ui->widget->palette().color(QPalette::Background);
    activeWidgetList->color2=setChartColor.ui->widget_2->palette().color(QPalette::Background);
    activeWidgetList->colortype=(setChartColor.ui->radioButton->isChecked()?WidgetList::SINGLE:
                                 setChartColor.ui->radioButton_2->isChecked()?WidgetList::CONTINUOUS:WidgetList::CATEGORICAL);
    activeWidgetList->activecolor=activeWidgetList->colortype!=WidgetList::SINGLE;
    activeWidgetList->combo[WidgetList::COMBO::COLOR]->setCurrentIndex(setChartColor.ui->comboBox->currentIndex());
    UpdateScatterPlot(activeWidgetList);
    showLegend(activeWidgetList,true);
    }
  setChartColor.close();
  }
//------------------------------------------------------------------------------
void MainWindow::setChartShapes() {
  SetChartParameter setChartParameter(this);
  setChartParameter.setWindowTitle("Set Plot Shape");
  setChartParameter.removeSizeSlider();
  populateColumnBox(activeWidgetList->datatable,setChartParameter.ui->comboBox,activeWidgetList->combo[WidgetList::COMBO::SHAPE]->currentIndex());
  setChartParameter.ui->CheckBox->setChecked(!activeWidgetList->activeshape);
  if (setChartParameter.exec()==QDialog::Accepted) {
    activeWidgetList->activeshape=!setChartParameter.ui->CheckBox->isChecked();
    activeWidgetList->combo[WidgetList::COMBO::SHAPE]->setCurrentIndex(setChartParameter.ui->comboBox->currentIndex());
    UpdateScatterPlot(activeWidgetList);
    showLegend(activeWidgetList,true);
    }
  setChartParameter.close();
  }
//------------------------------------------------------------------------------
void MainWindow::setScatterShapes() {
  scattershapes[0].addEllipse(0,0,40,40);
  scattershapes[1].addRect(0,0,40,40);
  scattershapes[2].addPolygon(QPolygonF()<<QPoint(0,0)<<QPoint(40,20)<<QPoint(0,40));
  scattershapes[2].closeSubpath();
  scattershapes[3].addPolygon(QPolygonF()<<QPoint(40,0)<<QPoint(0,20)<<QPoint(40,40));
  scattershapes[3].closeSubpath();
  scattershapes[4].addPolygon(QPolygonF()<<QPoint(0,20)<<QPoint(20,0)<<QPoint(40,20)<<QPoint(20,40));
  scattershapes[4].closeSubpath();
  scattershapes[5].addPolygon(QPolygonF()<<QPoint(0,0)<<QPoint(40,0)<<QPoint(20,40));
  scattershapes[5].closeSubpath();
  scattershapes[6].addPolygon(QPolygonF()<<QPoint(0,40)<<QPoint(40,40)<<QPoint(20,0));
  scattershapes[6].closeSubpath();
  scattershapes[7].addEllipse(0,0,20,40);
  scattershapes[8].addEllipse(0,0,40,20);
  scattershapes[9].addPolygon(QPolygonF()<<QPoint(20,0)<<QPoint(40,15)<<QPoint(30,40)<<QPoint(10,40)<<QPoint(0,15));
  scattershapes[9].closeSubpath();
  scattershapes[10].addPolygon(QPolygonF()<<QPoint(0,20)<<QPoint(10,40)<<QPoint(30,40)<<QPoint(40,20)<<QPoint(30,0)<<QPoint(10,0));
  scattershapes[10].closeSubpath();
  scattershapes[11].addPolygon(QPolygonF()<<QPoint(12,0)<<QPoint(28,0)<<QPoint(40,40)<<QPoint(0,40));
  scattershapes[11].closeSubpath();
  scattershapes[12].addPolygon(QPolygonF()<<QPoint(12,0)<<QPoint(28,00)<<QPoint(28,12)<<QPoint(40,12)<<QPoint(40,28)<<QPoint(28,28)
                               <<QPoint(28,40)<<QPoint(12,40)<<QPoint(12,28)<<QPoint(0,28)<<QPoint(0,12)<<QPoint(12,12));
  scattershapes[12].closeSubpath();
  scattershapes[13].addPolygon(QPolygonF()<<QPoint(0,12)<<QPoint(12,12)<<QPoint(20,0)<<QPoint(28,12)<<QPoint(40,12)<<QPoint(32,24)
                               <<QPoint(34,40)<<QPoint(20,28)<<QPoint(6,40)<<QPoint(8,24));
  scattershapes[13].closeSubpath();
  scattershapes[14].moveTo(20,20);
  scattershapes[14].arcTo(0,0,40,40,0,180);
  scattershapes[14].closeSubpath();
  scattershapes[15].moveTo(20,20);
  scattershapes[15].arcTo(0,0,40,40,90,180);
  scattershapes[15].closeSubpath();
  scattershapes[16].moveTo(20,20);
  scattershapes[16].arcTo(0,0,40,40,180,180);
  scattershapes[16].closeSubpath();
  }
//------------------------------------------------------------------------------
void MainWindow::setChartSizes() {
  SetChartParameter setChartParameter(this);
  setChartParameter.setWindowTitle("Set Plot Size");
  populateColumnBox(activeWidgetList->datatable,setChartParameter.ui->comboBox,activeWidgetList->combo[WidgetList::COMBO::SIZE]->currentIndex());
  setChartParameter.ui->CheckBox->setChecked(!activeWidgetList->activesize);
  setChartParameter.ui->horizontalSlider->setValue(!activeWidgetList->sizetype);
  if (setChartParameter.exec()==QDialog::Accepted) {
    activeWidgetList->activesize=!setChartParameter.ui->CheckBox->isChecked();
    activeWidgetList->combo[WidgetList::COMBO::SIZE]->setCurrentIndex(setChartParameter.ui->comboBox->currentIndex());
    UpdateScatterPlot(activeWidgetList);
    activeWidgetList->sizetype=setChartParameter.ui->horizontalSlider->value();
    showLegend(activeWidgetList,true);
    }
  setChartParameter.close();
  }
//------------------------------------------------------------------------------
void MainWindow::on_actionImport_triggered() {
  DataTable *dataTable;

  QString fileName = QFileDialog::getOpenFileName(this, tr(STATUS::FILE_CAPTION),"",
                                                  tr(STATUS::FILE_FILTER));
  if (fileName.isNull())
    return;
  ImportWindow importWindow(this);
  if (!importWindow.ImportData(fileName))
    return;
  if (importWindow.exec()==QDialog::Accepted) {
    dataTable=importWindow.setImportedData();
    dataTable->name=global::SetDataName(mainDataTable,QFileInfo(fileName).baseName());
    if (mainDataTable==nullptr)
      mainDataTable=dataTable;
    else
      global::GetLastClass(mainDataTable)->Next=dataTable;
    for (WidgetList *widgetList=mainWidgetList; widgetList!=nullptr; widgetList=widgetList->Next)
      if (widgetList->object!=nullptr)
        widgetList->combo[WidgetList::COMBO::TABLE]->addItem(dataTable->name);
    CreateTablePlot(dataTable);
    addFilters(dataTable);
    }
  importWindow.close();
  }
//------------------------------------------------------------------------------
void MainWindow::on_actionQuit_triggered() {
  close();
  }
//------------------------------------------------------------------------------
void MainWindow::closeEvent() {
  exit(EXIT_SUCCESS);
  }
//------------------------------------------------------------------------------
void MainWindow::on_actionTable_triggered() {
  if (mainDataTable!=nullptr)
    CreateTablePlot(mainDataTable);
  }
//------------------------------------------------------------------------------
void MainWindow::on_actionScatterplot_triggered() {
  if (mainDataTable!=nullptr)
    CreateScatterPlot(mainDataTable);
  }
//------------------------------------------------------------------------------
void MainWindow::on_actionReset_Filters_triggered() {
  DataTable *dt1;
  DataMatrix *dm1;
  int y;

  if (mainDataTable==nullptr)
    return;
  for (dt1=mainDataTable; dt1!=nullptr; dt1=dt1->Next)
    for (dm1=dt1->dataMatrix; dm1!=nullptr; dm1=dm1->Next)
      for (y=0; y<dt1->size; y++)
        dm1->Visible[y]=true;
  //UpdateTablePlot(dt1,ui->tabWidget->currentWidget()->findChild<QTableWidget *>());
  }
//------------------------------------------------------------------------------
void MainWindow::filterSliderChanged(ctkRangeSlider *slider,DataTable *dataTable,DataMatrix *dataMatrix) {
  WidgetList *widgetList;
  QList<QLabel *> labels;
  double min,max;

  labels=slider->parentWidget()->findChildren<QLabel *>();
  min=dataMatrix->getActualValue(slider->minimumValue());
  max=dataMatrix->getActualValue(slider->maximumValue());
  labels.at(RANGESLIDERMIN)->setText(QString::number(min));
  labels.at(RANGESLIDERMAX)->setText(QString::number(max));
  for (int y=0; y<dataTable->size; y++)
    dataMatrix->Visible[y]=(dataMatrix->value[y].toDouble()>=min && dataMatrix->value[y].toDouble()<=max);
  for (widgetList=mainWidgetList; widgetList!=nullptr; widgetList=widgetList->Next)
    if (widgetList->datatable==dataTable)
      updatePlot(widgetList);
  }
//------------------------------------------------------------------------------
void MainWindow::filterListWidgetChanged(QListWidget *listWidget,DataTable *dataTable,DataMatrix *dataMatrix) {
  WidgetList *widgetList;
  QList<QListWidgetItem *> selected;

  selected=listWidget->selectedItems();
  for (int y=0; y<dataTable->size; y++)
    for (int idx=0; idx<selected.size(); idx++) {
      dataMatrix->Visible[y]=(selected[idx]->text()==STATUS::ALL_STRINGS);
      if (selected[idx]->text()==dataMatrix->value[y])
        dataMatrix->Visible[y]=true;
      if (dataMatrix->Visible[y])
        break;
      }
  for (widgetList=mainWidgetList; widgetList!=nullptr; widgetList=widgetList->Next)
    if (widgetList->datatable==dataTable)
      updatePlot(widgetList);
  }
//------------------------------------------------------------------------------
void MainWindow::dataTableChanged(QComboBox *comboBox) {
  WidgetList *widgetList;
  DataTable *dataTable;

  dataTable=mainDataTable;
  for (int i1=0; i1<comboBox->currentIndex(); i1++)
    dataTable=dataTable->Next;
  for (widgetList=mainWidgetList; widgetList!=nullptr; widgetList=widgetList->Next)
    if (widgetList->combo[WidgetList::COMBO::TABLE]==comboBox) {
      widgetList->datatable=dataTable;
      for (int i1=1; i1<WidgetList::NCOMBO; i1++)
        populateColumnBox(dataTable,widgetList->combo[i1],0);
      widgetList->combo[WidgetList::COMBO::X]->setCurrentIndex(1);
      updatePlot(widgetList);
      return;
      }
  }
//------------------------------------------------------------------------------
void MainWindow::parameterChanged(QComboBox *comboBox) {
  WidgetList *widgetList;

  for (widgetList=mainWidgetList; widgetList!=nullptr; widgetList=widgetList->Next)
    for (int i1=0; i1<WidgetList::NCOMBO; i1++)
      if (widgetList->combo[i1]==comboBox) {
        updatePlot(widgetList);
        return;
        }
  }
//------------------------------------------------------------------------------
void MainWindow::closeTab(int index) {
  WidgetList *widgetList;
  int idx;

  ui->tabWidget->widget(index)->deleteLater();
  for (widgetList=mainWidgetList,idx=0; widgetList!=nullptr && idx<index; widgetList=widgetList->Next)
    if (widgetList->object!=nullptr)
      idx++;
  widgetList->object=nullptr;
  }
//------------------------------------------------------------------------------
void MainWindow::switchedTab(int index) {
  WidgetList *widgetList;
  int idx;

  for (widgetList=mainWidgetList,idx=0; widgetList!=nullptr && idx<index; widgetList=widgetList->Next)
    if (widgetList->object!=nullptr)
      idx++;
  activeWidgetList=widgetList;
  }
//------------------------------------------------------------------------------
void MainWindow::axisLabelClick(QCPAxis*,QCPAxis::SelectablePart) {
  QMessageBox::about(this,"Cannot draw plot","Too little data");
  }
//------------------------------------------------------------------------------
void MainWindow::updatePlot(WidgetList *widgetList) {
  if (widgetList->object==nullptr)
    return;
  switch(widgetList->plottype) {
    case WidgetList::TABLEPLOT:
      UpdateTablePlot(widgetList);
      break;
    case WidgetList::SCATTERPLOT:
      UpdateScatterPlot(widgetList);
      break;
    }
  }
//------------------------------------------------------------------------------
// User defined functions
//------------------------------------------------------------------------------
QGridLayout *MainWindow::AddTab(WidgetList *widgetList) {
  QWidget *myTab;
  QGridLayout *myLayout;

  myTab=new QWidget(ui->tabWidget);
  ui->tabWidget->addTab(myTab,STATUS::TABLE_NAME+QString::number(ui->tabWidget->count()+1));
  myLayout=new QGridLayout();
  myTab->setLayout(myLayout);
  connect(ui->tabWidget,static_cast<void(QTabWidget::*)(int)>(&QTabWidget::tabCloseRequested),[this](int index) {
      closeTab(index);
      }
    );
  connect(ui->tabWidget,static_cast<void(QTabWidget::*)(int)>(&QTabWidget::tabBarClicked),[this](int index) {
      switchedTab(index);
      }
    );
  ui->tabWidget->setCurrentWidget(myTab);
  activeWidgetList=widgetList;
  return myLayout;
  }
//------------------------------------------------------------------------------
QComboBox *MainWindow::AddDataTableComboBox(DataTable *myDataTable) {
  DataTable *dataTable;
  QComboBox *comboBox;
  int i1,myIndex;

  comboBox=new QComboBox();
  myIndex=0;
  for (dataTable=mainDataTable, i1=0; dataTable!=nullptr; dataTable=dataTable->Next, i1++) {
    comboBox->addItem(dataTable->name);
    if (myDataTable==dataTable)
      myIndex=i1;
    }
  comboBox->setCurrentIndex(myIndex);
  connect(comboBox,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),[=] {
      dataTableChanged(comboBox);
      }
    );
  return comboBox;
  }
//------------------------------------------------------------------------------
QComboBox *MainWindow::AddParameterComboBox(DataTable *dataTable,int index) {
  QComboBox *comboBox;

  comboBox=new QComboBox();
  comboBox->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
  populateColumnBox(dataTable,comboBox,index);
  connect(comboBox,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),[=] {
      parameterChanged(comboBox);
      }
    );
  return comboBox;
  }
//------------------------------------------------------------------------------
void MainWindow::populateColumnBox(DataTable *myDataTable,QComboBox *comboBox,int index) {
  DataMatrix *dataMatrix;

  if (comboBox==nullptr)
    return;
  comboBox->blockSignals(true);
  comboBox->clear();
  for (dataMatrix=myDataTable->dataMatrix; dataMatrix!=nullptr; dataMatrix=dataMatrix->Next)
    comboBox->addItem(dataMatrix->name);
  comboBox->setCurrentIndex(max(0,index));
  comboBox->blockSignals(false);
  }
//------------------------------------------------------------------------------
void MainWindow::addFilters(DataTable *dataTable) {
  DataMatrix *dataMatrix;
  QVBoxLayout *frameLayout;
  QGridLayout *myLayout;
  QLabel *label,*label2;
  ctkRangeSlider *slider;
  QFrame *frame;
  QListWidget *listWidget;
  int i1;

  frame=new QFrame();
  frame->setFrameShape(QFrame::Box);
  frameLayout=new QVBoxLayout();
  frame->setLayout(frameLayout);
  frame->setProperty(PROPERTIES::TABLEID,dataTable->id);
  ui->toolBox->addItem(frame,dataTable->name);
  for (dataMatrix=dataTable->dataMatrix; dataMatrix!=nullptr; dataMatrix=dataMatrix->Next) {
    frame=new QFrame();
    frame->setFrameShape(QFrame::Box);
    myLayout=new QGridLayout();
    frame->setLayout(myLayout);
    frameLayout->addWidget(frame);
    label=new QLabel(dataMatrix->name);
    label->setMaximumWidth(frame->width()-MAXLABELWIDTHDIFF);
    myLayout->addWidget(label,0,0,1,2);
    if (dataMatrix->valueType==global::STRING_TYPE) {
      listWidget=new QListWidget();
      listWidget->addItem(STATUS::ALL_STRINGS);
      for (i1=0; i1<dataMatrix->uniqueValue->size(); i1++)
        listWidget->addItem(dataMatrix->uniqueValue->at(i1));
      listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
      listWidget->item(0)->setSelected(true);
      connect(listWidget,&QListWidget::itemSelectionChanged,[=] {
          filterListWidgetChanged(listWidget,dataTable,dataMatrix);
          }
        );
      label->setMaximumWidth(listWidget->width());
      myLayout->addWidget(listWidget,1,0,1,1);
      }
    else {
      label=new QLabel(QString::number(dataMatrix->minValue));
      myLayout->addWidget(label,1,0,1,1);
      label2=new QLabel(QString::number(dataMatrix->maxValue));
      label2->setAlignment(Qt::AlignRight);
      myLayout->addWidget(label2,1,1,1,1);
      slider=new ctkRangeSlider(Qt::Horizontal,0);
      slider->setMinimum(0);
      slider->setMaximum(dataMatrix->intervals-1);
      slider->setMinimumPosition(0);
      slider->setMaximumPosition(dataMatrix->intervals-1);
      slider->setProperty("Orientation",true);
      connect(slider,&ctkRangeSlider::valuesChanged,[=] {
          filterSliderChanged(slider,dataTable,dataMatrix);
          }
        );
      label->setMaximumWidth(slider->width());
      myLayout->addWidget(slider,2,0,1,2);
      }
    }
  }
//------------------------------------------------------------------------------
void MainWindow::CreateTablePlot(DataTable *dataTable) {
  QTableWidget *tableWidget;
  QGridLayout *myLayout;
  QVBoxLayout *legend;
  WidgetList *widgetList;

  widgetList=new WidgetList();
  widgetList->datatable=dataTable;
  widgetList->plottype=WidgetList::TABLEPLOT;
  if (mainWidgetList==nullptr)
    mainWidgetList=widgetList;
  else
    global::GetLastClass(mainWidgetList)->Next=widgetList;
  tableWidget=new QTableWidget();
  myLayout=AddTab(widgetList);
  widgetList->combo[WidgetList::COMBO::TABLE]=AddDataTableComboBox(dataTable);
  widgetList->object=tableWidget;
  legend=new QVBoxLayout();
  widgetList->legend=legend;
  myLayout->addLayout(legend,0,0,Qt::AlignTop);
  showLegend(widgetList,false);
  myLayout->addWidget(tableWidget,0,1);
  UpdateTablePlot(widgetList);
  }
//------------------------------------------------------------------------------
void MainWindow::UpdateTablePlot(WidgetList *widgetList) {
  QStringList tableHeader;
  DataMatrix *dataMatrix;
  DataTable *dataTable;
  QTableWidget *tableWidget;
  int tableRows,x,y,y1;

  dataTable=widgetList->datatable;
  tableWidget=(QTableWidget *)widgetList->object;
  for (dataMatrix=dataTable->dataMatrix; dataMatrix!=nullptr; dataMatrix=dataMatrix->Next)
    tableHeader.append(dataMatrix->name);
  tableRows=dataTable->size;
  tableWidget->setRowCount(tableRows);
  tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
  tableWidget->setColumnCount(tableHeader.count());
  tableWidget->verticalHeader()->setVisible(false);
  tableWidget->setHorizontalHeaderLabels(tableHeader);
  for (y=y1=0; y<dataTable->size; y++) {
    for (x=0,dataMatrix=dataTable->dataMatrix; dataMatrix!=nullptr; x++,dataMatrix=dataMatrix->Next) {
      tableWidget->setItem(y1,x,new QTableWidgetItem(dataMatrix->value[y]));
      if (!dataMatrix->Visible[y])
        break;
      }
    if (dataMatrix==nullptr)
      y1++;
    }
  tableWidget->setRowCount(y1);
  }
//------------------------------------------------------------------------------
void MainWindow::CreateScatterPlot(DataTable *dataTable) {
  QGridLayout *myLayout;
  QVBoxLayout *legend;
  QCustomPlot *chart;
  WidgetList *widgetList;

  if (dataTable->dataMatrix->Next==nullptr) {
    QMessageBox::about(this,"Cannot draw plot","Too little data");
    return;
    }
  widgetList=new WidgetList();
  widgetList->datatable=dataTable;
  widgetList->plottype=WidgetList::SCATTERPLOT;
  if (mainWidgetList==nullptr)
    mainWidgetList=widgetList;
  else
    global::GetLastClass(mainWidgetList)->Next=widgetList;
  chart=new QCustomPlot();
  legend=new QVBoxLayout();
  widgetList->object=chart;
  widgetList->legend=legend;
  widgetList->combo[WidgetList::COMBO::TABLE]=AddDataTableComboBox(dataTable);
  widgetList->combo[WidgetList::COMBO::Y]=AddParameterComboBox(dataTable,0);
  widgetList->combo[WidgetList::COMBO::X]=AddParameterComboBox(dataTable,1);
  widgetList->combo[WidgetList::COMBO::COLOR]=AddParameterComboBox(dataTable,0);
  widgetList->combo[WidgetList::COMBO::SHAPE]=AddParameterComboBox(dataTable,0);
  widgetList->combo[WidgetList::COMBO::SIZE]=AddParameterComboBox(dataTable,0);
  myLayout=AddTab(widgetList);
  myLayout->addLayout(legend,0,0,Qt::AlignTop);
  showLegend(widgetList,false);
  myLayout->addWidget(chart,0,1);
  myLayout->setRowStretch(0,1);
  myLayout->setColumnStretch(1,1);
  UpdateScatterPlot(widgetList);
  }
//------------------------------------------------------------------------------
void MainWindow::UpdateScatterPlot(WidgetList *widgetList) {
  QCustomPlot *chart;
  PlotDataContainer plotdata;
  float redd,greend,blued;
  QString titleLegend;

  redd=greend=blued=0;
  plotdata=setPlotData(widgetList);
  chart=(QCustomPlot *)widgetList->object;
  chart->yAxis->setRange(plotdata.dmy->getMinAxis(),plotdata.dmy->getMaxAxis());
  chart->xAxis->setRange(plotdata.dmx->getMinAxis(),plotdata.dmx->getMaxAxis());
  chart->yAxis->setLabel(plotdata.dmy->name);
  chart->xAxis->setLabel(plotdata.dmx->name);
  //connect(chart,SIGNAL(axisClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)),this,SLOT(axisLabelClick(QCPAxis*,QCPAxis::SelectablePart)));
  chart->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(chart,static_cast<void(QCustomPlot::*)(const QPoint &)>(&QCustomPlot::customContextMenuRequested),[=] {
      ShowContextMenu();
      }
    );
  chart->clearGraphs();
  chart->clearItems();
  /*
  chart->legend->clear();
  if (plotdata.dmcolor!=nullptr)
    addLegendTitle(chart,"Colour: "+plotdata.dmcolor->name);
  if (plotdata.dmshape!=nullptr)
    addLegendTitle(chart,"Shape: "+plotdata.dmshape->name);
  if (plotdata.dmsize!=nullptr)
    addLegendTitle(chart,"Size: "+plotdata.dmsize->name);
  chart->legend->setBorderPen(Qt::NoPen);
  chart->plotLayout()->addElement(0, 1, chart->legend);
  chart->plotLayout()->setColumnStretchFactor(0,4);
  */
  if (widgetList->colortype==WidgetList::CONTINUOUS) {
    redd=(float)(widgetList->color2.red()-widgetList->color1.red())/(float)(plotdata.dmcolor->intervals-1);
    greend=(float)(widgetList->color2.green()-widgetList->color1.green())/(float)(plotdata.dmcolor->intervals-1);
    blued=(float)(widgetList->color2.blue()-widgetList->color1.blue())/(float)(plotdata.dmcolor->intervals-1);
    }
  for (int bin=0; bin<plotdata.ydata.size(); bin++) {
    if (plotdata.ydata[bin].size()==0)
      continue;
    QCPGraph *graph=chart->addGraph();
    graph->setName(plotdata.valueText[bin]);
    switch (widgetList->colortype) {
      case WidgetList::SINGLE:
        graph->setScatterStyle(QCPScatterStyle(scattershapes[plotdata.plotTypes[bin][SHAPE]%global::SCATTERSHAPES_LENGTH],
                                               QPen(Qt::darkGray,4),
                                               QBrush(widgetList->color1),
                                               widgetList->sizetype*plotdata.plotTypes[bin][SIZE]));
        break;
      case WidgetList::CONTINUOUS:
        graph->setScatterStyle(QCPScatterStyle(scattershapes[plotdata.plotTypes[bin][SHAPE]%global::SCATTERSHAPES_LENGTH],
                                               QPen(Qt::darkGray,4),
                                               QBrush(QColor(widgetList->color1.red()+redd*(float)plotdata.plotTypes[bin][COLOR],
                                                      widgetList->color1.green()+greend*(float)plotdata.plotTypes[bin][COLOR],
                                                      widgetList->color1.blue()+blued*(float)plotdata.plotTypes[bin][COLOR])),
                                               widgetList->sizetype*plotdata.plotTypes[bin][SIZE]));
        if (bin>0 && bin<chart->legend->itemCount())
          chart->legend->removeAt(chart->legend->itemCount()-1);
        break;
      case WidgetList::CATEGORICAL:
        graph->setScatterStyle(QCPScatterStyle(scattershapes[plotdata.plotTypes[bin][SHAPE]%global::SCATTERSHAPES_LENGTH],
                                               QPen(Qt::darkGray,4),
                                               QBrush(Qt::GlobalColor(COLORTYPES[plotdata.plotTypes[bin][COLOR]%ARRAY_SIZE(COLORTYPES)])),
                                               widgetList->sizetype*plotdata.plotTypes[bin][SIZE]));
        break;
      }
    graph->setLineStyle(QCPGraph::lsNone);
    graph->addData(plotdata.xdata[bin],plotdata.ydata[bin]);
    }
  // http://www.qcustomplot.com/documentation/thelayoutsystem.html
  chart->replot();
  }
//------------------------------------------------------------------------------
PlotDataContainer MainWindow::setPlotData(WidgetList *widgetList) {
  DataMatrix *dataMatrix;
  PlotDataContainer plotdata;
  int idx,nbins,uniqueIndex,totalIndex;

  for (idx=0,dataMatrix=widgetList->datatable->dataMatrix; dataMatrix!=nullptr; idx++,dataMatrix=dataMatrix->Next) {
    if (idx==widgetList->combo[WidgetList::COMBO::Y]->currentIndex())
      plotdata.dmy=dataMatrix;
    if (idx==widgetList->combo[WidgetList::COMBO::X]->currentIndex())
      plotdata.dmx=dataMatrix;
    if (idx==widgetList->combo[WidgetList::COMBO::COLOR]->currentIndex() && widgetList->activecolor)
      plotdata.dmcolor=dataMatrix;
    if (idx==widgetList->combo[WidgetList::COMBO::SHAPE]->currentIndex() && widgetList->activeshape)
      plotdata.dmshape=dataMatrix;
    if (idx==widgetList->combo[WidgetList::COMBO::SIZE]->currentIndex() && widgetList->activesize)
      plotdata.dmsize=dataMatrix;
    }
  nbins=(plotdata.dmcolor!=nullptr?plotdata.dmcolor->intervals:1)*
        (plotdata.dmshape!=nullptr?plotdata.dmshape->intervals:1)*
        (plotdata.dmsize!=nullptr?plotdata.dmsize->intervals:1);
  plotdata.ydata.resize(nbins);
  plotdata.xdata.resize(nbins);
  plotdata.plotTypes.resize(nbins);
  plotdata.valueText.resize(nbins);
  QVector<int> indx(nbins);
  for (int i1=0; i1<plotdata.ydata.size(); i1++) {
    plotdata.ydata[i1].resize(widgetList->datatable->size);
    plotdata.xdata[i1].resize(widgetList->datatable->size);
    plotdata.plotTypes[i1].resize(GRAPHTYPES_LENGTH);
    indx[i1]=0;
    }
  for (int y=0; y<widgetList->datatable->size; y++) {
    for (dataMatrix=widgetList->datatable->dataMatrix; dataMatrix!=nullptr; dataMatrix=dataMatrix->Next)
      if (!dataMatrix->Visible[y])
        break;
    if (dataMatrix!=nullptr)
      continue;
    uniqueIndex=0;
    totalIndex=1;
    if (plotdata.dmcolor!=nullptr) {
      uniqueIndex=plotdata.dmcolor->uniqueIndex[y];
      totalIndex*=plotdata.dmcolor->intervals;
      }
    if (plotdata.dmshape!=nullptr) {
      uniqueIndex=totalIndex*plotdata.dmshape->uniqueIndex[y]+uniqueIndex;
      totalIndex*=plotdata.dmshape->intervals;
      }
    if (plotdata.dmsize!=nullptr)
      uniqueIndex=totalIndex*plotdata.dmsize->uniqueIndex[y]+uniqueIndex;
    plotdata.ydata[uniqueIndex][indx[uniqueIndex]]=plotdata.dmy->value[y].toDouble();
    plotdata.xdata[uniqueIndex][indx[uniqueIndex]]=plotdata.dmx->value[y].toDouble();
    indx[uniqueIndex]++;
    if (indx[uniqueIndex]>1)
      continue;
    int plotTypes[GRAPHTYPES_LENGTH]={0,0,1};
    plotdata.valueText[uniqueIndex]="";
    if (plotdata.dmcolor!=nullptr) {
      plotTypes[COLOR]=plotdata.dmcolor->uniqueIndex[y];
      plotdata.valueText[uniqueIndex]=plotdata.dmcolor->value[y]+" ";
      }
    if (plotdata.dmshape!=nullptr) {
      plotTypes[SHAPE]=plotdata.dmshape->uniqueIndex[y];
      plotdata.valueText[uniqueIndex]+=plotdata.dmshape->value[y]+" ";
      }
    if (plotdata.dmsize!=nullptr) {
      plotTypes[SIZE]=plotdata.dmsize->uniqueIndex[y];
      plotdata.valueText[uniqueIndex]+=plotdata.dmsize->value[y];
      }
    for (int i1=0; i1<GRAPHTYPES_LENGTH; i1++)
      plotdata.plotTypes[uniqueIndex][i1]=plotTypes[i1];
    }
  for (int i1=0; i1<plotdata.ydata.size(); i1++) {
    plotdata.ydata[i1].resize(indx[i1]);
    plotdata.xdata[i1].resize(indx[i1]);
    }
  return plotdata;
  }
//------------------------------------------------------------------------------
void MainWindow::showLegend(WidgetList *widgetList,bool update) {
  QLabel *label;

  if (!update) {
    label=new QLabel("Data");
    widgetList->legend->addWidget(label);
    widgetList->legend->addWidget(widgetList->combo[WidgetList::COMBO::TABLE]);
    switch(widgetList->plottype) {
      case WidgetList::SCATTERPLOT:
        label=new QLabel("Y Axis");
        widgetList->legend->addWidget(label);
        widgetList->legend->addWidget(widgetList->combo[WidgetList::COMBO::Y]);
        label=new QLabel("X Axis");
        widgetList->legend->addWidget(label);
        widgetList->legend->addWidget(widgetList->combo[WidgetList::COMBO::X]);
        label=new QLabel("Colour");
        widgetList->legend->addWidget(label);
        widgetList->legend->addWidget(widgetList->combo[WidgetList::COMBO::COLOR]);
        label=new QLabel("Shape");
        widgetList->legend->addWidget(label);
        widgetList->legend->addWidget(widgetList->combo[WidgetList::COMBO::SHAPE]);
        label=new QLabel("Size");
        widgetList->legend->addWidget(label);
        widgetList->legend->addWidget(widgetList->combo[WidgetList::COMBO::SIZE]);
        break;
      }
    }
  switch(widgetList->plottype) {
    case WidgetList::SCATTERPLOT:
      widgetList->combo[WidgetList::COMBO::COLOR]->setEnabled(widgetList->activecolor);
      widgetList->combo[WidgetList::COMBO::SHAPE]->setEnabled(widgetList->activeshape);
      widgetList->combo[WidgetList::COMBO::SIZE]->setEnabled(widgetList->activesize);
      break;
    }
  }
//------------------------------------------------------------------------------
void MainWindow::addLegendTitle(QCustomPlot *chart,QString title) {
  QCPTextElement *legendTitle=new QCPTextElement(chart);
  legendTitle->setLayer(chart->legend->layer());
  legendTitle->setText(title);
  legendTitle->setFont(QFont("sans",9,QFont::Bold));
  if (chart->legend->hasElement(0, 0))
     chart->legend->insertRow(0);
  chart->legend->addElement(0,0,legendTitle);
  }
//------------------------------------------------------------------------------
