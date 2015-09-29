
#if !defined (MAPFRAME_H)
#define MAPFRAME_H

#ifndef MAPINFO_H
  #include "mapinfo.h"
#endif

enum
{                             // ���� ������ ��� �������� ����� �����
  IDC_MAPFRAME_RSC      = 1,  // ������ �������� ��� ��������� RSC
  IDC_MAPFRAME_REGISTER = 2,  // ������ ����������� ����� �����
  IDC_MAPFRAME_SCALE    = 3,  // ������ � �������� ����� ��� ��������
  IDC_MAPFRAME_CREATE   = 4,  // ������ ��� ������������� ������� �����
  IDC_MAPFRAME_APPEND   = 5,  // ������ ��� ���������� �����
  IDC_MAPFRAME_DIST     = 6,  // ������ ��� �������� ������� �����
  IDC_MAPFRAME_STRUCT   = 7,  // ������ ��������� ������ �������
  IDC_MAPFRAME_KIND     = 8,  // ������ � ���� ����������� �����
};

typedef struct MAPFRAMEDATA     // ������ ��� �������� ������� "����� �����"
{
 double        DistPointFrame; // ���������� ����� ������� ������� � ��������
 TMap *        Map;            // �������� �����
 TObjectInfo * ObjectInfo;     // ����������� ������ ����� �����
 long          ExCodeFrame;    // ��� ����� �����
 int           PointFrame;     // ���������� ����� � ����� �����
 int           Err;            // ��� ������
}
  MAPFRAMEDATA;

// ������������� ��������� MAPFRAMEDATA
void _fastcall mfInit(MAPFRAMEDATA * data);

// �������� ����� ����� ��� �������� �����
int _fastcall mfCreateFrameMap(MAPFRAMEDATA * data,
                               TMap * map, int list, long excodeframe,
                               TObjectInfo * objectinfo);

// �������� ����� ����� �� ������� ������
int _fastcall mfCreateFrameMapFour(MAPFRAMEDATA * data);

// �������� ����� ����� ��� �������-�������������� ����
int _fastcall mfCreateFrameMapGeog(MAPFRAMEDATA * data);

// �������� ����� ����� ��� ��������������� ����
int _fastcall mfCreateFrameMapTopo(MAPFRAMEDATA * data);

// �������� ����� ����� ��� ���� UTM �� North American Datum 1927
int _fastcall mfCreateFrameMapNAD27(MAPFRAMEDATA * data);     

// ������� ���������� ����� ����� � ���������� ����� ������� ������� �
// ��������. ���� ����� ������� ���, �� ���������� ����� �������� �������.
int _fastcall mfSetPointFrame(MAPFRAMEDATA * data);

//  ������ �����
int _fastcall mfAppendFrame(MAPFRAMEDATA * data);

// ��������� �� ������
int _fastcall mfMessage(MAPFRAMEDATA * data);


#ifdef __cplusplus

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++  �������� ��'���� "����� �����" ++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TMapFrame : public MAPFRAMEDATA
{
public:
enum {   // ���� ������ ��� �������� ����� �����
     IDC_MAPFRAME_RSC = 1,       // ������ �������� ��� ��������� RSC
     IDC_MAPFRAME_REGISTER = 2,  // ������ ����������� ����� �����
     IDC_MAPFRAME_SCALE    = 3,  // ������ � �������� ����� ��� ��������
     IDC_MAPFRAME_CREATE   = 4,  // ������ ��� ������������� ������� �����
     IDC_MAPFRAME_APPEND   = 5,  // ������ ��� ���������� �����
     IDC_MAPFRAME_DIST     = 6,  // ������ ��� �������� ������� �����
     IDC_MAPFRAME_STRUCT   = 7,  // ������ ��������� ������ �������
     IDC_MAPFRAME_KIND     = 8,  // ������ � ���� ����������� �����
     };

// ����������� ������
TMapFrame();

// ����������� � ��������� ����� � ������� ����� �����
TMapFrame(TMap * map,int list,long excodeframe,TObjectInfo * objectinfo);

// ����������� � ��������� �����
TMapFrame(TMap * map,int list,TObjectInfo * objectinfo);

// �������� ����� �����
int CreateFrameMap(TMap * map,int list,long excodeframe,TObjectInfo * objectinfo);

// ������ ����� �����
int AppendFrame();

// ��������� ������
int Error(int error) { Err = error; return Err; }
int Error() {return Err;}

private:

// �������� ����� ����� ��� ��������������� ����
int CreateFrameMapTopo();

// ����������� ���������� ����� ������� ��� ��������
int SetPointFrame();

// �������� ����� ����� ��� �������-�������������� ����
int CreateFrameMapGeog();

// �������� ����� �� ������� ������
int CreateFrameMapFour();

// ��������� �� ������
int Message();

};

#else

typedef  MAPFRAMEDATA  TMapFrame;

#endif  // __cplusplus

#endif
