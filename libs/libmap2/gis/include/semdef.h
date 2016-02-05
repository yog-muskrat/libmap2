
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
//  Определение числа типа "семантика"
// --------------------------------------------------------
typedef struct SEMCHAR
{
  unsigned char Type;        // Тип характеристики
  signed char  Scale;        // Масштабный коэффициент
  signed char  Value;        // Значение характеристики
}
  SEMCHAR;

typedef struct SEMSHORT
{
  unsigned char Type;        // Тип характеристики
  signed char  Scale;        // Масштабный коэффициент
  signed short Value;        // Значение характеристики
}
  SEMSHORT;

typedef struct SEMLONG
{
  unsigned char Type;        // Тип характеристики
  signed char  Scale;        // Масштабный коэффициент
#ifndef RISCCPU
  ::LONG     Value;        // Значение характеристики
#else
  char      Value[4];        // Значение характеристики
#endif
}
  SEMLONG;

typedef struct SEMDOUBLE
{
  unsigned char Type;        // Тип характеристики
  signed char  Scale;        // Масштабный коэффициент
#ifndef RISCCPU
  double       Value;        // Значение характеристики
#else
  char      Value[8];        // Значение характеристики
#endif
}
  SEMDOUBLE;

typedef struct SEMSTRING
{
  unsigned char Type;        // Тип характеристики
  unsigned char  Scale;      // Масштабный коэффициент
     char   Value[256];      // Значение характеристики
}
  SEMSTRING;

typedef struct SEMWSTRING    
{
  unsigned char Type;        // Тип характеристики
  signed char  Scale;        // Масштабный коэффициент
#ifndef RISCCPU              
  wchar_t Value[128];        // Значение характеристики в UNICODE  
#else
  char    Value[128 * 2];    // Значение характеристики в UNICODE  
#endif
}
  SEMWSTRING;

typedef union AnySemantic    // ЧИСЛО ТИПА СЕМАНТИКА
{
  SEMWSTRING WString;
  SEMSTRING  String;
  SEMCHAR    Char;
  SEMSHORT   Short;
  SEMLONG    Long;
  SEMDOUBLE  Double;
}
  SEMBASE;

// Типы характеристик
typedef enum sembasetype
{
  SEMBASESTRDOS = 0,   // CТРОКА СИМВОЛОВ (ASCIIZ),ОГРАНИЧЕННАЯ НУЛЕМ
  SEMBASESTRING = 126, // CТРОКА СИМВОЛОВ (ANSI),ОГРАНИЧЕННАЯ НУЛЕМ
  SEMBASESTRUNI = 127, // CТРОКА СИМВОЛОВ (UNICODE),ОГРАНИЧЕННАЯ НУЛЕМ
  SEMBASECHAR   = 1,   // 1 БАЙТ   SIGNED CHAR
  SEMBASESHORT  = 2,   // 2 БАЙТA  SIGNED SHORT
  SEMBASELONG   = 4,   // 4 БАЙТA  SIGNED INT
  SEMBASEDOUBLE = 8    // 8 БАЙТ   DOUBLE IEEE
}
  SEMBASETYPE;


//********************************************************************
//        Инициализация переменных класса TSemBase                   *
//********************************************************************

// Заполнить переменную Sembase
#define sbsInit(sembase) memset((void*)sembase, 0 , sizeof(SEMBASE));

//********************************************************************
//       Глобальные функции класса TSemBase                          *
//********************************************************************

// Установить значение характеристики
long int _fastcall sbsPutLongValue(SEMBASE * sembase, long int value);

// Установить значение характеристики
double _fastcall sbsPutDoubleValue(SEMBASE * sembase, double value);

//  Установить значение характеристики
//  Строка должна быть в кодах ANSI (для Windows) или KOI8 (для UNIX)
//  За перекодировку отвечает тот, кто вызывает эту функцию
char * _fastcall sbsPutStringValue(SEMBASE * sembase,
                                   const char * value, int maxsize);

