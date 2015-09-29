
#ifndef MAPLSTBS_H
#define MAPLSTBS_H

#ifndef MAPVERSN_H
  #include "mapversn.h"
#endif

#ifndef MAPREGIS_H
  #include "mapregis.h"  // �������� ����������� ����� (��)
#endif

#ifndef MAPDATA_H
  #include "mapdata.h"
#endif

#ifndef MAPHDR_H
  #include "maphdr.h"
#endif

#ifndef MAPDAT_H
  #include "mapdat.h"
#endif

#ifndef MAPSEM_H
  #include "mapsem.h"
#endif

#ifndef MAPDRW_H
  #include "mapdrw.h"
#endif

#ifndef MAPVEC_H
  #include "mapvec.h"
#endif

enum // �������������� ������
{
  LABEL_HDR = 0x00524448L,  // HDR0
  LABEL_DAT = 0x00544144L,  // DAT0
  LABEL_DRW = 0x00575244L,  // DRW0
  LABEL_VEC = 0x00434556L,  // VEC0

  LABEL_HDR_TURN = 0x48445200L,  // 0RDH
  LABEL_DAT_TURN = 0x44415400L,  // 0TAD
  LABEL_DRW_TURN = 0x44525700L,  // 0WRD
  LABEL_SEM_TURN = 0x53454D00L,  // 0MES    
  LABEL_VEC_TURN = 0x56454300L,  // 0CEV
};

#define Degree8Dec (100000000L)   // 10 ** 8

// ===============================================================

typedef struct PART
{
  char * ADDR;           // ����� ������� ������
  unsigned long   MIN;   // ��������� �������� �����
  unsigned long   MAX;   // �������� �������� �����
}
  PART;


typedef struct LISTSTACK    
{
  int    Number;      // ����� �����
  unsigned int Count; // ����� ��������� � �����
  int    Mode;        // ����� �������� �����
  HANDLE Head;        // ������������� ����� HDR
  HANDLE Data;        // ������������� ����� DAT
  HANDLE Semn;        // ������������� ����� SEM
  HANDLE Draw;        // ������������� ����� DRW
  HANDLE BackHead;    // ������������� ����� Back HDR
  HANDLE BackData;    // ������������� ����� Back DAT
  HANDLE BackSemn;    // ������������� ����� Back SEM
  HANDLE BackDraw;    // ������������� ����� Back DRW
  int    Reserve;     // ������
}
 LISTSTACK;

// ������������ ����� ������������ �������� ������
#define LISTSTACKLIMIT  12

class _DLLCLASS TObjectInfo;
class _DLLCLASS TMap;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  ����� ���������� ��������� ����� +++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#if defined(COMPACTGIS) || defined(MINIDATA) || defined(WINCE)
#define  HBLOCKNUMB  2L            // ����� ������
#define  BLOCKSIZE  (48*1024L)     // ������ ����� (48 ��)
#else
#define  HBLOCKNUMB  32L           // ����� ������          
#define  BLOCKSIZE  (96*1024L)     // ������ ����� (96 ��)  
#endif

#define  HMINSIZE   (BLOCKSIZE*3L) // ����������� ������

typedef struct HEADBUFFER
{
 char *        Memory;        // ����� ������� ������ ��� �������
 HANDLE        File ;         // ������������� ����� ������
 int           Number ;       // ����� ������
 int           Last;          // ��������� ������������ ����
 unsigned long Size;          // ������ ������� ������
 unsigned long BlockSize;     // ������ ����� ������
 PART Part[HBLOCKNUMB];       // �������� ������ ������
}
 HEADBUFFER;

// ���������������� ���������� ������ ����������
void _fastcall hbInit(HEADBUFFER * buffer);

// ���������� ����� ����������
void _fastcall hbFree(HEADBUFFER * buffer);

// �������� ����� ������ ������ ����������
void _fastcall hbClear(HEADBUFFER * buffer);

// �������� ��������� � ������
void _fastcall hbUpdate(HEADBUFFER * buffer, int number, char * record);

// ��������� ������,���������������� ����� ����������
int _fastcall hbAllocHeadBuffer(HEADBUFFER * buffer, unsigned long int size);

// ��������� ����� ������ �� ������ ������ ���������
char * _fastcall hbGetDataAddr(HEADBUFFER * buffer, int number);

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  ����� ������ ��������� ����� +++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#if defined(COMPACTGIS) || defined(MINIDATA) || defined(WINCE)
#define DBLOCKNUMB 1        // ����� ������
#else
#define DBLOCKNUMB 8        // ����� ������
#endif

#define DBLOCKSIZE 0x10000L // ������ ����� (64 ��) 

