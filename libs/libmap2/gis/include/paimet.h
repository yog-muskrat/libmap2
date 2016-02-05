
#ifndef PAIMET_H
#define PAIMET_H

#ifndef MAPGDI_H
  #include "mapgdi.h"
#endif

#ifndef MAPMETR_H
  #include "mapmetr.h"
#endif

#ifndef MAPSCRIP_H
  #include "mapscrip.h"
#endif

#define PAINTSTEP     1024       // Шаг вывода DIB в окно
#define PAINTLONG    32000       // (число объектов)

#define TESTSIZE     512                     // Рабочее число элементов
#define TESTMAX      (TESTSIZE+32)           // Число элементов с резервом
#define TESTSTEP     (TESTMAX/8)             // Ширина строки в байтах
#define TESTBUFFER   (TESTMAX * TESTSTEP)    // Размер буфера

enum OUTPUTTYPE
{
  OUTPUT_DIB    = 0,
  OUTPUT_DEVICE = 1
};

// ----------------------------------------------------------------
// Типы функций визуализации и проверки видимости объектов
// ----------------------------------------------------------------
#if defined(__BORLANDC__) || defined(LINUXAPI)                          // 09/03/07
typedef void _fastcall (*VISUALTABLE)(void* pm, const POLYDATAEX* data,
                                      const char * parm, float viewscale);

typedef int  _fastcall (*TESTTABLE)(void* pm, const POLYDATAEX* data,
                                     const char* parm, float viewscale);
#else
typedef void (_fastcall *VISUALTABLE)(void* pm, const POLYDATAEX* data,
					   			                           const char * parm, float viewscale);

typedef int  (_fastcall *TESTTABLE)(void* pm, const POLYDATAEX* data,
                                    const char* parm, float viewscale);
#endif

// Указатель на текущую таблицу функций отображения     // 11/06/01
// base - указатель на MAPBASE
#if defined(__BORLANDC__) || defined(LINUXAPI)                          // 09/03/07
typedef void _fastcall (*DEVICETABLE)(void* base, const POLYDATAEX* data,
                                      const char* parm, float viewscale);
#else
typedef void (_fastcall *DEVICETABLE)(void* base, const POLYDATAEX* data,
                                      const char* parm, float viewscale);
