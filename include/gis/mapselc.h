
#if !defined(MAPSELC_H)
#define MAPSELC_H

#ifndef MAPSAMP_H
  #include "mapsamp.h"
#endif

#ifndef MAPINFO_H           
  #include "mapinfo.h"
#endif


// ������� ������ ������� �� ���������
// ���������� ������� �� �������� �����

typedef struct KEYSELECT
{
  int  list;        // ����� ����� � ������
  KEY  minkey;      // ������ ������� ������
  KEY  maxkey;      // ������� ������� ������
}
  KEYSELECT;

typedef struct RECORDID  // ��������� ������ ��� ���������� �������
{                        // ������ �������� :
   int   Label;          // �����
   int   Length;         // �����
}
  RECORDID;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ��������� ������ ������ ����������� ����� ++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 enum TOTALSEEK                        
 {
    MSL_MAP = 1,      // ������� ������ � ������ �����
    MSL_VISIBLE = 2   // ������� ������ ����� ������� �� ����� ��������
 };

 enum DRAWOBJFLAG     // ������� ������ ����������� �������� :    
 {
    MSL_DRAW_ON   = 0,  // �������� �� ������ �������,
    MSL_DRAW_ONLY = 1,  // �������� ������ ����������� �������,
    MSL_DRAW_OFF  = 2,  // ��������� �� ������ ����������� �������
 };

// ������������������� ��������� ������ �������� �����
void _fastcall mslSelectAll(MAPSELECT * data);

// ���������� ����� � ������� ������ ��������
void _fastcall mslSetMap(MAPSELECT * data, TMap * map);

// ������� ����� �������� ������� ������ ��������
void _fastcall mslSetSelectBySelect(MAPSELECT * dest, MAPSELECT * src);

// ���������� ������� ������ ��������
// �� �������� �������� ����� (�����,�����������,����,���� ��������)
// ���� ������ �����(map), ��� �������� ���������� (Map)
int _fastcall mslSetSelectByMap(MAPSELECT * data, TMap * map);

//  ���������� ������� �������� �� ����� �������������
//  ����������� ���� ������� ������ ��������
//  view - ������� ������ �������� (��� ��� �� �����)
//  ��� ������ ���������� ����
int _fastcall mslGetMarkObjectCount(MAPSELECT * data, MAPSELECT * view);

//  ���������� ������� �������� �� ����� �������������
//  �������� ��������
//  ��� ������ ���������� ����
int _fastcall mslGetSelectObjectCount(MAPSELECT* data);

//  �������� ������� ��������� �������� ��� �������������� �����
void _fastcall mslUpdateSelectCountByObject(MAPSELECT* data, int number,
                                      TObjectHead * head, OBJECTDATA * objdata,
                                      SEMANTIC * semn, int operation);


// **************************************
//  ������� ������ �������� �����
// **************************************

// �������� ������������ �������� �������
// (����,�����������,��� �������,�����,���������,�������)
// (����,�����������,��� �������,�����)
// ���� ������ �� �������� �������� - ���������� ����
int _fastcall mslCheckObjectHead(MAPSELECT * data, TObjectHead* head, int number);
int _fastcall mslCheckObjectBySelect(MAPSELECT * data, TObjectHead* head, int number);
int _fastcall mslCheckMapObject(MAPSELECT * data, TObjectHead * head,
                                OBJECTDATA* objdata, SEMANTIC* semn, int number);
int _fastcall mslVerifyMapObject(MAPSELECT * data, TObjectHead * head,
       										  OBJECTDATA* objdata, SEMANTIC* semn, int number); 

int _fastcall mslCheckObjectByInfo(MAPSELECT * data,
                                   TObjectInfo * info);

// ���������� ����������� ����,����������� � ���� �������
void _fastcall mslObjectSetByObject(MAPSELECT * data,
                                    TObjectInfo * info);

