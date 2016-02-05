
//                        от HMAP

//                        для контроля рассогласования объектов
//                        Выровнил структуры PARAM для параметров
#if !defined(MAPERRPR_H)
#define MAPERRPR_H

#ifndef MAPAPI_H
  #include "mapapi.h"
#endif

#ifndef MAPDEF_H
  #include "mapdef.h"
#endif

#include "errtype.rh"          

#ifdef WIN32API
#pragma pack(push,1)           
#endif

typedef struct ERRORINFO
{
 long  Length;                 // Длина структуры
 long  ErrorType;              // Код ошибки
 long  Amend;                  //
 long  Mark;                   //
 long  FirstListNumber;        // Номер листа первого объекта
 long  FirstObjectNumber;      // Номер объекта первого объекта
 long  FirstNumberSemantic;    // Номер семантики первого объекта
 char  FirstListName[32];      // Имя листа первого объекта
 long  FirstKey;               // Идентификатор первого объекта
 long  FirstNumberSubject;     // Номер подобъекта первого объекта
 DOUBLEPOINT FirstPoint;       // Координаты первого объекта
 long  SecondListNumber;       // Номер листа второго объекта
 long  SecondObjectNumber;     // Номер объекта второго объекта
 long  SecondNumberSemantic;   // Номер семантики второго объекта
 char  SecondListName[32];     // Имя листа второго объекта
 long  SecondKey;              // Идентификатор второго объекта
 long  SecondNumberSubject;    // Номер подобъекта второго объекта
 DOUBLEPOINT SecondPoint;      // Координаты второго объекта
 char  Title[80];              // Текстовая строка для сообщения
}ERRORINFO;

// Флаги обработки данных
typedef struct WORKFLAG
   {
   long Struct;                // Обработка структуры
   long Pasp;                  // Обработка паспорта
   long Rsc;                   // Обработка классификатора
   long Data;                  // Обработка метрики
   long Semn;                  // Обработка семантики
   long TopologData;           // Обработка топологии
   long Add;                   // Обработка
   } WORKFLAG;

// Описание параметров контроля
/*typedef struct PARAMCONTROL
    {
    long Kind;                   // Вид редактирования
    long Loop;                   // Уровень редактирования петель
    double Close;                // Порог замыкания объектов
    double Reach;                // Порог дотягивания до рамки
    } PARAMCONTROL;
*/
// Новые структуры для нового контроля
typedef struct PARAM
   {
   long Parm1;
   long Parm3;
   double Parm2;
   double Parm4;
   } PARAM;

typedef struct PROTOCOL
    {
    long Text;
    long Bin;
    long Sit;
    } PROTOCOL;

typedef struct WORKCONTROL
   {
    long Kind;                   // Вид контроля
    long Prot;                   // Вид протокола
    PARAM Param;                 // Параметры контроля
   } WORKCONTROL;

#ifdef WIN32API
#pragma pack(pop)           
#endif

enum KINDCONTROLNEW
   {
   IKC_NOWORK            = 0,    // Нет обработки
   IKC_CONTROL           = 1,    // Контроль
   IKC_EDIT              = 2,    // Редактирование
   IKC_DELERROR          = 3,    // Удаление ошибочных элементов объекта
   IKC_DELOBJECT         = 4     // Удаление объекта с ошибкой
   };

enum REGIMPROT
    {
    IRP_NO               = 0,
    IRP_ALL              = 1,
    IRP_SELECT           = 2
    };

enum KINDPROT
   {
   IKP_NOPROT            = 0,
   IKP_LOG               = 1,
   IKP_ERR               = 2,
   IKP_LOGERR            = 3,
   IKP_SIT               = 4,
   IKP_LOGSIT            = 5,
   IKP_ERRSIT            = 6,
   IKP_ALL               = 7
   };

#define COUNTTYPECONTROL 70

