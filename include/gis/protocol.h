
#ifndef PROTOCOL_H

#ifndef MAPAPI_H
  #include "mapapi.h"
#endif

#include "mwmacro.h"               

// СПИСОК КОМАНД СЕКЦИИ [CONTROL]
#define PRO_ACT  0x5443412E        // .ACT
#define PRO_MAP  0x50414D2E        // .MAP
#define PRO_SIT  0x5449532E        // .SIT
#define PRO_ASK  0x4B53412E        // .ASK
#define PRO_REQ  0x5145522E        // .REQ
#define PRO_RSC  0x4353522E        // .RSC
#define PRO_MES  0x53454D2E        // .MES
#define PRO_OFF  0x46464F2E        // .OFF
#define PRO_COD  0x444F432E        // .COD
#define PRO_SYS  0x5359532E        // .SYS

// СПИСОК КОМАНД СЕКЦИИ [DATA]
#define PRO_DAT  0x5441442E        // .DAT
#define PRO_OBJ  0x4A424F2E        // .OBJ
#define PRO_KEY  0x59454B2E        // .KEY
#define PRO_GEN  0x4E45472E        // .GEN
#define PRO_MET  0x54454D2E        // .MET
#define PRO_SEM  0x4D45532E        // .SEM
#define PRO_TXT  0x5458542E        // .TXT
#define PRO_END  0x444E452E        // .END
#define PRO_EVN  0x4E56452E        // .EVN
#define PRO_SEG  0x4745532E        // .SEG
#define PRO_ON   0x5F4E4F2E        // .ON_
#define PRO_ANG  0x474E412E        // .ANG
#define PRO_SPL  0x4C50532E        // .SPL
#define PRO_APP  0x5050412E        // .APP
#define PRO_API  0x4950412E        // .API
#define PRO_APS  0x5350412E        // .APS
#define PRO_DEL  0x4C45442E        // .DEL
#define PRO_CHK  0x4B48432E        // .CHK
#define PRO_UNC  0x434E552E        // .UNC
#define PRO_ENA  0x414E452E        // .ENA
#define PRO_DIS  0x5349442E        // .DIS
#define PRO_COM  0x4D4F432E        // .COM
#define PRO_GET  0x5445472E        // .GET

#define PROOUTPUTBLOCK   (16*1024L)   // МИНИМАЛЬНЫЙ РАЗМЕР ВЫХОДНОГО БУФЕРА

typedef struct MAPPROTOCOL            // СТРУКТУРА УПРАВЛЕНИЯ ПРОТОКОЛОМ
{
  long int   Length;                  // Размер данной структуры
  long int   ClientIdent;             // Идентификатор клиента (адрес сокета)
  char *     InputBuffer;             // Адрес входного буфера
  long int   InputSize;               // Размер входного буфера
  long int   InputRecordSize;         // Размер входной записи
  char *     OutputBuffer;            // Адрес выходного буфера
  long int   OutputSize;              // Размер выходного буфера
  long int   OutputRecordSize;        // Размер выходной записи
  long int   TaskIdent;               // Идентификатор задачи или 0
  long int   Reserv[2];               // Резерв
}
  MAPPROTOCOL;

#define SYS_NONE  0
#define SYS_GEO42 1
#define SYS_WGS84 2
#define SYS_EP90  3
#define SYS_MET42 16

#define MAXSITCOUNT  16

typedef struct PROCONTROL     // ДАННЫЕ СЕКЦИИ CONTROL
{
  long int ClientIdent;       // Идентификатор клиента (адрес сокета)
  char     Act[16];           // Выполняемая команда
  char     Ask[16];           // Идентификатор запроса
  char     Map[256];          // Имя фоновой карты ("атласа")
  char     Sit[256];          // Имя пользовательской карты ("слоя")
  char     Rsc[256];          // Имя файла классификатора
  char     Mes[160];          // Комментарий к выполняемой операции
  long int Req;               // Режим отображения
  long int Off;               // Признак отмены команды
  long int Sys;               // Система координат SYS_WGS84,...
  long int Zone;              // Осевой меридиан зоны для CК42
  long int Count;             // Число переданных пользовательских карт
  struct
  {
   char    Sit[256];          // Имя пользовательской карты ("слоя")
  }
    List[MAXSITCOUNT];
}
  PROCONTROL;



