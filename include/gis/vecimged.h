#if !defined(VECIMGED_H)
#define VECIMGED_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifndef MAPGDI_H
  #include "mapgdi.h"    // (77) � (55) - �������
#endif

#define IMGBUFFERSIZE (4 * 1024L)
#ifdef __cplusplus


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  �������������� ���������� ����������� ++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ������� ��������� - �������
// X - ����� �������,
// Y - ������ ����.

class _DLLCLASS TVectorImageEdit
{
 public :

 /*********************************************************
 *                                                        *
 *       ������� ������������� ������ ������              *
 *                                                        *
 *********************************************************/

 public :

 // ���������� ����� ������ ������

  TVectorImageEdit()
   {
	    Memory = 0; // ������ �� �������������
  	  SetBuffer(0,0L);
   }

  TVectorImageEdit(IMGVECTOREX * vector)
  	{
     Memory = 0; // ������ �� �������������
     Load(vector);
  	}

  TVectorImageEdit(TVectorImageEdit * data)
   {
     Memory = 0; // ������ �� �������������
     Load(data);
  	}


  ~TVectorImageEdit() { SetBuffer(0,0L); }

 // ��������� ����� ������ ������

  char * Address() { return (char *)Vector;}

 // ������������������� ��������� ������, ����� ���������� = 0
 // ��� ������ ���������� ����

  int Create();

 // ��������� ������� ���������� �������
 // ��� ������ ���������� ����

  int GetImageSize(IMAGESIZE* imagesize);

 // ���������/���������� ������� �������������� ������

  int IsDirty() { return Isdirty; }

  int IsDirty(int dirty) { return (Isdirty = dirty && 1); }

 // ��������� ����� ������

  int Length()
   {
     if (Vector == 0) return 0;
     return Vector->Length;
   }

 // ��������� ������ �� ��������� ������
 // ������ ������ 64 �� �� �����������
 // ��� ������ ���������� ����,
 // ����� - ����� ����������� ������

  int Load(IMGVECTOREX * data);
  int Load(TVectorImageEdit * vector)
     {
       return Load((IMGVECTOREX *)(vector->Address()));
     }

 // ��������� ����� ����������,����������� ������

  int PolyCount()
  {
     if (Vector == 0) return 0;
     return Vector->Count;
   }

 // ���������� ����� ������ ������
 // address - ����� ������, length - ����� ������.
 // ������ ���������� Allocate() �������������.

  void SetBuffer(IMGVECTOREX * address,long int length = 0);

 // ��������� ������ �� ��������� ������
 // ���� ������ ������ ���������� �������,
 // �� �������� �� ������������
 // ��� ������ ���������� ����,
 // ����� - ����� ����������� ������

 int Unload(char * address,int length);

 // �������� ���� Border ������������ �������� ����� � ��� �� ����� �������
 // ������� �� �������� ���������� ������ ����������,���������� �����
 int Border();

 // ���������/���������� ������ �����                
 int GetCenter(LONGPOINT * delta);
 int SetCenter(LONGPOINT * delta);
                                                       
 // ��������� ����� ���������� ������� - ���� ����� - ������� (�������� ���) -
 // ������� ���� |IMGC_INDEX
 // ������������ ������ ��� �������������� ��������������� ������ ������
 // number - ���������� ������ � �������
 // ������� - ��������� ������� - 1

 int CorrectScrColor(int number);

 // ������� �������� ������ � ����������
 // number - ����� ������
 // color - ��������� �� ������� RSC
 // ���� - ������ ������ ����� ����

 int SCR2PRN(int number,COLORREF * color);

 // ������ ���� �������
 // 0 - �������� ����� - ����� �� ����
 // 1 - ������� RSC (���� - ������ |IMGC_INDEX )
 // 2 - ������� ��������� ����  RGB

 int KindPalette();

 // ��������� ������ �� ��������� ������ c ���������������
 // � ��������� �������
 // number - ����� ������
 // color - ��������� �� ������� RSC
 // ���� ������ ������ ���������� �������,
 // �� �������� �� ������������
 // ��� ������ ���������� ����,
 // ����� - ����� ����������� ������

 int Unload2PRN(char * address,int length,int number,COLORREF * color);

// ------------------------------------------------------------------
// ���������� ���� - COLORREF �� ������
// ------------------------------------------------------------------
unsigned long GetIndexColor(COLORREF color, COLORREF * palette,
                                         int colornumber);

// -------------------------------------------------
// ������� ��������� ������ � �������
// number - ����� ������
// color - ��������� �� ������� RSC
// ���� - ������ ������ ����� ����
// ---------------------------------------------------------
int PRN2SCR(int number,COLORREF * color);

// ------------------------------------------------ 
// �������� �������� �������,�������� ���������,��������
// ���������� ���� � ������� �����������
// ---------------------------------------------------------
int CorrectVector();

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
 *     ����������� ��������� �� ���������� �������        *
 *                                                        *
 *********************************************************/

 public :

 // ���������� ��������� �� ������ ����� ��������� ���������
 // number - ���������������� ����� ���������,
 // ������� � 1
 // ����������� �������� �� ����� ������ � ����� ������
 // ��� ������ ���������� ����

 char * FirstPoint(int number = 1);

 // ���������� ��������� �� �������� �����
 // �������� ���������
 // ����� ������ ����� 1
 // ��� ������ ���������� ����

 char * GoPoint(int number)
  {
    if ((number == NumberOfPoint) && (Point != 0)) return Point;

    if (((Point == 0) || (NumberOfPoint < 1)) &&
		      	(FirstPoint(SubjectNumber()) == 0))
    		{
		      return 0;
      }

  	 if ((number < 1) || (number > PointCount())) return 0;

  	 Point -= (NumberOfPoint-number)*sizeof(IMGVECTPOINT);

  	 NumberOfPoint = number;

  	 return (Point);
  }

 // ���������� ��������� �� �������� �����
 // ���������� ���������
 // ����� ������ ����� 1
 // ��� ������ ���������� ����

 char * GoPointSubject(int number,int subject)
  {
    if ((number == NumberOfPoint) && (Point != 0) &&
        (subject == SubjectNumber())) return Point;

    if (((Point == 0) || (NumberOfPoint < 1) ||
         (subject != SubjectNumber())) &&
		      	(FirstPoint(subject) == 0))
    		{
		      return 0;
         }

  	 if ((number < 1) || (number > PointCount())) return 0;

  	 Point -= (NumberOfPoint-number)*sizeof(IMGVECTPOINT);

  	 NumberOfPoint = number;

  	 return (Point);
  }

 // ���������� ��������� �� ��������� ����� ��������� ���������
 // number - ���������������� ����� ���������,
 // ������� � 1
 // ����������� �������� �� ����� ������ � ����� ������
 // ��� ������ ���������� ����

 char * LastPoint(int number = 1);

 // ���������� ��������� �� ��������� ����� �������
 // ������� ��� ����������
 // ��� ������ ���������� ����

 char * NextPoint()
  {
  	 if (Point == 0) return 0;
    if (NumberOfPoint >= PointCount()) return 0;
  	 NumberOfPoint++;
  	 return (char *)(Point += sizeof(IMGVECTPOINT));
  }

 // ���������� ��������� �� ���������� ����� �������
 // �������� ���������
 // ��� ������ ���������� ����

 char * PrevPoint()
  {
  	 if (Point == 0) return 0;
  	 if (NumberOfPoint <= 1) return 0;
  	 NumberOfPoint--;
  	 return (char *)(Point -= sizeof(IMGVECTPOINT));
  }

 // ����� ����� ���������,
 // ��������� � ��������
 // number - ���������������� ����� ���������,
 // ������� � 1
 // ���������� ����� ����� ��� ���� ��� ������
 // ����� ������ ����� 1

 int SeekNearPoint(int number,long x,long y,int numberpoint = 1);

 // ����� ����� �� ���� ����������
 // ��������� � ��������
 // ���������� ����� ����� ��� ���� ��� ������
 // ����� ������ ����� 1
 // ��� ����������� ������ ��������� ,
 // � ������� ������� �����,
 // ����� ������� ������� SubjectNumber()

 int SeekNearPoint(long x,long y);

 protected :

