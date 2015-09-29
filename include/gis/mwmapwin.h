
#if !defined(MWMAPWIN_H)
#define MWMAPWIN_H

#ifndef MWMACRO_H
  #include "mwmacro.h"
#endif

#ifndef MWFILEIN_H
  #include "mwfilein.h"     // Обработка INI - файлов
#endif

#ifndef MAPACCES_H
  #include "mapacces.h"
#endif

#include "mapversn.h"               // 24/02/04

typedef TMapAccess TMapDoc;

#ifdef LINUXAPI   // 10/03/02

#ifndef MWHANDLR_H
  #include "mwhandlr.h"
#endif

#endif    // LINUXAPI

#define IDTIMER_MARKER 4000          // 20/09/04
#define IDTIMER_SELECT 4001          // 21/02/06

#ifdef WIN32API  // 29/01/02
class DECLSPEC_IMPORT TModule;
class DECLSPEC_IMPORT TPrinter;
class DECLSPEC_IMPORT TWindow;
#endif

class _DLLCLASSTASK  TMapAction;

// Выбрать имя файла по заданным условиям
// (обязательно применять при выборе любого имени файла!)
// name     - строка для размещения результата выбора
// namesize - размер строки для результата (MAX_PATH)
// title    - заголовок диалога с учетом языка интерфейса
// filter   - список строк видов файлов
// flags    - управляющие флажки диалога
// index    - текущий номер строки вида файла при открытии диалога
// path     - текущая директория при открытии диалога
// Возвращает номер строки в списке типов файлов (>=0)
// При ошибке или отказе от выбора файла -
// возвращает отрицательное значение
int OpenFile(char * name, int namesize,
#ifdef WIN32API  // 29/01/02
             TWindow * window,
#else
             void    * window,
#endif
             const char * title, const char * filter,
             int  flags,  int    index,
             const char * path);

// Дополнительный флаг для диалога сохранения файла
#define OFLAG_SAVE 0x0F0000000

// Цвет выделенных объектов
#define SELECTCOLOR RGB(0xF0,0x20,0x90)   // 0x09020F0 - Фиолетовый


