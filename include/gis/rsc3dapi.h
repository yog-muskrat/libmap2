
#ifndef RSC3DAPI_H
#define RSC3DAPI_H

#ifndef RSCFL3D_H
   #include "rscfl3d.h"
#endif

#ifndef RSCAPI_H
   #include "rscapi.h"
#endif

typedef struct LEVELIMAGE
{
  long CodeLib0;          // ��� ���������� ��� ����������� 0 ������(��������)
  long Key0;              // ���� ����������� ��� 0 ������
  long CodeLib1;          // ��� ���������� ��� ����������� 1 ������(��������)
  long Key1;              // ���� ����������� ��� 1 ������
  long CodeLib2;          // ��� ���������� ��� ����������� 2 ������(��������)
  long Key2;              // ���� ����������� ��� 2 ������
  long Incode;            // ���������� ��� �������
  char Flag0;             // ���� �������������� ��� 0 ������
  char Flag1;             // ���� �������������� ��� 1 ������
  char Flag2;             // ���� �������������� ��� 2 ������
  char Rezerv;            // ������
}
  LEVELIMAGE ;


 // ����� ������� �������������� 3D �������� ��������������
 void Get3DLib(void * owner,LEVELIMAGE * levels,HMAP hmap,HRSC hrsc,long * ret);
 // ����� ������� ��������� ������� ���  ������ BMP
 long int Get3DDemo(HWND handle,HMAP hmap,HRSC hrsc,char * bmpname,
                     RECTEXTURE * tex, int enterflag);

