
#ifndef MAPLSTBS_H
#define MAPLSTBS_H

#ifndef MAPVERSN_H
  #include "mapversn.h"
#endif

#ifndef MAPREGIS_H
  #include "mapregis.h"  // ФОРМУЛЯР ЭЛЕКТРОННОЙ КАРТЫ (ЭК)
#endif

#ifndef MAPDATA_H
  #include "mapdata.h"
#endif

#ifndef MAPHDR_H
  #include "maphdr.h"
#endif

#ifndef MAPDAT_H
  #include "mapdat.h"
#endif

#ifndef MAPSEM_H
  #include "mapsem.h"
#endif

#ifndef MAPDRW_H
  #include "mapdrw.h"
#endif

#ifndef MAPVEC_H
  #include "mapvec.h"
#endif

enum // Идентификаторы файлов
{
  LABEL_HDR = 0x00524448L,  // HDR0
  LABEL_DAT = 0x00544144L,  // DAT0
  LABEL_DRW = 0x00575244L,  // DRW0
  LABEL_VEC = 0x00434556L,  // VEC0

  LABEL_HDR_TURN = 0x48445200L,  // 0RDH
  LABEL_DAT_TURN = 0x44415400L,  // 0TAD
  LABEL_DRW_TURN = 0x44525700L,  // 0WRD
  LABEL_SEM_TURN = 0x53454D00L,  // 0MES    
  LABEL_VEC_TURN = 0x56454300L,  // 0CEV
};

#define Degree8Dec (100000000L)   // 10 ** 8

// ===============================================================

typedef struct PART
{
  char * ADDR;           // АДРЕС ОБЛАСТИ ПАМЯТИ
  unsigned long   MIN;   // НАЧАЛЬНОЕ СМЕЩЕНИЕ БЛОКА
  unsigned long   MAX;   // КОНЕЧНОЕ СМЕЩЕНИЕ БЛОКА
}
  PART;


typedef struct LISTSTACK    
{
  int    Number;      // НОМЕР ЛИСТА
  unsigned int Count; // НОМЕР ОБРАЩЕНИЯ К ЛИСТУ
  int    Mode;        // РЕЖИМ ОТКРЫТИЯ ФАЙЛА
  HANDLE Head;        // ИДЕНТИФИКАТОР ФАЙЛА HDR
  HANDLE Data;        // ИДЕНТИФИКАТОР ФАЙЛА DAT
  HANDLE Semn;        // ИДЕНТИФИКАТОР ФАЙЛА SEM
  HANDLE Draw;        // ИДЕНТИФИКАТОР ФАЙЛА DRW
  HANDLE BackHead;    // ИДЕНТИФИКАТОР ФАЙЛА Back HDR
  HANDLE BackData;    // ИДЕНТИФИКАТОР ФАЙЛА Back DAT
  HANDLE BackSemn;    // ИДЕНТИФИКАТОР ФАЙЛА Back SEM
  HANDLE BackDraw;    // ИДЕНТИФИКАТОР ФАЙЛА Back DRW
  int    Reserve;     // РЕЗЕРВ
}
 LISTSTACK;

// МАКСИМАЛЬНОЕ ЧИСЛО ОДНОВРЕМЕННО ОТКРЫТЫХ ЛИСТОВ
#define LISTSTACKLIMIT  12

class _DLLCLASS TObjectInfo;
class _DLLCLASS TMap;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  БУФЕР ЗАГОЛОВКОВ АКТИВНОГО ЛИСТА +++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#if defined(COMPACTGIS) || defined(MINIDATA) || defined(WINCE)
#define  HBLOCKNUMB  2L            // ЧИСЛО БЛОКОВ
#define  BLOCKSIZE  (48*1024L)     // РАЗМЕР БЛОКА (48 Кб)
#else
#define  HBLOCKNUMB  32L           // ЧИСЛО БЛОКОВ          
#define  BLOCKSIZE  (96*1024L)     // РАЗМЕР БЛОКА (96 Кб)  
#endif

#define  HMINSIZE   (BLOCKSIZE*3L) // МИНИМАЛЬНЫЙ РАЗМЕР

typedef struct HEADBUFFER
{
 char *        Memory;        // АДРЕС ОБЛАСТИ ПАМЯТИ ПОД МЕТРИКУ
 HANDLE        File ;         // ИДЕНТИФИКАТОР ФАЙЛА ДАННЫХ
 int           Number ;       // ЧИСЛО БЛОКОВ
 int           Last;          // ПОСЛЕДНИЙ ОБРАБОТАННЫЙ БЛОК
 unsigned long Size;          // РАЗМЕР ОБЛАСТИ ПАМЯТИ
 unsigned long BlockSize;     // РАЗМЕР БЛОКА ДАННЫХ
 PART Part[HBLOCKNUMB];       // ОПИСАНИЕ БЛОКОВ ДАННЫХ
}
 HEADBUFFER;

// Инициализировать переменные буфера заголовков
void _fastcall hbInit(HEADBUFFER * buffer);

// Освободить буфер заголовков
void _fastcall hbFree(HEADBUFFER * buffer);

