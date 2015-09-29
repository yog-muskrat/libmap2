// 29/11/08

#ifndef MAPEDFRM_H
#define MAPEDFRM_H

#ifndef MEDAPI_H
  #include "medapi.h"   // �������� �������� ���������� MAPAPI
#endif


typedef struct MEDRSCPARM
{
 long int Regime;             // ����� ��������
                              // �� MED_KEY1 �� MED_KEY14
                              // == -1 - ������ �������� ���������� � �������!
 long int Repeat;             // ������������� ���������
                              // == 1 - �����������
                              // == 0 - �������������
                              // == -1 - ���������� � �������

 long int FlagKey;            // ���� ��������� ������� ��������
                              // ���� == 0, �� ����������� �������
                              //            ��������������� �������������,
                              //            ����� � ������������ � ���
 long int Rezerv;
 char NameDlg[128];           // �������� �������
 char Key[32];                // 0 - ����������, 1 - ��������
} MEDRSCPARM;


// ������� ������� ���������
#define HOTKEYCOUNT      23
#define KEY_INSERT       0
#define KEY_DELETE       1
#define KEY_REALPOINT    2
#define KEY_SELECTPOINT  3
#define KEY_CREATEPOINT  4
#define KEY_INSNOREPLY   5
#define KEY_LOCK         6
#define KEY_CENTRE       7
#define KEY_COPYPART     8
#define KEY_SAVEPOINT    9
#define KEY_LASTPOINT    10
#define KEY_PREVPOINT    11
#define KEY_REVERT       12
#define KEY_UNDO         13
#define KEY_SPACE        14
#define KEY_HORIZONT     15
#define KEY_VERTICAL     16
#define KEY_RECT         17
#define KEY_VARIABLE     18
#define KEY_AUTO         19
#define KEY_BARSIZE      20
#define KEY_PLACE        21
#define KEY_OPTIONS      22

// ��������� ��� ��������� ������� ������ ���������
typedef struct HOTKEYSPARM
{
char Name[256];            // �������� ������
long int Key;              // ��� �������
long int KeyAdd;           // ��� ���������� (��������������) �������
long int MenuIdent;        // ������������� ����
long int Rezerv;
} HOTKEYSPARM;


// ��������� ���������
typedef struct MEDPROPERTY
{
 double FindRadius;        // ������ ������
 double Step;              // ��� ����������
 double Filter;            // ����� ����������
 double ZoneWide;          // ������ ����
 double AdjustValue;       // ����� ������������
 double SplineValue;       // ����� �����������

 long int IsSetup;              // ��������� ������ ��������� ?
 long int IsDevide;             // ��������� �� ������   ?
 long int IsFrameCut;           // �������� �� �����   ?
 long int IsEditFrame;          // ������������� ����� ?

 long int IsSemantic;           // ����������� ��������� ?
 long int IsClearSelect;        // ���������� ��������� ?
 long int Is3dData;             // ���������� ������� ?
 long int IsCursor;             // ���� ������� ?

 long int IsNext;               // ������ �����������?
 long int IsSeek;               // ������ �����������?
 long int IsCross;              // ������� ����� �����������?
 long int FilterType;           // ��� ����������

 long int IsGroup;              // ������������ ������?
 long int FindSector;           // ������ ������
 long int Spy;                  // ������� �� ��������������?
 long int Speed;                // �������� ������������ (%)

 long int ViewSemanticCode;     // ��������������� ���������
 long int IsStatistic;          // ���������� ����������
 long int PointInSpline;        // ����� � �������
 long int AutoCode;             // ��� ����� ���������� ���������

 long int IsTrace;              // �����������
 long int Rezerv;               // ������

 long int MapSplineType;        // ��� ������� ��� MAP   
 long int SitSplineType;        // ��� ������� ��� SIT   
 
 long int IsDrawNumberPoints;   // �������� ������ ����� ��� �������� ���������   // 29/11/08
                                // �������   

 HOTKEYSPARM HotKey[32];        // ��������� ������� ������

} MEDPROPERTY;


// ��������� ����������
typedef struct CUTOPTIONS
{
 long int InMode;
 long int Incode;
 long int Outcode;
 long int Reserv;
} CUTOPTIONS;

