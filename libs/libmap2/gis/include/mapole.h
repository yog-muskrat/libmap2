
#if !defined(MAPOLE_H)
#define MAPOLE_H

#ifndef MAPTYPE_H
 #include "maptype.h"
#endif

#include "mapversn.h"

#ifndef HIDEOLE

#define PANOLE

typedef  struct OLE_PRINTPARM
{
  RECT   Rect;            // ������� ����������� - ������� � ������
  POINT  Shift;           // �������� �� ������ ����� � ������
  double Scale;           // ����� �������� ���������� � ������� ������
  double ViewScale;       // ����������� ��������������� ������������ �������� �������� 
}
  OLE_PRINTPARM;

#endif   // HIDEOLE

#endif

