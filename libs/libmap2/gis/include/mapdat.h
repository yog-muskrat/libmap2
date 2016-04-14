
#ifndef MAPDAT_H
#define MAPDAT_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifndef MAPDATA_H
  #include "mapdata.h"
#endif

#ifndef MEASURE_H
  #include "measure.h"
#endif

#include "maptrace.h"

class _DLLCLASS TTranslate;
class _DLLCLASS TMap;

#define DATABUFFERSIZE (4*1024L)  // МИНИМАЛЬНЫЙ РАЗМЕР БУФЕРА МЕТРИКИ 
#define DATABUFFERAPP  (64*1024L) // ПРИРАЩЕНИЕ БУФЕРА МЕТРИКИ

#define DATALENGTHLIMIT  MAXDATALENGTH  // Maximum of record size 

#ifndef TINYDATA

typedef LONGMETRIC OBJECTDATA;
#define CheckDataIdent(ident) ((ident & 0xFFF0FFF0) == 0x7FF07FF0)

#else

typedef SHORTMETRIC OBJECTDATA;
#define CheckDataIdent(ident) ((ident & 0x0FFF0) == 0x7FF0)

#endif

// Запросить координаты первой точки объекта
// в виде целого числа
long _fastcall dataX1Long(OBJECTDATA * data);
long _fastcall dataY1Long(OBJECTDATA * data);

// Запросить координаты первой точки объекта
// в виде числа с плавающей точкой
double _fastcall dataX1Double(OBJECTDATA * data);
double _fastcall dataY1Double(OBJECTDATA * data);
double _fastcall dataH1Double(OBJECTDATA * data);

// Запросить предельное число точек (по длине записи)
int _fastcall dataPointLimit(OBJECTDATA * data);

// Запросить размер точки метрики
int _fastcall dataPointSize(OBJECTDATA * data);

// Преобразовать точку метрики типа Kind() к типу DOUBLEPOINT
// с контролем принадлежности pointIn буферу записи метрики
// При ошибке возвращает 0
int _fastcall dataXYDouble(OBJECTDATA * data, char * pointIn,
                           DOUBLEPOINT * pointOut);

// Запрос  размерности метрики (0 - 2D, 1 - 3D)
int _fastcall dataDimension(OBJECTDATA * data);

// Вычисление периметра ( длины ) объекта
double _fastcall dataPerimeter(OBJECTDATA * data);

#ifdef __cplusplus

class _DLLCLASS TDataEdit;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  МЕТРИКА ОБ'ЕКТА ЭЛЕКТРОННОЙ КАРТЫ  +++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TObjectData
{                         // ***********
                          // ** DATA ***
 public :                 // ***********

  // Установить адрес начала метрики объекта
  TObjectData(char * addr)
  {
    Base = (OBJECTDATA *)addr;
  }

  TObjectData(const int addr)
  {
    Base = (OBJECTDATA *)addr;
  }

  TObjectData(OBJECTDATA * addr)
  {
    Base = addr;
  }

  // Установить адрес начала метрики объекта
  TObjectData()
  {
    Base = 0L;
  }

  // Виды форматов метрики
  enum KIND { IDSHORT2  = 0x7FFF7FFFL, // двухбайтовая целочисленная
              IDLONG2   = 0x7FFE7FFEL, // четырехбайтовая целочисленная
              IDFLOAT2  = 0x7FFD7FFDL, // с плавающей запятой
              IDDOUBLE2 = 0x7FFC7FFCL, // с плавающей запятой двойной точностью
              IDSHORT3  = 0x7FFB7FFBL, // двухбайтовая целочисленная  трехмерная
              IDLONG3   = 0x7FFA7FFAL, // четырехбайтовая целочисленная трехмерная
              IDFLOAT3  = 0x7FF97FF9L, // с плавающей запятой  трехмерная
              IDDOUBLE3 = 0x7FF87FF8L, // с плавающей запятой двойной точностью трехмерная
              IDBAD     = 0x7FF87FF7L  // неизвестный вид
            };

  // Типы метрики объектов (для совместимости с SXF)
  enum DATTYPE { INTEGER = 0, FLOAT = 2 };

  // Размер элемента метрики (FLOAT+LONG => DOUBLE) (для совместимости с SXF)
  enum DATSIZE { SHORT = 0, LONG = 1 };

  // Направление цифрования метрики
  enum DIRECT { UNDEFINED = OD_UNDEFINED, // не определено
                PLUS      = OD_RIGHT,     // по часовой стрелке
                MINUS     = OD_LEFT,      // против часовой стрелки
              };

  // Запросить адрес начала записи
  char * Address()
  { return (char *)Base; }

  // Запросить адрес повторяющейся части метрики
  char * BeginData()
  { return (char *)(&(Base->Desc)); }

  // Запросить размер дескриптора метрики
  int DescSize()
  { return sizeof(SHORTDESC); }

  // Есть реальные данные ?
  int IsCorrect()
  { if ((Base != 0) && (Kind() > IDBAD)) return(1);
    return(0); }

  // Есть реальные данные заданного типа ?
  int IsCorrect(KIND kind)
  { if ((Base != 0) && (Kind() == kind)) return(1);
    return(0); }

#ifndef TINYDATA
  // Запросить формат метрики (большой объект или нормальный?)
  int IsLarge()                              
  {
    if (Base != 0) return (Base->Control & METRIC_LONGCOUNT);
    return(0);
  }

  // Запросить тип высоты в третьей координате
  // (0 - абсолютная, иначе - относительная)
  int IsRelativeHeight()                     
  {
    if (Base != 0) return (Base->Control & METRIC_RELATIVEH);
    return(0);
  }
#endif

  // Запросить/Установить вид (идентификатор) метрики
  long Kind()
  { if (Base == 0) return 0;
    return Base->Ident; }

  long Kind(KIND kind)
  { if (Base == 0) return 0;
    return (Base->Ident = kind); }

  // Запрос размерности метрики
  // При 2-yx мерной метрике возврат 0,
  // При 3-yx мерной - 1
  int DatDimension();

  // Запросить размер точки метрики
  int PointSize();

  // Установить/Запросить длину записи метрики
  long Length()
  { if (Base == 0) return 0;
    return(Base->Length); }

  long Length(long length)
  { if (Base == 0) return 0;
    return(Base->Length = length); }

  // Загрузить метрику из указанной записи
  // размер выходного буфера не контролируется !
  int Load(TObjectData data);

  // Установить/Запросить число точек в объекте
  int PointCount();
  int PointCount(int count);

  // Запросить предельное число точек (по длине записи)
  int PointLimit();

  // Запросить сколько точек еще можно добавить (по длине записи)
  int PointReserve();

  // Установить/Запросить число составных частей (подобъектов + 1)
  int PolyCount()
  { if (Base == 0) return 0;
    return(Base->Part + 1); }

  int PolyCount(int polycount)
  { if (Base == 0) return 0;
    return ((Base->Part = (unsigned short)(polycount - 1)) + 1); }

  // Вычисление периметра объекта
  double Perimeter();

  // Запросить координаты первой точки объекта
  // в условной системе (дискреты)
  // Номер первой точки 1
  // При ошибке в структуре данных возвращает число 0
  long  X1Long();     // Запросить координаты
  long  Y1Long();     // первой точки объекта

  double X1Double();  // Запросить координаты
  double Y1Double();  // первой точки объекта
  double H1Double();

  // Запросить координаты второй точки объекта
  // в условной системе (дискреты)
  // При ошибке в структуре данных возвращает число 0
  long  X2Long();     // Запросить координаты
  long  Y2Long();     // второй точки объекта

  // Преобразовать точку метрики типа Kind() к типу DOUBLEPOINT
  // с контролем принадлежности pointIn буферу записи метрики
  // При ошибке возвращает 0
  int XYDouble(char * pointIn, DOUBLEPOINT * pointOut);

