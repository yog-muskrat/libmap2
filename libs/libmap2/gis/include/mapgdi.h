
#ifndef MAPGDI_H
#define MAPGDI_H

#ifndef MAPTYPE_H
 #include "maptype.h"
#endif


// ����� ���������������� ������� (������������ ��� Image ������ IMG_OBJECT)

#define IM_PRESS       0x00000000  // ������� ��� ���������� ����� (�� ���������)
#define IM_DONTPRESS   0x04000000  // �� ������� ��� ����������

#define IM_SCALE       0x01000000  // ��������������
#define IM_DONTSCALE   0x02000000  // �� ��������������

#define IM_SCALEDONTPRESS  (IM_SCALE | IM_DONTPRESS)  // ������ �����������

#define IM_CLEARSCALE 0x0F8FFFFFF  // ������ ����� ���������������


//-----------------------------------------------------------------
// �������� ������� ����������� ������������ ��'����
//-----------------------------------------------------------------

typedef struct PAINTPARM
{
  LONG Image;  // ��� ������� �����������

  char *   Parm ;  // ��������� ����������� ��� ��������������� �������.
                   // ������������ ��� Image ������ IMG_OBJECT (���������
                   // � ����� ������� ��������������� �� ��������������)

  LONG Mode ;  // ������� ����������� � ���������������
                   //   R2_COPYPEN   - ����������� ������
                   //   R2_NOT       - ����������� ��������� ���� (���� ������������)

                   //   IM_SCALE, IM_DONTSCALE, ... - �������� ����������������
                   //    (������������ ��� Image ������ IMG_OBJECT)

                   // ������ �������������: Mode = R2_NOT | IM_SCALE
}
  PAINTPARM;


//-----------------------------------------------------------------
// �������� ���������� ������
//-----------------------------------------------------------------
// �������� ����� ������ ����� ���� ������ ����� ������.
// ����������� ����� ������ - 5 ����: 4 ����� - ����� = 5 � 1 ���� = 0
// ���� � ������ ����������� '\n',
// �� ����������� ������� �� ��������� ������
//-----------------------------------------------------------------

typedef struct TEXTRECORD
{
  LONG Length ;                  // ����� ������, ������� ���� Length
  char Text[256];                // �����, ��������������� �������� 0
}                                // ����� ������ � ��������� WINDOWS
  TEXTRECORD;


//-----------------------------------------------------------------
// �������� ��������� ������������ ��'����
//-----------------------------------------------------------------
// ������� ��������� � ��� ������� ���������
// �������� � ���������� ������� ������������
//-----------------------------------------------------------------

typedef struct PLACEDATA         // ���������� � ������������ �������
{
  DOUBLEPOINT * Points    ;      // ������ ��������� ��������� ��������
  LONG *    PolyCounts;      // ������ ���������� ����� ��������
  LONG      Count     ;      // ���������� �������� ��� �������� TEXTRECORD
                                 // ��� ������� ���� IMG_TEXT :
  TEXTRECORD *  PolyText  ;      // ������� ��������������� �������������
                                 // ������� ���� TEXTRECORD, ������� �������
                                 // ����� ���� �������, �� �� ������ 5 ����,
                                 // ����� �������� ����� Count !
}
  PLACEDATA;


//-----------------------------------------------------------------
// ��������� ����������� ������� ���� �������
//-----------------------------------------------------------------

typedef struct PAINTEXAMPLE
{
  HDC       Hdc;       // �������� ����������
  RECT*     Rect;      // ������� ����������� � ��������

  LONG  Func;      // ����� ������� (IMG_LINE, IMG_DOT, ...)
  char*     Parm;      // ��������� �� ��������� �������

  POLYDATAEX* Data;    // �������
                       //   (���� Data != 0, �� text ������������)
                       //   (���� Data == 0, �� ��������� �������������)

  char*     Text;      // ����� ������ � ��������� WINDOWS
                       //   (���� Text == 0, �� ��������� �������������)

  LONG  Local;     // ����������� (LOCAL_LINE, LOCAL_SQUARE, ...)
                       //   (������������ ��� Data == 0)

  float     Factor;    // ����������� ���������� (Factor >= 0.0)
                       //  0.0 - �������������� �������������

  LONG  Colors;    // ����� ������ �������
  COLORREF* Palette;   // ��������� �� �������

  LONG  VisualType;     // ��� ������������ (VT_SCREEN, VT_PRINT, ...)
                            //    0 - �������

  LONG  FillIntensity;  // ������������� ������� (0,100)
                            //    0 - �������
                            //  100 - � �������� ������
  char      Reserve[16];
}
  PAINTEXAMPLE;


//******************************************************************
// ���� ������� ������������ ������������ ����������� ��'����� �� ��
//******************************************************************

#define IMG_EMPTY             127  // ������ ������� - ��� ����������

#define IMG_LINE              128
#define IMG_DOT               129

#define IMG_SQUARE            135

#define IMG_CIRCLE            140

#define IMG_TEXT              142

#define IMG_MULTIMARK         143
#define IMG_MULTISQUAREMARK   144

#define IMG_DRAW              147

#define IMG_DOTSHIFT          148

#define IMG_VECTOREX          149

#define IMG_TEMPLATE          150

#define IMG_TRUETYPE          151

#define IMG_TRUETEXT          152

#define IMG_HATCHSQUARE       153

#define IMG_SQUAREGLASS       154

#define IMG_SQUAREVECTOR      155
#define IMG_VECTOREXTURN      156

