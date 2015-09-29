
#ifndef MAPTYPE_H
#define MAPTYPE_H

#ifndef MAPMACRO_H
 #include "mapmacro.h"
#endif

#ifndef MAPERR_RH
  #include "maperr.rh"
#endif

#define LT left
#define RT right
#define UP top
#define DN bottom

// �������� ��������� ��������� ��� ������������

#define DELTANULL  ((double)(1e-3))    // 23/03/00

// �������� ��������� ��������� ��� ���������� ��������

#define DOUBLENULL  ((double)(1e-6))   // 26/04/00

// ������� ����������                  // 06/06/00

#define ROUND(x)    (((x) < 0) ? (long int)((x) - 0.5) : (long int)((x) + 0.5))


typedef struct SHORTPOINT    // ���������� �����
{
  unsigned short int X;
  unsigned short int Y;
}
  SHORTPOINT;

typedef struct LONGPOINT     // ���������� ����� (������� �������)
{
#ifdef __cplusplus        // 11/04/01
  union { LONG x; LONG X; };
  union { LONG y; LONG Y; };
#else
  long int X;
  long int Y;
#endif
}
  LONGPOINT;

typedef struct FLOATPOINT    // ���������� ����� (��������� �������)
{
  float X;
  float Y;
}
  FLOATPOINT;

typedef struct DOUBLEPOINT   // ���������� ����� (��������� �������)
{
#ifdef __cplusplus           // 11/04/01
  union { double x; double X; };
  union { double y; double Y; };

  void operator  = (double value)  {         x  = value;   y  = value;  }
   int operator != (double value)  { return (x != value || y != value); }
   int operator == (double value)  { return (x == value && y == value); }
#else
  double X;
  double Y;
#endif
}
  DOUBLEPOINT;


typedef struct DRAWPOINT     // ������ TPoint
{
#ifdef __cplusplus
  union { XYTYPE x; XYTYPE X; };           // 13/09/00
  union { XYTYPE y; XYTYPE Y; };

  void operator  = (int value)  {         x  = value;   y  = value;  }
   int operator != (int value)  { return (x != value || y != value); }
   int operator == (int value)  { return (x == value && y == value); }

  DRAWPOINT& operator - (DRAWPOINT& draw)
    { x -= draw.x;  y -= draw.y;  return *this;}

  DRAWPOINT& operator + (DRAWPOINT& draw)
    { x += draw.x;  y += draw.y;  return *this;}
#else        // 11/04/01
  XYTYPE X;
  XYTYPE Y;
#endif
}
  DRAWPOINT;


typedef struct DRAWSIZE      // ������ TSize
{
#ifdef __cplusplus           // 11/04/01
  union { int cx; int CX; };
  union { int cy; int CY; };

  void operator  = (int value)  {         cx  = value;   cy  = value;  }
  int operator != (int value)  { return (cx != value || cy != value); }
  int operator == (int value)  { return (cx == value && cy == value); }

  DRAWSIZE& operator - (DRAWSIZE& draw)
    { cx -= draw.cx;  cy -= draw.cy;  return *this;}

  DRAWSIZE& operator + (DRAWSIZE& draw)
    { cx += draw.cx;  cy += draw.cy;  return *this;}
#else
  int CX;
  int CY;
#endif
}
  DRAWSIZE;


typedef struct DRAWLINE      // ���������� �����
{
  DRAWPOINT First;
  DRAWPOINT Second;
}
  DRAWLINE;


//-----------------------------------------------------------------
// ���������� �������������� � ������ �����
// (X �����, Y ������, ������� ����������)
//-----------------------------------------------------------------

typedef struct FRAME         // �����
{
  long X1;
  long Y1;
  long X2;
  long Y2;

#ifdef __cplusplus
  void operator = (long value)
  {
    X1 = value;  Y1 = value;
    X2 = value;  Y2 = value;
  }

  FRAME operator = (FRAME frame)
  {
    X1 = frame.X1;  Y1 = frame.Y1;
    X2 = frame.X2;  Y2 = frame.Y2;  return *this;
  }

  int operator != (long value)
  {
    return ( X1 != value || Y1 != value ||
             X2 != value || Y2 != value );
  }

  int operator == (long value)
  {
    return ( X1 == value && Y1 == value &&
             X2 == value && Y2 == value);
  }
#endif
}
  FRAME;


typedef struct DFRAME        // ���������
{
  double X1;
  double Y1;
  double X2;
  double Y2;

#ifdef __cplusplus
  void operator = (double value)
  {
    X1 = value;  Y1 = value;
    X2 = value;  Y2 = value;
  }
#endif
}
  DFRAME;


//-----------------------------------------------------------------
// ���������� �������������� � ����
// (X ������, Y ����, ������� ����������)
//-----------------------------------------------------------------

typedef struct BOX           // �����
{
#ifdef __cplusplus    // 11/04/01
  union { long LT;  long lt; };
  union { long UP;  long up; };
  union { long RT;  long rt; };
  union { long DN;  long dn; };

  void operator = (long value)
  {
    LT = value;  UP = value;
    RT = value;  DN = value;
  }
#else
  long LT;
  long UP;
  long RT;
  long DN;
#endif
}
  BOX;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ��'������� ���������������
// (�������� ����������� �� ��������������� ������ �++ )
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef long int  HMAP;    // ������������� �������� ��������� �����
                           // (��������� �� TMapAccess)
typedef long int  HSITE;   // ������������� �������� ����������������
                           // ����� (��������� �� ������� �������)
                           // ���� ����� HMAP (��� 0) - �������� �
                           // ������ ��������� (������� ������)
typedef long int  HOBJ;    // ������������� ��'���� �����
                           // (��������� �� TObjectInfo)
typedef long int  HSELECT; // ������������� ��������� ������
                           // (��������� �� TMapSelect)
typedef long int  HRSC;    // ������������� �������������� �����
                           // (��������� �� TMapRsc)
typedef long int  HMTR3D;  // ������������� ��������� ������
                           // ���������� ������������ ���������
                           // (��������� �� TMtr3D)
typedef long int  HCROSS;  // (��������� �� TObjectCut)
typedef long int  HPOINT;  // (��������� �� ��������� CROSSPOINT)
typedef long int  HDRAW;   // (��������� �� ��������� TDrawEdit)
typedef long int  HPRINTER;// (��������� �� TPrinter)
typedef long int  HVECT;   // (��������� �� TVectorImageEdit)       // 29/07/03

// ��������� PANTASK/PANACTION
typedef long int HPANACTION;   // ��������� �� TPanAction
typedef long int HMAPACTION;   // ��������� �� TUserAction

typedef long int HPANTASK;     // ��������� �� TPanTask
typedef long int HMAPTASK;     // ��������� �� TUserTask

typedef long int HMAPDOC;      // ��������� �� TMapWindow

typedef long int HOBJSET;      // ��������� �� TObjectSet

typedef long int HIMAGE;       // ��������� �� TCopyImage           // 14/12/05

typedef long int HFORMULA;     // ��������� �� TStrFormula          // 17/01/07

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++  ��������� ������� ������� ��'����  +++++++++
//++++++++++++++  � ������� ��������� ����  +++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define PF_TESTTEXT    1    // ���� ������� ������� � �����
#define PF_SKIPNUMBER  2    // ���� �������� ������ � #          // 20/02/07
#define PF_UNICODETEXT 4    // ���� ������ � UNICODE             // 02/06/07

typedef struct _DLLCLASS POLYDATA                       
{
  POLYDATA() { memset(this, 0, sizeof(*this)); }

  DRAWPOINT * Points;  // ����� ������� �������� ���� POINT
                       // � ������������ �����
  long * PolyCounts;   // ����� ������� ���������� �����
  long        Count;   // ����� ������� (���������������, �������)
  char **      Text;   // ��������� �� ������ ������� �������
                       // �������� (���� ������ �����
                       // � �������������� ������� �������)
  long    AlignCode;   // ��� ������������ ��� ����������� ������
  char *   Semantic;   // ��������� �� ��������� ������� (SEMANTIC *)
                       // ���� ��������� �� ����� � ����������� - ����� 0
  BOX        Border;   // ������������� ��������� ������� � ��������
                       // ������������ ������� ���������
  double  ShowScale;   // ������� ������� ����������� ����������� �����
}
  POLYDATA;

typedef struct _DLLCLASS POLYDATAEX                     // 30/05/05
{
  POLYDATAEX() { memset(this, 0, sizeof(*this)); }

  DRAWPOINT * Points;  // ����� ������� �������� ���� POINT
                       // � ������������ �����
  long * PolyCounts;   // ����� ������� ���������� �����
  long        Count;   // ����� ������� (���������������, �������)
  char **      Text;   // ��������� �� ������ ������� �������
                       // �������� (���� ������ �����
                       // � �������������� ������� �������)
  short   AlignCode;   // ��� ������������ ��� ����������� ������
  short       Flags;   // ����� ��������� ������� - ����� 0            // 05/06/07
  char *   Semantic;   // ��������� �� ��������� ������� (SEMANTIC *)
                       // ���� ��������� �� ����� � ����������� - ����� 0
  BOX        Border;   // ������������� ��������� ������� � ��������
                       // ������������ ������� ���������
  double  ShowScale;   // ������� ������� ����������� ����������� �����
  HRSC       MapRsc;   // ������������� �����, ���������� ������������ ������
  float      Height;   // ������ ������ ����� ������� (���� 3D-����������) ��� 0  // 04/07/06
  float      DX;       // ���������� �� ������ ����� �� ������ �� �����           // 29/08/07
  float      DY;       // � �������� ����� - ��� �������������� ��������� ��������
}
  POLYDATAEX;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ������������ �������� ������������� �������
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#if defined(COMPACTGIS) || defined(MINIDATA)
#define GD_POINTCOUNT  32000L  // ���������� ��������� ���������� �����
                               // ������� �������
#define GD_POLYCOUNT   16000L  // ���������� ��������� ����������
                               // ����������� �������
#define GD_TEXTCOUNT   16000L  // ���������� ��������� ����������
                               // ������� � ������� �������

#define MAXDATALENGTH (1024*1024L) // ������������ ����� �������

#else

#define GD_POINTCOUNT 128000L  // ���������� ��������� ���������� �����
                               // ������� �������
#define GD_POLYCOUNT   64000L  // ���������� ��������� ����������
                               // ����������� �������
#define GD_TEXTCOUNT   32000L  // ���������� ��������� ����������
                               // ������� � ������� �������

#define MAXDATALENGTH (16*1024*1024L) // ������������ ����� �������

#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++ ��������� �������� ������������� ������� ��������     +++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef struct TEXTDATA      // ����� ������� � �������
{                            // ����� ����� = Length + 2
  unsigned char Length;      // ����� ��������
           char Text[256];   // ����� ���������� �����
  unsigned char Zero;        // ���������� ����
}
  TEXTDATA;


// ���� �������� ��������� ����� �������
typedef struct
{
  unsigned short int X;
  unsigned short int Y;
}
  XYSHORT;

typedef struct
{
  unsigned short int X;
  unsigned short int Y;
           float     H;
}
  XYHSHORT;

typedef struct
{
  LONG X;
  LONG Y;
}
  XYLONG;

typedef struct
{
  LONG X;
  LONG Y;
  float    H;
}
  XYHLONG;

typedef struct
{
  float X;
  float Y;
}
  XYFLOAT;

typedef struct
{
  float X;
  float Y;
  float H;
}
  XYHFLOAT;

