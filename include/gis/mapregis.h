#if !defined(MAPREGIS_H)
#define MAPREGIS_H

#ifndef MAPCREAT_H
  #include "mapcreat.h"
#endif

// ���������� ���������� ������ � ����������� �� ���� �����
void _fastcall mrRegisterFromMapType(MAPREGISTEREX * mapregister,
                                     int maptype);

// ������������� ���������� ������
void _fastcall mrClear(MAPREGISTEREX * data);
void _fastcall lrClear(LISTREGISTER * data);


#ifdef __cplusplus

class _DLLCLASS TMap;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  ����� "�������� ����� �����" +++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

struct _DLLCLASS TListRegister : public LISTREGISTER,
                                 public REGISTERTYPES
{
 public:


 TListRegister()
 {
   Clear();
 }

 ~TListRegister(){};

 // ������������� ���������� ������

 void Clear();

 // ����������� ����������� �����������
 // ��� ������� ������������� ���������
 // scale - ����������� ��������
 // maptype - ��� �����
 // ��� ������ ���������� 0

 int FactorScaleGeodetic(long scale, int maptype);

 // ������ ��������� ���� � ������������� ������� "��������"
 char *SystDate(char *date, int lenstring);


 // �������� ������������� ���������
 int CheckRightAngle(void);


 // �������� ������������� ���������
 int CheckGeodetic(void);


 // ���������� ������������� ���������� � ��������� ListRegister
 // X, Y - ������������� ���������� (� ������)
 int RightAngleCordinames(COORDINATES *X, COORDINATES *Y);


 // ������������ ����� ����� �� ������������
 // file - ����� ��� ��� �����
 // lenfile - ����� ������ ��� ��� �����
 // nomenclature - ������������ �����
 // ��� ������ ���������� 0
 int NameFileFromNomenclature(char *file, int lenfile,
                              char *nomenclature);

 // �������� ������������
 // nomenclature - ������������
 // type - ��� �����
 // scale - �������
 int CheckNomenclature(char *nomenclature, int type, long int scale);

 // �������� ������������
 // ��� �������� ������-�������
 // factorscale - ���������� ����������
 //               ��� ������� ������������� ���������
 int CheckNomenclatureTopo(char *nomenclature, int factorscale);


 // �������� ������������ ��� �������-�������������� ����
 // factorscale - ���������� ����������
 //               ��� ������� ������������� ���������
 int CheckNomenclatureGeog(char *nomenclature, int factorscale);

 // �������� ������������ ��� ����������������� ����
 // factorscale - ���������� ����������
 //               ��� ������� ������������� ���������
 int CheckNomenclatureAero(char *nomenclature, int factorscale);


 // �������� ������������ ��� ���� ��������������� ���� ������
 // factorscale - ���������� ����������
 //               ��� ������� ������������� ���������
 // �� �������� !!!
 int CheckNomenclatureCityPlan(char *nomenclature, int factorscale);

};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  ����� "�������� ������ �����" ++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

