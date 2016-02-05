#if !defined(VECIMGED_H)
#define VECIMGED_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifndef MAPGDI_H
  #include "mapgdi.h"    // (77) и (55) - функции
#endif

#define IMGBUFFERSIZE (4 * 1024L)
#ifdef __cplusplus


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  РЕДАКТИРОВАНИЕ ПАРАМЕТРОВ ОТОБРАЖЕНИЯ ++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Система координат - оконная
// X - слева направо,
// Y - сверху вниз.

class _DLLCLASS TVectorImageEdit
{
 public :

 /*********************************************************
 *                                                        *
 *       Функции инициализации данных класса              *
 *                                                        *
 *********************************************************/

 public :

 // Установить адрес начала записи

  TVectorImageEdit()
   {
	    Memory = 0; // Память не запрашивалась
  	  SetBuffer(0,0L);
   }

  TVectorImageEdit(IMGVECTOREX * vector)
  	{
     Memory = 0; // Память не запрашивалась
     Load(vector);
  	}

  TVectorImageEdit(TVectorImageEdit * data)
   {
     Memory = 0; // Память не запрашивалась
     Load(data);
  	}


  ~TVectorImageEdit() { SetBuffer(0,0L); }

 // Запросить адрес начала записи

  char * Address() { return (char *)Vector;}

 // Проинициализировать структуру данных, число фрагментов = 0
 // При ошибке возвращает ноль

  int Create();

 // Запросить размеры векторного объекта
 // При ошибке возвращает ноль

  int GetImageSize(IMAGESIZE* imagesize);

 // Запросить/Установить признак редактирования данных

  int IsDirty() { return Isdirty; }

  int IsDirty(int dirty) { return (Isdirty = dirty && 1); }

 // Запросить длину записи

  int Length()
   {
     if (Vector == 0) return 0;
     return Vector->Length;
   }

 // Загрузить данные из указанной записи
 // Запись длинее 64 Кб не загружается
 // При ошибке возвращает ноль,
 // иначе - длину загруженной записи

  int Load(IMGVECTOREX * data);
  int Load(TVectorImageEdit * vector)
     {
       return Load((IMGVECTOREX *)(vector->Address()));
     }

 // Запросить число фрагментов,описывающих объект

  int PolyCount()
  {
     if (Vector == 0) return 0;
     return Vector->Count;
   }

 // Установить адрес начала записи
 // address - адрес начала, length - длина буфера.
 // Память выделенная Allocate() освобождается.

  void SetBuffer(IMGVECTOREX * address,long int length = 0);

 // Выгрузить данные из указанной записи
 // Если запись длинее выделенной области,
 // то выгрузка не производится
 // При ошибке возвращает ноль,
 // иначе - длину выгруженной записи

 int Unload(char * address,int length);

 // Заполним поле Border максимальные габариты знака в мкм от точки отсчета
 // Пройдем по цепочкам векторного найдем наибольшие,наименьшие коорд
 int Border();

 // Запросить/установить отсчет знака                
 int GetCenter(LONGPOINT * delta);
 int SetCenter(LONGPOINT * delta);
                                                       
 // Коррекция цвета векторного объекта - если цвета - индексы (экранный вид) -
 // Добавим флаг |IMGC_INDEX
 // Использовать только для преобразования классификаторов старых версий
 // number - количество цветов в палитре
 // возврат - коррекция успешна - 1

 int CorrectScrColor(int number);

 // Перевод экранных цветов в принтерные
 // number - число цветов
 // color - указатель на палитру RSC
 // цвет - индекс должен иметь флаг

 int SCR2PRN(int number,COLORREF * color);

 // Запрос вида палитры
 // 0 - возможна любая - цвета не было
 // 1 - палитра RSC (цвет - индекс |IMGC_INDEX )
 // 2 - палитра свободная цвет  RGB

 int KindPalette();

 // Выгрузить данные из указанной записи c преобразованием
 // к свободной палитре
 // number - число цветов
 // color - указатель на палитру RSC
 // Если запись длинее выделенной области,
 // то выгрузка не производится
 // При ошибке возвращает ноль,
 // иначе - длину выгруженной записи

