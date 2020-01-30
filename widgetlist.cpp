#include "widgetlist.h"
//------------------------------------------------------------------------------
WidgetList::WidgetList() {
  datatable=nullptr;
  combo=new QComboBox*[NCOMBO];
  for (int i1=0; i1<NCOMBO; i1++)
    combo[i1]=nullptr;
  activecolor=activeshape=activesize=false;
  color1=color2=Qt::darkBlue;
  colortype=SINGLE;
  sizetype=global::DEFAULT_SCATTER_SIZE;
  plottype=-1;
  object=nullptr;
  legend=nullptr;
  Next=nullptr;
  }
//------------------------------------------------------------------------------
WidgetList::~WidgetList() {
  delete object;
  for (int i1=0; i1<NCOMBO; i1++)
    delete combo[i1];
  delete combo;
  delete Next;
  }
//------------------------------------------------------------------------------
