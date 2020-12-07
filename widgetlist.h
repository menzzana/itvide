#ifndef WIDGETLIST_H
#define WIDGETLIST_H
#include <QObject>
#include <QComboBox>
#include <QVBoxLayout>
#include "datatable.h"
//------------------------------------------------------------------------------
class WidgetList {
  public:
    enum GRAPH_TYPES {
      TABLEVIEW,SCATTERPLOT,BARCHART
      };
    enum COLOR_TYPES {
      SINGLE,CONTINUOUS,CATEGORICAL
      };
    enum CATEGORY {
      TABLE,Y,X,COLOR,SIZE,SHAPE
      };
    static const int NCOMBO=6;
    static const int ALWAYSACTIVE=3;

    DataTable *datatable;
    QComboBox **combo;
    bool *active;
    int plottype,ncombo;
    QColor color1,color2;
    int sizetype;
    int colortype;
    QObject *object;
    QVBoxLayout *legend;
    class WidgetList *Next;

    WidgetList(int graph_type);
    ~WidgetList();
  };
//------------------------------------------------------------------------------
#endif // WIDGETLIST_H