typedef struct
{
  double X;
  double Y;
}
  XYDOUBLE;

typedef struct
{
  double X;
  double Y;
  double H;
}
  XYHDOUBLE;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++ ��������� ���������� MAPAPI +++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

enum KIND                 // ���� �������� �������
{
  IDSHORT2  = 0x7FFF7FFF, // ������������ �������������
  IDLONG2   = 0x7FFE7FFE, // ��������������� �������������
  IDFLOAT2  = 0x7FFD7FFD, // � ��������� �������
  IDDOUBLE2 = 0x7FFC7FFC, // � ��������� ������� ������� ���������
  IDSHORT3  = 0x7FFB7FFB, // ������������ ������������� ����������
  IDLONG3   = 0x7FFA7FFA, // ��������������� ������������� ����������
  IDFLOAT3  = 0x7FF97FF9, // � ��������� ������� ����������
  IDDOUBLE3 = 0x7FF87FF8, // � ��������� ������� ������� ��������� ����������
  IDBAD     = 0x7FF87FF7  // ����������� ���
};

enum                          // �������������� ������ (Intel)
{
    FILE_SXF  = 0x00465853,   // �������� SXF ����
    FILE_TXT  = 0x4658532E,   // ��������� SXF ���� (.SXF)
    FILE_DIR  = 0x524944,     // ��������� DIR ����
    FILE_PCX  = 0x10,         // ���� PCX (������������ �� �����)
    FILE_BMP  = 0x4D42,       // ���� BMP
    FILE_TIFF = 0x4949,       // ���� TIFF
    FILE_JPEG = 0xD8FF,       // ���� JPEG
    FILE_MAP  = 0x00505350,   // ������� ������ �����
    FILE_RST  = 0x00545352,   // ���� RST
    FILE_RSW  = 0x00575352,   // ���� RSW
    FILE_MTR  = 0x0052544D,   // ���� MTR
    FILE_MTW  = 0x0057544D,   // ���� MTW
    FILE_MTL  = 0x004C544D,   // ���� MTL
    FILE_SIT  = 0x5449532E,   // ��������� SXF(.SIT) ����
    FILE_DXF  = 0x00465844,   // ���� DXF
    FILE_MIF  = 0x0046494D,   // ���� MAPINFO
    FILE_S57  = 0x00003000,   // ���� S57(�������)
    FILE_DGN  = 0x004E4744,   // ���� Macrostation(DGN)   // 23/03/04 Sh.
    FILE_MPT  = 0x0054504D,   // ���� MPT(������)
    FILE_RSC  = 0x00435352,   // ���� RSC
    FILE_MTQ  = 0x0051544D,   // ���� MTQ
    FILE_PLN  = 0x004E4C50,   // ���� PLN (Talka)    // 15/12/02
    FILE_SHP  = 0x00504853,   // ���� SHP (ArcView)  // 23/07/03
    FILE_PLS  = 0x00534C50,   // ���� PLS (������ �������)          // 05/07/04
    FILE_TEXT = 0x00545854,   // ���� TXT(������������� �������)    // 23/11/04
    FILE_GPS  = 0x47504724,   // ���� GPS/NMEA ($GPG)               // 07/12/04
    FILE_GRD  = 0x00445247,   // ���� GRD (������� ������� FOTOMOD) // 10/12/04
    FILE_DBF  = 0x00464244,   // ���� DBF (���� ������)             // 16/12/04 Sh.
    FILE_TIN  = 0x004E4954,   // ���� TIN                           // 31/03/05


                              // �������������� ������ (Sparc, Mips)

    FILE_MAP_TURN = 0x50535000, // ������� ������ �����
    FILE_MTW_TURN = 0x4D545700, // ���� MTW
    FILE_SXF_TURN = 0x53584600, // �������� SXF ����    //03/11/03
    FILE_DIR_TURN = 0x44495200, // ��������� DIR ����   //05/12/03
    FILE_RSW_TURN = 0x52535700, // ���� RSW  // 20/01/04
    FILE_RSC_TURN = 0x52534300, // ���� RSC
};

typedef struct FRAME MAPFRAME;

typedef struct DFRAME MAPDFRAME;

typedef struct MAPADJACENTSECTION  // �������� �������� �������
{
  long int number;                 // ����� �������
  long int first;                  // ������ ����� �������
  long int last;                   // ��������� ����� �������
}
  MAPADJACENTSECTION;

typedef struct MAPADJACENTLISTEX
{
  char      ListName[32];           // ��� �����
  long int  List;                   // ����� ����� � ������
  long int  Key;                    // ����� �������
  long int  Object;                 // ���������������� ����� ������� �� �����
  long int  Excode;                 // ����������������� ��� �������
  long int  First;                  // ������ ����� �������
  long int  Last;                   // ��������� ����� �������
}
  MAPADJACENTLISTEX;

typedef enum how       // ���� ������� ������ �� ���������
{
    CMBAD      = 0,    // ������ � ������
    CMPASS     = 0,    // ���������� ���� ���������  //11/12/03
      LESS     = 1,    // ������
    CMLESS     = 1,    // ������
    CMLESSEQ   = 3,    // ������ ��� �����
      EQUAL    = 2,    // �����
    CMEQUAL    = 2,    // �����
    CMNOTEQ    = 5,    // �� �����
      MORE     = 4,    // ������
    CMMORE     = 4,    // ������
    CMMOREEQ   = 6,    // ������ ��� �����
    CMANY      = 7,    // ����� ��������

    // ���� ���������� �������
    CMOR       = 16,   // "���" - ���� �� ���� �����������
    CMAND      = 32,   // "�"   - ��� ������ �����������
}
    HOW;

// ������, ������������ ������� ������ ��������
// ���� ������� WO_INMAP - ����� ����� ������������
// �� HSELECT !

enum SEEKTYPE        // ������� ������ ��'�����
{
   WO_FIRST  = 0,    // ������ � �������
   WO_LAST   = 2,    // ��������� � �������
   WO_NEXT   = 4,    // ��������� �� ��������� �����
   WO_BACK   = 8,    // ���������� �� ����� ����������
   WO_CANCEL = 16,   // ������� ��������� �������
   WO_INMAP  = 32,   // ������ �� ����� ����� (��������������� HSELECT)
   WO_VISUAL = 64,   // ����� ������ ����� ������� ��������
};

enum SELECTTYPEFLAG  // ������ ��������� ��������
{
   STF_CONTOUR = 0,  // ��������� ��������
   STF_OBJECT  = 1,  // ��������� ����� ����������� �������
};

enum SELECTLISTCODE           // ������� ������������ ������ ������� ������
{
   SELECTLIST_EXCLUSIVE = 0,  // ����������� ������� ������������ � ������
   SELECTLIST_UNION     = 1,  // ������� ��������� ������������ � ����������
   SELECTLIST_CROSS     = 2,  // ������� ��������� ���������� � ����������
};

enum SELECTMEASURE            // ��� ��������� ��"����� ��� ������  25/04/02
{
   MEASURE_LENGTH      = 1,   // ����� (�)
   MEASURE_SQUARE      = 2,   // ������� (��.�)
   MEASURE_PERIMETER   = 3,   // �������� (�)
   MEASURE_HEIGHT      = 10,  // ������ (�)
};

enum PPLACE           // ����������� ������� ���������
{
   PP_MAP     = 1,    // ���������� ����� � ������� ����� � ���������
   PP_PICTURE = 2,    // ���������� ����� � ������� ����������� � ��������
   PP_PLANE   = 3,    // ���������� ����� � ������� ������������� �������
                      // �� ��������� � ������
   PP_GEO     = 4,    // ���������� ����� � ������������� �����������
                      // � ��������
};

enum VTYPE               // ��� ����������� �����     // 13/09/00
{
   // �������� �����
   VT_SCREEN          = 1, // �������� (����� DIB)
   VT_SCREENCONTOUR   = 2, // �������� ���������

   // ���������� ��������� �����
   VT_PRINT           = 3, // ���������� ��������� (����� WIN API)
   VT_PRINTGLASS      = 4, // ���������� ��� ������� ���������
   VT_PRINTCONTOUR    = 5, // ���������� ���������, ��� �������� ������

   // ���������� �������������� �����
   VT_PRINTRST        = 6, // ���������� �������������� (����� WIN API)
   VT_PRINTGLASSRST   = 7, // ���������� ��� ������� ���������
   VT_PRINTCONTOURRST = 8, // ���������� ���������, ��� �������� ������

   // ���������� �������������� (�����������) �����        // 13/02/03
   VT_PRINTRSTSQUARE  = 9, // ���������� (������� ���������, ������� � �����,
                           //             ������, �������)
   VT_PRINTRSTLINE    =10, // ���������� (�����, ��������, ���������,
                           //             ������� � �����, ����������������)
   VT_PRINTRSTTEXT    =11, // ���������� (�������, �������)

   // ���������� ��������� (�����������) �����. ������������ ��� ��������
   // ������� (POSTSCRIPT, WMF, EMF)                       // 16/12/04
   VT_PRINTEX         =15, // ���������� ��������� (����� WIN API)
};

enum OUTPUTAREA            // ������ ������ ������� ������
{
  AREA_ALL            = 0, // �������� : ������� ������ - ���� �����
                           // �������� : ������� ������ �� ���������

  AREA_FRAME          = 1, // �������� : ������� ������ - �� RectMetr
                           // �������� : ������� ������ -> � RectMetr

  AREA_SELECT_FRAME   = 2, // �������� : ������� ������ - �� RectMetr
                           // �������� : ��� ������ �������������� ���������

  AREA_CHANGE_FRAME   = 3, // �������� : ������� ������ - �� RectMetr
                           // �������� : ��� ��������� ���������

  AREA_MOVE_FRAME     = 4, // �������� : ������� ������ - �� RectMetr
                           // �������� : ��� ����������� ���������

  AREA_SELECT_OBJECT  = 5, // �������� : ������� ������ - �� RectMetr
                           // �������� : ��� ������ ������� ������ �� �������

  AREA_SELECT_CONTOUR = 6, // �������� : ������� ������ - �� RectMetr
                           // �������� :  ��� ������ ������� ������ �� �������

  AREA_SELECT_TURN_FRAME = 10, // ���� ������ ����������� ���������
};

enum CHARCODE         // �������� ��������� �������
{
  CC_ASCIIZ  = 0  ,   // C����� �������� (ASCIIZ), ������������ �����
  CC_KOI8    = 125,   // C����� (KOI8), ������������ �����
  CC_ANSI    = 126,   // C����� (ANSI, WINDOWS), ������������ �����
  CC_UNICODE = 127,   // C����� �������� (UNICODE), ������������ �����
};

enum SPLINETYPE           // ���� ��������
{
  SPLINETYPE_NONE   = 0,  // ������� �����
  SPLINETYPE_SMOOTH = 2,  // ������������ ������ (������� ����)
  SPLINETYPE_POINTS = 4,  // ��������� ������ (�������� ����� �����)
};

enum POINTPOSITION        // ���������� ����� ������������ �������
{
  PS_FIRST   = 1,         // ��������� � ������ ������ �������
  PS_SECOND  = 2,         // ��������� �� ������ ������ �������
  PS_BEHIND  = 3,         // ����� ������ ������ ����� �������
  PS_BEYOND  = 4,         // ����� ������� ������ ����� �������
  PS_BETWEEN = 5,         // ����� �� ������� (����� �������)
  PS_LEFT    = 6,         // �����
  PS_RIGHT   = 7          // ������
};


