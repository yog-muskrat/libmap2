
#ifndef MAPCNT_H
#define MAPCNT_H

#ifndef MAPDEF_H
  #include "mapdef.h"
#endif

#ifndef MAPINFO_H
  #include "mapinfo.h"
#endif

#ifndef PAIMET_H
  #include "paimet.h"
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

 #ifndef TINBASE_H
   #include "tinbase.h"
 #endif

#ifndef HIDEMTL
 #ifndef MTLBASE_H
   #include "mtlbase.h"
 #endif
#endif


typedef struct DIBCONTEXT                               
{
  char* lpDib;               // Указатель на битовую область DIB

  int DibWidth;              // Ширина битовой области (в байтах)
  int DibHeight;             // Высота битовой области
  int DibElementSize;        // Размер элемента (в байтах) 3 или 4

  int VisualType;            // Тип визуализации
  int Reserve;
}
  DIBCONTEXT;

// Цепочка пользовательских карт
typedef struct SITCHAIN
{
  SITCHAIN() : Site(), Select(), Seek(), Real(), Active() { Next,Back = 0; RealMode = 0;}

  SITCHAIN*  Next;           // Указатель на следующую структуру
  SITCHAIN*  Back;           // Указатель на предыдущую структуру

  TSite      Site;           // Пользовательская карта
  TMapSelect Select;         // Условия отображения
  TMapSelect Seek;           // Условия поиска
  TMapSelect Real;           // Маска наличия объектов на карте
  TMapSelect Active;         // Условия выбора об'ектов для обработки 

  int        RealMode;       // Состояние карты для маски
  int        ViewOrder;      // ПРИЗНАК ОТОБРАЖЕНИЯ (0 - под картой, 1 - над картой) 
#ifdef LINUXAPI    
  unsigned
      char  ArrayIndex[256]; // Массив индексов соответствия цветов
#endif
}
  SITCHAIN;

// Обобщенная цепочка Rst, Mtr, Mtq файлов  
// =========================================================
typedef struct RMFCHAIN
{
  // Общие для всех
  RMFCHAIN() : Colors(), Rmf() { Next = 0; Back = 0; dH = 1;}

  RMFCHAIN*  Next;            // Указатель на следующую структуру
  RMFCHAIN*  Back;            // Указатель на предыдущую структуру

  int        View;            // Признак видимости = Шаг маски (0-5)     
  int        ViewOrder;       // Порядок отображения (0/1 - под/над картой)
  int        MaskType;        // Тип маски (0-8)
  int        Free;

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
  TBaseColors Colors;            // Цвета отображения растра

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
  TRmf      Rmf;
}
  RMFCHAIN;


// Краткая информация о цепочкe  
// =========================================================
typedef struct _DLLCLASS CHAININFO
{
  CHAININFO() { Count = 0; Begin = 0; CurrentNumber = 0; }

  int         Count;         // Количество звеньев
  RMFCHAIN*   Begin;         // Первое звено цепочки
  int         CurrentNumber; // Номер активной матрицы в цепочке
}
  CHAININFO;

typedef RMFCHAIN RSTCHAIN;
typedef RMFCHAIN MTRCHAIN;

#ifndef HIDEMTL
// Цепочка MTL-файлов           
typedef struct MTLCHAIN
{
  MTLCHAIN() : Mtl() { Next = 0; Back = 0; dH = 1;}

  MTLCHAIN* Next;            // Указатель на следующую структуру
  MTLCHAIN* Back;            // Указатель на предыдущую структуру

  int       Mode;            // Режим доступа (Read/Write)
  int       Share;           // Режим разделения данных

  int       View;            // Признак видимости = Шаг маски (0-5)     
  int       ViewOrder;       // Порядок отображения (0/1 - под/над картой)
  int       MaskType;        // Тип маски (0-8)
  int       Transparent;     // Вес цвета матрицы (от 0 до 100 ) 

  DFRAME    Frame;           // Габариты в районе (элементы)
  DFRAME    FrameMeters;     // Габариты в районе (метры)
  double    Scale;           // Масштаб растра
  double    Precision;       // Точность матрицы
  double    MeterInElement;  // Scale / Precision
  double    Element;         // Приведенная точность (BaseScale / Precision)
  unsigned
      char  ArrayIndex[256]; // Массив индексов соответствия цветов

  double    MinHeightValue;  // Минимальное и максимальное значения
  double    MaxHeightValue;  //  высот в матрице (в метрах)
  double    BotLevelHeight;  // Высота нижнего уровня матрицы (в метрах)
  double    MaxSummaryPower; // Максимальная суммарная мощность
                             // слоев матрицы (в метрах)  

  double MtrMinHeight;       // Мин. и макс. высота всей цепочки
  double MtrMaxHeight;       // в единицах текущей матрицы

  double dH;                 // Величина, обратная диапазону высот цепочки
                             // (для вычисления индекса в палитре)

  long int   TopScale;       // Знаменатель масштаба верхней границы видимости  
  long int   BottomScale;    // Знаменатель масштаба нижней границы видимости  

  int       LayerCount;      // Количество слоев

  TMtl      Mtl;             // Mатрица слоев
}
  MTLCHAIN;

#endif      // !HIDEMTL