// ��������� ������������ ������������� ������������� �������
// ���� ������ �� �������� �������� - ���������� ����
int _fastcall mslCheckSemantic(MAPSELECT * data, SEMANTIC * semn);



  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //  ������ ������� � �������� ��������� ��������� �������  +
  //  ���� ������� �� ��������� - ������������ ����          +
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//****************************************************
//  ������� ������ �� ������ �����
//****************************************************

// �������� ����
void _fastcall mslClearList(MAPSELECT * data, int number);

// �������� ��� �����
void _fastcall mslClearAllLists(MAPSELECT * data);

// �������� ����
void _fastcall mslSetList(MAPSELECT * data, int number);

// �������� ��� �����
void _fastcall mslSetAllLists(MAPSELECT * data);

// �������� ����
int _fastcall mslListCheck(MAPSELECT * data, int number);

// ���������� ���� ������ ������
int _fastcall mslSetListFlag(MAPSELECT * data, int flag);

//****************************************************
//  ������� ������ �� ������������ �������� �����
//****************************************************

// ��������/��������/�������� �����������
void _fastcall mslSetLocal(MAPSELECT * data, int number);

void _fastcall mslClearLocal(MAPSELECT * data, int number);

int _fastcall mslCheckLocal(MAPSELECT * data, int number);

// C������� ��� �����������
void _fastcall mslClearAllLocals(MAPSELECT * data);

// ������� ��� �����������
void _fastcall mslSetAllLocals(MAPSELECT * data);

// ���������� ���� ������ �� �����������
int _fastcall mslSetLocalFlag(MAPSELECT * data, int flag);

//**********************************************
//  ������� ������ �� ��������� �����
//**********************************************

// ��������/�������� �������
void _fastcall mslClearSegment(MAPSELECT * data, int number);

void _fastcall mslSetSegment(MAPSELECT * data, int number);

// ��������/�������� ��� ��������
void _fastcall mslSetAllSegments(MAPSELECT * data);

void _fastcall mslClearAllSegments(MAPSELECT * data);

// ���������, ���������� �� �������
// ��� ������ ���������� 2, ��� �������� �������� 1, ����� - 0
int _fastcall mslCheckSegment(MAPSELECT * data, int number);

// ���������� ���� ������ �� ���������
int _fastcall mslSetSegmentFlag(MAPSELECT * data, int flag);

//**********************************************
//  ������� ������ ��  ����� ��������
//**********************************************

// ��������/�������� ������
void _fastcall mslSetObject(MAPSELECT * data, int number);

void _fastcall mslClearObject(MAPSELECT * data, int number);

// ��������/�������� ��� �������
void _fastcall mslClearAllObjects(MAPSELECT * data);

void _fastcall mslSetAllObjects(MAPSELECT * data);

// ���������, ���������� �� ������ ������
// ��� ������ ���������� 2, ��� �������� �������� 1, ����� - 0
int _fastcall mslCheckObject(MAPSELECT * data, int number);

// ���������� ���� ������ �� ����� ��������
int _fastcall mslSetObjectFlag(MAPSELECT * data, int flag);

// ���������� ���� ������ ����������� ��������
int _fastcall mslSetDrawObjectFlag(MAPSELECT * data, int flag);

// ��������� ���� ������ ����������� ��������
int _fastcall mslGetDrawObjectFlag(MAPSELECT * data);

//****************************************************
//  ������� ������ �� ��������������� �������� �����
//****************************************************

// ��������/��������� min � max ������������� �������

long int _fastcall mslSetKeyMin(MAPSELECT * data, unsigned long int key);

long int _fastcall mslGetKeyMin(MAPSELECT * data);

long int _fastcall mslSetKeyMax(MAPSELECT * data, unsigned long int key);

long int _fastcall mslGetKeyMax(MAPSELECT * data);

// ���������, ���������� �� ������������� key
// ��� ������ ���������� 2, ��� �������� �������� 1, ����� - 0
int _fastcall mslKeyCheck(MAPSELECT * data, unsigned long int key);

// ���������� ���� ������ �� ��������������� ��������
int _fastcall mslSetKeyFlag(MAPSELECT * data, int flag);

