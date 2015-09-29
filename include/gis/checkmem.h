
#ifndef CHECKMEM_H
#define CHECKMEM_H

// ----------------------------------------------------------------------
// Список идентификаторов памяти                   
// ----------------------------------------------------------------------
typedef class THandleList
{
public:

  // Создать список
  // size    - размер элемента списка
  // reserve - минимальное число элементов
  THandleList(int reserve = 512);

  ~THandleList();

  // Добавить запись
  // item - адрес начала записи
  // size - контрольный размер (при несовпадении с size - ошибка)
  // При ошибке возвращает ноль
  int Append(long int item);

  // Проверить - есть ли такой элемент
  // Возвращает номер элемента в списке начиная с 1
  // При ошибке возвращает ноль

  int Check(long int item);

  // Число элементов
  int Count() { return ItemCount; }

  // Очистить список
  void Clear();

  // Удалить список
  // number - номер элемента начиная с 1
  void Delete(int number);

  // Запросить элемент
  // number - номер элемента начиная с 1
  long int Item(int number);

private:

  int Allocate(int size);

public:

  int        ItemCount;
  long int * ItemBegin;
  int        MemorySize;
  int        ItemReserve;
}
  THandleList;



#endif // CHECKMEM_H
