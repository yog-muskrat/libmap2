
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
// +++++++ ����� "����� ��������� ����������� �����" +++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectFrame : public TMapAction
{
 public :

  // ������� ������ "����� ���������"
  TMapSelectFrame(TMapTask * task, int ident);

  // ������� ������ "����� ���������"
 ~TMapSelectFrame();

  // ���������� ��������
  virtual void SetFrame(DOUBLEPOINT* first, DOUBLEPOINT* Second);

  // ��������� ������ ��������� �� ������� ������
  virtual void BuildFrame();

  // ����������/������� �� ����� ����� ���������
  virtual void PaintFrame();

  // ��������� ���������� ������� ��� ������� ������� �����
  // ���������� ������������� ����� ������ ������ �����
  // ���� ��� �������� ���� - ���������� ��������� ������
  virtual int Run() { return 1;}           

  /************************************************************
  *                                                           *
  *       ������ ��������� ���������� ������� ���� �����      *
  *                                                           *
  ************************************************************/

  // ������ : ����� �� ��������� ����� ������ ������� �� �����
  virtual int CanSelectObject()  { return 0; }  // ������ !        

  // ������� � ������ ��������� �������� ������������
  // MapWindow->SetMessage("...");
  virtual void Comment();
  virtual void CommentSelect(int width, int heigth);

  // ������� �� ������ ����� ������ �����
  virtual int LeftUp(UINT /*modKeys*/, TPoint& /*point*/);

  // ����������� ����� �� ���� � ������� �����
  virtual int Move(UINT /*modKeys*/, TPoint& /*point*/);

  // ������������ �� ����� ����� ���������
  virtual int Paint(TDC& dc, bool erase, TRect& rect);

  // ��������� �� ������ ��������� �������
  virtual int Revert();

 public :

  PAINTPARM Form;   // ��� ������� ��������� �� ������
                    // (���������� ����� 5/2 ���������)
  PLACEDATA Frame;  // �������� ��������� �����

  IMGDOT Image;     // �������� ���������� ����� (������ ���������)

  struct Border
  {
    DOUBLEPOINT UpLeft;     // ���������� ������ ����� (Map)
    DOUBLEPOINT UpRight;    // ���������� ������ �����
    DOUBLEPOINT DownRight;  // ���������� ������� �����
    DOUBLEPOINT DownLeft;   // ���������� ��������� �����
    DOUBLEPOINT UpLeftLast; // ���������� ��������� ����� (Map)
  }
    Border;

  LONG PointCount;         // ����� �����, ����������� ��������
  int  SelectedPoints;     // ������� �����

  DOUBLEPOINT First;      // ���������� ������� ���� (Map)
  DOUBLEPOINT Second;     // ���������� ������� ���� (Map)

  int FlagClear;          // ������� "������ �����"
};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++ ����� "����� ������������� ��������� ����������� �����" +++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectFrameLimit : public TMapSelectFrame
{
 public :

  // ������� ������ "����� ���������"
  TMapSelectFrameLimit(TMapTask * task, int ident);

  // ��������� ������ ��������� �� ������� ������
  void BuildFrame();

  // ��������� ������ ��������������� ��������� �� ������� ������
  void BuildLimit();

  // ���������� �� ����� ����� ��������������� �������
  void PaintLimit();

  // ���������� ����������� ������� ����������� ���������
  // place - ��� ������� ��������� (��������,TMapAccess::MAP)
  // type  - ������� ����������� ������� ����������� ���������
  // ���� type == 0, �������������� ������ ������������ ��
  // �� ������ �� ������ ����������� ���������
  void SetFrameLimit(double width, double height,
                     int place, int type);

  /************************************************************
  *                                                           *
  *       ������ ��������� ���������� ������� ���� �����      *
  *                                                           *
  ************************************************************/

  // ����������� ����� �� ���� � ������� �����
  virtual int Move(UINT /*modKeys*/, TPoint& /*point*/);

  // ������������ �� ����� ����� ���������
  virtual int Paint(TDC& dc, bool erase, TRect& rect);

 protected :

  PAINTPARM LimitForm;   // ��� ������� ��������� �� ������
                         // (�������� ����� ���������)
  PLACEDATA Limit;       // �������� ��������� �����

  IMGLINE LimitImage;    // �������� ����� (������ ���������)

  struct LimitBorder
   {
     DOUBLEPOINT UpLeft;     // ���������� ������ ����� (Picture)
     DOUBLEPOINT UpRight;    // ���������� ������ �����
     DOUBLEPOINT DownRight;  // ���������� ������� �����
     DOUBLEPOINT DownLeft;   // ���������� ��������� �����
     DOUBLEPOINT UpLeftLast; // ���������� ��������� ����� (Picture)
   }
     LimitBorder;

  int LimitPlace ;   // ������� ���������

  enum LIMITTYPE
      {
        SOFT = 0,    // ������ ���������� ������
        HARD = 1,    // ���������� ����� ��������� �������
      };

  int LimitType  ;   // ������ ����������� SOFT/HARD

  enum LIMITDIRECT
      {
        LD_LEFT  = 1,
        LD_RIGHT = 2,
        LD_UP    = 3,
        LD_DOWN  = 4,
      };

  int LimitDirect;       // ������������ �������

  DOUBLEPOINT LimitSize; // ������� ����������� �����������
                         // ���������

  long Scale;            // �������, ��� �������� �������� ������
};


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++ ����� "����� �������������� ��������� ����������� �����" +++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectFrameFixed : public TMapSelectFrame
{
 public :

  // ������� ������ "����� ���������"
  TMapSelectFrameFixed(TMapTask * task, int ident);

  // ��������� ������ ��������� �� ������� ������
  void BuildFrame();

  // ����������� ����� �� ���� � ������� �����
  int Move(UINT /*modKeys*/, TPoint& /*point*/);

  // ���������� ����������� ������� ����������� ���������
  void SetFrameLimit(double width, double height, int place);

 protected :

  int LimitPlace ;       // ������� ���������

  DOUBLEPOINT LimitSize; // ������� ����������� �����������
                         // ���������
};


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++   ����� "����� ����������� �������������� ���������      +++
// +++                   ����������� �����"                     +++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectRotateFixed : public TMapSelectFrame
{
 public :

  // ������� ������ "����� ���������"
  TMapSelectRotateFixed(TMapTask * task, int ident);

 ~TMapSelectRotateFixed();

  // ��������� ������ ���������
  virtual void BuildFrame();

  // ����������/������� �� ����� ����� ���������
  virtual void PaintFrame();

  // ������������ �� ����� ����� ���������
  virtual int Paint(TDC& dc, bool erase, TRect& rect);

  // ���������� ����������� ������� ����������� ���������
  //  scale - ������� ����������� � �������
  void SetFrameLimit(double width, double height, int place, int scale);

  // ��������� �������������� (����� �����������) �� �������
  void Quit() { TMapAction::Quit(); }                   

 protected :

  PLACEDATA Vector;      // �������� �������
  PAINTPARM VectorForm;  // ��� ������� ������� �� ������
                         // (�������� ����� ���������)
  IMGLINE   VectorImage; // �������� ����� (������ ���������)

  DOUBLEPOINT LimitSize; // ������� ����������� �����������
                         // ���������

  DOUBLEPOINT Points[5];     // ������� ������� (������� ->)
  LONG VectorPointCount[2];  // ����� ����� � �����������

  int LimitPlace;        // ������� ���������
  int Scale;             // ������� ����������� � �������
};


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++ ����� "����� �������������� ��������� ����������� �����  +++
// +++             �� ����������� ����� ���������"              +++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectCenterFixed : public TMapSelectFrame
{
 public :

  // ������� ������ "����� ���������"
  TMapSelectCenterFixed(TMapTask * task, int ident);

  // ������� �� ������ ����� ������ �����
  virtual int LeftUp(UINT /*modKeys*/, TPoint& /*point*/);

  // ��������� ������ ���������
  void BuildFrame();

  // ���������� ����������� ������� ����������� ���������
  void SetFrameLimit(double width, double height, int place);

 protected :

  int LimitPlace ;       // ������� ���������

  DOUBLEPOINT LimitSize; // ������� ����������� �����������
                         // ���������
};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ ����� "����� ��������� ����������� �����" +++++++
// +++++++ (� ������� ������� ��������� �����������) +++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectFrameAndChange : public TMapSelectFrame
{
 public :

  TMapSelectFrameAndChange(TMapTask * task, int ident);

  // ������� ������          
 ~TMapSelectFrameAndChange();

  // ����������� ��� ������������� ������
  virtual void Setup() { Run(); }

  // ������� ������
  virtual int CallDialog() { return 0; }

  // ����������� ��� �������� ������
  virtual int CanClose() { return (DialogActive == 0); }

  // ����� �� ��������� ����� ������� �� �����
  virtual int CanSelectObject();

  // ����� �� ��������� ����� ����� �������
  virtual int CanSelectThisObject(TObjectInfo* info);

  // ��������� ����� � ��� ����� ���������� �������
  virtual void SetSelectObject(TObjectInfo* info) {}

  // ��������� � ���������� ��������� �������
  virtual int Commit();

  // ������ �������
  virtual int KeyDown(UINT /*key*/, UINT /*repeatCount*/, UINT /*flags*/);

  // ������� �� ������� ����� ������ �����
  virtual int LeftDown(UINT /*modKeys*/, TPoint& /*point*/);

  // ������� �� ������ ����� ������ �����
  virtual int LeftUp(UINT /*modKeys*/, TPoint& /*point*/);

  // ����������� ����� �� ���� � ������� �����
  virtual int Move(UINT /*modKeys*/, TPoint& /*point*/);

  // ��������� �� ������ ��������� �������
  virtual int Revert();

  // ����������� ����� ������ ������ ��������� �������������
  // �������� CallDialog
  virtual int Run();

  //  ���������� ������� �� ������� �����
  virtual int SelectObject(TObjectInfo* info);          

  // ����������� ����� �� ����
  void MoveFrame();

 public :

  int ChangeFlag;  // ���� ������:
                   //  0 - ����� ������ ���������
                   //  1 - ����� ��������� ������ ��������� �������
  int ChangeLeft;
  int ChangeUp;
  int ChangeRight;
  int ChangeDown;
  int ChangePos;

  int MapCursor;
  int DialogActive;

  DOUBLEPOINT BeginPos;  // ����� ��������� ������� ����� ��� �����������
  RECT* RectMetr;
  char* Regime;

  DFRAME PlaneFrame;  // ��������� ������� � ������
};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ ����� "����� ����� ����������� �����" +++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectPoints : public TMapSelectFrame
{
 public :

  // ������� ������ "����� �����"
  TMapSelectPoints(TMapTask * task, int ident);

  // ������� ������ "����� �����"
 ~TMapSelectPoints();

  // ��������� ���������� ������� ��� ������� ������� �����
  // ���������� ������������� ����� ������ ��������� ����� �����
  // ���� ��� �������� ���� - ���������� ��������� ������
  virtual int Run() { return 0; }

  /************************************************************
  *                                                           *
  *       ������ ��������� ���������� ������� ���� �����      *
  *                                                           *
  ************************************************************/

  // ������� � ������ ��������� �������� ������������
  virtual void Comment();
  virtual void CommentSelect(int count, int value = 0);

  // ������� �� ������� ������ ������ �����
  virtual int RightDown(UINT /*modKeys*/, TPoint& /*point*/);

  // ������� �� ������� ������ ������ �����
  virtual int RightUp(UINT /*modKeys*/, TPoint& /*point*/);

  // ������� �� ������� ����� ������ �����
  virtual int LeftUp(UINT /*modKeys*/, TPoint& /*point*/);

  // ����������� ����� �� ���� � ������� �����
  virtual int Move(UINT /*modKeys*/, TPoint& /*point*/);

  // ��������� �� ������ ��������� �������
  virtual int Revert();

 public :

  int ChoiceFlag;                  // 0 - ����� ���������, 1 - ����� �����
  long PointsCount;                // ����� ����������� �����
  int  SelectPoints;               // ������� �����
  DOUBLEPOINT  Fact[MAXPOINTS];    // ����������� ���������� � ������
};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++ ����� "����� ������� ����������� �����" ++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectSquare : public TMapAction
{
 public :

  // ������� ������ "����� �����"
  TMapSelectSquare(TMapTask * task, int ident);

  // ������� ������ "����� �����"
 ~TMapSelectSquare();

  // ��������� ���������� ������� ��� ������� ������� �������
  // ���������� ������������� ����� ������ ��������� ����� �����
  // ���� ��� �������� ���� - ���������� ��������� ������
  virtual int Run() { return 0; }

  /************************************************************
  *                                                           *
  *       ������ ��������� ���������� ������� ���� �����      *
  *                                                           *
  ************************************************************/

  // ������ : ����� �� ��������� ����� ������ ������� �� �����
  int CanSelectObject()  { return 0; }  // ������ !

  // ������� � ������ ��������� �������� ������������
  virtual void Comment();

  // ��������� � ���������� ��������� �����
  virtual int Commit();

  // ������ �������
  virtual int KeyDown(UINT key, UINT /*repeatCount*/, UINT /*flags*/);

  // ������� �� ������� ����� ������ �����
  virtual int LeftUp(UINT /*modKeys*/, TPoint& /*point*/);

  // ������� �� ������� ������ ������ �����
  virtual int RightUp(UINT /*modKeys*/, TPoint& /*point*/);

  // ����������� ����� �� ���� � ������� �����
  virtual int Move(UINT /*modKeys*/, TPoint& /*point*/);

  // ������������ �� ����� ������ �������
  virtual int Paint(TDC& dc, bool erase, TRect& rect);

  // ��������� �� ������ ��������� �������
  virtual int Revert();

  // �������������
  int AutoScrolling(DOUBLEPOINT* viewpoint);

  // �������� �����
  int AppendPoint();

  // ������� ��������� �����
  int DeleteLastPoint();

 public :

  TDataEdit Square;
  PLACEDATA SquareData;
  LONG      SquareCounts;

  DOUBLEPOINT LinePoints[3];
  PLACEDATA   LineData;
  LONG        LineCounts;

  PAINTPARM Form;       // ��� ������� ������� �� ������
                        // (���������� ����� 5/2 ���������)
  IMGDOT Image;         // �������� ���������� �����
};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ ����� "����� ��������� ����������� �����" +++++++
// +++++++ (� ������� ������� ��������� �����������) +++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectFrameChangeAndRotate :
             public TMapSelectFrame
{
 public :

  // ������ ������ � ������
  enum REGIMETYPE
      {
        RECTCHANGESIDE = 1,  // �������� ������� ������� (�� ����� �������)
        RECTCHANGE     = 2,  // �������� ������� ������� (�� ���� �������)
        RECTMOVE       = 3,  // ���������� ������
        ROTATE         = 4   // ������� ������
      };


  //  �����������
  //  frame - ��������� ������ ��������� (� ������)
  //          ��� frame = 0, �������� �������� �������������
  //          �� ������
  //  secondpoint - ������� ��������������� ������� ������ �����
  //                ���������� ������� �� ��������� ����� (frame)
  TMapSelectFrameChangeAndRotate(TMapTask *task, int ident,
                                 DFRAME *frame = 0, int secondpoint = 0);
  ~TMapSelectFrameChangeAndRotate();

  // ��������� �����
  int BuildFrameUnique();

  //  ��������� � ���������� ��������� �������
  virtual int Commit();

  // ������� �� ������� ����� ������ �����
  virtual int LeftDown(UINT /*modKeys*/, TPoint& /*point*/);

  // ����������� ����� �� ���� � ������� �����
  virtual int Move(UINT modKeys, TPoint& point);

  // ������� �� ������ ����� ������ �����
  virtual int LeftUp(UINT /*modKeys*/, TPoint& /*point*/);

  // ������ ����� �������� ��� ����� �������� (� ���������)
  int SetStationaryPoint(DOUBLEPOINT *point = 0);

  // �������� DimBorder � ��������� ��������
  int OffsetDimBorderAndRun(double dx, double dy);

  // ��������� DimBorder � ��������� ��������
  int ExtendDimBorderAndRun(double dx, double dy);

  // ��������� �� ���������: ���� �������� (� ��������) �
  //                         ����������(� ���������)
  // � ��������� ��������
  int RotateAndOffsetAndRun(double corner = 0, double distance = 0);

  virtual int Run(int view = 1) { return 0; }

 protected :

  // ���������������� ���������� ������
  void InitData(DFRAME *frame = 0, int secondpoint = 0);

  //  ���������������� �������� �����
  void InitBorder();

  // �������� ��������� ����� �� �������
  void MousePlace(int *side, int *corner, int *regime);

  // �������� ������ ������� �� �������
  int ChangeSide(int side);

  // �������� ������ ������� �� ����
  int ChangeCorner(double corner = 0);

  // �������� ������������ �����
  void ChangeFish();

  // ��������� �������� ��������� � ������
  void ChangePlaneFrame();

  //  ���������� �� ����� ����� ���������
  virtual int Paint(TDC& dc, bool erase, TRect& rect);

  // ���������� ������ �� �������
  virtual void PaintFrame();

  // ���������� �����
  void PaintFish(TDC *dc = 0, TRect *rect = 0);

  // ���������� ����� �������� ��� ����� ��������
  void PaintStationaryPoint(TDC *dc = 0, TRect *rect = 0);

  // ��������� �� ������ ��������� �������
  virtual int Revert();

 public :

 DOUBLEPOINT TotalMove;      // C���� ���������
 double      TotalCorner;    // Y��� �������� ���������
 DFRAME      PlaneFrame;     // �������� (� ������)
 DFRAME      ViewPlaneFrame; // �������� � ������� (� ������)

 DOUBLEPOINT StationaryPoint; // ����� �������� (��� �� ����� ��������)

 protected :

 DOUBLEPOINT DownPoint;  // ���������� ����� ������� (Map)
 DOUBLEPOINT UpPoint;    // ���������� ����� �������

 PAINTPARM FormFish;     // ��� ������� ��������� �� ������ (�����)
 PLACEDATA FrameFish;    // �������� ��������� �����
 IMGLINE   ImageFish1;   // �������� 1 �����
 IMGLINE   ImageFish;    // �������� �����

 PLACEDATA FrameStationary;  // �������� ��������� �����
 LONG PointCountStationary;

 struct BorderFish
    {
    DOUBLEPOINT UpLeft;     // ���������� ������ ����� (Map)
    DOUBLEPOINT UpRight;    // ���������� ������ �����
    DOUBLEPOINT DownRight;  // ���������� ������� �����
    DOUBLEPOINT DownLeft;   // ���������� ��������� �����
    DOUBLEPOINT UpLeftLast; // ���������� ��������� ����� (Map)
    };

 // ������� ���������� ������� ����� (����� ������ ������� ����)
 DOUBLEPOINT DimBorder[8];

 int IsStationaryPoint;       // ������ ��������� ������ ��������
 int IsCornerStationary;      // ������ ��������� ���� ��������
 double CornerStationary;     // ������������ ���� ��������

// ���������� ����� � �������� (����� ������ ������� ����)
 BorderFish Fish[8];

 // ���������� ����� �������� � ��������
 DOUBLEPOINT FishStationary[4];

 double Precision;

 DFRAME Frame;      // �������� �����, ���� ���� (� ������)

 int Regime;        // ����� ������ � ������
 int CommitFlag;    // ���� ���������� �������� �����
                    // (��� ���������� ������)

 int CornerNumber;  // ����� ���������� ���� (����� ������ ������� ����)
 int SideNumber;    // ����� ��������� ������� (���� ����� ���� ���)
 int Change;        // �������� ��������

 int IsSecond;      // ���� ��� ��������������� �������� ������
                    // ����� ���������� ������� �� ��������� �����

};
/*  

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ ����� "����� ��������� ����������� �����" +++++++
// +++++++ (� ������� ������� ��������� �����������) +++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectFrameSizeable : public TMapSelectFrameAndChange
{
 public :

  //  �����������
  //  frame - ��������� ������ ��������� (�������� � ������)
  TMapSelectFrameSizeable(TMapTask * task, int ident);

  // ������� ������          
 ~TMapSelectFrameSizeable();

  //  ������� � ������ ��������� �������� ������������  
  void Comment();

  // ��������� � ���������� ��������� �������
  int Commit();

  // ������� �� ������ ����� ������ �����
  int LeftUp(UINT , TPoint&);

  // ����������� ����� �� ���� � ������� �����
  int Move(UINT, TPoint& );

  int Run() { return 1; }

  // ����������/������� �� ����� ����� ���������
  void PaintFrame();

  //  ���������� �� ����� ����� ���������
  int Paint(TDC& dc, bool erase, TRect& rect);

  char RegimeOle;  
};
*/

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++ ����� "����� ���������� ��������� ����������� �����" +++
// +++  ���  "����� ������� ��������� ����������� �����"    +++
// +++    (� ������� ������� ��������� �����������)         +++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectFrameTurn : public TMapSelectFrameAndChange
{
  public :

  TMapSelectFrameTurn(TMapTask *task, int ident);

  virtual int Run();

  public :

  DFRAME SavePlaneFrame;
  DOUBLEPOINT Third;     // ������ �����
  double Angle;          // ���� �������� ��������� (� ��������)
  char TurnFrame;
  char SaveTurnFrame;

  // ������� �� ��������

  PAINTPARM PageForm;         // ��� ������� ��������� �� ������
                              // (���������� ����� 2/2 ���������)

  IMGDOT      PageImage;      // �������� ���������� ����� (������ ���������)

  PLACEDATA   PageFrame;      // �������� ������� �����
  DOUBLEPOINT PageLine[2];
  LONG        PagePointCount; // ����� �����, ����������� ��������

  double      PageWidth;      // ������ �������� � �����������
  double      PageHeight;

  double      PrintScale;     // ������� ������

  protected:

  // ��������� ������ ��������� �� ������� ������
  virtual void BuildFrame();

  virtual void PaintFrame();
  virtual int  Paint(TDC& dc, bool, TRect& rect);

  // ������� �� ������ ����� ������ �����
  virtual int LeftUp(UINT modKeys, TPoint& point);

  // ����������� ����� �� ���� � ������� �����
  virtual int Move(UINT mode, TPoint& point);

  // ��������� � ���������� ��������� �������
  virtual int Commit();

  // ������ �������
  virtual int KeyDown(UINT key, UINT repeatCount, UINT flags);
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++ ����� "����� ��������� � �������" ++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapSelectFrameAndSquare : public TMapSelectFrameAndChange
{
 public :

  // ������� ������
  TMapSelectFrameAndSquare(TMapTask * task, int ident);

  // ������� ������
 ~TMapSelectFrameAndSquare();

  // ��������� ���������� ������� ��� ������� ������ ��������
  // ���������� ������������� ����� ������ ��������� �����
  // ���� ��� �������� ���� - ���������� ��������� ������
  virtual int Run();

  /************************************************************
  *                                                           *
  *       ������ ��������� ���������� ������� ���� �����      *
  *                                                           *
  ************************************************************/

  // ����� �� ��������� ����� ������� �� �����
  virtual int CanSelectObject()
  {
   if (Regime && *Regime == AREA_SELECT_OBJECT)
     return 1;
   else
     return 0;
  }

  // ������� � ������ ��������� �������� ������������
  virtual void Comment();

  // ��������� � ���������� ��������� �����
  virtual int Commit();

  // ������ �������
  virtual int KeyDown(UINT key, UINT /*repeatCount*/, UINT /*flags*/);

  // ������� �� ������� ����� ������ �����
  virtual int LeftUp(UINT /*modKeys*/, TPoint& /*point*/);

  // ������� �� ������� ������ ������ �����
  virtual int RightUp(UINT /*modKeys*/, TPoint& /*point*/);

  // ����������� ����� �� ���� � ������� �����
  virtual int Move(UINT /*modKeys*/, TPoint& /*point*/);

  // ������������ �� ����� ������ �������
  virtual int Paint(TDC& dc, bool erase, TRect& rect);

  virtual void PaintFrame();

  // ��������� �� ������ ��������� �������
  virtual int Revert();

  // �������������
  int AutoScrolling(DOUBLEPOINT* viewpoint);

  // �������� �����
  int AppendPoint();

  // ������� ��������� �����
  int DeleteLastPoint();

 public :

  TDataEdit Square;
  HOBJ      SquareHOBJ;
  PLACEDATA SquareData;
  LONG      SquareCounts;

  DOUBLEPOINT LinePoints[3];
  PLACEDATA   LineData;
  LONG        LineCounts;

  PAINTPARM Form;       // ��� ������� ������� �� ������
                        // (���������� ����� 5/2 ���������)
  IMGDOT Image;         // �������� ���������� �����

  int FlagEscape;
};

#endif
