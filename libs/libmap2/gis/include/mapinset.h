
#ifndef MAPINSET_H
#define MAPINSET_H

#ifndef AREALIST_H
  #include "arealist.h"
#endif

#ifndef MAPAPI_H
  #include "mapapi.h"
#endif

// ���������� ����� ������ �� �����
#define INSETLIMIT 1024

enum INSETPLACE      // ������ �������� ������
{
   INP_TOTAL   = 0,  // ���������� ��� ������ � �������� ����
   INP_FRAME   = 1,  // ���������� ��������� �������� � �������� ��������
};

typedef struct INSETITEM    // �������� �������� ������ ������
{
  INSETITEM()
  {
    Ident       = 0;
    Path[0]     = 0;
    Name[0]     = 0;
    Scale       = 100000;
    TopScale    = 40000000;
    BottomScale = 1;
    View        = 1;
    hMap        = 0;
    DataColor   = 0x07F7F7F;
    BorderColor = 0;
    Transparence= 0;
    BorderThick = 260;
    BorderView  = 1;
    PlaceFlag   = INP_TOTAL;
    FirstPlace  = 0;    
    SecondPlace = 0;
  }

  long int    Ident;        // ������������� ��������
  char        Path[260];    // ������ ���� � ����� ������
  char        Name[32];     // �������� �������� ������ (������������� �� ������)
  long int    Scale;        // ������� ����������� (������������� �� ������ ��� INP_FRAME)
  long int    TopScale;     // ����������� �������� ������� ������� ���������
  long int    BottomScale;  // ����������� �������� ������ ������� ���������
  long int    View;         // ������� ��������� ������

                            // ���������� � ������� ��������� ��������� (�����)
  DOUBLEPOINT FirstPlace;   // ���������� �������� ������ �������� ����
  DOUBLEPOINT SecondPlace;  // ���������� �������� ������� ������� ����
                            // ���������� � ������� ������ ������ ��� INP_FRAME (�����)
  DOUBLEPOINT FramePlace;   // ���������� �������� ������ �������� ����
  long int    PlaceFlag;    // ������ �������� (INP_TOTAL, INP_FRAME)

  HMAP        hMap;         // ������������� �������� ������ ��� ����

  long int    DataColor;    // ���� ���� ���� ������
  long int    Transparence; // ������� ������������ ����
  long int    BorderColor;  // ���� ����� ����
  long int    BorderThick;  // ������� �����
  long int    BorderView;   // ������� ����������� �����
}
  INSETITEM;


typedef class _DLLCLASS TInsetList : public TSimpleList
{
public:

  // ������� ������
  TInsetList() : TSimpleList(sizeof(INSETITEM)) { Ident = 1; }
  ~TInsetList()
    {
      while(ItemCount > 0)          
       Delete(ItemCount);
    }

  // �������� ������
  int Append(INSETITEM * item)
   { if (item)
       {
         item->Ident = Ident;                  
         Ident++;
       }
     return TSimpleList::Append((char*)item, sizeof(INSETITEM)); }

  // ������� ������
  // number - ����� ��������, ������� � 1
  void Delete(int number)
  {
    INSETITEM * item = Item(number);
    if (item && item->hMap)
      {
        mapCloseData(item->hMap);
        item->hMap = 0;
      }
    TSimpleList::Delete(number);
  }

  // ��������� �������
  INSETITEM * Item(int number)
   { return (INSETITEM*) TSimpleList::Item(number); }

  INSETITEM * ItemByIdent(int ident)
   {
     for (int i = 1; i <= ItemCount; i++)
     {
       if (Item(i)->Ident == ident)
         return (INSETITEM*) TSimpleList::Item(i);
     }

     return 0;
   }

public:

  long int Ident;
}
  TInsetList;

#ifdef LINUXAPI                  
 typedef struct SAVINGMAPINSET
  {
    long int        CountMapinset;            // ���������� ������
    long int        NumbMapinset[INSETLIMIT]; // ������ ���������� ������� ������
    DOUBLEPOINT     RectIn[INSETLIMIT];       // ������������ �� ����� (������� ����� ����)
    DOUBLEPOINT     RectInSec[INSETLIMIT];    // ������������ �� ����� (������ ������ ����)
    TInsetList      *InsetList;               // ������ ������
  }
  SAVINGMAPINSET;
#endif

#endif // MAPINSET_H


