
#ifndef FRMAPI_H
 #define FRMAPI_H

#ifndef HMAP
 #include "mapapi.h"
 #include "logapi.h"
#endif



#define FRMELEMENTCOUNT 7

#define FRM_ERROR    -1
#define FRM_RSCFRAME  1
#define FRM_NAMES     2
#define FRM_RSCCORN   3
#define FRM_TERRAIN   4
#define FRM_COORD     5
#define FRM_LISTNAME  6

typedef long int  HBORDER;       // КЛАСС ОФОРМЛЕНИЯ РАМКИ

typedef struct OUTFRAME
{
 long int InLineCode;
 long int OutLineCode;
 long int BarCode;
 double Wide;
}OUTFRAME;

typedef struct RSCNEIG
{
 long int Code;
 long int Neig;
 long int Point;
 double X1;
 double X2;
 double Y1;
 double Y2;
 double Allign;
}RSCNEIG;


typedef struct RSCLINE
{
 long int Use;
 long int Code;
 double X1;
 double Y1;
 double X2;
 double Y2;
}RSCLINE;

//---------------------------------------------------------------------------
// Схема линейного масштаба
//---------------------------------------------------------------------------

typedef struct LINESCALE
{
 long int Use;
 long int Code;
 double Distance;      // Расстояние от внутренней рамки
 double X;             // Точка привязки (нижний край)
 double Y;             // Точка привязки (центр)
}LINESCALE;


typedef struct GEONET
{
 long int LongLineCode;
 long int LineCode;      // Код поперечных линий
 long int BarCode;       // Код оттененного полигона
 long int ListNumber;    // Номер оформляемого листа
 double   Distance;      // Расстояние от внутренней рамки
 double   Wide;          // Ширина
 double   ExWide;        // Ширина 10- секундной зоны (для 50-100 тыс.)
}GEONET;

typedef struct GEOFRAME
{
 double B_SW;  // B ю-з
 double L_SW;  // L ю-з
 double B_NW;  // B с-з
 double L_NW;  // L с-з
 double B_NE;  // B с-в
 double L_NE;  // L с-в
 double B_SE;  // B ю-в
 double L_SE;  // L ю-в
}GEOFRAME;

