
#ifndef MSPARM_H
#define MSPARM_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifndef MTREXAPI_H
  #include "mtrexapi.h"
#endif

#ifndef MTLAPI_H
  #include "mtlapi.h"
#endif

#ifndef TINAPI_H
  #include "tinapi.h"
#endif

#ifndef MAPCREAT_H
  #include "mapcreat.h"
#endif

#define _EXPORTAPI __declspec(dllexport) WINAPI

#define ABSOLUTE_HEIGHT_CODE 4  // ��� �-�� ���������� ������
#define RELATIVE_HEIGHT_CODE 1  // ��� �-�� ������������� ������

//-----------------------------------------------------------------
//   ��������� ���������� ������� �����
//-----------------------------------------------------------------
typedef struct MTRPARM
{
  BUILDMTW BuildMtw;                   

  PRIORMTRPARM PriorMtrParm;           

  RECT   RectMetr;       // ������������� ������ � ������
                         // (� ����� ������)

  DFRAME DFrameMetr;     // ������������� ������ � ������
                         // (� ��������� ������)

  char Select;           // ���� ������ � ������ ���������
                         //  (��. MAP2MTROUTPUTAREA)

  char CoordinateSystem; // ���� ������� ��������� ��� �������
                         // ������� ������ (��. MAP2MTRCOORDINATESYSTEM)

  char SelectSheetName;  // ���� ������ ���� ������ �� ������

  char Compress;         // ���� ���������� ������

  char BuildBySheets;    // �������� ������ �� ������ ������

  char UseFilter;        // ���� ������������� ������� �������� (IMH-����)

  char Reserve;          // ���� ...

  char IsPriorMtrParm;   // ���� ���������� ��������������� ������ �������
                         //  0 - ������ �� �����������;
                         //  1 - ��������� ���������� �������� �������� ����� ��������,
                         //      ���������� � �������� ������� (PriorMtrParm.AbsHeightDifference)

  HWND MapWindowHandle;  // ������������� ���� �����

  int AbsoluteHeightCode;   // ��� �-�� ���.������
  int RelativeHeightCode;   // ��� �-�� ���.������

  int AbsoluteHeightSign;   // ���� �-�� ���.������       
  int Reserve2;             

  char NameMTR[MAX_PATH];   // ��� MTW-�����
  char NameTXT[MAX_PATH];   // ��� IMH-�����
}
  MTRPARM;


#ifndef HIDEMTL    
// ��������� ���������� ������� �������� ������� �����
typedef struct MTLPARM
{
  // ��������� �������� ������� ����� (API-���������)
  BUILDMTL MtlBuildParm;  

  // ������ ������ ���������
  long Length;

  // ������������� ���� �����
  HWND MapWindowHandle;

  // ������������� ������ � ������ (� ����� ������)
  RECT RectMetr;

  // ������������� ������ � ������ (� ��������� ������)
  DFRAME DFrameMetr;

  // �������� ������ � ������
  DFRAME RegionMetr;

  // ����� ���� ����������� �����
  long ZoneNumber;

  // ���� ������ � ������ ��������� (��. MAP2MTROUTPUTAREA)
  long Select;

  // ���� "�������/�����" ��� ������� ������� ������ (��. MAP2MTRCOORDINATESYSTEM)
  long CoordinateSystem;

  // ��� �������� ������ : 0-���� ������, 1-�����, 2-��������� ����;
  long InputDataType;

  // ����� ������������� �������� ������ :
  //  0 - �������� �����
  //  1 - ���������� ������
  long InputDataForm;

  // �������� ����������� �����
  long SitProjection;

  // ��� ����������� �����
  long SitType;

  // ���� ���������� ������
  long Compress;

  // ��� ��������������� �������  
  long PicketCode;

  // ���������� ��� ��������������� �������  
  long PicketIncode;

  // ���� ������������� ������� �����  
  long UseMtw;

  // ��� ��������������� �������  
  char PicketName [MAX_PATH];

  // ��� ����������� ������� (MTL-�����)
  char NameMTL [MAX_PATH];

  // ��� ����� ������� �������
  char NameTXT [MAX_PATH];

  // ��� �������� ����� �����
  char NameINPUTMAP [MAX_PATH];

  // ��� �������� ����� ���� ������
  char NameINPUTDBF [MAX_PATH];

  // ��� �������� ���������� �����
  char NameINPUTTXL [MAX_PATH];

  // ��� ������� �����
  char NameMTW [MAX_PATH];

  // ��� ����� ��������������
  char NameRSC [MAX_PATH];

  // ���������� �������� ����������� �����
  CONSTPROJ ConstProj;

}
  MTLPARM;
#endif  // HIDEMTL

#ifndef HIDETIN
// ��������� ���������� ������� �������� TIN-������  
typedef struct TINPARM
{
  // ��������� �������� TIN-������ (API-���������)
  TINBUILD TinBuild;

  // ������ ������ ���������
  long Length;

  // ������������� ���� �����
  HWND MapWindowHandle;

  // ������������� ������ � ������ (� ����� ������)
  RECT RectMetr;

  // ������������� ������ � ������ (� ��������� ������)
  DFRAME DFrameMetr;

  // �������� ������ � ������
  DFRAME RegionMetr;

  // ���� ������ � ������ ��������� (��. MAP2MTROUTPUTAREA)
  long Select;

  // ��� ����������� ������ (TIN-�����)
  char NameTIN[MAX_PATH];

}
  TINPARM;
#endif  // HIDETIN

