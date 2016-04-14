     
#if !defined(MAPSYST_H) 
#define MAPSYST_H

#define  LINUXAPI     // Тип системного интерфейса Linux  

#ifndef _LARGEFILE64_SOURCE
 #define _LARGEFILE64_SOURCE  //Additional functionality from LFS for large files. //NIITP
#endif

#define LP64MODEL

#ifdef LINUXAPI
  #define RISCCPU       // Выравнивание переменных и структур
#ifdef OC2000             
  #define MINIDATA      // IDSHORT2,IDDOUBLE2,IDDOUBLE3
#endif
  #define HIDEMTL
  #define HIDETIN       
//  #define HIDEMTQ       
  #define HIDEMETAFILE
  #define HIDEMTR3D
  #define HIDE3D        
  #define HIDEGDX       
  #define HIDEIMAGEDIT  
  #define HIDETIN       
//  #define HIDEUNION     
  #define WINAPI
  #define TURNRASTERTEXT    
#ifndef __cplusplus         
  #define HIDETRY
  #define HIDESET       
//  #define HIDEIML         
#endif
  #define HIDEPAINTSTEP  

  #define HIDESECTION

  #include <stddef.h>
  #include <stdint.h> 
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <fcntl.h>
  #include <time.h>
  #include <stdlib.h>
  #include <ctype.h>
  #include <errno.h>
  #include <string.h>  
#ifndef OC2000         
  #include <dlfcn.h>
  #include <sys/vfs.h> 
#else
  #include <version.h> 
#endif
#if (!defined(WATCOM) && !defined(OC2000))    
  #include <sys/vfs.h>
#endif  
#ifndef HIDESECTION                           
  #include <pthread.h>
#endif
  #include <iconv.h>                          
  
  typedef unsigned char BYTE;
  typedef struct PALETTEENTRY
  {
    BYTE peRed;
    BYTE peGreen;
    BYTE peBlue;
    BYTE peFlags;
  }
  PALETTEENTRY;

  typedef intptr_t HANDLE;


#ifdef LP64MODEL
//Типы, используемые для работы с данными

  typedef unsigned int UINT; //4 байта
  typedef int LONG; //4 байта 
  typedef unsigned int ULONG; //4 байта 
  typedef int COLORREF;
                     
  typedef unsigned short int WORD;
  typedef unsigned int DWORD;

  typedef HANDLE HBITMAP;
  typedef HANDLE HGLOBAL;
  typedef HANDLE HPALETTE;
  typedef HANDLE HDC;
  typedef HANDLE HPEN;
  typedef LONG XYTYPE;            
  typedef long int HWND;
  typedef long int HINSTANCE;
  typedef long int LPARAM;
  typedef long int WPARAM;            
  typedef long int LRESULT;
  typedef long int HMENU;             
  typedef void *   LPVOID;            
  typedef char *   LPTSTR;
  typedef char     WCHAR;             
#ifndef TCHAR
  typedef char TCHAR;
  #define _TEXT(x)   x                
#endif

#else //not LP64MODEL (usual ILP32)

  typedef unsigned int UINT;
  typedef long int LONG; 
  typedef unsigned long int ULONG;
  typedef long int COLORREF;
#ifndef OC2000                      
  typedef unsigned short int WORD;
  typedef unsigned long DWORD;
#else
#if (OS_VERSION > 206)              
  typedef unsigned short int WORD;
  typedef unsigned long DWORD;
#endif
#endif
  typedef HANDLE HBITMAP;
  typedef HANDLE HGLOBAL;
  typedef HANDLE HPALETTE;
  typedef HANDLE HDC;
  typedef HANDLE HPEN;
  typedef long int XYTYPE;            
  typedef long int HWND;
  typedef long int HINSTANCE;
  typedef long int LPARAM;
  typedef long int WPARAM;            
  typedef long int LRESULT;
  typedef long int HMENU;             
  typedef void *   LPVOID;            
  typedef char *   LPTSTR;
  typedef char     WCHAR;             
#ifndef TCHAR
  typedef char TCHAR;
  #define _TEXT(x)   x                
#endif
#endif //LP64MODEL

#if (!defined(WATCOM) && !defined(OC2000)) 
  #define strnicmp   strncasecmp
  #define stricmp    strcasecmp
  #define strcmpi    strcasecmp      

//#if defined(CROSS_MIPS) && !defined(NUMBERTURN) 
#if defined(CROSS_MIPS) 
  #define sinl sin
  #define cosl cos
#endif
#else
  #define strnicmp   strncmp
  #define stricmp    strcmp
  #define strcmpi    strcmp      
  #define sinl       sin
  #define cosl       cos
#endif

#ifndef FALSE                        
  #define FALSE      0
  #define TRUE       1
#endif

  #define PASCAL __stdcall
  #define WINAPI
  #define far        
  #define _import    
  #define near       
  #define _export    
  
//Из stdint.h
  #define UINT32_MAX   (4294967295U)

  // Данные макросы делают операции с цветом независимо от глубины цвета экрана
  // есть класс CELLColor. Реализации его методов в соответствующей 
  // глубине цвета библиотеке
  #define RGB(r,g,b) ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16))) 
  #define PALETTERGB(r,g,b)   (0x02000000 | RGB(r,g,b))  
  #define PALETTEINDEX(i)     ((COLORREF)(0x01000000 | (DWORD)(WORD)(i)))
  #define GetRValue(rgb)   ((BYTE) (rgb))                 
  #define GetGValue(rgb)   ((BYTE) (((WORD) (rgb)) >> 8)) 
  #define GetBValue(rgb)   ((BYTE) ((rgb) >> 16))         

  #define ERROR_ALREADY_EXISTS 183L
  #define ERROR_FILE_NOT_FOUND 2L
  #define LF_FACESIZE 32

  #define FILE_SHARE_READ S_IRUSR|S_IRGRP|S_IROTH
  #define FILE_SHARE_WRITE S_IWUSR|S_IWGRP|S_IWOTH
//  #define GENERIC_READ O_RDONLY
  #define GENERIC_READ  0x100000              
