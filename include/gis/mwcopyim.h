
#ifndef MWCOPYIM_H
#define MWCOPYIM_H

#ifndef MAPTYPE_H
 #include "maptype.h"
#endif

#ifdef LINUXAPI                 
 #include "xmapvis.h"
#endif

#ifdef WIN32API 

#ifdef SOFTIMAGE
extern "C"
{
HBITMAP _MAPAPI imgCreateBitmap(HDC hdc, long int width, long int height,
                                void ** memory);
}
#endif

#define SOFTIMAGECELL     4

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ КЛАСС "ПЕРЕМЕЩЕНИЕ ИЗОБРАЖЕНИЯ КАРТЫ" +++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class TCopyImage
{
 public :

  TCopyImage();

  TCopyImage(TCopyImage& image);

  ~TCopyImage();

  // Освободить область памяти
  void CloseImage();

  // Выделить область памяти под изображение
  // клиентной области окна
  // При ошибке возвращает ноль
  int OpenImage(HWND hwnd);

  // Копировать содержимое клиентной области
  // окна в область памяти
  // При ошибке возвращает ноль
  int CopyClientToImage(HDC hdc, RECT& rect);

  // Копировать содержимое клиентной области
  // окна в область памяти
  // При ошибке возвращает ноль
  int CopyClientToImage(HWND hwnd);

  // Копировать содержимое области памяти
  // в клиентную область заданного окна
  // При ошибке возвращает ноль
  int CopyImageToClient(HWND hwnd = 0);

  // Копировать содержимое области фрагмента памяти
  // При ошибке возвращает ноль
  int CopyImageToClient(HWND hwnd, RECT& rect);

  // Копировать содержимое области фрагмента памяти
  // по заданному контексту
  // При ошибке возвращает ноль
  int CopyImageToClient(HDC hdc, RECT& rect, POINT& point);

  // Копировать содержимое области фрагмента памяти
  // по заданному контексту
  // При ошибке возвращает ноль
  int CopyImageToClient(HDC hdc, RECT& rect);

  // Запросить параметры для формирования изображения
  // При ошибке возвращает ноль
  HDC  GetImageDc() { return ImageDC; }
  RECT GetImageRect() { return ClientRect; }
  HWND GetHandle() { return Hwnd; }
#ifdef SOFTIMAGE
  void * GetMemory() { return Memory; }
#endif

  // Запросить высоту и ширину битовой области
  int Width() { return (ClientRect.right - ClientRect.left); }
  int Height() { return (ClientRect.bottom - ClientRect.top); }

 protected :

  // Выделить область памяти под изображение
  // клиентной области окна
  // При ошибке возвращает ноль
  int Allocate(HWND hwnd);

 protected :

  HBITMAP Image;
  HDC     ImageDC;
  RECT    ClientRect;
  HWND    Hwnd;
  HBITMAP OrgBitMap;

#ifdef SOFTIMAGE
  void *  Memory;      // Адрес битовой области
#endif
};

// --------------------------------------------------------
//  Инициализация объекта "образ экрана"
// --------------------------------------------------------
inline TCopyImage::TCopyImage()
{
  Image      = 0;
  ImageDC    = 0;
  Hwnd       = 0;
  OrgBitMap  = 0;

#ifdef SOFTIMAGE
  Memory     = 0;
#endif
}

inline TCopyImage::TCopyImage(TCopyImage& image)
{
  Image      = 0;
  ImageDC    = 0;
  Hwnd       = 0;
  OrgBitMap  = 0;
#ifdef SOFTIMAGE
  Memory     = 0;
#endif

  if (image.GetHandle() != 0)
    {
      ClientRect = image.GetImageRect();
      Allocate(image.GetHandle());
    }

  if (Image)
    {
      CopyClientToImage(image.GetImageDc(), (RECT&)image.GetImageRect());
    }
}

// --------------------------------------------------------
//  Деинициализация объекта "образ экрана"
// --------------------------------------------------------
inline TCopyImage::~TCopyImage()
{
  CloseImage();
}

