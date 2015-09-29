
#ifndef RMFBASE_H
#define RMFBASE_H

#include "rmf.h"
#include "compress.h"
#include "mapdat.h"

#ifndef MAPTRANS_H   
  #include "maptrans.h"
#endif

#define min(a,b) (((a) < (b)) ? (a) : (b)) 
#define max(a,b) (((a) > (b)) ? (a) : (b))  // 24/11/05
class TRst;

// �������, ������������ � �����
typedef struct RMFRGBFILE  
{
   char Red;
   char Green;
   char Blue;
}
  RMFRGBFILE;

// ��������� ��������
typedef struct RMFELEMENT  
{
   LONG Str;
   LONG Col;
}
  RMFELEMENT;

// ��������� ����� � �-� �����������
typedef struct RMFBLOCK    
{
   union { RMFELEMENT Begin; RMFELEMENT UL; };  // ������� ����� ����
   union { RMFELEMENT End;   RMFELEMENT DR; };  // ������ ������ ����
}
  RMFBLOCK;

// ��������� ����� � ������
typedef struct RMFSITE   
{
   int Str;
   int Col;
}
  RMFSITE;

// ��������� ������
typedef struct RMFPART
{
   int      Index;       // ������ �����
   int      String;      // ����� ������
   int      Column;      // ����� �������
   char*    Address;     // ����� �����
   int      Isdirty;     // ������� ��������� �����
   unsigned Fresh;       // ������ �������� ������� �����
   int      Lock;        // ���� ������� �����          
                         // (���������� ����������)
}
  RMFPART;

// ��������� ������������� ��� �������� ���������� ��
// ����������������� ����� ��������� ������ ���
// ���������� �����i����� ����� ������
typedef struct RSTNEWBLOCK  
{
  int  FlagEdit;        // ���� ������������������� �����(0/1)
  RMFSITE Block;        // ��������� ����� � ������
}
  RSTNEWBLOCK;

// ���� �������� �������
enum RMFRETCODE { RMFOKEY = 1 };

// ������� ���������
enum RMFUNITS  { rmfm = 0, rmfdm = 1, rmfcm = 2, rmfmm = 3 };

enum { RMFFIRSTLINE = 1, RMFLASTLINE = -1 };

// ���������, ���������� ���������� ������ TRmf
typedef struct _DLLCLASS TRMFDATA
{
  TRMFDATA() : BORDER(), MASK(), Translate(), CompressData() {}   

  RMF        HEADER;             // ���������
  unsigned long  HEADEROFFSET;   // C������� �� ���������
  char       NAME[MAX_PATH];     // ������ ��� �����
  char       NAMEOFADDFILE[MAX_PATH];// ������ ��� ����������� �����
  COLORREF   PALETTE[256];       // �������

  BLOCKDESC* BLOCKDESCBUFF;      // ��������� �� ��������� ������
  int        BLOCKDESCLENGTH;    // ������ ������ ��� ��������� ������

  char*      BLOCKFLAGSBUFF;     // ��������� �� ������ ������ ������
  int        BLOCKFLAGSLENGTH;   // ������ ������ ��� ������� ������ ������

  char*      BORDERPOINTSBUFF;   // ��������� �� ������� �����
  int        BORDERPOINTSLENGTH; // ������ ������ ��� ������� �����
  int        BORDERPOINTSCOUNT;  // ����� ����� �����
  POLYDATAEX   BORDERDATA;         // ������� ����� (BORDERPOINTSBUFF)

  char*      BLOCKMASKBUFF;      // ��������� �� ������� ����� �����
  int        BLOCKMASKLENGTH;    // ������ ������ ��� ������� ����� �����
  int        BLOCKMASKWIDTH;     // ������ ����� � ����� (������ 32)

  TDataEdit  BORDER;         // ��������� �� �����  

  int        ACCESSMODE;     // ����� ������� � �����
  int        SHAREMODE;      // ����� ����������� ������� � �����
  HANDLE     FILEID;         // ������� ������������� �����
  HANDLE     FILEID0;        // ������������� ������� ����� (������ �� 4Gb)
  HANDLE     FILEID1;        // ������������� ������� ����� (������ �� 4Gb)

  int        ISCREATE;       // ���� Create/Open
  int        ISBLOCKDESC;    // ���� ���p��������� ��������� ������
  int        ISBLOCKFLAGS;   // ���� ���p��������� ������� ������ ������
  int        ISBORDER;       // ���� ���p��������� �����
  int        ISPALETTE;      // ���� ���p��������� �������
  int        ISHEADER;       // ���� ���p��������� ���������
  long       ISERROR;        // ���� ��������� ������
  int        ISADDITION;     // ���� ���p��������� ��������������� �������� ������
  int        ISMASK;         // ���� ���p��������� �����    

  char*      BUFFER;         // ��������� �� ������ ������
  int        BUFSIZE;        // ������ ����� ������
  int        BLOCKNUMB;      // �-�� ������ ������
  char* CompressBlockBuffer; // ����� ������ ������� �����
                             // (���������� ������ � BUFFER)

  RMFPART    PART[16];       // ��������� ������
  int        CURRENT;        // ����� ������� ����� ������
  int        BlockCountLimit;// ����������� ���������� ���������� ������ 
       // ����������� �������� � ���� ��� ���������� � �������� 100,200,256 �������
       // ������������� �������� 4,2,1 ���� ��������������.

  FILETIME  Condition;       // ��������� ����� ������  

  unsigned   Fresh;          // ������� ������ �������� ������� �����
  int    DuplicateExistence; // ���� ������������� ������ ��� ��������
                             // ������� ����������� ����� 
  
  double HeightUnitInMeter;  // ����� ������ ������ �� ����
  double HeightMeterInUnit;  // ����� ������ � ������� ������
  TRst          * Duplicate;  // ��������� �� ����� �����������

  RSTNEWBLOCK   NewBlock;     // ��������� ������������� ��� �������� ���������� ��
                              // ����������������� ����� ��������� ������ ���
                              // ����������� ����������� ����� ������
                              // ������������ � ������ WriteBlock - SaveDuplicates

  int           NewBorder;    // ���� ��������� ����� � ����
                              // ���� 1,�� ����� ������ ����������� ����� ����������
  int           ReadOk;

  TCompress     CompressData;

  RMFADDITION   ADDITION;  // �������������� �������� ������ (�������)

  int           NewMask;       // ���� ��������� ����� � ����    
                               // ���� 1,�� ����� ������ ����������� ����� ����������
  char*      MASKPOINTSBUFF;   // ��������� �� ������� �����       
  int        MASKPOINTSLENGTH; // ������ ������ ��� ������� �����  
  int        MASKPOINTSCOUNT;  // ����� ����� �����                
  POLYDATAEX   MASKDATA;       // ������� ����� (MASKPOINTSBUFF)   

  TTranslate Translate;        // ��������� ��������� ���������    
  int        GeoAvailableFlag; // ���� ����������� ������� ������������� ��������� 

  TDataEdit  MASK;             // ��������� �� �����  
}
 TRMFDATA;

// ������� ����� ���� �� ��������� RMF
// ��� ������ ���������� ����
int _fastcall rmfCreateByRmf(TRMFDATA *rmfdata, char* name,
                             RMF* rmf, RMFADDITION* rmfaddition,  
                             COLORREF* palette);

// �������� �������� ���� ����������
void _fastcall rmfClearAll(TRMFDATA *rmfdata);

// ������� ������
void _fastcall rmfClearBuffer(TRMFDATA *rmfdata);

// ��������� ������ � ����e
int _fastcall rmfSave(TRMFDATA *rmfdata, int force);

// �������� �����
void _fastcall rmfClose(TRMFDATA *rmfdata, int force);

// ���������� ������ ������
void _fastcall rmfFreeBuffer(TRMFDATA *rmfdata);

// �������� �����
// ��� ������ ���������� ����
int _fastcall rmfOpen(TRMFDATA *rmfdata, const char * name, int mode);

// �������� �����
// ��� ������ ���������� ����
int _fastcall rmfCreateByName(TRMFDATA *rmfdata, const char * name);

// ���������� � ���������������� ����� � ������� ����� �����
// ����� �������� � ���� �����
int _fastcall rmfAllocateBuffer(TRMFDATA *rmfdata, int count);

// �������� ������ ��� ��������� ������ ������
// ��� ������ ���������� ����
int _fastcall rmfAllocateBlockDesc(TRMFDATA *rmfdata, int size);

// �������� ������ ��� ������ ������ ������
// ��� ������ ���������� ����
int _fastcall rmfAllocateBlockFlags(TRMFDATA *rmfdata, int size);

// �������� ������ ��� ������� ����� �����
// ��� ������ ���������� ����
int _fastcall rmfAllocateBlockMask(TRMFDATA *rmfdata, int size);

// �������� ������ ��� ������� �����
// ��� ������ ���������� ����
int _fastcall rmfAllocateBorderPoints(TRMFDATA *rmfdata, int size);

// �������� ������ ��� ������� �����    
// ��� ������ ���������� ����
int _fastcall rmfAllocateMaskPoints(TRMFDATA *rmfdata, int size);

// ������� ����� ����
// ��� ������ ���������� ����
int _fastcall rmfCreate(TRMFDATA *rmfdata, const char * name,
                        int width, int height, int nbits,
                        COLORREF * palette, double scale, double precision);
			
// �������� ������������ ����� .RMF
// ��� ������ ���������� ���� (��� ������ Error())
int _fastcall rmfVerify(TRMFDATA *rmfdata, long int label);

// ������ �������� �� ��� ���������� �������� �� ������
int _fastcall rmfGetPoint(TRMFDATA *rmfdata, long *value, 
                          int string, int column);
			  