//  #define GENERIC_WRITE O_RDWR
  #define GENERIC_READWRITE O_RDWR
  #define GENERIC_WRITE O_WRONLY              
  #define OPEN_ALWAYS O_CREAT
  #define CREATE_ALWAYS O_CREAT|O_TRUNC
  #define OPEN_EXISTING O_EXCL
  #define CREAT_NEW O_CREAT|O_EXCL
  #define TRUNCATE_EXISTING O_CREAT|O_EXCL|O_TRUNC
  #define FILE_BEGIN SEEK_SET
  #define FILE_CURRENT SEEK_CUR
  #define FILE_END SEEK_END
  #define MAX_PATH 260                     
  #define FILE_ATTRIBUTE_READONLY S_IRUSR|S_IRGRP|S_IROTH
  #define FILE_ATTRIBUTE_ARCHIVE S_IWUSR|S_IWGRP|S_IWOTH|S_IRUSR|S_IRGRP|S_IROTH
  #define FILE_ATTRIBUTE_HIDDEN S_IRUSR|S_IRGRP|S_IROTH|S_IWUSR|S_IWGRP|S_IWOTH|S_IRUSR
  #define FILE_ATTRIBUTE_NORMAL S_IWUSR|S_IWGRP|S_IWOTH|S_IRUSR|S_IRGRP|S_IROTH
  #define FILE_ATTRIBUTE_OFFLINE S_IWUSR|S_IWGRP|S_IWOTH|S_IRUSR|S_IRGRP|S_IROTH
  #define FILE_ATTRIBUTE_SYSTEM S_IRUSR|S_IRGRP|S_IROTH|S_IWUSR|S_IWGRP|S_IWOTH|S_IRUSR
  #define FILE_ATTRIBUTE_TEMPORARY S_IWUSR|S_IWGRP|S_IWOTH|S_IRUSR|S_IRGRP|S_IROTH

  #define OFN_FILEMUSTEXIST       0x00001000        
  #define OFN_PATHMUSTEXIST       0x00000800
  #define OFN_CREATEPROMPT        0x00002000
  #define OFN_OVERWRITEPROMPT     0x00000002
  #define OFN_ALLOWMULTISELECT    0x00000200        
  #define OFN_HIDEREADONLY        0x00000004        
  #define OFN_NOREADONLYRETURN    0x00008000
  // Маски клавиш (полное соотвествие WIN32)        
  #define MK_LBUTTON                  0x0001
  #define MK_RBUTTON                  0x0002
  #define MK_SHIFT                    0x0004
  #define MK_CONTROL                  0x0008
  #define MK_MBUTTON                  0x0010
  // Коды клавиш (XWindow)
  #define VK_F10                      0xFFC7             // XK_F10
  #define VK_ESCAPE                   0xFF1B             // XK_Escape
  #define VK_TAB                      0xFF09             // XK_Tab
  #define VK_HOME                     0xFF50             // XK_Home
  #define VK_PRIOR                    0xFF55             // XK_Prior
  #define VK_NEXT                     0xFF56             // XK_Next
  #define VK_END                      0xFF57             // XK_End
  #define VK_LEFT                     0xFF51             // XK_Left
  #define VK_UP                       0xFF52             // XK_Up
  #define VK_RIGHT                    0xFF53             // XK_Right
  #define VK_DOWN                     0xFF54             // XK_Down
  #define VK_SHIFT                    0xFFE1             // XK_Shift_L      
  #define VK_CONTROL                  0xFFE3             // XK_Control_L
  #define VK_RETURN                   0xFF0D             // XK_Return     
  #define VK_F1                       0xFFBE             // XK_F1
  #define VK_LBUTTON                  0xFEE0             // XK_Pointer_Left 
  #define VK_RBUTTON                  0xFEE1             // XK_Pointer_Right
  #define VK_SPACE                    0x020              //  XK_space      
  #define VK_MENU                     0xFF67             //  XK_Menu
  #define VK_BACK                     0xFF08             // XK_BackSpace // back space, back char   
  #define VK_INSERT                   0xFF63             // XK_Insert      Insert, insert here    WIN32 Ins 45
  #define VK_ADD                      0xFFAB             // XK_KP_Add
  #define VK_DELETE                   0xFFFF             // XK_Delete  Delete, rubout WIN32 Del  0x2e
                                                         // XK_KP_Delete 0xFF9F не добавлена
  #define VK_SUBTRACT                 0xFFAD             // XK_KP_Subtract   WIN32 109

  #define MB_OK                       0x00000000L 
  #define MB_ICONHAND                 0x00000010L
  #define MB_OKCANCEL                 0x00000001L
  #define MB_YESNOCANCEL              0x00000003L
  #define MB_YESNO                    0x00000004L
  #define MB_ABORTRETRYIGNORE         0x00000002L
  #define MB_RETRYCANCEL              0x00000005L

  #define MB_ICONQUESTION             0x00000020L
  #define MB_ICONEXCLAMATION          0x00000030L
  #define MB_ICONWARNING              MB_ICONEXCLAMATION
  #define MB_ICONERROR                MB_ICONHAND
  #define MB_ICONASTERISK             0x00000040L             
  #define MB_ICONINFORMATION          MB_ICONASTERISK
  #define MB_ICONSTOP                 MB_ICONHAND
  #define MB_TASKMODAL                0x00002000L
  #define IDOK                        1
  #define IDCANCEL                    2
  #define IDABORT                     3
  #define IDRETRY                     4
  #define IDIGNORE                    5
  #define IDYES                       6
  #define IDNO                        7
  #define IDCLOSE                     8
  #define IDHELP                      9

  #define DT_PLOTTER          0   // Vector plotter
  #define DT_RASDISPLAY       1   // Raster display
  #define DT_RASPRINTER       2   // Raster printer

  #define R2_COPYPEN          0x3 // GXcopy   - src  для XWindow
//  #define R2_NOT              0x6 // GXxor      //0xa // GXinvert - (NOT dst) для XWindow 
  #define R2_NOT              0xa // GXinvert - (NOT dst) для XWindow 
  #define R2_NOTXORPEN        0x9 // GXequiv    - (NOT src) XOR dst  для XWindow   
  #define R2_XORPEN           0x6 // GXxor    - src XOR dst для XWindow            

  #define OEM_CHARSET         255
  #define RUSSIAN_CHARSET     204 
  #define BI_RGB              0L

  #define TA_LEFT             0     
  #define TA_RIGHT            2
  #define TA_CENTER           6

  #define TA_TOP              0
  #define TA_BOTTOM           8
  #define TA_BASELINE         24

  #define MF_SEPARATOR        0                                         
  #define MF_STRING           1

  // Стандартный вид курсора            // Коды XWindow:                
  #define IDC_ARROW    (char *)68L      // XC_left_ptr
  #define IDC_ICON     IDC_ARROW
  #define IDC_IBEAM    (char *)152L     // XC_xterm
  #define IDC_WAIT     (char *)150L     // XC_watch
  #define IDC_CROSS    (char *)34L      // XC_crosshair
  #define IDC_UPARROW  (char *)22L      // XC_center_ptr
  #define IDC_SIZEALL  (char *)52L      // XC_fleur
  #define IDC_SIZE     IDC_SIZEALL
  #define IDC_SIZENWSE (char *)32L      // XC_cross_reverse
  #define IDC_SIZENESW IDC_SIZENWSE
  #define IDC_SIZEWE   (char *)108L     // XC_sb_h_double_arrow
  #define IDC_SIZENS   (char *)116L     // XC_sb_v_double_arrow

  #define _fastcall

typedef struct _FILETIME
{
   DWORD dwLowDateTime;
   DWORD dwHighDateTime;
}
   FILETIME;

typedef struct tagSIZE
{
   LONG cx;
   LONG cy;
}
   SIZE;

typedef struct tagLOGFONT
{
   LONG lfHeight;
   LONG lfWidth;
   LONG lfEscapement;
   LONG lfOrientation;
   LONG lfWeight;
   BYTE lfItalic;
   BYTE lfUnderline;
   BYTE lfStrikeOut;
   BYTE lfCharSet;
   BYTE lfOutPrecision;
   BYTE lfClipPrecision;
   BYTE lfQuality;
   BYTE lfPitchAndFamily;
   char lfFaceName[LF_FACESIZE];
}
   LOGFONT;

typedef struct tagRGBQUAD
{
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbReserved;
  }
    RGBQUAD;

typedef struct _RECT
{
    long left;
    long top;
    long right;
    long bottom;
}
    RECT;

typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
  }
    BITMAPINFOHEADER;

typedef struct tagBITMAPINFO
{
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD bmiColors[1];
  }
    BITMAPINFO;

typedef struct tagPOINT
{
#ifdef __cplusplus                          
    union { LONG x; LONG X; };
    union { LONG y; LONG Y; };
#else
    LONG x;
    LONG y;
#endif
}
    POINT;


