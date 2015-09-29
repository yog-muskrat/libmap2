
#ifndef RSTBASE_H
#define RSTBASE_H

#ifndef RMFBASE_H
  #include "rmfbase.h"
#endif

#ifndef RST_H
  #include "rst.h"
#endif

//******************************************
//   ������� ����� ���������� �����������
//******************************************
class _DLLCLASS TRst : public  TRmf
{
  public:

  TRst();                                       // ����������� (������)
  TRst(char* name, int mode = 0);               // �����������
  TRst(char * name, int width, int height, int bit, COLORREF* palette = 0,
       double scale=0, double precision=0);

  // ����������� ����������� ����� ������������� �����
  TRst(HANDLE fileid, unsigned long headeroffset);
  ~TRst();

//****************************************************
// ����-������� ������ TRst:
//****************************************************

public:

  // �������� �����
  // ��� ������ ���������� ����
  int Create(char * name,long width, long height,
             long nbits, COLORREF* palette,
             double scale=0, double precision=0);

  // �������� �����
  // ��� ������ ���������� ����
  int Open(char *name, int mode = 0);

  // �������� �����
  void Close();

  // ����������� ����� ��������������� �������� ������
  int Location() {return (int)HEADER.Flag_Location;}

  // ��������� ����� ��������������� �������� ������
  void Location(int set){HEADER.Flag_Location = (unsigned char)set;}

  // ����������� ����� �������� � ������ � ������
  // (��� RST ������ <= 0x0101 - � ���������)
  double LocationX() { return HEADER.LocationX; }
  double LocationY() { return HEADER.LocationY; }

  // ��������� ����� �������� ����������� � ������ � ������
  double LocationX(double location);
  double LocationY(double location);

  // ����������� ��������
  double Scale() {return TRmf::Scale();}

  // ��������� ��������
  double Scale(double scale);

  // ����������� ���������� ��������� �� ����
  double Precision() {return TRmf::Precision();}

  // ��������� ���������� ��������� �� ����
  double Precision(double precision);

  // ����������� ����� �������������� �����������
  // 0 - ����������� ����������
  // 1 - ����������� ����������
  int Negative() { return TRmf::Negative();  }

  // ��������� ����� �������������� �����������
  int Negative(int number);

  // ��������� �����
  int SetBorder(TDataEdit* data);

  // �����������/��������� ����� ����������� �� �����
  int ShowByBorder() {return TRmf::ShowByBorder();}
  int ShowByBorder(int value);

  // ��������� �����  
  int SetMask(TDataEdit* data);

  // �����������/��������� ����� ����������� �� �����     
  int ShowByMask() {return TRmf::ShowByMask();}
  int ShowByMask(int value);

  // ������� �����
  int DeleteBorder();

  // ������ ����� {string,column} �������� "size" �� ������ "bits"
  // ���������� ���������� ���������� ����
  // ��� ������ ���������� ����
  int WriteBlock(int string, int column, char* bits, int size);

  // ������ ����� {string,column} �������� "size" �� DID-����� "mask"
  // �������� "color"
  // ��� ������ ���������� ����
  int PutBlockByMask(int string, int column, char* mask, long size,
                         long width,long height,long value);

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

  // ������ �������� ���������� �������������� ������� ������
  //  bitsR,bitsG - ��������� �� ������ ����������� �������� ��������
  //  bitsB         �������, ������� � ����� ���������
  //  left    - �������� ����� � ���������
  //  top     - �������� ������ � ���������
  //  width   - ������ � ���������
  //  height  - ������ � ���������
  //  ������������ ������ 8-������ ������ (����)
  // ��� ������ ���������� 0
  int GetFrameRGB(char* bitsR, char* bitsG, char* bitsB,       
                  int left, int top, int width, int height);

  // �������� ������� ����������� ����� �� i,j ����� ��������� ������
  // ������ �������� ��������� ������ - 8 ��� �� ������
  // ��� ������ ���������� ����
  int UpdateDuplicateAsBlock256(int string, int column);

  // �������� ������� ����������� ����� �� �����(string,column) ��������� ������
  // ��� ������ ���������� ����
  int UpdateDuplicateAsBlock(int string, int column);