  // Запросить способ выравнивания текста по горизонтали
  // у объекта
  // (FA_LEFT,FA_RIGHT,FA_CENTER - см. mapgdi.h)
  int GetTextHorizontalAlign();                      

  // Установить адрес начала метрики объекта
  OBJECTDATA * operator = (OBJECTDATA * Addr)
  {
    return (Base = Addr);
  }

  // Установить адрес начала метрики объекта
  char * operator = (char * Addr)
  {
    return (char *)(Base = (OBJECTDATA  *)Addr);
  }

  char * operator = (TDataEdit * edit);

  char * operator = (TDataEdit& edit);

  // Проверить указатель на данные
  int operator == (int Value)
  {
    return (Base == (OBJECTDATA *)Value);
  }

  int operator != (int Value)
  {
    return (Base != (OBJECTDATA *)Value);
  }

 /*********************************************************
 *                                                        *
 *        Функции выполнения расчетов по метрике          *
 *                                                        *
 *********************************************************/

 public :

  OBJECTDATA * Base;                 // УКАЗАТЕЛЬ НА ДАННЫЕ
};
#endif


// Map data type for desktop system is IDFLOAT2,3  only !
// Site data type for desktop system is IDDOUBLE2,3 only !
// Map data type for mobile system is IDSHORT2 (TINYDATA) only !

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++  РЕДАКТИРОВАНИЕ МЕТРИКИ ОБ'ЕКТА ЭЛЕКТРОННОЙ КАРТЫ  +++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//  Создать метрику объекта в формате "float" 2-ух мерную
//  TDataEdit metric;
//  if (metric.Create(IDFLOAT2))     // Выделить память и разметить
//    {
//      metric.InsertPoint(200.342,300.12);  // Добавить точку
//      metric.InsertPoint(250.71,350.176);
//      ...
//    }

class _DLLCLASS TDataEdit : public TObjectData
{

 /*********************************************************
 *                                                        *
 *       Функции инициализации данных класса              *
 *                                                        *
 *********************************************************/

 public :

#ifndef BUILD_DLL
  // Установить адрес начала метрики объекта
  // text - признак метрики с текстом (объекты типа "подпись")
  TDataEdit(char * address, long int length = 0, int text = 0) :
            TObjectData(), Measure()
  {
    Memory = 0;  // Память не запрашивалась
    SetBuffer(address,length,text);
  }
#endif

  TDataEdit() : TObjectData(), Measure()
  {
    Memory = 0;  // Память не запрашивалась
    SetBuffer(0,0L,0);
  }

#ifndef BUILD_DLL
  TDataEdit(TObjectData data,int text = 0) :
            TObjectData(), Measure()
  {
    Memory = 0;  // Память не запрашивалась
    SetObject(data,text);
  }
#endif

  TDataEdit(TDataEdit * data) : TObjectData(), Measure()
  {
    Memory = 0;  // Память не запрашивалась
    Load(data);
  }

 ~TDataEdit()
  {
    SetBuffer(0,0L,0);
  }

  // Направление цифрования метрики
  enum DIRECT { UNDEFINED = OD_UNDEFINED, // не определено
                PLUS      = OD_RIGHT,     // по часовой стрелке
                MINUS     = OD_LEFT,      // против часовой стрелки
              };

  // Виды форматов метрики
  enum KIND { IDSHORT2  = 0x7FFF7FFFL, // двухбайтовая целочисленная
              IDLONG2   = 0x7FFE7FFEL, // четырехбайтовая целочисленная
              IDFLOAT2  = 0x7FFD7FFDL, // с плавающей запятой
              IDDOUBLE2 = 0x7FFC7FFCL, // с плавающей запятой двойной точностью
              IDSHORT3  = 0x7FFB7FFBL, // двухбайтовая целочисленная  трехмерная
              IDLONG3   = 0x7FFA7FFAL, // четырехбайтовая целочисленная трехмерная
              IDFLOAT3  = 0x7FF97FF9L, // с плавающей запятой  трехмерная
              IDDOUBLE3 = 0x7FF87FF8L, // с плавающей запятой двойной точностью трехмерная
              IDBAD     = 0x7FF87FF7L  // неизвестный вид
            };
#ifndef TINYDATA
  // Установить тип высоты в третьей координате
  // (0 - абсолютная, иначе - относительная)
  int SetHeightType(int type)                     
  {
    if (Base != 0)
      {
       Isdirty = 1;                               

       if (type != 0)
         { Base->Control |= METRIC_RELATIVEH; return 1;}
       else
         { Base->Control &= ~METRIC_RELATIVEH; return 0;}
      }
    return(0);
  }
#endif

  // Для совместимости
  int  PolyKey(int key) { return key; };
  int  PolyKey() { return 0; };

  // Выделить память под запись метрики
  // Проинициализировать структуру данных
  // Создается идентификатор записи,число точек = 0
  // По умолчанию метрика 2-ух мерная
  // text - признак метрики с текстом (объекты типа "подпись")
  // Память автоматически освобождается в деструкторе
  // или при назначении другой области с помощью
  // SetBuffer(...), в том числе, SetBuffer(0,0).
  // При ошибке возвращает 0
  int _fastcall Allocate(int kind = IDFLOAT2,
                         int text = 0,
                         int size = DATABUFFERSIZE);

  // Освободить память под запись метрики       
  void Free() { SetBuffer(0, 0L, 0); }

  // Проинициализировать структуру данных
  // Создается идентификатор записи,число точек = 0
  // По умолчанию метрика 2-ух мерная
  // text - признак метрики с текстом (объекты типа "подпись")
  // При ошибке возвращает 0
  int _fastcall Clear(int kind = IDFLOAT2,int text = 0);
  int _fastcall Create(int kind = IDFLOAT2,int text = 0);

  // Загрузить метрику из указанной записи
  //  text - признак метрики с текстом (объекты типа "подпись")
  // Запись длинее 512 Кб не загружается
  // Указатель текущей точки на 1-ой точке объекта
  // Возвращает длину загруженной записи
  // При ошибке возвращает 0
  int _fastcall Load(OBJECTDATA * data, int text);
  int Load(TObjectData data, int text)
  {
    return Load(data.Base, text);
  }
  int Load(TDataEdit * data)
  {
    if (data == 0) return 0;
    return Load(data->Base, data->IsTextMetric());
  }
  int Load(TDataEdit& data)
  {
    return Load(data.Base, data.IsTextMetric());
  }

  // Установить описание буфера метрики
  //  address - адрес начала
  //  length  - длина буфера
  //  text    - признак метрики с текстом (объекты типа "подпись")
  // Память выделенная Allocate() освобождается.
  // Указатель текущей точки на 1-ой точке объекта,
  // если буфер содержит корректные данные
  void _fastcall SetBuffer(char * address,long int length,
                           int text = FALSE);

  void SetObject(TObjectData data,int text = FALSE)
  {
//    Tracer(">>>> CALL SetObject()\n");

    if (data == 0) SetBuffer(0,0L,0);
    else SetBuffer(data.Address(),data.Length(),text);
  }

  // Запросить/Установить признак редактирования данных
  int IsDirty()          { return Isdirty; }
  int IsDirty(int dirty) { return (Isdirty = dirty && 1); }

  //  Добавить подобъект из указанной записи
  //  data - откуда добавить
  //  number - номер подобъекта в data
  //  При ошибке возвращает 0
  int AppendSubject(TDataEdit *data, int number);

  //  Сделать объект из подобъекта
  //  data - откуда взять подобъект
  //  number - номер подобъекта в data
  //  При ошибке возвращает 0
  int LoadSubject(TDataEdit *data, int number);

protected :