extern "C"
{
//--------------------------------------------------------------
// Запросить количество доступных элементов оформления
//--------------------------------------------------------------
int WINAPI _export frmGetElementsCount();
//--------------------------------------------------------------
// Запросить название элемента оформления по его номеру
//--------------------------------------------------------------
const char * WINAPI _export frmGetElementName(int number, int language);
//--------------------------------------------------------------
// Запросить идентификатор элемента оформления по его номеру
//--------------------------------------------------------------
int WINAPI _export frmGetElementIdent(int number);
//--------------------------------------------------------------
// Запросить тип элемента оформления по его номеру (1-только для топокарт)
//--------------------------------------------------------------
int WINAPI _export frmGetTopoOnly(int number);

HBORDER WINAPI _export frmBorderCreate(HMAP hmap,HSITE site,HOBJ frame);
int WINAPI _export frmBorderFree(HBORDER border);                        



//--------------------------------------------------------------------------
//                    Нанесение зарамочного оформления
//
// Hmap      - документ
// sheet     - номер оформляемого листа
// rotsit    - повернутый лист
// frmsit    - карта создаваемого зарамочного оформления
// FrameTemp - имя файла шаблона зарамочного оформления
// Angle     - угол поворота оформляемого листа
// lblname   - файл описания создаваемой легенды
// logfile   - файл протокола
// mestarget - тип сообщений (0-только файл,1-только экран,2-файл+экран)
//
//       при ошибке возвращает 0
//--------------------------------------------------------------------------


int WINAPI _export frmCreateBorder(HMAP Hmap,int sheet,HSITE rotsit,
                   HSITE frmsit,char *FrameTemp,double Angle,
                   char *logfile,int mestarget);


//--------------------------------------------------------------------------
//              Нанесение легенды зарамочного оформления
//
// Hmap    - документ
// sheet   - номер оформляемого листа
// rotsit  - повернутый лист
// legsit  - карта создаваемой легенды
// lblname - файл описания создаваемой легенды
// Angle   - угол поворота оформляемого листа
// logfile   - файл протокола
// mestarget - тип сообщений (0-только файл,1-только экран,2-файл+экран)
//       при ошибке возвращает 0
//
//--------------------------------------------------------------------------

int WINAPI _export frmCreateLegend(HMAP Hmap,int sheet,HSITE rotsit,
                   HSITE legsit,char *lblname,double Angle,
                   char *logfile,int mestarget);

//--------------------------------------------------------------------------
// Определение номенклатуры листа карты в установленной кодировке
// для любого масштаба (5 000 - 200 000)
// sheet      - номер текущего листа
// neighbour  - номер соседа (0-своя,1-зап,2-сев,3-вост,4-южн)
// name       - строка для результата (длиной MAX_PATH)
// При ошибке возвращает 0
//--------------------------------------------------------------------------
int WINAPI _export  frmNeighbourCalculate(HMAP hmap,int sheet,int neighbour,
                                          int scale,char *name);

//--------------------------------------------------------------------------
// Определение номенклатуры листа карты в установленной кодировке
// для масштаба  1 : 5000
// listnumber       - номер текущего листа
// neighbournumber  - номер соседа (0-своя,1-зап,2-сев,3-вост,4-южн)
// string           - строка для результата (длиной MAX_PATH)
// При ошибке возвращает 0
//--------------------------------------------------------------------------
int WINAPI _export frmNeighbourCalculate5000(HMAP hmap,int listnumber,int neighbournumber,
                           char *string);
//--------------------------------------------------------------------------
// Определение номенклатуры листа карты в установленной кодировке
// для масштаба  1 : 100000
// listnumber       - номер текущего листа
// neighbournumber  - номер соседа (0-своя,1-зап,2-сев,3-вост,4-южн)
// string           - строка для результата (длиной MAX_PATH)
// При ошибке возвращает 0
//--------------------------------------------------------------------------
int WINAPI _export frmNeighbourCalculate100000(HMAP hmap,int listnumber,int neighbournumber,
                           char *string);
//--------------------------------------------------------------------------
// Определение номенклатуры листа карты в установленной кодировке
// для масштаба  1 : 200000
// listnumber       - номер текущего листа
// neighbournumber  - номер соседа (0-своя,1-зап,2-сев,3-вост,4-южн)
// string           - строка для результата (длиной MAX_PATH)
// При ошибке возвращает 0
//--------------------------------------------------------------------------
int WINAPI _export frmNeighbourCalculate200000(HMAP hmap,int listnumber,int neighbournumber,
                           char *string);
//--------------------------------------------------------------------------
// Определение номенклатуры листа карты в установленной кодировке
// для масштаба  1 : 500000
// listnumber       - номер текущего листа
// neighbournumber  - номер соседа (0-своя,1-зап,2-сев,3-вост,4-южн)
// string           - строка для результата (длиной MAX_PATH)
// При ошибке возвращает 0
//--------------------------------------------------------------------------
int WINAPI _export frmNeighbourCalculate500000(HMAP hmap,int listnumber,int neighbournumber,
                           char *string);

//--------------------------------------------------------------------------
// Определение номенклатуры листа карты в установленной кодировке
// для масштаба  1:1 000 000
// listnumber       - номер текущего листа
// neighbournumber  - номер соседа (0-своя,1-зап,2-сев,3-вост,4-южн)
// string           - строка для результата (длиной MAX_PATH)
// При ошибке возвращает 0
//--------------------------------------------------------------------------
int WINAPI _export frmNeighbourCalculate1000000(HMAP hmap,int listnumber,int neighbournumber,
                           char *string);


//--------------------------------------------------------------------------
// Определение номенклатуры листа карты в установленной кодировке
// для масштаба  1 : 25000
// listnumber       - номер текущего листа
// neighbournumber  - номер соседа (0-своя,1-зап,2-сев,3-вост,4-южн)
// string           - строка для результата (длиной MAX_PATH)
// При ошибке возвращает 0
//--------------------------------------------------------------------------
int WINAPI _export frmNeighbourCalculate25000(HMAP hmap,int listnumber,int neighbournumber,
                           char *string);
//--------------------------------------------------------------------------
// Определение номенклатуры листа карты в установленной кодировке
// для масштаба  1 : 10000
// listnumber       - номер текущего листа
// neighbournumber  - номер соседа (0-своя,1-зап,2-сев,3-вост,4-южн)
// string           - строка для результата (длиной MAX_PATH)
// При ошибке возвращает 0
//--------------------------------------------------------------------------
int WINAPI _export frmNeighbourCalculate10000(HMAP hmap,int listnumber,int neighbournumber,
                           char *string);
//--------------------------------------------------------------------------
// Определение номенклатуры листа карты в установленной кодировке
// для масштаба  1 : 50000
// listnumber       - номер текущего листа
// neighbournumber  - номер соседа (0-своя,1-зап,2-сев,3-вост,4-южн)
// string           - строка для результата (длиной MAX_PATH)
// При ошибке возвращает 0
//--------------------------------------------------------------------------
int WINAPI _export frmNeighbourCalculate50000(HMAP hmap,int listnumber,int neighbournumber,
                           char *string);
//--------------------------------------------------------------------------
// Определение кода номенклатуры листа карты в установленной кодировке
// listnumber       - номер текущего листа
// string           - строка для результата (длиной MAX_PATH)
// При ошибке возвращает 0
//--------------------------------------------------------------------------
int WINAPI _export frmCodeCalculate(HMAP hmap,int listnumber,char *string);

//-----------------------------------------------------------------------
// Определение угла разворота листа
//
//  hmap       - идентификатор карты
//  listnumber - номер листа
//  alfa       - переменная для записи результата
//
//  при ошибке возвращает 0
//-----------------------------------------------------------------------

int WINAPI _export frmGetRotateAngle(HMAP hmap,int listnumber,double *alfa);

//-----------------------------------------------------------------------------
// Поворот листа карты относительно юго - западного угла
//
// handle        - идентификатор окна для формирования линейки
// hmap          - идентификатор исходной карты
// listnumber    - номер поворачиваемого листа
// alfa          - угол поворота
// RotateName    - имя формируемой карты
// RotateRscName - классификатор формируемой карты
//
// При ошибке возвращает 0
//-----------------------------------------------------------------------------

int WINAPI _export frmTurnSheet(TASKPARM *parm,HMAP hmap,int listnumber,double alfa,
                 HSITE rotSit);

//-----------------------------------------------------------------------------
// Нанести внутреннюю рамку (FrameCode),
//         внешнюю    рамку (LineCode),
//                      фон (FillCode)
// с учетом точек прогиба
// hmap     - идентификатор исходной карты
// site     - повернутый лист
// delta    - расстояние между внутренней и внешней рамками в мм
// info     - рамка повернутого листа
// mode = 1 - совместить центры
//
// При ошибке возвращает 0
//-----------------------------------------------------------------------------

int WINAPI _export frmCreateFrameFill(HMAP hmap,HSITE site,double delta,long int LineCode,
                       long int FillCode,long int FrameCode,HOBJ info,int mode = 0);

int WINAPI _export frmCreateOutFrame(HBORDER border,OUTFRAME *frame);

//--------------------------------------------------------------
// Установить точку пересечения отрезков
// правятся всегда 2-я и 4-я точки!
//--------------------------------------------------------------

int WINAPI _export frmSetCross(double  X1,double Y1,double *X2,double *Y2,
                               double  X3,double Y3,double *X4,double *Y4);


//--------------------------------------------------------------
// Найти точку пересечения отрезков
//--------------------------------------------------------------

int WINAPI _export frmGetCross(double  X1,double Y1,double X2,double Y2,
                double  X3,double Y3,double X4,double Y4,
                double *XN,double *YN);

//----------------------------------------------------------------------
// Нанесение номенклатуры и кода номенклатуры (текст из паспорта)
// Горизонтально, центр подписи в т.x,y (m)
//----------------------------------------------------------------------

int WINAPI _export frmNomenclatureCreate(HMAP hmap,HSITE site,long int code,char *text,
                                         long int code1,char *textex,double x,double y);


//----------------------------------------------------------------------
// Нанесение названия листа (по центру над верхней рамкой, текст из паспорта)
//----------------------------------------------------------------------

int WINAPI _export frmSheetNameCreate(HMAP hmap,HSITE site,long int code,char *text,
                                      double x,double y);


//--------------------------------------------------------------
// Нанести линию заданного кода
// При frameinfo (замкнутый контур) != 0  - линия обрезается по
// frameinfo
// key - номер главного объекта (для группы) -1 - группы не создавать
//--------------------------------------------------------------

int WINAPI _export frmCreateRscLine(HMAP hMap,HSITE hSite,double x1,double x2,
                                    double y1,double y2,int excode,
                                    HOBJ frameinfo = 0,long int key = -1);


//--------------------------------------------------------------
// Нанести прямоугольник заданного кода
//--------------------------------------------------------------

int WINAPI _export frmCreateRscBox(HMAP hMap,HSITE hSite,double x1,double x2,
                   double y1,double y2,int excode,int local = LOCAL_LINE,long int key = -1);

//--------------------------------------------------------------
// Нанести полигон заданного кода
//--------------------------------------------------------------

int WINAPI _export frmCreateRscPolygon(HMAP hMap,HSITE hSite,int pointcount,DOUBLEPOINT *data,
                                    int excode,int local = LOCAL_SQUARE,long int key = -1);

//--------------------------------------------------------------
// Нанести текст заданного кода
// key - номер главного объекта (для группы) -1 - группы не создавать
//--------------------------------------------------------------

int WINAPI _export frmCreateRscTitle(HMAP hMap,HSITE hSite,
                   double x1,double x2,double y1,double y2,
                   int excode,int wide,char *text,int align = 0,long int key = -1);

//--------------------------------------------------------------
// Позиционировать подпись относительно точек отсчета
//--------------------------------------------------------------

int WINAPI _export frmSetTextPosition(double *X1,double *X2,
                    double *Y1,double *Y2,
                    double MinX,double MinY,
                    double MaxX,double MaxY,int position,double MetInMm);

//--------------------------------------------------------------
// Нанести подпись линии сетки
// key - номер главного объекта (для группы) -1 - группы не создавать
// bg = 0 - фон не создавать
//--------------------------------------------------------------

int WINAPI _export frmCreateNetLabel(HMAP hmap,HSITE hSit,double x1,double y1,int excode,
                   int hor,int vert,char *text,int direct = 0,
                   long int key = -1,int bg = 1);


//----------------------------------------------------------------------
// Нанесение схемы азимутов
//----------------------------------------------------------------------

int WINAPI _export frmCreateMeridian(HMAP hmap,HSITE hSit,HOBJ info,
                                     LISTREGISTER *sheetreg,char *String);


//----------------------------------------------------------------------
// Нанесение выходов километровой сетки смежной зоны
//----------------------------------------------------------------------

int WINAPI _export frmCreateAdjZone(HMAP Hmap,HSITE hSit,MAPREGISTER  *mapreg,
                                    LISTREGISTER *sheetreg,HOBJ info,DOUBLEPOINT *framepoint,
                                    char *string,double alfa);

//------------------------------------------------------------------------
//      Построение геодезической рамки для 1:10 000
//------------------------------------------------------------------------

int WINAPI _export frmCreateGeo10000(HMAP hmap,HSITE hSit,GEONET *geonet,HOBJ info);

//------------------------------------------------------------------------
//      Построение геодезической рамки для 1:50 000
//------------------------------------------------------------------------

int WINAPI _export frmCreateGeo50000(HMAP hmap,HSITE hSit,GEONET *geonet,HOBJ info);

//------------------------------------------------------------------------
//      Построение геодезической рамки для 1:200 000
//------------------------------------------------------------------------

int WINAPI _export frmCreateGeo200000(HMAP hmap,HSITE hSit,GEONET *geonet,HOBJ info);  

//------------------------------------------------------------------------
// Нанести номенклатуры всех соседей по бокам рамки листа
//------------------------------------------------------------------------

int WINAPI _export frmCreateAllNeighbour(HMAP hmap,HSITE hSit,HOBJ frameinfo,char *buf,int listnumber);

//---------------------------------------------------------------------
//     Линия (графика)
//---------------------------------------------------------------------

int WINAPI _export frmCreateDrawLine(HMAP hmap, HSITE hsite,double x1,double x2,
                                     double y1,double y2,double thick,long int color,long int key = -1);

//---------------------------------------------------------------------
//     Закрашенный прямоугольник (графика)
//---------------------------------------------------------------------

int WINAPI _export frmCreateDrawBar(HMAP hmap, HSITE hsite,double x1,double x2,
                                        double y1,double y2,long int color,long int key = -1);
//-------------------------------------------------------------------------
// Стандартный линейный масштаб для 1:1000 000
//-------------------------------------------------------------------------

int WINAPI _export frmCreateLinescale1000000(HMAP hmap,HSITE hSit,LINESCALE *scale);

//-------------------------------------------------------------------------
// Стандартный линейный масштаб для 1:500 000
//-------------------------------------------------------------------------

int WINAPI _export frmCreateLinescale500000(HMAP hmap,HSITE hSit,LINESCALE *scale);


//-------------------------------------------------------------------------
// Стандартный линейный масштаб для 1 : 200 000
//-------------------------------------------------------------------------

int WINAPI _export frmCreateLinescale200000(HMAP hmap,HSITE hSit,LINESCALE *scale);

//-------------------------------------------------------------------------
// Стандартный линейный масштаб для 1 : 50 000
//-------------------------------------------------------------------------

int WINAPI _export frmCreateLinescale50000(HMAP hmap,HSITE hSit,LINESCALE *scale);

//-------------------------------------------------------------------------
// Стандартный линейный масштаб для 1 : 100 000
//-------------------------------------------------------------------------

int WINAPI _export frmCreateLinescale100000(HMAP hmap,HSITE hSit,LINESCALE *scale);

//-------------------------------------------------------------------------
// Стандартный линейный масштаб для 1 : 25 000
//-------------------------------------------------------------------------

int WINAPI _export frmCreateLinescale25000(HMAP hmap,HSITE hSit,LINESCALE *scale);

//-------------------------------------------------------------------------
// Стандартный линейный масштаб для 1 : 10 000
//-------------------------------------------------------------------------

int WINAPI _export frmCreateLinescale10000(HMAP hmap,HSITE hSit,LINESCALE *scale);

//--------------------------------------------------------------
//  Коррекция длины линии
// Delta  - корректная длина(м)
// number=1 - корректировать первую точку
// number=2 - корректировать вторую точку
//--------------------------------------------------------------

int WINAPI _export frmSetLineLenght(double *x1,double *y1,double *x2,double *y2,
                                    double delta,int number);

//-------------------------------------------------------------------
//         Замена "я" на спецсимвол
//-------------------------------------------------------------------

int WINAPI _export frmPreSscanf(char *string);

//-------------------------------------------------------------------
//         Возврат "я"
//-------------------------------------------------------------------

int WINAPI _export frmPostSscanf(char *string);


//------------------------------------------------------------------------
// Нанести Подписи геодезических координат
//------------------------------------------------------------------------

int WINAPI _export frmCreateGeolabels(HMAP Hmap,HSITE frmsit,long int code,
                   long int linecode,GEOFRAME geoframe,
                   HOBJ info,DOUBLEPOINT* framepoint,double dx,long int labelcode);

//------------------------------------------------------------------------
// Нанести Подписи геодезических координат
// на топографической карте (масштаба до 1:500 000)
//------------------------------------------------------------------------

int WINAPI _export frmCreateGeolabels200t(HMAP Hmap,HSITE frmsit,long int code,
                   long int linecode,GEOFRAME geoframe,
                   HOBJ info,DOUBLEPOINT* framepoint,double dx,long int labelcode);

//------------------------------------------------------------------------
// Нанести Подписи геодезических координат
// на топографической карте масштаба 1:500 000
//------------------------------------------------------------------------

int WINAPI _export frmCreateGeolabels500tTopo(HMAP Hmap,HSITE frmsit,long int code,
                   long int linecode,GEOFRAME geoframe,
                   HOBJ info,DOUBLEPOINT* framepoint,double dx,long int labelcode);

//------------------------------------------------------------------------
// Нанести Подписи геодезических координат
// на топографической карте масштаба 1:1 000 000
//------------------------------------------------------------------------

int WINAPI _export frmCreateGeolabels1mTopo(HMAP Hmap,HSITE frmsit,long int code,
                   long int linecode,GEOFRAME geoframe,
                   HOBJ info,DOUBLEPOINT* framepoint,double dx,long int labelcode);
//------------------------------------------------------------------------
// Нанести Подписи геодезических координат
//------------------------------------------------------------------------

int WINAPI _export frmCreateIncLabel(HMAP hmap,HSITE frmsit,
                   LISTREGISTER *sheetreg,DOUBLEPOINT* framepoint,long int code,
                   double dx);

//------------------------------------------------------------------------
// Нанести угловые кресты и (если labelcode != 0) подписи
// подписи прямоугольных координат углов
//------------------------------------------------------------------------

int WINAPI _export frmCreateCorn(HMAP hmap,HSITE frmsit,double dx,long int code,
                   long int labelcode,DOUBLEPOINT *framepoint,double alfa);


//------------------------------------------------------------------------
// Нанести выходы километровой сетки (netCode)
// c подписями (textCode,twoTitleCode),
// кресты (пересечения коорд.линий - при необходимости)
// dx - расстояние в мм между внешней и внутренней рамками
// oldframe - исходная (неповернутая) рамка
//------------------------------------------------------------------------

int WINAPI _export frmCreateNet(HMAP hmap,HSITE frmsit,double dx,double step,
                   long int netCode,long int textCode,long int twoTitleCode,
                   long int crossCode,DOUBLEPOINT *framepoint,HOBJ info,HOBJ oldframeinfo,
                   double alfa);

//-------------------------------------------------------------------
//         Расчет точек рамки
//-------------------------------------------------------------------

int WINAPI _export frmSetFramePoint(DOUBLEPOINT *framepoint,HOBJ info);

//-------------------------------------------------------------------
//         Сообщение об ошибке
//
// message - текст сообщения
// target   0 - только в файл,
//          1 - только на экран,
//          2 - в файл и на экран
// filename - имя файла протокола
// mode     0 - дописать протокол
//          1 - пересоздать протокол
//
//-------------------------------------------------------------------

int WINAPI _export frmErrorMessage(char * message,int target = -1,char *filename = 0,int mode = 0);


int WINAPI _export GetPerpend(DOUBLEPOINT first,DOUBLEPOINT last,
                            DOUBLEPOINT middle,double distance,
                            DOUBLEPOINT *left,DOUBLEPOINT *right);




}
#endif

