
#ifndef RSTBASE_H
#define RSTBASE_H

#ifndef RMFBASE_H
  #include "rmfbase.h"
#endif

#ifndef RST_H
  #include "rst.h"
#endif

//******************************************
//   БАЗОВЫЙ КЛАСС РАСТРОВОГО ИЗОБРАЖЕНИЯ
//******************************************
class _DLLCLASS TRst : public  TRmf
{
  public:

  TRst();                                       // Конструктор (пустой)
  TRst(char* name, int mode = 0);               // Конструктор
  TRst(char * name, int width, int height, int bit, COLORREF* palette = 0,
       double scale=0, double precision=0);

  // Конструктор уменьшенной копии существующего файла
  TRst(HANDLE fileid, unsigned long headeroffset);
  ~TRst();

//****************************************************
// Член-функции класса TRst:
//****************************************************

public:

  // Создание файла
  // При ошибке возвращает ноль
  int Create(char * name,long width, long height,
             long nbits, COLORREF* palette,
             double scale=0, double precision=0);

  // Открытие файла
  // При ошибке возвращает ноль
  int Open(char *name, int mode = 0);

  // Закрытие файла
  void Close();

  // Определение флага установленности привязки растра
  int Location() {return (int)HEADER.Flag_Location;}

  // Установка флага установленности привязки растра
  void Location(int set){HEADER.Flag_Location = (unsigned char)set;}

  // Определение точки привязки в районе в метрах
  // (для RST версии <= 0x0101 - в элементах)
  double LocationX() { return HEADER.LocationX; }
  double LocationY() { return HEADER.LocationY; }

  // Установка точки привязки изображения в районе в метрах
  double LocationX(double location);
  double LocationY(double location);

  // Определение масштаба
  double Scale() {return TRmf::Scale();}

  // Установка масштаба
  double Scale(double scale);

  // Определение количества элементов на метр
  double Precision() {return TRmf::Precision();}

  // Установка количества элементов на метр
  double Precision(double precision);

  // Определение флага инвертирования изображения
  // 0 - изображение позитивное
  // 1 - изображение негативное
  int Negative() { return TRmf::Negative();  }

  // Установка флага инвертирования изображения
  int Negative(int number);

  // Установка рамки
  int SetBorder(TDataEdit* data);

  // Определение/Установка флага отображения по рамке
  int ShowByBorder() {return TRmf::ShowByBorder();}
  int ShowByBorder(int value);

  // Установка маску  
  int SetMask(TDataEdit* data);

  // Определение/Установка флага отображения по маске     
  int ShowByMask() {return TRmf::ShowByMask();}
  int ShowByMask(int value);

  // Удалить рамку
  int DeleteBorder();

  // Запись блока {string,column} размером "size" из памяти "bits"
  // Возвращает количество записанных байт
  // При ошибке возвращает ноль
  int WriteBlock(int string, int column, char* bits, int size);

  // Запись блока {string,column} размером "size" по DID-маске "mask"
  // индексом "color"
  // При ошибке возвращает ноль
  int PutBlockByMask(int string, int column, char* mask, long size,
                         long width,long height,long value);

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

  // Чтение цветовых плоскостей прямоугольного участка растра
  //  bitsR,bitsG - указатели на начало изображения байтовых областей
  //  bitsB         красной, зеленой и синей плоскости
  //  left    - смещение слева в элементах
  //  top     - смещение сверху в элементах
  //  width   - ширина в элементах
  //  height  - высота в элементах
  //  Поддерживает только 8-битные растры (пока)
  // При ошибке возвращает 0
  int GetFrameRGB(char* bitsR, char* bitsG, char* bitsB,       
                  int left, int top, int width, int height);

  // Обновить текущую уменьшенную копию по i,j блоку основного растра
  // размер элемента основного растра - 8 бит на пиксел
  // При ошибке возвращает ноль
  int UpdateDuplicateAsBlock256(int string, int column);

  // Обновить текущую уменьшенную копию по блоку(string,column) основного растра
  // При ошибке возвращает ноль
  int UpdateDuplicateAsBlock(int string, int column);

