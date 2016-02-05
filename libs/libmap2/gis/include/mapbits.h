

#if !defined(MAPBITS_H)
#define MAPBITS_H

#ifndef MAPMACRO_H
  #include "mapmacro.h"
#endif

#ifndef OC2000   
#ifndef MEMORY_H
  #include <memory.h>
  #define MEMORY_H
#endif                      
#endif

#define bitClearAll(bits)       memset(bits.Bits, 0, sizeof(bits))
#define bitSetAll(bits)         memset(bits.Bits, -1, sizeof(Bits))

#define bitClear32(bits,number) bits.Bits[0] &= ~(1 << (number & 0x01F)) 
#define bitClear32All(bits)     bits.Bits[0]  = 0

#define bitSet32(bits,number)   bits.Bits[0] |= (1 << (number & 0x01F))  
#define bitSet32All(bits)       bits.Bits[0]  = 0x0FFFFFFFFL             

#define bitCheck32(bits,number) (bits.Bits[0] & (1 << (number & 0x01F)))

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ����� ������: ����� ����� ++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifdef __cplusplus

class _DLLCLASS TBitSet32
{
 public:

 // ���� �������� ����������� �������
 enum RETCODE { SET = 1 , CLEAR = 0 } ;

 // ������������� ������
 TBitSet32() { Set(); }

 // �������� ��� ����
 void Clear() { Bits[0] = 0; }

 // ���������� ��� ���� � 1
 void Set() { Bits[0] = 0x0FFFFFFFFL; }

 // �������� �������� ���
 void Clear(int number)
 {
   Bits[0] &= ~(1 << (number & 0x01F));
 }

 // ���������� �������� ���
 void Set(int number)
 {
   Bits[0] |= (1 << (number & 0x01F));
 }

 // �������� �������� ���
 int Check(int number)
 {
   return (Bits[0] & (1 << (number & 0x01F)));
 }

// private:

 LONG Bits[1];

};

#else

typedef  struct { LONG Bits[1]; }  TBitSet32;

#endif    // __cplusplus

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ����� ������: ����� ����� ++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define bitClear256(bits,number)  bits.Bits[(number & 0x0FF) >> 3] \
                                &= (unsigned char)~(1 << (number & 0x07))

#define bitSet256(bits,number)    bits.Bits[(number & 0x0FF) >> 3] \
                                |= (unsigned char) (1 << (number & 0x7))

#define bitCheck256(bits,number) (bits.Bits[(number & 0x0FF) >> 3] \
                                  & (1 << (number & 0x7)))

class _DLLCLASS TBitSet256
{
  public:

 // ���� �������� ����������� �������
 enum RETCODE { SET = 1 , CLEAR = 0 } ;

 // ������������� ������
 TBitSet256() { Set(); }

 // �������� ��� ����
 void Clear() { memset(Bits,0,sizeof(Bits)); }

 // ���������� ��� ���� � 1
 void Set() { memset(Bits,-1,sizeof(Bits)); }

 // �������� �������� ���
 void Clear(int number)
 {
   Bits[(number & 0x0FF) >> 3] &= (unsigned char)
        ~(1 << (number & 0x07));
 }

 // ���������� �������� ���
 void Set(int number)
 {
   Bits[(number & 0x0FF) >> 3] |= (unsigned char)
        (1 << (number & 0x7));
 }

 // �������� �������� ���
 int Check(int number)
 {
   return (Bits[(number & 0x0FF) >> 3] &
            (1 << (number & 0x7)));
 }

// private:

 unsigned char Bits[32];

};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ����� ������: ����� ����� ++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define bitClear1K(bits,number)  bits.Bits[(number & 1023) >> 3] \
                                &= (unsigned char)~(1 << (number & 0x07))

#define bitSet1K(bits,number)    bits.Bits[(number & 1023) >> 3] \
                                |= (unsigned char) (1 << (number & 0x7))

#define bitCheck1K(bits,number)  (bits.Bits[(number & 1023) >> 3] \
                                  & (1 << (number & 0x7)))

#ifdef __cplusplus

class _DLLCLASS TBitSet1K
{
 public:

 // ���� �������� ����������� �������
 enum RETCODE { SET = 1 , CLEAR = 0 } ;

 // ������������� ������
 TBitSet1K() { Set(); }

 // �������� ��� ����
 void Clear() { memset(Bits,0,sizeof(Bits)); }

 // ���������� ��� ���� � 1
 void Set() { memset(Bits,-1,sizeof(Bits)); }

 // �������� �������� ���
 void Clear(int number)
 {
   Bits[(number & 1023) >> 3] &= (unsigned char)
         ~(1 << (number & 0x7));
 }

 // ���������� �������� ���
 void Set(int number)
 {
   Bits[(number & 1023) >> 3] |= (unsigned char)
        (1 << (number & 0x7));
 }

 // �������� �������� ���
 int Check(int number)
 {
   return (Bits[(number & 1023) >> 3] &
           (1 << (number & 0x7)));
 }

// private:

 unsigned char Bits[1024 / 8];

};

#else

//typedef struct { unsigned char Bits[1024 / 8] } TBitSet1K;

