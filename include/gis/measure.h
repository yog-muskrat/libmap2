
#ifndef MEASURE_H
#define MEASURE_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  КЛАСС "РАСЧЕТ ПАРАМЕТРОВ ОБ'ЕКТА"  +++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

enum
{
  tmsFIRST   = 1,  // совпадает с первой точкой отрезка
  tmsSECOND  = 2,  // совпадает со второй точкой отрезка
  tmsBEHIND  = 3,  // лежит позади первой точки отрезка
  tmsBEYOND  = 4,  // лежит впереди второй точки отрезка
  tmsBETWEEN = 5,  // лежит на отрезке (между точками)
  tmsLEFT    = 6,  // слева
  tmsRIGHT   = 7   // справа
};

typedef struct TMEASUREDATA
{
  double A;
  double B;           // Коэффициенты линии Ax+By+C=0;
  double C;
  int Sign;           // Знак результата Distance() (-1/1)
}
  TMEASUREDATA;

//  Инициализация данных
void _fastcall tmsInit(TMEASUREDATA *measuredata);

// Угол между прямыми (p11,p12) и (p21,p22) в радианах
// Возвращает модуль угла:
//   0    - прямые параллельны
//   PI/2 - прямые перпендикулярны
//  -1    - точки одного из отрезков совпадают, либо не заданы
double _fastcall tmsAngleBetweenLines(DOUBLEPOINT *p11, DOUBLEPOINT *p12,
                                      DOUBLEPOINT *p21, DOUBLEPOINT *p22);

// Определение угла наклона биссектрисы угла, заданного
// точками p1,p2,p3 с вершиной в точке p2
double _fastcall tmsBisectorAngle(DOUBLEPOINT *p1, DOUBLEPOINT *p2,
                                  DOUBLEPOINT *p3);

// Определение центра окружности по трем точкам
//  pc - точка центра
// Возвращает радиус окружности (0.0 - три точки совпадают,
//                              -1.0 - точки на одной прямой)
double _fastcall tmsCircleCenter(DOUBLEPOINT *p1, DOUBLEPOINT *p2,
                                 DOUBLEPOINT *p3, DOUBLEPOINT *pc);

// Вычисление расстояния между двумя точками
double _fastcall tmsDistancePoint(DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);

// Вычисление расстояния между точкой и прямой,
// заданной двумя точками
double _fastcall tmsDistance(TMEASUREDATA *measuredata,
                             DOUBLEPOINT *point, DOUBLEPOINT *xy1,
                             DOUBLEPOINT *xy2);

// Вычисление дирекционного угла в радианах
double _fastcall tmsDirectionAngle(DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);

// Определение входимости точки с координатами x,y
// в объект/подобъект
// возврат: 1-точка внутри объекта/подобъекта,
//          2-точка внешняя,
//          3-точка совпадает с точкой метрики,
//          4-точка лежит на отрезке метрики,
//          0 - непутевая метрика
// point   - координаты точки
int _fastcall tmsInsidePointCut(DOUBLEPOINT *xy1, DOUBLEPOINT *xy2,
                                DOUBLEPOINT * point, double precision/* = DELTANULL*/);

// Пересечение двух отрезков
// xy1,xy2 - первый отрезок,
// xy3,xy4 - второй отрезок
// point1,point2  - точки пересечения
// Возврат : 1 - одна точка пересечения,
//           2 - отрезок xy1,xy2 лежит  на отрезке xy3,xy4
// При отсутствии точки пересечения или ошибке возвращает ноль
int _fastcall tmsCrossCutData(TMEASUREDATA *measuredata,
                              DOUBLEPOINT *xy1, DOUBLEPOINT *xy2,
                              DOUBLEPOINT *xy3, DOUBLEPOINT *xy4,
                              DOUBLEPOINT *point1, DOUBLEPOINT *point2,
                              double precision/* = DELTANULL*/);

// Положение точки относительно отрезка
// Возвращает FIRST, SECOND, BEHIND, BEYOND, BETWEEN, LEFT, RIGHT
// При ошибке возвращает 0
int _fastcall tmsPointPositionNearCut(DOUBLEPOINT *point,
                                      DOUBLEPOINT *xy1,
                                      DOUBLEPOINT *xy2,
                                      double precision);  