// --------------------------------------------------------
//  Выделить область памяти под изображение
//  клиентной области окна
//  При ошибке возвращает ноль
// --------------------------------------------------------
inline int TCopyImage::Allocate(HWND hwnd)
{
  Hwnd = hwnd;

#ifndef SOFTIMAGE
  HDC Paint = ::GetDC(hwnd);
  if (Paint == 0) return 0;
#else
  ImageDC = ::CreateCompatibleDC(0);
  if (ImageDC == 0) return 0;
#endif

  // Эталон
#ifdef SOFTIMAGE
  Image  = imgCreateBitmap(ImageDC,ClientRect.RT - ClientRect.LT,
                           ClientRect.DN - ClientRect.UP, &Memory);
#else
  Image  = ::CreateCompatibleBitmap(Paint,ClientRect.RT - ClientRect.LT,
                                    ClientRect.DN - ClientRect.UP);
#endif
  if (Image)
    {
#ifndef SOFTIMAGE
      ImageDC = ::CreateCompatibleDC(0);
#endif
      if (ImageDC)
        OrgBitMap = (HBITMAP)::SelectObject(ImageDC, Image);
    }

#ifndef SOFTIMAGE
  // Освободить контекст
  ::ReleaseDC(hwnd,Paint);
#endif

  return 1;
}

// --------------------------------------------------------
//  Выделить область памяти под изображение
//  клиентной области окна
//  При ошибке возвращает ноль
// --------------------------------------------------------
inline int TCopyImage::OpenImage(HWND hwnd)
{
  if (hwnd == 0)
    {
      CloseImage();
      return 0;
    }

  if (hwnd == Hwnd)
    {
      int dx = ClientRect.RT - ClientRect.LT;
      int dy = ClientRect.DN - ClientRect.UP;

      ::GetClientRect(Hwnd, &ClientRect);

      int delta = (ClientRect.RT - ClientRect.LT - dx) +
                  (ClientRect.DN - ClientRect.UP - dy);
      if (delta == 0)
        {
          // Окно не изменилось
          return 1;
        }
    }

  CloseImage();

  ::GetClientRect(hwnd, &ClientRect);

  Allocate(hwnd);

  return (Image && ImageDC);
}

// --------------------------------------------------------
//  Копировать содержимое клиентной области
//  окна в область памяти
//  При ошибке возвращает ноль
// --------------------------------------------------------
inline int TCopyImage::CopyClientToImage(HDC hdc, RECT& rect)
{
  if ((hdc && ImageDC) == 0) return 0;

  // Сохранить образ окна в памяти
  ::BitBlt(ImageDC, rect.LT, rect.UP,                    
                   rect.RT - rect.LT,
                   rect.DN - rect.UP,
                   hdc, rect.LT, rect.UP, SRCCOPY);

  return 1;
}

// --------------------------------------------------------
//  Копировать содержимое клиентной области
//  окна в область памяти
//  При ошибке возвращает ноль
// --------------------------------------------------------
inline int TCopyImage::CopyClientToImage(HWND hwnd)
{
  if (OpenImage(hwnd) == 0) return 0;

  HRGN Region = ::CreateRectRgn(0,0,0,0);
  if (Region == 0) return 0;

  PAINTSTRUCT Ps;
  HDC Paint = ::BeginPaint(Hwnd,&Ps);

  // Определить видимую часть окна
  ::InvalidateRect(Hwnd,0,0);

  ::GetUpdateRgn(Hwnd,Region,0);
  ::SelectClipRgn(ImageDC,Region);

  // Сохранить образ окна в памяти
  ::BitBlt(ImageDC,0,0,
                  ClientRect.RT - ClientRect.LT,
                  ClientRect.DN - ClientRect.UP,
                  Paint,0,0,SRCCOPY);

  // Очистить невидимую часть окна белым цветом
  HBRUSH Brush = ::CreateSolidBrush(0x0FFFFFF);
  HRGN Clear   = ::CreateRectRgn(ClientRect.LT,
                                 ClientRect.UP,
                                 ClientRect.RT,
                                 ClientRect.DN);

  // clear ^= update;
  ::CombineRgn(Clear,Clear,Region,RGN_XOR);
  ::SelectClipRgn(ImageDC,0);
  ::FillRgn(ImageDC,Clear,Brush);
  ::DeleteObject(Region);
  ::DeleteObject(Clear);
  ::DeleteObject(Brush);

  ::EndPaint(Hwnd,&Ps);

  return 1;
}

