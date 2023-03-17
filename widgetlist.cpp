#include "widgetlist.h"
//------------------------------------------------------------------------------
WidgetList::WidgetList(int graph_type) {
  datatable=nullptr;
  plottype=graph_type;
  combo=new QComboBox*[NCOMBO];
  active=new bool[NCOMBO];
  for (int i1=0; i1<NCOMBO; i1++) {
    combo[i1]=nullptr;
    active[i1]=CATEGORY_ACTIVE[i1];
    }
  color1=Qt::darkBlue;
  color2=Qt::white;
  colortype=SINGLE;
  sizetype=global::DEFAULT_SCATTER_SIZE;
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
  delete active;
  delete Next;
  }
//------------------------------------------------------------------------------
