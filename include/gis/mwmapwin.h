
#if !defined(MWMAPWIN_H)
#define MWMAPWIN_H

#ifndef MWMACRO_H
  #include "mwmacro.h"
#endif

#ifndef MWFILEIN_H
  #include "mwfilein.h"     // ��������� INI - ������
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

// ������� ��� ����� �� �������� ��������
// (����������� ��������� ��� ������ ������ ����� �����!)
// name     - ������ ��� ���������� ���������� ������
// namesize - ������ ������ ��� ���������� (MAX_PATH)
// title    - ��������� ������� � ������ ����� ����������
// filter   - ������ ����� ����� ������
// flags    - ����������� ������ �������
// index    - ������� ����� ������ ���� ����� ��� �������� �������
// path     - ������� ���������� ��� �������� �������
// ���������� ����� ������ � ������ ����� ������ (>=0)
// ��� ������ ��� ������ �� ������ ����� -
// ���������� ������������� ��������
int OpenFile(char * name, int namesize,
#ifdef WIN32API  // 29/01/02
             TWindow * window,
#else
             void    * window,
#endif
             const char * title, const char * filter,
             int  flags,  int    index,
             const char * path);

// �������������� ���� ��� ������� ���������� �����
#define OFLAG_SAVE 0x0F0000000

// ���� ���������� ��������
#define SELECTCOLOR RGB(0xF0,0x20,0x90)   // 0x09020F0 - ����������


/******************************************************************
********************  ������� ��������� ***************************
*******************************************************************

    X map
  ^
  | (0,0) (������ ����������� "Picture")
  +---------------------------------------------------> X picture
  |                                                 ^
  |        (���������� ���� "Client")               |
  |   (0,0)                      X�                 |
  |     ----------------------->                    |
  |     |               |                           |
  |     |        x..... x  ���� ������������        |
  |     |        ....A. |                           |
  |     |        ...+.. |                           |
  |     |        ...... |                  �������� � ��������
  |     ---------x------x                  ������ ("RegionPix")
  |     |          ^                                |
  |     |          |                                |
  |     |         ������� �������� ������           |
  |     V                  ("Draw")                 |
  |       Y�                                        |
  |                                                 V
  +----------------------------------------------------> Y map
  |
  |  0,0 (������ ������ "Map" � ���������
  |       � "��������")
  |
  V              ���������� �.A � ������ X�,Y�; � ����������� X�,Y�
    Y picture     X� = Pix2Dis(RegionPix.X2 - Y�);
                  Y� = Pix2Dis(RegionPix.Y1 + X�);

******************************************************************/


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++ ����� "���� ����������� �����" ++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapWindow
{

public:

#ifdef WIN32API  // 29/01/02
    // ������� ������ "���� ����������� �����"
    TMapWindow(HWND hMain);
#else
    // ������� ������ "���� ����������� �����"
    TMapWindow(MSGHANDLER handler);
#endif

    // ������� ������ "���� ����������� �����"
    ~TMapWindow();

  /************************************************************
  *                                                           *
  *           ������ ���������� ����������                    *
  *                                                           *
  ************************************************************/

    // ��������� ��� ����������
    char * GetApplicationName();

    // ��������� ��� ����� "ini" ����������
    char * GetIniName();

    // ��������� ��� ����� "ini" �����
    const char * GetMapIniName()
#ifdef WIN32API  // 05/03/02
      { return MapDoc->GetMapIniName(); }
#else
      { return mapGetMapIniName((HMAP)MapDoc); }
#endif

    // ��������� ��� ����� "hlp" ����������
    char * GetHelpName();

    // ��������� ������� ���� �������� ����������
    int GetLanguage();

    // ���� ������ ��������� � ������� ����
    enum OPTIONLANGUAGE
     {
       ML_ENGLISH = 1,  // ����������
       ML_RUSSIAN = 2   // �������
     };

    // ��������� ��������� ������ ������������ (���������� ��� ���)
    // id - ������������� ������ (CM_MAPEDIT - ������ ���������, ...)
    // ���� ������ ��� - ���������� ����
    int GetPanelState(int id);

    // ��������� ���� � ���������� ����������
    char * GetPathShell();

    // ������� ���������� �������� ����� ����������� � ��������
    //   (X,Y � ����������� Windows)
    void GetPictureBorder(long& x, long& y);

#ifdef WIN32API  // 29/01/02
    // ��������� ������� ����������
    TPrinter* GetPrinter();

    // ������� ������ ��������� ��������
    void CmPrintSetup();

    // ��������� ������� ������ �������� ����������
    TModule * GetResourceModule();
#endif

    // ��������� ���������� dllname � ����� ����� ����� funcname
    // ��� ������ DLL ����������� � ���������� ����������
    // ��� ������ ���������� ����,
    // ���� message != 0 - ������ ��������� �� �����
    // �������� libinst �������� ������������� �����������
    // ���������� dllname
    FARPROC  LoadMapLibrary(const char * dllname,
                            HINSTANCE&   libinst,
                            const char * funcname,
                            bool message);

    // ��������� ��� ������������
    const char * GetUserName();

    // ��������� ��������� ��� ������ ������
    TASKPARM * GetTaskParm() {return (TASKPARM *) GetTaskParmEx();}
    TASKPARMEX * GetTaskParmEx();

    // ��������� ���������� ����������
    // ��� ������ ���������� ����                 // 18/09/03
    int CallMapLibrary(const char * dllname);


  /************************************************************
  *                                                           *
  *     ���������� ���������������� � ���������� ���������    *
  *                                                           *
  ************************************************************/

public:

   enum POINTTYPE      // ������ ����������� ��������� �����
    {
      PLANEPOINT      = 1,  // � ������ �� ��������� � ������������ � ���������
      MAPPOINT        = 2,  // � �������� �������� ����� (���������)
      PICTUREPOINT    = 3,  // � �������� �������� ������� �����������

      // ��-42
      GEORAD          = 4,  // � ��������
      GEOGRAD         = 5,  // � ��������
      GEOGRADMIN      = 6,  // � ��������, �������, ��������
     
      // WGS-84
      GEORADWGS84     = 7,  // � ��������
      GEOGRADWGS84    = 8,  // � ��������
      GEOGRADMINWGS84 = 9,  // � ��������, �������, ��������

      PLANE42POINT    = 10, // � ������ �� ��������� �� ��������� ����

      //��-90.11
      GEORADPZ90      = 11,  // � ��������
      GEOGRADPZ90     = 12,  // � ��������
      GEOGRADMINPZ90  = 13,  // � ��������, �������, ��������
      
      //���-2011
      GEORADGSK2011      = 14,  // � ��������
      GEOGRADGSK2011     = 15,  // � ��������
      GEOGRADMINGSK2011  = 16  // � ��������, �������, ��������
    };

    // ���������� ������������ ���������� �������� �����
    // � ��������� �������� ��������� (PICTURE,MAP,PLANE)
    void CalculateRectangular(POINT& point);

    // ������� ��������� ��������
    //   ���������:
    //    change  - ����������� ��������� �������� �������� ( > 0)
    //   ����������: 0 - ������� �� ���������, 1 - ������� ���������
    int ChangeScale(float change);

    // ������� ��������� �������� �� �������� �������
    // ����������: 0 - ������� �� ���������, 1 - ������� ���������
    int ChangeScaleByObject(TObjectInfo * info);

    // ������� ��������� �������� �� ��������� ���������� ��������
    // ����������: 0 - ������� �� ���������, 1 - ������� ���������
    int ChangeScaleBySelect();

   // ������� ��������� �������� �� ����������� ��������� � ������
   // ����������: 0 - ������� �� ���������, 1 - ������� ���������
   int ChangeScaleByFrame(DFRAME * frame);

    // �������������� ��������� ����� ��������� ������� (CLIENT)
    // � ���������� ����������� (PICTURE)
    POINT Client2Picture(POINT& point);

    // �������������� ��������� ��������������
    RECT Client2Picture(RECT& rect);

    // ��������� ���������� � �������������� ������� (Geo)
    // ��� ���������� �����������
    // ������������ ���������� ������� ����� � ��������
    // ���� �������������� ������� ��������� �� ��������������
    // �������� ��������� ������ ���� !
    // ����������� ��������� �������������� ��������� :
    // if (MapDoc->IsGeoSupported() != 0) { ��������������; }
    DOUBLEPOINT * GetGeoPoint(double height = 0);

    // ��������� ���������� � �������������� ������� (Geo)
    // ��� ���������� WGS84
    // ������������ ���������� ������� ����� � ��������
    // ���� �������������� ������� ��������� �� ��������������
    // �������� ��������� ������ ���� !
    DOUBLEPOINT * GetGeoWGS84Point()
     {
       return &WGS84GeoPoint;
     }

    // ��������� ���������� � �������������� ������� (Geo)
    // ��� ���������� �����
    // ������������ ���������� ������� ����� � ��������
    // ���� �������������� ������� ��������� �� ��������������
    // �������� ��������� ������ ���� !
    // ����������� ��������� �������������� ��������� :
    // if (MapDoc->IsGeoSupported() != 0) { ��������������; }
    DOUBLEPOINT * GetMapGeoPoint();

    // ��������� ���������� ������ �������� ���� �����
    POINT * GetPicturePoint();

    // ���������� ���������� ������ �������� ���� �����
    POINT * SetPicturePoint(POINT& point);

    // ��������� ���������� ������ �������� ���� ����� � ��������� � ������
    DOUBLEPOINT * GetMapWindowPoint();

    // ����������� �������� ����� ����� � ����� ������� ����
    // ���������� � ��������� � ������
    // ���������� ����� ��������
    DOUBLEPOINT * SetMapWindowPoint(DOUBLEPOINT * point);

    // �������������� ��������� ����� ����������� �����
    // � ���������� ��������� ������� ����
    POINT Picture2Client(POINT& point);

    // �������������� ��������� ����� �� ���������
    // � ����������� ��������� ������� (CLIENT)
    POINT PlaneToClient(DOUBLEPOINT &planepoint);

    // �������������� ��������� ����� �� �����
    // � ����������� ��������� ������� (CLIENT)
    POINT MapToClient(DOUBLEPOINT &mappoint);

    // ������������� ������� � ���������� ��� � �������
    // ���������� ����� ���������� ������
    // maxlength - ������ ������� ������ ( >= 14 !)
    char * RadianToGradString(double * rad,char * string,
                              int maxlength);

    // ������� ��������� ��������
    //   ���������:
    //          Scale - �������� �������, ������� ������ ��������
    //   ����������: 0 - ������� �� ���������, 1 - ������� ���������
    // free - ������� ������������� (�� ����������) ��������
    int SetMapScale(float scale, int free = 0);

    // ���������� ������ ����
    // ���������� ������������� ������� �������
    int SetMapCursor(int cursor = 0);

    // ���������� ����������� ������ ���� (IDC_WAIT, IDC_SIZE, ...)
    // ���������� ������������� ������� �������
    int SetWinCursor(char* cursor = 0);

    // ������ ������������� ����� � ���������� ���� � ������������� ������
    // �� �������� ����������� �������� (���������� �� ������ ��������
    // �� ���������� ����� � ������ ������)
    void SpaceInsert(char* string, char * format, double number);

public :

// ������������� ���������� ������� �����

POINT        PicturePoint; // ���������� � ����������� ����� (�������)
                           // �� �������� ������ ���� �����������
DOUBLEPOINT  MapPoint;     // ���������� � ���������� ������� ����� (��������)
                           // �� ������� ������ ���� ������ �����
DOUBLEPOINT  PlanePoint;   // ���������� �� ��������� (�����)
                           // �� ������� ������ ���� ������� ���������

// �������������� ���������� ������� �����

DOUBLEPOINT  GeoPoint;      // ���������� �� ��������� (�������)

DOUBLEPOINT  WGS84GeoPoint; // ���������� �� ��������� WGS84 (�������)

DOUBLEPOINT  PZ90GeoPoint;  // ���������� �� ��������� ��-90 (�������)

DOUBLEPOINT  GSK2011GeoPoint;  // ���������� �� ��������� ���-2011 (�������) 

protected :

DOUBLEPOINT MapWindowPoint; // ���������� ������ �������� ����
                            // ���� �� �����

  /************************************************************
  *                                                           *
  *           ���������� ������� ���������                    *
  *                                                           *
  ************************************************************/

public:

  enum PROCESS   // �������������� ���������
  {
    IDP_COMMENT     = 1,  // ����� ������������ ��������
    IDP_SCALECENTRE = 2,  // �������������� �� ������ ������
    IDP_LOCKMAP     = 4,  // ����������� ������ � ����������� �����
                          // (�� ��������� ����������� �����)
  };

  // ��������� ����������� ������ � ������ ���� MK_ ...
  int GetKeyStatus() { return KeyStatus; }
  int GetShiftStatus() { return (KeyStatus & MK_SHIFT); }

  enum SWITCH
  {
    ICP_OFF   = 0,  // ��������� ������
    ICP_ON    = 1,  // �������� ������
    ICP_CHECK = 2,  // ��������� ������
    OFF       = 0,  // ��������� ������
    ON        = 1,  // �������� ������
  };

  // "����������"/"�������" ����������� �����
  void LockMap()   { SetProcess(IDP_LOCKMAP,ON); }
  void UnlockMap() { SetProcess(IDP_LOCKMAP,OFF); }
  int IsLockMap()  { return CheckProcess(IDP_LOCKMAP); }

  // ��������� ������ �������� ��������
  int CheckProcess(int ident);

  // ���������� ������ �������� ��������
  int SetProcess(int ident, int mode);

  // ����������/��������� ������ �������� ��������
  // ���������� ������� �������� ������ �������� (0/1)
  int ControlProcess(int ident, int mode = ICP_CHECK);

  // ��������� ������� � ��������� ��������� ��������
  // title - �������� ��������
  void CreateProgress(const char * title);

  // �������� ������� ���������� (0 - 100)
  // ���� ������� ������ ����������� ������������� -
  // ���������� 0 !
  int SetProgressPercent(int value, const char * title = 0);

  // ������ ������� ���������� ��������
  void DeleteProgress();

  // ���������� ���������� ���� ���������
  virtual void SetNavigator(TMapAction * action) {};

  // ��������� ������� ����������� ���� ���������
  int IsNavigator() { return (Navigator != 0); }

  // ��������� - ������� �� �����-���� ����� �����           // 18/04/05
  virtual int IsActionActive() { return 0; }

protected :

 int    KeyStatus;            // ��������� ����������� ������ MK_ ...
 int    Process;              // ������ ���������� ����� �����

  /************************************************************
  *                                                           *
  *     ������ � ��������� ���������� �� ������� �����        *
  *                                                           *
  ************************************************************/

public :

  // ����������� �������� ������ � ������ � �� �����
  // � �������� �����������
  // ���� ��������� � ������ ��� - ���������� ����
  int AdjustData();

  // ������������� (1) / �������������� (0) �������� ���������� ������
  int LockAdjustData(int lock);              // 28/04/05

  // "������" � ��������� ������� � ������� ��������� �� �����
  virtual void ClearSelect() {}

  // ��������� - ����� �� �������� ������ �� ����� ?
  virtual int CanSelectObject() { return 1; }

  // ��������� - ����� �� �������� ������ ������ �� ����� ?
  virtual int CanSelectObject(TObjectInfo * /*info*/)
    { return 1; }

  // ��������� ������ �� ������ �� �����
  int IsObjectSelected(int real = -1)
   { return ((real & SelectFlag) != 0);}      // 20/03/02

  //  ������ ������� � ������� ����� (� ������� �������)
  virtual int SelectObject(TObjectInfo * info)
    { return 0; }

  // ��������� ������� � ���������� ������� � ������������ � �������
  // ��������� ������ ��� ��������� �������� �� �����
  // ���� info ��������� ����, �� ������� �������� �����������
  // �� �������� ��������� �������
  // ���� active �� ����� ���� - ��������� ������ ���������� ������� 
  // ���� ���������� ������� ��� - ������������ ����
  virtual int NextActiveObject(TObjectInfo * info, int active = 0)
    { return 0; }

  // ��������� ������� � ����������� ������� � ������������ � �������
  // ��������� ������ ��� ��������� �������� �� �����
  // ���� info ��������� ����, �� ������� �������� �����������
  // �� �������� ��������� �������
  // ���� active �� ����� ���� - ��������� ������ ���������� �������
  // ���� ����������� ������� ��� - ������������ ����
  virtual int PrevActiveObject(TObjectInfo * info, int active = 0)
    { return 0; }

  // ������ ������� � ������� frame (��������)
  TObjectInfo * WhatObject(TObjectInfo * info,
                           DFRAME * frame, int flag = WO_FIRST);

  // ����� ������� �� �������� ��������
  virtual int SearchObject(TObjectInfo * /*info*/,int /*flag*/, int /*type*/)
    { return 0; }

  // ����� ������� �� �������� ��������
  TObjectInfo * SeekObject(TObjectInfo * info,TMapSelect * select,
                            int flag = WO_FIRST|WO_INMAP);

  // ���������� ��������� ��������� ������
  // ����� ����� ��������� � ������� �������
  void SetLastSeekObject(TObjectInfo * info);

  // ���������� ��������� ������
  // ��������� ������ ������������� ����� ������� �� �����
  void SetSelectObject(TObjectInfo * info);

  // ���������� ������� �����,�� ������� ����������� �������� �����,
  // (� ���������) � ������ ����
  // ��� ������ ���������� ����
  // ����� - ���������� �������� ����� � ��������
  // � ��������� ������� ����
  POINT  ViewMapPoint(DOUBLEPOINT * point);

  // ���������� ������� �����,�� ������� ����������� �������� �����,
  // (� ������) � ������ ����
  // ��� ������ ���������� ����
  // ����� - ���������� �������� ����� � ��������
  // � ��������� ������� ����
  POINT  ViewPlanePoint(DOUBLEPOINT * point);

  // ���������� ������� �����,�� ������� ����������� �������� �����,
  // � ������������ ��������� ����
  // ���������� ��������� � �������� � ��������� �������
  // ��� ������ ���������� ����
  // ����� - ���������� �������� ����� � ��������             // 04/03/07
  // � ��������� ������� ����
  POINT  ViewMapPointInRect(DOUBLEPOINT * point, RECT  * rect, int update = 0);

  // ���������� ������� �����,�� ������� ���������� �������� ������,
  // � ������������ ��������� ����
  // ���������� ��������� � �������� � ��������� �������
  // ��� ������ ���������� ����
  // ����� - ���������� ������� ����� ������� ������� � ��������
  // � ��������� ������� ����
  POINT  ViewObject(TObjectInfo * info,RECT  * rect);

  // ��������� ������� �� �������������� ���������� �� ��������
  int GetDetailInfo() { return FlagDisplayDetailInfo; }

  // �������� ���� ������� �������������� ���������� �� ��������
  int ClearDetailInfo() { return (FlagDisplayDetailInfo = 0); }

  // ���������� ���� ������� �������������� ���������� �� ��������
  int SetDetailInfo(int flagdisplay)
     { return (FlagDisplayDetailInfo = flagdisplay); }

  // �������� ��������� ����� �� �����
  void ClearMarker();

  // �������� ��������� ����� �� �����
  void PaintMarker(HDC hdc,RECT& rect);
  void PaintMarker();

  // �������� ����� �� �����
  // point - ���������� � ���������
  void SetMarker(DOUBLEPOINT * point);

  // ��������� ���������� �����
  DOUBLEPOINT *GetMarkPoint() { return &MarkPoint; };

  // ��������� ������� ���������� �����
  int IsMarkedPoint() { return IsMarked; }

  // ��������� �������� �� ������� �� �����
  int IsViewSelected()
#ifdef WIN32API  // 29/01/02
     { return MapDoc->GetTotalSelectFlag(); }
#else
     { return mapGetTotalSelectFlag((HMAP)MapDoc); }
#endif

  // ���������� ��������� �������� �� �����
  // ���� ������ 0, ���������� �� ���� �� ���������
  void SetViewSelect(int select,
                     COLORREF color = 0);

  void PaintSelect(HDC hdc, RECT& rect);

  // ����������/�������� ������� ������ �������� �� �����
  // -1     - ���������� �����(�� ���� ������)
  // 0,1... - ����� �����,� �������� ������� ����������� �����
  int SeekScope(int scope);
  int SeekScope();

  // ����������/�������� ������� ������ �������� �� �����
  // view == 0 - ����� ����� ���� �������� �����
  // view == 1 - ����� ����� ������� ��������
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

  enum AREASEEKFLAGS         // ������ ������ �� �������          // 01/09/04
  {
    AS_NO     = 0,    // �� ��������� ����� �� �������
    AS_RUN    = 1,    // ��������� ����� �� �������
    AS_SELECT = 2,    // ������� ������� ������
    AS_FRAME  = 4,    // ��������� ����� �� �����
  };

  // ����������/�������� ����� �������� �� �������� �������
  // area = 0 - �� ��������� ����� �� �������
  // area = 1 - ��������� ����� �� �������
  // area = 2 - ��������� ����� �������
  // area = 4 - ��������� ����� �� �����
  int AreaSearch(int area);
  int AreaSearch(){return AreaSeekFlag;}

  // ���������� ������� ������
  // ��� ������ ���������� "0"
  TObjectInfo * PutSearchArea(TDataEdit * data);    // 16/10/02

  TObjectInfo * PutSearchArea(TObjectInfo * info);

  // ��������� ������� ������                      // 24/11/00
  TObjectInfo * GetSelectArea(void) {return (TObjectInfo *)&SelectArea;}

  // �������� ����������� �� ������� ������:
  // 0 - ������� �����������
  // 1 - ������� �����������
  int IsAreaSelected()
     {
        return (SelectArea.Data.IsCorrect() &&
                (SelectArea.Data.PointCount() >0) );
     }

  // ��������� ������� ������ ��� �����������       17/11/00
  TObjectInfo * GetAreaShow(void) {return (TObjectInfo * )&AreaShow;}


  /************************************************************
  *                                                           *
  *           ���������� ������� ������������                 *
  *                                                           *
  ************************************************************/

  // ���������������� ������� ���������

  void InitMessageTable();

  // ��������� ��������� ������ �� ����� ��������

  int LoadString(int id, char * buffer, int size);

  // MessageBox � ��������� �� ��������

  int MessageInfo(int idmessage, int idtitle);
  int MessageError(int idmessage, int idtitle);
  int MessageQuest(int idmessage, int idtitle);

  // ������� ��������� � ������ ���������
  // ��� ������ ��������� text = 0

  void SetMessage(const char * text);

  // ������� ��������� � ������� ������� � ��������� �� ��������
  // ��� ������ ��������� id = 0

  void SetMessage(int id);

  // ������� ��������� � ��������� ����

  void SetWindowTitle(const char * message);

  // ������ ��������� �� ��������� ����

  void ClearWindowTitle();

  // ������������ �������� �������
  // ��� ������ ���������� ���� (��� ������� ��� ����� ������ 100 ����)

  char * ObjectComment(TObjectInfo * info,char * comm,int length);

 // ������� ��������� � ��������� ����

 void SetObjectComment(TObjectInfo * info);

  // ������������ �������� �����

  void MapComment();

  // ������� � �������������� ������� �������� � �����

  void CommentMessage();

  // ����� ��������� ����� � ������� ������� (����������,������������)
  // point - ���������� � ��������� ������� ����

  void CommentPoint(POINT & point);

  //  ����� ��������� ����� � ������� ������� (���������� �����)

  void PointToString(DOUBLEPOINT * point,
                     int place,
                     char *string, int maxlength);

  //  ����� ��������� ����� � ������� ������� (���������� �����) ����������� �������
  // ������ ���������� ��� ����������� ����� ��������
  void PointToString(char *string, int maxlength);

  // �������� �������������� �������

  void EraseComment();

  // ������� ��������� � �������������� �������

  void SetComment(int type,const char * message);

  // ���������� ������ "HELP"
  // ident - ������������� �������
  // check - ������� �������� ���������� ������� HELP,
  // ���� ����� 0 - �������������� ����� HELP

  int ViewHelp(int ident, int check = 0);
  int ViewHelpEx(const char * help, int ident, int check = 0);

  // ������ ������ ��� ������� id
  // ��� ������ ���������� ���� (�� ������� ������)

  int PressButton(int id);

  // ������ ������ ��� ������� id

  void ReleaseButton(int id);

  // ���������� ����������� ������ ��� ������� id

  void EnableButton(int id, int enable = 1);               // 30/01/07

  // �������� ����������

  const char * GetViewName() {return GetApplicationName();}

  // ������������ �������� ���� �����

  char * GetMapType();

  // ��������� ���������� ������������ �������� �� ���� ������

  int ViewCount(int update = 0);

  // ��������� ���������� ���������� ��������

  int MarkCount(int update = 0);


public :

  enum VIEWTYPE  //  ���� ����������� �����
   {
     VIEW_NORMAL         = 1, // ������� (��������) �����������
     VIEW_SCHEMATICAL    = 2, // ����������� �����������
     VIEW_PRINTER        = 3, // "����������" �����������
     VIEW_PRINTERCONTOUR = 4  // "����������" ����������� �����������
   };

 int ViewType;              // ������ ����������� �����

 int PlaceSystem;           // ������� ������� ����������� ���������

 int FlagDisplayDetailInfo; // ������� ���� ��������������
                            // ���������� �� �������
 int MarkPointSwitch;       // ��������� ����������� ��������� ������� ����� ������� // 17.02.2000
                            // 0 - �� ����������� ��������� ������� ����� �������
                            // 1 - ����������� ��������� ������� ����� �������

 int AreaSeekFlag;          // ���� ������ �� �������� �������

 TMapAccess *  MapDoc;      // ��������� �� ������ ������ ���������-����� // 05/03/02
 TObjectInfo*  ObjectInfo;  // ��������� ������ �����
 TMapSelect    FindSelect;  // ������� ��������� ��������

#ifdef WIN32API  // 29/01/02
 TWindow *
         ApplicationWindow; // ��������� �� ������� ���� ����������,
                            // �������� ��� �������� ��������
#else
 MSGHANDLER MessageHandler; // ���������� ���������
#endif

 int TotalSeekSelect;       // ����� �������� ��������
 int TotalViewSelect;       // ����� ���������� ��������

 protected :

 int          SelectFlag;  // ������� ������ ������� �����

 char HelpName[256];       // ��� Help-�����

 DOUBLEPOINT MarkPoint;    // ���������� ���������� �����
 int IsMarked;             // ������� ��������� �����

#ifdef PANPROF
 char TypeName[48];        // �������� ���� �����
#else
 char TypeName[40];        // �������� ���� �����
#endif

 COLORREF SelectColor;     // ���� ��������� ��������
                           // 21/02/06 
 int      IsSelectTimer;   // ������� ���������� ������� ��������� ��������

 TObjectInfo  WorkInfo;    // �������������� ������

 PAINTPARM    SelectImage; // ������ ��������� �������

 IMGDOT       SelectLine;  // ������ �������� ��� ��������� ������
 IMGOBJECT    SelectPoint; // ������ �������� ������ ��� �������

 TObjectInfo  SelectArea;  // ������������� ������� ������     19.01.99
 TObjectInfo  AreaShow;

 int          IsAdjustLock; // ������� ���������� ���������� ����� �� �������

public :

  // ���������/���������� ������� ��������� �������� �� �����

  int GetThickOfSelectObject() { return MKM2PIX(SelectLine.Thick); }
  void SetThickOfSelectObject(int thick)
     { SelectLine.Thick    = PIX2MKM(thick); 
       MapDoc->SelectThick = SelectLine.Thick;          // 07/10/2002
     }

  // ���������/���������� ����� ��������� �������� �� �����

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

  COLORREF  ColorOfSelectObject;    // ���� ���������� �������
  COLORREF  ColorOfSelectedObjects; // ���� ��������� ��������
  COLORREF  ColorOfSetObjects;      // ���� ��������� ������ ��������  04/05/00

  /************************************************************
  *                                                           *
  *     "������� ��������� ��� ����������� �����"             *
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

  // ��������� ��������� �������� ���� ����������
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

  // ��������� ��������� ���� �����
  int MapWindowPort(int command, intptr_t parm = 0);

  void Invalidate(int erase = 0);

  void InvalidateRect(RECT& rect,int erase = 0);

  // �������� ������� ����, �������� �������������� ������������
  void InvalidateRectPlane(DFRAME * frame,int erase = 0);

  void UpdateWindow(RECT * rect = 0);

  void ScrollBy(int dx, int dy);

  // ���������� ������� ���� ��� ��������� ���������� �����
  // (������� ����� �����������)
  virtual void Refresh(RECT * rect = 0);
  void RefreshPlane(DFRAME * frame = 0);

  // ���������� ������� ���� ��� ��������� ���������� �����
  // (������� ����� �����������)
  // �� ������� PostMessage ("�������� Invalidate")
  void PostRefresh(RECT * rect = 0);
  void PostRefreshPlane(DFRAME * frame = 0);

  // ��������� ��� ����� ���������
  const char * GetDocPath()             // 20/06/02
   { if (MapDoc) return MapDoc->MapDocName;
     else return "";
   }

  // ������� ��� ����� �� �������� ��������
  // ���������� ����� ������ � ������ ����� ������ (>=0)
  // ��� ������ ��� ������ �� ������ ����� -
  // ���������� ������������� ��������
  int OpenFile(char * name, int namesize,
               const char * title, const char * filter,
               int  flags,  int    index,
               const char * path);


 // ��������� ������������� ���������
 // ���� ��������� ���������� ���������� �� ����
 virtual int OnMessage(long int msg, long int p1, long int p2, int * retcode)
          { return 0; }

 // ������� ������                                 // 27/05/02
 void CreateMapTimer(int ident, int period);

 // ������� ������
 void DeleteMapTimer(int ident);

 // ����������� ����� �� ���� � ������� �����
 virtual int OnMove(UINT modKeys, POINT& point)      // 02/05/06
          { return 0; }

protected :

#ifdef WIN32API  // 29/01/02
 TModule * Resource;          // ������ �������� ��������
#endif

 char WindowComment[260];     // ��� ����� INI ��� ���������

 MAPOBJDESCEX LastSeekObject; // ��������� ��������� ������

 int Language;                // ��� ����� ���������

 TASKPARMEX TaskParm;         // ��������� ��� ������ ������

 HWND HMainWindow;            // ������������� �������� ���� ����������

 TMapAction * Navigator;      // ���������� ���� ���������

 int UpdateMode;              // ����� ���������� ������

 RECT RefreshRect;            // ������� ���������� ������

 GRIDPARM GridParm;           // ��������� ���������� ������������� �����
 long int GridActive;         // ������� ����������� �����
 long int GridPoint;          // ������� ������ ����� ����� � ����� �����
 double   GridStep;           // ������� ��� �����

public:

 long int IsInvalidate;       // ������� ��������������� ���������� ����
 int IsSizeChanged;           // ������� ��������� �������� ����
#ifndef WIN32API
 int TimerSelectFlag;         // ���� ��������� ���������� ��������:
                              // 0 - �� ������ �������� � :OnPaint, 1 - ������
#endif
 
 struct TCreateObjectParm{ // ��������� ��� ������������ �������
    TCreateObjectParm(): Mode(-1), incode(-1), MapNumber(-1){}
    long int Mode  ;             // ����� ��������
                                 // �� MED_KEY1 �� MED_KEY14
				 // == -1 - ������ �� ���������
    long int incode;               // ��� ������������ �������
    long int MapNumber;          // ����� �� ������� ��������� ������
 } CreateObjectParm;
 
};

#endif  // MAPWIN_H

