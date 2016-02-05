
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
  int    measure;      // Вид измерения:длина,площадь,периметр,высота  
  int    range;        // тип выражения(единственное значение/диапазон)
  int    condition1;   // первое условие отбора(>,<,>=,...)
  int    condition2;   // второе условие отбора(>,<,>=,...)
  double value1;       // первое значение(в дискретах, для высоты в метрах) 
  double value2;       // второе значение(в дискретах, для высоты в метрах)
}
  MEASUREMENT;

typedef struct _DLLCLASS AREAPARM    // Описание параметров отбора объектов по области
{
  AREAPARM() : AreaData() { Distance = 0; }

  double     Distance;     // Размер области поиска в метрах
  TDataEdit  AreaData;     // Метрика области в районе в дискретах
  DFRAME     AreaFrame;    // Габариты области в метрах
  int        FilterFlag;   // Выполнять/не выполнять фильтр объектов
  int        InsideFlag;   // Выполнить поиск внутри области (InsideFlag=1)
}
  AREAPARM;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ ПАРАМЕТРЫ ОТБОРА ПО ХАРАКТЕРИСТИКАМ (СЕМАНТИКАМ)  +++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 enum                // КОДЫ УСЛОВИЙ
  {
    COM_PASS     = 0,             // Любое значение запрещено
    COM_FLAGPASS = 1,             // Имеются условия с кодом COM_PASS
  };

typedef struct _DLLCLASS COMPARE     // ПАРАМЕТРЫ ОТБОРА ПО ХАРАКТЕРИСТИКАМ (СЕМАНТИКАМ)
{
  COMPARE()
  {
    Count = 0; Flags = CMOR; MinCount = 0;
    memset((void *)&Numbers[0],0,sizeof(Numbers));
  }

  int Count;                      // Число заданных условий (характеристик)

  TSemBlock Semantics[SEMCOUNT];  // Описания характеристик
  int Conditions[SEMCOUNT];       // Условия поиска (>,<,!=,...)
  int Numbers[SEMCOUNT];          // Условия поиска (>,<,!=,...)
  int Flags;                      // Обобщенные характеристики поиска
                                  // и связующее условие (&&,||)
  int MinCount;                   // Минимальное число характеристик,
                                  // которые будут сравниваться
}
  COMPARE;

// Проинициализировать параметры отбора объектов по семантикам
void _fastcall comInit(COMPARE * data);

// Удалить/Очистить  параметры отбора объектов по семантикам
void _fastcall comFree(COMPARE * data);

// Добавить условие в список семантик
// При ошибке возвращает ноль, иначе - номер условия
int _fastcall comAppend(COMPARE * data, int code, SEMBLOCK * block);

// Удалить условие из списка
// number - номер условия в списке
// При ошибке возвращает ноль
int _fastcall comDelete(COMPARE * data, int number);

// Запросить код условия по номеру
// number - номер условия в списке
// При ошибке возвращает ноль
int _fastcall comGetCondition(COMPARE * data, int number);

// Установить код объединяющего условия
// При ошибке возвращает ноль
int _fastcall comSetLinkCode(COMPARE* data, int code);

// Запросить сравниваемое значение условия
// number - номер условия в списке
// При ошибке возвращает ноль
TSemBlock * _fastcall comGetValue(COMPARE * data, int number);