typedef struct GEODEGREE   // ���������� ����� � ��������
{
  long int Degree;         // �������
  long int Minute;         // ������
  float    Second;         // �������
}
  GEODEGREE;

typedef struct SIGNDEGREE  // ���������� ����� � ��������
{
  long int Degree;         // �������
  long int Minute;         // ������
  float    Second;         // �������
  long int Sign;           // ���� ����� (+1 ��� -1)
}
  SIGNDEGREE;



typedef struct MTRDESCRIBE   // �������� �������� �������
{
  char   Name[256];      // ��� �����
  double MinValue;       // ����������� �������� �������� � �������
  double MaxValue;       // ������������ �������� �������� � �������
  double ElementInPlane; // ������ �������� � ������ �� ���������
  DFRAME FrameMeters;    // �������� ������� (�����)
  long int ReliefType;   // ��� ������� (0 - ���������� ������,
                         //  1 - ���������� + �������������)
  long   UserType;       // ��� ���������������� ������
  long   View;           // ������� ��������������
}
  MTRDESCRIBE;

typedef struct MTRCOLORDESCEX  // �������� ��������� �����
                               // �������
{
  double MinHeight;            // ����������� ������ ��������
  double MaxHeight;            // ������������ ������ ��������
  COLORREF Color;              // ����,��������������� ��������� �����
}
  MTRCOLORDESCEX;

typedef struct MTR3DVIEW     // ��������� 3D-����������� ������� �����
{
  double AreaCenterX;        // ����� ������������ ������� X,Y
  double AreaCenterY;        //   (� ������ �� ���������)
  double ViewPointX;         // ����� ���������� X,Y,H
  double ViewPointY;         //   (� ������ �� ���������)
  double ViewPointH;         //
  unsigned long ShowScale;   // ����������� ��������
  unsigned char Style;       // C���� (0 - �����, 1 - �������)
  unsigned char ShowGrid;    // ������� ����� (0 - ���, 1 - ����)
  unsigned char GridStep;    // ��� ����� � �������� (2 - 255)
  unsigned char ModelHeight; // ������ ������ � �������� (2 - 127)
}
  MTR3DVIEW;

enum CUTSHAPE                // ����� �������
{
  CS_NONE          =   0,    // �����������
  CS_VERTICALANGLE =   1,    // ������������ ������� ������
                             //   � �������� � ����� CutX,CutY
  CS_VOLUMETRICAL  =  16,    // �������� �����
                             //   � �������� � ����� CutX,CutY,CutZ
  CS_HORIZONTAL    = 128,    // �������������� ���� �� ������ CutH
};

enum SCALETYPE               // ��� �����
{
  ST_NONE          =   0,    // �����������
  ST_ABSOLUTE      =   1,    // ����������
  ST_FROMRELIEF    =   2,    // ������������� �� �������
  ST_WITHOUTRELIEF =   3,    // ������������� ��� ����� �������
};

#define MTL3D_MAXMODEL 0x01FF  // ������������ ������ ������ ������� �����
                               // (�������� ������ ��������� ������)

typedef struct MTR3DVIEWEX   // ��������� 3D-����������� ������ (MTW � MTL)
{
  double AreaCenterX;        // ����� ������������ ������� X,Y
  double AreaCenterY;        //   (� ������ �� ���������)
  double CutX;               // ���������� ������� �������/������ X,Y,Z
  double CutY;               //   (� ������ �� ���������)      - ��� MTL
  double CutZ;
  double CutH;               // ������ ��������������� ����� (� ������)

    long ShowScale;          // ����������� �������� ����������� ���������
    long ModelHeight;        // ������ ������ � �������� (2 - MTL3D_MAXMODEL)
    long GridStep;           // ��� ����� � �������� (2 - 100)
    long CutShape;           // ����� ������� (��. CUTSHAPE)   - ��� MTL

   short ViewAngle;          // ���� ����������/������� (� ��������)
   short RotationAngle;      // ���� �������� ������������ ������ AreaCenter
                             //   (� ��������)
    char Style;              // C���� (0 - �����, 1 - �������)
    char ShowGrid;           // ������� ����� (0 - ���, 1 - ����)
    char Shadow;             // ������� ���� (0 - ���, 1 - ����)
    char ScaleType;          // ��� ����� (��. SCALETYPE)      - ��� MTL

    char CoverMatrix;        // ������� ������� �����   (0 - ���, 1 - ����)
    char CoverMap;           // ������� �����           (0 - ���, 1 - ����)
    char CoverRaster;        // ������� ������          (0 - ���, 1 - ����)
    char AccordScale;        // ������������ ���������  (0 - ���, 1 - ����)
    char CoverMtq;           // ������� ������� ��������(0 - ���, 1 - ����)  // 06/10/04
    char IsUpdate ;          // ����������� ����������� (0 - ���, 1 - ��)    // 21/10/05

    char Reserve[26];

  double CursorX;            // ���������� ��������� X,Y
  double CursorY;            //   (� ������ �� ���������)

    long Width;              // ������ �����������
    long Height;             // ������ �����������

    char Name[256];          // ��� ����� ������������ �������
                             //   (0 - ��� ������� �����)    - ��� MTL
}
  MTR3DVIEWEX;

                             // ��������� 3D-����������� ������ ����� (MTL)
typedef struct MTR3DVIEWEX MTL3DVIEW;                   // 16/10/03


typedef struct METAFILEBUILDPARM  // ��������� �������� ���������
{
  long CenterX;     // ���������� ������ ��������� �������
  long CenterY;     // (� ������ �� ���������)
  long Width;       // ������ ��������� (� �����������)
  long Height;      // ������ ��������� (� �����������)
  long Scale;       // ������� �����������
  long VisualType;  // ��� ������������
   // �������� �����
   //   VT_SCREEN          = 1, // �������� (����� DIB)
   //   VT_SCREENCONTOUR   = 2, // �������� ���������

   // ���������� ��������� �����
   //   VT_PRINT           = 3, // ���������� ��������� (����� WIN API)
   //   VT_PRINTGLASS      = 4, // ���������� ��� ������� ���������
   //   VT_PRINTCONTOUR    = 5, // ���������� ���������, ��� �������� ������

   // ���������� �������������� �����
   //   VT_PRINTRST        = 6, // ���������� �������������� (����� WIN API)
   //   VT_PRINTGLASSRST   = 7, // ���������� ��� ������� ���������
   //   VT_PRINTCONTOURRST = 8, // ���������� ���������, ��� �������� ������
}
  METAFILEBUILDPARM;


typedef struct METAFILEBUILDPARMEX  // ��������� �������� EMF-�����
{
  DFRAME Frame;     // �������� (�����)
  long Scale;       // ������� �����������
  char VisualType;  // ��� ������������
                    //  1 - �������� (BITMAP)
                    //  2 - ����������� (BITMAP)
                    //  3 - ����������
                    //  4 - ���������� ����������
                    //  5 - ��������� ����������
  char Border;      // ���� ��������� �����
  char Intensity;   // ������������� ������� % (0-100)   // 15/02/00
  char Black;       // ���� �����-������ �����������(1 - ����, 0 - ���)

  char DontClip;    // �� �������� ��������� �������� �� ����� (!= 0)
                    // (��������, Corel9 �� �������� ::SelectClipRgn() )
  char Reserve[7];  // ������ (������ ���� �������)
}
  METAFILEBUILDPARMEX;


typedef struct XIMAGEDESC   // ��������� ������� ������� XImage
{                           // (��� ���������� � XWindow)    // 25/09/00
  char *    Point;          // ����� ������ ������� ��������
  long int  Width;          // ������ ������ � ��������
  long int  Height;         // ����� �����
  long int  Depth;          // ������ �������� � ����� (8,15,16,24,32)
  long int  CellSize;       // ������ ��������(�������) � ������
  long int  RowSize;        // ������ ������ � ������
}
  XIMAGEDESC;


enum GRIDTYPE                // ��� �����
{
  GRT_NONE  =   0,           // �����������
  GRT_LINE  =   1,           // ����� �����
  GRT_NODE  =   2,           // ����� �����
  GRT_CROSS =   3,           // ����� �������
};

typedef struct GRIDPARM     // ��������� ���������� ������������� �����
{
  double    Step;           // ��� ����� � ������ �� ���������
  long int  Type;           // ��� �������� (�����, �����, ������)
  struct
  {
   long int Color;
   long int Thick;
  }
            Image;          // ���� � ������� ����� (RGB, ���)
  long int  Size;           // ������ �������� ���� "�����" � ��� (1:250)
  long int  Shadow;         // ������� ��������������� �����������
  long int  Under;          // ������� ����������� ��� ������ 
}
  GRIDPARM;

// ��������� ���������� ���� ���������
typedef struct TBUILDZONEVISIBILITY                    // 18/05/05
{
  DOUBLEPOINT PointCenter;      // �������� ����� 
  double      RadiusMeter;      // ���������� (� ������ �� ���������)
  double      Azimuth;          // ����������� (� ��������)
  double      Angle;            // ���� ������ (� ��������)
  double      DeltaHight;       // ������ ���������� (� ������)
  double      DeltaObservation; // ���������� ����������� ����� (� ������)
  long int    VisionRst;        // ��������� ��� �����������
                                // 0-�� ���� �����, 1-���� �� � �����   
  long int    StyleRst;         // ������� ��������� ������
                                // 0-����������, 1-��������������
                                // 2-�����������
  long int    ColorRst;         // ���� ������
  long int    Inversion;        // �������� ���������

}
  TBUILDZONEVISIBILITY;


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++ ��������� ��� �������� ������, ���� � ++++++++++++++++++
//++++++++ ���������������� ����                 ++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef struct APPENDPLANELIST
{
long Length;              // ����� ������ ��������� APPENDLIST

char Nomenclature[32];    // ������������ �����
char ListName[32];        // �������� �������� �����
char FileName[256];       // ��� ����� �� �������� � ������ �����
                          // ������ ���� � ������ ������ � ������������
                          // HDR,DAT,SEM ...

long Reserv;              // ������ ��� ������������, ������ ���� 0
                          // 17/10/01

// ������������� ���������� ����� � ������
// (��� ���������������� ����� (SITE) ������ ���� 0)

double XSouthWest   ;  // X �-�
double YSouthWest   ;  // Y �-�
double XNorthWest   ;  // X �-�
double YNorthWest   ;  // Y �-�
double XNorthEast   ;  // X �-�
double YNorthEast   ;  // Y �-�
double XSouthEast   ;  // X �-�
double YSouthEast   ;  // Y �-�
}
  APPENDPLANELIST;


typedef struct CREATEPLANE
{
long Length;              // ����� ������ ��������� CREATEPLANE

char MapName[32];         // ��� ������
long Scale;               // ����������� �������� �����

APPENDPLANELIST List;     // �������� ����� �����
}
  CREATEPLANE;


typedef struct CREATESITE
{
 long     Length;             // ����� ������ ��������� CREATESITE
 char     MapName[32];        // ��� ������
 long int MapType;            // ���������� ��� �����
 long int MaterialProjection; // �������� ���. ���������
 long     Scale;              // ����������� �������� �����

                              // � ��������
 double FirstMainParallel;    // ������ ������� ���������
 double SecondMainParallel;   // ������ ������� ���������
 double AxisMeridian;         // ������ ��������
 double MainPointParallel;    // ��������� ������� �����
}
  CREATESITE;

