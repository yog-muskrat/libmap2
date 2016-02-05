
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

  int          SelectCount;               // Число условий
  void       * SelectList[SELECTCOUNT];   // Список условий
  TMap       * Map;                       // Карта
}
  TSelectList;

typedef TSelectList SELECTLIST;

// Добавить в список условие поиска
TMapSelect * _fastcall slCreateSelect(SELECTLIST * data);

// Добавить в список условие поиска
int _fastcall slAppendSelect(SELECTLIST * data, void * select);

// Удалить из списка условие поиска
void _fastcall slDeleteSelect(SELECTLIST * data, void * select);

#endif
