
#if !defined(MAPSELC_H)
#define MAPSELC_H

#ifndef MAPSAMP_H
  #include "mapsamp.h"
#endif

#ifndef MAPINFO_H           
  #include "mapinfo.h"
#endif


// Условия поиска объекта по диапазону
// уникальных номеров на заданном листе

typedef struct KEYSELECT
{
  int  list;        // Номер листа в районе
  KEY  minkey;      // Нижняя граница поиска
  KEY  maxkey;      // Верхняя граница поиска
}
  KEYSELECT;

typedef struct RECORDID  // Описатель записи для сохранения условий
{                        // отбора объектов :
   int   Label;          // метка
   int   Length;         // длина
}
  RECORDID;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ПАРАМЕТРЫ ОТБОРА ДАННЫХ ЭЛЕКТРОННОЙ КАРТЫ ++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 enum TOTALSEEK                        
 {
    MSL_MAP = 1,      // ПРИЗНАК ПОИСКА В ДАННОЙ КАРТЕ
    MSL_VISIBLE = 2   // ПРИЗНАК ПОИСКА СРЕДИ ВИДИМЫХ НА КАРТЕ ОБЪЕКТОВ
 };

 enum DRAWOBJFLAG     // ПРИЗНАК ОТБОРА ГРАФИЧЕСКИХ ОБЪЕКТОВ :    
 {
    MSL_DRAW_ON   = 0,  // отобрать по общему фильтру,
    MSL_DRAW_ONLY = 1,  // отобрать только графические объекты,
    MSL_DRAW_OFF  = 2,  // исключить из отбора графические объекты
 };

// Проинициализировать параметры отбора объектов карты
void _fastcall mslSelectAll(MAPSELECT * data);

// Установить карту в условия отбора объектов
void _fastcall mslSetMap(MAPSELECT * data, TMap * map);

// Создать копию описания условий отбора объектов
void _fastcall mslSetSelectBySelect(MAPSELECT * dest, MAPSELECT * src);

// Установить условия отбора объектов
// по реальным объектам карты (листы,локализация,слои,виды объектов)
// Если задана карта(map), она замещает предыдущую (Map)
int _fastcall mslSetSelectByMap(MAPSELECT * data, TMap * map);

//  Определить сколько объектов на карте соответствуют
//  пересечению двух условий отбора объектов
//  view - условия отбора объектов (для той же карты)
//  При ошибке возвращает ноль
int _fastcall mslGetMarkObjectCount(MAPSELECT * data, MAPSELECT * view);

//  Определить сколько объектов на карте соответствуют
//  заданным условиям
//  При ошибке возвращает ноль
int _fastcall mslGetSelectObjectCount(MAPSELECT* data);

//  Обновить счетчик выбранных объектов при редактировании карты
void _fastcall mslUpdateSelectCountByObject(MAPSELECT* data, int number,
                                      TObjectHead * head, OBJECTDATA * objdata,
                                      SEMANTIC * semn, int operation);


// **************************************
//  Функции выбора объектов карты
// **************************************

// Проверка допустимости описания объекта
// (слой,локализация,вид объекта,номер,измерения,область)
// (слой,локализация,вид объекта,номер)
// Если объект не подходит условиям - возвращает ноль
int _fastcall mslCheckObjectHead(MAPSELECT * data, TObjectHead* head, int number);
int _fastcall mslCheckObjectBySelect(MAPSELECT * data, TObjectHead* head, int number);
int _fastcall mslCheckMapObject(MAPSELECT * data, TObjectHead * head,
                                OBJECTDATA* objdata, SEMANTIC* semn, int number);
int _fastcall mslVerifyMapObject(MAPSELECT * data, TObjectHead * head,
       										  OBJECTDATA* objdata, SEMANTIC* semn, int number); 

int _fastcall mslCheckObjectByInfo(MAPSELECT * data,
                                   TObjectInfo * info);

// Установить доступность слоя,локализации и кода объекта
void _fastcall mslObjectSetByObject(MAPSELECT * data,
                                    TObjectInfo * info);