#ifdef __cplusplus
extern "C"
{
#endif

// Инициализация внутренних данных для обработки Протокола
// Заполнение полей OutputBuffer, OutputSize...
// При ошибке возвращает ноль

long int _DLLTASK proInit(TASKPARMEX * parm, MAPPROTOCOL * data);

// Освобождение внутренних данных при завершении работы
// При ошибке возвращает ноль

void _DLLTASK proFree(MAPPROTOCOL * data);

// Уведомление о прекращении связи с прикладной задачей
// Все интерактивные запросы задачи удаляются из очереди

void _DLLTASK proCloseClient(TASKPARMEX * parm, long int ident);

// Обработка записи Протокола локального взаимодействия...
// parm - параметры связи с картой,
// data - описание передаваемых данных.
// После обработки входного буфера в выходной буфер помещается
// ответная запись, размер записи помещается в поле OutputRecordSize.
// Если данных для передачи нет - размер выходной записи равен нулю.
// Если размер буфера меньше размера передаваемой записи, функция
// proPutRecord автоматически перераспределит память под буфер.
// При ошибке возвращает ноль

long int _DLLTASK proPutRecord(TASKPARMEX * parm, MAPPROTOCOL * data);

// Запросить условия выполнения текущей интерактивной команды
// ident - идентификатор текущего запроса, заполняется при вызове
// При ошибке возвращает ноль

PROCONTROL * _DLLTASK proGetSelectParm(long int * ident);

// Подготовить ответ на команду SELECT и отправить данные в задачу
// Функция вызывается автоматически из обработчика команды SELECT
// hmap - идентификатор набора карт
// hobj - идентификатор выбранного объекта карты
// Если обработчик нужно завершить - возвращает ноль,
// для продолжения работы обработчика возвращает ненулевое значение

long int _DLLTASK proSelectReply(TASKPARMEX * parm, HMAP hmap,
                                 HOBJ hobj, long int ident);

// Запросить условия выполнения текущей интерактивной команды CREATE
// ident  - идентификатор текущего запроса, заполняется при вызове
// method - способ создания объекта (если данных нет - записывается 0)
// При ошибке возвращает ноль

PROCONTROL * _DLLTASK proGetCreateParm(HMAP hMap, HOBJ hObj,
                                       long int * method,
                                       long int * ident);

// Подготовить ответ на команду CREATE и отправить данные в задачу
// Функция вызывается автоматически из обработчика команды CREATE
// hmap - идентификатор набора карт
// hobj - идентификатор выбранного объекта карты
// Если обработчик нужно завершить - возвращает ноль,
// для продолжения работы обработчика возвращает ненулевое значение


///////////////////////////////////////NIITP////////////////////////////////////
long int _DLLTASK proCreateReply(TASKPARMEX * parm, HMAP hmap,
                                 HOBJ hobj, long int ident, short usage = 0, double x = 555.0, double y = 555.0);
				  
//long int _DLLTASK proCreateReply(TASKPARMEX * parm, HMAP hmap,
//                                 HOBJ hobj, long int ident);
//////////////////////////////////////////////////////////////////


// Уведомление о закрытии обработчика

void _DLLTASK proActionClose(TASKPARMEX * parm);

// Обработка события, команда EVENT
// map - фоновая карта для всех событий;
// Если event = PRO_EV_SELECT, то info - выбранный объект;
// Сообщение - SELECT.
// Если event = PRO_EV_CHANGE, то сообщение LOAD.
// Если event = PRO_EV_UPDATE, то parm - параметры обновления;
// Сообщение - CREATE, DATA или DELETE.

void _DLLTASK proEventReply(TASKPARMEX * parm, int event, HMAP hMap,
                            CHANGEINFO * change, HOBJ hObj);


// Отправить список выделенных объектов по запросу оператора
// hMap  - идентификатор карты, на которой выделены объекты
//         или выбран один объект (более высокий приоритет у объекта)
// info  - идентификатор выбранного объекта, если равен 0,
//         то передается список выделенных объектов
// ident - идентификатор задачи из списка задач в секции PROTOCOLLIST

void _DLLTASK proSendObjects(TASKPARMEX * parm, HMAP hMap,
                             HOBJ hObj, int ident);

// Запрос доступности пункта меню
// Если пункт меню обработан - возвращает 1

long int _DLLTASK proMenuEnable(COMMANDENABLER * commen);

// Отправить уведомление о вызове пункта меню
// Если открытых карт нет, hMap равен нулю
// Если на переданный идентификатор есть внешнее приложение - возвращает 
// ненулевое значение
// При ошибке возвращает ноль

long int _DLLTASK proMenuCommand(TASKPARMEX * parm, HMAP hMap, long int ident);

#ifdef __cplusplus
}
#endif

