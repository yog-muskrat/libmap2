
#ifndef MTRPALET_H
#define MTRPALET_H

#ifndef  MAPMACRO_H
 #include "mapmacro.h"
#endif

#ifndef BASCOLOR_H
 #include "bascolor.h"
#endif

typedef BASECOLORS TMTRPALETTE;

enum                       // ����� �������
{
  MTRPONLYSHADOW   = -1,   // ������ ���� (������� ������������)
  MTRPGRAY         =  0,   // ����������� �������
  MTRPCOLOR        =  1,   // ������� �������
};

enum                       // ���� ����                 
{
  MTRSHADOW_NONE   =  0,   // ���� �����������
  MTRSHADOW_PALE   =  1,   // �������
  MTRSHADOW_WEAK   =  2,   // ������
  MTRSHADOW_MIDDLE =  4,   // �������
  MTRSHADOW_HEAVY  =  8,   // �������
  MTRSHADOW_DEEP   = 16,   // ��������
};

// ������������� ������
void _fastcall mtrpInit(TMTRPALETTE *mtrpalette);

// ���������� �����
void _fastcall mtrpStyle(TMTRPALETTE *mtrpalette, int style);

//  ��������� ���������� ����������� � �������� �������
void _fastcall mtrpMakePalette(TMTRPALETTE *mtrpalette);

// ��������� ����� ������ � ������� �������
// ������������ ����� ������ - 256
int _fastcall mtrpGetCount(TMTRPALETTE *mtrpalette); 

// ���������� ����� ������ � ������� �������
// ������������ ����� ������ - 256
int _fastcall mtrpPutCount(TMTRPALETTE *mtrpalette, int count);

#ifdef __cplusplus

class  _DLLCLASS  TMtrPalette : public TBaseColors
{
 public:

   // �����������

   TMtrPalette ();

   // ����� �������

   enum
   {
     ONLYSHADOW = MTRPONLYSHADOW,  // ������ ���� (������� ������������)
     GRAY       = MTRPGRAY,        // ����������� �������
     COLOR      = MTRPCOLOR,       // ������� �������
   };

   // ���������/���������� ����� ������ � ������� �������
   // ������������ ����� ������ - 256

   int Count() { return GetColorCount(); }
   int Count(int count)
      {
        //if (count < 16) count = 16;
        if (count < 1) count = 1;  
        return SetColorCount(count);
      }

protected:

   // ���������� �������

   void MakePalette();

public:

   // ������������ ������� �������

   void RestorePalette() { MakePalette(); }

   // ���������/���������� ����� �����������

   int  Style()          { return ColorStyle; }
   void Style(int style);

   // ������������ ������  TMtrPalette

  TMtrPalette& operator= (TMtrPalette &mtrpalette);
   
};
#else

typedef TBaseColors TMtrPalette;  

#endif // __cplusplus

#endif

