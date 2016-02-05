
#ifndef DECIMGED_H
#define DECIMGED_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifndef MAPGDI_H
  #include "mapgdi.h"    // (146) � (57) - �������
#endif

#define IMGBUFFERSIZE (4 * 1024L)
#ifdef __cplusplus
class _DLLCLASS  TDecorImageEdit
{


 /*********************************************************
 *                                                        *
 *       ������� ������������� ������ ������              *
 *                                                        *
 *********************************************************/

 public :

 // ���������� ����� ������ ������

  TDecorImageEdit()
   {
	    Memory = 0; // ������ �� �������������
  	  SetBuffer(0,0L);
   }

  TDecorImageEdit(char * parm,long int length)
  	{
     Memory = 0; // ������ �� �������������
     SetBuffer(parm,length);
  	}

  TDecorImageEdit(TDecorImageEdit * data)
   {
     Memory = 0; // ������ �� �������������
     Load(data);
  	}


  ~TDecorImageEdit() { SetBuffer(0,0L); }

 // ��������� ����� ������ ������

  char * Address() { return (char *)Decor;}

 // ������������������� ��������� ������
 // ��� ������ ���������� ����

 int Create();

 // �������� ������

 int Clear();

 // ���������/���������� ������� �������������� ������

  int IsDirty() { return Isdirty; }

  int IsDirty(int dirty) { return (Isdirty = dirty && 1); }

 // ��������� ������� ��������� ��������
  int IsVect();

 // ��������� ����� ������

  int Length()
   {
     if (Decor == 0) return 0;
     return Decor->Length;
   }

 // ��������� ������ �� ��������� ������
 // ������ ������ 64 �� �� �����������
 // ��� ������ ���������� ����,
 // ����� - ����� ����������� ������

  int Load(IMGDECORATELINE * decor);

 //  ��������� �������� ������������ ������� �� ��������� ������
 //  ������ ���� IMGDECORATE
 //  ������ ������ 64 �� �� �����������                 
  int Load(IMGDECORATE * decor);

  int Load(TDecorImageEdit * decor)
     {
       return Load((IMGDECORATE *)(decor->Address()));
     }

 // ���������� ����� ������ ������
 // address - ����� ������, length - ����� ������.
 // ������ ���������� Allocate() �������������.

  void SetBuffer(char * address,long int length);

 // ��������� ������ �� ��������� ������
 // ���� ������ ������ ���������� �������,
 // �� �������� �� ������������
 // ��� ������ ���������� ����,
 // ����� - ����� ����������� ������

  int Unload(char * address,int length);

 protected :

 // �������� ������ ��� ������ �������
 // ������������������� ��������� ������
 // ��������� ������������� ������
 // ������ ������������� ������������� � �����������
 // ��� ��� ���������� ������ ������� � �������
 // SetBuffer(...), � ��� �����, SetBuffer(0,0).
 // ��� ������ ���������� ����

  int Allocate(int size = IMGBUFFERSIZE);

 // ��������� ������ ������ �������
 // ��� ������ ���������� ����, ����� - ����� ������ ������

 int Realloc();

 /*********************************************************
 *                                                        *
 *     ����������� ��������� �� ������ �������            *
 *                                                        *
 *********************************************************/

 public :

 // ���������� ��������� �� ������ ���������� �������� �����
 // number - ���������������� ����� �����,(1-7)
 // ��� ������ ���������� ����

 char * DatePart(int number = 1);

  // ���������� ��������� �� ���������� �����
  // ��� ������ ���������� ����

  char * GoPart(int number = 0);


 /*********************************************************
 *                                                        *
 *         ������ ������ �� ������� �����                 *
 *       (� ������������ � ������� ���������� ���������)  *
 *                                                        *
 *********************************************************/

 public :

 // ��������� ����� ���������� ����������� ������� �����
 // ��� ������ ���������� ����

 int ParmLength()
 {
   if (DescPart == 0) return 0;
  	return ((IMGDECOR *)DescPart)->Length - sizeof(IMGDECOR);
 };

 // ��������� ����� ������� �����
 // ����� ������� ��������� 1,
 // (DO_BASE,DO_END, ... - ��. mapgdi.h)
 // ���� �� ����������� ���������� 0

 int NumberPart() { return NumberOfPart; }

 // ��������� ������� ����������� ������� �����
 // ��� ������ ���������� ����

 int Number()
	 {
  		if (DescPart == 0) return 0;
  		return ((IMGDECOR *)DescPart)->Number;
	 }


 /*********************************************************
 *                                                        *
 *         ������� �������������� ��������� ������        *
 *                                                        *
 *********************************************************/

 public :

 // ������� �������� �����
 // ������� ���������� ������ �����
 // ��� ������ ���������� ����

 ptrdiff_t DeletePart(int number);

 // ��������� �����
 // ������ ����� ���������� �������
 int LoadPart(int imglength,int imgnumber,char *data,
                              int number);

 // ��������� ������ �� ��������� �����
 // ���� ������ ������ ���������� �������,
 // �� �������� �� ������������
 // ��� ������ ���������� ����,
 // ����� - ����� ����������� ������

  int UnloadPart(char * address,int length,int numberpart);

  // ��������� ������

  TDecorImageEdit * operator = (TDecorImageEdit * image)
	    {
       if (Load(image)) return image;
       return 0;
     }

   IMGDECORATELINE * operator = ( IMGDECORATELINE * data)
	    {
       if (Load(data)) return data;
       return 0;
     }

    IMGDECORATE * operator = ( IMGDECORATE * data)
	    {
       if (Load(data)) return data;
       return 0;
     }

   /*VIEPAR * operator = (VIEPAR * data)
    {
      if (Load(data)) return data;
      return 0;
    }*/

protected :

  // ���������� ����� ������ ������

  char * operator = (char * address)
	    {
       return (char *)(Decor = ( IMGDECORHEAD *)address);
     }


protected :

 IMGDECORHEAD * Decor;   // ����� ������
 long int BufferLength;  // ������ ������ ������
 int NumberOfPart;       // ������� ����� �����
 char * DescPart;        // ��������� �� ��������� �����
 char * Memory;          // ������ ��������� ������ � �����������
                								 // (���� != 0, ����������)
 int Isdirty;            // ������� �������������� ������

};

#endif //__cplusplus
#endif