// Цепочка TIN-файлов          
typedef struct TINCHAIN
{
  TINCHAIN() : Tin(){ 
     Next = 0;
     Back = 0;
     View = 1;  // отображение полное
     ViewOrder = 0; // под картой
  }

  TINCHAIN* Next;              // Указатель на следующую структуру
  TINCHAIN* Back;              // Указатель на предыдущую структуру

  int        View;             // Признак видимости
  int        ViewOrder;        // Порядок отображения (0/1 - под/над картой)
  
  TTin      Tin;               // Модель тин
}
  TINCHAIN;


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ КЛАСС ДАННЫХ: ЭЛЕКТРОННАЯ КАРТА + РАСТР ++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TMapControl : public TPaintMetric
{
public:

  // Инициализация/Закрытие района работ
  TMapControl();

  ~TMapControl();

  // Закрыть все данные
  void Close(void);

  // Определить наличие открытых данных
  int IsActive();

  // Запросить активную карту
  TMap * ActiveMap()
     { return GetMap(ActiveMapNumber()); }

  // Запросить/Установить номер активной карты
  int ActiveMapNumber();

  int ActiveMapNumber(int number)
     {
       if ((number > SiteCount()) || (number < 0))
         return 0;
       return SitCurrentNumber = number;
     }

  // Запросить условное название карты по номеру
  // Если номер равен 0, возвращается название "главной карты",
  // иначе - название соответствующей пользовательской карты
  // При ошибке возвращается пустая строка
  const char * MapSheetName(int number = 0);

  // Запросить описание карты
  // Если номер равен 0, возвращается описание "главной карты",
  // иначе - описание соответствующей пользовательской карты
  // При ошибке возвращается ноль
  TMap * GetMap(int number = 0);

  // Запросить название файла карты по номеру
  // Если номер равен 0, возвращается название файла "главной карты",
  // иначе - название файла соответствующей пользовательской карты
  // При ошибке возвращается пустая строка
  const char * MapFileName(int number = 0);

  // Запросить условия выбора объектов для отображения
  // Если номер равен 0, возвращаются условия "главной карты",
  // иначе - условия соответствующей пользовательской карты
  // При ошибке возвращается ноль
  TMapSelect * GetSelect(int number = 0)
     { return GetViewSelect(number); }

 // ************************************************************
 //                                                            *
 //            МАСШТАБИРОВАНИЕ КАРТЫ И ОТОБРАЖЕНИЕ             *
 //                                                            *
 // ************************************************************

public :

 // Изменить масштаб отображения карты
 double ChangeViewScale(double change);

 // Запросить ближайший масштаб из таблицы масштабов
 // ... 100000,200000,500000, ...
 long GetNewShowScale(long scale);

 // Установить коэффициент масштабирования карты
 double SetViewScale(double scale);

 // Запросить текущий масштаб отображения
 long GetShowScale() { return ShowScale; }
 double GetRealShowScale();

 // Установить масштаб отображения карты
 long SetShowScale(long scale);

 // Отобразить открытые данные
 int ShowData();

 // Пересчитать общие габариты района работ
 void SetRegion();

 // Запросить базовый масштаб отображения
 // (устанавливается по карте, при отсутствии карты - по матрице,
 //                            при отсутствии матриц - по растру)
 long GetBaseScale() {return BaseScale;}


 // ************************************************************
 //                                                            *
 //            ДОСТУП К "ГЛАВНОЙ КАРТЕ"                        *
 //                                                            *
 // ************************************************************


public :

  // Открыть векторные данные
  // При ошибке возвращает ноль
  int OpenMap(const char * mapname, int mode);

  // Закрыть векторные данные
  void CloseMap(void);

  // Установка вида отображения или печати объектов
  int SetVisualType(int type);
  int GetVisualType() { return (int)VisualType; }

  // Типы визуализации объектов
  enum VISUALTYPE {FILL            = VT_SCREEN,
                   SKELET          = VT_SCREENCONTOUR,
                   FILLPRINT       = VT_PRINT,
                   GLASSPRINT      = VT_PRINTGLASS,
                   CONTOURPRINT    = VT_PRINTCONTOUR,
                   FILLPRINTDIB    = VT_PRINTRST,
                   GLASSPRINTDIB   = VT_PRINTGLASSRST,
                   CONTOURPRINTDIB = VT_PRINTCONTOURRST};

  // Установка цветовой модели палитры при отображении объектов
  int SetColorModel(int colorModel);
  int GetColorModel() { return (int)ColorModel; }


  // ************************************************************
  //                                                            *
  //      СПРАВОЧНЫЕ ЗАПРОСЫ К "ВЕКТОРНОЙ ЭЛЕКТРОННОЙ КАРТЕ"    *
  //                                                            *
  // ************************************************************

public :

 // Открыть транзакцию перед выполнением операций редактирования карты
 // number - номер редактируемой карты
 // type   - код транзакции (функция редактора ...)
 // При ошибке возвращает ноль

 int OpenTransaction(int number, int type);

 // Закрыть транзакцию после выполнения
 // группы взаимосвязанных операций редактирования карты
 // number - номер редактируемой карты

 void CloseTransaction(int number);

 // Установить адрес функции оповещения о редактировании
 // карты

 int SetChangeCall(CHANGECALL call, long int parm);

 // Запросить - усиановлен ли адрес функции оповещения

 int IsChangeCall() { return (ChangeCall != 0); }

 // Запросить базовый масштаб карты

 long GetMapScale();

 // Запросить номер карты в цепочке
 // При ошибке возвращает -1

 int _fastcall GetMapNumber(TMap * map);

 // Запрос описания ресурсов векторной карты по номеру

 TMapRsc * GetResource(int number = 0);

 // Запрос условий выбора объектов для визуализации

 TMapSelect * GetViewSelect(int number = 0);

 // Запрос условий выбора объектов при поиске

 TMapSelect * GetSeekSelect(int number = 0);

 // Запрос маски наличия объектов на карте

 TMapSelect * GetRealSelect(int number = 0);

 // Согласовать маску наличия объектов на карте

 void AdjustRealSelect(int number,int force = 0);

 // Флажки, определяющие порядок поиска объектов
 // Первый в цепочке,последний,следующий за найденым ранее,предыдущий
 // WO_CANCEL - искать вместе с удаленными объектами (иначе,пропускать)
 // WO_INMAP - искать в заданной карте
 // (в т.ч. пользовательской => object->Map)

 enum SEEKTYPE { WO_FIRST = 0, WO_LAST = 2,
                 WO_NEXT  = 4, WO_BACK = 8, WO_PREV = 8,
                 WO_CANCEL = 16,
                 WO_INMAP  = 32, WO_VISUAL = 64};

 // Параметр object содержит адрес структуры, в которую будет
 // записан результат поиска (этот адрес возвращается при успешном
 // завершении).
 // frame - область поиска в дискретах

 MAPOBJDESC * _fastcall WhatObject(MAPOBJDESC * object, DFRAME * frame,
                                   int flag = WO_FIRST,
                                   TMapSelect * select = 0);

 // Поиск объекта по диапазону уникальных номеров
 // При ошибке возвращает ноль

 MAPOBJDESC * _fastcall SeekObject(MAPOBJDESC * object,KEYSELECT * select,
                                   int flag = WO_FIRST);

 // Поиск объектов по заданным условиям среди всех объектов
 // Если объект не найден - возвращает ноль

 MAPOBJDESC * _fastcall SeekObject(MAPOBJDESC * object,TMapSelect * select,
                                   int flag = WO_FIRST);

 // Поиск объекта по уникальному номеру в заданном листе карты
 // При ошибке возвращает ноль

 int _fastcall SeekObjectInList(TMap * map, int list,
                                long key, int flag);

 protected :

 // Поиск объектов по заданным условиям среди всех объектов
 // Если объект не найден - возвращает ноль

 MAPOBJDESC * _fastcall SeekObjectInMap(MAPOBJDESC * object,TMapSelect * select,
                                        int flag = WO_FIRST, int nMap = 0);


 // Поиск объектов по заданным условиям среди отображаемых объектов
 // (пересечение заданных условий с условиями из переменной "Select")
 // Если объект не найден - возвращает ноль

 MAPOBJDESC * _fastcall SeekViewObjectInMap(MAPOBJDESC * object,TMapSelect * select,
                                            int flag = WO_FIRST, int nMap = 0);

 // Поиск объекта по диапазону уникальных номеров в карте
 // При ошибке возвращает ноль

 MAPOBJDESC * _fastcall SeekObjectInMapByKey(MAPOBJDESC * object,
                                             KEYSELECT * select,
                                             int flag, int nMap);
 public :

 TMap       Map;          // ВЕКТОРНАЯ КАРТА

 TMapSelect Select;       // Условия выбора об'ектов для отображения
 TMapSelect Seek;         // Условия поиска об'ектов
 TMapSelect Real;         // Маска наличия об'ектов на карте
 TMapSelect Active;       // Условия выбора об'ектов для обработки 

 long int ShowScale;      // Текущий масштаб отображения карты
 int      RangeScale;     // Ранг из таблицы масштабного ряда для
                          // текущего масштаба карты
 int      ViewSeekFlag;   // Флаг поиска среди видимых об'ектов
 int      RealMode;       // Состояние карты для маски

  // ************************************************************
  //                                                            *
  //        ДОСТУП К "ПОЛЬЗОВАТЕЛЬСКОЙ ЭЛЕКТРОННОЙ КАРТЕ"       *
  //                                                            *
  // ************************************************************

 public :

  // Запросить число открытых карт (занесенных в цепочку)
  // При ошибке возвращает ноль

  int IsSiteActive() { return (GetSiteCount() > 0); }
  int GetSiteCount() { return SiteCount(); }
  int SiteCount() { return SitChainCount; }

  // Закрыть карту по ее последовательному номеру в списке
  // Если номер равен нулю - закрываются все карты

  void CloseSite(int number = 0);

  // Запросить элемент цепочки по номеру
  // При ошибке возвращается ноль

  SITCHAIN* GetSiteChain(int number);

  // Открыть карту (добавить в цепочку)
  // Возвращает номер карты в цепочке
  // При ошибке возвращает ноль

  int OpenSite(const char * name, int mode);

  // Запросить/Установить признак редактируемости карты по номеру
  // При установке возвращает старое значение
  // При ошибке возвращается -1

  int MapEdit(int number, int flag = -1);

  // Запросить/Установить признак видимости карты по номеру
  // При установке возвращает старое значение
  // При ошибке возвращается -1

  int MapVisible(int number, int flag = -1);

  // Запросить/Установить порядок отображения  
  //  (0 - под картой, 1 - над картой)
  // При ошибке возвращает -1
  int MapViewOrder(int number, int order = -1);

  // Запросить/Установить признак разрешения выбора объекта карты
  // При установке возвращает старое значение
  // При ошибке возвращается -1

  int MapInquiry(int number, int flag = -1);

  // Поменять очередность отображения ПК        
  // oldNumber - номер файла в цепочке
  // newNumber - устанавливаемый номер файла в цепочке
  //  При ошибке возвращает 0
  int ChangeOrderSiteShow(int oldNumber, int newNumber);

public :

 int         SitChainCount;    // Количество звеньев
 SITCHAIN *  SitChainBegin;    // Первое звено цепочки
 int         SitCurrentNumber; // Номер активной карты

 int         ViewMapNumber;    // Отображаемая карта или -1
 int         ViewListNumber;   // Отображаемый лист  или -1
 int         ViewObjectNumber; // Отображаемый объект или -1

  // ************************************************************
  //                                                            *
  //            ДОСТУП К "РАСТРОВОЙ ЭЛЕКТРОННОЙ КАРТЕ"          *
  //                                                            *
  // ************************************************************

public :

  // Активизировать растр из цепочки растровых данных
  // При ошибке возвращает ноль

  RSTCHAIN*  ActiveRst(int number) { return GetRstChain(number); }

  // Открыть растровые данные (добавить в цепочку растров)
  // Возвращает номер растового файла в цепочке растров
  // При ошибке возвращает ноль

  int OpenRst(const char * name, int mode);

  // Открыть растровые данные (заменить в цепочке растров)
  // При ошибке возвращает ноль

  int ChangeRst(RSTCHAIN * chain, const char * name, int mode = 0);

  // Закрыть растровые данные (удалить из цепочки)
  // number - номер растрового файла в цепочке
  // Если number == 0, закрываются все растровые данные

  void CloseRst(int number = 0);

  // Запросить число открытых растров (занесенных в цепочку)
  // При ошибке возвращает ноль

  int GetRstCount() { return RstCount(); }
  int RstCount()    { return RstChain.Count; }
  int IsRstActive() { return (RstCount() > 0); }

  // Запросить элемент цепочки по номеру
  // При ошибке возвращается ноль

  RSTCHAIN* GetRstChain(int number);

  // Запросить номер цепочки по имени файла         
  // При ошибке возвращается ноль

  int GetRstNumberByName(const char * name);

  // Запросить растр или уменьшенную копию

  TRmf * GetRstClass(RSTCHAIN * chain, int duplicate);

  // Запросить число цветов в палитре растра
  // Если палитра более 256 цветов - возвращает ноль !
  // При ошибке возвращается ноль

  int GetRstColorCount(int number);

  // Запросить имя файла растровых данных
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

  const char * GetRstName(int number);


  // Запрос/Установка текущего номера растра  

  int GetRstCurrentNumber() { return RstChain.CurrentNumber; }
  int SetRstCurrentNumber(int number)
                            { return RstChain.CurrentNumber = number; }

  // Отображение растров цепочки
  // order - признак отображения (0 - под картой, 1 - над картой)

  void ShowRstPlace(int order = 0, DIBCONTEXT* dc = 0);  

  // Рисование открытых растров (занесенных в цепочку)
  // number - номер в цепочке (number = 0  -  отобразить все)

  void ShowRst(int number = 0);

  // Установить точность растра в цепочке и
  // пересчитать общие габариты района работ
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

  int SetRstPrecision(int number,double precision);

  // Запросить габариты растра в районе работ
  // Возвращает указатель на габариты в элементах растра
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

  DFRAME * GetRstFrame(int number);

  // Запросить габариты растра в районе работ
  // Возвращает указатель на габариты растра в метрах
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

  DFRAME * GetRstFrameMeters(int number);

  // Запросить данные о проекции растра  
  // number - номер файла в цепочке
  // mapregister - адрес структуры, в которой будут размещены
  // данные о проекции
  // При ошибке возвращает ноль

  int GetRstProjectionData(int number, MAPREGISTEREX* mapregister);  

  // Установить данные о проекции растра  
  // number - номер файла в цепочке
  // mapregister - адрес структуры
  // При ошибке возвращает ноль
  int SetRstProjectionData(int number, MAPREGISTEREX* mapregister);

  // Запросить/Установить видимость растра
  // Если растр не виден - возвращает ноль
  // При ошибке возвращает -1
  int CheckRstView(int number);
  int SetRstView(int number,int view);

  // Запросить/Установить тип маски отображения растра (0-8)
  // При ошибке возвращает -1
  int GetRstMaskType(int number);                       
  int SetRstMaskType(int number,int masktype);

  // Запросить/Установить признак отображения цвета
  // При ошибке возвращает -1
  int CheckRstPaletteView(int number, int value);
  int SetRstPaletteView(int number,int color,int value);

  // Запросить/Установить порядок отображения
  //  (0 - под картой, 1 - над картой)
  // При ошибке возвращает -1
  int RstViewOrder(int number, int order = -1);

  // Запросить адрес активной палитры растра
  // (с учетом яркости и контрасности)
  // number - номер файла в цепочке
  // При ошибке возвращает 0
  COLORREF* GetRstPalette(int number);

  // Запросить адрес эталонной палитры растра
  // (без учета яркости и контрасности)
  // number - номер файла в цепочке
  // При ошибке возвращает 0
  COLORREF* GetRstStandardPalette(int number);

  // Запросить/Установить яркость палитры (от -4 до 4)
  // number - номер файла в цепочке
  // При ошибке возвращает 0
  int GetRstBright(int number);
  int SetRstBright(int number,int bright);

  // Запросить/Установить контрастность палитры (от -4 до 4)
  // number - номер файла в цепочке
  // При ошибке возвращает 0
  int GetRstContrast(int number);
  int SetRstContrast(int number,int contrast);

  //  Запись в палитру выбранного цвета
  //  number - номер файла в цепочке
  //  При ошибке возвращает 0
  int SetRstColor(int number,COLORREF color,int index);

  //  Обновить активную палитру с нулевой яркостью и контрастностью
  //  number - номер файла в цепочке
  //  При ошибке возвращает 0
  int RestoreRstPalette(int number);

  // Запросить видимость цвета (для 16- и 256-цветных растров)  
  //  number - номер файла в цепочке
  //  index  - индекс цвета в палитре растра(начиная с 0)
  //  Возвращает: 1 - цвет с данным индексом отображается
  //              0 - цвет с данным индексом не отображается
  //  При ошибке возвращает -1
  int CheckVisibilityColor(int number,int index);

  // Установить видимость цвета (для 16- и 256-цветных растров)  
  //  number - номер файла в цепочке
  //  index  - индекс цвета в палитре растра(начиная с 0)
  //  value: 1 - включить отображение цвета с данным индексом
  //         0 - отключить отображение цвета с данным индексом
  //  При ошибке возвращает 0
  int SetVisibilityColor(int number,int index, int value);

  // Установить видимость цвета (для 16- и 256-цветных растров)  
  //  number - номер файла в цепочке
  //  index  - индекс цвета в палитре растра(начиная с 0)
  //  value: 1 - включить отображение цвета с данным индексом
  //         0 - отключить отображение цвета с данным индексом
  //  Сохранение видимости цветов в заголовке файла растра(а также в INI-файле)
  //  При ошибке возвращает 0
  int SetVisibilityColorInRstFile(int number,int index, int value);

  // Запросить значение инверсии растра 
  // Если изображение растра позитивное - возвращает ноль
  // Если изображение растра негативное - возвращает 1
  // При ошибке возвращает -1
  int CheckInversionRst(int number);

  // Инвертировать растровую карту    
  // value:
  // 0 - установить изображение растра позитивным
  // 1 - установить изображение растра негативным
  //  При ошибке возвращает 0
  int InvertRst(int number, int value);

  // Установить рамку растра
  int SetRstBorderPlane(int number, TDataEdit* data);

  // Запросить рамку растра                  
  //  При ошибке возвращает 0
  TDataEdit* GetRstBorderPlane(int number);

  // Установка отображения растра по рамке    
  // value = 1 - отобразить растр по рамке
  //       = 0 - отобразить растр без учета рамки
  int ShowRstByBorder(int number, int value);

  // Определение способа отображения растра(относительно рамки)    
  // Возвращает 1 - при отображении растра по рамке
  //            0 - при отображении растра без учета рамки
  // При ошибке возвращает -1
  int CheckShowRstByBorder(int number);

  // Установка отображения растра по маске изображения   
  // value = 1 - отобразить растр по рамке
  //       = 0 - отобразить растр без учета рамки
  int ShowRstByMask(int number, int value);

  // Определение способа отображения растра(относительно маски изображения)    
  // Возвращает 1 - при отображении растра по маске изображения
  //            0 - при отображении растра без учета маски изображения
  // При ошибке возвращает -1
  int CheckShowRstByMask(int number);

  //  Инициализировать звено цепочки растровых данных
  void InitRstChainUnit(RSTCHAIN* rstchain, int mini = 0);

  // Поменять очередность отображения растровых данных     
  // oldNumber - номер файла в цепочке
  // newNumber - устанавливаемый номер файла в цепочке
  //  При ошибке возвращает 0
  int ChangeOrderRstShow(int oldNumber, int newNumber);

// protected :

  // Определение попадания растра в видимую клиентную область
  int CheckViewRmf();

  // Отобразить растр
  int ShowChainRst(int number, DIBCONTEXT* dc);                      

  // Отобразить блока растра в DIB
  void _fastcall ShowBlockRstDib(TRmf & rst, DIBCONTEXT* dc,         
                                 TBaseColors * colors);

  // Отобразить блока растра в DIB
  void _fastcall ShowBlockRstDib256(TRmf & rst, DIBCONTEXT* dc,     
                                    TBaseColors * colors);          

  // Отобразить блока растра на устройство
  void _fastcall ShowBlockRstDevice(TRmf & rst, TBaseColors * colors);  

public :

 FRAME FrameFillPix;
 FRAME FrameRst;

 CHAININFO  RstChain;          // Сведения о растровой цепочке

  // ************************************************************
  //                                                            *
  //            ДОСТУП К "МАТРИЧНОЙ ЭЛЕКТРОННОЙ КАРТЕ"          *
  //                                                            *
  // ************************************************************

public :

  // Открыть заданную матрицу, если она не открыта.
  // Текущей становится матрица "number".
  // Возвращает указатель на объект, связанный
  // с открываемой матрицей. При ошибке возвращает ноль.

  RMFCHAIN* ActiveMtr(int number) { return IsOpenMtr(number); }
  RMFCHAIN* IsOpenMtr(int number) { return GetChain (number); }

  // Закрыть матричные данные (удалить из цепочки)
  // number - номер матричного файла в цепочке
  // Если number == 0, закрываются все матричные данные

  void CloseMtr(int number = 0);

  // Открыть матричные данные (заменить в цепочке растров)
  // При ошибке возвращает ноль

  int ChangeMtr(RMFCHAIN * chain, const char * name, int mode = 0);

  // Запросить число занесенных в цепочку матриц

  int GetMtrCount() { return MtrCount(); }
  int MtrCount()    { return MtrChain.Count; }
  int IsMtrActive() { return (MtrChain.Count > 0); }    

  // Установить число (number) занесенных в цепочку матриц

  int SetMtrCount(int number) { return MtrChain.Count = number; }

  // Запрос/Установка адреса первого звена цепочки матриц

  RMFCHAIN* GetMtrChainBegin() { return MtrChain.Begin; }
  RMFCHAIN* SetMtrChainBegin(RMFCHAIN* mtrchainbegin)
                               { return MtrChain.Begin = mtrchainbegin; }

  // Запрос/Установка текущего номера открытой матрицы

  int GetMtrCurrentNumber() { return MtrChain.CurrentNumber; }
  int SetMtrCurrentNumber(int number)
                            { return MtrChain.CurrentNumber = number; }

  // Запросить элемент цепочки по номеру
  // При ошибке возвращается ноль

  RMFCHAIN* GetChain(int number);

  // Запросить элемент цепочки матриц качеств по номеру
  // При ошибке возвращается ноль

  RMFCHAIN* GetMtqChain(int number);

  // Запросить данные о проекции матрицы качеств          
  // number - номер файла в цепочке
  // mapregisterex - адрес структуры, в которой будут размещены
  // данные о проекции
  // При ошибке возвращает ноль
  int GetMtqProjectionData(int number, MAPREGISTEREX* mapregisterex);

  // Установить данные о проекции матрицы качеств    
  // number - номер файла в цепочке
  // mapregister - адрес структуры
  // При ошибке возвращает ноль
  int SetMtqProjectionData(int number, MAPREGISTEREX* mapregister);

  // Запросить номер в цепочке для матрицы, расположенной
  // в заданной точке
  // number - порядковый номер, найденной матрицы в точке
  // (1 - первая в данной точке, 2 - вторая ...)
  // При ошибке возвращается ноль

  int GetMtrNumberInPoint(double x, double y, int number);

  // Запросить описание файла матричных данных
  // number - номер файла в цепочке
  // describe - адрес структуры, в которой будет размещено
  // описание матрицы
  // При ошибке возвращает ноль

  int GetMtrDescribe(int number, MTRDESCRIBE* describe);

  // Запросить данные о проекции матричных данных
  // number - номер файла в цепочке
  // projectiondata - адрес структуры, в которой будут размещены
  // данные о проекции
  // При ошибке возвращает ноль

  int GetMtrProjectionData(int number, MTRPROJECTIONDATA* projectiondata);

  // Запросить данные о проекции матричных данных         
  // number - номер файла в цепочке
  // mapregisterex - адрес структуры, в которой будут размещены
  // данные о проекции
  // При ошибке возвращает ноль
  int GetMtrProjectionDataEx(int number, MAPREGISTEREX* mapregisterex);

  // Установить данные о проекции матричных данных   
  // number - номер файла в цепочке
  // mapregister - адрес структуры
  // При ошибке возвращает ноль
  int SetMtrProjectionDataEx(int number, MAPREGISTEREX* mapregister);

  // Запросить описание диапазона высот матрицы с номером
  // number в цепочке
  // colornumber - номер диапазона высот
  // colordesc - адрес структуры, в которой будет размещено
  // описание диапазона высот
  // При ошибке возвращает ноль

  int GetMtrColorDesc(int number, int colornumber, MTRCOLORDESCEX* colordesc);

  // Установить цвет диапазона высот матрицы с номером
  // number в цепочке
  // colornumber - номер диапазона высот
  // При ошибке возвращает ноль

  int SetMtrColor(int number,COLORREF color,int colornumber);

  // Запросить имя файла матричных данных
  // number - номер файла в цепочке
  // При ошибке возвращает ноль

  const char* GetMtrName(int number);

  // Запросить предельные значения высот цепочки матриц (в метрах)

  double GetHeightMin() {return MtrChainMinHeight;}
  double GetHeightMax() {return MtrChainMaxHeight;}

  // Установить/Запросить глубину тени матрицы высот
  // value - флаг наложения тени (от 0 до 16)
  //   MTRSHADOW_NONE   =  0,   // Тень отсутствует
  //   MTRSHADOW_PALE   =  1,   // Бледная
  //   MTRSHADOW_WEAK   =  2,   // Слабая
  //   MTRSHADOW_MIDDLE =  4,   // Средняя
  //   MTRSHADOW_HEAVY  =  8,   // Сильная
  //   MTRSHADOW_DEEP   = 16,   // Глубокая

  int SetMtrShadow(int value);                          
  int GetMtrShadow();

  // Установить/Запросить интенсивность тени матрицы высот
  // value - интенсивность тени (от 0 до 100)

  int SetMtrShadowIntensity(int value);                 
  int GetMtrShadowIntensity();

  // Установить/Запросить флаг установки пользовательского
  // диапазона высот цепочки матриц высот
  // (1 - установлен пользовательский диапазон,
  //  0 - диапазон установлен в SetRegion)

  int SetMtrChainUserDiapason(int value);               
  int GetMtrChainUserDiapason();

  // Выбор значения абсолютной высоты в заданной точке.
  // Координаты точки (x,y) задаются в метрах в системе координат
  // векторной карты. Возвращает значение высоты в метрах.
  // В случае ошибки при выборе высоты и в случае необеспеченности
  // заданной точки матричными данными возвращает ERRORHEIGHT.

  double GetHeightValue(double x, double y);
  double GetHeightValue(DOUBLEPOINT* point)
    { return GetHeightValue(point->x,point->y); }

  // Выбор значения абсолютной высоты в заданной точке из матрицы
  // с номером number в цепочке.                        
  // number - номер матрицы в цепочке.
  // Координаты точки задаются в метрах в системе координат
  // векторной карты. Возвращает значение высоты в метрах.
  // В случае ошибки при выборе высоты и в случае необеспеченности
  // заданной точки матричными данными возвращает ERRORHEIGHT.
  double GetHeightValue(int number,double x, double y);

  // Занесение значения абсолютной высоты в элемент матрицы,
  // соответствующий заданной точке.
  // number - номер матрицы в цепочке.
  // Координаты точки (x,y) и значение высоты (h) задаются в метрах
  // в системе координат векторной карты.
  // В случае ошибки возвращает ноль.

  int PutHeightValue(long int number, double x, double y, double h);
  int PutHeightValue(long int number, DOUBLEPOINT* point, double h)
    { return PutHeightValue(number,point->x,point->y,h); }

  // Выбор значения абсолютной высоты в заданной точке по самой точной
  // матрице.
  // Координаты точки задаются в метрах в системе координат
  // векторной карты. Возвращает значение высоты в метрах.
  // В случае ошибки при выборе высоты и в случае необеспеченности
  // заданной точки матричными данными возвращает ERRORHEIGHT.

  double GetPrecisionHeightValue(double x, double y);
  double GetPrecisionHeightValue(DOUBLEPOINT* point)
    { return GetPrecisionHeightValue(point->x,point->y); }

  // Расчет абсолютной высоты методом треугольников в заданной точке
  // по матрице с наименьшим размером элемента (более точной).
  // Высота вычисляется по самой точной матрице высот,а в случае
  // необеспеченности заданной точки данными матриц высот -
  // по самой точной матрице слоев.
  // Координаты точки (x,y) задаются в метрах в системе координат
  // векторной карты. Возвращает значение высоты в метрах.
  // В случае ошибки при выборе высоты и в случае необеспеченности
  // заданной точки матричными данными возвращает ERRORHEIGHT.

  double GetPrecisionHeightTriangle(double x, double y);

  // Выбор массива значений абсолютных высот, соответствующих
  // логическим элементам, лежащим на заданном отрезке.
  // Координаты точек, задающих начало и конец отрезка
  // (FirstPoint,SecondPoint) задаются в метрах в системе
  // координат векторной карты.
  // Размер массива высот, заданного адресом HeightArray,
  // должен соответствовать запрашиваемому количеству высот
  // (HeightCount), в противном случае возможны ошибки работы
  // с памятью.
  // В случае необеспеченности логического элемента матричными
  // данными его значение равно ERRORHEIGHT.
  // В случае ошибки при выборе высот возвращает ноль.

  int GetHeightArray (double*       HeightArray,
                      int           HeightCount,
                      DOUBLEPOINT*  FirstPoint,
                      DOUBLEPOINT*  SecondPoint);

  // Открыть матричные данные (добавить в цепочку матриц)
  // Возвращает номер файла в цепочке матриц
  // При ошибке возвращает ноль

  int OpenMtr(const char * name, int mode);

  // Отображение матриц цепочки
  // order - признак отображения (0 - под картой, 1 - над картой)

  void ShowMtrPlace(CHAININFO *info, int order = 0,
                    DIBCONTEXT* dc = 0);                

  // Рисование открытых матриц (занесенных в цепочку)
  // number - номер в цепочке (number = 0  -  отобразить все)

  void ShowMtr(CHAININFO *info, int number = 0);

  // Запросить/Установить порядок отображения
  //  (0 - под картой, 1 - над картой)
  // При ошибке возвращает -1
  int MtrViewOrder(int number, int order = -1);

  // Установить/Запросить видимость матрицы высот
  // 0 - матрица не отображаемая

  int CheckMtrView(int number);
  int SetMtrView(int number,int view);

  // Запросить/Установить тип маски отображения матрицы высот (0-8)
  // При ошибке возвращает -1
  int GetMtrMaskType(int number);                       
  int SetMtrMaskType(int number,int masktype);

  // Установить рамку матрицы
  //  При ошибке возвращает 0
  int SetMtrBorderPlane(int number, TDataEdit* data);

  // Запросить рамку матрицы                    
  // При отсутствии рамки возвращает 0
  TDataEdit* GetMtrBorderPlane(int number);

  // Установка отображения матрицы по рамке    
  // value = 1 - отобразить растр по рамке
  //       = 0 - отобразить растр без учета рамки
  int ShowMtrByBorder(int number, int value);

  // Определение способа отображения матрицы(относительно рамки)    
  // Возвращает 1 - при отображении матрицы по рамке
  //            0 - при отображении матрицы без учета рамки
  // При ошибке возвращает -1
  int CheckShowMtrByBorder(int number);

  // Поменять очередность отображения матриц            
  // oldNumber - номер файла в цепочке
  // newNumber - устанавливаемый номер файла в цепочке
  //  При ошибке возвращает 0
  int ChangeOrderMtrShow(int oldNumber, int newNumber);

// protected :

  // Инициализировать звено цепочки матричных данных
  void InitMtrChainUnit(RMFCHAIN* mtrchain);

  // Отобразить растр
  int ShowChainMtr(RMFCHAIN* mtrchain, DIBCONTEXT* dc);      

  // Рисование блока матрицы

  void ShowBlockMtrDib(RMFCHAIN* mtrchain, DIBCONTEXT* dc);  
  void ShowBlockMtrDevice(RMFCHAIN* mtrchain);

public : // блок TIN
// Открыть tin модель (добавить в цепочку матриц)
// Возвращает номер файла в цепочке
// При ошибке возвращает ноль
int OpenTin(const char * name, int mode);

// Закрыть tin модель
// number - номер файла модели в цепочке
// Если number == 0, закрываются все модели
// При ошибке возвращает 0
int CloseTin(const int number = 0);

// Запросить число занесенных в цепочку моделей
int GetTinCount();

// Запросить имя файла тин модели с номером number
const char* GetTinName(const int number);

// Получить треугольник с номером index
// number - номер TIN-файла в цепочке
// index - индекс в массиве треугольников
// При ошибке возвращает 0 
long int GetTriangle(const int number, 
                               TINTRIANGLE* const triangle, const int index);
  
// Отображение tin моделей цепочки
// order - признак отображения (0 - под картой, 1 - над картой)
int ShowTinPlace(int order = 0, DIBCONTEXT* _dc = 0);

// Запросить/Установить порядок отображения
//  (0 - под картой, 1 - над картой)
// При ошибке возвращает -1
int TinViewOrder(int number, int order = -1);
	 
// Установить/Запросить видимость матрицы высот
// 0 - тин модель не отображаемая
int CheckTinView(int number);
int SetTinView(int number,int view);

// Выбор значения высоты поверхности в заданной точке
// из TIN-модели с номером number в цепочке.
// number - номер TIN-модели в цепочке.
// Координаты точки задаются в метрах в системе координат
// векторной карты. Возвращает значение высоты в метрах.
// В случае ошибки при выборе высоты и в случае необеспеченности
// заданной точки данными возвращает ERRORHEIGHT.
double GetTinSurfaceHeight(int number, double x, double y);

// Выбор значения высоты поверхности в заданной точке.
// Координаты точки задаются в метрах в системе координат
// векторной карты. Возвращает значение высоты в метрах.
// Высота поверхности запрашивается из более точной TIN-модели.
// В случае ошибки при выборе высоты и в случае необеспеченности
// заданной точки данными TIN-модели возвращает ERRORHEIGHT.
double GetSurfaceHeight(double x, double y);
double GetSurfaceHeight(DOUBLEPOINT* point)
   { return GetSurfaceHeight(point->x, point->y); } 

TINCHAIN   *TinChainBegin;    // Первое звено цепочки
int         TinCurrentNumber; // Текущая тин модель

public : // блок МАТРИЦ

 CHAININFO  MtqChain;          // Сведения о цепочке матриц качеств
 CHAININFO  MtrChain;          // Сведения о матричной цепочке

 // Описание матричных карт
 // -------------------------------
 TMtrPalette  MtrPalette;      // Палитра матрицы
                               
 int    MatrixShadow;          // Глубина тени матрицы высот
 int    MtrShadow;             // Глубина тени матрицы высот
 int    MtrShadowIntensity;    // Интенсивность тени матрицы высот 
 double MatrixUnitShadow;      // Отношение масштаба в плане к масштабу по высоте (вычисляется)
 int    ColorsNumber;          // Число цветов палитры текущей матрицы

 FRAME FrameMtr;

 double MtrChainMinHeight;     // Минимальная высота цепочки
 double MtrChainMaxHeight;     // Максимальная высота цепочки

                               
 int    MtrChainUserDiapason;  // Флаг установки пользовательского
                               // диапазона высот цепочки
                               // (MtrChainMinHeight, MtrChainMaxHeight)
                               // (1 - установлен пользовательский диапазон,
                               //  0 - диапазон установлен в SetRegion)

 // Рабочие переменные отображения растра и матрицы
 // -----------------------------------------------
 int BorderFilter;      // Фильтр по рамке
 int MaskType;          // Тип маски
 int MaskStep;          // Шаг маски
 char Mask[8];          // Пиксельная маска

 int ESize;             // Размер элемента
 DFRAME DFrameElem;     // Область растра в элементах
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
 int StringBlockAddr;   // Номер строки прочитанного блока BlockAddr   
 int ColumnBlockAddr;   // Номер столбца прочитанного блока BlockAddr  
 char* ColumnAddr1;     // Указатели на столбцы в соседних блоках  
 char* ColumnAddr2;     // (для алгоритма наложения теней)
 double StringInBlockBegin;
 double ColumnInBlockBegin;
 double StringInBlockFloat;
 double ColumnInBlockFloat;

 unsigned char ColorFilter[256];  // Фильтр по цвету (для растра)

 // Таблицы преобразования цвета для визуализации теней (mtrshow.cpp)
 // Рабочие диапазоны таблиц преобразования цвета
 // для визуализации теней (Arctan и Sinus)
#define RANGE_ARCTAN  600    // -66 ... 66 градусов
#define RANGE_SINUS   256    // -57 ... 57 градусов     
#define SCALE_FACTOR  128.0  // Цена деления таблиц Arctan и Sinus

 long   Arctan[RANGE_ARCTAN];
 long   Sinus [RANGE_SINUS];
 unsigned char ShadowColor[RANGE_SINUS][256];           


  // ************************************************************
  //                                                            *
  //                 ДОСТУП К МАТРИЦЕ СЛОЕВ                     *
  //                                                            *
  // ************************************************************

#ifndef HIDEMTL

public :

  // Открыть заданную матрицу, если она не открыта.
  // Текущей становится матрица "number".
  // Возвращает указатель на объект, связанный
  // с открываемой матрицей. При ошибке возвращает ноль.
  MTLCHAIN* ActiveMtl(int number) { return IsOpenMtl(number); }
  MTLCHAIN* IsOpenMtl(int number) { return GetMtlChain (number); }

  // Закрыть матричные данные (удалить из цепочки)
  // number - номер матричного файла в цепочке
  // Если number == 0, закрываются все матричные данные
  void CloseMtl(int number = 0);

  // Запросить число занесенных в цепочку матриц
  int GetMtlCount() { return MtlCount(); }
  int MtlCount()    { return MtlChainCount; }
  int IsMtlActive() { return (MtlCount() > 0); }

  // Установить число (number) занесенных в цепочку матриц
  int SetMtlCount(int number) { return MtlChainCount = number; }

  // Запрос/Установка адреса первого звена цепочки матриц
  MTLCHAIN* GetMtlChainBegin() { return MtlChainBegin; }
  MTLCHAIN* SetMtlChainBegin(MTLCHAIN* mtlchainbegin)
                               { return MtlChainBegin = mtlchainbegin; }

  // Запрос/Установка текущего номера открытой матрицы
  int GetMtlCurrentNumber() { return MtlCurrentNumber; }
  int SetMtlCurrentNumber(int number)
                            { return MtlCurrentNumber = number; }

  // Запросить элемент цепочки по номеру
  // При ошибке возвращается ноль
  MTLCHAIN* GetMtlChain(int number);

  // Запросить номер в цепочке для матрицы, расположенной
  // в заданной точке
  // number - порядковый номер, найденной матрицы в точке
  // (1 - первая в данной точке, 2 - вторая ...)
  // При ошибке возвращается ноль
  int GetMtlNumberInPoint(double x,double y,int number);

  // Запросить номер в цепочке последней открытой матрицы
  // с установленным (равным 1) признаком видимости.
  // При ошибке возвращается ноль
  int GetMtlNumberLastVisible();

  // Запросить описание файла матричных данных
  // number - номер файла в цепочке
  // describe - адрес структуры, в которой будет размещено
  // описание матрицы
  // При ошибке возвращает ноль
  int GetMtlDescribe(int number, MTLDESCRIBE* describe);

  // Запросить данные о проекции матричных данных
  // number - номер файла в цепочке
  // projectiondata - адрес структуры, в которой будут размещены
  // данные о проекции
  // При ошибке возвращает ноль
  int GetMtlProjectionData(int number, MTRPROJECTIONDATA * projectiondata);

  // Запросить данные о проекции матричных данных    
  // number - номер файла в цепочке
  // mapregister - адрес структуры, в которой будут размещены
  // данные о проекции
  // При ошибке возвращает ноль
  int GetMtlProjectionDataEx(int number, MAPREGISTEREX* mapregister);

  // Установить данные о проекции матричных данных   
  // number - номер файла в цепочке
  // mapregister - адрес структуры
  // При ошибке возвращает ноль
  int SetMtlProjectionDataEx(int number, MAPREGISTEREX* mapregister);

  // Запросить имя файла матричных данных
  // number - номер файла в цепочке
  // При ошибке возвращает ноль
  const char* GetMtlName(int number);

  // Запросить минимальное значение высоты нижнего уровня
  // цепочки матриц (в метрах)
  double GetMinBotLevelHeight() {return MtlChainMinBotLevelHeight;}

  // Запросить значение максимальной суммарной мощности слоев
  // цепочки матриц (в метрах)
  double GetMaxSummaryPower() {return MtlChainMaxSummaryPower;}

  // Запросить суммарную мощность слоев матрицы
  // с номером number в цепочке.
  // В случае ошибки возвращает ERRORPOWER.
  double GetMaxSummaryPowerOfMtl(long int number);

  // Запросить значение максимального количества слоев цепочки матриц
  int GetMaxLayerCount() {return MtlChainMaxLayerCount;}

  // Запросить количество слоев матрицы с номером number в цепочке.
  // При ошибке возвращает ноль
  int GetLayerCountOfMtl(long int number);

  // Выбор значения абсолютной высоты в заданной точке.
  // Координаты точки (x,y) задаются в метрах в системе координат
  // векторной карты. Возвращает значение высоты в метрах.
  // В случае ошибки при выборе высоты и в случае необеспеченности
  // заданной точки матричными данными возвращает ERRORHEIGHT.
  double GetElementHeight(double x, double y);
  double GetElementHeight(DOUBLEPOINT* point)
    { return GetElementHeight(point->x,point->y); }

  // Выбор значения абсолютной высоты в заданной точке из матрицы
  // с номером number в цепочке.
  // number - номер матрицы в цепочке.
  // Координаты точки задаются в метрах в системе координат
  // векторной карты. Возвращает значение высоты в метрах.
  // В случае ошибки при выборе высоты и в случае необеспеченности
  // заданной точки матричными данными возвращает ERRORHEIGHT.
  double GetElementHeight(int number,double x, double y);

  // Занесение значения абсолютной высоты в элемент матрицы,
  // соответствующий заданной точке.
  // number - номер матрицы в цепочке.
  // Координаты точки (x,y) и значение высоты (h) задаются в метрах
  // в системе координат векторной карты.
  // В случае ошибки возвращает ноль.
  int PutElementHeight(long int number, double x, double y, double h);
  int PutElementHeight(long int number, DOUBLEPOINT* point, double h)
    { return PutElementHeight(number,point->x,point->y,h); }

  // Выбор значения абсолютной высоты в заданной точке по самой точной
  // матрице.
  // Координаты точки задаются в метрах в системе координат
  // векторной карты. Возвращает значение высоты в метрах.
  // В случае ошибки при выборе высоты и в случае необеспеченности
  // заданной точки матричными данными возвращает ERRORHEIGHT.
  double GetPrecisionElementHeight(double x, double y);
  double GetPrecisionElementHeight(DOUBLEPOINT* point)
    { return GetPrecisionElementHeight(point->x,point->y); }


  // Выбор значения мощности слоя layernumber в заданной точке.
  // Координаты точки задаются в метрах в системе координат
  // векторной карты. Возвращает значение мощности в метрах.
  // В случае ошибки при выборе мощности и в случае необеспеченности
  // заданной точки матричными данными возвращает ERRORPOWER.
  double GetElementPower(double x,double y,long int layernumber);
  double GetElementPower(DOUBLEPOINT* point,long int layernumber)
    { return GetElementPower(point->x,point->y,layernumber); }

  // Выбор значения мощности слоя layernumber в заданной точке
  // из матрицы с номером number в цепочке.
  // number - номер матрицы в цепочке.
  // Координаты точки задаются в метрах в системе координат
  // векторной карты. Возвращает значение мощности в метрах.
  // В случае ошибки при выборе мощности и в случае необеспеченности
  // заданной точки матричными данными возвращает ERRORPOWER.
  double GetElementPower(int number,double x,double y,long int layernumber);

  // Вычисление значений мощностей слоев в заданной точке
  // методом треугольников по матрице с номером number в цепочке.
  // Координаты точки задаются в метрах в системе координат
  // векторной карты.
  // powers - адрес массива для записи вычисленных значений мощностей
  // count - размер массива, должен быть не менее TMtl::LayerCount().
  // Возвращает количество заполненных элементов массива powers.
  // При ошибке возвращает ноль.
  int GetElementPowersTriangle(int number,double x,double y,
                               double* powers,int count);

  // Вычисление значения мощности слоя layernumber в заданной точке
  // методом треугольников по матрице с номером number в цепочке.
  // Координаты точки задаются в метрах в системе координат
  // векторной карты.
  // Возвращает значение мощности слоя в метрах.
  // При ошибке возвращает ERRORPOWER.
  double GetElementPowerTriangle(int number,double x,double y,
                                 int layernumber);

  // Занесение значения мощности слоя layernumber в элемент матрицы,
  // соответствующий заданной точке.
  // number - номер матрицы в цепочке.
  // Координаты точки (x,y) и значение мощности (p) задаются в метрах
  // в системе координат векторной карты.
  // В случае ошибки возвращает ноль.
  int PutElementPower(long int number, double x, double y, double p,
                      long int layernumber);
  int PutElementPower(long int number, DOUBLEPOINT* point, double p,
                      long int layernumber)
    { return PutElementPower(number,point->x,point->y,p,layernumber); }

  // Выбор значения мощности слоя layernumber в заданной точке
  // по самой точной матрице.
  // Координаты точки задаются в метрах в системе координат
  // векторной карты. Возвращает значение мощности в метрах.
  // В случае ошибки при выборе мощности и в случае необеспеченности
  // заданной точки матричными данными возвращает ERRORPOWER.
  double GetPrecisionElementPower(double x,double y,long int layernumber);
  double GetPrecisionElementPower(DOUBLEPOINT* point,long int layernumber)
    { return GetPrecisionElementPower(point->x,point->y,layernumber); }


  // Выбор массива значений абсолютных высот, соответствующих
  // логическим элементам, лежащим на заданном отрезке.
  // Координаты точек, задающих начало и конец отрезка
  // (FirstPoint,SecondPoint) задаются в метрах в системе
  // координат векторной карты.
  // Размер массива высот, заданного адресом HeightArray,
  // должен соответствовать запрашиваемому количеству высот
  // (HeightCount), в противном случае возможны ошибки работы
  // с памятью.
  // В случае необеспеченности логического элемента матричными
  // данными его значение равно ERRORHEIGHT.
  // В случае ошибки при выборе высот возвращает ноль.
  int GetHeightArrayFromMtl (double*       HeightArray,
                             int           HeightCount,
                             DOUBLEPOINT*  FirstPoint,
                             DOUBLEPOINT*  SecondPoint);

  // Открыть матричные данные (добавить в цепочку матриц)
  // Возвращает номер файла в цепочке матриц
  // При ошибке возвращает ноль
  int OpenMtl(const char * name, int mode);

  // Отображение матриц цепочки
  // order - признак отображения (0 - под картой, 1 - над картой)
  int ShowMtlPlace(int order = 0, DIBCONTEXT* dc = 0);  

  // Рисование открытых матриц (занесенных в цепочку)
  // number - номер в цепочке (number = 0  -  отобразить все)
  void ShowMtl(int number = 0);

  // Запросить/Установить порядок отображения
  //  (0 - под картой, 1 - над картой)
  // При ошибке возвращает -1
  int MtlViewOrder(int number, int order = -1);

  // Установить/Запросить видимость матрицы
  // 0 - матрица не отображаемая
  int CheckMtlView(int number);
  int SetMtlView(int number,int view);

  // Запросить/Установить тип маски отображения матрицы (0-8)
  // При ошибке возвращает -1
  int GetMtlMaskType(int number);                       
  int SetMtlMaskType(int number,int masktype);

  // Установить рамку матрицы
  //  При ошибке возвращает 0
  int SetMtlBorderPlane(int number, TDataEdit* data);

  // Запросить рамку матрицы
  // При отсутствии рамки возвращает 0
  TDataEdit* GetMtlBorderPlane(int number);

  // Установка отображения матрицы по рамке
  // value = 1 - отобразить растр по рамке
  //       = 0 - отобразить растр без учета рамки
  int ShowMtlByBorder(int number, int value);

  // Определение способа отображения матрицы(относительно рамки)
  // Возвращает 1 - при отображении матрицы по рамке
  //            0 - при отображении матрицы без учета рамки
  // При ошибке возвращает -1
  int CheckShowMtlByBorder(int number);

  // Поменять очередность отображения матриц       
  // oldNumber - номер файла в цепочке
  // newNumber - устанавливаемый номер файла в цепочке
  //  При ошибке возвращает 0
  int ChangeOrderMtlShow(int oldNumber, int newNumber);


// protected :

  // Инициализировать матричные данные
  void InitMtlChain();

  // Инициализировать звено цепочки матричных данных
  void InitMtlChainUnit(MTLCHAIN* mtlchain);

  // Отобразить матрицу слоев
  int ShowChainMtl(MTLCHAIN* mtlchain, DIBCONTEXT* dc);      

  // Рисование блока матрицы
  void ShowBlockMtlDib(MTLCHAIN* mtlchain, DIBCONTEXT* dc);  
  void ShowBlockMtlDevice(MTLCHAIN* mtlchain);

public :

  FRAME FrameMtl;

  double MtlChainMaxSummaryPower; // Максимальная суммарная мощность слоев
                                  // всей MTL-цепочки (в метрах)
  double MtlChainMinBotLevelHeight; // Минимальная высота нижнего уровня
                                    // всей MTL-цепочки (в метрах)
  int    MtlChainMaxLayerCount;  // Максимальное количество слоев
                                 // всей MTL-цепочки

  int       MtlChainCount;       // Количество звеньев
  MTLCHAIN* MtlChainBegin;       // Первое звено цепочки
  int       MtlCurrentNumber;    // Номер активной матрицы в цепочке

#endif  // HIDEMTL


#ifndef HIDETIN
  // ************************************************************
  //                                                            *
  //                 ДОСТУП К TIN-МОДЕЛИ                        *
  //                                                            *
  // ************************************************************

public :

  // Открыть заданную модель, если она не открыта.
  // Текущей становится модель "number".
  // Возвращает указатель на объект, связанный
  // с открываемой моделью. При ошибке возвращает ноль.
  TINCHAIN* ActiveTin(int number) { return IsOpenTin(number); }
  TINCHAIN* IsOpenTin(int number) { return GetTinChain(number); }

  // Закрыть модель (удалить из цепочки)
  // number - номер файла в цепочке
  // Если number == 0, закрываются все модели
  void CloseTin(int number = 0);

  // Запросить число занесенных в цепочку моделей
  int GetTinCount() { return TinCount(); }
  int TinCount()    { return TinChainCount; }
  int IsTinActive() { return (TinCount() > 0); }

  // Установить число (number) занесенных в цепочку моделей
  int SetTinCount(int number) { return TinChainCount = number; }

  // Запрос/Установка адреса первого звена цепочки моделей
  TINCHAIN* GetTinChainBegin() { return TinChainBegin; }
  TINCHAIN* SetTinChainBegin(TINCHAIN* tinchainbegin)
                               { return TinChainBegin = tinchainbegin; }

  // Запрос/Установка текущего номера открытой модели
  int GetTinCurrentNumber() { return TinCurrentNumber; }
  int SetTinCurrentNumber(int number)
                            { return TinCurrentNumber = number; }

  // Запросить элемент цепочки по номеру
  // При ошибке возвращается ноль
  TINCHAIN* GetTinChain(int number);

  // Запросить номер в цепочке для модели, расположенной
  // в заданной точке
  // number - порядковый номер, найденной модели в точке
  // (1 - первая в данной точке, 2 - вторая ...)
  // При ошибке возвращается ноль
  int GetTinNumberInPoint(double x,double y,int number);

  // Запросить номер в цепочке последней открытой модели
  // с установленным (равным 1) признаком видимости.
  // При ошибке возвращается ноль
  int GetTinNumberLastVisible();

  // Запросить описание файла модели
  // number - номер файла в цепочке
  // describe - адрес структуры, в которой будет размещено
  // описание модели
  // При ошибке возвращает ноль
  int GetTinDescribe(int number, TINDESCRIBE* describe);

  // Запросить имя файла модели
  // number - номер файла в цепочке
  // При ошибке возвращает ноль
  const char* GetTinName(int number);

  // Запросить описание файла модели
  // number - номер файла в цепочке
  // describe - адрес структуры, в которой будет размещено
  // описание модели
  // При ошибке возвращает ноль
  long int _MAPAPI mapGetTinDescribe(HMAP hMap, long int number,
                                     TINDESCRIBE * describe);

  // Выбор значения высоты поверхности в заданной точке.
  // Координаты точки задаются в метрах в системе координат
  // векторной карты. Возвращает значение высоты в метрах.
  // Высота поверхности запрашивается из более точной TIN-модели.
  // В случае ошибки при выборе высоты и в случае необеспеченности
  // заданной точки данными TIN-модели возвращает ERRORHEIGHT.
  double GetSurfaceHeight(double x, double y);
  double GetSurfaceHeight(DOUBLEPOINT* point)
    { return GetSurfaceHeight(point->x, point->y); }

  // Выбор значения высоты поверхности в заданной точке
  // из TIN-модели с номером number в цепочке.
  // number - номер TIN-модели в цепочке.
  // Координаты точки задаются в метрах в системе координат
  // векторной карты. Возвращает значение высоты в метрах.
  // В случае ошибки при выборе высоты и в случае необеспеченности
  // заданной точки данными возвращает ERRORHEIGHT.
  double GetTinSurfaceHeight(int number, double x, double y);

  // Открыть модель (добавить в цепочку матриц)
  // Возвращает номер файла в цепочке матриц
  // При ошибке возвращает ноль
  int OpenTin(const char * name, int mode);

  // Отображение моделей цепочки
  // order - признак отображения (0 - под картой, 1 - над картой)
  int ShowTinPlace(int order = 0, DIBCONTEXT* dc = 0);

  // Рисование открытых моделей (занесенных в цепочку)
  // number - номер в цепочке (number = 0  -  отобразить все)
  void ShowTin(int number = 0, DIBCONTEXT* dc = 0);

  // Запросить/Установить порядок отображения
  //  (0 - под картой, 1 - над картой)
  // При ошибке возвращает -1
  int TinViewOrder(int number, int order = -1);

  // Установить/Запросить видимость матрицы
  // 0 - модель не отображаемая
  int CheckTinView(int number);
  int SetTinView(int number, int view);

  // Запросить/Установить тип маски отображения матрицы (0-8)
  // При ошибке возвращает -1
  int GetTinMaskType(int number);
  int SetTinMaskType(int number, int masktype);

  // Установить рамку модели
  //  При ошибке возвращает 0
  int SetTinBorderPlane(int number, TDataEdit* data);

  // Запросить рамку модели
  // При отсутствии рамки возвращает 0
  TDataEdit* GetTinBorderPlane(int number);

  // Установка отображения модели по рамке
  // value = 1 - отобразить по рамке
  //       = 0 - отобразить без учета рамки
  int ShowTinByBorder(int number, int value);

  // Определение способа отображения модели(относительно рамки)
  // Возвращает 1 - при отображении модели по рамке
  //            0 - при отображении модели без учета рамки
  // При ошибке возвращает -1
  int CheckShowTinByBorder(int number);

  // Поменять очередность отображения моделей
  // oldNumber - номер файла в цепочке
  // newNumber - устанавливаемый номер файла в цепочке
  //  При ошибке возвращает 0
  int ChangeOrderTinShow(int oldNumber, int newNumber);

  // Инициализировать данные TIN-моделей
  void InitTinChain();

  // Инициализировать звено цепочки TIN-моделей
  void InitTinChainUnit(TINCHAIN* tinchain);

  // Отобразить TIN-модель
  int ShowChainTinFill(TINCHAIN* tinchain, DIBCONTEXT* dc);
  int ShowChainTinSkelet(TINCHAIN* tinchain, DIBCONTEXT* dc);

  // Определение попадания модели в видимую клиентную область
  int CheckViewTin();

  // Запрос вершины vertex из массив вершин TIN-модели
  // с номером number в цепочке
  // index - индекс в массиве вершин
  // При ошибке возвращает 0
  int GetTinVertex(long int number, TINVERTEX* vertex, long int index);

  // Запись вершины vertex в массив вершин TIN-модели
  // с номером number в цепочке
  // index - индекс в массиве вершин
  // При ошибке возвращает 0
  int PutTinVertex(long int number, const TINVERTEX* vertex, long int index);

  // Возврат/Установка флагов вершины TIN-модели
  // number - номер TIN-файла в цепочке
  // index - индекс в массиве вершин
  // flag - адрес структуры, содержащей значения флагов вершины
  // Структурa TINVERTEXFLAG описанa в MAPTYPE.H
  // При ошибке возвращает 0
  int GetTinVertexFlags(long int number, int index, TINVERTEXFLAG* flag);
  int SetTinVertexFlags(long int number, int index, const TINVERTEXFLAG* flag);

  // Возврат/Установка флагов треугольника TIN-модели
  // number - номер TIN-файла в цепочке
  // index - индекс в массиве треугольников
  // flag - адрес структуры, содержащей значения флагов треугольника
  // Структурa TINTRIANGLEFLAG описанa в MAPTYPE.H
  // При ошибке возвращает 0
  int GetTinTriangleFlags(long int number, int index, TINTRIANGLEFLAG* flag);
  int SetTinTriangleFlags(long int number, int index, const TINTRIANGLEFLAG* flag);

  // Запрос треугольника triangle из массива треугольников TIN-модели
  // с номером number в цепочке
  // index - индекс в массиве треугольников
  // При ошибке возвращает 0
  int GetTinTriangle(long int number, TINTRIANGLE* triangle, long int index);

  // Запись треугольника triangle в массив треугольников TIN-модели
  // с номером number в цепочке
  // index - индекс в массиве треугольников
  // При ошибке возвращает 0
  int PutTinTriangle(long int number, const TINTRIANGLE* triangle, long int index);

#endif  // HIDETIN



// ===========================================================
//           МАТРИЦЫ КАЧЕСТВ
// ===========================================================

  // Запросить число занесенных в цепочку матриц   
  int GetMtqCount() { return MtqCount(); }      
  int MtqCount()    { return MtqChain.Count; }

  // Закрыть данные матриц качеств
  void CloseMtq(int number);

  // Установить/Запросить тень матрицы качества
  // value - флаг наложения тени (1 - тень есть, 0 - тени нет)

  int SetMtqShadow(int number, int value);              
  int GetMtqShadow(int number);

  // Установить/Запросить видимость матрицы качества  
  // 0 - матрица качества не отображаемая
  int CheckMtqView(int number);
  int SetMtqView(int number,int view);

  // Определение способа отображения матрицы качеств(относительно рамки)
  // Возвращает 1 - при отображении матрицы по рамке
  //            0 - при отображении матрицы без учета рамки
  // При ошибке возвращает -1
  int CheckShowMtqByBorder(int number);

  // Установка отображения матрицы качеств по рамке
  // value = 1 - отобразить матрицы по рамке
  //       = 0 - отобразить матрицы без учета рамки
  //  При ошибке возвращает 0
  int ShowMtqByBorder(int number, int value);

  // Поменять очередность отображения матриц качеств
  // oldNumber - номер файла в цепочке
  // newNumber - устанавливаемый номер файла в цепочке
  //  При ошибке возвращает 0
  int ChangeOrderMtqShow(int oldNumber, int newNumber);

  // Установить рамку матрицы                          
  int SetMtqBorderPlane(int number, TDataEdit* data);

  //  Запросить рамку матрицы
  TDataEdit* GetMtqBorderPlane(int number);

public:

  // Запросить адрес таблицы функций визуализации в DIB
  VISUALTABLE* GetDibTable() { return DibFunc;}

  // Функция обратного вызова  
  void SetBreakCallAndParm(BREAKCALL call, long int parm)
  {
    BreakCall = call;
    BreakParm = parm;
  }

  // Установить отображение узлов
  // 0 - не отображать
  void SetNodeView(int mode) { IsNodeView = mode; }
  int GetNodeView() { return IsNodeView; }

  // Ининциализировать вид узла
  void InitNodeImage();

  // Установить цвета оформления узла
  void SetNodeFirstColor(COLORREF color = 0x02020F0);
  void SetNodeCenterColor(COLORREF color = 0x0FFFFFF);
  void SetNodeBorderColor(COLORREF color = 0);

  // Запросить цвета оформления узла
  COLORREF GetNodeFirstColor();
  COLORREF GetNodeCenterColor();
  COLORREF GetNodeBorderColor();

  // Установить тип узла
  void SetNodeType(int type = 2);
  int  GetNodeType();

  // Отобразить узлы объекта в DIB
  void ViewNode(POLYDATAEX * data);

 public :

  long int NodeFirstIndex;     // Индекс цвета первого узла для DIB
  long int NodeCenterIndex;    // Индекс цвета узла для DIB
  long int NodeBorderIndex;    // Индекс цвета границы узла для DIB

  COLORREF NodeFirstColor;     // Цвет первого узла для DIB
  COLORREF NodeCenterColor;    // Цвет узла для DIB
  COLORREF NodeBorderColor;    // Цвет границы узла для DIB

  int NodeSize;                // Тип узла (1,2,3)
  int IsNodeView;              // Признак отображения узлов

  CHANGECALL  ChangeCall;      // Адрес функции для оповещении о редактировании
  long int ChangeParm;         // Параметр функции оповещения

  BREAKCALL BreakCall;         // Функция обратного вызова
  long int  BreakParm;         // для прерывания отображения

  BEFOREPAINT BeforePaint;     // Функция обратного вызова      
  long int    BeforeParm;      // для рисования под картой

  int  SkeepTextFlag;          // Признак выбора подписи в точке ПОСЛЕДНЕЙ
  int  IsRestoreData;          // Признак восстановления списка открытых данных из INI-файла

  int  NotAdjust;              // Признак блокирования обновления карты из-за какого-либо
                               // процесса

  int TotalSeekFlag;           // Флаг глобального поиска
  int TotalSelectFlag;         // Флаг выделения объектов на карте
};


  // ************************************************************
  //                                                            *
  //            УПРАВЛЕНИЕ ОТОБРАЖЕНИЕМ И ПОИСКОМ               *
  //                                                            *
  // ************************************************************

