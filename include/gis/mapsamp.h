
#ifndef MAPSAMP_H
#define MAPSAMP_H

#ifndef MAPTYPE_H
 #include "maptype.h"
#endif

#ifndef MAPDEF_H
 #include "mapdef.h"
#endif

#ifndef MAPBITS_H
  #include "mapbits.h"
#endif

#ifndef MAPSEM_H
  #include "mapsem.h"
#endif

#define SEMCOUNT 64
#define MEASURECOUNT 100

typedef struct _DLLCLASS MEASUREMENT
{
  int    measure;      // ��� ���������:�����,�������,��������,������  
  int    range;        // ��� ���������(������������ ��������/��������)
  int    condition1;   // ������ ������� ������(>,<,>=,...)
  int    condition2;   // ������ ������� ������(>,<,>=,...)
  double value1;       // ������ ��������(� ���������, ��� ������ � ������) 
  double value2;       // ������ ��������(� ���������, ��� ������ � ������)
}
  MEASUREMENT;

typedef struct _DLLCLASS AREAPARM    // �������� ���������� ������ �������� �� �������
{
  AREAPARM() : AreaData() { Distance = 0; }

  double     Distance;     // ������ ������� ������ � ������
  TDataEdit  AreaData;     // ������� ������� � ������ � ���������
  DFRAME     AreaFrame;    // �������� ������� � ������
  int        FilterFlag;   // ���������/�� ��������� ������ ��������
  int        InsideFlag;   // ��������� ����� ������ ������� (InsideFlag=1)
}
  AREAPARM;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ ��������� ������ �� ��������������� (����������)  +++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 enum                // ���� �������
  {
    COM_PASS     = 0,             // ����� �������� ���������
    COM_FLAGPASS = 1,             // ������� ������� � ����� COM_PASS
  };

typedef struct _DLLCLASS COMPARE     // ��������� ������ �� ��������������� (����������)
{
  COMPARE()
  {
    Count = 0; Flags = CMOR; MinCount = 0;
    memset((void *)&Numbers[0],0,sizeof(Numbers));
  }

  int Count;                      // ����� �������� ������� (�������������)

  TSemBlock Semantics[SEMCOUNT];  // �������� �������������
  int Conditions[SEMCOUNT];       // ������� ������ (>,<,!=,...)
  int Numbers[SEMCOUNT];          // ������� ������ (>,<,!=,...)
  int Flags;                      // ���������� �������������� ������
                                  // � ��������� ������� (&&,||)
  int MinCount;                   // ����������� ����� �������������,
                                  // ������� ����� ������������
}
  COMPARE;

// ������������������� ��������� ������ �������� �� ����������
void _fastcall comInit(COMPARE * data);

// �������/��������  ��������� ������ �������� �� ����������
void _fastcall comFree(COMPARE * data);

// �������� ������� � ������ ��������
// ��� ������ ���������� ����, ����� - ����� �������
int _fastcall comAppend(COMPARE * data, int code, SEMBLOCK * block);

// ������� ������� �� ������
// number - ����� ������� � ������
// ��� ������ ���������� ����
int _fastcall comDelete(COMPARE * data, int number);

// ��������� ��� ������� �� ������
// number - ����� ������� � ������
// ��� ������ ���������� ����
int _fastcall comGetCondition(COMPARE * data, int number);

// ���������� ��� ������������� �������
// ��� ������ ���������� ����
int _fastcall comSetLinkCode(COMPARE* data, int code);

// ��������� ������������ �������� �������
// number - ����� ������� � ������
// ��� ������ ���������� ����
TSemBlock * _fastcall comGetValue(COMPARE * data, int number);

