
#ifndef MAPDAT_H
#define MAPDAT_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifndef MAPDATA_H
  #include "mapdata.h"
#endif

#ifndef MEASURE_H
  #include "measure.h"
#endif

#include "maptrace.h"

class _DLLCLASS TTranslate;
class _DLLCLASS TMap;

#define DATABUFFERSIZE (4*1024L)  // ����������� ������ ������ ������� 
#define DATABUFFERAPP  (64*1024L) // ���������� ������ �������

#define DATALENGTHLIMIT  MAXDATALENGTH  // Maximum of record size 

#ifndef TINYDATA

typedef LONGMETRIC OBJECTDATA;
#define CheckDataIdent(ident) ((ident & 0xFFF0FFF0) == 0x7FF07FF0)

#else

typedef SHORTMETRIC OBJECTDATA;
#define CheckDataIdent(ident) ((ident & 0x0FFF0) == 0x7FF0)

#endif

// ��������� ���������� ������ ����� �������
// � ���� ������ �����
long _fastcall dataX1Long(OBJECTDATA * data);
long _fastcall dataY1Long(OBJECTDATA * data);

// ��������� ���������� ������ ����� �������
// � ���� ����� � ��������� ������
double _fastcall dataX1Double(OBJECTDATA * data);
double _fastcall dataY1Double(OBJECTDATA * data);
double _fastcall dataH1Double(OBJECTDATA * data);

// ��������� ���������� ����� ����� (�� ����� ������)
int _fastcall dataPointLimit(OBJECTDATA * data);

// ��������� ������ ����� �������
int _fastcall dataPointSize(OBJECTDATA * data);

// ������������� ����� ������� ���� Kind() � ���� DOUBLEPOINT
// � ��������� �������������� pointIn ������ ������ �������
// ��� ������ ���������� 0
int _fastcall dataXYDouble(OBJECTDATA * data, char * pointIn,
                           DOUBLEPOINT * pointOut);

// ������  ����������� ������� (0 - 2D, 1 - 3D)
int _fastcall dataDimension(OBJECTDATA * data);

// ���������� ��������� ( ����� ) �������
double _fastcall dataPerimeter(OBJECTDATA * data);

#ifdef __cplusplus

class _DLLCLASS TDataEdit;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  ������� ��'���� ����������� �����  +++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TObjectData
{                         // ***********
                          // ** DATA ***
 public :                 // ***********

  // ���������� ����� ������ ������� �������
  TObjectData(char * addr)
  {
    Base = (OBJECTDATA *)addr;
  }

  TObjectData(const int addr)
  {
    Base = (OBJECTDATA *)addr;
  }

  TObjectData(OBJECTDATA * addr)
  {
    Base = addr;
  }

  // ���������� ����� ������ ������� �������
  TObjectData()
  {
    Base = 0L;
  }

  // ���� �������� �������
  enum KIND { IDSHORT2  = 0x7FFF7FFFL, // ������������ �������������
              IDLONG2   = 0x7FFE7FFEL, // ��������������� �������������
              IDFLOAT2  = 0x7FFD7FFDL, // � ��������� �������
              IDDOUBLE2 = 0x7FFC7FFCL, // � ��������� ������� ������� ���������
              IDSHORT3  = 0x7FFB7FFBL, // ������������ �������������  ����������
              IDLONG3   = 0x7FFA7FFAL, // ��������������� ������������� ����������
              IDFLOAT3  = 0x7FF97FF9L, // � ��������� �������  ����������
              IDDOUBLE3 = 0x7FF87FF8L, // � ��������� ������� ������� ��������� ����������
              IDBAD     = 0x7FF87FF7L  // ����������� ���
            };

  // ���� ������� �������� (��� ������������� � SXF)
  enum DATTYPE { INTEGER = 0, FLOAT = 2 };

  // ������ �������� ������� (FLOAT+LONG => DOUBLE) (��� ������������� � SXF)
  enum DATSIZE { SHORT = 0, LONG = 1 };

  // ����������� ���������� �������
  enum DIRECT { UNDEFINED = OD_UNDEFINED, // �� ����������
                PLUS      = OD_RIGHT,     // �� ������� �������
                MINUS     = OD_LEFT,      // ������ ������� �������
              };

  // ��������� ����� ������ ������
  char * Address()
  { return (char *)Base; }

  // ��������� ����� ������������� ����� �������
  char * BeginData()
  { return (char *)(&(Base->Desc)); }

  // ��������� ������ ����������� �������
  int DescSize()
  { return sizeof(SHORTDESC); }

  // ���� �������� ������ ?
  int IsCorrect()
  { if ((Base != 0) && (Kind() > IDBAD)) return(1);
    return(0); }

  // ���� �������� ������ ��������� ���� ?
  int IsCorrect(KIND kind)
  { if ((Base != 0) && (Kind() == kind)) return(1);
    return(0); }

#ifndef TINYDATA
  // ��������� ������ ������� (������� ������ ��� ����������?)
  int IsLarge()                              
  {
    if (Base != 0) return (Base->Control & METRIC_LONGCOUNT);
    return(0);
  }

  // ��������� ��� ������ � ������� ����������
  // (0 - ����������, ����� - �������������)
  int IsRelativeHeight()                     
  {
    if (Base != 0) return (Base->Control & METRIC_RELATIVEH);
    return(0);
  }
#endif

  // ���������/���������� ��� (�������������) �������
  long Kind()
  { if (Base == 0) return 0;
    return Base->Ident; }

  long Kind(KIND kind)
  { if (Base == 0) return 0;
    return (Base->Ident = kind); }

  // ������ ����������� �������
  // ��� 2-yx ������ ������� ������� 0,
  // ��� 3-yx ������ - 1
  int DatDimension();

  // ��������� ������ ����� �������
  int PointSize();

  // ����������/��������� ����� ������ �������
  long Length()
  { if (Base == 0) return 0;
    return(Base->Length); }

  long Length(long length)
  { if (Base == 0) return 0;
    return(Base->Length = length); }

  // ��������� ������� �� ��������� ������
  // ������ ��������� ������ �� �������������� !
  int Load(TObjectData data);

  // ����������/��������� ����� ����� � �������
  int PointCount();
  int PointCount(int count);

  // ��������� ���������� ����� ����� (�� ����� ������)
  int PointLimit();

  // ��������� ������� ����� ��� ����� �������� (�� ����� ������)
  int PointReserve();

  // ����������/��������� ����� ��������� ������ (����������� + 1)
  int PolyCount()
  { if (Base == 0) return 0;
    return(Base->Part + 1); }

  int PolyCount(int polycount)
  { if (Base == 0) return 0;
    return ((Base->Part = (unsigned short)(polycount - 1)) + 1); }

  // ���������� ��������� �������
  double Perimeter();

  // ��������� ���������� ������ ����� �������
  // � �������� ������� (��������)
  // ����� ������ ����� 1
  // ��� ������ � ��������� ������ ���������� ����� 0
  long  X1Long();     // ��������� ����������
  long  Y1Long();     // ������ ����� �������

  double X1Double();  // ��������� ����������
  double Y1Double();  // ������ ����� �������
  double H1Double();

  // ��������� ���������� ������ ����� �������
  // � �������� ������� (��������)
  // ��� ������ � ��������� ������ ���������� ����� 0
  long  X2Long();     // ��������� ����������
  long  Y2Long();     // ������ ����� �������

  // ������������� ����� ������� ���� Kind() � ���� DOUBLEPOINT
  // � ��������� �������������� pointIn ������ ������ �������
  // ��� ������ ���������� 0
  int XYDouble(char * pointIn, DOUBLEPOINT * pointOut);

  // ��������� ������ ������������ ������ �� �����������
  // � �������
  // (FA_LEFT,FA_RIGHT,FA_CENTER - ��. mapgdi.h)
  int GetTextHorizontalAlign();                      

