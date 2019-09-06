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
#ifndef SETCHARTCOLOR_H
#define SETCHARTCOLOR_H
//------------------------------------------------------------------------------
#include <QDialog>
#include <QComboBox>
#include <QColorDialog>
#include "datatable.h"
#include "datamatrix.h"
//------------------------------------------------------------------------------
namespace Ui {
  class SetChartColor;
  }
//------------------------------------------------------------------------------
class SetChartColor : public QDialog {
  Q_OBJECT

  public:
    explicit SetChartColor(QWidget *parent = 0);
    ~SetChartColor();

    Ui::SetChartColor *ui;

  private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
  };
//------------------------------------------------------------------------------
#endif // SETCHARTCOLOR_H