// Запрос значения характеристики в числовом виде
int _fastcall sbsGetLongValue(SEMBASE * sembase);

// Запрос значения характеристики в числовом виде
double _fastcall sbsGetDoubleValue(SEMBASE * sembase);

//  Запрос значения характеристики в символьном виде
char * _fastcall sbsGetStringValue(SEMBASE * sembase,
                                   char * Place, int MaxSize);

//  Cравнить текущую характеристику с заданной
HOW _fastcall sbsCompare(SEMBASE * sembase, SEMBASE * base);

//  Перекодировать строку символов из ANSI в ASCII (DOS)
//  Если значение характеристики не символьное - возвращает ноль
char * _fastcall sbsStringInDos(SEMBASE * sembase);

//  Перекодировать строку символов из ASCII (DOS) в ANSI
//  Выполняется автоматически при обращении к строке
//  Если значение характеристики не символьное - возвращает ноль
char * _fastcall sbsStringInAnsi(SEMBASE * sembase);

//  Преобразовать строку к числу типа "семантика"
//  в соответствии с типом характеристики (TYPE)
//  При ошибке возвращает ноль
int _fastcall sbsLoadAnyString(SEMBASE * sembase, int type,
                               const char * string, int maxsize);

//  Перевод строки,(изображающей число) в число типа "семантика"
//  Возврат - количество правильно преобразованных
//  символов, число м.б. округлено
int _fastcall sbsLoadStringNumber(SEMBASE * sembase,const char * str);

//  Загрузить число типа семантика
void _fastcall sbsLoadSemBase(SEMBASE * sembase,SEMBASE * sembaseval);

// Запросить длину значения характеристики
unsigned int _fastcall sbsGetLength(SEMBASE * sembase);


#ifdef __cplusplus

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++      МЕТОДЫ ДОСТУПА К ЧИСЛАМ ТИПА СЕМАНТИКА     ++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct _DLLCLASS TSemBase
{
public :

  // Типы характеристик
  typedef enum type
   {
     STRDOS = SEMBASESTRDOS, // CТРОКА СИМВОЛОВ (ASCIIZ),ОГРАНИЧЕННАЯ НУЛЕМ
     STRING = SEMBASESTRING, // CТРОКА СИМВОЛОВ (ANSI),ОГРАНИЧЕННАЯ НУЛЕМ
     STRUNI = SEMBASESTRUNI, // CТРОКА СИМВОЛОВ (UNICODE),ОГРАНИЧЕННАЯ НУЛЕМ
     CHAR   = SEMBASECHAR,   // 1 БАЙТ   SIGNED CHAR
     SHORT  = SEMBASESHORT,  // 2 БАЙТA  SIGNED SHORT
     LONG   = SEMBASELONG,   // 4 БАЙТA  SIGNED INT
     DOUBLE = SEMBASEDOUBLE  // 8 БАЙТ   DOUBLE IEEE
   }
     TYPE;


  // Заполнить класс числом типа семантика, либо подготовить место
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

  // Cравнить текущую характеристику с заданной
  // Для сравнения полученного результата с требуемым
  // использовать операцию "&"
  // if (one->Compare(two) & CMNOTEQ) { ... }
  HOW Compare(TSemBase * base);

  // Запросить значение характеристики в заданном виде
  double DoubleValue();

  // Преобразовать строку,содержащую цифровое значение,
  // к числу типа "семантика"
  // При ошибке возвращает ноль
  int LoadStringNumber(const char * string);

  // Преобразовать строку к числу типа "семантика"
  // в соответствии с типом характеристики (TYPE)
  // При ошибке возвращает ноль
  int LoadAnyString(int type, const char * string, int maxsize);

  // Запросить значение характеристики в заданном виде
  int LongValue();

  // Запросить масштабный коэффициент
  int Scale() { return(Sembase.Char.Scale); }
  int StringSize() { return(Sembase.String.Scale); }

  // Запросить тип характеристики
  TYPE Type() { return((TYPE)Sembase.String.Type); }

  // Запросить значение характеристики в заданном виде
  char * StringValue(char * place,int maxsize);

  // Перекодировать строку символов из ANSI в ASCII (DOS)
  // Если значение характеристики не символьное - возвращает ноль
  char * StringInDos();

  // Перекодировать строку символов из ASCII (DOS) в ANSI
  // Выполняется автоматически при обращении к строке
  // Если значение характеристики не символьное - возвращает ноль
  char * StringInAnsi();

  // Запросить длину значения характеристики
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


  // Загрузить число типа семантика
  void LoadSemBase(SEMBASE * sembaseval);


  // Установить значение характеристики
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

  // Строка должна быть в кодах ANSI !
  // За перекодировку отвечает тот, кто вызывает эту функцию
  char * Value(const char * value, int maxsize);

protected :

  //  Установить масштабный коэффициент
  int Scale(int scale)
     {
       return (int)(Sembase.Char.Scale = (signed char)scale);
     }

  int StringSize(int scale)
     {
       return (int)(Sembase.String.Scale = (unsigned char)scale);
     }

  // Установить тип характеристики
  TYPE Type(TYPE type)
   {
     return((TYPE)(Sembase.String.Type = (unsigned char)type));
   }

public :

  SEMBASE Sembase; // Число типа "семантика"  
};

