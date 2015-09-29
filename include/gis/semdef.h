
#if !defined(SEMDEF_H)
#define SEMDEF_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#if (!defined(QNX) && !defined(OC2000))  
#ifndef MEMORY_H
  #include <memory.h>
  #define MEMORY_H
#endif
#endif

// --------------------------------------------------------
//  ����������� ����� ���� "���������"
// --------------------------------------------------------
typedef struct SEMCHAR
{
  unsigned char Type;        // ��� ��������������
  signed char  Scale;        // ���������� �����������
  signed char  Value;        // �������� ��������������
}
  SEMCHAR;

typedef struct SEMSHORT
{
  unsigned char Type;        // ��� ��������������
  signed char  Scale;        // ���������� �����������
  signed short Value;        // �������� ��������������
}
  SEMSHORT;

typedef struct SEMLONG
{
  unsigned char Type;        // ��� ��������������
  signed char  Scale;        // ���������� �����������
#ifndef RISCCPU
  ::LONG     Value;        // �������� ��������������
#else
  char      Value[4];        // �������� ��������������
#endif
}
  SEMLONG;

typedef struct SEMDOUBLE
{
  unsigned char Type;        // ��� ��������������
  signed char  Scale;        // ���������� �����������
#ifndef RISCCPU
  double       Value;        // �������� ��������������
#else
  char      Value[8];        // �������� ��������������
#endif
}
  SEMDOUBLE;

typedef struct SEMSTRING
{
  unsigned char Type;        // ��� ��������������
  unsigned char  Scale;      // ���������� �����������
     char   Value[256];      // �������� ��������������
}
  SEMSTRING;

typedef struct SEMWSTRING    
{
  unsigned char Type;        // ��� ��������������
  signed char  Scale;        // ���������� �����������
#ifndef RISCCPU              
  wchar_t Value[128];        // �������� �������������� � UNICODE  
#else
  char    Value[128 * 2];    // �������� �������������� � UNICODE  
#endif
}
  SEMWSTRING;

typedef union AnySemantic    // ����� ���� ���������
{
  SEMWSTRING WString;
  SEMSTRING  String;
  SEMCHAR    Char;
  SEMSHORT   Short;
  SEMLONG    Long;
  SEMDOUBLE  Double;
}
  SEMBASE;

// ���� �������������
typedef enum sembasetype
{
  SEMBASESTRDOS = 0,   // C����� �������� (ASCIIZ),������������ �����
  SEMBASESTRING = 126, // C����� �������� (ANSI),������������ �����
  SEMBASESTRUNI = 127, // C����� �������� (UNICODE),������������ �����
  SEMBASECHAR   = 1,   // 1 ����   SIGNED CHAR
  SEMBASESHORT  = 2,   // 2 ����A  SIGNED SHORT
  SEMBASELONG   = 4,   // 4 ����A  SIGNED INT
  SEMBASEDOUBLE = 8    // 8 ����   DOUBLE IEEE
}
  SEMBASETYPE;


//********************************************************************
//        ������������� ���������� ������ TSemBase                   *
//********************************************************************

// ��������� ���������� Sembase
#define sbsInit(sembase) memset((void*)sembase, 0 , sizeof(SEMBASE));

//********************************************************************
//       ���������� ������� ������ TSemBase                          *
//********************************************************************

// ���������� �������� ��������������
long int _fastcall sbsPutLongValue(SEMBASE * sembase, long int value);

// ���������� �������� ��������������
double _fastcall sbsPutDoubleValue(SEMBASE * sembase, double value);

//  ���������� �������� ��������������
//  ������ ������ ���� � ����� ANSI (��� Windows) ��� KOI8 (��� UNIX)
//  �� ������������� �������� ���, ��� �������� ��� �������
char * _fastcall sbsPutStringValue(SEMBASE * sembase,
                                   const char * value, int maxsize);

// ������ �������� �������������� � �������� ����
int _fastcall sbsGetLongValue(SEMBASE * sembase);

// ������ �������� �������������� � �������� ����
double _fastcall sbsGetDoubleValue(SEMBASE * sembase);

//  ������ �������� �������������� � ���������� ����
char * _fastcall sbsGetStringValue(SEMBASE * sembase,
                                   char * Place, int MaxSize);

//  C������� ������� �������������� � ��������
HOW _fastcall sbsCompare(SEMBASE * sembase, SEMBASE * base);

