
#ifndef RSC3DAPI_H
#define RSC3DAPI_H

#ifndef RSCFL3D_H
   #include "rscfl3d.h"
#endif

#ifndef RSCAPI_H
   #include "rscapi.h"
#endif

typedef struct LEVELIMAGE
{
  long CodeLib0;          // Код библиотеки для изображения 0 уровня(ближнего)
  long Key0;              // Ключ изображения для 0 уровня
  long CodeLib1;          // Код библиотеки для изображения 1 уровня(ближнего)
  long Key1;              // Ключ изображения для 1 уровня
  long CodeLib2;          // Код библиотеки для изображения 2 уровня(ближнего)
  long Key2;              // Ключ изображения для 2 уровня
  long Incode;            // Внутренний код объекта
  char Flag0;             // Флаг редактирования для 0 уровня
  char Flag1;             // Флаг редактирования для 1 уровня
  char Flag2;             // Флаг редактирования для 2 уровня
  char Rezerv;            // Резерв
}
  LEVELIMAGE ;


 // Вызов диалога Редактирование 3D объектов классификатора
 void Get3DLib(void * owner,LEVELIMAGE * levels,HMAP hmap,HRSC hrsc,long * ret);
 // Вызов диалога просмотра текстур или  файлов BMP
 long int Get3DDemo(HWND handle,HMAP hmap,HRSC hrsc,char * bmpname,
                     RECTEXTURE * tex, int enterflag);

