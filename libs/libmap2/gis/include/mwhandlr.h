
#ifndef MWHANDLR_H
#define MWHANDLR_H

#ifndef MAPAPI_H
  #include "mapapi.h"
#endif

#ifndef SEEKAPI_H
  #include "seekapi.h"
#endif

#ifndef OBJAPI_H
  #include "objapi.h"         
#endif

#ifndef LISTAPI_H
  #include "listapi.h"        
#endif

/* 

#include "compdial.h"*/   

#define DECLSPEC_IMPORT

//===============================================================
// ТИПЫ ДИАЛОГОВ для AW_DODIALOG задаются в WPARAM  ввел для Kylix     
// в LPARAM задается адрес структуры параметров для диалога
#define    DT_LOADFROMSXF         1  // загрузить из SXF в MAP
#define    DT_GETTYPEOBJECTCREATE 2  // выбрать тип объекта карты из 
                                     // классификатора для создания
#define    DT_OBJECTINFOBEGIN     3  // создать диалог информации об объекте карты
#define    DT_SITECREATEFORMAP    4  // создать карту пользователя для открытой карты
#define    DT_OBJECTINFODESTROY   5  // удалить диалог информации об объекте карты
#define    DT_CLOSEDATAFORMAP     6  // создать диалог закрытия данных карты
#define    DT_SETVIEWSTAFF        7  // установить состав отображения
#define    DT_SETFINDOBJECTPARAM  8  // установить состав поиска
#define    DT_OBJECTINFOCONTINUE  9  // настроить диалог информации об объекте карты на новые парметры
#define    DT_VIEWDATALIST        10 // диалог состава документа
#define    DT_LOADBMP             11 // диалог загрузки BMP
#define    DT_OBJECTINFOBYSEEK    12 // выбор обьекта по поиску
#define    DT_MEDSEEKOBJECT       13 // Диалог перебора объекто
#define    DT_PALETTER            14 // Диалог управления палитрой
#define    DT_GETSITENUMBER       15 // Диалог выбора номера карты       
#define    DT_ZONEFORSELECT       16 // Диалог построения зоны вокруг выделенных
#define    DT_SETPARMPRINT        17 // Диалог параметров печати
#define    DT_MAP2SXF             18 // Диалог выгрузки в sxf
#define    DT_SORT                19 // Диалог сортировки

 // ТИПЫ СООБЩЕНИЙ для Linux для MainMessageHandler параметр aCode

#define    MainLinuxIdent 1

#define    MH_GETCURSORPOS        MainLinuxIdent       // 1 Запросить позицию курсора
#define    MH_SETCURSORPOS        MainLinuxIdent + 1   // 2 Установить позицию курсора
#define    MH_SCREENTOCLIENT      MainLinuxIdent + 2   // 3
#define    MH_CLIENTTOSCREEN      MainLinuxIdent + 3   // 4
#define    MH_CLOSE               MainLinuxIdent + 4   // 5 Удалить окно
#define    MH_GETKEYSTATE         MainLinuxIdent + 5   // 6 Запрос о состоянии клавиш
#define    MH_OPENFILE            MainLinuxIdent + 6   // 7 Открыть файл
#define    MH_GETXCONTEXT         MainLinuxIdent + 7   // 8 Запрос графического контекста  
                                              //   текущего окна карты
#define    MH_AFTERSTART          MainLinuxIdent + 9   // 9 Панораам стартовала надо выполнить настройку меню команд и оболочки
#define    MH_SELVIEWOBJ          MainLinuxIdent +10   // 10 Работа с подсвеченным объектом
                                              // WPARAM = 1 - начать    LPARAM - HOBJ
                                              // WPARAM = 2 - закончить
					      
 enum DATATYPE  //  ТИПЫ КАРТОГРАФИЧЕСКИХ ДАННЫХ  
 {
   DATA_SIT = 1,            // Сайт
   DATA_RST = 2,            // Растр 
   DATA_MTR = 3             // Матрица
 };  

