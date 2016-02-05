
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
  char* lpDib;               // ��������� �� ������� ������� DIB

  int DibWidth;              // ������ ������� ������� (� ������)
  int DibHeight;             // ������ ������� �������
  int DibElementSize;        // ������ �������� (� ������) 3 ��� 4

  int VisualType;            // ��� ������������
  int Reserve;
}
  DIBCONTEXT;

// ������� ���������������� ����
typedef struct SITCHAIN
{
  SITCHAIN() : Site(), Select(), Seek(), Real(), Active() { Next,Back = 0; RealMode = 0;}

  SITCHAIN*  Next;           // ��������� �� ��������� ���������
  SITCHAIN*  Back;           // ��������� �� ���������� ���������

  TSite      Site;           // ���������������� �����
  TMapSelect Select;         // ������� �����������
  TMapSelect Seek;           // ������� ������
  TMapSelect Real;           // ����� ������� �������� �� �����
  TMapSelect Active;         // ������� ������ ��'����� ��� ��������� 

  int        RealMode;       // ��������� ����� ��� �����
  int        ViewOrder;      // ������� ����������� (0 - ��� ������, 1 - ��� ������) 
#ifdef LINUXAPI    
  unsigned
      char  ArrayIndex[256]; // ������ �������� ������������ ������
#endif
}
  SITCHAIN;

// ���������� ������� Rst, Mtr, Mtq ������  
// =========================================================
typedef struct RMFCHAIN
{
  // ����� ��� ����
  RMFCHAIN() : Colors(), Rmf() { Next = 0; Back = 0; dH = 1;}

  RMFCHAIN*  Next;            // ��������� �� ��������� ���������
  RMFCHAIN*  Back;            // ��������� �� ���������� ���������

  int        View;            // ������� ��������� = ��� ����� (0-5)     
  int        ViewOrder;       // ������� ����������� (0/1 - ���/��� ������)
  int        MaskType;        // ��� ����� (0-8)
  int        Free;

  DFRAME     Frame;              // �������� � ������ (��������)
  DFRAME     FrameMeters;        // �������� � ������ (�����)
  double     Scale;              // ������� ������
  double     Precision;          // �������� ������
  double     MeterInElement;     // Scale / Precision
  double     Element;            // ����������� �������� (��� RSTSHOW)
  unsigned
  char       ArrayIndex[256];    // ������ �������� ������������ ������

  long int   TopScale;           // ����������� �������� ������� ������� ��������� 
  long int   BottomScale;        // ����������� �������� ������ ������� ���������  

  // ��� Rst
  int       Location;            // ������� �������� (0/1)
  int       InvisibleColors;     // ����� �������������� ������ (�� ��������)
  unsigned
  char      IndexVisible[256];   // �������� ����������� ������ (0/1)

  // ��� Rst � ������ �������
  TBaseColors Colors;            // ����� ����������� ������

  // ��� Mtr
  double    MinHeightValue;      // ����������� � ������������ ��������
  double    MaxHeightValue;      //  ����� � ������� (� ������)

  double MtrMinHeight;         // ���. � ����. ������ ���� �������
  double MtrMaxHeight;         // � �������� ������� �������

  double dH;                   // ��������, �������� ��������� ����� �������
                               // (��� ���������� ������� � �������)
  // ��� Mtr � ������ �������
  int    TypeHeight;           // ��� ����� (���=1,���=0)

  // ��� Mtq
  int    MtqShadow;            // ���� ������� ��������  

  // ����� ����� ������
  TRmf      Rmf;
}
  RMFCHAIN;


// ������� ���������� � ������e  
// =========================================================
typedef struct _DLLCLASS CHAININFO
{
  CHAININFO() { Count = 0; Begin = 0; CurrentNumber = 0; }

  int         Count;         // ���������� �������
  RMFCHAIN*   Begin;         // ������ ����� �������
  int         CurrentNumber; // ����� �������� ������� � �������
}
  CHAININFO;

typedef RMFCHAIN RSTCHAIN;
typedef RMFCHAIN MTRCHAIN;

#ifndef HIDEMTL
// ������� MTL-������           
typedef struct MTLCHAIN
{
  MTLCHAIN() : Mtl() { Next = 0; Back = 0; dH = 1;}

  MTLCHAIN* Next;            // ��������� �� ��������� ���������
  MTLCHAIN* Back;            // ��������� �� ���������� ���������

  int       Mode;            // ����� ������� (Read/Write)
  int       Share;           // ����� ���������� ������

  int       View;            // ������� ��������� = ��� ����� (0-5)     
  int       ViewOrder;       // ������� ����������� (0/1 - ���/��� ������)
  int       MaskType;        // ��� ����� (0-8)
  int       Transparent;     // ��� ����� ������� (�� 0 �� 100 ) 

  DFRAME    Frame;           // �������� � ������ (��������)
  DFRAME    FrameMeters;     // �������� � ������ (�����)
  double    Scale;           // ������� ������
  double    Precision;       // �������� �������
  double    MeterInElement;  // Scale / Precision
  double    Element;         // ����������� �������� (BaseScale / Precision)
  unsigned
      char  ArrayIndex[256]; // ������ �������� ������������ ������

  double    MinHeightValue;  // ����������� � ������������ ��������
  double    MaxHeightValue;  //  ����� � ������� (� ������)
  double    BotLevelHeight;  // ������ ������� ������ ������� (� ������)
  double    MaxSummaryPower; // ������������ ��������� ��������
                             // ����� ������� (� ������)  

  double MtrMinHeight;       // ���. � ����. ������ ���� �������
  double MtrMaxHeight;       // � �������� ������� �������

  double dH;                 // ��������, �������� ��������� ����� �������
                             // (��� ���������� ������� � �������)

  long int   TopScale;       // ����������� �������� ������� ������� ���������  
  long int   BottomScale;    // ����������� �������� ������ ������� ���������  

  int       LayerCount;      // ���������� �����

  TMtl      Mtl;             // M������ �����
}
  MTLCHAIN;

#endif      // !HIDEMTL


