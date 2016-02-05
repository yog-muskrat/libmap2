
//                        �� HMAP

//                        ��� �������� ��������������� ��������
//                        �������� ��������� PARAM ��� ����������
#if !defined(MAPERRPR_H)
#define MAPERRPR_H

#ifndef MAPAPI_H
  #include "mapapi.h"
#endif

#ifndef MAPDEF_H
  #include "mapdef.h"
#endif

#include "errtype.rh"          

#ifdef WIN32API
#pragma pack(push,1)           
#endif

typedef struct ERRORINFO
{
 long  Length;                 // ����� ���������
 long  ErrorType;              // ��� ������
 long  Amend;                  //
 long  Mark;                   //
 long  FirstListNumber;        // ����� ����� ������� �������
 long  FirstObjectNumber;      // ����� ������� ������� �������
 long  FirstNumberSemantic;    // ����� ��������� ������� �������
 char  FirstListName[32];      // ��� ����� ������� �������
 long  FirstKey;               // ������������� ������� �������
 long  FirstNumberSubject;     // ����� ���������� ������� �������
 DOUBLEPOINT FirstPoint;       // ���������� ������� �������
 long  SecondListNumber;       // ����� ����� ������� �������
 long  SecondObjectNumber;     // ����� ������� ������� �������
 long  SecondNumberSemantic;   // ����� ��������� ������� �������
 char  SecondListName[32];     // ��� ����� ������� �������
 long  SecondKey;              // ������������� ������� �������
 long  SecondNumberSubject;    // ����� ���������� ������� �������
 DOUBLEPOINT SecondPoint;      // ���������� ������� �������
 char  Title[80];              // ��������� ������ ��� ���������
}ERRORINFO;

// ����� ��������� ������
typedef struct WORKFLAG
   {
   long Struct;                // ��������� ���������
   long Pasp;                  // ��������� ��������
   long Rsc;                   // ��������� ��������������
   long Data;                  // ��������� �������
   long Semn;                  // ��������� ���������
   long TopologData;           // ��������� ���������
   long Add;                   // ���������
   } WORKFLAG;

// �������� ���������� ��������
/*typedef struct PARAMCONTROL
    {
    long Kind;                   // ��� ��������������
    long Loop;                   // ������� �������������� ������
    double Close;                // ����� ��������� ��������
    double Reach;                // ����� ����������� �� �����
    } PARAMCONTROL;
*/
// ����� ��������� ��� ������ ��������
typedef struct PARAM
   {
   long Parm1;
   long Parm3;
   double Parm2;
   double Parm4;
   } PARAM;

typedef struct PROTOCOL
    {
    long Text;
    long Bin;
    long Sit;
    } PROTOCOL;

typedef struct WORKCONTROL
   {
    long Kind;                   // ��� ��������
    long Prot;                   // ��� ���������
    PARAM Param;                 // ��������� ��������
   } WORKCONTROL;

#ifdef WIN32API
#pragma pack(pop)           
#endif

enum KINDCONTROLNEW
   {
   IKC_NOWORK            = 0,    // ��� ���������
   IKC_CONTROL           = 1,    // ��������
   IKC_EDIT              = 2,    // ��������������
   IKC_DELERROR          = 3,    // �������� ��������� ��������� �������
   IKC_DELOBJECT         = 4     // �������� ������� � �������
   };

enum REGIMPROT
    {
    IRP_NO               = 0,
    IRP_ALL              = 1,
    IRP_SELECT           = 2
    };

enum KINDPROT
   {
   IKP_NOPROT            = 0,
   IKP_LOG               = 1,
   IKP_ERR               = 2,
   IKP_LOGERR            = 3,
   IKP_SIT               = 4,
   IKP_LOGSIT            = 5,
   IKP_ERRSIT            = 6,
   IKP_ALL               = 7
   };

#define COUNTTYPECONTROL 70