#endif

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++ КЛАСС ОТОБРАЖЕНИЯ ОБ'ЕКТОВ КАРТЫ В МЕТРИЧЕСКИХ ЕДИНИЦАХ +++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TPaintMetric : public TMapMetric
{
 public:

  TPaintMetric();
 ~TPaintMetric();

  // Запросить/Установить интенсивность цвета заливки площадного
  // объекта при выводе на устройство (0 - 100)
  int _fastcall GetFillIntensity();
  int _fastcall SetFillIntensity(int intensity);

  // Установить палитру для DIB
  void _fastcall SetPaletteDib(COLORREF* palette, int count);

  // Вызывать для получения цвета, заносимого в DIB
  CELL IndexPaletteShare(int index)
  { return PaletteDIB[((unsigned char)index)];}

  // Определить цвет в формате RGB (24 бита)
  COLORREF _fastcall GetColor24(COLORREF color);

  // Определить цвет
  COLORREF _fastcall GetColor(COLORREF color);

  // Определить цвет
  COLORREF _fastcall GetColorText(COLORREF color);

  // Отобразить DIB в окно
  void _fastcall PaintDIB2WIN(HDC hdc, int x, int y);

  // Отобразить окно в DIB
  void _fastcall PaintWIN2DIB(HDC hdc, int x, int y);

 // Установить пошаговый вывод DIB в окно
 // (1 - короткий период, 0 - длинный)
 // Возвращает предыдущее значение
 int SetPaintStep(int flag)
 {
#ifndef HIDEPAINTSTEP              // 17/04/06
   int Old = PaintStep;
   if (flag)
     PaintStep = PAINTSTEP;
   else
     PaintStep = PAINTLONG;
   return Old;
#else
   return PaintStep;
#endif
 }

 int GetPaintStep()
 {
   return (PaintStep != PAINTLONG);
 }

 // Проверить счетчик отображения по шагу
 // Возвращает :  1 - пора отображать, 0 - пока не время
 int CheckPaintCount()
 {
   if (ObjectDrawCount++ < PaintStep)
     return 0;
   ObjectDrawCount = 0;
   return 1;
 }


  // Запросить/Установить значение полупрозрачности текущей карты
  // при выводе на устройство (0 - 100)
  unsigned int _fastcall GetCurrentTranslucency() const;
  unsigned int _fastcall SetCurrentTranslucency(unsigned int translucency); 

 public:

 HDC  dcWindow;         // Контекст окна
 HDC  hdc;              // Контекст устройства
 HDC  hdcDib;           // Контекст устройства вспомогательного DIB для подписей
 int  Technology;       // Тип устройства

 double HorLogicalInch; // Пикселов устройства в логическом дюйме
                        // по горизонтали
 double VerLogicalInch; // Пикселов устройства в логическом дюйме
                        // по вертикали
 HDC Savehdc;
 int SaveTechnology;

 double SaveHorLogicalInch;
 double SaveVerLogicalInch;

 // Функции SCRIPT-вывода
 SCRIPTTABLEEX ScriptTable;                                 // 05/06/07
 int IsScriptTableActive;

 // Флаг высветления верхней линии (реки, дороги)
 int TopLine;                                               // 12/07/06

 // Буфер для штриховки полигонов
 char ShadowBuffer[4096];                                   // 24/07/06

 // Текущая палитра
 COLORREF PaletteRGB[260];          // Для Windows-функций
 CELL     PaletteDIB[260];          // Для Dib
#if CELLSIZE == 2                   // 10/03/08
 CELL     PaletteDIBRezerv[260];
#else
#if CELLSIZE == 1
 CELL     PaletteDIBRezerv1[260];
 CELL     PaletteDIBRezerv2[260];
 CELL     PaletteDIBRezerv3[260];
#endif
#endif
 int CurrentBright;                 // Яркость палитры текущей карты
 int CurrentContrast;               // Контрастность палитры текущей карты
 unsigned int CurrentTranslucency;		// Полупрозрачность текущей карты

 COLORREF Palette[272];        // Палитра карты
 COLORREF PaletteFill[272];    // Палитра заливки площадных объектов
 COLORREF PaletteCMYK[272];    // Палитра карты CMYK       // 19/02/04

 int ColorModel;               // Отображение карты с использованием цветовой модели(0-RGB, 1-CMYK)  // 19/02/04
 long int ClearColor;          // Цвет очистки области рисования в DIB       // 19/02/04
                               // (для RGB-0x0FFFFFFL, для CMYK-0x0000000L)
 int ColorCount;               // Количество цветов в CMYK палитре карты     // 18/03/04
 int MapNumber;                // Номер отрисовываемой карты                 // 18/03/04

 int FillIntensity;            // Интенсивность цвета заливки площадного
 int SaveFillIntensity;        // Интенсивность для печати
 float Intensity;              // Текущая интенсивность цвета заливки площадного

 double PixDeviceInPixScreen;  // Пикселов устройства в пикселе экрана
 double PixDeviceFontIn100Mkm; // Пикселов устройства в десятых долях
                               // миллиметра (для шрифта)
                               
 double SavePixDeviceInPixScreen;
 double SavePixDeviceFontIn100Mkm;

 double HorPixDeviceInMkm;   // Пикселов устройства в мкм
 double VerPixDeviceInMkm;   // Пикселов устройства в мкм
 double PixDeviceFontInMkm;  // Пикселов устройства высоты шрифта
                             // в мкм высоты символов

 double SaveHorPixDeviceInMkm;
 double SaveVerPixDeviceInMkm;
 double SavePixDeviceFontInMkm;

 DRAWSIZE  szSeek;                  // Ширина и высота области поиска  // 01/12/00
 DRAWSIZE  szSeekSq;                // Ширина и высота области поиска для площадных

 int       ObjectDrawCount;         // Счетчик выведенных в DIB объектов
 int       PaintStep;               // Шаг вывода DIB в окно

 VISUALTABLE* DibFunc;              // Указатель на текущую таблицу для DIB
 DEVICETABLE* DeviceFunc;           // Указатель на текущую таблицу

 enum TYPEOUTPUT { DIB = 0, DEVICE = 1 };
 int TypeOutput;                    // Способ отображения
 int VisualType;                    // Вид отображаемой карты

 unsigned char
        ArrayIndexMap[272];         // Массив индексов соответствия цветов  // 23/07/02

 int SelectColor;                   // Цвет выделения объектов на карте
                                    // (-1 - не выделять)
 int SelectThick;                   // Толщина линии выделения объектов
};