// ������� TIN-������          
typedef struct TINCHAIN
{
  TINCHAIN() : Tin(){ 
     Next = 0;
     Back = 0;
     View = 1;  // ����������� ������
     ViewOrder = 0; // ��� ������
  }

  TINCHAIN* Next;              // ��������� �� ��������� ���������
  TINCHAIN* Back;              // ��������� �� ���������� ���������

  int        View;             // ������� ���������
  int        ViewOrder;        // ������� ����������� (0/1 - ���/��� ������)
  
  TTin      Tin;               // ������ ���
}
  TINCHAIN;


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ����� ������: ����������� ����� + ����� ++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TMapControl : public TPaintMetric
{
public:

  // �������������/�������� ������ �����
  TMapControl();

  ~TMapControl();

  // ������� ��� ������
  void Close(void);

  // ���������� ������� �������� ������
  int IsActive();

  // ��������� �������� �����
  TMap * ActiveMap()
     { return GetMap(ActiveMapNumber()); }

  // ���������/���������� ����� �������� �����
  int ActiveMapNumber();

  int ActiveMapNumber(int number)
     {
       if ((number > SiteCount()) || (number < 0))
         return 0;
       return SitCurrentNumber = number;
     }

  // ��������� �������� �������� ����� �� ������
  // ���� ����� ����� 0, ������������ �������� "������� �����",
  // ����� - �������� ��������������� ���������������� �����
  // ��� ������ ������������ ������ ������
  const char * MapSheetName(int number = 0);

  // ��������� �������� �����
  // ���� ����� ����� 0, ������������ �������� "������� �����",
  // ����� - �������� ��������������� ���������������� �����
  // ��� ������ ������������ ����
  TMap * GetMap(int number = 0);

  // ��������� �������� ����� ����� �� ������
  // ���� ����� ����� 0, ������������ �������� ����� "������� �����",
  // ����� - �������� ����� ��������������� ���������������� �����
  // ��� ������ ������������ ������ ������
  const char * MapFileName(int number = 0);

  // ��������� ������� ������ �������� ��� �����������
  // ���� ����� ����� 0, ������������ ������� "������� �����",
  // ����� - ������� ��������������� ���������������� �����
  // ��� ������ ������������ ����
  TMapSelect * GetSelect(int number = 0)
     { return GetViewSelect(number); }

 // ************************************************************
 //                                                            *
 //            ��������������� ����� � �����������             *
 //                                                            *
 // ************************************************************

public :

 // �������� ������� ����������� �����
 double ChangeViewScale(double change);

 // ��������� ��������� ������� �� ������� ���������
 // ... 100000,200000,500000, ...
 long GetNewShowScale(long scale);

 // ���������� ����������� ��������������� �����
 double SetViewScale(double scale);

 // ��������� ������� ������� �����������
 long GetShowScale() { return ShowScale; }
 double GetRealShowScale();

 // ���������� ������� ����������� �����
 long SetShowScale(long scale);

 // ���������� �������� ������
 int ShowData();

 // ����������� ����� �������� ������ �����
 void SetRegion();

 // ��������� ������� ������� �����������
 // (��������������� �� �����, ��� ���������� ����� - �� �������,
 //                            ��� ���������� ������ - �� ������)
 long GetBaseScale() {return BaseScale;}


 // ************************************************************
 //                                                            *
 //            ������ � "������� �����"                        *
 //                                                            *
 // ************************************************************


public :

  // ������� ��������� ������
  // ��� ������ ���������� ����
  int OpenMap(const char * mapname, int mode);

  // ������� ��������� ������
  void CloseMap(void);

  // ��������� ���� ����������� ��� ������ ��������
  int SetVisualType(int type);
  int GetVisualType() { return (int)VisualType; }

  // ���� ������������ ��������
  enum VISUALTYPE {FILL            = VT_SCREEN,
                   SKELET          = VT_SCREENCONTOUR,
                   FILLPRINT       = VT_PRINT,
                   GLASSPRINT      = VT_PRINTGLASS,
                   CONTOURPRINT    = VT_PRINTCONTOUR,
                   FILLPRINTDIB    = VT_PRINTRST,
                   GLASSPRINTDIB   = VT_PRINTGLASSRST,
                   CONTOURPRINTDIB = VT_PRINTCONTOURRST};

  // ��������� �������� ������ ������� ��� ����������� ��������
  int SetColorModel(int colorModel);
  int GetColorModel() { return (int)ColorModel; }


  // ************************************************************
  //                                                            *
  //      ���������� ������� � "��������� ����������� �����"    *
  //                                                            *
  // ************************************************************

public :

 // ������� ���������� ����� ����������� �������� �������������� �����
 // number - ����� ������������� �����
 // type   - ��� ���������� (������� ��������� ...)
 // ��� ������ ���������� ����

 int OpenTransaction(int number, int type);

 // ������� ���������� ����� ����������
 // ������ ��������������� �������� �������������� �����
 // number - ����� ������������� �����

 void CloseTransaction(int number);

 // ���������� ����� ������� ���������� � ��������������
 // �����

 int SetChangeCall(CHANGECALL call, long int parm);

 // ��������� - ���������� �� ����� ������� ����������

 int IsChangeCall() { return (ChangeCall != 0); }

 // ��������� ������� ������� �����

 long GetMapScale();

 // ��������� ����� ����� � �������
 // ��� ������ ���������� -1

 int _fastcall GetMapNumber(TMap * map);

 // ������ �������� �������� ��������� ����� �� ������

 TMapRsc * GetResource(int number = 0);

 // ������ ������� ������ �������� ��� ������������

 TMapSelect * GetViewSelect(int number = 0);

 // ������ ������� ������ �������� ��� ������

 TMapSelect * GetSeekSelect(int number = 0);

 // ������ ����� ������� �������� �� �����

 TMapSelect * GetRealSelect(int number = 0);

 // ����������� ����� ������� �������� �� �����

 void AdjustRealSelect(int number,int force = 0);

 // ������, ������������ ������� ������ ��������
 // ������ � �������,���������,��������� �� �������� �����,����������
 // WO_CANCEL - ������ ������ � ���������� ��������� (�����,����������)
 // WO_INMAP - ������ � �������� �����
 // (� �.�. ���������������� => object->Map)

 enum SEEKTYPE { WO_FIRST = 0, WO_LAST = 2,
                 WO_NEXT  = 4, WO_BACK = 8, WO_PREV = 8,
                 WO_CANCEL = 16,
                 WO_INMAP  = 32, WO_VISUAL = 64};

 // �������� object �������� ����� ���������, � ������� �����
 // ������� ��������� ������ (���� ����� ������������ ��� ��������
 // ����������).
 // frame - ������� ������ � ���������

 MAPOBJDESC * _fastcall WhatObject(MAPOBJDESC * object, DFRAME * frame,
                                   int flag = WO_FIRST,
                                   TMapSelect * select = 0);

 // ����� ������� �� ��������� ���������� �������
 // ��� ������ ���������� ����

 MAPOBJDESC * _fastcall SeekObject(MAPOBJDESC * object,KEYSELECT * select,
                                   int flag = WO_FIRST);

 // ����� �������� �� �������� �������� ����� ���� ��������
 // ���� ������ �� ������ - ���������� ����

 MAPOBJDESC * _fastcall SeekObject(MAPOBJDESC * object,TMapSelect * select,
                                   int flag = WO_FIRST);

 // ����� ������� �� ����������� ������ � �������� ����� �����
 // ��� ������ ���������� ����

 int _fastcall SeekObjectInList(TMap * map, int list,
                                long key, int flag);

 protected :

 // ����� �������� �� �������� �������� ����� ���� ��������
 // ���� ������ �� ������ - ���������� ����

 MAPOBJDESC * _fastcall SeekObjectInMap(MAPOBJDESC * object,TMapSelect * select,
                                        int flag = WO_FIRST, int nMap = 0);


 // ����� �������� �� �������� �������� ����� ������������ ��������
 // (����������� �������� ������� � ��������� �� ���������� "Select")
 // ���� ������ �� ������ - ���������� ����

 MAPOBJDESC * _fastcall SeekViewObjectInMap(MAPOBJDESC * object,TMapSelect * select,
                                            int flag = WO_FIRST, int nMap = 0);

 // ����� ������� �� ��������� ���������� ������� � �����
 // ��� ������ ���������� ����

 MAPOBJDESC * _fastcall SeekObjectInMapByKey(MAPOBJDESC * object,
                                             KEYSELECT * select,
                                             int flag, int nMap);
 public :

 TMap       Map;          // ��������� �����

 TMapSelect Select;       // ������� ������ ��'����� ��� �����������
 TMapSelect Seek;         // ������� ������ ��'�����
 TMapSelect Real;         // ����� ������� ��'����� �� �����
 TMapSelect Active;       // ������� ������ ��'����� ��� ��������� 

 long int ShowScale;      // ������� ������� ����������� �����
 int      RangeScale;     // ���� �� ������� ����������� ���� ���
                          // �������� �������� �����
 int      ViewSeekFlag;   // ���� ������ ����� ������� ��'�����
 int      RealMode;       // ��������� ����� ��� �����

  // ************************************************************
  //                                                            *
  //        ������ � "���������������� ����������� �����"       *
  //                                                            *
  // ************************************************************

 public :

  // ��������� ����� �������� ���� (���������� � �������)
  // ��� ������ ���������� ����

  int IsSiteActive() { return (GetSiteCount() > 0); }
  int GetSiteCount() { return SiteCount(); }
  int SiteCount() { return SitChainCount; }

  // ������� ����� �� �� ����������������� ������ � ������
  // ���� ����� ����� ���� - ����������� ��� �����

  void CloseSite(int number = 0);

  // ��������� ������� ������� �� ������
  // ��� ������ ������������ ����

  SITCHAIN* GetSiteChain(int number);

  // ������� ����� (�������� � �������)
  // ���������� ����� ����� � �������
  // ��� ������ ���������� ����

  int OpenSite(const char * name, int mode);

  // ���������/���������� ������� ��������������� ����� �� ������
  // ��� ��������� ���������� ������ ��������
  // ��� ������ ������������ -1

  int MapEdit(int number, int flag = -1);

  // ���������/���������� ������� ��������� ����� �� ������
  // ��� ��������� ���������� ������ ��������
  // ��� ������ ������������ -1

  int MapVisible(int number, int flag = -1);

  // ���������/���������� ������� �����������  
  //  (0 - ��� ������, 1 - ��� ������)
  // ��� ������ ���������� -1
  int MapViewOrder(int number, int order = -1);

  // ���������/���������� ������� ���������� ������ ������� �����
  // ��� ��������� ���������� ������ ��������
  // ��� ������ ������������ -1

  int MapInquiry(int number, int flag = -1);

  // �������� ����������� ����������� ��        
  // oldNumber - ����� ����� � �������
  // newNumber - ��������������� ����� ����� � �������
  //  ��� ������ ���������� 0
  int ChangeOrderSiteShow(int oldNumber, int newNumber);

public :

 int         SitChainCount;    // ���������� �������
 SITCHAIN *  SitChainBegin;    // ������ ����� �������
 int         SitCurrentNumber; // ����� �������� �����

 int         ViewMapNumber;    // ������������ ����� ��� -1
 int         ViewListNumber;   // ������������ ����  ��� -1
 int         ViewObjectNumber; // ������������ ������ ��� -1

  // ************************************************************
  //                                                            *
  //            ������ � "��������� ����������� �����"          *
  //                                                            *
  // ************************************************************

public :

  // �������������� ����� �� ������� ��������� ������
  // ��� ������ ���������� ����

  RSTCHAIN*  ActiveRst(int number) { return GetRstChain(number); }

  // ������� ��������� ������ (�������� � ������� �������)
  // ���������� ����� ��������� ����� � ������� �������
  // ��� ������ ���������� ����

  int OpenRst(const char * name, int mode);

  // ������� ��������� ������ (�������� � ������� �������)
  // ��� ������ ���������� ����

  int ChangeRst(RSTCHAIN * chain, const char * name, int mode = 0);

  // ������� ��������� ������ (������� �� �������)
  // number - ����� ���������� ����� � �������
  // ���� number == 0, ����������� ��� ��������� ������

  void CloseRst(int number = 0);

  // ��������� ����� �������� ������� (���������� � �������)
  // ��� ������ ���������� ����

  int GetRstCount() { return RstCount(); }
  int RstCount()    { return RstChain.Count; }
  int IsRstActive() { return (RstCount() > 0); }

  // ��������� ������� ������� �� ������
  // ��� ������ ������������ ����

  RSTCHAIN* GetRstChain(int number);

  // ��������� ����� ������� �� ����� �����         
  // ��� ������ ������������ ����

  int GetRstNumberByName(const char * name);

  // ��������� ����� ��� ����������� �����

  TRmf * GetRstClass(RSTCHAIN * chain, int duplicate);

  // ��������� ����� ������ � ������� ������
  // ���� ������� ����� 256 ������ - ���������� ���� !
  // ��� ������ ������������ ����

  int GetRstColorCount(int number);

  // ��������� ��� ����� ��������� ������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  const char * GetRstName(int number);


  // ������/��������� �������� ������ ������  

  int GetRstCurrentNumber() { return RstChain.CurrentNumber; }
  int SetRstCurrentNumber(int number)
                            { return RstChain.CurrentNumber = number; }

  // ����������� ������� �������
  // order - ������� ����������� (0 - ��� ������, 1 - ��� ������)

  void ShowRstPlace(int order = 0, DIBCONTEXT* dc = 0);  

  // ��������� �������� ������� (���������� � �������)
  // number - ����� � ������� (number = 0  -  ���������� ���)

  void ShowRst(int number = 0);

  // ���������� �������� ������ � ������� �
  // ����������� ����� �������� ������ �����
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  int SetRstPrecision(int number,double precision);

  // ��������� �������� ������ � ������ �����
  // ���������� ��������� �� �������� � ��������� ������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  DFRAME * GetRstFrame(int number);

  // ��������� �������� ������ � ������ �����
  // ���������� ��������� �� �������� ������ � ������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  DFRAME * GetRstFrameMeters(int number);

  // ��������� ������ � �������� ������  
  // number - ����� ����� � �������
  // mapregister - ����� ���������, � ������� ����� ���������
  // ������ � ��������
  // ��� ������ ���������� ����

  int GetRstProjectionData(int number, MAPREGISTEREX* mapregister);  

  // ���������� ������ � �������� ������  
  // number - ����� ����� � �������
  // mapregister - ����� ���������
  // ��� ������ ���������� ����
  int SetRstProjectionData(int number, MAPREGISTEREX* mapregister);

  // ���������/���������� ��������� ������
  // ���� ����� �� ����� - ���������� ����
  // ��� ������ ���������� -1
  int CheckRstView(int number);
  int SetRstView(int number,int view);

  // ���������/���������� ��� ����� ����������� ������ (0-8)
  // ��� ������ ���������� -1
  int GetRstMaskType(int number);                       
  int SetRstMaskType(int number,int masktype);

  // ���������/���������� ������� ����������� �����
  // ��� ������ ���������� -1
  int CheckRstPaletteView(int number, int value);
  int SetRstPaletteView(int number,int color,int value);

  // ���������/���������� ������� �����������
  //  (0 - ��� ������, 1 - ��� ������)
  // ��� ������ ���������� -1
  int RstViewOrder(int number, int order = -1);

  // ��������� ����� �������� ������� ������
  // (� ������ ������� � ������������)
  // number - ����� ����� � �������
  // ��� ������ ���������� 0
  COLORREF* GetRstPalette(int number);

  // ��������� ����� ��������� ������� ������
  // (��� ����� ������� � ������������)
  // number - ����� ����� � �������
  // ��� ������ ���������� 0
  COLORREF* GetRstStandardPalette(int number);

  // ���������/���������� ������� ������� (�� -4 �� 4)
  // number - ����� ����� � �������
  // ��� ������ ���������� 0
  int GetRstBright(int number);
  int SetRstBright(int number,int bright);

  // ���������/���������� ������������� ������� (�� -4 �� 4)
  // number - ����� ����� � �������
  // ��� ������ ���������� 0
  int GetRstContrast(int number);
  int SetRstContrast(int number,int contrast);

  //  ������ � ������� ���������� �����
  //  number - ����� ����� � �������
  //  ��� ������ ���������� 0
  int SetRstColor(int number,COLORREF color,int index);

  //  �������� �������� ������� � ������� �������� � ��������������
  //  number - ����� ����� � �������
  //  ��� ������ ���������� 0
  int RestoreRstPalette(int number);

  // ��������� ��������� ����� (��� 16- � 256-������� �������)  
  //  number - ����� ����� � �������
  //  index  - ������ ����� � ������� ������(������� � 0)
  //  ����������: 1 - ���� � ������ �������� ������������
  //              0 - ���� � ������ �������� �� ������������
  //  ��� ������ ���������� -1
  int CheckVisibilityColor(int number,int index);

  // ���������� ��������� ����� (��� 16- � 256-������� �������)  
  //  number - ����� ����� � �������
  //  index  - ������ ����� � ������� ������(������� � 0)
  //  value: 1 - �������� ����������� ����� � ������ ��������
  //         0 - ��������� ����������� ����� � ������ ��������
  //  ��� ������ ���������� 0
  int SetVisibilityColor(int number,int index, int value);

  // ���������� ��������� ����� (��� 16- � 256-������� �������)  
  //  number - ����� ����� � �������
  //  index  - ������ ����� � ������� ������(������� � 0)
  //  value: 1 - �������� ����������� ����� � ������ ��������
  //         0 - ��������� ����������� ����� � ������ ��������
  //  ���������� ��������� ������ � ��������� ����� ������(� ����� � INI-�����)
  //  ��� ������ ���������� 0
  int SetVisibilityColorInRstFile(int number,int index, int value);

  // ��������� �������� �������� ������ 
  // ���� ����������� ������ ���������� - ���������� ����
  // ���� ����������� ������ ���������� - ���������� 1
  // ��� ������ ���������� -1
  int CheckInversionRst(int number);

  // ������������� ��������� �����    
  // value:
  // 0 - ���������� ����������� ������ ����������
  // 1 - ���������� ����������� ������ ����������
  //  ��� ������ ���������� 0
  int InvertRst(int number, int value);

  // ���������� ����� ������
  int SetRstBorderPlane(int number, TDataEdit* data);

  // ��������� ����� ������                  
  //  ��� ������ ���������� 0
  TDataEdit* GetRstBorderPlane(int number);

  // ��������� ����������� ������ �� �����    
  // value = 1 - ���������� ����� �� �����
  //       = 0 - ���������� ����� ��� ����� �����
  int ShowRstByBorder(int number, int value);

  // ����������� ������� ����������� ������(������������ �����)    
  // ���������� 1 - ��� ����������� ������ �� �����
  //            0 - ��� ����������� ������ ��� ����� �����
  // ��� ������ ���������� -1
  int CheckShowRstByBorder(int number);

  // ��������� ����������� ������ �� ����� �����������   
  // value = 1 - ���������� ����� �� �����
  //       = 0 - ���������� ����� ��� ����� �����
  int ShowRstByMask(int number, int value);

  // ����������� ������� ����������� ������(������������ ����� �����������)    
  // ���������� 1 - ��� ����������� ������ �� ����� �����������
  //            0 - ��� ����������� ������ ��� ����� ����� �����������
  // ��� ������ ���������� -1
  int CheckShowRstByMask(int number);

  //  ���������������� ����� ������� ��������� ������
  void InitRstChainUnit(RSTCHAIN* rstchain, int mini = 0);

  // �������� ����������� ����������� ��������� ������     
  // oldNumber - ����� ����� � �������
  // newNumber - ��������������� ����� ����� � �������
  //  ��� ������ ���������� 0
  int ChangeOrderRstShow(int oldNumber, int newNumber);

// protected :

  // ����������� ��������� ������ � ������� ��������� �������
  int CheckViewRmf();

  // ���������� �����
  int ShowChainRst(int number, DIBCONTEXT* dc);                      

  // ���������� ����� ������ � DIB
  void _fastcall ShowBlockRstDib(TRmf & rst, DIBCONTEXT* dc,         
                                 TBaseColors * colors);

  // ���������� ����� ������ � DIB
  void _fastcall ShowBlockRstDib256(TRmf & rst, DIBCONTEXT* dc,     
                                    TBaseColors * colors);          

  // ���������� ����� ������ �� ����������
  void _fastcall ShowBlockRstDevice(TRmf & rst, TBaseColors * colors);  

public :

 FRAME FrameFillPix;
 FRAME FrameRst;

 CHAININFO  RstChain;          // �������� � ��������� �������

  // ************************************************************
  //                                                            *
  //            ������ � "��������� ����������� �����"          *
  //                                                            *
  // ************************************************************

public :

  // ������� �������� �������, ���� ��� �� �������.
  // ������� ���������� ������� "number".
  // ���������� ��������� �� ������, ���������
  // � ����������� ��������. ��� ������ ���������� ����.

  RMFCHAIN* ActiveMtr(int number) { return IsOpenMtr(number); }
  RMFCHAIN* IsOpenMtr(int number) { return GetChain (number); }

  // ������� ��������� ������ (������� �� �������)
  // number - ����� ���������� ����� � �������
  // ���� number == 0, ����������� ��� ��������� ������

  void CloseMtr(int number = 0);

  // ������� ��������� ������ (�������� � ������� �������)
  // ��� ������ ���������� ����

  int ChangeMtr(RMFCHAIN * chain, const char * name, int mode = 0);

  // ��������� ����� ���������� � ������� ������

  int GetMtrCount() { return MtrCount(); }
  int MtrCount()    { return MtrChain.Count; }
  int IsMtrActive() { return (MtrChain.Count > 0); }    

  // ���������� ����� (number) ���������� � ������� ������

  int SetMtrCount(int number) { return MtrChain.Count = number; }

  // ������/��������� ������ ������� ����� ������� ������

  RMFCHAIN* GetMtrChainBegin() { return MtrChain.Begin; }
  RMFCHAIN* SetMtrChainBegin(RMFCHAIN* mtrchainbegin)
                               { return MtrChain.Begin = mtrchainbegin; }

  // ������/��������� �������� ������ �������� �������

  int GetMtrCurrentNumber() { return MtrChain.CurrentNumber; }
  int SetMtrCurrentNumber(int number)
                            { return MtrChain.CurrentNumber = number; }

  // ��������� ������� ������� �� ������
  // ��� ������ ������������ ����

  RMFCHAIN* GetChain(int number);

  // ��������� ������� ������� ������ ������� �� ������
  // ��� ������ ������������ ����

  RMFCHAIN* GetMtqChain(int number);

  // ��������� ������ � �������� ������� �������          
  // number - ����� ����� � �������
  // mapregisterex - ����� ���������, � ������� ����� ���������
  // ������ � ��������
  // ��� ������ ���������� ����
  int GetMtqProjectionData(int number, MAPREGISTEREX* mapregisterex);

  // ���������� ������ � �������� ������� �������    
  // number - ����� ����� � �������
  // mapregister - ����� ���������
  // ��� ������ ���������� ����
  int SetMtqProjectionData(int number, MAPREGISTEREX* mapregister);

  // ��������� ����� � ������� ��� �������, �������������
  // � �������� �����
  // number - ���������� �����, ��������� ������� � �����
  // (1 - ������ � ������ �����, 2 - ������ ...)
  // ��� ������ ������������ ����

  int GetMtrNumberInPoint(double x, double y, int number);

  // ��������� �������� ����� ��������� ������
  // number - ����� ����� � �������
  // describe - ����� ���������, � ������� ����� ���������
  // �������� �������
  // ��� ������ ���������� ����

  int GetMtrDescribe(int number, MTRDESCRIBE* describe);

  // ��������� ������ � �������� ��������� ������
  // number - ����� ����� � �������
  // projectiondata - ����� ���������, � ������� ����� ���������
  // ������ � ��������
  // ��� ������ ���������� ����

  int GetMtrProjectionData(int number, MTRPROJECTIONDATA* projectiondata);

  // ��������� ������ � �������� ��������� ������         
  // number - ����� ����� � �������
  // mapregisterex - ����� ���������, � ������� ����� ���������
  // ������ � ��������
  // ��� ������ ���������� ����
  int GetMtrProjectionDataEx(int number, MAPREGISTEREX* mapregisterex);

  // ���������� ������ � �������� ��������� ������   
  // number - ����� ����� � �������
  // mapregister - ����� ���������
  // ��� ������ ���������� ����
  int SetMtrProjectionDataEx(int number, MAPREGISTEREX* mapregister);

  // ��������� �������� ��������� ����� ������� � �������
  // number � �������
  // colornumber - ����� ��������� �����
  // colordesc - ����� ���������, � ������� ����� ���������
  // �������� ��������� �����
  // ��� ������ ���������� ����

  int GetMtrColorDesc(int number, int colornumber, MTRCOLORDESCEX* colordesc);

  // ���������� ���� ��������� ����� ������� � �������
  // number � �������
  // colornumber - ����� ��������� �����
  // ��� ������ ���������� ����

  int SetMtrColor(int number,COLORREF color,int colornumber);

  // ��������� ��� ����� ��������� ������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  const char* GetMtrName(int number);

  // ��������� ���������� �������� ����� ������� ������ (� ������)

  double GetHeightMin() {return MtrChainMinHeight;}
  double GetHeightMax() {return MtrChainMaxHeight;}

  // ����������/��������� ������� ���� ������� �����
  // value - ���� ��������� ���� (�� 0 �� 16)
  //   MTRSHADOW_NONE   =  0,   // ���� �����������
  //   MTRSHADOW_PALE   =  1,   // �������
  //   MTRSHADOW_WEAK   =  2,   // ������
  //   MTRSHADOW_MIDDLE =  4,   // �������
  //   MTRSHADOW_HEAVY  =  8,   // �������
  //   MTRSHADOW_DEEP   = 16,   // ��������

  int SetMtrShadow(int value);                          
  int GetMtrShadow();

  // ����������/��������� ������������� ���� ������� �����
  // value - ������������� ���� (�� 0 �� 100)

  int SetMtrShadowIntensity(int value);                 
  int GetMtrShadowIntensity();

  // ����������/��������� ���� ��������� �����������������
  // ��������� ����� ������� ������ �����
  // (1 - ���������� ���������������� ��������,
  //  0 - �������� ���������� � SetRegion)

  int SetMtrChainUserDiapason(int value);               
  int GetMtrChainUserDiapason();

  // ����� �������� ���������� ������ � �������� �����.
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ���������� ������� ���������� ERRORHEIGHT.

  double GetHeightValue(double x, double y);
  double GetHeightValue(DOUBLEPOINT* point)
    { return GetHeightValue(point->x,point->y); }

  // ����� �������� ���������� ������ � �������� ����� �� �������
  // � ������� number � �������.                        
  // number - ����� ������� � �������.
  // ���������� ����� �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ���������� ������� ���������� ERRORHEIGHT.
  double GetHeightValue(int number,double x, double y);

  // ��������� �������� ���������� ������ � ������� �������,
  // ��������������� �������� �����.
  // number - ����� ������� � �������.
  // ���������� ����� (x,y) � �������� ������ (h) �������� � ������
  // � ������� ��������� ��������� �����.
  // � ������ ������ ���������� ����.

  int PutHeightValue(long int number, double x, double y, double h);
  int PutHeightValue(long int number, DOUBLEPOINT* point, double h)
    { return PutHeightValue(number,point->x,point->y,h); }

  // ����� �������� ���������� ������ � �������� ����� �� ����� ������
  // �������.
  // ���������� ����� �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ���������� ������� ���������� ERRORHEIGHT.

  double GetPrecisionHeightValue(double x, double y);
  double GetPrecisionHeightValue(DOUBLEPOINT* point)
    { return GetPrecisionHeightValue(point->x,point->y); }

  // ������ ���������� ������ ������� ������������� � �������� �����
  // �� ������� � ���������� �������� �������� (����� ������).
  // ������ ����������� �� ����� ������ ������� �����,� � ������
  // ���������������� �������� ����� ������� ������ ����� -
  // �� ����� ������ ������� �����.
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ���������� ������� ���������� ERRORHEIGHT.

  double GetPrecisionHeightTriangle(double x, double y);

  // ����� ������� �������� ���������� �����, ���������������
  // ���������� ���������, ������� �� �������� �������.
  // ���������� �����, �������� ������ � ����� �������
  // (FirstPoint,SecondPoint) �������� � ������ � �������
  // ��������� ��������� �����.
  // ������ ������� �����, ��������� ������� HeightArray,
  // ������ ��������������� �������������� ���������� �����
  // (HeightCount), � ��������� ������ �������� ������ ������
  // � �������.
  // � ������ ���������������� ����������� �������� ����������
  // ������� ��� �������� ����� ERRORHEIGHT.
  // � ������ ������ ��� ������ ����� ���������� ����.

  int GetHeightArray (double*       HeightArray,
                      int           HeightCount,
                      DOUBLEPOINT*  FirstPoint,
                      DOUBLEPOINT*  SecondPoint);

  // ������� ��������� ������ (�������� � ������� ������)
  // ���������� ����� ����� � ������� ������
  // ��� ������ ���������� ����

  int OpenMtr(const char * name, int mode);

  // ����������� ������ �������
  // order - ������� ����������� (0 - ��� ������, 1 - ��� ������)

  void ShowMtrPlace(CHAININFO *info, int order = 0,
                    DIBCONTEXT* dc = 0);                

  // ��������� �������� ������ (���������� � �������)
  // number - ����� � ������� (number = 0  -  ���������� ���)

  void ShowMtr(CHAININFO *info, int number = 0);

  // ���������/���������� ������� �����������
  //  (0 - ��� ������, 1 - ��� ������)
  // ��� ������ ���������� -1
  int MtrViewOrder(int number, int order = -1);

  // ����������/��������� ��������� ������� �����
  // 0 - ������� �� ������������

  int CheckMtrView(int number);
  int SetMtrView(int number,int view);

  // ���������/���������� ��� ����� ����������� ������� ����� (0-8)
  // ��� ������ ���������� -1
  int GetMtrMaskType(int number);                       
  int SetMtrMaskType(int number,int masktype);

  // ���������� ����� �������
  //  ��� ������ ���������� 0
  int SetMtrBorderPlane(int number, TDataEdit* data);

  // ��������� ����� �������                    
  // ��� ���������� ����� ���������� 0
  TDataEdit* GetMtrBorderPlane(int number);

  // ��������� ����������� ������� �� �����    
  // value = 1 - ���������� ����� �� �����
  //       = 0 - ���������� ����� ��� ����� �����
  int ShowMtrByBorder(int number, int value);

  // ����������� ������� ����������� �������(������������ �����)    
  // ���������� 1 - ��� ����������� ������� �� �����
  //            0 - ��� ����������� ������� ��� ����� �����
  // ��� ������ ���������� -1
  int CheckShowMtrByBorder(int number);

  // �������� ����������� ����������� ������            
  // oldNumber - ����� ����� � �������
  // newNumber - ��������������� ����� ����� � �������
  //  ��� ������ ���������� 0
  int ChangeOrderMtrShow(int oldNumber, int newNumber);

// protected :

  // ���������������� ����� ������� ��������� ������
  void InitMtrChainUnit(RMFCHAIN* mtrchain);

  // ���������� �����
  int ShowChainMtr(RMFCHAIN* mtrchain, DIBCONTEXT* dc);      

  // ��������� ����� �������

  void ShowBlockMtrDib(RMFCHAIN* mtrchain, DIBCONTEXT* dc);  
  void ShowBlockMtrDevice(RMFCHAIN* mtrchain);

public : // ���� TIN
// ������� tin ������ (�������� � ������� ������)
// ���������� ����� ����� � �������
// ��� ������ ���������� ����
int OpenTin(const char * name, int mode);

// ������� tin ������
// number - ����� ����� ������ � �������
// ���� number == 0, ����������� ��� ������
// ��� ������ ���������� 0
int CloseTin(const int number = 0);

// ��������� ����� ���������� � ������� �������
int GetTinCount();

// ��������� ��� ����� ��� ������ � ������� number
const char* GetTinName(const int number);

// �������� ����������� � ������� index
// number - ����� TIN-����� � �������
// index - ������ � ������� �������������
// ��� ������ ���������� 0 
long int GetTriangle(const int number, 
                               TINTRIANGLE* const triangle, const int index);
  
// ����������� tin ������� �������
// order - ������� ����������� (0 - ��� ������, 1 - ��� ������)
int ShowTinPlace(int order = 0, DIBCONTEXT* _dc = 0);

// ���������/���������� ������� �����������
//  (0 - ��� ������, 1 - ��� ������)
// ��� ������ ���������� -1
int TinViewOrder(int number, int order = -1);
	 
// ����������/��������� ��������� ������� �����
// 0 - ��� ������ �� ������������
int CheckTinView(int number);
int SetTinView(int number,int view);

// ����� �������� ������ ����������� � �������� �����
// �� TIN-������ � ������� number � �������.
// number - ����� TIN-������ � �������.
// ���������� ����� �������� � ������ � ������� ���������
// ��������� �����. ���������� �������� ������ � ������.
// � ������ ������ ��� ������ ������ � � ������ ����������������
// �������� ����� ������� ���������� ERRORHEIGHT.
double GetTinSurfaceHeight(int number, double x, double y);

// ����� �������� ������ ����������� � �������� �����.
// ���������� ����� �������� � ������ � ������� ���������
// ��������� �����. ���������� �������� ������ � ������.
// ������ ����������� ������������� �� ����� ������ TIN-������.
// � ������ ������ ��� ������ ������ � � ������ ����������������
// �������� ����� ������� TIN-������ ���������� ERRORHEIGHT.
double GetSurfaceHeight(double x, double y);
double GetSurfaceHeight(DOUBLEPOINT* point)
   { return GetSurfaceHeight(point->x, point->y); } 

TINCHAIN   *TinChainBegin;    // ������ ����� �������
int         TinCurrentNumber; // ������� ��� ������

public : // ���� ������

 CHAININFO  MtqChain;          // �������� � ������� ������ �������
 CHAININFO  MtrChain;          // �������� � ��������� �������

 // �������� ��������� ����
 // -------------------------------
 TMtrPalette  MtrPalette;      // ������� �������
                               
 int    MatrixShadow;          // ������� ���� ������� �����
 int    MtrShadow;             // ������� ���� ������� �����
 int    MtrShadowIntensity;    // ������������� ���� ������� ����� 
 double MatrixUnitShadow;      // ��������� �������� � ����� � �������� �� ������ (�����������)
 int    ColorsNumber;          // ����� ������ ������� ������� �������

 FRAME FrameMtr;

 double MtrChainMinHeight;     // ����������� ������ �������
 double MtrChainMaxHeight;     // ������������ ������ �������

                               
 int    MtrChainUserDiapason;  // ���� ��������� �����������������
                               // ��������� ����� �������
                               // (MtrChainMinHeight, MtrChainMaxHeight)
                               // (1 - ���������� ���������������� ��������,
                               //  0 - �������� ���������� � SetRegion)

 // ������� ���������� ����������� ������ � �������
 // -----------------------------------------------
 int BorderFilter;      // ������ �� �����
 int MaskType;          // ��� �����
 int MaskStep;          // ��� �����
 char Mask[8];          // ���������� �����

 int ESize;             // ������ ��������
 DFRAME DFrameElem;     // ������� ������ � ���������
 double ShiftX,ShiftY;  // �������� ������ ����������

 int StrCurrPix;        // ������� ������ �������� ����� (� ������� Frame)
 int ColCurrPix;        // ����� ������� �������� ����� (� ������� Frame)
 int StrNextPix;        // ������� ������ ���������� ����� (� ������� Frame)
 int ColNextPix;        // ����� ������� ���������� ����� (� ������� Frame)
 int BlockHeight;       // ������ �������� �����
 int BlockWidth;        // ������ �������� �����
 int BlockWidth1;       // ������ ����������� ����� (��� ��������� ��������� �����)  
 int BlockWidth2;       // ������ ���������� �����  (��� ��������� ��������� �����)
 int Visible;           // ���� ��������� ����� (0,1,2)
 char* BlockAddr;       // ����� ������������ �����
 int StringBlockAddr;   // ����� ������ ������������ ����� BlockAddr   
 int ColumnBlockAddr;   // ����� ������� ������������ ����� BlockAddr  
 char* ColumnAddr1;     // ��������� �� ������� � �������� ������  
 char* ColumnAddr2;     // (��� ��������� ��������� �����)
 double StringInBlockBegin;
 double ColumnInBlockBegin;
 double StringInBlockFloat;
 double ColumnInBlockFloat;

 unsigned char ColorFilter[256];  // ������ �� ����� (��� ������)

 // ������� �������������� ����� ��� ������������ ����� (mtrshow.cpp)
 // ������� ��������� ������ �������������� �����
 // ��� ������������ ����� (Arctan � Sinus)
#define RANGE_ARCTAN  600    // -66 ... 66 ��������
#define RANGE_SINUS   256    // -57 ... 57 ��������     
#define SCALE_FACTOR  128.0  // ���� ������� ������ Arctan � Sinus

 long   Arctan[RANGE_ARCTAN];
 long   Sinus [RANGE_SINUS];
 unsigned char ShadowColor[RANGE_SINUS][256];           


  // ************************************************************
  //                                                            *
  //                 ������ � ������� �����                     *
  //                                                            *
  // ************************************************************

#ifndef HIDEMTL

public :

  // ������� �������� �������, ���� ��� �� �������.
  // ������� ���������� ������� "number".
  // ���������� ��������� �� ������, ���������
  // � ����������� ��������. ��� ������ ���������� ����.
  MTLCHAIN* ActiveMtl(int number) { return IsOpenMtl(number); }
  MTLCHAIN* IsOpenMtl(int number) { return GetMtlChain (number); }

  // ������� ��������� ������ (������� �� �������)
  // number - ����� ���������� ����� � �������
  // ���� number == 0, ����������� ��� ��������� ������
  void CloseMtl(int number = 0);

  // ��������� ����� ���������� � ������� ������
  int GetMtlCount() { return MtlCount(); }
  int MtlCount()    { return MtlChainCount; }
  int IsMtlActive() { return (MtlCount() > 0); }

  // ���������� ����� (number) ���������� � ������� ������
  int SetMtlCount(int number) { return MtlChainCount = number; }

  // ������/��������� ������ ������� ����� ������� ������
  MTLCHAIN* GetMtlChainBegin() { return MtlChainBegin; }
  MTLCHAIN* SetMtlChainBegin(MTLCHAIN* mtlchainbegin)
                               { return MtlChainBegin = mtlchainbegin; }

  // ������/��������� �������� ������ �������� �������
  int GetMtlCurrentNumber() { return MtlCurrentNumber; }
  int SetMtlCurrentNumber(int number)
                            { return MtlCurrentNumber = number; }

  // ��������� ������� ������� �� ������
  // ��� ������ ������������ ����
  MTLCHAIN* GetMtlChain(int number);

  // ��������� ����� � ������� ��� �������, �������������
  // � �������� �����
  // number - ���������� �����, ��������� ������� � �����
  // (1 - ������ � ������ �����, 2 - ������ ...)
  // ��� ������ ������������ ����
  int GetMtlNumberInPoint(double x,double y,int number);

  // ��������� ����� � ������� ��������� �������� �������
  // � ������������� (������ 1) ��������� ���������.
  // ��� ������ ������������ ����
  int GetMtlNumberLastVisible();

  // ��������� �������� ����� ��������� ������
  // number - ����� ����� � �������
  // describe - ����� ���������, � ������� ����� ���������
  // �������� �������
  // ��� ������ ���������� ����
  int GetMtlDescribe(int number, MTLDESCRIBE* describe);

  // ��������� ������ � �������� ��������� ������
  // number - ����� ����� � �������
  // projectiondata - ����� ���������, � ������� ����� ���������
  // ������ � ��������
  // ��� ������ ���������� ����
  int GetMtlProjectionData(int number, MTRPROJECTIONDATA * projectiondata);

  // ��������� ������ � �������� ��������� ������    
  // number - ����� ����� � �������
  // mapregister - ����� ���������, � ������� ����� ���������
  // ������ � ��������
  // ��� ������ ���������� ����
  int GetMtlProjectionDataEx(int number, MAPREGISTEREX* mapregister);

  // ���������� ������ � �������� ��������� ������   
  // number - ����� ����� � �������
  // mapregister - ����� ���������
  // ��� ������ ���������� ����
  int SetMtlProjectionDataEx(int number, MAPREGISTEREX* mapregister);

  // ��������� ��� ����� ��������� ������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����
  const char* GetMtlName(int number);

  // ��������� ����������� �������� ������ ������� ������
  // ������� ������ (� ������)
  double GetMinBotLevelHeight() {return MtlChainMinBotLevelHeight;}

  // ��������� �������� ������������ ��������� �������� �����
  // ������� ������ (� ������)
  double GetMaxSummaryPower() {return MtlChainMaxSummaryPower;}

  // ��������� ��������� �������� ����� �������
  // � ������� number � �������.
  // � ������ ������ ���������� ERRORPOWER.
  double GetMaxSummaryPowerOfMtl(long int number);

  // ��������� �������� ������������� ���������� ����� ������� ������
  int GetMaxLayerCount() {return MtlChainMaxLayerCount;}

  // ��������� ���������� ����� ������� � ������� number � �������.
  // ��� ������ ���������� ����
  int GetLayerCountOfMtl(long int number);

  // ����� �������� ���������� ������ � �������� �����.
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ���������� ������� ���������� ERRORHEIGHT.
  double GetElementHeight(double x, double y);
  double GetElementHeight(DOUBLEPOINT* point)
    { return GetElementHeight(point->x,point->y); }

  // ����� �������� ���������� ������ � �������� ����� �� �������
  // � ������� number � �������.
  // number - ����� ������� � �������.
  // ���������� ����� �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ���������� ������� ���������� ERRORHEIGHT.
  double GetElementHeight(int number,double x, double y);

  // ��������� �������� ���������� ������ � ������� �������,
  // ��������������� �������� �����.
  // number - ����� ������� � �������.
  // ���������� ����� (x,y) � �������� ������ (h) �������� � ������
  // � ������� ��������� ��������� �����.
  // � ������ ������ ���������� ����.
  int PutElementHeight(long int number, double x, double y, double h);
  int PutElementHeight(long int number, DOUBLEPOINT* point, double h)
    { return PutElementHeight(number,point->x,point->y,h); }

  // ����� �������� ���������� ������ � �������� ����� �� ����� ������
  // �������.
  // ���������� ����� �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ���������� ������� ���������� ERRORHEIGHT.
  double GetPrecisionElementHeight(double x, double y);
  double GetPrecisionElementHeight(DOUBLEPOINT* point)
    { return GetPrecisionElementHeight(point->x,point->y); }


  // ����� �������� �������� ���� layernumber � �������� �����.
  // ���������� ����� �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� �������� � ������.
  // � ������ ������ ��� ������ �������� � � ������ ����������������
  // �������� ����� ���������� ������� ���������� ERRORPOWER.
  double GetElementPower(double x,double y,long int layernumber);
  double GetElementPower(DOUBLEPOINT* point,long int layernumber)
    { return GetElementPower(point->x,point->y,layernumber); }

  // ����� �������� �������� ���� layernumber � �������� �����
  // �� ������� � ������� number � �������.
  // number - ����� ������� � �������.
  // ���������� ����� �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� �������� � ������.
  // � ������ ������ ��� ������ �������� � � ������ ����������������
  // �������� ����� ���������� ������� ���������� ERRORPOWER.
  double GetElementPower(int number,double x,double y,long int layernumber);

  // ���������� �������� ��������� ����� � �������� �����
  // ������� ������������� �� ������� � ������� number � �������.
  // ���������� ����� �������� � ������ � ������� ���������
  // ��������� �����.
  // powers - ����� ������� ��� ������ ����������� �������� ���������
  // count - ������ �������, ������ ���� �� ����� TMtl::LayerCount().
  // ���������� ���������� ����������� ��������� ������� powers.
  // ��� ������ ���������� ����.
  int GetElementPowersTriangle(int number,double x,double y,
                               double* powers,int count);

  // ���������� �������� �������� ���� layernumber � �������� �����
  // ������� ������������� �� ������� � ������� number � �������.
  // ���������� ����� �������� � ������ � ������� ���������
  // ��������� �����.
  // ���������� �������� �������� ���� � ������.
  // ��� ������ ���������� ERRORPOWER.
  double GetElementPowerTriangle(int number,double x,double y,
                                 int layernumber);

  // ��������� �������� �������� ���� layernumber � ������� �������,
  // ��������������� �������� �����.
  // number - ����� ������� � �������.
  // ���������� ����� (x,y) � �������� �������� (p) �������� � ������
  // � ������� ��������� ��������� �����.
  // � ������ ������ ���������� ����.
  int PutElementPower(long int number, double x, double y, double p,
                      long int layernumber);
  int PutElementPower(long int number, DOUBLEPOINT* point, double p,
                      long int layernumber)
    { return PutElementPower(number,point->x,point->y,p,layernumber); }

  // ����� �������� �������� ���� layernumber � �������� �����
  // �� ����� ������ �������.
  // ���������� ����� �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� �������� � ������.
  // � ������ ������ ��� ������ �������� � � ������ ����������������
  // �������� ����� ���������� ������� ���������� ERRORPOWER.
  double GetPrecisionElementPower(double x,double y,long int layernumber);
  double GetPrecisionElementPower(DOUBLEPOINT* point,long int layernumber)
    { return GetPrecisionElementPower(point->x,point->y,layernumber); }


  // ����� ������� �������� ���������� �����, ���������������
  // ���������� ���������, ������� �� �������� �������.
  // ���������� �����, �������� ������ � ����� �������
  // (FirstPoint,SecondPoint) �������� � ������ � �������
  // ��������� ��������� �����.
  // ������ ������� �����, ��������� ������� HeightArray,
  // ������ ��������������� �������������� ���������� �����
  // (HeightCount), � ��������� ������ �������� ������ ������
  // � �������.
  // � ������ ���������������� ����������� �������� ����������
  // ������� ��� �������� ����� ERRORHEIGHT.
  // � ������ ������ ��� ������ ����� ���������� ����.
  int GetHeightArrayFromMtl (double*       HeightArray,
                             int           HeightCount,
                             DOUBLEPOINT*  FirstPoint,
                             DOUBLEPOINT*  SecondPoint);

  // ������� ��������� ������ (�������� � ������� ������)
  // ���������� ����� ����� � ������� ������
  // ��� ������ ���������� ����
  int OpenMtl(const char * name, int mode);

  // ����������� ������ �������
  // order - ������� ����������� (0 - ��� ������, 1 - ��� ������)
  int ShowMtlPlace(int order = 0, DIBCONTEXT* dc = 0);  

  // ��������� �������� ������ (���������� � �������)
  // number - ����� � ������� (number = 0  -  ���������� ���)
  void ShowMtl(int number = 0);

  // ���������/���������� ������� �����������
  //  (0 - ��� ������, 1 - ��� ������)
  // ��� ������ ���������� -1
  int MtlViewOrder(int number, int order = -1);

  // ����������/��������� ��������� �������
  // 0 - ������� �� ������������
  int CheckMtlView(int number);
  int SetMtlView(int number,int view);

  // ���������/���������� ��� ����� ����������� ������� (0-8)
  // ��� ������ ���������� -1
  int GetMtlMaskType(int number);                       
  int SetMtlMaskType(int number,int masktype);

  // ���������� ����� �������
  //  ��� ������ ���������� 0
  int SetMtlBorderPlane(int number, TDataEdit* data);

  // ��������� ����� �������
  // ��� ���������� ����� ���������� 0
  TDataEdit* GetMtlBorderPlane(int number);

  // ��������� ����������� ������� �� �����
  // value = 1 - ���������� ����� �� �����
  //       = 0 - ���������� ����� ��� ����� �����
  int ShowMtlByBorder(int number, int value);

  // ����������� ������� ����������� �������(������������ �����)
  // ���������� 1 - ��� ����������� ������� �� �����
  //            0 - ��� ����������� ������� ��� ����� �����
  // ��� ������ ���������� -1
  int CheckShowMtlByBorder(int number);

  // �������� ����������� ����������� ������       
  // oldNumber - ����� ����� � �������
  // newNumber - ��������������� ����� ����� � �������
  //  ��� ������ ���������� 0
  int ChangeOrderMtlShow(int oldNumber, int newNumber);


// protected :

  // ���������������� ��������� ������
  void InitMtlChain();

  // ���������������� ����� ������� ��������� ������
  void InitMtlChainUnit(MTLCHAIN* mtlchain);

  // ���������� ������� �����
  int ShowChainMtl(MTLCHAIN* mtlchain, DIBCONTEXT* dc);      

  // ��������� ����� �������
  void ShowBlockMtlDib(MTLCHAIN* mtlchain, DIBCONTEXT* dc);  
  void ShowBlockMtlDevice(MTLCHAIN* mtlchain);

public :

  FRAME FrameMtl;

  double MtlChainMaxSummaryPower; // ������������ ��������� �������� �����
                                  // ���� MTL-������� (� ������)
  double MtlChainMinBotLevelHeight; // ����������� ������ ������� ������
                                    // ���� MTL-������� (� ������)
  int    MtlChainMaxLayerCount;  // ������������ ���������� �����
                                 // ���� MTL-�������

  int       MtlChainCount;       // ���������� �������
  MTLCHAIN* MtlChainBegin;       // ������ ����� �������
  int       MtlCurrentNumber;    // ����� �������� ������� � �������

#endif  // HIDEMTL


#ifndef HIDETIN
  // ************************************************************
  //                                                            *
  //                 ������ � TIN-������                        *
  //                                                            *
  // ************************************************************

public :

  // ������� �������� ������, ���� ��� �� �������.
  // ������� ���������� ������ "number".
  // ���������� ��������� �� ������, ���������
  // � ����������� �������. ��� ������ ���������� ����.
  TINCHAIN* ActiveTin(int number) { return IsOpenTin(number); }
  TINCHAIN* IsOpenTin(int number) { return GetTinChain(number); }

  // ������� ������ (������� �� �������)
  // number - ����� ����� � �������
  // ���� number == 0, ����������� ��� ������
  void CloseTin(int number = 0);

  // ��������� ����� ���������� � ������� �������
  int GetTinCount() { return TinCount(); }
  int TinCount()    { return TinChainCount; }
  int IsTinActive() { return (TinCount() > 0); }

  // ���������� ����� (number) ���������� � ������� �������
  int SetTinCount(int number) { return TinChainCount = number; }

  // ������/��������� ������ ������� ����� ������� �������
  TINCHAIN* GetTinChainBegin() { return TinChainBegin; }
  TINCHAIN* SetTinChainBegin(TINCHAIN* tinchainbegin)
                               { return TinChainBegin = tinchainbegin; }

  // ������/��������� �������� ������ �������� ������
  int GetTinCurrentNumber() { return TinCurrentNumber; }
  int SetTinCurrentNumber(int number)
                            { return TinCurrentNumber = number; }

  // ��������� ������� ������� �� ������
  // ��� ������ ������������ ����
  TINCHAIN* GetTinChain(int number);

  // ��������� ����� � ������� ��� ������, �������������
  // � �������� �����
  // number - ���������� �����, ��������� ������ � �����
  // (1 - ������ � ������ �����, 2 - ������ ...)
  // ��� ������ ������������ ����
  int GetTinNumberInPoint(double x,double y,int number);

  // ��������� ����� � ������� ��������� �������� ������
  // � ������������� (������ 1) ��������� ���������.
  // ��� ������ ������������ ����
  int GetTinNumberLastVisible();

  // ��������� �������� ����� ������
  // number - ����� ����� � �������
  // describe - ����� ���������, � ������� ����� ���������
  // �������� ������
  // ��� ������ ���������� ����
  int GetTinDescribe(int number, TINDESCRIBE* describe);

  // ��������� ��� ����� ������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����
  const char* GetTinName(int number);

  // ��������� �������� ����� ������
  // number - ����� ����� � �������
  // describe - ����� ���������, � ������� ����� ���������
  // �������� ������
  // ��� ������ ���������� ����
  long int _MAPAPI mapGetTinDescribe(HMAP hMap, long int number,
                                     TINDESCRIBE * describe);

  // ����� �������� ������ ����������� � �������� �����.
  // ���������� ����� �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // ������ ����������� ������������� �� ����� ������ TIN-������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ������� TIN-������ ���������� ERRORHEIGHT.
  double GetSurfaceHeight(double x, double y);
  double GetSurfaceHeight(DOUBLEPOINT* point)
    { return GetSurfaceHeight(point->x, point->y); }

  // ����� �������� ������ ����������� � �������� �����
  // �� TIN-������ � ������� number � �������.
  // number - ����� TIN-������ � �������.
  // ���������� ����� �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ������� ���������� ERRORHEIGHT.
  double GetTinSurfaceHeight(int number, double x, double y);

  // ������� ������ (�������� � ������� ������)
  // ���������� ����� ����� � ������� ������
  // ��� ������ ���������� ����
  int OpenTin(const char * name, int mode);

  // ����������� ������� �������
  // order - ������� ����������� (0 - ��� ������, 1 - ��� ������)
  int ShowTinPlace(int order = 0, DIBCONTEXT* dc = 0);

  // ��������� �������� ������� (���������� � �������)
  // number - ����� � ������� (number = 0  -  ���������� ���)
  void ShowTin(int number = 0, DIBCONTEXT* dc = 0);

  // ���������/���������� ������� �����������
  //  (0 - ��� ������, 1 - ��� ������)
  // ��� ������ ���������� -1
  int TinViewOrder(int number, int order = -1);

  // ����������/��������� ��������� �������
  // 0 - ������ �� ������������
  int CheckTinView(int number);
  int SetTinView(int number, int view);

  // ���������/���������� ��� ����� ����������� ������� (0-8)
  // ��� ������ ���������� -1
  int GetTinMaskType(int number);
  int SetTinMaskType(int number, int masktype);

  // ���������� ����� ������
  //  ��� ������ ���������� 0
  int SetTinBorderPlane(int number, TDataEdit* data);

  // ��������� ����� ������
  // ��� ���������� ����� ���������� 0
  TDataEdit* GetTinBorderPlane(int number);

  // ��������� ����������� ������ �� �����
  // value = 1 - ���������� �� �����
  //       = 0 - ���������� ��� ����� �����
  int ShowTinByBorder(int number, int value);

  // ����������� ������� ����������� ������(������������ �����)
  // ���������� 1 - ��� ����������� ������ �� �����
  //            0 - ��� ����������� ������ ��� ����� �����
  // ��� ������ ���������� -1
  int CheckShowTinByBorder(int number);

  // �������� ����������� ����������� �������
  // oldNumber - ����� ����� � �������
  // newNumber - ��������������� ����� ����� � �������
  //  ��� ������ ���������� 0
  int ChangeOrderTinShow(int oldNumber, int newNumber);

  // ���������������� ������ TIN-�������
  void InitTinChain();

  // ���������������� ����� ������� TIN-�������
  void InitTinChainUnit(TINCHAIN* tinchain);

  // ���������� TIN-������
  int ShowChainTinFill(TINCHAIN* tinchain, DIBCONTEXT* dc);
  int ShowChainTinSkelet(TINCHAIN* tinchain, DIBCONTEXT* dc);

  // ����������� ��������� ������ � ������� ��������� �������
  int CheckViewTin();

  // ������ ������� vertex �� ������ ������ TIN-������
  // � ������� number � �������
  // index - ������ � ������� ������
  // ��� ������ ���������� 0
  int GetTinVertex(long int number, TINVERTEX* vertex, long int index);

  // ������ ������� vertex � ������ ������ TIN-������
  // � ������� number � �������
  // index - ������ � ������� ������
  // ��� ������ ���������� 0
  int PutTinVertex(long int number, const TINVERTEX* vertex, long int index);

  // �������/��������� ������ ������� TIN-������
  // number - ����� TIN-����� � �������
  // index - ������ � ������� ������
  // flag - ����� ���������, ���������� �������� ������ �������
  // ��������a TINVERTEXFLAG ������a � MAPTYPE.H
  // ��� ������ ���������� 0
  int GetTinVertexFlags(long int number, int index, TINVERTEXFLAG* flag);
  int SetTinVertexFlags(long int number, int index, const TINVERTEXFLAG* flag);

  // �������/��������� ������ ������������ TIN-������
  // number - ����� TIN-����� � �������
  // index - ������ � ������� �������������
  // flag - ����� ���������, ���������� �������� ������ ������������
  // ��������a TINTRIANGLEFLAG ������a � MAPTYPE.H
  // ��� ������ ���������� 0
  int GetTinTriangleFlags(long int number, int index, TINTRIANGLEFLAG* flag);
  int SetTinTriangleFlags(long int number, int index, const TINTRIANGLEFLAG* flag);

  // ������ ������������ triangle �� ������� ������������� TIN-������
  // � ������� number � �������
  // index - ������ � ������� �������������
  // ��� ������ ���������� 0
  int GetTinTriangle(long int number, TINTRIANGLE* triangle, long int index);

  // ������ ������������ triangle � ������ ������������� TIN-������
  // � ������� number � �������
  // index - ������ � ������� �������������
  // ��� ������ ���������� 0
  int PutTinTriangle(long int number, const TINTRIANGLE* triangle, long int index);

#endif  // HIDETIN



// ===========================================================
//           ������� �������
// ===========================================================

  // ��������� ����� ���������� � ������� ������   
  int GetMtqCount() { return MtqCount(); }      
  int MtqCount()    { return MtqChain.Count; }

  // ������� ������ ������ �������
  void CloseMtq(int number);

  // ����������/��������� ���� ������� ��������
  // value - ���� ��������� ���� (1 - ���� ����, 0 - ���� ���)

  int SetMtqShadow(int number, int value);              
  int GetMtqShadow(int number);

  // ����������/��������� ��������� ������� ��������  
  // 0 - ������� �������� �� ������������
  int CheckMtqView(int number);
  int SetMtqView(int number,int view);

  // ����������� ������� ����������� ������� �������(������������ �����)
  // ���������� 1 - ��� ����������� ������� �� �����
  //            0 - ��� ����������� ������� ��� ����� �����
  // ��� ������ ���������� -1
  int CheckShowMtqByBorder(int number);

  // ��������� ����������� ������� ������� �� �����
  // value = 1 - ���������� ������� �� �����
  //       = 0 - ���������� ������� ��� ����� �����
  //  ��� ������ ���������� 0
  int ShowMtqByBorder(int number, int value);

  // �������� ����������� ����������� ������ �������
  // oldNumber - ����� ����� � �������
  // newNumber - ��������������� ����� ����� � �������
  //  ��� ������ ���������� 0
  int ChangeOrderMtqShow(int oldNumber, int newNumber);

  // ���������� ����� �������                          
  int SetMtqBorderPlane(int number, TDataEdit* data);

  //  ��������� ����� �������
  TDataEdit* GetMtqBorderPlane(int number);

public:

  // ��������� ����� ������� ������� ������������ � DIB
  VISUALTABLE* GetDibTable() { return DibFunc;}

  // ������� ��������� ������  
  void SetBreakCallAndParm(BREAKCALL call, long int parm)
  {
    BreakCall = call;
    BreakParm = parm;
  }

  // ���������� ����������� �����
  // 0 - �� ����������
  void SetNodeView(int mode) { IsNodeView = mode; }
  int GetNodeView() { return IsNodeView; }

  // ����������������� ��� ����
  void InitNodeImage();

  // ���������� ����� ���������� ����
  void SetNodeFirstColor(COLORREF color = 0x02020F0);
  void SetNodeCenterColor(COLORREF color = 0x0FFFFFF);
  void SetNodeBorderColor(COLORREF color = 0);

  // ��������� ����� ���������� ����
  COLORREF GetNodeFirstColor();
  COLORREF GetNodeCenterColor();
  COLORREF GetNodeBorderColor();

  // ���������� ��� ����
  void SetNodeType(int type = 2);
  int  GetNodeType();

  // ���������� ���� ������� � DIB
  void ViewNode(POLYDATAEX * data);

 public :

  long int NodeFirstIndex;     // ������ ����� ������� ���� ��� DIB
  long int NodeCenterIndex;    // ������ ����� ���� ��� DIB
  long int NodeBorderIndex;    // ������ ����� ������� ���� ��� DIB

  COLORREF NodeFirstColor;     // ���� ������� ���� ��� DIB
  COLORREF NodeCenterColor;    // ���� ���� ��� DIB
  COLORREF NodeBorderColor;    // ���� ������� ���� ��� DIB

  int NodeSize;                // ��� ���� (1,2,3)
  int IsNodeView;              // ������� ����������� �����

  CHANGECALL  ChangeCall;      // ����� ������� ��� ���������� � ��������������
  long int ChangeParm;         // �������� ������� ����������

  BREAKCALL BreakCall;         // ������� ��������� ������
  long int  BreakParm;         // ��� ���������� �����������

  BEFOREPAINT BeforePaint;     // ������� ��������� ������      
  long int    BeforeParm;      // ��� ��������� ��� ������

  int  SkeepTextFlag;          // ������� ������ ������� � ����� ���������
  int  IsRestoreData;          // ������� �������������� ������ �������� ������ �� INI-�����

  int  NotAdjust;              // ������� ������������ ���������� ����� ��-�� ������-����
                               // ��������

  int TotalSeekFlag;           // ���� ����������� ������
  int TotalSelectFlag;         // ���� ��������� �������� �� �����
};


  // ************************************************************
  //                                                            *
  //            ���������� ������������ � �������               *
  //                                                            *
  // ************************************************************

