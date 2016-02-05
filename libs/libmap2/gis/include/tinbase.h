
#ifndef TINBASE_H
#define TINBASE_H

#include "mapversn.h"
#include "mapsyst.h"
#include "mapdat.h"
#include "tin.h"

struct TINTRIANGLE{ // �����������
   TINTRIANGLE(DOUBLEPOINT PointA, double HeightA,
                DOUBLEPOINT PointB, double HeightB,
	        DOUBLEPOINT PointC, double HeightC):
	           PointA(PointA), HeightA(HeightA),
	           PointB(PointB), HeightB(HeightB),
                   PointC(PointC), HeightC(HeightC){}
   
   TINTRIANGLE():
      PointA(), HeightA(0),
      PointB(), HeightB(0),
      PointC(), HeightC(0){}		   
		
   // ���������� ����� �� ����� ������ ������������      
   int IsInsidePoint(const double x, const double y);
   
   // ����� �������� ������ ����������� � �������� �����
   // ���������� ����� �������� � ������ � ������� ���������
   // ��������� �����. ���������� �������� ������ � ������.
   // � ������ ������ ��� ������ ������ � � ������ ����������������
   // �������� ����� ������� ���������� ERRORHEIGHT
   double GetTriangleHeight(double x, double y);
   
   
   DOUBLEPOINT PointA,  PointB,  PointC; // ���������� �����
   double     HeightA, HeightB, HeightC; // ������ ��������������� �����
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++ ����� ������ ��� +++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TTin{
public:
   TTin();
  ~TTin();
  
  // ����������� ��� ����� � ������������ ������
  TTin(const char* name);
  
  // ��������� �� �����
  // ���������� 0 � ������ ������
  int Load(const char* name);
  
  // ����� �������� ������ ����������� � �������� �����
  // ���������� ����� �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // � ������ ������ ��� ������ ������ � � ������ ����������������
  // �������� ����� ������� ���������� ERRORHEIGHT  
  double GetTinSurfaceHeight(double x, double y);
  
  // �������� ����� �������������
  long int GetTriangleCount(){
     return TriangleCount;
  }
  
  // �������� ����������� � ������� index
  // � ������ ������ ���������� ����
  long int GetTriangle(TINTRIANGLE* const triangle, const int index){
     if(index < 0 || index > TriangleCount - 1)
        return 0;
     *triangle = Triangle[index];
     return 1;
  }
  
  // �������� ��� �����
  const char* GetFileName(){
     return FileName;
  }
  
  // �������� ������� �������
  unsigned long GetBaseScale(){
     return BaseScale;
  }
  
  // �������� �������� � ������
  const DFRAME& GetFrameMeters(){
     return FrameMeters;
  }
  
  // �������� ����������� �������� ������
  double GetMinHeightValue(){
     return MinHeightValue;
  }
  
  // �������� ������������ �������� ������
  double GetMaxHeightValue(){
     return MaxHeightValue;
  }

private:
   TTin(const TTin& Tin);
   const TTin& operator=(const TTin&);
   long int TriangleCount; // ���������� �������������
   TINTRIANGLE* Triangle; // ��������� �� ������ �������������
   char FileName[MAX_PATH];  // ��� ����� 
   unsigned long BaseScale;  // ������� �������
   DFRAME FrameMeters;       // �������� � ������
   double MinHeightValue,    // �������� �� ������
          MaxHeightValue;
   void SetBorderHeightValue(); // ���������� �������� �� ������
};

#ifndef HIDETIN

#ifndef MAPMACRO_H
  #include "mapmacro.h"
#endif

#ifdef __cplusplus

#include <windows.h>

#include "tin.h"
#include "tinapi.h"
#include "mapdat.h"

class _DLLCLASS TTin
{
 public:

  // ����������� �� ���������
  TTin();

  // ����������� ��� �������� ����� �� ��������� � �������
  TTin(char* name, TIN* tin, COLORREF* palette = 0);

  // ����������� ��� ����� � ������������ ������
  TTin(char* name, int mode);

 ~TTin();

//*****************************************************************
//  ����-������� ������ TTin
//*****************************************************************

  // ������� ������ ������� � �����
  int AccessMode() { return ACCESSMODE; }

  // ������� �������� ����� "�������� ��� ��������������"
  int IsTinEdit() { return (AccessMode() & GENERIC_WRITE); }