typedef struct _SYSTEMTIME
{
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
}
    SYSTEMTIME;

typedef struct tagMSG    
{
    HWND hwnd;
    UINT message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD time;
    POINT pt;
}
    MSG;

typedef struct TMessage    
{
    WPARAM    WParam;
    LPARAM    LParam;
    long int  Result;
}
    TMessage;

typedef struct MENUSTRINGTABLE    
{
    int       IdItem;             // Идентификатор строки
    char      NameItem[MAX_PATH]; // Текст
    int       Enable;             // Доступность
    int       Check;
}
   MENUSTRINGTABLE;

// Прототипы переопределенных функций (XWindow.cpp)
char * _fastcall strlwr(char * string);
char * _fastcall itoa(int number, char * string,int index);
char * _fastcall ltoa(long number, char* string,int index);
void   _fastcall GetSystemTime(SYSTEMTIME * systemtime);
int    _fastcall MessageBox(HWND hwnd, const TCHAR * message,
                            const TCHAR * title, int flag);

// Прототипы функций, определенных только для Linux (xwindow.cpp)  

// Конвертировать индекс палитры в цвет вида COLORREF
// index - индекс палитры XWindow
// возвращает COLORREF
COLORREF _fastcall ConvertIndexPaletteToCOLORREF(COLORREF index);

// Конвертировать цвет вида COLORREF в индекс палитры
// color - цвет вида COLORREF
// возвращает индекс палитры
COLORREF _fastcall ConvertCOLORREFToIndexPalette(COLORREF color);

typedef int(WINAPI *FARPROC) ();

#ifdef OC2000
 #define HIDELOG               
#endif

#endif     // LINUX

#ifdef WIN32API       // Windows GDI
                       
typedef struct XDrawHandle        
{
  unsigned long newhandle;
  unsigned long oldhandle;
}
  XDrawHandle;

typedef XDrawHandle  XHPEN;
typedef XDrawHandle  XHBRUSH;

#else

typedef long int   XHPEN;
typedef long int   XHBRUSH;

#endif

#ifdef BUILD_DLL
// Прототипы переопределенных функций (XWindow.cpp)
int _fastcall CheckDiskFreeSpaceEx(const char * name, double length);
#endif

#ifdef WIN32API
 #if !defined(STRICT)
    #define STRICT
 #endif
 #include <windows.h>
 #include <stdlib.h>
 typedef long int XYTYPE;

#if defined(__BORLANDC__) // Для Borland C++
  #include <dir.h>        
#endif
#endif

// MAPTRACER   - включение трассировки (TRUE/FALSE);
// TRACE_MEM   - трассировка работы с памятью;
// TRACE_MAP   - трассировка работы конструкторов,деструкторов,
//               доступа к району работ;
// TRACE_READ  - трассировка операций чтения;
// TRACE_WRITE - трассировка операций записи.

#ifndef MAPTRACER
 #define MAPTRACER 0
#endif
#ifndef TRACE_MAP
 #define TRACE_MAP TRUE
#endif
#ifndef TRACE_MEM
 #define TRACE_MEM TRUE
#endif
#ifndef TRACE_READ
 #define TRACE_READ FALSE
#endif
#ifndef TRACE_WRITE
 #define TRACE_WRITE FALSE
#endif

#ifdef WINCE
  #undef  LINUXAPI
//  #define HIDETRY
  #define HIDELOG
  #define HIDEACC43
  #define MINIDATA
  #define HIDEDIB
  #define HIDECUT
  #define RISCCPU
  #define HIDEMTL
  #define HIDETIN       
  #define HIDEMTQ
  #define HIDEMTR3D
  #define HIDEMETAFILE
  #define HIDERSC3D
  #define HIDE3D

  #define stricmp    strcmp
  #define strcmpi    strcmp
  #define strnicmp   strncmp
  #define strncmpi   strncmp
  #define ltoa       _ltoa

  #define MB_TASKMODAL    0
  #define OEM_CHARSET     255
  #define FW_ULTRALIGHT   FW_EXTRALIGHT

  #define TA_LEFT         0
  #define TA_RIGHT        2
  #define TA_CENTER       6

  #define TA_TOP          0
  #define TA_BOTTOM       8
  #define TA_BASELINE    24

#else

 #undef UNICODE
 #undef _UNICODE

#ifndef __BORLANDC__          // Кроме Borland C++
 #define strncmpi strnicmp
#endif

#endif    // WINCE

#ifdef BUILD_DLL

#ifndef UNICODE

#ifndef LINUXAPI   
 #ifndef TCHAR
  typedef char TCHAR;
 #endif
#endif 

#ifndef _TEXT
#define _TEXT(x)  x
#define _tcscat   strcat
#define _tcsncat  strncat   
#define _tcscpy   strcpy

#ifndef GISWEB       
#define _tcsncat  strncat
#define _tcsncpy  strncpy
#endif
#endif

#endif

#endif // BUILD_DLL

#ifndef MAPTRACE_H
  #include "maptrace.h"  // Трассировка вызовов функций
#endif

// --------------------------------------------------------------
// РЕАЛИЗАЦИЯ СИСТЕМНЫХ ФУНКЦИЙ В БИБЛИОТЕКАХ
//  MAPACCES.DLL (Borland C++) и MAPAXSVC.DLL (Visual C++)
// --------------------------------------------------------------
// ПРИ ОШИБКЕ ВСЕ ФУНКЦИИ ВОЗВРАЩАЮТ НОЛЬ !

// Преобразовать строку "char" в UNICODE
// ---------------------------------------
#ifdef __cplusplus        
inline int StringToUnicode(const char * src,
                           WCHAR * dest,int bytes)
{
  if ((src == 0) || (dest == 0)) return 0;

#ifdef WIN32API       // UNICODE            
  return MultiByteToWideChar(CP_ACP,0,
                             src,-1,
                             dest,bytes);   
#else
#ifndef LINUXAPI                            
  return (int)strncpy(dest,src,bytes);
#else
  iconv_t    mycodec;
#ifndef ANSI                                
  const char *fromcode = "KOI8-R";
#else
  const char *fromcode = "CP1251";
#endif
  const char *tocode   = "UTF-8";
  size_t inbytes       = (size_t)bytes;     // 19/03/09
  size_t outbytes      = (size_t)bytes;
  int    ret = 0;

  mycodec = iconv_open(tocode, fromcode);

  if ((ptrdiff_t)mycodec > -1)
  {
    char **src1  = (char **)&src;     
    char **dest1 = (char **)&dest;

    ret = iconv(mycodec, src1, &inbytes, dest1, &outbytes);
    if (ret == -1) ret = 0;
    iconv_close(mycodec);
  }

  return ret;
#endif
#endif

}
#else
 #define StringToUnicode(src,dest,bytes) strncpy(dest,src,bytes)
#endif

