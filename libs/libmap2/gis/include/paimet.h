
#ifndef PAIMET_H
#define PAIMET_H

#ifndef MAPGDI_H
  #include "mapgdi.h"
#endif

#ifndef MAPMETR_H
  #include "mapmetr.h"
#endif

#ifndef MAPSCRIP_H
  #include "mapscrip.h"
#endif

#define PAINTSTEP     1024       // ��� ������ DIB � ����
#define PAINTLONG    32000       // (����� ��������)

#define TESTSIZE     512                     // ������� ����� ���������
#define TESTMAX      (TESTSIZE+32)           // ����� ��������� � ��������
#define TESTSTEP     (TESTMAX/8)             // ������ ������ � ������
#define TESTBUFFER   (TESTMAX * TESTSTEP)    // ������ ������

enum OUTPUTTYPE
{
  OUTPUT_DIB    = 0,
  OUTPUT_DEVICE = 1
};

// ----------------------------------------------------------------
// ���� ������� ������������ � �������� ��������� ��������
// ----------------------------------------------------------------
#if defined(__BORLANDC__) || defined(LINUXAPI)                          // 09/03/07
typedef void _fastcall (*VISUALTABLE)(void* pm, const POLYDATAEX* data,
                                      const char * parm, float viewscale);

typedef int  _fastcall (*TESTTABLE)(void* pm, const POLYDATAEX* data,
                                     const char* parm, float viewscale);
#else
typedef void (_fastcall *VISUALTABLE)(void* pm, const POLYDATAEX* data,
					   			                           const char * parm, float viewscale);

typedef int  (_fastcall *TESTTABLE)(void* pm, const POLYDATAEX* data,
                                    const char* parm, float viewscale);
#endif

// ��������� �� ������� ������� ������� �����������     // 11/06/01
// base - ��������� �� MAPBASE
#if defined(__BORLANDC__) || defined(LINUXAPI)                          // 09/03/07
typedef void _fastcall (*DEVICETABLE)(void* base, const POLYDATAEX* data,
                                      const char* parm, float viewscale);
#else
typedef void (_fastcall *DEVICETABLE)(void* base, const POLYDATAEX* data,
                                      const char* parm, float viewscale);