// --------------------------------------------------------
//  Копировать содержимое области памяти
//  в клиентную область окна
//  При ошибке возвращает ноль
// --------------------------------------------------------
inline int TCopyImage::CopyImageToClient(HWND hwnd)
{
  if (hwnd == 0)   hwnd = Hwnd;
  if (hwnd == 0)   return 0;
  if (ImageDC == 0) return 0;

  HDC Screen = ::GetDC(hwnd);
  ::BitBlt(Screen,0,0,
                  ClientRect.RT - ClientRect.LT,
                  ClientRect.DN - ClientRect.UP,
                  ImageDC,
                  0,0,SRCCOPY);

  // Освободить контекст
  ::ReleaseDC(hwnd,Screen);

  return 1;
}

// --------------------------------------------------------
//  Копировать содержимое области фрагмента памяти
//  При ошибке возвращает ноль
// --------------------------------------------------------
inline int TCopyImage::CopyImageToClient(HWND hwnd, RECT& rect)
{
  if ((hwnd && ImageDC) == 0) return 0;
  HDC hdc = ::GetDC(hwnd);

  ::BitBlt(hdc,rect.LT,rect.UP,
               rect.RT - rect.LT,
               rect.DN - rect.UP,
               ImageDC,
               rect.LT,rect.UP,SRCCOPY);

  // Освободить контекст
  ::ReleaseDC(hwnd, hdc);

  return 1;
}

// --------------------------------------------------------
//  Копировать содержимое области фрагмента памяти
//  по заданному контексту
//  При ошибке возвращает ноль
// --------------------------------------------------------
inline int TCopyImage::CopyImageToClient(HDC hdc, RECT& rect)
{
  if ((hdc && ImageDC) == 0) return 0;

  ::BitBlt(hdc,rect.LT,rect.UP,
               rect.RT - rect.LT,
               rect.DN - rect.UP,
               ImageDC,
               rect.LT,rect.UP,SRCCOPY);
  return 1;
}

// --------------------------------------------------------
//  Копировать содержимое области фрагмента памяти
//  по заданному контексту
//  При ошибке возвращает ноль
// --------------------------------------------------------
inline int TCopyImage::CopyImageToClient(HDC hdc, RECT& rect, POINT& point)
{
  if ((hdc && ImageDC) == 0) return 0;

  ::BitBlt(hdc,point.x,  point.y,
               rect.RT - rect.LT,
               rect.DN - rect.UP,
               ImageDC,
               rect.LT,rect.UP,SRCCOPY);
  return 1;
}

// --------------------------------------------------------
// Освободить область памяти
// --------------------------------------------------------
inline void TCopyImage::CloseImage()
{
  if (OrgBitMap && ImageDC) ::SelectObject(ImageDC,OrgBitMap);
  if (Image)
    ::DeleteObject(Image);
  Image  = 0;
  if (ImageDC)
    ::DeleteDC(ImageDC);
  ImageDC = 0;
  Hwnd   = 0;
  OrgBitMap = 0;

#ifdef SOFTIMAGE
  Memory     = 0;
#endif
}

#else   // LINUXAPI           
#include "xcontext.h"

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ КЛАСС "ПЕРЕМЕЩЕНИЕ ИЗОБРАЖЕНИЯ КАРТЫ" +++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class TCopyImage
{
 public :

  TCopyImage();

  ~TCopyImage();

  // Освободить область памяти
  void CloseImage();

  // Выделить область памяти под изображение
  // клиентной области окна
  // При ошибке возвращает ноль
  int OpenImage(HWND hwnd);

  // Копировать содержимое области фрагмента памяти
  // по заданному контексту
  // При ошибке возвращает ноль
  int CopyImageToClient(HDC hdc, RECT& rect);

  // Запросить параметры для формирования изображения
  // При ошибке возвращает ноль
  HDC  GetImageDc() { return (HDC)&Image;}
  HWND GetHandle()  { return Hwnd; }

 protected :
  XIMAGEDESC        Image;
  HWND              Hwnd;
  XImage            *xImage;
  XWindowAttributes Attribute;
};