// ��������� ���� ����������� ��� ������ ��������
int _fastcall cntSetVisualType(TMapControl * data, int type);

// ���������� ������� ����������� �����
void _fastcall cntSetViewScale(TMapControl * data, double * scale);

// ���������� ������� �����������
int _fastcall cntSetViewScalePlace(TMapControl *mapcnt,
                                   long int *x, long int *y,float scale);

// �������� ������� ����������� ������������ ��������
int _fastcall cntChangeViewScale(TMapControl *mapcnt,
                                 long int *x, long int *y,float change);

// ��������� ������� ������� �����������
double _fastcall cntGetRealShowScale(TMapControl * data);

// ���������� ������� ������� �����������           
double _fastcall cntSetRealShowScale(TMapControl * data, double scale);

// ����������� �������� ������ �����
void _fastcall cntSetRegion(TMapControl * data);

// ���������� �������� ������
int _fastcall cntShowData(TMapControl * data);

// ������� �������� ��������� �������
int _fastcall cntCheckViewObject(TMapControl * data,
                                 TObjectHead * head, TMap * map);

// ��������� "���������" �������
int _fastcall cntTestObject(TMapControl * cont, TObjectHead * head,
                            TMap * map);

// ������ ������� �� �������� ����������� � ������ (��������);
// ����� ����������� ����� ��� ��������,������� ����� �� ������
MAPOBJDESC * _fastcall cntWhatObjectInMap(TMapControl * cont,
                                          MAPOBJDESC * object,
                                          DFRAME * frame, int flag, int nMap,
                                          TMapSelect * select);

