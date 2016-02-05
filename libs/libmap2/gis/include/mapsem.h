
#if !defined(MAPSEM_H)
#define MAPSEM_H


#ifndef SEMDEF_H
  #include "semdef.h"
#endif

#ifndef MAPMACRO_H
  #include "mapmacro.h"
#endif

#define SEMIDENT 0x7FFF      // ИДЕНТИФИКАТОР НАЧАЛА ЗАПИСИ 
#define SEMIDENT_TURN 0xFF7F // ИДЕНТИФИКАТОР НАЧАЛА НЕПЕРЕВЕРНУТОЙ ЗАПИСИ

typedef struct SEMANTIC       // СЕМАНТИКА ОБ'ЕКТА
{
  unsigned short int Ident;   // 0x7FFF
  unsigned short int Length;  // Длина записи
}
  SEMANTIC;

typedef enum SEMVTYPE // Типы характеристик
{
  SEMVSTRDOS = 0,     // CТРОКА СИМВОЛОВ (ASCIIZ),ОГРАНИЧЕННАЯ НУЛЕМ
  SEMVSTRING = 126,   // CТРОКА СИМВОЛОВ (ANSI),ОГРАНИЧЕННАЯ НУЛЕМ
  SEMVSTRUNI = 127,   // CТРОКА СИМВОЛОВ (UNICODE),ОГРАНИЧЕННАЯ НУЛЕМ
  SEMVCHAR   = 1,     // 1 БАЙТ   SIGNED CHAR
  SEMVSHORT  = 2,     // 2 БАЙТA  SIGNED SHORT
  SEMVLONG   = 4,     // 4 БАЙТA  SIGNED INT
  SEMVDOUBLE = 8      // 8 БАЙТ   DOUBLE IEEE
}
  SEMVTYPE;

typedef struct _DLLCLASS SEMANTICDATA
{
 SEMANTICDATA() : Work() { Base = 0; Memory = 0; }

 SEMANTIC *    Base;     // Указатель на семантику (переменная длина)
 char     *    Memory;   // Способ обработки памяти в деструкторе
                								 // (если != 0, освободить)
 TWorkSemantic Work;     // Описание буфера семантики
}
  SEMANTICDATA;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  СЕМАНТИКА ОБ'ЕКТА ЭЛЕКТРОННОЙ КАРТЫ  +++++++++++++
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

  // Запросить адрес записи
  char * Address()
   {
     return (char *)Base;
   }

  // Проинициализировать запись семантки
  // Установить идентификатор записи и длину
  // При ошибке возвращает 0, при удаче 1
  int Clear()
  {
    if (Base == 0) return 0;
    Base->Ident   = SEMIDENT;
    Base->Length  = sizeof(SEMANTIC);
    return 1;
  }

  int Create() { return Clear(); }  // Синонимы

  // Запросить длину данных
  int DataLength()
   {
     if (!IsCorrect()) return 0;
     return (Base->Length - sizeof(SEMANTIC));
   }

  // Проверить корректность начала записи
  int IsCorrect()
   {
     if (Base == 0) return 0;
     return (Base->Ident == SEMIDENT);
   }

  // Запросить длину записи
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

  // Установить длину записи
  int Length(int length)
   {
     if (Base == 0) return 0;
     return (int)(Base->Length = (unsigned short int)length);
   }

 public :

 SEMANTIC *  Base;  // УКАЗАТЕЛЬ НА СЕМАНТИКУ (ПЕРЕМЕННАЯ ДЛИНА)

};

