
#ifndef M3DGDI_H
#define M3DGDI_H

#define DELTA3D  0.001       // точность совпадения метрик (до 1мм)

//******************************************************************
//                   ВИДЫ ЭЛЕМЕНТОВ ИЗОБРАЖЕНИЯ                    *
//******************************************************************

#define IMG3D_ANY              0  // Произвольный
#define IMG3D_CUBE             1  // Куб
#define IMG3D_SPHERE           2  // Сфера
#define IMG3D_CYLINDER         3  // Цилиндр
#define IMG3D_CONE             3  // Конус
#define IMG3D_QUAD             4  // Четырехугольник
#define IMG3D_ADJOINQUAD       5  // Примыкающий четырехугольник
#define IMG3D_COMBPOLYGON      6  // Связанный многоугольник
#define IMG3D_LINE            11  // Линия сплошная


//******************************************************************
//                   ТИПЫ СЕЧЕНИЙ ОБЪЕМНОЙ ЛИНИИ                   *
//******************************************************************
#define SECT_CIRCLE        1  // Oкружность
#define SECT_RECT          2  // Прямоугольник
#define SECT_MOUND         3  // Трапеция(насыпь)


//******************************************************************
//                   ВИДЫ УЗЛОВ ИЗОБРАЖЕНИЯ (для инициализации)    *
//******************************************************************
#define NODE_ANY               0  // Произвольный
#define NODE_BOX               1  // Короб
#define NODE_SPHERE            2  // Сфера
#define NODE_VCYLINDER         3  // Цилиндр вертикальный
#define NODE_HCYLINDER         4  // Цилиндр горизонтальный
#define NODE_CROSSQUAD         5  // Изображение объемное
#define NODE_HQUAD             6  // Плоскость горизонтальная
#define NODE_VQUAD             7  // Плоскость вертикальная
#define NODE_TOP               8  // Призма треугольная горизонтальная

//******************************************************************
// ВИДЫ ФУНКЦИЙ ВИЗУАЛИЗАЦИИ ПРОИЗВОЛЬНЫХ ОБЪЕМНЫХ
//             ГРАФИЧЕСКИХ ОБ'ЕКТОВ НА ЭК
//******************************************************************
#define F3D_NULL               0  // Пустая функция - ничего не рисует
#define F3D_EMPTY              1  // Пустая функция - рисует отсутствие объекта
#define F3D_MARK               2  // Знак
#define F3D_MARKBYLINE         3  // Знак по линии
#define F3D_MARKBYPOINT        4  // Знак по точкам    (F3D_MARK)
#define F3D_MARKBYSQUARE       5  // Знак по площади
#define F3D_VERTBYLINE         6  // Вертикальная плоскость по линии
#define F3D_HORIZONTBYLINE     7  // Горизонтальная плоскость по линии
#define F3D_HORIZONT           8  // Горизонтальная плоскость
#define F3D_LINEBYSURFACE      9  // Полоса учетом поверхности
#define F3D_TREE              10  // Набор функций
#define F3D_TOPONSQUARE       11  // "Крыша над площадным "
#define F3D_SQUARECYLINDER    12  // Цилиндр горизонтальный над площадным
#define F3D_FLATLINE          14  // Плоская линия
#define F3D_SURFACE           15  // Плоскость с учетом поверхности
#define F3D_SECTIONBYLINE     16  // Линия c заданным сечением



//                      Набор функций (кол-во)
//                              |
//       ---------------------------------------------------
//       |                                                  |
//   Заголовок(длина + N Функции)                  Заголовок(длина + N Функции)
//       |                                                  |
//   Параметры функции (+кол-во узлов)     Параметры функции (+кол-во узлов)
//       |                                                  |
//       ------------------------------                     |
//       |                            |                     |
//  Узел (+ кол-во описаний)       Узел (+1описание)  Узел (+2 описания)
//       |                            |                     |
//       |                            |               --------------------
//       |                            |               |                   |
//   Описание (+ кол-во элементов)  Описание        Описание            Описание
//       |                            |               |                   |
//   -------------------              |           ------------            |
//   |                  |             |           |           |           |
// Элемент          Элемент        Элемент     Элемент     Элемент      Элемент
//   |                  |             |           |           |           |
// Метрика по типу
//   точки(либо рамеры)

