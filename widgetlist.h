#ifndef WIDGETLIST_H
#define WIDGETLIST_H
#include <QObject>
#include <QComboBox>
#include <QVBoxLayout>
#include "datatable.h"
//------------------------------------------------------------------------------
class WidgetList {
  public:
    enum GRAPH_TYPES {TABLEPLOT,SCATTERPLOT};
    enum COLOR_TYPES {SINGLE,CONTINUOUS,CATEGORICAL};
    enum COMBO {TABLE,Y,X,COLOR,SIZE,SHAPE};
    static const int NCOMBO=6;

    DataTable *datatable;
    QComboBox **combo;
    bool activecolor,activeshape,activesize;
    int plottype;
    QColor color1,color2;
    int sizetype;
    int colortype;
    QObject *object;
    QVBoxLayout *legend;
    class WidgetList *Next;

    WidgetList();
    ~WidgetList();
  };
//------------------------------------------------------------------------------
#endif // WIDGETLIST_H
