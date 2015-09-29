
#ifndef COMPRESS_H
#define COMPRESS_H

#include "mapmacro.h"

typedef struct TCOMPRESSDATA
{
  // ���������� ��� ��������� LZW
  char *Used;
  char *Follower;
  int *Next;
  int *Predecessor;
}
  TCOMPRESSDATA;

// ������������� ������� �����������
int _fastcall tcInitTab(TCOMPRESSDATA *compressdata);

// ��������� ������ �������
void _fastcall tcFillTab(TCOMPRESSDATA *compressdata, int pred, char foll);

// ����� ������ � �������
int _fastcall tcFindIndex(TCOMPRESSDATA *compressdata, int pred, char foll);

// ���������� �����
int _fastcall tcCompress(TCOMPRESSDATA *compressdata, const char* in,  int sizein,
                       char* out, int sizeout);

// ������������ �����
int _fastcall tcDecompress(TCOMPRESSDATA *compressdata, 
                           const char* in,  int sizein,
                           char* out, int sizeout);

// ������ ����� 32-������ ��������� ������
// (�������� ����� ���� ����������� ����������
//  ������������ ��� ���������� ��������)
int _fastcall tcCompressMtr(TCOMPRESSDATA *compressdata, 
                              const char* in,  int sizein,
                              char* out, int sizeout, long minimum);

// �������� ����� 32-������ ��������� ������
int _fastcall tcDecompressMtr(TCOMPRESSDATA *compressdata, 
                              const char* in,  int sizein,
                              char* out, int sizeout);

class _DLLCLASS  TCompress: public TCOMPRESSDATA
{
 public:

  TCompress();
 ~TCompress();

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

 private:

  // ������������� ������� ����������� LZW
  int InitTab();

  // ��������� ������ ������� LZW
  void FillTab(int pred,char foll);

  // ����� ������ � ������� LZW
  int FindIndex(int pred,char foll);

};

#endif  // COMPRESS_H