#define SEMNBUFFERSIZE (4*1024L)  // МИНИМАЛЬНЫЙ РАЗМЕР БУФЕРА CЕМАНТИКИ

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++ РЕДАКТИРОВАНИЕ СЕМАНТИКИ ОБ'ЕКТА ЭЛЕКТРОННОЙ КАРТЫ  ++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TSemnEdit : public SEMANTICDATA
{
 public :

  // Типы характеристик
  typedef enum type
   {
     STRDOS = SEMVSTRDOS, // CТРОКА СИМВОЛОВ (ASCIIZ),ОГРАНИЧЕННАЯ НУЛЕМ
     STRING = SEMVSTRING, // CТРОКА СИМВОЛОВ (ANSI),ОГРАНИЧЕННАЯ НУЛЕМ
     STRUNI = SEMVSTRUNI, // CТРОКА СИМВОЛОВ (UNICODE),ОГРАНИЧЕННАЯ НУЛЕМ
     CHAR   = SEMVCHAR,   // 1 БАЙТ   SIGNED CHAR
     SHORT  = SEMVSHORT,  // 2 БАЙТA  SIGNED SHORT
     LONG   = SEMVLONG,   // 4 БАЙТA  SIGNED INT
     DOUBLE = SEMVDOUBLE  // 8 БАЙТ   DOUBLE IEEE
   }
     TYPE;

   TSemnEdit() : SEMANTICDATA()
     {
       Access(0,0,0);
     }


   // Установить доступ к семантике объекта
   TSemnEdit(char HUGER * begin) : SEMANTICDATA()
     {
       Access(begin);
     }

   TSemnEdit(TObjectSemn semn) : SEMANTICDATA()
     {
       Access(semn.Address(),semn.Length());
     }

   // Установить доступ к семантике объекта
   TSemnEdit(char HUGER * begin,     // начало семантики
             long lengthsemantic,    // общая длина семантики
             long lengthbuffer = 0)  // общая длина буфера
           : SEMANTICDATA()
     {
       Access(begin,lengthsemantic,lengthbuffer);
     }

   ~TSemnEdit() { Access(0,0,0); }

   int Access(TObjectSemn semn)
     {
       return Access(semn.Address(),semn.Length());
     }

   int Access(char HUGER * begin,     // начало семантики
              long lengthsemantic,    // общая длина семантики
              long lengthbuffer = 0); // общая длина буфера


  // Запросить адрес записи
  char * Address() { return (char *)Base; }

  // Выделить память под минимальную запись семантики
  // Проинициализировать структуру данных
  // Создается идентификатор записи
  // Память автоматически освобождается в деструкторе
  // или при назначении другой области с помощью
  // SetBuffer(...), в том числе, SetBuffer(0,0).
  // При ошибке возвращает ноль
  int Allocate(int length = SEMNBUFFERSIZE);

  // Добавить характеристику (в конец семантики)
  // type    - предполагаемый тип значения (TYPE)
  // code    - код семантики
  // place   - адрес строки,содержащей значение семантики
  // maxsize - длина строки
  // При ошибке возвращает ноль
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

  // Добавить характеристику (в конец семантики)
  // При ошибке возвращает ноль
  TSemBlock * Append( TSemBlock * block);

  // Проверить реальную длину записи
  // и установить новое значение (КОНТРОЛЬ СТРУКТУРЫ ЗАПИСИ)
  // correct - признак необходимости корректировки длины
  //           записи семантики по реально определенной
  // При ошибке возвращает ноль
  int CheckLength(int correct = TRUE);

  // Проинициализировать запись семантки
  // Установить идентификатор записи и длину
  // При ошибке возвращает 0, при удаче 1
  int Clear()
   {
     if (Base == 0) return Allocate();
     Work.Length(0);
     Base->Ident   = SEMIDENT;
     Base->Length  = sizeof(SEMANTIC);
     return 1;
   }

  int Create() { return Clear(); }  // Синонимы

  // Запросить последовательный номер текущей характеристики
  int CurrentNumber() { return Work.Number; }

  // Запросить длину данных в записи
  int DataLength()
   {
     if ((Base == 0) || (Base->Ident != SEMIDENT)) return 0;
     int length = Base->Length;
     if (length > sizeof(SEMANTIC))
       return (length-sizeof(SEMANTIC));
     else
       return 0;
   }

  // Удалить текущую характеристику
  // Выбор характеристики - см. TWorkSemantic
  int Delete()
   {
     int ret;
     if (Base == 0) return 0;
     ret = Work.Delete();
     Base->Length = (unsigned short)(sizeof(SEMANTIC) + Work.Length());
     return ret;
   }

  // Вставить характеристику (перед текущим блоком )
  // При ошибке возвращает ноль
  TSemBlock * Insert( TSemBlock * block)
   {
     if ((block && Base) == 0) return 0;
     TSemBlock * newblock;
     newblock = Work.Insert(block);
     Base->Length = (unsigned short)(sizeof(SEMANTIC) + Work.Length());
     return newblock;
   }

  // Проверить корректность структуры записи
  int IsCorrect()
   {
     return ((Base && Base->Ident == SEMIDENT) &&
             (DataLength() == Work.Length()));
   }

  // Запросить признак редактирования данных
  int IsDirty() { return Work.IsDirty(); }

  // Установить признак редактирования данных
  int IsDirty(int dirty) { return Work.IsDirty(dirty); }

  // Запросить код объекта из служебной семантики
  // При ошибке возвращает ноль
  long int GetObjectExcode();

  // Запросить код объекта из служебной семантики
  // и удалить характеристику из семантики
  // При ошибке возвращает ноль
  long int GetObjectExcodeAndDelete();

  // Перейти на первую характеристику
  TSemBlock * GoFirst()
  { return Work.GoFirst(); }

  // Перейти на следующую характеристику из уже существующих
  // При ошибке возвращает ноль
 	TSemBlock * GoNext()
  { return Work.GoNext(); }

  // Перейти на характеристику с порядковым номером number
  // При ошибке возвращает ноль
  TSemBlock * GoNumber(int number)
  { return Work.GoNumber(number); }


  // Найти характеристику по коду семантики
  // При ошибке возвращает ноль
  TSemBlock * FindCode(int code)
  { return Work.FindCode(code); }

  // Поместить код объекта в служебную семантику
  // При ошибке возвращает ноль
  int PutObjectExcode(long int);

  // Запросить полную длину записи
  int Length()
   { if (Base && Base->Ident == SEMIDENT)
       return Base->Length;
     return 0;
   }

  // Загрузить запись семантики из заданной области
  // При ошибке возвращает ноль
  // При успешном выполнении - размер загруженной записи
  int Load(TObjectSemn semn);

  // Загрузить набор семантических характеристик
  // из заданной области
  // При ошибке возвращает ноль
  // При успешном выполнении - размер созданной записи
  int Load(TWorkSemantic * worksemn);

  // Заменить код характеристики у текущего блока
  // При ошибке возвращает ноль
  TSemBlock * ReplyCode(int code)
  { return Work.ReplyCode(code); }

  // Заменить значение характеристики у текущего блока
  TSemBlock * ReplyValue(char * value,int maxsize)
  { return Work.ReplyValue(value, maxsize); }

  // Установить описание буфера семантики
  char * SetBuffer(char * address,long int length)
   {
     Access(address,0,length);
     return address;
   }

  // Запросить значение характеристики в символьном виде (ANSI)
  // number - последовательный номер характеристики,
  // place - адрес размещения строки,
  // maxsize - максимальная длина строки
  // При ошибке возвращает ноль,
  // при успешном выполнении - адрес строки (равен place)
  char * StringValue(int number,char *place,int maxsize)
  { return Work.StringValue(number, place, maxsize); }

  
  // Заменить текущую характеристику
  // При ошибке возвращает ноль
  TSemBlock * Update(TSemBlock * block)
   {
     if ((block && Base) == 0) return 0;
     TSemBlock * newblock;
     newblock = Work.Update(block);
     Base->Length = (unsigned short)(sizeof(SEMANTIC) + Work.Length());
     return newblock;
   }

  // Перегруженные операции
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


// Инициализация данных по умолчанию
void _fastcall sedInit(SEMANTICDATA *semndata);

// Освободить память
void _fastcall sedFree(SEMANTICDATA *semndata);

// Выделить память под максимальную запись семантики
// Проинициализировать структуру данных
// Создается идентификатор записи
// Память автоматически освобождается в деструкторе
// или при назначении другой области с помощью
// Access(...)или SetBuffer(...), в том числе, SetBuffer(0,0).
// При ошибке возвращает ноль
int _fastcall sedAllocate(SEMANTICDATA *semndata, int length);

//  Установить доступ к семантике объекта
int _fastcall sedAccess(SEMANTICDATA *semndata,
                        char HUGER * begin,   // начало семантики
                        long lengthsemantic,  // общая длина семантики
                        long lengthbuffer);   // общая длина буфера

// Загрузить запись семантики из заданной области
// При ошибке возвращает ноль
// При успешном выполнении - размер загруженной записи
int _fastcall sedLoad(SEMANTICDATA *semndata, SEMANTIC * semn);

// Загрузить набор семантических характеристик
// из заданной области
// При ошибке возвращает ноль
// При успешном выполнении - размер созданной записи
int _fastcall sedLoadWorkSemn(SEMANTICDATA *semndata,
                              WORKSEMANTIC * worksemn);

// Добавить характеристику (в конец семантики)
// type    - предполагаемый тип значения (TYPE)
// code    - код семантики
// place   - адрес строки,содержащей значение семантики
// maxsize - длина строки
// При ошибке возвращает ноль
TSemBlock * _fastcall sedAppend(SEMANTICDATA *semndata,
                                int code,const char * place,int maxsize,
                               	int type);

// Добавить характеристику (в конец семантики)
// При ошибке возвращает ноль
TSemBlock * _fastcall sedAppendSemn(SEMANTICDATA *semndata,
                                    TSemBlock * block);

// Добавить числовую характеристику (в конец семантики)
// При ошибке возвращает ноль
TSemBlock * _fastcall sedAppendLongValue(SEMANTICDATA *semndata,
                                         int code, long int value);

// Добавить числовую характеристику (в конец семантики)
// При ошибке возвращает ноль
TSemBlock * _fastcall sedAppendDoubleValue(SEMANTICDATA *semndata,
                                           int code, double * value);

// Запросить код объекта из служебной семантики
// При ошибке возвращает ноль
long int _fastcall sedGetObjectExcode(SEMANTICDATA *semndata);

// Запросить код объекта из служебной семантики
// и удалить характеристику из семантики
// При ошибке возвращает ноль
long int _fastcall sedGetObjectExcodeAndDelete(SEMANTICDATA *semndata);

// Поместить код объекта в служебную семантику
// При ошибке возвращает ноль
ptrdiff_t _fastcall sedPutObjectExcode(SEMANTICDATA *semndata, long int code);

// Проверить реальную длину записи
// и установить новое значение (КОНТРОЛЬ СТРУКТУРЫ ЗАПИСИ)
// correct - признак необходимости корректировки длины
//           записи семантики по реально определенной
// При ошибке возвращает ноль
int _fastcall sedCheckLength(SEMANTICDATA *semndata, int correct);

// Проинициализировать запись семантки
// Установить идентификатор записи и длину
// При ошибке возвращает 0, при удаче 1
int _fastcall sedClear(SEMANTICDATA *semndata);

// Запросить длину данных в записи
int _fastcall sedDataLength(SEMANTICDATA *semndata);

// Удалить текущую характеристику
// Выбор характеристики - см. TWorkSemantic
int _fastcall sedDelete(SEMANTICDATA *semndata);

// Вставить характеристику (перед текущим блоком )
// При ошибке возвращает ноль
TSemBlock * _fastcall sedInsert(SEMANTICDATA *semndata, TSemBlock * block);

// Заменить текущую характеристику
// При ошибке возвращает ноль
TSemBlock * _fastcall sedUpdate(SEMANTICDATA *semndata, TSemBlock * block);

// Запросить значение семантической характеристики в символьном виде
// При ошибке возвращает ноль
char * _fastcall sedGetStringValue(SEMANTICDATA *semndata, int code,
                                   char * place, int size);

#endif  // MAPSEM_H


