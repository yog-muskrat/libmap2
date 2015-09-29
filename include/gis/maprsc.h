
#if !defined(MAPRSC_H)
#define MAPRSC_H

#ifndef MAPERROR_H
  #include "maperror.h"
#endif

#ifndef MAPSEM_H
  #include "mapsem.h"
#endif

#ifndef MAPGDI_H
  #include "mapgdi.h"
#endif

#ifndef MAPVERSN_H                 
  #include "mapversn.h"
#endif

#ifdef HIDE3D
 #define HIDERSC3D                 
#endif

#ifndef HIDERSC3D                  
#ifndef DRWTREE_H
  #include "drwtree.h"
#endif

#ifndef RSCFL3D_H
  #include "rscfl3d.h"
#endif

#endif    // HIDERSC3D            

#ifdef LP64MODEL
 #define MAXMEMBUFFERSIZE 1024L
 #define MEMAUGMENT 256
#endif

class TMap;
class TFontDraw;

// ������ � �������
typedef struct MEMHEAD
{
  char * Previous;              // ����� ��������������� �������� ������
  long Length;                  // ����� �������� ������
  long Offset;                  // ������ ���������� �����
  long Reserv;                  // ������. = 0                        
}
 MEMHEAD;

#define AUGMENTOBJECT    100
#define AUGMENTSEMANTIC   20
#define AUGMENTSEGMENT    20
#define AUGMENTIML        20
#define AUGMENTTXT        10
#define AUGMENTFRM        10                       
#define AUGMENTGRS       100
#define AUGMENTRECORD    400                       

#ifndef HIDEIML                 
#ifdef __cplusplus              
 struct IMLLIST;                
#else
 #include "mapgdiex.h"           
#endif
#endif

 struct TABOBJ;
 struct TABDEF;
 struct TABIML;
 struct TABSEM;
 struct TABPOS;
 struct TABLIM;
 struct IMAGEVALUE;
 struct TABPAL;
 struct TABGRS;
 struct TABSEG;
 struct TABCLS;
 struct RELATION;               
 struct TABP3D;                 
 struct TABTAB;                 
 struct TABL3D;                 
 struct TABFRM;                 

typedef struct RSCHEAD
{
  ULONG Label   ;    // �����
  ULONG Length  ;    // ����� �����
  ULONG Version ;    // ������ ��������� RSC 0x0700
  ULONG Series  ;    // ���������
  ULONG Style   ;    // H���� ������H�� �����
  ULONG Mode    ;    // H���� ����������� ������H��
  ULONG Language;    // 1 - ����������, 2 - �������
  ULONG MaxKey  ;    // ������������ ������������� ������� ��'�����

  char               Date[8] ;    // ���� �����H�� �����
  char               Type[32];    // ��� �����
  char               Name[32];    // �����H�� H����H�� ���������.
  char               Code[8] ;    // ��� ��������������

  ULONG Scale   ;    // ������� �����
  ULONG ScaleRow;    // 0 - ������ ���������� ���
                                  // 1 - ������ ���������� ���

  ULONG Off_Obj ;    // �����H�� H� ������� ��'�����
  ULONG Len_Obj ;    // ���H� �������
  ULONG Num_Obj ;    // ����� �������

  ULONG Off_Sem ;    // �����H�� H� ������� ����H����
  ULONG Len_Sem ;    // ���H� �������
  ULONG Num_Sem ;    // ����� �������

  ULONG Off_Cls ;    // �����H�� H� �������������
  ULONG Len_Cls ;    // ���H� �������
  ULONG Num_Cls ;    // ����� �������

  ULONG Off_Def ;    // �����H�� H� ������� ������H��
  ULONG Len_Def ;    // ���H� �������
  ULONG Num_Def ;    // ����� �������

  ULONG Off_Pos ;    // �����H�� H� ������� ����.���
  ULONG Len_Pos ;    // ���H� �������
  ULONG Num_Pos ;    // ����� �������

  ULONG Off_Seg ;    // �����H�� H� ������� �����H���
  ULONG Len_Seg ;    // ���H� �������
  ULONG Num_Seg ;    // ����� �������

  ULONG Off_Lim ;    // �����H�� H� ������� �������
  ULONG Len_Lim ;    // ���H� �������
  ULONG Num_Lim ;    // ����� �������

  ULONG Off_Par ;    // �����H�� H� ������� ����������
  ULONG Len_Par ;    // ���H� �������
  ULONG Num_Par ;    // ����� �������

  ULONG Off_Prn ;    // �����H�� H� ������� ���.������
  ULONG Len_Prn ;    // ���H� �������
  ULONG Num_Prn ;    // ����� �������

  ULONG Off_Pal ;    // �����H�� H� ������� ������
  ULONG Len_Pal ;    // ���H� �������
  ULONG Num_Pal ;    // ����� �������

  ULONG Off_Txt ;    // �����H�� H� ������� �������
  ULONG Len_Txt ;    // ���H� �������
  ULONG Num_Txt ;    // ����� �������

  ULONG Off_Iml ;    // �����H�� H� ������� ���������
  ULONG Len_Iml ;    // ���H� �������
  ULONG Num_Iml ;    // ����� �������

  ULONG Off_Grs ;    // �����H�� H� ������� ����������� ���������
  ULONG Len_Grs ;    // ���H� �������
  ULONG Num_Grs ;    // ����� �������

  ULONG Off_Tab ;    // �����H�� H� ������� ������
  ULONG Len_Tab ;    // ���H� �������
  ULONG Num_Tab ;    // ����� �������
  char            ObjectCode ;    // ���� ������������� ������ ��� �����
  char            ColorStyle ;    // H���� ����������� ������H�� ������� 
  char             Reserv1[2] ;   // ������ = 0                  
  ULONG CharCode3D;   // ������,�� ������������
  ULONG Series3D  ;   // ������,�� ������������
  ULONG Reserv[5] ;   // ������ = 0

  ULONG CharCode  ;   // ���������
  ULONG ColorCount;   // ���������� ������ � �������
}
  RSCHEAD;

// ������ �� ������ ������
typedef struct RSCRECORD
{
  ULONG Code;         // ��� ��������� 3D ����������
  ULONG Offset;       // ����� � ������
  ULONG Flag;         // ���� ���������,�������� ...
  ULONG Type;         // ���  ������
  LONG         Key;          // ���� ������
}
  RSCRECORD;

// �������� ��������
typedef struct RSCOBJ
{
   ULONG      Code    ; // ����������������� ���
   unsigned short int Local   ; // �������� �����������
   unsigned short int Segment ; // �0��� ���� ( �� ����� 256)
   unsigned short int Scale   ; // 1 - ��'��� ��������������
                                // 0 - ��'��� �� ��������������
   unsigned short int Bot     ; // ������ ������� ���������
   unsigned short int Top     ; // ������� ������� ���������
   unsigned char      Name[32]; // �������� ( ����� �� 30 ��������)
}
               RSCOBJ;

#define MAXSEMANTICCODE  65500                     
// �������� ��������
typedef struct RSCSEM
{
  unsigned short int Code     ; // ����������������� ���
  unsigned short int Type     ; // ��� �������� �������� (SEMTYPE)
  unsigned short int Reply    ; // 1 - ��'��� ��������������
  unsigned char      Name[32] ; // ��������  ( ����� �� 30 ��������)
  unsigned char      Unit[8]  ; // ������� ��������� (����)
}
               RSCSEM;

typedef struct RSCSEG
{
  ULONG Length   ;   // ����� ������
           char     Name[32] ;   // H����H��
           char     Short[16];   // �������� ��� ����
  unsigned char     Number   ;   // ����� �����H��
  unsigned char     Order    ;   // ������� ������ �����H��
  unsigned short    Count    ;   // ����� �������� ����
  LONG          Code[1]  ;   // ��������� ����
}
  RSCSEG;

// �������� ���������

typedef struct RSCDEF
{
 float MinValue;   // ����������� �������� ��������� ��� ��'����
 float DefValue;   // ������������ �������� ��������� ��� ��'����
 float MaxValue;   // ������������ �������� ��������� ��� ��'����
}
               RSCDEF;

typedef struct VIEPAR
{
   ULONG Length  ;    /* ���H� ������                  */
   unsigned short int Incode  ;    /* �H����HH�� ��� ��'����        */
   unsigned short int Number  ;    /* H���� ��H���� ��������H��     */
   unsigned char      Param   ;    /* ��������� ��H���� ��������H�� */
}
                   VIEPAR;

typedef struct HEADDEFCLS
{
  unsigned short int Flag     ;    // 0x7FFF - ������������� ������
                                   // ������
  unsigned short int Free     ;    // ���������� ��������� �������
  unsigned short int Number   ;    // ����� ���������� �������
  short int          Reserv   ;    // ������. = 0                        
}
               HEADDEFCLS;

// ------------------------------------------------------------------
// ������� ��������������� �������� ��� �������
// i ������� �������� �������������� ��� ������� � i ���������� �����
// -------------------------------------------------------------------

typedef struct TABRSC
  {
    TABOBJ *           TabObj;    // �������������� �������
    TABPOS *           TabPos;    // ��������� ��������� (��� - 0)
    TABLIM *           TabLim;    // ������  (��� - 0)
    VIEPAR *           ViewParm;  // ��������� �����������
    VIEPAR *           PrintParm; // ��������� ������
    TABP3D *           Dim3Parm1; // 3D ��������� ������� ������
    TABP3D *           Dim3Parm2; // 3D ��������� ������� ������
    TABP3D *           Dim3Parm3; // 3D ��������� �������� ������
    ULONG      Excode;    // ������� ��� �������
    unsigned short int Function;  // ������� ��� �����������
    unsigned short int Flags;     // ���� �����������
    unsigned short int Segment;   // �������
    unsigned char      Local;     // �����������
    unsigned char      Extloc;    // �����������
    unsigned short int Extend;    // ����� ���������� (����� � �����)
    unsigned char      Extsem;    // ������� ������� ��������� ��� �����������
    unsigned char      Reserv;    // ������
  }
    TABRSC;


// ------------------------------------------------------------------
// ������� ��������������� �������� ������������ ����������� ���������
// i ������� �������� �������������� ��� ������ � i �������
// ������ ����� � �� ���� - ��� 0
// -------------------------------------------------------------------

typedef struct TABGRSITEM
  {
    ULONG  Code     ;   // ��� ���������
    unsigned short int Number   ;   // ���������� ����� ������ �����������
    unsigned short int Default  ;   // ��� ������������� �������� 1,����� 0
    ULONG  Value    ;   // �������� ���������
    ULONG  Function ;   // ����� ������� ����������� ������
    IMAGEVALUE *       Item     ;   // �����  � ��������� �����������
  }
    TABGRSITEM;

 enum FLFORRSC      // ����� ��� TABRSC
   {
     rscFREE    = 0,  // ����������� �� ����
     rscLOWFONT = 1,  // ���� ����� ����������
     rscKILL    = 2,  // ������ ������ ������
     rscDEL     = 4,  // ������ ������ � ������� ������ ������
     rscSERIA   = 8,  // ������� ������ � �����
     rscGETH    = 16, // ������� ����������
     rscPICT    = 32  // ���������� ������
   };

enum FLFORRECORD      // ����� ��� TABRECORD
   {
     recFREE    = 0,  // ����������� �� ����
     recCORR    = 1,  // ���� ������
     recDEL     = 2   // ������ �������
     /*
     rscDEL     = 4,  // ������ ������ � ������� ������ ������
     rscSERIA   = 8,  // ������� ������ � �����
     rscGETH    = 16, // ������� ����������
     rscPICT    = 32  // ���������� ������
     */
   };

  enum FRAMEINCODERSC
  {
   MAXSEMANTICCOUNT = 1024,
   COLOROFSERVOBJECT = 13,         // ������ ����� ��������� ��������
   COUNTOFTAB        = 14,         // ���������� ������
  };

  enum  IDENTFORRSC
   {
     HEADIDENT      =  0x7FFF, // ������������� ������ ���������
                               // ��� ��������������
   };


// ��������� ��� ������ � ����������� ��������� �� �������       
typedef struct FORMOPER  // �������
{
   double Value;   // ��������
   long Number;    // ����� ���� � �������� ����� �������� (� 1)
   char Flag;      // 0 - �� ��������, 1 - ������ � ����� ����� Number,
                   // 2 - ����� ����� �������� - ��� ���������
   char Sign;      // 0 - ����� ������ ��������
                   // 1 - ���� ��������� ����� ��������(� +v -v, � *v - 1/v)
   char Res1;
   char res2;
}
 FORMOPER;

typedef struct FORMNODE
{
  FORMOPER Oper[10]; // ��������
  long Number;       // ����� ����(� 1)
  long Parent;       // ����� ���� �������� (� 1)
  long Rezerv;       // ������
  char  Type;        // ��� ��������
  char Count;        // �������� ���������� ��������� (���� 10)(� 1)
  char Bracket;      // T�� ������ ( 0 - ���, 1 - �������, 2 - ����������,
                     //                       3 - �������� )
  char Close;        // 0 - ��� �������� ������, 1 - ���� ������
}
  FORMNODE;




// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ ������������� ����������� ��������� �����   +++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef class _DLLCLASS TMapRsc
{

  public :
  enum FLTRSC      // ����� ��� TABRSC
   {
     FREE    = ::rscFREE,    // ����������� �� ����
     LOWFONT = ::rscLOWFONT, // ���� ����� ����������
     KILL    = ::rscKILL,    // ������ ������ ������
     DEL     = ::rscDEL,     // ������ ������ � ������� ������ ������
     SERIA   = ::rscSERIA,   // ������� ������ � �����
     GETH    = ::rscGETH     // ������� ����������
   };

  enum
   {
     FIRSTSERVEXCODE  = ::FIRSTSERVEXCODE , // ������ ������� ����� ���������
     LINESERVEXCODE   = ::LINESERVEXCODE  , // ������� ��� ���������� ���������
     LINESERVINCODE   = ::LINESERVINCODE  , // ���������� ��� ���������� ���������
     SQUARESERVEXCODE = ::SQUARESERVEXCODE, // ������� ��� ���������� ����������
     SQUARESERVINCODE = ::SQUARESERVINCODE, // ���������� ��� ���������� ����������
     POINTSERVEXCODE  = ::POINTSERVEXCODE , // ������� ��� ����������  ���������
     POINTSERVINCODE  = ::POINTSERVINCODE , // ���������� ��� ���������� ���������
     TEXTSERVEXCODE   = ::TEXTSERVEXCODE  , // ������� ��� ���������� ������
     TEXTSERVINCODE   = ::TEXTSERVINCODE  , // ���������� ��� ���������� ������
     VECTSERVEXCODE   = :: VECTSERVEXCODE , // ������� ��� ���������� ����������
     VECTSERVINCODE   = ::VECTSERVINCODE  , // ���������� ��� ���������� ����������
     COMSERVEXCODE    = ::COMSERVEXCODE   , // ������� ��� ���������� �������
     COMSERVINCODE    = ::COMSERVINCODE   , // ���������� ��� ���������� �������
     MAXSEMANTICCOUNT = ::MAXSEMANTICCOUNT,
   };

  enum
   {
     SERVOBJECT        = ::SERVOBJECT,        // ���������� ��������� ��������
     COUNTOFTAB        = ::COUNTOFTAB,        // ���������� ������
     COLOROFSERVOBJECT = ::COLOROFSERVOBJECT, // ������ ����� ��������� ��������
   };

 /****************************************************************
 *                                                               *
 *             �������/������� ������ � ����� RSC                *
 *                                                               *
 ****************************************************************/

public :

 TMapRsc();

 ~TMapRsc();

 // ������� ������ � ��������������
 // ��������� ������� �������
 // ��� ������ ���������� ����
 int OpenRsc(const char * rsc, int mode  = 0);

 // ������ ������ � ���������� ������ ��� ������
 // c ����� ���������������
 // ���� ����������� ��������� �� ����� createsem = 0
 // ��� ������ ���������� 0
 int CreateRsc();
 int CreateRsc(char * name, RSCCREATE * rsccreate = 0,
                            PALETTE256 * palette  = 0,
                            int createsem = 1);

 // ������ ����� ������ ��������������
 int GetRscDescribe(RSCCREATE * rsccreate,PALETTE256 * palette);

 // ��������� - ������� ���� ����� ��������, ������������ � ��������������
 // type 0 - ��� ��������, 1- � �������� ����, ������� ����(�������� ��� �������)
 int GetRscObjectCodeType(void);
 int SetRscObjectCodeType(int type);

 // ������� ������� �������
 void CloseRsc();

 // ������ � ������ �������� �����
 int Commit(void);

 // ������ � ������ �������� �����
 int Save(int mode);

 // ������������ ����� RSC
 // ��� ������������ RSC �� �����
 int BackCopy(int restore);

 // �������� ��������� ��������
 int CreateServObjects();

 // ������ ������ ������ ������� ��������
 TABRSC * GetTabRsc(int incode)
   {
     if (!IsActive()) return 0;
     return(TabRsc + incode);
   }

 // ��������� ������������� �������� ������ �����
 RSCHEAD * GetRscId() { return &Rsc; }

 // ������ ������ ������ ������� ����������� �� ��������� �� ������ (� 1 )
 TABGRSITEM * GetTabGrsItem(int index)
   {
     if (!IsActive()) return 0;
     return (TabGrsItem + index);
   }

 // ������ ������� ������� ����������� �� ���������
 long GetTabGrsCount()
   {
     if (!IsActive()) return 0;
     return TabGrsCount;
   }

 // ���������� �������� �� ������� �����
 int IsActive();

 // ������ - ����� �� ������������� ������������� ?
 int IsWrite();

 // ��������� ��� ����� ��������������
 char * NameRSC() { return RscName; }

 // ��������� ������ (� �����) ��� ����� ��������������
 int GetRscName(char * name, int size);

 const char * GetRscName() { return RscPath; }        

 // ��������� ������������� ����� ��������������
 HANDLE GetFileRSC()
   {
      if (!IsActive()) return 0;
      return File_RSC;
   }

  // ���������/������� ����� �������� ����� ����� API
 int ApiOpenFlag(void);
 int ApiOpenFlag(int);

 // ��������� ��� ������ ���������� ��������� ��������
 // ���� ������ �� ����, ���������� ����
 long int Error();

 // ���������/������� ��������� �����
 int Style(void);
 int Style(int);

 // ���������/������� ����������� �������            
 int ColorStyle(void);
 int ColorStyle(int);

 // ���������/������� ������������� �������������� ��������
 int MaxKey(void);
 int SetMaxKey(void);


 // ���������/������� ����������� �����
 int Mode(void);
 int Mode(int);



 // ���������/������� ���� ��������������
 int ClassificatorCode(char * classificator);
 char * ClassificatorCode();

 // ���������/������� ������ ������� ���������
 int ScaleTableNumber();
 int ScaleTableNumber(int scaletable);

 // ������ �������� �� ������ � ������� �������
 long GetScaleItem(int number);

 // ������ �������� �� ������ � ��������� ������� ���������(0,1)    
 long  GetTableScaleItem(int tablenumber, int number);

 // ���������/������� ����� ��������������
 int GetClassificatorLanguage();
 int SetClassificatorLanguage(int language = ML_RUSSIAN );

 // ������ ���� �������� �����
 char * Date();

 // ���������/�������  �������� �����
 long Scale();
 long Scale(long scale);

 // ���������/�������  ���� ��������������
 char * Type();
 char * SetType(char *str);

 // ���������/�������  ����� ��������������
 char * Name();
 char * SetName(char *str);

 // �������� ��������� � Rsc
 int SetModify(void);

 // ��������� - ���� �� ��������� RSC
 int IsModify();

 // ��������� ������ ������ ��������������
 // ���� �������� �������� - ����� ������������� ������
 // ��� ������ ���������� ����
 int LoadOldVersion(const char * oldrsc, const char * newname, long scale);
 int CheckAndLoadOldVersion(const char * name, long scale);   

 // ���������� ������������ ����� ������� �������������� �
 // ������ � �� �����
 // 1  - ������ ���������
 // 0  - ������
 // -1 - ��������
 int AdjustData(void);

 // ��������� ������ ����� ��������������
 // ��� ������ ���������� 0
 long int FileSize();

 // ������������ ������������� � �����
 int Revert(void);

 // ������ �������������� - ���������� � ������
 // ������������ 0 ��� �������
 int Press(void);                            

 // �������� ������ �� ��������
 // size - ������ ������
 // ������� ��������� � �������� �������.
 // ��� ������ ���������� 0
 int ClearofBlank(char * name,int size);

 // ������ ����������� ������ �������� �� ����� (���������� ����� � 0)
 // Type - ��� ������� : ��� ���� �� ����� - 1,
 //                      ��� ���� �� ��������� ����� - 2,
 //                      ��� ��������� �� ����� - 3,
 //                      ��� ��������� �� ��������� ����� - 4,
 //                      ��� ������� �� ����� - 5
 // ��� ���������� - 0 , ��� ������ IDS_NOTFIND
 int GetElementbyName(char * name,int type);

 // ���������� ��� ������ ���������� ��������� ��������
 long int Error(int error);

 protected :
 // ������� ������ � ��������������
 // ��������� ������� �������
 // ��� ������ ���������� ����
 int OpenRsc();

 /****************************************************************
 *                                                               *
 *             ������ � ������� �������������� (RSC)             *
 *                                                               *
 ****************************************************************/

public :

 // ������ �������������� �������� �������  �� ����������� ������ (� 1)
 TABPAL * GetTabPal(int number);

 // ������ ������ �������  �� �� ������                              
 COLORREF * GetPalette(int number = 1);

 //  ������ ���������� ������
 int GetPaletteCount();                                              

 // ������ ����� ������� �� ������ (� 1)                             
 char * GetPaletteName(int number);

 // ���������� ��� ������� �� ������ (� 1)                          
 // ���������� ����� ������������ �������
 int SetPaletteName(int number,char * name);

 // ������� ������� �� ������ (c 1)(���� ������� �� ���������)      
 int  DeletePalette(int number);

 // ������ ���������� ������, ����������� � ��������������
 int GetRscColorCount();

 // ���������� ���������� ������, ����������� � ��������������
 int SetRscColorCount(int number);

 // ������ �������� ����� �� ������� � �������
 COLORREF GetRscColor(int index);

 // ������ ������ ����� � ������� index ������ �������
 COLORREF * GetRscPalette(int index = 0);

 // ���������� ��� ������� (����� ������� c 1)
 int SetRscPalette(COLORREF * colorref,int number);

 // ���������� ���� � �������
 // ���������� ������ ����
 COLORREF SetRscColor(COLORREF color,int index = 0);

 // ������������ ������� � ����� �� ������ �������  (� 1)
 // ���������� ������� � �������������
 // ���������� ����� �������
 COLORREF * ResetPalette(int number = 1);       

 // ���������� ��������������� ������� (c 1) �� ���������
 // ���������� ����� �������
 COLORREF * SetDefaultPalette(int number = 1);  

 //  ������ �������� ������������� ����� �� ������� � �������
 COLORREF GetDefaultColor(int index);

 // �������� ����� �������
 // palette - ����� �������,count - ���������� ������ � �������
 // name    - �������� �������
 // ���������� ��������� �� ��������� �������
 // 0 - ��� ������
 TABPAL * AppendPalette(COLORREF * palette,int count,char *name );

// ��������  �������
// number  - ����� ���������� ������� (���� ������ ��� ������� �����������)
// palette - ����� �������,count - ���������� ������ � �������
// name    - �������� �������
// ���������� ��������� �� ��������� �������
// 0 - ��� ������
TABPAL * ReplacePalette(int number,COLORREF * palette,int count,char *name);

// �������������� ������� �� RGB � CMYK                       
// number - ���������� ������
// rgb - ����� �������(COLORREF)
// cmyk - �����, ��� ���������� ������� CMYK (4 ����� �� ����)
int CreateCMYK(long int count,char * rgb,char * cmyk);

// ��������� ������� CMYK                        
// number - ���������� ������������ ������
// begin  - ������� CMYK ������
// 0 - ��� ������

int SetCMYKPalette(long number,long * begin);

// ��������� ������� CMYK                        
// ���������� ����� CMYK �������
// 0 - ��� ������
char * GetCMYKPalette();


 /****************************************************************
 *                                                               *
 *     ������ � �������� ����������� ����������� �����           *
 *                                                               *
 *    ����������� ���������� � 0                                 *
 *                                                               *
 ****************************************************************/

 // ������ ���������� �����������
 int GetLocalCount() {return 6;}

 // ������ �������� ����������� �� �� ������ (0 - ��������, ...)
 // �������� �������� �� ���� ������ ...
 const char * GetLocalName(int local,int language = ML_RUSSIAN);

 // ������ ����� ����� �����������
 int GetLocalNameSize() {return 16;}

 /****************************************************************
 *                                                               *
 *     ������ � �������� ��������� (�����) ����������� �����     *
 *                                                               *
 *    ���������� ���� ��������� ���������� � 0                   *
 *    ��� ������ ������� 0                                       *
 *                                                               *
 ****************************************************************/

public:

 // ������ �������������� �������� �������� �� �����������
 // ���� c�������
 TABSEG * GetTabSeg(int incode);

 // ��������� ��������� �������� �����
 // RSCSEGMENT -  ��������� ������� ������  (��. maptype.h)
 // incode - ���������� ����� ����
 // ��� ������ ���������� ���� ( ��� ������ �� ����� 0 )
 // ����� ���������� ����� ����
 int GetSegment( int incode, RSCSEGMENT *segment);

 // ������ ���������� ���������
 int GetSegCount();

 // ������ ����� �������� �� ����������� ���� ��������
 char * GetSegName(int incode);

 // ������ ����������� ���� �������� �� �����
 // ��� ���������� �������� ������� - 0 , ��� ������ IDS_NOTFIND
 int GetSegmentByName(char * name);

 // ������ ����� ����� ��������
 int GetSegNameSize();

 // ������ ��������� ����� �������� �� ����������� ���� ��������
 const char * GetSegShortName(int number);

 // ������ ������� ������ �������� �� ����� �� ����������� ���� ��������
 int GetSegOrder(int incode);

 // ������ ���������� �������� �������� �� ����������� ���� ��������
 int GetSegmentObjectCount(int incode);

 // ������ ���������� �� ��������� �������� �������� �� ����������� ���� ��������
 int GetSegmentObjectRealCount(int incode);            

 // ��������� ����� �������� �� ����������� ���� ��������
 int SetSegName(int incode,char * name);

 // ��������� ��������� ����� �������� �� ����������� ���� ��������
 int SetSegShortName(int incode,char * shortname);

 // ��������� ������� ������ �������� �� ����������� ���� ��������
 int SetSegOrder(int incode,char order);

 // �������� ����� ������� - ���������� ���������� N �������� � 1
 int AppendSeg(RSCSEG * rseg);
 int AppendSegment( RSCSEGMENT * segment);

 // ������� ������� �� ����������� ����  ��������(��������� ���� �� ���������)
 int DeleteSegment(int incode);

 // ��������� ������� �� ������ ���� � ������
 // �� ���������� ���� � � ��������� ���� - ������� �� �����������
 // ���������� ����� ����� ����, ���� 0 - ������
 int MoveSegmentObjects(int oldcode,int newcode);

 /****************************************************************
 *                                                               *
 *       ������ � �������� ����� ��'����� ����������� �����      *
 *                                                               *
 *   ���������� ���� �������� ���������� � 1.                    *
 *   ��� ������ ������� 0 .                                      *
 *   ���� ��� �������������� �������� 0 �������� ����� ��������  *
 *   ��������� IsActive();                                       *
 *                                                               *
 ****************************************************************/

public:
// ������ �������������� ������������� �������� �� ����������� ����
// TABPOS * GetTabObj(int incode);

 // ������ ���������� ��������
 int GetObjCount();

 // ������ �������� �������  �� ����������� ����
 // ���� ��� = 0 - ���������� �� ���������
 int GetDescribeObj( int incode,RSCOBJECT * object);

 // ������ �������� ���� ������� �� ����������� ����
 long GetObjExcode(int incode);

 // ������ �������� ���� ���������� ������� �� �����������
 long GetServObjExcode(int local);

 // ������ ���������� ������� �� ����������� ����
 int GetObjExtend(int incode);

 // ������ ����� ����������� ������� �� ����������� ����
 //int GetObjFlags(int incode);

 // ������ ������� ����������� ������� �� ����������� ����
 // ������������ �������� �� ������ ��������� ��������
 // ������� GetLastFunction()
  int GetObjFunction(int incode);

 // ������ ����������� ���� ������� �� �������� ���� � �����������
 // ��� ������ ���������� 0
 int GetObjIncode(long excode,int local);

 // ������ ����������� ���� ������� �� �������� ����, �����������
 // � ����������
 // ��� ������ ���������� 0
 int GetObjIncode(long excode,int local,int extend);

 // ������ ����������� ���� ������� �� �������� ����, �����������
 // � ��������� �������
 // ��� ������ ���������� 0
 int _fastcall GetObjIncode(long excode,int local,TObjectSemn semn);

 // ������ ���������� �������� � ������ ������������ � ������ ����
 int  GetSegmentObjNumber(int segment,int local);

 // ������ ���������� �������� � ������ ������� ����� � ������������
 // ��� ������ ��� ���������� ���������� 0
 int GetObjNumber(long excode,int local);

 // ���������������� ������ ����������� ���� ������� �� ��������
 // ���� � ����������� ���� ����������� ������� (��� ����������
 // ����������� ���� - ����� � ������� �������
 // ��� ������ ���������� 0
 int GetNextObjIncode(long excode,int incode = 0);

 // ������ ����������� ���� ���������� ������� �� �����������
 int GetServObjIncode(int local);

 // ������ ����������� ������� �� ����������� ����
 int GetObjLocal(int incode);

 // ������ ����������� ����������� ������� �� ����������� ����
 int GetObjExtloc(int incode);

 // ������ ����� ������� �� ����������� ����
 const char * GetObjName(int incode);

 // ������ ����� ������� �� ����������� ����
 const char * GetObjKey(int incode);

 // ������ �������������� ������� �� ����������� ����
 long GetObjIdent(int incode);

 // ������ ����������� ���� ������� �� ��������������
 long GetObjIdentIncode(int ident);

 // ������ ����������� ���� ������� �� �����
 long GetObjKeyIncode(const char * key);

 // ������ ����� ����� �������
 int GetObjNameSize();

 // ������ �������� ������� �� ����������� ����
 int GetObjSegment(int incode);

 // ������ ������� ������� ��������� �� ����������� ����
 int _fastcall GetObjBot(int incode);

 // ������ ������ ������� ��������� �� ����������� ����
 int _fastcall GetObjTop(int incode);

 // ������ ���������������� ������� �� ����������� ����
 int _fastcall GetObjScale(int incode);

 // ������ ����������� ������� �� ����������� ����                
 int _fastcall GetObjPress(int incode);

 // ������ ����������� ���������� ������� �� ����������� ����
 int GetObjDirect(int incode);

 // ������ ������ ��������� ������� ������������
 int GetLastFunction();

 // ������ ����������� ���� ����� �����
 // ��������� ����������� ������ - ������� 0
 int GetFrameCode();

 // ������ �������� ���� ����� �����
 long GetFrameCodeEx();

 // �������� ������������� � �������� ��� �������������
 // ����� ����� ������� 1
 // ��������� ����������� ������ - ������� 0
 int CheckFrameCode();

 // �������� ������� ��� ������� �� ����������� ����
 // �������� �� ������� ����� �� ��������
 long SetObjExcode(int incode,long excode);

 // �������������� ������� ��� �������
 // ���������� ����� ������� ��� ���������
 // �������� �� ������� ����� �� ��������
 long UpdateObjExcode(int incode,long newexcode);

 // �������������� ����������� �������
 // ���������� ����� ������� ��� ���������
 // �������� �� ������� ����� �� ��������
 long UpdateObjLocal(int incode,int newlocal);

 // �������� ���� ����������� ������� �� ����������� ����
 //int SetObjFlags(int incode,int flag);

 // �������� ������� ������� �� ����������� ����
 // (������� ����� ���� ����� 0)
 int SetObjSegment(int incode,int seg);

 // �������� ������� ����������� ������� �� ����������� ����
 // (������� ����������� ����� ���� ����� 0)
// int SetObjFunction(int incode,int number);

 // �������� ����������� ������� �� ����������� ����
 // (����������� ������� ����� ���� ����� 0)
 // ���� ������� ����������� ������������� �������,
 // ��� ������� �� ����������.
 // �������� �� ������� ����� �� ��������
 int SetObjLocal(int incode,int loc);

 // �������� ����������� ����������� ������� �� ����������� ����
 // (����������� ����������� ������� ��������� �������� 0 ��� 1)
 // ��������� �� "����������� �������" (1- ����������� �� 2 ������)
 int SetObjExtloc(int incode,int exl);

 // �������� ���������������� ������� �� ����������� ����(0/1)
 // 1 - ���������������� �������� :
 // ��� �������� - ���������� ������ �����,
 // ��� ���������
 // ��� �������    - �������� ���� ������� �������������
 //                  ���������� ����� 2 ������� ������� �������
 // ��� ��������   - ���� �� ��������� ��� ���������� �������� �����

 int SetObjScale(int incode,int scale);

 // �������� ����������� ������� �� ����������� ����(0/1)
 // 1 - �� �������
 int SetObjPress(int incode,int press);

 // �������� ��� ������� �� ����������� ����
 char * SetObjName(int incode,char * name);

 // �������� ���� ������� �� ����������� ����           
 char * SetObjKey(int incode,char * key);

 // �������� ������� ������� ��������� ������� �� ����������� ����
 int SetObjTop(int incode,int top);

 // �������� ������ ������� ��������� ������� �� ����������� ����
 int SetObjBot(int incode,int bot);

 // �������� ����������� ���������� ������� �� ����������� ����
 int SetObjDirect(int incode,int direct);

 // ������� ����� ������ - ���������� ���������� ��� �������
 // ���� ��� ������ - �� ����� ������������� ��������� �� �������
 // ��� �������,��� �������� �������������� ���������� �������
 // �� ���� + ����������� ����� = 1
 int AppendObject(RSCOBJ * robj,int check = 1);

 // ������� ����� ������ - ���������� ���������� ��� �������
 // ������� ��� ���������� ������� ������������� ���������� ������� (��� ������
 // �����������).
 // ���� ��������� ���� ��� �������� �������  �� ���������� - ������
 // ��������� � ��������� ����
 // ���� ����� ������ (������� ��� � �����������) ��� ���������� -
 // ������ �� ��������� - ������� 0.
 // ��� ������ - ���������� 0, ����� ���������� ��� ���������� �������
  int AppendObjectDefaultView(RSCOBJECT * robj);

 // ������� ������ - ���������� ���������� ��� ���������� �������
 // ���� ������ ������ � ����� - �������� �� ��������
 int DeleteObject(int incode);

 // ������� ������ �� ����� - ���������� ���������� ��� ���������� �������
 // ���� ������ �� ������ � ����� - �������� �� ��������

 int DeleteSeriaObject(int incode);
 // ����������� ������ �� ����� �����
 // (c ������� ����� FIRSTSERVEXCODE)
 // ��������� ������ �� ����������
 // ���������� ���������� ��� ������ �������
 // ��� ����,����� ������ ������ ������� ��� ���������� ������-
 // ��������, ������������ ������ �������������� ������� ��� �������
 int CopyObject(int oldincode);

 // ����������� ������ �� ��������� �� ����������� ���� �����
 // (������� ��� ����������)
 // ���� ������ ������ ������ � ����� - ����������� �� ��������
 // ���������� ���������� ��� ������ �������
 int CopyObject(int newincode,int oldincode);

 // ��������� ��� ������� �������������� ��������� ���� + ��������-
 // ���. ��� ���������� ���������� 0
 int CheckObjectCode(unsigned long code,int local);

 // ����������� ������� �� ������� �������������� -
 // ���������� ���������� ��� ������ �������
 int CopyObject(TMapRsc * source,int oldincode,int segment,TMap * map);

 // �������� �������� �������  �� ����������� ����
 // ��� ������� ����� ������� ��� � ����������� � ���� - �� ��������
 // ���� ������� ��� �� ������������� ������ �������� -
 // �������� ������� ��� �� ������������
 // ���������� ���������� ��� , ���� 0
 int UpdateObject( int incode,RSCOBJECT * object);

 // ���p����� ���������� ��������� �������� �������        
 int _fastcall GetObjectRelateCount(int incode);

 // ���p����� �������� ��������� ������� �� ����������� ���� ������� �  
 // �� ����������� ������ ��������� ������� (� 1)
 // ���������� ������������� �������
 // ��� ������ ���������� 0
 int GetObjectRelateOrder(int incode,int order,RSCRELATION * relate);

 // ���p����� �������� ��������� ������� �������           
 // �� ������ ���������
 // ��� ���������� ������� ���������� 0
 int GetObjectRelate(int incode,int semanticcode,RSCRELATION * relate);

 // �������� �������� ���� �������� �������� ��������� �������  
 // ���������� ������������� �������  , ���� 0
 int UpdateObjectRelate(int incode,int semanticcode,int ident,char * prefix,
                        int decimal);

 // ������� ��������� ������� ������� �� �������������� �������        
 // ���������� ���������� ��������� ��������� ��������
 int DeleteObjectRelateIdent(int incode,int ident);

 // ������� ��������� ������� �� ��������� ���������                   
 int DeleteObjectRelate(int incode,int semanticcode);

 // ������� ��� ��������� ������� ����������� �� ������ ������         
 // ident - ������������� �������
 // ���������� ���������� ��������� ��������� ��������
 int DeleteObjectRelationText(int ident);

 // ����� ��������� ������ ����� ���������� ������� ��������� �������  
 // ����������� �� ������ � ������ ���������������
 // ���������� ���������� ���������� ��� �������.
 // ���� ����� ������ ��� 0
 int CheckRelation(int ident,int order);

 // ���������� ������� ������� ��������� ��� �������� �� ����������  
 // �������� (������� ����� (�������) ��������� ������� � ������� ���������
 // ���������� ���������� ������������ ��������
 int SetObjectView(unsigned long scale);

protected:

 // ���������� ������������� �������� ������� �� ����������� ����
 //TABPOS * SetTabObj(int incode,TABPOS * aobj);


 /****************************************************************
 *                                                               *
 *       ������ � �������� �������� ����������� �����            *
 *                                                               *
 ****************************************************************/

public:

  enum
   {
     HEADIDENT      =::HEADIDENT, // ������������� ������ ���������
                                  // ��� ��������������
     MINVALUESEMSER = -32760,  // ����������� �������� ���������
     MAXVALUESEMSER = 32760,   // ������������ �������� ���������
                               // ��� ������� ����� ��� �������.
   };

 // ������ ���������� �������� �������������� ��  ����
 // ������������� ��������������
 int GetClassificatorCount(int incode);

 // ������ ��������� �������� �������������� ��  ����
 // ������������� �������������� � ����������� ������ (� 1)
 int GetClassificatorValue(int incode,int number);

 // ������ "�����" �������� �������������� ��  ����
 // ������������� �������������� � ����������� ������ (� 1)
 const char * GetClassificatorName(int incode,int number);

 // ������ �������������� �������� �������������� ��  ����
 // ������������� �������������� � ����������� ������ (� 1)

 TABCLS * GetTabCls(int incode,int number);

 // ������ ���������� ��������
 int GetSemCount();

 //  ��������� ����������� ��������� �������� ������������� �������-
 //  ������� �� �������� ���� ��������� � ����������� ���� �������
 //  semtype - ����� ���������, � ������� ����� ��������
 //  �������� ��������������,
 //  code - ��� ���������,
 //  objincode - ���������� ��� �������.
 //  ��� ������ ���������� ����
 int SemanticDescribeEx(RSCSEMANTICEX *semtypeex,             
                         int code, int objincode);

 // ������ �������� �� ������� ��������� � ������
 TABSEM * GetOffSem();
                                                              // tdc
 // ������ ����� ��������� �� ����
 // ������������� ��������������
 const char * GetSemName(int code);

 // ������ ����� ��������� �� ����������� ������
 // ������������� �������������� ( � 1 )
 const char * GetSemOrderName(int number);

 // ������ �������� ���� ��������� �� ����������� ������
 // ������������� �������������� (� 1 )
 int GetSemOrderExcode(int number);

 // ������ ����� ����� ���������
 int GetSemNameSize();

 // ������ ������������� �������� ��������� �� ����
 int GetSemReply(int code);

 // ������ �������� ��������� ��������� �� ����
 int GetSemService(int code);

 // ������ ���� �������� ��������� �� ����
 int GetSemType(int code);

 // ������ "�����" �������� �� ���� ��������� �
 // ���� ��������
 const char * GetSemValueName(int code,int value);

 // ������ ��������� ����� ��������� �� �������� ����
 const char * GetSemShortName(int excode);

 // ������ ����� ����� ���� �������� ���������
 int GetSemValuePoleSize(int code);

 // ������ �������� �������� ���������
 int GetSemValuePoleDecimal(int code);

 // ������ ������������ ����� "�����" ��������
 int GetSemValueSize();

 // ������ ������������ ������� ��������� ���������
 // ���� ��� ������� ��������� - ���������� ���������
 // �� ������ ������
 // ��� ������ ���������� ������ ������ (��. ��� ������)
 const char * GetSemUnit(int code);

 // ������ ������������ ����� ������������ ������� ���������
 int GetSemUnitSize();

 // ��������� ��� ��������� �������������� ����
 // ��� ���������� ���������� 0
 int CheckSemanticCode(int code);

 // ��������� ��������� ����� ���������� �� �������� ���� ���������
 int SetSemShortName(int excode,char * shortname);

 // ��������� ������� � �������� �������� ���������
 int SetSemDecimal(int excode,int size,int decimal);

 // �������� ����� ��������� - ����������
 // ��������� �� ��������� ���������
 TABSEM *  AppendSemantic(RSCSEM * rsem);

 // �������� ����� ��������� - ����������  ��� ��������� ���������
 unsigned long AppendSemantic(RSCSEMANTICEX * rsem);

 // �������� ����������� ���������
 // ��� ������ ���������� 0
 unsigned long AppendStandardSemantic();

 // �������� ��������� ���������
 // ��� ������ ���������� 0
 unsigned long AppendSystemSemantic();

 // �������� ���������
 // rsem - ����� ���������, c ��������� ��������������,
 // code - ��� ��������� ������� ���������,
 // ���������� ��� ������������ ���������
 // ���� ������������� ����������� - classupdate = 1  ��� ����
 // ������� ����� ��� ������ ������������� ��������������
 // ��� ������ ���������� 0
 // ��������� ��������������� ��� ������
 int UpdateSemantic(int code,RSCSEMANTICEX * rsem,int classupdate=0);

 // ������� ���������
 // ��������� �������� �� ����������� �� ���������
 // ��� �������� ����� ��������� ������������� �������� ���� ������� �����,
 // ������������ ������ ���������
 int DeleteSemantic(int code);

 // ��������� ��� �������������� �������������� �������� ��������
 // ��� ���������� ���������� 0
 int CheckClassificatorCode(int semanticcode,int value);

 // �������� ����� "�������" ��������������
 // (�������� �������� � ����������) ����������
 // ��������� �� ������������ ���������
 TABSEM *  AppendCls( int codesemantic,short int value,char * name);

 // ������ �������������� �������� ��������� �� ����
 // ������������� ��������������
 TABSEM * GetTabSem(int incode);

 // ������ �������������� �������� ��������� �� ����
 // ������������� �������������� (����������)
 TABSEM * GetTabSemEx(int code);

 // ������ ������������� ��������� � �������� ��������������
 int GetSemInfo(int code,APPLYSEMANTIC * applysemantic);

 // ����������� c�������� �� ������� �������������� -
 // ���������� 1 - ������� ����������
 int CopySemantic(TMapRsc *source,int oldcode);

 // �������� ���������� �������� �������������� �� ������ � 1
 // ���������� ����� ��� 0
 int UpdateClassificatorName(int semanticcode,int index,char * name);

 /****************************************************************
 *                                                               *
 *  ������ � �������� � �������������� ��������� ��������        *
 *                                                               *
 ****************************************************************/

public:

 // ������ �������������� �������� ��������� �������� �� �����������
 // ���� �������
 TABPOS * GetTabPos(int incode);

 // ������ ���������� ��������� �������� �� ����������� ���� �������
 int GetObjOnlyPosSemCount(int incode);

 // ������ ���������� ��������� �������� �� ����������� ���� �������
 // c ������ ��������� ��� ���� � ����� ��������                     
 int GetObjPosSemCount(int incode);

 // ������ ���������� ������������ �������� �� ����������� ���� �������
 int GetObjMustSemCount(int incode);

 // ������ ���� ��������� ��������� �� ����������� ���� ������� �
 // ����������� ������ � ��������� ���������� (c 1)
 int GetObjOnlyPosSem(int incode,int number);

 // ������ ���� ��������� ��������� �� ����������� ���� ������� �
 // ����������� ������ � ��������� ���������� (c 1)
 // c ������ ��������� ��� ���� � ����� ��������                     
 int GetObjPosSem(int incode,int number);

 // ������ ���� ��������� �� ����������� ���� ������� �
 // ����������� ������(c 1) � ������ ���������� ������������
 // ��������� ��� ���� � ����� ��������� ���� � �����         
 int GetObjOrderSem(int incode,int number);

 // ������ ������� ������ ���� ��������� �� ����������� ���� �������
 // � ������ ���������� ������������
 // 0 - ��������� �� ����������� ������� ���� �����           
 int GetObjSemOrderNumber(int incode,int semcode);

 // ������ ��������� ������� �����������?
 // 0 - ���, 1- ��                                           
 int IsObjSemOrdered(int incode);

 // �������� ������� �������� ��� ������� � ������������ � ������� �������
 // count - ������ ������� �������� �������
 // semantics - ��������� �� ������������� ������ �������� �������.
 // ��������� ������� �� �������� ������� (� ��� ����� � �����) - ������������,
 // ���� ����� - �� ��������� ��������� ������� � ����� ������
 // ��� ���������� ���������� ���������� ���������� �������� �������
 int SetObjSemanticOrder(int objincode,int count,long * semantics);

 // ��������������� ������ �������� ��� ������� � ������������ �
 // ����������� ��������
 // count - ������ ������� �������� ������� ��� ����������
 // semantics - ��������� �� ������ ������� ��������� �������� �������.
 // order     - ��������� �� �������� ������ �������� ����������������
 // ����������� �������� ������� ��������(� 1 )
 // ��� ���������� ���������� ���������� 1
 int SortObjSemantic(int objincode,int count,long * semantics,long * orders);

 // ������ ���� ������������ ��������� �� ����������� ���� ������� �
 // ����������� ������ � ��������� ���������� (c 1)
 int GetObjMustSem(int incode,int number);

 // ������ ������������� ��������� ��� ������� �� ����������� ����
 // � ���� ���������
 // c ������ ��������� ��� ���� � ����� ��������                    
 int GetObjCanSem(int incode,int codesem);

 // ������ ������������� ��������� ��� ������� �� ����������� ����
 // � ���� ���������
 int GetOnlyObjCanSem(int incode,int codesem);

 // ������ ���������� ��������� �������� �� ����������� ���� �������
 int GetObjLimSemCount(int incode);

 // ������ ���� ��������� ��������� �� ����������� ���� ������� �
 // ����������� ������ � ��������� ���������� (c 1)
 int GetObjLimSem(int incode,int number);

 // �������� ��������� �������
 // seria = 1 ,e��� ������ �� �����
 // t�pe - ��� ��������� (�� maptype.h SEMANTIC_FOR_OBJECT)
 // ���������� �� ���������������� �����
 // � ���������� ������� ���� (������� � 1)
 int AppendObjectSemantic(int objincode,int semincode,int type,int seria = 0);

 // ������� ��������� ���� ������������ ��������� � �������
 // seria = 1 ,e��� ������ �� �����
 // ��� ���������� ���������� ���������� ���������� ��� �������
 int DeletePosSemantic(int objincode,int semincode,int seria = 0);

 // ��������� ��������� - �������������� � ���������� �� ������.
 // seria = 1 ,e��� ������ �� �����
 // ���������� ���������������� ����� (� 1) � ��������� ����������
 // ���� ����� �� ���� - ���������� 0
 int SetTypePosSemantic(int objincode,int semincode,int seria = 0);

 // ��������� ��������� - ������������ � ���������� �� ������.
 // seria = 1 ,e��� ������ �� �����
 // ���������� ���������������� ����� (� 1) � ������������
 // ����������
 // ���� ����� �� ���� - ���������� 0
 int SetTypeMustSemantic(int objincode,int semincode,int seria = 0);

 // ��������� ���������� �������� ��� ���� �� ����������� ������
 // ���� � 0
 long GetSegSemCount(int number);

 // ��������� ��� ��������� �� ����������� ������ ���� � ������
 // ��������� � ������ (� 1)
 long GetSegSemCode(int numberseg,int order);

 // �������� ��� ��������� � ������ ���� � ���������� �������
 // numberseg ( c 0)
 long AppendSegSemCode(int numberseg,long code);

 // ������� ��� ��������� �� ������ ���� � ���������� �������
 // numberseg ( c 0)
 long DeleteSegSemCode(int numberseg,long code);

 // ������� ������ �������� ��� ����
 // index - ���������� N ���� (c 0)
 // type - ��� �������� ��� ����� 0 - ���
 //                               1 - ������ ������������
 // ���������� ��������� �� ������������ ����
 TABSEG * BuildSegmentSemantic(int index,int type);

 // ������� �������� ��������� �������� �� ����������� ���� �������
 // seria = 1 ,e��� ������ �� �����
 // ���� ����� ���� - ������������ ��������� �� ������������ �������
 TABPOS * AppendPos(int incode,int seria = 0);

protected:

 // ���������� ������������� �������� ��������� �������� �� �����������
 // ���� ���������
// TABPOS * SetTabPos(int incode,TABPOS * apos);

 // ������� �������� ��������� �������� �� ����������� ���� �������
 // seria = 1 ,e��� ������ �� �����
 // ���� ����� ���� - ������������ ��������� �� ������������ �������

 int DeletePos(int incode,int seria = 0);

 // �������� ��������� ��������� �������
 // seria = 1 ,e��� ������ �� �����
 // ���������� �� ���������������� �����
 // � ��������� ���������� (������� � 1)
 int AppendPosSemantic(int objincode,int semincode,int seria = 0);

 /****************************************************************
 *                                                               *
 *  ������ � �������� � �������������� ������� ���������         *
 *                                                               *
 ****************************************************************/

public:

 // ������ �������������� ������� ���������� �������� ���������
 // �� ����������� ���� ������� � ����������� ���� ���������,
 // ���� �� ����� ��������� �� ������ ������ ������������ �����
 // ��������� ��� ������ ���������
 // ���� �� ����� ���������� 0
 TABDEF * GetTabDef(int objincode,int semincode);

 // ��������� ������� ������� ���������� �������� ���������
 // �� ����������� ���� ������� � ���� ���������,
 // ���� �� ����� ���������� 0
 TABDEF * CheckTabDef(int incodeobject,int semcode);

 // ������ ��������,��������� � ��������� �������� ���������
 // �� ����������� ���� ������� � ���� ���������
 // ���� �� ����� ���������� 0
 int GetDefValue(int incodeobject,int semcode,RSCDEF * def);

 // ������ �������� ����������� �������� ���������
 // �� ����������� ���� ������� � ����������� ���� ���������
 // �������������� �������� ������� ������ ���������
 // CheckTabDef(int objincode,int semincode);
 // ���� �� ����� ���������� 0
 // ��� ������  IDS_NOTFIND
 float GetDefMin(int objincode,int semincode);

 // ������ �������� ��������� �� ���������
 // �� ����������� ���� ������� � ����������� ���� ���������
 // �������������� �������� ������� ������ ���������
 // CheckTabDef(int objincode,int semincode);
 // ���� �� ����� ���������� 0
 // ��� ������  IDS_NOTFIND
 float GetDefDef(int objincode,int semincode);

 // ������ ��������� ����������� �������� ���������
 // �� ����������� ���� ������� � ����������� ���� ���������
 // �������������� �������� ������� ������ ���������
 // CheckTabDef(int objincode,int semincode);
 // ��� ������  IDS_NOTFIND
 // ���� �� ����� ���������� 0
 float GetDefMax(int objincode,int semincode);

 // ������ �������� ��������� �� ���������
 // �� ����������� ���� ������� � ����������� ���� ���������
 // �������� ������������� � ���������� ������
 // ���� �� ������ ���� ������ - ���������� ������������ �����-
 // ��� ���������,���� ��� ������������� ����������� ���� �������
 // ����� - ������ ��������������� ����������� ���� �������
 // ���������� 1,��� ������ 0
 int GetDefValueSemantic(int objincode,int semanticcode,
                         char * strdef,int lenstr);

//protected:  

 // �������� ����� ��������� �� ��������� ��� �� ������
 // ���������� ��������� �� ������������ ���������
 TABSEM * AppendDef(int incodeobject,int semanticcode,
                   float objmin,float objdef,float objmax);

 // ������� ��������� �� ��������� - ����� (objincode = 0)
 // ��� �� ������
 // ���������� ��������� �� ������������ ��������� (������ - 0 )
 TABSEM * DeleteDef(int objincode,int semincode);

 // ������� ��������� �� ������ �� ����� ����������
 // ���������� ��� ������� (������ - 0 )
 int DeleteDefObject(int incode);

 // �������� ��������� �� ��������� - ����� (objincode = 0)
 // ���� �� ������
 // ���� ���������� ��������� �� ����� - ������� �����
 // ���������� ��������� �� ������������ ��������� (������ - 0 )
 TABSEM * UpdateDef(int incodeobject,int semanticcode,
                   float objmin,float objdef,float objmax);


 /****************************************************************
 *                                                               *
 *     ������ � �������� � �������������� ������� �������        *
 *                                                               *
 ****************************************************************/

public:

 // ������ �������������� �������� ������� �� ����������� ���� �������
 TABLIM * GetTabLim(int incode);

 // ��� �������� ����� ����� �� ������������� �������       23.12 n.
 TABLIM * InitSeria(long excode,int local);

 // �������� ������ �������� � ����� �� ����������� ���� � ����� ����������
 // ����� - ��������� ����������� ���������� (�������� �� �������������� ���),
 // �� ��������� �������������� ��������� ���� � �����������   23.11 n.
                                                      
 int UpdateSeriaObject(int incode,int extend,TABLIM * limit,TABPOS * possemantic);
 // �������� ������� ��� �����                           23/11/ n.
 int UpdateCodeSeria(TABLIM * limit,long excode);
  // �������� ����������� �����                         
 int UpdateLocalSeria(TABLIM * limit,char local);

 // �������� ������������ ��������� �����               24/11/ n.
 // limit    -  ������������� �����,
 // number   -  ���������� ����� ��������� � ����� (1 ��� 2)
 // code     -  ��� ���������,
 // count    -  ���������� ������������� (������ 1)
 // countdef -  ����� ������������� ������������ � 1,
 // gate     -  ����� �������
 // ��� ����������  ���� ���������� ����� �������������
 // ���������� ������� ���������� (����� ���������� - �������� 0)
 // ����������  ������������� ����� ��� ������ ������� �������
 // ��� ������ 0
 TABLIM * UpdateGateSeria(TABLIM * limit,int number,int code,
                             int count,int countdef,double * gate );

 // ������� ����� �����                                          
 // ���� ������ ������ �� ���� ����������  ������������� ������
 // ������� �������
 // ����� ����������  ������������� ����� ������� �������
 // ���������� ������� ���������� (����� ���������� - �������� 0)
 // ��� ������ 0
 TABLIM * DeleteLimit(TABLIM * alim,int number);


 // �������� ���������� ��������� �����               24/11/ n.
 // limit    -  ������������� �����,
 // count    -  ���������� ����������(������ 1)
 // count ������ ��������������� ���������� �� �������������� �����
 // extend   -  ����� ����������
 // ����������  ������������� ������� �������
 // ��� ������ 0
 TABLIM * UpdateExtendSeria(TABLIM * limit,int count,char * extend);

 // ���������� ������������� �������� ������� �� ����������� ����
// TABLIM * SetTabLim(int incode,TABLIM * alim);

 // ������� ����� - ������� ������� ������� � ��� �������
 // �������� � �����,�������� ������ �� ��������� ���������,
 // ������ ���������
 int DeleteSeria(long excode,int local);

 // �������� ��������� �������� ����� �� ������������� �������
 // incode - ���������� ��� ������� c ����� ����������
 // ��� ������� ��������� �������� �� ���� ����� ����� �������������
 // ��������� ������� � �������� incode.
 // ������������ ��� ��������� ������ �� "�������" ��������
 int UpdateSeriaSemantic(int incode);              

 // �������� ����� ������� ������� ��� �������� � ���������� ��������
 // ���������� ������������� �������� ������� �� ����������� ����
 // ident - ������������� �������� ������� - ��������
 TABLIM * CopyTabLim(TABLIM * ident);                    

 // ������ ���������� ������������� �� ������ ���������
 // code     -  ��� ���������
 int GetGateCount(long excode,int local,int code );  

 // �������� ����� ������������ ����� ��������       
 // incode - ���������� ��� ������ �� �������� ����� - ���������
 // ���������� ���������� ��� ������� ������� �����,
 // ��� ������ 0
 long CopySeria(long incode);


 /****************************************************************
 *                                                               *
 *       ������ � �������� ���������� ������������ ��'�����      *
 *                                                               *
 ****************************************************************/

public:

 // ������ ������ ������ ������� ���������� �� ����������� ���� �������
 VIEPAR * GetTabPar(int incode);

 // ������ ������ ������ ���������� ������������ �� ����������� ���� �������
 char * GetPar(int incode);

 // ������ ����� ���������� ������������ �� ����������� ���� �������
 long GetParLength(int incode);

 // ���������� ���� ��� �������, ���������� ������� ����
 // �������� "��������" ���� ����������� ������� �� ���������
 int SetObjColorIndex(int incode,int color);
 int SetObjColor(int incode,COLORREF color);

 // ���������� ����� ������ ������� ���������� �� ����������� ����
 // ���� ������� 0 - ������
 VIEPAR * SetTabPar(int incode,VIEPAR * apar);

 // ���������� ����� ������ ������� ���������� �� ����������� ����,
 // ������ �������,����� � ����������
 // ���� ������� 0 - ������
 VIEPAR * SetTabPar(int incode,int length,int number,char * param);

 // ������� ������� ��� ������������ ������� �� �����������
 int CreateDefaultView(int incode);

 // ������ � �������� ����������� �������
 //  (������ string ������ length �������� ���
 //   ����������� ��������������� ������� �������)
 // ��� ������ ������� 0
 int GetImageSize(int incode,IMAGESIZE * imagesize,
                  int length = 0,const char * string = "");

 // ����� "��������" ���� ����������� �������  �� ����������� ���� 
 // � ���� �����������  0 - ��������, 1 - ����������
 // ��� ���������� ����� ���������� 0xFF000000
 // ��� ������ ���������� 0
 COLORREF GetObjectBaseColor(int incode,int viewtype);

 // ����� "��������" ���� ����������� ��������� �� ������ ������� � ���������� 
 COLORREF GetBasePrimColor(int number, char * param);


 // ����� �� ������� ������� �� �������
 // number - ����� ������� �����������
 // param  - ��������� �����������
 // angle  - ���� �������� ������� ��� ����
 // ��� ������ ������� 0
 // ��� ������� � ��������
 int GetImageFrame(int number, const char * param,
                   double angle, IMAGEFRAME * imageframe);

 // ������� ����� �� ���� a ������������ ����� origin
 int TurnPoint(DOUBLEPOINT * origin,DOUBLEPOINT * point,
               double sina,double cosa);

 // �������� ������������ ����������� � ��������� �� ����������� �������
 // ���� ������ ������������ ��� IMG_DRAW , ���������� ��������� ��� ���������
 // ����������.
 // ��� ������ ������� 0
 int GetImageSuitable(int local,int number);

 // ������ ������� ����������� ��������
 // �� ����� ���������� ���
 // TABLETEMPLATE (���������� � Mapgdi.h)
 // ��� ������ ������� 0
 int GetTemplateTable(int incode,TABLETEMPLATE * table);

 // ������ �������� ���������� ��������� ��� ����������� �������
 int GetObjExtsem(int incode);

 // ��������� �������� ���������� ��������� ��� ����������� �������
 int SetObjExtsem(int incode, int flag );

 /****************************************************************
 *                                                               *
 *       ������ � �������� ���������� ������ ��'�����            *
 *                                                               *
 ****************************************************************/

 public:

 // ������ ������ ������ ������� ���������� ������
 // �� ����������� ���� �������
 VIEPAR * GetTabPrn(int incode);

 // ������ ������ ������ ���������� ������ �� ����������� ���� �������
 char  * GetPrn(int incode);

 // ������ ����� ���������� ������ �� ����������� ���� �������
  long GetPrnLength(int incode);

 // ���������� ����� ������ ������� ���������� �� ����������� ����
 // ���� ������� 0 - ������
 VIEPAR * SetTabPrn(int incode,VIEPAR * apar);

 // ���������� ����� ������ ������� ���������� �� ����������� ����,    
 // ������ �������,����� � ����������
 // ���� ������� 0 - ������
 VIEPAR * SetTabPrn(int incode,int length,int number,char * param);

 // �������� ���������� ��������� �������  �� ����������� ����
 void DeleteTabPrn(int incode);

 /****************************************************************
 *                                                               *
 *       ������ � �������� ���������� ������� ���������          *  // 29//11/00
 *                                                               *
 ****************************************************************/

 public:
 // ������ ���������� ���������                  
 // 0 - ��� ������
 int GetImlCount();

 // ������ ��������� �������� ���������� �� ����������� ������ (c 1)
 // ' ' - ��� ������
 char * GetImlName(int number);

 // ������ ��������� �������� ���������� �� ����������� ������ (c 1)
 // ' ' - ��� ������
 char * SetImlName(int number,char * name);


 // ������ ����� ���������� �� ����������� ������ (c 1)
 // ' ' - ��� ������
 char * GetImlNameDLL(int number);

// ������ ������� ����������(� 1) �� ����������� ������    
// 0 - ��� ������
 int GetImlIndex(int number);

 // ������ ����������� ������ ����������(� 1) �� ����
 // 0 - ��� ������
 int GetImlOrder(int code);

 // ������ ���� �� ����������� ������ ����������(c 1)         
 // 0 - ��� ������
 int GetImlCode(int number);

 // �������� ����� ����������
 // name    - �������� �������� ����������
 // dllname - �������� DLL
 // ���������� ��������� �� ��������� ����������
 // 0 - ��� ������
 TABIML * AppendLibrary(char * dllname,char * name);

 // �������� ����� ����������
 // name    - �������� �������� ����������
 // dllname - �������� DLL
 // ���������� ��� ��������� ����������
 // 0 - ��� ������
 long int CodeAppendLibrary(char * dllname,char * name);    

 // �������� ��������� ���������������� ��������(IMG_LIBRARY)    
 // 0 - ��� ������
 void  SetUserObjectRefer();

 // ������� ������� ���������������� ��������(IMG_LIBRARY)
 void  BreakUserObjectRefer();

#ifndef HIDEIML                 
 // ��������� �������� �������,
 // �������������� ����������� �� �������
 const IMLLIST * GetImageList(int index);
#endif

 // ������� ���������� �� ����           
 int  DeleteLibrary(int code);

 /****************************************************************
 *                                                               *
 *       ������ � �������� ���������� ������� �������            *  
 *                                                               *
 ****************************************************************/

 public:

 // ������ ���������� �������
 // 0 - ��� ������
  int GetFontCount();

 // ������ ��������� ����� ������ �� ����������� ������
 // 0 - ��� ������
  char * GetFontName(int number);

 // ������ ���� ������ �� ����������� ������
 // 0 - ��� ������
  int GetFontcode(int number);

 // ������ ������ �� ����������� ������
 // ���������� ��� ������
 // 0 - ��� ������
 int GetFont(int number,RSCFONT * font);

 // �������� ����� ����� - ����������
 // ��� ������
 // 0 - ��� ������
 int AppendFont(RSCFONT * font);

 // �������� ����� - ���������� ��� ������
 // index - ���������� ����� ������ (� 1)
 // 0 - ��� ������
 int ReplaceFont(int index,RSCFONT * font);          

 // ���������� ������� �������
 // 0 - ��� ������
 int FillFontTable();

 // ���������� ������� �������
 // 0 - ��� ������
 int FreeFontTable();

 // �������� ��������� ������� ( ���������� ������ �� ������� �������)
 // ��� ���������� key = 0,newkey = 0.
 // ��� �������� ������ � ����� key - �������� ��� ������  ��  �����
 // c ����� newkey, ����  newkey = 0, �������� �� 1 �����.
 // 0 - ��� ������
 void  SetTextRefer(int key, int newkey);                       

 // �������� ��������� ������
 // ���������� ���������� ����� ������ � �������
 // 0 - ��� ������
 int SetTextOrder(int key);

 // ������ / ������ ������� ��� ��������� ������ ������ �� ����������� ������
 // 0 - ��� ������
 unsigned char GetFontFixedChar(int number);
 int SetFontFixedChar(int number,unsigned char fixedchar);

 // ������� ����� �� ����� , ���� ����� ������������� ����� �� �������      
 // ���� �������� , newkey - ���� ������� ������. ���� newkey = 0,
 // ����� �������� ����� �� ���������.
 int  DeleteFont(int key,int newkey);

 // ������ ������������� ��������� ��� ����������� ����������������� �������
 long GetUserObjectSemanticFlag(int number, int function);                   


 /****************************************************************
 *                                                               *
 *       �������������� ������� ��������� 3D ����������          *  
 *                                                               *
 ****************************************************************/
#ifndef HIDERSC3D                                                    
 // �������� ������������ ���������� ���������� ����������
 // name    - �������� �������� ����������
 // dllname - ��� ����� .p3d
 // ���������� ��������� �� c�������� ����������
 // 0 - ��� ������
 TABL3D * Append3DLibrary(char * dllname,char * name);

 // �������� ����� ���������� ���������� ����������
 // name    - �������� �������� ����������
 // dllname - ��� ����� .p3d
 // ���������� ��������� �� c�������� ����������
 // 0 - ��� ������
 TABL3D * New3DLibrary(char * dllname, char * name);

 // ������ ���������� ��������� ���������� ����������
 // 0 - ��� ������
 int Get3DLibraryCount();

 // ������ ����������� ������ ���������� ���������� ���������� (� 1)
 // �� ����
 // 0 - ��� ������
 int Get3DLibraryOrder(int code);

 // ������ ���� �� ����������� ������ ���������� 3D ���������� (c 1)
 // 0 - ��� ������
 int Get3DLibraryCode(int number);

 // ������ ���� �� ����� ���������� 3D ����������
 // 0 - ��� ������
 int Get3DLibraryCodeByName(const char * dllname);

 // ������ ���������� ���������� ���������� �� ����
 // 0 - ��� ������
 TABL3D * Get3DLibrary(int code);

 // ������� ���������� ���������� ���������� �� ����
 int  Delete3DLibrary(int code);

 // ������ ����� ���������� ���������� ���������� �� ����
 // 0 - ��� ������
 char * Get3DLibraryName(int code);

 // ������ ����� ����� ���������� ���������� ���������� �� ����
 // 0 - ��� ������
 char *  Get3DLibraryFileName(int code);

 // ������ �������� ���������� ���������� ���������� �� ����
 // 0 - ��� ������
 long Get3DLibraryOffset(int code);


 /****************************************************************
 *                                                               *
 *       �������������� 3D �������                               *  
 *                                                               *
 ****************************************************************/

 // ���������������� 3D �������
 // 0 - ��� ������
 int Init3D();

 // ������ ������� 3D ���������� ������� �� ������ (0,1,2 - ��� 0 - �������)
 // � ����������� ������ (������� ) ������� � 1
 // ��� ���������� ������� - �������� ��������� � ������� �������
 // ��� ������ ��� ���������� 0
 TABP3D * Get3DObject(long incode,long level);

 // ������ ������������� 3D ���������� ������� �� ������ (0,1,2 - ��� 0 - �������)
 // � ����������� ������ (������� ) ������� � 1
 // ��� ������ ��� ���������� 0
 long Is3DParam(long incode,long level);   

 // ������ ����� ���������� ������� �� ������ (0,1,2 - ��� 0 - �������)
 // � ����������� ������ (������� ) ������� � 1
 // ��� ������ ��� ���������� 0
 long Get3DLength(long incode,long level);

 // ������ ������� ����������� ���������� ������� �� ������ (0,1,2 - ��� 0 - �������)
 // � ����������� ������ (������� ) ������� � 1
 // ��� ������ ��� ���������� 0
 long Get3DFunction(long incode,long level);

 // ������ ���� ���������� ����������� ���������� �������
 // �� ������ (0,1,2 - ��� 0 - �������)
 // � ����������� ������ (������� ) ������� � 1
 // ��� ������ ��� ���������� 0
 long Get3DObjectLibraryCode(long incode,long level);

 // ������ ����� ����������� ���������� �������
 // �� ������ (0,1,2 - ��� 0 - �������)
 // � ����������� ������ (������� ) ������� � 1
 // ��� ������ ��� ���������� 0
 long Get3DObjectKey(long incode,long level);

 // ������ ������� ����������� ���������� ������� �� ������ (0,1,2 - ��� 0 - �������)
 // � ����������� ������ (������� ) ������� � 1
 // ��� ������ ��� ���������� 0
 F3DTREE * Get3DParam(long incode,long level);

 // ������� ������ �� ������ (0,1,2 - ��� 0 - �������)
 // � ����������� ������ (������� ) ������� � 1
 // � ������������ �� ���� ���������� � ����� �������
 // ��� ������ 0
 long Set3DImageToObject(long incode, long level,long code, long key);

 // ������ ���������� 3D �����������
 // � ���� ���������� � ����� �����������
 // ��� ������ ��� ���������� 0
 // ����� ��������� ���������� ���������� F3DTREE
 F3DTREE * Get3DImageParam(long code,long key);

// ���������� ��������� 3D �����������
// �� ���� ����������,�����,������ �������,���� �������,
// ����� ���������� � ����������
// ��� ������ ��� ���������� 0
long Set3DImageParam(long code,long key,long type,long length, char * param);

// �������� �������� 3D �����������
// �� ���� ����������,�����
// ��� ������ ��� ���������� 0
long Set3DImageName(long code,long key,char * name);

// ������� ��������� 3D �����������
// �� ���� ����������,���� �������,��������� ��������,
// ����� ���������� � ���������� (���� P3DTREE)
// ��� ������ ��� ���������� 0 , ����� ��� �����������
long Create3DImage(long code,long type,long length,char * param,char * name);

// ������� ������������ ������                                        
// �� ���� ����������
// ��� ������ ���������� 0, ���� ��� - 1 ����� 2
long Create3DDefaultImage(long code);

// ��������� ����� ���������� ������� ��������� ���� � ����������
// (OBJECT_PARAMETERS,OBJECT_TEXTURE ...  rscfl3d.h)
// ��� ������ 0.
long TakeRecordCount(long code,long type);

// ��������� ��������� ������ ���������� ���� �� ����
// ��� ������ 0.
RECHEAD * TakeCodeRecordHead(long code);

// ��������� ��������� ������ �� ���� ���������� � �����            
// ��� ������ ��� ���������� 0
RECHEAD * TakeKeyRecordHead(long code,long key);

// ��������� ��������� �� ��������� ������ ���������� ���� �� ����������� ������
// � ���������� c ������ �����
// ( ��� - OBJECT_PARAMETERS,OBJECT_TEXTURE ...  rscfl3d.h)
// ��������� ��� ������, ��� ������ 0.

long TakeRecordHead(long number,long code,long type,RECHEAD * address);

// ��������� ����� ���������� �������
// ��� ������ 0.
long TakeTextureCount();

// ��������� ����� �������� �� ����������� ������
// ��� ������ 0.
RECTEXTURE * TakeTexture(long number);

// ������� ������ ��������
// �� ���� ����������,��������� ��������,
// ��� ������ ��� ���������� 0 , ����� ��� ��������
long Create3DTexture(long code,RECTEXTURE * texture,char * name);

// �������� ������ ��������
// �� ���� ����������,����� ��������,��������� ��������,
// ��� ������ ��� ���������� 0 , ����� ��� ��������
long Replace3DTexture(long libcode,long key,RECTEXTURE * texture,char * name);

// ������� ������ ��������
// �� ���� ����������,����� ��������
// ��� ������ ��� ���������� 0
long Delete3DTexture(long libcode,long key);

// ��������� ������������� ��������
// �� ���� ����������,����� ��������
// ���������� ���������� ��������, ������������ ������ ��������
// ��� ������ ��� ���������� 0
long _fastcall Used3DTexture(long libcode,long key);

// ��������� ��������� ���� ������ ����������
// �� ���� ���������� � ���� ������
// ��������� ����, ��� ������ 0.
long TakeFreeKey(long code,long type);

// ������ 3D ����������� ������� �� ������ (0,1,2 - ��� 0 - �������)
// � ����������� ������ (������� ) ������� � 1
// ��� ������ 0                                                     
long Delete3DImageFromObject(long incode, long level);

// ��������� ����� ���������� ��������� �� ����(������ � ������� �������)(� 1)
// ��� ������ 0.
ACT3DMATERIALMODE * Take3DMaterial(long number);     

// �������� ��������� ��������� �� ���� ���������� � �����
// ��� ������ 0, ����� ��� ������ ���������
long Replace3DMaterial(long libcode,long key,ACT3DMATERIALMODE * material); 

// ������� ��������� ��������� �� ���� ���������� � �����
// ��� ������ 0, ����� ��� ������ ���������
long Delete3DMaterial(long libcode,long key); 

// �������� �������� ��������� �� ���� ���������� � �����
// (�������� ��������� ��� ������ ����������)
// ��� ������ 0
long Replace3DMaterialName(long libcode,long key, char * name);     

// ������� ������ ��������� �� ���� ����������, ���������� ��������� �
// �������� (�������� ��������� ��� ������ ����������)
// ��� ������ 0 ����� ��� ������ ���������
long Create3DMaterial(long libcode,ACT3DMATERIALMODE * material,char * name);


#endif   // HIDERSC3D                         

 /****************************************************************
 *                                                               *
 * ������ � �������� ���������� ������� ����������� �� ��������� *  
 *                                                               *
 ****************************************************************/

 public:

 // ������ ���������� �����������
 // 0 - ��� ������
 int GetGrsItemCount();

 // ������ ����������� �� ����������� ������,���� ��������� � �������� ���������
 // 0 - ��� ������
 IMAGEVALUE * GetGrsItem(unsigned long int index,unsigned long int code,
                         unsigned long  int value);

 // �������� ����� ������ ����������� �� ���� ���������
 // � ������ ������� �����������
 // ���������� ���������� ����� ������
 // 0 - ��� ������
 int AppendGrs(unsigned long int code, unsigned long int image);

 // �������� ����������e �� ����������� ������ ������ � �������� ���������
 // ���������� ���������� ����� ������
 // 0 - ��� ������
 int AppendGrsItem(unsigned long int index,unsigned long  int value,
                   IMAGEVALUE * item);

 // ��������� ����������e �� ����������� ������ ������ � �������� ���������
 // ���������� ��������� �� ���������
 // 0 - ��� ������
 char * GetGrsItemParam(unsigned long int index,unsigned long  int value);

 // ��������� ����� ������� ����������� �� ����������� ������ ������ �
 // �������� ���������
 // 0 - ��� ������
 int GetGrsItemFunction(unsigned long int index,unsigned long  int value);

/*****************************************************************
 *                                                               *
 * ������ � �������� �������� ���������                          *
 *                                                               *
 ****************************************************************/


  // ������� ������������� ������,�������� ������,��������� ���������;
  int OpenTRscBase(const char * name, int mode)
     {
       Mode_RSC = mode;
       return(OpenTRscBase(name));
     }

   //  ������� ������������� ������,��������� � ���������
   int OpenTRscBase(const char * name);

   // C������ �������������,�������� ������,��������� ���������,
   int CreateTRscBase(char * name);

   // ������� �������������
   int CloseRscBase(void);

   //  ������� ������������� � �������� �� ������
   int Exit(int error);

   // ����������/��������� ����� �������
   int AccessMode(int mode);

   int AccessMode() { return Mode_RSC; }

   int AccessShare(int mode) { return (Share_RSC = mode); }
   int AccessShare() { return Share_RSC; }

   // �������� ������� ������ � ���������
   int TurnHeader(RSCHEAD * rsc);

   // �������� ������� ������ � ��������� ��������
   int TurnTable();

   // �������� ������� ������ ������� ������         
   int TurnTableTab(TABTAB * tab);

   // ������ ������ ������ ������
   int IsOldVersion();

   // ������������� �����
   char * DecodeString(char * text,int length);

/*****************************************************************
 *                                                               *
 *              ������ � ������                                  *
 *                                                               *
 ****************************************************************/

 // �������� ������� ������ �������� �����
 // ��� ������ ���������� ����

  char * GetMemoryBlock(long length);

 // ����� �������������� ������
 // ��� ������ ���������� ����
 // length - ������ �������� �������

   long OpenMemory(long length = 32*1024);

 // ����� �������������� ������
 // ��� ������ ���������� ����

  int CloseMemory();

/*****************************************************************
 *                                                               *
 *              ������ � ��������                                *
 *                                                               *
 ****************************************************************/
#ifdef LP64MODEL
//��������� ������ ������� ������� Memlist �� buffersize ���������
intptr_t ReallocMemlist(ULONG);
#endif

//�������� ������ � 64-���������� ������ �� 32-���������� �������
intptr_t Off_64(ULONG) const;

//�������� ������ � 64-���������� ������ �� 32-���������� �������
intptr_t Off_64(void *) const;

//�������� 32-��������� ������ ��� 64-���������� ������
ULONG Off_32(intptr_t);
 
//�������� 32-��������� ������ ��� 64-���������� ������
ULONG Off_32(void *);
 /****************************************************************
 *                                                               *
 *            ���������� ���������� ������ TMapRsc               *
 *                                                               *
 ****************************************************************/

 public:

 char RscPath[MAX_PATH];     // ������ ���� ������� � ��������������
 char RscName[MAX_PATH];     // ��� ����� ��������������

 TABRSC *     TabRsc;         // ������� �������� ���������� ��� �������

 TABGRSITEM * TabGrsItem;     // T������ ����������� ���������

 long int     TabRscCount;    // ����� ������� � ������� �������� ����������

 long int     TabGrsCount;    // ����� ������� � ������� ����������� ���������

 long int     ModifyFlag;     // ���� ��������� RSC

 long int     LastError;      // ��� ������ ��������� ��������

 long int     APIOpenFlag;    // ������� �������� ����� API
 long int     Mode_RSC;       // ����� ������� � ��������������
 long int     Share_RSC;      // ����� ������� � ��������������
 HANDLE       File_RSC;       // ������������� �����
 char         SeekFont[256];  // ������� ������������ ����� ������ � ������
                              // � ����� �������
 long int     Is3DWork;       // 1 - ������� ������ � 3D �������������
 RSCRECORD  * TabRecord;      // ������� ������� � P3D - ������
 long int     RealRecCount;   // ���������� ������� ��������� � ������� �������
 long int     RecordCount;    // ����� ���������� ��������� � ������� �������

 char *  DanRsc;              // ������ ������� ������ ��������������

 RSCHEAD  Rsc;                // ��������� ����� �������� (��������������)

 MEMHEAD * Memory;            // ��������� �������� �������

 int  Freeobject;             // ���������� ��������� ��������
 int  Freesemantic;           // ���������� ��������� ��������
 int  Freesegment;            // ���������� ��������� ���������
 int  Freeiml;                // ���������� ��������� ���������
 int  Freetxt;                // ���������� ��������� �������
 int  Freefrm;                // ���������� ��������� �������
 int  Freegrs;                // ���������� ��������� ������� ���������

#ifdef LP64MODEL
intptr_t * Memlist;           //������ �������
unsigned int MemLength;       //������ ������� �������
unsigned int MemCounter;      //������� �������� ��������
#endif

}
TMapRsc;

