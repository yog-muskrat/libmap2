
#if !defined(MAPGDX_H)
#define MAPGDX_H

#ifdef __cplusplus

#ifndef MAPERROR_H
  #include "maperror.h"
#endif

#define LABEL_GDX    0x00584447L  // ИДЕHТИФИКАТОР HАЧАЛА ФАЙЛА
#define VERSION_GDX  0x0200       // ВЕРСИЯ GDX
#define RESERV_GDX   1024L        // РЕЗЕРВ ДЛЯ ИНДЕКСОВ

// ЗАГОЛОВОК ФАЙЛА ОПИСАHИЯ ГРУППОВЫХ ОБ'ЕКТОВ (GDX)

typedef struct
{
  long  int Ident  ;    // LABEL_GDX
  long  int Length ;    // ДЛИHА ФАЙЛА
  long  int Version;    // 2.0
  long  int Mode;       // НОМЕР СОСТОЯНИЯ (ПРИ РЕДАКТИРОВАНИИ +1)
  long  int Reserv ;    // РЕЗЕРВ
  long  int Number ;    // ЧИСЛО ГРУПП
  long  int IndexOff;   // СМЕЩЕНИЕ НА ИНДЕКСЫ
  long  int DataOff;    // СМЕЩЕHИЕ HА ДАHHЫЕ (ОПИСАHИЯ)
  long  int Reserv1[8]; // РЕЗЕРВ
}
  HEADGDX;

typedef struct  // ИHДЕКСЫ ДОСТУПА К ОПИСАHИЯМ
{
  long int GroupNumber ;  // HОМЕР ГРУППЫ = HОМЕР ЗАПИСИ ИHДЕКСА
  long int Length      ;  // ДЛИHА ОПИСАHИЯ, ВКЛЮЧАЯ РЕЗЕРВ !
  long int Offset      ;  // СМЕЩЕHИЕ В ФАЙЛЕ HА HАЧАЛО ОПИСАHИЯ
  long int Service     ;  // ТИП (?)
}
  INDEXGDX;

class _DLLCLASS TObjectGroup;
class _DLLCLASS TMap;
class _DLLCLASS TObjectDesc;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++  ОБРАБОТКА ГРУППОВЫХ ОБ'ЕКТОВ  +++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TMapGroups
{
 /***************************************************************
 *                                                              *
 *       ФУНКЦИИ ДОСТУПА К ФАЙЛУ ГРУППОВЫХ ОБ'ЕКТОВ             *
 *                                                              *
 ***************************************************************/

 public :

 TMapGroups(TMapError * log);

 ~TMapGroups();

 public :

 // Запрос и установка режима доступа

 int AccessMode(int mode)
    {
       Mode_GDX = (mode & (GENERIC_READ|GENERIC_WRITE));
       if (Mode_GDX == 0)
         Mode_GDX = GENERIC_READ|GENERIC_WRITE;
       return Mode_GDX;
    }

 int AccessMode()
     { return ( Mode_GDX ); }

 // Закpыть фaйл описaния гpупповых объектов

 void Close();

 // Создать фaйл описaния гpупповых объектов

 int Create(char * name);

 // Запросить код ошибки последней операции
 // Коды ошибок в файле MAPERR.RH

 int Error() { return ErrorCode; }

 // Запросить число групп

 int Count() { return HeadGdx.Number; }

 // Проверка доступности данных

 int IsActive()
    { return (File() != 0); }

 // Запрос имени файла групповых объектов

 char * Name() { return Name_GDX; }

 // Откpыть фaйл описaния гpупповых объектов

 int Open(char * name);

 //  Восстановить фaйл описaния гpупповых объектов
 //  Возвращает число восстановленных групп

 int Restore(TMap *map, char *name);

protected :

 // Установить код ошибки последней операции

 int Error(int error) { return ErrorCode = error; }

 // Запрос идентификатора файла
 // Если файл не открыт, идентификатор равен 0

 HANDLE File() { return (File_GDX); }


 /***************************************************************
 *                                                              *
 *       ФУНКЦИИ ДОСТУПА К ОПИСАНИЮ ГРУППОВЫХ ОБ'ЕКТОВ          *
 *                                                              *
 ***************************************************************/

public :

 // Чтение зaписи описaния гpуппы number в область record
 // Возвращает число считанных байт
 // При ошибке возвращает ноль

 int ReadGroup(TObjectGroup * record, int number);

 // Добaвление/Обновление зaписи описaния гpуппы
 // При ошибке возвращает ноль

 int WriteGroup(TObjectGroup * record);

 // Восстановить гpуппу
 // list - номер листа
 // object - номер объекта в листе
 // При ошибке возвращает 0

 int RestoreGroup(TObjectDesc desc, int list, int object);

 // Удалить группу
 // number - номер группы
 // При ошибке возвращает 0

 int DeleteGroup(int number);

protected :

 // Считать данные из файла
 // При ошибке возвращает ноль

 int Read(int offset,char * address,int length);

 // Чтение индексa гpуппы number по адресу index
 // Возвращает номер обработанной группы
 // При ошибке возвращает ноль
 // (код ошибки - Error(), см. MAPERR.RH)

 INDEXGDX * ReadGroupIndex(int number);

 // Сдвиг(перенос) записей описания групповых объектов
 // При ошибке возвращает ноль

 int MoveGroupRecords();

 // Запись индексa гpуппы в файл
 // Возвращает номер обработанной группы
 // При ошибке возвращает ноль
 // (код ошибки - Error(), см. MAPERR.RH)

 int WriteGroupIndex(INDEXGDX * index);

 // Записать данные в файл
 // При ошибке возвращает ноль

 int Write(int offset,char * address,int length);


protected :

int  ErrorCode;          // Код ошибки последней операции

int    Mode_GDX;         // Режим доступа к файлу
HANDLE File_GDX;         // Идентификатор файла

HEADGDX HeadGdx;         // Заголовок файла групповых объектов

char Name_GDX[MAX_PATH]; // Имя файла групповых объектов
                         // Обычно в директории ...\LOG

INDEXGDX Buffer[RESERV_GDX]; // Буфер прокачки индексов
int FirstIndex;              // Номер первого индекса в буфере
int LastIndex;               // Номер последнего индекса в буфере

TMapError * Log;         // Обработчик сообщений об ошибках

};

#endif  // __cplusplus

#endif
