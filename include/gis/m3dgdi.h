
#ifndef M3DGDI_H
#define M3DGDI_H

#define DELTA3D  0.001       // �������� ���������� ������ (�� 1��)

//******************************************************************
//                   ���� ��������� �����������                    *
//******************************************************************

#define IMG3D_ANY              0  // ������������
#define IMG3D_CUBE             1  // ���
#define IMG3D_SPHERE           2  // �����
#define IMG3D_CYLINDER         3  // �������
#define IMG3D_CONE             3  // �����
#define IMG3D_QUAD             4  // ���������������
#define IMG3D_ADJOINQUAD       5  // ����������� ���������������
#define IMG3D_COMBPOLYGON      6  // ��������� �������������
#define IMG3D_LINE            11  // ����� ��������


//******************************************************************
//                   ���� ������� �������� �����                   *
//******************************************************************
#define SECT_CIRCLE        1  // O���������
#define SECT_RECT          2  // �������������
#define SECT_MOUND         3  // ��������(������)


//******************************************************************
//                   ���� ����� ����������� (��� �������������)    *
//******************************************************************
#define NODE_ANY               0  // ������������
#define NODE_BOX               1  // �����
#define NODE_SPHERE            2  // �����
#define NODE_VCYLINDER         3  // ������� ������������
#define NODE_HCYLINDER         4  // ������� ��������������
#define NODE_CROSSQUAD         5  // ����������� ��������
#define NODE_HQUAD             6  // ��������� ��������������
#define NODE_VQUAD             7  // ��������� ������������
#define NODE_TOP               8  // ������ ����������� ��������������

//******************************************************************
// ���� ������� ������������ ������������ ��������
//             ����������� ��'����� �� ��
//******************************************************************
#define F3D_NULL               0  // ������ ������� - ������ �� ������
#define F3D_EMPTY              1  // ������ ������� - ������ ���������� �������
#define F3D_MARK               2  // ����
#define F3D_MARKBYLINE         3  // ���� �� �����
#define F3D_MARKBYPOINT        4  // ���� �� ������    (F3D_MARK)
#define F3D_MARKBYSQUARE       5  // ���� �� �������
#define F3D_VERTBYLINE         6  // ������������ ��������� �� �����
#define F3D_HORIZONTBYLINE     7  // �������������� ��������� �� �����
#define F3D_HORIZONT           8  // �������������� ���������
#define F3D_LINEBYSURFACE      9  // ������ ������ �����������
#define F3D_TREE              10  // ����� �������
#define F3D_TOPONSQUARE       11  // "����� ��� ��������� "
#define F3D_SQUARECYLINDER    12  // ������� �������������� ��� ���������
#define F3D_FLATLINE          14  // ������� �����
#define F3D_SURFACE           15  // ��������� � ������ �����������
#define F3D_SECTIONBYLINE     16  // ����� c �������� ��������



//                      ����� ������� (���-��)
//                              |
//       ---------------------------------------------------
//       |                                                  |
//   ���������(����� + N �������)                  ���������(����� + N �������)
//       |                                                  |
//   ��������� ������� (+���-�� �����)     ��������� ������� (+���-�� �����)
//       |                                                  |
//       ------------------------------                     |
//       |                            |                     |
//  ���� (+ ���-�� ��������)       ���� (+1��������)  ���� (+2 ��������)
//       |                            |                     |
//       |                            |               --------------------
//       |                            |               |                   |
//   �������� (+ ���-�� ���������)  ��������        ��������            ��������
//       |                            |               |                   |
//   -------------------              |           ------------            |
//   |                  |             |           |           |           |
// �������          �������        �������     �������     �������      �������
//   |                  |             |           |           |           |
// ������� �� ����
//   �����(���� ������)