  // Увеличить размер буфера метрики
  // Возвращает новый размер буфера
  // При ошибке возвращает 0
  int Realloc();


 /*********************************************************
 *                                                        *
 * Перемещение указателя по метрике объекта и подобъектов *
 *                                                        *
 *********************************************************/

 public :

  // Установить указатель на первую точку метрики объекта
  // Выполняется контроль по длине записи и длине буфера
  // При ошибке возвращает 0
  char * FirstPoint() { return FirstPointSubject(0); }

  // Установить указатель на первую точку метрики подобъекта
  // number - последовательный номер подобъекта
  // ( 0 - объект, 1 - первый подобъект и т.д.)
  // Выполняется контроль по длине записи и длине буфера
  // При ошибке возвращает 0
  char * _fastcall FirstPointSubject(int number = 0);

  // Установить указатель на заданную точку метрики
  // текущего объекта или подобъекта
  // Номер первой точки 1
  // При ошибке возвращает 0
  char * GoPoint(int number)
  {
    if ((number == NumberOfPoint) && (Point != 0)) return Point;

    if (((Point == 0) || (NumberOfPoint < 1)) &&
        (FirstPointSubject(SubjectNumber()) == 0)) return 0;

    if ((number < 1) || (number > PointCount())) return 0;

    Point = Point - (NumberOfPoint - number)*SizeOfPoint;

    NumberOfPoint = number;

    return Point;
  }

  // Установить указатель на заданную точку метрики
  // указанного объекта или подобъекта
  // Номер первой точки 1
  // При ошибке возвращает 0
  char * GoPointSubject(int number,int subject)
  {
    if ((number == NumberOfPoint) && (Point != 0) &&
        (subject == SubjectNumber())) return Point;

    if (((Point == 0) || (NumberOfPoint < 1) ||
         (subject != SubjectNumber())) &&
        (FirstPointSubject(subject) == 0)) return 0;

    if ((number < 1) || (number > PointCount())) return 0;

    Point = Point - (NumberOfPoint - number)*SizeOfPoint;

    NumberOfPoint = number;

    return Point;
  }

  // Установить указатель на последнюю точку метрики объекта
  // Выполняется контроль по длине записи и длине буфера
  // При ошибке возвращает 0
  char * LastPoint();

  // Установить указатель на последнюю точку метрики подобъекта
  // number - последовательный номер подобъекта
  // ( 0 - объект, 1 - первый подобъект и т.д.)
  // Выполняется контроль по длине записи и длине буфера
  // При ошибке возвращает 0
  char * LastPointSubject(int number = 0);

  // Установить указатель на следующую точку метрики
  // объекта или подобъекта
  // При ошибке возвращает 0
  char * NextPoint();

  // Установить указатель на предыдущую точку метрики
  // объекта или подобъекта
  // При ошибке возвращает 0
  char * PrevPoint()
  {
    if (Point == 0) return 0;
    if (NumberOfPoint <= 1) return 0;
    NumberOfPoint--;
    return (char *)(Point -= SizeOfPoint);
  }

 protected :

  // Установить указатель на дескриптор подобъекта/объекта
  // Контроль длины записи или буфера не выполняется
  // При ошибке возвращает 0
  char * _fastcall DescPointSubject(int number = 0);


 /*********************************************************
 *                                                        *
 *       Запрос данных из метрики объекта/подобъекта      *
 *     (в соответствии с текущим положением указателя)    *
 *                                                        *
 *********************************************************/

 public :

  // Запросить адрес текущей точки объекта/подобъекта
  char * CurrentPoint() { return Point; }

  // Запросить номер текущей точки
  // Номер первой точки 1, если не установлено - возвращает 0
  int PointNumber() { return NumberOfPoint; }

  // Запросить число точек в метрике подобъекта/объекта
  // Значение берется из указателя на текущий подобъект/объект
  // При ошибке возвращает 0
  int PointCount();

  // Запросить число точек в метрике подобъекта/объекта
  // subject - последовательный номер подобъекта
  // При ошибке возвращает 0
  int SubjectPointCount(int subject)            
   {
     if (FirstPointSubject(subject) == 0)
       return 0;
     return PointCount();  
   }

  int SetObjectPointCount(int count)
   { return TObjectData::PointCount(count); }

  // Запросить номер текущего подобъекта
  // Номер первого подобъекта 1, если не установлено или
  // указатель на метрике объекта - возвращает 0
  int SubjectNumber() { return NumberOfSubject; }

  // Запросить координаты текущей точки подобъекта/объекта
  // в виде целого числа или с плавающей запятой
  // При ошибке возвращает 0
  long X();
  long Y();

  double XDouble();
  double YDouble();
  double HDouble();

  // Запросить координаты заданной точки подобъекта/объекта
  // При ошибке возвращает 0
  double _fastcall XNDouble(int number);
  double _fastcall YNDouble(int number);
  double _fastcall HNDouble(int number);

  // Преобразовать точку метрики типа Kind() к типу DOUBLEPOINT
  // с контролем принадлежности pointIn буферу записи метрики
  // При ошибке возвращает 0
  int XYDouble(char * pointIn, DOUBLEPOINT * pointOut);

  // Запросить координаты первой точки объекта
  // в условной системе (дискреты)
  // При ошибке в структуре данных возвращает число 0
  long  X1Long();     // Запросить координаты
  long  Y1Long();     // первой точки объекта

  double X1Double();  // Запросить координаты
  double Y1Double();  // первой точки объекта

 /*********************************************************
 *                                                        *
 *          Функции запроса информации о метрике          *
 *                                                        *
 *********************************************************/

 public :

  // Определение габаритов объекта
  //  dframe - вычисленные габариты объекта/подобъекта
  // При ошибке возвращает 0
  int Dimensions(DFRAME * dframe);

  // Определение габаритов объекта/подобъекта
  //  dframe - габариты
  //  subject - номер подобъекта
  // При ошибке возвращает 0
  int DimensionsSubject(DFRAME * dframe, int subject = 0);

  // Определение направления цифрования объекта/подобъекта
  // Возвращает: OD_RIGTH,OD_LEFT,OD_UNDEFINED (см.maptype.h)
  int GetDirection(int subject = 0);

  // Запросить замкнутость объекта/подобъекта
  // возврат - 1 - замкнут
  //           0 - незамкнут или ошибка
  int GetExclusiveSubject(int number = 0);

  // Вычисление длины объекта
  double PolyPerimeter();

  // Вычисление длины подобъекта/объекта
  // subject - номер подобъекта (если = 0, обрабатывается объект)
  double PolySubjectPerimeter(int subject);   

  // Вычисление площади объекта/подобъекта
  // При ошибке возвращает 0
  double SquareSubject(int subject = 0);

  // Вычисление площади объекта
  double Square();

  // Общее число точек в объекте с подобъектами
  int TotalPointCount();

 protected :

  // Вычисление знаковой площади объекта/подобъекта
  // При ошибке возвращает 0
  double SignedSquareSubject(int subject = 0);


 /*********************************************************
 *                                                        *
 *            Функции определения особых точек            *
 *                                                        *
 *********************************************************/

 public :

  // Пересечение отрезка и метрики объекта/подобъекта
  //  xy1, xy2  - координаты отрезка
  //  first     - номер первой точки участка
  //  last      - номер последней точки участка
  //  subject   - номер объекта/подобъекта
  //             (0 - объект, 1 - первый подобъект и т.д.)
  //  precision - точность
  // Возвращает две структуры NUMBERPOINT, включающие номер
  // точки метрики, после которой находится точка пересечения
  // и структуру DOUBLEPOINT - координаты точки пересечения
  // Две структуры заполняются если отрезок xy1,xy2 лежит
  // на отрезке метрики
  // При отсутствии точек пересечения или ошибке возвращает 0

