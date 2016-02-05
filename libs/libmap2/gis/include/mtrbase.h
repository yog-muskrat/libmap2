
#ifndef MTRBASE_H
#define MTRBASE_H

#ifndef RMFBASE_H
  #include "rmfbase.h"
#endif

typedef TRMFDATA TMTRDATA;

// Создание файла матрицы с характеристиками, заданными в структурах
// BUILDMTW, MTRPROJECTIONDATA.
// Если MTRPROJECTIONDATA равен нулю, то данные о проекции не устанавливаются.
// Параметр checkdiskfreespace определяет проверку наличия свободного
// места на диске (при checkdiskfreespace = 0 проверка не выполняется)  
int _fastcall mtrCreate(TMTRDATA *mtrdata, const char* name,
                        BUILDMTW* MtrParm,
                        MTRPROJECTIONDATA * MtrProjectionData,
                        int checkdiskfreespace);

// Открытие файла
int _fastcall mtrOpen(TMTRDATA *mtrdata, const char* mtrname, int mode);

// Поиск ближайшей значащей точки в заданном направлении
// в пределах габаритов матрицы
//  string - строка точки начала сканирования (абсолютные индексы)
//  column - столбец точки начала сканирования
//  direct - направление сканирования (0 - 15)
//  pstr   - строка точки конца сканирования (абсолютные индексы)
//  pcol   - столбец точки конца сканирования
//  value  - значение найденой точки
int _fastcall mtrScanPoint(TMTRDATA *mtrdata, int string, 
                           int column, int direct,
                           int *pstr, int *pcol, long *value);

// Возврат минимального значения высоты в метрах
double _fastcall mtrMinimumHeight(TMTRDATA *mtrdata);  

// Возврат минимального значения высоты в метрах
double _fastcall mtrMinHeightMeter(TMTRDATA *mtrdata);

// Возврат максимального значения высоты в метрах
double _fastcall mtrMaximumHeight(TMTRDATA *mtrdata);

// Возврат максимального значения высоты в метрах
double _fastcall mtrMaxHeightMeter(TMTRDATA *mtrdata);

// Возврат размера элемента в байтах
int _fastcall mtrElementSizeBytes(TMTRDATA *mtrdata);

#ifndef HIDEMTQ            
                            

// ===========================================================
//           МАТРИЦЫ КАЧЕСТВ   
// ===========================================================

//--------------------------------------------------------------
// Создание файла матрицы качеств с характеристиками, заданными
// в структурах MTRBUILDPARMEX, MTRPROJECTIONDATA и палитрой.
//--------------------------------------------------------------
int _fastcall mtrCreateMtqFileEx(TMTRDATA *mtrdata, const char* name,
                                 BUILDMTW* MtrParm,
                                 MTRPROJECTIONDATA * MtrProjectionData,
                                 COLORREF* palette, int countpalette);

#endif

#ifdef __cplusplus

class _DLLCLASS TMtr: public TRmf
{
 public:

  // Пустой объект
  TMtr();

  // Объект для связи с существующим файлом матрицы
  TMtr(const char* name, int mode = 0);

  // Открытие файла
  int Open(const char *name, int mode = 0);

  // Создание файла матрицы с заданными характеристиками    
  // Параметр checkdiskfreespace определяет проверку наличия свободного
  // места на диске (при checkdiskfreespace = 0 проверка не выполняется)
  int Create(const char* name, BUILDMTW* parm,
             MTRPROJECTIONDATA * mtrprojectiondata,
             int checkdiskfreespace = 1);

  // Возврат минимального значения высоты в метрах
  double MinimumHeight()  { return HeightUnitToMeter(HEADER.Minimum); }
  double MinHeightMeter() { return HeightUnitToMeter(HEADER.Minimum); }

  // Возврат максимального значения высоты в метрах
  double MaximumHeight()  { return HeightUnitToMeter(HEADER.Maximum); }
  double MaxHeightMeter() { return HeightUnitToMeter(HEADER.Maximum); }

  // Возврат размера элемента в байтах
  int ElementSizeBytes() { return (ElementSize()>>3); }

  // Поиск ближайшей значащей точки в заданном направлении
  // в пределах габаритов матрицы (для построения матрицы)
  //  string - строка точки начала сканирования (абсолютные индексы)
  //  column - столбец точки начала сканирования
  //  direct - направление сканирования (0 - 15)
  //  pstr   - строка точки конца сканирования (абсолютные индексы)
  //  pcol   - столбец точки конца сканирования
  //  value  - значение найденой точки
  int ScanPoint(int string, int column, int direct,
                int& pstr, int& pcol, long& value);
};
#else

typedef TRMFDATA TMtr;  

#endif // __cplusplus

#endif  // MTRBASE_H