typedef struct CREATESITEEX   // 11/05/07
{
 long     Length;             // ����� ������ ��������� CREATESITE
 char     MapName[256];       // ��� ������ � ��������� ANSI (UNICODE - ��� ������� "Un")
 long int MapType;            // ���������� ��� �����
 long int MaterialProjection; // �������� ���. ���������
 long int EllipsoideKind;     // ��� ���������� (1 - �����������, 9 - WGS84,...)
 long     Scale;              // ����������� �������� �����
 long     Reserve;            // ������ (������ ���� 0)

                              // � ��������
 double FirstMainParallel;    // ������ ������� ���������
 double SecondMainParallel;   // ������ ������� ���������
 double AxisMeridian;         // ������ ��������
 double MainPointParallel;    // ��������� ������� �����
 double PoleLatitude;         // ������ ������ ��������
 double PoleLongitude;        // ������� ������ ��������
}
  CREATESITEEX;

typedef struct CREATESITEUN   // 11/05/07
{
 long     Length;             // ����� ������ ��������� CREATESITE
 WCHAR    MapName[128];       // ��� ������ � ��������� UNICODE (��� ������� "Un")
 long int MapType;            // ���������� ��� �����
 long int MaterialProjection; // �������� ���. ���������
 long int EllipsoideKind;     // ��� ���������� (1 - �����������, 9 - WGS84,...)
 long     Scale;              // ����������� �������� �����
 long     Reserve;            // ������ (������ ���� 0)

                              // � ��������
 double FirstMainParallel;    // ������ ������� ���������
 double SecondMainParallel;   // ������ ������� ���������
 double AxisMeridian;         // ������ ��������
 double MainPointParallel;    // ��������� ������� �����
 double PoleLatitude;         // ������ ������ ��������
 double PoleLongitude;        // ������� ������ ��������
}
  CREATESITEUN;


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++ ��������� ���������� 4 ������ �� ������������ ++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



typedef union
{
  struct
  {
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;
    unsigned char b4;
  }
    Byte;              // ������������� � ���� 8-������� �����

  struct
  {
    unsigned short w1;
    unsigned short w2;
  }
    Word;              // ������������� � ���� 16-������� �����

  ULONG Long;  // ������������� � ���� 32-�������� ����

#ifdef __cplusplus
  long Value() { return (long) Long; }

  // ��������� �������� (long)
  long GetLong(long & value)
  {
    return (long)(Long = (ULONG)value);
  }

  // ��������� �������� (long)
  long GetLong(unsigned long & value)
  {
    return (long)(Long = (ULONG)value);
  }

  // ��������� �������� (long) �� ������ address (4 �����)
  long GetLong(const char* address)
  {
#ifdef RISCCPU
    Byte.b1 = address[0];
    Byte.b2 = address[1];
    Byte.b3 = address[2];
    Byte.b4 = address[3];
#else
    Long = *((ULONG *)address);
#endif
    return (long)Long;
  }

  // ��������� �������� (long) �� ������ address (4 �����)
  // � �������� ������������������ ����
  long GetTurnLong(long & value)
  {
    return GetTurnLong((char *)&value);
  }

  // ��������� �������� (long) �� ������ address (4 �����)
  // � �������� ������������������ ����
  long GetTurnLong(unsigned long & value)
  {
    return GetTurnLong((char *)&value);
  }

  // ��������� �������� (long) �� ������ address (4 �����)
  // � �������� ������������������ ����
  long GetTurnLong(char* address)
  {
    Byte.b4 = address[0];
    Byte.b3 = address[1];
    Byte.b2 = address[2];
    Byte.b1 = address[3];
    return (long)Long;
  }

  // ���������� �������� (long) �� ������ address (4 �����)
  long PutLong(long & value)
  {
    return (value = (long)Long);
  }

  // ���������� �������� (long) �� ������ address (4 �����)
  long PutLong(unsigned long & value)
  {
    return (long)(value = (unsigned long)Long);
  }

  // ���������� �������� (long) �� ������ address (4 �����)
  long PutLong(char* address)
  {
#ifdef RISCCPU
    address[0] = Byte.b1;
    address[1] = Byte.b2;
    address[2] = Byte.b3;
    address[3] = Byte.b4;
#else
    *((ULONG *)address) = Long;
#endif
    return (long)Long;
  }

  // ��������� �������� (short int)
  int GetShort(short int & value)
  {
    return GetShort((char *)&value);
  }

  // ��������� �������� (short int)
  int GetShort(unsigned short int & value)
  {
    return GetShort((char *)&value);
  }

  // ��������� �������� (int) �� ������ address (2 �����)
  int GetShort(char* address)
  {
    Long = 0;
#ifdef RISCCPU
#ifdef NUMBERTURN              // 04/03/00
    Byte.b3 = address[0];
    Byte.b4 = address[1];
#else
    Byte.b1 = address[0];
    Byte.b2 = address[1];
#endif
#else
    Word.w1 = *((unsigned short *)address);
#endif
    return (int)Long;
  }

  // ��������� �������� (int) �� ������ address (2 �����)
  // � �������� ������������������ ����
  int GetTurnShort(short int & value)
  {
    return GetTurnShort((char *)&value);
  }

  // ��������� �������� (int) �� ������ address (2 �����)
  // � �������� ������������������ ����
  int GetTurnShort(unsigned short int & value)
  {
    return GetTurnShort((char *)&value);
  }

  // ��������� �������� (int) �� ������ address (2 �����)
  // � �������� ������������������ ����
  int GetTurnShort(char* address)
  {
    Long = 0;
#ifdef NUMBERTURN
    Byte.b4 = address[0];
    Byte.b3 = address[1];
#else
    Byte.b2 = address[0];
    Byte.b1 = address[1];
#endif
    return (int)Long;
  }

  // ���������� �������� (short int)
  int PutShort(short int & value)
  {
    return PutShort((char *)&value);
  }

  // ���������� �������� (short int)
  int PutShort(unsigned short int & value)
  {
    return PutShort((char *)&value);
  }

  // ���������� �������� (int) �� ������ address (2 �����)
  int PutShort(char* address)
  {
#ifdef RISCCPU
#ifdef NUMBERTURN              // 04/03/00
    address[0] = Byte.b3;
    address[1] = Byte.b4;
#else
    address[0] = Byte.b1;
    address[1] = Byte.b2;
#endif
#else
    *((unsigned short *)address) = Word.w1;
#endif
    return (int)Long;
  }
#endif  // __cplusplus
}
  REGISTER;

// ����������� ��� � (REGISTER , char*) :

#if defined(__BORLANDC__) // ��� Borland C++

#define LongToRegister(register, point) register.Long = ((long *)point)[0];

#else

#define LongToRegister(register, point) { register.Byte.b1 = ((char *)point)[0]; \
                                          register.Byte.b2 = ((char *)point)[1]; \
                                          register.Byte.b3 = ((char *)point)[2]; \
                                          register.Byte.b4 = ((char *)point)[3]; }
#endif

#define TurnLongToRegister(register, point) { register.Byte.b4 = ((char *)point)[0]; \
                                              register.Byte.b3 = ((char *)point)[1]; \
                                              register.Byte.b2 = ((char *)point)[2]; \
                                              register.Byte.b1 = ((char *)point)[3]; }

#define RegisterToLong(register, point) { ((char *)point)[0] = register.Byte.b1; \
                                          ((char *)point)[1] = register.Byte.b2; \
                                          ((char *)point)[2] = register.Byte.b3; \
                                          ((char *)point)[3] = register.Byte.b4; }

#define TurnRegisterToLong(register, point) { ((char *)point)[0] = register.Byte.b4; \
                                              ((char *)point)[1] = register.Byte.b3; \
                                              ((char *)point)[2] = register.Byte.b2; \
                                              ((char *)point)[3] = register.Byte.b1; }

#ifdef NUMBERTURN
#define ShortToRegister(register, point) {register.Long    = 0;        \
                                          register.Byte.b3 = ((char *)point)[0]; \
                                          register.Byte.b4 = ((char *)point)[1]; }

#define RegisterToShort(register, point) {((char *)point)[0] = register.Byte.b3; \
                                          ((char *)point)[1] = register.Byte.b4; }

#else
#define ShortToRegister(register, point) {register.Long    = 0;        \
                                          register.Byte.b1 = ((char *)point)[0]; \
                                          register.Byte.b2 = ((char *)point)[1]; }

#define RegisterToShort(register, point) {((char *)point)[0] = register.Byte.b1; \
                                          ((char *)point)[1] = register.Byte.b2; }
#endif

#ifdef NUMBERTURN
#define TurnShortToRegister(register, point) {register.Long    = 0;    \
                                          register.Byte.b4 = ((char *)point)[0]; \
                                          register.Byte.b3 = ((char *)point)[1]; }
#else
#define TurnShortToRegister(register, point) {register.Long    = 0;    \
                                          register.Byte.b2 = ((char *)point)[0]; \
                                          register.Byte.b1 = ((char *)point)[1]; }
#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++ ��������� ���������� 8 ������ �� ������������ ++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef union
{
  struct
  {
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;
    unsigned char b4;
    unsigned char b5;
    unsigned char b6;
    unsigned char b7;
    unsigned char b8;
  }
    Byte;              // ������������� � ���� 8-������� �����

  double Double;  //  ������������� � ���� 64-�������� ����

#ifdef __cplusplus
  double Value() { return Double; }

  // ��������� �������� (double) �� ������ address (8 ����)
  double GetDouble(double & value)
  {
    return GetDouble((char *)&value);
  }

  // ��������� �������� (double) �� ������ address (8 ����)
  double GetDouble(const char* address)
  {
#ifdef RISCCPU
    Byte.b1 = address[0];
    Byte.b2 = address[1];
    Byte.b3 = address[2];
    Byte.b4 = address[3];
    Byte.b5 = address[4];
    Byte.b6 = address[5];
    Byte.b7 = address[6];
    Byte.b8 = address[7];
#else
    Double = *((double *)address);
#endif
    return (double)Double;
  }

  // ��������� �������� (double) �� ������ address (8 ����)
  // � �������� ������������������ ����
  double GetTurnDouble(double & value)
  {
    return GetTurnDouble((char *)&value);
  }

  // ��������� �������� (double) �� ������ address (8 ����)
  // � �������� ������������������ ����
  double GetTurnDouble(const char* address)
  {
    Byte.b8 = address[0];
    Byte.b7 = address[1];
    Byte.b6 = address[2];
    Byte.b5 = address[3];
    Byte.b4 = address[4];
    Byte.b3 = address[5];
    Byte.b2 = address[6];
    Byte.b1 = address[7];
    return (double)Double;
  }

  // ���������� �������� (double) �� ������ address (8 ����)
  double PutDouble(double & value)
  {
    return PutDouble((char *)&value);
  }

  // ���������� �������� (double) �� ������ address (8 ����)
  double PutDouble(char* address)
  {
#ifdef RISCCPU
    address[0] = Byte.b1;
    address[1] = Byte.b2;
    address[2] = Byte.b3;
    address[3] = Byte.b4;
    address[4] = Byte.b5;
    address[5] = Byte.b6;
    address[6] = Byte.b7;
    address[7] = Byte.b8;
#else
    *((double *)address) = Double;
#endif
    return (double)Double;
  }
#endif  // __cplusplus
}
  DOUBLEREGISTER;

// ����������� ��� � (DOUBLEREGISTER , char*) :