typedef struct DATABUFFER
{
 char *        Memory;        // ����� ������� ������ ��� �������
 HANDLE        File ;         // ������������� ����� ������
 int           Number ;       // ����� ������
 int           Last;          // ��������� ������������ ����
 unsigned long Size;          // ������ ������� ������
 PART Part[DBLOCKNUMB];       // �������� ������ ������
}
 DATABUFFER;

// ���������������� ���������� ������ ������
void _fastcall dbInit(DATABUFFER * buffer);

// ���������� ����� ������
void _fastcall dbFree(DATABUFFER * buffer);

// �������� ����� ������ ������ ������
void _fastcall dbClear(DATABUFFER * buffer);

//  ��������� ������, ���������������� ����� ������
int _fastcall dbAllocDataBuffer(DATABUFFER * buffer, unsigned long int size);

// ��������� ����� ������ �� ��������
char * _fastcall dbGetDataAddr(DATABUFFER * buffer, unsigned long int offset);


char * _fastcall dbGetSemnAddr(DATABUFFER * buffer, unsigned long int offset);

#if defined(COMPACTGIS) || defined(MINIDATA) || defined(WINCE)
#define LDBLOCKNUMB 4         // ����� ������
#else
#define LDBLOCKNUMB 64        // ����� ������                  
#endif

//#define LDBLOCKSIZE (DATALENGTHLIMIT + 1024) // ������ ����� 
#define LDBLOCKSIZE (256*1024L)                // ������ ����� 

typedef struct LONGBUFFER
{
 char *        Memory;        // ����� ������� ������ ��� �������
 HANDLE        File ;         // ������������� ����� ������
 int           Number ;       // ����� ������
 int           Last;          // ��������� ������������ ����
 int           BlockSize;     // ������ ����� ������
 unsigned long Size;          // ������ ������� ������
 PART Part[LDBLOCKNUMB];      // �������� ������ ������
}
 LONGBUFFER;

// ���������������� ���������� ������ ������
void _fastcall lbInit(LONGBUFFER * buffer);

// ���������� ����� ������
void _fastcall lbFree(LONGBUFFER * buffer);

// �������� ����� ������ ������ ������
void _fastcall lbClear(LONGBUFFER * buffer);

//  ��������� ������, ���������������� ����� ������
int _fastcall lbAllocDataBuffer(LONGBUFFER * buffer,
                                unsigned long int size, int notlimit);

// ��������� ����� ������ �� ��������
char * _fastcall lbGetDataAddr(LONGBUFFER * buffer, unsigned long int offset);

#define SemnZero 0  

