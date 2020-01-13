#include "widgetlist.h"
//------------------------------------------------------------------------------
WidgetList::WidgetList() {
  datatable=nullptr;
  tablecmb=yaxiscmb=xaxiscmb=nullptr;
  colorindex=-1;
  shapeindex=-1;
  sizeindex=-1;
  color1=color2=Qt::darkBlue;
  colortype=SINGLE;
  sizetype=global::DEFAULT_SCATTER_SIZE;
  plottype=-1;
  object=nullptr;
  Next=nullptr;
  }
//------------------------------------------------------------------------------
WidgetList::~WidgetList() {
  delete object;
  delete Next;
  }
//------------------------------------------------------------------------------
