
#ifndef MWSCREEN_H
#define MWSCREEN_H

#ifndef MAPTYPE_H
 #include "maptype.h"
#endif

#ifndef MWCOPYIM_H
 #include "mwcopyim.h"
#endif


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ КЛАСС "ПЕРЕМЕЩЕНИЕ ИЗОБРАЖЕНИЯ КАРТЫ" +++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class TCopyScreen : public TCopyImage
{
 public :

  TCopyScreen() : TCopyImage() { X = 0; Y = 0; }

  // Копировать содержимое клиентной области
  // окна в область памяти с запоминанием текущего положения
  // окна в изображении
  // При ошибке возвращает ноль
  int CopyClientToImage(HDC hdc, RECT& rect, int x, int y)
  {
    X = x; Y = y;
    return TCopyImage::CopyClientToImage(hdc, rect);
  }

  // Копировать содержимое клиентной области
  // окна в область памяти с запоминанием текущего положения
  // окна в изображении
  // При ошибке возвращает ноль
  int CopyClientToImage(HWND hwnd, int x, int y)
  {
    int  ret;
    RECT rect;
    HDC  hdc;
    OpenImage(hwnd);
    X = x; Y = y;
    hdc  = ::GetDC(hwnd);
    ret  = TCopyImage::CopyClientToImage(hdc, ClientRect);
    ::ReleaseDC(hwnd, hdc);
    return ret;
  }

  // Копировать содержимое фрагмента области памяти
  // по заданному контексту с учетом
  // изменения позиции окна (скроллированием)
  // При ошибке возвращает ноль
  int CopyImageToClient(HDC hdc, RECT& rect, int x, int y)
  {
    if (ScrollImage(hdc, rect, x, y) == 0)
      return TCopyImage::CopyImageToClient(hdc, rect);
    return 1;
  }

 protected :

  // Скроллировать содержимое памяти с учетом
  // изменения позиции окна
  int ScrollImage(HDC hdc, RECT& rect, int x, int y);

 protected :

  int X;                // Координаты верхнего левого угла окна
  int Y;                // в изображении
};

#endif