// Очистить блоки памяти буфера заголовков
void _fastcall hbClear(HEADBUFFER * buffer);

// Обновить заголовок в буфере
void _fastcall hbUpdate(HEADBUFFER * buffer, int number, char * record);

// Запросить память,инициализировать буфер заголовков
int _fastcall hbAllocHeadBuffer(HEADBUFFER * buffer, unsigned long int size);

// Запросить адрес данных по номеру записи заголовка
char * _fastcall hbGetDataAddr(HEADBUFFER * buffer, int number);

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  БУФЕР ДАННЫХ АКТИВНОГО ЛИСТА +++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#if defined(COMPACTGIS) || defined(MINIDATA) || defined(WINCE)
#define DBLOCKNUMB 1        // ЧИСЛО БЛОКОВ
#else
#define DBLOCKNUMB 8        // ЧИСЛО БЛОКОВ
#endif

#define DBLOCKSIZE 0x10000L // РАЗМЕР БЛОКА (64 Кб) 

typedef struct DATABUFFER
{
 char *        Memory;        // АДРЕС ОБЛАСТИ ПАМЯТИ ПОД МЕТРИКУ
 HANDLE        File ;         // ИДЕНТИФИКАТОР ФАЙЛА ДАННЫХ
 int           Number ;       // ЧИСЛО БЛОКОВ
 int           Last;          // ПОСЛЕДНИЙ ОБРАБОТАННЫЙ БЛОК
 unsigned long Size;          // РАЗМЕР ОБЛАСТИ ПАМЯТИ
 PART Part[DBLOCKNUMB];       // ОПИСАНИЕ БЛОКОВ ДАННЫХ
}
 DATABUFFER;

// Инициализировать переменные буфера данных
void _fastcall dbInit(DATABUFFER * buffer);

// Освободить буфер данных
void _fastcall dbFree(DATABUFFER * buffer);

// Очистить блоки памяти буфера данных
void _fastcall dbClear(DATABUFFER * buffer);

//  Запросить память, инициализировать буфер данных
int _fastcall dbAllocDataBuffer(DATABUFFER * buffer, unsigned long int size);

// Запросить адрес данных по смещению
char * _fastcall dbGetDataAddr(DATABUFFER * buffer, unsigned long int offset);


char * _fastcall dbGetSemnAddr(DATABUFFER * buffer, unsigned long int offset);

#if defined(COMPACTGIS) || defined(MINIDATA) || defined(WINCE)
#define LDBLOCKNUMB 4         // ЧИСЛО БЛОКОВ
#else
#define LDBLOCKNUMB 64        // ЧИСЛО БЛОКОВ                  
#endif

//#define LDBLOCKSIZE (DATALENGTHLIMIT + 1024) // РАЗМЕР БЛОКА 
#define LDBLOCKSIZE (256*1024L)                // РАЗМЕР БЛОКА 

typedef struct LONGBUFFER
{
 char *        Memory;        // АДРЕС ОБЛАСТИ ПАМЯТИ ПОД МЕТРИКУ
 HANDLE        File ;         // ИДЕНТИФИКАТОР ФАЙЛА ДАННЫХ
 int           Number ;       // ЧИСЛО БЛОКОВ
 int           Last;          // ПОСЛЕДНИЙ ОБРАБОТАННЫЙ БЛОК
 int           BlockSize;     // РАЗМЕР БЛОКА ДАННЫХ
 unsigned long Size;          // РАЗМЕР ОБЛАСТИ ПАМЯТИ
 PART Part[LDBLOCKNUMB];      // ОПИСАНИЕ БЛОКОВ ДАННЫХ
}
 LONGBUFFER;

// Инициализировать переменные буфера данных
void _fastcall lbInit(LONGBUFFER * buffer);

// Освободить буфер данных
void _fastcall lbFree(LONGBUFFER * buffer);

// Очистить блоки памяти буфера данных
void _fastcall lbClear(LONGBUFFER * buffer);

//  Запросить память, инициализировать буфер данных
int _fastcall lbAllocDataBuffer(LONGBUFFER * buffer,
                                unsigned long int size, int notlimit);

// Запросить адрес данных по смещению
char * _fastcall lbGetDataAddr(LONGBUFFER * buffer, unsigned long int offset);

#define SemnZero 0  

