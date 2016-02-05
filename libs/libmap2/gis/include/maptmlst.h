
#if !defined(MAPTMLST_H)
#define MAPTMLST_H

#ifdef __cplusplus

#ifndef MAPDEF_H
  #include "mapdef.h"
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  ВРЕМЕННАЯ КОПИЯ ЛИСТА ЭЛЕКТРОННОЙ КАРТЫ  +++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Класс предназначен для создания копии файлов листа
// при выполнении сортировки, трансформирования и других
// процессов (файлы  ...~DA,~SE,~HD)

class _DLLCLASS TMapTempList
{
 public :

 TMapTempList();

 ~TMapTempList();

 // Создать копию файлов заданного листа
 // При ошибке возвращает ноль
 int Create(TMap * map,int list);

 // Удалить копию файлов
 // Используется для "сбора мусора"
 // После удачной замены файлов исходного листа
 // файлов копии уже нет
 void Delete();

 // Запросить код ошибки выполнения последней операции
 long int Error() { return MapList.Error(); }

 // Заменить файлы исходного листа
 // Удалаяет исходные файлы листа и замещает их
 // файлами копии
 // Если замещаемые файлы открыты с помощью
 // отдельного объекта TMapList во время
 // вызова Remove() - возвращает 0
 // savecopy  - сохранить файлы данных листа (~HD,~SE,~DA,~DR),
 // share     - признак разделенного доступа (если не равен 0,
 //             то замещение файлов выполняется в любом случае,
 //             иначе - только при монопольном доступе к карте),
 // saveback  - сохранить файлы отката (^HD,^SE,^DA,^DR)
 // При неудаче возвращает ноль, код ошибки - см. Error()
 int Remove(int share = 1, int savecopy = 0, int saveback = 0);

 // Запросить/Установить признак запуска специальной сортировки данных
 int IsFreeAppend() { return MapList.IsFreeAppend(); }
 int IsFreeAppend(int start)
    { return MapList.IsFreeAppend(start); }

 /***************************************************************
 *                                                              *
 *          Функции заполнения копии листа карты                *
 *                                                              *
 ***************************************************************/


 // Создать новый объект
 // При неудаче возвращает ноль, код ошибки - см. Error()
 // При успешном выполнении - номер созданного объекта в листе
 // Объекты нумеруются с единицы
 int AppendObject(TObjectInfo * object)
 {
   return MapList.AppendObject(object);
 }

 int AppendObject(TObjectDesc desc,
                  TObjectData data = (char*)0,
                  TObjectSemn semn = (char*)0,
                  TObjectDraw draw = (char*)0)
 {
    return MapList.AppendObject(desc.Base,data.Base,semn.Base,draw.Base);
 }

 //  Удалить объект, заданный номером в листе
 int DeleteObject(int number)
    {
      return MapList.DeleteObject(number);
    }

 // Обновить объект,number - номер объекта в листе,
 // после обновления становится текущим
 // При неудаче возвращает ноль, код ошибки - см. Error()
 // При успешном выполнении - номер отредактированного объекта в листе
 // Если number задан ошибочно, возвращается номер, определенный
 // по логической цепочке
 int UpdateObject(int number, TObjectInfo * object)
    {
      return MapList.UpdateObject(number,object);
    }

 int UpdateObject(int number,TObjectHead * head,
                             TObjectData data = (char*)0,
                             TObjectSemn semn = (char*)0,
                             TObjectDraw draw = (char*)0)
    {
      return MapList.UpdateObject(number,head,data.Base,
                                              semn.Base,draw.Base);
    }


 /***************************************************************
 *                                                              *
 *       Запросы описания объектов, метрики и семантики         *
 *                                                              *
 ***************************************************************/

public:
/*
 // Запросить метрику текущего объекта
 // При ошибке возвращает ноль
 OBJECTDATA * DataAddr()
    {
      return MapList.DataAddr();
    }

#ifndef TINYDATA
 // Запросить метрику текущего объекта
 // При ошибке возвращает ноль
 IMGDRAW * DrawAddr()
    {
      return MapList.DrawAddr();
    }
#endif
*/
 // Запросить описание "первого" объекта (в логической цепочке)
 // "Первый" объект становится текущим
 // Объекты нумеруются с единицы
 TObjectHead * FirstHead()
    {
      return MapList.FirstHead();
    }

 // Запросить описание "последнего" объекта (в логической цепочке)
 // "Последний" объект становится текущим
 // Объекты нумеруются с единицы
 TObjectHead * LastHead()
    {
      return MapList.LastHead();
    }

int PrepareList;   // Номер замещаемого листа

double CopyXSW;    // Копия координат листа обстановки
double CopyYSW;
double CopyXNE;
double CopyYNE;

int IsRemove;      // Признак успешной замены листа


TMapList MapList;  // Лист карты

};

#endif  // __cplusplus

#endif

