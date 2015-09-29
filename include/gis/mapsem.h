
#if !defined(MAPSEM_H)
#define MAPSEM_H


#ifndef SEMDEF_H
  #include "semdef.h"
#endif

#ifndef MAPMACRO_H
  #include "mapmacro.h"
#endif

#define SEMIDENT 0x7FFF      // ������������� ������ ������ 
#define SEMIDENT_TURN 0xFF7F // ������������� ������ �������������� ������

typedef struct SEMANTIC       // ��������� ��'����
{
  unsigned short int Ident;   // 0x7FFF
  unsigned short int Length;  // ����� ������
}
  SEMANTIC;

typedef enum SEMVTYPE // ���� �������������
{
  SEMVSTRDOS = 0,     // C����� �������� (ASCIIZ),������������ �����
  SEMVSTRING = 126,   // C����� �������� (ANSI),������������ �����
  SEMVSTRUNI = 127,   // C����� �������� (UNICODE),������������ �����
  SEMVCHAR   = 1,     // 1 ����   SIGNED CHAR
  SEMVSHORT  = 2,     // 2 ����A  SIGNED SHORT
  SEMVLONG   = 4,     // 4 ����A  SIGNED INT
  SEMVDOUBLE = 8      // 8 ����   DOUBLE IEEE
}
  SEMVTYPE;

typedef struct _DLLCLASS SEMANTICDATA
{
 SEMANTICDATA() : Work() { Base = 0; Memory = 0; }

 SEMANTIC *    Base;     // ��������� �� ��������� (���������� �����)
 char     *    Memory;   // ������ ��������� ������ � �����������
                								 // (���� != 0, ����������)
 TWorkSemantic Work;     // �������� ������ ���������
}
  SEMANTICDATA;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  ��������� ��'���� ����������� �����  +++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TObjectSemn
{                         // ***********
                          // ** SEMN ***
 public :                 // ***********

  TObjectSemn(SEMANTIC * Addr)
   {
     Base = Addr;
   }

  TObjectSemn(char HUGER * Addr)
   {
     Base = (SEMANTIC *)Addr;
   }

  TObjectSemn(const int Addr)
   {
     Base = (SEMANTIC *)Addr;
   }

  TObjectSemn()
  {
    Base = 0L;
  }

  // ��������� ����� ������
  char * Address()
   {
     return (char *)Base;
   }

  // ������������������� ������ ��������
  // ���������� ������������� ������ � �����
  // ��� ������ ���������� 0, ��� ����� 1
  int Clear()
  {
    if (Base == 0) return 0;
    Base->Ident   = SEMIDENT;
    Base->Length  = sizeof(SEMANTIC);
    return 1;
  }

  int Create() { return Clear(); }  // ��������

  // ��������� ����� ������
  int DataLength()
   {
     if (!IsCorrect()) return 0;
     return (Base->Length - sizeof(SEMANTIC));
   }

  // ��������� ������������ ������ ������
  int IsCorrect()
   {
     if (Base == 0) return 0;
     return (Base->Ident == SEMIDENT);
   }

  // ��������� ����� ������
  int Length()
   {
     if (!IsCorrect()) return 0;
     return Base->Length;
   }


  SEMANTIC * operator = (SEMANTIC * Addr)
   {
     return(Base = Addr);
   }

  int operator == (intptr_t value)
   {
     return((intptr_t)Base == value);
   }

  int operator != (intptr_t value)
   {
     return((intptr_t)Base != value);
   }

 protected :

  // ���������� ����� ������
  int Length(int length)
   {
     if (Base == 0) return 0;
     return (int)(Base->Length = (unsigned short int)length);
   }

 public :

 SEMANTIC *  Base;  // ��������� �� ��������� (���������� �����)

};

