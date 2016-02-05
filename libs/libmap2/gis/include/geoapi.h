
#ifndef GEOAPI_H
#define GEOAPI_H

#ifndef GEOTYPE
 #include "GeoType.h"
#endif

#include "MapApi.h"

#define GLAPI _export WINAPI

typedef long int  HTEOIMP;  // ������������� ������ �������  TEO
typedef long int  HTEOEXP;  // ������������� ������ �������� TEO
typedef long int  HTPRIMP;  // ������������� ������ �������  TPR
typedef long int  HTPREXP;  // ������������� ������ �������� TPR

extern "C"
{
// ����������� ������� ������� ������������� ������

 int WINAPI _export glGeoLoad(HMAP hmap, TASKPARM *parm,char *inFilename,
                    char *teoFilename,char *tprFilename,char *xyhFilename);

 //--------------------------------------------------------------
 // �������� ����� TEO
 //--------------------------------------------------------------

 // ��������� ������ ������� TEO -  �����
 // filename - ������ ��� �������������� �����
 // ��� ������ ���������� 0,
 // ����� - ��������� �� ��������� �����

 HTEOIMP GLAPI CreateInputTeo(const char *filename);

 // �������� ������ ������� TEO -  �����
 // filename - ������ ��� �������������� �����
 // ��� ������ ���������� 0,
 // ����� - ��������� �� ��������� �����

 long int GLAPI CloseInputTeo(HTEOIMP hti);

 // ��������� ����������
 // ��� ������ ���������� 0

 long int GLAPI GetStatisticTeo(HTEOIMP hti,TEOSTAT *stat);

 // ������� ��������� ���� ���������
 // ��� ������ ���������� 0
 // ����� ��� ���� (COURSE_ ...)

 long int GLAPI NextBlockTeo(HTEOIMP hti);

 // ������� ������� �����
 // � point ���������� �������� �����
 // ��� ������ ���������� 0

 long int GLAPI NextBasePointTeo(HTEOIMP hti,BASEPOINT* point);

 // ������� ����� ����
 // � point ���������� �������� �����
 // ��� ������ ���������� 0

 long int GLAPI NextMeasurePointTeo(HTEOIMP hti,MEASUREPOINT* point);

 //--------------------------------------------------------------
 // �������� ����� TPR
 //--------------------------------------------------------------

 // ��������� ������ ������� TPR -  �����
 // filename - ������ ��� �������������� �����
 // ��� ������ ���������� 0,
 // ����� - ��������� �� ��������� �����

 HTPRIMP GLAPI CreateInputTpr(const char *filename);

 // �������� ������ ������� TEO -  �����
 // filename - ������ ��� �������������� �����
 // ��� ������ ���������� 0,
 // ����� - ��������� �� ��������� �����

 long int GLAPI CloseInputTpr(HTPRIMP hti);

 // ��������� ����������
 // ��� ������ ���������� 0

 long int GLAPI GetStatisticTpr(HTPRIMP hti,TEOSTAT *stat);

 // ������� ��������� ���� ���������
 // ��� ������ ���������� 0
 // ����� ��� ���� (COURSE_ ...)

 long int GLAPI NextBlockTpr(HTPRIMP hti);

 // ������� ������� �����
 // � point ���������� �������� �����
 // ��� ������ ���������� 0

 long int GLAPI NextBasePointTpr(HTPRIMP hti,BASEPOINT* point);

 // ������� ����� ����
 // � point ���������� �������� �����
 // ��� ������ ���������� 0

 long int GLAPI NextMeasurePointTpr(HTPRIMP hti,MEASUREPOINT* point);

 //--------------------------------------------------------------
 // ���������� ����� TEO
 //--------------------------------------------------------------
 // ��������� ������ �������� TEO -  �����
 // filename - ������ ��� ��������������� �����
 // ��� ������ ���������� 0,
 // ����� - ��������� �� ��������� �����

 HTEOEXP GLAPI CreateOutTeo(const char *filename);

 // �������� ������ ������� TEO -  �����
 // filename - ������ ��� �������������� �����
 // ��� ������ ���������� 0,
 // ����� - ��������� �� ��������� �����

 long int GLAPI CloseOutTeo(HTEOEXP hte);

 // �������� ������ �����������
 // text - ����� ��������� (����� ������� ������������ "//")
 // ��� ������ ���������� 0

 long int GLAPI WriteMessageTeo(HTEOEXP hte,const char *text);

 // �������� ����������
 // stat - �������������� ���������� (������������ � ���� .INF)
 // ��� ������ ���������� 0

 long int GLAPI WriteStatisticTeo(HTEOEXP hte,TEOSTAT *stat);

 // �������� ������� ������ �����
 // type - ������ ���������� (�������������) (COURSE_UNDEFINED, ...)
 // ��� ������ ���������� 0

 long int GLAPI WriteBeginBlockTeo(HTEOEXP hte,int type);

 // �������� ���������� � ������� �����
 // point - �������� �����
 // ��� ������ ���������� 0

 long int GLAPI WriteBasePointTeo(HTEOEXP hte,BASEPOINT *point);

 // �������� ���������� � ����� ���� � ������ .DAT
 // point - �������� �����
 // ��� ������ ���������� 0

 long int GLAPI WriteMeasurePointTeo(HTEOEXP hte,MEASUREPOINT *point);

 // �������� ������� ����� �����
 // ��� ������ ���������� 0

 long int GLAPI WriteEndBlockTeo(HTEOEXP hte);


 //--------------------------------------------------------------
 // ���������� ����� TPR
 //--------------------------------------------------------------

 // ��������� ������ �������� TEO -  �����
 // filename - ������ ��� ��������������� �����
 // ��� ������ ���������� 0,
 // ����� - ��������� �� ��������� �����

 HTPREXP GLAPI CreateOutTpr(const char *filename);

 // �������� ������ ������� TEO -  �����
 // filename - ������ ��� �������������� �����
 // ��� ������ ���������� 0,
 // ����� - ��������� �� ��������� �����

 long int GLAPI CloseOutTpr(HTPREXP hte);

 // �������� ������ �����������
 // text - ����� ��������� (����� ������� ������������ "//")
 // ��� ������ ���������� 0

 long int GLAPI WriteMessageTpr(HTPREXP hte,const char *text);

 // �������� ����������
 // stat - �������������� ���������� (������������ � ���� .INF)
 // ��� ������ ���������� 0

 long int GLAPI WriteStatisticTpr(HTPREXP hte,TEOSTAT *stat);

 // �������� ������� ������ �����
 // type - ������ ���������� (�������������) (COURSE_UNDEFINED, ...)
 // ��� ������ ���������� 0

 long int GLAPI WriteBeginBlockTpr(HTPREXP hte,int type);

 // �������� ���������� � ������� �����
 // point - �������� �����
 // ��� ������ ���������� 0

 long int GLAPI WriteBasePointTpr(HTPREXP hte,BASEPOINT *point);

 // �������� ���������� � ����� ���� � ������ .DAT
 // point - �������� �����
 // ��� ������ ���������� 0

 long int GLAPI WriteMeasurePointTpr(HTPREXP hte,MEASUREPOINT *point);

 // �������� ������� ����� �����
 // ��� ������ ���������� 0

 long int GLAPI WriteEndBlockTpr(HTPREXP hte);

}
#endif
