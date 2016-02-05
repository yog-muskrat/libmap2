
#ifndef MAPCUTOB_H
#define MAPCUTOB_H

#ifndef MAPBITS_H
 #include "mapbits.h"
#endif

#ifndef MEASURE_H
 #include "measure.h"
#endif

#ifndef MAPINFO_H
 #include "mapinfo.h"
#endif

#ifndef MAPSELC_H
 #include "mapselc.h"
#endif

// ������������ ����� ����� ����������� �� ����� �������
#define MAXPOINTCROSS       100

// ����� ����� ����������� ��� ������������ ������� ������
#define MAXPOINT            1000

// �������� ��� ������� ���� float
#define PRECISION           -1

// ��������� ��� ����������� �������� �����
#define CONSTANTSCALE       100000.

// ��������� ��� �������� ���������� �����������
#define COUNTBITS           1024*64

#define DELTA_ANGLE M_PI/180.

enum {
       pcOFF    = 0,     // �� ����������
       pcLINE   = 1,     // ���������� ���� ���������� (��� ��������)
       pcSQUARE = 2      // ���������� ��� ����������� (��� ���������)
     };

enum {                  // ����� ����� ������� ������������
       pcBEFORE = 1,    // �� ����� �����������
       pcAFTER  = 2,    // ����� ����� �����������
       pcALL    = 3,    // � ��, � �����
       pcNO     = 4,    // �� ��, �� �����
     };

enum {
       pcINSIDE   = 1,  // ������
       pcOUTSIDE  = 2,  // �� ���������
       pcCUTSUB   = 3   // ��������� ������ �����������
     };

typedef struct POINTCROSS
{
  DOUBLEPOINT XY;    // ���������� ����� �����������
  double       H;    // ������ ����� �����������
  LONGPOINT Num;     // ����� ������ ������� �������������
                     // ������� ��������� ����� �����������
  LONGPOINT NumAd;   // ����� ������ ������� �������������
                     // ������� ��������� ����� �����������
  int Work;          // ������� ��������� �����
                     // OFF - �� ����������
                     // LINE  - ���������� ��� ��������
                     // SQUARE - ���������� ��� ���������
  int  Inside;       // ������� ������ �������
                     // enum INSIDE ��� PointCross
}
  POINTCROSS;


typedef struct POINTBEAK
{
  int Number;        // ����� ����� �������
  int Process;       // ������� ������� ����� � �������� ���������
}
  POINTBEAK;