#define DoubleToRegister(register, point) { register.Byte.b1 = ((char *)point)[0]; \
                                          register.Byte.b2 = ((char *)point)[1]; \
                                          register.Byte.b3 = ((char *)point)[2]; \
                                          register.Byte.b4 = ((char *)point)[3]; \
                                          register.Byte.b5 = ((char *)point)[4]; \
                                          register.Byte.b6 = ((char *)point)[5]; \
                                          register.Byte.b7 = ((char *)point)[6]; \
                                          register.Byte.b8 = ((char *)point)[7]; }

#define TurnDoubleToRegister(register, point) { register.Byte.b8 = ((char *)point)[0]; \
                                              register.Byte.b7 = ((char *)point)[1]; \
                                              register.Byte.b6 = ((char *)point)[2]; \
                                              register.Byte.b5 = ((char *)point)[3]; \
                                              register.Byte.b4 = ((char *)point)[4]; \
                                              register.Byte.b3 = ((char *)point)[5]; \
                                              register.Byte.b2 = ((char *)point)[6]; \
                                              register.Byte.b1 = ((char *)point)[7]; }

#define RegisterToDouble(register, point) { ((char *)point)[0] = register.Byte.b1; \
                                          ((char *)point)[1] = register.Byte.b2; \
                                          ((char *)point)[2] = register.Byte.b3; \
                                          ((char *)point)[3] = register.Byte.b4; \
                                          ((char *)point)[4] = register.Byte.b5; \
                                          ((char *)point)[5] = register.Byte.b6; \
                                          ((char *)point)[6] = register.Byte.b7; \
                                          ((char *)point)[7] = register.Byte.b8; }

// ��������� �������� (short int)

#if !defined(WINCE) && !defined(NUMBERTURN)    // 07/06/02
  #define GetWordValue(value) ((int)((unsigned short) value))
#else
 #ifdef __cplusplus
  inline int GetWordValue(long int value) // 25/04/01
   {
     REGISTER Register;
     return Register.GetShort((char *)&value);
   }
 #else
  #define GetWordValue(value) ((int)((unsigned short) value))
 #endif
#endif


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++   C�������� �������� ����������� �������   ++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef struct PALETTE256
{
  WORD         palVersion;
  WORD         palNumEntries;
  PALETTEENTRY palPalEntry[256];
}
  PALETTE256;

typedef ULONG CELL4;              // 28/07/06
typedef unsigned short CELL2;
typedef unsigned char  CELL1;

// ������ ������������ �������� DIB
#ifdef  WIN32API

#ifndef WINCE
  typedef CELL4  CELL;
  #define CELLSIZE 4
#else
  typedef CELL2  CELL;
  #define CELLSIZE 2
#endif

#else

#if defined(MINIDATA) || defined(TYNIDATA)
  typedef CELL1  CELL;
  #define CELLSIZE 1
#else
//#ifdef NUMBERTURN
  typedef CELL4  CELL;
  #define CELLSIZE 4
//#else
//  typedef CELL2  CELL;
//  #define CELLSIZE 2
//#endif  // NUMBERTURN
#endif

#endif // !WIN32API


// ----------------------------------------------------------------
// C�������� �������� � ������� ����������� ��������
// ��� ������� ���� � ���. (��. MAPGDI.H)
// ��� ������� � �������� - ������� ����� �����
// ���� ������ "���������" - TwoPoint = 1, ����� - 0;
// ��� "���������������" ������� - ������� 0;
// ----------------------------------------------------------------

typedef struct IMAGESIZE
{           // 11/10/02
   unsigned long Number;          // ����� ������� �����������
   unsigned long Base  ;          // ������ ���� �������
            long DeltaH;          // ���������� �� ������ ��������
            long DeltaV;          // ���� ��������� �� ����(�����
                                  // �������) �������
   unsigned long HorizontalSize;  // ������� �� �����������
   unsigned long VerticalSize  ;  // ������� �� ���������

   unsigned long Horizontal : 1;  // ���������� �������������
   unsigned long Vertical   : 1;  // ���������� �����������
   unsigned long TwoPoint   : 1;  // ������� �� 2 �����
   unsigned long AlignV     : 2;  // ������������ �� ���������
   unsigned long AlignH     : 2;  // ������������ �� �����������
   unsigned long Wide       : 2;  // ������ ������
   unsigned long Type       : 8;  // ��� ������ (0-4)
   unsigned long Italic     : 1;  // ������ ��������    // 13/06/06
   unsigned long Rezerv     :14;  // ������
}
  IMAGESIZE;

// ----------------------------------------------------------------
// C�������� ����������� ���������� ����� ����������� �������
// � ���� ������������ ��������������. ��� ������� ���� � ���
// �� ����������� ����� � ������� �������� ������������ ������
// ����� ������� �������. ����������� ���� ���������������� (X �����,
// Y ������).
// ----------------------------------------------------------------

typedef struct IMAGEFRAME
{
   DOUBLEPOINT LeftTop;          // ���������� ������ ����� � ���
   DOUBLEPOINT RightTop;         // ���������� ������ ����� � ���
   DOUBLEPOINT RightBottom;      // ���������� ������� ����� � ���
   DOUBLEPOINT LeftBottom;       // ���������� ��������� ����� � ���
}
  IMAGEFRAME;

// ----------------------------------------------------------------
// ������� ��������� ������
// ----------------------------------------------------------------
#ifdef WIN32API
typedef long int (WINAPI * BREAKCALL)(long int parm);
typedef long int (WINAPI * BEFOREPAINT)
                 (long int parm, HDC hdc, RECT * rect);
typedef long int (WINAPI * MASKCALL)(long int parm);     // 15/02/05
#else
typedef long int (*BREAKCALL)(long int parm);
typedef long int (*BEFOREPAINT)
                 (long int parm, HDC hdc, RECT * rect);
typedef long int (* MASKCALL)(long int parm);            // 15/02/05
#endif

#ifdef LINUXAPI        // 04/04/02
// ----------------------------------------------------------------
// ���������� ���������
// ----------------------------------------------------------------
typedef long int (* MSGHANDLER)
    (long int hwnd, long int code, long int p1, long int p2, long int typemsg);  // 04/04/02

// ------------------------------------------------------------------
//  ������� MessageBox ��� LINUX
// ------------------------------------------------------------------
typedef int (* MESSAGEBOX)(HWND hwnd, const TCHAR * message,
                           const TCHAR * title, int flag);
#endif

// ----------------------------------------------------------------
//  ���� ������ ��������� � ������� ����
// ----------------------------------------------------------------

enum MAPAPILANGUAGE
{
  ML_ENGLISH = 1,  // ����������
  ML_RUSSIAN = 2   // �������
};

// ----------------------------------------------------------------
//  �������������� ������ (WM_COMMAND)
// ----------------------------------------------------------------

#define WM_OBJECT       0x585    // ����� �������
#define WM_LIST         0x586    // ����� �����
#define WM_INFOLIST     0x584    // ���������� � �����
#define WM_ERRORCOORD   0x583    // ���������� � ������� ��������
#define WM_ERROR        0x587    // ���������� �� �������
#define WM_MAP          0x588    // ����� ������� �����

#define WM_PROGRESSBAR  0x590    // ��������� � ��������� ��������
#define WM_MAPEVENT     0x591    // ��������� � �������� �����

// ----------------------------------------------------------------
//  �������������� ��������� (MESSAGE)
// ----------------------------------------------------------------

#define WM_LEFTTOPPOINT 0x600    // C�������� ���� ����� �� ������
                                 // ������ ��������� �������� ������
                                 // ���� ���� ����� � �������� �����������
                                 // wparam : (POINT * point)         //28/11/02
                                 // lparam : 0
                                 // result : 0x600

#define WM_MOVEDOC      0x601    // C�������� ���� ����� �� ������
                                 // �������� �� �������������
                                 // ����������� ����������� ����� � ��������
                                 // �����, ���������� �������� ������ ���� ����
                                 // ����� � �������� �����������
                                 // wparam : (POINT * point)         //28/11/02
                                 // lparam : 0 ��� (POINT * marker)  //28/11/02
                                 // ���������� �������,������������ �� �����������
                                 // result : 0x601

#define WM_OPENDOC      0x602    // C�������� ���� ���������� ��� ����� �� ������
                                 // �������� �� �������������
                                 // ������� ����� �� ����� ����� (MAP,MTW,RSW,...)
                                 // wparam : (const char * name)
                                 // lparam : 0 ��� (DOUBLEPOINT * point),
                                 // ���������� � ������ �����, ������� �����
                                 // �������� � ������ ���� �����
                                 // result : 0x602

// --------------------------------------------------------------
//  ��������� ���������� DLL
//  ��� ������ DLL ����������� � ���������� ����������
//  ��� ������ ���������� ���� � ������ ��������� �� �����
// --------------------------------------------------------------

#ifdef __cplusplus
FARPROC LoadMapLibrary(const char * dllname,
                       HINSTANCE&   libinst,
                       const char * funcname,
                       int message = 1);
#else
FARPROC LoadMapLibrary(const char * dllname,
                       HINSTANCE    libinst,
                       const char * funcname,
                       int message );
#endif


// --------------------------------------------------------------
//  ��������� ��� ������ ���������� �����
// --------------------------------------------------------------

typedef struct TASKPARM        // ��������� ���������� ������
{
  long int    Language;        // ��� ����� �������� (1 - ENGLISH,
                               // 2 - RUSSIAN, ...)
  HINSTANCE   Resource;        // ������ �������� ����������
  const char* HelpName;        // ������ ��� ����� ".hlp"
  const char* IniName;         // ������ ��� ����� ".ini" ����������
  const char* PathShell;       // ������� ���������� (exe,dll,...)
  const char* ApplicationName; // ��� ����������
#ifdef WIN32API
  HWND        Handle;          // ������������� �������� ���� ����������
#else
  MSGHANDLER  Handle;          // ������������� ����������� ������ �������� ���� ����������
#endif
}
  TASKPARM;

typedef struct DROMPARM
{
  int Precision; // �������� ���������� (0 - 0.  1 - 0.00  2 - 0.0000  3 - 0.000000  4 - 0.00000000)
  int Value;     // ������� ��������� (0 - ��, 1 - �, 2 - ��, 3 - ��)
}
  DromParm;

typedef struct TASKPARMEX      // ��������� ���������� ������
{
  long int    Language;        // ��� ����� �������� (1 - ENGLISH,
                               // 2 - RUSSIAN, ...)
  HINSTANCE   Resource;        // ������ �������� ����������
  const char* HelpName;        // ������ ��� ����� ".hlp"
  const char* IniName;         // ������ ��� ����� ".ini" ����������
  const char* PathShell;       // ������� ���������� (exe,dll,...)
  const char* ApplicationName; // ��� ����������
#ifdef WIN32API
  HWND        Handle;          // ������������� �������� ���� ����������
#else
  MSGHANDLER  Handle;          // ������������� ����������� ������ �������� ���� ����������
#endif
  HWND        DocHandle;       // ������������� ���� ����� (���������)
  long int    StayOnTop;       // ������� ����������� ����� �������� StayOnTop  // 14/05/05
}
  TASKPARMEX;


// --------------------------------------------------------------
// ������ ��������� �� ������
// code - ��� ������ (��. MAPERR.RH)
// --------------------------------------------------------------
#ifdef __cplusplus
extern "C"
{
#endif
  void _MAPAPI ErrorMessage(int code,const char * filename);
#ifdef __cplusplus
}
#endif

