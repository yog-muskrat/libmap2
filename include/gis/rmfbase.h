
#ifndef RMFBASE_H
#define RMFBASE_H

#include "rmf.h"
#include "compress.h"
#include "mapdat.h"

#ifndef MAPTRANS_H   
  #include "maptrans.h"
#endif

#define min(a,b) (((a) < (b)) ? (a) : (b)) 
#define max(a,b) (((a) > (b)) ? (a) : (b))  // 24/11/05
class TRst;

// Палитра, определенная в файле
typedef struct RMFRGBFILE  
{
   char Red;
   char Green;
   char Blue;
}
  RMFRGBFILE;

// Положение элемента
typedef struct RMFELEMENT  
{
   LONG Str;
   LONG Col;
}
  RMFELEMENT;

// Положение блока в р-м изображении
typedef struct RMFBLOCK    
{
   union { RMFELEMENT Begin; RMFELEMENT UL; };  // Верхний левый угол
   union { RMFELEMENT End;   RMFELEMENT DR; };  // Нижний правый угол
}
  RMFBLOCK;

// Положение блока в БЛОКАХ
typedef struct RMFSITE   
{
   int Str;
   int Col;
}
  RMFSITE;

// Описатель буфера
typedef struct RMFPART
{
   int      Index;       // индекс блока
   int      String;      // номер строки
   int      Column;      // номер колонки
   char*    Address;     // адрес блока
   int      Isdirty;     // наличие изменений блока
   unsigned Fresh;       // индекс давности запроса блока
   int      Lock;        // флаг захвата блока          
                         // (блокировка обновления)
}
  RMFPART;

// Структура предназначена для передачи информации об
// отредактированном блоке основного растра при
// обновление уменьiенной копии растра
typedef struct RSTNEWBLOCK  
{
  int  FlagEdit;        // Флаг отредактированности блока(0/1)
  RMFSITE Block;        // Положение блока в БЛОКАХ
}
  RSTNEWBLOCK;

// Коды возврата функций
enum RMFRETCODE { RMFOKEY = 1 };

// Единицы измерения
enum RMFUNITS  { rmfm = 0, rmfdm = 1, rmfcm = 2, rmfmm = 3 };

enum { RMFFIRSTLINE = 1, RMFLASTLINE = -1 };

// Структура, содержащие переменные класса TRmf
typedef struct _DLLCLASS TRMFDATA
{
  TRMFDATA() : BORDER(), MASK(), Translate(), CompressData() {}   

  RMF        HEADER;             // Заголовок
  unsigned long  HEADEROFFSET;   // Cмещение на заголовок
  char       NAME[MAX_PATH];     // Полное имя файла
  char       NAMEOFADDFILE[MAX_PATH];// Полное имя добавочного файла
  COLORREF   PALETTE[256];       // Палитра

  BLOCKDESC* BLOCKDESCBUFF;      // Указатель на описатель блоков
  int        BLOCKDESCLENGTH;    // Размер буфера для описателя блоков

  char*      BLOCKFLAGSBUFF;     // Указатель на массив флагов блоков
  int        BLOCKFLAGSLENGTH;   // Размер буфера для массива флагов блоков

  char*      BORDERPOINTSBUFF;   // Указатель на метрику рамки
  int        BORDERPOINTSLENGTH; // Размер буфера для метрики рамки
  int        BORDERPOINTSCOUNT;  // Число точек рамки
  POLYDATAEX   BORDERDATA;         // Метрика рамки (BORDERPOINTSBUFF)

  char*      BLOCKMASKBUFF;      // Указатель на битовую маску блока
  int        BLOCKMASKLENGTH;    // Размер буфера для битовой маски блока
  int        BLOCKMASKWIDTH;     // Ширина маски в битах (кратно 32)

  TDataEdit  BORDER;         // Указатель на рамку  

  int        ACCESSMODE;     // Режим доступа к файлу
  int        SHAREMODE;      // Режим совместного доступа к файлу
  HANDLE     FILEID;         // Текущий идентификатор файла
  HANDLE     FILEID0;        // Идентификатор первого файла (Размер до 4Gb)
  HANDLE     FILEID1;        // Идентификатор второго файла (Размер до 4Gb)

  int        ISCREATE;       // Флаг Create/Open
  int        ISBLOCKDESC;    // Флаг корpектировки описателя блоков
  int        ISBLOCKFLAGS;   // Флаг корpектировки массива флагов блоков
  int        ISBORDER;       // Флаг корpектировки рамки
  int        ISPALETTE;      // Флаг корpектировки палитры
  int        ISHEADER;       // Флаг корpектировки заголовка
  long       ISERROR;        // Флаг состояния ошибки
  int        ISADDITION;     // Флаг корpектировки дополнительного описания растра
  int        ISMASK;         // Флаг корpектировки маски    

  char*      BUFFER;         // Указатель на начало буфера
  int        BUFSIZE;        // Размер блока буфера
  int        BLOCKNUMB;      // К-во блоков буфера
  char* CompressBlockBuffer; // Буфер чтения сжатого блока
                             // (выделяется вместе с BUFFER)

  RMFPART    PART[16];       // Описатель буфера
  int        CURRENT;        // Номер текущей части буфера
  int        BlockCountLimit;// Ограничение количества выделяемых блоков 
       // Ограничения вступают в силу при добавлении в документ 100,200,256 растров
       // Рекомендовано выделять 4,2,1 блок соответственно.

  FILETIME  Condition;       // Состояние файла данных  

  unsigned   Fresh;          // текущий индекс давности запроса блока
  int    DuplicateExistence; // Флаг использования класса при создании
                             // объекта уменьшенной копии 
  
  double HeightUnitInMeter;  // Число единиц высоты на метр
  double HeightMeterInUnit;  // Число метров в единице высоты
  TRst          * Duplicate;  // Указатель на КЛАСС УМЕНЬШЕННОЙ

  RSTNEWBLOCK   NewBlock;     // Структура предназначена для передачи информации об
                              // отредактированном блоке основного растра при
                              // ообновление уменьненной копии растра
                              // Используется в связке WriteBlock - SaveDuplicates

  int           NewBorder;    // Флаг занесения рамки в файл
                              // Если 1,то длина каждой уменьшенной копии изменилась
  int           ReadOk;

  TCompress     CompressData;

  RMFADDITION   ADDITION;  // Дополнительное описание растра (матрицы)

  int           NewMask;       // Флаг занесения маски в файл    
                               // Если 1,то длина каждой уменьшенной копии изменилась
  char*      MASKPOINTSBUFF;   // Указатель на метрику маски       
  int        MASKPOINTSLENGTH; // Размер буфера для метрики маски  
  int        MASKPOINTSCOUNT;  // Число точек маски                
  POLYDATAEX   MASKDATA;       // Метрика маски (MASKPOINTSBUFF)   

  TTranslate Translate;        // ПАРАМЕТРЫ ПЕРЕСЧЕТА КООРДИНАТ    
  int        GeoAvailableFlag; // ФЛАГ ВОЗМОЖНОСТИ РАСЧЕТА ГЕОДЕЗИЧЕСКИХ КООРДИНАТ 

  TDataEdit  MASK;             // Указатель на маску  
}
 TRMFDATA;

// Создать новый файл по заголовку RMF
// При ошибке возвращает ноль
int _fastcall rmfCreateByRmf(TRMFDATA *rmfdata, char* name,
                             RMF* rmf, RMFADDITION* rmfaddition,  
                             COLORREF* palette);

// Сбросить значения всех переменных
void _fastcall rmfClearAll(TRMFDATA *rmfdata);

// Очистка буфера
void _fastcall rmfClearBuffer(TRMFDATA *rmfdata);

// Сохранить данные в файлe
int _fastcall rmfSave(TRMFDATA *rmfdata, int force);

// Закрытие файла
void _fastcall rmfClose(TRMFDATA *rmfdata, int force);

// Освободить память буфера
void _fastcall rmfFreeBuffer(TRMFDATA *rmfdata);

// Открытие файла
// При ошибке возвращает ноль
int _fastcall rmfOpen(TRMFDATA *rmfdata, const char * name, int mode);

// Создание файла
// При ошибке возвращает ноль
int _fastcall rmfCreateByName(TRMFDATA *rmfdata, const char * name);

// Разместить и инициализировать буфер и битовую маску блока
// Буфер включает в себя блоки
int _fastcall rmfAllocateBuffer(TRMFDATA *rmfdata, int count);

// Выделить память под описатели блоков данных
// При ошибке возвращает ноль
int _fastcall rmfAllocateBlockDesc(TRMFDATA *rmfdata, int size);

// Выделить память под массив флагов блоков
// При ошибке возвращает ноль
int _fastcall rmfAllocateBlockFlags(TRMFDATA *rmfdata, int size);

// Выделить память под битовую маску блока
// При ошибке возвращает ноль
int _fastcall rmfAllocateBlockMask(TRMFDATA *rmfdata, int size);

// Выделить память под метрику рамки
// При ошибке возвращает ноль
int _fastcall rmfAllocateBorderPoints(TRMFDATA *rmfdata, int size);

// Выделить память под метрику маски    
// При ошибке возвращает ноль
int _fastcall rmfAllocateMaskPoints(TRMFDATA *rmfdata, int size);

// Создать новый файл
// При ошибке возвращает ноль
int _fastcall rmfCreate(TRMFDATA *rmfdata, const char * name,
                        int width, int height, int nbits,
                        COLORREF * palette, double scale, double precision);
			