typedef TMapRsc TRSCDATA;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++   ���������� ���������� �������, ������ � ��������  ++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ������ ����� ������ ��������������
int _fastcall rscGetRscDescribe(TRSCDATA * data,RSCCREATE * rsccreate,
                                PALETTE256 * palette);
// ���������� �������� �� ������� �����
int _fastcall rscIsActive(TRSCDATA * data);

// ������ ������ �������  �� �� ������
COLORREF * _fastcall rscGetPalette(TRSCDATA * data,int number);

// ������ �������������� �������� �������  �� ����������� ������ (� 1)
TABPAL * _fastcall rscGetTabPal(TRSCDATA * data,int number);

// ���������/�������  �������� �����
long _fastcall rscGetScale(TRSCDATA * data);
long _fastcall rscScale(TRSCDATA * data,long scale);

// ������ ���� �������� �����
char * _fastcall rscDate(TRSCDATA * data);

// ���������/�������  ���� ��������������
char * _fastcall rscType(TRSCDATA * data);
char * _fastcall rscSetType(TRSCDATA * data,char *str);

// ���������/�������  ����� ��������������
char * _fastcall rscName(TRSCDATA * data);
char * _fastcall rscSetName(TRSCDATA * data,char *str);

// ��������� ������ (� �����) ��� ����� ��������������
int  _fastcall rscGetRscName(TRSCDATA * data,char * name, int size);

