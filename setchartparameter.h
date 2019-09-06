#ifndef SETCHARTPARAMETER_H
#define SETCHARTPARAMETER_H
//------------------------------------------------------------------------------
#include <QDialog>
//------------------------------------------------------------------------------
namespace Ui {
  class SetChartParameter;
  }
//------------------------------------------------------------------------------
class SetChartParameter : public QDialog {
  Q_OBJECT

  public:
  explicit SetChartParameter(QWidget *parent = 0);
  ~SetChartParameter();
  void removeSizeSlider();

  Ui::SetChartParameter *ui;
  };
//------------------------------------------------------------------------------
#endif // SETCHARTPARAMETER_H
