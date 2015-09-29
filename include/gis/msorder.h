
#ifndef MSORDER_H
#define MSORDER_H

#ifndef MAPMACRO_H
 #include "mapmacro.h"
#endif

#define LABEL_VPO       0x004F5056

typedef struct ORDERCELL
{
  long int Layer;            // ����� "����"
  long int Local;            // ����������� "����"
}
  ORDERCELL;

typedef struct LAYERORDER    // ������ "VPO"
{
  long int  Label;            // ������������� ������ ������ LABEL_VPO
  long int  Length;           // ����� ������
  long int  Mode;             // ������������� ��������� ��������������
  long int  Reserv;           // ������ (=0)
  int Count;                  // ����� ��������� � �������
  ORDERCELL First;            // ����� ������� "����" �
                              // ����������� ������� "����"
                              // ����� Layer+Local ������ Count-1
}
  LAYERORDER;

#endif // MSORDER_H
