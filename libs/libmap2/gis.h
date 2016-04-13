#ifndef GIS_H
#define GIS_H

/// Выключение предупреждений компилятора для сторонних картографических библиотек.
#pragma GCC diagnostic push

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#pragma GCC diagnostic ignored "-Wreorder"
#pragma GCC diagnostic ignored "-Wparentheses"

#include "mapapi.h"
#include "seekapi.h"
#include "rscapi.h"
#include "sitapi.h"
#include "mathapi.h"

#pragma GCC diagnostic pop


#endif // GIS_H