  // ���������� ����� ������ ������� �������
  OBJECTDATA * operator = (OBJECTDATA * Addr)
  {
    return (Base = Addr);
  }

  // ���������� ����� ������ ������� �������
  char * operator = (char * Addr)
  {
    return (char *)(Base = (OBJECTDATA  *)Addr);
  }

  char * operator = (TDataEdit * edit);

  char * operator = (TDataEdit& edit);

  // ��������� ��������� �� ������
  int operator == (int Value)
  {
    return (Base == (OBJECTDATA *)Value);
  }

  int operator != (int Value)
  {
    return (Base != (OBJECTDATA *)Value);
  }

 /*********************************************************
 *                                                        *
 *        ������� ���������� �������� �� �������          *
 *                                                        *
 *********************************************************/

 public :

  OBJECTDATA * Base;                 // ��������� �� ������
};
#endif


// Map data type for desktop system is IDFLOAT2,3  only !
// Site data type for desktop system is IDDOUBLE2,3 only !
// Map data type for mobile system is IDSHORT2 (TINYDATA) only !

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++  �������������� ������� ��'���� ����������� �����  +++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//  ������� ������� ������� � ������� "float" 2-�� ������
//  TDataEdit metric;
//  if (metric.Create(IDFLOAT2))     // �������� ������ � ���������
//    {
//      metric.InsertPoint(200.342,300.12);  // �������� �����
//      metric.InsertPoint(250.71,350.176);
//      ...
//    }

class _DLLCLASS TDataEdit : public TObjectData
{

 /*********************************************************
 *                                                        *
 *       ������� ������������� ������ ������              *
 *                                                        *
 *********************************************************/

 public :

#ifndef BUILD_DLL
  // ���������� ����� ������ ������� �������
  // text - ������� ������� � ������� (������� ���� "�������")
  TDataEdit(char * address, long int length = 0, int text = 0) :
            TObjectData(), Measure()
  {
    Memory = 0;  // ������ �� �������������
    SetBuffer(address,length,text);
  }
#endif

  TDataEdit() : TObjectData(), Measure()
  {
    Memory = 0;  // ������ �� �������������
    SetBuffer(0,0L,0);
  }

#ifndef BUILD_DLL
  TDataEdit(TObjectData data,int text = 0) :
            TObjectData(), Measure()
  {
    Memory = 0;  // ������ �� �������������
    SetObject(data,text);
  }
#endif

  TDataEdit(TDataEdit * data) : TObjectData(), Measure()
  {
    Memory = 0;  // ������ �� �������������
    Load(data);
  }

 ~TDataEdit()
  {
    SetBuffer(0,0L,0);
  }

  // ����������� ���������� �������
  enum DIRECT { UNDEFINED = OD_UNDEFINED, // �� ����������
                PLUS      = OD_RIGHT,     // �� ������� �������
                MINUS     = OD_LEFT,      // ������ ������� �������
              };

  // ���� �������� �������
  enum KIND { IDSHORT2  = 0x7FFF7FFFL, // ������������ �������������
              IDLONG2   = 0x7FFE7FFEL, // ��������������� �������������
              IDFLOAT2  = 0x7FFD7FFDL, // � ��������� �������
              IDDOUBLE2 = 0x7FFC7FFCL, // � ��������� ������� ������� ���������
              IDSHORT3  = 0x7FFB7FFBL, // ������������ �������������  ����������
              IDLONG3   = 0x7FFA7FFAL, // ��������������� ������������� ����������
              IDFLOAT3  = 0x7FF97FF9L, // � ��������� �������  ����������
              IDDOUBLE3 = 0x7FF87FF8L, // � ��������� ������� ������� ��������� ����������
              IDBAD     = 0x7FF87FF7L  // ����������� ���
            };
#ifndef TINYDATA
  // ���������� ��� ������ � ������� ����������
  // (0 - ����������, ����� - �������������)
  int SetHeightType(int type)                     
  {
    if (Base != 0)
      {
       Isdirty = 1;                               

       if (type != 0)
         { Base->Control |= METRIC_RELATIVEH; return 1;}
       else
         { Base->Control &= ~METRIC_RELATIVEH; return 0;}
      }
    return(0);
  }
#endif

  // ��� �������������
  int  PolyKey(int key) { return key; };
  int  PolyKey() { return 0; };

  // �������� ������ ��� ������ �������
  // ������������������� ��������� ������
  // ��������� ������������� ������,����� ����� = 0
  // �� ��������� ������� 2-�� ������
  // text - ������� ������� � ������� (������� ���� "�������")
  // ������ ������������� ������������� � �����������
  // ��� ��� ���������� ������ ������� � �������
  // SetBuffer(...), � ��� �����, SetBuffer(0,0).
  // ��� ������ ���������� 0
  int _fastcall Allocate(int kind = IDFLOAT2,
                         int text = 0,
                         int size = DATABUFFERSIZE);

  // ���������� ������ ��� ������ �������       
  void Free() { SetBuffer(0, 0L, 0); }

  // ������������������� ��������� ������
  // ��������� ������������� ������,����� ����� = 0
  // �� ��������� ������� 2-�� ������
  // text - ������� ������� � ������� (������� ���� "�������")
  // ��� ������ ���������� 0
  int _fastcall Clear(int kind = IDFLOAT2,int text = 0);
  int _fastcall Create(int kind = IDFLOAT2,int text = 0);

  // ��������� ������� �� ��������� ������
  //  text - ������� ������� � ������� (������� ���� "�������")
  // ������ ������ 512 �� �� �����������
  // ��������� ������� ����� �� 1-�� ����� �������
  // ���������� ����� ����������� ������
  // ��� ������ ���������� 0
  int _fastcall Load(OBJECTDATA * data, int text);
  int Load(TObjectData data, int text)
  {
    return Load(data.Base, text);
  }
  int Load(TDataEdit * data)
  {
    if (data == 0) return 0;
    return Load(data->Base, data->IsTextMetric());
  }
  int Load(TDataEdit& data)
  {
    return Load(data.Base, data.IsTextMetric());
  }

  // ���������� �������� ������ �������
  //  address - ����� ������
  //  length  - ����� ������
  //  text    - ������� ������� � ������� (������� ���� "�������")
  // ������ ���������� Allocate() �������������.
  // ��������� ������� ����� �� 1-�� ����� �������,
  // ���� ����� �������� ���������� ������
  void _fastcall SetBuffer(char * address,long int length,
                           int text = FALSE);

  void SetObject(TObjectData data,int text = FALSE)
  {
//    Tracer(">>>> CALL SetObject()\n");

    if (data == 0) SetBuffer(0,0L,0);
    else SetBuffer(data.Address(),data.Length(),text);
  }

  // ���������/���������� ������� �������������� ������
  int IsDirty()          { return Isdirty; }
  int IsDirty(int dirty) { return (Isdirty = dirty && 1); }

  //  �������� ��������� �� ��������� ������
  //  data - ������ ��������
  //  number - ����� ���������� � data
  //  ��� ������ ���������� 0
  int AppendSubject(TDataEdit *data, int number);

  //  ������� ������ �� ����������
  //  data - ������ ����� ���������
  //  number - ����� ���������� � data
  //  ��� ������ ���������� 0
  int LoadSubject(TDataEdit *data, int number);

protected :

  // ��������� ������ ������ �������
  // ���������� ����� ������ ������
  // ��� ������ ���������� 0
  int Realloc();


 /*********************************************************
 *                                                        *
 * ����������� ��������� �� ������� ������� � ����������� *
 *                                                        *
 *********************************************************/

 public :

  // ���������� ��������� �� ������ ����� ������� �������
  // ����������� �������� �� ����� ������ � ����� ������
  // ��� ������ ���������� 0
  char * FirstPoint() { return FirstPointSubject(0); }

