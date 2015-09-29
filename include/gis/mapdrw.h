
#if !defined(MAPDRW_H)
#define MAPDRW_H

#ifndef MAPMACRO_H
  #include "mapmacro.h"
#endif

#ifndef MAPGDI_H
  #include "mapgdi.h"
#endif

#define DRAWBUFFERSIZE (4*1024L)  // МИНИМАЛЬНЫЙ РАЗМЕР БУФЕРА !


// ОПИСАНИЕ СПОСОБА ИЗОБРАЖЕНИЯ ОБ'ЕКТА
// ----------------------------------------------
//  Минимальная длина описания :  (см. MAPGDI.H)
//   - для IMG_LINE   : 16 байт,
//   - для IMG_SQUARE : 12 байт ...

#define DRAWIDENT 0x7FFF7FFE


// Запросить адрес первого примитива
// При ошибке возвращает 0
char *  _fastcall drawBeginData(IMGDRAW * draw);

// Запросить размер полезных данных
// При ошибке возвращает 0
int _fastcall drawDataLength(IMGDRAW * draw);

// Запросить полную длину записи
// При ошибке возвращает 0
int _fastcall drawLength(IMGDRAW * draw);

// Запросить длину параметров по номеру функции и ее параметрам
// При ошибке возвращает 0
int _fastcall drawElementParmLength(int image, const char * point);

// Запросить адрес примитива
// по последовательному номеру (начиная с 1)
// При ошибке возвращает 0
char * _fastcall drawElementAddress(IMGDRAW * draw, int number);

// Запросить функцию отображения примитива
// по последовательному номеру (начиная с 1)
// При ошибке возвращает 0
int _fastcall drawElementFunction(IMGDRAW * draw, int number);

// Проверить вхождение функции отображения в список примитивов
// При ошибке возвращает 0
int _fastcall drawCheckElementFunction(int function);



typedef struct DRAWEDIT        // РЕДАКТИРОВАНИЕ ГРАФИЧЕСКОГО ОПИСАНИЯ
{
 IMGDRAW *   Base;             // Графическое описание объекта
 long int    BufferLength;     // Размер буфера графического описания
 char *      Memory;           // Способ обработки памяти в деструкторе
                								       // (если != 0, освободить)
 int         NumberOfElement;  // Текущий номер элемента (начиная с 1)
 int         Isdirty;          // Признак редактирования данных
}
  DRAWEDIT;

// Конструктор класса
void _fastcall dredInit(DRAWEDIT * data);

// Деструктор класса
void _fastcall dredFree(DRAWEDIT * data);

// Выделить память под максимальную запись графики
// Проинициализировать структуру данных
// Память автоматически освобождается в деструкторе
// или при назначении другой области с помощью
// SetBuffer(...), в том числе, SetBuffer(0,0).
// При ошибке возвращает ноль
int _fastcall dredAllocate(DRAWEDIT * data, int size); 

// Проинициализировать структуру данных
// При ошибке возвращает ноль
int _fastcall dredClear(DRAWEDIT * data);

// Установить параметры буфера данных
// address - адрес начала, length - длина буфера.
// Память выделенная Allocate() освобождается.
void _fastcall dredSetBuffer(DRAWEDIT * data, char * address,
                             long int length);

// Загрузить описание из указанной записи
// При ошибке возвращает ноль, иначе - длину загруженной записи
int _fastcall dredLoad(DRAWEDIT * data, IMGDRAW * draw);

// Загрузить описание из указанной записи параметров
// принтерных функций (IMG_LINE ...)
// Запись длинее DRAWBUFFERSIZE не загружается
// По-элементно разбираются только "пользовательские функции"
// При ошибке возвращает ноль, иначе - количество загруженных примитивов
int _fastcall dredLoadParm(DRAWEDIT * data, int image, const char * parm);

// Запросить длину параметров примитива по его номеру (номер с 1)
// При ошибке возвращает 0
int _fastcall dredElementParmLength(DRAWEDIT * data, int number);

// Разобрать функцию на примитивы и добавить их
// Возвращает число добавленных примитивов или ноль
int _fastcall dredFunc2Elements(DRAWEDIT * data, int image,
                                const char * parm);

// Установить признак  сплайн - мeтрики
// 1 - метрика по сплайну, 0 - нет
int _fastcall dredSetSpline(DRAWEDIT * data, int spline);

// Добавить новый элемент описания объекта
// При ошибке возвращает ноль,иначе - число элементов в записи
int _fastcall dredAppendElement(DRAWEDIT * data, int image,
                                const char * parm);

