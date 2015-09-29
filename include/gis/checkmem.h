
#ifndef CHECKMEM_H
#define CHECKMEM_H

// ----------------------------------------------------------------------
// ������ ��������������� ������                   
// ----------------------------------------------------------------------
typedef class THandleList
{
public:

  // ������� ������
  // size    - ������ �������� ������
  // reserve - ����������� ����� ���������
  THandleList(int reserve = 512);

  ~THandleList();

  // �������� ������
  // item - ����� ������ ������
  // size - ����������� ������ (��� ������������ � size - ������)
  // ��� ������ ���������� ����
  int Append(long int item);

  // ��������� - ���� �� ����� �������
  // ���������� ����� �������� � ������ ������� � 1
  // ��� ������ ���������� ����

  int Check(long int item);

  // ����� ���������
  int Count() { return ItemCount; }

  // �������� ������
  void Clear();

  // ������� ������
  // number - ����� �������� ������� � 1
  void Delete(int number);

  // ��������� �������
  // number - ����� �������� ������� � 1
  long int Item(int number);

private:

  int Allocate(int size);

public:

  int        ItemCount;
  long int * ItemBegin;
  int        MemorySize;
  int        ItemReserve;
}
  THandleList;



#endif // CHECKMEM_H