// ������� �������� ���������� �� ������ ������� �� ������� �������.
// ���� ��� ��������� �����-�� ����� ������� ������� �� ������ - ����������
// ���������� �� � �������. �������� ���������� ������ �� �������, ��� �����
// ����� ��������� ����� ������� �� ���������� ����������
// ��������� ������� ������������ �� ������ �������.
//
// ���������� ����� ����� ���� ��������(��� ����� � ��� �� �������)
// ���� - ������������ ������� ��������� ����� ������� � ���������
// ���������� ��������� ����� ����� (��� ������):
//   �����, ��������� ������������ ...
//
// ���� ������� �� ����� ������� ����������� ���������
// �������� ������� ���������� ����������(����, ��������...)
// ����� ����� ��������
// ���� ���������: IMG3D_ANY - ������������,
//                 IMG3D_CUBE - ���,
//                 IMG3D_SPHERE - �����,
//                 IMG3D_CYLINDER - �������,
//                 IMG3D_CONE - �����,
//                 IMG3D_QUAD - ���������������,
//                 IMG3D_ADJOINQUAD - ����������� ���������������,
//                 IMG3D_COMBPOLYGON - ��������� �������������,
//                 IMG3D_LINE - �����.


//******************************************************************
//                 ��������������� ���������                       *
//******************************************************************
typedef struct IMG3DRGBA            // ���� RGBA
{
  float R;                          // �������
  float G;                          // �������
  float B;                          // �����
  float A;                          // �����, ������� ��������������

  IMG3DRGBA& operator = (IMG3DRGBA& color)                                
  { R = color.R;  G = color.G;  B = color.B; A = color.A; return *this;}
}
  IMG3DRGBA;


typedef struct IMG3DPOINT           // �����
{
  double X;                         // ���������� � ������
  double Y;                         //
  double Z;                         //
  int operator == (IMG3DPOINT * value)                                     
     { return ((X - value->X < DELTA3D) && ( value->X - X < DELTA3D)&&
                (Y - value->Y < DELTA3D) && ( value->Y - Y < DELTA3D)&&
                (Z - value->Z < DELTA3D) && ( value->Z - Z < DELTA3D)); }
}
  IMG3DPOINT;


typedef struct IMG3DRELATE          // ������������ ������ � IMG3DVALUE
{                                   // ��� ��������� �� ���� Type
 short int Ident;                   // ������������� ������� ���������
 short int Refer;                   // ��� ������
} IMG3DRELATE;


typedef struct IMG3DVALUE           // ��������������� ��������
{
   long  int Type ;                 // 0 - ����� ��������
                                    // > 0 ����� ����� ���������
                                    // < 0  - ����� �� ������ �� ������� IMG3DRELATE
   float     Value;                 // ��������
   float     Factor;                // ����������� ��� ��������( ����� Type == 0)
   float     Offset;                // ����� ��������( ����� Type == 0)
}
  IMG3DVALUE;



typedef struct TEXTURETYPE          // ���������� � ��������
{
            long  int Type;         // 0 ��� ����� ���������
   unsigned long  int Code;         // ����� ��������  = 0
            long  int Key;          // ���� �������� - �������� � ��������
                                    // �����
            long  int Reserve;      // ������   
}
  TEXTURETYPE;


typedef struct ACT3DMATERIALMODE    // ��������� ���������
{
  IMG3DRGBA AmbientColor ;          // ���������� ����
  IMG3DRGBA DiffuseColor ;          // ���������  ����
  IMG3DRGBA SpecularColor;          // ����������
  IMG3DRGBA EmissiveColor;          // ����������
  double     Shininess;             // ���������� ����������   
}
  ACT3DMATERIALMODE;

typedef struct IMG3DROTATION        // ������� ����� ������������ ��������
{                                   // ���������
  float X;                          //
  float Y;                          // ������-������� � ��������� ��������
  float Z;                          //
  float Angle;                      // ���� �������� ������ ������� �������
}
  IMG3DROTATION ;

enum FUNCTIONREFERENCE              // �������� �������������� ��������.�������
{
     treeTOP    = 0,                // ���������� ������ (�� Y)
     treeBOTTOM = 1,                // ���������� �����  (�� Y)
     treeLEFT   = 2,                // ���������� �����  (�� �������)
     treeWRITE  = 4,                // ���������� ������ (�� �������)
};
                                    // ���� ������������ ���� ������������
                                    // �����������

#define ALLBYRELIEF            0    // � ������ ������� ���������
#define ALLFREE                1    // ��� ����� ������� (���������� ��
                                    // ������� ������� ������������ �������
                                    // ������ ������� �������)
#define TOPFREE                2    // ��� ����� ������ ��� ������� �������
                                    // ��������� (������ ��������� ������������
                                    // ������������ ������� ������ �������
                                    // ������� + RelativeHeight)

//******************************************************************
//            ��������� ���������� �������                         *
//******************************************************************

typedef struct F3DMARK              // ����
{
  IMG3DVALUE      Height;           // ������ ����� (�� Y)
  IMG3DVALUE      RelativeHeight;   // ������ ������������ ����� ������������
                                    // �������
  IMG3DVALUE      SizeX;            // ������� ����� (������(�� X))
  IMG3DVALUE      SizeZ;            // ������� ����� (�����(�� Z)))
  long            Scale[3];         // ����� ���������������� (�� ������
                                    // (�� X), �� ������(�� Y), �� �����(�� Z))
  char            Vector;           // ���� ���������� ��� ���������� �����:
                                    //   0 - �����������������,
                                    //   1 - ���������� ����� ������� ��������
                                    //       �������,
                                    //   2 -  -"-  ����� ������� �����������
                                    //       �������,
                                    //   3 -  -"-  ����� ����������� ����, �
                                    //        ������� �������� �������� ����
  char            Reserve1[3];      
  IMG3DPOINT      Point[2];         // Point[0] - ���������� ����� ������ �����
                                    //            ������������ ����� �������
                                    // Point[1] - �������� �������� ���������
                                    //            ����� ������������ ����� ������
                                    //            �����
                                    // �������� ����� ������� �� ���� �����)
  long            Count;            // ���������� �����
  long            Reserve2;         
}
  F3DMARK;

typedef struct F3DVERTBYLINE        // ������������ ��������� �� �����
{
  IMG3DVALUE      Height;           // ������ ���������(�����)
  IMG3DVALUE      RelativeHeight;   // ������ ������������ ��������� ������������
                                    // ������� �������:
                                    //       ������������� - �����,
                                    //       ������������� - ����
  IMG3DVALUE      Removal;          // �������� ��������� �� �����������,
                                    // ������������ ������� �������(���� ���)
  long            SurfaceFlag;      // ���� ������������ ��������� ������������
                                    // �����������: ALLBYRELIEF, ALLFREE,
                                    // TOPFREE (��. ����)
  long            Count;            // ���������� �����
}
  F3DVERTBYLINE;

typedef struct F3DHORIZONT          // �������������� ���������
{
  IMG3DVALUE      Height;           // ������ ���������(�����) = 0
  IMG3DVALUE      RelativeHeight;   // ������ ������������ ��������� ������������
                                    // ������� ������ ������� �������:
                                    //       ������������� - �����,
                                    //       ������������� - ����
  long            Count;            // ���������� �����
  long            Reserve;          
}
  F3DHORIZONT;

typedef struct F3DMARKBYLINE        // ���� �� �����
{
  IMG3DVALUE      Height;           // ������ ����� (�� Y)
  IMG3DVALUE      RelativeHeight;   // ������ ������������ ����� ������������
                                    // �������
  IMG3DVALUE      Distance;         // ���������� �� ����� ����� �������
  F3DMARK         Mark;             // �������� �����
}
  F3DMARKBYLINE;

typedef struct F3DMARKBYSQUARE      // ���� �� �������
{
  IMG3DVALUE      Height;           // ������ ����� (�� Y)
  IMG3DVALUE      RelativeHeight;   // ������ ������������ ����� ������������
                                    // �������
  IMG3DVALUE      DistanceX;        // ���������� �� ��� X ����� �������
  IMG3DVALUE      DistanceZ;        // ���������� �� ��� Z ����� �������
  F3DMARK         Mark;             // �������� �����
}
  F3DMARKBYSQUARE;