// ������ ������� �� �������� ����������� � ������ (��������);
// ����� ����������� ����� ��� ��������,������� ����� �� ������
MAPOBJDESC * _fastcall cntWhatObjectInMapForText(TMapControl * cont,
                                                 MAPOBJDESC * object,
                                                 DFRAME * frame, int flag, int nMap,
                                                 TMapSelect * select);

// ������� ��������� ����������� �������� ������
void _fastcall cntShowSelectData(TMapControl * cont, int mapnumber,
                                 COLORREF color, TMapSelect * select);

// ������� ������������ ����� �� ��� ������, ���� ����������
// �������. ��������� ������ ���������� � �������
int _fastcall cntShowList(TMapControl * cont, int number);

// ������� ��������� ������� �������� �����
int _fastcall cntShowObject(TMapControl * cont, TMap * map,
                            TObjectHead * head, float viewscale);

// ������� ��������� ���������� �������
int _fastcall cntShowInfo(TMapControl * cont, TObjectInfo * object);

//  ������� ��������� ���������� �������               
int _fastcall cntShowSelectInfo(TMapControl * cont, TObjectInfo * object,
                                COLORREF color);

// ����� ������� ����������� ������� �����
int _fastcall cntVisualObject(TMapControl * data, long incode, TMap* map,
                              POLYDATAEX* metric, float scaleview);