class _DLLCLASS TObjectCutSubject;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++  TPointCross ++++++++++++++++++++++++
// ++++ ����� : ���������� ����� ����������� ���� ������ +++
//                  ��� �����'����� !!!
// ������ ��'��� - �� �������� ����� (����������� ���������)
// ������ ��'��� - ������� ����� (������������)
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TPointCross
{
  public:

  enum WORK
  {
    OFF    = pcOFF,     // �� ����������
    LINE   = pcLINE,    // ���������� ���� ���������� (��� ��������)
    SQUARE = pcSQUARE   // ���������� ��� ����������� (��� ���������)
  };

  enum FLAGINSIDE       // ����� ����� ������� ������������
  {
    BEFORE = pcBEFORE,  // �� ����� �����������
    AFTER  = pcAFTER,   // ����� ����� �����������
    ALL    = pcALL,     // � ��, � �����
    NO     = pcNO,      // �� ��, �� �����
  };

  // ������� ������������ ��������� ������� � ������������
  // ������������ �������
  enum PLACELINE
  {
    INSIDE  = pcINSIDE,    // ������
    OUTSIDE = pcOUTSIDE,   // �� ���������
    CUTSUB  = pcCUTSUB,    // ��������� ������ �����������
  };

  TPointCross();
  ~TPointCross();

  // info1 - 1 ������ (���������), �� �������� ����� ( �������� �����)
  // info2 - 2 ������ (������������), ������� �����
  // method - ����� ������� ��������:
  //          LOCAL_LINE - ��������,
  //          LOCAL_SQUARE - ���������
  // subject2 - ����� �������/���������� 2 ������� (�� ��������� = 0)
  // subject1 - ����� �������/���������� 1 ������� (�� ��������� = 0)
  // precision - ������ ��� ���������� ����� �����������
  TPointCross(TObjectInfo *info1, TObjectInfo *info2, int method,
              int subject2 = 0, int subject1 = 0, double precision = PRECISION);

  // data1 - ������ (���������), �� �������� ����� ( �������� �����)
  // data2 - ������ (������������), ������� �����
  // method - ����� ������� ��������:
  //          LOCAL_LINE - ��������,
  //          LOCAL_SQUARE - ���������
  // subject2 - ����� �������/���������� 2 ������� (�� ��������� = 0)
  // subject1 - ����� �������/���������� 1 ������� (�� ��������� = 0)
  // precision - ������ ��� ���������� ����� �����������
  // ������� �������� ��������� � ������ ������� �������
  TPointCross(TDataEdit *data1, TDataEdit *data2, int method,
              int subject2 = 0, int subject1 = 0, double precision = PRECISION);

  // ���������� ��� �������
  void CloseAll();

  // ��������� �������
  // method - ����� ������� ��������:
  //          LOCAL_LINE - ��������,
  //          LOCAL_SQUARE - ���������
  // subject2 - ����� �������/���������� 2 ������� (�� ��������� = 0)
  // subject1 - ����� �������/���������� 1 ������� (�� ��������� = 0)
  // precision - ������ ��� ���������� ����� �����������
  int LoadObjects(TObjectInfo* info1, TObjectInfo* info2, int method,
                  int subject2 = 0, int subject1 = 0,
                  double precision = PRECISION);
  int LoadObjects(TDataEdit *data1, TDataEdit *data2, int method,
                  int subject2 = 0, int subject1 = 0,
                  double precision = PRECISION);

  // ���������� ��� ������� � �������� ���������� �����
  int SetKindPrecision(TDataEdit *data,
                       double precision = PRECISION);

  // �������� ����� ����������� � �������
  int InsertPointCross();

  // ��� ������
  int Error() { return ErrorCode; }

  // ����� ��������� ����� �����������(�� ������� PointCross2)
  // �������� ��������� PointCross2
  // ��� ������ ���������� 0
  int GetNextPoint(POINTCROSS *point1, POINTCROSS *point2);

  // ����� ����� ����������� � ������� POINTCROSS
  int GetPointCross(DOUBLEPOINT *point, POINTCROSS *cross, int count);

  // ����� ����� ����������� � ������� POINTCROSS
  int GetPointCrossEx(POINTCROSS *crossin, POINTCROSS *cross, int count);

  // �������� �� ������������ ����� ������� ������� �� �������
  // data1 - ������ (���������), �� �������� ����� ( �������� �����)
  // data2 - ������ (������������), ������� �����
  // ������� �������� �.�. ��������� � ������ ������� �������
  // precision - ������ ��� ���������� ����� �����������
  // ��� ������ ��� ���������� ������������� �����
  // ���������� 0
  int IsCutObject(TDataEdit *data1, TDataEdit *data2,
                  double precision = -1);

  // ���� ������ �������
  // pointcross - � ������ ������� ����� ����������� ������
  //            = 1 � �������
  //            = 2 �� ������� ( �� ��������� )
  int _fastcall CollectorOneObject(TDataEdit *data, int subnum = 0,
                                   int pointcross = 2);

  // ������� �����
  int _fastcall DeleteBeak(TDataEdit *data);

  protected:

  // �������� ����������� �������� ��������
  int _fastcall ControlLocal(TDataEdit *data1, int method);


  // �������� ������ ��� ���������
  int LoadData();

  // ���������� ������� � ������ ������� �������
  int UnitedData();

  // ���������� ������� ��������� ������� � ������ ������� �������
  // dataout - ������� ��������� �������
  // infoin -  �������� ������
  // infoout - �������� ������
  int UnitedData(TDataEdit *dataout, TObjectInfo *infoin = 0,
                 TObjectInfo *infoout = 0);

  // ��������� ������ ����� �����������
  int SetAllPointCross();


  /*******************************************************************
  *            ���������� ������� POINTCROSS                         *
  *******************************************************************/

  // ������������� ������ POINTCROSS
  void _fastcall SortPointCross(POINTCROSS *mass, int count, TDataEdit *data);

  // ������������� ���������� � ������� POINTCROSS
  void _fastcall SortCoordinamesPointCross(POINTCROSS *mass, int num, TDataEdit *data);

  // ������������� ����� �� �������
  // cross - ������ ����� �����������
  // begin - ��������� ������ � ������� cross
  // count - ���������� ����� ��� ����������
  int _fastcall SortPoint(POINTCROSS *cross, int begin, int count,
                DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);


 /*******************************************************************
 *            ��������������� ���������                             *
 *******************************************************************/

  // ������� ����� � ����������� ������������ �� ������� POINTCROSS
  void _fastcall DeletePointCross(POINTCROSS *cross, POINTCROSS *cross2,
                                  int *count,
                                  TDataEdit *data);

  // ���������� ��������� POINTCROSS
  void _fastcall SetPointCross(POINTCROSS *pointcross, DOUBLEPOINT *xy,
                     int begnum1, int endnum1, double h = 0,
                     int begnum2 = 0, int endnum2 = 0);

  // ����������� ������� ����� �� �������
  void _fastcall AveragePoint(POINTCROSS *pointcross, DOUBLEPOINT *point,
                    int begin, int end);

  // ������� ������ �� ����������
  // dataout - ����
  // datain  - ������
  // subnum  - ����� ���������� � datain
  int _fastcall CreateDataObject(TDataEdit *dataout, TDataEdit *datain,
                       int subnum = 0);

  // ��������� �������
  // out, in - ����, ������
  // outsub, insub - ������ ��������/�����������
  // direction - �����������: 1 = ������ ����, 0 - ����� �����
  // begin, end - � ����� �� ����� ����� ���������
  int _fastcall MoveData(TDataEdit *out,  TDataEdit *in,
               int direction, int begin, int end,
               int outsub = 0, int insub = 0);

  // ����� ������� �� �������
  // dataout - ���� ��������� �����
  // datin -   ������ ����� �����
  // num - ������ � ������� ����� ����������� �������
  // subout - ����� ����������, ���� ��������� �����
  // ������� = 0 - ������
  //         > 0 - ����� �������� �������� � PointCross1+1
  //         < 0 - ������� ���������
  int _fastcall GetDataObject(TDataEdit *dataout, TDataEdit *datain,
                    POINTCROSS *cross, int num, int count,
                    int subout = 0);

  // �������� ����������� ������
  void _fastcall ChangeDirection(int in, int *out);


  /*******************************************************************
  *        ����������� ����� �����������                             *
  *******************************************************************/

  // ����������� ����� ����������� ��������
  int PointCrossObj();

  // ����������� ������� � ������� �������
  // xy1, xy2 - ���������� �������
  // beg1, end1 - ������ ����� ������� �������
  // data - ������� ������������ �������/����������
  int _fastcall CrossLengthData(DOUBLEPOINT xy1, DOUBLEPOINT xy2,
                      int beg1, int end1, TDataEdit *data,
                      int countin, int excin);

  // ��������� �� ���������� ���������� � ����������� �����
  // ������������ ����� ����������� �������
  // data1 - ��� ���������
  // data2 - ��� ���������
  // cross1 - ������ ������ ����� �����������
  // cross2 - ������ ������ ����� �����������
  // num - ������� ����� � cross1
  // count - ���������� ��������� � ��������� POINTCROSS
  // flag1 - ��� ����������� ���� Inside ����� �� ������ ��� cross1
  // flag2 - ��� ����������� ���� Inside ����� �� ������ ��� cross2
  //       = 0 - ����������� ��������
  //       = 1 - ����������� ��������
  // direct -  = 1 ����������� ���������� �������� ���������
  //           = 0 ����������� ���������� �������� �� ���������
  int _fastcall GetInsidePointCross(TDataEdit *data1, TDataEdit *data2,
                        POINTCROSS *cross1, POINTCROSS *cross2,
                        int flag1, int flag2,
                        int num, int count, int direct);

  // ������� ���������
  // dataout - ����
  // datain  - ������
  // subnum  - ����� ���������� � datain
  // all - = 1 - ��� �������� ��������� ��� ���������
  //       = 0 - � ��������� ���������

  int _fastcall DoSubject(TDataEdit *dataout, TDataEdit *datain, int subnum = 0, int all = 0);

  // ����������� ����������� ������������ �������, ���������� �
  // ������ �� �������� �����
  // data - ������� ������������ �������
  // dframe1 - �������� �������, �� �������� �����
  // subnum -  ����� ����������
  // ������� - 0 - ������,
  //           1 - ������/��������� ��������� ����������� �������
  //           2 - ������/��������� ������������ � ��������
  int _fastcall InsideDimensions(TDataEdit *data, DFRAME dframe1, int subnum);

  //  ��������� ������ ������ ��� ������� ����� �����������
  //  ��� ������ ���������� ����, ����� - ����� ������ ������
  int Realloc();

  // ���������������� ������� ����� �����������
  // cross1 - �������� ������
  // cross2 - ��������� ������
  void _fastcall CorrectPointCrossALLNO(POINTCROSS *cross,
                                        int count);

  // ��������� ����� ��� ����� ���������� ������  
  // cross1 - ����� ����������� ������� ������� (�������)
  // cross2 - ����� ����������� ������� �������
  void SetHeightPointCross(POINTCROSS *cross1 = 0, POINTCROSS *cross2 = 0,
                           TDataEdit *data1 = 0, TDataEdit *data2 = 0,
                           int count = 0);

  // ��������� ����� �� �������� ���������� �� �������� �����
  // x1, �1 - ������ �����
  // x2, �2 - ������ �����
  // delta - ����������
  // number - ����� ���������� ��� ���������� ����������
  void _fastcall SeekVirtualPointByDistance(double x1,double y1,
                                            double *x2,double *y2,
                                            double delta);

  // �������� ������� ����� ������� ������������ �������
  // (������ � ��������� �����)
  // delta - ���������e
  int _fastcall DragPoints(TDataEdit *data1, double delta = 2,
                           int subject = 0);

  // ������� �����
  int _fastcall DeleteLoop(TDataEdit *data);

  // �������� ������� ����� �����������, ���������� �����
  int _fastcall ChangePointCrossBeak(POINTCROSS *crossin,
                                     int count, int exc);

  // ������������� ���������� ������
  void InitPointCross();

  public:

  double Precision;             // ����������

  TObjectInfo *Info1;           // �������� �������
  TObjectInfo *Info2;

  int ErrorCode;                // ��� ������
  int InsideObject1;            // ��� ���������� ����� �����������
                                // ������ ��������� ������� ������� �� ������
  int InsideObject2;            // ��� ���������� ����� �����������
                                // ������ ��������� 2-�� ������� � ������
  int InsideObjectSub2;         // ��� ���������� ����� ����������� ������ ���������
                                // 2-�� ������� � ������ � ����������� c ������������
  int PlaceLine;                // ��� ���������� ����� ����������� ��� �
                                // �������� ������� � ������������,
                                // ����������� ����� - ������� ������������
                                // ��������� ������� � ������������
                                // ������������ �������
                                //  - ������ ��������� ������� � ������ = IN
                                //  - ������ ������ ����� � �������     = OUT

  int Subject1;                 // �������������� ����������
  int Subject2;
  int FlagDirectSubject1;       // ������� ��������� ����������� ����������
  int FlagDirectSubject2;       // � �����������                  
  int RealPlace;                // ������� �������� ���������
  int FlagDeleteEqualPoint;     // ������� �������� ���������� �����
  int Local;                    // ������� ����������� ������� �������
  int Kind;                     // ��� �������
  int Direct;                   // ������� ��������� ����������� ����������
  int Direction;                // ������� ���������� ����������� ����������
                                // ��������� ��������
  int CountPointCross;          // ������ ������ ��� PointCross

  int All;                      // �������� ������� ���� �� ����� ����� �����
  int No;

  POINTBEAK PointBeak1[MAXPOINT];// ����� - �������
  POINTBEAK PointBeak2[MAXPOINT];

  int IsFlagBeak;               // ���� ������ � �������� PointBeak
                                // 0 - �� ������ �� �������� ��������
                                // 1 - �������������� ������� �������������� �������

  int Full;                     // ��� ��������� �������� ������� ���������
                                // ����������� �������-������

  int FlagInsideObjects;        // ���� �������� �� ���������� 2-�� ������� � ������
                                // 0 - �� ���������
                                // 1 - ���������                   

  TDataEdit Data1;              // ������� �������������� ��������
  TDataEdit Data2;

  POINTCROSS *PointCross1;      // ��������������� ���������
  POINTCROSS *PointCross2;
  int NumCross;                 // ����� ��������� � ��������
                                // PointCross1, PointCross2

  // �� TObjectCutSubject
  TDataEdit *ObjectOut;         // �������������� ������ ��������
                                // ��������� �����������
  TDataEdit DataOut;            // ������� ��������� �������

  // �� TObjectCut
  TBitSet64K SubObject;         // ������ �����������,
                                // ���������� � ���� ����������
  int    SubNum;                // ����� ����� �����������
  int    LoadSub;               // ���� ������ � ������� �����������

  TDataEdit DataOutSub;         // ������� ��������� �������
};

