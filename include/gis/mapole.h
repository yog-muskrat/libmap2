
#if !defined(MAPOLE_H)
#define MAPOLE_H

#ifndef MAPTYPE_H
 #include "maptype.h"
#endif

#include "mapversn.h"

#ifndef HIDEOLE

#define PANOLE

typedef  struct OLE_PRINTPARM
{
  RECT   Rect;            // Область отображения - пикселы в районе
  POINT  Shift;           // Смещение на начало листа и отступ
  double Scale;           // Число пикселов устройства в пикселе экрана
  double ViewScale;       // Коэффициент масштабирования относительно базового масштаба 
}
  OLE_PRINTPARM;

#endif   // HIDEOLE

#endif

