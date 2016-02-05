#if !defined(MAPREGIS_H)
#define MAPREGIS_H

#ifndef MAPCREAT_H
  #include "mapcreat.h"
#endif

// Заполнение справочных данных в зависимости от типа карты
void _fastcall mrRegisterFromMapType(MAPREGISTEREX * mapregister,
                                     int maptype);

// Инициализация переменных класса
void _fastcall mrClear(MAPREGISTEREX * data);
void _fastcall lrClear(LISTREGISTER * data);


#ifdef __cplusplus

class _DLLCLASS TMap;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  КЛАСС "ФОРМУЛЯР ЛИСТА КАРТЫ" +++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

struct _DLLCLASS TListRegister : public LISTREGISTER,
                                 public REGISTERTYPES
{
 public:


 TListRegister()
 {
   Clear();
 }

 ~TListRegister(){};

 // Инициализация переменных класса

 void Clear();

 // Определение масштабного коффициента
 // для расчета геодезических координат
 // scale - знаменатель масштаба
 // maptype - тип карты
 // при ошибке возвращает 0

 int FactorScaleGeodetic(long scale, int maptype);

 // Запрос системной даты в установленном формате "ГГГГММДД"
 char *SystDate(char *date, int lenstring);


 // Контроль прямоугольных координат
 int CheckRightAngle(void);


 // Контроль геодезических координат
 int CheckGeodetic(void);


 // Установить геодезические координаты в структуре ListRegister
 // X, Y - прямоугольные координаты (в метрах)
 int RightAngleCordinames(COORDINATES *X, COORDINATES *Y);


 // Формирование имени файла по номенклатуре
 // file - место под имя файла
 // lenfile - длина строки под имя файла
 // nomenclature - номенклатура листа
 // при ошибке возвращает 0
 int NameFileFromNomenclature(char *file, int lenfile,
                              char *nomenclature);

 // Контроль номенклатуры
 // nomenclature - номенклатура
 // type - тип карты
 // scale - масштаб
 int CheckNomenclature(char *nomenclature, int type, long int scale);

 // Контроль номенклатуры
 // для проекции Гаусса-Крюгера
 // factorscale - масштабный коффициент
 //               для расчета геодезических координат
 int CheckNomenclatureTopo(char *nomenclature, int factorscale);


 // Контроль номенклатуры для обзорно-географических карт
 // factorscale - масштабный коффициент
 //               для расчета геодезических координат
 int CheckNomenclatureGeog(char *nomenclature, int factorscale);

 // Контроль номенклатуры для аэронавигационных карт
 // factorscale - масштабный коффициент
 //               для расчета геодезических координат
 int CheckNomenclatureAero(char *nomenclature, int factorscale);


 // Контроль номенклатуры для карт топографический план города
 // factorscale - масштабный коффициент
 //               для расчета геодезических координат
 // НЕ ДОПИСАНО !!!
 int CheckNomenclatureCityPlan(char *nomenclature, int factorscale);

};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++  КЛАСС "ФОРМУЛЯР РАЙОНА РАБОТ" ++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

