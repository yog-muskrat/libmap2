#ifndef MAPVIEWZ_H
#define MAPVIEWZ_H

#include "maptype.h"
#include "mapacces.h"


// Вычисление длины объекта c учетом рельефа
double _fastcall LengthWithHeight(TMapAccess* mapacc,TObjectInfo *info);
void HeightArray(double *array, int count);

// Вычисление площади объекта с учетом рельефа
double _fastcall SquareWithHeight(TMapAccess* mapacc,TObjectInfo *info);
double SquareElem(TMapAccess* mapacc,TObjectInfo * info, int elem);

// Определение видимости из точки point1 точку point2       
long int _fastcall VisibilityFromPoint(TMapAccess* mapacc,DOUBLEPOINT * point1,
                                       DOUBLEPOINT * point2,double deltaheight);



// Класс:  Построение зоны видимости по матрице высот
class _DLLCLASS TVisibilityZ
{
  public :

  TVisibilityZ();
 ~TVisibilityZ();
 
  // Построить метрику(сектор) по точке, азимуту, углу и радиусу
  int CreateNewInfo();

  int BuildSection(TMapAccess* mapacc, char * namerst,
                   TBUILDZONEVISIBILITY *zonevisibility);
  int Vidio();
  int VidioB();
  void PointSource();
  int Line(long x1,long y1,long x2,long y2);
  int LineA(long x1,long y1,long x2,long y2);
  int LineB(long x1,long y1,long x2,long y2);

  TObjectInfo Info;
  TRst Rst;
  TMapAccess* MapDoc;
  
  DOUBLEPOINT  FirstPoint;
  DOUBLEPOINT  PointCenter; // Координаты центра
  double MeterInElement;
  double HeigthCenter;
  double locatX,locatY,Tmax;
  double Azimuth;
  double Angle;
  double RadiusMeter;
  double DeltaObservation;
  long int Precision,Scale;
  long Colord,Inicol;
  int Height;
  int NumberRst;
  int xx,yy;
};
#endif
