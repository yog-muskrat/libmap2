
#ifndef RSTAPI_H
#define RSTAPI_H

#ifndef MAPTYPE_H
  #include "maptype.h"   // �������� �������� ���������� MAPAPI
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ �������� ������� ������� � ��������� ����� ++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifdef __cplusplus
extern "C"
{
#endif

  // ������� ��������� ������
  // ���������� ������������� �������� ��������� ����� (TMapAccess*)
  // rstname - ��� ����� ��������� �����
  // mode    - ����� ������/������ (GENERIC_READ, GENERIC_WRITE ��� 0)
  // GENERIC_READ - ��� ������ ������ �� ������
  // ��� ������ ���������� ����

_MAPIMP  HMAP _MAPAPI mapOpenRst(const char * rstname,
#ifdef __cplusplus
                          long int mode = 0);  
#else
                          long int mode);
#endif  


  // ������� ��������� ������ � �������� ������ �����
  // (�������� � ������� �������)
  // ���������� ����� ����� � ������� �������
  // hMap    - ������������� �������� ��������� �����
  // rstname - ��� ����� ��������� �����
  // mode    - ����� ������/������ (GENERIC_READ, GENERIC_WRITE ��� 0)
  // GENERIC_READ - ��� ������ ������ �� ������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapOpenRstForMap(HMAP hMap,
                                    const char * rstname,
                                    long int mode);


  // �������� ����� ���������� �����������
  // rstname    - ��� ������������ �����
  // width      - ������ ���������� ����������� � ���������
  // height     - ������ ���������� ����������� � ���������
  // nbits      - ������ �������� (��� �� ������)
  // palette    - ����� ��������������� �������
  // colorcount - ����� ��������� � ����� �������
  // scale      - �������
  // precision  - ���������� ������
  // ��� �������� ���������� ������� ������� ���� rstname � �����������
  // ��������� � �������� ������.
  //  ��� ������ ���������� 0

_MAPIMP  HMAP _MAPAPI mapCreateRst(const char * rstname,
                                long int width, long int height,
                                long int nbits,
                                COLORREF* palette, long int colorcount,
#ifdef __cplusplus  
                                double scale=0, double precision=0);  
#else
                                double scale, double precision);  
#endif


  // �������� ����� ���������� �����������
  // hMap       - ������������� �������� ��������� �����
  // rstname    - ��� ������������ �����
  // width      - ������ ���������� ����������� � ���������
  // height     - ������ ���������� ����������� � ���������
  // nbits      - ������ �������� (��� �� ������)
  // palette    - ����� ��������������� �������
  // colorcount - ����� ��������� � ����� �������
  // scale      - �������
  // precision  - ���������� ������
  // location   - �������� ���-��������� ���� ������ � ������(� ������)
  // ��� �������� ���������� ������� ������� ���� rstname � �����������
  // ��������� � �������� ������ � ��������� ��� � ������� �������
  // �������� ��������� ����� (TMapAccess*).
  // ����������  ����� ����� � ������� ������� �������� ��������� �����
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapCreateAndAppendRst(HMAP hMap,const char * rstname,
                                long int width, long int height,
                                long int nbits,
                                COLORREF* palette, long int colorcount,
                                double scale, double precision,
                                DOUBLEPOINT location);


  // ������ ����e�������� ����� ����� ��������� ����� �� �� ��������  
  // hMap       - ������������� �������� ��������� �����
  // width      - ������ ���������� ����������� � ���������
  // height     - ������ ���������� ����������� � ���������
  // nbits      - ������ �������� (��� �� ������)
  // ����������  ����e�������� ����� ����� ��������� ����� (����)
  // ��� ������ ���������� ����

_MAPIMP  double _MAPAPI mapRstFileLengthCalculation(HMAP hMap, long int width,  
                                                        long int height,
                                                        long int nbits);
  // ���������� �������
_MAPIMP  double _MAPAPI mapRtsFileLengthCalculation(HMAP hMap, long int width,
                                                        long int height,
                                                        long int nbits);


  // ������� ��������� ������ � �������� ������ �����
  // hMap   - ������������� �������� ��������� �����
  // number - ����� ���������� ����� � �������
  // ���� number == 0, ����������� ��� ��������� ������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapCloseRstForMap(HMAP hMap,
                                     long int number);


  // ������� ��������� ������
  // hMap   - ������������� �������� ��������� �����
  // number - ����� ������������ ������
  // ���� number == 0, ����������� ��� ������ � ����

_MAPIMP  void _MAPAPI mapCloseRst(HMAP hMap,
#ifdef __cplusplus  
                           long int number = 0);  
#else
                           long int number);  
#endif


  // ��������� ��� ����� ��������� ������
  // hMap   - ������������� �������� ��������� �����
  // number - ����� ����� � �������
  // ��� ������ ���������� ������ ������

_MAPIMP  const char * _MAPAPI mapGetRstName(HMAP hMap,long int number);

  // ��������� ��� ����� ��������� ������ � ��������� UNICODE
  // hMap   - ������������� �������� ��������� �����
  // number - ����� ����� � �������
  // name - ����� ������ ��� ���������� ����������
  // size - ������ ������
  // ��� ������ ���������� ������ ������

_MAPIMP  long int _MAPAPI mapGetRstNameUn(HMAP hMap,long int number,
                                          WCHAR * name, long int size);

  // ��������� ����� �������� ������ ��������� ������
  // hMap    - ������������� �������� ��������� �����
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstCount(HMAP hMap);


  // ������ �������� ������ ������  
  // hMap    - ������������� �������� ��������� �����
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstCurrentNumber(HMAP hMap);


  // ��������� �������� ������ ������  
  // hMap    - ������������� �������� ��������� �����
  // number  - ����� ������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapSetRstCurrentNumber(HMAP hMap,long int number);


  // ���������/���������� ������� ��������� ������
  //  hMap   - ������������� �������� ��������� �����
  //  number - ����� ����� � �������
  //  view = 0 - �� �����
  //  view = 1 - ������ ���������
  //  view = 2 - ����������
  //  view = 3 - ��������������
  //  view = 4 - �������
  //  view = 5 - ����������

_MAPIMP  long int _MAPAPI mapGetRstView(HMAP hMap,long int number);
_MAPIMP  long int _MAPAPI mapSetRstView(HMAP hMap,long int number,
                                           long int view);


  // ���������� ������� ��������� ������ �������
  //  userLabel  - ���������������� ����� ������
  //                -1             - ��� ������
  //                RSW_QUALITY    - ������ �������
  //                RSW_VISIBILITY - ������ ���������
  //                RSW_WEB        - ��������� ����� ��� WEB
  //  view - ������� ���������
  //                0 - �� �����
  //                1 - ������
  //                2 - ����������
  //                3 - ��������������
  //                4 - �������
  //                5 - ����������
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapSetRstGroupView(HMAP hMap,long int userLabel,
                                                long int view);      

  // ���������/���������� ������� ����������� ������
  // hMap   - ������������� �������� ��������� �����
  // number - ����� ���������� ����� � �������
  //  (0 - ��� ������, 1 - ��� ������)
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapSetRstViewOrder(HMAP hMap, long int number,
                                      long int order);
_MAPIMP  long int _MAPAPI mapGetRstViewOrder(HMAP hMap, long int number);


  // �������� ����������� ����������� ������� (rst) � �������  
  // ��������� ����� � ������� ������������ � ��������� �������
  // ��������� ������� � ������� ���������� � 1 � ������������� ������� mapGetRstCount(..)
  //   oldNumber - ����� ����� � �������
  //   newNumber - ��������������� ����� ����� � �������
  //  ��� ������ ���������� 0

_MAPIMP long int _MAPAPI mapChangeOrderRstShow(HMAP hMap, long int oldNumber,
                                                          long int newNumber);

  // �������� ����������� ����������� ��������� ������ � ������� �������  
  // ��������� ����� � ������� ������������ � ��������� �������
  // ��������� ������� � ������� ���������� � 1 � ������������� ������� mapGetRstCount(..)
  //     oldNumber - ����� ����� � �������
  //     newNumber - ��������������� ����� ����� � �������
  //  ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapChangOrderRstInChain(HMAP hMap, long int oldNumber,
                                                             long int newNumber);

  // ���������������� �������� ������� ��� ������
  // ���� ��� ������ ������������ ��� ������, ��
  // ������ ����� ����� ��������� ��� ������. ��� ���������
  // ������ ������ ����� ����� ��������� ��� ������, ��������� -
  // ��� ������. ����� ���������� ������ � ������ ��� ������ -
  // ��� ������ ��� ������. ����� - ����� ������ ����� ��� ������.
  // ���������� ����� ������ ������������� ��� ������ ��� ����.
  // ��� ��������� ���������� �� ������ - ����� ����� ������������
  // hMap    - ������������� �������� ��������� �����

_MAPIMP  long int _MAPAPI mapTurnRstViewOrder(HMAP hMap);


  // ��������� ���������� ������ � ������� ������
  // hMap   - ������������� �������� ��������� �����
  // number - ����� ����� � �������
  // ��� ������ ������������ 0

_MAPIMP  long int _MAPAPI mapGetRstColorCount (HMAP hMap, long int number);


  // ��������� �������� ������� ������
  // hMap    - ������������� �������� ��������� �����
  // palette - ����� ������� ��� ���������� �������
  // count   - ����� ����������� ��������� �������
  //           (���� count > 256, �� ������������ ����)
  // number  - ����� ����� � �������
  // (������ ������� � ������ / 4)
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstPalette(HMAP hMap, COLORREF * palette,
                                    long int count,
                                    long int number);


  // ���������� �������� ������� ������
  // hMap    - ������������� �������� ��������� �����
  // palette - ����� ��������������� �������
  // count   - ����� ��������� � ����� �������
  // number  - ����� ����� � �������
  // ���� palette ����� 0, ��������������� ������� �� ���������  
  // count �� ����� 256
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapSetRstPalette(HMAP hMap, COLORREF * palette,
                                    long int count,
                                    long int number);


  // ��������� �������� ��������� ������� ������
  // (��� ����� ������� � ������������)
  // hMap    - ������������� �������� ��������� �����
  // palette - ����� ������� ��� ���������� �������
  // count   - ����� ����������� ��������� �������
  //           (���� count > 256, �� ������������ ����)
  // number  - ����� ����� � �������
  // (������ ������� � ������ / 4)
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstStandardPalette(HMAP hMap, COLORREF * palette,
                                    long int count,
                                    long int number);


  // ��������� ������� ������� ������
  // hMap   - ������������� �������� ��������� �����
  // number - ����� ����� � �������

_MAPIMP  long int _MAPAPI mapGetRstBright (HMAP hMap,long int number);


  // ��������� ������������� ������� ������
  // hMap   - ������������� �������� ��������� �����
  // number - ����� ����� � �������

_MAPIMP  long int _MAPAPI mapGetRstContrast (HMAP hMap,long int number);


  // ��������� ���������������� ������
  // hMap   - ������������� �������� ��������� �����
  // number - ����� ����� � �������

_MAPIMP  long int _MAPAPI mapGetRstTranslucency(HMAP hMap,long int number);


  // ��������� �������������� ������� ������
  // hMap   - ������������� �������� ��������� �����
  // number - ����� ����� � �������

_MAPIMP  long int _MAPAPI mapGetRstGamma (HMAP hMap,long int number);



  // ���������� ������� ������� ������
  // hMap   - ������������� �������� ��������� �����
  // number - ����� ����� � �������
  // bright - �������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapSetRstBright (HMAP hMap, long int bright,
                                               long int number);


  // ���������� ������������� ������� ������
  // hMap     - ������������� �������� ��������� �����
  // number   - ����� ����� � �������
  // contrast - ��������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapSetRstContrast (HMAP hMap, long int contrast,
                                                 long int number);

  // ���������� �������� ������������ ������
  // hMap   - ������������� �������� ��������� �����
  // number - ����� ����� � �������
  // translucency - �������� ������������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapSetRstTranslucency (HMAP hMap, long int translucency,
                                                 long int number);



  // ���������� �������������� ������� ������
  // hMap   - ������������� �������� ��������� �����
  // number - ����� ����� � �������
  // gamma  - �������������� �������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapSetRstGamma (HMAP hMap, long int gamma,
                                              long int number);


  //  �������� �������� ������� � ������� �������� � ��������������
  //  hMap   - ������������� �������� ��������� �����
  //  number - ����� ����� � �������
  //  ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapRestoreRstPalette(HMAP hMap, long int number);


  // ��������� �������� �������� ������
  //  hMap   - ������������� �������� ��������� �����
  //  number - ����� ����� � �������
  // ���� ����������� ������ ���������� - ���������� ����
  // ���� ����������� ������ ���������� - ���������� 1
  // ��� ������ ���������� -1

