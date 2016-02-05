
#if !defined(MAPDRW_H)
#define MAPDRW_H

#ifndef MAPMACRO_H
  #include "mapmacro.h"
#endif

#ifndef MAPGDI_H
  #include "mapgdi.h"
#endif

#define DRAWBUFFERSIZE (4*1024L)  // ����������� ������ ������ !


// �������� ������� ����������� ��'����
// ----------------------------------------------
//  ����������� ����� �������� :  (��. MAPGDI.H)
//   - ��� IMG_LINE   : 16 ����,
//   - ��� IMG_SQUARE : 12 ���� ...

#define DRAWIDENT 0x7FFF7FFE


// ��������� ����� ������� ���������
// ��� ������ ���������� 0
char *  _fastcall drawBeginData(IMGDRAW * draw);

// ��������� ������ �������� ������
// ��� ������ ���������� 0
int _fastcall drawDataLength(IMGDRAW * draw);

// ��������� ������ ����� ������
// ��� ������ ���������� 0
int _fastcall drawLength(IMGDRAW * draw);

// ��������� ����� ���������� �� ������ ������� � �� ����������
// ��� ������ ���������� 0
int _fastcall drawElementParmLength(int image, const char * point);

// ��������� ����� ���������
// �� ����������������� ������ (������� � 1)
// ��� ������ ���������� 0
char * _fastcall drawElementAddress(IMGDRAW * draw, int number);

// ��������� ������� ����������� ���������
// �� ����������������� ������ (������� � 1)
// ��� ������ ���������� 0
int _fastcall drawElementFunction(IMGDRAW * draw, int number);

// ��������� ��������� ������� ����������� � ������ ����������
// ��� ������ ���������� 0
int _fastcall drawCheckElementFunction(int function);



typedef struct DRAWEDIT        // �������������� ������������ ��������
{
 IMGDRAW *   Base;             // ����������� �������� �������
 long int    BufferLength;     // ������ ������ ������������ ��������
 char *      Memory;           // ������ ��������� ������ � �����������
                								       // (���� != 0, ����������)
 int         NumberOfElement;  // ������� ����� �������� (������� � 1)
 int         Isdirty;          // ������� �������������� ������
}
  DRAWEDIT;

// ����������� ������
void _fastcall dredInit(DRAWEDIT * data);

// ���������� ������
void _fastcall dredFree(DRAWEDIT * data);

// �������� ������ ��� ������������ ������ �������
// ������������������� ��������� ������
// ������ ������������� ������������� � �����������
// ��� ��� ���������� ������ ������� � �������
// SetBuffer(...), � ��� �����, SetBuffer(0,0).
// ��� ������ ���������� ����
int _fastcall dredAllocate(DRAWEDIT * data, int size); 

// ������������������� ��������� ������
// ��� ������ ���������� ����
int _fastcall dredClear(DRAWEDIT * data);

// ���������� ��������� ������ ������
// address - ����� ������, length - ����� ������.
// ������ ���������� Allocate() �������������.
void _fastcall dredSetBuffer(DRAWEDIT * data, char * address,
                             long int length);

// ��������� �������� �� ��������� ������
// ��� ������ ���������� ����, ����� - ����� ����������� ������
int _fastcall dredLoad(DRAWEDIT * data, IMGDRAW * draw);

// ��������� �������� �� ��������� ������ ����������
// ���������� ������� (IMG_LINE ...)
// ������ ������ DRAWBUFFERSIZE �� �����������
// ��-��������� ����������� ������ "���������������� �������"
// ��� ������ ���������� ����, ����� - ���������� ����������� ����������
int _fastcall dredLoadParm(DRAWEDIT * data, int image, const char * parm);

// ��������� ����� ���������� ��������� �� ��� ������ (����� � 1)
// ��� ������ ���������� 0
int _fastcall dredElementParmLength(DRAWEDIT * data, int number);

// ��������� ������� �� ��������� � �������� ��
// ���������� ����� ����������� ���������� ��� ����
int _fastcall dredFunc2Elements(DRAWEDIT * data, int image,
                                const char * parm);

// ���������� �������  ������ - �e�����
// 1 - ������� �� �������, 0 - ���
int _fastcall dredSetSpline(DRAWEDIT * data, int spline);

// �������� ����� ������� �������� �������
// ��� ������ ���������� ����,����� - ����� ��������� � ������
int _fastcall dredAppendElement(DRAWEDIT * data, int image,
                                const char * parm);