  // ���������� ��������� �� ���������� ���������
  // ��� ������ ���������� ����

  char * DescPointSubject(int number = 0);


 /*********************************************************
 *                                                        *
 *         ������ ������ �� �������� ���������            *
 *       (� ������������ � ������� ���������� ���������)  *
 *                                                        *
 *********************************************************/

 public :

 // ��������� ����� ������� ����� �������� ���������

 char * CurrentPoint() { return (char *)Point; }

 // ���������/���������� ��������� ����������� �������� ���������
 // ��� ������ ���������� ����

 char * Parm()
	 {
  		if (DescPoint == 0) return 0;
  		return (char *)&(((IMGPOLYDESC *)DescPoint)->Parm);
	 }

 char * Parm(char * parm,int length);

 // ��������� ����� ������� �����
 // ����� ������ ����� 1, ���� �� ����������� - ���������� 0

 int PointNumber() { return NumberOfPoint; }

 // ��������� ����� ����� �� ���������
 // �������� ������� �� ��������� �� ������� ��������
 // ��� ������ ���������� ����

 int PointCount()
	 {
  		if (DescPoint == 0) return 0;
  		return (int)*(long *)((char *)&(((IMGPOLYDESC *)DescPoint)->Count)+
       ((IMGPOLYDESC *)DescPoint)->Length - 4);
	 }

 // ��������� ����� ���������� ����������� �������� ���������
 // (�� ������ 4 ����)
 // ��� ������ ���������� ����

 int ParmLength();

 // ��������� ����� �������� ���������
 // ����� ������� ��������� 1,
 // ���� �� ����������� ���������� 0

 int SubjectNumber() { return NumberOfSubject; }

 // ���������/���������� ��� ������������ ��������� �������� ���������
 // (VT_SQUARE,VT_LINE, ... - ��. mapgdi.h)
 // ��� ������ ���������� ���� (VT_SQUARE)

 int Type()
	 {
  		if (DescPoint == 0) return 0;
  		return ((IMGPOLYDESC *)DescPoint)->Type;
	 }

 int Type(int type)
	 {
  		if (DescPoint == 0) return 0;
  		return (((IMGPOLYDESC *)DescPoint)->Type =
                                    (unsigned short )type);
	 }

 // ���������/���������� ��� ����� �������� ���������
 // (IMG_LINE,IMG_DOT ... - ��. mapgdi.h)
 // ��� ������ ���������� ���� (�������������� �����)

 int Image()
	 {
  		if (DescPoint == 0) return 0;
  		return ((IMGPOLYDESC *)DescPoint)->Image;
	 }

 int Image(int image)
	 {
  		if (DescPoint == 0) return 0;
  		return (((IMGPOLYDESC *)DescPoint)->Image =
                                 (unsigned short )image);
	 }

 // ��������� ���������� ������� ����� ���������
 // ��� ������ � ��������� ������ ������������ ����� 0

 long int X()
  {
    if (Point)
       return ((IMGVECTPOINT *)Point)->Hor;
    return 0;
  }

 long int Y()
  {
    if (Point)
      return ((IMGVECTPOINT *)Point)->Ver;
    return 0;
  }

 // ��������� ���������� �������� ����� ���������
 // ��� ������ � ��������� ������ ������������ ����� 0

 long int XN(int number)
  {
    GoPoint(number);
    return X();
  }

 long int YN(int number)
  {
    GoPoint(number);
    return Y();
  }

 /*********************************************************
 *                                                        *
 *         ������� �������������� ��������� ������        *
 *                                                        *
 *********************************************************/

 public :

 // ������� ��������� ������ ���������
 // ����������� �������� �� ����� ������ � ����� ������
 // ����� ����� = 0
 // ��� ������ ���������� ����

 int CreateSubject();

 // ������� �������� ��������
 // ������� ���������� ������ ����� ������� ���������
 // ��� ������ ���������� ����

 ptrdiff_t DeleteSubject(int number);


 /*********************************************************
 *                                                        *
 *         ������� ����� �������                          *
 *                                                        *
 *********************************************************/

 public :                                                     

 // ��������� ���������� ������

 int GetBlockCount();

