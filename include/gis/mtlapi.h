
#ifndef MTLAPI_H
#define MTLAPI_H

#ifndef MAPTYPE_H
  #include "maptype.h"   // �������� �������� ���������� MAPAPI
#endif

#ifndef MAPCREAT_H
  #include "mapcreat.h" 
#endif

//------------------------------------------------------------------
//  ��������� �������� ������� �����
//------------------------------------------------------------------
typedef struct BUILDMTL     // ������ ��������� 160 ����
{
  unsigned
  long int StructSize;     // ������ ������ ��������� :
                           //  sizeof (BUILDMTL)
  long int Free;           // ������ ���� ����

  double   BeginX;         // ������������� ���������� ������
  double   BeginY;         // (���-��������� ����) ������� � ������

  double   EndX;           // ������������� ���������� ���������
  double   EndY;           // (������ - ���������� ����) ������� � ������

  double   ElemSizeMeters; // ������ ������� ������������� �������
                           // � ������ �� ���������

  long int LayerCount;     // ���������� �����

  long int LayerForm;      // ����� ������������� ���-��� � �����
                           // ���������� �������� :
                           //  0 - �������� �����
                           //  1 - ��������� ������

  long int HeightSizeBytes; // ������ ������ ������� � ������
                            // ���������� �������� :
                            //  0 - ������ �����������,
                            //  2 - ������ "short int"
                            //  4 - ������ "long int"

  long int LayerSizeBytes;  // ������ �������� ���� � ������
                            // ���������� �������� :
                            //  1 - �������� "unsigned char"
                            //  2 - �������� "unsigned short int"
                            //  4 - �������� "unsigned long int"

  long int HeightMeasure;  // E������ ��������� ������
                           // ���������� �������� :
                           //  0 - �����
                           //  1 - ���������
                           //  2 - ����������
                           //  3 - ����������

  long int LayerMeasure;   // E������ ��������� �������� ����
                           // ���������� ��������
                           // - �� ��,��� ��� HeightMeasure

  long int UserType;       // ������������ �����, �����������
                           // � ����������� ��������

  long int Scale;          // �������

  char     Reserve[80];    // ������ ���� ����
}
  BUILDMTL;


//------------------------------------------------------------------
//  ��������� �������� ������� ����� (���������� ���������)
//------------------------------------------------------------------
typedef struct MTLBUILDPARM     // ������ ��������� 128 ����
{
  unsigned
  long int StructSize;     // ������ ������ ��������� :
                           //  sizeof (MTRLAYERBUILDPARM)

  double   BeginX;         // ������������� ���������� ������
  double   BeginY;         // (���-��������� ����) ������� � ������

  double   EndX;           // ������������� ���������� ���������
  double   EndY;           // (������ - ���������� ����) ������� � ������

  double   ElemSizeMeters; // ������ ������� ������������� �������
                           // � ������ �� ���������

  long int LayerCount;     // ���������� �����

  long int LayerForm;      // ����� ������������� ���-��� � �����
                           // ���������� �������� :
                           //  0 - �������� �����
                           //  1 - ��������� ������

  long int HeightSizeBytes; // ������ ������ ������� � ������
                            // ���������� �������� :
                            //  0 - ������ �����������,
                            //  2 - ������ "short int"
                            //  4 - ������ "long int"

  long int LayerSizeBytes;  // ������ �������� ���� � ������
                            // ���������� �������� :
                            //  1 - �������� "unsigned char"
                            //  2 - �������� "unsigned short int"
                            //  4 - �������� "unsigned long int"

  long int HeightMeasure;  // E������ ��������� ������
                           // ���������� �������� :
                           //  0 - �����
                           //  1 - ���������
                           //  2 - ����������
                           //  3 - ����������

  long int LayerMeasure;   // E������ ��������� �������� ����
                           // ���������� ��������
                           // - �� ��,��� ��� HeightMeasure

  long int UserType;       // ������������ �����, �����������
                           // � ����������� ��������

  long int Scale;          // �������

  char     Reserve[52];     // ������ ���� ����
}
  MTLBUILDPARM;


