
#ifndef MAPMIND_H
#define MAPMIND_H

#ifndef MAPDATA_H
  #include "mapdata.h"
#endif  

typedef enum VALUETYPE
{
  VALUESTRDOS = 0,     // Cτςολα σινχομοχ (ASCIIZ),οηςαξιώεξξαρ ξυμεν
  VALUESTRING = 126,   // Cτςολα σινχομοχ (ANSI),οηςαξιώεξξαρ ξυμεν
  VALUESTRUNI = 127,   // Cτςολα σινχομοχ (UNICODE),οηςαξιώεξξαρ ξυμεν
  VALUECHAR   = 1,     // 1 βακτ   SIGNED CHAR
  VALUESHORT  = 2,     // 2 βακτA  SIGNED SHORT
  VALUELONG   = 4,     // 4 βακτA  SIGNED INT
  VALUEDOUBLE = 8      // 8 βακτ   DOUBLE IEEE
}
  VALUETYPE;


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++  "POINT ATTRIBUTE RECORD" ++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//  RECORD IDENTIFIER
//  RECORD LENGTH
//  SUBJECT COUNT
//  ATTRIBUTE TYPE
//  RESERVE
//  DEFAULT VALUE
// -----------------------  REPEAT --------------------------
//   SUBJECT NUMBER
//   POINTS COUNT
//    ATTRIBUTE
// ----------------------------------------------------------
//  ALIGN
//

// ---------------------------------------------------------
//  RECORD HEAD
// ---------------------------------------------------------

typedef struct MINDPOINTHEAD
{
  long  int          Ident;       // Record identifier (0x7FFFFF7F)
  long  int          Length;      // Record length
  unsigned short int Part;        // Subject count
  unsigned char      Type;        // Attribute type (VALUETYPE)
  unsigned char      Free;        // Must be zero
  unsigned char      Default[8];  // Default value
  LONGDESC Desc;                  // Subject descriptor
}
  MINDPOINTHEAD;



#endif