// Проверка корректности файла .RMF
// При ошибке возвращает ноль (код ошибки Error())
int _fastcall rmfVerify(TRMFDATA *rmfdata, long int label);

// Чтение элемента по его абсолютным индексам из буфера
int _fastcall rmfGetPoint(TRMFDATA *rmfdata, long *value, 
                          int string, int column);
			  
// Чтение double-элемента по его абсолютным индексам из буфера
int _fastcall rmfGetDoublePoint(TRMFDATA *rmfdata, 
                                double *value, int string, int column);

//  Чтение элемента  по его прямоугольным координатам (в метрах)
//  из буфера
int _fastcall rmfGetPlanePoint(TRMFDATA *rmfdata,
                               long *value, double x, double y);

//  Чтение DOUBLE-элемента  по его прямоугольным координатам
//  (в метрах) из буфера
int _fastcall rmfGetDoublePlanePoint(TRMFDATA *rmfdata,
                                     double *value, double x, double y);

//  Вычисление значения элемента методом треугольников по заданным
//  прямоугольным координатам (в метрах)
int _fastcall rmfGetPlanePointTriangle(TRMFDATA *rmfdata,
                                       double *value, double x, double y) ;

// Запись элемента по его абсолютным индексам в буфер
int _fastcall rmfPutPoint(TRMFDATA *rmfdata,
                          long value, int string, int column);

// Запись double-элемента по его абсолютным индексам в буфер
int _fastcall rmfPutDoublePoint(TRMFDATA *rmfdata,
                                double value, int string, int column);

//  Запись элемента  по его прямоугольным координатам (в метрах)
//  в буфер
int _fastcall rmfPutPlanePoint(TRMFDATA *rmfdata,
                               long value, double x, double y);

//  Запись DOUBLE-элемента  по его прямоугольным координатам
//  (в метрах) в буфер
int _fastcall rmfPutDoublePlanePoint(TRMFDATA *rmfdata,
                                     double value, double x, double y);

// Чтение элемента по его абсолютным индексам из файла.
// При ошибке возвращает ноль.
int _fastcall rmfReadPoint(TRMFDATA *rmfdata,
                           long *color, int string, int column);

// Запись элемента по его абсолютным индексам в файл
int _fastcall rmfWritePoint(TRMFDATA *rmfdata,
                            long color, int string, int column);

// Запись отрезка по абс. коорд. растра
// x1,y1 - строка,столбец начальной точки отрезка
// x2,y2 - строка,столбец конечной точки отрезка
// При ошибке возвращает ноль
int _fastcall rmfPutLine(TRMFDATA *rmfdata,
                         long color, int x1, int y1, int x2, int y2);

// Запись отрезка по прямоугольным координатам растра (в метрах)
//  x1,y1 - координаты начальной точки отрезка
//  x2,y2 - координаты конечной точки отрезка
// При ошибке возвращает ноль
int _fastcall rmfPutPlaneLine(TRMFDATA *rmfdata,
                              long value, double x1, double y1,
			      double x2, double y2);

// Запись прямоугольного участка растра
//  bits    - указатель на начало изображения битовой области
//  left    - смещение слева в элементах (выравнено на границу байта)
//  top     - смещение сверху в элементах
//  width   - ширина в элементах
//  height  - высота в элементах
//  begining    - начало изображения:
//    == FIRSTLINE - (bits - указатель на первую строку битовой области)
//    == LASTLINE  - (bits - указатель на последнюю строку битовой области,
//                           в BMP изображение хранится снизу - вверх)
//  widthinbyte - ширина в байтах
// Принцип выравнивания:
//  при rmfdata->HEADER.ElementSize == 1 (бит) - left кратно 8,
//                                  == 4 (бит) - left кратно 2
// При ошибке возвращает 0
int _fastcall rmfPutFrame(TRMFDATA *rmfdata,char* bits,
                          int left, int top,
			                    int width, int height,
                          int begining, int widthinbyte);

// Установить диапазон отображаемых элементов матрицы     
// с учетом значений высот, содержащихся в области bits
//   width  - ширина области в элементах
//   height - высота областив элементах
//   begining - начало изображения:
//     == FIRSTLINE - (bits - указатель на первую строку области)
//     == LASTLINE  - (bits - указатель на последнюю строку области)
// При ошибке возвращает 0
int _fastcall rmfSetFrameRange(TRMFDATA *rmfdata,char* bits,
			                         int width,int height,int begining);

// Запись блока из буфера в файл
int _fastcall rmfWriteBlockByIndex(TRMFDATA *rmfdata, int partindex);

// Запись блока буфера {string,column}
// При ошибке возвращает ноль.
int _fastcall rmfSaveBlock(TRMFDATA *rmfdata, int string, int column);

// Чтение блока {string,column} размером "size" в память "bits"
// Возвращает количество прочитанных байт
// При ошибке возвращает ноль
int _fastcall rmfReadBlockToMemory(TRMFDATA *rmfdata, int string,
                                   int column, char* bits, int size);

// Запись блока {string,column} размером "size" из памяти "bits"
// Возвращает количество записанных байт
// При ошибке возвращает ноль
int _fastcall rmfWriteBlock(TRMFDATA *rmfdata,
                            int string, int column, char* bits, int size);

// Чтение описателя блоков из файла в буфер
// При ошибке возвращает ноль
int _fastcall rmfReadBlockDesc(TRMFDATA *rmfdata);

// Запись описателя блоков в файл из буфера
// При ошибке возвращает ноль
int _fastcall rmfWriteBlockDesc(TRMFDATA *rmfdata);

// Чтение массива флагов блоков из файла в буфер
// При ошибке возвращает ноль
int _fastcall rmfReadBlockFlags(TRMFDATA *rmfdata);

// Запись массива флагов блоков в файл из буфера
// При ошибке возвращает ноль
int _fastcall rmfWriteBlockFlags(TRMFDATA *rmfdata);

// Чтение рамки из файла
// При ошибке возвращает ноль
int _fastcall rmfReadBorder(TRMFDATA *rmfdata);

// Запись рамки в файл из буфера
// При ошибке возвращает ноль
int _fastcall rmfWriteBorder(TRMFDATA *rmfdata);

// Чтение маски из файла           
// При ошибке возвращает ноль
int _fastcall rmfReadMask(TRMFDATA *rmfdata);

// Запись маски в файл из буфера   
// При ошибке возвращает ноль
int _fastcall rmfWriteMask(TRMFDATA *rmfdata);

// Определение положения блока
int _fastcall rmfWhereBlock(TRMFDATA *rmfdata,
                            RMFBLOCK *datablock, int string, int column);

// Поиск координат Юго-Западного блока                    
int _fastcall rmfWhereSouthWestBlock(TRMFDATA *rmfdata, RMFBLOCK * block);

// Поиск координат Юго-Западного блока в метрах           
int _fastcall rmfWhereSouthWestBlockPlane(TRMFDATA *rmfdata,
                                          double * x, double * y);

// Чтение палитры из файла
// При ошибке возвращает ноль
int _fastcall rmfReadPalette(TRMFDATA *rmfdata);

// Запись палитры в файл
// (До вызова функции необходимо установить длину палитры в
//  заголовке - PaletteLength(long))
// При ошибке возвращает ноль
int _fastcall rmfWritePalette(TRMFDATA *rmfdata);

// Чтение дополнительного описания из файла
// При ошибке возвращает ноль
int _fastcall rmfReadAddition(TRMFDATA *rmfdata);

// Запись дополнительного описания в файл
// (До вызова функции необходимо установить длину дополнительного
//  описания в  заголовке - AdditionLength(long))
// При ошибке возвращает ноль
int _fastcall rmfWriteAddition(TRMFDATA *rmfdata);

// Чтение заголовка из файла
// При ошибке возвращает ноль
int _fastcall rmfReadHeader(TRMFDATA *rmfdata);

// Запись заголовка в файл
// При ошибке возвращает ноль
int _fastcall rmfWriteHeader(TRMFDATA *rmfdata);

// Установить смещение в растре перед чтением/записью
// offset - смещение
// При обработке файлов с размером более 4GB:
//   HEADER.OffsetFactor = 8;
//   offset = offset >> HEADER.OffsetFactor;
// При ошибке возвращает ноль
int _fastcall rmfOffsetTheFile(TRMFDATA *rmfdata, long int offset, int type);

// Определение фактической длины файла
// ПОДДЕРЖКА ФАЙЛОВ С РАЗМЕРОМ БОЛЕЕ 4GB
// Возвращает длину файла в байтах
// При обработке файлов с размером более 4GB:
//  unsigned long int top64 = 0;
//  unsigned long int lowSize = rmfLongFileLength(rmfdata, (long int*)&top64);
//  if (rmfdata->HEADER.OffsetFactor != 0)
//    {  fileLength = top64 << (rmfdata->HEADER.OffsetFactor*3);
//       fileLength |= lowSize;  }
// При ошибке возвращает ноль
unsigned long int _fastcall rmfLongFileLength(TRMFDATA *rmfdata, long int* top64);

// Формирование имени добавочного файла
// при обработке изображений размером более 4GB
// Для растра *.rsw создается добавочный файл *.rsw.01
// Для матрицы *.mtw создается добавочный файл *.mtw.01
// При ошибке возвращает ноль
int _fastcall rmfNameOfAdditionalFile (TRMFDATA *rmfdata, char* name);

// Создание добавочного файла
// при обработке изображений размером более 4GB
// Для растра *.rsw создается добавочный файл *.rsw.01
// Для матрицы *.mtw создается добавочный файл *.mtw.01
// При ошибке возвращает ноль
int _fastcall rmfCreateAdditionalFile(TRMFDATA *rmfdata, const char * mame);

