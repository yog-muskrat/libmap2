
#ifndef MAPDATA_H
#define MAPDATA_H

#include "mapversn.h"          // Current Version of Software

// ÓÔÌÂÚ· Ô˚È‚ÔÎ ÔÙÎÚ˘ÙÈÒ ÏÈÛÙ·
#define ERR_FILEMANY 0
#define ERR_MEMALL   1
#define ERR_DISKALL  2

#define ERR_STRMAP   3

#define ERR_OPENHDR  4
#define ERR_READHDR  5
#define ERR_WRITEHDR 6
#define ERR_STRHDR   7

#define ERR_OPENDAT  8
#define ERR_READDAT  9
#define ERR_WRITEDAT 10
#define ERR_STRDAT   11

#define ERR_OPENSEM  12
#define ERR_READSEM  13
#define ERR_WRITESEM 14
#define ERR_STRSEM   15

#ifndef TINYDATA

#define ERR_OPENDRW  20
#define ERR_READDRW  21
#define ERR_WRITEDRW 22
#define ERR_STRDRW   23

#define ERR_OPENVEC  24
#define ERR_READVEC  25
#define ERR_WRITEVEC 26
#define ERR_STRVEC   27

#endif

#ifdef GEODATA
 #include "mapgeosp.h"         // for GeoSp 
#else

#ifndef MAPCREAT_H
  #include "mapcreat.h"        // Passport Records Description
#endif

#define  PSPIDENT  0x7F7F7F7F

// Èƒ≈Œ‘…∆…À¡‘œ“ ∆¡ Ã¡ –¡”–œ“‘¡ “¡ œŒ¡ ƒÃ— œ‘À“Ÿ‘œ«œ … ⁄¡À“Ÿ‘Ÿ» ∆œ“Õ¡‘œ◊
 #ifdef FORMAT_M
   #define LABEL_PSP 0x004D5350L   // PSM0    
 #else
  #ifdef FORMAT_T
    #define LABEL_PSP 0x00545350L  // PST0    
  #else
   #ifdef FORMAT_U
    #define LABEL_PSP 0x00555350L  // PSU0    
   #else
    #ifdef FORMAT_D
     #define LABEL_PSP 0x00445350L  // PSD0    
    #else
     #ifdef FORMAT_N
      #define LABEL_PSP 0x004E5350L  // PSN0   
     #else
     #ifdef FORMAT_2
      #define LABEL_PSP 0x00325350L  // PS20   
     #else
      #define LABEL_PSP 0x00505350L  // PSP0
     #endif
     #endif
    #endif
   #endif
  #endif
 #endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++  "VECTOR MAP PASSPORT" +++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Comment :
//
// ---------------------------------------------------------
//  PASSPORT HEAD
// ---------------------------------------------------------

