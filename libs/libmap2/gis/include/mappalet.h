
#if !defined(MAPPALET_H)
#define MAPPALET_H

#ifndef MAPMACRO_H
  #include "mapmacro.h"
#endif

//++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++ Индексы документов массива структур палитр +++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define INDEX_MAP    0              // Карта
#define INDEX_RST    1              // Растр
#define INDEX_MTR    2              // Матрица(растр)
#define INDEX_MTQ    3              // Матрица качеств 

#ifndef NUMBERTURN  
#ifndef WINCE
 #define BACKGROUNDCOLOR  0x0CECECEL    // Цвет фона    
#else
 #define BACKGROUNDCOLOR  0x0FFFFFFL    // Цвет фона    
#endif
#else
#define BACKGROUNDCOLOR  0x00C0C0C0L  // Цвет фона      
#endif

typedef struct TMAPPALETTE
{
    COLORREF PaletteShare[256];  // Общая палитра
    char     SetPaletteOrder[4]; // Порядок установки палитр документов
    COLORREF BACKGROUND;         // Цвет фона
    int      COUNTCOLOR;         // Количество заполненных цветов общей палитры (<=256)
}
 TMAPPALETTE;

// Инициализация данных
void _fastcall mpalInit(TMAPPALETTE *mappalette);

// Очистка общей палитры
void _fastcall mpalClearPalette(TMAPPALETTE *mappalette);

// Установка цвета фона в общую палитру
void _fastcall mpalSetBackGround(TMAPPALETTE *mappalette);

// Добавление палитры документа в общую палитру
void _fastcall mpalSetPalette(TMAPPALETTE *mappalette,
                              int CountColorDoc, COLORREF* palette,
                              unsigned char* index);

// Заполнение палитры DIB общей палитрой
void _fastcall mpalSetPaletteDib(TMAPPALETTE *mappalette);

#ifdef __cplusplus
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ КЛАСС "НАСТРОЙКА ПАЛИТРЫ ДОКУМЕНТА" +++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TMapPalette : public TMAPPALETTE // ****************
{                                                // ** MAPPALETTE **
                                                 // ****************
  public :

    TMapPalette();

   ~TMapPalette() {}

    // Установка/запрос цвета фона
    COLORREF BackGround(COLORREF color) {return BACKGROUND=color;}
    COLORREF BackGround() {return BACKGROUND;}

    // Очистить общую палитру
    void ClearPalette();

    // Установка/запрос количества заполненных цветов общей палитры
    int CountColor(int countColor) {return COUNTCOLOR=countColor;}
    int CountColor() {return COUNTCOLOR;}

    // Установить цвет фона в общую палитру
    void SetBackGround();

    // Добавить палитру документа в общую палитру
    void SetPalette(int CountColor, COLORREF* palette, unsigned char* index);

    // Заполнить палитру DIB общей палитрой
    void SetPaletteDib();

};
#else

typedef TMAPPALETTE TMapPalette;   

#endif    // __cplusplus

#endif    // DOCPALET_H
