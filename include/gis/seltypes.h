
#ifndef SELTYPES_H
#define SELTYPES_H

// �������� ��������� ���������� ��� ������� ������

typedef  char LISTSNAME[MAX_PATH];   // ��� �����

typedef struct  NAMESARRAY
{
   long int   Size;          // ������ ���������
   long int   Count;         // ���������� ������� LISTSNAME
   LISTSNAME  Record[1];     // ������
}
   NAMESARRAY;

#endif          // SELTYPES_H