  // Обновить уменьшенную копию
  // Если number = 0, обновить все уменьшенные копии
  // Количество копий не больше 3 (number <= 3)
  // Если уменьшенные копии не существуют, создается одна копия
  int UpdateDuplicates(int number = 0);

  // Возвращает указатель на класс TRst для отображения основного изображения
  // или TRstDuplicate для отображения уменьшенной копии
  TRmf & GetRstClass(int duplicate);  

  // При наличии копии возвращает указатель на класс TRstDuplicate,
  // иначе - указатель на класс TRst основного изображения
  // number - номер копии(начиная с 1)
  TRst & GetRstDuplicate();

  // Создать уменьшенную копию растра
  // number - номер копии(начиная с 1)
  // При успешном завершении создает объект уменьшенной копии Duplicate,
  // создает заголовок и блоки уменьшенной копии с записью в файл.
  // Duplicate инициализируется заголовком и блоками созданной уменьшенной копии
  // При ошибке :
  //   возвращает ноль,
  //   смещение на уменьшенную копию в основном растре устанавливается в ноль,
  //   объект Duplicate удаляется и устанавливается в ноль.
  int CreateDuplicate(int number);

  // Создать заголовок уменьшенной копии растра
  // number - номер копии(начиная с 1)
  // При успешном завершении создается объект уменьшенной копии Duplicate,
  // создается заголовок уменьшенной копии с записью в файл.
  // Duplicate инициализируется заголовком созданной уменьшенной копии
  // При ошибке возвращает ноль
  int CreateDuplicate(int number,
                      long width, long height,
                      long elementSize,
                      double scale, double precision,
                      DOUBLEPOINT location);

  // Создать изображение текущей уменьшенной копи Duplicate растра c 8 б\п
  // (Duplicate должен содержать заголовок уменьшенной копии)
  // divisor - линейный коэффициент уменьшения основного растра
  // При ошибке :
  //   возвращает ноль,
  //   смещение на уменьшенную копию в основном растре устанавливается в ноль,
  //   объект Duplicate удаляется и устанавливается в ноль.
  int CreateDuplicateImage256(int divisor);

  // Создать изображение текущей уменьшенной копи Duplicate растра
  // (Duplicate должен содержать заголовок уменьшенной копии)
  // divisor - линейный коэффициент уменьшения основного растра
  // При ошибке :
  //   возвращает ноль,
  //   смещение на уменьшенную копию в основном растре устанавливается в ноль,
  //   объект Duplicate удаляется и устанавливается в ноль.
  int CreateDuplicateImage(int divisor);

  // Сохранить данные уменьшенных копий в файлe
  // Синхронизировать общие параметры (длину файла, масштаб,
  // разрешающую способность, привязку) основного изображения с
  // параметрами уменьшенных копий
  // При ошибке возвращает ноль
  int SaveDuplicates(int force);

protected :

  // Чтение заголовка из файла старого формата (RST/MTR)
  int ReadOldHeader(RST * header);

  // Инициализируется заголовок нового формата
  // Заполняется палитра,рамка,описатель блоков
  int InitializeNewHeader(RST * header);

  // Записать заголовок,рамка,описатель блоков
  // новой структуры в конец файла
  int WriteNewHeaderToFileEnd(RST * header);

private :

  // Прочитать заголовок и др. служебные структуры уменьшенной
  // копии растра по смещению headeroffset от начала файла растра
  int ReadDuplicate(unsigned long headeroffset);

  // Создание заголовка уменьшенной копии растра с записью в файл
  // headeroffset - смещение относительно начала файла на заголовок
  //                уменьшенной копии
  // offsetFactor - для больших файлов (> 4Gb) д.б. равно 8, иначе 0
  // При ошибке возвращает 0
  int CreateDuplicateHeader(unsigned long headeroffset,
                            long width, long height,
                            long elementSize,
                            double scale, double precision,
                            DOUBLEPOINT location, int offsetFactor);
};

typedef TRmf TRSTDATA;

// Создание файла
// При ошибке возвращает
int _fastcall rstCreate(TRSTDATA *rstdata, const char * name, long width,
                        long height, long nbits, COLORREF* palette,
                        double scale, double precision);