// Функция рисуется независимо от других функций по метрике объекта.
// Если для рисование какой-то части объекта зависит от другой - необходимо
// объединить их в функцию. Например размещение знаков по площади, где выбор
// места рисования знака зависит от параметров размещения
// Параметры функции определяются по номеру Функции.
//
// Количество узлов может быть различно(для одной и той же функции)
// Узел - определенным образом связанная часть метрики с размерами
// Существует несколько видов узлов (для выбора):
//   Короб, Плоскость вертикальная ...
//
// Узел состоит из более простых графических элементов
// Элементы имеющие одинаковое оформление(цвет, текстуру...)
// имеют общее Описание
// Типы элементов: IMG3D_ANY - произвольный,
//                 IMG3D_CUBE - куб,
//                 IMG3D_SPHERE - сфера,
//                 IMG3D_CYLINDER - цилиндр,
//                 IMG3D_CONE - конус,
//                 IMG3D_QUAD - четырехугольник,
//                 IMG3D_ADJOINQUAD - примыкающий четырехугольник,
//                 IMG3D_COMBPOLYGON - связанный многоугольник,
//                 IMG3D_LINE - линия.


//******************************************************************
//                 ВСПОМОГАТЕЛЬНЫЕ СТРУКТУРЫ                       *
//******************************************************************
typedef struct IMG3DRGBA            // ЦВЕТ RGBA
{
  float R;                          // Красный
  float G;                          // Зеленый
  float B;                          // Синий
  float A;                          // Альфа, степень непрозрачности

  IMG3DRGBA& operator = (IMG3DRGBA& color)                                
  { R = color.R;  G = color.G;  B = color.B; A = color.A; return *this;}
}
  IMG3DRGBA;


typedef struct IMG3DPOINT           // ТОЧКА
{
  double X;                         // Координаты в метрах
  double Y;                         //
  double Z;                         //
  int operator == (IMG3DPOINT * value)                                     
     { return ((X - value->X < DELTA3D) && ( value->X - X < DELTA3D)&&
                (Y - value->Y < DELTA3D) && ( value->Y - Y < DELTA3D)&&
                (Z - value->Z < DELTA3D) && ( value->Z - Z < DELTA3D)); }
}
  IMG3DPOINT;


typedef struct IMG3DRELATE          // Используется только в IMG3DVALUE
{                                   // при наложении на поле Type
 short int Ident;                   // Идентификатор функции источника
 short int Refer;                   // Тип ссылки
} IMG3DRELATE;


typedef struct IMG3DVALUE           // КОМБИНИРОВАННОЕ ЗНАЧЕНИЕ
{
   long  int Type ;                 // 0 - брать значение
                                    // > 0 брать номер семантики
                                    // < 0  - брать по ссылке на функцию IMG3DRELATE
   float     Value;                 // Значение
   float     Factor;                // Коэффициент для значения( кроме Type == 0)
   float     Offset;                // Сдвиг значения( кроме Type == 0)
}
  IMG3DVALUE;



typedef struct TEXTURETYPE          // ИНФОРМАЦИЯ О ТЕКСТУРЕ
{
            long  int Type;         // 0 или номер семантики
   unsigned long  int Code;         // Номер текстуры  = 0
            long  int Key;          // Ключ текстуры - уникален в пределах
                                    // файла
            long  int Reserve;      // Резерв   
}
  TEXTURETYPE;


typedef struct ACT3DMATERIALMODE    // ПАРАМЕТРЫ МАТЕРИАЛА
{
  IMG3DRGBA AmbientColor ;          // Рассеянный цвет
  IMG3DRGBA DiffuseColor ;          // Диффузный  цвет
  IMG3DRGBA SpecularColor;          // Зеркальный
  IMG3DRGBA EmissiveColor;          // Излучаемый
  double     Shininess;             // Зеркальная экспонента   
}
  ACT3DMATERIALMODE;

typedef struct IMG3DROTATION        // ПОВОРОТ ЧАСТИ ОТНОСИТЕЛЬНО ТЕКУЩЕГО
{                                   // ПОЛОЖЕНИЯ
  float X;                          //
  float Y;                          // вектор-нормаль к плоскости вращения
  float Z;                          //
  float Angle;                      // угол вращения против часовой стрелки
}
  IMG3DROTATION ;

