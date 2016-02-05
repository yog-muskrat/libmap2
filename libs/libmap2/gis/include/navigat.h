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
// +++++++ ����� "������ ������������" +++++++++++++++++++++
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
//++++ ����� ��������� ����� ++++++++++++++++++++++++++++++++++++
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

 // ���������� ���������� ZOOM (������������ �������� 1:1)
 // scale - ����������� ���������� (-50 ... 50)
 void SetScale(long scale)
 {
  Scale = scale;
  if(Scale >= 2)SetCursor(0,IDC_CROSS);
  else          SetCursor(0,IDC_SIZEALL);
 }

 int         FlagZoom;         // ���� �������������� �����������
 int         FlagImage;        //

 void SetContens();            // ���������� ������
 void SavePoint();             // ��������� �����
 void RestorePoint();          // ������������ �����

 void SetPointCount(int count)  {PointCount   = count;}
 void SetCurrentPoint(int point){CurrentPoint = point;}
 int  GetPointCount()  {return PointCount;}
 int  GetCurrentPoint(){return CurrentPoint;}
 int  Delete();                                // �������� ��������
 int  SaveFile();                              // ��������� � ����
 int  ReadFile();                              // ������� ����
 int  GetNameFile(char *name,int size);        // ��������� ��� �����

 int PointCount;               // ����� �����
 int CurrentPoint;             // ������� �����
 long       Scale;             // ������� ���������� ZOOM ���. �-�� 1:1
 XYHDOUBLE  PointArray[100];   // �������� �����.
 char       PointText[8000];
 private:

 TMapService *Task;
 long        RealScale;        // ����������� ��������
 long        MainScale;        // ������� �-� �����
 TRect       BoxRect;          // ������� ��������� ���� ����� � ZOOM
 int         FlagDown;         // ���� ������� ����� ������
 TPoint      FirstPoint;       // ��������� ��������� ���������
 TCopyImage  CopyImage;        // ����� �����������

 DOUBLEPOINT ZoomLTPoint;      // �������� ZOOM � ������ (MAP) (���.�����.)
 DOUBLEPOINT ZoomRBPoint;      // �������� ZOOM � ������ (MAP) (����.����.)



//----------------------------------------------------------------
// ������� �� ������� ����
//----------------------------------------------------------------

 void EvLButtonDown(uint modKeys, TPoint& point);
 void EvLButtonUp(uint modKeys, TPoint& point);
 void EvMouseMove(uint modKeys, TPoint& point);

