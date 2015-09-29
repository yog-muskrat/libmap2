
#ifndef MAPCUTOB_H
#define MAPCUTOB_H

#ifndef MAPBITS_H
 #include "mapbits.h"
#endif

#ifndef MEASURE_H
 #include "measure.h"
#endif

#ifndef MAPINFO_H
 #include "mapinfo.h"
#endif

#ifndef MAPSELC_H
 #include "mapselc.h"
#endif

// Максимальное число точек пересечения на одном отрезке
#define MAXPOINTCROSS       100

// Число точек пересечения для минимального размера буфера
#define MAXPOINT            1000

// Точность для метрики типа float
#define PRECISION           -1

// Константа для определения точности карты
#define CONSTANTSCALE       100000.

// Константа для проверки количества подобъектов
#define COUNTBITS           1024*64

#define DELTA_ANGLE M_PI/180.

enum {
       pcOFF    = 0,     // не обработана
       pcLINE   = 1,     // обработано одно напрвление (для линейных)
       pcSQUARE = 2      // обработаны все направления (для площадных)
     };

enum {                  // какие точки метрики использовать
       pcBEFORE = 1,    // до точки пересечения
       pcAFTER  = 2,    // после точки пересечения
       pcALL    = 3,    // и до, и после
       pcNO     = 4,    // ни до, ни после
     };

enum {
       pcINSIDE   = 1,  // входит
       pcOUTSIDE  = 2,  // за пределами
       pcCUTSUB   = 3   // обработка только подобъектов
     };

typedef struct POINTCROSS
{
  DOUBLEPOINT XY;    // координата точки пересечения
  double       H;    // высота точки пересечения
  LONGPOINT Num;     // между какими точками пересекаемого
                     // объекта находится точка пересечения
  LONGPOINT NumAd;   // между какими точками пересекающего
                     // объекта находится точка пересечения
  int Work;          // признак обработки точки
                     // OFF - не обработана
                     // LINE  - обработана для линейных
                     // SQUARE - обработана для площадных
  int  Inside;       // признак забора метрики
                     // enum INSIDE для PointCross
}
  POINTCROSS;


typedef struct POINTBEAK
{
  int Number;        // Номер точки метрики
  int Process;       // Признак участия точки в процессе обработки
}
  POINTBEAK;

