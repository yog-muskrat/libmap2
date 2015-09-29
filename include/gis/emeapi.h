
#ifndef MAPAPI_H
  #include "mapapi.h"
#endif

extern "C"
{

 // �������� ��� ����� - �������� �����
 // name - ����� ��� (������ 8.3)
 // hMap - ������������� �������� ����������� �����
 // (������������ ���� ������ : ����� ���������, ����������������
 // �����, �����, ������� ...)
 // hSite - ������������� �������� ����������������
 // �����,  ���� ����� hMap (��� 0) - �������� �
 // ������ ��������� (������� ������).
 // ���� ����� ������� ����������� �������������� (����������), ��
 // ������ ��� ����� ��������� ������ � ����� � ��� �� ����������)
 // ��� �������� ���������� ���������� ��������� ��������
 // (1 - Ok; -1 - ������ ��� ��������)
 // ��� ������ (����� ��� �� �������) ���������� ����

 long int _MAPAPI mapChangeMapName(HMAP hMap,HSITE hSite,
                                   const char * name);

 // �������� ��� ����� - ��������������
 // name - ����� ��� (������ 8.3)
 // ���� �� ������ ������ �� ���������!
 // ��� ������ (����� ��� �� �������) ���������� ����

 long int _MAPAPI mapChangeRscName(HMAP hMap,HSITE hSite,
                                   const char * name);

 // �������� ����� ������ ������ �� ���� �����
 // number - ����� ����� ����� (������� � 1)
 // ��� ������, ������� �� ���� ������� �� ���������
 // ������ �����, ���������� ����� ����������
 // ������������� ��� �� ��������.
 // ��� ������ (����� ��� �� �������) ���������� ����

 long int _MAPAPI mapChangeListName(HMAP hMap,HSITE hSite,
                                    long int number,
                                    const char * head,
                                    const char * data,
                                    const char * semn,
                                    const char * draw);

 // ���������� ����� ������� ���������� ������ ������
 // ������������� ����� ������� ���� :
 // long int _WINAPI CallWrite(char * name, long int offset,
 //                            void * buffer, long int size);
 // ��� ������ ������� CallWrite(...) ������ ������� 0,
 // ����� - ����� ���������� ����.
 // ��� ������ CallWrite(...) �������� name ��������� �� ���
 // ����� ��� ���� � ���� (8.3).
 // ��� ������ ��������� ������ ���������� ����

 long int _MAPAPI mapSetUpdateFunction(void * address);


}       // extern "C"