/*  Для Kylix         
 // Параметры вызова диалога открытия файла 
 struct OPENFILEPARM
 {
   long int    Size;     // Размер структуры   
   char       * name;    // строка для размещения результата выбора
   int        namesize;  // размер строки для результата (MAX_PATH)
   const char * title;   // заголовок диалога с учетом языка интерфейса
   const char * filter;  // список строк видов файлов
   int        flags;     // управляющие флажки диалога
   int        index;     // текущий номер строки вида файла при открытии диалога
   const char * path;    // текущая директория при открытии диалога
 };

 // Параметры вызова диалога создания объекта   
 struct DLGCREATEOBJPARM  
 {
  long int    Size;            // Размер структуры
  HMAP        hMap;            // Идентификатор карты
  TASKPARM   *TaskParm;        // Параметры задачи 
  HOBJ        hObj;            // Идентификатор объекта
  HSELECT     hSelect;         // Фильтр
  MEDRSCPARM *MedRscParm;      // Режимы диалога "ВЫБОР СОЗДАВАЕМОГО ОБ ЕКТА КАРТЫ"
 };
			
 // Параметры вызова диалога выбора объекта   
 struct DLGSELECTOBJECTPARMBEGIN  
 {
  long int      Size;          // Размер структуры
  HOBJ          hObj;          // Идентификатор объекта
  MAPDFRAME*    frame;         // place - применяемая система координат (геодезические
                               // координаты не обрабатываются)
  long int      place;         // frame - прямоугольник поиска в соответствии с place,
                               // причем центр прямоугольника обязан совпадать с точкой,
                               // указанной в Position структуры OBJECTFORM
  OBJECTFORM*   objform;			    
  TASKPARM*     taskparm;      // Структура TASKPARM описана в maptype.h 
  HCHOICEOBJECT *choiceobject;
 };

 // Параметры вызова диалога создания карты   
 struct DLGSITECREATEFORMAP  
  {     
   long int   Size;            // Размер структуры     
   HMAP       hMap;            // Идентификатор карты    
   TASKPARM   *TaskParm;       // Структура TASKPARM описана в maptype.h     
   char       *mapname;        // Полное имя карты
  };

 // Параметры вызова диалога закрытия данных карты   
 struct DLGCLOSEDATAFORMAP  
  {     
   long int   Size;            // Размер структуры     
   HMAP       hMap;            // Идентификатор карты    
   long int   datatype;        // Тип данных DATA_SIT, DATA_RST, DATA_MTR    
  };

 // Параметры вызова диалога контекста отображения  
 struct DLGVIEWSTAFF
 {
   long int Size;            // Размер структуры     
   HMAP     hMap;            // Идентификатор карты    
   TASKPARM *TaskParm;       // Структура TASKPARM описана в maptype.h     
   int      *Note;
   long int mode;
 };

 // Параметры вызова диалога контекста поиска  
 struct DLGSEEKOBJ
 {
   long int Size;            // Размер структуры     
   HMAP     hMap;            // Идентификатор карты    
   TASKPARM *TaskParm;       // Структура TASKPARM описана в maptype.h     
   int      *Note;
 };

 // Параметры вызова диалога "Список данных электронной карты."
 struct DLGMAPLIST
 {
   long int    Size;         // Размер структуры     
   HMAP        hMap;         // Идентификатор карты    
   TASKPARM    *TaskParm;    // Структура TASKPARM описана в maptype.h     
   MAPLISTPARM *MapListParm; //
 };		    

 // Параметры вызова диалога копирования объектов на другую карту 
 struct DLGMAPEDITGROUP
 {
   long int    Size;         // Размер структуры     
   HMAP        hMap;         // Идентификатор карты    
   TASKPARM    *TaskParm;    // Структура TASKPARM описана в maptype.h     
   long int    regime;
   HOBJ        hObj;         // Идентификатор объекта карты    
   MEDPROPERTY *medproperty;  // Параметры редактора
 };

 // Выбор объекта по SELECT для поиска
 struct DLGSELECTOBJECTSEEK
 {
   long int    Size;         // Размер структуры         
   HOBJ        hObj;         // Идентификатор объекта карты        
   long int    flag;                 
   HSELECT     hSelect;      // Фильтр поиска
   OBJECTFORM  *objform;			    
   TASKPARM    *TaskParm;    // Структура TASKPARM описана в maptype.h     
 };

 // Параметры вызова диалога настройки цветов 
 struct DLGPALETTECONTROLPARM
 {
   long int       Size;         // Размер структуры         
   HMAP           hMap;         // Идентификатор карты    
   PALETTECNTPARM *paletteparm;
   TASKPARM       *TaskParm;    // Структура TASKPARM описана в maptype.h     
 };

  // Параметры вызова диалога выбора активной карты 
 struct DLGGETSITENUMBER
 {
   long int       Size;         // Размер структуры         
   HMAP           hMap;         // Идентификатор карты    
   long int       sitenumber;   // номер карты
 };

 // Параметры вызова диалога печати
 struct DLGPRINT   
 {
   long int  Size;              // Размер структуры         
   char      filename[MAX_PATH];// имя файла с путем
   long int  scale;             // масштаб
   long int  infile;            // признак выдачи ( 0 - отказ; 1- в файл; 2- на устройство)
   long int  resolution;        // разрешение устройства печати   
 };
		      
 // Параметры вызова диалога построения зоны вокруг выделенных объектов
 struct MCLBUILDZONESELECTED
 {
   long int               Size;         // Размер структуры         
   HMAP                   hMap;         // Идентификатор карты    
   TASKPARM               *TaskParm;    // Структура TASKPARM описана в maptype.h     
   BUILDZONESELECTEDPARM  *zoneselparm; // ПАРАМЕТРЫ ПОСТРОЕНИЯ ЗОНЫ ВОКРУГ ВЫДЕЛЕННЫХ ОБ ЕКТОВ
 };

  // Параметры вызова диалога выгрузки карты в SXF, DIR        
  struct DLGMAP2SXF
  {
   long int               Size;         // Размер структуры         
   HMAP                   hMap;         // Идентификатор карты    
   char                   *NameFile;     // Имя файла 
  };

  // Параметры вызова диалога сортировки карты        
  struct DLGSORT
  {
   long int               Size;         // Размер структуры         
   HMAP                   hMap;         // Идентификатор карты    
  };
*/
#endif  // MWHANDLR_H