enum BEGIN_KINDCONTROL
   {
//   IBK_STRUCT            = 0,
   IBK_STRUCT_PASP       = 0,
   IBK_STRUCT_DATA       = 1,
   IBK_STRUCT_SEMN       = 2,
   IBK_STRUCT_DRAW       = 3,       
   IBK_STRUCT_RSCOBJ     = 4,
   IBK_STRUCT_RSCSEM     = 5,
   IBK_STRUCT_RSCCLS     = 6,
//   IBK_PASP              = 10,
   IBK_PASP_FRAME        = 10,
   IBK_PASP_GEO          = 11,
   IBK_PASP_RULE         = 12,
   IBK_PASP_CONSTPROJ    = 13,
   IBK_RSC               = 20,
//   IBK_DATA              = 30,
   IBK_DATA_NULL         = 30,
   IBK_DATA_BORDER       = 31,
   IBK_DATA_CLOSESQ      = 32,
   IBK_DATA_CLOSELN      = 33,
   IBK_DATA_DIRECT       = 34,
   IBK_DATA_REACH        = 35,
   IBK_DATA_EQUAL        = 36,
//   IBK_SEMN              = 40,
   IBK_SEMN_PASS         = 40,
   IBK_SEMN_UNEXPECTED   = 41,
   IBK_SEMN_VALUE        = 42,
//   IBK_TOPOLOG           = 50,
   IBK_TOPOLOG_LOOP      = 50,
   IBK_TOPOLOG_SUBJECT   = 51,
   IBK_TOPOLOG_DUPKEY    = 52,
   IBK_TOPOLOG_CROSS     = 53,
   IBK_TOPOLOG_MAIN      = 54,
   IBK_TOPOLOG_DUPDATA   = 55,
   IBK_TOPOLOG_GAP       = 56,
   IBK_TOPOLOG_ADJUST    = 57,
//   IBK_ADD               = 60
   IBK_ADD_SPACE         = 60,
   IBK_ADD_BREAKOFF      = 61,
   IBK_ADD_WATER         = 62,
   IBK_ADD_Z             = 63,
   IBK_ADD_INPUT         = 64,   
   IBK_ADD_HIEGHT        = 65,
   IBK_ADD_ADJUST        = 66
   };

//------------------------------------------------------------------
// ����� IEC-����� (errtype.rh)
//------------------------------------------------------------------
//#define ErrorTypeCount 25   
//#define ErrorTypeCount 32   
//#define ErrorTypeCount 37   
#define ErrorTypeCount   IEC_TYPECOUNT   


#define KindControlCount 16

enum KINDCONTROL  // ���� ������
    {
    IKC_MAP_STRUCT         = 1,   // ������ � ��������� ������

    IKC_DAT_EQUAL          = 2,   // ������� ����� � �������
    IKC_DAT_CLOSESQ        = 3,   // O����� �� �������
    IKC_DAT_CLOSELN        = 4,   // O����� �� �������
    IKC_DAT_LOOP           = 5,   // ����� � ������
    IKC_DAT_BORDER         = 6,   // �������� �������
    IKC_DAT_NULL           = 7,   // ����������� ������
    IKC_DAT_REACH          = 8,   // ������ ����������� �� �����
    IKC_DAT_DIRECT         = 9,   // ����������� ����������
    IKC_DAT_SUBJECT        = 10,  // ������ ����������


    IKC_SEM_VALUE          = 11,  // ������������ ��������
    IKC_SEM_PASS           = 12,  // ��� ������������ �������������
    IKC_SEM_UNEXPECTED     = 13,  // ������ ���������

    IKC_SEM_HEIGHT         = 14,  // ���������� ������

    IKC_DAT_ADJUST         = 15   // ������ � ������
    };


enum DATAFLAGCONTR
     {
     DATA_NULL       = 0x80000000l,
     DATA_BOX        = 0x40000000l,
     DATA_CLOSESQ    = 0x20000000l,
     DATA_CLOSELINE  = 0x10000000l,
     DATA_DIRECT     = 0x08000000l,
     DATA_REACH      = 0x04000000l,
     DATA_DBLEPOINT  = 0x02000000l,
     DATA_LOOP       = 0x01000000l,
     DATA_POBJECT    = 0x00800000l,
//     enum FLAGCONTR {
     SEMN_ABSENCEOBLIGE = 0x80000000l,
     SEMN_UNPERMISSIBLE = 0x40000000l,
     SEMN_RANGE         = 0x20000000l
//                    };
     };



extern "C"
{
// �������� ������� ����� ���������
int _export WINAPI ExistFileError(TMap * map);

// ������ ���������� ������ � �����
int _export WINAPI GetCountError(TMap * map);
// ������ ��������� ������ �� ����� ���������
int _export WINAPI LoadError(TMap * map,int number,ERRORINFO * error);
// ������ ���������� � ���� ���������
int _export WINAPI WriteError(TMap * map,ERRORINFO * error);

// �������� ����� ���������
int _export WINAPI DeleteFileError(TMap * map);

// ������������ ������� � �������������� ������
int _export WINAPI MarkError(TMap * map,int number);

// �������� ������
int _export WINAPI ControlMap(HMAP doc,WORKCONTROL * parm,HWND handle,HSELECT);

// �������� ������� ����� ���������
int _export WINAPI ExistFileDocError(HMAP map);

// ������ ���������� ������ � �����
int _export WINAPI GetCountDocError(HMAP map);
// ������ ��������� ������ �� ����� ���������
int _export WINAPI LoadDocError(HMAP map,long int number,ERRORINFO * error);
// ������ ���������� � ���� ���������
int _export WINAPI WriteDocError(HMAP map,ERRORINFO * error);
int _export WINAPI WriteDocTitle(HMAP hmap,char * text);    
// �������� ����� ���������
int _export WINAPI DeleteFileDocError(HMAP map);

// ������������ ������� � �������������� ������
int _export WINAPI MarkDocError(HMAP map,long int number);

}

#endif