// Открытие файла
// При ошибке возвращает ноль
// При успешном выполнении возвращает RMFOKEY
int _fastcall rstOpen(TRSTDATA *rstdata, const char* name, int mode);

// Чтение заголовка из файла старого формата (RST)
// Инициализируется заголовок нового формата
// Заполняется палитра,рамка,описатель блоков
// При ошибке возвращает ноль
int _fastcall rstReadOldHeader(TRSTDATA *rstdata, RST * header);

// Инициализируется заголовок нового формата
// Заполняется палитра,рамка,описатель блоков
// При ошибке возвращает ноль
int _fastcall rstInitializeNewHeader(TRSTDATA *rstdata, RST * header);

// Записать заголовок новой структуры в конец файла
// При ошибке возвращает ноль
int _fastcall rstWriteNewHeaderToFileEnd(TRSTDATA *rstdata, RST * header);

// Закрытие файла
void _fastcall rstClose(TRSTDATA *rstdata);

// Установка точки привязки изображения в районе в метрах
double _fastcall rstLocationX(TRSTDATA *rstdata, double location);

// Установка точки привязки изображения в районе в метрах
double _fastcall rstLocationY(TRSTDATA *rstdata, double location);

// Установка масштаба
double _fastcall rstScale(TRSTDATA *rstdata, double scale);

// Установка количества элементов на метр
double _fastcall rstPrecision(TRSTDATA *rstdata, double precision);

// Установка флага инвертирования изображения
int _fastcall rstNegative(TRSTDATA *rstdata, int number);

// Установить рамку
int _fastcall rstSetBorder(TRSTDATA *rstdata, DATAEDIT* data);  

// Установить маску  
int _fastcall rstSetMask(TRSTDATA *rstdata, DATAEDIT* data);  

// Установка флага отображения по рамке
int _fastcall rstPutShowByBorder(TRSTDATA *rstdata, int value);

// Установка флага отображения по рамке
#define rstGetShowByBorder  rmfGetShowByBorder

// Установка флага отображения по маске    
int _fastcall rstPutShowByMask(TRSTDATA *rstdata, int value);

// Запрос флага отображения по рамке       
#define rstGetShowByMask  rmfGetShowByMask

// Удалить рамку
int _fastcall rstDeleteBorder(TRSTDATA *rstdata);

// Запись блока {string,column} размером "size" из памяти "bits"
// Возвращает количество записанных байт
// При ошибке возвращает ноль
int _fastcall rstWriteBlock(TRSTDATA *rstdata, 
                            int string, int column, char* bits, int size);

// Запись блока {string,column} размером "size" по DID-маске "mask"
// индексом "color"
// При ошибке возвращает ноль
int _fastcall rstPutBlockByMask(TRSTDATA *rstdata, 
                                int string, int column, char* mask, long size,
                                long width,long height,long value);

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
//  при rstdata->RmfData.RmfData.HEADER.ElementSize == 1 (бит) - left,width кратны 8,
//                    == 4 (бит) - left,width кратны 2
// При ошибке возвращает 0
int _fastcall rstPutFrame(TRSTDATA *rstdata, char* bits,
                          int left, int top, int width, int height,
                          int begining, int widthinbyte);

//-----------------------------------------------------------------
// Чтение цветовых плоскостей прямоугольного участка растра
//  bitsR,bitsG - указатели на начало изображения байтовых областей
//  bitsB         красной, зеленой и синей плоскости
//  left    - смещение слева в элементах
//  top     - смещение сверху в элементах
//  width   - ширина в элементах
//  height  - высота в элементах
//  Поддерживает только 8-битные растры (пока)
// При ошибке возвращает 0
//-----------------------------------------------------------------
int _fastcall rstGetFrameRGB(TRMFDATA *rstdata,
                             char* bitsR, char* bitsG, char* bitsB,
                             int left, int top, int width, int height);

// Возвращает указатель на структуру TRSTDATA для отображения
// основного изображения или TRSTDUPLICATE для отображения
// уменьшенной копии
TRmf * _fastcall rstGetRstClass(TRmf * rstdata, int duplicate);


// При наличии копии возвращает указатель на класс TRstDuplicate,
// иначе - указатель на класс TRst основного изображения
TRst * _fastcall rstGetRstDuplicate(TRst *rstdata);