extern "C"
{

 // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 // +++++ ОПИСАНИЕ ФУНКЦИЙ ДОСТУПА К 3D ИЗОБРАЖЕНИЯМ    +++++
 // +++++      И 3D ПАРАМЕТРАМ  ОБ'ЕКТОВ                +++++
 // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 // Инициализировать 3D графику
 // hRsc - идентификатор классификатора карты
 // При ошибке возвращает 0

 long int WINAPI mapInitRsc3D(HRSC hRsc);

 // Запрос 3D параметров объекта по уровню (0,1,2 - где 0 - ближний)
 // и порядковому номеру (индексу ) объекта с 1
 // При отсутствии параметров запрошенного уровня выдаются параметры
 // ближнего уровня
 // При ошибке или отсутствии 0

 const char * WINAPI mapGetRsc3DParam(HRSC hRsc,long int incode,
                                      long int level);

 // Запрос 3D параметров объекта по уровню (0,1,2 - где 0 - ближний)
 // и порядковому номеру (индексу ) объекта с 1
 // при ошибке или отсутствии параметров укаанного уровня возвращает 0.

 const char * WINAPI mapIsRsc3DParam(HRSC hRsc, long int incode,
                                          long int level);

 // Запросить общее количество записей указанного типа
 // (OBJECT_PARAMETERS,OBJECT_TEXTURE ...  rscfl3d.h)
 // в библиотеке с кодом code
 // При ошибке или отсутствии 0

 long int WINAPI mapTakeRscRecordCount(HRSC hRsc, long int code, long int type);

 // Запросить заголовок записи указанного типа
 // ( тип - OBJECT_PARAMETERS,OBJECT_TEXTURE ...  rscfl3d.h)
 // по порядковому номеру
 // в библиотеке c данным кодом
 // Возвращает код записи, при ошибке 0.

 long int WINAPI mapTakeRscRecordHead(HRSC hRsc, long int number, long int code,
                                     long int type, RECHEAD * address);

 // Запросить заголовок записи  по коду
 // Возвращает запись, при ошибке 0.

 RECHEAD * WINAPI mapTakeRscCodeRecordHead(HRSC hRsc,long int code);

 // Запросить заголовок записи указанного типа по коду библиотеки и ключу
 // Возвращает запись, при ошибке 0.                  

 RECHEAD * WINAPI mapTakeRscKeyRecordHead(HRSC hRsc,long int code,long int key);

 // Запросить адрес текстуры по порядковому номеру (c 1)
 // При ошибке возвращает 0.

 RECTEXTURE * WINAPI mapTakeRscTexture(HRSC hRsc,long int number);

 // Создать параметры 3D изображения
 // по коду библиотеки,типу метрики,условному названию,
 // длине параметров и параметрам (типа F3DTREE)
 // При ошибке или отсутствии возвращает 0 , иначе код изображения

 long int WINAPI mapCreateRsc3DImage(HRSC hRsc, long int code, long int type,
                                     long int length, char * param,char * name);

 // Запрос параметров 3D изображения
 // и коду библиотеки и ключу изображения.
 // При ошибке или отсутствии 0
 // иначе адрес параметров изображения (в виде F3DTREE mapgdi3d.h )

 char * WINAPI mapGetRsc3DImageParam(HRSC hRsc, long int code, long int key);

 // Установить параметры 3D изображения
 // по коду библиотеки,ключу изображения ,типу метрики (0, 1 ... rscfl3d.h),
 // длине параметров и параметрам (в виде F3DTREE mapgdi3d.h )
 // При ошибке или отсутствии возвращает 0, иначе код записи

 long int WINAPI mapSetRsc3DImageParam(HRSC hRsc,long int code,
                                  long int key,long int type,long int length,
                                  char * param);

 // Заменить название 3D изображения
 // по коду библиотеки,ключу изображения
 // При ошибке или отсутствии возвращает 0

 long int WINAPI mapSetRsc3DImageName(HRSC hRsc,long int code,
                                               long int key, char * name);

 // Связать объект по уровню (0,1,2 - где 0 - ближний)
 // и порядковому номеру (индексу ) объекта с 1
 // с изображением по коду библиотеки и ключу объекта.
 // При ошибке возвращает 0.

 long int WINAPI mapSetRsc3DImageToObject(HRSC hRsc, long int incode,
                                   long int level, long int code, long int key);

 // Запрос ключа отображения параметров объекта
 // по уровню (0,1,2 - где 0 - ближний)
 // и порядковому номеру (индексу ) объекта с 1
 // при ошибке или отсутствии возвращает 0

 long int WINAPI mapGetRsc3DObjectKey(HRSC hRsc,long int incode,long int level);

 // Убрать 3D изображение объекта по уровню (0,1,2 - где 0 - ближний)
 // и порядковому номеру (индексу ) объекта с 1
 // при ошибке 0                                                     

 long int WINAPI mapDeleteRsc3DImageFromObject(HRSC hRsc,long int incode,
                                                        long int level);

 // Запросить адрес параметров материала по номеру в таблице записей (c 1)
 // При ошибке 0.                                                  
 ACT3DMATERIALMODE * WINAPI mapTakeRsc3DMaterial(HRSC hRsc,long int number);

 // Заменить параметры материала по коду библиотеки и ключу материала
 // При ошибке 0, иначе код записи материала
 long WINAPI mapReplaceRsc3DMaterial(HRSC hRsc,long int libcode,long int key,
                          ACT3DMATERIALMODE * material);           

 // Удалить параметры материала по коду библиотеки и ключу
 // При ошибке 0, иначе код записи материала                       
 long WINAPI mapDeleteRsc3DMaterial(HRSC hRsc,long int libcode,long int key);

 // Заменить название материала по коду библиотеки и ключу
 // (название уникально для данной библиотеки)
 // При ошибке 0
 long WINAPI mapReplaceRsc3DMaterialName(HRSC hRsc,long int libcode,long int key,
                          char * name);                              

 // Создать запись материала по коду библиотеки, параметрам материала и
 // названию (название уникально для данной библиотеки)
 // При ошибке 0 иначе код записи материала
 long WINAPI mapCreateRsc3DMaterial(HRSC hRsc,long int libcode,    
                                    ACT3DMATERIALMODE * material,char * name);

 // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 // +++ ОПИСАНИЕ ФУНКЦИЙ ДОСТУПА К БИБЛИОТЕКАМ 3D ОБ'ЕКТОВ ++
 // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 // Запрос имени библиотеки трехмерных параметров по коду
 // При ошибке возвращает пустую строку.

 const char * WINAPI mapGetRsc3DLibraryName(HRSC hRsc,long int code);

 // Запрос количества библиотек трехмерных параметров
 // При ошибке возвращает 0.

 long int WINAPI mapGetRsc3DLibraryCount(HRSC hRsc);

 // Запрос кода библиотеки по порядковому номеру библиотеки 3D параметров (c 1)
 // При ошибке возвращает 0.

 long int WINAPI mapGetRsc3DLibraryCode(HRSC hRsc,long int number);

 // Запрос наличия активных(есть ссылки  и файл найден) библиотек
 // При ошибке возвращает 0.

 long int WINAPI mapIsActive3DLibrary(HRSC hRsc);



} // extern "C"

#endif