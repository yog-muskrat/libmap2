#ifndef MAPBASE_H
#define MAPBASE_H

#ifndef MAPTYPE_H
  #include "maptype.h"
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

#ifndef HIDETIN
 #ifndef TINBASE_H
   #include "tinbase.h"
 #endif
#endif

enum OUTPUTTYPE
{
  OUTPUT_DIB    = 0,
  OUTPUT_DEVICE = 1
};

// ----------------------------------------------------------------
// ���� ������� ������������ � �������� ��������� ��������
// ----------------------------------------------------------------
#ifndef WINCE
typedef void _fastcall (*VISUALTABLE)(void* pm, const POLYDATAEX* data,
                                      const char * parm, float viewscale);

typedef int  _fastcall (*TESTTABLE)(void* pm, const POLYDATAEX* data,
                                     const char* parm, float viewscale);
#else
typedef void (_fastcall *VISUALTABLE)(void* pm, const POLYDATAEX* data,
					   			                           const char * parm, float viewscale);

typedef int  (_fastcall *TESTTABLE)(void* pm, const POLYDATAEX* data,
                                    const char* parm, float viewscale);

#endif


// ���������� ������� Rst, Mtr, Mtq ������  
// =========================================================
typedef struct RMFCHAIN
{
  // ����� ��� ����

#ifdef __cplusplus  
  RMFCHAIN() : Colors() {}

  RMFCHAIN*  Next;            // ��������� �� ��������� ���������
  RMFCHAIN*  Back;            // ��������� �� ���������� ���������
#else
  void*      Next;            // ��������� �� ��������� ���������
  void*      Back;            // ��������� �� ���������� ���������
#endif

  int        View;            // ������� ��������� = ��� ����� (0-5)     
  int        ViewOrder;       // ������� ����������� (0/1 - ���/��� ������)
  int        MaskType;        // ��� ����� (0-8)
  int        Free;
//   FILETIME   Condition;       // ��������� ����� ������  

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
#ifdef __cplusplus
  TBaseColors Colors;            // ����� ����������� ������
#else
  BASECOLORS  Colors;            // ����� ����������� ������
#endif

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
#ifdef __cplusplus
  TRmf      Rmf;
#else
  TRMFDATA  Rmf;
#endif
}
  RMFCHAIN;


// ������� ���������� � ������e  
// =========================================================
typedef struct CHAININFO
{
 int         Count;         // ���������� �������
 RMFCHAIN*   Begin;         // ������ ����� �������
 int         CurrentNumber; // ����� �������� ������� � �������
}              CHAININFO;



typedef RMFCHAIN RSTCHAIN;
typedef RMFCHAIN MTRCHAIN;


// ������� ���������������� ����

typedef struct SITCHAIN
{
#ifdef __cplusplus           
  SITCHAIN() : Site(), Select(), Seek(), Real() { Next,Back = 0; }

  SITCHAIN*  Next;           // ��������� �� ��������� ���������
  SITCHAIN*  Back;           // ��������� �� ���������� ���������
#else
  void*      Next;           // ��������� �� ��������� ���������
  void*      Back;           // ��������� �� ���������� ���������
#endif
  TSite      Site;           // ���������������� �����
  TMapSelect Select;         // ������� �����������
  TMapSelect Seek;           // ������� ������
  TMapSelect Real;           // ����� ������� �������� �� �����
  int    RealMode;           // ��������� ����� ��� �����
  int        ViewOrder;      // ������� ����������� (0 - ��� ������, 1 - ��� ������) 
#ifdef LINUXAPI    
  unsigned
      char  ArrayIndex[256]; // ������ �������� ������������ ������
#endif
}
  SITCHAIN;

#ifndef HIDETIN
// ������� TIN-������          

