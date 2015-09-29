// 29/11/08

#ifndef MAPEDFRM_H
#define MAPEDFRM_H

#ifndef MEDAPI_H
  #include "medapi.h"   // Описание структур интерфейса MAPAPI
#endif


typedef struct MEDRSCPARM
{
 long int Regime;             // Режим создания
                              // от MED_KEY1 до MED_KEY14
                              // == -1 - режимы создания недоступны в диалоге!
 long int Repeat;             // Повторяемость семантики
                              // == 1 - повторяемая
                              // == 0 - неповторяемая
                              // == -1 - недоступна в диалоге

 long int FlagKey;            // Флаг установки режимов создания
                              // если == 0, то доступность режимов
                              //            устанавливается автоматически,
                              //            иначе в соответствии с Кеу
 long int Rezerv;
 char NameDlg[128];           // Название диалога
 char Key[32];                // 0 - недоступен, 1 - доступен
} MEDRSCPARM;


// Горячие клавиши редактора
#define HOTKEYCOUNT      23
#define KEY_INSERT       0
#define KEY_DELETE       1
#define KEY_REALPOINT    2
#define KEY_SELECTPOINT  3
#define KEY_CREATEPOINT  4
#define KEY_INSNOREPLY   5
#define KEY_LOCK         6
#define KEY_CENTRE       7
#define KEY_COPYPART     8
#define KEY_SAVEPOINT    9
#define KEY_LASTPOINT    10
#define KEY_PREVPOINT    11
#define KEY_REVERT       12
#define KEY_UNDO         13
#define KEY_SPACE        14
#define KEY_HORIZONT     15
#define KEY_VERTICAL     16
#define KEY_RECT         17
#define KEY_VARIABLE     18
#define KEY_AUTO         19
#define KEY_BARSIZE      20
#define KEY_PLACE        21
#define KEY_OPTIONS      22

// Структура для настройки горячих клавиш редактора
typedef struct HOTKEYSPARM
{
char Name[256];            // Название режима
long int Key;              // Код клавиши
long int KeyAdd;           // Код добавочной (альтернативной) клавиши
long int MenuIdent;        // Идентификатор меню
long int Rezerv;
} HOTKEYSPARM;


// Параметры редактора
typedef struct MEDPROPERTY
{
 double FindRadius;        // Радиус поиска
 double Step;              // Шаг цифрования
 double Filter;            // Порог фильтрации
 double ZoneWide;          // Ширина зоны
 double AdjustValue;       // Порог согласования
 double SplineValue;       // Порог сглаживания

 long int IsSetup;              // параметры сеанса заполнены ?
 long int IsDevide;             // Разрезать по рамкам   ?
 long int IsFrameCut;           // Обрезать по рамке   ?
 long int IsEditFrame;          // Редактировать рамку ?

 long int IsSemantic;           // Запрашивать семантику ?
 long int IsClearSelect;        // Сбрасывать выделение ?
 long int Is3dData;             // Трехмерная метрика ?
 long int IsCursor;             // Свои курсоры ?

 long int IsNext;               // Искать продолжение?
 long int IsSeek;               // Искать пересечение?
 long int IsCross;              // Ставить точки пересечения?
 long int FilterType;           // Тип фильтрации

 long int IsGroup;              // Обрабатывать группы?
 long int FindSector;           // Сектор поиска
 long int Spy;                  // Следить за векторизатором?
 long int Speed;                // Скорость векторизации (%)

 long int ViewSemanticCode;     // Просматриваемая семантика
 long int IsStatistic;          // Показывать статистику
 long int PointInSpline;        // Точек в сплайне
 long int AutoCode;             // Код линии оформления автофигур

 long int IsTrace;              // Трассировка
 long int Rezerv;               // Резерв

 long int MapSplineType;        // Тип сплайна для MAP   
 long int SitSplineType;        // Тип сплайна для SIT   
 
 long int IsDrawNumberPoints;   // Рисовать номера точек при создании линейного   // 29/11/08
                                // объекта   

 HOTKEYSPARM HotKey[32];        // Настройка горячих клавиш

} MEDPROPERTY;