 int Unload2PRN(char * address,int length,int number,COLORREF * color);

// ------------------------------------------------------------------
// Переписать цвет - COLORREF на индекс
// ------------------------------------------------------------------
unsigned long GetIndexColor(COLORREF color, COLORREF * palette,
                                         int colornumber);

// -------------------------------------------------
// Перевод свободных цветов в индексы
// number - число цветов
// color - указатель на палитру RSC
// цвет - индекс должен иметь флаг
// ---------------------------------------------------------
int PRN2SCR(int number,COLORREF * color);

// ------------------------------------------------ 
// Контроль размеров цепочек,удаление удаленных,проверка
// правильных длин у цепочек окружностей
// ---------------------------------------------------------
int CorrectVector();

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
 *     Перемещение указателя по фрагментам объекта        *
 *                                                        *
 *********************************************************/

 public :

 // Установить указатель на первую точку заданного фрагмента
 // number - последовательный номер фрагмента,
 // начиная с 1
 // Выполняется контроль по длине записи и длине буфера
 // При ошибке возвращает ноль

 char * FirstPoint(int number = 1);

 // Установить указатель на заданную точку
 // текущего фрагмента
 // Номер первой точки 1
 // При ошибке возвращает ноль

 char * GoPoint(int number)
  {
    if ((number == NumberOfPoint) && (Point != 0)) return Point;

    if (((Point == 0) || (NumberOfPoint < 1)) &&
		      	(FirstPoint(SubjectNumber()) == 0))
    		{
		      return 0;
      }

  	 if ((number < 1) || (number > PointCount())) return 0;

  	 Point -= (NumberOfPoint-number)*sizeof(IMGVECTPOINT);

  	 NumberOfPoint = number;

  	 return (Point);
  }

 // Установить указатель на заданную точку
 // указанного фрагмента
 // Номер первой точки 1
 // При ошибке возвращает ноль

 char * GoPointSubject(int number,int subject)
  {
    if ((number == NumberOfPoint) && (Point != 0) &&
        (subject == SubjectNumber())) return Point;

    if (((Point == 0) || (NumberOfPoint < 1) ||
         (subject != SubjectNumber())) &&
		      	(FirstPoint(subject) == 0))
    		{
		      return 0;
         }

  	 if ((number < 1) || (number > PointCount())) return 0;

  	 Point -= (NumberOfPoint-number)*sizeof(IMGVECTPOINT);

  	 NumberOfPoint = number;

  	 return (Point);
  }

 // Установить указатель на последнюю точку заданного фрагмента
 // number - последовательный номер фрагмента,
 // начиная с 1
 // Выполняется контроль по длине записи и длине буфера
 // При ошибке возвращает ноль

 char * LastPoint(int number = 1);

 // Установить указатель на следующую точку метрики
 // объекта или подобъекта
 // При ошибке возвращает ноль

 char * NextPoint()
  {
  	 if (Point == 0) return 0;
    if (NumberOfPoint >= PointCount()) return 0;
  	 NumberOfPoint++;
  	 return (char *)(Point += sizeof(IMGVECTPOINT));
  }

 // Установить указатель на предыдущую точку метрики
 // текущего фрагмента
 // При ошибке возвращает ноль

 char * PrevPoint()
  {
  	 if (Point == 0) return 0;
  	 if (NumberOfPoint <= 1) return 0;
  	 NumberOfPoint--;
  	 return (char *)(Point -= sizeof(IMGVECTPOINT));
  }

 // Найти точку фрагмента,
 // ближайшую к заданной
 // number - последовательный номер фрагмента,
 // начиная с 1
 // Возвращает номер точки или ноль при ошибке
 // Номер первой точки 1

 int SeekNearPoint(int number,long x,long y,int numberpoint = 1);

 // Найти точку по всем фрагментам
 // ближайшую к заданной
 // Возвращает номер точки или ноль при ошибке
 // Номер первой точки 1
 // Для определения номера фрагмента ,
 // в котором найдена точка,
 // нужно вызвать функцию SubjectNumber()