#endif // __cplusplus

typedef struct SEMBASEVAL
{
  SEMBASE Sembase;
}
  SEMBASEVAL;

typedef struct _DLLCLASS SEMBLOCK // СОСТАВ СЕМАНТИЧЕСКОЙ ХАРАКТЕРИСТИКИ
{
#ifndef RISCCPU                   
  unsigned short int SemCode;     // КОД СЕМАНТИКИ
#else
  unsigned char      SemCode[2];
#endif
#ifdef __cplusplus
  TSemBase    Data;               // ЗНАЧЕНИЕ СЕМАНТИКИ - ЧИСЛО ТИПА СЕМАНТИКА
#else
  SEMBASEVAL  Data;               // ЗНАЧЕНИЕ СЕМАНТИКИ - ЧИСЛО ТИПА СЕМАНТИКА
#endif
}
  SEMBLOCK;

// Конструкторы класса
#define sblInit(semb) memset((void*)semb, 0, sizeof(SEMBLOCK));

#ifdef __cplusplus

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++ МЕТОДЫ ДОСТУПА К СЕМАНТИЧЕСКИМ ХАРАКТЕРИСТИКАМ  ++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct _DLLCLASS TSemBlock : public SEMBLOCK
{
  public:

  // Типы характеристик
  typedef enum type
   {
     STRDOS = 0,   // CТРОКА СИМВОЛОВ (ASCIIZ),ОГРАНИЧЕННАЯ НУЛЕМ
     STRING = 126, // CТРОКА СИМВОЛОВ (ANSI),ОГРАНИЧЕННАЯ НУЛЕМ
     STRUNI = 127, // CТРОКА СИМВОЛОВ (UNICODE),ОГРАНИЧЕННАЯ НУЛЕМ
     CHAR   = 1,   // 1 БАЙТ   SIGNED CHAR
     SHORT  = 2,   // 2 БАЙТA  SIGNED SHORT
     LONG   = 4,   // 4 БАЙТA  SIGNED INT
     DOUBLE = 8    // 8 БАЙТ   DOUBLE

   }
     TYPE;


   // Инициализация или очистка класса
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

   // Запросить код семантики
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

   // Установить код семантики
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

   // Сравнить код семантики + значение
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

   // Сравнить код характеристики
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

   // Сравнить значение характеристики
   HOW CompareData (TSemBase * sembase)
      {
        return ( Data.Compare(sembase));
      }

   // Запросить значение характеристики в заданном виде
   double DoubleValue()
      {
        return(Data.DoubleValue());
      }

   // Запросить длину значения семантики
   int Length()
      {
        return (sizeof(SemCode) + Data.Length());
      }

   // Запросить значение характеристики в заданном виде
   int  LongValue()
      {
        return(Data.LongValue());
      }

   // Перекодировать строку символов из ASCII (DOS) в ANSI
   // Если значение характеристики не символьное - возвращает ноль
   char * StringInAnsi()
      {
        return Data.StringInAnsi();
      }

   // Перекодировать строку символов из ANSI в ASCII (DOS)
   // Если значение характеристики не символьное - возвращает ноль
   char * StringInDos()
      {
        return Data.StringInDos();
      }

   // Запросить значение характеристики в заданном виде
   // place - адрес области, куда помещается строка
   // maxsize - предельный размер выходной строки
   char * StringValue(char *place, int maxsize)
      {
        return(Data.StringValue(place,maxsize));
      }

   // Запросить тип значения семантики
   int Type ()
      {
        return (int)Data.Type();
      }

   // Установить значение характеристики
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

  // Строка должна быть в кодах ANSI/KOI8
  char * Value(const char * value,int maxsize = 0)
     {
       return Data.Value(value,maxsize);
     }

  // Строка должна быть в кодах ANSI/KOI8
  // При ошибке возвращает ноль
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
  TSemBlock *  Block;  // Указатель на текущий блок семантики
  int         AppLen;  // 1 - разрешает увеличивать общую длину семантики
  int      IsCorrect;  // 1 - длина семантики корректна
  long     SemLength;  // Длина записи семантики
  long     BufLength;  // Длина буфера семантики
  char *      EndSem;  // Конец семантики
  char *      BegSem;  // Начало семантики
  int         Number;  // Номер текущей характеристики
  int        Isdirty;  // Признак редактирования семантики
}
  WORKSEMANTIC;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++ МЕТОДЫ ОБРАБОТКИ НАБОРА СЕМАНТИЧЕСКИХ ХАРАКТЕРИСТИК ++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Конструкторы класса