enum FUNCTIONREFERENCE              // ПРИЗНАКИ ОТНОСИТЕЛЬНОГО РАСПОЛОЖ.ФУНКЦИЙ
{
     treeTOP    = 0,                // разместить сверху (по Y)
     treeBOTTOM = 1,                // разместить снизу  (по Y)
     treeLEFT   = 2,                // разместить слева  (от метрики)
     treeWRITE  = 4,                // разместить справа (от метрики)
};
                                    // ФЛАГ РАСПОЛОЖЕНИЯ УЗЛА ОТНОСИТЕЛЬНО
                                    // ПОВЕРХНОСТИ

#define ALLBYRELIEF            0    // с учетом рельефа местности
#define ALLFREE                1    // без учета рельефа (построение по
                                    // высотам ведется относительно средней
                                    // высоты метрики объекта)
#define TOPFREE                2    // без учета рельфа для верхней границы
                                    // плоскости (высота плоскости отладывается
                                    // относительно средней высоты метрики
                                    // объекта + RelativeHeight)

//******************************************************************
//            СТРУКТУРЫ ПАРАМЕТРОВ ФУНКЦИЙ                         *
//******************************************************************

typedef struct F3DMARK              // ЗНАК
{
  IMG3DVALUE      Height;           // Высота знака (по Y)
  IMG3DVALUE      RelativeHeight;   // Высота расположения знака относительно
                                    // метрики
  IMG3DVALUE      SizeX;            // Размеры знака (ширина(по X))
  IMG3DVALUE      SizeZ;            // Размеры знака (длина(по Z)))
  long            Scale[3];         // Флаги масштабируемости (по ширине
                                    // (по X), по высоте(по Y), по длине(по Z))
  char            Vector;           // Флаг ориентации для векторного знака:
                                    //   0 - неориентированный,
                                    //   1 - ориентация вдоль метрики текущего
                                    //       отрезка,
                                    //   2 -  -"-  вдоль метрики предыдущего
                                    //       отрезка,
                                    //   3 -  -"-  вдоль биссектрисы угла, в
                                    //        вершине которого ставится знак
  char            Reserve1[3];      
  IMG3DPOINT      Point[2];         // Point[0] - координаты точки начала знака
                                    //            относительно точки метрики
                                    // Point[1] - смещение минимума габаритов
                                    //            знака относительно точки начала
                                    //            знака
                                    // задается двумя точками от нуля знака)
  long            Count;            // Количество узлов
  long            Reserve2;         
}
  F3DMARK;

typedef struct F3DVERTBYLINE        // ВЕРТИКАЛЬНАЯ ПЛОСКОСТЬ ПО ЛИНИИ
{
  IMG3DVALUE      Height;           // Высота плоскости(вверх)
  IMG3DVALUE      RelativeHeight;   // Высота расположения плоскости относительно
                                    // метрики объекта:
                                    //       положительная - вверх,
                                    //       отрицательная - вниз
  IMG3DVALUE      Removal;          // Смещение плоскости по поверхности,
                                    // относительно метрики объекта(пока нет)
  long            SurfaceFlag;      // Флаг расположения плоскости относительно
                                    // поверхности: ALLBYRELIEF, ALLFREE,
                                    // TOPFREE (см. выше)
  long            Count;            // Количество узлов
}
  F3DVERTBYLINE;

typedef struct F3DHORIZONT          // ГОРИЗОНТАЛЬНАЯ ПЛОСКОСТЬ
{
  IMG3DVALUE      Height;           // Высота плоскости(вверх) = 0
  IMG3DVALUE      RelativeHeight;   // Высота расположения плоскости относительно
                                    // средней высоты метрики объекта:
                                    //       положительная - вверх,
                                    //       отрицательная - вниз
  long            Count;            // Количество узлов
  long            Reserve;          
}
  F3DHORIZONT;

typedef struct F3DMARKBYLINE        // ЗНАК ПО ЛИНИИ
{
  IMG3DVALUE      Height;           // Высота знака (по Y)
  IMG3DVALUE      RelativeHeight;   // Высота расположения знака относительно
                                    // метрики
  IMG3DVALUE      Distance;         // Расстояние по линии между знаками
  F3DMARK         Mark;             // Описание знака
}
  F3DMARKBYLINE;

typedef struct F3DMARKBYSQUARE      // ЗНАК ПО ПЛОЩАДИ
{
  IMG3DVALUE      Height;           // Высота знака (по Y)
  IMG3DVALUE      RelativeHeight;   // Высота расположения знака относительно
                                    // метрики
  IMG3DVALUE      DistanceX;        // Расстояние по оси X между знаками
  IMG3DVALUE      DistanceZ;        // Расстояние по оси Z между знаками
  F3DMARK         Mark;             // Описание знака
}
  F3DMARKBYSQUARE;

