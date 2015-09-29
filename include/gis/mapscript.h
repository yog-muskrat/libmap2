#ifndef MAPSCRIPT_H
#define MAPSCRIPT_H

#ifndef MAPTYPE_H
 # include "maptype.h"
#endif

typedef void (WINAPI * SCRIPTLINE)(POINT * point, long int count);
typedef void (WINAPI * SETUPLINE)(long int thick, COLORREF color);

typedef void (WINAPI * SCRIPTPOLYGON)(POINT * point,
                     long int * count, long int polycount, RECT * border);
typedef void (WINAPI * SETUPPOLYGON)(COLORREF color);

typedef void (WINAPI * SCRIPTTEXT)(long int x, long int y,
                                 const char * text, LOGFONT * logfont,
                                 long int align, COLORREF color);

typedef long int (WINAPI * SETUPPERCENT)(long int percent);

typedef struct SCRIPTTABLE     // Таблица функций формирования SCRIPT
{
  SCRIPTLINE    DrawLine;      // Построение линии
  SCRIPTPOLYGON DrawPolygon;   // Построение полигона
  SCRIPTTEXT    DrawText;      // Нанесение текста

  SETUPLINE     SetupLine;     // Параметры линии
  SETUPPOLYGON  SetupPolygon;  // Параметры полигона

  SETUPPERCENT  SetupPercent;  // Сообщить процент выполнения
}
 SCRIPTTABLE;

#ifdef __cplusplus
extern "C"
{
#endif

// Сохранить изображение карты в виде векторного SCRIPT-описания
// в базовом масштабе карты и текущем составе отображения
// hMap       - идентификатор открытой карты
// precision  - число точек на метр изображения в SCRIPT-описании
//              по горизонтали(h) и вертикали(v)
// table      - таблица функций формирования SCRIPT-записей по координатам
// При ошибке возвращает ноль

long int _MAPAPI mapPaintToScript(HMAP hMap, double hprecision, double vprecision,
                                  SCRIPTTABLE * table);

// Примечание.
// SCRIPT описание формируется из набора примитивов - линии, полигона,
// текста (DrawLine,...). Параметры линии и полигона устанавливаются
// перед вызовом соответствующих примитивов (SetupLine,...).
// Параметры текста передаются вместе с координатами и текстом
// в кодировке ANSI (DrawText).
// Координаты передаются в системе Windows в точках устройства отображения
// для базового масштаба карты
// Состав объектов соответствует текущему составу отображения с
// учетом масштабов видимости объектов
// Для определения текущего процента выведенных данных вызывается
// функция SetupPercent. Если необходимо завершить выполнение
// вывода, функция должна вернуть нулевое значение.

#ifdef __cplusplus
} // extern "C"
#endif

#endif // MAPSCRIPT_H