// Установка вида отображения или печати объектов
int _fastcall cntSetVisualType(TMapControl * data, int type);

// Установить масштаб отображения карты
void _fastcall cntSetViewScale(TMapControl * data, double * scale);

// Установить масштаб отображения
int _fastcall cntSetViewScalePlace(TMapControl *mapcnt,
                                   long int *x, long int *y,float scale);

// Изменить масштаб отображения относительно текущего
int _fastcall cntChangeViewScale(TMapControl *mapcnt,
                                 long int *x, long int *y,float change);

// Запросить текущий масштаб отображения
double _fastcall cntGetRealShowScale(TMapControl * data);

// Установить текущий масштаб отображения           
double _fastcall cntSetRealShowScale(TMapControl * data, double scale);

// Пересчитать габариты района работ
void _fastcall cntSetRegion(TMapControl * data);

// Отобразить открытые данные
int _fastcall cntShowData(TMapControl * data);

// Функция проверки видимости объекта
int _fastcall cntCheckViewObject(TMapControl * data,
                                 TObjectHead * head, TMap * map);

// Проверить "видимость" объекта
int _fastcall cntTestObject(TMapControl * cont, TObjectHead * head,
                            TMap * map);

// Запрос объекта по заданным координатам в районе (дискреты);
// Поиск выполняется среди тех объектов,которые видны на экране
MAPOBJDESC * _fastcall cntWhatObjectInMap(TMapControl * cont,
                                          MAPOBJDESC * object,
                                          DFRAME * frame, int flag, int nMap,
                                          TMapSelect * select);