//  �������������� ������ �������� �� ANSI � ASCII (DOS)
//  ���� �������� �������������� �� ���������� - ���������� ����
char * _fastcall sbsStringInDos(SEMBASE * sembase);

//  �������������� ������ �������� �� ASCII (DOS) � ANSI
//  ����������� ������������� ��� ��������� � ������
//  ���� �������� �������������� �� ���������� - ���������� ����
char * _fastcall sbsStringInAnsi(SEMBASE * sembase);

//  ������������� ������ � ����� ���� "���������"
//  � ������������ � ����� �������������� (TYPE)
//  ��� ������ ���������� ����
int _fastcall sbsLoadAnyString(SEMBASE * sembase, int type,
                               const char * string, int maxsize);

//  ������� ������,(������������ �����) � ����� ���� "���������"
//  ������� - ���������� ��������� ���������������
//  ��������, ����� �.�. ���������
int _fastcall sbsLoadStringNumber(SEMBASE * sembase,const char * str);

//  ��������� ����� ���� ���������
void _fastcall sbsLoadSemBase(SEMBASE * sembase,SEMBASE * sembaseval);

// ��������� ����� �������� ��������������
unsigned int _fastcall sbsGetLength(SEMBASE * sembase);


#ifdef __cplusplus

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++      ������ ������� � ������ ���� ���������     ++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct _DLLCLASS TSemBase
{
public :

  // ���� �������������
  typedef enum type
   {
     STRDOS = SEMBASESTRDOS, // C����� �������� (ASCIIZ),������������ �����
     STRING = SEMBASESTRING, // C����� �������� (ANSI),������������ �����
     STRUNI = SEMBASESTRUNI, // C����� �������� (UNICODE),������������ �����
     CHAR   = SEMBASECHAR,   // 1 ����   SIGNED CHAR
     SHORT  = SEMBASESHORT,  // 2 ����A  SIGNED SHORT
     LONG   = SEMBASELONG,   // 4 ����A  SIGNED INT
     DOUBLE = SEMBASEDOUBLE  // 8 ����   DOUBLE IEEE
   }
     TYPE;


  // ��������� ����� ������ ���� ���������, ���� ����������� �����
  TSemBase()
     {
       memset((char *)&Sembase,0, sizeof(SEMBASE));
     }

  TSemBase(SEMBASE * sembase)
     {
       LoadSemBase(sembase);
     }

  TSemBase(int type, const char * string)
     {
       LoadAnyString(type, string, 0);
     }

  TSemBase(signed char charval)
     {
       Scale(0);
       Value(charval);
     }

  TSemBase(short shortval)
    {
      Scale(0);
      Value(shortval);
    }

  TSemBase(long longval)
    {
      Scale(0);
      Value(longval);
    }

  TSemBase(double doubleval)
     {
       Value(doubleval);
     }

  // C������� ������� �������������� � ��������
  // ��� ��������� ����������� ���������� � ���������
  // ������������ �������� "&"
  // if (one->Compare(two) & CMNOTEQ) { ... }
  HOW Compare(TSemBase * base);

  // ��������� �������� �������������� � �������� ����
  double DoubleValue();

  // ������������� ������,���������� �������� ��������,
  // � ����� ���� "���������"
  // ��� ������ ���������� ����
  int LoadStringNumber(const char * string);

  // ������������� ������ � ����� ���� "���������"
  // � ������������ � ����� �������������� (TYPE)
  // ��� ������ ���������� ����
  int LoadAnyString(int type, const char * string, int maxsize);

  // ��������� �������� �������������� � �������� ����
  int LongValue();

  // ��������� ���������� �����������
  int Scale() { return(Sembase.Char.Scale); }
  int StringSize() { return(Sembase.String.Scale); }

  // ��������� ��� ��������������
  TYPE Type() { return((TYPE)Sembase.String.Type); }

  // ��������� �������� �������������� � �������� ����
  char * StringValue(char * place,int maxsize);

  // �������������� ������ �������� �� ANSI � ASCII (DOS)
  // ���� �������� �������������� �� ���������� - ���������� ����
  char * StringInDos();

  // �������������� ������ �������� �� ASCII (DOS) � ANSI
  // ����������� ������������� ��� ��������� � ������
  // ���� �������� �������������� �� ���������� - ���������� ����
  char * StringInAnsi();

  // ��������� ����� �������� ��������������
  int Length()
     {
       if ((Type() == STRING) || (Type() == STRDOS))
         return(StringSize()
                       +sizeof(Sembase.String.Type)
                       +sizeof(Sembase.String.Scale) + 1);
       else
         return(Type() +sizeof(Sembase.String.Type)
                       +sizeof(Sembase.String.Scale));
     }


  // ��������� ����� ���� ���������
  void LoadSemBase(SEMBASE * sembaseval);


  // ���������� �������� ��������������
  signed char Value(signed char value)
     {
       Type(SHORT);
       return (signed char)(Sembase.Short.Value = value);
     }

  signed short Value(signed short value)
     {
       Type(SHORT);
       return(Sembase.Short.Value = value);
     }

  long int Value(long int value)
     {
       Type(LONG);
#ifndef RISCCPU
       return (Sembase.Long.Value = value);
#else
       REGISTER reg;
       reg.Long = value;
       return reg.PutLong(Sembase.Long.Value);
#endif
     }

  double Value(double value)
     {
       Type(DOUBLE);
       Scale(0);
#ifndef RISCCPU
       return(Sembase.Double.Value = value);
#else
       DOUBLEREGISTER reg;
       reg.Double = value;
       return reg.PutDouble(Sembase.Double.Value);
#endif
     }

  // ������ ������ ���� � ����� ANSI !
  // �� ������������� �������� ���, ��� �������� ��� �������
  char * Value(const char * value, int maxsize);

protected :

  //  ���������� ���������� �����������
  int Scale(int scale)
     {
       return (int)(Sembase.Char.Scale = (signed char)scale);
     }

  int StringSize(int scale)
     {
       return (int)(Sembase.String.Scale = (unsigned char)scale);
     }

  // ���������� ��� ��������������
  TYPE Type(TYPE type)
   {
     return((TYPE)(Sembase.String.Type = (unsigned char)type));
   }

public :

  SEMBASE Sembase; // ����� ���� "���������"  
};