//**********************************************
//  ������� ������ �� ��������������� ��������
//**********************************************

// �������� ��� ������� �� ������ �������������
void _fastcall mslClearAllSemantics(MAPSELECT * data);

// ��������/�������� �������������� ��������

// ���������� ���� ������ �� ���������������
int _fastcall mslSetSemanticFlag(MAPSELECT * data, int flag);

// �������� ��� ������� �� ������ �������������
void _fastcall mslClearAllSemantics(MAPSELECT * data);

// �������� ������� � ������
// ��� ������ ���������� ����, ����� - 1
int _fastcall mslSemanticAppend(MAPSELECT * data, int code, int semcode, char * value);

// ������� ������� �� ������
// number - ����� ������� � ������ (�� 1 �� SEMCOUNT)
// ��� ������ ���������� ����
int _fastcall mslSemanticDelete(MAPSELECT * data, int number);

// ��������� ����� �������� � ������ �������
int _fastcall mslSemanticCount(MAPSELECT * data);

// ��������� ��� �������
// number - ����� ������� � ������ (�� 1 �� SEMCOUNT)
// ��� ������ ���������� ����
int _fastcall mslSemanticCondition(MAPSELECT * data, int number);

// ��������� �������� �������������� �� ������ �������
// number - ����� ������� � ������ (�� 1 �� SEMCOUNT)
// ��� ������ ���������� ����, ����� - place
char * _fastcall mslSemanticValue(MAPSELECT * data,int number,char * place,int size);

// ��������� ��� ��������� �� ������ � ������
// number - ����� ������� � ������ (�� 1 �� SEMCOUNT)
// ��� ������ ���������� ����
int _fastcall mslSemanticCode(MAPSELECT * data, int number);

// ��������� ��� �������������� �� ������ � ������
// number - ����� ������� � ������ (�� 1 �� SEMCOUNT)
// ��� ������ ���������� ����� ������ ������
const char * _fastcall mslSemanticCodeName(MAPSELECT * data, int number);

// ���������� ��� ������������� �������
// CMOR ��� CMAND
// ��� ������ ���������� ����
int _fastcall mslSemanticLink(MAPSELECT * data, int code);

// ��������� ��� ������������� �������
// CMOR ��� CMAND
int _fastcall mslGetSemanticLink(MAPSELECT * data);

//****************************************************
//  ������� ������ �� ���������� ��������
//****************************************************

// ��������/�������� ����� �������� �� ����������
// ----------------------------------------------
int _fastcall mslSetMeasureFlag(MAPSELECT * data, int flag);

int _fastcall mslSetMeasureLink(MAPSELECT * data, int code);

int _fastcall mslMeasureClear(MAPSELECT * data);

int _fastcall mslMeasureAdd(MAPSELECT * data, MEASUREMENT* pmeasure);

int _fastcall mslMeasureCheck(MAPSELECT * data, TObjectHead* head, DATAEDIT * objdata);

int _fastcall mslMeasureCondition(MAPSELECT * data, int number, int expression);

double _fastcall mslMeasureValue(MAPSELECT * data, int number, int expression);

//*****************************************************
//  ������� ������ �������� ��  ������������� �������
//*****************************************************

int _fastcall mslSetAreaFlag(MAPSELECT * data, int flag);

void _fastcall mslAreaFree(MAPSELECT * data);

// ���������� ��������� ������ �� �������:
// distance - ������ ������� ������(����������) � ������
// info   - ������ ������� (� ������ !)
// filter - ���� ������� ������� �������� (1 - ����������)
// inside - ���� ������ ������ �������
// sample - ���� ������������ ������ ��������,���������������
//          ��������� ������ �� ������� (0 - �� �����������)
// ��� ������ ���������� 0
int _fastcall mslAreaSet(MAPSELECT * data, double distance, TObjectInfo * info,
                         int filter, int inside, int sample, MAPSELECT* view);

// ������� ������ ���������� �� ������� ��������
// ��� ������ ���������� "0"
int _fastcall mslSetSampleByArea(MAPSELECT * data, MAPSELECT* view);