typedef struct
{
  char Value[64];
}
  SETID;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  �������� ���� ����������� �����  +++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TMapList
{
 public :

 TMapList();
 ~TMapList();


 /***************************************************************
 *                                                              *
 *      �������/������� ���� �����                              *
 *                                                              *
 ***************************************************************/

public :

 // ��������� �������� ����� � ����������� ����� ������
 // ��� ������ ���������� ����
 int CopyList(TMap * map, int number, LISTREGISTER * mapreg,
              char * path);

 int CopyList(TMap * map, int number, TListRegister * mapreg,
              char * path)
 {
   return CopyList(map, number, (LISTREGISTER *)mapreg, path);
 }

 //  ��������� �������� ����� � ����������� ����� ������
 //  � ���������� ���������
 //  ��� ������ ���������� ����                 // �� ���������� �� �

 int CopyListAndChange(TMap * map, char * prefix,
                       TMap * srcmap, int list, HWND handle);

 // ��������� �������� ����� ������� �� ���������
 // ������� ������ ����� ������
 // map     - �����, � ������� ��������� ����
 // number  - ����� ������������ �����
 // mapreg  - �������� �����
 // ��� ������ ���������� ����
 int CreateList(TMap * map, int number, LISTREGISTER * mapreg);
 int CreateList(TMap * map, int number, TListRegister * mapreg)
 {
   return CreateList(map, number, (LISTREGISTER *)mapreg);
 }

 // ������� ��� ������� �����                      
 // ��� ������ ���������� ����
 int ClearList(TMap * map, int number);

 // ������� ���� ������ �����
 // mode - ����� �������� �����,
 // ���� ������ 0, ������������� ������ ��� ������ ������,
 // ���� ������ 0 - ����������� ������� ����
 // (������ ����������� � �����������)
 void Close(int mode = -1);

 // ��������� ����������� �����
 // ��� ������ ���������� ����
 int IsActive() { return ( List != 0 ); }

 // ���������� �������� ����� ������� �� ���������
 int ListRegister(int list, LISTREGISTER * mapreg);
 int ListRegister(int list, TListRegister * mapreg)
  {
    return ListRegister(list,(LISTREGISTER *)mapreg);
  }

 // ���������/������� ������������ �����
 const char* Nomenclature(const char* nomenclature);
 const char* Nomenclature();

 // ���������/������� �������� �����
 const char* Name(const char* name);
 const char* Name();

 // ������� �������� ���� � ������ �����
 // ��� ������ ���������� ����
 int Open(TMap * map, int number);

 // �������� ��� ���� ������������ ������� ������
 // ��� ������ ���������� ����
 int AllocateNotLimit(TMap * map, int number);

 // ��������������� ������� �������� ����� � ���������
 // ��������� ������� ����� � �������� �����������
 // ��� ������ ���������� ����
 int ReplaceListObjects(double deltaX, double deltaY);

 /***************************************************************
 *                                                              *
 *      ������ / ��������� ������� � �������� �����             *
 *                                                              *
 ***************************************************************/


public :

 // ��������� ����� �������� � �����
 int Count();

 // ��������� ��� ����� ������
 const char * DataName();

 // ��������� ��� ����� �������
 const char * DrawName();

 // ��������� ��� ������ ���������� ��������� ��������
 long int Error() { return (LastError); }

 // ��������� ��� ����� ���������� ������ (����������) ��������
 const char * HeadName();

 // ������/��������� �������� ���������� ��������� ��� Site
 int IsBorderUpdate() { return BorderUpdate; }
 int IsBorderUpdate(int mode) { return BorderUpdate = mode; }

 // ������ - �������� ����� ��������������� ?
 int IsDirty() { return Isdirty; }
 int IsDirty(int dirty) { return (Isdirty = dirty); }

 // ���������/���������� ������� ������� ����������� ���������� ������
 int IsFreeAppend() { return FreeAppend; }
 int IsFreeAppend(int start) { return FreeAppend = start; }

 // ���������/���������� ������� ��������������� ������
 int IsSorted();
 int IsSorted(int sorted);

 // ������ - ����� �� ������������� ���� ?
 int IsWrite() { return (FileAccess & GENERIC_WRITE); }

 // ��������� ����� �����
 int Number() { return List; }

 // ��������� ��� ����� ���������
 const char * SemnName();

 // ���������� ���������� ����� �������� � �����
 // (��� ������ ������ TINYDATA)
 int SetObjectsLimit(int limit);

 // ���������� ��� ������ ���������� ��������� ��������
 long int Error(int error) { return (LastError = error); }

 // ������� ���� ��������� � �������� ������
 int CreateSemnFile();

protected :

 // ������� ���� ������� � �������� ������
 int CreateDataFile();

 // ������� ���� ������� � �������� ������
 int CreateDrawFile();

 // ��������� ���� � ��������� ���������� (LOG)
 const char * PathLOG();

 /***************************************************************
 *                                                              *
 *         ������ ���������� ������ � �����                     *
 *                                                              *
 ***************************************************************/

public :

 // ���������/����������	���� �������� ������ �����
 const char* CreationDate(const char* date);
 const char* CreationDate();

 // ���������/����������	���� ������ ���������
 const char* Date(const char* date);
 const char* Date();

 // ���������/����������	���� ���������
 const char* DateAngle(const char* date);
 const char* DateAngle();

 // ���������/������� ���� ��������� ���������
 int MaterialKind(int kind);
 int MaterialKind();

 // ���������/������� ���� ��������� ���������
 int MaterialType(int type);
 int MaterialType();

 // ���������/������� ���������� ���������
 double MagneticAngle(double value);
 double MagneticAngle();

 // ���������/������� �������� ��������� ���������� ���������
 double YearMagneticAngle(double value);
 double YearMagneticAngle();

 // ���������/������� �������� ��������� ����������
 double MeridianAngle(double value);
 double MeridianAngle();

 // ���������/������� ������ ������� �������
 long int ReliefHeight(long int height);
 long int ReliefHeight();

 /***************************************************************
 *                                                              *
 *        ��������� ��������� ������ ...\LOG\... ^DA,^SE,^HD    *
 *    (�������� ����� ���� ����������� �������� �����)          *
 *                                                              *
 ***************************************************************/

public :

 // ������� ��������� �����
 void DeleteBackFiles();

 // ��������� ����� ����������� �����
 // ��� ������ ���������� ����
 int GetBackObjectCount();

 // ������� ����� �������
 // number - ���������� ����� ������, ������� c 1
 // ��� ������ ���������� ����
 int MarkBackObject(int number);

 // ������� ����� �������
 // number - ���������� ����� ������ ����� ���� �����, ������� c 1
 // ��� ������ ���������� ����
 TObjectHead * ReadBackObject(int number, char *buffer);

 // ��������� ����� ������� � ��������� �����
 // ��� ������ ���������� ����
 int _fastcall SaveBackObject(TObjectHead * head,
                              OBJECTDATA * data = 0,
                              SEMANTIC   * semn = 0,
                              IMGDRAW    * draw = 0);   

 /***************************************************************
 *                                                              *
 *                 ������� / ���������                          *
 *   ������������� � ������������� ��������� ����� �����        *
 *      ������������� ���������� ���������� � ��������          *
 *                                                              *
 ***************************************************************/

public :

 // ���������/���������� "B" ���-��������� ���� ����� (������� !)
 double  BSouthWestCoordinate(double value);
 double  BSouthWestCoordinate();
 double  BSW() {return BSouthWestCoordinate();}
 double  BSW(double value) {return BSouthWestCoordinate(value);}

 // ���������/���������� "B" ������-��������� ���� �����
 double  BNorthWestCoordinate(double value);
 double  BNorthWestCoordinate();
 double  BNW() {return BNorthWestCoordinate();}
 double  BNW(double value) {return BNorthWestCoordinate(value);}

 // ���������/���������� "B" ������-���������� ���� �����
 double  BNorthEastCoordinate(double value);
 double  BNorthEastCoordinate();
 double  BNE() {return BNorthEastCoordinate();}
 double  BNE(double value) {return BNorthEastCoordinate(value);}

 // ���������/���������� "B" ���-���������� ���� �����
 double  BSouthEastCoordinate(double value);
 double  BSouthEastCoordinate();
 double  BSE() {return BSouthEastCoordinate();}
 double  BSE(double value) {return BSouthEastCoordinate(value);}

 // ���������/���������� "L" ���-��������� ���� �����
 double  LSouthWestCoordinate(double value);
 double  LSouthWestCoordinate();
 double  LSW() {return LSouthWestCoordinate();}
 double  LSW(double value) {return LSouthWestCoordinate(value);}

 // ���������/���������� "L" ������-��������� ���� �����
 double  LNorthWestCoordinate(double value);
 double  LNorthWestCoordinate();
 double  LNW() {return LNorthWestCoordinate();}
 double  LNW(double value) {return LNorthWestCoordinate(value);}

 // ���������/���������� "L" ������-���������� ���� �����
 double  LNorthEastCoordinate(double value);
 double  LNorthEastCoordinate();
 double  LNE() {return LNorthEastCoordinate();}
 double  LNE(double value) {return LNorthEastCoordinate(value);}

 // ���������/���������� "L" ���-���������� ���� �����
 double  LSouthEastCoordinate(double);
 double  LSouthEastCoordinate();
 double  LSE() {return LSouthEastCoordinate();}
 double  LSE(double value) {return LSouthEastCoordinate(value);}

 // ���������/���������� "X" ���-��������� ���� ����� (����� !)
 double XSouthWest(double value);
 double X1m(double value) { return XSouthWest(value); }
 double XSouthWest();
 double X1m() { return XSouthWest(); }

 // ���������/���������� "X" ������-��������� ���� �����
 double XNorthWest(double value);
 double X2m(double value) { return XNorthWest(value); }
 double XNorthWest();
 double X2m() { return XNorthWest(); }

 // ���������/���������� "X" ������-���������� ���� �����
 double XNorthEast(double value);
 double X3m(double value) { return XNorthEast(value); }
 double XNorthEast();
 double X3m() { return XNorthEast(); }

 // ���������/���������� "X" ���-���������� ���� �����
 double XSouthEast(double value);
 double X4m(double value) { return XSouthEast(value); }
 double XSouthEast();
 double X4m() { return XSouthEast(); }

 // ���������/���������� "Y" ���-��������� ���� �����
 double YSouthWest(double value);
 double Y1m(double value) { return YSouthWest(value); }
 double YSouthWest();
 double Y1m() { return YSouthWest(); }

 // ���������/���������� "Y" ������-��������� ���� �����
 double YNorthWest(double value);
 double Y2m(double value) { return YNorthWest(value); }
 double YNorthWest();
 double Y2m() { return YNorthWest(); }

 // ���������/���������� "Y" ������-���������� ���� �����
 double YNorthEast(double value);
 double Y3m(double value) { return YNorthEast(value); }
 double YNorthEast();
 double Y3m() { return YNorthEast(); }

 // ���������/���������� "Y" ���-���������� ���� �����
 double YSouthEast(double value);
 double Y4m(double value) { return YSouthEast(value); }
 double YSouthEast();
 double Y4m() { return YSouthEast(); }

 /***************************************************************
 *                                                              *
 *       ������� �������� ��������, ������� � ���������         *
 *                                                              *
 ***************************************************************/

public:

 // ��������� ������ ����� ����� �����
 // ���� ����� ������� - ������� ������ ��������� �����
 // ���� ����� ���, �� ������������ 0
 TObjectDesc GetListFrameDesc() { return GetFrameDesc(); }
 TObjectDesc GetFrameDesc();

 // ��������� ����� ������� - ����� �����
 // ��� ������ ������������ ����
 int GetListFrameNumber();

 // ��������� ������� �� �������� (��� ������ = 0)
 // ��� ������ ���������� ����
 OBJECTDATA * DataAddr(long offset);

 // ��������� ������� �������
 // ��� ������ ���������� ����
 OBJECTDATA * ObjectData(TObjectDesc desc) { return DataAddr(desc.Metric()); }

#ifndef TINYDATA
 // ��������� ����������� �������� �������� �������
 // �� ��������
 // ��� ������ ���������� ����
 IMGDRAW * DrawAddr(long offset);
#endif

 // ��������� �������� "����������" ������� � ������������
 // ��� ������ ���������� ����

 TObjectHead * _fastcall GetLastLocalHead(int local)
 {
   return GetObject(GetLastLocalNumber(local));
 }

 // ��������� ����� "����������" ������� � ������������
 // ��� ������ ���������� ����

 int _fastcall GetLastLocalNumber(int local);

 // ��������� �������� "�������" ������� (� ���������� �������)
 // "������" ������ ���������� �������
 // ������� ���������� � �������
 // ��� ������ ���������� ����
 TObjectHead * FirstHead();

 // ��������� ����� "�������" ������� (� ���������� �������)
 // ��� ������ ���������� ����
 int FirstNumber();

 // ��������� �������� "����������" ������� (� ���������� �������)
 // "���������" ������ ���������� �������
 // ������� ���������� � �������
 // ��� ������ ���������� ����
 TObjectHead * LastHead();

 // ��������� ����� "����������" ������� (� ���������� �������)
 // ��� ������ ���������� ����
 int LastNumber();

 // ��������� �������� ������� �� ������
 // ������ number ���������� �������
 // ��� ������ ���������� ����
 TObjectHead * ObjectDesc(int number);

 TObjectHead * GetObject(int number)
 {
   return ObjectDesc(number);
 }

#ifndef TINYDATA
 // ��������� ����������� �������� �������� �������
 // �� ��������
 // ��� ������ ���������� ����
 IMGDRAW * ObjectDraw(long offset)
	 {
  		return DrawAddr(offset);
	 }
#endif

 // ��������� ��������� �� ��������
 SEMANTIC * SemnAddr(long offset);

 /***************************************************************
 *                                                              *
 *    ������ �������������� �������� �������� ����� �����       *
 *                                                              *
 ***************************************************************/

public:

 // ������� ����� ������
 // ��� ������� ���������� ����, ��� ������ - ��. Error()
 // ��� �������� ���������� - ����� ���������� ������� � �����
 // ������� ���������� � �������
 int _fastcall AppendObjectData(TObjectHead * head,
                                OBJECTDATA  * data = 0,
                                SEMANTIC    * semn = 0,
                                IMGDRAW     * draw = 0);

 // ������� ����� ������
 // ��� ������� ���������� ����, ��� ������ - ��. Error()
 // ��� �������� ���������� - ����� ���������� ������� � �����
 // ������� ���������� � �������
 int AppendObject(TObjectDesc desc,
                  TObjectData data = (char *)0,
                  TObjectSemn semn = (char*)0,
                  TObjectDraw draw = (char*)0)
 {
   return  AppendObjectData(desc.Base, data.Base, semn.Base, draw.Base);
 }

 int AppendObject(TObjectInfo * object);

 // ������� ������, �������� ������� � �����
 // ��� ������� ���������� ����, ��� ������ - ��. Error()
 int DeleteObject(int number);

 // �������� ������,number - ����� ������� � �����,
 // ����� ���������� ���������� �������
 // ��� ������� ���������� ����, ��� ������ - ��. Error()
 // ��� �������� ���������� - ����� ������������������ ������� � �����
 // ���� number ����� ��������, ������������ �����, ������������
 // �� ���������� �������
 int _fastcall UpdateObjectData(int number, TObjectHead * head,
                                OBJECTDATA * data = 0,
                                SEMANTIC   * semn = 0,
                                IMGDRAW    * draw = 0);

 // �������� ������,number - ����� ������� � �����,
 // ����� ���������� ���������� �������
 // ��� ������� ���������� ����, ��� ������ - ��. Error()
 // ��� �������� ���������� - ����� ������������������ ������� � �����
 // ���� number ����� ��������, ������������ �����, ������������
 // �� ���������� �������
 int UpdateObject(int number,TObjectDesc desc,
                  TObjectData  data = (char *)0,
                  TObjectSemn  semn = (char*)0,
                  TObjectDraw  draw = (char*)0)
 {
   return UpdateObjectData(number, desc.Base, data.Base,
                                   semn.Base, draw.Base);
 }

 int UpdateObject(int number, TObjectInfo * object);

 // �������� ����������� �������� �������,
 // number - ����� ������� � �����, ����� ���������� ���������� �������
 // ��� ������� ���������� ����, ��� ������ - ��. Error()
 // ��� �������� ���������� - ����� ������������������ ������� � �����
 // ���� number ����� ��������, ������������ �����, ������������
 // �� ���������� �������
 int UpdateObjectDraw(int number, IMGDRAW * draw);

 // ���������� �������� ������� � �����
 void _fastcall BuildBorder(TObjectHead * head, OBJECTDATA * data,
                            SEMANTIC * semn, IMGDRAW * draw);

 // ���������� �������� �������
 void _fastcall BuildTextBorder(TObjectHead * head, OBJECTDATA * data,
                                SEMANTIC    * semn, IMGDRAW * draw = 0);

protected:

 //  ������� �� ����� �������� �������
 //  number - ����� �������
 //  desc   - ����������� �������� �������
 //  ��� �������� ���������� ���������� ����,
 //  ��� ������ - ��� ������
 int _fastcall ReadObjectDesc(int number, TObjectHead * head);

 //  �������� � ���� �������� �������
 //  ��� �������� ���������� ���������� ����,
 //  ��� ������ - ��� ������
 int _fastcall WriteObjectDesc(int number, TObjectHead * head);

 //  �������� � ���� ������� �������
 //  ��� �������� ���������� ���������� ����,
 //  ��� ������ - ��� ������
 int _fastcall WriteObjectData(TObjectHead * head, OBJECTDATA * data);

 //  �������� � ���� ������� �������
 //  ��� �������� ���������� ���������� ����,
 //  ��� ������ - ��� ������
 int _fastcall WriteObjectDraw(TObjectHead * head, IMGDRAW * draw);

 //  �������� � ���� ��������� �������
 //  ��� �������� ���������� ���������� ����,
 //  ��� ������ - ��� ������
 int _fastcall WriteObjectSemn(TObjectHead * head, SEMANTIC * data);


 /***************************************************************
 *                                                              *
 *        ��������� ��������� ������ ...\LOG\... ^DA,^SE,^HD    *
 *    (�������� ����� ���� ����������� �������� �����)          *
 *                                                              *
 ***************************************************************/

public:

 // ������������ ����� �������
 // number - ���������� ����� ������ ����� ���� ��������
 // ��� ������ ���������� ����
 int RestoreBackObject(int number, TObjectInfo * info);

 // ���������������� ������� ����������������� ����� ������� info
 // copynumber - ���������������� ����� ����� ������� info (1, 2, ...)
 // � ������� �� ��������� �������� �������������� � ����������
 // ���������� � ���������������� ����������� copynumber,
 // ���� �� ����� ������� ������ ����� ��� ����� ����������
 // ��� ������ ���������� ����
 int ReadObjectCopyByNumber(int copynumber, TObjectInfo * info);

 // ������� ����������������� ����� ������� info
 // ���������� ����� ���������� (Commit) �������������� ����� �������
 // �� ����� (������ ����������� �������� ��������������)
 // ������� ����� ������� �� ������ �� copynumber
 // ����� copynumber+1 ���������� ������
 // ��� ������ ���������� ����
 int DeleteObjectCopyToNumber(int copynumber, TObjectInfo * info);

 // ������ ����
 void LockList()
 {
#ifndef HIDESECTION
   EnterTheCriticalSection(&Section);
#endif
 }

 // ���������� ����
 void UnLockList()
 {
#ifndef HIDESECTION
  LeaveTheCriticalSection(&Section);
#endif
 }

public:

 int   List;               // ����� �������� �����
 int   ErrorList;          // ����� ���������� �����

#ifndef GISSERV
 int   ShowNumber;         // ����� �������
#endif

 TMap * MapBase;           // ��������� �� �����,� ������� ����������� ����

 HEADBUFFER  HeadBuff;     // �������� ������ ���������� ��������� �����
 LONGBUFFER  DataBuff;     // �������� ������ ������� ��������� �����
 DATABUFFER  SemnBuff;     // �������� ������ ��������� ��������� �����
 DATABUFFER  DrawBuff;     // �������� ������ ������� ��������� �����

#ifndef TINYDATA
 TVectorFile VectBuff;     // �������� ������ 3D-�������� ��������� �����
#endif

 HANDLE File_HDR;          // ������������� ����� ����������
 HANDLE File_DAT;          // ������������� ����� ������
 HANDLE File_SEM;          // ������������� ����� ���������
 HANDLE File_DRW;          // ������������� ����� �������

 SETID SetId;              // ������������� ������ �������� ��'�����
 SHEETDESC * LstId;        // ������������� ���������� ������ �� ����

 char Path_LIST[MAX_PATH]; // ���� ������� � ������ �������� �����

 int   FileAccess;         // ����� ������� � �����
 int   FileShare;          // ����� ������� � �����

 long int LastError;       // ��� ������ ��������� ��������

 int Isdirty;              // ������� ������������� ������

 HANDLE Back_HDR;          // ������������� ���������� �����
 HANDLE Back_DAT;          // ������������� ���������� �����
 HANDLE Back_SEM;          // ������������� ���������� �����
 HANDLE Back_DRW;          // ������������� ���������� �����

 int FreeAppend;           // ������� ���������� ����������� ����������

 int BorderUpdate;         // ������� ���������� ��������� �����

 long LockOffset;          // ������� ���������� �����

 struct LISTSTACK
  Stack[LISTSTACKLIMIT];   // ������ �������� ������

 unsigned int StackIndex;  // ������� ��������� � ����� ������

 int ActionLogMode;        // ����� ������� � �������

#ifndef HIDESECTION
 MAPCRITICALSECTION Section; // ������������� ������� �� ������ �������  
#endif
};