class _DLLCLASS TObjectCutSubject;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++  TPointCross ++++++++++++++++++++++++
// ++++ КЛАСС : НАХОЖДЕНИЕ ТОЧЕК ПЕРЕСЕЧЕНИЯ ДВУХ МЕТРИК +++
//                  БЕЗ ПОДОБ'ЕКТОВ !!!
// ПЕРВЫЙ ОБ'ЕКТ - по которому режут (обязательно замкнутый)
// ВТОРОЙ ОБ'ЕКТ - который режут (произвольный)
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TPointCross
{
  public:

  enum WORK
  {
    OFF    = pcOFF,     // не обработана
    LINE   = pcLINE,    // обработано одно напрвление (для линейных)
    SQUARE = pcSQUARE   // обработаны все направления (для площадных)
  };

  enum FLAGINSIDE       // какие точки метрики использовать
  {
    BEFORE = pcBEFORE,  // до точки пересечения
    AFTER  = pcAFTER,   // после точки пересечения
    ALL    = pcALL,     // и до, и после
    NO     = pcNO,      // ни до, ни после
  };

  // Признак расположения линейного объекта с подобъектами
  // относительно первого
  enum PLACELINE
  {
    INSIDE  = pcINSIDE,    // входит
    OUTSIDE = pcOUTSIDE,   // за пределами
    CUTSUB  = pcCUTSUB,    // обработка только подобъектов
  };

  TPointCross();
  ~TPointCross();

  // info1 - 1 объект (замкнутый), по которому режут ( например рамка)
  // info2 - 2 объект (произвольный), который режут
  // method - метод нарезки объектов:
  //          LOCAL_LINE - линейный,
  //          LOCAL_SQUARE - площадной
  // subject2 - номер объекта/подобъекта 2 объекта (по умолчанию = 0)
  // subject1 - номер объекта/подобъекта 1 объекта (по умолчанию = 0)
  // precision - допуск для нахождения точек пересечения
  TPointCross(TObjectInfo *info1, TObjectInfo *info2, int method,
              int subject2 = 0, int subject1 = 0, double precision = PRECISION);

  // data1 - объект (замкнутый), по которому режут ( например рамка)
  // data2 - объект (произвольный), который режут
  // method - метод нарезки объектов:
  //          LOCAL_LINE - линейный,
  //          LOCAL_SQUARE - площадной
  // subject2 - номер объекта/подобъекта 2 объекта (по умолчанию = 0)
  // subject1 - номер объекта/подобъекта 1 объекта (по умолчанию = 0)
  // precision - допуск для нахождения точек пересечения
  // метрика объектов приведена к единой системе отсчета
  TPointCross(TDataEdit *data1, TDataEdit *data2, int method,
              int subject2 = 0, int subject1 = 0, double precision = PRECISION);

  // Освободить все ресурсы
  void CloseAll();

  // Загрузить объекты
  // method - метод нарезки объектов:
  //          LOCAL_LINE - линейный,
  //          LOCAL_SQUARE - площадной
  // subject2 - номер объекта/подобъекта 2 объекта (по умолчанию = 0)
  // subject1 - номер объекта/подобъекта 1 объекта (по умолчанию = 0)
  // precision - допуск для нахождения точек пересечения
  int LoadObjects(TObjectInfo* info1, TObjectInfo* info2, int method,
                  int subject2 = 0, int subject1 = 0,
                  double precision = PRECISION);
  int LoadObjects(TDataEdit *data1, TDataEdit *data2, int method,
                  int subject2 = 0, int subject1 = 0,
                  double precision = PRECISION);

  // Установить тип метрики и точность фильтрации точек
  int SetKindPrecision(TDataEdit *data,
                       double precision = PRECISION);

  // Вставить точки пересечения в метрику
  int InsertPointCross();

  // Код ошибки
  int Error() { return ErrorCode; }

  // Взять следующую точку пересечения(из массива PointCross2)
  // Исходным считается PointCross2
  // При ошибке возвращает 0
  int GetNextPoint(POINTCROSS *point1, POINTCROSS *point2);

  // Найти точку пересечения в массиве POINTCROSS
  int GetPointCross(DOUBLEPOINT *point, POINTCROSS *cross, int count);

  // Найти точку пересечения в массиве POINTCROSS
  int GetPointCrossEx(POINTCROSS *crossin, POINTCROSS *cross, int count);

  // Проверка на небходимость резки второго объекта по первому
  // data1 - объект (замкнутый), по которому режут ( например рамка)
  // data2 - объект (произвольный), который режут
  // метрика объектов д.б. приведена к единой системе отсчета
  // precision - допуск для нахождения точек пересечения
  // При ошибке или отсутствия необходимости резки
  // возвращает 0
  int IsCutObject(TDataEdit *data1, TDataEdit *data2,
                  double precision = -1);

  // Сбор одного объекта
  // pointcross - с какого массива точек пересечения начать
  //            = 1 с первого
  //            = 2 со второго ( по умолчанию )
  int _fastcall CollectorOneObject(TDataEdit *data, int subnum = 0,
                                   int pointcross = 2);

  // Удалить клювы
  int _fastcall DeleteBeak(TDataEdit *data);

  protected:

  // Проверка локализации исходных объектов
  int _fastcall ControlLocal(TDataEdit *data1, int method);


  // Загрузка данных для обработки
  int LoadData();

  // Приведение метрики к единой системе отсчета
  int UnitedData();

  // Приведение метрики выходного объекта к единой системе отсчета
  // dataout - метрика выходного объекта
  // infoin -  исходный объект
  // infoout - выходной объект
  int UnitedData(TDataEdit *dataout, TObjectInfo *infoin = 0,
                 TObjectInfo *infoout = 0);

  // Заполнить массив точек пересечения
  int SetAllPointCross();


  /*******************************************************************
  *            СОРТИРОВКА МАССИВА POINTCROSS                         *
  *******************************************************************/

  // Отсортировать массив POINTCROSS
  void _fastcall SortPointCross(POINTCROSS *mass, int count, TDataEdit *data);

  // Отсортировать координаты в массиве POINTCROSS
  void _fastcall SortCoordinamesPointCross(POINTCROSS *mass, int num, TDataEdit *data);

  // Отсортировать точки на отрезке
  // cross - массив точек пересечения
  // begin - начальный индекс в массиве cross
  // count - количество точек для сортировки
  int _fastcall SortPoint(POINTCROSS *cross, int begin, int count,
                DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);


 /*******************************************************************
 *            ВСПОМОГАТЕЛЬНЫЕ ПРОГРАММЫ                             *
 *******************************************************************/

  // Удалить точки с одинаковыми координатами из массива POINTCROSS
  void _fastcall DeletePointCross(POINTCROSS *cross, POINTCROSS *cross2,
                                  int *count,
                                  TDataEdit *data);

  // Заполнение структуры POINTCROSS
  void _fastcall SetPointCross(POINTCROSS *pointcross, DOUBLEPOINT *xy,
                     int begnum1, int endnum1, double h = 0,
                     int begnum2 = 0, int endnum2 = 0);

  // Определение средней точки на отрезке
  void _fastcall AveragePoint(POINTCROSS *pointcross, DOUBLEPOINT *point,
                    int begin, int end);

  // Сделать объект из подобъекта
  // dataout - куда
  // datain  - откуда
  // subnum  - номер подобъекта в datain
  int _fastcall CreateDataObject(TDataEdit *dataout, TDataEdit *datain,
                       int subnum = 0);

  // Пересылка метрики
  // out, in - куда, откуда
  // outsub, insub - номера объектов/подобъектов
  // direction - направление: 1 = сверху вниз, 0 - снизу вверх
  // begin, end - с какой по какую точки переслать
  int _fastcall MoveData(TDataEdit *out,  TDataEdit *in,
               int direction, int begin, int end,
               int outsub = 0, int insub = 0);

  // Взять метрику из объекта
  // dataout - куда добавлять точки
  // datin -   откуда брать точки
  // num - индекс в массиве точек пересечения объекта
  // subout - номер подобъекта, куда добавлять точки
  // возврат = 0 - ошибка
  //         > 0 - номер текущего элемента в PointCross1+1
  //         < 0 - метрика кончилась
  int _fastcall GetDataObject(TDataEdit *dataout, TDataEdit *datain,
                    POINTCROSS *cross, int num, int count,
                    int subout = 0);

  // Изменить направление обхода
  void _fastcall ChangeDirection(int in, int *out);


  /*******************************************************************
  *        РАССТАНОВКА ТОЧЕК ПЕРЕСЕЧЕНИЯ                             *
  *******************************************************************/

  // Расстановка точек пересечения объектов
  int PointCrossObj();

  // Пересечение отрезка и метрики объекта
  // xy1, xy2 - координаты отрезка
  // beg1, end1 - номера точек метрики отрезка
  // data - метрика разрезаемого объекта/подобъекта
  int _fastcall CrossLengthData(DOUBLEPOINT xy1, DOUBLEPOINT xy2,
                      int beg1, int end1, TDataEdit *data,
                      int countin, int excin);

  // Проверить на входимость предыдущую и последующую точки
  // относительно точки пересечения метрики
  // data1 - что проверяем
  // data2 - где проверяем
  // cross1 - первый массив точек пересечения
  // cross2 - второй массив точек пересечения
  // num - текущий номер в cross1
  // count - количество элементов в структуре POINTCROSS
  // flag1 - при простановке поля Inside взять за основу для cross1
  // flag2 - при простановке поля Inside взять за основу для cross2
  //       = 0 - пересечение объектов
  //       = 1 - объединение объектов
  // direct -  = 1 направление цифрования объектов совпадает
  //           = 0 направление цифрования объектов не совпадает
  int _fastcall GetInsidePointCross(TDataEdit *data1, TDataEdit *data2,
                        POINTCROSS *cross1, POINTCROSS *cross2,
                        int flag1, int flag2,
                        int num, int count, int direct);

  // Сделать подобъект
  // dataout - куда
  // datain  - откуда
  // subnum  - номер подобъекта в datain
  // all - = 1 - без проверки габаритов для площадных
  //       = 0 - с проверкой габаритов

  int _fastcall DoSubject(TDataEdit *dataout, TDataEdit *datain, int subnum = 0, int all = 0);

  // Определение подобъектов разрезаемого объекта, попадающих в
  // объект по которому режут
  // data - метрика разрезаемого объекта
  // dframe1 - габариты объекта, по которому режут
  // subnum -  номер подобъекта
  // возврат - 0 - ошибка,
  //           1 - объект/подобъект полностью принадлежит объекту
  //           2 - объект/подобъект пересекается с объектом
  int _fastcall InsideDimensions(TDataEdit *data, DFRAME dframe1, int subnum);

  //  Увеличить размер буфера для массива точек пересечения
  //  При ошибке возвращает ноль, иначе - новый размер буфера
  int Realloc();

  // Откорректировать массивы точек пересечения
  // cross1 - линейный объект
  // cross2 - площадной объект
  void _fastcall CorrectPointCrossALLNO(POINTCROSS *cross,
                                        int count);

  // Выставить более или менее правильную высоту  
  // cross1 - точки пересечения первого объекта (контура)
  // cross2 - точки пересечения второго объекта
  void SetHeightPointCross(POINTCROSS *cross1 = 0, POINTCROSS *cross2 = 0,
                           TDataEdit *data1 = 0, TDataEdit *data2 = 0,
                           int count = 0);

  // Вычислить точку на заданном расстоянии на заданной линии
  // x1, у1 - первая точка
  // x2, у2 - вторая точка
  // delta - расстояние
  // number - номер параметров для размещения результата
  void _fastcall SeekVirtualPointByDistance(double x1,double y1,
                                            double *x2,double *y2,
                                            double delta);

  // Оттянуть крайние точки метрики незамкнутого объекта
  // (первая и последняя точки)
  // delta - расстояниe
  int _fastcall DragPoints(TDataEdit *data1, double delta = 2,
                           int subject = 0);

  // Удалить петли
  int _fastcall DeleteLoop(TDataEdit *data);

  // Поменять местами точки пересечения, образующие клювы
  int _fastcall ChangePointCrossBeak(POINTCROSS *crossin,
                                     int count, int exc);

  // Инициализация переменных класса
  void InitPointCross();

  public:

  double Precision;             // Округление

  TObjectInfo *Info1;           // Исходные объекты
  TObjectInfo *Info2;

  int ErrorCode;                // Код ошибки
  int InsideObject1;            // При отсутствии точек пересечения
                                // полное вхождение первого объекта во второй
  int InsideObject2;            // При отсутствии точек пересечения
                                // полное вхождение 2-го объекта в первый
  int InsideObjectSub2;         // При отсутствии точек пересечения полное вхождение
                                // 2-го объекта в первый и пересечение c подобъектами
  int PlaceLine;                // При отсутствии точек пересечения для л
                                // инейного объекта с подобъектами,
                                // подлежащими резке - признак расположения
                                // линейного объекта с подобъектами
                                // относительно первого
                                //  - полное вхождение второго в первый = IN
                                //  - второй объект лежит в стороне     = OUT

  int Subject1;                 // Обрабатываемые подобъекты
  int Subject2;
  int FlagDirectSubject1;       // Признак изменения направления цифрования
  int FlagDirectSubject2;       // в подобъектах                  
  int RealPlace;                // Признак реальных координат
  int FlagDeleteEqualPoint;     // Признак удаления одинаковых точек
  int Local;                    // Признак локализации второго объекта
  int Kind;                     // Тип метрики
  int Direct;                   // Признак изменения направления цифрования
  int Direction;                // Признак совпадения направления цифрования
                                // замкнутых объектов
  int CountPointCross;          // Размер буфера под PointCross

  int All;                      // Признаки наличия хотя бы одной общей точки
  int No;

  POINTBEAK PointBeak1[MAXPOINT];// Точки - выбросы
  POINTBEAK PointBeak2[MAXPOINT];

  int IsFlagBeak;               // Флаг работы с массивом PointBeak
                                // 0 - на массив не обращать внимание
                                // 1 - корректировать метрику соответственно массиву

  int Full;                     // Для площадных объектов признак обработки
                                // подобъектов объекта-резака

  int FlagInsideObjects;        // Флаг проверки на входимость 2-го объекта в первый
                                // 0 - не проверять
                                // 1 - проверять                   

  TDataEdit Data1;              // Метрика обрабатываемых объектов
  TDataEdit Data2;

  POINTCROSS *PointCross1;      // Вспомогательные структуры
  POINTCROSS *PointCross2;
  int NumCross;                 // Число элементов в массивах
                                // PointCross1, PointCross2

  // От TObjectCutSubject
  TDataEdit *ObjectOut;         // Результирующий объект является
                                // полностью дополнением
  TDataEdit DataOut;            // Метрика выходного объекта

  // От TObjectCut
  TBitSet64K SubObject;         // Список подобъектов,
                                // попадающих в зону разрезания
  int    SubNum;                // Общее число подобъектов
  int    LoadSub;               // Флаг работы с классом подобъектов

  TDataEdit DataOutSub;         // Метрика выходного объекта
};

