#ifndef M3DMODEL_H
#define M3DMODEL_H

#include "m3dgdi.h"

typedef struct IMG3DANGLE     // ���� �������� (�� 1 ������� �������)
{                             //
  double AngleX;              // �� ���� � ���� X (� �������� � ����� �������)
  double AngleY;              // �� ���� � ���� Y
  double AngleZ;              // �� ���� � ���� Z
}
  IMG3DANGLE;


typedef struct FIXATION       // C�������� ��� �������� �����������
{
  IMG3DPOINT Offset;          // �������� ������������ 1 ����� ������
  IMG3DANGLE Angle;           // ������� ������������ ������� ������� �������
  IMG3DPOINT Factor;          // ������ - ���������� �� ����
}
  FIXATION;

typedef struct WRAPIMAGE      // C�������� ��� ������� ����������� (40 ����)
{
  char       FlagHeight;      // ���� ������� �� ������
                              // ��. TEXTUREMEASURE(m3dgdi.h)
  char       WrapHeight;      // ������ �� ���������� ��� �� ������� �� ������
  char       FlagVector;      // ���� ������� �� ����������� ������� ��������
                              // ��. TEXTUREMEASURE(m3dgdi.h)
  char       WrapVector;      // ������ �� ����������
                              // ��� �� ������� �� ������� ��������
  long       Reserv;          //
  IMG3DVALUE ValueHeight;     // �������� ������� �� ������
  IMG3DVALUE ValueVector;     // �������� ������� �� ������� ��������
}
  WRAPIMAGE;


enum IMAGETYPE      // ��� ��������� �����������
   {
     rscIMGTREE    = 0,  // ����������� ������
     rscMODEL      = 1   // ����������� ������
   };

typedef struct IMAGEHEAD      // �������� �� �����������
{
  long       Length;          // ����� ����� ���������
  long       Key;             // ���� ������ ��� �������
  long       Code;            // ��� ����������, ��� �������� ������ ��� ������
  char       Flag;            // ��� ��������� ��.IMAGETYPE
  char       Cut;             // ���� ������� �� ��������� (1 - ��������, 0 - ���)
  char       Stretch;         // ���� ������������ (1 - �����������, 0 - ���)
  char       Reserv[5];       //
  IMG3DVALUE Heigth;          // ����� ������ ����������� (��������,
                              // ������ �� ���������)
  IMG3DVALUE RelativeHeight;  // ������������� ������ ����������� (��������,
                              // ������ �� ���������
                              // ��� ������� ��� ����� ������������)
  WRAPIMAGE Wrap;             // ������ ��� ������� �����������
  FIXATION  Fixator;          // ������ ��� �������� �����������
                              // � ����� ��������� ������
  long Count;                 // ���������� ����� ��� ����������� �������
                              // (��� ������ = 0)
//IMG3DPOINT  Point[Count];   // ����� ����� o�������� �������
                              // (�� 2 ����� �� �������)
}
 IMAGEHEAD;


typedef struct DESCMODEL      // �������� ������
{
  long Length;                // ����� �����
  long Count;                 // ���������� ����������� �������
  long Rezerv[2];             // ������
  IMAGEHEAD Head[1];          // ��������� ����������� ����������� �������
                              // ���� ���������� ������ (��������� ��� �������)
}
  DESCMODEL;

typedef struct M3DMODEL          // C�������� ������
{
  unsigned long Ident;        // ������������� ������
  long          Length;       // �����
  long          Form;         // ����
                              // (������ ��� �������� ������)
  long          Reserv1;      // ������
  IMG3DPOINT    Base[2];      // ������ ��� �������� �������
                              // ���������� ����� ������ ��������� �� �������
  long          Count;        // ���������� ����� ����� ��������� ������
  long          Reserv2;      // ������
 //IMG3DPOINT  Point[Count];  // ����� ����� ��������� ������ (�� 2 ����� �� �������)
 //DESCMODEL   Desk;          // �������� ������
}
  M3DMODEL;


typedef struct PACKET         // ����� ������� ��� �������
{
  long      Length;           // �����
  long      Count;            // ���������� �������
  // long       Key;          // ���� ������ ��� �������
  // long       Code;         // ��� ����������, ��� �������� ������ ��� ������
}
  PACKET;

#endif





