
#if !defined(MAPRSC_H)
#define MAPRSC_H

#ifndef MAPERROR_H
  #include "maperror.h"
#endif

#ifndef MAPSEM_H
  #include "mapsem.h"
#endif

#ifndef MAPGDI_H
  #include "mapgdi.h"
#endif

#ifndef MAPVERSN_H                 
  #include "mapversn.h"
#endif

#ifdef HIDE3D
 #define HIDERSC3D                 
#endif

#ifndef HIDERSC3D                  
#ifndef DRWTREE_H
  #include "drwtree.h"
#endif

#ifndef RSCFL3D_H
  #include "rscfl3d.h"
#endif

#endif    // HIDERSC3D            

#ifdef LP64MODEL
 #define MAXMEMBUFFERSIZE 1024L
 #define MEMAUGMENT 256
#endif

class TMap;
class TFontDraw;

// Работа с пямятью
typedef struct MEMHEAD
{
  char * Previous;              // Адрес предшествующего элемента памяти
  long Length;                  // Длина элемента памяти
  long Offset;                  // Начало свободного места
  long Reserv;                  // Резерв. = 0                        
}
 MEMHEAD;

#define AUGMENTOBJECT    100
#define AUGMENTSEMANTIC   20
#define AUGMENTSEGMENT    20
#define AUGMENTIML        20
#define AUGMENTTXT        10
#define AUGMENTFRM        10                       
#define AUGMENTGRS       100
#define AUGMENTRECORD    400                       

#ifndef HIDEIML                 
#ifdef __cplusplus              
 struct IMLLIST;                
#else
 #include "mapgdiex.h"           
#endif
#endif

 struct TABOBJ;
 struct TABDEF;
 struct TABIML;
 struct TABSEM;
 struct TABPOS;
 struct TABLIM;
 struct IMAGEVALUE;
 struct TABPAL;
 struct TABGRS;
 struct TABSEG;
 struct TABCLS;
 struct RELATION;               
 struct TABP3D;                 
 struct TABTAB;                 
 struct TABL3D;                 
 struct TABFRM;                 

typedef struct RSCHEAD
{
  ULONG Label   ;    // МЕТКА
  ULONG Length  ;    // ДЛИНА ФАЙЛА
  ULONG Version ;    // ВЕРСИЯ СТРУКТУРЫ RSC 0x0700
  ULONG Series  ;    // КОДИРОВКА
  ULONG Style   ;    // HОМЕР СОСТОЯHИЯ ФАЙЛА
  ULONG Mode    ;    // HОМЕР МОДИФИКАЦИИ СОСТОЯHИЯ
  ULONG Language;    // 1 - АНГЛИЙСКИЙ, 2 - РУССКИЙ
  ULONG MaxKey  ;    // МАКСИМАЛЬНЫЙ ИДЕНТИФИКАТОР ТАБЛИЦЫ ОБ'ЕКТОВ

  char               Date[8] ;    // ДАТА СОЗДАHИЯ ФАЙЛА
  char               Type[32];    // ТИП КАРТЫ
  char               Name[32];    // УСЛОВHОЕ HАЗВАHИЕ КЛАССИФИК.
  char               Code[8] ;    // КОД КЛАССИФИКАТОРА

  ULONG Scale   ;    // МАСШТАБ КАРТЫ
  ULONG ScaleRow;    // 0 - ПЕРВЫЙ МАСШТАБНЫЙ РЯД
                                  // 1 - ВТОРОЙ МАСШТАБНЫЙ РЯД

  ULONG Off_Obj ;    // СМЕЩЕHИЕ HА ТАБЛИЦУ ОБ'ЕКТОВ
  ULONG Len_Obj ;    // ДЛИHА ТАБЛИЦЫ
  ULONG Num_Obj ;    // ЧИСЛО ЗАПИСЕЙ

  ULONG Off_Sem ;    // СМЕЩЕHИЕ HА ТАБЛИЦУ СЕМАHТИКИ
  ULONG Len_Sem ;    // ДЛИHА ТАБЛИЦЫ
  ULONG Num_Sem ;    // ЧИСЛО ЗАПИСЕЙ

  ULONG Off_Cls ;    // СМЕЩЕHИЕ HА КЛАССИФИКАТОР
  ULONG Len_Cls ;    // ДЛИHА ТАБЛИЦЫ
  ULONG Num_Cls ;    // ЧИСЛО ЗАПИСЕЙ

  ULONG Off_Def ;    // СМЕЩЕHИЕ HА ТАБЛИЦУ УМОЛЧАHИЙ
  ULONG Len_Def ;    // ДЛИHА ТАБЛИЦЫ
  ULONG Num_Def ;    // ЧИСЛО ЗАПИСЕЙ

  ULONG Off_Pos ;    // СМЕЩЕHИЕ HА ТАБЛИЦУ ВОЗМ.СЕМ
  ULONG Len_Pos ;    // ДЛИHА ТАБЛИЦЫ
  ULONG Num_Pos ;    // ЧИСЛО ЗАПИСЕЙ

  ULONG Off_Seg ;    // СМЕЩЕHИЕ HА ТАБЛИЦУ СЕГМЕHТОВ
  ULONG Len_Seg ;    // ДЛИHА ТАБЛИЦЫ
  ULONG Num_Seg ;    // ЧИСЛО ЗАПИСЕЙ

  ULONG Off_Lim ;    // СМЕЩЕHИЕ HА ТАБЛИЦУ ПОРОГОВ
  ULONG Len_Lim ;    // ДЛИHА ТАБЛИЦЫ
  ULONG Num_Lim ;    // ЧИСЛО ЗАПИСЕЙ

  ULONG Off_Par ;    // СМЕЩЕHИЕ HА ТАБЛИЦУ ПАРАМЕТРОВ
  ULONG Len_Par ;    // ДЛИHА ТАБЛИЦЫ
  ULONG Num_Par ;    // ЧИСЛО ЗАПИСЕЙ

  ULONG Off_Prn ;    // СМЕЩЕHИЕ HА ТАБЛИЦУ ПАР.ПЕЧАТИ
  ULONG Len_Prn ;    // ДЛИHА ТАБЛИЦЫ
  ULONG Num_Prn ;    // ЧИСЛО ЗАПИСЕЙ

  ULONG Off_Pal ;    // СМЕЩЕHИЕ HА ТАБЛИЦУ ПАЛИТР
  ULONG Len_Pal ;    // ДЛИHА ТАБЛИЦЫ
  ULONG Num_Pal ;    // ЧИСЛО ЗАПИСЕЙ

  ULONG Off_Txt ;    // СМЕЩЕHИЕ HА ТАБЛИЦУ ШРИФТОВ
  ULONG Len_Txt ;    // ДЛИHА ТАБЛИЦЫ
  ULONG Num_Txt ;    // ЧИСЛО ЗАПИСЕЙ

  ULONG Off_Iml ;    // СМЕЩЕHИЕ HА ТАБЛИЦУ БИБЛИОТЕК
  ULONG Len_Iml ;    // ДЛИHА ТАБЛИЦЫ
  ULONG Num_Iml ;    // ЧИСЛО ЗАПИСЕЙ

  ULONG Off_Grs ;    // СМЕЩЕHИЕ HА ТАБЛИЦУ ИЗОБРАЖЕНИЙ СЕМАНТИКИ
  ULONG Len_Grs ;    // ДЛИHА ТАБЛИЦЫ
  ULONG Num_Grs ;    // ЧИСЛО ЗАПИСЕЙ

  ULONG Off_Tab ;    // СМЕЩЕHИЕ HА ТАБЛИЦУ ТАБЛИЦ
  ULONG Len_Tab ;    // ДЛИHА ТАБЛИЦЫ
  ULONG Num_Tab ;    // ЧИСЛО ЗАПИСЕЙ
  char            ObjectCode ;    // ФЛАГ ИСПОЛЬЗОВАНИЯ КЛЮЧЕЙ КАК КОДОВ
  char            ColorStyle ;    // HОМЕР МОДИФИКАЦИИ СОСТОЯHИЯ ПАЛИТРЫ 
  char             Reserv1[2] ;   // РЕЗЕРВ = 0                  
  ULONG CharCode3D;   // РЕЗЕРВ,НЕ ИСПОЛЬЗОВАТЬ
  ULONG Series3D  ;   // РЕЗЕРВ,НЕ ИСПОЛЬЗОВАТЬ
  ULONG Reserv[5] ;   // РЕЗЕРВ = 0

  ULONG CharCode  ;   // КОДИРОВКА
  ULONG ColorCount;   // КОЛИЧЕСТВО ЦВЕТОВ В ПАЛИТРЕ
}
  RSCHEAD;

// Ссылки на записи файлов
typedef struct RSCRECORD
{
  ULONG Code;         // КОД БИЛИОТЕКИ 3D ПАРАМЕТРОВ
  ULONG Offset;       // АДРЕС В ПАМЯТИ
  ULONG Flag;         // ФЛАГ ИЗМЕНЕНИЯ,УДАЛЕНИЯ ...
  ULONG Type;         // ТИП  ЗАПИСИ
  LONG         Key;          // КЛЮЧ ЗАПИСИ
}
  RSCRECORD;

// описание объектов
typedef struct RSCOBJ
{
   ULONG      Code    ; // КЛАССИФИКАЦИОННЫЙ КОД
   unsigned short int Local   ; // ХАРАКТЕР ЛОКАЛИЗАЦИИ
   unsigned short int Segment ; // Н0МЕР СЛОЯ ( НЕ БОЛЕЕ 256)
   unsigned short int Scale   ; // 1 - ОБ'ЕКТ МАСШТАБИРУЕТСЯ
                                // 0 - ОБ'ЕКТ НЕ МАСШТАБИРУЕТСЯ
   unsigned short int Bot     ; // НИЖНЯЯ ГРАНИЦА ВИДИМОСТИ
   unsigned short int Top     ; // ВЕРХНЯЯ ГРАНИЦА ВИДИМОСТИ
   unsigned char      Name[32]; // НАЗВАНИЕ ( ТЕКСТ ДО 30 СИМВОЛОВ)
}
               RSCOBJ;

#define MAXSEMANTICCODE  65500                     
// описание семантик
typedef struct RSCSEM
{
  unsigned short int Code     ; // КЛАССИФИКАЦИОННЫЙ КОД
  unsigned short int Type     ; // ТИП ЗНАЧЕНИЯ ЭЛЕМЕНТА (SEMTYPE)
  unsigned short int Reply    ; // 1 - ОБ'ЕКТ МАСШТАБИРУЕТСЯ
  unsigned char      Name[32] ; // НАЗВАНИЕ  ( ТЕКСТ ДО 30 СИМВОЛОВ)
  unsigned char      Unit[8]  ; // ЕДИНИЦА ИЗМЕРЕНИЯ (СОКР)
}
               RSCSEM;

typedef struct RSCSEG
{
  ULONG Length   ;   // ДЛИНА ЗАПИСИ
           char     Name[32] ;   // HАЗВАHИЕ
           char     Short[16];   // КОРОТКОЕ ИМЯ СЛОЯ
  unsigned char     Number   ;   // НОМЕР СЕГМЕHТА
  unsigned char     Order    ;   // ПОРЯДОК ВЫБОРА СЕГМЕHТА
  unsigned short    Count    ;   // ЧИСЛО СЕМАНТИК СЛОЯ
  LONG          Code[1]  ;   // СЕМАНТИКА СЛОЯ
}
  RSCSEG;

// описание умолчаний

typedef struct RSCDEF
{
 float MinValue;   // МИНИМАЛЬНОЕ ЗНАЧЕНИЕ СЕМАНТИКИ ДЛЯ ОБ'ЕКТА
 float DefValue;   // УМАЛЧИВАЕМОЕ ЗНАЧЕНИЕ СЕМАНТИКИ ДЛЯ ОБ'ЕКТА
 float MaxValue;   // МАКСИМАЛЬНОЕ ЗНАЧЕНИЕ СЕМАНТИКИ ДЛЯ ОБ'ЕКТА
}
               RSCDEF;

typedef struct VIEPAR
{
   ULONG Length  ;    /* ДЛИHА ЗАПИСИ                  */
   unsigned short int Incode  ;    /* ВHУТРЕHHИЙ КОД ОБ'ЕКТА        */
   unsigned short int Number  ;    /* HОМЕР ФУHКЦИИ ОТОБРАЖЕHИЯ     */
   unsigned char      Param   ;    /* ПАРАМЕТРЫ ФУHКЦИИ ОТОБРАЖЕHИЯ */
}
                   VIEPAR;

typedef struct HEADDEFCLS
{
  unsigned short int Flag     ;    // 0x7FFF - идентификатор начала
                                   // записи
  unsigned short int Free     ;    // количество свободных записей
  unsigned short int Number   ;    // общее количество записей
  short int          Reserv   ;    // Резерв. = 0                        
}
               HEADDEFCLS;

// ------------------------------------------------------------------
// Таблица идентификаторов ресурсов для объекта
// i элемент содержит идентификаторы для объекта с i внутренним кодом
// -------------------------------------------------------------------

typedef struct TABRSC
  {
    TABOBJ *           TabObj;    // Характеристики объекта
    TABPOS *           TabPos;    // Возможные семантики (нет - 0)
    TABLIM *           TabLim;    // Пороги  (нет - 0)
    VIEPAR *           ViewParm;  // Параметры изображения
    VIEPAR *           PrintParm; // Параметры печати
    TABP3D *           Dim3Parm1; // 3D параметры первого уровня
    TABP3D *           Dim3Parm2; // 3D параметры второго уровня
    TABP3D *           Dim3Parm3; // 3D параметры третьего уровня
    ULONG      Excode;    // Внешний код объекта
    unsigned short int Function;  // Функция для отображения
    unsigned short int Flags;     // Флаг исправлений
    unsigned short int Segment;   // Сегмент
    unsigned char      Local;     // Локализация
    unsigned char      Extloc;    // Векторность
    unsigned short int Extend;    // Номер расширения (номер в серии)
    unsigned char      Extsem;    // Признак запроса семантики для отображения
    unsigned char      Reserv;    // Резерв
  }
    TABRSC;


// ------------------------------------------------------------------
// Таблица идентификаторов ресурсов графического изображения семантики
// i элемент содержит идентификаторы для группы с i номером
// группы может и не быть - все 0
// -------------------------------------------------------------------

typedef struct TABGRSITEM
  {
    ULONG  Code     ;   // Код семантики
    unsigned short int Number   ;   // Порядковый номер группы отображения
    unsigned short int Default  ;   // Для умалчиваемого значения 1,иначе 0
    ULONG  Value    ;   // Значение семантики
    ULONG  Function ;   // Номер функции отображения группы
    IMAGEVALUE *       Item     ;   // Номер  и параметры изображения
  }
    TABGRSITEM;

 enum FLFORRSC      // ФЛАГИ ДЛЯ TABRSC
   {
     rscFREE    = 0,  // Исправлений не было
     rscLOWFONT = 1,  // Этот шрифт понижается
     rscKILL    = 2,  // Объект удален совсем
     rscDEL     = 4,  // Объект удален в текущем сеансе работы
     rscSERIA   = 8,  // Объекты входят в серию
     rscGETH    = 16, // Объекты собираются
     rscPICT    = 32  // Выделенный объект
   };

enum FLFORRECORD      // ФЛАГИ ДЛЯ TABRECORD
   {
     recFREE    = 0,  // Исправлений не было
     recCORR    = 1,  // Была правка
     recDEL     = 2   // Запись удалена
     /*
     rscDEL     = 4,  // Объект удален в текущем сеансе работы
     rscSERIA   = 8,  // Объекты входят в серию
     rscGETH    = 16, // Объекты собираются
     rscPICT    = 32  // Выделенный объект
     */
   };

  enum FRAMEINCODERSC
  {
   MAXSEMANTICCOUNT = 1024,
   COLOROFSERVOBJECT = 13,         // индекс цвета служебных объектов
   COUNTOFTAB        = 14,         // количество таблиц
  };

  enum  IDENTFORRSC
   {
     HEADIDENT      =  0x7FFF, // идентификатор начала умолчаний
                               // или классификатора
   };


// Структура для работы с вычислением семантики по формуле       
typedef struct FORMOPER  // Операнд
{
   double Value;   // Значение
   long Number;    // Номер узла с которого взять значение (с 1)
   char Flag;      // 0 - не заполнен, 1 - работа с узлом номер Number,
                   // 2 - можно брать значение - все посчитано
   char Sign;      // 0 - брать прямую операцию
                   // 1 - Флаг обратного знака операнда(у +v -v, у *v - 1/v)
   char Res1;
   char res2;
}
 FORMOPER;

typedef struct FORMNODE
{
  FORMOPER Oper[10]; // Операнды
  long Number;       // Номер узла(с 1)
  long Parent;       // Номер узла родителя (с 1)
  long Rezerv;       // Резерв
  char  Type;        // Тип операции
  char Count;        // Реальное количество операндов (макс 10)(с 1)
  char Bracket;      // Tип скобок ( 0 - нет, 1 - круглые, 2 - квадратные,
                     //                       3 - фигурные )
  char Close;        // 0 - нет ответной скобки, 1 - узел закрыт
}
  FORMNODE;




// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ КЛАССИФИКАТОР ЭЛЕКТРОННОЙ ВЕКТОРНОЙ КАРТЫ   +++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef class _DLLCLASS TMapRsc
{

  public :
  enum FLTRSC      // ФЛАГИ ДЛЯ TABRSC
   {
     FREE    = ::rscFREE,    // Исправлений не было
     LOWFONT = ::rscLOWFONT, // Этот шрифт понижается
     KILL    = ::rscKILL,    // Объект удален совсем
     DEL     = ::rscDEL,     // Объект удален в текущем сеансе работы
     SERIA   = ::rscSERIA,   // Объекты входят в серию
     GETH    = ::rscGETH     // Объекты собираются
   };

  enum
   {
     FIRSTSERVEXCODE  = ::FIRSTSERVEXCODE , // начало внешних кодов служебных
     LINESERVEXCODE   = ::LINESERVEXCODE  , // внешний код служебного линейного
     LINESERVINCODE   = ::LINESERVINCODE  , // внутренний код служебного линейного
     SQUARESERVEXCODE = ::SQUARESERVEXCODE, // внешний код служебного площадного
     SQUARESERVINCODE = ::SQUARESERVINCODE, // внутренний код служебного площадного
     POINTSERVEXCODE  = ::POINTSERVEXCODE , // внешний код служебного  точечного
     POINTSERVINCODE  = ::POINTSERVINCODE , // внутренний код служебного точечного
     TEXTSERVEXCODE   = ::TEXTSERVEXCODE  , // внешний код служебного текста
     TEXTSERVINCODE   = ::TEXTSERVINCODE  , // внутренний код служебного текста
     VECTSERVEXCODE   = :: VECTSERVEXCODE , // внешний код служебного векторного
     VECTSERVINCODE   = ::VECTSERVINCODE  , // внутренний код служебного векторного
     COMSERVEXCODE    = ::COMSERVEXCODE   , // внешний код служебного шаблона
     COMSERVINCODE    = ::COMSERVINCODE   , // внутренний код служебного шаблона
     MAXSEMANTICCOUNT = ::MAXSEMANTICCOUNT,
   };

  enum
   {
     SERVOBJECT        = ::SERVOBJECT,        // количество служебных объектов
     COUNTOFTAB        = ::COUNTOFTAB,        // количество таблиц
     COLOROFSERVOBJECT = ::COLOROFSERVOBJECT, // индекс цвета служебных объектов
   };

 /****************************************************************
 *                                                               *
 *             ОТКРЫТЬ/ЗАКРЫТЬ ДОСТУП К ФАЙЛУ RSC                *
 *                                                               *
 ****************************************************************/

public :

 TMapRsc();

 ~TMapRsc();

 // Открыть доступ к классификатору
 // Построить таблицу адресов
 // При ошибке возвращает ноль
 int OpenRsc(const char * rsc, int mode  = 0);

 // Запрос памяти и заполнение таблиц для работы
 // c новым классификатором
 // Если стандартная семантика не нужна createsem = 0
 // при ошибке возвращает 0
 int CreateRsc();
 int CreateRsc(char * name, RSCCREATE * rsccreate = 0,
                            PALETTE256 * palette  = 0,
                            int createsem = 1);

 // Запрос общих данных классификатора
 int GetRscDescribe(RSCCREATE * rsccreate,PALETTE256 * palette);

 // Установка - возврат типа кодов объектов, используемых в классификаторе
 // type 0 - код числовой, 1- в качестве кода, берется ключ(короткое имя объекта)
 int GetRscObjectCodeType(void);
 int SetRscObjectCodeType(int type);

 // Закрыть таблицу адресов
 void CloseRsc();

 // Сборка и запись ресурсов карты
 int Commit(void);

 // Сборка и запись ресурсов карты
 int Save(int mode);

 // Сформировать копию RSC
 // или восстановить RSC из копии
 int BackCopy(int restore);

 // Создание служебных объектов
 int CreateServObjects();

 // Запрос адреса записи таблицы ресурсов
 TABRSC * GetTabRsc(int incode)
   {
     if (!IsActive()) return 0;
     return(TabRsc + incode);
   }

 // Запросить идентификатор ресурсов района работ
 RSCHEAD * GetRscId() { return &Rsc; }

 // Запрос адреса записи таблицы изображений по семантике по номеру (с 1 )
 TABGRSITEM * GetTabGrsItem(int index)
   {
     if (!IsActive()) return 0;
     return (TabGrsItem + index);
   }

 // Запрос размера таблицы изображений по семантике
 long GetTabGrsCount()
   {
     if (!IsActive()) return 0;
     return TabGrsCount;
   }

 // Определить доступны ли ресурсы карты
 int IsActive();

 // Запрос - можно ли редактировать классификатор ?
 int IsWrite();

 // Запросить имя файла классификатора
 char * NameRSC() { return RscName; }

 // Запросить полное (с путем) имя файла классификатора
 int GetRscName(char * name, int size);

 const char * GetRscName() { return RscPath; }        

 // Запросить идентификатор файла классификатора
 HANDLE GetFileRSC()
   {
      if (!IsActive()) return 0;
      return File_RSC;
   }

  // Установка/возврат флага открытия файла через API
 int ApiOpenFlag(void);
 int ApiOpenFlag(int);

 // Запросить код ошибки выполнения последней операции
 // Если ошибок не было, возвращает ноль
 long int Error();

 // Установка/возврат состояния файла
 int Style(void);
 int Style(int);

 // Установка/возврат модификации палитры            
 int ColorStyle(void);
 int ColorStyle(int);

 // Установка/возврат максимального идентификатора объектов
 int MaxKey(void);
 int SetMaxKey(void);


 // Установка/возврат модификации файла
 int Mode(void);
 int Mode(int);



 // Установка/возврат кода классификатора
 int ClassificatorCode(char * classificator);
 char * ClassificatorCode();

 // Установка/возврат номера таблицы масштабов
 int ScaleTableNumber();
 int ScaleTableNumber(int scaletable);

 // Запрос масштаба по номеру в текущей таблице
 long GetScaleItem(int number);

 // Запрос масштаба по номеру в указанной таблице масштабов(0,1)    
 long  GetTableScaleItem(int tablenumber, int number);

 // Установка/возврат языка классификатора
 int GetClassificatorLanguage();
 int SetClassificatorLanguage(int language = ML_RUSSIAN );

 // Запрос даты создания файла
 char * Date();

 // Установка/возврат  масштаба карты
 long Scale();
 long Scale(long scale);

 // Установка/возврат  типа классификатора
 char * Type();
 char * SetType(char *str);

 // Установка/возврат  имени классификатора
 char * Name();
 char * SetName(char *str);

 // Отметить изменения в Rsc
 int SetModify(void);

 // Запросить - были ли изменения RSC
 int IsModify();

 // Загрузить старую версию классификатора
 // Если загрузка успешная - новый классификатор открыт
 // При ошибке возвращает ноль
 int LoadOldVersion(const char * oldrsc, const char * newname, long scale);
 int CheckAndLoadOldVersion(const char * name, long scale);   

 // Установить соответствие между данными классификатора в
 // памяти и на диске
 // 1  - данные совпадают
 // 0  - ошибка
 // -1 - обновили
 int AdjustData(void);

 // Запросить размер файла классификатора
 // При ошибке возвращает 0
 long int FileSize();

 // Восстановить классификатор с диска
 int Revert(void);

 // Сжатие классификатора - происходит в памяти
 // возвращается 0 при неудаче
 int Press(void);                            

 // Очистить строку от пробелов
 // size - размер строки
 // Убирает начальные и конечные пробелы.
 // При ошибке возвращает 0
 int ClearofBlank(char * name,int size);

 // Запрос порядкового номера элемента по имени (порядковый номер с 0)
 // Type - тип запроса : для слоя по имени - 1,
 //                      для слоя по короткому имени - 2,
 //                      для семантики по имени - 3,
 //                      для семантики по короткому имени - 4,
 //                      для объекта по ключу - 5
 // При отсутствии - 0 , код ошибки IDS_NOTFIND
 int GetElementbyName(char * name,int type);

 // Установить код ошибки выполнения последней операции
 long int Error(int error);

 protected :
 // Открыть доступ к классификатору
 // Построить таблицу адресов
 // При ошибке возвращает ноль
 int OpenRsc();

 /****************************************************************
 *                                                               *
 *             ДОСТУП К ПАЛИТРЕ КЛАССИФИКАТОРА (RSC)             *
 *                                                               *
 ****************************************************************/

public :

 // Запрос идентификатора описания палитры  по порядковому номеру (с 1)
 TABPAL * GetTabPal(int number);

 // Запрос адреса палитры  по ее номеру                              
 COLORREF * GetPalette(int number = 1);

 //  Запрос количества палитр
 int GetPaletteCount();                                              

 // Запрос имени палитры по номеру (с 1)                             
 char * GetPaletteName(int number);

 // Установить имя палитры по номеру (с 1)                          
 // Возвращает номер исправленной палитры
 int SetPaletteName(int number,char * name);

 // Удалить палитру по номеру (c 1)(одна палитра не удаляется)      
 int  DeletePalette(int number);

 // Запрос количества цветов, примененных в классификаторе
 int GetRscColorCount();

 // Установить количество цветов, примененных в классификаторе
 int SetRscColorCount(int number);

 // Запрос значения цвета по индексу в палитре
 COLORREF GetRscColor(int index);

 // Запрос адреса цвета с номером index первой палитры
 COLORREF * GetRscPalette(int index = 0);

 // Установить всю палитру (номер палитры c 1)
 int SetRscPalette(COLORREF * colorref,int number);

 // Установить цвет в палитру
 // Возвращает бывший цвет
 COLORREF SetRscColor(COLORREF color,int index = 0);

 // Восстановить палитру с диска по номеру палитры  (с 1)
 // сбрасывает яркость и контрастность
 // Возвращает адрес палитры
 COLORREF * ResetPalette(int number = 1);       

 // Установить соответствующую палитру (c 1) по умолчанию
 // Возвращает адрес палитры
 COLORREF * SetDefaultPalette(int number = 1);  

 //  Запрос значения умалчиваемого цвета по индексу в палитре
 COLORREF GetDefaultColor(int index);

 // Записать новую палитру
 // palette - цвета палитры,count - количество цветов в палитре
 // name    - название палитры
 // возвращает указатель на созданную палитру
 // 0 - при ошибке
 TABPAL * AppendPalette(COLORREF * palette,int count,char *name );

// Заменить  палитру
// number  - номер заменяемой палитры (если такого нет палитра добавляется)
// palette - цвета палитры,count - количество цветов в палитре
// name    - название палитры
// возвращает указатель на созданную палитру
// 0 - при ошибке
TABPAL * ReplacePalette(int number,COLORREF * palette,int count,char *name);

// Преобразование палитры из RGB в CMYK                       
// number - количество цветов
// rgb - адрес палитры(COLORREF)
// cmyk - адрес, для размещения палитры CMYK (4 байта на цвет)
int CreateCMYK(long int count,char * rgb,char * cmyk);

// Заполнить палитру CMYK                        
// number - количество записываемых цветов
// begin  - область CMYK цветов
// 0 - при ошибке

int SetCMYKPalette(long number,long * begin);

// Запросить палитру CMYK                        
// Возвращает адрес CMYK палитры
// 0 - при ошибке
char * GetCMYKPalette();


 /****************************************************************
 *                                                               *
 *     ДОСТУП К ОПИСАНИЮ ЛОКАЛИЗАЦИЙ ЭЛЕКТРОННОЙ КАРТЫ           *
 *                                                               *
 *    локализации начинаются с 0                                 *
 *                                                               *
 ****************************************************************/

 // Запрос количества локализаций
 int GetLocalCount() {return 6;}

 // Запрос названия локализации по ее номеру (0 - линейный, ...)
 // Названия хранятся на двух языках ...
 const char * GetLocalName(int local,int language = ML_RUSSIAN);

 // Запрос длины имени локализации
 int GetLocalNameSize() {return 16;}

 /****************************************************************
 *                                                               *
 *     ДОСТУП К ОПИСАНИЮ СЕГМЕНТОВ (СЛОЕВ) ЭЛЕКТРОННОЙ КАРТЫ     *
 *                                                               *
 *    внутренние коды сегментов начинаются с 0                   *
 *    при ошибке возврат 0                                       *
 *                                                               *
 ****************************************************************/

public:

 // Запрос идентификатора описания сегмента по внутреннему
 // коду cегмента
 TABSEG * GetTabSeg(int incode);

 // Заполнить структуру описания слоев
 // RSCSEGMENT -  структура входных данных  (см. maptype.h)
 // incode - порядковый номер слоя
 // При ошибке возвращает ноль ( код ошибки не равен 0 )
 // иначе порядковый номер слоя
 int GetSegment( int incode, RSCSEGMENT *segment);

 // Запрос количества сегментов
 int GetSegCount();

 // Запрос имени сегмента по внутреннему коду сегмента
 char * GetSegName(int incode);

 // Запрос внутреннего кода сегмента по имени
 // При отсутствии сегмента возврат - 0 , код ошибки IDS_NOTFIND
 int GetSegmentByName(char * name);

 // Запрос длины имени сегмента
 int GetSegNameSize();

 // Запрос короткого имени сегмента по внутреннему коду сегмента
 const char * GetSegShortName(int number);

 // Запрос порядка вывода сегмента на экран по внутреннему коду сегмента
 int GetSegOrder(int incode);

 // Запрос количества объектов сегмента по внутреннему коду сегмента
 int GetSegmentObjectCount(int incode);

 // Запрос количества не удаленных объектов сегмента по внутреннему коду сегмента
 int GetSegmentObjectRealCount(int incode);            

 // Установка имени сегмента по внутреннему коду сегмента
 int SetSegName(int incode,char * name);

 // Установка короткого имени сегмента по внутреннему коду сегмента
 int SetSegShortName(int incode,char * shortname);

 // Установка порядка вывода сегмента по внутреннему коду сегмента
 int SetSegOrder(int incode,char order);

 // Записать новый сегмент - возвращает порядковый N сегмента с 1
 int AppendSeg(RSCSEG * rseg);
 int AppendSegment( RSCSEGMENT * segment);

 // Удалить сегмент по внутреннему коду  сегмента(служебный слой не удаляется)
 int DeleteSegment(int incode);

 // Перенести объекты из одного слоя в другой
 // Из служебного слоя и в служебный слой - объекты не переносятся
 // Возвращает новый номер слоя, либо 0 - ошибка
 int MoveSegmentObjects(int oldcode,int newcode);

 /****************************************************************
 *                                                               *
 *       ДОСТУП К ОПИСАНИЮ ВИДОВ ОБ'ЕКТОВ ЭЛЕКТРОННОЙ КАРТЫ      *
 *                                                               *
 *   Внутренние коды объектов начинаются с 1.                    *
 *   При ошибке возврат 0 .                                      *
 *   Если для характеристики возможно 0 значение перед запросом  *
 *   проверить IsActive();                                       *
 *                                                               *
 ****************************************************************/

public:
// Запрос идентификатора характеристик объектов по внутреннему коду
// TABPOS * GetTabObj(int incode);

 // Запрос количества объектов
 int GetObjCount();

 // Запрос описания объекта  по внутреннему коду
 // если код = 0 - заполнение по умолчанию
 int GetDescribeObj( int incode,RSCOBJECT * object);

 // Запрос внешнего кода объекта по внутреннему коду
 long GetObjExcode(int incode);

 // Запрос внешнего кода служебного объекта по локализации
 long GetServObjExcode(int local);

 // Запрос расширения объекта по внутреннему коду
 int GetObjExtend(int incode);

 // Запрос флага исправления объекта по внутреннему коду
 //int GetObjFlags(int incode);

 // Запрос функции отображения объекта по внутреннему коду
 // Возвращаемое значение не должно превышать значения
 // функции GetLastFunction()
  int GetObjFunction(int incode);

 // Запрос внутреннего кода объекта по внешнему коду и локализации
 // При ошибке возвращает 0
 int GetObjIncode(long excode,int local);

 // Запрос внутреннего кода объекта по внешнему коду, локализации
 // и расширению
 // При ошибке возвращает 0
 int GetObjIncode(long excode,int local,int extend);

 // Запрос внутреннего кода объекта по внешнему коду, локализации
 // и семантике объекта
 // При ошибке возвращает 0
 int _fastcall GetObjIncode(long excode,int local,TObjectSemn semn);

 // Запрос количества объектов с данной локализацией в данном слое
 int  GetSegmentObjNumber(int segment,int local);

 // Запрос количества объектов с данным внешним кодом и локализацией
 // При ошибке или отсутствии возвращает 0
 int GetObjNumber(long excode,int local);

 // Последовательный запрос внутреннего кода объекта по внешнему
 // коду и внутреннему коду предыдущего объекта (при отсутствии
 // внутреннего кода - поиск с первого объекта
 // При ошибке возвращает 0
 int GetNextObjIncode(long excode,int incode = 0);

 // Запрос внутренного кода служебного объекта по локализации
 int GetServObjIncode(int local);

 // Запрос локализации объекта по внутреннему коду
 int GetObjLocal(int incode);

 // Запрос расширенной локализации объекта по внутреннему коду
 int GetObjExtloc(int incode);

 // Запрос имени объекта по внутреннему коду
 const char * GetObjName(int incode);

 // Запрос ключа объекта по внутреннему коду
 const char * GetObjKey(int incode);

 // Запрос идентификатора объекта по внутреннему коду
 long GetObjIdent(int incode);

 // Запрос внутреннего кода объекта по идентификатору
 long GetObjIdentIncode(int ident);

 // Запрос внутреннего кода объекта по ключу
 long GetObjKeyIncode(const char * key);

 // Запрос длины имени объекта
 int GetObjNameSize();

 // Запрос сегмента объекта по внутреннему коду
 int GetObjSegment(int incode);

 // Запрос верхней границы видимости по внутреннему коду
 int _fastcall GetObjBot(int incode);

 // Запрос нижней границы видимости по внутреннему коду
 int _fastcall GetObjTop(int incode);

 // Запрос масштабируемости объекта по внутреннему коду
 int _fastcall GetObjScale(int incode);

 // Запрос сжимаемости объекта по внутреннему коду                
 int _fastcall GetObjPress(int incode);

 // Запрос направления цифрования объекта по внутреннему коду
 int GetObjDirect(int incode);

 // Запрос номера последней функции визуализации
 int GetLastFunction();

 // Запрос внутреннего кода рамки листа
 // Остальные структурные ошибки - возврат 0
 int GetFrameCode();

 // Запрос внешнего кода рамки листа
 long GetFrameCodeEx();

 // Проверка существования и создание при необходимости
 // рамки листа возврат 1
 // Остальные структурные ошибки - возврат 0
 int CheckFrameCode();

 // Записать внешний код объекта по внутреннему коду
 // Проверка на наличие серии не делается
 long SetObjExcode(int incode,long excode);

 // Переопределить внешний код объекта
 // Замещается также внешний код умолчаний
 // Проверка на наличие серии не делается
 long UpdateObjExcode(int incode,long newexcode);

 // Переопределить локализацию объекта
 // Замещается также внешний код умолчаний
 // Проверка на наличие серии не делается
 long UpdateObjLocal(int incode,int newlocal);

 // Записать флаг исправления объекта по внутреннему коду
 //int SetObjFlags(int incode,int flag);

 // Записать сегмент объекта по внутреннему коду
 // (сегмент может быть равен 0)
 int SetObjSegment(int incode,int seg);

 // Записать функцию отображения объекта по внутреннему коду
 // (Функция отображения может быть равна 0)
// int SetObjFunction(int incode,int number);

 // Записать локализацию объекта по внутреннему коду
 // (локализация объекта может быть равна 0)
 // Если сменили локализацию существующего объекта,
 // вид объекта не исправляем.
 // Проверка на наличие серии не делается
 int SetObjLocal(int incode,int loc);

 // Записать расширенную локализацию объекта по внутреннему коду
 // (расширенная локализация объекта принимает значения 0 или 1)
 // Указывает на "векторность объекта" (1- изображение по 2 точкам)
 int SetObjExtloc(int incode,int exl);

 // Записать масштабируемость объекта по внутреннему коду(0/1)
 // 1 - масштабируемость означает :
 // для линейных - увеличение ширины линии,
 // для векторных
 // для шрифтов    - величина базы объекта соответствует
 //                  расстоянию между 2 первыми точками метрики
 // для точечных   - знак не пропадает при увеличении масштаба карты

 int SetObjScale(int incode,int scale);

 // Записать сжимаемость объекта по внутреннему коду(0/1)
 // 1 - не сжимать
 int SetObjPress(int incode,int press);

 // Записать имя объекта по внутреннему коду
 char * SetObjName(int incode,char * name);

 // Записать ключ объекта по внутреннему коду           
 char * SetObjKey(int incode,char * key);

 // Записать верхнюю границу видимости объекта по внутреннему коду
 int SetObjTop(int incode,int top);

 // Записать нижнюю границу видимости объекта по внутреннему коду
 int SetObjBot(int incode,int bot);

 // Записать направление цифрования объекта по внутреннему коду
 int SetObjDirect(int incode,int direct);

 // Создать новый объект - возвращает внутренний код объекта
 // если это шаблон - на входе дополнительно указатель на таблицу
 // для шаблона,для проверки единственности созданного объекта
 // по коду + локализация снеск = 1
 int AppendObject(RSCOBJ * robj,int check = 1);

 // Создать новый объект - возвращает внутренний код объекта
 // Внешний вид созданного объекта соответствует служебному объекту (для данной
 // локализации).
 // Если указанный слой для создания объекта  не существует - объект
 // создается в служебном слое
 // Если такой объект (внешний код и локализация) уже существует -
 // объект не создается - возврат 0.
 // При ошибке - возвращает 0, иначе внутренний код созданного объекта
  int AppendObjectDefaultView(RSCOBJECT * robj);

 // Удалить объект - возвращает внутренний код удаленного объекта
 // если объект входит в серию - удаление не делается
 int DeleteObject(int incode);

 // Удалить объект из серии - возвращает внутренний код удаленного объекта
 // если объект не входит в серию - удаление не делается

 int DeleteSeriaObject(int incode);
 // Скопировать объект на новое место
 // (c внешним кодом FIRSTSERVEXCODE)
 // удаленный объект не копируется
 // возвращает внутренний код нового объекта
 // Для того,чтобы данный объект остался при сохранении класси-
 // фикатора, пользователь должен переопределить внешний код объекта
 int CopyObject(int oldincode);

 // Скопировать объект на указанное по внутреннему коду место
 // (внешний код обнуляется)
 // если старый объект входит в серию - копирование не делается
 // возвращает внутренний код нового объекта
 int CopyObject(int newincode,int oldincode);

 // Проверяет для объекта единственность сочетания кода + локализа-
 // ции. При совпадении возвращает 0
 int CheckObjectCode(unsigned long code,int local);

 // Копирование объекта из другого классификатора -
 // возвращает внутренний код нового объекта
 int CopyObject(TMapRsc * source,int oldincode,int segment,TMap * map);

 // Обновить описание объекта  по внутреннему коду
 // При наличии серии внешний код и локализация и слой - не меняются
 // Если внешний вид не соответствует новому описанию -
 // Заменить внешний вид на умалчиваемый
 // Возвращает внутренний код , либо 0
 int UpdateObject( int incode,RSCOBJECT * object);

 // Запpосить количество связанных подписей объекта        
 int _fastcall GetObjectRelateCount(int incode);

 // Запpосить описание связанной подписи по внутреннему коду объекта и  
 // по порядковому номеру связанной подписи (с 1)
 // возвращает идентификатор подписи
 // при ошибке возвращает 0
 int GetObjectRelateOrder(int incode,int order,RSCRELATION * relate);

 // Запpосить описание связанной подписи объекта           
 // по данной семантике
 // при отсутствии таковой возвращает 0
 int GetObjectRelate(int incode,int semanticcode,RSCRELATION * relate);

 // Обновить описание либо добавить описание связанной подписи  
 // Возвращает идентификатор подписи  , либо 0
 int UpdateObjectRelate(int incode,int semanticcode,int ident,char * prefix,
                        int decimal);

 // Удалить связанные подписи объекта по идентификатору подписи        
 // Возвращает количество удаленных связанных подписей
 int DeleteObjectRelateIdent(int incode,int ident);

 // Удалить связанную подпись по указанной семантике                   
 int DeleteObjectRelate(int incode,int semanticcode);

 // Удалить все связанные подписи ссылающиеся на данный объект         
 // ident - идентификатор объекта
 // Возвращает количество удаленных связанных подписей
 int DeleteObjectRelationText(int ident);

 // Найти следующий объект после указанного имеющий связанную подпись  
 // ссылающуюся на объект с данным идентификатором
 // Возвращает возвращает внутренний код объекта.
 // если таких больше нет 0
 int CheckRelation(int ident,int order);

 // Установить верхнюю границу видимости для подписей по указанному  
 // масштабу (подпись видна (включая) следуюший масштаб в таблице масштабов
 // Возвращает количество исправленных объектов
 int SetObjectView(unsigned long scale);

protected:

 // Установить идентификатор описания объекта по внутреннему коду
 //TABPOS * SetTabObj(int incode,TABPOS * aobj);


 /****************************************************************
 *                                                               *
 *       ДОСТУП К ОПИСАНИЮ СЕМАНТИК ЭЛЕКТРОННОЙ КАРТЫ            *
 *                                                               *
 ****************************************************************/

public:

  enum
   {
     HEADIDENT      =::HEADIDENT, // идентификатор начала умолчаний
                                  // или классификатора
     MINVALUESEMSER = -32760,  // минимальное значение семантики
     MAXVALUESEMSER = 32760,   // максимальное значение семантики
                               // при наличии серии или классиф.
   };

 // Запрос количества значений классификатора по  коду
 // семантической характеристики
 int GetClassificatorCount(int incode);

 // Запрос числового значения классификатора по  коду
 // семантической характеристики и порядковому номеру (с 1)
 int GetClassificatorValue(int incode,int number);

 // Запрос "имени" значения классификатора по  коду
 // семантической характеристики и порядковому номеру (с 1)
 const char * GetClassificatorName(int incode,int number);

 // Запрос идентификатора описания классификатора по  коду
 // семантической характеристики и порядковому номеру (с 1)

 TABCLS * GetTabCls(int incode,int number);

 // Запрос количества семантик
 int GetSemCount();

 //  Заполнить расширенную структуру описания семантической характе-
 //  ристики по внешнему коду семантики и внутреннему коду объекта
 //  semtype - адрес структуры, в которую будет помещено
 //  описание характеристики,
 //  code - код семантики,
 //  objincode - внутренний код объекта.
 //  При ошибке возвращает ноль
 int SemanticDescribeEx(RSCSEMANTICEX *semtypeex,             
                         int code, int objincode);

 // Запрос смещения на таблицу семантики в памяти
 TABSEM * GetOffSem();
                                                              // tdc
 // Запрос имени семантики по коду
 // семантической характеристики
 const char * GetSemName(int code);

 // Запрос имени семантики по порядковому номеру
 // семантической характеристики ( с 1 )
 const char * GetSemOrderName(int number);

 // Запрос внешнего кода семантики по порядковому номеру
 // семантической характеристики (с 1 )
 int GetSemOrderExcode(int number);

 // Запрос длины имени семантики
 int GetSemNameSize();

 // Запрос повторяемости значения семантики по коду
 int GetSemReply(int code);

 // Запрос признака служебной семантики по коду
 int GetSemService(int code);

 // Запрос типа значения семантики по коду
 int GetSemType(int code);

 // Запрос "имени" значения по коду семантики и
 // коду значения
 const char * GetSemValueName(int code,int value);

 // Запрос короткого имени семантики по внешнему коду
 const char * GetSemShortName(int excode);

 // Запрос общей длины поля значения семантики
 int GetSemValuePoleSize(int code);

 // Запрос точности значения семантики
 int GetSemValuePoleDecimal(int code);

 // Запрос максимальной длины "имени" значения
 int GetSemValueSize();

 // Запрос наименования единицы измерения семантики
 // Если нет единицы измерения - возвращает указатель
 // на пустую строку
 // При ошибке возвращает пустую строку (см. код ошибки)
 const char * GetSemUnit(int code);

 // Запрос максимальной длины наименования единицы измерения
 int GetSemUnitSize();

 // Проверяет для семантики единственность кода
 // При совпадении возвращает 0
 int CheckSemanticCode(int code);

 // Установка короткого имени сегмантики по внешнему коду семантики
 int SetSemShortName(int excode,char * shortname);

 // Установка размера и точности значения семантики
 int SetSemDecimal(int excode,int size,int decimal);

 // Записать новую семантику - возвращает
 // указатель на созданную семантику
 TABSEM *  AppendSemantic(RSCSEM * rsem);

 // Записать новую семантику - возвращает  код созданной семантики
 unsigned long AppendSemantic(RSCSEMANTICEX * rsem);

 // Создадим стандартную семантику
 // При ошибке возвращает 0
 unsigned long AppendStandardSemantic();

 // Создадим системную семантику
 // При ошибке возвращает 0
 unsigned long AppendSystemSemantic();

 // Обновить семантику
 // rsem - адрес структуры, c описанием характеристики,
 // code - код семантики которую обновляем,
 // Возвращает код исправленной семантики
 // Если классификатор исправлялся - classupdate = 1  при этом
 // очищено место под запись исправленного классификатора
 // При ошибке возвращает 0
 // Создается соответствующий код ошибки
 int UpdateSemantic(int code,RSCSEMANTICEX * rsem,int classupdate=0);

 // Удалить семантику
 // Семантика влияющая на изображение не удаляется
 // Для удаления такой семантики первоначально измените либо удалите серии,
 // использующие данную семантику
 int DeleteSemantic(int code);

 // Проверяет для классификатора единственность числовых значений
 // При совпадении возвращает 0
 int CheckClassificatorCode(int semanticcode,int value);

 // Записать новую "строчку" классификатора
 // (числовое значение и символьное) возвращает
 // указатель на исправленную семантику
 TABSEM *  AppendCls( int codesemantic,short int value,char * name);

 // Запрос идентификатора описания семантики по коду
 // семантической характеристики
 TABSEM * GetTabSem(int incode);

 // Запрос идентификатора описания семантики по коду
 // семантической характеристики (устаревшая)
 TABSEM * GetTabSemEx(int code);

 // Запрос использования семантики в объектах классификатора
 int GetSemInfo(int code,APPLYSEMANTIC * applysemantic);

 // Копирование cемантики из другого классификатора -
 // возвращает 1 - хорошее завершение
 int CopySemantic(TMapRsc *source,int oldcode);

 // Заменить символьное значение классификатора по номеру с 1
 // возвращает номер или 0
 int UpdateClassificatorName(int semanticcode,int index,char * name);

 /****************************************************************
 *                                                               *
 *  ДОСТУП К ОПИСАНИЮ И РЕДАКТИРОВАНИЮ ВОЗМОЖНЫХ СЕМАНТИК        *
 *                                                               *
 ****************************************************************/

public:

 // Запрос идентификатора описания возможных семантик по внутреннему
 // коду объекта
 TABPOS * GetTabPos(int incode);

 // Запрос количества возможных семантик по внутреннему коду объекта
 int GetObjOnlyPosSemCount(int incode);

 // Запрос количества возможных семантик по внутреннему коду объекта
 // c учетом возможных для слоя и общих семантик                     
 int GetObjPosSemCount(int incode);

 // Запрос количества обязательных семантик по внутреннему коду объекта
 int GetObjMustSemCount(int incode);

 // Запрос кода возможной семантики по внутреннему коду объекта и
 // порядковому номеру в возможных семантиках (c 1)
 int GetObjOnlyPosSem(int incode,int number);

 // Запрос кода возможной семантики по внутреннему коду объекта и
 // порядковому номеру в возможных семантиках (c 1)
 // c учетом возможных для слоя и общих семантик                     
 int GetObjPosSem(int incode,int number);

 // Запрос кода семантики по внутреннему коду объекта и
 // порядковому номеру(c 1) с учетом сортировки пользователя
 // возможные для слоя и общие семантики идут в конце         
 int GetObjOrderSem(int incode,int number);

 // Запрос порядка вывода кода семантики по внутреннему коду объекта
 // с учетом сортировки пользователя
 // 0 - семантика не принадлежит объекту либо общая           
 int GetObjSemOrderNumber(int incode,int semcode);

 // Запрос семантика объекта сортирована?
 // 0 - нет, 1- да                                           
 int IsObjSemOrdered(int incode);

 // Записать порядок семантик для объекта в соответствии с входным списком
 // count - размер массива семантик объекта
 // semantics - указатель на сортированный список семантик объекта.
 // Семантики которые не наначены объекту (в том числе и общие) - пропускаются,
 // Если какие - то семантики пропущены пишутся в конец списка
 // при нормальном завершении возвращает количество семантик объекта
 int SetObjSemanticOrder(int objincode,int count,long * semantics);

 // Пересортировать массив семантик для объекта в соответствии с
 // порядковыми номерами
 // count - размер массива семантик объекта для сортировки
 // semantics - указатель на список номеров требуемых семантик объекта.
 // order     - указатель на выходной массив заполнен отсортированными
 // порядковыми номерами входных семантик(с 1 )
 // при нормальном завершении возвращает 1
 int SortObjSemantic(int objincode,int count,long * semantics,long * orders);

 // Запрос кода обязательной семантики по внутреннему коду объекта и
 // порядковому номеру в возможных семантиках (c 1)
 int GetObjMustSem(int incode,int number);

 // Запрос использования семантики для объекта по внутреннему коду
 // и коду семантики
 // c учетом возможных для слоя и общих семантик                    
 int GetObjCanSem(int incode,int codesem);

 // Запрос использования семантики для объекта по внутреннему коду
 // и коду семантики
 int GetOnlyObjCanSem(int incode,int codesem);

 // Запрос количества пороговых семантик по внутреннему коду объекта
 int GetObjLimSemCount(int incode);

 // Запрос кода пороговой семантики по внутреннему коду объекта и
 // порядковому номеру в пороговых семантиках (c 1)
 int GetObjLimSem(int incode,int number);

 // Добавить семантику объекту
 // seria = 1 ,eсли объект из серии
 // tуpe - тип семантики (из maptype.h SEMANTIC_FOR_OBJECT)
 // возвращает ее последовательный номер
 // в семантиках данного типа (начиная с 1)
 int AppendObjectSemantic(int objincode,int semincode,int type,int seria = 0);

 // Удалить возможную либо обязательную семантику у объекта
 // seria = 1 ,eсли объект из серии
 // при нормальном завершении возвращает внутренний код объекта
 int DeletePosSemantic(int objincode,int semincode,int seria = 0);

 // Назначить семантику - дополнительной в семантиках на объект.
 // seria = 1 ,eсли объект из серии
 // Возвращает последовательный номер (с 1) в возможных семантиках
 // если такой не было - возвращает 0
 int SetTypePosSemantic(int objincode,int semincode,int seria = 0);

 // Назначить семантику - обязательной в семантиках на объект.
 // seria = 1 ,eсли объект из серии
 // Возвращает последовательный номер (с 1) в обязательных
 // семантиках
 // если такой не было - возвращает 0
 int SetTypeMustSemantic(int objincode,int semincode,int seria = 0);

 // Запросить количество семантик для слоя по порядковому номеру
 // слоя с 0
 long GetSegSemCount(int number);

 // Запросить код семантики по порядковому номеру слоя и номеру
 // семантики в списке (с 1)
 long GetSegSemCode(int numberseg,int order);

 // Добавить код семантики в список слоя с порядковым номером
 // numberseg ( c 0)
 long AppendSegSemCode(int numberseg,long code);

 // Удалить код семантики из списка слоя с порядковым номером
 // numberseg ( c 0)
 long DeleteSegSemCode(int numberseg,long code);

 // Создать список семантик для слоя
 // index - порядковый N слоя (c 0)
 // type - тип семантик для сбора 0 - все
 //                               1 - только обязательные
 // возвращает указатель на исправленный слой
 TABSEG * BuildSegmentSemantic(int index,int type);

 // Создать описание возможных семантик по внутреннему коду объекта
 // seria = 1 ,eсли объект из серии
 // если такое есть - возвращается указатель на существующую таблицу
 TABPOS * AppendPos(int incode,int seria = 0);

protected:

 // Установить идентификатор описания возможных семантик по внутреннему
 // коду семантики
// TABPOS * SetTabPos(int incode,TABPOS * apos);

 // Создать описание возможных семантик по внутреннему коду объекта
 // seria = 1 ,eсли объект из серии
 // если такое есть - возвращается указатель на существующую таблицу

 int DeletePos(int incode,int seria = 0);

 // Добавить возможную семантику объекту
 // seria = 1 ,eсли объект из серии
 // возвращает ее последовательный номер
 // в возможных семантиках (начиная с 1)
 int AppendPosSemantic(int objincode,int semincode,int seria = 0);

 /****************************************************************
 *                                                               *
 *  ДОСТУП К ОПИСАНИЮ И РЕДАКТИРОВАНИЮ ТАБЛИЦЫ УМОЛЧАНИЙ         *
 *                                                               *
 ****************************************************************/

public:

 // Запрос идентификатора таблицы допустимых значений семантики
 // по внутреннему коду объекта и внутреннему коду семантики,
 // Если не нашли умолчаний на данный объект возвращаются общие
 // умолчания для данной семантики
 // если не нашли возвращает 0
 TABDEF * GetTabDef(int objincode,int semincode);

 // проверить наличие таблицы допустимых значений семантики
 // по внутреннему коду объекта и коду семантики,
 // если не нашли возвращает 0
 TABDEF * CheckTabDef(int incodeobject,int semcode);

 // Запрос минимума,умолчания и максимума значения семантики
 // по внутреннему коду объекта и коду семантики
 // если не нашли возвращаем 0
 int GetDefValue(int incodeobject,int semcode,RSCDEF * def);

 // Запрос минимума допустимого значения семантики
 // по внутреннему коду объекта и внутреннему коду семантики
 // предварительно запрсить наличие такого умолчания
 // CheckTabDef(int objincode,int semincode);
 // если не нашли возвращаем 0
 // Код ошибки  IDS_NOTFIND
 float GetDefMin(int objincode,int semincode);

 // Запрос значения семантики по умолчанию
 // по внутреннему коду объекта и внутреннему коду семантики
 // предварительно запрсить наличие такого умолчания
 // CheckTabDef(int objincode,int semincode);
 // если не нашли возвращаем 0
 // Код ошибки  IDS_NOTFIND
 float GetDefDef(int objincode,int semincode);

 // Запрос максимума допустимого значения семантики
 // по внутреннему коду объекта и внутреннему коду семантики
 // предварительно запрсить наличие такого умолчания
 // CheckTabDef(int objincode,int semincode);
 // Код ошибки  IDS_NOTFIND
 // если не нашли возвращаем 0
 float GetDefMax(int objincode,int semincode);

 // Запрос значения семантики по умолчанию
 // по внутреннему коду объекта и внутреннему коду семантики
 // Значение преобразовано в символьную строку
 // Если на объект есть пороги - возвращает умалчиваемое значе-
 // ние семантики,если оно соответствует внутреннему коду объекта
 // иначе - первое соответствующее внутреннему коду объекта
 // возвращает 1,при ошибке 0
 int GetDefValueSemantic(int objincode,int semanticcode,
                         char * strdef,int lenstr);

//protected:  

 // Записать новые умолчания на семантику или на объект
 // возвращает указатель на исправленную семантику
 TABSEM * AppendDef(int incodeobject,int semanticcode,
                   float objmin,float objdef,float objmax);

 // Удалить умолчания на семантику - общие (objincode = 0)
 // или на объект
 // возвращает указатель на исправленную семантику (ошибка - 0 )
 TABSEM * DeleteDef(int objincode,int semincode);

 // Удалить умолчания на объект по любым семантикам
 // возвращает код объекта (ошибка - 0 )
 int DeleteDefObject(int incode);

 // Заменить умолчания на семантику - общие (objincode = 0)
 // либо на объект
 // Если требуемого умолчания не нашли - добавим новое
 // возвращает указатель на исправленную семантику (ошибка - 0 )
 TABSEM * UpdateDef(int incodeobject,int semanticcode,
                   float objmin,float objdef,float objmax);


 /****************************************************************
 *                                                               *
 *     ДОСТУП К ОПИСАНИЮ И РЕДАКТИРОВАНИЮ ТАБЛИЦЫ ПОРОГОВ        *
 *                                                               *
 ****************************************************************/

public:

 // Запрос идентификатора описания порогов по внутреннему коду объекта
 TABLIM * GetTabLim(int incode);

 // Для создания новой серии по существующему объекту       23.12 n.
 TABLIM * InitSeria(long excode,int local);

 // Обновить объект входящий в серию по внутреннему коду и общей информации
 // серии - поставить назначенное расширение (контроля за однозначностью нет),
 // не проверяет единственность сочетания кода и локализации   23.11 n.
                                                      
 int UpdateSeriaObject(int incode,int extend,TABLIM * limit,TABPOS * possemantic);
 // Обновить внешний код серии                           23/11/ n.
 int UpdateCodeSeria(TABLIM * limit,long excode);
  // Обновить локадизацию серии                         
 int UpdateLocalSeria(TABLIM * limit,char local);

 // Обновить ограничители семантики серии               24/11/ n.
 // limit    -  идентификатор серии,
 // number   -  порядковый номер семантики в серии (1 или 2)
 // code     -  код семантики,
 // count    -  количество ограничителей (больше 1)
 // countdef -  номер умалчиваемого ограничителя с 1,
 // gate     -  адрес порогов
 // при обновлении  если изменилось число ограничителей
 // обнуляется таблица расширений (длина правильная - значения 0)
 // возвращает  идентификатор новой или старой таблицы порогов
 // при ошибке 0
 TABLIM * UpdateGateSeria(TABLIM * limit,int number,int code,
                             int count,int countdef,double * gate );

 // Удалить порог серии                                          
 // Если такого порога не было возвращает  идентификатор старой
 // таблицы порогов
 // иначе возвращает  идентификатор новой таблицы порогов
 // обнуляется таблица расширений (длина правильная - значения 0)
 // при ошибке 0
 TABLIM * DeleteLimit(TABLIM * alim,int number);


 // Обновить расширения семантики серии               24/11/ n.
 // limit    -  идентификатор серии,
 // count    -  количество расширений(больше 1)
 // count должен соответствовать расчетному по идентификатору серии
 // extend   -  адрес расширений
 // возвращает  идентификатор таблицы порогов
 // при ошибке 0
 TABLIM * UpdateExtendSeria(TABLIM * limit,int count,char * extend);

 // Установить идентификатор описания порогов по внутреннему коду
// TABLIM * SetTabLim(int incode,TABLIM * alim);

 // Удалить серию - удалить таблицу порогов и все объекты
 // входящие в серию,обнулить ссылки на возможную семантику,
 // убрать умолчания
 int DeleteSeria(long excode,int local);

 // Обновить семантику объектов серии по исправленному объекту
 // incode - внутренний код объекта c новой семантикой
 // при наличии изменений влияющих на саму серию будет восстановлена
 // семантика объекта с заданным incode.
 // Использовать при изменении только не "видовых" семантик
 int UpdateSeriaSemantic(int incode);              

 // Созвание копии таблицы порогов без привязки к конкретным объектам
 // Установить идентификатор описания порогов по внутреннему коду
 // ident - идентификатор описания порогов - источник
 TABLIM * CopyTabLim(TABLIM * ident);                    

 // Запрос количества ограничителей по данной семантике
 // code     -  код семантики
 int GetGateCount(long excode,int local,int code );  

 // Созвание копии существующей серии объектов       
 // incode - внутренний код одного из объектов серии - источника
 // Возвращает внутренний код первого объекта серии,
 // при ошибке 0
 long CopySeria(long incode);


 /****************************************************************
 *                                                               *
 *       ДОСТУП К ОПИСАНИЮ ПАРАМЕТРОВ ВИЗУАЛИЗАЦИИ ОБ'ЕКТОВ      *
 *                                                               *
 ****************************************************************/

public:

 // Запрос адреса записи таблицы параметров по внутреннему коду объекта
 VIEPAR * GetTabPar(int incode);

 // Запрос адреса начала параметров визуализации по внутреннему коду объекта
 char * GetPar(int incode);

 // Запрос длины параметров визуализации по внутреннему коду объекта
 long GetParLength(int incode);

 // Установить цвет для объекта, возвращаем текущий цвет
 // Заменяет "основной" цвет отображения объекта на указанный
 int SetObjColorIndex(int incode,int color);
 int SetObjColor(int incode,COLORREF color);

 // Установить адрес записи таблицы параметров по внутреннему коду
 // если возврат 0 - ошибка
 VIEPAR * SetTabPar(int incode,VIEPAR * apar);

 // Установить адрес записи таблицы параметров по внутреннему коду,
 // номеру функции,длине и параметрам
 // если возврат 0 - ошибка
 VIEPAR * SetTabPar(int incode,int length,int number,char * param);

 // Создать внешний вид стандартного объекта по локализации
 int CreateDefaultView(int incode);

 // Размер и свойства отображения объекта
 //  (Строка string длиной length задается для
 //   определения горизонтального размера подписи)
 // при ошибке возврат 0
 int GetImageSize(int incode,IMAGESIZE * imagesize,
                  int length = 0,const char * string = "");

 // Найти "основной" цвет изображения объекта  по внутреннему коду 
 // и виду отображения  0 - экранный, 1 - принтерный
 // При отсутствии цвета возвращает 0xFF000000
 // При ошибке возвращает 0
 COLORREF GetObjectBaseColor(int incode,int viewtype);

 // Найти "основной" цвет изображения примитива по номеру функции и параметрам 
 COLORREF GetBasePrimColor(int number, char * param);


 // Рамка по размеру объекта по метрике
 // number - номер функции отображения
 // param  - параметры отображения
 // angle  - угол поворота объекта или ноль
 // При ошибке возврат 0
 // все размеры в микронах
 int GetImageFrame(int number, const char * param,
                   double angle, IMAGEFRAME * imageframe);

 // Поворот точки на угол a относительно точки origin
 int TurnPoint(DOUBLEPOINT * origin,DOUBLEPOINT * point,
               double sina,double cosa);

 // Проверка соответствия локализации и примитива из отображения объекта
 // Если объект отображается как IMG_DRAW , необходимо проверить все примитивы
 // поочередно.
 // при ошибке возврат 0
 int GetImageSuitable(int local,int number);

 // Запрос таблицы отображения шаблонов
 // На входе внутренний код
 // TABLETEMPLATE (определено в Mapgdi.h)
 // при ошибке возврат 0
 int GetTemplateTable(int incode,TABLETEMPLATE * table);

 // Запрос признака применения семантики для отображения объекта
 int GetObjExtsem(int incode);

 // Установка признака применения семантики для отображения объекта
 int SetObjExtsem(int incode, int flag );

 /****************************************************************
 *                                                               *
 *       ДОСТУП К ОПИСАНИЮ ПАРАМЕТРОВ ПЕЧАТИ ОБ'ЕКТОВ            *
 *                                                               *
 ****************************************************************/

 public:

 // Запрос адреса записи таблицы параметров печати
 // по внутреннему коду объекта
 VIEPAR * GetTabPrn(int incode);

 // Запрос адреса начала параметров печати по внутреннему коду объекта
 char  * GetPrn(int incode);

 // Запрос длины параметров печати по внутреннему коду объекта
  long GetPrnLength(int incode);

 // Установить адрес записи таблицы параметров по внутреннему коду
 // если возврат 0 - ошибка
 VIEPAR * SetTabPrn(int incode,VIEPAR * apar);

 // Установить адрес записи таблицы параметров по внутреннему коду,    
 // номеру функции,длине и параметрам
 // если возврат 0 - ошибка
 VIEPAR * SetTabPrn(int incode,int length,int number,char * param);

 // Сбросить принтерные параметры объекта  по внутреннему коду
 void DeleteTabPrn(int incode);

 /****************************************************************
 *                                                               *
 *       ДОСТУП К ОПИСАНИЮ ПАРАМЕТРОВ ТАБЛИЦЫ БИБЛИОТЕК          *  // 29//11/00
 *                                                               *
 ****************************************************************/

 public:
 // Запрос количества библиотек                  
 // 0 - при ошибке
 int GetImlCount();

 // Запрос условного названия библиотеки по порядковому номеру (c 1)
 // ' ' - при ошибке
 char * GetImlName(int number);

 // Запись условного названия библиотеки по порядковому номеру (c 1)
 // ' ' - при ошибке
 char * SetImlName(int number,char * name);


 // Запрос имени библиотеки по порядковому номеру (c 1)
 // ' ' - при ошибке
 char * GetImlNameDLL(int number);

// Запрос индекса библиотеки(с 1) по порядковому номеру    
// 0 - при ошибке
 int GetImlIndex(int number);

 // Запрос порядкового номера библиотеки(с 1) по коду
 // 0 - при ошибке
 int GetImlOrder(int code);

 // Запрос кода по порядковому номеру библиотеки(c 1)         
 // 0 - при ошибке
 int GetImlCode(int number);

 // Записать новую библиотеку
 // name    - условное название библиотеки
 // dllname - название DLL
 // возвращает указатель на созданную библиотеку
 // 0 - при ошибке
 TABIML * AppendLibrary(char * dllname,char * name);

 // Записать новую библиотеку
 // name    - условное название библиотеки
 // dllname - название DLL
 // возвращает код созданной библиотеки
 // 0 - при ошибке
 long int CodeAppendLibrary(char * dllname,char * name);    

 // Дополним параметры пользовательских объектов(IMG_LIBRARY)    
 // 0 - при ошибке
 void  SetUserObjectRefer();

 // Сбросим индексы пользовательских объектов(IMG_LIBRARY)
 void  BreakUserObjectRefer();

#ifndef HIDEIML                 
 // Запросить описание функций,
 // поддерживаемых библиотекой по индексу
 const IMLLIST * GetImageList(int index);
#endif

 // Удалить библиотеку по коду           
 int  DeleteLibrary(int code);

 /****************************************************************
 *                                                               *
 *       ДОСТУП К ОПИСАНИЮ ПАРАМЕТРОВ ТАБЛИЦЫ ШРИФТОВ            *  
 *                                                               *
 ****************************************************************/

 public:

 // Запрос количества шрифтов
 // 0 - при ошибке
  int GetFontCount();

 // Запрос условного имени шрифта по порядковому номеру
 // 0 - при ошибке
  char * GetFontName(int number);

 // Запрос кода шрифта по порядковому номеру
 // 0 - при ошибке
  int GetFontcode(int number);

 // Запрос шрифта по порядковому номеру
 // Возвращает код шрифта
 // 0 - при ошибке
 int GetFont(int number,RSCFONT * font);

 // Записать новый шрифт - возвращает
 // код шрифта
 // 0 - при ошибке
 int AppendFont(RSCFONT * font);

 // Заменить шрифт - возвращает код шрифта
 // index - порядковый номер шрифта (с 1)
 // 0 - при ошибке
 int ReplaceFont(int index,RSCFONT * font);          

 // Заполнение таблицы шрифтов
 // 0 - при ошибке
 int FillFontTable();

 // Освободить таблицу шрифтов
 // 0 - при ошибке
 int FreeFontTable();

 // Дополним параметры шрифтов ( установить ссылку на таблицу шрифтов)
 // при дополнении key = 0,newkey = 0.
 // при удалении шрифта с кодом key - заменяем код шрифта  на  шрифт
 // c кодом newkey, если  newkey = 0, заменяем на 1 шрифт.
 // 0 - при ошибке
 void  SetTextRefer(int key, int newkey);                       

 // Дополним параметры шрифта
 // Возвращает порядковый номер шрифта в таблице
 // 0 - при ошибке
 int SetTextOrder(int key);

 // Запрос / Запись символа для уточнения высоты шрифта по порядковому номеру
 // 0 - при ошибке
 unsigned char GetFontFixedChar(int number);
 int SetFontFixedChar(int number,unsigned char fixedchar);

 // Удалить шрифт по ключу , если нужно переназначить шрифт во внешнем      
 // виде объектов , newkey - ключ другого шрифта. Если newkey = 0,
 // будет назначен шрифт по умолчанию.
 int  DeleteFont(int key,int newkey);

 // Запрос необходимости семантики для отображения пользовательского объекта
 long GetUserObjectSemanticFlag(int number, int function);                   


 /****************************************************************
 *                                                               *
 *       РЕДАКТИРОВАНИЕ ТАБЛИЦЫ БИБЛИОТЕК 3D ПАРАМЕТРОВ          *  
 *                                                               *
 ****************************************************************/
#ifndef HIDERSC3D                                                    
 // Добавить существующую библиотеку трехмерных параметров
 // name    - условное название библиотеки
 // dllname - имя файла .p3d
 // возвращает указатель на cозданную библиотеку
 // 0 - при ошибке
 TABL3D * Append3DLibrary(char * dllname,char * name);

 // Записать новую библиотеку трехмерных параметров
 // name    - условное название библиотеки
 // dllname - имя файла .p3d
 // возвращает указатель на cозданную библиотеку
 // 0 - при ошибке
 TABL3D * New3DLibrary(char * dllname, char * name);

 // Запрос количества библиотек трехмерных параметров
 // 0 - при ошибке
 int Get3DLibraryCount();

 // Запрос порядкового номера библиотеки трехмерных параметров (с 1)
 // по коду
 // 0 - при ошибке
 int Get3DLibraryOrder(int code);

 // Запрос кода по порядковому номеру библиотеки 3D параметров (c 1)
 // 0 - при ошибке
 int Get3DLibraryCode(int number);

 // Запрос кода по имени библиотеки 3D параметров
 // 0 - при ошибке
 int Get3DLibraryCodeByName(const char * dllname);

 // Запрос библиотеки трехмерных параметров по коду
 // 0 - при ошибке
 TABL3D * Get3DLibrary(int code);

 // Удалить библиотеку трехмерных параметров по коду
 int  Delete3DLibrary(int code);

 // Запрос имени библиотеки трехмерных параметров по коду
 // 0 - при ошибке
 char * Get3DLibraryName(int code);

 // Запрос имени файла библиотеки трехмерных параметров по коду
 // 0 - при ошибке
 char *  Get3DLibraryFileName(int code);

 // Запрос смещения библиотеки трехмерных параметров по коду
 // 0 - при ошибке
 long Get3DLibraryOffset(int code);


 /****************************************************************
 *                                                               *
 *       РЕДАКТИРОВАНИЕ 3D ГРАФИКИ                               *  
 *                                                               *
 ****************************************************************/

 // Инициализировать 3D графику
 // 0 - при ошибке
 int Init3D();

 // Запрос таблицы 3D параметров объекта по уровню (0,1,2 - где 0 - ближний)
 // и порядковому номеру (индексу ) объекта с 1
 // При отсутствии нужного - выдаются параметры с меньшим уровнем
 // при ошибке или отсутствии 0
 TABP3D * Get3DObject(long incode,long level);

 // Запрос существования 3D параметров объекта по уровню (0,1,2 - где 0 - ближний)
 // и порядковому номеру (индексу ) объекта с 1
 // при ошибке или отсутствии 0
 long Is3DParam(long incode,long level);   

 // Запрос длины параметров объекта по уровню (0,1,2 - где 0 - ближний)
 // и порядковому номеру (индексу ) объекта с 1
 // при ошибке или отсутствии 0
 long Get3DLength(long incode,long level);

 // Запрос функции отображения параметров объекта по уровню (0,1,2 - где 0 - ближний)
 // и порядковому номеру (индексу ) объекта с 1
 // при ошибке или отсутствии 0
 long Get3DFunction(long incode,long level);

 // Запрос кода библиотеки отображения параметров объекта
 // по уровню (0,1,2 - где 0 - ближний)
 // и порядковому номеру (индексу ) объекта с 1
 // при ошибке или отсутствии 0
 long Get3DObjectLibraryCode(long incode,long level);

 // Запрос ключа отображения параметров объекта
 // по уровню (0,1,2 - где 0 - ближний)
 // и порядковому номеру (индексу ) объекта с 1
 // при ошибке или отсутствии 0
 long Get3DObjectKey(long incode,long level);

 // Запрос функции отображения параметров объекта по уровню (0,1,2 - где 0 - ближний)
 // и порядковому номеру (индексу ) объекта с 1
 // при ошибке или отсутствии 0
 F3DTREE * Get3DParam(long incode,long level);

 // Связать объект по уровню (0,1,2 - где 0 - ближний)
 // и порядковому номеру (индексу ) объекта с 1
 // с изображением по коду библиотеки и ключу объекта
 // при ошибке 0
 long Set3DImageToObject(long incode, long level,long code, long key);

 // Запрос параметров 3D изображения
 // и коду библиотеки и ключу изображения
 // при ошибке или отсутствии 0
 // иначе указатель параметров иображения F3DTREE
 F3DTREE * Get3DImageParam(long code,long key);

// Установить параметры 3D изображения
// по коду библиотеки,ключу,номеру функции,типу метрики,
// длине параметров и параметрам
// при ошибке или отсутствии 0
long Set3DImageParam(long code,long key,long type,long length, char * param);

// Заменить название 3D изображения
// по коду библиотеки,ключу
// при ошибке или отсутствии 0
long Set3DImageName(long code,long key,char * name);

// Создать параметры 3D изображения
// по коду библиотеки,типу метрики,условному названию,
// длине параметров и параметрам (типа P3DTREE)
// при ошибке или отсутствии 0 , иначе код изображения
long Create3DImage(long code,long type,long length,char * param,char * name);

// Создать умалчиваемый шаблон                                        
// по коду библиотеки
// при ошибке возвращает 0, если был - 1 иначе 2
long Create3DDefaultImage(long code);

// Запросить общее количество записей укаанного типа в библиотеке
// (OBJECT_PARAMETERS,OBJECT_TEXTURE ...  rscfl3d.h)
// при ошибке 0.
long TakeRecordCount(long code,long type);

// Запросить заголовок записи указанного типа по коду
// При ошибке 0.
RECHEAD * TakeCodeRecordHead(long code);

// Запросить заголовок записи по коду библиотеки и ключу            
// при ошибке или отсутствии 0
RECHEAD * TakeKeyRecordHead(long code,long key);

// Запросить указатель на заголовок записи указанного типа по порядковому номеру
// в библиотеке c данным кодом
// ( тип - OBJECT_PARAMETERS,OBJECT_TEXTURE ...  rscfl3d.h)
// Вовращает код записи, при ошибке 0.

long TakeRecordHead(long number,long code,long type,RECHEAD * address);

// Запросить общее количество текстур
// при ошибке 0.
long TakeTextureCount();

// Запросить адрес текстуры по порядковому номеру
// При ошибке 0.
RECTEXTURE * TakeTexture(long number);

// Создать запись текстуры
// по коду библиотеки,условному названию,
// при ошибке или отсутствии 0 , иначе код текстуры
long Create3DTexture(long code,RECTEXTURE * texture,char * name);

// Заменить запись текстуры
// по коду библиотеки,ключу текстуры,условному названию,
// при ошибке или отсутствии 0 , иначе код текстуры
long Replace3DTexture(long libcode,long key,RECTEXTURE * texture,char * name);

// Удалить запись текстуры
// по коду библиотеки,ключу текстуры
// при ошибке или отсутствии 0
long Delete3DTexture(long libcode,long key);

// Запросить использование текстуры
// по коду библиотеки,ключу текстуры
// Возвращает количество объектов, использующих данную текстуру
// при ошибке или отсутствии 0
long _fastcall Used3DTexture(long libcode,long key);

// Запросить свободный ключ записи библиотеки
// по коду библиотеки и типу записи
// вовращает ключ, при ошибке 0.
long TakeFreeKey(long code,long type);

// Убрать 3D изображение объекта по уровню (0,1,2 - где 0 - ближний)
// и порядковому номеру (индексу ) объекта с 1
// при ошибке 0                                                     
long Delete3DImageFromObject(long incode, long level);

// Запросить адрес параметров материала по коду(номеру в таблице записей)(с 1)
// При ошибке 0.
ACT3DMATERIALMODE * Take3DMaterial(long number);     

// Заменить параметры материала по коду библиотеки и ключу
// При ошибке 0, иначе код записи материала
long Replace3DMaterial(long libcode,long key,ACT3DMATERIALMODE * material); 

// Удалить параметры материала по коду библиотеки и ключу
// При ошибке 0, иначе код записи материала
long Delete3DMaterial(long libcode,long key); 

// Заменить название материала по коду библиотеки и ключу
// (название уникально для данной библиотеки)
// При ошибке 0
long Replace3DMaterialName(long libcode,long key, char * name);     

// Создать запись материала по коду библиотеки, параметрам материала и
// названию (название уникально для данной библиотеки)
// При ошибке 0 иначе код записи материала
long Create3DMaterial(long libcode,ACT3DMATERIALMODE * material,char * name);


#endif   // HIDERSC3D                         

 /****************************************************************
 *                                                               *
 * ДОСТУП К ОПИСАНИЮ ПАРАМЕТРОВ ТАБЛИЦЫ ИЗОБРАЖЕНИЙ ПО СЕМАНТИКЕ *  
 *                                                               *
 ****************************************************************/

 public:

 // Запрос количества изображений
 // 0 - при ошибке
 int GetGrsItemCount();

 // Запрос отображения по порядковому номеру,коду семантики и значению семантики
 // 0 - при ошибке
 IMAGEVALUE * GetGrsItem(unsigned long int index,unsigned long int code,
                         unsigned long  int value);

 // Записать новую группу отображений по коду семантики
 // и номеру функции отображения
 // возвращает порядковый номер группы
 // 0 - при ошибке
 int AppendGrs(unsigned long int code, unsigned long int image);

 // Записать отображениe по порядковому номеру группы и значению семантики
 // возвращает порядковый номер группы
 // 0 - при ошибке
 int AppendGrsItem(unsigned long int index,unsigned long  int value,
                   IMAGEVALUE * item);

 // Запросить отображениe по порядковому номеру группы и значению семантики
 // возвращает указатель на параметры
 // 0 - при ошибке
 char * GetGrsItemParam(unsigned long int index,unsigned long  int value);

 // Запросить номер функции отображения по порядковому номеру группы и
 // значению семантики
 // 0 - при ошибке
 int GetGrsItemFunction(unsigned long int index,unsigned long  int value);

/*****************************************************************
 *                                                               *
 * ДОСТУП К ОПИСАНИЮ ОСНОВНОЙ СТРУКТУРЫ                          *
 *                                                               *
 ****************************************************************/


  // Открыть классификатор района,выделить память,проверить структуру;
  int OpenTRscBase(const char * name, int mode)
     {
       Mode_RSC = mode;
       return(OpenTRscBase(name));
     }

   //  Открыть классификатор района,проверить и заполнить
   int OpenTRscBase(const char * name);

   // Cоздать классификатор,выделить память,заполнить заголовок,
   int CreateTRscBase(char * name);

   // Закрыть классификатор
   int CloseRscBase(void);

   //  Закрыть классификатор и сообщить об ошибке
   int Exit(int error);

   // Установить/Запросить режим доступа
   int AccessMode(int mode);

   int AccessMode() { return Mode_RSC; }

   int AccessShare(int mode) { return (Share_RSC = mode); }
   int AccessShare() { return Share_RSC; }

   // Поменять порядок байтов в заголовке
   int TurnHeader(RSCHEAD * rsc);

   // Поменять порядок байтов в остальных таблицах
   int TurnTable();

   // Поменять порядок байтов таблице таблиц         
   int TurnTableTab(TABTAB * tab);

   // Запрос старой версии данных
   int IsOldVersion();

   // Декодирование строк
   char * DecodeString(char * text,int length);

/*****************************************************************
 *                                                               *
 *              ДОСТУП К ПАМЯТИ                                  *
 *                                                               *
 ****************************************************************/

 // Выделить участок памяти заданной длины
 // При ошибке возвращает ноль

  char * GetMemoryBlock(long length);

 // Взять дополнительную память
 // При ошибке возвращает ноль
 // length - размер элемента цепочки

   long OpenMemory(long length = 32*1024);

 // Сдать дополнительную память
 // При ошибке возвращает ноль

  int CloseMemory();

/*****************************************************************
 *                                                               *
 *              ДОСТУП К ТАБЛИЦАМ                                *
 *                                                               *
 ****************************************************************/
#ifdef LP64MODEL
//Увеличить размер массива адресов Memlist на buffersize элементов
intptr_t ReallocMemlist(ULONG);
#endif

//Получить доступ к 64-разрядному адресу по 32-разрядному индексу
intptr_t Off_64(ULONG) const;

//Получить доступ к 64-разрядному адресу по 32-разрядному индексу
intptr_t Off_64(void *) const;

//Получить 32-разрядный индекс для 64-разрядного адреса
ULONG Off_32(intptr_t);
 
//Получить 32-разрядный индекс для 64-разрядного адреса
ULONG Off_32(void *);
 /****************************************************************
 *                                                               *
 *            ВНУТРЕННИЕ ПЕРЕМЕННЫЕ КЛАССА TMapRsc               *
 *                                                               *
 ****************************************************************/

 public:

 char RscPath[MAX_PATH];     // Полный путь доступа к классификатору
 char RscName[MAX_PATH];     // Имя файла классификатора

 TABRSC *     TabRsc;         // Таблица основных параметров для объекта

 TABGRSITEM * TabGrsItem;     // Tаблице изображений семантики

 long int     TabRscCount;    // Число записей в таблице основных параметров

 long int     TabGrsCount;    // Число записей в таблице изображений семантики

 long int     ModifyFlag;     // Флаг изменения RSC

 long int     LastError;      // Код ошибки последней операции

 long int     APIOpenFlag;    // Признак открытия через API
 long int     Mode_RSC;       // Режим доступа к классификатору
 long int     Share_RSC;      // Режим доступа к классификатору
 HANDLE       File_RSC;       // Идентификатор файла
 char         SeekFont[256];  // Таблица соответствия кодов шрифта и строки
                              // в общей таблице
 long int     Is3DWork;       // 1 - открыли работу с 3D изображениями
 RSCRECORD  * TabRecord;      // Таблица записей с P3D - файлов
 long int     RealRecCount;   // Количество занятых элементов в таблице записей
 long int     RecordCount;    // Общее количество элементов в таблице записей

 char *  DanRsc;              // Начало области памяти классификатора

 RSCHEAD  Rsc;                // ЗАГОЛОВОК ФАЙЛА РЕСУРСОВ (КЛАССИФИКАТОРА)

 MEMHEAD * Memory;            // Заголовок элемента цепочки

 int  Freeobject;             // Количество свободных объектов
 int  Freesemantic;           // Количество свободных семантик
 int  Freesegment;            // Количество свободных сегментов
 int  Freeiml;                // Количество свободных библиотек
 int  Freetxt;                // Количество свободных шрифтов
 int  Freefrm;                // Количество свободных шрифтов
 int  Freegrs;                // Количество свободных образов семантики

#ifdef LP64MODEL
intptr_t * Memlist;           //Массив адресов
unsigned int MemLength;       //Размер массива адресов
unsigned int MemCounter;      //Текущее значение счетчика
#endif

}
TMapRsc;