#define wsemInit(wsem) memset((void*)wsem, 0, sizeof(WORKSEMANTIC));

void _fastcall wsemInitSem(WORKSEMANTIC * worksemantic, char HUGER * begin,    // начало семантики
                 long lengthsemantic,   // общая длина семантики
                 long lengthbuffer);    // длина буфера


//  Установить доступ к семантике объекта
void _fastcall wsemAccess(WORKSEMANTIC * worksemantic, char HUGER * begin,  // начало семантики
                           long lengthsemantic, // общая длина семантики
                           long lengthbuffer );  // общая длина буфера

// Проверка и коррекция длины семантики
void _fastcall wsemCheckSemLength(WORKSEMANTIC * worksemantic);

// Запросить длину семантики
int _fastcall wsemGetLength(WORKSEMANTIC * worksemantic);

//  Найти блок по коду характеристики
TSemBlock * _fastcall wsemFindCode(WORKSEMANTIC * worksemantic, int code);

// При ошибке возвращает ноль
TSemBlock * _fastcall wsemUpdate(WORKSEMANTIC * worksemantic, TSemBlock * block);

//  Вставить характеристику (перед текущим блоком )
TSemBlock * _fastcall wsemInsert( WORKSEMANTIC * worksemantic, TSemBlock * block);

//  Удалить текущую характеристику
int _fastcall wsemDelete(WORKSEMANTIC * worksemantic);

//  Определить количество семантик
int _fastcall wsemSemanticsAmount(WORKSEMANTIC * worksemantic);

// Перейти на первую характеристику
TSemBlock * _fastcall wsemGoFirst(WORKSEMANTIC * worksemantic);

// Перейти на следующую характеристику из уже существующих
// При ошибке возвращает ноль
TSemBlock * _fastcall wsemGoNext(WORKSEMANTIC * worksemantic);

