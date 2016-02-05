
#ifndef OBSETAPI_H
#define OBSETAPI_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

typedef  long int  HOBJLIST;

#ifdef __cplusplus
extern "C"
{
#endif

 // ������� ���� ������� ��������
 // ��� ������ ���������� ����

 HOBJLIST WINAPI _export obsOpenObjSetFile(HMAP hmap);

 // ������� ���� ������� ��������
 // ��� ������ ���������� ����

 long int WINAPI _export obsCloseObjSetFile(HOBJLIST objset);

 // ��������� ����� ������� � �����
 // ��� ������ ���������� ���� (���� ��������)

 long int WINAPI _export obsObjSetsCount(HOBJLIST objset);

 // �������� ������ (������) � ����
 // name - ��� ������ � �����
 // (������ ����������� �� ���������� ������ �������� � hmap ����)
 // ��� ������ ���������� ����

 long int WINAPI _export obsAddObjSet(HOBJLIST objset, HMAP hmap, const char* name);

 // ������� ������ (������) �� ����� �� �����
 // ��� ������ ���������� ����

 long int WINAPI _export obsDeleteObjSet(HOBJLIST objset, const char* name);

 // ����� ������ (������) �� ����� � �����
 // ���� ������ � ������ name ������� � �����, ���������� "1"
 // ����� - ����.

 long int WINAPI _export obsFindObjSet(HOBJLIST objset, const char* name);

 // ��������� ��� ������ �� ������ � �����
 // ��� ������ ���������� ����

 char* WINAPI _export obsObjSetName(HOBJLIST objset, int number, char *buffer, int bufsize);

 // ��������� ������� ������� ����� � ������
 // number - ����� ������ � �����,
 // info - ������ �����.
 // ���� ������ ����� ������������� ������, ���������� "1"
 // ����� - ����.

 long int WINAPI _export obsTestMapObjectByObjSet(HOBJLIST objset, int number, HOBJ info, HMAP hmap);


 // ��������� ������� ����� � ������
 // number - ����� ������ � �����,
 // info - ������ �����.
 // nmap - ����� �����
 // ���� ����� ���������� � ������, ���������� "1"
 // ����� - ����.
 long int WINAPI _export obsTestMapByObjSet(HOBJLIST objset, int number, HMAP hmap, int nmap);

 // ���������� hselect �� ��������� ������ ����� ������� ��������
 // number  - ����� ������ � �����,
 // hselect - �������� ������ ��� ���������� ���������� ������� ��������,
 // hsite   - ������������� �����, ��� ������� ����������� �������� ������
 // ���� ��� hsite ������� ������, ���������� "1"
 // ����� - ����.
 
 long int WINAPI _export obsSetSelectByObjSet(HOBJLIST objset, int number, HMAP hmap, HSITE hsite, HSELECT hselect);


#ifdef __cplusplus
}       // extern "C"
#endif


#endif  // OBSETAPI_H