typedef struct
{
  char Value[64];
}
  SETID;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  АКТИВНЫЙ ЛИСТ ЭЛЕКТРОННОЙ КАРТЫ  +++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TMapList
{
 public :

 TMapList();
 ~TMapList();


 /***************************************************************
 *                                                              *
 *      ОТКРЫТЬ/СОЗДАТЬ ЛИСТ КАРТЫ                              *
 *                                                              *
 ***************************************************************/

public :

 // Заполнить описание листа и скопировать файлы данных
 // При ошибке возвращает ноль
 int CopyList(TMap * map, int number, LISTREGISTER * mapreg,
              char * path);

 int CopyList(TMap * map, int number, TListRegister * mapreg,
              char * path)
 {
   return CopyList(map, number, (LISTREGISTER *)mapreg, path);
 }

 //  Заполнить описание листа и скопировать файлы данных
 //  с пересчетом координат
 //  При ошибке возвращает ноль                 // Не переносить на С

 int CopyListAndChange(TMap * map, char * prefix,
                       TMap * srcmap, int list, HWND handle);

 // Заполнить описание листа данными из формуляра
 // Создать пустые файлы данных
 // map     - карта, в которой создается лист
 // number  - номер создаваемого листа
 // mapreg  - формуляр листа
 // При ошибке возвращает ноль
 int CreateList(TMap * map, int number, LISTREGISTER * mapreg);
 int CreateList(TMap * map, int number, TListRegister * mapreg)
 {
   return CreateList(map, number, (LISTREGISTER *)mapreg);
 }

 // Удалить все объекты листа                      
 // При ошибке возвращает ноль
 int ClearList(TMap * map, int number);

 // Закрыть лист района работ
 // mode - режим закрытия листа,
 // если больше 0, освобождается память под буферы данных,
 // если меньше 0 - закрывается текущий лист
 // (обычно выполняется в деструкторе)
 void Close(int mode = -1);

 // Проверить доступность листа
 // При ошибке возвращает ноль
 int IsActive() { return ( List != 0 ); }

 // Заполнение описания листа данными из формуляра
 int ListRegister(int list, LISTREGISTER * mapreg);
 int ListRegister(int list, TListRegister * mapreg)
  {
    return ListRegister(list,(LISTREGISTER *)mapreg);
  }

 // Установка/возврат номенклатуры листа
 const char* Nomenclature(const char* nomenclature);
 const char* Nomenclature();

 // Установка/возврат названия листа
 const char* Name(const char* name);
 const char* Name();

 // Открыть заданный лист в районе работ
 // При ошибке возвращает ноль
 int Open(TMap * map, int number);

 // Выделить под лист максимальную область памяти
 // При ошибке возвращает ноль
 int AllocateNotLimit(TMap * map, int number);

 // Скорректировать метрику объектов листа в дискретах
 // Подвинуть объекты листа в заданном направлении
 // При ошибке возвращает ноль
 int ReplaceListObjects(double deltaX, double deltaY);

 /***************************************************************
 *                                                              *
 *      ЗАПРОС / УСТАНОВКА ДОСТУПА К ОПИСАНИЮ ЛИСТА             *
 *                                                              *
 ***************************************************************/


public :

 // Запросить число объектов в листе
 int Count();

 // Запросить имя файла данных
 const char * DataName();

 // Запросить имя файла графики
 const char * DrawName();

 // Запросить код ошибки выполнения последней операции
 long int Error() { return (LastError); }

 // Запросить имя файла справочных данных (заголовков) объектов
 const char * HeadName();

 // Запрос/Установка признака обновления габаритов для Site
 int IsBorderUpdate() { return BorderUpdate; }
 int IsBorderUpdate(int mode) { return BorderUpdate = mode; }

 // Запрос - описание листа редактировалось ?
 int IsDirty() { return Isdirty; }
 int IsDirty(int dirty) { return (Isdirty = dirty); }

 // Запросить/Установить признак запуска специальной сортировки данных
 int IsFreeAppend() { return FreeAppend; }
 int IsFreeAppend(int start) { return FreeAppend = start; }

 // Запросить/Установить признак отсортированных данных
 int IsSorted();
 int IsSorted(int sorted);

 // Запрос - можно ли редактировать лист ?
 int IsWrite() { return (FileAccess & GENERIC_WRITE); }

 // Запросить номер листа
 int Number() { return List; }

 // Запросить имя файла семантики
 const char * SemnName();

 // Установить предельное число объектов в листе
 // (для модели данных TINYDATA)
 int SetObjectsLimit(int limit);

 // Установить код ошибки выполнения последней операции
 long int Error(int error) { return (LastError = error); }

 // Создать файл семантики и выделить память
 int CreateSemnFile();

protected :

 // Создать файл метрики и выделить память
 int CreateDataFile();

 // Создать файл графики и выделить память
 int CreateDrawFile();

 // Запросить путь к служебной директории (LOG)
 const char * PathLOG();

 /***************************************************************
 *                                                              *
 *         ЗАПРОС СПРАВОЧНЫХ ДАННЫХ О ЛИСТЕ                     *
 *                                                              *
 ***************************************************************/

public :

 // Запросить/установить	дату создания файлов листа
 const char* CreationDate(const char* date);
 const char* CreationDate();

 // Запросить/установить	дату съемки местности
 const char* Date(const char* date);
 const char* Date();

 // Запросить/установить	дату склонения
 const char* DateAngle(const char* date);
 const char* DateAngle();

 // Установка/возврат вида исходного материала
 int MaterialKind(int kind);
 int MaterialKind();

 // Установка/возврат типа исходного материала
 int MaterialType(int type);
 int MaterialType();

 // Установка/возврат магнитного склонения
 double MagneticAngle(double value);
 double MagneticAngle();

 // Установка/возврат годового изменения магнитного склонения
 double YearMagneticAngle(double value);
 double YearMagneticAngle();

 // Установка/возврат среднего сближения меридианов
 double MeridianAngle(double value);
 double MeridianAngle();

 // Установка/возврат высоты сечения рельефа
 long int ReliefHeight(long int height);
 long int ReliefHeight();

 /***************************************************************
 *                                                              *
 *        Обработка резервных файлов ...\LOG\... ^DA,^SE,^HD    *
 *    (содержат копии всех обновляемых объектов листа)          *
 *                                                              *
 ***************************************************************/

public :

 // Удалить резервные файлы
 void DeleteBackFiles();

 // Запросить число сохраненных копий
 // При ошибке возвращает ноль
 int GetBackObjectCount();

 // Удалить копию объекта
 // number - порядковый номер записи, начиная c 1
 // При ошибке возвращает ноль
 int MarkBackObject(int number);

 // Считать копию объекта
 // number - порядковый номер записи среди всех копий, начиная c 1
 // При ошибке возвращает ноль
 TObjectHead * ReadBackObject(int number, char *buffer);

 // Сохранить копию объекта в резервном файле
 // При ошибке возвращает ноль
 int _fastcall SaveBackObject(TObjectHead * head,
                              OBJECTDATA * data = 0,
                              SEMANTIC   * semn = 0,
                              IMGDRAW    * draw = 0);   

 /***************************************************************
 *                                                              *
 *                 Запросы / установка                          *
 *   прямоугольных и геодезических координат углов листа        *
 *      Геодезические координаты измеряются в радианах          *
 *                                                              *
 ***************************************************************/

public :

 // Запросить/установить "B" юго-западного угла листа (РАДИАНЫ !)
 double  BSouthWestCoordinate(double value);
 double  BSouthWestCoordinate();
 double  BSW() {return BSouthWestCoordinate();}
 double  BSW(double value) {return BSouthWestCoordinate(value);}

 // Запросить/установить "B" северо-западного угла листа
 double  BNorthWestCoordinate(double value);
 double  BNorthWestCoordinate();
 double  BNW() {return BNorthWestCoordinate();}
 double  BNW(double value) {return BNorthWestCoordinate(value);}

 // Запросить/установить "B" северо-восточного угла листа
 double  BNorthEastCoordinate(double value);
 double  BNorthEastCoordinate();
 double  BNE() {return BNorthEastCoordinate();}
 double  BNE(double value) {return BNorthEastCoordinate(value);}

 // Запросить/установить "B" юго-восточного угла листа
 double  BSouthEastCoordinate(double value);
 double  BSouthEastCoordinate();
 double  BSE() {return BSouthEastCoordinate();}
 double  BSE(double value) {return BSouthEastCoordinate(value);}

 // Запросить/установить "L" юго-западного угла листа
 double  LSouthWestCoordinate(double value);
 double  LSouthWestCoordinate();
 double  LSW() {return LSouthWestCoordinate();}
 double  LSW(double value) {return LSouthWestCoordinate(value);}

 // Запросить/установить "L" северо-западного угла листа
 double  LNorthWestCoordinate(double value);
 double  LNorthWestCoordinate();
 double  LNW() {return LNorthWestCoordinate();}
 double  LNW(double value) {return LNorthWestCoordinate(value);}

 // Запросить/установить "L" северо-восточного угла листа
 double  LNorthEastCoordinate(double value);
 double  LNorthEastCoordinate();
 double  LNE() {return LNorthEastCoordinate();}
 double  LNE(double value) {return LNorthEastCoordinate(value);}

 // Запросить/установить "L" юго-восточного угла листа
 double  LSouthEastCoordinate(double);
 double  LSouthEastCoordinate();
 double  LSE() {return LSouthEastCoordinate();}
 double  LSE(double value) {return LSouthEastCoordinate(value);}

 // Запросить/установить "X" юго-западного угла листа (МЕТРЫ !)
 double XSouthWest(double value);
 double X1m(double value) { return XSouthWest(value); }
 double XSouthWest();
 double X1m() { return XSouthWest(); }

 // Запросить/установить "X" северо-западного угла листа
 double XNorthWest(double value);
 double X2m(double value) { return XNorthWest(value); }
 double XNorthWest();
 double X2m() { return XNorthWest(); }

 // Запросить/установить "X" северо-восточного угла листа
 double XNorthEast(double value);
 double X3m(double value) { return XNorthEast(value); }
 double XNorthEast();
 double X3m() { return XNorthEast(); }

 // Запросить/установить "X" юго-восточного угла листа
 double XSouthEast(double value);
 double X4m(double value) { return XSouthEast(value); }
 double XSouthEast();
 double X4m() { return XSouthEast(); }

 // Запросить/установить "Y" юго-западного угла листа
 double YSouthWest(double value);
 double Y1m(double value) { return YSouthWest(value); }
 double YSouthWest();
 double Y1m() { return YSouthWest(); }

 // Запросить/установить "Y" северо-западного угла листа
 double YNorthWest(double value);
 double Y2m(double value) { return YNorthWest(value); }
 double YNorthWest();
 double Y2m() { return YNorthWest(); }

 // Запросить/установить "Y" северо-восточного угла листа
 double YNorthEast(double value);
 double Y3m(double value) { return YNorthEast(value); }
 double YNorthEast();
 double Y3m() { return YNorthEast(); }

 // Запросить/установить "Y" юго-восточного угла листа
 double YSouthEast(double value);
 double Y4m(double value) { return YSouthEast(value); }
 double YSouthEast();
 double Y4m() { return YSouthEast(); }

 /***************************************************************
 *                                                              *
 *       Запросы описания объектов, метрики и семантики         *
 *                                                              *
 ***************************************************************/

public:

 // Запросить объект рамки листа карты
 // Если рамка найдена - текущий объект описывает рамку
 // Если рамки нет, то возвращается 0
 TObjectDesc GetListFrameDesc() { return GetFrameDesc(); }
 TObjectDesc GetFrameDesc();

 // Запросить номер объекта - рамки листа
 // При ошибке возвращается ноль
 int GetListFrameNumber();

 // Запросить метрику по смещению (при ошибке = 0)
 // При ошибке возвращает ноль
 OBJECTDATA * DataAddr(long offset);

 // Запросить метрику объекта
 // При ошибке возвращает ноль
 OBJECTDATA * ObjectData(TObjectDesc desc) { return DataAddr(desc.Metric()); }

#ifndef TINYDATA
 // Запросить графическое описание текущего объекта
 // по смещению
 // При ошибке возвращает ноль
 IMGDRAW * DrawAddr(long offset);
#endif

 // Запросить описание "последнего" объекта с локализацией
 // При ошибке возвращает ноль

 TObjectHead * _fastcall GetLastLocalHead(int local)
 {
   return GetObject(GetLastLocalNumber(local));
 }

 // Запросить номер "последнего" объекта с локализацией
 // При ошибке возвращает ноль

 int _fastcall GetLastLocalNumber(int local);

 // Запросить описание "первого" объекта (в логической цепочке)
 // "Первый" объект становится текущим
 // Объекты нумеруются с единицы
 // При ошибке возвращает ноль
 TObjectHead * FirstHead();

 // Запросить номер "первого" объекта (в логической цепочке)
 // При ошибке возвращает ноль
 int FirstNumber();

 // Запросить описание "последнего" объекта (в логической цепочке)
 // "Последний" объект становится текущим
 // Объекты нумеруются с единицы
 // При ошибке возвращает ноль
 TObjectHead * LastHead();

 // Запросить номер "последнего" объекта (в логической цепочке)
 // При ошибке возвращает ноль
 int LastNumber();

 // Запросить описание объекта по номеру
 // Объект number становится текущим
 // При ошибке возвращает ноль
 TObjectHead * ObjectDesc(int number);

 TObjectHead * GetObject(int number)
 {
   return ObjectDesc(number);
 }

#ifndef TINYDATA
 // Запросить графическое описание текущего объекта
 // по смещению
 // При ошибке возвращает ноль
 IMGDRAW * ObjectDraw(long offset)
	 {
  		return DrawAddr(offset);
	 }
#endif

 // Запросить семантику по смещению
 SEMANTIC * SemnAddr(long offset);

 /***************************************************************
 *                                                              *
 *    Методы редактирования объектов текущего листа карты       *
 *                                                              *
 ***************************************************************/

public:

 // Создать новый объект
 // При неудаче возвращает ноль, код ошибки - см. Error()
 // При успешном выполнении - номер созданного объекта в листе
 // Объекты нумеруются с единицы
 int _fastcall AppendObjectData(TObjectHead * head,
                                OBJECTDATA  * data = 0,
                                SEMANTIC    * semn = 0,
                                IMGDRAW     * draw = 0);

 // Создать новый объект
 // При неудаче возвращает ноль, код ошибки - см. Error()
 // При успешном выполнении - номер созданного объекта в листе
 // Объекты нумеруются с единицы
 int AppendObject(TObjectDesc desc,
                  TObjectData data = (char *)0,
                  TObjectSemn semn = (char*)0,
                  TObjectDraw draw = (char*)0)
 {
   return  AppendObjectData(desc.Base, data.Base, semn.Base, draw.Base);
 }

 int AppendObject(TObjectInfo * object);

 // Удалить объект, заданный номером в листе
 // При неудаче возвращает ноль, код ошибки - см. Error()
 int DeleteObject(int number);

 // Обновить объект,number - номер объекта в листе,
 // после обновления становится текущим
 // При неудаче возвращает ноль, код ошибки - см. Error()
 // При успешном выполнении - номер отредактированного объекта в листе
 // Если number задан ошибочно, возвращается номер, определенный
 // по логической цепочке
 int _fastcall UpdateObjectData(int number, TObjectHead * head,
                                OBJECTDATA * data = 0,
                                SEMANTIC   * semn = 0,
                                IMGDRAW    * draw = 0);

 // Обновить объект,number - номер объекта в листе,
 // после обновления становится текущим
 // При неудаче возвращает ноль, код ошибки - см. Error()
 // При успешном выполнении - номер отредактированного объекта в листе
 // Если number задан ошибочно, возвращается номер, определенный
 // по логической цепочке
 int UpdateObject(int number,TObjectDesc desc,
                  TObjectData  data = (char *)0,
                  TObjectSemn  semn = (char*)0,
                  TObjectDraw  draw = (char*)0)
 {
   return UpdateObjectData(number, desc.Base, data.Base,
                                   semn.Base, draw.Base);
 }

 int UpdateObject(int number, TObjectInfo * object);

 // Обновить графическое описание объекта,
 // number - номер объекта в листе, после обновления становится текущим
 // При неудаче возвращает ноль, код ошибки - см. Error()
 // При успешном выполнении - номер отредактированного объекта в листе
 // Если number задан ошибочно, возвращается номер, определенный
 // по логической цепочке
 int UpdateObjectDraw(int number, IMGDRAW * draw);

 // Определить габариты объекта в листе
 void _fastcall BuildBorder(TObjectHead * head, OBJECTDATA * data,
                            SEMANTIC * semn, IMGDRAW * draw);

 // Определить габариты подписи
 void _fastcall BuildTextBorder(TObjectHead * head, OBJECTDATA * data,
                                SEMANTIC    * semn, IMGDRAW * draw = 0);

protected:

 //  Считать из файла описание объекта
 //  number - номер объекта
 //  desc   - заполняемое описание объекта
 //  При успешном завершении возвращает ноль,
 //  При ошибке - код ошибки
 int _fastcall ReadObjectDesc(int number, TObjectHead * head);

 //  Записать в файл описание объекта
 //  При успешном завершении возвращает ноль,
 //  При ошибке - код ошибки
 int _fastcall WriteObjectDesc(int number, TObjectHead * head);

 //  Записать в файл метрику объекта
 //  При успешном завершении возвращает ноль,
 //  При ошибке - код ошибки
 int _fastcall WriteObjectData(TObjectHead * head, OBJECTDATA * data);

 //  Записать в файл графику объекта
 //  При успешном завершении возвращает ноль,
 //  При ошибке - код ошибки
 int _fastcall WriteObjectDraw(TObjectHead * head, IMGDRAW * draw);

 //  Записать в файл семантику объекта
 //  При успешном завершении возвращает ноль,
 //  При ошибке - код ошибки
 int _fastcall WriteObjectSemn(TObjectHead * head, SEMANTIC * data);


 /***************************************************************
 *                                                              *
 *        Обработка резервных файлов ...\LOG\... ^DA,^SE,^HD    *
 *    (содержат копии всех обновляемых объектов листа)          *
 *                                                              *
 ***************************************************************/

public:

 // Восстановить копию объекта
 // number - порядковый номер записи копий всех объектов
 // При ошибке возвращает ноль
 int RestoreBackObject(int number, TObjectInfo * info);

 // Последовательный перебор отредактированных копий объекта info
 // copynumber - последовательный номер копии объекта info (1, 2, ...)
 // в порядке от последней операции редактирования к предыдущей
 // Вызывается с последовательным увеличением copynumber,
 // пока не будет найдена нужная копия или копии закончатся
 // При ошибке возвращает ноль
 int ReadObjectCopyByNumber(int copynumber, TObjectInfo * info);

 // Удалить отредактированные копии объекта info
 // Вызывается после сохранения (Commit) соответсвующей копии объекта
 // на карте (отмене выполненных операций редактирования)
 // Удаляет копии объекта от первой до copynumber
 // Копия copynumber+1 становится первой
 // При ошибке возвращает ноль
 int DeleteObjectCopyToNumber(int copynumber, TObjectInfo * info);

 // Занять лист
 void LockList()
 {
#ifndef HIDESECTION
   EnterTheCriticalSection(&Section);
#endif
 }

 // Освободить лист
 void UnLockList()
 {
#ifndef HIDESECTION
  LeaveTheCriticalSection(&Section);
#endif
 }

public:

 int   List;               // НОМЕР ТЕКУЩЕГО ЛИСТА
 int   ErrorList;          // НОМЕР ОШИБОЧНОГО ЛИСТА

#ifndef GISSERV
 int   ShowNumber;         // НОМЕР ОБЪЕКТА
#endif

 TMap * MapBase;           // УКАЗАТЕЛЬ НА КАРТУ,К КОТОРОЙ ПРИНАДЛЕЖИТ ЛИСТ

 HEADBUFFER  HeadBuff;     // ОПИСАНИЕ БУФЕРА ЗАГОЛОВКОВ АКТИВНОГО ЛИСТА
 LONGBUFFER  DataBuff;     // ОПИСАНИЕ БУФЕРА МЕТРИКИ АКТИВНОГО ЛИСТА
 DATABUFFER  SemnBuff;     // ОПИСАНИЕ БУФЕРА СЕМАНТИКИ АКТИВНОГО ЛИСТА
 DATABUFFER  DrawBuff;     // ОПИСАНИЕ БУФЕРА ГРАФИКИ АКТИВНОГО ЛИСТА

#ifndef TINYDATA
 TVectorFile VectBuff;     // ОПИСАНИЕ БУФЕРА 3D-ВЕКТОРОВ АКТИВНОГО ЛИСТА
#endif

 HANDLE File_HDR;          // ИДЕНТИФИКАТОР ФАЙЛА ЗАГОЛОВКОВ
 HANDLE File_DAT;          // ИДЕНТИФИКАТОР ФАЙЛА ДАННЫХ
 HANDLE File_SEM;          // ИДЕНТИФИКАТОР ФАЙЛА СЕМАНТИКИ
 HANDLE File_DRW;          // ИДЕНТИФИКАТОР ФАЙЛА ГРАФИКИ

 SETID SetId;              // ИДЕНТИФИКАТОР НАБОРА ОПИСАНИЙ ОБ'ЕКТОВ
 SHEETDESC * LstId;        // ИДЕНТИФИКАТОР ПАСПОРТНЫХ ДАННЫХ НА ЛИСТ

 char Path_LIST[MAX_PATH]; // ПУТЬ ДОСТУПА К ФАЙЛАМ ТЕКУЩЕГО ЛИСТА

 int   FileAccess;         // РЕЖИМ ДОСТУПА К ЛИСТУ
 int   FileShare;          // РЕЖИМ ДОСТУПА К ЛИСТУ

 long int LastError;       // КОД ОШИБКИ ПОСЛЕДНЕЙ ОПЕРАЦИИ

 int Isdirty;              // ПРИЗНАК РЕДАКТИРОВАНИ ЗАПИСИ

 HANDLE Back_HDR;          // ИДЕНТИФИКАТОР РЕЗЕРВНОГО ФАЙЛА
 HANDLE Back_DAT;          // ИДЕНТИФИКАТОР РЕЗЕРВНОГО ФАЙЛА
 HANDLE Back_SEM;          // ИДЕНТИФИКАТОР РЕЗЕРВНОГО ФАЙЛА
 HANDLE Back_DRW;          // ИДЕНТИФИКАТОР РЕЗЕРВНОГО ФАЙЛА

 int FreeAppend;           // ПРИЗНАК ВЫПОЛНЕНИЯ СПЕЦИАЛЬНОЙ СОРТИРОВКИ

 int BorderUpdate;         // ПРИЗНАК ОБНОВЛЕНИЯ ГАБАРИТОВ ЛИСТА

 long LockOffset;          // ПОЗИЦИЯ БЛОКИРОВКИ ФАЙЛА

 struct LISTSTACK
  Stack[LISTSTACKLIMIT];   // СПИСОК ОТКРЫТЫХ ЛИСТОВ

 unsigned int StackIndex;  // СЧЕТЧИК ОБРАЩЕНИЙ К СТЕКУ ЛИСТОВ

 int ActionLogMode;        // РЕЖИМ ДОСТУПА К ЖУРНАЛУ

#ifndef HIDESECTION
 MAPCRITICALSECTION Section; // РАЗГРАНИЧЕНИЕ ДОСТУПА НА ЗАПИСЬ ПОТОКОВ  
#endif
};