typedef struct PASSPORTHEAD       // Passport Head
{
  int IsSite() { return (Data.FlagRealPlace != 0); }

  ULONG Label;        // Passport identifier (0x7F7F7F7F)
  ULONG Length;       // Record length

#if defined(FORMAT_U) || defined(FORMAT_N) 
  ULONG Series;       // Data series
  ULONG Version;      // Structure version   (0x00000700)
#else
  ULONG Version;      // Structure version   (0x00000700)
  ULONG Series;       // Data series
#endif

#if defined(FORMAT_T) || defined(FORMAT_2)  
  ULONG Mode;         // Update data mode
  ULONG Count;        // Count of sheet
#else
  ULONG Count;        // Count of sheet
  ULONG Mode;         // Update data mode
#endif

  unsigned char     ScaleType;    // Number of scale table
  unsigned char     CharType;     // Number of string table
                                  //  (0 - ANSI, 1 - KOI8)
  unsigned char     OrderFlag;    // View by order
  unsigned char   PrecisionFlag;  // Double precision flag
                                  // (0 - FLOAT, 1 - DOUBLE, 2 - METRE) 
  unsigned char     Precision;    // (0 - MAX, 2 - centimeters, 3 - millimeters) 
  unsigned char     Free2[3];     // Must be zero

#if defined(FORMAT_U) || defined(FORMAT_2)  
  double            MapY;         // Map "zero position" by Y
  double            MapX;         // Map "zero position" by X
#else
  double            MapX;         // Map "zero position" by X
  double            MapY;         // Map "zero position" by Y
#endif

#ifndef TINYDATA
  double            XMin;         // Map X min (Down)
  double            YMin;         // Map Y min (Left)
  double            XMax;         // Map X max (Up)
  double            YMax;         // Map Y max (Right)
#else
 LONG          XMin;         // Map X min (Down)
 LONG          YMin;         // Map Y min (Left)
 LONG          XMax;         // Map X max (Up)
 LONG          YMax;         // Map Y max (Right)
#endif

#if defined(FORMAT_D) || defined(FORMAT_N) 
  char          RscName[260];     // Classifier file name
  ULONG RscStyle;     // Classifier file mode

  MAPREGISTEREX     Data;         // Passport descriptor (align by 8)
#else
  MAPREGISTEREX     Data;         // Passport descriptor (align by 8)

  char          RscName[260];     // Classifier file name
  ULONG RscStyle;     // Classifier file mode
#endif

#ifndef TINYDATA
  char          GdxName[260];     // Group file name
  ULONG GdxFlag ;     // Group file flag

  ULONG TableOffset;  // Offset for excode table
  ULONG TableLength;  // Length of excode table

  ULONG Reserv[6];    // Must be zero
#endif
}
  PASSPORTHEAD;

// ---------------------------------------------------------
//  MAP SHEET DESCRIPTION
// ---------------------------------------------------------


#ifndef TINYDATA

typedef struct SHEETDESC          // Map Sheet Description
{
  int CheckErrorNumber(int number)
  {
    return ((Errors & (1 << number)) != 0);
  }

  void SetErrorNumber(int number)
  {
    Errors |= (1 << number);
  }

  ULONG Label;        // Sheet descriptor identifier (0x7F7F7F7F)

#ifdef FORMAT_2                   
  ULONG SheetNumber;  // Sheet number in map
  ULONG FrameNumber;  // Sheet frame object number
  ULONG Count;        // Sheet objects count
#else
  ULONG Count;        // Sheet objects count
  ULONG SheetNumber;  // Sheet number in map
  ULONG FrameNumber;  // Sheet frame object number
#endif

#if defined(FORMAT_M) || defined(FORMAT_T) || defined(FORMAT_N)
  DFRAME            Border;       // Sheet border  (discretes)

  double            XMin;         // Sheet X min (Down) (meters)
  double            YMin;         // Sheet Y min (Left)
  double            XMax;         // Sheet X max (Up)
  double            YMax;         // Sheet Y max (Right)

  LISTREGISTER      Data;         // Sheet descriptor    (align by 8)

  DOUBLEPOINT       ViewPosition; // View position X (down), Y (left)
#else
  double            XMin;         // Sheet X min (Down) (meters)
  double            YMin;         // Sheet Y min (Left)
  double            XMax;         // Sheet X max (Up)
  double            YMax;         // Sheet Y max (Right)

  DFRAME            Border;       // Sheet border  (discretes)

  DOUBLEPOINT       ViewPosition; // View position X (down), Y (left)

  LISTREGISTER      Data;         // Sheet descriptor    (align by 8)
#endif
  char              Date[12];     // Create sheet files date
  ULONG Errors;       // Sheet errors flags

#if defined(FORMAT_U) || defined(FORMAT_D) || defined(FORMAT_2)  
  char         SemnName[264];     // Semantic File Name
  char         DrawName[264];     // Image File Name
  char         HeadName[264];     // Head File Name
  char         DataName[264];     // Metric File Name
#else
  char         HeadName[264];     // Head File Name
  char         DataName[264];     // Metric File Name
  char         SemnName[264];     // Semantic File Name
  char         DrawName[264];     // Image File Name
#endif

  unsigned char     IsSorted;     // Sorted flag       
  unsigned char     FileFlag;     // Create File flag  
                                  // 1 - HDR, 2 - DAT, 4 - SEM, 8 - DRW
  unsigned char     Reserv1[2];   // Must be zero
  ULONG Reserv2[3];   // Must be zero
}
  SHEETDESC;

