
#ifndef AREALIST_H
#define AREALIST_H

#ifndef MAPTYPE_H
 #include "maptype.h"
#endif 

typedef struct ALSITEM     // �������� �������� ������ ������� �����
{
  long Ident;              // ������������� ��������
  char Path[260];          // ������ ���� � �������� ������
  char Name[32];           // ��� ������ (������� �� ��������)
  long Scale;              // ������� ������ (������� �� ��������)
  long Minimum;            // ������ ������� �������� � ������ (��������, 100 000)
  long Maximum;            // ������� ������� �������� � ������ (��������, 500 000)
  long Priority;           // ��������� ������ ��� ���������� ���������
}
  ALSITEM;

typedef struct ALSITEMEX   // �������� �������� ������ ������� �����
{                                                                     
  long Ident;              // ������������� ��������
  long Scale;              // ������� ������ (������� �� ��������)
  long Minimum;            // ������ ������� �������� � ������ (��������, 100 000)
  long Maximum;            // ������� ������� �������� � ������ (��������, 500 000)
  long Priority;           // ��������� ������ ��� ���������� ���������
  long Reserve;            // ������ = 0
}
  ALSITEMEX;

typedef long int HALS;     // ������������� ������ ������� �����

// ������ ��������� ��������, ����������� ����� ����� (������� ������)
#define SEMALSPATH   7701  // ���� � �����
#define SEMALSNAME   7702  // ��� ������ �����
#define SEMALSSCALE  7703  // ������� ������ �����
#define SEMALSMIN    7704  // ������ ������� ��������
#define SEMALSMAX    7705  // ������� ������� ��������
#define SEMALSMODE   7706  // ����� ��������� ������
#define SEMALSPRIOR  7707  // ��������� ������

#define ALS_UP          1  // ����� ����� ������� ��������
#define ALS_DOWN        2  // ����� ����� �������� ��������
#define ALS_ANY         0  // ����� ����� �����
#define ALS_BACK        4  // ��������� � �����

// ----------------------------------------------------------------------
// ������ �������� ������������� �������                   
// ----------------------------------------------------------------------
typedef class _DLLCLASS TSimpleList
{
public:

  // ������� ������
  // size    - ������ �������� ������
  // reserve - ����������� ����� ���������
  TSimpleList(int size, int reserve = 256);

  ~TSimpleList() { Clear(); }

  // �������� ������
  // item - ����� ������ ������
  // size - ����������� ������ (��� ������������ � size - ������)
  // ��� ������ ���������� ����
  int Append(const char * item, int size);

  // ����� ���������
  int  Count() { return ItemCount; }

  // �������� ������
  void Clear();

  // ������� ������
  // number - ����� ��������, ������� � 1
  void Delete(int number);

  // ��������� �������
  // number - ����� ��������, ������� � 1
  char * Item(int number);
  
private:

  int Allocate(int size);

public:

  int    ItemCount;
  char * ItemBegin;
  int    ItemSize;
  int    MemorySize;
  int    ItemReserve;
}
  TSimpleList;

// ----------------------------------------------------------------------
// ������ ������� �����
// ----------------------------------------------------------------------
typedef class _DLLCLASS TAreaList : public TSimpleList
{
public:

  // ������� ������
  TAreaList() : TSimpleList(sizeof(ALSITEM)) {}

  // �������� ������
  int Append(ALSITEM * item)
   { return TSimpleList::Append((char*)item, sizeof(ALSITEM)); }
  
  // ��������� �������
  ALSITEM * Item(int number)
   { return (ALSITEM*) TSimpleList::Item(number); }
}  
  TAreaList;


