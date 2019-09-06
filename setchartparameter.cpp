#include "setchartparameter.h"
#include "ui_setchartparameter.h"
//------------------------------------------------------------------------------
SetChartParameter::SetChartParameter(QWidget *parent) : QDialog(parent),
  ui(new Ui::SetChartParameter) {
  ui->setupUi(this);
  }
//------------------------------------------------------------------------------
SetChartParameter::~SetChartParameter() {
  delete ui;
  }
//------------------------------------------------------------------------------
void SetChartParameter::removeSizeSlider() {
  ui->horizontalSlider->setVisible(false);
  ui->label_2->setVisible(false);
  }
//------------------------------------------------------------------------------