// ����� ������� ����������� �������
int _fastcall cntVisualObjectParm(TMapControl * data, VIEPAR* ViewParm,
                                  POLYDATAEX* metric, float scaleview, int scale);

// ������������ ������� �� ��������� ������������ ��������
int _fastcall cntVisualGraphic(TMapControl * data, TObjectHead* head,
                               TMap* map, POLYDATAEX* metric, float scaleview);

// ������� ��������� ������� ���� IMGOBJECT
int _fastcall cntVisualIMGOBJECT(TMapControl * data, POLYDATAEX* metric,
                                 PAINTPARM* image, TMap* map);

// ������� ��������� ������������ ������� ���� IMGOBJECT
int _fastcall cntGraphicIMGOBJECT(TMapControl * data, POLYDATAEX* metric,
                                  PAINTPARM* image, TMap* map,
                                  TObjectHead* head);

  // ************************************************************
  //                                                            *
  //            ������ � "������� �����"                        *
  //                                                            *
  // ************************************************************
  
// ������� �������� ������
void _fastcall cntClose(TMapControl * data);

// ���������� ������� �������� ������
int _fastcall cntIsActive(TMapControl * data);

// ������� ��������� ������
int _fastcall cntOpenMap(TMapControl * data, const char * name, int mode);

// ������� ��������� ������
void _fastcall cntCloseMap(TMapControl * data);

