#ifndef MAPOBJEX_H
#define MAPOBJEX_H

 typedef struct RSCSELSEG
 {
  unsigned long    Segment ;       // �0��� ���� ( �� ����� 255)
  unsigned char    Name[32] ;      // �������� ( �� ����� 30)
  unsigned long    ObjectIncode ;  // ���������� ��� �������
 }
                RSCSELSEG;

 //����� ���� ��������������
 //���������� IDOK ��� �������� ���������� ������� ������
 //���  IDCANCEL � ��������� ������
/*
 long int _import WINAPI  dialogCopyRscObject(TWindow* parent, int resId,
                               TObjectInfo* info, TMapRsc* maprsc,
                               RSCSELSEG* parm,
                               TModule* resourcemodule);
  */
#endif    //MAPOBJEX_H
