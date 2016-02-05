
#if !defined(MAPTRACT_H)
#define MAPTRACT_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#define TACBUFCOUNT  128
#define TACBUFLENGTH  (sizeof(ACTIONHEAD)+TACBUFCOUNT*sizeof(ACTIONRECORD))

typedef struct TACHEAD     // ��������� �����
{
  long int       Label;    // ����� ������ �����
  long int       Length;   // ����� �����
  long int       Version;  // ������ ���������
  long int       Count;    // ����� ����������
  long int       Date;     // ���� �������� ������ (YYYYMMDD)
  long int       Time;     // ����� �������� ������ (������ �� 00:00:00)
  long int       Free;     // ������ ���������� ������� � ����� �����
  unsigned short Ident;    // ������������� ��������� ������
    signed short Tasks;    // ����� ������������ �����
}
  TACHEAD;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ������� ��������� ���������� +++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef class _DLLCLASS TTransaction
{
 public:

 TTransaction();
 ~TTransaction();

 public:

 char   LogName[MAX_PATH];// ��� ����� ������� ����������
 HANDLE File_TAC;         // ������������� �����

 int    IsAction;         // ������� �������� �� ������ ����������
 ACTIONHEAD * Head;       // ��������� �������� �� ������ ����������

 int    ReadNumber;       // ����� ����������� ����������
 int    ReadOffset;       // �������� �� ������� ����������
                          // ��� ������
 ACTIONHEAD ReadHead;     // ��������� ����������� ����������

 TACHEAD  TacHead;        // ��������� ����� �������

 int Iswrite;             // ���������� �� ������
 int LastError;           // ��� ������ ��������� ��������

 int IsLongAction;        // ������� "�������" ����������

 char Buffer[TACBUFLENGTH];  // ����� ����������

 unsigned short TaskIdent;   // ������������� ������� ������
 unsigned short Align;       

#if defined(WIN32API) && !defined(WINCE)
 char UserName[MAX_COMPUTERNAME_LENGTH + 4];     
#else
 char UserName[32];                              
#endif
}
  TTransaction;

typedef TTransaction TTRANSACTION;


 // ������� ������ ����������
 // ���� ������� ��� ��� ��������� �������� - ��������� ����� ������
 // ��� ������ ���������� ����
 int _fastcall trOpen(TTRANSACTION *transaction, const char * name);

 // �������� ������ ����������
 // ��� ������ ���������� ����
 int _fastcall trClear(TTRANSACTION *transaction);

 // ������� ������ ����������
 void _fastcall trClose(TTRANSACTION *transaction);

 // ��������� ����� ���������� � �������
 // ��� ������ ���������� ����
 int _fastcall trCount(TTRANSACTION *transaction);

 // ��������� ����� ������������ � ����� �������������
 // ��� ������ ���������� ����
 int _fastcall trGetUserCount(TTRANSACTION *transaction);

 // ��������� ���� �������� �������
 // date - ���� � ������� "YYYYMMDD"
 // time - ����� � ������� "����� ������ �� 00:00:00"
 // �� ��������� ����
 // ��� ������ ���������� ����
 int _fastcall trDate(TTRANSACTION *transaction,
                      long int * date, long int * time);

 // ������� ������ ����������
 // type - ��� ���������� (�� 0x4000 �� 0�0FFFF - �� ���������)
 // ��� ������ ���������� ����
 int _fastcall trCreateAction(TTRANSACTION *transaction, int type);

 // ������ � �������� ���������� �������� �� ��������
 // ��� ������ ���������� ����
 int _fastcall trPutRecord(TTRANSACTION *transaction, ACTIONRECORD * record);

 // ������� ������ ����������
 void _fastcall trCommitAction(TTRANSACTION *transaction, int longaction);

 // ��������� ����� ������ ����������,�����������
 // ����� ��������� ���� � �������
 // date - ���� � ������� "YYYYMMDD"
 // time - ����� � ������� "����� ������ �� 00:00:00"
 // �� ��������� ����
 // ��� ������ ���������� ����
 int _fastcall trGetActionNumberByTime(TTRANSACTION *transaction,
                                       long int date, long int time);

 // ������� ��������� �������� ���������� �� �������
 // number - ���������������� ����� ����������
 // (�� 1 �� Count(...)).
 // ��� ������ ���������� ����,
 // ����� - ����� �������� � ����������
 int _fastcall trReadAction(TTRANSACTION *transaction,
                            int number, ACTIONHEAD * head);

 // ������� ��������� �������� ��������� �� ���������� ����������
 // ������ �� �������
 // ���� ����� ���������� ����������� ���������� �����
 // ��� ������ ���� - ���������� ����
 // ��� ������ ���������� ����,                           
 // ����� - ����� ����������
 int _fastcall trReadLastAction(TTRANSACTION *transaction, int flag);

 // �������� ���������� ��� ����������
 // ��� ������ ���������� ����,
 int _fastcall trMarkAction(TTRANSACTION *transaction, int number);

 // ��������� �������� �� ��������
 // number - ����� �������� (�� 1 �� ReadAction(...))
 // ��� ������ ���������� ����
 int _fastcall trGetActionRecord(TTRANSACTION *transaction,
                                 int number, ACTIONRECORD * record);

 // ��������� ���������� �������� � ����������
 // ��� ������ ���������� ����
 int _fastcall trGetActionRecordCount(TTRANSACTION *transaction);

 // ������� ������ ����������
 // ��� ������ ���������� ����
 int _fastcall trCreate(TTRANSACTION *transaction, const char * name);

 // �������� ������ � ������
 // ��� ������ ���������� ����
 int _fastcall trWrite(TTRANSACTION *transaction,
                       int offset,const char * address, int size);

 // C������ ������ �� �������
 // ��� ������ ���������� ����
 int _fastcall trRead(TTRANSACTION *transaction,
                      int offset,char * address, int size);

 // ������ ������ � �������
 // ��� ������ ���������� ����
 int _fastcall trLock(TTRANSACTION *transaction);

 // ���������� ������ � �������
 void _fastcall trUnlock(TTRANSACTION *transaction);

#endif  // MAPTRACT_H

