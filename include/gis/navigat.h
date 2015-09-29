#ifndef NAVIGAT_H
#define NAVIGAT_H

#ifdef WIN32API

#ifndef MTACTION_H
  #include "mtaction.h"
#endif
#ifndef MSERVICE_H
  #include "mservice.h"
#endif

#ifndef MWCOPYIM_H
  #include "Mwcopyim.h"
#endif

#include <owl\dialog.h>
#include <owl\static.h>
#include <owl\button.h>
#include <owl\gadgetwi.h>
#include <owl\combobox.h>
#include "openmap.h"
#include "Awhelpid.rh"
#else
#include <qvariant.h>
#include <qobjectlist.h>  // for component system PS "Designer"
#include <designer_component.h>
#include <qdialog.h>
#include <qevent.h>
#include <qpen.h>
#include <qpainter.h>
#include <qbrush.h>
#include <qlineedit.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qframe.h>
#include <qtoolbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qlayout.h>
#include <qlabel.h>
#endif                                     

#include "navigat.rh"
#include <fstream.h>

#ifndef XCONTEXT_H
  #include "xcontext.h"
#endif

#ifdef WIN32API                                     
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ КЛАСС "ПАНЕЛЬ ИНСТРУМЕНТОВ" +++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class TNavToolsPanel : public TGadgetWindow
{
  public :

  TNavToolsPanel(TWindow * parent,TMapService *task);
  ~TNavToolsPanel(){;}

  void SetupWindow();
  void ButtonHandler(uint id);
  void ButtonEnable(TCommandEnabler& ce);
  void SetPointCount(int count){PointCount = count;}
  void SetTask(TMapService *task){Task = task;}
  bool IdleAction(long idleCount);
  private:
  TWindow     * ParentDialog;
  TMapService * Task;
  int PointCount;


 DECLARE_RESPONSE_TABLE(TNavToolsPanel);
};

