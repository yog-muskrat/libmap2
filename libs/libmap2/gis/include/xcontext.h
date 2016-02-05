
#ifndef XCONTEXT_H           
#define XCONTEXT_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

typedef struct XCONTEXT  // ������ Windows HDC ��� XWindow
{
  Display * xcDisplay;   // ����� � X-��������
  Window    xcWindow;    // ������������� ����
  GC        xcContext;   // ����������� �������� ����
  DRAWPOINT xcPoint;     // ������������ ������������ ������� � ����
                         // (����� ������� ���� � ��������)
}
  XCONTEXT;

#define XHDC       XCONTEXT*

#endif  // XCONTEXT_H