typedef TMapList MAPLISTDATA;

// Закрыть текущий лист
void _fastcall mlClose(MAPLISTDATA * data, int mode);

// Открыть новый лист
// При ошибке возвращает ноль
int _fastcall mlOpen(MAPLISTDATA * data, void * mapbase, int number);

// Заполнить описание листа данными из формуляра
// Создать пустые файлы данных
// При ошибке возвращает ноль
int _fastcall mlCreateList(MAPLISTDATA * data, void * map,       
                           int number, LISTREGISTER * mapreg);

// Установить признак "лист не активен"
void _fastcall mlNotActive(MAPLISTDATA * data);

// Распределение памяти под прокачку данных об объектах
int _fastcall mlAllocBuffers(MAPLISTDATA * data, int notlimit);

// Освобождение памяти, занятой под прокачку данных об объектах
void _fastcall mlFreeBuffers(MAPLISTDATA * data);

// Запросить была ли ошибка
int _fastcall mlCheckError(MAPLISTDATA * data, int number);

// Выдать сообщение об ошибке
int _fastcall mlErrorMessage(MAPLISTDATA * data, int code,
                             const char * name, int number);

// Установка параметров листа из области LISTREGISTER
// При ошибке возвращает ноль
int _fastcall mlListRegister(MAPLISTDATA * data, int list,
                             LISTREGISTER * mapreg);