// Открытие добавочного файла
// при обработке изображений размером более 4GB
// Для растра *.rsw создается добавочный файл *.rsw.01
// Для матрицы *.mtw создается добавочный файл *.mtw.01
// При ошибке возвращает ноль
int _fastcall rmfOpenAdditionalFile(TRMFDATA *rmfdata, const char * name);

// Определение фактической длины файла
// Возвращает длину файла в байтах
// При обработке файлов с размером более 4GB:
// возвращает длину текущего файла в байтах в зависимости
// от rmfdata->FILEID (воможные значения FILEID0, FILEID1)
// При ошибке возвращает ноль
unsigned long _fastcall rmfFileLength(TRMFDATA *rmfdata);

// Определение теорeтической длины файла
// Использовать до создания растров
// При ошибке возвращает ноль
double _fastcall rmfCalculationFileLength(TRMFDATA *rmfdata, int width,
                                          int height, int bitpixel);

// Запросить дату обновления файла
// При ошибке возвращает ноль
int _fastcall rmfGetUpdateTime(TRMFDATA *rmfdata, FILETIME * mtime);

// Проверить наличие свободного места на диске
// При ошибке возвращает ноль
int _fastcall rmfDiskFreeSpace(TRMFDATA *rmfdata, char*name);

// Установка указателя на палитру
COLORREF* _fastcall rmfPalette(TRMFDATA *rmfdata, COLORREF* palette, int count);

// Запросить адрес блока, заданного своими индексами
// Если заданного блока нет в буфере, то он считывается из файла
// При ошибке возвращает ноль
char* _fastcall rmfGetBlockAddress(TRMFDATA *rmfdata, int string, int column);

// Запросить адрес блока, заданного своими индексами
// Если заданного блока нет в буфере, то он считывается из файла
// Захватить блок (заблокировать обновление)
// При ошибке возвращает ноль                           
char* _fastcall rmfGetBlockAddressAndLock(TRMFDATA *rmfdata, int string, int column);

// Освободить блоки (разблокировать обновление)
void  _fastcall rmfUnLockBlocks(TRMFDATA *rmfdata);     

// Запросить адрес блока, заданного своими индексами
// Если заданного блока нет в буфере, то он считывается из файла
// При отсутствии в файле - создается
// При ошибке возвращает ноль
char* _fastcall rmfGetBlockAddressAndCreate(TRMFDATA *rmfdata,
                                            int string, int column);

// Чтение блока {string,column} в текущий блок буфера
int _fastcall rmfReadBlock(TRMFDATA *rmfdata, int string, int column);

// Заполнение блока буфера значением "отсутствие информации"
int _fastcall rmfBufferBlockInit(TRMFDATA *rmfdata, int partindex);

// Заполнение блока значением "отсутствие информации"  
int _fastcall rmfFillBlock(TRMFDATA *rmfdata, int string, int column);

// Заполнение цветом части растра, ограниченной рамкой  
int _fastcall rmfFillVisiblePart(TRMFDATA *rmfdata, long int color);

// Заполнение цветом части блока растра-256, ограниченной рамкой 
int _fastcall rmfFillVisiblePartBlock256(TRMFDATA *rmfdata, long strBlock, long colBlock, long color);

// Заполнение цветом части блока растра, ограниченной рамкой 
int _fastcall rmfFillVisiblePartBlock(TRMFDATA *rmfdata, long strBlock, long colBlock, long color);

// Cохранить содержимое буфера
int _fastcall rmfSaveBuffer(TRMFDATA *rmfdata);

// Удалить рамку
int _fastcall rmfDeleteBorder(TRMFDATA *rmfdata);

// Установить рамку
int _fastcall rmfSetBorder(TRMFDATA *rmfdata, DATAEDIT* data); 

// Инициализация метрики рамки
void _fastcall rmfBorderDataInit(TRMFDATA *rmfdata);

// Запрос метрики рамки относительно блока
POLYDATAEX* _fastcall rmfGetBorderMetric(TRMFDATA *rmfdata,
                                    int string, int column);

// Запрос перевернутой по вертикали метрики рамки относительно блока
POLYDATAEX* _fastcall rmfGetBorderMetricTurn(TRMFDATA *rmfdata,  
                                    int string, int column);

// Удалить маску                                             
int _fastcall rmfDeleteMask(TRMFDATA *rmfdata);

// Установить маску                                          
int _fastcall rmfSetMask(TRMFDATA *rmfdata, DATAEDIT* data);

// Инициализация метрики маски                               
void _fastcall rmfMaskDataInit(TRMFDATA *rmfdata);

// Возврат байтового массива индексов НЕВИДИМЫХ цветов
//          (для 16 и 256-цветных растров)
//  bytes - массив индексов (1 - цвет невиден, 0 - цвет виден)
//  size  - размер массива
// Возвращает число НЕВИДИМЫХ цветов
int _fastcall rmfGetInvisibleColors(TRMFDATA *rmfdata,
                                    unsigned char* bytes, int size);

// Установка байтового массива индексов НЕВИДИМЫХ цветов
//          (для 16 и 256-цветных растров)
//  bytes - массив индексов (1 - цвет невиден, 0 - цвет виден)
//  size  - размер массива
// Возвращает число НЕВИДИМЫХ цветов
int _fastcall rmfSetInvisibleColors(TRMFDATA *rmfdata,
                                    unsigned char* bytes, int size);

// Возврат байтового массива индексов ВИДИМЫХ цветов
//          (для 16 и 256-цветных растров)
//  bytes - массив индексов (1 - цвет виден, 0 - цвет невиден)
//  size  - размер массива
// Возвращает число НЕВИДИМЫХ цветов
int _fastcall rmfGetVisibleColors(TRMFDATA *rmfdata,
                                  unsigned char* bytes, int size);

// Установка байтового массива индексов ВИДИМЫХ цветов
//          (для 16 и 256-цветных растров)
//  bytes - массив индексов (1 - цвет виден, 0 - цвет невиден)
//  size  - размер массива
// Возвращает число НЕВИДИМЫХ цветов
int _fastcall rmfSetVisibleColors(TRMFDATA *rmfdata,
                                  unsigned char* bytes, int size);

// Запись блока {string,column} размером "size" по DIB-маске "mask"
// индексом "color"
// При ошибке возвращает ноль
int _fastcall rmfPutBlockByMask(TRMFDATA *rmfdata, int string,
                                int column, char* mask, long size,
                                long width,long height,long value);

// Чтение прямоугольного участка растра
//  bits    - указатель на начало изображения битовой области
//  left    - смещение слева в элементах (выравнено на границу байта)
//  top     - смещение сверху в элементах
//  width   - ширина в элементах (выравнено на границу байта)
//  height  - высота в элементах
// Принцип выравнивания:
//  при rmfdata->rmfdata->HEADER.ElementSize == 1 (бит) - left,width кратны 8,
//                    == 4 (бит) - left,width кратны 2
// При ошибке возвращает 0
int _fastcall rmfGetFrame(TRMFDATA *rmfdata, char* bits, int left,
                          int top, int width, int height, int widthinbyte);

// Отображение прямоугольного участка исходного растра    
// в результирующем растре, расположенном в области памяти.
//   bits   - указатель на начало области памяти;
//   width  - ширина области памяти в элементах COLORREF
//            (количество столбцов результирующего растра);
//   height - высота области памяти в элементах
//            (количество строк результирующего растра);
//   strL,colL,strR,colR - координаты левого и правого элементов
//                         исходного растра, которые определяют
//                         верхний граничный отрезок прямоугольного
//                         участка.
// При ошибке возвращает ноль.
int _fastcall rmfGetFrameTurn(TRMFDATA *rmfdata,COLORREF* bits,
                              int width, int height,
                              double strL, double colL,
                              double strR, double colR);

// Установка единицы измерения (для матрицы)
unsigned long _fastcall rmfPutMeasure(TRMFDATA *rmfdata, unsigned long measure);

// Возврат единицы измерения (для матрицы)
unsigned long _fastcall rmfGetMeasure(TRMFDATA *rmfdata);

// Установить режим доступа
int _fastcall rmfAccessMode(TRMFDATA *rmfdata,UINT mode);

// Определение высоты текущего блока
long _fastcall rmfCurrentBlockHeight(TRMFDATA *rmfdata, int string);

// Определение ширины текущего блока
long _fastcall rmfCurrentBlockWidth(TRMFDATA *rmfdata, int column);

// Определение длины блока
long _fastcall rmfGetBlockLength(TRMFDATA *rmfdata, int index);

// Установка длины блока
long _fastcall rmfPutBlockLength(TRMFDATA *rmfdata, int index, long length);

// Определение размера текущего блока (байт)
long _fastcall rmfCurrentBlockSize(TRMFDATA *rmfdata, int string, int column);

// Определение размера блока (байт)
long _fastcall rmfBlockSize(TRMFDATA *rmfdata);

// Определение смещения на блок в файле
unsigned long _fastcall rmfGetBlockOffset(TRMFDATA *rmfdata, int index);

// Установка смещения на блок в файле
unsigned long _fastcall rmfPutBlockOffset(TRMFDATA *rmfdata,
                                          int index, unsigned long offset);
// Возврат флага отображения блока
int _fastcall rmfGetBlockVisible(TRMFDATA *rmfdata, int index);

// Установка флага отображения блока
int _fastcall rmfPutBlockVisible(TRMFDATA *rmfdata, int index, int view);

// Возврат флага отображения по рамке
int _fastcall rmfGetShowByBorder(TRMFDATA *rmfdata);

