#ifndef RSCFL3D_H
#define RSCFL3D_H
#include "m3dgdi.h"

// �������� ��������� ��������  � ����������� ��������. �� ����� ��������� �� ������
// ����� 3D ����������.
// ����� ��������� ������ ��������.
// � ������ �������������� ����� ���������� ���� ��� ��������� ������ ����������.

// ��� �������
#define OBJECT_PARAMETERS   1  // ��������� �������
#define OBJECT_TEXTURE      2  // ��������
#define TAB_SEMANTIC        3  // ������� ������������ ��������
#define TAB_RULES           4  // ������� ������� �������� �� ������� � ���������
#define TAB_MATERIAL        5  // �������� ���������

#define FIRSTKEY_PARAMETERS  0x4F0000   // ����������� ���� ������ ����������
#define FIRSTKEY_TEXTURE     0x540000   // ����������� ���� ������ ��������
#define FIRSTKEY_SEMANTIC    0x530000   // ����������� ���� ������ ��������
#define FIRSTKEY_RULES       0x520000   // ����������� ���� ������ ������
#define FIRSTKEY_MATERIAL    0x4D0000   // ����������� ���� ������ ���������
/*
// �������� ��� ������� ����������� ����
  {                                     0
   10L,    25L,                         1
   50L, 100L,   200L,                   2
   500L,   1000L, 2000L,                3
   5000L,  10000L, 25000L,              4
   50000L, 100000L,200000L,             5
   500000L,1000000L, 2500000L,          6
   5000000L,10000000L,                  7
   50000000L,40000000L                  8
  }


*/

// ��������� �����
typedef struct P3DHEAD
     {
      unsigned long  int Label    ;    // ����� ����� .P3D
      unsigned long  int Length   ;    // ����� �����
      unsigned long  int Version  ;    // ������  (100)
      unsigned long  int Count    ;    // ���������� �������
      char               IsWrite  ;    // ���� �������� �����(1 - ������-������)
                                       // O - ������ ������
                                       // 2 - �����
      char               ScaleIndex;   // ������ ����������� ����
      char               Reserv[2];    // ������
      unsigned long  int Reserv1  ;    // ������1
     }
  P3DHEAD;

// ��������� � ������ ������ ����
typedef struct RECHEAD
  {
      unsigned long  int Length  ;    // ����� ������  c ����������
      unsigned long  int Type    ;    // ��� ������
      long int           Key     ;    // ���� ������ �������� ��� �������
                                      // ����� � ������� ����
      long int           Reserv  ;    // ������
      char               Name[32];    // �������� ����������, �������� ��� ���������
  }
  RECHEAD;

// ������ ��������
typedef struct RECTEXTURE
  {
     unsigned long int Length   ;    // ����� ������
     unsigned long Height       ;    // ������ ��������
     unsigned long Width        ;    // ������ ��������
     unsigned char Reserv[4]    ;    // ������
  }
  RECTEXTURE;

// ������ ����������
typedef struct RECPARM
  {
    unsigned long int Length  ;  // ����� ������
    unsigned long Type        ;  // ��� ������� (1 - 1�, 2- 2�,0 - �����)
                                 // ��������� ��� ����������� ���������� ��
                                 // ������� �������� � �������� ������� RSC
                                 // ����� ���������
  }
  RECPARM;

// ������ ��������� - ��������� ACT3DMATERIALMODE �� m3dgdi.h

// ������ ���������
typedef struct RECSEM
  {
    unsigned long int Length    ;  // ����� ������
    unsigned long int RscCode   ;  // ��������� ����������� ��� � RSC
    unsigned long int TypeValue ;  // ��� �������� (��������, ������������,����������)
    unsigned long int CountItem ;  // ��� ������������ - ���������� ��������
                                   // ����� �������� ITEMSEM
  }
  RECSEM;

 // ������ �������� ���������
typedef struct ITEMSEM
  {
    unsigned long int RscCode   ;  // ��������� ����������� ��� � RSC
    unsigned long int FileCode  ;  // ��� � �����
    char              Name[32]  ;  // ���
  }
  ITEMSEM;

#endif  // RSCFL3D_H