typedef TMapList MAPLISTDATA;

// ������� ������� ����
void _fastcall mlClose(MAPLISTDATA * data, int mode);

// ������� ����� ����
// ��� ������ ���������� ����
int _fastcall mlOpen(MAPLISTDATA * data, void * mapbase, int number);

// ��������� �������� ����� ������� �� ���������
// ������� ������ ����� ������
// ��� ������ ���������� ����
int _fastcall mlCreateList(MAPLISTDATA * data, void * map,       
                           int number, LISTREGISTER * mapreg);

// ���������� ������� "���� �� �������"
void _fastcall mlNotActive(MAPLISTDATA * data);

// ������������� ������ ��� �������� ������ �� ��������
int _fastcall mlAllocBuffers(MAPLISTDATA * data, int notlimit);

// ������������ ������, ������� ��� �������� ������ �� ��������
void _fastcall mlFreeBuffers(MAPLISTDATA * data);

// ��������� ���� �� ������
int _fastcall mlCheckError(MAPLISTDATA * data, int number);

// ������ ��������� �� ������
int _fastcall mlErrorMessage(MAPLISTDATA * data, int code,
                             const char * name, int number);

// ��������� ���������� ����� �� ������� LISTREGISTER
// ��� ������ ���������� ����
int _fastcall mlListRegister(MAPLISTDATA * data, int list,
                             LISTREGISTER * mapreg);

