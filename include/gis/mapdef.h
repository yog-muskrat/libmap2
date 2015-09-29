
#if !defined(MAPDEF_H)
#define MAPDEF_H

#ifndef MAPRSC_H
  #include "maprsc.h"    // ������������� ������ �����
#endif

#ifndef MAPREGIS_H
  #include "mapregis.h"  // �������� ����������� ����� (��)
#endif

#ifndef MAPLST_H
  #include "maplst.h"    // ���� ������ ����� (���� ��)
#endif

#ifndef MAPTRANS_H
  #include "maptrans.h"
#endif

#ifndef MAPERROR_H
  #include "maperror.h"  // ��������� ������ ����������
#endif

#ifndef MAPTRACT_H
  #include "maptract.h"
#endif

#ifndef MAPGDX_H
  #include "mapgdx.h"
#endif

#ifndef MAPSELLS_H
  #include "mapsells.h"
#endif

#ifndef HIDESHOW
#ifndef MAPCOLOR_H
  #include "mapcolor.h"
#endif
#endif

#ifndef MAPMETR_H
 #include "mapmetr.h"          
#endif

// �������������� ������ �� DOS � WINDOWS
char * _DLLCLASS Dos2Win(char * Text,int length);

// �������������� ������ �� WINDOWS � DOS
char * _DLLCLASS Win2Dos(char * Text,int length);

// �������������� ������ �� DOS � KOI8
char * _DLLCLASS Win2Koi8(char * Text,int length);

// �������������� ������ �� KOI8 � DOS
char * _DLLCLASS Koi82Win(char * Text,int length);

#define Degree8Dec (100000000L)   // 10 ** 8

// �������������� ��������� ������
#define LABEL_DSK 0x004B5344L  // DSK0
#define LABEL_CFG 0x00474643L  // CFG0
#define LABEL_MAK 0x004B414DL  // MAK0
#define LABEL_MSK 0x004B534DL  // MSK0

class TMapSelect;

// �������� �������� ���������
enum PRECISIONFLAG                                      
{
  PF_FLOAT = 0, PF_DOUBLE = 1, PF_METRE = 2
};