typedef  TPointCross TPOINTCROSSDATA;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++ ФУНКЦИИ НАХОЖДЕНИЯ ТОЧЕК ПЕРЕСЕЧЕНИЯ ДВУХ МЕТРИК +++
//                  БЕЗ ПОДОБ'ЕКТОВ !!!
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Загрузить объекты TObjectInfo1, TObjectInfo2
// precision - допуск для нахождения точек пересечения
int _fastcall pcLoadInfoObjects(TPOINTCROSSDATA *pc,
                                TObjectInfo *info1,
                                TObjectInfo *info2, int method,
                                int subject2, int subject1, double *precision);

// Загрузить объекты DATAEDIT 1, DATAEDIT 2
// precision - допуск для нахождения точек пересечения
int _fastcall pcLoadDataObjects(TPOINTCROSSDATA *pc,
                            TDataEdit *data1, TDataEdit *data2,
                            int method, int subject2, int subject1,
                            double *precision);

// Установить тип метрики и точность фильтрации точек
int _fastcall pcSetKindPrecision(TPOINTCROSSDATA *pc,
                                 TDataEdit *data, double *precision);

// Приведение метрики к единой системе отсчета
int _fastcall pcUnitedData(TPOINTCROSSDATA *pc);

// Приведение метрики выходного объекта к единой системе отсчета
// dataout - метрика выходного объекта
// infoin -  исходный объект
// infoout - выходной объект
int _fastcall pcUnitedDataOut(TPOINTCROSSDATA *pc,
                              TDataEdit *dataout,
                              TObjectInfo *infoin,
                              TObjectInfo *infoout);

//  Увеличить размер буфера для массива точек пересечения
//  При ошибке возвращает ноль, иначе - новый размер буфера
int _fastcall pcRealloc(TPOINTCROSSDATA *pc);

// Проверка локализации исходных объектов
int _fastcall pcControlLocal(TPOINTCROSSDATA *pc,
                             TDataEdit *data1, int method);

// Отсортировать массив POINTCROSS по возрастанию номеров точек
// в объекте и по координатам
void _fastcall pcSortPointCross(POINTCROSS *cross, int count,
                                TDataEdit *data);

// Отсортировать координаты в массиве POINTCROSS
void _fastcall pcSortCoordinamesPointCross
               (POINTCROSS *cross, int num, TDataEdit *data);

// Отсортировать точки
// cross - массив точек пересечения
// begin - начальный индекс в массиве cross
// count - количество точек для сортировки
int _fastcall pcSortPoint(POINTCROSS *cross, int begin, int count,
                          DOUBLEPOINT *xy1, DOUBLEPOINT *xy2);

// Найти точку пересечения в массиве POINTCROSS
int _fastcall pcGetPointCross(DOUBLEPOINT *point,
                              POINTCROSS *cross, int count);

int _fastcall pcGetPointCrossEx(POINTCROSS *crossin,
                               POINTCROSS *cross, int count);

// Удалить точки с одинаковыми координатами из массива POINTCROSS
void _fastcall pcDeletePointCross(TPOINTCROSSDATA *pc,
                                  POINTCROSS *cross,
                                  POINTCROSS *cross2,
                                  int *count,
                                  TDataEdit *data);

// Заполнение структуры POINTCROSS
void _fastcall pcSetPointCross(POINTCROSS *pointcross,
                               DOUBLEPOINT *xy,
                               int begnum1, int endnum1,
                               double h,int begnum2, int endnum2);

// Определение средней точки на отрезке
void _fastcall pcAveragePoint(POINTCROSS *pointcross, DOUBLEPOINT *point,
                              int begin, int end);

// Сделать объект из подобъекта
// dataout - куда
// datain  - откуда
// subnum  - номер подобъекта в datain
int _fastcall pcCreateDataObject(TDataEdit *dataout, TDataEdit *datain,
                                  int subnum);


// Пересылка метрики
// out, in - куда, откуда
// outsub, insub - номера объектов/подобъектов
// direction - направление: 1 = сверху вниз, 0 - снизу вверх
// begin, end - с какой по какую точки переслать
int _fastcall pcMoveData(TDataEdit *out, TDataEdit *in,
                         int direction, int begin, int end,
                         int outsub, int insub);

// Взять метрику из объекта
// dataout - куда добавлять точки
// datin -   откуда брать точки
// num - индекс в массиве точек пересечения объекта
// subout - номер подобъекта, куда добавлять точки
// возврат = 0 - ошибка
//         > 0 - номер текущего элемента в PointCross1+1
//         < 0 - метрика кончилась
int _fastcall pcGetDataObject(TPOINTCROSSDATA *pc,
                              TDataEdit *dataout, TDataEdit *datain,
                              POINTCROSS *cross, int num, int count,
                              int subout);

// Изменить направление обхода
void _fastcall pcChangeDirection(int in, int *out);

// Расстановка точек пересечения объектов
int _fastcall pcPointCrossObj(TPOINTCROSSDATA *pc);

// Сбор одного объекта
// data - куда класть метрику
// subnum - куда класть метрику (в какой подобъект)
// pointcross - с какого массива точек пересечения начать
//            = 1 с первого
//            = 2 со второго ( по умолчанию )
int _fastcall pcCollectorOneObject(TPOINTCROSSDATA *pc,
                                   TDataEdit *data, int subnum,
                                   int pointcross);

// Определение подобъектов разрезаемого объекта, попадающих в
// объект по которому режут
// data - метрика разрезаемого объекта
// dframe1 - габариты объекта, по которому режут
// subnum -  номер подобъекта
// возврат - 0 - ошибка,
//           1 - объект/подобъект полностью принадлежит объекту
//           2 - объект/подобъект пересекается с объектом
int _fastcall pcInsideDimensions(TDataEdit *data,
                                 DFRAME *dframe1, int subnum);

// Сделать подобъект
// dataout - куда
// datain  - откуда
// subnum  - номер подобъекта в datain
// all - = 1 - без проверки габаритов для площадных
//       = 0 - с проверкой габаритов
int _fastcall pcDoSubject(TPOINTCROSSDATA *pc,
                          TDataEdit *dataout, TDataEdit *datain,
                          int subnum, int all);

// Вставить точки пересечения в метрику
int _fastcall pcInsertPointCross(TPOINTCROSSDATA *pc);

// Проверка на небходимость резки второго объекта по первому
// data1 - объект (замкнутый), по которому режут ( например рамка)
// data2 - объект (произвольный), который режут
// метрика объектов д.б. приведена к единой системе отсчета
// precision - допуск для нахождения точек пересечения
// При ошибке или отсутствия необходимости резки
// возвращает 0
int _fastcall pcIsCutObject(TPOINTCROSSDATA *pc,
                            TDataEdit *data1, TDataEdit *data2,
                            double *precision);

// Выставить более или менее правильную высоту
// cross1 - точки пересечения первого объекта (контура)
// cross2 - точки пересечения второго объекта
void _fastcall pcSetHeightPointCross(POINTCROSS *cross1, POINTCROSS *cross2,
                                     TDataEdit *data1, TDataEdit *data2,
                                     int count);

// Откорректировать массивы точек пересечения
void _fastcall pcCorrectPointCrossALLNO(TPOINTCROSSDATA *pc,
                                        POINTCROSS *cross,
                                        int count);

// Откорректировать массивы точек пересечения
//void _fastcall pcCorrectPointCrossALL(TPOINTCROSSDATA *pc,
//                                      POINTCROSS *cross1, POINTCROSS *cross2,
//                                      int *count, int exc);

