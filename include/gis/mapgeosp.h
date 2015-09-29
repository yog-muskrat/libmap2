
#ifndef MAPGEOSP_H
#define MAPGEOSP_H


#ifdef GEODESK

#ifndef MAPCREAT_H
  #include "mapcreat.h"        // Passport Records Description
#endif

#define  PSPIDENT  0x7F7F7F7F

// éÄÅÎÔÉÆÉËÁÔÏÒ ÆÁÊÌÁ ÐÁÓÐÏÒÔÁ ÒÁÊÏÎÁ
// #define LABEL_PSP 0x50535000L  // PSP0    

#define LABEL_PSP 0x00505350L  // PSP0

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++  "VECTOR MAP PASSPORT" +++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Comment :
//
//  NUMBERTURN must be defined for MIPS, SPARC, etc.
//  All records must be aligned by 8 !
//  TINYDATA must be defined for compact data model

// ---------------------------------------------------------
//  PASSPORT HEAD
// ---------------------------------------------------------

typedef struct PASSPORTHEAD       // Passport Head
{
  unsigned long int Label;        // Passport identifier (0x7F7F7F7F)
  unsigned long int Length;       // Record length

  unsigned long int Series;       // Data series   GeoSp  
  unsigned long int Version;      // Structure version   (0x00000700)

  unsigned long int Count;        // Count of sheet
  unsigned long int Mode;         // Update data mode

  unsigned char     ScaleType;    // Number of scale table
  unsigned char     CharType;     // Number of string table
                                  //  (0 - ANSI, 1 - KOI8)
  unsigned char     OrderFlag;    // View by order
  unsigned char   PrecisionFlag;  // Double precision flag

  unsigned char     Precision;    // (0 - MAX, 2 - centimeters, 3 - millimeters) 
  unsigned char     Free2[3];     // Must be zero

  double            MapX;         // Map "zero position" by X
  double            MapY;         // Map "zero position" by Y

  double            XMax;         // Map X max (Up)      GeoSp
  double            YMax;         // Map Y max (Right)
  double            XMin;         // Map X min (Down)
  double            YMin;         // Map Y min (Left)

  MAPREGISTEREX     Data;         // Passport descriptor (align by 8)

  unsigned long int RscStyle;     // Classifier file mode  GeoSp
  char          RscName[260];     // Classifier file name

  char          GdxName[260];     // Group file name
  unsigned long int GdxFlag ;     // Group file flag

  unsigned long int TableOffset;  // Offset for excode table
  unsigned long int TableLength;  // Length of excode table

  unsigned long int Reserv[6];    // Must be zero
}
  PASSPORTHEAD;

// ---------------------------------------------------------
//  MAP SHEET DESCRIPTION
// ---------------------------------------------------------


typedef struct SHEETDESC          // Map Sheet Description
{
  unsigned long int Label;        // Sheet descriptor identifier (0x7F7F7F7F)
  unsigned long int Count;        // Sheet objects count
  unsigned long int SheetNumber;  // Sheet number in map
  unsigned long int FrameNumber;  // Sheet frame object number

  DFRAME            Border;       // Sheet border  (discretes)  GeoSp

  double            XMin;         // Sheet X min (Down) (meters)
  double            YMin;         // Sheet Y min (Left)
  double            XMax;         // Sheet X max (Up)
  double            YMax;         // Sheet Y max (Right)

  DOUBLEPOINT       ViewPosition; // View position X (down), Y (left)

  LISTREGISTER      Data;         // Sheet descriptor    (align by 8)

  char              Date[12];     // Create sheet files date
  unsigned long int Errors;       // Sheet errors flags

  char         SemnName[264];     // Semantic File Name    GeoSp
  char         DrawName[264];     // Image File Name
  char         HeadName[264];     // Head File Name
  char         DataName[264];     // Metric File Name

  unsigned char     IsSorted;     // Sorted flag       
  unsigned char     FileFlag;     // Create File flag  
                                  // 1 - HDR, 2 - DAT, 4 - SEM, 8 - DRW
  unsigned char     Reserv1[2];   // Must be zero
  unsigned long int Reserv2[3];   // Must be zero
}
  SHEETDESC;


#define FLAG_HDR   1
#define FLAG_DAT   2
#define FLAG_SEM   4
#define FLAG_DRW   8
#define FLAG_VEC  16              

// ---------------------------------------------------------
//  ZERO HEAD
// ---------------------------------------------------------