// ������ double-�������� �� ��� ���������� �������� �� ������
int _fastcall rmfGetDoublePoint(TRMFDATA *rmfdata, 
                                double *value, int string, int column);

//  ������ ��������  �� ��� ������������� ����������� (� ������)
//  �� ������
int _fastcall rmfGetPlanePoint(TRMFDATA *rmfdata,
                               long *value, double x, double y);

//  ������ DOUBLE-��������  �� ��� ������������� �����������
//  (� ������) �� ������
int _fastcall rmfGetDoublePlanePoint(TRMFDATA *rmfdata,
                                     double *value, double x, double y);

//  ���������� �������� �������� ������� ������������� �� ��������
//  ������������� ����������� (� ������)
int _fastcall rmfGetPlanePointTriangle(TRMFDATA *rmfdata,
                                       double *value, double x, double y) ;

// ������ �������� �� ��� ���������� �������� � �����
int _fastcall rmfPutPoint(TRMFDATA *rmfdata,
                          long value, int string, int column);

// ������ double-�������� �� ��� ���������� �������� � �����
int _fastcall rmfPutDoublePoint(TRMFDATA *rmfdata,
                                double value, int string, int column);

//  ������ ��������  �� ��� ������������� ����������� (� ������)
//  � �����
int _fastcall rmfPutPlanePoint(TRMFDATA *rmfdata,
                               long value, double x, double y);

//  ������ DOUBLE-��������  �� ��� ������������� �����������
//  (� ������) � �����
int _fastcall rmfPutDoublePlanePoint(TRMFDATA *rmfdata,
                                     double value, double x, double y);

// ������ �������� �� ��� ���������� �������� �� �����.
// ��� ������ ���������� ����.
int _fastcall rmfReadPoint(TRMFDATA *rmfdata,
                           long *color, int string, int column);

// ������ �������� �� ��� ���������� �������� � ����
int _fastcall rmfWritePoint(TRMFDATA *rmfdata,
                            long color, int string, int column);

// ������ ������� �� ���. �����. ������
// x1,y1 - ������,������� ��������� ����� �������
// x2,y2 - ������,������� �������� ����� �������
// ��� ������ ���������� ����
int _fastcall rmfPutLine(TRMFDATA *rmfdata,
                         long color, int x1, int y1, int x2, int y2);

// ������ ������� �� ������������� ����������� ������ (� ������)
//  x1,y1 - ���������� ��������� ����� �������
//  x2,y2 - ���������� �������� ����� �������
// ��� ������ ���������� ����
int _fastcall rmfPutPlaneLine(TRMFDATA *rmfdata,
                              long value, double x1, double y1,
			      double x2, double y2);

// ������ �������������� ������� ������
//  bits    - ��������� �� ������ ����������� ������� �������
//  left    - �������� ����� � ��������� (��������� �� ������� �����)
//  top     - �������� ������ � ���������
//  width   - ������ � ���������
//  height  - ������ � ���������
//  begining    - ������ �����������:
//    == FIRSTLINE - (bits - ��������� �� ������ ������ ������� �������)
//    == LASTLINE  - (bits - ��������� �� ��������� ������ ������� �������,
//                           � BMP ����������� �������� ����� - �����)
//  widthinbyte - ������ � ������
// ������� ������������:
//  ��� rmfdata->HEADER.ElementSize == 1 (���) - left ������ 8,
//                                  == 4 (���) - left ������ 2
// ��� ������ ���������� 0
int _fastcall rmfPutFrame(TRMFDATA *rmfdata,char* bits,
                          int left, int top,
			                    int width, int height,
                          int begining, int widthinbyte);

// ���������� �������� ������������ ��������� �������     
// � ������ �������� �����, ������������ � ������� bits
//   width  - ������ ������� � ���������
//   height - ������ �������� ���������
//   begining - ������ �����������:
//     == FIRSTLINE - (bits - ��������� �� ������ ������ �������)
//     == LASTLINE  - (bits - ��������� �� ��������� ������ �������)
// ��� ������ ���������� 0
int _fastcall rmfSetFrameRange(TRMFDATA *rmfdata,char* bits,
			                         int width,int height,int begining);

// ������ ����� �� ������ � ����
int _fastcall rmfWriteBlockByIndex(TRMFDATA *rmfdata, int partindex);

// ������ ����� ������ {string,column}
// ��� ������ ���������� ����.
int _fastcall rmfSaveBlock(TRMFDATA *rmfdata, int string, int column);

// ������ ����� {string,column} �������� "size" � ������ "bits"
// ���������� ���������� ����������� ����
// ��� ������ ���������� ����
int _fastcall rmfReadBlockToMemory(TRMFDATA *rmfdata, int string,
                                   int column, char* bits, int size);

// ������ ����� {string,column} �������� "size" �� ������ "bits"
// ���������� ���������� ���������� ����
// ��� ������ ���������� ����
int _fastcall rmfWriteBlock(TRMFDATA *rmfdata,
                            int string, int column, char* bits, int size);

// ������ ��������� ������ �� ����� � �����
// ��� ������ ���������� ����
int _fastcall rmfReadBlockDesc(TRMFDATA *rmfdata);

// ������ ��������� ������ � ���� �� ������
// ��� ������ ���������� ����
int _fastcall rmfWriteBlockDesc(TRMFDATA *rmfdata);

// ������ ������� ������ ������ �� ����� � �����
// ��� ������ ���������� ����
int _fastcall rmfReadBlockFlags(TRMFDATA *rmfdata);

// ������ ������� ������ ������ � ���� �� ������
// ��� ������ ���������� ����
int _fastcall rmfWriteBlockFlags(TRMFDATA *rmfdata);

// ������ ����� �� �����
// ��� ������ ���������� ����
int _fastcall rmfReadBorder(TRMFDATA *rmfdata);

// ������ ����� � ���� �� ������
// ��� ������ ���������� ����
int _fastcall rmfWriteBorder(TRMFDATA *rmfdata);

// ������ ����� �� �����           
// ��� ������ ���������� ����
int _fastcall rmfReadMask(TRMFDATA *rmfdata);

// ������ ����� � ���� �� ������   
// ��� ������ ���������� ����
int _fastcall rmfWriteMask(TRMFDATA *rmfdata);

// ����������� ��������� �����
int _fastcall rmfWhereBlock(TRMFDATA *rmfdata,
                            RMFBLOCK *datablock, int string, int column);

// ����� ��������� ���-��������� �����                    
int _fastcall rmfWhereSouthWestBlock(TRMFDATA *rmfdata, RMFBLOCK * block);

// ����� ��������� ���-��������� ����� � ������           
int _fastcall rmfWhereSouthWestBlockPlane(TRMFDATA *rmfdata,
                                          double * x, double * y);

// ������ ������� �� �����
// ��� ������ ���������� ����
int _fastcall rmfReadPalette(TRMFDATA *rmfdata);

// ������ ������� � ����
// (�� ������ ������� ���������� ���������� ����� ������� �
//  ��������� - PaletteLength(long))
// ��� ������ ���������� ����
int _fastcall rmfWritePalette(TRMFDATA *rmfdata);

// ������ ��������������� �������� �� �����
// ��� ������ ���������� ����
int _fastcall rmfReadAddition(TRMFDATA *rmfdata);

// ������ ��������������� �������� � ����
// (�� ������ ������� ���������� ���������� ����� ���������������
//  �������� �  ��������� - AdditionLength(long))
// ��� ������ ���������� ����
int _fastcall rmfWriteAddition(TRMFDATA *rmfdata);

// ������ ��������� �� �����
// ��� ������ ���������� ����
int _fastcall rmfReadHeader(TRMFDATA *rmfdata);

// ������ ��������� � ����
// ��� ������ ���������� ����
int _fastcall rmfWriteHeader(TRMFDATA *rmfdata);

// ���������� �������� � ������ ����� �������/�������
// offset - ��������
// ��� ��������� ������ � �������� ����� 4GB:
//   HEADER.OffsetFactor = 8;
//   offset = offset >> HEADER.OffsetFactor;
// ��� ������ ���������� ����
int _fastcall rmfOffsetTheFile(TRMFDATA *rmfdata, long int offset, int type);

// ����������� ����������� ����� �����
// ��������� ������ � �������� ����� 4GB
// ���������� ����� ����� � ������
// ��� ��������� ������ � �������� ����� 4GB:
//  unsigned long int top64 = 0;
//  unsigned long int lowSize = rmfLongFileLength(rmfdata, (long int*)&top64);
//  if (rmfdata->HEADER.OffsetFactor != 0)
//    {  fileLength = top64 << (rmfdata->HEADER.OffsetFactor*3);
//       fileLength |= lowSize;  }
// ��� ������ ���������� ����
unsigned long int _fastcall rmfLongFileLength(TRMFDATA *rmfdata, long int* top64);

// ������������ ����� ����������� �����
// ��� ��������� ����������� �������� ����� 4GB
// ��� ������ *.rsw ��������� ���������� ���� *.rsw.01
// ��� ������� *.mtw ��������� ���������� ���� *.mtw.01
// ��� ������ ���������� ����
int _fastcall rmfNameOfAdditionalFile (TRMFDATA *rmfdata, char* name);

// �������� ����������� �����
// ��� ��������� ����������� �������� ����� 4GB
// ��� ������ *.rsw ��������� ���������� ���� *.rsw.01
// ��� ������� *.mtw ��������� ���������� ���� *.mtw.01
// ��� ������ ���������� ����
int _fastcall rmfCreateAdditionalFile(TRMFDATA *rmfdata, const char * mame);