// Функции записи и чтения  данных листа карты
// Возвращает число обработанных байт
// При ошибке возвращает ноль
int _fastcall mlWrite(HANDLE file, int offset,            
                      const char * address, int length);

int _fastcall mlWriteDesc(MAPLISTDATA * data, int offset,
                          const char * address);

int _fastcall mlWriteData(MAPLISTDATA * data, int offset,
                          const char * address, int length);

int _fastcall mlWriteDraw(MAPLISTDATA * data, int offset,
                          const char * address, int length);

int _fastcall mlWriteSemn(MAPLISTDATA * data, int offset,
                          const char * address, int length);

int _fastcall mlReadDesc(MAPLISTDATA * data, int offset,
                         char * address, int length);

int _fastcall mlReadData(MAPLISTDATA * data, int offset,
                         char * address, int length);

int _fastcall mlReadSemn(MAPLISTDATA * data, int offset,
                         char * address, int length);

// Запросить число объектов в листе
int _fastcall mlCount(MAPLISTDATA * data);

// Добавить новый объект на лист
// При неудаче возвращает ноль, код ошибки - см. Error()
// При успешном выполнении - номер объекта в листе
int _fastcall mlAppendObjectData(MAPLISTDATA * mldata,
                                 TObjectHead * head, OBJECTDATA * data,
                                 SEMANTIC    * semn, IMGDRAW * draw);