typedef struct F3DHORIZONTBYLINE    // �������������� ��������� �� �����
{
  IMG3DVALUE      Height;           // ������ ���������(�����)(= 0)
  IMG3DVALUE      RelativeHeight;   // ������ ������������ ��������� ������������
                                    // ������� �������
  IMG3DVALUE      WidthPlane;       // ������ ���������
  IMG3DVALUE      Removal;          // �������� ��������� �� �����������,
                                    // ������������ ������� �������(���� ���)
  long            SurfaceFlag;      // ���� ������������ ��������� ������������
                                    // �����������: ALLBYRELIEF, ALLFREE(��. ����)
  long            Count;            // ���������� �����
}
  F3DHORIZONTBYLINE;


typedef struct F3DSQUARECYLINDER    // ������� �������������� ����������� ��
                                    // ������� (������ �����)
{
  IMG3DVALUE      Height;           // ������ ������� ����� ���������
                                    // (���� ����-������������ �������� ��������)
  IMG3DVALUE      RelativeHeight;   // ������ ������������ ������ ������������
                                    // �������
  unsigned long   Part;             // ������������ ����� (IMG3D_ALL - IMG3D_CLIP)
  unsigned long   Direct;           // 0 - ����� ������ �������� ������� �������
                                    // �������, 1 - �������
  unsigned long   Reserve;
  long            Count;            // ���������� �����
}
  F3DSQUARECYLINDER;

#define F3DFLATLINE F3DVERTBYLINE           // Height - ������ �����
#define F3DSURFACE  F3DHORIZONT             // RelativeHeight - ��� ����������
#define F3DLINEBYSURFACE F3DHORIZONTBYLINE  //( � ������� ��� SurfaceFlag;
                                            //  RelativeHeight;)

typedef struct SECTCIRCLE           // ��������� ����������
{
  IMG3DVALUE  Radius;               // P����� ����������
}
  SECTCIRCLE;

typedef struct SECTRECT             // ��������� ��������������
{
  IMG3DVALUE  Heigth;               // ������
  IMG3DVALUE  Width;                // ������
  char        FlagHide[8];           // 1 - �������� �������
                                    // ������� ��������� �� ������� �������
                                    // �� ���� �������. ������ - ����.
}
  SECTRECT;

typedef struct SECTMOUND             // ��������� ��������
{
  IMG3DVALUE  Heigth;                // ������
  IMG3DVALUE  WidthTop;              // ������ �����
  IMG3DVALUE  WidthBase;             // ������ ���������
  char        FlagHide[8];           // 1 - �������� �������
                                     // ������� ��������� �� ������� �������
                                     // �� ���� �������. ������ - ����.
}
  SECTMOUND;



typedef struct F3DSECTIONBYLINE     // ����� c �������� ��������
{
  IMG3DVALUE      Height;           // ������ ���������(�����)(= ������ ��-��)
  IMG3DVALUE      RelativeHeight;   // ������ ������������ ������ ������� ������������
                                    // ������� �������
  IMG3DVALUE      Removal;          // �������� ������� �� �����������,
                                    // ������������ ������� �������(���� ���)
  long            SurfaceFlag;      // ���� ������������ ������� ������������
                                    // �����������: ALLBYRELIEF, ALLFREE(��. ����)
  long            PlugFlag;         // ����������� ������� ������,��������� �����
                                    // IMG3D_BEGIN | IMG3D_END
  long            Type;             // ��� ������� �����:
                                    // (�������������� ����� - �� �����)
                                    // SECT_CIRCLE - ����������
                                    // SECT_RECT - �������������
                                    // SECT_MOUND - ��������(������)
  long            Length;           // ����� ���������� �������(������ � ��������)
  long            Count;            // ���������� �����
  long            Reserv;           // ������
}
  F3DSECTIONBYLINE;

//******************************************************************
//                          ����� �������                          *
//******************************************************************
// ��������� ��������� �������� �������� 3D ������� ������������
// ��������������� ���� �� ������ � ����������� �� ���� �������

typedef struct F3DTREE              // ����� �������
{
  unsigned long     Ident;          // ������������� ������ 0x73DD73DD
  long              Length;         // ����� ������
  long              MaxIdent;       // ������������ ��������������
                                    // ������������� �������
  long              Count;          // ���������� �������
                                    // ����� ���������,��������� � ������� �������
}
  IMG3DTREE;


typedef struct F3DHEAD              // ��������� ����� ����������
{
  unsigned long     Length;         // ����� ���������� >= 4
                                    // (������� sizeof(F3DHEAD))
  unsigned long     Number;         // ����� �������
  long              Ident;          // ������������� �������
  long              Reserve;        // ������
                                    // ����� ���� ��������� ���������������
                                    // ������� (�� Number)
}
  F3DHEAD;


typedef struct IMG3DNODE            // ����
{
  long              Length;         // ����� ������
  long              Reserve1;       
  IMG3DVALUE        Size[3];        // ������� ���� (������(�� X), ������(�� Y),
                                    //               �����(�� Z))
  long              Count;          // ���������� ��������
  long              Reserve2;       
}
  IMG3DNODE;

                                 // ���� ������������� �������
#define REPEAT_NOT    0          // �� ��������� (������)
#define REPEAT_HOR    1          // �� �����������
#define REPEAT_VER    2          // �� ���������
#define REPEAT_ALL    3          // �� ����� ������������

enum TEXTUREMEASURE              // ��� ������� ��������
{
  texGMetr    = 1,               // ������ �������� �� ����������� � ������
  texGUnit    = 2,               // ������ �������� �� ����������� � �����
  texVMetr    = 4,               // ������ �������� �� ��������� � ������
  texVUnit    = 8,               // ������ �������� �� ��������� � �����
};


// ���� ���� ������� �� ��������� SemColorFlag = 1
// ������������ ���� �����:
//      ��� COLORREF � ((IMG3DVALUE*)&(Desc->Color))->Value
//      A - ��������� � ((IMG3DVALUE*)&(Desc->Color))->Factor
//      ������������ ��� ����� �� ��������� ������� �� ������������� �����
// ����� ��������� �� ��������� ����� � COLORREF ����� �
// ((IMG3DVALUE*)&(Desc->Color))->Type

typedef struct IMG3DDESCRIPTION     // ��������
{
  long              Length;         // ����� ������
  char              ColorFlag;      // 1 - ������� �����,0 - ����������
  char              MaterialFlag;   // 1 - ������� ���������,0 - ����������
  char              TextureFlag;    // 1 - ������� ��������,0 - ����������
  char              SemColorFlag;   //             =    IMG3DVALUE RGBA  value COLORREF
  IMG3DRGBA         Color;          // ���� (RGBA)
  ACT3DMATERIALMODE Material;       // ��������
  long              Transparent;    // ������������ (0-���, 1-���������)
  long              Smooth;         // ���������� ������(0-���, 1-�������)
  TEXTURETYPE       Texture;        // ���������� � ��������
  char              FlagMeasure;    // ��� ������� �������� TEXTUREMEASURE
  char              TransparentTex; // ������������ �������� (0,1)
  char              SmoothTex;      // ���������� �������� (0,1)
  char              WrapTex;        // ������������� ��������
                                    // (��.���� ������������� �������)
  long              Reserve1;       
  IMG3DVALUE        WrapValue[2];   // �������� ������������� �������� ��
                                    // ���� ���������� �����������(��� 0 ���
                                    // ������������ �������������)
  long              Count;          // ���������� ��������� � ����� ���������
  long              Reserve2;       
}
  IMG3DDESCRIPTION;

typedef struct IMG3DELEMENT         // �������
{
  long              Length;         // ����� ������
  long              Type;           // ��������� � ������� �� ����
                                    //   IMG3D_ANY - ������������,
                                    //   IMG3D_CUBE - ���,
                                    //   IMG3D_SPHERE - �����,
                                    //   IMG3D_CYILINDER - �������,
                                    //   IMG3D_CONE - �����,
                                    //   IMG3D_QUAD - ���������������,
                                    //   IMG3D_ADJOINQUAD - �����������
                                    //                      ���������������,
                                    //   IMG3D_COMBPOLYGON - ���������
                                    //                       �������������,
                                    //   IMG3D_LINE - �����.
                                    // ������� �� ����


}
 IMG3DELEMENT;

