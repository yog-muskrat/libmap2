
#ifndef TIN_H
#define TIN_H

#define VERSION_TIN      0x00010000    // Веpсия структуры 1.0
#define LABEL_TIN        0x004E4954L

#include "mapcreat.h"
//------------------------------------------------------------------
// ЗАГОЛОВОК ФАЙЛА ФОРМАТА TIN
//------------------------------------------------------------------
struct TTinHeader{               // Заголовок tin файла
  unsigned long Label;          // Идентификатор начала файла (TIN0)
   unsigned long TriangleCount;  // Число треугольников
  unsigned long BaseScale;      // Базовый масштаб
  
  double            XMin;       // Tin X min (Down)
  double            YMin;       // Tin Y min (Left)
  double            XMax;       // Tin X max (Up)
  double            YMax;       // Tin Y max (Right)  
}; 

#endif   // TIN_H

