
#ifndef TINBASE_H
#define TINBASE_H

#include "mapversn.h"
#include "mapsyst.h"
#include "mapdat.h"
#include "tin.h"

struct TINTRIANGLE{ // Треугольник
   TINTRIANGLE(DOUBLEPOINT PointA, double HeightA,
                DOUBLEPOINT PointB, double HeightB,
	        DOUBLEPOINT PointC, double HeightC):
	           PointA(PointA), HeightA(HeightA),
	           PointB(PointB), HeightB(HeightB),
                   PointC(PointC), HeightC(HeightC){}
   
   TINTRIANGLE():
      PointA(), HeightA(0),
      PointB(), HeightB(0),
      PointC(), HeightC(0){}		   
		
   // определить лежит ли точка внутри треугольника      
   int IsInsidePoint(const double x, const double y);
   
   // Выбор значения высоты поверхности в заданной точке
   // Координаты точки задаются в метрах в системе координат
   // векторной карты. Возвращает значение высоты в метрах.
   // В случае ошибки при выборе высоты и в случае необеспеченности
   // заданной точки данными возвращает ERRORHEIGHT
   double GetTriangleHeight(double x, double y);
   
   
   DOUBLEPOINT PointA,  PointB,  PointC; // Координаты точек
   double     HeightA, HeightB, HeightC; // Высоты соответствующих точек
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++ КЛАСС МОДЕЛЬ ТИН +++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TTin{
public:
   TTin();
  ~TTin();
  
  // Конструктор для связи с существующим файлом
  TTin(const char* name);
  
  // Загрузить из файла
  // возвращает 0 в случае ошибки
  int Load(const char* name);
  
  // Выбор значения высоты поверхности в заданной точке
  // Координаты точки задаются в метрах в системе координат
  // векторной карты. Возвращает значение высоты в метрах.
  // В случае ошибки при выборе высоты и в случае необеспеченности
  // заданной точки данными возвращает ERRORHEIGHT  
  double GetTinSurfaceHeight(double x, double y);
  
  // Получить число треугольников
  long int GetTriangleCount(){
     return TriangleCount;
  }
  
  // Получить треугольник с номером index
  // в случае ошибки возвращает ноль
  long int GetTriangle(TINTRIANGLE* const triangle, const int index){
     if(index < 0 || index > TriangleCount - 1)
        return 0;
     *triangle = Triangle[index];
     return 1;
  }
  
  // Получить имя файла
  const char* GetFileName(){
     return FileName;
  }
  
  // Получить базовый масштаб
  unsigned long GetBaseScale(){
     return BaseScale;
  }
  
  // Получить габариты в метрах
  const DFRAME& GetFrameMeters(){
     return FrameMeters;
  }
  
  // Получить минимальное значание высоты
  double GetMinHeightValue(){
     return MinHeightValue;
  }
  
  // Получить максимальное значание высоты
  double GetMaxHeightValue(){
     return MaxHeightValue;
  }

private:
   TTin(const TTin& Tin);
   const TTin& operator=(const TTin&);
   long int TriangleCount; // Количество треугольников
   TINTRIANGLE* Triangle; // Указатель на массив треугольников
   char FileName[MAX_PATH];  // Имя файла 
   unsigned long BaseScale;  // Базовый масштаб
   DFRAME FrameMeters;       // Габариты в метрах
   double MinHeightValue,    // Габариты по высоте
          MaxHeightValue;
   void SetBorderHeightValue(); // Установить габариты по высоте
};

#ifndef HIDETIN

#ifndef MAPMACRO_H
  #include "mapmacro.h"
#endif

#ifdef __cplusplus

#include <windows.h>

#include "tin.h"
#include "tinapi.h"
#include "mapdat.h"

class _DLLCLASS TTin
{
 public:

  // Конструктор по умолчанию
  TTin();

  // Конструктор для создания файла по заголовку и палитре
  TTin(char* name, TIN* tin, COLORREF* palette = 0);

  // Конструктор для связи с существующим файлом
  TTin(char* name, int mode);

 ~TTin();

//*****************************************************************
//  Член-функции класса TTin
//*****************************************************************

  // Возврат режима доступа к файлу
  int AccessMode() { return ACCESSMODE; }

  // Возврат значения флага "доступно для редактирования"
  int IsTinEdit() { return (AccessMode() & GENERIC_WRITE); }

  // Возврат/Установка значения флага корpектировки заголовка
  int IsHeader() { return ISHEADER; }
  int IsHeader(int set) { return (ISHEADER = set); }