_MAPIMP  long int _MAPAPI mapCheckInversionRst(HMAP hMap,long int number);


  // ������������� ��������� �����
  // hMap   - ������������� �������� ��������� �����
  // number - ����� ����� � �������
  // value:
  // 0 - ���������� ����������� ������ ����������
  // 1 - ���������� ����������� ������ ����������
  //  ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapInvertRst(HMAP hMap,long int number, long int value);


  // ��������� ��������� ����� (��� 16- � 256-������� �������)  
  //  hMap   - ������������� �������� ��������� �����
  //  number - ����� ����� � �������
  //  index  - ������ ����� � ������� ������(������� � 0)
  //  ����������: 1 - ���� � ������ �������� ������������
  //              0 - ���� � ������ �������� �� ������������
  //  ��� ������ ���������� -1

_MAPIMP  long int _MAPAPI mapCheckVisibilityColor(HMAP hMap, long int number,
                                                      long int index);


  // ���������� ��������� ����� (��� 16- � 256-������� �������)  
  //  hMap   - ������������� �������� ��������� �����
  //  number - ����� ����� � �������
  //  index  - ������ ����� � ������� ������(������� � 0)
  //  value: 1 - �������� ����������� ����� � ������ ��������
  //         0 - ��������� ����������� ����� � ������ ��������
  //  ���������� ��������� ������ � INI-�����
  //                                  (�� ��������� � �������� ����� ������)
  //  ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapSetVisibilityColor(HMAP hMap, long int number,
                                                    long int index,
                                                    long int value);


  // ���������� ��������� ����� (��� 16- � 256-������� �������)  
  //  hMap   - ������������� �������� ��������� �����
  //  number - ����� ����� � �������
  //  index  - ������ ����� � ������� ������(������� � 0)
  //  value: 1 - �������� ����������� ����� � ������ ��������
  //         0 - ��������� ����������� ����� � ������ ��������
  //  ���������� ��������� ������ � ��������� ����� ������(� ����� � INI-�����)
  //  ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapSetVisibilityColorInRstFile(HMAP hMap, long int number,
                                                  long int index,
                                                  long int value);


  // ��������� ���� � ��� ����� ������  
  // hMap      - ������������� �������� ��������� �����
  // maskType  - ���� �����(0 - ����� �����������)
  // maskStep  - ��� �����
  // number - ����� ����� � �������

_MAPIMP  long int _MAPAPI mapGetRstMaskType (HMAP hMap,long int number,
                                      long int* maskType, long int* maskStep);


  // ���������� ���� � ��� ����� ������  
  // hMap      - ������������� �������� ��������� �����
  // maskType  - ���� �����(0 - ����� �����������)
  // maskStep  - ��� �����
  // number - ����� ����� � �������

_MAPIMP  long int _MAPAPI mapSetRstMaskType (HMAP hMap,long int number,
                                      long int maskType, long int maskStep);


  // ���������� ������� ������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // scale      - ����������� ��������
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapSetRstScale(HMAP hMap,long int number,double scale);


  // ��������� ������� ������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // scale      - ��������� ����������, ���� �������� �������� ��������
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapGetRstScale(HMAP hMap,long int number,double *scale);


  // ��������� �������� �������� ������ � ������� ������ ��������� ������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // �� ������ bottomScale ������������ ����������� �������� ������ ������� ��������� ������
  // �� ������ topScale ������������ ����������� �������� ������� ������� ��������� ������
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapGetRstRangeScaleVisible(HMAP hMap,long int number,
                       long int *bottomScale, long int *topScale);  


  // ���������� �������� �������� ������ � ������� ������ ��������� ������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // bottomScale   - ����������� �������� ������ ������� ��������� ������
  // topScale   - ����������� �������� ������� ������� ��������� ������
  //              bottomScale <= topScale, ����� ���������� 0
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapSetRstRangeScaleVisible(HMAP hMap,long int number,
                      long int bottomScale, long int topScale);   


  // ���������� ���������� ������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // precision  - ���������� ������, ���������� ��� ������������ (����� �� ����)
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapSetRstPrecision(HMAP hMap,long int number,double precision);


  // ��������� ���������� ������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // precision  - ���������� ������ (����� �� ����)
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapGetRstPrecision(HMAP hMap,long int number,double *precision);


  // ���������� ����� ������ �� ������� ���������� �������
  // ��������� ������ ������ ����� �� ����� 4-� �����
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // info       - ��������� ������ �����
  // ����� ���������� ������� ����������� ������ ����������� �������� ��������
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapSetRstBorder(HMAP hMap,long int number,HOBJ info);


  // ��������� ������ ����� ������               
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // info       - ������������� ������� �����
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstBorder(HMAP hMap,long int number,HOBJ info);


  // ������� ����� ������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ����� ���������� ������� ����������� ������ ����� ������
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapDeleteRstBorder(HMAP hMap,long int number);


  // ����������� ������������� ����� ������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapCheckExistenceRstBorder(HMAP hMap,long int number);


  // ��������� ����������� ������ �� �����
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // value  = 1 - ���������� ����� �� �����
  //        = 0 - ���������� ����� ��� ����� �����

_MAPIMP  long int _MAPAPI mapShowRstByBorder(HMAP hMap,long int number, long int value);

  // ����������� ������� ����������� ������(������������ �����)
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ���������� 1 - ��� ����������� ������ �� �����
  //            0 - ��� ����������� ������ ��� ����� �����
  // ��� ������ ���������� -1

_MAPIMP  long int _MAPAPI mapCheckShowRstByBorder(HMAP hMap,long int number);

  // ���������� ���������� ����� �����, �������  
  // ������ � ������������� �������� ������(�������) �
  // ����� ���������� �������� �� ����� pointIn (���������� � ������).
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // �� ������ pointOut ������������ ���������� ��������� ����� � ������
  // ��� ������ ��� ���������� ����� ���������� 0.

_MAPIMP  long int _MAPAPI mapGetImmediatePointOfRstBorder(HMAP hMap, long int number,
                                           DOUBLEPOINT* pointIn,
                                           DOUBLEPOINT* pointOut);


  // ��������� ������ � �������� ������  
  // number      - ����� ����� � �������
  // mapregister - ����� ���������, � ������� ����� ���������
  // ������ � ��������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstProjectionData(HMAP hMap, int number,
                                                  MAPREGISTEREX* mapregister);


  // ��������� ������ � �������� ������ �� ����� �����  
  // name        - ��� ����� ������
  // mapregister - ����� ���������, � ������� ����� ���������
  // ������ � ��������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstProjectionDataByName(const char* name,
                                                  MAPREGISTEREX* mapregister);

  // ���������� ������ � �������� ������  
  // number - ����� ����� � �������
  // mapregister - ����� ���������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapSetRstProjectionData(HMAP hMap, int number,
                                                  MAPREGISTEREX* mapregister);

  // ��������� �������� ������ � ������ � ������ �����
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // frame      - ������������ �������� ������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstFrameMeters(HMAP hMap,DFRAME *frame, long int number);


  // ��������� ����������� �������� ������������� ������ � ������ � ������ �����   
  // ��� ����������� ������ �� ����� ������������ �������� �����
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // frame      - ������������ �������� ������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetActualRstFrame(HMAP hMap,DFRAME *frame, long int number);


  // ���������� �������� ������ � ������ �����(� ������)
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // location   - ���������� ���-��������� ���� ������(� ������)
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapSetRstLocation(HMAP hMap,long int number, DOUBLEPOINT* location);


  // ��������� �������� ������ � ������ �����(� ������)
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // location   - ���������� ���-��������� ���� ������(� ������)
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapGetRstLocation(HMAP hMap,long int number, DOUBLEPOINT *location);


  // ��������� ���� ������������� �������� ������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapCheckExistenceRstLocation(HMAP hMap,long int number);




  //**********************************************************************
  // ��� ��������� ����� �� ������� (Dx,Dy)?
  //    ��������� �������� ������ - mapGetRstLocation(...)
  //    �������� ����� �������� �� ������� (Dx,Dy)
  //    ���������� ����� ����� �������� - mapSetRstLocation(...)
  //    ����������� ����.
  //**********************************************************************
  // ��� ��������� ����� � ���������� �������� ?
  //    ��������� �������� ������ - mapGetRstLocation(...)
  //    ��������� ����������� �������� ������ - mapGetRstScale(...)
  //    �������� ����� �������� � ���������� ����������� ��������
  //    ���������� ����� ����� �������� - mapSetRstLocation(...)
  //    ���������� ����� ����������� �������� - mapSetRstScale(...)
  //    ����������� ����.
  //**********************************************************************


  // ��������� ������ �������� ������ � ������ �� ���������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // metinelem  - ������ �������� ������ � ������ �� ���������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstMeterInElement(HMAP hMap,long int number,double *metinelem);


  // ��������� ������ ����� ������ � ��������� ������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // eleminpix  - ������ ����� ������ � ��������� ������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetSizeRstElemInPix(HMAP hMap,long int number,double *eleminpix);


  // ��������� ������ ������ � ���������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstWidth(HMAP hMap,long int number);


  // ��������� ������ ������ � ���������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstHeight(HMAP hMap,long int number);


  // ��������� ����� ������ � ������        
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP  unsigned long int _MAPAPI mapGetRstLength(HMAP hMap,long int number);


  // ��������� ������ �������� ������ � �����
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstElementSize(HMAP hMap,long int number);


  // ��������� ���� ��������������� ������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapCheckRstEdit(HMAP hMap,long int number);


  // ��������� ����� ��������� ������ ������ (0 - ����� �� ����)
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapCheckRstCompressNumber(HMAP hMap,long int number);


  // ������ �������� �� ���������� ��������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // string, column - ������ � ������� ��������
  // value      - �������� ��������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstPoint(HMAP hMap, long int number,long int *value, long int string, long int column);


  // ������ �������� �� ���������� ��������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // string, column - ������ � ������� ��������
  // value      - �������� ��������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapPutRstPoint(HMAP hMap, long int number,long int value, long int string, long int column);


  // ������ ��������  �� ��� ������������� �����������
  // (� ������) �� ������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // x,y        - ���������� ��������
  // value      - �������� ��������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstPlanePoint(HMAP hMap, long int number,long int *value, double x, double y);


  // ������ �������� �� ��� ������������� ����������� �� ������ �������������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // x,y        - ���������� ��������
  // value      - �������� ��������
  // ��� ������ ���������� ����              

