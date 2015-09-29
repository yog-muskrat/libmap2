
#ifndef MEASURE_H
#define MEASURE_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  ����� "������ ���������� ��'����"  +++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

enum
{
  tmsFIRST   = 1,  // ��������� � ������ ������ �������
  tmsSECOND  = 2,  // ��������� �� ������ ������ �������
  tmsBEHIND  = 3,  // ����� ������ ������ ����� �������
  tmsBEYOND  = 4,  // ����� ������� ������ ����� �������
  tmsBETWEEN = 5,  // ����� �� ������� (����� �������)
  tmsLEFT    = 6,  // �����
  tmsRIGHT   = 7   // ������
};

typedef struct TMEASUREDATA
{
  double A;
  double B;           // ������������ ����� Ax+By+C=0;
  double C;
  int Sign;           // ���� ���������� Distance() (-1/1)
}
  TMEASUREDATA;

//  ������������� ������
void _fastcall tmsInit(TMEASUREDATA *measuredata);

// ���� ����� ������� (p11,p12) � (p21,p22) � ��������
// ���������� ������ ����:
//   0    - ������ �����������
//   PI/2 - ������ ���������������
//  -1    - ����� ������ �� �������� ���������, ���� �� ������
double _fastcall tmsAngleBetweenLines(DOUBLEPOINT *p11, DOUBLEPOINT *p12,
                                      DOUBLEPOINT *p21, DOUBLEPOINT *p22);

// ����������� ���� ������� ����������� ����, ���������
// ������� p1,p2,p3 � �������� � ����� p2
double _fastcall tmsBisectorAngle(DOUBLEPOINT *p1, DOUBLEPOINT *p2,
                                  DOUBLEPOINT *p3);

// ����������� ������ ���������� �� ���� ������
//  pc - ����� ������
// ���������� ������ ���������� (0.0 - ��� ����� ���������,
//                              -1.0 - ����� �� ����� ������)
double _fastcall tmsCircleCenter(DOUBLEPOINT *p1, DOUBLEPOINT *p2,
                                 DOUBLEPOINT *p3, DOUBLEPOINT *pc);

// ���������� ���������� ����� ����� �������
double _fastcall tmsDistancePoint(DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);

// ���������� ���������� ����� ������ � ������,
// �������� ����� �������
double _fastcall tmsDistance(TMEASUREDATA *measuredata,
                             DOUBLEPOINT *point, DOUBLEPOINT *xy1,
                             DOUBLEPOINT *xy2);

// ���������� ������������� ���� � ��������
double _fastcall tmsDirectionAngle(DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);

// ����������� ���������� ����� � ������������ x,y
// � ������/���������
// �������: 1-����� ������ �������/����������,
//          2-����� �������,
//          3-����� ��������� � ������ �������,
//          4-����� ����� �� ������� �������,
//          0 - ��������� �������
// point   - ���������� �����
int _fastcall tmsInsidePointCut(DOUBLEPOINT *xy1, DOUBLEPOINT *xy2,
                                DOUBLEPOINT * point, double precision/* = DELTANULL*/);

// ����������� ���� ��������
// xy1,xy2 - ������ �������,
// xy3,xy4 - ������ �������
// point1,point2  - ����� �����������
// ������� : 1 - ���� ����� �����������,
//           2 - ������� xy1,xy2 �����  �� ������� xy3,xy4
// ��� ���������� ����� ����������� ��� ������ ���������� ����
int _fastcall tmsCrossCutData(TMEASUREDATA *measuredata,
                              DOUBLEPOINT *xy1, DOUBLEPOINT *xy2,
                              DOUBLEPOINT *xy3, DOUBLEPOINT *xy4,
                              DOUBLEPOINT *point1, DOUBLEPOINT *point2,
                              double precision/* = DELTANULL*/);

// ��������� ����� ������������ �������
// ���������� FIRST, SECOND, BEHIND, BEYOND, BETWEEN, LEFT, RIGHT
// ��� ������ ���������� 0
int _fastcall tmsPointPositionNearCut(DOUBLEPOINT *point,
                                      DOUBLEPOINT *xy1,
                                      DOUBLEPOINT *xy2,
                                      double precision);  