// Технология устройства
extern int PrintTechnology;   // 23/04/01

// Размер области отображения
extern DRAWSIZE PrintDrawSize;

// Таблицы функций рисования
extern DEVICETABLE FillFunc[256];     // Рисование с заливкой
extern DEVICETABLE FillFuncPS[256];   // Рисование с заливкой (для PostScript)
extern DEVICETABLE GlassFunc[256];    // Рисование прозрачное
extern DEVICETABLE ContourFunc[256];  // Рисование контурное
                                      // 28/01/03
extern DEVICETABLE SquareFunc[256];   // Рисование заливок площадей
extern DEVICETABLE LineFunc[256];     // Рисование линий, точечных, векторных
extern DEVICETABLE TextFunc[256];     // Рисование подписей, шаблонов

// Инициализация
void _fastcall pmetInit(TPaintMetric* pmet); // 09/07/01

// Освобождение
void _fastcall pmetFree(TPaintMetric* pmet); // 09/07/01

// Установить интенсивность цвета заливки площадного
// объекта при выводе на устройство (0 - 100)
int _fastcall pmetSetFillIntensity(TPaintMetric* pmet, int intensity);
int _fastcall pmetGetFillIntensity(TPaintMetric* pmet);

// Пикселов устройства в 1 метре по вертикали и горизонтали
double _fastcall pmetGetHorPixDeviceInMetr(TPaintMetric* pmet);
double _fastcall pmetGetVerPixDeviceInMetr(TPaintMetric* pmet);

// Установить контекст устройства (по окончании работы
// с контекстом всегда выполнять RestoreHDCMap)
#ifdef __cplusplus   // 25/04/01
void _fastcall pmetSetHDCMap(TPaintMetric* pmet, HDC hDC, 
                             double horPixInInch = -1, double verPixInInch = -1);
#else
void _fastcall pmetSetHDCMap(TPaintMetric* pmet, HDC hDC, 
                             double horPixInInch, double verPixInInch);    // 10/02/05
#endif

// Восстановить контекст устройства
void _fastcall pmetRestoreHDCMap(TPaintMetric* pmet);

// Установить палитры карты и заливки площадных объектов // 25/04/01
void _fastcall pmetSetPaletteMap(TPaintMetric* pmet, int count, COLORREF* palette, int intensity);

// Запросить цветовую модель вывода карты (0 - RGB, 1 - CMYK)  // 03/03/04
int  _fastcall pmetGetColorModel(TPaintMetric* pmet);

// Установить цветовую модель вывода карты (0 - RGB, 1 - CMYK) // 03/03/04
void  _fastcall pmetSetColorModel(TPaintMetric* pmet, int colorModel);

// Установить CMYK-палитру карты             // 02/03/04
//void _fastcall pmetSetPaletteCMYK(TPaintMetric* pmet, int Count, long int* palette);
void _fastcall pmetSetPaletteCMYK(TPaintMetric* pmet, int Count, long int* palette, long int number, int intensity);

// Установить цвет заливки площадного объекта
COLORREF _fastcall pmetGetColorMapFill(TPaintMetric* pmet, unsigned char index);

// Установка цвета печати контура
COLORREF _fastcall pmetGetColor(TPaintMetric* pmet, COLORREF color);