_MAPIMP  long int _MAPAPI mapGetRstPlanePointTriangle(HMAP hMap, long int number,long int *value, double x, double y);


  // ����������� ����� ����� ������ �� ������������� ����������� ����� 
  // (� ������)
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // x,y        - ���������� ��������
  // color      - ���� ��������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstPlanePointColor(HMAP hMap, long int number,
                                            COLORREF* color, double x, double y);

  // ������ ��������  �� ��� ������������� �����������
  // (� ������) � �����
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // x,y        - ���������� ��������
  // value      - �������� ��������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapPutRstPlanePoint(HMAP hMap, long int number,long int value, double x, double y);


  // ������ ������� � ����������� ��������� ������ �� ������������� ����������� (� ������)  
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // color - ���� ������� ���� COLORREF ��� ������� � 16,24,32 ����� �� �������;
  //         ������ ����� � ������� ��� ������� � 1,4,8 ����� �� �������.
  //  point1 - ���������� ��������� ����� �������
  //  point2 - ���������� �������� ����� �������
  // ��� ������ ���������� ����
_MAPIMP  long int _MAPAPI mapPutRstPlaneLine(HMAP hMap, long int number, long color,
                                      DOUBLEPOINT *point1, DOUBLEPOINT *point2);


  // ��������� ���������� ������ ������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstBlockCount(HMAP hMap,long int number);


  // ��������� ����� ����� ������ ������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstBlockRow(HMAP hMap,long int number);


  // ��������� ����� �������� ������ ������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstBlockColumn(HMAP hMap,long int number);


  // ��������� ������ ������������ ����� ������ � ������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstBlockSize(HMAP hMap,long int number);


  // ��������� ������ �������� ����� {string,column} ������ � ������
  // (� ������ ��������� ������)
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // string, column - ���������� �����
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstCurrentBlockSize(HMAP hMap,long int number,
                                             long int string,long int column);


  // ��������� ������ ������������ ����� ������ � ���������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstBlockWidth(HMAP hMap,long int number);


  // ��������� ������ ������������ ����� ������ � ���������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstBlockHeight(HMAP hMap,long int number);


  // ��������� ������ �������� ����� {string,column} ������ � ���������
  // (� ������ ��������� ������)
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // column     - ������� �����
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstCurrentBlockWidth(HMAP hMap,long int number,
                                              long int column);


  // ��������� ������ �������� ����� {string,column} ������ � ���������
  // (� ������ ��������� ������)
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // string     - ������ �����
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstCurrentBlockHeight(HMAP hMap,long int number,
                                               long int string);


  // ��������� ����� ����� ������ �� ������ ������ � �������
  // ����� ���������� ���� ����� ����� ��������� ������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // string     - ������ �����
  // column     - ������� �����
  // ��� ������� ���������� ����� ����� ������� ������� �����
  // ��� ������ ���������� ����, ����� - ����� ���������� �����

_MAPIMP  char *  _MAPAPI mapGetRstBlock(HMAP hMap,long int number,
                                 long int string,
                                 long int column);


  // ��������� ����� ����� ������ �� ������ ������ � �������
  // ��� ���������� � ����� - ���������
  // ��� ������� ���������� ����� ����� ������� ������� �����
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // string     - ������ �����
  // column     - ������� �����
  // ��� ������ ���������� ����
_MAPIMP  char *  _MAPAPI mapGetRstBlockAndCreate(HMAP hMap,long int number,
                                 long int string,
                                 long int column);


  // ��������� ������� ����� ������ � �����
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // i          - ���������� ����� �����
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapCheckRstBlockExistence(HMAP hMap,long int number,long int i);


  // ������� ����� ����������� �����
  // (0 - �� ������������, 1- ������������, 2 - �������� ������ )
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // i          - ���������� ����� �����
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapCheckRstBlockVisible(HMAP hMap,long int number,long int i);  


  // ������ ����� {string,column} � ���� ���������� �����������  �� ������ bits.
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // string     - ������ �����
  // column     - ������� �����
  // bits       - ��������� �� ������ ����������� ������� �������
  // sizebits   - ������ ������� bits � ������
  // ���������� ���������� ���������� ����.
  // ��� ������ ���������� ����.

_MAPIMP  long int _MAPAPI mapWriteRstBlock(HMAP hMap,long int number,
                                long int string, long int column,
                                char * bits, long int sizebits);


  // ������ ����� {string,column} �������� "size" �� DIB-����� "mask"
  // �������� "value"
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // string     - ������ �����
  // column     - ������� �����
  // mask       - ��������� �� ������ �����
  // size       - ������ ������� mask � ������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapPutRstBlockByMask(HMAP hMap,long int number,
                                long int string, long int column,
                                char* mask, long int size,
                                long int width,long int height,
                                long value);


  // �������� ��������� ������ � ����
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapSaveRst(HMAP hMap,long int number);


  // ������ �������������� ������� ������
  //  hMap    - ������������� �������� ��������� �����
  //  number  - ����� ����� � �������
  //  bits    - ��������� �� ������ ����������� ������� �������
  //  left    - �������� ����� � ��������� (��������� �� ������� �����)
  //  top     - �������� ������ � ���������
  //  width   - ������ � ��������� (��������� �� ������� �����)
  //  height  - ������ � ���������
  //  begining  - ������ �����������:
  //    ==  1  - (bits - ��������� �� ������ ������ ������� �������)
  //    == -1  - (bits - ��������� �� ��������� ������ ������� �������,
  //                           � BMP ����������� �������� ����� - �����)
  //  widthinbyte    - ������ �������������� ������� ������ � ������
  // ������� ������������:
  //  ��� ElementSize() == 1 (���) - left,width ������ 8,
  //                    == 4 (���) - left,width ������ 2
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapPutRstFrame(HMAP hMap, long int number, char* bits,
                                  long int left, long int top,
                                  long int width, long int height,
#ifdef __cplusplus  
                                  long int begining/* = 1*/,
                                  long int widthinbyte /*= 0*/);  
#else
                                  long int begining,
                                  long int widthinbyte);
#endif

  // ������ �������������� ������� ������
  //  hMap       - ������������� �������� ��������� �����
  //  number     - ����� ����� � �������
  //  bits    - ��������� �� ������ ����������� ������� �������
  //  left    - �������� ����� � ��������� (��������� �� ������� �����)
  //  top     - �������� ������ � ���������
  //  width   - ������ � ��������� (��������� �� ������� �����)
  //  height  - ������ � ���������
  //  widthinbyte    - ������ �������������� ������� ������ � ������
  // ������� ������������:
  //  ��� ElementSize() == 1 (���) - left,width ������ 8,
  //                    == 4 (���) - left,width ������ 2
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapGetRstFrame(HMAP hMap, long int number, char* bits,
                                  long int left, long int top,
                                  long int width, long int height,
#ifdef __cplusplus  
                                  long int widthinbyte = 0);