typedef struct F3DHORIZONTBYLINE    // Горизонтальная плоскость по линии
{
  IMG3DVALUE      Height;           // Высота плоскости(вверх)(= 0)
  IMG3DVALUE      RelativeHeight;   // Высота расположения плоскости относительно
                                    // метрики объекта
  IMG3DVALUE      WidthPlane;       // Ширина плоскости
  IMG3DVALUE      Removal;          // Смещение плоскости по поверхности,
                                    // относительно метрики объекта(пока нет)
  long            SurfaceFlag;      // Флаг расположения плоскости относительно
                                    // поверхности: ALLBYRELIEF, ALLFREE(см. выше)
  long            Count;            // Количество узлов
}
  F3DHORIZONTBYLINE;


typedef struct F3DSQUARECYLINDER    // Цилиндр горизонтальный погруженный по
                                    // площади (четыре точки)
{
  IMG3DVALUE      Height;           // Высота видимой части основания
                                    // (если ноль-отображается половина цилиндра)
  IMG3DVALUE      RelativeHeight;   // Высота расположения фигуры относительно
                                    // метрики
  unsigned long   Part;             // Отображаемые части (IMG3D_ALL - IMG3D_CLIP)
  unsigned long   Direct;           // 0 - вдоль самого длинного отрезка метрики
                                    // объекта, 1 - поперек
  unsigned long   Reserve;
  long            Count;            // Количество узлов
}
  F3DSQUARECYLINDER;

#define F3DFLATLINE F3DVERTBYLINE           // Height - ширина линии
#define F3DSURFACE  F3DHORIZONT             // RelativeHeight - без параметров
#define F3DLINEBYSURFACE F3DHORIZONTBYLINE  //( в диалоге нет SurfaceFlag;
                                            //  RelativeHeight;)

typedef struct SECTCIRCLE           // Параметры окружности
{
  IMG3DVALUE  Radius;               // Pадиус окружности
}
  SECTCIRCLE;

typedef struct SECTRECT             // Параметры прямоугольника
{
  IMG3DVALUE  Heigth;               // Высота
  IMG3DVALUE  Width;                // Ширина
  char        FlagHide[8];           // 1 - спрятать сторону
                                    // стороны считаются по часовой стрелке
                                    // по напр метрики. первая - верх.
}
  SECTRECT;

typedef struct SECTMOUND             // Параметры трапеции
{
  IMG3DVALUE  Heigth;                // Высота
  IMG3DVALUE  WidthTop;              // Ширина верха
  IMG3DVALUE  WidthBase;             // Ширина основания
  char        FlagHide[8];           // 1 - спрятать сторону
                                     // стороны считаются по часовой стрелке
                                     // по напр метрики. первая - верх.
}
  SECTMOUND;



typedef struct F3DSECTIONBYLINE     // Линия c заданным сечением
{
  IMG3DVALUE      Height;           // Высота плоскости(вверх)(= высоте эл-та)
  IMG3DVALUE      RelativeHeight;   // Высота расположения центра сечения относительно
                                    // метрики объекта
  IMG3DVALUE      Removal;          // Смещение сечения по поверхности,
                                    // относительно метрики объекта(пока нет)
  long            SurfaceFlag;      // Флаг расположения сечения относительно
                                    // поверхности: ALLBYRELIEF, ALLFREE(см. выше)
  long            PlugFlag;         // Отображение сечений первой,последней точки
                                    // IMG3D_BEGIN | IMG3D_END
  long            Type;             // Тип сечения линии:
                                    // (геометрический центр - по линии)
                                    // SECT_CIRCLE - окружность
                                    // SECT_RECT - прямоугольник
                                    // SECT_MOUND - трапеция(насыпь)
  long            Length;           // Длина параметров сечения(вместе с метрикой)
  long            Count;            // Количество узлов
  long            Reserv;           // Резерв
}
  F3DSECTIONBYLINE;

//******************************************************************
//                          НАБОР ФУНКЦИЙ                          *
//******************************************************************
// Следующие структуры образуют описание 3D объекта располагаясь
// последовательно друг за другом в зависимости от вида объекта