 // ���������� ��������� �� ������ ����� ��������� �����
 // number - ���������������� ����� �����,
 // ������� � 1
 // ����������� �������� �� ����� ������ � ����� ������
 // ��� ������ ���������� ����

 char * BlockFirstPoint(int number = 1);

 // ������ ������ ������ ������� ����� (� VT_OBJECT)
 // number - ���������������� ����� �����,
 // ������� � 1
 // ��� ������ ���������� ����

 int BlockFirstSubject(int number);

 // ������ ������ ����� (� 1) � �������� ����������� ��������
 // number - ���������������� ����� ���������,
 // ������� � 1                                    

 int GetBlockNumber(int number);

 // ������ ���������� ������� ����� (� VT_OBJECT �� VT_END ������������)
 // number - ���������������� ����� �����, ������� � 1
 // ��� ������ ���������� ����

 int GetBlockSize(int number);

 /*********************************************************
 *                                                        *
 *      ������� �������������� ����� �������              *
 *                                                        *
 *********************************************************/


 public :

 // �������� ���������� ����� �� ��������
 // ����������� ����� ���������� ���������
 // � ������� ������
 // number - ����� ���������
 // ��� ���������� ����� �������������� ����� ������
 // ��� ������ ���������� ����

 int AppendPoint(int number,long int x,long int y);

 // ������� ������� ����� ���������
 // ���� ����� �� ���� - ������ �� ���������
 // ������� ���������� ����� ��������� �� ���������
 // ��� ������ ���������� ����

 int DeletePoint();

 // �������� �� ������� ���������� �����
 // ��� ������ ���������� ����

 int DeleteEqualPoint();

 // �������� ����� � ��������
 // �� ������� ������
 // ���� ����� �� ���� - ����������� ������ �����
 // ����������� ����� ���������� ������� ������
 // ��� ���������� ����� �������������� ����� ������
 // ��� ������ ���������� ����

 int InsertPoint(long int x,long int y);

 //  �������� ��� ���������� ������� ������� �� ��������
 //  �������� (delta), � ������ ���� �������
 //  center - 1 ��� ��������� �������, 0 - ��� ������
 //  ��� ������ ���������� ����                                 

 int RelocateObject(LONGPOINT * delta,int center);

 // �������� ��� ���������� ��������� ���������
 // �� �������� �������� (delta)
 // ��� ������ ���������� ����

 int RelocateSubject(int number,LONGPOINT * delta);

 // ���������� ���������� ������� ����� ���������

 void UpdatePoint(long int x,long int y)
	   {
      X(x); Y(y);
    }

 long int X(long int x)
  {
    if (Point)
      return (((IMGVECTPOINT *)Point)->Hor = x);
    return 0;
  }

 long int Y(long int y)
  {
    if (Point)
      return (((IMGVECTPOINT *)Point)->Ver = y);
    return 0;
  }

protected :

  // �������� ����� ��� �������������
  // ��� ������ ���������� ����

  int AppendFreePoint(int number);

  // �������� ����� � ������� �������
  // ��� �������������
  // ��� ������ ���������� ����

  int InsertFreePoint();

public :

  // ��������� ������

  TVectorImageEdit * operator = (TVectorImageEdit * image)
	    {
       if (Load(image)) return image;
       return 0;
     }

  IMGVECTOREX * operator = (IMGVECTOREX * data)
	    {
       if (Load(data)) return data;
       return 0;
     }

protected :

  // ���������� ����� ������ ������

  char * operator = (char * address)
	    {
       return (char *)(Vector = (IMGVECTOREX *)address);
     }


protected :

 IMGVECTOREX * Vector;   // ����� ������
 long int BufferLength;  // ������ ������ ������
 char * Point;           // ��������� ������� �����
 int NumberOfPoint;      // ����� ������� ����� ���������
                         // ���������� � 1
 int NumberOfSubject;    // ������� ����� ���������
 char * DescPoint;       // ��������� �� ��������� ���������
 char * Memory;          // ������ ��������� ������ � �����������
                								 // (���� != 0, ����������)
 int Isdirty;            // ������� �������������� ������

};

#endif   //__cplusplus
#endif