  // �������/��������� �������� ����� ���p��������� ���������
  int IsHeader() { return ISHEADER; }
  int IsHeader(int set) { return (ISHEADER = set); }

  // �������/��������� ����� ISCREATE
  int IsCreate() { return ISCREATE; }
  int IsCreate(int set) { return ISCREATE = set; }
  
  // �������/��������� ����� ������������� �������
  int IsPalette() { return ISPALETTE; }
  int IsPalette(int set) { return (ISPALETTE = set); }

  // �������/��������� ����� ������������� ������� ������
  int IsVertexArray() { return ISVERTEXARRAY; }
  int IsVertexArray(int set) { return (ISVERTEXARRAY = set); }

  // �������/��������� ����� ������������� ������� �������������
  int IsTriangleArray() { return ISTRIANGLEARRAY; }
  int IsTriangleArray(int set) { return (ISTRIANGLEARRAY = set); }

  // �������/��������� ����� ������������� ������� �������� ������
  int IsVertexNormalArray() { return ISVERTEXNORMALARRAY; }
  int IsVertexNormalArray(int set) { return (ISVERTEXNORMALARRAY = set); }

  // �������/��������� ����� ������������� ������� �������� �������������    
  int IsTriangleNormalArray() { return ISTRIANGLENORMALARRAY; }
  int IsTriangleNormalArray(int set) { return (ISTRIANGLENORMALARRAY = set); }

  // ��������� ������ � ����e
  int Save(int force);

  // �������/��������� ����� ������
  long Error() { return ISERROR; }
  long Error(long error) { return (ISERROR = error); }

  // �������/��������� ��������� ������� "��������"
  double  MeterInElement() { return TinMeterInElement; }
  double  MeterInElement(double element) { return (TinMeterInElement = element); }

  // ���������/������� �����
  int SetBorder(TDataEdit* data);
  TDataEdit* GetBorder() { return &BORDER; }

  // �������/��������� ����� ����������� �� �����
  int ShowByBorder();
  int ShowByBorder(int value);

  // ������� �����
  int DeleteBorder();

  // ������� ����� ���� �� ��������� TIN
  // ��� ������ ���������� ����
  int CreateByTin(const char* name, TIN* tin, COLORREF* palette);

  // �������� �����
  void Close() { Close(0); }

  // ������ ������� � ������ ������
  // index - ������ � ������� ������
  // ��� ������ ���������� 0
  int PutVertex(const TINVERTEX* vertex, int index);

  // ������ ������� �� ������� ������
  // index - ������ � ������� ������
  // ��� ������ ���������� 0
  int GetVertex(TINVERTEX* vertex, int index);

  // ������� �����a ���������
  TIN* GetHeader() { return &HEADER; }

  // �������/��������� ������ ������� TIN-������
  // index - ������ � ������� ������
  // flag - ����� ���������, ���������� �������� ������ �������
  // ��������a TINVERTEXFLAG ������a � TINAPI.H
  // ��� ������ ���������� 0
  int GetVertexFlags(int index, TINVERTEXFLAG* flag);
  int SetVertexFlags(int index, const TINVERTEXFLAG* flag);

  // ������ ������������ � ������ �������������
  // index - ������ � ������� �������������
  // ��� ������ ���������� 0
  int PutTriangle(const TINTRIANGLE* triangle, int index);

  // ������ ������������ �� ������a �������������
  // index - ������ � ������� �������������
  // ��� ������ ���������� 0
  int GetTriangle(TINTRIANGLE* triangle, int index);

  // �������/��������� ������ ������������ TIN-������
  // index - ������ � ������� �������������
  // flag - ����� ���������, ���������� �������� ������ ������������
  // ��������a TINTRIANGLEFLAG ������a � TINAPI.H
  // ��� ������ ���������� 0
  int GetTriangleFlags(int index, TINTRIANGLEFLAG* flag);
  int SetTriangleFlags(int index, const TINTRIANGLEFLAG* flag);

  // ������ ������������ (triangle), ����������� �������� �����.
  // (x,y) - ������������� ���������� ����� � ������.
  // ���������� ������ ������������, ����������� �������� �����.
  // ��� ������ ���������� -1
  int GetPlaneTriangle(TINTRIANGLE* triangle, double x, double y);

  // ����� �������� ������ ����������� � �������� �����.
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ������� � height �������� ������ � ������.
  // ��� ������ ���������� ����.
  int GetPlaneSurfaceHeight(double& height, double x, double y);

