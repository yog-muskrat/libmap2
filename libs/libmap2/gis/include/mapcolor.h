
#ifndef MAPCOLOR_H
#define MAPCOLOR_H

#ifndef MAPMACRO_H
  #include "mapmacro.h"
#endif

#include "bascolor.h"

#ifdef __cplusplus

class _DLLCLASS TMap;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++    ����� �����    +++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TMapColors : public TBaseColors
{
 public :

  // ���������� �������� ������� �����
  TMapColors(TMap * map = 0)
  {
     MapBase = map;
     RestoreColors();
  }

  // ������������ �������� ������� �����
  void RestoreColors();

  // ��������� ����� ������ �����
  // ��� ������ ���������� ����

  int GetPaletteCount();

  // ��������� �������� ������� �� ������
  // ��� ������ ���������� ������ ������

  const char * GetPaletteName(int number);

  // ���������� ������� ������� �� ������
  // (������� ��������������� � MapColors)
  // ��� ������ ���������� ����

  COLORREF * GetPaletteByNumber(int number);

 public :

  TMap * MapBase;       // ����� � ������
};

#else

typedef TBaseColors TMapColors;

#endif // __cplusplus

#endif