// Проверить допустимость семантических характеристик объекта
// Если объект не подходит условиям - возвращает ноль
int _fastcall mslCheckSemantic(MAPSELECT * data, SEMANTIC * semn);



  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //  Методы доступа к описанию выбранных признаков объекта  +
  //  Если условие не выполнено - возвращается ноль          +
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//****************************************************
//  ПРАВИЛА ОТБОРА ПО ЛИСТАМ КАРТЫ
//****************************************************

// Сбросить лист
void _fastcall mslClearList(MAPSELECT * data, int number);

// Сбросить все листы
void _fastcall mslClearAllLists(MAPSELECT * data);

// Отметить лист
void _fastcall mslSetList(MAPSELECT * data, int number);

// Отметить все листы
void _fastcall mslSetAllLists(MAPSELECT * data);

// Опросить лист
int _fastcall mslListCheck(MAPSELECT * data, int number);

// Установить флаг отбора листов
int _fastcall mslSetListFlag(MAPSELECT * data, int flag);

//****************************************************
//  ПРАВИЛА ОТБОРА ПО ЛОКАЛИЗАЦИЯМ ОБЪЕКТОВ КАРТЫ
//****************************************************

// Отметить/сбросить/опросить локализацию
void _fastcall mslSetLocal(MAPSELECT * data, int number);

void _fastcall mslClearLocal(MAPSELECT * data, int number);

int _fastcall mslCheckLocal(MAPSELECT * data, int number);

// Cбросить все локализации
void _fastcall mslClearAllLocals(MAPSELECT * data);

// Выбрать все локализации
void _fastcall mslSetAllLocals(MAPSELECT * data);

// Установить флаг отбора по локализации
int _fastcall mslSetLocalFlag(MAPSELECT * data, int flag);

//**********************************************
//  ПРАВИЛА ОТБОРА ПО СЕГМЕНТАМ КАРТЫ
//**********************************************

// Отметить/сбросить сегмент
void _fastcall mslClearSegment(MAPSELECT * data, int number);

void _fastcall mslSetSegment(MAPSELECT * data, int number);

// Отметить/сбросить все сегменты
void _fastcall mslSetAllSegments(MAPSELECT * data);

void _fastcall mslClearAllSegments(MAPSELECT * data);

// Проверить, установлен ли сегмент
// При ошибке возвращает 2, при успешной проверке 1, иначе - 0
int _fastcall mslCheckSegment(MAPSELECT * data, int number);

// Установить флаг отбора по сегментам
int _fastcall mslSetSegmentFlag(MAPSELECT * data, int flag);

//**********************************************
//  ПРАВИЛА ОТБОРА ПО  ВИДАМ ОБЪЕКТОВ
//**********************************************

// Отметить/сбросить объект
void _fastcall mslSetObject(MAPSELECT * data, int number);

void _fastcall mslClearObject(MAPSELECT * data, int number);

// Отметить/сбросить все объекты
void _fastcall mslClearAllObjects(MAPSELECT * data);

void _fastcall mslSetAllObjects(MAPSELECT * data);

// Проверить, установлен ли данный объект
// При ошибке возвращает 2, при успешной проверке 1, иначе - 0
int _fastcall mslCheckObject(MAPSELECT * data, int number);

// Установить флаг отбора по видам объектов
int _fastcall mslSetObjectFlag(MAPSELECT * data, int flag);

// Установить флаг отбора графических объектов
int _fastcall mslSetDrawObjectFlag(MAPSELECT * data, int flag);

// Запросить флаг отбора графических объектов
int _fastcall mslGetDrawObjectFlag(MAPSELECT * data);

//****************************************************
//  ПРАВИЛА ОТБОРА ПО ИДЕНТИФИКАТОРАМ ОБЪЕКТОВ КАРТЫ
//****************************************************

// Отметить/запросить min и max идентификатор объекта

long int _fastcall mslSetKeyMin(MAPSELECT * data, unsigned long int key);

long int _fastcall mslGetKeyMin(MAPSELECT * data);

long int _fastcall mslSetKeyMax(MAPSELECT * data, unsigned long int key);

long int _fastcall mslGetKeyMax(MAPSELECT * data);

// Проверить, установлен ли идентификатор key
// При ошибке возвращает 2, при успешной проверке 1, иначе - 0
int _fastcall mslKeyCheck(MAPSELECT * data, unsigned long int key);

