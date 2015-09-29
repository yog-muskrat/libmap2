
#if !defined(MAPERROR_H)
#define MAPERROR_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifndef MAPERR_RH
  #include "maperr.rh"
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  ��������� ��������� �� �������   ++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TMapError
{
public:

 TMapError()
   {
     FileLog = 0;
     Error(0);
   }

 ~TMapError()
   {
     Close(0);
   }

 /***************************************************************
 *                                                              *
 *      ���������� �������� � ������� ������ �����              *
 *                                                              *
 ***************************************************************/

public:

 // ������� ������ ������ �����
 // message != 0, ���� �������� �����������, ��� ���������� �����
 // ��� ������ ���������� ����
 int Close(int message = 1);

 // ��������� ������ ������ �����
 // ��� ������ ���������� ����
 int Commit();

 // ��������� ����������� ������� ��� ������
 // ��� ������ ���������� ����
 int IsLogActive() { return (File() != 0); }

 // ��������� ��� ����� ���������
 // (1 - ����������, 2 - �������, ...)
 int LanguageCode();

 // ��������� ������������� ���� ��� ��������� ���������
 HWND MessageHandle() { return Handle; }

 // ���������� ������������� ���� ��� ��������� ���������
 HWND MessageHandle(HWND handle)  { return Handle = handle; }

 // ��������� ������ ��� (����) ����� �������
 const char * NameLOG() { return Name_LOG; }

 // ������� ������ ������ �����
 // ��� ������ ���������� ����
 int Open(const char * name,int message = 1);

 // ��������� ��������� ���� ��������� ���������
 // �������� ��������� IMM_ERROR (��. mapmacro.h)
 long int SendMessage(long int code,long int parm);

 // �������� ��������� � ������
 // message - ����� ������ ���������
 // type    - ��� ��������� (��. MESSAGETYPE)
 // ��� ������ ���������� ����
 int WriteToLog(const char * message,int type);


protected :

 // ��������� ������������� ����� �������
 HANDLE File() { return FileLog; }


 /***************************************************************
 *                                                              *
 *      ������ �� ������� � � ������ ���������                  *
 *                                                              *
 ***************************************************************/

public:

 // ��������� ��� ������ ���������� ��������� ��������
 // ���� ������ �� ����, ���������� ����
 long int Error() { return (LastError); }

 // ���������� ��� ������ ���������� ��������� ��������
 long int Error(int error) { return (LastError = error); }

 // C������� �� ������ ��� ��������� ������
 void ErrorMessage(int code,const char * filename);

public:

 long int LastError;      // ��� ������ ��������� ��������
 HANDLE   FileLog;        // ������������� ����� �������
 char Name_LOG[MAX_PATH]; // ������ ��� ����� ������� ������
 HWND Handle;             // ������������� ���� ��� ��������� ���������
};

typedef TMapError TMAPERRORDATA;


// ������ ���������� �� ������ ��������� �� �����
int IsMessageEnable();

// ������� ������ ������ �����
// ��� ������ ���������� ����
int _fastcall meOpenErrorLog(TMAPERRORDATA* data,
                             const char * name, int mode);

// ������� ������ ������ �����
// ��� ������ ���������� ����
int _fastcall meCloseErrorLog(TMAPERRORDATA* data, int mode);

// �������� ��������� � ������
// message - ����� ������ ���������
// type    - ��� ��������� (��. MESSAGETYPE)
// ��� ������ ���������� ����
int _fastcall meWriteToErrorLog(TMAPERRORDATA* data,
                                const char * message, int type);

// ��������� ������ ������ �����
// ��� ������ ���������� ����
int _fastcall meCommitErrorLog(TMAPERRORDATA* data);

// C������� �� ������ ��� ��������� ������
void _fastcall meErrorMessage(TMAPERRORDATA* data, int code,
                              const char * filename);

extern "C"
{
  void _MAPAPI ErrorMessage(int code, const char * filename);
}

#endif

