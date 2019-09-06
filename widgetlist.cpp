#include "widgetlist.h"
//------------------------------------------------------------------------------
WidgetList::WidgetList() {
  datatable=NULL;
  tablecmb=yaxiscmb=xaxiscmb=NULL;
  colorindex=-1;
  shapeindex=-1;
  sizeindex=-1;
  color1=color2=Qt::darkBlue;
  colortype=SINGLE;
  sizetype=global::DEFAULT_SCATTER_SIZE;
  plottype=-1;
  object=NULL;
  Next=NULL;
  }
//------------------------------------------------------------------------------
WidgetList::~WidgetList() {
  delete object;
  delete Next;
  }
//------------------------------------------------------------------------------
