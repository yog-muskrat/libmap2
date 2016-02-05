#ifndef MAPBASE_H
#define MAPBASE_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifndef RSTBASE_H
  #include "rstbase.h"
#endif

#ifndef MTRBASE_H
  #include "mtrbase.h"
#endif

#ifndef MTRPALET_H
  #include "mtrpalet.h"
#endif

#ifndef MAPSELC_H
  #include "mapselc.h"
#endif

#ifndef MAPPALET_H
  #include "mappalet.h"
#endif

#ifndef HIDETIN
 #ifndef TINBASE_H
   #include "tinbase.h"
 #endif
#endif

enum OUTPUTTYPE
{
  OUTPUT_DIB    = 0,
  OUTPUT_DEVICE = 1
};

// ----------------------------------------------------------------
// Типы функций визуализации и проверки видимости объектов
// ----------------------------------------------------------------
#ifndef WINCE
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


// Обобщенная цепочка Rst, Mtr, Mtq файлов  
// =========================================================
typedef struct RMFCHAIN
{
  // Общие для всех

#ifdef __cplusplus  
  RMFCHAIN() : Colors() {}

  RMFCHAIN*  Next;            // Указатель на следующую структуру
  RMFCHAIN*  Back;            // Указатель на предыдущую структуру
#else
  void*      Next;            // Указатель на следующую структуру
  void*      Back;            // Указатель на предыдущую структуру
#endif

  int        View;            // Признак видимости = Шаг маски (0-5)     
  int        ViewOrder;       // Порядок отображения (0/1 - под/над картой)
  int        MaskType;        // Тип маски (0-8)
  int        Free;
//   FILETIME   Condition;       // Состояние файла данных  

  DFRAME     Frame;              // Габариты в районе (элементы)
  DFRAME     FrameMeters;        // Габариты в районе (метры)
  double     Scale;              // Масштаб растра
  double     Precision;          // Точность растра
  double     MeterInElement;     // Scale / Precision
  double     Element;            // Приведенная точность (для RSTSHOW)
  unsigned
  char       ArrayIndex[256];    // Массив индексов соответствия цветов

  long int   TopScale;           // Знаменатель масштаба верхней границы видимости 
  long int   BottomScale;        // Знаменатель масштаба нижней границы видимости  

  // Для Rst
  int       Location;            // Признак привязки (0/1)
  int       InvisibleColors;     // Число неотображаемых цветов (по паспорту)
  unsigned
  char      IndexVisible[256];   // Признаки отображения цветов (0/1)

  // Для Rst и матриц качеств
#ifdef __cplusplus
  TBaseColors Colors;            // Цвета отображения растра
#else
  BASECOLORS  Colors;            // Цвета отображения растра
#endif

  // Для Mtr
  double    MinHeightValue;      // Минимальное и максимальное значения
  double    MaxHeightValue;      //  высот в матрице (в метрах)

  double MtrMinHeight;         // Мин. и макс. высота всей цепочки
  double MtrMaxHeight;         // в единицах текущей матрицы

  double dH;                   // Величина, обратная диапазону высот цепочки
                               // (для вычисления индекса в палитре)

  // Для Mtr и матриц качеств
  int    TypeHeight;           // Тип высот (абс=1,отн=0)

  // Для Mtq
  int    MtqShadow;            // Тень матрицы качества  

  // Общий класс данных
#ifdef __cplusplus
  TRmf      Rmf;
#else
  TRMFDATA  Rmf;
#endif
}
  RMFCHAIN;


// Краткая информация о цепочкe  
// =========================================================
typedef struct CHAININFO
{
 int         Count;         // Количество звеньев
 RMFCHAIN*   Begin;         // Первое звено цепочки
 int         CurrentNumber; // Номер активной матрицы в цепочке
}              CHAININFO;



typedef RMFCHAIN RSTCHAIN;
typedef RMFCHAIN MTRCHAIN;


// Цепочка пользовательских карт

