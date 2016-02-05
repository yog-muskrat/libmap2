
#ifndef OBSETAPI_H
#define OBSETAPI_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

typedef  long int  HOBJLIST;

#ifdef __cplusplus
extern "C"
{
#endif

 // Открыть файл списков объектов
 // При ошибке возвращает ноль

 HOBJLIST WINAPI _export obsOpenObjSetFile(HMAP hmap);

 // Закрыть файл списков объектов
 // При ошибке возвращает ноль

 long int WINAPI _export obsCloseObjSetFile(HOBJLIST objset);

 // Запросить число списков в файле
 // При ошибке возвращает ноль (ноль допустим)

 long int WINAPI _export obsObjSetsCount(HOBJLIST objset);

 // Добавить список (запись) в файл
 // name - имя списка в файле
 // (Список формируется из контекстов поиска открытых в hmap карт)
 // При ошибке возвращает ноль

 long int WINAPI _export obsAddObjSet(HOBJLIST objset, HMAP hmap, const char* name);

 // Удалить список (запись) по имени из файла
 // При ошибке возвращает ноль

 long int WINAPI _export obsDeleteObjSet(HOBJLIST objset, const char* name);

 // Найти список (запись) по имени в файле
 // Если запись с именем name имеется в файле, возвращает "1"
 // иначе - ноль.

 long int WINAPI _export obsFindObjSet(HOBJLIST objset, const char* name);

 // Запросить имя списка по номеру в файле
 // При ошибке возвращает ноль

 char* WINAPI _export obsObjSetName(HOBJLIST objset, int number, char *buffer, int bufsize);

 // Проверить наличие объекта карты в списке
 // number - номер списка в файле,
 // info - объект карты.
 // Если объект карты удовлетворяет списку, возвращает "1"
 // иначе - ноль.

 long int WINAPI _export obsTestMapObjectByObjSet(HOBJLIST objset, int number, HOBJ info, HMAP hmap);


 // Проверить наличие карты в списке
 // number - номер списка в файле,
 // info - объект карты.
 // nmap - номер карты
 // Если карта содержится в списке, возвращает "1"
 // иначе - ноль.
 long int WINAPI _export obsTestMapByObjSet(HOBJLIST objset, int number, HMAP hmap, int nmap);

 // Установить hselect по указанной записи файла списков объектов
 // number  - номер списка в файле,
 // hselect - контекст поиска для размещения параметров фильтра объектов,
 // hsite   - идентификатор карты, для которой заполняется контекст поиска
 // Если для hsite имеется запись, возвращает "1"
 // иначе - ноль.
 
 long int WINAPI _export obsSetSelectByObjSet(HOBJLIST objset, int number, HMAP hmap, HSITE hsite, HSELECT hselect);


#ifdef __cplusplus
}       // extern "C"
#endif


#endif  // OBSETAPI_H