struct _DLLCLASS TMapRegister : public MAPREGISTEREX,
                                public REGISTERTYPES
{
 public:

 TMapRegister()
 {
   SetValueType();
   Clear();
 }

 ~TMapRegister(){};

 //  Установить значения в таблицах для
 //  - типов карт
 //  - единиц измерения
 //  - вида эллипсоида
 //  - системы высот
 //  - системы координат
 //  - проекция
 //  - вида исходного материала
 //  - типа ИКМ
 //  - типа снимков
 //  - вида рамки

 void SetValueType();


 // Инициализация переменных класса
 void Clear();


 // Заполнение справочных данных в зависимости от типа карты
 void RegisterFromMapType(int maptype);

 // Заполнение справочных данных
 void RegisterFromData(MAPREGISTEREX * mapreg,LISTREGISTER * listreg);

 // Определение масштабного коффициента
 // для расчета геодезических координат
 // scale - знаменатель масштаба
 // maptype - тип карты
 // при ошибке возвращает 0
 int FactorScaleGeodetic(long scale, int maptype);


 // Определение осевого меридиана зоны (в минутах) по номенклатуре
 // 0.X-XX - начало строки номенклатуры, где XX - номер зоны
 int CalcAxisMeridianMinute(char *nomenclature);


 // Определение осевого меридиана зоны (в радианах) по номенклатуре
 // 0.X-XX - начало строки номенклатуры, где XX - номер зоны
 // при ошибке возвращает 0
 double CalcAxisMeridian(char *nomenclature);


 // Определение осевого меридиана зоны (в радианах)
 // по геодезическим координатам листа
 double CalcAxisMeridian(COORDINATES *L);


 // Дополнить данные по имеющимся    
 int PrepareRegister(int datpro = 0);


 // Установка значения осевого меридиана района по номенклатуре
 // 0.X-XX - начало строки номенклатуры, где XX - номер зоны
 // при ошибке (если не совпадает с уже существующим AxisMeridian)
 // возвращает 0
 int SetAxisMeridian(char *nomenclature);


 // Установка значения осевого меридиана района
 // по координатам листа
 // при ошибке (если не совпадает с уже существующим AxisMeridian)
 // возвращает 0
 int SetAxisMeridian(COORDINATES *L);


 // Вычисление геодезических координат B, L
 // для Равноугольной проекции Гаусса-Крюгера
 // по номенклатуре и масштабному коэффициету 1,2,3,4,5,6...
 // 0.X-XX - начало строки номенклатуры,
 // 0(1) - полушарие, X - пояс, XX - номер зоны
 // при ошибке возвращает 0
 // при нормальном завершении координаты B,L в радианах
 int GeodeticsCoordinateGauss(char *nomenclature, int factorscale,
                              COORDINATES *B, COORDINATES *L);


 // Вычисление сближения меридианов (в радианах)
 // по геодезическим координатам (в радианах) и
 // осевому меридиану (в радианах)
 double GridConvergence(COORDINATES *B, COORDINATES *L,
                        double axismeridian);


 // Расчет прямоугольных координат листа по геодезическим
 // B, L - геодезические координаты
 // X, Y - прямоугольные координаты
 // projection - проекция
 // map - район, к которому привязать
 // при ошибке (недостаточно данных для рассчета) возвращает 0

 int GeodeticToRightAngle(COORDINATES *B, COORDINATES *L,
                          COORDINATES *X, COORDINATES *Y,
                          int projection, TMap *map = 0);


 // Расчет геодезических координат листа по прямоугольным
 // B, L - геодезические координаты
 // X, Y - прямоугольные координаты
 // projection - проекция
 // map - район, к которому привязать
 // при ошибке (недостаточно данных для рассчета) возвращает 0

 int RightAngleToGeodetic(COORDINATES *X, COORDINATES *Y,
                          COORDINATES *B, COORDINATES *L,
                          int projection, TMap *map = 0);


 // Заполнение структуры CONSTPROJ в зависимости от проекции
 // контроль данных предусмотрен в классе TTranslate
 // при ошибке (отсутствие заданной проекции) возвращает 0
 int SetConstproj(int projection, CONSTPROJ *constproj);


 //  Взять адрес таблицы масштабов
 //  maptype - тип карты
 long int *GetAddrScale(int maptype);


 //  Взять число элементов в таблице масштабов
 //  maptype - тип карты
 int GetCountScale(int maptype);


 //  Взять адрес таблицы шаблонов номнклатур
 //  maptype - тип карты
 char **GetAddrPicture(int maptype);


 // Расчет данных на лист топографической карты
 // Равноугольная проекция Гаусса-Крюгера
 // входные данные : номенклатура,
 //                  знаменатель масштаба
 //                  проекции исходного материала
 // выходные данные: геодезические координаты,
 //                  прямоугольные координаты,
 //                  размеры рамки,
 //                  сближение меридианов
 int TopographicChartSheet(char *nomenclature,
                          long scale,
                          int projection = GAUSSCONFORMAL, TMap *map = 0);

 //  Установить флаг DataProjection
 void SetDataProjection();

 private:

 // Перевод минут (0.00) в радианы
 double MinuteToRadian(double minute);

 // Перевод секунд (0.00) в радианы
 double SecondToRadian(double sec);

 public:


// Описание листа карты
TListRegister ListRegister;

// Таблицы соответствия значений и типов
// Тип карты
int TableMapType[COUNTMAPTYPE];

// единицы измерения
int TableUnit[COUNTUNIT];

// единицы измерения по высоте
int TableUnitHeight[COUNTUNITHEIGHT];

// вид эллипсоида
int TableEll[COUNTELL];

// система высот
int TableHeight[COUNTHEIGHT];

// система координат
int TableCoord[COUNTCOORD];

// проекция
int TableProj[COUNTPROJ];

// вид исходного материала
int TableMapInitKind[COUNTMAPINITKIND];

// тип ИКМ
int TableMapInitType[COUNTMAPINITTYPE];

// тип снимков
int TablePhoto[COUNTPHOTO];

// вид рамки
int TableFrame[COUNTFRAME];

// Коды подсистем для обзорок
int TableBlock[COUNTGEOGRAPHICCODE];
};

#endif  // __cplusplus

#endif