// ��������� ����� ������������ ������
// ���������� FIRST, SECOND, LEFT, RIGHT
// ��� ������ ���������� 0
int _fastcall tmsPointPositionNearLine(DOUBLEPOINT *point,
                                       DOUBLEPOINT *xy1,
                                       DOUBLEPOINT *xy2);

// ��������� (�������) ����� ������������ ������
// ���������� LEFT, RIGHT
// ��� ������ ���������� 0
int _fastcall tmsPointSideNearLine(DOUBLEPOINT *point,
                                   DOUBLEPOINT *xy1,
                                   DOUBLEPOINT *xy2);

// ���������� ��������� ����� �� �������, ������� �������
// � ��������� m1/m2
// ��� ������ ���������� 0
int _fastcall tmsPointPositionOnCut(DOUBLEPOINT *point,
                                    DOUBLEPOINT *p1,
                                    DOUBLEPOINT *p2,
                                    double m1, double m2);

// ���������� ����� ������� � ������������� ������������
//  radius - ����������,
//  angle  - ���� � ��������
double _fastcall tmsRcosInt(int radius, double angle);
double _fastcall tmsRsinInt(int radius, double angle);

double _fastcall tmsRcosDouble(double radius, double angle);
double _fastcall tmsRsinDouble(double radius, double angle);

// ����������� ���� ����� �� �������������� �� ������� (point1-point2)
// �� ���������� distance �� ����� point (�� ��������� point1)
int _fastcall tmsSeekPointNormalLine(DOUBLEPOINT *point1,
                                     DOUBLEPOINT *point2,
                                     DOUBLEPOINT *pointout1,
                                     DOUBLEPOINT *pointout2,
                                     double distance, DOUBLEPOINT *point/* = 0*/);

// ��������� ������������ ��������� ����� A,B,C
void _fastcall tmsCalcFactor(TMEASUREDATA *measuredata,
                             DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);

// ����� ����� ����������� ������� � ������ ,
// �������� �������������� A,B,C
// xy1,xy2 - �������
// point - ����������� ����� �����������
// ������� 1 - ����� ����������� ����������, 0 - ���
int _fastcall tmsCrossCutLine(TMEASUREDATA *measuredata,
                              DOUBLEPOINT *xy1, DOUBLEPOINT *xy2,
                              DOUBLEPOINT *point);

// ������������� ����� �����,
// �������� �������������� A,B,C
// point -  �����
// ������� 0 - ����� ����������� �����
double _fastcall tmsInsidePointLine(TMEASUREDATA *measuredata,
                                    DOUBLEPOINT *point);


//=================================================================
// "����������" �������������� ������� � ������� �� ���������.
//=================================================================

// ��� fabs(x) < DOUBLENULL � fabs(y) < DOUBLENULL ���������� 0
double tmsAtan2(double y, double x);

// ��� x < 0 ���������� 0
double tmsSqrt(double x);
//=================================================================