// ��������� �������� � ����������� �������
typedef struct ROTATEMOVEPARAM
{
 double Angle;                 // ���� �������� � ��������
 DOUBLEPOINT Delta;            // �������� � ������
 DOUBLEPOINT StationaryPoint;  // ����� ��������/����� �������� � ������
 long int Regime;              // ����� �����������
                               // 0 - �� ����������,
                               // 1 - �� �����������
                               // 2 - �� ����������
 long int Scale;               // ������� ��������������� ������������
                               // ����� �������� (0 ��� 1)
} ROTATEMOVEPARAM;


// ��������� ����������� �������
typedef struct MULTIOBJECTPARM
{
 DFRAME Frame;                 // �������� �������
 DOUBLEPOINT Offset;           // �������� ������������ ������ (������� ������ ����)

 // ����������� � ���� ������������
 DOUBLEPOINT Step;             // ��� ��� ����������� � ���� ������������
 DOUBLEPOINT Koordinates;      // �������� ���������� ��� ����������� � ���� ������������
 double Distance;              // ��� ��� ����������� � ����� �����������
 double Angle;                 // ���� �������� � ��������
 long int FlagDirect;          // ����������� � ���� ��� ����� �����������
                               // 0 - �� ����  ������������
                               // 1 - � ����� �����������
 long int FlagCount;           // ����������� �� ���������� ���
                               // �� �������� �����������
                               // (1 - �� ����������, 0 - �� �����������)
 long int CountX;              // ���������� �� ������ ��� ����������� � ���� ������������
 long int CountY;              // ���������� �� ������ ��� ����������� � ���� ������������

 // ����������� � ����� �����������
 long int    Count;                 // ���������� ��� ����������� � ����� �����������
 long int    Log;                   // ������ � ������ ����������

} MULTIOBJECTPARM;

// ��������� ��������� ����������� ������������ �������
typedef struct UPDATEIMAGEOBJECT
{
 HDRAW DrawLine;      // ��������� �� ����������� �������� ��������� �������
 HDRAW DrawSquare;    // ��������� �� ����������� �������� ���������� �������
 HDRAW DrawPoint;     // ��������� �� ����������� �������� ��������� �������
 HDRAW DrawTitle;     // ��������� �� ����������� �������
 long int CodeLine;   // ��� ��������� �������
 long int CodeSquare; // ��� ���������� �������
 long int CodePoint;  // ��� ��������� �������
 long int CodeTitle;  // ��� �������
 long int NoEnableLine;   // ����������� ����������� ��� ��������� ����
 long int NoEnableSquare; // 0 - ��������, 1 - ���
 long int NoEnablePoint;
 long int NoEnableTitle;
} UPDATEIMAGEOBJECT;

// ������� �������� �� ��������
#define INIT          		1	// ������������� (�������) �������
#define SUBJECT 	      	2	// ������� ����� ���������
#define POINTN          3	// ������������ ����� �����
#define POINTMIN  	     4	// ������������ ����� �����
#define POINTMAX      		5	// ����������� ����� �����
#define ANYPOINT       	6	// ������ ������������ ���������� �����
#define MYPOINT        	7	// ����� ����� �� ������ �������
#define OTHERPOINT     	8	// ����� ����� � ������� �������
#define SPLINEON     	 	9	// �������� ����� ������������ ������� �� �������
#define BARON     		    10	// �������� ����� ������������ ������� �� //��������������
#define STRIPEON     	 	11	// �������� ����� ������������ ������� �� ������
#define CIRCLEON     		 12	// �������� ����� ������������ ������� �� //����������
#define ARBITRON     		 13	// ��������� ������ ��������������� ������������
#define ATTRIBUTE     		14	// ������ ��������� �� ������
#define SETTEXT     		  15	// ������ �����
#define MEMOPOINT     		16	// ��������� ��������� ��������� �����
#define REMEMBERPOINT   17 // �������� ����� � ����������� �� ������
#define GROUPHEAD       18 // �������� �������� ��������
#define GROUPSUBORD     19	// �������� �������� ������������ �������
#define ENDGROUP        20	// ��������� �������� ������
#define COMMIT          21	// �������� ������
#define QUIT     	     	22	// ��������� ����� ��������
#define ANYDIRECT     		23	// ��������� ������ �����. � ����.
#define STAFF           24 // ������� ��������������� ��
#define STAFFON         25 // ������ �������� ���������������� ��
#define STAFFOFF        26 // ��������� �������� ���������������� ��
#define POINT1		        27	// ������ ���� �����
#define POINT2			       28	// ������ ��� �����
#define POINT3		       	29	// ������ ��� �����
#define SEMANTICCODE 	 	30	// �������� ��������� �� ����

// ��� �������� �������� �� ��������
typedef struct TESCENE   
{
  char SceneId[256];            // ������������� �������� (������������ ��� ������� �������)
  long int  ActionCount;        // ���������� ��������� � ��������
  long int  Rezerv;
}TESCENE;

typedef struct SCACTION
{
  char ActionMessage[256];      // ���������� ��������
  long int ActionType;          // ��� ��������
  long int Number;              // ����� ��� ������������ ������ (POINTN, MEMOPOINT � �.�)
} SCACTION;


// ������ ��� ������� medSeekObject (������ �������� ��������)
enum SEEKREGIME
{
  SEEK_RESTORE        = 0, // �������������� ������������������ �������
  SEEK_RESTORE_DELETE = 1, // �������������� ��������� ��������
  SEEK_CREATE         = 2, // �������� ������� �� ����������� �� ���������� �����
  SEEK_MARK_DELETE    = 3, // �������� ���������� ��������
  SEEK_MARK_DELETESUB = 4, // �������� ����������� ���������� ��������
  SEEK_MARK_CREATESUB = 5, // �������� ����������� ���������� ������� �� ����������
  SEEK_MARK_COPY      = 6, // ����������� ���������� �������� �� ������ �����
  SEEK_MARK_MODIFY    = 7, // ��������� ���� ���������� ��������
  SEEK_MARK_CUT       = 8, // ���������� ���������� ��������
  SEEK_MARK_CROSS     = 9, // �������� ����� ����������� ���������� ��������
  SEEK_MARK_CONSENT   = 10,// ������������ ���������� ��������
  SEEK_MARK_VISIBILITY= 11,// ��������� ��������� ���������� ��������
  SEEK_MARK_DIRECT    = 12,// ��������� ����������� ���������� ���������� ��������
  SEEK_MARK_SPLINE    = 13,// ����������� ���������� ��������
  SEEK_MARK_FILTER    = 14,// ���������� ���������� ��������
  SEEK_MARK_ADDHIGHT  = 15 // ���������� ������ � ���������� �������
};

// ������ ��� ������� medMessageSet
//       (������ ������� ������ ����������� ��������)
enum SETREGIME             
{
  SET_ONE   = 1,           // ��������� ������
  SET_GROUP = 2,           // ��� ������
  SET_HIERARCHY = 3        // ��������
};