// �������� ����������� �����
// ��� ��������� ����������� �������� ����� 4GB
// ��� ������ *.rsw ��������� ���������� ���� *.rsw.01
// ��� ������� *.mtw ��������� ���������� ���� *.mtw.01
// ��� ������ ���������� ����
int _fastcall rmfOpenAdditionalFile(TRMFDATA *rmfdata, const char * name);

// ����������� ����������� ����� �����
// ���������� ����� ����� � ������
// ��� ��������� ������ � �������� ����� 4GB:
// ���������� ����� �������� ����� � ������ � �����������
// �� rmfdata->FILEID (�������� �������� FILEID0, FILEID1)
// ��� ������ ���������� ����
unsigned long _fastcall rmfFileLength(TRMFDATA *rmfdata);

// ����������� ����e�������� ����� �����
// ������������ �� �������� �������
// ��� ������ ���������� ����
double _fastcall rmfCalculationFileLength(TRMFDATA *rmfdata, int width,
                                          int height, int bitpixel);

// ��������� ���� ���������� �����
// ��� ������ ���������� ����
int _fastcall rmfGetUpdateTime(TRMFDATA *rmfdata, FILETIME * mtime);

// ��������� ������� ���������� ����� �� �����
// ��� ������ ���������� ����
int _fastcall rmfDiskFreeSpace(TRMFDATA *rmfdata, char*name);

// ��������� ��������� �� �������
COLORREF* _fastcall rmfPalette(TRMFDATA *rmfdata, COLORREF* palette, int count);

// ��������� ����� �����, ��������� ������ ���������
// ���� ��������� ����� ��� � ������, �� �� ����������� �� �����
// ��� ������ ���������� ����
char* _fastcall rmfGetBlockAddress(TRMFDATA *rmfdata, int string, int column);

// ��������� ����� �����, ��������� ������ ���������
// ���� ��������� ����� ��� � ������, �� �� ����������� �� �����
// ��������� ���� (������������� ����������)
// ��� ������ ���������� ����                           
char* _fastcall rmfGetBlockAddressAndLock(TRMFDATA *rmfdata, int string, int column);

// ���������� ����� (�������������� ����������)
void  _fastcall rmfUnLockBlocks(TRMFDATA *rmfdata);     

// ��������� ����� �����, ��������� ������ ���������
// ���� ��������� ����� ��� � ������, �� �� ����������� �� �����
// ��� ���������� � ����� - ���������
// ��� ������ ���������� ����
char* _fastcall rmfGetBlockAddressAndCreate(TRMFDATA *rmfdata,
                                            int string, int column);

// ������ ����� {string,column} � ������� ���� ������
int _fastcall rmfReadBlock(TRMFDATA *rmfdata, int string, int column);

// ���������� ����� ������ ��������� "���������� ����������"
int _fastcall rmfBufferBlockInit(TRMFDATA *rmfdata, int partindex);

// ���������� ����� ��������� "���������� ����������"  
int _fastcall rmfFillBlock(TRMFDATA *rmfdata, int string, int column);

// ���������� ������ ����� ������, ������������ ������  
int _fastcall rmfFillVisiblePart(TRMFDATA *rmfdata, long int color);

// ���������� ������ ����� ����� ������-256, ������������ ������ 
int _fastcall rmfFillVisiblePartBlock256(TRMFDATA *rmfdata, long strBlock, long colBlock, long color);

// ���������� ������ ����� ����� ������, ������������ ������ 
int _fastcall rmfFillVisiblePartBlock(TRMFDATA *rmfdata, long strBlock, long colBlock, long color);

// C�������� ���������� ������
int _fastcall rmfSaveBuffer(TRMFDATA *rmfdata);

// ������� �����
int _fastcall rmfDeleteBorder(TRMFDATA *rmfdata);

// ���������� �����
int _fastcall rmfSetBorder(TRMFDATA *rmfdata, DATAEDIT* data); 

// ������������� ������� �����
void _fastcall rmfBorderDataInit(TRMFDATA *rmfdata);

// ������ ������� ����� ������������ �����
POLYDATAEX* _fastcall rmfGetBorderMetric(TRMFDATA *rmfdata,
                                    int string, int column);

// ������ ������������ �� ��������� ������� ����� ������������ �����
POLYDATAEX* _fastcall rmfGetBorderMetricTurn(TRMFDATA *rmfdata,  
                                    int string, int column);

// ������� �����                                             
int _fastcall rmfDeleteMask(TRMFDATA *rmfdata);

// ���������� �����                                          
int _fastcall rmfSetMask(TRMFDATA *rmfdata, DATAEDIT* data);

// ������������� ������� �����                               
void _fastcall rmfMaskDataInit(TRMFDATA *rmfdata);

// ������� ��������� ������� �������� ��������� ������
//          (��� 16 � 256-������� �������)
//  bytes - ������ �������� (1 - ���� �������, 0 - ���� �����)
//  size  - ������ �������
// ���������� ����� ��������� ������
int _fastcall rmfGetInvisibleColors(TRMFDATA *rmfdata,
                                    unsigned char* bytes, int size);

// ��������� ��������� ������� �������� ��������� ������
//          (��� 16 � 256-������� �������)
//  bytes - ������ �������� (1 - ���� �������, 0 - ���� �����)
//  size  - ������ �������
// ���������� ����� ��������� ������
int _fastcall rmfSetInvisibleColors(TRMFDATA *rmfdata,
                                    unsigned char* bytes, int size);

// ������� ��������� ������� �������� ������� ������
//          (��� 16 � 256-������� �������)
//  bytes - ������ �������� (1 - ���� �����, 0 - ���� �������)
//  size  - ������ �������
// ���������� ����� ��������� ������
int _fastcall rmfGetVisibleColors(TRMFDATA *rmfdata,
                                  unsigned char* bytes, int size);

// ��������� ��������� ������� �������� ������� ������
//          (��� 16 � 256-������� �������)
//  bytes - ������ �������� (1 - ���� �����, 0 - ���� �������)
//  size  - ������ �������
// ���������� ����� ��������� ������
int _fastcall rmfSetVisibleColors(TRMFDATA *rmfdata,
                                  unsigned char* bytes, int size);

// ������ ����� {string,column} �������� "size" �� DIB-����� "mask"
// �������� "color"
// ��� ������ ���������� ����
int _fastcall rmfPutBlockByMask(TRMFDATA *rmfdata, int string,
                                int column, char* mask, long size,
                                long width,long height,long value);

// ������ �������������� ������� ������
//  bits    - ��������� �� ������ ����������� ������� �������
//  left    - �������� ����� � ��������� (��������� �� ������� �����)
//  top     - �������� ������ � ���������
//  width   - ������ � ��������� (��������� �� ������� �����)
//  height  - ������ � ���������
// ������� ������������:
//  ��� rmfdata->rmfdata->HEADER.ElementSize == 1 (���) - left,width ������ 8,
//                    == 4 (���) - left,width ������ 2
// ��� ������ ���������� 0
int _fastcall rmfGetFrame(TRMFDATA *rmfdata, char* bits, int left,
                          int top, int width, int height, int widthinbyte);

// ����������� �������������� ������� ��������� ������    
// � �������������� ������, ������������� � ������� ������.
//   bits   - ��������� �� ������ ������� ������;
//   width  - ������ ������� ������ � ��������� COLORREF
//            (���������� �������� ��������������� ������);
//   height - ������ ������� ������ � ���������
//            (���������� ����� ��������������� ������);
//   strL,colL,strR,colR - ���������� ������ � ������� ���������
//                         ��������� ������, ������� ����������
//                         ������� ��������� ������� ��������������
//                         �������.
// ��� ������ ���������� ����.
int _fastcall rmfGetFrameTurn(TRMFDATA *rmfdata,COLORREF* bits,
                              int width, int height,
                              double strL, double colL,
                              double strR, double colR);

// ��������� ������� ��������� (��� �������)
unsigned long _fastcall rmfPutMeasure(TRMFDATA *rmfdata, unsigned long measure);

// ������� ������� ��������� (��� �������)
unsigned long _fastcall rmfGetMeasure(TRMFDATA *rmfdata);

// ���������� ����� �������
int _fastcall rmfAccessMode(TRMFDATA *rmfdata,UINT mode);

// ����������� ������ �������� �����
long _fastcall rmfCurrentBlockHeight(TRMFDATA *rmfdata, int string);

// ����������� ������ �������� �����
long _fastcall rmfCurrentBlockWidth(TRMFDATA *rmfdata, int column);

// ����������� ����� �����
long _fastcall rmfGetBlockLength(TRMFDATA *rmfdata, int index);

// ��������� ����� �����
long _fastcall rmfPutBlockLength(TRMFDATA *rmfdata, int index, long length);

// ����������� ������� �������� ����� (����)
long _fastcall rmfCurrentBlockSize(TRMFDATA *rmfdata, int string, int column);

// ����������� ������� ����� (����)
long _fastcall rmfBlockSize(TRMFDATA *rmfdata);

// ����������� �������� �� ���� � �����
unsigned long _fastcall rmfGetBlockOffset(TRMFDATA *rmfdata, int index);

// ��������� �������� �� ���� � �����
unsigned long _fastcall rmfPutBlockOffset(TRMFDATA *rmfdata,
                                          int index, unsigned long offset);
// ������� ����� ����������� �����
int _fastcall rmfGetBlockVisible(TRMFDATA *rmfdata, int index);

// ��������� ����� ����������� �����
int _fastcall rmfPutBlockVisible(TRMFDATA *rmfdata, int index, int view);

// ������� ����� ����������� �� �����
int _fastcall rmfGetShowByBorder(TRMFDATA *rmfdata);

// ��������� ����� ����������� �� �����
int _fastcall rmfPutShowByBorder(TRMFDATA *rmfdata, int value);

// ������� ����� ����������� �� �����          
int _fastcall rmfGetShowByMask(TRMFDATA *rmfdata);