// Установить цвет заливки площадного объекта
COLORREF _fastcall pmetGetColorFill(TPaintMetric* pmet, COLORREF color);

// Пересчет параметров (пикселы экрана -> пикселы устройства)
long _fastcall pmetScreen2Device(TPaintMetric* pmet, float pixel);

// Пересчет параметров (0.001 мм -> пикселы устройства)
long _fastcall pmetMetric2Device(TPaintMetric* pmet, long metric);

// Возвратить цвет из текущей палитры
COLORREF _fastcall pmetGetColorMap(TPaintMetric* pmet, unsigned char index);

// Вертикальная штриховка полигона
void _fastcall pmetVerticalFrameColorShade(TPaintMetric* pmet,
                                           const POLYDATAEX* pdata,
                                           const IMGVECTORGRADIENT * parm,
                                           float viewscale);

//-----------------------------------------------------------------
// Функции рисования (параметры в микронах)
//-----------------------------------------------------------------

void _fastcall pmetLineThin(void* pm, const POLYDATAEX* data,
                            const char* parm, float scaleview);
void _fastcall pmetLine(void* pm, const POLYDATAEX* data,
                        const char* parm, float scaleview);
void _fastcall pmetDot(void* pm, const POLYDATAEX* data,
                       const char* parm, float scaleview);
void _fastcall pmetShiftDot(void* pm, const POLYDATAEX* data,
                            const char* parm, float scaleview);

void _fastcall pmetSquare(void* pm, const POLYDATAEX* data,
                          const char* parm, float scaleview);
void _fastcall pmetSquareCross(void* pm, const POLYDATAEX* data,
                               const char* parm, float scaleview);
void _fastcall pmetMultiSquareMark(void* pm, const POLYDATAEX* data,
                                   const char* parm, float scaleview);
void _fastcall pmetMultiMark(void* pm, const POLYDATAEX* data,
                             const char* parm, float scaleview);
void _fastcall pmetCircle(void* pm, const POLYDATAEX* data,
                          const char* parm, float scaleview);

void _fastcall pmetText(void* pm, const POLYDATAEX* data,
                        const char* parm, float scaleview);
void _fastcall pmetTrueText(void* pm, const POLYDATAEX* data,
                            const char* parm, float scaleview);
void _fastcall pmetTrueType(void* pm, const POLYDATAEX* data,
                            const char* parm, float scaleview);

void _fastcall pmetTemplate(void* pm, const POLYDATAEX* data,
                            const char* parm, float scaleview);

// Набор примитивов (147)
void _fastcall pmetDraw(void* pm, const POLYDATAEX* data,
                        const char* parm, float scaleview);

// Векторная штриховка площадных объектов (153)
void _fastcall pmetShadeSquare(void* pm, const POLYDATAEX * data,
                               const char * parm, float viewscale);

// Преобразовать цвет с учетом яркости и контрастности (154)
void _fastcall pmetSquareGlass(void * pm, const POLYDATAEX* data,
                               const char* parm, float scaleview);

// Преобразовать цвет с учетом яркости, контрастности и тона (164)
void _fastcall pmetSquareToneGlass(void * pm, const POLYDATAEX* data,
                                   const char* parm, float scaleview);  // 05/01/06

// Преобразовать цвет с учетом яркости, контрастности, тона и прозрачности (167)
void _fastcall pmetPolygonGlass(void * pm, const POLYDATAEX* data,
                                const char* parm, float scaleview);  // 26/01/09

// Преобразовать цвет с учетом яркости, контрастности, тона и прозрачности (168)
void _fastcall pmetLineGlass(void * pm, const POLYDATAEX* data,
                             const char* parm, float viewscale);

// Прозрачный площадной объект, заполненный векторными объектами
void _fastcall pmetSquareVector(void* pm, const POLYDATAEX* pdata,
                                const char* Parm, float viewscale);

// Наборная штриховая линия (158)
void _fastcall pmetDashLine(void* pm, const POLYDATAEX* data,
                            const char* parm, float viewscale);

