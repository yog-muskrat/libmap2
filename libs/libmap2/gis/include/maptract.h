
#if !defined(MAPTRACT_H)
#define MAPTRACT_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#define TACBUFCOUNT  128
#define TACBUFLENGTH  (sizeof(ACTIONHEAD)+TACBUFCOUNT*sizeof(ACTIONRECORD))

typedef struct TACHEAD     // ЗАГОЛОВОК ФАЙЛА
{
  long int       Label;    // Метка начала файла
  long int       Length;   // Длина файла
  long int       Version;  // Версия структуры
  long int       Count;    // Число транзакций
  long int       Date;     // Дата создания набора (YYYYMMDD)
  long int       Time;     // Время создания набора (секунд от 00:00:00)
  long int       Free;     // Размер свободного участка в конце файла
  unsigned short Ident;    // Идентификатор последней задачи
    signed short Tasks;    // Число подключенных задач
}
  TACHEAD;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ВЕДЕНИЕ ПРОТОКОЛА ТРАНЗАКЦИЙ +++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef class _DLLCLASS TTransaction
{
 public:

 TTransaction();
 ~TTransaction();

 public:

 char   LogName[MAX_PATH];// Имя файла журнала транзакций
 HANDLE File_TAC;         // Идентификатор файла

 int    IsAction;         // Признак открытой на запись транзакции
 ACTIONHEAD * Head;       // Заголовок открытой на запись транзакции

 int    ReadNumber;       // Номер считываемой транзакции
 int    ReadOffset;       // Смещение на текущую транзакцию
                          // для чтения
 ACTIONHEAD ReadHead;     // Заголовок считываемой транзакции

 TACHEAD  TacHead;        // Заголовок файла журнала

 int Iswrite;             // Разрешение на запись
 int LastError;           // Код ошибки последней операции

 int IsLongAction;        // Признак "длинной" транзакции

 char Buffer[TACBUFLENGTH];  // Буфер транзакции

 unsigned short TaskIdent;   // Идентификатор текущей задачи
 unsigned short Align;       

#if defined(WIN32API) && !defined(WINCE)
 char UserName[MAX_COMPUTERNAME_LENGTH + 4];     
#else
 char UserName[32];                              
#endif
}
  TTransaction;

typedef TTransaction TTRANSACTION;


 // Открыть журнал транзакций
 // Если журнала нет или структура ошибочна - создается новый журнал
 // При ошибке возвращает ноль
 int _fastcall trOpen(TTRANSACTION *transaction, const char * name);

 // Очистить журнал транзакций
 // При ошибке возвращает ноль
 int _fastcall trClear(TTRANSACTION *transaction);

 // Закрыть журнал транзакций
 void _fastcall trClose(TTRANSACTION *transaction);

 // Запросить число транзакций в журнале
 // При ошибке возвращает ноль
 int _fastcall trCount(TTRANSACTION *transaction);

 // Запросить число подключенных к карте пользователей
 // При ошибке возвращает ноль
 int _fastcall trGetUserCount(TTRANSACTION *transaction);

 // Запросить дату создания журнала
 // date - дата в формате "YYYYMMDD"
 // time - время в формате "число секунд от 00:00:00"
 // на указанную дату
 // При ошибке возвращает ноль
 int _fastcall trDate(TTRANSACTION *transaction,
                      long int * date, long int * time);

 // Открыть запись транзакции
 // type - тип транзакции (от 0x4000 до 0х0FFFF - за Панорамой)
 // При ошибке возвращает ноль
 int _fastcall trCreateAction(TTRANSACTION *transaction, int type);

 // Внести в описание транзакции сведения об операции
 // При ошибке возвращает ноль
 int _fastcall trPutRecord(TTRANSACTION *transaction, ACTIONRECORD * record);

 // Закрыть запись транзакции
 void _fastcall trCommitAction(TTRANSACTION *transaction, int longaction);

 // Запросить номер первой транзакции,выполненной
 // после указанных даты и времени
 // date - дата в формате "YYYYMMDD"
 // time - время в формате "число секунд от 00:00:00"
 // на указанную дату
 // При ошибке возвращает ноль
 int _fastcall trGetActionNumberByTime(TTRANSACTION *transaction,
                                       long int date, long int time);

 // Считать заголовок описания транзакции из журнала
 // number - последовательный номер транзакции
 // (от 1 до Count(...)).
 // При ошибке возвращает ноль,
 // иначе - число операций в транзакции
 int _fastcall trReadAction(TTRANSACTION *transaction,
                            int number, ACTIONHEAD * head);

 // Считать заголовок описания последней не отмененной транзакции
 // задачи из журнала
 // Если после транзакции выполнялась сортировка карты
 // или журнал пуст - возвращает ноль
 // При ошибке возвращает ноль,                           
 // иначе - номер транзакции
 int _fastcall trReadLastAction(TTRANSACTION *transaction, int flag);

 // Пометить транзакцию как отмененную
 // При ошибке возвращает ноль,
 int _fastcall trMarkAction(TTRANSACTION *transaction, int number);

 // Запросить сведения об операции
 // number - номер операции (от 1 до ReadAction(...))
 // При ошибке возвращает ноль
 int _fastcall trGetActionRecord(TTRANSACTION *transaction,
                                 int number, ACTIONRECORD * record);

 // Запросить количество операций в транзакции
 // При ошибке возвращает ноль
 int _fastcall trGetActionRecordCount(TTRANSACTION *transaction);

 // Создать журнал транзакций
 // При ошибке возвращает ноль
 int _fastcall trCreate(TTRANSACTION *transaction, const char * name);

 // Записать данные в журнал
 // При ошибке возвращает ноль
 int _fastcall trWrite(TTRANSACTION *transaction,
                       int offset,const char * address, int size);

 // Cчитать данные из журнала
 // При ошибке возвращает ноль
 int _fastcall trRead(TTRANSACTION *transaction,
                      int offset,char * address, int size);

 // Занять доступ к журналу
 // При ошибке возвращает ноль
 int _fastcall trLock(TTRANSACTION *transaction);

 // Освободить доступ к журналу
 void _fastcall trUnlock(TTRANSACTION *transaction);

#endif  // MAPTRACT_H

