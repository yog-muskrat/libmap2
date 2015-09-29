#ifndef MATHTRIA_H
#define MATHTRIA_H
#include "mapacces.h"
#include "mapdat.h"
class _DLLCLASS TTrianglesClippingProcess
{
 public:
  TTrianglesClippingProcess(TMapAccess * mapAccess, double precision);
  ~TTrianglesClippingProcess();
  int Load(TObjectInfo *data);
  // Отсечение следующего треугольного объекта
  // Возвращает метрику элементарного треугольного объекта
  // При ошибке возвращает 0
  int GetNextObject(TObjectInfo * data);
  // Преобразование подобъектов объекта в объект
  // При ошибке возвращает 0
  int TransformationSubjects(TDataEdit* data);
  // При ошибке возвращает 0
  int SaveObjectToSite(TDataEdit * dataObject);
  // Метрика объекта (остатки)
  TDataEdit * DataObject;
  HOBJ Info;   
  int FirstPoint;
  protected:
  TMapAccess * MapAccess;
  double      Precision;
  // Направление цифрования объекта/подобъекта
  long int Direction;
  // классификационный код объекта
  long int Excode;
  // характер локализации объекта
  long int Local;
  // Номер листа, которому принадлежит поступивший объект
  long int ListNumber;
};
#endif