// Обновитьобъект на листе
// При неудаче возвращает ноль, код ошибки - см. Error()
// При успешном выполнении - номер объекта в листе
int _fastcall mlUpdateObjectData(MAPLISTDATA * mldata, int number,
                                 TObjectHead * head, OBJECTDATA * data,
                                 SEMANTIC    * semn, IMGDRAW    * draw);

// Обновить графическое описание объекта,
// При неудаче возвращает ноль, код ошибки - см. Error()
int _fastcall mlUpdateObjectDraw(MAPLISTDATA * data,
                                 int number, IMGDRAW * draw);

// Запросить описание объекта по номеру
// Объект number становится текущим
// При ошибке возвращает ноль
TObjectHead * _fastcall mlGetObjectHead(MAPLISTDATA * data, int number);

// Запросить метрику объекта по номеру
// Объект number становится текущим
// При ошибке возвращает ноль
OBJECTDATA * _fastcall mlGetObjectData(MAPLISTDATA * data, int number); 

// Запросить семантику объекта по номеру
// Объект number становится текущим
// При ошибке возвращает ноль
SEMANTIC * _fastcall mlGetObjectSemn(MAPLISTDATA * data, int number);

// Запросить графику объекта по номеру
// Объект number становится текущим
// При ошибке возвращает ноль
IMGDRAW * _fastcall mlGetObjectDraw(MAPLISTDATA * data, int number); 