// ������� ������������ ������
int _fastcall cntShowMap(TMapControl * cont);

//  ��������� ������������ ������ ����������� �����
int _fastcall cntAdjustData(TMapControl * data);

// ������� ���������� ����� ����������� �������� �������������� �����
// number - ����� ������������� �����
// ��� ������ ���������� ����
int _fastcall cntOpenTransaction(TMapControl * data, int number, int type);

// ������� ���������� ����� ����������
// ������ ��������������� �������� �������������� �����
// number - ����� ������������� �����
void _fastcall cntCloseTransaction(TMapControl * data, int number);


  // ************************************************************
  //                                                            *
  //        ������ � "���������������� ����������� �����"       *
  //                                                            *
  // ************************************************************

// ��������� ������� ������� �� ������
// ��� ������ ������������ ����
SITCHAIN * _fastcall cntGetSiteChain(TMapControl * data, int number);

// ��������� ����� �� ����������������� ������
TMap * _fastcall cntGetMap(TMapControl * data, int number);

// ������ ����� ������� �������� �� �����
TMapSelect * _fastcall cntGetRealSelect(TMapControl * data, int number);

// ����������� ����� ������� �������� �� �����
void _fastcall cntAdjustRealSelect(TMapControl * data, int number,
                                   int force);

// ������� ����� (�������� � �������)
// ��� ������ ���������� ����
int _fastcall cntOpenSite(TMapControl * data, const char * name, int mode,
                          const char * rscname = 0);

// ������� ����� �� �� ����������������� ������ � ������
// ���� ����� ����� ���� - ����������� ��� �����
void _fastcall cntCloseSite(TMapControl * data, int number);

// ���������/���������� ������� ��������������� ����� �� ������
int _fastcall cntMapEdit(TMapControl * data, int number, int flag);

// ���������/���������� ������� ��������� ����� �� ������
int _fastcall cntMapVisible(TMapControl * data, int number, int flag);

// ���������/���������� ������� �����������  
//  (0 - ��� �������� ������, 1 - ��� �������� ������)
// ��� ������ ���������� -1
int _fastcall cntMapViewOrder(TMapControl * data, int number, int order);

// ���������/���������� ������� ���������� ������ ������� �����
int _fastcall cntMapInquiry(TMapControl * data, int number, int flag);

// ��������� �������� ����� ����� �� ������
const char * _fastcall cntMapFileName(TMapControl * data, int number);

// ��������� �������� �������� ����� �� ������
const char * _fastcall cntMapSheetName(TMapControl * data, int number);

// ������ �������� �������� ��������� ����� �� ������
TMapRsc * _fastcall cntGetResource(TMapControl * data, int number);

// ��������� ����� ����� � �������
int _fastcall cntGetMapNumber(TMapControl * data, TMap * map);

// ������ ������� ������ �������� ��� ������������ �� ������
TMapSelect * _fastcall cntGetViewSelect(TMapControl * data, int number);

// ������ ������� ������ �������� ��� ������ �� ������
TMapSelect * cntGetSeekSelect(TMapControl * data, int number);

// ������ ����� ������� �������� �� �����/
TMapSelect * _fastcall cntGetRealSelect(TMapControl * data, int number);

// ���������� ��� ������ ����������
int _fastcall cntShowSituation(TMapControl * data);

// ���������� ��� ������ ����������  
// order - ������� ����������� (0 - ��� ������, 1 - ��� ������)
int  _fastcall cntShowSituationPlace(TMapControl * data, int order);

// ���������� ������ ����������
int _fastcall cntShowSite(TMapControl * cont,
                          TMap * map, TMapSelect * select, int number);  


  // ************************************************************
  //                                                            *
  //            ������ � "��������� ����������� �����"          *
  //                                                            *
  // ************************************************************


// ���������� ���� ������ � DIB
void _fastcall cntShowBlockRstDib(TMapControl *mapcnt, TRmf *Rstdib,
                                  DIBCONTEXT* dc,       
                                  TBaseColors *colors); 

// ���������� ���� ������-256 � DIB
void _fastcall cntShowBlockRstDib256(TMapControl *mapcnt, TRmf *Rstdib,
                                  DIBCONTEXT* dc,                    
                                  TBaseColors *colors);              

// ���������� �����
int _fastcall cntShowChainRst(TMapControl *mapcnt, int number,
                                  DIBCONTEXT* dc);                    

// ��������� ������� �������
// number - ����� ������ � ������� (number = 0  -  ���������� ���)
void _fastcall cntShowRst(TMapControl *mapcnt, int number);

// ����������� ������� �������
// order - ������� ����������� (0 - ��� ������, 1 - ��� ������)
int _fastcall cntShowRstPlace(TMapControl *mapcnt, int order,
                                  DIBCONTEXT* dc);                    


// ������� ��������� ������
int _fastcall cntOpenRst(TMapControl *mapcnt, const char * name, int mode);

//  ���������������� ����� ������� ��������� ������
// ����� ����������� �-�� ��������� - ActiveRst(RstNumber);
void _fastcall cntInitRstChainUnit(TMapControl *mapcnt,
                                   RSTCHAIN* rstchain, int mini);

// ������� ��������� ������
void _fastcall cntCloseRst(TMapControl *mapcnt, int number);

// ��������� ������� ��������� ������
// ���� ����� �� ����� - ���������� ����
// ��� ������ ���������� -1
int _fastcall cntCheckRstView(TMapControl *mapcnt, int number);

// ���������� ������� ��������� ������
//  view = 0   - �� �����
//  view = 1   - ������
//  view = 2   - ����������
//  view = 3   - ��������������
//  view = 4   - �������
//  view = 5   - ����������
// ��� ������ ���������� -1
int _fastcall cntSetRstView(TMapControl *mapcnt, int number, int view);

// ���������/���������� ��� ����� ����������� ������ (0-8)
// ��� ������ ���������� -1
int _fastcall cntGetRstMaskType(TMapControl *mapcnt, int number);   
int _fastcall cntSetRstMaskType(TMapControl *mapcnt, int number,int masktype);

// ���������/���������� ������� �����������
//  (0 - ��� ������, 1 - ��� ������)
// ��� ������ ���������� -1
int _fastcall cntRstViewOrder(TMapControl *mapcnt, int number, int order);

// ���������������� �������� ������� ��� ������
int _fastcall cntTurnRstViewOrder(TMapControl *mapcnt);  

// ��������� ������� ����������� �����
// ����������:  1 - ����������; 0 - �� ����������; -1 - ������
int _fastcall cntCheckRstPaletteView(TMapControl *mapcnt, int number, int index);

// ���������� ������� ����������� �����
// ��� ������ ������������  -1     =Shabakov D.A.=
int _fastcall cntSetRstPaletteView(TMapControl *mapcnt, int number,int index,int value);

// ��������� ������� ������� �� ������
// ��� ������ ������������ ����
RSTCHAIN* _fastcall cntGetRstChain(TMapControl *mapcnt, int number);

// ��������� ����� ������ �� ������� ����� �����
// ��� ������ ������������ ����
int _fastcall cntGetRstNumberByName(TMapControl *mapcnt, const char * name);

// ��������� ��������� ����� (��� 16- � 256-������� �������)  
//  number - ����� ����� � �������
//  index  - ������ ����� � ������� ������(������� � 0)
//  ����������: 1 - ���� � ������ �������� ������������
//              0 - ���� � ������ �������� �� ������������
//  ��� ������ ���������� -1
int _fastcall cntCheckVisibilityColor(TMapControl *mapcnt, int number,int index);

