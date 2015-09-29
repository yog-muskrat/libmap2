
#ifndef MSPARM_H
#define MSPARM_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifndef MTREXAPI_H
  #include "mtrexapi.h"
#endif

#ifndef MTLAPI_H
  #include "mtlapi.h"
#endif

#ifndef TINAPI_H
  #include "tinapi.h"
#endif

#ifndef MAPCREAT_H
  #include "mapcreat.h"
#endif

#define _EXPORTAPI __declspec(dllexport) WINAPI

#define ABSOLUTE_HEIGHT_CODE 4  // Код х-ки АБСОЛЮТНАЯ ВЫСОТА
#define RELATIVE_HEIGHT_CODE 1  // Код х-ки ОТНОСИТЕЛЬНАЯ ВЫСОТА

//-----------------------------------------------------------------
//   Параметры построения матрицы высот
//-----------------------------------------------------------------
typedef struct MTRPARM
{
  BUILDMTW BuildMtw;                   

  PRIORMTRPARM PriorMtrParm;           

  RECT   RectMetr;       // Прямоугольник вывода в районе
                         // (в целых метрах)

  DFRAME DFrameMetr;     // Прямоугольник вывода в районе
                         // (в плавающих метрах)

  char Select;           // Флаг выбора и вывода фрагмента
                         //  (см. MAP2MTROUTPUTAREA)

  char CoordinateSystem; // Флаг системы координат при задании
                         // области вывода (см. MAP2MTRCOORDINATESYSTEM)

  char SelectSheetName;  // Флаг выбора имен матриц по листам

  char Compress;         // Флаг выполнения сжатия

  char BuildBySheets;    // Создание матриц по листам района

  char UseFilter;        // Флаг использования фильтра объектов (IMH-файл)

  char Reserve;          // Флаг ...

  char IsPriorMtrParm;   // Флаг выполнения предварительной оценки матрицы
                         //  0 - оценка не выполнялась;
                         //  1 - вычислена абсолютная величина разности высот объектов,
                         //      попадающих в элементы матрицы (PriorMtrParm.AbsHeightDifference)

  HWND MapWindowHandle;  // Идентификатор окна карты

  int AbsoluteHeightCode;   // Код х-ки Абс.высота
  int RelativeHeightCode;   // Код х-ки Отн.высота

  int AbsoluteHeightSign;   // Знак х-ки Абс.высота       
  int Reserve2;             

  char NameMTR[MAX_PATH];   // Имя MTW-файла
  char NameTXT[MAX_PATH];   // Имя IMH-файла
}
  MTRPARM;


#ifndef HIDEMTL    
// СТРУКТУРА ПАРАМЕТРОВ ДИАЛОГА СОЗДАНИЯ МАТРИЦЫ СЛОЕВ
typedef struct MTLPARM
{
  // Параметры создания матрицы слоев (API-структура)
  BUILDMTL MtlBuildParm;  

  // Размер данной структуры
  long Length;

  // Идентификатор окна карты
  HWND MapWindowHandle;

  // Прямоугольник вывода в районе (в целых метрах)
  RECT RectMetr;

  // Прямоугольник вывода в районе (в плавающих метрах)
  DFRAME DFrameMetr;

  // Габариты района в метрах
  DFRAME RegionMetr;

  // Номер зоны создаваемой карты
  long ZoneNumber;

  // Флаг выбора и вывода фрагмента (см. MAP2MTROUTPUTAREA)
  long Select;

  // Флаг "Градусы/Метры" при задании области вывода (см. MAP2MTRCOORDINATESYSTEM)
  long CoordinateSystem;

  // Тип исходных данных : 0-база данных, 1-карта, 2-текстовый файл;
  long InputDataType;

  // Форма представления исходных данных :
  //  0 - Мощности слоев
  //  1 - Абсолютные высоты
  long InputDataForm;

  // Проекция создаваемой карты
  long SitProjection;

  // Тип создаваемой карты
  long SitType;

  // Флаг выполнения сжатия
  long Compress;

  // Код обрабатываемого объекта  
  long PicketCode;

  // Внутренний код обрабатываемого объекта  
  long PicketIncode;

  // Флаг использования матрицы высот  
  long UseMtw;

  // Имя обрабатываемого объекта  
  char PicketName [MAX_PATH];

  // Имя создаваемой матрицы (MTL-файла)
  char NameMTL [MAX_PATH];

  // Имя файла легенды матрицы
  char NameTXT [MAX_PATH];

  // Имя входного файла карты
  char NameINPUTMAP [MAX_PATH];

  // Имя входного файла базы данных
  char NameINPUTDBF [MAX_PATH];

  // Имя входного текстового файла
  char NameINPUTTXL [MAX_PATH];

  // Имя матрицы высот
  char NameMTW [MAX_PATH];

  // Имя файла классификатора
  char NameRSC [MAX_PATH];

  // Постоянные проекции создаваемой карты
  CONSTPROJ ConstProj;

}
  MTLPARM;
