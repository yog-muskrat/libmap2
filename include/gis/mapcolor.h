
#ifndef MAPCOLOR_H
#define MAPCOLOR_H

#ifndef MAPMACRO_H
  #include "mapmacro.h"
#endif

#include "bascolor.h"

#ifdef __cplusplus

class _DLLCLASS TMap;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++    ЦВЕТА КАРТЫ    +++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TMapColors : public TBaseColors
{
 public :

  // Установить исходную палитру карты
  TMapColors(TMap * map = 0)
  {
     MapBase = map;
     RestoreColors();
  }

  // Восстановить исходную палитру карты
  void RestoreColors();

  // Запросить число палитр карты
  // При ошибке возвращает ноль

  int GetPaletteCount();

  // Запросить название палитры по номеру
  // При ошибке возвращает пустую строку

  const char * GetPaletteName(int number);

  // Установить текущую палитру по номеру
  // (палитра устанавливается в MapColors)
  // При ошибке возвращает ноль

  COLORREF * GetPaletteByNumber(int number);

 public :

  TMap * MapBase;       // Связь с картой
};

#else

typedef TBaseColors TMapColors;

#endif // __cplusplus

#endif