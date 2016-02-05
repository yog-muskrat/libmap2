
#ifndef MTRBASE_H
#define MTRBASE_H

#ifndef RMFBASE_H
  #include "rmfbase.h"
#endif

typedef TRMFDATA TMTRDATA;

// �������� ����� ������� � ����������������, ��������� � ����������
// BUILDMTW, MTRPROJECTIONDATA.
// ���� MTRPROJECTIONDATA ����� ����, �� ������ � �������� �� ���������������.
// �������� checkdiskfreespace ���������� �������� ������� ����������
// ����� �� ����� (��� checkdiskfreespace = 0 �������� �� �����������)  
int _fastcall mtrCreate(TMTRDATA *mtrdata, const char* name,
                        BUILDMTW* MtrParm,
                        MTRPROJECTIONDATA * MtrProjectionData,
                        int checkdiskfreespace);

// �������� �����
int _fastcall mtrOpen(TMTRDATA *mtrdata, const char* mtrname, int mode);

// ����� ��������� �������� ����� � �������� �����������
// � �������� ��������� �������
//  string - ������ ����� ������ ������������ (���������� �������)
//  column - ������� ����� ������ ������������
//  direct - ����������� ������������ (0 - 15)
//  pstr   - ������ ����� ����� ������������ (���������� �������)
//  pcol   - ������� ����� ����� ������������
//  value  - �������� �������� �����
int _fastcall mtrScanPoint(TMTRDATA *mtrdata, int string, 
                           int column, int direct,
                           int *pstr, int *pcol, long *value);

// ������� ������������ �������� ������ � ������
double _fastcall mtrMinimumHeight(TMTRDATA *mtrdata);  

// ������� ������������ �������� ������ � ������
double _fastcall mtrMinHeightMeter(TMTRDATA *mtrdata);

// ������� ������������� �������� ������ � ������
double _fastcall mtrMaximumHeight(TMTRDATA *mtrdata);

// ������� ������������� �������� ������ � ������
double _fastcall mtrMaxHeightMeter(TMTRDATA *mtrdata);

// ������� ������� �������� � ������
int _fastcall mtrElementSizeBytes(TMTRDATA *mtrdata);

#ifndef HIDEMTQ            
                            

// ===========================================================
//           ������� �������   
// ===========================================================

//--------------------------------------------------------------
// �������� ����� ������� ������� � ����������������, ���������
// � ���������� MTRBUILDPARMEX, MTRPROJECTIONDATA � ��������.
//--------------------------------------------------------------
int _fastcall mtrCreateMtqFileEx(TMTRDATA *mtrdata, const char* name,
                                 BUILDMTW* MtrParm,
                                 MTRPROJECTIONDATA * MtrProjectionData,
                                 COLORREF* palette, int countpalette);

#endif

#ifdef __cplusplus

class _DLLCLASS TMtr: public TRmf
{
 public:

  // ������ ������
  TMtr();

  // ������ ��� ����� � ������������ ������ �������
  TMtr(const char* name, int mode = 0);

  // �������� �����
  int Open(const char *name, int mode = 0);

  // �������� ����� ������� � ��������� ����������������    
  // �������� checkdiskfreespace ���������� �������� ������� ����������
  // ����� �� ����� (��� checkdiskfreespace = 0 �������� �� �����������)
  int Create(const char* name, BUILDMTW* parm,
             MTRPROJECTIONDATA * mtrprojectiondata,
             int checkdiskfreespace = 1);

  // ������� ������������ �������� ������ � ������
  double MinimumHeight()  { return HeightUnitToMeter(HEADER.Minimum); }
  double MinHeightMeter() { return HeightUnitToMeter(HEADER.Minimum); }

  // ������� ������������� �������� ������ � ������
  double MaximumHeight()  { return HeightUnitToMeter(HEADER.Maximum); }
  double MaxHeightMeter() { return HeightUnitToMeter(HEADER.Maximum); }

  // ������� ������� �������� � ������
  int ElementSizeBytes() { return (ElementSize()>>3); }

  // ����� ��������� �������� ����� � �������� �����������
  // � �������� ��������� ������� (��� ���������� �������)
  //  string - ������ ����� ������ ������������ (���������� �������)
  //  column - ������� ����� ������ ������������
  //  direct - ����������� ������������ (0 - 15)
  //  pstr   - ������ ����� ����� ������������ (���������� �������)
  //  pcol   - ������� ����� ����� ������������
  //  value  - �������� �������� �����
  int ScanPoint(int string, int column, int direct,
                int& pstr, int& pcol, long& value);
};
#else

typedef TRMFDATA TMtr;  

#endif // __cplusplus

#endif  // MTRBASE_H

