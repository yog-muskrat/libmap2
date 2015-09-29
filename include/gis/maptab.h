
#ifndef MAPTAB_H
#define MAPTAB_H

#ifndef MAPTYPE_H
 #include "maptype.h"
#endif

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ���� � ������� ������� ������������� �����
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define TABVERSION 0x010001
#define LABEL_TAB  0x00424154L     // TAB0


typedef struct TABHEAD     // ��������� � ������ �������
{
  long Ident;              // �������������    (LABEL_TAB)
  long Length;             // ����� �����
  long Version;            // ������ ��������� (TABVERSION)
  long Mode;               // ��������� ������ (���������� ��� ��������������)
  long OffsetBegin;        // ������ ������� �������� � �����
  long OffsetCount;        // ����� ������� � ������� ��������
  long RecordBegin;        // ������ ������� ������� � �����
  long RecordCount;        // ���������� �������
  long RecordSize;         // ������ ����� ������
  long Reserv[23];         // ������ (�.�. 0)
}
  TABHEAD;

#define OFFBLOCKSIZE  (64*1024L)           // ������ ����� ��������
#define RECBLOCKCOUNT 2048L                // ����� ������� � ����� �������

typedef struct TABBUFFER
{
 HANDLE        File;           // ������������� ����� ������
 unsigned long Size;           // ������ ������� ������
 TABHEAD       Head;           // ��������� �����
 long          IsDirty;        // ������� ���������� ���������
 unsigned long Lock;           // ������ ����������� ������� � ����� 
 unsigned long Error;          // ��� ������ ��������� ��������
 char *        Offset;         // ����� ������� ������ ��� �������� �� �������
 unsigned long OffsetMin;      // ������ ����� �������� � �����
 unsigned long OffsetMax;      // ����� ����� �������� � �����
 unsigned long OffsetSize;     // ������ ������� ��������
 long          IsOffsetDirty;  // ������� ���������� ������ ��������
 char      *   Record;         // ����� ������� ������ ��� ������
 unsigned long RecordMin;      // ������ ����� �������� � �����
 unsigned long RecordMax;      // ����� ����� �������� � �����
 unsigned long RecordSize;     // ������ ������� ��������
 long          IsRecordDirty;  // ������� ���������� ������ ������� 
 unsigned long MaxCount;       // ���������� ����� �������
 char          Name[MAX_PATH]; // ��� �����
}
 TABBUFFER;


typedef class _DLLCLASS TTableFile : public TABBUFFER
{
 public:

   TTableFile();
   ~TTableFile();

   // ������� ���� � ������� �������
   // ��� �������� ���������� ���������� ��������� ��������
   // recordsize - ������ ������ � �����
   int _fastcall Create(const char * name, int recordsize);

   // ������� ���� � ������� �������
   // ��� �������� ���������� ���������� ��������� ��������
   int _fastcall Open(const char * name);

   // ������� ����
   void _fastcall Close();

   // ��������� ����� ������ �� �� ������
   char * _fastcall GetRecord(int number);

   // �������� ������ �� ������
   // force - ������� ������������ ���������� ������ � �����
   int _fastcall PutRecord(const char * record,
                           int number, int force);
}
  TTableFile;

#endif
