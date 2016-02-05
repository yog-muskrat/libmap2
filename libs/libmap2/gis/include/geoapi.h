
#ifndef GEOAPI_H
#define GEOAPI_H

#ifndef GEOTYPE
 #include "GeoType.h"
#endif

#include "MapApi.h"

#define GLAPI _export WINAPI

typedef long int  HTEOIMP;  // ИДЕНТИФИКАТОР КЛАССА ИМПОРТА  TEO
typedef long int  HTEOEXP;  // ИДЕНТИФИКАТОР КЛАССА ЭКСПОРТА TEO
typedef long int  HTPRIMP;  // ИДЕНТИФИКАТОР КЛАССА ИМПОРТА  TPR
typedef long int  HTPREXP;  // ИДЕНТИФИКАТОР КЛАССА ЭКСПОРТА TPR

extern "C"
{
// Активизация диалога импорта геодезических данных

 int WINAPI _export glGeoLoad(HMAP hmap, TASKPARM *parm,char *inFilename,
                    char *teoFilename,char *tprFilename,char *xyhFilename);

 //--------------------------------------------------------------
 // Загрузка файла TEO
 //--------------------------------------------------------------

 // Созданние класса импорта TEO -  файла
 // filename - полное имя импортируемого файла
 // При ошибке возвращает 0,
 // иначе - указатель на созданный класс

 HTEOIMP GLAPI CreateInputTeo(const char *filename);

 // Удаление класса импорта TEO -  файла
 // filename - полное имя импортируемого файла
 // При ошибке возвращает 0,
 // иначе - указатель на созданный класс

 long int GLAPI CloseInputTeo(HTEOIMP hti);

 // Запросить статистику
 // при ошибке возвращает 0

 long int GLAPI GetStatisticTeo(HTEOIMP hti,TEOSTAT *stat);

 // Открыть следующий блок измерений
 // при ошибке возвращает 0
 // иначе тип хода (COURSE_ ...)

 long int GLAPI NextBlockTeo(HTEOIMP hti);

 // Считать базовую точку
 // в point помещается описание точки
 // при ошибке возвращает 0

 long int GLAPI NextBasePointTeo(HTEOIMP hti,BASEPOINT* point);

 // Считать точку хода
 // в point помещается описание точки
 // при ошибке возвращает 0

 long int GLAPI NextMeasurePointTeo(HTEOIMP hti,MEASUREPOINT* point);

 //--------------------------------------------------------------
 // Загрузка файла TPR
 //--------------------------------------------------------------

 // Созданние класса импорта TPR -  файла
 // filename - полное имя импортируемого файла
 // При ошибке возвращает 0,
 // иначе - указатель на созданный класс

 HTPRIMP GLAPI CreateInputTpr(const char *filename);

 // Удаление класса импорта TEO -  файла
 // filename - полное имя импортируемого файла
 // При ошибке возвращает 0,
 // иначе - указатель на созданный класс

 long int GLAPI CloseInputTpr(HTPRIMP hti);

 // Запросить статистику
 // при ошибке возвращает 0

 long int GLAPI GetStatisticTpr(HTPRIMP hti,TEOSTAT *stat);

 // Открыть следующий блок измерений
 // при ошибке возвращает 0
 // иначе тип хода (COURSE_ ...)

 long int GLAPI NextBlockTpr(HTPRIMP hti);

 // Считать базовую точку
 // в point помещается описание точки
 // при ошибке возвращает 0

 long int GLAPI NextBasePointTpr(HTPRIMP hti,BASEPOINT* point);

 // Считать точку хода
 // в point помещается описание точки
 // при ошибке возвращает 0

 long int GLAPI NextMeasurePointTpr(HTPRIMP hti,MEASUREPOINT* point);

 //--------------------------------------------------------------
 // Сохранение файла TEO
 //--------------------------------------------------------------
 // Созданние класса экспорта TEO -  файла
 // filename - полное имя экспортируемого файла
 // При ошибке возвращает 0,
 // иначе - указатель на созданный класс

 HTEOEXP GLAPI CreateOutTeo(const char *filename);

 // Удаление класса импорта TEO -  файла
 // filename - полное имя импортируемого файла
 // При ошибке возвращает 0,
 // иначе - указатель на созданный класс

 long int GLAPI CloseOutTeo(HTEOEXP hte);

 // Записать строку комментария
 // text - текст сообщения (перед текстом записывается "//")
 // при ошибке возвращает 0

 long int GLAPI WriteMessageTeo(HTEOEXP hte,const char *text);

 // Записать статистику
 // stat - статистическая информация (записывается в блок .INF)
 // при ошибке возвращает 0

 long int GLAPI WriteStatisticTeo(HTEOEXP hte,TEOSTAT *stat);

 // Записать признак начала блока
 // type - строка параметров (необязательно) (COURSE_UNDEFINED, ...)
 // при ошибке возвращает 0

 long int GLAPI WriteBeginBlockTeo(HTEOEXP hte,int type);

 // Записать информацию о базовой точке
 // point - описание точки
 // при ошибке возвращает 0

 long int GLAPI WriteBasePointTeo(HTEOEXP hte,BASEPOINT *point);

 // Записать информацию о точке хода в секцию .DAT
 // point - описание точки
 // при ошибке возвращает 0

 long int GLAPI WriteMeasurePointTeo(HTEOEXP hte,MEASUREPOINT *point);

 // Записать признак конца блока
 // при ошибке возвращает 0

 long int GLAPI WriteEndBlockTeo(HTEOEXP hte);


 //--------------------------------------------------------------
 // Сохранение файла TPR
 //--------------------------------------------------------------

 // Созданние класса экспорта TEO -  файла
 // filename - полное имя экспортируемого файла
 // При ошибке возвращает 0,
 // иначе - указатель на созданный класс

 HTPREXP GLAPI CreateOutTpr(const char *filename);

 // Удаление класса импорта TEO -  файла
 // filename - полное имя импортируемого файла
 // При ошибке возвращает 0,
 // иначе - указатель на созданный класс

 long int GLAPI CloseOutTpr(HTPREXP hte);

 // Записать строку комментария
 // text - текст сообщения (перед текстом записывается "//")
 // при ошибке возвращает 0

 long int GLAPI WriteMessageTpr(HTPREXP hte,const char *text);

 // Записать статистику
 // stat - статистическая информация (записывается в блок .INF)
 // при ошибке возвращает 0

 long int GLAPI WriteStatisticTpr(HTPREXP hte,TEOSTAT *stat);

 // Записать признак начала блока
 // type - строка параметров (необязательно) (COURSE_UNDEFINED, ...)
 // при ошибке возвращает 0

 long int GLAPI WriteBeginBlockTpr(HTPREXP hte,int type);

 // Записать информацию о базовой точке
 // point - описание точки
 // при ошибке возвращает 0

 long int GLAPI WriteBasePointTpr(HTPREXP hte,BASEPOINT *point);

 // Записать информацию о точке хода в секцию .DAT
 // point - описание точки
 // при ошибке возвращает 0

 long int GLAPI WriteMeasurePointTpr(HTPREXP hte,MEASUREPOINT *point);

 // Записать признак конца блока
 // при ошибке возвращает 0

 long int GLAPI WriteEndBlockTpr(HTPREXP hte);

}
#endif