// ������ ���������� ��������
int  _fastcall rscGetObjCount(TRSCDATA * data);

// ������ �������� ���� ���������� ������� �� �����������
long _fastcall rscGetServObjExcode(TRSCDATA * data,int local);

// ������ ����������� ���� ���������� ������� �� �����������
int _fastcall rscGetServObjIncode(TRSCDATA * data,int local);

// ������ ����������� ���� ������� �� �������� ���� � �����������
// ��� ������ ���������� 0
int _fastcall rscGetObjIncode(TRSCDATA * data,long excode,int local);

//  ������ ����������� ���� ������� �� �������� ����,�����������
//  � ����������
//  ��� ������ ���������� 0
int _fastcall rscGetObjExtendIncode(TRSCDATA * data,long excode,int local,
                                    int extend);

// ���������������� ������ ����������� ���� ������� �� ��������
// ���� � ����������� ���� ����������� ������� (��� ����������
// ����������� ���� - ����� � ������� �������
int  _fastcall rscGetNextObjIncode(TRSCDATA * data,long excode,int incode);

// ������ ����� ������� �� ����������� ����
const char * _fastcall rscGetObjName(TRSCDATA * data,int incode);

// ������ ����� ������� �� ����������� ����
const char * _fastcall rscGetObjKey(TRSCDATA * data,int incode);