// ��������� ����� ����������� �� �����        
int _fastcall rmfPutShowByMask(TRMFDATA *rmfdata, int value);

// ������� ���������� ������
long _fastcall rmfBlockCount(TRMFDATA *rmfdata);

// ������� ���������� ����� ������
long _fastcall rmfBlockStringCount(TRMFDATA *rmfdata);

// ������� ���������� ������� ������
long _fastcall rmfBlockColumnCount(TRMFDATA *rmfdata);

// �������/��������� ������ ����� (�����)
long _fastcall rmfGetBlockHeight(TRMFDATA *rmfdata);
long _fastcall rmfPutBlockHeight(TRMFDATA *rmfdata, long height);

// �������/��������� ������ ����� (��������)
long _fastcall rmfGetBlockWidth(TRMFDATA *rmfdata);
long _fastcall rmfPutBlockWidth(TRMFDATA *rmfdata, long width);

// �������/��������� ������������ �������� ��������(��� �������)
double _fastcall rmfGetMinimum(TRMFDATA *rmfdata);
double _fastcall rmfPutMinimum(TRMFDATA *rmfdata, double minimum);

// �������/��������� ������������� �������� ��������(��� �������)
double _fastcall rmfGetMaximum(TRMFDATA *rmfdata);
double _fastcall rmfPutMaximum(TRMFDATA *rmfdata, double maximum);

// �������/��������� ���������� ��������� �� ����
double _fastcall rmfGetPrecision(TRMFDATA *rmfdata);
double _fastcall rmfPutPrecision(TRMFDATA *rmfdata, double precision);

// �������/��������� ��������
double _fastcall rmfGetScale(TRMFDATA *rmfdata);
double _fastcall rmfPutScale(TRMFDATA *rmfdata, double scale);

// �������/��������� ���� �����
long _fastcall rmfGetMapType(TRMFDATA *rmfdata);
long _fastcall rmfPutMapType(TRMFDATA *rmfdata, long maptype);

// �������/��������� ���� ��������
long _fastcall rmfGetProjectionType(TRMFDATA *rmfdata);
long _fastcall rmfPutProjectionType(TRMFDATA *rmfdata, long projectiontype);

// �������/��������� ���������� ������ �� �������
double _fastcall rmfGetMeterInElement(TRMFDATA *rmfdata);
double _fastcall rmfPutMeterInElement(TRMFDATA *rmfdata, double meterinelement);

// ��������� �������� ��������� ��������� � ���������� ������ ��
// �������� ��������� ���������
long _fastcall rmfSetProjection(TRMFDATA *rmfdata);  

// ������ �������� ��������� ���������             
// ���� ���� ����������� ������� ������������� ��������� ����� ����,
// �� ��� ������ �������� �-�
// �� ������ ��������� MAPREGISTEREX
long _fastcall rmfGetRegister(TRMFDATA *rmfdata,MAPREGISTEREX* mapregister);
// ��������� �������� ��������� ��������� �             
// ����� ����������� ������� ������������� ���������
// �� ������ ��������� MAPREGISTEREX
long _fastcall rmfSetRegister(TRMFDATA *rmfdata,MAPREGISTEREX* mapregister);

// �������/��������� ����� �������� � ������ � ������
double _fastcall rmfGetLocationX(TRMFDATA *rmfdata);
double _fastcall rmfPutLocationX(TRMFDATA *rmfdata, double location);

double _fastcall rmfGetLocationY(TRMFDATA *rmfdata);
double _fastcall rmfPutLocationY(TRMFDATA *rmfdata, double location);

// �������/��������� ������ ������� ���������
double _fastcall rmfGetFirstMainParallel(TRMFDATA *rmfdata);
double _fastcall rmfPutFirstMainParallel(TRMFDATA *rmfdata, double parallel);

// �������/��������� ������ ������� ���������
double _fastcall rmfGetSecondMainParallel(TRMFDATA *rmfdata);
double _fastcall rmfPutSecondMainParallel(TRMFDATA *rmfdata, double parallel);

// �������/��������� ��������� ������� �����
double _fastcall rmfGetMainPointParallel(TRMFDATA *rmfdata);
double _fastcall rmfPutMainPointParallel(TRMFDATA *rmfdata, double parallel);

// �������/��������� ������� ���������
double _fastcall rmfGetAxisMeridian(TRMFDATA *rmfdata);
double _fastcall rmfPutAxisMeridian(TRMFDATA *rmfdata, double meridian);

// �������/��������� ������ ������ ��������                 
double _fastcall rmfGetPoleLatitude(TRMFDATA *rmfdata);
double _fastcall rmfPutPoleLatitude(TRMFDATA *rmfdata, double polelatitude);

// �������/��������� ������� ������ ��������                
double _fastcall rmfGetPoleLongitude(TRMFDATA *rmfdata);
double _fastcall rmfPutPoleLongitude(TRMFDATA *rmfdata, double polelongitude);

// �������/��������� ���� ����������                        
long _fastcall rmfGetEllipsoideKind(TRMFDATA *rmfdata);
long _fastcall rmfPutEllipsoideKind(TRMFDATA *rmfdata, long ellipsoidekind);

// �������/��������� ������� �����                          
long _fastcall rmfGetHeightSystem(TRMFDATA *rmfdata);
long _fastcall rmfPutHeightSystem(TRMFDATA *rmfdata, long heightsystem);

// �������/��������� ������� ���������                      
long _fastcall rmfGetCoordinateSystem(TRMFDATA *rmfdata);
long _fastcall rmfPutCoordinateSystem(TRMFDATA *rmfdata, long coordinatesystem);

// �������/��������� ������ ����                            
long _fastcall rmfGetZoneNumber(TRMFDATA *rmfdata);
long _fastcall rmfPutZoneNumber(TRMFDATA *rmfdata, long zonenumber);

// �������/��������� ������ �-� �����������
long _fastcall rmfGetHeight(TRMFDATA *rmfdata);
long _fastcall rmfPutHeight(TRMFDATA *rmfdata, long height);

// �������/��������� ������ �-� �����������
long _fastcall rmfGetWidth(TRMFDATA *rmfdata);
long _fastcall rmfPutWidth(TRMFDATA *rmfdata, long width);

// �������/��������� �������� ����������(��� �������)
double _fastcall rmfGetPseudoCode(TRMFDATA *rmfdata);
double _fastcall rmfPutPseudoCode(TRMFDATA *rmfdata, double pseudocode);

class _DLLCLASS TRmf : public TRMFDATA
{
protected:

  // ������������ ������
  TRmf(char * name, int width, int height, int bit,
       COLORREF* palette = 0, double scale = 0,
       double precision = 0);

public :

 // ������� ���������
 enum UNITS  { m = rmfm, dm = rmfdm, cm = rmfcm, mm = rmfmm };

 // ���� �������� �������
 enum RETCODE { OKEY = RMFOKEY };

 enum { FIRSTLINE = RMFFIRSTLINE, LASTLINE = RMFLASTLINE };

//-----------------------------------------------------------------
// ����������� �� ���������
//-----------------------------------------------------------------

  TRmf();
  TRmf(char* name, RMF* rmf, RMFADDITION* rmfaddition, COLORREF* palette = 0); 

 ~TRmf();


//*****************************************************************
//  ����-������� ������ TRmf
//*****************************************************************

  // ������� ������ ������� � �����
  int AccessMode() { return ACCESSMODE; }

  // ������� �������� ����� "�������� ��� ��������������"
  int IsRmfEdit() { return (AccessMode() & GENERIC_WRITE); }

  // ��������� ����� ������������ �������
  int IsPalette(int set) { return (ISPALETTE = set); }

  // ��������� ����� ������������ ��������������� �������� ������
  int IsAddition(int set) { return (ISADDITION = set); }

  // ��������� ������ � ����e
  int Save(int force);

  // ���������/������� �����
  int SetBorder(TDataEdit* data);
  TDataEdit* GetBorder() { return &BORDER; }

  // ������� �����
  int DeleteBorder();

  // ���������/������� ����� �����������       
  int SetMask(TDataEdit* data);                

  TDataEdit* GetMask() { return &MASK; }       

  // ������� �����                             
  int DeleteMask();


  // ������� ������ ������� ����� �����
  char* GetMaskAddress() { return BLOCKMASKBUFF; }

  // ������� ������ ������� ������ ��������� ������
  char* BlockFlags() { return BLOCKFLAGSBUFF; }

  // �������/��������� ������ ����� � ������
  int BlockMaskWidth() { return BLOCKMASKWIDTH; }
  int BlockMaskWidth(int width) { return BLOCKMASKWIDTH = width; }

  // �������� �����
  void Close() { Close(0); }

//*****************************************************************
//  ������� ��� ������ � �������
//*****************************************************************

protected :

  // ���������� ������ � ������� ����� �����
  int AllocateBuffer(int count = 8);

  // �������� ������ ��� ������� ����� �����
  int AllocateBlockMask(int size);

  // ������������ ������
  void FreeBuffer();

  // ���������� ������
  int SaveBuffer();

  // ������� ������
  void ClearBuffer();

  // ������� ��������� �� ������� ���� ������
  char* Bits() { return PART[CURRENT].Address; }

  // �����������/��������� �������������� �������� ����� ������
  int IsDirty()        { return PART[CURRENT].Isdirty; }
  int IsDirty(int set) { return PART[CURRENT].Isdirty = set; }

  // ���������� ����� ������ ��������� "���������� ����������"
  int BufferBlockInit(int partindex);

  // ������������� ������� �����
  void BorderDataInit();

  // ������������� ������� ����� �����������
  void MaskDataInit();  



public:

  // ������� �����a ���������
  RMF* GetHeader() { return &HEADER; }

  // ������� �����a ���������      
  // �������������� �������� ������ (�������)
  RMFADDITION* GetAdditionHeader() {return &ADDITION;}

  // C������� �� ���������
  unsigned long HeaderOffset(){ return HEADEROFFSET;}   

  // ������ �����a �����, ��������� ������ ���������
  // ���� ��������� ����� ��� � ������, �� �� ����������� �� �����
  // ��� ������ ���������� ����
  char* GetBlockAddress(int string, int column);

  // ��������� ����� �����, ��������� ������ ���������
  // ���� ��������� ����� ��� � ������, �� �� ����������� �� �����
  // ��� ���������� � ����� - ���������
  // ��� ������ ���������� ����
  char* GetBlockAddressAndCreate(int string, int column);

  // ����������� ��������� �����
  int WhereBlock(RMFBLOCK& block, int string, int column);

  // ����� ��������� ���-��������� ����� � ������           
  int WhereSouthWestBlockPlane(double * x, double * y);

  // ��������� ������� �����
  int BlockBeginColumn(int column) { return column*BlockWidth(); }

  // ��������� ������ �����
  int BlockBeginString(int string) { return string*BlockHeight(); }

  // �������/��������� �������� �� ���� � �����
  unsigned long BlockOffset(int index);
  unsigned long BlockOffset(int index, unsigned long offset);

  // �������/��������� ����� �����
  long BlockLength(int index);
  long BlockLength(int index, long length);

  // �������/��������� ����� ��������� �����
  int BlockVisible(int index);
  int BlockVisible(int index, int view);

  // ������ ������� ����� ������������ �����
  POLYDATAEX* GetBorderMetric(int string, int column);

  // ������ ������������ �� ��������� ������� ����� ������������ �����
  POLYDATAEX* GetBorderMetricTurn(int string, int column);  
  
//*****************************************************************
//  ������� ���������� � ������������
//*****************************************************************

  // ���������� ����� LZW
  int Compress(const char* in,  int sizein,
                     char* out, int sizeout);

  // ������������ ����� LZW
  int Decompress(const char* in,  int sizein,
                       char* out, int sizeout);

  // ���������� ����� 32-������ �������
  // (�������� ����� ���� ����������� ����������
  //  ������������ ��� ���������� ��������)
  int CompressMtr(const char* in,  int sizein,
                        char* out, int sizeout, long minimum);

  // ������������ ����� 32-������ �������
  int DecompressMtr(const char* in,  int sizein,
                          char* out, int sizeout);



//*****************************************************************
//  ������� ��� ������ � ������ :
//*****************************************************************

protected:

  // ���������� ����� �������
  int AccessMode(UINT mode)
 	{
    ACCESSMODE = (mode & (GENERIC_READ|GENERIC_WRITE));
    if (ACCESSMODE == 0) ACCESSMODE = GENERIC_READ|GENERIC_WRITE;
    return ACCESSMODE;
  }

  // ������� ����� ����
  // ��� ������ ���������� ����
  int Create(char * name, int width, int height, int nbits,
             COLORREF * palette,
             double scale = 0, double precision = 0);

public:

  int Create(char* name, RMF* rmf, RMFADDITION* rmfaddition, COLORREF* palette = 0); 

protected:

  // �������� �����
  // force - ������� ������������ ������
  void Close(int force);

  // �������� �����
  // ��� ������ ���������� ����
  int Open(const char * name, int mode = 0);

  // �������/��������� ������ ����������� ������� � �����
  int ShareMode() { return SHAREMODE; }
  int ShareMode(UINT shmode)
  {
    SHAREMODE = shmode;
    return SHAREMODE;
  }

protected:

  // �������� �������� ���� ���������� ������
  void ClearAll();

  // �������� ������ ��� ��������� ������ ������
  // ��� ������ ���������� ����
  int AllocateBlockDesc(int size);
   BLOCKDESC* BlockDesc() { return BLOCKDESCBUFF; }  // ������� ������

  // �������� ������ ��� ������ ������ ������
  // ��� ������ ���������� ����
  int AllocateBlockFlags(int size);

  // �������� ������ ��� ������� �����
  // ��� ������ ���������� ����
  int AllocateBorderPoints(int size);
        char* BorderPoints() { return BORDERPOINTSBUFF; }

  // �������� ������ ��� �������
  // ��� ������ ���������� ����
  int AllocateMaskPoints(int size);                        
        char* MaskPoints() { return MASKPOINTSBUFF; }      

  // �������/��������� ����� ���p��������� ��������� ������
  int IsBlockDesc() { return ISBLOCKDESC; }
  int IsBlockDesc(int set) { return (ISBLOCKDESC = set); }

  // �������/��������� ����� ���p��������� ������� ������ ������
  int IsBlockFlags() { return ISBLOCKFLAGS; }
  int IsBlockFlags(int set) { return (ISBLOCKFLAGS = set); }

  // �������/��������� �������� ����� ���p��������� �����
  int IsBorder() { return ISBORDER; }
  int IsBorder(int set) { return (ISBORDER = set); }

  // �������/��������� �������� ����� ���p���������
  int IsMask() { return ISMASK; }                          
  int IsMask(int set) { return (ISMASK = set); }           

  // ������� �������� ����� ���p��������� �������
  int IsPalette() { return ISPALETTE; }

  // ������� �������� ����� ���p��������� ��������������� �������� ������
  int IsAddition() { return ISADDITION; }

  // �������/��������� �������� ����� ���p��������� ���������
  int IsHeader() { return ISHEADER; }
  int IsHeader(int set) { return (ISHEADER = set); }

  // �������/��������� ����� ISCREATE
  int IsCreate() { return ISCREATE; }
  int IsCreate(int set) { return ISCREATE = set; }

  // �������� ������������ ����� .RMF
  // ��� ������ ���������� ���� (��� ������ Error())
  int Verify(long int label);

  // �������� �����
  // ��� ������ ���������� ����
  int Create(const char * name);

public:

  // �������/��������� ����� ������
  long Error() { return ISERROR; }
  long Error(long error) { return (ISERROR = error); }

  // ������ �������� �� ���������� ��������
  // ��� ������ ���������� ����
  int GetPoint(long& value, int string, int column);
  int GetPoint(double& value, int string, int column);

  // ������ �������� �� ���������� ��������
  // ��� ������ ���������� ����
  int PutPoint(long value, int string, int column);
  int PutPoint(double value, int string, int column);

  // ������ �������� �� ��� ������������� �����������
  // (� ������) �� ������
  int GetPlanePoint(long&   value, double x, double y);
  int GetPlanePoint(double& value, double x, double y);

  // ���������� �������� ������ (� ������) ������� �������������
  // �� �������� ���������� ��������
  int GetHeightTriangle(double& height,double Str,double Col);
  int GetHeightTriangle2(double& height,double Str,double Col);

  // ���������� �������� �������� ������� ������������� �� ��������
  // ������������� ����������� (� ������)
  int GetPlanePointTriangle(double& value, double x, double y);

  // ������ ��������  �� ��� ������������� �����������
  // (� ������) � �����
  int PutPlanePoint(long   value, double x, double y);
  int PutPlanePoint(double value, double x, double y);

  // ������ �������� �� ���������� �������� �� �����
  // ��� ������ ���������� ����
  int ReadPoint(long& value, int string, int column);

  // ������ �������� �� ���������� �������� � ����
  // ��� ������ ���������� ����
  int WritePoint(long value, int string, int column);

  // ������ ������� �� ���. �����. ������
  //  x1,y1 - ������,������� ��������� ����� �������
  //  x2,y2 - ������,������� �������� ����� �������
  // ��� ������ ���������� ����
  int PutLine(long value, int x1, int y1, int x2, int y2);

  // ������ ������� �� ������������� ����������� ������ (� ������)
  //  x1,y1 - ���������� ��������� ����� �������
  //  x2,y2 - ���������� �������� ����� �������
  // ��� ������ ���������� ����
  int PutPlaneLine(long value, double x1, double y1, double x2, double y2);
  int PutPlaneLine(double value, double x1, double y1, double x2, double y2);

  // ������ �������������� ������� ������
  //  bits    - ��������� �� ������ ����������� ������� �������
  //  left    - �������� ����� � ��������� (��������� �� ������� �����)
  //  top     - �������� ������ � ���������
  //  width   - ������ � ��������� (��������� �� ������� �����)
  //  height  - ������ � ���������
  // ������� ������������:
  //  ��� ElementSize() == 1 (���) - left,width ������ 8,
  //                    == 4 (���) - left,width ������ 2
  // ��� ������ ���������� 0
  int GetFrame(char* bits, int left, int top, int width, int height,
               int widthinbyte = 0);



  // ������ �������������� ������� ������
  //  bits    - ��������� �� ������ ����������� ������� �������
  //  left    - �������� ����� � ��������� (��������� �� ������� �����)
  //  top     - �������� ������ � ���������
  //  width   - ������ � ��������� (��������� �� ������� �����)
  //  height  - ������ � ���������
  //  begining  - ������ �����������:
  //    == FIRSTLINE - (bits - ��������� �� ������ ������ ������� �������)
  //    == LASTLINE  - (bits - ��������� �� ��������� ������ ������� �������,
  //                           � BMP ����������� �������� ����� - �����)
  // ������� ������������:
  //  ��� ElementSize() == 1 (���) - left,width ������ 8,
  //                    == 4 (���) - left,width ������ 2
  // ��� ������ ���������� 0
  int PutFrame(char* bits, int left, int top, int width, int height,
               int begining = RMFFIRSTLINE, int widthinbyte = 0);