  int CrossCutData(DOUBLEPOINT * xy1, DOUBLEPOINT * xy2,
                   int first, int last,
                   NUMBERPOINT * point1, NUMBERPOINT * point2,
                   int subject = 0, double precision = DELTANULL);

  // Определение входимости точки с координатами x,y
  // в объект/подобъект
  //  point   - координаты точки
  //  subject - номер объекта/подобъекта
  // Возвращает: 1 - точка внутри объекта/подобъекта,
  //             2 - точка внешняя,
  //             3 - точка совпадает с точкой метрики,
  //             4 - точка лежит на отрезке метрики,
  //             0 - ошибка метрики

  int Inside(DOUBLEPOINT * point, int subject = 0);

  // Найти точку метрики объекта и подобъектов,
  // ближайшую к заданной. Для определения номера
  // подобъекта/объекта, в котором найдена точка,
  // нужно вызвать функцию SubjectNumber()
  // Возвращает номер точки (номер первой точки 1)
  // При ошибке возвращает 0

  int SeekNearPoint(double x,double y);

  // Найти точку метрики подобъекта, ближайшую к заданной
  //  number - последовательный номер подобъекта
  //           (0 - объект, 1 - первый подобъект и т.д.)
  // Возвращает номер точки (номер первой точки - 1)
  // При ошибке возвращает 0

  int SeekNearPoint(double x,double y,int number);

  // Найти точку на участке метрики подобъекта,
  // ближайшую к заданной
  //  number - последовательный номер подобъекта
  //           (0 - объект, 1 - первый подобъект и т.д.)
  //  first  - номер первой точки участка
  //  last   - номер последней точки участка
  // Возвращает номер точки (номер первой точки - 1)
  // При ошибке возвращает 0

  int SeekNearPoint(double x,double y,int number,int first,int last);

  // Найти точку на контурах объекта и подобъектов,
  // ближайшую к заданной
  // Для определения номера подобъекта/объекта
  // нужно вызвать функцию SubjectNumber()
  // Возвращает номер точки метрики, за которой расположена
  // точка на контуре (номер первой точки - 1)
  // Координаты точки помещаются по адресу point
  // При ошибке возвращает 0

  int SeekNearVirtualPoint(double x,double y,XYDOUBLE * point);

  // Найти точку на контуре подобъекта, ближайшую к заданной
  //  number - последовательный номер подобъекта
  //           (0 - объект, 1 - первый подобъект и т.д.)
  // Возвращает номер точки метрики за которой расположена
  // точка на контуре (номер первой точки - 1)
  // Координаты точки помещаются по адресу point
  // При ошибке возвращает 0

  int SeekNearVirtualPoint(double x,double y,int number,XYDOUBLE * point);

  // Найти точку на участке контура подобъекта, ближайшую к заданной
  //  number - последовательный номер подобъекта
  //           (0 - объект, 1 - первый подобъект и т.д.)
  //  first  - номер первой точки участка
  //  last   - номер последней точки участка
  // Возвращает номер точки метрики за которой расположена
  // точка на контуре (номер первой точки - 1)
  // Координаты точки помещаются по адресу point
  // При ошибке возвращает 0

  int SeekNearVirtualPoint(double x,double y,int number,int first,int last,
                           XYDOUBLE * point);

  // Определение координат точки, лежащей на заданном
  // расстоянии (по периметру) от заданной точки
  // number - номер начальной точки
  // distance - расстояние
  // если distance > = 0 - поиск по направлению цифрования
  //               <   0 - поиск против направления цифрования
  // point - координаты выходной точки
  // subject - номер подобъекта
  // Возвращает номер точки, за которой находится или
  // c которой совпадает
  // Если точки совпадают - возвращает отрицательный номер точки
  // При ошибке возвращает 0

  int SeekVirtualPointByDistance(int number, double distance,
                                 DOUBLEPOINT *point,
                                 int subject = 0);

  // Найти точку на отрезке, ближайшую к заданной
  // segment - массив из 2-х элементов (отрезок из двух точек)
  // При ошибке возвращает 0
  // Координаты точки помещаются по адресу target

  int SeekVirtualPointOnSegment(double x,double y,
                                DOUBLEPOINT *segment,
                                DOUBLEPOINT *target);

 /*********************************************************
 *                                                        *
 *            Функции редактирования метрики              *
 *                                                        *
 *********************************************************/

 public :

  // Изменить формат записи метрики (IDFLOAT2,...,IDDOUBLE3)
  // При ошибке возвращает 0, иначе - тип нового формата записи !
  // Для подписи он может быть изменен (в тип IDSHORT2, IDFLOAT2)
  int ChangeKind(int kind);

  // Изменить формат записи метрики обычного объекта
  // в объект типа подпись (text != 0) или наоборот (text = 0)
  // При ошибке возвращает 0, иначе - тип нового формата записи !
  int ChangeTextFormat(int text = 0);

  // Создать дескриптор подобъекта в записи метрики
  // В конец записи добавляется дескриптор подобъекта
  // Выполняется контроль по длине записи и длине буфера
  // Число точек = 0, номер подобъекта = максимальный номер + 1
  // (как правило, записывается порядковый номер подобъекта)
  // При ошибке возвращает 0
  int CreateSubject();

  // Вставить дескриптор объекта/подобъекта в записи метрики  
  // В указанную позицию записи добавляется дескриптор подобъекта
  // Число точек = 0, номер подобъекта = subject
  // При удачном завершении возвращает 1, иначе 0 (FALSE)
  int InsertSubject(int subject);

  // Удалить подобъект в записи метрики
  // Текущей становится первая точка объекта
  // При ошибке возвращает 0
  int DeleteSubject(int number);

 /*********************************************************
 *                                                        *
 *          Функции редактирования точек метрики          *
 *                                                        *
 *********************************************************/

 public :

  // Добавить координаты точки в метрику объекта
  // Добавляемая точка становится последней в метрике объекта
  // Добавляемая точка становится текущей точкой
  // Координаты преобразуются в формат записи метрики
  // При добавлении точек контролируется длина буфера
  // При ошибке возвращает 0
  int AppendPoint(double x,double y)
  {
    return AppendPointSubject(0, x, y);
  }

  int AppendPoint(double x,double y,double h)
  {
    return AppendPointSubject(0, x, y, h);
  }

  int AppendPoint(DOUBLEPOINT * point)
  {
    return AppendPoint(point->X,point->Y);
  }

  // Добавить точку в метрику объекта/подобъекта
  // Добавляемая точка становится последней в метрике подобъекта
  // number - номер подобъекта, если равен нулю - обрабатывается
  // метрика объекта.
  // Добавляемая точка становится текущей точкой
  // При добавлении точек контролируется длина буфера
  // При ошибке возвращает 0
  int AppendPointSubject(int number,double x,double y);
  int AppendPointSubject(int number,double x,double y,double h)
  {
    if (AppendPointSubject(number,x,y) == 0) return 0;
    H(h);
    return 1;
  }

  int AppendPointSubject(int number,DOUBLEPOINT * point)
  {
    return AppendPointSubject(number,point->X,point->Y);
  }

  // Изменить направление метрики всего объекта
  // Возвращает новое значение направления цифрования
  // При ошибке возвращает 0
  int ChangeDirection();

  // Изменить направление метрики подобъекта
  // При ошибке возвращает 0
  int ChangeDirection(int subject);

  // Удалить текущую точку метрики объекта/подобъекта
  // Если точек не было - ничего не удаляется
  // Текущей становится точка следующая за удаленной
  // При ошибке возвращает 0
  int DeletePoint();

  // Удаление из метрики одинаковых точек
  // precision - точность
  // height    - признак учета трехмерной метрики 
  // При ошибке возвращает 0
  int DeleteEqualPoint(double precision = DELTANULL, int height = 0);