typedef struct SITCHAIN
{
#ifdef __cplusplus           
  SITCHAIN() : Site(), Select(), Seek(), Real() { Next,Back = 0; }

  SITCHAIN*  Next;           // Указатель на следующую структуру
  SITCHAIN*  Back;           // Указатель на предыдущую структуру
#else
  void*      Next;           // Указатель на следующую структуру
  void*      Back;           // Указатель на предыдущую структуру
#endif
  TSite      Site;           // Пользовательская карта
  TMapSelect Select;         // Условия отображения
  TMapSelect Seek;           // Условия поиска
  TMapSelect Real;           // Маска наличия объектов на карте
  int    RealMode;           // Состояние карты для маски
  int        ViewOrder;      // ПРИЗНАК ОТОБРАЖЕНИЯ (0 - под картой, 1 - над картой) 
#ifdef LINUXAPI    
  unsigned
      char  ArrayIndex[256]; // Массив индексов соответствия цветов
#endif
}
  SITCHAIN;

#ifndef HIDETIN
// Цепочка TIN-файлов          

typedef struct TINCHAIN
{
  TINCHAIN() : Colors() {}

  TINCHAIN* Next;              // Указатель на следующую структуру
  TINCHAIN* Back;              // Указатель на предыдущую структуру

  long int  Mode;              // Режим доступа (Read/Write)
  long int  Share;             // Режим разделения данных

  long int  View;              // Признак видимости = Шаг маски (0-5)
  long int  ViewOrder;         // Порядок отображения (0/1 - под/над картой)

  long int  MaskType;          // Тип маски (0-8)
  long int  Free;              // Выравнивание

  DFRAME    Frame;             // Габариты в районе (элементы)  
  DFRAME    FrameMeters;       // Габариты в районе (метры)

  double    MinHeightValue;    // Минимальное значение высоты поверхности (метры)
  double    MaxHeightValue;    // Максимальное значение высоты поверхности (метры)

  long int  VertexCount;       // Kоличество вершин
  long int  TriangleCount;     // Kоличество треугольников

  long int  UserLabel;         // Пользовательский идентификатор
  long int  Length;            // Длина файла с заголовком

  long int  ModelType;         // Тип модели
  long int  Method;            // Метод построения модели

  long int  TopScale;          // Знаменатель масштаба верхней границы видимости
  long int  BottomScale;       // Знаменатель масштаба нижней границы видимости

  TBaseColors  Colors;         // Цвета отображения TIN-модели

  TTin      Tin;
}
  TINCHAIN;
#endif  // HIDETIN


// Указатель на текущую таблицу функций отображения     
// base - указатель на MAPBASE
#ifndef WINCE
typedef void _fastcall (*DEVICETABLE)(void* base, const POLYDATAEX* data,
                                      const char* parm, float viewscale);
#else
typedef void (_fastcall *DEVICETABLE)(void* base, const POLYDATAEX* data,
                                      const char* parm, float viewscale);
#endif