//  Проверить допустимость семантических характеристик объекта
//  При успешной проверке возвращает 1, иначе - 0
int _fastcall comCheckSemantic(COMPARE * data, SEMANTIC * semn);


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ КЛАСС : УСЛОВИЯ ОТБОРА ПО СЕМАНТИКЕ ++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TCompare : public COMPARE
{
 public :

 TCompare() : COMPARE(){}

 ~TCompare() {}

 enum                // КОДЫ УСЛОВИЙ
  {
    PASS     = COM_PASS,  // ЛЮБОЕ ЗНАЧЕНИЕ ЗАПРЕЩЕНО
    LESS     = CMLESS,    // МЕНЬШЕ
    LESSEQ   = CMLESSEQ,  // МЕНЬШЕ ИЛИ РАВНО
    EQUAL    = CMEQUAL,   // РАВНО
    NOTEQ    = CMNOTEQ,   // НЕ РАВНО
    MORE     = CMMORE,    // БОЛЬШЕ
    MOREEQ   = CMMOREEQ,  // БОЛЬШЕ ИЛИ РАВНО
    ANY      = CMANY,     // ЛЮБОЕ ЗНАЧЕНИЕ ДОПУСТИМО
  };


 enum                // ОБОБЩАЮЩИЕ ФЛАЖКИ
  {
    FLAGPASS = COM_FLAGPASS, // ИМЕЮТСЯ УСЛОВИЯ С КОДОМ PASS

                     // ОБЪЕДИНЯЮЩЕЕ УСЛОВИЕ :
    OR       = CMOR,         // "ИЛИ" - ХОТЯ БЫ ОДНО ВЫПОЛНЯЕТСЯ
    AND      = CMAND,        // "И"   - ВСЕ ДОЛЖНЫ ВЫПОЛНИТЬСЯ
  };

 // Добавить условие в список
 // При ошибке возвращает ноль, иначе - номер условия

 int Append(int code,TSemBlock * block);

 // Проверить допустимость семантических характеристик объекта
 // Если объект не подходит условиям - возвращает ноль

 int CheckSemantic(TObjectSemn semn);

 // Удалить все условия из списка

 void Clear();

 // Удалить условие из списка
 // number - номер условия в списке (от 1 до GetCount())
 // При ошибке возвращает ноль

 int Delete(int number);

 // Запросить число заданных в списке условий

 int GetCount() { return Count; }

 // Запросить максимально возможное число условий

 int GetLimit() { return SEMCOUNT; }

 // Запросить код условия
 // number - номер условия в списке (от 1 до GetCount())
 // При ошибке возвращает ноль

 int GetCondition(int number);

 // Запросить сравниваемое значение условия
 // number - номер условия в списке (от 1 до GetCount())
 // При ошибке возвращает ноль

 TSemBlock * GetValue(int number);

 // Запросить код объединяющего условия
 // При ошибке возвращает ноль

 int GetLinkCode() { return (Flags & (AND | OR)); }

 // Установить код объединяющего условия
 // При ошибке возвращает ноль

 int SetLinkCode(int code);

};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++ ПАРАМЕТРЫ ОТБОРА ПО  ЗАДАННЫМ  ИЗМЕРЕНИЯМ  +++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 enum                // Вид измерения
  {
    PM_LENGTH      = 1,          // Длина
    PM_SQUARE      = 2,          // Площадь
    PM_PERIMETER   = 3,          // Периметр
    PM_LENGTHKM    = 4,          // Длина (км)
    PM_SQUAREKM    = 5,          // Площадь (кв. км)
    PM_PERIMETERKM = 6,          // Периметр (км)
    PM_SQUAREMM    = 7,          // Площадь (кв. мм)           
    PM_HEIGHT      = 10,         // Высота (м)
  } ;

 enum                // Тип выражения для поиска
  {
    PM_SINGLE = 1,          // Единственное значение
    PM_RANGE  = 2,          // Диапазон значений
  };


typedef struct _DLLCLASS MEASUREMENTDATA       // ПАРАМЕТРЫ ОТБОРА ПО ЗАДАННЫМ ИЗМЕРЕНИЯМ
{
  MEASUREMENTDATA()
  {
    MeasureCount = 0; Flag = CMOR;
    memset((void *)Measure, 0, sizeof(Measure));
  }

 int MeasureCount;                   // Число условий в списке
 MEASUREMENT  Measure[MEASURECOUNT]; // Описание условий
 int Flag;                           // Код связующего условия(OR\AND)
}
  MEASUREMENTDATA;

