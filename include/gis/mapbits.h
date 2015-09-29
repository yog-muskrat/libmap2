

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
// ++++++++ КЛАСС ДАННЫХ: НАБОР БИТОВ ++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifdef __cplusplus

class _DLLCLASS TBitSet32
{
 public:

 // Коды возврата управляющих функций
 enum RETCODE { SET = 1 , CLEAR = 0 } ;

 // Инициализация данных
 TBitSet32() { Set(); }

 // Обнулить все биты
 void Clear() { Bits[0] = 0; }

 // Установить все биты в 1
 void Set() { Bits[0] = 0x0FFFFFFFFL; }

 // Обнулить заданный бит
 void Clear(int number)
 {
   Bits[0] &= ~(1 << (number & 0x01F));
 }

 // Установить заданный бит
 void Set(int number)
 {
   Bits[0] |= (1 << (number & 0x01F));
 }

 // Опросить заданный бит
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
// ++++++++ КЛАСС ДАННЫХ: НАБОР БИТОВ ++++++++++++++++++++++
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

 // Коды возврата управляющих функций
 enum RETCODE { SET = 1 , CLEAR = 0 } ;

 // Инициализация данных
 TBitSet256() { Set(); }

 // Обнулить все биты
 void Clear() { memset(Bits,0,sizeof(Bits)); }

 // Установить все биты в 1
 void Set() { memset(Bits,-1,sizeof(Bits)); }

 // Обнулить заданный бит
 void Clear(int number)
 {
   Bits[(number & 0x0FF) >> 3] &= (unsigned char)
        ~(1 << (number & 0x07));
 }

 // Установить заданный бит
 void Set(int number)
 {
   Bits[(number & 0x0FF) >> 3] |= (unsigned char)
        (1 << (number & 0x7));
 }

 // Опросить заданный бит
 int Check(int number)
 {
   return (Bits[(number & 0x0FF) >> 3] &
            (1 << (number & 0x7)));
 }

// private:

 unsigned char Bits[32];

};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ КЛАСС ДАННЫХ: НАБОР БИТОВ ++++++++++++++++++++++
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

 // Коды возврата управляющих функций
 enum RETCODE { SET = 1 , CLEAR = 0 } ;

 // Инициализация данных
 TBitSet1K() { Set(); }

 // Обнулить все биты
 void Clear() { memset(Bits,0,sizeof(Bits)); }

 // Установить все биты в 1
 void Set() { memset(Bits,-1,sizeof(Bits)); }

 // Обнулить заданный бит
 void Clear(int number)
 {
   Bits[(number & 1023) >> 3] &= (unsigned char)
         ~(1 << (number & 0x7));
 }

 // Установить заданный бит
 void Set(int number)
 {
   Bits[(number & 1023) >> 3] |= (unsigned char)
        (1 << (number & 0x7));
 }

 // Опросить заданный бит
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
// ++++++++ КЛАСС ДАННЫХ: НАБОР БИТОВ ++++++++++++++++++++++
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

 // Коды возврата управляющих функций

 enum RETCODE { SET = 1 , CLEAR = 0 } ;

 // Инициализация данных

   TBitSet4K() { Set(); }

 // Обнулить все биты

   void Clear() { memset(Bits,0,sizeof(Bits)); }

 // Установить все биты в 1

   void Set() { memset(Bits,-1,sizeof(Bits)); }

 // Обнулить заданный бит

   void Clear(int number)
      {
        Bits[(number & 4095) >> 3] &= (unsigned char)
             ~(1 << (number & 0x7));
      }

 // Установить заданный бит

   void Set(int number)
      {
        Bits[(number & 4095) >> 3] |= (unsigned char)
             (1 << (number & 0x7));
      }

 // Опросить заданный бит

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
// ++++++++ КЛАСС ДАННЫХ: НАБОР БИТОВ ++++++++++++++++++++++
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

 // Коды возврата управляющих функций

 enum RETCODE { SET = 1 , CLEAR = 0 } ;

 // Инициализация данных

   TBitSet64K() { Set(); }

 // Обнулить все биты

   void Clear() { memset(Bits,0,sizeof(Bits)); }

 // Установить все биты в 1

   void Set() { memset(Bits,-1,sizeof(Bits)); }

 // Обнулить заданный бит

   void Clear(int number)
       {
         Bits[(number & 0x0FFFF) >> 3] &= (unsigned char)
            ~(1 << (number & 0x7));
       }

 // Установить заданный бит

   void Set(int number)
       {
         Bits[(number & 0x0FFFF) >> 3] |= (unsigned char)
             (1 << (number & 0x7));
       }

 // Опросить заданный бит

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

 // Запросить число единиц в битовом массиве
 // в пределах заданного числа бит

 int _fastcall bitCount64K(TBitSet64K * bits, int limit);

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ КЛАСС ДАННЫХ: НАБОР БИТОВ ПЕРЕМЕННОЙ ДЛИНЫ +++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#ifdef __cplusplus

class _DLLCLASS TBitSetVariable
{
  public:

  // Коды возврата управляющих функций

  enum RETCODE { SET = 1 , CLEAR = 0 } ;

  // Инициализация данных

  TBitSetVariable(unsigned int count = 0)
     {
       Bits = 0;
       size = 0;
       ChangeSize(count);
     }

  ~TBitSetVariable() { Free();} 

  // Освободить память

  void Free()              
     {
       delete [] Bits;
       Bits = 0;
     }

  // Изменить число бит в массиве

  void ChangeSize(unsigned int count)
     {
       delete [] Bits;
       if (count < 8) count = 1024;
       size = (count + 7) >> 3;
       Bits = new unsigned char[size];
     }


  // Обнулить все биты

  void Clear() { if (Bits) memset(Bits, 0, size); }

  // Установить все биты в 1

  void Set() { if (Bits) memset(Bits, -1, size); }

  // Обнулить заданный бит

  void Clear(unsigned int number)
       {
         if (Bits && ((number >> 3) < size))
           Bits[number >> 3] &= (unsigned char)
                                 ~(1 << (number & 0x7));
       }

  // Установить заданный бит

  void Set(unsigned int number)
       {
         if (Bits && ((number >> 3) < size))
           Bits[number >> 3] |= (unsigned char)
                                (1 << (number & 0x7));
       }

  // Опросить заданный бит

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

