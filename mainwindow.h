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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//------------------------------------------------------------------------------
#include <QMainWindow>
#include <stdio.h>
#include "importwindow.h"
#include "setchartcolor.h"
#include "ui_setchartcolor.h"
#include "setchartparameter.h"
#include "ui_setchartparameter.h"
#include <qfiledialog.h>
#include <QLayout>
#include <QToolBox>
#include <QTableWidget>
#include <QFrame>
#include <QLabel>
#include <QCheckBox>
#include <QSlider>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QListWidget>
#include <QList>
#include <QMessageBox>
#include <qcustomplot.h>
#include <rangeslider.h>
#include "datatable.h"
#include "datamatrix.h"
#include "widgetlist.h"
#include "global.h"
#include "plotdatacontainer.h"
//------------------------------------------------------------------------------
namespace Ui {
  class MainWindow;
  }
//------------------------------------------------------------------------------
class MainWindow : public QMainWindow {
  Q_OBJECT
  
  public:
    //Variables
    DataTable *mainDataTable;
    WidgetList *mainWidgetList,*activeWidgetList;
    QPainterPath scattershapes[global::SCATTERSHAPES_LENGTH];

    //Functions
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QGridLayout *AddTab(WidgetList *widgetList);
    QComboBox *AddDataTableComboBox(DataTable *myDataTable);
    QComboBox *AddParameterComboBox(WidgetList *widgetList,int index);
    QComboBox *AddAggregationComboBox(WidgetList *widgetList);
    void populateColumnBox(DataTable *myDataTable,QComboBox *comboBox,int index);
    void addFilters(DataTable *dataTable);
    void createTablePlot(DataTable *dataTable);
    void updateTablePlot(WidgetList *widgetList);
    void createScatterPlot(DataTable *dataTable);
    void updateScatterPlot(WidgetList *widgetList);
    void createBarChart(DataTable *dataTable);
    void updateBarChart(WidgetList *widgetList);
    PlotDataContainer setPlotData(WidgetList *widgetList);
    WidgetList *createPlotData(DataTable *dataTable,int graphtype);

  private slots:
    void on_actionImport_triggered();
    void on_actionQuit_triggered();
    void on_actionTable_triggered();
    void on_actionScatterplot_triggered();
    void closeEvent();
    void filterSliderChanged(RangeSlider *slider,DataTable *dataTable,DataMatrix *dataMatrix);
    void filterListWidgetChanged(QListWidget *listWidget,DataTable *dataTable,DataMatrix *dataMatrix);
    void dataTableChanged(QComboBox *comboBox);
    void closeTab(int index);
    void switchedTab(int index);
    void axisLabelClick(QCPAxis*,QCPAxis::SelectablePart);
    void updatePlot(WidgetList *widgetList);
    void on_actionReset_Filters_triggered();
    void showContextMenu();
    void setChartColor();
    void setChartShapes();
    void setScatterShapes();
    void setChartSizes();
    void showLegend(WidgetList *widgetList,bool update);
    void addLegendTitle(QCustomPlot *chart,QString title);
    void on_actionBarchart_triggered();

  private:
    Ui::MainWindow *ui;
    const int RANGESLIDERMIN=1;
    const int RANGESLIDERMAX=2;
    const int MAXLABELWIDTHDIFF=500;
  };
//------------------------------------------------------------------------------
#endif // MAINWINDOW_H
