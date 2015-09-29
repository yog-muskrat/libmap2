
#ifndef MTACTION_H
#define MTACTION_H

#ifndef MTMAPTAS_H
  #include "mtmaptas.h"    // TMapTask
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ КЛАСС "ОБРАБОТКА КОМАНДЫ УПРАВЛЕНИЯ" ++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapAction
{
  public :

  // Создать объект "обработчик команды"
  // Если обработчик должен начать работу с диалога,
  // то диалог должен создаваться в Setup() ...
  TMapAction(TMapTask * task,int ident)
     {
       ActionTask  = task;
       ActionIdent = ident;
       MapWindow   = task->GetMapWindow();
       MapDoc      = MapWindow->MapDoc;
     }

  // Удалить обработчик и освободить все ресурсы !!!
  // Результаты работы здесь не сохраняются
  virtual ~TMapAction(){
     MapWindow->SetWindowTitle(0); // Вернем заголовок главного окна
     MapWindow->SetMessage(0);     // Вернем текст в статус строке
  }

  // Выполнить настройку обработчика
  // Вызывается после вызова конструктора
  virtual void Setup() { Comment(); }

  // Запросить способ выбора объекта
  // Без диалога - не ноль, иначе - ноль
  virtual int GetSelectObjectType() { return 1; }

  // Установить адрес обработчика в задаче
  // Вызывается автоматически после конструктора
  virtual void SetTaskAction() { if (Task()) Task()->Action = this; }

  // Удалить адрес обработчика в задаче
  // Вызывается автоматически
  virtual void ClearTaskAction() { if (Task()) Task()->Action = 0; }

 /************************************************************
 *                                                           *
 *         Методы управления обработчиком команд             *
 *                                                           *
 ************************************************************/

public :

  // Запрос справки о текущем режиме работы (F1)
  virtual int CallHelp()
    { if (ActionTask) ActionTask->CallHelp(Ident()); return 1;}

  // Запросить : можно ли отключить обработчик команды
  // Если разрешено - будет вызван деструктор обработчика
  // Перед выдачей разрешения можно сохранить результаты
  // работы обработчика ...
  // Задача может удалить обработчик и не вызывая CanClose() !
  virtual int CanClose() { return 1; }

  // Запросить : можно ли перезапустить обработчик
  // при повторном нажатии кнопки
  // Если не разрешено - будет
  // выполняться закрытие обработчика (CanClose() ...)
  virtual int CanRestartByButton() { return 0; }

  // Запросить идентификатор обрабатываемой команды
  int Ident() { return ActionIdent; }

  // Запрос - это сервисный обработчик ?
  virtual int IsService() { return 0; }

  // Извещение о том, что обработчик будет завершен
  // в результате повторного нажатия его кнопки
  // Вызывается, если разрешил CanClose()
  // Применяется для обеспечения перезапуска обработчика (Restart())
  virtual void CancelNotify() {}

  // Извещение о том, что операция над объектом завершена
  // Функция может вызываться после выполнения Commit() до
  // перехода к следующему объекту 
  virtual void CommitNotify(TObjectInfo * /*info*/) {}

  // Запросить задачу, которой принадлежит обработчик
  TMapTask * Task() { return ActionTask; }

protected :

  // Выполнить самоликвидацию (вызов деструктора)
  // с сохранением результатов работы ...
  // CanClose() вызывается !
  void Close()
    { if (ActionTask) ActionTask->CloseAction(Ident()); }

  // Выполнить самоликвидацию (вызов деструктора)
  // без сохранения результатов работы
  // CanClose() не будет вызываться !
  // После этой функции нельзя использовать
  // переменные класса, его уже нет !!!
  void Quit()
    { if (ActionTask) ActionTask->DestroyAction(Ident()); }

  // Выполнить "перезагрузку" обработчика
  // (вызов деструктора и затем конструктора)
  // без сохранения результатов работы
  // CanClose() не будет вызываться !
  void Restart()
    { if (ActionTask) ActionTask->RestartAction(Ident()); }

 /************************************************************
 *                                                           *
 *       Справочные данные об окне карты и приложении        *
 *                                                           *
 ************************************************************/

public :

  // Запросить координаты верхнего левого угла окна
  // в логической системе карты (Map) в дискретах
  DOUBLEPOINT * GetMapWindowPoint()
     {
       return MapWindow->GetMapWindowPoint();
     }

  // Запросить идентификатор окна карты
  HWND GetMapWindowHandle() { return MapWindow->GetHandle(); }

  // Запросить размеры клиентной области окна карты
  RECT GetMapWindowClientRect()
   {
     return MapWindow->GetClientRect();
   }

 /************************************************************
 *                                                           *
 *       Методы обработки прикладных событий окна карты      *
 *                                                           *
 ************************************************************/

public :

 // Извещение об изменении содержания данных
 // (карт, растров, матриц ...)
 // Если активен обработчик - проверить,
 // что он не работает c закрытыми данными !
 virtual void ChangeData() {}

 // Запрос : можно ли выполнить выбор нового объекта
 // на карте для обработки
 // Обработчик карты выполнит выбор объекта в точке нажатия
 // левой кнопки мышки,
 // если CanSelectObject() возвращает ненулевое значение
 virtual int CanSelectObject()  { return 1; }

 // Запрос : можно ли выполнить выбор данного объекта
 // на карте для обработки
 // Может вызываться до выполнения Setup() !
 // Например: можно ли удалить данный объект и т.п.
 virtual int CanSelectThisObject(TObjectInfo * )  { return 1; }

 // Запрос : можно ли выполнить сборку группы
 // для данного объекта карты
 // Запрет применяется только для отдельных операций
 // над составом группы !
 virtual int CanUnionGroupData(TObjectInfo * )  { return 1; }

 // Сообщение о завершении обработки объекта
 virtual int Commit() { return 0; }

 // Извещение : активизирован объект (между CanSelectThisObject()
 // и SelectObject()). Позволяет перебирать объекты с одного
 // нажатия кнопкой мышки. Для программного перехода к следующему/предыдущему
 // объекту применяется MapWindow->NextActiveObject() и
 // MapWindow->PrevActiveObject().
 // Обработчик может накапливать выбранные объекты
 // для совместной обработки :
 // TObjectInfo * Target = new TObjectInfo(info);
 virtual int ActiveObject(TObjectInfo * ) { return 0; }

 // Извещение : выполнен выбор объекта (двойным нажатием, Ctrl+Left,...)
 // Обработчик может накапливать выбранные объекты
 // для совместной обработки :
 // TObjectInfo * Target = new TObjectInfo(info);
 virtual int SelectObject(TObjectInfo * ) { return 0; }

 // Сообщение об отмене обработки объекта
 // Выполняется отключение обработчика !
 virtual int Revert() { return 0; }

 /************************************************************
 *                                                           *
 *       Методы обработки системных событий окна карты       *
 *     Если событие не обрабатывается и может быть передано  *
 *        обработчику окна карты  - возвращается 0           *
 *                                                           *
 ************************************************************/

 typedef POINT TPoint;

 typedef struct TRect : public RECT
 {
   int Width()  { return (RT - LT); }
   int Height() { return (DN - UP); }
 }
  TRect;

 typedef TRect TRECT;

 typedef struct TDC
 {
   TDC(HDC handle)  { Handle = handle; }

   HDC GetHandle() { return Handle; }
   operator HDC()  { return Handle; }
   HDC operator = (HDC handle) { return (Handle = handle); }

   HDC Handle;
 }
   TDC;

 typedef TDC THDC;

 typedef struct TMenu
 {
   TMenu(HMENU handle)  
   { 
     Handle = handle; 
#ifdef LINUXAPI                    
     if (handle == 0)
     {
       CountItem = 0;
       memset((char *)&MenuTable[0], 0, sizeof(MenuTable));
     }
#endif
   }


   int AppendMenu(UINT flags,UINT item,const char * name)
   { 
#ifdef WIN32API           
     return ::AppendMenu(Handle, flags, item, name); 
#else
     { 
        if (CountItem > 63) return 0;
	
	MenuTable[CountItem].IdItem   = item;
        if (item == 0) 
	{
          CountItem = CountItem + 1;
	  return 1;
	}
	if (name)
          strncpy(MenuTable[CountItem].NameItem, name, 
	          sizeof(MENUSTRINGTABLE));
	MenuTable[CountItem].Enable   = flags;
	CountItem = CountItem + 1;
	
        return 1; 
     }
#endif
   }

#ifdef WIN32API
   int CheckMenuItem(int item, int state = MF_CHECKED)   
      { return ::CheckMenuItem(Handle, item, state);    }
#endif

   HMENU GetHandle() { return Handle; }
   operator HMENU()  { return Handle; }
   HMENU operator = (HMENU handle) { return (Handle = handle); }

   HMENU Handle;
#ifdef LINUXAPI                    
   MENUSTRINGTABLE MenuTable[64];
   int             CountItem;
#endif
 }
   TMenu;

 typedef TMenu TMENU;

 // Запросить - реагирует ли обработчик на клавишу Shift
 // Если да, то перемещение экрана мышкой при нажатом Shift блокируется
 virtual int IsShiftUsed() { return 0;}              

 // Запросить - реагирует ли обработчик на клавишу Tab
 // Если да, то перемещение экрана мышкой при нажатии Tab блокируется
 virtual int IsTabUsed() { return 0;}              

 // Нажата клавиша
 virtual int KeyDown(UINT /*key*/, UINT /*repeatCount*/, UINT /*flags*/)
                                    { return 0; }
 // Управление "мышью"
 // Нажата левая кнопка в текущей точке
 virtual int LeftDown(UINT /*modKeys*/, POINT& /*point*/)
                                    { return 0; }
 // Отпущена левая кнопка в текущей точке
 virtual int LeftUp(UINT /*modKeys*/, POINT& /*point*/)
                                    { return 0; }
 // Перемещение мышки по окну в текущей точке
 virtual int Move(UINT /*modKeys*/, POINT& /*point*/)
                                    { return 0; }

 // Нажата правая кнопка в текущей точке
 // Если возвращает ненулевое значение -
 // всплывающее меню блокируется (не всплывает !)
 // Может применятся, когда правая кнопка нажимается
 // вместе с клавишами ALT,CNTRL и т.п.
 virtual int RightDown(UINT /*modKeys*/, POINT& /*point*/)
                                    { return 0; }

 // Нажата правая кнопка в текущей точке
 virtual int RightUp(UINT /*modKeys*/, POINT& /*point*/)
                                    { return 0; }

 // Добавить пункты меню для текущей операции
 // Всплывающее меню при нажатии правой кнопки мышки
 int CallPopupMenu(HMENU hmenu)
#ifdef WIN32API                        
    { TMENU Tmenu(hmenu); return CallRightMenu(&Tmenu); }
#else
    { return CallRightMenu((TMENU *)hmenu); }
#endif
 virtual int CallRightMenu(TMENU * /*Menu*/)
                                    { return 0; }

 // Управление "отображением"
 // Обработчик может нарисовать "под картой"
 int BeforePaint(HDC dc, RECT& rect)
  { THDC Thdc(dc); return BeforePaint(Thdc, (TRECT&)rect); }

 virtual int BeforePaint(THDC& dc, TRECT& rect) { return 0; }

 // Управление "отображением"
 // Обработчик может нарисовать "на карте"
 // (карта уже нарисована ...)
 int Paint(HDC dc, bool erase, RECT& rect)
  { THDC Thdc(dc); return Paint(Thdc,erase,(TRECT&)rect); }
 virtual int Paint(THDC& dc, bool erase, TRECT& rect)
                                    { return 0; }

 // Запрос на перевывод комментария текущей операции обработчика
 // (Вызывается автоматически после выполнения Setup(),
 // при получении фокуса и изменении кода языка)
 // Обработчик может выполнить MapWindow->SetMessage(....);
 virtual void ResetMessage() { Comment(); }
 virtual void Comment() {}  // Синоним ResetMessage()

 // Сообщение о том, что обработчик может выполнить фоновый процесс
 virtual void IdleAction(long count) {}

 /************************************************************
 *                                                           *
 *         Запрос координат текущей точки при обработке      *
 *                  событий окна карты                       *
 *                                                           *
 ************************************************************/

  // Запросить координаты в системе изображения (Picture)
  // Координаты текущей точки в пикселах
  POINT * GetPicturePoint() { return &(MapWindow->PicturePoint);}

  // Запросить координаты в логической системе карты (Map)
  // Координаты текущей точки в дискретах
  DOUBLEPOINT * GetMapPoint() { return &(MapWindow->MapPoint);}

  // Запросить координаты в прямоугольной местной системе (Plane)
  // Координаты текущей точки в метрах
  DOUBLEPOINT * GetPlanePoint() { return &(MapWindow->PlanePoint);}

  // Запросить координаты в географической системе (Geo)
  // Координаты текущей точки в радианах
  // Если географическая система координат не поддерживается
  // значение координат всегда ноль !
  // Проверка поддержки географических координат
  DOUBLEPOINT * GetGeoPoint() { return MapWindow->GetGeoPoint();}

  // Проверка поддержки географических координат
  // Если не поддерживаются - возвращает ноль
  int IsGeoSupported()
     { return MapDoc->IsGeoSupported(); }

protected :

 TMapTask * ActionTask;  // Указатель на задачу,которой принадлежит
                         // обработчик команды
 int ActionIdent;        // Идентификатор обработчика команд

 TMapWindow * MapWindow; // Окно обрабатываемой карты

 TMapAccess * MapDoc;    // Документ - "электронная карта"
};

#endif

