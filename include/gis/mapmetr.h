
#ifndef MAPMETR_H
#define MAPMETR_H

#ifndef MAPVERSN_H
  #include "mapversn.h"
#endif

#ifndef MAPHDR_H
  #include "maphdr.h"
#endif

#ifndef MAPDAT_H
  #include "mapdat.h"
#endif

#ifndef MAPCALC_H
 #include "mapcalc.h"          
#endif

/***************************************************************
********************  ������� ��������� ************************
****************************************************************

    X� X�
  ^
  | (0,0) (������ �����������)
  +---------------------------------------------------> X�
  |                                                 ^
  |        (���������� ����)                        |
  |   (0,0)                      X�                 |
  |     ---------+------+------>                    |
  |     |        ...... |  ���� ������������        |
  |     |        ...... |                           |
  |     |        ...... |                           |
  |     |        ...... |                         ��������
  |     ---------+------+                      ������ (Region)
  |     |          ^                                |
  |     |          |                                |
  |     |         ������� �������� ������           |
  |     V                  (Draw)                   |
  |       Y�                                        |
  |                                                 |
  | ZeroX,ZeroY (�����)                             V
  +----------------------------------------------------> Y� Y�
  |  0,0 (������ ������ � ���������
  |       � ��������)
  |
  V
    Y�

****************************************************************
****************************************************************/

#define MINV -65000.0
#define MAXV  65000.0
#define ROUNDL(x) ROUND(max(MINV, min(MAXV, x)))

class _DLLCLASS TMapMetricMemory
{
public :

 TMapMetricMemory();

 ~TMapMetricMemory();

 // �������� ������ ��� ����� ���������
 int AllocateMetricMemory(int pointlimit = 0);

public :

 // ���������� � �������, ����������� ��� ������ � ����� ��� ���� �����������
 // ������� ����� �������� ������, ���������� ��� �������������� ���������
 // ---------------------------------------------------------------------------

 int GlobalPointLimit;       // ���������� ��������                  
 int GlobalPolyLimit;        // ��������� ������������ ��������
 int GlobalTextLimit;        // �������� �����

 int AllocBuffPointError;    // ������� ������ ��������� �� ������ ��������� ������
                             // (�� ������������ ���������)

 XYTYPE *    GlobalPointArea;// ����� ������� �����
 long int *  GlobalPolyArea; // ����� ������� ��������� �����
 char **     GlobalTextArea; // ����� ������� ������� ��������

 char * lpPoint;             // ����� ���������� ������� ������
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  ����� "�������� ������� ��'����� " +++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TMapMetric : public TMapMetricMemory
{
public :

 // ������������� ������ ��� ��������� �������

 TMapMetric();

 // ���������� �������

 ~TMapMetric();

 // ��������� �������������� ������� ������� � ����������
 // ���������� �����������
 // ��� �������� ���������� ���������� 0 !

 int _fastcall BuildMetric(TObjectDesc desc, OBJECTDATA * data, POLYDATAEX * polydata);

 // ���������� ��������� ������� �����������
 // ������������ �������� ����� � ��������
 // viewposition - ���������� ����� � ������ � ���������

 void _fastcall SetListPosition(DOUBLEPOINT * viewposition);

 // ���������� ��������� ������������ �������
 // ������������ �������� ����� � ��������
 // listframe - ���������� ����� � ������ � ���������

 void _fastcall SetListPosition(DOUBLEPOINT * viewposition, DFRAME * frame);

 // ���������� ��������� ������� ����������� �����
 // ���������� � ��������
 // ���������� ������ ������ ��������, ������� ����������
 // ������������ ����� ���������� �����������

 double SetSitePosition();

 // ���������� ��������� ������������ ������� ��� �����
 // ���������� ������������ �������� ����� � ��������
 // listframe - ���������� ����� � ������ � ���������
 // ���������� ������ ������ ��������, ������� ����������
 // ������������ ����� ���������� �����������

 double _fastcall SetSitePosition(DFRAME * Draw);

 // ������ ���������� ������

 void ClassLock();

 // ���������� ���������� ������

 void ClassUnLock();

 /***************************************************************
 *                                                              *
 *      ������� ��������� ���������                             *
 *                                                              *
 ***************************************************************/

public :

 // ������� ������� ?
 int TurnIsActive() { return TurnActive; }

 // ���������/���������� ���� �������� �����
 double GetTurnAngle() { return Angle; }
 double SetTurnAngle(double angle, double fixation);

 // ����������� �������� � ������� � ������� � ������ ��������
 void Pix2Dis(DOUBLEPOINT& pix, DOUBLEPOINT& dis);
 void Dis2Pix(DOUBLEPOINT& dis, DOUBLEPOINT& pix);
 void Dis2Pix(DOUBLEPOINT& dis, POINT& pix);

 // ����������� �������� � ����� � �������
 double Dis2MetX(double disX) {return (ZeroX + MetInDis*disX);}
 double Dis2MetY(double disY) {return (ZeroY + MetInDis*disY);}
 double Met2DisX(double metX) {return ((metX-ZeroX)*DisInMet);}
 double Met2DisY(double metY) {return ((metY-ZeroY)*DisInMet);}

 // ����������� �������� ������ � �������� � �������
 double Elem2Dis(double element) {return element*DisInElem;}
 double Dis2Elem(double discret) {return discret*ElemInDis;}

 // ����������� �������� � ������� � �������
 double HorDis2Pix(double discret) {return discret*HorPixInDis;}
 double HorPix2Dis(double pixel) {return pixel*HorDisInPix;}
 double VerDis2Pix(double discret) {return discret*VerPixInDis;}
 double VerPix2Dis(double pixel) {return pixel*VerDisInPix;}

 long HorDis2PixL(double discret) {return ROUND(discret*HorPixInDis);}
 long HorPix2DisL(double pixel) {return ROUND(pixel*HorDisInPix);}
 long HorDis2Pix(long discret) {return ROUND(discret*HorPixInDis);}
 long HorPix2Dis(long pixel) {return ROUND(pixel*HorDisInPix);}

 long VerDis2PixL(double discret) {return ROUND(discret*VerPixInDis);}
 long VerPix2DisL(double pixel) {return ROUND(pixel*VerDisInPix);}
 long VerDis2Pix(long discret) {return ROUND(discret*VerPixInDis);}
 long VerPix2Dis(long pixel) {return ROUND(pixel*VerDisInPix);}

 // ����������� �������� ������ � ������� � �������
 double HorElem2Pix(double element) {return element*HorPixInElem;}
 double HorPix2Elem(double pixel) {return pixel*HorElemInPix;}
 long   HorElem2PixL(double element) {return ROUND(element*HorPixInElem);}
 long   HorPix2ElemL(double pixel) {return ROUND(pixel*HorElemInPix);}
 long   HorElem2Pix(long element) {return ROUND(element*HorPixInElem);}
 long   HorPix2Elem(long pixel) {return ROUND(pixel*HorElemInPix);}

 double VerElem2Pix(double element) {return element*VerPixInElem;}
 double VerPix2Elem(double pixel) {return pixel*VerElemInPix;}
 long   VerElem2PixL(double element) {return ROUND(element*VerPixInElem);}
 long   VerPix2ElemL(double pixel) {return ROUND(pixel*VerElemInPix);}
 long   VerElem2Pix(long element) {return ROUND(element*VerPixInElem);}
 long   VerPix2Elem(long pixel) {return ROUND(pixel*VerElemInPix);}

 // ����������� �������� ��������� �� ������� � �������
 void RegionDisToPix(DFRAME& regiondis, DFRAME& regionpix);

 // ����������� �������� �� ��������� � �������
 void RegionElemToPix(DFRAME& regionelem, DFRAME& regionpix);

 // ����������� �������� �� ��������� � ��������
 void RegionElemToDis(DFRAME& regionelem, DFRAME& regiondis);

 // ����������� ���������� ������� ������������ ������������
 // ������� ��������� ������
 // ���������: - ���������� ������� ����������� � ��������
 //              ������������ ������� �����������;
 // ���������� ������� �������� ��������� � ������
 DFRAME& SetDrawPlace(RECT& drawpix);

 // ������������ ���������� ������� ������������
 void RestoreDrawPlace();

 double& GetDiscret() { return Discret; }
 double SetDiscret(double digit)
 {
   double OldDiscret = Discret;
   Discret = digit;
   UpdatePlace();
   return OldDiscret;
 }

 double SetElement(double elemmetr)
 {
   double OldElement = Element;
   Element = elemmetr;
   UpdatePlace();
   return OldElement;
 }

 // ���������� "�������� ���������� ������"
 void _fastcall SetPixel(double& horpixel, double& verpixel);

 // ��������� "�������� ���������� ������"
 double& GetHorizontalPixel() {return HorizontalPixel;}
 double& GetVerticalPixel() {return VerticalPixel;}

 // ����������� ������������ � �������� �����������
 void UpdatePlace();

 // ������� ��������� ��������
 // change - ����������� ��������� �������� �������� ( > 0)
 // scale  - ����� �������� �������� �����������
 // ���������� ����� �������� ������������ ���������������
 double GetDrawScale() {return ViewScale;}
 double ChangeDrawScale(double change);
 double SetDrawScale(double scale);

 DFRAME GetRegionPix() {return RegionPix;}

 // ��������� ����� ������ � number �������
 double GetMetInDis() { return MetInDis; }
 double GetMetInDis(double number)
   { return MetInDis * number; }

 // ��������� ������� ������ � number ��������
 double GetMetInPix()
   { return MetInDis * HorPix2Dis((double)1); }
 double GetMetInPix(double number)
   { return MetInDis * HorPix2Dis(number); }

 double GetHorMetInPix()                           
   { return MetInDis * HorDisInPix; }
 double GetVerMetInPix()
   { return MetInDis * VerDisInPix; }

 // ��������� ���������� ����� �������� �����
 // � ������������� ������� ��������� � ������
 double& GetZeroX() { return ZeroX; }
 double& GetZeroY() { return ZeroY; }

protected:

 // ����������� �������� ������ (� �������� � ���������)
 //  regionelem - �������� ������ � ���������
 //  precision  - ������ ��������
 void UpdateRegionElem(DFRAME& regionelem, double& precision);

 // ���������� ���������� ����� �������� �����
 // � ������������� ������� ��������� � ������
 double SetZeroX(double x) { return ZeroX = x; }
 double SetZeroY(double y) { return ZeroY = y; }

 // ���������� ����� ������ � ����� ��������
 double SetMetInDis(double metindis)
 {
   MetInDis = metindis;
   DisInMet = 1.0/MetInDis;
   return MetInDis;
 }

 // ��������� ����� (��������� �������)
 //  turnpoint - ���������� ���������� �����
 void Turn(DOUBLEPOINT& point, DOUBLEPOINT& turnpoint);
 void Inverse(DOUBLEPOINT& point, DOUBLEPOINT& turnpoint);

 // ��������� ������������ (��������� �������)
 //  turnframe - �������� ����������� �������������
 void Turn(DFRAME& frame, DFRAME& turnframe);
 void Inverse(DFRAME& frame, DFRAME& turnframe);

public:

 // ������ ��� ���������� �����
 // --------------------------

 DFRAME RegionPix;    // �������� ������ ������ � ��������   
 DFRAME DrawDPix;     // ������� ����������� � ��������      
 DFRAME SaveDrawDPix; // � ������ ����� (1-�.�.; 2-�.�.)     

 DFRAME RegionDis;    // �������� ������ ������ � ���������
 DFRAME DrawDis;      // ������� ����������� � ���������
                      // � ������ ����� (1-�.�.; 2-�.�.)

 DFRAME DrawMet;      // ������� ����������� ����������
                      // � ������ (1-�.�.; 2-�.�.)

 DRAWSIZE szDraw;     // ������ � ������ ������� ���������      

 double ZeroX;        // ���������� ����� �������� �����
 double ZeroY;        // � ������������� ������� ��������� (�����)

 double MetInDis;     // ������ �� ��������� � ����� ��������
 double DisInMet;     // ����� ������� �� ���� ���������

 double ViewScale;    // ������� ������� �����������
                      // = 5   -> ����������� ��������� � 5 ���
                      // = 0.1 -> ����������� ��������� � 10 ���

 double VerticalPixel;    // ����� ����� �� ���� �� ����������
 double HorizontalPixel;  // ����� ����� �� ���� �� ����������
 double Discret;          // ����� ����� �� ���� �� �����

 double HorDisInPix;     // ����� ����� ����� � ����� ������
 double HorPixInDis;     // ����� ����� ������ � ����� �����
 double VerDisInPix;     // ����� ����� ����� � ����� ������
 double VerPixInDis;     // ����� ����� ������ � ����� �����

 double Element;         // ����� ��������� �� ���� � ������
 double HorElemInPix;    // ����� ��������� ������ � ����� ������
 double HorPixInElem;    // ����� ����� ������ � �������� ������
 double VerElemInPix;    // ����� ��������� ������ � ����� ������
 double VerPixInElem;    // ����� ����� ������ � �������� ������

 double DisInElem;       // ����� ����� ����� �� �������
 double ElemInDis;       // ����� ��������� � ����� ������

 double Angle;           // ���� �������� �����
 double SinTurn;         // sin ���� �������� �����
 double CosTurn;         // cos ���� �������� �����
 int TurnActive;         // ���� ����������� ��������


 FRAME ListDrawBorder;    // ������� ������������ ������� � �����
                          // ��� �������� ��������� ��������

 DOUBLEPOINT AreaInList;  // ��������� ������� ������������ �
                          // ������� ����� �����

 long int BaseScale;      // ������� ������� ����������� �����

 // ����������, ����������� ��� ������ � ���������� ���������
 // ------------------------------------------------------------------------------

 char * lpWork;              // ����� ������ ������� ���������� �������
 long int WorkSize;          // ������ ������� ������� (24�)

 TSpline Spline;             // ���������� ������� �� ������� 
 int     HideSplineFlag;     // ������� ������ ���������� �������

#ifndef HIDESECTION
 MAPCRITICALSECTION Section;              
#endif
};

typedef  TMapMetric MAPBASE;

// ������������� ������ ��� ��������� �������
void _fastcall mmInit(MAPBASE * data);

// ���������� �������
void _fastcall mmFree(MAPBASE * data);

// ���������� "�������� ���������� ������"
void _fastcall mmSetPixel(MAPBASE * data, double * hpixel, double * vpixel);

// ����������� ������������ � �������� �����������
void _fastcall mmUpdatePlace(MAPBASE * data);

// ���������� ������� �����������
void _fastcall mmSetDrawScale(MAPBASE * data, double * scale);

// ���������� ���� �������� �����
void _fastcall mmSetTurnAngle(MAPBASE * data, double * angle,
                              double * fixation);

// ����������� ���������� ������� ������������ ������������
// ������� ��������� ������
void _fastcall mmSetDrawPlace(MAPBASE * data, RECT * drawpix);

// ������������ ���������� ������� ������������
void _fastcall mmRestoreDrawPlace(MAPBASE * data);

// ����������� �������� �� ������� � �������
void _fastcall mmRegionDisToPix(MAPBASE * data, DFRAME * regiondis,
                                DFRAME * regionpix);

// ����������� �������� �� ��������� � �������
void _fastcall mmRegionElemToPix(MAPBASE * data, DFRAME * regionelem,
                                 DFRAME * regionpix);

// ����������� �������� �� ��������� � ��������
void _fastcall mmRegionElemToDis(MAPBASE * data, DFRAME * regionelem,
                                 DFRAME * regiondis);

// ���������� �������� ������ � ���������
void _fastcall mmSetRegionDis(MAPBASE * data, DFRAME * regiondis);

// �������� �������� ������
void _fastcall mmUpdateRegionElem(MAPBASE * base, DFRAME * regionelem,
                                  double * precision);

// ��������� �������� ������ �� �������� delta
void _fastcall mmEnlargeRegionDis(MAPBASE * base, double * delta);

// ��������� �����
void _fastcall mmTurn(MAPBASE * base, DOUBLEPOINT * point,
                      DOUBLEPOINT * turnpoint);

// ��������� ����� �������
void _fastcall mmInverse(MAPBASE * base, DOUBLEPOINT * point,
                         DOUBLEPOINT * turnpoint);

// ��������� ������������
void _fastcall mmTurnFrame(MAPBASE * base, DFRAME * frame, DFRAME * turnframe);

// ��������� ������������ �������
void _fastcall mmInverseFrame(MAPBASE * base, DFRAME * frame, DFRAME * turnframe);

// ����������� ������� � �������� � ������ ��������
void _fastcall mmPix2Dis(MAPBASE * base, DOUBLEPOINT * pix,
                         DOUBLEPOINT * dis);

// ����������� �������� � ������� � ������ ��������
void _fastcall mmDis2Pix(MAPBASE * base, DOUBLEPOINT * dis,
                         DOUBLEPOINT * pix);

// ����������� �������� � ������� � ������ ��������
void _fastcall mmDis2PixDraw(MAPBASE * base, DOUBLEPOINT * dis,
                             POINT * pix);

// ���������� ��������� ������� �����������
// ������������ �������� ����� � ��������
// viewposition - ���������� ����� � ������ � ���������
void _fastcall mmSetListPosition(MAPBASE * data, DOUBLEPOINT * viewposition);

// ���������� ��������� ������������ �������
// ������������ �������� ����� � ��������
// viewposition - ���������� ����� � ������ � ���������
void _fastcall mmSetListPositionDraw(MAPBASE * data,
                                     DOUBLEPOINT * viewposition,
                                     DFRAME * draw);

// ���������� ��������� ������� ����������� �����
// ���������� � ��������
// ���������� ������ ������ ��������, ������� ����������
// ������������ ����� ���������� �����������
double _fastcall mmSetSitePosition(MAPBASE * data);

// ���������� ��������� ������������ ������� ��� �����
// ���������� ������������ �������� ����� � ��������
// draw - ���������� ����� � ������ � ���������
// ���������� ������ ������ ��������, ������� ����������
// ������������ ����� ���������� �����������
double _fastcall mmSetSitePositionDraw(MAPBASE * data, DFRAME * draw);

// ��������� �������������� ������� ������� � ����������
// ���������� �����������
// ��� ������ ���������� ����
int _fastcall mmBuildMetric(MAPBASE * base, TObjectHead * head,
                            OBJECTDATA * data, POLYDATAEX * polydata);  

// ������� ������� ������� ������� �� ��������� ���������� ���������
void mmCutMetric(MAPBASE * base, POLYDATAEX * polydata);  

// ���������� ����� ������ � ����� ��������
void _fastcall mmSetMetInDis(MAPBASE * base, double * metindis);

// ���������� ������ ��������
void _fastcall mmSetDiscret(MAPBASE * data, double * digit);

// ���������� ������ ��������
void _fastcall mmSetElement(MAPBASE * data, double * elemmetr);


// ������� ����������������� ������, ����������� ��� ������������� ���������
// ��� ������ ���������� ����
int _fastcall mmReAllocBuffPoint(TMapMetricMemory * base, int pointcount);     

// ������� ��������� ������� ������, ����������� ��� ������������� ���������
int _fastcall mmAllocBuffPoint(TMapMetricMemory * base, int pointlimit = 0);

// ������� ������������ ������� ������, ����������� ��� ������������� ���������
void _fastcall mmFreeBuffPoint(TMapMetricMemory * base);


#endif