typedef  TPointCross TPOINTCROSSDATA;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++ ������� ���������� ����� ����������� ���� ������ +++
//                  ��� �����'����� !!!
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ��������� ������� TObjectInfo1, TObjectInfo2
// precision - ������ ��� ���������� ����� �����������
int _fastcall pcLoadInfoObjects(TPOINTCROSSDATA *pc,
                                TObjectInfo *info1,
                                TObjectInfo *info2, int method,
                                int subject2, int subject1, double *precision);

// ��������� ������� DATAEDIT 1, DATAEDIT 2
// precision - ������ ��� ���������� ����� �����������
int _fastcall pcLoadDataObjects(TPOINTCROSSDATA *pc,
                            TDataEdit *data1, TDataEdit *data2,
                            int method, int subject2, int subject1,
                            double *precision);

// ���������� ��� ������� � �������� ���������� �����
int _fastcall pcSetKindPrecision(TPOINTCROSSDATA *pc,
                                 TDataEdit *data, double *precision);

// ���������� ������� � ������ ������� �������
int _fastcall pcUnitedData(TPOINTCROSSDATA *pc);

// ���������� ������� ��������� ������� � ������ ������� �������
// dataout - ������� ��������� �������
// infoin -  �������� ������
// infoout - �������� ������
int _fastcall pcUnitedDataOut(TPOINTCROSSDATA *pc,
                              TDataEdit *dataout,
                              TObjectInfo *infoin,
                              TObjectInfo *infoout);

//  ��������� ������ ������ ��� ������� ����� �����������
//  ��� ������ ���������� ����, ����� - ����� ������ ������
int _fastcall pcRealloc(TPOINTCROSSDATA *pc);

// �������� ����������� �������� ��������
int _fastcall pcControlLocal(TPOINTCROSSDATA *pc,
                             TDataEdit *data1, int method);

// ������������� ������ POINTCROSS �� ����������� ������� �����
// � ������� � �� �����������
void _fastcall pcSortPointCross(POINTCROSS *cross, int count,
                                TDataEdit *data);

// ������������� ���������� � ������� POINTCROSS
void _fastcall pcSortCoordinamesPointCross
               (POINTCROSS *cross, int num, TDataEdit *data);

// ������������� �����
// cross - ������ ����� �����������
// begin - ��������� ������ � ������� cross
// count - ���������� ����� ��� ����������
int _fastcall pcSortPoint(POINTCROSS *cross, int begin, int count,
                          DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);

// ����� ����� ����������� � ������� POINTCROSS
int _fastcall pcGetPointCross(DOUBLEPOINT *point,
                              POINTCROSS *cross, int count);

int _fastcall pcGetPointCrossEx(POINTCROSS *crossin,
                               POINTCROSS *cross, int count);

// ������� ����� � ����������� ������������ �� ������� POINTCROSS
void _fastcall pcDeletePointCross(TPOINTCROSSDATA *pc,
                                  POINTCROSS *cross,
                                  POINTCROSS *cross2,
                                  int *count,
                                  TDataEdit *data);

// ���������� ��������� POINTCROSS
void _fastcall pcSetPointCross(POINTCROSS *pointcross,
                               DOUBLEPOINT *xy,
                               int begnum1, int endnum1,
                               double h,int begnum2, int endnum2);

// ����������� ������� ����� �� �������
void _fastcall pcAveragePoint(POINTCROSS *pointcross, DOUBLEPOINT *point,
                              int begin, int end);

// ������� ������ �� ����������
// dataout - ����
// datain  - ������
// subnum  - ����� ���������� � datain
int _fastcall pcCreateDataObject(TDataEdit *dataout, TDataEdit *datain,
                                  int subnum);


// ��������� �������
// out, in - ����, ������
// outsub, insub - ������ ��������/�����������
// direction - �����������: 1 = ������ ����, 0 - ����� �����
// begin, end - � ����� �� ����� ����� ���������
int _fastcall pcMoveData(TDataEdit *out, TDataEdit *in,
                         int direction, int begin, int end,
                         int outsub, int insub);

// ����� ������� �� �������
// dataout - ���� ��������� �����
// datin -   ������ ����� �����
// num - ������ � ������� ����� ����������� �������
// subout - ����� ����������, ���� ��������� �����
// ������� = 0 - ������
//         > 0 - ����� �������� �������� � PointCross1+1
//         < 0 - ������� ���������
int _fastcall pcGetDataObject(TPOINTCROSSDATA *pc,
                              TDataEdit *dataout, TDataEdit *datain,
                              POINTCROSS *cross, int num, int count,
                              int subout);

// �������� ����������� ������
void _fastcall pcChangeDirection(int in, int *out);

// ����������� ����� ����������� ��������
int _fastcall pcPointCrossObj(TPOINTCROSSDATA *pc);

// ���� ������ �������
// data - ���� ������ �������
// subnum - ���� ������ ������� (� ����� ���������)
// pointcross - � ������ ������� ����� ����������� ������
//            = 1 � �������
//            = 2 �� ������� ( �� ��������� )
int _fastcall pcCollectorOneObject(TPOINTCROSSDATA *pc,
                                   TDataEdit *data, int subnum,
                                   int pointcross);

// ����������� ����������� ������������ �������, ���������� �
// ������ �� �������� �����
// data - ������� ������������ �������
// dframe1 - �������� �������, �� �������� �����
// subnum -  ����� ����������
// ������� - 0 - ������,
//           1 - ������/��������� ��������� ����������� �������
//           2 - ������/��������� ������������ � ��������
int _fastcall pcInsideDimensions(TDataEdit *data,
                                 DFRAME *dframe1, int subnum);

// ������� ���������
// dataout - ����
// datain  - ������
// subnum  - ����� ���������� � datain
// all - = 1 - ��� �������� ��������� ��� ���������
//       = 0 - � ��������� ���������
int _fastcall pcDoSubject(TPOINTCROSSDATA *pc,
                          TDataEdit *dataout, TDataEdit *datain,
                          int subnum, int all);

// �������� ����� ����������� � �������
int _fastcall pcInsertPointCross(TPOINTCROSSDATA *pc);

// �������� �� ������������ ����� ������� ������� �� �������
// data1 - ������ (���������), �� �������� ����� ( �������� �����)
// data2 - ������ (������������), ������� �����
// ������� �������� �.�. ��������� � ������ ������� �������
// precision - ������ ��� ���������� ����� �����������
// ��� ������ ��� ���������� ������������� �����
// ���������� 0
int _fastcall pcIsCutObject(TPOINTCROSSDATA *pc,
                            TDataEdit *data1, TDataEdit *data2,
                            double *precision);

// ��������� ����� ��� ����� ���������� ������
// cross1 - ����� ����������� ������� ������� (�������)
// cross2 - ����� ����������� ������� �������
void _fastcall pcSetHeightPointCross(POINTCROSS *cross1, POINTCROSS *cross2,
                                     TDataEdit *data1, TDataEdit *data2,
                                     int count);