// Создать уменьшенную копию растра
// number - номер копии(начиная с 1)
// При успешном завершении создает объект уменьшенной копии rstdata->Duplicate,
// создает заголовок и блоки уменьшенной копии с записью в файл.
// rstdata->Duplicate инициализируется заголовком и блоками созданной уменьшенной копии
// При ошибке :
//   возвращает ноль,
//   смещение на уменьшенную копию в основном растре устанавливается в ноль,
//   объект rstdata->Duplicate удаляется и устанавливается в ноль.
int _fastcall rstCreateDuplicate(TRSTDATA *rstdata, int number);

// Создать заголовок уменьшенной копии растра
// number - номер копии(начиная с 1)
// При успешном завершении создает объект уменьшенной копии rstdata->Duplicate,
// создает заголовок уменьшенной копии с записью в файл.
// rstdata->Duplicate инициализируется заголовком созданной уменьшенной копии
// При ошибке возвращает ноль
int _fastcall rstCreateDuplicateCopyHeader(TRSTDATA *rstdata, int number,
                                           long width, long height,
                                           long elementSize,
                                           double scale, double precision,
                                           DOUBLEPOINT location);

// Обновить текущую уменьшенную копию по i,j блоку основного растра
// размер элемента основного растра - 8 бит на пиксел
// При ошибке возвращает ноль
int _fastcall rstUpdateDuplicateAsBlock256(TRSTDATA *rstdata, 
                                           int string, int column);

// Обновить текущую уменьшенную копию по i,j блоку основного растра
// При ошибке возвращает ноль
int _fastcall rstUpdateDuplicateAsBlock(TRSTDATA *rstdata,
                                        int string, int column);

// Сохранить данные уменьшенных копий в файлe
// Синхронизировать общие параметры (длину файла, масштаб,
// разрешающую способность, привязку) основного изображения с
// параметрами уменьшенных копий
// При ошибке возвращает ноль
int _fastcall rstSaveDuplicates(TRSTDATA *rstdata, int force);

// Обновить уменьшенную копию
// Если number = 0, обновить все уменьшенные копии
// Количество копий не больше MAX_DUPLICATECOUNT (number <= MAX_DUPLICATECOUNT)
// Если уменьшенные копии не существуют, создается одна копия
int _fastcall rstUpdateDuplicates(TRSTDATA *rstdata, int number);

// Создать изображение текущей уменьшенной копи rstdata->Duplicate растра c 8 б\п
// (rstdata->Duplicate должен содержать заголовок уменьшенной копии)
// divisor - линейный коэффициент уменьшения основного растра
// При ошибке :
//   возвращает ноль,
//   смещение на уменьшенную копию в основном растре устанавливается в ноль,
//   объект rstdata->Duplicate удаляется и устанавливается в ноль.
int _fastcall rstCreateDuplicateImage256(TRSTDATA *rstdata, int divisor);

// Создать изображение текущей уменьшенной копи rstdata->Duplicate растра
// (rstdata->Duplicate должен содержать заголовок уменьшенной копии)
// divisor - линейный коэффициент уменьшения основного растра
// При ошибке :
//   возвращает ноль,
//   смещение на уменьшенную копию в основном растре устанавливается в ноль,
//   объект rstdata->Duplicate удаляется и устанавливается в ноль.
int _fastcall rstCreateDuplicateImage(TRSTDATA *rstdata, int divisor);


// Прочитать заголовок и др. служебные структуры уменьшенной
// копии растра по смещению headeroffset от начала файла растра
int _fastcall rstReadDuplicate(TRSTDATA *rstdupdata, 
                               unsigned long headeroffset);

// Создание заголовка уменьшенной копии растра с записью в файл
// headeroffset - смещение относительно начала файла на заголовок
//                уменьшенной копии
// При ошибке возвращает 0
int _fastcall rstCreateDuplicateHeader(TRSTDATA *rstdupdata,
                                       unsigned long headeroffset,
                                       long width, long height,
                                       long elementSize,
                                       double scale, double precision,
                                       DOUBLEPOINT location,
                                       int offsetFactor);  

#endif   // RSTBASE_H