// Проинициализировать параметры отбора объектов по измерениям
void _fastcall pmInit(MEASUREMENTDATA * data);

// Удалить/Очистить  параметры отбора объектов по измерениям
void _fastcall pmFree(MEASUREMENTDATA * data);

// Запросить число условий в списке
int _fastcall pmCount(MEASUREMENTDATA * data);

// Добавить измерение в список
// При ошибке возвращает ноль
int _fastcall pmAdd(MEASUREMENTDATA * data, MEASUREMENT* pmeasure);

// Запросить вид измерения в списке по номеру number
// (длина,периметр,...)
int _fastcall pmMeasureKind(MEASUREMENTDATA * data, int number);

// Запросить вид выражения по номеру number в списке
// (единственное значение/диапазон значений)
int _fastcall pmRange(MEASUREMENTDATA * data, int number);

// Запросить код первого условия по номеру number в списке (>,<,...)
// При ошибке возвращает ноль
int _fastcall pmFirstCondition(MEASUREMENTDATA * data, int number);

// Запросить код второго условия по номеру number в списке (>,<,...)
// (только для диапазона значений)
// При ошибке возвращает ноль
int _fastcall pmSecondCondition(MEASUREMENTDATA * data, int number);

// Запросить первое значение измерения по номеру number в списке
// При ошибке возвращает ноль
double _fastcall pmFirstValue(MEASUREMENTDATA * data, int number);

// Запросить второе значение измерения по номеру number в списке
// При ошибке возвращает ноль
double _fastcall pmSecondValue(MEASUREMENTDATA * data, int number);

// Запросить код связующего условия
int _fastcall pmGetLinkCode(MEASUREMENTDATA * data);

// Установить код связующего условия
int _fastcall pmSetLinkCode(MEASUREMENTDATA * data, int code);

//  Проверить запись списка по номеру number
//  При успешной проверке возвращает 1, иначе - 0
int _fastcall pmTest(MEASUREMENTDATA * data, int number, double value);

//  Проверить соответствие условий и значений
//  При успешной проверке возвращает 1, иначе - 0
int _fastcall pmTestCondition(int condition, double target, double source);

//  Проверить запись списка по номеру number по высоте   
//  При успешной проверке возвращает 1, иначе - 0
int _fastcall pmTestByHeight(MEASUREMENTDATA * data, int number, DATAEDIT * metric);