typedef TMapRsc TRSCDATA;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++   ПОСТРОЕНИЕ СПРАВОЧНОЙ ТАБЛИЦЫ, ДОСТУП К РЕСУРСАМ  ++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Запрос общих данных классификатора
int _fastcall rscGetRscDescribe(TRSCDATA * data,RSCCREATE * rsccreate,
                                PALETTE256 * palette);
// Определить доступны ли ресурсы карты
int _fastcall rscIsActive(TRSCDATA * data);

// Запрос адреса палитры  по ее номеру
COLORREF * _fastcall rscGetPalette(TRSCDATA * data,int number);

// Запрос идентификатора описания палитры  по порядковому номеру (с 1)
TABPAL * _fastcall rscGetTabPal(TRSCDATA * data,int number);

// Установка/возврат  масштаба карты
long _fastcall rscGetScale(TRSCDATA * data);
long _fastcall rscScale(TRSCDATA * data,long scale);

// Запрос даты создания файла
char * _fastcall rscDate(TRSCDATA * data);

// Установка/возврат  типа классификатора
char * _fastcall rscType(TRSCDATA * data);
char * _fastcall rscSetType(TRSCDATA * data,char *str);

// Установка/возврат  имени классификатора
char * _fastcall rscName(TRSCDATA * data);
char * _fastcall rscSetName(TRSCDATA * data,char *str);

