
#ifndef MAPINSET_H
#define MAPINSET_H

#ifndef AREALIST_H
  #include "arealist.h"
#endif

#ifndef MAPAPI_H
  #include "mapapi.h"
#endif

// Предельное число врезок на карте
#define INSETLIMIT 1024

enum INSETPLACE      // СПОСОБ ПРИВЯЗКИ ВРЕЗКИ
{
   INP_TOTAL   = 0,  // Отображать все данные в заданном окне
   INP_FRAME   = 1,  // Отображать указанный фрагмент в заданном масштабе
};

typedef struct INSETITEM    // ОПИСАНИЕ ЭЛЕМЕНТА СПИСКА ВРЕЗОК
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

  long int    Ident;        // Идентификатор элемента
  char        Path[260];    // Полный путь к файлу данных
  char        Name[32];     // Условное название данных (первоначально из данных)
  long int    Scale;        // Масштаб отображения (первоначально из данных для INP_FRAME)
  long int    TopScale;     // Знаменатель масштаба верхней границы видимости
  long int    BottomScale;  // Знаменатель масштаба нижней границы видимости
  long int    View;         // Признак видимости врезки

                            // Координаты в системе открытого документа (метры)
  DOUBLEPOINT FirstPlace;   // Координаты привязки левого верхнего угла
  DOUBLEPOINT SecondPlace;  // Координаты привязки правого нижнего угла
                            // Координаты в системе данных врезки для INP_FRAME (метры)
  DOUBLEPOINT FramePlace;   // Координаты привязки левого верхнего угла
  long int    PlaceFlag;    // Способ привязки (INP_TOTAL, INP_FRAME)

  HMAP        hMap;         // Идентификатор открытых данных или ноль

  long int    DataColor;    // Цвет фона окна данных
  long int    Transparence; // Признак прозрачности фона
  long int    BorderColor;  // Цвет рамки окна
  long int    BorderThick;  // Толщина рамки
  long int    BorderView;   // Признак отображения рамки
}
  INSETITEM;


typedef class _DLLCLASS TInsetList : public TSimpleList
{
public:

  // Создать список
  TInsetList() : TSimpleList(sizeof(INSETITEM)) { Ident = 1; }
  ~TInsetList()
    {
      while(ItemCount > 0)          
       Delete(ItemCount);
    }

  // Добавить запись
  int Append(INSETITEM * item)
   { if (item)
       {
         item->Ident = Ident;                  
         Ident++;
       }
     return TSimpleList::Append((char*)item, sizeof(INSETITEM)); }

  // Удалить список
  // number - номер элемента, начиная с 1
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

  // Запросить элемент
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
    long int        CountMapinset;            // Количество врезок
    long int        NumbMapinset[INSETLIMIT]; // Массив уникальных номеров врезок
    DOUBLEPOINT     RectIn[INSETLIMIT];       // Расположение на карте (верхний левый угол)
    DOUBLEPOINT     RectInSec[INSETLIMIT];    // Расположение на карте (нижний правый угол)
    TInsetList      *InsetList;               // Список врезок
  }
  SAVINGMAPINSET;
#endif

#endif // MAPINSET_H