// ������� ������� �������� �������
// number - ����� �������� (������� � 1)
// ��� ������ ���������� ����
int _fastcall dredDeleteElement(DRAWEDIT * data, int number);

// ��������� ��� ���������� ���������
// �� ��� ������ (����� � 1) (IMG_LINE, IMG_DOT, ...)
// ��� ������ ���������� 0
int _fastcall dredElementIdent(DRAWEDIT * data,int number);

// ��������� ����� ���������� ���������
// �� ��� ������ (����� � 1)
// ��� ������ ���������� 0
char * _fastcall dredElementParmAddres(DRAWEDIT * data,int number);


#ifdef __cplusplus

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  ����������� �������� ��'���� �����  ++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TObjectDraw
{                         // ***********
                          // ** DRAW ***
 public :                 // ***********

 // ���������� ����� ������ ������� �������
 TObjectDraw(IMGDRAW * addr)
   {
     Base = addr;
   }

 TObjectDraw(char * addr)
   {
     Base = (IMGDRAW *)addr;
   }

 TObjectDraw(const int addr)
   {
     Base = (IMGDRAW *)addr;
   }

 TObjectDraw()
   {
     Base = 0;
   }

 // ��������� ����� ������ ������
 // ��� ������ ���������� 0
 char * Address() { return (char *)Base; }

 // ��������� ����� ������� ���������
 // ��� ������ ���������� 0
 char * BeginData()
   {
     if (Base == 0) return 0;
     return (char *) &(Base->Image);
   }

 // ��������� ������ �������� ������
 // ��� ������ ���������� 0
 int DataLength()
   {
     int length = Length();
     if (length == 0) return 0;
     return (length - sizeof(IMGDRAW) + sizeof(IMGDECOR)+
                      sizeof(Base->Parm));
   }

 // ��������� ����� ���������� � ������ ����
 // ��� ������ ���������� 0
 int Count()
   {
     if (Base == 0) return 0;
     return Base->Count;
   }

 // ��������� ������������ ��������� ������
 // ��� ������ ���������� 0
 int IsCorrect()
   {
     if (Base == 0) return 0;
     return (Base->Ident == DRAWIDENT);
   }

 // ��������� ������ ����� ������
 // ��� ������ ���������� 0
 int Length()
   {
     if (Base == 0) return 0;
     return Base->Length;
   }

 // ��������� ����� ���������
 // �� ����������������� ������ (������� � 1)
 // ��� ������ ���������� 0
 char * ElementAddress(int number = 1);

 // ��������� ��� ���������� ���������
 // �� ��� ������   (IMG_LINE, IMG_DOT, ...)
 // ��� ������ ���������� 0
 int ElementIdent(char * point)
   {
     if (point == 0) return 0;
     return ((IMGDECOR *)point)->Number;
   }

 // ��������� ����� ���������� ���������
 // �� ��� ������
 // ��� ������ ���������� 0
 char * ElementParmAddress(char * point)
   {
     if (point == 0) return 0;
     return (point + sizeof(IMGDECOR));
   }

 // ��������� ������ ����� ��������� �� ��� ������
 // ��� ������ ���������� 0
 int ElementLength(char * point)
   {
     if (point == 0) return 0;
     return  ((IMGDECOR *)point)->Length;
   }

 // ��������� ������ ����� ��������� �� ������ ������� � ����������
 // ��� ������ ���������� 0
 int ElementLength(int image, char *point)
   {
     if (point == 0) return 0;
     return (ElementParmLength(image,point)) + sizeof(IMGDECOR);
   }

 //  ��������� ����� ���������� �� ������ ������� � �� ����������
 //  ��� ������ ���������� 0
 int ElementParmLength(int image, char *point);

 // ���������� ����� ������ ������
 char * operator = (char * Addr)
   {
     return (char *)(Base = (IMGDRAW  *)Addr);
   }

 // ���������� ����� ������ ������
 char * operator = (IMGDRAW * Addr)
   {
     return (char *)(Base = Addr);
   }

 // ��������� ��������� �� ������
 int operator == (int Value)
   {
     return (Base == (IMGDRAW  *)Value);
   }

 int operator != (int Value)
   {
     return (Base != (IMGDRAW  *)Value);
   }

 public :

 IMGDRAW * Base;

};

#else

typedef struct TObjectDraw
{
  IMGDRAW *  Base;  // ��������� �� ������� (���������� �����)
}
  TObjectDraw;

#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++ �������������� ������������ �������� ��'���� ����� ++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifdef __cplusplus