// Запросить полное (с путем) имя файла классификатора
int  _fastcall rscGetRscName(TRSCDATA * data,char * name, int size);

// Запрос количества объектов
int  _fastcall rscGetObjCount(TRSCDATA * data);

// Запрос внешнего кода служебного объекта по локализации
long _fastcall rscGetServObjExcode(TRSCDATA * data,int local);

// Запрос внутреннего кода служебного объекта по локализации
int _fastcall rscGetServObjIncode(TRSCDATA * data,int local);

// Запрос внутреннего кода объекта по внешнему коду и локализации
// При ошибке возвращает 0
int _fastcall rscGetObjIncode(TRSCDATA * data,long excode,int local);

//  Запрос внутреннего кода объекта по внешнему коду,локализации
//  и расширению
//  При ошибке возвращает 0
int _fastcall rscGetObjExtendIncode(TRSCDATA * data,long excode,int local,
                                    int extend);

// Последовательный запрос внутреннего кода объекта по внешнему
// коду и внутреннему коду предыдущего объекта (при отсутствии
// внутреннего кода - поиск с первого объекта
int  _fastcall rscGetNextObjIncode(TRSCDATA * data,long excode,int incode);

// Запрос имени объекта по внутреннему коду
const char * _fastcall rscGetObjName(TRSCDATA * data,int incode);