// ������ ������������� ������� �� ����������� ����
long _fastcall rscGetObjIdent(TRSCDATA * data,int incode);          

// ������ ����������� ���� ������� �� �������������                        
long _fastcall rscGetObjIdentIncode(TRSCDATA * data,int ident);

// ������ ����������� ���� ������� �� �����             
long _fastcall rscGetObjKeyIncode(TRSCDATA * data,const char * key);

// ������ ����� ����� �������
int _fastcall rscGetObjNameSize();

// ������ ������ ������� ��������� �� ����������� ����
int _fastcall rscGetObjBot(TRSCDATA * data,int incode);

// ������ �����e� ������� ��������� �� ����������� ����
int _fastcall rscGetObjTop(TRSCDATA * data,int incode);

// ������ ���������������� ������� �� ����������� ����
int _fastcall rscGetObjScale(TRSCDATA * data,int incode);

// ������ ����������� ������� �� ����������� ����
int _fastcall rscGetObjPress(TRSCDATA * data,int incode);

// �������� ����������� ������� �� ����������� ���� (0/1)           
// 0 - �������, 1 - �� �������
int _fastcall rscSetObjPress(TRSCDATA * data, int incode,int press);

//----------------------------------------------------------------------------------------- 
 // ������ ������� ���������������� ������� �� ����������� ����     
int _fastcall rscGetObjScaleLimit(TRSCDATA * data,int incode);

// ������ ������� ����������� ������� �� ����������� ����
int _fastcall rscGetObjPressLimit(TRSCDATA * data,int incode);

// �������� ������ ���������������� ������� �� ����������� ����  
int _fastcall rscSetObjScaleLimit(TRSCDATA * data,int incode,int scalelimit);

// �������� ������ ����������� ������� �� ����������� ����
int _fastcall rscSetObjPressLimit(TRSCDATA * data,int incode,int presslimit);
//------------------------------------------------------------------------------------------- 

// ������ ����������� ���������� ������� �� ����������� ����
int _fastcall rscGetObjDirect(TRSCDATA * data,int incode);

// ������ ���������� ��������� �������� �� ����������� ���� �������
int _fastcall rscGetObjOnlyPosSemCount(TRSCDATA * data,int incode);

// ������ ���������� ��������� �������� �� ����������� ���� �������
// c ������ ��������� ��� ���� � ����� ��������                     
int _fastcall rscGetObjPosSemCount(TRSCDATA * data,int incode);

// ������ ���������� ������������ �������� �� ����������� ���� �������
int _fastcall rscGetObjMustSemCount(TRSCDATA * data,int incode);

// ������ ���� ��������� ��������� �� ����������� ���� ������� �
// ����������� ������ � ��������� ���������� (c 1)
int _fastcall rscGetObjOnlyPosSem(TRSCDATA * data,int incode,int number);

// ������ ���� ��������� ��������� �� ����������� ���� ������� �
// ����������� ������ � ��������� ���������� (c 1)
// c ������ ��������� ��� ���� � ����� ��������                     
int _fastcall rscGetObjPosSem(TRSCDATA * data,int incode,int number);

// ������ ���� ��������� �� ����������� ���� ������� �
// ����������� ������(c 1) � ������ ���������� ������������
// ��������� ��� ���� � ����� ��������� ���� � �����         
int _fastcall rscGetObjOrderSem(TRSCDATA * data,int incode,int number);

// �������� ������� �������� ��� ������� � ������������ � ������� �������
// count - ������ ������� �������� �������
// semantics - ��������� �� ������������� ������ �������� �������.
// order     - ��������� �� �������� ������ ���������� �������
// ��������� ������� �� �������� ������� (� ��� ����� � �����) - ������������,
// ���� ����� - �� ��������� ��������� ������� � ����� ������
// ��� ���������� ���������� ���������� ���������� �������� �������
int  _fastcall  rscSetObjSemanticOrder(TRSCDATA * data,int objincode,
                                       int count,long * semantics);

// ��������������� ������ �������� ��� ������� � ������������ �
// ����������� ��������
// count - ������ ������� �������� ������� ��� ����������
// semantics - ��������� �� ������ ������� ��������� �������� �������.
// order     - ��������� �� �������� ������ �������� ����������������
// ����������� �������� ������� ��������(� 1 )
// ��� ���������� ���������� ���������� 1

int  _fastcall  rscSortObjSemantic(TRSCDATA * data,int objincode,
                                     int count,long * semantics,long * orders);

// ������ ������� ������ ���� ��������� �� ����������� ���� �������
// � ������ ���������� ������������
// 0 - ��������� �� ����������� ������� ���� �����           
int _fastcall rscGetObjSemOrderNumber(TRSCDATA * data,int incode,int semcode);

// ������ ��������� ������� �����������?
// 0 - ���, 1- ��                                           
int rscIsObjSemOrdered(TRSCDATA * data,int incode);

// ������ ���� ������������ ��������� �� ����������� ���� ������� �
// ����������� ������ � ��������� ���������� (c 1)
int _fastcall rscGetObjMustSem(TRSCDATA * data,int incode,int number);

// ������ ���������� ��������� �������� �� ����������� ���� �������
int _fastcall rscGetObjLimSemCount(TRSCDATA * data,int incode);

// ������ ���� ��������� ��������� �� ����������� ���� ������� �
// ����������� ������ � ��������� ���������� (c 1)
int _fastcall rscGetObjLimSem(TRSCDATA * data,int incode,int number);

// ������ �������������� �������� ��������� �� ����
TABSEM * _fastcall rscGetTabSem(TRSCDATA * data,int code);

//  ������ ���������� ��������
int _fastcall rscGetSemCount(TRSCDATA * data);

// ������ ����� ��������� �� ����
const char * _fastcall rscGetSemName(TRSCDATA * data,int code);

// ������ ����� ����� ���������
int _fastcall rscGetSemNameSize();

// ������ ��������� ����� ��������� �� ����
const char * _fastcall rscGetSemShortName(TRSCDATA * data,int code);

// ������ ����� ����� ���� �������� ���������
int _fastcall rscGetSemValuePoleSize(TRSCDATA * data,int code);

// ������ �������� �������� ���������
int _fastcall rscGetSemValuePoleDecimal(TRSCDATA * data,int code);

// ������ ��������� ����� �������� �� ����������� ���� ��������
const char * _fastcall rscGetSegShortName(TRSCDATA * data,int number);

// ������ ���������� ���������
int _fastcall rscGetSegCount(TRSCDATA * data);

// ������ ����� �������� �� ����������� ���� ��������
char * _fastcall rscGetSegName(TRSCDATA * data,int number);

// ��������� ��������� �������� �����
// RSCSEGMENT -  ��������� ������� ������  (��. maptype.h)
// incode - ���������� ����� ����
// ��� ������ ���������� ���� ( ��� ������ �� ����� 0 )
// ����� ���������� ����� ����
int _fastcall rscGetSegment(TRSCDATA * data,int incode, RSCSEGMENT *segment);