// Считать из файла описание объекта
// При успешном завершении возвращает ноль,
// При ошибке - код ошибки
int _fastcall mlReadObjectDesc(MAPLISTDATA * data,
                               int object, TObjectHead * head);

// Записать в файл описание объекта
// При успешном завершении возвращает ноль,
// При ошибке - код ошибки
int _fastcall mlWriteObjectDesc(MAPLISTDATA * data,
                                int object, TObjectHead * head);

// Записать в файл метрику объекта
// При успешном завершении возвращает ноль,
// При ошибке - код ошибки
int _fastcall mlWriteObjectData(MAPLISTDATA * mldata,
                                TObjectHead * head, OBJECTDATA *  data);

// Обновить графическое описание объекта
int _fastcall mlWriteObjectDraw(MAPLISTDATA * data,
                                TObjectHead * head, IMGDRAW * draw);

// Записать в файл семантику объекта
// При успешном завершении возвращает ноль,
// При ошибке - код ошибки
int _fastcall mlWriteObjectSemn(MAPLISTDATA * data,
                                TObjectHead * head, SEMANTIC * semn);

// Определить габариты объекта в листе
void _fastcall mlBuildBorder(MAPLISTDATA * mldata, TObjectHead * head,
                             OBJECTDATA * data, SEMANTIC * semn,
                             IMGDRAW    * draw);

