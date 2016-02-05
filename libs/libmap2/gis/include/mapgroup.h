
#if !defined(MAPGROUP_H)
#define MAPGROUP_H

#ifdef __cplusplus

#ifndef MAPMACRO_H
  #include "mapmacro.h"
#endif

typedef struct   // ��������� �����H�� ���������� ��'����
{
   int Ident       ;  // 0x7FFF7FFFF
   LONG Length ;  // ���H� �����H��,H� ������� ������ !!
   int GroupNumber ;  // H���� ������
   int Type        ;  // ��� ������
   int ListCount   ;  // ����� ������,���������� ������
}
  HEADRECGDX;

typedef struct   // �����H�� ������� ��'����� � �����
{
  int Number;       // ����� ��'���� � �����
  KEY Key;          // ���������� ����� ��'���� � �����
}
  NUMBERKEY;

// ����� ��������� �����H�� ������ ���� �����H�� ����� ������
// � �������� ������H��� �����, ����� ������ = ����� ������
// �����H�� � �������� ����� ������� �� ������ ����� (4 �����),
// ���������� �������� (4 �����) � ���������������� �������
// ��'����� + ���������� ������� ��'����� � �����, �������� � ������ H� ������H�� ����� (4 �����).

#define RESERVGROUP 64

typedef struct      // ��������� ����������� ������
{                   // (���� ��'��� � ������)
  HEADRECGDX Gdx;   // ��������� ������
  int List;         // ����� ����� � ������
  int Count;        // ����� ��'����� � ������ � ������� �����
  NUMBERKEY Number; // ����� ��'���� � ����� +
                    // ���������� ����� ��'���� � �����
  char  Reserv[RESERVGROUP]; // ������ ��� ��������������
}
  MINGDXRECORD;

#define GROUPBUFSIZE (32*1024L)   // ������������ ������ ������
#define RECGDXIDENT  0x7FFF7FFF   // ������������� ������

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++  ��������� ��������� ��'�����  +++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TMap;

class _DLLCLASS TObjectGroup
{

public :

 TObjectGroup()
  {
    RecordGdx = 0;
    Memory    = 0;
    LengthMem = 0;
  }

 TObjectGroup(HEADRECGDX * address)
  {
    Memory = 0;
    Load(address);
  }

 TObjectGroup(TObjectGroup * record)
  {
    Memory = 0;
    Load(record);
  }

 ~TObjectGroup() { Clear(); }

 // ������� �������� ������

 void Clear() { Record((HEADRECGDX *)0,0); }

 // ������� ������ ��������� ��������
 // number - ����� ������,
 // ���� ����� 0 - ��� ������ � ���� ����������� �������������.
 // ���������� ������� ������ ��� ������������ ������ (32��)
 // (��������� ������ ����� �������� �� 8000 ��������)
 // ��� ������ ���������� ����

 int Create(int number = 0,int type = 0);

 // ��������� - ������������ �� �������� ������
 // ��� ������ ���������� ����

 int IsActive() { return (RecordGdx != 0); }

 // ��������� ������ ��������� �������� �� ������
 // ��� ������ ���������� ����

 int Load(HEADRECGDX * address);
 int Load(TObjectGroup * group)
  {
    if (Load((HEADRECGDX *)(group->Address())))
       {
       NumberKey = group->NumberKey;
       ObjectCountAll = group->ObjectCountAll;
       return 1;
       }
    return 0;
  }

 // ���������� ����� ������ ��������� ��������
 // ��� ������ ���������� ����

 int Record(HEADRECGDX * address,long int length);


 /***************************************************************
 *                                                              *
 *       ������� ������� � �������� ������ ��'�����             *
 *                                                              *
 ***************************************************************/

public :

 // ��������� ����� ������ ��������� ��������
 // ��� ������ ���������� ����

 char * Address() { return (char *)RecordGdx; }

 // ��������� ������������ ������
 // ��� ������ ���������� ����

 int Check()
    {
      if (RecordGdx == 0) return 0;
      return (RecordGdx->Ident == RECGDXIDENT);
    }

 // ���������/���������� ����� ������
 // ��� ������ ���������� ����

 int Number()
    {
      if (RecordGdx == 0) return 0;
      return RecordGdx->GroupNumber;
    }

 int Number(int number)
    {
      if (RecordGdx == 0) return 0;
      return RecordGdx->GroupNumber = number;
    }

 // ��������� ������ ������ (�� ������� ������)
 // ��� ������ ���������� ����

 long int Length()
    {
      if (RecordGdx == 0) return 0;
      return RecordGdx->Length;
    }

 // ��������� ������ ������ ������ (������� ������)
 // ��� ������ ���������� ����

 long int FullLength()
    {
      if (RecordGdx == 0) return 0;
      return RecordGdx->Length + sizeof(RESERVGROUP);
    }


 // ��������� ��� ������
 // ��� ������ ���������� ����

 int Type()
    {
      if (RecordGdx == 0) return 0;
      return RecordGdx->Type;
    }


 // ���������� ��� ������
 // ��� ������ ���������� ����

 int Type(int type)
    {
      if (RecordGdx == 0) return 0;
      return (RecordGdx->Type = type);
    }

 // �������� � ������ ����� ������
 // list  - ����� �����
 // number - ����� ������� + ���������� ����� �������
 // ��� ������ ���������� ����

 int AppendObject(int list, NUMBERKEY number);


 // ������� ������ �� ������
 // list  - ����� �����
 // number- ����� �������
 // ��� ������ ���������� ����

 int DeleteObject(int list, int number);

 // ������� ������ �� ������
 // list  - ����� �����
 // number- ���������� ����� �������
 // ��� ������ ���������� ����

 int DeleteObject(int list, KEY number);

 // ����� ������ �� ������ ����� � ������ ������� � �����
 // list - ����� �����
 // number - ����� �������
 // ��� ������ ���������� ����

 int FindObjectNumber(int list, int number);

 // ����� ������ �� ������ ����� � ����������� ������ �������
 // list - ����� �����
 // number - ���������� ����� �������
 // ��� ������ ���������� ����

 int FindObjectNumber(int list, KEY number);

 // ��������� ����� ������ � ������
 // ��� ������ ���������� ����

 int ListCount()
    {
      if (RecordGdx == 0) return 0;
      return RecordGdx->ListCount;
    }

 // ����������� ������ ����� �� ����������� ������ ����� � ������
 // number - ���������� ����� ����� c 1
 // ��� ������ ���������� ����

 int ListNumber(int number);

 // ������ ���������� ������� � ������
 // �� ������ ����� � ������ ������� � �����
 // list - ����� �����
 // number - ����� �������
 // ��� ������ ���������� ����

 int NextObjectNumber(int list, int number);

 // ��������� ����� �������� � �����
 // list - ����� �����
 // ��� ������ ���������� ����

 int ObjectCount(int list);

 // ��������� ����� �������� � ������
 // ��� ������ ���������� ����

 int ObjectCountGroup(){return ObjectCountAll;}

 // ����������� ������ ������� �� ������ �����
 // � ����������� ������ �������  � ������
 // list - ����� �����
 // number - ���������� ����� ������� � ������ (c 1)
 // ��� ������ ���������� ����

 int ObjectNumber(int list, int number);

 // ����������� ����������� ������ ������� �� ������ �����
 // � ����������� ������ �������  � ������
 // list - ����� �����
 // number - ���������� ����� ������� � ������ (c 1)
 // ��� ������ ���������� ����

 KEY ObjectKey(int list, int number);


 // ����������� ����������� ������ ������� �� ������ �����
 // � ����������� ������ ������� � �����
 // list - ����� �����
 // number - ���������� ����� ������� � ����� (c 1)
 // ��� ������ ���������� ����

 KEY ObjectKeyNumber(int list, int number);

#ifndef LINUXAPI
 // ������ �a���� ����a��� �p���� number � ������� record
 // ���������� ����� ��������� ����
 // ��� ������ ���������� ����

 int ReadGroup(TMap * map, int number = 0);

 // ���a������/���������� �a���� ����a��� �p����
 // ��� ������ ���������� ����

 int WriteGroup(TMap * map);
#endif

 // ���������� ����� ����� �������� � ������
 // ��� ������ ���������� ����

 void SetObjectCountAll();

 protected:

 //  ��������� ������ ������ ������ �� buffersize
 //  ��� ������ ���������� ����, ����� - ����� ������ ������

 long int Realloc(long int buffersize = DATABUFFERSIZE);


public:

int          List;      // ������� ����� �����

protected :

HEADRECGDX * RecordGdx; // ��������� �� ������

long int     LengthMem; // ����� ������
char *       Memory;    // ����� ���������� ������� ������
NUMBERKEY *  NumberKey; // ��������� �� �������� ������� �������� � �����
int          ObjectCountAll; // ����� ����� �������� � ������
};

#endif  // __cplusplus

#endif