//  ��������� ������������ ������������� ������������� �������
//  ��� �������� �������� ���������� 1, ����� - 0
int _fastcall comCheckSemantic(COMPARE * data, SEMANTIC * semn);


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ����� : ������� ������ �� ��������� ++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TCompare : public COMPARE
{
 public :

 TCompare() : COMPARE(){}

 ~TCompare() {}

 enum                // ���� �������
  {
    PASS     = COM_PASS,  // ����� �������� ���������
    LESS     = CMLESS,    // ������
    LESSEQ   = CMLESSEQ,  // ������ ��� �����
    EQUAL    = CMEQUAL,   // �����
    NOTEQ    = CMNOTEQ,   // �� �����
    MORE     = CMMORE,    // ������
    MOREEQ   = CMMOREEQ,  // ������ ��� �����
    ANY      = CMANY,     // ����� �������� ���������
  };


 enum                // ���������� ������
  {
    FLAGPASS = COM_FLAGPASS, // ������� ������� � ����� PASS

                     // ������������ ������� :
    OR       = CMOR,         // "���" - ���� �� ���� �����������
    AND      = CMAND,        // "�"   - ��� ������ �����������
  };

 // �������� ������� � ������
 // ��� ������ ���������� ����, ����� - ����� �������

 int Append(int code,TSemBlock * block);

 // ��������� ������������ ������������� ������������� �������
 // ���� ������ �� �������� �������� - ���������� ����

 int CheckSemantic(TObjectSemn semn);

 // ������� ��� ������� �� ������

 void Clear();

 // ������� ������� �� ������
 // number - ����� ������� � ������ (�� 1 �� GetCount())
 // ��� ������ ���������� ����

 int Delete(int number);

 // ��������� ����� �������� � ������ �������

 int GetCount() { return Count; }

 // ��������� ����������� ��������� ����� �������

 int GetLimit() { return SEMCOUNT; }

 // ��������� ��� �������
 // number - ����� ������� � ������ (�� 1 �� GetCount())
 // ��� ������ ���������� ����

 int GetCondition(int number);

 // ��������� ������������ �������� �������
 // number - ����� ������� � ������ (�� 1 �� GetCount())
 // ��� ������ ���������� ����

 TSemBlock * GetValue(int number);

 // ��������� ��� ������������� �������
 // ��� ������ ���������� ����

 int GetLinkCode() { return (Flags & (AND | OR)); }

 // ���������� ��� ������������� �������
 // ��� ������ ���������� ����

 int SetLinkCode(int code);

};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++ ��������� ������ ��  ��������  ����������  +++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 enum                // ��� ���������
  {
    PM_LENGTH      = 1,          // �����
    PM_SQUARE      = 2,          // �������
    PM_PERIMETER   = 3,          // ��������
    PM_LENGTHKM    = 4,          // ����� (��)
    PM_SQUAREKM    = 5,          // ������� (��. ��)
    PM_PERIMETERKM = 6,          // �������� (��)
    PM_SQUAREMM    = 7,          // ������� (��. ��)           
    PM_HEIGHT      = 10,         // ������ (�)
  } ;

 enum                // ��� ��������� ��� ������
  {
    PM_SINGLE = 1,          // ������������ ��������
    PM_RANGE  = 2,          // �������� ��������
  };


typedef struct _DLLCLASS MEASUREMENTDATA       // ��������� ������ �� �������� ����������
{
  MEASUREMENTDATA()
  {
    MeasureCount = 0; Flag = CMOR;
    memset((void *)Measure, 0, sizeof(Measure));
  }

 int MeasureCount;                   // ����� ������� � ������
 MEASUREMENT  Measure[MEASURECOUNT]; // �������� �������
 int Flag;                           // ��� ���������� �������(OR\AND)
}
  MEASUREMENTDATA;

// ������������������� ��������� ������ �������� �� ����������
void _fastcall pmInit(MEASUREMENTDATA * data);

// �������/��������  ��������� ������ �������� �� ����������
void _fastcall pmFree(MEASUREMENTDATA * data);

// ��������� ����� ������� � ������
int _fastcall pmCount(MEASUREMENTDATA * data);

// �������� ��������� � ������
// ��� ������ ���������� ����
int _fastcall pmAdd(MEASUREMENTDATA * data, MEASUREMENT* pmeasure);

// ��������� ��� ��������� � ������ �� ������ number
// (�����,��������,...)
int _fastcall pmMeasureKind(MEASUREMENTDATA * data, int number);

// ��������� ��� ��������� �� ������ number � ������
// (������������ ��������/�������� ��������)
int _fastcall pmRange(MEASUREMENTDATA * data, int number);

// ��������� ��� ������� ������� �� ������ number � ������ (>,<,...)
// ��� ������ ���������� ����
int _fastcall pmFirstCondition(MEASUREMENTDATA * data, int number);

// ��������� ��� ������� ������� �� ������ number � ������ (>,<,...)
// (������ ��� ��������� ��������)
// ��� ������ ���������� ����
int _fastcall pmSecondCondition(MEASUREMENTDATA * data, int number);

// ��������� ������ �������� ��������� �� ������ number � ������
// ��� ������ ���������� ����
double _fastcall pmFirstValue(MEASUREMENTDATA * data, int number);

// ��������� ������ �������� ��������� �� ������ number � ������
// ��� ������ ���������� ����
double _fastcall pmSecondValue(MEASUREMENTDATA * data, int number);

// ��������� ��� ���������� �������
int _fastcall pmGetLinkCode(MEASUREMENTDATA * data);