// Удалить элемент описания объекта
// number - номер элемента (начиная с 1)
// При ошибке возвращает ноль
int _fastcall dredDeleteElement(DRAWEDIT * data, int number);

// Запросить тип параметров примитива
// по его номеру (номер с 1) (IMG_LINE, IMG_DOT, ...)
// При ошибке возвращает 0
int _fastcall dredElementIdent(DRAWEDIT * data,int number);

// Запросить адрес параметров примитива
// по его номеру (номер с 1)
// При ошибке возвращает 0
char * _fastcall dredElementParmAddres(DRAWEDIT * data,int number);


#ifdef __cplusplus

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  ГРАФИЧЕСКОЕ ОПИСАНИЕ ОБ'ЕКТА КАРТЫ  ++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TObjectDraw
{                         // ***********
                          // ** DRAW ***
 public :                 // ***********

 // Установить адрес начала метрики объекта
 TObjectDraw(IMGDRAW * addr)
   {
     Base = addr;
   }

 TObjectDraw(char * addr)
   {
     Base = (IMGDRAW *)addr;
   }

 TObjectDraw(const int addr)
   {
     Base = (IMGDRAW *)addr;
   }

 TObjectDraw()
   {
     Base = 0;
   }

 // Запросить адрес начала записи
 // При ошибке возвращает 0
 char * Address() { return (char *)Base; }

 // Запросить адрес первого примитива
 // При ошибке возвращает 0
 char * BeginData()
   {
     if (Base == 0) return 0;
     return (char *) &(Base->Image);
   }

 // Запросить размер полезных данных
 // При ошибке возвращает 0
 int DataLength()
   {
     int length = Length();
     if (length == 0) return 0;
     return (length - sizeof(IMGDRAW) + sizeof(IMGDECOR)+
                      sizeof(Base->Parm));
   }

 // Запросить число примитивов в записи вида
 // При ошибке возвращает 0
 int Count()
   {
     if (Base == 0) return 0;
     return Base->Count;
   }

 // Проверить корректность структуры записи
 // При ошибке возвращает 0
 int IsCorrect()
   {
     if (Base == 0) return 0;
     return (Base->Ident == DRAWIDENT);
   }

 // Запросить полную длину записи
 // При ошибке возвращает 0
 int Length()
   {
     if (Base == 0) return 0;
     return Base->Length;
   }

 // Запросить адрес примитива
 // по последовательному номеру (начиная с 1)
 // При ошибке возвращает 0
 char * ElementAddress(int number = 1);

 // Запросить тип параметров примитива
 // по его адресу   (IMG_LINE, IMG_DOT, ...)
 // При ошибке возвращает 0
 int ElementIdent(char * point)
   {
     if (point == 0) return 0;
     return ((IMGDECOR *)point)->Number;
   }

 // Запросить адрес параметров примитива
 // по его адресу
 // При ошибке возвращает 0
 char * ElementParmAddress(char * point)
   {
     if (point == 0) return 0;
     return (point + sizeof(IMGDECOR));
   }

 // Запросить полную длину примитива по его адресу
 // При ошибке возвращает 0
 int ElementLength(char * point)
   {
     if (point == 0) return 0;
     return  ((IMGDECOR *)point)->Length;
   }

 // Запросить полную длину примитива по номеру функции и параметрам
 // При ошибке возвращает 0
 int ElementLength(int image, char *point)
   {
     if (point == 0) return 0;
     return (ElementParmLength(image,point)) + sizeof(IMGDECOR);
   }

 //  Запросить длину параметров по номеру функции и ее параметрам
 //  При ошибке возвращает 0
 int ElementParmLength(int image, char *point);

 // Установить адрес начала данных
 char * operator = (char * Addr)
   {
     return (char *)(Base = (IMGDRAW  *)Addr);
   }

 // Установить адрес начала данных
 char * operator = (IMGDRAW * Addr)
   {
     return (char *)(Base = Addr);
   }

 // Проверить указатель на данные
 int operator == (int Value)
   {
     return (Base == (IMGDRAW  *)Value);
   }

 int operator != (int Value)
   {
     return (Base != (IMGDRAW  *)Value);
   }

 public :

 IMGDRAW * Base;

};

#else

typedef struct TObjectDraw
{
  IMGDRAW *  Base;  // УКАЗАТЕЛЬ НА ГРАФИКУ (ПЕРЕМЕННАЯ ДЛИНА)
}
  TObjectDraw;

