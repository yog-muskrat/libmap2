
#if !defined(MAPHDR_H)
#define MAPHDR_H

#ifndef MAPMACRO_H
  #include "mapmacro.h"
#endif

#ifndef MAPDATA_H
  #include "mapdata.h"
#endif

#ifndef MAPSEM_H
  #include "mapsem.h"
#endif

typedef long int OBJID;

// ������������� ��'���� ����������� �����
// (���������� ����� ������� � �������� �����)

typedef struct _DLLCLASS KEY
{
#ifdef __cplusplus  
  union
  {
   struct
   {
   unsigned short int Member;   // ����� � ��'�������� ��'�����
   unsigned short int Union;    // ����� ��'�������� ��'�����
   }
    shortkey;

   ULONG longkey;
  };
#else
  unsigned long longkey;  
#endif // __cplusplus

#ifdef __cplusplus

  KEY() {}

  KEY(int _union,int _member)
   {
     shortkey.Union  = (unsigned short) _union;
     shortkey.Member = (unsigned short) _member;
   }

  KEY(long int key)
   {
     longkey = (ULONG)key;
   }

  KEY(const KEY& key)             
   {
     longkey = key.Long();
   }

  unsigned long Long() const { return longkey; } 

  int operator != (unsigned long int key)
   {
     return (longkey != key);
   }

  int operator == (unsigned long int key)
   {
     return (longkey == key);
   }

  int operator > (KEY key)
   {
     return (longkey > key.Long());
   }

  int operator < (KEY key)
   {
     return (longkey < key.Long());
   }

  KEY operator = (unsigned long int key)
   {
     longkey = key;
     return *this;
   }

#endif  // __cplusplus
}
  KEY;

#ifdef  __cplusplus  
class TMapRsc;
#endif  // __cplusplus

// ������������� ��������� �������
// ��� ������ ���������� ����
int odRegisterDesc(TObjectHead * head, long excode, int local,
                   void * maprsc, SEMANTIC *semn);                  

int odRegisterDescRsc(TObjectHead * head, int incode, void * maprsc); 

int odInit(TObjectHead * head);

//  ���������� ����������� ��������
int odDatKind(TObjectHead * head,int ident);

// ��������� ����������� �������
// 2-�� ��� 3-�� ������
int odDatDimension(TObjectHead * head, int dim);

// ��������� ����������� �����������
int odExtLoc(TObjectHead * head, const int extloc);

// ��������� ��������� ������ ���������
int odIsBotTop(TObjectHead * head, int mode);

// ��������� �������� ����������������
int odScale(TObjectHead * head, const int scale);

// ��������� �������� ������
int odPress(TObjectHead * head, const int press);

// ��������� ������� ������� ���������
int odSetTop(TObjectHead * head,const int top);

// ������ ������� ������� ���������
int odTop(TObjectHead * head);

// ��������� �������� ��������
int odCancel(TObjectHead * head, const int cancel);

// ��������� - ��������� ����������� ��� ����������� �����
int odGetObjExtsem(TObjectHead * head, void * maprsc);

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  �������� ��'���� ����������� �����  ++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifdef __cplusplus
class _DLLCLASS TObjectDesc         // *************
{                                   // ** OBJECT ***
 public :                           // *************

  TObjectDesc(TObjectHead * head) { Base = head; }
  TObjectDesc() { Base = 0; }

  // ���� ���������� �����������  TObjectDesc::LINE ...
  enum LOCAL { LINE = 0, SQUARE = 1, POINT = 2, TITLE = 3,
               VECTOR = 4, MIXED = 5 };

  // ������ ������ ����������� ��������� � �������
  int Back()
  {
#ifndef TINYDATA
    if (Base == 0) return 0;
    return Base->Back;
#else
    return 0;
#endif
  }

  // ������ � ��������� ������ ������� ���������
  int Bot(const int bot)
  {
    if (Base == 0) return 0;
    return (Base->Bot = (unsigned short)bot);
  }

  int Bot()
  {
    if (Base == 0) return 0;
    return (Base->Bot);
  }

  // ������ � ��������� �������� ��������
  int Cancel(const int cancel);

  int Cancel()
  {
#ifndef TINYDATA
    if (Base == 0) return 0;
    return (Base->Cancel);
#else
    return 0;
#endif
  }

  // �������� ���������� ��������� (��� ���� � ����)
  // ��� ������ ���������� 0.
  int Clear();

  // ������ � ��������� ���� �������
  int Code(const int code)
  {
    if (Base == 0) return 0;
    return (Base->Code = (unsigned short)code);
  }

  int Code()
  {
    if (Base == 0) return 0;
    return (Base->Code);
  }

  // ������ � ��������� ����������� �������
  // 2-�� ��� 3-�� ������
  int DatDimension()
  {
#ifndef TINYDATA
    if (Base == 0) return 0;
    return (Base->Dimension);
#else
    return 0;
#endif
  }

  int DatDimension(int dim);

  // ��������� ���� � ������� �������
  // TObjectData::KIND (IDSHORT2,IDLONG2, ...)
  int DatKind(int ident);

  // ������ � ��������� ������ ������
  int Group(const int group)
  {
#ifndef TINYDATA
    if (Base == 0) return 0;
    return (Base->Group = (unsigned short)group);
#else
    return 0;
#endif
  }