/******************************************************************
********************  СИСТЕМЫ КООРДИНАТ ***************************
*******************************************************************

    X map
  ^
  | (0,0) (Начало изображения "Picture")
  +---------------------------------------------------> X picture
  |                                                 ^
  |        (Координаты окна "Client")               |
  |   (0,0)                      Xо                 |
  |     ----------------------->                    |
  |     |               |                           |
  |     |        x..... x  Окно визуализации        |
  |     |        ....A. |                           |
  |     |        ...+.. |                           |
  |     |        ...... |                  Габариты в пикселах
  |     ---------x------x                  района ("RegionPix")
  |     |          ^                                |
  |     |          |                                |
  |     |         Область текущего вывода           |
  |     V                  ("Draw")                 |
  |       Yо                                        |
  |                                                 V
  +----------------------------------------------------> Y map
  |
  |  0,0 (Начало района "Map" в дискретах
  |       и "пикселах")
  |
  V              координаты т.A в районе Xд,Yд; в изображении Xи,Yи
    Y picture     Xд = Pix2Dis(RegionPix.X2 - Yи);
                  Yд = Pix2Dis(RegionPix.Y1 + Xи);

******************************************************************/


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++ КЛАСС "ОКНО ЭЛЕКТРОННОЙ КАРТЫ" ++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapWindow
{

public:

#ifdef WIN32API  // 29/01/02
    // Создать объект "окно электронной карты"
    TMapWindow(HWND hMain);
#else
    // Создать объект "окно электронной карты"
    TMapWindow(MSGHANDLER handler);
#endif

    // Удалить объект "окно электронной карты"
    ~TMapWindow();

  /************************************************************
  *                                                           *
  *           Запрос справочной информации                    *
  *                                                           *
  ************************************************************/

    // Запросить имя приложения
    char * GetApplicationName();

    // Запросить имя файла "ini" приложения
    char * GetIniName();

    // Запросить имя файла "ini" карты
    const char * GetMapIniName()
#ifdef WIN32API  // 05/03/02
      { return MapDoc->GetMapIniName(); }
#else
      { return mapGetMapIniName((HMAP)MapDoc); }
#endif

    // Запросить имя файла "hlp" приложения
    char * GetHelpName();

    // Запросить текущий язык диалогов приложения
    int GetLanguage();

    // КОДЫ ЯЗЫКОВ СООБЩЕНИЙ И ПУНКТОВ МЕНЮ
    enum OPTIONLANGUAGE
     {
       ML_ENGLISH = 1,  // АНГЛИЙСКИЙ
       ML_RUSSIAN = 2   // РУССКИЙ
     };

    // Запросить состояние панели инструментов (отображена или нет)
    // id - идентификатор панели (CM_MAPEDIT - панель редактора, ...)
    // Если панели нет - возвращает ноль
    int GetPanelState(int id);

    // Запросить путь к директории приложения
    char * GetPathShell();

    // Функция возвращает габариты всего изображения в пикселах
    //   (X,Y в координатах Windows)
    void GetPictureBorder(long& x, long& y);

#ifdef WIN32API  // 29/01/02
    // Запросить принтер приложения
    TPrinter* GetPrinter();

    // Вызвать диалог настройки принтера
    void CmPrintSetup();

    // Запросить текущий модуль ресурсов приложения
    TModule * GetResourceModule();
#endif

    // Загрузить библиотеку dllname и найти точку входа funcname
    // При поиске DLL проверяется и директория приложения
    // При ошибке возвращает ноль,
    // если message != 0 - выдает сообщение на экран
    // Параметр libinst содержит идентификатор загруженной
    // библиотеки dllname
    FARPROC  LoadMapLibrary(const char * dllname,
                            HINSTANCE&   libinst,
                            const char * funcname,
                            bool message);

    // Запросить имя пользователя
    const char * GetUserName();

    // Запросить параметры для вызова задачи
    TASKPARM * GetTaskParm() {return (TASKPARM *) GetTaskParmEx();}
    TASKPARMEX * GetTaskParmEx();

    // Запустить прикладную библиотеку
    // При ошибке возвращает ноль                 // 18/09/03
    int CallMapLibrary(const char * dllname);


  /************************************************************
  *                                                           *
  *     Управление масштабированием и пересчетом координат    *
  *                                                           *
  ************************************************************/

public:

   enum POINTTYPE      // ФОРМАТ ОТОБРАЖЕНИЯ КООРДИНАТ ТОЧКИ
    {
      PLANEPOINT      = 1,  // В метрах на местности в соответствии с проекцией
      MAPPOINT        = 2,  // В условных единицах карты (дискретах)
      PICTUREPOINT    = 3,  // В пикселах текущего полного изображения

      // СК-42
      GEORAD          = 4,  // В радианах
      GEOGRAD         = 5,  // В градусах
      GEOGRADMIN      = 6,  // В градусах, минутах, секундах
     
      // WGS-84
      GEORADWGS84     = 7,  // В радианах
      GEOGRADWGS84    = 8,  // В градусах
      GEOGRADMINWGS84 = 9,  // В градусах, минутах, секундах

      PLANE42POINT    = 10, // В метрах на местности по ближайшей зоне

      //ПЗ-90.11
      GEORADPZ90      = 11,  // В радианах
      GEOGRADPZ90     = 12,  // В градусах
      GEOGRADMINPZ90  = 13,  // В градусах, минутах, секундах
      
      //ГСК-2011
      GEORADGSK2011      = 14,  // В радианах
      GEOGRADGSK2011     = 15,  // В градусах
      GEOGRADMINGSK2011  = 16  // В градусах, минутах, секундах
    };

    // Рассчитать прямогольные координаты заданной точки
    // в различных системах координат (PICTURE,MAP,PLANE)
    void CalculateRectangular(POINT& point);

    // Функция изменения масштаба
    //   Параметры:
    //    change  - коэффициент изменения текущего масштаба ( > 0)
    //   Возвращает: 0 - масштаб не изменился, 1 - масштаб изменился
    int ChangeScale(float change);

    // Функция изменения масштаба по размерам объекта
    // Возвращает: 0 - масштаб не изменился, 1 - масштаб изменился
    int ChangeScaleByObject(TObjectInfo * info);

    // Функция изменения масштаба по габаритам выделенных объектов
    // Возвращает: 0 - масштаб не изменился, 1 - масштаб изменился
    int ChangeScaleBySelect();

   // Функция изменения масштаба по координатам фрагмента в метрах
   // Возвращает: 0 - масштаб не изменился, 1 - масштаб изменился
   int ChangeScaleByFrame(DFRAME * frame);

    // Преобразование координат точки клиентной области (CLIENT)
    // в координаты изображения (PICTURE)
    POINT Client2Picture(POINT& point);

    // Преобразование координат прямоугольника
    RECT Client2Picture(RECT& rect);

    // Запросить координаты в географической системе (Geo)
    // для эллипсоида Красовского
    // Возвращаются координаты текущей точки в радианах
    // Если географическая система координат не поддерживается
    // значение координат всегда ноль !
    // Определение поддержки географических координат :
    // if (MapDoc->IsGeoSupported() != 0) { поддерживаются; }
    DOUBLEPOINT * GetGeoPoint(double height = 0);

    // Запросить координаты в географической системе (Geo)
    // для эллипсоида WGS84
    // Возвращаются координаты текущей точки в радианах
    // Если географическая система координат не поддерживается
    // значение координат всегда ноль !
    DOUBLEPOINT * GetGeoWGS84Point()
     {
       return &WGS84GeoPoint;
     }

    // Запросить координаты в географической системе (Geo)
    // для эллипсоида карты
    // Возвращаются координаты текущей точки в радианах
    // Если географическая система координат не поддерживается
    // значение координат всегда ноль !
    // Определение поддержки географических координат :
    // if (MapDoc->IsGeoSupported() != 0) { поддерживаются; }
    DOUBLEPOINT * GetMapGeoPoint();

    // Запросить координаты левого верхнего угла карты
    POINT * GetPicturePoint();

    // Установить координаты левого верхнего угла карты
    POINT * SetPicturePoint(POINT& point);

    // Запросить координаты левого верхнего угла карты в дискретах в районе
    DOUBLEPOINT * GetMapWindowPoint();

    // Переместить заданную точку карты в левый верхний угол
    // Координаты в дискретах в районе
    // Возвращает новое значение
    DOUBLEPOINT * SetMapWindowPoint(DOUBLEPOINT * point);

    // Преобразование координат точки изображения карты
    // в координаты клиентной области окна
    POINT Picture2Client(POINT& point);

    // Преобразование координат точки на местности
    // к координатам клиентной области (CLIENT)
    POINT PlaneToClient(DOUBLEPOINT &planepoint);

    // Преобразование координат точки на карте
    // к координатам клиентной области (CLIENT)
    POINT MapToClient(DOUBLEPOINT &mappoint);

    // Преобразовать радианы в символьный вид в градусы
    // Возвращает адрес переданной строки
    // maxlength - размер входной строки ( >= 14 !)
    char * RadianToGradString(double * rad,char * string,
                              int maxlength);

    // Функция изменения масштаба
    //   Параметры:
    //          Scale - реальный масштаб, который желают получить
    //   Возвращает: 0 - масштаб не изменился, 1 - масштаб изменился
    // free - признак произвольного (не табличного) масштаба
    int SetMapScale(float scale, int free = 0);

    // Установить курсор окна
    // Возвращает идентификатор старого курсора
    int SetMapCursor(int cursor = 0);

    // Установить стандартный курсор окна (IDC_WAIT, IDC_SIZE, ...)
    // Возвращает идентификатор старого курсора
    int SetWinCursor(char* cursor = 0);

    // Запись вещественного числа в символьном виде с фиксированной точкой
    // со вставкой разделяющих пробелов (разделение на тройки символов
    // от десятичной точки к началу строки)
    void SpaceInsert(char* string, char * format, double number);

public :

// ПРЯМОУГОЛЬНЫЕ КООРДИНАТЫ ТЕКУЩЕЙ ТОЧКИ

POINT        PicturePoint; // Координаты в изображении карты (пикселы)
                           // от верхнего левого угла изображения
DOUBLEPOINT  MapPoint;     // Координаты в логической системе карты (дискреты)
                           // от нижнего левого угла района работ
DOUBLEPOINT  PlanePoint;   // Координаты на местности (метры)
                           // от нижнего левого угла системы координат

// ГЕОГРАФИЧЕСКИЕ КООРДИНАТЫ ТЕКУЩЕЙ ТОЧКИ

DOUBLEPOINT  GeoPoint;      // Координаты на местности (радианы)

DOUBLEPOINT  WGS84GeoPoint; // Координаты на местности WGS84 (радианы)

DOUBLEPOINT  PZ90GeoPoint;  // Координаты на местности ПЗ-90 (радианы)

DOUBLEPOINT  GSK2011GeoPoint;  // Координаты на местности ГСК-2011 (радианы) 

protected :

DOUBLEPOINT MapWindowPoint; // Координаты левого верхнего угла
                            // окна на карте

  /************************************************************
  *                                                           *
  *           Управление текущим процессом                    *
  *                                                           *
  ************************************************************/

public:

  enum PROCESS   // ИДЕНТИФИКАТОРЫ ПРОЦЕССОВ
  {
    IDP_COMMENT     = 1,  // Вывод комментариев разрешен
    IDP_SCALECENTRE = 2,  // Масштабировать от центра экрана
    IDP_LOCKMAP     = 4,  // БЛОКИРОВАТЬ ДОСТУП К ИЗОБРАЖЕНИЮ КАРТЫ
                          // (НЕ ОБНОВЛЯТЬ ИЗОБРАЖЕНИЕ КАРТЫ)
  };

  // Состояние управляющих клавиш и кнопок мыши MK_ ...
  int GetKeyStatus() { return KeyStatus; }
  int GetShiftStatus() { return (KeyStatus & MK_SHIFT); }

  enum SWITCH
  {
    ICP_OFF   = 0,  // Выключить флажок
    ICP_ON    = 1,  // Включить флажок
    ICP_CHECK = 2,  // Проверить флажок
    OFF       = 0,  // Выключить флажок
    ON        = 1,  // Включить флажок
  };

  // "Заморозить"/"Оживить" изображение карты
  void LockMap()   { SetProcess(IDP_LOCKMAP,ON); }
  void UnlockMap() { SetProcess(IDP_LOCKMAP,OFF); }
  int IsLockMap()  { return CheckProcess(IDP_LOCKMAP); }

  // Проверить флажок текущего процесса
  int CheckProcess(int ident);

  // Установить флажок текущего процесса
  int SetProcess(int ident, int mode);

  // Установить/Проверить флажок текущего процесса
  // Возвращает текущее значение флажка процесса (0/1)
  int ControlProcess(int ident, int mode = ICP_CHECK);

  // Запустить линейку с процентом выполнени процесса
  // title - название процесса
  void CreateProgress(const char * title);

  // Показать процент выполнения (0 - 100)
  // Если процесс должен завершиться принудительно -
  // возвращает 0 !
  int SetProgressPercent(int value, const char * title = 0);

  // Убрать линейку выполнения процесса
  void DeleteProgress();

  // Установить обработчик окна навигации
  virtual void SetNavigator(TMapAction * action) {};

  // Запросить наличие обработчика окна навигации
  int IsNavigator() { return (Navigator != 0); }

  // Запросить - активен ли какой-либо режим задач           // 18/04/05
  virtual int IsActionActive() { return 0; }

protected :

 int    KeyStatus;            // Состояние управляющих клавиш MK_ ...
 int    Process;              // Флажки управления окном карты

  /************************************************************
  *                                                           *
  *     Запрос и обработка информации об объекте карты        *
  *                                                           *
  ************************************************************/

public :

  // Согласовать описание данных в памяти и на диске
  // и обновить изображение
  // Если изменений в памяти нет - возвращает ноль
  int AdjustData();

  // Заблокировать (1) / разблокировать (0) контроль обновления данных
  int LockAdjustData(int lock);              // 28/04/05

  // "Забыть" о выбранном объекте и стереть выделение на карте
  virtual void ClearSelect() {}

  // Запросить - можно ли выбирать объект на карте ?
  virtual int CanSelectObject() { return 1; }

  // Запросить - можно ли выбирать данный объект на карте ?
  virtual int CanSelectObject(TObjectInfo * /*info*/)
    { return 1; }

  // Запросить выбран ли объект на карте
  int IsObjectSelected(int real = -1)
   { return ((real & SelectFlag) != 0);}      // 20/03/02

  //  Запрос объекта в текущей точке (в позиции курсора)
  virtual int SelectObject(TObjectInfo * info)
    { return 0; }

  // Выполнить переход к следующему объекту в соответствии с текущей
  // операцией поиска или выделения объектов на карте
  // Если info равняется нулю, то перебор объектов выполняется
  // от текущего активного объекта
  // Если active не равен нулю - найденный объект становится текущим 
  // Если следующего объекта нет - возвращается ноль
  virtual int NextActiveObject(TObjectInfo * info, int active = 0)
    { return 0; }

  // Выполнить переход к предыдущему объекту в соответствии с текущей
  // операцией поиска или выделения объектов на карте
  // Если info равняется нулю, то перебор объектов выполняется
  // от текущего активного объекта
  // Если active не равен нулю - найденный объект становится текущим
  // Если предыдущего объекта нет - возвращается ноль
  virtual int PrevActiveObject(TObjectInfo * info, int active = 0)
    { return 0; }

  // Запрос объекта в области frame (дискреты)
  TObjectInfo * WhatObject(TObjectInfo * info,
                           DFRAME * frame, int flag = WO_FIRST);

  // Поиск объекта по заданным условиям
  virtual int SearchObject(TObjectInfo * /*info*/,int /*flag*/, int /*type*/)
    { return 0; }

  // Поиск объекта по заданным условиям
  TObjectInfo * SeekObject(TObjectInfo * info,TMapSelect * select,
                            int flag = WO_FIRST|WO_INMAP);

  // Установить последний найденный объект
  // Поиск будет продолжен с данного объекта
  void SetLastSeekObject(TObjectInfo * info);

  // Установить выбранный объект
  // Выбранный объект автоматически будет выделен на карте
  void SetSelectObject(TObjectInfo * info);

  // Отобразить участок карты,на котором расположена заданная точка,
  // (в дискретах) в центре окна
  // При ошибке возвращает ноль
  // Иначе - координаты заданной точки в пикселах
  // в клиентной области окна
  POINT  ViewMapPoint(DOUBLEPOINT * point);

  // Отобразить участок карты,на котором расположена заданная точка,
  // (в метрах) в центре окна
  // При ошибке возвращает ноль
  // Иначе - координаты заданной точки в пикселах
  // в клиентной области окна
  POINT  ViewPlanePoint(DOUBLEPOINT * point);

  // Отобразить участок карты,на котором расположена заданная точка,
  // в определенном фрагменте окна
  // Координаты фрагмента в пикселах в клиентной области
  // При ошибке возвращает ноль
  // Иначе - координаты заданной точки в пикселах             // 04/03/07
  // в клиентной области окна
  POINT  ViewMapPointInRect(DOUBLEPOINT * point, RECT  * rect, int update = 0);

  // Отобразить участок карты,на котором расположен заданный объект,
  // в определенном фрагменте окна
  // Координаты фрагмента в пикселах в клиентной области
  // При ошибке возвращает ноль
  // Иначе - координаты видимой точки метрики объекта в пикселах
  // в клиентной области окна
  POINT  ViewObject(TObjectInfo * info,RECT  * rect);

  // Запросить открыта ли дополнительная информация по объектам
  int GetDetailInfo() { return FlagDisplayDetailInfo; }

  // Сбросить флаг наличия дополнительной информации по объектам
  int ClearDetailInfo() { return (FlagDisplayDetailInfo = 0); }

  // Установить флаг наличия дополнительной информации по объектам
  int SetDetailInfo(int flagdisplay)
     { return (FlagDisplayDetailInfo = flagdisplay); }

  // Отменить выделение точки на карте
  void ClearMarker();

  // Показать выделение точки на карте
  void PaintMarker(HDC hdc,RECT& rect);
  void PaintMarker();

  // Отметить точку на карте
  // point - координаты в дискретах
  void SetMarker(DOUBLEPOINT * point);

  // Запросить выделенную точку
  DOUBLEPOINT *GetMarkPoint() { return &MarkPoint; };

  // Запросить наличие выделенной точки
  int IsMarkedPoint() { return IsMarked; }

  // Запросить отмечены ли объекты на карте
  int IsViewSelected()
#ifdef WIN32API  // 29/01/02
     { return MapDoc->GetTotalSelectFlag(); }
#else
     { return mapGetTotalSelectFlag((HMAP)MapDoc); }
#endif

  // Установить выделение объектов на карте
  // Цвет равный 0, заменяется на цвет по умолчанию
  void SetViewSelect(int select,
                     COLORREF color = 0);

  void PaintSelect(HDC hdc, RECT& rect);

  // Установить/опросить границы поиска объектов на карте
  // -1     - глобальный поиск(по всем картам)
  // 0,1... - номер карты,в пределах которой выполняется поиск
  int SeekScope(int scope);
  int SeekScope();

  // Установить/опросить границы поиска объектов на карте
  // view == 0 - поиск среди всех объектов карты
  // view == 1 - поиск среди видимых объектов
  int VisualSearch(int view)
#ifdef WIN32API  // 29/01/02
     { MapDoc->SetTotalSeekViewRule(view);
       return MapDoc->GetTotalSeekViewRule(); }
#else
     { mapSetTotalSeekViewRule((HMAP)MapDoc, view);
       return mapGetTotalSeekViewRule((HMAP)MapDoc); }
#endif
  int VisualSearch()
#ifdef WIN32API  // 29/01/02
     { return MapDoc->GetTotalSeekViewRule(); }
#else
     { return mapGetTotalSeekViewRule((HMAP)MapDoc); }
#endif

  enum AREASEEKFLAGS         // Флажки поиска по области          // 01/09/04
  {
    AS_NO     = 0,    // Не выполнять поиск по области
    AS_RUN    = 1,    // Выполнить поиск по области
    AS_SELECT = 2,    // Выбрать область поиска
    AS_FRAME  = 4,    // Выполнить поиск по рамке
  };

  // Установить/опросить поиск объектов по заданной области
  // area = 0 - не выполнять поиск по области
  // area = 1 - выполнить поиск по области
  // area = 2 - выполнить выбор области
  // area = 4 - выполнить поиск по рамке
  int AreaSearch(int area);
  int AreaSearch(){return AreaSeekFlag;}

  // Установить область поиска
  // При ошибке возвращает "0"
  TObjectInfo * PutSearchArea(TDataEdit * data);    // 16/10/02

  TObjectInfo * PutSearchArea(TObjectInfo * info);

  // Запросить область поиска                      // 24/11/00
  TObjectInfo * GetSelectArea(void) {return (TObjectInfo *)&SelectArea;}

  // Опросить установлена ли область поиска:
  // 0 - область отсутствует
  // 1 - область установлена
  int IsAreaSelected()
     {
        return (SelectArea.Data.IsCorrect() &&
                (SelectArea.Data.PointCount() >0) );
     }

  // Запросить область поиска для отображения       17/11/00
  TObjectInfo * GetAreaShow(void) {return (TObjectInfo * )&AreaShow;}


  /************************************************************
  *                                                           *
  *           Управление выводом комментариев                 *
  *                                                           *
  ************************************************************/

  // Инициализировать таблицу сообщений

  void InitMessageTable();

  // Загрузить текстовую строку из общих ресурсов

  int LoadString(int id, char * buffer, int size);

  // MessageBox с загрузкой из ресурсов

  int MessageInfo(int idmessage, int idtitle);
  int MessageError(int idmessage, int idtitle);
  int MessageQuest(int idmessage, int idtitle);

  // Вывести сообщение в строку состояния
  // Для отмены сообщения text = 0

  void SetMessage(const char * text);

  // Вывести сообщение в линейку статуса с загрузкой из ресурсов
  // Для отмены сообщения id = 0

  void SetMessage(int id);

  // Вывести сообщение в заголовок окна

  void SetWindowTitle(const char * message);

  // Убрать сообщение из заголовка окна

  void ClearWindowTitle();

  // Сформировать описание объекта
  // При ошибке возвращает ноль (нет объекта или буфер меньше 100 байт)

  char * ObjectComment(TObjectInfo * info,char * comm,int length);

 // Вывести сообщение в заголовок окна

 void SetObjectComment(TObjectInfo * info);

  // Сформировать описание карты

  void MapComment();

  // Вывести в информационную линейку сведения о карте

  void CommentMessage();

  // Вывод сообщений карты в линейку статуса (координаты,номенклатура)
  // point - координаты в клиентной области окна

  void CommentPoint(POINT & point);

  //  Вывод сообщений карты в линейку статуса (координаты точки)

  void PointToString(DOUBLEPOINT * point,
                     int place,
                     char *string, int maxlength);

  //  Вывод сообщений карты в линейку статуса (координаты точки) сокращенный вариант
  // строки неоходимые для отображения точки поворота
  void PointToString(char *string, int maxlength);

  // Очистить информационную линейку

  void EraseComment();

  // Вывести сообщение в информационную линейку

  void SetComment(int type,const char * message);

  // Отобразить раздел "HELP"
  // ident - идентификатор раздела
  // check - признак проверки активности системы HELP,
  // если равен 0 - принудительный вывод HELP

  int ViewHelp(int ident, int check = 0);
  int ViewHelpEx(const char * help, int ident, int check = 0);

  // Нажать кнопку для команды id
  // При ошибке возвращает ноль (не найдена кнопка)

  int PressButton(int id);

  // Отжать кнопку для команды id

  void ReleaseButton(int id);

  // Установить доступность кнопки для команды id

  void EnableButton(int id, int enable = 1);               // 30/01/07

  // Название приложения

  const char * GetViewName() {return GetApplicationName();}

  // Сформировать название типа карты

  char * GetMapType();

  // Запросить количество отображаемых объектов по всем картам

  int ViewCount(int update = 0);

  // Запросить количество выделенных объектов

  int MarkCount(int update = 0);


public :

  enum VIEWTYPE  //  ТИПЫ ОТОБРАЖЕНИЯ КАРТЫ
   {
     VIEW_NORMAL         = 1, // Быстрое (экранное) отображение
     VIEW_SCHEMATICAL    = 2, // Схематичное отображение
     VIEW_PRINTER        = 3, // "Принтерное" отображение
     VIEW_PRINTERCONTOUR = 4  // "Принтерное" схематичное отображение
   };

 int ViewType;              // Способ отображения карты

 int PlaceSystem;           // Текущая система отображения координат

 int FlagDisplayDetailInfo; // Открыто окно дополнительной
                            // информации по объекту
 int MarkPointSwitch;       // Состояние мониторинга положения текущей точки метрики // 17.02.2000
                            // 0 - не отслеживать положение текущей точки метрики
                            // 1 - отслеживать положение текущей точки метрики

 int AreaSeekFlag;          // Флаг поиска по заданной области

 TMapAccess *  MapDoc;      // Указатель на объект класса документа-карты // 05/03/02
 TObjectInfo*  ObjectInfo;  // Выбранный объект карты
 TMapSelect    FindSelect;  // Условия выделения объектов

#ifdef WIN32API  // 29/01/02
 TWindow *
         ApplicationWindow; // Указатель на главное окно приложения,
                            // родитель для создания диалогов
#else
 MSGHANDLER MessageHandler; // Обработчик сообщений
#endif

 int TotalSeekSelect;       // Всего выделено объектов
 int TotalViewSelect;       // Всего отображено объектов

 protected :

 int          SelectFlag;  // Признак выбора объекта карты

 char HelpName[256];       // Имя Help-файла

 DOUBLEPOINT MarkPoint;    // Координаты отмеченной точки
 int IsMarked;             // Признак выделения точки

#ifdef PANPROF
 char TypeName[48];        // Название типа карты
#else
 char TypeName[40];        // Название типа карты
#endif

 COLORREF SelectColor;     // Цвет выделения объектов
                           // 21/02/06 
 int      IsSelectTimer;   // Признак активности таймера выделения объектов

 TObjectInfo  WorkInfo;    // Обрабатываемый объект

 PAINTPARM    SelectImage; // Способ выделения объекта

 IMGDOT       SelectLine;  // Выбран линейный или площадной объект
 IMGOBJECT    SelectPoint; // Выбран точечный объект или подпись

 TObjectInfo  SelectArea;  // Установленная область поиска     19.01.99
 TObjectInfo  AreaShow;

 int          IsAdjustLock; // Признак блокировки обновления карты по таймеру

public :

  // Запросить/Установить толщину выделения объектов на карте

  int GetThickOfSelectObject() { return MKM2PIX(SelectLine.Thick); }
  void SetThickOfSelectObject(int thick)
     { SelectLine.Thick    = PIX2MKM(thick); 
       MapDoc->SelectThick = SelectLine.Thick;          // 07/10/2002
     }

  // Запросить/Установить цвета выделения объектов на карте

  void SetColorOfSelectObject(COLORREF color);

  COLORREF GetColorOfSelectObject()
        { return ColorOfSelectObject; }

  void SetColorOfSelectedObjects(COLORREF color);

  COLORREF GetColorOfSelectedObjects()
        { return ColorOfSelectedObjects; }

  void SetColorOfSetObjects(COLORREF color)  // 04/05/00
        { ColorOfSetObjects = color; }

  COLORREF GetColorOfSetObjects()            // 04/05/00
        { return ColorOfSetObjects; }

  COLORREF  ColorOfSelectObject;    // Цвет выбранного объекта
  COLORREF  ColorOfSelectedObjects; // Цвет выделения объектов
  COLORREF  ColorOfSetObjects;      // Цвет выделения набора объектов  04/05/00

  /************************************************************
  *                                                           *
  *     "Оконный интерфейс для электронной карты"             *
  *                                                           *
  ************************************************************/

  virtual HWND GetHandle() { return 0; }

  HWND GetMainHandle() { return HMainWindow; }

  void GetCursorPos(POINT& pos)
   {
#ifdef WIN32API  // 14/02/02
     ::GetCursorPos(&pos);
#else
    if (MessageHandler)
     MessageHandler(0, MH_GETCURSORPOS, (long int)&pos, 0, 0);   // 04/04/02
#endif
   }

  void SetCursorPos(int x, int y)
   {
#ifdef WIN32API  // 14/02/02
     ::SetCursorPos(x,y);
#else
     if (MessageHandler)
       MessageHandler(0, MH_SETCURSORPOS, x, y, 0);   // 04/04/02
#endif
   }

  RECT GetClientRect();
  void GetClientRect(RECT& rect)
   {
     rect = GetClientRect();
   }

  void ScreenToClient(POINT& point)
   {
     HWND Handle = GetHandle();

     if (Handle)
#ifdef WIN32API  // 14/02/02
       ::ScreenToClient(Handle,&point);
#else
       if (MessageHandler)
         MessageHandler(Handle, MH_SCREENTOCLIENT, (long int)&point, 0, 0);   // 04/04/02
#endif
   }

  void ClientToScreen(POINT& point)
   {

     HWND Handle = GetHandle();
     if (Handle)
#ifdef WIN32API  // 14/02/02
       ::ClientToScreen(Handle,&point);
#else
       if (MessageHandler)
         MessageHandler(Handle, MH_CLIENTTOSCREEN, (long int)&point, 0, 0);   // 04/04/02
#endif
   }

  RECT GetMainClientRect();
  void GetMainClientRect(RECT& rect)
   {
     rect = GetMainClientRect();
   }

  int SendMessage(int msg, intptr_t p1 = 0, intptr_t p2 = 0)
   {

     HWND Handle = GetHandle();

     if (Handle)
#ifdef WIN32API
       return ::SendMessage(Handle,msg,p1,p2);
#else
       if (MessageHandler)
       {
         int ret;

         ret = MessageHandler(Handle, msg, p1, p2, 0);
	 if (!ret) OnMessage(msg, p1, p2, &ret);
	 return ret;  
       }
#endif
     return 0;
   }

  int PostMessage(int msg, intptr_t p1 = 0, intptr_t p2 = 0)
   {

     HWND Handle = GetHandle();

     if (Handle)
#ifdef WIN32API  // 14/02/02
       return ::PostMessage(Handle,msg,p1,p2);
#else
       if (MessageHandler)
         return MessageHandler(Handle, msg, p1, p2, 1);   // 04/04/02
#endif
     return 0;
   }

  // Отправить сообщение главному окну приложения
  int MainMessage(int message,intptr_t wparam,intptr_t lparam = 0)
   {

     HWND Handle = GetMainHandle();

#ifdef WIN32API  // 14/02/02
     if (Handle)
       return ::SendMessage(Handle,message,wparam,lparam);
#else
       if (MessageHandler)
         return MessageHandler(Handle, message, wparam, lparam, 0);   // 04/04/02
#endif
     return 0;
   }

  // Отправить сообщение окну карты
  int MapWindowPort(int command, intptr_t parm = 0);

  void Invalidate(int erase = 0);

  void InvalidateRect(RECT& rect,int erase = 0);

  // Обновить область окна, заданную прямоугольными координатами
  void InvalidateRectPlane(DFRAME * frame,int erase = 0);

  void UpdateWindow(RECT * rect = 0);

  void ScrollBy(int dx, int dy);

  // Ускоренная очистка окна без изменения содержания карты
  // (стереть следы обработчика)
  virtual void Refresh(RECT * rect = 0);
  void RefreshPlane(DFRAME * frame = 0);

  // Ускоренная очистка окна без изменения содержания карты
  // (стереть следы обработчика)
  // по команде PostMessage ("красивый Invalidate")
  void PostRefresh(RECT * rect = 0);
  void PostRefreshPlane(DFRAME * frame = 0);

  // Запросить имя файла документа
  const char * GetDocPath()             // 20/06/02
   { if (MapDoc) return MapDoc->MapDocName;
     else return "";
   }

  // Выбрать имя файла по заданным условиям
  // Возвращает номер строки в списке типов файлов (>=0)
  // При ошибке или отказе от выбора файла -
  // возвращает отрицательное значение
  int OpenFile(char * name, int namesize,
               const char * title, const char * filter,
               int  flags,  int    index,
               const char * path);


 // Обработка произвольного сообщения
 // Если сообщение обработано возвращает не ноль
 virtual int OnMessage(long int msg, long int p1, long int p2, int * retcode)
          { return 0; }

 // Создать таймер                                 // 27/05/02
 void CreateMapTimer(int ident, int period);

 // Удалить таймер
 void DeleteMapTimer(int ident);

 // Перемещение мышки по окну в текущей точке
 virtual int OnMove(UINT modKeys, POINT& point)      // 02/05/06
          { return 0; }

protected :

#ifdef WIN32API  // 29/01/02
 TModule * Resource;          // Модуль ресурсов диалогов
#endif

 char WindowComment[260];     // Имя файла INI для документа

 MAPOBJDESCEX LastSeekObject; // Последний найденный объект

 int Language;                // Код языка сообщений

 TASKPARMEX TaskParm;         // Параметры для вызова задачи

 HWND HMainWindow;            // Идентификатор главного окна приложения

 TMapAction * Navigator;      // Обработчик окна навигации

 int UpdateMode;              // Режим обновления экрана

 RECT RefreshRect;            // Область обновления экрана

 GRIDPARM GridParm;           // Структура параметров прямоугольной сетки
 long int GridActive;         // Признак отображения сетки
 long int GridPoint;          // Признак выбора новых точек в узлах сетки
 double   GridStep;           // Текущий шаг сетки

public:

 long int IsInvalidate;       // Признак принудительного обновления окна
 int IsSizeChanged;           // Признак изменения размеров окна
#ifndef WIN32API
 int TimerSelectFlag;         // Флаг отрисовки выделенных объектов:
                              // 0 - не рисуем повторно в :OnPaint, 1 - рисуем
#endif
 
 struct TCreateObjectParm{ // Параметры для создаваемого объекта
    TCreateObjectParm(): Mode(-1), incode(-1), MapNumber(-1){}
    long int Mode  ;             // Режим создания
                                 // от MED_KEY1 до MED_KEY14
				 // == -1 - объект не создавать
    long int incode;               // Код создаваемого объекта
    long int MapNumber;          // Номер на которой создается объект
 } CreateObjectParm;
 
};

#endif  // MAPWIN_H

