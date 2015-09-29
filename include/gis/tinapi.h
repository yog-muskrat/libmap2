
#ifndef TINAPI_H
#define TINAPI_H

#ifndef MAPTYPE_H
  #include "maptype.h"   // �������� �������� ���������� MAPAPI
#endif

#ifndef MAPCREAT_H
  #include "mapcreat.h"
#endif

#ifndef TINBASE_H
  #include "tinbase.h"
#endif
  
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ �������� ������� ������� � TIN-������ +++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern "C"
{
  // ��������� ����� �������� TIN-������
  // ��� ������ ���������� 0

  long int _MAPAPI mapGetTinCount(HMAP hMap);

  // ������� TIN-������ � �������� ������ ����� (�������� � �������)
  // ���������� ����� ����� � �������
  // ��� ������ ���������� 0
  long int _MAPAPI mapOpenTinForMap(HMAP hMap,
                                    const char * tinname,
                                    long int mode);

  // ������� TIN-������ � �������� ������ �����
  // number - ����� ����� ������ � �������
  // ���� number == 0, ����������� ��� ������
  // ��� ������ ���������� 0
  long int _MAPAPI mapCloseTinForMap(HMAP hMap, long int number);

  // ����� �������� ������ ����������� TIN-������ � �������� �����
  // ������ ����������� ������������� �� TIN-������ � �������
  // ������� ����� � �������.
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ������� TIN-������ ���������� ERRORHEIGHT.
  double _MAPAPI mapGetSurfaceHeight(HMAP hMap, double x, double y);

  // ����� �������� ������ ����������� TIN-������ � �������� �����
  // �� ����� � ������� number � �������.
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ������� TIN-������ ���������� ERRORHEIGHT.
  double _MAPAPI mapGetTinSurfaceHeight(HMAP hMap, long int number,
                                        double x, double y);

  // ������ ������������ �� ������� ������������� TIN-������
  // number - ����� TIN-����� � �������
  // index - ������ � ������� �������������
  // ��� ������ ���������� 0
  long int _MAPAPI mapGetTinTriangle(HMAP hMap, long int number,
                                     TINTRIANGLE* triangle, long int index);

  // ���������/���������� ������� ��������� TIN-������
  //  hMap   - ������������� �������� �������� ��������� �����
  //  number - ����� ����� � �������
  //  view = 0 - �� �����
  //  view = 1 - ������
  _MAPIMP long int _MAPAPI mapGetTinView(HMAP hMap,long int number);
  _MAPIMP long int _MAPAPI mapSetTinView(HMAP hMap,long int number,
                                         long int view);

  // ���������/���������� ������� ����������� TIN-������
  //  hMap   - ������������� �������� �������� ��������� �����
  //  number - ����� ����� � �������
  //  order  - ������� (0 - ��� ������, 1 - ��� ������)
  // ��� ������ ���������� 0 					 
  _MAPIMP long int _MAPAPI mapGetTinViewOrder(HMAP hMap, long int number);
  _MAPIMP long int _MAPAPI mapSetTinViewOrder(HMAP hMap, long int number,
                                              long int order);
}

#endif // TINAPI_H

