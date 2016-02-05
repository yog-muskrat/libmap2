
#ifndef MAPPROJ_H
#define MAPPROJ_H

#ifdef __cplusplus

#ifndef MAPACCES_H
  #include "mapacces.h"
#endif


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ����� : ������ ����������� ����� +++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TMapProject
{
  public :

  TMapProject();
  ~TMapProject();

  // ������� ������ � ���������������� ��� ������
  // mapproject - ������ ��� ����� �������
  // ��� ������ ���������� ����
  int _fastcall OpenProject(TMapAccess * mapaccess,
                            const char * mapproject);

  // �������� ������ � ���������������� ��� ������  
  // mapproject - ������ ��� ����� �������
  // ��� ������ ���������� ����
  int _fastcall AppendProject(TMapAccess * mapaccess,
                              const char * mapproject);

  // ��������� ������ ����������� ����� � �������
  // mapproject - ������ ��� ����� �������
  // ��� ������ ���������� ����
  int _fastcall SaveProject(TMapAccess * mapaccess,
                            const char * mapproject);

  // ���������� ������������ ������ [MAP]
  // ��� ������ ���������� ����
  int _fastcall OpenMainMap(TMapAccess * mapaccess,
                            const char * mapproject);

  // ���������� ������������ ������ [MAP]   
  // ��� ������ ���������� ����
  int _fastcall AppendMainMap(TMapAccess * mapaccess,
                              const char * mapproject);

  // ���������� ������ [RSTLIST]
  // ��� ������ ���������� ����
  int _fastcall OpenRstList(TMapAccess * mapaccess,
                            const char * mapproject);

  // ���������� ������ [MTRLIST]
  // ��� ������ ���������� ����
  int _fastcall OpenMtrList(TMapAccess * mapaccess,
                            const char * mapproject);

  // ���������� ������ [MTLLIST]
  // ��� ������ ���������� ����
  int _fastcall OpenMtlList(TMapAccess * mapaccess,
                            const char * mapproject);

  // ���������� ������ [TINLIST]
  // ��� ������ ���������� ����
  int _fastcall OpenTinList(TMapAccess * mapaccess,      
                            const char * mapproject);
                            
  // ���������� ������ [SITELIST]
  // ��� ������ ���������� ����
  int _fastcall OpenSiteList(TMapAccess * mapaccess,
                             const char * mapproject);

  // ���������� ������������ ������ [MAP]
  // ��� ������ ���������� ����
  int _fastcall SaveMainMap(TMapAccess * mapaccess,
                            const char * mapproject);

  // ���������� ������ [RSTLIST]
  // ��� ������ ���������� ����
  int _fastcall SaveRstList(TMapAccess * mapaccess,
                            const char * mapproject);

  // ���������� ������ [MTRLIST]
  // ��� ������ ���������� ����
  int _fastcall SaveMtrList(TMapAccess * mapaccess,
                            const char * mapproject);

  // ���������� ������ [MTLLIST]
  // ��� ������ ���������� ����
  int _fastcall SaveMtlList(TMapAccess * mapaccess,
                            const char * mapproject);

  // ���������� ������ [TINLIST]
  // ��� ������ ���������� ����
  int _fastcall SaveTinList(TMapAccess * mapaccess,      
                            const char * mapproject);

  // ���������� ������ [SITELIST]
  // ��� ������ ���������� ����
  int _fastcall SaveSiteList(TMapAccess * mapaccess,
                             const char * mapproject);

#ifndef HIDEMTQ        

  // ���������� ������ [MTQLIST]
  // ��� ������ ���������� ����
  int _fastcall OpenMtqList(TMapAccess * mapaccess,
                            const char * mapproject);

  // ���������� ������ [MTQLIST]
  // ��� ������ ���������� ����
  int _fastcall SaveMtqList(TMapAccess * mapaccess,
                            const char * mapproject);

#endif // LINUXAPI

protected :

  // ��������� ������� �� ������� ������
  // ��� ������ ���������� ����
  int _fastcall LoadPalette(TBaseColors * colors,
                            char * palette);

  // ��������� ������� �� ������� ������
  // ��� ������ ���������� ����
  int _fastcall SavePalette(TBaseColors * colors,
                            char * palette, int size);
};

#endif  // __cplusplus

#endif  // MAPPROJ_H

