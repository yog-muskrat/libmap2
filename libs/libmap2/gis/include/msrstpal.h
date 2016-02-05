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

typedef struct RSTCOLORSPARM  // ��������� �������� ������� "������� ������"
{
  TWindow*  MapListWindow;     // ��������� �� ������� ����� ������� "������ �������"
  TWindow*  ColorDialog;       // ��������� �� ������� ����� ������� "������� ������"
  HWND      HwndMessage;       // ������������� ���� ���������
  long int  RstNumber;         // ����� ��������� ������
  COLORREF  RstPalette[256];   // ������� ������
  COLORREF  SavePalette[256];  // ������� ������(��)
  char      IndexColor[256];   // ������ ����������� ������ �������
  char      SaveIndexColor[256];// ������ ����������� ������ �������(��)
  COLORREF  AdditionalColors[16]; // �������������� ����� ��� ������� Windows   
  long int  ColorsCount;       // ���������� ������ ������
  char      FlagApply;         // ���� ���������� ������ "���������"
  char      FlagWriteToFile;   // ���� ������ ��������� � ���� (��������� ������)
  char      FlagWindowsPalette;// ���� ������������� ����������� ������� Windows
  char      FlagChange;        // ���� ������������ ���������
  char      FlagWriteToFile_CancelColor;   // ���� ������ ��������� � ���� (���������� ������) 
  char      Reserve[7];
}
  RSTCOLORSPARM;

 class TRstPaletteWindow;
 class TRstColorWindow;

//++++++++++++++++++++++++++++++++++++++++++++++++++
//+++   ����� ������ ����� � ���� �������        +++
//++++++++++++++++++++++++++++++++++++++++++++++++++

class TSelectColRst : public TWindow
{
 public:
  TSelectColRst(TWindow* parent,TMapAccess* mapAccess,
                RSTCOLORSPARM* colorsParam);

  // ����������
  ~TSelectColRst();

  // �������� ������� ��������� ���� � �������
  virtual void PaintMarcer(int color);

  void Paint(TDC& dc, bool, TRect&);

  // ������� ���� � ������� �������� ����� ������ ����
  void EvLButtonDown(UINT modKeys, TPoint& point);

  // �������������� ����������� ������ ������ ����� � �������
  //         �������� ������ ������ ����
  void EvRButtonUp(uint modKeys, TPoint& point);

  // ������������ �����, ��� ������� �������� ��������� ����  
  // ���������� ��������� ������������� ����
  void EvMouseMove(uint modKeys, TPoint& point);

 protected:

  TWindow *   Parent;
  TMapAccess* MapAccess;

  // ��������� �������� ������� "������� ������"
  RSTCOLORSPARM* ColorsParam;

  int dx, dy, hc;
  int BoxW,BoxH;

 private:
  // ������������� ������� COLORREF � ���� LOGPALETTE
  LOGPALETTE * InitLogPalette(COLORREF * palette, int colorCount);
  LOGPALETTE* RstLogPalette;

  DECLARE_RESPONSE_TABLE(TSelectColRst);
};

//++++++++++++++++++++++++++++++++++++++++++++++++++
//+++ ����� ����� ������� ��� ������             +++
//+++ ���������������� ����� �� ������� ������   +++
//++++++++++++++++++++++++++++++++++++++++++++++++++
class TRstPaletteDialog : public TDialog
{
 public:

   TRstPaletteDialog(TWindow* parent,TMapAccess* mapAccesC,
                   RSTCOLORSPARM* colorsParam,
                   int* index,
                   int resId, TModule * module);

   // ����������
   ~TRstPaletteDialog();

   // ������������ ������
   void EvPaint();

 private:
   void SetupWindow();
   // ��������� �������� ������� "������� ������"
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
//+++ ����� ��������� ���������� �����           +++
//++++++++++++++++++++++++++++++++++++++++++++++++++
class TRstColorWindow : public TWindow
{
 public:
    TRstColorWindow(TWindow* parent, COLORREF* color);

    // ����������
    ~TRstColorWindow() {};

    void Paint(TDC& dc, bool erase, TRect& rect);

 private:
   COLORREF* Color;

   DECLARE_RESPONSE_TABLE(TRstColorWindow);
};




//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++   ����� ������ ���������������� ����� �� ������� ������   +++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class TRstPaletteWindow : public TSelectColRst
{
 public:
  TRstPaletteWindow(TWindow* parent,TMapAccess* mapAccess,
                RSTCOLORSPARM* colorsParam, int * index);

  // ������� ���� � ������� �������� ����� ������ ����
  void EvLButtonDown(UINT modKeys, TPoint& point);

  // �������������� ����������� ������ ������ ����� � �������
  //         �������� ������ ������ ����
  void EvRButtonUp(uint modKeys, TPoint& point);

  // �������� ������� ��������� ���� � �������
  void PaintMarcer(int color);

  private:
  int * Index;

  DECLARE_RESPONSE_TABLE(TRstPaletteWindow);
};

#endif