// ���������� ��������� ����� (��� 16- � 256-������� �������)  
//  number - ����� ����� � �������
//  index  - ������ ����� � ������� ������(������� � 0)
//  value: 1 - �������� ����������� ����� � ������ ��������
//         0 - ��������� ����������� ����� � ������ ��������
//  ���������� ��������� ������ � INI-�����
//                                  (�� ��������� � �������� ����� ������)
//  ��� ������ ���������� 0
int _fastcall cntSetVisibilityColor(TMapControl *mapcnt, int number,int index, int value);

// ���������� ��������� ����� (��� 16- � 256-������� �������)  
//  number - ����� ����� � �������
//  index  - ������ ����� � ������� ������(������� � 0)
//  value: 1 - �������� ����������� ����� � ������ ��������
//         0 - ��������� ����������� ����� � ������ ��������
//  ���������� ��������� ������ � ��������� ����� ������(� ����� � INI-�����)
//  ��� ������ ���������� 0
int _fastcall cntSetVisibilityColorInRstFile(TMapControl *mapcnt, int number,int index, int value);

// ���������� �������� ������ � ������� �
// ����������� ����� �������� ������ �����
int _fastcall cntSetRstPrecision(TMapControl *mapcnt, int number, double precision);

// ��������� �������� ������ � ������ �����
// ���������� ��������� �� �������� � ��������� ������
//  number - ����� ����� � �������
// ��� ������ ���������� ����
DFRAME * _fastcall cntGetRstFrame(TMapControl *mapcnt, int number);

// ��������� �������� ������ � ������ �����
// ���������� ��������� �� �������� ������ � ������
//  number - ����� ����� � �������
// ��� ������ ���������� ����
DFRAME * _fastcall cntGetRstFrameMeters(TMapControl *mapcnt, int number);

//  ������ � ������� ���������� �����
//  number - ����� ����� � �������
//  ��� ������ ���������� 0
int _fastcall cntSetRstColor(TMapControl *mapcnt,
                             int number,COLORREF color,int index);

//  �������� �������� ������� � ������� �������� � ��������������
//  number - ����� ����� � �������
//  ��� ������ ���������� 0
int _fastcall cntRestoreRstPalette(TMapControl *mapcnt, int number);

// ������������� ��������� �����
// value:
// 0 - ���������� ����������� ������ ����������
// 1 - ���������� ����������� ������ ����������
//  ��� ������ ���������� 0
int _fastcall cntInvertRst(TMapControl *mapcnt, int number, int value);

// ���������� ����� ������
int _fastcall cntSetRstBorderPlane(TMapControl *mapcnt,
                                   int number, TDataEdit* data);

// ���������� ����� ������ � ��������� ������  
int _fastcall cntSetRstMask(TMapControl *mapcnt,  int number, TDataEdit* data);

// ��������� ����� ������       
//  ��� ������ ���������� 0
TDataEdit* _fastcall cntGetRstMask(TMapControl *mapcnt, int number);

// ��������� ����� ������
// ��� ������ ���������� 0
TDataEdit* _fastcall cntGetRstBorderPlane(TMapControl *mapcnt, int number);

// ��������� ����������� ������ �� �����
// value = 1 - ���������� ����� �� �����
//       = 0 - ���������� ����� ��� ����� �����
//  ��� ������ ���������� 0
int _fastcall cntShowRstByBorder(TMapControl *mapcnt, int number, int value);

// �������� ����������� ����������� ��������� ������
// oldNumber - ����� ����� � �������
// newNumber - ��������������� ����� ����� � �������
// ��� ������ ���������� 0
int _fastcall cntChangeOrderRstShow(TMapControl *mapcnt,
                                    int oldNumber, int newNumber);

// ��������� ��� ����� ��������� ������
// ��� ������ ���������� ����
const char * _fastcall cntGetRstName(TMapControl *mapcnt, int number);

// ��������� ����� �������� ������� ������
// (� ������ ������� � ������������)
// number - ����� ����� � �������
// ��� ������ ���������� 0
COLORREF* _fastcall cntGetRstPalette(TMapControl *mapcnt, int number);

// ��������� ������� ������� (�� -4 �� 4)
// number - ����� ����� � �������
// ��� ������ ���������� 0
int _fastcall cntGetRstBright(TMapControl *mapcnt, int number);


  // ************************************************************
  //                                                            *
  //            ������ � "��������� ����������� �����"          *
  //                                                            *
  // ************************************************************

// ���������������� ����� ������� ��������� ������
void _fastcall cntInitMtrChainUnit(TMapControl *mapcnt, RMFCHAIN* mtrchain);

// ������� ��������� ������
int _fastcall cntOpenMtr(TMapControl *mapcnt, const char * name, int mode);

// ������� ��������� ������
void _fastcall cntCloseMtr(TMapControl *mapcnt, int number);

// ��������� ������� �������� ����������� � ������
// ��� ����������� ������ (MTR, MTL, MTQ) � �����
void cntInitTables(TMapControl *mapcnt);               

// ����������/��������� ��������� ������� �����
// 0 - ������� �� ������������
int _fastcall cntCheckMtrView(TMapControl *mapcnt, int number);

// ���������� ������� ��������� ������� �����
//  view = 0   - �� �����
//  view = 1   - ������
//  view = 2   - ����������
//  view = 3   - ��������������
//  view = 4   - �������
//  view = 5   - ����������
// ��� ������ ���������� -1
int _fastcall cntSetMtrView(TMapControl *mapcnt, int number,int view);

// ���������/���������� ��� ����� ����������� ������� ����� (0-8)
// ��� ������ ���������� -1
int _fastcall cntGetMtrMaskType(TMapControl *mapcnt, int number);   
int _fastcall cntSetMtrMaskType(TMapControl *mapcnt, int number,int masktype);

// ����������/��������� ������� ���� ������� �����
// value - ���� ��������� ���� (�� 0 �� 16)
//   MTRSHADOW_NONE   =  0,   // ���� �����������
//   MTRSHADOW_PALE   =  1,   // �������
//   MTRSHADOW_WEAK   =  2,   // ������
//   MTRSHADOW_MIDDLE =  4,   // �������
//   MTRSHADOW_HEAVY  =  8,   // �������
//   MTRSHADOW_DEEP   = 16,   // ��������
int _fastcall cntGetMtrShadow(TMapControl *mapcnt);
int _fastcall cntSetMtrShadow(TMapControl *mapcnt, int value);

//-----------------------------------------------------------------
// ����������/��������� ������������� ���� ������� �����
// value - ������������� ���� (�� 0 �� 100)
//-----------------------------------------------------------------
int _fastcall cntGetMtrShadowIntensity(TMapControl *mapcnt);        
int _fastcall cntSetMtrShadowIntensity(TMapControl *mapcnt, int value);

// ����������/��������� ���� ��������� �����������������
// ��������� ����� ������� ������ �����
// (1 - ���������� ���������������� ��������,
//  0 - �������� ���������� � SetRegion)
int _fastcall cntGetMtrChainUserDiapason(TMapControl *mapcnt);      
int _fastcall cntSetMtrChainUserDiapason(TMapControl *mapcnt, int value);

// ��������� ������� ������� �� ������
// ��� ������ ������������ ����
RMFCHAIN* _fastcall cntGetChain(TMapControl *mapcnt, int number);

// ��������� ��� ����� ��������x ������
// ��� ������ ���������� ����
const char * _fastcall cntGetMtrName(TMapControl *mapcnt, int number);

// ���������/���������� ������� �����������
//  (0 - ��� ������, 1 - ��� ������)
// ��� ������ ���������� -1
int _fastcall cntMtrViewOrder(TMapControl *mapcnt, int number, int order);

// ���������� ����� �������
int _fastcall cntSetMtrBorderPlane(TMapControl *mapcnt,
                                   int number, TDataEdit* data);

//  ��������� ����� �������                  
TDataEdit* _fastcall cntGetMtrBorderPlane(TMapControl *mapcnt, int number);

// ��������� ����������� ������� �� �����    
// value = 1 - ���������� ������� �� �����
//       = 0 - ���������� ������� ��� ����� �����
//  ��� ������ ���������� 0
int _fastcall cntShowMtrByBorder(TMapControl *mapcnt, int number, int value);

// ����������� ������� ����������� �������(������������ �����)  
// ���������� 1 - ��� ����������� ������� �� �����
//            0 - ��� ����������� ������� ��� ����� �����
// ��� ������ ���������� -1
int _fastcall cntCheckShowMtrByBorder(TMapControl *mapcnt, int number);

// ����������� ������� �������
// order - ������� ����������� (0 - ��� ������, 1 - ��� ������)
int _fastcall cntShowMtrPlace(TMapControl *mapcnt, CHAININFO *info, int order,
                                  DIBCONTEXT* dc);                


// ��������� ������ �������
// number - ����� ������� � ������� (number = 0  -  ���������� ���)
void _fastcall cntShowMtr(TMapControl *mapcnt, CHAININFO *info, int number);

// ���������� �����
int _fastcall cntShowChainMtr(TMapControl *mapcnt, RMFCHAIN* chain,
                                  DIBCONTEXT* dc);          


// ���������� ���� ������ � DIB
void _fastcall cntShowBlockMtrDib(TMapControl *mapcnt, RMFCHAIN* chain,
                                  DIBCONTEXT* dc); 


// ����� �������� ���������� ������ � �������� �����.
double _fastcall cntGetHeightValue(TMapControl *mapcnt, double x, double y);

// ����� �������� ���������� ������ � �������� ����� �� �������
// � ������� number � �������.                        
// number - ����� ������� � �������.
double _fastcall cntGetMtrHeightValue(TMapControl *mapcnt,
                                      int number,double x, double y);

// ��������� �������� ���������� ������ � ������� �������,
// ��������������� �������� �����.
// number - ����� ������� � �������.
int _fastcall cntPutHeightValue(TMapControl *mapcnt, long int number,
                                double x, double y, double h);

// ����� �������� ���������� ������ � �������� �����.
// ������ ���������� �� ����� ������ ������� �����,� � ������
// ���������������� �������� ����� ������� ������ ����� - �� �����
// ������ ������� �����. ���� ������ �� ������� �� ������,
// ����������� ������ �� TIN-������.
// ���������� ����� �������� � ������ � ������� ���������
// ��������� �����. ���������� �������� ������ � ������.
// � ������ ������ ��� ������ ������ � � ������ ����������������
// �������� ����� ������� � ������� ���������� ERRORHEIGHT.
double _fastcall cntGetPrecisionHeightValue(TMapControl *mapcnt,
                                            double x, double y);

// ������ ���������� ������ ������� ������������� � �������� �����
// �� ������� � ���������� �������� �������� (����� ������).
// ������ ����������� �� ����� ������ ������� �����,� � ������
// ���������������� �������� ����� ������� ������ ����� -
// �� ����� ������ ������� �����. ���� ������ �� ������� �� ������,
// ����������� ������ �� TIN-������.
// ���������� ����� (x,y) �������� � ������ � ������� ���������
// ��������� �����. ���������� �������� ������ � ������.
// � ������ ������ ��� ������ ������ � � ������ ����������������
// �������� ����� ������� � ������� ���������� ERRORHEIGHT.
double _fastcall cntGetPrecisionHeightTriangle(TMapControl *mapcnt,
                                               double x, double y);

//   ����� ������� �������� ���������� �����, ���������������
//   ���������� ���������, ������� �� �������� �������.
//   ��� ������ ���������� ����
int _fastcall cntGetHeightArray(TMapControl*  mapcnt,
                                double*       HeightArray,
                                int           HeightCount,
                                DOUBLEPOINT*  FirstPoint,
                                DOUBLEPOINT*  SecondPoint);

// ��������� �������� ����� ��������� ������
// number - ����� ����� � �������
// describe - ����� ���������, � ������� ����� ���������
// �������� �������
// ��� ������ ���������� ����
int _fastcall cntGetMtrDescribe(TMapControl*  mapcnt,
                                int number, MTRDESCRIBE * describe);

// ��������� ������ � �������� ��������� ������
// number - ����� ����� � �������
// projectiondata - ����� ���������, � ������� ����� ���������
// ������ � ��������
// ��� ������ ���������� ����
int _fastcall cntGetMtrProjectionData(TMapControl*  mapcnt,
                                      int number, MTRPROJECTIONDATA* projectiondata);


// ��������� ������ � �������� ��������� ������    
// number - ����� ����� � �������
// mapregister - ����� ���������, � ������� ����� ���������
// ������ � ��������
// ��� ������ ���������� ����
int _fastcall cntGetMtrProjectionDataEx(TMapControl *mapcnt,
                                      int number, MAPREGISTEREX* mapregister);

// ���������� ������ � �������� ��������� ������   
// number - ����� ����� � �������
// mapregister - ����� ���������
// ��� ������ ���������� ����
int _fastcall cntSetMtrProjectionDataEx(TMapControl *mapcnt,
                                         int number, MAPREGISTEREX* mapregister);

// ��������� �������� ��������� ����� ������� � �������
// number � �������
// colornumber - ����� ��������� �����
// colordesc - ����� ���������, � ������� ����� ���������
// �������� ��������� �����
// ��� ������ ���������� ����
int _fastcall cntGetMtrColorDesc(TMapControl*  mapcnt,
                                 int number, int colornumber,
                                 MTRCOLORDESCEX * colordesc);

// ���������� ���� ��������� ����� ������� � �������
// number � �������
// colornumber - ����� ��������� �����
// ��� ������ ���������� ����
int _fastcall cntSetMtrColor(TMapControl*  mapcnt,
                             int number,COLORREF color,
                             int colornumber);