// ���������������� ������� ����� �����������
void _fastcall pcCorrectPointCrossALLNO(TPOINTCROSSDATA *pc,
                                        POINTCROSS *cross,
                                        int count);

// ���������������� ������� ����� �����������
//void _fastcall pcCorrectPointCrossALL(TPOINTCROSSDATA *pc,
//                                      POINTCROSS *cross1, POINTCROSS *cross2,
//                                      int *count, int exc);

// ��������� �� ���������� ���������� � ����������� �����
// ������������ ����� ����������� �������
// data1 - ��� ���������
// data2 - ��� ���������
// cross1 - ������ ������ ����� �����������
// cross2 - ������ ������ ����� �����������
// num - ������� ����� � cross1
// count - ���������� ��������� � ��������� POINTCROSS
// flag1 - ��� ����������� ���� Inside ����� �� ������ ��� cross1
// flag2 - ��� ����������� ���� Inside ����� �� ������ ��� cross2
//       = 0 - ����������� ��������
//       = 1 - ����������� ��������
// direct -  = 1 ����������� ���������� �������� ���������
//           = 0 ����������� ���������� �������� �� ���������
int _fastcall pcGetInsidePointCross(TPOINTCROSSDATA *pc,
                                    TDataEdit *data1, TDataEdit *data2,
                                    POINTCROSS *cross1, POINTCROSS *cross2,
                                    int flag1, int flag2,
                                    int num, int count, int direct);

// ��������� ����� �� �������� ���������� �� �������� �����
// �� ��������� �����
// x1, �1 - ��������� �����
// x2, �2 - �������� �����
// delta - ����������
// ��������� � �������� �����
void _fastcall pcSeekVirtualPointByDistance(double x1,double y1,
                                            double *x2,double *y2,
                                            double delta);

// �������� ������� ����� ������� ������������ �������
// (������ � ��������� �����)
// delta - ���������e
int _fastcall pcDragPoints(TDataEdit *data1, double delta, int subject);


// ���������� ���������� ������������� ����� � ������� ����� �����������
// count - ���������� ����� � �������
// ���� ����� ��� ���������� 1
int _fastcall pcGetFreePoint(TPOINTCROSSDATA *pc,
                             POINTCROSS *prev, POINTCROSS *next,
                             int count, int exclusive,
                             int nprev, int nnext);

// ���������� ����� ��� �������� �� ����������
// count - ���������� ����� � �������
// ���� ����� ��� ���������� 0
int _fastcall pcGetInsidePoint(POINTCROSS *prev, POINTCROSS *next,
                               TDataEdit *data, int count,
                               DOUBLEPOINT *point,
                               int nprev, int nnext);

// ������� �����
int _fastcall pcDeleteBeak(TPOINTCROSSDATA *pc,TDataEdit *data);

// �������� ������� ����� �����������, ���������� �����
int _fastcall pcChangePointCrossBeak(TPOINTCROSSDATA *pc,
                                     POINTCROSS *crossin,
                                     int count, int exc);

                                     
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++ ������� : ����������� ��'���� � �����'����  ++++++++++
//      ( �� ������� �������� ������� ���������� )
// ������ ��'��� - �� �������� ����� (����������� ���������)
// ������ ��'��� - ������� ����� (������������)
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ��������� �������
int _fastcall csLoadDataObjects(TPOINTCROSSDATA *pc,
                                TDataEdit *data1, TDataEdit *data2,
                                int method, int subject,
                                double *precision);

// ���������� ���� ������ ������� � ������� PointCross1, PointCross2
int _fastcall csSetInside(TPOINTCROSSDATA *pc);

// ����� ��������� ������ (������ ��� ���������)
TDataEdit *_fastcall csGetNextObject(TPOINTCROSSDATA *pc);

// ���� ������ �������
int _fastcall csCollectorOneObject(TPOINTCROSSDATA *pc, TDataEdit *data, int subnum);

// ���������������� ������� ����� �����������
// cross1 - ��������� ������
// cross2 - ��������� ������
int _fastcall csCorrectPointCross(TPOINTCROSSDATA *pc,
                                  POINTCROSS *cross1, POINTCROSS *cross2,
                                  TDataEdit *data1, TDataEdit *data2,
                                  int count);

// ���������� ��������� ����� ������������ ��������
// ���������� BEFORE - ���� ��� ����� ����� � �������
//            ALL    - ������ ���� ����� ����� � �������
int _fastcall csGetPlacePoint(DOUBLEPOINT *point1, DOUBLEPOINT *point2,
                              TDataEdit *data1,TDataEdit *data2);



// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++ ����� : ����������� ��'���� � �����'����  ++++++++++
//      ( �� ������� �������� ������� ���������� )
// ������ ��'��� - �� �������� ����� (����������� ���������)
// ������ ��'��� - ������� ����� (������������)
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TObjectCutSubject : public TPointCross
{
  public:

  //*********************************************************
  //  �������� �������
  //  TObjectCutSubject - �����������,
  //  LoadObjects - ��������� ������,
  //  GetNextObject - ����� ��������� ������
  //*********************************************************

  TObjectCutSubject();

  // info1 - ������� ������a
  // info2 - ������� �������, ������ ����� ���������
  // subject - ����� ���������� 2 ������� (�� ��������� = 0)
  // ������� �������� ������ ���� ��������� � ������ ������� �������
  TObjectCutSubject(TObjectInfo *info1, TObjectInfo *info2,
                    int method = LOCAL_SQUARE,
                    int subject = 0,
                    double precision = PRECISION);

  // data1 - ������� ������a
  // data2 - ������� �������, ������ ����� ���������
  // subject - ����� ���������� 2 ������� (�� ��������� = 0)
  // ������� �������� ����� ��������� � ������ ������� �������
  TObjectCutSubject(TDataEdit *data1, TDataEdit *data2,
                    int method = LOCAL_SQUARE,
                    int subject = 0,
                    double precision = PRECISION);

  // ��������� �������
  int LoadObjects(TObjectInfo* info1, TObjectInfo* info2,
                  int method = LOCAL_SQUARE,
                  int subject = 0, double precision = PRECISION);

  // ��������� �������
  int LoadObjects(TDataEdit *data1, TDataEdit *data2,
                  int method = LOCAL_SQUARE,
                  int subject = 0, double precision = PRECISION);

  // ����� ��������� ������
  // ��� ������ ���������� 0
  TDataEdit *GetNextObject();


  //*********************************************************
  //  ��������������� ������� ��� ������������� �����������
  //*********************************************************

  // ���� ������ �������
  int CollectorOneObject(TDataEdit *data, int subnum = 0);

  protected:

  // ���������� ���� ������ ������� � ������� PointCross1, PointCross2
  int SetInside();

  // ���������������� ������� ����� �����������
  // cross1 - �������� ������
  // cross2 - ��������� ������
  int _fastcall CorrectPointCross(POINTCROSS *cross1,
                                  POINTCROSS *cross2,
                                  TDataEdit *data1,
                                  TDataEdit *data2,
                                  int count);

  // ���������� ��������� ����� ������������ ��������
  // ���������� BEFORE - ���� ��� ����� ����� � �������
  //            ALL    - ������ ���� ����� ����� � �������
  int _fastcall GetPlacePoint(DOUBLEPOINT *point1,
                              DOUBLEPOINT *point2,
                              TDataEdit *data1,
                              TDataEdit *data2);
};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++  TObjectCut  ++++++++++++++++++++++++
// +++++++++++++ ����� : ����������� ��'�����  +++++++++++++
// ������ ��'��� - ������ (��� �����������, ���������),
//                 �� �������� ����� ( �������� �����)
// ������ ��'��� - ������ (c ������������, ������������),
//                 ������� �����
// method - ����� ������� ��������:
//          LOCAL_LINE - ��������,
//          LOCAL_SQUARE - ���������
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TObjectCut : public TPointCross
{

 public:

  //*********************************************************
  //  �������� �������
  //  TObjectCut - �����������,
  //  LoadObjects - ��������� ������,
  //  GetNextObject - ����� ��������� ������
  //*********************************************************

  TObjectCut();
  ~TObjectCut();

  // ����������� ������ TObjectCut
  // info1 - ������ (��� �����������, ���������),
  //         �� �������� ����� ( �������� �����)
  // info2 - ������ (c ������������, ������������), ������� �����
  // method - ����� ������� ��������:
  //          LOCAL_LINE - ��������,
  //          LOCAL_SQUARE - ���������
  // full - ��� ��������� �������� ������� ���������
  //        ����������� �������-������ (���� ��� ����)
  TObjectCut(TObjectInfo* info1, TObjectInfo* info2, int method,
             double precision = PRECISION, int full = 0);

  // ����������� ������ TObjectCut
  // data1 - ������ (��� �����������, ���������),
  //         �� �������� ����� ( �������� �����)
  // data2 - ������ (c ������������, ������������), ������� �����
  // method - ����� ������� ��������:
  //          LOCAL_LINE - ��������,
  //          LOCAL_SQUARE - ���������
  // ������� �������� ��������� � ������ ������� �������
  // full - ��� ��������� �������� ������� ���������
  //        ����������� �������-������ (���� ��� ����)
  TObjectCut(TDataEdit *data1, TDataEdit *data2, int method,
             double precision = PRECISION, int full = 0);

  // ��������� �������
  // precision - ������ ��� ���������� ����� �����������
  // full - ��� ��������� �������� ������� ���������
  //        ����������� �������-������ (���� ��� ����)
  int LoadObjects(TObjectInfo* info1, TObjectInfo* info2, int method,
                  double precision = PRECISION, int full = 0);
  int LoadObjects(TDataEdit *data1, TDataEdit *data2, int method,
                  double precision = PRECISION, int full = 0);
  int LoadObjects(TDataEdit *data1, TDataEdit *data2, int method, int subject,
                  double precision = PRECISION, int full = 0);

  // ����� ��������� ������
  // ���� � ��������� ������� ���� ���������� -
  // ���������� ������ � ������������,
  // ����� ����� ��������� ������� ��� ��������������� ������
  // � ��������� ��� �� ���������
  // ��� ������ ���������� 0
  TDataEdit *GetNextObject();


  //*********************************************************
  //  ��������������� ������� ��� ������������� �����������
  //*********************************************************

  // ���������� ��� �������
  void CloseAll();

  // ������������� ���������� ������
  void InitObjectCut();

  // ���������� ���� ������ ������� � ������� PointCross1, PointCross2
  int SetInside();

  // ����������� ����������� ������������ �������, ���������� �
  // ������ �� �������� �����
  // data1 - ������� �������, �� �������� �����
  // data2 - ������� ������������ �������
  int InsideSubObject(TDataEdit *data1, TDataEdit *data2);

  // ����� ��������� ������ ��� ������ � ������������
  // num  - ����� ���������� � datain
  int GetNextObjectSub(int num, int loadsub = 0);

  // �������� � �������� ���������� ���������� ��� �������� ��������
  int AppendLineSubject();

  // ��������� ����������� ��������� �������(�� �������� �����),
  // � ���������� ���������� �������(������� �����)
  // data1 - �� �������� �����
  // data2 - ������� �����
  // subject - ��������� �������, ������� �����
  int InsideDimentionsSubject(TDataEdit *data1, TDataEdit *data2,
                              int subject);

  public:

  TObjectCutSubject * Subcut;   // ����� ������ � ������������ TObjectCutSubject
};