  // Вставить точку в метрику объекта/подобъекта
  // за текущей точкой
  // Если точек не было - добавляется первая точка
  // Добавляемая точка становится текущей точкой
  // При добавлении точек контролируется длина буфера
  // При ошибке возвращает 0
  int InsertPoint(double x,double y);
  int InsertPoint(double x,double y,double h)
  {
    if (InsertPoint(x,y) == 0) return 0;
    H(h);
    return 1;
  }

  int InsertPoint(DOUBLEPOINT * point)
  {
    return InsertPoint(point->X,point->Y);
  }


  // Линейная фильтрация метрики
  //  precision - точность
  // Удаляет: 1. двойные точки метрики;
  //          2. незамкнутые подобъекты < 2 точек;
  //          3. замкнутые подобъекты < 4 точек;
  //          4. точки метрики, лежащие в середине отрезка прямой
  //             на расстоянии precision от прямой.
  // Объект не удаляет никогда !!!
  // Возвращает общее число точек метрики
  // При ошибках возвращает:
  //    0 - ошибка структуры
  //   -1 - объект состоит из одной точки
  //   -2 - объект состоит из двух одинаковых точек
  //   -3 - число точек замкнутого контура объекта равно 3
  //  -10 - число точек метрики превышает длину записи метрики
  int LinearFilter(double precision = DELTANULL);
  int Filter(double precision = DELTANULL)
     { return LinearFilter(precision); }             

  // Сместить все координаты метрики объекта на заданную
  // величину (delta)
  // При ошибке возвращает 0
  int RelocateObject(DOUBLEPOINT * delta);

  // Сместить все координаты метрики объекта/подъобъекта на заданную
  // величину (delta)
  // number - номер объекта/подобъекта
  // При ошибке возвращает 0
  int RelocateSubject(int number, DOUBLEPOINT * delta);

  // Повернуть объект вокруг центра ( center )
  // на заданный угол ( anglevalue ).
  // Угол задается в радианах и может принимать значения:
  // от 0 до PI и от 0 до -PI или
  // от 0 до PI и от 0 до 2PI
  // При ошибке возвращает 0
  int RotateObject(DOUBLEPOINT *center, double anglevalue);

  // Повернуть объект/подобъект вокруг центра ( center )
  // на заданный угол ( anglevalue ).
  // Угол задается в радианах и может принимать значения:
  // от 0 до PI и от 0 до -PI или
  // от 0 до PI и от 0 до 2PI
  // number - номер подобъекта
  // При ошибке возвращает 0
  int RotateSubject(DOUBLEPOINT *center, double anglevalue,
                    int number = 0);

  // Масштабировать(factor) метрику объекта
  // factor - коэффициент
  // deltanull - смещение относительно 0
  // При ошибке возвращает ноль
  int ScopeObject(DOUBLEPOINT *factor, DOUBLEPOINT *deltanull);

  // Масштабировать(factor) метрику объекта/подобъекта
  // factor - коэффициент
  // deltanull - смещение относительно 0
  // number - номер подобъекта
  // При ошибке возвращает ноль
  int ScopeSubject(DOUBLEPOINT *factor, DOUBLEPOINT *deltanull,
                   int number = 0);

  // Масштабировать (factor) и cместить все координаты метрики
  // объекта на заданную величину (delta)
  // factor - коэффициент
  // deltanull - смещение относительно 0
  // delta - непосредственно смещение
  // При ошибке возвращает ноль
  int ScopeAndRelocateObject(DOUBLEPOINT *factor,
                             DOUBLEPOINT *deltanull,
                             DOUBLEPOINT *delta);

  // Масштабировать (factor) и cместить все координаты метрики
  // объекта/подобъекта на заданную величину (delta)
  // factor - коэффициент
  // deltanull - смещение относительно 0
  // delta - непосредственно смещение
  // number - номер подобъекта
  // При ошибке возвращает ноль
  int ScopeAndRelocateSublect(DOUBLEPOINT *factor,
                              DOUBLEPOINT *deltanull,
                              DOUBLEPOINT *delta,
                              int number = 0);

  // Удалить петли
  int DeleteLoop(double precision = DELTANULL);


  // Соединение поворотом по дуге по часовой стрелке
  // т.1 и т.3 (центр т.2 , радиус в дискретах - radius)
  int BuildCircular(DOUBLEPOINT * point1,
                    DOUBLEPOINT * point2,
                    DOUBLEPOINT * point3,
                    double radius);

  // РЕЖИМЫ ЗАМЫКАНИЯ ОБ'ЕКТА
  enum { ABR_APPEND   = 0,  // Добавить точку в конце объекта
                            // не добавляет, если объект замкнут
         ABR_LAST     = 1,  // Обновить последнюю точку
         ABR_FIRST    = 2,  // Обновить первую точку
         ABR_ADDLAST  = 3,  // Добавить точку в конце объекта
         ABR_ADDFIRST = 4   // Добавить первую точку
       };

  // Замкнуть объект/подобъект
  //  mode = 0 - добавить последнюю точку
  //             (не добавляет, если объект замкнут)
  //       = 1 - заменить последнюю точку
  //       = 2 - заменить первую точку
  //       = 3 - добавить последнюю точку
  //       = 4 - добавить первую точку
  // При ошибке возвращает 0
  int SetExclusiveSubject(int number = 0, int mode = 0);
  int Abridge(int number = 0, int mode = 0)
  {
    return SetExclusiveSubject(number,mode);
  }

  // Замкнуть объект и все подобъекты
  // При ошибке возвращает 0
  int AbridgeObject(int mode = 1);

  // Установить координаты текущей точки подобъекта/объекта
  // в виде целого числа или с плавающей запятой
  // Координаты записываются в соответствии с форматом
  // записи (см. Kind()).
  void UpdatePoint(DOUBLEPOINT * point)
  {
    UpdatePoint(point->X,point->Y);
  }

  void UpdatePoint(double x,double y)
  {
    X(x); Y(y);
  }

  void UpdatePoint(double x,double y,double h)
  {
    X(x); H(h); Y(y);
  }

  double X(double x) { return XDouble(x); }
  double Y(double y) { return YDouble(y); }
  double H(double h) { return HDouble(h); }

  double XDouble(double x);
  double YDouble(double y);
  double HDouble(double h);


  // Контроль структуры метрики объекта         
  // При ошибке возвращает ноль, если метрика исправлялась -
  // возвращает отрицательное значение

  int StructControl();


 /*********************************************************
 *                                                        *
 *       Запрос данных о тексте подписи из метрики        *
 *                  объекта/подобъекта                    *
 *                                                        *
 *********************************************************/

 public :

  // Это метрика подписи ?
  int IsTextMetric() { return (IsTextData != 0); }

  // Текст имеет кодировку UNICODE ?
  int IsUnicodeText()
  {
#ifndef TINYDATA
    if (Base != 0)
      return (Base->Control & METRIC_UNICODETEXT);
#endif
    return 0;
  }

  // Запросить длину текстовой строки (число символов)
  // (Общая длина описания текста на два байта больше)
  // При ошибке или для пустой строки возвращает 0
  int TextLength();

  // Запросить содержание текстовой строки
  // text   - адрес для размещения строки
  // length - длина выделенной области под строку
  // При удачном завершении возвращается значение text,
  // переданная строка имеет кодировку ANSI
  // При ошибке возвращает 0
  char * GetText(char * text,int length);

  // Запросить содержание текстовой строки
  // во внутреннем формате !
  // При ошибке возвращает 0
  char * GetObjectText();

  // Установить новое содержание текстовой строки
  // text   - адрес новой строки
  // При удачном завершении возвращается значение text,
  // переданная строка должна иметь кодировку ANSI
  // При ошибке возвращает 0
  char * PutText(char * text) { return PutText(text,-1); }