#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++ РЕДАКТИРОВАНИЕ ГРАФИЧЕСКОГО ОПИСАНИЯ ОБ'ЕКТА КАРТЫ ++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifdef __cplusplus

class _DLLCLASS TDrawEdit : public DRAWEDIT
{
 /*********************************************************
 *                                                        *
 *       Функции инициализации данных класса              *
 *                                                        *
 *********************************************************/

 public :

 // Установить адрес начала описания
 TDrawEdit(char * address,long int length = 0)
  	{
     Memory = 0;
     SetBuffer(address,length);
  	}

 TDrawEdit() 
   {
     Memory = 0;
  	  SetBuffer(0,0L);
   }

 TDrawEdit(TObjectDraw draw)
   {
     Memory = 0;
     SetBuffer(draw.Address(),draw.Length());
  	}

 TDrawEdit(int number,char * point)
   {
     Memory = 0;
     Load(number,point);
   }

 ~TDrawEdit() { SetBuffer(0,0L); }


 // Запросить адрес начала записи
 // При ошибке возвращает 0
 char * Address() { return (char *)Base; }

 // Запросить адрес первого примитива
 // При ошибке возвращает 0
 char * BeginData()
   {
     if (Base == 0) return 0;
     return (char *) &(Base->Image);
   }

 // Запросить размер полезных данных
 // При ошибке возвращает 0
 int DataLength()
   {
     if (Base == 0) return 0;
     int length = Base->Length;
     if (length == 0) return 0;
     return (length - sizeof(IMGDRAW) + sizeof(IMGDECOR)+
                      sizeof(Base->Parm));
   }

 // Запросить число примитивов в записи вида
 // При ошибке возвращает 0
 int Count()
   {
     if (Base == 0) return 0;
       return Base->Count;
   }

 // Проверить корректность структуры записи
 // При ошибке возвращает 0
 int IsCorrect()
   {
     if (Base == 0) return 0;
     return (Base->Ident == DRAWIDENT);
   }

 // Запросить полную длину записи
 // При ошибке возвращает 0
 int Length()
   {
     if (Base == 0) return 0;
     return Base->Length;
   }


 // Выделить память под максимальную запись графики
 // Проинициализировать структуру данных
 // Память автоматически освобождается в деструкторе
 // или при назначении другой области с помощью
 // SetBuffer(...), в том числе, SetBuffer(0,0).
 // При ошибке возвращает ноль
 int Allocate();

 // Проинициализировать структуру данных
 // При ошибке возвращает ноль
 int Clear();

 int Create()
 {
   if (Base != 0) return Clear();
   return Allocate();
 }

 // Загрузить описание из указанной записи
 // Запись длинее DRAWBUFFERSIZE не загружается
 // При ошибке возвращает ноль, иначе - длину загруженной записи
 int Load(TObjectDraw draw);
 int Load(TDrawEdit * draw)
 { if (draw) return Load(draw->Base);
   return 0; }

 // Загрузить описание из указанной записи параметров
 // принтерных функций (IMG_LINE ...)
 // Запись длинее DRAWBUFFERSIZE не загружается
 // При ошибке возвращает ноль, иначе - количество загруженных примитивов
 int Load(int image,char * param);

 // Установить параметры буфера данных
 // address - адрес начала, length - длина буфера.
 // Память выделенная Allocate() освобождается.
 void SetBuffer(char * address,long int length);

 // Запросить/Установить признак редактирования данных
 int IsDirty() { return Isdirty; }
 int IsDirty(int dirty) { return (Isdirty = dirty && 1); }

 // Запросить признак  сплайн - мeтрики
 int IsSpline() {return ((Base->Flags)& IMGD_SPLINE);}

 // Установить признак  сплайн - мeтрики
 // 1 - метрика по сплайну, 0 - нет
 int SetSpline(int spline);

 // Заменить "верхний" цвет верхнего элемента        
 int SetTopColor(int color);

 /*********************************************************
 *                                                        *
 *      Редактирование графического описания объекта      *
 *                                                        *
 *********************************************************/

 public :

 // Добавить новый примитив
 // При ошибке возвращает ноль,иначе - число примитивов в записи
 int AppendElement(int image,char * parm);

 // Запросить номер текущего примитива
 int CurrentNumber()
   {
     return NumberOfElement;
   }

 // Удалить примитив
 // number - номер примитива (начиная с 1)
 // При ошибке возвращает ноль
 int DeleteElement(int number);

 // Проверка - функция входит в список примитивов
 // Возвращает 1,если это примитив - иначе 0
 int IsElement(int image);

