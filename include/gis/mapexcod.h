
#ifndef MAPEXCOD_H
#define MAPEXCOD_H

#ifndef MAPDEF_H
 #include "mapdef.h"
#endif

typedef struct EXCODEHEAD
{
  LONG Ident;     // ������������� ������
  LONG Length;    // ����� ������� � ���������
  LONG Mode;      // ����������� ��������������
  LONG Style;     // ��������� ��������������
  LONG Size;      // ����������� ������ �����
  LONG Reserv[6]; // ������
  LONG Count;     // ����� ������� (��� ��������)
}
  EXCODEHEAD;

#define EXCODEIDENT 0x7EEE7EEE

// ����� �������� ������� ������� ����� � �������� �����

typedef struct TMapExcode
{
 public:

 // ������� �������
 TMapExcode();

 // ������� �������
 ~TMapExcode();

 // ������� �������
 int _fastcall Open(TMap * map);

 // ��������� ������� �������� � �������� �����
 // ��� ������ ���������� ����
 int _fastcall Save();

 // ������� �������
 void _fastcall Close();

 // �������������� ������� � ��������� ������� ��������
 // � �������� ����� (��� �������������)
 // ��� ������ ���������� ����
 int _fastcall CheckCodeList(TMap * map);

 public:

  EXCODEHEAD  TableHead;   // ��������� �������
  TMap * Map;              // �������������� �����
  char * Memory;           // ������ ��� ������ �������
  int    Length;           // ����� ������� ������
}
 TMapExcode;

typedef TMapExcode TEXCODEDATA;

#endif // MAPEXCOD_H
