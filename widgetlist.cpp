#include "widgetlist.h"
//------------------------------------------------------------------------------
WidgetList::WidgetList(int graph_type) {
  datatable=nullptr;
  plottype=graph_type;
  switch(plottype) {
    case GRAPH_TYPES::TABLEVIEW:
      ncombo=1;
      break;
    case GRAPH_TYPES::SCATTERPLOT:
      ncombo=6;
      break;
    case GRAPH_TYPES::BARCHART:
      ncombo=4;
      break;
    }
  combo=new QComboBox*[ncombo];
  active=new bool[ncombo];
  for (int i1=0; i1<ncombo; i1++) {
    combo[i1]=nullptr;
    active[i1]=i1<ALWAYSACTIVE;
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
  for (int i1=0; i1<ncombo; i1++)
    delete combo[i1];
  delete combo;
  delete active;
  delete Next;
  }
//------------------------------------------------------------------------------