// Запрос объекта по заданным координатам в районе (дискреты);
// Поиск выполняется среди тех объектов,которые видны на экране
MAPOBJDESC * _fastcall cntWhatObjectInMapForText(TMapControl * cont,
                                                 MAPOBJDESC * object,
                                                 DFRAME * frame, int flag, int nMap,
                                                 TMapSelect * select);

// Функция выделения запрошенных объектов района
void _fastcall cntShowSelectData(TMapControl * cont, int mapnumber,
                                 COLORREF color, TMapSelect * select);

// Функция визуализации листа по его номеру, лист становится
// текущим. Нумерация листов начинается с единицы
int _fastcall cntShowList(TMapControl * cont, int number);

// Функция рисования объекта текущего листа
int _fastcall cntShowObject(TMapControl * cont, TMap * map,
                            TObjectHead * head, float viewscale);

// Функция рисования выбранного объекта
int _fastcall cntShowInfo(TMapControl * cont, TObjectInfo * object);

//  Функция рисования выбранного объекта               
int _fastcall cntShowSelectInfo(TMapControl * cont, TObjectInfo * object,
                                COLORREF color);

// Вызов функций отображения объекта карты
int _fastcall cntVisualObject(TMapControl * data, long incode, TMap* map,
                              POLYDATAEX* metric, float scaleview);

