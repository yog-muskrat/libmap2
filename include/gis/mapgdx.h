
#if !defined(MAPGDX_H)
#define MAPGDX_H

#ifdef __cplusplus

#ifndef MAPERROR_H
  #include "maperror.h"
#endif

#define LABEL_GDX    0x00584447L  // ���H��������� H����� �����
#define VERSION_GDX  0x0200       // ������ GDX
#define RESERV_GDX   1024L        // ������ ��� ��������

// ��������� ����� �����H�� ��������� ��'����� (GDX)

typedef struct
{
  long  int Ident  ;    // LABEL_GDX
  long  int Length ;    // ���H� �����
  long  int Version;    // 2.0
  long  int Mode;       // ����� ��������� (��� �������������� +1)
  long  int Reserv ;    // ������
  long  int Number ;    // ����� �����
  long  int IndexOff;   // �������� �� �������
  long  int DataOff;    // �����H�� H� ��HH�� (�����H��)
  long  int Reserv1[8]; // ������
}
  HEADGDX;

typedef struct  // �H����� ������� � �����H���
{
  long int GroupNumber ;  // H���� ������ = H���� ������ �H�����
  long int Length      ;  // ���H� �����H��, ������� ������ !
  long int Offset      ;  // �����H�� � ����� H� H����� �����H��
  long int Service     ;  // ��� (?)
}
  INDEXGDX;

class _DLLCLASS TObjectGroup;
class _DLLCLASS TMap;
class _DLLCLASS TObjectDesc;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++  ��������� ��������� ��'�����  +++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TMapGroups
{
 /***************************************************************
 *                                                              *
 *       ������� ������� � ����� ��������� ��'�����             *
 *                                                              *
 ***************************************************************/

 public :

 TMapGroups(TMapError * log);

 ~TMapGroups();

 public :

 // ������ � ��������� ������ �������

 int AccessMode(int mode)
    {
       Mode_GDX = (mode & (GENERIC_READ|GENERIC_WRITE));
       if (Mode_GDX == 0)
         Mode_GDX = GENERIC_READ|GENERIC_WRITE;
       return Mode_GDX;
    }

 int AccessMode()
     { return ( Mode_GDX ); }

 // ���p��� �a�� ����a��� �p������� ��������

 void Close();

 // ������� �a�� ����a��� �p������� ��������

 int Create(char * name);

 // ��������� ��� ������ ��������� ��������
 // ���� ������ � ����� MAPERR.RH

 int Error() { return ErrorCode; }

 // ��������� ����� �����

 int Count() { return HeadGdx.Number; }

 // �������� ����������� ������

 int IsActive()
    { return (File() != 0); }

 // ������ ����� ����� ��������� ��������

 char * Name() { return Name_GDX; }

 // ���p��� �a�� ����a��� �p������� ��������

 int Open(char * name);

 //  ������������ �a�� ����a��� �p������� ��������
 //  ���������� ����� ��������������� �����

 int Restore(TMap *map, char *name);

protected :

 // ���������� ��� ������ ��������� ��������

 int Error(int error) { return ErrorCode = error; }

 // ������ �������������� �����
 // ���� ���� �� ������, ������������� ����� 0

 HANDLE File() { return (File_GDX); }


 /***************************************************************
 *                                                              *
 *       ������� ������� � �������� ��������� ��'�����          *
 *                                                              *
 ***************************************************************/

public :

 // ������ �a���� ����a��� �p���� number � ������� record
 // ���������� ����� ��������� ����
 // ��� ������ ���������� ����

 int ReadGroup(TObjectGroup * record, int number);

 // ���a������/���������� �a���� ����a��� �p����
 // ��� ������ ���������� ����

 int WriteGroup(TObjectGroup * record);

 // ������������ �p����
 // list - ����� �����
 // object - ����� ������� � �����
 // ��� ������ ���������� 0

 int RestoreGroup(TObjectDesc desc, int list, int object);

 // ������� ������
 // number - ����� ������
 // ��� ������ ���������� 0

 int DeleteGroup(int number);

protected :

 // ������� ������ �� �����
 // ��� ������ ���������� ����

 int Read(int offset,char * address,int length);

 // ������ ������a �p���� number �� ������ index
 // ���������� ����� ������������ ������
 // ��� ������ ���������� ����
 // (��� ������ - Error(), ��. MAPERR.RH)

 INDEXGDX * ReadGroupIndex(int number);

 // �����(�������) ������� �������� ��������� ��������
 // ��� ������ ���������� ����

 int MoveGroupRecords();

 // ������ ������a �p���� � ����
 // ���������� ����� ������������ ������
 // ��� ������ ���������� ����
 // (��� ������ - Error(), ��. MAPERR.RH)

 int WriteGroupIndex(INDEXGDX * index);

 // �������� ������ � ����
 // ��� ������ ���������� ����

 int Write(int offset,char * address,int length);


protected :

int  ErrorCode;          // ��� ������ ��������� ��������

int    Mode_GDX;         // ����� ������� � �����
HANDLE File_GDX;         // ������������� �����

HEADGDX HeadGdx;         // ��������� ����� ��������� ��������

char Name_GDX[MAX_PATH]; // ��� ����� ��������� ��������
                         // ������ � ���������� ...\LOG

INDEXGDX Buffer[RESERV_GDX]; // ����� �������� ��������
int FirstIndex;              // ����� ������� ������� � ������
int LastIndex;               // ����� ���������� ������� � ������

TMapError * Log;         // ���������� ��������� �� �������

};

#endif  // __cplusplus

#endif