#ifdef __cplusplus

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  ����� "������ ���������� ��'����"  +++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TMeasure: public TMEASUREDATA
{
  public :

  TMeasure();

  // ���� ����� ������� (p11,p12) � (p21,p22) � ��������
  // ���������� ������ ����:
  //   0    - ������ �����������
  //   PI/2 - ������ ���������������
  //  -1    - ����� ������ �� �������� ���������, ���� �� ������
  double AngleBetweenLines(DOUBLEPOINT *p11, DOUBLEPOINT *p12,
                           DOUBLEPOINT *p21, DOUBLEPOINT *p22);

  // ����������� ���� ������� ����������� ����, ���������
  // ������� p1,p2,p3 � �������� � ����� p2

  double BisectorAngle(DOUBLEPOINT *p1, DOUBLEPOINT *p2,
                       DOUBLEPOINT *p3);

  // ����������� ������ ���������� �� ���� ������
  //  pc - ����� ������
  // ���������� ������ ���������� (0.0 - ��� ����� ���������,
  //                              -1.0 - ����� �� ����� ������)

  double CircleCenter(DOUBLEPOINT *p1, DOUBLEPOINT *p2,
                      DOUBLEPOINT *p3, DOUBLEPOINT *pc);

  // ���������� ���������� ����� ����� �������

  double Distance(DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);

  // ���������� ���������� ����� ������ � ������,
  // �������� ����� �������

  double Distance(DOUBLEPOINT *point, DOUBLEPOINT *xy1,
                                      DOUBLEPOINT *xy2);

  // ���������� ������������� ���� � ��������

  double DirectionAngle(DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);

  // ����������� ���������� ����� � ������������ x,y
  // � ������/���������
  // �������: 1-����� ������ �������/����������,
  //          2-����� �������,
  //          3-����� ��������� � ������ �������,
  //          4-����� ����� �� ������� �������,
  //          0 - ��������� �������
  // point   - ���������� �����

  int InsidePointCut(DOUBLEPOINT *xy1, DOUBLEPOINT *xy2,
                     DOUBLEPOINT *point, double precision = DELTANULL);

  // ����������� ���� ��������
  // xy1,xy2 - ������ �������,
  // xy3,xy4 - ������ �������
  // point1,point2  - ����� �����������
  // ������� : 1 - ���� ����� �����������,
  //           2 - ������� xy1,xy2 �����  �� ������� xy3,xy4
  // ��� ���������� ����� ����������� ��� ������ ���������� ����

  int CrossCutData(DOUBLEPOINT *xy1, DOUBLEPOINT *xy2,
                   DOUBLEPOINT *xy3, DOUBLEPOINT *xy4,
                   DOUBLEPOINT *point1, DOUBLEPOINT *point2,
                   double precision = DELTANULL);

  enum {
         FIRST   = tmsFIRST,  // ��������� � ������ ������ �������
         SECOND  = tmsSECOND, // ��������� �� ������ ������ �������
         BEHIND  = tmsBEHIND, // ����� ������ ������ ����� �������
         BEYOND  = tmsBEYOND, // ����� ������� ������ ����� �������
         BETWEEN = tmsBETWEEN,// ����� �� ������� (����� �������)
         LEFT    = tmsLEFT,   // �����
         RIGHT   = tmsRIGHT   // ������
       };

  // ��������� ����� ������������ �������
  // ���������� FIRST, SECOND, BEHIND, BEYOND, BETWEEN, LEFT, RIGHT
  // ��� ������ ���������� 0

  int PointPositionNearCut(DOUBLEPOINT *point,
                           DOUBLEPOINT *xy1, DOUBLEPOINT *xy2,
                           double precision = DELTANULL); 

  // ��������� ����� ������������ ������
  // ���������� FIRST, SECOND, LEFT, RIGHT
  // ��� ������ ���������� 0

  int PointPositionNearLine(DOUBLEPOINT *point,
                            DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);

  // ��������� (�������) ����� ������������ ������
  // ���������� LEFT, RIGHT
  // ��� ������ ���������� 0

  int PointSideNearLine(DOUBLEPOINT *point,
                        DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);

  // ���������� ��������� ����� �� �������, ������� �������
  // � ��������� m1/m2
  // ��� ������ ���������� 0

  int PointPositionOnCut(DOUBLEPOINT *point,
                         DOUBLEPOINT *p1, DOUBLEPOINT *p2,
                         double m1, double m2);

  // ���������� ����� ������� � ������������� ������������
  //  radius - ����������,
  //  angle  - ���� � ��������

  double Rcos(int radius, double angle);
  double Rsin(int radius, double angle);

  double Rcos(double radius, double angle);
  double Rsin(double radius, double angle);

  // ����������� ���� ����� �� �������������� �� ������� (point1-point2)
  // �� ���������� distance �� ����� point (�� ��������� point1)

  int SeekPointNormalLine(DOUBLEPOINT *point1, DOUBLEPOINT *point2,
                          DOUBLEPOINT *pointout1, DOUBLEPOINT *pointout2,
                          double distance, DOUBLEPOINT *point = 0);

 protected :

  // ��������� ������������ ��������� ����� A,B,C

  void CalcFactor(DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);

  // ����� ����� ����������� ������� � ������ ,
  // �������� �������������� A,B,C
  // xy1,xy2 - �������
  // point - ����������� ����� �����������
  // ������� 1 - ����� ����������� ����������, 0 - ���

  int CrossCutLine(DOUBLEPOINT *xy1, DOUBLEPOINT *xy2,
                   DOUBLEPOINT *point);

  // ������������� ����� �����,
  // �������� �������������� A,B,C
  // point -  �����
  // ������� 0 - ����� ����������� �����

  double InsidePointLine(DOUBLEPOINT *point);

};

#else

typedef  TMEASUREDATA  TMeasure;


#endif // __cplusplus

#endif // MEASURE_H