// Проверить на входимость предыдущую и последующую точки
// относительно точки пересечения метрики
// data1 - что проверяем
// data2 - где проверяем
// cross1 - первый массив точек пересечения
// cross2 - второй массив точек пересечения
// num - текущий номер в cross1
// count - количество элементов в структуре POINTCROSS
// flag1 - при простановке поля Inside взять за основу для cross1
// flag2 - при простановке поля Inside взять за основу для cross2
//       = 0 - пересечение объектов
//       = 1 - объединение объектов
// direct -  = 1 направление цифрования объектов совпадает
//           = 0 направление цифрования объектов не совпадает
int _fastcall pcGetInsidePointCross(TPOINTCROSSDATA *pc,
                                    TDataEdit *data1, TDataEdit *data2,
                                    POINTCROSS *cross1, POINTCROSS *cross2,
                                    int flag1, int flag2,
                                    int num, int count, int direct);

// Вычислить точку на заданном расстоянии на заданной линии
// от начальной точки
// x1, у1 - начальная точка
// x2, у2 - конечная точка
// delta - расстояние
// результат в конечной точке
void _fastcall pcSeekVirtualPointByDistance(double x1,double y1,
                                            double *x2,double *y2,
                                            double delta);

// Оттянуть крайние точки метрики незамкнутого объекта
// (первая и последняя точки)
// delta - расстояниe
int _fastcall pcDragPoints(TDataEdit *data1, double delta, int subject);


// Определить отсутствие промежуточных точек в массиве точек пересечения
// count - количество точек в метрике
// Если точек нет возвращает 1
int _fastcall pcGetFreePoint(TPOINTCROSSDATA *pc,
                             POINTCROSS *prev, POINTCROSS *next,
                             int count, int exclusive,
                             int nprev, int nnext);

// Определить точку для проверки на входимость
// count - количество точек в метрике
// Если точки нет возвращает 0
int _fastcall pcGetInsidePoint(POINTCROSS *prev, POINTCROSS *next,
                               TDataEdit *data, int count,
                               DOUBLEPOINT *point,
                               int nprev, int nnext);

// Удалить клювы
int _fastcall pcDeleteBeak(TPOINTCROSSDATA *pc,TDataEdit *data);

// Поменять местами точки пересечения, образующие клювы
int _fastcall pcChangePointCrossBeak(TPOINTCROSSDATA *pc,
                                     POINTCROSS *crossin,
                                     int count, int exc);

                                     
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++ ФУНКЦИИ : ПЕРЕСЕЧЕНИЕ ОБ'ЕКТА И ПОДОБ'ЕКТА  ++++++++++
//      ( от объекта отрезать область подобъекта )
// ПЕРВЫЙ ОБ'ЕКТ - по которому режут (обязательно замкнутый)
// ВТОРОЙ ОБ'ЕКТ - который режут (произвольный)
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Загрузить объекты
int _fastcall csLoadDataObjects(TPOINTCROSSDATA *pc,
                                TDataEdit *data1, TDataEdit *data2,
                                int method, int subject,
                                double *precision);

// Проставить флаг забора метрики в массивы PointCross1, PointCross2
int _fastcall csSetInside(TPOINTCROSSDATA *pc);

// Взять следующий объект (только для площадных)
TDataEdit *_fastcall csGetNextObject(TPOINTCROSSDATA *pc);

// Сбор одного объекта
int _fastcall csCollectorOneObject(TPOINTCROSSDATA *pc, TDataEdit *data, int subnum);

// Откорректировать массивы точек пересечения
// cross1 - площадной объект
// cross2 - площадной объект
int _fastcall csCorrectPointCross(TPOINTCROSSDATA *pc,
                                  POINTCROSS *cross1, POINTCROSS *cross2,
                                  TDataEdit *data1, TDataEdit *data2,
                                  int count);

// Определить положение точек относительно объектов
// возвращает BEFORE - если обе точки лежат в объекте
//            ALL    - только одна точка лежит в объекте
int _fastcall csGetPlacePoint(DOUBLEPOINT *point1, DOUBLEPOINT *point2,
                              TDataEdit *data1,TDataEdit *data2);



// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++ КЛАСС : ПЕРЕСЕЧЕНИЕ ОБ'ЕКТА И ПОДОБ'ЕКТА  ++++++++++
//      ( от объекта отрезать область подобъекта )
// ПЕРВЫЙ ОБ'ЕКТ - по которому режут (обязательно замкнутый)
// ВТОРОЙ ОБ'ЕКТ - который режут (произвольный)
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TObjectCutSubject : public TPointCross
{
  public:

  //*********************************************************
  //  ОСНОВНЫЕ ФУНКЦИИ
  //  TObjectCutSubject - конструктор,
  //  LoadObjects - загрузить объект,
  //  GetNextObject - взять следующий объект
  //*********************************************************

  TObjectCutSubject();

  // info1 - область объектa
  // info2 - область объекта, откуда взять подобъект
  // subject - номер подобъекта 2 объекта (по умолчанию = 0)
  // метрика объектов должна быть приведена к единой системе отсчета
  TObjectCutSubject(TObjectInfo *info1, TObjectInfo *info2,
                    int method = LOCAL_SQUARE,
                    int subject = 0,
                    double precision = PRECISION);

  // data1 - область объектa
  // data2 - область объекта, откуда взять подобъект
  // subject - номер подобъекта 2 объекта (по умолчанию = 0)
  // метрика объектов будет приведена к единой системе отсчета
  TObjectCutSubject(TDataEdit *data1, TDataEdit *data2,
                    int method = LOCAL_SQUARE,
                    int subject = 0,
                    double precision = PRECISION);

  // Загрузить объекты
  int LoadObjects(TObjectInfo* info1, TObjectInfo* info2,
                  int method = LOCAL_SQUARE,
                  int subject = 0, double precision = PRECISION);

  // Загрузить объекты
  int LoadObjects(TDataEdit *data1, TDataEdit *data2,
                  int method = LOCAL_SQUARE,
                  int subject = 0, double precision = PRECISION);

  // Взять следующий объект
  // При ошибке возвращает 0
  TDataEdit *GetNextObject();


  //*********************************************************
  //  ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ ПРОМЕЖУТОЧНЫХ РЕЗУЛЬТАТОВ
  //*********************************************************

  // Сбор одного объекта
  int CollectorOneObject(TDataEdit *data, int subnum = 0);

  protected:

  // Проставить флаг забора метрики в массивы PointCross1, PointCross2
  int SetInside();

  // Откорректировать массивы точек пересечения
  // cross1 - линейный объект
  // cross2 - площадной объект
  int _fastcall CorrectPointCross(POINTCROSS *cross1,
                                  POINTCROSS *cross2,
                                  TDataEdit *data1,
                                  TDataEdit *data2,
                                  int count);

  // Определить положение точек относительно объектов
  // возвращает BEFORE - если обе точки лежат в объекте
  //            ALL    - только одна точка лежит в объекте
  int _fastcall GetPlacePoint(DOUBLEPOINT *point1,
                              DOUBLEPOINT *point2,
                              TDataEdit *data1,
                              TDataEdit *data2);
};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++  TObjectCut  ++++++++++++++++++++++++
// +++++++++++++ КЛАСС : ПЕРЕСЕЧЕНИЕ ОБ'ЕКТОВ  +++++++++++++
// ПЕРВЫЙ ОБ'ЕКТ - объект (без подобъектов, замкнутый),
//                 по которому режут ( например рамка)
// ВТОРОЙ ОБ'ЕКТ - объект (c подобъектами, произвольный),
//                 который режут
// method - метод нарезки объектов:
//          LOCAL_LINE - линейный,
//          LOCAL_SQUARE - площадной
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TObjectCut : public TPointCross
{

 public:

  //*********************************************************
  //  ОСНОВНЫЕ ФУНКЦИИ
  //  TObjectCut - конструктор,
  //  LoadObjects - загрузить объект,
  //  GetNextObject - взять следующий объект
  //*********************************************************

  TObjectCut();
  ~TObjectCut();

  // Конструктор класса TObjectCut
  // info1 - объект (без подобъектов, замкнутый),
  //         по которому режут ( например рамка)
  // info2 - объект (c подобъектами, произвольный), который режут
  // method - метод нарезки объектов:
  //          LOCAL_LINE - линейный,
  //          LOCAL_SQUARE - площадной
  // full - для площадных объектов признак обработки
  //        подобъектов объекта-резака (если они есть)
  TObjectCut(TObjectInfo* info1, TObjectInfo* info2, int method,
             double precision = PRECISION, int full = 0);

  // Конструктор класса TObjectCut
  // data1 - объект (без подобъектов, замкнутый),
  //         по которому режут ( например рамка)
  // data2 - объект (c подобъектами, произвольный), который режут
  // method - метод нарезки объектов:
  //          LOCAL_LINE - линейный,
  //          LOCAL_SQUARE - площадной
  // метрика объектов приведена к единой системе отсчета
  // full - для площадных объектов признак обработки
  //        подобъектов объекта-резака (если они есть)
  TObjectCut(TDataEdit *data1, TDataEdit *data2, int method,
             double precision = PRECISION, int full = 0);

  // Загрузить объекты
  // precision - допуск для нахождения точек пересечения
  // full - для площадных объектов признак обработки
  //        подобъектов объекта-резака (если они есть)
  int LoadObjects(TObjectInfo* info1, TObjectInfo* info2, int method,
                  double precision = PRECISION, int full = 0);
  int LoadObjects(TDataEdit *data1, TDataEdit *data2, int method,
                  double precision = PRECISION, int full = 0);
  int LoadObjects(TDataEdit *data1, TDataEdit *data2, int method, int subject,
                  double precision = PRECISION, int full = 0);

  // Взять следующий объект
  // Если у линейного объекта есть подобъекты -
  // возвращает объект с подобъектами,
  // иначе часть линейного объекта как сомостоятельный объект
  // К площадным это не относится
  // При ошибке возвращает 0
  TDataEdit *GetNextObject();


  //*********************************************************
  //  ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ ПРОМЕЖУТОЧНЫХ РЕЗУЛЬТАТОВ
  //*********************************************************

  // Освободить все ресурсы
  void CloseAll();

  // Инициализация переменных класса
  void InitObjectCut();

  // Проставить флаг забора метрики в массивы PointCross1, PointCross2
  int SetInside();

  // Определение подобъектов разрезаемого объекта, попадающих в
  // объект по которому режут
  // data1 - метрика объекта, по которому режут
  // data2 - метрика разрезаемого объекта
  int InsideSubObject(TDataEdit *data1, TDataEdit *data2);

  // Взять очередной объект при работе с подобъектами
  // num  - номер подобъекта в datain
  int GetNextObjectSub(int num, int loadsub = 0);

  // Порезать и добавить оставшиеся подобъекты для линейных объектов
  int AppendLineSubject();

  // Проверить пересечение исходного объекта(по которому режут),
  // с габаритами подобъекта объекта(который режут)
  // data1 - по которому режут
  // data2 - который режут
  // subject - подобъект объекта, который режут
  int InsideDimentionsSubject(TDataEdit *data1, TDataEdit *data2,
                              int subject);

  public:

  TObjectCutSubject * Subcut;   // Класс работы с подобъектами TObjectCutSubject
};

