
#ifndef XCONTEXT_H           
#define XCONTEXT_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

typedef struct XCONTEXT  // Аналог Windows HDC для XWindow
{
  Display * xcDisplay;   // Связь с X-сервером
  Window    xcWindow;    // Идентификатор окна
  GC        xcContext;   // Графический контекст окна
  DRAWPOINT xcPoint;     // Расположение отображаемой области в окне
                         // (левый верхний угол в пикселах)
}
  XCONTEXT;

#define XHDC       XCONTEXT*

#endif  // XCONTEXT_H

