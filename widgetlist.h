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
      TABLE,Y,X,COLOR,SIZE,SHAPE,AGGREGATION
      };
    static const int NCOMBO=7;
    DataTable *datatable;
    QComboBox **combo;
    bool *active;
    int plottype;
    QColor color1,color2;
    int sizetype;
    int colortype;
    QObject *object;
    QVBoxLayout *legend;
    class WidgetList *Next;

    WidgetList(int graph_type);
    ~WidgetList();
  };
const QString CATEGORY_TEXT[]={
  "Data","Y Axis","X Axis","Colour","Shape","Size","Aggregation"
  };
const int CATEGORY_COLUMN[]={
  false,true,true,true,true,true,false
  };
const int CATEGORY_ACTIVE[]={
  true,true,true,false,false,false,true
  };
//------------------------------------------------------------------------------
#endif // WIDGETLIST_H