// +++++++++++ ФУНКЦИИ : ПЕРЕСЕЧЕНИЕ ОБ'ЕКТОВ  +++++++++++++
// ПЕРВЫЙ ОБ'ЕКТ - объект (без подобъектов, замкнутый),
//                 по которому режут ( например рамка)
// ВТОРОЙ ОБ'ЕКТ - объект (c подобъектами, произвольный),
//                 который режут
// method - метод нарезки объектов:
//          LOCAL_LINE - линейный,
//          LOCAL_SQUARE - площадной
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Загрузить объекты
int _fastcall coLoadInfoObjects(TPOINTCROSSDATA *pc,
                                TObjectInfo *info1, TObjectInfo *info2,
                                int method, double *precision, int full);

int _fastcall coLoadDataObjects(TPOINTCROSSDATA *pc,
                                TDataEdit *data1, TDataEdit *data2,
                                int method, double *precision, int full);

int _fastcall coLoadSubjectObjects(TPOINTCROSSDATA *pc,
                                   TDataEdit *data1, TDataEdit *data2,
                                   int method, int subject,
                                   double *precision, int full);

// Проставить флаг забора метрики в массивы PointCross1, PointCross2
int _fastcall coSetInside(TPOINTCROSSDATA *pc);

// Определение подобъектов разрезаемого объекта, попадающих в
// объект по которому режут
// data1 - метрика объекта, по которому режут
// data2 - метрика разрезаемого объекта
int _fastcall coInsideSubObject(TPOINTCROSSDATA *pc,
                                TDataEdit *data1, TDataEdit *data2);

// Взять следующий объект
// Если у линейного объекта есть подобъекты -
// возвращает объект с подобъектами,
// иначе часть линейного объекта как сомостоятельный объект
// К площадным это не относится
TDataEdit *_fastcall coGetNextObject(TObjectCut * pc);

// Проверить пересечение исходного объекта(по которому режут),
// с габаритами подобъекта объекта(который режут)
// data1 - по которому режут
// data2 - который режут
// subject - подобъект объекта, который режут
int _fastcall coInsideDimentionsSubject(TDataEdit *data1,
                                        TDataEdit *data2,
                                        int subject);

// Порезать и добавить оставшиеся подобъекты для линейных объектов
int _fastcall coAppendLineSubject(TObjectCut *pc);

// Взять очередной объект при работе с подобъектами
// dataout - куда
// datain  - откуда
// subnum  - номер подобъекта в datain
int _fastcall coGetNextObjectSub(TObjectCut * pc, int num, int loadsub);


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++ КЛАСС : ОБ'ЕДИНЕНИЕ ОБ'ЕКТОВ                    ++++
// ++++ Метрика в должна быть единой системе отсчета!   ++++
// Если не можем сразу собрать объект,
// то запускаем еще раз, предварительно дотянув объекты
// друг до друга по допуску дотяга (это долго).
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TObjectUnion : public TObjectCut