//----------------------------------------------------------------
// ��������� ����
//----------------------------------------------------------------

 void Paint(TDC& dc, bool, TRect&);
 void ShowPoint(TDC& DC);

 DECLARE_RESPONSE_TABLE(TRasterZoom);
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++ ���� ������� +++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class TMedZoom : public TDialog
{
  public:

  TMedZoom(TMapService * task);
 ~TMedZoom();

  void SetupWindow();

  //  ��������� ����
  //  rezim = 1 - �������� ������
  //  rezim = 0 - �������� ������ ��� �������� > 1:1
  void Invalidate(int rezim = 0);

  // ��������� �������� ����
  void EvSize(uint sizeType, TSize& size);

  void SetTask(TMapService *task);

  // ���������� ����� �������� ��������
  int SetScale(int scale);

  // ����������� ����������� �������� �����������
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

  // ��������� ������� � 2 ����
  void Minus();

  // ��������� ������� � 2 ����
  void Plus();

  // ������� ����
  void EvClose()
  {
    if (Task && Task->MapWindow->GetMainHandle())
      ::PostMessage(Task->MapWindow->GetMainHandle(),WM_COMMAND,CM_NAVIGATOR,0);
  }

  // ��������� �����
  void SavePoint()
  {
   if(RasterZoom)RasterZoom->SavePoint();
   if(Tools)Tools->SetPointCount(RasterZoom->GetPointCount());
   SetList(RasterZoom->GetPointCount());
  }

  // �������� ��������
  void Clear()
  {
   if(RasterZoom == 0)return;
   RasterZoom->SetPointCount(0);
   RasterZoom->SetCurrentPoint(0);
   if(Tools)Tools->SetPointCount(0);
   RasterZoom->Invalidate(0);
   SetList(0);
  }

  // ������� ������� �����
  void Delete()
  {
   if((RasterZoom == 0)||(Tools == 0))return;
   Tools->SetPointCount(RasterZoom->Delete());
   RasterZoom->Invalidate(0);
   PointList->DeleteString(RasterZoom->GetCurrentPoint());
   SetList(RasterZoom->GetPointCount());
  }

  // ������������ �����
  void RestorePoint(){if(RasterZoom)RasterZoom->RestorePoint();}

  // ������� �����
  void SelectPoint()
  {
   if((RasterZoom == 0)||(PointList == 0))return;
   RasterZoom->SetCurrentPoint(PointList->GetSelIndex());
   ind = PointList->GetSelIndex();
   RestorePoint();
   SetScale(RasterZoom->Scale);
  }

  // ������
  void Begin()
  {
   if(RasterZoom == 0)return;
   RasterZoom->SetCurrentPoint(0);
   SetList(RasterZoom->GetPointCount());
   RestorePoint();
  }

  // �����
  void End()
  {
   if(RasterZoom == 0)return;
   RasterZoom->SetCurrentPoint(RasterZoom->GetPointCount()-1);
   SetList(RasterZoom->GetPointCount());
   RestorePoint();
  }

 // ���������
  void Next()
  {
   if(RasterZoom == 0)return;
   if(RasterZoom->GetCurrentPoint() == RasterZoom->GetPointCount()-1)Begin();
   else
      RasterZoom->SetCurrentPoint(RasterZoom->GetCurrentPoint()+1);
   SetList(RasterZoom->GetPointCount());
   RestorePoint();
  }

  // ����������
  void Prev()
  {
   if(RasterZoom == 0)return;
   if(RasterZoom->CurrentPoint == 0)End();
   else
      RasterZoom->SetCurrentPoint(RasterZoom->GetCurrentPoint()-1);
   SetList(RasterZoom->GetPointCount());
   RestorePoint();
  }

  // ��������� ������

  void SetList(int count);
  void InitText(int);
  void Close(){EvClose();}

  void  Open();                                  // ������� ���� �� �����
  void  Save();                                  // ��������� � ���� �� �����
  int   SetFileName(char*, int, int);
  int   ind;
  void  CmNavOk(){SetPointLast(); return; }
  void  SetPointText();
  void  SetPointLast();

//----------------------------------------------------------------
//     ������������� �� ��������� ������� ����
//----------------------------------------------------------------

  void EvSysCommand(uint cmdType, TPoint&);
  void SetContens(){RasterZoom->SetContens();} //���������� ������

  private:

  TMapService *Task;
  TStatic     *Value;
  TComboBox   *PointList;
  long         Scale;       // �������� ��������
  TRasterZoom *RasterZoom;  // �����������
  TNavToolsPanel *Tools;

  int          FlagSlider;  // ������� ������������� ��������� ��������
  int          FlagLarge;   // ��������� (������) ����


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
//++++ ����� ��������� ����� ++++++++++++++++++++++++++++++++++++
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

 // ���������� ���������� ZOOM (������������ �������� 1:1)
 // scale - ����������� ���������� (-50 ... 50)
 void SetScale(long scale)
 {
  Scale = scale;
 }

 int         FlagZoom;         // ���� �������������� �����������
 int         FlagImage;        //

 void SetContens();            // ���������� ������
 void SavePoint();             // ��������� �����
 void RestorePoint();          // ������������ �����

 void SetPointCount(int count)  {PointCount   = count;}
 void SetCurrentPoint(int point){CurrentPoint = point;}
 int  GetPointCount()  {return PointCount;}
 int  GetCurrentPoint(){return CurrentPoint;}
 int  Delete();                                // �������� ��������
 int  SaveFile();                              // ��������� � ����
 int  ReadFile();                              // ������� ����
 int  GetNameFile(char *name,int size);        // ��������� ��� �����

 int PointCount;               // ����� �����
 int CurrentPoint;             // ������� �����
 long       Scale;             // ������� ���������� ZOOM ���. �-�� 1:1
 XYHDOUBLE  PointArray[100];   // �������� �����.
 char       PointText[8000];
 XCONTEXT   FxDC;                // �������� ��������� �����
 int flag;
 RECT FramRec;

 //----------------------------------------------------------------
 // ��������� ����
 //----------------------------------------------------------------
 void ShowPoint(HDC& DC);
 void paintEvent(QPaintEvent *paint);

 private:

 TMapService *Task;
 long        RealScale;        // ����������� ��������
 long        MainScale;        // ������� �-� �����
 RECT       BoxRect;          // ������� ��������� ���� ����� � ZOOM
 int         FlagDown;         // ���� ������� ����� ������
 POINT      FirstPoint;       // ��������� ��������� ���������
 POINT      FirstPointMove;       // ��������� ��������� ���������
// TCopyImage  CopyImage;        // ����� �����������

 DOUBLEPOINT ZoomLTPoint;      // �������� ZOOM � ������ (MAP) (���.�����.)
 DOUBLEPOINT ZoomRBPoint;      // �������� ZOOM � ������ (MAP) (����.����.)



 //----------------------------------------------------------------
 // ������� �� ������� ����
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

  //  ��������� ����
  //  rezim = 1 - �������� ������
  //  rezim = 0 - �������� ������ ��� �������� > 1:1
  void Invalidate(int rezim = 0);

  // ������ ������� (��������� ESC � ENTER)
  void keyPressEvent(QKeyEvent*);

  //������� ������
  void closeEvent(QCloseEvent* e);

  // ���������� ������ ����
  void resizeEvent(QResizeEvent*evsize);

  // ���������� ����� �������� ��������
  int SetScale(int scale);

  // ����������� ����������� �������� �����������
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
  long         Scale;       // �������� ��������
  int          ind;
  TRasterZoom *RasterZoom;  // �����������

  int          FlagSlider;  // ������� ������������� ��������� ��������
  int          FlagLarge;   // ��������� (������) ����


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
// +++++++ ����� "��������� �����" +++++++++++++++++++++++++++++++++
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


 void Setup();               // ���������� �������� ������
 void ResetMessage();        // ��������� ���������

 int Move(UINT,TPoint&);      // ������� �� ����������� ����
 int Paint(TDC&,bool,TRect& );// ������� �� ���������

 void IdleAction(long IdleCount);

 TMapService *Task;
#ifdef WIN32API                                     
 TStatic     *Value;       // ������� ������ �������� ��������
#endif
 TRasterZoom *RasterZoom;  // �����������
};

#endif
