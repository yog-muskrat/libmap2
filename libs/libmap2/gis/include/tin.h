
#ifndef TIN_H
#define TIN_H

#define VERSION_TIN      0x00010000    // ��p��� ��������� 1.0
#define LABEL_TIN        0x004E4954L

#include "mapcreat.h"
//------------------------------------------------------------------
// ��������� ����� ������� TIN
//------------------------------------------------------------------
struct TTinHeader{               // ��������� tin �����
  unsigned long Label;          // ������������� ������ ����� (TIN0)
   unsigned long TriangleCount;  // ����� �������������
  unsigned long BaseScale;      // ������� �������
  
  double            XMin;       // Tin X min (Down)
  double            YMin;       // Tin Y min (Left)
  double            XMax;       // Tin X max (Up)
  double            YMax;       // Tin Y max (Right)  
}; 

#endif   // TIN_H