// Вызов функций отображения объекта
int _fastcall cntVisualObjectParm(TMapControl * data, VIEPAR* ViewParm,
                                  POLYDATAEX* metric, float scaleview, int scale);

// Визуализация объекта по заданному графическому описанию
int _fastcall cntVisualGraphic(TMapControl * data, TObjectHead* head,
                               TMap* map, POLYDATAEX* metric, float scaleview);

// Функция рисования объекта типа IMGOBJECT
int _fastcall cntVisualIMGOBJECT(TMapControl * data, POLYDATAEX* metric,
                                 PAINTPARM* image, TMap* map);

// Функция рисования графического объекта типа IMGOBJECT
int _fastcall cntGraphicIMGOBJECT(TMapControl * data, POLYDATAEX* metric,
                                  PAINTPARM* image, TMap* map,
                                  TObjectHead* head);

  // ************************************************************
  //                                                            *
  //            ДОСТУП К "ГЛАВНОЙ КАРТЕ"                        *
  //                                                            *
  // ************************************************************
  
// Закрыть цифровые данные
void _fastcall cntClose(TMapControl * data);

// Определить наличие открытых данных
int _fastcall cntIsActive(TMapControl * data);

// Открыть векторные данные
int _fastcall cntOpenMap(TMapControl * data, const char * name, int mode);