// Установка флага отображения по рамке
int _fastcall rmfPutShowByBorder(TRMFDATA *rmfdata, int value);

// Возврат флага отображения по маске          
int _fastcall rmfGetShowByMask(TRMFDATA *rmfdata);

// Установка флага отображения по маске        
int _fastcall rmfPutShowByMask(TRMFDATA *rmfdata, int value);

// Возврат количества блоков
long _fastcall rmfBlockCount(TRMFDATA *rmfdata);

// Возврат количества строк блоков
long _fastcall rmfBlockStringCount(TRMFDATA *rmfdata);

// Возврат количества колонок блоков
long _fastcall rmfBlockColumnCount(TRMFDATA *rmfdata);

// Возврат/Установка высоты блока (строк)
long _fastcall rmfGetBlockHeight(TRMFDATA *rmfdata);
long _fastcall rmfPutBlockHeight(TRMFDATA *rmfdata, long height);

// Возврат/Установка ширины блока (столбцов)
long _fastcall rmfGetBlockWidth(TRMFDATA *rmfdata);
long _fastcall rmfPutBlockWidth(TRMFDATA *rmfdata, long width);

// Возврат/Установка минимального значения элемента(для матрицы)
double _fastcall rmfGetMinimum(TRMFDATA *rmfdata);
double _fastcall rmfPutMinimum(TRMFDATA *rmfdata, double minimum);

// Возврат/Установка максимального значения элемента(для матрицы)
double _fastcall rmfGetMaximum(TRMFDATA *rmfdata);
double _fastcall rmfPutMaximum(TRMFDATA *rmfdata, double maximum);

// Возврат/Установка количества элементов на метр
double _fastcall rmfGetPrecision(TRMFDATA *rmfdata);
double _fastcall rmfPutPrecision(TRMFDATA *rmfdata, double precision);

// Возврат/Установка масштаба
double _fastcall rmfGetScale(TRMFDATA *rmfdata);
double _fastcall rmfPutScale(TRMFDATA *rmfdata, double scale);

// Возврат/Установка типа карты
long _fastcall rmfGetMapType(TRMFDATA *rmfdata);
long _fastcall rmfPutMapType(TRMFDATA *rmfdata, long maptype);

// Возврат/Установка типа проекции
long _fastcall rmfGetProjectionType(TRMFDATA *rmfdata);
long _fastcall rmfPutProjectionType(TRMFDATA *rmfdata, long projectiontype);

// Возврат/Установка количества метров на элемент
double _fastcall rmfGetMeterInElement(TRMFDATA *rmfdata);
double _fastcall rmfPutMeterInElement(TRMFDATA *rmfdata, double meterinelement);

// Установка проекции исходного материала и справочных данных по
// проекции исходного материала
long _fastcall rmfSetProjection(TRMFDATA *rmfdata);  

// Запрос проекции исходного материала             
// Если флаг возможности расчета геодезических координат равен нулю,
// то нет смысла вызывать ф-ю
// по данным структуры MAPREGISTEREX
long _fastcall rmfGetRegister(TRMFDATA *rmfdata,MAPREGISTEREX* mapregister);
// Установка проекции исходного материала и             
// флага возможности расчета геодезических координат
// по данным структуры MAPREGISTEREX
long _fastcall rmfSetRegister(TRMFDATA *rmfdata,MAPREGISTEREX* mapregister);

// Возврат/Установка точки привязки в районе в метрах
double _fastcall rmfGetLocationX(TRMFDATA *rmfdata);
double _fastcall rmfPutLocationX(TRMFDATA *rmfdata, double location);

double _fastcall rmfGetLocationY(TRMFDATA *rmfdata);
double _fastcall rmfPutLocationY(TRMFDATA *rmfdata, double location);

// Возврат/Установка первой главной параллели
double _fastcall rmfGetFirstMainParallel(TRMFDATA *rmfdata);
double _fastcall rmfPutFirstMainParallel(TRMFDATA *rmfdata, double parallel);

// Возврат/Установка второй главной параллели
double _fastcall rmfGetSecondMainParallel(TRMFDATA *rmfdata);
double _fastcall rmfPutSecondMainParallel(TRMFDATA *rmfdata, double parallel);

// Возврат/Установка параллели главной точки
double _fastcall rmfGetMainPointParallel(TRMFDATA *rmfdata);
double _fastcall rmfPutMainPointParallel(TRMFDATA *rmfdata, double parallel);

// Возврат/Установка осевого меридиана
double _fastcall rmfGetAxisMeridian(TRMFDATA *rmfdata);
double _fastcall rmfPutAxisMeridian(TRMFDATA *rmfdata, double meridian);

// Возврат/Установка Широты полюса проекции                 
double _fastcall rmfGetPoleLatitude(TRMFDATA *rmfdata);
double _fastcall rmfPutPoleLatitude(TRMFDATA *rmfdata, double polelatitude);

// Возврат/Установка Долготы полюса проекции                
double _fastcall rmfGetPoleLongitude(TRMFDATA *rmfdata);
double _fastcall rmfPutPoleLongitude(TRMFDATA *rmfdata, double polelongitude);

// Возврат/Установка Вида эллипсоида                        
long _fastcall rmfGetEllipsoideKind(TRMFDATA *rmfdata);
long _fastcall rmfPutEllipsoideKind(TRMFDATA *rmfdata, long ellipsoidekind);

// Возврат/Установка Системы высот                          
long _fastcall rmfGetHeightSystem(TRMFDATA *rmfdata);
long _fastcall rmfPutHeightSystem(TRMFDATA *rmfdata, long heightsystem);

// Возврат/Установка Системы координат                      
long _fastcall rmfGetCoordinateSystem(TRMFDATA *rmfdata);
long _fastcall rmfPutCoordinateSystem(TRMFDATA *rmfdata, long coordinatesystem);

// Возврат/Установка Номера зоны                            
long _fastcall rmfGetZoneNumber(TRMFDATA *rmfdata);
long _fastcall rmfPutZoneNumber(TRMFDATA *rmfdata, long zonenumber);

// Возврат/Установка высоты р-м изображения
long _fastcall rmfGetHeight(TRMFDATA *rmfdata);
long _fastcall rmfPutHeight(TRMFDATA *rmfdata, long height);

// Возврат/Установка ширины р-м изображения
long _fastcall rmfGetWidth(TRMFDATA *rmfdata);
long _fastcall rmfPutWidth(TRMFDATA *rmfdata, long width);

// Возврат/Установка значения псевдокода(для матрицы)
double _fastcall rmfGetPseudoCode(TRMFDATA *rmfdata);
double _fastcall rmfPutPseudoCode(TRMFDATA *rmfdata, double pseudocode);

class _DLLCLASS TRmf : public TRMFDATA
{
protected:

  // Конструкторы класса
  TRmf(char * name, int width, int height, int bit,
       COLORREF* palette = 0, double scale = 0,
       double precision = 0);

public :

 // Единицы измерения
 enum UNITS  { m = rmfm, dm = rmfdm, cm = rmfcm, mm = rmfmm };

 // Коды возврата функций
 enum RETCODE { OKEY = RMFOKEY };

 enum { FIRSTLINE = RMFFIRSTLINE, LASTLINE = RMFLASTLINE };

//-----------------------------------------------------------------
// Конструктор по умолчанию
//-----------------------------------------------------------------

  TRmf();
  TRmf(char* name, RMF* rmf, RMFADDITION* rmfaddition, COLORREF* palette = 0); 

 ~TRmf();


//*****************************************************************
//  Член-функции класса TRmf
//*****************************************************************

  // Возврат режима доступа к файлу
  int AccessMode() { return ACCESSMODE; }

  // Возврат значения флага "доступно для редактирования"
  int IsRmfEdit() { return (AccessMode() & GENERIC_WRITE); }

  // Установка флага коректировки палитры
  int IsPalette(int set) { return (ISPALETTE = set); }

  // Установка флага коректировки дополнительного описания растра
  int IsAddition(int set) { return (ISADDITION = set); }

  // Сохранить данные в файлe
  int Save(int force);

  // Установка/Возврат рамки
  int SetBorder(TDataEdit* data);
  TDataEdit* GetBorder() { return &BORDER; }

  // Удалить рамку
  int DeleteBorder();

  // Установка/Возврат маски изображения       
  int SetMask(TDataEdit* data);                

  TDataEdit* GetMask() { return &MASK; }       

  // Удалить маску                             
  int DeleteMask();


  // Возврат адреса битовой маски блока
  char* GetMaskAddress() { return BLOCKMASKBUFF; }

  // Возврат адреса массива флагов видимости блоков
  char* BlockFlags() { return BLOCKFLAGSBUFF; }

  // Возврат/Установка ширины маски в байтах
  int BlockMaskWidth() { return BLOCKMASKWIDTH; }
  int BlockMaskWidth(int width) { return BLOCKMASKWIDTH = width; }

  // Закрытие файла
  void Close() { Close(0); }

//*****************************************************************
//  Функции для работы с буфером
//*****************************************************************

protected :

  // Размещение буфера и битовую маску блока
  int AllocateBuffer(int count = 8);

  // Выделить память под битовую маску блока
  int AllocateBlockMask(int size);

  // Освобождение буфера
  void FreeBuffer();

  // Сохранение буфера
  int SaveBuffer();

  // Очистка буфера
  void ClearBuffer();

  // Возврат указателя на текущий блок буфера
  char* Bits() { return PART[CURRENT].Address; }