  // Возврат/Установка флага ISCREATE
  int IsCreate() { return ISCREATE; }
  int IsCreate(int set) { return ISCREATE = set; }
  
  // Возврат/Установка флага корректировки палитры
  int IsPalette() { return ISPALETTE; }
  int IsPalette(int set) { return (ISPALETTE = set); }

  // Возврат/Установка флага корректировки массива вершин
  int IsVertexArray() { return ISVERTEXARRAY; }
  int IsVertexArray(int set) { return (ISVERTEXARRAY = set); }

  // Возврат/Установка флага корректировки массива треугольников
  int IsTriangleArray() { return ISTRIANGLEARRAY; }
  int IsTriangleArray(int set) { return (ISTRIANGLEARRAY = set); }

  // Возврат/Установка флага корректировки массива нормалей вершин
  int IsVertexNormalArray() { return ISVERTEXNORMALARRAY; }
  int IsVertexNormalArray(int set) { return (ISVERTEXNORMALARRAY = set); }

  // Возврат/Установка флага корректировки массива нормалей треугольников    
  int IsTriangleNormalArray() { return ISTRIANGLENORMALARRAY; }
  int IsTriangleNormalArray(int set) { return (ISTRIANGLENORMALARRAY = set); }

  // Сохранить данные в файлe
  int Save(int force);

  // Возврат/Установка флага ошибки
  long Error() { return ISERROR; }
  long Error(long error) { return (ISERROR = error); }

  // Возврат/Установка условного размера "элемента"
  double  MeterInElement() { return TinMeterInElement; }
  double  MeterInElement(double element) { return (TinMeterInElement = element); }

  // Установка/Возврат рамки
  int SetBorder(TDataEdit* data);
  TDataEdit* GetBorder() { return &BORDER; }

  // Возврат/Установка флага отображения по рамке
  int ShowByBorder();
  int ShowByBorder(int value);

  // Удалить рамку
  int DeleteBorder();

  // Создать новый файл по заголовку TIN
  // При ошибке возвращает ноль
  int CreateByTin(const char* name, TIN* tin, COLORREF* palette);

  // Закрытие файла
  void Close() { Close(0); }

  // Запись вершины в массив вершин
  // index - индекс в массиве вершин
  // При ошибке возвращает 0
  int PutVertex(const TINVERTEX* vertex, int index);

  // Запрос вершины из массива вершин
  // index - индекс в массиве вершин
  // При ошибке возвращает 0
  int GetVertex(TINVERTEX* vertex, int index);

  // Возврат адресa заголовка
  TIN* GetHeader() { return &HEADER; }

  // Возврат/Установка флагов вершины TIN-модели
  // index - индекс в массиве вершин
  // flag - адрес структуры, содержащей значения флагов вершины
  // Структурa TINVERTEXFLAG описанa в TINAPI.H
  // При ошибке возвращает 0
  int GetVertexFlags(int index, TINVERTEXFLAG* flag);
  int SetVertexFlags(int index, const TINVERTEXFLAG* flag);

  // Запись треугольника в массив треугольников
  // index - индекс в массиве треугольников
  // При ошибке возвращает 0
  int PutTriangle(const TINTRIANGLE* triangle, int index);

  // Запрос треугольника из массивa треугольников
  // index - индекс в массиве треугольников
  // При ошибке возвращает 0
  int GetTriangle(TINTRIANGLE* triangle, int index);

  // Возврат/Установка флагов треугольника TIN-модели
  // index - индекс в массиве треугольников
  // flag - адрес структуры, содержащей значения флагов треугольника
  // Структурa TINTRIANGLEFLAG описанa в TINAPI.H
  // При ошибке возвращает 0
  int GetTriangleFlags(int index, TINTRIANGLEFLAG* flag);
  int SetTriangleFlags(int index, const TINTRIANGLEFLAG* flag);

  // Запрос треугольника (triangle), содержащего заданную точку.
  // (x,y) - прямоугольные координаты точки в метрах.
  // Возвращает индекс треугольника, содержащего заданную точку.
  // При ошибке возвращает -1
  int GetPlaneTriangle(TINTRIANGLE* triangle, double x, double y);

  // Выбор значения высоты поверхности в заданной точке.
  // Координаты точки (x,y) задаются в метрах в системе координат
  // векторной карты. Заносит в height значение высоты в метрах.
  // При ошибке возвращает ноль.
  int GetPlaneSurfaceHeight(double& height, double x, double y);

