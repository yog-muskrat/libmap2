
#ifndef PROTOCOL_H

#ifndef MAPAPI_H
  #include "mapapi.h"
#endif

#include "mwmacro.h"               

// ������ ������ ������ [CONTROL]
#define PRO_ACT  0x5443412E        // .ACT
#define PRO_MAP  0x50414D2E        // .MAP
#define PRO_SIT  0x5449532E        // .SIT
#define PRO_ASK  0x4B53412E        // .ASK
#define PRO_REQ  0x5145522E        // .REQ
#define PRO_RSC  0x4353522E        // .RSC
#define PRO_MES  0x53454D2E        // .MES
#define PRO_OFF  0x46464F2E        // .OFF
#define PRO_COD  0x444F432E        // .COD
#define PRO_SYS  0x5359532E        // .SYS

// ������ ������ ������ [DATA]
#define PRO_DAT  0x5441442E        // .DAT
#define PRO_OBJ  0x4A424F2E        // .OBJ
#define PRO_KEY  0x59454B2E        // .KEY
#define PRO_GEN  0x4E45472E        // .GEN
#define PRO_MET  0x54454D2E        // .MET
#define PRO_SEM  0x4D45532E        // .SEM
#define PRO_TXT  0x5458542E        // .TXT
#define PRO_END  0x444E452E        // .END
#define PRO_EVN  0x4E56452E        // .EVN
#define PRO_SEG  0x4745532E        // .SEG
#define PRO_ON   0x5F4E4F2E        // .ON_
#define PRO_ANG  0x474E412E        // .ANG
#define PRO_SPL  0x4C50532E        // .SPL
#define PRO_APP  0x5050412E        // .APP
#define PRO_API  0x4950412E        // .API
#define PRO_APS  0x5350412E        // .APS
#define PRO_DEL  0x4C45442E        // .DEL
#define PRO_CHK  0x4B48432E        // .CHK
#define PRO_UNC  0x434E552E        // .UNC
#define PRO_ENA  0x414E452E        // .ENA
#define PRO_DIS  0x5349442E        // .DIS
#define PRO_COM  0x4D4F432E        // .COM
#define PRO_GET  0x5445472E        // .GET

#define PROOUTPUTBLOCK   (16*1024L)   // ����������� ������ ��������� ������

typedef struct MAPPROTOCOL            // ��������� ���������� ����������
{
  long int   Length;                  // ������ ������ ���������
  long int   ClientIdent;             // ������������� ������� (����� ������)
  char *     InputBuffer;             // ����� �������� ������
  long int   InputSize;               // ������ �������� ������
  long int   InputRecordSize;         // ������ ������� ������
  char *     OutputBuffer;            // ����� ��������� ������
  long int   OutputSize;              // ������ ��������� ������
  long int   OutputRecordSize;        // ������ �������� ������
  long int   TaskIdent;               // ������������� ������ ��� 0
  long int   Reserv[2];               // ������
}
  MAPPROTOCOL;

#define SYS_NONE  0
#define SYS_GEO42 1
#define SYS_WGS84 2
#define SYS_EP90  3
#define SYS_MET42 16

#define MAXSITCOUNT  16

typedef struct PROCONTROL     // ������ ������ CONTROL
{
  long int ClientIdent;       // ������������� ������� (����� ������)
  char     Act[16];           // ����������� �������
  char     Ask[16];           // ������������� �������
  char     Map[256];          // ��� ������� ����� ("������")
  char     Sit[256];          // ��� ���������������� ����� ("����")
  char     Rsc[256];          // ��� ����� ��������������
  char     Mes[160];          // ����������� � ����������� ��������
  long int Req;               // ����� �����������
  long int Off;               // ������� ������ �������
  long int Sys;               // ������� ��������� SYS_WGS84,...
  long int Zone;              // ������ �������� ���� ��� C�42
  long int Count;             // ����� ���������� ���������������� ����
  struct
  {
   char    Sit[256];          // ��� ���������������� ����� ("����")
  }
    List[MAXSITCOUNT];
}
  PROCONTROL;



