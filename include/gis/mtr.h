
#if !defined(MTR_H)
#define MTR_H

#define LABEL_MTR 0x0052544D  // M���� ����� ������� (MTR0)

//   ������� ������� �����

struct MTR {

ULONG  Label          ;// ������������� ������
                                     // ����� (MTR0)

  LONG  MBord_X1       ;// ���������� ����� �������
  LONG  MBord_Y1       ;//    X, Y ( �� )
  LONG  MBord_X2       ;
  LONG  MBord_Y2       ;

unsigned short int  Num_Blks_Vert  ;// �-�� ������ �� ���������
unsigned short int  Num_Blks_Horz  ;//           �� �����������

unsigned short int  Blksize_Vert   ;// �-�� �����    � �����
unsigned short int  Blksize_Horz   ;//      �������� � �����

unsigned short int  Blksize_Vert_tr;// �-�� ����� � ��������� �����
unsigned short int  Blksize_Horz_tr;//   �������� � ��������� �����

unsigned short int  Matr_Size_Vert ;// �-�� �����    � �������
unsigned short int  Matr_Size_Horz ;//      �������� � �������

unsigned short int  Elem_Size      ;// ������ ��������: 1,2,4 �����

ULONG  Elem_Size_mm   ;// �-�� ����������� �� �������
unsigned short int  Num_Diskr_Elem ;// �-�� �������     �� �������


// unsigned short int   Flag       ;// � � � �    � � � � � � �

unsigned short int  TypeHeight : 1; // ��� ����� 0-�������������
                                    //           1-����������
unsigned short int  TruncBlocks: 1; // ������� ���ޣ���� ������

unsigned short int  MtrType    : 1; // ��� �-�� : 0-����������,
                                    //            1-���������
unsigned short int  Free       :13; // ������


unsigned short int  Measure     ;// ������� ��������� ������

  LONG  H_min       ;
  LONG  H_max       ;

  LONG  PseudoCode  ;
ULONG  Num_Diskr_m ;// ������������ ����-� (���/����)
  LONG  Scale       ;// �������
  signed short int  Type        ;// ��� ��������� ����-���������
unsigned char       Reserve [6] ;// ������
unsigned short int  Version     ;// ������ ���-�� �������� �������
unsigned short int  Reserve2    ;

} ;

#endif  // MTR_H