#endif

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++ ����� ����������� ��'����� ����� � ����������� �������� +++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TPaintMetric : public TMapMetric
{
 public:

  TPaintMetric();
 ~TPaintMetric();

  // ���������/���������� ������������� ����� ������� ����������
  // ������� ��� ������ �� ���������� (0 - 100)
  int _fastcall GetFillIntensity();
  int _fastcall SetFillIntensity(int intensity);

  // ���������� ������� ��� DIB
  void _fastcall SetPaletteDib(COLORREF* palette, int count);

  // �������� ��� ��������� �����, ���������� � DIB
  CELL IndexPaletteShare(int index)
  { return PaletteDIB[((unsigned char)index)];}

  // ���������� ���� � ������� RGB (24 ����)
  COLORREF _fastcall GetColor24(COLORREF color);

  // ���������� ����
  COLORREF _fastcall GetColor(COLORREF color);

  // ���������� ����
  COLORREF _fastcall GetColorText(COLORREF color);

  // ���������� DIB � ����
  void _fastcall PaintDIB2WIN(HDC hdc, int x, int y);

  // ���������� ���� � DIB
  void _fastcall PaintWIN2DIB(HDC hdc, int x, int y);

 // ���������� ��������� ����� DIB � ����
 // (1 - �������� ������, 0 - �������)
 // ���������� ���������� ��������
 int SetPaintStep(int flag)
 {
#ifndef HIDEPAINTSTEP              // 17/04/06
   int Old = PaintStep;
   if (flag)
     PaintStep = PAINTSTEP;
   else
     PaintStep = PAINTLONG;
   return Old;
#else
   return PaintStep;
#endif
 }

 int GetPaintStep()
 {
   return (PaintStep != PAINTLONG);
 }

 // ��������� ������� ����������� �� ����
 // ���������� :  1 - ���� ����������, 0 - ���� �� �����
 int CheckPaintCount()
 {
   if (ObjectDrawCount++ < PaintStep)
     return 0;
   ObjectDrawCount = 0;
   return 1;
 }


  // ���������/���������� �������� ���������������� ������� �����
  // ��� ������ �� ���������� (0 - 100)
  unsigned int _fastcall GetCurrentTranslucency() const;
  unsigned int _fastcall SetCurrentTranslucency(unsigned int translucency); 

 public:

 HDC  dcWindow;         // �������� ����
 HDC  hdc;              // �������� ����������
 HDC  hdcDib;           // �������� ���������� ���������������� DIB ��� ��������
 int  Technology;       // ��� ����������

 double HorLogicalInch; // �������� ���������� � ���������� �����
                        // �� �����������
 double VerLogicalInch; // �������� ���������� � ���������� �����
                        // �� ���������
 HDC Savehdc;
 int SaveTechnology;

 double SaveHorLogicalInch;
 double SaveVerLogicalInch;

 // ������� SCRIPT-������
 SCRIPTTABLEEX ScriptTable;                                 // 05/06/07
 int IsScriptTableActive;

 // ���� ����������� ������� ����� (����, ������)
 int TopLine;                                               // 12/07/06

 // ����� ��� ��������� ���������
 char ShadowBuffer[4096];                                   // 24/07/06

 // ������� �������
 COLORREF PaletteRGB[260];          // ��� Windows-�������
 CELL     PaletteDIB[260];          // ��� Dib
#if CELLSIZE == 2                   // 10/03/08
 CELL     PaletteDIBRezerv[260];
#else
#if CELLSIZE == 1
 CELL     PaletteDIBRezerv1[260];
 CELL     PaletteDIBRezerv2[260];
 CELL     PaletteDIBRezerv3[260];
#endif
#endif
 int CurrentBright;                 // ������� ������� ������� �����
 int CurrentContrast;               // ������������� ������� ������� �����
 unsigned int CurrentTranslucency;		// ���������������� ������� �����

 COLORREF Palette[272];        // ������� �����
 COLORREF PaletteFill[272];    // ������� ������� ��������� ��������
 COLORREF PaletteCMYK[272];    // ������� ����� CMYK       // 19/02/04

 int ColorModel;               // ����������� ����� � �������������� �������� ������(0-RGB, 1-CMYK)  // 19/02/04
 long int ClearColor;          // ���� ������� ������� ��������� � DIB       // 19/02/04
                               // (��� RGB-0x0FFFFFFL, ��� CMYK-0x0000000L)
 int ColorCount;               // ���������� ������ � CMYK ������� �����     // 18/03/04
 int MapNumber;                // ����� �������������� �����                 // 18/03/04

 int FillIntensity;            // ������������� ����� ������� ����������
 int SaveFillIntensity;        // ������������� ��� ������
 float Intensity;              // ������� ������������� ����� ������� ����������

 double PixDeviceInPixScreen;  // �������� ���������� � ������� ������
 double PixDeviceFontIn100Mkm; // �������� ���������� � ������� �����
                               // ���������� (��� ������)
                               
 double SavePixDeviceInPixScreen;
 double SavePixDeviceFontIn100Mkm;

 double HorPixDeviceInMkm;   // �������� ���������� � ���
 double VerPixDeviceInMkm;   // �������� ���������� � ���
 double PixDeviceFontInMkm;  // �������� ���������� ������ ������
                             // � ��� ������ ��������

 double SaveHorPixDeviceInMkm;
 double SaveVerPixDeviceInMkm;
 double SavePixDeviceFontInMkm;

 DRAWSIZE  szSeek;                  // ������ � ������ ������� ������  // 01/12/00
 DRAWSIZE  szSeekSq;                // ������ � ������ ������� ������ ��� ���������

 int       ObjectDrawCount;         // ������� ���������� � DIB ��������
 int       PaintStep;               // ��� ������ DIB � ����

 VISUALTABLE* DibFunc;              // ��������� �� ������� ������� ��� DIB
 DEVICETABLE* DeviceFunc;           // ��������� �� ������� �������

 enum TYPEOUTPUT { DIB = 0, DEVICE = 1 };
 int TypeOutput;                    // ������ �����������
 int VisualType;                    // ��� ������������ �����

 unsigned char
        ArrayIndexMap[272];         // ������ �������� ������������ ������  // 23/07/02

 int SelectColor;                   // ���� ��������� �������� �� �����
                                    // (-1 - �� ��������)
 int SelectThick;                   // ������� ����� ��������� ��������
};