// Установить флаг отбора по идентификаторам объектов
int _fastcall mslSetKeyFlag(MAPSELECT * data, int flag);

//**********************************************
//  ПРАВИЛА ОТБОРА ПО ХАРАКТЕРИСТИКАМ ОБЪЕКТОВ
//**********************************************

// Сбросить все условия из списка характеристик
void _fastcall mslClearAllSemantics(MAPSELECT * data);

// Отметить/опросить характеристики объектов

// Установить флаг отбора по характеристикам
int _fastcall mslSetSemanticFlag(MAPSELECT * data, int flag);

// Сбросить все условия из списка характеристик
void _fastcall mslClearAllSemantics(MAPSELECT * data);

// Добавить условие в список
// При ошибке возвращает ноль, иначе - 1
int _fastcall mslSemanticAppend(MAPSELECT * data, int code, int semcode, char * value);

// Удалить условие из списка
// number - номер условия в списке (от 1 до SEMCOUNT)
// При ошибке возвращает ноль
int _fastcall mslSemanticDelete(MAPSELECT * data, int number);

// Запросить число заданных в списке условий
int _fastcall mslSemanticCount(MAPSELECT * data);

// Запросить код условия
// number - номер условия в списке (от 1 до SEMCOUNT)
// При ошибке возвращает ноль
int _fastcall mslSemanticCondition(MAPSELECT * data, int number);

// Запросить значение характеристики из списка условий
// number - номер условия в списке (от 1 до SEMCOUNT)
// При ошибке возвращает ноль, иначе - place
char * _fastcall mslSemanticValue(MAPSELECT * data,int number,char * place,int size);

// Запросить код семантики по номеру в списке
// number - номер условия в списке (от 1 до SEMCOUNT)
// При ошибке возвращает ноль
int _fastcall mslSemanticCode(MAPSELECT * data, int number);

// Запросить имя характеристики по номеру в списке
// number - номер условия в списке (от 1 до SEMCOUNT)
// При ошибке возвращает адрес пустой строки
const char * _fastcall mslSemanticCodeName(MAPSELECT * data, int number);

// Установить код объединяющего условия
// CMOR или CMAND
// При ошибке возвращает ноль
int _fastcall mslSemanticLink(MAPSELECT * data, int code);

// Запросить код объединяющего условия
// CMOR или CMAND
int _fastcall mslGetSemanticLink(MAPSELECT * data);

//****************************************************
//  ПРАВИЛА ОТБОРА ПО ИЗМЕРЕНИЯМ ОБЪЕКТОВ
//****************************************************

// Отметить/опросить отбор объектов по измерениям
// ----------------------------------------------
int _fastcall mslSetMeasureFlag(MAPSELECT * data, int flag);

int _fastcall mslSetMeasureLink(MAPSELECT * data, int code);

int _fastcall mslMeasureClear(MAPSELECT * data);

int _fastcall mslMeasureAdd(MAPSELECT * data, MEASUREMENT* pmeasure);

int _fastcall mslMeasureCheck(MAPSELECT * data, TObjectHead* head, DATAEDIT * objdata);

int _fastcall mslMeasureCondition(MAPSELECT * data, int number, int expression);

double _fastcall mslMeasureValue(MAPSELECT * data, int number, int expression);

//*****************************************************
//  ПРАВИЛА ОТБОРА ОБЪЕКТОВ ПО  УСТАНОВЛЕННОЙ ОБЛАСТИ
//*****************************************************

int _fastcall mslSetAreaFlag(MAPSELECT * data, int flag);

void _fastcall mslAreaFree(MAPSELECT * data);

// Установить параметры отбора по области:
// distance - размер области поиска(расстояние) в метрах
// info   - данные области (в метрах !)
// filter - флаг наличия фильтра объектов (1 - установить)
// inside - флаг отбора внутри области
// sample - флаг формирования списка объектов,удовлетворяющих
//          критериям отбора по области (0 - не формировать)
// При ошибке возвращает 0
int _fastcall mslAreaSet(MAPSELECT * data, double distance, TObjectInfo * info,
                         int filter, int inside, int sample, MAPSELECT* view);

