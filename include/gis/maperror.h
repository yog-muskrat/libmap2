
#if !defined(MAPERROR_H)
#define MAPERROR_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifndef MAPERR_RH
  #include "maperr.rh"
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  ОБРАБОТКА СООБЩЕНИЙ ОБ ОШИБКАХ   ++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TMapError
{
public:

 TMapError()
   {
     FileLog = 0;
     Error(0);
   }

 ~TMapError()
   {
     Close(0);
   }

 /***************************************************************
 *                                                              *
 *      Управление доступом к журналу района работ              *
 *                                                              *
 ***************************************************************/

public:

 // Закрыть журнал района работ
 // message != 0, если закрытие контрольное, для сохранения файла
 // При ошибке возвращает ноль
 int Close(int message = 1);

 // Сохранить журнал района работ
 // При ошибке возвращает ноль
 int Commit();

 // Проверить доступность журнала для записи
 // При ошибке возвращает ноль
 int IsLogActive() { return (File() != 0); }

 // Запросить код языка сообщений
 // (1 - английский, 2 - русский, ...)
 int LanguageCode();

 // Запросить идентификатор окна для обработки сообщений
 HWND MessageHandle() { return Handle; }

 // Установить идентификатор окна для обработки сообщений
 HWND MessageHandle(HWND handle)  { return Handle = handle; }

 // Запросить полное имя (путь) файла журнала
 const char * NameLOG() { return Name_LOG; }

 // Открыть журнал района работ
 // При ошибке возвращает ноль
 int Open(const char * name,int message = 1);

 // Отправить сообщение окну обработки сообщений
 // Посылает сообщение IMM_ERROR (см. mapmacro.h)
 long int SendMessage(long int code,long int parm);

 // Записать сообщение в журнал
 // message - адрес строки сообщения
 // type    - тип сообщения (см. MESSAGETYPE)
 // При ошибке возвращает ноль
 int WriteToLog(const char * message,int type);


protected :

 // Запросить идентификатор файла журнала
 HANDLE File() { return FileLog; }


 /***************************************************************
 *                                                              *
 *      Выдача на консоль и в журнал сообщений                  *
 *                                                              *
 ***************************************************************/

public:

 // Запросить код ошибки выполнения последней операции
 // Если ошибок не было, возвращает ноль
 long int Error() { return (LastError); }

 // Установить код ошибки выполнения последней операции
 long int Error(int error) { return (LastError = error); }

 // Cообщить об ошибке при обработке данных
 void ErrorMessage(int code,const char * filename);

public:

 long int LastError;      // КОД ОШИБКИ ПОСЛЕДНЕЙ ОПЕРАЦИИ
 HANDLE   FileLog;        // ИДЕНТИФИКАТОР ФАЙЛА ЖУРНАЛА
 char Name_LOG[MAX_PATH]; // ПОЛНОЕ ИМЯ ФАЙЛА ЖУРНАЛА РАЙОНА
 HWND Handle;             // ИДЕНТИФИКАТОР ОКНА ДЛЯ ОБРАБОТКИ СООБЩЕНИЙ
};

typedef TMapError TMAPERRORDATA;


// Запрос разрешения на выдачу сообщения на экран
int IsMessageEnable();

// Открыть журнал района работ
// При ошибке возвращает ноль
int _fastcall meOpenErrorLog(TMAPERRORDATA* data,
                             const char * name, int mode);

// Закрыть журнал района работ
// При ошибке возвращает ноль
int _fastcall meCloseErrorLog(TMAPERRORDATA* data, int mode);

// Записать сообщение в журнал
// message - адрес строки сообщения
// type    - тип сообщения (см. MESSAGETYPE)
// При ошибке возвращает ноль
int _fastcall meWriteToErrorLog(TMAPERRORDATA* data,
                                const char * message, int type);

// Сохранить журнал района работ
// При ошибке возвращает ноль
int _fastcall meCommitErrorLog(TMAPERRORDATA* data);

// Cообщить об ошибке при обработке данных
void _fastcall meErrorMessage(TMAPERRORDATA* data, int code,
                              const char * filename);

extern "C"
{
  void _MAPAPI ErrorMessage(int code, const char * filename);
}

#endif

