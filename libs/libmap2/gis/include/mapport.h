#ifndef MAPPORT_H
#define MAPPORT_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifdef WIN32API

typedef long int HCOMPORT;

extern "C"
{

// Открыть COM-порт для чтения GPS - сообщений в формате NMEA O183
// portname - имя COM-порта (например, "COM1:")
// baudrate - частота обмена с портом (например, 4800)
// При ошибке возвращает 0
HCOMPORT _MAPAPI gpsOpen(LPTSTR portname, long int baudrate);

// Закрыть COM-порт
void _MAPAPI gpsClose(HCOMPORT hcomport);

// Открыть COM-порт для чтения/записи
// portname - имя COM-порта (например, "COM1:")
// baudrate - частота обмена с портом (например, 4800)
// При ошибке возвращает 0
HCOMPORT _MAPAPI gpsOpenComPort(LPTSTR portname, long int baudrate);

// Закрыть COM-порт
void _MAPAPI gpsCloseComPort(HCOMPORT hcomport);

// Запросить - обновились ли координаты точки
long int _MAPAPI gpsIsUpdate(HCOMPORT hcomport);

// Запросить координаты текущей точки в радианах в системе 42 года
// Признак обновления координат сбрасывается
long int _MAPAPI gpsGetPoint(HCOMPORT hcomport, DOUBLEPOINT * point,
                             double * height);

// Запросить координаты текущей точки в градусах в системе GPS
// Признак обновления координат сбрасывается
long int _MAPAPI gpsGetSourcePoint(HCOMPORT hcomport, DOUBLEPOINT * point,
                                   double * height);

// Запросить число видимых спутников
long int _MAPAPI gpsSatelliteCount(HCOMPORT hcomport);

// Запросить качество приема данных
long int _MAPAPI gpsQuality(HCOMPORT hcomport);

// Запросить имя открытого COM-порта
LPTSTR _MAPAPI gpsPortName(HCOMPORT hcomport);

// Запросить идентификатор открытого COM-порта
// Если порт закрыт - возвращает ноль
HANDLE _MAPAPI gpsPortHandle(HCOMPORT hcomport);

// Запросить содержимое последней записи из GPS
// buffer - адрес буфера для размещения результата
// size   - размер буфера
// При ошибке возвращает ноль
long int _MAPAPI gpsGetRecord(HCOMPORT hcomport, char * buffer, long int size);

} // extern "C"

#endif

#endif  // MAPPORT_H
