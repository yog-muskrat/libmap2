#ifndef MSRSTPAL_H
#define MSRSTPAL_H

#ifndef MAPCNT_H
  #include "Mapcnt.h"
#endif

#ifndef MAPACCES_H
  #include "Mapacces.h"
#endif

#ifndef MWCONTRL_H
  #include "mwcontrl.h"
#endif

typedef struct RSTCOLORSPARM  // ПАРАМЕТРЫ СОЗДАНИЯ ДИАЛОГА "Палитра растра"
{
  TWindow*  MapListWindow;     // Указатель на оконный класс диалога "Список растров"
  TWindow*  ColorDialog;       // Указатель на оконный класс диалога "Палитра растра"
  HWND      HwndMessage;       // Идентификатор окна документа
  long int  RstNumber;         // Номер активного растра
  COLORREF  RstPalette[256];   // Палитра растра
  COLORREF  SavePalette[256];  // Палитра растра(НЗ)
  char      IndexColor[256];   // Массив отображения цветов палитры
  char      SaveIndexColor[256];// Массив отображения цветов палитры(НЗ)
  COLORREF  AdditionalColors[16]; // Дополнительный набор для палитры Windows   
  long int  ColorsCount;       // Количество цветов растра
  char      FlagApply;         // Флаг активности кнопки "Применить"
  char      FlagWriteToFile;   // Флаг записи изменений в файл (изменение цветов)
  char      FlagWindowsPalette;// Флаг использования стандартной палитры Windows
  char      FlagChange;        // Флаг состоявшихся изменений
  char      FlagWriteToFile_CancelColor;   // Флаг записи изменений в файл (отключение цветов) 
  char      Reserve[7];
}
  RSTCOLORSPARM;

 class TRstPaletteWindow;
 class TRstColorWindow;

//++++++++++++++++++++++++++++++++++++++++++++++++++
//+++   Класс выбора цвета в окне диалога        +++
//++++++++++++++++++++++++++++++++++++++++++++++++++

class TSelectColRst : public TWindow
{
 public:
  TSelectColRst(TWindow* parent,TMapAccess* mapAccess,
                RSTCOLORSPARM* colorsParam);

  // Деструктор
  ~TSelectColRst();

  // Пометить крестом выбранный цвет в палитре
  virtual void PaintMarcer(int color);

  void Paint(TDC& dc, bool, TRect&);

  // Выбрать цвет в палитре нажатием левой кнопки мыши
  void EvLButtonDown(UINT modKeys, TPoint& point);

  // Активизировать стандартный диалог выбора цвета в палитре
  //         нажатием правой кнопки мыши
  void EvRButtonUp(uint modKeys, TPoint& point);

  // Отслеживание цвета, над которым движется указатель мыши  
  // Посылается сообщение родительскому окну
  void EvMouseMove(uint modKeys, TPoint& point);

 protected:

  TWindow *   Parent;
  TMapAccess* MapAccess;

  // ПАРАМЕТРЫ СОЗДАНИЯ ДИАЛОГА "Палитра растра"
  RSTCOLORSPARM* ColorsParam;

  int dx, dy, hc;
  int BoxW,BoxH;

 private:
  // Преобразовать палитру COLORREF к типу LOGPALETTE
  LOGPALETTE * InitLogPalette(COLORREF * palette, int colorCount);
  LOGPALETTE* RstLogPalette;

  DECLARE_RESPONSE_TABLE(TSelectColRst);
};

//++++++++++++++++++++++++++++++++++++++++++++++++++
//+++ Класс блока диалога для выбора             +++
//+++ устанавливаемого цвета из палитры растра   +++
//++++++++++++++++++++++++++++++++++++++++++++++++++
class TRstPaletteDialog : public TDialog
{
 public:

   TRstPaletteDialog(TWindow* parent,TMapAccess* mapAccesC,
                   RSTCOLORSPARM* colorsParam,
                   int* index,
                   int resId, TModule * module);

   // Деструктор
   ~TRstPaletteDialog();

   // Перерисовать диалог
   void EvPaint();

 private:
   void SetupWindow();
   // ПАРАМЕТРЫ СОЗДАНИЯ ДИАЛОГА "Палитра растра"
   RSTCOLORSPARM*  ColorsParam;

 private:
   TRstPaletteWindow* RstPaletteWindow;
   TStatic*           PaletteBorder;
   TRstColorWindow*   RstColorWindow;
   TStatic*           RstColBorder;

   int *          Index;
   COLORREF       Color;

   DECLARE_RESPONSE_TABLE(TRstPaletteDialog);
};



//++++++++++++++++++++++++++++++++++++++++++++++++++
//+++ Класс рисования выбранного цвета           +++
//++++++++++++++++++++++++++++++++++++++++++++++++++
class TRstColorWindow : public TWindow
{
 public:
    TRstColorWindow(TWindow* parent, COLORREF* color);

    // Деструктор
    ~TRstColorWindow() {};

    void Paint(TDC& dc, bool erase, TRect& rect);

 private:
   COLORREF* Color;

   DECLARE_RESPONSE_TABLE(TRstColorWindow);
};




//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++   Класс выбора устанавливаемого цвета из палитры растра   +++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class TRstPaletteWindow : public TSelectColRst
{
 public:
  TRstPaletteWindow(TWindow* parent,TMapAccess* mapAccess,
                RSTCOLORSPARM* colorsParam, int * index);

  // Выбрать цвет в палитре нажатием левой кнопки мыши
  void EvLButtonDown(UINT modKeys, TPoint& point);

  // Активизировать стандартный диалог выбора цвета в палитре
  //         нажатием правой кнопки мыши
  void EvRButtonUp(uint modKeys, TPoint& point);

  // Пометить крестом выбранный цвет в палитре
  void PaintMarcer(int color);

  private:
  int * Index;

  DECLARE_RESPONSE_TABLE(TRstPaletteWindow);
};

#endif
