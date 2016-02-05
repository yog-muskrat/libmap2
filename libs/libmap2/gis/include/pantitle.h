#ifndef PANTITLE_H
#define PANTITLE_H

#include "mapversn.h"

#define RUS_VERSION  "Версия 9.20.0\0"
#define ENGL_VERSION "Version 9.20.0\0"

#define filemax 7      // Месяц сборки GIS ToolKit
#define filemin 4      // День сборки  GIS ToolKit 

#ifdef OPERATOR
#define ENGL_PANTITLE   "Operator 2"
#define ENGL_BACKTITLE  "Operator 2"

#define RUS_PANTITLE   "ГИС Интеграция"
#define RUS_BACKTITLE  "ГИС Интеграция"

#undef PANEDIT
#undef MAP2005
#undef PANPROM

#else

#ifdef NAVIGATOR
#define ENGL_PANTITLE   "Navigator 2005"
#define RUS_PANTITLE    "Навигатор 2005"
#define ENGL_BACKTITLE  "GIS Panorama 9"
#define RUS_BACKTITLE   "GIS Panorama 9"

#else

#ifdef MAPVIEW
#define ENGL_PANTITLE   "MapView 2005"
#define RUS_PANTITLE    "MapView 2005"

#define ENGL_BACKTITLE  "GIS Panorama 9 View"
#define RUS_BACKTITLE  "GIS Panorama 9 View"

#undef PANEDIT
#undef MAP2005
#undef PANPROM

#else

#ifdef PANEDIT    // 16/05/05
#ifdef PANVECTOR  // 11/01/06
#define ENGL_PANTITLE   "VectOr 9"
#define ENGL_BACKTITLE  "VectOr 9"

#define RUS_PANTITLE   "VectOr 9"
#define RUS_BACKTITLE  "VectOr 9"
#else
#define ENGL_PANTITLE   "Panorama Editor 9"
#define ENGL_BACKTITLE  "GIS Panorama Editor 9"

#define RUS_PANTITLE   "Панорама-Редактор 9"
#define RUS_BACKTITLE  "GIS Panorama Editor 9"
#endif
#else

#ifdef MAP2005
#define ENGL_PANTITLE   "Map 2005"
#define RUS_PANTITLE    "Карта 2005"
#ifdef PANDESK                                       // 25/10/06
 #define ENGL_BACKTITLE  "GIS Panorama 9 Desktop"
 #define RUS_BACKTITLE   "GIS Panorama 9 Desktop"
#else
 #define ENGL_BACKTITLE  "GIS Panorama 9"
 #define RUS_BACKTITLE   "GIS Panorama 9"
#endif

#else

#ifdef PANPROM

#define ENGL_PANTITLE   "GIS 2005" // 08/04/04
#define ENGL_BACKTITLE  "" //"Systemprom"

#define RUS_PANTITLE   "ГИС Акация"
#define RUS_BACKTITLE  "" //"Системпром"

#else

#ifndef RUS_PANTITLE 
#define ENGL_PANTITLE   "Panorama"
#define RUS_PANTITLE    "Панорама"
#define ENGL_BACKTITLE  "GIS Panorama 9"
#define RUS_BACKTITLE   "GIS Panorama 9"
#endif

#endif // PANPROM
#endif // MAP2005
#endif // PANEDIT 
#endif // NAVIGATOR 
#endif
#endif



#endif

