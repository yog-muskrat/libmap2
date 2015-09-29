
#ifndef MAPMETR_H
#define MAPMETR_H

#ifndef MAPVERSN_H
  #include "mapversn.h"
#endif

#ifndef MAPHDR_H
  #include "maphdr.h"
#endif

#ifndef MAPDAT_H
  #include "mapdat.h"
#endif

#ifndef MAPCALC_H
 #include "mapcalc.h"          
#endif

/***************************************************************
********************  СИСТЕМЫ КООРДИНАТ ************************
****************************************************************

    Xд Xп
  ^
  | (0,0) (Начало изображения)
  +---------------------------------------------------> Xи
  |                                                 ^
  |        (Координаты окна)                        |
  |   (0,0)                      Xо                 |
  |     ---------+------+------>                    |
  |     |        ...... |  Окно визуализации        |
  |     |        ...... |                           |
  |     |        ...... |                           |
  |     |        ...... |                         Габариты
  |     ---------+------+                      района (Region)
  |     |          ^                                |
  |     |          |                                |
  |     |         Область текущего вывода           |
  |     V                  (Draw)                   |
  |       Yо                                        |
  |                                                 |
  | ZeroX,ZeroY (метры)                             V
  +----------------------------------------------------> Yд Yп
  |  0,0 (Начало района в дискретах
  |       и пикселах)
  |
  V
    Yи

****************************************************************
****************************************************************/

#define MINV -65000.0
#define MAXV  65000.0
#define ROUNDL(x) ROUND(max(MINV, min(MAXV, x)))

class _DLLCLASS TMapMetricMemory
{
public :

 TMapMetricMemory();

 ~TMapMetricMemory();

 // Выделить память под буфер координат
 int AllocateMetricMemory(int pointlimit = 0);

public :

 // Переменные и функции, необходимые для работы с общей для всех открываемых
 // районов работ областью памяти, выделяемой под преобразование координат
 // ---------------------------------------------------------------------------

 int GlobalPointLimit;       // Предельные значения                  
 int GlobalPolyLimit;        // элементов метрического описания
 int GlobalTextLimit;        // объектов карты

 int AllocBuffPointError;    // Признак выдачи сообщения об ошибке выделения памяти
                             // (от зацикливания сообщений)

 XYTYPE *    GlobalPointArea;// Адрес области точек
 long int *  GlobalPolyArea; // Адрес области количеств точек
 char **     GlobalTextArea; // Адрес области адресов подписей