typedef struct F3DTREE              // Набор функций
{
  unsigned long     Ident;          // Идентификатор записи 0x73DD73DD
  long              Length;         // Длина записи
  long              MaxIdent;       // Максимальный использованный
                                    // идентификатор функции
  long              Count;          // Количество функций
                                    // Далее заголовки,параметры и метрика функций
}
  IMG3DTREE;


typedef struct F3DHEAD              // ЗАГОЛОВОК ЧАСТИ ПАРАМЕТРОВ
{
  unsigned long     Length;         // Длина параметров >= 4
                                    // (включая sizeof(F3DHEAD))
  unsigned long     Number;         // Номер функции
  long              Ident;          // Идентификатор функции
  long              Reserve;        // Резерв
                                    // Далее идут параметры соответствующей
                                    // функции (по Number)
}
  F3DHEAD;


typedef struct IMG3DNODE            // УЗЕЛ
{
  long              Length;         // Длина записи
  long              Reserve1;       
  IMG3DVALUE        Size[3];        // Размеры узла (ширина(по X), высота(по Y),
                                    //               длина(по Z))
  long              Count;          // Количество описаний
  long              Reserve2;       
}
  IMG3DNODE;

                                 // ФЛАГ ПОВТОРЯЕМОСТИ ТЕКСТУР
#define REPEAT_NOT    0          // Не повторять (тянуть)
#define REPEAT_HOR    1          // По горизонтали
#define REPEAT_VER    2          // По вертикали
#define REPEAT_ALL    3          // По обоим направлениям

enum TEXTUREMEASURE              // Тип размера текстуры
{
  texGMetr    = 1,               // Размер текстуры по горизонтали в метрах
  texGUnit    = 2,               // Размер текстуры по горизонтали в разах
  texVMetr    = 4,               // Размер текстуры по вертикали в метрах
  texVUnit    = 8,               // Размер текстуры по вертикали в разах
};


// Если цвет берется из семантики SemColorFlag = 1
// умалчиваемый цвет лежит:
//      как COLORREF в ((IMG3DVALUE*)&(Desc->Color))->Value
//      A - компонент в ((IMG3DVALUE*)&(Desc->Color))->Factor
//      Прозрачность для цвета по семантике берется из умалчиваемого цвета
// номер семантики со значением цвета в COLORREF лежит в
// ((IMG3DVALUE*)&(Desc->Color))->Type

typedef struct IMG3DDESCRIPTION     // ОПИСАНИЕ
{
  long              Length;         // Длина записи
  char              ColorFlag;      // 1 - наличие цвета,0 - отсутствие
  char              MaterialFlag;   // 1 - наличие материала,0 - отсутствие
  char              TextureFlag;    // 1 - наличие текстуры,0 - отсутствие
  char              SemColorFlag;   //             =    IMG3DVALUE RGBA  value COLORREF
  IMG3DRGBA         Color;          // Цвет (RGBA)
  ACT3DMATERIALMODE Material;       // Материал
  long              Transparent;    // Прозрачность (0-нет, 1-прозрачна)
  long              Smooth;         // Размытость цветов(0-нет, 1-размыта)
  TEXTURETYPE       Texture;        // Информация о текстуре
  char              FlagMeasure;    // Тип размера текстуры TEXTUREMEASURE
  char              TransparentTex; // Прозрачность текстуры (0,1)
  char              SmoothTex;      // Размытость текстуры (0,1)
  char              WrapTex;        // Повторяемость текстуры
                                    // (см.ФЛАГ ПОВТОРЯЕМОСТИ ТЕКСТУР)
  long              Reserve1;       
  IMG3DVALUE        WrapValue[2];   // Значения повторяемости текстуры по
                                    // двум текстурным координатам(или 0 при
                                    // произвольной повторяемости)
  long              Count;          // Количество элементов с таким описанием
  long              Reserve2;       
}
  IMG3DDESCRIPTION;

typedef struct IMG3DELEMENT         // ЭЛЕМЕНТ
{
  long              Length;         // Длина записи
  long              Type;           // Параметры и метрика по типу
                                    //   IMG3D_ANY - произвольный,
                                    //   IMG3D_CUBE - куб,
                                    //   IMG3D_SPHERE - сфера,
                                    //   IMG3D_CYILINDER - цилиндр,
                                    //   IMG3D_CONE - конус,
                                    //   IMG3D_QUAD - четырехугольник,
                                    //   IMG3D_ADJOINQUAD - примыкающий
                                    //                      четырехугольник,
                                    //   IMG3D_COMBPOLYGON - связанный
                                    //                       многоугольник,
                                    //   IMG3D_LINE - линия.
                                    // Метрика по типу


}
 IMG3DELEMENT;