//  Определить габариты подписи
void _fastcall mlBuildTextBorder(MAPLISTDATA * mldata, TObjectHead * head,
                                 OBJECTDATA *  data, SEMANTIC * semn,
                                 IMGDRAW    *  draw);

// Запросить объект рамки листа карты
// Если рамка найдена - текущий объект описывает рамку
// Если рамки нет, то возвращается 0
TObjectHead * _fastcall mlGetListFrameDesc(MAPLISTDATA * data);

// Запросить номер объекта - рамки листа
// При ошибке возвращается ноль
int _fastcall mlGetListFrameNumber(MAPLISTDATA * data);

// Создать файл метрики и выделить память
int _fastcall mlCreateDataFile(MAPLISTDATA * data);

// Создать файл графики и выделить память
int _fastcall mlCreateDrawFile(MAPLISTDATA * data);

// Создать файл семантики и выделить память
int _fastcall mlCreateSemnFile(MAPLISTDATA * data);


// Открыть резервные файлы
int _fastcall mlOpenBackFiles(MAPLISTDATA * data);

// Закрыть резервные файлы
void _fastcall mlCloseBackFiles(MAPLISTDATA * data);

// Восстановить копию объекта
// Возвращает номер восстанавливаемой копии объекта
int _fastcall mlRestoreBackObject(MAPLISTDATA * data, int number,
                                  void * objinfo);                    

//  Последовательный перебор отредактированных копий объекта
//  При ошибке возвращает ноль              
int _fastcall mlReadObjectCopyByNumber(MAPLISTDATA * data,
                                       int number, void * info);

//  Удалить отредактированные копии объекта
//  При ошибке возвращает ноль              
int _fastcall mlDeleteObjectCopyToNumber(MAPLISTDATA * data,
                                         int number, void * objinfo); 


#endif

