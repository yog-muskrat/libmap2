
#ifndef MTSELFR_H
#define MTSELFR_H

#ifndef MTACTION_H
  #include "mtaction.h"    // TMapAction
#endif

#ifndef MSPARM_H
  #include "msparm.h"
#endif

#define MAXPOINTS           300         

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ КЛАСС "ВЫБОР ФРАГМЕНТА ЭЛЕКТРОННОЙ КАРТЫ" +++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectFrame : public TMapAction
{
 public :

  // Создать объект "выбор фрагмента"
  TMapSelectFrame(TMapTask * task, int ident);

  // Удалить объект "выбор фрагмента"
 ~TMapSelectFrame();

  // Установить фрагмент
  virtual void SetFrame(DOUBLEPOINT* first, DOUBLEPOINT* Second);

  // Построить контур фрагмента по угловым точкам
  virtual void BuildFrame();

  // Нарисовать/Стереть на карте рамку фрагмента
  virtual void PaintFrame();

  // Выполнить прикладную функцию для которой выбрана рамка
  // Вызывается автоматически после выбора второй точки
  // Если код возврата ноль - обработчик завершает работу
  virtual int Run() { return 1;}           

  /************************************************************
  *                                                           *
  *       Методы обработки прикладных событий окна карты      *
  *                                                           *
  ************************************************************/

  // Запрос : можно ли выполнить выбор нового объекта на карте
  virtual int CanSelectObject()  { return 0; }  // НЕЛЬЗЯ !        

  // Указать в строке сообщений действия пользователя
  // MapWindow->SetMessage("...");
  virtual void Comment();
  virtual void CommentSelect(int width, int heigth);

  // Реакция на отпуск левой кнопки мышки
  virtual int LeftUp(UINT /*modKeys*/, TPoint& /*point*/);

  // Перемещение мышки по окну в текущей точке
  virtual int Move(UINT /*modKeys*/, TPoint& /*point*/);

  // Перерисовать на карте рамку фрагмента
  virtual int Paint(TDC& dc, bool erase, TRect& rect);

  // Сообщение об отмене обработки объекта
  virtual int Revert();

 public :

  PAINTPARM Form;   // Вид контура фрагмента на экране
                    // (пунктирная линия 5/2 инверсная)
  PLACEDATA Frame;  // Описание фрагмента карты

  IMGDOT Image;     // Описание пунктирной линии (контур фрагмента)

  struct Border
  {
    DOUBLEPOINT UpLeft;     // Координаты первой точки (Map)
    DOUBLEPOINT UpRight;    // Координаты второй точки
    DOUBLEPOINT DownRight;  // Координаты третьей точки
    DOUBLEPOINT DownLeft;   // Координаты четвертой точки
    DOUBLEPOINT UpLeftLast; // Координаты последней точки (Map)
  }
    Border;

  LONG PointCount;         // Число точек, описывающих фрагмент
  int  SelectedPoints;     // Выбрано точек

  DOUBLEPOINT First;      // Координаты первого угла (Map)
  DOUBLEPOINT Second;     // Координаты второго угла (Map)

  int FlagClear;          // Признак "контур стерт"
};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++ КЛАСС "ВЫБОР ОГРАНИЧЕННОГО ФРАГМЕНТА ЭЛЕКТРОННОЙ КАРТЫ" +++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectFrameLimit : public TMapSelectFrame
{
 public :

  // Создать объект "выбор фрагмента"
  TMapSelectFrameLimit(TMapTask * task, int ident);

  // Построить контур фрагмента по угловым точкам
  void BuildFrame();

  // Построить контур ограничивающего фрагмента по угловым точкам
  void BuildLimit();

  // Нарисовать на карте рамку ограничивающего контура
  void PaintLimit();

  // Установить ограничения размера выбираемого фрагмента
  // place - тип системы координат (например,TMapAccess::MAP)
  // type  - признак ограничения размера выбираемого фрагмента
  // Если type == 0, ограничивающий контур отображается но
  // не влияет на размер выбираемого фрагмента
  void SetFrameLimit(double width, double height,
                     int place, int type);

  /************************************************************
  *                                                           *
  *       Методы обработки прикладных событий окна карты      *
  *                                                           *
  ************************************************************/

  // Перемещение мышки по окну в текущей точке
  virtual int Move(UINT /*modKeys*/, TPoint& /*point*/);

  // Перерисовать на карте рамку фрагмента
  virtual int Paint(TDC& dc, bool erase, TRect& rect);

 protected :

  PAINTPARM LimitForm;   // Вид контура фрагмента на экране
                         // (сплошная линия инверсная)
  PLACEDATA Limit;       // Описание фрагмента карты

  IMGLINE LimitImage;    // Описание линии (контур фрагмента)

  struct LimitBorder
   {
     DOUBLEPOINT UpLeft;     // Координаты первой точки (Picture)
     DOUBLEPOINT UpRight;    // Координаты второй точки
     DOUBLEPOINT DownRight;  // Координаты третьей точки
     DOUBLEPOINT DownLeft;   // Координаты четвертой точки
     DOUBLEPOINT UpLeftLast; // Координаты последней точки (Picture)
   }
     LimitBorder;

  int LimitPlace ;   // Система координат

  enum LIMITTYPE
      {
        SOFT = 0,    // Только отображать контур
        HARD = 1,    // Ограничить выбор размерами контура
      };

  int LimitType  ;   // Способ ограничения SOFT/HARD

  enum LIMITDIRECT
      {
        LD_LEFT  = 1,
        LD_RIGHT = 2,
        LD_UP    = 3,
        LD_DOWN  = 4,
      };

  int LimitDirect;       // Расположение контура

  DOUBLEPOINT LimitSize; // Размеры ограничений выбираемого
                         // фрагмента

  long Scale;            // Масштаб, для которого вычислен контур
};


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++ КЛАСС "ВЫБОР ФИКСИРОВАННОГО ФРАГМЕНТА ЭЛЕКТРОННОЙ КАРТЫ" +++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectFrameFixed : public TMapSelectFrame
{
 public :

  // Создать объект "выбор фрагмента"
  TMapSelectFrameFixed(TMapTask * task, int ident);

  // Построить контур фрагмента по угловым точкам
  void BuildFrame();

  // Перемещение мышки по окну в текущей точке
  int Move(UINT /*modKeys*/, TPoint& /*point*/);

  // Установить ограничения размера выбираемого фрагмента
  void SetFrameLimit(double width, double height, int place);

 protected :

  int LimitPlace ;       // Система координат

  DOUBLEPOINT LimitSize; // Размеры ограничений выбираемого
                         // фрагмента
};


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++   КЛАСС "ВЫБОР ПОВЕРНУТОГО ФИКСИРОВАННОГО ФРАГМЕНТА      +++
// +++                   ЭЛЕКТРОННОЙ КАРТЫ"                     +++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectRotateFixed : public TMapSelectFrame
{
 public :

  // Создать объект "выбор фрагмента"
  TMapSelectRotateFixed(TMapTask * task, int ident);

 ~TMapSelectRotateFixed();

  // Построить контур фрагмента
  virtual void BuildFrame();

  // Нарисовать/Стереть на карте рамку фрагмента
  virtual void PaintFrame();

  // Перерисовать на карте рамку фрагмента
  virtual int Paint(TDC& dc, bool erase, TRect& rect);

  // Установить ограничения размера выбираемого фрагмента
  //  scale - масштаб изображения в диалоге
  void SetFrameLimit(double width, double height, int place, int scale);

  // Выполнить самоликвидацию (вызов деструктора) из диалога
  void Quit() { TMapAction::Quit(); }                   

 protected :

  PLACEDATA Vector;      // Описание вектора
  PAINTPARM VectorForm;  // Вид контура вектора на экране
                         // (сплошная линия инверсная)
  IMGLINE   VectorImage; // Описание линии (контур фрагмента)

  DOUBLEPOINT LimitSize; // Размеры ограничений выбираемого
                         // фрагмента

  DOUBLEPOINT Points[5];     // Метрика вектора (стрелки ->)
  LONG VectorPointCount[2];  // Число точек в подобъектах

  int LimitPlace;        // Система координат
  int Scale;             // Масштаб изображения в диалоге
};


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++ КЛАСС "ВЫБОР ФИКСИРОВАННОГО ФРАГМЕНТА ЭЛЕКТРОННОЙ КАРТЫ  +++
// +++             ПО ЦЕНТРАЛЬНОЙ ТОЧКЕ ФРАГМЕНТА"              +++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectCenterFixed : public TMapSelectFrame
{
 public :

  // Создать объект "выбор фрагмента"
  TMapSelectCenterFixed(TMapTask * task, int ident);

  // Реакция на отпуск левой кнопки мышки
  virtual int LeftUp(UINT /*modKeys*/, TPoint& /*point*/);

  // Построить контур фрагмента
  void BuildFrame();

  // Установить ограничения размера выбираемого фрагмента
  void SetFrameLimit(double width, double height, int place);

 protected :

  int LimitPlace ;       // Система координат

  DOUBLEPOINT LimitSize; // Размеры ограничений выбираемого
                         // фрагмента
};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ КЛАСС "ВЫБОР ФРАГМЕНТА ЭЛЕКТРОННОЙ КАРТЫ" +++++++
// +++++++ (с вызовом диалога обработки изображения) +++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectFrameAndChange : public TMapSelectFrame
{
 public :

  TMapSelectFrameAndChange(TMapTask * task, int ident);

  // Удалить объект          
 ~TMapSelectFrameAndChange();

  // Выполняется при инициализации класса
  virtual void Setup() { Run(); }

  // Вызвать диалог
  virtual int CallDialog() { return 0; }

  // Выполняется при закрытии класса
  virtual int CanClose() { return (DialogActive == 0); }

  // Можно ли выполнить выбор объекта на карте
  virtual int CanSelectObject();

  // Можно ли выполнить выбор этого объекта
  virtual int CanSelectThisObject(TObjectInfo* info);

  // Сохранить номер и имя листа выбранного объекта
  virtual void SetSelectObject(TObjectInfo* info) {}

  // Сообщение о завершении обработки объекта
  virtual int Commit();

  // Нажата клавиша
  virtual int KeyDown(UINT /*key*/, UINT /*repeatCount*/, UINT /*flags*/);

  // Реакция на нажатие левой кнопки мышки
  virtual int LeftDown(UINT /*modKeys*/, TPoint& /*point*/);

  // Реакция на отпуск левой кнопки мышки
  virtual int LeftUp(UINT /*modKeys*/, TPoint& /*point*/);

  // Перемещение мышки по окну в текущей точке
  virtual int Move(UINT /*modKeys*/, TPoint& /*point*/);

  // Сообщение об отмене обработки объекта
  virtual int Revert();

  // Выполняется после выбора границ фрагмента автоматически
  // Вызывает CallDialog
  virtual int Run();

  //  Установить область по объекту карты
  virtual int SelectObject(TObjectInfo* info);          

  // Перемещение рамки по окну
  void MoveFrame();

 public :

  int ChangeFlag;  // Флаг режима:
                   //  0 - режим выбора фрагмента
                   //  1 - режим изменения границ выбранной области
  int ChangeLeft;
  int ChangeUp;
  int ChangeRight;
  int ChangeDown;
  int ChangePos;

  int MapCursor;
  int DialogActive;

  DOUBLEPOINT BeginPos;  // Точка начальной позиции рамки при перемещении
  RECT* RectMetr;
  char* Regime;

  DFRAME PlaneFrame;  // Выбранная область в метрах
};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ КЛАСС "ВЫБОР ТОЧЕК ЭЛЕКТРОННОЙ КАРТЫ" +++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectPoints : public TMapSelectFrame
{
 public :

  // Создать объект "выбор точек"
  TMapSelectPoints(TMapTask * task, int ident);

  // Удалить объект "выбор точек"
 ~TMapSelectPoints();

  // Выполнить прикладную функцию для которой выбраны точки
  // Вызывается автоматически после выбора последней точки точки
  // Если код возврата ноль - обработчик завершает работу
  virtual int Run() { return 0; }

  /************************************************************
  *                                                           *
  *       Методы обработки прикладных событий окна карты      *
  *                                                           *
  ************************************************************/

  // Указать в строке сообщений действия пользователя
  virtual void Comment();
  virtual void CommentSelect(int count, int value = 0);

  // Реакция на нажатие правой кнопки мышки
  virtual int RightDown(UINT /*modKeys*/, TPoint& /*point*/);

  // Реакция на отжатие правой кнопки мышки
  virtual int RightUp(UINT /*modKeys*/, TPoint& /*point*/);

  // Реакция на отжатие левой кнопки мышки
  virtual int LeftUp(UINT /*modKeys*/, TPoint& /*point*/);

  // Перемещение мышки по окну в текущей точке
  virtual int Move(UINT /*modKeys*/, TPoint& /*point*/);

  // Сообщение об отмене обработки объекта
  virtual int Revert();

 public :

  int ChoiceFlag;                  // 0 - выбор фрагмента, 1 - выбор точек
  long PointsCount;                // Число необходимых точек
  int  SelectPoints;               // Выбрано точек
  DOUBLEPOINT  Fact[MAXPOINTS];    // Фактические координаты в метрах
};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++ КЛАСС "ВЫБОР ПЛОЩАДИ ЭЛЕКТРОННОЙ КАРТЫ" ++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectSquare : public TMapAction
{
 public :

  // Создать объект "выбор точек"
  TMapSelectSquare(TMapTask * task, int ident);

  // Удалить объект "выбор точек"
 ~TMapSelectSquare();

  // Выполнить прикладную функцию для которой выбрана площадь
  // Вызывается автоматически после выбора последней точки точки
  // Если код возврата ноль - обработчик завершает работу
  virtual int Run() { return 0; }

  /************************************************************
  *                                                           *
  *       Методы обработки прикладных событий окна карты      *
  *                                                           *
  ************************************************************/

  // Запрос : можно ли выполнить выбор нового объекта на карте
  int CanSelectObject()  { return 0; }  // НЕЛЬЗЯ !

  // Указать в строке сообщений действия пользователя
  virtual void Comment();

  // Сообщение о завершении обработки точки
  virtual int Commit();

  // Нажата клавиша
  virtual int KeyDown(UINT key, UINT /*repeatCount*/, UINT /*flags*/);

  // Реакция на отжатие левой кнопки мышки
  virtual int LeftUp(UINT /*modKeys*/, TPoint& /*point*/);

  // Реакция на отжатие правой кнопки мышки
  virtual int RightUp(UINT /*modKeys*/, TPoint& /*point*/);

  // Перемещение мышки по окну в текущей точке
  virtual int Move(UINT /*modKeys*/, TPoint& /*point*/);

  // Перерисовать на карте контур площади
  virtual int Paint(TDC& dc, bool erase, TRect& rect);

  // Сообщение об отмене обработки объекта
  virtual int Revert();

  // Автоскроллинг
  int AutoScrolling(DOUBLEPOINT* viewpoint);

  // Добавить точку
  int AppendPoint();

  // Удалить последнюю точку
  int DeleteLastPoint();

 public :

  TDataEdit Square;
  PLACEDATA SquareData;
  LONG      SquareCounts;

  DOUBLEPOINT LinePoints[3];
  PLACEDATA   LineData;
  LONG        LineCounts;

  PAINTPARM Form;       // Вид контура площади на экране
                        // (пунктирная линия 5/2 инверсная)
  IMGDOT Image;         // Описание пунктирной линии
};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ КЛАСС "ВЫБОР ФРАГМЕНТА ЭЛЕКТРОННОЙ КАРТЫ" +++++++
// +++++++ (с вызовом диалога обработки изображения) +++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectFrameChangeAndRotate :
             public TMapSelectFrame
{
 public :

  // Режимы работы с рамкой
  enum REGIMETYPE
      {
        RECTCHANGESIDE = 1,  // Изменять размеры контура (по одной стороне)
        RECTCHANGE     = 2,  // Изменять размеры контура (по двум стронам)
        RECTMOVE       = 3,  // Перемещать контур
        ROTATE         = 4   // Вращать контур
      };


  //  Конструктор
  //  frame - начальный размер фрагмента (в метрах)
  //          при frame = 0, фрагмент задается пользователем
  //          на экране
  //  secondpoint - признак автоматического расчета второй точки
  //                резинового контура по габаритам рамки (frame)
  TMapSelectFrameChangeAndRotate(TMapTask *task, int ident,
                                 DFRAME *frame = 0, int secondpoint = 0);
  ~TMapSelectFrameChangeAndRotate();

  // Построить рамку
  int BuildFrameUnique();

  //  Сообщение о завершении обработки объекта
  virtual int Commit();

  // Реакция на нажатие левой кнопки мышки
  virtual int LeftDown(UINT /*modKeys*/, TPoint& /*point*/);

  // Перемещение мышки по окну в текущей точке
  virtual int Move(UINT modKeys, TPoint& point);

  // Реакция на отпуск левой кнопки мышки
  virtual int LeftUp(UINT /*modKeys*/, TPoint& /*point*/);

  // Задать центр поворота или точку привязки (в дискретах)
  int SetStationaryPoint(DOUBLEPOINT *point = 0);

  // Сместить DimBorder и выполнить операцию
  int OffsetDimBorderAndRun(double dx, double dy);

  // Расширить DimBorder и выполнить операцию
  int ExtendDimBorderAndRun(double dx, double dy);

  // Повернуть со смещением: угол поворота (в радианах) и
  //                         расстояние(в дискретах)
  // и выполнить операцию
  int RotateAndOffsetAndRun(double corner = 0, double distance = 0);

  virtual int Run(int view = 1) { return 0; }

 protected :

  // Инициализировать переменные класса
  void InitData(DFRAME *frame = 0, int secondpoint = 0);

  //  Инициализировать габариты рамки
  void InitBorder();

  // Отловить положение мышки на контуре
  void MousePlace(int *side, int *corner, int *regime);

  // Изменить размер контура по стороне
  int ChangeSide(int side);

  // Изменить размер контура по углу
  int ChangeCorner(double corner = 0);

  // Изменить расположение фишек
  void ChangeFish();

  // Посчитать габариты фрагмента в метрах
  void ChangePlaneFrame();

  //  Нарисовать на карте рамку фрагмента
  virtual int Paint(TDC& dc, bool erase, TRect& rect);

  // Нарисовать маркер на контуре
  virtual void PaintFrame();

  // Нарисовать фишки
  void PaintFish(TDC *dc = 0, TRect *rect = 0);

  // Нарисовать точку привязки или центр поворота
  void PaintStationaryPoint(TDC *dc = 0, TRect *rect = 0);

  // Сообщение об отмене обработки объекта
  virtual int Revert();

 public :

 DOUBLEPOINT TotalMove;      // Cдвиг фрагмента
 double      TotalCorner;    // Yгол поворота фрагмента
 DFRAME      PlaneFrame;     // Габариты (в метрах)
 DFRAME      ViewPlaneFrame; // Габариты с фишками (в метрах)

 DOUBLEPOINT StationaryPoint; // Точка привязки (она же центр поворота)

 protected :

 DOUBLEPOINT DownPoint;  // Координаты точки нажатия (Map)
 DOUBLEPOINT UpPoint;    // Координаты точки отжатия

 PAINTPARM FormFish;     // Вид контура фрагмента на экране (фишка)
 PLACEDATA FrameFish;    // Описание фрагмента карты
 IMGLINE   ImageFish1;   // Описание 1 фишки
 IMGLINE   ImageFish;    // Описание фишки

 PLACEDATA FrameStationary;  // Описание фрагмента карты
 LONG PointCountStationary;

 struct BorderFish
    {
    DOUBLEPOINT UpLeft;     // Координаты первой точки (Map)
    DOUBLEPOINT UpRight;    // Координаты второй точки
    DOUBLEPOINT DownRight;  // Координаты третьей точки
    DOUBLEPOINT DownLeft;   // Координаты четвертой точки
    DOUBLEPOINT UpLeftLast; // Координаты последней точки (Map)
    };

 // Текущие координаты захвата рамки (слева сверху направо вниз)
 DOUBLEPOINT DimBorder[8];

 int IsStationaryPoint;       // Флажок установки центра поворота
 int IsCornerStationary;      // Флажок установки угла поворота
 double CornerStationary;     // Стационарный угол поворота

// Координаты фишек в пикселах (слева сверху направо вниз)
 BorderFish Fish[8];

 // Координаты точки привязки в пикселах
 DOUBLEPOINT FishStationary[4];

 double Precision;

 DFRAME Frame;      // Исходная рамка, если есть (в метрах)

 int Regime;        // Режим работы с рамкой
 int CommitFlag;    // Флаг выполнения операций ввода
                    // (для повторения режима)

 int CornerNumber;  // Номер выбранного угла (слева сверху направо вниз)
 int SideNumber;    // Номер выбранной стороны (верх право лево низ)
 int Change;        // Изменить фрагмент

 int IsSecond;      // Флаг для автоматического рассчета второй
                    // точки резинового контура по габаритам рамки

};
/*  

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ КЛАСС "ВЫБОР ФРАГМЕНТА ЭЛЕКТРОННОЙ КАРТЫ" +++++++
// +++++++ (с вызовом диалога обработки изображения) +++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectFrameSizeable : public TMapSelectFrameAndChange
{
 public :

  //  Конструктор
  //  frame - начальный размер фрагмента (пикселях в районе)
  TMapSelectFrameSizeable(TMapTask * task, int ident);

  // Удалить объект          
 ~TMapSelectFrameSizeable();

  //  Указать в строке сообщений действия пользователя  
  void Comment();

  // Сообщение о завершении обработки объекта
  int Commit();

  // Реакция на отпуск левой кнопки мышки
  int LeftUp(UINT , TPoint&);

  // Перемещение мышки по окну в текущей точке
  int Move(UINT, TPoint& );

  int Run() { return 1; }

  // Нарисовать/Стереть на карте рамку фрагмента
  void PaintFrame();

  //  Нарисовать на карте рамку фрагмента
  int Paint(TDC& dc, bool erase, TRect& rect);

  char RegimeOle;  
};
*/

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++ КЛАСС "ВЫБОР НАКЛОННОГО ФРАГМЕНТА ЭЛЕКТРОННОЙ КАРТЫ" +++
// +++  или  "ВЫБОР ПРЯМОГО ФРАГМЕНТА ЭЛЕКТРОННОЙ КАРТЫ"    +++
// +++    (с вызовом диалога обработки изображения)         +++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectFrameTurn : public TMapSelectFrameAndChange
{
  public :

  TMapSelectFrameTurn(TMapTask *task, int ident);

  virtual int Run();

  public :

  DFRAME SavePlaneFrame;
  DOUBLEPOINT Third;     // Третья точка
  double Angle;          // Угол поворота фрагмента (в радианах)
  char TurnFrame;
  char SaveTurnFrame;

  // Деление на страницы

  PAINTPARM PageForm;         // Вид контура фрагмента на экране
                              // (пунктирная линия 2/2 инверсная)

  IMGDOT      PageImage;      // Описание пунктирной линии (контур фрагмента)

  PLACEDATA   PageFrame;      // Описание метрики линии
  DOUBLEPOINT PageLine[2];
  LONG        PagePointCount; // Число точек, описывающих фрагмент

  double      PageWidth;      // Размер страницы в миллиметрах
  double      PageHeight;

  double      PrintScale;     // Масштаб печати

  protected:

  // Построить контур фрагмента по угловым точкам
  virtual void BuildFrame();

  virtual void PaintFrame();
  virtual int  Paint(TDC& dc, bool, TRect& rect);

  // Реакция на отпуск левой кнопки мышки
  virtual int LeftUp(UINT modKeys, TPoint& point);

  // Перемещение мышки по окну в текущей точке
  virtual int Move(UINT mode, TPoint& point);

  // Сообщение о завершении обработки объекта
  virtual int Commit();

  // Нажата клавиша
  virtual int KeyDown(UINT key, UINT repeatCount, UINT flags);
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++ КЛАСС "ВЫБОР ФРАГМЕНТА И ПЛОЩАДИ" ++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectFrameAndSquare : public TMapSelectFrameAndChange
{
 public :

  // Создать объект
  TMapSelectFrameAndSquare(TMapTask * task, int ident);

  // Удалить объект
 ~TMapSelectFrameAndSquare();

  // Выполнить прикладную функцию для которой выбран фрагмент
  // Вызывается автоматически после выбора последней точки
  // Если код возврата ноль - обработчик завершает работу
  virtual int Run();

  /************************************************************
  *                                                           *
  *       Методы обработки прикладных событий окна карты      *
  *                                                           *
  ************************************************************/

  // Можно ли выполнить выбор объекта на карте
  virtual int CanSelectObject()
  {
   if (Regime && *Regime == AREA_SELECT_OBJECT)
     return 1;
   else
     return 0;
  }

  // Указать в строке сообщений действия пользователя
  virtual void Comment();

  // Сообщение о завершении обработки точки
  virtual int Commit();

  // Нажата клавиша
  virtual int KeyDown(UINT key, UINT /*repeatCount*/, UINT /*flags*/);

  // Реакция на отжатие левой кнопки мышки
  virtual int LeftUp(UINT /*modKeys*/, TPoint& /*point*/);

  // Реакция на отжатие правой кнопки мышки
  virtual int RightUp(UINT /*modKeys*/, TPoint& /*point*/);

  // Перемещение мышки по окну в текущей точке
  virtual int Move(UINT /*modKeys*/, TPoint& /*point*/);

  // Перерисовать на карте контур площади
  virtual int Paint(TDC& dc, bool erase, TRect& rect);

  virtual void PaintFrame();

  // Сообщение об отмене обработки объекта
  virtual int Revert();

  // Автоскроллинг
  int AutoScrolling(DOUBLEPOINT* viewpoint);

  // Добавить точку
  int AppendPoint();

  // Удалить последнюю точку
  int DeleteLastPoint();

 public :

  TDataEdit Square;
  HOBJ      SquareHOBJ;
  PLACEDATA SquareData;
  LONG      SquareCounts;

  DOUBLEPOINT LinePoints[3];
  PLACEDATA   LineData;
  LONG        LineCounts;

  PAINTPARM Form;       // Вид контура площади на экране
                        // (пунктирная линия 5/2 инверсная)
  IMGDOT Image;         // Описание пунктирной линии

  int FlagEscape;
};

#endif