#define IMG_DECORATE          157
#define IMG_DASH              158
#define IMG_LINESHIFT         159
#define IMG_VECTORTEXT        160
#define IMG_VECTORNODE        161       // ��������� � ����� (IMGVECTOREX)
#define IMG_THICKENLINE       162       // ������������ �����
#define IMG_MIDDLETHICKENLINE 163       // ������������ ����� � �������� �� ������
#define IMG_SQUAREGLASSCOLOR  164
#define IMG_GRAPHICMARK       165       // ���� �� ����� (���, Metafile )
#define IMG_HATCHSQUARESHIFT  166       // ����������� ��������� �� ��������� ��������� // 31/03/08
#define IMG_POLYGONGLASS      167       // �������-������ � ��������� ������������ // 19/01/09
#define IMG_LINEGLASS         168       // �����-������ � ��������� ������������ // 23/01/09

#define IMG_VECTORGRADIENT    199       // ��������� �������

#define IMG_PERCENT           249       // ��������� ���� IMG_LONG
#define IMG_LIBRARY           250

#define IMG_SEMANTIC          251       // ��������� ���� IMG_LONG
#define IMG_COLOR             252       // ��������� ���� IMG_LONG
#define IMG_DOUBLE            253
#define IMG_LONG              254

#define IMG_OBJECT            255       // ����� ������� ���������������
                                        // �� ��������������

// ���������� ���� (��� IMG_SQUAREMARK, IMG_MULTISQUAREMARK,
//                      IMG_SQUARECROSS, IMG_FONT, IMG_SQUAREGLASSCOLOR)
#define IMGC_TRANSPARENT  0x0FFFFFFFFL
#define IMGC_NOMARK       0x0FFFFFFFFL  // �� �������� (��� IMG_OBJECT)

// ����� ��� ����������� ������� ����� (������|IMGC_INDEX, RGB)
#define IMGC_INDEX        0x0F0000000L  // ���� ����� �� ������� �����
#define IMGC_CLEARINDEX   0x0FF000000L  // ��� ������� ����� ����� (& IMGC_CLEARINDEX)
#define IMGC_CLEARCOLOR   0x000FFFFFFL  // ���� ������� �����      (& IMGC_CLEARCOLOR)

// ���������� ������ ����� 
// color - ����� ����� � ������� RSC, ������� � 0 !!!
// ���� ���� IMGC_INDEX �� ����������, ���� � ������� RGB
#define SETCOLORINDEX(color)   (((long int)(color))|IMGC_INDEX)

#define IMGC_SYSTEM       0x0F1000000L  // ���� ����� �� ��������� ������� (LINUX)  // 16/10/03
#define SETCOLORSYSTEM(color)  (((long int)(color))|IMGC_SYSTEM)

// ���������� ������ ����� (����������: 0 - RGB, 1 - ������ �� �������)
#define TESTCOLORINDEX(color)  ((((long int)(color))&IMGC_CLEARINDEX)==IMGC_INDEX)

// ���������� ������ ����� (����������: 0 - RGB, 1 - ������ �� ��������� �������)
#define TESTCOLORSYSTEM(color) ((((long int)(color))&IMGC_CLEARINDEX)==IMGC_SYSTEM)  // 16/10/03

// ��� ����� ���������� 4x4 (16 ���) (��� IMG_SQUAREMARK, IMG_MULTISQUAREMARK)
//  1 - ����������� �������� �����
//  0 - �������������
// �������� ����� �����:
//  0000(0)  1111(F)  1010(A)  0101(5)
//  0000(0)  1111(F)  0101(5)  1010(A)
//  0000(0)  1111(F)  1010(A)  0101(5)
//  0000(0)  1111(F)  0101(5)  1010(A)
#define IMGK_REGULAR0     0x00000000L  // ���������� (��������� ���)
#define IMGK_REGULAR      0x0000FFFFL  // ���������� (��������� ���)
#define IMGK_ONECHESS     0x0000A5A5L  // ���������
#define IMGK_TWOCHESS     0x00005A5AL  // ��������� ���������

// ����������� ������� (��� IMG_OBJECT)
#define IMGL_LINE      0  // ��������
#define IMGL_SQUARE    1  // ���������
#define IMGL_POINT     2  // ��������
#define IMGL_TITLE     3  // �������
#define IMGL_VECTOR    4  // ���������
#define IMGL_MIXED     5  // ������� ������� (������)

// ��� ��p������ (��� IMG_SQUARECROSS)
#define SC_HORIZONTAL  1  // ��p������������ �������
#define SC_VERTICAL    2  // ��p���a������ �������
#define SC_QUADRATIC   3  // �����a��
#define SC_CROSS45     4  // ��� ����� 45 ��������
#define SC_CROSS135    5  // ��� ����� 135 ��������

// ���� ��������� ������� (��� SCR_VECTOR)
#define VT_THICK2      2  // ����� ������� 2
#define VT_THICK3      3  // ����� ������� 3
#define VT_THICK4      4  // ����� ������� 4
#define VT_THICK5      5  // ����� ������� 5
#define VT_CIRCLE2     8  // ���������� ������� 2
#define VT_CIRCLE3     9  // ���������� ������� 3
#define VT_CIRCLE4    10  // ���������� ������� 4
#define VT_CIRCLE5    11  // ���������� ������� 5

// ���� ��������� ������� (IMG_VECTOREX)
#define VT_SQUARE      0  // �������
#define VT_LINE        1  // �����
#define VT_ROUND       6  // ���� (�������)
#define VT_CIRCLE      7  // ����������
#define VT_FREE       12  // ������� �� ����������

// ���� ��������� ������� (IMG_VECTOREX)
#define VT_ELLIPSE    64  // ������
#define VT_OVAL       65  // ������ (�������)
#define VT_ARC        66  // ������� ���� ����
#define VT_PIE        67  // ������ (�������)
#define VT_TEXT       68  // ������� ���� ����� (����������)
#define VT_STEXT      69  // ������� ���� ����� (�� ���������)
#define VT_ARC_REVERT 70  // ������� ���� ����

// ���� ��������� ������� ��� �������� ��������� �����
#define VT_OBJECT    101  // ������ �����
#define VT_SUBJECT   102  // ������ ����������
#define VT_END       103  // ����� �����

// �������� ��������� �������� � ������� � �������
#define MKMINPIX     250  //  1000 * 25.4 / 96 = 264.583333
#define PIX2MKM(pixel)  (((long int)(pixel))  * MKMINPIX)
#define MKM2PIX(metric) (((long int)(metric)) / MKMINPIX)

//------------------------------------------------------------------
// ��� IMG_FONT
//------------------------------------------------------------------

// ���������� ���� (���� ��� ����)
#define UNIC_TRANSPARENT  255

// ������������� ������ �������
#define UNIW_NORMAL       0  // ����������
#define UNIW_NARROW       1  // �������
#define UNIW_WIDE         2  // �������

// ������������ �� ���������
#define UNIA_BASELINE     0  // �� ������� �����
#define UNIA_TOP          1  // �� �����
#define UNIA_BOTTOM       2  // �� ����

// ������������ �� �����������
#define UNIA_LEFT         0  // �� ������ ����
#define UNIA_CENTER       1  // �� ������
#define UNIA_RIGHT        2  // �� ������� ����

// ���������� ���������� ������ ������� � ��������
#define CharMin  5  // ������� ������� < CharMin, �� ������������
                    // 5 - 25/10/99

// ������������� ������ ������� (mapgds.h)
//  UNIW_NORMAL     - ����������
//  UNIW_NARROW     - �������
//  UNIW_WIDE       - �������

#ifdef LINUXAPI  // 23/04/01
// ��� ������, ������� ������� (Windows-���������)
//  FW_THIN         - ������
//  FW_ULTRALIGTH   - ������
//  FW_NORMAL       - �������
//  FW_MEDIUM       - ����������
//  FW_BOLD         - �������
#define FW_DONTCARE         0
#define FW_THIN             100
#define FW_EXTRALIGHT       200
#define FW_LIGHT            300
#define FW_NORMAL           400
#define FW_MEDIUM           500
#define FW_SEMIBOLD         600
#define FW_BOLD             700
#define FW_EXTRABOLD        800
#define FW_HEAVY            900

#define FW_ULTRALIGHT       FW_EXTRALIGHT
#define FW_REGULAR          FW_NORMAL
#define FW_DEMIBOLD         FW_SEMIBOLD
#define FW_ULTRABOLD        FW_EXTRABOLD
#define FW_BLACK            FW_HEAVY

#endif // LINUXAPI


// ������������ �� ����������� (Windows-���������)
#define FA_LEFT      0     // ����� = TA_LEFT       // 14/09/00
#define FA_RIGHT     2     // ������ = TA_RIGHT     // 14/09/00
#define FA_CENTER    6     // �� ������ = TA_CENTER // 14/09/00

// ������������ �� ��������� (Windows-���������)
#define FA_TOP       0     // ������ = TA_TOP       // 14/09/00
#define FA_BOTTOM    8     // ����� = TA_BOTTOM     // 14/09/00
#define FA_BASELINE  24    // �� ������� ����� = TA_BASELINE  // 14/09/00
#define FA_MIDDLE    4120  // �� ������� ����� = (TA_BASELINE|0x01000) // 14/09/00

// ����� ������� ������������
#define FA_MASK     (FA_CENTER | FA_MIDDLE)         // 23/04/03


// ���� ������������ ������ (����������, � ������� �������)
#define CA_BASELINE_LEFT          20
#define CA_BASELINE_RIGHT         21
#define CA_BASELINE_CENTER        22

#define CA_MIDDLE_LEFT            23
#define CA_MIDDLE_RIGHT           24
#define CA_MIDDLE_CENTER          25

#define CA_TOP_LEFT               26
#define CA_TOP_RIGHT              27
#define CA_TOP_CENTER             28

#define CA_BOTTOM_LEFT            29
#define CA_BOTTOM_RIGHT           30
#define CA_BOTTOM_CENTER          31

// �������� ����� ������������ ������
#define CA_MINCODE  CA_BASELINE_LEFT
#define CA_MAXCODE  CA_BOTTOM_CENTER

// ������� �������� (Windows-���������)
//  RUSSIAN_CHARSET - ��� ������ (ANSI/WINDOWS)
//  OEM_CHARSET     - ��� ������ (OEM/866/DOS)
//------------------------------------------------------------------

//******************************************************************
//               ��������� ���������� ������������                 *
//******************************************************************
//      ��� ������� (�������, �����, ���������� ...) � ��������    *
//                 (� �������� ����� ����������)                   *
//******************************************************************
// ����������:                                                     *
//  1. ���� � ������� COLORREF (0x00BBGGRR) ��� ����� �������      *
//     ������� ����� � ������� �����, ���� ������� ���� ����� 0x0F *
//  2. ��� �������� �������� � ������ ������ (��������)            *
//     ������������ �������� PIX2MKM(����� ��������):              *
//     Parm->Thick = PIX2MKM(2);  (������� 2 �������)              *
//******************************************************************

typedef struct IMGLINE           // (128) �����
{                                //      (size = 8)
  ULONG Color;           // ���� ����� (COLORREF)
  ULONG Thick;           // ������� �����
}
  IMGLINE;