// Проверить измерения объекта
// (DATAEDIT настроен на данные объекта desc)
// При успешной проверке возвращает 1, иначе - 0
int _fastcall pmMeasureCheck(MEASUREMENTDATA * data, TMap * map,
                             TObjectHead* head, DATAEDIT * metric);


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ КЛАСС : ПАРАМЕТРЫ ОТБОРА ПО ЗАДАННЫМ  ИЗМЕРЕНИЯМ  +++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TPlaneMeasure : public MEASUREMENTDATA
{
 public :

 TPlaneMeasure() : MEASUREMENTDATA() {;}

 ~TPlaneMeasure() {}

  enum                // КОДЫ УСЛОВИЙ
  {
    LESS     = CMLESS,    // МЕНЬШЕ
    LESSEQ   = CMLESSEQ,  // МЕНЬШЕ ИЛИ РАВНО
    EQUAL    = CMEQUAL,   // РАВНО
    NOTEQ    = CMNOTEQ,   // НЕ РАВНО
    MORE     = CMMORE,    // БОЛЬШЕ
    MOREEQ   = CMMOREEQ,  // БОЛЬШЕ ИЛИ РАВНО
  };

  enum                // Вид измерения
  {
    LENGTH      = PM_LENGTH,          // Длина
    SQUARE      = PM_SQUARE,          // Площадь
    PERIMETER   = PM_PERIMETER,       // Периметр
    LENGTHKM    = PM_LENGTHKM,        // Длина (км)
    SQUAREKM    = PM_SQUAREKM,        // Площадь (кв. км)
    PERIMETERKM = PM_PERIMETERKM,     // Периметр (км)
    HEIGHT      = PM_HEIGHT,          // Высота (м)
  };

  enum                // Тип выражения для поиска
  {
    SINGLE = PM_SINGLE,   // Единственное значение
    RANGE  = PM_RANGE,    // Диапазон значений
  };

  enum                // ОБЪЕДИНЯЮЩЕЕ УСЛОВИЕ :
  {
    OR       = CMOR,      // "ИЛИ" - ХОТЯ БЫ ОДНО ВЫПОЛНЯЕТСЯ
    AND      = CMAND,     // "И"   - ВСЕ ДОЛЖНЫ ВЫПОЛНИТЬСЯ
  };


 // Добавить измерение в список

 int Add(MEASUREMENT* pmeasure);

 // Удалить все условия из списка

 void Clear();

 // Число условий в списке

 int Count();

 // Вид измерения в списке по номеру number
 // (длина,периметр,...)

 int MeasureKind(int number);

 // Вид выражения по номеру number в списке
 // (единственное значение/диапазон значений)

 int Range(int number);

 // Код первого условия по номеру number в списке (>,<,...)

 int FirstCondition(int number);

 // Код второго условия по номеру number в списке (>,<,...)
 // (только для диапазона значений)

 int SecondCondition(int number);

 // Первое значение измерения по номеру number в списке

 double FirstValue(int number);

 // Второе значение измерения по номеру number в списке
 // (только для диапазона значений)

 double SecondValue(int number);

 // Запросить/установить код связующего условия

 int GetLinkCode();

 int SetLinkCode(int code);

 // Проверить измерения объекта
 // (TDataEdit настроен на данные указанного объекта)
 //  При успешной проверке возвращает 1, иначе - 0

 int _fastcall MeasureCheck(TMap * map, TObjectDesc desc, TDataEdit * data);

 //  Проверить запись списка по номеру number
 //  При успешной проверке возвращает 1, иначе - 0

 int Test(int number, double value);

 //  Проверить соответствие условий и значений
 //  При успешной проверке возвращает 1, иначе - 0

 int TestCondition(int condition, double target, double source);

 //  Проверить запись списка по номеру number по высоте   
 //  При успешной проверке возвращает 1, иначе - 0

 int TestByHeight(int number, TDataEdit * data);

};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ КЛАСС : ОТБОР ОБ'ЕКТОВ КАРТЫ +++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef class _DLLCLASS TSample
{
 public :

 TSample(TMap* map = 0);

 ~TSample();

 // Добавить отбираемый объект в список
 // number - номер объекта в листе карты
 // list   - номер листа в карте
 // При ошибке возвращает ноль

 int AppendSample(int number, int list = 1);

 // Удалить объект из списка
 // number - номер объекта в листе карты
 // list   - номер листа в карте
 // При ошибке возвращает ноль

 int DeleteSample(int number, int list = 1);

 // Выполнить настройку класса на указанный элемент списка
 // Если заданного номера нет - выбирается следующий
 // в данном листе в соответствии с flag (WO_NEXT, WO_BACK)
 // При ошибке возвращает ноль

 int _fastcall Adjustment(int number, int list = 1, int flag = 0);

 // Проинициализировать класс отбора объектов карты

 void ClearSample();

 // Проверить наличие объекта в списке
 // Возвращает номер в списке
 // Если объекта нет - возвращает ноль

 int CheckSample(int number, int list);

 // Проверить наличие спискa для листа list
 // Если спискa нет - возвращает ноль

 int CheckSample(int list);

 // Запросить число объектов в списке для листа list

 int GetSamplesCount(int list = 1);

 // Запросить первый элемент списка объектов для листа list
 // Лист list становится текущим
 // Если листа нет - возвращает ноль

 int GetFirstSample(int list = 1);

 // Запросить последний элемент списка объектов для текущего листа
 // При ошибке - возвращает ноль

 int GetLastSample(int list = 1);

 // Запросить очередной элемент списка объектов для текущего листа
 // Если объекта нет - возвращает ноль

 int GetNextSample(int list);

 // Запросить предыдущий элемент списка объектов для текущего листа
 // Если предыдущего объекта нет - возвращает ноль

 int GetPrevSample(int list);

 // Запросить элемент списка объектов по номеру для текущего листа
 // При ошибке - возвращает ноль

 int GetSample(int number, int list);

 // Запросить - есть ли отобранные объекты

 int IsSample() { return Sample; }
 int SampleSelect() { return Sample; }

 // Запросить число листов в списке

 int GetSampleListCount() { return Count; }

 // Запросить адрес области памяти

 char * GetSampleMemory() { return Memory; }

 // Запросить размер области памяти

 int GetSampleMemoryLength() { return Length; }

 // Запросить размер занятой области памяти

 int GetSampleMemorySize() { return Size; }

 protected :

 // Выделить память под список отобранных объектов карты
 // При ошибке возвращает ноль

 int Allocate(int size);

 // Скопировать переданный список отобранных объектов карты
 // При ошибке возвращает ноль

 int Load(TSample * sample);

 // Определить позицию нового элемента

 int * SeekPosition(int * begin, int number);

 // Запросить адрес списка для листа list
 // При list = 0 возвращает адрес списка текущего листа
 // При ошибке возвращает ноль

 int * SeekSample(int list = 0);

 public :

 TMap     * Map;          // Карта, на которой выбираются объекты

 int        Count;        // Max число отобранных листов
 char *     Memory;       // Адрес выделенной области памяти
 int        Length;       // Размер выделенной области памяти
 int        Size;         // Длина записи
 int        ListSize;     // Длина списка листов
 int        Item;         // Индекс в списке объектов для листа List
 int        CheckItem;    // Индекс, на котором не выполнилось условие CheckSample
 int        Sample;       // Признак условий поиска по номерам  

 TBitSet256 Segments;     // Описание отобранных сегментов данных
 TBitSet32  Locals;       // Описание отобранных локализаций данных
 TBitSet64K Objects;      // Описание отобранных видов объектов
 TBitSet4K  Lists;        // Описание отобранных листов карты

 int FlagSegments;        // Признак отбора сегментов
 int FlagLocals;          // Признак отбора локализаций
 int FlagObjects;         // Признак отбора объектов
 int FlagLists;           // Признак отбора листов
 int FlagSemantics;       // Признак отбора характеристик объектов
 int FlagKeys;            // Признак отбора по номерам
 int FlagArea;            // Признак отбора по заданному участку
                          // местности произвольной конфигурации
 int FlagFrame;           // Признак отбора по габаритам объекта
                          // (попадание в заданный прямоугольник)
 int FlagMeasure;         // Признак отбора по измерениям объектов
 int FlagTotalSeek;       // Признаки обобщенного поиска           
 int FlagInversion;       // Признак инверсии поиска по области    
 int FlagFrozenMap;       // Признак фиксирования состава карты    
 int FlagDrawObjects;     // Признак отбора графических объектов : 
								  // 0 - отбор по "общему" фильтру,
								  // 1 - отобрать только графические объекты,
								  // 2 - не отбирать графические объекты.

 KEY KeyMini;             // Минимальное допустимое значение номера объекта
 KEY KeyMaxi;             // Максимальное допустимое значение номера объекта

 FRAME Frame;             // Габаритная рамка для отсеивания объектов
                          // по их габаритам на местности

 AREAPARM  AreaParm;      // Параметры отбора объектов по области

 TCompare Condition;      // Условия поиска объектов
                          // по семантическим характеристикам
 TPlaneMeasure Measure;   // Условия отбора объектов по измерениям

 int          IsModify;   // Признак изменения условий

 int          MarkCount;  // Счетчик объектов по пересечению условий
 int          SelectCount;// Счетчик объектов по заданным условиям

 TMapSelect * MarkSelect; // Условия отображения в последнем запросе

 int          MapMode;    // Состояние данных

 long int  SendHandle;    // Идентификатор окна сообщений

 long int  FrozenCount;   // Число зафиксированных объектов листа карты  

 long int *AddrFrozenCount;// Адрес массива значений числа объектов по листам карты

 TMapRsc * Rsc;           // Классификатор (когда карта недоступна)

 int       MapComplex;    // Признак одновременного учета Sample с друг.пар-ми

 int       FlagTitle;      // Признак поиска текста подписи
 char      TitleText[255]; // Текст подписи для поиска

 int       IsActive;       // Признак установки условий поиска  

}
  TSample;

