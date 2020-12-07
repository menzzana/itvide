#include "setchartparameter.h"
#include "ui_setchartparameter.h"
//------------------------------------------------------------------------------
setChartParameter::setChartParameter(QWidget *parent) : QDialog(parent),
  ui(new Ui::SetChartParameter) {
  ui->setupUi(this);
  }
//------------------------------------------------------------------------------
setChartParameter::~setChartParameter() {
  delete ui;
  }
//------------------------------------------------------------------------------
void setChartParameter::removeSizeSlider() {
  ui->horizontalSlider->setVisible(false);
  ui->label_2->setVisible(false);
  }
//------------------------------------------------------------------------------