#endif // __cplusplus

typedef struct SEMBASEVAL
{
  SEMBASE Sembase;
}
  SEMBASEVAL;

typedef struct _DLLCLASS SEMBLOCK // ������ ������������� ��������������
{
#ifndef RISCCPU                   
  unsigned short int SemCode;     // ��� ���������
#else
  unsigned char      SemCode[2];
#endif
#ifdef __cplusplus
  TSemBase    Data;               // �������� ��������� - ����� ���� ���������
#else
  SEMBASEVAL  Data;               // �������� ��������� - ����� ���� ���������
#endif
}
  SEMBLOCK;

// ������������ ������
#define sblInit(semb) memset((void*)semb, 0, sizeof(SEMBLOCK));

#ifdef __cplusplus

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++ ������ ������� � ������������� ���������������  ++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct _DLLCLASS TSemBlock : public SEMBLOCK
{
  public:

  // ���� �������������
  typedef enum type
   {
     STRDOS = 0,   // C����� �������� (ASCIIZ),������������ �����
     STRING = 126, // C����� �������� (ANSI),������������ �����
     STRUNI = 127, // C����� �������� (UNICODE),������������ �����
     CHAR   = 1,   // 1 ����   SIGNED CHAR
     SHORT  = 2,   // 2 ����A  SIGNED SHORT
     LONG   = 4,   // 4 ����A  SIGNED INT
     DOUBLE = 8    // 8 ����   DOUBLE

   }
     TYPE;


   // ������������� ��� ������� ������
   TSemBlock()
      {
        Code(0);
        Value(0l);
      }

   TSemBlock(int code, TSemBase * sbase)
      {
        Code(code);
        memmove((char *)&Data,(char *)sbase,sbase->Length());
      }

   TSemBlock(int code, int type, const char * value, int maxsize = 0)
      {
        Code(code);
        Value(type,value,maxsize);
      }

   // ��������� ��� ���������
   int Code()
      {
#ifndef RISCCPU                   
        return (SemCode);
#else
        REGISTER reg;

       	ShortToRegister(reg, SemCode);
       	return reg.Long;
#endif
      }

   // ���������� ��� ���������
   int Code(int code)
      {
#ifndef RISCCPU                   
        return (SemCode = (unsigned short int)code);
#else
        REGISTER reg;

       	ShortToRegister(reg, &code);
       	RegisterToShort(reg, SemCode);
        return reg.Long;
#endif
      }

   // �������� ��� ��������� + ��������
   HOW Compare (TSemBlock * semdata)
      {
#ifndef RISCCPU                   
        if (Code() != semdata->SemCode) return(CMBAD);
#else
        REGISTER reg;

	ShortToRegister(reg, semdata->SemCode);
        if ((unsigned short int)Code() != (unsigned short int)reg.Long) return(CMBAD);
#endif
        return CompareData((TSemBase *)&(semdata->Data));
      }

   // �������� ��� ��������������
   HOW CompareCode (int code)
      {
#ifndef RISCCPU                   
        if ((unsigned short int)code < SemCode) return(CMLESS);

        if ((unsigned short int)code > SemCode) return(CMMORE);
#else
        REGISTER reg;

	ShortToRegister(reg, SemCode);

        if ((unsigned short int)code < (unsigned short int)reg.Long) return(CMLESS);

        if ((unsigned short int)code > (unsigned short int)reg.Long) return(CMMORE);
#endif

        return(CMEQUAL);
      }

   // �������� �������� ��������������
   HOW CompareData (TSemBase * sembase)
      {
        return ( Data.Compare(sembase));
      }

   // ��������� �������� �������������� � �������� ����
   double DoubleValue()
      {
        return(Data.DoubleValue());
      }

   // ��������� ����� �������� ���������
   int Length()
      {
        return (sizeof(SemCode) + Data.Length());
      }

   // ��������� �������� �������������� � �������� ����
   int  LongValue()
      {
        return(Data.LongValue());
      }

   // �������������� ������ �������� �� ASCII (DOS) � ANSI
   // ���� �������� �������������� �� ���������� - ���������� ����
   char * StringInAnsi()
      {
        return Data.StringInAnsi();
      }

   // �������������� ������ �������� �� ANSI � ASCII (DOS)
   // ���� �������� �������������� �� ���������� - ���������� ����
   char * StringInDos()
      {
        return Data.StringInDos();
      }

   // ��������� �������� �������������� � �������� ����
   // place - ����� �������, ���� ���������� ������
   // maxsize - ���������� ������ �������� ������
   char * StringValue(char *place, int maxsize)
      {
        return(Data.StringValue(place,maxsize));
      }

   // ��������� ��� �������� ���������
   int Type ()
      {
        return (int)Data.Type();
      }

   // ���������� �������� ��������������
   signed char Value(signed char value)
     {
       return Data.Value(value);
     }

  signed short Value(signed short value)
     {
       return Data.Value(value);
     }

  long int Value(long int value)
     {
       return Data.Value(value);
     }

  double Value(double value)
     {
       return Data.Value(value);
     }

  // ������ ������ ���� � ����� ANSI/KOI8
  char * Value(const char * value,int maxsize = 0)
     {
       return Data.Value(value,maxsize);
     }

  // ������ ������ ���� � ����� ANSI/KOI8
  // ��� ������ ���������� ����
  int Value(int type,const char * value,int maxsize = 0)
     {
       return Data.LoadAnyString(type,value,maxsize);
     }
};
#else
  typedef SEMBLOCK TSemBlock;