  // ������ ��������� ���-�������� ������� �� ������� ������
  // ��� ������ ���������� 0
  int GetSouthWestVertex(XYHDOUBLE* point);


  // ���������� �������� ������ � ����� ��������� ������������ (triangle)
  // ���������� ����� (x,y) �������� � ������ � ������� ���������
  // ��������� �����. ���������� �������� ������ � ������.
  // ��� ������ ���������� ERRORHEIGHT.
  double CalcHeightByTriangle(TINTRIANGLE* triangle, double x, double y);

  // ���������� ������ � ����� (p) 3D-o������ (p1-p2)   
  double CalcHeightInPointOfEdge(TINVERTEX* p1, TINVERTEX* p2, DOUBLEPOINT* p);

  // ���������� ������� ������
  double CalcModelSquare();

  // ������� ��������� �� �������
  COLORREF* Palette() { return PALETTE; }

  // �������� �����
  // ��� ������ ���������� ����
  int Open(const char * name, int mode = 0);

protected:

  // �������/��������� ������ ����������� ������� � �����
  int ShareMode() { return SHAREMODE; }
  int ShareMode(UINT shmode)
  {
    SHAREMODE = shmode;
    return SHAREMODE;
  }

  // �������� �����
  // force - ������� ������������ ������
  void Close(int force);

  // �������� �������� ���� ���������� ������
  void ClearAll();

  // ���������� ����� �������
  int AccessMode(UINT mode)
 	{
    ACCESSMODE = (mode & (GENERIC_READ|GENERIC_WRITE));
    if (ACCESSMODE == 0) ACCESSMODE = GENERIC_READ|GENERIC_WRITE;
    return ACCESSMODE;
  }

  // ������ ��������� �� �����
  // ��� ������ ���������� ����
  int ReadHeader();

  // ������ ��������� � ����
  // ��� ������ ���������� ����
  int WriteHeader();

  // ������ ������� �� �����
  // ��� ������ ���������� ����
  int ReadPalette();

  // ������ ������� � ����
  // ��� ������ ���������� ����
  int WritePalette();

  // ������ ������� ������ �� ����� � �����
  // ��� ������ ���������� ����
  int ReadVertexArray();

  // ������ ������� ������ �� ������ � ����
  // ��� ������ ���������� ����
  int WriteVertexArray();

  // �������� ������ ��� ������� ������
  // ��� ������ ���������� ����
  int AllocateVertexArray(int size);

  // ������ ������� �������� ������ �� ����� � �����
  // ��� ������ ���������� ����
  int ReadVertexNormalArray();

  // ������ ������� �������� ������ �� ������ � ����
  // ��� ������ ���������� ����
  int WriteVertexNormalArray();

  // �������� ������ ��� ������� �������� ������
  // ��� ������ ���������� ����
  int AllocateVertexNormalArray(int size);

  // ������ ������� ������������� �� ����� � �����
  // ��� ������ ���������� ����
  int ReadTriangleArray();

  // ������ ������� ������������� �� ������ � ����
  // ��� ������ ���������� ����
  int WriteTriangleArray();

  // �������� ������ ��� ������� �������������
  // ��� ������ ���������� ����
  int AllocateTriangleArray(int size);

  // ������ ������� �������� ������������� �� ����� � �����
  // ��� ������ ���������� ����
  int ReadTriangleNormalArray();

  // ������ ������� �������� ������������� �� ������ � ����
  // ��� ������ ���������� ����
  int WriteTriangleNormalArray();

  // �������� ������ ��� ������� �������� �������������
  // ��� ������ ���������� ����
  int AllocateTriangleNormalArray(int size);

  // ������������� ������� �����
  void BorderDataInit();

  // �������/��������� �������� ����� ���p��������� �����
  int IsBorder() { return ISBORDER; }
  int IsBorder(int set) { return (ISBORDER = set); }

  // �������� ������ ��� ������� �����
  // ��� ������ ���������� ����
  int AllocateBorderPoints(int size);
        char* BorderPoints() { return BORDERPOINTSBUFF; }

  // �������/��������� �������� �� ������ "�����" � �����
  unsigned long BorderOffset() { return (HEADER.BorderOffset); }
  unsigned long BorderOffset(unsigned long borderoffset)
  {
    IsHeader(TRUE);
    IsBorder(TRUE);
    return HEADER.BorderOffset=borderoffset;
  }