 // ����������� �������������� ������� ��������� ������    
 // � �������������� ������, ������������� � ������� ������.
 //   bits   - ��������� �� ������ ������� ������;
 //   width  - ������ ������� ������ � ��������� COLORREF
 //            (���������� �������� ��������������� ������);
 //   height - ������ ������� ������ � ���������
 //            (���������� ����� ��������������� ������);
 //   strL,colL,strR,colR - ���������� ������ � ������� ���������
 //                         ��������� ������, ������� ����������
 //                         ������� ��������� ������� ��������������
 //                         �������.
 // ��� ������ ���������� ����.
 int GetFrameTurn(COLORREF* bits, int width, int height,
                  double strL, double colL, double strR, double colR);

                  
  // ������ ����� {string,column} �������� "size" �� DID-����� "mask"
  // �������� "color"
  // ��� ������ ���������� ����
  int PutBlockByMask(int string, int column, char* mask, long size,
                         long width,long height,long value);

  // ��������� ���� ���������� �����
  // ��� ������ ���������� ����
  int GetUpdateTime(FILETIME * mtime);

  // ����������� ���������� �-�. �����������
  int IsActive() { return ((int)FILEID); }

  // �������/��������� ������� ����� �����
  char* Name() { return NAME; }
  char* Name(char* name)
  {
    if (name == 0) return 0;
    return strncpy(NAME, name, sizeof(NAME));
  }

  // ������� ��������� �� �������
  COLORREF* Palette() { return PALETTE; }

  // ������� ��������� �� �������������� �������� ������
  RMFADDITION* Addition() { return &ADDITION; }

  // ��������� ����� �������
  //  count - ����� ��������� �� ������� �������
  COLORREF* Palette(COLORREF* palette, int count);

  // ���������/���������� ������� ������� (�� - 16 �� 16)     
  // ��� ������ ���������� 0
  int GetBright()  {return HEADER.Bright;}
  int SetBright(int bright)
     { IsHeader(TRUE);  return (HEADER.Bright = (BYTE)bright); }

  // ���������/���������� ������������� ������� (�� -16 �� 16) 
  // ��� ������ ���������� 0
  int GetContrast() {return HEADER.Contrast;}
  int SetContrast(int contrast)
     { IsHeader(TRUE);  return (HEADER.Contrast = (BYTE)contrast); }

  // ���������/���������� �����-������� (�� -16 �� 16)       
  // ��� ������ ���������� 0
  int GetGamma(){return HEADER.Gamma;}
  int SetGamma(int gamma)
     { IsHeader(TRUE);  return (HEADER.Gamma = (BYTE)gamma); }

//*****************************************************************
//  ������� ��������� � ����������� ����� ���������
//*****************************************************************

  // �������/��������� �������������� �����
  unsigned long Label() { return HEADER.Label; }
  unsigned long Label(unsigned long label)
  {
    IsHeader(TRUE);
    return HEADER.Label=label;
  }

  // �������/��������� ������ ���������
  unsigned long Version() { return (HEADER.Version); }
  unsigned long Version(unsigned long version)
  {
    IsHeader(TRUE);
    return HEADER.Version=version;
  }

  // �������/��������� ����� �����
  unsigned long Length() { return (HEADER.Length); }
  unsigned long Length(unsigned long length)
  {
    IsHeader(TRUE);
    return HEADER.Length=length;
  }

  // �������/��������� �������� �� ��������� ����������� �����
  unsigned long DuplicateOffset() { return (HEADER.DuplicateOffset); }
  unsigned long DuplicateOffset(unsigned long offset)
  {
    IsHeader(TRUE);
    return HEADER.DuplicateOffset=offset;
  }

  // �������/��������� ����������������� ��������������
  unsigned long UserLabel() { return (HEADER.UserLabel); }
  unsigned long UserLabel(unsigned long userlabel)
  {
    IsHeader(TRUE);
    return HEADER.UserLabel=userlabel;
  }

  // �������/��������� ��������� �����
  char* UserName() { return (HEADER.UserName); }
  char* UserName(char* name)
  {
    if (name == 0) return 0;
    IsHeader(1);
    strncpy(HEADER.UserName, name, sizeof(HEADER.UserName));
    return (HEADER.UserName);
  }

  // �������/��������� ������� �������� (���)
  long ElementSize() { return (HEADER.ElementSize); }
  long ElementSize(long size)
  {
    IsHeader(TRUE);
    return HEADER.ElementSize=size;
  }

  // ������� ���������� ������
  long ColorCount() { return (0x01<<HEADER.ElementSize); }

  // �������/��������� ������ �-� �����������
  long Height() { return (HEADER.Height); }
  long Height(long height)
  {
    IsHeader(TRUE);
    return HEADER.Height=height;
  }

  // �������/��������� ������ �-� �����������
  long Width() { return (HEADER.Width); }
  long Width(long width)
  {
    IsHeader(TRUE);
    return HEADER.Width=width;
  }

  // �������/��������� ���������� �������� ������ (������ � ������)
  long BlockColumnCount() { return (HEADER.BlockColumnCount); }
  long BlockColumnCount(long column)
  {
    IsHeader(TRUE);
    return HEADER.BlockColumnCount=column;
  }

  // �������/��������� ���������� ����� ������ (������ � �������)
  long BlockStringCount() { return (HEADER.BlockStringCount); }
  long BlockStringCount(long string)
  {
    IsHeader(TRUE);
    return HEADER.BlockStringCount=string;
  }

  // ������� ���������� ������
  long BlockCount() { return HEADER.BlockColumnCount  *
                             HEADER.BlockStringCount; }

  // �������/��������� ������ �����(�����)
  long BlockHeight() { return (HEADER.BlockHeight); }
  long BlockHeight(long height)
  {
    IsHeader(TRUE);
    return HEADER.BlockHeight=height;
  }

  // �������/��������� ������ �����(��������)
  long BlockWidth() { return (HEADER.BlockWidth); }
  long BlockWidth(long width)
  {
    IsHeader(TRUE);
    return HEADER.BlockWidth=width;
  }

  // �������/��������� ������ ��������� �����
  long CutBlockHeight() { return (HEADER.TruncBlockHeight); }
  long CutBlockHeight(long height)
  {
    IsHeader(TRUE);
    return HEADER.TruncBlockHeight=height;
  }

  // �������/��������� ������ ��������� �����
  long CutBlockWidth() { return (HEADER.TruncBlockWidth); }
  long CutBlockWidth(long width)
  {
    IsHeader(TRUE);
    return HEADER.TruncBlockWidth=width;
  }

  // ����������� ������ �������� �����
  long CurrentBlockHeight(int string)
  {
    if (string == BlockStringCount()-1) return CutBlockHeight();
                                   else return BlockHeight();
  }

  // ����������� ������ �������� �����
  long CurrentBlockWidth(int column)
  {
    if (column == BlockColumnCount()-1) return CutBlockWidth();
                                   else return BlockWidth();
  }

  // ����������� ������� ����� (����)
  long BlockSize() { return (HEADER.BlockHeight *
                             HEADER.BlockWidth  *
                             HEADER.ElementSize / 8); }

  // ����������� ������� �������� ����� (����)
  long CurrentBlockSize(int string, int column)
  {
    return (CurrentBlockHeight(string) *
            CurrentBlockWidth(column) * HEADER.ElementSize / 8);
  }

  // �������/��������� �������� �� ������ "�����" � �����
  unsigned long BorderOffset() { return (HEADER.BorderOffset); }
  unsigned long BorderOffset(unsigned long borderoffset)
  {
    IsHeader(TRUE);
    IsBorder(TRUE);
    return HEADER.BorderOffset=borderoffset;
  }

  // �������/��������� ����� ������ "�����"
  long BorderLength() { return (HEADER.BorderLength); }
  long BorderLength(long borderlength)
  {
    IsHeader(TRUE);
    IsBorder(TRUE);
    return HEADER.BorderLength = borderlength;
  }

  // �������/��������� ����� ����������� �� �����
  int ShowByBorder();
  int ShowByBorder(int value);

  // �������/��������� �������� �� ������ "" � �����             
  unsigned long MaskOffset() { return (ADDITION.MaskOffset); }   
  unsigned long MaskOffset(unsigned long maskoffset)           
  {
    IsHeader(TRUE);
    IsAddition(TRUE);
    IsMask(TRUE);
    return ADDITION.MaskOffset=maskoffset;
  }

  // �������/��������� ����� ������ ""                            
  long MaskLength() { return (ADDITION.MaskLength); }             
  long MaskLength(long masklength)                              
  {
    IsHeader(TRUE);
    IsAddition(TRUE);
    IsMask(TRUE);
    return ADDITION.MaskLength = masklength;
  }

  // �������/��������� ����� ����������� ��                       
  int ShowByMask();
  int ShowByMask(int value);

  // �������/��������� �������� �� ������� � �����
  unsigned long PaletteOffset() { return (HEADER.PaletteOffset); }
  unsigned long PaletteOffset(unsigned long paletteoffset)
  {
    IsHeader(TRUE);
    IsPalette(TRUE);
    return HEADER.PaletteOffset = paletteoffset;
  }

  // �������/��������� ����� �������
  long PaletteLength() { return (HEADER.PaletteLength); }
  long PaletteLength(long palettelength)
  {
    IsHeader(TRUE);
    IsPalette(TRUE);
    return HEADER.PaletteLength = palettelength;
  }

  // �������/��������� �������� �� ������ "�������������e �������e ������" � �����
  unsigned long AdditionOffset() { return (HEADER.AdditionOffset); }
  unsigned long AdditionOffset(unsigned long additionoffset)
  {
    IsHeader(TRUE);
    IsAddition(TRUE);
    return HEADER.AdditionOffset = additionoffset;
  }