extern "C"
{
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//            �������  ��������� ( ����������� ��� )
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 // ������ ������ ���� ������� �� ����� ��������
 // ( ������ ��� ��������� ����� )
 // hmap - ������������� �������� ��������� �����
 // hobj - ������������� �������
 // hselect - ������
 // (���� hselect == 0 - ������ �� ������������)
 //           (���� hselect == 0 - ������ �� ������������)
 //            ���� hselect != 0 � � hselect �����������
 //            �����, �� ������ �������� �� ����� �����.
 //            ���� � hselect ����� �� �����������, ������
 //            �������� �� ���� ������ ���������.
 // ���������� ���������� ��� �������
 // ��� ������ ��� ������ ���������� 0
 long int _export WINAPI medChoiceTypeObjectSpecific
                        (HMAP hmap, TASKPARM *taskparm,
                         HOBJ hobj, HSELECT hselect,
                         MEDRSCPARM *medparm);


 // ������ ������ ���� ������������ ��������� �������
 // ( ������ ��� ��������� ����� )
 //  ������� ����������� �������� ������ ��� ��������� �����
 //  hmap - ������������� �������� ��������� �����
 //  hobj - ������������� �������
 //  hselect - ������
 //           (���� hselect == 0 - ������ �� ������������)
 //            ���� hselect != 0 � � hselect �����������
 //            �����, �� ������ �������� �� ����� �����.
 //            ���� � hselect ����� �� �����������, ������
 //            �������� �� ���� ������ ���������.
 // name - ��������� �������
 // ��� ���������� ���������� ���������� ��� ������� ����� 0
 // ��� ������ ��� ������ ���������� 0

 long int _export WINAPI medChoiceLineImageSpecific
                        (HMAP hmap,TASKPARM *taskparm,
                         HOBJ object, HSELECT hselect,
                         MEDRSCPARM *medparm);


 // ������ ������ ���� ������������ ���������� �������
 // ( ������ ��� ��������� ����� )
 //  hmap - ������������� �������� ��������� �����
 //  hobj - ������������� �������
 //  hselect - ������
 //           (���� hselect == 0 - ������ �� ������������)
 //            ���� hselect != 0 � � hselect �����������
 //            �����, �� ������ �������� �� ����� �����.
 //            ���� � hselect ����� �� �����������, ������
 //            �������� �� ���� ������ ���������.
 // name - ��������� �������
 // ��� ���������� ���������� ���������� ��� ������� ����� 0
 // ��� ������ ��� ������ ���������� 0

 long int _export WINAPI medChoiceSquareImageSpecific
                        (HMAP hmap, TASKPARM *taskparm,
                         HOBJ object, HSELECT hselect,
                         MEDRSCPARM *medparm);


 // ��������� ���������� ���������
 // hmap - ������������� �������� ��������� �����
 // parameters - ��������� ����������
 // ���������� - 0 - �����
 //              1 - ����� ���������
 //              -1 - ��������� �� ���������

 long int _export WINAPI medSetEditParameters
                        (HMAP hmap, TASKPARM *taskparm,
                         MEDPROPERTY *parameters);


 // ���������/ ��������� ������ ������������ �������
 // title - ������ ��� �����
 // length - ����� ������
 // name - ��������� �������
 //        ���� == 0 - ��������� �� ��������
 // ��� ������ ���������� 0, ����� 1

 long int _export WINAPI medSetTitle(TASKPARM *taskparm,
                                     char *title, long int length,
                                     char *name);

 // ���������/ ��������� ������ ������������� �������
 // hobj - ������������� ������� ���� �������
 // subject - ����� �����������
 // ��� ������ ���������� 0, ����� 1

 long int _export WINAPI medSetPolyTitle(TASKPARM *taskparm,
                                         HOBJ hobj, long int subject);


 // ������� �����
 // pointcount - ����� ����� �����
 // oldpoint - ���������� �����
 // firstpoint - ������� �����
 // newpoint - ����� �����
 // ��� ������ ���������� 0, ����� 1

 long int _export WINAPI medInsertPoint(TASKPARM *taskparm,
                                        long int pointcount,
                                        DOUBLEPOINT oldpoint,
                                        DOUBLEPOINT firstpoint,
                                        DOUBLEPOINT *newpoint);


 // �������� ������� �������
 // info - ������ ���� ������
 // ��� ������ ���������� 0, ����� 1

 long int _export WINAPI medCreateMixedLabel(HMAP hmap,TASKPARM *taskparm,
                                             HOBJ info);


 // ��������� ������ ������� �������
 // info - ������ ���� ������� ��� ������
 // ��� ������ ���������� 0, ����� 1

 long int _export WINAPI medSetMixedLabel(HMAP hmap,TASKPARM *taskparm,
                                          HOBJ info);


 // ������ ����� �����/������
 // number - ����� �����/������
 // type - ��� (0 - �����, 1 - �����)
 // ��� ������ ���������� 0, ����� 1

 long int _export WINAPI medSetMapNumber(HMAP hmap, TASKPARM *taskparm,
                                         long int *number, long int type);


 // ������ ����� �����/������
 // number - ����� �����/������
 // type - ��� (0 - �����, 1 - �����)
 // count - ���������� �������� ����.�������
 // multy - ( 1- ������������� �����, 0 - ���)
 // ��� ������ ���������� 0, ����� 1
 
 long int _export WINAPI medSetListMapNumber(HMAP hmap, TASKPARM *taskparm,
                                         long int *number, long int type,
                                         long int count, long int multy);


 // ������ ������ ������� �������� �������:
 // - ������������ ������, �������������� �������������,
 //   ��������� ������������� � �.�.
 // name - �������� �������
 // mode - ������ �������� (������������� �� MED_KEY1 �� MED_KEY14)
 //        = -1 - ������ �������� ���������� � �������!
 // local - �����������(���) �������
 // ��� ������ ���������� 0, ����� 1

 long int _export WINAPI medSetCreationMode(TASKPARM *taskparm,
                                            char *name,
                                            long int *mode,
                                            long int local);

 // ���������� ��������� ���������� ��������
 // ��� ������ ��� ������ ���������� 0, ����� 1

 long int _export WINAPI medUpdateSemanticBySelected(HMAP hmap,
                                                     TASKPARM *taskparm);


 // ������ ���������� �������� � ����������� �������
 // ������� ��������� : rotateparm.Regime
 //                                0 - �� ����������,
 //                                1 - �� �����������
 //                                2 - �� ����������
 //                     rotateparm.StationaryPoint (����� ��������/����� �������� � ������)
 //                     rotateparm.Scale (0 ��� 1)
 //                     frame (��� Regime == 1 - �������� � ������)
 // �������� ���������: rotateparm.Regime
 //                     rotateparm.StationaryPoint
 //                     rotateparm.Angle
 //                     rotateparm.Delta
 // ��� ������ ��� ������ ���������� 0,
 // ����� 1 � ��������� ��������� rotateparm

 long int _export WINAPI medGetRotateParam(HMAP hmap, TASKPARM *taskparm,
                                           ROTATEMOVEPARAM *rotateparm,
                                           DFRAME frame);


 // ������ ������ ������� � ����� �����
 // mapnumber - ����� ������� �����
 // groupnumber - ����� ������ � ������
 // property - ��������� ���������� ���������
 // ��� ������ ��� ������ ���������� 0,
 // ����� 1, ��������� mapnumber, groupnumber
 long int _export WINAPI medSetMaket(HMAP hmap, TASKPARM *taskparm,
                                     long int *mapnumber,
                                     long int *groupnumber,
                                     MEDPROPERTY *property);


 // ������ �������� ��������
 // regime (SEEKREGIME) - ������ ������ � ���������
 // hobj - ��������� ������ (���� = 0,
 //                          ���� ������ � ����������� ���������)
 // property - ��������� ���������� ���������
 // ��� ������ ��� ������ ���������� 0,
 long int _export WINAPI medSeekObject(HMAP hmap, TASKPARM *taskparm,
                                       long int regime, HOBJ hobj,
                                       MEDPROPERTY *property);

 // ������ �������������� ������ ������� ���������� ��������
 // ��� ������ ��� ������ ���������� 0, ����� 1
 long int _export WINAPI medSeekEdit(HMAP hmap, TASKPARM *taskparm);


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//            �������  ��������� ( ���������������� ��� )
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


 // ����� ������� ������ ���� ������������ �������
 // � ���������� ������� ���������� ���������
 // object - ������������� �������
 // filter - ������
 // (���� filter == 0 - ������ �� ������������)
 // ���������� ��� ������� ��� 0 ��� ������

 long int _export WINAPI medChoiceTypeGraphics(HMAP hmap,
                                               TASKPARM *taskparm,
                                               HOBJ object,
                                               HSELECT filter/*= 0*/,
                                               MEDRSCPARM *medparm/*= 0*/);


 // ��������� ������ ���������
 // hrsc - ������������� ����� ��������
 // bot - ������ �������
 // top - ������� �������
 // botdefault - ������������ �������� �� ��������������
 // ��� ������ ���������� 0, ����� 1

 long int _export WINAPI medSetBotTop(TASKPARM *taskparm,
                                      HRSC hrsc,
                                      long int *bot, long int *top,
                                      long int *botdefault);


 // ����/��������� ���� ���������
 // value - �������� ���� (� ��������)
 // ��� ������ ���������� 0, ����� 1

 long int _export WINAPI medSetTurnAngle(TASKPARM *taskparm,
                                         double *value);



 // ����/��������� ���������� ���������� �������
 // options - ��������� ����������
 // ��� ������ ���������� 0, ����� 1

 long int _export WINAPI medSetCutParameters(HMAP hmap, TASKPARM *taskparm,
                                             CUTOPTIONS *options);


 // ���� �������� ��������������
 // size - ������ ��������������
 // ��� ������ ���������� 0, ����� 1

 long int _export WINAPI medSetBarSize(TASKPARM *taskparm,
                                       DOUBLEPOINT *size);


 // ������ ��������� �������
 // ��� ������ ���������� 0, ����� 1

 long int _export WINAPI medSetRadius(TASKPARM *taskparm,
                                      double *radius);

 // ������ ��������� ������� �� ������ "-"
 // ��� ������ ���������� 0, ����� 1

 long int _export WINAPI medSetRadiusSign(TASKPARM *taskparm,
                                         double *radius);

 // --------------------------------------------------------------
 //    ������� �������������� ��������� ���������� �� �����
 // --------------------------------------------------------------

 // ���������� ��������� � ���������� �������
 // ��� ������ ��� ������ ���������� 0, ����� 1

 long int _export WINAPI medAddSemanticBySelected(HMAP hmap,
                                                  TASKPARM *taskparm);


 // �������� ��������� � ���������� ��������
 // ��� ������ ��� ������ ���������� 0, ����� 1

 long int _export WINAPI medDeleteSemanticBySelected(HMAP hmap,
                                                     TASKPARM *taskparm);

 // ���������� ���� ������������� ��������������
 // � ���������� ��������
 // ��� ������ ��� ������ ���������� 0, ����� 1

 long int _export WINAPI medSemanticCodeUpdateBySelected(HMAP hmap,
                                                         TASKPARM *taskparm);


 // �������������� ������������� ������������� �������
 // � ���������� ��������
 // ��� ������ ��� ������ ���������� 0, ����� 1

 long int _export WINAPI medEditSemanticListBySelected(HMAP hmap,
                                                       TASKPARM *taskparm);


 // ������ ����������� �������� �� ������ �����
 // mapnumber - ����� ������� �����
 // hobj - �������/�������� ������
 //       (�������� ��� ������� � ��� ������� ���)
 // selected - ������� ������� ���������� ������� ��� ��� (0 ��� 1)
 // ��� ������ ��� ������ ���������� 0,
 // ����� 1 ��� -1 � ��������� hobj (�������, �����������, ���,
 //                           ������� ���, ������� �����)
 // ���� ��� �������� = -1 - �������� ����������� �������
 //                          �� ���������� hobjsel

 long int _export WINAPI medCopyObjectToMap(HMAP hmap, TASKPARM *taskparm,
                                            long int mapnumber,
                                            HOBJ hobj,
                                            long int selected);

 // �������� ���������, �� ��������������� ���� �������
 // asc - = 1 - �������� ������ ��� ��������
 //       = 0 - ������� �����
 // ��� ������ ���������� 0

 long int _export WINAPI medDeleteAbsurdSemantic(TASKPARM *taskparm,
                                                 HOBJ object, int asc);

 // ��������� ���������� ������� �� ini �����
 // name - �������� �������������� �������
 // ininame - ��� ini �����
 // rect - ���������� �������

 long int _export WINAPI medReadSizeDialog(const char *name, const char *ininame,
                                      RECT &rect);

 // ��������� ������� ������� � ini ����
 // name - �������� �������������� �������
 // ininame - ��� ini �����
 // rect - ���������� �������
 long int _export WINAPI medWriteSizeDialog(const char *name, const char *ininame,
                                       RECT rect);

 // ��������� ������� ������
 // ��� ������ ��� ������ ���������� 0,
 long int _export WINAPI medSetHotKey(TASKPARM *taskparm,
                                      HOTKEYSPARM *hotkey, int count);

 // ������������� ������� ������
 // ��� ������ ��� ������ ���������� 0,
 long int _export WINAPI medInitHotKey(TASKPARM *taskparm, HOTKEYSPARM *hotkey, 
                                       int count);
                                       
}       // extern "C"

#endif  // MAPEDFRM