// ������� ������ � ������  ������ ����� �����
// ���������� ����� ������������ ����
// ��� ������ ���������� ����
int _fastcall mlWrite(HANDLE file, int offset,            
                      const char * address, int length);

int _fastcall mlWriteDesc(MAPLISTDATA * data, int offset,
                          const char * address);

int _fastcall mlWriteData(MAPLISTDATA * data, int offset,
                          const char * address, int length);

int _fastcall mlWriteDraw(MAPLISTDATA * data, int offset,
                          const char * address, int length);

int _fastcall mlWriteSemn(MAPLISTDATA * data, int offset,
                          const char * address, int length);

int _fastcall mlReadDesc(MAPLISTDATA * data, int offset,
                         char * address, int length);

int _fastcall mlReadData(MAPLISTDATA * data, int offset,
                         char * address, int length);

int _fastcall mlReadSemn(MAPLISTDATA * data, int offset,
                         char * address, int length);

// ��������� ����� �������� � �����
int _fastcall mlCount(MAPLISTDATA * data);

// �������� ����� ������ �� ����
// ��� ������� ���������� ����, ��� ������ - ��. Error()
// ��� �������� ���������� - ����� ������� � �����
int _fastcall mlAppendObjectData(MAPLISTDATA * mldata,
                                 TObjectHead * head, OBJECTDATA * data,
                                 SEMANTIC    * semn, IMGDRAW * draw);