  // Запрос координат юго-западной вершины из массива вершин
  // При ошибке возвращает 0
  int GetSouthWestVertex(XYHDOUBLE* point);


  // Вычисление значения высоты в точке заданного треугольника (triangle)
  // Координаты точки (x,y) задаются в метрах в системе координат
  // векторной карты. Возвращает значение высоты в метрах.
  // При ошибке возвращает ERRORHEIGHT.
  double CalcHeightByTriangle(TINTRIANGLE* triangle, double x, double y);

  // Вычисление высоты в точке (p) 3D-oтрезка (p1-p2)   
  double CalcHeightInPointOfEdge(TINVERTEX* p1, TINVERTEX* p2, DOUBLEPOINT* p);

  // Вычисление площади модели
  double CalcModelSquare();

  // Возврат указателя на палитру
  COLORREF* Palette() { return PALETTE; }

  // Открытие файла
  // При ошибке возвращает ноль
  int Open(const char * name, int mode = 0);

protected:

  // Возврат/Установка режима совместного доступа к файлу
  int ShareMode() { return SHAREMODE; }
  int ShareMode(UINT shmode)
  {
    SHAREMODE = shmode;
    return SHAREMODE;
  }

  // Закрытие файла
  // force - признак освобождения памяти
  void Close(int force);

  // Сбросить значения всех переменных класса
  void ClearAll();

  // Установить режим доступа
  int AccessMode(UINT mode)
 	{
    ACCESSMODE = (mode & (GENERIC_READ|GENERIC_WRITE));
    if (ACCESSMODE == 0) ACCESSMODE = GENERIC_READ|GENERIC_WRITE;
    return ACCESSMODE;
  }

  // Чтение заголовка из файла
  // При ошибке возвращает ноль
  int ReadHeader();

  // Запись заголовка в файл
  // При ошибке возвращает ноль
  int WriteHeader();

  // Чтение палитры из файла
  // При ошибке возвращает ноль
  int ReadPalette();

  // Запись палитры в файл
  // При ошибке возвращает ноль
  int WritePalette();

  // Чтение массива вершин из файла в буфер
  // При ошибке возвращает ноль
  int ReadVertexArray();

  // Запись массива вершин из буфера в файл
  // При ошибке возвращает ноль
  int WriteVertexArray();

  // Выделить память для массива вершин
  // При ошибке возвращает ноль
  int AllocateVertexArray(int size);

  // Чтение массива нормалей вершин из файла в буфер
  // При ошибке возвращает ноль
  int ReadVertexNormalArray();

  // Запись массива нормалей вершин из буфера в файл
  // При ошибке возвращает ноль
  int WriteVertexNormalArray();

  // Выделить память для массива нормалей вершин
  // При ошибке возвращает ноль
  int AllocateVertexNormalArray(int size);

  // Чтение массива треугольников из файла в буфер
  // При ошибке возвращает ноль
  int ReadTriangleArray();

  // Запись массива треугольников из буфера в файл
  // При ошибке возвращает ноль
  int WriteTriangleArray();

  // Выделить память для массива треугольников
  // При ошибке возвращает ноль
  int AllocateTriangleArray(int size);

  // Чтение массива нормалей треугольников из файла в буфер
  // При ошибке возвращает ноль
  int ReadTriangleNormalArray();

  // Запись массива нормалей треугольников из буфера в файл
  // При ошибке возвращает ноль
  int WriteTriangleNormalArray();

  // Выделить память для массива нормалей треугольников
  // При ошибке возвращает ноль
  int AllocateTriangleNormalArray(int size);

  // Инициализация метрики рамки
  void BorderDataInit();

  // Возврат/Установка значения флага корpектировки рамки
  int IsBorder() { return ISBORDER; }
  int IsBorder(int set) { return (ISBORDER = set); }

  // Выделить память под метрику рамки
  // При ошибке возвращает ноль
  int AllocateBorderPoints(int size);
        char* BorderPoints() { return BORDERPOINTSBUFF; }

  // Возврат/Установка смещения на запись "рамка" в файле
  unsigned long BorderOffset() { return (HEADER.BorderOffset); }
  unsigned long BorderOffset(unsigned long borderoffset)
  {
    IsHeader(TRUE);
    IsBorder(TRUE);
    return HEADER.BorderOffset=borderoffset;
  }

