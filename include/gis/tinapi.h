
#ifndef TINAPI_H
#define TINAPI_H

#ifndef MAPTYPE_H
  #include "maptype.h"   // Описание структур интерфейса MAPAPI
#endif

#ifndef MAPCREAT_H
  #include "mapcreat.h"
#endif

#ifndef TINBASE_H
  #include "tinbase.h"
#endif
  
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ ОПИСАНИЕ ФУНКЦИЙ ДОСТУПА К TIN-МОДЕЛИ +++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern "C"
{
  // Запросить число открытых TIN-файлов
  // При ошибке возвращает 0

  long int _MAPAPI mapGetTinCount(HMAP hMap);

  // Открыть TIN-модель в заданном районе работ (добавить в цепочку)
  // Возвращает номер файла в цепочке
  // При ошибке возвращает 0
  long int _MAPAPI mapOpenTinForMap(HMAP hMap,
                                    const char * tinname,
                                    long int mode);

  // Закрыть TIN-модель в заданном районе работ
  // number - номер файла модели в цепочке
  // Если number == 0, закрываются все модели
  // При ошибке возвращает 0
  long int _MAPAPI mapCloseTinForMap(HMAP hMap, long int number);

  // Выбор значения высоты поверхности TIN-модели в заданной точке
  // Высота поверхности запрашивается из TIN-модели с меньшим
  // номером файла в цепочке.
  // Координаты точки (x,y) задаются в метрах в системе координат
  // векторной карты. Возвращает значение высоты в метрах.
  // В случае ошибки при выборе высоты и в случае необеспеченности
  // заданной точки данными TIN-модели возвращает ERRORHEIGHT.
  double _MAPAPI mapGetSurfaceHeight(HMAP hMap, double x, double y);

  // Выбор значения высоты поверхности TIN-модели в заданной точке
  // из файла с номером number в цепочке.
  // Координаты точки (x,y) задаются в метрах в системе координат
  // векторной карты. Возвращает значение высоты в метрах.
  // В случае ошибки при выборе высоты и в случае необеспеченности
  // заданной точки данными TIN-модели возвращает ERRORHEIGHT.
  double _MAPAPI mapGetTinSurfaceHeight(HMAP hMap, long int number,
                                        double x, double y);

  // Запрос треугольника из массива треугольников TIN-модели
  // number - номер TIN-файла в цепочке
  // index - индекс в массиве треугольников
  // При ошибке возвращает 0
  long int _MAPAPI mapGetTinTriangle(HMAP hMap, long int number,
                                     TINTRIANGLE* triangle, long int index);

  // Запросить/Установить степень видимости TIN-модели
  //  hMap   - идентификатор открытой основной векторной карты
  //  number - номер файла в цепочке
  //  view = 0 - не виден
  //  view = 1 - полная
  _MAPIMP long int _MAPAPI mapGetTinView(HMAP hMap,long int number);
  _MAPIMP long int _MAPAPI mapSetTinView(HMAP hMap,long int number,
                                         long int view);

  // Запросить/Установить порядок отображения TIN-модели
  //  hMap   - идентификатор открытой основной векторной карты
  //  number - номер файла в цепочке
  //  order  - порядок (0 - под картой, 1 - над картой)
  // При ошибке возвращает 0 					 
  _MAPIMP long int _MAPAPI mapGetTinViewOrder(HMAP hMap, long int number);
  _MAPIMP long int _MAPAPI mapSetTinViewOrder(HMAP hMap, long int number,
                                              long int order);
}

#endif // TINAPI_H

