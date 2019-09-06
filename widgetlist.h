#ifndef WIDGETLIST_H
#define WIDGETLIST_H
#include <QObject>
#include <QComboBox>
#include "datatable.h"
//------------------------------------------------------------------------------
class WidgetList {
  public:
    enum GRAPH_TYPES {TABLEPLOT,SCATTERPLOT};
    enum COLOR_TYPES {SINGLE,CONTINUOUS,CATEGORICAL};

    DataTable *datatable;
    QComboBox *tablecmb,*yaxiscmb,*xaxiscmb;
    int colorindex,shapeindex,sizeindex,plottype;
    QColor color1,color2;
    int sizetype;
    int colortype;
    QObject *object;
    class WidgetList *Next;

    WidgetList();
    ~WidgetList();
  };
//------------------------------------------------------------------------------
#endif // WIDGETLIST_H