enum MESSAGETYPE
{
  MT_INFO     = 0,    // �������������� ���������
  MT_ERROR    = 1,    // ��������� �� ������
  MT_WARNING  = 2,    // �������������� ���������
  MT_CONTINUE = 4,    // ����������� ����������� ���������
                      // (�� ��� �� ������)
};

// --------------------------------------------------------------
// �������� �������� ��� ������ � ����
// --------------------------------------------------------------

#define MENUEXTENDIDENT   0x7FFF7FFF

typedef struct MENUEXTEND         // �������� ������� ����
{
  long int Ident;                 // ����� ������ ������ 0x7FFF7FFF
  long int Count;                 // ����� ������� ����
  struct
  {
   long int Command;              // ������������� ������� (-1 ��� �����������)
   long int Check;                // ������� ��������� ������ �������� (0/1)
   char     Text[32];             // ����� ������ ����
  }
   Item[32];
}
  MENUEXTEND;

typedef struct COMMANDENABLER     // ������ ��������� ������ ���� ��� ������
{
  long int     Command;           // ������������� ������� (-1 ��� �����������)
  long int     Enable;            // ������� ����������
  long int     Check;             // ������� ����������� "�������" - 1, ������ - 0
  MENUEXTEND * Menu;              // ������ ����, ������� ����������� �� �������
  char         Text[256];         // ����� ����� ������ ����
}
  COMMANDENABLER;

typedef struct VIEWHELPEX         // ������ �� ����������� HELP (AW_VIEWHELPEX)
{
  const char * HelpName;          // ��� ����� HELP
  long int     Topic;             // ����� �������
}
  VIEWHELPEX;


typedef struct CONTROLMENU        // ��������/�������/����������/���������... ����� �������� ���� (AW_MENUCONTROL)
{                                 // WPARAM=MC_APEENDMENU,MC_DELETEMENU...,LPARAM=CONTROLMENU*  // 12/01/05
  char Name[32];                  // ��� ������ ���� (�������������)
  char Caption[64];               // �������� ������ ���� (������������ �� ������)      // 23/03/05
  char After[32];                 // ��� ������ ����, �� ������� ����������� ������ ����� ("MenuFile","MenuView"...)
}                                 // ���� ����� 0, �� � �����, ���� ������ #, �� �� ��� ���������� ����� � 1,
  CONTROLMENU;                    // ������� ����� �������� ������ �����

typedef struct CONTROLITEM        // ��������/�������... �������� �������� ���� (AW_MENUCONTROL)
{                                 // WPARAM=MC_APPENDMENUITEM..,LPARAM=CONTROLITEM*
  char Name[32];                  // ��� ������ ���� (�������������) ("MenuFile","MenuView"...,"MenuTask"...)
  char Caption[64];               // �������� ��������� ���� (������������ �� ������)    // 23/03/05
  long int Item;                  // �������� ������������� ������� (���������� ������ ��� ������ ������ ����)
  long int SubItem;               // �������� ������������� ������� (���������� ������ ��� ������ ��������� ����)
  long int After;                 // ������������� ������/��������� �� ������� ����������� ����� ����,
}                                 // 0 - � �����, -1 - � ������, -2 - ������ � �.�.
  CONTROLITEM; 





//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++  �������� �������� �������������� (RSC)                   +++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ����������� ��'���� (���)
enum OBJECT_LOCAL { LOCAL_LINE = 0,  LOCAL_SQUARE = 1, LOCAL_POINT = 2,
                    LOCAL_TITLE = 3, LOCAL_VECTOR = 4, LOCAL_MIXED = 5 };

// ����������� ���������� ��'����
enum OBJECT_DIRECT
{
   OD_UNDEFINED = 1,        // ����� ������� ��� �����������
   OD_RIGHT     = 2,        // ��'��� ����� �� �������
   OD_LEFT      = 4,        // ��'��� ����� �� �������
};

// ������ ��������� ��'����      //01/03/01

enum { ABR_APPEND   = 0,  // �������� ����� � ����� �������
                            // �� ���������, ���� ������ �������
       ABR_LAST     = 1,  // �������� ��������� �����
       ABR_FIRST    = 2,  // �������� ������ �����
       ABR_ADDLAST  = 3,  // �������� ����� � ����� �������
       ABR_ADDFIRST = 4   // �������� ������ �����
     };

#define  OTHERSCALERSC  10000L
#define  MAXSCALERSC  40000000L

// ��������� ��� �������� ��������������
typedef struct RSCCREATE
{
  char Name[32]; // �������� ��������������
  char Type[32]; // ��� ��������������
  char Code[8];  // ��� �������������� 
  LONG Scale;    // ����������� ��������
  LONG Language; // ���� (MAPAPILANGUAGE)
}
  RSCCREATE;

typedef struct RSCCREATEUN
{
  WCHAR Name[32]; // �������� ��������������
  WCHAR Type[32]; // ��� ��������������
  WCHAR Code[8];  // ��� ��������������
  LONG Scale;     // ����������� ��������
  LONG Language;  // ���� (MAPAPILANGUAGE)
}
  RSCCREATEUN;

// �������� ��'�����
typedef struct RSCOBJECT
{
   ULONG Length   ; // ������ ���������
   ULONG Code     ; // ����������������� ���
   ULONG Local    ; // �������� �����������  (OBJECT_LOCAL)
   ULONG Segment  ; // �0��� ���� ( �� ����� 255)
   ULONG Scale    ; // 1 - ��'��� ��������������
                            // 0 - ��'��� �� ��������������
   ULONG Direct   ; // ����������� ���������� ��'���� (OBJECT_DIRECT)
   ULONG Bot      ; // ������ ������� ��������� (����������� ��������)
   ULONG Top      ; // ������� ������� ��������� (����������� ��������)
   unsigned char Name[32] ; // �������� ( �� ����� 30)
}
   RSCOBJECT;

typedef struct RSCOBJECTEX                              // 02/04/03
{
   ULONG Length   ; // ������ ���������
   ULONG Code     ; // ����������������� ���
   ULONG Local    ; // �������� �����������  (OBJECT_LOCAL)
   ULONG Segment  ; // �0��� ���� ( �� ����� 255)
   ULONG Scale    ; // 1 - ��'��� ��������������
                            // 0 - ��'��� �� ��������������
   ULONG Direct   ; // ����������� ���������� ��'���� (OBJECT_DIRECT)
   ULONG Bot      ; // ������ ������� ��������� (����������� ��������)
   ULONG Top      ; // ������� ������� ��������� (����������� ��������)
   unsigned char Name[32] ; // ��������
   unsigned char Key [32] ; // ���������� ���������� ���� �������
}
   RSCOBJECTEX;


// �������� �����
typedef struct RSCSEGMENT
{
   ULONG Order;     // ������� ������ ���� �� ������
   unsigned char Name[32];  // �������� ( �� ����� 30)
}
   RSCSEGMENT;

// �������� ���������
typedef struct RSCSEMANTICEX  // ����������� �������� �������������
                              // �������������� ��'����
{
  LONG Code;         // ������� ���
  LONG Type;         // ��� ��������
  LONG Reply;        // ����������� ���������� (1)
  LONG Enable;       // ����������(1),������������(2)
                         // (��� �������� ��������� ���� �� �����������)
  LONG Service;      // ���������,��������� ��� ���� �������� (1)
  LONG Reserv;       // ������ (������ ���� ����� 0)
  char     Name[32];     // �������� ��������������
  char     Unit[8];      // ������� ���������
  double   Minimum;      // ����������� ��������
  double   Default;      // ������������ ��������
  double   Maximum;      // ������������ ��������
  LONG Size;         // ����� ������ ���� �������� ���������
  LONG Decimal;      // �������� ���� �������� ���������
  char     ShortName[16];// �������� ��� ��������� (����� � ����� ��)
}
  RSCSEMANTICEX;

enum FRAMEINCODE                   // 06/04/06
{
   FIRSTSERVEXCODE  = 1000000000l, // ������ ������� ����� ���������
   LINESERVEXCODE   = 1000000001l, // ������� ��� ���������� ���������
   LINESERVINCODE   = 1          , // ���������� ��� ���������� ���������
   SQUARESERVEXCODE = 1000000002l, // ������� ��� ���������� ����������
   SQUARESERVINCODE = 2          , // ���������� ��� ���������� ����������
   POINTSERVEXCODE  = 1000000003l, // ������� ��� ����������  ���������
   POINTSERVINCODE  = 3          , // ���������� ��� ���������� ���������
   TEXTSERVEXCODE   = 1000000004l, // ������� ��� ���������� ������
   TEXTSERVINCODE   = 4          , // ���������� ��� ���������� ������
   VECTSERVEXCODE   = 1000000005l, // ������� ��� ���������� ����������
   VECTSERVINCODE   = 5          , // ���������� ��� ���������� ����������
   COMSERVEXCODE    = 1000000006l, // ������� ��� ���������� �������
   COMSERVINCODE    = 6          , // ���������� ��� ���������� �������
   SERVOBJECT       = 15         , // ���������� ��������� ��������
};

enum SEMTYPE           // ���� �������� ���������
{
   TUNDEFINED = -1,    // �������� �� �����������
   TSTRING    = 0,     // ���������� ������
   TNUMBER    = 1,     // �������� ��������
   TANYFILE   = 9,     // ��� ����� ������������������� ����
   TBMPFILE   = 10,    // ��� ����� BMP
   TOLEFILE   = 11,    // ��� �����,��������������� OLE-��������
   TREFER     = 12,    // ������ �� ������������ ������ �����
                       // (���������� ����� �������)
   TMAPFILE   = 13,    // ��� �����-�������� ������
   TTXTFILE   = 14,    // ��� ���������� �����
   TPCXFILE   = 15,    // ��� ����� PCX
   TCODE      = 16,    // �������� � ���� ��������� ����
                       // �� �������������� ��������
   TDATE      = 17,    // �������� ���� � �������� ���� (��������)
   TANGLE     = 18,    // ������� �������� � ��������
   TTIME      = 19,    // �������� ������� � �������� ���� (������)
   TFONT      = 20,    // ��� ������ ("Arial", "Courier"...)
   TCOLOR     = 21,    // �������� �������� ����� � RGB
   TLAST      = 21     // ������� ������� ������ �����
};

// ����������������� ���� ������������� �������������,
// �������� �� ��� �����                                     // 22/03/04
// ---------------------------------------------------
#define EXTSEMANTIC         31001  // ������ ��������� ��������� ��������
#define SEMIMAGESCALE       31001  // ������� ����������� ����� � ���������
#define SEMIMAGECOLOR       31002  // ���� ����������� ����� RGB
#define SEMIMAGEHIGHT       31003  // ������ ������          // 24/09/04
#define SEMIMAGEFONT        31004  // �������� ������        // 11/05/05
#define SEMIMAGETHICK       31005  // ������� ����� � ��            // 05/05/06
#define SEMIMAGETHICK2      31006  // ������� ��������� ����� � ��  // 05/05/06
#define SEMCOLORWEIGHT      31007  // ��� ����� ������� � ��������� // 25/12/08
#define SEMFONTCOLOR        31008  // ���� ������� 
#define SEMTRANSLUCENCY     31009  // ����������������
#define SEMIMAGEBRIGHT      31010  // �������
#define SEMIMAGECONTRAST    31011  // �������������
#define SEMFONTNUMBER       31012  // ����� ������
#define EXTSEMANTICEND      31012  // ����� ��������� 


