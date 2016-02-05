
#if !defined(MOMACRO_H)
#define MOMACRO_H

#if defined(BUILD_DLLOBJ)
   #define _DLLOBJ __export
#else
   #define _DLLOBJ __import
#endif

#endif