#define SEMNBUFFERSIZE (4*1024L)  // ����������� ������ ������ C��������

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++ �������������� ��������� ��'���� ����������� �����  ++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TSemnEdit : public SEMANTICDATA
{
 public :

  // ���� �������������
  typedef enum type
   {
     STRDOS = SEMVSTRDOS, // C����� �������� (ASCIIZ),������������ �����
     STRING = SEMVSTRING, // C����� �������� (ANSI),������������ �����
     STRUNI = SEMVSTRUNI, // C����� �������� (UNICODE),������������ �����
     CHAR   = SEMVCHAR,   // 1 ����   SIGNED CHAR
     SHORT  = SEMVSHORT,  // 2 ����A  SIGNED SHORT
     LONG   = SEMVLONG,   // 4 ����A  SIGNED INT
     DOUBLE = SEMVDOUBLE  // 8 ����   DOUBLE IEEE
   }
     TYPE;

   TSemnEdit() : SEMANTICDATA()
     {
       Access(0,0,0);
     }


   // ���������� ������ � ��������� �������
   TSemnEdit(char HUGER * begin) : SEMANTICDATA()
     {
       Access(begin);
     }

   TSemnEdit(TObjectSemn semn) : SEMANTICDATA()
     {
       Access(semn.Address(),semn.Length());
     }

   // ���������� ������ � ��������� �������
   TSemnEdit(char HUGER * begin,     // ������ ���������
             long lengthsemantic,    // ����� ����� ���������
             long lengthbuffer = 0)  // ����� ����� ������
           : SEMANTICDATA()
     {
       Access(begin,lengthsemantic,lengthbuffer);
     }

   ~TSemnEdit() { Access(0,0,0); }

   int Access(TObjectSemn semn)
     {
       return Access(semn.Address(),semn.Length());
     }

   int Access(char HUGER * begin,     // ������ ���������
              long lengthsemantic,    // ����� ����� ���������
              long lengthbuffer = 0); // ����� ����� ������


  // ��������� ����� ������
  char * Address() { return (char *)Base; }

  // �������� ������ ��� ����������� ������ ���������
  // ������������������� ��������� ������
  // ��������� ������������� ������
  // ������ ������������� ������������� � �����������
  // ��� ��� ���������� ������ ������� � �������
  // SetBuffer(...), � ��� �����, SetBuffer(0,0).
  // ��� ������ ���������� ����
  int Allocate(int length = SEMNBUFFERSIZE);

  // �������� �������������� (� ����� ���������)
  // type    - �������������� ��� �������� (TYPE)
  // code    - ��� ���������
  // place   - ����� ������,���������� �������� ���������
  // maxsize - ����� ������
  // ��� ������ ���������� ����
  TSemBlock * Append(int code,char * place,int maxsize,int type = STRING)
   {
     TSemBlock newblock;
     newblock.Code(code);
     if (newblock.Value(type,place,maxsize) == 0)
       {
         return 0;
       }
     return Append(&newblock);
   }

  TSemBlock * Append(int code, long int value);

  // �������� �������������� (� ����� ���������)
  // ��� ������ ���������� ����
  TSemBlock * Append( TSemBlock * block);

  // ��������� �������� ����� ������
  // � ���������� ����� �������� (�������� ��������� ������)
  // correct - ������� ������������� ������������� �����
  //           ������ ��������� �� ������� ������������
  // ��� ������ ���������� ����
  int CheckLength(int correct = TRUE);

  // ������������������� ������ ��������
  // ���������� ������������� ������ � �����
  // ��� ������ ���������� 0, ��� ����� 1
  int Clear()
   {
     if (Base == 0) return Allocate();
     Work.Length(0);
     Base->Ident   = SEMIDENT;
     Base->Length  = sizeof(SEMANTIC);
     return 1;
   }

  int Create() { return Clear(); }  // ��������

  // ��������� ���������������� ����� ������� ��������������
  int CurrentNumber() { return Work.Number; }

  // ��������� ����� ������ � ������
  int DataLength()
   {
     if ((Base == 0) || (Base->Ident != SEMIDENT)) return 0;
     int length = Base->Length;
     if (length > sizeof(SEMANTIC))
       return (length-sizeof(SEMANTIC));
     else
       return 0;
   }

  // ������� ������� ��������������
  // ����� �������������� - ��. TWorkSemantic
  int Delete()
   {
     int ret;
     if (Base == 0) return 0;
     ret = Work.Delete();
     Base->Length = (unsigned short)(sizeof(SEMANTIC) + Work.Length());
     return ret;
   }

  // �������� �������������� (����� ������� ������ )
  // ��� ������ ���������� ����
  TSemBlock * Insert( TSemBlock * block)
   {
     if ((block && Base) == 0) return 0;
     TSemBlock * newblock;
     newblock = Work.Insert(block);
     Base->Length = (unsigned short)(sizeof(SEMANTIC) + Work.Length());
     return newblock;
   }

  // ��������� ������������ ��������� ������
  int IsCorrect()
   {
     return ((Base && Base->Ident == SEMIDENT) &&
             (DataLength() == Work.Length()));
   }

  // ��������� ������� �������������� ������
  int IsDirty() { return Work.IsDirty(); }

  // ���������� ������� �������������� ������
  int IsDirty(int dirty) { return Work.IsDirty(dirty); }

  // ��������� ��� ������� �� ��������� ���������
  // ��� ������ ���������� ����
  long int GetObjectExcode();

  // ��������� ��� ������� �� ��������� ���������
  // � ������� �������������� �� ���������
  // ��� ������ ���������� ����
  long int GetObjectExcodeAndDelete();

  // ������� �� ������ ��������������
  TSemBlock * GoFirst()
  { return Work.GoFirst(); }

  // ������� �� ��������� �������������� �� ��� ������������
  // ��� ������ ���������� ����
 	TSemBlock * GoNext()
  { return Work.GoNext(); }

  // ������� �� �������������� � ���������� ������� number
  // ��� ������ ���������� ����
  TSemBlock * GoNumber(int number)
  { return Work.GoNumber(number); }


  // ����� �������������� �� ���� ���������
  // ��� ������ ���������� ����
  TSemBlock * FindCode(int code)
  { return Work.FindCode(code); }

  // ��������� ��� ������� � ��������� ���������
  // ��� ������ ���������� ����
  int PutObjectExcode(long int);

  // ��������� ������ ����� ������
  int Length()
   { if (Base && Base->Ident == SEMIDENT)
       return Base->Length;
     return 0;
   }

  // ��������� ������ ��������� �� �������� �������
  // ��� ������ ���������� ����
  // ��� �������� ���������� - ������ ����������� ������
  int Load(TObjectSemn semn);

  // ��������� ����� ������������� �������������
  // �� �������� �������
  // ��� ������ ���������� ����
  // ��� �������� ���������� - ������ ��������� ������
  int Load(TWorkSemantic * worksemn);

  // �������� ��� �������������� � �������� �����
  // ��� ������ ���������� ����
  TSemBlock * ReplyCode(int code)
  { return Work.ReplyCode(code); }

  // �������� �������� �������������� � �������� �����
  TSemBlock * ReplyValue(char * value,int maxsize)
  { return Work.ReplyValue(value, maxsize); }

  // ���������� �������� ������ ���������
  char * SetBuffer(char * address,long int length)
   {
     Access(address,0,length);
     return address;
   }

  // ��������� �������� �������������� � ���������� ���� (ANSI)
  // number - ���������������� ����� ��������������,
  // place - ����� ���������� ������,
  // maxsize - ������������ ����� ������
  // ��� ������ ���������� ����,
  // ��� �������� ���������� - ����� ������ (����� place)
  char * StringValue(int number,char *place,int maxsize)
  { return Work.StringValue(number, place, maxsize); }

  
  // �������� ������� ��������������
  // ��� ������ ���������� ����
  TSemBlock * Update(TSemBlock * block)
   {
     if ((block && Base) == 0) return 0;
     TSemBlock * newblock;
     newblock = Work.Update(block);
     Base->Length = (unsigned short)(sizeof(SEMANTIC) + Work.Length());
     return newblock;
   }

  // ������������� ��������
  SEMANTIC * operator = (SEMANTIC * begin)
   {
     Access((char *)begin);
     return Base;
   }

  int operator == (intptr_t value)
   {
     return (int)((intptr_t)Base == value);
   }

  int operator != (intptr_t value)
   {
     return (int)((intptr_t)Base != value);
   }

  operator TObjectSemn()
   {
     return Base;
   }
};