// ��������� �������������� ������� �������� �������
// ��� �������� �������� ���������� 1, ����� - 0
int _fastcall mslCheckByArea(MAPSELECT * data,TObjectHead* head,OBJECTDATA* objdata);

// ��������� �������������� ������� �������� �������
// 0 - �� ��������
int _fastcall mslAreaCheck(MAPSELECT * data, TObjectHead* head, DATAEDIT * dataed);

// ��������� �������������� ������� �������� �������
int _fastcall mslAreaCheckByHead(MAPSELECT * data, TObjectHead* head);

// ��������� �� ��������� �������������� ������� �������� �������
// 0 - ������ �� ��������
int _fastcall mslAreaCheckByFrame(MAPSELECT * data, TObjectHead* head,
                                  DOUBLEPOINT* viewposition);

// �������� ���������� ����� �������� � ��������
// ���������� 0 ��� ������
int _fastcall mslToMeasureDistance(MAPSELECT * data, DATAEDIT * dataed,
                                   double* pdistance, DOUBLEPOINT* vpos);

// ���������, ������ �� ������� � ������
// ���������� "0",���� ���
int _fastcall mslIsAreaInside(MAPSELECT * data, DATAEDIT * dataed,DOUBLEPOINT* vpos);

//****************************************************
//  ������� ������ �� ��������� �������� �����
//****************************************************

// �������� ���������� �����
int _fastcall mslFrameClear(MAPSELECT * data);

// ���������� ���������� �����
int _fastcall mslFrameSet(MAPSELECT * data, FRAME * frame);

// �������� ����������� ���������� �����
int _fastcall mslFrameCheck(MAPSELECT * data, FRAME * frame);
int _fastcall mslFrameCheckHead(MAPSELECT * data, TObjectDesc desc);


//****************************************************
//  ������� ����������� ������ ��� �����
//****************************************************

int _fastcall mslClearTotalSeek(MAPSELECT * data);

// ���������� �������� ����������� ������
int _fastcall mslTotalSeekSelect(MAPSELECT * data, TMap* map, int visible);

// ��������� ������� ����������� ������ ��� �����
int _fastcall mslTotalSeekForMapSelect(MAPSELECT * data);

// ��������� ������� ����������� ������ �� ��������� ��������
int _fastcall mslVisibleSeekSelect(MAPSELECT * data);

// ��������� �������� ����������� ������
int _fastcall mslGetTotalSeekSelect(MAPSELECT * data);

// *********************************************
//  ������� ����������� ������� �������� �����
// *********************************************

// ������������� ������ �������� �����
int _fastcall mslFreezeMapStaff(MAPSELECT * data);

// �������� ������ � ������������� ������� �����
int _fastcall mslDefreezeMapStaff(MAPSELECT * data);

// *********************************************************
//  ������� �������������� ������ ���������� �������� �����
// *********************************************************

// ������������� ������ ���������� ��������
// ��� ������ ���������� "0"

int _fastcall mslInvertSample(MAPSELECT * data);

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ����� : ����� ������ ����������� ����� +++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ������������ ��� ������ ������������ ������,
// ������ �������� � ��������� ����������
// (����,����,�����������,��������������,������� ������������)

class _DLLCLASS TMapSelect : public TSample
{
  public:

 // �������� ������ ������
 enum FLAG  {
               ALL    = 0 ,     // ������ ������� �� �����������
               SELECT = 1       // ��������� �� ��������
            };

 enum CHECK {
               VIEW  = 1,       // ������ ������� �������
               SKIP  = 0        // ������ ������� ������������
            };

 enum AREA  {
               RECT  = 1,       // ����� �� �������������� �������
               POLY  = 2        // ����� �� ������ ���������
            };

 enum TOTALSEEK
            {
               TS_MAP = MSL_MAP,        // ������� ������ � ������ �����
               TS_VISIBLE = MSL_VISIBLE // ������� ������ ����� ������� �� ����� ��������
            };