// ������ ������� ������ �������� �� ����� �� ����������� ������
int _fastcall rscGetSegOrder(TRSCDATA * data,int number);

// ��������� ����� �������� �� ����������� ������ ��������
int _fastcall rscSetSegName(TRSCDATA * data,int number,char * name);

// ��������� ������� ������ �������� �� ����������� ������ ��������
int _fastcall rscSetSegOrder(TRSCDATA * data,int incode,char order);

// ������ ����� ����� ��������
int _fastcall rscGetSegNameSize();

// ������ �������������� �������� �������� �� ����������� ���� ��������
TABSEG * _fastcall rscGetTabSeg(TRSCDATA * data,int incode);

// �������� ������ �� ��������
// size - ������ ������
// ������� ��������� � �������� �������.
// ��� ������ ���������� 0
int _fastcall rscClearofBlank(char * name,int size);

// ������ ����������� ���� �������� �� �����
// ��� ���������� �������� ������� - 0 , ��� ������ IDS_NOTFIND
int _fastcall rscGetSegmentByName(TRSCDATA * data,char * name);

// ������ ����������� ������ �������� �� ����� (���������� ����� � 0)
// Type - ��� ������� : ��� ���� �� ����� - 1,
//                      ��� ���� �� ��������� ����� - 2,
//                      ��� ��������� �� ����� - 3,
//                      ��� ��������� �� ��������� ����� - 4,
//                      ��� ������� �� �����   - 5
// ��� ���������� - 0 , ��� ������ IDS_NOTFIND
int _fastcall rscGetElementbyName(TRSCDATA * data,const char * name,int type);

// ������ ���� ��������� �� ����������� ������
// ������������� �������������� (� 1 )
int _fastcall rscGetSemOrderExcode(TRSCDATA * data,int number);

// ���������� ������� �� ���������  number - ����� ������� (c 1)
COLORREF * _fastcall rscSetDefaultPalette(TRSCDATA * data,int number);

// ������ �������� ������������� ����� �� ������� � �������
COLORREF _fastcall rscGetDefaultColor(TRSCDATA * data,int index);

// ������ �������� ����� �� ������� � ������ �������
COLORREF _fastcall rscGetRscColor(TRSCDATA * data,int index);

// ������ ���������� ������ � ������� ��������������
int _fastcall rscGetRscColorCount(TRSCDATA * data);

// ���������� ���������� ������, ����������� � ��������������
int _fastcall rscSetRscColorCount(TRSCDATA * data,int number);

// ������ ������ ����� � ������� index ������ �������
COLORREF * _fastcall rscGetRscPalette(TRSCDATA * data,int index);

// ������ ���������� ������
int _fastcall rscGetPaletteCount(TRSCDATA * data);

// ������ ����� ������� �� �� ������
char * _fastcall rscGetPaletteName(TRSCDATA * data,int number);

// ���������� ���� (� ������ �������)
// ���������� ������ ����
COLORREF  _fastcall rscSetRscColor(TRSCDATA * data,COLORREF color,int index);

// ���������� ��� ������ �������
int _fastcall rscSetRscPalette(TRSCDATA * data,COLORREF * colorref,int number);

// ������������ ������� � ����� �� ������ (� 1)
// ���������� ������� � �������������
// ���������� ����� �������
COLORREF * _fastcall rscResetPalette(TRSCDATA * data,int number);

// ������ ������ ��������� ������� ������������
int _fastcall rscGetLastFunction();

// �������� ����� �������
// palette - ����� �������,count - ���������� ������ � �������
// name    - �������� �������
// ���������� ��������� �� ��������� �������
// 0 - ��� ������
TABPAL * _fastcall rscAppendPalette(TRSCDATA * data,COLORREF * palette,
                                    int count,char *name );

// �������������� ������� �� RGB � CMYK                
// number - ���������� ������
// rgb - ����� �������(COLORREF)
// cmyk - �����, ��� ���������� ������� CMYK (4 ����� �� ����)
int _fastcall rscCreateCMYK(long int count,char * rgb,char * cmyk);

// ��������� ������� CMYK                        
// number - ���������� ������������ ������
// begin  - ������� CMYK ������
// 0 - ��� ������
int _fastcall rscSetCMYKPalette(TRSCDATA * data,long number,long * begin);

// ��������� ������� CMYK                        
// ���������� ����� CMYK �������
// 0 - ��� ������
char * _fastcall rscGetCMYKPalette(TRSCDATA * data);

// �������� ������� ������ �������� �����
char * _fastcall rscGetMemoryBlock(TRSCDATA * data,long length);

//  ����� �������������� ������
long _fastcall rscOpenMemory(TRSCDATA * data,long length);

//  ����� �������������� ������
int _fastcall rscCloseMemory(TRSCDATA * data);

// ������/��������� ������������� �������������� ��������
int _fastcall rscMaxKey(TRSCDATA * data);
int _fastcall rscSetMaxKey(TRSCDATA * data);

// ������/��������� ����������� �����
int  _fastcall rscMode(TRSCDATA * data);
int _fastcall rscSetMode(TRSCDATA * data,int mode);

// ������ ����������� �������                               
int _fastcall rscColorStyle(TRSCDATA * data);

// ������/��������� cod� �������������� ��������
char * _fastcall rscClassificatorCode(TRSCDATA * data);
int _fastcall rscSetClassificatorCode(TRSCDATA * data,char * code);

// ������/��������� ����� ��������������
int _fastcall rscGetClassificatorLanguage(TRSCDATA * data);
int _fastcall rscSetClassificatorLanguage(TRSCDATA * data,int language);

// ������/��������� ������ ������� ���������
int _fastcall rscScaleTableNumber(TRSCDATA * data);
int _fastcall rscSetScaleTableNumber(TRSCDATA * data,int scaletable);

// ������ ���� �������� ��������� �� ����
int _fastcall rscGetSemType(TRSCDATA * data,int code);

// ������ �������� ��������� ��������� �� ����
// ��������� �������� 0 - 1
int _fastcall rscGetSemService(TRSCDATA * data,int code);

// ������ ���������� �������� �������������� ��  ����
// ������������� ��������������
int _fastcall rscGetClassificatorCount(TRSCDATA * data,int incode);

// ������ �������������� �������� �������������� ��  ����
// ������������� �������������� � ����������� ������ (� 1)
TABCLS * _fastcall rscGetTabCls(TRSCDATA * data,int incode,int number);

// ������ ��������� �������� �������������� ��  ����
// ������������� �������������� � ����������� ������ (� 1)
int _fastcall rscGetClassificatorValue(TRSCDATA * data,int incode,int number);

// ������ "�����" �������� �������������� ��  ����
// ������������� �������������� � ����������� ������ (� 1)
const char * _fastcall rscGetClassificatorName(TRSCDATA * data,int incode,
                                               int number);

//  ������ "�����" �������� �� ���� ��������� �
//  ���� ��������
const char * _fastcall rscGetSemValueName(TRSCDATA * data,int code,int value);

//  ������ ������������ ����� "�����" ��������
int _fastcall rscGetSemValueSize();

//  ������ ������������ ������� ��������� ���������
//  ���� ��� ������� ��������� - ���������� ���������
//  �� ������ ������
//  ��� ������ ���������� ������ ������
const char * _fastcall rscGetSemUnit(TRSCDATA * data,int code);

//  ������ ������������ ����� ������������ ������� ���������
int _fastcall rscGetSemUnitSize();

// ������ ������������� �������� ��������� �� ����
int _fastcall rscGetSemReply(TRSCDATA * data,int code);

// �������� ������������� � �������� ��� �������������
// ����� ����� ������� 1
// ��������� ����������� ������ - ������� 0
int _fastcall rscCheckFrameCode(TRSCDATA * data);

// ������ ����������� ���� ����� �����
// ��������� ����������� ������ - ������� 0
int _fastcall  rscGetFrameCode();

// ������ �������� ���� ����� �����
long _fastcall rscGetFrameCodeEx(TRSCDATA * data);

// ������ ����� ���������� ������������ �� ����������� ���� �������
long _fastcall rscGetParLength(TRSCDATA * data,int incode);

// ���������� ����� ������ ������� ���������� �� ����������� ����,
// ������ �������,����� � ����������
// ���� ������� 0 - ������
VIEPAR * _fastcall rscSetTabPar(TRSCDATA * data,int incode,int length,
                                int number,char * param);

// ���������� ����� ������ ������� ���������� �� ����������� ����
// � ����������
// ���� ������� 0 - ������
VIEPAR  * _fastcall rscSetTabParHead(TRSCDATA * data,int incode,VIEPAR  * apar);

// ���������� ����� ������ ������� ���������� ���������� �� �����������
// ����, ������ �������,����� � ����������
// ���� ������� 0 - ������
VIEPAR * _fastcall rscSetTabPrn(TRSCDATA * data,int incode,int length,
                                int number,char * param);

// ���������� ����� ������ ������� ���������� ���������� �� �������-
// ���� ���� � ����������
// ���� ������� 0 - ������
VIEPAR  * _fastcall rscSetTabPrnHead(TRSCDATA * data,int incode,VIEPAR  * apar);

// �������� ���������� ��������� �������
// �� ����������� ����
void _fastcall rscDeleteTabPrn(TRSCDATA * data,int incode);

// ������ - ����� �� ������������� RSC ?
int _fastcall rscIsWrite(TRSCDATA * data);

// ������� ������ - ���������� ���������� ��� ���������� �������
// ���� ������ ������ � ����� - �������� �� ��������
int _fastcall rscDeleteObject(TRSCDATA * data,int incode);

// ������� ����� ������ - ���������� ���������� ��� �������
// ���� check == 0 ��� �������� �� �������������� �������
int  _fastcall rscAppendObject(TRSCDATA * data,RSCOBJ * robj,int check);

// ������� ������� ��� ������������ ������� �� �����������
int  _fastcall rscCreateDefaultView(TRSCDATA * data,int incode);

// �������� ������� ��� ������� �� ����������� ����
// �������� �� ������� ����� �� ��������
long _fastcall  rscSetObjExcode(TRSCDATA * data,int incode,long excode);

// ������� ��������� �� ������ �� ����� ����������
// ���������� ��� ������� (������ - 0 )
int _fastcall rscDeleteDefObject(TRSCDATA * data,int incode);

// ������� ��������� �� ��������� - ����� (objincode = 0)
// ��� �� ������
// ���������� ��������� �� ������������ ��������� (������ - 0 )
TABSEM * _fastcall rscDeleteDef(TRSCDATA * data,int objincode,int semcode);

// ������� ����� - ������� ������� ������� � ��� �������
// �������� � �����,�������� ������ �� ��������� ���������,
// ������ ���������
int  _fastcall rscDeleteSeria(TRSCDATA * data,long excode,int local);

// ����������� ������ �� ��������� �� ����������� ����
// ����� (������� ��� ����������)
// ���� �� ��������� ����� ��� ������ �� ����� - ����������� ��
// ��������
// ���� ������ - �������� ������, ����������� �� ��������
// ���������� ���������� ��� ������ �������
int _fastcall rscCopyObjectIncode(TRSCDATA * data,int newincode,int oldincode);

// �������������� ������� ��� �������
// ���������� ����� ������� ��� ���������
// �������� �� ������� ����� �� ��������
long _fastcall rscUpdateObjExcode(TRSCDATA * data,int incode,long newexcode);

// �������������� ����������� �������
// ���������� ����� ������� ��� ���������
// �������� �� ������� ����� �� ��������
long _fastcall rscUpdateObjLocal(TRSCDATA * data,int incode,int newlocal);

// �������� ����������� ����������� ������� �� ����������� ����
// (����������� ����������� ������� ��������� �������� 0 ��� 1)
// ��������� �� "����������� �������" (1 - ����������� �� 2 ������)
int _fastcall rscSetObjExtloc(TRSCDATA * data,int incode,int exl);

// �������� ���� ������� �� ����������� ����
char * _fastcall rscSetObjKey(TRSCDATA * data,int incode,char * key);

// �������� ����������� ���������� �������
int _fastcall rscSetObjDirect(TRSCDATA * data,int incode,int direct);

// ��������� ��� ������� �������������� ��������� ���� + ��������-
// ���. ��� ���������� ���������� 0
int _fastcall rscCheckObjectCode(TRSCDATA * data,unsigned long code,int local);

// ������ ����� ��������� �� ����������� ������
// ������������� �������������� ( � 1 )
const char * _fastcall rscGetSemOrderName(TRSCDATA * data,int number);

// �������� ����� ���� - ���������� ���������� N ���� � 0
int  _fastcall rscAppendSeg(TRSCDATA * data,RSCSEG * rseg);
int _fastcall rscAppendSegment(TRSCDATA * data,RSCSEGMENT * segment);

// �������� ��������� ��������
int  _fastcall rscCreateServObjects(TRSCDATA * data);

// ������ �������� �� ������� ��������� � ������
TABSEM *  _fastcall rscGetOffSem(TRSCDATA * data);

// ��������� ������� ������ � ������� ���������� �������� ���������
// �� ����������� ���� ������� � ���� ���������,
// ���� �� ����� ���������� 0
TABDEF *  _fastcall rscCheckTabDef(TRSCDATA * data,int incodeobject,int semcode);

// ��������� �������,��������� � �������� �������� ���������
// �� ����������� ���� ������� � ���� ���������
// ���� �� ����� ���������� 0
int  _fastcall rscGetDefValue(TRSCDATA * data,int incodeobject, int semcode,
                              RSCDEF * valdef);

// ������ �������� ��������� �� ���������
// �� ����������� ���� ������� � ����������� ���� ���������
// �������� ������������� � ���������� ������
// ���� �� ������ ���� ������ - ���������� ������������ �����-
// ��� ���������,���� ��� ������������� ����������� ���� �������
// ����� - ������ ��������������� ����������� ���� �������
// ���������� 1,��� ������ 0
int _fastcall rscGetDefValueSemantic(TRSCDATA * data,int objincode,
                                int semanticcode,char * strdef,int lenstrdef);

// ������ �������� �� ������ � ������� �������
long  _fastcall rscGetScaleItem(TRSCDATA * data,int number);

// ������ �������� �� ������ � ��������� ������� ���������(0,1)
long  _fastcall rscGetTableScaleItem(TRSCDATA * data, int tablenumber, int number);

// ��������� ������ ����� ��������������
// ��� ������ ���������� 0
long int _fastcall rscFileSize(TRSCDATA * data);

// ���������/������� ����� �������� ����� ����� API
int _fastcall rscApiOpenFlag(TRSCDATA * data);
int _fastcall rscSetApiOpenFlag(TRSCDATA * data,int flag);

// ������ ���������� �������� �������� �� ����������� ���� ��������
int _fastcall rscGetSegmentObjectCount(TRSCDATA * data,int incode);

// ������ ���������� �� ��������� �������� �������� �� ����������� ���� ��������
int _fastcall rscGetSegmentObjectRealCount(TRSCDATA * data,int incode);

// ������� ������� �� ����������� ����  ��������
// ��������� ���� �� ���������
int _fastcall rscDeleteSegment(TRSCDATA * data,int incode);

// ��������� ������� �� ������ ���� � ������
// �� ���������� ���� � � ��������� ���� - ������� �� �����������
// ���������� ����� ����� ����, ���� 0 - ������
int _fastcall rscMoveSegmentObjects(TRSCDATA * data,int oldcode,int newcode);

// ������ ���������� �������� � ������ ������� ����� � ������������
// ��� ������ ��� ���������� ���������� 0
int _fastcall rscGetObjNumber(TRSCDATA * data,long excode,int local);

// ������ ������������� ��������� � �������� ��������������
int _fastcall rscGetSemInfo(TRSCDATA * data,int code,
                            APPLYSEMANTIC * applysemantic);

// ������ ���������� �������� � ������ ������������ � ������ ����
int _fastcall rscGetSegmentObjNumber(TRSCDATA * data,int segment,int local);

// ��������� �������� �������  �� ����������� ����
// ���� ��� = 0 - ���������� �� ���������
int _fastcall rscGetDescribeObj(TRSCDATA * data,int incode,RSCOBJECT * object);

// ������ ������� ����������� ��������
// �� ����� ���������� ���
// TABLETEMPLATE (���������� � Mapgdi.h)
// ��� ������ ������� 0
int _fastcall rscGetTemplateTable(TRSCDATA * data,int incode,
                                  TABLETEMPLATE * table);

// ������ ����� ���������� ������ �� ����������� ���� �������
long _fastcall rscGetPrnLength(TRSCDATA * data,int incode);

// ������ �������� ���� ������� �� ����������� ����
long _fastcall rscGetObjExcode(TRSCDATA * data,int incode);

// ������ �������� ������� �� ����������� ����
int _fastcall rscGetObjSegment(TRSCDATA * data,int incode);

// ������ ����������� ������� �� ����������� ����
int _fastcall rscGetObjLocal(TRSCDATA * data,int incode);

// ������ ������� ����������� ������� �� ����������� ����
// ������������ �������� �� ������ ��������� ��������
// ������� GetLastFunction()
int _fastcall rscGetObjFunction(TRSCDATA * data,int incode);

// ������ ������ ������ ���������� ������������ �� ����������� ���� �������
char  * _fastcall rscGetPar(TRSCDATA * data,int incode);

// ������ ������ ������ ������� ���������� �� ����������� ���� �������
VIEPAR * _fastcall rscGetTabPar(TRSCDATA * data,int incode);

// ������ ������ ������ ������� ���������� ������
// �� ����������� ���� �������
VIEPAR  * _fastcall rscGetTabPrn(TRSCDATA * data,int incode);

// ������ ������ ������ ���������� ������ �� ����������� ���� �������
char  * _fastcall rscGetPrn(TRSCDATA * data,int incode);

// ������ ����������� ����������� ������� �� ����������� ����
int _fastcall rscGetObjExtloc(TRSCDATA * data,int incode);

// ������ �������� ���������� ��������� ��� ����������� �������
int _fastcall rscGetObjExtsem(TRSCDATA * data,int incode);
// ��������� �������� ���������� ��������� ��� ����������� �������
int _fastcall rscSetObjExtsem(TRSCDATA * data,int incode, int flag );

