
#if !defined (MAPFRAME_H)
#define MAPFRAME_H

#ifndef MAPINFO_H
  #include "mapinfo.h"
#endif

enum
{                             // Коды ошибок при создании рамки листа
  IDC_MAPFRAME_RSC      = 1,  // Ошибка открытия или структуры RSC
  IDC_MAPFRAME_REGISTER = 2,  // Ошибка регистрации рамки листа
  IDC_MAPFRAME_SCALE    = 3,  // Ошибка в масштабе карты для топокарт
  IDC_MAPFRAME_CREATE   = 4,  // Ошибка при инициализации объекта рамка
  IDC_MAPFRAME_APPEND   = 5,  // Ошибка при добавлении точки
  IDC_MAPFRAME_DIST     = 6,  // Ошибка при контроле угловых точек
  IDC_MAPFRAME_STRUCT   = 7,  // Ошибка структуры вызова функции
  IDC_MAPFRAME_KIND     = 8,  // Ошибка в виде создаваемой рамки
};

typedef struct MAPFRAMEDATA     // ДАННЫЕ ДЛЯ СОЗДАНИЯ ОБЪЕКТА "РАМКА ЛИСТА"
{
 double        DistPointFrame; // Расстояние между точками прогиба в радианах
 TMap *        Map;            // Открытая карта
 TObjectInfo * ObjectInfo;     // Создаваемый объект рамки листа
 long          ExCodeFrame;    // Код рамки листа
 int           PointFrame;     // Количество точек у рамки листа
 int           Err;            // Код ошибки
}
  MAPFRAMEDATA;

// Инициализация структуры MAPFRAMEDATA
void _fastcall mfInit(MAPFRAMEDATA * data);

// Создание рамки листа для открытой карты
int _fastcall mfCreateFrameMap(MAPFRAMEDATA * data,
                               TMap * map, int list, long excodeframe,
                               TObjectInfo * objectinfo);

// Создание рамки листа по четырем точкам
int _fastcall mfCreateFrameMapFour(MAPFRAMEDATA * data);

// Создание рамки листа для обзорно-географических карт
int _fastcall mfCreateFrameMapGeog(MAPFRAMEDATA * data);

// Создание рамки листа для топографических карт
int _fastcall mfCreateFrameMapTopo(MAPFRAMEDATA * data);

// Создание рамки листа для карт UTM на North American Datum 1927
int _fastcall mfCreateFrameMapNAD27(MAPFRAMEDATA * data);     

// Подсчет количества точек рамки и расстояние между точками прогиба в
// радианах. Если точек прогиба нет, то расстояние между угловыми точками.
int _fastcall mfSetPointFrame(MAPFRAMEDATA * data);

//  Запись рамки
int _fastcall mfAppendFrame(MAPFRAMEDATA * data);

// Сообщение об ошибке
int _fastcall mfMessage(MAPFRAMEDATA * data);


#ifdef __cplusplus

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++  СОЗДАНИЕ ОБ'ЕКТА "РАМКА ЛИСТА" ++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TMapFrame : public MAPFRAMEDATA
{
public:
enum {   // Коды ошибок при создании рамки листа
     IDC_MAPFRAME_RSC = 1,       // Ошибка открытия или структуры RSC
     IDC_MAPFRAME_REGISTER = 2,  // Ошибка регистрации рамки листа
     IDC_MAPFRAME_SCALE    = 3,  // Ошибка в масштабе карты для топокарт
     IDC_MAPFRAME_CREATE   = 4,  // Ошибка при инициализации объекта рамка
     IDC_MAPFRAME_APPEND   = 5,  // Ошибка при добавлении точки
     IDC_MAPFRAME_DIST     = 6,  // Ошибка при контроле угловых точек
     IDC_MAPFRAME_STRUCT   = 7,  // Ошибка структуры вызова функции
     IDC_MAPFRAME_KIND     = 8,  // Ошибка в виде создаваемой рамки
     };

// Конструктор пустой
TMapFrame();

// Конструктор с паспортом листа и внешним кодом рамки
TMapFrame(TMap * map,int list,long excodeframe,TObjectInfo * objectinfo);

// Конструктор с паспортом листа
TMapFrame(TMap * map,int list,TObjectInfo * objectinfo);

// Создание рамки листа
int CreateFrameMap(TMap * map,int list,long excodeframe,TObjectInfo * objectinfo);

// Запись рамки листа
int AppendFrame();

// Обработка ошибок
int Error(int error) { Err = error; return Err; }
int Error() {return Err;}

private:

// Создание рамки листа для топографических карт
int CreateFrameMapTopo();

// Определение количества точек прогиба для топокарт
int SetPointFrame();

// Создание рамки листа для обзорно-географических карт
int CreateFrameMapGeog();

// Создание рамки по четырем точкам
int CreateFrameMapFour();

// Сообщение об ошибке
int Message();

};

#else

typedef  MAPFRAMEDATA  TMapFrame;

#endif  // __cplusplus

#endif
