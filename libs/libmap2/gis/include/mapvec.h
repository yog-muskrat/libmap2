
#ifndef MAPVEC_H
#define MAPVEC_H

#ifndef MAPTAB_H
 #include "maptab.h"
#endif

#ifdef HIDEFORMAT
  #define HIDEVECT
#endif

class TMapList;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ���� � ������� ������� ������������� �����
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef struct VECDATA     // ������ �������� 3D-������
{                          //
  long        Code;        // ��� ���������� (��� ���������� �����������, ����� 0)
  long        Key;         // ���� ����������� (��� ���������� �����������, ����� 0)
  XYHDOUBLE   Offset;      // �������� ����� ������ ������������ ������ ����� �������
  double      Angle;       // ���� �������� ��� X ������ ������������ ��� X �����
}
  VECDATA;

typedef struct VECRECORD   // ������ ������� �������� (������ ����� VEC)
{                          //
  long        Number;      // ����� �������
  long        BaseKey;     // ���� �������
  VECDATA     Data;        // ������ ��������
}
  VECRECORD;

// ������ ����� ������� �� ������� �������� �� ��� ���������� ������ ����� �������.
// �� ����������� �������� ���������� ������ ����� ������� ������. ���������� �������� = Offset.
// Angle - ���� �������� ��� X ������ ������������ ��� X �����.

#ifndef HIDEVECT
typedef class _DLLCLASS TVectorFile : public TTableFile
#else
typedef class _DLLCLASS TVectorFile
#endif
{
 public:

#ifndef HIDEVECT
   TVectorFile(TMapList * data);
   ~TVectorFile();
#else
   TVectorFile(TMapList * ) {}
   ~TVectorFile() {}
#endif

#ifndef HIDEVECT
   // ������� ���� � ������� �������
   // ��� �������� ���������� ���������� ��������� ��������
   int _fastcall Create(TMapList * data);

   // ������� ���� � ������� �������
   // ��� �������� ���������� ���������� ��������� ��������
   int _fastcall Open(TMapList * data);

   // ������� ����
   void _fastcall Close();

   // ��������� ����� ������ �� �� ������
   VECDATA * _fastcall Record(TMapList * data, int number);

   // �������� ������ �� ������
   // force - ������� ������������ ���������� ������ � �����
   int _fastcall Record(TMapList * data, const VECDATA * record,
                        int number, int key, int force);
#else
   // ������� ���� � ������� �������
   // ��� �������� ���������� ���������� ��������� ��������
   int _fastcall Create(TMapList * ) { return 0; }

   // ������� ���� � ������� �������
   // ��� �������� ���������� ���������� ��������� ��������
   int _fastcall Open(TMapList * ) { return 0; }

   // ������� ����
   void _fastcall Close() {}

   // ��������� ����� ������ �� �� ������
   VECDATA * _fastcall Record(TMapList * , int )
   { return 0; }

   // �������� ������ �� ������
   // force - ������� ������������ ���������� ������ � �����
   int _fastcall Record(TMapList * , const VECDATA * ,
                        int , int , int )
   { return 0; }
#endif

#ifndef HIDEVECT
   // ��������� ��� ����� ��������
   const char * GetFileName() { return Name; }

   // ��������� - ���� �� � ����� ������?
   int IsEmpty() { return (Head.RecordCount == 0); }

   // ���������� ���������� ������������ �����
   void _fastcall SetFileExt(const char * ext = 0);

   // ������������ ��� ����� �������� 3D-������
   // ��� �������� ���������� ���������� ��������� ��������
   const char * _fastcall GetName(TMapList * data);
#else
   // ��������� ��� ����� ��������
   const char * GetFileName() { return ""; }

   // ��������� - ���� �� � ����� ������?
   int IsEmpty() { return 1; }

   // ���������� ���������� ������������ �����
   void _fastcall SetFileExt(const char * ext = 0) {}

   // ������������ ��� ����� �������� 3D-������
   // ��� �������� ���������� ���������� ��������� ��������
   const char * _fastcall GetName(TMapList * ) { return ""; }
#endif

 protected:

#ifndef HIDEVECT
  TMapList *    Data;

  HANDLE        Back_VEC;     // ������������� ���������� �����

  char          Ext[8];       // ���������� ������������ �����
#endif  
}
  TVectorFile;

#endif