#ifdef __cplusplus
extern "C"
{
#endif

// ������������� ���������� ������ ��� ��������� ���������
// ���������� ����� OutputBuffer, OutputSize...
// ��� ������ ���������� ����

long int _DLLTASK proInit(TASKPARMEX * parm, MAPPROTOCOL * data);

// ������������ ���������� ������ ��� ���������� ������
// ��� ������ ���������� ����

void _DLLTASK proFree(MAPPROTOCOL * data);

// ����������� � ����������� ����� � ���������� �������
// ��� ������������� ������� ������ ��������� �� �������

void _DLLTASK proCloseClient(TASKPARMEX * parm, long int ident);

// ��������� ������ ��������� ���������� ��������������...
// parm - ��������� ����� � ������,
// data - �������� ������������ ������.
// ����� ��������� �������� ������ � �������� ����� ����������
// �������� ������, ������ ������ ���������� � ���� OutputRecordSize.
// ���� ������ ��� �������� ��� - ������ �������� ������ ����� ����.
// ���� ������ ������ ������ ������� ������������ ������, �������
// proPutRecord ������������� ��������������� ������ ��� �����.
// ��� ������ ���������� ����

long int _DLLTASK proPutRecord(TASKPARMEX * parm, MAPPROTOCOL * data);

// ��������� ������� ���������� ������� ������������� �������
// ident - ������������� �������� �������, ����������� ��� ������
// ��� ������ ���������� ����

PROCONTROL * _DLLTASK proGetSelectParm(long int * ident);

// ����������� ����� �� ������� SELECT � ��������� ������ � ������
// ������� ���������� ������������� �� ����������� ������� SELECT
// hmap - ������������� ������ ����
// hobj - ������������� ���������� ������� �����
// ���� ���������� ����� ��������� - ���������� ����,
// ��� ����������� ������ ����������� ���������� ��������� ��������

long int _DLLTASK proSelectReply(TASKPARMEX * parm, HMAP hmap,
                                 HOBJ hobj, long int ident);

// ��������� ������� ���������� ������� ������������� ������� CREATE
// ident  - ������������� �������� �������, ����������� ��� ������
// method - ������ �������� ������� (���� ������ ��� - ������������ 0)
// ��� ������ ���������� ����

PROCONTROL * _DLLTASK proGetCreateParm(HMAP hMap, HOBJ hObj,
                                       long int * method,
                                       long int * ident);

// ����������� ����� �� ������� CREATE � ��������� ������ � ������
// ������� ���������� ������������� �� ����������� ������� CREATE
// hmap - ������������� ������ ����
// hobj - ������������� ���������� ������� �����
// ���� ���������� ����� ��������� - ���������� ����,
// ��� ����������� ������ ����������� ���������� ��������� ��������


///////////////////////////////////////NIITP////////////////////////////////////
long int _DLLTASK proCreateReply(TASKPARMEX * parm, HMAP hmap,
                                 HOBJ hobj, long int ident, short usage = 0, double x = 555.0, double y = 555.0);
				  
//long int _DLLTASK proCreateReply(TASKPARMEX * parm, HMAP hmap,
//                                 HOBJ hobj, long int ident);
//////////////////////////////////////////////////////////////////


// ����������� � �������� �����������

void _DLLTASK proActionClose(TASKPARMEX * parm);

// ��������� �������, ������� EVENT
// map - ������� ����� ��� ���� �������;
// ���� event = PRO_EV_SELECT, �� info - ��������� ������;
// ��������� - SELECT.
// ���� event = PRO_EV_CHANGE, �� ��������� LOAD.
// ���� event = PRO_EV_UPDATE, �� parm - ��������� ����������;
// ��������� - CREATE, DATA ��� DELETE.

void _DLLTASK proEventReply(TASKPARMEX * parm, int event, HMAP hMap,
                            CHANGEINFO * change, HOBJ hObj);


// ��������� ������ ���������� �������� �� ������� ���������
// hMap  - ������������� �����, �� ������� �������� �������
//         ��� ������ ���� ������ (����� ������� ��������� � �������)
// info  - ������������� ���������� �������, ���� ����� 0,
//         �� ���������� ������ ���������� ��������
// ident - ������������� ������ �� ������ ����� � ������ PROTOCOLLIST

void _DLLTASK proSendObjects(TASKPARMEX * parm, HMAP hMap,
                             HOBJ hObj, int ident);

// ������ ����������� ������ ����
// ���� ����� ���� ��������� - ���������� 1

long int _DLLTASK proMenuEnable(COMMANDENABLER * commen);

// ��������� ����������� � ������ ������ ����
// ���� �������� ���� ���, hMap ����� ����
// ���� �� ���������� ������������� ���� ������� ���������� - ���������� 
// ��������� ��������
// ��� ������ ���������� ����

long int _DLLTASK proMenuCommand(TASKPARMEX * parm, HMAP hMap, long int ident);

#ifdef __cplusplus
}
#endif