  // Определение/установка загрязненности текущего блока буфера
  int IsDirty()        { return PART[CURRENT].Isdirty; }
  int IsDirty(int set) { return PART[CURRENT].Isdirty = set; }

  // Заполнение блока буфера значением "отсутствие информации"
  int BufferBlockInit(int partindex);

  // Инициализация метрики рамки
  void BorderDataInit();

  // Инициализация метрики маски изображения
  void MaskDataInit();  



public:

  // Возврат адресa заголовка
  RMF* GetHeader() { return &HEADER; }

  // Возврат адресa заголовка      
  // Дополнительное описание растра (матрицы)
  RMFADDITION* GetAdditionHeader() {return &ADDITION;}

  // Cмещение на заголовок
  unsigned long HeaderOffset(){ return HEADEROFFSET;}   

  // Запрос адресa блока, заданного своими индексами
  // Если заданного блока нет в буфере, то он считывается из файла
  // При ошибке возвращает ноль
  char* GetBlockAddress(int string, int column);

  // Запросить адрес блока, заданного своими индексами
  // Если заданного блока нет в буфере, то он считывается из файла
  // При отсутствии в файле - создается
  // При ошибке возвращает ноль
  char* GetBlockAddressAndCreate(int string, int column);

  // Определение положения блока
  int WhereBlock(RMFBLOCK& block, int string, int column);

  // Поиск координат Юго-Западного блока в метрах           
  int WhereSouthWestBlockPlane(double * x, double * y);

  // Начальная колонка блока
  int BlockBeginColumn(int column) { return column*BlockWidth(); }

  // Начальная строка блока
  int BlockBeginString(int string) { return string*BlockHeight(); }

  // Возврат/Установка смещения на блок в файле
  unsigned long BlockOffset(int index);
  unsigned long BlockOffset(int index, unsigned long offset);

  // Возврат/Установка длины блока
  long BlockLength(int index);
  long BlockLength(int index, long length);

  // Возврат/Установка флага видимости блока
  int BlockVisible(int index);
  int BlockVisible(int index, int view);

  // Запрос метрики рамки относительно блока
  POLYDATAEX* GetBorderMetric(int string, int column);

  // Запрос перевернутой по вертикали метрики рамки относительно блока
  POLYDATAEX* GetBorderMetricTurn(int string, int column);  
  
//*****************************************************************
//  Функции компрессии и декомпрессии
//*****************************************************************

  // Компрессия блока LZW
  int Compress(const char* in,  int sizein,
                     char* out, int sizeout);

  // Декомпрессия блока LZW
  int Decompress(const char* in,  int sizein,
                       char* out, int sizeout);

  // Компрессия блока 32-битной матрицы
  // (Значения высот ниже минимальной кодируются
  //  псевдокодами без сохранения значения)
  int CompressMtr(const char* in,  int sizein,
                        char* out, int sizeout, long minimum);

  // Декомпрессия блока 32-битной матрицы
  int DecompressMtr(const char* in,  int sizein,
                          char* out, int sizeout);



//*****************************************************************
//  Функции для работы с файлом :
//*****************************************************************

protected:

  // Установить режим доступа
  int AccessMode(UINT mode)
 	{
    ACCESSMODE = (mode & (GENERIC_READ|GENERIC_WRITE));
    if (ACCESSMODE == 0) ACCESSMODE = GENERIC_READ|GENERIC_WRITE;
    return ACCESSMODE;
  }

  // Создать новый файл
  // При ошибке возвращает ноль
  int Create(char * name, int width, int height, int nbits,
             COLORREF * palette,
             double scale = 0, double precision = 0);

public:

  int Create(char* name, RMF* rmf, RMFADDITION* rmfaddition, COLORREF* palette = 0); 

protected:

  // Закрытие файла
  // force - признак освобождения памяти
  void Close(int force);

  // Открытие файла
  // При ошибке возвращает ноль
  int Open(const char * name, int mode = 0);

  // Возврат/Установка режима совместного доступа к файлу
  int ShareMode() { return SHAREMODE; }
  int ShareMode(UINT shmode)
  {
    SHAREMODE = shmode;
    return SHAREMODE;
  }

protected:

  // Сбросить значения всех переменных класса
  void ClearAll();

  // Выделить память под описатели блоков данных
  // При ошибке возвращает ноль
  int AllocateBlockDesc(int size);
   BLOCKDESC* BlockDesc() { return BLOCKDESCBUFF; }  // Возврат адреса

  // Выделить память под массив флагов блоков
  // При ошибке возвращает ноль
  int AllocateBlockFlags(int size);

  // Выделить память под метрику рамки
  // При ошибке возвращает ноль
  int AllocateBorderPoints(int size);
        char* BorderPoints() { return BORDERPOINTSBUFF; }

  // Выделить память под метрику
  // При ошибке возвращает ноль
  int AllocateMaskPoints(int size);                        
        char* MaskPoints() { return MASKPOINTSBUFF; }      

  // Возврат/Установка флага корpектировки описателя блоков
  int IsBlockDesc() { return ISBLOCKDESC; }
  int IsBlockDesc(int set) { return (ISBLOCKDESC = set); }

  // Возврат/Установка флага корpектировки массива флагов блоков
  int IsBlockFlags() { return ISBLOCKFLAGS; }
  int IsBlockFlags(int set) { return (ISBLOCKFLAGS = set); }

  // Возврат/Установка значения флага корpектировки рамки
  int IsBorder() { return ISBORDER; }
  int IsBorder(int set) { return (ISBORDER = set); }

  // Возврат/Установка значения флага корpектировки
  int IsMask() { return ISMASK; }                          
  int IsMask(int set) { return (ISMASK = set); }           

  // Возврат значения флага корpектировки палитры
  int IsPalette() { return ISPALETTE; }

  // Возврат значения флага корpектировки дополнительного описания растра
  int IsAddition() { return ISADDITION; }

  // Возврат/Установка значения флага корpектировки заголовка
  int IsHeader() { return ISHEADER; }
  int IsHeader(int set) { return (ISHEADER = set); }

  // Возврат/Установка флага ISCREATE
  int IsCreate() { return ISCREATE; }
  int IsCreate(int set) { return ISCREATE = set; }

  // Проверка корректности файла .RMF
  // При ошибке возвращает ноль (код ошибки Error())
  int Verify(long int label);

  // Создание файла
  // При ошибке возвращает ноль
  int Create(const char * name);

public:

  // Возврат/Установка флага ошибки
  long Error() { return ISERROR; }
  long Error(long error) { return (ISERROR = error); }

  // Чтение элемента по абсолютным индексам
  // При ошибке возвращает ноль
  int GetPoint(long& value, int string, int column);
  int GetPoint(double& value, int string, int column);

  // Запись элемента по абсолютным индексам
  // При ошибке возвращает ноль
  int PutPoint(long value, int string, int column);
  int PutPoint(double value, int string, int column);

  // Чтение элемента по его прямоугольным координатам
  // (в метрах) из буфера
  int GetPlanePoint(long&   value, double x, double y);
  int GetPlanePoint(double& value, double x, double y);

  // Вычисление значения высоты (в метрах) методом треугольников
  // по заданным абсолютным индексам
  int GetHeightTriangle(double& height,double Str,double Col);
  int GetHeightTriangle2(double& height,double Str,double Col);

  // Вычисление значения элемента методом треугольников по заданным
  // прямоугольным координатам (в метрах)
  int GetPlanePointTriangle(double& value, double x, double y);

  // Запись элемента  по его прямоугольным координатам
  // (в метрах) в буфер
  int PutPlanePoint(long   value, double x, double y);
  int PutPlanePoint(double value, double x, double y);

  // Чтение элемента по абсолютным индексам из файла
  // При ошибке возвращает ноль
  int ReadPoint(long& value, int string, int column);

  // Запись элемента по абсолютным индексам в файл
  // При ошибке возвращает ноль
  int WritePoint(long value, int string, int column);

  // Запись отрезка по абс. коорд. растра
  //  x1,y1 - строка,столбец начальной точки отрезка
  //  x2,y2 - строка,столбец конечной точки отрезка
  // При ошибке возвращает ноль
  int PutLine(long value, int x1, int y1, int x2, int y2);

  // Запись отрезка по прямоугольным координатам растра (в метрах)
  //  x1,y1 - координаты начальной точки отрезка
  //  x2,y2 - координаты конечной точки отрезка
  // При ошибке возвращает ноль
  int PutPlaneLine(long value, double x1, double y1, double x2, double y2);
  int PutPlaneLine(double value, double x1, double y1, double x2, double y2);

  // Чтение прямоугольного участка растра
  //  bits    - указатель на начало изображения битовой области
  //  left    - смещение слева в элементах (выравнено на границу байта)
  //  top     - смещение сверху в элементах
  //  width   - ширина в элементах (выравнено на границу байта)
  //  height  - высота в элементах
  // Принцип выравнивания:
  //  при ElementSize() == 1 (бит) - left,width кратны 8,
  //                    == 4 (бит) - left,width кратны 2
  // При ошибке возвращает 0
  int GetFrame(char* bits, int left, int top, int width, int height,
               int widthinbyte = 0);



  // Запись прямоугольного участка растра
  //  bits    - указатель на начало изображения битовой области
  //  left    - смещение слева в элементах (выравнено на границу байта)
  //  top     - смещение сверху в элементах
  //  width   - ширина в элементах (выравнено на границу байта)
  //  height  - высота в элементах
  //  begining  - начало изображения:
  //    == FIRSTLINE - (bits - указатель на первую строку битовой области)
  //    == LASTLINE  - (bits - указатель на послелнюю строку битовой области,
  //                           в BMP изображение хранится снизу - вверх)
  // Принцип выравнивания:
  //  при ElementSize() == 1 (бит) - left,width кратны 8,
  //                    == 4 (бит) - left,width кратны 2
  // При ошибке возвращает 0
  int PutFrame(char* bits, int left, int top, int width, int height,
               int begining = RMFFIRSTLINE, int widthinbyte = 0);


