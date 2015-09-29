
#if !defined(MAPGROUP_H)
#define MAPGROUP_H

#ifdef __cplusplus

#ifndef MAPMACRO_H
  #include "mapmacro.h"
#endif

typedef struct   // ЗАГОЛОВОК ОПИСАHИЯ ГРУППОВОГО ОБ'ЕКТА
{
   int Ident       ;  // 0x7FFF7FFFF
   LONG Length ;  // ДЛИHА ОПИСАHИЯ,HЕ ВКЛЮЧАЯ РЕЗЕРВ !!
   int GroupNumber ;  // HОМЕР ГРУППЫ
   int Type        ;  // ТИП ГРУППЫ
   int ListCount   ;  // ЧИСЛО ЛИСТОВ,СОДЕРЖАЩИХ ГРУППУ
}
  HEADRECGDX;

typedef struct   // ОПИСАHИЕ НОМЕРОВ ОБ'ЕКТОВ В ЛИСТЕ
{
  int Number;       // НОМЕР ОБ'ЕКТА В ЛИСТЕ
  KEY Key;          // УНИКАЛЬНЫЙ НОМЕР ОБ'ЕКТА В ЛИСТЕ
}
  NUMBERKEY;

// ПОСЛЕ ЗАГОЛОВКА ОПИСАHИЯ ГРУППЫ ИДЕТ ОПИСАHИЕ ЧАСТИ ГРУППЫ
// В ПРЕДЕЛАХ ОТДЕЛЬHОГО ЛИСТА, ЧИСЛО ЧАСТЕЙ = ЧИСЛУ ЛИСТОВ
// ОПИСАHИЕ В ПРЕДЕЛАХ ЛИСТА СОСТОИТ ИЗ НОМЕРА ЛИСТА (4 БАЙТА),
// КОЛИЧЕСТВА ОБЬЕКТОВ (4 БАЙТА) И ПОСЛЕДОВАТЕЛЬНЫХ НОМЕРОВ
// ОБ'ЕКТОВ + УНИКАЛЬНЫХ НОМЕРОВ ОБ'ЕКТОВ В ЛИСТЕ, ВХОДЯЩИХ В ГРУППУ HА ОТДЕЛЬHОМ ЛИСТЕ (4 БАЙТА).

#define RESERVGROUP 64

typedef struct      // СТРУКТУРА МИНИМАЛЬНОЙ ЗАПИСИ
{                   // (ОДИН ОБ'ЕКТ В ГРУППЕ)
  HEADRECGDX Gdx;   // ЗАГОЛОВОК ЗАПИСИ
  int List;         // НОМЕР ЛИСТА В РАЙОНЕ
  int Count;        // ЧИСЛО ОБ'ЕКТОВ В ГРУППЕ С ДАННОГО ЛИСТА
  NUMBERKEY Number; // НОМЕР ОБ'ЕКТА В ЛИСТЕ +
                    // УНИКАЛЬНЫЙ НОМЕР ОБ'ЕКТА В ЛИСТЕ
  char  Reserv[RESERVGROUP]; // РЕЗЕРВ ДЛЯ РЕДАКТИРОВАНИЯ
}
  MINGDXRECORD;

#define GROUPBUFSIZE (32*1024L)   // МАКСИМАЛЬНЫЙ РАЗМЕР ЗАПИСИ
#define RECGDXIDENT  0x7FFF7FFF   // ИДЕНТИФИКАТОР ЗАПИСИ

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++  ОБРАБОТКА ГРУППОВЫХ ОБ'ЕКТОВ  +++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TMap;

class _DLLCLASS TObjectGroup
{

public :

 TObjectGroup()
  {
    RecordGdx = 0;
    Memory    = 0;
    LengthMem = 0;
  }

 TObjectGroup(HEADRECGDX * address)
  {
    Memory = 0;
    Load(address);
  }

 TObjectGroup(TObjectGroup * record)
  {
    Memory = 0;
    Load(record);
  }

 ~TObjectGroup() { Clear(); }

 // Удалить описание группы

 void Clear() { Record((HEADRECGDX *)0,0); }

 // Создать запись групповых объектов
 // number - номер группы,
 // если равен 0 - при записи в файл формируется автоматически.
 // Выделяется область памяти под максимальную запись (32Кб)
 // (Групповой объект может состоять из 8000 объектов)
 // При ошибке возвращает ноль

 int Create(int number = 0,int type = 0);

 // Запросить - сформировано ли описание группы
 // При ошибке возвращает ноль

 int IsActive() { return (RecordGdx != 0); }

 // Загрузить запись групповых объектов из буфера
 // При ошибке возвращает ноль

 int Load(HEADRECGDX * address);
 int Load(TObjectGroup * group)
  {
    if (Load((HEADRECGDX *)(group->Address())))
       {
       NumberKey = group->NumberKey;
       ObjectCountAll = group->ObjectCountAll;
       return 1;
       }
    return 0;
  }

 // Установить адрес записи групповых объектов
 // При ошибке возвращает ноль

 int Record(HEADRECGDX * address,long int length);


 /***************************************************************
 *                                                              *
 *       ФУНКЦИИ ДОСТУПА К ОПИСАНИЮ ГРУППЫ ОБ'ЕКТОВ             *
 *                                                              *
 ***************************************************************/

public :

