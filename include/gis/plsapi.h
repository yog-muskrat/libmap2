
#ifndef PLSAPI_H

#define PLSAPI_H

#ifndef MAPAPI_H
   #include "mapapi.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

 // Преобразование из пикселов в изображении в координаты
 // на местности в метрах
 // Применение :
 // xmet = xdis; ymet = ydis;
 // PictureToPlane(xmet,ymet);
 double _MAPAPI plsPictureToPlaneX(HMAP hMap, double x, double y);
 double _MAPAPI plsPictureToPlaneY(HMAP hMap, double x, double y);

 // Преобразование из метров на местности в пикселы на
 // изображении
 double _MAPAPI plsPlaneToPictureX(HMAP hMap,double x, double y);
 double _MAPAPI plsPlaneToPictureY(HMAP hMap,double x, double y);

 // Преобразование из метров на местности в геодезические
 // координаты в радианах в соответствии с проекцией карты
 // (поддерживается не для всех карт !)
 // При ошибке возвращает ноль
 // Применение :
 // if (IsGeoSupported())      |  или :
 //   {                        |  if (IsGeoSupported())
 //     B = Xmet; L = Ymet;    |    {
 //     Plan2Geo(B,L);         |      Plan2Geo(B=Xmet,L=Ymet);
 //   }                        |    }
 double _MAPAPI plsPlaneToGeoBx(HMAP hMap,double Bx, double Ly);
 double _MAPAPI plsPlaneToGeoLy(HMAP hMap,double Bx, double Ly);

 // Преобразование из геодезических координат в радианах
 // в метры на местности в соответствии с проекцией карты
 // (поддерживается не для всех карт !)
 // При ошибке возвращает ноль
 double _MAPAPI plsGeoToPlaneX(HMAP hMap, double Bx, double Ly);
 double _MAPAPI plsGeoToPlaneY(HMAP hMap, double Bx, double Ly);

 // Преобразование геодезических координаты в радианах из системы 1942г
 // (эллипсоид Красовского) в геодезические координаты в радианах
 // (общеземной эллипсоид WGS84) (поддерживается не для всех карт !)
 // При ошибке возвращает ноль
 double _MAPAPI plsGeo42ToGeoWGS84Bx(HMAP hMap, double Bx, double Ly);
 double _MAPAPI plsGeo42ToGeoWGS84Ly(HMAP hMap, double Bx, double Ly);

 // Преобразование геодезических координаты в радианах из системы WGS 84
 // (общеземной эллипсоид WGS84) (поддерживается не для всех карт !)
 // в геодезические координаты в радианах в систему 1942 г (эллипсоид Красовского)
 // При ошибке возвращает ноль
 double _MAPAPI plsGeoWGS84ToGeo42Bx(HMAP hMap, double Bx, double Ly);
 double _MAPAPI plsGeoWGS84ToGeo42Ly(HMAP hMap, double Bx, double Ly);

 // Преобразование геодезических координат в радианах из системы ПЗ-90
 // (общеземной эллипсоид ПЗ-90) в геодезические координаты в радианах
 // системы 1942 г (эллипсоид Красовского) (поддерживается не для всех карт !)
 //  При ошибке возвращает ноль
 // Применение :
 // if (mapIsGeoSupported())
 //   {
 //     mapGeoEP90ToGeo42(hMap,&B,&L);
 //   }
 double _MAPAPI plsGeoEP90ToGeo42Bx(HMAP hMap, double Bx, double Ly);
 double _MAPAPI plsGeoEP90ToGeo42Ly(HMAP hMap, double Bx, double Ly);

 // Преобразование геодезических координат в радианах из системы 1942 г
 // (эллипсоид Красовского) в геодезические координаты в радианах
 // системы ПЗ-90(общеземной эллипсоид ПЗ-90) (поддерживается не для всех карт !)
 //  При ошибке возвращает ноль
 // Применение :
 // if (mapIsGeoSupported())
 //   {
 //     mapGeo42ToGeoEP90(hMap,&B,&L);
 //   }
 double _MAPAPI plsGeo42ToGeoEP90Bx(HMAP hMap, double Bx, double Ly);
 double _MAPAPI plsGeo42ToGeoEP90Ly(HMAP hMap, double Bx, double Ly);

 // Построение ортодромии с учетом особенностей PLSQL                    
 // hObj - объект, в который будет запомнена линия ортодромии
 // firstB, firstL - координаты первой точки в градусах с долями
 // secondB, secondL - координаты второй точки в градусах с долями
 // При ошибке возвращает ноль
 long int _MAPAPI plsOrthodrome(HOBJ hObj, double firstB, double firstL,
                                      double secondB, double secondL);


 // hObj - объект, на котором ищется точка
 // hObjNew - объект, в который пишется маршрут до найденной точки
 // number - номер начальной точки
 // distance - расстояние
 // subject - номер подобъекта
 // возвращает ноль при ошибке
 long int _MAPAPI plsSeekVirtualPointByDistance(HOBJ hObj, HOBJ hObjNew, long int number,
                                             double distance, long int subject);

 // Поиск обектов в окрестности точки, среди активных объектов
 // Применяется для выбора объекта при нажатии левой кнопки мыши на карте
 // Поиск выполнется среди тех объектов,которые видны на экране !
 // Активные объекты - те, что доступны для интерактивного выбора (оператором)
 // Установка условий поиска выполняется функцией mapSetSiteActiveSelect()
 // hMap  - идентификатор открытой карты,
 // hObj  - идентификатор объекта в памяти,
 //         предварительно созданного функцией mapCreateObject()
 //         или mapCreateSiteObject(),
 //         в котором будет размещен результат поиска.
 // pointX, pointY - точка поиска объекта в метрах на карте
 // deltaPix - радиус области поиска в пикселах
 // flagseek  - порядок поиска объектов (WO_FIRST, WO_NEXT...)
 // Если объект не найден - возвращает ноль