// ������������� ������ �� ���������
void _fastcall sedInit(SEMANTICDATA *semndata);

// ���������� ������
void _fastcall sedFree(SEMANTICDATA *semndata);

// �������� ������ ��� ������������ ������ ���������
// ������������������� ��������� ������
// ��������� ������������� ������
// ������ ������������� ������������� � �����������
// ��� ��� ���������� ������ ������� � �������
// Access(...)��� SetBuffer(...), � ��� �����, SetBuffer(0,0).
// ��� ������ ���������� ����
int _fastcall sedAllocate(SEMANTICDATA *semndata, int length);

//  ���������� ������ � ��������� �������
int _fastcall sedAccess(SEMANTICDATA *semndata,
                        char HUGER * begin,   // ������ ���������
                        long lengthsemantic,  // ����� ����� ���������
                        long lengthbuffer);   // ����� ����� ������

// ��������� ������ ��������� �� �������� �������
// ��� ������ ���������� ����
// ��� �������� ���������� - ������ ����������� ������
int _fastcall sedLoad(SEMANTICDATA *semndata, SEMANTIC * semn);

// ��������� ����� ������������� �������������
// �� �������� �������
// ��� ������ ���������� ����
// ��� �������� ���������� - ������ ��������� ������
int _fastcall sedLoadWorkSemn(SEMANTICDATA *semndata,
                              WORKSEMANTIC * worksemn);

