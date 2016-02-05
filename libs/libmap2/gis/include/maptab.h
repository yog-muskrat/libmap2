
#ifndef MAPTAB_H
#define MAPTAB_H

#ifndef MAPTYPE_H
 #include "maptype.h"
#endif

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Файл с набором записей фиксированной длины
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define TABVERSION 0x010001
#define LABEL_TAB  0x00424154L     // TAB0


typedef struct TABHEAD     // Заголовок к набору записей
{
  long Ident;              // Идентификатор    (LABEL_TAB)
  long Length;             // Длина файла
  long Version;            // Версия структуры (TABVERSION)
  long Mode;               // Состояние данных (изменяется при редактировании)
  long OffsetBegin;        // Начало таблицы смещений в файле
  long OffsetCount;        // Число записей в таблице смещений
  long RecordBegin;        // Начало таблицы записей в файле
  long RecordCount;        // Количество записей
  long RecordSize;         // Размер одной записи
  long Reserv[23];         // Резерв (д.б. 0)
}
  TABHEAD;

#define OFFBLOCKSIZE  (64*1024L)           // РАЗМЕР БЛОКА СМЕЩЕНИЙ
#define RECBLOCKCOUNT 2048L                // ЧИСЛО ЗАПИСЕЙ В БЛОКЕ ЗАПИСЕЙ

typedef struct TABBUFFER
{
 HANDLE        File;           // Идентификатор файла данных
 unsigned long Size;           // Размер области памяти
 TABHEAD       Head;           // Заголовок файла
 long          IsDirty;        // Признак обновления заголовка
 unsigned long Lock;           // Начало блокируемой области в файле 
 unsigned long Error;          // Код ошибки последней операции
 char *        Offset;         // Адрес области памяти под смещения на вектора
 unsigned long OffsetMin;      // Начало блока смещений в файле
 unsigned long OffsetMax;      // Конец блока смещений в файле
 unsigned long OffsetSize;     // Размер области смещений
 long          IsOffsetDirty;  // Признак обновления буфера смещений
 char      *   Record;         // Адрес области памяти под записи
 unsigned long RecordMin;      // Начало блока векторов в файле
 unsigned long RecordMax;      // Конец блока векторов в файле
 unsigned long RecordSize;     // Размер области векторов
 long          IsRecordDirty;  // Признак обновления буфера записей 
 unsigned long MaxCount;       // Предельное число записей
 char          Name[MAX_PATH]; // Имя файла
}
 TABBUFFER;


typedef class _DLLCLASS TTableFile : public TABBUFFER
{
 public:

   TTableFile();
   ~TTableFile();

   // Создать файл с набором записей
   // При успешном завершении возвращает ненулевое значение
   // recordsize - размер записи в файле
   int _fastcall Create(const char * name, int recordsize);

   // Открыть файл с набором записей
   // При успешном завершении возвращает ненулевое значение
   int _fastcall Open(const char * name);

   // Закрыть файл
   void _fastcall Close();

   // Запросить адрес записи по ее номеру
   char * _fastcall GetRecord(int number);

   // Обновить запись по номеру
   // force - признак немедленного обновления записи в файле
   int _fastcall PutRecord(const char * record,
                           int number, int force);
}
  TTableFile;

#endif