typedef struct IMGTHICKENLINE    // (162,163) ������������ �����
{                                //      (size = 12)
  ULONG Color;           // ���� ����� (COLORREF)
  ULONG Thick;           // ������� �����������
  ULONG Thick2;          // ������� ������������ (���������)
}
  IMGTHICKENLINE;

typedef struct IMGDOT            // (129) ���������� �����
{                                //      (size = 16)
  ULONG Color;           // ���� �����
  ULONG Thick;           // ������a ��p���
  ULONG Dash ;           // ����� ��p���
  ULONG Blank;           // ����� �p�����
}
  IMGDOT;

typedef struct IMGSQUARE         // (135) ��������� ��'���
{                                //      (size = 4)
  ULONG Color;           // ���� �������
}
  IMGSQUARE;

typedef struct IMGCIRCLE         // (140) ����������
{                                //      (size = 12)
  ULONG Color ;          // ���� ����������
  ULONG Thick ;          // ������� �����
  ULONG Radius;          // ������ ����������
}
  IMGCIRCLE;


typedef struct IMGTEXT           // (142) �����                   // 30/01/01
{                                //      (size = 32)
  ULONG  Color       ;   // ���� ������
  ULONG  BkgndColor  ;   // ���� ���� (IMGC_TRANSPARENT - ����������)
  ULONG  ShadowColor ;   // ���� ���� (IMGC_TRANSPARENT - ����������)
  ULONG  Height      ;   // ������ (��� ������������ �� �������
                                 // �� ��������� 1800 ���)
  unsigned short Weight      ;   // ��� ������, ������� ������� (FW_THIN, ...)
  unsigned char  Outline     ;   // ������� ������ ���� � ���� ������� // 17/07/07
                                 // 0 - �� ��������. 1 - ������ ������, 2 - �������
  unsigned char  Reserve     ;   // ������
  unsigned short Align       ;   // ������������ (FA_LEFT|FA_BASELINE, ...)
  unsigned short Service     ;   // ����� 0
  unsigned char  Wide        ;   // ������������� ������ ������� (UNIW_NORMAL, ...)
  unsigned char  Horizontal  ;   // ������� ��������������� ������������ (0/1)
  unsigned char  Italic      ;   // ������� ������� �������� (0/1)
  unsigned char  Underline   ;   // ������� �������������    (0/1)
  unsigned char  StrikeOut   ;   // ������� ��������������   (0/1)
  unsigned char  Type        ;   // ��� ������ (����� � �������: 0,1,2,3,4)
  unsigned char  CharSet     ;   // ������� �������� (RUSSIAN_CHARSET, ...)
  unsigned char  Flag        ;   // ����� ��� ������ :
                                 //  1 - ������� ������������ �� �������
}
  IMGTEXT;

#define IMGTEXT_SCALE  1
#define IMGTEXT_SHOWCODE 2                       // 21/07/06

typedef IMGTEXT IMGFONT;


typedef struct IMGMARKCHAIN      // �������� ��������� ��'��� �������
{                                //      (size = 4 + 128 = 132)
  ULONG Color    ;       // ���� �����
  unsigned char Bits[128];       // ��������� ����������� 32x32 � �������� ����
}
  IMGMARKCHAIN;


typedef struct IMGMULTIMARK      // (143) ������������ ��������
{                                //      (size = 20 + 132*Count)
  ULONG Length;          // ������ ����� ������ �������� �������
  ULONG Count ;          // ����� ������ � �����
  ULONG Size  ;          // ������ � �������� (��� ������)
  ULONG PosV  ;          // ����� �������� ����� PosV,PosH  <  Size
  ULONG PosH  ;          //  (��� IMGMULTISQUAREMARK - ��� ����� >= Size)
                                 // �����: Count �������� ���� IMGMARKCHAIN
}
  IMGMULTIMARK;


typedef struct IMGMULTISQUAREMARK// (144) ��������� + ������������ ��������
{                                //      (size = 4 + 20+132*Count )
  unsigned short Kind    ;       // ��� ����� ���������� 4x4 (16 ���)
                                 //  (IMGK_REGULAR, ...)
  unsigned char  FullMark;       // ���� ����������
                                 //  0 - �� ���� �������
                                 //  1 - ������ ������� �������
  unsigned char  Weight  ;       // ��� �����, ������� �������   // 27/04/00
                                 //  0 - ������
                                 //  1 - ����������
  IMGMULTIMARK   Mark    ;       // (143) ������������ ��������
                                 // �����: Count �������� ���� IMGMARKCHAIN
}
  IMGMULTISQUAREMARK;


typedef struct IMGDECOR          // ��������� ����� ����������
{
  unsigned short Length;         // ����� ���������� >= 4
                                 // (������� sizeof(IMGDECOR))
  unsigned short Number;         // ����� �������
}
  IMGDECOR;

// ����� ��� ������ ����������   // 28/07/00
#define IMGD_SPLINE       0x0001 // ���� ��������� �� ���������� �������

typedef struct IMGDRAW           // (147) ����� ����������
{
  ULONG Ident   ;        // ������������� ������ 0x7FFF7FFE
  ULONG Length  ;        // ������ ����� ������ �������� �������
  unsigned short Count  ;        // ���������� ����������
  unsigned short Flags  ;        // ������ ���� 0
  IMGDECOR      Image   ;        // ��������� ������� ���������
  ULONG Parm[1] ;        // ��������� ��������� �� ����
                                 // ����� ��������� � ���������
                                 // ��������� ����������
} IMGDRAW;

typedef IMGDRAW  SCRDRAW ;