// **********************************************************
//
//  Внутренние функции и структуры обработки протокола
//
// **********************************************************

typedef struct PRODATA        // ДАННЫЕ ДЛЯ ОБРАБОТКИ СЕКЦИИ DATA
{
  HMAP      hMap;             // Идентификатор фоновой карты
  HSITE     hSite;            // Идентификатор пользовательской карты
  DFRAME    Border;           // Общие габариты поступившей метрики
  long  int Req;              // Режим отображения
  long  int Sys;              // Система координат SYS_WGS84,...
  long  int Zone;             // Осевой меридиан зоны для CК42
  HWND      Hwnd;             // Идентификатор текущего окна карты
}
  PRODATA;

#define PROSELECTCOUNT 32     // Максимальное число запросов в очереди

#define PROSELECTTYPE  MT_PROTOCOLSELECT  // Запрос на выбор
#define PROCREATETYPE  MT_PROTOCOLCREATE  // Запрос на создание

typedef struct SELECTCONTROL  // СТЕК ИНТЕРАКТИВНЫХ ЗАПРОСОВ
{
 int        Ident;            // Идентификатор запроса;
 int        Type;             // Тип запроса 0 - SELECT, 1 - CREATE
 PROCONTROL Control;          // Копия данных из секции [CONTROL]
 char *     Buffer;           // Копия входной секции данных или 0
 int        Size;             // Размер буфера
 char *     Current;          // Текущая позиция в буфере
 HWND       Hwnd;             // Идентификатор окна карты
 long int   IsActive;         // Признак состояния выполнения команд
}
 SELECTCONTROL;

#define PROEVENTCOUNT 32      // Максимальное число приложений в списке

#define PRO_EV_CHANGE 1       // Изменение состава документа
#define PRO_EV_SELECT 2       // Выбор объекта на карте
#define PRO_EV_UPDATE 4       // Изменение данных объекта

typedef struct EVENTCONTROL
{
 int        Ident;           // Идентификатор запроса
 int        ClientIdent;     // Идентификатор приложения
 char       Map[256];        // Имя фоновой карты ("атласа")
 int        Flag;            // Флаг событий PRO_EV_CHANGE,...
 int        Count;           // Число пользовательских карт в списке
 struct
  {
   char     Sit[256];        // Имя пользовательской карты ("слоя")
   int      Flag;            // Флаг событий PRO_EV_CHANGE,...
  }
    List[MAXSITCOUNT];
}
 EVENTCONTROL;

// Найти символ в строке

char * _fastcall proSeekChar(const char * point, char symbol);

// Выбрать очередную строку из буфера
// Ищет символы '\n' и/или '\r' и становится за ними
// Пустые строки и пробелы автоматически пропускаются
// point - адрес текущей позиции в буфере
// limit - длина оставшейся части записи
// Возвращает адрес начала новой строки (после пробелов)
// Значение переменной limit корректируется автоматически
// Если данные закончились - возвращает ноль

char * _fastcall proGetNextString(char * point, int * limit);

