#ifndef MATHAPI_H
#define MATHAPI_H
#ifndef MAPTYPE_H
  #include "maptype.h"   // �������� �������� ���������� MAPAPI
#endif
#include "mapapi.h"
#include <math.h>
#include <stdio.h>
typedef long int  HCUT;    // ������������� ��'����
 // *********************************************************
 // ����� �������:
 // =============
 // HCUT hCut = mathCreateCutProcess(hMap, info, precision);
 // if (hCut)
 //    {
 //    while(mathGetNextTriangularObject(hCut, infoNew))
 //         {
 //         ...
 //         }
 //    mathFreeCutProcess(hCut);
 //    }
 // **********************************************************
extern "C"
{
// ��������� ������������� ������������ ������� �� �������� ���������� ������ �����
// �������� ������ (�����������)
// info - ��������� ����� �����
// ���������� ��������� �� �����
// ��� ������ ���������� 0
HCUT _export  WINAPI  mathCreateCutProcess(HMAP Map, HOBJ info, double precision);
// ��������� ������������� ������������ ������� �� �������� ���������� ������ �����
// ��������� ��������� ����������� ������
// info - ��������� (����������� ������)
// ��� ���������� ����� �����(���� �������� ������ ����� 3-� ������ �������)    
//     info ���������� ��������� � 3-� ������ ��������
// ���������� ������� �������� ���������� ������ �����
// ��� ������ ���������� 0
HOBJ _export  WINAPI  mathGetNextTriangularObject(HCUT hcut, HOBJ info);
// ��������� ������������� ������������ ������� �� �������� ���������� ������ �����
// ������������ ������ (����������)
long int _export  WINAPI  mathFreeCutProcess(HCUT hcut);
//******************************************************************
//        ������� ������� ��������� ����� ��� ���������            *
//        �� ��������� ��������� ������                            *
//******************************************************************
//  �������������� ������� :                                       *
//                                                                 *
//  // �������� ����������                                         *
//  HINSTANCE libInst;                                             *
//                                                                 *
//  // ����� �������                                               *
//  int (WINAPI *GetObjectCenter)(HMAP hmap, HOBJ info, double *x, *
//                                double *y);                      *
//                                                                 *
//  (FARPROC) GetObjectCenter = mapLoadLibrary("mapmath.dll",      *
//                                          &libInst,              *
//                                          "mathGetObjectCenter");*          *
//                                                                 *
//  int code = (GetObjectCenter*)(hmap,info,&x,&y);                *
//    ...                                                          *
//                                                                 *
//  // �������� ����������                                         *
//  ::FreeLibrary(libInst);                                        *
//                                                                 *
//*****************************************************************/
// ����������� ����� � ��������� ��������
long int _export  WINAPI  mathCreateLineCross(HMAP hMap, HOBJ inobj, HOBJ outinfo,
                                          double step);
// ���������������� �����
long int _export  WINAPI  mathLineInterpolate(HOBJ inobj, HOBJ outobj,
                                          double step);
// ���������� ����� ���������� �������
long int _export  WINAPI  mathGetObjectCenter(HMAP hmap, HOBJ info,
                                          double *x,double *y);
// ���������� ����� ������� ����� ������� � ������������ x1,y1 � x2,y2
// delta - ��� �����������
// number - ����� �����
// ��� ������ ���������� 0
long int _export  WINAPI  mathSetLineLength(double *x1,double *y1,double *x2,double *y2,
                                       double delta,long int number);
// �������� ������ ����������� �� �������� ��������� ������
// hmap - ������������� �������� ������
// info  - �������� ������� ���ޣ�� ����������� ������ ����� (�������
//                                              ������ ���� ���������)
// scale - ����������� �������� ����� (25000 - 1000000)
// listreg - ����� ������� �������� ���������� ������ ����� �����
// sheet - ������������ ����� �����������
// ������������ ��������: ��� ������ - 0,
// ��� ���������� ���������� ���������� ���� ��������� LISTREGISTER ���
// ������� �����
long int _export  WINAPI  mathSheetFromFrame(HMAP  hmap,
                                  HOBJ info, long scale,
                                  LISTREGISTER* listreg,
                                  long sheet);
// �������� ��������� ������ �������� �����������
// info  - �������� ������� ���������� ������ �����
// �������� ���������:
// frame - ���������� 2-� ����� ������� ���������� �����
// regim - �������� �ޣ�� ����������� ����� ������ ��������
//                    (0 - ������ �������� �� ������������
//                     1 - ������ �������� ������������)
// ��� ������ ���������� 0
long int _export  WINAPI  mathCheckFrame(HMAP hmap, HOBJ info, FRAME*frame,
                                         int &regim);
// ���������� ����� ������� �������� LISTREGISTER ���������� ������
// array - ����� ������ �����������,������������ �� �������� �������
// listreg - ����� ������� �������� ���������� ������ ����� �����
// scale   - ����������� �������� (25000 - 1000000)
// countname - ����� ������������ �����������
// ��� ������ ���������� 0
long int _export  WINAPI  mathSetListRegister(char* array,
                                              LISTREGISTER*listreg,
                                              long scale, long countname);
// ���������� �����������,�� ������������� �������� �������
// info  - �������� ������� ���������� ������ �����
// listreg - ����� ������� �������� ���������� ������ ����� �����
// count   - ����� ������������ ����������� ����� ����������
// ��� ������ ���������� 0, �����  ����� ����������� ����� ����������
long int _export  WINAPI  mathSetBelongNomenclature(HMAP hmap, HOBJ info,
                                                    LISTREGISTER*listreg,
                                                    long count);
// ���������� ������������ ����� �� �������� scale � ������������� �����������
// ������ b,l (� ��������)
// name - ������������ �����
// comp - ������� ����������(��������� ��������� ����� - 1
//                           �� ���������              - 0)
// ��� ������ ���������� 0, ����� 1
long int _export  WINAPI  mathGetRuleSheetName(long int scale,double b,double l,
                                               char *name,long int comp);
}       // extern "C"
#endif  // MATHAPI_H