  // �������/��������� ����� ������ "�������������e �������e ������"
  long AdditionLength() { return (HEADER.AdditionLength); }
  long AdditionLength(long addlength)
  {
    IsHeader(TRUE);
    IsAddition(TRUE);
    return HEADER.AdditionLength = addlength;
  }

  // �������/��������� �������� �� ������ "��������� ������" � �����
  unsigned long BlockDescOffset() { return (HEADER.BlockDescOffset); }
  unsigned long BlockDescOffset(unsigned long blockdescoffset)
  {
    IsHeader(TRUE);
    IsBlockDesc(TRUE);
    return HEADER.BlockDescOffset = blockdescoffset;
  }

  // �������/��������� ����� ������ "��������� ������"
  long BlockDescLength() { return (HEADER.BlockDescLength); }
  long BlockDescLength(long blockdesclength)
  {
    IsHeader(TRUE);
    IsBlockDesc(TRUE);
    return HEADER.BlockDescLength = blockdesclength;
  }

  // �������/��������� �������� �� ������ "������� ������ ������" � �����
  unsigned long BlockFlagsOffset() { return (HEADER.BlockFlagsOffset); }
  unsigned long BlockFlagsOffset(unsigned long blockflagsoffset)
  {
    IsHeader(TRUE);
    IsBlockFlags(TRUE);
    return HEADER.BlockFlagsOffset = blockflagsoffset;
  }

  // �������/��������� ����� ������ "������� ������ ������"
  long BlockFlagsLength() { return (HEADER.BlockFlagsLength); }
  long BlockFlagsLength(long blockflagslength)
  {
    IsHeader(TRUE);
    IsBlockFlags(TRUE);
    return HEADER.BlockFlagsLength = blockflagslength;
  }

  // �������/��������� �������� �� ��������� ������ � �����
  unsigned long CompressDataOffset() { return (HEADER.CompressDataOffset); }
  unsigned long CompressDataOffset(unsigned long offset)
  {
    IsHeader(TRUE);
    return HEADER.CompressDataOffset = offset;
  }

  // �������/��������� ���������� ���������� ������
  long CompressDataCount() { return HEADER.CompressDataCount; }
  long CompressDataCount(long count)
  {
    IsHeader(TRUE);
    return HEADER.CompressDataCount = count;
  }

  // �������/��������� ����� ������ "��������� ������"
  long CompressDataLength() { return HEADER.CompressDataLength; }
  long CompressDataLength(long length)
  {
    IsHeader(TRUE);
    return HEADER.CompressDataLength = length;
  }

  // �������/��������� ���� �����
  long MapType() { return HEADER.MapType; }
  long MapType(long maptype)
  {
    IsHeader(TRUE);
    return HEADER.MapType = maptype;
  }

  // �������/��������� ���� ��������
  long ProjectionType() { return HEADER.ProjectionType; }
  long ProjectionType(long projectiontype)
  {
    IsHeader(TRUE);
    return HEADER.ProjectionType = projectiontype;
  }

  // �������/��������� ���� ����������                      
  long EllipsoideKind();
  long EllipsoideKind(long ellipsoidekind);

  // �������/��������� ������� �����                        
  long HeightSystem();
  long HeightSystem(long heightsystem);

  // �������/��������� ������� ���������                    
  long CoordinateSystem();
  long CoordinateSystem(long coordinatesystem);

  // �������/��������� ������ ����                           
  long ZoneNumber();
  long ZoneNumber(long zonenumber);

  // ��������� �������� ��������� ��������� �
  // ����� ����������� ������� ������������� ���������
  // �� ������ ��������� rmfdata->HEADER
  long SetProjection();  

  // ������ �������� ��������� ���������             
  // ���� ���� ����������� ������� ������������� ��������� ����� ����,
  // �� ��� ������ �������� �-�
  // �� ������ ��������� MAPREGISTEREX
  long GetRegister(MAPREGISTEREX* mapregister);  
  // ��������� �������� ��������� ��������� �
  // ����� ����������� ������� ������������� ���������
  // �� ������ ��������� MAPREGISTEREX
  long SetRegister(MAPREGISTEREX* mapregister);  

  // �������/��������� ��������
  double Scale() { return max(1.0, HEADER.Scale); }
  double Scale(double scale)
  {
    IsHeader(TRUE);
    return HEADER.Scale = max(1.0, scale);
  }

  // �������/��������� ���������� ��������� �� ����
  double Precision() { return max(1.0, HEADER.Precision); }
  double Precision(double precision)
  {
    IsHeader(TRUE);
    return HEADER.Precision = max(1.0, precision);
  }

  // �������/��������� ���������� ������ �� �������
  double MeterInElement() { return (HEADER.MeterInElement); }
  double MeterInElement(double meterinelement)
  {
    IsHeader(TRUE);
    return (HEADER.MeterInElement=meterinelement);
  }

  // ����������� ����� �������� � ������ � ������
  // (��� RSW ������ <= 0x0101 - � ���������)
  double LocationX() { return HEADER.LocationX; }
  double LocationY() { return HEADER.LocationY; }

  // ��������� ����� �������� ����������� � ������ � ������
  double LocationX(double location)
  {
    IsHeader(TRUE);
    HEADER.Flag_Location = 1;
    return HEADER.LocationX=location;
  }

  double LocationY(double location)
  {
    IsHeader(TRUE);
    HEADER.Flag_Location = 1;
    return HEADER.LocationY=location;
  }

  // ������������� ���������� ����� � ������
  // (��� RSW ������ <= 0x0101 - ����������� !!!)
  double X1() { return HEADER.LocationX; }
  double Y1() { return HEADER.LocationY; }
  double X2() { return HEADER.LocationX + (double)(HEADER.Height) *
                       HEADER.MeterInElement; }
  double Y2() { return HEADER.LocationY + (double)(HEADER.Width) *
                       HEADER.MeterInElement; }

  // �������/��������� ������ ������� ���������
  double FirstMainParallel() { return (HEADER.FirstMainParallel); }
  double FirstMainParallel(double mainparallel)
  {
    IsHeader(TRUE);
    return (HEADER.FirstMainParallel=mainparallel);
  }

  // �������/��������� ������ ������� ���������
  double SecondMainParallel() { return (HEADER.SecondMainParallel); }
  double SecondMainParallel(double mainparallel)
  {
    IsHeader(TRUE);
    return (HEADER.SecondMainParallel=mainparallel);
  }

  // �������/��������� ������� ���������
  double AxisMeridian() { return (HEADER.AxisMeridian); }
  double AxisMeridian(double meridian)
  {
    IsHeader(TRUE);
    return (HEADER.AxisMeridian=meridian);
  }

  // �������/��������� ��������� ������� �����
  double MainPointParallel() { return (HEADER.MainPointParallel); }
  double MainPointParallel(double mainpoint)
  {
    IsHeader(TRUE);
    return (HEADER.MainPointParallel=mainpoint);
  }

  // �������/��������� ������ ������ ��������                 
  double PoleLatitude() { return (ADDITION.PoleLatitude); }
  double PoleLatitude(double polelatitude)
  {
    // ��������� ����� ������������ ��������������� �������� ������
    IsAddition(TRUE);
    return (ADDITION.PoleLatitude=polelatitude);
  }

  // �������/��������� ������� ������ ��������                 
  double PoleLongitude() { return (ADDITION.PoleLongitude); }
  double PoleLongitude(double polelongitude)
  {
    IsAddition(TRUE);
    return (ADDITION.PoleLongitude=polelongitude);
  }

  // �������/��������� ������ ��������� ������ ������
  int CompressNumber() { return (HEADER.CompressNumber); }
  int CompressNumber(int number)
  {
    IsHeader(TRUE);
    return (HEADER.CompressNumber = (unsigned char)number);
  }

  // �������/��������� ���� ����� (0 - ����� �����������)
  int MaskType() {return HEADER.MaskType;}
  int MaskType(int type)
  {
    IsHeader(TRUE);
    return (HEADER.MaskType = (unsigned char)type);
  }

  // �������/��������� ���� �����
  int MaskStep() {return HEADER.MaskStep;}
  int MaskStep(int step)
  {
    IsHeader(TRUE);
    return (HEADER.MaskStep = (unsigned char)step);
  }

  // ��������� ���� � ���� �����
  void SetMask(int type, int step)
  {
    IsHeader(TRUE);
    HEADER.MaskType = (unsigned char)type;
    HEADER.MaskStep = (unsigned char)step;
  }

  // �������/��������� ��������� ������� �������� ��������� ������
  //          (��� 16 � 256-������� �������)
  //  bytes - ������ �������� (1 - ���� �������, 0 - ���� �����)
  //  size  - ������ �������
  // ���������� ����� ��������� ������
  int GetInvisibleColors(unsigned char* bytes, int size);
  int SetInvisibleColors(unsigned char* bytes, int size);

  // �������/��������� ��������� ������� �������� ������� ������
  //          (��� 16 � 256-������� �������)
  //  bytes - ������ �������� (1 - ���� �����, 0 - ���� �������)
  //  size  - ������ �������
  // ���������� ����� ��������� ������
  int GetVisibleColors(unsigned char* bytes, int size);
  int SetVisibleColors(unsigned char* bytes, int size);

  // �������/��������� �������� ������� �������� ��������� ������
  unsigned char* InvisibleColorsBits() { return HEADER.InvisibleColors; }
  unsigned char* InvisibleColorsBits(unsigned char* bits)
  {
    if (bits == 0) return 0;
    IsHeader(TRUE);
    memcpy(HEADER.InvisibleColors, bits, 32);
    return HEADER.InvisibleColors;
  }

