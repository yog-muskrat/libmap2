
#ifndef MAPTRACE_H
#define MAPTRACE_H

//#include "mapversn.h"

//#define MAPTRACER TRUE
//#define TRACE_MEM TRUE

#ifndef MAPTRACER
  #define MAPTRACER FALSE   // Если трассировка нужна -
                            //  поставить TRUE
#endif


#define TracerSun(message) \
        { FILE* HFile = fopen( "/export/home/maptrace.log", "a+" );\
          fprintf( HFile, message);\
          fclose( HFile );}


#ifdef WINCE
  #define LOGFILENAME ".\\maptrace.log"
#else
  #define LOGFILENAME "c:\\maptrace.log"
#endif

#if MAPTRACER != FALSE

  #include <stdio.h>

#ifndef LINUXAPI   

//*******************************************************************
//  Пример вызова трассировки :
//   Tracer("0x%04X|message = 0x%04X BEGIN.\n", hwnd, uMsg);
//*******************************************************************

  #define Tracer2(str, num, mes) \
          { FILE* hFile = fopen( LOGFILENAME, "a+" );\
            fprintf( hFile, str, num, mes);\
            fclose( hFile );}

  #define Tracer1(str, mes) \
          { FILE* hFile = fopen( LOGFILENAME, "a+" );\
            fprintf( hFile, str, mes);\
            fclose( hFile );}

  #define Tracer(message) \
          { FILE* HFile = fopen( LOGFILENAME, "a+" );\
            fprintf( HFile, message);\
            fclose( HFile );}

//*******************************************************************
//  Пример вызова трассировки :
//   TraceCode("0x%04X|message = 0x%04X BEGIN.\n", hwnd, uMsg);
//*******************************************************************

  #define TraceCode(str, nwin, nmes) \
          { FILE* hFile = fopen( LOGFILENAME, "a+" );\
            fprintf( hFile, str, nwin, nmes);\
            fclose( hFile );}
  #define TraceMessage(message) \
          { FILE* hFile = fopen( LOGFILENAME, "a+" );\
            fprintf( hFile, message);\
            fclose( hFile );}

  #define TraceMessage2(message, v1, v2) \
          { FILE* hFile = fopen( LOGFILENAME, "a+" );\
            fprintf( hFile, message, v1, v2);\
            fclose( hFile );}

#else                         
  #define Tracer2(str, num, mes) \
          { FILE* hFile = fopen( "/maptrace.log", "a+" );\
            fprintf( hFile, str, num, mes);\
            fclose( hFile );}

  #define Tracer1(str, mes) \
          { FILE* hFile = fopen( "/maptrace.log", "a+" );\
            fprintf( hFile, str, mes);\
            fclose( hFile );}

  #define Tracer(message) \
          { FILE* HFile = fopen( "/maptrace.log", "a+" );\
            fprintf( HFile, message);\
            fclose( HFile );}

#ifdef OC2000                 
  #define TraceCode(str, nwin, nmes) \
          { printf(str, nwin, nmes); }
  #define TraceMessage(message) \
          { printf(message); }
#else
  #define TraceCode(str, nwin, nmes) \
          { FILE* hFile = fopen( "/maptrace.log", "a+" );\
            fprintf( hFile, str, nwin, nmes);\
            fclose( hFile );}
  #define TraceMessage(message) \
          { FILE* hFile = fopen( "/maptrace.log", "a+" );\
            fprintf( hFile, message);\
            fclose( hFile );}
  #define TraceMessage2(message, v1, v2) \
          { FILE* hFile = fopen( "/maptrace.log", "a+" );\
            fprintf( hFile, message, v1, v2);\
            fclose( hFile );}
#endif  //OC2000

#endif
#else
  #define Tracer2(str, num, mes)
  #define Tracer1(str, mes)
  #define Tracer(message)

  #define TraceCode(str, nwin, nmes)
  #define TraceMessage(message)
  #define TraceMessage2(message, v1, v2)
#endif


#ifdef GISWEB
  #include <stdio.h>

  extern char WebProtocol[];

  #define GisTraceCode(str, nwin, nmes) \
          { FILE* hFile = fopen( WebProtocol, "a+" );\
            fprintf( hFile, str, nwin, nmes);\
            fclose( hFile );}
  #define GisTraceMessage(message) \
          { FILE* hFile = fopen( WebProtocol, "a+" );\
            fprintf( hFile, message);\
            fclose( hFile );}
#else
#ifndef LINUXAPI
  #include <stdio.h>

  #define GisTraceCode(str, nwin, nmes) \
          { FILE* hFile = fopen( "c:\\maptrace.log", "a+" );\
            fprintf( hFile, str, nwin, nmes);\
            fclose( hFile );}
  #define GisTraceMessage(message) \
          { FILE* hFile = fopen( "c:\\maptrace.log", "a+" );\
            fprintf( hFile, message);\
            fclose( hFile );}
#else
  #define GisTraceCode(str, nwin, nmes)
  #define GisTraceMessage(message) 
#endif
#endif

#endif
