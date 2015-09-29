
#ifndef BASCOLOR_H
#define BASCOLOR_H

#ifndef MAPMACRO_H
  #include "mapmacro.h"
#endif

#define COLORSNUMBER  260            

typedef struct BASECOLORS
{
  COLORREF Palette[COLORSNUMBER];    // Цвета карты
  COLORREF BaseColors[COLORSNUMBER]; // Чистые цвета карты
  unsigned char Function[COLORSNUMBER]; // Функция преобразования каналов цвета  
                                        // с учетом яркости и контрастности
  int ModifyFlag;                    // Флаг изменения
  int Bright;                        // Яркость палитры (от -16 до 16)
  int Contrast;                      // Контрастность палитры (от -16 до 16)
  int Number;                        // Используемое количество цветов (< 256)
  int PaletteNumber;                 // Номер текущей палитры
  int ColorStyle;                    // Стиль палитры   
  int NonlinearBright;               // Коэффициент изменения яркости по нелинейной зависимости (от 0 до 64) 
                                     // (только для растров 16,24,32 бит на пиксел)
  int Transparent;                   // Вес цвета изображения (от 0 до 100%) 
}
  BASECOLORS;

#ifdef BUILD_DLL

// Инициализация данных
void bcInit(BASECOLORS * base);

// Инициализация данных
void bcInitData(BASECOLORS * base,COLORREF * color,int number);

// Инициализировать цвета карты
int bcInitBaseColors(BASECOLORS * base, COLORREF * color, int count);

// Установить цвет в палитре карты ("чистый")
COLORREF bcSetColor(BASECOLORS * base, COLORREF color, int index);

// Установить яркость
int bcSetBright(BASECOLORS * base, int bright);

// Установить яркость (параболическую)                  
int bcSetNonlinearBright(BASECOLORS * base, int bright);

// Установить контрастность
int bcSetContrast(BASECOLORS * base, int contrast);

// Установить стиль палитры
int bcSetColorStyle(BASECOLORS * base, int colorstyle);

// Преобразовать палитру с учетом яркости и контрастности
// Возвращает адрес преобразованной палитры
COLORREF* bcBuildColors(BASECOLORS * base);

// Установка количества цветов карты
int bcSetColorCount(BASECOLORS * base, int count);  
 
// Запрос чистого значения цвета карты по индексу
COLORREF bcGetBaseColor(BASECOLORS * base, int index);

// Прересчёт цвета из CMYK в Rgb  
COLORREF  bcCmykToRgb(LONG * color);

// Сформировать двухинтервальную палитру              
// Двухинтервальная палитра формируется с использованием трёх
// цветов (начального, промежуточного, конечного), задающих границы
// двух интервалов. Составляющие интенсивности цветов внутри интервала
// равномерно изменяются от начального цвета интервала к конечному.
// firstColor - адрес начального цвета первого интервала
// mediumColor - адрес промежуточного цвета (конечного первого
//               интервала, начального второго интервала)
// lastColor - адрес конечного цвета второго интервала
// count  - число элементов в палитре
// mediumPosition - номер промежуточного цвета в палитре,
//                  (число от 0 до count-1)
// При ошибке возвращает ноль
int bcMakeTwoIntervalPalette(BASECOLORS * base,
                             COLORREF  firstColor,
                             COLORREF  mediumColor,
                             COLORREF  lastColor,
                             int count,
                             int mediumPosition);
#endif


#ifdef __cplusplus

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++               ЦВЕТА КАРТЫ                           ++++
//+++            ( <256)                                  ++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class  _DLLCLASS TBaseColors : public BASECOLORS
{
  public :

 TBaseColors();

 TBaseColors(COLORREF * color,int number);

 ~TBaseColors(){};

  // Инициализировать цвета карты
  // указатель на палитру и количество цветов (<256 )
  // при ошибке возвращает 0

  int InitBaseColors(COLORREF * color,int index);

  // Установить цвет в палитре карты ("чистый")
  // index меньше 256
  // при ошибке возвращает 0

  COLORREF SetColor(COLORREF color,int index);

  // Запрос значения цвета карты по индексу

  COLORREF GetColor(int index)
  { if ((unsigned)index >= (unsigned)Number) return 0;
    return Palette[index];}

  // Запрос чистого значения цвета карты по индексу

  COLORREF GetBaseColor(int index)
   { if ((unsigned)index >= (unsigned)Number) return 0;
     return BaseColors[index]; }

  // Установить палитру по умолчанию

  COLORREF * SetDefaultColors();

  // Запрос/Установка количества цветов карты

  int GetColorCount() { return Number; }
  int SetColorCount(int count)
     {
       if (count < 0) count = 0;
        else
         if (count > COLORSNUMBER) count = COLORSNUMBER;

       return (Number = count);
     }

  // Запрос адреса палитры карты

  COLORREF * GetPalette() { return &Palette[0]; }

  // Запрос адреса стандартной палитры

  COLORREF * GetStandardPalette() { return &BaseColors[0]; }

  // Запросить яркость

  int GetBright(void) { return Bright; }

  // Установить яркость (линейную)

  int SetBright(int bright);

  // Установить яркость (параболическую)                
  //  factor - коэффициент параболы (от -32 до 32)
  //           степень параболы = 1 + factor/8
  int SetNonlinearBright(int factor);

  // Запросить способ изменение яркости цвета 
  // (только для растров 16,24,32 бит на пиксел)
  // Возвращает: (от 0 до 40)
  // 0 - изменение яркости цвета стандартным способом
  // 32 - изменение яркости цвета по нелинейной зависимости
  int GetNonlinearBright(void) { return NonlinearBright; }

  // Запросить контрастность

  int GetContrast(void) { return Contrast; }

  // Установить контрастность

  int SetContrast(int contrast);

  // Запросить стиль палитры

  int GetColorStyle(void) { return ColorStyle; }

  // Установить стиль палитры

  int SetColorStyle(int colorstyle);

  // Присваивание класса  TBaseColors

  TBaseColors& operator= (TBaseColors &colors);

protected :

  // Преобразовать палитру с учетом яркости и контрастности
  // Возвращает адрес преобразованной палитры

  COLORREF *  BuildColors();
};

#else

typedef BASECOLORS TBaseColors;

#endif  // __cplusplus

#endif
