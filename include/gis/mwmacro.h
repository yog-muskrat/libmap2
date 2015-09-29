
#ifndef MWMACRO_H
#define MWMACRO_H

#ifdef BUILD_DLLTASK
  #define _DLLTASK __export WINAPI
  #define _DLLCLASSTASK __export 
#else
  #define _DLLTASK WINAPI
  #define _DLLCLASSTASK 
#endif

#endif