struct _DLLCLASS TMapRegister : public MAPREGISTEREX,
                                public REGISTERTYPES
{
 public:

 TMapRegister()
 {
   SetValueType();
   Clear();
 }

 ~TMapRegister(){};

 //  ���������� �������� � �������� ���
 //  - ����� ����
 //  - ������ ���������
 //  - ���� ����������
 //  - ������� �����
 //  - ������� ���������
 //  - ��������
 //  - ���� ��������� ���������
 //  - ���� ���
 //  - ���� �������
 //  - ���� �����

 void SetValueType();


 // ������������� ���������� ������
 void Clear();


 // ���������� ���������� ������ � ����������� �� ���� �����
 void RegisterFromMapType(int maptype);

 // ���������� ���������� ������
 void RegisterFromData(MAPREGISTEREX * mapreg,LISTREGISTER * listreg);

 // ����������� ����������� �����������
 // ��� ������� ������������� ���������
 // scale - ����������� ��������
 // maptype - ��� �����
 // ��� ������ ���������� 0
 int FactorScaleGeodetic(long scale, int maptype);


 // ����������� ������� ��������� ���� (� �������) �� ������������
 // 0.X-XX - ������ ������ ������������, ��� XX - ����� ����
 int CalcAxisMeridianMinute(char *nomenclature);


 // ����������� ������� ��������� ���� (� ��������) �� ������������
 // 0.X-XX - ������ ������ ������������, ��� XX - ����� ����
 // ��� ������ ���������� 0
 double CalcAxisMeridian(char *nomenclature);


 // ����������� ������� ��������� ���� (� ��������)
 // �� ������������� ����������� �����
 double CalcAxisMeridian(COORDINATES *L);


 // ��������� ������ �� ���������    
 int PrepareRegister(int datpro = 0);


 // ��������� �������� ������� ��������� ������ �� ������������
 // 0.X-XX - ������ ������ ������������, ��� XX - ����� ����
 // ��� ������ (���� �� ��������� � ��� ������������ AxisMeridian)
 // ���������� 0
 int SetAxisMeridian(char *nomenclature);


 // ��������� �������� ������� ��������� ������
 // �� ����������� �����
 // ��� ������ (���� �� ��������� � ��� ������������ AxisMeridian)
 // ���������� 0
 int SetAxisMeridian(COORDINATES *L);


 // ���������� ������������� ��������� B, L
 // ��� ������������� �������� ������-�������
 // �� ������������ � ����������� ����������� 1,2,3,4,5,6...
 // 0.X-XX - ������ ������ ������������,
 // 0(1) - ���������, X - ����, XX - ����� ����
 // ��� ������ ���������� 0
 // ��� ���������� ���������� ���������� B,L � ��������
 int GeodeticsCoordinateGauss(char *nomenclature, int factorscale,
                              COORDINATES *B, COORDINATES *L);


 // ���������� ��������� ���������� (� ��������)
 // �� ������������� ����������� (� ��������) �
 // ������� ��������� (� ��������)
 double GridConvergence(COORDINATES *B, COORDINATES *L,
                        double axismeridian);


 // ������ ������������� ��������� ����� �� �������������
 // B, L - ������������� ����������
 // X, Y - ������������� ����������
 // projection - ��������
 // map - �����, � �������� ���������
 // ��� ������ (������������ ������ ��� ��������) ���������� 0

 int GeodeticToRightAngle(COORDINATES *B, COORDINATES *L,
                          COORDINATES *X, COORDINATES *Y,
                          int projection, TMap *map = 0);


 // ������ ������������� ��������� ����� �� �������������
 // B, L - ������������� ����������
 // X, Y - ������������� ����������
 // projection - ��������
 // map - �����, � �������� ���������
 // ��� ������ (������������ ������ ��� ��������) ���������� 0

 int RightAngleToGeodetic(COORDINATES *X, COORDINATES *Y,
                          COORDINATES *B, COORDINATES *L,
                          int projection, TMap *map = 0);


 // ���������� ��������� CONSTPROJ � ����������� �� ��������
 // �������� ������ ������������ � ������ TTranslate
 // ��� ������ (���������� �������� ��������) ���������� 0
 int SetConstproj(int projection, CONSTPROJ *constproj);


 //  ����� ����� ������� ���������
 //  maptype - ��� �����
 long int *GetAddrScale(int maptype);


 //  ����� ����� ��������� � ������� ���������
 //  maptype - ��� �����
 int GetCountScale(int maptype);


 //  ����� ����� ������� �������� ����������
 //  maptype - ��� �����
 char **GetAddrPicture(int maptype);


 // ������ ������ �� ���� ��������������� �����
 // ������������� �������� ������-�������
 // ������� ������ : ������������,
 //                  ����������� ��������
 //                  �������� ��������� ���������
 // �������� ������: ������������� ����������,
 //                  ������������� ����������,
 //                  ������� �����,
 //                  ��������� ����������
 int TopographicChartSheet(char *nomenclature,
                          long scale,
                          int projection = GAUSSCONFORMAL, TMap *map = 0);

 //  ���������� ���� DataProjection
 void SetDataProjection();

 private:

 // ������� ����� (0.00) � �������
 double MinuteToRadian(double minute);

 // ������� ������ (0.00) � �������
 double SecondToRadian(double sec);

 public:


// �������� ����� �����
TListRegister ListRegister;

// ������� ������������ �������� � �����
// ��� �����
int TableMapType[COUNTMAPTYPE];

// ������� ���������
int TableUnit[COUNTUNIT];

// ������� ��������� �� ������
int TableUnitHeight[COUNTUNITHEIGHT];

// ��� ����������
int TableEll[COUNTELL];

// ������� �����
int TableHeight[COUNTHEIGHT];

// ������� ���������
int TableCoord[COUNTCOORD];

// ��������
int TableProj[COUNTPROJ];

// ��� ��������� ���������
int TableMapInitKind[COUNTMAPINITKIND];

// ��� ���
int TableMapInitType[COUNTMAPINITTYPE];

// ��� �������
int TablePhoto[COUNTPHOTO];

// ��� �����
int TableFrame[COUNTFRAME];

// ���� ��������� ��� �������
int TableBlock[COUNTGEOGRAPHICCODE];
};

#endif  // __cplusplus

#endif