  // ���������� ��������� �� ������ ����� ������� ����������
  // number - ���������������� ����� ����������
  // ( 0 - ������, 1 - ������ ��������� � �.�.)
  // ����������� �������� �� ����� ������ � ����� ������
  // ��� ������ ���������� 0
  char * _fastcall FirstPointSubject(int number = 0);

  // ���������� ��������� �� �������� ����� �������
  // �������� ������� ��� ����������
  // ����� ������ ����� 1
  // ��� ������ ���������� 0
  char * GoPoint(int number)
  {
    if ((number == NumberOfPoint) && (Point != 0)) return Point;

    if (((Point == 0) || (NumberOfPoint < 1)) &&
        (FirstPointSubject(SubjectNumber()) == 0)) return 0;

    if ((number < 1) || (number > PointCount())) return 0;

    Point = Point - (NumberOfPoint - number)*SizeOfPoint;

    NumberOfPoint = number;

    return Point;
  }

  // ���������� ��������� �� �������� ����� �������
  // ���������� ������� ��� ����������
  // ����� ������ ����� 1
  // ��� ������ ���������� 0
  char * GoPointSubject(int number,int subject)
  {
    if ((number == NumberOfPoint) && (Point != 0) &&
        (subject == SubjectNumber())) return Point;

    if (((Point == 0) || (NumberOfPoint < 1) ||
         (subject != SubjectNumber())) &&
        (FirstPointSubject(subject) == 0)) return 0;

    if ((number < 1) || (number > PointCount())) return 0;

    Point = Point - (NumberOfPoint - number)*SizeOfPoint;

    NumberOfPoint = number;

    return Point;
  }

  // ���������� ��������� �� ��������� ����� ������� �������
  // ����������� �������� �� ����� ������ � ����� ������
  // ��� ������ ���������� 0
  char * LastPoint();

  // ���������� ��������� �� ��������� ����� ������� ����������
  // number - ���������������� ����� ����������
  // ( 0 - ������, 1 - ������ ��������� � �.�.)
  // ����������� �������� �� ����� ������ � ����� ������
  // ��� ������ ���������� 0
  char * LastPointSubject(int number = 0);

  // ���������� ��������� �� ��������� ����� �������
  // ������� ��� ����������
  // ��� ������ ���������� 0
  char * NextPoint();

  // ���������� ��������� �� ���������� ����� �������
  // ������� ��� ����������
  // ��� ������ ���������� 0
  char * PrevPoint()
  {
    if (Point == 0) return 0;
    if (NumberOfPoint <= 1) return 0;
    NumberOfPoint--;
    return (char *)(Point -= SizeOfPoint);
  }

 protected :

  // ���������� ��������� �� ���������� ����������/�������
  // �������� ����� ������ ��� ������ �� �����������
  // ��� ������ ���������� 0
  char * _fastcall DescPointSubject(int number = 0);


 /*********************************************************
 *                                                        *
 *       ������ ������ �� ������� �������/����������      *
 *     (� ������������ � ������� ���������� ���������)    *
 *                                                        *
 *********************************************************/

 public :

  // ��������� ����� ������� ����� �������/����������
  char * CurrentPoint() { return Point; }

  // ��������� ����� ������� �����
  // ����� ������ ����� 1, ���� �� ����������� - ���������� 0
  int PointNumber() { return NumberOfPoint; }

  // ��������� ����� ����� � ������� ����������/�������
  // �������� ������� �� ��������� �� ������� ���������/������
  // ��� ������ ���������� 0
  int PointCount();

  // ��������� ����� ����� � ������� ����������/�������
  // subject - ���������������� ����� ����������
  // ��� ������ ���������� 0
  int SubjectPointCount(int subject)            
   {
     if (FirstPointSubject(subject) == 0)
       return 0;
     return PointCount();  
   }

  int SetObjectPointCount(int count)
   { return TObjectData::PointCount(count); }

  // ��������� ����� �������� ����������
  // ����� ������� ���������� 1, ���� �� ����������� ���
  // ��������� �� ������� ������� - ���������� 0
  int SubjectNumber() { return NumberOfSubject; }

  // ��������� ���������� ������� ����� ����������/�������
  // � ���� ������ ����� ��� � ��������� �������
  // ��� ������ ���������� 0
  long X();
  long Y();

  double XDouble();
  double YDouble();
  double HDouble();

  // ��������� ���������� �������� ����� ����������/�������
  // ��� ������ ���������� 0
  double _fastcall XNDouble(int number);
  double _fastcall YNDouble(int number);
  double _fastcall HNDouble(int number);

  // ������������� ����� ������� ���� Kind() � ���� DOUBLEPOINT
  // � ��������� �������������� pointIn ������ ������ �������
  // ��� ������ ���������� 0
  int XYDouble(char * pointIn, DOUBLEPOINT * pointOut);

  // ��������� ���������� ������ ����� �������
  // � �������� ������� (��������)
  // ��� ������ � ��������� ������ ���������� ����� 0
  long  X1Long();     // ��������� ����������
  long  Y1Long();     // ������ ����� �������

  double X1Double();  // ��������� ����������
  double Y1Double();  // ������ ����� �������

 /*********************************************************
 *                                                        *
 *          ������� ������� ���������� � �������          *
 *                                                        *
 *********************************************************/

 public :

  // ����������� ��������� �������
  //  dframe - ����������� �������� �������/����������
  // ��� ������ ���������� 0
  int Dimensions(DFRAME * dframe);

  // ����������� ��������� �������/����������
  //  dframe - ��������
  //  subject - ����� ����������
  // ��� ������ ���������� 0
  int DimensionsSubject(DFRAME * dframe, int subject = 0);

  // ����������� ����������� ���������� �������/����������
  // ����������: OD_RIGTH,OD_LEFT,OD_UNDEFINED (��.maptype.h)
  int GetDirection(int subject = 0);

  // ��������� ����������� �������/����������
  // ������� - 1 - �������
  //           0 - ��������� ��� ������
  int GetExclusiveSubject(int number = 0);

  // ���������� ����� �������
  double PolyPerimeter();

  // ���������� ����� ����������/�������
  // subject - ����� ���������� (���� = 0, �������������� ������)
  double PolySubjectPerimeter(int subject);   

  // ���������� ������� �������/����������
  // ��� ������ ���������� 0
  double SquareSubject(int subject = 0);

  // ���������� ������� �������
  double Square();

  // ����� ����� ����� � ������� � ������������
  int TotalPointCount();

 protected :

  // ���������� �������� ������� �������/����������
  // ��� ������ ���������� 0
  double SignedSquareSubject(int subject = 0);


 /*********************************************************
 *                                                        *
 *            ������� ����������� ������ �����            *
 *                                                        *
 *********************************************************/

 public :

  // ����������� ������� � ������� �������/����������
  //  xy1, xy2  - ���������� �������
  //  first     - ����� ������ ����� �������
  //  last      - ����� ��������� ����� �������
  //  subject   - ����� �������/����������
  //             (0 - ������, 1 - ������ ��������� � �.�.)
  //  precision - ��������
  // ���������� ��� ��������� NUMBERPOINT, ���������� �����
  // ����� �������, ����� ������� ��������� ����� �����������
  // � ��������� DOUBLEPOINT - ���������� ����� �����������
  // ��� ��������� ����������� ���� ������� xy1,xy2 �����
  // �� ������� �������
  // ��� ���������� ����� ����������� ��� ������ ���������� 0

  int CrossCutData(DOUBLEPOINT * xy1, DOUBLEPOINT * xy2,
                   int first, int last,
                   NUMBERPOINT * point1, NUMBERPOINT * point2,
                   int subject = 0, double precision = DELTANULL);

  // ����������� ���������� ����� � ������������ x,y
  // � ������/���������
  //  point   - ���������� �����
  //  subject - ����� �������/����������
  // ����������: 1 - ����� ������ �������/����������,
  //             2 - ����� �������,
  //             3 - ����� ��������� � ������ �������,
  //             4 - ����� ����� �� ������� �������,
  //             0 - ������ �������

  int Inside(DOUBLEPOINT * point, int subject = 0);

  // ����� ����� ������� ������� � �����������,
  // ��������� � ��������. ��� ����������� ������
  // ����������/�������, � ������� ������� �����,
  // ����� ������� ������� SubjectNumber()
  // ���������� ����� ����� (����� ������ ����� 1)
  // ��� ������ ���������� 0

  int SeekNearPoint(double x,double y);

  // ����� ����� ������� ����������, ��������� � ��������
  //  number - ���������������� ����� ����������
  //           (0 - ������, 1 - ������ ��������� � �.�.)
  // ���������� ����� ����� (����� ������ ����� - 1)
  // ��� ������ ���������� 0

  int SeekNearPoint(double x,double y,int number);

  // ����� ����� �� ������� ������� ����������,
  // ��������� � ��������
  //  number - ���������������� ����� ����������
  //           (0 - ������, 1 - ������ ��������� � �.�.)
  //  first  - ����� ������ ����� �������
  //  last   - ����� ��������� ����� �������
  // ���������� ����� ����� (����� ������ ����� - 1)
  // ��� ������ ���������� 0

  int SeekNearPoint(double x,double y,int number,int first,int last);

  // ����� ����� �� �������� ������� � �����������,
  // ��������� � ��������
  // ��� ����������� ������ ����������/�������
  // ����� ������� ������� SubjectNumber()
  // ���������� ����� ����� �������, �� ������� �����������
  // ����� �� ������� (����� ������ ����� - 1)
  // ���������� ����� ���������� �� ������ point
  // ��� ������ ���������� 0

  int SeekNearVirtualPoint(double x,double y,XYDOUBLE * point);

  // ����� ����� �� ������� ����������, ��������� � ��������
  //  number - ���������������� ����� ����������
  //           (0 - ������, 1 - ������ ��������� � �.�.)
  // ���������� ����� ����� ������� �� ������� �����������
  // ����� �� ������� (����� ������ ����� - 1)
  // ���������� ����� ���������� �� ������ point
  // ��� ������ ���������� 0

  int SeekNearVirtualPoint(double x,double y,int number,XYDOUBLE * point);

  // ����� ����� �� ������� ������� ����������, ��������� � ��������
  //  number - ���������������� ����� ����������
  //           (0 - ������, 1 - ������ ��������� � �.�.)
  //  first  - ����� ������ ����� �������
  //  last   - ����� ��������� ����� �������
  // ���������� ����� ����� ������� �� ������� �����������
  // ����� �� ������� (����� ������ ����� - 1)
  // ���������� ����� ���������� �� ������ point
  // ��� ������ ���������� 0

  int SeekNearVirtualPoint(double x,double y,int number,int first,int last,
                           XYDOUBLE * point);

  // ����������� ��������� �����, ������� �� ��������
  // ���������� (�� ���������) �� �������� �����
  // number - ����� ��������� �����
  // distance - ����������
  // ���� distance > = 0 - ����� �� ����������� ����������
  //               <   0 - ����� ������ ����������� ����������
  // point - ���������� �������� �����
  // subject - ����� ����������
  // ���������� ����� �����, �� ������� ��������� ���
  // c ������� ���������
  // ���� ����� ��������� - ���������� ������������� ����� �����
  // ��� ������ ���������� 0

  int SeekVirtualPointByDistance(int number, double distance,
                                 DOUBLEPOINT *point,
                                 int subject = 0);

  // ����� ����� �� �������, ��������� � ��������
  // segment - ������ �� 2-� ��������� (������� �� ���� �����)
  // ��� ������ ���������� 0
  // ���������� ����� ���������� �� ������ target

  int SeekVirtualPointOnSegment(double x,double y,
                                DOUBLEPOINT *segment,
                                DOUBLEPOINT *target);

 /*********************************************************
 *                                                        *
 *            ������� �������������� �������              *
 *                                                        *
 *********************************************************/

 public :

  // �������� ������ ������ ������� (IDFLOAT2,...,IDDOUBLE3)
  // ��� ������ ���������� 0, ����� - ��� ������ ������� ������ !
  // ��� ������� �� ����� ���� ������� (� ��� IDSHORT2, IDFLOAT2)
  int ChangeKind(int kind);

  // �������� ������ ������ ������� �������� �������
  // � ������ ���� ������� (text != 0) ��� �������� (text = 0)
  // ��� ������ ���������� 0, ����� - ��� ������ ������� ������ !
  int ChangeTextFormat(int text = 0);

  // ������� ���������� ���������� � ������ �������
  // � ����� ������ ����������� ���������� ����������
  // ����������� �������� �� ����� ������ � ����� ������
  // ����� ����� = 0, ����� ���������� = ������������ ����� + 1
  // (��� �������, ������������ ���������� ����� ����������)
  // ��� ������ ���������� 0
  int CreateSubject();

  // �������� ���������� �������/���������� � ������ �������  
  // � ��������� ������� ������ ����������� ���������� ����������
  // ����� ����� = 0, ����� ���������� = subject
  // ��� ������� ���������� ���������� 1, ����� 0 (FALSE)
  int InsertSubject(int subject);

  // ������� ��������� � ������ �������
  // ������� ���������� ������ ����� �������
  // ��� ������ ���������� 0
  int DeleteSubject(int number);

 /*********************************************************
 *                                                        *
 *          ������� �������������� ����� �������          *
 *                                                        *
 *********************************************************/

 public :

  // �������� ���������� ����� � ������� �������
  // ����������� ����� ���������� ��������� � ������� �������
  // ����������� ����� ���������� ������� ������
  // ���������� ������������� � ������ ������ �������
  // ��� ���������� ����� �������������� ����� ������
  // ��� ������ ���������� 0
  int AppendPoint(double x,double y)
  {
    return AppendPointSubject(0, x, y);
  }

  int AppendPoint(double x,double y,double h)
  {
    return AppendPointSubject(0, x, y, h);
  }

  int AppendPoint(DOUBLEPOINT * point)
  {
    return AppendPoint(point->X,point->Y);
  }

  // �������� ����� � ������� �������/����������
  // ����������� ����� ���������� ��������� � ������� ����������
  // number - ����� ����������, ���� ����� ���� - ��������������
  // ������� �������.
  // ����������� ����� ���������� ������� ������
  // ��� ���������� ����� �������������� ����� ������
  // ��� ������ ���������� 0
  int AppendPointSubject(int number,double x,double y);
  int AppendPointSubject(int number,double x,double y,double h)
  {
    if (AppendPointSubject(number,x,y) == 0) return 0;
    H(h);
    return 1;
  }

  int AppendPointSubject(int number,DOUBLEPOINT * point)
  {
    return AppendPointSubject(number,point->X,point->Y);
  }

  // �������� ����������� ������� ����� �������
  // ���������� ����� �������� ����������� ����������
  // ��� ������ ���������� 0
  int ChangeDirection();

  // �������� ����������� ������� ����������
  // ��� ������ ���������� 0
  int ChangeDirection(int subject);

  // ������� ������� ����� ������� �������/����������
  // ���� ����� �� ���� - ������ �� ���������
  // ������� ���������� ����� ��������� �� ���������
  // ��� ������ ���������� 0
  int DeletePoint();

  // �������� �� ������� ���������� �����
  // precision - ��������
  // height    - ������� ����� ���������� ������� 
  // ��� ������ ���������� 0
  int DeleteEqualPoint(double precision = DELTANULL, int height = 0);