// Создать список отобранных по области объектов
// При ошибке возвращает "0"
int _fastcall mslSetSampleByArea(MAPSELECT * data, MAPSELECT* view);

// Проверить принадлежность объекта заданной области
// При успешной проверке возвращает 1, иначе - 0
int _fastcall mslCheckByArea(MAPSELECT * data,TObjectHead* head,OBJECTDATA* objdata);

// Проверить принадлежность объекта заданной области
// 0 - не подходит
int _fastcall mslAreaCheck(MAPSELECT * data, TObjectHead* head, DATAEDIT * dataed);

// Проверить принадлежность объекта заданной области
int _fastcall mslAreaCheckByHead(MAPSELECT * data, TObjectHead* head);

// Проверить по габаритам принадлежность объекта заданной области
// 0 - объект не подходит
int _fastcall mslAreaCheckByFrame(MAPSELECT * data, TObjectHead* head,
                                  DOUBLEPOINT* viewposition);

// Измерить расстояние между объектом и областью
// Возвращает 0 при ошибке
int _fastcall mslToMeasureDistance(MAPSELECT * data, DATAEDIT * dataed,
                                   double* pdistance, DOUBLEPOINT* vpos);

// Проверить, входит ли область в объект
// Возвращает "0",если нет
int _fastcall mslIsAreaInside(MAPSELECT * data, DATAEDIT * dataed,DOUBLEPOINT* vpos);

//****************************************************
//  ПРАВИЛА ОТБОРА ПО ГАБАРИТАМ ОБЪЕКТОВ КАРТЫ
//****************************************************

// Сбросить габаритную рамку
int _fastcall mslFrameClear(MAPSELECT * data);

// Установить габаритную рамку
int _fastcall mslFrameSet(MAPSELECT * data, FRAME * frame);

// Проверка пересечения габаритных рамок
int _fastcall mslFrameCheck(MAPSELECT * data, FRAME * frame);
int _fastcall mslFrameCheckHead(MAPSELECT * data, TObjectDesc desc);


//****************************************************
//  ПРАВИЛА ОБОБЩЕННОГО ПОИСКА ДЛЯ КАРТЫ
//****************************************************

int _fastcall mslClearTotalSeek(MAPSELECT * data);

// Установить признаки обобщенного поиска
int _fastcall mslTotalSeekSelect(MAPSELECT * data, TMap* map, int visible);

// Запросить признак обобщенного поиска для карты
int _fastcall mslTotalSeekForMapSelect(MAPSELECT * data);

// Запросить признак обобщенного поиска по видимости объектов
int _fastcall mslVisibleSeekSelect(MAPSELECT * data);

// Запросить признаки обобщенного поиска
int _fastcall mslGetTotalSeekSelect(MAPSELECT * data);

// *********************************************
//  Функции запоминания состава объектов карты
// *********************************************

// Зафиксировать состав объектов карты
int _fastcall mslFreezeMapStaff(MAPSELECT * data);

// Сбросить данные о фиксированном составе карты
int _fastcall mslDefreezeMapStaff(MAPSELECT * data);

// *********************************************************
//  Функция инвертирования списка отобранных объектов карты
// *********************************************************

// Инвертировать список отобранных объектов
// При ошибке возвращает "0"

int _fastcall mslInvertSample(MAPSELECT * data);

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ КЛАСС : ОТБОР ДАННЫХ ЭЛЕКТРОННОЙ КАРТЫ +++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ИСПОЛЬЗУЕТСЯ ДЛЯ ВЫБОРА ОТОБРАЖАЕМЫХ ДАННЫХ,
// ПОИСКА ОБЪЕКТОВ С ЗАДАННЫМИ ПРИЗНАКАМИ
// (ЛИСТ,СЛОЙ,ЛОКАЛИЗАЦИЯ,ХАРАКТЕРИСТИКИ,ОБЛАСТЬ РАСПОЛОЖЕНИЯ)

class _DLLCLASS TMapSelect : public TSample
{
  public:

 // Признаки отбора данных
 enum FLAG  {
               ALL    = 0 ,     // ДАННЫЙ ПРИЗНАК НЕ ПРОВЕРЯЕТСЯ
               SELECT = 1       // ПРОВЕРИТЬ ПО ОПИСАНИЮ
            };

