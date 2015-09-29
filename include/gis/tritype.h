
#ifndef TRIANGLETYPE_H
#define TRIANGLETYPE_H

// ������������ �������/������ ������� � �������
#if defined(_DELONE_DLL)
  #define _DELONECLASS _export
#else
  #define _DELONECLASS _import
#endif

// ��������� � �������� ����������� �����
#define IDC_PERCENT_DELONE     0x3000

#define TR_ONLY           0
#define TR_THICKEN        1
#define TR_FACTORIZATION  2

// ����������� ������ ������� ������
#define VERTEXCOUNT     50000  

// ����������� ������ ������� �������������
#define TRIANGLECOUNT  150000  


// ������������� ����������� ������������
// (��������� �� TConstTriangle)

typedef long int HTRIANG;


// ��������� ������� �������������   (56 ����)

typedef struct
{
  long int A;         // ������ ������ ������������
  long int B;
  long int C;

  long int EdgeAB;    // ������ ң��� ������������
  long int EdgeBC;
  long int EdgeCA;

  long int NearAB;    // ������ �������� �������������
  long int NearBC;
  long int NearCA;

  long int ParentAB;  // �������������� ������� ������� ������������ (1-��, 0-���)
  long int ParentBC;
  long int ParentCA;

  long int Cancel;    // ���� ��������
  long int Reserve;
}
  TRIANGLE;


// ��������� ������� �����   (32 ����a)

typedef struct
{
  long int A;       // ������ ������ �����
  long int B;

  long int LTri;    // ����� ������ ������������
  long int RTri;    // ����� ������� ������������

  long int Live;    // ���� - "�����" ����� (�� ��� �������� ң��� �������)
  long int Cancel;  // ���� ��������

  long int Flag;    // ���� :
                    //  0 - ����� �� ������ � ������
                    //      ����������� �����,
                    //  1 - ����� ������ � ������ �����������
                    //      ����� �������� ��������,
                    //  2 - ����� ������ � ������ �����������
                    //      ����� ���������� ��������,
                    //  3 - ����� ������ � ������ �����������
                    //      ����� �������,
                    //  4 - ����� ������ � ������ �������
                    //      �������� ���������� ������������.
  long int Reserve;
}
  EDGE;


// ��������� ������� ������   (32 ����a)    

typedef struct
{
  double X;
  double Y;
  double H;

  long int Cancel;  // ���� ��������
  long int Flag;    // ���� : 0 - ������� ������� (�������� ������)
                    //        1 - ������� ����������� ����������� �����
                    //        2 - ������� ����������� ������� ������� ����������
}
  VERTEX;

#endif  // TRIANGLETYPE_H