  // �������� ����������� �����
  // ���� number = 0, �������� ��� ����������� �����
  // ���������� ����� �� ������ 3 (number <= 3)
  // ���� ����������� ����� �� ����������, ��������� ���� �����
  int UpdateDuplicates(int number = 0);

  // ���������� ��������� �� ����� TRst ��� ����������� ��������� �����������
  // ��� TRstDuplicate ��� ����������� ����������� �����
  TRmf & GetRstClass(int duplicate);  

  // ��� ������� ����� ���������� ��������� �� ����� TRstDuplicate,
  // ����� - ��������� �� ����� TRst ��������� �����������
  // number - ����� �����(������� � 1)
  TRst & GetRstDuplicate();

  // ������� ����������� ����� ������
  // number - ����� �����(������� � 1)
  // ��� �������� ���������� ������� ������ ����������� ����� Duplicate,
  // ������� ��������� � ����� ����������� ����� � ������� � ����.
  // Duplicate ���������������� ���������� � ������� ��������� ����������� �����
  // ��� ������ :
  //   ���������� ����,
  //   �������� �� ����������� ����� � �������� ������ ��������������� � ����,
  //   ������ Duplicate ��������� � ��������������� � ����.
  int CreateDuplicate(int number);

  // ������� ��������� ����������� ����� ������
  // number - ����� �����(������� � 1)
  // ��� �������� ���������� ��������� ������ ����������� ����� Duplicate,
  // ��������� ��������� ����������� ����� � ������� � ����.
  // Duplicate ���������������� ���������� ��������� ����������� �����
  // ��� ������ ���������� ����
  int CreateDuplicate(int number,
                      long width, long height,
                      long elementSize,
                      double scale, double precision,
                      DOUBLEPOINT location);

  // ������� ����������� ������� ����������� ���� Duplicate ������ c 8 �\�
  // (Duplicate ������ ��������� ��������� ����������� �����)
  // divisor - �������� ����������� ���������� ��������� ������
  // ��� ������ :
  //   ���������� ����,
  //   �������� �� ����������� ����� � �������� ������ ��������������� � ����,
  //   ������ Duplicate ��������� � ��������������� � ����.
  int CreateDuplicateImage256(int divisor);

  // ������� ����������� ������� ����������� ���� Duplicate ������
  // (Duplicate ������ ��������� ��������� ����������� �����)
  // divisor - �������� ����������� ���������� ��������� ������
  // ��� ������ :
  //   ���������� ����,
  //   �������� �� ����������� ����� � �������� ������ ��������������� � ����,
  //   ������ Duplicate ��������� � ��������������� � ����.
  int CreateDuplicateImage(int divisor);

  // ��������� ������ ����������� ����� � ����e
  // ���������������� ����� ��������� (����� �����, �������,
  // ����������� �����������, ��������) ��������� ����������� �
  // ����������� ����������� �����
  // ��� ������ ���������� ����
  int SaveDuplicates(int force);

protected :

  // ������ ��������� �� ����� ������� ������� (RST/MTR)
  int ReadOldHeader(RST * header);

  // ���������������� ��������� ������ �������
  // ����������� �������,�����,��������� ������
  int InitializeNewHeader(RST * header);

  // �������� ���������,�����,��������� ������
  // ����� ��������� � ����� �����
  int WriteNewHeaderToFileEnd(RST * header);

private :

  // ��������� ��������� � ��. ��������� ��������� �����������
  // ����� ������ �� �������� headeroffset �� ������ ����� ������
  int ReadDuplicate(unsigned long headeroffset);

  // �������� ��������� ����������� ����� ������ � ������� � ����
  // headeroffset - �������� ������������ ������ ����� �� ���������
  //                ����������� �����
  // offsetFactor - ��� ������� ������ (> 4Gb) �.�. ����� 8, ����� 0
  // ��� ������ ���������� 0
  int CreateDuplicateHeader(unsigned long headeroffset,
                            long width, long height,
                            long elementSize,
                            double scale, double precision,
                            DOUBLEPOINT location, int offsetFactor);
};

typedef TRmf TRSTDATA;

// �������� �����
// ��� ������ ����������
int _fastcall rstCreate(TRSTDATA *rstdata, const char * name, long width,
                        long height, long nbits, COLORREF* palette,
                        double scale, double precision);