// Параметры рассечения
typedef struct CUTOPTIONS
{
 long int InMode;
 long int Incode;
 long int Outcode;
 long int Reserv;
} CUTOPTIONS;

// Параметры поворота и перемещения объекта
typedef struct ROTATEMOVEPARAM
{
 double Angle;                 // Угол поворота в радианах
 DOUBLEPOINT Delta;            // Смещение в метрах
 DOUBLEPOINT StationaryPoint;  // Точка привязки/центр поворота в метрах
 long int Regime;              // Режим перемещения
                               // 0 - по расстоянию,
                               // 1 - по координатам
                               // 2 - по приращению
 long int Scale;               // Признак масштабирования относительно
                               // точки привязки (0 или 1)
} ROTATEMOVEPARAM;


// Параметры размножения объекта
typedef struct MULTIOBJECTPARM
{
 DFRAME Frame;                 // Габариты объекта
 DOUBLEPOINT Offset;           // Смещение относительно начала (нижнего левого угла)

 // Размножение в двух направлениях
 DOUBLEPOINT Step;             // Шаг при размножении в двух направлениях
 DOUBLEPOINT Koordinates;      // Конечные координаты при размножении в двух направлениях
 double Distance;              // Шаг при размножении в одном направлении
 double Angle;                 // Угол поворота в радианах
 long int FlagDirect;          // Размножение в двух или одном направлении
                               // 0 - по двум  направлениям
                               // 1 - в одном направлении
 long int FlagCount;           // Размножение по количеству или
                               // по конечным координатам
                               // (1 - по количеству, 0 - по координатам)
 long int CountX;              // Количество по высоте при размножении в двух направлениях
 long int CountY;              // Количество по ширине при размножении в двух направлениях

 // Размножение в одном направлении
 long int    Count;                 // Количество при размножении в одном направлении
 long int    Log;                   // Запись в журнал транзакций

} MULTIOBJECTPARM;

// Параметры изменения изображения графического объекта
typedef struct UPDATEIMAGEOBJECT
{
 HDRAW DrawLine;      // Указатель на графическое описание линейного объекта
 HDRAW DrawSquare;    // Указатель на графическое описание площадного объекта
 HDRAW DrawPoint;     // Указатель на графическое описание точечного объекта
 HDRAW DrawTitle;     // Указатель на графическое подписи
 long int CodeLine;   // Код линейного объекта
 long int CodeSquare; // Код площадного объекта
 long int CodePoint;  // Код точечного объекта
 long int CodeTitle;  // Код подписи
 long int NoEnableLine;   // Доступность локализации при изменении вида
 long int NoEnableSquare; // 0 - доступно, 1 - нет
 long int NoEnablePoint;
 long int NoEnableTitle;
} UPDATEIMAGEOBJECT;

// Команды создания по сценарию
#define INIT          		1	// Инициализация (очистка) метрики
#define SUBJECT 	      	2	// Создать новый подобъект
#define POINTN          3	// Определенное число точек
#define POINTMIN  	     4	// Максимальное число точек
#define POINTMAX      		5	// Минимальное число точек
#define ANYPOINT       	6	// Ввести произвольное количество точек
#define MYPOINT        	7	// Взять точку со своего объекта
#define OTHERPOINT     	8	// Взять точку с другого объекта
#define SPLINEON     	 	9	// Включить режим перестроения метрики по сплайну
#define BARON     		    10	// Включить режим перестроения метрики по //прямоугольнику
#define STRIPEON     	 	11	// Включить режим перестроения метрики по полосе
#define CIRCLEON     		 12	// Включить режим перестроения метрики по //окружности
#define ARBITRON     		 13	// Выключить режимы принудительного перестроения
#define ATTRIBUTE     		14	// Ввести семантику по бланку
#define SETTEXT     		  15	// Ввести текст
#define MEMOPOINT     		16	// Запомнить последнюю введенную точку
#define REMEMBERPOINT   17 // Добавить точку с извлечением из памяти
#define GROUPHEAD       18 // Добавить описание главного
#define GROUPSUBORD     19	// Добавить описание подчиненного объекта
#define ENDGROUP        20	// Закончить описание группы
#define COMMIT          21	// Записать объект
#define QUIT     	     	22	// Завершить режим создания
#define ANYDIRECT     		23	// Выключить режимы гориз. и верт.
#define STAFF           24 // Создать комбинированный КП
#define STAFFON         25 // Начало создания комбинированного КП
#define STAFFOFF        26 // Завешение создания комбинированного КП
#define POINT1		        27	// Ввести одну точку
#define POINT2			       28	// Ввести две точки
#define POINT3		       	29	// Ввести три точки
#define SEMANTICCODE 	 	30	// Добавить семантику по коду