//------------------------------------------------------------------
//  �������� �������� ������� ����� (������ ��������� 1024 �����)
//------------------------------------------------------------------
typedef struct MTLDESCRIBE
{
  char  Name[260];              // ��� ����� �������
  char  MaterialFileName[260];  // ��� ����� �������� ����������

  long  LayerCount;      // ���-�� �����
  long  MaterialCount;   // ���-�� ����������

  double ElementInPlane; // ������ �������� � ������ �� ���������

  DFRAME FrameMeters;    // �������� ������� � ����� (�����)

  double MinHeightValue; // ����������� �������� ������ �������� � ������� (�����)
  double MaxHeightValue; // ������������ �������� ������ �������� � ������� (�����)

  double BotLevelHeight; // ������ �������� ������� ������� ������ (�����)  

  long   UserType;       // ��� ���������������� ������
  long   View;           // ������� ��������������
  long   UserLabel;      // ���������������� �������������
  long   ReliefPresence; // ������� ������� �������  

  double MaxSummaryPower; // ������������ ��������� ��������
                          // �����  (�����)  

  char   Reserve[408];   // ������

}
  MTLDESCRIBE;

// �������� - ���������� ����� ������� � ������ �������,
//            ��������������� ��'����� ���� �� ���,
//            ���������������� �������������� ���������
//            (����������� ����� �����).

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ �������� ������� ������� � �������� ����� +++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern "C"
{

  // ������� ��������� ������
  // ���������� ������������� �������� ��������� ����� (TMapAccess*)
  // ��� ������ ���������� ����

  HMAP _MAPAPI mapOpenMtl(const char * mtrname,
                          long int mode = 0);

  // ������� ��������� ������ � �������� ������ �����
  // (�������� � ������� ������)
  // ���������� ����� ����� � ������� ������
  // ��� ������ ���������� ����

  long int _MAPAPI mapOpenMtlForMap(HMAP hMap,
                                    const char * mtrname,
                                    long int mode);

  // ������� ��������� ������
  // number - ����� ����������� �������
  // ���� number == 0, ����������� ��� ������� � ����

  void _MAPAPI mapCloseMtl(HMAP hMap,long int number = 0);

  // ������� ��������� ������ � �������� ������ �����
  // number - ����� ���������� ����� � �������
  // ���� number == 0, ����������� ��� ��������� ������
  // ��� ������ ���������� ����

  long int _MAPAPI mapCloseMtlForMap(HMAP hMap,
                                     long int number);

  // ���������� ������� �� �������� ������� ������ �����
  // ��� ������ ���������� ����
  // hMap    - �������� ����� ��� ���������� �������,
  // mtrname - ������ ��� ����� ����������� �������,
  // ininame - ������ ��� ����� ������� ����������� �������,
  // mtrparm - ��������� ����������� �������,
  // hselect - ������������� ��������� ������ �������� �����,
  // handle   - ������������� ���� �������, �������� ����������
  // ��������� � ���� �������� :
  //  0x0378 - ��������� � �������� ����������� ����� (� WPARAM),
  //  ���� ������� ������ ���� ������������� ��������, � �����
  //  ������ ��������� �������� 0x0378.
  // ���� handle ����� ���� - ��������� �� ����������.

  long int _MAPAPI mapBuildMtlEx(HMAP hMap,
                                 const char * mtrname,
                                 const char * ininame,
                                 BUILDMTL * mtrparm,
                                 HSELECT  hselect,
                                 HWND     handle);

  // ���������� ������� �� �������� ������� ������ ����� (����������)
  // ��� ������ ���������� ����
  // hMap    - �������� ����� ��� ���������� �������,
  // mtrname - ������ ��� ����� ����������� �������,
  // ininame - ������ ��� ����� ������� ����������� �������,
  // mtrparm - ��������� ����������� �������,
  // hselect - ������������� ��������� ������ �������� �����,
  // handle  - ������������� ���� �������, �������� ����������
  // ��������� � ���� �������� :
  //  0x0378 - ��������� � �������� ����������� ����� (� WPARAM),
  //  ���� ������� ������ ���� ������������� ��������, � �����
  //  ������ ��������� �������� 0x0378.
  // ���� handle ����� ���� - ��������� �� ����������.

  long int _MAPAPI mapBuildMtl(HMAP hMap,
                               const char * mtrname,
                               const char * ininame,
                               MTLBUILDPARM * mtrparm,
                               HSELECT  hselect,
                               HWND     handle);


  /*********************************************************
  *                                                        *
  *           ������ ������ �� ������� �����               *
  *                                                        *
  *********************************************************/

  // ��������� �������� ����� ��������� ������
  // number - ����� ����� � �������
  // describe - ����� ���������, � ������� ����� ���������
  // �������� �������
  // ��� ������ ���������� ����

  long int _MAPAPI mapGetMtlDescribe(HMAP hMap,long int number,
                                     MTLDESCRIBE * describe);

  // ��������� ��� ����� ��������� ������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  const char * _MAPAPI mapGetMtlName(HMAP hMap,long int number);

  // ��������� ����� �������� ������ ��������� ������
  // ��� ������ ���������� ����

  long int _MAPAPI mapGetMtlCount(HMAP hMap);

  // ��������� ������������ ���������� ����� ���� ������ MTL-�������
  // ��� ������ ���������� ����

  long int _MAPAPI mapGetMaxLayerCount(HMAP hMap);

  // ��������� ���������� ����� ������� � ������� number � �������.
  // ��� ������ ���������� ����

  long int _MAPAPI mapGetLayerCountOfMtl(HMAP hMap,long int number);

  // ��������� ����������� ������ ������� ������
  // ��� ������ ���������� ERRORHEIGHT

  double _MAPAPI mapGetMinBotLevelHeight(HMAP hMap);    

  // ��������� ������������ ��������� �������� �����
  // ��� ������ ���������� ERRORPOWER

  double _MAPAPI mapGetMaxSummaryPower(HMAP hMap);    

  // ����� �������� ���������� ������ � �������� �����.
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ���������� ������� ���������� ERRORHEIGHT.

  double _MAPAPI mapGetElementHeight(HMAP hMap,double x,double y);

  // ����� �������� ���������� ������ � �������� ����� �� �������
  // � ������� number � �������.
  // number - ����� ������� � �������.
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ���������� ������� ���������� ERRORHEIGHT.

  double _MAPAPI mapGetElementHeightOfMtl(HMAP hMap,long int number,double x,double y);

  // ����� �������� �������� ���� � �������� �����.
  // layernumber - ����� ����.
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� �������� ���� � ������.
  // � ������ ������ � � ������ ���������������� ��������
  // ����� ���������� ������� ���������� ERRORPOWER.

  double _MAPAPI mapGetElementPower(HMAP hMap,double x,double y,long layernumber);

  // ����� �������� �������� ���� � �������� ����� �� �������
  // � ������� number � �������.
  // layernumber - ����� ����.
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� �������� ���� � ������.
  // � ������ ������ � � ������ ���������������� ��������
  // ����� ���������� ������� ���������� ERRORPOWER.

  double _MAPAPI mapGetElementPowerOfMtl(HMAP hMap,long int number,
                                         double x,double y,long layernumber);

  // ���������� �������� ��������� ����� � �������� �����
  // ������� ������������� �� ������� � ������� number � �������.
  // ���������� ����� �������� � ������ � ������� ���������
  // ��������� �����.
  // powers - ����� ������� ��� ������ ����������� ��������
  //          ��������� (� ������)
  // count - ������ �������, ������ ���� �� ����� TMtl::LayerCount().
  // ���������� ���������� ����������� ��������� ������� powers.
  // ��� ������ ���������� ����.

  long int _MAPAPI mapGetElementPowersTriangleOfMtl
                      (HMAP hMap,long int number,
                       double x,double y,
                       double* powers,long int count);

  // ���������� �������� �������� ���� layernumber � �������� �����
  // ������� ������������� �� ������� � ������� number � �������.
  // ���������� ����� �������� � ������ � ������� ���������
  // ��������� �����.
  // ���������� �������� �������� ���� � ������.
  // ��� ������ ���������� ERRORPOWER.

  double _MAPAPI mapGetElementPowerTriangleOfMtl  
                   (HMAP hMap,long int number,
                    double x,double y,long int layernumber);

  // ��������� �������� ���������� ������ � ������� �������,
  // ��������������� �������� �����.
  // number - ����� ������� � �������.
  // ���������� ����� (x,y) � �������� ������ (h) �������� � ������
  // � ������� ��������� ��������� �����.
  // � ������ ������ ���������� ����.

  long int _MAPAPI mapPutElementHeight(HMAP hMap,long int number,
                                       double x, double y, double h);


  // ��������� �������� �������� ���� layernumber � �������,
  // ��������������� �������� �����.
  // number - ����� ������� � �������.
  // ���������� ����� (x,y) � �������� �������� (power) ��������
  // � ������ � ������� ��������� ��������� �����.
  // � ������ ������ ���������� 0.

  long int _MAPAPI mapPutElementPower(HMAP hMap,long int number,
                                      double x,double y,double power,
                                      long int layernumber);

  // ��������� ����� � ������� ��� �������, �������������
  // � �������� �����
  // number - ���������� �����, ��������� ������� � �����
  // (1 - ������ � ������ �����, 2 - ������ ...)
  // ��� ������ ������������ ����

  long int _MAPAPI mapGetMtlNumberInPoint(HMAP hMap,double x, double y,
                                          long int number);
                                          
  // ��������� ����� � ������� ��������� �������� �������
  // � ������������� (������ 1) ��������� ���������.
  // ��� ������ ������������ ����

  long int _MAPAPI mapGetMtlNumberLastVisible(HMAP hMap);

  // ��������� ������ ������� ����� ������� � ������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  long int _MAPAPI mapGetMtlBlockSize(HMAP hMap,long int number);

  // ��������� ����� ����� ������� �� ������ ������ � �������
  // ����� ���������� ���� ����� ����� ��������� ������
  // number - ����� ����� � �������
  // ��� ������� ���������� ����� ����� ������� ������� �����
  // ��� ������ ���������� ����, ����� - ����� ���������� �����

  char *  _MAPAPI mapGetMtlBlockAddress(HMAP hMap,long int number,
                                                  long int row,
                                                  long int column);

  // ��������� ����� ����� ������ �������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  long int _MAPAPI mapGetMtlBlockRow(HMAP hMap,long int number);

  // ��������� ����� �������� ������ �������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  long int _MAPAPI mapGetMtlBlockColumn(HMAP hMap,long int number);

  // ��������� ����� ����� ��������� � �������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  long int _MAPAPI mapGetMtlElementRow(HMAP hMap,long int number);

  // ��������� ����� �������� ��������� � �������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  long int _MAPAPI mapGetMtlElementColumn(HMAP hMap,long int number);

  // ����� ������� �������� ���������� �����, ���������������
  // ���������� ���������, ������� �� �������� �������.
  // ���������� �����, �������� ������ � ����� �������
  // (FirstPoint,SecondPoint) �������� � ������ � �������
  // ��������� ��������� �����.
  // ������ ������� �����, ��������� ������� HeightArray,
  // ������ ��������������� �������������� ���������� �����
  // (HeightCount), � ��������� ������ �������� ������ ������
  // � �������.
  // � ������ ���������������� ����������� �������� ����������
  // ������� ��� �������� ����� ERRORHEIGHT (-111111.0 �)
  // � ������ ������ ��� ������ ����� ���������� ����.

  long int _MAPAPI mapGetHeightArrayFromMtl(HMAP   hMap,
                                            double*   HeightArray,
                                            long int  HeightCount,
                                            DOUBLEPOINT*  FirstPoint,
                                            DOUBLEPOINT*  SecondPoint);


  // ����� �������� ����� ���� layernumber.
  // number - ����� ������� � �������
  // � ������ ������ ���������� ����.

  COLORREF _MAPAPI mapGetLayerColor(HMAP hMap,long int number,long int layernumber);

  // ����� ��������� ����� (���� ���������) ���� layernumber.
  // number - ����� ������� � �������
  // � ������ ������ ���������� ����.

  char* _MAPAPI mapGetLayerShortName(HMAP hMap,long int number,long int layernumber);

  // ����� ����� (�������� ���������) ���� layernumber.
  // number - ����� ������� � �������
  // � ������ ������ ���������� ����.

  char* _MAPAPI mapGetLayerLongName(HMAP hMap,long int number,long int layernumber);

  // ����� ������������ �������� ���� layernumber � ������.
  // number - ����� ������� � �������
  // � ������ ������ ���������� ����.

  long int _MAPAPI mapGetMaxLayerHeight(HMAP hMap,long int number,long int layernumber);

  // ��������� ������������ �������� ���� layernumber � ������.
  // number - ����� ������� � �������
  // � ������ ������ ���������� ����.

  long int _MAPAPI mapSetMaxLayerHeight(HMAP hMap,long int number,long int layernumber,long int maxlayerheight);

  // ��������� �������� ����� ���� layernumber.
  // number - ����� ������� � �������
  // � ������ ������ ���������� ����.

  long int _MAPAPI mapSetLayerColor(HMAP hMap,long int number,
                                    long int layernumber,
                                    COLORREF layercolor);

  // ��������� ��������� ����� (���� ���������) ���� layernumber.
  // number - ����� ������� � �������
  // � ������ ������ ���������� ����.

  char* _MAPAPI mapSetLayerShortName(HMAP hMap,long int number,
                                     long int layernumber,
                                     char* layername);

  // ��������� ����� (�������� ���������) ���� layernumber.
  // number - ����� ������� � �������
  // � ������ ������ ���������� ����.

  char* _MAPAPI mapSetLayerLongName(HMAP hMap,long int number,
                                    long int layernumber,
                                    char* layername);

  // ��������� ������ � �������� ��������� ������
  // number - ����� ����� � �������
  // projectiondata - ����� ���������, � ������� ����� ���������
  // ������ � ��������
  // ��������a MTRPROJECTIONDATA ������a � maptype.h
  // ��� ������ ���������� ����

  long int _MAPAPI mapGetMtlProjectionData
                     (HMAP hMap,long int number,
                      MTRPROJECTIONDATA * projectiondata);

  /*********************************************************
  *                                                        *
  *     �������� ������� ��� �������� ������ �����         *
  *                                                        *
  *********************************************************/

  // ������� ��������� �����
  // ���������� ������������� �������� ��������� ����� (TMapAccess*)
  // ��������a BUILDMTL ������a � mtlapi.h
  // ��� ������ ���������� ����

  HMAP _MAPAPI mapCreateMtlEx(const char * mtrname,
                              BUILDMTL * mtrparm);

  // ������� ���� �������
  // hmap -  ������������� �������� ��������� �����
  // mtrname - ������ ��� ����� �������
  // ��������a BUILDMTL ������a � mtlapi.h
  // ��������a MTRPROJECTIONDATA ������a � maptype.h
  // ����������  ����� ����� � ������� ������
  // ��� ������ ���������� ����

  long int _MAPAPI mapCreateAndAppendMtlEx(HMAP hMap,
                                           const char * mtrname,
                                           BUILDMTL * mtrparm,
                                           MTRPROJECTIONDATA * mtrprojectiondata);

  // ������� ��������� ����� (����������)
  // ���������� ������������� �������� ��������� ����� (TMapAccess*)
  // ��������a MTLBUILDPARM ������a � mtlapi.h
  // ��� ������ ���������� ����

  HMAP _MAPAPI mapCreateMtl(const char * mtrname,
                            MTLBUILDPARM * mtrparm);

  // ������� ���� ������� (����������)
  // hmap -  ������������� �������� ��������� �����
  // mtrname - ������ ��� ����� �������
  // ��������a MTLBUILDPARM ������a � mtlapi.h
  // ��������a MTRPROJECTIONDATA ������a � maptype.h
  // ����������  ����� ����� � ������� ������
  // ��� ������ ���������� ����

  long int _MAPAPI mapCreateAndAppendMtl(HMAP hMap,
                                         const char * mtrname,
                                         MTLBUILDPARM * mtrparm,
                                         MTRPROJECTIONDATA * mtrprojectiondata);

                                           
  // �������� ��������� ������� � ����
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  long int _MAPAPI mapSaveMtl(HMAP hMap,long int number);

  // ���������� �������� ������������ ��������� �������
  // number   - ����� ������� � �������
  // minvalue - ����������� �������� ������������� ��������
  //            � �������� �������
  // maxvalue - ������������ �������� ������������� ��������
  //            � �������� �������
  // ��� ������ ���������� 0

  long int _MAPAPI mapSetMtlShowRange(HMAP hMap,
                                      long int number,
                                      double minvalue,
                                      double maxvalue);

  // ���������� ������ ������� ����� �������
  // number - ����� ������� � �������
  // botlevel - ������ ������� ����� � ������
  // ��� ������ ���������� 0

  long int _MAPAPI mapSetMtlBotLevel(HMAP hMap,
                                     long int number,
                                     double botlevel);

  // ���������� ������������ ��������� �������� ����� �������
  // maxsummarypower - ������������ ��������� �������� � ������
  // ��� ������ ���������� 0

  long int _MAPAPI mapSetMtlMaxSummaryPower(HMAP hMap,
                                            long int number,
                                            double maxsummarypower);

  // ���������� ������ � �������� ��������� ������
  // number - ����� ����� � �������
  // mapregister - ����� ���������, ���������� ������ � ��������
  // ��������a MAPREGISTEREX ������a � mapcreat.h
  // ��� ������ ���������� ����

  long int _MAPAPI mapSetMtlProjectionData(HMAP hMap,      
                                           long int number,
                                           MAPREGISTEREX* mapregister);

                                            
  /*********************************************************
  *                                                        *
  *   �������� ������� ��� ������ � ������ ������� �����   *
  *                                                        *
  *********************************************************/

  // ���������� ����� ������� �� ������� ���������� �������
  // ��������� ������ ������ ����� �� ����� 4-� �����
  // number     - ����� ����� � �������
  // info       - ��������� ������ �����
  // ����� ���������� ������� ����������� ������� ����������� �������� ��������
  // ��� ������ ���������� 0

  long int _MAPAPI mapSetMtlBorder(HMAP hMap,long int number,HOBJ info);

  // ��������� ������ ����� �������               
  // number     - ����� ����� � �������
  // ��� ������ ���������� ����

  long int _MAPAPI mapGetMtlBorder(HMAP hMap,long int number,HOBJ info);

  // ������� ����� �������
  // number     - ����� ����� � �������
  // ����� ���������� ������� ����������� ������� ����� ������
  // ��� ������ ���������� 0

  long int _MAPAPI mapDeleteMtlBorder(HMAP hMap,long int number);

  // ����������� ������������� ����� �������
  // ���� ����� ������� ���������� ���������� 1, ����� ���������� 0

  long int _MAPAPI mapCheckExistenceMtlBorder(HMAP hMap,long int number);

  // ����������� ������� ����������� �������(������������ �����)    
  // ���������� 1 - ��� ����������� ������� �� �����
  //            0 - ��� ����������� ������� ��� ����� �����
  // ��� ������ ���������� -1

  long int _MAPAPI mapCheckShowMtlByBorder(HMAP hMap,long int number);

  // ���������� ���������� � ���������� ����� ����� �����, ������� 
  // ������ � ������������� �������� ������(�������) �
  // ����� ���������� �������� �� ����� pointIn (���������� � ������).
  // �� ������ pointOut ������������ ���������� ��������� ����� � ������
  // ��� ������ ��� ���������� ����� ���������� 0.

  long int _MAPAPI mapGetImmediatePointOfMtlBorder(HMAP hMap, long int number,
                                           DOUBLEPOINT* pointIn,
                                           DOUBLEPOINT* pointOut);

  // ��������� ����������� �������� ������������ ������� � ������ � ������ �����   
  // ��� ����������� ������� �� ����� ������������ �������� �����
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  long int _MAPAPI mapGetActualMtlFrame(HMAP hMap,DFRAME *frame, long int number);

  // ��������� ������� �������
  // number - ����� ����� � �������
  // ��� ������ ���������� ����

  long int _MAPAPI mapGetMtlScale(HMAP hMap,long int number);

  // ��������� �������� �������� ������ � ������� ������ ��������� �������
  // number     - ����� ����� � �������
  // �� ������ bottomScale ������������ ����������� �������� ������ ������� ��������� �������
  // �� ������ topScale ������������ ����������� �������� ������� ������� ��������� �������
  // ��� ������ ���������� 0
  long int _MAPAPI mapGetMtlRangeScaleVisible(HMAP hMap,long int number, long int *bottomScale, long int *topScale);  

  // ���������� �������� �������� ������ � ������� ������ ��������� �������
  // number     - ����� ����� � �������
  // bottomScale   - ����������� �������� ������ ������� ��������� �������
  // topScale   - ����������� �������� ������� ������� ��������� �������
  //              bottomScale <= topScale, ����� ���������� 0
  // ��� ������ ���������� 0
  long int _MAPAPI mapSetMtlRangeScaleVisible(HMAP hMap,long int number, long int bottomScale, long int topScale);   


  /*********************************************************
  *                                                        *
  *          ���������� ������������ �������               *
  *                                                        *
  *********************************************************/

  // ���������/���������� ������� ��������� �������
  //  number - ����� ����� � �������
  //  view = 0 - �� �����
  //  view = 1 - ������
  //  view = 2 - ����������
  //  view = 3 - ��������������
  //  view = 4 - �������
  //  view = 5 - ����������

  long int _MAPAPI mapGetMtlView(HMAP hMap,long int number);
  long int _MAPAPI mapSetMtlView(HMAP hMap,long int number,
                                           long int view);


}

#endif // MTLAPI_H
