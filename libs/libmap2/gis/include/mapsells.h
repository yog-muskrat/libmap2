
#if !defined(MAPSELLS_H)
#define MAPSELLS_H

class  TMap;
class  TMapSelect;

#define SELECTCOUNT 256

typedef class _DLLCLASS TSelectList
{
 public:

  TSelectList(TMap * map);
  ~TSelectList();

 public:

  int          SelectCount;               // ����� �������
  void       * SelectList[SELECTCOUNT];   // ������ �������
  TMap       * Map;                       // �����
}
  TSelectList;

typedef TSelectList SELECTLIST;

// �������� � ������ ������� ������
TMapSelect * _fastcall slCreateSelect(SELECTLIST * data);

// �������� � ������ ������� ������
int _fastcall slAppendSelect(SELECTLIST * data, void * select);

// ������� �� ������ ������� ������
void _fastcall slDeleteSelect(SELECTLIST * data, void * select);

#endif