 enum CHECK {
               VIEW  = 1,       // ДАННЫЙ ПРИЗНАК ОТОБРАН
               SKIP  = 0        // ДАННЫЙ ПРИЗНАК ПРОПУСКАЕТСЯ
            };

 enum AREA  {
               RECT  = 1,       // ВЫБОР ПО ПРЯМОУГОЛЬНОМУ УЧАСТКУ
               POLY  = 2        // ВЫБОР ПО НАБОРУ КООРДИНАТ
            };

 enum TOTALSEEK
            {
               TS_MAP = MSL_MAP,        // ПРИЗНАК ПОИСКА В ДАННОЙ КАРТЕ
               TS_VISIBLE = MSL_VISIBLE // ПРИЗНАК ПОИСКА СРЕДИ ВИДИМЫХ НА КАРТЕ ОБЪЕКТОВ
            };

 enum CODE           // КОДЫ УСЛОВИЙ
  {
    PASS     = COM_PASS,  // ЛЮБОЕ ЗНАЧЕНИЕ ЗАПРЕЩЕНО
    LESS     = CMLESS,    // МЕНЬШЕ
    LESSEQ   = CMLESSEQ,  // МЕНЬШЕ ИЛИ РАВНО
    EQUAL    = CMEQUAL,   // РАВНО
    NOTEQ    = CMNOTEQ,   // НЕ РАВНО
    MORE     = CMMORE,    // БОЛЬШЕ
    MOREEQ   = CMMOREEQ,  // БОЛЬШЕ ИЛИ РАВНО
    ANY      = CMANY,     // ЛЮБОЕ ЗНАЧЕНИЕ ДОПУСТИМО

                     // ОБЪЕДИНЯЮЩЕЕ УСЛОВИЕ :
    OR       = CMOR,      // "ИЛИ" - ХОТЯ БЫ ОДНО ВЫПОЛНЯЕТСЯ
    AND      = CMAND,     // "И"   - ВСЕ ДОЛЖНЫ ВЫПОЛНИТЬСЯ
  };

  // Инициализация данных
  TMapSelect(TMap * map = 0);

  TMapSelect(TMapRsc * rsc);

  // Создать копию описания условий отбора объектов
  TMapSelect(TMapSelect * select) : TSample()
   {
     SetSelect(select);
   }

  ~TMapSelect();

  // Выбрать все данные о карте
  void Clear() { SelectAll(); }
  void SelectAll();

  // Установить карту
  void SetMap(TMap * map);

  TMap * GetMap() { return Map; }

  TMapRsc * GetRsc() { return Rsc; }

  // Запросить - есть ли условия для проверки
  int IsSelectActive() { return IsActive; }

  // Cкопировать условия отбора объектов
  void SetSelect(TMapSelect * select);

  // Запросить размер записи, необходимый для сохранения условий поиска
  int GetSelectRecordSize();

  // Сформировать запись для сохранения условий поиска
  // buffer - адрес записи
  // length - длина буфера,для размещения записи
  // При ошибке возвращает ноль
  int GetSelectRecord(char * buffer,int length);

  // Заполнить условия поиска из записи
  // buffer - адрес записи
  // length - длина записи или буфера,содержащего запись (не меньше записи)
  // При ошибке возвращает ноль
  int PutSelectRecord(char * buffer,int length);
  int PutSelectRecordOld(char * buffer,int length);

  // Определить сколько объектов на карте соответствуют
  // заданным условиям
  // При ошибке возвращает ноль
  int GetSelectObjectCount();

  //  Определить сколько объектов на карте соответствуют
  //  пересечению двух условий отбора объектов
  //  view - условия отбора объектов (для той же карты)
  //  При ошибке возвращает ноль
  int GetMarkObjectCount(TMapSelect * select);

  // Установить условия отбора объектов
  // по реальным объектам карты (листы,локализация,слои,виды объектов)
  // Если задана карта(map), она замещает предыдущую (Map)
  int SetSelectByMap(TMap * map = 0);

  // Обновить счетчик выбранных объектов при редактировании карты
  // operation : OO_DELETE, OO_APPEND, OO_UPDATE
  void _fastcall UpdateSelectCountByObject(int number,
                                 TObjectDesc desc, TObjectData data,
                                 TObjectSemn semn, int operation);