// +++++++++++ ������� : ����������� ��'�����  +++++++++++++
// ������ ��'��� - ������ (��� �����������, ���������),
//                 �� �������� ����� ( �������� �����)
// ������ ��'��� - ������ (c ������������, ������������),
//                 ������� �����
// method - ����� ������� ��������:
//          LOCAL_LINE - ��������,
//          LOCAL_SQUARE - ���������
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ��������� �������
int _fastcall coLoadInfoObjects(TPOINTCROSSDATA *pc,
                                TObjectInfo *info1, TObjectInfo *info2,
                                int method, double *precision, int full);

int _fastcall coLoadDataObjects(TPOINTCROSSDATA *pc,
                                TDataEdit *data1, TDataEdit *data2,
                                int method, double *precision, int full);

int _fastcall coLoadSubjectObjects(TPOINTCROSSDATA *pc,
                                   TDataEdit *data1, TDataEdit *data2,
                                   int method, int subject,
                                   double *precision, int full);

// ���������� ���� ������ ������� � ������� PointCross1, PointCross2
int _fastcall coSetInside(TPOINTCROSSDATA *pc);

// ����������� ����������� ������������ �������, ���������� �
// ������ �� �������� �����
// data1 - ������� �������, �� �������� �����
// data2 - ������� ������������ �������
int _fastcall coInsideSubObject(TPOINTCROSSDATA *pc,
                                TDataEdit *data1, TDataEdit *data2);

// ����� ��������� ������
// ���� � ��������� ������� ���� ���������� -
// ���������� ������ � ������������,
// ����� ����� ��������� ������� ��� ��������������� ������
// � ��������� ��� �� ���������
TDataEdit *_fastcall coGetNextObject(TObjectCut * pc);

// ��������� ����������� ��������� �������(�� �������� �����),
// � ���������� ���������� �������(������� �����)
// data1 - �� �������� �����
// data2 - ������� �����
// subject - ��������� �������, ������� �����
int _fastcall coInsideDimentionsSubject(TDataEdit *data1,
                                        TDataEdit *data2,
                                        int subject);

// �������� � �������� ���������� ���������� ��� �������� ��������
int _fastcall coAppendLineSubject(TObjectCut *pc);

// ����� ��������� ������ ��� ������ � ������������
// dataout - ����
// datain  - ������
// subnum  - ����� ���������� � datain
int _fastcall coGetNextObjectSub(TObjectCut * pc, int num, int loadsub);


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++ ����� : ��'�������� ��'�����                    ++++
// ++++ ������� � ������ ���� ������ ������� �������!   ++++
// ���� �� ����� ����� ������� ������,
// �� ��������� ��� ���, �������������� ������� �������
// ���� �� ����� �� ������� ������ (��� �����).
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TObjectUnion : public TObjectCut