  // Запросить способ выравнивания текста по горизонтали
  // у текущего подобъекта
  // (FA_LEFT,FA_RIGHT,FA_CENTER - см. mapgdi.h)
  int GetTextHorizontalAlign();

  // Запросить способ выравнивания текста по вертикали
  // у текущего подобъекта
  // (FA_BOTTOM,FA_TOP,FA_BASELINE,FA_MIDDLE)
  int GetTextVerticalAlign();

  // Установить способ выравнивания текста по горизонтали
  // subject - номер подобъекта (-1 - установить всем)
  // (FA_LEFT,FA_RIGHT,FA_CENTER)
  int PutTextHorizontalAlign(int align, int subject);

  // Установить способ выравнивания текста по вертикали
  // subject - номер подобъекта (-1 - установить всем)
  // (FA_BOTTOM,FA_TOP,FA_BASELINE,FA_MIDDLE)
  int PutTextVerticalAlign(int align, int subject);

  // Установить новое содержание текстовой строки
  // у текущего подобъекта
  // text   - адрес новой строки
  // align  - комбинация флажков выравнивания (FA_BOTTOM|FA_CENTER,...)
  // При удачном завершении возвращается значение text,
  // переданная строка должна иметь кодировку ANSI
  // При ошибке возвращает 0
  char * _fastcall PutText(const char * text, int align, int isunicode = 0);

  // Запросить адрес начала текста подобъекта
  // Строка имеет кодировку ANSI
  // При ошибке возвращает 0
  TEXTDATA * GetTextData();

  // Установить новое содержание текстовой строки
  // text   - адрес новой строки (начинается с поля длины),
  // строка должна быть в кодировке ANSI для любой платформы
  // При ошибке возвращает 0
  char * _fastcall PutTextData(TEXTDATA * text, int isunicode = 0);

 /*********************************************************
 *                                                        *
 *               Расчеты по объекту                       *
 *                                                        *
 *********************************************************/

 public :

  // Вычисление расстояния между двумя точками
  double Distance(DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);

  // Вычисление расстояния между точкой и прямой,
  // заданной двумя точками
  double Distance(DOUBLEPOINT *point, DOUBLEPOINT *xy1,
                                      DOUBLEPOINT *xy2);

  // Вычисление периметра объекта
  double Perimeter();

  // Определение двух точек по перпендикуляру от отрезка (point1-point2)
  // на расстоянии distance от точки point (по умолчанию point1)
  int SeekPointNormalLine(DOUBLEPOINT *point1, DOUBLEPOINT *point2,
                          DOUBLEPOINT *pointout1, DOUBLEPOINT *pointout2,
                          double distance, DOUBLEPOINT *point = 0);

  // Вычисление дирекционного угла от точки XY1 к XY2 в радианах
  double DirectionAngle(DOUBLEPOINT *XY1, DOUBLEPOINT *XY2);

 public :

  // Проверить указатель на данные
  int operator == (int Value)
  {
    return (Base == (OBJECTDATA *)Value);
  }

  int operator != (int Value)
  {
    return (Base != (OBJECTDATA *)Value);
  }

 protected :

  // Установить адрес начала метрики объекта
  OBJECTDATA * operator = (OBJECTDATA * Addr)
  {
    SetBuffer((char *)Addr, Addr->Length);
    return (Addr);
  }

  // Установить адрес начала метрики объекта
  char * operator = (char * Addr)
  {
    return (char *)(Base = (OBJECTDATA  *)Addr);
  }

 public:

  long int BufferLength;  // Размер буфера метрики
  char HUGER * Point;     // Указатель текущей точки
  int SizeOfPoint;        // Размер в байтах описания точки
  int NumberOfPoint;      // Номер текущей точки объекта или подобъекта
                          // начинается с 1
  int NumberOfSubject;    // Текущий номер объекта (= 0)
                          // или подобъекта (> 0)
  char HUGER * DescPoint; // Указатель на дескриптор метрики текущего
                          // подобъекта или объекта
  char * Memory;          // Способ обработки памяти в деструкторе
                          // (если != 0, освободить)
  int IsTextData;         // Признак метрики с текстом
  int Isdirty;            // Признак редактирования метрики
  int IsSemRefer;         // Признак ссылки на семантику в тексте подписи 

  TMeasure     Measure;   // Расчеты параметров об'екта
};

typedef TDataEdit DATAEDIT;

// Выделить память под максимальную запись метрики
// Проинициализировать структуру данных
// Создается идентификатор записи,число точек = 0
// При ошибке возвращает ноль
int _fastcall deAllocate(DATAEDIT * data, int kind, int text, int size);

// Увеличить размер буфера метрики
// При ошибке возвращает ноль, иначе - новый размер буфера
int _fastcall deRealloc(DATAEDIT * data);

// Проинициализировать структуру данных
// Создается идентификатор записи,число точек = 0
// При ошибке возвращает ноль
int _fastcall deClear(DATAEDIT * data, int kind, int text);

// Проинициализировать структуру данных
// Создается идентификатор записи,число точек = 0
// При ошибке возвращает ноль
int _fastcall deCreate(DATAEDIT * data, int kind, int text);

// Установить описание буфера метрики
// address - адрес начала, length - длина буфера
// Указатель текущей точки на 1-ой точке объекта
void _fastcall deSetBuffer(DATAEDIT * data, char * address,
                           long int length, int text);

// Создать дескриптор подобъекта в записи метрики
// В конец записи добавляется дескриптор подобъекта
// Число точек = 0, номер подобъекта = максимальный номер + 1
// (как правило, записывается порядковый номер подобъекта)
// При удачном завершении возвращает 1, иначе 0 (FALSE)
int _fastcall deCreateSubject(DATAEDIT * data);

// Вставить дескриптор объекта/подобъекта в записи метрики  
// В указанную позицию записи добавляется дескриптор подобъекта
// Число точек = 0, номер подобъекта = subject
// При удачном завершении возвращает 1, иначе 0 (FALSE)
int _fastcall deInsertSubject(DATAEDIT * data, int subject);

// Загрузить метрику из указанной записи
// Запись длинее 512 Кб не загружается
int _fastcall deLoad(DATAEDIT * dataed, OBJECTDATA * data, int text);

// Удалить подобъект в записи метрики
// При ошибке возвращает ноль
int _fastcall deDeleteSubject(DATAEDIT * data, int number);

// Добавить подобъект из указанной записи
// src    - откуда добавить
// number - номер подобъекта в src
// При ошибке возвращает 0
int _fastcall deAppendSubject(TDataEdit * data, TDataEdit * src, int number);

// Сделать объект из подобъекта
// data - откуда взять подобъект
// number - номер подобъекта в data
// При ошибке возвращает 0
int _fastcall deLoadSubject(TDataEdit * data, TDataEdit * src, int number);

// Установить указатель на дескриптор подобъекта/объекта
// Контроль длины записи или буфера не выполняется
// При ошибке возвращает ноль
char * _fastcall deDescPointSubject(DATAEDIT * data, int number);

// Запросить число точек в подобъекте
// number - номер подобъекта в data
// При ошибке возвращает ноль
int _fastcall dePointCount(DATAEDIT * data, int number);

// Установить указатель на первую точку метрики подобъекта
// number - последовательный номер подобъекта
// ( 0 - объект, 1 - первый подобъект и т.д.)
// При ошибке возвращает ноль
char * _fastcall deFirstPointSubject(DATAEDIT * data, int number);

// Установить указатель на последнюю точку метрики подобъекта
// number - последовательный номер подобъекта
// ( 0 - объект, 1 - первый подобъект и т.д.)
// Контроль числа точек не выполняется !
// При ошибке возвращает ноль
char * _fastcall deLastPointSubject(DATAEDIT * data, int number);