typedef struct IMGDOTSHIFT       // (148) ������� ���������
{                                //
  IMGDOT    Dot   ;              // �������
  LONG      Shift ;              // ����������� � �������� ������
                                 // 0 - ������� ����� ������ �������� � ���
                                 // > 0 ���������� ������ �� ���,����� �����
                                 // ��� ������ = - ������ ������� ����� �����
                                 // �������� �  ���
}
 IMGDOTSHIFT;

typedef IMGDOTSHIFT SCRDOTSHIFT;

typedef struct IMGVECTPOINT      // ��� (149) �������� ����� �������
{                                //      (size = 8)
  LONG Hor;                      // ���������� �� ����� ��������
  LONG Ver;                      // ������ � ���� � ������������
                                 // � ����� �������:
                                 //  �����  �������  ����� ������ � ���������
                                 // Circle, Round  (h,v)  (dh,dh)
                                 // Ellipse, Oval  (h,v)  (dh,dv)
                                 // Arc,      Pie  (h,v)  (dh,dv) (h1,v1)(h2,v2)
}
  IMGVECTPOINT;


typedef struct IMGPOLYDESC       // ��� (149) �������� �������
{                                //      (size = 12 + 8*Count + Length)
  unsigned char  Type    ;       // ��� ������� (VT_SQUARE, ...)
                                 // ��� ��������� ����� VT_OBJECT,
                                 // VT_SUBJECT, VT_END)
  unsigned char  Image   ;       // ��� ����������
                                 // (IMG_SQUARE, IMG_LINE, IMG_DOT,
                                 // IMG_VECTORTEXT)                 // 11/04/05
  unsigned short Length  ;       // ����� ���������� (>= 4)
  ULONG  Parm    ;       // ��������� ������� �� �� ����
  ULONG  Count   ;       // ����� ����� � �������
  IMGVECTPOINT   Point[1];       // ���������� �� 512 �����
}
  IMGPOLYDESC;

typedef struct IMGVECTOREX       // (149,156) ��������� ���������� ��'����
{                                //      (size = 20 + ...)
  LONG Length      ;             // ������ ����� ������ �������� �������
  LONG PosV        ;             // ����� �������� ����� �� ���������
  LONG PosH        ;             //  � ����������� (��������� ������ �����)
  LONG Base        ;             // ����� ������� ������ ����� �����
  LONG VLine1      ;             // ������ ������� �� ���������  (0)
  LONG VLine2      ;             // �����  ������� �� ���������  (VSize)
  LONG VSize       ;             // ��������� ������ ������� �� ���������
  LONG HLine1      ;             // ������ ������� �� ����������� (0)
  LONG HLine2      ;             // ����� ������� �� �����������  (HSize)
  LONG HSize       ;             // ��������� ������ ������� �� �����������
  char Static      ;             // 1 - �������������� ������������
                                 // 0 - �� �������
  char Mirror      ;             // ���� ����������� ����������� �����
                                 // � ����������� ������ ����� �������
  char NoPress     ;             // ������� ������� ������ �����
  char Scale       ;             // ������� ������������ �� �������
  char Centre      ;             // ������� ������������� �� �������
  char Reserve[3]  ;             // ������
  LONG Border      ;             // �������� ����� �� ������� � ��� ��� 0
  LONG Count       ;             // ����� ����������,����������� ����
  IMGPOLYDESC  Desc;             // �������� ���������
}
  IMGVECTOREX;                   // �� �� ��� IMG_VECTOREXTURN (156)

typedef struct TABLETEMPLATE     // ���������� ����� ���������� �������
{
  LONG Length  ;                 // ����� ���������
  int Order[12];                 // ������ � ����������
                                 // 0-������ ������
                                 // -1 �����  -2 ����
                                 // >0  ����� ��������� �������  (�����)
  LONG Origin  ;                 // ����� ������ ��������
  LONG Static  ;                 // 1 - �������������� ������������
                                 // 0 - �� �������
}
  TABLETEMPLATE;

typedef struct IMGTEMPLATE       // (150) ��������� ���������� �������
{                                //      (size = 20 + ...)
  LONG Length               ;    // ������ ����� ������ �������� �������
  TABLETEMPLATE Table       ;    // ���������� ����� ���������� �������
  LONG          Count       ;    // ���������� ����������
  IMGDECOR      Text        ;    // ��������� ������
  ULONG Parmtext[1] ;    // ��������� ������
  IMGDECOR      Line        ;    // ��������� �����
  ULONG Parmline[1] ;    // ��������� �����
  IMGDECOR      Mark        ;    // ��������� �����
  ULONG Parmmark[1] ;    // ��������� �����
}
  IMGTEMPLATE;

typedef struct IMGTRUETYPE       // (151) ��������� ����� �� TRUETYPE ������
{
  IMGTEXT Text     ;             // ��������� ������
  char FontName[32];             // �������� �������� ������
  LONG Number      ;             // ����� ����� � ������
  LONG MinV        ;             // �������� �����
  LONG MinH        ;             //  ������������ ����� ��������
  LONG MaxV        ;             // (0,0)
  LONG MaxH        ;             // (H,H/2) - ��������� ��������
  LONG PosV        ;             // ����� �������� ����� �� ���������
  LONG PosH        ;             // � ����������� (0,0)
}
  IMGTRUETYPE;

typedef struct IMGTRUETEXT       // (152) �����
{                                //      (size = 64)
  IMGTEXT Text     ;             // ��������� ������ (���� Type - �����������)
  char FontName[32];             // �������� �������� ������
}
  IMGTRUETEXT;

typedef struct IMGSQUAREGLASS    // (154) ��������� ��'��� - ������
{                                //      (size = 8)
  LONG Bright;            // ������� ��������� ������� (+/- 100)
  LONG Contrast;          // ������� ��������� ��������� (+/- 100)
}
  IMGSQUAREGLASS;