//  Продолжить поиск характеристики по коду семантики(после текущего)
TSemBlock * _fastcall wsemFindCodeNext(WORKSEMANTIC * worksemantic, int code);

//  Загрузить набор семантических характеристик
//  из заданной области
//  При ошибке возвращает ноль
//  При успешном выполнении - размер созданной записи
int _fastcall wsemLoad(WORKSEMANTIC * worksemantic,
                       WORKSEMANTIC * worksemn); 

//  Установить длину семантики
//  Возвращает новую длину семантики или 0 при ошибке
int _fastcall wsemPutLength(WORKSEMANTIC * worksemantic, int value);

//  Перейти на конец записи семантики
TSemBlock * _fastcall wsemGoEnd(WORKSEMANTIC * worksemantic);

// Добавить характеристику (в конец семантики)
TSemBlock * _fastcall wsemAppend(WORKSEMANTIC * worksemantic, TSemBlock * block);

//  Перейти на характеристику с порядковым номером number
//  number начинается с 1
TSemBlock * _fastcall wsemGoNumber(WORKSEMANTIC * worksemantic, int number);

//  Заменить значение характеристики у текущего блока
TSemBlock * _fastcall wsemReplyValue(WORKSEMANTIC * worksemantic,
                                     char * value, int maxsize);