// �������������� �� �����
// ��� ������� ���������� ����, ��� ������ - ��. Error()
// ��� �������� ���������� - ����� ������� � �����
int _fastcall mlUpdateObjectData(MAPLISTDATA * mldata, int number,
                                 TObjectHead * head, OBJECTDATA * data,
                                 SEMANTIC    * semn, IMGDRAW    * draw);

// �������� ����������� �������� �������,
// ��� ������� ���������� ����, ��� ������ - ��. Error()
int _fastcall mlUpdateObjectDraw(MAPLISTDATA * data,
                                 int number, IMGDRAW * draw);

// ��������� �������� ������� �� ������
// ������ number ���������� �������
// ��� ������ ���������� ����
TObjectHead * _fastcall mlGetObjectHead(MAPLISTDATA * data, int number);

// ��������� ������� ������� �� ������
// ������ number ���������� �������
// ��� ������ ���������� ����
OBJECTDATA * _fastcall mlGetObjectData(MAPLISTDATA * data, int number); 

// ��������� ��������� ������� �� ������
// ������ number ���������� �������
// ��� ������ ���������� ����
SEMANTIC * _fastcall mlGetObjectSemn(MAPLISTDATA * data, int number);

// ��������� ������� ������� �� ������
// ������ number ���������� �������
// ��� ������ ���������� ����
IMGDRAW * _fastcall mlGetObjectDraw(MAPLISTDATA * data, int number); 