{

  public:

  //*********************************************************
  //  �������� �������
  //  TObjectUnion - �����������,
  //  LoadObjects - ��������� ������,
  //  GetObject - ����� ������
  //*********************************************************

  TObjectUnion();
  ~TObjectUnion();

  // data1 -  1 ������
  // data2 -  2 ������
  // method - ����� ������ ��������:
  //          LOCAL_LINE - ��������,
  //          LOCAL_SQUARE - ���������
  // limit - ������ ������
  // precision - ������ ��� ���������� ����� �����������
  // ������� �������� ��������� � ������ ������� �������
  TObjectUnion(TDataEdit *data1, TDataEdit *data2, int method,
               double limit = PRECISION, double precision = PRECISION);

  // ��������� �������
  // method - ����� ������ ��������:
  //          LOCAL_LINE - ��������,
  //          LOCAL_SQUARE - ���������
  // limit - ������ ������
  // precision - ������ ��� ���������� ����� �����������
  int LoadObjects(TDataEdit *data1, TDataEdit *data2, int method,
                  double limit = PRECISION, double precision = PRECISION);

  // ����� ���������� ������
  TDataEdit *GetObject();

  protected:

  // �������� ������ ��� ���������
  int LoadData();

  // ���� ������ �������
  int _fastcall CollectorOneObjectLine(TDataEdit *data);

  // ���������� ���� ������ ������� � ������� PointCross1, PointCross2
  int SetInside();

  // ������� ��������� ���������� �������
  int GetSubjectSquare();

  // ������� �������� ������
  TDataEdit *GetObjectLine();

  // ������� ��������� ��������� �������
  int _fastcall GetSubjectLine(TDataEdit *dataout, TObjectUnion *objectunion);

  // ������� ��������� ���������
  TDataEdit *GetObjectSquare();

  // ������� ����������� ����������� ������� datain
  // � ����������� ��������������� �������
  int _fastcall GetSubjectSubjectSquare(TDataEdit *data1,
                                        TDataEdit *data2);

  // ������� ����������� ����������� � ��������
  // datain - ������ (Data1 ��� Data2)
  // bitin - ���� ����������� ��������������� �������
  int _fastcall GetSubjectObjectSquare(TDataEdit *datain,
                                       TBitSet64K *bitin);

  // ��������� ���� ������������ ����������� ���������� �
  // ����������� �������� �������� ������
  int SetBitsSubjects();

  // �������� ������ ��� Result
  int AllocateResult();

  // ���������������� ������� ����� �����������
  // cross1 - �������� ������
  // cross2 - ��������� ������
  void _fastcall CorrectPointCross(POINTCROSS *cross1,
                                   POINTCROSS *cross2,
                                   TDataEdit *data1,
                                   TDataEdit *data2,
                                   int count, int direct);

  // ���������� ��������� ����� ������������ ��������
  // ���������� BEFORE - ���� ��� ����� ����� � �������
  //            ALL    - ������ ���� ����� ����� � �������
  int _fastcall GetPlacePoint(DOUBLEPOINT *point1, DOUBLEPOINT *point2,
                              TDataEdit *data1, TDataEdit *data2);

  // �������� ������� �������� �� Limit
  int AdjustPoint(TDataEdit *data1, TDataEdit *data2);

 // ���������, ����� �� ���������� �����
 int CheckAdjustPoint(TDataEdit *data,DOUBLEPOINT * xy1,DOUBLEPOINT * xy2);

 int CheckPointCross(double x,double y);

 // ���������� Limit �� ������������ ����������
 int DefineLimit(TDataEdit *data1, TDataEdit *data2);

 // ������� ����� ��������� ������� � �������
 // ���������� ������� ����������� ������ �������
 //  = 1 - ������ ����� ������
 //  = 2 - ������ ����� ������ ������� � ��������� ������ �������
 //  = 3 - ��������� ����� ������ ������� � ������ ������ �������
 //  = 4 - ��������� ����� ������
 int IsObjectLineLimit(TDataEdit *data1,TDataEdit *data2);

 // ������ ����������� ��������� ��������
// TDataEdit *PovtorUnionSquareObjects(int get = 0);

  protected:

  // ���������� ���������� ����� ��������� 
  double Limit;
  int    Vector;

  // ������� ��������� ����������
  TDataEdit DataOutSub;

  // ������ �������� ��������/�����������  
  TBitSet64K SubObject1;
  TBitSet64K SubObject2;

  // ������� ����������� ��������
  int FlagCross;

  // ���� ������ ����� ���������
  int AdjustFlag;

  // ���� ������� ������, ���� ������ ��� �� ����������,
  int PovtorUnion;

  // ����� �����������
  int SubNum1;
  int SubNum2;

  // ������ ��� ���������� ����������� ����������� ���������� �
  // ����������� �������� �������� ������
  // ������������� �������� - ���������� 1 �������
  // ������������� �������� - ���������� 2 �������
  int *Result;
  int CountResult;

  // �������������� ������� ��� ����������
  // ������ ������� ������
  TDataEdit *ObjectOut;

  TDataEdit *DataOld1;
  TDataEdit *DataOld2;

};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++            TSquareUnion (������)                ++++
// ++++ ����������� ���������������� ��������� �������� ++++
// ++++ ������� ������ ���� � ������ ������� �������!   ++++
//    � ������� �� TObjectUnion ������ ���������� �������
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
// ��������� ��� �������� ���������� �� ����� �� ��������� �������
//---------------------------------------------------------------------------
typedef struct SQUAREPOINT
{
  double X, Y;                // ���������� �����
  double Distance;            // ��������� ���������� �� ��������� ������� (�� ������ ��� �� �����)
  long int  PointNum;         // ����� ��������� ����� �� ������ �������   
  short int IsDistanceToLine; // ���������� �� ����� ��� �� ������
  short int IsCheckIntersect; // ��������� �� ����������� � �������� ������ �������
}
  SQUAREPOINT;
//---------------------------------------------------------------------------
// ��������� ��� �������� �����, �������� � ������
//---------------------------------------------------------------------------
typedef struct PASSPOINT
{
  int Num;                // ����� ����� � ������� ����� ������� ��� ������� �������
  int IsPointFromObject1; // ������� �������������� ����� � ������� �������
}
  PASSPOINT;

class _DLLCLASS TSquareUnion
{

  public:

  TSquareUnion();
  ~TSquareUnion();

// ����������� ���� ��������� �������� �� �������
// info1     - ������ ������
// info2     - ������ ������
// info      - ���������
// precision - ������ �����������
// isalwaysunion - ���� �������������� ������ (1 - ����� ������)
// ��� ������ ���������� 0
long int Union(HOBJ info1, HOBJ info2, HOBJ info, double precision,
               long int isalwaysunion);                 