// ���������� ��� ���������� �������
int _fastcall pmSetLinkCode(MEASUREMENTDATA * data, int code);

//  ��������� ������ ������ �� ������ number
//  ��� �������� �������� ���������� 1, ����� - 0
int _fastcall pmTest(MEASUREMENTDATA * data, int number, double value);

//  ��������� ������������ ������� � ��������
//  ��� �������� �������� ���������� 1, ����� - 0
int _fastcall pmTestCondition(int condition, double target, double source);

//  ��������� ������ ������ �� ������ number �� ������   
//  ��� �������� �������� ���������� 1, ����� - 0
int _fastcall pmTestByHeight(MEASUREMENTDATA * data, int number, DATAEDIT * metric);

// ��������� ��������� �������
// (DATAEDIT �������� �� ������ ������� desc)
// ��� �������� �������� ���������� 1, ����� - 0
int _fastcall pmMeasureCheck(MEASUREMENTDATA * data, TMap * map,
                             TObjectHead* head, DATAEDIT * metric);


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ ����� : ��������� ������ �� ��������  ����������  +++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TPlaneMeasure : public MEASUREMENTDATA
{
 public :

 TPlaneMeasure() : MEASUREMENTDATA() {;}

 ~TPlaneMeasure() {}

  enum                // ���� �������
  {
    LESS     = CMLESS,    // ������
    LESSEQ   = CMLESSEQ,  // ������ ��� �����
    EQUAL    = CMEQUAL,   // �����
    NOTEQ    = CMNOTEQ,   // �� �����
    MORE     = CMMORE,    // ������
    MOREEQ   = CMMOREEQ,  // ������ ��� �����
  };

  enum                // ��� ���������
  {
    LENGTH      = PM_LENGTH,          // �����
    SQUARE      = PM_SQUARE,          // �������
    PERIMETER   = PM_PERIMETER,       // ��������
    LENGTHKM    = PM_LENGTHKM,        // ����� (��)
    SQUAREKM    = PM_SQUAREKM,        // ������� (��. ��)
    PERIMETERKM = PM_PERIMETERKM,     // �������� (��)
    HEIGHT      = PM_HEIGHT,          // ������ (�)
  };

  enum                // ��� ��������� ��� ������
  {
    SINGLE = PM_SINGLE,   // ������������ ��������
    RANGE  = PM_RANGE,    // �������� ��������
  };

  enum                // ������������ ������� :
  {
    OR       = CMOR,      // "���" - ���� �� ���� �����������
    AND      = CMAND,     // "�"   - ��� ������ �����������
  };


 // �������� ��������� � ������

 int Add(MEASUREMENT* pmeasure);

 // ������� ��� ������� �� ������

 void Clear();

 // ����� ������� � ������

 int Count();

 // ��� ��������� � ������ �� ������ number
 // (�����,��������,...)

 int MeasureKind(int number);

 // ��� ��������� �� ������ number � ������
 // (������������ ��������/�������� ��������)

 int Range(int number);

 // ��� ������� ������� �� ������ number � ������ (>,<,...)

 int FirstCondition(int number);

 // ��� ������� ������� �� ������ number � ������ (>,<,...)
 // (������ ��� ��������� ��������)

 int SecondCondition(int number);

 // ������ �������� ��������� �� ������ number � ������

 double FirstValue(int number);

 // ������ �������� ��������� �� ������ number � ������
 // (������ ��� ��������� ��������)

 double SecondValue(int number);

 // ���������/���������� ��� ���������� �������

 int GetLinkCode();

 int SetLinkCode(int code);

 // ��������� ��������� �������
 // (TDataEdit �������� �� ������ ���������� �������)
 //  ��� �������� �������� ���������� 1, ����� - 0

 int _fastcall MeasureCheck(TMap * map, TObjectDesc desc, TDataEdit * data);

 //  ��������� ������ ������ �� ������ number
 //  ��� �������� �������� ���������� 1, ����� - 0

 int Test(int number, double value);

 //  ��������� ������������ ������� � ��������
 //  ��� �������� �������� ���������� 1, ����� - 0

 int TestCondition(int condition, double target, double source);

 //  ��������� ������ ������ �� ������ number �� ������   
 //  ��� �������� �������� ���������� 1, ����� - 0

 int TestByHeight(int number, TDataEdit * data);

};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ����� : ����� ��'����� ����� +++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef class _DLLCLASS TSample
{
 public :

 TSample(TMap* map = 0);

 ~TSample();

 // �������� ���������� ������ � ������
 // number - ����� ������� � ����� �����
 // list   - ����� ����� � �����
 // ��� ������ ���������� ����

 int AppendSample(int number, int list = 1);

 // ������� ������ �� ������
 // number - ����� ������� � ����� �����
 // list   - ����� ����� � �����
 // ��� ������ ���������� ����

 int DeleteSample(int number, int list = 1);

 // ��������� ��������� ������ �� ��������� ������� ������
 // ���� ��������� ������ ��� - ���������� ���������
 // � ������ ����� � ������������ � flag (WO_NEXT, WO_BACK)
 // ��� ������ ���������� ����

 int _fastcall Adjustment(int number, int list = 1, int flag = 0);

 // ������������������� ����� ������ �������� �����

 void ClearSample();

 // ��������� ������� ������� � ������
 // ���������� ����� � ������
 // ���� ������� ��� - ���������� ����

 int CheckSample(int number, int list);

 // ��������� ������� �����a ��� ����� list
 // ���� �����a ��� - ���������� ����

 int CheckSample(int list);

 // ��������� ����� �������� � ������ ��� ����� list

 int GetSamplesCount(int list = 1);

 // ��������� ������ ������� ������ �������� ��� ����� list
 // ���� list ���������� �������
 // ���� ����� ��� - ���������� ����

 int GetFirstSample(int list = 1);

 // ��������� ��������� ������� ������ �������� ��� �������� �����
 // ��� ������ - ���������� ����

 int GetLastSample(int list = 1);

 // ��������� ��������� ������� ������ �������� ��� �������� �����
 // ���� ������� ��� - ���������� ����

 int GetNextSample(int list);

 // ��������� ���������� ������� ������ �������� ��� �������� �����
 // ���� ����������� ������� ��� - ���������� ����

 int GetPrevSample(int list);

 // ��������� ������� ������ �������� �� ������ ��� �������� �����
 // ��� ������ - ���������� ����

 int GetSample(int number, int list);

 // ��������� - ���� �� ���������� �������

 int IsSample() { return Sample; }
 int SampleSelect() { return Sample; }

 // ��������� ����� ������ � ������

 int GetSampleListCount() { return Count; }

 // ��������� ����� ������� ������

 char * GetSampleMemory() { return Memory; }

 // ��������� ������ ������� ������

 int GetSampleMemoryLength() { return Length; }

 // ��������� ������ ������� ������� ������

 int GetSampleMemorySize() { return Size; }

 protected :

 // �������� ������ ��� ������ ���������� �������� �����
 // ��� ������ ���������� ����

 int Allocate(int size);

 // ����������� ���������� ������ ���������� �������� �����
 // ��� ������ ���������� ����

 int Load(TSample * sample);

 // ���������� ������� ������ ��������

 int * SeekPosition(int * begin, int number);

 // ��������� ����� ������ ��� ����� list
 // ��� list = 0 ���������� ����� ������ �������� �����
 // ��� ������ ���������� ����

 int * SeekSample(int list = 0);

 public :

 TMap     * Map;          // �����, �� ������� ���������� �������

 int        Count;        // Max ����� ���������� ������
 char *     Memory;       // ����� ���������� ������� ������
 int        Length;       // ������ ���������� ������� ������
 int        Size;         // ����� ������
 int        ListSize;     // ����� ������ ������
 int        Item;         // ������ � ������ �������� ��� ����� List
 int        CheckItem;    // ������, �� ������� �� ����������� ������� CheckSample
 int        Sample;       // ������� ������� ������ �� �������  

 TBitSet256 Segments;     // �������� ���������� ��������� ������
 TBitSet32  Locals;       // �������� ���������� ����������� ������
 TBitSet64K Objects;      // �������� ���������� ����� ��������
 TBitSet4K  Lists;        // �������� ���������� ������ �����

 int FlagSegments;        // ������� ������ ���������
 int FlagLocals;          // ������� ������ �����������
 int FlagObjects;         // ������� ������ ��������
 int FlagLists;           // ������� ������ ������
 int FlagSemantics;       // ������� ������ ������������� ��������
 int FlagKeys;            // ������� ������ �� �������
 int FlagArea;            // ������� ������ �� ��������� �������
                          // ��������� ������������ ������������
 int FlagFrame;           // ������� ������ �� ��������� �������
                          // (��������� � �������� �������������)
 int FlagMeasure;         // ������� ������ �� ���������� ��������
 int FlagTotalSeek;       // �������� ����������� ������           
 int FlagInversion;       // ������� �������� ������ �� �������    
 int FlagFrozenMap;       // ������� ������������ ������� �����    
 int FlagDrawObjects;     // ������� ������ ����������� �������� : 
								  // 0 - ����� �� "������" �������,
								  // 1 - �������� ������ ����������� �������,
								  // 2 - �� �������� ����������� �������.

 KEY KeyMini;             // ����������� ���������� �������� ������ �������
 KEY KeyMaxi;             // ������������ ���������� �������� ������ �������

 FRAME Frame;             // ���������� ����� ��� ���������� ��������
                          // �� �� ��������� �� ���������

 AREAPARM  AreaParm;      // ��������� ������ �������� �� �������

 TCompare Condition;      // ������� ������ ��������
                          // �� ������������� ���������������
 TPlaneMeasure Measure;   // ������� ������ �������� �� ����������

 int          IsModify;   // ������� ��������� �������

 int          MarkCount;  // ������� �������� �� ����������� �������
 int          SelectCount;// ������� �������� �� �������� ��������

 TMapSelect * MarkSelect; // ������� ����������� � ��������� �������

 int          MapMode;    // ��������� ������

 long int  SendHandle;    // ������������� ���� ���������

 long int  FrozenCount;   // ����� ��������������� �������� ����� �����  

 long int *AddrFrozenCount;// ����� ������� �������� ����� �������� �� ������ �����

 TMapRsc * Rsc;           // ������������� (����� ����� ����������)

 int       MapComplex;    // ������� �������������� ����� Sample � ����.���-��

 int       FlagTitle;      // ������� ������ ������ �������
 char      TitleText[255]; // ����� ������� ��� ������

 int       IsActive;       // ������� ��������� ������� ������  

}
  TSample;

