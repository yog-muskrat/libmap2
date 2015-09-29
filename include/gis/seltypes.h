
#ifndef SELTYPES_H
#define SELTYPES_H

// Описание структуры параметров для фильтра листов

typedef  char LISTSNAME[MAX_PATH];   // Имя листа

typedef struct  NAMESARRAY
{
   long int   Size;          // Размер структуры
   long int   Count;         // Количество записей LISTSNAME
   LISTSNAME  Record[1];     // Записи
}
   NAMESARRAY;

#endif          // SELTYPES_H