_MAPIMP  long int _MAPAPI plsWhatActiveObject(HMAP hMap, HOBJ hObj,               
                                              double pointX, double pointY,
                                              long int deltaPix, long int flagSeek);

// Найти точку на контурах объекта и подобъектов,
// ближайшую к заданной
// hMap    - идентификатор открытой карты,
// info    - идентификатор объекта в памяти
// pointinX, pointinY - координаты точки в прямоугольной
//                      системе координат , в метрах на местности
// Возвращает координату Х точки
_MAPIMP double _MAPAPI plsSeekNearVirtualPointX(HMAP hMap, HOBJ info,
                                                double pointinX, double pointinY);

// Найти точку на контурах объекта и подобъектов,
// ближайшую к заданной
// hMap    - идентификатор открытой карты,
// info    - идентификатор объекта в памяти
// pointinX, pointinY - координаты точки в прямоугольной
//                      системе координат , в метрах на местности
// Возвращает координату Y точки
_MAPIMP double _MAPAPI plsSeekNearVirtualPointY(HMAP hMap, HOBJ info,
                                                double pointinX, double pointinY);

#if defined(LINUXAPI) && defined(HIDEX11)
 // Создать GIF-файл с размещением на диске
 // hmap          - идентификатор открытых данных
 // left, top     - координаты левого верхнего угла изображения карты (в пикселах)
 // right, bottom - координаты правого нижнего угла изображения карты (в пикселах)
 // namefile      - имя GIF-файла
 // Возвращает размер GIF-файла (в байтах)
 // При ошибке возвращает 0
 long int _MAPAPI plsCreateGifFileFromMap(HMAP hMap,
                                          int left, int top,
                                          int right, int bottom,
                                          char* namefile);

 // Создать GIF-файл по открытой карте с выделенными объектами
 // hmap          - идентификатор открытых данных
 // left, top     - координаты левого верхнего угла изображения карты (в пикселах)
 // right, bottom - координаты правого нижнего угла изображения карты (в пикселах)
 // namefile      - имя GIF-файла
 // select - условия отбора объектов, если равны 0, то применяются
 //          условия обобщенного поиска\выделения
 // Возвращает размер GIF-файла (в байтах)
 // При ошибке возвращает 0
 long int _MAPAPI plsCreateGifFileFromMapSel(HMAP hMap,
                                             int left, int top,
                                             int right, int bottom,
                                             char* namefile,
                                             HSELECT select);