#ifndef HIDEMTQ
//-----------------------------------------------------------------
// ��������� ���������� ������� �������� ������� �������
//-----------------------------------------------------------------
typedef struct MTQPARM  
{
  BUILDSURFACE BuildMtq;   // ��������� �������� ������� (API-���������)

  RECT RectMetr;           // ������������� ������ � ������ (� ����� ������)

  DFRAME DFrameMetr;       // ������������� ������ � ������ (� ��������� ������)

  long int Select;         // ���� ������ � ������ ��������� (��. MAP2MTROUTPUTAREA)
  
  HWND MapWindowHandle;    // ������������� ���� �����

  long int InputDataType;  // ��� �������� ������ (0 - �����, 1 - ���� ������)

  long int DbfFieldX;      // ������ ����� � ���� ������ ��� X,Y,H
  long int DbfFieldY;
  long int DbfFieldH;

  long int Precision;      // �������� ������������� ������ � ����������
                           // �������� �����

  long int PaletteCount;             // ����� ������
  long int SmoothColorModification;  // ���� : ������� ���������
                                     // ������ �������������� �������

  long int SingleColourChange;       // ���� : ���� ��������� ��������� ������
                                     //        �������������� �������

  COLORREF Palette[256];             // �������
  COLORREF SkeletPalette[256];       // ��������� �������

  char NameMTQ[MAX_PATH];  // ��� ����������� ������� �������
  char NameMTW[MAX_PATH];  // ��� ����������� ������� �����
  char NameMAP[MAX_PATH];  // ��� �������� �����
  char NameDBF[MAX_PATH];  // ��� �������� ���� ������
}
  MTQPARM;
#endif  // HIDEMTQ

enum MAP2MTRCOORDINATESYSTEM
{
  MAP2MTR_RECTANGULAR = 0,  // ������������� (�����)
  MAP2MTR_GEOGRADUS   = 1,  // ������������� (�������)
};

enum MAP2MTROUTPUTAREA       // ������ ��������/�������� ������� 
{
  MAP2MTR_ALL          = 0,  // �������� : ������� ������ - ���� �����
                             // �������� : ������� ������ �� ���������

  MAP2MTR_FRAME        = 1,  // �������� : ������� ������ - �� RectMetr
                             // �������� : ������� ������ -> � RectMetr

  MAP2MTR_SELECT_FRAME = 2,  // �������� : ������� ������ - �� RectMetr
                             // �������� : ��� ������ ���������

  MAP2MTR_CHANGE_FRAME = 3,  // �������� : ������� ������ - �� RectMetr
                             // �������� : ��� ��������� ���������
};

enum MAP2MTLINPUTDATACOORDINATE
{
  MAP2MTL_1942_METER    = 0,  // ������� ��������� 1942 �.(�����)
  MAP2MTL_1942_GRADUS   = 1,  // ������� ��������� 1942 �.(�������)
  MAP2MTL_1942_RADIAN   = 2,  // ������� ��������� 1942 �.(�������)
  MAP2MTL_1942_GRMINSEC = 3,  // ����. �����. 1942 �.(�������,������,�������)
  MAP2MTL_LOCAL_METER   = 4,  // ������� (�����)
  MAP2MTL_WGS84_GRADUS  = 5,  // WGS-84 (�������)
  MAP2MTL_WGS84_RADIAN  = 6,  // WGS-84 (�������)
};


//-----------------------------------------------------------------
//     ��������� ���������� ������
//-----------------------------------------------------------------
typedef struct RSTBUILDPARM
{
  BUILDMTW BuildMtw;  

  RECT   RectMetr;  // ������������� ������ � ������ (� ����� ������)

  DFRAME DFrameMetr;  // ������������� ������ � ������
                      // (� ��������� ������)

  char Select;        // ���� ������ � ������ ���������
                      //  (��. MAP2MTROUTPUTAREA)

  char CoordinateSystem; // ���� ������� ��������� ��� �������
                  // ������� ������ (��. MAP2MTRCOORDINATESYSTEM)

  char SelectSheetName;  // ���� ������ ���� ������ �� ������

  char Compress;         // ���� ���������� ������

  char BuildBySheets;    // ���� ���������� �� ������

  char Free[3];

  HWND MapWindowHandle;  // ������������� ���� �����

  char Free1[4];         // ������������

  char NameRST [MAX_PATH];  // ��� RST-�����
  char NameTXT [MAX_PATH];  // ��� ���-�����
}
  RSTBUILDPARM;

 typedef struct AREAGRADUS
 {
   long LTG; long LTM; long LTS; long CorrectLT;
   long RTG; long RTM; long RTS; long CorrectRT;
   long DNG; long DNM; long DNS; long CorrectDN;
   long UPG; long UPM; long UPS; long CorrectUP;
 }
   AREAGRADUS;

typedef struct MTQPALETTEPARM    //  ��������� �������� ������� ������� �������
{
  unsigned
  long int StructSize;  // ������ ������ ��������� : sizeof (MTQPALETTEPARM)
  HWND     Handle;      // ������������� ���� ����������

  double   Minimum;     // ����������� �������� ������������ ��������������
  double   Maximum;     // ������������ �������� ������������ ��������������

  long int ResultColorCount;         // ���-�� ������ �������������� �������
  long int SmoothColorModification;  // ���� : ������� ���������
                                     //        ������ �������������� �������

  long int SingleColourChange;  // ���� : ���� ��������� ��������� ������
                                //        �������������� �������
  long int Precision;           // �������� ������������� ������ � ����������
                                // �������� �����

  COLORREF SkeletPalette[256];  // �������� (���������) �������
  COLORREF ResultPalette[256];  // �������������� �������

  char HelpName[256];  // ������ ��� ����� ".hlp"
  char Reserve[256];   // ������ ���� ����
}
  MTQPALETTEPARM;

#endif  // MSPARM_H