 enum CODE           // ���� �������
  {
    PASS     = COM_PASS,  // ����� �������� ���������
    LESS     = CMLESS,    // ������
    LESSEQ   = CMLESSEQ,  // ������ ��� �����
    EQUAL    = CMEQUAL,   // �����
    NOTEQ    = CMNOTEQ,   // �� �����
    MORE     = CMMORE,    // ������
    MOREEQ   = CMMOREEQ,  // ������ ��� �����
    ANY      = CMANY,     // ����� �������� ���������

                     // ������������ ������� :
    OR       = CMOR,      // "���" - ���� �� ���� �����������
    AND      = CMAND,     // "�"   - ��� ������ �����������
  };

  // ������������� ������
  TMapSelect(TMap * map = 0);

  TMapSelect(TMapRsc * rsc);

  // ������� ����� �������� ������� ������ ��������
  TMapSelect(TMapSelect * select) : TSample()
   {
     SetSelect(select);
   }

  ~TMapSelect();

  // ������� ��� ������ � �����
  void Clear() { SelectAll(); }
  void SelectAll();

  // ���������� �����
  void SetMap(TMap * map);

  TMap * GetMap() { return Map; }

  TMapRsc * GetRsc() { return Rsc; }

  // ��������� - ���� �� ������� ��� ��������
  int IsSelectActive() { return IsActive; }

  // C���������� ������� ������ ��������
  void SetSelect(TMapSelect * select);

  // ��������� ������ ������, ����������� ��� ���������� ������� ������
  int GetSelectRecordSize();

  // ������������ ������ ��� ���������� ������� ������
  // buffer - ����� ������
  // length - ����� ������,��� ���������� ������
  // ��� ������ ���������� ����
  int GetSelectRecord(char * buffer,int length);

  // ��������� ������� ������ �� ������
  // buffer - ����� ������
  // length - ����� ������ ��� ������,����������� ������ (�� ������ ������)
  // ��� ������ ���������� ����
  int PutSelectRecord(char * buffer,int length);
  int PutSelectRecordOld(char * buffer,int length);

  // ���������� ������� �������� �� ����� �������������
  // �������� ��������
  // ��� ������ ���������� ����
  int GetSelectObjectCount();

  //  ���������� ������� �������� �� ����� �������������
  //  ����������� ���� ������� ������ ��������
  //  view - ������� ������ �������� (��� ��� �� �����)
  //  ��� ������ ���������� ����
  int GetMarkObjectCount(TMapSelect * select);

  // ���������� ������� ������ ��������
  // �� �������� �������� ����� (�����,�����������,����,���� ��������)
  // ���� ������ �����(map), ��� �������� ���������� (Map)
  int SetSelectByMap(TMap * map = 0);

  // �������� ������� ��������� �������� ��� �������������� �����
  // operation : OO_DELETE, OO_APPEND, OO_UPDATE
  void _fastcall UpdateSelectCountByObject(int number,
                                 TObjectDesc desc, TObjectData data,
                                 TObjectSemn semn, int operation);

  // ������������� ������ ���������� ��������
  // ��� ������ ���������� ����      
  int _fastcall InvertSample();


  // -------------------------------------------------------------
  //  ������ ������ �������� �����
  // -------------------------------------------------------------

  // �������� ������������ �������� �������
  // (����,�����������,��� �������,�����,���������,�������)
  // (����,�����������,��� �������,�����)
  // ���� ������ �� �������� �������� - ���������� ����
  int CheckObject(TObjectDesc desc, int number);
  int _fastcall CheckObject(TObjectInfo * info);
  int _fastcall CheckObject(TObjectDesc desc, TObjectData data,
                            TObjectSemn semn, int number);

  // ��������� ������������ ������������� ������������� �������
  // ���� ������ �� �������� �������� - ���������� ����
  int CheckSemantic(TObjectSemn semn);

  // -------------------------------------------------------------
  //  ������ ������� � �������� ��������� ��������� �������
  //  ���� ������� �� ��������� - ������������ ����
  // -------------------------------------------------------------

