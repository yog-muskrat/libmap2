
//---------------------------------------------------------------------------
#ifndef GISFORMS_H
#define GISFORMS_H

#ifndef MAPAPI_H
  #include "mapapi.h"
#endif

#ifndef LISTAPI_H
  #include "listapi.h"
#endif

#ifndef PICTRAPI_H
  #include "pictrapi.h"
#endif

#ifndef MEDAPI_H
  #include "medapi.h"
#endif

#ifndef PRNAPI_H
  #include "prnapi.h"
#endif

#ifndef Mmstruct_H
  #include "mmstruct.h"      
#endif


#ifdef TEST
extern "C"
{
 //            ������ "������ ������ ����������� �����"
 // �������� ������� "������ ������ ����������� �����" �� ����������
 // ������ �������� :
 //            �������� "������ �������",
 //            �������� "������ ������",
 //            �������� "������ ���������������� ����"
 // � �������� ������� � ������� ��� ������ � ����������, ����������
 // � ����������������� �������.
 // ��� ������ ���������� ����
 //
 // ��� ��������� ��������� ������(����������/�������� ����)
 // �� ������� "������ ������ ����������� �����" ����������
 // ���� ��������� (maplistparm->Window) ���������:
 //    -  WM_MOVEDOC(0x601) ����������� ������� ����� � �������� ������
 //               � ������ ����.
 //       WPARAM - ��������� �� �������� ����� ���� DOUBLEPOINT
 //       ���������� ����� � ������� ����������� � ��������
 //
 //    -  MT_CHANGEDATA(0x65D) ��������� �� ��������� ������� ������
 //       WPARAM,LPARAM �� ������������.

 // ������ ������ !!!
 // ���� ������������ #define BUILD_DATALIST, ��:
 //     ��� ��������� ��������� ������(����������/�������� ����)
 //     �� ������� "������ ������ ����������� �����" ����������
 //     ���� ��������� (maplistparm->Window) ���������:
 //       -  (0x827) ����������� ������� ����� � �������� ������
 //               � ������ ����.
 //       WPARAM - ��������� �� �������� ����� ���� DOUBLEPOINT
 //       ���������� ����� � ������� ����������� � ��������
 //
 //       -  (0x82E) ��������� �� ��������� ������� ������
 //       WPARAM,LPARAM �� ������������.

 //     ��� ����������� ��������������� ������� ������������ ����
 //     ������� "������ ������ ����������� �����",
 //     �� ������� "������ ������ ����������� �����" ����������
 //     ���� ��������� (maplistparm->Window) ���������:
 //       -  (0x620)  ��������� �� ������ ���� "���������������� �� ����� �����"
 //       -  (0x621)  ��������� �� ������ ���� "���������������� �� ���� ������"
 //       -  (0x622)  ��������� �� ������ ���� "���������� ����� �� ��������� �������"
 //       -  (0x623)  ��������� �� ������ ���� "���������� ����� �� ���������� �������"

 long int _export WINAPI  LoadMapListDialog(HMAP hMap,
                                            MAPLISTPARM* maplistparm,
                                            TASKPARM* parm);

 // --------------------------------------------------------------
 // �������� ������� "���������� ��������"
 // ������ �������� :
 // - �������� "���������� ��������� ��������"
 //  (��������� ����� ���� �����, ����� ���������� �������,
 //   ����� ���������� ��������,������� ����� ���������
 //   ���������� ��� ����������� �������);
 // - �������� "���������� �������� �����";
 // - �������� "���������� �������� �������";
 // - �������� "���������� �������� ������".
 //
 // ����� ��������� ���������� ������� � ��������� paletteParm
 // ����������� ������������� � ������� "���������� ��������"
 // ��������: ����� ��������� ��������, ����� ���������� ��������,
 //           ������� ����� ��������� ��������
 //
 // ��� ������ ���������� ����
 // --------------------------------------------------------------
 long int _export WINAPI  LoadPaletteControl(HMAP hMap,
                                             PALETTECNTPARM* paletteParm,
                                             TASKPARM* parm);

 // --------------------------------------------------------------
 // �������� ������� "���������� ��������" � ������������ ����������� ��������
 // ������ �������� :
 // - �������� "���������� ��������� ��������"
 //  (��������� ����� ���� �����, ����� ���������� �������,
 //   ����� ���������� ��������,������� ����� ���������
 //   ���������� ��� ����������� �������);
 // - �������� "���������� �������� �����";
 // - �������� "���������� �������� �������";
 // - �������� "���������� �������� ������".
 // ��������� PALETTECNTPARM  � TASKPARM ������� � maptype.h
 // pageNumber - ����� �������� �������� ��� �������� ������� "���������� ��������"
 //              0 - �������������� �������� "���������� ��������� ��������"
 //                   (��������� ����� ���� �����, ����� ���������� �������,
 //                   ����� ���������� ��������,������� ����� ���������
 //                   ���������� ��� ����������� �������);
 //              1 - �������������� �������� "���������� �������� �����";
 //              2 - �������������� �������� "���������� �������� �������";
 //              3 - �������������� �������� "���������� �������� ������".
 // number - ����� ��������� ����� (������, �������, ��) � ������� ��������
 //          ���� number == 0, �� �������������� �������� "���������� ��������� ��������"
 //          ���������� ���������� �����. �� ����� 0.
 //          � �������� "���������� �������� �������" �� ������������.
 // ��� ������ ���������� ����
 // --------------------------------------------------------------
 long int _export WINAPI  LoadPaletteControlEx(HMAP hMap,
                                               PALETTECNTPARM* paletteParm,
                                               TASKPARM* parm,
                                               long int pageNumber,
                                               long int number);


// --------------------------------------------------------------
// �������� ������� "������� ���������"
// ��� ������ ���������� ����
// --------------------------------------------------------------
 long int _export WINAPI  LoadDialogScaleView(HMAP hMap, HWND handle, TASKPARM * parm,
                                              long int * topScale, long int * bottomScale,
                                              char* title);

// --------------------------------------------------------------
// �������� ������������ �����������(BMP,PCX,TIFF, GeoTIFF) � ��������� ������ (RSW)
// ������ ����������� ������������� �������� �������� ������������
// ����������� � ��������� ������ (RSW)
//    map - �����,���������� ��������� ������;
//    lpszsource - ��� ����� ��������� BMP,PCX,TIFF,GeoTIFF (������ ������� 260 ����);
//    lpsztarget - ������� ��� ����� ����� ���������� ������� (������ ������� 260 ����);
//    ��� ������ ���������� ����
// --------------------------------------------------------------
 long int WINAPI _export LoadImageToRstEx(HMAP hmap,
                                          char* lpszsource,
                                          char* lpsztarget,
                                          TASKPARM* parm);


// --------------------------------------------------------------
// ������ "������������� ������� ������"
// ����������� ������:
//           ������� ����������� ��������� ����� �� 90 ��������,
//           ������� ����������� ��������� ����� �� 180 ��������,
//           ������� ����������� ��������� ����� �� 270 ��������,
//           ���������� ������� ����������� ��������� �����(������������ ������������ ���),
//           ���������� ������� ����������� ��������� �����(������������ �������������� ���).
//    hmap   -  ������������� �������� ��������� �����
//    handle -  ������������� ���� ���������
//    reDraw -  ���� ����������� ���� ��������� �� ���������� ��������
//    name   - ��� ����� ��������� ����� (������ ������� 260 ����);
//    ��� ������ ���������� ����
// --------------------------------------------------------------
long int WINAPI _export LoadRstMirrorDialogEx(HMAP hmap, HWND handle,
                                              char* name, TASKPARM* parm,
                                              int * reDraw);

// --------------------------------------------------------------
// ������ "����������� ��������� �����"
// ����������� ������: ����������\������������ ����� ��������� �����,
//                     ����������� ����� ��������� �����.
//    map    - �����,���������� ��������� ������;
//    handle -  ������������� ���� ���������
//    name   - ��� ����� ��������� �����
//    reDraw -  ���� ����������� ���� ��������� �� ���������� ��������
//    ��� ������ ���������� ����
// --------------------------------------------------------------
long int WINAPI _export LoadRstCompressDialog(HMAP hmap, HWND handle,
                                              char* name,
                                              TASKPARM* parm, int* reDraw);

// --------------------------------------------------------------
// ������ ������ ���� ������� �� ����� ��������
// hmap - ������������� �������� ��������� �����
// hobj - ������������� �������
// choiceparm - ��������� ��� ������� ������ ���� �������
// name - ��������� �������
// ���������� ���������� ��� �������, hobj �������������
// ��������� ����� � ���� �������
// ��� ������ ��� ������ ���������� 0

// ��� ������ ������ � �������� ���������� � ���������
// TASKPARM ���������� ���� � ����� *.hlp, �������
// �������� ����� � ��������������� "6300"
// --------------------------------------------------------------
long int _export WINAPI medChoiceTypeObjectParm(HMAP hmap, TASKPARM *taskparm,
                                                HOBJ hobj, CHOICEOBJECTPARM *choiceparm,
                                                char *name);

// --------------------------------------------------------------
// ��������� �������
// --------------------------------------------------------------
HPRINTER _export WINAPI prnLoadPrinter();

// --------------------------------------------------------------
// ������ �����
//  hmap      - ������������� �����
//  printer   - ������������� ���������� ������
//  printparm - ��������� ������� ������ ����� (���� Length ������
//              ��������� ������ ���������)
//  taskparm  - ��������� ������ (���� Handle ������ ���������
//              ������������� �������� ����)
//  title     - ��������� �������
// ��� ������ ���������� 0
// --------------------------------------------------------------
long int _export WINAPI prnMapPrintTitle(HMAP hmap, HPRINTER printer,
                                         MAPPRINTPARM* printparm,
                                         TASKPARM* taskparm, char* title);
// --------------------------------------------------------------
// ���������� �������
// --------------------------------------------------------------
void _export WINAPI prnFreePrinter(HPRINTER printer);

// **************************************************************
// ������� ������ � ���������� ����������� � ������ �����
// **************************************************************

// --------------------------------------------------------------
// ������ "���������� ������ ����������� �������� �����"
// hmap    - ������������� �������� �������� �����
// parm    - ��������� ������ (��. maptype.h)
// note    - ����� ����������,������������ ��� ���� � ����������
//           ������ �������� �������� ��� ������ ��������� �������
//           (��������� note = 0).
// ���� ������ ���������, ���������� ��������� ��������
// --------------------------------------------------------------
long int _export WINAPI selSetViewStaff(HMAP hmap,
                                        TASKPARM* parm,
                                        long int* note);

// --------------------------------------------------------------
// ������ "���������� ������ ����������� �������� �����"
// hmap    - ������������� �������� �������� �����
// parm    - ��������� ������ (��. maptype.h)
// note    - ����� ����������,������������ ��� ���� � ����������
//           ������ �������� �������� ��� ������ ��������� �������
//           (��������� note = 0).
// restmode- ���� �������������� ��������� ����������� ����� :
//           "-1" - ���������� ������������ �������� �����������;
//           "0"  - ������������ ������� ��������� ��������� �����������.
// ���� ������ ���������, ���������� ��������� ��������
// --------------------------------------------------------------
long int _export WINAPI selSetViewStaffEx(HMAP hmap, TASKPARM* parm,
                                          long int* note,
                                          long int restmode);

// --------------------------------------------------------------
// ������ "���������� ������ ������ �������� �����"
// ������ ������ �������� ����� ������������� �����������������/������������
// � ��������� ����� ��� ������/���������� ���������.
// hmap - ������������� �������� ��������� �����
// note - ����� ����������,������������ ��� ���� � ����������
//        ������ �������� �������� ��� ������ ��������� �������
//       (��������� note = 0).
// ����������: "1" - ������ ����� ������ ��������;
//             "2" - ������ ����� ��������� �������� �����;
//             "0" - ������ ��� �����.
// --------------------------------------------------------------
 long int _export WINAPI selSetObjectsSearch(HMAP hmap,
                                             TASKPARM* parm,
                                             long int* note);

// --------------------------------------------------------------
// ������ "���������� ������ ������ �������� �����" (�����������)
// ������ ������ �������� ����� ������������� �����������������/������������
// � ��������� ����� ��� ������/���������� ���������.
// ��� ��������� ����������� �������� �������������� ������� ������
// ������������ ��������� RESTOREMODE (��. mmstruct.h).
// hmap    - ������������� �������� ��������� �����;
// parm    - ��������� ������ (��. maptype.h);
// resmode - ��������� �������������� ������� ������.
// ����������: "1" - ������ ����� ������ ��������;
//             "2" - ������ ����� ��������� �������� �����;
//             "0" - ������ ��� �����.
// --------------------------------------------------------------
long int _export WINAPI selSetObjectsSearchEx(HMAP hmap,
                                              TASKPARM* parm,
                                              RESTOREMODE* resmode);

// --------------------------------------------------------------
// ������������ ��������� (������) ����������� �������� �����
// hmap - ������������� �������� ��������� �����
// ��� ������ ���������� ����
// --------------------------------------------------------------
 long int _export WINAPI selRestoreSelect(HMAP hmap);

// --------------------------------------------------------------
// ��������� ��������� (������) ����������� �������� �����
// hmap - ������������� �������� ��������� �����
// ��� ������ ���������� ����
// --------------------------------------------------------------
 long int _export WINAPI selSaveSelect(HMAP hmap);

// --------------------------------------------------------------
// ������ ������ �� �������������� ����� ������������� ��������������
// hrsc - ������������� �������������� �������� �����;
// parm - ��������� ������ (��. maptype.h).
// ��� �������� ���������� ���������� ��� ��������� ���������,
// ����� - "-1".
// --------------------------------------------------------------
long int _export WINAPI selSemanticSelect(HRSC hrsc, TASKPARM* parm);

// --------------------------------------------------------------
// ������ ������ �� �������������� ����� �������������
// �������������� c ����������������� ����� ���������.
// hrsc - ������������� �������������� �������� �����;
// parm - ��������� ������ (��. maptype.h);
// code - ����������������� �������� ���� ��������������
//       (��� �������� ����� ������ ��� �������������� ����� ������).
// ��� �������� ���������� ���������� ��� ��������� ���������,
// ����� - "-1".
// --------------------------------------------------------------
long int _export WINAPI selSemanticSelectInit(HRSC hrsc, TASKPARM* parm, long int code);

// --------------------------------------------------------------
// ������ ������ �� �������������� ����� �������������
// �������������� �� ������� ��������.
// hrsc   - ������������� �������������� �������� �����;
// parm   - ��������� ������ (��. maptype.h);
// filter - ������ ����� �������� ��� ������ (������);
// count  - ���������� ��������� � ������� filter.
// ��� �������� ���������� ���������� ��� ��������� ���������,
// ����� - "-1".
// --------------------------------------------------------------
long int _export WINAPI selSemanticSelectFilter(HRSC hrsc,TASKPARM* parm,
						long int *filter,
						long int count);

// --------------------------------------------------------------
// ������ ������ �� �������������� ����� �������������
// �������������� �� ������� �������� c ����������������� ����� ���������.
// hrsc   - ������������� �������������� �������� �����;
// parm   - ��������� ������ (��. maptype.h);
// code   - ����������������� �������� ���� ��������������
//          (��� �������� ����� ������ ��� �������������� ����� ������);
// filter - ������ ����� �������� ��� ������ (������);
// count  - ���������� ��������� � ������� filter.
// ��� �������� ���������� ���������� ��� ��������� ���������,
// ����� - "-1".
// --------------------------------------------------------------
long int _export WINAPI selSemanticSelectFilterInit(HRSC hrsc, TASKPARM* parm,
						long int code,
						long int *filter,
						long int count);

// --------------------------------------------------------------
// ���������� ������ ����� �����
// hwnd      - ������������� ������������� ����;
// hrsc      - ������������� �������������� �������� �����;
// hselect   - ������������� ��������� ������ ����� (������);
// title     - ��������� ����� ������� ����� �����;
// hinstance - ������������� ���������� (dll) �������� ����� �������.
// --------------------------------------------------------------
long int _export WINAPI selSetLayersFilter(HWND hwnd, HRSC hrsc,
                    			HSELECT hselect, char *title,
                                	HINSTANCE hinstance);


// --------------------------------------------------------------
// ���������� ������ �������� �����
// � ��������� ������� HSELECT ������ ���� ����������� �����.
// title - ��������� ���� ������� �������� �����,
// ���� == 0, ��������������� ����������� ���������.
// ��� hmap != 0 ������ �����, ����������� � �������� � ������� �������
// ����������� � ������������ � ����������� �������� �������� �����
// (������ �. �. ������, ��� � RSC !),
// ����� - �� �������������� �������� ����� (������ ������)
// ���� ������ ���������, ���������� ��������� ��������
// --------------------------------------------------------------
long int _export WINAPI selSetFilterTitle(TASKPARM* parm, HSELECT hselect,
                                          HMAP hmap, char * title);


// --------------------------------------------------------------
// ���������� ������� ������ �������� ����� �� �������� ���������
// hmap    - ������������� �������� ��������� �����;
// hselect - ������������� ��������� ������ ����� (������);
// arname  - ������� ������ �� �������� (��. mmstruct.h)
// parm   - ��������� ������ (��. maptype.h);
// --------------------------------------------------------------
long int _export WINAPI selSearchName(HMAP hmap, HSELECT hselect,
                                      ARRAYNAME*  arname, TASKPARM* parm);

// **************************************************************
// ������� ������ ���� �������
// **************************************************************

// --------------------------------------------------------------
// ������ ������ ���� ������� �� ����� ��������
// hmap - ������������� �������� ��������� �����
// hobj - ������������� �������
// choiceparm - ��������� ��� ������� ������ ���� �������
// name - ��������� �������
// ���������� ���������� ��� �������
// ��� ������ ��� ������ ���������� 0
// --------------------------------------------------------------

 long int _export WINAPI medChoiceTypeObjectParm
                        (HMAP hmap, TASKPARM *taskparm,
                         HOBJ hobj, CHOICEOBJECTPARM *choiceparm,
                         char *name);

// --------------------------------------------------------------
// ������� ��� ������� �� ����� ��������
// hmap - ������������� �������� ��������� �����
// hobj - ������������� �������
// ���������� ���������� ��� �������
// ��� ������ ��� ������ ���������� 0
// --------------------------------------------------------------

long int _export WINAPI medChoiceTypeObject(HMAP hmap,
                                            TASKPARM *taskparm,
                                            HOBJ hobj);

// --------------------------------------------------------------
// ������� ��� ������� �� ����� ��������, ��������� ������
// hmap - ������������� �������� ��������� �����
// hobj - ������������� �������
// hselect - ������
//           (���� hselect == 0 - ������ �� ������������)
//            ���� hselect != 0 � � hselect �����������
//            �����, �� ������ �������� �� ����� �����.
//            ���� � hselect ����� �� �����������, ������
//            �������� �� ���� ������ ���������.
// name - ��������� �������
// ���������� ���������� ��� �������
// ��� ������ ��� ������ ���������� 0
// --------------------------------------------------------------
long int _export WINAPI medChoiceTypeObjectSelect
                       (HMAP hmap, TASKPARM *taskparm,
                        HOBJ hobj, HSELECT hselect,
                        char *name);

// --------------------------------------------------------------
//  ������� ����������� �������� ������
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
// --------------------------------------------------------------
long int _export WINAPI medChoiceLineImage
                       (HMAP hmap,TASKPARM *taskparm,
                        HOBJ object, HSELECT hselect,
                        char *name);

// --------------------------------------------------------------
//  ������� ����������� ��������� ������
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
// --------------------------------------------------------------

long int _export WINAPI medChoiceSquareImage
                       (HMAP hmap, TASKPARM *taskparm,
                        HOBJ object, HSELECT hselect,
                        char *name);

// --------------------------------------------------------------
//  ������� ����������� �������� ������
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
// --------------------------------------------------------------

long int _export WINAPI medChoicePointImage
                       (HMAP hmap, TASKPARM *taskparm,
                        HOBJ object, HSELECT hselect,
                        char *name);

// --------------------------------------------------------------
//  ������� ����������� ������ ���� �������
// hmap - ������������� �������� ��������� �����
// hobj - ������������� �������
// hselect - ������
// (���� hselect == 0 - ������ �� ������������)
//           (���� hselect == 0 - ������ �� ������������)
//            ���� hselect != 0 � � hselect �����������
//            �����, �� ������ �������� �� ����� �����.
//            ���� � hselect ����� �� �����������, ������
//            �������� �� ���� ������ ���������.
// name - ��������� �������
// ��� ���������� ���������� ���������� ��� ������� ����� 0
// ��� ������ ��� ������ ���������� 0
// --------------------------------------------------------------

long int _export WINAPI medChoiceTitleImage(HMAP hmap,
                                            TASKPARM *taskparm,
                                            HOBJ object,
                                            HSELECT hselect,
                                            char *name);


// **************************************************************
// ������� ������ � ���������� ��������������
// **************************************************************

// --------------------------------------------------------------------
//  ����� ������� �������������� ��������������
//  hmap - ������������� �������� ��������� �����
//  ��������� TASKPARM ������� � maptype.h
// --------------------------------------------------------------------

long int _export WINAPI CallMapFunction(long int hmap, TASKPARM * parm);


// --------------------------------------------------------------------
//  ����� ������� �������������� �������������� � ��������� ������� �����,
//  �������� � �������������� �������
//  hmap - ������������� �������� ��������� �����
//  ��������� TASKPARM ������� � maptype.h
//  mapnumber - ����� ����� (��� ��������� < 0 ���������� ������)
//  layernumber - ����� ���� (��� ��������� > 0 ������� �������� ����)
//  objectnumber - ���������� ����� �������������� ������� (� 1)
//  ��� ������� ��������������� �������� ������� � ���� ��������� �� ��������,
//  ����� ������� �����.
//  ���� ��� ��������� ��������� �������������, ������� �������� - "����� ������"
// --------------------------------------------------------------------

long int _export WINAPI rscEditForObject(long int hmap, TASKPARM * parm,
                                         long int mapnumber,
                                         long int layernumber,
                                         long int objectnumber);


// --------------------------------------------------------------------
//  ����� ������� �������������� �������������� � ��������� ������� �����,
//  hmap - ������������� �������� ��������� �����
//  ��������� TASKPARM ������� � maptype.h
//  ������� �������� - "������"
// --------------------------------------------------------------------

long int _export WINAPI rscEditForFont(long int hmap, TASKPARM * parm);

// --------------------------------------------------------------------
//  ����� ������� �������� �������������� � ����������� ���������������,
//  name - ������ ��� � �����
//  ��������� TASKPARM ������� � maptype.h
// --------------------------------------------------------------------

long int _export WINAPI rscCreate(char * name, TASKPARM * parm);

// --------------------------------------------------------------------
//  ����� ������� �������������� ��������������
//  name - ������ ��� � �����
//  ��������� TASKPARM ������� � maptype.h
// --------------------------------------------------------------------

long int _export WINAPI rscOpen(char * name, TASKPARM * parm);

// **************************************************************
//  ������� ������ � ��������� �����                                
// **************************************************************

// --------------------------------------------------------------
// �������������� ��������
// hmap     - ������������� �������� �����,
// mapname  - ��������� �� ������ ������ 260 ��������,
//            ���������� ��� ����� (����� ��������)
// parm     - ��������� ���������� ��� ������� (��. maptype.h)
// ��� ������ ���������� ����
// --------------------------------------------------------------

int _export WINAPI MapPaspEdit(long int hmap, char *mapname, TASKPARM * parm);

// --------------------------------------------------------------
// �������� �����
// hmap     - ������������� �������� �����,
// mapname  - ��������� �� ������ ������ 260 ��������,
//            ���������� ��� ����� (����� ��������)
//            ����� ������ ������� �������� ������ ����� ����������
// parm     - ��������� ���������� ��� ������� (��. maptype.h)
// ��� ������ ���������� ����
// --------------------------------------------------------------

int _export WINAPI MapPaspPlan(char *mapname, TASKPARM * parm);

// --------------------------------------------------------------
// �������� ���������������� �����
// hmap     - ������������� �������� �����,
// mapname  - ��������� �� ������ ������ 260 ��������,
//            ���������� ��� ����� (����� ��������)
//            ����� ������ ������� �������� ������ ����� ����������
// parm     - ��������� ���������� ��� ������� (��. maptype.h)
// ��� ������ ���������� ����
// --------------------------------------------------------------

int _export WINAPI MapPaspSit(char *mapname, TASKPARM * parm);

// --------------------------------------------------------------
// �������� ���������� � ���������� ���������������� �����
// � �������� � �������� ����� �����
// hmap     - ������������� �������� �����,
// mapname  - ��������� �� ������ ������ 260 ��������,
//            ���������� ��� ����� (����� ��������)
//            ����� ������ ������� �������� ������ ����� ����������
// path     - ���������� � ������� ����� ���������� ������� ����
//            (������������ ����� ������� ������)
// parm     - ��������� ���������� ��� ������� (��. maptype.h)
// ��� ������ ���������� ����
// --------------------------------------------------------------

int _export WINAPI  MapPaspSitDoc(long int hmap, char *mapname, char * path,
                                  TASKPARM * parm);

// --------------------------------------------------------------
// �������� ���������� � ���������� ���������������� �����
// � �������� ��� ������� ����� �����
// hmap     - ������������� �������� �����,
// mapname  - ��������� �� ������ ������ 260 ��������,
//            ���������� ��� ����� (����� ��������)
//            ����� ������ ������� �������� ������ ����� ����������
// parm     - ��������� ���������� ��� ������� (��. maptype.h)
// ��� ������ ���������� ����
// --------------------------------------------------------------

int _export WINAPI  MapPaspSitDocByName(long int hmap, char *mapname, TASKPARM * parm);

// --------------------------------------------------------------
// �������� ���������������� �����
// mapname  - ��������� �� ������ ������ 260 ��������,
//            ���������� ��� ����� (����� ��������)
//            ����� ������ ������� �������� ������ ����� ����������
// rscname  - ��� ����� �������������� (Rsc)
// areaname - ��� ������
// parm     - ��������� ���������� ��� ������� (��. maptype.h)
// ��� ������ ��� ������ �� ����� ���������� ����
// --------------------------------------------------------------

int _export WINAPI  MapPaspSitCreate(char * mapname, char *rscname,
                                     char * areaname, TASKPARM * parm);

}
#endif   // TEST


} // extern "C"

#endif