  // �������/��������� ����� ������ "�����"
  long BorderLength() { return (HEADER.BorderLength); }
  long BorderLength(long borderlength)
  {
    IsHeader(TRUE);
    IsBorder(TRUE);
    return HEADER.BorderLength = borderlength;
  }

  // ������ ����� �� �����
  // ��� ������ ���������� ����
  int ReadBorder();

  // ������ ����� � ����
  // ��� ������ ���������� ����
  int WriteBorder();
        
protected:

  int Create(const char* name, TIN* tin, COLORREF* palette = 0);
  int CreateByName(const char* name);

public:

  // �������� ����� � ����������������,
  // ��������� � API-��������� TINBUILD
  int Create(const char* name, const TINBUILD* parm,
             COLORREF* palette, int colorcount);


//*****************************************************************
//  ������� ��������� � ����������� ����� ���������
//*****************************************************************

  // �������/��������� �������������� �����
  unsigned long Label() { return HEADER.Label; }
  unsigned long Label(unsigned long label)
  {
    IsHeader(1);
    return HEADER.Label = label;
  }

  // �������/��������� ������ ���������
  unsigned long Version() { return HEADER.Version; }
  unsigned long Version(unsigned long version)
  {
    IsHeader(1);
    return HEADER.Version = version;
  }

  // �������/��������� ����� �����
  unsigned long Length() { return HEADER.Length; }
  unsigned long Length(unsigned long length)
  {
    IsHeader(1);
    return HEADER.Length = length;
  }

  // �������/��������� ����������������� ��������������
  unsigned long UserLabel() { return HEADER.UserLabel; }
  unsigned long UserLabel(unsigned long userlabel)
  {
    IsHeader(1);
    return HEADER.UserLabel = userlabel;
  }


  // �������/��������� ���a ������
  long ModelType() { return HEADER.ModelType; }
  long ModelType(long modeltype)
  {
    IsHeader(1);
    return HEADER.ModelType = modeltype;
  }

  // �������/��������� �����a ���������� ������
  long Method() { return HEADER.Method; }
  long Method(long method)
  {
    IsHeader(1);
    return HEADER.Method = method;
  }

  // �������/��������� ��������a ������
  MAPREGISTEREX* ModelRegister() { return &HEADER.ModelRegister; }
  MAPREGISTEREX* ModelRegister(const MAPREGISTEREX* modelRegister);

  // �������/��������� ���������a ������ ������
  long VertexCount() { return HEADER.VertexCount; }
  long VertexCount(long vertexcount)
  {
    IsHeader(1);
    return HEADER.VertexCount = vertexcount;
  }

  // �������/��������� ���������a ������������� ������
  long TriangleCount() { return HEADER.TriangleCount; }
  long TriangleCount(long trianglecount)
  {
    IsHeader(1);
    return HEADER.TriangleCount = trianglecount;
  }

  // �������/��������� �������� �� ������ ������
  unsigned long VertexOffset() { return HEADER.VertexOffset; }
  unsigned long VertexOffset(unsigned long offset)
  {
    IsHeader(1);
    return HEADER.VertexOffset = offset;
  }

  // �������/��������� �������� �� ������ �������������
  unsigned long TriangleOffset() { return HEADER.TriangleOffset; }
  unsigned long TriangleOffset(unsigned long offset)
  {
    IsHeader(1);
    return HEADER.TriangleOffset = offset;
  }

  // �������/��������� �������� �� ������ �������� ������
  unsigned long VertexNormalOffset() { return HEADER.VertexOffset; }
  unsigned long VertexNormalOffset(unsigned long offset)
  {
    IsHeader(1);
    return HEADER.VertexNormalOffset = offset;
  }

  // �������/��������� �������� �� ������ �������� �������������
  unsigned long TriangleNormalOffset() { return HEADER.TriangleOffset; }
  unsigned long TriangleNormalOffset(unsigned long offset)
  {
    IsHeader(1);
    return HEADER.TriangleNormalOffset = offset;
  }

  // �������/��������� �������� �� ������� ����������� �����������
  unsigned long PaletteOffset() { return HEADER.PaletteOffset; }
  unsigned long PaletteOffset(unsigned long offset)
  {
    IsHeader(1);
    return HEADER.PaletteOffset = offset;
  }

  // �������/��������� ���������� ������ ������� ����������� �����������
  unsigned long PaletteColorCount() { return HEADER.PaletteColorCount; }
  unsigned long PaletteColorCount(unsigned long palettecolorcount)
  {
    IsHeader(1);
    return HEADER.PaletteColorCount = palettecolorcount;
  }

