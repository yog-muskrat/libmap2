
#ifndef BASCOLOR_H
#define BASCOLOR_H

#ifndef MAPMACRO_H
  #include "mapmacro.h"
#endif

#define COLORSNUMBER  260            

typedef struct BASECOLORS
{
  COLORREF Palette[COLORSNUMBER];    // ����� �����
  COLORREF BaseColors[COLORSNUMBER]; // ������ ����� �����
  unsigned char Function[COLORSNUMBER]; // ������� �������������� ������� �����  
                                        // � ������ ������� � �������������
  int ModifyFlag;                    // ���� ���������
  int Bright;                        // ������� ������� (�� -16 �� 16)
  int Contrast;                      // ������������� ������� (�� -16 �� 16)
  int Number;                        // ������������ ���������� ������ (< 256)
  int PaletteNumber;                 // ����� ������� �������
  int ColorStyle;                    // ����� �������   
  int NonlinearBright;               // ����������� ��������� ������� �� ���������� ����������� (�� 0 �� 64) 
                                     // (������ ��� ������� 16,24,32 ��� �� ������)
  int Transparent;                   // ��� ����� ����������� (�� 0 �� 100%) 
}
  BASECOLORS;

#ifdef BUILD_DLL

// ������������� ������
void bcInit(BASECOLORS * base);

// ������������� ������
void bcInitData(BASECOLORS * base,COLORREF * color,int number);

// ���������������� ����� �����
int bcInitBaseColors(BASECOLORS * base, COLORREF * color, int count);

// ���������� ���� � ������� ����� ("������")
COLORREF bcSetColor(BASECOLORS * base, COLORREF color, int index);

// ���������� �������
int bcSetBright(BASECOLORS * base, int bright);

// ���������� ������� (��������������)                  
int bcSetNonlinearBright(BASECOLORS * base, int bright);

// ���������� �������������
int bcSetContrast(BASECOLORS * base, int contrast);

// ���������� ����� �������
int bcSetColorStyle(BASECOLORS * base, int colorstyle);

// ������������� ������� � ������ ������� � �������������
// ���������� ����� ��������������� �������
COLORREF* bcBuildColors(BASECOLORS * base);

// ��������� ���������� ������ �����
int bcSetColorCount(BASECOLORS * base, int count);  
 
// ������ ������� �������� ����� ����� �� �������
COLORREF bcGetBaseColor(BASECOLORS * base, int index);

// ������ޣ� ����� �� CMYK � Rgb  
COLORREF  bcCmykToRgb(LONG * color);

// ������������ ���������������� �������              
// ���������������� ������� ����������� � �������������� �ң�
// ������ (����������, ��������������, ���������), �������� �������
// ���� ����������. ������������ ������������� ������ ������ ���������
// ���������� ���������� �� ���������� ����� ��������� � ���������.
// firstColor - ����� ���������� ����� ������� ���������
// mediumColor - ����� �������������� ����� (��������� �������
//               ���������, ���������� ������� ���������)
// lastColor - ����� ��������� ����� ������� ���������
// count  - ����� ��������� � �������
// mediumPosition - ����� �������������� ����� � �������,
//                  (����� �� 0 �� count-1)
// ��� ������ ���������� ����
int bcMakeTwoIntervalPalette(BASECOLORS * base,
                             COLORREF  firstColor,
                             COLORREF  mediumColor,
                             COLORREF  lastColor,
                             int count,
                             int mediumPosition);
#endif


#ifdef __cplusplus

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++               ����� �����                           ++++
//+++            ( <256)                                  ++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class  _DLLCLASS TBaseColors : public BASECOLORS
{
  public :

 TBaseColors();

 TBaseColors(COLORREF * color,int number);

 ~TBaseColors(){};

  // ���������������� ����� �����
  // ��������� �� ������� � ���������� ������ (<256 )
  // ��� ������ ���������� 0

  int InitBaseColors(COLORREF * color,int index);

  // ���������� ���� � ������� ����� ("������")
  // index ������ 256
  // ��� ������ ���������� 0

  COLORREF SetColor(COLORREF color,int index);

  // ������ �������� ����� ����� �� �������

  COLORREF GetColor(int index)
  { if ((unsigned)index >= (unsigned)Number) return 0;
    return Palette[index];}

  // ������ ������� �������� ����� ����� �� �������

  COLORREF GetBaseColor(int index)
   { if ((unsigned)index >= (unsigned)Number) return 0;
     return BaseColors[index]; }

  // ���������� ������� �� ���������

  COLORREF * SetDefaultColors();

  // ������/��������� ���������� ������ �����

  int GetColorCount() { return Number; }
  int SetColorCount(int count)
     {
       if (count < 0) count = 0;
        else
         if (count > COLORSNUMBER) count = COLORSNUMBER;

       return (Number = count);
     }

  // ������ ������ ������� �����

  COLORREF * GetPalette() { return &Palette[0]; }

  // ������ ������ ����������� �������

  COLORREF * GetStandardPalette() { return &BaseColors[0]; }

  // ��������� �������

  int GetBright(void) { return Bright; }

  // ���������� ������� (��������)

  int SetBright(int bright);

  // ���������� ������� (��������������)                
  //  factor - ����������� �������� (�� -32 �� 32)
  //           ������� �������� = 1 + factor/8
  int SetNonlinearBright(int factor);

  // ��������� ������ ��������� ������� ����� 
  // (������ ��� ������� 16,24,32 ��� �� ������)
  // ����������: (�� 0 �� 40)
  // 0 - ��������� ������� ����� ����������� ��������
  // 32 - ��������� ������� ����� �� ���������� �����������
  int GetNonlinearBright(void) { return NonlinearBright; }

  // ��������� �������������

  int GetContrast(void) { return Contrast; }

  // ���������� �������������

  int SetContrast(int contrast);

  // ��������� ����� �������

  int GetColorStyle(void) { return ColorStyle; }

  // ���������� ����� �������

  int SetColorStyle(int colorstyle);

  // ������������ ������  TBaseColors

  TBaseColors& operator= (TBaseColors &colors);

protected :

  // ������������� ������� � ������ ������� � �������������
  // ���������� ����� ��������������� �������

  COLORREF *  BuildColors();
};

#else

typedef BASECOLORS TBaseColors;

#endif  // __cplusplus

#endif