  // ���������� ����������� ����,����������� � ���� �������
  void ObjectSet(TObjectInfo * info);

  // ��������/�������� �������� �� ���������
  // ---------------------------------------

  int FrameClear()
    {
      IsModify    = 1;
      Frame = 0;
      return (FlagFrame = ALL);
    }

  int FrameSet(FRAME * frame)
    {
      IsModify    = 1;
      if (frame == 0) return FrameClear();
      Frame     = *frame;
      return (FlagFrame = SELECT);
    }

  // �������� ����������� ���������� �����

  int FrameCheck(FRAME * frame);
  int FrameCheck(TObjectDesc desc);

  // ��������/�������� �����������
  // -----------------------------

  void LocalClear(int number)
    {
      IsModify    = 1;
      Locals.Clear(number);
    }

  void LocalClear()
    {
      IsModify    = 1;
      Locals.Clear();
    }

  void LocalSet(int number)
    {
      IsModify    = 1;
      Locals.Set(number);
    }

  void LocalSet()
    {
      IsModify    = 1;
      Locals.Set();
    }

  int LocalCheck(int number)
    {
      return Locals.Check(number);
    }

  int LocalSelect(FLAG flag)
    {
      IsModify    = 1;
      return FlagLocals = flag;
    }

  int LocalSelect()
    {
      return FlagLocals;
    }

  // ��������/�������� ������������� �������
  // ---------------------------------------

  KEY KeyMin(KEY key)
    {
      IsModify    = 1;
      return KeyMini = key;
    }

  long int KeyMin()
    {
      return *(LONG*)&KeyMini;
    }

  KEY KeyMax(KEY key)
    {
      IsModify    = 1;
      return KeyMaxi = key;
    }

  long int KeyMax()
    {
      return *(LONG*)&KeyMaxi;
    }

  int KeyCheck(unsigned long int key)
    {
      if ((key < KeyMini.Long()) || (key > KeyMaxi.Long()))
        {
          return 0;
        }

      return 1;
    }

  int KeySelect(FLAG flag)
    {
      IsModify    = 1;
      return FlagKeys = flag;
    }

  int KeySelect()
    {
      return FlagKeys;
    }

  // ��������/�������� ��� �������
  // -----------------------------

  void ObjectClear(int number)
    {
      IsModify    = 1;
      Objects.Clear(number);
    }

  void ObjectClear()
    {
      IsModify    = 1;
      Objects.Clear();
    }

  void ObjectSet(int number)
    {
      IsModify    = 1;
      Objects.Set(number);
    }

  void ObjectSet()
    {
      IsModify    = 1;
      Objects.Set();
    }

  int ObjectCheck(int number)
    {
      return Objects.Check(number);
    }

  int ObjectSelect(FLAG flag)
    {
      IsModify    = 1;
      return FlagObjects = flag;
    }

  int ObjectSelect()
    {
      return FlagObjects;
    }


  // ��������/�������� �������
  // -----------------------------

  void SegmentClear(int number)
    {
      IsModify    = 1;
      Segments.Clear(number);
    }

  void SegmentClear()
    {
      IsModify    = 1;
      Segments.Clear();
    }

  void SegmentSet(int number)
    {
      IsModify    = 1;
      Segments.Set(number);
    }

  void SegmentSet()
    {
      IsModify    = 1;
      Segments.Set();
    }

  int SegmentCheck(int number)
    {
      return Segments.Check(number);
    }

  int SegmentSelect(FLAG flag)
    {
      IsModify    = 1;
      return FlagSegments = flag;
    }

  int SegmentSelect()
    {
      return FlagSegments;
    }


 // ��������/�������� �������������� ��������
 // ----------------------------------------------

 int SemanticSelect(FLAG flag)
    {
      IsModify    = 1;
      return FlagSemantics = flag;
    }

 int SemanticSelect()
    {
      return FlagSemantics;
    }

 // �������� ������� � ������
 // ��� ������ ���������� ����, ����� - ����� �������

 int SemanticAppend(int code,int semcode,char * value);