typedef TSample MAPSELECT;

// Выделить память под список отобранных объектов карты
// При ошибке возвращает ноль
int _fastcall smAllocate(MAPSELECT * data, int size);

// Скопировать переданный список отобранных объектов карты
// При ошибке возвращает ноль
int _fastcall smLoad(MAPSELECT * dest, MAPSELECT * data);

// Добавить объект в список
// number - номер объекта в листе карты
// list   - номер листа в карте
// При ошибке возвращает ноль
int _fastcall smAppendSample(MAPSELECT * data, int number, int list);

// Проверить наличие объекта в списке
// Возвращает номер в списке или 0
int _fastcall smCheckSample(MAPSELECT * data, int number, int list);

// Проверить наличие спискa для листа list
// Если спискa нет, возвращает ноль
int _fastcall smCheckSampleByList(MAPSELECT * data, int list);

// Определить позицию нового элемента в списке
// begin  - адрес начала списка для нового элемента
// number - номер нового элемента
// Возвращает адрес для записи нового элемента
int* _fastcall smSeekPosition(MAPSELECT * data, int * begin, int number);

// Запросить первый элемент списка объектов для листа list
// (номер первого объекта для выбора)
// Возвращает номер первого объекта в списке для листа list
// Если для листа отсутствует списк или при ошибке возвращает ноль
int _fastcall smGetFirstSample(MAPSELECT * data, int list);