// Закрыть векторные данные
void _fastcall cntCloseMap(TMapControl * data);

// Функция визуализации района
int _fastcall cntShowMap(TMapControl * cont);

//  Выполнить согласование данных электронной карты
int _fastcall cntAdjustData(TMapControl * data);

// Открыть транзакцию перед выполнением операций редактирования карты
// number - номер редактируемой карты
// При ошибке возвращает ноль
int _fastcall cntOpenTransaction(TMapControl * data, int number, int type);

// Закрыть транзакцию после выполнения
// группы взаимосвязанных операций редактирования карты
// number - номер редактируемой карты
void _fastcall cntCloseTransaction(TMapControl * data, int number);


  // ************************************************************
  //                                                            *
  //        ДОСТУП К "ПОЛЬЗОВАТЕЛЬСКОЙ ЭЛЕКТРОННОЙ КАРТЕ"       *
  //                                                            *
  // ************************************************************

// Запросить элемент цепочки по номеру
// При ошибке возвращается ноль
SITCHAIN * _fastcall cntGetSiteChain(TMapControl * data, int number);

// Запросить карту по последовательному номеру
TMap * _fastcall cntGetMap(TMapControl * data, int number);

// Запрос маски наличия объектов на карте
TMapSelect * _fastcall cntGetRealSelect(TMapControl * data, int number);

// Согласовать маску наличия объектов на карте
void _fastcall cntAdjustRealSelect(TMapControl * data, int number,
                                   int force);

// Открыть карту (добавить в цепочку)
// При ошибке возвращает ноль
int _fastcall cntOpenSite(TMapControl * data, const char * name, int mode,
                          const char * rscname = 0);

// Закрыть карту по ее последовательному номеру в списке
// Если номер равен нулю - закрываются все карты
void _fastcall cntCloseSite(TMapControl * data, int number);

// Запросить/Установить признак редактируемости карты по номеру
int _fastcall cntMapEdit(TMapControl * data, int number, int flag);

// Запросить/Установить признак видимости карты по номеру
int _fastcall cntMapVisible(TMapControl * data, int number, int flag);

// Запросить/Установить порядок отображения  
//  (0 - под основной картой, 1 - над основной картой)
// При ошибке возвращает -1
int _fastcall cntMapViewOrder(TMapControl * data, int number, int order);

// Запросить/Установить признак разрешения выбора объекта карты
int _fastcall cntMapInquiry(TMapControl * data, int number, int flag);

// Запросить название файла карты по номеру
const char * _fastcall cntMapFileName(TMapControl * data, int number);

// Запросить условное название карты по номеру
const char * _fastcall cntMapSheetName(TMapControl * data, int number);

// Запрос описания ресурсов векторной карты по номеру
TMapRsc * _fastcall cntGetResource(TMapControl * data, int number);

// Запросить номер карты в цепочке
int _fastcall cntGetMapNumber(TMapControl * data, TMap * map);

// Запрос условий выбора объектов для визуализации по номеру
TMapSelect * _fastcall cntGetViewSelect(TMapControl * data, int number);

// Запрос условий выбора объектов для поиска по номеру
TMapSelect * cntGetSeekSelect(TMapControl * data, int number);

// Запрос маски наличия объектов на карте/
TMapSelect * _fastcall cntGetRealSelect(TMapControl * data, int number);

// Отобразить все данные обстановки
int _fastcall cntShowSituation(TMapControl * data);

// Отобразить все данные обстановки  
// order - признак отображения (0 - под картой, 1 - над картой)
int  _fastcall cntShowSituationPlace(TMapControl * data, int order);

// Отобразить данные обстановки
int _fastcall cntShowSite(TMapControl * cont,
                          TMap * map, TMapSelect * select, int number);  


  // ************************************************************
  //                                                            *
  //            ДОСТУП К "РАСТРОВОЙ ЭЛЕКТРОННОЙ КАРТЕ"          *
  //                                                            *
  // ************************************************************


// Отобразить блок растра в DIB
void _fastcall cntShowBlockRstDib(TMapControl *mapcnt, TRmf *Rstdib,
                                  DIBCONTEXT* dc,       
                                  TBaseColors *colors); 

// Отобразить блок растра-256 в DIB
void _fastcall cntShowBlockRstDib256(TMapControl *mapcnt, TRmf *Rstdib,
                                  DIBCONTEXT* dc,                    
                                  TBaseColors *colors);              

// Отобразить растр
int _fastcall cntShowChainRst(TMapControl *mapcnt, int number,
                                  DIBCONTEXT* dc);                    

// Рисование растров цепочки
// number - номер растра в цепочке (number = 0  -  отобразить все)
void _fastcall cntShowRst(TMapControl *mapcnt, int number);

// Отображение растров цепочки
// order - признак отображения (0 - под картой, 1 - над картой)
int _fastcall cntShowRstPlace(TMapControl *mapcnt, int order,
                                  DIBCONTEXT* dc);                    


// Открыть растровые данные
int _fastcall cntOpenRst(TMapControl *mapcnt, const char * name, int mode);

//  Инициализировать звено цепочки растровых данных
// Перед выполнением ф-ии выполнить - ActiveRst(RstNumber);
void _fastcall cntInitRstChainUnit(TMapControl *mapcnt,
                                   RSTCHAIN* rstchain, int mini);

// Закрыть растровые данные
void _fastcall cntCloseRst(TMapControl *mapcnt, int number);

// Запросить степень видимости растра
// Если растр не виден - возвращает ноль
// При ошибке возвращает -1
int _fastcall cntCheckRstView(TMapControl *mapcnt, int number);

// Установить степень видимости растра
//  view = 0   - не виден
//  view = 1   - полная
//  view = 2   - насыщенная
//  view = 3   - полупрозрачная
//  view = 4   - средняя
//  view = 5   - прозрачная
// При ошибке возвращает -1
int _fastcall cntSetRstView(TMapControl *mapcnt, int number, int view);

// Запросить/Установить тип маски отображения растра (0-8)
// При ошибке возвращает -1
int _fastcall cntGetRstMaskType(TMapControl *mapcnt, int number);   
int _fastcall cntSetRstMaskType(TMapControl *mapcnt, int number,int masktype);

// Запросить/Установить порядок отображения
//  (0 - под картой, 1 - над картой)
// При ошибке возвращает -1
int _fastcall cntRstViewOrder(TMapControl *mapcnt, int number, int order);

// Последовательный просмотр растров над картой
int _fastcall cntTurnRstViewOrder(TMapControl *mapcnt);  

// Запросить признак отображения цвета
// Возвращает:  1 - отображать; 0 - не отображать; -1 - ошибка
int _fastcall cntCheckRstPaletteView(TMapControl *mapcnt, int number, int index);

// Установить признак отображения цвета
// При ошибке возвращается  -1     =Shabakov D.A.=
int _fastcall cntSetRstPaletteView(TMapControl *mapcnt, int number,int index,int value);

// Запросить элемент цепочки по номеру
// При ошибке возвращается ноль
RSTCHAIN* _fastcall cntGetRstChain(TMapControl *mapcnt, int number);

// Запросить номер растра по полному имени файла
// При ошибке возвращается ноль
int _fastcall cntGetRstNumberByName(TMapControl *mapcnt, const char * name);

// Запросить видимость цвета (для 16- и 256-цветных растров)  
//  number - номер файла в цепочке
//  index  - индекс цвета в палитре растра(начиная с 0)
//  Возвращает: 1 - цвет с данным индексом отображается
//              0 - цвет с данным индексом не отображается
//  При ошибке возвращает -1
int _fastcall cntCheckVisibilityColor(TMapControl *mapcnt, int number,int index);

