
#if !defined(VECEXAPI_H)
#define VECEXAPI_H

#ifndef MAPAPI_H
  #include "mapapi.h"    // ��������� ������� ������������
#endif

#ifndef Mmstruct_H
  #include "mmstruct.h"      
#endif

#ifdef WIN32API
   #define HMESSAGE HWND
#else
   #define HMESSAGE MSGHANDLER
#endif

typedef struct INFOLIST {
  char Nomenclature[32];     // ������������
  long   Scale;              // �������
  long   CountObject;        // ���������� ��������
  int   Type;                // ��� �����
                  } INFOLIST;



typedef struct INFOSXF {
  char  SheetName[32];
  char  Nomenclature[32];
  long  RealCoordinate;
  long  Scale;
  long  RecordCount;
  long  MapType;
                  } INFOSXF;

typedef struct INFODIR {
  char  SheetName[32];
  char  NameRsc[MAX_PATH];
  long  CountList;
                  } INFODIR;

//#include "vecexdll.h"

extern "C"
{

//---------------------------------------------------------------------------
//  ����������� �������� �����
//   hMap,hSite - �������������� ����� (��.MAPAPI.H),
//   mode       - ����� ������ (0 - ��������, 1 - ��������������),
//   handle     - ������������� ���� ������� �������� ���������.
//
//  �������������� ���������� ��������� ��������� :
//  WM_LIST   = 0x586   WParam - ���������� ������ � ������
//                      LParam - ����� �������� �����
//  WM_OBJECT = 0x585   WParam - ������� ������������ ��������
//  WM_ERROR  = 0x587   WParam - ���������� ����� ������� ��� 0
//                      LParam = 1 - ������ � �����
//                             = 2 - ������ � ��������������
//                             = 3 - ������ � �������� �������
//                             = 4 - ������ � �������
//                             = 5 - ������ � ���������
//                             = 6 - ������ � �������
//  ���������� ���������� ������ � ������
//---------------------------------------------------------------------------

long int WINAPI _export mapStructControl(HMAP hMap,HSITE hSite,
                                         long mode,HMESSAGE handle);

//---------------------------------------------------------------------------
//       ���������� ���� ���� � ����������, �������� � ��������
//
//           mapdoc - ����������� ��������
//           handle - ������������� ���� ������� �������� ���������
//           mode   - ������ ��������� ����� (0 - ����������� ��� �����,
//                                            1 - ������ ���������������)
//                                  2 - ��������� ����� ������  

//---------------------------------------------------------------------------

long int _export WINAPI MapSortProcess(HMAP mapdoc,HMESSAGE handle,
                                       long int mode);


//========================================================================
//   ������� �������� �����
//========================================================================
//  �������������� ���������� ��������� ��������� :
//  WM_LIST   = 0x586   WParam - ���������� ������ � ������
//                      LParam - ����� �������� �����
//  WM_OBJECT = 0x585   WParam - ������� ������������ ��������
//  WM_INFOLIST = 0x584 LParam - ����� ��������� INFOLIST
// ----------------------------------------------------------------
// ��������� ����� �� ����� SXF
// ----------------------------------------------------------------

long int WINAPI _export LoadSxfToMap(char * namesxf,
                                     char * namemap,
                                     char * namersc,
                                     HMESSAGE handle);

// ----------------------------------------------------------------
// ��������� ����� �� ����� SXF � �������������� Select
// ----------------------------------------------------------------

long int WINAPI _export LoadSxfToMapSelect(char * namesxf,
                                           char * namemap,
                                           char * namersc,
                                           HMESSAGE handle,
                                           HSELECT select);

// ----------------------------------------------------------------
// ��������� ����� �� ����� SXF � �������������� Select 
// � ���������� ����� �����
// ----------------------------------------------------------------

long int WINAPI _export LoadSxfToMapSelectName(char * namesxf,
                                               char * namemap,
                                               char * namersc,
                                               HMESSAGE handle,
                                               HSELECT select,
                                               char * name,
                                               char * namehdr);

// ----------------------------------------------------------------
// ��������� ����� �� ����� TXT
// ----------------------------------------------------------------

long int WINAPI _export LoadTxtToMap(char * nametxt,
                                     char * namemap,
                                     char * namersc,
                                     HMESSAGE handle);

// ----------------------------------------------------------------
// ��������� ����� �� ����� TXT � ������������� Select
// ----------------------------------------------------------------

long int WINAPI _export LoadTxtToMapSelect(char * nametxt,
                                           char * namemap,
                                           char * namersc,
                                           HMESSAGE handle,
                                           HSELECT select);


// ----------------------------------------------------------------
// ��������� ����� �� ����� TXT � ������������� Select � ���������� �����
// ----------------------------------------------------------------

long int WINAPI _export LoadTxtToMapSelectName(char * nametxt,
                                               char * namemap,
                                               char * namersc,
                                               HMESSAGE handle,
                                               HSELECT select,
                                               char * name,
                                               char * namehdr);


// ----------------------------------------------------------------
// ��������� ����� �� ������ DIR
// ----------------------------------------------------------------

long int WINAPI _export LoadDirToMap(char* namedir,
                                     char* namemap,
                                     HMESSAGE handle);

// ----------------------------------------------------------------
// ��������� ����� �� ������ DIR � ��������������  Select
// ----------------------------------------------------------------

long int WINAPI _export LoadDirToMapSelect(char* namedir,
                                           char* namemap,
                                           HMESSAGE handle,
                                           HSELECT select);


// ----------------------------------------------------------------
// ��������� ����� �� ������ DIR � ��������������  Select � 
// ���������� ����� ������ � ����� ����� ��������
// ----------------------------------------------------------------

long int WINAPI _export LoadDirToMapSelectName(char* namedir,
                                               char* namemap,
                                               HMESSAGE handle,
                                               HSELECT select,
                                               char * name,
                                               char* namersc);


// ----------------------------------------------------------------
// ��������� ����� �� ������ �� ������� ������
// ----------------------------------------------------------------

long int WINAPI _export LoadMapToMap(HMAP  map,
                                     char * namemap,
                                     HMESSAGE handle);

// ----------------------------------------------------------------
// ��������� ����� �� ������ ������� ������ � ��������������  Select
// ----------------------------------------------------------------

long int WINAPI _export LoadMapToMapSelect(HMAP map,
                                           char* namemap,
                                           HMESSAGE handle,
                                           HSELECT select);


//========================================================================
//   ������� ���������� �����
//========================================================================

// ----------------------------------------------------------------
// �������� ����� �� ����� SXF
// ----------------------------------------------------------------

long int WINAPI _export UpdateMapFromSxf(char* namesxf,
                                         char* namemap,
                                         HMESSAGE handle);

// ----------------------------------------------------------------
// �������� ����� �� ����� SXF � �������������� Select
// ----------------------------------------------------------------

long int WINAPI _export UpdateMapFromSxfSelect(char* namesxf,
                                               char* namemap,
                                               HMESSAGE handle,
                                               HSELECT select);

// ----------------------------------------------------------------
// �������� ����� �� ������ ������� ������ � ��������������  Select
// ----------------------------------------------------------------

long int WINAPI _export UpdateMapToMapSelect(HMAP map,                
                                             const char* namemap,
                                             HMESSAGE handle,
                                             HSELECT select);

// ----------------------------------------------------------------
// �������� � ����� ������ �� ����� SXF � �������������� Select
// ----------------------------------------------------------------

long int WINAPI _export AppendMapFromSxfSelect(char* namesxf,
                                         char* namemap,
                                         HMESSAGE handle,
                                         HSELECT select);


// ----------------------------------------------------------------
// �������� ����� �� ����� TXT
// ----------------------------------------------------------------

long int WINAPI _export UpdateMapFromTxt(char* nametxt,
                                         char* namemap,
                                         HMESSAGE handle);

// ----------------------------------------------------------------
// �������� ����� �� ����� TXT � �������������� Select
// ----------------------------------------------------------------

long int WINAPI _export UpdateMapFromTxtSelect(char* nametxt,
                                         char* namemap,
                                         HMESSAGE handle,
                                         HSELECT select);


// ----------------------------------------------------------------
// �������� � ����� ������ �� ����� TXT � �������������� Select
// ----------------------------------------------------------------

long int WINAPI _export AppendMapFromTxtSelect(char* namesxf,
                                         char* namemap,
                                         HMESSAGE handle,
                                         HSELECT select);

// ----------------------------------------------------------------
// �������� ����� �� ����� DIR � �������������� Select
// ----------------------------------------------------------------

long int WINAPI _export UpdateMapFromDirSelect(char* namedir,
                                         char* namemap,
                                         HMESSAGE handle,
                                         HSELECT select);


// ----------------------------------------------------------------
// �������� � ����� ������ �� ����� DIR � �������������� Select
// ----------------------------------------------------------------

long int WINAPI _export AppendMapFromDirSelect(char* namedir,
                                         char* namemap,
                                         HMESSAGE handle,
                                         HSELECT select);

//========================================================================
//   ������� ���������� �����
//========================================================================
//  �������������� ���������� ��������� ��������� :
//  WM_LIST   = 0x586   WParam - ���������� ������ � ������
//                      LParam - ����� �������� �����
//  WM_OBJECT = 0x585   WParam - ������� ������������ ��������

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ SXF(Windows)
// ----------------------------------------------------------------

long int WINAPI _export SaveSxfFromMap(char * namemap,
                                       int list,
                                       char * namesxf,
                                       HMESSAGE handle);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ SXF(Windows) �
//          ��������������  Select
// ----------------------------------------------------------------

long int WINAPI _export SaveSxfFromMapSelect(char * namemap,
                                             int list,
                                             char * namesxf,
                                             HMESSAGE handle,
                                             HSELECT select,
                                             int flag = 0,
                                             char * nameregion = NULL);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ SXF(Windows) �
//          ��������������  Select
// ----------------------------------------------------------------

long int WINAPI _export SaveSxfFromHMapSelect(HMAP map,
                                             int list,
                                             char * namesxf,
                                             HMESSAGE handle,
                                             HSELECT select,
                                             int flag = 0,
                                             char * nameregion = NULL);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ SXF(DOS)
// ----------------------------------------------------------------

long int WINAPI _export SaveSxfDosFromMap(char * namemap,
                                          int list,
                                          char * namesxf,
                                          HMESSAGE handle);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ SXF(Dos) �
//          ��������������  Select
// ----------------------------------------------------------------

long int WINAPI _export SaveSxfDosFromMapSelect(char * namemap,
                                                int list,
                                                char * namesxf,
                                                HMESSAGE handle,
                                                HSELECT select,
                                                char * nameregion=NULL);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ SXF(Dos) �
//          ��������������  Select
// ----------------------------------------------------------------

long int WINAPI _export SaveSxfDosFromHMapSelect(HMAP map,
                                                int list,
                                                char * namesxf,
                                                HMESSAGE handle,
                                                HSELECT select,
                                                char * nameregion=NULL);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ TXT(XY)
// ----------------------------------------------------------------


long int WINAPI _export SaveTxtFromMap(char * namemap,
                                       int   list,
                                       char * nametxt,
                                       HMESSAGE handle);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ TXT(XY) �
//      �������������� Select
// ----------------------------------------------------------------

long int WINAPI _export SaveTxtFromMapSelect(char * namemap,
                                             int list,
                                             char * nametxt,
                                             HMESSAGE handle,
                                             HSELECT select,
                                             char * nameregion = NULL);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ TXT(XY) �
// �������������� Select
// namemap - ��� ����������� �����,
// list    - ����� �����,
// nametxt - ��� ����� TXF,
// handle  - ������������� ����, �������� ���������� ��������� � ���� ��������
//           (WM_INFOLIST, WM_OBJECT)
// nameregion - ��� ������ (�����)
// precision  - ����� ������ ����� ������� ��� ������������� ���������
// ----------------------------------------------------------------

long int WINAPI _export SaveTxtFromMapSelectEx(const char * namemap,
                                               long int list,
                                               const char * nametxt,
                                               HMESSAGE handle,
                                               HSELECT select,
                                               const char * nameregion,
                                               long int precision);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ TXT(BL)
// ----------------------------------------------------------------


long int WINAPI _export SaveTxtGeoFromMap(char * namemap,
                                          int list,
                                          char * nametxt,
                                          HMESSAGE handle);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ TXT(BL) �
//      �������������� Select
// ----------------------------------------------------------------

long int WINAPI _export SaveTxtGeoFromMapSelect(char * namemap,
                                                int list,
                                                char * nametxt,
                                                HMESSAGE handle,
                                                HSELECT select,
                                                char * nameregion = NULL);
long int WINAPI _export SaveTxtGeoGradFromMapSelect(char * namemap,
                                                int list,
                                                char * nametxt,
                                                HMESSAGE handle,
                                                HSELECT select,
                                                char * NameRegion = NULL);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ SXF(WINDOWS) �� DIR
// ----------------------------------------------------------------

long int WINAPI _export SaveDirSxfFromMap(char* namemap,
                                     char* namedir,
                                     HMESSAGE handle);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ SXF(WINDOWS) �� DIR
//   � �������������� Select
// ----------------------------------------------------------------

long int WINAPI _export SaveDirSxfFromMapSelect(char* namemap,
                                     char* namedir,
                                     HMESSAGE handle,
                                     HSELECT select);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ SXF(WINDOWS) �� DIR
//   � �������������� Select
// ----------------------------------------------------------------

long int WINAPI _export SaveDirSxfIntFromMapSelect(char* namemap,
                                     char* namedir,
                                     HMESSAGE handle,
                                     HSELECT select);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ SXF(DOS) �� DIR
// ----------------------------------------------------------------

long int WINAPI _export SaveDirSxfDosFromMap(char* namemap,
                                     char* namedir,
                                     HMESSAGE handle);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ SXF(DOS) �� DIR
//   � �������������� Select
// ----------------------------------------------------------------

long int WINAPI _export SaveDirSxfDosFromMapSelect(char* namemap,
                                     char* namedir,
                                     HMESSAGE handle,
                                     HSELECT select);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ TXT(XY) �� DIR
// ----------------------------------------------------------------

long int WINAPI _export SaveDirTxtFromMap(char* namemap,
                                     char* namedir,
                                     HMESSAGE handle);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ TXT(XY) �� DIR
//   � �������������� Select
// ----------------------------------------------------------------

long int WINAPI _export SaveDirTxtFromMapSelect(char* namemap,
                                     char* namedir,
                                     HMESSAGE handle,
                                     HSELECT select);
// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ TXT(BL) �� DIR
// ----------------------------------------------------------------

long int WINAPI _export SaveDirTxtGeoFromMap(char* namemap,
                                     char* namedir,
                                     HMESSAGE handle);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ TXT(BL) �� DIR
//   � �������������� Select
// ----------------------------------------------------------------

long int WINAPI _export SaveDirTxtGeoFromMapSelect(char* namemap,
                                     char* namedir,
                                     HMESSAGE handle,
                                     HSELECT select);

// ----------------------------------------------------------------
// �������� �� ����������� ������� � ������ TXT(BL �������) �� DIR
//   � �������������� Select
// ----------------------------------------------------------------

long int WINAPI _export SaveDirTxtGeoGradFromMapSelect(char* namemap,
                                     char* namedir,
                                     HMESSAGE handle,
                                     HSELECT select);

// ----------------------------------------------------------------
//   ����������������� ������ �� ������
// ----------------------------------------------------------------

int WINAPI _export TransVector(HOBJ FrameReal , HOBJ FrameTeor);

//-------------------------------------------------------------------
//  ��������� ���������� ���������� � ����� �� SXF
// ------------------------------------------------------------------
long int _MAPAPI _export GetInfoSxf(char * namesxf,
                                  INFOSXF * infosxf);

//-------------------------------------------------------------------
//  ��������� ���������� ���������� �� DIR
// ------------------------------------------------------------------
long int _MAPAPI _export GetInfoDir(char * namedir,
                                  INFODIR * infodir);

// ------------------------------------------------------------------
// ��������� ������ ������ SXF � DIR
// ------------------------------------------------------------------
long int _MAPAPI _export GetDir(char * namedir,
                                NAMESARRAY * sxfdir, long int length);

// ------------------------------------------------------------------
// ��������� ���������� ������ ��������� �����
// �� ����� ����� SXF
// ��������� MAPREGISTER � LISTREGISTER ������� � mapcreat.h
// ��� ������ ���������� ����
// ------------------------------------------------------------------
long int _MAPAPI mapGetSxfInfoByName(const char * name,        
                                     MAPREGISTER * map,
                                     LISTREGISTER * sheet);

}       // extern "C"

#endif  // VECEXAPI_H