// Запросить последний элемент списка объектов для листа list
// Лист list становится текущим
// При ошибке возвращает ноль
int _fastcall smGetLastSample(MAPSELECT * data, int list);

// Запросить очередной элемент списка объектов для текущего листа
// При ошибке возвращает ноль
int _fastcall smGetNextSample(MAPSELECT * data, int list);

// Запросить число объектов в списке для листа list
// При отсутствии списка для листа list и при ошибке возвращает ноль
int _fastcall smGetSamplesCount(MAPSELECT * data, int list);

// Запросить адрес списка по номеру листа
// При list = 0 возвращает адрес списка текущего листа
// При ошибке возвращает ноль
int * _fastcall smSeekSample(MAPSELECT * data, int list);

// Запросить предыдущий элемент списка объектов для текущего листа
// Если предыдущего объекта нет, возвращает ноль
int _fastcall smGetPrevSample(MAPSELECT * data, int list);

// Запросить элемент списка объектов по номеру для текущего листа
// При ошибке возвращает ноль
int _fastcall smGetSample(MAPSELECT * data, int number, int list);

// Выполнить настройку на указанный объект
// При ошибке возвращает ноль
int _fastcall smAdjustment(MAPSELECT * data, int number, int list, int flag);

// Удалить объект из списка
// number - номер объекта в листе карты
// list   - номер листа в карте
// При ошибке возвращает ноль
int _fastcall smDeleteSample(MAPSELECT * data, int number, int list);

#endif  // MAPSAMP_H

