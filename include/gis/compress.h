
#ifndef COMPRESS_H
#define COMPRESS_H

#include "mapmacro.h"

typedef struct TCOMPRESSDATA
{
  // Переменные для алгоритма LZW
  char *Used;
  char *Follower;
  int *Next;
  int *Predecessor;
}
  TCOMPRESSDATA;

// Инициализация таблицы кодирования
int _fastcall tcInitTab(TCOMPRESSDATA *compressdata);

// Заполнить строку таблицы
void _fastcall tcFillTab(TCOMPRESSDATA *compressdata, int pred, char foll);

// Найти индекс в таблице
int _fastcall tcFindIndex(TCOMPRESSDATA *compressdata, int pred, char foll);

// Компрессия блока
int _fastcall tcCompress(TCOMPRESSDATA *compressdata, const char* in,  int sizein,
                       char* out, int sizeout);

// Декомпрессия блока
int _fastcall tcDecompress(TCOMPRESSDATA *compressdata, 
                           const char* in,  int sizein,
                           char* out, int sizeout);

// Сжатие блока 32-битных матричных данных
// (Значения высот ниже минимальной кодируются
//  псевдокодами без сохранения значения)
int _fastcall tcCompressMtr(TCOMPRESSDATA *compressdata, 
                              const char* in,  int sizein,
                              char* out, int sizeout, long minimum);

// Разжатие блока 32-битных матричных данных
int _fastcall tcDecompressMtr(TCOMPRESSDATA *compressdata, 
                              const char* in,  int sizein,
                              char* out, int sizeout);

class _DLLCLASS  TCompress: public TCOMPRESSDATA
{
 public:

  TCompress();
 ~TCompress();

  // Компрессия блока LZW
  int Compress(const char* in,  int sizein,
                     char* out, int sizeout);

  // Декомпрессия блока LZW
  int Decompress(const char* in,  int sizein,
                       char* out, int sizeout);

  // Компрессия блока 32-битной матрицы
  // (Значения высот ниже минимальной кодируются
  //  псевдокодами без сохранения значения)
  int CompressMtr(const char* in,  int sizein,
                        char* out, int sizeout, long minimum);

  // Декомпрессия блока 32-битной матрицы
  int DecompressMtr(const char* in,  int sizein,
                          char* out, int sizeout);

 private:

  // Инициализация таблицы кодирования LZW
  int InitTab();

  // Заполнить строку таблицы LZW
  void FillTab(int pred,char foll);

  // Найти индекс в таблице LZW
  int FindIndex(int pred,char foll);

};

#endif  // COMPRESS_H