  // �������� ����� � ������� �������/����������
  // �� ������� ������
  // ���� ����� �� ���� - ����������� ������ �����
  // ����������� ����� ���������� ������� ������
  // ��� ���������� ����� �������������� ����� ������
  // ��� ������ ���������� 0
  int InsertPoint(double x,double y);
  int InsertPoint(double x,double y,double h)
  {
    if (InsertPoint(x,y) == 0) return 0;
    H(h);
    return 1;
  }

  int InsertPoint(DOUBLEPOINT * point)
  {
    return InsertPoint(point->X,point->Y);
  }


  // �������� ���������� �������
  //  precision - ��������
  // �������: 1. ������� ����� �������;
  //          2. ����������� ���������� < 2 �����;
  //          3. ��������� ���������� < 4 �����;
  //          4. ����� �������, ������� � �������� ������� ������
  //             �� ���������� precision �� ������.
  // ������ �� ������� ������� !!!
  // ���������� ����� ����� ����� �������
  // ��� ������� ����������:
  //    0 - ������ ���������
  //   -1 - ������ ������� �� ����� �����
  //   -2 - ������ ������� �� ���� ���������� �����
  //   -3 - ����� ����� ���������� ������� ������� ����� 3
  //  -10 - ����� ����� ������� ��������� ����� ������ �������
  int LinearFilter(double precision = DELTANULL);
  int Filter(double precision = DELTANULL)
     { return LinearFilter(precision); }             

  // �������� ��� ���������� ������� ������� �� ��������
  // �������� (delta)
  // ��� ������ ���������� 0
  int RelocateObject(DOUBLEPOINT * delta);

  // �������� ��� ���������� ������� �������/����������� �� ��������
  // �������� (delta)
  // number - ����� �������/����������
  // ��� ������ ���������� 0
  int RelocateSubject(int number, DOUBLEPOINT * delta);

  // ��������� ������ ������ ������ ( center )
  // �� �������� ���� ( anglevalue ).
  // ���� �������� � �������� � ����� ��������� ��������:
  // �� 0 �� PI � �� 0 �� -PI ���
  // �� 0 �� PI � �� 0 �� 2PI
  // ��� ������ ���������� 0
  int RotateObject(DOUBLEPOINT *center, double anglevalue);

  // ��������� ������/��������� ������ ������ ( center )
  // �� �������� ���� ( anglevalue ).
  // ���� �������� � �������� � ����� ��������� ��������:
  // �� 0 �� PI � �� 0 �� -PI ���
  // �� 0 �� PI � �� 0 �� 2PI
  // number - ����� ����������
  // ��� ������ ���������� 0
  int RotateSubject(DOUBLEPOINT *center, double anglevalue,
                    int number = 0);

  // ��������������(factor) ������� �������
  // factor - �����������
  // deltanull - �������� ������������ 0
  // ��� ������ ���������� ����
  int ScopeObject(DOUBLEPOINT *factor, DOUBLEPOINT *deltanull);

  // ��������������(factor) ������� �������/����������
  // factor - �����������
  // deltanull - �������� ������������ 0
  // number - ����� ����������
  // ��� ������ ���������� ����
  int ScopeSubject(DOUBLEPOINT *factor, DOUBLEPOINT *deltanull,
                   int number = 0);

  // �������������� (factor) � c������� ��� ���������� �������
  // ������� �� �������� �������� (delta)
  // factor - �����������
  // deltanull - �������� ������������ 0
  // delta - ��������������� ��������
  // ��� ������ ���������� ����
  int ScopeAndRelocateObject(DOUBLEPOINT *factor,
                             DOUBLEPOINT *deltanull,
                             DOUBLEPOINT *delta);

  // �������������� (factor) � c������� ��� ���������� �������
  // �������/���������� �� �������� �������� (delta)
  // factor - �����������
  // deltanull - �������� ������������ 0
  // delta - ��������������� ��������
  // number - ����� ����������
  // ��� ������ ���������� ����
  int ScopeAndRelocateSublect(DOUBLEPOINT *factor,
                              DOUBLEPOINT *deltanull,
                              DOUBLEPOINT *delta,
                              int number = 0);

  // ������� �����
  int DeleteLoop(double precision = DELTANULL);


  // ���������� ��������� �� ���� �� ������� �������
  // �.1 � �.3 (����� �.2 , ������ � ��������� - radius)
  int BuildCircular(DOUBLEPOINT * point1,
                    DOUBLEPOINT * point2,
                    DOUBLEPOINT * point3,
                    double radius);

  // ������ ��������� ��'����
  enum { ABR_APPEND   = 0,  // �������� ����� � ����� �������
                            // �� ���������, ���� ������ �������
         ABR_LAST     = 1,  // �������� ��������� �����
         ABR_FIRST    = 2,  // �������� ������ �����
         ABR_ADDLAST  = 3,  // �������� ����� � ����� �������
         ABR_ADDFIRST = 4   // �������� ������ �����
       };

  // �������� ������/���������
  //  mode = 0 - �������� ��������� �����
  //             (�� ���������, ���� ������ �������)
  //       = 1 - �������� ��������� �����
  //       = 2 - �������� ������ �����
  //       = 3 - �������� ��������� �����
  //       = 4 - �������� ������ �����
  // ��� ������ ���������� 0
  int SetExclusiveSubject(int number = 0, int mode = 0);
  int Abridge(int number = 0, int mode = 0)
  {
    return SetExclusiveSubject(number,mode);
  }

  // �������� ������ � ��� ����������
  // ��� ������ ���������� 0
  int AbridgeObject(int mode = 1);

  // ���������� ���������� ������� ����� ����������/�������
  // � ���� ������ ����� ��� � ��������� �������
  // ���������� ������������ � ������������ � ��������
  // ������ (��. Kind()).
  void UpdatePoint(DOUBLEPOINT * point)
  {
    UpdatePoint(point->X,point->Y);
  }

  void UpdatePoint(double x,double y)
  {
    X(x); Y(y);
  }

  void UpdatePoint(double x,double y,double h)
  {
    X(x); H(h); Y(y);
  }

  double X(double x) { return XDouble(x); }
  double Y(double y) { return YDouble(y); }
  double H(double h) { return HDouble(h); }

  double XDouble(double x);
  double YDouble(double y);
  double HDouble(double h);


  // �������� ��������� ������� �������         
  // ��� ������ ���������� ����, ���� ������� ������������ -
  // ���������� ������������� ��������

  int StructControl();


 /*********************************************************
 *                                                        *
 *       ������ ������ � ������ ������� �� �������        *
 *                  �������/����������                    *
 *                                                        *
 *********************************************************/

 public :

  // ��� ������� ������� ?
  int IsTextMetric() { return (IsTextData != 0); }

  // ����� ����� ��������� UNICODE ?
  int IsUnicodeText()
  {
#ifndef TINYDATA
    if (Base != 0)
      return (Base->Control & METRIC_UNICODETEXT);
#endif
    return 0;
  }

  // ��������� ����� ��������� ������ (����� ��������)
  // (����� ����� �������� ������ �� ��� ����� ������)
  // ��� ������ ��� ��� ������ ������ ���������� 0
  int TextLength();

  // ��������� ���������� ��������� ������
  // text   - ����� ��� ���������� ������
  // length - ����� ���������� ������� ��� ������
  // ��� ������� ���������� ������������ �������� text,
  // ���������� ������ ����� ��������� ANSI
  // ��� ������ ���������� 0
  char * GetText(char * text,int length);

  // ��������� ���������� ��������� ������
  // �� ���������� ������� !
  // ��� ������ ���������� 0
  char * GetObjectText();

  // ���������� ����� ���������� ��������� ������
  // text   - ����� ����� ������
  // ��� ������� ���������� ������������ �������� text,
  // ���������� ������ ������ ����� ��������� ANSI
  // ��� ������ ���������� 0
  char * PutText(char * text) { return PutText(text,-1); }

  // ��������� ������ ������������ ������ �� �����������
  // � �������� ����������
  // (FA_LEFT,FA_RIGHT,FA_CENTER - ��. mapgdi.h)
  int GetTextHorizontalAlign();