#endif  // HIDEMTL

#ifndef HIDETIN
// СТРУКТУРА ПАРАМЕТРОВ ДИАЛОГА СОЗДАНИЯ TIN-МОДЕЛИ  
typedef struct TINPARM
{
  // Параметры создания TIN-модели (API-структура)
  TINBUILD TinBuild;

  // Размер данной структуры
  long Length;

  // Идентификатор окна карты
  HWND MapWindowHandle;

  // Прямоугольник вывода в районе (в целых метрах)
  RECT RectMetr;

  // Прямоугольник вывода в районе (в плавающих метрах)
  DFRAME DFrameMetr;

  // Габариты района в метрах
  DFRAME RegionMetr;

  // Флаг выбора и вывода фрагмента (см. MAP2MTROUTPUTAREA)
  long Select;

  // Имя создаваемой модели (TIN-файла)
  char NameTIN[MAX_PATH];

}
  TINPARM;
#endif  // HIDETIN

#ifndef HIDEMTQ
//-----------------------------------------------------------------
// СТРУКТУРА ПАРАМЕТРОВ ДИАЛОГА СОЗДАНИЯ МАТРИЦЫ КАЧЕСТВ
//-----------------------------------------------------------------
typedef struct MTQPARM  
{
  BUILDSURFACE BuildMtq;   // Параметры создания матрицы (API-структура)

  RECT RectMetr;           // Прямоугольник вывода в районе (в целых метрах)

  DFRAME DFrameMetr;       // Прямоугольник вывода в районе (в плавающих метрах)

  long int Select;         // Флаг выбора и вывода фрагмента (см. MAP2MTROUTPUTAREA)
  
  HWND MapWindowHandle;    // Идентификатор окна карты

  long int InputDataType;  // Тип исходных данных (0 - карта, 1 - база данных)

  long int DbfFieldX;      // Номера полей в базе данных для X,Y,H
  long int DbfFieldY;
  long int DbfFieldH;

  long int Precision;      // Точность представления границ и интервалов
                           // цветовой шкалы

  long int PaletteCount;             // Число цветов
  long int SmoothColorModification;  // Флаг : плавное изменение
                                     // цветов результирующей палитры

  long int SingleColourChange;       // Флаг : было изменение одиночных цветов
                                     //        результирующей палитры

  COLORREF Palette[256];             // Палитра
  COLORREF SkeletPalette[256];       // Скелетная палитра

  char NameMTQ[MAX_PATH];  // Имя создаваемой матрицы качеств
  char NameMTW[MAX_PATH];  // Имя создаваемой матрицы высот
  char NameMAP[MAX_PATH];  // Имя исходной карты
  char NameDBF[MAX_PATH];  // Имя исходной базы данных
}
  MTQPARM;
#endif  // HIDEMTQ

enum MAP2MTRCOORDINATESYSTEM
{
  MAP2MTR_RECTANGULAR = 0,  // Прямоугольная (метры)
  MAP2MTR_GEOGRADUS   = 1,  // Геодезическая (градусы)
};