typedef struct TINCHAIN
{
  TINCHAIN() : Colors() {}

  TINCHAIN* Next;              // ��������� �� ��������� ���������
  TINCHAIN* Back;              // ��������� �� ���������� ���������

  long int  Mode;              // ����� ������� (Read/Write)
  long int  Share;             // ����� ���������� ������

  long int  View;              // ������� ��������� = ��� ����� (0-5)
  long int  ViewOrder;         // ������� ����������� (0/1 - ���/��� ������)

  long int  MaskType;          // ��� ����� (0-8)
  long int  Free;              // ������������

  DFRAME    Frame;             // �������� � ������ (��������)  
  DFRAME    FrameMeters;       // �������� � ������ (�����)

  double    MinHeightValue;    // ����������� �������� ������ ����������� (�����)
  double    MaxHeightValue;    // ������������ �������� ������ ����������� (�����)

  long int  VertexCount;       // K��������� ������
  long int  TriangleCount;     // K��������� �������������

  long int  UserLabel;         // ���������������� �������������
  long int  Length;            // ����� ����� � ����������

  long int  ModelType;         // ��� ������
  long int  Method;            // ����� ���������� ������

  long int  TopScale;          // ����������� �������� ������� ������� ���������
  long int  BottomScale;       // ����������� �������� ������ ������� ���������

  TBaseColors  Colors;         // ����� ����������� TIN-������

  TTin      Tin;
}
  TINCHAIN;
#endif  // HIDETIN


// ��������� �� ������� ������� ������� �����������     
// base - ��������� �� MAPBASE
#ifndef WINCE
typedef void _fastcall (*DEVICETABLE)(void* base, const POLYDATAEX* data,
                                      const char* parm, float viewscale);
#else
typedef void (_fastcall *DEVICETABLE)(void* base, const POLYDATAEX* data,
                                      const char* parm, float viewscale);
#endif