// �������� �����
// ��� ������ ���������� ����
// ��� �������� ���������� ���������� RMFOKEY
int _fastcall rstOpen(TRSTDATA *rstdata, const char* name, int mode);

// ������ ��������� �� ����� ������� ������� (RST)
// ���������������� ��������� ������ �������
// ����������� �������,�����,��������� ������
// ��� ������ ���������� ����
int _fastcall rstReadOldHeader(TRSTDATA *rstdata, RST * header);

// ���������������� ��������� ������ �������
// ����������� �������,�����,��������� ������
// ��� ������ ���������� ����
int _fastcall rstInitializeNewHeader(TRSTDATA *rstdata, RST * header);

// �������� ��������� ����� ��������� � ����� �����
// ��� ������ ���������� ����
int _fastcall rstWriteNewHeaderToFileEnd(TRSTDATA *rstdata, RST * header);

// �������� �����
void _fastcall rstClose(TRSTDATA *rstdata);

// ��������� ����� �������� ����������� � ������ � ������
double _fastcall rstLocationX(TRSTDATA *rstdata, double location);

// ��������� ����� �������� ����������� � ������ � ������
double _fastcall rstLocationY(TRSTDATA *rstdata, double location);

// ��������� ��������
double _fastcall rstScale(TRSTDATA *rstdata, double scale);

// ��������� ���������� ��������� �� ����
double _fastcall rstPrecision(TRSTDATA *rstdata, double precision);

// ��������� ����� �������������� �����������
int _fastcall rstNegative(TRSTDATA *rstdata, int number);

// ���������� �����
int _fastcall rstSetBorder(TRSTDATA *rstdata, DATAEDIT* data);  

// ���������� �����  
int _fastcall rstSetMask(TRSTDATA *rstdata, DATAEDIT* data);  

// ��������� ����� ����������� �� �����
int _fastcall rstPutShowByBorder(TRSTDATA *rstdata, int value);

// ��������� ����� ����������� �� �����
#define rstGetShowByBorder  rmfGetShowByBorder

// ��������� ����� ����������� �� �����    
int _fastcall rstPutShowByMask(TRSTDATA *rstdata, int value);

// ������ ����� ����������� �� �����       
#define rstGetShowByMask  rmfGetShowByMask

// ������� �����
int _fastcall rstDeleteBorder(TRSTDATA *rstdata);

// ������ ����� {string,column} �������� "size" �� ������ "bits"
// ���������� ���������� ���������� ����
// ��� ������ ���������� ����
int _fastcall rstWriteBlock(TRSTDATA *rstdata, 
                            int string, int column, char* bits, int size);

// ������ ����� {string,column} �������� "size" �� DID-����� "mask"
// �������� "color"
// ��� ������ ���������� ����
int _fastcall rstPutBlockByMask(TRSTDATA *rstdata, 
                                int string, int column, char* mask, long size,
                                long width,long height,long value);

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
//  ��� rstdata->RmfData.RmfData.HEADER.ElementSize == 1 (���) - left,width ������ 8,
//                    == 4 (���) - left,width ������ 2
// ��� ������ ���������� 0
int _fastcall rstPutFrame(TRSTDATA *rstdata, char* bits,
                          int left, int top, int width, int height,
                          int begining, int widthinbyte);

//-----------------------------------------------------------------
// ������ �������� ���������� �������������� ������� ������
//  bitsR,bitsG - ��������� �� ������ ����������� �������� ��������
//  bitsB         �������, ������� � ����� ���������
//  left    - �������� ����� � ���������
//  top     - �������� ������ � ���������
//  width   - ������ � ���������
//  height  - ������ � ���������
//  ������������ ������ 8-������ ������ (����)
// ��� ������ ���������� 0
//-----------------------------------------------------------------
int _fastcall rstGetFrameRGB(TRMFDATA *rstdata,
                             char* bitsR, char* bitsG, char* bitsB,
                             int left, int top, int width, int height);

// ���������� ��������� �� ��������� TRSTDATA ��� �����������
// ��������� ����������� ��� TRSTDUPLICATE ��� �����������
// ����������� �����
TRmf * _fastcall rstGetRstClass(TRmf * rstdata, int duplicate);


// ��� ������� ����� ���������� ��������� �� ����� TRstDuplicate,
// ����� - ��������� �� ����� TRst ��������� �����������
TRst * _fastcall rstGetRstDuplicate(TRst *rstdata);