// ���������� ����������
extern int PrintTechnology;   // 23/04/01

// ������ ������� �����������
extern DRAWSIZE PrintDrawSize;

// ������� ������� ���������
extern DEVICETABLE FillFunc[256];     // ��������� � ��������
extern DEVICETABLE FillFuncPS[256];   // ��������� � �������� (��� PostScript)
extern DEVICETABLE GlassFunc[256];    // ��������� ����������
extern DEVICETABLE ContourFunc[256];  // ��������� ���������
                                      // 28/01/03
extern DEVICETABLE SquareFunc[256];   // ��������� ������� ��������
extern DEVICETABLE LineFunc[256];     // ��������� �����, ��������, ���������
extern DEVICETABLE TextFunc[256];     // ��������� ��������, ��������

// �������������
void _fastcall pmetInit(TPaintMetric* pmet); // 09/07/01

// ������������
void _fastcall pmetFree(TPaintMetric* pmet); // 09/07/01

// ���������� ������������� ����� ������� ����������
// ������� ��� ������ �� ���������� (0 - 100)
int _fastcall pmetSetFillIntensity(TPaintMetric* pmet, int intensity);
int _fastcall pmetGetFillIntensity(TPaintMetric* pmet);

// �������� ���������� � 1 ����� �� ��������� � �����������
double _fastcall pmetGetHorPixDeviceInMetr(TPaintMetric* pmet);
double _fastcall pmetGetVerPixDeviceInMetr(TPaintMetric* pmet);

// ���������� �������� ���������� (�� ��������� ������
// � ���������� ������ ��������� RestoreHDCMap)
#ifdef __cplusplus   // 25/04/01
void _fastcall pmetSetHDCMap(TPaintMetric* pmet, HDC hDC, 
                             double horPixInInch = -1, double verPixInInch = -1);
#else
void _fastcall pmetSetHDCMap(TPaintMetric* pmet, HDC hDC, 
                             double horPixInInch, double verPixInInch);    // 10/02/05
#endif

// ������������ �������� ����������
void _fastcall pmetRestoreHDCMap(TPaintMetric* pmet);

// ���������� ������� ����� � ������� ��������� �������� // 25/04/01
void _fastcall pmetSetPaletteMap(TPaintMetric* pmet, int count, COLORREF* palette, int intensity);

// ��������� �������� ������ ������ ����� (0 - RGB, 1 - CMYK)  // 03/03/04
int  _fastcall pmetGetColorModel(TPaintMetric* pmet);

// ���������� �������� ������ ������ ����� (0 - RGB, 1 - CMYK) // 03/03/04
void  _fastcall pmetSetColorModel(TPaintMetric* pmet, int colorModel);

// ���������� CMYK-������� �����             // 02/03/04
//void _fastcall pmetSetPaletteCMYK(TPaintMetric* pmet, int Count, long int* palette);
void _fastcall pmetSetPaletteCMYK(TPaintMetric* pmet, int Count, long int* palette, long int number, int intensity);

// ���������� ���� ������� ���������� �������
COLORREF _fastcall pmetGetColorMapFill(TPaintMetric* pmet, unsigned char index);

// ��������� ����� ������ �������
COLORREF _fastcall pmetGetColor(TPaintMetric* pmet, COLORREF color);