#endif  // __cplusplus


typedef struct WORKSEMANTIC
{
  TSemBlock *  Block;  // ��������� �� ������� ���� ���������
  int         AppLen;  // 1 - ��������� ����������� ����� ����� ���������
  int      IsCorrect;  // 1 - ����� ��������� ���������
  long     SemLength;  // ����� ������ ���������
  long     BufLength;  // ����� ������ ���������
  char *      EndSem;  // ����� ���������
  char *      BegSem;  // ������ ���������
  int         Number;  // ����� ������� ��������������
  int        Isdirty;  // ������� �������������� ���������
}
  WORKSEMANTIC;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++ ������ ��������� ������ ������������� ������������� ++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ������������ ������
#define wsemInit(wsem) memset((void*)wsem, 0, sizeof(WORKSEMANTIC));

void _fastcall wsemInitSem(WORKSEMANTIC * worksemantic, char HUGER * begin,    // ������ ���������
                 long lengthsemantic,   // ����� ����� ���������
                 long lengthbuffer);    // ����� ������


//  ���������� ������ � ��������� �������
void _fastcall wsemAccess(WORKSEMANTIC * worksemantic, char HUGER * begin,  // ������ ���������
                           long lengthsemantic, // ����� ����� ���������
                           long lengthbuffer );  // ����� ����� ������

// �������� � ��������� ����� ���������
void _fastcall wsemCheckSemLength(WORKSEMANTIC * worksemantic);

// ��������� ����� ���������
int _fastcall wsemGetLength(WORKSEMANTIC * worksemantic);