// Создать GIF-файл с размещением на диске по открытой карте и пользовательскому    
// объекту
// hMap        - идентификатор открытых данных
// hObj        - идентификатор пользовательского объекта
// imageParm   - параметры рисования объекта (см. MAPGDI.H структуры типа IMGOBJECT,
//                                            IMGLINE, IMGCIRCLE...)
// imageType   - тип параметров рисования объекта (см. MAPGDI.H вид ф-ции отображения
//                                     объектов типа IMG_OBJECT, IMG_LINE, IMG_CIRCLE...)
// left, top   - координаты левого верхнего угла изображения карты (в пикселах)
// right, bottom - координаты правого нижнего угла изображения карты (в пикселах)
// namefile      - имя GIF-файла
// Возвращает размер GIF-файла (в байтах)
// При ошибке возвращает 0
long int WINAPI _export plsCreateGifFileFromMapAndObj(HMAP hMap, HOBJ hObj,
                                                      char* imageParm, long int sizeParm,  
                                                      long int imageType,
                                                      int left, int top,
                          			      int right, int bottom,
						      char* namefile);

// Создать GIF-файл с размещением на диске по открытой карте и пользовательскому    
// объекту
// hMap        - идентификатор открытых данных
// hObj        - идентификатор пользовательского объекта
// imageParm   - параметры рисования объекта (см. MAPGDI.H структуры типа IMGOBJECT,
//                                            IMGLINE, IMGCIRCLE...)
// imageType   - тип параметров рисования объекта (см. MAPGDI.H вид ф-ции отображения
//                                     объектов типа IMG_OBJECT, IMG_LINE, IMG_CIRCLE...)
// left, top   - координаты левого верхнего угла изображения карты (в пикселах)
// right, bottom - координаты правого нижнего угла изображения карты (в пикселах)
// namefile      - имя GIF-файла
// Возвращает размер GIF-файла (в байтах)
// При ошибке возвращает 0
long int WINAPI _export plsCreateGifFileFromMapSelObj(HMAP hMap, HSELECT select,
                                     HOBJ hObj, char* imageParm, long int sizeParm,
                                     long int imageType,int left, int top,
        			     int right, int bottom, char* namefile);


// Определить габариты объекта
// hObj    - идентификатор объекта в памяти
// numPoint - номер точки габаритов, начиная с 1 (ЮЗ угол)
// Возвращает: координату Х точки
_MAPIMP double _MAPAPI plsObjectFrameX(HOBJ hObj, long int numPoint);
 
// Определить габариты объекта
// hObj    - идентификатор объекта в памяти
// numPoint - номер точки габаритов, начиная с 1 (ЮЗ угол)
// Возвращает: координату Y точки
_MAPIMP double _MAPAPI plsObjectFrameY(HOBJ hObj, long int numPoint);
 


// Положение точки относительно отрезка
// pointX, pointY - координаты точки
// xy1X, xy1Y, xy2X, xy2Y   - координаты концов отрезка
// precision - точность поиска (в метрах)
// Возвращает позицию точки:
//  1 - совпадает с первой точкой отрезка
//  2 - совпадает со второй точкой отрезка
//  3 - лежит позади первой точки отрезка
//  4 - лежит впереди второй точки отрезка
//  5 - лежит на отрезке (между точками)
//  6 - слева от отрезка
//  7 - справа от отрезка
// При ошибке возвращает 0
_MAPIMP long int _MAPAPI plsGetPointPosition(double pointX, double pointY,       
                                             double xy1X, double xy1Y,
                                             double xy2X, double xy2Y,
                                             double precision);

// Вычисление длины объекта от начала до заданной точки                          
// info  - идентификатор объекта карты в памяти
// point - координаты точки, расположенной вдоль(вблизи) объекта
// Если точка не на объекте - ищется ближайшая точка на контуре
// Координаты точки обновляются!
// При ошибке возвращает 0
_MAPIMP double _MAPAPI plsLengthToPoint(HOBJ hObj, double pointX, double pointY);


#endif    // LINUXAPI && HIDEX11

#ifdef __cplusplus
}              // extern "C"
#endif

#endif   // PLSAPI_H