// Запрос ключа объекта по внутреннему коду
const char * _fastcall rscGetObjKey(TRSCDATA * data,int incode);

// Запрос идентификтора объекта по внутреннему коду
long _fastcall rscGetObjIdent(TRSCDATA * data,int incode);          

// Запрос внутреннего кода объекта по идентификтору                        
long _fastcall rscGetObjIdentIncode(TRSCDATA * data,int ident);

// Запрос внутреннего кода объекта по ключу             
long _fastcall rscGetObjKeyIncode(TRSCDATA * data,const char * key);

// Запрос длины имени объекта
int _fastcall rscGetObjNameSize();

// Запрос нижней границы видимости по внутреннему коду
int _fastcall rscGetObjBot(TRSCDATA * data,int incode);

// Запрос верхнeй границы видимости по внутреннему коду
int _fastcall rscGetObjTop(TRSCDATA * data,int incode);

// Запрос масштабируемости объекта по внутреннему коду
int _fastcall rscGetObjScale(TRSCDATA * data,int incode);

// Запрос сжимаемости объекта по внутреннему коду
int _fastcall rscGetObjPress(TRSCDATA * data,int incode);

// Записать сжимаемость объекта по внутреннему коду (0/1)           
// 0 - сжимать, 1 - не сжимать
int _fastcall rscSetObjPress(TRSCDATA * data, int incode,int press);

//----------------------------------------------------------------------------------------- 
 // Запрос предела масштабируемости объекта по внутреннему коду     
int _fastcall rscGetObjScaleLimit(TRSCDATA * data,int incode);

// Запрос предела сжимаемости объекта по внутреннему коду
int _fastcall rscGetObjPressLimit(TRSCDATA * data,int incode);

// Записать предел масштабируемости объекта по внутреннему коду  
int _fastcall rscSetObjScaleLimit(TRSCDATA * data,int incode,int scalelimit);

// Записать предел сжимаемости объекта по внутреннему коду
int _fastcall rscSetObjPressLimit(TRSCDATA * data,int incode,int presslimit);
//------------------------------------------------------------------------------------------- 

// Запрос направления цифрования объекта по внутреннему коду
int _fastcall rscGetObjDirect(TRSCDATA * data,int incode);

// Запрос количества возможных семантик по внутреннему коду объекта
int _fastcall rscGetObjOnlyPosSemCount(TRSCDATA * data,int incode);

// Запрос количества возможных семантик по внутреннему коду объекта
// c учетом возможных для слоя и общих семантик                     
int _fastcall rscGetObjPosSemCount(TRSCDATA * data,int incode);

// Запрос количества обязательных семантик по внутреннему коду объекта
int _fastcall rscGetObjMustSemCount(TRSCDATA * data,int incode);

// Запрос кода возможной семантики по внутреннему коду объекта и
// порядковому номеру в возможных семантиках (c 1)
int _fastcall rscGetObjOnlyPosSem(TRSCDATA * data,int incode,int number);

// Запрос кода возможной семантики по внутреннему коду объекта и
// порядковому номеру в возможных семантиках (c 1)
// c учетом возможных для слоя и общих семантик                     
int _fastcall rscGetObjPosSem(TRSCDATA * data,int incode,int number);

// Запрос кода семантики по внутреннему коду объекта и
// порядковому номеру(c 1) с учетом сортировки пользователя
// возможные для слоя и общие семантики идут в конце         
int _fastcall rscGetObjOrderSem(TRSCDATA * data,int incode,int number);

// Записать порядок семантик для объекта в соответствии с входным списком
// count - размер массива семантик объекта
// semantics - указатель на сортированный список семантик объекта.
// order     - указатель на выходной массив порядковых номеров
// Семантики которые не наначены объекту (в том числе и общие) - пропускаются,
// Если какие - то семантики пропущены пишутся в конец списка
// при нормальном завершении возвращает количество семантик объекта
int  _fastcall  rscSetObjSemanticOrder(TRSCDATA * data,int objincode,
                                       int count,long * semantics);

// Пересортировать массив семантик для объекта в соответствии с
// порядковыми номерами
// count - размер массива семантик объекта для сортировки
// semantics - указатель на список номеров требуемых семантик объекта.
// order     - указатель на выходной массив заполнен отсортированными
// порядковыми номерами входных семантик(с 1 )
// при нормальном завершении возвращает 1

int  _fastcall  rscSortObjSemantic(TRSCDATA * data,int objincode,
                                     int count,long * semantics,long * orders);