typedef struct IMGSQUAREVECTOR   // (155) ��������� + ���������
{                                //
  LONG           Length  ;       // ����� ���������
  unsigned short Kind    ;       // ��� ����� ���������� 4x4 (16 ���)
                                 //  (IMGK_REGULAR, ...)
  unsigned char  FullMark;       // ���� ����������
                                 //  0 - �� ���� �������
                                 //  1 - ������ ������� �������
  unsigned char  Reserv  ;       // ������ ���� 0
  LONG           StepHor ;       // ���������� ����� ������� �� �����������
  LONG           StepVer ;       // ���������� ����� ������� �� ���������
  LONG           Angle   ;       // ���� �������� ����� �� ��������� �� �������
  IMGVECTOREX    Mark    ;       // �������� �����
}
  IMGSQUAREVECTOR;


#define DO_BASE      1           // ������� ������ (����� ���� �������)
                                 // ������� ����������� �������
#define DO_FIRST     2           // �� ������ �����
#define DO_END       3           // �� ��������� �����
#define DO_LEFT      4           // ����� �� ������ �����
#define DO_RIGHT     5           // ������ �� ������ �����
#define DO_MIDDLE1   6           // ����� ����� (1 - �����������)
#define DO_MIDDLE2   7           // ����� ����� (2 - �����������)


typedef struct IMGDECORHEAD      // ��������� ������������ ���������
{
  ULONG Length      ;    // ������ ����� ������ �������� �������
           LONG Begin       ;    // ����� ������ �����
           LONG End         ;    // ����� ����� �����
           LONG Left        ;    // ����� ������ �������
           LONG Right       ;    // ����� ����� �������
           LONG First       ;    // ����� ������� ������������ �����
           LONG Second      ;    // ����� ������� ������������ �����
           char Equidistant ;    // ���������� ��������� �� ���� �����
           char Reserv[3]   ;    // ������ - ����� 0
}
  IMGDECORHEAD;

typedef struct IMGDECORATE        // (157) ����������� ��������
{
  IMGDECORHEAD   Head         ;   // ���������
  IMGDECOR       Base         ;   // ��������� ������� �������
  ULONG  BaseParm[1]  ;   // ��������� ������� �� ����
  IMGDECOR       Begin        ;   // ��������� ���������� ����� �����
  ULONG  BeginParm[1] ;   // ��������� �� ����
  IMGDECOR       End          ;   // ��������� ���������� ����� �����
  ULONG  EndParm[1]   ;   // ��������� �� ����
  IMGDECOR       Left         ;   // ��������� ���������� ����� �������
  ULONG  LeftParm[1]  ;   // ��������� �� ����
  IMGDECOR       Rigth        ;   // ��������� ���������� ����� �������
  ULONG  RigthParm[1] ;   // ��������� �� ����
  IMGDECOR       First        ;   // ��������� ������� ����� ����� �������
  ULONG  FirstParm[1] ;   // ��������� �� ����
  IMGDECOR       Second       ;   // ��������� ������� ����� ����� �������
  ULONG  SecondParm[1];   // ��������� �� ����
}
  IMGDECORATE;

typedef struct IMGSECTION     // �������� ��������� ������ ��� (158)
{
  ULONG Length;       // ����� ���������� (������� IMGSECTION)
  ULONG Number;       // ����� �������(IMG_EMPTY, IMG_LINE, IMG_VECTOREX,
                              //               IMG_TRUETYPE)
  ULONG Base;         // ����� �������, ���������� �������
  ULONG Parm[1];      // ���������
}
  IMGSECTION;

typedef struct IMGDASH           // (158) �������� ��������� �����
{
  LONG    Length;            // ������ ����� ������ �������� �������,
  LONG    Count;             // ����� ��������� ������ (�������, ��������, ������)
  LONG    Last;              // ���������� ����� ������ (�� 0 �� Count-1),
                                 // ����������� ������ �������
  LONG    Border;            // ������������ ������� ������
  LONG    Reserve;           // ������
  IMGSECTION  Section[1];        // �������� ��������� ������
}
  IMGDASH;

typedef struct IMGLINESHIFT      // (159) C�������� �����
{
  LONG    Length;            // ������ ����� ������ �������� �������,
  LONG    Shift;             // ����������� � �������� ������
                                 // = 0 - ����� ����� ����� ��� �������
                                 // > 0 - ����� ������ �� ���, ����� �����
  IMGDECOR    Head;              // ��������� �����
  LONG    Parm[1];           // ��������� ����� �� �� ����
}
  IMGLINESHIFT;

typedef struct IMGVECTORTEXT     // (160) ��������� ������� ���������� (VT_TEXT)
{                                // (size = 68)
  IMGTEXT  Text     ;            // ��������� ������
  LONG Code     ;            // ��� ��������� �������, ��� ������ �����������
                                 // ������ ��� 0 ��� ����������� ������
  char     Title[32];            // ���������� �����
}
  IMGVECTORTEXT;

typedef struct IMGSQUAREGLASSCOLOR // (164) ��������� ��'��� - ������� ������
{                                  // (size = 12)
         LONG Color;               // ���� ����������� (IMGC_TRANSPARENT - ����������)
  LONG Bright;              // ������� ��������� ������� (+/- 100)
  LONG Contrast;            // ������� ��������� ��������� (+/- 100)
}
  IMGSQUAREGLASSCOLOR;