typedef struct MAPBASE
{
 // Описание векторной карты
 // --------------------------

 TMap Map;                // ВЕКТОРНАЯ КАРТА (ПЕРВАЯ ПЕРЕМЕННАЯ !)

 int VisualType;          // Вид отображаемой карты

 int RangeScale;          // Ранг из таблицы масштабного ряда для
                          // текущего масштаба карты

 long int ShowScale;      // Текущий масштаб отображения карты
 long int BaseScale;      // Базовый масштаб отображения карты

 TMapSelect Select;       // Условия выбора об'ектов для отображения
 TMapSelect Seek;         // Условия выбора об'ектов для обработки
 int ViewSeekFlag;        // Флаг поиска среди видимых об'ектов

 TMapSelect Real;         // Маска наличия об'ектов на карте
 int    RealMode;         // Состояние карты для маски


 // Данные для размещения карты
 // --------------------------

 void * MapBase;      // Указатель на структуру данных
                      // для синхронизации конструктора/деструктора

 DFRAME RegionPix;    // Габариты общего района в пикселах   
 FRAME DrawPix;       // Область перерисовки в пикселах
 FRAME SaveDrawPix;   // в районе работ (1-л.н.; 2-п.в.)

 DFRAME RegionDis;    // Габариты общего района в дискретах
 DFRAME DrawDis;      // Область перерисовки в дискретах
                      // в районе работ (1-л.н.; 2-п.в.)

 DFRAME DrawMet;      // Область перерисовки абсолютная
                      // в метрах (1-л.н.; 2-п.в.)

 double ZeroX;        // Координаты точки привязки карты
 double ZeroY;        // к прямоугольной системе координат (метры)

 double MetInDis;     // Метров на местности в одном дискрете
 double DisInMet;     // Число дискрет на метр местности

 double ViewScale;    // Текущий масштаб отображения
                      // = 5   -> Изображение увеличено в 5 раз
                      // = 0.1 -> Изображение уменьшено в 10 раз

 double VerticalPixel;    // Число точек на метр на устройстве
 double HorizontalPixel;  // Число точек на метр на устройстве
 double Discret;          // Число точек на метр на карте

 double HorDisInPix;     // Число точек карты в точке экрана
 double HorPixInDis;     // Число точек экрана в точке карты
 double VerDisInPix;     // Число точек карты в точке экрана
 double VerPixInDis;     // Число точек экрана в точке карты

 double Element;         // Число элементов на метр в растре
 double HorElemInPix;    // Число элементов растра в точке экрана
 double HorPixInElem;    // Число точек экрана в элементе растра
 double VerElemInPix;    // Число элементов растра в точке экрана
 double VerPixInElem;    // Число точек экрана в элементе растра

 double DisInElem;       // Число точек карты на элемент
 double ElemInDis;       // Число элементов в точке экрана

 double Angle;           // Угол поворота карты
 double SinTurn;         // sin угла поворота карты
 double CosTurn;         // cos угла поворота карты
 int TurnActive;         // Флаг активизации поворота


 FRAME ListDrawBorder;    // Границы отображаемой области в листе
                          // для контроля видимости объектов

 POLYDATAEX  PolyData;      // Описание метрики последнего обработанного
                          // объекта в области визуализации

 DOUBLEPOINT AreaInList;  // Положение области визуализации в
                          // текущем листе карты

 // Описание пользовательских карт
 // -------------------------------

 int         SitChainCount;    // Количество звеньев
 SITCHAIN *  SitChainBegin;    // Первое звено цепочки
 int         SitCurrentNumber; // Номер активной карты

 // Описание растровых карт
 // -------------------------------

 FRAME FrameFillPix;
 FRAME FrameRst;

 CHAININFO  RstChain;          // Сведения о растровой цепочке
 CHAININFO  MtqChain;          // Сведения о цепочке матриц качеств

 // Описание матричных карт
 // -------------------------------

 TMtrPalette  MtrPalette;      // Палитра матрицы

 int MtrShadow;                // Тень матриц высот      
 int Reserve;

 FRAME FrameMtr;

 double MtrChainMinHeight;     // Минимальная высота цепочки
 double MtrChainMaxHeight;     // Максимальная высота цепочки

                               
 int    MtrChainUserDiapason;  // Флаг установки пользовательского
                               // диапазона высот цепочки
                               // (MtrChainMinHeight, MtrChainMaxHeight)
                               // (1 - установлен пользовательский диапазон,
                               //  0 - диапазон установлен в SetRegion)
 int    Reserve2;

 CHAININFO  MtrChain;          // Сведения о матричной цепочке

 // Рабочие переменные отображения растра и матрицы
 // -----------------------------------------------

 int BorderFilter;      // Фильтр по рамке
 int MaskType;          // Тип маски
 int MaskStep;          // Шаг маски
 char Mask[8];          // Пиксельная маска

 int ESize;             // Размер элемента
 DFRAME* DFrameElem;    // Область растра в элементах
 double ShiftX,ShiftY;  // Поправки ошибок вычисления

 int StrCurrPix;        // Верхняя строка текущего блока (в системе Frame)
 int ColCurrPix;        // Левый столбец текущего блока (в системе Frame)
 int StrNextPix;        // Верхняя строка следующего блока (в системе Frame)
 int ColNextPix;        // Левый столбец следующего блока (в системе Frame)
 int BlockHeight;       // Высота текущего блока
 int BlockWidth;        // Ширина текущего блока
 int BlockWidth1;       // Ширина предыдущего блока (для алгоритма наложения теней)  
 int BlockWidth2;       // Ширина следующего блока  (для алгоритма наложения теней)
 int Visible;           // Флаг видимости блока (0,1,2)
 char* BlockAddr;       // Адрес прочитанного блока
 int StringBlockAddr;    // Номер строки прочитанного блока BlockAddr   
 int ColumnBlockAddr;    // Номер столбца прочитанного блока BlockAddr  
 char* ColumnAddr1;     // Указатели на столбцы в соседних блоках  
 char* ColumnAddr2;     // (для алгоритма наложения теней)
 double StringInBlockBegin;
 double ColumnInBlockBegin;
 double StringInBlockFloat;
 double ColumnInBlockFloat;

 unsigned char ColorFilter[256];  // Фильтр по цвету (для растра)
 /*  
 double MtrMinHeight;         // Мин. и макс. высота всей цепочки
 double MtrMaxHeight;         // в единицах текущей матрицы

 double dH;                   // Величина, обратная диапазону высот цепочки
                              // (для вычисления индекса в палитре)
 */

 VISUALTABLE* DibFunc;        // Указатель на текущую таблицу для DIB

 int TypeOutput;              // Способ отображения

 HPALETTE ViewPalette;        // Идентификатор палитры окна
 unsigned char
        ArrayIndexMap[272];   // Массив индексов соответствия цветов  

 BREAKCALL BreakCall;         // Функция обратного вызова
 long int  BreakParm;         // для прерывания отображения

 BEFOREPAINT BeforePaint;     // Функция обратного вызова      
 long int    BeforeParm;      // для рисования под картой

 // Переменные класса TPaintDevice
 // ---------------------------------

 HDC hdc;               // Контекст устройства
 HDC hdcDib;            // Контекст устройства вспомогательного DIB для подписей
 int Technology;        // Тип устройства

 double HorLogicalInch; // Пикселов устройства в логическом дюйме
                        // по горизонтали
 double VerLogicalInch; // Пикселов устройства в логическом дюйме
                        // по вертикали
 HDC Savehdc;
 int SaveTechnology;

 double SaveHorLogicalInch;
 double SaveVerLogicalInch;

 DRAWSIZE DrawSize;     // Ширина и высота области рисования

 // Переменные класса TPaintMetric
 // ---------------------------------

 COLORREF Palette[272];        // Палитра карты
 COLORREF PaletteFill[272];    // Палитра заливки площадных объектов
 COLORREF PaletteCMYK[272];    // Палитра карты CMYK       

 int ColorModel;               // Отображение карты с использованием цветовой модели(0-RGB, 1-CMYK)  
 long int ClearColor;          // Цвет очистки области рисования в DIB       
                               // (для RGB-0x0FFFFFFL, для CMYK-0x0000000L)
 int ColorCount;               // Количество цветов в CMYK палитре карты     
 int MapNumber;                // Номер отрисовываемой карты                 

 int FillIntensity;            // Интенсивность цвета заливки площадного
 int SaveFillIntensity;        // Интенсивность для печати
 float Intensity;              // Текущая интенсивность цвета заливки площадного

 double PixDeviceInPixScreen;   // Пикселов устройства в пикселе экрана
 double PixDeviceFontIn100Mkm;  // Пикселов устройства в десятых долях
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

 DEVICETABLE* DeviceFunc;     // Указатель на текущую таблицу

 int SelectColor;             // Цвет выделения объектов на карте
                              // (-1 - не выделять)
 int SelectThick;             // Толщина линии выделения объектов


 // Переменные класса TMapPaint
 // ---------------------------------

 int  FlagDib;                // Флаг работы с DIB (запоминается счетчик
                              // обращения к созданию DIB)

 TMapPalette MapPalette;      // Палитра отображаемой карты


 // Переменные класса TMapAccess
 // ---------------------------------

 int TotalSeekFlag;           // Флаг глобального поиска
 int TotalSelectFlag;         // Флаг выделения объектов на карте

 char MapDocName[MAX_PATH];   // Имя файла документа

#ifdef __cplusplus
 char MapIniName[MAX_PATH];   // Имя INI файла документа

 int  IsProjectActive;        // Признак открытия проекта
 char ProjectName[MAX_PATH];  // Имя файла проекта

 int  HideSplineFlag;         // Признак отмены построения сплайна
#endif

#ifdef WIN32API               
 HWND EventHandle;            // Идентификатор окна для сообщениях о событиях
 int  EventFlag;              // Флаг типов событий
#endif

 int  SkeepTextFlag;          // Признак выбора подписи в точке ПОСЛЕДНЕЙ   
 int  IsRestoreData;          // Признак восстановления списка открытых данных из INI-файла
}
  MAPBASE;



#endif  // MAPBASE_H