// Запрос порядка вывода кода семантики по внутреннему коду объекта
// с учетом сортировки пользователя
// 0 - семантика не принадлежит объекту либо общая           
int _fastcall rscGetObjSemOrderNumber(TRSCDATA * data,int incode,int semcode);

// Запрос семантика объекта сортирована?
// 0 - нет, 1- да                                           
int rscIsObjSemOrdered(TRSCDATA * data,int incode);

// Запрос кода обязательной семантики по внутреннему коду объекта и
// порядковому номеру в возможных семантиках (c 1)
int _fastcall rscGetObjMustSem(TRSCDATA * data,int incode,int number);

// Запрос количества пороговых семантик по внутреннему коду объекта
int _fastcall rscGetObjLimSemCount(TRSCDATA * data,int incode);

// Запрос кода пороговой семантики по внутреннему коду объекта и
// порядковому номеру в пороговых семантиках (c 1)
int _fastcall rscGetObjLimSem(TRSCDATA * data,int incode,int number);

// Запрос идентификатора описания семантики по коду
TABSEM * _fastcall rscGetTabSem(TRSCDATA * data,int code);

//  Запрос количества семантик
int _fastcall rscGetSemCount(TRSCDATA * data);

// Запрос имени семантики по коду
const char * _fastcall rscGetSemName(TRSCDATA * data,int code);

// Запрос длины имени семантики
int _fastcall rscGetSemNameSize();

// Запрос короткого имени семантики по коду
const char * _fastcall rscGetSemShortName(TRSCDATA * data,int code);

// Запрос общей длины поля значения семантики
int _fastcall rscGetSemValuePoleSize(TRSCDATA * data,int code);

// Запрос точности значения семантики
int _fastcall rscGetSemValuePoleDecimal(TRSCDATA * data,int code);

// Запрос короткого имени сегмента по внутреннему коду сегмента
const char * _fastcall rscGetSegShortName(TRSCDATA * data,int number);

// Запрос количества сегментов
int _fastcall rscGetSegCount(TRSCDATA * data);

// Запрос имени сегмента по внутреннему коду сегмента
char * _fastcall rscGetSegName(TRSCDATA * data,int number);

// Заполнить структуру описания слоев
// RSCSEGMENT -  структура входных данных  (см. maptype.h)
// incode - порядковый номер слоя
// При ошибке возвращает ноль ( код ошибки не равен 0 )
// иначе порядковый номер слоя
int _fastcall rscGetSegment(TRSCDATA * data,int incode, RSCSEGMENT *segment);

// Запрос порядка вывода сегмента на экран по порядковому номеру
int _fastcall rscGetSegOrder(TRSCDATA * data,int number);

// Установка имени сегмента по порядковому номеру сегмента
int _fastcall rscSetSegName(TRSCDATA * data,int number,char * name);

// Установка порядка вывода сегмента по порядковому номеру сегмента
int _fastcall rscSetSegOrder(TRSCDATA * data,int incode,char order);

// Запрос длины имени сегмента
int _fastcall rscGetSegNameSize();

// Запрос идентификатора описания сегмента по внутреннему коду сегмента
TABSEG * _fastcall rscGetTabSeg(TRSCDATA * data,int incode);

// Очистить строку от пробелов
// size - размер строки
// Убирает начальные и конечные пробелы.
// При ошибке возвращает 0
int _fastcall rscClearofBlank(char * name,int size);

// Запрос внутреннего кода сегмента по имени
// При отсутствии сегмента возврат - 0 , код ошибки IDS_NOTFIND
int _fastcall rscGetSegmentByName(TRSCDATA * data,char * name);

// Запрос порядкового номера элемента по имени (порядковый номер с 0)
// Type - тип запроса : для слоя по имени - 1,
//                      для слоя по короткому имени - 2,
//                      для семантики по имени - 3,
//                      для семантики по короткому имени - 4,
//                      для объекта по ключу   - 5
// При отсутствии - 0 , код ошибки IDS_NOTFIND
int _fastcall rscGetElementbyName(TRSCDATA * data,const char * name,int type);

// Запрос кода семантики по порядковому номеру
// семантической характеристики (с 1 )
int _fastcall rscGetSemOrderExcode(TRSCDATA * data,int number);

// Установить палитру по умолчанию  number - номер палитры (c 1)
COLORREF * _fastcall rscSetDefaultPalette(TRSCDATA * data,int number);

// Запрос значения умалчиваемого цвета по индексу в палитре
COLORREF _fastcall rscGetDefaultColor(TRSCDATA * data,int index);

// Запрос значения цвета по индексу в первой палитре
COLORREF _fastcall rscGetRscColor(TRSCDATA * data,int index);

// Запрос количества цветов в палитре классификатора
int _fastcall rscGetRscColorCount(TRSCDATA * data);

// Установить количество цветов, примененных в классификаторе
int _fastcall rscSetRscColorCount(TRSCDATA * data,int number);

// Запрос адреса цвета с номером index первой палитры
COLORREF * _fastcall rscGetRscPalette(TRSCDATA * data,int index);

// Запрос количества палитр
int _fastcall rscGetPaletteCount(TRSCDATA * data);

// Запрос имени палитры по ее номеру
char * _fastcall rscGetPaletteName(TRSCDATA * data,int number);

// Установить цвет (в первой палитре)
// Возвращает бывший цвет
COLORREF  _fastcall rscSetRscColor(TRSCDATA * data,COLORREF color,int index);

// Установить всю первую палитру
int _fastcall rscSetRscPalette(TRSCDATA * data,COLORREF * colorref,int number);

// Восстановить палитру с диска по номеру (с 1)
// сбрасывает яркость и контрастность
// Возвращает адрес палитры
COLORREF * _fastcall rscResetPalette(TRSCDATA * data,int number);

// Запрос номера последней функции визуализации
int _fastcall rscGetLastFunction();

// Записать новую палитру
// palette - цвета палитры,count - количество цветов в палитре
// name    - название палитры
// возвращает указатель на созданную палитру
// 0 - при ошибке
TABPAL * _fastcall rscAppendPalette(TRSCDATA * data,COLORREF * palette,
                                    int count,char *name );

// Преобразование палитры из RGB в CMYK                
// number - количество цветов
// rgb - адрес палитры(COLORREF)
// cmyk - адрес, для размещения палитры CMYK (4 байта на цвет)
int _fastcall rscCreateCMYK(long int count,char * rgb,char * cmyk);

// Заполнить палитру CMYK                        
// number - количество записываемых цветов
// begin  - область CMYK цветов
// 0 - при ошибке
int _fastcall rscSetCMYKPalette(TRSCDATA * data,long number,long * begin);

// Запросить палитру CMYK                        
// Возвращает адрес CMYK палитры
// 0 - при ошибке
char * _fastcall rscGetCMYKPalette(TRSCDATA * data);

// Выделить участок памяти заданной длины
char * _fastcall rscGetMemoryBlock(TRSCDATA * data,long length);

//  Взять дополнительную память
long _fastcall rscOpenMemory(TRSCDATA * data,long length);

//  Сдать дополнительную память
int _fastcall rscCloseMemory(TRSCDATA * data);

// Запрос/Установка максимального идентификатора объектов
int _fastcall rscMaxKey(TRSCDATA * data);
int _fastcall rscSetMaxKey(TRSCDATA * data);

// Запрос/Установка модификации файла
int  _fastcall rscMode(TRSCDATA * data);
int _fastcall rscSetMode(TRSCDATA * data,int mode);

// Запрос модификации палитры                               
int _fastcall rscColorStyle(TRSCDATA * data);

// Запрос/Установка codа классификатора объектов
char * _fastcall rscClassificatorCode(TRSCDATA * data);
int _fastcall rscSetClassificatorCode(TRSCDATA * data,char * code);

// Запрос/Установка языка классификатора
int _fastcall rscGetClassificatorLanguage(TRSCDATA * data);
int _fastcall rscSetClassificatorLanguage(TRSCDATA * data,int language);

// Запрос/Установка номера таблицы масштабов
int _fastcall rscScaleTableNumber(TRSCDATA * data);
int _fastcall rscSetScaleTableNumber(TRSCDATA * data,int scaletable);

// Запрос типа значения семантики по коду
int _fastcall rscGetSemType(TRSCDATA * data,int code);

// Запрос признака служебной семантики по коду
// Принимает значения 0 - 1
int _fastcall rscGetSemService(TRSCDATA * data,int code);

// Запрос количества значений классификатора по  коду
// семантической характеристики
int _fastcall rscGetClassificatorCount(TRSCDATA * data,int incode);

// Запрос идентификатора описания классификатора по  коду
// семантической характеристики и порядковому номеру (с 1)
TABCLS * _fastcall rscGetTabCls(TRSCDATA * data,int incode,int number);

// Запрос числового значения классификатора по  коду
// семантической характеристики и порядковому номеру (с 1)
int _fastcall rscGetClassificatorValue(TRSCDATA * data,int incode,int number);

// Запрос "имени" значения классификатора по  коду
// семантической характеристики и порядковому номеру (с 1)
const char * _fastcall rscGetClassificatorName(TRSCDATA * data,int incode,
                                               int number);

//  Запрос "имени" значения по коду семантики и
//  коду значения
const char * _fastcall rscGetSemValueName(TRSCDATA * data,int code,int value);

//  Запрос максимальной длины "имени" значения
int _fastcall rscGetSemValueSize();

//  Запрос наименования единицы измерения семантики
//  Если нет единицы измерения - возвращает указатель
//  на пустую строку
//  При ошибке возвращает пустую строку
const char * _fastcall rscGetSemUnit(TRSCDATA * data,int code);

//  Запрос максимальной длины наименования единицы измерения
int _fastcall rscGetSemUnitSize();

// Запрос повторяемости значения семантики по коду
int _fastcall rscGetSemReply(TRSCDATA * data,int code);

// Проверка существования и создание при необходимости
// рамки листа возврат 1
// Остальные структурные ошибки - возврат 0
int _fastcall rscCheckFrameCode(TRSCDATA * data);

// Запрос внутреннего кода рамки листа
// Остальные структурные ошибки - возврат 0
int _fastcall  rscGetFrameCode();

// Запрос внешнего кода рамки листа
long _fastcall rscGetFrameCodeEx(TRSCDATA * data);

// Запрос длины параметров визуализации по внутреннему коду объекта
long _fastcall rscGetParLength(TRSCDATA * data,int incode);

// Установить адрес записи таблицы параметров по внутреннему коду,
// номеру функции,длине и параметрам
// если возврат 0 - ошибка
VIEPAR * _fastcall rscSetTabPar(TRSCDATA * data,int incode,int length,
                                int number,char * param);

// Установить адрес записи таблицы параметров по внутреннему коду
// и параметрам
// если возврат 0 - ошибка
VIEPAR  * _fastcall rscSetTabParHead(TRSCDATA * data,int incode,VIEPAR  * apar);

// Установить адрес записи таблицы принтерных параметров по внутреннему
// коду, номеру функции,длине и параметрам
// если возврат 0 - ошибка
VIEPAR * _fastcall rscSetTabPrn(TRSCDATA * data,int incode,int length,
                                int number,char * param);

// Установить адрес записи таблицы принтерных параметров по внутрен-
// нему коду и параметрам
// если возврат 0 - ошибка
VIEPAR  * _fastcall rscSetTabPrnHead(TRSCDATA * data,int incode,VIEPAR  * apar);

// Сбросить принтерные параметры объекта
// по внутреннему коду
void _fastcall rscDeleteTabPrn(TRSCDATA * data,int incode);

// Запрос - можно ли редактировать RSC ?
int _fastcall rscIsWrite(TRSCDATA * data);

// Удалить объект - возвращает внутренний код удаленного объекта
// если объект входит в серию - удаление не делается
int _fastcall rscDeleteObject(TRSCDATA * data,int incode);

// Создать новый объект - возвращает внутренний код объекта
// если check == 0 нет проверки на единственность объекта
int  _fastcall rscAppendObject(TRSCDATA * data,RSCOBJ * robj,int check);

// Создать внешний вид стандартного объекта по локализации
int  _fastcall rscCreateDefaultView(TRSCDATA * data,int incode);

// Записать внешний код объекта по внутреннему коду
// Проверка на наличие серии не делается
long _fastcall  rscSetObjExcode(TRSCDATA * data,int incode,long excode);

// Удалить умолчания на объект по любым семантикам
// возвращает код объекта (ошибка - 0 )
int _fastcall rscDeleteDefObject(TRSCDATA * data,int incode);

// Удалить умолчания на семантику - общие (objincode = 0)
// или на объект
// возвращает указатель на исправленную семантику (ошибка - 0 )
TABSEM * _fastcall rscDeleteDef(TRSCDATA * data,int objincode,int semcode);

// Удалить серию - удалить таблицу порогов и все объекты
// входящие в серию,обнулить ссылки на возможную семантику,
// убрать умолчания
int  _fastcall rscDeleteSeria(TRSCDATA * data,long excode,int local);

// Скопировать объект на указанное по внутреннему коду
// место (внешний код обнуляется)
// если на указанном месте был объект из серии - копирование не
// делается
// если объект - источник удален, копирование не делается
// возвращает внутренний код нового объекта
int _fastcall rscCopyObjectIncode(TRSCDATA * data,int newincode,int oldincode);

// Переопределить внешний код объекта
// Замещается также внешний код умолчаний
// Проверка на наличие серии не делается
long _fastcall rscUpdateObjExcode(TRSCDATA * data,int incode,long newexcode);

// Переопределить локализацию объекта
// Замещается также внешний код умолчаний
// Проверка на наличие серии не делается
long _fastcall rscUpdateObjLocal(TRSCDATA * data,int incode,int newlocal);

// Записать расширенную локализацию объекта по внутреннему коду
// (расширенная локализация объекта принимает значения 0 или 1)
// Указывает на "векторность объекта" (1 - изображение по 2 точкам)
int _fastcall rscSetObjExtloc(TRSCDATA * data,int incode,int exl);

// Записать ключ объекта по внутреннему коду
char * _fastcall rscSetObjKey(TRSCDATA * data,int incode,char * key);

// Записать направление цифрования объекта
int _fastcall rscSetObjDirect(TRSCDATA * data,int incode,int direct);

// Проверяет для объекта единственность сочетания кода + локализа-
// ции. При совпадении возвращает 0
int _fastcall rscCheckObjectCode(TRSCDATA * data,unsigned long code,int local);

// Запрос имени семантики по порядковому номеру
// семантической характеристики ( с 1 )
const char * _fastcall rscGetSemOrderName(TRSCDATA * data,int number);

// Записать новый слой - возвращает порядковый N слоя с 0
int  _fastcall rscAppendSeg(TRSCDATA * data,RSCSEG * rseg);
int _fastcall rscAppendSegment(TRSCDATA * data,RSCSEGMENT * segment);

// Создание служебных объектов
int  _fastcall rscCreateServObjects(TRSCDATA * data);

// Запрос смещения на таблицу семантики в памяти
TABSEM *  _fastcall rscGetOffSem(TRSCDATA * data);

// проверить наличие записи в таблице допустимых значений семантики
// по внутреннему коду объекта и коду семантики,
// если не нашли возвращает 0
TABDEF *  _fastcall rscCheckTabDef(TRSCDATA * data,int incodeobject,int semcode);

// Заполняет минимум,умолчание и максимум значения семантики
// по внутреннему коду объекта и коду семантики
// если не нашли возвращаем 0
int  _fastcall rscGetDefValue(TRSCDATA * data,int incodeobject, int semcode,
                              RSCDEF * valdef);

// Запрос значения семантики по умолчанию
// по внутреннему коду объекта и внутреннему коду семантики
// Значение преобразовано в символьную строку
// Если на объект есть пороги - возвращает умалчиваемое значе-
// ние семантики,если оно соответствует внутреннему коду объекта
// иначе - первое соответствующее внутреннему коду объекта
// возвращает 1,при ошибке 0
int _fastcall rscGetDefValueSemantic(TRSCDATA * data,int objincode,
                                int semanticcode,char * strdef,int lenstrdef);

// Запрос масштаба по номеру в текущей таблице
long  _fastcall rscGetScaleItem(TRSCDATA * data,int number);

// Запрос масштаба по номеру в указанной таблице масштабов(0,1)
long  _fastcall rscGetTableScaleItem(TRSCDATA * data, int tablenumber, int number);

// Запросить размер файла классификатора
// При ошибке возвращает 0
long int _fastcall rscFileSize(TRSCDATA * data);

// Установка/возврат флага открытия файла через API
int _fastcall rscApiOpenFlag(TRSCDATA * data);
int _fastcall rscSetApiOpenFlag(TRSCDATA * data,int flag);

// Запрос количества объектов сегмента по внутреннему коду сегмента
int _fastcall rscGetSegmentObjectCount(TRSCDATA * data,int incode);

// Запрос количества не удаленных объектов сегмента по внутреннему коду сегмента
int _fastcall rscGetSegmentObjectRealCount(TRSCDATA * data,int incode);

// Удалить сегмент по внутреннему коду  сегмента
// Служебный слой не удаляется
int _fastcall rscDeleteSegment(TRSCDATA * data,int incode);

// Перенести объекты из одного слоя в другой
// Из служебного слоя и в служебный слой - объекты не переносятся
// Возвращает новый номер слоя, либо 0 - ошибка
int _fastcall rscMoveSegmentObjects(TRSCDATA * data,int oldcode,int newcode);

// Запрос количества объектов с данным внешним кодом и локализацией
// При ошибке или отсутствии возвращает 0
int _fastcall rscGetObjNumber(TRSCDATA * data,long excode,int local);

// Запрос использования семантики в объектах классификатора
int _fastcall rscGetSemInfo(TRSCDATA * data,int code,
                            APPLYSEMANTIC * applysemantic);

// Запрос количества объектов с данной локализацией в данном слое
int _fastcall rscGetSegmentObjNumber(TRSCDATA * data,int segment,int local);

// Запросить описание объекта  по внутреннему коду
// если код = 0 - заполнение по умолчанию
int _fastcall rscGetDescribeObj(TRSCDATA * data,int incode,RSCOBJECT * object);

// Запрос таблицы отображения шаблонов
// На входе внутренний код
// TABLETEMPLATE (определено в Mapgdi.h)
// при ошибке возврат 0
int _fastcall rscGetTemplateTable(TRSCDATA * data,int incode,
                                  TABLETEMPLATE * table);

