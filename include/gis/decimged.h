
#ifndef DECIMGED_H
#define DECIMGED_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifndef MAPGDI_H
  #include "mapgdi.h"    // (146) и (57) - функции
#endif

#define IMGBUFFERSIZE (4 * 1024L)
#ifdef __cplusplus
class _DLLCLASS  TDecorImageEdit
{


 /*********************************************************
 *                                                        *
 *       Функции инициализации данных класса              *
 *                                                        *
 *********************************************************/

 public :

 // Установить адрес начала записи

  TDecorImageEdit()
   {
	    Memory = 0; // Память не запрашивалась
  	  SetBuffer(0,0L);
   }

  TDecorImageEdit(char * parm,long int length)
  	{
     Memory = 0; // Память не запрашивалась
     SetBuffer(parm,length);
  	}

  TDecorImageEdit(TDecorImageEdit * data)
   {
     Memory = 0; // Память не запрашивалась
     Load(data);
  	}


  ~TDecorImageEdit() { SetBuffer(0,0L); }

 // Запросить адрес начала записи

  char * Address() { return (char *)Decor;}

 // Проинициализировать структуру данных
 // При ошибке возвращает ноль

 int Create();

 // Очистить запись

 int Clear();

 // Запросить/Установить признак редактирования данных

  int IsDirty() { return Isdirty; }

  int IsDirty(int dirty) { return (Isdirty = dirty && 1); }

 // Запросить наличие векторных объектов
  int IsVect();

 // Запросить длину записи

  int Length()
   {
     if (Decor == 0) return 0;
     return Decor->Length;
   }

 // Загрузить данные из указанной записи
 // Запись длинее 64 Кб не загружается
 // При ошибке возвращает ноль,
 // иначе - длину загруженной записи

  int Load(IMGDECORATELINE * decor);

 //  Загрузить описание оформленного объекта из указанной записи
 //  Запись типа IMGDECORATE
 //  Запись длинее 64 Кб не загружается                 
  int Load(IMGDECORATE * decor);

  int Load(TDecorImageEdit * decor)
     {
       return Load((IMGDECORATE *)(decor->Address()));
     }

 // Установить адрес начала записи
 // address - адрес начала, length - длина буфера.
 // Память выделенная Allocate() освобождается.

  void SetBuffer(char * address,long int length);

 // Выгрузить данные из указанной записи
 // Если запись длинее выделенной области,
 // то выгрузка не производится
 // При ошибке возвращает ноль,
 // иначе - длину выгруженной записи

  int Unload(char * address,int length);

 protected :

 // Выделить память под запись метрики
 // Проинициализировать структуру данных
 // Создается идентификатор записи
 // Память автоматически освобождается в деструкторе
 // или при назначении другой области с помощью
 // SetBuffer(...), в том числе, SetBuffer(0,0).
 // При ошибке возвращает ноль

  int Allocate(int size = IMGBUFFERSIZE);

 // Увеличить размер буфера метрики
 // При ошибке возвращает ноль, иначе - новый размер буфера

 int Realloc();

 /*********************************************************
 *                                                        *
 *     Перемещение указателя по частям объекта            *
 *                                                        *
 *********************************************************/

 public :

 // Установить указатель на начало параметров заданной части
 // number - последовательный номер части,(1-7)
 // При ошибке возвращает ноль

 char * DatePart(int number = 1);

  // Установить указатель на дескриптор части
  // При ошибке возвращает ноль

  char * GoPart(int number = 0);


 /*********************************************************
 *                                                        *
 *         Запрос данных из текущей части                 *
 *       (в соответствии с текущим положением указателя)  *
 *                                                        *
 *********************************************************/

 public :

 // Запросить длину параметров отображения текущей части
 // При ошибке возвращает ноль

 int ParmLength()
 {
   if (DescPart == 0) return 0;
  	return ((IMGDECOR *)DescPart)->Length - sizeof(IMGDECOR);
 };

 // Запросить номер текущей части
 // Номер первого фрагмента 1,
 // (DO_BASE,DO_END, ... - см. mapgdi.h)
 // если не установлено возвращает 0

 int NumberPart() { return NumberOfPart; }

 // Запросить функцию отображения текущей части
 // При ошибке возвращает ноль

 int Number()
	 {
  		if (DescPart == 0) return 0;
  		return ((IMGDECOR *)DescPart)->Number;
	 }


 /*********************************************************
 *                                                        *
 *         Функции редактирования структуры записи        *
 *                                                        *
 *********************************************************/

 public :

 // Удалить заданную часть
 // Текущей становится первая часть
 // При ошибке возвращает ноль

 ptrdiff_t DeletePart(int number);

 // Загрузить часть
 // данная часть становится текущей
 int LoadPart(int imglength,int imgnumber,char *data,
                              int number);

 // Выгрузить данные из указанной части
 // Если запись длинее выделенной области,
 // то выгрузка не производится
 // При ошибке возвращает ноль,
 // иначе - длину выгруженной записи

  int UnloadPart(char * address,int length,int numberpart);

  // Загрузить запись

  TDecorImageEdit * operator = (TDecorImageEdit * image)
	    {
       if (Load(image)) return image;
       return 0;
     }

   IMGDECORATELINE * operator = ( IMGDECORATELINE * data)
	    {
       if (Load(data)) return data;
       return 0;
     }

    IMGDECORATE * operator = ( IMGDECORATE * data)
	    {
       if (Load(data)) return data;
       return 0;
     }

   /*VIEPAR * operator = (VIEPAR * data)
    {
      if (Load(data)) return data;
      return 0;
    }*/

protected :

  // Установить адрес начала записи

  char * operator = (char * address)
	    {
       return (char *)(Decor = ( IMGDECORHEAD *)address);
     }


protected :

 IMGDECORHEAD * Decor;   // Адрес записи
 long int BufferLength;  // Размер буфера данных
 int NumberOfPart;       // Текущий номер части
 char * DescPart;        // Указатель на заголовок части
 char * Memory;          // Способ обработки памяти в деструкторе
                								 // (если != 0, освободить)
 int Isdirty;            // Признак редактирования записи

};

#endif //__cplusplus
#endif