// Преобразовать символы UNICODE в строку "char"
// ---------------------------------------
#ifdef __cplusplus        
inline int UnicodeToString(const WCHAR * src,              
                           char * dest, int bytes)
{

  if ((src == 0) || (dest == 0)) return 0;

#ifdef WIN32API
  return WideCharToMultiByte(CP_ACP,0,
                             src,-1,
                             dest,bytes/sizeof(TCHAR),0,0);
#else
#ifndef LINUXAPI                            
  return (int)strncpy(dest,src,bytes);
#else
  iconv_t    mycodec;
#ifndef ANSI                                
  const char *tocode   = "KOI8-R";
#else
  const char *tocode   = "CP1251";
#endif
  const char *fromcode = "UTF-8";
  size_t inbytes       = (size_t)bytes;             // 19/03/09
  size_t outbytes      = (size_t)bytes;
  int    ret = 0; 

  mycodec = iconv_open(tocode, fromcode);
  if ((ptrdiff_t)mycodec > -1)
  {
    char **src1  = (char **)&src;      
    char **dest1 = (char **)&dest;

    ret = iconv(mycodec, src1, &inbytes, dest1, &outbytes);
    if (ret == -1) ret = 0;
    iconv_close(mycodec);
  }

  return ret;
#endif
#endif

}
#else
 #define UnicodeToString(src,dest,bytes) strncpy(dest,src,bytes)
#endif

#ifdef LINUXAPI
// Процедура strupr для LINUX
#ifdef __cplusplus        
 inline char * strupr(char * string) {return string;} 
#else
 #define strupr(string) string
#endif

#endif

// РАБОТА С ПАМЯТЬЮ
// ----------------------
#ifdef __cplusplus        
inline char * AllocateTheMemory(int size)
{
  void * Memory;

#ifdef WIN32API
  #ifdef WINCE                   
    Memory = new char[size];  
  #else
    Memory = ::VirtualAlloc(NULL,(DWORD)size,
                            MEM_RESERVE | MEM_COMMIT,
                            PAGE_READWRITE);
  #endif
#else
 #ifdef LINUXAPI
    Memory = malloc(size);          
 #else
    Memory = 0;
 #endif

#endif

#if TRACE_MEM == TRUE
  Tracer2("\n+++++ 0x%04X - Allocate memory block, size - 0x%04X\n",
          Memory,size);
#endif

  return (char *) Memory;
}
#else
 #define AllocateTheMemory(size) (char *) malloc(size)
#endif

#ifdef __cplusplus        
inline int FreeTheMemory(char * address)
{
#if TRACE_MEM == TRUE
  Tracer1("\n----- 0x%04X - Free memory block\n",address);
#endif

#ifdef WIN32API
  if (address == 0) return 0;
 #ifdef WINCE                     
   delete [] address;
   return 1;
 #else 
   return ::VirtualFree((LPVOID)address,0,MEM_RELEASE);
 #endif
#else

 #ifdef LINUXAPI
  free(address);
  return 1;
 #else
  return 0;
 #endif

#endif
}
#else
 #define FreeTheMemory(address) free(address)
#endif 

#ifdef __cplusplus        
inline int GetTheLastError()
{

 int ret;

#ifdef WIN32API

  ret = ::GetLastError();

#else

  ret = 0;

#endif

  return ret;

}
#else
 #define GetTheLastError() 0
#endif 

// РАБОТА С ФАЙЛАМИ
// ----------------------

#ifdef __cplusplus   
inline void SplitThePath(const char *path, char *drive, char *dir,
                         char *name, char *ext)
{

#if defined(WINCE) || defined(LINUXAPI)
  int first = 0;                
  int size, begin;
  int end;
  int drivesize;                  

  if(!path) return ;

  size = strlen(path);

  // DRIVE
  if (drive)
  {
    drive[0] = 0;
    drivesize = strcspn(path, ":");                    
    if (drivesize !=  size)  // строка содержит ':'    
    {
      strncpy(drive, path, drivesize+1);
      drive[drivesize+1] = 0;
      first = drivesize+1;
    }
  }

  begin = first;
  end = size;

  if (dir)  dir[0] = 0;
#ifndef LINUXAPI
  while((path[begin] != '\\') &&  (begin <= end))
  {
      begin++;
  }
#else 
  while((path[begin] != '/') &&  (begin <= end))
  {
    begin++;
  }
#endif

#ifndef LINUXAPI
  while((path[end] != '\\') &&  (end > begin))
  {
    end--;
  }
#else  
  while((path[end] != '/') &&  (end > begin))
  {
    end--;
  }
#endif
  if (begin < end)
  {
    end++;

    if (dir)   
    {
      strncpy(dir, path+begin, end-begin);
      dir[end-begin] = 0;
    }
    begin = end;
  }
  else
  {
    begin = first;
  }

  if (name) name[0] = 0;
  if (ext)  ext[0]  = 0;

  if (begin < (end = size))
  {
    //EXT
    while((path[end] != '.') && (begin < end))
    {
      end--;
    }

    if (begin < end)
    {
      if (name)
      {
        strncpy(name, path+begin, end-begin);
        name[end-begin] = 0;
      }

      if(ext && (end < size))
      {
        strncpy(ext, path+end, size-end);
        ext[size-end] = 0;
      }
    }
    else
    {
      if (name)           
      {
        strncpy(name, path + end, size - end);
        name[size - end] = 0;
      }
    }
  }

#else // if WIN32API

#if defined(__BORLANDC__) // Для Borland C++
  fnsplit(path,drive,dir,name,ext);           
#else
  _splitpath(path,drive,dir,name,ext);
#endif

#endif

}
#else
void SplitThePath(const char *path, char *drive, char *dir,
                         char *name, char *ext); // xwindow.cpp
#endif

#ifdef __cplusplus   
inline void MakeThePath(char *path, const char *drive, const char *dir,
                        const char *name, const char *ext)
{

#if defined(WINCE) || defined(LINUXAPI)

  if(!path) return ;
  path[0] = 0;              
  if(drive)
  {
    strcat(path, drive);
  }

  if(dir)
  {
    strcat(path, dir);
  }

  if(name)
  {
    strcat(path, name);

    if(ext)
    {
      strcat(path, ext);
    }
  }

#else // if WIN32API

#if defined(__BORLANDC__) // Для Borland C++
  fnmerge(path,drive,dir,name,ext);         
#else
  _makepath(path,drive,dir,name,ext);
#endif

#endif

}
#else
void MakeThePath(char *path, const char *drive, const char *dir,
                        const char *name, const char *ext); // xwindow.cpp
#endif