// Для создания объектов по сценарию
typedef struct TESCENE   
{
  char SceneId[256];            // Идентификатор сценария (индивидуален для каждого объекта)
  long int  ActionCount;        // Количество процессов в сценарии
  long int  Rezerv;
}TESCENE;

typedef struct SCACTION
{
  char ActionMessage[256];      // Коментарий процесса
  long int ActionType;          // Тип процесса
  long int Number;              // Номер для нумерованных команд (POINTN, MEMOPOINT и т.д)
} SCACTION;


// Режимы для функции medSeekObject (диалог перебора объектов)
enum SEEKREGIME
{
  SEEK_RESTORE        = 0, // восстановление отредактированного объекта
  SEEK_RESTORE_DELETE = 1, // восстановление удаленных объектов
  SEEK_CREATE         = 2, // создание объекта по координатам из текстового файла
  SEEK_MARK_DELETE    = 3, // удаление выделенных объектов
  SEEK_MARK_DELETESUB = 4, // удаление подобъектов выделенных объектов
  SEEK_MARK_CREATESUB = 5, // создание подобъектов выбранного объекта по выделенным
  SEEK_MARK_COPY      = 6, // копирование выделенных объектов на другую карту
  SEEK_MARK_MODIFY    = 7, // изменение кода выделенных объектов
  SEEK_MARK_CUT       = 8, // рассечение выделенных объектов
  SEEK_MARK_CROSS     = 9, // создание точек пересечение выделенных объектов
  SEEK_MARK_CONSENT   = 10,// согласование выделенных объектов
  SEEK_MARK_VISIBILITY= 11,// изменение видимости выделенных объектов
  SEEK_MARK_DIRECT    = 12,// изменение направления цифрования выделенных объектов
  SEEK_MARK_SPLINE    = 13,// сглаживание выделенных объектов
  SEEK_MARK_FILTER    = 14,// фильтрация выделенных объектов
  SEEK_MARK_ADDHIGHT  = 15 // добавление высоты в выделенные объекты
};

// Режимы для функции medMessageSet
//       (Диалог запроса режима объединения объектов)
enum SETREGIME             
{
  SET_ONE   = 1,           // отдельный объект
  SET_GROUP = 2,           // вся группа
  SET_HIERARCHY = 3        // иерархия
};