// ������� ����������� ����� ������
// number - ����� �����(������� � 1)
// ��� �������� ���������� ������� ������ ����������� ����� rstdata->Duplicate,
// ������� ��������� � ����� ����������� ����� � ������� � ����.
// rstdata->Duplicate ���������������� ���������� � ������� ��������� ����������� �����
// ��� ������ :
//   ���������� ����,
//   �������� �� ����������� ����� � �������� ������ ��������������� � ����,
//   ������ rstdata->Duplicate ��������� � ��������������� � ����.
int _fastcall rstCreateDuplicate(TRSTDATA *rstdata, int number);

// ������� ��������� ����������� ����� ������
// number - ����� �����(������� � 1)
// ��� �������� ���������� ������� ������ ����������� ����� rstdata->Duplicate,
// ������� ��������� ����������� ����� � ������� � ����.
// rstdata->Duplicate ���������������� ���������� ��������� ����������� �����
// ��� ������ ���������� ����
int _fastcall rstCreateDuplicateCopyHeader(TRSTDATA *rstdata, int number,
                                           long width, long height,
                                           long elementSize,
                                           double scale, double precision,
                                           DOUBLEPOINT location);

// �������� ������� ����������� ����� �� i,j ����� ��������� ������
// ������ �������� ��������� ������ - 8 ��� �� ������
// ��� ������ ���������� ����
int _fastcall rstUpdateDuplicateAsBlock256(TRSTDATA *rstdata, 
                                           int string, int column);

// �������� ������� ����������� ����� �� i,j ����� ��������� ������
// ��� ������ ���������� ����
int _fastcall rstUpdateDuplicateAsBlock(TRSTDATA *rstdata,
                                        int string, int column);

// ��������� ������ ����������� ����� � ����e
// ���������������� ����� ��������� (����� �����, �������,
// ����������� �����������, ��������) ��������� ����������� �
// ����������� ����������� �����
// ��� ������ ���������� ����
int _fastcall rstSaveDuplicates(TRSTDATA *rstdata, int force);

// �������� ����������� �����
// ���� number = 0, �������� ��� ����������� �����
// ���������� ����� �� ������ MAX_DUPLICATECOUNT (number <= MAX_DUPLICATECOUNT)
// ���� ����������� ����� �� ����������, ��������� ���� �����
int _fastcall rstUpdateDuplicates(TRSTDATA *rstdata, int number);

// ������� ����������� ������� ����������� ���� rstdata->Duplicate ������ c 8 �\�
// (rstdata->Duplicate ������ ��������� ��������� ����������� �����)
// divisor - �������� ����������� ���������� ��������� ������
// ��� ������ :
//   ���������� ����,
//   �������� �� ����������� ����� � �������� ������ ��������������� � ����,
//   ������ rstdata->Duplicate ��������� � ��������������� � ����.
int _fastcall rstCreateDuplicateImage256(TRSTDATA *rstdata, int divisor);

// ������� ����������� ������� ����������� ���� rstdata->Duplicate ������
// (rstdata->Duplicate ������ ��������� ��������� ����������� �����)
// divisor - �������� ����������� ���������� ��������� ������
// ��� ������ :
//   ���������� ����,
//   �������� �� ����������� ����� � �������� ������ ��������������� � ����,
//   ������ rstdata->Duplicate ��������� � ��������������� � ����.
int _fastcall rstCreateDuplicateImage(TRSTDATA *rstdata, int divisor);


// ��������� ��������� � ��. ��������� ��������� �����������
// ����� ������ �� �������� headeroffset �� ������ ����� ������
int _fastcall rstReadDuplicate(TRSTDATA *rstdupdata, 
                               unsigned long headeroffset);

// �������� ��������� ����������� ����� ������ � ������� � ����
// headeroffset - �������� ������������ ������ ����� �� ���������
//                ����������� �����
// ��� ������ ���������� 0
int _fastcall rstCreateDuplicateHeader(TRSTDATA *rstdupdata,
                                       unsigned long headeroffset,
                                       long width, long height,
                                       long elementSize,
                                       double scale, double precision,
                                       DOUBLEPOINT location,
                                       int offsetFactor);  

#endif   // RSTBASE_H