extern "C"
{

 // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 // +++++ �������� ������� ������� � 3D ������������    +++++
 // +++++      � 3D ����������  ��'�����                +++++
 // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 // ���������������� 3D �������
 // hRsc - ������������� �������������� �����
 // ��� ������ ���������� 0

 long int WINAPI mapInitRsc3D(HRSC hRsc);

 // ������ 3D ���������� ������� �� ������ (0,1,2 - ��� 0 - �������)
 // � ����������� ������ (������� ) ������� � 1
 // ��� ���������� ���������� ������������ ������ �������� ���������
 // �������� ������
 // ��� ������ ��� ���������� 0

 const char * WINAPI mapGetRsc3DParam(HRSC hRsc,long int incode,
                                      long int level);

 // ������ 3D ���������� ������� �� ������ (0,1,2 - ��� 0 - �������)
 // � ����������� ������ (������� ) ������� � 1
 // ��� ������ ��� ���������� ���������� ��������� ������ ���������� 0.

 const char * WINAPI mapIsRsc3DParam(HRSC hRsc, long int incode,
                                          long int level);

 // ��������� ����� ���������� ������� ���������� ����
 // (OBJECT_PARAMETERS,OBJECT_TEXTURE ...  rscfl3d.h)
 // � ���������� � ����� code
 // ��� ������ ��� ���������� 0

 long int WINAPI mapTakeRscRecordCount(HRSC hRsc, long int code, long int type);

 // ��������� ��������� ������ ���������� ����
 // ( ��� - OBJECT_PARAMETERS,OBJECT_TEXTURE ...  rscfl3d.h)
 // �� ����������� ������
 // � ���������� c ������ �����
 // ���������� ��� ������, ��� ������ 0.

 long int WINAPI mapTakeRscRecordHead(HRSC hRsc, long int number, long int code,
                                     long int type, RECHEAD * address);

 // ��������� ��������� ������  �� ����
 // ���������� ������, ��� ������ 0.

 RECHEAD * WINAPI mapTakeRscCodeRecordHead(HRSC hRsc,long int code);

 // ��������� ��������� ������ ���������� ���� �� ���� ���������� � �����
 // ���������� ������, ��� ������ 0.                  

 RECHEAD * WINAPI mapTakeRscKeyRecordHead(HRSC hRsc,long int code,long int key);

 // ��������� ����� �������� �� ����������� ������ (c 1)
 // ��� ������ ���������� 0.

 RECTEXTURE * WINAPI mapTakeRscTexture(HRSC hRsc,long int number);

 // ������� ��������� 3D �����������
 // �� ���� ����������,���� �������,��������� ��������,
 // ����� ���������� � ���������� (���� F3DTREE)
 // ��� ������ ��� ���������� ���������� 0 , ����� ��� �����������

 long int WINAPI mapCreateRsc3DImage(HRSC hRsc, long int code, long int type,
                                     long int length, char * param,char * name);

 // ������ ���������� 3D �����������
 // � ���� ���������� � ����� �����������.
 // ��� ������ ��� ���������� 0
 // ����� ����� ���������� ����������� (� ���� F3DTREE mapgdi3d.h )

 char * WINAPI mapGetRsc3DImageParam(HRSC hRsc, long int code, long int key);

 // ���������� ��������� 3D �����������
 // �� ���� ����������,����� ����������� ,���� ������� (0, 1 ... rscfl3d.h),
 // ����� ���������� � ���������� (� ���� F3DTREE mapgdi3d.h )
 // ��� ������ ��� ���������� ���������� 0, ����� ��� ������

 long int WINAPI mapSetRsc3DImageParam(HRSC hRsc,long int code,
                                  long int key,long int type,long int length,
                                  char * param);

 // �������� �������� 3D �����������
 // �� ���� ����������,����� �����������
 // ��� ������ ��� ���������� ���������� 0

 long int WINAPI mapSetRsc3DImageName(HRSC hRsc,long int code,
                                               long int key, char * name);

 // ������� ������ �� ������ (0,1,2 - ��� 0 - �������)
 // � ����������� ������ (������� ) ������� � 1
 // � ������������ �� ���� ���������� � ����� �������.
 // ��� ������ ���������� 0.

 long int WINAPI mapSetRsc3DImageToObject(HRSC hRsc, long int incode,
                                   long int level, long int code, long int key);

 // ������ ����� ����������� ���������� �������
 // �� ������ (0,1,2 - ��� 0 - �������)
 // � ����������� ������ (������� ) ������� � 1
 // ��� ������ ��� ���������� ���������� 0

 long int WINAPI mapGetRsc3DObjectKey(HRSC hRsc,long int incode,long int level);

 // ������ 3D ����������� ������� �� ������ (0,1,2 - ��� 0 - �������)
 // � ����������� ������ (������� ) ������� � 1
 // ��� ������ 0                                                     

 long int WINAPI mapDeleteRsc3DImageFromObject(HRSC hRsc,long int incode,
                                                        long int level);

 // ��������� ����� ���������� ��������� �� ������ � ������� ������� (c 1)
 // ��� ������ 0.                                                  
 ACT3DMATERIALMODE * WINAPI mapTakeRsc3DMaterial(HRSC hRsc,long int number);

 // �������� ��������� ��������� �� ���� ���������� � ����� ���������
 // ��� ������ 0, ����� ��� ������ ���������
 long WINAPI mapReplaceRsc3DMaterial(HRSC hRsc,long int libcode,long int key,
                          ACT3DMATERIALMODE * material);           

 // ������� ��������� ��������� �� ���� ���������� � �����
 // ��� ������ 0, ����� ��� ������ ���������                       
 long WINAPI mapDeleteRsc3DMaterial(HRSC hRsc,long int libcode,long int key);

 // �������� �������� ��������� �� ���� ���������� � �����
 // (�������� ��������� ��� ������ ����������)
 // ��� ������ 0
 long WINAPI mapReplaceRsc3DMaterialName(HRSC hRsc,long int libcode,long int key,
                          char * name);                              

 // ������� ������ ��������� �� ���� ����������, ���������� ��������� �
 // �������� (�������� ��������� ��� ������ ����������)
 // ��� ������ 0 ����� ��� ������ ���������
 long WINAPI mapCreateRsc3DMaterial(HRSC hRsc,long int libcode,    
                                    ACT3DMATERIALMODE * material,char * name);

 // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 // +++ �������� ������� ������� � ����������� 3D ��'����� ++
 // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 // ������ ����� ���������� ���������� ���������� �� ����
 // ��� ������ ���������� ������ ������.

 const char * WINAPI mapGetRsc3DLibraryName(HRSC hRsc,long int code);

 // ������ ���������� ��������� ���������� ����������
 // ��� ������ ���������� 0.

 long int WINAPI mapGetRsc3DLibraryCount(HRSC hRsc);

 // ������ ���� ���������� �� ����������� ������ ���������� 3D ���������� (c 1)
 // ��� ������ ���������� 0.

 long int WINAPI mapGetRsc3DLibraryCode(HRSC hRsc,long int number);

 // ������ ������� ��������(���� ������  � ���� ������) ���������
 // ��� ������ ���������� 0.

 long int WINAPI mapIsActive3DLibrary(HRSC hRsc);



} // extern "C"

#endif