#ifdef __cplusplus

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++ МЕТОДЫ ОБРАБОТКИ НАБОРА СЕМАНТИЧЕСКИХ ХАРАКТЕРИСТИК ++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TWorkSemantic : public WORKSEMANTIC
{
  public:

   // Конструкторы класса
   TWorkSemantic(char HUGER * begin,    // начало семантики
                 long lengthsemantic,   // общая длина семантики
                 long lengthbuffer = 0  // длина буфера
                )
     {
       Access(begin,lengthsemantic,lengthbuffer);
     }

   TWorkSemantic()
     {
       Block     = 0;
       AppLen    = 0;     // нельзя добавлять
       IsCorrect = 0;     // длина семантики не проверялась
       SemLength = 0;
       BufLength = 0;
       EndSem    = 0;
       BegSem    = 0;
       Number    = 0;
       Isdirty   = 0;
     }

   // Деструктор класса
   ~TWorkSemantic(){}

   // Установить доступ к семантике объекта
   void Access(char HUGER * begin,     // начало семантики
               long lengthsemantic,    // общая длина семантики
               long lengthbuffer = 0); // общая длина буфера

   // Добавить характеристику (в конец семантики)
   TSemBlock * Append( TSemBlock * block)
     {
       GoEnd();                   // перешли на конец
       return(Insert(block));     // добавили
     }

   // Запросить длину буфера
   int BufferLength() { return BufLength; }

   // Проверка и коррекция длины семантики
   void CheckSemLength();

   // Удалить текущую характеристику
   // При ошибке возвращает ноль
   int Delete();

   // Вставить характеристику (перед текущим блоком )
   // При ошибке возвращает ноль
   TSemBlock * Insert( TSemBlock * block);

   // Запросить/Установить признак редактирования данных
   int IsDirty() { return Isdirty; }
   int IsDirty(int dirty) { return (Isdirty = dirty && 1); }

   // Найти характеристику по коду семантики
   // При ошибке возвращает ноль
   TSemBlock * FindCode(int code);

   // Найти характеристику по коду семантики и значению
   // При ошибке возвращает ноль
   TSemBlock * FindCodeAndValue(int code,char * value);
   TSemBlock * FindCodeAndValue(int code,long value);
   TSemBlock * FindCodeAndValue(int code,double& value);

   // Найти характеристику по коду семантики и сравнить значение
   // Если семантика с кодом code не найдена - возвращает CMBAD !!!
   HOW CompareCodeAndValue(int code,char * value);
   HOW CompareCodeAndValue(int code,long value);
   HOW CompareCodeAndValue(int code,double& value);

   // Продолжить поиск характеристики по коду семантики(после текущего)
   // При ошибке возвращает ноль
   TSemBlock * FindCodeNext(int code);

   // Найти характеристику по коду семантики и значению
   // При ошибке возвращает ноль
   TSemBlock * FindBlock(TSemBlock * block);

   // Продолжить поиск характеристики по коду семантики и значению (после текущего)
   // При ошибке возвращает ноль
   TSemBlock * FindBlockNext(TSemBlock *Block);

   // Запросить код характеристики
   // number - последовательный номер характеристики
   // При ошибке возвращает ноль
   int GetCode(int number)
     {
        if (GoNumber(number) == 0) return 0;
        return Block->Code();
     }

   //  Перейти на конец записи семантики
   // (за последней характеристикой)
   TSemBlock * GoEnd();

   // Перейти на первую характеристику
   TSemBlock * GoFirst()
     {
       Number = 1;
                     return Block = (TSemBlock *)BegSem;
     }

   // Перейти на следующую характеристику из уже существующих
   // При ошибке возвращает ноль
          TSemBlock * GoNext();

   // Запросить адрес текущей характеристики
   TSemBlock * GoNumber()
     {
       return Block;
     }

   // Перейти на характеристику с порядковым номером number
   // При ошибке возвращает ноль
   TSemBlock * GoNumber(int number);

   // Запросить длину семантики
   int Length()
     {
       if (IsCorrect == 0) CheckSemLength();
       return SemLength;
     }

   // Запросить последовательный номер текущей характеристики
   int CurrentNumber() { return Number; }

   // Заменить код характеристики у текущего блока
   // При ошибке возвращает ноль
   TSemBlock * ReplyCode(int code)
      {
        if ((Block == (TSemBlock *)EndSem) || (Block == 0))
          {
            return 0;  // если такого блока нет
          }

        Block->Code(code);
        IsDirty(1);
                      return(Block);
      }

   // Заменить значение характеристики у текущего блока
   TSemBlock * ReplyValue(char * value,int maxsize);

   // Определить количество семантик
   int Count() { return SemanticsAmount(); }
   int SemanticsAmount();

   // Запросить значение характеристики в символьном виде (ANSI)
   // number - последовательный номер характеристики,
   // place - адрес размещения строки,
   // maxsize - максимальная длина строки
   // При ошибке возвращает ноль,
   // при успешном выполнении - адрес строки (равен place)
   char * StringValue(int number,char *place,int maxsize)
      {
        if (GoNumber(number) == 0) return 0;
        return Block->StringValue(place,maxsize);
      }

   // Запросить значение семантической характеристики объекта
   // в виде числа с плавающей точкой двойной точности
   // number  - последовательный номер характеристики
   // Если значение семантики не может быть преобразовано
   // к числовому виду или - возвращает 0
   double DoubleValue(int number)
      {
        if (GoNumber(number) == 0) return 0;
        return Block->DoubleValue();
      }

   // Заменить текущую характеристику
   // При ошибке возвращает ноль
   TSemBlock * Update(TSemBlock * block)
    {
      if ((char HUGER *)Block < EndSem)  // находимся не в конце семантики
         Delete();
      return Insert(block);
    }

   //  Установить длину семантики
   //  Возвращает новую длину семантики или 0 при ошибке
   int Length(int value);

   // Загрузить набор семантических характеристик
   // из заданной области
   // При ошибке возвращает ноль
   // При успешном выполнении - размер созданной записи
   int Load(TWorkSemantic * worksemn);

   // Перекодировать все строки символов из ASCII (DOS) в ANSI
   void StringsInAnsi();

   // Перекодировать все строки символов из ANSI в ASCII (DOS)
   void StringsInDos();
};

#else

typedef  WORKSEMANTIC  TWorkSemantic; 


#endif  // __cplusplus

#endif  // MAPSEM_H