// ������� �� ����� �������� �������
// ��� �������� ���������� ���������� ����,
// ��� ������ - ��� ������
int _fastcall mlReadObjectDesc(MAPLISTDATA * data,
                               int object, TObjectHead * head);

// �������� � ���� �������� �������
// ��� �������� ���������� ���������� ����,
// ��� ������ - ��� ������
int _fastcall mlWriteObjectDesc(MAPLISTDATA * data,
                                int object, TObjectHead * head);

// �������� � ���� ������� �������
// ��� �������� ���������� ���������� ����,
// ��� ������ - ��� ������
int _fastcall mlWriteObjectData(MAPLISTDATA * mldata,
                                TObjectHead * head, OBJECTDATA *  data);

// �������� ����������� �������� �������
int _fastcall mlWriteObjectDraw(MAPLISTDATA * data,
                                TObjectHead * head, IMGDRAW * draw);

// �������� � ���� ��������� �������
// ��� �������� ���������� ���������� ����,
// ��� ������ - ��� ������
int _fastcall mlWriteObjectSemn(MAPLISTDATA * data,
                                TObjectHead * head, SEMANTIC * semn);

// ���������� �������� ������� � �����
void _fastcall mlBuildBorder(MAPLISTDATA * mldata, TObjectHead * head,
                             OBJECTDATA * data, SEMANTIC * semn,
                             IMGDRAW    * draw);

