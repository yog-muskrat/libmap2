
#ifndef ERRORVALUE
 #define ERRORVALUE -1111
#endif

#ifndef GEOTYPE_H
#define GEOTYPE_H

typedef struct TEOSTAT     // БЛОК СТАТИСТИКИ
{
 long int BlockCount;      // Количество блоков данных
 long int MaxBlockSize;    // Максимальное количество точек в блоке
}
 TEOSTAT;

enum COURSETYPE            // Тип теодолитного хода
{
 COURSE_UNDEFINED = 0, // Неопределен
 COURSE_UNLOCK    = 1, // Разомкнутый
 COURSE_CLOSE     = 2, // Сомкнутый
 COURSE_LOCK      = 3, // Замкнутый
 COURSE_ADJOIN    = 4, // С 1-м примычным углом
 COURSE_FREE      = 5, // Свободный (висячий)
 COURSE_LINK      = 6  // С координатной привязкой
};

enum TPRTYPE    // Тип прямой задачи
{
 TPR_UNDEFINED    = 0, // Неопределен
 TPR_INTERSECTION = 1, // Засечка
 TPR_POLAR        = 2, // Полярка
};

enum BASEPOINTTYPE    // Тип представления базовой точки
{
 BASE_N_X_Y_H   = 0, // N X Y H
 BASE_N_X_Y     = 1, // N X Y
 BASE_N_A       = 2, // N A
 BASE_N         = 3  // N
};

typedef struct BASEPOINT   // ЗАПИСЬ БАЗОВОЙ ТОЧКИ
{
 char Name[256];           // Название (номер) точки
 double X;                 // X
 double Y;                 // Y
 double H;                 // H
 double A;                 // A
 double Hi;                // Высота инструмента     

 long int Type;            // Тип записи (BASE_N_X_Y_H, ...)
 long int Rezerv;          //
}
 BASEPOINT;

enum MEAPOINTTYPE          // Тип записи измерений
{
 MEA_N_N          = 0, // N N
 MEA_N_N_A        = 1, // N N A
 MEA_N_N_A_D      = 2, // N N A D
 MEA_N_N_A_D_H    = 3, // N N A D H
};


// Измененная структура К.Е. от 
typedef struct MEASUREPOINT  // ЗАПИСЬ ТОЧКИ ХОДА  (формирование записи в TPR2)
{
 char Name1[256];      // Название (номер) точки стояния
 char Name2[256];      // Название (номер) наблюдаемой точки
 double Angle;         // Горизонтальный угол (левый поворотный)
 double Distance;      // Расстояние
 double dH;            // Превышение
 double Ha;            // Горизонтальный угол                   
 double Va;            // Вертикальный угол                     
 double Sd;            // Наклонное расстояние                  
 double Direct;        // Дирекционный угол на следующую точку  
 double Ht;            // Высота отражателя                     
 double Hi;            // Высота прибора                        
 char Code[32];        // Полевой код                           
 int Priz;             // признак записи в файл TPR             
 long int Type;        // Тип записи (MEA_...)
 long int Rezerv;      //
}
 MEASUREPOINT;




#endif