// Запрос длины параметров печати по внутреннему коду объекта
long _fastcall rscGetPrnLength(TRSCDATA * data,int incode);

// Запрос внешнего кода объекта по внутреннему коду
long _fastcall rscGetObjExcode(TRSCDATA * data,int incode);

// Запрос сегмента объекта по внутреннему коду
int _fastcall rscGetObjSegment(TRSCDATA * data,int incode);

// Запрос локализации объекта по внутреннему коду
int _fastcall rscGetObjLocal(TRSCDATA * data,int incode);

// Запрос функции отображения объекта по внутреннему коду
// Возвращаемое значение не должно превышать значения
// функции GetLastFunction()
int _fastcall rscGetObjFunction(TRSCDATA * data,int incode);

// Запрос адреса начала параметров визуализации по внутреннему коду объекта
char  * _fastcall rscGetPar(TRSCDATA * data,int incode);

// Запрос адреса записи таблицы параметров по внутреннему коду объекта
VIEPAR * _fastcall rscGetTabPar(TRSCDATA * data,int incode);

// Запрос адреса записи таблицы параметров печати
// по внутреннему коду объекта
VIEPAR  * _fastcall rscGetTabPrn(TRSCDATA * data,int incode);

// Запрос адреса начала параметров печати по внутреннему коду объекта
char  * _fastcall rscGetPrn(TRSCDATA * data,int incode);

// Запрос расширенной локализации объекта по внутреннему коду
int _fastcall rscGetObjExtloc(TRSCDATA * data,int incode);

// Запрос признака применения семантики для отображения объекта
int _fastcall rscGetObjExtsem(TRSCDATA * data,int incode);
// Установка признака применения семантики для отображения объекта
int _fastcall rscSetObjExtsem(TRSCDATA * data,int incode, int flag );

//  Запрос идентификатора описания возможных семантик по внутреннему
//  коду объекта
TABPOS * _fastcall rscGetTabPos(TRSCDATA * data,int incode);

//  Запрос идентификатора описания порогов по внутреннему коду объекта
TABLIM * _fastcall rscGetTabLim(TRSCDATA * data,int incode);

// Запрос расширения объекта по внутреннему коду
int  _fastcall rscGetObjExtend(TRSCDATA * data,int incode);

// Записать сегмент объекта по внутреннему коду
int  _fastcall rscSetObjSegment(TRSCDATA * data,int incode,int segment);

// Сборка и запись ресурсов карты
int _fastcall rscSave(TRSCDATA * data,int mode);
int _fastcall rscGethRsc(TRSCDATA * data);

//  Сформировать копию RSC
int _fastcall rscBackCopy(TRSCDATA * data,int restore);

//  Закрыть классификатор и сообщить об ошибке
int _fastcall  rscExit(TRSCDATA * data,int error);

//  Закрыть классификатор
int _fastcall  rscCloseRscBase(TRSCDATA * data);

//  Удалить таблицы ссылок для объектов
void _fastcall rscCloseRsc(TRSCDATA * data);

// Освободить таблицу шрифтов
// 0 - при ошибке
int _fastcall rscFreeFontTable(TRSCDATA * data);

//  Открыть классификатор района,проверить и заполнить
int _fastcall rscOpenTRscBase(TRSCDATA * data,const char * name);

//  Создать классификатор
int  _fastcall rscCreateTRscBase(TRSCDATA * data,const char * name);

//  Открыть классификатор
//  При ошибке возвращает ноль
int _fastcall rscOpenRsc(TRSCDATA * data,const char * rsc, int mode);

//  Запрос памяти и заполнение таблиц для работы с объектами
int /*_fastcall*/ rscOpenTableRsc(TRSCDATA * data);

//  Создание нового классификатора
int _fastcall  rscCreateRsc(TRSCDATA * data,char * name, RSCCREATE * rsccreate,
                            PALETTE256 * palette,int createsem);

// Установить/Запросить режим доступа
int _fastcall rscSetAccessMode(TRSCDATA * data,int mode);
int _fastcall rscAccessMode(TRSCDATA * data);
int _fastcall rscSetAccessShare(TRSCDATA * data,int mode);
int _fastcall rscAccessShare(TRSCDATA * data);

// Декодирование строк
char *  _fastcall rscDecodeString(TRSCDATA * data,char * text,int length);

// Заполнение таблицы шрифтов
// 0 - при ошибке
int _fastcall rscFillFontTable(TRSCDATA * data);


// Дополним параметры шрифтов ( установить ссылку на таблицу шрифтов)
// для "простых" функций
void  _fastcall rscSetTextReferParam(TRSCDATA * data,int key, int newkey,
                                      int func, char * objparam);

// Дополним параметры шрифтов ( установить ссылку на таблицу шрифтов)
// при дополнении key = 0,newkey = 0.
// при удалении шрифта с кодом key - заменяем код шрифта  на  шрифт
// c кодом newkey, если  newkey = 0, заменяем на 1 шрифт.
// 0 - при ошибке
void  _fastcall rscSetTextRefer(TRSCDATA * data,int key,int newkey);     

// Записать новый шрифт - возвращает
// код шрифта
// При ошибке 0
int _fastcall rscAppendFont(TRSCDATA * data,RSCFONT * font);

// Создадим системную семантику
// При ошибке возвращает 0
unsigned long _fastcall rscAppendSystemSemantic(TRSCDATA * data);

// Создадим стандартную семантику
// При ошибке возвращает 0
unsigned long _fastcall rscAppendStandardSemantic(TRSCDATA * data);

// Записать новую семантику - возвращает
// указатель на созданную семантику
TABSEM * _fastcall rscAppendSemantic(TRSCDATA * data,RSCSEM * rsem);

// Проверяет для семантики единственность кода
// При совпадении возвращает 0
int _fastcall rscCheckSemanticCode(TRSCDATA * data,int code);

// Установка короткого имени сегмантики по внешнему коду семантики
int _fastcall rscSetSemShortName(TRSCDATA * data,int code,char * shortname);

// Добавить возможную семантику объекту
// Если объект не из серии
// возвращает ее последовательный номер
// в возможных семантиках (начиная с 1),0 - ошибка
int  _fastcall rscAppendPosSemantic(TRSCDATA * data,int objincode,
                                    int semincode,int seria);

// Создать описание возможных семантик по внутреннему коду объекта
// если такое есть - возвращается указатель на существующую таблицу
TABPOS * _fastcall rscAppendPos(TRSCDATA * data,int incode,int seria);

// Поменять порядок байтов в заголовке
int _fastcall rscTurnHeader(TRSCDATA * data,RSCHEAD * rsc);

// Поменять порядок байтов в остальных таблицах
int _fastcall rscTurnTable(TRSCDATA * data);

// Поменять порядок байтов в таблице таблиц
int _fastcall rscTurnTableTab(TRSCDATA * data,TABTAB * tab);

// Поменять порядок байтов в параметрах объекта
// number - номер функции отображения
// param  - адрес параметров отображения
// возвращает указатель на конец параметров
char * _fastcall rscTurnParam(int number,char *param);

// Поменять порядок байтов в параметрах объекта(из LINUX в WINDOW)
// number - номер функции отображения
// param  - адрес параметров отображения
// возвращает указатель на конец параметров
char * _fastcall rscTurnParamBack(int number,char *param);    

// Сборка и запись ресурсов карты
int _fastcall rscCommit(TRSCDATA * data);

// Восстановить классификатор с диска
int _fastcall rscRevert(TRSCDATA * data);


// Запросить функцию отображения элемента векторных параметров объекта 
// param  - параметры отображения
// number - номер элемента (с 1)
// При ошибке возвращает 0
long _fastcall rscGetVectorElementIdent(IMGVECTOREX * vector, long number);

// Запросить параметры отображения элемента векторных параметров объекта 
// param  - параметры отображения
// number - номер элемента (с 1)
// При ошибке возвращает 0
char * _fastcall rscGetVectorElementParam(IMGVECTOREX * vector, long number);

// Запросить размеры векторного объекта
// semantic - указатель на семантику объекта, если подпись зависит от семантики
// При ошибке возвращает ноль
int _fastcall rscGetVectorSize(IMGVECTOREX * vector,IMAGESIZE* imagesize,
                                char * semantic, TRSCDATA * rsc);   

// Установить соответствие между данными классификатора в
// памяти и на диске
// 1  - данные совпадают
// 0  - ошибка
// -1 - обновили
int _fastcall rscAdjustData(TRSCDATA * data);

// Размер и свойства отображения объекта
// при ошибке возврат 0
// все размеры в микронах
// для шрифтов и шаблонов - размеры одной буквы
// если размеры 0 - объект не ограничивается
// (Строка string длиной length задается для
// определения горизонтального размера подписи)
// type = 0 - берется экранное отображение, 1 - принтерное
// При отсутствии принтерного вида - возврат 0  (код ошибки IDS_NOTFIND)
int _fastcall rscGetImageSize(TRSCDATA * data,int incode, IMAGESIZE * imagesize,
                              int lengthstr, const char * string,int imagetype);
// Размер и свойства отображения шрифта                           
// при ошибке возврат 0
// все размеры в микронах
// (Строка string длиной length задается для
// определения горизонтального размера подписи)
// нет строки - размеры одной буквы
int _fastcall rscGetTextSize( IMGTEXT * param, IMAGESIZE * imagesize,
                              const TFontDraw* fontDraw,
                              const char * text, int length);

// Найти "основной" цвет изображения объекта  по внутреннему коду 
// и виду отображения  0 - экранный, 1 - принтерный
// При отсутствии цвета возвращает 0xFF000000
// При ошибке возвращает 0
COLORREF _fastcall rscGetObjectBaseColor(TRSCDATA * data, int incode,
                                          long int viewtype);
// Найти "основной" цвет изображения примитива по номеру функции и параметрам 
COLORREF _fastcall rscGetBasePrimColor(TRSCDATA * data,int number, char * param);


// Запрос внутреннего кода объекта по внешнему коду, локализации
// и семантике объекта
// При ошибке возвращает 0
int _fastcall rscGetObjIncodeSem(TRSCDATA * data,long excode,int local,
                                        SEMANTICDATA *semnedit);
int _fastcall rscGetObjIncodeSemantic(TRSCDATA * data, long excode,
                                      int local, SEMANTIC * semn);

// Запрос имени локализации по номеру локализации
const char * _fastcall rscGetLocalName(TRSCDATA * data,int local,int language);

// Запрос количества локализаций
int _fastcall rscGetLocalCount();

// Запрос длины имени локализации
int _fastcall rscGetLocalNameSize();

// Установка короткого имени сегмента по внутреннему коду сегмента (c 0)
int _fastcall rscSetSegShortName(TRSCDATA * data,int incode,char * shortname);

// Запросить количество семантик для слоя по порядковому номеру
// слоя с 0
long _fastcall rscGetSegSemCount(TRSCDATA * data,int number);

// Запросить код семантики по порядковому номеру слоя (c 0) и
// номеру семантики в списке (с 1)
long _fastcall rscGetSegSemCode(TRSCDATA * data,int number,int order);

// Добавить код семантики в список слоя с порядковым номером
// numberseg ( c 0)
// возврат - порядковый номер добавленной семантики в списке (с 1)
long _fastcall rscAppendSegSemCode(TRSCDATA * data,int number,long code);

// Удалить код семантики из списка слоя с порядковым номером
// numberseg ( c 0)
long _fastcall rscDeleteSegSemCode(TRSCDATA * data,int number,long code);

// Создать список семантик для слоя
// index - порядковый N слоя
// type - тип семантик для сбора 0 - все
//                               1 - только обязательные
// возвращает указатель на исправленный слой
TABSEG * _fastcall rscBuildSegmentSemantic(TRSCDATA * data,int index,int type);

// Создать новый объект - возвращает внутренний код объекта
// Внешний вид созданного объекта соответствует служебному объекту (для данной
// локализации).
// Если указанный слой для создания объекта  не существует - объект
// создается в служебном слое
// Если такой объект (внешний код и локализация) уже существует -
// объект не создается - возврат 0.
// При ошибке - возвращает 0, иначе внутренний код созданного объекта
int _fastcall rscAppendObjectDefaultView(TRSCDATA * data,RSCOBJECT * robj);

// Скопировать объект на новое место
// (c внешним кодом FIRSTSERVEXCODE)
// удаленный объект не копируется
// возвращает внутренний код нового объекта
// Для того,чтобы данный объект остался при сохранении,
// пользователь должен переопределить внешний код
int _fastcall rscCopyObject(TRSCDATA * data,int oldincode);

// Обновить описание объекта  по внутреннему коду
// При наличии серии внешний код и локализация и слой - не меняются
// Если внешний вид не соответствует новому описанию -
// Заменить внешний вид на умалчиваемый
// Возвращает внутренний код , либо 0
int  _fastcall rscUpdateObject(TRSCDATA * data, int incode,RSCOBJECT * object);

// Рамка по размеру объекта по метрике
// number - номер функции отображения
// param  - параметры отображения
// angle  - угол поворота объекта в радианах (от направления на север
// по часовой стрелке)
// При ошибке возврат 0
int _fastcall rscGetImageFrame(TRSCDATA * data,int number, const char * param,
                           double angle,
                           IMAGEFRAME * imageframe);

// Поворот точки на угол a относительно точки origin  
int _fastcall rscTurnPoint(DOUBLEPOINT * origin, DOUBLEPOINT * point,
                       double sina, double cosa);

// Записать локализацию объекта по внутреннему коду
// (локализация объекта может быть равна 0)
// Если сменили локализацию существующего объекта,
// вид объекта не исправляем.
// Проверка на наличие серии не делается
int _fastcall  rscSetObjLocal(TRSCDATA * data,int incode,int local);

// Проверка соответствия локализации и примитива из отображения объекта
// при ошибке возврат 0
int _fastcall  rscGetImageSuitable(int local,int number);

// Запрос использования семантики для объекта по внутреннему коду объекта
// и коду семантики
// c учетом возможных для слоя и общих семантик                    
int _fastcall rscGetObjCanSem(TRSCDATA * data,int incode,int codesem);

// Запрос использования семантики для объекта по внутреннему коду объекта
// и коду семантики
int _fastcall rscGetOnlyObjCanSem(TRSCDATA * data,int incode,int codesem);

// Записать новую семантику - возвращает  код созданной семантики
// при ошибке возвращает 0                                       
unsigned long _fastcall rscAppendRscSemantic(TRSCDATA * data,RSCSEMANTICEX * rsem);

// Установка размера и точности значения семантики
int _fastcall  rscSetSemDecimal(TRSCDATA * data,int code,int size,int decimal);

// Записать новую "строчку" классификатора
// (числовое значение и символьное) возвращает
// указатель на исправленную семантику
TABSEM * _fastcall rscAppendCls(TRSCDATA * data,int codesemantic,
                                short int value,char * name);

// Проверяет для классификатора единственность числовых значений
// При совпадении возвращает 0
int _fastcall  rscCheckClassificatorCode(TRSCDATA * data,int codesemantic,
                                         int value);

// Обновить семантику
// rsem - адрес структуры, c описанием характеристики,
// code - код семантики которую обновляем,
// Если классификатор исправлялся - classupdate = 1  при этом
// очищено место под запись исправленного классификатора
// При ошибке возвращает 0
// Возвращает код исправленной семантики
// При ошибке возвращает 0
// Создается соответствующий код ошибки                   
 int _fastcall  rscUpdateSemantic(TRSCDATA * data,int code,RSCSEMANTICEX * rsem,
                                   int classupdate);

// Удалить семантику
// Семантика влияющая на изображение не удаляется
// Для удаления такой семантики первоначально измените либо удалите серии,
// использующие данную семантику
int _fastcall  rscDeleteSemantic(TRSCDATA * data,int code);

// Добавить семантику объекту eсли объект не из серии
// tуpe - тип семантики (из maptype.h SEMANTIC_FOR_OBJECT)
// возвращает ее последовательный номер
// в семантиках данного типа (начиная с 1)
int _fastcall  rscAppendObjectSemantic(TRSCDATA * data,int objincode,
                                       int semincode,int type,int seria);

// Удалить возможную либо обязательную семантику у объекта
// Если объект не из серии
// при нормальном завершении возвращает внутренний код объекта
int  _fastcall  rscDeletePosSemantic(TRSCDATA * data,int objincode,
                                     int semincode,int seria);

// Назначить семантику - дополнительной в семантиках на объект.
// Если объект не из серии
// Возвращает последовательный номер (с 1) в возможных семантиках
// если такой не было - возвращает 0
int _fastcall  rscSetTypePosSemantic(TRSCDATA * data,int objincode,
                                     int semincode,int seria);

// Назначить семантику - обязательной в семантиках на объект.
// Если объект не из серии
// Возвращает последовательный номер (с 1) в обязательных
// семантиках
// если такой не было - возвращает 0
int _fastcall  rscSetTypeMustSemantic(TRSCDATA * data,int objincode,
                                      int semincode,int seria);

//  Заполнить расширенную структуру описания семантической характе-
//  ристики по внешнему коду семантики и внутреннему коду объекта
//  semtype - адрес структуры, в которую будет помещено
//  описание характеристики,
//  code - код семантики,
//  objincode - внутренний код объекта.
//  При ошибке возвращает ноль                     
int _fastcall rscSemanticDescribeEx(TRSCDATA * data,RSCSEMANTICEX *semtypeex,
                                int code, int objincode);

// Записать новые умолчания на семантику (incodeobject=0 )
// или на объект
// возвращает указатель на исправленную семантику
TABSEM * _fastcall rscAppendDef(TRSCDATA * data,int incodeobject,
                   int semanticcode,
                   float objmin,float objdef,float objmax);

// Заменить умолчания на семантику - общие (objincode = 0)
// либо на объект
// Если требуемого умолчания не нашли - добавим новое
// возвращает указатель на исправленную семантику (ошибка - 0 )
TABSEM * _fastcall rscUpdateDef(TRSCDATA * data,int incodeobject,
                  int semanticcode, float objmin,float objdef,float objmax);

// Записать новую библиотеку
// name    - условное название библиотеки
// dllname - название DLL
// возвращает указатель на созданную библиотеку
// 0 - при ошибке
TABIML * _fastcall rscAppendLibrary(TRSCDATA * data,char * dllname,char * name);