#endif


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ����� ������: ����� ����� ++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define bitClear4K(bits,number)  bits.Bits[(number & 4095) >> 3] \
                                &= (unsigned char)~(1 << (number & 0x07))

#define bitSet4K(bits,number)    bits.Bits[(number & 4095) >> 3] \
                                |= (unsigned char) (1 << (number & 0x7))

#define bitCheck4K(bits,number) (bits.Bits[(number & 4095) >> 3] \
                                 & (1 << (number & 0x7)))


#ifdef __cplusplus

class _DLLCLASS TBitSet4K
{
  public:

 // ���� �������� ����������� �������

 enum RETCODE { SET = 1 , CLEAR = 0 } ;

 // ������������� ������

   TBitSet4K() { Set(); }

 // �������� ��� ����

   void Clear() { memset(Bits,0,sizeof(Bits)); }

 // ���������� ��� ���� � 1

   void Set() { memset(Bits,-1,sizeof(Bits)); }

 // �������� �������� ���

   void Clear(int number)
      {
        Bits[(number & 4095) >> 3] &= (unsigned char)
             ~(1 << (number & 0x7));
      }

 // ���������� �������� ���

   void Set(int number)
      {
        Bits[(number & 4095) >> 3] |= (unsigned char)
             (1 << (number & 0x7));
      }

 // �������� �������� ���

   int Check(int number)
      {
        return (Bits[(number & 4095) >> 3] &
           (1 << (number & 0x7)));
      }

//  private:

 unsigned char Bits[4096 / 8];

};

#else

typedef struct TBitSet4K { unsigned char Bits[4096 / 8];} TBitSet4K; 

#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ����� ������: ����� ����� ++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define bitClear64K(bits,number)  bits.Bits[(number & 0x0FFFF) >> 3] \
                                &= (unsigned char)~(1 << (number & 0x07))

#define bitSet64K(bits,number)    bits.Bits[(number & 0x0FFFF) >> 3] \
                                |= (unsigned char) (1 << (number & 0x7))

#define bitCheck64K(bits,number) (bits.Bits[(number & 0x0FFFF) >> 3] \
                                  & (1 << (number & 0x7)))


#ifdef __cplusplus

class _DLLCLASS TBitSet64K
{
  public:

 // ���� �������� ����������� �������

 enum RETCODE { SET = 1 , CLEAR = 0 } ;

 // ������������� ������

   TBitSet64K() { Set(); }

 // �������� ��� ����

   void Clear() { memset(Bits,0,sizeof(Bits)); }

 // ���������� ��� ���� � 1

   void Set() { memset(Bits,-1,sizeof(Bits)); }

 // �������� �������� ���

   void Clear(int number)
       {
         Bits[(number & 0x0FFFF) >> 3] &= (unsigned char)
            ~(1 << (number & 0x7));
       }

 // ���������� �������� ���

   void Set(int number)
       {
         Bits[(number & 0x0FFFF) >> 3] |= (unsigned char)
             (1 << (number & 0x7));
       }

 // �������� �������� ���

   int Check(int number)
        {
          return (Bits[(number & 0x0FFFF) >> 3] &
                       (1 << (number & 0x7)));
        }

//  private:

 unsigned char Bits[64*1024 / 8];

};

#else

typedef struct TBitSet64K { unsigned char Bits[64*1024 / 8];} TBitSet64K; 

#endif  // __cplusplus

 // ��������� ����� ������ � ������� �������
 // � �������� ��������� ����� ���

 int _fastcall bitCount64K(TBitSet64K * bits, int limit);

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ����� ������: ����� ����� ���������� ����� +++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#ifdef __cplusplus

class _DLLCLASS TBitSetVariable
{
  public:

  // ���� �������� ����������� �������

  enum RETCODE { SET = 1 , CLEAR = 0 } ;

  // ������������� ������

  TBitSetVariable(unsigned int count = 0)
     {
       Bits = 0;
       size = 0;
       ChangeSize(count);
     }

  ~TBitSetVariable() { Free();} 

  // ���������� ������

  void Free()              
     {
       delete [] Bits;
       Bits = 0;
     }

  // �������� ����� ��� � �������

  void ChangeSize(unsigned int count)
     {
       delete [] Bits;
       if (count < 8) count = 1024;
       size = (count + 7) >> 3;
       Bits = new unsigned char[size];
     }


  // �������� ��� ����

  void Clear() { if (Bits) memset(Bits, 0, size); }

  // ���������� ��� ���� � 1

  void Set() { if (Bits) memset(Bits, -1, size); }

  // �������� �������� ���

  void Clear(unsigned int number)
       {
         if (Bits && ((number >> 3) < size))
           Bits[number >> 3] &= (unsigned char)
                                 ~(1 << (number & 0x7));
       }

  // ���������� �������� ���

  void Set(unsigned int number)
       {
         if (Bits && ((number >> 3) < size))
           Bits[number >> 3] |= (unsigned char)
                                (1 << (number & 0x7));
       }

  // �������� �������� ���

  int Check(unsigned int number)
        {
          if (Bits && ((number >> 3) < size))
            return (Bits[number >> 3] & (1 << (number & 0x7)));
          return 0;
        }

  private:

  unsigned char * Bits;
  unsigned int size;

};

#endif  // __cplusplus


#endif  // MAPBITS_H