 int SeekNearPoint(long x,long y);

 protected :

  // Установить указатель на дескриптор фрагмента
  // При ошибке возвращает ноль

  char * DescPointSubject(int number = 0);


 /*********************************************************
 *                                                        *
 *         Запрос данных из текущего фрагмента            *
 *       (в соответствии с текущим положением указателя)  *
 *                                                        *
 *********************************************************/

 public :

 // Запросить адрес текущей точки текущего фрагмента

 char * CurrentPoint() { return (char *)Point; }

 // Запросить/Установить параметры отображения текущего фрагмента
 // При ошибке возвращает ноль

 char * Parm()
	 {
  		if (DescPoint == 0) return 0;
  		return (char *)&(((IMGPOLYDESC *)DescPoint)->Parm);
	 }

 char * Parm(char * parm,int length);

 // Запросить номер текущей точки
 // Номер первой точки 1, если не установлено - возвращает 0

 int PointNumber() { return NumberOfPoint; }

 // Запросить число точек во фрагменте
 // Значение берется из указателя на текущий фрагмент
 // При ошибке возвращает ноль

 int PointCount()
	 {
  		if (DescPoint == 0) return 0;
  		return (int)*(long *)((char *)&(((IMGPOLYDESC *)DescPoint)->Count)+
       ((IMGPOLYDESC *)DescPoint)->Length - 4);
	 }

 // Запросить длину параметров отображения текущего фрагмента
 // (не меньше 4 байт)
 // При ошибке возвращает ноль

 int ParmLength();

 // Запросить номер текущего фрагмента
 // Номер первого фрагмента 1,
 // если не установлено возвращает 0

 int SubjectNumber() { return NumberOfSubject; }

 // Запросить/Установить тип графического примитива текущего фрагмента
 // (VT_SQUARE,VT_LINE, ... - см. mapgdi.h)
 // При ошибке возвращает ноль (VT_SQUARE)

 int Type()
	 {
  		if (DescPoint == 0) return 0;
  		return ((IMGPOLYDESC *)DescPoint)->Type;
	 }

 int Type(int type)
	 {
  		if (DescPoint == 0) return 0;
  		return (((IMGPOLYDESC *)DescPoint)->Type =
                                    (unsigned short )type);
	 }

 // Запросить/Установить тип линии текущего фрагмента
 // (IMG_LINE,IMG_DOT ... - см. mapgdi.h)
 // При ошибке возвращает ноль (неотображаемая линия)

 int Image()
	 {
  		if (DescPoint == 0) return 0;
  		return ((IMGPOLYDESC *)DescPoint)->Image;
	 }

 int Image(int image)
	 {
  		if (DescPoint == 0) return 0;
  		return (((IMGPOLYDESC *)DescPoint)->Image =
                                 (unsigned short )image);
	 }

 // Запросить координаты текущей точки фрагмента
 // При ошибке в структуре данных возвращается число 0

 long int X()
  {
    if (Point)
       return ((IMGVECTPOINT *)Point)->Hor;
    return 0;
  }

 long int Y()
  {
    if (Point)
      return ((IMGVECTPOINT *)Point)->Ver;
    return 0;
  }

 // Запросить координаты заданной точки фрагмента
 // При ошибке в структуре данных возвращается число 0

 long int XN(int number)
  {
    GoPoint(number);
    return X();
  }

 long int YN(int number)
  {
    GoPoint(number);
    return Y();
  }

 /*********************************************************
 *                                                        *
 *         Функции редактирования структуры записи        *
 *                                                        *
 *********************************************************/

 public :

 // Создать заголовок нового фрагмента
 // Выполняется контроль по длине записи и длине буфера
 // Число точек = 0
 // При ошибке возвращает ноль

 int CreateSubject();

 // Удалить заданный фрагмент
 // Текущей становится первая точка первого фрагмента
 // При ошибке возвращает ноль

 ptrdiff_t DeleteSubject(int number);


 /*********************************************************
 *                                                        *
 *         Функции блока цепочек                          *
 *                                                        *
 *********************************************************/

 public :                                                     

 // Запросить количество блоков