// Открыть файл
#ifdef __cplusplus   
inline HANDLE OpenTheFile(const char * name,int access = 0,
                          int mode = FILE_SHARE_READ|FILE_SHARE_WRITE,
                          int attribute = 0)
{
  HANDLE file;

  if (name == 0) name = "";

  if (attribute == 0) attribute = OPEN_ALWAYS;

#ifdef LINUXAPI
  if (attribute & O_CREAT)   
    mode = FILE_SHARE_READ | FILE_SHARE_WRITE;

  if (access == 0) access = O_RDWR;                      
  else
  {
    if (access & GENERIC_READ)
    {
      // Уберем GENERIC_READ(это наш флаг)
      access = access & 0xFFEFFFFF;
      if (access & GENERIC_WRITE) 
      {
        // Уберем GENERIC_WRITE
        access = access & 0xFFFFFFFE;
	// Зададим аттрибуты файла на запись и чтение
        access = access | O_RDWR;
      }
    }
  }

  access=access|attribute;

  if (!(access & O_CREAT)) mode = 0; 
#endif

#ifdef WIN32API

  if (access == 0) access = GENERIC_READ|GENERIC_WRITE;     

#ifdef UNICODE
  TCHAR tname[MAX_PATH];
  StringToUnicode(name,tname,sizeof(tname));
#endif

  if ((file = ::CreateFile(
#ifndef UNICODE
                            name,
#else
                            tname,
#endif
                            access,mode,NULL,
                            attribute,FILE_ATTRIBUTE_NORMAL,
                            0)) == INVALID_HANDLE_VALUE)
    {
      file = 0;
    }
#else

  #ifdef LINUXAPI
   if ((int)(file = open64(name,access,mode)) == -1)  //NIITP: на свой страх и риск: дополнительно для работы с большими файлами везде в коде требуется 8-байтовый
   {							//указатель (например long long int). Иначе с помощью lseek(...) невозможно попасть за границу в 2 Гб прямой адресацией.
     file = 0;						//Добавлено ТОЛЬКО для построения больших матриц, которые строятся простым добавлением информации в конец
   }							//файла с помощью переопределенной функцией write(...). Эта функция переопределяется по флагу _LARGEFILE64_SOURCE в Makefile.

   if ((access & O_CREAT) && file)                       
   {
     char        dir[MAX_PATH];
     struct stat statv;
     int         flag = (S_IXUSR|S_IXGRP|S_IXOTH);     
  
     memset(dir, 0, MAX_PATH);
     SplitThePath(name, 0, dir, 0, 0);
     if (strlen(dir))
     {
       // Узнаем права каталога на запись и чтение 
       stat(dir, &statv);
     }
     else statv.st_mode = FILE_SHARE_READ | FILE_SHARE_WRITE;

     // Установим права созданного файла на запись и чтение 
     chmod(name, (statv.st_mode & ~flag));
   }     
  #else
    file = 0;
  #endif

#endif

#if TRACE_MAP == TRUE
  Tracer2("\n->>>> Open file : %s,"
          "\n      Handle    = 0x%04X\n", name,file);
#endif

  return file;
}
#else                          
HANDLE OpenTheFile(const char * name,int access ,
                          int mode ,
                          int attribute );
#endif


#ifdef __cplusplus   
 inline HANDLE OpenTheShareFile(const char * name,int access = 0,
                               int mode = FILE_SHARE_READ|FILE_SHARE_WRITE,
                               int attribute = 0)
{
  HANDLE file;

  if (name == 0) name = "";

#ifdef LINUXAPI         
  if (attribute & O_CREAT)  
  {
    mode = FILE_SHARE_READ | FILE_SHARE_WRITE;
  }    
#endif

  if ((mode & FILE_SHARE_WRITE) == 0)
    {
      // Доступ на запись монопольный
      return OpenTheFile(name,access,mode,attribute);
    }

  if (attribute == 0) attribute = OPEN_ALWAYS;

#ifdef LINUXAPI

  if (access == 0) access = O_RDWR;                      
  else
  {
    if (access & GENERIC_READ)
    {
      // Уберем GENERIC_READ(это наш флаг)
      access = access & 0xFFEFFFFF;
      if (access & GENERIC_WRITE) 
      {
        // Уберем GENERIC_WRITE
        access = access & 0xFFFFFFFE;
	// Зададим аттрибуты файла на запись и чтение
        access = access | O_RDWR;
      }
    }
  }

  access = access|attribute;
  
  if (!(access & O_CREAT)) 
  {
   mode = 0; 
  }  
  
  if ((file = open64(name,access,mode)) == -1) //NIITP 
    {
      file = 0;
    }

  if ((access & O_CREAT) && file)                       
  {
     char        dir[MAX_PATH];
     struct stat statv;
     int         flag = (S_IXUSR|S_IXGRP|S_IXOTH);

     memset(dir, 0, MAX_PATH);
     SplitThePath(name, 0, dir, 0, 0);
     if (strlen(dir))
     {
       // Узнаем права каталога на запись и чтение 
       stat(dir, &statv);
     }
     else statv.st_mode = FILE_SHARE_READ | FILE_SHARE_WRITE;

     // Установим права созданного файла на запись и чтение
     chmod(name, (statv.st_mode & ~flag));
  }
#else

#ifdef WIN32API

  if (access == 0) access = GENERIC_READ|GENERIC_WRITE;        


#ifdef UNICODE
  TCHAR tname[MAX_PATH];
  StringToUnicode(name,tname,sizeof(tname));
#endif


  if ((file = ::CreateFile(
#ifndef UNICODE
                           name,
#else
                           tname,
#endif
                           access,mode,NULL,
                           attribute,FILE_FLAG_WRITE_THROUGH,
                           0)) == INVALID_HANDLE_VALUE)
    {
      file = 0;
    }
#else

      file = 0;

#endif // WIN32API

#endif // LINUXAPI

#if TRACE_MAP == TRUE
  Tracer2("\n->>>> Open file : %s,"
          "\n      Handle    = 0x%04X\n", name,file);
#endif

  return file;
}
#else
HANDLE OpenTheShareFile(const char * name,int access,
                               int mode ,
                               int attribute );
#endif

// Закрыть файл
#ifdef __cplusplus   
#ifndef WINCE
inline int CloseTheFile(HANDLE& file)
#else
inline int CloseTheFile(HANDLE file)
#endif
{
  int ret;

#ifdef WIN32API

  if (file != 0)
    {
      ret = ::CloseHandle(file);
    }
  else
    {
      ret = 0;
    }

#if TRACE_MAP == TRUE
  Tracer2("\n-<<<< Close for : 0x%04X, ret = %u\n", (int)file,ret);
#endif

  file = 0;
#else

 #ifdef LINUXAPI
  if (file > 0)          
    {
      ret = close(file); 

      if (ret == 0) ret = 1;  
      else ret = 0;

#if TRACE_MAP == TRUE
  Tracer2("\n-<<<< Close for : 0x%04X, ret = %u\n", (int)file,ret);
#endif
    }
  else
    {
      ret = 0;
    }
  #else
    file = 0;
    ret  = 0;
  #endif

#endif

  return ret;
}
#else
int CloseTheFile(HANDLE file);      
#endif

// Проверить наличие файла
#ifdef __cplusplus   
 inline int ExistTheFile(const char * name)
{
  int ret;                              
  HANDLE handle;

  if (name == 0) return 0;

  handle = OpenTheFile(name,
                              GENERIC_READ,
                              FILE_SHARE_READ|FILE_SHARE_WRITE,OPEN_EXISTING);

#ifdef LINUXAPI

  if (((int)handle) <= 0)
  {
    ret = 0;    
  }  
  else
  {
    ret = 1;
    CloseTheFile(handle);
  }

#else
  ret = handle && 1;

  CloseTheFile(handle);
#endif

  return ret;
}
#else
 int ExistTheFile(const char * name);
#endif 

// Считать блок данных из файла
#ifdef __cplusplus   
inline int ReadTheFile(HANDLE file,char * address,long int length,
                       long int * result)
{
  int ret;

#ifdef WIN32API

  ret = ::ReadFile(file,address,length,(LPDWORD)result,NULL);

#else

  #ifdef LINUXAPI
    ret = read(file,address,length);  
    if (ret==-1) ret=0;
    else *result=ret;
  #else
    ret = 0;
  #endif

#endif

#if TRACE_READ == TRUE
  Tracer2("\n--->> Read for : 0x%04X, total = %u\n", (int)file,*ret);
#endif

  return ret;
}
#else
#define ReadTheFile(file,address,length,result) ((*result=read(file,address,length)) != -1)
#endif