// ��������� ����� � ������� ��� �������, �������������
// � �������� �����
// number - ���������� �����, ��������� ������� � �����
// (1 - ������ � ������ �����, 2 - ������ ...)
// ��� ������ ������������ ����
int _fastcall cntGetMtrNumberInPoint(TMapControl*  mapcnt,
                                     double x, double y, int number);

// �������� ����������� ����������� ������    
// oldNumber - ����� ����� � �������
// newNumber - ��������������� ����� ����� � �������
//  ��� ������ ���������� 0
int _fastcall cntChangeOrderMtrShow(TMapControl*  mapcnt,
                                    int oldNumber, int newNumber);

// ���������������� ���������� ����������� �������  
void _fastcall cntInitMtrShowVariables(TMapControl* mapcnt);

// ���������������� ���������� ����������� ������� ����� 
void _fastcall cntInitMtlShowVariables(TMapControl* mapcnt);

// ������� Rmf ������
int _fastcall cntOpenRmf(TMapControl *mapcnt, const char * name, int mode,
                         int flag);

// ������� Rmf ������
void _fastcall cntCloseRmf(TMapControl* mapcnt, CHAININFO *info, int number);

// ��������� ������� ������� �� ������
// ��� ������ ������������ ����
RMFCHAIN* _fastcall cntGetRmfChain(CHAININFO *info, int number);

// ��������� ����� ������� �� ����� �����         
// ��� ������ ������������ ����
int _fastcall cntGetRmfNumberByName(CHAININFO *info, const char * name);

// ��������� ������������ ���� ���. ����-���������
void _fastcall cntCheckMapTypeRmf(TMapControl *mapcnt, RSTCHAIN *chain);

// ��������� ��������� ������� � �����
int _fastcall cntCheckDimensionRmf(TMapControl *mapcnt, RSTCHAIN *chain);

// ��������� ������������ ���� ����� ������� � ����������� �������  
int _fastcall cntCheckMtrTypeRmf(TMapControl *mapcnt, RSTCHAIN *chain, int curType);

// ��������� ������� ���������
// ����������: 1- ����� �����; 0- ����� �� �����         
// ��� ������ ���������� -1
int _fastcall cntCheckRmfView(CHAININFO *info, int number);

// ���������� ������� ���������
//  view = 0   - �� �����
//  view = 1   - ������
//  view = 2   - ����������      //  ���������� �������� 
//  view = 3   - ��������������  //  ���������� �������� 
//  view = 4   - �������         //  ���������� �������� 
//  view = 5   - ����������      //  ���������� �������� 
// ��� ������ ���������� -1
int _fastcall cntSetRmfView(CHAININFO *info, int number, int view);

// ���������/���������� ������� ������������ �����������  
// procentValue - ������������ ����������� (�� 0 �� 100%)
// ��� ������ ���������� -1
int _fastcall cntGetRmfTransparent(CHAININFO *info, int number);
int _fastcall cntSetRmfTransparent(CHAININFO *info, int number, int procentValue);

// ���������/���������� ��� ����� ����������� (0-8)
// ��� ������ ���������� -1
int _fastcall cntGetRmfMaskType(CHAININFO *info, int number);   
int _fastcall cntSetRmfMaskType(CHAININFO *info, int number,int masktype);

// ���������/���������� ������� �����������
//  (0 - ��� ������, 1 - ��� ������)
// ��� ������ ���������� -1
int _fastcall cntRmfViewOrder(CHAININFO *info, int number, int order);

// ���������������� �������� ������� ��� ������
int _fastcall cntTurnRmfViewOrder(CHAININFO *info);  

// ��������� ������� ����������� �����
// ����������:  1 - ����������; 0 - �� ����������; -1 - ������
int _fastcall cntCheckRmfPaletteView(CHAININFO *info, int number, int index);

// ���������� ������� ����������� �����
// ��� ������ ������������  -1
int _fastcall cntSetRmfPaletteView(CHAININFO *info, int number,int index,int value);

// ���������� �������� � �������
int _fastcall cntSetRmfPrecision(CHAININFO *info, int number, double precision);

// ��������� �������� � ������ �����
// ���������� ��������� �� �������� � ��������� ������
//  number - ����� ����� � �������
// ��� ������ ���������� ����
DFRAME * _fastcall cntGetRmfFrame(CHAININFO *info, int number);

// ��������� �������� � ������ �����
// ���������� ��������� �� �������� ������ � ������
//  number - ����� ����� � �������
// ��� ������ ���������� ����
DFRAME * _fastcall cntGetRmfFrameMeters(CHAININFO *info, int number);

// ��������� ��� ����� ������
// ��� ������ ���������� ����
const char * _fastcall cntGetRmfName(CHAININFO *info, int number);

// ��������� ����� �������� ������� ������
// (� ������ ������� � ������������)
// number - ����� ����� � �������
// ��� ������ ���������� 0
COLORREF* _fastcall cntGetRmfPalette(CHAININFO *info, int number);

// ���������/���������� ������� ������� (�� -4 �� 4)
// number - ����� ����� � �������
// ��� ������ ���������� 0
int _fastcall cntGetRmfBright(CHAININFO *info, int number);

// ����� �������e ������ � �������� ����� �� ������� ������.
// ���������� ����� �������� � ������ � ������� ���������
// ��������� �����. ���������� �������� ������ � ������.
// � ������ ������ ��� ������ ������ � � ������ ����������������
// �������� ����� ���������� ������� height = ERRORHEIGHT,
// ���������� 0.
int _fastcall cntGetRmfElementHeight(CHAININFO *info, double x, double y,
                                     double *height);

// ����� �������e ������ � �������� ����� �������.
// ���������� ����� �������� � ������ � ������� ���������
// ��������� �����. ���������� �������� ������ � ������.
// � ������ ������ ��� ������ ������ � � ������ ����������������
// �������� ����� ���������� ������� height = ERRORHEIGHT.
// ���� ����� ��� ������� ��� ������ ��� ������ ���������� 0
int _fastcall cntGetRmfElementHeightChain(RMFCHAIN *chain, double x, double y,
                                          double *height);

// ��������� �������� ���������� ������ � ������� �������,
// ��������������� �������� �����.
// number - ����� ������� � �������.
// ���������� ����� (x,y) � �������� ������ (h) �������� � ������
// � ������� ��������� ��������� �����.
// � ������ ������ ���������� ����.
int _fastcall cntPutRmfHeightValue(CHAININFO *info, long int number,
                                   double x, double y, double h);

// ��������� �������� ����� ��������� ������
// number - ����� ����� � �������
// describe - ����� ���������, � ������� ����� ���������
// �������� �������
// ��� ������ ���������� ����
int _fastcall cntGetRmfDescribe(CHAININFO *info,
                                int number, MTRDESCRIBE * describe);

// ��������� ������ � �������� ��������� ������
// number - ����� ����� � �������
// projectiondata - ����� ���������, � ������� ����� ���������
// ������ � ��������
// ��� ������ ���������� ����
int _fastcall cntGetRmfProjectionData(CHAININFO *info,
                                      int number, MTRPROJECTIONDATA* projectiondata);


// ��������� ������ � �������� ��������� ������   
// number - ����� ����� � �������
// projectiondata - ����� ���������, � ������� ����� ���������
// ������ � ��������
// ��� ������ ���������� ����
int _fastcall cntGetRmfMapRegisterEx(CHAININFO *info,
                                      int number, MAPREGISTEREX* projectiondata);

// ���������� ������ � ��������      
// number - ����� ����� � �������
// mapregister - ����� ���������, � ������� ����� ���������
// ������ � ��������
// ��� ������ ���������� ����
int _fastcall cntSetRmfMapRegisterEx(CHAININFO *info,
                                      int number, MAPREGISTEREX* mapregister);


// ��������� ����� � ������� ��� �������, �������������
// � �������� �����
// number - ���������� �����, ��������� ������� � �����
// (1 - ������ � ������ �����, 2 - ������ ...)
// ��� ������ ������������ ����
int _fastcall cntGetRmfNumberInPoint(CHAININFO *info,
                                     double x, double y, int number);

// �������� ����������� ����������� ������
// oldNumber - ����� ����� � �������
// newNumber - ��������������� ����� ����� � �������
//  ��� ������ ���������� 0
int _fastcall cntChangeOrderRmfShow(CHAININFO *info,
                                    int oldNumber, int newNumber);

// ����������� ��������� � ������� ��������� �������
int _fastcall cntCheckViewRmf(TMapControl *mapcnt);

// ���������� �����
int _fastcall cntSetRmfBorderPlane(CHAININFO *info,
                                   int number, TDataEdit* data);

//  ��������� �����
TDataEdit* _fastcall cntGetRmfBorderPlane(CHAININFO *info, int number);

#ifndef HIDEMTQ    

// ===========================================================
//           ������� �������  
// ===========================================================

// ������� ������ ������� �������
int _fastcall cntOpenMtq(TMapControl *mapcnt, const char * name,
                         int mode);

// ������� ������ ������� �������
void _fastcall cntCloseMtq(TMapControl *mapcnt, int number);

// ��������� ���������� ������ � ������� ������� �������
// ��� ������ ���������� 0
int _fastcall cntGetMtqPaletteCount(RMFCHAIN *chain);

// ��������� �������� ��������� ����� ������� ������� � �������
// number � �������
// colordesc - ����� ���������, � ������� ����� ���������
// �������� ��������� �����
// ��� ������ ���������� ����
int _fastcall cntGetMtqColorDesc(TMapControl *mapcnt,long int number,
                                 long int colornumber,
                                 MTRCOLORDESCEX * colordesc);

// ����������/��������� ���� ������� ��������
// value - ���� ��������� ���� (1 - ���� ����, 0 - ���� ���)
int _fastcall cntSetMtqShadow(TMapControl *mapcnt, int number, int value);  
int _fastcall cntGetMtqShadow(TMapControl *mapcnt, int number);

// ���������� ���� ��������� ����� ������� ������� � �������  // number � �������
// colornumber - ����� ��������� �����
// ��� ������ ���������� ����
int _fastcall cntSetMtqColor(TMapControl*  mapcnt,
                             int number,COLORREF color,
                             int colornumber);

// ��������� ��������� ����� ������� ������� (�� 256-������)
//  number - ����� ����� � �������
//  index  - ������ ����� � ������� �������(������� � 0)
//  ����������: 1 - ���� � ������ �������� ������������
//              0 - ���� � ������ �������� �� ������������
//  ��� ������ ���������� -1
int _fastcall cntCheckMtqVisibilityColor(TMapControl *mapcnt,
                                         int number,int index);

// ��������� ������� ������� �� ������
// ��� ������ ������������ ����
RMFCHAIN* _fastcall cntGetMtqChain(TMapControl *mapcnt, int number);

// ��������� ����������� ������� �� �����    
// value = 1 - ���������� ������� �� �����
//       = 0 - ���������� ������� ��� ����� �����
//  ��� ������ ���������� 0
int _fastcall cntShowMtqByBorder(TMapControl *mapcnt, int number, int value);

// ����������� ������� ����������� �������(������������ �����)
// ���������� 1 - ��� ����������� ������� �� �����
//            0 - ��� ����������� ������� ��� ����� �����
// ��� ������ ���������� -1
int _fastcall cntCheckShowMtqByBorder(TMapControl *mapcnt, int number);

// �������� ����������� ����������� ������ �������
// oldNumber - ����� ����� � �������
// newNumber - ��������������� ����� ����� � �������
//  ��� ������ ���������� 0
int _fastcall cntChangeOrderMtqShow(TMapControl*  mapcnt,
                                    int oldNumber, int newNumber);

// ���������� ����� ������� �������
int _fastcall cntSetMtqBorderPlane(TMapControl *mapcnt,
                                   int number, TDataEdit* data);

// ��������� ����� ������� �������
TDataEdit* _fastcall cntGetMtqBorderPlane(TMapControl *mapcnt, int number);

// ��������� ������ � �������� ������� �������          
// number - ����� ����� � �������
// mapregisterex - ����� ���������, � ������� ����� ���������
// ������ � ��������
// ��� ������ ���������� ����
int _fastcall cntGetMtqProjectionData(TMapControl *mapcnt,
                                      int number, MAPREGISTEREX* mapregisterex);

// ���������� ������ � �������� ������� �������    
// number - ����� ����� � �������
// mapregister - ����� ���������
// ��� ������ ���������� ����
int _fastcall cntSetMtqProjectionData(TMapControl *mapcnt,
                                      int number, MAPREGISTEREX* mapregister);

// �������� � ���� ������� ������� �������         
// (���������� ������ ������ �������� 256,
//  ����� ������ - ADDITION.MatrixColorCount)
// chain - ����� �������
// palette - ����� �������� �������
// count - ����� ������ �������� �������
// ��� ������ ���������� ����
int _fastcall cntResetMtqPalette(RMFCHAIN* chain,
                                 COLORREF *palette, int count);

// ����������/��������� ��������� ������� ��������  
//  view = 0   - ������� �������� �� ������������
//  view = 1   - ������
//  view = 2   - ����������
//  view = 3   - ��������������
//  view = 4   - �������
//  view = 5   - ����������
int _fastcall cntCheckMtqView(TMapControl *mapcnt, int number);
int _fastcall cntSetMtqView(TMapControl *mapcnt, int number, int view);

#endif

#endif  // MAPCNT_H