// ���������� ���� ������� ���������� �������
COLORREF _fastcall pmetGetColorFill(TPaintMetric* pmet, COLORREF color);

// �������� ���������� (������� ������ -> ������� ����������)
long _fastcall pmetScreen2Device(TPaintMetric* pmet, float pixel);

// �������� ���������� (0.001 �� -> ������� ����������)
long _fastcall pmetMetric2Device(TPaintMetric* pmet, long metric);

// ���������� ���� �� ������� �������
COLORREF _fastcall pmetGetColorMap(TPaintMetric* pmet, unsigned char index);

// ������������ ��������� ��������
void _fastcall pmetVerticalFrameColorShade(TPaintMetric* pmet,
                                           const POLYDATAEX* pdata,
                                           const IMGVECTORGRADIENT * parm,
                                           float viewscale);

//-----------------------------------------------------------------
// ������� ��������� (��������� � ��������)
//-----------------------------------------------------------------

void _fastcall pmetLineThin(void* pm, const POLYDATAEX* data,
                            const char* parm, float scaleview);
void _fastcall pmetLine(void* pm, const POLYDATAEX* data,
                        const char* parm, float scaleview);
void _fastcall pmetDot(void* pm, const POLYDATAEX* data,
                       const char* parm, float scaleview);
void _fastcall pmetShiftDot(void* pm, const POLYDATAEX* data,
                            const char* parm, float scaleview);

void _fastcall pmetSquare(void* pm, const POLYDATAEX* data,
                          const char* parm, float scaleview);
void _fastcall pmetSquareCross(void* pm, const POLYDATAEX* data,
                               const char* parm, float scaleview);
void _fastcall pmetMultiSquareMark(void* pm, const POLYDATAEX* data,
                                   const char* parm, float scaleview);
void _fastcall pmetMultiMark(void* pm, const POLYDATAEX* data,
                             const char* parm, float scaleview);
void _fastcall pmetCircle(void* pm, const POLYDATAEX* data,
                          const char* parm, float scaleview);

void _fastcall pmetText(void* pm, const POLYDATAEX* data,
                        const char* parm, float scaleview);
void _fastcall pmetTrueText(void* pm, const POLYDATAEX* data,
                            const char* parm, float scaleview);
void _fastcall pmetTrueType(void* pm, const POLYDATAEX* data,
                            const char* parm, float scaleview);

void _fastcall pmetTemplate(void* pm, const POLYDATAEX* data,
                            const char* parm, float scaleview);

// ����� ���������� (147)
void _fastcall pmetDraw(void* pm, const POLYDATAEX* data,
                        const char* parm, float scaleview);

// ��������� ��������� ��������� �������� (153)
void _fastcall pmetShadeSquare(void* pm, const POLYDATAEX * data,
                               const char * parm, float viewscale);

// ������������� ���� � ������ ������� � ������������� (154)
void _fastcall pmetSquareGlass(void * pm, const POLYDATAEX* data,
                               const char* parm, float scaleview);

// ������������� ���� � ������ �������, ������������� � ���� (164)
void _fastcall pmetSquareToneGlass(void * pm, const POLYDATAEX* data,
                                   const char* parm, float scaleview);  // 05/01/06

// ������������� ���� � ������ �������, �������������, ���� � ������������ (167)
void _fastcall pmetPolygonGlass(void * pm, const POLYDATAEX* data,
                                const char* parm, float scaleview);  // 26/01/09

// ������������� ���� � ������ �������, �������������, ���� � ������������ (168)
void _fastcall pmetLineGlass(void * pm, const POLYDATAEX* data,
                             const char* parm, float viewscale);

// ���������� ��������� ������, ����������� ���������� ���������
void _fastcall pmetSquareVector(void* pm, const POLYDATAEX* pdata,
                                const char* Parm, float viewscale);

// �������� ��������� ����� (158)
void _fastcall pmetDashLine(void* pm, const POLYDATAEX* data,
                            const char* parm, float viewscale);