typedef TSample MAPSELECT;

// �������� ������ ��� ������ ���������� �������� �����
// ��� ������ ���������� ����
int _fastcall smAllocate(MAPSELECT * data, int size);

// ����������� ���������� ������ ���������� �������� �����
// ��� ������ ���������� ����
int _fastcall smLoad(MAPSELECT * dest, MAPSELECT * data);

// �������� ������ � ������
// number - ����� ������� � ����� �����
// list   - ����� ����� � �����
// ��� ������ ���������� ����
int _fastcall smAppendSample(MAPSELECT * data, int number, int list);

// ��������� ������� ������� � ������
// ���������� ����� � ������ ��� 0
int _fastcall smCheckSample(MAPSELECT * data, int number, int list);

// ��������� ������� �����a ��� ����� list
// ���� �����a ���, ���������� ����
int _fastcall smCheckSampleByList(MAPSELECT * data, int list);

// ���������� ������� ������ �������� � ������
// begin  - ����� ������ ������ ��� ������ ��������
// number - ����� ������ ��������
// ���������� ����� ��� ������ ������ ��������
int* _fastcall smSeekPosition(MAPSELECT * data, int * begin, int number);

// ��������� ������ ������� ������ �������� ��� ����� list
// (����� ������� ������� ��� ������)
// ���������� ����� ������� ������� � ������ ��� ����� list
// ���� ��� ����� ����������� ����� ��� ��� ������ ���������� ����
int _fastcall smGetFirstSample(MAPSELECT * data, int list);