// Записать новую библиотеку
// name    - условное название библиотеки
// dllname - название DLL
// возвращает код созданной библиотеки
// 0 - при ошибке
long int _fastcall rscCodeAppendLibrary(TRSCDATA * data,char * dllname,
                                                char * name);    

// Запрос количества библиотек
// 0 - при ошибке
int _fastcall rscGetImlCount(TRSCDATA * data);

// Запрос условного названия библиотеки по порядковому номеру (c 1)
// ' ' - при ошибке
char * _fastcall rscGetImlName(TRSCDATA * data,int number);

// Запись условного названия библиотеки по порядковому номеру (c 1)
// ' ' - при ошибке
char * _fastcall rscSetImlName(TRSCDATA * data,int number,char * name);

// Запрос имени библиотеки по порядковому номеру (c 1)
// ' ' - при ошибке
char * _fastcall rscGetImlNameDLL(TRSCDATA * data,int number);

// Запрос индекса библиотеки(с 1) по порядковому номеру    
// 0 - при ошибке
int  _fastcall rscGetImlIndex(TRSCDATA * data,int number);

// Запрос порядкового номера библиотеки(с 1) по коду
// 0 - при ошибке
int  _fastcall rscGetImlOrder(TRSCDATA * data,int code);

// Запрос кода по порядковому номеру библиотеки(c 1)         
 // 0 - при ошибке
int  _fastcall rscGetImlCode(TRSCDATA * data,int number);

// Запросить описание функций,
// поддерживаемых библиотекой по индексу
IMLLIST * _fastcall rscGetImageList(TRSCDATA * data,int index);

// Дополним параметры пользовательских объектов(IMG_LIBRARY)
void _fastcall rscSetUserObjectRefer(TRSCDATA * data);

// Сбросим индексы пользовательских объектов(IMG_LIBRARY)
void _fastcall rscBreakUserObjectRefer(TRSCDATA * data);

// Удалить библиотеку по коду           
int  _fastcall rscDeleteLibrary(TRSCDATA * data,int code);

// Запpосить количество связанных подписей объекта        
int _fastcall rscGetObjectRelateCount(TRSCDATA * data,int incode);

// Запpосить описание связанной подписи по внутреннему коду объекта и  
// по порядковому номеру связанной подписи (с 1)
// возвращает идентификатор подписи
// при ошибке возвращает 0
int _fastcall rscGetObjectRelateOrder(TRSCDATA * data,int incode,int order,
                                      RSCRELATION * relate);

// Запpосить описание связанной подписи объекта           
// по данной семантике
// при отсутствии таковой возвращает 0
int _fastcall rscGetObjectRelate(TRSCDATA * data,int incode,int semanticcode,
                                 RSCRELATION * relate);

// Обновить описание либо добавить описание связанной подписи  
// Возвращает идентификатор подписи  , либо 0
int _fastcall rscUpdateObjectRelate(TRSCDATA * data,int incode,int semanticcode,
                                     int ident,char * prefix,int decimal);

// Удалить связанные подписи объекта по идентификатору подписи        
// Возвращает количество удаленных связанных подписей
int _fastcall rscDeleteObjectRelateIdent(TRSCDATA * data,int incode,int ident);

// Удалить связанную подпись по указанной семантике                   
int _fastcall rscDeleteObjectRelate(TRSCDATA * data,int incode,int semanticcode);

// Удалить все связанные подписи ссылающиеся на данный объект         
// ident - идентификатор объекта
// Возвращает количество удаленных связанных подписей
int _fastcall rscDeleteObjectRelationText(TRSCDATA * data,int ident);

// Найти следующий объект после указанного имеющий связанную подпись  
// ссылающуюся на объект с данным идентификатором
// Возвращает возвращает внутренний код объекта.
// если таких больше нет 0
int _fastcall rscCheckRelation(TRSCDATA * data,int ident,int order);

// Установить имя палитры по номеру (с 1)                          
// Возвращает номер исправленной палитры
int _fastcall rscSetPaletteName(TRSCDATA * data,int number,char * name);

// Удалить палитру по номеру (c 1)(одна палитра не удаляется)       
int _fastcall rscDeletePalette(TRSCDATA * data,int number);

// Установить верхнюю границу видимости для подписей по указанному  
// масштабу (подпись видна (включая) следуюший масштаб в таблице масштабов
// Возвращает количество исправленных объектов
int _fastcall rscSetObjectView(TRSCDATA * data,unsigned long scale);

// Заменить символьное значение классификатора по номеру с 1       
// Возвращает номер или 0
int _fastcall rscUpdateClassificatorName(TRSCDATA * data,int semanticcode,
                                         int index,char * name);

// Установка - возврат типа кодов объектов, используемых в классификаторе 
// type 0 - код числовой, 1- в качестве кода, берется ключ(короткое имя объекта)
int _fastcall rscGetRscObjectCodeType(TRSCDATA * data);
int _fastcall rscSetRscObjectCodeType(TRSCDATA * data,int type);

// Удалить шрифт по ключу , если нужно переназначить шрифт во внешнем      
// виде объектов , newkey - ключ другого шрифта. Если newkey = 0,
// будет назначен шрифт по умолчанию.
int  _fastcall rscDeleteFont(TRSCDATA * data,int key,int newkey);

// Находит для классификатора семантики по строковому значению числовое
// Если не нашли возвращает 0                                             
int _fastcall  rscFindClassificatorCode(TRSCDATA * data,
                               unsigned long codesemantic, const char * string);

// Разобрать строку на узлы                                                
// 0 - ошибка
// 1 - значение вычислено
int _fastcall rscReadFormula(HRSC hrsc, HOBJ info, const char * formula,
                             long int * err, FORMNODE * node);

// Вычислить значение по узлам
// 0 - ошибка, 1 - значение вычислено
long CalcFormula(FORMNODE * node,long nodecount,double * value);

// Записать новую формулу - возвращает код формулы
// formula - символьная строка с текстом формулы,
// name    - название формулы
// type    - 0 (числовая формула)
// errcode - код ошибки при проверке формулы (maperr.rh)
// При ошибке 0
int _fastcall rscAppendFormula(TRSCDATA * data, const char * formula,
                               const char * name, long type, long * errcode);

// Заменить формулу - возвращает код формулы
// code    - код заменяемой формулы
// formula - символьная строка с текстом формулы,
// name    - название формулы
// type    - 0 (числовая формула)
// errcode - код ошибки при проверке формулы (maperr.rh)
// При ошибке 0
int _fastcall rscUpdateFormula(TRSCDATA * data, long code, const char * formula,
                               const char * name, long type, long * errcode);

// Запрос формулы по коду семантики
// Возвращает символьную строку с текстом формулы,
// При ошибке ' '
const char * _fastcall rscGetFormulaBySemanticCode(TRSCDATA * data, long code);

// Запрос формулы по коду формулы
// Возвращает символьную строку с текстом формулы,
// При ошибке возвращает ' '
const char * _fastcall rscGetFormulaByCode(TRSCDATA * data, long code);

// Запрос названия формулы по коду формулы
// Возвращает символьную строку с текстом формулы,
// При ошибке возвращает ' '
const char * _fastcall rscGetFormulaNameByCode(TRSCDATA * data, long code);

// Запрос формулы по порядковому номеру (с 1)
// Возвращает символьную строку с текстом формулы,
// При ошибке возвращает ' '
const char * _fastcall rscGetFormulaByNumber(TRSCDATA * data, long number);

// Запрос кода формулы по порядковому номеру (с 1)
// При ошибке возвращает 0
long _fastcall rscGetFormulaCodeByNumber(TRSCDATA * data, long number);

// Назначить семантике формулу для расчетов
// Возвращает код формулы или 0
long _fastcall rscSetFormulaToSemantic(TRSCDATA * data, long code,
                                                      long semanticcode );

// Удалить формулу для расчетов по коду формулы
// При ошибке возвращает 0
long _fastcall rscDeleteFormula(TRSCDATA * data, long code);

// Запрос количества формул
long _fastcall rscGetFormulaCount(TRSCDATA * data);


#ifndef HIDERSC3D                                               
// Добавить существующую библиотеку трехмерных параметров       
// name    - условное название библиотеки
// dllname - имя файла .p3d
// возвращает указатель на cозданную библиотеку
// 0 - при ошибке
TABL3D * _fastcall rscAppend3DLibrary(TRSCDATA * data,char * dllname,char * name);

// Записать новую библиотеку трехмерных параметров
// name    - условное название библиотеки
// dllname - имя файла .p3d
// возвращает указатель на cозданную библиотеку
// 0 - при ошибке
TABL3D * _fastcall rscNew3DLibrary(TRSCDATA * data,char * dllname,
                                  char * name);

// Запрос количества библиотек трехмерных параметров
// 0 - при ошибке
int _fastcall rscGet3DLibraryCount(TRSCDATA * data);

// Запрос порядкового номера библиотеки трехмерных параметров (с 1)
// по коду
// 0 - при ошибке
int  _fastcall rscGet3DLibraryOrder(TRSCDATA * data,int code);

// Запрос кода по порядковому номеру библиотеки 3D параметров (c 1)
// 0 - при ошибке
int  /*_fastcall */rscGet3DLibraryCode(TRSCDATA * data,int number);

// Запрос кода по имени библиотеки 3D параметров
// 0 - при ошибке
int  _fastcall rscGet3DLibraryCodeByName(TRSCDATA * data,const char * dllname);

// Запрос библиотеки трехмерных параметров по коду
// 0 - при ошибке
TABL3D *  _fastcall rscGet3DLibrary(TRSCDATA * data,int code);

// Запрос имени библиотеки трехмерных параметров по коду
// 0 - при ошибке
char *  _fastcall rscGet3DLibraryName(TRSCDATA * data,int code);

// Запрос имени файла библиотеки трехмерных параметров по коду
// 0 - при ошибке
char *  _fastcall rscGet3DLibraryFileName(TRSCDATA * data,int code);

// Запрос смещения библиотеки трехмерных параметров по коду
// 0 - при ошибке
long _fastcall rscGet3DLibraryOffset(TRSCDATA * data,int code);

// Удалить библиотеку трехмерных параметров по коду
int  _fastcall rscDelete3DLibrary(TRSCDATA * data,int code);

// Инициализировать 3D графику
// 0 - при ошибке
int _fastcall rscInit3D(TRSCDATA * data);

// Проверка и считывание p3D файлов в память
// Настройка таблицы записей адресу библиотеки
// 0 - при ошибке
// 2 - файл уже в памяти
int _fastcall rscInitp3DFile(TRSCDATA * data,TABL3D * ald);

// Согласовать ссылки на параметры с таблицей записей
// 0 - при ошибке
int _fastcall rscAdjustRecordWithParam(TRSCDATA * data);

// Согласовать ссылки на текстуры для библиотеки
// с порядковым номером number (с 1) с таблицей записей
// 0 - при ошибке
int _fastcall rscAdjustRecordWithTexture(TRSCDATA * data,int number);

// Запрос таблицы 3D параметров объекта по уровню (0,1,2 - где 0 - ближний)
// и порядковому номеру (индексу ) объекта с 1
// При отсутствии нужного - выдаются параметры с меньшим уровнем
// при ошибке или отсутствии 0
TABP3D * /*_fastcall*/ rscGet3DObject(TRSCDATA * data,long incode,long level);

// Запрос существования 3D параметров объекта по уровню (0,1,2 - где 0 - ближний)
// и порядковому номеру (индексу ) объекта с 1
// при ошибке или отсутствии 0
long _fastcall rscIs3DParam(TRSCDATA * data,long incode,long level);   

// Запрос длины параметров объекта по уровню (0,1,2 - где 0 - ближний)
// и порядковому номеру (индексу ) объекта с 1
// при ошибке или отсутствии 0
long _fastcall rscGet3DLength(TRSCDATA * data,long incode,long level);

// Запрос функции отображения параметров объекта по уровню (0,1,2 - где 0 - ближний)
// и порядковому номеру (индексу ) объекта с 1
// при ошибке или отсутствии 0
long _fastcall rscGet3DFunction(TRSCDATA * data,long incode,long level);

// Запрос ключа отображения параметров объекта
// по уровню (0,1,2 - где 0 - ближний)
// и порядковому номеру (индексу ) объекта с 1
// при ошибке или отсутствии 0
long _fastcall rscGet3DObjectKey(TRSCDATA * data,long incode,long level);

// Запрос кода библиотеки отображения параметров объекта
// по уровню (0,1,2 - где 0 - ближний)
// и порядковому номеру (индексу ) объекта с 1
// при ошибке или отсутствии 0
long _fastcall rscGet3DObjectLibraryCode(TRSCDATA * data,long incode,long level);

// Запрос функции отображения параметров объекта по уровню (0,1,2 - где 0 - ближний)
// и порядковому номеру (индексу ) объекта с 1
// при ошибке или отсутствии 0
F3DTREE * /*_fastcall*/ rscGet3DParam(TRSCDATA * data,long incode,long level);

// Связать объект по уровню (0,1,2 - где 0 - ближний)
// и порядковому номеру (индексу ) объекта с 1
// с изображением по коду библиотеки и ключу объекта
// при ошибке 0
long /*_fastcall*/ rscSet3DImageToObject(TRSCDATA * data, long incode, long level,
                                     long code, long key);

// Запрос параметров 3D изображения
// и коду библиотеки и ключу изображения
// при ошибке или отсутствии 0
// иначе указатель параметров иображения F3DTREE
F3DTREE * /*_fastcall*/ rscGet3DImageParam(TRSCDATA * data,long code,long key);

// Установить параметры 3D изображения
// по коду библиотеки,ключу,номеру функции,типу метрики,
// длине параметров и параметрам
// при ошибке или отсутствии 0
long _fastcall rscSet3DImageParam(TRSCDATA * data,long code,long key,
                                  long type,long length,char * param);

// Заменить название 3D изображения
// по коду библиотеки,ключу
// при ошибке или отсутствии 0
long _fastcall rscSet3DImageName(TRSCDATA * data,long code,long key,
                                  char * name);

// Создать параметры 3D изображения
// по коду библиотеки,типу метрики,условному названию,
// длине параметров и параметрам (типа P3DTREE)
// при ошибке или отсутствии 0 , иначе код изображения
long /*_fastcall*/ rscCreate3DImage(TRSCDATA * data,long code,long type,
                                long length,char * param,char * name);

// Создать умалчиваемый шаблон                                        
// по коду библиотеки
// при ошибке возвращает 0, если был - 1 иначе 2
long rscCreate3DDefaultImage(TRSCDATA * data,long code);

// Запросить общее количество записей укаанного типа в библиотеке
// (OBJECT_PARAMETERS,OBJECT_TEXTURE ...  rscfl3d.h)
// при ошибке 0.
long _fastcall rscTakeRecordCount(TRSCDATA * data,long code,long type);

// Запросить заголовок записи указанного типа по коду
// При ошибке 0.
RECHEAD * _fastcall rscTakeCodeRecordHead(TRSCDATA * data,long code);

// Запросить заголовок записи по коду библиотеки и ключу            
// при ошибке или отсутствии 0
RECHEAD * _fastcall rscTakeKeyRecordHead(TRSCDATA * data,long code,long key);

// Запросить указатель на заголовок записи указанного типа по порядковому номеру
// в библиотеке c данным кодом
// ( тип - OBJECT_PARAMETERS,OBJECT_TEXTURE ...  rscfl3d.h)
// Вовращает код записи, при ошибке 0.
long _fastcall rscTakeRecordHead(TRSCDATA * data,long number,long code,long type,
                                           RECHEAD * address);

// Запросить общее количество текстур
// при ошибке 0.
long _fastcall rscTakeTextureCount(TRSCDATA * data);

// Запросить адрес текстуры по порядковому номеру
// При ошибке 0.
RECTEXTURE * /*_fastcall*/ rscTakeTexture(TRSCDATA * data,long number);

// Создать запись текстуры
// по коду библиотеки,условному названию,
// при ошибке или отсутствии 0 , иначе код текстуры
long /*_fastcall*/ rscCreate3DTexture(TRSCDATA * data,long code,
                                 RECTEXTURE * texture,char * name);
// Заменить запись текстуры
// по коду библиотеки,ключу текстуры,условному названию,
// при ошибке или отсутствии 0 , иначе код текстуры
long _fastcall rscReplace3DTexture(TRSCDATA * data,long libcode,long key,
                                   RECTEXTURE * texture,char * name);
                                                                 
// Удалить запись текстуры
// по коду библиотеки,ключу текстуры
// при ошибке или отсутствии 0
long _fastcall rscDelete3DTexture(TRSCDATA * data,long libcode,long key);

// Запросить использование текстуры                              
// по коду библиотеки,ключу текстуры
// Возвращает количество объектов, использующих данную текстуру
// при ошибке или отсутствии 0
long _fastcall rscUsed3DTexture(TRSCDATA * data,long libcode,long key);

// Запросить свободный ключ записи библиотеки
// по коду библиотеки и типу записи
// вовращает ключ, при ошибке 0.
long _fastcall rscTakeFreeKey(TRSCDATA * data,long code,long type);

// Убрать 3D изображение объекта по уровню (0,1,2 - где 0 - ближний)
// и порядковому номеру (индексу ) объекта с 1
// при ошибке 0                                                     

long _fastcall rscDelete3DImageFromObject(TRSCDATA * data, long incode,
                                          long level);

// Запросить адрес параметров материала по номеру в таблице записей
// При ошибке 0.
ACT3DMATERIALMODE * _fastcall rscTakeMaterial(TRSCDATA * data,long number);     

// Заменить параметры материала по коду библиотеки и ключу
// При ошибке 0, иначе код текстуры
long _fastcall rscReplaceMaterial(TRSCDATA * data,long libcode,long key,
                          ACT3DMATERIALMODE * material);           

// Удалить параметры материала по коду библиотеки и ключу
// При ошибке 0, иначе код текстуры
long _fastcall rscDeleteMaterial(TRSCDATA * data,long libcode,long key); 

// Заменить название материала по коду библиотеки и ключу
// (название уникально для данной библиотеки)
// При ошибке 0
long _fastcall rscReplaceMaterialName(TRSCDATA * data,long libcode,long key,
                          char * name);                              

// Создать запись материала по коду библиотеки, параметрам материала и
// названию (название уникально для данной библиотеки)
// При ошибке 0 иначе ключ записи
long _fastcall rscCreateMaterial(TRSCDATA * data,long libcode,    
                                    ACT3DMATERIALMODE * material,char * name);

#endif  // HIDERSC3D

#endif

