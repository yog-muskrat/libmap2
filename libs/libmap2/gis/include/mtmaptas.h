
#ifndef MTMAPTAS_H
#define MTMAPTAS_H

#ifndef MWMAPWIN_H
 #include "mwmapwin.h"
#endif

#define KD_CNTRL  2

// Флаг активного модального диалога в системе          
// Для предотвращения запуска второго модального диалога из "висячих" панелей
extern int IsDialogActive;  

class _DLLCLASSTASK TMapAction;   // см. MTaction.h

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ КЛАСС "УПРАВЛЕНИЕ ПРИКЛАДНОЙ ЗАДАЧЕЙ" +++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapTask
{
 public :

  TMapTask(TMapWindow * window);

  virtual ~TMapTask() {}

  // Принудительное завершение работы задачи
  // через ::PostMessage(...)
  void Quit();

  /************************************************************
  *                                                           *
  *   Функции подключения/отключения обработчиков команд      *
  *   ----------------------------------------------------    *
  *      Некоторые команды могут выполняться задачей          *
  *  без назначения обработчика (управление состоянием ...)   *
  *       (см. MTmaptas.cpp)                                  *
  *                                                           *
  ************************************************************/

  typedef struct TCommandEnabler
  {
    TCommandEnabler(int id)
      { enable = 0; check = -1; Id = id; text[0] = 0; }

    void Enable(int flag) { enable = flag && 1; }
    int  Enable() { return enable; }
    void SetCheck(int flag = 0) { check = flag && 1; }
    int  Check() { return check; }
    int  Ident() { return Id; }
    char * SetText(const char * newtext)
      { if (newtext) strcpy(text,newtext); else text[0] = 0; 
        return text;}
    char * Text() { return text; }

    int Id;
    int enable;
    int check;
    char text[256];
  }
   TCommandEnabler;

  // Запросить описание команды
  virtual void CallHelp(int comid) { GetAction(comid,-1); }

  // Запросить описание команды
  virtual void ViewHelp(int topic)
        { if (MapWindow) MapWindow->ViewHelp(topic); }

  // Отключить обработчик команды
  // (он может отказаться при CanClose())
  virtual void CloseAction(int comid);

  // Отключить обработчик команды принудительно
  virtual void DestroyAction(int comid = 0);

  // Найти обработчик команды и активизировать (если run != 0)
  // Список команд и обработчиков располагается
  // в функции GetAction() ! (см. MTmaptas.cpp)
  // Если команда не поддерживается задачей -
  // возвращает ноль
  virtual TMapAction * GetAction(int comid, int run = 1);

  // Запросить обрабатывается ли указанная команда в данной задаче
  // Если нет - возвращает ноль
  int EnableAction(TCommandEnabler& ce)
    { return EnableAction(ce.Ident(),ce); }
  virtual int EnableAction(int comid,TCommandEnabler& ce);

  // Обработка оконных сообщений в задаче
  // Если сообщение не обработано - возвращает ноль
  virtual int PrepareMessage(int /*message*/, WPARAM /*wparam*/,
                             LPARAM /*lparam*/, int * /*retcode*/)
                                { return 0; }

  // Запросить поддерживает ли задача работу
  // с несколькими окнами документов
  // Если нет - возвращает ноль
  virtual int IsMultiDocTask() { return 1; }

  // Перезапуск обработчика команды
  virtual void RestartAction(int comid);

  // Окно документа получило фокус ввода
  virtual void SetFocus(HWND hwnd) {};

  /************************************************************
  *                                                           *
  *           Функции создания панелей пиктограмм             *
  *                                                           *
  ************************************************************/

  // Создать стандартную панель инструментов задачи
  // panel - номер панели (см. userapi.h)
  virtual int CreateTaskPanel(int panel = 1) { return 0;};

  // Создать пустую панель инструментов
  // hInst   - идентификатор модуля содержащего ресурсы кнопок
  // name    - заголовок панели
  // panelId - желаемый идентификатор панели или 0, если хотите,
  //           чтобы система выделила его сама
  // Возвращает: идентификатор созданной панели может не совпадать с
  //             panelId, если такой идентификатор не свободен
  int CreatePanel(HINSTANCE hInst, const char* name, int panelId = 0);

  // Добавить/вставить кнопку в панель
  // panelID  - идентификатор панели
  // bmpFace  - идентификатор изображения кнопки в ресурсах
  // command  - идентификатор кнопки, если 0 - разделитель
  // after    - идентификатор существующей кнопки, после которой
  //            вставляется кнопка, если 0 - в конец панели
  int InsertButton(int panelID, intptr_t bmpFace, int command, int after = 0);

  // Добавить/вставить кнопку в панель
  // panelID  - идентификатор панели
  // bmpFace  - идентификатор изображения кнопки в ресурсах
  // command  - идентификатор кнопки, если 0 - разделитель
  // after    - идентификатор существующей кнопки, после которой
  //            вставляется кнопка, если 0 - в конец панели
  // Отличается от InsertButton тем, что изображение bmpFace          
  //                            на кнопочке отрисовывается с фоном
  int InsertButtonEx(int panelID, intptr_t bmpFace, int command, int after = 0); 

  // Добавить/вставить элемент управления в панель
  // panelID  - идентификатор панели
  // ctrlId   - Идентификатор создаваемого элемента управления,
  //            если CtrlId = (-1) - вставляется разделитель
  // hwnd     - идентификатор окна элемента управления
  // after    - идентификатор элемента управления в панели инструментов,
  //            после которого вставляется создаваемый элемент управления.
  //            Если after = NULL - добавляется в конец
  int InsertControl(int panelID, HWND hwnd, int ctrlId, int after = 0);

  // Переместить панель инструментов прикладной задачи
  // panelID  - идентификатор панели
  // rect     - координаты нового положения панели
  // position - расположение панели в окне (см. LOCAL)
  // layout   - признак немедленного обновления окна
  int MovePanel(int panelID, RECT rect,
                int  position, int layout = 1);

  // Удалить кнопку из панели
  // panelID  - идентификатор панели
  // command  - идентификатор кнопки
  int DeleteButton(int panelID, int command);

  // Изменить картинку на кнопке
  // panelID  - идентификатор панели
  // command  - идентификатор кнопки
  // bmpFace  - идентификатор нового изображения кнопки
  int SetButtonFace(int panelID, int command, HBITMAP bmpFace); 

  // Запрос HWND панели инструментов
  // panelID  - идентификатор панели
  HWND GetPanelHandle(int panelID);                             

  // Показать/Скрыть панель инструментов прикладной задачи
  // panelID  - идентификатор панели
  // show - 0 - скрыть панель,
  //         1 - показать панель
  int ShowPanel(int panelID, int show = 1);             

  // Запрос на закрытие панели инструментов
  // Если это главная панель задачи,
  // то она может отключить текущий обработчик
  virtual int PanelCanClose(int panelID);

  // Отпускание правой кнопки мыши над панелью         
  // panelID  - идентификатор панели
  // point    - положение курсора на экране
  // ctrlID   - идентификатор элемента управления панели,
  //            над которым быля нажата клавиша
  virtual int PanelRightUp(int panelID, POINT * point, long int ctdlID = 0)
     { return 0; }

  // Уведомление о закрытии панели инструментов        
  virtual void PanelClosed(int panelID) {}

  // Запросить флаг активного модального диалога в системе          
  // Возвращает: 0-нет активных диалогов, 1-наличие активного диалога
  // Для предотвращения запуска второго модального диалога из "висячих" панелей
  int GetFlagIsDialogActive();

  // Установить флаг активного модального диалога в системе         
  // Устанавливать 1 перед запуском диалога и 0 после его закрытия
  // Для предотвращения запуска второго модального диалога из "висячих" панелей
  int SetFlagIsDialogActive(int value);


  /************************************************************
  *                                                           *
  *           Извещения о различных событиях                  *
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

  // Извещение об завершении текущего обработчика какой-то задачи
  // ident - идентификатор обработчика
  virtual void AnyActionClose(int ident) {}

  // Извещение об запуске обработчика какой-то задачи
  // ident - идентификатор обработчика
  virtual void AnyActionOpen(int ident) {}

  // Извещение о том, что закрывается карта и будет
  // закрыта задача (можно запомнить параметры сеанса в INI-файле и т.п.)
  // Если задача закрывается, а карта остается открытой - это
  // событие не вызывается
  virtual void BeforeCloseMap() {}

  // Извещение об изменении содержания данных
  // (карт, растров, матриц ...)
  // Если активен обработчик - проверить,
  // что он не работает c закрытыми данными !
  virtual void ChangeData() {}

  // Извещение об изменении размера главного окна
  // Передаются размеры клиентной области окна
  virtual void ChangeMainSize(int /*width*/, int /*height*/) {}

  // Извещение о наступлении периода проверки данных
  // Вызывается для обеспечения синхронизации данных
  // в многопользовательском режиме работы с частотой,
  // выбранной пользователем (Параметры/Период обновления)
  virtual void AdjustData() {}

  // Извещение о редактировании объекта векторной карты
  // Приходит при обновлении одной из векторных карт документа
  // changeinfo - см. maptype.h
  // Если при обработке извещения редактировать карту -
  // может произойти зацикливание !
  virtual void ChangeObject(CHANGEINFO* /*changeinfo*/) {}

  // Запрос - нужно ли извещать задачу об
  // изменениях объектов (посылка извещений понижает
  // скорость редактирования векторной карты)
  virtual int IsChangeObjectActive() { return 0; }

  // Извещение об изменении языка сообщений
  virtual void ChangeLanguage(int /*code*/) {}

  // Нажата клавиша
  // key   - код нажатой клавиши
  // flags - признак нажатия служебной клавиши
  //         (0 - не нажаты, 2 - нажата CTRL : flags & KD_CNTRL)
  virtual int KeyDown(UINT /*key*/, UINT /*repeatCount*/, UINT /*flags*/)
                                            { return 0; }

  // Перемещение мышки по окну в текущей точке           
  virtual int Move(UINT /*modKeys*/, POINT& /*point*/)
                                    { return 0; }

  // Управление "отображением"
  // Задача может нарисовать "под картой"
  int BeforePaint(HDC dc, RECT& rect)
   { THDC Thdc(dc); return BeforePaint(Thdc, (TRECT&)rect); }

  virtual int BeforePaint(THDC& dc, TRECT& rect) { return 0; }

  // Управление "отображением"
  // Задача может нарисовать "на карте"
  // (карта уже нарисована ...)
  int Paint(HDC dc, bool erase, RECT& rect)
   { THDC Thdc(dc); return Paint(Thdc,erase,(TRECT&)rect); }

  virtual int Paint(THDC& dc, bool erase, TRECT& rect)
                                     { return 0; }

  /************************************************************
  *                                                           *
  *           Функции запроса справочных данных               *
  *                                                           *
  ************************************************************/

  // Запросить имя данной задачи
  virtual const char * Name() { return "MapTask"; }

  // Отправить сообщение главному окну приложения
  int MainMessage(int message,intptr_t wparm,intptr_t lparm = 0)
   { return MapWindow->MainMessage(message,wparm,lparm); }

  // Запросить идентификатор панели данной задачи
  // Переопределяется в конце класса
  virtual int PanelIdent() { return 0; }

  // Запросить модуль ресурсов приложения (с учетом языка интерфейса)
  // Может изменяться в ходе работы программы !
