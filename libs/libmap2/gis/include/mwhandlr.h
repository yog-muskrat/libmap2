
#ifndef MWHANDLR_H
#define MWHANDLR_H

#ifndef MAPAPI_H
  #include "mapapi.h"
#endif

#ifndef SEEKAPI_H
  #include "seekapi.h"
#endif

#ifndef OBJAPI_H
  #include "objapi.h"         
#endif

#ifndef LISTAPI_H
  #include "listapi.h"        
#endif

/* 

#include "compdial.h"*/   

#define DECLSPEC_IMPORT

//===============================================================
// ���� �������� ��� AW_DODIALOG �������� � WPARAM  ���� ��� Kylix     
// � LPARAM �������� ����� ��������� ���������� ��� �������
#define    DT_LOADFROMSXF         1  // ��������� �� SXF � MAP
#define    DT_GETTYPEOBJECTCREATE 2  // ������� ��� ������� ����� �� 
                                     // �������������� ��� ��������
#define    DT_OBJECTINFOBEGIN     3  // ������� ������ ���������� �� ������� �����
#define    DT_SITECREATEFORMAP    4  // ������� ����� ������������ ��� �������� �����
#define    DT_OBJECTINFODESTROY   5  // ������� ������ ���������� �� ������� �����
#define    DT_CLOSEDATAFORMAP     6  // ������� ������ �������� ������ �����
#define    DT_SETVIEWSTAFF        7  // ���������� ������ �����������
#define    DT_SETFINDOBJECTPARAM  8  // ���������� ������ ������
#define    DT_OBJECTINFOCONTINUE  9  // ��������� ������ ���������� �� ������� ����� �� ����� ��������
#define    DT_VIEWDATALIST        10 // ������ ������� ���������
#define    DT_LOADBMP             11 // ������ �������� BMP
#define    DT_OBJECTINFOBYSEEK    12 // ����� ������� �� ������
#define    DT_MEDSEEKOBJECT       13 // ������ �������� �������
#define    DT_PALETTER            14 // ������ ���������� ��������
#define    DT_GETSITENUMBER       15 // ������ ������ ������ �����       
#define    DT_ZONEFORSELECT       16 // ������ ���������� ���� ������ ����������
#define    DT_SETPARMPRINT        17 // ������ ���������� ������
#define    DT_MAP2SXF             18 // ������ �������� � sxf
#define    DT_SORT                19 // ������ ����������

 // ���� ��������� ��� Linux ��� MainMessageHandler �������� aCode

#define    MainLinuxIdent 1

#define    MH_GETCURSORPOS        MainLinuxIdent       // 1 ��������� ������� �������
#define    MH_SETCURSORPOS        MainLinuxIdent + 1   // 2 ���������� ������� �������
#define    MH_SCREENTOCLIENT      MainLinuxIdent + 2   // 3
#define    MH_CLIENTTOSCREEN      MainLinuxIdent + 3   // 4
#define    MH_CLOSE               MainLinuxIdent + 4   // 5 ������� ����
#define    MH_GETKEYSTATE         MainLinuxIdent + 5   // 6 ������ � ��������� ������
#define    MH_OPENFILE            MainLinuxIdent + 6   // 7 ������� ����
#define    MH_GETXCONTEXT         MainLinuxIdent + 7   // 8 ������ ������������ ���������  
                                              //   �������� ���� �����
#define    MH_AFTERSTART          MainLinuxIdent + 9   // 9 �������� ���������� ���� ��������� ��������� ���� ������ � ��������
#define    MH_SELVIEWOBJ          MainLinuxIdent +10   // 10 ������ � ������������ ��������
                                              // WPARAM = 1 - ������    LPARAM - HOBJ
                                              // WPARAM = 2 - ���������
					      
 enum DATATYPE  //  ���� ���������������� ������  
 {
   DATA_SIT = 1,            // ����
   DATA_RST = 2,            // ����� 
   DATA_MTR = 3             // �������
 };  