// ����������������� ���� ������������� �������������
// ---------------------------------------------------
#define OBJEXCODEINSEMANTIC 32800  // ����������������� ��� ��'����
#define SEMOBJEXCODE        32800  // ����������������� ��� ��'����

#define GROUPLEADER         32801  // ������� ��'����, �������� ������
#define SEMGROUPLEADER      32801  // �� ����������� ��'���

#define GROUPSLAVE          32802  // ������� ��'����, �� �������
#define SEMGROUPSLAVE       32802  // ������� ������ �� �������� ��'����;

#define GROUPPARTNER        32803  // ������� ��'����, ���������
#define SEMGROUPPARTNER     32803  // � ������ ������������ ��'�����

#define SEMOBJECTTOTEXT     32804  // ������ �� ������� �� ��'����
#define SEMOBJECTFROMTEXT   32805  // ������ �� ��'��� �� �������

#define SEMLAYERSHORTNAME   32810  // �������� ��� ���� ��'����
#define SEMOBJECTSHORTNAME  32811  // �������� ��� ��'���� (����)

#define SEMOBJECTDATE       32820  // ���� �������� ��'����
#define SEMOBJECTTIME       32821  // ����� �������� ��'����
#define SEMOBJECTAUTHOR     32822  // ��� ���������

#define SEMSERVICEFIRST     32800  // ������ ��������� ����������� ��������
#define SEMSERVICELAST      32822  // �����  ��������� ����������� ��������

#define SHEETFRAMEINCODE    15l       // ���������� ��� ����� �����  05/02/02
#define SHEETFRAMEEXCODE    91000000l // ������� ��� ����� �����

enum SEMANTIC_FOR_OBJECT   // ������������� ��������� ��� ��������
{
  NONE_SEMANTIC     = 0,   // �� ������������
  POSSIBLE_SEMANTIC = 1,   // ���������
  MUST_SEMANTIC     = 2,   // ������������
  IMAGE_SEMANTIC    = 3,   // ������ �� ��� �����������
  ALL_SEMANTIC      = 4    // ��� ���������
};


// �������� ������������� ��������� ��� ��'�����
typedef struct APPLYSEMANTIC
{                           // ���������� ��'�����,������������ ���������
  long Possible;            // ��� ������������
  long Must;                // ��� ���������
  long Image;               // ��������� ������������ ��� ��������� ����
}
  APPLYSEMANTIC;

// �������� ������
typedef struct RSCFONT
{
  char    Font[32];     // ��������
  char    Name[32];     // �������� ��������
  long    CharSet ;     // ������� ��������
}
  RSCFONT;

// �������� ������� �� ���� �� �������� ��������� ("����� ��'����")
typedef struct RSCRELATION                                 // 01/11/01
{
  unsigned long  ObjectCode   ; // ���������� ��� ������� ���������
  unsigned long  SemanticCode ; // ��� ������������� ���������
  char           Prefix[7]    ; // ���������� ������� (�����) ��� �������
  char           Decimal      ; // ���������� ������ ����� �������
}
  RSCRELATION;

// ����� ������ �������� ��������������                  // 14/04/06
enum SEEK_RSCOBJECT
{
   SEEK_EXCODE = 1,        // ����� �� ����
   SEEK_KEY    = 2,        // ����� �� �����
   SEEK_NAME   = 4,        // ����� �� �����
};


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++ ��������������� ��������� +++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ��������� ������
#define ERRORHEIGHT  -111111.0

// ��������� �������� ����
#define ERRORPOWER   -1111111.0

typedef struct BUILDMTW    //  ��������� �������� ������� �����
{
  unsigned
  long int StructSize;     // ������ ������ ��������� :
                           //  sizeof (BUILDMTW)
  long int Free;           // ������ ���� ����

  double   BeginX;         // ������������� ���������� ������
  double   BeginY;         // (���-��������� ����) ������� � ������

  double   Width;          // ������ ������� � ������
  double   Height;         // ������ ������� � ������

  double   ElemSizeMeters; // ������ ������� ������������� �������
                           // � ������ �� ���������

  long int ElemSizeBytes;  // P����� �������� ������� � ������
                           // (���������� �������� : 1,2,4,8)
                           // ��� �������� ������� �� ���������
                           // ����� �������� ������� ����
                           // ������ ���� ����� 4

  long int Unit;           // E������ ��������� ������
                           // (0 - �����, 1 - ���������,
                           //  2 - ����������, 3 - ���������� )

  long int ReliefType;     // ��� ������� (0 - ���������� ������,
                           //  1 - ���������� + �������������,
                           //  2 - �������������)

  long int UserType;       // ������������ �����, �����������
                           // � ����������� ��������

  long int Scale;          // ����������� �������� �����������
                           // ��������� ����� (��� �������� �������
                           // �� ��������� ����� �������� �������
                           // ���� ����� �������� �� �����������
                           // �������� ��������� �����)

  long int HeightSuper;    // ������ ��� ��������� � ������� �����
                           // ������ ������� � ���������� ������� :
                           //  0 - �������
                           //  1 - ������������
                           //  2 - �����������

  long int FastBuilding;   // ���������� ����
                           // ����� �������� ������� (��� Method = 0) :
                           //  0 - ���������������� ������������ �� 16 ������������,
                           //    ��� ������������ ��������� �����������
                           //  1 - ���������������� ������������ �� 8 ������������,
                           //    ��� ������������ ��������� �����������
                           //  2 - ���������������� ������������ �� 16 ������������,
                           //    � ������������� ��������� �����������
                           //  3 - ���������������� ������������ �� 8 ������������,
                           //    � ������������� ��������� �����������

  long int Method;    // ����� ���������� ����������� :
                      //  0 - ����� ������������ ������� FastBuilding
                      //  1 - ���������������� ������������ �� 16 ������������
                      //  2 - ���������������� ������������ �� 8 ������������
                      //  3 - ���������������� ������������ �� 16 ������������,
                      //      ����������� �����������
                      //  8 - �������� ������������ �� ����� �������������
                      //     (� ������ ������������ ������ �������� �������)
                      //  16 - ������� ����������� � ������� �������
                      //       ��� ReliefType = 2

  long int Extremum;  // ���� ������������ ��������� �����������
                      //     (��� Method = 1,2,3) :
                      //  0 - ��������� ���������� �� �����������
                      //  1 - ��������� ���������� �����������

  HOBJ Border;        // ������������� ���������� ������� �����,
                      // �� �������� ��������������� ����� �����������
                      // ������� (���� ������ ���������� ��� ���������
                      // �������, ������������ ���������� �����
                      // BeginX, BeginY, Width, Height ������
                      // ���������, �� ����� �� ���������������)

  long int LimitMatrixFrame;
                      // ���� ����������� ��������� �������
                      // ��� Method = 1,2,3,8 (�������� �������
                      // ������������ ���������� ����� BeginX,
                      // BeginY, Width, Height ������ ���������) :
                      //  0 - ����������� �� �����������
                      //  1 - �������� ������� ��������������
                      //      ���������� ������
                      //  2 - �������� ������� ��������������
                      //      ���������� ������� ������������
                      //      �������� � ���������� �������


  long int NotUse3DMetric;
                      // ���� - �� ������������ ���������� �������
                      // �������� :
                      //  0 - ���������� ������� ������������
                      //  1 - ���������� ������� �� ������������

  long int SurfaceSquare3DObject;
                      // ���� - ������� ����������� ������ ����������
                      // ������� �� ��� ���������� ������� :
                      //  0 - �� ������� �����������
                      //  1 - ������� �����������
                      // ���� �������� NotUse3DMetric ����� 1,
                      // �� ����������� �� ��������

  long int AltitudeMarksNet;  // 03/10/06
                      // ���� �������������� ��������� �������� ����� ���
                      // ���������������� ������������ (Method = 1,2,3) :
                      //  0 - ��� ������ �������� ����� ����������� ���������� �
                      //      ��������� � ������� ����� ������� ������ (��� �������
                      //      ������ - 3D-�������,��������� �� ����� �� ������ ��
                      //      16 ���������� �����������; ������ ��������� �������
                      //      ������������ ������� ����� � �������, ��������� ���
                      //      ������������ ������� �� ����� �� ������� �����������.
                      //      ���� ������� ������ ������������ ������� ���� �����
                      //      � ���������� ������� ��� ������ �������� ����� � ��������
                      //      ���������� ������������ ��������� �������.
                      //  1 - �� ������ �������� ����� ��������� ������������,
                      //      ң��� ������������ (��� ����� ң���) ��������� � �������
                      //      � ���� 3D-�������� (���� ����� �� ���������� �������
                      //      � ���������� �������, �� ��� ��������� �������,
                      //      ���� ����������, �� ��������� ����� �����, ������������
                      //      ��� �������� � ������ ����������� � ��������);
                      //  2 - �������������� ��������� �������� ����� �� �����������,
                      //      ������ ����� ��������� � ���� ������� �������,
                      //      ������ ����������� ��� ���������� �����������
                      //      �� ������ ������� �����

  long int LimitMatrixByFramesOfSheets;
                      // ���� ����������� ������� ������� ������
                      // (��� Method = 1,2,3,8) :
                      //  0 - ����������� ������� �� �����������,
                      //      ������������� �������� ����� �������������
                      //      ��� ����� ������
                      //  1 - ����������� ������� �����������,
                      //      ������������� �������� �������������
                      //      ������ ������ ��������� ����� ������

  char Reserve[20];   // ������ ���� ����
}
  BUILDMTW;


typedef struct MTRPROJECTIONDATA  //  ��������� �������� ������� �����
{                                 //   (������ � ��������)
  long int  StructSize;         // ������ ������ ��������� : 128 ����
                                //  sizeof (MTRPROJECTIONDATA)

  long int  Free;               // ������ ���� ����

  long int  MapType;            // ��� ����� (�������� � ������������
                                //   � MAPTYPE, ���� MAPCREAT.H)

  long int  ProjectionType;     // ��� �������� (�������� � ������������
                                //   � MAPPROJECTION, ���� MAPCREAT.H)
                                // long  MaterialProjection; // �������� ���. ���������

                                // � ��������
  double    FirstMainParallel;  // ������ ������� ���������
  double    SecondMainParallel; // ������ ������� ���������
  double    AxisMeridian;       // ������ ��������
  double    MainPointParallel;  // ��������� ������� �����
  double    PoleLatitude;       // ������ ������ ��������                 // 27/06/05
  double    PoleLongitude;      // ������� ������ ��������                // 27/06/05

  long      EllipsoideKind;     // ��� ����������                         // 01/07/05
  long      HeightSystem;       // ������� �����                          // 01/07/05
  long      CoordinateSystem;   // ������� ���������                      // 01/07/05

  char      Reserve[52];        // ������ ���� ����
}
  MTRPROJECTIONDATA;

// ��������� ���������� ������� ����������� (������� ������� ��� ������� �����)

