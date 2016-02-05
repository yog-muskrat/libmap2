
#ifndef MTLBASE_H
#define MTLBASE_H

#ifndef HIDEMTL

#ifndef RMFBASE_H
  #include "rmfbase.h"
#endif

#ifdef __cplusplus

#include "mtlapi.h"
//------------------------------------------------------------------
//  ЗАГОЛОВОК ЗАПИСИ "ОПИСАТЕЛЬ СЛОЕВ" (MTL0)
//------------------------------------------------------------------
typedef struct LAYERHEADER // РАЗМЕР СТРУКТУРЫ 320 БАЙТ
{
  long  Ident;             // ИДЕНТИФИКАТОР НАЧАЛА ЗАПИСИ
                           //  (7FFF7FFF)
  long  Length;            // ДЛИНА ЗАПИСИ "ОПИСАТЕЛЬ СЛОЕВ"

  long  LayerCount;        // К-ВО СЛОЕВ
  long  MaterialCount;     // К-ВО МАТЕРИАЛОВ

  long  HeightSizeBytes;   // РАЗМЕР ВЫСОТЫ РЕЛЬЕФА В БАЙТАХ
                           // (ЕСЛИ НОЛЬ - РЕЛЬЕФ ОТСУТСТВУЕТ)
  long  LayerSizeBytes;    // РАЗМЕР МОЩНОСТИ СЛОЯ В БАЙТАХ

  unsigned
  long  LayerPseudoCode;   // ЗНАЧЕНИЕ ПСЕВДОКОДА ДЛЯ МОЩНОСТИ СЛОЯ
  long  LayerMeasure;      // ЕДИНИЦА ИЗМЕРЕНИЯ МОЩНОСТИ СЛОЯ

  double  BotLevelMeter;   // НИЖНИЙ УРОВЕНЬ СЛОЕВ В МЕТРАХ

  double  MaxSummaryPowerMeter;  // МАКСИМАЛЬНАЯ СУММАРНАЯ МОЩНОСТЬ
                                 // СЛОЕВ В МЕТРАХ        

  char  Reserve[12];            // РЕЗЕРВ                 
  char  MaterialFileName[260];  // ИМЯ ФАЙЛА ОПИСАНИЯ МАТЕРИАЛОВ
}
  LAYERHEADER;

// ПОСЛЕ ЗАГОЛОВКА ЗАПИСИ "ОПИСАТЕЛЬ СЛОЕВ" ПОСЛЕДОВАТЕЛЬНО РАСПОЛОЖЕНЫ
// СОБСТВЕННО ОПИСАТЕЛИ СЛОЕВ В КОЛИЧЕСТВЕ LayerCount

//------------------------------------------------------------------
//  ОПИСАТЕЛЬ СЛОЯ (MTL0) - УСТАРЕВШАЯ СТРУКТУРА         
//------------------------------------------------------------------
typedef struct LAYERDESCOLD  // РАЗМЕР СТРУКТУРЫ 48 БАЙТ
{
  long  MaterialCode;     // КОД МАТЕРИАЛА
  long  LayerColor;       // ЦВЕТ СЛОЯ (ПРИ MaterialCode = 0)
  long  MaxLayerHeight;   // МАКСИМАЛЬНАЯ МОЩНОСТЬ СЛОЯ (МЕТРЫ)
  char  Reserve[20];      // РЕЗЕРВ
  char  ShortName[16];    // КОРОТКОЕ ИМЯ СЛОЯ
}
  LAYERDESCOLD;

//------------------------------------------------------------------
//  ОПИСАТЕЛЬ СЛОЯ (MTL0)                                
//------------------------------------------------------------------
typedef struct LAYERDESC  // РАЗМЕР СТРУКТУРЫ 128 БАЙТ
{
  long  MaterialCode;     // КОД МАТЕРИАЛА
  long  LayerColor;       // ЦВЕТ СЛОЯ (ПРИ MaterialCode = 0)
  long  MaxLayerHeight;   // МАКСИМАЛЬНАЯ МОЩНОСТЬ СЛОЯ (МЕТРЫ)
  char  Reserve[20];      // РЕЗЕРВ
  char  ShortName[16];    // КОРОТКОЕ ИМЯ СЛОЯ - КЛЮЧ СЕМАНТИКИ
  char  LongName[32];     // ИМЯ СЛОЯ - НАЗВАНИЕ СЕМАНТИКИ
  char  Reserve2[48];     // РЕЗЕРВ
}
  LAYERDESC;


