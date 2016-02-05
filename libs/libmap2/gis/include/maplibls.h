
#if !defined(MAPLIBLS_H)
#define MAPLIBLS_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifndef MAPVERSN_H
  #include "mapversn.h"
#endif

#ifndef PAIMET_H
  #include "paimet.h"
#endif  

#ifndef MAPGDIEX_H
  #include "mapgdiex.h"
#endif

#define MAXLIBRARYCOUNT 64

typedef IMLLIST * (WINAPI* DLLIMAGELIST)(void);


typedef int (WINAPI* DLLIMAGEBORDER)
        (long int type, const POLYDATAEX* data,
         const IMGDRAW * parm, const IMGCONTEXT * context, FRAME * border);

typedef int (WINAPI* DLLPAINTIMAGE)
       (long int, const POLYDATAEX*,
        const IMGDRAW *, const IMGCONTEXT *);

typedef int (WINAPI* DLLPAINTEXAMPLE)
       (long int, const IMGDRAW *, const IMGCONTEXT *);

typedef int (WINAPI* DLLTESTVISIBLE)
       (long int, const POLYDATAEX*,
        const IMGDRAW *, const IMGCONTEXT *);

typedef int (WINAPI* DLLCLOSELIBRARY) ();

typedef struct LIBRARYLIST
{
  // ����� ����������� �������� � ����������
  DLLIMAGELIST    GetImageList;

  // ������ ����������� ������� � ���
  DLLIMAGEBORDER  GetImageBorder;

  // ���������� ������ � �������� ����
  DLLPAINTIMAGE   PaintImage;

  // ���������� ������� ������� � �������� ����
  DLLPAINTEXAMPLE PaintExample;

  // ���������� ��������� ������� � �������� �������
  DLLTESTVISIBLE  TestVisible;

  // ���������� ������� ����������
  DLLCLOSELIBRARY CloseLibrary;

  char      Name[MAX_PATH];    // ��� ����������
  int       Count;             // ����� �����������
  HINSTANCE HInstance;         // ������������� ����������

  IMLLIST * ImageList;         // �������� ���������� �����������
}
  LIBRARYLIST;

typedef struct LIBRARYLISTDATA
{
 int Count;                            // ����� ����������� ���������

 LIBRARYLIST Library[MAXLIBRARYCOUNT]; // �������� ����������
}
  LIBRARYLISTDATA;

// ��������� �������� ����������� ������� � ��������� � ������� ��������
// ���� ������� �� �������������� - ���������� ����,
// ����� - ��������� ��������
int _fastcall llGetImageBorder(int number, long int code,
                               const POLYDATAEX* data,
                               const IMGDRAW * parm,
                               const IMGCONTEXT * context,
                               FRAME * border);


// ���������� ������
int _fastcall llPaintImage(int number, long int code,
                           const POLYDATAEX * data,
                           const IMGDRAW * parm, const IMGCONTEXT * context);

// ���������� ������ �������
int _fastcall llPaintExample(int number, long int code,
                             const IMGDRAW * parm,
                             const IMGCONTEXT * context);

// ���������� ��������� �������
int _fastcall llTestVisible(int number, long int code,
                            const POLYDATAEX * data,
                            const IMGDRAW * parm, const IMGCONTEXT * context);

// ��������� �������� ����������� ������� � ��������� � ������� ��������
// ���� ������� �� �������������� - ���������� ����,
// ����� - ��������� ��������
int _fastcall llGetImageBorder(int number, long int code,
                               const POLYDATAEX* data,
                               const IMGDRAW * parm,
                               const IMGCONTEXT * context,
                               FRAME * border);

// ��������� �������� ����������� ������� � ��������
// � ������� ��������
// ���� ������� �� �������������� - ���������� ����,
// ����� - ��������� ��������
int _fastcall llGetImageSize(TPaintMetric * pmet,              
                             const IMGLIBRARY * parm,
                             IMAGESIZE * imagesize);


// �������� ���������� � ������
// ���������� ����� ���������� � ������ (1,...)
// ��� ������ ���������� ����
int _fastcall llOpenLibrary(const char * name);

// ������� ���������� �� ������
// name - ��� ���������� (*.IML)
// number - ����� ���������� � ������
void _fastcall llCloseLibraryByName(const char * name);
void _fastcall llCloseLibrary(int number);

// ��������� �������� �������,
// �������������� �����������
const IMLLIST * _fastcall llGetImageList(int number);

// ������ ������������� ��������� ��� �����������
int _fastcall llGetSemanticFlag(int number, int index);

// ��������� ������ �������
// ��� ������ ���������� ����
int _fastcall llLoadLibrary(const char * name, LIBRARYLIST * library, int i);

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++  ������ ��������� ����������� �������  +++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifdef __cplusplus

class _DLLCLASS TLibraryList : public LIBRARYLISTDATA
{

public :

 // ���������������� ������ ���������
 TLibraryList();

 // ������� ������ ���������
 ~TLibraryList();

 // ������� ���������� �� ������
 // name - ��� ���������� (*.IML)
 // number - ����� ���������� � ������ (1 - MAXLIBRARYCOUNT)
 void CloseLibrary(const char * name);
 void CloseLibrary(int number);

 // ��������� ����������� ����������
 int IsLibraryActive(int number)
  {
    if ((number <= 0) || (number > MAXLIBRARYCOUNT))
      return 0;
    return Library[number-1].Count;
  }

 // ��������� ����� ��������� � ������
 int LibraryCount() { return Count; }

#ifndef HIDESECTION
 MAPCRITICALSECTION Section;                     
#endif

};

#else

typedef LIBRARYLISTDATA TLibraryList;

#endif

// ����� ������ ������������ ���������
extern TLibraryList LibraryList;


#endif