 // ������� ��� ������� �� ������

 void SemanticClear();

 // ������� ������� �� ������
 // number - ����� ������� � ������ (�� 1 �� GetCount())
 // ��� ������ ���������� ����

 int SemanticDelete(int number);

 // ��������� ����� �������� � ������ �������

 int SemanticCount()
    {
      return Condition.GetCount();
    }

 // ��������� ��� �������
 // number - ����� ������� � ������ (�� 1 �� GetCount())
 // ��� ������ ���������� ����

 int SemanticCondition(int number)
    {
      return Condition.GetCondition(number);
    }

 // ��������� �������� �������������� �� �������
 // number - ����� ������� � ������ (�� 1 �� GetCount())
 // ��� ������ ���������� ����, ����� - place

 char * SemanticValue(int number,char * place,int size);

 // ��������� �������� �������������� �� �������
 // number - ����� ������� � ������ (�� 1 �� GetCount())
 // ��� ������ ���������� ����, ����� - place

 int SemanticCode(int number)
    {
      TSemBlock * block = Condition.GetValue(number);
      if (block == 0) return 0;
      return block->Code();
    }

 // ��������� �������� �������������� �� �������
 // number - ����� ������� � ������ (�� 1 �� GetCount())
 // ��� ������ ���������� ����� ������ ������

 const char * SemanticCodeName(int number);

 // ��������� ��� ������������� �������
 // ��� ������ ���������� ����

 int SemanticLink()
    {
      return Condition.GetLinkCode();
    }

 // ���������� ��� ������������� �������
 // TMapSelect::OR ��� TMapSelect::AND
 // ��� ������ ���������� ����

 int SemanticLink(int code)
    {
      IsModify    = 1;
      return Condition.SetLinkCode(code);
    }

 // ��������/�������� ������� �������� ������                    

 int  InversionFlag(int flag)
    {
       IsModify    = 1;
       return (FlagInversion = flag);
    }

 int  InversionFlag()
    {
       return FlagInversion;
    }


 // ��������/�������� ������� ������
 // --------------------------------

 // ��������/�������� �������

 int AreaSelect(FLAG flag)
    {
      IsModify    = 1;
      return FlagArea = flag;
    }

 int AreaSelect()
    {
      return FlagArea;
    }

 // �������� ��������� �������
 void AreaClear();

 // ���������� ��������� ������ �� �������:
 // distance - ������ ������� ������(����������) � ������
 // info   - ������ �������
 // filter - ���� ������� ������� �������� (1 - ����������)
 // inside - ���� ������ ������ �������
 // sample - ���� ������������ ������ ��������,���������������
 //          ��������� ������ �� ������� (0 - �� �����������)

 void AreaSet(double distance, TObjectInfo * info,
              int filter = 0, int inside = 0, int sample = 0,
              TMapSelect* view=0);

 // ����������/�������� ������ ��������

 int AreaFilter(int flag)
    {
      IsModify    = 1;
      return AreaParm.FilterFlag = flag;
    }

 int AreaFilter()
    {
       return AreaParm.FilterFlag;
    }

 //  ����������/��������� �������� ����������

 double AreaDistance(double dist)
    {
       return AreaParm.Distance = dist;
    }

 double AreaDistance()
    {
       return AreaParm.Distance;
    }

 // ���������� ������ �������

 int LoadAreaSource(TObjectInfo *info);

 // ��������� ������ �������

 TDataEdit * AreaSource()
    {
       return (&(AreaParm.AreaData));
    }

 // ��������� �������� �������

 DFRAME * AreaFrame()
    {
       if ( AreaSelect() == ALL ) return 0;
       return &(AreaParm.AreaFrame);
    }

 // ����������/�������� ������� ������(������/��� �������)
 // (flag = 1 - ������, 0 - ���)

 int AreaInside(int flag)
    {
      IsModify    = 1;
      return AreaParm.InsideFlag = flag;
    }

 int AreaInside()
    {
       return AreaParm.InsideFlag;
    }

