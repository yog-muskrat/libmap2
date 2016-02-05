
#ifndef PICEXPRM_H
#define PICEXPRM_H

#include "maptype.h"

#define WM_PCX2RST               0x590       // Конвертер  PCX в RST
#define WM_PCX2RST_PROGRESS      0x591
#define WM_PCX2RST_ERROR         0x592

#define WM_RSTCOMPRESS           0x593       // Сжатие растра
#define WM_RSTCOMPRESS_ERROR     0x594

// СТРУКТУРА ДЛЯ ПЕРЕДАЧИ ИНФОРМАЦИИ О ГРАФИЧЕСКИХ ФАЙЛАХ ДИАЛОГУ ОТ КОНВЕРТЕРА
typedef struct DATAINFORMATION
       {
       unsigned long int InputFileLength ;  // длина файла графического изображения
       long int Width           ;  // ширина изображения
       long int Height          ;  // высота изображения
       long int BitPerPixel     ;  // кол-во бит на пиксел
       double   Precision       ;  // разрешаюшая способность изображения (т\д)
       char PaletteType[4]      ;  // Устаревшее поле. Резерв      

       long int BlockCount      ;  // кол-во блоков в растре
       double   RswFileLength   ;  // теоретическая длина файла *.rsw
       char CompressImage[16]   ;  // сжатие изображения  
       }
          DATAINFORMATION;


// СТРУКТУРА ДЛЯ ПЕРЕДАЧИ ИНФОРМАЦИИ О GeoTIFF-ФАЙЛАХ
typedef struct GEOTIFFINFORMATION   
       {
        unsigned long int StructSize;  // длина СТРУКТУРЫ
        unsigned long int TypeCS;      // Тип координатной системы

        unsigned long int Spheroid;    // Эллипсоид
        unsigned long int Datum;       // Геодезические даты
        unsigned long int PrimeMeridian;//Осевой меридиан

        unsigned long int Projection;  // Проекция
        unsigned long int Zone;        // Номер зоны

        unsigned long int Units;       // Единицы измерения линий (Метры, градусы ...)


        DFRAME FrameImage;             // Габариты изображения в районе
        double UnitsInElement_X;       // Размер элемента в единицах измерения по оси X
        double UnitsInElement_Y;       // Размер элемента в единицах измерения по оси Y
        double UnitsInElement_Z;       // Размер элемента в единицах измерения по оси Z
        char Information[256]  ;       // Информация о проекции, имени программы и т.д.
        double PrecisionInch;          // разрешаюшая способность изображения (т\д) 
        double PrecisionMet;           // разрешаюшая способность изображения (т\м) 
        unsigned long int UnitsAngular;// Единицы измерения углов (градусы, радианы ...)  

        char Reserv[244];
       }
          GEOTIFFINFORMATION;

 // СТРУКТУРА ДЛЯ ПЕРЕДАЧИ СООБЩЕНИЙ ОБ ОШИБКАХ ДИАЛОГУ ОТ КОНВЕРТЕРА
typedef struct ERRORINFORMATION
       {
       char * MessageR    ;  // Сообщение об ошибке на русском языке
       char * MessageE    ;  // Сообщение об ошибке на английском языке
       }
           ERRORINFORMATION;

// Тип платформы (0 - INTEL, 1 - MOTOROLA)    
#define INTEL    0
#define MOTOROLA 1

// Структура изображения TIFF (0 - BLOCK, 1- STRIP, 2 - NONFRAG)
#define BLOCK    0
#define STRIP    1
#define NONFRAG  2


#endif  //PICEXPRM_H
