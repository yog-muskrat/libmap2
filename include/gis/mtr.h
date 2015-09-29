
#if !defined(MTR_H)
#define MTR_H

#define LABEL_MTR 0x0052544D  // Mетка файла матрицы (MTR0)

//   ПАСПОРТ МАТРИЦЫ ВЫСОТ

struct MTR {

ULONG  Label          ;// идентификатор начала
                                     // файла (MTR0)

  LONG  MBord_X1       ;// габаритная рамка матрицы
  LONG  MBord_Y1       ;//    X, Y ( дм )
  LONG  MBord_X2       ;
  LONG  MBord_Y2       ;

unsigned short int  Num_Blks_Vert  ;// к-во блоков по вертикали
unsigned short int  Num_Blks_Horz  ;//           по горизонтали

unsigned short int  Blksize_Vert   ;// к-во строк    в блоке
unsigned short int  Blksize_Horz   ;//      столбцов в блоке

unsigned short int  Blksize_Vert_tr;// к-во строк в усеченном блоке
unsigned short int  Blksize_Horz_tr;//   столбцов в усеченном блоке

unsigned short int  Matr_Size_Vert ;// к-во строк    в матрице
unsigned short int  Matr_Size_Horz ;//      столбцов в матрице

unsigned short int  Elem_Size      ;// размер элемента: 1,2,4 байта

ULONG  Elem_Size_mm   ;// к-во миллиметров на элемент
unsigned short int  Num_Diskr_Elem ;// к-во дискрет     на элемент


// unsigned short int   Flag       ;// п о л е    ф л а ж к о в

unsigned short int  TypeHeight : 1; // тип высот 0-относительные
                                    //           1-абсолютные
unsigned short int  TruncBlocks: 1; // наличие усечённых блоков

unsigned short int  MtrType    : 1; // тип м-цы : 0-регулярная,
                                    //            1-списковая
unsigned short int  Free       :13; // резерв


unsigned short int  Measure     ;// единица измерения высоты

  LONG  H_min       ;
  LONG  H_max       ;

  LONG  PseudoCode  ;
ULONG  Num_Diskr_m ;// дискретность цифр-я (точ/метр)
  LONG  Scale       ;// масштаб
  signed short int  Type        ;// тип исходного карт-материала
unsigned char       Reserve [6] ;// резерв
unsigned short int  Version     ;// версия стр-ры паспорта матрицы
unsigned short int  Reserve2    ;

} ;

#endif  // MTR_H