 int GetBlockCount();

 // Установить указатель на первую точку заданного блока
 // number - последовательный номер блока,
 // начиная с 1
 // Выполняется контроль по длине записи и длине буфера
 // При ошибке возвращает ноль

 char * BlockFirstPoint(int number = 1);

 // Запрос номера первой цепочки блока (с VT_OBJECT)
 // number - последовательный номер блока,
 // начиная с 1
 // При ошибке возвращает ноль

 int BlockFirstSubject(int number);

 // Запрос номера блока (с 1) к которому принадлежит фрагмент
 // number - последовательный номер фрагмента,
 // начиная с 1                                    

 int GetBlockNumber(int number);

 // Запрос количества цепочек блока (с VT_OBJECT по VT_END включительно)
 // number - последовательный номер блока, начиная с 1
 // При ошибке возвращает ноль

 int GetBlockSize(int number);

 /*********************************************************
 *                                                        *
 *      Функции редактирования точек метрики              *
 *                                                        *
 *********************************************************/


 public :

 // Добавить координаты точки во фрагмент
 // Добавляемая точка становится последней
 // и текущей точкой
 // number - номер фрагмента
 // При добавлении точек контролируется длина буфера
 // При ошибке возвращает ноль

 int AppendPoint(int number,long int x,long int y);

 // Удалить текущую точку фрагмента
 // Если точек не было - ничего не удаляется
 // Текущей становится точка следующая за удаленной
 // При ошибке возвращает ноль

 int DeletePoint();

 // Удаление из метрики одинаковых точек
 // При ошибке возвращает ноль

 int DeleteEqualPoint();

 // Вставить точку в фрагмент
 // за текущей точкой
 // Если точек не было - добавляется первая точка
 // Добавляемая точка становится текущей точкой
 // При добавлении точек контролируется длина буфера
 // При ошибке возвращает ноль

 int InsertPoint(long int x,long int y);

 //  Сместить все координаты метрики объекта на заданную
 //  величину (delta), с учетом типа цепочек
 //  center - 1 при изменении отсчета, 0 - при сдвиге
 //  При ошибке возвращает ноль                                 

 int RelocateObject(LONGPOINT * delta,int center);

 // Сместить все координаты заданного фрагмента
 // на заданную величину (delta)
 // При ошибке возвращает ноль

 int RelocateSubject(int number,LONGPOINT * delta);

 // Установить координаты текущей точки фрагмента

 void UpdatePoint(long int x,long int y)
	   {
      X(x); Y(y);
    }

 long int X(long int x)
  {
    if (Point)
      return (((IMGVECTPOINT *)Point)->Hor = x);
    return 0;
  }

 long int Y(long int y)
  {
    if (Point)
      return (((IMGVECTPOINT *)Point)->Ver = y);
    return 0;
  }

protected :

  // Добавить точку без инициализации
  // При ошибке возвращает ноль

  int AppendFreePoint(int number);

  // Вставить точку в текущую позицию
  // без инициализации
  // При ошибке возвращает ноль

  int InsertFreePoint();

public :

  // Загрузить запись

  TVectorImageEdit * operator = (TVectorImageEdit * image)
	    {
       if (Load(image)) return image;
       return 0;
     }

  IMGVECTOREX * operator = (IMGVECTOREX * data)
	    {
       if (Load(data)) return data;
       return 0;
     }

protected :

  // Установить адрес начала записи

  char * operator = (char * address)
	    {
       return (char *)(Vector = (IMGVECTOREX *)address);
     }


protected :

 IMGVECTOREX * Vector;   // Адрес записи
 long int BufferLength;  // Размер буфера данных
 char * Point;           // Указатель текущей точки
 int NumberOfPoint;      // Номер текущей точки фрагмента
                         // начинается с 1
 int NumberOfSubject;    // Текущий номер фрагмента
 char * DescPoint;       // Указатель на заголовок фрагмента
 char * Memory;          // Способ обработки памяти в деструкторе
                								 // (если != 0, освободить)
 int Isdirty;            // Признак редактирования записи

};

#endif   //__cplusplus
#endif