//  ������ �������������� �������� ��������� �������� �� �����������
//  ���� �������
TABPOS * _fastcall rscGetTabPos(TRSCDATA * data,int incode);

//  ������ �������������� �������� ������� �� ����������� ���� �������
TABLIM * _fastcall rscGetTabLim(TRSCDATA * data,int incode);

// ������ ���������� ������� �� ����������� ����
int  _fastcall rscGetObjExtend(TRSCDATA * data,int incode);

// �������� ������� ������� �� ����������� ����
int  _fastcall rscSetObjSegment(TRSCDATA * data,int incode,int segment);

// ������ � ������ �������� �����
int _fastcall rscSave(TRSCDATA * data,int mode);
int _fastcall rscGethRsc(TRSCDATA * data);

//  ������������ ����� RSC
int _fastcall rscBackCopy(TRSCDATA * data,int restore);

//  ������� ������������� � �������� �� ������
int _fastcall  rscExit(TRSCDATA * data,int error);

//  ������� �������������
int _fastcall  rscCloseRscBase(TRSCDATA * data);

//  ������� ������� ������ ��� ��������
void _fastcall rscCloseRsc(TRSCDATA * data);

// ���������� ������� �������
// 0 - ��� ������
int _fastcall rscFreeFontTable(TRSCDATA * data);

//  ������� ������������� ������,��������� � ���������
int _fastcall rscOpenTRscBase(TRSCDATA * data,const char * name);

//  ������� �������������
int  _fastcall rscCreateTRscBase(TRSCDATA * data,const char * name);

//  ������� �������������
//  ��� ������ ���������� ����
int _fastcall rscOpenRsc(TRSCDATA * data,const char * rsc, int mode);

//  ������ ������ � ���������� ������ ��� ������ � ���������
int /*_fastcall*/ rscOpenTableRsc(TRSCDATA * data);

//  �������� ������ ��������������
int _fastcall  rscCreateRsc(TRSCDATA * data,char * name, RSCCREATE * rsccreate,
                            PALETTE256 * palette,int createsem);

// ����������/��������� ����� �������
int _fastcall rscSetAccessMode(TRSCDATA * data,int mode);
int _fastcall rscAccessMode(TRSCDATA * data);
int _fastcall rscSetAccessShare(TRSCDATA * data,int mode);
int _fastcall rscAccessShare(TRSCDATA * data);

// ������������� �����
char *  _fastcall rscDecodeString(TRSCDATA * data,char * text,int length);

// ���������� ������� �������
// 0 - ��� ������
int _fastcall rscFillFontTable(TRSCDATA * data);


// �������� ��������� ������� ( ���������� ������ �� ������� �������)
// ��� "�������" �������
void  _fastcall rscSetTextReferParam(TRSCDATA * data,int key, int newkey,
                                      int func, char * objparam);

// �������� ��������� ������� ( ���������� ������ �� ������� �������)
// ��� ���������� key = 0,newkey = 0.
// ��� �������� ������ � ����� key - �������� ��� ������  ��  �����
// c ����� newkey, ����  newkey = 0, �������� �� 1 �����.
// 0 - ��� ������
void  _fastcall rscSetTextRefer(TRSCDATA * data,int key,int newkey);     

// �������� ����� ����� - ����������
// ��� ������
// ��� ������ 0
int _fastcall rscAppendFont(TRSCDATA * data,RSCFONT * font);

// �������� ��������� ���������
// ��� ������ ���������� 0
unsigned long _fastcall rscAppendSystemSemantic(TRSCDATA * data);

// �������� ����������� ���������
// ��� ������ ���������� 0
unsigned long _fastcall rscAppendStandardSemantic(TRSCDATA * data);

// �������� ����� ��������� - ����������
// ��������� �� ��������� ���������
TABSEM * _fastcall rscAppendSemantic(TRSCDATA * data,RSCSEM * rsem);

// ��������� ��� ��������� �������������� ����
// ��� ���������� ���������� 0
int _fastcall rscCheckSemanticCode(TRSCDATA * data,int code);

// ��������� ��������� ����� ���������� �� �������� ���� ���������
int _fastcall rscSetSemShortName(TRSCDATA * data,int code,char * shortname);

// �������� ��������� ��������� �������
// ���� ������ �� �� �����
// ���������� �� ���������������� �����
// � ��������� ���������� (������� � 1),0 - ������
int  _fastcall rscAppendPosSemantic(TRSCDATA * data,int objincode,
                                    int semincode,int seria);

// ������� �������� ��������� �������� �� ����������� ���� �������
// ���� ����� ���� - ������������ ��������� �� ������������ �������
TABPOS * _fastcall rscAppendPos(TRSCDATA * data,int incode,int seria);

// �������� ������� ������ � ���������
int _fastcall rscTurnHeader(TRSCDATA * data,RSCHEAD * rsc);

// �������� ������� ������ � ��������� ��������
int _fastcall rscTurnTable(TRSCDATA * data);

// �������� ������� ������ � ������� ������
int _fastcall rscTurnTableTab(TRSCDATA * data,TABTAB * tab);

// �������� ������� ������ � ���������� �������
// number - ����� ������� �����������
// param  - ����� ���������� �����������
// ���������� ��������� �� ����� ����������
char * _fastcall rscTurnParam(int number,char *param);

// �������� ������� ������ � ���������� �������(�� LINUX � WINDOW)
// number - ����� ������� �����������
// param  - ����� ���������� �����������
// ���������� ��������� �� ����� ����������
char * _fastcall rscTurnParamBack(int number,char *param);    

// ������ � ������ �������� �����
int _fastcall rscCommit(TRSCDATA * data);

// ������������ ������������� � �����
int _fastcall rscRevert(TRSCDATA * data);


// ��������� ������� ����������� �������� ��������� ���������� ������� 
// param  - ��������� �����������
// number - ����� �������� (� 1)
// ��� ������ ���������� 0
long _fastcall rscGetVectorElementIdent(IMGVECTOREX * vector, long number);

// ��������� ��������� ����������� �������� ��������� ���������� ������� 
// param  - ��������� �����������
// number - ����� �������� (� 1)
// ��� ������ ���������� 0
char * _fastcall rscGetVectorElementParam(IMGVECTOREX * vector, long number);

// ��������� ������� ���������� �������
// semantic - ��������� �� ��������� �������, ���� ������� ������� �� ���������
// ��� ������ ���������� ����
int _fastcall rscGetVectorSize(IMGVECTOREX * vector,IMAGESIZE* imagesize,
                                char * semantic, TRSCDATA * rsc);   

// ���������� ������������ ����� ������� �������������� �
// ������ � �� �����
// 1  - ������ ���������
// 0  - ������
// -1 - ��������
int _fastcall rscAdjustData(TRSCDATA * data);

// ������ � �������� ����������� �������
// ��� ������ ������� 0
// ��� ������� � ��������
// ��� ������� � �������� - ������� ����� �����
// ���� ������� 0 - ������ �� ��������������
// (������ string ������ length �������� ���
// ����������� ��������������� ������� �������)
// type = 0 - ������� �������� �����������, 1 - ����������
// ��� ���������� ����������� ���� - ������� 0  (��� ������ IDS_NOTFIND)
int _fastcall rscGetImageSize(TRSCDATA * data,int incode, IMAGESIZE * imagesize,
                              int lengthstr, const char * string,int imagetype);
// ������ � �������� ����������� ������                           
// ��� ������ ������� 0
// ��� ������� � ��������
// (������ string ������ length �������� ���
// ����������� ��������������� ������� �������)
// ��� ������ - ������� ����� �����
int _fastcall rscGetTextSize( IMGTEXT * param, IMAGESIZE * imagesize,
                              const TFontDraw* fontDraw,
                              const char * text, int length);

// ����� "��������" ���� ����������� �������  �� ����������� ���� 
// � ���� �����������  0 - ��������, 1 - ����������
// ��� ���������� ����� ���������� 0xFF000000
// ��� ������ ���������� 0
COLORREF _fastcall rscGetObjectBaseColor(TRSCDATA * data, int incode,
                                          long int viewtype);
// ����� "��������" ���� ����������� ��������� �� ������ ������� � ���������� 
COLORREF _fastcall rscGetBasePrimColor(TRSCDATA * data,int number, char * param);


// ������ ����������� ���� ������� �� �������� ����, �����������
// � ��������� �������
// ��� ������ ���������� 0
int _fastcall rscGetObjIncodeSem(TRSCDATA * data,long excode,int local,
                                        SEMANTICDATA *semnedit);
int _fastcall rscGetObjIncodeSemantic(TRSCDATA * data, long excode,
                                      int local, SEMANTIC * semn);

// ������ ����� ����������� �� ������ �����������
const char * _fastcall rscGetLocalName(TRSCDATA * data,int local,int language);

// ������ ���������� �����������
int _fastcall rscGetLocalCount();

// ������ ����� ����� �����������
int _fastcall rscGetLocalNameSize();

// ��������� ��������� ����� �������� �� ����������� ���� �������� (c 0)
int _fastcall rscSetSegShortName(TRSCDATA * data,int incode,char * shortname);

// ��������� ���������� �������� ��� ���� �� ����������� ������
// ���� � 0
long _fastcall rscGetSegSemCount(TRSCDATA * data,int number);

// ��������� ��� ��������� �� ����������� ������ ���� (c 0) �
// ������ ��������� � ������ (� 1)
long _fastcall rscGetSegSemCode(TRSCDATA * data,int number,int order);

// �������� ��� ��������� � ������ ���� � ���������� �������
// numberseg ( c 0)
// ������� - ���������� ����� ����������� ��������� � ������ (� 1)
long _fastcall rscAppendSegSemCode(TRSCDATA * data,int number,long code);

// ������� ��� ��������� �� ������ ���� � ���������� �������
// numberseg ( c 0)
long _fastcall rscDeleteSegSemCode(TRSCDATA * data,int number,long code);

// ������� ������ �������� ��� ����
// index - ���������� N ����
// type - ��� �������� ��� ����� 0 - ���
//                               1 - ������ ������������
// ���������� ��������� �� ������������ ����
TABSEG * _fastcall rscBuildSegmentSemantic(TRSCDATA * data,int index,int type);

// ������� ����� ������ - ���������� ���������� ��� �������
// ������� ��� ���������� ������� ������������� ���������� ������� (��� ������
// �����������).
// ���� ��������� ���� ��� �������� �������  �� ���������� - ������
// ��������� � ��������� ����
// ���� ����� ������ (������� ��� � �����������) ��� ���������� -
// ������ �� ��������� - ������� 0.
// ��� ������ - ���������� 0, ����� ���������� ��� ���������� �������
int _fastcall rscAppendObjectDefaultView(TRSCDATA * data,RSCOBJECT * robj);

// ����������� ������ �� ����� �����
// (c ������� ����� FIRSTSERVEXCODE)
// ��������� ������ �� ����������
// ���������� ���������� ��� ������ �������
// ��� ����,����� ������ ������ ������� ��� ����������,
// ������������ ������ �������������� ������� ���
int _fastcall rscCopyObject(TRSCDATA * data,int oldincode);

// �������� �������� �������  �� ����������� ����
// ��� ������� ����� ������� ��� � ����������� � ���� - �� ��������
// ���� ������� ��� �� ������������� ������ �������� -
// �������� ������� ��� �� ������������
// ���������� ���������� ��� , ���� 0
int  _fastcall rscUpdateObject(TRSCDATA * data, int incode,RSCOBJECT * object);

// ����� �� ������� ������� �� �������
// number - ����� ������� �����������
// param  - ��������� �����������
// angle  - ���� �������� ������� � �������� (�� ����������� �� �����
// �� ������� �������)
// ��� ������ ������� 0
int _fastcall rscGetImageFrame(TRSCDATA * data,int number, const char * param,
                           double angle,
                           IMAGEFRAME * imageframe);

// ������� ����� �� ���� a ������������ ����� origin  
int _fastcall rscTurnPoint(DOUBLEPOINT * origin, DOUBLEPOINT * point,
                       double sina, double cosa);

// �������� ����������� ������� �� ����������� ����
// (����������� ������� ����� ���� ����� 0)
// ���� ������� ����������� ������������� �������,
// ��� ������� �� ����������.
// �������� �� ������� ����� �� ��������
int _fastcall  rscSetObjLocal(TRSCDATA * data,int incode,int local);

// �������� ������������ ����������� � ��������� �� ����������� �������
// ��� ������ ������� 0
int _fastcall  rscGetImageSuitable(int local,int number);

// ������ ������������� ��������� ��� ������� �� ����������� ���� �������
// � ���� ���������
// c ������ ��������� ��� ���� � ����� ��������                    
int _fastcall rscGetObjCanSem(TRSCDATA * data,int incode,int codesem);

// ������ ������������� ��������� ��� ������� �� ����������� ���� �������
// � ���� ���������
int _fastcall rscGetOnlyObjCanSem(TRSCDATA * data,int incode,int codesem);

// �������� ����� ��������� - ����������  ��� ��������� ���������
// ��� ������ ���������� 0                                       
unsigned long _fastcall rscAppendRscSemantic(TRSCDATA * data,RSCSEMANTICEX * rsem);

// ��������� ������� � �������� �������� ���������
int _fastcall  rscSetSemDecimal(TRSCDATA * data,int code,int size,int decimal);

// �������� ����� "�������" ��������������
// (�������� �������� � ����������) ����������
// ��������� �� ������������ ���������
TABSEM * _fastcall rscAppendCls(TRSCDATA * data,int codesemantic,
                                short int value,char * name);

// ��������� ��� �������������� �������������� �������� ��������
// ��� ���������� ���������� 0
int _fastcall  rscCheckClassificatorCode(TRSCDATA * data,int codesemantic,
                                         int value);

// �������� ���������
// rsem - ����� ���������, c ��������� ��������������,
// code - ��� ��������� ������� ���������,
// ���� ������������� ����������� - classupdate = 1  ��� ����
// ������� ����� ��� ������ ������������� ��������������
// ��� ������ ���������� 0
// ���������� ��� ������������ ���������
// ��� ������ ���������� 0
// ��������� ��������������� ��� ������                   
 int _fastcall  rscUpdateSemantic(TRSCDATA * data,int code,RSCSEMANTICEX * rsem,
                                   int classupdate);

// ������� ���������
// ��������� �������� �� ����������� �� ���������
// ��� �������� ����� ��������� ������������� �������� ���� ������� �����,
// ������������ ������ ���������
int _fastcall  rscDeleteSemantic(TRSCDATA * data,int code);

// �������� ��������� ������� e��� ������ �� �� �����
// t�pe - ��� ��������� (�� maptype.h SEMANTIC_FOR_OBJECT)
// ���������� �� ���������������� �����
// � ���������� ������� ���� (������� � 1)
int _fastcall  rscAppendObjectSemantic(TRSCDATA * data,int objincode,
                                       int semincode,int type,int seria);

// ������� ��������� ���� ������������ ��������� � �������
// ���� ������ �� �� �����
// ��� ���������� ���������� ���������� ���������� ��� �������
int  _fastcall  rscDeletePosSemantic(TRSCDATA * data,int objincode,
                                     int semincode,int seria);

// ��������� ��������� - �������������� � ���������� �� ������.
// ���� ������ �� �� �����
// ���������� ���������������� ����� (� 1) � ��������� ����������
// ���� ����� �� ���� - ���������� 0
int _fastcall  rscSetTypePosSemantic(TRSCDATA * data,int objincode,
                                     int semincode,int seria);

// ��������� ��������� - ������������ � ���������� �� ������.
// ���� ������ �� �� �����
// ���������� ���������������� ����� (� 1) � ������������
// ����������
// ���� ����� �� ���� - ���������� 0
int _fastcall  rscSetTypeMustSemantic(TRSCDATA * data,int objincode,
                                      int semincode,int seria);

//  ��������� ����������� ��������� �������� ������������� �������-
//  ������� �� �������� ���� ��������� � ����������� ���� �������
//  semtype - ����� ���������, � ������� ����� ��������
//  �������� ��������������,
//  code - ��� ���������,
//  objincode - ���������� ��� �������.
//  ��� ������ ���������� ����                     
int _fastcall rscSemanticDescribeEx(TRSCDATA * data,RSCSEMANTICEX *semtypeex,
                                int code, int objincode);

// �������� ����� ��������� �� ��������� (incodeobject=0 )
// ��� �� ������
// ���������� ��������� �� ������������ ���������
TABSEM * _fastcall rscAppendDef(TRSCDATA * data,int incodeobject,
                   int semanticcode,
                   float objmin,float objdef,float objmax);

// �������� ��������� �� ��������� - ����� (objincode = 0)
// ���� �� ������
// ���� ���������� ��������� �� ����� - ������� �����
// ���������� ��������� �� ������������ ��������� (������ - 0 )
TABSEM * _fastcall rscUpdateDef(TRSCDATA * data,int incodeobject,
                  int semanticcode, float objmin,float objdef,float objmax);

// �������� ����� ����������
// name    - �������� �������� ����������
// dllname - �������� DLL
// ���������� ��������� �� ��������� ����������
// 0 - ��� ������
TABIML * _fastcall rscAppendLibrary(TRSCDATA * data,char * dllname,char * name);

// �������� ����� ����������
// name    - �������� �������� ����������
// dllname - �������� DLL
// ���������� ��� ��������� ����������
// 0 - ��� ������
long int _fastcall rscCodeAppendLibrary(TRSCDATA * data,char * dllname,
                                                char * name);    

// ������ ���������� ���������
// 0 - ��� ������
int _fastcall rscGetImlCount(TRSCDATA * data);

// ������ ��������� �������� ���������� �� ����������� ������ (c 1)
// ' ' - ��� ������
char * _fastcall rscGetImlName(TRSCDATA * data,int number);

// ������ ��������� �������� ���������� �� ����������� ������ (c 1)
// ' ' - ��� ������
char * _fastcall rscSetImlName(TRSCDATA * data,int number,char * name);

// ������ ����� ���������� �� ����������� ������ (c 1)
// ' ' - ��� ������
char * _fastcall rscGetImlNameDLL(TRSCDATA * data,int number);

