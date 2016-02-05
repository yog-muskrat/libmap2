
#if !defined(DRWTREE_H)
#define DRWTREE_H

#ifndef MAPMACRO_H
  #include "mapmacro.h"
#endif

#ifndef M3DGDI_H
  #include "m3dgdi.h"
#endif

#define TREEBUFFERSIZE (4*1024L)  // ����������� ������ ������ !

#define TREEIDENT  0x73DD73DD     // ������������� ������ ������� ����������
                                  
#define TREEIDENTN 0x73DD73DE     // ������������� ������ �������  �� ����������

#define TREERECORDLIMIT (256*1024L)  // ���������� ������ ������

typedef struct DTREEPLACE
     {
       long Function  ;    // ���������� ����� �������
       long Node      ;    // ���������� ����� ���� (� �������� �����)
       long Describe  ;    // ���������� ����� �������� (� �������� �����)
       long Element   ;    // ���������� ����� �������� (� �������� �����)
     }
DTREEPLACE;

// ����������� �������� ���������� ���������� ������������ ����� 5-�����������
// ������. ������ ������� - �������(F3DMARK,F3DMARKBYLINE ...), ������ - ����
// ������������ ������� ��������� ����� �������(�����,��������� ������������ ...)
// 3 - �������� (��������,����...),4 - �������� (���,�����,���������������...)
// � �������� (����� ��� ��������� ��������������� ��������)
// ������� ����� �������� ����� ���������� ��������� �� ��������� DTREEPLACE,
// � ������� �������� � ����� ����� ������ ��������� ������
// ������� ���� - ����� �����, ������������� �����, ����� ����� - ���������
// � ��������� ��������� ����� ��������� DTREEPLACE
// (�������� : ������ ������
//                    place.Function = 2; place.Node = 3;  place.Describe = 1;
//                    place.Element = 2;
//            - ���������� ����� 2 ��������,3 ����, 2 �������.
// ��� �������� ���������� ������
// �� ������� ��������� ������ ������� ����� ��������� DTREEPLACE
// (�������� : place.Function = 2; place.Node = 0;
//             - ���������� ���������� ����� � 2 �������.
//             place.Function = 1; place.Node = 1;  place.Describe = 0;
//             - ���������� ����� ���������� �������� 1 ���� 1 �������
// ��� ������ ���������� 0

typedef struct DTREENAVIGATOR
     {
       long Ident     ;    // ����� ����������
       long Level     ;    // ����� �������� ������   ( 1 - 5 )
       char * Address ;    // ����� �������� ��������
       DTREEPLACE Place;
     }
DTREENAVIGATOR;

// ��� �������� ����� ������� � ������ ���������� ������� ����������
// � ������� : GetParamLength(F3DHEAD * head);
//             GetNodeCount(F3DHEAD * head);
//             IsTreeFunction(long function)
//             InitTreeFunction(...)

// ��� �������� ����� ����� � ������ ���������� ������� ����������
// � ������� :
//             long TDrawEdit::AddNodeCount(F3DHEAD * head);
//             long TDrawTree::GetNodeCount(F3DHEAD * head)