extern "C"
{
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//            ДИАЛОГИ  РЕДАКТОРА ( СТАНДАРТНЫЙ ВИД )
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 // Диалог выбора вида объекта из файла ресурсов
 // ( только для редактора карты )
 // hmap - идентификатор открытой векторной карты
 // hobj - идентификатор объекта
 // hselect - фильтр
 // (если hselect == 0 - фильтр не используется)
 //           (если hselect == 0 - фильтр не используется)
 //            Если hselect != 0 и в hselect установлена
 //            карта, то диалог работает по одной карте.
 //            Если в hselect карта не установлена, диалог
 //            работает по всем картам документа.
 // возвращает внутренний код объекта
 // при ошибке или отказе возвращает 0
 long int _export WINAPI medChoiceTypeObjectSpecific
                        (HMAP hmap, TASKPARM *taskparm,
                         HOBJ hobj, HSELECT hselect,
                         MEDRSCPARM *medparm);


 // Диалог выбора вида графического линейного объекта
 // ( только для редактора карты )
 //  Выбрать графический линейный объект для редактора карты
 //  hmap - идентификатор открытой векторной карты
 //  hobj - идентификатор объекта
 //  hselect - фильтр
 //           (если hselect == 0 - фильтр не используется)
 //            Если hselect != 0 и в hselect установлена
 //            карта, то диалог работает по одной карте.
 //            Если в hselect карта не установлена, диалог
 //            работает по всем картам документа.
 // name - заголовок диалога
 // При нормальном завершении внутренний код объекта равен 0
 // при ошибке или отказе возвращает 0

 long int _export WINAPI medChoiceLineImageSpecific
                        (HMAP hmap,TASKPARM *taskparm,
                         HOBJ object, HSELECT hselect,
                         MEDRSCPARM *medparm);


 // Диалог выбора вида графического площадного объекта
 // ( только для редактора карты )
 //  hmap - идентификатор открытой векторной карты
 //  hobj - идентификатор объекта
 //  hselect - фильтр
 //           (если hselect == 0 - фильтр не используется)
 //            Если hselect != 0 и в hselect установлена
 //            карта, то диалог работает по одной карте.
 //            Если в hselect карта не установлена, диалог
 //            работает по всем картам документа.
 // name - заголовок диалога
 // При нормальном завершении внутренний код объекта равен 0
 // при ошибке или отказе возвращает 0

 long int _export WINAPI medChoiceSquareImageSpecific
                        (HMAP hmap, TASKPARM *taskparm,
                         HOBJ object, HSELECT hselect,
                         MEDRSCPARM *medparm);


 // Установка параметров редактора
 // hmap - идентификатор открытой векторной карты
 // parameters - структура параметров
 // Возвращает - 0 - отказ
 //              1 - новые установки
 //              -1 - установки по умолчанию

 long int _export WINAPI medSetEditParameters
                        (HMAP hmap, TASKPARM *taskparm,
                         MEDPROPERTY *parameters);


 // Установка/ изменение текста однострочной подписи
 // title - строка для текта
 // length - длина строки
 // name - заголовок диалога
 //        если == 0 - заголовок из ресурсов
 // При отказе возвращает 0, иначе 1

 long int _export WINAPI medSetTitle(TASKPARM *taskparm,
                                     char *title, long int length,
                                     char *name);

 // Установка/ изменение текста многострочной подписи
 // hobj - идентификатор объекта типа ПОДПИСЬ
 // subject - номер продобъекта
 // При отказе возвращает 0, иначе 1

 long int _export WINAPI medSetPolyTitle(TASKPARM *taskparm,
                                         HOBJ hobj, long int subject);


 // Вставка точки
 // pointcount - общее число точек
 // oldpoint - предыдущая точка
 // firstpoint - текущая точка
 // newpoint - новая точка
 // При отказе возвращает 0, иначе 1

 long int _export WINAPI medInsertPoint(TASKPARM *taskparm,
                                        long int pointcount,
                                        DOUBLEPOINT oldpoint,
                                        DOUBLEPOINT firstpoint,
                                        DOUBLEPOINT *newpoint);


 // Создание подписи шаблона
 // info - объект типа ШАБЛОН
 // При отказе возвращает 0, иначе 1

 long int _export WINAPI medCreateMixedLabel(HMAP hmap,TASKPARM *taskparm,
                                             HOBJ info);


 // Изменение текста сложной подписи
 // info - объект типа ПОДПИСЬ или ШАБЛОН
 // При отказе возвращает 0, иначе 1

 long int _export WINAPI medSetMixedLabel(HMAP hmap,TASKPARM *taskparm,
                                          HOBJ info);


 // Диалог смены карты/растра
 // number - номер карты/растра
 // type - тип (0 - карта, 1 - растр)
 // При отказе возвращает 0, иначе 1

 long int _export WINAPI medSetMapNumber(HMAP hmap, TASKPARM *taskparm,
                                         long int *number, long int type);


 // Диалог смены карты/растра
 // number - номер карты/растра
 // type - тип (0 - карта, 1 - растр)
 // count - количество открытых карт.растров
 // multy - ( 1- множественный выбор, 0 - нет)
 // При отказе возвращает 0, иначе 1
 
 long int _export WINAPI medSetListMapNumber(HMAP hmap, TASKPARM *taskparm,
                                         long int *number, long int type,
                                         long int count, long int multy);


 // Диалог выбора способа создания объекта:
 // - произвольный контур, горизонтальный прямоугольник,
 //   наклонный прямоугольник и т.д.
 // name - название диалога
 // mode - способ создания (идентификатор от MED_KEY1 до MED_KEY14)
 //        = -1 - режимы создания недоступны в диалоге!
 // local - локализация(тип) объекта
 // При отказе возвращает 0, иначе 1

 long int _export WINAPI medSetCreationMode(TASKPARM *taskparm,
                                            char *name,
                                            long int *mode,
                                            long int local);

 // Обновление семантики выделенных объектов
 // При ошибке или отказе возвращает 0, иначе 1

 long int _export WINAPI medUpdateSemanticBySelected(HMAP hmap,
                                                     TASKPARM *taskparm);


 // Запрос параметров поворота и перемещения объекта
 // Входные параметры : rotateparm.Regime
 //                                0 - по расстоянию,
 //                                1 - по координатам
 //                                2 - по приращению
 //                     rotateparm.StationaryPoint (точка привязки/центр поворота в метрах)
 //                     rotateparm.Scale (0 или 1)
 //                     frame (для Regime == 1 - габариты в метрах)
 // Выходные параметры: rotateparm.Regime
 //                     rotateparm.StationaryPoint
 //                     rotateparm.Angle
 //                     rotateparm.Delta
 // При ошибке или отказе возвращает 0,
 // иначе 1 и заполняет структуру rotateparm

 long int _export WINAPI medGetRotateParam(HMAP hmap, TASKPARM *taskparm,
                                           ROTATEMOVEPARAM *rotateparm,
                                           DFRAME frame);


 // Диалог выбора макетов и смены карты
 // mapnumber - номер текущей карты
 // groupnumber - номер группы в макете
 // property - структура параметров редактора
 // При ошибке или отказе возвращает 0,
 // иначе 1, заполняет mapnumber, groupnumber
 long int _export WINAPI medSetMaket(HMAP hmap, TASKPARM *taskparm,
                                     long int *mapnumber,
                                     long int *groupnumber,
                                     MEDPROPERTY *property);


 // Диалог перебора объектов
 // regime (SEEKREGIME) - режимы работы с объектами
 // hobj - выбранный объект (если = 0,
 //                          идет работа с выделенными объектами)
 // property - структура параметров редактора
 // При ошибке или отказе возвращает 0,
 long int _export WINAPI medSeekObject(HMAP hmap, TASKPARM *taskparm,
                                       long int regime, HOBJ hobj,
                                       MEDPROPERTY *property);

 // Диалог редактирования текста подписи выделенных объектов
 // При ошибке или отказе возвращает 0, иначе 1
 long int _export WINAPI medSeekEdit(HMAP hmap, TASKPARM *taskparm);


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//            ДИАЛОГИ  РЕДАКТОРА ( ПРОФЕССИОНАЛЬНЫЙ ВИД )
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


 // Вызов диалога выбора вида графического объекта
 // с установкой текущих параметров редактора
 // object - идентификатор объекта
 // filter - фильтр
 // (если filter == 0 - фильтр не используется)
 // возвращает код объекта или 0 при ошибке

 long int _export WINAPI medChoiceTypeGraphics(HMAP hmap,
                                               TASKPARM *taskparm,
                                               HOBJ object,
                                               HSELECT filter/*= 0*/,
                                               MEDRSCPARM *medparm/*= 0*/);


 // Настройка границ видимости
 // hrsc - идентификатор файла ресурсов
 // bot - нижняя граница
 // top - верхняя граница
 // botdefault - умалчиваемое значение из классификатора
 // При отказе возвращает 0, иначе 1

 long int _export WINAPI medSetBotTop(TASKPARM *taskparm,
                                      HRSC hrsc,
                                      long int *bot, long int *top,
                                      long int *botdefault);


 // Ввод/изменение угла разворота
 // value - значение угла (в радианах)
 // При отказе возвращает 0, иначе 1

 long int _export WINAPI medSetTurnAngle(TASKPARM *taskparm,
                                         double *value);



 // Ввод/изменение параметров рассечения объекта
 // options - структура параметров
 // При отказе возвращает 0, иначе 1

 long int _export WINAPI medSetCutParameters(HMAP hmap, TASKPARM *taskparm,
                                             CUTOPTIONS *options);


 // Ввод размеров прямоугольника
 // size - размер прямоугольника
 // При отказе возвращает 0, иначе 1

 long int _export WINAPI medSetBarSize(TASKPARM *taskparm,
                                       DOUBLEPOINT *size);


 // Диалог установки радиуса
 // При отказе возвращает 0, иначе 1

 long int _export WINAPI medSetRadius(TASKPARM *taskparm,
                                      double *radius);

 // Диалог установки радиуса со знаком "-"
 // При отказе возвращает 0, иначе 1

 long int _export WINAPI medSetRadiusSign(TASKPARM *taskparm,
                                         double *radius);

 // --------------------------------------------------------------
 //    ДИАЛОГИ РЕДАКТИРОВАНИЯ СЕМАНТИКИ ВЫДЕЛЕННЫХ ОБ ЕКТОВ
 // --------------------------------------------------------------

 // Добавление семантики в выделенные объекты
 // При ошибке или отказе возвращает 0, иначе 1

 long int _export WINAPI medAddSemanticBySelected(HMAP hmap,
                                                  TASKPARM *taskparm);


 // Удаление семантики у выделенных объектов
 // При ошибке или отказе возвращает 0, иначе 1

 long int _export WINAPI medDeleteSemanticBySelected(HMAP hmap,
                                                     TASKPARM *taskparm);

 // Обновление кода семантической характеристики
 // у выделенных объектов
 // При ошибке или отказе возвращает 0, иначе 1

 long int _export WINAPI medSemanticCodeUpdateBySelected(HMAP hmap,
                                                         TASKPARM *taskparm);


 // Редактирование семантических характеристик списком
 // у выделенных объектов
 // При ошибке или отказе возвращает 0, иначе 1

 long int _export WINAPI medEditSemanticListBySelected(HMAP hmap,
                                                       TASKPARM *taskparm);


 // Диалог копирования объектов на другую карту
 // mapnumber - номер текущей карты
 // hobj - входной/выходной объект
 //       (содержит код объекта и его внешний вид)
 // selected - признак наличия выбранного объекта или нет (0 или 1)
 // При ошибке или отказе возвращает 0,
 // иначе 1 или -1 и заполняет hobj (сегмент, локализацию, код,
 //                           внешний вид, текущую карту)
 // если код возврата = -1 - обрезать переносимые объекты
 //                          по выбранному hobjsel

 long int _export WINAPI medCopyObjectToMap(HMAP hmap, TASKPARM *taskparm,
                                            long int mapnumber,
                                            HOBJ hobj,
                                            long int selected);

 // Удаление семантики, не соответствующей коду объекта
 // asc - = 1 - задавать вопрос при удалении
 //       = 0 - удалять молча
 // При ошибке возвращает 0

 long int _export WINAPI medDeleteAbsurdSemantic(TASKPARM *taskparm,
                                                 HOBJ object, int asc);

 // Запросить координаты диалога из ini файла
 // name - название идентификатора диалога
 // ininame - имя ini файла
 // rect - координаты диалога

 long int _export WINAPI medReadSizeDialog(const char *name, const char *ininame,
                                      RECT &rect);

 // Сохранить размеры диалога в ini файл
 // name - название идентификатора диалога
 // ininame - имя ini файла
 // rect - координаты диалога
 long int _export WINAPI medWriteSizeDialog(const char *name, const char *ininame,
                                       RECT rect);

 // Настройка горячих клавиш
 // При ошибке или отказе возвращает 0,
 long int _export WINAPI medSetHotKey(TASKPARM *taskparm,
                                      HOTKEYSPARM *hotkey, int count);

 // Инициализация горячих клавиш
 // При ошибке или отказе возвращает 0,
 long int _export WINAPI medInitHotKey(TASKPARM *taskparm, HOTKEYSPARM *hotkey, 
                                       int count);
                                       
}       // extern "C"

#endif  // MAPEDFRM