#ifdef WIN32API   
  TModule * GetResourceModule()
    { return MapWindow->GetResourceModule(); }
#endif

  // Загрузить текстовую строку из общих ресурсов
  virtual int LoadString(int id, char * buffer, int size);

  // Запросить код языка сообщений
  int GetLanguage()
    { return MapWindow->GetLanguage();}

  // КОДЫ ЯЗЫКОВ СООБЩЕНИЙ И ПУНКТОВ МЕНЮ
  enum OPTIONLANGUAGE
   {
     ML_ENGLISH = 1,  // АНГЛИЙСКИЙ
     ML_RUSSIAN = 2   // РУССКИЙ
   };

  // Запросить окно электронной карты
  TMapWindow * GetMapWindow() { return MapWindow; }


  // Запрос координат текущей точки
  // ----------------------------------

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
  DOUBLEPOINT * GetGeoPoint() { return MapWindow->GetGeoPoint();}

  // Проверка поддержки географических координат
  // Если не поддерживаются - возвращает ноль
  int IsGeoSupported()
     { return MapDoc->IsGeoSupported(); }

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
  //  Пример вызова:
  //
  //  int ret = OpenFile(name, size,
  //                     "Открыть/Загрузить новую карту",
  //                     "Карты местности (*.map)|*.MAP|",
  //                     OFN_FILEMUSTEXIST, 0, 0);
  //
  int OpenFile(char * name, int namesize,
               const char * title, const char * filter,
               int  flags,  int    index,
               const char * path);

 public :

  TMapWindow * MapWindow;   // Окно обрабатываемой карты

  TMapAccess * MapDoc;      // Документ : "электронная карта"
                            // Производный от TMapAccess

 public :

  TMapAction * Action;      // Указатель на текущий обработчик
                            // или ноль
                            // Устанавливается и сбрасывается
                            // автоматически !
};