  // Возврат/Установка длины записи "рамка"
  long BorderLength() { return (HEADER.BorderLength); }
  long BorderLength(long borderlength)
  {
    IsHeader(TRUE);
    IsBorder(TRUE);
    return HEADER.BorderLength = borderlength;
  }

  // Чтение рамки из файла
  // При ошибке возвращает ноль
  int ReadBorder();

  // Запись рамки в файл
  // При ошибке возвращает ноль
  int WriteBorder();
        
protected:

  int Create(const char* name, TIN* tin, COLORREF* palette = 0);
  int CreateByName(const char* name);

public:

  // Создание файла с характеристиками,
  // заданными в API-структуре TINBUILD
  int Create(const char* name, const TINBUILD* parm,
             COLORREF* palette, int colorcount);


//*****************************************************************
//  Функции установки и определения полей заголовка
//*****************************************************************

  // Возврат/Установка идентификатора файла
  unsigned long Label() { return HEADER.Label; }
  unsigned long Label(unsigned long label)
  {
    IsHeader(1);
    return HEADER.Label = label;
  }

  // Возврат/Установка версии структуры
  unsigned long Version() { return HEADER.Version; }
  unsigned long Version(unsigned long version)
  {
    IsHeader(1);
    return HEADER.Version = version;
  }

  // Возврат/Установка длины файла
  unsigned long Length() { return HEADER.Length; }
  unsigned long Length(unsigned long length)
  {
    IsHeader(1);
    return HEADER.Length = length;
  }

  // Возврат/Установка пользовательского идентификатора
  unsigned long UserLabel() { return HEADER.UserLabel; }
  unsigned long UserLabel(unsigned long userlabel)
  {
    IsHeader(1);
    return HEADER.UserLabel = userlabel;
  }


  // Возврат/Установка типa модели
  long ModelType() { return HEADER.ModelType; }
  long ModelType(long modeltype)
  {
    IsHeader(1);
    return HEADER.ModelType = modeltype;
  }

  // Возврат/Установка методa построения модели
  long Method() { return HEADER.Method; }
  long Method(long method)
  {
    IsHeader(1);
    return HEADER.Method = method;
  }

  // Возврат/Установка формулярa модели
  MAPREGISTEREX* ModelRegister() { return &HEADER.ModelRegister; }
  MAPREGISTEREX* ModelRegister(const MAPREGISTEREX* modelRegister);

  // Возврат/Установка количествa вершин модели
  long VertexCount() { return HEADER.VertexCount; }
  long VertexCount(long vertexcount)
  {
    IsHeader(1);
    return HEADER.VertexCount = vertexcount;
  }

  // Возврат/Установка количествa треугольников модели
  long TriangleCount() { return HEADER.TriangleCount; }
  long TriangleCount(long trianglecount)
  {
    IsHeader(1);
    return HEADER.TriangleCount = trianglecount;
  }

  // Возврат/Установка смещения на массив вершин
  unsigned long VertexOffset() { return HEADER.VertexOffset; }
  unsigned long VertexOffset(unsigned long offset)
  {
    IsHeader(1);
    return HEADER.VertexOffset = offset;
  }

  // Возврат/Установка смещения на массив треугольников
  unsigned long TriangleOffset() { return HEADER.TriangleOffset; }
  unsigned long TriangleOffset(unsigned long offset)
  {
    IsHeader(1);
    return HEADER.TriangleOffset = offset;
  }

  // Возврат/Установка смещения на массив нормалей вершин
  unsigned long VertexNormalOffset() { return HEADER.VertexOffset; }
  unsigned long VertexNormalOffset(unsigned long offset)
  {
    IsHeader(1);
    return HEADER.VertexNormalOffset = offset;
  }

  // Возврат/Установка смещения на массив нормалей треугольников
  unsigned long TriangleNormalOffset() { return HEADER.TriangleOffset; }
  unsigned long TriangleNormalOffset(unsigned long offset)
  {
    IsHeader(1);
    return HEADER.TriangleNormalOffset = offset;
  }

  // Возврат/Установка смещения на палитру отображения поверхности
  unsigned long PaletteOffset() { return HEADER.PaletteOffset; }
  unsigned long PaletteOffset(unsigned long offset)
  {
    IsHeader(1);
    return HEADER.PaletteOffset = offset;
  }

  // Возврат/Установка количества цветов палитры отображения поверхности
  unsigned long PaletteColorCount() { return HEADER.PaletteColorCount; }
  unsigned long PaletteColorCount(unsigned long palettecolorcount)
  {
    IsHeader(1);
    return HEADER.PaletteColorCount = palettecolorcount;
  }