  int Group()
  {
#ifndef TINYDATA
    if (Base == 0) return 0;
    return (Base->Group);
#else
    return 0;
#endif
  }

  // ������ �������������� ������������ �������� �������
  long int Graphic()
  {
#ifndef TINYDATA
    if (Base == 0) return 0;
    return (Base->Graphic);
#else
    return 0;
#endif
  }

  // ������ � ��������� ����������� �����������
  int ExtLoc(const int extloc);

  int ExtLoc()
  {
#ifndef TINYDATA
    if (Base == 0) return 0;
    return (Base->Extloc);
#else
    return 0;
#endif
  }

  // ������ �������������� ������� ������
  FVSPR * Ident() const { return Base; }

#ifndef TINYDATA
  // ������/��������� ��������� ������ ���������
  int IsBotTop()
  {
    if (Base == 0) return 0;
    return (Base->IsBotTop);
  }

  int IsBotTop(int mode);

  // ������ � ��������� ������ �������
  long int Key()
  {
    if (Base == 0) return 0;
    return (Base->BaseKey);
  }

  long int Key(long int key)
  {
    if (Base == 0) return 0;
    return (Base->BaseKey = key);
  }

  KEY Key(KEY key)
  {
    if (Base == 0) return 0;
    return (KEY)(Base->BaseKey = key.longkey);
  }

  // ������ ��������� �������� ������� ������� �������� 3D-������  
  int IsVector3D()
  {
    if (Base == 0) return 0;
    return (Base->Vector);
  }
  
  int IsVector3D(int vector)
  {
    if (Base == 0) return 0;
    return (Base->Vector = (vector != 0));
  }
#endif

  // ������ ����� ������ ���������� ������
  int Length() const { return sizeof(FVSPR); }

  // ���������� �������� �������� ������� �� ���������
  void Load(TObjectDesc desc);

  // ������ � ��������� ��������� �����������
  int Local(const int local)
  {
    if (Base == 0) return 0;
    return (Base->Local = (unsigned short)local);
  }

  int Local()
  {
    if (Base == 0) return 0;
    return (Base->Local);
  }

  // ������ ������ ���������� ��������� � �������
  int Next()
  {
#ifndef TINYDATA
    if (Base == 0) return 0;
    return Base->Next;
#else
    return 0;
#endif
  }

  // ������ �������������� ������� �������
  long Metric()
  {
    if (Base == 0) return 0;
    return (Base->Metric);
  }

  // ������������� ��������� �������
  // ��� ������ ���������� ����
  int RegisterDesc(long excode, int local,
                   TMapRsc * maprsc, TObjectSemn semn);

  int RegisterDesc(int incode,TMapRsc * maprsc);


#ifndef TINYDATA
  // ������ � ��������� �������� ����������������
  int Scale()
  {
    if (Base == 0) return 0;
    return (Base->ScaleFlag);
  }

  // ������ � ��������� �������� ������
  int Press()
  {
    if (Base == 0) return 0;
    return (Base->PressFlag);
  }
#endif

  int Scale(const int scale);

  int Press(const int press);

  // ������ � ��������� ������ ����
  int Segment(const int segment)
  {
    if (Base == 0) return 0;
    return (Base->Segment = (unsigned short)segment);
  }

  int Segment()
  {
    if (Base == 0) return 0;
    return (Base->Segment);
  }

#ifndef TINYDATA
  // ������ �������������� ��������� �������
  long Semantic()
  {
    if (Base == 0) return 0;
    return (Base->Semantic);
  }
#endif

  // ������ � ��������� ������� ������� ���������
  int Top(const int top);

  int Top();

  // ������ � ��������� ��������� �������
  long int X1(long int x)
  {
    if (Base == 0) return 0;
    return (Base->X1 = x);
  }

  long int X1()
  {
    if (Base == 0) return 0;
    return (Base->X1);
  }

  long int Y1(long int y)
  {
    if (Base == 0) return 0;
    return (Base->Y1 = y);
  }

  long int Y1()
  {
    if (Base == 0) return 0;
    return (Base->Y1);
  }

  long int X2(long int x)
  {
    if (Base == 0) return 0;
    return (Base->X2 = x);
  }

  long int X2()
  {
    if (Base == 0) return 0;
    return (Base->X2);
  }

  long int Y2(long int y)
  {
    if (Base == 0) return 0;
    return (Base->Y2 = y);
  }

  long int Y2()
  {
    if (Base == 0) return 0;
    return (Base->Y2);
  }

  TObjectDesc operator = (TObjectHead * Ident)
      {
         Base = Ident;
         return(*this);
      }

  TObjectDesc operator = (char * Ident)
      {
         Base = (FVSPR *) Ident;
         return(*this);
      }

  TObjectDesc operator = (TObjectDesc desc)
      {
         Base = (FVSPR *) desc.Ident();
         return(*this);
      }

  int operator == (FVSPR * Ident)
     {
        return ( Base == Ident );
     }

  int operator != (FVSPR * Ident)
     {
        return ( Base != Ident );
     }

  int operator != (TObjectDesc desc)
     {
        return ( Base != desc.Ident() );
     }


  FVSPR * Base;
};

#else

typedef struct TObjectDesc
{
  FVSPR * Base;
}
 TObjectDesc;

#endif  // __cplusplus


#endif