extern "C"
{

// ������� ������ ������� �����
// listname - ���� � ������ ������� ����� (����� "ALS")
// ��� ������ ���������� ����, ����� - ������������� ������ �������

HALS _MAPAPI alsOpenAreaList(const char * listname);

// ������� ������ ������� �����
// listname - ���� � ������ ������� ����� (����� "ALS")
// listtype - ��� ������ ������� (0 - ���������� � ���������� �������������
//            ���������, 1 - ��������� � ������� ������� ���������
// rscname -  ��� �������������� ��� �������� ������ (������ - "arealist.rsc")
// ��� ������ ���������� ����, ����� - ������������� ������ �������

HALS _MAPAPI alsCreateAreaList(const char * listname, long int listtype);
HALS _MAPAPI alsCreateAreaListEx(const char * listname,
                                 const char * rscname, long int listtype);

// ������� ������ ������� �����
// hals - ������������� ������ �������

void _MAPAPI alsCloseAreaList(HALS hals);

// ��������� �������� �� ����� ����������
// hals - ������������� ������ ������� (������)
// ���� ��� - ���������� ����

HALS _MAPAPI alsIsGlobalAreaList(HALS hals);

// ��������� ����� ��������� � ������
// hals - ������������� ������ �������

long int _MAPAPI alsGetItemCount(HALS hals);

// ��������� �������� �������� ������ �������
// hals   - ������������� ������ �������
// number - ���������� ����� ��������, ������� � 1
// item   - ����������� ��������� �������� ��������
// ��� ������ ���������� ����

long int _MAPAPI alsGetItem(HALS hals, long int number, ALSITEM * item);

// ��������� �������� �������� ������ �������
// hals   - ������������� ������ �������
// number - ���������� ����� ��������, ������� � 1
// item   - ����������� ��������� �������� ��������
// ��� ������ ���������� ����

long int _MAPAPI alsGetItem(HALS hals, long int number, ALSITEM * item);
long int _MAPAPI alsGetItemEx(HALS hals, long int number, ALSITEMEX * item); 

// ��������� ��� �������� ������ �������                 
// hals   - ������������� ������ �������
// number - ���������� ����� ��������, ������� � 1
// name   - ����� ������ ��� ������ ����������
// size   - ����� ������� ������ � ������ (�� ����� 32)
// ��� ������ ���������� ����

long int _MAPAPI alsGetItemName(HALS hals, long int number, char * name, long int size);

// ��������� ���� � �������� ��� �������� �� ������ �������         
// hals   - ������������� ������ �������
// number - ���������� ����� ��������, ������� � 1
// path   - ����� ������ ��� ������ ����������
// size   - ����� ������� ������ � ������ (�� ����� 260)
// ��� ������ ���������� ����

long int _MAPAPI alsGetItemPath(HALS hals, long int number, char * path, long int size);

// ��������� �������� �������� ������ �������
// hals   - ������������� ������ �������
// ident  - ������������� ��������
// item   - ����������� ��������� �������� ��������
// ��� ������ ���������� ����

long int _MAPAPI alsGetItemByIdent(HALS hals, long int ident, ALSITEM * item);

// ��������� �������� �������� ������ �������                    
// hals   - ������������� ������ �������
// ident  - ������������� ��������
// item   - ����������� ��������� �������� ��������
// ��� ������ ���������� ����

long int _MAPAPI alsGetItemByIdentEx(HALS hals, long int ident, ALSITEMEX * item);

// �������� ������� � ������ �������
// hals - ������������� ������ �������
// path - ������ ���� � �������� ������ �����
// ��� ������ ���������� ����

long int _MAPAPI alsAppendItem(HALS hals, const char * path);


// ���������� ������� ��������� ��� ��������������� �������� � �����
// hals    - ������������� ������ �������
// ident   - ������������� ��������, ��. ALSITEM
// minimum - ������ ������� �������� � ������ (��������, 100 000)
// maximum - ������� ������� �������� � ������ (��������, 500 000)
// ��� ������ ���������� ����

long int _MAPAPI alsSetItemMiniMax(HALS hals, long int ident,
                                   long int minimum,
                                   long int maximum);

// ���������� ��������� ������ �����
// hals     - ������������� ������ �������
// ident    - ������������� ��������, ��. ALSITEM
// priority - ��������� ������ ������
// ��� ������ ���������� ����

long int _MAPAPI alsSetItemPriority(HALS hals, long int ident,
                                    long int priority);

// ���������� ������� ��������� ��� ��������������� �������� � �����
// hals   - ������������� ������ �������
// ident   - ������������� ��������, ��. ALSITEM
// ��� ������ ���������� ����

long int _MAPAPI alsDeleteItem(HALS hals, long int ident);


// ����� ������� ������������� � �������� ����� ���� ����������
// �������� (� ����� ������� ��������)
// hals   - ������������� ������ �������
// ident   - ������������� ��������, ��. ALSITEM
// point  - ������������� ���������� �������� ����� � ��������
// item   - ����������� ��������� �������� ���������� ��������
// ��� ������ ���������� ����

long int _MAPAPI alsGoItemDown(HALS hals, long int ident,
                               DOUBLEPOINT * point, ALSITEM * item);

// ����� ������� ������������� � �������� ����� ���� ���������
// �������� (� ����� ������� ��������)
// hals   - ������������� ������ �������
// scale  - ������� �������� ��������
// point  - ������������� ���������� �������� ����� � ��������
// item   - ����������� ��������� �������� ���������� ��������
// ��� ������ ���������� ����

long int _MAPAPI alsGoItemDownByScale(HALS hals, long int scale,
                                      DOUBLEPOINT * point, ALSITEM * item);

// ����� ������� ������������� � �������� ����� ���� ���������
// �������� (� ����� ������� ��������)
// hals   - ������������� ������ �������
// scale  - ������� �������� ��������
// frame  - ���������� �������� ������� �� ������
// item   - ����������� ��������� �������� ���������� ��������
// ��� ������ ���������� ����

long int _MAPAPI alsGoItemDownByScaleEx(HALS hals, long int scale,
                                        HOBJ frame, ALSITEM * target);

// ����� ������� ������������� � �������� ����� ���� ����������
// �������� (� ����� ������ ��������)
// hals   - ������������� ������ �������
// ident   - ������������� ��������, ��. ALSITEM
// point  - ������������� ���������� �������� ����� � ��������
// item   - ����������� ��������� �������� ���������� ��������
// ��� ������ ���������� ����

long int _MAPAPI alsGoItemUp(HALS hals, long int ident,
                             DOUBLEPOINT * point, ALSITEM * item);

// ����� ������� ������������� � �������� ����� ���� ����������
// �������� (� ����� ������ ��������)
// hals   - ������������� ������ �������
// scale  - ������� �������� ��������
// point  - ������������� ���������� �������� ����� � ��������
// item   - ����������� ��������� �������� ���������� ��������
// ��� ������ ���������� ����

long int _MAPAPI alsGoItemUpByScale(HALS hals, long int scale,
                                    DOUBLEPOINT * point, ALSITEM * item);

// ����� ������� ������������� � �������� ����� ���� ���������
// �������� (� ����� ������ ��������)
// hals   - ������������� ������ �������
// scale  - ������� �������� ��������
// frame  - ������������� ���������� �������� ������� �� ������
// item   - ����������� ��������� �������� ���������� ��������
// ��� ������ ���������� ����

long int _MAPAPI alsGoItemUpByScaleEx(HALS hals, long int scale,
                                      HOBJ frame, ALSITEM * target);

// ���������� ������� ����������� � ������ ���������� �����������
// ������ � �������� �������� �������
// width  - ������ ������� � ��������,
// height - ������ ������� � ��������

void _MAPAPI alsSetPictureSize(HALS hals, long int width,
                               long int height);

// �������� �� ����� ��������� ������� ������
// hdc   - �������� ���� ����������� ������
// rect  - ���������� ���� � ������� ������� ����������� ������
// ident - ������������� ��������, ��. ALSITEM
// color - ���� ��������� �������� �� ������
// thick - ������� ����� ��������� � ��������

void _MAPAPI alsPaintSelectItem(HALS hals, HDC hdc,
                                RECT * rect, long int ident,
                                COLORREF color, int thick);

// ��������� ��������� ������ � ����������� ������
// ident - ������������� �������� (������), ��. ALSITEM
// point - ����������� ���������� � �������� ��� �������� �������� �����������
// ��� ������ ���������� ����

long int _MAPAPI alsGetItemPosition(HALS hals, long int ident, POINT * point);

// ������� � ����� ��� ������
// hals   - ������������� ������ �������
// point  - ������������� ���������� �������� ����� � ��������
// ��� ������ ���������� ����

long int _MAPAPI alsItemList(HALS hals, TAreaList * list, DOUBLEPOINT * point);


// ��������� - ���� �� � ����� �����
// direct    - ����������� ������ (ALS_UP, ALS_DOWN, ALS_ANY)
// point     - ������������� ���������� �������� ����� � ��������
// ���� ����� ���� - ���������� ��������� ��������
// ��� ������ ���������� ����

long int _MAPAPI alsEnableItem(HALS hals, long int scale,
                               DOUBLEPOINT * point, long int direct);

// ��������� - ���� �� � �������� ������� �����
// direct    - ����������� ������ (ALS_UP, ALS_DOWN, ALS_ANY)
// frame     - ���������� �������� ������� �� ������
// ���� ����� ���� - ���������� ��������� ��������
// ��� ������ ���������� ����

long int _MAPAPI alsEnableItemEx(HALS hals, long int scale,
                                 HOBJ frame, long int direct);
                                      
}  // extern "C"


#endif  //  AREALIST_H