{

  public:

  //*********************************************************
  //  ОСНОВНЫЕ ФУНКЦИИ
  //  TObjectUnion - конструктор,
  //  LoadObjects - загрузить объект,
  //  GetObject - взять объект
  //*********************************************************

  TObjectUnion();
  ~TObjectUnion();

  // data1 -  1 объект
  // data2 -  2 объект
  // method - метод сборки объектов:
  //          LOCAL_LINE - линейный,
  //          LOCAL_SQUARE - площадной
  // limit - допуск дотяга
  // precision - допуск для нахождения точек пересечения
  // метрика объектов приведена к единой системе отсчета
  TObjectUnion(TDataEdit *data1, TDataEdit *data2, int method,
               double limit = PRECISION, double precision = PRECISION);

  // Загрузить объекты
  // method - метод сборки объектов:
  //          LOCAL_LINE - линейный,
  //          LOCAL_SQUARE - площадной
  // limit - допуск дотяга
  // precision - допуск для нахождения точек пересечения
  int LoadObjects(TDataEdit *data1, TDataEdit *data2, int method,
                  double limit = PRECISION, double precision = PRECISION);

  // Взять полученный объект
  TDataEdit *GetObject();

  protected:

  // Загрузка данных для обработки
  int LoadData();

  // Сбор одного объекта
  int _fastcall CollectorOneObjectLine(TDataEdit *data);

  // Проставить флаг забора метрики в массивы PointCross1, PointCross2
  int SetInside();

  // Собрать подобъект площадного объекта
  int GetSubjectSquare();

  // Собрать линейный объект
  TDataEdit *GetObjectLine();

  // Собрать подобъект линейного объекта
  int _fastcall GetSubjectLine(TDataEdit *dataout, TObjectUnion *objectunion);

  // Собрать площадной полностью
  TDataEdit *GetObjectSquare();

  // Сделать пересечение подобъектов объекта datain
  // с подобъктами результирующего объекта
  int _fastcall GetSubjectSubjectSquare(TDataEdit *data1,
                                        TDataEdit *data2);

  // Сделать пересечение подобъектов с объектом
  // datain - объект (Data1 или Data2)
  // bitin - биты подобъектов результирующего объекта
  int _fastcall GetSubjectObjectSquare(TDataEdit *datain,
                                       TBitSet64K *bitin);

  // Выставить биты соответствия подобъектов результата и
  // подобъектов объектов исходных данных
  int SetBitsSubjects();

  // Выделить память под Result
  int AllocateResult();

  // Откорректировать массивы точек пересечения
  // cross1 - линейный объект
  // cross2 - площадной объект
  void _fastcall CorrectPointCross(POINTCROSS *cross1,
                                   POINTCROSS *cross2,
                                   TDataEdit *data1,
                                   TDataEdit *data2,
                                   int count, int direct);

  // Определить положение точек относительно объектов
  // возвращает BEFORE - если обе точки лежат в объекте
  //            ALL    - только одна точка лежит в объекте
  int _fastcall GetPlacePoint(DOUBLEPOINT *point1, DOUBLEPOINT *point2,
                              TDataEdit *data1, TDataEdit *data2);

  // Дотянуть метрику объектов по Limit
  int AdjustPoint(TDataEdit *data1, TDataEdit *data2);

 // Проверить, можно ли дотягивать точку
 int CheckAdjustPoint(TDataEdit *data,DOUBLEPOINT * xy1,DOUBLEPOINT * xy2);

 int CheckPointCross(double x,double y);

 // Установить Limit по минимальному расстоянию
 int DefineLimit(TDataEdit *data1, TDataEdit *data2);

 // Крайние точки линейного объекта в допуске
 // Возвращает признак направления забора метрики
 //  = 1 - первые точки метрик
 //  = 2 - первая точка первой метрики и последняя второй метрики
 //  = 3 - последняя точка первой метрики и первая второй метрики
 //  = 4 - последние точки метрик
 int IsObjectLineLimit(TDataEdit *data1,TDataEdit *data2);

 // Повтор объединения площадных объектов
// TDataEdit *PovtorUnionSquareObjects(int get = 0);

  protected:

  // Допустимое расстояние между объектами 
  double Limit;
  int    Vector;

  // Метрика выходного подобъекта
  TDataEdit DataOutSub;

  // Список линейных объектов/подобъектов  
  TBitSet64K SubObject1;
  TBitSet64K SubObject2;

  // Признак пересечения объектов
  int FlagCross;

  // Флаг дотяга между объектами
  int AdjustFlag;

  // Флаг повтора сборки, если первый раз не получилось,
  int PovtorUnion;

  // Число подобъектов
  int SubNum1;
  int SubNum2;

  // Массив для нахождения пересечений подобъектов результата и
  // подобъектов объектов исходных данных
  // положительные значения - подобъекты 1 объекта
  // отрицательные значения - подобъекты 2 объекта
  int *Result;
  int CountResult;

  // Результирующий объекта при поглощении
  // одного объекта другим
  TDataEdit *ObjectOut;

  TDataEdit *DataOld1;
  TDataEdit *DataOld2;

};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++            TSquareUnion (Борзов)                ++++
// ++++ ОБЪЕДИНЕНИЕ НЕПЕРЕСЕКАЮЩИХСЯ ЗАМКНУТЫХ ОБЪЕКТОВ ++++
// ++++ Метрика должна быть в единой системе отсчета!   ++++
//    В отличии от TObjectUnion всегда объединяет контура
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
// Структура для хранения расстояния от точки до соседнего объекта
//---------------------------------------------------------------------------
typedef struct SQUAREPOINT
{
  double X, Y;                // Координаты точки
  double Distance;            // Ближайшее расстояние до соседнего объекта (до прямой или до точки)
  long int  PointNum;         // Номер ближайшей точки на другом объекте   
  short int IsDistanceToLine; // Расстояние до точки или до прямой
  short int IsCheckIntersect; // Проверено ли пересечение с контуром своего объекта
}
  SQUAREPOINT;
//---------------------------------------------------------------------------
// Структура для хранения точек, попавших в допуск
//---------------------------------------------------------------------------
typedef struct PASSPOINT
{
  int Num;                // Номер точки в массиве точек первого или второго объекта
  int IsPointFromObject1; // Признак принадлежности точки к первому объекту
}
  PASSPOINT;

class _DLLCLASS TSquareUnion
{

  public:

  TSquareUnion();
  ~TSquareUnion();

// Объединение двух площадных объектов по контуру
// info1     - первый объект
// info2     - второй объект
// info      - результат
// precision - допуск дотягивания
// isalwaysunion - флаг принудительной сшивки (1 - сшить всегда)
// При ошибке возвращает 0
long int Union(HOBJ info1, HOBJ info2, HOBJ info, double precision,
               long int isalwaysunion);                 