enum PRECISIONTYPE                                       
{
  PT_MAXIMUM = 1, PT_CENTIMETERS = 2, PT_MILLIMETERS = 3
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++   ����������� ��������� �����  +++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TMap : public TMapMetricMemory
{
 public :

 // ������� ������� ������,��������� � ���������
 TMap();

 public :

 // ������� �������
 ~TMap();


 /*********************************************************
 *                                                        *
 *     ������� ������� � ������ ������/�����              *
 *                                                        *
 *********************************************************/

 // �������� ����� �� ������� ������ ����� � ������
 // map - ����������� �����,
 // handle - ������������� ����,������� ����� ����������
 // � ���� �������� (IMM_LIST - 0x586)
 // ��� ������ ���������� ����
 int Append(TMap * map,HWND handle);

 //  �������� ����� �� ������� ������ ����� � ��������������� ���������
 //  map - ����������� �����,
 //  handle - ������������� ����,������� ����� ����������
 //  � ���� ��������
 //  ��� ������ ���������� ����

 int AppendAndChange(TMap * map, HWND handle);      

 // ������� "������" ����� �����
 // ��� ������ ���������� ����
 int CreateData(const char * mapname,
                const	char * rscname,
                TMapRegister * mapreg);
 int CreateDataEx(const char * mapname,    
                const	char * rscname,
                MAPREGISTEREX * mapreg,
                LISTREGISTER * listreg);

 int Create(const char * mapname,
            const	char * rscname,
            TMapRegister * mapreg)
    { return CreateData(mapname,rscname,mapreg); }
 int CreateEx(const char * mapname,         
            const	char * rscname,
            MAPREGISTEREX * mapreg,
            LISTREGISTER * listreg)
    { return CreateDataEx(mapname,rscname,mapreg,listreg); }

 // ������� ��������� ����� ����� (���������������� �����)
 // ����� ������ ����������,
 // ������������� � ������� ���������� �������
 // ��� �������� ������ ����� ��������� �������������
 // ��� ������ ���������� ����
 int CreateTempMap(const	char * rscname);

 // ������� ��� ������� �����                      
 // ��� ������ ���������� ����
 int ClearList(int number)
    { return List.ClearList(this, number); }

 // ������� ����� �����
 void CloseData();
 void Close() { CloseData(); }

 // ��������� ������ ����� (�������������)
 // ��� ������ ���������� ����
 TMapRsc * GetResource()
    {
      if (Rsc.IsActive()) return &Rsc;
      return 0;
    }

 // ��������� ��� ����� ������� ������ �����
 const char * GetLogName() { return MapError.NameLOG(); }

 // ��������� ��� ����� �������� �����
 const char * GetMapName() { return Name_MAP; }

 // ��������� ��� ����� ��������������
 const char * GetRscName() { return Rsc.RscName; } 

 // ��������� ������ ��� ���� ����� �������� �����
 // name - ����� ��� ���������� �����
 // size - ������ ���������� ������� (������������� MAX_PATH)
 // ��� �������� ���������� ���������� ����� ������� ������
 // ��� ������ ���������� ����� ������ ������
 char * GetRscFileName(char * name, int size);

 const char * GetRscFileName() { return Rsc.GetRscName(); }  

 // ��������� ��� ������������� ����� �� ����� �����   
 // name    - ��� ����� �������� ����� (MAP,SIT)
 // rscname - ��� ����� RSC
 // size    - ������ ������ ��� ���������� ����� RSC
 // ��� ������ ���������� ����

 intptr_t GetRscNameByName(const char * name, char * rscname, int size);

 // ������� ����� �����
 // ��� ������ ���������� ����
 int OpenData(const char * map,int mode  = 0);
 int Open(const char * map,int mode  = 0)
    { return OpenData(map,mode); }

 // ��������� ����� ������ ������ (ver. 4.5)
 // ������� ����� �����
 // ��� ������ ���������� ����
 int LoadOldVersionData(const char * map);

 // �������� ��������� ����������
 // flag - ������� ������ ��������� ����������:
 // LOG_ANYACTION(0) - ��� �������, LOG_MYACTION(1) - ������������ ���������
 // ���� ���������� (���������� ���������� ������ �������������)
 // ���� ����� ���������� ����������� ���������� �����
 // ��� ������ ���� - ���������� ����
 // ��� ������ ���������� ����,
 // ����� - ���������� ��������������� ��������
 int AbolitionLastAction(int flag = LOG_MYACTION);

 // ������� ����������
 // type - ��� ���������� (�� 0x4000 �� 0�0FFFF - �� ���������)
 // ��� ������ ���������� ����
 int CreateAction(int type);

 // ������� ������ ����������
 void CommitAction(int longaction = 0);

 // ������������� ���������������� ����� � �������� ����� ���������
 // ��� ������ ���������� ����
 int TransformByMap(TMap * map);

 // ��������� ���������� ������ ��������� �����
 // �� ����� ����� - �������� ����� (MAP,SIT)
 // ��������� MAPREGISTEREX � LISTREGISTER ������� � mapcreat.h
 // sheetnumber - ����� ����� ����� ���
 // �������� ������������� ���������� ������
 // ��� ������ ���������� ����

 int GetMapInfoByName(const char * name,
                      int sheetnumber,
                      TMapRegister * mapregister);

 // ���������� ����� � ��������� ��������

 void SetParent(HSITE hsite, TMapMetricMemory * memory)
 {
   hSite        = hsite;
   ParentMemory = memory;
 }

 // �������� ������ ��� �������� ���������

 int AllocateBorderMemory();

 /*********************************************************
 *                                                        *
 *     ������ ������ �� ��'���� �������� �����           *
 *                                                        *
 **********************************************************
 *                                                        *
 *         ����� � ������� ���������� � ������� !!!       *
 *                                                        *
 *********************************************************/

public :

 // ��������� ����� ������ �������� ����� �� ��������
 // ��� ������ ������������ ����
 OBJECTDATA * GetData(long offset) {return(GetDataAddr(offset));}
 OBJECTDATA * GetDataAddr(long offset)
      { return (List.DataAddr(offset)); }

 // ��������� ����� ������ �������� ����� �� �������� �������
 // ��� ������ ������������ ����
 OBJECTDATA * GetObjectMetric(TObjectDesc desc) { return(GetDataAddr(desc));}
 OBJECTDATA * GetData(TObjectDesc desc) {return(GetDataAddr(desc));}
 OBJECTDATA * GetDataAddr(TObjectDesc desc)
      {
       if ((desc != 0) && (desc.Metric() != 0))
         return List.DataAddr(desc.Metric());
       else
         return 0;
      }

#ifndef TINYDATA
 // ��������� ����� ������������ �������� �� ��������
 // ��� ������ ������������ ����
 IMGDRAW * GetDraw(long offset) {return(GetDrawAddr(offset));}
 IMGDRAW * GetDrawAddr(long offset)
      { return (List.DrawAddr(offset)); }

 // ��������� ����� ������������ �������� �� �������� �������
 // ��� ������ ������������ ����
 IMGDRAW * GetObjectGraphic(TObjectDesc desc) {return(GetDrawAddr(desc));}
 IMGDRAW * GetDraw(TObjectDesc desc) {return(GetDrawAddr(desc));}
 IMGDRAW * GetDrawAddr(TObjectDesc desc)
      {
       if ((desc != 0) && (desc.Graphic() != 0))
         return List.DrawAddr(desc.Graphic());
       else
         return 0;
      }
#endif

 // ��������� ������ ����� �������� ����� �����
 // ���� ����� ������� - ������� ������ ��������� �����
 // ���� ����� ���, �� ������������ 0
 TObjectHead * GetFrameDesc();

/*
 // ��������� ����� �������� ������� � ������� �����
 // ��� ������ ������������ ����
 int GetCurrentObjectNumber() { return GetCurrObjectNumber(); }
 int GetCurrObjectNumber()
      { return (List.Object); }
*/

 // ��������� ������ (���������) ������ �������� �����
 // ������� � ����� ���������� ����������� ������
 // ��� ������ ������������ ����
 TObjectHead * GetFirstObject()
      { return List.FirstHead(); }
 int GetFirstObjectNumber()
      { return List.FirstNumber(); }

 // ��������� ��������� (���������) ������ �������� �����
 // ������� � ����� ���������� ����������� ������
 // ��� ������ ������������ ����
 TObjectHead * GetLastObject()
      { return List.LastHead(); }
 int GetLastObjectNumber()
      { return List.LastNumber(); }

 // ��������� ������ �������� ����� �� ������
 // ������� � ����� ���������� ������ "Number"
 // ��� ������ ������������ ����
 TObjectHead * GetObject(int number)
      { return (List.ObjectDesc(number)); }

 // ��������� ���������� �������� � ������� �����
 // ��� ������ ������������ ����
 int GetObjectCount()
      { return (List.Count()); }

 // ��������� ����� ��������� ������� �� ��������
 // ��� ������ ������������ ����
 SEMANTIC * GetObjectSemantic(TObjectDesc desc) {return (GetSemnAddr(desc));}
 SEMANTIC * GetObjectSemantic(long offset) {return(GetSemnAddr(offset));}
 SEMANTIC * GetSemn(long offset) {return(GetSemnAddr(offset));}
 SEMANTIC * GetSemnAddr(long offset)
      { return (List.SemnAddr(offset)); }

 // ��������� ����� ��������� ������� �� �������� �������
 // ��� ������ ������������ ����
 SEMANTIC * GetSemn(TObjectDesc desc) {return(GetSemnAddr(desc));}
#ifndef TINYDATA
 SEMANTIC * GetSemnAddr(TObjectDesc desc)
      {
       if ((desc != 0) && (desc.Semantic() != 0))
         return List.SemnAddr(desc.Semantic());
       else
         return 0;
      }
#else
 SEMANTIC * GetSemnAddr(TObjectDesc desc);
#endif

 /*********************************************************
 *                                                        *
 *     ������ ������������� �������� ����� / ������       *
 *                                                        *
 *********************************************************/

 // ��������� ��������� ����� � "����"
 // ���������� ���� ������ � ���������
 // ���� ���� �������� - ������������ TRUE
 int CheckFrame(int list,DFRAME * frame);

 // ��������� ����� �������� �����
 // ��� ������ ������������ ����
 // ����� � ������� ���������� � ������� !!!
 int GetCurrentListNumber() { return GetCurrListNumber(); }
 int GetCurrListNumber()
      { return (List.List); }

 // ��������� ���������� ������ � ������
 // ��� ������ ������������ ����
 int GetListCount()
      { return (Count()); }

 // ��������� ��� (������������) ����� �� ������
 // �� ��������� ������������ ��� �������� �����
 // ��� ������ ������������ ����
 const char * GetListName(int list)
      { return (ListName(list)); }

 const char * GetListName()
      { return (ListName(List.List)); }

 // ��������� ����� ����� �� ������������                       
 // ��� ������ ������������ ����
 int _fastcall SeekListByName(const char * name);

 // ����� ������� �� ����������� ������ � �������� ����� �����
 // ��� ������ ������������ ����                                
 int _fastcall SeekObjectInList(int list, long key, int flag = 0);

 // ��������� ����� �������� � �������� �����
 // ��� ������ ������������ ����
 int GetObjectCount(int list);

 // ������ ������������ ����� ����� ���������� ������ �������� �����.
 // ���������� ��� ����������� ����� ����������� ��������
 // ���� ������ �� ������������ ��������, �� ���������� 0, ����� 1
 int GetAccordingProjection();

 /*********************************************************
 *                                                        *
 *     �������������� ��������� � ������ �����            *
 *                                                        *
 *********************************************************/

 // ������������� �� ������� ������ � ������������� �������
 // �� ������� � ���������
 double Dis2DMetX(long   disX)
     { return ((MapX + MetInDis * (double)disX)*10.0); }

 double Dis2DMetY(long   disY)
     { return ((MapY + MetInDis * (double)disY)*10.0); }

 // �� ������� � �����
 long   Dis2MetX (long   disX)
     { return (long)(MapX + MetInDis * (double)disX + 0.5); }

 long   Dis2MetY (long   disY)
     { return (long)(MapY + MetInDis * (double)disY + 0.5); }

 // �� ������� � �����
 double Dis2MetX (double disX)
     { return (MapX + MetInDis * disX); }

 double Dis2MetY (double disY)
     { return (MapY + MetInDis * disY); }

 // ������������� �� ������������� ������� � ������� ������
 // �� ���������� � ��������
 long   DMet2DisX(double dMetX)
     { return (long)((dMetX/10.0 - MapX)/MetInDis + 0.5); }

 long   DMet2DisY(double dMetY)
     { return (long)((dMetY/10.0 - MapY)/MetInDis + 0.5); }

 // �� ������ � ��������
 long   Met2DisX (long   metX)
     { return (long)(((double)metX - MapX)/MetInDis + 0.5); }

 long   Met2DisY (long   metY)
     { return (long)(((double)metY - MapY)/MetInDis + 0.5); }

 // �� ������ � ��������
 double Met2DisX (double metX)
     { return ((metX - MapX)/MetInDis); }

 double Met2DisY (double metY)
     { return ((metY - MapY)/MetInDis); }

 // �������������� �������� ������������� �� ������� � �����
 double Dis2MetLine (double dis)
     { return MetInDis * dis; }

 // �������������� �������� ������������� �� ������ � ��������

 double Met2DisLine (double met)
     { return met/MetInDis; }

 // �������������� ��������� ������������� �� ������� � �����
 double Dis2MetSquare (double dis)
     { return MetInDis * MetInDis * dis; }


 /***************************************************************
 *                                                              *
 *      ������ / ��������� ������� � ����� ��������             *
 *                                                              *
 ***************************************************************/

 // ������ � ��������� ������ �������
 int AccessMode(int mode)
    {
       FileAccess = (mode & (GENERIC_READ|GENERIC_WRITE));
       if (FileAccess == 0)
         FileAccess = GENERIC_READ|GENERIC_WRITE;
       return FileAccess;
    }

 int AccessMode()
     { return FileAccess; }


 // ������ � ��������� ����� ������ � ������
 int Count();

 // ��������� ��� ������ ��������� ��������
 int Error() { return MapError.LastError; }

 // �������� ����������� ������
 int IsActive()
    { return ((File_MAP != 0) && (GetListCount() != 0)); }

 // ��������� - ��������������� �� ���������� ������ ?
 int IsDirty() { return Isdirty; }

 // �����������/��������� ����� ����������� ������� ������������� ���������
 int IsGeo() { return GeoAvailableFlag;}
 int IsGeo(int set) { return GeoAvailableFlag = set;}

 // ��������� - ����� ������� ?
 // ���� ����� ������� ���������� ����
 int IsOpen()
    { return (File() != 0); }

 // ������� �������� ��������� � ������� �������� � ��� ����� - SIT
 // (0 - �������� ������� - ��������)
 int IsRealPlace();

 // ������� �������� ��������� � ������� �������� (�����) ��� ����� �����
 int IsRealMetric()                                      
 {
   return ((PspId.Data.FlagRealPlace != 0) || (PspId.PrecisionFlag == PF_METRE));
 }

 // ������ - ����� �� ������������� ������� ?
 int IsWrite()                                      
 { return (IsActive() && (AccessMode() & GENERIC_WRITE) && Edit); }

 // ���������� ������ � ����� ��������
 // �� ��������� (� �����������.�������)
 double MetersInDis() { return MetInDis; }

 // ������ ���� ������� � �������� (��� ����� �����)
 char * PathMAP() { return Path_MAP; }

 // ������ ���� ������� � ������� � ��������� ������
 char * PathLOG() { return Path_LOG; }

 // ������ �������������� ����� �������� (��.::CreateFile(...) )
 // ���� ���� �� ������, ������������� ����� 0
 HANDLE File() { return (File_MAP); }

 // ��������� ����������� ������ � ������ � �� �����
 // ��� �������������� ���������� ����
 int CheckMode();

 // ���������� ����� ������� ���������� � ��������������
 // �����
 int SetChangeCall(CHANGECALL call, long int parm);

 // ������ � ��������� ������ �������
 int ShareMode(int mode)  { return FileShare = mode;   }

 int ShareMode() { return FileShare; }

 // �������� �������������� ������ � �������� ������
 // ���������� ����� ���������� ��������� ������
 int UpdateMode();

 // ������ ������ ��������� ������
 // (0 - ����������, 1 - ��������)
 int WorkMode() { return ( Mode_Work ); }

 // �������� ��������� � ������
 // message - ����� ������ ���������
 // type    - ��� ��������� (��. MESSAGETYPE)
 // ��� ������ ���������� ����
 int WriteToLog(const char * message,int type);

 /***************************************************************
 *                                                              *
 *      ��������� ������ �����                                  *
 *                                                              *
 ***************************************************************/

public :

 // �������� ������ ������ � ����������� � �� ���������� �� �����
 // ��� ������ ���������� ����
 int AdjustData();

 // �������� ���� � �����
 // srcmap - �����,���������� ����������� ����
 // list - ����������� ����
 // ����������� ������ ������ ���� ��� �� ��������,
 // ������� ��������� � ��������, ��� � � ������ �����
 // ��� ������ ���������� ����
 // ��� ��������� ������� ����� ����� ��������� �������� !
 int AppendList(TMap * srcmap,int list,int save);

 // �������� ���� � ����� � ��������������� ��������� ��������
 // srcmap - �����,���������� ����������� ����
 // list - ����������� ����
 // prefix - ��������� � ������ ����� �����
 // ��� ������ ���������� ����

 int AppendListAndChange(TMap * srcmap, int list, char* prefix, int save,
                         HWND handle = 0);

 // ��������� ����������� ���������� ������ � �����
 // ��� ������ ���������� ����
 int Commit() { return Save(TRUE); }

 // ������� � ������ ����� ���� (���� ���������� ���������)
 // save    - ������� ������������ ���������� �����
 // mapreg  - �������� ������������ �����
 // ��� ������ ���������� ����
 // ��� ��������� ������� ����� ����� ��������� �������� !
 int CreateList(LISTREGISTER * mapreg, int save = 1);        

 // ������� �� ������ ����
 // save    - ������� ������������ ���������� �����
 // ��� ������ ���������� ����
 // ��� ��������� ������� ����� ����� ��������� �������� !
 int DeleteList(int list,int save = FALSE);

 // ������� �������� ���� c ������� Number
 // ������� ���������� ���� "number"
 // ��� ������ ���������� ����
 int OpenList(int number);

 // ������� �������� ����, ���� �� �� ������
 // ������� ���������� ���� "number"
 // ��� ������ ���������� ����
 int IsOpenList(int number);

 // �������� ��� ���� ������������ ������� ������
 // ��� ������ ���������� ����
 int AllocateNotLimit(int number);

 // ��������� ���������� �������� �� ������� MapRegister
 // ��� ������ ���������� ����
 int MapRegister(MAPREGISTEREX * mapreg);

 // ��������� MapRegister ��� ��������� �����
 int ListToRegister(TMapRegister * mapreg, int list);

 // ��������� ���������� MapRegister �� �������� �����
 // ��� ������ ���������� ����
 int ListToRegister(MAPREGISTEREX * mapreg,
                    LISTREGISTER * listreg, int list);

 // ������������ ��������� ���������� ������
 // �� ������ ���������� ���������� � �����
 // ��� ������ ���������� ����
 int Revert();

 // ��������� ��������� � ��������
 // ��� ������ ���������� ����
 int Save(int force = FALSE);

 // ��������� ������ ��������� ������
 // (0 - ����������, 1 - ��������)
 int WorkMode(int mode);

 // ������ ����
 void LockList() { List.LockList(); }

 // ���������� ����
 void UnLockList() { List.UnLockList(); }

 // ��������� ������� ������ � ������������� �������
 void SetNullPoint();

 // ���������� ����� � �������������
 // newname - ���� � ������ ����� �����
 // ��� ������ ���������� ���������� ����
 int CopyMap(const char * newname);

 // �������� ������ �����
 // name - ��� ������
 // ��� ������ ���������� ����
 int DeleteMap();

protected :

 // ������� ������� ������,��������� � ���������
 // ��� ������ ���������� ����
 int OpenMap(const char * map, int mode = 0);

 // ������� ����� �������
 // ��� ������ ���������� ����, ��� ������ � Error()
 int CreateMap(const char * map,TMapRegister * mapreg,TMapRsc * maprsc);

 /***************************************************************
 *                                                              *
 *      ������� / ��������� ������ � �������� �����             *
 *                                                              *
 ***************************************************************/

public :

 // ������ � ��������� ������� ��������� �������� �����
 // ���������� � �������� !
 double AxisMeridian(double meridian);
 double AxisMeridian();

 // ������/��������� �������� ������� ������ � ��������
 int DataProjection();
 int DataProjection(int datpro);

 // ������ � ��������� ���� ����������
 int EllipsoideKind(int kind);
 int EllipsoideKind();


 // ������ � ��������� ������ ������� ���������
 // ���������� � �������� !
 double FirstMainParallel(double parallel);
 double FirstMainParallel();

 // ������ ������� ����� ��������
 // ���������� � �������� !
 double MainPointParallel(double parallel);
 double MainPointParallel();

 // ������ ������ ��������                 
 // ���������� � �������� !
 double PoleLatitude(double parallel);
 double PoleLatitude();

 // ������� ������ ��������
 // ���������� � �������� !
 double PoleLongitude(double parallel);
 double PoleLongitude();

 // ������ � ��������� �������� ��������� ���������
 int MaterialProjection();
 int MaterialProjection(int value)
 {
   return (PspId.Data.MaterialProjection = value);
 }

 // ������ � ��������� ������ ������� ���������
 // ���������� � �������� !
 double SecondMainParallel(double parallel);
 double SecondMainParallel();

 // ������ � ��������� ����� ��������� ��������
 int ProjectionFlag(int flag);
 int ProjectionFlag ();

 // ������ ������� ������� ����������
 // ��� ������ ������������ ����
 double BigAxis();

 // ������ ��������������� ����������
 // ��� ������ ������������ ����
 double Eccentricity();

 // ���������� �������� � ���������� ������ �� ��������
 // ��������� ���������
 void SetDataProjection();

 // ������� ���� ����������
 int GetEllipsoid()
 {
   return Translate.GetEllipsoid();
 }

 // ��������� ����� ���� ��� ��������������� ����
 int GetNumberZone()
 {
   return Translate.GetNumberZone();
 }

 int ZoneNumber() { return GetNumberZone(); }

 // ����������� ������������� ��������� B � L �� ������������� X � Y
 // ������� ������:
 //        x,y  -  ������������� ���������� ����� � ������
 // �������� ������:
 //        B,L  -  ������ � ������� ����� � ��������
 void XY2BL(double x, double y, double * B, double * L)
 {
   Translate.XY2BL(x, y, B, L);
 }

 // ����������� ������������� ��������� X � Y �� ������������� B � L
 // ������� ������:
 //        B,L  -  ������������� ���������� ����� � ��������
 // �������� ������:
 //        x,y  -  ������������� ���������� ����� � ������
 void BL2XY(double B, double L, double *x, double *y)
 {
   Translate.BL2XY(B, L, x, y);
 }

 // ************************************************************
 //                                                            *
 //       ������ � ��������� ��������� ������ (���������)      *
 //                                                            *
 // ************************************************************

 double X1(double x);
 double X1();

 double Y1(double y);
 double Y1();

 double X2(double x);
 double X2();

 double Y2(double y);
 double Y2();

 /***************************************************************
 *                                                              *
 *      ������ ������������� ��������� ��������� �����          *
 *          ������������� ���������� � ������                   *
 *                                                              *
 ***************************************************************/

 double XL1m(int list)
 {
   if (LstId == 0) return 0;
   return ((LstId+list-1)->XMin);
 }

 double YL1m(int list)
 {
   if (LstId == 0) return 0;
   return ((LstId+list-1)->YMin);
 }

 double XL2m(int list)
 {
   if (LstId == 0) return 0;
   return ((LstId+list-1)->XMax);
 }

 double YL2m(int list)
 {
   if (LstId == 0) return 0;
   return ((LstId+list-1)->YMax);
 }

 // ������ ��������� ����� � ��������� !!!
 // ��� ������ ���������� ����
 // list - ����� �����,  1 <= list <= Count()
 DFRAME * ListFrame(int list);

 // ������ ������� ����� ����������� ����� � ������ � ���������
 // ��� ������ ���������� ����
 DOUBLEPOINT * ViewPosition(int list);
 DOUBLEPOINT * ViewPosition()
   { return ViewPosition(List.Number()); }

 /***************************************************************
 *                                                              *
 *      ������� / ��������� ������ � ������ �����               *
 *                                                              *
 ***************************************************************/

 // ������ - ������� ��������� ������ ���������� ?
 // ���� �� - ����� ����� ������������ � �������
 // �� �������� � �������� (������� �������),
 // ����� - � ������������ �������
 int IsOrder();

 // ��������� ������� ��������� ������
 int IsOrder(int order);

 // ������ � ��������� ����� �����
 // ������� - ��� �����, ��� ������ - 0
 const char * SheetName(int list);
 const char * SheetName(const char * name,int list);

 // ������ � ��������� ������������ �����
 // ��� ������ ������������ ����
 const char * Nomenclature(int list);
 const char * Nomenclature(const char * name,int list);

 const char * ListName(int list = 1) { return Nomenclature(list); }
 const char * ListName(const char * name,int list)
  { return Nomenclature(name,list); }

 // ��������� �������� ��������� ����� � ������
 // ������������ ��������� �� ���������� �����
 // � ������ � ���������
 // �� ��������� ������� ������� ����
 // ��� ������ ������������ ����
 DFRAME * GetListFrame(int list)
  {  return ListFrame(list); }

 // ��������� ����� ������� - ����� �����
 // �� ��������� ������� ������� ����
 // ��� ������ ������������ ����
 int GetListFrameNumber(int list);

 int GetListFrameNumber()
  {
    return GetListFrameNumber(List.Number());
  }

 /***************************************************************
 *                                                              *
 *  ������� / ��������� ������ � ������� ��������� � ��������   *
 *                                                              *
 ***************************************************************/

public :

 // ������ � ��������� ������� ���������
 int CoordinateSystem();
 int CoordinateSystem(int value)
 {
   return (PspId.Data.CoordinateSystem = value);
 }

 // ������ � ��������� ������������ ����������
 unsigned long int DeviceCapability();

 // ������ � ��������� ������� �����
 int HeightSystem();

 // ������ � ��������� ������� ��������� �� ������
 int HeightUnit();

 // ������ � ��������� ������� ��������� � �����
 int PlaneUnit();

 // ������ � ��������� �������� �����
 long int Scale(long int scale);
 long int Scale();

 /***************************************************************
 *                                                              *
 *      ������� / ��������� ���������� ������                   *
 *                                                              *
 ***************************************************************/

 public :

 // ���������� ��������� ������ � ����������
 void CreateMapBorder(void);

 // ��������� - ��������� ������� ������� ?
 int IsGroup();

 // ��������� �������� ������� ��������� ��������
 int IsGroup(int group);

 // ������ � ��������� ����� ������
 const char * Name(const char * name);
 const char * Name();

 // ������ � ��������� ����� ����� RSC � ������� �����
 const char * NameRSC();
 const char * NameRSC(const char * name);

 // ������ � ��������� ����� ����� GDX
 const char * NameGDX();
 const char * NameGDX(const char * name);

 // ������ � ��������� ����� ����� HDR
 // number - ����� �����,
 // ��� �������� ���������� ��� �����
 // ��� ������ ������������ ����
 const char * NameHDR(int number);
 const char * NameHDR(int number,const char * name);

 // ������ � ��������� ����� ����� DAT
 // number - ����� �����,
 // ��� �������� ���������� ��� �����
 // ��� ������ ������������ ����
 const char * NameDAT(int number);
 const char * NameDAT(int number,const char * name);

 // ������ � ��������� ����� ����� GRA (����������� �������� �������)
 // number - ����� �����,
 // ��� �������� ���������� ��� �����
 // ��� ������ ������������ ����
 const char * NameDRW(int number);
 const char * NameDRW(int number,const char * name);

 // ������ � ��������� ����� ����� SEM
 // number - ����� �����,
 // ��� �������� ���������� ��� �����
 // ��� ������ ������������ ����
 const char * NameSEM(int number);
 const char * NameSEM(int number,const char * name);

 // ������ � ��������� ������ ������� ���������
 int ScaleTableNumber(int number);
 int ScaleTableNumber();

 // ������ � ��������� ���� �����
 int MapType(int type);
 int MapType();

 // ������ � ��������� ���� �����
 int FrameKind(int kind);
 int FrameKind();

 // ��������� ��������� ����� number � ������
 int  _fastcall UpdateListBorder(int number = 1, int save = 1);
 void _fastcall UpdateListBorder(int number,DOUBLEPOINT * pointmin,
                                            DOUBLEPOINT * pointmax);

 // ����������� ������������� ���������� �����
 void _fastcall UpdateListGeoBorder(int number);

 // ���������/���������� ������� �������� �������� ���������
 // 0 - �������, 1 - ����������
 int GetPrecision();
 int SetPrecision(int precision);

 // ���������/���������� ����� ������ ����� ������� ��� �������� ���������
 // 1 - ������������, 2 - ����������, 3 - ����������
 int GetPrecisionType();                                         
 int SetPrecisionType(int precision);

  // ���������/���������� �������� ���������������� ������� �����
  // ��� ������ �� ���������� (0 - 100)
  unsigned int _fastcall GetCurrentTranslucency() const
  {
    return MapColors.Transparent;
  }
  
  unsigned int _fastcall SetCurrentTranslucency(unsigned int translucency)
  {
    if ( translucency > 100 ) translucency = 100;
    return MapColors.Transparent = translucency;
  }


 protected:

 // �������� ������ ��� ���������, ����������� ����� �����
 // ��������� �� ������� �� �����-��������
 // ��� ������ ���������� ����
 int AllocateLists(int newcount,int oldcount);

 // �������� ������ ��� ���������, ����������� ���� �����
 // ����� ����� �������� � ������ ����� Count()+1
 // ��� ������ ���������� ����
 int AllocateOneList();

 // ���������� ��������� ����� number � ����������
 void CreateListBorder(int number);

 // ���������� ��������� ������ � ���������
 void CalculateBorder(int count);

 /***************************************************************
 *                                                              *
 *               ���������� ������ ��������� �����              *
 *                                                              *
 ***************************************************************/

public :

 int    FileAccess;         // ����� ������� � �������� (W/R)
 int    FileShare;          // ��������������������� ������
 HANDLE File_MAP;           // ������������� �����

 int IsRelink;              // ������� ���������� �������������

 double MetInDis;           // ���������� ������ � ����� ��������
                            // �� ��������� (� �����������.�������)
 double MapX;               // ������ ��������� ������ � ������
 double MapY;               // � ������������� ������� �� ���������

 long   MaxX;               // �������� ������ � ���������
 long   MaxY;               // � ������� ������
 long   MinX;
 long   MinY;

 char Name_MAP[MAX_PATH];   // ��� ����� ��������
 char Short_MAP[MAX_PATH];  // ��� ����� ��������
 char Path_MAP[MAX_PATH];   // ���� ������� � ��������
 char Path_LOG[MAX_PATH];   // ���� ������� � �������
                            // � ��������� ������

 int  Isdirty;              // ������� �������������� ��������
 int  GeoAvailableFlag;     // ���� ����������� ������� ������������� ���������

 PASSPORTHEAD   PspId;      // ������������� ���������� ������ ������
 SHEETDESC *    LstId;      // ������������� �������� ������� �����
 int            LstIdSize;  // ������ �������� ������    

 int IsTempMap;             // ������� ��������� �����

 int Mode_Work;             // ����� ������ � ������
                            // 0 - ������� ��������
                            // != 0 - ���������� ������

 HSITE hSite;               // ������������� �������� ������ ����

 CHANGECALL  ChangeCall;    // ����� ������� ���������� � ��������������
 long int    ChangeParm;    // �������� ������� ����������

 int         View;          // ������� ��������� (0/1)
 int         Edit;          // ������� ��������������� (0/1)
 int         Inquiry;       // ������� ������ ��'����� �� ����� (0/1)

 long int    TopScale;      // ����������� �������� ������� ������� ���������  
 long int    BottomScale;   // ����������� �������� ������ ������� ���������  

 TTransaction ActionLog;    // ������ ����������

 int ActionLogMode;         // ����� ������� � ������� (0 - ������ ������)

 TMapRsc     Rsc;           // �������� ���������� �� ����� �����

#ifndef HIDESHOW
 TMapColors  MapColors;     // �������� ������� �����
#endif

 TSelectList SelectList;    // ������ ��������������� ������� ������

 TMapError   MapError;      // �������� ������

 TMapSelect * SeekSelect;   // ������� ������/��������� �� �����
 TMapSelect * ViewSelect;   // ������� ����������� �� �����

 TMapList    List;          // �������� ��������� ����� ������

 TTranslate  Translate;     // ��������� ��������� ���������

 long int    AdjustMode;    // ��������� ���������� ���������� �����

 long int    RangeScaleBot; // ������ �������� �������� �����������
 long int    RangeScaleTop; // ������ �������� �������� �����������  

#ifndef HIDEGDX   
 TMapGroups  Groups;        // �������� ����� ��������� �� �����
#endif

 TMapMetricMemory * ParentMemory;  
};

typedef TMap TSite;

// --------------------------------------------------------------
//  ������� �������� ���� c ������� Number
//  ������� ���������� ���� "number"
//  ��� ������ ���������� ����
// --------------------------------------------------------------
inline int TMap::OpenList(int number)
{
  // ����� ����� ���������� ?
  if (number < 1) return 0;

  // ������� ��������� ����
  return List.Open(this,number);
}

// --------------------------------------------------------------
//  ������� �������� ����, ���� �� �� ������
//  ������� ���������� ���� "number"
//  ��� ������ ���������� ����
// --------------------------------------------------------------
inline int TMap::IsOpenList(int number)
{
  // ����� ����� ���������� ?
  if (number < 1) return 0;

  // ���� ��� ������ ?
  if (List.Number() != number)
    {
      return(OpenList(number));
    }
  else
    {
      return 1;
    }
}

// --------------------------------------------------------------
// �������� ��� ���� ������������ ������� ������
// ��� ������ ���������� ����
// --------------------------------------------------------------
inline int TMap::AllocateNotLimit(int number)
{
  return List.AllocateNotLimit(this, number);
}

typedef TMap TMAPDATA;

#ifdef BUILD_DLL
// ������� ����� �����
void _fastcall tmCloseData(TMap * data);

// ������� ����� �����
// ��� ������ ���������� ����
int _fastcall tmOpenData(TMap * data, const char * map, int mode);

// ������� "������" ����� �����
// ��� ������ ���������� ����
int _fastcall tmCreateData(TMap * data, const char * mapname,
                           const	char * rscname,
                           MAPREGISTEREX * mapreg, LISTREGISTER * listreg);

// ������� ������� ������,��������� � ���������
// ��� ������ ���������� ����
int _fastcall tmOpenMap(TMap * data, const char * name, int mode);

// ������� ������� ������ � ���������
// ��� ������ ���������� ����
int _fastcall tmCreateMap(TMap * data, const char * mapname,
                          MAPREGISTEREX * mapreg, LISTREGISTER * listreg,
                          TMapRsc * maprsc);

// ������� ��������� ����� ����� (���������������� �����)
// ����� ������ ����������,
// ������������� � ������� ���������� �������
// ��� �������� ������ ����� ��������� �������������
// ��� ������ ���������� ����
int _fastcall tmCreateTempMap(TMap * data, const	char * rscname);

// ������� � ������ ����� ���� (���� ���������� ���������)
// ��� ������ ���������� ����
// ��� ��������� ������� ����� ����� ��������� �������� !
int _fastcall tmCreateList(TMap * data, LISTREGISTER * listreg, int save);

// ������� �� ������ ����
// ��� ������ ���������� ����
// ��� ��������� ������� ����� ����� ��������� �������� !
int _fastcall tmDeleteList(TMap * data, int list, int save);

// �������� ������ ��� ���������, ����������� ����� �����
// ��������� �� ������� �� �����-��������
// ��� ������ ���������� ����
int _fastcall tmAllocateLists(TMap * data, int newcount,int oldcount);

// �������� ������ ��� ���������, ����������� ���� �����
// ����� ����� �������� � ������ ����� Count()+1
// ��� ������ ���������� ����
int _fastcall tmAllocateOneList(TMap * data);

// ���������� ��������� ������ � ���������
void _fastcall tmCalculateBorder(TMap * data, int count);

// ���������� ��������� ������
void _fastcall tmCreateMapBorder(TMap * data);

// ��������� ��������� ����� number � ������
int _fastcall tmUpdateListBorder(TMap * data, int list, int save);

// ��������� ��������� ����� number � ������
void _fastcall tmUpdateListBorderByValue(TMap * data, int number,
                                         DOUBLEPOINT * pointmin,
                                         DOUBLEPOINT * pointmax);

// ���������� �������� ����� �� ��������� ��������       
void _fastcall tmUpdateListBorderByObjects(TMap * data);

//  ����������� ������������� ���������� �����
void _fastcall tmUpdateListGeoBorder(TMap * data, int number);

//  ��������� ��������� ����� � ������
void _fastcall tmCreateListBorder(TMap * data, int number);

// �������� �������������� ������ � �������� ������
// ���������� ����� ���������� ��������� ������
int _fastcall tmUpdateMode(TMap * data);

// ��������� ������������ ������ � ������ � �� �����
// ��� �������������� ���������� ����
int _fastcall tmCheckMode(TMap * data);

// ��������� ������ ��������� ������
// (0 - ����������, 1 - ��������)
int _fastcall tmWorkMode(TMap * data, int mode);

// ������� �������� ����, ���� �� �� ������
// ������� ���������� ���� "number"
// ��� ������ ���������� ����
int _fastcall tmIsOpenList(TMap * data, int number);

// ������ - ����� �� ������������� ������� ?
int _fastcall tmIsWrite(TMap * data);

// ��������� ��������� � ��������
int _fastcall tmSave(TMap * data, int force);

// �������� ������ ������ � ����������� � �� ���������� �� �����
// ���� ��������� ������ ���������� - ���������� ������������� ��������
// ��� ������ ���������� ����
int _fastcall tmAdjustData(TMap * data);

// ��������� ����� ������� - ����� �����
// �� ��������� ������� ������� ����
// ��� ������ ������������ ����
int _fastcall tmGetListFrameNumber(TMap * data, int list);

// ��������� ������ ����� �������� ����� �����
// ���� ����� ���, �� ������������ 0
TObjectHead * _fastcall tmGetFrameDesc(TMap * data);

// ��������� ����� �������� � �������� �����
int _fastcall tmGetObjectCount(TMap * data, int list);

// ��������� ������ � �������� ����� �����
TObjectHead * _fastcall tmGetObjectHead(TMap * data, int list, int object);

// ��������� ����� ������ ������
// ������� ����� �����
// ��� ������ ���������� ����
int _fastcall tmLoadOldVersionData(TMap * data, const char * map);

// ��������� - ������� ������ �� ��������?
int _fastcall tmDataProjection(TMap * data);

// ���������� �������� � ���������� ������ �� ��������
// ��������� ���������
void _fastcall tmSetDataProjection(TMap * data);

// ��������� ���������� �������� �� ������� MAPREGISTEREX
// ��� ������ ���������� ����
int _fastcall tmMapRegister(TMap * data, MAPREGISTEREX * mapreg);

// ��������� ���������� MapRegister �� �������� �����
// ��� ������ ���������� ����
int _fastcall tmListToRegister(TMap * data, MAPREGISTEREX * mapreg,
                               LISTREGISTER * listreg, int list);

// ������������ ��������� ���������� ������
// �� ������ ���������� ���������� � �����
// ��� ������ ���������� ����
int _fastcall tmRevert(TMap * data);

// ��������� ��������� ����� � "����"
// ���������� ���� ������ � ���������
int _fastcall tmCheckFrame(TMAPDATA * data, int list, DFRAME * frame);

// ������ ��������� ����� � ��������� !!!
// ��� ������ ���������� ����
// list - ����� �����,  1 <= list <= Count()
DFRAME * _fastcall tmListFrame(TMap * data, int list);

// ���������� ������ �������� �����
int _fastcall tmWritePasp(TMAPDATA * data, int offset,
                          char * address, int length);

// ������ ������� ����� ����������� ����� � ������
// ��� ������ ���������� ����
DOUBLEPOINT * _fastcall tmViewPosition(TMAPDATA * data, int list);

// ������������ �������� ������� �����
void _fastcall mcRestoreColors(TMAPDATA * data);

// ���������� ������� ������� �� ������
// (������� ��������������� � MapColors)
// ��� ������ ���������� ����
COLORREF * _fastcall mcGetPaletteByNumber(TMAPDATA * data, int number);

// ������ ������������ �����                     
const char * _fastcall tmGetListName(TMap * map, int list);

// ������ ����� ������
int _fastcall tmGetListCount(TMap * map);

// ����� ����� ����� �� ������������
int _fastcall tmGetListNumber(TMap * map, const char * name);

#endif  // BUILD_DLL

#endif