// Установить смещение в файле перед чтением/записью
#ifdef __cplusplus   
inline long int OffsetTheFile(HANDLE file,long int offset,int type)
{
  long int ret;

#ifdef WIN32API

  if (file != 0)
    {
      if (type == FILE_BEGIN)      
        {
          long int top64 = 0;
          ret = ::SetFilePointer(file,offset,&top64,type);
        }
      else
          ret = ::SetFilePointer(file,offset,0,type);

      if (ret == (long int)0x0FFFFFFFF) ret = 0;
    }
  else
    {
      ret = 0;
    }
#else

 #ifdef LINUXAPI
    if (file != 0)
    {
      ret = lseek(file,offset,type);       
      if (ret == (long int)0x0FFFFFFFF) ret = 0;
    }
    else
    {
      ret = 0;
    }
  #else
    ret = 0;
  #endif

#endif

#if TRACE_READ == TRUE
  Tracer2("\n===== Offset for: 0x%04X, offset = %li\n",
                                      (int)file,ret);
#endif

  return ret;
}
#else
#define OffsetTheFile(file, offset, type) lseek(file,offset,type)
#endif 

// Запросить длину файла

#ifdef __cplusplus   
inline long int LengthTheFile(HANDLE file)
{
  long int ret;

#ifdef WIN32API

  if (file != 0)
    {
      long int top64 = 0;                                
      ret = ::SetFilePointer(file, 0, &top64, FILE_END);
      if (ret == (long int)0x0FFFFFFFF) ret = 0;
    }
  else
    {
      ret = 0;
    }
#else

 #ifdef LINUXAPI
  if (file != 0)
    {
      ret = lseek(file,0,SEEK_END);
      if (ret == (long int)0x0FFFFFFFF) ret = 0;
    }
  else
    {
      ret = 0;
    }
  #else
    ret = 0;
  #endif

#endif

#if TRACE_READ == TRUE
  Tracer2("\n===== Length for: 0x%04X, length = %li\n",
                                     (int)file,ret);
#endif

  return ret;
}
#else
#define LengthTheFile(file) lseek(file,0,SEEK_END)
#endif

// Установить новую длину файла

#ifdef __cplusplus   
inline int EndTheFile(HANDLE file)
{
  int ret;

#ifdef WIN32API

  if (file != 0)
    {
      ret = ::SetEndOfFile(file);
    }
  else
    {
      ret = 0;
    }

#else

  #ifdef LINUXAPI
    if (file != 0)
    {
      ret = lseek(file,0,SEEK_CUR);   
#ifdef WATCOM  
      ret = ltrunc(file,ret,0);
#else
      ret = ftruncate(file,ret);
#endif
      if (ret == -1) ret = 0;         
      else ret = 1;
    }
    else
    {
      ret = 0;
    }
  #else
    ret = 0;
  #endif

#endif

#if TRACE_WRITE == TRUE
  Tracer1("\n----< End   for : 0x%04X\n", file);
#endif

  return ret;
}
#else
 int EndTheFile(HANDLE file); // xwindow.cpp
#endif

// Записать блок данных в файл

#ifdef __cplusplus   
inline int WriteTheFile(HANDLE file,const char * address,long int length,
                        long int * result)
{
  int ret;

#ifdef WIN32API

  ret = ::WriteFile(file,address,length,(LPDWORD)result,NULL);

#else

  #ifdef LINUXAPI
    ret = write(file,address,length);
    if (ret==-1) ret=0;
    else *result=ret;
  #else
    ret = 0;
  #endif

#endif  // WIN32API

#if TRACE_WRITE == TRUE
  Tracer2("\n---<< Write for : 0x%04X, total = %lu\n", file,result);
#endif

  return ret;

}
#else
#define WriteTheFile(file,address,length,result) ((*result=write(file,address,length)) != -1)
#endif

#ifdef __cplusplus   
inline int DeleteTheFile(const char * name)
{
  int ret;

#ifdef WIN32API

#ifdef UNICODE
  TCHAR tname[MAX_PATH];
  StringToUnicode(name,tname,sizeof(tname));
  ret = ::DeleteFile(tname);
#else
  ret = ::DeleteFile(name);
#endif

#else

  #ifdef LINUXAPI
    ret = unlink(name);      
    
    if (ret == 0) ret = 1;           
    else ret = 0;
  #else
    ret = 0;
  #endif

#endif

#if TRACE_MAP == TRUE
  Tracer2("\n===== Delete for : %s, ret = %u\n", name,ret);
#endif

  return ret;
}
#else
#define DeleteTheFile(name) unlink(name)
#endif

#ifdef __cplusplus   
inline int MoveTheFile(const char * oldname,const char * newname)
{
  int ret;

#ifdef WIN32API

#ifdef UNICODE
  TCHAR toldname[MAX_PATH];
  StringToUnicode(oldname,toldname,sizeof(toldname));

  TCHAR tnewname[MAX_PATH];
  StringToUnicode(newname,tnewname,sizeof(tnewname));

  ret = ::MoveFile(toldname,tnewname);
#else

  OSVERSIONINFO version;                                               
  version.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

  // Запросить версию Windows
  // 5.0 - Windows 2000
  // 5.1 - Windows XP
  if ((GetVersionEx(&version) != 0) && (version.dwMajorVersion >= 5))
    {
      ret = ::MoveFileEx(oldname,newname,                              
                         MOVEFILE_COPY_ALLOWED|MOVEFILE_REPLACE_EXISTING|MOVEFILE_WRITE_THROUGH);
    }
  else
    {
      ret = ::MoveFile(oldname,newname);                               
    }
#endif

#else

  #ifdef LINUXAPI
    ret = rename(oldname,newname);   

    if (ret == 0) ret = 1;           
    else ret = 0;
  #else
    ret = 0;
  #endif
#endif

#if TRACE_MAP == TRUE
  Tracer2("\n===== Move from %s to %s", oldname,newname);
  Tracer1("\n      Move ret : %u\n", ret);
#endif

  return ret;
}
#else
#define MoveTheFile(oldname,newname) rename(oldname,newname)
#endif

#ifdef WIN32API   
inline int CopyTheFile(const char * oldname,
                       const char * newname, int exist = 0)
{
  int ret;

#ifdef WIN32API

#ifdef UNICODE
  TCHAR toldname[MAX_PATH];
  StringToUnicode(oldname,toldname,sizeof(toldname));

  TCHAR tnewname[MAX_PATH];
  StringToUnicode(newname,tnewname,sizeof(tnewname));

  ret = ::CopyFile(toldname,tnewname,exist);
#else
  ret = ::CopyFile(oldname,newname,exist);
#endif

#else
    ret = 0;
#endif

#if TRACE_MAP == TRUE
  Tracer2("\n===== Copy from %s to %s", oldname,newname);
  Tracer1("\n      Copy ret : %u\n", ret);
#endif

  return ret;
}
#else
int CopyTheFile(const char * oldname,
                const char * newname, int exist);
#endif