//******************************************************************
//                    МЕТРИКА ПО ТИПУ ЭЛЕМЕНТА                     *
//  (вершины у многоугольников должны стоять в направлении против  *
//   часовой стрелки)                                              *
//******************************************************************


typedef struct IMG3DCUBE            // (1)   КУБ
{
  IMG3DPOINT     Point;             // Координаты точки привязки элемента
                                    // относительно нуля знака(передняя левая
                                    // нижняя вершина-первая точка)
  IMG3DROTATION  Rotate;            // Поворот элемента в системе
                                    // координат знака
  float          Width;             // Ширина
  float          Height;            // Высота
  float          Depth;             // Глубина
  unsigned long  Reserve;           // Резерв
}
  IMG3DCUBE;


typedef struct IMG3DSPHERE          // (2) СФЕРА
{
  IMG3DPOINT     Point;             // Координаты точки привязки элемента
                                    // относительно нуля знака
  IMG3DROTATION  Rotate;            // Поворот элемента в системе
                                    // координат знака
  float          Radius;            // Радиус
  unsigned long  Reserve;           // Резерв
}
  IMG3DSPHERE;

// Отображаемые части (флажки можно объединять)
#define IMG3D_SIDES   1             // Отображать стороны
#define IMG3D_BOTTOM  2             //            низ
#define IMG3D_TOP     4             //            верх
#define IMG3D_CLIP    8             // Не отображать невидимую часть
#define IMG3D_BEGIN   16            // Отображать сечение в первой точке метрики
#define IMG3D_END     32            // Отображать сечение в последней точке метрики


typedef struct IMG3DCYLINDER        // (3) ЦИЛИНДР (КОНУС)
{
  IMG3DPOINT     Point;             // Координаты точки привязки элемента
                                    // относительно нуля знака
  IMG3DROTATION  Rotate;            // Поворот элемента в системе
                                    // координат знака
  unsigned long  Part;              // Отображаемые части (IMG3D_ALL - IMG3D_BOTTOM)
  float          Radius;            // Радиус основания
  float          RadiusH;           // Радиус цилиндра на заданной высоте Height
                                    // или ноль(если это конус)
  float          Height;            // Высота
}
  IMG3DCILINDER;


typedef struct IMG3DQUAD            // (4,5) ЧЕТЫРЕХУГОЛЬНИК (ПРИМЫКАЮЩИЙ)
{
  IMG3DPOINT   Vertex[4];           // Координаты углов относительно нуля знака
}
  IMG3DQUAD;


#define IMG3DADJOINQUAD IMG3DQUAD   // (5) ПРИМЫКАЮЩИЙ ЧЕТЫРЕХУГОЛЬНИК
                                    // (первые две вершины дублируют последние
                                    //  две вершины предыдущего элемента)


typedef struct IMG3DCOMBPOLYGON     // (6) СВЯЗАННЫЙ ВЫПУКЛЫЙ МНОГОУГОЛЬНИК
{
  long         Count;               // Число углов(все они связаны с точками
                                    // других элементов)
  long         Reserve;             
  IMG3DPOINT   Vertex[1];           // Координаты углов(по числу), относительно
                                    // нуля знака
}
  IMG3DCOMBPOLYGON;


typedef struct IMG3DLINE            // (11) ЛИНИЯ СПЛОШНАЯ
{
  long         Count;               // Число вершин ломаной
  float        Width;               // Ширина линии
  IMG3DPOINT   Vertex[1];           // Координаты вершин(по числу), относительно
                                    // нуля знака
}
  IMG3DLINE;


//******************************************************************
//          СТРУКТУРЫ  ДЛЯ ВЫДЕЛЕНИЯ ЧАСТИ ИЗОБРАЖЕНИЯ             *
//******************************************************************

typedef struct SELECTPART           // ОПИСАНИЕ ВЫДЕЛЯЕМОЙ ЧАСТИ ИЗОБРАЖЕНИЯ
{
  long          Function;           // Номер функции в таблице визуализации
                                    // (см.выше)     (0 для всего изображения)
  long          Node;               // Номер узла    (0 для всей функция)
  long          Description;        // Номер описания(0 для всего узла)
  long          Element;            // Номер элемента(0 для всего описания)
}
   SELECTPART;

#endif  // M3DGDI_H