//  ����� ���� �� ���� ��������������
TSemBlock * _fastcall wsemFindCode(WORKSEMANTIC * worksemantic, int code);

// ��� ������ ���������� ����
TSemBlock * _fastcall wsemUpdate(WORKSEMANTIC * worksemantic, TSemBlock * block);

//  �������� �������������� (����� ������� ������ )
TSemBlock * _fastcall wsemInsert( WORKSEMANTIC * worksemantic, TSemBlock * block);

//  ������� ������� ��������������
int _fastcall wsemDelete(WORKSEMANTIC * worksemantic);

//  ���������� ���������� ��������
int _fastcall wsemSemanticsAmount(WORKSEMANTIC * worksemantic);

// ������� �� ������ ��������������
TSemBlock * _fastcall wsemGoFirst(WORKSEMANTIC * worksemantic);

// ������� �� ��������� �������������� �� ��� ������������
// ��� ������ ���������� ����
TSemBlock * _fastcall wsemGoNext(WORKSEMANTIC * worksemantic);

//  ���������� ����� �������������� �� ���� ���������(����� ��������)
TSemBlock * _fastcall wsemFindCodeNext(WORKSEMANTIC * worksemantic, int code);

//  ��������� ����� ������������� �������������
//  �� �������� �������
//  ��� ������ ���������� ����
//  ��� �������� ���������� - ������ ��������� ������
int _fastcall wsemLoad(WORKSEMANTIC * worksemantic,
                       WORKSEMANTIC * worksemn); 

//  ���������� ����� ���������
//  ���������� ����� ����� ��������� ��� 0 ��� ������
int _fastcall wsemPutLength(WORKSEMANTIC * worksemantic, int value);

//  ������� �� ����� ������ ���������
TSemBlock * _fastcall wsemGoEnd(WORKSEMANTIC * worksemantic);

// �������� �������������� (� ����� ���������)
TSemBlock * _fastcall wsemAppend(WORKSEMANTIC * worksemantic, TSemBlock * block);

//  ������� �� �������������� � ���������� ������� number
//  number ���������� � 1
TSemBlock * _fastcall wsemGoNumber(WORKSEMANTIC * worksemantic, int number);

//  �������� �������� �������������� � �������� �����
TSemBlock * _fastcall wsemReplyValue(WORKSEMANTIC * worksemantic,
                                     char * value, int maxsize);