 char * lpPoint;             // Адрес выделенной области памяти
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  КЛАСС "ПЕРЕСЧЕТ МЕТРИКИ ОБ'ЕКТОВ " +++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TMapMetric : public TMapMetricMemory
{
public :

 // Инициализация данных для пересчета метрики

 TMapMetric();

 // Освободить ресурсы

 ~TMapMetric();

 // Выполнить преобразование метрики объекта в координаты
 // устройства отображения
 // При успешном выполнении возвращает 0 !

 int _fastcall BuildMetric(TObjectDesc desc, OBJECTDATA * data, POLYDATAEX * polydata);

 // Установить положение области отображения
 // относительно текущего листа в пикселах
 // viewposition - координаты листа в районе в дискретах

 void _fastcall SetListPosition(DOUBLEPOINT * viewposition);

 // Установить положение произвольной области
 // относительно текущего листа в пикселах
 // listframe - координаты листа в районе в дискретах

 void _fastcall SetListPosition(DOUBLEPOINT * viewposition, DFRAME * frame);

 // Установить положение области отображения карты
 // обстановки в пикселах
 // Возвращает старый размер дискрета, который необходимо
 // восстановить после выполнения отображения

 double SetSitePosition();

 // Установить положение произвольной области для карты
 // обстановки относительно текущего листа в пикселах
 // listframe - координаты листа в районе в дискретах
 // Возвращает старый размер дискрета, который необходимо
 // восстановить после выполнения отображения

 double _fastcall SetSitePosition(DFRAME * Draw);

 // Занять переменные класса

 void ClassLock();

 // Освободить переменные класса

 void ClassUnLock();

 /***************************************************************
 *                                                              *
 *      ФУНКЦИИ ПЕРЕСЧЕТА КООРДИНАТ                             *
 *                                                              *
 ***************************************************************/

public :

 // Поворот активен ?
 int TurnIsActive() { return TurnActive; }

 // Запросить/Установить угол поворота карты
 double GetTurnAngle() { return Angle; }
 double SetTurnAngle(double angle, double fixation);

 // Пересчитать дискреты в пикселы и обратно С УЧЕТОМ ПОВОРОТА
 void Pix2Dis(DOUBLEPOINT& pix, DOUBLEPOINT& dis);
 void Dis2Pix(DOUBLEPOINT& dis, DOUBLEPOINT& pix);
 void Dis2Pix(DOUBLEPOINT& dis, POINT& pix);

 // Пересчитать дискреты в метры и обратно
 double Dis2MetX(double disX) {return (ZeroX + MetInDis*disX);}
 double Dis2MetY(double disY) {return (ZeroY + MetInDis*disY);}
 double Met2DisX(double metX) {return ((metX-ZeroX)*DisInMet);}
 double Met2DisY(double metY) {return ((metY-ZeroY)*DisInMet);}

 // Пересчитать элементы растра в дискреты и обратно
 double Elem2Dis(double element) {return element*DisInElem;}
 double Dis2Elem(double discret) {return discret*ElemInDis;}

 // Пересчитать дискреты в пикселы и обратно
 double HorDis2Pix(double discret) {return discret*HorPixInDis;}
 double HorPix2Dis(double pixel) {return pixel*HorDisInPix;}
 double VerDis2Pix(double discret) {return discret*VerPixInDis;}
 double VerPix2Dis(double pixel) {return pixel*VerDisInPix;}

 long HorDis2PixL(double discret) {return ROUND(discret*HorPixInDis);}
 long HorPix2DisL(double pixel) {return ROUND(pixel*HorDisInPix);}
 long HorDis2Pix(long discret) {return ROUND(discret*HorPixInDis);}
 long HorPix2Dis(long pixel) {return ROUND(pixel*HorDisInPix);}

 long VerDis2PixL(double discret) {return ROUND(discret*VerPixInDis);}
 long VerPix2DisL(double pixel) {return ROUND(pixel*VerDisInPix);}
 long VerDis2Pix(long discret) {return ROUND(discret*VerPixInDis);}
 long VerPix2Dis(long pixel) {return ROUND(pixel*VerDisInPix);}

 // Пересчитать элементы растра в пикселы и обратно
 double HorElem2Pix(double element) {return element*HorPixInElem;}
 double HorPix2Elem(double pixel) {return pixel*HorElemInPix;}
 long   HorElem2PixL(double element) {return ROUND(element*HorPixInElem);}
 long   HorPix2ElemL(double pixel) {return ROUND(pixel*HorElemInPix);}
 long   HorElem2Pix(long element) {return ROUND(element*HorPixInElem);}
 long   HorPix2Elem(long pixel) {return ROUND(pixel*HorElemInPix);}

 double VerElem2Pix(double element) {return element*VerPixInElem;}
 double VerPix2Elem(double pixel) {return pixel*VerElemInPix;}
 long   VerElem2PixL(double element) {return ROUND(element*VerPixInElem);}
 long   VerPix2ElemL(double pixel) {return ROUND(pixel*VerElemInPix);}
 long   VerElem2Pix(long element) {return ROUND(element*VerPixInElem);}
 long   VerPix2Elem(long pixel) {return ROUND(pixel*VerElemInPix);}

 // Пересчитать габариты фрагмента из дискрет в пикселы
 void RegionDisToPix(DFRAME& regiondis, DFRAME& regionpix);

 // Пересчитать габариты из элементов в пикселы
 void RegionElemToPix(DFRAME& regionelem, DFRAME& regionpix);

 // Пересчитать габариты из элементов в дискреты
 void RegionElemToDis(DFRAME& regionelem, DFRAME& regiondis);

 // Пересчитать координаты области визуализации относительно
 // системы координат района
 // Параметры: - координаты области перерисовки в пикселах
 //              относительно полного изображения;
 // Возвращает текущее значение координат в районе
 DFRAME& SetDrawPlace(RECT& drawpix);

 // Восстановить координаты области визуализации
 void RestoreDrawPlace();

 double& GetDiscret() { return Discret; }
 double SetDiscret(double digit)
 {
   double OldDiscret = Discret;
   Discret = digit;
   UpdatePlace();
   return OldDiscret;
 }

 double SetElement(double elemmetr)
 {
   double OldElement = Element;
   Element = elemmetr;
   UpdatePlace();
   return OldElement;
 }

 // Установить "точность устройства вывода"
 void _fastcall SetPixel(double& horpixel, double& verpixel);

 // Запросить "точность устройства вывода"
 double& GetHorizontalPixel() {return HorizontalPixel;}
 double& GetVerticalPixel() {return VerticalPixel;}

 // Пересчитать коэффициенты и габариты изображения
 void UpdatePlace();

 // Функции изменения масштаба
 // change - коэффициент изменения текущего масштаба ( > 0)
 // scale  - новое значение масштаба отображения
 // Возвращают новое значение коэффициента масштабирования
 double GetDrawScale() {return ViewScale;}
 double ChangeDrawScale(double change);
 double SetDrawScale(double scale);

 DFRAME GetRegionPix() {return RegionPix;}

 // Запросить число метров в number дискрет
 double GetMetInDis() { return MetInDis; }
 double GetMetInDis(double number)
   { return MetInDis * number; }

 // Запросить сколько метров в number пикселах
 double GetMetInPix()
   { return MetInDis * HorPix2Dis((double)1); }
 double GetMetInPix(double number)
   { return MetInDis * HorPix2Dis(number); }

 double GetHorMetInPix()                           
   { return MetInDis * HorDisInPix; }
 double GetVerMetInPix()
   { return MetInDis * VerDisInPix; }

 // Запросить координаты точки привязки карты
 // к прямоугольной системе координат в метрах
 double& GetZeroX() { return ZeroX; }
 double& GetZeroY() { return ZeroY; }

protected:

 // Пересчитать габариты района (в пикселах и дискретах)
 //  regionelem - габариты района в элементах
 //  precision  - размер элемента
 void UpdateRegionElem(DFRAME& regionelem, double& precision);

 // Установить координаты точки привязки карты
 // к прямоугольной системе координат в метрах
 double SetZeroX(double x) { return ZeroX = x; }
 double SetZeroY(double y) { return ZeroY = y; }

 // Установить число метров в одном дискрете
 double SetMetInDis(double metindis)
 {
   MetInDis = metindis;
   DisInMet = 1.0/MetInDis;
   return MetInDis;
 }

 // Повернуть точку (повернуть обратно)
 //  turnpoint - координаты повернутой точки
 void Turn(DOUBLEPOINT& point, DOUBLEPOINT& turnpoint);
 void Inverse(DOUBLEPOINT& point, DOUBLEPOINT& turnpoint);

 // Повернуть прямоуголник (повернуть обратно)
 //  turnframe - габариты повернутого прямоуголника
 void Turn(DFRAME& frame, DFRAME& turnframe);
 void Inverse(DFRAME& frame, DFRAME& turnframe);

public:

 // Данные для размещения карты
 // --------------------------

 DFRAME RegionPix;    // Габариты общего района в пикселах   
 DFRAME DrawDPix;     // Область перерисовки в пикселах      
 DFRAME SaveDrawDPix; // в районе работ (1-л.н.; 2-п.в.)     

 DFRAME RegionDis;    // Габариты общего района в дискретах
 DFRAME DrawDis;      // Область перерисовки в дискретах
                      // в районе работ (1-л.н.; 2-п.в.)

 DFRAME DrawMet;      // Область перерисовки абсолютная
                      // в метрах (1-л.н.; 2-п.в.)

 DRAWSIZE szDraw;     // Ширина и высота области рисования      

 double ZeroX;        // Координаты точки привязки карты
 double ZeroY;        // к прямоугольной системе координат (метры)

 double MetInDis;     // Метров на местности в одном дискрете
 double DisInMet;     // Число дискрет на метр местности

 double ViewScale;    // Текущий масштаб отображения
                      // = 5   -> Изображение увеличено в 5 раз
                      // = 0.1 -> Изображение уменьшено в 10 раз

 double VerticalPixel;    // Число точек на метр на устройстве
 double HorizontalPixel;  // Число точек на метр на устройстве
 double Discret;          // Число точек на метр на карте

 double HorDisInPix;     // Число точек карты в точке экрана
 double HorPixInDis;     // Число точек экрана в точке карты
 double VerDisInPix;     // Число точек карты в точке экрана
 double VerPixInDis;     // Число точек экрана в точке карты

 double Element;         // Число элементов на метр в растре
 double HorElemInPix;    // Число элементов растра в точке экрана
 double HorPixInElem;    // Число точек экрана в элементе растра
 double VerElemInPix;    // Число элементов растра в точке экрана
 double VerPixInElem;    // Число точек экрана в элементе растра

 double DisInElem;       // Число точек карты на элемент
 double ElemInDis;       // Число элементов в точке экрана

 double Angle;           // Угол поворота карты
 double SinTurn;         // sin угла поворота карты
 double CosTurn;         // cos угла поворота карты
 int TurnActive;         // Флаг активизации поворота


 FRAME ListDrawBorder;    // Границы отображаемой области в листе
                          // для контроля видимости объектов

 DOUBLEPOINT AreaInList;  // Положение области визуализации в
                          // текущем листе карты

 long int BaseScale;      // Базовый масштаб отображения карты

 // Переменные, необходимые для работы с векторными объектами
 // ------------------------------------------------------------------------------

 char * lpWork;              // Адрес буфера описани векторного объекта
 long int WorkSize;          // Размер области описани (24К)

 TSpline Spline;             // Построение сплайна по метрике 
 int     HideSplineFlag;     // Признак отмены построения сплайна

#ifndef HIDESECTION
 MAPCRITICALSECTION Section;              
#endif
};

typedef  TMapMetric MAPBASE;

// Инициализация данных для пересчета метрики
void _fastcall mmInit(MAPBASE * data);

// Освободить ресурсы
void _fastcall mmFree(MAPBASE * data);

// Установить "точность устройства вывода"
void _fastcall mmSetPixel(MAPBASE * data, double * hpixel, double * vpixel);

// Пересчитать коэффициенты и габариты изображения
void _fastcall mmUpdatePlace(MAPBASE * data);

// Измененить масштаб отображения
void _fastcall mmSetDrawScale(MAPBASE * data, double * scale);

// Установить угол поворота карты
void _fastcall mmSetTurnAngle(MAPBASE * data, double * angle,
                              double * fixation);

// Пересчитать координаты области визуализации относительно
// системы координат района
void _fastcall mmSetDrawPlace(MAPBASE * data, RECT * drawpix);

// Восстановить координаты области визуализации
void _fastcall mmRestoreDrawPlace(MAPBASE * data);

// Пересчитать габариты из дискрет в пикселы
void _fastcall mmRegionDisToPix(MAPBASE * data, DFRAME * regiondis,
                                DFRAME * regionpix);

// Пересчитать габариты из элементов в пикселы
void _fastcall mmRegionElemToPix(MAPBASE * data, DFRAME * regionelem,
                                 DFRAME * regionpix);

// Пересчитать габариты из элементов в дискреты
void _fastcall mmRegionElemToDis(MAPBASE * data, DFRAME * regionelem,
                                 DFRAME * regiondis);

// Установить габариты района в дискретах
void _fastcall mmSetRegionDis(MAPBASE * data, DFRAME * regiondis);

// Обновить габариты района
void _fastcall mmUpdateRegionElem(MAPBASE * base, DFRAME * regionelem,
                                  double * precision);

// Расширить габариты района на величину delta
void _fastcall mmEnlargeRegionDis(MAPBASE * base, double * delta);

// Повернуть точку
void _fastcall mmTurn(MAPBASE * base, DOUBLEPOINT * point,
                      DOUBLEPOINT * turnpoint);

// Повернуть точку обратно
void _fastcall mmInverse(MAPBASE * base, DOUBLEPOINT * point,
                         DOUBLEPOINT * turnpoint);

// Повернуть прямоуголник
void _fastcall mmTurnFrame(MAPBASE * base, DFRAME * frame, DFRAME * turnframe);

// Повернуть прямоуголник обратно
void _fastcall mmInverseFrame(MAPBASE * base, DFRAME * frame, DFRAME * turnframe);

// Пересчитать пикселы в дискреты с учетом поворота
void _fastcall mmPix2Dis(MAPBASE * base, DOUBLEPOINT * pix,
                         DOUBLEPOINT * dis);

// Пересчитать дискреты в пикселы с учетом поворота
void _fastcall mmDis2Pix(MAPBASE * base, DOUBLEPOINT * dis,
                         DOUBLEPOINT * pix);

// Пересчитать дискреты в пикселы с учетом поворота
void _fastcall mmDis2PixDraw(MAPBASE * base, DOUBLEPOINT * dis,
                             POINT * pix);

// Установить положение области отображения
// относительно текущего листа в пикселах
// viewposition - координаты листа в районе в дискретах
void _fastcall mmSetListPosition(MAPBASE * data, DOUBLEPOINT * viewposition);

// Установить положение произвольной области
// относительно текущего листа в пикселах
// viewposition - координаты листа в районе в дискретах
void _fastcall mmSetListPositionDraw(MAPBASE * data,
                                     DOUBLEPOINT * viewposition,
                                     DFRAME * draw);

// Установить положение области отображения карты
// обстановки в пикселах
// Возвращает старый размер дискрета, который необходимо
// восстановить после выполнения отображения
double _fastcall mmSetSitePosition(MAPBASE * data);

// Установить положение произвольной области для карты
// обстановки относительно текущего листа в пикселах
// draw - координаты листа в районе в дискретах
// Возвращает старый размер дискрета, который необходимо
// восстановить после выполнения отображения
double _fastcall mmSetSitePositionDraw(MAPBASE * data, DFRAME * draw);

// Выполнить преобразование метрики объекта в координаты
// устройства отображения
// При ошибке возвращает ноль
int _fastcall mmBuildMetric(MAPBASE * base, TObjectHead * head,
                            OBJECTDATA * data, POLYDATAEX * polydata);  

// Функция обрезки метрики объекта по предельно допустимым габаритам
void mmCutMetric(MAPBASE * base, POLYDATAEX * polydata);  

// Установить число метров в одном дискрете
void _fastcall mmSetMetInDis(MAPBASE * base, double * metindis);

// Установить размер дискрета
void _fastcall mmSetDiscret(MAPBASE * data, double * digit);

// Установить размер элемента
void _fastcall mmSetElement(MAPBASE * data, double * elemmetr);


// Функция перераспределения памяти, необходимой для преобразовани координат
// При ошибке возвращает ноль
int _fastcall mmReAllocBuffPoint(TMapMetricMemory * base, int pointcount);     

// Функция выделения области памяти, необходимой для преобразовани координат
int _fastcall mmAllocBuffPoint(TMapMetricMemory * base, int pointlimit = 0);

// Функция освобождения области памяти, необходимой для преобразовани координат
void _fastcall mmFreeBuffPoint(TMapMetricMemory * base);


#endif