// �������� �������������� (� ����� ���������)
// type    - �������������� ��� �������� (TYPE)
// code    - ��� ���������
// place   - ����� ������,���������� �������� ���������
// maxsize - ����� ������
// ��� ������ ���������� ����
TSemBlock * _fastcall sedAppend(SEMANTICDATA *semndata,
                                int code,const char * place,int maxsize,
                               	int type);

// �������� �������������� (� ����� ���������)
// ��� ������ ���������� ����
TSemBlock * _fastcall sedAppendSemn(SEMANTICDATA *semndata,
                                    TSemBlock * block);

// �������� �������� �������������� (� ����� ���������)
// ��� ������ ���������� ����
TSemBlock * _fastcall sedAppendLongValue(SEMANTICDATA *semndata,
                                         int code, long int value);

// �������� �������� �������������� (� ����� ���������)
// ��� ������ ���������� ����
TSemBlock * _fastcall sedAppendDoubleValue(SEMANTICDATA *semndata,
                                           int code, double * value);

// ��������� ��� ������� �� ��������� ���������
// ��� ������ ���������� ����
long int _fastcall sedGetObjectExcode(SEMANTICDATA *semndata);

// ��������� ��� ������� �� ��������� ���������
// � ������� �������������� �� ���������
// ��� ������ ���������� ����
long int _fastcall sedGetObjectExcodeAndDelete(SEMANTICDATA *semndata);

// ��������� ��� ������� � ��������� ���������
// ��� ������ ���������� ����
ptrdiff_t _fastcall sedPutObjectExcode(SEMANTICDATA *semndata, long int code);

// ��������� �������� ����� ������
// � ���������� ����� �������� (�������� ��������� ������)
// correct - ������� ������������� ������������� �����
//           ������ ��������� �� ������� ������������
// ��� ������ ���������� ����
int _fastcall sedCheckLength(SEMANTICDATA *semndata, int correct);

// ������������������� ������ ��������
// ���������� ������������� ������ � �����
// ��� ������ ���������� 0, ��� ����� 1
int _fastcall sedClear(SEMANTICDATA *semndata);

// ��������� ����� ������ � ������
int _fastcall sedDataLength(SEMANTICDATA *semndata);

// ������� ������� ��������������
// ����� �������������� - ��. TWorkSemantic
int _fastcall sedDelete(SEMANTICDATA *semndata);

// �������� �������������� (����� ������� ������ )
// ��� ������ ���������� ����
TSemBlock * _fastcall sedInsert(SEMANTICDATA *semndata, TSemBlock * block);

// �������� ������� ��������������
// ��� ������ ���������� ����
TSemBlock * _fastcall sedUpdate(SEMANTICDATA *semndata, TSemBlock * block);

// ��������� �������� ������������� �������������� � ���������� ����
// ��� ������ ���������� ����
char * _fastcall sedGetStringValue(SEMANTICDATA *semndata, int code,
                                   char * place, int size);

#endif  // MAPSEM_H