  // ��������� ������ ������������ ������ �� ���������
  // � �������� ����������
  // (FA_BOTTOM,FA_TOP,FA_BASELINE,FA_MIDDLE)
  int GetTextVerticalAlign();

  // ���������� ������ ������������ ������ �� �����������
  // subject - ����� ���������� (-1 - ���������� ����)
  // (FA_LEFT,FA_RIGHT,FA_CENTER)
  int PutTextHorizontalAlign(int align, int subject);

  // ���������� ������ ������������ ������ �� ���������
  // subject - ����� ���������� (-1 - ���������� ����)
  // (FA_BOTTOM,FA_TOP,FA_BASELINE,FA_MIDDLE)
  int PutTextVerticalAlign(int align, int subject);

  // ���������� ����� ���������� ��������� ������
  // � �������� ����������
  // text   - ����� ����� ������
  // align  - ���������� ������� ������������ (FA_BOTTOM|FA_CENTER,...)
  // ��� ������� ���������� ������������ �������� text,
  // ���������� ������ ������ ����� ��������� ANSI
  // ��� ������ ���������� 0
  char * _fastcall PutText(const char * text, int align, int isunicode = 0);

  // ��������� ����� ������ ������ ����������
  // ������ ����� ��������� ANSI
  // ��� ������ ���������� 0
  TEXTDATA * GetTextData();

  // ���������� ����� ���������� ��������� ������
  // text   - ����� ����� ������ (���������� � ���� �����),
  // ������ ������ ���� � ��������� ANSI ��� ����� ���������
  // ��� ������ ���������� 0
  char * _fastcall PutTextData(TEXTDATA * text, int isunicode = 0);

 /*********************************************************
 *                                                        *
 *               ������� �� �������                       *
 *                                                        *
 *********************************************************/

 public :

  // ���������� ���������� ����� ����� �������
  double Distance(DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);

  // ���������� ���������� ����� ������ � ������,
  // �������� ����� �������
  double Distance(DOUBLEPOINT *point, DOUBLEPOINT *xy1,
                                      DOUBLEPOINT *xy2);

  // ���������� ��������� �������
  double Perimeter();

  // ����������� ���� ����� �� �������������� �� ������� (point1-point2)
  // �� ���������� distance �� ����� point (�� ��������� point1)
  int SeekPointNormalLine(DOUBLEPOINT *point1, DOUBLEPOINT *point2,
                          DOUBLEPOINT *pointout1, DOUBLEPOINT *pointout2,
                          double distance, DOUBLEPOINT *point = 0);

  // ���������� ������������� ���� �� ����� XY1 � XY2 � ��������
  double DirectionAngle(DOUBLEPOINT *XY1, DOUBLEPOINT *XY2);

 public :

  // ��������� ��������� �� ������
  int operator == (int Value)
  {
    return (Base == (OBJECTDATA *)Value);
  }

  int operator != (int Value)
  {
    return (Base != (OBJECTDATA *)Value);
  }

 protected :

  // ���������� ����� ������ ������� �������
  OBJECTDATA * operator = (OBJECTDATA * Addr)
  {
    SetBuffer((char *)Addr, Addr->Length);
    return (Addr);
  }

  // ���������� ����� ������ ������� �������
  char * operator = (char * Addr)
  {
    return (char *)(Base = (OBJECTDATA  *)Addr);
  }

 public:

  long int BufferLength;  // ������ ������ �������
  char HUGER * Point;     // ��������� ������� �����
  int SizeOfPoint;        // ������ � ������ �������� �����
  int NumberOfPoint;      // ����� ������� ����� ������� ��� ����������
                          // ���������� � 1
  int NumberOfSubject;    // ������� ����� ������� (= 0)
                          // ��� ���������� (> 0)
  char HUGER * DescPoint; // ��������� �� ���������� ������� ��������
                          // ���������� ��� �������
  char * Memory;          // ������ ��������� ������ � �����������
                          // (���� != 0, ����������)
  int IsTextData;         // ������� ������� � �������
  int Isdirty;            // ������� �������������� �������
  int IsSemRefer;         // ������� ������ �� ��������� � ������ ������� 

  TMeasure     Measure;   // ������� ���������� ��'����
};

typedef TDataEdit DATAEDIT;

// �������� ������ ��� ������������ ������ �������
// ������������������� ��������� ������
// ��������� ������������� ������,����� ����� = 0
// ��� ������ ���������� ����
int _fastcall deAllocate(DATAEDIT * data, int kind, int text, int size);

// ��������� ������ ������ �������
// ��� ������ ���������� ����, ����� - ����� ������ ������
int _fastcall deRealloc(DATAEDIT * data);

// ������������������� ��������� ������
// ��������� ������������� ������,����� ����� = 0
// ��� ������ ���������� ����
int _fastcall deClear(DATAEDIT * data, int kind, int text);

// ������������������� ��������� ������
// ��������� ������������� ������,����� ����� = 0
// ��� ������ ���������� ����
int _fastcall deCreate(DATAEDIT * data, int kind, int text);

// ���������� �������� ������ �������
// address - ����� ������, length - ����� ������
// ��������� ������� ����� �� 1-�� ����� �������
void _fastcall deSetBuffer(DATAEDIT * data, char * address,
                           long int length, int text);

// ������� ���������� ���������� � ������ �������
// � ����� ������ ����������� ���������� ����������
// ����� ����� = 0, ����� ���������� = ������������ ����� + 1
// (��� �������, ������������ ���������� ����� ����������)
// ��� ������� ���������� ���������� 1, ����� 0 (FALSE)
int _fastcall deCreateSubject(DATAEDIT * data);

// �������� ���������� �������/���������� � ������ �������  
// � ��������� ������� ������ ����������� ���������� ����������
// ����� ����� = 0, ����� ���������� = subject
// ��� ������� ���������� ���������� 1, ����� 0 (FALSE)
int _fastcall deInsertSubject(DATAEDIT * data, int subject);

// ��������� ������� �� ��������� ������
// ������ ������ 512 �� �� �����������
int _fastcall deLoad(DATAEDIT * dataed, OBJECTDATA * data, int text);

// ������� ��������� � ������ �������
// ��� ������ ���������� ����
int _fastcall deDeleteSubject(DATAEDIT * data, int number);

// �������� ��������� �� ��������� ������
// src    - ������ ��������
// number - ����� ���������� � src
// ��� ������ ���������� 0
int _fastcall deAppendSubject(TDataEdit * data, TDataEdit * src, int number);

// ������� ������ �� ����������
// data - ������ ����� ���������
// number - ����� ���������� � data
// ��� ������ ���������� 0
int _fastcall deLoadSubject(TDataEdit * data, TDataEdit * src, int number);

// ���������� ��������� �� ���������� ����������/�������
// �������� ����� ������ ��� ������ �� �����������
// ��� ������ ���������� ����
char * _fastcall deDescPointSubject(DATAEDIT * data, int number);

// ��������� ����� ����� � ����������
// number - ����� ���������� � data
// ��� ������ ���������� ����
int _fastcall dePointCount(DATAEDIT * data, int number);

// ���������� ��������� �� ������ ����� ������� ����������
// number - ���������������� ����� ����������
// ( 0 - ������, 1 - ������ ��������� � �.�.)
// ��� ������ ���������� ����
char * _fastcall deFirstPointSubject(DATAEDIT * data, int number);

// ���������� ��������� �� ��������� ����� ������� ����������
// number - ���������������� ����� ����������
// ( 0 - ������, 1 - ������ ��������� � �.�.)
// �������� ����� ����� �� ����������� !
// ��� ������ ���������� ����
char * _fastcall deLastPointSubject(DATAEDIT * data, int number);