#else
                                  long int widthinbyte);
#endif

  // ������ �������� ���������� �������������� ������� ������
  //  hMap       - ������������� �������� ��������� �����
  //  number     - ����� ����� � �������
  //  bitsR,bitsG - ��������� �� ������ ����������� �������� ��������
  //  bitsB         �������, ������� � ����� ���������
  //  left    - �������� ����� � ���������
  //  top     - �������� ������ � ���������
  //  width   - ������ � ���������
  //  height  - ������ � ���������
  //  ������������ ������ 8-������ ������ (����)
  // ��� ������ ���������� 0

_MAPIMP  long int _MAPAPI mapGetRstFrameRGB(HMAP hMap, long int number,
                          char* bitsR, char* bitsG, char* bitsB,
                          long int left, long int top,
                          long int width, long int height);


  // ����������� �������������� ������� ��������� ������    
  // � �������������� ������, ������������� � ������� ������.
  //   hMap   - ������������� �������� ��������� �����
  //   number - ����� ����� � �������
  //   bits   - ��������� �� ������ ������� ������;
  //   width  - ������ ������� ������ � ��������� COLORREF
  //            (���������� �������� ��������������� ������);
  //   height - ������ ������� ������ � ���������
  //            (���������� ����� ��������������� ������);
  //   StrL,ColL,StrR,ColR - ���������� ������ � ������� ���������
  //                         ��������� ������, ������� ����������
  //                         ������� ��������� ������� ��������������
  //                         �������.
  // ��� ������ ���������� ����.

_MAPIMP  long int _MAPAPI mapGetRstFrameTurn(HMAP hMap,        
                      long int number, COLORREF* bits,
                      long int width, long int height,
                      double StrL, double ColL,
                      double StrR, double ColR);


  // ����������� �������� ������ � ������� 
  // ��� �������� �������� �����������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // element    - �������� ������
  // pixel      - ��������� � ��������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapRstElementToPixel(HMAP hMap, long int number,
                                        double element,double *pixel);


  // ����������� ������� � �������� ������
  // ��� �������� �������� �����������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // element    - ��������� � ��������� ������
  // pixel      - �������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapPixelToRstElement(HMAP hMap, long int number,
                                        double pixel, double *element);


  // ������������ ������� ����� �������� ����� {string,column} 
  // � ������ ����� ������
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // string     - ������ �����
  // column     - ������� �����
  // bits       - ������� ������� �����
  // size       - ������ ������� ������� ����� � ������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapBuildRstBlockMask(HMAP hMap, long int number,
                                        char * bits, long int size,
                                        long int string, long int column);

  // ���������� ����� ����������� ������ �� ������� �������    
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // info       - ������ ����� � ������������
  // ����� ���������� ������� ����������� ������ ����������� �������� ��������
  // ��� ������ ���������� 0
_MAPIMP  long int _MAPAPI mapSetRstMask(HMAP hMap,long int number,HOBJ info);

  // ������� ������ ����� ������, ������������ ������.  
  // hMap       - ������������� �������� ��������� �����
  // number     - ����� ����� � �������
  // ��� ������ ���������� 0
_MAPIMP  long int _MAPAPI mapFillRstVisiblePart (HMAP hMap, long int number, long int color);

  // �������� ����������� �����   
  // ���� ����������� ����� �� ����������, ��������� ���� �����
  // hMap   - ������������� �������� ��������� �����
  // number - ����� ����� � �������

_MAPIMP  long int _MAPAPI mapUpdateRstDuplicates (HMAP hMap, long int number);

  // �������� ����������� ����� ����� (string,column) ������       
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapUpdateRstDuplicateOfBlock(HMAP hMap, long int number,
                                          int string, int column);

  // ��������� ���������������� ������������� ������
  // number    - ����� ����� � �������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapGetRstUserLabel(HMAP hMap, long int number);   

  // ���������� ���������������� ������������� ������
  // number    - ����� ����� � �������
  // userLabel - ������������� ������
  // ��� ������ ���������� ����

_MAPIMP  long int _MAPAPI mapSetRstUserLabel(HMAP hMap, long int number,
                                             long int userLabel);           

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // RSTAPI_H