typedef struct FVZER              // Zero head  (size = 48)
{
 unsigned long  int Label      ;  // Zero head label
 unsigned long  int Count      ;  // Objects count
 unsigned long  int Last       ;  // Last object number    GeoSp
 unsigned long  int First      ;  // First object number
 unsigned long  int FreeKey    ;  // Free object key (Last key + 1)
 unsigned long  int SquareLast ;  // Number of last polygon object
 unsigned long  int LineLast   ;  // Number of last line object
 unsigned long  int PointLast  ;  // Number of last point object
 unsigned long  int TitleLast  ;  // Number of last text object
 unsigned long  int VectorLast ;  // Number of last vector object
 unsigned long  int Reserv     ;  // Must be zero
 unsigned short int Series     ;  // Structure series      GeoSp
 unsigned short int Version    ;  // Structure version (0x0700)
}
  FVZER;

typedef struct FVZER TZeroHead;

// ---------------------------------------------------------
//  OBJECT HEAD
// ---------------------------------------------------------

typedef struct FVSPR              // Object head (size = 48)
{
 unsigned long  int Next      ;   // Number of next object
 unsigned long  int Back      ;   // Number of previous object

 unsigned short int Local   :4;   // Local number
 unsigned short int BFree   :4;   // Must be zero
 unsigned short int Segment :8;   // Layer number
 unsigned short int Code      ;   // Internal object code

 unsigned long  int BaseKey   ;   // Object identifier    GeoSp

          long  int X1        ;   // X min (down)
          long  int Y1        ;   // Y min (left)
          long  int X2        ;   // X max (up)
          long  int Y2        ;   // Y max (right)

 unsigned short int Group     ;   // Object group number
 unsigned short int Cancel   :1;  // Delete flag
 unsigned short int Extloc   :1;  // Local flag
 unsigned short int IsBotTop :1;  // Set scale level flag
 unsigned short int PressFlag:1;  // Press flag                 
 unsigned short int Vector   :1;  // 3D-vector flag             
 unsigned short int Dimension:1;  // Data dimension flag
 unsigned short int ScaleFlag:1;  // Scaling flag
 unsigned short int ExtSem   :1;  // Service semantic flag (31001,...)
 unsigned short int Bot      :4;  // Bottom scale level for view
 unsigned short int Top      :4;  // Top scale level for view (15-top)

 unsigned long  int Metric    ;   // Offset of object metric   GeoSp
 unsigned long  int Semantic  ;   // Offset of object semantic
 unsigned long  int Graphic   ;   // Offset of object image
}
  FVSPR;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  úáçïìï÷ïë ïâ'åëôá üìåëôòïîîïê ëáòôù  +++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef struct FVSPR TObjectHead;


// --------------------------------------------------------
// ********************   OBJECT METRIC   *****************
// --------------------------------------------------------
//
//  RECORD IDENTIFIER
//  RECORD LENGTH
//  SUBJECT COUNT
// -----------------------  REPEAT --------------------------
//  SUBJECT NUMBER
//  POINTS COUNT
//  COORDINATES
//  IF METRIC WITH TEXT :
//                        TEXT LENGTH  (1 BYTE),
//                        TEXT         (ANSI)
//                        0x00         (1 BYTE)
// ----------------------------------------------------------

// Record identifier (SHORT)
#define SHORTIDENT  IDSHORT2

// Record identifier (FLOAT)
#define FLOATIDENT  IDFLOAT2

// Record identifier (LONG)
#define LONGIDENT   IDLONG2

// Record identifier (DOUBLE)
#define DOUBLEIDENT IDDOUBLE2

// Record identifier(SHORT 3D)
#define SHORTIDENT3 IDSHORT3

// Record identifier (FLOAT 3D)
#define FLOATIDENT3 IDFLOAT3

// Record identifier (DOUBLE 3D)
#define DOUBLEIDENT3 IDDOUBLE3

typedef struct OLDDESC       // SUBJECT DESCRIPTOR
{
  unsigned short int Key  ;  // Points count
  unsigned short int Count;  // Points count            
}
  OLDDESC;

typedef struct LONGDESC      // SUBJECT DESCRIPTOR
{
  unsigned long  int Amount; // Points count              
}
  LONGDESC;

typedef LONGDESC SHORTDESC;

typedef struct LONGMETRIC       // OBJECT METRIC HEAD
{
  long  int          Ident;     // Record identifier
  long  int          Length;    // Record length
  unsigned short int Part;      // Subject count
  unsigned short int Control;   // Flags
  LONGDESC Desc;                // Subject descriptor
}
  LONGMETRIC;

// Value list for field "Control"
#define METRIC_LONGCOUNT         1 // Points count > 65536 in "Amount" field
#define METRIC_SMOOTHSPLINE      2 // Build "smooth" spline for view
#define METRIC_POINTSPLINE       4 // Build "round" spline (include all points)
#define METRIC_RELATIVEH         8 // In H - relative height                      
#define METRIC_UNICODETEXT      16 // Unicode text                                

typedef LONGMETRIC SHORTMETRIC;

#endif // GEODESK

#endif // MAPGEOSP_H