// ���������� ��������� �� �������� ����� �������
// ���������� ������� ��� ����������
// ����� ������ ����� 1
// ��� ������ ���������� 0
char * _fastcall deGoPointSubject(DATAEDIT * data, int number, int subject);

// ���������� ��������� �� ��������� ����� �������
// ������� ��� ����������
// ��� ������ ���������� 0
char * _fastcall deNextPoint(DATAEDIT * data);

// ���������� ��������� �� ���������� ����� �������
// ������� ��� ����������
// ��� ������ ���������� 0
char * _fastcall dePrevPoint(DATAEDIT * data);

// �������� ����� � ������� �������/����������
// ��� ������ ���������� ����
int _fastcall deAppendPointSubject(DATAEDIT * data, int number,
                                   double * x, double * y);

// ��������� ���������� ������� ����� ����������/�������
// � ���� ����� � ��������� ������
double _fastcall deXDouble(DATAEDIT * data);
double _fastcall deYDouble(DATAEDIT * data);
double _fastcall deHDouble(DATAEDIT * data);

// ���������� ���������� ������� ����� ����������/�������
// � ���� ����� � ��������� ������
double _fastcall deSetXDouble(DATAEDIT * data, double * x);
double _fastcall deSetYDouble(DATAEDIT * data, double * y);
double _fastcall deSetHDouble(DATAEDIT * data, double * h);

// ��������� ���������� ������� ����� ����������/�������
// � ���� ������ �����
long _fastcall deXLong(DATAEDIT * data);
long _fastcall deYLong(DATAEDIT * data);

// �������� ����� � ������� �������/����������
// �� ������� ������
// ����������� ����� ���������� ������� ������
// ��� ������ ���������� ����
int _fastcall deInsertPoint(DATAEDIT * data, double * x,double * y);

// ������� ������� ����� ������� �������/����������
// ���� ����� �� ���� - ������ �� ���������
// ������� ���������� ����� ��������� �� ���������
// ��� ������ ���������� ����
int _fastcall deDeletePoint(DATAEDIT * data);

// ��������� ����� ������ ������ ����������
// ��� ������ ���������� 0
TEXTDATA * _fastcall deGetTextData(DATAEDIT * data);

// ��������� ������ ������������ ������ �� �����������
// (FA_LEFT,FA_RIGHT,FA_CENTER - ��. mapgdi.h)
int _fastcall deGetTextHorizontalAlign(DATAEDIT * data);

// ��������� ������ ������������ ������ �� ���������
// (FA_BOTTOM,FA_TOP,FA_BASELINE,FA_MIDDLE)
int _fastcall deGetTextVerticalAlign(DATAEDIT * data);

// ���������� ������ ������������ ������ �� �����������
// (FA_LEFT,FA_RIGHT,FA_CENTER)
int _fastcall dePutTextHorizontalAlign(DATAEDIT * data, int align,
                                       int subject);

// ���������� ������ ������������ ������ �� ���������
// (FA_BOTTOM,FA_TOP,FA_BASELINE,FA_MIDDLE)
int _fastcall dePutTextVerticalAlign(DATAEDIT * data, int align,
                                     int subject);

// ��������� ���������� ��������� ������
// text   - ����� ��� ���������� ������
// length - ����� ���������� ������� ��� ������
// ��� ������� ���������� ������������ �������� text,
// ���������� ������ ����� ��������� ANSI
// ��� ������ ���������� ����
char * _fastcall deGetText(DATAEDIT * data, char * text, int length);

// ���������� ����� ���������� ��������� ������    
// text   - ����� ����� ������ (���������� � ���� �����)
// ��� ������ ���������� 0
char * _fastcall dePutTextData(DATAEDIT * data, TEXTDATA * textdata, int isunicode);

// ���������� ����� ���������� ��������� ������
// text   - ����� ����� ������
// ��� ������� ���������� ������������ �������� text,
// ���������� ������ ������ ����� ��������� ANSI
// ��� ������ ���������� ����
char * _fastcall dePutText(DATAEDIT * data, const char * text, 
                           int code, int isunicode);

// �������� ������ ������ ������� (IDSHORT2,...)
// ��� ������ ���������� 0, ����� - ��� ������ ������� ������ !
int _fastcall deChangeKind(DATAEDIT * data, int format);

// �������� ������ ������ ������� �������� �������
// � ������ ���� ������� (text != 0) ��� �������� (text = 0)
// ��� ������ ���������� 0, ����� - ��� ������ ������� ������ !
int _fastcall deChangeTextFormat(DATAEDIT * data, int text);

// �������� ������ � ��� ����������
// ��� ������ ���������� 0
int _fastcall deAbridgeObject(DATAEDIT * data, int mode);

// ��������  ������/���������
// mode - = 0 - �������� ��������� �����
//              �� ���������, ���� ������ �������
//        = 1 - �������� ��������� �����
//        = 2 - �������� ������ �����
//        = 3 - �������� ��������� �����
//        = 4 - �������� ������ �����
// ������� - 1 - �������
// ��� ������ ���������� 0
int _fastcall deSetExclusiveSubject(DATAEDIT * data, int number, int mode);

// �������� �� ������� ���������� �����
// precision - �������� (0.0...n)
// height    - ������� ����� ���������� ������� 
// ��� ������ ���������� ����
int _fastcall deDeleteEqualPoint(DATAEDIT * data, double * precision,
                                 int height);

// ��������� ����������� �������/����������
// ����������:  1 - �������, 0 - ���������
int _fastcall deGetExclusiveSubject(DATAEDIT * data, int number);

// ����������� ��������� �������
// dframe - ����������� �������� �������/����������
// ��� ������ ���������� 0
int _fastcall deDimensions(DATAEDIT * data, DFRAME * dframe);

// ���������� ����� �������
double _fastcall dePolyPerimeter(DATAEDIT * data);

// ���������� ����� ����������/�������
// subject - ����� ���������� (���� = 0, �������������� ������)
double _fastcall dePolySubjectPerimeter(DATAEDIT* data, int subject); 

// ���������� ������� �������
double _fastcall deSquare(DATAEDIT * data);

// ����� ����� ����� � ������� � ������������
int _fastcall deTotalPointCount(DATAEDIT * data);

// �������� ���������� �������
// precision - ��������
// ���������� ����� ����� ����� �������
// ��� ������� ���������� <= 0
int _fastcall deLinearFilter(DATAEDIT * data, double * precision);

// �������� ��� ���������� ������� ������� �� ��������
// �������� (delta)
// ��� ������ ���������� ����
int _fastcall deRelocateObject(DATAEDIT * data, DOUBLEPOINT * delta);

// �������� ��� ���������� ������� �������/����������� �� ��������
// �������� (delta)
// number - ����� �������/����������
// ��� ������ ���������� ����
int _fastcall deRelocateSubject(DATAEDIT * data, int number,
                                DOUBLEPOINT * delta);

// ��������� ������ ������ ������ ( center )
// �� �������� ���� ( anglevalue ).
// ���� �������� � �������� � ����� ��������� ��������:
// �� 0 �� PI � �� 0 �� -PI ���  �� 0 �� PI � �� 0 �� 2PI
// ��� ������ ���������� 0
int _fastcall deRotateObject(DATAEDIT * data,
                             DOUBLEPOINT * center, double anglevalue);

// ��������� ������/��������� ������ ������ ( center )
// �� �������� ���� ( anglevalue ).
int _fastcall deRotateSubject(DATAEDIT * data, DOUBLEPOINT *center,
                              double anglevalue, int number);

// ��������������(factor) ������� �������
// factor - �����������
// deltanull - �������� ������������ 0
// ��� ������ ���������� ����
int _fastcall deScopeObject(DATAEDIT * data, DOUBLEPOINT *factor,
                            DOUBLEPOINT *deltanull);

int _fastcall deScopeSubject(DATAEDIT * data, DOUBLEPOINT *factor,
                             DOUBLEPOINT *deltanull, int number);