 // ��������� �������������� ������� �������� �������
 // 0 - �� ��������

 int _fastcall AreaCheck(TObjectDesc desc, TDataEdit * data);

 int _fastcall AreaCheck(TObjectDesc desc);

 // ���������� ����� ��� ������ ��� � ������� �������
 int TitleSet(char * text);

 protected :

 // ��������� �� ��������� �������������� ������� �������� �������
 // 0 - ������ �� ��������

 int _fastcall AreaCheckByFrame(TObjectDesc desc,
                                DOUBLEPOINT* viewposition);

 // �������� ���������� �� �������
 // ��� ������ ���������� 0, ����� - 1,
 // �� ������ distance ��������� �������� ����������

 int _fastcall ToMeasureDistance(TDataEdit * data, double* distance,
                                 DOUBLEPOINT* viewposition);

 // ��������� ��������� ������� � ������
 // (������� ������ � ������,���� ������ �� �����
 //  ����� ������ �������)
 // ���������� "0",���� �� ������

 int _fastcall IsAreaInside(TDataEdit * data,
                            DOUBLEPOINT* viewposition);

 public :

 // ������� ������ ���������� �� ������� ��������
 // ��� ������ ���������� "0"

 int SetSampleByArea(TMapSelect* view);

 // ���������� ������������� ���� ����������
 // � ��� ����� ���������

 void SetWinHandle(HWND hwnd)
 {
   SendHandle = (long int) hwnd;
 }

 // �������� ������������� ���� ����������
 // � ��� ����� ���������

 void ClearWinHandle()
 {
   SendHandle = -1;
 }


 // ��������/�������� ��������� ����
 // --------------------------------

 void ListClear(int number)
    {
      IsModify    = 1;
      Lists.Clear(number);
    }

 void ListClear()
    {
      IsModify    = 1;
      Lists.Clear();
    }

 void ListSet(int number)
    {
      IsModify    = 1;
      Lists.Set(number);
    }

 void ListSet()
    {
      IsModify    = 1;
      Lists.Set();
    }

 int ListCheck(int number)
    {
      if (FlagLists == 0) return 1;
      return Lists.Check(number);
    }

 int ListSelect(FLAG flag)
    {
      IsModify    = 1;
      return FlagLists = flag;
    }

 int ListSelect()
    {
      return FlagLists;
    }

 // ��������/�������� ����� �������� �� ����������
 // ----------------------------------------------
  int MeasureSelect(FLAG flag);

 int MeasureSelect()
    {
      return FlagMeasure;
    }

 int MeasureLink();

 int MeasureLink(int code);

 int MeasureClear();

 int MeasureAdd(MEASUREMENT* pmeasure);

 int MeasureCheck(TObjectDesc desc, TDataEdit * data);

 int MeasureCount()
    {
       return Measure.MeasureCount;
    }

 int MeasureRange(int number);

 int MeasureKind(int number);

 int MeasureCondition(int number, int expression = 1);

 double MeasureValue(int number, int expression = 1);

 // -------------------------------------------------------------
 //  ������ ������� � �������� ��������� ����������� ������
 // -------------------------------------------------------------

 // �������� �������� ����������� ������
 int ClearTotalSeek();

 // ���������� �������� ����������� ������
 int TotalSeekSelect(TMap* map = 0, int visible = 0);

 // ��������� �������� ����������� ������
 int TotalSeekSelect(void)
 {
   return FlagTotalSeek;
 }

 // ��������� ������� ����������� ������ ��� �����
 int TotalSeekForMapSelect()
 {
   return (FlagTotalSeek & TS_MAP);
 }

 // ��������� ������� ����������� ������ �� ��������� ��������
 int VisibleSeekSelect()
 {
   return (FlagTotalSeek & TS_VISIBLE);
 }

  // ************************************************************
  //                                                            *
  //         ����������� ��������                               *
  //                                                            *
  // ************************************************************

public :

  operator HSELECT()
  {
    return (HSELECT) this;
  }
};

#endif // MAPSELC_H