typedef struct IMGGRAPHICMARK      // (165) �������� ���� - ����������� �����������
{                                  // (size = 352)
  LONG Length   ;              // ������ ����� ������ �������� �������
  LONG Ident    ;              // ������������� ����������� = 0
  char     Name[256];              // ��� ����� �����������
  LONG Type     ;              // 1 - BMP, 2 - JPEG, 3 - Metafile
  LONG Height   ;              // �������� ����� ( ������, ������)
  LONG Width    ;              //
  LONG PosV     ;              // ����� �������� ����� �� ���������
  LONG PosH     ;              // � ����������� (�� ������ ���������
  LONG Shift        ;          // �������� ����
  IMGLINE  Contour      ;          // ��������� �������
  char     ContourFlag  ;          // ���� ������� �������
  char     ShadeFlag    ;          // ���� ������� ����
  char     Reserv[14]   ;          // ������
}
 IMGGRAPHICMARK;

typedef struct IMGHATCHSQUARESHIFT  // (166) ������������ ��������� �� ��������� ���������
{                                   // 04/04/08
  LONG Length;               // ������ ����� ������ �������� �������,
                                 // ������� ��������� ����� ���������
  LONG Angle ;               // ���� ������� ��������� � �������� (0,45,90,135,180,225,270,315)
                                 // ������ ������� ������� �� �����������
  LONG Step  ;               // ���������� ����� ����� ����� ���������
  LONG Number;               // ����� ������� ����� ��������� (IMGLINE, IMGDOT, IMGDASH)
  LONG Shift ;               // �������� ��� ������ ����� ���������
                                 // �����: ��������� ����� ���������
} IMGHATCHSQUARESHIFT;

typedef struct IMGPOLYGONGLASS   // (167) ��������� ��'��� - ������� ������ C ��������� ������������
{                                // (size = 16) (������ IMGSQUAREGLASSCOLOR)
         LONG Color;             // ���� ����������� (IMGC_TRANSPARENT - ����������, ����)
  LONG Bright;            // ������� ��������� ������� (+/- 100)
  LONG Contrast;          // ������� ��������� ��������� (+/- 100)
         LONG Transparency;      // ������� ������������ (�� 0 - �� ������������, �� 100 - �������� ����)
}
  IMGPOLYGONGLASS;


typedef struct IMGLINEGLASS      // (167) �������� ��'��� - ������� ������ C ��������� ������������
{                                // (size = 20) (������ IMGSQUAREGLASSCOLOR)
           LONG Color;           // ���� ����������� (IMGC_TRANSPARENT - ����������, ����)
  ULONG Thick;           // ������� �����
  LONG Bright;          // ������� ��������� ������� (+/- 100)
  LONG Contrast;        // ������� ��������� ��������� (+/- 100)
           LONG Transparency;    // ������� ������������ (�� 0 - �� ������������, �� 100 - �������� ����)
}
  IMGLINEGLASS;

typedef struct IMGLIBRARY        // (250) ��������� ��'����(������ ������������)
{
  LONG Length  ;             // ������ ����� ������ �������� �������
  LONG Code    ;             // ��� DLL (IML)
  LONG Index   ;             // ������ DLL � ������ ���������
  LONG Function;             // ��� �������
  IMGDRAW  Draw    ;             // ���������
}
  IMGLIBRARY;

typedef struct IMGDOUBLE         // (253) ��������� ��������� ���� DOUBLE
{
  double Value;
}
  IMGDOUBLE;

typedef struct IMGLONG           // (254) ��������� ��������� ���� LONG
{
  LONG Value;
}
  IMGLONG;

typedef struct IMGOBJECT         // (255) ����������/�������� ��'���
{                                //  � �������� ������ ��������������
                                 //      (size = 16)
  ULONG Color ;          // ���� ��������� ������� �� �����
                                 //  (IMGC_NOMARK - �� ��������)
  ULONG Incode;          // ���������� ��� �������
                                 //  (0 - ��������������� �� Excode � Local)
  ULONG Excode;          // ������� ��� �������
  ULONG Local ;          // ����������� ������� (IMGL_LINE, ...)

  // ��� ������� ���� PaintMapObject(...) Incode ���������������
  // �������������. ���� ��������� ������ �� �����, �� ������
  // ������ ��������� ����� ��������� ����.
}
  IMGOBJECT;



typedef struct IMGVECTORGRADIENT    // ��������������� ���������
{
  ULONG Color;        // ���� ����������� ������� (COLORREF)
  ULONG Left;         // ������� ���������� ��������� �����
  ULONG Right;        // ������� ���������� ��������� ������
  ULONG Bright;       // ������� ��������� ������� �������
}
  IMGVECTORGRADIENT;


//**********************************************************************
// ���������� ��������� ���������� ������������ (�������� �� IMGDRAW...)
//**********************************************************************

#define IMG_LINEDOT           130
#define IMG_DOUBLELINE        131
#define IMG_DOTDLINE          132
#define IMG_DOUBLEDOT         133
#define IMG_SHIFTLINEDOT      134
#define IMG_SQUARECROSS       136
#define IMG_MARK              137
#define IMG_SQUAREMARK        138
#define IMG_LEFTLINEDOT       145
#define IMG_DECORATELINE      146


typedef struct IMGLINEDOT        // (130) ������� �� �����
{                                //      (size = 24)
  IMGLINE Line;                  // ������ �����
  IMGDOT  Dot ;                  // ������� �����
}
  IMGLINEDOT;


typedef struct IMGDOUBLELINE     // (131) ����� �� �����
{                                //      (size = 16)
  IMGLINE OneLine;               // ������ �����
  IMGLINE TwoLine;               // ������� �����
}
  IMGDOUBLELINE;


