
#if !defined(MAPDEF_H)
#define MAPDEF_H

#ifndef MAPRSC_H
  #include "maprsc.h"    // КЛАССИФИКАТОР РАЙОНА РАБОТ
#endif

#ifndef MAPREGIS_H
  #include "mapregis.h"  // ФОРМУЛЯР ЭЛЕКТРОННОЙ КАРТЫ (ЭК)
#endif

#ifndef MAPLST_H
  #include "maplst.h"    // ЛИСТ РАЙОНА РАБОТ (ЛИСТ ЭК)
#endif

#ifndef MAPTRANS_H
  #include "maptrans.h"
#endif

#ifndef MAPERROR_H
  #include "maperror.h"  // ОБРАБОТКА ОШИБОК ВЫПОЛНЕНИЯ
#endif

#ifndef MAPTRACT_H
  #include "maptract.h"
#endif

#ifndef MAPGDX_H
  #include "mapgdx.h"
#endif

#ifndef MAPSELLS_H
  #include "mapsells.h"
#endif

#ifndef HIDESHOW
#ifndef MAPCOLOR_H
  #include "mapcolor.h"
#endif
#endif

#ifndef MAPMETR_H
 #include "mapmetr.h"          
#endif

// Преобразование строки из DOS в WINDOWS
char * _DLLCLASS Dos2Win(char * Text,int length);

// Преобразование строки из WINDOWS в DOS
char * _DLLCLASS Win2Dos(char * Text,int length);

// Преобразование строки из DOS в KOI8
char * _DLLCLASS Win2Koi8(char * Text,int length);

// Преобразование строки из KOI8 в DOS
char * _DLLCLASS Koi82Win(char * Text,int length);

#define Degree8Dec (100000000L)   // 10 ** 8

// Идентификаторы служебных файлов
#define LABEL_DSK 0x004B5344L  // DSK0
#define LABEL_CFG 0x00474643L  // CFG0
#define LABEL_MAK 0x004B414DL  // MAK0
#define LABEL_MSK 0x004B534DL  // MSK0

class TMapSelect;

// Точность хранения координат
enum PRECISIONFLAG                                      
{
  PF_FLOAT = 0, PF_DOUBLE = 1, PF_METRE = 2
};