// ��� �������� ����� ��������� � ������ ���������� ������� ����������
// � ������� :

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++   ����������� �������� 3D ��������   ++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TDrawTree
{
 public :

          //******    ��������� ������    *****************

 // ���������� ����� ������ ����������� �������� �������
 TDrawTree(F3DTREE * addr)
   {
     Base = addr;
     BufferLength = 0;
     Memory = 0;
     IsDirty = 0;
     memset(&Navig1,0,sizeof(Navig1));
     memset(&Navig2,0,sizeof(Navig2));
   }

 TDrawTree(char * addr)
   {
     Base = (F3DTREE *)addr;
     BufferLength = 0;
     Memory = 0;
     IsDirty = 0;
     memset(&Navig1,0,sizeof(Navig1));
     memset(&Navig2,0,sizeof(Navig2));
   }

 TDrawTree(const int addr)
   {
     Base = (F3DTREE *)addr;
     BufferLength = 0;
     Memory = 0;
     IsDirty = 0;
     memset(&Navig1,0,sizeof(Navig1));
     memset(&Navig2,0,sizeof(Navig2));
   }

 TDrawTree()
   {
     Base = 0;
     BufferLength = 0;
     Memory = 0;
     IsDirty = 0;
     memset(&Navig1,0,sizeof(Navig1));
     memset(&Navig2,0,sizeof(Navig2));
   }

  // ���������� ����� ������ ������
 char * operator = (char * Addr)
   {
     return (char *)(Base = (F3DTREE  *)Addr);
   }

 // ���������� ����� ������ ������
 char * operator = (F3DTREE * Addr)
   {
     return (char *)(Base = Addr);
   }

 // ��������� ��������� �� ������
 int operator == (int Value)
   {
     return (Base == (F3DTREE  *)Value);
   }

 int operator != (int Value)
   {
     return (Base != (F3DTREE  *)Value);
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
     if ((Base->Ident >= TREEIDENT)||(Base->Ident<=TREEIDENTN))   
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

 // ��������� ����� ������ �� ��������� ������
 // �� ������� ��������� ������ ������� ����� place
 // (�������� : place.Function = 2; place.Node = 0;
 //             - ���������� ���������� ����� � 2 �������.
 //             place.Function = 1; place.Node = 1;  place.Describe = 0;
 //             - ���������� ���������� �������� � 1 ���� 1 �������
 // ��� ������ ���������� 0
 long PartCount(DTREEPLACE * place);

 // ��������� ����� ����� �� ��������� ������
 // �� ������� ��������� ��������� ��������� ����� place
 // ��� ������ ���������� 0
 char * PartAddress(DTREEPLACE * place);

 // ��������� ������ ����� ����� �� ��������� ������
 // ��� ������ ���������� 0
 long PartLength(DTREEPLACE * place);


            //******     ������� �� ��������   *****************

 // ���������  ��������� ������� ����������� � ������ ����������
 // ��� ������ ���������� 0
 long IsTreeFunction(long function);

 // ���������������� ��������� ������� � ���������� ������� ���������
 // �����
 // ��� ������ ���������� 0
 long InitTreeFunction(long image,long length, char * work);

 // ��������� ����� �������
 // ��� ������ ���������� 0
 long FunctionCount()
   {
     if (Base == 0) return 0;
     return Base->Count;
   }

 // ��������� ��� ���������� �������
 // number - ���������������� ����� (� 1)
 // ��� ������ ���������� 0
 long FunctionParametersType(long number);

 // ��������� ������������� �������
 // number - ���������������� ����� (� 1)
 // ��� ������ ���������� 0
 long FunctionIdent(long number);

 // ��������� ������ ���������� ������� (�� ������� ����)
 // head ��������� �� ��������� �������
 // ��� ������ ���������� -1 (�.� ����� � �� ���� �����)
 long GetParamLength (F3DHEAD * head);

 // ��������� ���������� ������ ������� c ��������������� dstIdent
 // �� ������� c ��������������� srcIdent �� ������������� �������
 // ����� - ��������� 1 ����� 0
 long CanHeigthRefer(long dstIdent,long srcIdent);

 // ��������� ���������� ����� � �������
 // head ��������� �� ��������� �������
 // ��� ������ ���������� -1 (�.� ����� � �� ���� �����)
 long GetNodeCount(F3DHEAD * head);

 // ��������� ��������� ���� � ������ ����������� �����
 // ��� ������ ���������� 0
 long IsTreeNode(long image);

 // ���������������� ��������� ���� � ���������� ������� ���������
 // �����
 // ��� ������ ���������� 0, ����� ����� �������
 long InitTreeNode(long image,long length, char * work);

            //******     ������� �� ���������   *****************

 // ��������� ����� ����� ��������
 // ��� ������ ���������� 0
 long DescribeCount();

 // ������ ������ �������� �� ����������� ������ (� 1)
 // ��� ������ ���������� 0
 IMG3DDESCRIPTION * GetDescribe(int number);

 // ������ � ������� �������� ���� �������
 // ��� ������ ���������� 0
 long ClearDescription(void);
            //******     ������� �� ���������   *****************

 // ��������� ��� ��������
 // ��� ������ ���������� 0
 long ElementType(DTREEPLACE * place);

 // ��������� ����� ������� ��������
 // ��� ������ ���������� 0
 char * ElementMetricAddress(DTREEPLACE * place);

 // �������� ����� �����
 // �� �������� ������������� ��������������� �����
 // ��������������� ������ ���� ���������
 long ChangeMarkSize(F3DMARK * mark,IMG3DPOINT * scale);

 // �������� ����� �����
 // ��� ��������� ��������� - ����� �������� �����
 long ExactMarkSize(F3DMARK * mark);

 // �������� ����� ����
 // �� �������� ������������� ��������������� ����
 // center - ����� ������� ����(mark.Point[0])
 // ��������������� ������ ���� ���������
 long ChangeNodeSize(IMG3DNODE * node,IMG3DPOINT * scale,IMG3DPOINT * center);

 // �������� ����� ���� � �������� ����
 // ��� ��������� ��������� - ����� ����� ����
 // � point ��������
 long ExactNodeSize(IMG3DNODE * node,IMG3DPOINT * point);

 // �������� ����
 // ����� ��������� ���� ���������� ������������� ������ �����
 long MoveNode(IMG3DNODE * node,IMG3DPOINT * offset);

 // ������� ���� (������������ ������ ���������)
 // axes = 1 - ������ ��� �
 // axes = 2 - ������ ��� Y
 // axes = 3 - ������ ��� Z
 // center - ����� �������� ����� mark.Point[0]
 // ����� �������� ���� ���������� ������������� ������ �����
 long RotateNode(IMG3DNODE * node,long axes,float angle,IMG3DPOINT * center);

 // ������� ����� (������������ ������ ���������)
 // axes = 1 - ������ ��� �
 // axes = 2 - ������ ��� Y
 // axes = 3 - ������ ��� Z
 // center - ����� �������� ����� mark.Point[0]
 long RotatePoint(IMG3DPOINT * point,long axes,float angle,IMG3DPOINT * center);


 // ���������� ��������������� �������(������ �������� �������������� GluObject)
 // � ��������������� ���� ��������
 // �������� ������� axes = 1 - ������ ��� �
 //                  axes = 2 - ������ ��� Y
 //                  axes = 3 - ������ ��� Z
 // �� ���� angle (� ��������)
 long RotateGluObject(IMG3DROTATION* rotate,long axes,long angle);

 // ��������� �������� �� ������(������������ 0) � ������ �������
 // ��� ����� ���������(� ������������� ����������)
 // ��� ������ ���������� 0
 long FunctionHeigth(long function,float * offset ,float * heigth);
 
 // ��������� �������� �� ������(������������ 0) � ������ ������
 // ��� ����� ���������(� ������������� ����������)
 // ��� ������ ���������� 0
 long Heigth(float * offset ,float * heigth);

 public :
 F3DTREE *   Base;
 long        BufferLength;     // ������ ������ ������������ ��������
 char *      Memory;           // ������ ��������� ������ � �����������
                								       // (���� != 0, ����������)
 long        IsDirty;          // ������� �������������� ������

 DTREENAVIGATOR Navig1;        // ��������� ��� ����������� �� ������
 DTREENAVIGATOR Navig2;        // ��������� ��� ����������� �� ������
};


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++   �������������� ����������� �������� 3D ��������   ++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TEditTree : public TDrawTree
{
 /*********************************************************
 *                                                        *
 *       ������� ������������� ������ ������              *
 *                                                        *
 *********************************************************/
 public :
    // ���������� ����� ������ ��������
 TEditTree(char * address,long int length = 0)
  	{
     Memory = 0;
     SetBuffer(address,length);
  	}

 TEditTree()
   {
     Memory = 0;
  	  SetBuffer(0,0L);
   }

 TEditTree(TDrawTree draw)
   {
     Memory = 0;
     SetBuffer(draw.Address(),draw.Length());
  	}

 TEditTree(F3DTREE * param)
   {
     Memory = 0;
     Load(param);
   }

 ~TEditTree() { SetBuffer(0,0L); }


 // �������� ������ ��� ������������ ������ �������
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
   return Allocate(TREEBUFFERSIZE);
 }

 // ��������� �������� �� ��������� ������
 // ��� ������ ���������� ����, ����� - ����� ����������� ������
 long Load(TDrawTree draw);
 long Load(TEditTree * draw)
 { if (draw) return Load(draw->Base);
   return 0; }

 // ��������� �������� �� ��������� ������ ����������
 // ���������� ������� (F3D_TREE)
 // ������ ������ DRAWBUFFERSIZE �� �����������
 // ��� ������ ���������� ����, ����� - ����� ����������� ������
 long Load(F3DTREE * dtree);
 // ���������� ��������� ������ ������
 // address - ����� ������, length - ����� ������.
 // ������ ���������� Allocate() �������������.
 void SetBuffer(char * address,long length);

 // ���������/���������� ������� �������������� ������
 long GetDirty();
 long SetDirty(long dirty);


/*********************************************************
 *                                                        *
 *      ��������� �� ������                               *
 *                                                        *
 *********************************************************/
/*
 public :

 // ����� ����� �����
 // ��� ��������� � 1.
 // ���� �� ����� ���������� �� ��������� ������� ������ 0
 char * GetPart(DTREEPLACE * place,long how);

 // ����� ���������
 // 0 - ��������� ���
 int GetNavigator();

 // ���������� ���������
 // ��������� ����� �������������� ��������
 // ���� 0, ���� ������ ���
 char * SetNavigatorPlace(long navigator,DTREEPLACE * place);

 // ��������� ����� ����������
 // ��������� ����� �������������� ��������
 char * SetNavigatorPlace(long navigator,DTREEPLACE * place);

 // ���������� ��������� �� ��������� ���� ���������� �������
 // ���� how = 0 - � �������� �����,
 // ���� how = 1 - �� ����� ������
 // ��������� ����� �������������� ��������
 // ���� 0, ���� ������ ���
 char * Next(long navigator,long how);
 char * Prev(long navigator,long how);

 // ���������� ��������� �� ������� ����� ��� ����
 // ��������� ����� �������������� ��������
 // ���� 0, ���� ������ ���
 char * Low(long navigator);
 char * Up(long navigator);

 // ��������� ����� �������� ��������
 long GetCurrentNavLength(long navigator);

 // ��������� ��� �������� ��������
 long GetCurrentNavLength(long navigator);
*/
 /*********************************************************
 *                                                        *
 *    �������������� ������������ �������� 3d �������     *
 *                                                        *
 *********************************************************/
 public :

 // �������� ����� ������� � ������ ��������� � ����������
 // ��� ������ ���������� ����,����� - ����� ������� � ������
 long AppendFunction(long image,long length,F3DHEAD * param);

 // �������� ����� ������� c �������������� ����������
 // ��� ������ ���������� ����,����� - ����� ������� � ������
 long AppendFunctionWithInit(long image);

 // ������� �������
 // number - ����� ������� (������� � 1)
 // ��� ������ ���������� ����, ����� ���������� ���������� �������
 int DeleteFunction(long number);

 // ����������� ������� ��  ����� ����� (����� � 1)
 // ��� ������ ���������� 0
 long MoveFunction(long oldnumber,long newnumber);

 // Bc������ ������� �� ������
 // ��� ����� ���������� Ident = 0
 // ��� ������ ���������� ����,����� ����� �������
 long InsertFunction(long number, long length,F3DHEAD * param);

 // �������� ������� �� ������ �� ������ � ������ ��������� � ����������  
 // ��� ������ ���������� ����,����� - ����� ������� � ������
 long ReplaceFunction(long number, long image,long length,F3DHEAD * param);

 // ��������� ������ �� ������������ ������ �������
 // ����������� ��� �������������
 // ��� ������ ���������� ����, ����� 1
 long ChangeFunctionRefer();

 // �������� � ������� ����� ���� � ������ ��������� � ����������
 // function - ���������� ����� �������
 // ��� ������ ���������� ����,����� - ����� ����� � �������
 long AppendNode(long function,long length,char * param);

 // �������� ����� ���� � ������� c �������������� ����������
 // function - ���������� ����� �������
 // node - ��� ����
 // ��� ������ ���������� ����,����� - ����� ����� � �������
 long AppendNodeWithInit(long function,long node);

 // ������� ����
 // number - ����� ������� (������� � 1)
 // ��� ������ ���������� ����, ����� 1
 int DeleteNode(DTREEPLACE * place);

 // �������� �������� �����
 // number - ����� �������, � ������� �������� ����
 // mark - ����� ���������� ����������

 int ReplaceMark(int number,F3DMARK * mark,long length);

 protected:
 // ��������� �� 1 ���������� ����� � �������
 // head ��������� �� ��������� �������
 // ���������� ���������� �����
 long AddNodeCount(F3DHEAD * head);

};

#endif