//class TPointText;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++ Класс рисования карты ++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class TRasterZoom : public TWindow
{
 public:

	TRasterZoom(TWindow* parent,TMapService *task);
  ~TRasterZoom(){SaveFile();}

 void SetupWindow();

 void SetTask(TMapService *task)
 {
  Task     = task;
  FlagZoom = 1;
 }

 // Установить увеличение ZOOM (относительно масштаба 1:1)
 // scale - коэффициент увеличения (-50 ... 50)
 void SetScale(long scale)
 {
  Scale = scale;
  if(Scale >= 2)SetCursor(0,IDC_CROSS);
  else          SetCursor(0,IDC_SIZEALL);
 }

 int         FlagZoom;         // Флаг принудительной перерисовки
 int         FlagImage;        //

 void SetContens();            // Установить состав
 void SavePoint();             // Сохранить точку
 void RestorePoint();          // Восстановить экран

 void SetPointCount(int count)  {PointCount   = count;}
 void SetCurrentPoint(int point){CurrentPoint = point;}
 int  GetPointCount()  {return PointCount;}
 int  GetCurrentPoint(){return CurrentPoint;}
 int  Delete();                                // Очистить сценарий
 int  SaveFile();                              // Сохранить в файл
 int  ReadFile();                              // Считать файл
 int  GetNameFile(char *name,int size);        // Запросить имя файла

 int PointCount;               // Всего точек
 int CurrentPoint;             // Текущая точка
 long       Scale;             // Текущее увеличение ZOOM отн. м-ба 1:1
 XYHDOUBLE  PointArray[100];   // Памятные места.
 char       PointText[8000];
 private:

 TMapService *Task;
 long        RealScale;        // Знаменатель масштаба
 long        MainScale;        // Текущий м-б карты
 TRect       BoxRect;          // Текущее положение окна карты в ZOOM
 int         FlagDown;         // Флаг нажатия левой кнопки
 TPoint      FirstPoint;       // Последнее положение указателя
 TCopyImage  CopyImage;        // Копия изображения

 DOUBLEPOINT ZoomLTPoint;      // Габариты ZOOM в районе (MAP) (лев.верхн.)
 DOUBLEPOINT ZoomRBPoint;      // Габариты ZOOM в районе (MAP) (прав.нижн.)



//----------------------------------------------------------------
// Отклики на события мыши
//----------------------------------------------------------------

 void EvLButtonDown(uint modKeys, TPoint& point);
 void EvLButtonUp(uint modKeys, TPoint& point);
 void EvMouseMove(uint modKeys, TPoint& point);

//----------------------------------------------------------------
// Рисование окна
//----------------------------------------------------------------

 void Paint(TDC& dc, bool, TRect&);
 void ShowPoint(TDC& DC);

 DECLARE_RESPONSE_TABLE(TRasterZoom);
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++ Блок диалога +++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class TMedZoom : public TDialog
{
  public:

  TMedZoom(TMapService * task);
 ~TMedZoom();

  void SetupWindow();

  //  Рисование окна
  //  rezim = 1 - рисовать всегда
  //  rezim = 0 - рисовать только при масштабе > 1:1
  void Invalidate(int rezim = 0);

  // Изменение размеров окна
  void EvSize(uint sizeType, TSize& size);

  void SetTask(TMapService *task);

  // Установить новое значение масштаба
  int SetScale(int scale);

  // Определение знаменателя масштаба отображения
  long GetScale()
  {
   if(Task == 0)return 0;
   long RealScale;
   if(Scale >= 0)RealScale = (Task->MapDoc->GetMapScale())>>(Scale/2);
   if(Scale <  0)RealScale = (Task->MapDoc->GetMapScale())<<(Scale/-2);
   RealScale = Task->MapDoc->GetNewShowScale(RealScale);
   return (RealScale);
  }

  void ViewHelp()
  {
   if(Task == 0)return;
   Task->MapWindow->ViewHelp(IDN_NAVIGATOR);
   ::SetFocus(Task->MapWindow->GetHandle());
  }

  // Уменьшить масштаб в 2 раза
  void Minus();

  // Увеличить масштаб в 2 раза
  void Plus();

  // Закрыть окно
  void EvClose()
  {
    if (Task && Task->MapWindow->GetMainHandle())
      ::PostMessage(Task->MapWindow->GetMainHandle(),WM_COMMAND,CM_NAVIGATOR,0);
  }

  // Сохранить точку
  void SavePoint()
  {
   if(RasterZoom)RasterZoom->SavePoint();
   if(Tools)Tools->SetPointCount(RasterZoom->GetPointCount());
   SetList(RasterZoom->GetPointCount());
  }

  // Очистить сценарий
  void Clear()
  {
   if(RasterZoom == 0)return;
   RasterZoom->SetPointCount(0);
   RasterZoom->SetCurrentPoint(0);
   if(Tools)Tools->SetPointCount(0);
   RasterZoom->Invalidate(0);
   SetList(0);
  }

  // Удалить текущую точку
  void Delete()
  {
   if((RasterZoom == 0)||(Tools == 0))return;
   Tools->SetPointCount(RasterZoom->Delete());
   RasterZoom->Invalidate(0);
   PointList->DeleteString(RasterZoom->GetCurrentPoint());
   SetList(RasterZoom->GetPointCount());
  }

  // Восстановить экран
  void RestorePoint(){if(RasterZoom)RasterZoom->RestorePoint();}

  // Выбрана точка
  void SelectPoint()
  {
   if((RasterZoom == 0)||(PointList == 0))return;
   RasterZoom->SetCurrentPoint(PointList->GetSelIndex());
   ind = PointList->GetSelIndex();
   RestorePoint();
   SetScale(RasterZoom->Scale);
  }

  // Начало
  void Begin()
  {
   if(RasterZoom == 0)return;
   RasterZoom->SetCurrentPoint(0);
   SetList(RasterZoom->GetPointCount());
   RestorePoint();
  }

  // Конец
  void End()
  {
   if(RasterZoom == 0)return;
   RasterZoom->SetCurrentPoint(RasterZoom->GetPointCount()-1);
   SetList(RasterZoom->GetPointCount());
   RestorePoint();
  }

 // Следующая
  void Next()
  {
   if(RasterZoom == 0)return;
   if(RasterZoom->GetCurrentPoint() == RasterZoom->GetPointCount()-1)Begin();
   else
      RasterZoom->SetCurrentPoint(RasterZoom->GetCurrentPoint()+1);
   SetList(RasterZoom->GetPointCount());
   RestorePoint();
  }

  // Предыдущая
  void Prev()
  {
   if(RasterZoom == 0)return;
   if(RasterZoom->CurrentPoint == 0)End();
   else
      RasterZoom->SetCurrentPoint(RasterZoom->GetCurrentPoint()-1);
   SetList(RasterZoom->GetPointCount());
   RestorePoint();
  }

  // Настроить список

  void SetList(int count);
  void InitText(int);
  void Close(){EvClose();}

  void  Open();                                  // Открыть файл на диске
  void  Save();                                  // Сохранить в файл на диске
  int   SetFileName(char*, int, int);
  int   ind;
  void  CmNavOk(){SetPointLast(); return; }
  void  SetPointText();
  void  SetPointLast();

//----------------------------------------------------------------
//     Отреагировать на изменение размера окна
//----------------------------------------------------------------

  void EvSysCommand(uint cmdType, TPoint&);
  void SetContens(){RasterZoom->SetContens();} //Установить состав

  private:

  TMapService *Task;
  TStatic     *Value;
  TComboBox   *PointList;
  long         Scale;       // Значение масштаба
  TRasterZoom *RasterZoom;  // Рисовальщик
  TNavToolsPanel *Tools;

  int          FlagSlider;  // Признак необходимости установки масштаба
  int          FlagLarge;   // Состояние (размер) окна


  DECLARE_RESPONSE_TABLE(TMedZoom);
};


/*
class TPointText : public TDialog
{
  public:

  TPointText(TRasterZoom*parent, int resId);

  void SetupWindow();
DECLARE_RESPONSE_TABLE(TPointText);
};*/

#else

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLineEdit;
class QFrame;
class QToolButton;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++ Класс рисования карты ++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class TRasterZoom : public QWidget
{
 public:

	TRasterZoom(QWidget* parent,TMapService *task);
  ~TRasterZoom(){SaveFile();}

 void SetupWindow();

 void TRasterZoom::SetStr(double x, double y);

 void SetTask(TMapService *task)
 {
  Task     = task;
  FlagZoom = 1;
 }

 // Установить увеличение ZOOM (относительно масштаба 1:1)
 // scale - коэффициент увеличения (-50 ... 50)
 void SetScale(long scale)
 {
  Scale = scale;
 }

 int         FlagZoom;         // Флаг принудительной перерисовки
 int         FlagImage;        //

 void SetContens();            // Установить состав
 void SavePoint();             // Сохранить точку
 void RestorePoint();          // Восстановить экран

 void SetPointCount(int count)  {PointCount   = count;}
 void SetCurrentPoint(int point){CurrentPoint = point;}
 int  GetPointCount()  {return PointCount;}
 int  GetCurrentPoint(){return CurrentPoint;}
 int  Delete();                                // Очистить сценарий
 int  SaveFile();                              // Сохранить в файл
 int  ReadFile();                              // Считать файл
 int  GetNameFile(char *name,int size);        // Запросить имя файла

 int PointCount;               // Всего точек
 int CurrentPoint;             // Текущая точка
 long       Scale;             // Текущее увеличение ZOOM отн. м-ба 1:1
 XYHDOUBLE  PointArray[100];   // Памятные места.
 char       PointText[8000];
 XCONTEXT   FxDC;                // Контекст отрисовки карты
 int flag;
 RECT FramRec;

 //----------------------------------------------------------------
 // Рисование окна
 //----------------------------------------------------------------
 void ShowPoint(HDC& DC);
 void paintEvent(QPaintEvent *paint);

 private:

 TMapService *Task;
 long        RealScale;        // Знаменатель масштаба
 long        MainScale;        // Текущий м-б карты
 RECT       BoxRect;          // Текущее положение окна карты в ZOOM
 int         FlagDown;         // Флаг нажатия левой кнопки
 POINT      FirstPoint;       // Последнее положение указателя
 POINT      FirstPointMove;       // Последнее положение указателя
// TCopyImage  CopyImage;        // Копия изображения

 DOUBLEPOINT ZoomLTPoint;      // Габариты ZOOM в районе (MAP) (лев.верхн.)
 DOUBLEPOINT ZoomRBPoint;      // Габариты ZOOM в районе (MAP) (прав.нижн.)



 //----------------------------------------------------------------
 // Отклики на события мыши
 //----------------------------------------------------------------
 void mouseReleaseEvent(QMouseEvent* event);
 void mousePressEvent(QMouseEvent * event);
 void mouseMoveEvent(QMouseEvent* event);


};

class TMedZoom : public QDialog
{
    Q_OBJECT

public:
    TMedZoom(TMapService * task, QWidget* parent);
    ~TMedZoom();

  QLabel* leScale;
  QFrame* fNavig;
  QLabel* leXY;
  QFrame* fStatus;
  QToolButton* tbNavig;
  QBoxLayout *buttons;

  void SetTask(TMapService *task);

  //  Рисование окна
  //  rezim = 1 - рисовать всегда
  //  rezim = 0 - рисовать только при масштабе > 1:1
  void Invalidate(int rezim = 0);

  // Нажата клавиша (обработка ESC и ENTER)
  void keyPressEvent(QKeyEvent*);

  //Закрыть диалог
  void closeEvent(QCloseEvent* e);

  // Измененить размер окна
  void resizeEvent(QResizeEvent*evsize);

  // Установить новое значение масштаба
  int SetScale(int scale);

  // Определение знаменателя масштаба отображения
  long GetScale()
  {
   if(Task == 0)return 0;
   long RealScale;
   if(Scale >= 0)RealScale = (Task->MapDoc->GetMapScale())>>(Scale/2);
   if(Scale <  0)RealScale = (Task->MapDoc->GetMapScale())<<(Scale/-2);
   RealScale = Task->MapDoc->GetNewShowScale(RealScale);
   return (RealScale);
  }

  int Move;

  private:

  TMapService *Task;
  long         Scale;       // Значение масштаба
  int          ind;
  TRasterZoom *RasterZoom;  // Рисовальщик

  int          FlagSlider;  // Признак необходимости установки масштаба
  int          FlagLarge;   // Состояние (размер) окна


  protected slots:

  void SetContens();

};


#endif                                     

inline void TMedZoom::Invalidate(int rezim)
{
 if((Scale >= 2)||(rezim != 0))
   {
#ifdef WIN32API                                     
     if(RasterZoom)RasterZoom->Invalidate(false);
#else
     QPaintEvent *paint;
     if(RasterZoom)RasterZoom->paintEvent(paint);
#endif
   }
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ КЛАСС "НАВИГАТОР КАРТЫ" +++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class TServiceNavigator : public TMapAction
{
 public :
 TServiceNavigator::TServiceNavigator(TMapService * task,int ident)
                             :TMapAction(task,ident)
 {
  Task   = task;
 }
 ~TServiceNavigator();


 void Setup();               // Установить исходные данные
 void ResetMessage();        // Перевывод сообщения

 int Move(UINT,TPoint&);      // Реакция на перемещение мыши
 int Paint(TDC&,bool,TRect& );// Реакция на скроллинг

 void IdleAction(long IdleCount);

 TMapService *Task;
#ifdef WIN32API                                     
 TStatic     *Value;       // Область вывода значения масштаба
#endif
 TRasterZoom *RasterZoom;  // Рисовальщик
};

#endif