  protected:

// Вычисление квадрата расстояния между двумя точками
double GetDistanceSquare(double x1, double y1, double x2, double y2);

// Возвращает номер точки на замкнутом объекте (нумерация от 0)
int GetNum(int Num, int Count);

// Возвращает номер точки на замкнутом объекте (нумерация от 1)
int GetNum1(int Num, int Count);

// Вычисление квадрата расстояния от точки x,y до точки x1,y1 и до отрезка x1,y1 - x2,y2
int GetPieceDistance(double x1, double y1, double x2, double y2, 
                     double x, double y, double *Distance);

// Вычисляет проекцию точки (x,y) на прямую (x1,y1 - x2,y2)
void ProjectionPointToLine(double x1, double y1, double x2, double y2, 
                           double x, double y, double *xout, double *yout);

// Добавление подобъекта из другого объекта
long int AddSubjectFromObject(HOBJ toobj, HOBJ fromobj, int fromsubjnum);

// Проверяет пересекаются ли 2 отрезка
bool IsSegmentIntersect(double x1, double y1, double x2, double y2,
                        double x3, double y3, double x4, double y4);

// Заполняет список координат точек (заодно удаляем двойные точки)
int SetPoints(SQUAREPOINT *points, int *pointcount, HOBJ obj, int subjectnum);

// Проверяем связь на пересечение с контуром первого объекта
bool IsIntersectObj1(SQUAREPOINT *points1, int count1, int point1,
                     SQUAREPOINT *points2, int point2, bool isdistancetoline);

// Проверяем связь на пересечение с незамкнутой линией первого объекта
// (для внутренних контуров)
bool IsIntersectLine1(SQUAREPOINT *points1, int count1, int point1,
                      SQUAREPOINT *points2, int point2, bool isdistancetoline);  

// Вычисляем расстояние между каждой точкой первого объекта и
// ближайшей точкой или линей второго объекта и возвращаем ближайшую связь
void CalcDistance(SQUAREPOINT *points1, int count1, 
                  SQUAREPOINT *points2, int count2);                             

// Вычисляем расстояние между каждой точкой НЕЗАМКНУТОГО первого объекта и
// ближайшей точкой или линей НЕЗАМКНУТОГО второго объекта
void CalcDistanceToLine(SQUAREPOINT *points1, int count1, 
                        SQUAREPOINT *points2, int count2);

// Ищет самую ближайшую связь
void FindBestConnectInObj(SQUAREPOINT *points, int count, double mindist,
                          double *bestdist, int *bestnum);                       

// Расчёт расстояния от точки point1 с учётом пересечения со своим объектом
void CalcDistAllowIntersect(SQUAREPOINT *points1, int count1, int point1,
                            SQUAREPOINT *points2, int count2);                   

// Проверяет связь на пересечение и в случае пересечения уточняет её
bool IsConnectIntersect(SQUAREPOINT *points1, int count1, int point,
                        SQUAREPOINT *points2, int count2);                       

// Ищет самую ближайшую связь не пересекающуюся со своим объектом
void FindBestConnect(SQUAREPOINT *points1, int count1,
                     SQUAREPOINT *points2, int count2, double MinDist,
                     bool *ispointfromobj1, int *point, double *dist);           

// Ищем пару самых коротких связей
void FindConnects(SQUAREPOINT *points1, int count1, SQUAREPOINT *points2, int count2,
                  int *point1, bool *ispoint1fromobj1, int *point2, bool *ispoint2fromobj1,
                  double *dist1, double *dist2);                                 

// Добавляем точки по контуру объекта
void AddContour(SQUAREPOINT *points, int count, HOBJ obj, 
                int subject, int point1, int point2, bool isforwarddir);

// Добавляет точку на линии, ближайшей к точке point1
void AddToLine(HOBJ obj, int subject, SQUAREPOINT *points1, 
               int point1, SQUAREPOINT *points2);

// Проверяет надо ли присоединять контур в случае когда обе связи идут
// к одному отрезку
bool NeedAddContour(bool isforwarddir, double x1, double y1, double x2, double y2,
                   double x3, double y3, double x4, double y4);

// Возвращает координаты точки (меняет x и y)
void GetPoint(SQUAREPOINT *points1, SQUAREPOINT *points2,
              int num, bool ispointinobj1, DOUBLEPOINT *point);

// Определяет положение точки p относительно луча p1->p2
bool IsPointLeft(DOUBLEPOINT *p, DOUBLEPOINT *p1, DOUBLEPOINT *p2);

// Проверяет контур второго объекта и присоединяет его
void CheckAndAddContour(SQUAREPOINT *points1, SQUAREPOINT *points2, int count2,
                        int point1, int point2,
                        bool ispoint1inobj1, bool ispoint2inobj1,
                        bool isforwarddir1, bool isforwarddir2, bool isobj1left,
                        int Point1, int Point2, HOBJ obj, int subject);

// Добавляет точки в объединённый объект
void AddPoints(SQUAREPOINT *points1, int count1, SQUAREPOINT *points2, int count2,
               HOBJ obj, int subject, int point1, int point2,
               bool ispoint1inobj1, bool ispoint2inobj1,
               bool isforwarddir2, bool isforwarddir1, bool isobj1left, int *addcount2);

// Добавляет точки во внутренний подобъект
void AddPointsInSubject(SQUAREPOINT *points1, int count1,
                        SQUAREPOINT *points2, int count2,
                        HOBJ obj, int point1, int point2,
                        bool ispoint1inobj1, bool ispoint2inobj1);   

// Возвращает площадь объединённого объекта
double GetConnectSquare(SQUAREPOINT *points1, int count1,            
                        SQUAREPOINT *points2, int count2,
                        HOBJ obj, int point1, int point2,
                        bool ispoint1fromobj1, bool ispoint2fromobj1,
                        bool isequaldir, bool isobj1left);

// Вычисляет объединённый объект
void ConnectObjects(SQUAREPOINT *points1, int *count1,
                    SQUAREPOINT *points2, int *count2,
                    int point1, int point2,
                    bool ispoint1fromobj1, bool ispoint2fromobj1,
                    HOBJ obj, DOUBLEPOINT *points,
                    bool isequaldir, bool isobj1left);

// Добавляет точку в список точек, попавших в допуск
void AddPassPoint(int *passcount, PASSPOINT *passpoints,
                  int pointnum, bool ispointfromobject1);                        

// Добавляет точку в список точек, только если она крайняя из попавших в допуск
void AddExtremPassPoint(int *passcount, PASSPOINT *passpoints,
                        SQUAREPOINT *points, int pointnum, int priornum,
                        int nextnum, double precision, bool ispointfromobject1); 

// Заполнение списка точек, попавших в допуск
void SetPassPoints(int *passcount, PASSPOINT *passpoints, int precision,
                   SQUAREPOINT *points, int count, SQUAREPOINT *points2, int count2,
                   bool ispointfromobject1);                                     

// Поиск связи для присоединения внутренних контуров
void FindConnect(bool *ispointfromobj1, bool defaultispointfromobj1,
                 int truenum, int firstnum, int *foundnum,
                 SQUAREPOINT *points, int count, double precision);

// Ищет лучшую пару для соединения внутренних контуров
bool FindConnectPair(SQUAREPOINT *points1, int count1, SQUAREPOINT *points2, int count2,
                     double precision, bool *ispoint1fromobj1, bool *ispoint2fromobj1,
                     int *point1, int *point2);

// Проверка треугольной связи
bool IsTriangleConnect(SQUAREPOINT *points1, SQUAREPOINT *points2,   
                       int point1, int point2,
                       bool ispoint1fromobj1,
                       bool ispoint2fromobj1);
};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++  TObjectConsent +++++++++++++++++++++
// +++++++++++++ КЛАСС : СОГЛАСОВАНИЕ ОБ'ЕКТОВ  ++++++++++++
// ПЕРВЫЙ ОБ'ЕКТ - объект (c подобъектами), который согласовывают
// ВТОРОЙ ОБ'ЕКТ - объект (без подобъектов, замкнутый),
//                 по которому согласовывают.
//
// СОГЛАСОВАНИЕ ТОЛЬКО ПЛОЩАДНЫХ ОБ'ЕКТОВ ИЛИ
// ЛИНЕЙНЫХ ЗАМКНУТЫХ (при методе согласования SQUARE).
//
// ЕСЛИ ПЕРВЫЙ ОБ'ЕКТ ЛИНЕЙНЫЙ (не замкнутый)
// и метод согласования LINE, на выходе получаем внешнюю
// метрику линейного объекта
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TObjectConsent : public TObjectCutSubject
{

 public:

  //*********************************************************
  //  ОСНОВНЫЕ ФУНКЦИИ
  //  TObjectConsent - конструктор,
  //  LoadObjects - загрузить объект,
  //  GetNextObject - взять следующий объект
  //*********************************************************


  TObjectConsent():TObjectCutSubject(),
                   SubObject(), DataOutSub(), Subcut() 
                  {LoadSub = 0;};

  // data1 - объект (c подобъектами), который согласовывают
  // data2 - объект (без подобъектов, замкнутый),
  //                 по которому согласовывают.
  // method - метод согласования объектов:
  //          LOCAL_LINE - линейный,
  //          LOCAL_SQUARE - площадной (по умолчанию)
  // subject - номер подобъекта 2 объекта (по умолчанию = 0)
  // метрика объектов приведена к единой системе отсчета
  TObjectConsent(TDataEdit *data1, TDataEdit *data2, int method = LOCAL_SQUARE,
                 int subject = 0, double precision = PRECISION):
  TObjectCutSubject(data1, data2, method, subject, precision),
                 SubObject(), DataOutSub(), Subcut() 
                 {LoadSub = 0;};

  // info1 - объект (c подобъектами), который согласовывают
  // info2 - объект (без подобъектов, замкнутый),
  //                 по которому согласовывают.
  // subject - номер подобъекта 2 объекта (по умолчанию = 0)
  // метрика объектов должна быть приведена к единой системе отсчета

  TObjectConsent(TObjectInfo *info1, TObjectInfo *info2,
                 int method = LOCAL_SQUARE,
                 int subject = 0, double precision = PRECISION):
  TObjectCutSubject(info1, info2, method, subject, precision),
                 SubObject(), DataOutSub(), Subcut() 
                 {LoadSub = 0;};

  // Загрузить объекты
  // info1 - объект (c подобъектами), который согласовывают
  // info2 - объект (без подобъектов, замкнутый),
  //                 по которому согласовывают.
  // method - метод согласования объектов:
  //          LOCAL_LINE - линейный,
  //          LOCAL_SQUARE - площадной (по умолчанию)
  // subject - номер подобъекта 2 объекта (по умолчанию = 0)
  // метрика объектов будет приведена к единой системе отсчета
  int LoadObjects(TObjectInfo* info1, TObjectInfo* info2,
                  int method = LOCAL_SQUARE, int subject = 0,
                  double precision = PRECISION);

  // Загрузить объекты
  // data1 - объект (c подобъектами), который согласовывают
  // data2 - объект (без подобъектов, замкнутый),
  //                 по которому согласовывают.
  // method - метод согласования объектов:
  //          LOCAL_LINE - линейный,
  //          LOCAL_SQUARE - площадной (по умолчанию)
  // subject - номер подобъекта 2 объекта (по умолчанию = 0)
  // метрика должна быть объектов приведена к единой системе отсчета
  int LoadObjects(TDataEdit *data1, TDataEdit *data2,
                  int method = LOCAL_SQUARE, int subject = 0,
                  double precision = PRECISION);

  // Взять следующий объект
  // При ошибке возвращает 0
  TDataEdit *GetNextObject();


  //*********************************************************
  //  ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ ПРОМЕЖУТОЧНЫХ РЕЗУЛЬТАТОВ
  //*********************************************************

  // Взять очередной объект при работе с подобъектами
  // num  - номер подобъекта в datain
  int GetNextObjectSub(int loadsub = 0);

  // Порезать и добавить оставшиеся подобъекты для линейных объектов
  int AppendLineSubject();

  // Общее число подобъектов
  int SubNum;    

  protected:

  // Список подобъектов, попадающих в зону разрезания
  TBitSet64K SubObject;

  // Флаг работы с классом подобъектов
  int LoadSub;

  // Метрика выходного объекта (остатки подобъектов)
  TDataEdit DataOutSub;

  // Класс работы с подобъектами
  TObjectCutSubject Subcut;
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++  TObjectCutByLine++++++++++++++++++++
// ++++ КЛАСС : РАЗРЕЗАНИЕ ПЛОЩАДНОГО ОБ'ЕКТА ПО ЛИНИИ +++++
// ПЕРВЫЙ ОБ'ЕКТ - объект (линия без подобъектов),
//                 по которой режут
// ВТОРОЙ ОБ'ЕКТ - объект (c подобъектами, произвольный),
//                 который режут
// method - метод нарезки объектов:
//          LOCAL_LINE - линейный,
//          LOCAL_SQUARE - площадной
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TObjectCutByLine : public TPointCross
{
  public:

  enum INSIDEDUBL
       {
       OFF    = 0,     // отсутствует
       FIRST  = 1,     // обрабатывается в первый раз
       SECOND = 2      // обрабатывается второй раз и последний
       };

  //*********************************************************
  //  ОСНОВНЫЕ ФУНКЦИИ
  //  TObjectCutByLine - конструктор,
  //  LoadObjects      - загрузить объект,
  //  GetNextObject    - взять следующий объект
  //*********************************************************

  TObjectCutByLine();
  ~TObjectCutByLine();

  // Конструктор класса TObjectCutByLine
  // info1 - объект (линия без подобъектов),
  //         по которому режут
  // info2 - объект (подобъектами, произвольный),
  //         который режут
  // method - метод нарезки объектов:
  //          LOCAL_LINE - линейный,
  //          LOCAL_SQUARE - площадной
  TObjectCutByLine(TObjectInfo* info1, TObjectInfo* info2, int method,
                   double precision = PRECISION);

  // Конструктор класса TObjectCutByLine
  // data1  - объект (линия без подобъектов),
  //          по которому режут
  // data2  - объект (c подобъектами, произвольный),
  //          который режут
  // method - метод нарезки объектов:
  //          LOCAL_LINE - линейный,
  //          LOCAL_SQUARE - площадной
  // метрика объектов приведена к единой системе отсчета
  TObjectCutByLine(TDataEdit *data1, TDataEdit *data2, int method,
                   double precision = PRECISION);

  // Загрузить объекты
  // precision - допуск для нахождения точек пересечения
  int LoadObjects(TObjectInfo* info1, TObjectInfo* info2, int method,
                  double precision = PRECISION);
  int LoadObjects(TDataEdit *data1, TDataEdit *data2, int method,
                  double precision = PRECISION);
  int LoadObjects(TDataEdit *data1, TDataEdit *data2, int method, int subject,
                  double precision = PRECISION);

  // Взять следующий объект
  // Для линейных возвращает часть линейного объекта
  // как самостоятельный объект
  // При ошибке возвращает 0
  TDataEdit *GetNextObject();

  protected:

  // Инициализация переменных класса
  int InitObjectCut();

  // Проверка локализации исходных объектов
  int _fastcall ControlLocal(TDataEdit *data2, int method);

  // Проставить флаг забора метрики в массивы PointCross1, PointCross2
  int SetInside();

  // Определение подобъектов разрезаемого объекта
  int _fastcall InsideSubObject(TDataEdit *data);

  // Взять очередной объект при работе с подобъектами
  // dataout - куда
  // datain  - откуда
  // subnum  - номер подобъекта в datain
  int _fastcall GetNextObjectSub(int num, int loadsub);

  // Откорректировать массивы точек пересечения
  // cross1 - линейный объект
  // cross2 - площадной объект
  void _fastcall CorrectPointCross(POINTCROSS *cross1,
                                   POINTCROSS *cross2,
                                   TDataEdit *data1,
                                   TDataEdit *data2,
                                   int count);

  // Определить положение точек относительно объектов
  // возвращает ALL     - если обе точки лежат в объекте
  //            BEFORE  - только одна точка лежит в объекте
  int _fastcall GetPlacePoint(DOUBLEPOINT *point1, DOUBLEPOINT *point2,
                              TDataEdit *data);

  protected:

  // Метрика выходного объекта
  TDataEdit DataOut;

  // Метрика выходного объекта (остатки подобъектов)
  TDataEdit DataOutSub;

  private:

  // Список подобъектов, попадающих в зону разрезания
  TBitSet64K SubObject;

  // Общее число подобъектов
  int SubNum;

  // Флаг работы с классом подобъектов
  int LoadSub;

  // Класс работы с подобъектами
  TObjectCutSubject Subcut;

  int * InsideDublicate1;
  int * InsideDublicate2;
  int SetInsideDublicate;
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++  TPointCrossObject +++++++++++++++++++++
// +++ КЛАСС : НАХОЖДЕНИЕ ТОЧЕК ПЕРЕСЕЧЕНИЯ ДВУХ ОБ'ЕКТОВ ++
//                  С ПОДОБ'ЕКТАМИ !!!
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TPointCrossObject
{
  public:

  TPointCrossObject();
  ~TPointCrossObject();

  // Загрузить объекты
  // info1 - 1 объект
  // info2 - 2 объект
  // Возвращает число точек пересечения
  int LoadObjects(TObjectInfo *info1, TObjectInfo *info2,
                  double precision = PRECISION);

  // Загрузить объекты
  // info1 - 1 объект
  // info2 - 2 объект
  // subject1 - номер подобъекта 1 объекта
  // subject2 - номер подобъекта 2 объекта
  // Возвращает число точек пересечения
  int LoadObjects(TObjectInfo *info1, TObjectInfo *info2,
                  int subject1, int subject2,
                  double precision = PRECISION);

  // Запросить точку пересечения
  // number - номер точки
  // point - точка (КООРДИНАТЫ В МЕТРАХ НА МЕСТНОСТИ)
  // При ошибке возвращает 0
  int GetPoint(int number, CROSSPOINT *point);

  protected:

  // Установить значение выходных данных
  // number - номер точки
  // point - куда
  // При ошибке возвращает 0
  int _fastcall SetPoint(int number, CROSSPOINT *point);


  protected:

  // Метрика обрабатываемых объектов
  TDataEdit Data1;
  TDataEdit Data2;

  TObjectInfo *Info1;
  TObjectInfo *Info2;

  // Класс нахождения точек пересечения
  TPointCross PointCross;

  // Адрес массива точек пересечения
  CROSSPOINT *Memory;

  public:

  // Число точек пересечения
  int NumCross;
};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++  TObjectCutSubLine  +++++++++++++++++++++
// +++++++++++++ КЛАСС : ПЕРЕСЕЧЕНИЕ ОБ'ЕКТОВ  +++++++++++++
// ПЕРВЫЙ ОБ'ЕКТ - объект (без подобъектов, замкнутый),
//                 по которому режут ( например рамка)
// ВТОРОЙ ОБ'ЕКТ - объект (c подобъектами, произвольный),
//                 который режут
// method - метод нарезки объектов:
//          LOCAL_LINE - линейный,
//          LOCAL_SQUARE - площадной     
// в TObjectCutSubLine добавлен вариант
// ПЕРВЫЙ ОБ'ЕКТ - объект (площадной объект c подобъектами),
// ВТОРОЙ ОБ'ЕКТ - объект (линейный),
// method - метод нарезки объектов:
//          LOCAL_LINE - линейный,
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TObjectCutSubLine : public TObjectCut
{

  public:

  //*********************************************************
  //  ОСНОВНЫЕ ФУНКЦИИ
  //  TObjectCutSubLine - конструктор,
  //  LoadObjects - загрузить объект,
  //  GetObject - взять объект
  //*********************************************************

  TObjectCutSubLine();
  ~TObjectCutSubLine();

  TObjectCutSubLine(TDataEdit *data1, TDataEdit *data2, int method,
                    double precision = PRECISION,int full = 0);

  TObjectCutSubLine(TObjectInfo* info1, TObjectInfo* info2, int method,
             double precision = PRECISION, int full = 0);

  // Загрузить объекты
  int LoadObjects(TDataEdit *data1, TDataEdit *data2, int method,
                  double precision = PRECISION, int full = 0);
  int LoadObjects(TObjectInfo* info1, TObjectInfo* info2, int method,
                  double precision = PRECISION, int full = 0);

  // Взять полученный объект
  TObjectInfo *GetNextObject(TObjectInfo * info);     

public:

  // Число итоговых подобъектов
  int ResultSubNum;

  // Выходной объект
  TObjectInfo InfoOut;                  

  int FlagSubLine;
  
};

#endif