// ��������� ��������� ������� ������ �������� ��� ����� list
// ���� list ���������� �������
// ��� ������ ���������� ����
int _fastcall smGetLastSample(MAPSELECT * data, int list);

// ��������� ��������� ������� ������ �������� ��� �������� �����
// ��� ������ ���������� ����
int _fastcall smGetNextSample(MAPSELECT * data, int list);

// ��������� ����� �������� � ������ ��� ����� list
// ��� ���������� ������ ��� ����� list � ��� ������ ���������� ����
int _fastcall smGetSamplesCount(MAPSELECT * data, int list);

// ��������� ����� ������ �� ������ �����
// ��� list = 0 ���������� ����� ������ �������� �����
// ��� ������ ���������� ����
int * _fastcall smSeekSample(MAPSELECT * data, int list);

// ��������� ���������� ������� ������ �������� ��� �������� �����
// ���� ����������� ������� ���, ���������� ����
int _fastcall smGetPrevSample(MAPSELECT * data, int list);

// ��������� ������� ������ �������� �� ������ ��� �������� �����
// ��� ������ ���������� ����
int _fastcall smGetSample(MAPSELECT * data, int number, int list);

// ��������� ��������� �� ��������� ������
// ��� ������ ���������� ����
int _fastcall smAdjustment(MAPSELECT * data, int number, int list, int flag);

// ������� ������ �� ������
// number - ����� ������� � ����� �����
// list   - ����� ����� � �����
// ��� ������ ���������� ����
int _fastcall smDeleteSample(MAPSELECT * data, int number, int list);

#endif  // MAPSAMP_H