// Положение точки относительно прямой
// Возвращает FIRST, SECOND, LEFT, RIGHT
// При ошибке возвращает 0
int _fastcall tmsPointPositionNearLine(DOUBLEPOINT *point,
                                       DOUBLEPOINT *xy1,
                                       DOUBLEPOINT *xy2);

// Положение (сторона) точки относительно прямой
// Возвращает LEFT, RIGHT
// При ошибке возвращает 0
int _fastcall tmsPointSideNearLine(DOUBLEPOINT *point,
                                   DOUBLEPOINT *xy1,
                                   DOUBLEPOINT *xy2);

// Определить положение точки на отрезке, делящей отрезок
// в отношении m1/m2
// При ошибке возвращает 0
int _fastcall tmsPointPositionOnCut(DOUBLEPOINT *point,
                                    DOUBLEPOINT *p1,
                                    DOUBLEPOINT *p2,
                                    double m1, double m2);

// Вычисление длины катетов в прямоугольном треугольнике
//  radius - гипотенуза,
//  angle  - угол в радианах
double _fastcall tmsRcosInt(int radius, double angle);
double _fastcall tmsRsinInt(int radius, double angle);

double _fastcall tmsRcosDouble(double radius, double angle);
double _fastcall tmsRsinDouble(double radius, double angle);

// Определение двух точек по перпендикуляру от отрезка (point1-point2)
// на расстоянии distance от точки point (по умолчанию point1)
int _fastcall tmsSeekPointNormalLine(DOUBLEPOINT *point1,
                                     DOUBLEPOINT *point2,
                                     DOUBLEPOINT *pointout1,
                                     DOUBLEPOINT *pointout2,
                                     double distance, DOUBLEPOINT *point/* = 0*/);

// Посчитать коэффициенты уравнения линии A,B,C
void _fastcall tmsCalcFactor(TMEASUREDATA *measuredata,
                             DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);

// Найти точку пересечения отрезка с линией ,
// заданной коэффициентами A,B,C
// xy1,xy2 - отрезок
// point - вычисленная точка пересечения
// возврат 1 - точка пересечения существует, 0 - нет
int _fastcall tmsCrossCutLine(TMEASUREDATA *measuredata,
                              DOUBLEPOINT *xy1, DOUBLEPOINT *xy2,
                              DOUBLEPOINT *point);

// Принадежность точки линии,
// заданной коэффициентами A,B,C
// point -  точка
// возврат 0 - точка принадлежит линии
double _fastcall tmsInsidePointLine(TMEASUREDATA *measuredata,
                                    DOUBLEPOINT *point);


//=================================================================
// "Безопасные" математические функции с защитой от зависаний.
//=================================================================

// При fabs(x) < DOUBLENULL и fabs(y) < DOUBLENULL возвращает 0
double tmsAtan2(double y, double x);

// При x < 0 возвращает 0
double tmsSqrt(double x);
//=================================================================