enum BEGIN_KINDCONTROL
   {
//   IBK_STRUCT            = 0,
   IBK_STRUCT_PASP       = 0,
   IBK_STRUCT_DATA       = 1,
   IBK_STRUCT_SEMN       = 2,
   IBK_STRUCT_DRAW       = 3,       
   IBK_STRUCT_RSCOBJ     = 4,
   IBK_STRUCT_RSCSEM     = 5,
   IBK_STRUCT_RSCCLS     = 6,
//   IBK_PASP              = 10,
   IBK_PASP_FRAME        = 10,
   IBK_PASP_GEO          = 11,
   IBK_PASP_RULE         = 12,
   IBK_PASP_CONSTPROJ    = 13,
   IBK_RSC               = 20,
//   IBK_DATA              = 30,
   IBK_DATA_NULL         = 30,
   IBK_DATA_BORDER       = 31,
   IBK_DATA_CLOSESQ      = 32,
   IBK_DATA_CLOSELN      = 33,
   IBK_DATA_DIRECT       = 34,
   IBK_DATA_REACH        = 35,
   IBK_DATA_EQUAL        = 36,
//   IBK_SEMN              = 40,
   IBK_SEMN_PASS         = 40,
   IBK_SEMN_UNEXPECTED   = 41,
   IBK_SEMN_VALUE        = 42,
//   IBK_TOPOLOG           = 50,
   IBK_TOPOLOG_LOOP      = 50,
   IBK_TOPOLOG_SUBJECT   = 51,
   IBK_TOPOLOG_DUPKEY    = 52,
   IBK_TOPOLOG_CROSS     = 53,
   IBK_TOPOLOG_MAIN      = 54,
   IBK_TOPOLOG_DUPDATA   = 55,
   IBK_TOPOLOG_GAP       = 56,
   IBK_TOPOLOG_ADJUST    = 57,
//   IBK_ADD               = 60
   IBK_ADD_SPACE         = 60,
   IBK_ADD_BREAKOFF      = 61,
   IBK_ADD_WATER         = 62,
   IBK_ADD_Z             = 63,
   IBK_ADD_INPUT         = 64,   
   IBK_ADD_HIEGHT        = 65,
   IBK_ADD_ADJUST        = 66
   };

//------------------------------------------------------------------
// Число IEC-кодов (errtype.rh)
//------------------------------------------------------------------
//#define ErrorTypeCount 25   
//#define ErrorTypeCount 32   
//#define ErrorTypeCount 37   
#define ErrorTypeCount   IEC_TYPECOUNT   


#define KindControlCount 16

enum KINDCONTROL  // Коды ошибок
    {
    IKC_MAP_STRUCT         = 1,   // Ошибка в структуре данных

    IKC_DAT_EQUAL          = 2,   // Двойные точки в метрике
    IKC_DAT_CLOSESQ        = 3,   // Oбъект не замкнут
    IKC_DAT_CLOSELN        = 4,   // Oбъект не замкнут
    IKC_DAT_LOOP           = 5,   // Петля у объета
    IKC_DAT_BORDER         = 6,   // Габариты объекта
    IKC_DAT_NULL           = 7,   // Вырожденный объект
    IKC_DAT_REACH          = 8,   // Ошибка дотягивания до рамки
    IKC_DAT_DIRECT         = 9,   // Направление цифрования
    IKC_DAT_SUBJECT        = 10,  // Ошибка входимости


    IKC_SEM_VALUE          = 11,  // Недопустимое значение
    IKC_SEM_PASS           = 12,  // Нет обязательных характеристик
    IKC_SEM_UNEXPECTED     = 13,  // Лишняя семантика

    IKC_SEM_HEIGHT         = 14,  // Абсолютной высоты

    IKC_DAT_ADJUST         = 15   // Ошибка в сводке
    };


enum DATAFLAGCONTR
     {
     DATA_NULL       = 0x80000000l,
     DATA_BOX        = 0x40000000l,
     DATA_CLOSESQ    = 0x20000000l,
     DATA_CLOSELINE  = 0x10000000l,
     DATA_DIRECT     = 0x08000000l,
     DATA_REACH      = 0x04000000l,
     DATA_DBLEPOINT  = 0x02000000l,
     DATA_LOOP       = 0x01000000l,
     DATA_POBJECT    = 0x00800000l,
//     enum FLAGCONTR {
     SEMN_ABSENCEOBLIGE = 0x80000000l,
     SEMN_UNPERMISSIBLE = 0x40000000l,
     SEMN_RANGE         = 0x20000000l
//                    };
     };



extern "C"
{
// Проверка наличия файла протокола
int _export WINAPI ExistFileError(TMap * map);

// Запрос количества ошибок в файле
int _export WINAPI GetCountError(TMap * map);
// Чтение очередной записи из файла протокола
int _export WINAPI LoadError(TMap * map,int number,ERRORINFO * error);
// Запись информации в файл протокола
int _export WINAPI WriteError(TMap * map,ERRORINFO * error);

// Удаление файла протокола
int _export WINAPI DeleteFileError(TMap * map);

// Проставление отметки о редактировании ошибки
int _export WINAPI MarkError(TMap * map,int number);

// Контроль данных
int _export WINAPI ControlMap(HMAP doc,WORKCONTROL * parm,HWND handle,HSELECT);

// Проверка наличия файла протокола
int _export WINAPI ExistFileDocError(HMAP map);

// Запрос количества ошибок в файле
int _export WINAPI GetCountDocError(HMAP map);
// Чтение очередной записи из файла протокола
int _export WINAPI LoadDocError(HMAP map,long int number,ERRORINFO * error);
// Запись информации в файл протокола
int _export WINAPI WriteDocError(HMAP map,ERRORINFO * error);
int _export WINAPI WriteDocTitle(HMAP hmap,char * text);    
// Удаление файла протокола
int _export WINAPI DeleteFileDocError(HMAP map);

// Проставление отметки о редактировании ошибки
int _export WINAPI MarkDocError(HMAP map,long int number);

}

#endif