// Установить видимость цвета (для 16- и 256-цветных растров)  
//  number - номер файла в цепочке
//  index  - индекс цвета в палитре растра(начиная с 0)
//  value: 1 - включить отображение цвета с данным индексом
//         0 - отключить отображение цвета с данным индексом
//  Сохранение видимости цветов в INI-файле
//                                  (не заносится в заголовк файла растра)
//  При ошибке возвращает 0
int _fastcall cntSetVisibilityColor(TMapControl *mapcnt, int number,int index, int value);

// Установить видимость цвета (для 16- и 256-цветных растров)  
//  number - номер файла в цепочке
//  index  - индекс цвета в палитре растра(начиная с 0)
//  value: 1 - включить отображение цвета с данным индексом
//         0 - отключить отображение цвета с данным индексом
//  Сохранение видимости цветов в заголовке файла растра(а также в INI-файле)
//  При ошибке возвращает 0
int _fastcall cntSetVisibilityColorInRstFile(TMapControl *mapcnt, int number,int index, int value);

// Установить точность растра в цепочке и
// пересчитать общие габариты района работ
int _fastcall cntSetRstPrecision(TMapControl *mapcnt, int number, double precision);

// Запросить габариты растра в районе работ
// Возвращает указатель на габариты в элементах растра
//  number - номер файла в цепочке
// При ошибке возвращает ноль
DFRAME * _fastcall cntGetRstFrame(TMapControl *mapcnt, int number);

// Запросить габариты растра в районе работ
// Возвращает указатель на габариты растра в метрах
//  number - номер файла в цепочке
// При ошибке возвращает ноль
DFRAME * _fastcall cntGetRstFrameMeters(TMapControl *mapcnt, int number);

//  Запись в палитру выбранного цвета
//  number - номер файла в цепочке
//  При ошибке возвращает 0
int _fastcall cntSetRstColor(TMapControl *mapcnt,
                             int number,COLORREF color,int index);

//  Обновить активную палитру с нулевой яркостью и контрастностью
//  number - номер файла в цепочке
//  При ошибке возвращает 0
int _fastcall cntRestoreRstPalette(TMapControl *mapcnt, int number);

// Инвертировать растровую карту
// value:
// 0 - установить изображение растра позитивным
// 1 - установить изображение растра негативным
//  При ошибке возвращает 0
int _fastcall cntInvertRst(TMapControl *mapcnt, int number, int value);

// Установить рамку растра
int _fastcall cntSetRstBorderPlane(TMapControl *mapcnt,
                                   int number, TDataEdit* data);

// Установить маску растра в элементах растра  
int _fastcall cntSetRstMask(TMapControl *mapcnt,  int number, TDataEdit* data);

// Запросить маску растра       
//  При ошибке возвращает 0
TDataEdit* _fastcall cntGetRstMask(TMapControl *mapcnt, int number);

// Запросить рамку растра
// При ошибке возвращает 0
TDataEdit* _fastcall cntGetRstBorderPlane(TMapControl *mapcnt, int number);

// Установка отображения растра по рамке
// value = 1 - отобразить растр по рамке
//       = 0 - отобразить растр без учета рамки
//  При ошибке возвращает 0
int _fastcall cntShowRstByBorder(TMapControl *mapcnt, int number, int value);

// Поменять очередность отображения растровых данных
// oldNumber - номер файла в цепочке
// newNumber - устанавливаемый номер файла в цепочке
// При ошибке возвращает 0
int _fastcall cntChangeOrderRstShow(TMapControl *mapcnt,
                                    int oldNumber, int newNumber);

// Запросить имя файла растровых данных
// При ошибке возвращает ноль
const char * _fastcall cntGetRstName(TMapControl *mapcnt, int number);

// Запросить адрес активной палитры растра
// (с учетом яркости и контрасности)
// number - номер файла в цепочке
// При ошибке возвращает 0
COLORREF* _fastcall cntGetRstPalette(TMapControl *mapcnt, int number);

// Запросить яркость палитры (от -4 до 4)
// number - номер файла в цепочке
// При ошибке возвращает 0
int _fastcall cntGetRstBright(TMapControl *mapcnt, int number);


  // ************************************************************
  //                                                            *
  //            ДОСТУП К "МАТРИЧНОЙ ЭЛЕКТРОННОЙ КАРТЕ"          *
  //                                                            *
  // ************************************************************

// Инициализировать звено цепочки матричных данных
void _fastcall cntInitMtrChainUnit(TMapControl *mapcnt, RMFCHAIN* mtrchain);

// Открыть матричные данные
int _fastcall cntOpenMtr(TMapControl *mapcnt, const char * name, int mode);

// Закрыть матричные данные
void _fastcall cntCloseMtr(TMapControl *mapcnt, int number);

// Заполнить таблицы значений арктангенса и синуса
// для отображения матриц (MTR, MTL, MTQ) в тенях
void cntInitTables(TMapControl *mapcnt);               

// Установить/Запросить видимость матрицы высот
// 0 - матрица не отображаемая
int _fastcall cntCheckMtrView(TMapControl *mapcnt, int number);

// Установить степень видимости матрицы высот
//  view = 0   - не виден
//  view = 1   - полная
//  view = 2   - насыщенная
//  view = 3   - полупрозрачная
//  view = 4   - средняя
//  view = 5   - прозрачная
// При ошибке возвращает -1
int _fastcall cntSetMtrView(TMapControl *mapcnt, int number,int view);

// Запросить/Установить тип маски отображения матрицы высот (0-8)
// При ошибке возвращает -1
int _fastcall cntGetMtrMaskType(TMapControl *mapcnt, int number);   
int _fastcall cntSetMtrMaskType(TMapControl *mapcnt, int number,int masktype);

// Установить/Запросить глубину тени матрицы высот
// value - флаг наложения тени (от 0 до 16)
//   MTRSHADOW_NONE   =  0,   // Тень отсутствует
//   MTRSHADOW_PALE   =  1,   // Бледная
//   MTRSHADOW_WEAK   =  2,   // Слабая
//   MTRSHADOW_MIDDLE =  4,   // Средняя
//   MTRSHADOW_HEAVY  =  8,   // Сильная
//   MTRSHADOW_DEEP   = 16,   // Глубокая
int _fastcall cntGetMtrShadow(TMapControl *mapcnt);
int _fastcall cntSetMtrShadow(TMapControl *mapcnt, int value);

//-----------------------------------------------------------------
// Установить/Запросить интенсивность тени матрицы высот
// value - интенсивность тени (от 0 до 100)
//-----------------------------------------------------------------
int _fastcall cntGetMtrShadowIntensity(TMapControl *mapcnt);        
int _fastcall cntSetMtrShadowIntensity(TMapControl *mapcnt, int value);

// Установить/Запросить флаг установки пользовательского
// диапазона высот цепочки матриц высот
// (1 - установлен пользовательский диапазон,
//  0 - диапазон установлен в SetRegion)
int _fastcall cntGetMtrChainUserDiapason(TMapControl *mapcnt);      
int _fastcall cntSetMtrChainUserDiapason(TMapControl *mapcnt, int value);

// Запросить элемент цепочки по номеру
// При ошибке возвращается ноль
RMFCHAIN* _fastcall cntGetChain(TMapControl *mapcnt, int number);

// Запросить имя файла матричныx данных
// При ошибке возвращает ноль
const char * _fastcall cntGetMtrName(TMapControl *mapcnt, int number);

// Запросить/Установить порядок отображения
//  (0 - под картой, 1 - над картой)
// При ошибке возвращает -1
int _fastcall cntMtrViewOrder(TMapControl *mapcnt, int number, int order);

// Установить рамку матрицы
int _fastcall cntSetMtrBorderPlane(TMapControl *mapcnt,
                                   int number, TDataEdit* data);

//  Запросить рамку матрицы                  
TDataEdit* _fastcall cntGetMtrBorderPlane(TMapControl *mapcnt, int number);

// Установка отображения матрицы по рамке    
// value = 1 - отобразить матрицы по рамке
//       = 0 - отобразить матрицы без учета рамки
//  При ошибке возвращает 0
int _fastcall cntShowMtrByBorder(TMapControl *mapcnt, int number, int value);

// Определение способа отображения матрицы(относительно рамки)  
// Возвращает 1 - при отображении матрицы по рамке
//            0 - при отображении матрицы без учета рамки
// При ошибке возвращает -1
int _fastcall cntCheckShowMtrByBorder(TMapControl *mapcnt, int number);

// Отображение растров цепочки
// order - признак отображения (0 - под картой, 1 - над картой)
int _fastcall cntShowMtrPlace(TMapControl *mapcnt, CHAININFO *info, int order,
                                  DIBCONTEXT* dc);                


// Рисование матриц цепочки
// number - номер матрицы в цепочке (number = 0  -  отобразить все)
void _fastcall cntShowMtr(TMapControl *mapcnt, CHAININFO *info, int number);

// Отобразить растр
int _fastcall cntShowChainMtr(TMapControl *mapcnt, RMFCHAIN* chain,
                                  DIBCONTEXT* dc);          


// Отобразить блок растра в DIB
void _fastcall cntShowBlockMtrDib(TMapControl *mapcnt, RMFCHAIN* chain,
                                  DIBCONTEXT* dc); 


// Выбор значения абсолютной высоты в заданной точке.
double _fastcall cntGetHeightValue(TMapControl *mapcnt, double x, double y);

// Выбор значения абсолютной высоты в заданной точке из матрицы
// с номером number в цепочке.                        
// number - номер матрицы в цепочке.
double _fastcall cntGetMtrHeightValue(TMapControl *mapcnt,
                                      int number,double x, double y);

// Занесение значения абсолютной высоты в элемент матрицы,
// соответствующий заданной точке.
// number - номер матрицы в цепочке.
int _fastcall cntPutHeightValue(TMapControl *mapcnt, long int number,
                                double x, double y, double h);

// Выбор значения абсолютной высоты в заданной точке.
// Высота выбирается из самой точной матрицы высот,а в случае
// необеспеченности заданной точки данными матриц высот - по самой
// точной матрице слоев. Если высота не выбрана из матриц,
// выполняется запрос из TIN-модели.
// Координаты точки задаются в метрах в системе координат
// векторной карты. Возвращает значение высоты в метрах.
// В случае ошибки при выборе высоты и в случае необеспеченности
// заданной точки данными о высотах возвращает ERRORHEIGHT.
double _fastcall cntGetPrecisionHeightValue(TMapControl *mapcnt,
                                            double x, double y);

// Расчет абсолютной высоты методом треугольников в заданной точке
// по матрице с наименьшим размером элемента (более точной).
// Высота вычисляется по самой точной матрице высот,а в случае
// необеспеченности заданной точки данными матриц высот -
// по самой точной матрице слоев. Если высота не выбрана из матриц,
// выполняется запрос из TIN-модели.
// Координаты точки (x,y) задаются в метрах в системе координат
// векторной карты. Возвращает значение высоты в метрах.
// В случае ошибки при выборе высоты и в случае необеспеченности
// заданной точки данными о высотах возвращает ERRORHEIGHT.
double _fastcall cntGetPrecisionHeightTriangle(TMapControl *mapcnt,
                                               double x, double y);

//   Выбор массива значений абсолютных высот, соответствующих
//   логическим элементам, лежащим на заданном отрезке.
//   При ошибке возвращает ноль
int _fastcall cntGetHeightArray(TMapControl*  mapcnt,
                                double*       HeightArray,
                                int           HeightCount,
                                DOUBLEPOINT*  FirstPoint,
                                DOUBLEPOINT*  SecondPoint);

// Запросить описание файла матричных данных
// number - номер файла в цепочке
// describe - адрес структуры, в которой будет размещено
// описание матрицы
// При ошибке возвращает ноль
int _fastcall cntGetMtrDescribe(TMapControl*  mapcnt,
                                int number, MTRDESCRIBE * describe);

// Запросить данные о проекции матричных данных
// number - номер файла в цепочке
// projectiondata - адрес структуры, в которой будут размещены
// данные о проекции
// При ошибке возвращает ноль
int _fastcall cntGetMtrProjectionData(TMapControl*  mapcnt,
                                      int number, MTRPROJECTIONDATA* projectiondata);


// Запросить данные о проекции матричных данных    
// number - номер файла в цепочке
// mapregister - адрес структуры, в которой будут размещены
// данные о проекции
// При ошибке возвращает ноль
int _fastcall cntGetMtrProjectionDataEx(TMapControl *mapcnt,
                                      int number, MAPREGISTEREX* mapregister);

// Установить данные о проекции матричных данных   
// number - номер файла в цепочке
// mapregister - адрес структуры
// При ошибке возвращает ноль
int _fastcall cntSetMtrProjectionDataEx(TMapControl *mapcnt,
                                         int number, MAPREGISTEREX* mapregister);

// Запросить описание диапазона высот матрицы с номером
// number в цепочке
// colornumber - номер диапазона высот
// colordesc - адрес структуры, в которой будет размещено
// описание диапазона высот
// При ошибке возвращает ноль
int _fastcall cntGetMtrColorDesc(TMapControl*  mapcnt,
                                 int number, int colornumber,
                                 MTRCOLORDESCEX * colordesc);

// Установить цвет диапазона высот матрицы с номером
// number в цепочке
// colornumber - номер диапазона высот
// При ошибке возвращает ноль
int _fastcall cntSetMtrColor(TMapControl*  mapcnt,
                             int number,COLORREF color,
                             int colornumber);

