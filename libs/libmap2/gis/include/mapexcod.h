
#ifndef MAPEXCOD_H
#define MAPEXCOD_H

#ifndef MAPDEF_H
 #include "mapdef.h"
#endif

typedef struct EXCODEHEAD
{
  LONG Ident;     // Идентификатор записи
  LONG Length;    // Длина таблицы и заголовка
  LONG Mode;      // Модификация классификатора
  LONG Style;     // Состояние классификатора
  LONG Size;      // Контрольный размер файла
  LONG Reserv[6]; // Резерв
  LONG Count;     // Число записей (для контроля)
}
  EXCODEHEAD;

#define EXCODEIDENT 0x7EEE7EEE

// Класс создания таблицы внешних кодов в паспорте карты

typedef struct TMapExcode
{
 public:

 // Создать таблицу
 TMapExcode();

 // Закрыть таблицу
 ~TMapExcode();

 // Открыть таблицу
 int _fastcall Open(TMap * map);

 // Сохранить таблицу объектов в паспорте карты
 // При ошибке возвращает ноль
 int _fastcall Save();

 // Закрыть таблицу
 void _fastcall Close();

 // Перекодировать объекты и сохранить таблицу объектов
 // в паспорте карты (при необходимости)
 // При ошибке возвращает ноль
 int _fastcall CheckCodeList(TMap * map);

 public:

  EXCODEHEAD  TableHead;   // Заголовок таблицы
  TMap * Map;              // Обрабатываемая карта
  char * Memory;           // Память под записи таблицы
  int    Length;           // Длина области памяти
}
 TMapExcode;

typedef TMapExcode TEXCODEDATA;

#endif // MAPEXCOD_H
