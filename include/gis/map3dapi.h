
#ifndef MAP3DAPIH
#define MAP3DAPIH

#include "maptype.h"

extern "C"
{

//---------------------------------------------------------------------------
// �������� ������ � ini-����� ����� ��� ������ "3D-���������"
//---------------------------------------------------------------------------
#define IniFileSection "MAP3D"


typedef long int  HTASK3D;    // ������������� ������ ����������� �����������
                              // ������(�����, ������, �������)

//---------------------------------------------------------------------------
// ��������� �������� �������� ������ ��� ���������� 3D-������
//---------------------------------------------------------------------------
typedef struct CREATETASK3D
{
  DFRAME   SelectFrame;       // �������� ���������� ��� ���������� ������
                              // ������� ������ (� ������ �� ���������)
  long int Area;              // ������� ���������� ������:
                              //   0 - ���� �����
                              //   1 - ����� ������� ������ (SelectFrame)
                              //   2 - �� ������� ���� �����
  long int MoveAdjust;        // ������������� ����������� ����- � ���������� ����
                              //   0 - �� ����������������
                              //   1 - ���������������� �����������
                              //   2 - ���������������� ���������������
                              //   3 - ���������������� ����������� �
                              //       ���������������

                              // �������� ���������� wParam (notification code)
                              // ��������� ���� WM_COMMAND, ���������� �� ���� 3D-������
                              // ���� ���������, ������� ���������� ������ ���
                              // ������������� ������ 3D-������ � ����������� �������
                              // (��� ����, ���� ������������� �� �����)

  long int CmStop3d;          // ��������� ������� � ����������� ��������
  long int CmMove3d;          // ��������� � ����������� ������ ��������
                              // 3D-������ ��� �������� ������ �������������
                              // �����������
  long int CmSelectFrame3d;   // ��������� � ������������� ������ �����
                              // ������ ��� ���������� �� ��� ����� �����
                              // 3D-������
  long int CmSelectObject3d;  // ��������� � ������ ��� ������ ������ �������
                              // �� ���������� ������
  long int CmScale3d;         // ��������� � ���������������
                              // ���������� ������

  char     Reserve[252];
}
  CREATETASK3D;

//---------------------------------------------------------------------------
// ������� ���� ����������� ���������� ������ ���������� ������
// ��������� � ���������� ���������� ������.
// ����� ��������� ������ ������ ������� �������� ���� � ������� 3D-�������
// ������� �����, � ������������ ����������� �� ��� � ������� ���� � ����������,
// ��������� �� ���������� ����� ���� � �������� ����������
//   ����:
//      hMap  - ������������� �������� ������
//       data - �������� ������ ��� ���������� 3D-������ 
//      tparm - �������� ���������� ����������
//   ����������:  ������������� ���������� ������
//   ��� ������ ���������� ����
//---------------------------------------------------------------------------
HTASK3D _MAPAPI t3dOpen(HMAP hMap, CREATETASK3D* data, TASKPARMEX* tparm);

//---------------------------------------------------------------------------
// ������� ���� ����������� ���������� ������ ������
//   ����:
//     hTask3D - ������������� ���������� ������
//---------------------------------------------------------------------------
void _MAPAPI t3dClose(HTASK3D hTask3D);

//---------------------------------------------------------------------------
// ���������� ����� �������� ���������� ������ � �������� �����(����������
// �������� � ������ �� ���������), ������������ ������
//   ����:
//     hTask3D - ������������� ���������� ������
//       point - ����� �������� ������ ������ (� ������ �� ���������)
//   ��� ������ ���������� ����
//---------------------------------------------------------------------------
long int _MAPAPI t3dSetPoint(HTASK3D hTask3D, XYHDOUBLE* point);

//---------------------------------------------------------------------------
// ���������� ����� �������� ���������� ������ � �������� ����� � ���������
// � �������� �����������, ������������ ������
//   ����:
//     hTask3D - ������������� ���������� ������
//      point1 - ����� �������� ������ �������� ������ (� ������ �� ���������)
//      point2 - �����, �������� ����������� �������� ������ (� ������ �� ���������)
//   ��� ������ ���������� ����
//---------------------------------------------------------------------------
long int _MAPAPI t3dSetPointAndDirect(HTASK3D hTask3D, XYHDOUBLE* point1,
                                      XYHDOUBLE* point2);

//---------------------------------------------------------------------------
// ��������� ��������� ������ �������� ���������� ������
// (� ������ �� ���������)
//   ����:
//     hTask3D - ������������� ���������� ������
//       point - ����� ��� ��������� ������������ ����� � ������ �� ���������
//   ��� ������ ���������� ����
//---------------------------------------------------------------------------
long int _MAPAPI t3dGetPoint(HTASK3D hTask3D, XYHDOUBLE* point);

//---------------------------------------------------------------------------
// ��������� ���������� ������������� �������� 2D � 3D ����
//   ����:
//     hTask3D - ������������� ���������� ������
//   ����������: 1 - ������������� ��������, 0 - ���������
//---------------------------------------------------------------------------
long int _MAPAPI t3dMoveAdjustIsActive(HTASK3D hTask3D);

//---------------------------------------------------------------------------
// ����������� ������ ��������� ����� � ������ � �� �����
// (��� ������������� ����������� ����������� � ����������� ����� 3D-������)
//   ��� ������ ���������� ����
//---------------------------------------------------------------------------
long int _MAPAPI t3dAdjustData(HTASK3D hTask3D);

//---------------------------------------------------------------------------
// �������� � ���������� 3D-������ ��������� �����
//   ��� ������ ���������� ����
//---------------------------------------------------------------------------
long int _MAPAPI t3dUpdateData(HTASK3D hTask3D);

//---------------------------------------------------------------------------
// �������� ������ �� ���������� ������
//   ����:
//     hTask3D - ������������� ���������� ������
//        hObj - ������������� ���������� �������
//   ��� ������ ���������� ����
//---------------------------------------------------------------------------
long int _MAPAPI t3dSetSelectObject(HTASK3D hTask3D, HOBJ hObj);

//---------------------------------------------------------------------------
// �������� ��������� ������� �� ���������� ������ (���� ������ ��� �����
// ������� �������� t3dSetSelectObject)
//   ����:
//     hTask3D - ������������� ���������� ������
//   ��� ������ ���������� ����
//---------------------------------------------------------------------------
long int _MAPAPI t3dClearSelectObject(HTASK3D hTask3D);

//---------------------------------------------------------------------------
// ����������� ���������� �� ���������� ������ �������
//   ����:
//     hTask3D - ������������� ���������� ������
//        hObj - ������������� ������� ��� ����������� ���������� �������
//   ��� ������ ���������� ����
//---------------------------------------------------------------------------
long int _MAPAPI t3dGetSelectObject(HTASK3D hTask3D, HOBJ hObj);


//---------------------------------------------------------------------------
// ��������� ������� ������������ �������� ����������� 3D-������
//   ����:
//     hTask3D - ������������� ���������� ������
//       scale - ����� ��� �������� ����������� ��������
//   ��� ������ ���������� ����
//---------------------------------------------------------------------------
long int WINAPI t3dGetViewScale(HTASK3D hTask3D, double* scale);

}       // extern "C"

#endif