enum MAP2MTROUTPUTAREA       // Режимы открытия/закрытия диалога 
{
  MAP2MTR_ALL          = 0,  // Открытие : область вывода - весь район
                             // Закрытие : область вывода не сохранять

  MAP2MTR_FRAME        = 1,  // Открытие : область вывода - из RectMetr
                             // Закрытие : область вывода -> в RectMetr

  MAP2MTR_SELECT_FRAME = 2,  // Открытие : область вывода - из RectMetr
                             // Закрытие : для выбора фрагмента

  MAP2MTR_CHANGE_FRAME = 3,  // Открытие : область вывода - из RectMetr
                             // Закрытие : для изменения фрагмента
};

enum MAP2MTLINPUTDATACOORDINATE
{
  MAP2MTL_1942_METER    = 0,  // Система координат 1942 г.(метры)
  MAP2MTL_1942_GRADUS   = 1,  // Система координат 1942 г.(градусы)
  MAP2MTL_1942_RADIAN   = 2,  // Система координат 1942 г.(радианы)
  MAP2MTL_1942_GRMINSEC = 3,  // Сист. коорд. 1942 г.(градусы,минуты,секунды)
  MAP2MTL_LOCAL_METER   = 4,  // Местная (метры)
  MAP2MTL_WGS84_GRADUS  = 5,  // WGS-84 (градусы)
  MAP2MTL_WGS84_RADIAN  = 6,  // WGS-84 (радианы)
};


//-----------------------------------------------------------------
//     Параметры построения растра
//-----------------------------------------------------------------
typedef struct RSTBUILDPARM
{
  BUILDMTW BuildMtw;  

  RECT   RectMetr;  // Прямоугольник вывода в районе (в целых метрах)

  DFRAME DFrameMetr;  // Прямоугольник вывода в районе
                      // (в плавающих метрах)

  char Select;        // Флаг выбора и вывода фрагмента
                      //  (см. MAP2MTROUTPUTAREA)

  char CoordinateSystem; // Флаг системы координат при задании
                  // области вывода (см. MAP2MTRCOORDINATESYSTEM)

  char SelectSheetName;  // Флаг выбора имен матриц по листам

  char Compress;         // Флаг выполнения сжатия

  char BuildBySheets;    // Флаг построения по листам

  char Free[3];

  HWND MapWindowHandle;  // Идентификатор окна карты

  char Free1[4];         // Выравнивание

  char NameRST [MAX_PATH];  // Имя RST-файла
  char NameTXT [MAX_PATH];  // Имя ТХТ-файла
}
  RSTBUILDPARM;

 typedef struct AREAGRADUS
 {
   long LTG; long LTM; long LTS; long CorrectLT;
   long RTG; long RTM; long RTS; long CorrectRT;
   long DNG; long DNM; long DNS; long CorrectDN;
   long UPG; long UPM; long UPS; long CorrectUP;
 }
   AREAGRADUS;

typedef struct MTQPALETTEPARM    //  ПАРАМЕТРЫ СОЗДАНИЯ ПАЛИТРЫ МАТРИЦЫ КАЧЕСТВ
{
  unsigned
  long int StructSize;  // Размер данной структуры : sizeof (MTQPALETTEPARM)
  HWND     Handle;      // Идентификатор окна приложения

  double   Minimum;     // Минимальное значение моделируемой характеристики
  double   Maximum;     // Максимальное значение моделируемой характеристики

  long int ResultColorCount;         // Кол-во цветов результирующей палитры
  long int SmoothColorModification;  // Флаг : плавное изменение
                                     //        цветов результирующей палитры

  long int SingleColourChange;  // Флаг : было изменение одиночных цветов
                                //        результирующей палитры
  long int Precision;           // Точность представления границ и интервалов
                                // цветовой шкалы

  COLORREF SkeletPalette[256];  // Исходная (скелетная) палитра
  COLORREF ResultPalette[256];  // Результирующая палитра

  char HelpName[256];  // Полное имя файла ".hlp"
  char Reserve[256];   // Должны быть нули
}
  MTQPALETTEPARM;

#endif  // MSPARM_H
