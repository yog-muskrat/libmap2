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
  // ��������� ���������� ������������ �������
  // ���������� ������� ������������� ������������ �������
  // ��� ������ ���������� 0
  int GetNextObject(TObjectInfo * data);
  // �������������� ����������� ������� � ������
  // ��� ������ ���������� 0
  int TransformationSubjects(TDataEdit* data);
  // ��� ������ ���������� 0
  int SaveObjectToSite(TDataEdit * dataObject);
  // ������� ������� (�������)
  TDataEdit * DataObject;
  HOBJ Info;   
  int FirstPoint;
  protected:
  TMapAccess * MapAccess;
  double      Precision;
  // ����������� ���������� �������/����������
  long int Direction;
  // ����������������� ��� �������
  long int Excode;
  // �������� ����������� �������
  long int Local;
  // ����� �����, �������� ����������� ����������� ������
  long int ListNumber;
};
#endif