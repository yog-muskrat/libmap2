
#ifndef MTRPALET_H
#define MTRPALET_H

#ifndef  MAPMACRO_H
 #include "mapmacro.h"
#endif

#ifndef BASCOLOR_H
 #include "bascolor.h"
#endif

typedef BASECOLORS TMTRPALETTE;

enum                       // Стиль палитры
{
  MTRPONLYSHADOW   = -1,   // Только тени (палитра игнорируется)
  MTRPGRAY         =  0,   // Полутоновая палитра
  MTRPCOLOR        =  1,   // Цветная палитра
};

enum                       // Флаг тени                 
{
  MTRSHADOW_NONE   =  0,   // Тень отсутствует
  MTRSHADOW_PALE   =  1,   // Бледная
  MTRSHADOW_WEAK   =  2,   // Слабая
  MTRSHADOW_MIDDLE =  4,   // Средняя
  MTRSHADOW_HEAVY  =  8,   // Сильная
  MTRSHADOW_DEEP   = 16,   // Глубокая
};

// Инициализация данных
void _fastcall mtrpInit(TMTRPALETTE *mtrpalette);

// Установить стиль
void _fastcall mtrpStyle(TMTRPALETTE *mtrpalette, int style);

//  Начальное заполнение действующей и активной палитры
void _fastcall mtrpMakePalette(TMTRPALETTE *mtrpalette);

// Запросить число цветов в палитре матрицы
// Максимальное число цветов - 256
int _fastcall mtrpGetCount(TMTRPALETTE *mtrpalette); 

// Установить число цветов в палитре матрицы
// Максимальное число цветов - 256
int _fastcall mtrpPutCount(TMTRPALETTE *mtrpalette, int count);

#ifdef __cplusplus

class  _DLLCLASS  TMtrPalette : public TBaseColors
{
 public:

   // Конструктор

   TMtrPalette ();

   // Стиль палитры

   enum
   {
     ONLYSHADOW = MTRPONLYSHADOW,  // Только тени (палитра игнорируется)
     GRAY       = MTRPGRAY,        // Полутоновая палитра
     COLOR      = MTRPCOLOR,       // Цветная палитра
   };

   // Запросить/Установить число цветов в палитре матрицы
   // Максимальное число цветов - 256

   int Count() { return GetColorCount(); }
   int Count(int count)
      {
        //if (count < 16) count = 16;
        if (count < 1) count = 1;  
        return SetColorCount(count);
      }

protected:

   // Заполнение палитры

   void MakePalette();

public:

   // Восстановить палитру матрицы

   void RestorePalette() { MakePalette(); }

   // Запросить/Установить стиль отображения

   int  Style()          { return ColorStyle; }
   void Style(int style);

   // Присваивание класса  TMtrPalette

  TMtrPalette& operator= (TMtrPalette &mtrpalette);
   
};
#else

typedef TBaseColors TMtrPalette;  

#endif // __cplusplus

#endif