  protected:

// ���������� �������� ���������� ����� ����� �������
double GetDistanceSquare(double x1, double y1, double x2, double y2);

// ���������� ����� ����� �� ��������� ������� (��������� �� 0)
int GetNum(int Num, int Count);

// ���������� ����� ����� �� ��������� ������� (��������� �� 1)
int GetNum1(int Num, int Count);

// ���������� �������� ���������� �� ����� x,y �� ����� x1,y1 � �� ������� x1,y1 - x2,y2
int GetPieceDistance(double x1, double y1, double x2, double y2, 
                     double x, double y, double *Distance);

// ��������� �������� ����� (x,y) �� ������ (x1,y1 - x2,y2)
void ProjectionPointToLine(double x1, double y1, double x2, double y2, 
                           double x, double y, double *xout, double *yout);

// ���������� ���������� �� ������� �������
long int AddSubjectFromObject(HOBJ toobj, HOBJ fromobj, int fromsubjnum);

// ��������� ������������ �� 2 �������
bool IsSegmentIntersect(double x1, double y1, double x2, double y2,
                        double x3, double y3, double x4, double y4);

// ��������� ������ ��������� ����� (������ ������� ������� �����)
int SetPoints(SQUAREPOINT *points, int *pointcount, HOBJ obj, int subjectnum);

// ��������� ����� �� ����������� � �������� ������� �������
bool IsIntersectObj1(SQUAREPOINT *points1, int count1, int point1,
                     SQUAREPOINT *points2, int point2, bool isdistancetoline);

// ��������� ����� �� ����������� � ����������� ������ ������� �������
// (��� ���������� ��������)
bool IsIntersectLine1(SQUAREPOINT *points1, int count1, int point1,
                      SQUAREPOINT *points2, int point2, bool isdistancetoline);  

// ��������� ���������� ����� ������ ������ ������� ������� �
// ��������� ������ ��� ����� ������� ������� � ���������� ��������� �����
void CalcDistance(SQUAREPOINT *points1, int count1, 
                  SQUAREPOINT *points2, int count2);                             

// ��������� ���������� ����� ������ ������ ������������ ������� ������� �
// ��������� ������ ��� ����� ������������ ������� �������
void CalcDistanceToLine(SQUAREPOINT *points1, int count1, 
                        SQUAREPOINT *points2, int count2);

// ���� ����� ��������� �����
void FindBestConnectInObj(SQUAREPOINT *points, int count, double mindist,
                          double *bestdist, int *bestnum);                       

// ���ޣ� ���������� �� ����� point1 � �ޣ��� ����������� �� ����� ��������
void CalcDistAllowIntersect(SQUAREPOINT *points1, int count1, int point1,
                            SQUAREPOINT *points2, int count2);                   

// ��������� ����� �� ����������� � � ������ ����������� �������� ţ
bool IsConnectIntersect(SQUAREPOINT *points1, int count1, int point,
                        SQUAREPOINT *points2, int count2);                       

// ���� ����� ��������� ����� �� �������������� �� ����� ��������
void FindBestConnect(SQUAREPOINT *points1, int count1,
                     SQUAREPOINT *points2, int count2, double MinDist,
                     bool *ispointfromobj1, int *point, double *dist);           

// ���� ���� ����� �������� ������
void FindConnects(SQUAREPOINT *points1, int count1, SQUAREPOINT *points2, int count2,
                  int *point1, bool *ispoint1fromobj1, int *point2, bool *ispoint2fromobj1,
                  double *dist1, double *dist2);                                 

// ��������� ����� �� ������� �������
void AddContour(SQUAREPOINT *points, int count, HOBJ obj, 
                int subject, int point1, int point2, bool isforwarddir);

// ��������� ����� �� �����, ��������� � ����� point1
void AddToLine(HOBJ obj, int subject, SQUAREPOINT *points1, 
               int point1, SQUAREPOINT *points2);

// ��������� ���� �� ������������ ������ � ������ ����� ��� ����� ����
// � ������ �������
bool NeedAddContour(bool isforwarddir, double x1, double y1, double x2, double y2,
                   double x3, double y3, double x4, double y4);

// ���������� ���������� ����� (������ x � y)
void GetPoint(SQUAREPOINT *points1, SQUAREPOINT *points2,
              int num, bool ispointinobj1, DOUBLEPOINT *point);

// ���������� ��������� ����� p ������������ ���� p1->p2
bool IsPointLeft(DOUBLEPOINT *p, DOUBLEPOINT *p1, DOUBLEPOINT *p2);

// ��������� ������ ������� ������� � ������������ ���
void CheckAndAddContour(SQUAREPOINT *points1, SQUAREPOINT *points2, int count2,
                        int point1, int point2,
                        bool ispoint1inobj1, bool ispoint2inobj1,
                        bool isforwarddir1, bool isforwarddir2, bool isobj1left,
                        int Point1, int Point2, HOBJ obj, int subject);

// ��������� ����� � ������Σ���� ������
void AddPoints(SQUAREPOINT *points1, int count1, SQUAREPOINT *points2, int count2,
               HOBJ obj, int subject, int point1, int point2,
               bool ispoint1inobj1, bool ispoint2inobj1,
               bool isforwarddir2, bool isforwarddir1, bool isobj1left, int *addcount2);

// ��������� ����� �� ���������� ���������
void AddPointsInSubject(SQUAREPOINT *points1, int count1,
                        SQUAREPOINT *points2, int count2,
                        HOBJ obj, int point1, int point2,
                        bool ispoint1inobj1, bool ispoint2inobj1);   

// ���������� ������� ������Σ����� �������
double GetConnectSquare(SQUAREPOINT *points1, int count1,            
                        SQUAREPOINT *points2, int count2,
                        HOBJ obj, int point1, int point2,
                        bool ispoint1fromobj1, bool ispoint2fromobj1,
                        bool isequaldir, bool isobj1left);

// ��������� ������Σ���� ������
void ConnectObjects(SQUAREPOINT *points1, int *count1,
                    SQUAREPOINT *points2, int *count2,
                    int point1, int point2,
                    bool ispoint1fromobj1, bool ispoint2fromobj1,
                    HOBJ obj, DOUBLEPOINT *points,
                    bool isequaldir, bool isobj1left);

// ��������� ����� � ������ �����, �������� � ������
void AddPassPoint(int *passcount, PASSPOINT *passpoints,
                  int pointnum, bool ispointfromobject1);                        

// ��������� ����� � ������ �����, ������ ���� ��� ������� �� �������� � ������
void AddExtremPassPoint(int *passcount, PASSPOINT *passpoints,
                        SQUAREPOINT *points, int pointnum, int priornum,
                        int nextnum, double precision, bool ispointfromobject1); 

// ���������� ������ �����, �������� � ������
void SetPassPoints(int *passcount, PASSPOINT *passpoints, int precision,
                   SQUAREPOINT *points, int count, SQUAREPOINT *points2, int count2,
                   bool ispointfromobject1);                                     

// ����� ����� ��� ������������� ���������� ��������
void FindConnect(bool *ispointfromobj1, bool defaultispointfromobj1,
                 int truenum, int firstnum, int *foundnum,
                 SQUAREPOINT *points, int count, double precision);

// ���� ������ ���� ��� ���������� ���������� ��������
bool FindConnectPair(SQUAREPOINT *points1, int count1, SQUAREPOINT *points2, int count2,
                     double precision, bool *ispoint1fromobj1, bool *ispoint2fromobj1,
                     int *point1, int *point2);

// �������� ����������� �����
bool IsTriangleConnect(SQUAREPOINT *points1, SQUAREPOINT *points2,   
                       int point1, int point2,
                       bool ispoint1fromobj1,
                       bool ispoint2fromobj1);
};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++  TObjectConsent +++++++++++++++++++++
// +++++++++++++ ����� : ������������ ��'�����  ++++++++++++
// ������ ��'��� - ������ (c ������������), ������� �������������
// ������ ��'��� - ������ (��� �����������, ���������),
//                 �� �������� �������������.
//
// ������������ ������ ��������� ��'����� ���
// �������� ��������� (��� ������ ������������ SQUARE).
//
// ���� ������ ��'��� �������� (�� ���������)
// � ����� ������������ LINE, �� ������ �������� �������
// ������� ��������� �������
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TObjectConsent : public TObjectCutSubject
{

 public:

  //*********************************************************
  //  �������� �������
  //  TObjectConsent - �����������,
  //  LoadObjects - ��������� ������,
  //  GetNextObject - ����� ��������� ������
  //*********************************************************


  TObjectConsent():TObjectCutSubject(),
                   SubObject(), DataOutSub(), Subcut() 
                  {LoadSub = 0;};

  // data1 - ������ (c ������������), ������� �������������
  // data2 - ������ (��� �����������, ���������),
  //                 �� �������� �������������.
  // method - ����� ������������ ��������:
  //          LOCAL_LINE - ��������,
  //          LOCAL_SQUARE - ��������� (�� ���������)
  // subject - ����� ���������� 2 ������� (�� ��������� = 0)
  // ������� �������� ��������� � ������ ������� �������
  TObjectConsent(TDataEdit *data1, TDataEdit *data2, int method = LOCAL_SQUARE,
                 int subject = 0, double precision = PRECISION):
  TObjectCutSubject(data1, data2, method, subject, precision),
                 SubObject(), DataOutSub(), Subcut() 
                 {LoadSub = 0;};

  // info1 - ������ (c ������������), ������� �������������
  // info2 - ������ (��� �����������, ���������),
  //                 �� �������� �������������.
  // subject - ����� ���������� 2 ������� (�� ��������� = 0)
  // ������� �������� ������ ���� ��������� � ������ ������� �������

  TObjectConsent(TObjectInfo *info1, TObjectInfo *info2,
                 int method = LOCAL_SQUARE,
                 int subject = 0, double precision = PRECISION):
  TObjectCutSubject(info1, info2, method, subject, precision),
                 SubObject(), DataOutSub(), Subcut() 
                 {LoadSub = 0;};

  // ��������� �������
  // info1 - ������ (c ������������), ������� �������������
  // info2 - ������ (��� �����������, ���������),
  //                 �� �������� �������������.
  // method - ����� ������������ ��������:
  //          LOCAL_LINE - ��������,
  //          LOCAL_SQUARE - ��������� (�� ���������)
  // subject - ����� ���������� 2 ������� (�� ��������� = 0)
  // ������� �������� ����� ��������� � ������ ������� �������
  int LoadObjects(TObjectInfo* info1, TObjectInfo* info2,
                  int method = LOCAL_SQUARE, int subject = 0,
                  double precision = PRECISION);

  // ��������� �������
  // data1 - ������ (c ������������), ������� �������������
  // data2 - ������ (��� �����������, ���������),
  //                 �� �������� �������������.
  // method - ����� ������������ ��������:
  //          LOCAL_LINE - ��������,
  //          LOCAL_SQUARE - ��������� (�� ���������)
  // subject - ����� ���������� 2 ������� (�� ��������� = 0)
  // ������� ������ ���� �������� ��������� � ������ ������� �������
  int LoadObjects(TDataEdit *data1, TDataEdit *data2,
                  int method = LOCAL_SQUARE, int subject = 0,
                  double precision = PRECISION);

  // ����� ��������� ������
  // ��� ������ ���������� 0
  TDataEdit *GetNextObject();


  //*********************************************************
  //  ��������������� ������� ��� ������������� �����������
  //*********************************************************

  // ����� ��������� ������ ��� ������ � ������������
  // num  - ����� ���������� � datain
  int GetNextObjectSub(int loadsub = 0);

  // �������� � �������� ���������� ���������� ��� �������� ��������
  int AppendLineSubject();

  // ����� ����� �����������
  int SubNum;    

  protected:

  // ������ �����������, ���������� � ���� ����������
  TBitSet64K SubObject;

  // ���� ������ � ������� �����������
  int LoadSub;

  // ������� ��������� ������� (������� �����������)
  TDataEdit DataOutSub;

  // ����� ������ � ������������
  TObjectCutSubject Subcut;
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++  TObjectCutByLine++++++++++++++++++++
// ++++ ����� : ���������� ���������� ��'���� �� ����� +++++
// ������ ��'��� - ������ (����� ��� �����������),
//                 �� ������� �����
// ������ ��'��� - ������ (c ������������, ������������),
//                 ������� �����
// method - ����� ������� ��������:
//          LOCAL_LINE - ��������,
//          LOCAL_SQUARE - ���������
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TObjectCutByLine : public TPointCross
{
  public:

  enum INSIDEDUBL
       {
       OFF    = 0,     // �����������
       FIRST  = 1,     // �������������� � ������ ���
       SECOND = 2      // �������������� ������ ��� � ���������
       };

  //*********************************************************
  //  �������� �������
  //  TObjectCutByLine - �����������,
  //  LoadObjects      - ��������� ������,
  //  GetNextObject    - ����� ��������� ������
  //*********************************************************

  TObjectCutByLine();
  ~TObjectCutByLine();

  // ����������� ������ TObjectCutByLine
  // info1 - ������ (����� ��� �����������),
  //         �� �������� �����
  // info2 - ������ (������������, ������������),
  //         ������� �����
  // method - ����� ������� ��������:
  //          LOCAL_LINE - ��������,
  //          LOCAL_SQUARE - ���������
  TObjectCutByLine(TObjectInfo* info1, TObjectInfo* info2, int method,
                   double precision = PRECISION);

  // ����������� ������ TObjectCutByLine
  // data1  - ������ (����� ��� �����������),
  //          �� �������� �����
  // data2  - ������ (c ������������, ������������),
  //          ������� �����
  // method - ����� ������� ��������:
  //          LOCAL_LINE - ��������,
  //          LOCAL_SQUARE - ���������
  // ������� �������� ��������� � ������ ������� �������
  TObjectCutByLine(TDataEdit *data1, TDataEdit *data2, int method,
                   double precision = PRECISION);

  // ��������� �������
  // precision - ������ ��� ���������� ����� �����������
  int LoadObjects(TObjectInfo* info1, TObjectInfo* info2, int method,
                  double precision = PRECISION);
  int LoadObjects(TDataEdit *data1, TDataEdit *data2, int method,
                  double precision = PRECISION);
  int LoadObjects(TDataEdit *data1, TDataEdit *data2, int method, int subject,
                  double precision = PRECISION);

  // ����� ��������� ������
  // ��� �������� ���������� ����� ��������� �������
  // ��� ��������������� ������
  // ��� ������ ���������� 0
  TDataEdit *GetNextObject();

  protected:

  // ������������� ���������� ������
  int InitObjectCut();

  // �������� ����������� �������� ��������
  int _fastcall ControlLocal(TDataEdit *data2, int method);

  // ���������� ���� ������ ������� � ������� PointCross1, PointCross2
  int SetInside();

  // ����������� ����������� ������������ �������
  int _fastcall InsideSubObject(TDataEdit *data);

  // ����� ��������� ������ ��� ������ � ������������
  // dataout - ����
  // datain  - ������
  // subnum  - ����� ���������� � datain
  int _fastcall GetNextObjectSub(int num, int loadsub);

  // ���������������� ������� ����� �����������
  // cross1 - �������� ������
  // cross2 - ��������� ������
  void _fastcall CorrectPointCross(POINTCROSS *cross1,
                                   POINTCROSS *cross2,
                                   TDataEdit *data1,
                                   TDataEdit *data2,
                                   int count);

  // ���������� ��������� ����� ������������ ��������
  // ���������� ALL     - ���� ��� ����� ����� � �������
  //            BEFORE  - ������ ���� ����� ����� � �������
  int _fastcall GetPlacePoint(DOUBLEPOINT *point1, DOUBLEPOINT *point2,
                              TDataEdit *data);

  protected:

  // ������� ��������� �������
  TDataEdit DataOut;

  // ������� ��������� ������� (������� �����������)
  TDataEdit DataOutSub;

  private:

  // ������ �����������, ���������� � ���� ����������
  TBitSet64K SubObject;

  // ����� ����� �����������
  int SubNum;

  // ���� ������ � ������� �����������
  int LoadSub;

  // ����� ������ � ������������
  TObjectCutSubject Subcut;

  int * InsideDublicate1;
  int * InsideDublicate2;
  int SetInsideDublicate;
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++  TPointCrossObject +++++++++++++++++++++
// +++ ����� : ���������� ����� ����������� ���� ��'����� ++
//                  � �����'������ !!!
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TPointCrossObject
{
  public:

  TPointCrossObject();
  ~TPointCrossObject();

  // ��������� �������
  // info1 - 1 ������
  // info2 - 2 ������
  // ���������� ����� ����� �����������
  int LoadObjects(TObjectInfo *info1, TObjectInfo *info2,
                  double precision = PRECISION);

  // ��������� �������
  // info1 - 1 ������
  // info2 - 2 ������
  // subject1 - ����� ���������� 1 �������
  // subject2 - ����� ���������� 2 �������
  // ���������� ����� ����� �����������
  int LoadObjects(TObjectInfo *info1, TObjectInfo *info2,
                  int subject1, int subject2,
                  double precision = PRECISION);

  // ��������� ����� �����������
  // number - ����� �����
  // point - ����� (���������� � ������ �� ���������)
  // ��� ������ ���������� 0
  int GetPoint(int number, CROSSPOINT *point);

  protected:

  // ���������� �������� �������� ������
  // number - ����� �����
  // point - ����
  // ��� ������ ���������� 0
  int _fastcall SetPoint(int number, CROSSPOINT *point);


  protected:

  // ������� �������������� ��������
  TDataEdit Data1;
  TDataEdit Data2;

  TObjectInfo *Info1;
  TObjectInfo *Info2;

  // ����� ���������� ����� �����������
  TPointCross PointCross;

  // ����� ������� ����� �����������
  CROSSPOINT *Memory;

  public:

  // ����� ����� �����������
  int NumCross;
};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++  TObjectCutSubLine  +++++++++++++++++++++
// +++++++++++++ ����� : ����������� ��'�����  +++++++++++++
// ������ ��'��� - ������ (��� �����������, ���������),
//                 �� �������� ����� ( �������� �����)
// ������ ��'��� - ������ (c ������������, ������������),
//                 ������� �����
// method - ����� ������� ��������:
//          LOCAL_LINE - ��������,
//          LOCAL_SQUARE - ���������     
// � TObjectCutSubLine �������� �������
// ������ ��'��� - ������ (��������� ������ c ������������),
// ������ ��'��� - ������ (��������),
// method - ����� ������� ��������:
//          LOCAL_LINE - ��������,
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TObjectCutSubLine : public TObjectCut
{

  public:

  //*********************************************************
  //  �������� �������
  //  TObjectCutSubLine - �����������,
  //  LoadObjects - ��������� ������,
  //  GetObject - ����� ������
  //*********************************************************

  TObjectCutSubLine();
  ~TObjectCutSubLine();

  TObjectCutSubLine(TDataEdit *data1, TDataEdit *data2, int method,
                    double precision = PRECISION,int full = 0);

  TObjectCutSubLine(TObjectInfo* info1, TObjectInfo* info2, int method,
             double precision = PRECISION, int full = 0);

  // ��������� �������
  int LoadObjects(TDataEdit *data1, TDataEdit *data2, int method,
                  double precision = PRECISION, int full = 0);
  int LoadObjects(TObjectInfo* info1, TObjectInfo* info2, int method,
                  double precision = PRECISION, int full = 0);

  // ����� ���������� ������
  TObjectInfo *GetNextObject(TObjectInfo * info);     

public:

  // ����� �������� �����������
  int ResultSubNum;

  // �������� ������
  TObjectInfo InfoOut;                  

  int FlagSubLine;
  
};

#endif

