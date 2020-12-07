#ifndef SETCHARTPARAMETER_H
#define SETCHARTPARAMETER_H
//------------------------------------------------------------------------------
#include <QDialog>
//------------------------------------------------------------------------------
namespace Ui {
  class SetChartParameter;
  }
//------------------------------------------------------------------------------
class setChartParameter : public QDialog {
  Q_OBJECT

  public:
  explicit setChartParameter(QWidget *parent = 0);
  ~setChartParameter();
  void removeSizeSlider();

  Ui::SetChartParameter *ui;
  };
//------------------------------------------------------------------------------
#endif // SETCHARTPARAMETER_H
