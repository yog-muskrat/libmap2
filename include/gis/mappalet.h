
#if !defined(MAPPALET_H)
#define MAPPALET_H

#ifndef MAPMACRO_H
  #include "mapmacro.h"
#endif

//++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++ ������� ���������� ������� �������� ������ +++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define INDEX_MAP    0              // �����
#define INDEX_RST    1              // �����
#define INDEX_MTR    2              // �������(�����)
#define INDEX_MTQ    3              // ������� ������� 

#ifndef NUMBERTURN  
#ifndef WINCE
 #define BACKGROUNDCOLOR  0x0CECECEL    // ���� ����    
#else
 #define BACKGROUNDCOLOR  0x0FFFFFFL    // ���� ����    
#endif
#else
#define BACKGROUNDCOLOR  0x00C0C0C0L  // ���� ����      
#endif

typedef struct TMAPPALETTE
{
    COLORREF PaletteShare[256];  // ����� �������
    char     SetPaletteOrder[4]; // ������� ��������� ������ ����������
    COLORREF BACKGROUND;         // ���� ����
    int      COUNTCOLOR;         // ���������� ����������� ������ ����� ������� (<=256)
}
 TMAPPALETTE;

// ������������� ������
void _fastcall mpalInit(TMAPPALETTE *mappalette);

// ������� ����� �������
void _fastcall mpalClearPalette(TMAPPALETTE *mappalette);

// ��������� ����� ���� � ����� �������
void _fastcall mpalSetBackGround(TMAPPALETTE *mappalette);

// ���������� ������� ��������� � ����� �������
void _fastcall mpalSetPalette(TMAPPALETTE *mappalette,
                              int CountColorDoc, COLORREF* palette,
                              unsigned char* index);

// ���������� ������� DIB ����� ��������
void _fastcall mpalSetPaletteDib(TMAPPALETTE *mappalette);

#ifdef __cplusplus
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ ����� "��������� ������� ���������" +++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TMapPalette : public TMAPPALETTE // ****************
{                                                // ** MAPPALETTE **
                                                 // ****************
  public :

    TMapPalette();

   ~TMapPalette() {}

    // ���������/������ ����� ����
    COLORREF BackGround(COLORREF color) {return BACKGROUND=color;}
    COLORREF BackGround() {return BACKGROUND;}

    // �������� ����� �������
    void ClearPalette();

    // ���������/������ ���������� ����������� ������ ����� �������
    int CountColor(int countColor) {return COUNTCOLOR=countColor;}
    int CountColor() {return COUNTCOLOR;}

    // ���������� ���� ���� � ����� �������
    void SetBackGround();

    // �������� ������� ��������� � ����� �������
    void SetPalette(int CountColor, COLORREF* palette, unsigned char* index);

    // ��������� ������� DIB ����� ��������
    void SetPaletteDib();

};
#else

typedef TMAPPALETTE TMapPalette;   

#endif    // __cplusplus

#endif    // DOCPALET_H
