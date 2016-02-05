#ifndef RSCFL3D_H
#define RSCFL3D_H
#include "m3dgdi.h"

// Содержит параметры объектов  и относящиеся текстуры. Не может ссылаться на другие
// файлы 3D параметров.
// Может содержать лишние текстуры.
// К одному классификатору можно подключить один или несколько файлов параметров.

// Тип записей
#define OBJECT_PARAMETERS   1  // Параметры объекта
#define OBJECT_TEXTURE      2  // Текстура
#define TAB_SEMANTIC        3  // Таблица соответствия семантик
#define TAB_RULES           4  // Правила задания описания по объекту и семантике
#define TAB_MATERIAL        5  // Описание материала

#define FIRSTKEY_PARAMETERS  0x4F0000   // минимальный ключ записи параметров
#define FIRSTKEY_TEXTURE     0x540000   // минимальный ключ записи текстуры
#define FIRSTKEY_SEMANTIC    0x530000   // минимальный ключ записи семантик
#define FIRSTKEY_RULES       0x520000   // минимальный ключ записи правил
#define FIRSTKEY_MATERIAL    0x4D0000   // минимальный ключ записи материала
/*
// Масштабы для которых применяется файл
  {                                     0
   10L,    25L,                         1
   50L, 100L,   200L,                   2
   500L,   1000L, 2000L,                3
   5000L,  10000L, 25000L,              4
   50000L, 100000L,200000L,             5
   500000L,1000000L, 2500000L,          6
   5000000L,10000000L,                  7
   50000000L,40000000L                  8
  }


*/

// Заголовок файла
typedef struct P3DHEAD
     {
      unsigned long  int Label    ;    // Метка файла .P3D
      unsigned long  int Length   ;    // Длина файла
      unsigned long  int Version  ;    // Версия  (100)
      unsigned long  int Count    ;    // Количество записей
      char               IsWrite  ;    // Флаг открытия файла(1 - чтение-запись)
                                       // O - только запись
                                       // 2 - новый
      char               ScaleIndex;   // Индекс масштабного ряда
      char               Reserv[2];    // Резерв
      unsigned long  int Reserv1  ;    // Резерв1
     }
  P3DHEAD;

// Заголовок к записи любого типа
typedef struct RECHEAD
  {
      unsigned long  int Length  ;    // Длина записи  c заголовком
      unsigned long  int Type    ;    // Тип записи
      long int           Key     ;    // Ключ записи уникален для данного
                                      // файла и данного типа
      long int           Reserv  ;    // Резерв
      char               Name[32];    // Название параметров, текстуры или семантики
  }
  RECHEAD;

// Запись текстуры
typedef struct RECTEXTURE
  {
     unsigned long int Length   ;    // Длина записи
     unsigned long Height       ;    // Высота картинки
     unsigned long Width        ;    // Ширина картинки
     unsigned char Reserv[4]    ;    // Резерв
  }
  RECTEXTURE;

// Запись параметров
typedef struct RECPARM
  {
    unsigned long int Length  ;  // Длина записи
    unsigned long Type        ;  // Тип метрики (1 - 1т, 2- 2т,0 - много)
                                 // Необходим для отображения параметров не
                                 // имеющих привязки к объектам данного RSC
                                 // Далее параметры
  }
  RECPARM;

// Запись материала - структура ACT3DMATERIALMODE из m3dgdi.h

// Запись семантики
typedef struct RECSEM
  {
    unsigned long int Length    ;  // Длина записи
    unsigned long int RscCode   ;  // Последний назначенный код в RSC
    unsigned long int TypeValue ;  // Тип значения (числовой, перечислимый,символьный)
    unsigned long int CountItem ;  // При перечислимых - количество значений
                                   // далее значения ITEMSEM
  }
  RECSEM;

 // Запись значений семантики
typedef struct ITEMSEM
  {
    unsigned long int RscCode   ;  // Последний назначенный код в RSC
    unsigned long int FileCode  ;  // Код в файле
    char              Name[32]  ;  // Имя
  }
  ITEMSEM;

#endif  // RSCFL3D_H