// **********************************************************
//
//  ���������� ������� � ��������� ��������� ���������
//
// **********************************************************

typedef struct PRODATA        // ������ ��� ��������� ������ DATA
{
  HMAP      hMap;             // ������������� ������� �����
  HSITE     hSite;            // ������������� ���������������� �����
  DFRAME    Border;           // ����� �������� ����������� �������
  long  int Req;              // ����� �����������
  long  int Sys;              // ������� ��������� SYS_WGS84,...
  long  int Zone;             // ������ �������� ���� ��� C�42
  HWND      Hwnd;             // ������������� �������� ���� �����
}
  PRODATA;

#define PROSELECTCOUNT 32     // ������������ ����� �������� � �������

#define PROSELECTTYPE  MT_PROTOCOLSELECT  // ������ �� �����
#define PROCREATETYPE  MT_PROTOCOLCREATE  // ������ �� ��������

typedef struct SELECTCONTROL  // ���� ������������� ��������
{
 int        Ident;            // ������������� �������;
 int        Type;             // ��� ������� 0 - SELECT, 1 - CREATE
 PROCONTROL Control;          // ����� ������ �� ������ [CONTROL]
 char *     Buffer;           // ����� ������� ������ ������ ��� 0
 int        Size;             // ������ ������
 char *     Current;          // ������� ������� � ������
 HWND       Hwnd;             // ������������� ���� �����
 long int   IsActive;         // ������� ��������� ���������� ������
}
 SELECTCONTROL;

#define PROEVENTCOUNT 32      // ������������ ����� ���������� � ������

#define PRO_EV_CHANGE 1       // ��������� ������� ���������
#define PRO_EV_SELECT 2       // ����� ������� �� �����
#define PRO_EV_UPDATE 4       // ��������� ������ �������

typedef struct EVENTCONTROL
{
 int        Ident;           // ������������� �������
 int        ClientIdent;     // ������������� ����������
 char       Map[256];        // ��� ������� ����� ("������")
 int        Flag;            // ���� ������� PRO_EV_CHANGE,...
 int        Count;           // ����� ���������������� ���� � ������
 struct
  {
   char     Sit[256];        // ��� ���������������� ����� ("����")
   int      Flag;            // ���� ������� PRO_EV_CHANGE,...
  }
    List[MAXSITCOUNT];
}
 EVENTCONTROL;

// ����� ������ � ������

char * _fastcall proSeekChar(const char * point, char symbol);

// ������� ��������� ������ �� ������
// ���� ������� '\n' �/��� '\r' � ���������� �� ����
// ������ ������ � ������� ������������� ������������
// point - ����� ������� ������� � ������
// limit - ����� ���������� ����� ������
// ���������� ����� ������ ����� ������ (����� ��������)
// �������� ���������� limit �������������� �������������
// ���� ������ ����������� - ���������� ����

char * _fastcall proGetNextString(char * point, int * limit);

// ������� ��������� �������
// ���� ������� '\n' �/��� '\r' � �������� ������ �� ���
// point - ����� ������� ������� � ������
// limit - ����� ���������� ����� ������
// value - ����� ������ ��� ����������
// size  - ����� ������ ��� ���������� (� ������ ����������� 0)
// ���������� ����� ����� ������
// ���� ������ ����������� - ���������� ����

char * _fastcall proGetValue(char * point, int * stringlimit,
                             char * value, int size);


// �������� ������ � �������� �������� � ��������� �����
// ������
// ��� ������ ���������� ����

char * _fastcall proPutValue(MAPPROTOCOL * data, const char * value,
                             int size);

// ��������� ������ �� ��������� (�� 3)
// size - ������ ����� ��� ������ ���������� (����������)
// ���������� ����� ��������� ����������
// ��� ������ ���������� ����

int _fastcall proSeekValue3(const char * value,
                            char * pole1, char * pole2, char * pole3, int size);

// ��������� ������ �� ��������� (�� 5)
// ���������� ����� ��������� ����������
// ��� ������ ���������� ����

int _fastcall proSeekValue5(const char * value,
                            char * pole1, char * pole2, char * pole3,
                            char * pole4, char * pole5, int size);


//  ������� ������ ��� ���������������� �����

char * _fastcall proBuildSitName(HMAP hMap, char * sitname, int size);

// ���������� ������� ��������� ������
// ��� ������ ���������� ����

int _fastcall proRealloc(MAPPROTOCOL * data, int delta);

// ���������� ������ �� ������� ������
// ��� �������� ���������� ���������� ����� ��������� ������ ������
// ��� ������ ���������� ����

char * _fastcall proPrepareRecord(TASKPARMEX * parm, MAPPROTOCOL * data,
                                  char * point, int * limit);


// ���������� ������ ������ CONTROL
// parm       - ��������� ����� � ������,
// data       - �������� ������������ ������,
// proControl - ������ ������ CONTROL
// proData    - �������� ������ ��� ��������� ������ DATA
// ��� ������ ���������� ����

int _fastcall proGetControl(TASKPARMEX * parm,
                            PROCONTROL * proControl, PRODATA * proData);


// ��������� ������ ������ �������� ������

void _fastcall proReceiptControl(MAPPROTOCOL * data,
                                 PROCONTROL * proControl);


// ���������� ������ �� ������ DATA
// ��� �������� ���������� ���������� ����� ��������� ������ ������
// ��� ������ ���������� ����

char * _fastcall proGetData(TASKPARMEX * parm, MAPPROTOCOL * data,
                            char * point, int * stringlimit,
                            PRODATA * proData);

// ���������� ������ ������� ������� �� ������ DATA
// ��� �������� ���������� ���������� ����� ��������� ������ ������
// hobj  - ������������� ������������ �������
// count - ��������� ����� �����������
// ��� ������ ���������� ����

char * _fastcall proGetMetric(HOBJ hobj, int subjcount,
                              char * point, int * stringlimit,
                              PRODATA * proData);

// ���������� ������ ������� ������� �� ������ DATA
// ��� �������� ���������� ���������� ����� ��������� ������ ������
// hobj  - ������������� ������������ �������
// count - ��������� ����� �����������
// ��� ������ ���������� ����

char * _fastcall proGetSemantic(HOBJ hobj, int count,
                                char * point, int * stringlimit,
                                PRODATA * proData);


// ���������� ������ �� ������ DATA ��� ������ DELETE__
// ��� �������� ���������� ���������� ����� ��������� ������ ������
// ��� ������ ���������� ����

char * _fastcall proDeleteObjects(TASKPARMEX * parm, MAPPROTOCOL * data,
                                  char * point, int * stringlimit,
                                  PROCONTROL * proControl,
                                  int objects);


// ���������� ������ �� ������ DATA ��� ������ SAVE__
// ��� �������� ���������� ���������� ����� ��������� ������ ������
// ��� ������ ���������� ����

char * _fastcall proSaveObjects(TASKPARMEX * parm, MAPPROTOCOL * data,
                                char * point, int * stringlimit,
                                PRODATA * proData, int dataflag);


// ��������� �������� ������� � �������� ������
void _fastcall proSaveObject(MAPPROTOCOL * data, PRODATA * proData,
                             HOBJ hobj, int number, HRSC hRsc);

                             
