
#ifndef MTRPAI3D_H
#define MTRPAI3D_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifndef MTRBASE_H
  #include "mtrbase.h"
#endif

#ifndef MTRPALET_H
  #include "mtrpalet.h"
#endif

class _DLLCLASS TMapAccess;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ����� "���������� ����������� �������" +++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS  TMtr3D
{
 public:

  TMtr3D(TMapAccess* doc, long width=100, long height=100);
 ~TMtr3D();

  // ���������� ������� � BITMAP � ���������� ����
  HBITMAP BuildMtr3Dold(MTR3DVIEW* parm);

  // ���������� ������� � BITMAP � ���������� ����
  HBITMAP BuildMtr3D(MTL3DVIEW* parm);

  // ���������� ������� �� ����� � ���������� ����
  void Paint(HDC hDC, MTR3DVIEW* parm);

  // ���������� ������� �� ����� � ���������� ����
  void PaintEx(HDC hDC, MTL3DVIEW* parm);

  // ���������� ������� �� ����� � ���������� ����
  // ������������ ������ ��� ��������� ���� �������
  void PaintAngle(HDC hDC, MTL3DVIEW* parm);

  // ���������� ������ ������� ������
  int SetDrawSize(long width, long height);

  // ���������� �������� ������������ �����
  void SetHeightFilter(double hmin, double hmax);

  // ���������� ������� ����������
  void SetHeightWater(double height);

 protected:

  // ������� ��� DIB�
  int CreateBitmap();

  // ������� ��� DIB�
  void DeleteBitmap();

  // ���������� DIB2 �� ����������
  void PaintDevice(HDC hDC);

  // ���������� ����� � ��������� � ��������� (� DIB1)
  void ShowGrid();

  // ���������� ������� ������ � ��������� � ��������� (� DIB1)
  void ShowMatrix();

  // �������� ���� � ��������� (� DIB1)
  void PutShadow();

  // ���������� ������� � ���������� ���� (�� DIB1 � DIB2)
  void ShowMtr3D();

  // ���������� ������� DIB
  void SetPaletteDib();

  // ���������� ������� �������
  void SetPaletteMtr(int style);

  // ���������������� ������� ����
  void SetupPalette();

  COLORREF PaletteShare[260]; // ����� ������� (��������� + ����� �������) 
  HPALETTE ViewPalette;       // ������������� ������� ����

  double VisualHmin;          // �������� ������������ �����
  double VisualHmax;          //
  double HeightWater;         // ������� ����������

  long DrawWidth,DrawHeight;  // ������� ������
  int DrawCenterX;            // ����� ������������� �������
  int DrawCenterY;
  double MatrixUnitShadow;    // ��������� �������� � �����
                              // � �������� �� ������ (�����������)
  MTL3DVIEW Parm;             // ��������� ������ �������
  TMapAccess* MapDoc;         // ��������� �� TMapAccess

  BITMAPINFOHEADER* hDib1Header;
  BITMAPINFO        hDib2Header;     
  BITMAPINFO        hDib3Header;
  RGBQUAD*    hDib1Palette;
  HDC         dcDib1;
  HDC         dcDib2;
  HDC         dcDib3;
  HPALETTE    dcDib1Palette;
  HBITMAP     hBitmap1;
  HBITMAP     hBitmap2;
  HBITMAP     hBitmap3;
  void*       lpBits1;
  void*       lpBits2;
  void*       lpBits3;
  char HUGER* lpDib1;
  char HUGER* lpDib2;
  char HUGER* lpDib3;

  unsigned short* HeightBuffer;  // ��������� �� ����� �����

  int         IsBuild;           
};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ����� "���������� ����������� ������� �����" +++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS  TMtl3D
{
 public:

  TMtl3D(TMapAccess* doc);
 ~TMtl3D();

  // ���������� ������� �� ����� � ���������� ����
  void Paint(HDC hDC, MTL3DVIEW* parm);

 protected:

  // ���������� ������ ������� ������
  int SetDrawSize(int width, int height);

  // ������� ��� DIB�
  int CreateBitmap();

  // ������� ��� DIB�
  void DeleteBitmap();

  // ���������� ������� � BITMAP � ���������� ����
  HBITMAP BuildMtl3D(MTL3DVIEW* parm);

  // ���������� DIB2 �� ����������
  void PaintDevice(HDC hDC);

  // ���������� ����� � ��������� � ��������� (� DIB1)
  void ShowGrid();

  // ��������� ������������ ���� � ��������� (� DIB1)
  void AngleCut();

  // ���������� ������� ������ � ��������� � ��������� (� DIB1)
  void ShowMatrix();

  // �������� ���� � ��������� (� DIB1)
  void PutShadow();

  // ���������� ������� � ���������� ���� (�� DIB1 � DIB2)
  void Show3D();

  // ���������� ��������� ������������
  void Set3DParm(MTL3DVIEW* parm);

  // ���������� ������� ������� ������� (�������, �����)
  void SetReliefPalette(int style);

  COLORREF PaletteShare[260]; // ����� ������� (����� ������� + ���������) 

  int MaxLayerCount;          // ������������ ����� ����� ������
  int DrawWidth, DrawHeight;  // ������� ������
  int DrawCenterX;            // ����� ������������� �������
  int DrawCenterY;
  double MatrixUnitShadow;    // ��������� �������� � �����
                              // � �������� �� ������ (�����������)
  MTL3DVIEW Parm;             // ��������� ������ �������
  TMapAccess* MapDoc;         // ��������� �� TMapAccess

  BITMAPINFOHEADER* hDib1Header;
  BITMAPINFOHEADER* hDib2Header;
  HDC         dcDib1;
  HDC         dcDib2;
  HPALETTE    dcDib1Palette;
  HBITMAP     hBitmap1;
  HBITMAP     hBitmap2;
  void*       lpBits1;
  void*       lpBits2;
  char HUGER* lpDib1;
  char HUGER* lpDib2;

  unsigned short* HeightBuffer;  // ��������� �� ����� �����
  double* PowerBuffer;  // ��������� �� ����� ������� ��������� �����
  short* IndexBuffer;   // ��������� �� ����� ��������
};

#endif  // MTRPAI3D_H