class _DLLCLASS TDrawEdit : public DRAWEDIT
{
 /*********************************************************
 *                                                        *
 *       ������� ������������� ������ ������              *
 *                                                        *
 *********************************************************/

 public :

 // ���������� ����� ������ ��������
 TDrawEdit(char * address,long int length = 0)
  	{
     Memory = 0;
     SetBuffer(address,length);
  	}

 TDrawEdit() 
   {
     Memory = 0;
  	  SetBuffer(0,0L);
   }

 TDrawEdit(TObjectDraw draw)
   {
     Memory = 0;
     SetBuffer(draw.Address(),draw.Length());
  	}

 TDrawEdit(int number,char * point)
   {
     Memory = 0;
     Load(number,point);
   }

 ~TDrawEdit() { SetBuffer(0,0L); }


 // ��������� ����� ������ ������
 // ��� ������ ���������� 0
 char * Address() { return (char *)Base; }

 // ��������� ����� ������� ���������
 // ��� ������ ���������� 0
 char * BeginData()
   {
     if (Base == 0) return 0;
     return (char *) &(Base->Image);
   }

 // ��������� ������ �������� ������
 // ��� ������ ���������� 0
 int DataLength()
   {
     if (Base == 0) return 0;
     int length = Base->Length;
     if (length == 0) return 0;
     return (length - sizeof(IMGDRAW) + sizeof(IMGDECOR)+
                      sizeof(Base->Parm));
   }

 // ��������� ����� ���������� � ������ ����
 // ��� ������ ���������� 0
 int Count()
   {
     if (Base == 0) return 0;
       return Base->Count;
   }

 // ��������� ������������ ��������� ������
 // ��� ������ ���������� 0
 int IsCorrect()
   {
     if (Base == 0) return 0;
     return (Base->Ident == DRAWIDENT);
   }

 // ��������� ������ ����� ������
 // ��� ������ ���������� 0
 int Length()
   {
     if (Base == 0) return 0;
     return Base->Length;
   }


 // �������� ������ ��� ������������ ������ �������
 // ������������������� ��������� ������
 // ������ ������������� ������������� � �����������
 // ��� ��� ���������� ������ ������� � �������
 // SetBuffer(...), � ��� �����, SetBuffer(0,0).
 // ��� ������ ���������� ����
 int Allocate();

 // ������������������� ��������� ������
 // ��� ������ ���������� ����
 int Clear();

 int Create()
 {
   if (Base != 0) return Clear();
   return Allocate();
 }

 // ��������� �������� �� ��������� ������
 // ������ ������ DRAWBUFFERSIZE �� �����������
 // ��� ������ ���������� ����, ����� - ����� ����������� ������
 int Load(TObjectDraw draw);
 int Load(TDrawEdit * draw)
 { if (draw) return Load(draw->Base);
   return 0; }

 // ��������� �������� �� ��������� ������ ����������
 // ���������� ������� (IMG_LINE ...)
 // ������ ������ DRAWBUFFERSIZE �� �����������
 // ��� ������ ���������� ����, ����� - ���������� ����������� ����������
 int Load(int image,char * param);

 // ���������� ��������� ������ ������
 // address - ����� ������, length - ����� ������.
 // ������ ���������� Allocate() �������������.
 void SetBuffer(char * address,long int length);

 // ���������/���������� ������� �������������� ������
 int IsDirty() { return Isdirty; }
 int IsDirty(int dirty) { return (Isdirty = dirty && 1); }

 // ��������� �������  ������ - �e�����
 int IsSpline() {return ((Base->Flags)& IMGD_SPLINE);}

 // ���������� �������  ������ - �e�����
 // 1 - ������� �� �������, 0 - ���
 int SetSpline(int spline);

 // �������� "�������" ���� �������� ��������        
 int SetTopColor(int color);

 /*********************************************************
 *                                                        *
 *      �������������� ������������ �������� �������      *
 *                                                        *
 *********************************************************/

 public :

 // �������� ����� ��������
 // ��� ������ ���������� ����,����� - ����� ���������� � ������
 int AppendElement(int image,char * parm);

 // ��������� ����� �������� ���������
 int CurrentNumber()
   {
     return NumberOfElement;
   }

 // ������� ��������
 // number - ����� ��������� (������� � 1)
 // ��� ������ ���������� ����
 int DeleteElement(int number);

 // �������� - ������� ������ � ������ ����������
 // ���������� 1,���� ��� �������� - ����� 0
 int IsElement(int image);

 // �������� - ������� ������ � ������ ������������ ����������
 // ���������� 1,���� ��� �������� - ����� 0
 int IsPaintElement(int image);