#else

typedef struct SHEETDESC          // Map Sheet Description
{
  int CheckErrorNumber(int number)
  {
    return ((Errors & (1 << number)) != 0);
  }

  void SetErrorNumber(int number)
  {
    Errors |= (1 << number); 
  }

  ULONG Label;        // Sheet descriptor identifier (0x7F7F7F7F)
  ULONG Count;        // Sheet objects count
  ULONG SheetNumber;  // Sheet number in map
  ULONG FrameNumber;  // Sheet frame object number

 LONG           XMin;        // Sheet X min (Down)
 LONG           YMin;        // Sheet Y min (Left)
 LONG           XMax;        // Sheet X max (Up)
 LONG           YMax;        // Sheet Y max (Right)

  DFRAME            Border;       // Sheet border  (discretes)

  DOUBLEPOINT       ViewPosition; // View position X (down), Y (left)

  LISTREGISTER      Data;         // Sheet descriptor    (align by 8)

  char         HeadName[16];      // Head File Name
  char         DataName[16];      // Metric File Name
  char         SemnName[16];      // Semantic File Name
  char         DrawName[16];      // Image File Name

  ULONG Semantic;    // Semantic records offset or zero
  unsigned short int Errors;      // Sheet errors flags
  unsigned short int Reserv;      // Must be zero
}
  SHEETDESC;

#endif   // TINYDATA

#define FLAG_HDR   1
#define FLAG_DAT   2
#define FLAG_SEM   4
#define FLAG_DRW   8
#define FLAG_VEC  16              

// ---------------------------------------------------------
//  ZERO HEAD
// ---------------------------------------------------------

#ifdef TINYDATA

typedef struct FVZER              // Zero head  (size = 16)
{
 ULONG Label      ;  // Zero head label
 unsigned short int Count      ;  // Objects count
 unsigned short int SquareLast ;  // Number of last polygon object
 unsigned short int LineLast   ;  // Number of last line object
 unsigned short int PointLast  ;  // Number of last point object
 unsigned short int Limit      ;  // Limit of objects count
 unsigned short int Version    ;  // Structure version (0x0700)
}
  FVZER;

#else

typedef struct FVZER              // Zero head  (size = 48)
{
 ULONG Label      ;  // Zero head label
 ULONG Count      ;  // Objects count
#if defined(FORMAT_T) || defined(FORMAT_D)          
 ULONG Last       ;  // Last object number
 ULONG First      ;  // First object number
#else
 ULONG First      ;  // First object number
 ULONG Last       ;  // Last object number
#endif
 ULONG FreeKey    ;  // Free object key (Last key + 1)
 ULONG SquareLast ;  // Number of last polygon object
 ULONG LineLast   ;  // Number of last line object
 ULONG PointLast  ;  // Number of last point object
#if defined(FORMAT_N) || defined(FORMAT_2)        
 ULONG VectorLast ;  // Number of last vector object
 ULONG TitleLast  ;  // Number of last text object
#else
 ULONG TitleLast  ;  // Number of last text object
 ULONG VectorLast ;  // Number of last vector object
#endif
 ULONG Reserv     ;  // Must be zero
 unsigned short int Version    ;  // Structure version (0x0700)
 unsigned short int Series     ;  // Structure series
}
  FVZER;
#endif

typedef struct FVZER TZeroHead;

// ---------------------------------------------------------
//  OBJECT HEAD
// ---------------------------------------------------------