// --------------------------------------------------------------
//  Описание таблицы обработчиков команд (Action)
// --------------------------------------------------------------

#define SeekAction(comid,run)               \
  int ActionRun = run;                      \
  switch(comid)

#define CheckAction(comid,actiontype,topic)     \
    case comid :                                \
      if (ActionRun == 0)                       \
        return (TMapAction *)1;                 \
      if (ActionRun == -1)                      \
        { MapWindow->ViewHelp(topic);           \
          return 0;}                            \
      try                                       \
       {                                        \
         return                                 \
            new actiontype(this,comid);         \
       }                                        \
      catch(...)                                \
       {                                        \
         ::MessageBox(0,                        \
          "Application error", Name(),          \
           MB_OK | MB_ICONSTOP);                \
       }                                        \
      break


#define ReturnAction()  return (TMapAction *)0

// --------------------------------------------------------------
//  Описание таблицы выполнения команд без обработчиков (Command)
// --------------------------------------------------------------

#define SeekCommand(comid,run)              \
  int CommandRun = run;                     \
  switch(comid)

#define CheckCommand(comid,call,topic)      \
    case comid :                            \
         if (CommandRun == 0)               \
            return (TMapAction *)1;         \
         if (CommandRun == -1)              \
           {ViewHelp(topic);                \
            return (TMapAction *)0;}        \
         call();                            \
         return ((TMapAction *)-1)

#define CheckCommandAndIdent(comid,call,topic) \
    case comid :                            \
         if (CommandRun == 0)               \
            return (TMapAction *)1;         \
         if (CommandRun == -1)              \
           {ViewHelp(topic);                \
            return (TMapAction *)0;}        \
         call(comid);                       \
         return ((TMapAction *)-1)

#endif // MTMAPTAS_H