 // ��������� ����� ���������
 // �� ��� ����������������� ������ (������� � 1)
 // ��� ������ ���������� 0
 char * ElementAddress(int number = 1);

 // ��������� ��� ���������� ���������
 // �� ��� ������ (����� � 1) (IMG_LINE, IMG_DOT, ...)
 // ��� ������ ���������� 0
 int ElementIdent(int number);

 // Bc������ ����� �������� �� ������
 // ��� ������ ���������� ����,����� ����� ��������� � ������
 int InsertElement(int number,int image,char * parm);

 // �������� ��������
 // ��� ������ ���������� ����,����� ����� ��������� � ������
 int ReplaceElement(int number,int image,char * parm);

 // ����������� ��������
 // ��  ����� ����� (����� � 1)
 // ��� ������ ���������� 0
 int ElementMove(int oldnumber,int newnumber);

 // �������� ����� ������� �������� �������  c �������������� ����������
 // ��� ������ ���������� ����,����� - ����� ��������� � ������
 int AppendElementWithInit(int image);

 // Bc������ ����� �������� �� ������  c �������������� ����������
 // ��� ������ ���������� ����,����� ����� ��������� � ������
 int InsertElementWithInit(int number,int image);

 // �������� ��������  �� ������  c �������������� ����������
 // ��� ������ ���������� ����,����� ����� ��������� � ������
 int ReplaceElementWithInit(int number,int image);

 // ������������� �������
 int Init(int image,char * parm);

 // ������������� ������� c ������ ���������� ����������
 // number - ����� ���������, image - ����� ��������, work - ��� ���������
 // ���������� 1,���� ���-�� ��������, ����� 0
int ReplaceInit(int number,int image,char * work);              

 // ��������� ����� ���������� ���������
 // �� ��� ������ (����� � 1)
 // ��� ������ ���������� 0
 char * ElementParmAddress(int number);

 // ��������� ����� ���������� ��������� �� ��� ������ (����� � 1)
 // ��� ������ ���������� 0
 int ElementParmLength(int number);

 // ��������� ����� ��������� �� ��� ������ (����� � 1)
 // ��� ������ ���������� 0
 int ElementLength(int number);

 protected:

 // ��������� ���������� ������� �� ��������� � �������� ��
 // ������� - ����� ����������� ����������
 int Func2Elements(int image,char * parm);

 public:

 // ���������� ����� ������ ������
 char * operator = (char * address)
	    {
       if (address == 0) SetBuffer(0,0L);
         else SetBuffer(address,((IMGDRAW  *)address)->Length);
       return address;
     }

 // ��������� ��������� �� ������
 int operator == (int Value)
   {
     return (Base == (IMGDRAW  *)Value);
   }

 int operator != (int Value)
   {
     return (Base != (IMGDRAW  *)Value);
   }

 operator TObjectDraw()
    {
      return Base;
    }

};

//+++++++++++++++++++++++++++
//+++++ ������ �������� +++++
//+++++++++++++++++++++++++++
class _DLLCLASS TFontDraw
{
public:
   // ��������� ������ ������� 64
   virtual int getHeight() const = 0;
   virtual int getWidth() const = 0;
   virtual int getAscent() const = 0;
   virtual int getDescent() const = 0;
   virtual int getInterval() const = 0;
   
   virtual char* getCharWidth() const = 0;
	        
   // �������� ������ �������� ���� ������� � ������� �� ���� X � Y.
   // ������� ����� ���� ����� ��������� � ����� (100-64)/2
   virtual int getShiftInMatrix() const = 0;
		 
   // C������� �� ��� Y
   virtual int getShiftFromTop() const = 0;
   virtual int getShiftFromMiddle() const = 0;
   virtual int getShiftFromBase() const = 0;
   virtual int getShiftFromBottom() const = 0;
   
   // ��������� ��������� �� ������ ����������� �������
   virtual char* getCharRaster(int number) const = 0;
   
   // ��������� ������ �������
   virtual double getCharWidthR(int number, int height) const = 0;
   
   virtual ~TFontDraw(){}
};

extern "C"
{
// ��������� ���������� �������
_MAPIMP long int _MAPAPI mapGetDrawFontCount();

// ��������� ����� � ������� number
_MAPIMP const TFontDraw* _MAPAPI mapGetFontDraw(long int number);

} // extern "C"
#else

typedef  DRAWEDIT  TDrawEdit;

#endif  // __cplusplus

#endif