typedef struct BUILDSURFACE  // 29/05/07
{
 unsigned
 long int StructSize; // ������ ������ ��������� : sizeof (BUILDSURFACE) = 320 ����
 long int FileMtw;    // ���� ���������� ������������ ����� :
                      //   0 - �������� ����� ������� ������� (*.mtq)
                      //   1 - �������� ����� ������� ����� (*.mtw)

 double BeginX;    // ������������� ���������� ������
 double BeginY;    // (���-��������� ����) ������� � ������

 double Width;     // ������ ������� � ������
 double Height;    // ������ ������� � ������

 double MinValue;  // �������� �������� �������������� �������� ����������� �������,
 double MaxValue;  // ���� MinValue >= MaxValue � ������� ��������� ����������� �������� ��������

 double ElemSizeMeters;  // ������ ������� ������������� �������
                         // � ������ �� ��������� (������� �������)

 long int UserType;      // ������������ �����, ����������� � ����������� ��������
                         //  (���, �������������� �������)

 long int Free;          // ������ ���� ����

 char UserName[32];      // �������� ��� ������� (�������� �������������� ��������)

 HOBJ Border;  // ������������� ���������� ������� �����, ��������������� �������
               // ����������� ��������� ������� (���� ����� ����, �� �� ������������)
               // ���� ������ ���������� ��� ��������� �������, ������������ ����������
               // ����� BeginX, BeginY, Width, Height ������ ���������, �� �� ������������

 HWND Handle;  // ������������� ���� �������, �������� ����������
               // ��������� 0x0581 � �������� ����������� ����� (� WPARAM),
               // ���� ������� ������ ���� ������������� ��������, � �����
               // ������ ��������� �������� 0x0581.
               // ���� Handle ����� ���� - ��������� �� ����������.

 COLORREF* Palette;      // ����� ������� ����������� ������� �������(*.mtq),
                         // ���� ����� ���� - ������������ ������� �� ���������
 long int PaletteCount;  // K��������� ������ � ������� (�� 1 �� 256)

 long int Method;        // ����� ���������� ����������� :
                         //  8 - �������� ������������ �� ����� �������������
                         //      ( ������������ ����� ������� PointArray )
                         //  9 - ��������������� ������������ �� ��������� �����������
                         //       ������ ������������� ��������
                         //      ( ������������ ����� ������� �������� ����� )

 XYHDOUBLE* PointArray;  // ����� ������� �������� �������������� �������� (��� Method = 1)
 long int PointCount;    // ����� ����� � ������� PointArray (��� Method = 1)

 long int SemanticCode;  // ��� ��������� ������������ �������������� (��� Method = 2)

 long int LocalSurfacePointCount;  // K��������� ����� ��� ���������� ��������� �����������
                                   // ������ ������������� �������� (��� Method = 2)

 long int LocalSurfaceRebuildPointCount;  // K��������� �����̣���� ����� ��� ��������
                                          // � ���������� ������������� ��������,
                                          // ��� ������� ��������������� ���������
                                          // ����������� (��� Method = 2)
 double MaxMetricCutLength;  // ������������ ����� � ������ ������� �������
                             // ��� ����������� ����� (��� Method = 2)

 char Reserve[168];          // ������ ���� ����
}
  BUILDSURFACE;


 // ����������� �������� ���������� ��'����  // 01/02/02
 typedef struct
 {
   int         ListNumber;        // ����� ����� ���������� ��'����
   int         ObjectNumber;      // ����� ���������� ��'���� � �����
   HSITE       Map;               // �������� ����������� �����
 }
  MAPOBJDESCEX;

typedef struct
{
  DOUBLEPOINT XY;     // ���������� ����� �����������
  double       H;     // ������ ����� �����������
                      // (�� �������)
  HOBJ Info1;
  long int Number1;   // �� ����� ������ ������� Info1
                      // ��������� ����� �����������
  long int Subject1;  // ����� �������/���������� ������� info2
  HOBJ Info2;
  long int Number2;   // �� ����� ������ ������� Info2
                      // ��������� ����� �����������
  long int Subject2;  // ����� �������/���������� ������� info2
}
  CROSSPOINT;


// ��������� ����������� ������ ���������� ������
// ��������� �� ��� ������������ � �������� �������
// ��������� � ��������� AW_CREATETASKPANEL
typedef struct PANELINFO
{
  HINSTANCE hInst;     // ������������� ���������� ���������� ������ ������
  long int  Count;     // ���������� ������������ ���������������(������) �
                       // ������ ��������� ��������� AW_CREATETASKPANEL
  char      Name[32];  // ����������� �������� ������
}
  PANELINFO;

typedef struct PANELPOS   // �������� LPARAM ��������� AW_MOVEPANEL
{
  RECT Rect;              // ���������� ������ ��������� ������
  long int  Position;     // ������������ ������ � ���� (��. LOCAL)
  long int  Layout;       // ������� ������������ ���������� ����
}
  PANELPOS;

typedef struct BUTTONINFO   // �������� LPARAM ��������� AW_INSERTBUTTON
{
  long int Command;         // ������������� ����������� ������,
                            // ���� Command = (-1) - ����������� �����������
  HBITMAP  hBitmap;         // ������������� �������� �� ������
                            // ��� Linux - ��������� �� ��������� BUTTONINFOLX
  long int Sibling;         // ������������� ������ � ������ ������������,
                            // ����� ������� ����������� ����������� ������.
                            // ���� Sibling = NULL - ����������� � �����
}
  BUTTONINFO;

#ifdef LINUXAPI                   // 07/06/05
typedef struct BUTTONINFOLX // �������� hBitmap ��������� BUTTONINFO
{
  HBITMAP  hBitmap;         // ������������� �������� �� ������

  char     Hint[80];        // ���������
}
  BUTTONINFOLX;
#endif


typedef struct CONTRINFO  // �������� LPARAM ��������� AW_INSERTBUTTON
{
  long int CtrlId;          // ������������� ������������ �������� ����������,
                            // ���� CtrlId = (-1) - ����������� �����������
  HWND     hWindow;         // ������������� ���� �������� ����������

  long int Sibling;         // ������������� �������� ���������� � ������
                            // ������������, ����� �������� �����������
                            // ����������� ������� ����������.
                            // ���� Sibling = NULL - ����������� � �����
}
  CONTRINFO;

typedef struct HITCONTROLINFO // �������� LPARAM ������� MT_PANELRBUTTONUP
{
  POINT    Position;          // ��������� ������� �� ������

  long int CtrlID;            // ������������� �������� ���������� ������,
                              // ��� ������� ���� ������ �������
}
  HITCONTROLINFO;        //03/07/00

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ������� ��������� ���������� +++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef enum READLOG   // ������� ���������� ����������
{
  READ_ANYACTION = 0,  // ������� ��������� ����������
  LOG_ANYACTION  = 0,  // ���������� ��������� ����������
  READ_MYACTION  = 1,  // ������� ���� ��������� ����������
                       // (�� ����� ������������)
  LOG_MYACTION   = 1,  // ���������� ���� ����������
}
 READLOG;

// ����������������� ���� ����������
enum ACTION_TYPE
{
  AT_OPEN     = 60000,     // ������ ������
  AT_CLOSE    = 60001,     // ������ ������
  AT_LOGON    = 60002,     // ������ � ������ ��������
  AT_LOGOFF   = 60003,     // ������ � ������ ���������
  AT_CLEAR    = 60004,     // ����� ������ ������� (����������,...)
  AT_FIRST    = AT_OPEN,   // ������ ����������������� ���
  AT_LAST     = AT_CLEAR,  // ��������� ����������������� ���
  AT_UNDO     = 60005,     // ������ �����-���� ���������� ����������
  AT_NEXT     = 60006,     // ����������� ���������� ����������
};

// ���� Type == AT_OPEN, ����� ��������� ����
// �������� ��������� ����������, ������ 16 ����
// (��� ���������� � ����).

typedef struct ACTIONHEAD  // ��������� �������� ����������
{
  short int      Ident;    // 0x7FFF
  unsigned short Task;     // ������������� ������,����������� ����������
  unsigned short Count;    // ����� �������� (Length = 16+Count*16)
  unsigned short Type;     // ��� ���������� (��� ������)
  long  int      Date;     // ���� ���������� ����������
  long  int      Time;     // ����� ���������� ����������
}
 ACTIONHEAD;

// ���� �������� ��� ��'�����
enum OBJECT_OPERATION
{
   OO_APPEND    = 1,        // �������� ��' ����
   OO_DELETE    = 2,        // �������� ��'����
   OO_UPDATE    = 4,        // ���������� ��'����
   OO_UNDO      = 8,        // �������������� ��'����
};

// ����� ������������ ��������� ��'����
enum ACTION_MASK
{
   AM_HEAD      = 1,        // �������� ���������� ������
   AM_METRIC    = 2,        // �������� ������� ��'����
   AM_SEMANTIC  = 4,        // �������� ���������
   AM_DRAW      = 8,        // �������� ����������� ��������
};

typedef struct ACTIONRECORD // �������� ��������� ��������
{                           // (��� AT_OPEN - ��� ������ 16 ����)
  long int      Key;        // ���������� ����� ������� � �����
  long int      Number;     // ���������������� ����� � ������ ���������
  long int      Back;       // ����� ������ � ����� ������ (���������)
  unsigned char Type;       // ��� ��������
  unsigned char Mask;       // ����� ������������ ��������� �������
  short         List;       // ����� �����
}
 ACTIONRECORD;

// ���� �������� ������ �������
enum COLORMODEL
{
   MODEL_RGB       = 0,
   MODEL_CMYKINDEX = 1,     // ����������� ��������� ������ CMYK �������
   MODEL_CMYKCOLOR = 2,     // ����������� ������� CMYK �������
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ���������� � ��������� �� ���� �����  ++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifdef WIN32API
typedef long int (WINAPI * CHANGECALL)(long int parm, long int value);
#else
typedef long int (*CHANGECALL)(long int parm, long int value);
#endif

typedef struct CHANGEINFO
{
  HSITE    hSite;     // ������������� ����� � ���������
  short int List;     // ����� ����� �����
  unsigned char Type; // ��� �������� (OBJECT_OPERATION)
  unsigned char Mask; // ����� ������������ ��������� ������� (ACTION_MASK)
  long  int Key;      // ���������� ����� ������� � �����
  long  int Object;   // ���������������� ����� ������� � �����
}
  CHANGEINFO;


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++ ��������� ������������ � ������ ������ +++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef struct FILEMAPPING  // ��������� ����������� ����� � ������
{
  HANDLE   hFile;           // ������������� ��������� �����
  HANDLE   hMapping;        // ������������� ����������� (� UNIX = 0)
  char *   Address;         // ����� ������� ������ ��� ����������� ������
  unsigned long int Offset; // �������� � ����� �� ������ ���� ������
  unsigned long int Size;   // ������ ������������ ������� � �����
  unsigned long int Shift;  // �������� �� ������ ���� � ������� ������
                            // ��� ����� ��������� ������� �������� (64 ��)
}
  FILEMAPPING;

// 20/05/04
// ���� �������� ���������� �������, ������� �����, � ������ - �����
// (��. mapCreateObjectsCross(...) � seekapi.h)
#define FLAGINSIDEOBJECTS  32

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++ ��������� �� ���� �� �����  +++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct PUTTOMAPINFO
{
  long int Incode;     // ���������� ��� �������
  long int MapNumber;  // ����� �����
  long int Regime;     // ������ ��������� �������

}
  PUTTOMAPINFO;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++ ���������� � ����� ����������� ++++++++++++
// +++++++++++++  ������� � �������� ���������� ++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct NUMBERPOINT
{
  DOUBLEPOINT Point;   // ���������� �����
  long int Number;     // ����� ����� �������, �� ������� ������� point
  long int Update;     // ����������� ������ ����� �������
  long int Equal;      // ����� ����� ���������� � �������
  long int Reserve;
}
  NUMBERPOINT;

#endif  // MAPTYPE_H

