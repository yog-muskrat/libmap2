
#ifndef MTRPAI3D_H
#define MTRPAI3D_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifndef MTRBASE_H
  #include "mtrbase.h"
#endif

#ifndef MTRPALET_H
  #include "mtrpalet.h"
#endif

class _DLLCLASS TMapAccess;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ КЛАСС "ТРЕХМЕРНОЕ ОТОБРАЖЕНИЕ МАТРИЦЫ" +++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS  TMtr3D
{
 public:

  TMtr3D(TMapAccess* doc, long width=100, long height=100);
 ~TMtr3D();

  // Отобразить матрицу в BITMAP в трехмерном виде
  HBITMAP BuildMtr3Dold(MTR3DVIEW* parm);

  // Отобразить матрицу в BITMAP в трехмерном виде
  HBITMAP BuildMtr3D(MTL3DVIEW* parm);

  // Отобразить матрицу на экран в трехмерном виде
  void Paint(HDC hDC, MTR3DVIEW* parm);

  // Отобразить матрицу на экран в трехмерном виде
  void PaintEx(HDC hDC, MTL3DVIEW* parm);

  // Отобразить матрицу на экран в трехмерном виде
  // Использовать только при изменении угла наклона
  void PaintAngle(HDC hDC, MTL3DVIEW* parm);

  // Установить размер области вывода
  int SetDrawSize(long width, long height);

  // Установить диапазон отображаемых высот
  void SetHeightFilter(double hmin, double hmax);

  // Установить уровень затопления
  void SetHeightWater(double height);

 protected:

  // Создать два DIBа
  int CreateBitmap();

  // Удалить два DIBа
  void DeleteBitmap();

  // Отобразить DIB2 на устройство
  void PaintDevice(HDC hDC);

  // Отобразить сетку в плоскости с поворотом (в DIB1)
  void ShowGrid();

  // Отобразить цепочку матриц в плоскости с поворотом (в DIB1)
  void ShowMatrix();

  // Наложить тень в плоскости (в DIB1)
  void PutShadow();

  // Отобразить матрицу в трехмерном виде (из DIB1 в DIB2)
  void ShowMtr3D();

  // Установить палитру DIB
  void SetPaletteDib();

  // Установить палитру матрицы
  void SetPaletteMtr(int style);

  // Инициализировать палитру окна
  void SetupPalette();

  COLORREF PaletteShare[260]; // Общая палитра (служебные + цвета матрицы) 
  HPALETTE ViewPalette;       // Идентификатор палитры окна

  double VisualHmin;          // Диапазон отображаемых высот
  double VisualHmax;          //
  double HeightWater;         // Уровень затопления

  long DrawWidth,DrawHeight;  // Область вывода
  int DrawCenterX;            // Центр невыравненной области
  int DrawCenterY;
  double MatrixUnitShadow;    // Отношение масштаба в плане
                              // к масштабу по высоте (вычисляется)
  MTL3DVIEW Parm;             // Параметры вывода матрицы
  TMapAccess* MapDoc;         // Указатель на TMapAccess

  BITMAPINFOHEADER* hDib1Header;
  BITMAPINFO        hDib2Header;     
  BITMAPINFO        hDib3Header;
  RGBQUAD*    hDib1Palette;
  HDC         dcDib1;
  HDC         dcDib2;
  HDC         dcDib3;
  HPALETTE    dcDib1Palette;
  HBITMAP     hBitmap1;
  HBITMAP     hBitmap2;
  HBITMAP     hBitmap3;
  void*       lpBits1;
  void*       lpBits2;
  void*       lpBits3;
  char HUGER* lpDib1;
  char HUGER* lpDib2;
  char HUGER* lpDib3;

  unsigned short* HeightBuffer;  // Указатель на буфер высот

  int         IsBuild;           
};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ КЛАСС "ТРЕХМЕРНОЕ ОТОБРАЖЕНИЕ МАТРИЦЫ СЛОЕВ" +++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS  TMtl3D
{
 public:

  TMtl3D(TMapAccess* doc);
 ~TMtl3D();

  // Отобразить матрицу на экран в трехмерном виде
  void Paint(HDC hDC, MTL3DVIEW* parm);

 protected:

  // Установить размер области вывода
  int SetDrawSize(int width, int height);

  // Создать два DIBа
  int CreateBitmap();

  // Удалить два DIBа
  void DeleteBitmap();

  // Отобразить матрицу в BITMAP в трехмерном виде
  HBITMAP BuildMtl3D(MTL3DVIEW* parm);

  // Отобразить DIB2 на устройство
  void PaintDevice(HDC hDC);

  // Отобразить сетку в плоскости с поворотом (в DIB1)
  void ShowGrid();

  // Выполнить вертикальный срез в плоскости (в DIB1)
  void AngleCut();

  // Отобразить цепочку матриц в плоскости с поворотом (в DIB1)
  void ShowMatrix();

  // Наложить тень в плоскости (в DIB1)
  void PutShadow();

  // Отобразить матрицу в трехмерном виде (из DIB1 в DIB2)
  void Show3D();

  // Установить параметры визуализации
  void Set3DParm(MTL3DVIEW* parm);

  // Установить палитру рельефа матрицы (цветную, серую)
  void SetReliefPalette(int style);

  COLORREF PaletteShare[260]; // Общая палитра (цвета матрицы + служебные) 

  int MaxLayerCount;          // Максимальное число слоев матриц
  int DrawWidth, DrawHeight;  // Область вывода
  int DrawCenterX;            // Центр невыравненной области
  int DrawCenterY;
  double MatrixUnitShadow;    // Отношение масштаба в плане
                              // к масштабу по высоте (вычисляется)
  MTL3DVIEW Parm;             // Параметры вывода матрицы
  TMapAccess* MapDoc;         // Указатель на TMapAccess

  BITMAPINFOHEADER* hDib1Header;
  BITMAPINFOHEADER* hDib2Header;
  HDC         dcDib1;
  HDC         dcDib2;
  HPALETTE    dcDib1Palette;
  HBITMAP     hBitmap1;
  HBITMAP     hBitmap2;
  void*       lpBits1;
  void*       lpBits2;
  char HUGER* lpDib1;
  char HUGER* lpDib2;

  unsigned short* HeightBuffer;  // Указатель на буфер высот
  double* PowerBuffer;  // Указатель на буфер профиля переднего плана
  short* IndexBuffer;   // Указатель на буфер индексов
};

#endif  // MTRPAI3D_H