// Установить указатель на заданную точку метрики
// указанного объекта или подобъекта
// Номер первой точки 1
// При ошибке возвращает 0
char * _fastcall deGoPointSubject(DATAEDIT * data, int number, int subject);

// Установить указатель на следующую точку метрики
// объекта или подобъекта
// При ошибке возвращает 0
char * _fastcall deNextPoint(DATAEDIT * data);

// Установить указатель на предыдущую точку метрики
// объекта или подобъекта
// При ошибке возвращает 0
char * _fastcall dePrevPoint(DATAEDIT * data);

// Добавить точку в метрику объекта/подобъекта
// При ошибке возвращает ноль
int _fastcall deAppendPointSubject(DATAEDIT * data, int number,
                                   double * x, double * y);

// Запросить координаты текущей точки подобъекта/объекта
// в виде числа с плавающей точкой
double _fastcall deXDouble(DATAEDIT * data);
double _fastcall deYDouble(DATAEDIT * data);
double _fastcall deHDouble(DATAEDIT * data);

// Установить координаты текущей точки подобъекта/объекта
// в виде числа с плавающей точкой
double _fastcall deSetXDouble(DATAEDIT * data, double * x);
double _fastcall deSetYDouble(DATAEDIT * data, double * y);
double _fastcall deSetHDouble(DATAEDIT * data, double * h);

// Запросить координаты текущей точки подобъекта/объекта
// в виде целого числа
long _fastcall deXLong(DATAEDIT * data);
long _fastcall deYLong(DATAEDIT * data);

// Вставить точку в метрику объекта/подобъекта
// за текущей точкой
// Добавляемая точка становится текущей точкой
// При ошибке возвращает ноль
int _fastcall deInsertPoint(DATAEDIT * data, double * x,double * y);

// Удалить текущую точку метрики объекта/подобъекта
// Если точек не было - ничего не удаляется
// Текущей становится точка следующая за удаленной
// При ошибке возвращает ноль
int _fastcall deDeletePoint(DATAEDIT * data);

// Запросить адрес начала текста подобъекта
// При ошибке возвращает 0
TEXTDATA * _fastcall deGetTextData(DATAEDIT * data);

// Запросить способ выравнивания текста по горизонтали
// (FA_LEFT,FA_RIGHT,FA_CENTER - см. mapgdi.h)
int _fastcall deGetTextHorizontalAlign(DATAEDIT * data);

// Запросить способ выравнивания текста по вертикали
// (FA_BOTTOM,FA_TOP,FA_BASELINE,FA_MIDDLE)
int _fastcall deGetTextVerticalAlign(DATAEDIT * data);

// Установить способ выравнивания текста по горизонтали
// (FA_LEFT,FA_RIGHT,FA_CENTER)
int _fastcall dePutTextHorizontalAlign(DATAEDIT * data, int align,
                                       int subject);

// Установить способ выравнивания текста по вертикали
// (FA_BOTTOM,FA_TOP,FA_BASELINE,FA_MIDDLE)
int _fastcall dePutTextVerticalAlign(DATAEDIT * data, int align,
                                     int subject);

// Запросить содержание текстовой строки
// text   - адрес для размещения строки
// length - длина выделенной области под строку
// При удачном завершении возвращается значение text,
// переданная строка имеет кодировку ANSI
// При ошибке возвращает ноль
char * _fastcall deGetText(DATAEDIT * data, char * text, int length);

// Установить новое содержание текстовой строки    
// text   - адрес новой строки (начинается с поля длины)
// При ошибке возвращает 0
char * _fastcall dePutTextData(DATAEDIT * data, TEXTDATA * textdata, int isunicode);

// Установить новое содержание текстовой строки
// text   - адрес новой строки
// При удачном завершении возвращается значение text,
// переданная строка должна иметь кодировку ANSI
// При ошибке возвращает ноль
char * _fastcall dePutText(DATAEDIT * data, const char * text, 
                           int code, int isunicode);

// Изменить формат записи метрики (IDSHORT2,...)
// При ошибке возвращает 0, иначе - тип нового формата записи !
int _fastcall deChangeKind(DATAEDIT * data, int format);

// Изменить формат записи метрики обычного объекта
// в объект типа подпись (text != 0) или наоборот (text = 0)
// При ошибке возвращает 0, иначе - тип нового формата записи !
int _fastcall deChangeTextFormat(DATAEDIT * data, int text);

// Замкнуть объект и все подобъекты
// При ошибке возвращает 0
int _fastcall deAbridgeObject(DATAEDIT * data, int mode);

// Замкнуть  объект/подобъект
// mode - = 0 - добавить последнюю точку
//              не добавляет, если объект замкнут
//        = 1 - заменить последнюю точку
//        = 2 - заменить первую точку
//        = 3 - добавить последнюю точку
//        = 4 - добавить первую точку
// возврат - 1 - замкнут
// При ошибке возвращает 0
int _fastcall deSetExclusiveSubject(DATAEDIT * data, int number, int mode);

// Удаление из метрики одинаковых точек
// precision - точность (0.0...n)
// height    - признак учета трехмерной метрики 
// При ошибке возвращает ноль
int _fastcall deDeleteEqualPoint(DATAEDIT * data, double * precision,
                                 int height);

// Запросить замкнутость объекта/подобъекта
// Возвращает:  1 - замкнут, 0 - незамкнут
int _fastcall deGetExclusiveSubject(DATAEDIT * data, int number);

// Определение габаритов объекта
// dframe - вычисленные габариты объекта/подобъекта
// При ошибке возвращает 0
int _fastcall deDimensions(DATAEDIT * data, DFRAME * dframe);

// Вычисление длины объекта
double _fastcall dePolyPerimeter(DATAEDIT * data);

// Вычисление длины подобъекта/объекта
// subject - номер подобъекта (если = 0, обрабатывается объект)
double _fastcall dePolySubjectPerimeter(DATAEDIT* data, int subject); 

// Вычисление площади объекта
double _fastcall deSquare(DATAEDIT * data);

// Общее число точек в объекте с подобъектами
int _fastcall deTotalPointCount(DATAEDIT * data);

// Линейная фильтрация метрики
// precision - точность
// Возвращает общее число точек метрики
// При ошибках возвращает <= 0
int _fastcall deLinearFilter(DATAEDIT * data, double * precision);

// Сместить все координаты метрики объекта на заданную
// величину (delta)
// При ошибке возвращает ноль
int _fastcall deRelocateObject(DATAEDIT * data, DOUBLEPOINT * delta);

// Сместить все координаты метрики объекта/подъобъекта на заданную
// величину (delta)
// number - номер объекта/подобъекта
// При ошибке возвращает ноль
int _fastcall deRelocateSubject(DATAEDIT * data, int number,
                                DOUBLEPOINT * delta);

// Повернуть объект вокруг центра ( center )
// на заданный угол ( anglevalue ).
// Угол задается в радианах и может принимать значения:
// от 0 до PI и от 0 до -PI или  от 0 до PI и от 0 до 2PI
// При ошибке возвращает 0
int _fastcall deRotateObject(DATAEDIT * data,
                             DOUBLEPOINT * center, double anglevalue);

// Повернуть объект/подобъект вокруг центра ( center )
// на заданный угол ( anglevalue ).
int _fastcall deRotateSubject(DATAEDIT * data, DOUBLEPOINT *center,
                              double anglevalue, int number);

// Масштабировать(factor) метрику объекта
// factor - коэффициент
// deltanull - смещение относительно 0
// При ошибке возвращает ноль
int _fastcall deScopeObject(DATAEDIT * data, DOUBLEPOINT *factor,
                            DOUBLEPOINT *deltanull);