// Выбрать параметры команды
// Ищет символы '\n' и/или '\r' и выбирает строку до них
// point - адрес текущей позиции в буфере
// limit - длина оставшейся части записи
// value - адрес буфера для результата
// size  - длина буфера для результата (с учетом замыкающего 0)
// Возвращает адрес конца строки
// Если данные закончились - возвращает ноль

char * _fastcall proGetValue(char * point, int * stringlimit,
                             char * value, int size);


// Добавить данные в выходной протокол с контролем длины
// буфера
// При ошибке возвращает ноль

char * _fastcall proPutValue(MAPPROTOCOL * data, const char * value,
                             int size);

// Разобрать строку на параметры (до 3)
// size - размер строк для записи параметров (одинаковый)
// Возвращает число найденных параметров
// При ошибке возвращает ноль

int _fastcall proSeekValue3(const char * value,
                            char * pole1, char * pole2, char * pole3, int size);

// Разобрать строку на параметры (до 5)
// Возвращает число найденных параметров
// При ошибке возвращает ноль

int _fastcall proSeekValue5(const char * value,
                            char * pole1, char * pole2, char * pole3,
                            char * pole4, char * pole5, int size);


//  Собрать полное имя пользовательской карты

char * _fastcall proBuildSitName(HMAP hMap, char * sitname, int size);

// Увеличение размера выходного буфера
// При ошибке возвращает ноль

int _fastcall proRealloc(MAPPROTOCOL * data, int delta);

// Обработать запись во входном буфере
// При успешном выполнении возвращает адрес следующей записи данных
// При ошибке возвращает ноль

char * _fastcall proPrepareRecord(TASKPARMEX * parm, MAPPROTOCOL * data,
                                  char * point, int * limit);


// Обработать данные секции CONTROL
// parm       - параметры связи с картой,
// data       - описание передаваемых данных,
// proControl - данные секции CONTROL
// proData    - исходные данные для обработки секции DATA
// При ошибке возвращает ноль

int _fastcall proGetControl(TASKPARMEX * parm,
                            PROCONTROL * proControl, PRODATA * proData);


// Заполнить секцию команд ответной записи

void _fastcall proReceiptControl(MAPPROTOCOL * data,
                                 PROCONTROL * proControl);


// Обработать данные из секции DATA
// При успешном выполнении возвращает адрес следующей записи данных
// При ошибке возвращает ноль

char * _fastcall proGetData(TASKPARMEX * parm, MAPPROTOCOL * data,
                            char * point, int * stringlimit,
                            PRODATA * proData);

// Обработать данные метрики объекта из секции DATA
// При успешном выполнении возвращает адрес следующей записи данных
// hobj  - идентификатор заполняемого объекта
// count - ожидаемое число подобъектов
// При ошибке возвращает ноль

char * _fastcall proGetMetric(HOBJ hobj, int subjcount,
                              char * point, int * stringlimit,
                              PRODATA * proData);

// Обработать данные метрики объекта из секции DATA
// При успешном выполнении возвращает адрес следующей записи данных
// hobj  - идентификатор заполняемого объекта
// count - ожидаемое число подобъектов
// При ошибке возвращает ноль

char * _fastcall proGetSemantic(HOBJ hobj, int count,
                                char * point, int * stringlimit,
                                PRODATA * proData);


// Обработать данные из секции DATA для режима DELETE__
// При успешном выполнении возвращает адрес следующей записи данных
// При ошибке возвращает ноль

char * _fastcall proDeleteObjects(TASKPARMEX * parm, MAPPROTOCOL * data,
                                  char * point, int * stringlimit,
                                  PROCONTROL * proControl,
                                  int objects);


// Обработать данные из секции DATA для режима SAVE__
// При успешном выполнении возвращает адрес следующей записи данных
// При ошибке возвращает ноль

char * _fastcall proSaveObjects(TASKPARMEX * parm, MAPPROTOCOL * data,
                                char * point, int * stringlimit,
                                PRODATA * proData, int dataflag);


// Сохранить описание объекта в выходном буфере
void _fastcall proSaveObject(MAPPROTOCOL * data, PRODATA * proData,
                             HOBJ hobj, int number, HRSC hRsc);

                             
