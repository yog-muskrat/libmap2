
#ifndef MAPSET_H
#define MAPSET_H

#ifdef __cplusplus                 // �� ���������� �� �

#ifndef MAPACCES_H
  #include "mapacces.h"
#endif

#define MAXINFOCOUNT 64

// *********************************************************************
//         ���� �������� ��� ���������� ������ ����� ��������� :
//
// 32801 - ������� �������, �������� ������ �� ����������� ������;
// 32802 - ������� �������, �� ������� ������� ������ �� �������� �������;
// 32803 - ������� �������, ��������� � ������ ������������ ��������.
// *********************************************************************

typedef struct OBJECTCHAIN
{
  OBJECTCHAIN *Next;              // ��������� �� ��������� ���������
  OBJECTCHAIN *Back;              // ��������� �� ���������� ���������
  int         ObjectCount;        // ���������� �������� � �������
  TObjectInfo Info[MAXINFOCOUNT]; // ������ Info
}
  OBJECTCHAIN;


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ����� ��������, ������������ � ������   ++++++++
// ++++++++    �� ������������� ��������������      ++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TObjectSet
{

public:

  enum SEMKODGROUP
       {
       EGUITABLE   = GROUPPARTNER, // ������� �������, ��������� � ������
                                   // ������������ ��������
                                   // (������� ������ ������������ � ������);
       GENERAL     = GROUPLEADER,  // ������� �������, �������� ������ ��
                                   // ����������� ������
                                   // (������� ������ ��������� �� �������);
       SUBORDINATE = GROUPSLAVE,   // ������� �������, �� ������� �������
                                   // ������ �� �������� �������;
       };

public:

  TObjectSet();

  // semn - ��� ������������� �������������� ��� ������ � info
  //        EGUITABLE, GENERAL, SUBORDINATE
  // ���� semn = 0 - ���� ������ ���������� ��������� ���������
  TObjectSet(TObjectInfo *info, int semn = 0);

  ~TObjectSet();

  // ��������� ������ �� ������������ � info ��������� ���������
  // semn - ��� ������������� �������������� ��� ������ � info
  //        EGUITABLE, GENERAL, SUBORDINATE
  // ���� semn = 0 - ���� ������ ���������� ��������� ���������
  int Build(TObjectInfo *info, int semn = 0);

  // ��������� Select �� ��������� ��������
  int BuildSelect(TMapSelect *select);

  // ��������� ������ �� �������� �����, ������� � ��� ���
  // ������� ����������� �����
  // �� ������������ � info ��������� ���������
  int BuildInsertKnot(TObjectInfo *info);

  // ��������� ������ ������������ �������� �� Select
  // map - �����
  // listnumber - ����� �����
  void BuildEguitableSelect(TMap *map, int listnumber);

  // ��������� ����� ������ ������������ ��������
  void BuildEguitable();

  // ��������� ����� ������, ������� ������� � ����������� �������
  void BuildGeneral();

  // ���������� ������� �������� ������
  int IsActive();

  // ���������� ������ ����� ���������� info
  // =======================================

  // ���������������� ���������� ������ �� ������������ �
  // info ��������� ��������� ��� ����������� ������
  // �������� �� ����� (��������� ������ ���� ������)
  // ��� ����������� ���������� ������ ������������
  // ������� AppendNext
  // type - ��� ������
  //        ���� == 0, ��� ����� �� ������������ � info
  //        ��������� ���������
  // semn - ��� ������������� �������������� ��� ������ � info
  //            EGUITABLE, GENERAL, SUBORDINATE
  // ���� semn = 0 - ���� ������ ���������� ��������� ���������
  // ���������� �������������� ��� ��������� ��� ���������� �������
  int InitBuild(TObjectInfo *info, int type = 0, int semn = 0);

  // ���������� ���������� ������ (�������� ��������� ������)
  // type - �������������� ��� ��������� ��� �������� �������
  // ���������� �������������� ��� ��������� ��� ����������
  // ������� ��� 0
  int AppendNext(TObjectInfo *info, int type);

  // ������� ������ ����� ������ ��������
  int Object(TObjectSet *set);

  // ������� ���������
  // =================

  // ��������� ���������� �������� � ������
  int GetCount();

  // ��������� ������ �� ������ (� 1)
  TObjectInfo *GetObject(int number);

  // ��������� �������� �������� ������
  DFRAME *ViewObjectFramePlane(DFRAME *frame);

  // ���������� �������
  // ==================

  // �������� ������������ ������ ������
  // save - ���������� � ����
  //      =  0 - �� ���������, 1 - ���������
  // ���������� ���������� ����� ������� ��� 0
  int AppendEguitable(TObjectInfo *info, int save = 0);

  // �������� ����������� ������ ������
  // save - ���������� � ����
  //      =  0 - �� ���������, 1 - ���������
  // ���� ������ info �������� ��������� ��������� � �������� �������
  // - ��������� ��������� ��������� (������� ����� ������ �� �������� ������)
  // ���� ������ info �������� ��������� ��������� � �������� �����������
  // - ��������� � �����, ������� ��������� ���������
  // ���������� ���������� ����� ������� ��� 0
  int AppendSubordinate(TObjectInfo *info, int save = 0);

  // �������� ����������� ������ ������
  // save - ���������� � ����
  //      =  0 - �� ���������, 1 - ���������
  // ���� ������ info �������� ��������� ��������� � �������� �����������
  // - ��������� ������������ ������ � ������� �����
  // ���������� ���������� ����� ������� ��� 0
  int AppendSubordinateNew(TObjectInfo *info, int save);

  // �������� ������� ������ ������
  // save - ���������� � ����
  //      =  0 - �� ���������, 1 - ���������
  // ���� ������ info �������� ��������� ��������� � �������� �������
  // - ��������� � �����, �� ������� ��������� ���������
  // ���� ������ info �������� ��������� ��������� � �������� �����������
  // - ��������� ��������� ��������� (������� ����� ������ �� �������� ������)
  // ���������� ���������� ����� ������� ��� 0
  int AppendGeneral(TObjectInfo *info, int save = 0);

  // �������� ������� ������ ������
  // save - ���������� � ����
  //      =  0 - �� ���������, 1 - ���������
  // ���� ������ info �������� ��������� ��������� � �������� �������
  // - ��������� ������������ ������ � ������� �����
  // ���������� ���������� ����� ������� ��� 0
  int AppendGeneralNew(TObjectInfo *info, int save);

  // ����� ������ � ������ �� ��� ������ �� �����
  TObjectInfo *Find(int number);

  // ����� ������� ������ � ������
  // group - ����� ������
  TObjectInfo *FindGeneral(long int group = 0);

  // ����� ������ � ������������� �������, ������� � ����������� ������
  // group - ����� ������
  // number - ���������� ����� ������� � ������
  TObjectInfo *FindNoEgualGroup(long int group, int *number);

  // ������������� ������� ������ � ������
  // number - ����� ������� �� �����
  // ���� number = 0, ����������� ������ ���������� ������
  int NominateGeneral(int number = 0);

  // ������� ������ �� ������ �� ����������� ������ (� 1)
  // ��������� ���������� �� ���������
  // ���� ������ ������� � ������ - ��������� ��� ������
  // save - ���������� � ����
  //      =  0 - �� ���������, 1 - ���������
  int Remove(int number, int save = 0);

  // ������� ������ �� ������ �� ��� ������ �� ����� (� 1)
  // save - ���������� � ����
  //      =  0 - �� ���������, 1 - ���������
  int RemoveNumber(int number, int save = 0);

  // ������� ������ �� ������ �� ����������� ������
  // save - ���������� � ����
  //      =  0 - �� ���������, 1 - ���������
  int RemoveKey(KEY key, int save = 0);

  // ������� ��� ������� �� ������
  // save - ���������� � ����
  //      =  0 - �� ���������, 1 - ���������
  void RemoveAll(int save = 0);

  // ������������������� ������
  void Clear();

  // ���������� ������
  // regime -
  //    = 1 -  �������� ��������� ������
  //           ���� ������ ������� - ������� ��������, ������� ������ ���
  //           � ������� �����
  //           ���� ������ ����������� ��� ������������ - �������� ��� � ������� �����,
  //           ������ �� set
  //    = 2 -  ���� �����
  //           ����������� ����� set � ��� ������� ���������� � ������� �����
  //    = 3 -  ������� ��������
  //           ����� ������� ������ ������ set � �������� ��� ��� �����������
  //           � ������� �����, ������ ��������
  // info - �� ������ ������� ������ ���������������
  // save - ���������� � ����
  //      =  0 - �� ���������, 1 - ���������
  int Union(TObjectSet *set, int regime, TObjectInfo *info,
            int save = 1);

  // ���������� ������, �������� ����� set
  int UnionWithDestroy(TObjectSet *set, int save);

  // ���������� ������, ������ �������� (������� ������� ������)
  int UnionHierarchy(TObjectSet *set, int save);

  // ������ ����� ��������
  // =====================

  // �����
  TMap *GetMap();

  // ����
  int GetListNumber();

  // ����� ������
  long int GetGroupNumber();

  // ��� ������
  // ���������� - EGUITABLE - ������ ������������ ��������
  //            - GENERAL   - ������ ��������,
  //                          ���� �� ������� �������
  //            - 0 ��� ������
  int GetGroupType();

  // ��������� ��������� ��������� ��� ���������� ������
  // groupnumber -  ����� ������
  // ���������� ������� ������� ��� 0
  int GetGroupSemn(TObjectInfo *info, long int groupnumber = 0);

  // ��������� ���������� ��������� ��������� ��� ������
  // semn -  ��� ��������� ���������
  // ���������� ����� ������ ��� 0
  long int GetGroupSemn(TObjectInfo *info, int semn);

  // ��� ������
  long int GetError() {return ErrorCode;}

  // ���������/���������� ������� �������������� ������
  int IsDirty() { return Isdirty; }
  int IsDirty(int flag) { return Isdirty = flag; }

  // ��� ��������� ������
  // groupnumber - ����������, ���� ���������� ����� ������
  //              ( ���� �� ����� )
  // ���������� ������� ������� ��� 0
  int IsObjectGroup(TObjectInfo *info, long int *groupnumber = 0);

  // ������� ������ � �����
  // ���� ������ �������� ��������� � �� ������� � ������,
  // ��������� ���������� �������� �����������
  int DeleteObject(TObjectInfo *info);


  // �������� �� ����� ��� ���������
  // ================================

  // ������� ��� ������� ������ � �����
  int Delete();

  // ������� ��������� ��������� �� �������
  // group - ����� ������
  // ���� group == 0, �� ������������ GroupNumber
  int DeleteSemantic(TObjectInfo *info, long int group = 0);

  // ������� ��� ��������� ��������� �� �������
  // group - ����� ������
  int DeleteAllSemantic(TObjectInfo *info);

  // ����������� ��� ������� ������
  // �������� ��� ���������� ������� �� ��������
  // �������� (delta) � ������ �� ���������
  // update - ��������� ������� �� ����� ��� ���
  int Move(DOUBLEPOINT * delta, int update = 0);

  // ����������� ��� ������� ������
  // �������� ��� ���������� ������� �� ��������
  // �������� (delta)
  // ������� ������� ���������� ��� ����� ����� (Site ��� Map)
  int MoveData(DOUBLEPOINT *delta);

  // ��������� ��� ������� ������ ��������� � �������������
  // ������� X,Y (� �.)  ������ ( center )
  // �� �������� ���� ( anglevalue ).
  // ���� �������� � �������� � ����� ��������� ��������:
  // �� 0 �� PI � �� 0 �� -PI ���
  // �� 0 �� PI � �� 0 �� 2PI
  // ��� ������ ���������� 0
  int Rotate(DOUBLEPOINT *center,double anglevalue,
             int update = 0);

  // ��������� ��� ������� (��������� ��� ���������� �������)
  // ������ ��������� � �������������
  // ������� X,Y ������ ( center )
  // �� �������� ���� ( anglevalue ).
  // ����� � ������� ������ ���� � ����� ������� �������.
  // ���� �������� � �������� � ����� ��������� ��������:
  // �� 0 �� PI � �� 0 �� -PI ���
  // �� 0 �� PI � �� 0 �� 2PI
  // ������� ������� ���������� ��� ����� ����� (Site ��� Map)
  // ��� ������ ���������� 0
  int RotateData(DOUBLEPOINT *center,double anglevalue);

  // ��������������(factor) ��� ������� ������
  // factor - �����������
  // deltanull - �������� ������������ 0
  // ��� ������ ���������� ����
  int ScopeData(DOUBLEPOINT *factor, DOUBLEPOINT *deltanull);

  // ��������������(factor) � ��������(delta)
  // ��� ������� ������
  // factor - �����������
  // deltanull - �������� ������������ 0
  // delta - ��������������� ��������
  // ��� ������ ���������� ����
  int ScopeAndRelocateData(DOUBLEPOINT *factor,
                           DOUBLEPOINT *deltanull,
                           DOUBLEPOINT *delta);

  // ������������ ������� ������ �� �����
  // ����� �������� ��������, �����������
  int Revert();

  // ��������� ������
  // always - ��������� ������ ��� ������, ���� ���� ���������
  //        = 0 - ���� ���������
  //        = 1 - ������
  int Save(int always = 0);

  // ��������� ������ �������� �� ������ �����  
  // ��� �������� ������� ����������� ������ ����������� ����  
  // ��� ������ ��������������, ���� ��� �� ������ -  
  // �� ��������������� � ����  
  // ������� ������������� � ������������ � ����� �����
  // map - �����
  // AutoCorrect - �������������� ��������� ������ ������
  // list - ����� �����
  // ��� ������ ���������� ���� 
  // � ������ ����� ���������� ���������� ������������� ��������
  int ChangeMap(TMap * map, const int AutoCorrect = 0, const int list = 1);
  
  // ���������� ����� ������
  // newGroupNumber - ����� ����� ������:
  //   0 - ������������ ����� �������� �������(������ � ������� �������)
  //     - ������ ���������� �����(������ � ������������� ��������)
  // ��� ������ ���������� ����
  int SetGroupNumber(const int newGroupNumber = 0);

  // �������� �����������
  // ====================

  // �������� ������
  int PaintGroup(TMapAccess *doc, HDC hDC,
                 RECT& rect, COLORREF color = RGB(0x0,0xFF,0xFF),
                 int thick = 2);

protected:

  // ������� ������������� � ���������������
  // =======================================

  // ���������������� ������ ������
  void InitObjectChain();

  // ���������������� ����� �������
  // ���������� ����� ���������� ��� ������ ����� ��� 0
  OBJECTCHAIN *InitSectionChain();

  // �������� ���������� ������
  void InitVariable();

  // ���������� ������
  void FreeMemory();

  // �������� ������
  // dirty - ��������� ��������� ��� ���
  // ���������� ���������� ����� ������� ��� 0
  int Append(TObjectInfo *info, int dirty = 0);

  // ��������� ����� ����� � ������� �� ������ ������� (� 1)
  // objchain - ���������� ����� ������� � �������
  // objsection - ���������� ����� ������� � �����
  // ���������� ����� ����� � ������� ��� 0
  int GetSectionNumber(int objchain, int *objsection);

  // ��������� ����� ������� �� ������ ����� � ������� (� 1)
  // ���������� ����� ����� ��� 0
  OBJECTCHAIN *GetSection(int number);

  // ������ ������� �������� � ������
  TObjectInfo *GetFirst();

  // ������ ���������� �������� � ������
  TObjectInfo *GetNext();

  // ������� ������ �� ������
  // ��������� ���������� �� ���������
  // ���� ������ ������� � ������ - ��������� ��� ������
  // save - ���������� � ����
  //      =  0 - �� ���������, 1 - ���������
  int Remove(TObjectInfo *info, int save = 0);

  // �������� �� ����� ��������� �� ������ �������,
  // ���� ��� �� ����� ������
  int UpdateDeleteObject();

  // �������� �� ����� ��������� �������� ������
  // ��� ���������� ������ ��� �������� �������� �������
  // info - ������� ������
  int UpdateSemantic(TObjectInfo *info, long int grnumber = 0);
  
protected:

  // �������� ������� �������(��� �������������� ������)
  DOUBLEPOINT Delta;
  DOUBLEPOINT Center;
  double Angle;

  long int GroupNumber;             // ����� ������
  long int ErrorCode;               // ��� ������

  int          ObjectChainCount;    // ���������� �������
  OBJECTCHAIN *ObjectChainBegin;    // ������ ����� �������
  int          ObjectCountAll;      // ����� ����� �������� � �������

  TMap *Map;                        // �����
  int  ListNumber;                  // ����� �����
  int  GroupType;                   // ��� ������
  int  FlagGeneralObject;           // ������� � ������ ��������
                                    // �������, ���� ��� ������ GENERAL

  TObjectInfo InfoBuild;            // ������, � �������� ��������
                                    // ���������� ������ (Build(TObjectInfo *info))
  int FlagDeleteObject;             // ������� � ������ ��������� ��������

  OBJECTCHAIN *ObjectChainCurrent;  // ������� ����� �������
  int          ObjectNumberCurrent; // ������� ������ � ������� ����� �������
  int          FlagFirst;           // ���������� ������� �������
                                    // ������� ������� � ������

  // ������� �������������� ������
  int Isdirty;

  int Reserv;

};

#endif  // __cplusplus

#endif  // MAPSET_H
