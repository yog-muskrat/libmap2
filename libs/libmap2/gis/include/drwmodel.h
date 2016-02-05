
#if !defined(DRWMODEL_H)
#define DRWMODEL_H

#ifndef MAPMACRO_H
  #include "mapmacro.h"
#endif

#ifndef MAPTYPE_H
 #include "maptype.h"
#endif

#ifndef M3DGDI_H
  #include "m3dgdi.h"
#endif
#ifndef M3DMODEL_H
  #include "m3dmodel.h"
#endif

#define MODELBUFFERSIZE (4*1024L)     // ����������� ������ ������ !

#define MODELIDENT  0x73DA73DA       // ������������� ������

#define MODELRECORDLIMIT (256*1024L)  // ���������� ������ ������



// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++   ����������� �������� 3D ��������   ++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TDrawModel
{
 public :

 //******    ��������� ������    *****************

 // ���������� ����� ������ �������� ������
 TDrawModel(M3DMODEL * addr)
   {
     Base = addr;
     BufferLength = 0;
     Memory = 0;
     IsDirty = 0;
   }

 TDrawModel(char * addr)
   {
     Base = (M3DMODEL *)addr;
     BufferLength = 0;
     Memory = 0;
     IsDirty = 0;
   }

 TDrawModel(const int addr)
   {
     Base = (M3DMODEL *)addr;
     BufferLength = 0;
     Memory = 0;
     IsDirty = 0;
   }

 TDrawModel()
   {
     Base = 0;
     BufferLength = 0;
     Memory = 0;
     IsDirty = 0;
   }

  // ���������� ����� ������ ������
 char * operator = (char * Addr)
   {
     return (char *)(Base = (M3DMODEL *)Addr);
   }

 // ���������� ����� ������ ������
 char * operator = (M3DMODEL * Addr)
   {
     return (char *)(Base = Addr);
   }

 // ��������� ��������� �� ������
 int operator == (int Value)
   {
     return (Base == (M3DMODEL  *)Value);
   }

 int operator != (int Value)
   {
     return (Base != (M3DMODEL  *)Value);
   }

              //******     ����� �������    *****************

 // ��������� ����� ������ ������
 // ��� ������ ���������� 0
 char * Address() { return (char *)Base; }

 // ��������� ������������ ��������� ������
 // ��� ������ ���������� 0
 long IsCorrect()
   {
     if (Base == 0) return 0;
     if (Base->Ident == MODELIDENT)
       return 1;
     return 0;
   }

 // ��������� ������ ����� ������
 // ��� ������ ���������� 0
 long Length()
   {
     if (Base == 0) return 0;
     return Base->Length;
   }

 // ***************** ������� ��� ������ � ������� ������ *****************

 // ��������� ���� ����� ������
 long Key()
   {
     if (Base == 0) return 0;
     return Base->Form;
   }

 // ��������� ���������� �������� ����� ��������� ������
 long PointCount()
   {
     if (Base == 0) return 0;
     return Base->Count;
   }

 // ��������� ����� ������ �������� ����� ��������� ������
 IMG3DPOINT * Points()
   {
     if (Base == 0) return (IMG3DPOINT *)0;
     return (IMG3DPOINT *)((char *)Base + sizeof(M3DMODEL));

   }

 // ***************** ������� ��� ������ � ����������� *****************

 // ��������� ���������� ����������
 long SubmodelCount();

 // ��������� ����� ��������� �� ����������� ������ � 1
 long SubmodelLength(long number);

 // ��������� ��������� ��������� �� ����������� ������ � 1
 IMAGEHEAD * SubmodelHead(long number);

 // ��������� ��� ��������� ( ������ ��� ������ ) cm. IMAGETYPE
 long SubmodelType(long number);

 // ��������� ���������� ����� ��������� �������
 long SubmodelPointCount(long number);

 // ��������� ����� ������ ����� ����� ��������� �������
 IMG3DPOINT * SubmodelPoints(long number);


/*
 // ���������������� ��������� ������� � ���������� ������� ���������
 // �����
 // ��� ������ ���������� 0
 long InitSubmodel(long image,long length, char * work);
*/
/*
 // ��������� ���������� ������ ������� c ��������������� dstIdent
 // �� ������� c ��������������� srcIdent �� ������������� �������
 // ����� - ��������� 1 ����� 0
 long CanHeigthRefer(long dstIdent,long srcIdent);
*/
/*
 // ��������� �������� �� ������(������������ 0) � ������ �������
 // ��� ����� ���������(� ������������� ����������)
 // ��� ������ ���������� 0
 long FunctionHeigth(long function,float * offset ,float * heigth);

 // ��������� �������� �� ������(������������ 0) � ������ ������
 // ��� ����� ���������(� ������������� ����������)
 // ��� ������ ���������� 0
 long Heigth(float * offset ,float * heigth);
*/
 public :
 M3DMODEL *  Base;             // ��������� ������
 long        BufferLength;     // ������ ������ ������������ ��������
 char *      Memory;           // ������ ��������� ������ � �����������
                								       // (���� != 0, ����������)
 long        IsDirty;          // ������� �������������� ������
};


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++   �������������� ����������� �������� 3D ��������   ++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TEditModel : public TDrawModel
{
 /*********************************************************
 *                                                        *
 *       ������� ������������� ������ ������              *
 *                                                        *
 *********************************************************/
 public :
    // ���������� ����� ������ ��������
 TEditModel(char * address,long int length = 0)
  	{
     Memory = 0;
     SetBuffer(address,length);
  	}

 TEditModel()
   {
     Memory = 0;
  	  SetBuffer(0,0L);
   }

 TEditModel(TDrawModel model)
   {
     Memory = 0;
     SetBuffer(model.Address(),model.Length());
  	}

 TEditModel(M3DMODEL * model)
   {
     Memory = 0;
     Load(model);
   }

 ~TEditModel() { SetBuffer(0,0L); }


 // �������� ������ ��� ������������ ������ ������
 // ������������������� ��������� ������
 // ������ ������������� ������������� � �����������
 // ��� ��� ���������� ������ ������� � �������
 // SetBuffer(...), � ��� �����, SetBuffer(0,0).
 // ��� ������ ���������� ����
 long Allocate(long size);

 // ������������������� ��������� ������
 // ��� ������ ���������� ����
 long Clear();

 long Create()
 {
   if (Base != 0) return Clear();
   return Allocate(MODELBUFFERSIZE);
 }

 // ��������� �������� �� ��������� ������
 // ��� ������ ���������� ����, ����� - ����� ����������� ������
 long Load(TDrawModel model);
 long Load(TEditModel * model)
 { if (model) return Load(model->Base);
   return 0; }

 // ��������� �������� �� ��������� ������ ���������� ������
 // long key ���� ������ 
 // long code - ��� ����������, ��� �������� ������ ��� ������
 long Load(HRSC hrsc, long key, long code);

 // ��������� �������� �� ��������� ������ ���������� ������ (M3DMODEL)
 // ������ ������ MODELBUFFERSIZE �� �����������
 // ��� ������ ���������� ����, ����� - ����� ����������� ������
 long Load(M3DMODEL * model);

 // ���������� ��������� ������ ������
 // address - ����� ������, length - ����� ������.
 // ������ ���������� Allocate() �������������.
 void SetBuffer(char * address,long length);

 // ���������/���������� ������� �������������� ������
 long GetDirty();

 long SetDirty(long dirty);

 /*********************************************************
 *                                                        *
 *    �������������� ������������ �������� 3d ������      *
 *                                                        *
 *********************************************************/
 public :

 // ***************** ������� ��� ������ � ������� ������ *****************

 // �������� ����� ��������� ������
 // count - ����� �������� ������
 // point - ����� ������ ����� (�� 2 �� �������)
 long ReplaceFormPoint(HRSC hrsc,long count, IMG3DPOINT * point);

 // �������� ������� ����� ��������� ������
 // begin - ��������� �� ������ ������� �� 2 ����� ������ � �����
 long AppendFormPoint(HRSC hrsc,IMG3DPOINT * begin);

 // �������� ������� ����� ��������� ������
 long ReplaceFormPoint(HRSC hrsc,long number,IMG3DPOINT * begin,IMG3DPOINT * end);

 // ������� ������� ����� ��������� ������
 long DeleteFormPoint(long number);

 // �������� ������ �������� ��������� ������
 long ReplaceBaseModel(long number, IMG3DPOINT * begin,IMG3DPOINT * end);

 // ***************** ������� ��� ������ � ����������� *****************

 // �������� ��������� ( ������ ��������� ���������� ������ �� ������)
 long ReplaceSubmodel(long number,long length,M3DMODEL * param);

 // �������� ��������� � ������ ��������� � ����������
 // ��� ������ ���������� ����,����� - ����� ����������
 long AppendSubmodel(HRSC hrsc, IMAGEHEAD * head);

 // �������� ����� ��������� �  �������������� ����������
 // ��� ������ ���������� ����,����� - ����� ���������� � ������
 long AppendSubmodelWithInit(long image);

 // ������� ���������
 // number - ����� ������� (������� � 2 - ������� ����� ������ ��������)
 // ��� ������ ���������� ����, ����� ���������� ���������� ����������
 long DeleteSubmodel(long number);

 // �������� ������� ����� ��������� ���������
 long AppendSubFormPoint(long subnumber, IMG3DPOINT * begin, IMG3DPOINT * end);

 // ������� ������� ����� ��������� ���������
 long DeleteSubFormPoint(long subnumber,long number);

 // �������� �������� ���������
 // number - ���������� ����� � 1
 long ReplaceFixation(long number,FIXATION * fix);

 // �������� �� ����� ��������� ������ ���������
 // ������� ��������� � ������ ���������
 long CuttingSubmodel(HRSC hrsc,long count, IMG3DPOINT * point,FIXATION * fix);


 // ***************** ������ � ���������   *****************

 // �������� ������� (�������, ��� ������� ����������� ��������� XZ)
 // 1 - �����
 // 2 - ������ �������� ������ (������ �������� � �������)
 // 3 - ������ �������� ������ (������ �������� � �������)
 // 4 - ���� ����� �����
 // 5 - ����� �� �������(������ ������)
 // 6 - ������ �������� ������ (������ ������)(������ �������� � �������)
 // 7 - ������ �������� ������(������ ������) (������ �������� � �������)
 // 8 - ���� ����� ����� (������ ������)
 // 0 - ��� ��������� ������
 long CompareSection(IMG3DPOINT * secton1,IMG3DPOINT * section2);

 // �������� �� ������� �������
 // ���������� ���������� �������������� ��������
 // �� ������ result ������ ���� ��������������� �����
 // �� ����� 4 * sizeof(IMG3DPOINT)
 long CutSection(IMG3DPOINT * secton1,IMG3DPOINT * section2,
                 IMG3DPOINT * result);

 // ������������� ����� �� ��������� � ������� ��������� ������
 long FixPoint(IMG3DPOINT * point, FIXATION * fix);



// protected:
};

#endif
