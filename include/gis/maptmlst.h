
#if !defined(MAPTMLST_H)
#define MAPTMLST_H

#ifdef __cplusplus

#ifndef MAPDEF_H
  #include "mapdef.h"
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  ��������� ����� ����� ����������� �����  +++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ����� ������������ ��� �������� ����� ������ �����
// ��� ���������� ����������, ����������������� � ������
// ��������� (�����  ...~DA,~SE,~HD)

class _DLLCLASS TMapTempList
{
 public :

 TMapTempList();

 ~TMapTempList();

 // ������� ����� ������ ��������� �����
 // ��� ������ ���������� ����
 int Create(TMap * map,int list);

 // ������� ����� ������
 // ������������ ��� "����� ������"
 // ����� ������� ������ ������ ��������� �����
 // ������ ����� ��� ���
 void Delete();

 // ��������� ��� ������ ���������� ��������� ��������
 long int Error() { return MapList.Error(); }

 // �������� ����� ��������� �����
 // �������� �������� ����� ����� � �������� ��
 // ������� �����
 // ���� ���������� ����� ������� � �������
 // ���������� ������� TMapList �� �����
 // ������ Remove() - ���������� 0
 // savecopy  - ��������� ����� ������ ����� (~HD,~SE,~DA,~DR),
 // share     - ������� ������������ ������� (���� �� ����� 0,
 //             �� ��������� ������ ����������� � ����� ������,
 //             ����� - ������ ��� ����������� ������� � �����),
 // saveback  - ��������� ����� ������ (^HD,^SE,^DA,^DR)
 // ��� ������� ���������� ����, ��� ������ - ��. Error()
 int Remove(int share = 1, int savecopy = 0, int saveback = 0);

 // ���������/���������� ������� ������� ����������� ���������� ������
 int IsFreeAppend() { return MapList.IsFreeAppend(); }
 int IsFreeAppend(int start)
    { return MapList.IsFreeAppend(start); }

 /***************************************************************
 *                                                              *
 *          ������� ���������� ����� ����� �����                *
 *                                                              *
 ***************************************************************/


 // ������� ����� ������
 // ��� ������� ���������� ����, ��� ������ - ��. Error()
 // ��� �������� ���������� - ����� ���������� ������� � �����
 // ������� ���������� � �������
 int AppendObject(TObjectInfo * object)
 {
   return MapList.AppendObject(object);
 }

 int AppendObject(TObjectDesc desc,
                  TObjectData data = (char*)0,
                  TObjectSemn semn = (char*)0,
                  TObjectDraw draw = (char*)0)
 {
    return MapList.AppendObject(desc.Base,data.Base,semn.Base,draw.Base);
 }

 //  ������� ������, �������� ������� � �����
 int DeleteObject(int number)
    {
      return MapList.DeleteObject(number);
    }

 // �������� ������,number - ����� ������� � �����,
 // ����� ���������� ���������� �������
 // ��� ������� ���������� ����, ��� ������ - ��. Error()
 // ��� �������� ���������� - ����� ������������������ ������� � �����
 // ���� number ����� ��������, ������������ �����, ������������
 // �� ���������� �������
 int UpdateObject(int number, TObjectInfo * object)
    {
      return MapList.UpdateObject(number,object);
    }

 int UpdateObject(int number,TObjectHead * head,
                             TObjectData data = (char*)0,
                             TObjectSemn semn = (char*)0,
                             TObjectDraw draw = (char*)0)
    {
      return MapList.UpdateObject(number,head,data.Base,
                                              semn.Base,draw.Base);
    }


 /***************************************************************
 *                                                              *
 *       ������� �������� ��������, ������� � ���������         *
 *                                                              *
 ***************************************************************/

public:
/*
 // ��������� ������� �������� �������
 // ��� ������ ���������� ����
 OBJECTDATA * DataAddr()
    {
      return MapList.DataAddr();
    }

#ifndef TINYDATA
 // ��������� ������� �������� �������
 // ��� ������ ���������� ����
 IMGDRAW * DrawAddr()
    {
      return MapList.DrawAddr();
    }
#endif
*/
 // ��������� �������� "�������" ������� (� ���������� �������)
 // "������" ������ ���������� �������
 // ������� ���������� � �������
 TObjectHead * FirstHead()
    {
      return MapList.FirstHead();
    }

 // ��������� �������� "����������" ������� (� ���������� �������)
 // "���������" ������ ���������� �������
 // ������� ���������� � �������
 TObjectHead * LastHead()
    {
      return MapList.LastHead();
    }

int PrepareList;   // ����� ����������� �����

double CopyXSW;    // ����� ��������� ����� ����������
double CopyYSW;
double CopyXNE;
double CopyYNE;

int IsRemove;      // ������� �������� ������ �����


TMapList MapList;  // ���� �����

};

#endif  // __cplusplus

#endif