#ifdef __cplusplus

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++ ������ ��������� ������ ������������� ������������� ++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TWorkSemantic : public WORKSEMANTIC
{
  public:

   // ������������ ������
   TWorkSemantic(char HUGER * begin,    // ������ ���������
                 long lengthsemantic,   // ����� ����� ���������
                 long lengthbuffer = 0  // ����� ������
                )
     {
       Access(begin,lengthsemantic,lengthbuffer);
     }

   TWorkSemantic()
     {
       Block     = 0;
       AppLen    = 0;     // ������ ���������
       IsCorrect = 0;     // ����� ��������� �� �����������
       SemLength = 0;
       BufLength = 0;
       EndSem    = 0;
       BegSem    = 0;
       Number    = 0;
       Isdirty   = 0;
     }

   // ���������� ������
   ~TWorkSemantic(){}

   // ���������� ������ � ��������� �������
   void Access(char HUGER * begin,     // ������ ���������
               long lengthsemantic,    // ����� ����� ���������
               long lengthbuffer = 0); // ����� ����� ������

   // �������� �������������� (� ����� ���������)
   TSemBlock * Append( TSemBlock * block)
     {
       GoEnd();                   // ������� �� �����
       return(Insert(block));     // ��������
     }

   // ��������� ����� ������
   int BufferLength() { return BufLength; }

   // �������� � ��������� ����� ���������
   void CheckSemLength();

   // ������� ������� ��������������
   // ��� ������ ���������� ����
   int Delete();

   // �������� �������������� (����� ������� ������ )
   // ��� ������ ���������� ����
   TSemBlock * Insert( TSemBlock * block);

   // ���������/���������� ������� �������������� ������
   int IsDirty() { return Isdirty; }
   int IsDirty(int dirty) { return (Isdirty = dirty && 1); }

   // ����� �������������� �� ���� ���������
   // ��� ������ ���������� ����
   TSemBlock * FindCode(int code);

   // ����� �������������� �� ���� ��������� � ��������
   // ��� ������ ���������� ����
   TSemBlock * FindCodeAndValue(int code,char * value);
   TSemBlock * FindCodeAndValue(int code,long value);
   TSemBlock * FindCodeAndValue(int code,double& value);

   // ����� �������������� �� ���� ��������� � �������� ��������
   // ���� ��������� � ����� code �� ������� - ���������� CMBAD !!!
   HOW CompareCodeAndValue(int code,char * value);
   HOW CompareCodeAndValue(int code,long value);
   HOW CompareCodeAndValue(int code,double& value);

   // ���������� ����� �������������� �� ���� ���������(����� ��������)
   // ��� ������ ���������� ����
   TSemBlock * FindCodeNext(int code);

   // ����� �������������� �� ���� ��������� � ��������
   // ��� ������ ���������� ����
   TSemBlock * FindBlock(TSemBlock * block);

   // ���������� ����� �������������� �� ���� ��������� � �������� (����� ��������)
   // ��� ������ ���������� ����
   TSemBlock * FindBlockNext(TSemBlock *Block);

   // ��������� ��� ��������������
   // number - ���������������� ����� ��������������
   // ��� ������ ���������� ����
   int GetCode(int number)
     {
        if (GoNumber(number) == 0) return 0;
        return Block->Code();
     }

   //  ������� �� ����� ������ ���������
   // (�� ��������� ���������������)
   TSemBlock * GoEnd();

   // ������� �� ������ ��������������
   TSemBlock * GoFirst()
     {
       Number = 1;
                     return Block = (TSemBlock *)BegSem;
     }

   // ������� �� ��������� �������������� �� ��� ������������
   // ��� ������ ���������� ����
          TSemBlock * GoNext();

   // ��������� ����� ������� ��������������
   TSemBlock * GoNumber()
     {
       return Block;
     }

   // ������� �� �������������� � ���������� ������� number
   // ��� ������ ���������� ����
   TSemBlock * GoNumber(int number);

   // ��������� ����� ���������
   int Length()
     {
       if (IsCorrect == 0) CheckSemLength();
       return SemLength;
     }

   // ��������� ���������������� ����� ������� ��������������
   int CurrentNumber() { return Number; }

   // �������� ��� �������������� � �������� �����
   // ��� ������ ���������� ����
   TSemBlock * ReplyCode(int code)
      {
        if ((Block == (TSemBlock *)EndSem) || (Block == 0))
          {
            return 0;  // ���� ������ ����� ���
          }

        Block->Code(code);
        IsDirty(1);
                      return(Block);
      }

   // �������� �������� �������������� � �������� �����
   TSemBlock * ReplyValue(char * value,int maxsize);

   // ���������� ���������� ��������
   int Count() { return SemanticsAmount(); }
   int SemanticsAmount();

   // ��������� �������� �������������� � ���������� ���� (ANSI)
   // number - ���������������� ����� ��������������,
   // place - ����� ���������� ������,
   // maxsize - ������������ ����� ������
   // ��� ������ ���������� ����,
   // ��� �������� ���������� - ����� ������ (����� place)
   char * StringValue(int number,char *place,int maxsize)
      {
        if (GoNumber(number) == 0) return 0;
        return Block->StringValue(place,maxsize);
      }

   // ��������� �������� ������������� �������������� �������
   // � ���� ����� � ��������� ������ ������� ��������
   // number  - ���������������� ����� ��������������
   // ���� �������� ��������� �� ����� ���� �������������
   // � ��������� ���� ��� - ���������� 0
   double DoubleValue(int number)
      {
        if (GoNumber(number) == 0) return 0;
        return Block->DoubleValue();
      }

   // �������� ������� ��������������
   // ��� ������ ���������� ����
   TSemBlock * Update(TSemBlock * block)
    {
      if ((char HUGER *)Block < EndSem)  // ��������� �� � ����� ���������
         Delete();
      return Insert(block);
    }

   //  ���������� ����� ���������
   //  ���������� ����� ����� ��������� ��� 0 ��� ������
   int Length(int value);

   // ��������� ����� ������������� �������������
   // �� �������� �������
   // ��� ������ ���������� ����
   // ��� �������� ���������� - ������ ��������� ������
   int Load(TWorkSemantic * worksemn);

   // �������������� ��� ������ �������� �� ASCII (DOS) � ANSI
   void StringsInAnsi();

   // �������������� ��� ������ �������� �� ANSI � ASCII (DOS)
   void StringsInDos();
};

#else

typedef  WORKSEMANTIC  TWorkSemantic; 


#endif  // __cplusplus

#endif  // MAPSEM_H