// ������� ������ �� ����� � �������� � ����������, ������ SELECT,CREATE
// ��� �������� ���������� ���������� ����� ��������� ������ ������
// ��� ������ ���������� ����

char * _fastcall proSelectObject(TASKPARMEX * parm, PROCONTROL * proControl,
                                 char * point, int * stringlimit,
                                 PRODATA * proData, int type, int objects);

// ������������������� ������� ���������� ������ �������
// ��� ������ ���������� ����

int _fastcall proSelectInit();

// ���������� ������� ������ �������

void _fastcall proSelectFree();

// ������� �� ������� ������� ��������� ���� ��� ����������
// ����������
// type  - ��� ������� (����� �������,�������� �������...),
//         ���� type ����� 0, ��������� ������� ���� �����.
// ident - ������������� ���������� (�������)

void _fastcall proDeleteRecord(TASKPARMEX * parm, int type, int ident);

// ������� �� ������� ������� � ��������� �����
// name - ��� ����������� ����� ���������

void _fastcall proDeleteRecordByName(TASKPARMEX * parm, const char * name);


// ��������� ��������� ����� ���������
// ��� ������ ���������� ����

int _fastcall proLoadMapEdit(TASKPARMEX * parm);

// ��������� ��������� ����� ���������

void _fastcall proFreeMapEdit();

// ������ �� ����� ��������, ������� SHOWDATA

char * _fastcall proShowData(TASKPARMEX * parm,
                             char * point, int * stringlimit,
                             PRODATA * proData);

// ������ �� ��������� ��������

char * _fastcall proMarkObjects(TASKPARMEX * parm, PROCONTROL * proControl,
                                char * point, int * stringlimit,
                                PRODATA * proData, int dataflag);

// ������� ��������� ������

void _fastcall proCloseData(TASKPARMEX * parm, PROCONTROL * proControl);


// ������ �� ��������� �������� ����

char * _fastcall proMenu(TASKPARMEX * parm,
                         char * point, int * stringlimit,
                         PRODATA * proData, PROCONTROL * proControl);

// ������� ������ ����, ��������� ��� ��������� �������
// ident - ������������� ���������� (�������)

void _fastcall proMenuClose(TASKPARMEX * parm, int ident);

// ������������������� ������� ���������� �������

int _fastcall proEventInit();

//  ���������� ������� ���������� �������

void _fastcall proEventFree();

// ������� �� ������� ������� � ��������� �����

void _fastcall proDeleteEventByName(const char * name);

// ������� �� ������� ������� ��� ���������� ����������
// ident - ������������� ���������� (�������)

void _fastcall proDeleteEvent(int ident);

// ��������� �������� �� �������, ������� EVENT

char *_fastcall proEvents(TASKPARMEX * parm, PROCONTROL * proControl,
                          char * point, int * stringlimit,
                          PRODATA * proData, int datasec);

// ��������� ������������� ��� ������� LOAD

void _fastcall proLoadReply(MAPPROTOCOL * data, PROCONTROL * proControl,
                            PRODATA * proData);

// �������� ����� � ������� ������� � ������ ������� ���������
// hobj  - ������������� ������������ �������
// ��� ������ ���������� ����

void _fastcall proAppendPoint(HOBJ hobj,
                              double * B, double * L, double * H,
                              int subject, PRODATA * proData);


// ���������� ���������������

void _fastcall proEditData(PROCONTROL * proControl, PRODATA * proData);


// ���������� ������������ ������

char * _fastcall proViewData(TASKPARMEX * parm, PROCONTROL * proControl,
                             char * point, int * stringlimit,
                             PRODATA * proData, int dataflag);

// ���������� ������������ ������, ��������� ������ [DATA]

char * _fastcall proViewSite(HSELECT hSelect, HRSC hRsc, int view,
                             char * point, int * stringlimit);


// ������ ���������� �����������
void _fastcall proGetView(MAPPROTOCOL * data, PROCONTROL * proControl,
                          PRODATA * proData);


// ������ ������ �������� ����
void _fastcall proGetMap(TASKPARMEX * parm, MAPPROTOCOL * data,
                         PROCONTROL * proControl);

#endif  // PROTOCOL_H