 // Запросить адрес записи групповых объектов
 // При ошибке возвращает ноль

 char * Address() { return (char *)RecordGdx; }

 // Проверить корректность записи
 // При ошибке возвращает ноль

 int Check()
    {
      if (RecordGdx == 0) return 0;
      return (RecordGdx->Ident == RECGDXIDENT);
    }

 // Запросить/Установить номер группы
 // При ошибке возвращает ноль

 int Number()
    {
      if (RecordGdx == 0) return 0;
      return RecordGdx->GroupNumber;
    }

 int Number(int number)
    {
      if (RecordGdx == 0) return 0;
      return RecordGdx->GroupNumber = number;
    }

 // Запросить размер записи (не включая резерв)
 // При ошибке возвращает ноль

 long int Length()
    {
      if (RecordGdx == 0) return 0;
      return RecordGdx->Length;
    }

 // Запросить полный размер записи (включая резерв)
 // При ошибке возвращает ноль

 long int FullLength()
    {
      if (RecordGdx == 0) return 0;
      return RecordGdx->Length + sizeof(RESERVGROUP);
    }


 // Запросить тип группы
 // При ошибке возвращает ноль

 int Type()
    {
      if (RecordGdx == 0) return 0;
      return RecordGdx->Type;
    }


 // Установить тип группы
 // При ошибке возвращает ноль

 int Type(int type)
    {
      if (RecordGdx == 0) return 0;
      return (RecordGdx->Type = type);
    }

 // Добавить в группу новый объект
 // list  - номер листа
 // number - номер объекта + уникальный номер объекта
 // При ошибке возвращает ноль

 int AppendObject(int list, NUMBERKEY number);


 // Удалить объект из группы
 // list  - номер листа
 // number- номер объекта
 // При ошибке возвращает ноль

 int DeleteObject(int list, int number);

 // Удалить объект из группы
 // list  - номер листа
 // number- уникальный номер объекта
 // При ошибке возвращает ноль

 int DeleteObject(int list, KEY number);

 // Поиск записи по номеру листа и номеру объекта в листе
 // list - номер листа
 // number - номер объекта
 // При ошибке возвращает ноль

 int FindObjectNumber(int list, int number);

 // Поиск записи по номеру листа и уникальному номеру объекта
 // list - номер листа
 // number - уникальный номер объекта
 // При ошибке возвращает ноль

 int FindObjectNumber(int list, KEY number);

 // Запросить число листов в группе
 // При ошибке возвращает ноль

 int ListCount()
    {
      if (RecordGdx == 0) return 0;
      return RecordGdx->ListCount;
    }

 // Определение номера листа по порядковому номеру листа в группе
 // number - порядковый номер листа c 1
 // При ошибке возвращает ноль

 int ListNumber(int number);

 // Запрос следующего объекта в группе
 // по номеру листа и номеру объекта в листе
 // list - номер листа
 // number - номер объекта
 // При ошибке возвращает ноль

 int NextObjectNumber(int list, int number);

 // Запросить число объектов в листе
 // list - номер листа
 // При ошибке возвращает ноль

 int ObjectCount(int list);

 // Запросить число объектов в группе
 // При ошибке возвращает ноль

 int ObjectCountGroup(){return ObjectCountAll;}

 // Определение номера объекта по номеру листа
 // и порядковому номеру объекта  в группе
 // list - номер листа
 // number - порядковый номер объекта в группе (c 1)
 // При ошибке возвращает ноль

 int ObjectNumber(int list, int number);

 // Определение уникального номера объекта по номеру листа
 // и порядковому номеру объекта  в группе
 // list - номер листа
 // number - порядковый номер объекта в группе (c 1)
 // При ошибке возвращает ноль

 KEY ObjectKey(int list, int number);


 // Определение уникального номера объекта по номеру листа
 // и порядковому номеру объекта в листе
 // list - номер листа
 // number - порядковый номер объекта в листе (c 1)
 // При ошибке возвращает ноль

 KEY ObjectKeyNumber(int list, int number);

#ifndef LINUXAPI
 // Чтение зaписи описaния гpуппы number в область record
 // Возвращает число считанных байт
 // При ошибке возвращает ноль

 int ReadGroup(TMap * map, int number = 0);

 // Добaвление/Обновление зaписи описaния гpуппы
 // При ошибке возвращает ноль

 int WriteGroup(TMap * map);
#endif

 // Установить общее число объектов в группе
 // При ошибке возвращает ноль

 void SetObjectCountAll();

 protected:

 //  Увеличить размер буфера данных на buffersize
 //  При ошибке возвращает ноль, иначе - новый размер буфера

 long int Realloc(long int buffersize = DATABUFFERSIZE);


public:

int          List;      // Текущий номер листа

protected :

HEADRECGDX * RecordGdx; // Указатель на запись

long int     LengthMem; // Длина буфера
char *       Memory;    // Адрес выделенной области памяти
NUMBERKEY *  NumberKey; // Указатель на описание номеров объектов в листе
int          ObjectCountAll; // Общее число объектов в группе
};

#endif  // __cplusplus

#endif