class _DLLCLASS TMtl: public TRmf
{
 public:

 // Пустой объект
 TMtl();

 // Объект для связи с существующим файлом матрицы
 TMtl(const char* name, int mode = 0);

 ~TMtl();


 //***************************************************************
 //  Функции установки и определения полей заголовка (RMF)
 //***************************************************************

 // Возврат/Установка смещения в файле записи "ОПИСАТЕЛЬ СЛОЕВ"
 unsigned long LayerDescOffset() { return (HEADER.LayerDescOffset); }
 unsigned long LayerDescOffset(unsigned long layerdescoffset)
 {
   IsHeader(1);
   IsLayerDesc(1);
   return HEADER.LayerDescOffset = layerdescoffset;
 }

 // Возврат/Установка длины записи "ОПИСАТЕЛЬ СЛОЕВ"
 long LayerDescLength() { return (HEADER.LayerDescLength); }
 long LayerDescLength(long layerdesclength)
 {
   IsHeader(1);
   IsLayerDesc(1);
   return HEADER.LayerDescLength = layerdesclength;
 }

 // Возврат размера элемента в байтах
 int ElementSizeBytes() { return (ElementSize()>>3); }

 // Возврат минимального значения высоты в метрах
 double MinimumHeight()  { return HeightUnitToMeter(HEADER.Minimum); }
 double MinHeightMeter() { return HeightUnitToMeter(HEADER.Minimum); }

 // Возврат максимального значения высоты в метрах
 double MaximumHeight()  { return HeightUnitToMeter(HEADER.Maximum); }
 double MaxHeightMeter() { return HeightUnitToMeter(HEADER.Maximum); }


 //***************************************************************
 // Функции установки и определения полей записи "ОПИСАТЕЛЬ СЛОЕВ"
 //***************************************************************

