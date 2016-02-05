
#ifndef MAPOLD_H
#define MAPOLD_H


typedef struct MTRBUILDPARM  // ��������� �������� �������
{
  double BeginX;         // ������������� ���������� ������
  double BeginY;         // (���-��������� ����) �������  � ������

  double Width;          // ������ ������� � ������
  double Height;         // ������ ������� � ������

  double ElemSizeMeters; // ������ ������� ������������� �������
                         // � ������ �� ���������
  long int ReliefType;   // ��� ������� (0 - ���������� ������,
                         //              1 - ���������� + �������������)
  long int Filter;       // ������� ������������� ����� MTRCREA.TXT
                         // (0 - �� ������������, 1 - ������������)
  long int UserType;     // ������������ �����, �����������
                         // � ����������� ��������
}
  MTRBUILDPARM;

typedef struct MTRBUILDPARMEX  //  ��������� �������� ������� �����
{
  unsigned
  long int StructSize;     // ������ ������ ��������� :
                           //  sizeof (MTRBUILDPARMEX)

  double   BeginX;         // ������������� ���������� ������
  double   BeginY;         // (���-��������� ����) ������� � ������

  double   Width;          // ������ ������� � ������
  double   Height;         // ������ ������� � ������

  double   ElemSizeMeters; // ������ ������� ������������� �������
                           // � ������ �� ���������

  long int ElemSizeBytes;  // P����� �������� ������� � ������
                           // (���������� �������� : 1,2,4,8)

  long int Unit;           // E������ ��������� ������
                           // (0 - �����, 1 - ���������,
                           //  2 - ����������, 3 - ���������� )

  long int ReliefType;     // ��� ������� (0 - ���������� ������,
                           //    1 - ���������� + �������������)

  long int UserType;       // ������������ �����, �����������
                           // � ����������� ��������

  long int Scale;          // ����������� �������� �����������
                           // ��������� ����� (��� �������� �������
                           // �� ��������� ����� �������� �������
                           // ���� ����� �������� �� �����������
                           // �������� ��������� �����)

  long int HeightSuper;    // ������ ��� ��������� � �������
                           // ����� ������ ������� � ����������
                           // ������� (0 - �������, 1 - ������������)

  long int FastBuilding;   // ������� �������� �������
                           // (0 - �������, 1 - �������)

  char     Reserve[8];     // ������ ���� ����
}
  MTRBUILDPARMEX;


typedef struct MTRCOLORDESC  // �������� ��������� �����
                             // �������         
{
  COLORREF Color;            // ����,��������������� ��������� �����
  double MinHeight;          // ����������� ������ ��������
  double MaxHeight;          // ������������ ������ ��������
}
  MTRCOLORDESC;

typedef struct SEMANTICTYPE  // �������� �������������
                             // �������������� ��'����
{
  long int Code;       // ������� ���
  long int Type;       // ��� ��������
  long int Reply;      // ����������� ���������� (1)
  long int Enable;     // ����������(1),������������(2)
                       // (��� �������� ��������� ���� �� �����������)
  long int Service;    // ���������,��������� ��� ���� �������� (1)
  char     Name[32];   // �������� ��������������
  char     Unit[8];    // ������� ���������
  double   Minimum;    // ����������� ��������
  double   Default;    // ������������ ��������
  double   Maximum;    // ������������ ��������
}
  SEMANTICTYPE;

typedef SEMANTICTYPE RSCSEMANTIC;


typedef struct SEMANTICTYPEEX  // ����������� �������� �������������    
                               // �������������� ��'����
{
  long int Code;         // ������� ���
  long int Type;         // ��� ��������
  long int Reply;        // ����������� ���������� (1)
  long int Enable;       // ����������(1),������������(2)
                         // (��� �������� ��������� ���� �� �����������)
  long int Service;      // ���������,��������� ��� ���� �������� (1)
  char     Name[32];     // �������� ��������������
  char     Unit[8];      // ������� ���������
  double   Minimum;      // ����������� ��������
  double   Default;      // ������������ ��������
  double   Maximum;      // ������������ ��������
  long int Size;         // ����� ������ ���� �������� ���������
  long int Decimal;      // �������� ���� �������� ���������
  char     ShortName[16];// �������� ��� ��������� (����� � ����� ��)
  long int Reserv;       // ������
}
  SEMANTICTYPEEX;

typedef struct MAPADJACENTLIST
{
  char      ListName[25];           // ��� �����
  long int  Key;                    // ����� �������
  long int  Excode;                 // ����������������� ��� �������
  long int  First;                  // ������ ����� �������
  long int  Last;                   // ��������� ����� �������
}
  MAPADJACENTLIST;


#endif