 // Проверка - функция входит в список отображаемых примитивов
 // Возвращает 1,если это примитив - иначе 0
 int IsPaintElement(int image);

 // Запросить адрес примитива
 // по его последовательному номеру (начиная с 1)
 // При ошибке возвращает 0
 char * ElementAddress(int number = 1);

 // Запросить тип параметров примитива
 // по его номеру (номер с 1) (IMG_LINE, IMG_DOT, ...)
 // При ошибке возвращает 0
 int ElementIdent(int number);

 // Bcтавить новый примитив по номеру
 // При ошибке возвращает ноль,иначе номер примитива в записи
 int InsertElement(int number,int image,char * parm);

 // Заменить примитив
 // При ошибке возвращает ноль,иначе номер примитива в записи
 int ReplaceElement(int number,int image,char * parm);

 // Передвинуть примитив
 // на  новое место (номер с 1)
 // При ошибке возвращает 0
 int ElementMove(int oldnumber,int newnumber);

 // Добавить новый элемент описания объекта  c инициализацией параметров
 // При ошибке возвращает ноль,иначе - число элементов в записи
 int AppendElementWithInit(int image);

 // Bcтавить новый примитив по номеру  c инициализацией параметров
 // При ошибке возвращает ноль,иначе номер примитива в записи
 int InsertElementWithInit(int number,int image);

 // Заменить примитив  по номеру  c инициализацией параметров
 // При ошибке возвращает ноль,иначе номер примитива в записи
 int ReplaceElementWithInit(int number,int image);

 // Инициализация функций
 int Init(int image,char * parm);

 // Инициализация функций c учетом заменяемых параметров
 // number - номер примитива, image - новый примитив, work - его параметры
 // Возвращает 1,если что-то изменено, иначе 0
int ReplaceInit(int number,int image,char * work);              

 // Запросить адрес параметров примитива
 // по его номеру (номер с 1)
 // При ошибке возвращает 0
 char * ElementParmAddress(int number);

 // Запросить длину параметров примитива по его номеру (номер с 1)
 // При ошибке возвращает 0
 int ElementParmLength(int number);

 // Запросить длину примитива по его номеру (номер с 1)
 // При ошибке возвращает 0
 int ElementLength(int number);

 protected:

 // Разобрать принтерную функцию на примитивы и добавить их
 // возврат - число добавленных примитивов
 int Func2Elements(int image,char * parm);

 public:

 // Установить адрес начала данных
 char * operator = (char * address)
	    {
       if (address == 0) SetBuffer(0,0L);
         else SetBuffer(address,((IMGDRAW  *)address)->Length);
       return address;
     }

 // Проверить указатель на данные
 int operator == (int Value)
   {
     return (Base == (IMGDRAW  *)Value);
   }

 int operator != (int Value)
   {
     return (Base != (IMGDRAW  *)Value);
   }

 operator TObjectDraw()
    {
      return Base;
    }

};

//+++++++++++++++++++++++++++
//+++++ ШРИФТЫ ПОДПИСЕЙ +++++
//+++++++++++++++++++++++++++
class _DLLCLASS TFontDraw
{
public:
   // Параметры шрифта высотой 64
   virtual int getHeight() const = 0;
   virtual int getWidth() const = 0;
   virtual int getAscent() const = 0;
   virtual int getDescent() const = 0;
   virtual int getInterval() const = 0;
   
   virtual char* getCharWidth() const = 0;
	        
   // Привязка левого верхнего угла символа в матрице по осям X и Y.
   // Верхний левый угол знака находится в точке (100-64)/2
   virtual int getShiftInMatrix() const = 0;
		 
   // Cмещения по оси Y
   virtual int getShiftFromTop() const = 0;
   virtual int getShiftFromMiddle() const = 0;
   virtual int getShiftFromBase() const = 0;
   virtual int getShiftFromBottom() const = 0;
   
   // Запросить указатель на сжатое изображение символа
   virtual char* getCharRaster(int number) const = 0;
   
   // Запросить ширину символа
   virtual double getCharWidthR(int number, int height) const = 0;
   
   virtual ~TFontDraw(){}
};

extern "C"
{
// Запросить количество шрифтов
_MAPIMP long int _MAPAPI mapGetDrawFontCount();

// Запросить шрифт с номером number
_MAPIMP const TFontDraw* _MAPAPI mapGetFontDraw(long int number);

} // extern "C"
#else

typedef  DRAWEDIT  TDrawEdit;

#endif  // __cplusplus

#endif