/*  ��� Kylix         
 // ��������� ������ ������� �������� ����� 
 struct OPENFILEPARM
 {
   long int    Size;     // ������ ���������   
   char       * name;    // ������ ��� ���������� ���������� ������
   int        namesize;  // ������ ������ ��� ���������� (MAX_PATH)
   const char * title;   // ��������� ������� � ������ ����� ����������
   const char * filter;  // ������ ����� ����� ������
   int        flags;     // ����������� ������ �������
   int        index;     // ������� ����� ������ ���� ����� ��� �������� �������
   const char * path;    // ������� ���������� ��� �������� �������
 };

 // ��������� ������ ������� �������� �������   
 struct DLGCREATEOBJPARM  
 {
  long int    Size;            // ������ ���������
  HMAP        hMap;            // ������������� �����
  TASKPARM   *TaskParm;        // ��������� ������ 
  HOBJ        hObj;            // ������������� �������
  HSELECT     hSelect;         // ������
  MEDRSCPARM *MedRscParm;      // ������ ������� "����� ������������ �� ���� �����"
 };
			
 // ��������� ������ ������� ������ �������   
 struct DLGSELECTOBJECTPARMBEGIN  
 {
  long int      Size;          // ������ ���������
  HOBJ          hObj;          // ������������� �������
  MAPDFRAME*    frame;         // place - ����������� ������� ��������� (�������������
                               // ���������� �� ��������������)
  long int      place;         // frame - ������������� ������ � ������������ � place,
                               // ������ ����� �������������� ������ ��������� � ������,
                               // ��������� � Position ��������� OBJECTFORM
  OBJECTFORM*   objform;			    
  TASKPARM*     taskparm;      // ��������� TASKPARM ������� � maptype.h 
  HCHOICEOBJECT *choiceobject;
 };

 // ��������� ������ ������� �������� �����   
 struct DLGSITECREATEFORMAP  
  {     
   long int   Size;            // ������ ���������     
   HMAP       hMap;            // ������������� �����    
   TASKPARM   *TaskParm;       // ��������� TASKPARM ������� � maptype.h     
   char       *mapname;        // ������ ��� �����
  };

 // ��������� ������ ������� �������� ������ �����   
 struct DLGCLOSEDATAFORMAP  
  {     
   long int   Size;            // ������ ���������     
   HMAP       hMap;            // ������������� �����    
   long int   datatype;        // ��� ������ DATA_SIT, DATA_RST, DATA_MTR    
  };

 // ��������� ������ ������� ��������� �����������  
 struct DLGVIEWSTAFF
 {
   long int Size;            // ������ ���������     
   HMAP     hMap;            // ������������� �����    
   TASKPARM *TaskParm;       // ��������� TASKPARM ������� � maptype.h     
   int      *Note;
   long int mode;
 };

 // ��������� ������ ������� ��������� ������  
 struct DLGSEEKOBJ
 {
   long int Size;            // ������ ���������     
   HMAP     hMap;            // ������������� �����    
   TASKPARM *TaskParm;       // ��������� TASKPARM ������� � maptype.h     
   int      *Note;
 };

 // ��������� ������ ������� "������ ������ ����������� �����."
 struct DLGMAPLIST
 {
   long int    Size;         // ������ ���������     
   HMAP        hMap;         // ������������� �����    
   TASKPARM    *TaskParm;    // ��������� TASKPARM ������� � maptype.h     
   MAPLISTPARM *MapListParm; //
 };		    

 // ��������� ������ ������� ����������� �������� �� ������ ����� 
 struct DLGMAPEDITGROUP
 {
   long int    Size;         // ������ ���������     
   HMAP        hMap;         // ������������� �����    
   TASKPARM    *TaskParm;    // ��������� TASKPARM ������� � maptype.h     
   long int    regime;
   HOBJ        hObj;         // ������������� ������� �����    
   MEDPROPERTY *medproperty;  // ��������� ���������
 };

 // ����� ������� �� SELECT ��� ������
 struct DLGSELECTOBJECTSEEK
 {
   long int    Size;         // ������ ���������         
   HOBJ        hObj;         // ������������� ������� �����        
   long int    flag;                 
   HSELECT     hSelect;      // ������ ������
   OBJECTFORM  *objform;			    
   TASKPARM    *TaskParm;    // ��������� TASKPARM ������� � maptype.h     
 };

 // ��������� ������ ������� ��������� ������ 
 struct DLGPALETTECONTROLPARM
 {
   long int       Size;         // ������ ���������         
   HMAP           hMap;         // ������������� �����    
   PALETTECNTPARM *paletteparm;
   TASKPARM       *TaskParm;    // ��������� TASKPARM ������� � maptype.h     
 };

  // ��������� ������ ������� ������ �������� ����� 
 struct DLGGETSITENUMBER
 {
   long int       Size;         // ������ ���������         
   HMAP           hMap;         // ������������� �����    
   long int       sitenumber;   // ����� �����
 };

 // ��������� ������ ������� ������
 struct DLGPRINT   
 {
   long int  Size;              // ������ ���������         
   char      filename[MAX_PATH];// ��� ����� � �����
   long int  scale;             // �������
   long int  infile;            // ������� ������ ( 0 - �����; 1- � ����; 2- �� ����������)
   long int  resolution;        // ���������� ���������� ������   
 };
		      
 // ��������� ������ ������� ���������� ���� ������ ���������� ��������
 struct MCLBUILDZONESELECTED
 {
   long int               Size;         // ������ ���������         
   HMAP                   hMap;         // ������������� �����    
   TASKPARM               *TaskParm;    // ��������� TASKPARM ������� � maptype.h     
   BUILDZONESELECTEDPARM  *zoneselparm; // ��������� ���������� ���� ������ ���������� �� �����
 };

  // ��������� ������ ������� �������� ����� � SXF, DIR        
  struct DLGMAP2SXF
  {
   long int               Size;         // ������ ���������         
   HMAP                   hMap;         // ������������� �����    
   char                   *NameFile;     // ��� ����� 
  };

  // ��������� ������ ������� ���������� �����        
  struct DLGSORT
  {
   long int               Size;         // ������ ���������         
   HMAP                   hMap;         // ������������� �����    
  };
*/
#endif  // MWHANDLR_H