// ������ ������� ����������(� 1) �� ����������� ������    
// 0 - ��� ������
int  _fastcall rscGetImlIndex(TRSCDATA * data,int number);

// ������ ����������� ������ ����������(� 1) �� ����
// 0 - ��� ������
int  _fastcall rscGetImlOrder(TRSCDATA * data,int code);

// ������ ���� �� ����������� ������ ����������(c 1)         
 // 0 - ��� ������
int  _fastcall rscGetImlCode(TRSCDATA * data,int number);

// ��������� �������� �������,
// �������������� ����������� �� �������
IMLLIST * _fastcall rscGetImageList(TRSCDATA * data,int index);

// �������� ��������� ���������������� ��������(IMG_LIBRARY)
void _fastcall rscSetUserObjectRefer(TRSCDATA * data);

// ������� ������� ���������������� ��������(IMG_LIBRARY)
void _fastcall rscBreakUserObjectRefer(TRSCDATA * data);

// ������� ���������� �� ����           
int  _fastcall rscDeleteLibrary(TRSCDATA * data,int code);

// ���p����� ���������� ��������� �������� �������        
int _fastcall rscGetObjectRelateCount(TRSCDATA * data,int incode);

// ���p����� �������� ��������� ������� �� ����������� ���� ������� �  
// �� ����������� ������ ��������� ������� (� 1)
// ���������� ������������� �������
// ��� ������ ���������� 0
int _fastcall rscGetObjectRelateOrder(TRSCDATA * data,int incode,int order,
                                      RSCRELATION * relate);

// ���p����� �������� ��������� ������� �������           
// �� ������ ���������
// ��� ���������� ������� ���������� 0
int _fastcall rscGetObjectRelate(TRSCDATA * data,int incode,int semanticcode,
                                 RSCRELATION * relate);

// �������� �������� ���� �������� �������� ��������� �������  
// ���������� ������������� �������  , ���� 0
int _fastcall rscUpdateObjectRelate(TRSCDATA * data,int incode,int semanticcode,
                                     int ident,char * prefix,int decimal);

// ������� ��������� ������� ������� �� �������������� �������        
// ���������� ���������� ��������� ��������� ��������
int _fastcall rscDeleteObjectRelateIdent(TRSCDATA * data,int incode,int ident);

// ������� ��������� ������� �� ��������� ���������                   
int _fastcall rscDeleteObjectRelate(TRSCDATA * data,int incode,int semanticcode);

// ������� ��� ��������� ������� ����������� �� ������ ������         
// ident - ������������� �������
// ���������� ���������� ��������� ��������� ��������
int _fastcall rscDeleteObjectRelationText(TRSCDATA * data,int ident);

// ����� ��������� ������ ����� ���������� ������� ��������� �������  
// ����������� �� ������ � ������ ���������������
// ���������� ���������� ���������� ��� �������.
// ���� ����� ������ ��� 0
int _fastcall rscCheckRelation(TRSCDATA * data,int ident,int order);

// ���������� ��� ������� �� ������ (� 1)                          
// ���������� ����� ������������ �������
int _fastcall rscSetPaletteName(TRSCDATA * data,int number,char * name);

// ������� ������� �� ������ (c 1)(���� ������� �� ���������)       
int _fastcall rscDeletePalette(TRSCDATA * data,int number);

// ���������� ������� ������� ��������� ��� �������� �� ����������  
// �������� (������� ����� (�������) ��������� ������� � ������� ���������
// ���������� ���������� ������������ ��������
int _fastcall rscSetObjectView(TRSCDATA * data,unsigned long scale);

// �������� ���������� �������� �������������� �� ������ � 1       
// ���������� ����� ��� 0
int _fastcall rscUpdateClassificatorName(TRSCDATA * data,int semanticcode,
                                         int index,char * name);

// ��������� - ������� ���� ����� ��������, ������������ � �������������� 
// type 0 - ��� ��������, 1- � �������� ����, ������� ����(�������� ��� �������)
int _fastcall rscGetRscObjectCodeType(TRSCDATA * data);
int _fastcall rscSetRscObjectCodeType(TRSCDATA * data,int type);

// ������� ����� �� ����� , ���� ����� ������������� ����� �� �������      
// ���� �������� , newkey - ���� ������� ������. ���� newkey = 0,
// ����� �������� ����� �� ���������.
int  _fastcall rscDeleteFont(TRSCDATA * data,int key,int newkey);

// ������� ��� �������������� ��������� �� ���������� �������� ��������
// ���� �� ����� ���������� 0                                             
int _fastcall  rscFindClassificatorCode(TRSCDATA * data,
                               unsigned long codesemantic, const char * string);

// ��������� ������ �� ����                                                
// 0 - ������
// 1 - �������� ���������
int _fastcall rscReadFormula(HRSC hrsc, HOBJ info, const char * formula,
                             long int * err, FORMNODE * node);

// ��������� �������� �� �����
// 0 - ������, 1 - �������� ���������
long CalcFormula(FORMNODE * node,long nodecount,double * value);

// �������� ����� ������� - ���������� ��� �������
// formula - ���������� ������ � ������� �������,
// name    - �������� �������
// type    - 0 (�������� �������)
// errcode - ��� ������ ��� �������� ������� (maperr.rh)
// ��� ������ 0
int _fastcall rscAppendFormula(TRSCDATA * data, const char * formula,
                               const char * name, long type, long * errcode);

// �������� ������� - ���������� ��� �������
// code    - ��� ���������� �������
// formula - ���������� ������ � ������� �������,
// name    - �������� �������
// type    - 0 (�������� �������)
// errcode - ��� ������ ��� �������� ������� (maperr.rh)
// ��� ������ 0
int _fastcall rscUpdateFormula(TRSCDATA * data, long code, const char * formula,
                               const char * name, long type, long * errcode);

// ������ ������� �� ���� ���������
// ���������� ���������� ������ � ������� �������,
// ��� ������ ' '
const char * _fastcall rscGetFormulaBySemanticCode(TRSCDATA * data, long code);

// ������ ������� �� ���� �������
// ���������� ���������� ������ � ������� �������,
// ��� ������ ���������� ' '
const char * _fastcall rscGetFormulaByCode(TRSCDATA * data, long code);

// ������ �������� ������� �� ���� �������
// ���������� ���������� ������ � ������� �������,
// ��� ������ ���������� ' '
const char * _fastcall rscGetFormulaNameByCode(TRSCDATA * data, long code);

// ������ ������� �� ����������� ������ (� 1)
// ���������� ���������� ������ � ������� �������,
// ��� ������ ���������� ' '
const char * _fastcall rscGetFormulaByNumber(TRSCDATA * data, long number);

// ������ ���� ������� �� ����������� ������ (� 1)
// ��� ������ ���������� 0
long _fastcall rscGetFormulaCodeByNumber(TRSCDATA * data, long number);

// ��������� ��������� ������� ��� ��������
// ���������� ��� ������� ��� 0
long _fastcall rscSetFormulaToSemantic(TRSCDATA * data, long code,
                                                      long semanticcode );

// ������� ������� ��� �������� �� ���� �������
// ��� ������ ���������� 0
long _fastcall rscDeleteFormula(TRSCDATA * data, long code);

// ������ ���������� ������
long _fastcall rscGetFormulaCount(TRSCDATA * data);


#ifndef HIDERSC3D                                               
// �������� ������������ ���������� ���������� ����������       
// name    - �������� �������� ����������
// dllname - ��� ����� .p3d
// ���������� ��������� �� c�������� ����������
// 0 - ��� ������
TABL3D * _fastcall rscAppend3DLibrary(TRSCDATA * data,char * dllname,char * name);

// �������� ����� ���������� ���������� ����������
// name    - �������� �������� ����������
// dllname - ��� ����� .p3d
// ���������� ��������� �� c�������� ����������
// 0 - ��� ������
TABL3D * _fastcall rscNew3DLibrary(TRSCDATA * data,char * dllname,
                                  char * name);

// ������ ���������� ��������� ���������� ����������
// 0 - ��� ������
int _fastcall rscGet3DLibraryCount(TRSCDATA * data);

// ������ ����������� ������ ���������� ���������� ���������� (� 1)
// �� ����
// 0 - ��� ������
int  _fastcall rscGet3DLibraryOrder(TRSCDATA * data,int code);

// ������ ���� �� ����������� ������ ���������� 3D ���������� (c 1)
// 0 - ��� ������
int  /*_fastcall */rscGet3DLibraryCode(TRSCDATA * data,int number);

// ������ ���� �� ����� ���������� 3D ����������
// 0 - ��� ������
int  _fastcall rscGet3DLibraryCodeByName(TRSCDATA * data,const char * dllname);

// ������ ���������� ���������� ���������� �� ����
// 0 - ��� ������
TABL3D *  _fastcall rscGet3DLibrary(TRSCDATA * data,int code);

// ������ ����� ���������� ���������� ���������� �� ����
// 0 - ��� ������
char *  _fastcall rscGet3DLibraryName(TRSCDATA * data,int code);

// ������ ����� ����� ���������� ���������� ���������� �� ����
// 0 - ��� ������
char *  _fastcall rscGet3DLibraryFileName(TRSCDATA * data,int code);

// ������ �������� ���������� ���������� ���������� �� ����
// 0 - ��� ������
long _fastcall rscGet3DLibraryOffset(TRSCDATA * data,int code);

// ������� ���������� ���������� ���������� �� ����
int  _fastcall rscDelete3DLibrary(TRSCDATA * data,int code);

// ���������������� 3D �������
// 0 - ��� ������
int _fastcall rscInit3D(TRSCDATA * data);

// �������� � ���������� p3D ������ � ������
// ��������� ������� ������� ������ ����������
// 0 - ��� ������
// 2 - ���� ��� � ������
int _fastcall rscInitp3DFile(TRSCDATA * data,TABL3D * ald);

// ����������� ������ �� ��������� � �������� �������
// 0 - ��� ������
int _fastcall rscAdjustRecordWithParam(TRSCDATA * data);

// ����������� ������ �� �������� ��� ����������
// � ���������� ������� number (� 1) � �������� �������
// 0 - ��� ������
int _fastcall rscAdjustRecordWithTexture(TRSCDATA * data,int number);

// ������ ������� 3D ���������� ������� �� ������ (0,1,2 - ��� 0 - �������)
// � ����������� ������ (������� ) ������� � 1
// ��� ���������� ������� - �������� ��������� � ������� �������
// ��� ������ ��� ���������� 0
TABP3D * /*_fastcall*/ rscGet3DObject(TRSCDATA * data,long incode,long level);

// ������ ������������� 3D ���������� ������� �� ������ (0,1,2 - ��� 0 - �������)
// � ����������� ������ (������� ) ������� � 1
// ��� ������ ��� ���������� 0
long _fastcall rscIs3DParam(TRSCDATA * data,long incode,long level);   

// ������ ����� ���������� ������� �� ������ (0,1,2 - ��� 0 - �������)
// � ����������� ������ (������� ) ������� � 1
// ��� ������ ��� ���������� 0
long _fastcall rscGet3DLength(TRSCDATA * data,long incode,long level);

// ������ ������� ����������� ���������� ������� �� ������ (0,1,2 - ��� 0 - �������)
// � ����������� ������ (������� ) ������� � 1
// ��� ������ ��� ���������� 0
long _fastcall rscGet3DFunction(TRSCDATA * data,long incode,long level);

// ������ ����� ����������� ���������� �������
// �� ������ (0,1,2 - ��� 0 - �������)
// � ����������� ������ (������� ) ������� � 1
// ��� ������ ��� ���������� 0
long _fastcall rscGet3DObjectKey(TRSCDATA * data,long incode,long level);

// ������ ���� ���������� ����������� ���������� �������
// �� ������ (0,1,2 - ��� 0 - �������)
// � ����������� ������ (������� ) ������� � 1
// ��� ������ ��� ���������� 0
long _fastcall rscGet3DObjectLibraryCode(TRSCDATA * data,long incode,long level);

// ������ ������� ����������� ���������� ������� �� ������ (0,1,2 - ��� 0 - �������)
// � ����������� ������ (������� ) ������� � 1
// ��� ������ ��� ���������� 0
F3DTREE * /*_fastcall*/ rscGet3DParam(TRSCDATA * data,long incode,long level);

// ������� ������ �� ������ (0,1,2 - ��� 0 - �������)
// � ����������� ������ (������� ) ������� � 1
// � ������������ �� ���� ���������� � ����� �������
// ��� ������ 0
long /*_fastcall*/ rscSet3DImageToObject(TRSCDATA * data, long incode, long level,
                                     long code, long key);

// ������ ���������� 3D �����������
// � ���� ���������� � ����� �����������
// ��� ������ ��� ���������� 0
// ����� ��������� ���������� ���������� F3DTREE
F3DTREE * /*_fastcall*/ rscGet3DImageParam(TRSCDATA * data,long code,long key);

// ���������� ��������� 3D �����������
// �� ���� ����������,�����,������ �������,���� �������,
// ����� ���������� � ����������
// ��� ������ ��� ���������� 0
long _fastcall rscSet3DImageParam(TRSCDATA * data,long code,long key,
                                  long type,long length,char * param);

// �������� �������� 3D �����������
// �� ���� ����������,�����
// ��� ������ ��� ���������� 0
long _fastcall rscSet3DImageName(TRSCDATA * data,long code,long key,
                                  char * name);

// ������� ��������� 3D �����������
// �� ���� ����������,���� �������,��������� ��������,
// ����� ���������� � ���������� (���� P3DTREE)
// ��� ������ ��� ���������� 0 , ����� ��� �����������
long /*_fastcall*/ rscCreate3DImage(TRSCDATA * data,long code,long type,
                                long length,char * param,char * name);

// ������� ������������ ������                                        
// �� ���� ����������
// ��� ������ ���������� 0, ���� ��� - 1 ����� 2
long rscCreate3DDefaultImage(TRSCDATA * data,long code);

// ��������� ����� ���������� ������� ��������� ���� � ����������
// (OBJECT_PARAMETERS,OBJECT_TEXTURE ...  rscfl3d.h)
// ��� ������ 0.
long _fastcall rscTakeRecordCount(TRSCDATA * data,long code,long type);

// ��������� ��������� ������ ���������� ���� �� ����
// ��� ������ 0.
RECHEAD * _fastcall rscTakeCodeRecordHead(TRSCDATA * data,long code);

// ��������� ��������� ������ �� ���� ���������� � �����            
// ��� ������ ��� ���������� 0
RECHEAD * _fastcall rscTakeKeyRecordHead(TRSCDATA * data,long code,long key);

// ��������� ��������� �� ��������� ������ ���������� ���� �� ����������� ������
// � ���������� c ������ �����
// ( ��� - OBJECT_PARAMETERS,OBJECT_TEXTURE ...  rscfl3d.h)
// ��������� ��� ������, ��� ������ 0.
long _fastcall rscTakeRecordHead(TRSCDATA * data,long number,long code,long type,
                                           RECHEAD * address);

// ��������� ����� ���������� �������
// ��� ������ 0.
long _fastcall rscTakeTextureCount(TRSCDATA * data);

// ��������� ����� �������� �� ����������� ������
// ��� ������ 0.
RECTEXTURE * /*_fastcall*/ rscTakeTexture(TRSCDATA * data,long number);

// ������� ������ ��������
// �� ���� ����������,��������� ��������,
// ��� ������ ��� ���������� 0 , ����� ��� ��������
long /*_fastcall*/ rscCreate3DTexture(TRSCDATA * data,long code,
                                 RECTEXTURE * texture,char * name);
// �������� ������ ��������
// �� ���� ����������,����� ��������,��������� ��������,
// ��� ������ ��� ���������� 0 , ����� ��� ��������
long _fastcall rscReplace3DTexture(TRSCDATA * data,long libcode,long key,
                                   RECTEXTURE * texture,char * name);
                                                                 
// ������� ������ ��������
// �� ���� ����������,����� ��������
// ��� ������ ��� ���������� 0
long _fastcall rscDelete3DTexture(TRSCDATA * data,long libcode,long key);

// ��������� ������������� ��������                              
// �� ���� ����������,����� ��������
// ���������� ���������� ��������, ������������ ������ ��������
// ��� ������ ��� ���������� 0
long _fastcall rscUsed3DTexture(TRSCDATA * data,long libcode,long key);

// ��������� ��������� ���� ������ ����������
// �� ���� ���������� � ���� ������
// ��������� ����, ��� ������ 0.
long _fastcall rscTakeFreeKey(TRSCDATA * data,long code,long type);

// ������ 3D ����������� ������� �� ������ (0,1,2 - ��� 0 - �������)
// � ����������� ������ (������� ) ������� � 1
// ��� ������ 0                                                     

long _fastcall rscDelete3DImageFromObject(TRSCDATA * data, long incode,
                                          long level);

// ��������� ����� ���������� ��������� �� ������ � ������� �������
// ��� ������ 0.
ACT3DMATERIALMODE * _fastcall rscTakeMaterial(TRSCDATA * data,long number);     

// �������� ��������� ��������� �� ���� ���������� � �����
// ��� ������ 0, ����� ��� ��������
long _fastcall rscReplaceMaterial(TRSCDATA * data,long libcode,long key,
                          ACT3DMATERIALMODE * material);           

// ������� ��������� ��������� �� ���� ���������� � �����
// ��� ������ 0, ����� ��� ��������
long _fastcall rscDeleteMaterial(TRSCDATA * data,long libcode,long key); 

// �������� �������� ��������� �� ���� ���������� � �����
// (�������� ��������� ��� ������ ����������)
// ��� ������ 0
long _fastcall rscReplaceMaterialName(TRSCDATA * data,long libcode,long key,
                          char * name);                              

// ������� ������ ��������� �� ���� ����������, ���������� ��������� �
// �������� (�������� ��������� ��� ������ ����������)
// ��� ������ 0 ����� ���� ������
long _fastcall rscCreateMaterial(TRSCDATA * data,long libcode,    
                                    ACT3DMATERIALMODE * material,char * name);

#endif  // HIDERSC3D

#endif