typedef struct _DLLCLASS FVSPR    // Object head (size = 48)
{
 FVSPR() { memset(this, 0, sizeof(FVSPR)); }          

 ULONG Next      ;   // Number of next object
 ULONG Back      ;   // Number of previous object
 unsigned char      Local     ;   // Local number 4 bits!
 unsigned char      Segment   ;   // Layer number
 unsigned short int Code      ;   // Internal object code

#if defined(FORMAT_T) || defined(FORMAT_2) 
         LONG X2        ;   // X max (up)
         LONG Y2        ;   // Y max (right)
         LONG X1        ;   // X min (down)
         LONG Y1        ;   // Y min (left)

#else
         LONG X1        ;   // X min (down)
         LONG Y1        ;   // Y min (left)
         LONG X2        ;   // X max (up)
         LONG Y2        ;   // Y max (right)
#endif

 ULONG BaseKey   ;   // Object identifier
 unsigned short int Group     ;   // Object group number
#if defined(FORMAT_U) || defined(FORMAT_N)          
 unsigned short int Bot      :4;  // Bottom scale level for view
 unsigned short int Top      :4;  // Top scale level for view (15-top)
 unsigned short int Cancel   :1;  // Delete flag
 unsigned short int Extloc   :1;  // Local flag
 unsigned short int IsBotTop :1;  // Set scale level flag
 unsigned short int Vector   :1;  // 3D-vector flag             
 unsigned short int PressFlag:1;  // Press flag                 
 unsigned short int Dimension:1;  // Data dimension flag
 unsigned short int ScaleFlag:1;  // Scaling flag
 unsigned short int ExtSem   :1;  // Service semantic flag (31001,...)
#else
 unsigned short int Cancel   :1;  // Delete flag
 unsigned short int Extloc   :1;  // Local flag
 unsigned short int IsBotTop :1;  // Set scale level flag
 unsigned short int Vector   :1;  // 3D-vector flag             
 unsigned short int PressFlag:1;  // Press flag                 
 unsigned short int Dimension:1;  // Data dimension flag
 unsigned short int ScaleFlag:1;  // Scaling flag
 unsigned short int ExtSem   :1;  // Service semantic flag (31001,...)
 unsigned short int Bot      :4;  // Bottom scale level for view
 unsigned short int Top      :4;  // Top scale level for view (15-top)
#endif

#if defined(FORMAT_M) || defined(FORMAT_D)          
 ULONG Metric    ;   // Offset of object metric
 ULONG Semantic  ;   // Offset of object semantic
 ULONG Graphic   ;   // Offset of object image
#else
#if defined(FORMAT_U) || defined(FORMAT_2)    
 ULONG Semantic  ;   // Offset of object semantic
 ULONG Graphic   ;   // Offset of object image
 ULONG Metric    ;   // Offset of object metric
#else
#ifdef FORMAT_N                   
 ULONG Graphic   ;   // Offset of object image
 ULONG Semantic  ;   // Offset of object semantic
 ULONG Metric    ;   // Offset of object metric
#else
 ULONG Semantic  ;   // Offset of object semantic
 ULONG Metric    ;   // Offset of object metric
 ULONG Graphic   ;   // Offset of object image
#endif
#endif
#endif
}
  FVSPR;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  ˙·ÁÔÏÔ˜ÔÎ Ô‚'ÂÎÙ· ¸ÏÂÎÙÚÔÓÓÔÍ Î·ÚÙ˘  +++++++++++++
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
  ULONG Amount; // Points count              
}
  LONGDESC;

typedef LONGDESC SHORTDESC;

#ifdef TINYDATA

typedef struct LONGMETRIC       // OBJECT METRIC HEAD
{
  short int          Ident;     // Record identifier  0x7FFF
  unsigned short int Length;    // Record length
  unsigned short int Part;      // Subject count
  LONGDESC Desc;                // Subject descriptor
}
  LONGMETRIC;

#else

typedef struct LONGMETRIC       // OBJECT METRIC HEAD
{
 LONG          Ident;     // Record identifier
 LONG          Length;    // Record length
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

#endif

typedef LONGMETRIC SHORTMETRIC;

#endif // !GEODESK

#endif // MAPDATA_H