  // ������� ��������� ������ ������� ���� ��������� ������ (�����)
  double X1() { return HEADER.X1; }
  double Y1() { return HEADER.Y1; }

  // ��������� ��������� ������ ������� ���� ��������� ������ (�����)
  double X1(double x1)
  {
    IsHeader(1);
    return HEADER.X1 = x1;
  }

  double Y1(double y1)
  {
    IsHeader(1);
    return HEADER.Y1 = y1;
  }

  // ������� ��������� ������� �������� ���� ��������� ������ (�����)
  double X2() { return HEADER.X2; }
  double Y2() { return HEADER.Y2; }

  // ��������� ��������� ������� �������� ���� ��������� ������ (�����)
  double X2(double x2)
  {
    IsHeader(1);
    return HEADER.X2 = x2;
  }

  double Y2(double y2)
  {
    IsHeader(1);
    return HEADER.Y2 = y2;
  }

  // ������� ������������ �������� ������ � ������
  double H1() { return HEADER.H1; }
  double MinHeightMeter() { return HEADER.H1; }

  // ������� ������������� �������� ������ � ������
  double H2() { return HEADER.H2; }
  double MaxHeightMeter() { return HEADER.H2; }

  // ��������� ������������ �������� ������ � ������
  double H1(double h1)
  {
    IsHeader(1);
    return HEADER.H1 = h1;
  }

  // ��������� ������������� �������� ������ � ������
  double H2(double h2)
  {
    IsHeader(1);
    return HEADER.H2 = h2;
  }


  // ����������� ���������� TIN-�����������
  int IsActive() { return (int)FILEID; }


  // �������/��������� ������� ����� �����
  char* Name() { return NAME; }
  char* Name(char* name)
  {
    if (name == 0) return 0;
    return strncpy(NAME, name, sizeof(NAME));
  }


private:

  // ���������
  TIN  HEADER;

  // C������� �� ���������
  unsigned long  HEADEROFFSET;

  // ��������� �� ������ ������
  TINVERTEX*  VERTEXARRAYBUFF;

  // ������ ������ ��� ������� ������
  int  VERTEXARRAYLENGTH;

  // ��������� �� ������ �������������
  TINTRIANGLE*  TRIANGLEARRAYBUFF;

  // ������ ������ ��� ������� �������������
  int  TRIANGLEARRAYLENGTH;

  // ��������� �� ������ �������� ������
  XYHDOUBLE*  VERTEXNORMALARRAYBUFF;

  // ������ ������ ��� ������� �������� ������
  int  VERTEXNORMALARRAYLENGTH;

  // ��������� �� ������ �������� �������������
  XYHDOUBLE*  TRIANGLENORMALARRAYBUFF;

  // ������ ������ ��� ������� �������� �������������
  int  TRIANGLENORMALARRAYLENGTH;

  // ������������� �����
  HANDLE  FILEID;

  // ������ ��� �����
  char  NAME[260];

  // �������
  COLORREF  PALETTE[256];

  // ����� ������� � �����
  int  ACCESSMODE;

  // ����� ����������� ������� � �����
  int  SHAREMODE;

  // ���� Create/Open
  int  ISCREATE;

  // ���� ���p��������� �����
  int  ISBORDER;

  // ���� ���p��������� �������
  int  ISPALETTE;

  // ���� ���p��������� ���������
  int  ISHEADER;

  // ���� ���p��������� ������� ������
  int  ISVERTEXARRAY;

  // ���� ���p��������� ������� �������������
  int  ISTRIANGLEARRAY;

  // ���� ���p��������� ������� �������� ������
  int  ISVERTEXNORMALARRAY;

  // ���� ���p��������� ������� �������� �������������
  int  ISTRIANGLENORMALARRAY;

  // ���� ��������� ������
  long  ISERROR;

  // �������� ������ "��������"
  double  TinMeterInElement;


  TDataEdit  BORDER;             // ��������� �� �����
  char*      BORDERPOINTSBUFF;   // ��������� �� ������� �����
  int        BORDERPOINTSLENGTH; // ������ ������ ��� ������� �����
  int        BORDERPOINTSCOUNT;  // ����� ����� �����
  POLYDATAEX BORDERDATA;         // ������� ����� (BORDERPOINTSBUFF)

};

#endif // __cplusplus

#endif // !HIDETIN

#endif  // TINBASE_H


