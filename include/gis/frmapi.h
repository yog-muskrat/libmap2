
#ifndef FRMAPI_H
 #define FRMAPI_H

#ifndef HMAP
 #include "mapapi.h"
 #include "logapi.h"
#endif



#define FRMELEMENTCOUNT 7

#define FRM_ERROR    -1
#define FRM_RSCFRAME  1
#define FRM_NAMES     2
#define FRM_RSCCORN   3
#define FRM_TERRAIN   4
#define FRM_COORD     5
#define FRM_LISTNAME  6

typedef long int  HBORDER;       // ����� ���������� �����

typedef struct OUTFRAME
{
 long int InLineCode;
 long int OutLineCode;
 long int BarCode;
 double Wide;
}OUTFRAME;

typedef struct RSCNEIG
{
 long int Code;
 long int Neig;
 long int Point;
 double X1;
 double X2;
 double Y1;
 double Y2;
 double Allign;
}RSCNEIG;


typedef struct RSCLINE
{
 long int Use;
 long int Code;
 double X1;
 double Y1;
 double X2;
 double Y2;
}RSCLINE;

//---------------------------------------------------------------------------
// ����� ��������� ��������
//---------------------------------------------------------------------------

typedef struct LINESCALE
{
 long int Use;
 long int Code;
 double Distance;      // ���������� �� ���������� �����
 double X;             // ����� �������� (������ ����)
 double Y;             // ����� �������� (�����)
}LINESCALE;


typedef struct GEONET
{
 long int LongLineCode;
 long int LineCode;      // ��� ���������� �����
 long int BarCode;       // ��� ����������� ��������
 long int ListNumber;    // ����� ������������ �����
 double   Distance;      // ���������� �� ���������� �����
 double   Wide;          // ������
 double   ExWide;        // ������ 10- ��������� ���� (��� 50-100 ���.)
}GEONET;

typedef struct GEOFRAME
{
 double B_SW;  // B �-�
 double L_SW;  // L �-�
 double B_NW;  // B �-�
 double L_NW;  // L �-�
 double B_NE;  // B �-�
 double L_NE;  // L �-�
 double B_SE;  // B �-�
 double L_SE;  // L �-�
}GEOFRAME;