  // Инвертировать список отобранных объектов
  // При ошибке возвращает ноль      
  int _fastcall InvertSample();


  // -------------------------------------------------------------
  //  Методы выбора объектов карты
  // -------------------------------------------------------------

  // Проверка допустимости описания объекта
  // (слой,локализация,вид объекта,номер,измерения,область)
  // (слой,локализация,вид объекта,номер)
  // Если объект не подходит условиям - возвращает ноль
  int CheckObject(TObjectDesc desc, int number);
  int _fastcall CheckObject(TObjectInfo * info);
  int _fastcall CheckObject(TObjectDesc desc, TObjectData data,
                            TObjectSemn semn, int number);

  // Проверить допустимость семантических характеристик объекта
  // Если объект не подходит условиям - возвращает ноль
  int CheckSemantic(TObjectSemn semn);

  // -------------------------------------------------------------
  //  Методы доступа к описанию выбранных признаков объекта
  //  Если условие не выполнено - возвращается ноль
  // -------------------------------------------------------------

  // Установить доступность слоя,локализации и кода объекта
  void ObjectSet(TObjectInfo * info);

  // Отметить/опросить проверку по габаритам
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

  // Проверка пересечения габаритных рамок

  int FrameCheck(FRAME * frame);
  int FrameCheck(TObjectDesc desc);

  // Отметить/опросить локализацию
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

  // Отметить/опросить идентификатор объекта
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

  // Отметить/опросить вид объекта
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


  // Отметить/опросить сегмент
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


 // Отметить/опросить характеристики объектов
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

 // Добавить условие в список
 // При ошибке возвращает ноль, иначе - номер условия

 int SemanticAppend(int code,int semcode,char * value);

 // Удалить все условия из списка

 void SemanticClear();

 // Удалить условие из списка
 // number - номер условия в списке (от 1 до GetCount())
 // При ошибке возвращает ноль

 int SemanticDelete(int number);

 // Запросить число заданных в списке условий

 int SemanticCount()
    {
      return Condition.GetCount();
    }

 // Запросить код условия
 // number - номер условия в списке (от 1 до GetCount())
 // При ошибке возвращает ноль

 int SemanticCondition(int number)
    {
      return Condition.GetCondition(number);
    }

 // Запросить значение характеристики из условия
 // number - номер условия в списке (от 1 до GetCount())
 // При ошибке возвращает ноль, иначе - place

 char * SemanticValue(int number,char * place,int size);

 // Запросить значение характеристики из условия
 // number - номер условия в списке (от 1 до GetCount())
 // При ошибке возвращает ноль, иначе - place

 int SemanticCode(int number)
    {
      TSemBlock * block = Condition.GetValue(number);
      if (block == 0) return 0;
      return block->Code();
    }

 // Запросить значение характеристики из условия
 // number - номер условия в списке (от 1 до GetCount())
 // При ошибке возвращает адрес пустой строки

 const char * SemanticCodeName(int number);

 // Запросить код объединяющего условия
 // При ошибке возвращает ноль

 int SemanticLink()
    {
      return Condition.GetLinkCode();
    }

 // Установить код объединяющего условия
 // TMapSelect::OR или TMapSelect::AND
 // При ошибке возвращает ноль

 int SemanticLink(int code)
    {
      IsModify    = 1;
      return Condition.SetLinkCode(code);
    }

 // Отметить/опросить признак инверсии поиска                    

 int  InversionFlag(int flag)
    {
       IsModify    = 1;
       return (FlagInversion = flag);
    }

 int  InversionFlag()
    {
       return FlagInversion;
    }


 // Отметить/опросить область поиска
 // --------------------------------

 // Отметить/опросить область

 int AreaSelect(FLAG flag)
    {
      IsModify    = 1;
      return FlagArea = flag;
    }

 int AreaSelect()
    {
      return FlagArea;
    }

 // Сбросить параметры области
 void AreaClear();

