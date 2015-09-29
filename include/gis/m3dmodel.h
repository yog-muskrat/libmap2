#ifndef M3DMODEL_H
#define M3DMODEL_H

#include "m3dgdi.h"

typedef struct IMG3DANGLE     // Угол поворота (от 1 отрезка метрики)
{                             //
  double AngleX;              // На угол с осью X (в градусах и долях градуса)
  double AngleY;              // На угол с осью Y
  double AngleZ;              // На угол с осью Z
}
  IMG3DANGLE;


typedef struct FIXATION       // Cтруктура для привязки изображений
{
  IMG3DPOINT Offset;          // Смещение относительно 1 точки модели
  IMG3DANGLE Angle;           // Поворот относительно первого отрезка метрики
  IMG3DPOINT Factor;          // Сжатие - растяжение по осям
}
  FIXATION;

typedef struct WRAPIMAGE      // Cтруктура для повтора изображений (40 байт)
{
  char       FlagHeight;      // Флаг повтора по высоте
                              // см. TEXTUREMEASURE(m3dgdi.h)
  char       WrapHeight;      // Повтор по количеству или по размеру по высоте
  char       FlagVector;      // Флаг повтора по направлению вектора привязки
                              // см. TEXTUREMEASURE(m3dgdi.h)
  char       WrapVector;      // Повтор по количеству
                              // или по размеру по вектору привязки
  long       Reserv;          //
  IMG3DVALUE ValueHeight;     // Величина повтора по высоте
  IMG3DVALUE ValueVector;     // Величина повтора по вектору привязки
}
  WRAPIMAGE;


enum IMAGETYPE      // Тип структуры изображения
   {
     rscIMGTREE    = 0,  // Изображение шаблон
     rscMODEL      = 1   // Изображение модель
   };

typedef struct IMAGEHEAD      // Сведения об изображении
{
  long       Length;          // Общая длина заголовка
  long       Key;             // Ключ модели или шаблона
  long       Code;            // Код библиотеки, где записана модель или шаблон
  char       Flag;            // Тип структуры см.IMAGETYPE
  char       Cut;             // Флаг вырезки из основания (1 - вырезаем, 0 - нет)
  char       Stretch;         // Флаг растягивания (1 - растягивать, 0 - нет)
  char       Reserv[5];       //
  IMG3DVALUE Heigth;          // Общая высота изображения (возможно,
                              // взятая из семантики)
  IMG3DVALUE RelativeHeight;  // Относительная высота изображения (возможно,
                              // взятая из семантики
                              // или указано над каким изображением)
  WRAPIMAGE Wrap;             // Данные для повтора изображения
  FIXATION  Fixator;          // Данные для привязки изображения
                              // к форме основания модели
  long Count;                 // Количество точек для изображения шаблона
                              // (для модели = 0)
//IMG3DPOINT  Point[Count];   // Точки формы oснования шаблона
                              // (по 2 точки на отрезок)
}
 IMAGEHEAD;


typedef struct DESCMODEL      // Описание модели
{
  long Length;                // Общая длина
  long Count;                 // Количество подчиненных моделей
  long Rezerv[2];             // Резерв
  IMAGEHEAD Head[1];          // Заголовок изображения подчиненных моделей
                              // Одна существует всегда (заполняет все пробелы)
}
  DESCMODEL;

typedef struct M3DMODEL          // Cтруктура модели
{
  unsigned long Ident;        // Идентификатор записи
  long          Length;       // Длина
  long          Form;         // Ключ
                              // (только для основной модели)
  long          Reserv1;      // Резерв
  IMG3DPOINT    Base[2];      // Вектор для привязки моделей
                              // координаты формы модели считаются от вектора
  long          Count;        // Количество точек формы основания модели
  long          Reserv2;      // Резерв
 //IMG3DPOINT  Point[Count];  // Точки формы основания модели (по 2 точки на отрезок)
 //DESCMODEL   Desk;          // Описание модели
}
  M3DMODEL;


typedef struct PACKET         // Пакет моделей для объекта
{
  long      Length;           // Длина
  long      Count;            // Количество моделей
  // long       Key;          // Ключ модели или шаблона
  // long       Code;         // Код библиотеки, где записана модель или шаблон
}
  PACKET;

#endif