  // �������/��������� ����� �������������� �����������
  // 0 - ����������� ����������
  // 1 - ����������� ����������
  int Negative() { return (HEADER.Flag_Negative); }
  int Negative(int number)
  {
    IsHeader(TRUE);
    return (HEADER.Flag_Negative = (unsigned char)number);
  }

  // �������/��������� ������������ �������� ��������(��� �������)
  double Minimum() { return (HEADER.Minimum); }
  double Minimum(double minimum)
  {
    IsHeader(TRUE);
    return (HEADER.Minimum=minimum);
  }

  // �������/��������� ������������� �������� ��������(��� �������)
  double Maximum() { return (HEADER.Maximum); }
  double Maximum(double maximum)
  {
    IsHeader(TRUE);
    return (HEADER.Maximum=maximum);
  }

  // �������/��������� �������� ����������(��� �������)
  double PseudoCode() { return (HEADER.PseudoCode); }
  double PseudoCode(double pseudocode)
  {
    IsHeader(TRUE);
    return (HEADER.PseudoCode=pseudocode);
  }


  // �������/��������� ������� ��������� (��� �������)
  unsigned long Measure() { return (HEADER.Measure); }
  unsigned long Measure(unsigned long measure);

  // �������/��������� ���� �������
  unsigned char MtrType() { return HEADER.MtrType; }
  unsigned char MtrType(unsigned char mtrtype)
  {
    IsHeader(TRUE);
    return HEADER.MtrType = mtrtype;
  }

  // �������/��������� ������ ���������� �����������        
  unsigned char Method() { return HEADER.Method; }
  unsigned char Method(unsigned char method)
  {
    IsHeader(TRUE);
    return HEADER.Method = method;
  }

  // �������/��������� ����� "������ ��� ���������"         
  unsigned char HeightSuper() { return HEADER.HeightSuper; }
  unsigned char HeightSuper(unsigned char heightsuper)
  {
    IsHeader(TRUE);
    return HEADER.HeightSuper = heightsuper;
  }

  // �������/��������� ����� ������������ ��������� �����������  
  unsigned char Extremum() { return HEADER.Extremum; }
  unsigned char Extremum(unsigned char extremum)
  {
    IsHeader(TRUE);
    return HEADER.Extremum = extremum;
  }

  // ��������� ������� ���������� ����� �� �����
  // ��� ������ ���������� ����
  int DiskFreeSpace(char* name);

  // ����������� ����������� ����� �����
  // ��� ������ ���������� ����
  unsigned long FileLength();

  // ����������� ����e�������� ����� �����
  // ������������ �� �������� �������
  // ��� ������ ���������� ����
  double CalculationFileLength(int width, int height, int bitpixel);

  // ����������� ������� ������ � �����
  inline double HeightUnitToMeter(double unit)
  {
    return unit*HeightMeterInUnit;
  }

  // ����������� ����� � ������� ������
  inline double HeightMeterToUnit(double meter)
  {
    return meter*HeightUnitInMeter;
  }


//*****************************************************************
// ������� ��������� � ����������� �����
// ��������������� �������� ������ ( ������� )
//*****************************************************************

  // �������/��������� ������ ��������� ����� (� �������� �������)
  double AbsHeightDifference() { return ADDITION.AbsHeightDifference; }
  double AbsHeightDifference(double difference)
  {
    IsAddition(TRUE);
    return (ADDITION.AbsHeightDifference = difference);
  }

  
//*****************************************************************
//  ������� ��� ������ � ������
//*****************************************************************

public:

  // ������ ����� {string,column} �������� size � ������ bits.
  // ���������� ���������� ����������� ����.
  // ��� ������ ���������� ����.
  int ReadBlock(int string, int column, char* bits, int size);

  // ������ ����� {string,column} �������� size �� ������ bits.
  // ���������� ���������� ���������� ����.
  // ��� ������ ���������� ����.
  int WriteBlock(int string, int column, char* bits, int size);

  // ������ ����� ������ {string,column}
  // ��� ������ ���������� ����.
  int SaveBlock(int string, int column);

protected:

  // ������ ����� {string,column} �� ������ "Part[iCur].addr"
  int ReadBlock(int string, int column);

  // ������ ����� {string,column} �� ������� "Part[iCur].addr"
  int WriteBlock(int partindex);

  // ������ ��������� �� �����
  // ��� ������ ���������� ����
  int ReadHeader();

  // ������ ��������� � ����
  // ��� ������ ���������� ����
  int WriteHeader();

  // ������ ������� �� �����
  // ��� ������ ���������� ����
  int ReadPalette();

  // ������ ������� � ����
  // ��� ������ ���������� ����
  int WritePalette();

  // ������ ��������������� �������� ������ �� �����
  // ��� ������ ���������� ����
  int ReadAddition();

  // ������ ��������������� �������� ������ � ����
  // ��� ������ ���������� ����
  int WriteAddition();

  // ������ ��������� ������ �� ����� � �����
  // ��� ������ ���������� ����
  int ReadBlockDesc();

  // ������ ��������� ������ � ���� �� ������
  // ��� ������ ���������� ����
  int WriteBlockDesc();

  // ������ ������� ������ ������ �� ����� � �����
  // ��� ������ ���������� ����
  int ReadBlockFlags();

  // ������ ������� ������ ������ � ���� �� ������
  // ��� ������ ���������� ����
  int WriteBlockFlags();

  // ������ ����� �� �����
  // ��� ������ ���������� ����
  int ReadBorder();

  // ������ ����� � ����
  // ��� ������ ���������� ����
  int WriteBorder();

  // ������ ����� �� �����       
  // ��� ������ ���������� ����
  int ReadMask();

  // ������ ����� � ����         
  // ��� ������ ���������� ����
  int WriteMask();

public:

  // ����������� �������������� ����� ������
  friend int operator == (const RMFELEMENT& point, const RMFBLOCK& block)
  {
    if( (point.Col >= block.Begin.Col) && (point.Col <= block.End.Col) &&
        (point.Str >= block.Begin.Str) && (point.Str <= block.End.Str) )
         return TRUE;
    else return FALSE;
  }

  friend int operator != (const RMFELEMENT& point, const RMFBLOCK& block)
  {
	  if( (point.Col >= block.Begin.Col) && (point.Col <= block.End.Col) &&
        (point.Str >= block.Begin.Str) && (point.Str <= block.End.Str) )
         return FALSE;
    else return TRUE;
  }

};


//-----------------------------------------------------------------
// ����������� �������� �� ���� � �����
//-----------------------------------------------------------------
inline unsigned long TRmf::BlockOffset(int index)
{
  if (BLOCKDESCBUFF == 0)
  {
    Error(IDS_STRUCT);
    return 0;
  }

  if (index < 0  ||  index >= BlockCount())
  {
    Error(IDS_STRUCT);
    return 0;
  }

  // �������� � ����� ����� ������� �� ��������� ������ BlockDesc
  return (BLOCKDESCBUFF+index)->Offset;
}

//-----------------------------------------------------------------
// ��������� �������� �� ���� � �����
//-----------------------------------------------------------------
inline unsigned long TRmf::BlockOffset(int index, unsigned long offset)
{
  if (BLOCKDESCBUFF == 0)
  {
    Error(IDS_STRUCT);
    return 0;
  }

  if (index < 0  ||  index >= BlockCount())
  {
    Error(IDS_STRUCT);
    return 0;
  }

  IsBlockDesc(1);  // ��������� ��������� ������
  IsHeader(1);     // ���������� ����� �����

  // �������� � ����� ����� ������� �� ��������� ������ BlockDesc
  return (BLOCKDESCBUFF+index)->Offset = offset;
}

//-----------------------------------------------------------------
// ����������� ����� �����
//-----------------------------------------------------------------
inline long TRmf::BlockLength(int index)
{
  if (BLOCKDESCBUFF == 0)
  {
    Error(IDS_STRUCT);
    return 0;
  }

  if (index < 0  ||  index >= BlockCount())
  {
    Error(IDS_STRUCT);
    return 0;
  }

  // �������� � ����� ����� ������� �� ��������� ������ BlockDesc
  return (BLOCKDESCBUFF+index)->Length;
}

//-----------------------------------------------------------------
// ��������� ����� �����
//-----------------------------------------------------------------
inline long TRmf::BlockLength(int index, long length)
{
  if (BLOCKDESCBUFF == 0)
  {
    Error(IDS_STRUCT);
    return 0;
  }

  if (index < 0  ||  index >= BlockCount())
  {
    Error(IDS_STRUCT);
    return 0;
  }

  IsBlockDesc(1);  // ��������� ��������� ������
  IsHeader(1);     // ���������� ����� �����

  // �������� � ����� ����� ������� �� ��������� ������ BlockDesc
  return (BLOCKDESCBUFF+index)->Length = length;
}

//-----------------------------------------------------------------
// ������� ����� ����������� �����
//-----------------------------------------------------------------
inline int TRmf::BlockVisible(int index)
{
  if (BLOCKFLAGSBUFF == 0)  // ���� ������� ��� - ����� ��� !
  {
    return 1;
  }

  if (index < 0  ||  index >= BlockCount())
  {
    Error(IDS_STRUCT);
    return 0;
  }

  return *(BLOCKFLAGSBUFF+index);
}

//-----------------------------------------------------------------
// ��������� ����� ����������� �����
//-----------------------------------------------------------------
inline int TRmf::BlockVisible(int index, int view)
{
  if (BLOCKFLAGSBUFF == 0) return 0;

  if (index < 0  ||  index >= BlockCount())
  {
    Error(IDS_STRUCT);
    return 0;
  }

  IsBlockFlags(1);  // ��������� ������ ������ ������
  IsHeader(1);      // ���������� ����� �����

  return *(BLOCKFLAGSBUFF+index) = (char)view;
}

#endif   // RMFBASE_H