typedef struct IMGDOTDLINE       // (132) ������� ����� �� ��������
{                                //      (size = 32)
  IMGDOT        Dot   ;          // ������ �����
  IMGDOUBLELINE Double;          // ������� �����
}
  IMGDOTDLINE;


typedef struct IMGDOUBLEDOT      // (133) ������� �������
{                                //      (size = 32)
  IMGDOT OneDot;                 // ������ �����
  IMGDOT TwoDot;                 // ������� �����
}
  IMGDOUBLEDOT;


typedef struct IMGSHIFTLINEDOT   // (134) �������, ��������� ������, �� �����
{                                //      (size = 24)
  IMGLINE Line;                  // ������ �����
  IMGDOT  Dot ;                  // ������� �����-�������
}
  IMGSHIFTLINEDOT;


typedef struct IMGSQUARECROSS    // (136) ������������ �������
{                                //      (size = 16)
  ULONG Color;           // ���� ��p������ (IMGC_TRANSPARENT - ����������)
  ULONG Kind ;           // ��� ��p������ (SC_HORIZONTAL, ...)
  ULONG Thick;           // ������a ��p��a
  ULONG Blank;           // ������a �p����a
}
  IMGSQUARECROSS;

typedef struct IMGMARK           // (137) �������� ��������� ��'���
{                                //      (size = 16 + 128 = 144)
  ULONG Color    ;       // ���� �����
  ULONG Size     ;       // ������ � �������� (��� ������)
  ULONG PosV     ;       // ����� �������� ����� PosV,PosH < Size
  ULONG PosH     ;       //  (��� IMGSQUAREMARK - ��� ����� >= Size
  unsigned char Bits[128];       // ��������� ����������� 32x32 � �������� ����
}
  IMGMARK;

typedef struct IMGSQUAREMARK     // (138) ��������� + ��������
{                                //      (size = 8 + 144 = 152)
  ULONG  Color   ;       // ���� ���� (IMGC_TRANSPARENT - ����������)
  unsigned short Kind    ;       // ��� ����� ���������� 4x4 (16 ���)
                                 //  (IMGK_REGULAR, ...)
  unsigned char  FullMark;       // ���� ����������
                                 //  0 - �� ���� �������
                                 //  1 - ������ ������� �������
  unsigned char  Weight  ;       // ��� �����, ������� �������   // 27/04/00
                                 //  0 - ������
                                 //  1 - ����������
  IMGMARK        Mark    ;       // �������� �����
}
  IMGSQUAREMARK;



typedef struct IMGLEFTLINEDOT    // (145) �������, ��������� �����, �� �����
{                                //      (size = 24)
  IMGLINE Line;                  // ������ �����
  IMGDOT  Dot ;                  // ������� �����-�������
}
  IMGLEFTLINEDOT;


typedef struct IMGDECHEAD        // ��������� ������������ ���������
{
  ULONG Length   ;       // ������ ����� ������ �������� �������
           LONG Distance ;       // ���������� ����� ������������ �������.
}
 IMGDECHEAD;
                                 // ������ �� ���������� � ������
                                 //
typedef struct IMGDECORATELINE   // (146) ����������� ��������
{
  IMGDECHEAD     Head        ;   // ���������
  IMGDECOR       Base        ;   // ��������� ������� �������
  ULONG  BaseParm[1] ;   // ��������� ������� �� ����
  IMGDECOR       First       ;   // ��������� ����������
  ULONG  FirstParm[1];   // ��������� �� ����
  IMGDECOR       End         ;   // ��������� ���������
  ULONG  EndParm[1]  ;   // ��������� �� ����
  IMGDECOR       Left        ;   // ��������� ������
  ULONG  LeftParm[1] ;   // ��������� �� ����
  IMGDECOR       Rigth       ;   // ��������� �������
  ULONG  RigthParm[1];   // ��������� �� ����
  IMGDECOR       Middle1     ;   // ��������� ������� ������������
  ULONG  Mid1Parm[1] ;   // ��������� �� ����
  IMGDECOR       Middle2     ;   // ��������� ������� ������������
  ULONG  Mid2Parm[1] ;   // ��������� �� ����
}
  IMGDECORATELINE;

                                 // ( ) ����������� ��������
typedef IMGDECORATELINE SCRDECORATELINE;
                                 // ����� ��������� ������ ���������
                                 // �������� ��������� �����

typedef struct IMGHATCHSQUARE    // (153) ������������ ���������
{
  LONG Length;               // ������ ����� ������ �������� �������,
                                 // ������� ��������� ����� ���������
  LONG Angle ;               // ���� ������� ��������� � �������� (0,45,90,135)
                                 // ������ ������� ������� �� �����������
  LONG Step  ;               // ���������� ����� ����� ����� ���������
  LONG Number;               // ����� ������� ��������� ����� (IMGLINE ��� IMGDOT)
                                 // �����: ��������� ����� ���������
} IMGHATCHSQUARE ;

typedef struct IMGNODE           // (167) ���� �� ������ (���� ����������)
{                                //      (size = 28)
  ULONG Color1;          // ���� ���������� (IMGC_TRANSPARENT - ����������)
  ULONG Color2;          // ���� �������
  ULONG Thick;           // ������� �����
  ULONG Radius1;         // ������ ��������� ����������
  ULONG Radius2;         // ������ ��������� ����������,
                                 // ��� �������� ������������� ����� ����� Radius1
  ULONG VertexCount;     // ����� ������� ������ (0 - ����������)
  ULONG Angle;           // ��������� ���� �������� ����� ������������
                                 // ������������ ���, �� ������� �������, � ��������
}
  IMGNODE;

#endif  // MAPGDI_H

