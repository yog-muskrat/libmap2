
#ifndef MSORDER_H
#define MSORDER_H

#ifndef MAPMACRO_H
 #include "mapmacro.h"
#endif

#define LABEL_VPO       0x004F5056

typedef struct ORDERCELL
{
  long int Layer;            // Номер "слоя"
  long int Local;            // Локализация "слоя"
}
  ORDERCELL;

typedef struct LAYERORDER    // Запись "VPO"
{
  long int  Label;            // Идентификатор начала записи LABEL_VPO
  long int  Length;           // Длина записи
  long int  Mode;             // Идентификатор состояния классификатора
  long int  Reserv;           // Резерв (=0)
  int Count;                  // Число элементов в массиве
  ORDERCELL First;            // Номер нижнего "слоя" и
                              // локализация нижнего "слоя"
                              // Далее Layer+Local числом Count-1
}
  LAYERORDER;

#endif // MSORDER_H