 // Отображение прямоугольного участка исходного растра    
 // в результирующем растре, расположенном в области памяти.
 //   bits   - указатель на начало области памяти;
 //   width  - ширина области памяти в элементах COLORREF
 //            (количество столбцов результирующего растра);
 //   height - высота области памяти в элементах
 //            (количество строк результирующего растра);
 //   strL,colL,strR,colR - координаты левого и правого элементов
 //                         исходного растра, которые определяют
 //                         верхний граничный отрезок прямоугольного
 //                         участка.
 // При ошибке возвращает ноль.
 int GetFrameTurn(COLORREF* bits, int width, int height,
                  double strL, double colL, double strR, double colR);

                  
  // Запись блока {string,column} размером "size" по DID-маске "mask"
  // индексом "color"
  // При ошибке возвращает ноль
  int PutBlockByMask(int string, int column, char* mask, long size,
                         long width,long height,long value);

  // Запросить дату обновления файла
  // При ошибке возвращает ноль
  int GetUpdateTime(FILETIME * mtime);

  // Определение активности р-м. изображения
  int IsActive() { return ((int)FILEID); }

  // Возврат/Установка полного имени файла
  char* Name() { return NAME; }
  char* Name(char* name)
  {
    if (name == 0) return 0;
    return strncpy(NAME, name, sizeof(NAME));
  }

  // Возврат указателя на палитру
  COLORREF* Palette() { return PALETTE; }

  // Возврат указателя на дополнительное описание растра
  RMFADDITION* Addition() { return &ADDITION; }

  // Установка новой палитры
  //  count - число элементов во входной палитре
  COLORREF* Palette(COLORREF* palette, int count);

  // Запросить/Установить яркость палитры (от - 16 до 16)     
  // При ошибке возвращает 0
  int GetBright()  {return HEADER.Bright;}
  int SetBright(int bright)
     { IsHeader(TRUE);  return (HEADER.Bright = (BYTE)bright); }

  // Запросить/Установить контрастность палитры (от -16 до 16) 
  // При ошибке возвращает 0
  int GetContrast() {return HEADER.Contrast;}
  int SetContrast(int contrast)
     { IsHeader(TRUE);  return (HEADER.Contrast = (BYTE)contrast); }

  // Запросить/Установить гамма-функцию (от -16 до 16)       
  // При ошибке возвращает 0
  int GetGamma(){return HEADER.Gamma;}
  int SetGamma(int gamma)
     { IsHeader(TRUE);  return (HEADER.Gamma = (BYTE)gamma); }

//*****************************************************************
//  Функции установки и определения полей заголовка
//*****************************************************************

  // Возврат/Установка идентификатора файла
  unsigned long Label() { return HEADER.Label; }
  unsigned long Label(unsigned long label)
  {
    IsHeader(TRUE);
    return HEADER.Label=label;
  }

  // Возврат/Установка версии структуры
  unsigned long Version() { return (HEADER.Version); }
  unsigned long Version(unsigned long version)
  {
    IsHeader(TRUE);
    return HEADER.Version=version;
  }

  // Возврат/Установка длины файла
  unsigned long Length() { return (HEADER.Length); }
  unsigned long Length(unsigned long length)
  {
    IsHeader(TRUE);
    return HEADER.Length=length;
  }

  // Возврат/Установка смещения на заголовок уменьшенной копии
  unsigned long DuplicateOffset() { return (HEADER.DuplicateOffset); }
  unsigned long DuplicateOffset(unsigned long offset)
  {
    IsHeader(TRUE);
    return HEADER.DuplicateOffset=offset;
  }

  // Возврат/Установка пользовательского идентификатора
  unsigned long UserLabel() { return (HEADER.UserLabel); }
  unsigned long UserLabel(unsigned long userlabel)
  {
    IsHeader(TRUE);
    return HEADER.UserLabel=userlabel;
  }

  // Возврат/Установка условного имени
  char* UserName() { return (HEADER.UserName); }
  char* UserName(char* name)
  {
    if (name == 0) return 0;
    IsHeader(1);
    strncpy(HEADER.UserName, name, sizeof(HEADER.UserName));
    return (HEADER.UserName);
  }

  // Возврат/Установка размера элемента (бит)
  long ElementSize() { return (HEADER.ElementSize); }
  long ElementSize(long size)
  {
    IsHeader(TRUE);
    return HEADER.ElementSize=size;
  }

  // Возврат количества цветов
  long ColorCount() { return (0x01<<HEADER.ElementSize); }

  // Возврат/Установка высоты р-м изображения
  long Height() { return (HEADER.Height); }
  long Height(long height)
  {
    IsHeader(TRUE);
    return HEADER.Height=height;
  }

  // Возврат/Установка ширины р-м изображения
  long Width() { return (HEADER.Width); }
  long Width(long width)
  {
    IsHeader(TRUE);
    return HEADER.Width=width;
  }

  // Возврат/Установка количества столбцов блоков (блоков в строке)
  long BlockColumnCount() { return (HEADER.BlockColumnCount); }
  long BlockColumnCount(long column)
  {
    IsHeader(TRUE);
    return HEADER.BlockColumnCount=column;
  }

  // Возврат/Установка количества строк блоков (блоков в столбце)
  long BlockStringCount() { return (HEADER.BlockStringCount); }
  long BlockStringCount(long string)
  {
    IsHeader(TRUE);
    return HEADER.BlockStringCount=string;
  }

  // Возврат количества блоков
  long BlockCount() { return HEADER.BlockColumnCount  *
                             HEADER.BlockStringCount; }

  // Возврат/Установка высоты блока(строк)
  long BlockHeight() { return (HEADER.BlockHeight); }
  long BlockHeight(long height)
  {
    IsHeader(TRUE);
    return HEADER.BlockHeight=height;
  }

  // Возврат/Установка ширины блока(столбцов)
  long BlockWidth() { return (HEADER.BlockWidth); }
  long BlockWidth(long width)
  {
    IsHeader(TRUE);
    return HEADER.BlockWidth=width;
  }

  // Возврат/Установка высоты усеченого блока
  long CutBlockHeight() { return (HEADER.TruncBlockHeight); }
  long CutBlockHeight(long height)
  {
    IsHeader(TRUE);
    return HEADER.TruncBlockHeight=height;
  }

  // Возврат/Установка ширины усеченого блока
  long CutBlockWidth() { return (HEADER.TruncBlockWidth); }
  long CutBlockWidth(long width)
  {
    IsHeader(TRUE);
    return HEADER.TruncBlockWidth=width;
  }

  // Определение высоты текущего блока
  long CurrentBlockHeight(int string)
  {
    if (string == BlockStringCount()-1) return CutBlockHeight();
                                   else return BlockHeight();
  }

  // Определение ширины текущего блока
  long CurrentBlockWidth(int column)
  {
    if (column == BlockColumnCount()-1) return CutBlockWidth();
                                   else return BlockWidth();
  }

  // Определение размера блока (байт)
  long BlockSize() { return (HEADER.BlockHeight *
                             HEADER.BlockWidth  *
                             HEADER.ElementSize / 8); }

  // Определение размера текущего блока (байт)
  long CurrentBlockSize(int string, int column)
  {
    return (CurrentBlockHeight(string) *
            CurrentBlockWidth(column) * HEADER.ElementSize / 8);
  }

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

  // Возврат/Установка флага отображения по рамке
  int ShowByBorder();
  int ShowByBorder(int value);

  // Возврат/Установка смещения на запись "" в файле             
  unsigned long MaskOffset() { return (ADDITION.MaskOffset); }   
  unsigned long MaskOffset(unsigned long maskoffset)           
  {
    IsHeader(TRUE);
    IsAddition(TRUE);
    IsMask(TRUE);
    return ADDITION.MaskOffset=maskoffset;
  }

  // Возврат/Установка длины записи ""                            
  long MaskLength() { return (ADDITION.MaskLength); }             
  long MaskLength(long masklength)                              
  {
    IsHeader(TRUE);
    IsAddition(TRUE);
    IsMask(TRUE);
    return ADDITION.MaskLength = masklength;
  }

  // Возврат/Установка флага отображения по                       
  int ShowByMask();
  int ShowByMask(int value);

  // Возврат/Установка смещения на палитру в файле
  unsigned long PaletteOffset() { return (HEADER.PaletteOffset); }
  unsigned long PaletteOffset(unsigned long paletteoffset)
  {
    IsHeader(TRUE);
    IsPalette(TRUE);
    return HEADER.PaletteOffset = paletteoffset;
  }

  // Возврат/Установка длины палитры
  long PaletteLength() { return (HEADER.PaletteLength); }
  long PaletteLength(long palettelength)
  {
    IsHeader(TRUE);
    IsPalette(TRUE);
    return HEADER.PaletteLength = palettelength;
  }

  // Возврат/Установка смещения на запись "дополнительноe описаниe растра" в файле
  unsigned long AdditionOffset() { return (HEADER.AdditionOffset); }
  unsigned long AdditionOffset(unsigned long additionoffset)
  {
    IsHeader(TRUE);
    IsAddition(TRUE);
    return HEADER.AdditionOffset = additionoffset;
  }