extern "C"
{
//--------------------------------------------------------------
// ��������� ���������� ��������� ��������� ����������
//--------------------------------------------------------------
int WINAPI _export frmGetElementsCount();
//--------------------------------------------------------------
// ��������� �������� �������� ���������� �� ��� ������
//--------------------------------------------------------------
const char * WINAPI _export frmGetElementName(int number, int language);
//--------------------------------------------------------------
// ��������� ������������� �������� ���������� �� ��� ������
//--------------------------------------------------------------
int WINAPI _export frmGetElementIdent(int number);
//--------------------------------------------------------------
// ��������� ��� �������� ���������� �� ��� ������ (1-������ ��� ��������)
//--------------------------------------------------------------
int WINAPI _export frmGetTopoOnly(int number);

HBORDER WINAPI _export frmBorderCreate(HMAP hmap,HSITE site,HOBJ frame);
int WINAPI _export frmBorderFree(HBORDER border);                        



//--------------------------------------------------------------------------
//                    ��������� ����������� ����������
//
// Hmap      - ��������
// sheet     - ����� ������������ �����
// rotsit    - ���������� ����
// frmsit    - ����� ������������ ����������� ����������
// FrameTemp - ��� ����� ������� ����������� ����������
// Angle     - ���� �������� ������������ �����
// lblname   - ���� �������� ����������� �������
// logfile   - ���� ���������
// mestarget - ��� ��������� (0-������ ����,1-������ �����,2-����+�����)
//
//       ��� ������ ���������� 0
//--------------------------------------------------------------------------


int WINAPI _export frmCreateBorder(HMAP Hmap,int sheet,HSITE rotsit,
                   HSITE frmsit,char *FrameTemp,double Angle,
                   char *logfile,int mestarget);


//--------------------------------------------------------------------------
//              ��������� ������� ����������� ����������
//
// Hmap    - ��������
// sheet   - ����� ������������ �����
// rotsit  - ���������� ����
// legsit  - ����� ����������� �������
// lblname - ���� �������� ����������� �������
// Angle   - ���� �������� ������������ �����
// logfile   - ���� ���������
// mestarget - ��� ��������� (0-������ ����,1-������ �����,2-����+�����)
//       ��� ������ ���������� 0
//
//--------------------------------------------------------------------------

int WINAPI _export frmCreateLegend(HMAP Hmap,int sheet,HSITE rotsit,
                   HSITE legsit,char *lblname,double Angle,
                   char *logfile,int mestarget);

//--------------------------------------------------------------------------
// ����������� ������������ ����� ����� � ������������� ���������
// ��� ������ �������� (5 000 - 200 000)
// sheet      - ����� �������� �����
// neighbour  - ����� ������ (0-����,1-���,2-���,3-����,4-���)
// name       - ������ ��� ���������� (������ MAX_PATH)
// ��� ������ ���������� 0
//--------------------------------------------------------------------------
int WINAPI _export  frmNeighbourCalculate(HMAP hmap,int sheet,int neighbour,
                                          int scale,char *name);

//--------------------------------------------------------------------------
// ����������� ������������ ����� ����� � ������������� ���������
// ��� ��������  1 : 5000
// listnumber       - ����� �������� �����
// neighbournumber  - ����� ������ (0-����,1-���,2-���,3-����,4-���)
// string           - ������ ��� ���������� (������ MAX_PATH)
// ��� ������ ���������� 0
//--------------------------------------------------------------------------
int WINAPI _export frmNeighbourCalculate5000(HMAP hmap,int listnumber,int neighbournumber,
                           char *string);
//--------------------------------------------------------------------------
// ����������� ������������ ����� ����� � ������������� ���������
// ��� ��������  1 : 100000
// listnumber       - ����� �������� �����
// neighbournumber  - ����� ������ (0-����,1-���,2-���,3-����,4-���)
// string           - ������ ��� ���������� (������ MAX_PATH)
// ��� ������ ���������� 0
//--------------------------------------------------------------------------
int WINAPI _export frmNeighbourCalculate100000(HMAP hmap,int listnumber,int neighbournumber,
                           char *string);
//--------------------------------------------------------------------------
// ����������� ������������ ����� ����� � ������������� ���������
// ��� ��������  1 : 200000
// listnumber       - ����� �������� �����
// neighbournumber  - ����� ������ (0-����,1-���,2-���,3-����,4-���)
// string           - ������ ��� ���������� (������ MAX_PATH)
// ��� ������ ���������� 0
//--------------------------------------------------------------------------
int WINAPI _export frmNeighbourCalculate200000(HMAP hmap,int listnumber,int neighbournumber,
                           char *string);
//--------------------------------------------------------------------------
// ����������� ������������ ����� ����� � ������������� ���������
// ��� ��������  1 : 500000
// listnumber       - ����� �������� �����
// neighbournumber  - ����� ������ (0-����,1-���,2-���,3-����,4-���)
// string           - ������ ��� ���������� (������ MAX_PATH)
// ��� ������ ���������� 0
//--------------------------------------------------------------------------
int WINAPI _export frmNeighbourCalculate500000(HMAP hmap,int listnumber,int neighbournumber,
                           char *string);

//--------------------------------------------------------------------------
// ����������� ������������ ����� ����� � ������������� ���������
// ��� ��������  1:1 000 000
// listnumber       - ����� �������� �����
// neighbournumber  - ����� ������ (0-����,1-���,2-���,3-����,4-���)
// string           - ������ ��� ���������� (������ MAX_PATH)
// ��� ������ ���������� 0
//--------------------------------------------------------------------------
int WINAPI _export frmNeighbourCalculate1000000(HMAP hmap,int listnumber,int neighbournumber,
                           char *string);


//--------------------------------------------------------------------------
// ����������� ������������ ����� ����� � ������������� ���������
// ��� ��������  1 : 25000
// listnumber       - ����� �������� �����
// neighbournumber  - ����� ������ (0-����,1-���,2-���,3-����,4-���)
// string           - ������ ��� ���������� (������ MAX_PATH)
// ��� ������ ���������� 0
//--------------------------------------------------------------------------
int WINAPI _export frmNeighbourCalculate25000(HMAP hmap,int listnumber,int neighbournumber,
                           char *string);
//--------------------------------------------------------------------------
// ����������� ������������ ����� ����� � ������������� ���������
// ��� ��������  1 : 10000
// listnumber       - ����� �������� �����
// neighbournumber  - ����� ������ (0-����,1-���,2-���,3-����,4-���)
// string           - ������ ��� ���������� (������ MAX_PATH)
// ��� ������ ���������� 0
//--------------------------------------------------------------------------
int WINAPI _export frmNeighbourCalculate10000(HMAP hmap,int listnumber,int neighbournumber,
                           char *string);
//--------------------------------------------------------------------------
// ����������� ������������ ����� ����� � ������������� ���������
// ��� ��������  1 : 50000
// listnumber       - ����� �������� �����
// neighbournumber  - ����� ������ (0-����,1-���,2-���,3-����,4-���)
// string           - ������ ��� ���������� (������ MAX_PATH)
// ��� ������ ���������� 0
//--------------------------------------------------------------------------
int WINAPI _export frmNeighbourCalculate50000(HMAP hmap,int listnumber,int neighbournumber,
                           char *string);
//--------------------------------------------------------------------------
// ����������� ���� ������������ ����� ����� � ������������� ���������
// listnumber       - ����� �������� �����
// string           - ������ ��� ���������� (������ MAX_PATH)
// ��� ������ ���������� 0
//--------------------------------------------------------------------------
int WINAPI _export frmCodeCalculate(HMAP hmap,int listnumber,char *string);

//-----------------------------------------------------------------------
// ����������� ���� ��������� �����
//
//  hmap       - ������������� �����
//  listnumber - ����� �����
//  alfa       - ���������� ��� ������ ����������
//
//  ��� ������ ���������� 0
//-----------------------------------------------------------------------

int WINAPI _export frmGetRotateAngle(HMAP hmap,int listnumber,double *alfa);

//-----------------------------------------------------------------------------
// ������� ����� ����� ������������ ��� - ��������� ����
//
// handle        - ������������� ���� ��� ������������ �������
// hmap          - ������������� �������� �����
// listnumber    - ����� ��������������� �����
// alfa          - ���� ��������
// RotateName    - ��� ����������� �����
// RotateRscName - ������������� ����������� �����
//
// ��� ������ ���������� 0
//-----------------------------------------------------------------------------

int WINAPI _export frmTurnSheet(TASKPARM *parm,HMAP hmap,int listnumber,double alfa,
                 HSITE rotSit);

//-----------------------------------------------------------------------------
// ������� ���������� ����� (FrameCode),
//         �������    ����� (LineCode),
//                      ��� (FillCode)
// � ������ ����� �������
// hmap     - ������������� �������� �����
// site     - ���������� ����
// delta    - ���������� ����� ���������� � ������� ������� � ��
// info     - ����� ����������� �����
// mode = 1 - ���������� ������
//
// ��� ������ ���������� 0
//-----------------------------------------------------------------------------

int WINAPI _export frmCreateFrameFill(HMAP hmap,HSITE site,double delta,long int LineCode,
                       long int FillCode,long int FrameCode,HOBJ info,int mode = 0);

int WINAPI _export frmCreateOutFrame(HBORDER border,OUTFRAME *frame);

//--------------------------------------------------------------
// ���������� ����� ����������� ��������
// �������� ������ 2-� � 4-� �����!
//--------------------------------------------------------------

int WINAPI _export frmSetCross(double  X1,double Y1,double *X2,double *Y2,
                               double  X3,double Y3,double *X4,double *Y4);


//--------------------------------------------------------------
// ����� ����� ����������� ��������
//--------------------------------------------------------------

int WINAPI _export frmGetCross(double  X1,double Y1,double X2,double Y2,
                double  X3,double Y3,double X4,double Y4,
                double *XN,double *YN);

//----------------------------------------------------------------------
// ��������� ������������ � ���� ������������ (����� �� ��������)
// �������������, ����� ������� � �.x,y (m)
//----------------------------------------------------------------------

int WINAPI _export frmNomenclatureCreate(HMAP hmap,HSITE site,long int code,char *text,
                                         long int code1,char *textex,double x,double y);


//----------------------------------------------------------------------
// ��������� �������� ����� (�� ������ ��� ������� ������, ����� �� ��������)
//----------------------------------------------------------------------

int WINAPI _export frmSheetNameCreate(HMAP hmap,HSITE site,long int code,char *text,
                                      double x,double y);


//--------------------------------------------------------------
// ������� ����� ��������� ����
// ��� frameinfo (��������� ������) != 0  - ����� ���������� ��
// frameinfo
// key - ����� �������� ������� (��� ������) -1 - ������ �� ���������
//--------------------------------------------------------------

int WINAPI _export frmCreateRscLine(HMAP hMap,HSITE hSite,double x1,double x2,
                                    double y1,double y2,int excode,
                                    HOBJ frameinfo = 0,long int key = -1);


//--------------------------------------------------------------
// ������� ������������� ��������� ����
//--------------------------------------------------------------

int WINAPI _export frmCreateRscBox(HMAP hMap,HSITE hSite,double x1,double x2,
                   double y1,double y2,int excode,int local = LOCAL_LINE,long int key = -1);

//--------------------------------------------------------------
// ������� ������� ��������� ����
//--------------------------------------------------------------

int WINAPI _export frmCreateRscPolygon(HMAP hMap,HSITE hSite,int pointcount,DOUBLEPOINT *data,
                                    int excode,int local = LOCAL_SQUARE,long int key = -1);

//--------------------------------------------------------------
// ������� ����� ��������� ����
// key - ����� �������� ������� (��� ������) -1 - ������ �� ���������
//--------------------------------------------------------------

int WINAPI _export frmCreateRscTitle(HMAP hMap,HSITE hSite,
                   double x1,double x2,double y1,double y2,
                   int excode,int wide,char *text,int align = 0,long int key = -1);

//--------------------------------------------------------------
// ��������������� ������� ������������ ����� �������
//--------------------------------------------------------------

int WINAPI _export frmSetTextPosition(double *X1,double *X2,
                    double *Y1,double *Y2,
                    double MinX,double MinY,
                    double MaxX,double MaxY,int position,double MetInMm);

//--------------------------------------------------------------
// ������� ������� ����� �����
// key - ����� �������� ������� (��� ������) -1 - ������ �� ���������
// bg = 0 - ��� �� ���������
//--------------------------------------------------------------

int WINAPI _export frmCreateNetLabel(HMAP hmap,HSITE hSit,double x1,double y1,int excode,
                   int hor,int vert,char *text,int direct = 0,
                   long int key = -1,int bg = 1);


//----------------------------------------------------------------------
// ��������� ����� ��������
//----------------------------------------------------------------------

int WINAPI _export frmCreateMeridian(HMAP hmap,HSITE hSit,HOBJ info,
                                     LISTREGISTER *sheetreg,char *String);


//----------------------------------------------------------------------
// ��������� ������� ������������ ����� ������� ����
//----------------------------------------------------------------------

int WINAPI _export frmCreateAdjZone(HMAP Hmap,HSITE hSit,MAPREGISTER  *mapreg,
                                    LISTREGISTER *sheetreg,HOBJ info,DOUBLEPOINT *framepoint,
                                    char *string,double alfa);

//------------------------------------------------------------------------
//      ���������� ������������� ����� ��� 1:10 000
//------------------------------------------------------------------------

int WINAPI _export frmCreateGeo10000(HMAP hmap,HSITE hSit,GEONET *geonet,HOBJ info);

//------------------------------------------------------------------------
//      ���������� ������������� ����� ��� 1:50 000
//------------------------------------------------------------------------

int WINAPI _export frmCreateGeo50000(HMAP hmap,HSITE hSit,GEONET *geonet,HOBJ info);

//------------------------------------------------------------------------
//      ���������� ������������� ����� ��� 1:200 000
//------------------------------------------------------------------------

int WINAPI _export frmCreateGeo200000(HMAP hmap,HSITE hSit,GEONET *geonet,HOBJ info);  

//------------------------------------------------------------------------
// ������� ������������ ���� ������� �� ����� ����� �����
//------------------------------------------------------------------------

int WINAPI _export frmCreateAllNeighbour(HMAP hmap,HSITE hSit,HOBJ frameinfo,char *buf,int listnumber);

//---------------------------------------------------------------------
//     ����� (�������)
//---------------------------------------------------------------------

int WINAPI _export frmCreateDrawLine(HMAP hmap, HSITE hsite,double x1,double x2,
                                     double y1,double y2,double thick,long int color,long int key = -1);

//---------------------------------------------------------------------
//     ����������� ������������� (�������)
//---------------------------------------------------------------------

int WINAPI _export frmCreateDrawBar(HMAP hmap, HSITE hsite,double x1,double x2,
                                        double y1,double y2,long int color,long int key = -1);
//-------------------------------------------------------------------------
// ����������� �������� ������� ��� 1:1000 000
//-------------------------------------------------------------------------

int WINAPI _export frmCreateLinescale1000000(HMAP hmap,HSITE hSit,LINESCALE *scale);

//-------------------------------------------------------------------------
// ����������� �������� ������� ��� 1:500 000
//-------------------------------------------------------------------------

int WINAPI _export frmCreateLinescale500000(HMAP hmap,HSITE hSit,LINESCALE *scale);


//-------------------------------------------------------------------------
// ����������� �������� ������� ��� 1 : 200 000
//-------------------------------------------------------------------------

int WINAPI _export frmCreateLinescale200000(HMAP hmap,HSITE hSit,LINESCALE *scale);

//-------------------------------------------------------------------------
// ����������� �������� ������� ��� 1 : 50 000
//-------------------------------------------------------------------------

int WINAPI _export frmCreateLinescale50000(HMAP hmap,HSITE hSit,LINESCALE *scale);

//-------------------------------------------------------------------------
// ����������� �������� ������� ��� 1 : 100 000
//-------------------------------------------------------------------------

int WINAPI _export frmCreateLinescale100000(HMAP hmap,HSITE hSit,LINESCALE *scale);

//-------------------------------------------------------------------------
// ����������� �������� ������� ��� 1 : 25 000
//-------------------------------------------------------------------------

int WINAPI _export frmCreateLinescale25000(HMAP hmap,HSITE hSit,LINESCALE *scale);

//-------------------------------------------------------------------------
// ����������� �������� ������� ��� 1 : 10 000
//-------------------------------------------------------------------------

int WINAPI _export frmCreateLinescale10000(HMAP hmap,HSITE hSit,LINESCALE *scale);

//--------------------------------------------------------------
//  ��������� ����� �����
// Delta  - ���������� �����(�)
// number=1 - �������������� ������ �����
// number=2 - �������������� ������ �����
//--------------------------------------------------------------

int WINAPI _export frmSetLineLenght(double *x1,double *y1,double *x2,double *y2,
                                    double delta,int number);

//-------------------------------------------------------------------
//         ������ "�" �� ����������
//-------------------------------------------------------------------

int WINAPI _export frmPreSscanf(char *string);

//-------------------------------------------------------------------
//         ������� "�"
//-------------------------------------------------------------------

int WINAPI _export frmPostSscanf(char *string);


//------------------------------------------------------------------------
// ������� ������� ������������� ���������
//------------------------------------------------------------------------

int WINAPI _export frmCreateGeolabels(HMAP Hmap,HSITE frmsit,long int code,
                   long int linecode,GEOFRAME geoframe,
                   HOBJ info,DOUBLEPOINT* framepoint,double dx,long int labelcode);

//------------------------------------------------------------------------
// ������� ������� ������������� ���������
// �� ��������������� ����� (�������� �� 1:500 000)
//------------------------------------------------------------------------

int WINAPI _export frmCreateGeolabels200t(HMAP Hmap,HSITE frmsit,long int code,
                   long int linecode,GEOFRAME geoframe,
                   HOBJ info,DOUBLEPOINT* framepoint,double dx,long int labelcode);

//------------------------------------------------------------------------
// ������� ������� ������������� ���������
// �� ��������������� ����� �������� 1:500 000
//------------------------------------------------------------------------

int WINAPI _export frmCreateGeolabels500tTopo(HMAP Hmap,HSITE frmsit,long int code,
                   long int linecode,GEOFRAME geoframe,
                   HOBJ info,DOUBLEPOINT* framepoint,double dx,long int labelcode);

//------------------------------------------------------------------------
// ������� ������� ������������� ���������
// �� ��������������� ����� �������� 1:1 000 000
//------------------------------------------------------------------------

int WINAPI _export frmCreateGeolabels1mTopo(HMAP Hmap,HSITE frmsit,long int code,
                   long int linecode,GEOFRAME geoframe,
                   HOBJ info,DOUBLEPOINT* framepoint,double dx,long int labelcode);
//------------------------------------------------------------------------
// ������� ������� ������������� ���������
//------------------------------------------------------------------------

int WINAPI _export frmCreateIncLabel(HMAP hmap,HSITE frmsit,
                   LISTREGISTER *sheetreg,DOUBLEPOINT* framepoint,long int code,
                   double dx);

//------------------------------------------------------------------------
// ������� ������� ������ � (���� labelcode != 0) �������
// ������� ������������� ��������� �����
//------------------------------------------------------------------------

int WINAPI _export frmCreateCorn(HMAP hmap,HSITE frmsit,double dx,long int code,
                   long int labelcode,DOUBLEPOINT *framepoint,double alfa);


//------------------------------------------------------------------------
// ������� ������ ������������ ����� (netCode)
// c ��������� (textCode,twoTitleCode),
// ������ (����������� �����.����� - ��� �������������)
// dx - ���������� � �� ����� ������� � ���������� �������
// oldframe - �������� (������������) �����
//------------------------------------------------------------------------

int WINAPI _export frmCreateNet(HMAP hmap,HSITE frmsit,double dx,double step,
                   long int netCode,long int textCode,long int twoTitleCode,
                   long int crossCode,DOUBLEPOINT *framepoint,HOBJ info,HOBJ oldframeinfo,
                   double alfa);

//-------------------------------------------------------------------
//         ������ ����� �����
//-------------------------------------------------------------------

int WINAPI _export frmSetFramePoint(DOUBLEPOINT *framepoint,HOBJ info);

//-------------------------------------------------------------------
//         ��������� �� ������
//
// message - ����� ���������
// target   0 - ������ � ����,
//          1 - ������ �� �����,
//          2 - � ���� � �� �����
// filename - ��� ����� ���������
// mode     0 - �������� ��������
//          1 - ����������� ��������
//
//-------------------------------------------------------------------

int WINAPI _export frmErrorMessage(char * message,int target = -1,char *filename = 0,int mode = 0);


int WINAPI _export GetPerpend(DOUBLEPOINT first,DOUBLEPOINT last,
                            DOUBLEPOINT middle,double distance,
                            DOUBLEPOINT *left,DOUBLEPOINT *right);




}
#endif