// Запросить номер в цепочке для матрицы, расположенной
// в заданной точке
// number - порядковый номер, найденной матрицы в точке
// (1 - первая в данной точке, 2 - вторая ...)
// При ошибке возвращается ноль
int _fastcall cntGetMtrNumberInPoint(TMapControl*  mapcnt,
                                     double x, double y, int number);

// Поменять очередность отображения матриц    
// oldNumber - номер файла в цепочке
// newNumber - устанавливаемый номер файла в цепочке
//  При ошибке возвращает 0
int _fastcall cntChangeOrderMtrShow(TMapControl*  mapcnt,
                                    int oldNumber, int newNumber);

// Инициализировать переменные отображения матрицы  
void _fastcall cntInitMtrShowVariables(TMapControl* mapcnt);

// Инициализировать переменные отображения матрицы слоев 
void _fastcall cntInitMtlShowVariables(TMapControl* mapcnt);

// Открыть Rmf данные
int _fastcall cntOpenRmf(TMapControl *mapcnt, const char * name, int mode,
                         int flag);

// Закрыть Rmf данные
void _fastcall cntCloseRmf(TMapControl* mapcnt, CHAININFO *info, int number);

// Запросить элемент цепочки по номеру
// При ошибке возвращается ноль
RMFCHAIN* _fastcall cntGetRmfChain(CHAININFO *info, int number);

// Запросить номер цепочки по имени файла         
// При ошибке возвращается ноль
int _fastcall cntGetRmfNumberByName(CHAININFO *info, const char * name);

// Проверить соответствие типа исх. карт-материала
void _fastcall cntCheckMapTypeRmf(TMapControl *mapcnt, RSTCHAIN *chain);

// Проверить попадание матрицы в район
int _fastcall cntCheckDimensionRmf(TMapControl *mapcnt, RSTCHAIN *chain);

// Проверить соответствие типа высот цепочки и добавляемой матрицы  
int _fastcall cntCheckMtrTypeRmf(TMapControl *mapcnt, RSTCHAIN *chain, int curType);

// Запросить степень видимости
// Возвращает: 1- растр виден; 0- растр не виден         
// При ошибке возвращает -1
int _fastcall cntCheckRmfView(CHAININFO *info, int number);

// Установить степень видимости
//  view = 0   - не виден
//  view = 1   - полная
//  view = 2   - насыщенная      //  устаревшее значение 
//  view = 3   - полупрозрачная  //  устаревшее значение 
//  view = 4   - средняя         //  устаревшее значение 
//  view = 5   - прозрачная      //  устаревшее значение 
// При ошибке возвращает -1
int _fastcall cntSetRmfView(CHAININFO *info, int number, int view);

// Запросить/Установить степень прозрачности изображения  
// procentValue - прозрачность изображения (от 0 до 100%)
// При ошибке возвращает -1
int _fastcall cntGetRmfTransparent(CHAININFO *info, int number);
int _fastcall cntSetRmfTransparent(CHAININFO *info, int number, int procentValue);

// Запросить/Установить тип маски отображения (0-8)
// При ошибке возвращает -1
int _fastcall cntGetRmfMaskType(CHAININFO *info, int number);   
int _fastcall cntSetRmfMaskType(CHAININFO *info, int number,int masktype);

// Запросить/Установить порядок отображения
//  (0 - под картой, 1 - над картой)
// При ошибке возвращает -1
int _fastcall cntRmfViewOrder(CHAININFO *info, int number, int order);

// Последовательный просмотр растров над картой
int _fastcall cntTurnRmfViewOrder(CHAININFO *info);  

// Запросить признак отображения цвета
// Возвращает:  1 - отображать; 0 - не отображать; -1 - ошибка
int _fastcall cntCheckRmfPaletteView(CHAININFO *info, int number, int index);

// Установить признак отображения цвета
// При ошибке возвращается  -1
int _fastcall cntSetRmfPaletteView(CHAININFO *info, int number,int index,int value);

// Установить точность в цепочке
int _fastcall cntSetRmfPrecision(CHAININFO *info, int number, double precision);

// Запросить габариты в районе работ
// Возвращает указатель на габариты в элементах растра
//  number - номер файла в цепочке
// При ошибке возвращает ноль
DFRAME * _fastcall cntGetRmfFrame(CHAININFO *info, int number);

// Запросить габариты в районе работ
// Возвращает указатель на габариты растра в метрах
//  number - номер файла в цепочке
// При ошибке возвращает ноль
DFRAME * _fastcall cntGetRmfFrameMeters(CHAININFO *info, int number);

// Запросить имя файла данных
// При ошибке возвращает ноль
const char * _fastcall cntGetRmfName(CHAININFO *info, int number);

// Запросить адрес активной палитры растра
// (с учетом яркости и контрасности)
// number - номер файла в цепочке
// При ошибке возвращает 0
COLORREF* _fastcall cntGetRmfPalette(CHAININFO *info, int number);

// Запросить/Установить яркость палитры (от -4 до 4)
// number - номер файла в цепочке
// При ошибке возвращает 0
int _fastcall cntGetRmfBright(CHAININFO *info, int number);

// Выбор значениe высоты в заданной точке по цепочке матриц.
// Координаты точки задаются в метрах в системе координат
// векторной карты. Возвращает значение высоты в метрах.
// В случае ошибки при выборе высоты и в случае необеспеченности
// заданной точки матричными данными height = ERRORHEIGHT,
// возвращает 0.
int _fastcall cntGetRmfElementHeight(CHAININFO *info, double x, double y,
                                     double *height);

// Выбор значениe высоты в заданной точке цепочки.
// Координаты точки задаются в метрах в системе координат
// векторной карты. Возвращает значение высоты в метрах.
// В случае ошибки при выборе высоты и в случае необеспеченности
// заданной точки матричными данными height = ERRORHEIGHT.
// Если точка вне матрицы или ошибка при чтении возвращает 0
int _fastcall cntGetRmfElementHeightChain(RMFCHAIN *chain, double x, double y,
                                          double *height);

// Занесение значения абсолютной высоты в элемент матрицы,
// соответствующий заданной точке.
// number - номер матрицы в цепочке.
// Координаты точки (x,y) и значение высоты (h) задаются в метрах
// в системе координат векторной карты.
// В случае ошибки возвращает ноль.
int _fastcall cntPutRmfHeightValue(CHAININFO *info, long int number,
                                   double x, double y, double h);

// Запросить описание файла матричных данных
// number - номер файла в цепочке
// describe - адрес структуры, в которой будет размещено
// описание матрицы
// При ошибке возвращает ноль
int _fastcall cntGetRmfDescribe(CHAININFO *info,
                                int number, MTRDESCRIBE * describe);

// Запросить данные о проекции матричных данных
// number - номер файла в цепочке
// projectiondata - адрес структуры, в которой будут размещены
// данные о проекции
// При ошибке возвращает ноль
int _fastcall cntGetRmfProjectionData(CHAININFO *info,
                                      int number, MTRPROJECTIONDATA* projectiondata);


// Запросить данные о проекции матричных данных   
// number - номер файла в цепочке
// projectiondata - адрес структуры, в которой будут размещены
// данные о проекции
// При ошибке возвращает ноль
int _fastcall cntGetRmfMapRegisterEx(CHAININFO *info,
                                      int number, MAPREGISTEREX* projectiondata);

// Установить данные о проекции      
// number - номер файла в цепочке
// mapregister - адрес структуры, в которой будут размещены
// данные о проекции
// При ошибке возвращает ноль
int _fastcall cntSetRmfMapRegisterEx(CHAININFO *info,
                                      int number, MAPREGISTEREX* mapregister);


// Запросить номер в цепочке для матрицы, расположенной
// в заданной точке
// number - порядковый номер, найденной матрицы в точке
// (1 - первая в данной точке, 2 - вторая ...)
// При ошибке возвращается ноль
int _fastcall cntGetRmfNumberInPoint(CHAININFO *info,
                                     double x, double y, int number);

// Поменять очередность отображения матриц
// oldNumber - номер файла в цепочке
// newNumber - устанавливаемый номер файла в цепочке
//  При ошибке возвращает 0
int _fastcall cntChangeOrderRmfShow(CHAININFO *info,
                                    int oldNumber, int newNumber);

// Определение попадания в видимую клиентную область
int _fastcall cntCheckViewRmf(TMapControl *mapcnt);

// Установить рамку
int _fastcall cntSetRmfBorderPlane(CHAININFO *info,
                                   int number, TDataEdit* data);

//  Запросить рамку
TDataEdit* _fastcall cntGetRmfBorderPlane(CHAININFO *info, int number);

#ifndef HIDEMTQ    

// ===========================================================
//           МАТРИЦЫ КАЧЕСТВ  
// ===========================================================

// Открыть данные матрицы качеств
int _fastcall cntOpenMtq(TMapControl *mapcnt, const char * name,
                         int mode);

// Закрыть данные матрицы качеств
void _fastcall cntCloseMtq(TMapControl *mapcnt, int number);

// Запросить количество цветов в палитре матрицы качеств
// При ошибке возвращает 0
int _fastcall cntGetMtqPaletteCount(RMFCHAIN *chain);

// Запросить описание диапазона высот матрицы качеств с номером
// number в цепочке
// colordesc - адрес структуры, в которой будет размещено
// описание диапазона высот
// При ошибке возвращает ноль
int _fastcall cntGetMtqColorDesc(TMapControl *mapcnt,long int number,
                                 long int colornumber,
                                 MTRCOLORDESCEX * colordesc);

// Установить/Запросить тень матрицы качества
// value - флаг наложения тени (1 - тень есть, 0 - тени нет)
int _fastcall cntSetMtqShadow(TMapControl *mapcnt, int number, int value);  
int _fastcall cntGetMtqShadow(TMapControl *mapcnt, int number);

// Установить цвет диапазона высот матрицы качеств с номером  // number в цепочке
// colornumber - номер диапазона высот
// При ошибке возвращает ноль
int _fastcall cntSetMtqColor(TMapControl*  mapcnt,
                             int number,COLORREF color,
                             int colornumber);

// Запросить видимость цвета матрицы качеств (до 256-цветов)
//  number - номер файла в цепочке
//  index  - индекс цвета в палитре матрицы(начиная с 0)
//  Возвращает: 1 - цвет с данным индексом отображается
//              0 - цвет с данным индексом не отображается
//  При ошибке возвращает -1
int _fastcall cntCheckMtqVisibilityColor(TMapControl *mapcnt,
                                         int number,int index);

// Запросить элемент цепочки по номеру
// При ошибке возвращается ноль
RMFCHAIN* _fastcall cntGetMtqChain(TMapControl *mapcnt, int number);

// Установка отображения матрицы по рамке    
// value = 1 - отобразить матрицы по рамке
//       = 0 - отобразить матрицы без учета рамки
//  При ошибке возвращает 0
int _fastcall cntShowMtqByBorder(TMapControl *mapcnt, int number, int value);

// Определение способа отображения матрицы(относительно рамки)
// Возвращает 1 - при отображении матрицы по рамке
//            0 - при отображении матрицы без учета рамки
// При ошибке возвращает -1
int _fastcall cntCheckShowMtqByBorder(TMapControl *mapcnt, int number);

// Поменять очередность отображения матриц качеств
// oldNumber - номер файла в цепочке
// newNumber - устанавливаемый номер файла в цепочке
//  При ошибке возвращает 0
int _fastcall cntChangeOrderMtqShow(TMapControl*  mapcnt,
                                    int oldNumber, int newNumber);

// Установить рамку матрицы качеств
int _fastcall cntSetMtqBorderPlane(TMapControl *mapcnt,
                                   int number, TDataEdit* data);

// Запросить рамку матрицы качеств
TDataEdit* _fastcall cntGetMtqBorderPlane(TMapControl *mapcnt, int number);

// Запросить данные о проекции матрицы качеств          
// number - номер файла в цепочке
// mapregisterex - адрес структуры, в которой будут размещены
// данные о проекции
// При ошибке возвращает ноль
int _fastcall cntGetMtqProjectionData(TMapControl *mapcnt,
                                      int number, MAPREGISTEREX* mapregisterex);

// Установить данные о проекции матрицы качеств    
// number - номер файла в цепочке
// mapregister - адрес структуры
// При ошибке возвращает ноль
int _fastcall cntSetMtqProjectionData(TMapControl *mapcnt,
                                      int number, MAPREGISTEREX* mapregister);

// Записать в файл палитру матрицы качеств         
// (записываем всегда массив размером 256,
//  число цветов - ADDITION.MatrixColorCount)
// chain - звено цепочки
// palette - адрес заданной палитры
// count - число цветов заданной палитры
// При ошибке возвращает ноль
int _fastcall cntResetMtqPalette(RMFCHAIN* chain,
                                 COLORREF *palette, int count);

// Установить/Запросить видимость матрицы качества  
//  view = 0   - матрица качества не отображаемая
//  view = 1   - полная
//  view = 2   - насыщенная
//  view = 3   - полупрозрачная
//  view = 4   - средняя
//  view = 5   - прозрачная
int _fastcall cntCheckMtqView(TMapControl *mapcnt, int number);
int _fastcall cntSetMtqView(TMapControl *mapcnt, int number, int view);

#endif

#endif  // MAPCNT_H