  // Возврат/Установка длины записи "дополнительноe описаниe растра"
  long AdditionLength() { return (HEADER.AdditionLength); }
  long AdditionLength(long addlength)
  {
    IsHeader(TRUE);
    IsAddition(TRUE);
    return HEADER.AdditionLength = addlength;
  }

  // Возврат/Установка смещения на запись "описатель блоков" в файле
  unsigned long BlockDescOffset() { return (HEADER.BlockDescOffset); }
  unsigned long BlockDescOffset(unsigned long blockdescoffset)
  {
    IsHeader(TRUE);
    IsBlockDesc(TRUE);
    return HEADER.BlockDescOffset = blockdescoffset;
  }

  // Возврат/Установка длины записи "описатель блоков"
  long BlockDescLength() { return (HEADER.BlockDescLength); }
  long BlockDescLength(long blockdesclength)
  {
    IsHeader(TRUE);
    IsBlockDesc(TRUE);
    return HEADER.BlockDescLength = blockdesclength;
  }

  // Возврат/Установка смещения на запись "массива флагов блоков" в файле
  unsigned long BlockFlagsOffset() { return (HEADER.BlockFlagsOffset); }
  unsigned long BlockFlagsOffset(unsigned long blockflagsoffset)
  {
    IsHeader(TRUE);
    IsBlockFlags(TRUE);
    return HEADER.BlockFlagsOffset = blockflagsoffset;
  }

  // Возврат/Установка длины записи "массива флагов блоков"
  long BlockFlagsLength() { return (HEADER.BlockFlagsLength); }
  long BlockFlagsLength(long blockflagslength)
  {
    IsHeader(TRUE);
    IsBlockFlags(TRUE);
    return HEADER.BlockFlagsLength = blockflagslength;
  }

  // Возврат/Установка смещения на алгоритмы сжатия в файле
  unsigned long CompressDataOffset() { return (HEADER.CompressDataOffset); }
  unsigned long CompressDataOffset(unsigned long offset)
  {
    IsHeader(TRUE);
    return HEADER.CompressDataOffset = offset;
  }

  // Возврат/Установка количества алгоритмов сжатия
  long CompressDataCount() { return HEADER.CompressDataCount; }
  long CompressDataCount(long count)
  {
    IsHeader(TRUE);
    return HEADER.CompressDataCount = count;
  }

  // Возврат/Установка длины записи "алгоритмы сжатия"
  long CompressDataLength() { return HEADER.CompressDataLength; }
  long CompressDataLength(long length)
  {
    IsHeader(TRUE);
    return HEADER.CompressDataLength = length;
  }

  // Возврат/Установка типа карты
  long MapType() { return HEADER.MapType; }
  long MapType(long maptype)
  {
    IsHeader(TRUE);
    return HEADER.MapType = maptype;
  }

  // Возврат/Установка типа проекции
  long ProjectionType() { return HEADER.ProjectionType; }
  long ProjectionType(long projectiontype)
  {
    IsHeader(TRUE);
    return HEADER.ProjectionType = projectiontype;
  }

  // Возврат/Установка Вида эллипсоида                      
  long EllipsoideKind();
  long EllipsoideKind(long ellipsoidekind);

  // Возврат/Установка Системы высот                        
  long HeightSystem();
  long HeightSystem(long heightsystem);

  // Возврат/Установка Системы координат                    
  long CoordinateSystem();
  long CoordinateSystem(long coordinatesystem);

  // Возврат/Установка Номера зоны                           
  long ZoneNumber();
  long ZoneNumber(long zonenumber);

  // Установка проекции исходного материала и
  // флага возможности расчета геодезических координат
  // по данным заголовка rmfdata->HEADER
  long SetProjection();  

  // Запрос проекции исходного материала             
  // Если флаг возможности расчета геодезических координат равен нулю,
  // то нет смысла вызывать ф-ю
  // по данным структуры MAPREGISTEREX
  long GetRegister(MAPREGISTEREX* mapregister);  
  // Установка проекции исходного материала и
  // флага возможности расчета геодезических координат
  // по данным структуры MAPREGISTEREX
  long SetRegister(MAPREGISTEREX* mapregister);  

  // Возврат/Установка масштаба
  double Scale() { return max(1.0, HEADER.Scale); }
  double Scale(double scale)
  {
    IsHeader(TRUE);
    return HEADER.Scale = max(1.0, scale);
  }

  // Возврат/Установка количества элементов на метр
  double Precision() { return max(1.0, HEADER.Precision); }
  double Precision(double precision)
  {
    IsHeader(TRUE);
    return HEADER.Precision = max(1.0, precision);
  }

  // Возврат/Установка количества метров на элемент
  double MeterInElement() { return (HEADER.MeterInElement); }
  double MeterInElement(double meterinelement)
  {
    IsHeader(TRUE);
    return (HEADER.MeterInElement=meterinelement);
  }

  // Определение точки привязки в районе в метрах
  // (для RSW версии <= 0x0101 - в элементах)
  double LocationX() { return HEADER.LocationX; }
  double LocationY() { return HEADER.LocationY; }

  // Установка точки привязки изображения в районе в метрах
  double LocationX(double location)
  {
    IsHeader(TRUE);
    HEADER.Flag_Location = 1;
    return HEADER.LocationX=location;
  }

  double LocationY(double location)
  {
    IsHeader(TRUE);
    HEADER.Flag_Location = 1;
    return HEADER.LocationY=location;
  }

  // Прямоугольные координаты углов в метрах
  // (для RSW версии <= 0x0101 - НЕКОРРЕКТНЫ !!!)
  double X1() { return HEADER.LocationX; }
  double Y1() { return HEADER.LocationY; }
  double X2() { return HEADER.LocationX + (double)(HEADER.Height) *
                       HEADER.MeterInElement; }
  double Y2() { return HEADER.LocationY + (double)(HEADER.Width) *
                       HEADER.MeterInElement; }

  // Возврат/Установка первой главной параллели
  double FirstMainParallel() { return (HEADER.FirstMainParallel); }
  double FirstMainParallel(double mainparallel)
  {
    IsHeader(TRUE);
    return (HEADER.FirstMainParallel=mainparallel);
  }

  // Возврат/Установка второй главной параллели
  double SecondMainParallel() { return (HEADER.SecondMainParallel); }
  double SecondMainParallel(double mainparallel)
  {
    IsHeader(TRUE);
    return (HEADER.SecondMainParallel=mainparallel);
  }

  // Возврат/Установка осевого меридиана
  double AxisMeridian() { return (HEADER.AxisMeridian); }
  double AxisMeridian(double meridian)
  {
    IsHeader(TRUE);
    return (HEADER.AxisMeridian=meridian);
  }

  // Возврат/Установка параллели главной точки
  double MainPointParallel() { return (HEADER.MainPointParallel); }
  double MainPointParallel(double mainpoint)
  {
    IsHeader(TRUE);
    return (HEADER.MainPointParallel=mainpoint);
  }

  // Возврат/Установка Широты полюса проекции                 
  double PoleLatitude() { return (ADDITION.PoleLatitude); }
  double PoleLatitude(double polelatitude)
  {
    // Установка флага коректировки дополнительного описания растра
    IsAddition(TRUE);
    return (ADDITION.PoleLatitude=polelatitude);
  }

  // Возврат/Установка Долготы полюса проекции                 
  double PoleLongitude() { return (ADDITION.PoleLongitude); }
  double PoleLongitude(double polelongitude)
  {
    IsAddition(TRUE);
    return (ADDITION.PoleLongitude=polelongitude);
  }

  // Возврат/Установка номера алгоритма сжатия блоков
  int CompressNumber() { return (HEADER.CompressNumber); }
  int CompressNumber(int number)
  {
    IsHeader(TRUE);
    return (HEADER.CompressNumber = (unsigned char)number);
  }

  // Возврат/Установка типа маски (0 - маска отсутствует)
  int MaskType() {return HEADER.MaskType;}
  int MaskType(int type)
  {
    IsHeader(TRUE);
    return (HEADER.MaskType = (unsigned char)type);
  }

  // Возврат/Установка шага маски
  int MaskStep() {return HEADER.MaskStep;}
  int MaskStep(int step)
  {
    IsHeader(TRUE);
    return (HEADER.MaskStep = (unsigned char)step);
  }

  // Установка типа и шага маски
  void SetMask(int type, int step)
  {
    IsHeader(TRUE);
    HEADER.MaskType = (unsigned char)type;
    HEADER.MaskStep = (unsigned char)step;
  }

  // Возврат/Установка БАЙТОВОГО массива индексов НЕВИДИМЫХ цветов
  //          (для 16 и 256-цветных растров)
  //  bytes - массив индексов (1 - цвет невиден, 0 - цвет виден)
  //  size  - размер массива
  // Возвращает число НЕВИДИМЫХ цветов
  int GetInvisibleColors(unsigned char* bytes, int size);
  int SetInvisibleColors(unsigned char* bytes, int size);

  // Возврат/Установка БАЙТОВОГО массива индексов ВИДИМЫХ цветов
  //          (для 16 и 256-цветных растров)
  //  bytes - массив индексов (1 - цвет виден, 0 - цвет невиден)
  //  size  - размер массива
  // Возвращает число НЕВИДИМЫХ цветов
  int GetVisibleColors(unsigned char* bytes, int size);
  int SetVisibleColors(unsigned char* bytes, int size);

