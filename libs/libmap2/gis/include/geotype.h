
#ifndef ERRORVALUE
 #define ERRORVALUE -1111
#endif

#ifndef GEOTYPE_H
#define GEOTYPE_H

typedef struct TEOSTAT     // ���� ����������
{
 long int BlockCount;      // ���������� ������ ������
 long int MaxBlockSize;    // ������������ ���������� ����� � �����
}
 TEOSTAT;

enum COURSETYPE            // ��� ������������ ����
{
 COURSE_UNDEFINED = 0, // �����������
 COURSE_UNLOCK    = 1, // �����������
 COURSE_CLOSE     = 2, // ���������
 COURSE_LOCK      = 3, // ���������
 COURSE_ADJOIN    = 4, // � 1-� ��������� �����
 COURSE_FREE      = 5, // ��������� (�������)
 COURSE_LINK      = 6  // � ������������ ���������
};

enum TPRTYPE    // ��� ������ ������
{
 TPR_UNDEFINED    = 0, // �����������
 TPR_INTERSECTION = 1, // �������
 TPR_POLAR        = 2, // �������
};

enum BASEPOINTTYPE    // ��� ������������� ������� �����
{
 BASE_N_X_Y_H   = 0, // N X Y H
 BASE_N_X_Y     = 1, // N X Y
 BASE_N_A       = 2, // N A
 BASE_N         = 3  // N
};

typedef struct BASEPOINT   // ������ ������� �����
{
 char Name[256];           // �������� (�����) �����
 double X;                 // X
 double Y;                 // Y
 double H;                 // H
 double A;                 // A
 double Hi;                // ������ �����������     

 long int Type;            // ��� ������ (BASE_N_X_Y_H, ...)
 long int Rezerv;          //
}
 BASEPOINT;

enum MEAPOINTTYPE          // ��� ������ ���������
{
 MEA_N_N          = 0, // N N
 MEA_N_N_A        = 1, // N N A
 MEA_N_N_A_D      = 2, // N N A D
 MEA_N_N_A_D_H    = 3, // N N A D H
};


// ���������� ��������� �.�. �� 
typedef struct MEASUREPOINT  // ������ ����� ����  (������������ ������ � TPR2)
{
 char Name1[256];      // �������� (�����) ����� �������
 char Name2[256];      // �������� (�����) ����������� �����
 double Angle;         // �������������� ���� (����� ����������)
 double Distance;      // ����������
 double dH;            // ����������
 double Ha;            // �������������� ����                   
 double Va;            // ������������ ����                     
 double Sd;            // ��������� ����������                  
 double Direct;        // ������������ ���� �� ��������� �����  
 double Ht;            // ������ ����������                     
 double Hi;            // ������ �������                        
 char Code[32];        // ������� ���                           
 int Priz;             // ������� ������ � ���� TPR             
 long int Type;        // ��� ������ (MEA_...)
 long int Rezerv;      //
}
 MEASUREPOINT;




#endif