// --------------------------------------------------------
//  Инициализация объекта "образ экрана"
// --------------------------------------------------------
inline TCopyImage::TCopyImage()
{
  Hwnd       = 0;
  xImage     = 0;
  memset((char *)&Image, 0x0, sizeof(XIMAGEDESC));
}

// --------------------------------------------------------
//  Деинициализация объекта "образ экрана"
// --------------------------------------------------------
inline TCopyImage::~TCopyImage()
{
  CloseImage();
}

// --------------------------------------------------------
// Выделить область памяти под изображение
// клиентной области окна
// При ошибке возвращает ноль
// --------------------------------------------------------
inline int TCopyImage::OpenImage(HWND hwnd)
{
  if (hwnd == 0)
    {
      CloseImage();
      return 0;
    }
  Window win = ((XCONTEXT *)hwnd)->xcWindow;
  Window Win = 0;
  if (Hwnd)
    Win = ((XCONTEXT *)Hwnd)->xcWindow;

  if (win == Win)
    {
      XWindowAttributes attrib;
      int dx = Attribute.width;                                         
      int dy = Attribute.height;

      XGetWindowAttributes(((XCONTEXT *)hwnd)->xcDisplay, win, &attrib);

      attrib.width = attrib.width / 4;
      attrib.width = attrib.width * 4;

      int delta = (attrib.width - dx) + (attrib.height - dy);
      if (delta == 0)
        {
          // Окно не изменилось
          return 1;
        }
    }

  CloseImage();
  Hwnd = hwnd;

  XGetWindowAttributes(((XCONTEXT *)Hwnd)->xcDisplay, ((XCONTEXT *)Hwnd)->xcWindow, &Attribute);   

  Attribute.width = Attribute.width / 4;
  Attribute.width = Attribute.width * 4;

  // Получим образ окна карты в памяти
  xImage = XGetImage(((XCONTEXT *)Hwnd)->xcDisplay, ((XCONTEXT *)Hwnd)->xcWindow,
                     0, 0, Attribute.width, Attribute.height,
                     0x0FFFFFFFF, ZPixmap);

  if (xImage)
  {
    Image.Point    = xImage->data;
    Image.Width    = Attribute.width;
    Image.Height   = Attribute.height;
    Image.Depth    = mapGetMapScreenDepth();
    Image.CellSize = (Image.Depth) / 8;
    Image.RowSize  = Image.Width * Image.CellSize;
  }

  return (xImage > 0);
}

// --------------------------------------------------------
//  Копировать содержимое области фрагмента памяти
//  При ошибке возвращает ноль
// --------------------------------------------------------
inline int TCopyImage::CopyImageToClient(HDC hdc, RECT& rect)
{
  int width, height;                                                    

  if ((hdc && xImage) == 0) return 0;

  if ((rect.RT - rect.LT) > Attribute.width) width = Attribute.width;
  else width = rect.RT - rect.LT;
  if ((rect.DN - rect.UP) > Attribute.height) height = Attribute.width;
  else height = rect.DN - rect.UP;

  XPutImage(((XCONTEXT *)hdc)->xcDisplay, ((XCONTEXT *)hdc)->xcWindow,
            ((XCONTEXT *)hdc)->xcContext, xImage,
            rect.LT, rect.UP, rect.LT, rect.UP,
            width, height);

  return 1;
}

// --------------------------------------------------------
// Освободить область памяти
// --------------------------------------------------------
inline void TCopyImage::CloseImage()
{
  if (xImage) XDestroyImage(xImage);
  xImage = 0;
  memset((char *)&Image, 0x0, sizeof(XIMAGEDESC));
  Hwnd  = 0;
}
#endif     // WIN32API

#endif