typedef struct MAPBASE
{
 // �������� ��������� �����
 // --------------------------

 TMap Map;                // ��������� ����� (������ ���������� !)

 int VisualType;          // ��� ������������ �����

 int RangeScale;          // ���� �� ������� ����������� ���� ���
                          // �������� �������� �����

 long int ShowScale;      // ������� ������� ����������� �����
 long int BaseScale;      // ������� ������� ����������� �����

 TMapSelect Select;       // ������� ������ ��'����� ��� �����������
 TMapSelect Seek;         // ������� ������ ��'����� ��� ���������
 int ViewSeekFlag;        // ���� ������ ����� ������� ��'�����

 TMapSelect Real;         // ����� ������� ��'����� �� �����
 int    RealMode;         // ��������� ����� ��� �����


 // ������ ��� ���������� �����
 // --------------------------

 void * MapBase;      // ��������� �� ��������� ������
                      // ��� ������������� ������������/�����������

 DFRAME RegionPix;    // �������� ������ ������ � ��������   
 FRAME DrawPix;       // ������� ����������� � ��������
 FRAME SaveDrawPix;   // � ������ ����� (1-�.�.; 2-�.�.)

 DFRAME RegionDis;    // �������� ������ ������ � ���������
 DFRAME DrawDis;      // ������� ����������� � ���������
                      // � ������ ����� (1-�.�.; 2-�.�.)

 DFRAME DrawMet;      // ������� ����������� ����������
                      // � ������ (1-�.�.; 2-�.�.)

 double ZeroX;        // ���������� ����� �������� �����
 double ZeroY;        // � ������������� ������� ��������� (�����)

 double MetInDis;     // ������ �� ��������� � ����� ��������
 double DisInMet;     // ����� ������� �� ���� ���������

 double ViewScale;    // ������� ������� �����������
                      // = 5   -> ����������� ��������� � 5 ���
                      // = 0.1 -> ����������� ��������� � 10 ���

 double VerticalPixel;    // ����� ����� �� ���� �� ����������
 double HorizontalPixel;  // ����� ����� �� ���� �� ����������
 double Discret;          // ����� ����� �� ���� �� �����

 double HorDisInPix;     // ����� ����� ����� � ����� ������
 double HorPixInDis;     // ����� ����� ������ � ����� �����
 double VerDisInPix;     // ����� ����� ����� � ����� ������
 double VerPixInDis;     // ����� ����� ������ � ����� �����

 double Element;         // ����� ��������� �� ���� � ������
 double HorElemInPix;    // ����� ��������� ������ � ����� ������
 double HorPixInElem;    // ����� ����� ������ � �������� ������
 double VerElemInPix;    // ����� ��������� ������ � ����� ������
 double VerPixInElem;    // ����� ����� ������ � �������� ������

 double DisInElem;       // ����� ����� ����� �� �������
 double ElemInDis;       // ����� ��������� � ����� ������

 double Angle;           // ���� �������� �����
 double SinTurn;         // sin ���� �������� �����
 double CosTurn;         // cos ���� �������� �����
 int TurnActive;         // ���� ����������� ��������


 FRAME ListDrawBorder;    // ������� ������������ ������� � �����
                          // ��� �������� ��������� ��������

 POLYDATAEX  PolyData;      // �������� ������� ���������� �������������
                          // ������� � ������� ������������

 DOUBLEPOINT AreaInList;  // ��������� ������� ������������ �
                          // ������� ����� �����

 // �������� ���������������� ����
 // -------------------------------

 int         SitChainCount;    // ���������� �������
 SITCHAIN *  SitChainBegin;    // ������ ����� �������
 int         SitCurrentNumber; // ����� �������� �����

 // �������� ��������� ����
 // -------------------------------

 FRAME FrameFillPix;
 FRAME FrameRst;

 CHAININFO  RstChain;          // �������� � ��������� �������
 CHAININFO  MtqChain;          // �������� � ������� ������ �������

 // �������� ��������� ����
 // -------------------------------

 TMtrPalette  MtrPalette;      // ������� �������

 int MtrShadow;                // ���� ������ �����      
 int Reserve;

 FRAME FrameMtr;

 double MtrChainMinHeight;     // ����������� ������ �������
 double MtrChainMaxHeight;     // ������������ ������ �������

                               
 int    MtrChainUserDiapason;  // ���� ��������� �����������������
                               // ��������� ����� �������
                               // (MtrChainMinHeight, MtrChainMaxHeight)
                               // (1 - ���������� ���������������� ��������,
                               //  0 - �������� ���������� � SetRegion)
 int    Reserve2;

 CHAININFO  MtrChain;          // �������� � ��������� �������

 // ������� ���������� ����������� ������ � �������
 // -----------------------------------------------

 int BorderFilter;      // ������ �� �����
 int MaskType;          // ��� �����
 int MaskStep;          // ��� �����
 char Mask[8];          // ���������� �����

 int ESize;             // ������ ��������
 DFRAME* DFrameElem;    // ������� ������ � ���������
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
 int StringBlockAddr;    // ����� ������ ������������ ����� BlockAddr   
 int ColumnBlockAddr;    // ����� ������� ������������ ����� BlockAddr  
 char* ColumnAddr1;     // ��������� �� ������� � �������� ������  
 char* ColumnAddr2;     // (��� ��������� ��������� �����)
 double StringInBlockBegin;
 double ColumnInBlockBegin;
 double StringInBlockFloat;
 double ColumnInBlockFloat;

 unsigned char ColorFilter[256];  // ������ �� ����� (��� ������)
 /*  
 double MtrMinHeight;         // ���. � ����. ������ ���� �������
 double MtrMaxHeight;         // � �������� ������� �������

 double dH;                   // ��������, �������� ��������� ����� �������
                              // (��� ���������� ������� � �������)
 */

 VISUALTABLE* DibFunc;        // ��������� �� ������� ������� ��� DIB

 int TypeOutput;              // ������ �����������

 HPALETTE ViewPalette;        // ������������� ������� ����
 unsigned char
        ArrayIndexMap[272];   // ������ �������� ������������ ������  

 BREAKCALL BreakCall;         // ������� ��������� ������
 long int  BreakParm;         // ��� ���������� �����������

 BEFOREPAINT BeforePaint;     // ������� ��������� ������      
 long int    BeforeParm;      // ��� ��������� ��� ������

 // ���������� ������ TPaintDevice
 // ---------------------------------

 HDC hdc;               // �������� ����������
 HDC hdcDib;            // �������� ���������� ���������������� DIB ��� ��������
 int Technology;        // ��� ����������

 double HorLogicalInch; // �������� ���������� � ���������� �����
                        // �� �����������
 double VerLogicalInch; // �������� ���������� � ���������� �����
                        // �� ���������
 HDC Savehdc;
 int SaveTechnology;

 double SaveHorLogicalInch;
 double SaveVerLogicalInch;

 DRAWSIZE DrawSize;     // ������ � ������ ������� ���������

 // ���������� ������ TPaintMetric
 // ---------------------------------

 COLORREF Palette[272];        // ������� �����
 COLORREF PaletteFill[272];    // ������� ������� ��������� ��������
 COLORREF PaletteCMYK[272];    // ������� ����� CMYK       

 int ColorModel;               // ����������� ����� � �������������� �������� ������(0-RGB, 1-CMYK)  
 long int ClearColor;          // ���� ������� ������� ��������� � DIB       
                               // (��� RGB-0x0FFFFFFL, ��� CMYK-0x0000000L)
 int ColorCount;               // ���������� ������ � CMYK ������� �����     
 int MapNumber;                // ����� �������������� �����                 

 int FillIntensity;            // ������������� ����� ������� ����������
 int SaveFillIntensity;        // ������������� ��� ������
 float Intensity;              // ������� ������������� ����� ������� ����������

 double PixDeviceInPixScreen;   // �������� ���������� � ������� ������
 double PixDeviceFontIn100Mkm;  // �������� ���������� � ������� �����
                                 // ���������� (��� ������)
 double SavePixDeviceInPixScreen;
 double SavePixDeviceFontIn100Mkm;

 double HorPixDeviceInMkm;   // �������� ���������� � ���
 double VerPixDeviceInMkm;   // �������� ���������� � ���
 double PixDeviceFontInMkm;  // �������� ���������� ������ ������
                             // � ��� ������ ��������

 double SaveHorPixDeviceInMkm;
 double SaveVerPixDeviceInMkm;
 double SavePixDeviceFontInMkm;

 DEVICETABLE* DeviceFunc;     // ��������� �� ������� �������

 int SelectColor;             // ���� ��������� �������� �� �����
                              // (-1 - �� ��������)
 int SelectThick;             // ������� ����� ��������� ��������


 // ���������� ������ TMapPaint
 // ---------------------------------

 int  FlagDib;                // ���� ������ � DIB (������������ �������
                              // ��������� � �������� DIB)

 TMapPalette MapPalette;      // ������� ������������ �����


 // ���������� ������ TMapAccess
 // ---------------------------------

 int TotalSeekFlag;           // ���� ����������� ������
 int TotalSelectFlag;         // ���� ��������� �������� �� �����

 char MapDocName[MAX_PATH];   // ��� ����� ���������

#ifdef __cplusplus
 char MapIniName[MAX_PATH];   // ��� INI ����� ���������

 int  IsProjectActive;        // ������� �������� �������
 char ProjectName[MAX_PATH];  // ��� ����� �������

 int  HideSplineFlag;         // ������� ������ ���������� �������
#endif

#ifdef WIN32API               
 HWND EventHandle;            // ������������� ���� ��� ���������� � ��������
 int  EventFlag;              // ���� ����� �������
#endif

 int  SkeepTextFlag;          // ������� ������ ������� � ����� ���������   
 int  IsRestoreData;          // ������� �������������� ������ �������� ������ �� INI-�����
}
  MAPBASE;



#endif  // MAPBASE_H