// Выбрать объект на карте и передать в приложение, режимы SELECT,CREATE
// При успешном выполнении возвращает адрес следующей записи данных
// При ошибке возвращает ноль

char * _fastcall proSelectObject(TASKPARMEX * parm, PROCONTROL * proControl,
                                 char * point, int * stringlimit,
                                 PRODATA * proData, int type, int objects);

// Проинициализировать область параметров выбора объекта
// При ошибке возвращает ноль

int _fastcall proSelectInit();

// Освободить ресурсы выбора объекта

void _fastcall proSelectFree();

// Удалить из очереди запросы заданного типа для указанного
// приложения
// type  - тип запроса (выбор объекта,создание объекта...),
//         если type равно 0, удаляются запросы всех типов.
// ident - идентификатор приложения (клиента)

void _fastcall proDeleteRecord(TASKPARMEX * parm, int type, int ident);

// Удалить из очереди запросы к указанной карте
// name - имя закрываемой карты местности

void _fastcall proDeleteRecordByName(TASKPARMEX * parm, const char * name);


// Загрузить служебную копию редактора
// При ошибке возвращает ноль

int _fastcall proLoadMapEdit(TASKPARMEX * parm);

// Выгрузить служебную копию редактора

void _fastcall proFreeMapEdit();

// Запрос на показ объектов, команда SHOWDATA

char * _fastcall proShowData(TASKPARMEX * parm,
                             char * point, int * stringlimit,
                             PRODATA * proData);

// Запрос на выделение объектов

char * _fastcall proMarkObjects(TASKPARMEX * parm, PROCONTROL * proControl,
                                char * point, int * stringlimit,
                                PRODATA * proData, int dataflag);

// Закрыть указанные данные

void _fastcall proCloseData(TASKPARMEX * parm, PROCONTROL * proControl);


// Запрос на обработку главного меню

char * _fastcall proMenu(TASKPARMEX * parm,
                         char * point, int * stringlimit,
                         PRODATA * proData, PROCONTROL * proControl);

// Удалить пункты меню, созданные для закрытого клиента
// ident - идентификатор приложения (клиента)

void _fastcall proMenuClose(TASKPARMEX * parm, int ident);

// Проинициализировать область параметров событий

int _fastcall proEventInit();

//  Освободить ресурсы параметров событий

void _fastcall proEventFree();

// Удалить из очереди запросы к указанной карте

void _fastcall proDeleteEventByName(const char * name);

// Удалить из очереди запросы для указанного приложения
// ident - идентификатор приложения (клиента)

void _fastcall proDeleteEvent(int ident);

// Обработка подписки на события, команда EVENT

char *_fastcall proEvents(TASKPARMEX * parm, PROCONTROL * proControl,
                          char * point, int * stringlimit,
                          PRODATA * proData, int datasec);

// Заполнить подтверждение для команды LOAD

void _fastcall proLoadReply(MAPPROTOCOL * data, PROCONTROL * proControl,
                            PRODATA * proData);

// Добавить точку в метрику объекта с учетом системы координат
// hobj  - идентификатор заполняемого объекта
// При ошибке возвращает ноль

void _fastcall proAppendPoint(HOBJ hobj,
                              double * B, double * L, double * H,
                              int subject, PRODATA * proData);


// Управление редактированием

void _fastcall proEditData(PROCONTROL * proControl, PRODATA * proData);


// Управление отображением данных

char * _fastcall proViewData(TASKPARMEX * parm, PROCONTROL * proControl,
                             char * point, int * stringlimit,
                             PRODATA * proData, int dataflag);

// Управление отображением данных, обработка секции [DATA]

char * _fastcall proViewSite(HSELECT hSelect, HRSC hRsc, int view,
                             char * point, int * stringlimit);


// Запрос параметров отображения
void _fastcall proGetView(MAPPROTOCOL * data, PROCONTROL * proControl,
                          PRODATA * proData);


// Запрос списка открытых окон
void _fastcall proGetMap(TASKPARMEX * parm, MAPPROTOCOL * data,
                         PROCONTROL * proControl);

#endif  // PROTOCOL_H
