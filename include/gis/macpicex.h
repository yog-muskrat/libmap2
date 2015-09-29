#ifndef PICEX_H
#define PICEX_H

#if defined(PICEX_DLL)
  #define _PICEX _export WINAPI
#else
  #define _PICEX _import WINAPI
#endif

#endif  // PICEX_H