// Специальные функции (221)
void _fastcall pmetCallPaint(void* pm, const POLYDATAEX * data,
                             const char * parm, float scaleview);

//-----------------------------------------------------------------
// Функции рисования (параметры в пикселах)
//-----------------------------------------------------------------

// Площадной
void _fastcall DeviceSquare(TPaintMetric* pmet, const POLYDATAEX* data, IMGSQUARE* parm);

// Линия сплошная
void _fastcall DeviceLine(TPaintMetric* pmet, const POLYDATAEX* data, IMGLINE* parm, double thick);

// Линия сплошная утолщающаяся
void _fastcall DeviceThickenLine(TPaintMetric* pmet, const POLYDATAEX* data, COLORREF color,
                                 double thick, double thickEnd);

                                 // Линия сплошная утолщающаяся к середине от концов
void _fastcall DeviceMiddleThickenLine(TPaintMetric* pmet, const POLYDATAEX* data, COLORREF color,
                                 double thick, double thickMiddle);
// Линия сплошная
void _fastcall DeviceLinePlotter(TPaintMetric* pmet, const POLYDATAEX* data, IMGLINE* parm);

// Линия штриховая
void _fastcall DeviceLineDash(TPaintMetric* pmet, const POLYDATAEX* data, IMGDOT* parm, double thick);

// Линия штриховая смещеннная
void _fastcall DeviceShiftDash(HDC hdc, const POLYDATAEX* data, IMGDOTSHIFT* parm);

// Площадной, заполненный точечными
void _fastcall DeviceSquareMark(TPaintMetric* pmet, const POLYDATAEX* data, IMGSQUAREMARK* parm, char* mask);

// Точечный
void _fastcall DeviceMark(TPaintMetric* pmet, const POLYDATAEX* data, IMGMARK* parm, float scaleview);  // 25/10/01

// Подпись
void _fastcall deviceText(TPaintMetric* pmet, const POLYDATAEX* data, IMGTEXT* parm, float scaleview);
void _fastcall deviceTrueText(TPaintMetric* pmet, const POLYDATAEX* data, IMGTRUETEXT* parm, float scaleview);

// Символ
void _fastcall deviceTrueType(TPaintMetric* pmet, const POLYDATAEX* data, IMGTRUETYPE* truetype, float scaleview);

// Отображение линии из двух точек                        // 10/07/06
void _fastcall pmetDrawLine(TPaintMetric* pmet, int x1, int y1,
                                                int x2, int y2);

//  Отображение полилинии                                 // 10/07/06
void _fastcall pmetPolyLine(TPaintMetric* pmet, POINT * point, int count);

//  Рисование площадного объекта выбранной кистью         // 10/07/06
void _fastcall pmetDrawSquare(TPaintMetric* pmet, POINT* point, int count);

//  Рисование сложного площадного объекта выбранной кистью   10/07/06
void _fastcall pmetDrawPolygons(TPaintMetric* pmet, const POLYDATAEX* data);

//  Установить параметры отображаемой линии                  10/07/06
XHPEN _fastcall pmetSelectPen(TPaintMetric* pmet, int thick, unsigned long color);

//  Установить параметры отображаемой линии               // 10/07/06
XHPEN _fastcall pmetSelectFastPen(TPaintMetric* pmet, int thick, unsigned long color);

//  Установить параметры заливки полигона (кисть)         // 10/07/06
XHBRUSH _fastcall pmetSelectBrush(TPaintMetric* pmet, unsigned long color);

// Вывод строки текста или символа                         10/07/06
void _fastcall pmetDrawText(TPaintMetric* pmet, int x, int y,
                            TCHAR * text, int length,            // 24/04/03
                            LOGFONT* font, int align, long color);

// Вывод строки текста или символа UNICODE                 05/06/07
void _fastcall pmetDrawTextUn(TPaintMetric* pmet, int x, int y,
                              WCHAR * text, int length,
                              LOGFONT* font, int align, long color);
#endif  // PAIMET_H