  // Возврат координат левого нижнего угла габаритов модели (метры)
  double X1() { return HEADER.X1; }
  double Y1() { return HEADER.Y1; }

  // Установка координат левого нижнего угла габаритов модели (метры)
  double X1(double x1)
  {
    IsHeader(1);
    return HEADER.X1 = x1;
  }

  double Y1(double y1)
  {
    IsHeader(1);
    return HEADER.Y1 = y1;
  }

  // Возврат координат правого верхнего угла габаритов модели (метры)
  double X2() { return HEADER.X2; }
  double Y2() { return HEADER.Y2; }

  // Установка координат правого верхнего угла габаритов модели (метры)
  double X2(double x2)
  {
    IsHeader(1);
    return HEADER.X2 = x2;
  }

  double Y2(double y2)
  {
    IsHeader(1);
    return HEADER.Y2 = y2;
  }

  // Возврат минимального значения высоты в метрах
  double H1() { return HEADER.H1; }
  double MinHeightMeter() { return HEADER.H1; }

  // Возврат максимального значения высоты в метрах
  double H2() { return HEADER.H2; }
  double MaxHeightMeter() { return HEADER.H2; }

  // Установка минимального значения высоты в метрах
  double H1(double h1)
  {
    IsHeader(1);
    return HEADER.H1 = h1;
  }

  // Установка максимального значения высоты в метрах
  double H2(double h2)
  {
    IsHeader(1);
    return HEADER.H2 = h2;
  }


  // Определение активности TIN-изображения
  int IsActive() { return (int)FILEID; }


  // Возврат/Установка полного имени файла
  char* Name() { return NAME; }
  char* Name(char* name)
  {
    if (name == 0) return 0;
    return strncpy(NAME, name, sizeof(NAME));
  }


private:

  // Заголовок
  TIN  HEADER;

  // Cмещение на заголовок
  unsigned long  HEADEROFFSET;

  // Указатель на массив вершин
  TINVERTEX*  VERTEXARRAYBUFF;

  // Размер буфера для массива вершин
  int  VERTEXARRAYLENGTH;

  // Указатель на массив треугольников
  TINTRIANGLE*  TRIANGLEARRAYBUFF;

  // Размер буфера для массива треугольников
  int  TRIANGLEARRAYLENGTH;

  // Указатель на массив нормалей вершин
  XYHDOUBLE*  VERTEXNORMALARRAYBUFF;

  // Размер буфера для массива нормалей вершин
  int  VERTEXNORMALARRAYLENGTH;

  // Указатель на массив нормалей треугольников
  XYHDOUBLE*  TRIANGLENORMALARRAYBUFF;

  // Размер буфера для массива нормалей треугольников
  int  TRIANGLENORMALARRAYLENGTH;

  // Идентификатор файла
  HANDLE  FILEID;

  // Полное имя файла
  char  NAME[260];

  // Палитра
  COLORREF  PALETTE[256];

  // Режим доступа к файлу
  int  ACCESSMODE;

  // Режим совместного доступа к файлу
  int  SHAREMODE;

  // Флаг Create/Open
  int  ISCREATE;

  // Флаг корpектировки рамки
  int  ISBORDER;

  // Флаг корpектировки палитры
  int  ISPALETTE;

  // Флаг корpектировки заголовка
  int  ISHEADER;

  // Флаг корpектировки массива вершин
  int  ISVERTEXARRAY;

  // Флаг корpектировки массива треугольников
  int  ISTRIANGLEARRAY;

  // Флаг корpектировки массива нормалей вершин
  int  ISVERTEXNORMALARRAY;

  // Флаг корpектировки массива нормалей треугольников
  int  ISTRIANGLENORMALARRAY;

  // Флаг состояния ошибки
  long  ISERROR;

  // Условный размер "элемента"
  double  TinMeterInElement;


  TDataEdit  BORDER;             // Указатель на рамку
  char*      BORDERPOINTSBUFF;   // Указатель на метрику рамки
  int        BORDERPOINTSLENGTH; // Размер буфера для метрики рамки
  int        BORDERPOINTSCOUNT;  // Число точек рамки
  POLYDATAEX BORDERDATA;         // Метрика рамки (BORDERPOINTSBUFF)

};

#endif // __cplusplus

#endif // !HIDETIN

#endif  // TINBASE_H