//  ���������� �������� �������
void _fastcall mlBuildTextBorder(MAPLISTDATA * mldata, TObjectHead * head,
                                 OBJECTDATA *  data, SEMANTIC * semn,
                                 IMGDRAW    *  draw);

// ��������� ������ ����� ����� �����
// ���� ����� ������� - ������� ������ ��������� �����
// ���� ����� ���, �� ������������ 0
TObjectHead * _fastcall mlGetListFrameDesc(MAPLISTDATA * data);

// ��������� ����� ������� - ����� �����
// ��� ������ ������������ ����
int _fastcall mlGetListFrameNumber(MAPLISTDATA * data);

// ������� ���� ������� � �������� ������
int _fastcall mlCreateDataFile(MAPLISTDATA * data);

// ������� ���� ������� � �������� ������
int _fastcall mlCreateDrawFile(MAPLISTDATA * data);

// ������� ���� ��������� � �������� ������
int _fastcall mlCreateSemnFile(MAPLISTDATA * data);


// ������� ��������� �����
int _fastcall mlOpenBackFiles(MAPLISTDATA * data);

// ������� ��������� �����
void _fastcall mlCloseBackFiles(MAPLISTDATA * data);

// ������������ ����� �������
// ���������� ����� ����������������� ����� �������
int _fastcall mlRestoreBackObject(MAPLISTDATA * data, int number,
                                  void * objinfo);                    

//  ���������������� ������� ����������������� ����� �������
//  ��� ������ ���������� ����              
int _fastcall mlReadObjectCopyByNumber(MAPLISTDATA * data,
                                       int number, void * info);

//  ������� ����������������� ����� �������
//  ��� ������ ���������� ����              
int _fastcall mlDeleteObjectCopyToNumber(MAPLISTDATA * data,
                                         int number, void * objinfo); 


#endif