#ifdef __cplusplus

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  КЛАСС "РАСЧЕТ ПАРАМЕТРОВ ОБ'ЕКТА"  +++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TMeasure: public TMEASUREDATA
{
  public :

  TMeasure();

  // Угол между прямыми (p11,p12) и (p21,p22) в радианах
  // Возвращает модуль угла:
  //   0    - прямые параллельны
  //   PI/2 - прямые перпендикулярны
  //  -1    - точки одного из отрезков совпадают, либо не заданы
  double AngleBetweenLines(DOUBLEPOINT *p11, DOUBLEPOINT *p12,
                           DOUBLEPOINT *p21, DOUBLEPOINT *p22);

  // Определение угла наклона биссектрисы угла, заданного
  // точками p1,p2,p3 с вершиной в точке p2

  double BisectorAngle(DOUBLEPOINT *p1, DOUBLEPOINT *p2,
                       DOUBLEPOINT *p3);

  // Определение центра окружности по трем точкам
  //  pc - точка центра
  // Возвращает радиус окружности (0.0 - три точки совпадают,
  //                              -1.0 - точки на одной прямой)

  double CircleCenter(DOUBLEPOINT *p1, DOUBLEPOINT *p2,
                      DOUBLEPOINT *p3, DOUBLEPOINT *pc);

  // Вычисление расстояния между двумя точками

  double Distance(DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);

  // Вычисление расстояния между точкой и прямой,
  // заданной двумя точками

  double Distance(DOUBLEPOINT *point, DOUBLEPOINT *xy1,
                                      DOUBLEPOINT *xy2);

  // Вычисление дирекционного угла в радианах

  double DirectionAngle(DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);

  // Определение входимости точки с координатами x,y
  // в объект/подобъект
  // возврат: 1-точка внутри объекта/подобъекта,
  //          2-точка внешняя,
  //          3-точка совпадает с точкой метрики,
  //          4-точка лежит на отрезке метрики,
  //          0 - непутевая метрика
  // point   - координаты точки

  int InsidePointCut(DOUBLEPOINT *xy1, DOUBLEPOINT *xy2,
                     DOUBLEPOINT *point, double precision = DELTANULL);

  // Пересечение двух отрезков
  // xy1,xy2 - первый отрезок,
  // xy3,xy4 - второй отрезок
  // point1,point2  - точки пересечения
  // Возврат : 1 - одна точка пересечения,
  //           2 - отрезок xy1,xy2 лежит  на отрезке xy3,xy4
  // При отсутствии точки пересечения или ошибке возвращает ноль

  int CrossCutData(DOUBLEPOINT *xy1, DOUBLEPOINT *xy2,
                   DOUBLEPOINT *xy3, DOUBLEPOINT *xy4,
                   DOUBLEPOINT *point1, DOUBLEPOINT *point2,
                   double precision = DELTANULL);

  enum {
         FIRST   = tmsFIRST,  // совпадает с первой точкой отрезка
         SECOND  = tmsSECOND, // совпадает со второй точкой отрезка
         BEHIND  = tmsBEHIND, // лежит позади первой точки отрезка
         BEYOND  = tmsBEYOND, // лежит впереди второй точки отрезка
         BETWEEN = tmsBETWEEN,// лежит на отрезке (между точками)
         LEFT    = tmsLEFT,   // слева
         RIGHT   = tmsRIGHT   // справа
       };

  // Положение точки относительно отрезка
  // Возвращает FIRST, SECOND, BEHIND, BEYOND, BETWEEN, LEFT, RIGHT
  // При ошибке возвращает 0

  int PointPositionNearCut(DOUBLEPOINT *point,
                           DOUBLEPOINT *xy1, DOUBLEPOINT *xy2,
                           double precision = DELTANULL); 

  // Положение точки относительно прямой
  // Возвращает FIRST, SECOND, LEFT, RIGHT
  // При ошибке возвращает 0

  int PointPositionNearLine(DOUBLEPOINT *point,
                            DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);

  // Положение (сторона) точки относительно прямой
  // Возвращает LEFT, RIGHT
  // При ошибке возвращает 0

  int PointSideNearLine(DOUBLEPOINT *point,
                        DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);

  // Определить положение точки на отрезке, делящей отрезок
  // в отношении m1/m2
  // При ошибке возвращает 0

  int PointPositionOnCut(DOUBLEPOINT *point,
                         DOUBLEPOINT *p1, DOUBLEPOINT *p2,
                         double m1, double m2);

  // Вычисление длины катетов в прямоугольном треугольнике
  //  radius - гипотенуза,
  //  angle  - угол в радианах

  double Rcos(int radius, double angle);
  double Rsin(int radius, double angle);

  double Rcos(double radius, double angle);
  double Rsin(double radius, double angle);

  // Определение двух точек по перпендикуляру от отрезка (point1-point2)
  // на расстоянии distance от точки point (по умолчанию point1)

  int SeekPointNormalLine(DOUBLEPOINT *point1, DOUBLEPOINT *point2,
                          DOUBLEPOINT *pointout1, DOUBLEPOINT *pointout2,
                          double distance, DOUBLEPOINT *point = 0);

 protected :

  // Посчитать коэффициенты уравнения линии A,B,C

  void CalcFactor(DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);

  // Найти точку пересечения отрезка с линией ,
  // заданной коэффициентами A,B,C
  // xy1,xy2 - отрезок
  // point - вычисленная точка пересечения
  // возврат 1 - точка пересечения существует, 0 - нет

  int CrossCutLine(DOUBLEPOINT *xy1, DOUBLEPOINT *xy2,
                   DOUBLEPOINT *point);

  // Принадежность точки линии,
  // заданной коэффициентами A,B,C
  // point -  точка
  // возврат 0 - точка принадлежит линии

  double InsidePointLine(DOUBLEPOINT *point);

};

#else

typedef  TMEASUREDATA  TMeasure;


#endif // __cplusplus

#endif // MEASURE_H