int _fastcall deScopeSubject(DATAEDIT * data, DOUBLEPOINT *factor,
                             DOUBLEPOINT *deltanull, int number);

// Масштабировать (factor) и cместить все координаты метрики
// объекта на заданную величину (delta)
// factor - коэффициент
// deltanull - смещение относительно 0
// delta - непосредственно смещение
// При ошибке возвращает ноль
int _fastcall deScopeAndRelocateObject(DATAEDIT * data,
                                       DOUBLEPOINT *factor,
                                       DOUBLEPOINT *deltanull,
                                       DOUBLEPOINT *delta);

int _fastcall deScopeAndRelocateSublect(DATAEDIT * data,
                                        DOUBLEPOINT *factor,
                                        DOUBLEPOINT *deltanull,
                                        DOUBLEPOINT *delta,
                                        int number);

// Пересечение отрезка и метрики объекта / подобъекта
// При отсутствии точек пересечения или ошибке возвращает ноль
int _fastcall deCrossCutData(DATAEDIT * data,
                             DOUBLEPOINT * xy1, DOUBLEPOINT * xy2,
                             int first, int last,
                             NUMBERPOINT * point1,
                             NUMBERPOINT * point2, int subject,
                             double precision);

// Пересечение отрезка и метрики объекта / подобъекта 
// xy1, xy2 - координаты отрезка
// data - метрика объекта/подобъекта
// subject - номер объекта/подобъекта
// ( 0 - объект, 1 - первый подобъект и т.д.)
// first - номер первой точки участка
// last  - номер последней точки участка
// pointo - указатель на массив структур NUMBERPOINT из 2 элементов
//          для заполнения информации об исходном отрезке (1-я и 2-я точка)
// pointm - указатель на массив структур NUMBERPOINT из 2 элементов
//          для заполнения информации об отрезке метрики (1-я и 2-я точка)
//
// Возвращает 0 - нет точек пересечения
//            1 - одна точка пересечения лежит в pointo[0]
//           -1 - 1 или 2 точки пересечения лежат в pointo и/или pointm
// точки пересечения лежат на одной линии исходного отрезка и отрезка метрики
// Во всех заполненных структурах NUMBERPOINT :
//  -  номер точки(Number) есть номер точки метрики,
//     за которой находится точка пересечения(Point)
//  -  Update != 0 - исходный отрезок и отрезок метрики лежат на одной прямой
//            = 1 - точка пересечения является виртуальной
//            < 0 - точка пересечения совпадает с точкой
//                  исходного отрезка, если это pointm ( -1 или -2)
//                  или точкой отрезка метрики, если это pointo ( -1 или -2)
//            = 0 - чистая точка пересечения
int _fastcall deCrossCutDataEx(DATAEDIT * data,
                              DOUBLEPOINT * xy1, DOUBLEPOINT * xy2,
                              int first, int last,
                              NUMBERPOINT *pointo,
                              NUMBERPOINT *pointm, int subject,
                              double precision);

// Определение направления цифрования объекта/подобъекта
// Возвращает: OD_PLUS      - по часовой стрелке
//             OD_MINUS     - против часовой стрелки
//             OD_UNDEFINED - не определено
// При ошибке возвращает ноль
int _fastcall deGetDirection(DATAEDIT * data, int subject);

// Определение входимости точки с координатами x,y
// в объект/подобъект
// При ошибке возвращает ноль
int _fastcall deInside(DATAEDIT * data, DOUBLEPOINT * point, int subject);

// Определение габаритов объекта / подобъекта
// При ошибке возвращает 0
int _fastcall deDimensionsSubject(DATAEDIT * data, DFRAME * dframe,
                                  int subject);

// Вычисление знаковой площади объекта/подобъекта
double _fastcall deSignedSquareSubject(DATAEDIT * data, int subject);

// Определение координат точки, лежащей на заданном
// расстоянии (по периметру) от заданной точки
// При ошибке возвращает 0
int _fastcall deSeekVirtualPointByDistance(DATAEDIT * data,
                                           int number,
                                           double distance,
                                           DOUBLEPOINT *point,
                                           int subject);

// Найти точку метрики объекта и подобъектов,
// ближайшую к заданной
// Для определения номера подобъекта/объекта
// нужно вызвать функцию SubjectNumber()
// При ошибке возвращает 0
int _fastcall deSeekNearPoint(DATAEDIT * data, double * x, double * y);

// Найти точку метрики подобъекта,
// ближайшую к заданной
// number - последовательный номер подобъекта
int _fastcall deSeekNearPointSubject(DATAEDIT * data, double * x,
                                     double * y, int number);

// Найти точку на участке метрики подобъекта,
// ближайшую к заданной
// При ошибке возвращает 0
int _fastcall deSeekNearPointSubjectPart(DATAEDIT * data, double * x,
                                         double * y, int number,
                                         int first, int last);

// Найти точку на контурах объекта и подобъектов,
// ближайшую к заданной
// Для определения номера подобъекта/объекта
// нужно вызвать функцию SubjectNumber()
// При ошибке возвращает 0
int _fastcall deSeekNearVirtualPoint(DATAEDIT * data,
                                     double * x, double * y,
                                     XYDOUBLE * point);

// Найти точку на контуре подобъекта,
// ближайшую к заданной
// При ошибке возвращает 0
int _fastcall deSeekNearVirtualPointSubject(DATAEDIT * data,
                                            double * x, double * y,
                                            int number, XYDOUBLE * point);

// Найти точку на участке контура подобъекта
// в заданном диапазоне точек, ближайшую к заданной
int _fastcall deSeekNearVirtualPointSubjectPart(DATAEDIT * data,
                                 double * x,double * y, int number,
                                 int first, int last, XYDOUBLE * point);


// Найти точку на отрезке, ближайшую к заданной
// segment - массив из 2-х элементов (отрезок из двух точек)
// При ошибке возвращает 0
// Координаты точки помещаются по адресу target
int _fastcall deSeekVirtualPointOnSegment(double * x,double * y,
                                          DOUBLEPOINT * point,
                                          DOUBLEPOINT * target);

// Соединение поворотом по дуге по часовой стрелке
// т.1 и т.3 (центр т.2 , радиус - radius)
// При ошибке возвращает 0
int _fastcall deBuildCircular(DATAEDIT * data, DOUBLEPOINT * point1,
                              DOUBLEPOINT * point2,
                              DOUBLEPOINT * point3,
                              double radius);

// Изменить направление метрики всего объекта
// Возвращает новое значение направления цифрования
// При ошибке возвращает 0
int _fastcall deChangeDirection(DATAEDIT * data);

// Изменить направление метрики подобъекта
// При ошибке возвращает 0
int _fastcall deChangeDirectionSubject(DATAEDIT * data, int subject);

// Удалить петли у объекта
// При ошибке возвращает ноль

int _fastcall deDeleteLoop(DATAEDIT * data, double * precision);

// Установить параметры для вычисления по геодезическим
// координатам
// При отсутствии флага возможности расчета геодезических
// координат или ошибке возвращает 0
int _fastcall deSetTranslate(DATAEDIT * data, TMap * map,
                             TTranslate *translate);       

// Запросить габариты объекта в метрах (по метрике)       
// frame - адрес области для размещения результата
// При ошибке возвращает 0, иначе - frame
DFRAME * _fastcall deObjectFramePlane(DATAEDIT * data, DFRAME * dframe,
                                      TMap * map, int list);

// Вычисление площади объекта/подобъекта по его геодезическим
// координатам
// При отсутствии флага возможности расчета геодезических
// координат возвращает 0
// subject - номер подобъекта
//       ( -1 - площадь объекта с вычетом площади подобъектов)
// Результат в метрах на местности
// При ошибке возвращает 0
double _fastcall deSquareReal(DATAEDIT * data, TMap * map, int subject); 


#endif