  // Возврат/Установка БИТОВОГО массива индексов НЕВИДИМЫХ цветов
  unsigned char* InvisibleColorsBits() { return HEADER.InvisibleColors; }
  unsigned char* InvisibleColorsBits(unsigned char* bits)
  {
    if (bits == 0) return 0;
    IsHeader(TRUE);
    memcpy(HEADER.InvisibleColors, bits, 32);
    return HEADER.InvisibleColors;
  }

  // Возврат/Установка флага инвертирования изображения
  // 0 - изображение позитивное
  // 1 - изображение негативное
  int Negative() { return (HEADER.Flag_Negative); }
  int Negative(int number)
  {
    IsHeader(TRUE);
    return (HEADER.Flag_Negative = (unsigned char)number);
  }

  // Возврат/Установка минимального значения элемента(для матрицы)
  double Minimum() { return (HEADER.Minimum); }
  double Minimum(double minimum)
  {
    IsHeader(TRUE);
    return (HEADER.Minimum=minimum);
  }

  // Возврат/Установка максимального значения элемента(для матрицы)
  double Maximum() { return (HEADER.Maximum); }
  double Maximum(double maximum)
  {
    IsHeader(TRUE);
    return (HEADER.Maximum=maximum);
  }

  // Возврат/Установка значения псевдокода(для матрицы)
  double PseudoCode() { return (HEADER.PseudoCode); }
  double PseudoCode(double pseudocode)
  {
    IsHeader(TRUE);
    return (HEADER.PseudoCode=pseudocode);
  }


  // Возврат/Установка единицы измерения (для матрицы)
  unsigned long Measure() { return (HEADER.Measure); }
  unsigned long Measure(unsigned long measure);

  // Возврат/Установка типа матрицы
  unsigned char MtrType() { return HEADER.MtrType; }
  unsigned char MtrType(unsigned char mtrtype)
  {
    IsHeader(TRUE);
    return HEADER.MtrType = mtrtype;
  }

  // Возврат/Установка метода построения поверхности        
  unsigned char Method() { return HEADER.Method; }
  unsigned char Method(unsigned char method)
  {
    IsHeader(TRUE);
    return HEADER.Method = method;
  }

  // Возврат/Установка флага "высота при наложении"         
  unsigned char HeightSuper() { return HEADER.HeightSuper; }
  unsigned char HeightSuper(unsigned char heightsuper)
  {
    IsHeader(TRUE);
    return HEADER.HeightSuper = heightsuper;
  }

  // Возврат/Установка флага формирования локальных экстремумов  
  unsigned char Extremum() { return HEADER.Extremum; }
  unsigned char Extremum(unsigned char extremum)
  {
    IsHeader(TRUE);
    return HEADER.Extremum = extremum;
  }

  // Проверить наличие свободного места на диске
  // При ошибке возвращает ноль
  int DiskFreeSpace(char* name);

  // Определение фактической длины файла
  // При ошибке возвращает ноль
  unsigned long FileLength();

  // Определение теорeтической длины файла
  // Использовать до создания растров
  // При ошибке возвращает ноль
  double CalculationFileLength(int width, int height, int bitpixel);

  // Пересчитать единицы высоты в метры
  inline double HeightUnitToMeter(double unit)
  {
    return unit*HeightMeterInUnit;
  }

  // Пересчитать метры в единицы высоты
  inline double HeightMeterToUnit(double meter)
  {
    return meter*HeightUnitInMeter;
  }


//*****************************************************************
// Функции установки и определения полей
// дополнительного описания растра ( матрицы )
//*****************************************************************

  // Возврат/Установка ошибки наложения высот (в единицах матрицы)
  double AbsHeightDifference() { return ADDITION.AbsHeightDifference; }
  double AbsHeightDifference(double difference)
  {
    IsAddition(TRUE);
    return (ADDITION.AbsHeightDifference = difference);
  }

  
//*****************************************************************
//  Функции для работы с файлом
//*****************************************************************

public:

  // Чтение блока {string,column} размером size в память bits.
  // Возвращает количество прочитанных байт.
  // При ошибке возвращает ноль.
  int ReadBlock(int string, int column, char* bits, int size);

  // Запись блока {string,column} размером size из памяти bits.
  // Возвращает количество записанных байт.
  // При ошибке возвращает ноль.
  int WriteBlock(int string, int column, char* bits, int size);

  // Запись блока буфера {string,column}
  // При ошибке возвращает ноль.
  int SaveBlock(int string, int column);

protected:

  // Чтение блока {string,column} по адресу "Part[iCur].addr"
  int ReadBlock(int string, int column);

  // Запись блока {string,column} из области "Part[iCur].addr"
  int WriteBlock(int partindex);

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

  // Чтение дополнительного описания растра из файла
  // При ошибке возвращает ноль
  int ReadAddition();

  // Запись дополнительного описания растра в файл
  // При ошибке возвращает ноль
  int WriteAddition();

  // Чтение описателя блоков из файла в буфер
  // При ошибке возвращает ноль
  int ReadBlockDesc();

  // Запись описателя блоков в файл из буфера
  // При ошибке возвращает ноль
  int WriteBlockDesc();

  // Чтение массива флагов блоков из файла в буфер
  // При ошибке возвращает ноль
  int ReadBlockFlags();

  // Запись массива флагов блоков в файл из буфера
  // При ошибке возвращает ноль
  int WriteBlockFlags();

  // Чтение рамки из файла
  // При ошибке возвращает ноль
  int ReadBorder();

  // Запись рамки в файл
  // При ошибке возвращает ноль
  int WriteBorder();

  // Чтение маски из файла       
  // При ошибке возвращает ноль
  int ReadMask();

  // Запись маски в файл         
  // При ошибке возвращает ноль
  int WriteMask();

public:

  // Определение принадлежности точки району
  friend int operator == (const RMFELEMENT& point, const RMFBLOCK& block)
  {
    if( (point.Col >= block.Begin.Col) && (point.Col <= block.End.Col) &&
        (point.Str >= block.Begin.Str) && (point.Str <= block.End.Str) )
         return TRUE;
    else return FALSE;
  }

  friend int operator != (const RMFELEMENT& point, const RMFBLOCK& block)
  {
	  if( (point.Col >= block.Begin.Col) && (point.Col <= block.End.Col) &&
        (point.Str >= block.Begin.Str) && (point.Str <= block.End.Str) )
         return FALSE;
    else return TRUE;
  }

};


//-----------------------------------------------------------------
// Определение смещения на блок в файле
//-----------------------------------------------------------------
inline unsigned long TRmf::BlockOffset(int index)
{
  if (BLOCKDESCBUFF == 0)
  {
    Error(IDS_STRUCT);
    return 0;
  }

  if (index < 0  ||  index >= BlockCount())
  {
    Error(IDS_STRUCT);
    return 0;
  }

  // Смещение и длина блока берется из описателя блоков BlockDesc
  return (BLOCKDESCBUFF+index)->Offset;
}

//-----------------------------------------------------------------
// Установка смещения на блок в файле
//-----------------------------------------------------------------
inline unsigned long TRmf::BlockOffset(int index, unsigned long offset)
{
  if (BLOCKDESCBUFF == 0)
  {
    Error(IDS_STRUCT);
    return 0;
  }

  if (index < 0  ||  index >= BlockCount())
  {
    Error(IDS_STRUCT);
    return 0;
  }

  IsBlockDesc(1);  // Изменился описатель блоков
  IsHeader(1);     // Изменилась длина файла

  // Смещение и длина блока берется из описателя блоков BlockDesc
  return (BLOCKDESCBUFF+index)->Offset = offset;
}

//-----------------------------------------------------------------
// Определение длины блока
//-----------------------------------------------------------------
inline long TRmf::BlockLength(int index)
{
  if (BLOCKDESCBUFF == 0)
  {
    Error(IDS_STRUCT);
    return 0;
  }

  if (index < 0  ||  index >= BlockCount())
  {
    Error(IDS_STRUCT);
    return 0;
  }

  // Смещение и длина блока берется из описателя блоков BlockDesc
  return (BLOCKDESCBUFF+index)->Length;
}

//-----------------------------------------------------------------
// Установка длины блока
//-----------------------------------------------------------------
inline long TRmf::BlockLength(int index, long length)
{
  if (BLOCKDESCBUFF == 0)
  {
    Error(IDS_STRUCT);
    return 0;
  }

  if (index < 0  ||  index >= BlockCount())
  {
    Error(IDS_STRUCT);
    return 0;
  }

  IsBlockDesc(1);  // Изменился описатель блоков
  IsHeader(1);     // Изменилась длина файла

  // Смещение и длина блока берется из описателя блоков BlockDesc
  return (BLOCKDESCBUFF+index)->Length = length;
}

//-----------------------------------------------------------------
// Возврат флага отображения блока
//-----------------------------------------------------------------
inline int TRmf::BlockVisible(int index)
{
  if (BLOCKFLAGSBUFF == 0)  // Если флажков нет - видно все !
  {
    return 1;
  }

  if (index < 0  ||  index >= BlockCount())
  {
    Error(IDS_STRUCT);
    return 0;
  }

  return *(BLOCKFLAGSBUFF+index);
}

//-----------------------------------------------------------------
// Установка флага отображения блока
//-----------------------------------------------------------------
inline int TRmf::BlockVisible(int index, int view)
{
  if (BLOCKFLAGSBUFF == 0) return 0;

  if (index < 0  ||  index >= BlockCount())
  {
    Error(IDS_STRUCT);
    return 0;
  }

  IsBlockFlags(1);  // Изменился массив флагов блоков
  IsHeader(1);      // Изменилась длина файла

  return *(BLOCKFLAGSBUFF+index) = (char)view;
}

#endif   // RMFBASE_H


