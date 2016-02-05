
#ifndef RST_H  
#define RST_H

#define RSTIDN 0x00545352L

#define RSTVEROLD 0x0201
#define RSTVER    0x0202

typedef struct RST  {

ULONG IDN;     // ������������� ������ �����  0x00545352(RST0)
ULONG LEN;     // ���H� ����� � ����������
unsigned short int AVR;     // ���������� C���� �����
unsigned short int AHR;     // ���������� �������� �����
unsigned short int BVR;     // �-�� ������ �� ���������
unsigned short int BHR;     // �-�� ������ �� �����������
unsigned short int EVR;     // �-�� �����  � �����
unsigned short int EHR;     // �-�� �������� � �����
unsigned short int DVR;     // �-�� ����� � ����� ������H��� ����
unsigned short int DHR;     // �-�� �������� � ����� ������H�� ����H��
unsigned short int BSZ;     // ������ ����� (����)
unsigned short int ESZ;     // ������ �����H�� (���)
unsigned short int DSZ;     // ������ ����� ������H��� ����
unsigned short int EDZ;     // ����� �����H��� H� ����

unsigned short int FLG_BORD : 1;     // ���� ����H����HH���� �����
unsigned short int FLG_STPR : 1;     // ���� ������H�� �������� 
unsigned short int FLG_COLR : 1;     // ���� ����� ��������H��  
unsigned short int FLG_PRCN : 1;     // ���� ����H����HH���� ����� �����H��� H� ���� 
unsigned short int FLG_RESR : 12;    // ������ ������H�� ���������

  LONG RMX;     // � ����� �����
  LONG RMY;     // Y ����� �����
unsigned short int VER;     // ������ ���������  2.2
unsigned short int SER;     // ������H�� ����
unsigned short int X1 ;     // ������H��� X (|) H��H��� ������ ����
unsigned short int Y1 ;     // ������H��� Y (->) H��H��� ������ ����
unsigned short int X2 ;     // ������H��� X ����H��� ������ ����
unsigned short int Y2 ;     // ������H��� Y ����H��� ������ ����
unsigned short int X3 ;     // ������H��� X ����H��� ������� ����
unsigned short int Y3 ;     // ������H��� Y ����H��� ������� ����
unsigned short int X4 ;     // ������H��� X H��H��� ������� ����
unsigned short int Y4 ;     // ������H��� Y H��H��� ������� ����
unsigned char  COLOR  ;     // ���� ��������H�� �/� ������  
unsigned char  FLG_NEW_HEADER;  // ���� ������������� ��������� �����
                            // ��������� �� �������� LEN (0/1)

						  } RST ;

typedef struct RSTPAL  {

                        RST Rst;        // ����H�� ���������
                        char Pal[48];   // ������� ��� 16 ������

                       } RSTPAL ;    
 
#endif   // RST_H