//******************************************************************
//                    ������� �� ���� ��������                     *
//  (������� � ��������������� ������ ������ � ����������� ������  *
//   ������� �������)                                              *
//******************************************************************


typedef struct IMG3DCUBE            // (1)   ���
{
  IMG3DPOINT     Point;             // ���������� ����� �������� ��������
                                    // ������������ ���� �����(�������� �����
                                    // ������ �������-������ �����)
  IMG3DROTATION  Rotate;            // ������� �������� � �������
                                    // ��������� �����
  float          Width;             // ������
  float          Height;            // ������
  float          Depth;             // �������
  unsigned long  Reserve;           // ������
}
  IMG3DCUBE;


typedef struct IMG3DSPHERE          // (2) �����
{
  IMG3DPOINT     Point;             // ���������� ����� �������� ��������
                                    // ������������ ���� �����
  IMG3DROTATION  Rotate;            // ������� �������� � �������
                                    // ��������� �����
  float          Radius;            // ������
  unsigned long  Reserve;           // ������
}
  IMG3DSPHERE;

// ������������ ����� (������ ����� ����������)
#define IMG3D_SIDES   1             // ���������� �������
#define IMG3D_BOTTOM  2             //            ���
#define IMG3D_TOP     4             //            ����
#define IMG3D_CLIP    8             // �� ���������� ��������� �����
#define IMG3D_BEGIN   16            // ���������� ������� � ������ ����� �������
#define IMG3D_END     32            // ���������� ������� � ��������� ����� �������


typedef struct IMG3DCYLINDER        // (3) ������� (�����)
{
  IMG3DPOINT     Point;             // ���������� ����� �������� ��������
                                    // ������������ ���� �����
  IMG3DROTATION  Rotate;            // ������� �������� � �������
                                    // ��������� �����
  unsigned long  Part;              // ������������ ����� (IMG3D_ALL - IMG3D_BOTTOM)
  float          Radius;            // ������ ���������
  float          RadiusH;           // ������ �������� �� �������� ������ Height
                                    // ��� ����(���� ��� �����)
  float          Height;            // ������
}
  IMG3DCILINDER;


typedef struct IMG3DQUAD            // (4,5) ��������������� (�����������)
{
  IMG3DPOINT   Vertex[4];           // ���������� ����� ������������ ���� �����
}
  IMG3DQUAD;


#define IMG3DADJOINQUAD IMG3DQUAD   // (5) ����������� ���������������
                                    // (������ ��� ������� ��������� ���������
                                    //  ��� ������� ����������� ��������)


typedef struct IMG3DCOMBPOLYGON     // (6) ��������� �������� �������������
{
  long         Count;               // ����� �����(��� ��� ������� � �������
                                    // ������ ���������)
  long         Reserve;             
  IMG3DPOINT   Vertex[1];           // ���������� �����(�� �����), ������������
                                    // ���� �����
}
  IMG3DCOMBPOLYGON;


typedef struct IMG3DLINE            // (11) ����� ��������
{
  long         Count;               // ����� ������ �������
  float        Width;               // ������ �����
  IMG3DPOINT   Vertex[1];           // ���������� ������(�� �����), ������������
                                    // ���� �����
}
  IMG3DLINE;


//******************************************************************
//          ���������  ��� ��������� ����� �����������             *
//******************************************************************

typedef struct SELECTPART           // �������� ���������� ����� �����������
{
  long          Function;           // ����� ������� � ������� ������������
                                    // (��.����)     (0 ��� ����� �����������)
  long          Node;               // ����� ����    (0 ��� ���� �������)
  long          Description;        // ����� ��������(0 ��� ����� ����)
  long          Element;            // ����� ��������(0 ��� ����� ��������)
}
   SELECTPART;

#endif  // M3DGDI_H