 // Установить параметры отбора по области:
 // distance - размер области поиска(расстояние) в метрах
 // info   - данные области
 // filter - флаг наличия фильтра объектов (1 - установить)
 // inside - флаг отбора внутри области
 // sample - флаг формирования списка объектов,удовлетворяющих
 //          критериям отбора по области (0 - не формировать)

 void AreaSet(double distance, TObjectInfo * info,
              int filter = 0, int inside = 0, int sample = 0,
              TMapSelect* view=0);

 // Установить/опросить фильтр объектов

 int AreaFilter(int flag)
    {
      IsModify    = 1;
      return AreaParm.FilterFlag = flag;
    }

 int AreaFilter()
    {
       return AreaParm.FilterFlag;
    }

 //  Установить/запросить значение расстояния

 double AreaDistance(double dist)
    {
       return AreaParm.Distance = dist;
    }

 double AreaDistance()
    {
       return AreaParm.Distance;
    }

 // Установить данные области

 int LoadAreaSource(TObjectInfo *info);

 // Запросить данные области

 TDataEdit * AreaSource()
    {
       return (&(AreaParm.AreaData));
    }

 // Запросить габариты области

 DFRAME * AreaFrame()
    {
       if ( AreaSelect() == ALL ) return 0;
       return &(AreaParm.AreaFrame);
    }

 // Установить/опросить пределы поиска(внутри/вне области)
 // (flag = 1 - внутри, 0 - вне)

 int AreaInside(int flag)
    {
      IsModify    = 1;
      return AreaParm.InsideFlag = flag;
    }

 int AreaInside()
    {
       return AreaParm.InsideFlag;
    }

 // Проверить принадлежность объекта заданной области
 // 0 - не подходит

 int _fastcall AreaCheck(TObjectDesc desc, TDataEdit * data);

 int _fastcall AreaCheck(TObjectDesc desc);

 // Установить текст для поиска его в метрике подписи
 int TitleSet(char * text);

 protected :

 // Проверить по габаритам принадлежность объекта заданной области
 // 0 - объект не подходит

 int _fastcall AreaCheckByFrame(TObjectDesc desc,
                                DOUBLEPOINT* viewposition);

 // Измерить расстояние до объекта
 // При ошибке возвращает 0, иначе - 1,
 // по адресу distance заносится значение расстояния

 int _fastcall ToMeasureDistance(TDataEdit * data, double* distance,
                                 DOUBLEPOINT* viewposition);

 // Проверить вхождение области в объект
 // (Область входит в объект,если первая ее точка
 //  лежит внутри объекта)
 // Возвращает "0",если не входит

 int _fastcall IsAreaInside(TDataEdit * data,
                            DOUBLEPOINT* viewposition);

 public :

 // Создать список отобранных по области объектов
 // При ошибке возвращает "0"

 int SetSampleByArea(TMapSelect* view);

 // Установить идентификатор окна назначения
 // и код языка сообщений

 void SetWinHandle(HWND hwnd)
 {
   SendHandle = (long int) hwnd;
 }

 // Сбросить идентификатор окна назначения
 // и код языка сообщений

 void ClearWinHandle()
 {
   SendHandle = -1;
 }


 // Отметить/опросить выбранный лист
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

 // Отметить/опросить отбор объектов по измерениям
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
 //  Методы доступа к описанию признаков обобщенного поиска
 // -------------------------------------------------------------

 // Сбросить признаки обобщенного поиска
 int ClearTotalSeek();

 // Установить признаки обобщенного поиска
 int TotalSeekSelect(TMap* map = 0, int visible = 0);

 // Запросить признаки обобщенного поиска
 int TotalSeekSelect(void)
 {
   return FlagTotalSeek;
 }

 // Запросить признак обобщенного поиска для карты
 int TotalSeekForMapSelect()
 {
   return (FlagTotalSeek & TS_MAP);
 }

 // Запросить признак обобщенного поиска по видимости объектов
 int VisibleSeekSelect()
 {
   return (FlagTotalSeek & TS_VISIBLE);
 }

  // ************************************************************
  //                                                            *
  //         СПЕЦИАЛЬНЫЕ ОПЕРАЦИИ                               *
  //                                                            *
  // ************************************************************

public :

  operator HSELECT()
  {
    return (HSELECT) this;
  }
};

#endif // MAPSELC_H