#ifdef __cplusplus   
inline int CreateTheDirectory(const char * name)
{

 int ret;

#ifdef WIN32API

  SECURITY_ATTRIBUTES Attributes;  // security descriptor
  Attributes.nLength = sizeof(SECURITY_ATTRIBUTES);
  Attributes.lpSecurityDescriptor = NULL;
  Attributes.bInheritHandle = TRUE;

#ifdef UNICODE
  TCHAR tname[MAX_PATH];
  StringToUnicode(name,tname,sizeof(tname));
  ret = ::CreateDirectory(tname,&Attributes);
#else
  ret = ::CreateDirectory(name,&Attributes);
#endif

  if ((ret == 0) && (::GetTheLastError() == ERROR_ALREADY_EXISTS))
    {
      ret = 1;     
    }
  else
    {
      // Дополнительная проверка для NT    
#ifdef UNICODE
#ifndef WINCE                              
      ret = ::SetCurrentDirectory(tname);
#endif
#else
      ret = ::SetCurrentDirectory(name);
#endif
    }

#else
  #ifdef LINUXAPI  
    ret = mkdir(name, S_IRWXU|S_IRWXG|S_IRWXO);   
    if (ret == -1)
      {
        if (errno == EEXIST) ret = 1;
        else ret = 0;
      }
    else ret = 1;

    if (ret && (errno != EEXIST))           
    {
      char   currentdir[MAX_PATH];
      struct stat statv;
      int i = -1;

      // Узнаем имя каталога, в котором создается текущий подкаталог
      strcpy(currentdir, name);

      if (strlen(currentdir) > 1)
      {
        currentdir[strlen(currentdir) - 1] = 0;
	while ((i > -1) && (currentdir[i] != '/'))
	{
	  currentdir[i] = 0;
	  i--;
	}

	if (i > -1) currentdir[i] = 0;
      }

      if (i == -1) statv.st_mode = S_IRWXU|S_IRWXG|S_IRWXO;
      else
        // Узнаем права каталога на запись и чтение
        stat(currentdir, &statv);
      // Установим права созданного каталога на запись и чтение
      chmod(name, statv.st_mode);
    }
  #else
    ret = 0;
  #endif

#endif

#if TRACE_MAP == TRUE
  Tracer1("\n===== Create Directory : %s", name);
  Tracer1("\n      Create ret : %u\n", ret);
#endif

  return ret;

}
#else
int CreateTheDirectory(const char * name); // xwindow.cpp
#endif

#ifdef __cplusplus   
inline int DeleteTheDirectory(const char * name)
{
 int ret;

#ifdef WIN32API

#ifdef UNICODE
  TCHAR tname[MAX_PATH];
  StringToUnicode(name,tname,sizeof(tname));
  ret = ::RemoveDirectory(tname);
#else
  ret = ::RemoveDirectory(name);
#endif

#else
 #ifdef LINUXAPI
  ret = rmdir(name);

  if (ret == 0) ret = 1;           
  else ret = 0;
 #endif
#endif

  return ret;
}
#else
#define DeleteTheDirectory(name) rmdir(name)
#endif

#ifdef __cplusplus   
inline ptrdiff_t GetTheCurrentDirectory(char * name, long int size)
{
 int ret;

#ifdef WIN32API
#ifndef WINCE                              
  ret = ::GetCurrentDirectory(size,name);
#else
  ret = 0;
#endif
#else

 #ifdef LINUXAPI
  ret = (ptrdiff_t) getcwd(name,size);
 #endif

#endif

  return ret;
}
#else
#define GetTheCurrentDirectory(name,size) getcwd(name,size)
#endif

#ifdef __cplusplus   
inline int SetTheFileAttributes(const char * name,
                                long int attributes)
{
 int ret;

#ifdef WIN32API

#ifdef UNICODE
  TCHAR tname[MAX_PATH];
  StringToUnicode(name,tname,sizeof(tname));
  ret = ::SetFileAttributes(tname,(DWORD)attributes);
#else
  ret = ::SetFileAttributes(name,(DWORD)attributes);
#endif

#else

  #ifdef LINUXAPI
    ret = chmod(name,attributes);
    if (ret == 0) ret = 1;   
    else ret = 0;            
  #else
    ret = 0;
  #endif

#endif

  return ret;
}
#else
#ifndef OC2000 
#define SetTheFileAttributes(name,attributes) (chmod(name,attributes) != -1)
#else
#define SetTheFileAttributes(name,attributes) 1
#endif // OC2000
#endif

#ifdef __cplusplus   
inline int GetTheTempPath(int bytes,char * buffer)
{
  int ret;          
  if ((bytes <= 0) || (buffer == 0)) return 0;

#ifdef WIN32API

#ifdef UNICODE
  TCHAR tname[MAX_PATH];
  ret = ::GetTempPath(sizeof(tname)/sizeof(TCHAR),tname);
  if (ret)
    {
      UnicodeToString(tname,buffer,bytes);
    }
#else
  ret = ::GetTempPath(bytes,buffer);
#endif

#else

  #ifdef LINUXAPI
    if (getenv("TMPDIR") == NULL)
	buffer = strcpy(buffer,P_tmpdir);
    else if (strcmp(getenv("TMPDIR"),"") == 0)
	buffer = strcpy(buffer,P_tmpdir);
    else
    buffer = strncpy(buffer,getenv("TMPDIR"),bytes);   
    ret = 4;
  #else
    ret = 0;
  #endif

#endif

  return ret;
}
#else
#ifndef OC2000               
#define GetTheTempPath(bytes,buffer) strncpy(buffer,P_tmpdir,bytes)
#else
#define GetTheTempPath(bytes,buffer) strncpy(buffer,"/tmp",bytes)
#endif
#endif


#ifdef __cplusplus   
inline int GetTheSystemDate(char * dest,int size)
{
  SYSTEMTIME data;             
  long form = 19900000;  
  int delta;

  if (dest == 0) return 0;
  if (size < 10) return 0;
  
  GetSystemTime(&data);         

  delta = (data.wYear - 1990) * 10000;  // ГОД
  if (delta > 0) form += delta;
  delta     = data.wMonth * 100;            // МЕСЯЦ
  if (delta > 0) form += delta;
  delta     = data.wDay;                    // ДЕНЬ
  if (delta > 0) form += delta;

  ltoa(form,dest,10);

  return 1;
}
#else
int GetTheSystemDate(char * dest,int size);
#endif

// Запрос даты и времени в формате "YYYYMMDD" и число секунд от 00:00:00
#ifdef __cplusplus   
inline void GetTheSystemDateAndTime(long int *date, long int *outtime) 
{
  int delta;
  SYSTEMTIME data;

  GetSystemTime(&data);        

  if (date != 0)               
    {
      *date = 19900000;

       delta = (data.wYear - 1990) * 10000;  // ГОД
       if (delta > 0) *date += delta;
         delta     = data.wMonth * 100;            // МЕСЯЦ
       if (delta > 0) *date += delta;
         delta     = data.wDay;                    // ДЕНЬ
       if (delta > 0) *date += delta;
    }

  if (outtime != 0)
    *outtime = (long)data.wSecond + (long)data.wMinute*60L +
               (long)data.wHour*3600L;
}
#else
void GetTheSystemDateAndTime(long int *date, long int *outtime); // xwindow.cpp
#endif

#ifdef __cplusplus   
inline long int SendTheMessage(HWND Handle,long int messagenumber,long int code,long int parm)
{
#ifndef LINUXAPI
  return ::SendMessage(Handle,messagenumber,code,parm);
#else
  return 1;
#endif
}
#else
#define SendTheMessage(Handle,messagenumber,code,parm) 1   
#endif

#ifdef __cplusplus   
inline int LockTheFile(HANDLE file,long int offset,
                       long int size)
{
#ifdef WIN32API
#ifndef WINCE                                       
	return LockFile(file,offset,0,size,0);
#else
  return 1;
#endif
#else
  return 1;
#endif
}
#else
#define LockTheFile(file,offset,size) 1
#endif

#ifdef __cplusplus   
inline int UnlockTheFile(HANDLE file,long int offset,
                         long int size)
{
#ifdef WIN32API
#ifndef WINCE                                   
  return UnlockFile(file,offset,0,size,0);
#else
  return 1;
#endif
#else
  return 1;
#endif
}
#else
#define UnlockTheFile(file,offset,size)
#endif