enum PRECISIONTYPE                                       
{
  PT_MAXIMUM = 1, PT_CENTIMETERS = 2, PT_MILLIMETERS = 3
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++   ЭЛЕКТРОННАЯ ВЕКТОРНАЯ КАРТА  +++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TMap : public TMapMetricMemory
{
 public :

 // Открыть паспорт района,проверить и заполнить
 TMap();

 public :

 // Закрыть паспорт
 ~TMap();


 /*********************************************************
 *                                                        *
 *     ФУНКЦИИ ДОСТУПА К ДАННЫМ РАЙОНА/ЛИСТА              *
 *                                                        *
 *********************************************************/

 // Добавить листы из другого района работ в данный
 // map - добавляемый район,
 // handle - идентификатор окна,которое будет извещаться
 // о ходе процесса (IMM_LIST - 0x586)
 // При ошибке возвращает ноль
 int Append(TMap * map,HWND handle);

 //  Добавить листы из другого района работ с преобразованием координат
 //  map - добавляемый район,
 //  handle - идентификатор окна,которое будет извещаться
 //  о ходе процесса
 //  При ошибке возвращает ноль

 int AppendAndChange(TMap * map, HWND handle);      

 // Создать "пустой" район работ
 // При ошибке возвращает ноль
 int CreateData(const char * mapname,
                const	char * rscname,
                TMapRegister * mapreg);
 int CreateDataEx(const char * mapname,    
                const	char * rscname,
                MAPREGISTEREX * mapreg,
                LISTREGISTER * listreg);

 int Create(const char * mapname,
            const	char * rscname,
            TMapRegister * mapreg)
    { return CreateData(mapname,rscname,mapreg); }
 int CreateEx(const char * mapname,         
            const	char * rscname,
            MAPREGISTEREX * mapreg,
            LISTREGISTER * listreg)
    { return CreateDataEx(mapname,rscname,mapreg,listreg); }

 // Создать временный район работ (пользовательскую карту)
 // Имена файлов уникальные,
 // располагаются в рабочей директории системы
 // При закрытии района файлы удаляются автоматически
 // При ошибке возвращает ноль
 int CreateTempMap(const	char * rscname);

 // Удалить все объекты листа                      
 // При ошибке возвращает ноль
 int ClearList(int number)
    { return List.ClearList(this, number); }

 // Закрыть район работ
 void CloseData();
 void Close() { CloseData(); }

 // Запросить ресуры карты (классификатор)
 // При ошибке возвращает ноль
 TMapRsc * GetResource()
    {
      if (Rsc.IsActive()) return &Rsc;
      return 0;
    }

 // Запросить имя файла журнала района работ
 const char * GetLogName() { return MapError.NameLOG(); }

 // Запросить имя файла паспорта карты
 const char * GetMapName() { return Name_MAP; }

 // Запросить имя файла классификатора
 const char * GetRscName() { return Rsc.RscName; } 

 // Запросить полное имя пути файла ресурсов карты
 // name - место для размещения имени
 // size - размер выделенной области (рекомендуется MAX_PATH)
 // При успешном выполнении возвращает адрес входной строки
 // При ошибке возвращает адрес пустой строки
 char * GetRscFileName(char * name, int size);

 const char * GetRscFileName() { return Rsc.GetRscName(); }  

 // Запросить имя классификатор карты по имени карты   
 // name    - имя файла паспорта карты (MAP,SIT)
 // rscname - имя файла RSC
 // size    - размер буфера для размещения имени RSC
 // При ошибке возвращает ноль

 intptr_t GetRscNameByName(const char * name, char * rscname, int size);

 // Открыть район работ
 // При ошибке возвращает ноль
 int OpenData(const char * map,int mode  = 0);
 int Open(const char * map,int mode  = 0)
    { return OpenData(map,mode); }

 // Загрузить карту старой версии (ver. 4.5)
 // Открыть район работ
 // При ошибке возвращает ноль
 int LoadOldVersionData(const char * map);

 // Отменить последнюю транзакцию
 // flag - условия выбора последней транзакции:
 // LOG_ANYACTION(0) - нет условий, LOG_MYACTION(1) - обрабатывать последнюю
 // свою транзакцию (пропускать транзакции других пользователей)
 // Если после транзакции выполнялась сортировка карты
 // или журнал пуст - возвращает ноль
 // При ошибке возвращает ноль,
 // иначе - количество восстановленных операций
 int AbolitionLastAction(int flag = LOG_MYACTION);

 // Открыть транзакцию
 // type - тип транзакции (от 0x4000 до 0х0FFFF - за Панорамой)
 // При ошибке возвращает ноль
 int CreateAction(int type);

 // Закрыть запись транзакции
 void CommitAction(int longaction = 0);

 // Преобразовать пользовательскую карту в проекцию карты местности
 // При ошибке возвращает ноль
 int TransformByMap(TMap * map);

 // Запросить паспортные данные векторной карты
 // по имени файла - паспорта карты (MAP,SIT)
 // Структуры MAPREGISTEREX и LISTREGISTER описаны в mapcreat.h
 // sheetnumber - номер листа карты для
 // которого запрашиваются паспортные данные
 // При ошибке возвращает ноль

 int GetMapInfoByName(const char * name,
                      int sheetnumber,
                      TMapRegister * mapregister);

 // Установить связь с ресурсами родителя

 void SetParent(HSITE hsite, TMapMetricMemory * memory)
 {
   hSite        = hsite;
   ParentMemory = memory;
 }

 // Выделить память под пересчет координат

 int AllocateBorderMemory();

 /*********************************************************
 *                                                        *
 *     ЗАПРОС ДАННЫХ ПО ОБ'КТАМ ТЕКУЩЕГО ЛИСТА           *
 *                                                        *
 **********************************************************
 *                                                        *
 *         Листы и объекты нумеруются с единицы !!!       *
 *                                                        *
 *********************************************************/

public :

 // Запросить адрес данных текущего листа по смещению
 // При ошибке возвращается ноль
 OBJECTDATA * GetData(long offset) {return(GetDataAddr(offset));}
 OBJECTDATA * GetDataAddr(long offset)
      { return (List.DataAddr(offset)); }

 // Запросить адрес данных текущего листа по описанию объекта
 // При ошибке возвращается ноль
 OBJECTDATA * GetObjectMetric(TObjectDesc desc) { return(GetDataAddr(desc));}
 OBJECTDATA * GetData(TObjectDesc desc) {return(GetDataAddr(desc));}
 OBJECTDATA * GetDataAddr(TObjectDesc desc)
      {
       if ((desc != 0) && (desc.Metric() != 0))
         return List.DataAddr(desc.Metric());
       else
         return 0;
      }

#ifndef TINYDATA
 // Запросить адрес графического описания по смещению
 // При ошибке возвращается ноль
 IMGDRAW * GetDraw(long offset) {return(GetDrawAddr(offset));}
 IMGDRAW * GetDrawAddr(long offset)
      { return (List.DrawAddr(offset)); }

 // Запросить адрес графического описания по описанию объекта
 // При ошибке возвращается ноль
 IMGDRAW * GetObjectGraphic(TObjectDesc desc) {return(GetDrawAddr(desc));}
 IMGDRAW * GetDraw(TObjectDesc desc) {return(GetDrawAddr(desc));}
 IMGDRAW * GetDrawAddr(TObjectDesc desc)
      {
       if ((desc != 0) && (desc.Graphic() != 0))
         return List.DrawAddr(desc.Graphic());
       else
         return 0;
      }
#endif

 // Запросить объект рамки текущего листа карты
 // Если рамка найдена - текущий объект описывает рамку
 // Если рамки нет, то возвращается 0
 TObjectHead * GetFrameDesc();

/*
 // Запросить номер текущего объекта в текущем листе
 // При ошибке возвращается ноль
 int GetCurrentObjectNumber() { return GetCurrObjectNumber(); }
 int GetCurrObjectNumber()
      { return (List.Object); }
*/

 // Запросить первый (логически) объект текущего листа
 // Текущим в листе становится запрошенный объект
 // При ошибке возвращается ноль
 TObjectHead * GetFirstObject()
      { return List.FirstHead(); }
 int GetFirstObjectNumber()
      { return List.FirstNumber(); }

 // Запросить последний (логически) объект текущего листа
 // Текущим в листе становится запрошенный объект
 // При ошибке возвращается ноль
 TObjectHead * GetLastObject()
      { return List.LastHead(); }
 int GetLastObjectNumber()
      { return List.LastNumber(); }

 // Запросить объект текущего листа по номеру
 // Текущим в листе становится объект "Number"
 // При ошибке возвращается ноль
 TObjectHead * GetObject(int number)
      { return (List.ObjectDesc(number)); }

 // Запросить количество объектов в текущем листе
 // При ошибке возвращается ноль
 int GetObjectCount()
      { return (List.Count()); }

 // Запросить адрес семантики объекта по смещению
 // При ошибке возвращается ноль
 SEMANTIC * GetObjectSemantic(TObjectDesc desc) {return (GetSemnAddr(desc));}
 SEMANTIC * GetObjectSemantic(long offset) {return(GetSemnAddr(offset));}
 SEMANTIC * GetSemn(long offset) {return(GetSemnAddr(offset));}
 SEMANTIC * GetSemnAddr(long offset)
      { return (List.SemnAddr(offset)); }

 // Запросить адрес семантики объекта по описанию объекта
 // При ошибке возвращается ноль
 SEMANTIC * GetSemn(TObjectDesc desc) {return(GetSemnAddr(desc));}
#ifndef TINYDATA
 SEMANTIC * GetSemnAddr(TObjectDesc desc)
      {
       if ((desc != 0) && (desc.Semantic() != 0))
         return List.SemnAddr(desc.Semantic());
       else
         return 0;
      }
#else
 SEMANTIC * GetSemnAddr(TObjectDesc desc);
#endif

 /*********************************************************
 *                                                        *
 *     ЗАПРОС ХАРАКТЕРИСТИК ТЕКУЩЕГО ЛИСТА / РАЙОНА       *
 *                                                        *
 *********************************************************/

 // Проверить попадание листа в "окно"
 // Координаты окна заданы в дискретах
 // Если лист попадает - возвращается TRUE
 int CheckFrame(int list,DFRAME * frame);

 // Запросить номер текущего листа
 // При ошибке возвращается ноль
 // Листы и объекты нумеруются с единицы !!!
 int GetCurrentListNumber() { return GetCurrListNumber(); }
 int GetCurrListNumber()
      { return (List.List); }

 // Запросить количество листов в районе
 // При ошибке возвращается ноль
 int GetListCount()
      { return (Count()); }

 // Запросить имя (номенклатуру) листа по номеру
 // По умолчанию возвращается имя текущего листа
 // При ошибке возвращается ноль
 const char * GetListName(int list)
      { return (ListName(list)); }

 const char * GetListName()
      { return (ListName(List.List)); }

 // Запросить номер листа по номенклатуре                       
 // При ошибке возвращается ноль
 int _fastcall SeekListByName(const char * name);

 // Поиск объекта по уникальному номеру в заданном листе карты
 // При ошибке возвращается ноль                                
 int _fastcall SeekObjectInList(int list, long key, int flag = 0);

 // Запросить число объектов в заданном листе
 // При ошибке возвращается ноль
 int GetObjectCount(int list);

 // Запрос соответствия рамки листа паспортным данным текущего листа.
 // Необходимо для выставления флага соответсвия проекции
 // Если данные не соответсвуют проекции, то возвращает 0, иначе 1
 int GetAccordingProjection();

 /*********************************************************
 *                                                        *
 *     ПРЕОБРАЗОВАНИЕ КООРДИНАТ В РАЙОНЕ РАБОТ            *
 *                                                        *
 *********************************************************/

 // Преобразовать из системы района в прямоугольную систему
 // Из дискрет в дециметры
 double Dis2DMetX(long   disX)
     { return ((MapX + MetInDis * (double)disX)*10.0); }

 double Dis2DMetY(long   disY)
     { return ((MapY + MetInDis * (double)disY)*10.0); }

 // Из дискрет в метры
 long   Dis2MetX (long   disX)
     { return (long)(MapX + MetInDis * (double)disX + 0.5); }

 long   Dis2MetY (long   disY)
     { return (long)(MapY + MetInDis * (double)disY + 0.5); }

 // Из дискрет в метры
 double Dis2MetX (double disX)
     { return (MapX + MetInDis * disX); }

 double Dis2MetY (double disY)
     { return (MapY + MetInDis * disY); }

 // Преобразовать из прямоугольной системы в систему района
 // Из дециметров в дискреты
 long   DMet2DisX(double dMetX)
     { return (long)((dMetX/10.0 - MapX)/MetInDis + 0.5); }

 long   DMet2DisY(double dMetY)
     { return (long)((dMetY/10.0 - MapY)/MetInDis + 0.5); }

 // Из метров в дискреты
 long   Met2DisX (long   metX)
     { return (long)(((double)metX - MapX)/MetInDis + 0.5); }

 long   Met2DisY (long   metY)
     { return (long)(((double)metY - MapY)/MetInDis + 0.5); }

 // Из метров в дискреты
 double Met2DisX (double metX)
     { return ((metX - MapX)/MetInDis); }

 double Met2DisY (double metY)
     { return ((metY - MapY)/MetInDis); }

 // Преобразование линейных характеристик из дискрет в метры
 double Dis2MetLine (double dis)
     { return MetInDis * dis; }

 // Преобразование линейных характеристик из метров в дискреты

 double Met2DisLine (double met)
     { return met/MetInDis; }

 // Преобразование площадных характеристик из дискрет в метры
 double Dis2MetSquare (double dis)
     { return MetInDis * MetInDis * dis; }


 /***************************************************************
 *                                                              *
 *      Запрос / установка доступа к файлу паспорта             *
 *                                                              *
 ***************************************************************/

 // Запрос и установка режима доступа
 int AccessMode(int mode)
    {
       FileAccess = (mode & (GENERIC_READ|GENERIC_WRITE));
       if (FileAccess == 0)
         FileAccess = GENERIC_READ|GENERIC_WRITE;
       return FileAccess;
    }

 int AccessMode()
     { return FileAccess; }


 // Запрос и установка числа листов в районе
 int Count();

 // Запросить код ошибки последней операции
 int Error() { return MapError.LastError; }

 // Проверка доступности данных
 int IsActive()
    { return ((File_MAP != 0) && (GetListCount() != 0)); }

 // Запросить - редактировались ли паспортные данные ?
 int IsDirty() { return Isdirty; }

 // Определение/установка флага возможности расчета геодезических координат
 int IsGeo() { return GeoAvailableFlag;}
 int IsGeo(int set) { return GeoAvailableFlag = set;}

 // Проверить - карта открыта ?
 // Если карта закрыта возвращает ноль
 int IsOpen()
    { return (File() != 0); }

 // Наличие реальных координат в метрике объектов и тип карты - SIT
 // (0 - условная метрика - дискреты)
 int IsRealPlace();

 // Наличие реальных координат в метрике объектов (метры) для любой карты
 int IsRealMetric()                                      
 {
   return ((PspId.Data.FlagRealPlace != 0) || (PspId.PrecisionFlag == PF_METRE));
 }

 // Запрос - можно ли редактировать паспорт ?
 int IsWrite()                                      
 { return (IsActive() && (AccessMode() & GENERIC_WRITE) && Edit); }

 // Количество метров в одном дискрете
 // на местности (в прямоугольн.системе)
 double MetersInDis() { return MetInDis; }

 // Запрос пути доступа к паспорту (без имени файла)
 char * PathMAP() { return Path_MAP; }

 // Запрос пути доступа к журналу и служебным файлам
 char * PathLOG() { return Path_LOG; }

 // Запрос идентификатора файла паспорта (см.::CreateFile(...) )
 // Если файл не открыт, идентификатор равен 0
 HANDLE File() { return (File_MAP); }

 // Проверить соответсвие данных в памяти и на диске
 // При несоответствии возвращает ноль
 int CheckMode();

 // Установить адрес функции оповещения о редактировании
 // карты
 int SetChangeCall(CHANGECALL call, long int parm);

 // Запрос и установка режима доступа
 int ShareMode(int mode)  { return FileShare = mode;   }

 int ShareMode() { return FileShare; }

 // Отметить редактирование данных в паспорте района
 // Возвращает номер очередного состояния данных
 int UpdateMode();

 // Запрос режима обработки данных
 // (0 - скоростной, 1 - надежный)
 int WorkMode() { return ( Mode_Work ); }

 // Записать сообщение в журнал
 // message - адрес строки сообщения
 // type    - тип сообщения (см. MESSAGETYPE)
 // При ошибке возвращает ноль
 int WriteToLog(const char * message,int type);

 /***************************************************************
 *                                                              *
 *      Обработка листов карты                                  *
 *                                                              *
 ***************************************************************/

public :

 // Привести данные района в соответсвие с их состоянием на диске
 // При ошибке возвращает ноль
 int AdjustData();

 // Добавить лист в район
 // srcmap - карта,содержащая добавляемый лист
 // list - добавляемый лист
 // Добавляемые данные должны быть той же проекции,
 // системы координат и масштаба, что и в районе работ
 // При ошибке возвращает ноль
 // При неудачной попытке район может оказаться закрытым !
 int AppendList(TMap * srcmap,int list,int save);

 // Добавить лист в район с преобразованием координат объектов
 // srcmap - карта,содержащая добавляемый лист
 // list - добавляемый лист
 // prefix - приставка к новому имени листа
 // При ошибке возвращает ноль

 int AppendListAndChange(TMap * srcmap, int list, char* prefix, int save,
                         HWND handle = 0);

 // Сохранить обновленные паспортные данные в файле
 // При ошибке возвращает ноль
 int Commit() { return Save(TRUE); }

 // Создать в районе новый лист (лист становится последним)
 // save    - признак немедленного обновления файла
 // mapreg  - формуляр создаваемого листа
 // При ошибке возвращает ноль
 // При неудачной попытке район может оказаться закрытым !
 int CreateList(LISTREGISTER * mapreg, int save = 1);        

 // Удалить из района лист
 // save    - признак немедленного обновления файла
 // При ошибке возвращает ноль
 // При неудачной попытке район может оказаться закрытым !
 int DeleteList(int list,int save = FALSE);

 // Открыть заданный лист c номером Number
 // Текущим становится лист "number"
 // При ошибке возвращает ноль
 int OpenList(int number);

 // Открыть заданный лист, если он не открыт
 // Текущим становится лист "number"
 // При ошибке возвращает ноль
 int IsOpenList(int number);

 // Выделить под лист максимальную область памяти
 // При ошибке возвращает ноль
 int AllocateNotLimit(int number);

 // Установка параметров паспорта из области MapRegister
 // При ошибке возвращает ноль
 int MapRegister(MAPREGISTEREX * mapreg);

 // Установка MapRegister для заданного листа
 int ListToRegister(TMapRegister * mapreg, int list);

 // Установка параметров MapRegister по текущему листу
 // При ошибке возвращает ноль
 int ListToRegister(MAPREGISTEREX * mapreg,
                    LISTREGISTER * listreg, int list);

 // Восстановить состояние паспортных данных
 // на момент последнего сохранения в файле
 // При ошибке возвращает ноль
 int Revert();

 // Сохранить изменения в паспорте
 // При ошибке возвращает ноль
 int Save(int force = FALSE);

 // Установка режима обработки данных
 // (0 - скоростной, 1 - надежный)
 int WorkMode(int mode);

 // Занять лист
 void LockList() { List.LockList(); }

 // Освободить лист
 void UnLockList() { List.UnLockList(); }

 // Привязать систему района к прямоугольной системе
 void SetNullPoint();

 // Копировать карту в поддиректорию
 // newname - путь к новому имени карты
 // При ошибке параметров возвращает ноль
 int CopyMap(const char * newname);

 // Удаление района работ
 // name - имя района
 // При ошибке возвращает ноль
 int DeleteMap();

protected :

 // Открыть паспорт района,проверить и заполнить
 // При ошибке возвращает ноль
 int OpenMap(const char * map, int mode = 0);

 // Создать новый паспорт
 // При ошибке возвращает ноль, код ошибки в Error()
 int CreateMap(const char * map,TMapRegister * mapreg,TMapRsc * maprsc);

 /***************************************************************
 *                                                              *
 *      Запросы / установка данных о проекции карты             *
 *                                                              *
 ***************************************************************/

public :

 // Запрос и установка осевого меридиана проекции карты
 // Измеряется в радианах !
 double AxisMeridian(double meridian);
 double AxisMeridian();

 // Запрос/установка признака наличия данных о проекции
 int DataProjection();
 int DataProjection(int datpro);

 // Запрос и установка вида эллипсоида
 int EllipsoideKind(int kind);
 int EllipsoideKind();


 // Запрос и установка первой главной параллели
 // Измеряется в радианах !
 double FirstMainParallel(double parallel);
 double FirstMainParallel();

 // Широта главной точки проекции
 // Измеряется в радианах !
 double MainPointParallel(double parallel);
 double MainPointParallel();

 // Широта полюса проекции                 
 // Измеряется в радианах !
 double PoleLatitude(double parallel);
 double PoleLatitude();

 // Долгота полюса проекции
 // Измеряется в радианах !
 double PoleLongitude(double parallel);
 double PoleLongitude();

 // Запрос и установка проекции исходного материала
 int MaterialProjection();
 int MaterialProjection(int value)
 {
   return (PspId.Data.MaterialProjection = value);
 }

 // Запрос и установка второй главной параллели
 // Измеряется в радианах !
 double SecondMainParallel(double parallel);
 double SecondMainParallel();

 // Запрос и установка флага состояния проекции
 int ProjectionFlag(int flag);
 int ProjectionFlag ();

 // Запрос большой полуоси эллипсоида
 // При ошибке возвращается ноль
 double BigAxis();

 // Запрос эксцентриситета эллипсоида
 // При ошибке возвращается ноль
 double Eccentricity();

 // Установить проекцию и справочные данные по проекции
 // исходного материала
 void SetDataProjection();

 // Возврат вида эллипсоида
 int GetEllipsoid()
 {
   return Translate.GetEllipsoid();
 }

 // Запросить номер зоны для топографических карт
 int GetNumberZone()
 {
   return Translate.GetNumberZone();
 }

 int ZoneNumber() { return GetNumberZone(); }

 // Определение геодезических координат B и L по прямоугольным X и Y
 // Входные данные:
 //        x,y  -  прямоугольные координаты точки в метрах
 // Выходные данные:
 //        B,L  -  широта и долгота точки в радианах
 void XY2BL(double x, double y, double * B, double * L)
 {
   Translate.XY2BL(x, y, B, L);
 }

 // Определение прямоугольных координат X и Y по геодезическим B и L
 // Входные данные:
 //        B,L  -  геодезические координаты точки в радианах
 // Выходные данные:
 //        x,y  -  прямоугольные координаты точки в метрах
 void BL2XY(double B, double L, double *x, double *y)
 {
   Translate.BL2XY(B, L, x, y);
 }

 // ************************************************************
 //                                                            *
 //       ЗАПРОС И УСТАНОВКА ГАБАРИТОВ РАЙОНА (ДЕЦИМЕТРЫ)      *
 //                                                            *
 // ************************************************************

 double X1(double x);
 double X1();

 double Y1(double y);
 double Y1();

 double X2(double x);
 double X2();

 double Y2(double y);
 double Y2();

 /***************************************************************
 *                                                              *
 *      Запрос прямоугольных координат габаритов листа          *
 *          Прямоугольные координаты в метрах                   *
 *                                                              *
 ***************************************************************/

 double XL1m(int list)
 {
   if (LstId == 0) return 0;
   return ((LstId+list-1)->XMin);
 }

 double YL1m(int list)
 {
   if (LstId == 0) return 0;
   return ((LstId+list-1)->YMin);
 }

 double XL2m(int list)
 {
   if (LstId == 0) return 0;
   return ((LstId+list-1)->XMax);
 }

 double YL2m(int list)
 {
   if (LstId == 0) return 0;
   return ((LstId+list-1)->YMax);
 }

 // Запрос габаритов листа в дискретах !!!
 // При ошибке возвращает ноль
 // list - номер листа,  1 <= list <= Count()
 DFRAME * ListFrame(int list);

 // Запрос позиции точки отображения листа в районе в дискретах
 // При ошибке возвращает ноль
 DOUBLEPOINT * ViewPosition(int list);
 DOUBLEPOINT * ViewPosition()
   { return ViewPosition(List.Number()); }

 /***************************************************************
 *                                                              *
 *      Запросы / установка данных о листах карты               *
 *                                                              *
 ***************************************************************/

 // Запрос - порядок обработки листов установлен ?
 // Если да - листы будут отображаться в порядке
 // их описания в паспорте (порядок номеров),
 // иначе - в произвольном порядке
 int IsOrder();

 // Установка порядка обработки листов
 int IsOrder(int order);

 // Запрос и установка имени листа
 // возврат - имя листа, при ошибке - 0
 const char * SheetName(int list);
 const char * SheetName(const char * name,int list);

 // Запрос и установка номенклатуры листа
 // При ошибке возвращается ноль
 const char * Nomenclature(int list);
 const char * Nomenclature(const char * name,int list);

 const char * ListName(int list = 1) { return Nomenclature(list); }
 const char * ListName(const char * name,int list)
  { return Nomenclature(name,list); }

 // Запросить габариты заданного листа в районе
 // Возвращается указатель на координаты листа
 // в районе в дискретах
 // По умолчанию берется текущий лист
 // При ошибке возвращается ноль
 DFRAME * GetListFrame(int list)
  {  return ListFrame(list); }

 // Запросить номер объекта - рамки листа
 // По умолчанию берется текущий лист
 // При ошибке возвращается ноль
 int GetListFrameNumber(int list);

 int GetListFrameNumber()
  {
    return GetListFrameNumber(List.Number());
  }

 /***************************************************************
 *                                                              *
 *  Запросы / установка данных о системе координат и масштабе   *
 *                                                              *
 ***************************************************************/

public :

 // Запрос и установка системы координат
 int CoordinateSystem();
 int CoordinateSystem(int value)
 {
   return (PspId.Data.CoordinateSystem = value);
 }

 // Запрос и установка дискретности цифрования
 unsigned long int DeviceCapability();

 // Запрос и установка системы высот
 int HeightSystem();

 // Запрос и установка единицы измерения по высоте
 int HeightUnit();

 // Запрос и установка единицы измерения в плане
 int PlaneUnit();

 // Запрос и установка масштаба карты
 long int Scale(long int scale);
 long int Scale();

 /***************************************************************
 *                                                              *
 *      Запросы / установка справочных данных                   *
 *                                                              *
 ***************************************************************/

 public :

 // Заполнение габаритов района в дециметрах
 void CreateMapBorder(void);

 // Запросить - групповые объекты имеются ?
 int IsGroup();

 // Установка признака наличия групповых объектов
 int IsGroup(int group);

 // Запрос и установка имени района
 const char * Name(const char * name);
 const char * Name();

 // Запрос и установка имени файла RSC в паспорт карты
 const char * NameRSC();
 const char * NameRSC(const char * name);

 // Запрос и установка имени файла GDX
 const char * NameGDX();
 const char * NameGDX(const char * name);

 // Запрос и установка имени файла HDR
 // number - номер листа,
 // для которого изменяется имя файла
 // При ошибке возвращается ноль
 const char * NameHDR(int number);
 const char * NameHDR(int number,const char * name);

 // Запрос и установка имени файла DAT
 // number - номер листа,
 // для которого изменяется имя файла
 // При ошибке возвращается ноль
 const char * NameDAT(int number);
 const char * NameDAT(int number,const char * name);

 // Запрос и установка имени файла GRA (графическое описание объекта)
 // number - номер листа,
 // для которого изменяется имя файла
 // При ошибке возвращается ноль
 const char * NameDRW(int number);
 const char * NameDRW(int number,const char * name);

 // Запрос и установка имени файла SEM
 // number - номер листа,
 // для которого изменяется имя файла
 // При ошибке возвращается ноль
 const char * NameSEM(int number);
 const char * NameSEM(int number,const char * name);

 // Запрос и установка номера таблицы масштабов
 int ScaleTableNumber(int number);
 int ScaleTableNumber();

 // Запрос и установка типа карты
 int MapType(int type);
 int MapType();

 // Запрос и установка вида рамки
 int FrameKind(int kind);
 int FrameKind();

 // Изменение габаритов листа number в метрах
 int  _fastcall UpdateListBorder(int number = 1, int save = 1);
 void _fastcall UpdateListBorder(int number,DOUBLEPOINT * pointmin,
                                            DOUBLEPOINT * pointmax);

 // Пересчитать геодезические координаты листа
 void _fastcall UpdateListGeoBorder(int number);

 // Запросить/Установить степень точности хранения координат
 // 0 - обычная, 1 - повышенная
 int GetPrecision();
 int SetPrecision(int precision);

 // Запросить/Установить число знаков после запятой для хранения координат
 // 1 - максимальное, 2 - сантиметры, 3 - миллиметры
 int GetPrecisionType();                                         
 int SetPrecisionType(int precision);

  // Запросить/Установить значение полупрозрачности текущей карты
  // при выводе на устройство (0 - 100)
  unsigned int _fastcall GetCurrentTranslucency() const
  {
    return MapColors.Transparent;
  }
  
  unsigned int _fastcall SetCurrentTranslucency(unsigned int translucency)
  {
    if ( translucency > 100 ) translucency = 100;
    return MapColors.Transparent = translucency;
  }


 protected:

 // Выделить память под структуры, описывающие листы карты
 // Заполнить их данными из файла-паспорта
 // При ошибке возвращает ноль
 int AllocateLists(int newcount,int oldcount);

 // Выделить память под структуру, описывающую лист карты
 // Общее число структур в памяти будет Count()+1
 // При ошибке возвращает ноль
 int AllocateOneList();

 // Заполнение габаритов листа number в дециметрах
 void CreateListBorder(int number);

 // Заполнение габаритов листов в дискретах
 void CalculateBorder(int count);

 /***************************************************************
 *                                                              *
 *               ВНУТРЕННИЕ КЛАССЫ ВЕКТОРНОЙ КАРТЫ              *
 *                                                              *
 ***************************************************************/

public :

 int    FileAccess;         // РЕЖИМ ДОСТУПА К ПАСПОРТУ (W/R)
 int    FileShare;          // МНОГОПОЛЬЗОВАТЕЛЬСКИЙ ДОСТУП
 HANDLE File_MAP;           // ИДЕНТИФИКАТОР ФАЙЛА

 int IsRelink;              // ПРИЗНАК ВЫПОЛНЕНИЯ ПЕРЕКОДИРОВКИ

 double MetInDis;           // КОЛИЧЕСТВО МЕТРОВ В ОДНОМ ДИСКРЕТЕ
                            // НА МЕСТНОСТИ (В ПРЯМОУГОЛЬН.СИСТЕМЕ)
 double MapX;               // НАЧАЛО КООРДИНАТ РАЙОНА В МЕТРАХ
 double MapY;               // В ПРЯМОУГОЛЬНОЙ СИСТЕМЕ НА МЕСТНОСТИ

 long   MaxX;               // ГАБАРИТЫ РАЙОНА В ДИСКРЕТАХ
 long   MaxY;               // В СИСТЕМЕ РАЙОНА
 long   MinX;
 long   MinY;

 char Name_MAP[MAX_PATH];   // ИМЯ ФАЙЛА ПАСПОРТА
 char Short_MAP[MAX_PATH];  // ИМЯ ФАЙЛА ПАСПОРТА
 char Path_MAP[MAX_PATH];   // ПУТЬ ДОСТУПА К ПАСПОРТУ
 char Path_LOG[MAX_PATH];   // ПУТЬ ДОСТУПА К ЖУРНАЛУ
                            // И СЛУЖЕБНЫМ ФАЙЛАМ

 int  Isdirty;              // ПРИЗНАК РЕДАКТИРОВАНИЯ ПАСПОРТА
 int  GeoAvailableFlag;     // ФЛАГ ВОЗМОЖНОСТИ РАСЧЕТА ГЕОДЕЗИЧЕСКИХ КООРДИНАТ

 PASSPORTHEAD   PspId;      // ИДЕНТИФИКАТОР ПАСПОРТНЫХ ДАННЫХ РАЙОНА
 SHEETDESC *    LstId;      // ИДЕНТИФИКАТОР ОПИСАНИЯ ПЕРВОГО ЛИСТА
 int            LstIdSize;  // РАЗМЕР ОПИСАНИЯ ЛИСТОВ    

 int IsTempMap;             // ПРИЗНАК ВРЕМЕННОЙ КАРТЫ

 int Mode_Work;             // РЕЖИМ РАБОТЫ С КАРТОЙ
                            // 0 - главное скорость
                            // != 0 - надежность данных

 HSITE hSite;               // ИДЕНТИФИКАТОР ЭЛЕМЕНТА СПИСКА КАРТ

 CHANGECALL  ChangeCall;    // АДРЕС ФУНКЦИИ ОПОВЕЩЕНИЯ О РЕДАКТИРОВАНИИ
 long int    ChangeParm;    // ПАРАМЕТР ФУНКЦИИ ОПОВЕЩЕНИЯ

 int         View;          // ПРИЗНАК ВИДИМОСТИ (0/1)
 int         Edit;          // ПРИЗНАК РЕДАКТИРУЕМОСТИ (0/1)
 int         Inquiry;       // ПРИЗНАК ВЫБОРА ОБ'ЕКТОВ НА КАРТЕ (0/1)

 long int    TopScale;      // Знаменатель масштаба верхней границы видимости  
 long int    BottomScale;   // Знаменатель масштаба нижней границы видимости  

 TTransaction ActionLog;    // ЖУРНАЛ ТРАНЗАКЦИЙ

 int ActionLogMode;         // РЕЖИМ ДОСТУПА К ЖУРНАЛУ (0 - ТОЛЬКО ЧТЕНИЕ)

 TMapRsc     Rsc;           // ОПИСАНИЕ ПАРАМЕТРОВ ОБ ЕКТОВ КАРТЫ

#ifndef HIDESHOW
 TMapColors  MapColors;     // ОПИСАНИЕ ПАЛИТРЫ КАРТЫ
#endif

 TSelectList SelectList;    // СПИСОК ИДЕНТИФИКАТОРОВ УСЛОВИЙ ПОИСКА

 TMapError   MapError;      // ПРОТОКОЛ ОШИБОК

 TMapSelect * SeekSelect;   // УСЛОВИЯ ПОИСКА/ВЫДЕЛЕНИЯ ПО КАРТЕ
 TMapSelect * ViewSelect;   // УСЛОВИЯ ОТОБРАЖЕНИЯ ПО КАРТЕ

 TMapList    List;          // ОПИСАНИЕ АКТИВНОГО ЛИСТА РАЙОНА

 TTranslate  Translate;     // ПАРАМЕТРЫ ПЕРЕСЧЕТА КООРДИНАТ

 long int    AdjustMode;    // СОСТОЯНИЕ ПОСЛЕДНЕГО ОБНОВЛЕНИЯ КАРТЫ

 long int    RangeScaleBot; // ИНДЕКС ТЕКУЩЕГО МАСШТАБА ОТОБРАЖЕНИЯ
 long int    RangeScaleTop; // ИНДЕКС ТЕКУЩЕГО МАСШТАБА ОТОБРАЖЕНИЯ  

#ifndef HIDEGDX   
 TMapGroups  Groups;        // ОПИСАНИЕ ФАЙЛА ГРУППОВЫХ ОБ ЕКТОВ
#endif

 TMapMetricMemory * ParentMemory;  
};

typedef TMap TSite;

// --------------------------------------------------------------
//  Открыть заданный лист c номером Number
//  Текущим становится лист "number"
//  При ошибке возвращает ноль
// --------------------------------------------------------------
inline int TMap::OpenList(int number)
{
  // Номер листа корректный ?
  if (number < 1) return 0;

  // Открыть указанный лист
  return List.Open(this,number);
}

// --------------------------------------------------------------
//  Открыть заданный лист, если он не открыт
//  Текущим становится лист "number"
//  При ошибке возвращает ноль
// --------------------------------------------------------------
inline int TMap::IsOpenList(int number)
{
  // Номер листа корректный ?
  if (number < 1) return 0;

  // Лист уже открыт ?
  if (List.Number() != number)
    {
      return(OpenList(number));
    }
  else
    {
      return 1;
    }
}

// --------------------------------------------------------------
// Выделить под лист максимальную область памяти
// При ошибке возвращает ноль
// --------------------------------------------------------------
inline int TMap::AllocateNotLimit(int number)
{
  return List.AllocateNotLimit(this, number);
}

typedef TMap TMAPDATA;

#ifdef BUILD_DLL
// Закрыть район работ
void _fastcall tmCloseData(TMap * data);

// Открыть район работ
// При ошибке возвращает ноль
int _fastcall tmOpenData(TMap * data, const char * map, int mode);

// Создать "пустой" район работ
// При ошибке возвращает ноль
int _fastcall tmCreateData(TMap * data, const char * mapname,
                           const	char * rscname,
                           MAPREGISTEREX * mapreg, LISTREGISTER * listreg);

// Открыть паспорт района,проверить и заполнить
// При ошибке возвращает ноль
int _fastcall tmOpenMap(TMap * data, const char * name, int mode);

// Создать паспорт района и заполнить
// При ошибке возвращает ноль
int _fastcall tmCreateMap(TMap * data, const char * mapname,
                          MAPREGISTEREX * mapreg, LISTREGISTER * listreg,
                          TMapRsc * maprsc);

// Создать временный район работ (пользовательскую карту)
// Имена файлов уникальные,
// располагаются в рабочей директории системы
// При закрытии района файлы удаляются автоматически
// При ошибке возвращает ноль
int _fastcall tmCreateTempMap(TMap * data, const	char * rscname);

// Создать в районе новый лист (лист становится последним)
// При ошибке возвращает ноль
// При неудачной попытке район может оказаться закрытым !
int _fastcall tmCreateList(TMap * data, LISTREGISTER * listreg, int save);

// Удалить из района лист
// При ошибке возвращает ноль
// При неудачной попытке район может оказаться закрытым !
int _fastcall tmDeleteList(TMap * data, int list, int save);

// Выделить память под структуры, описывающие листы карты
// Заполнить их данными из файла-паспорта
// При ошибке возвращает ноль
int _fastcall tmAllocateLists(TMap * data, int newcount,int oldcount);

// Выделить память под структуру, описывающую лист карты
// Общее число структур в памяти будет Count()+1
// При ошибке возвращает ноль
int _fastcall tmAllocateOneList(TMap * data);

// Заполнение габаритов листов в дискретах
void _fastcall tmCalculateBorder(TMap * data, int count);

// Заполнение габаритов района
void _fastcall tmCreateMapBorder(TMap * data);

// Изменение габаритов листа number в метрах
int _fastcall tmUpdateListBorder(TMap * data, int list, int save);

// Изменение габаритов листа number в метрах
void _fastcall tmUpdateListBorderByValue(TMap * data, int number,
                                         DOUBLEPOINT * pointmin,
                                         DOUBLEPOINT * pointmax);

// Рассчитать габариты листа по габаритам объектов       
void _fastcall tmUpdateListBorderByObjects(TMap * data);

//  Пересчитать геодезические координаты листа
void _fastcall tmUpdateListGeoBorder(TMap * data, int number);

//  Установка габаритов листа в метрах
void _fastcall tmCreateListBorder(TMap * data, int number);

// Отметить редактирование данных в паспорте района
// Возвращает номер очередного состояния данных
int _fastcall tmUpdateMode(TMap * data);

// Проверить соответствие данных в памяти и на диске
// При несоответствии возвращает ноль
int _fastcall tmCheckMode(TMap * data);

// Установка режима обработки данных
// (0 - скоростной, 1 - надежный)
int _fastcall tmWorkMode(TMap * data, int mode);

// Открыть заданный лист, если он не открыт
// Текущим становится лист "number"
// При ошибке возвращает ноль
int _fastcall tmIsOpenList(TMap * data, int number);

// Запрос - можно ли редактировать паспорт ?
int _fastcall tmIsWrite(TMap * data);

// Сохранить изменения в паспорте
int _fastcall tmSave(TMap * data, int force);

// Привести данные района в соответсвие с их состоянием на диске
// Если состояние данных изменялось - возвращает отрицательное значение
// При ошибке возвращает ноль
int _fastcall tmAdjustData(TMap * data);

// Запросить номер объекта - рамки листа
// По умолчанию берется текущий лист
// При ошибке возвращается ноль
int _fastcall tmGetListFrameNumber(TMap * data, int list);

// Запросить объект рамки текущего листа корты
// Если рамки нет, то возвращается 0
TObjectHead * _fastcall tmGetFrameDesc(TMap * data);

// Запросить число объектов в заданном листе
int _fastcall tmGetObjectCount(TMap * data, int list);

// Запросить объект в заданном листе карты
TObjectHead * _fastcall tmGetObjectHead(TMap * data, int list, int object);

// Загрузить карту старой версии
// Открыть район работ
// При ошибке возвращает ноль
int _fastcall tmLoadOldVersionData(TMap * data, const char * map);

// Запросить - имеются данные по проекции?
int _fastcall tmDataProjection(TMap * data);

// Установить проекцию и справочные данные по проекции
// исходного материала
void _fastcall tmSetDataProjection(TMap * data);

// Установка параметров паспорта из области MAPREGISTEREX
// При ошибке возвращает ноль
int _fastcall tmMapRegister(TMap * data, MAPREGISTEREX * mapreg);

// Установка параметров MapRegister по текущему листу
// При ошибке возвращает ноль
int _fastcall tmListToRegister(TMap * data, MAPREGISTEREX * mapreg,
                               LISTREGISTER * listreg, int list);

// Восстановить состояние паспортных данных
// на момент последнего сохранения в файле
// При ошибке возвращает ноль
int _fastcall tmRevert(TMap * data);

// Проверить попадание листа в "окно"
// Координаты окна заданы в дискретах
int _fastcall tmCheckFrame(TMAPDATA * data, int list, DFRAME * frame);

// Запрос габаритов листа в дискретах !!!
// При ошибке возвращает ноль
// list - номер листа,  1 <= list <= Count()
DFRAME * _fastcall tmListFrame(TMap * data, int list);

// Обновление данных паспорта карты
int _fastcall tmWritePasp(TMAPDATA * data, int offset,
                          char * address, int length);

// Запрос позиции точки отображения листа в районе
// При ошибке возвращает ноль
DOUBLEPOINT * _fastcall tmViewPosition(TMAPDATA * data, int list);

// Восстановить исходную палитру карты
void _fastcall mcRestoreColors(TMAPDATA * data);

// Установить текущую палитру по номеру
// (палитра устанавливается в MapColors)
// При ошибке возвращает ноль
COLORREF * _fastcall mcGetPaletteByNumber(TMAPDATA * data, int number);

// Запрос номенклатуры листа                     
const char * _fastcall tmGetListName(TMap * map, int list);

// Запрос числа листов
int _fastcall tmGetListCount(TMap * map);

// Найти номер листа по номенклатуре
int _fastcall tmGetListNumber(TMap * map, const char * name);

#endif  // BUILD_DLL

#endif