// �������������� (factor) � c������� ��� ���������� �������
// ������� �� �������� �������� (delta)
// factor - �����������
// deltanull - �������� ������������ 0
// delta - ��������������� ��������
// ��� ������ ���������� ����
int _fastcall deScopeAndRelocateObject(DATAEDIT * data,
                                       DOUBLEPOINT *factor,
                                       DOUBLEPOINT *deltanull,
                                       DOUBLEPOINT *delta);

int _fastcall deScopeAndRelocateSublect(DATAEDIT * data,
                                        DOUBLEPOINT *factor,
                                        DOUBLEPOINT *deltanull,
                                        DOUBLEPOINT *delta,
                                        int number);

// ����������� ������� � ������� ������� / ����������
// ��� ���������� ����� ����������� ��� ������ ���������� ����
int _fastcall deCrossCutData(DATAEDIT * data,
                             DOUBLEPOINT * xy1, DOUBLEPOINT * xy2,
                             int first, int last,
                             NUMBERPOINT * point1,
                             NUMBERPOINT * point2, int subject,
                             double precision);

// ����������� ������� � ������� ������� / ���������� 
// xy1, xy2 - ���������� �������
// data - ������� �������/����������
// subject - ����� �������/����������
// ( 0 - ������, 1 - ������ ��������� � �.�.)
// first - ����� ������ ����� �������
// last  - ����� ��������� ����� �������
// pointo - ��������� �� ������ �������� NUMBERPOINT �� 2 ���������
//          ��� ���������� ���������� �� �������� ������� (1-� � 2-� �����)
// pointm - ��������� �� ������ �������� NUMBERPOINT �� 2 ���������
//          ��� ���������� ���������� �� ������� ������� (1-� � 2-� �����)
//
// ���������� 0 - ��� ����� �����������
//            1 - ���� ����� ����������� ����� � pointo[0]
//           -1 - 1 ��� 2 ����� ����������� ����� � pointo �/��� pointm
// ����� ����������� ����� �� ����� ����� ��������� ������� � ������� �������
// �� ���� ����������� ���������� NUMBERPOINT :
//  -  ����� �����(Number) ���� ����� ����� �������,
//     �� ������� ��������� ����� �����������(Point)
//  -  Update != 0 - �������� ������� � ������� ������� ����� �� ����� ������
//            = 1 - ����� ����������� �������� �����������
//            < 0 - ����� ����������� ��������� � ������
//                  ��������� �������, ���� ��� pointm ( -1 ��� -2)
//                  ��� ������ ������� �������, ���� ��� pointo ( -1 ��� -2)
//            = 0 - ������ ����� �����������
int _fastcall deCrossCutDataEx(DATAEDIT * data,
                              DOUBLEPOINT * xy1, DOUBLEPOINT * xy2,
                              int first, int last,
                              NUMBERPOINT *pointo,
                              NUMBERPOINT *pointm, int subject,
                              double precision);

// ����������� ����������� ���������� �������/����������
// ����������: OD_PLUS      - �� ������� �������
//             OD_MINUS     - ������ ������� �������
//             OD_UNDEFINED - �� ����������
// ��� ������ ���������� ����
int _fastcall deGetDirection(DATAEDIT * data, int subject);

// ����������� ���������� ����� � ������������ x,y
// � ������/���������
// ��� ������ ���������� ����
int _fastcall deInside(DATAEDIT * data, DOUBLEPOINT * point, int subject);

// ����������� ��������� ������� / ����������
// ��� ������ ���������� 0
int _fastcall deDimensionsSubject(DATAEDIT * data, DFRAME * dframe,
                                  int subject);

// ���������� �������� ������� �������/����������
double _fastcall deSignedSquareSubject(DATAEDIT * data, int subject);

// ����������� ��������� �����, ������� �� ��������
// ���������� (�� ���������) �� �������� �����
// ��� ������ ���������� 0
int _fastcall deSeekVirtualPointByDistance(DATAEDIT * data,
                                           int number,
                                           double distance,
                                           DOUBLEPOINT *point,
                                           int subject);

// ����� ����� ������� ������� � �����������,
// ��������� � ��������
// ��� ����������� ������ ����������/�������
// ����� ������� ������� SubjectNumber()
// ��� ������ ���������� 0
int _fastcall deSeekNearPoint(DATAEDIT * data, double * x, double * y);

// ����� ����� ������� ����������,
// ��������� � ��������
// number - ���������������� ����� ����������
int _fastcall deSeekNearPointSubject(DATAEDIT * data, double * x,
                                     double * y, int number);

// ����� ����� �� ������� ������� ����������,
// ��������� � ��������
// ��� ������ ���������� 0
int _fastcall deSeekNearPointSubjectPart(DATAEDIT * data, double * x,
                                         double * y, int number,
                                         int first, int last);

// ����� ����� �� �������� ������� � �����������,
// ��������� � ��������
// ��� ����������� ������ ����������/�������
// ����� ������� ������� SubjectNumber()
// ��� ������ ���������� 0
int _fastcall deSeekNearVirtualPoint(DATAEDIT * data,
                                     double * x, double * y,
                                     XYDOUBLE * point);

// ����� ����� �� ������� ����������,
// ��������� � ��������
// ��� ������ ���������� 0
int _fastcall deSeekNearVirtualPointSubject(DATAEDIT * data,
                                            double * x, double * y,
                                            int number, XYDOUBLE * point);

// ����� ����� �� ������� ������� ����������
// � �������� ��������� �����, ��������� � ��������
int _fastcall deSeekNearVirtualPointSubjectPart(DATAEDIT * data,
                                 double * x,double * y, int number,
                                 int first, int last, XYDOUBLE * point);


// ����� ����� �� �������, ��������� � ��������
// segment - ������ �� 2-� ��������� (������� �� ���� �����)
// ��� ������ ���������� 0
// ���������� ����� ���������� �� ������ target
int _fastcall deSeekVirtualPointOnSegment(double * x,double * y,
                                          DOUBLEPOINT * point,
                                          DOUBLEPOINT * target);

// ���������� ��������� �� ���� �� ������� �������
// �.1 � �.3 (����� �.2 , ������ - radius)
// ��� ������ ���������� 0
int _fastcall deBuildCircular(DATAEDIT * data, DOUBLEPOINT * point1,
                              DOUBLEPOINT * point2,
                              DOUBLEPOINT * point3,
                              double radius);

// �������� ����������� ������� ����� �������
// ���������� ����� �������� ����������� ����������
// ��� ������ ���������� 0
int _fastcall deChangeDirection(DATAEDIT * data);

// �������� ����������� ������� ����������
// ��� ������ ���������� 0
int _fastcall deChangeDirectionSubject(DATAEDIT * data, int subject);

// ������� ����� � �������
// ��� ������ ���������� ����

int _fastcall deDeleteLoop(DATAEDIT * data, double * precision);

// ���������� ��������� ��� ���������� �� �������������
// �����������
// ��� ���������� ����� ����������� ������� �������������
// ��������� ��� ������ ���������� 0
int _fastcall deSetTranslate(DATAEDIT * data, TMap * map,
                             TTranslate *translate);       

// ��������� �������� ������� � ������ (�� �������)       
// frame - ����� ������� ��� ���������� ����������
// ��� ������ ���������� 0, ����� - frame
DFRAME * _fastcall deObjectFramePlane(DATAEDIT * data, DFRAME * dframe,
                                      TMap * map, int list);

// ���������� ������� �������/���������� �� ��� �������������
// �����������
// ��� ���������� ����� ����������� ������� �������������
// ��������� ���������� 0
// subject - ����� ����������
//       ( -1 - ������� ������� � ������� ������� �����������)
// ��������� � ������ �� ���������
// ��� ������ ���������� 0
double _fastcall deSquareReal(DATAEDIT * data, TMap * map, int subject); 


#endif

