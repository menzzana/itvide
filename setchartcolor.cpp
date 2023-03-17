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
#include "setchartcolor.h"
#include "ui_setchartcolor.h"
//------------------------------------------------------------------------------
SetChartColor::SetChartColor(QWidget *parent) :
    QDialog(parent), ui(new Ui::SetChartColor) {
  ui->setupUi(this);
  }
//------------------------------------------------------------------------------
SetChartColor::~SetChartColor() {
  delete ui;
  }
//------------------------------------------------------------------------------
void SetChartColor::on_pushButton_clicked() {
  QPalette pal=palette();
  QColor color=QColorDialog::getColor(ui->widget->palette().color(QPalette::Window),this);
  if (color.isValid()) {
    pal.setColor(QPalette::Window,color);
    ui->widget->setPalette(pal);
    }
  }
//------------------------------------------------------------------------------
void SetChartColor::on_pushButton_2_clicked() {
  QPalette pal=palette();
  QColor color=QColorDialog::getColor(ui->widget_2->palette().color(QPalette::Window),this);
  if (color.isValid()) {
    pal.setColor(QPalette::Window,color);
    ui->widget_2->setPalette(pal);
    }
  }
//------------------------------------------------------------------------------