 //-------------------------------------------------------------
 // Возврат идентификатора записи "ОПИСАТЕЛЬ СЛОЕВ"
 //-------------------------------------------------------------
 inline long TMtl::Ident()
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   return LAYERHEADERBUFF->Ident;
 }

 //-------------------------------------------------------------
 // Установка идентификатора записи "ОПИСАТЕЛЬ СЛОЕВ"
 //-------------------------------------------------------------
 inline long TMtl::Ident(long ident)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   IsLayerDesc(1);

   return LAYERHEADERBUFF->Ident = ident;
 }

 //-------------------------------------------------------------
 // Возврат длины записи "ОПИСАТЕЛЬ СЛОЕВ"
 //-------------------------------------------------------------
 inline long TMtl::LayerHeaderLength()  
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   return LAYERHEADERBUFF->Length;
 }

 //-------------------------------------------------------------
 // Установка длины записи "ОПИСАТЕЛЬ СЛОЕВ"
 //-------------------------------------------------------------
 inline long TMtl::LayerHeaderLength(long length)  
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   IsLayerDesc(1);

   return LAYERHEADERBUFF->Length = length;
 }

 //-------------------------------------------------------------
 // Возврат количества слоев
 //-------------------------------------------------------------
 inline long TMtl::LayerCount()
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   return LAYERHEADERBUFF->LayerCount;
 }

 //-------------------------------------------------------------
 // Установка количества слоев
 //-------------------------------------------------------------
 inline long TMtl::LayerCount(long layercount)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   IsLayerDesc(1);

   return LAYERHEADERBUFF->LayerCount = layercount;
 }

 //-------------------------------------------------------------
 // Возврат количества материалов
 //-------------------------------------------------------------
 inline long TMtl::MaterialCount()
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   return LAYERHEADERBUFF->MaterialCount;
 }

 //-------------------------------------------------------------
 // Установка количества  материалов
 //-------------------------------------------------------------
 inline long TMtl::MaterialCount(long materialcount)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   IsLayerDesc(1);

   return LAYERHEADERBUFF->MaterialCount = materialcount;
 }

 //-------------------------------------------------------------
 // Возврат нижнего уровня слоев в метрах
 //-------------------------------------------------------------
 inline double TMtl::BotLevelMeter()
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   return LAYERHEADERBUFF->BotLevelMeter;
 }

 //-------------------------------------------------------------
 // Установка нижнего уровня слоев в метрах
 //-------------------------------------------------------------
 inline double TMtl::BotLevelMeter(double botlevelmeter)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   IsLayerDesc(1);

   return LAYERHEADERBUFF->BotLevelMeter = botlevelmeter;
 }

 //-------------------------------------------------------------
 // Возврат максимальной суммарной мощности слоев в метрах  
 //-------------------------------------------------------------
 inline double TMtl::MaxSummaryPowerMeter()
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (LAYERHEADERBUFF->MaxSummaryPowerMeter <= 0)
   {
     return HeightUnitToMeter(Maximum()) -
            min(BotLevelMeter(),HeightUnitToMeter(Minimum()));
   }

   return LAYERHEADERBUFF->MaxSummaryPowerMeter;
 }

 //-------------------------------------------------------------
 // Установка максимальной суммарной мощности слоев в метрах  
 //-------------------------------------------------------------
 inline double TMtl::MaxSummaryPowerMeter(double maxsummarypower)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   IsLayerDesc(1);

   return LAYERHEADERBUFF->MaxSummaryPowerMeter = maxsummarypower;
 }

 //-------------------------------------------------------------
 // Возврат размера высоты рельефа в байтах
 //-------------------------------------------------------------
 inline long TMtl::HeightSizeBytes()
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   return LAYERHEADERBUFF->HeightSizeBytes;
 }

 //-------------------------------------------------------------
 // Установка размера высоты рельефа в байтах
 //-------------------------------------------------------------
 inline long TMtl::HeightSizeBytes(long heightsizebytes)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   IsLayerDesc(1);

   return LAYERHEADERBUFF->HeightSizeBytes = heightsizebytes;
 }

 //-------------------------------------------------------------
 // Возврат размера мощности слоя в байтах
 //-------------------------------------------------------------
 inline long TMtl::LayerSizeBytes()
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   return LAYERHEADERBUFF->LayerSizeBytes;
 }

 //-------------------------------------------------------------
 // Установка размера мощности слоя в байтах
 //-------------------------------------------------------------
 inline long TMtl::LayerSizeBytes(long layersizebytes)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   IsLayerDesc(1);

   return LAYERHEADERBUFF->LayerSizeBytes = layersizebytes;
 }

 //-------------------------------------------------------------
 // Возврат значения псевдокода для мощности слоя
 //-------------------------------------------------------------
 inline unsigned long TMtl::LayerPseudoCode()
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   return LAYERHEADERBUFF->LayerPseudoCode;
 }

 //-------------------------------------------------------------
 // Установка значения псевдокода для мощности слоя
 //-------------------------------------------------------------
 inline unsigned long
 TMtl::LayerPseudoCode(unsigned long layerpseudocode)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   IsLayerDesc(1);

   return LAYERHEADERBUFF->LayerPseudoCode = layerpseudocode;
 }

 //-------------------------------------------------------------
 // Возврат единицы измерения мощности слоя
 //-------------------------------------------------------------
 inline long TMtl::LayerMeasure()
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   return LAYERHEADERBUFF->LayerMeasure;
 }

 // Установка единицы измерения мощности слоя
 long LayerMeasure(long layermeasure);

 //-------------------------------------------------------------
 // Возврат имени файла описания материалов
 //-------------------------------------------------------------
 inline char* MaterialFileName()
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   return LAYERHEADERBUFF->MaterialFileName;
 }

 //-------------------------------------------------------------
 // Установка имени файла описания материалов
 //-------------------------------------------------------------
 inline char* MaterialFileName(char* name)
 {
   if (name == 0)
   {
     Error(IDS_PARM);
     return 0;
   }

   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   IsLayerDesc(1);

   strncpy(LAYERHEADERBUFF->MaterialFileName, name, sizeof(LAYERHEADERBUFF->MaterialFileName));

   return LAYERHEADERBUFF->MaterialFileName;
 }

 //-------------------------------------------------------------
 // Возврат кода материала слоя layer
 //-------------------------------------------------------------
 inline long MaterialCode(long layer)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (layer < 1 || layer > LAYERHEADERBUFF->LayerCount)
   {
     Error(IDS_STRUCT);
     return 0;
   }

   return (LAYERDESCBUFF + layer - 1)->MaterialCode;
 }

 //-------------------------------------------------------------
 // Установка кода материала(materialcode) слоя layer
 //-------------------------------------------------------------
 inline long MaterialCode(long layer, long materialcode)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (layer < 1 || layer > LAYERHEADERBUFF->LayerCount)
   {
     Error(IDS_STRUCT);
     return 0;
   }

   IsLayerDesc(1);

   return (LAYERDESCBUFF + layer - 1)->MaterialCode = materialcode;
 }

 //-------------------------------------------------------------
 // Возврат цвета слоя layer
 //-------------------------------------------------------------
 inline long LayerColor(long layer)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (layer < 1 || layer > LAYERHEADERBUFF->LayerCount)
   {
     Error(IDS_STRUCT);
     return 0;
   }

   return (LAYERDESCBUFF + layer - 1)->LayerColor;
 }

 //-------------------------------------------------------------
 // Установка цвета(layercolor) слоя layer
 //-------------------------------------------------------------
 inline long LayerColor(long layer, long layercolor)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (layer < 1 || layer > LAYERHEADERBUFF->LayerCount)
   {
     Error(IDS_STRUCT);
     return 0;
   }

   IsLayerDesc(1);

   return (LAYERDESCBUFF + layer - 1)->LayerColor = layercolor;
 }

 //-------------------------------------------------------------
 // Возврат максимальной мощности слоя layer
 //-------------------------------------------------------------
 inline long MaxLayerHeight(long layer)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (layer < 1 || layer > LAYERHEADERBUFF->LayerCount)
   {
     Error(IDS_STRUCT);
     return 0;
   }

   return (LAYERDESCBUFF + layer - 1)->MaxLayerHeight;
 }

 //-------------------------------------------------------------
 // Установка максимальной мощности(maxlayerheight) слоя layer
 //-------------------------------------------------------------
 inline long MaxLayerHeight(long layer, long maxlayerheight)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (layer < 1 || layer > LAYERHEADERBUFF->LayerCount)
   {
     Error(IDS_STRUCT);
     return 0;
   }

   IsLayerDesc(1);

   return (LAYERDESCBUFF + layer - 1)->MaxLayerHeight = maxlayerheight;
 }

 //-------------------------------------------------------------
 // Возврат короткого имени (ключ семантики) слоя layer
 //-------------------------------------------------------------
 inline char* ShortName(long layer)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (layer < 1 || layer > LAYERHEADERBUFF->LayerCount)
   {
     Error(IDS_STRUCT);
     return 0;
   }

   return (LAYERDESCBUFF + layer - 1)->ShortName;
 }

 //-------------------------------------------------------------
 // Установка короткого имени name (ключ семантики) слоя layer
 //-------------------------------------------------------------
 inline char* ShortName(long layer, char* name)
 {
   if (name == 0)
   {
     Error(IDS_PARM);
     return 0;
   }

   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (layer < 1 || layer > LAYERHEADERBUFF->LayerCount)
   {
     Error(IDS_STRUCT);
     return 0;
   }

   IsLayerDesc(1);

   strncpy((char*)(LAYERDESCBUFF + layer - 1)->ShortName,
            name, sizeof((LAYERDESCBUFF + layer - 1)->ShortName));

   return (LAYERDESCBUFF + layer - 1)->ShortName;
 }

 //-------------------------------------------------------------
 // Возврат имени (название семантики) слоя layer
 //-------------------------------------------------------------
 inline char* LongName(long layer)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (layer < 1 || layer > LAYERHEADERBUFF->LayerCount)
   {
     Error(IDS_STRUCT);
     return 0;
   }

   return (LAYERDESCBUFF + layer - 1)->LongName;
 }

 //-------------------------------------------------------------
 // Установка имени name (название семантики) слоя layer
 //-------------------------------------------------------------
 inline char* LongName(long layer, char* name)
 {
   if (name == 0)
   {
     Error(IDS_PARM);
     return 0;
   }

   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (layer < 1 || layer > LAYERHEADERBUFF->LayerCount)
   {
     Error(IDS_STRUCT);
     return 0;
   }

   IsLayerDesc(1);

   strncpy((char*)(LAYERDESCBUFF + layer - 1)->LongName,
            name, sizeof((LAYERDESCBUFF + layer - 1)->LongName));

   return (LAYERDESCBUFF + layer - 1)->LongName;
 }

 //***************************************************************
 //  Функции для работы с файлом :
 //***************************************************************

 // Открытие файла
 int Open(const char *name, int mode = 0);

 // Сохранить данные в файлe
 int Save(int force);  

 // Создание файла матрицы с заданными характеристиками    
 int Create(const char* name, BUILDMTL* parm,
            MTRPROJECTIONDATA * mtrprojectiondata);

 // Создание файла матрицы с заданными характеристиками
 /*
 int Create(const char* name, MTLBUILDPARM* parm);

 int CreateMtlFileEx(const char* name, MTLBUILDPARM* parm,
                     MTRPROJECTIONDATA * mtrprojectiondata); */

 // Запросить описание файла матрицы
 // describe - адрес структуры, в которой будет размещено
 // описание матрицы
 // При ошибке возвращает ноль
 int GetMtlDescribe(MTLDESCRIBE* describe);


 //***************************************************************
 //  Функции ввода/вывода для элементов матрицы слоев :
 //***************************************************************

 // Получение адреса элемента,заданного его абсолютными индексами.
 // Элемент содержит высоту (при HeightSizeBytes() != 0)
 // и массив мощностей.
 // Высота представлена числом типа :
 //  - short  при HeightSizeBytes() == 2
 //  - long   при HeightSizeBytes() == 4
 // Массив мощностей содержит числа типа :
 //  - unsigned char   при LayerSizeBytes() == 1
 //  - unsigned short  при LayerSizeBytes() == 2
 //  - unsigned long   при LayerSizeBytes() == 4
 // При ошибке возвращает ноль.
 char* GetElement(int string,int column);

 // Получение адреса элемента,заданного его абсолютными индексами.
 // Если элемент отсутствует в буфере, то он создается.
 // При ошибке возвращает ноль.
 char* GetElementAndCreate(int string,int column);

 // Получение адреса массива мощностей элемента,
 // заданного его абсолютными индексами.
 // Массив мощностей содержит элементы типа :
 //  - unsigned char  при LayerSizeBytes() == 1
 //  - unsigned short при LayerSizeBytes() == 2
 //  - unsigned long  при LayerSizeBytes() == 4
 // При ошибке возвращает ноль.
 char* GetPowers(int string,int column);

 // Получение адреса элемента,заданного его
 // прямоугольными координатами в метрах.
 // При ошибке возвращает ноль.
 char* GetPlaneElement(double x,double y);

 // Получение адреса элемента,заданного его
 // прямоугольными координатами в метрах.
 // Если элемент отсутствует в буфере, то он создается.
 // При ошибке возвращает ноль.
 char* GetPlaneElementAndCreate(double x,double y);

 // Выбор значения абсолютной высоты в заданной точке.
 // Координаты точки (x,y) задаются в метрах в системе координат
 // векторной карты. Заносит в height значение высоты в метрах.
 // При ошибке возвращает ноль.
 //double GetPlaneHeight(double x,double y);
 int GetPlaneHeight(double& height,double x,double y);

 // Вычисление значения высоты методом треугольников по заданным
 // абсолютным индексам
 int GetHeightTriangle(double& height,double Str,double Col);

 // Вычисление значения высоты методом треугольников по заданным
 // прямоугольным координатам (в метрах)
 int GetPlaneHeightTriangle(double& height, double x, double y);

 // Вычисление значений мощностей слоев методом треугольников
 // по заданным абсолютным индексам
 // powers - адрес массива для записи вычисленных значений мощностей
 // count - размер массива, должен быть не менее TMtl::LayerCount().
 // Возвращает количество заполненных элементов массива powers.
 // При ошибке возвращает ноль.
 int GetPowersTriangle(double Str,double Col,
                       double* powers,long count);

 // Вычисление значений мощностей слоев методом треугольников
 // по заданным прямоугольным координатам (в метрах).
 // powers - адрес массива для записи вычисленных значений мощностей
 // count - размер массива, должен быть не менее TMtl::LayerCount().
 // Возвращает количество заполненных элементов массива powers.
 // При ошибке возвращает ноль.
 int GetPlanePowersTriangle(double x,double y,
                            double* powers,long count);

 // Выбор значения мощности слоя layernumber в заданной точке.
 // Координаты точки (x,y) задаются в метрах в системе координат
 // векторной карты.
 // При ошибке возвращает ноль.
 int GetPlanePower(double& power,double x,double y,long layernumber);

 
 // Вычисление значения мощности слоя layernumber (в метрах)
 // методом треугольников по заданным  прямоугольным координатам
 // (в метрах). При ошибке возвращает ноль.
 int GetPlanePowerTriangle(double& power,double x,double y,int layernumber);

 
 // Вычисление значения значения мощности слоя layernumber (в метрах)
 // методом треугольников по заданным абсолютным индексам
 // При ошибке возвращает ноль.
 int GetPowerTriangle(double& power,double Str,double Col,int layernumber);

 // Выбор значения абсолютной высоты из элемента,заданного
 // его абсолютными индексами. При ошибке возвращает ноль.
 int GetHeight(long& height,int string,int column);

 // Выбор значения мощности слоя layernumber из элемента,
 // заданного его абсолютными индексами. При ошибке возвращает ноль.
 int GetPower(long& power,int string,int column,int layernumber);

 // Занесение значения абсолютной высоты в элемент,
 // соответствующий заданной точке.
 // Координаты точки и высота(x,y,h) задаются в метрах
 // в системе координат векторной карты.
 // В случае ошибки возвращает 0.
 int PutPlaneHeight(double x,double y,double h);

 // Занесение значения мощности слоя layernumber в заданной точке.
 // Координаты точки (x,y) и значение мощности (power)
 // задаются в метрах в системе координат векторной карты.
 // В случае ошибки возвращает 0.
 int PutPlanePower(double x,double y,double power,long layernumber);

 // Запись в буфер элемента,
 // заданного его абсолютными индексами.
 // address - адрес элемента.
 // size - размер элемента в байтах.
 // При ошибке возвращает ноль.
 int PutElement(char* address,int size,int string,int column);

 // Запись в буфер элемента,
 // заданного его прямоугольными координатами в метрах.
 // address - адрес элемента.
 // size - размер элемента в байтах.
 // При ошибке возвращает ноль.
 int PutPlaneElement(char* address,int size,double x,double y);

 // Пересчитать единицы мощности в метры
 inline double PowerUnitToMeter(double unit)
 {
   return unit*PowerMeterInUnit;
 }

 // Пересчитать метры в единицы мощности
 inline double PowerMeterToUnit(double meter)
 {
   return meter*PowerUnitInMeter;
 }

 protected:

 // Сброс значений всех переменных класса
 void ClearAll();

 // Выделение памяти для описателя слоев.
 // При ошибке возвращает ноль.
 int AllocateLayerDesc(int size);

 // Получение адреса блока, заданного своими индексами.
 // Если заданного блока нет в буфере, то он считывается из файла,
 // при отсутствии в файле - создается.
 // При ошибке возвращает ноль
 char* GetBlockAddressAndCreate(int string, int column);

 // Заполнение блока буфера значением "отсутствие информации"
 int BufferBlockInit(int partindex);

 // Возврат адреса заголовка описателя слоев
 LAYERHEADER* LayerHeader() { return LAYERHEADERBUFF; }

 // Возврат адреса описателя первого слоя
 LAYERDESC* LayerDesc() { return LAYERDESCBUFF; }

 // Возврат/Установка флага корpектировки описателя слоев
 int IsLayerDesc() { return ISLAYERDESC; }
 int IsLayerDesc(int set) { return (ISLAYERDESC = set); }

 // Чтение описателя слоев. При ошибке возвращает ноль.
 int ReadLayerDesc();

 // Запись описателя слоев. При ошибке возвращает ноль.
 int WriteLayerDesc();

 //*****************************************************************
 //  Член-данные:
 //*****************************************************************

protected:

 LAYERHEADER* LAYERHEADERBUFF; // Адрес заголовка описателя слоев
 LAYERDESC* LAYERDESCBUFF;     // Адрес описателя первого слоя
 int   LAYERDESCLENGTH;        // Размер буфера для описателя слоев
 int   ISLAYERDESC;            // Флаг корpектировки описателя слоев
 
 double PowerUnitInMeter;     // Число единиц мощности на метр
 double PowerMeterInUnit;     // Число метров в единице мощности

};

#endif // __cplusplus

#endif // !HIDEMTL

#endif  // MTLBASE_H