#ifdef __cplusplus  
inline void SleepTheThread(long int milliseconds = 1)
{
#ifdef WIN32API
  Sleep(milliseconds);
#endif
}
#else
#define SleepTheThread(milliseconds)
#endif


//-----------------------------------------------------------------
// Проверить наличие свободного места на диске
// При ошибке возвращает ноль
//-----------------------------------------------------------------
#ifdef __cplusplus  
inline int CheckTheDiskFreeSpace(const char *name, double length)
{
#ifdef WIN32API
#ifndef WINCE

  DWORD    SectorsPerCluster;
  DWORD    BytesPerSector;
  DWORD    NumberOfFreeClusters;
  DWORD    TotalNumberOfClusters;
  char     RootDisk[MAX_PATH];

  if (name == 0 )  return 0;

  ::SplitThePath(name,RootDisk,NULL,NULL,NULL);

  if (::GetDiskFreeSpace
          (strcat(RootDisk,"\\"),
           &SectorsPerCluster,
           &BytesPerSector,
           &NumberOfFreeClusters,
           &TotalNumberOfClusters) == 0)
    {
      // "Не могу определить свободное место на диске .
      return 1;
    }

  if (NumberOfFreeClusters == 0 ||   
      (SectorsPerCluster*BytesPerSector) < (length/NumberOfFreeClusters))
    {
      // Отсутствует свободное место на диске
      return 0;
    }
#endif       // !WINCE

  return 1;

#else
#ifndef NUMBERTURN                                  
    struct statfs stbuf;                            

    if (statfs(name,&stbuf) == -1) return 0;
    
////////NIITP/////////////////////////////////////////////////////////////////////////////////////////// 
//некорректное обращение с типами: unsigned long * unsigned long с приведением к double
// приводит к переполнению типа (unsigned long) в результате умножения и дальнейшие операции теряют смысл :
 //if ((stbuf.f_bsize*stbuf.f_bfree) < length)  
    if (((double)(stbuf.f_bsize)*(double)(stbuf.f_bfree)) < length) // правильный вариант //NIITP
    {
      return 0;
    }

    return 1;                 
#else
    return 1;
#endif
#endif
}
#else
#define CheckTheDiskFreeSpace(name,length) 1
#endif

#ifdef __cplusplus  
inline int CheckDiskFreeSpace(const char *name, double length)
{
#ifdef WIN32API
#ifndef WINCE

#ifndef BUILD_DLL
  return CheckTheDiskFreeSpace(name, length);
#else
  return CheckDiskFreeSpaceEx(name,length);     // xwindow.cpp
#endif
#else
  return 1;
#endif       // !WINCE
#else
#if !defined(OC2000) && !defined(NUMBERTURN)                
  struct statfs stbuf;

  if (statfs(name,&stbuf) == -1) return 1;
  return (stbuf.f_bsize*stbuf.f_bfree);
#else  
  return 1;
#endif       // !OC2000
#endif
}
#else
#define CheckDiskFreeSpace(name,length) 1
#endif


/***** example *******************************************************
inline int LockTheFileOrSleep(HANDLE file,long int offset,
                              long int size,long int seconds = 5)
{
  int count = seconds * 1000;
  while(count-- > 0)
   {
     if (LockTheFile(file,offset,size)) return 1;
     SleepTheThread(1000);
   }

  return 0;
}
*******************************************************************/

//-----------------------------------------------------------------
// Получить короткое имя файла
// При ошибке возвращает ноль
//-----------------------------------------------------------------
#ifdef __cplusplus   
inline int GetShortFileName(char * filename,char * shortname, long int size)
{
  if ( (filename == 0) || (shortname == 0) || (size <= 0) ) return 0;

#ifdef WIN32API
#ifndef WINCE                                          

 HANDLE handle = ::OpenTheFile(filename,GENERIC_READ,
                               FILE_SHARE_READ|FILE_SHARE_WRITE,
                               OPEN_EXISTING);
 if (handle)
   {
     ::GetShortPathName(filename,shortname,size);
     ::CloseTheFile(handle);
     return 1;
   }

#endif
#endif

 strncpy(shortname,filename,size);
 return 0;

}
#else
#define GetShortFileName(filename,shortname,size) strncpy(shortname,filename,size)
#endif

//-----------------------------------------------------------------
// Получить длинное имя файла
// При ошибке возвращает ноль
//-----------------------------------------------------------------
#ifdef __cplusplus   
inline int GetLongFileName(char * filename,char * longname, long int size)
{
 if ( (filename == 0) || (longname == 0) || (size <= 0) ) return 0;

#ifdef WIN32API
#ifndef WINCE                                                     

 HANDLE handle = ::OpenTheFile(filename,GENERIC_READ,
                               FILE_SHARE_READ|FILE_SHARE_WRITE,
                               OPEN_EXISTING);
 if (handle)
   {
     WIN32_FIND_DATA name;
     ::FindFirstFile(filename,&name);
     strncpy(longname, name.cFileName, size);
     ::CloseTheFile(handle);
     return 1;
   }

#endif
#endif

 strncpy(longname,filename,size);
 return 0;

}
#else
#define GetLongFileName(filename,longname,size) strncpy(longname,filename,size)
#endif

#ifndef HIDESECTION   
#ifdef __cplusplus
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++ РАЗГРАНИЧЕНИЕ ДОСТУПА НА ЗАПИСЬ ПОТОКОВ++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifdef WIN32API
typedef CRITICAL_SECTION MAPCRITICALSECTION;
#else
typedef pthread_mutex_t MAPCRITICALSECTION;
#endif

//-----------------------------------------------------------------
// Инициализация критической секции
//-----------------------------------------------------------------
inline void InitializeTheCriticalSection(MAPCRITICALSECTION *section)
{
#ifdef WIN32API
  InitializeCriticalSection(section);
#else
  pthread_mutexattr_t attr;                                
  
  pthread_mutexattr_init(&attr);
#ifndef NUMBERTURN
  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
#else
  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
#endif
  pthread_mutex_init(section, &attr);

  pthread_mutexattr_destroy(&attr);
#endif
}

//-----------------------------------------------------------------
// Удаление критической секции
//-----------------------------------------------------------------
inline void DeleteTheCriticalSection(MAPCRITICALSECTION *section)
{
#ifdef WIN32API
  DeleteCriticalSection(section);
#else
  pthread_mutex_destroy(section);
#endif
}

//-----------------------------------------------------------------
// Активировать критическую секцию
//-----------------------------------------------------------------
inline void EnterTheCriticalSection(MAPCRITICALSECTION *section)
{
#ifdef WIN32API
  EnterCriticalSection(section);
#else
  pthread_mutex_lock(section);
#endif
}

//-----------------------------------------------------------------
// Деактивировать критическую секцию
//-----------------------------------------------------------------
inline void LeaveTheCriticalSection(MAPCRITICALSECTION *section)
{
#ifdef WIN32API
  LeaveCriticalSection(section);
#else
  pthread_mutex_unlock(section);
#endif
}
#endif // __cplusplus
#endif // !HIDESECTION

//-----------------------------------------------------------------
// Получение компонент цвета для данной глубины цвета
// т.е. разложения поля DIB матрицы на компоненты цвета
//-----------------------------------------------------------------
struct CELLColor{
  static int getRed(const COLORREF Color);
  static int getGreen(const COLORREF Color);
  static int getBlue(const COLORREF Color);
  static COLORREF getRGB(const int Red, const int Green, const int Blue);
};  
#endif  // MAPSYST_H