// ����������� ������� (221)
void _fastcall pmetCallPaint(void* pm, const POLYDATAEX * data,
                             const char * parm, float scaleview);

//-----------------------------------------------------------------
// ������� ��������� (��������� � ��������)
//-----------------------------------------------------------------

// ���������
void _fastcall DeviceSquare(TPaintMetric* pmet, const POLYDATAEX* data, IMGSQUARE* parm);

// ����� ��������
void _fastcall DeviceLine(TPaintMetric* pmet, const POLYDATAEX* data, IMGLINE* parm, double thick);

// ����� �������� ������������
void _fastcall DeviceThickenLine(TPaintMetric* pmet, const POLYDATAEX* data, COLORREF color,
                                 double thick, double thickEnd);

                                 // ����� �������� ������������ � �������� �� ������
void _fastcall DeviceMiddleThickenLine(TPaintMetric* pmet, const POLYDATAEX* data, COLORREF color,
                                 double thick, double thickMiddle);
// ����� ��������
void _fastcall DeviceLinePlotter(TPaintMetric* pmet, const POLYDATAEX* data, IMGLINE* parm);

// ����� ���������
void _fastcall DeviceLineDash(TPaintMetric* pmet, const POLYDATAEX* data, IMGDOT* parm, double thick);

// ����� ��������� ����������
void _fastcall DeviceShiftDash(HDC hdc, const POLYDATAEX* data, IMGDOTSHIFT* parm);

// ���������, ����������� ���������
void _fastcall DeviceSquareMark(TPaintMetric* pmet, const POLYDATAEX* data, IMGSQUAREMARK* parm, char* mask);

// ��������
void _fastcall DeviceMark(TPaintMetric* pmet, const POLYDATAEX* data, IMGMARK* parm, float scaleview);  // 25/10/01

// �������
void _fastcall deviceText(TPaintMetric* pmet, const POLYDATAEX* data, IMGTEXT* parm, float scaleview);
void _fastcall deviceTrueText(TPaintMetric* pmet, const POLYDATAEX* data, IMGTRUETEXT* parm, float scaleview);

// ������
void _fastcall deviceTrueType(TPaintMetric* pmet, const POLYDATAEX* data, IMGTRUETYPE* truetype, float scaleview);

// ����������� ����� �� ���� �����                        // 10/07/06
void _fastcall pmetDrawLine(TPaintMetric* pmet, int x1, int y1,
                                                int x2, int y2);

//  ����������� ���������                                 // 10/07/06
void _fastcall pmetPolyLine(TPaintMetric* pmet, POINT * point, int count);

//  ��������� ���������� ������� ��������� ������         // 10/07/06
void _fastcall pmetDrawSquare(TPaintMetric* pmet, POINT* point, int count);

//  ��������� �������� ���������� ������� ��������� ������   10/07/06
void _fastcall pmetDrawPolygons(TPaintMetric* pmet, const POLYDATAEX* data);

//  ���������� ��������� ������������ �����                  10/07/06
XHPEN _fastcall pmetSelectPen(TPaintMetric* pmet, int thick, unsigned long color);

//  ���������� ��������� ������������ �����               // 10/07/06
XHPEN _fastcall pmetSelectFastPen(TPaintMetric* pmet, int thick, unsigned long color);

//  ���������� ��������� ������� �������� (�����)         // 10/07/06
XHBRUSH _fastcall pmetSelectBrush(TPaintMetric* pmet, unsigned long color);

// ����� ������ ������ ��� �������                         10/07/06
void _fastcall pmetDrawText(TPaintMetric* pmet, int x, int y,
                            TCHAR * text, int length,            // 24/04/03
                            LOGFONT* font, int align, long color);

// ����� ������ ������ ��� ������� UNICODE                 05/06/07
void _fastcall pmetDrawTextUn(TPaintMetric* pmet, int x, int y,
                              WCHAR * text, int length,
                              LOGFONT* font, int align, long color);
#endif  // PAIMET_H


