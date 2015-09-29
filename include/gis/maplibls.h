
#if !defined(MAPLIBLS_H)
#define MAPLIBLS_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifndef MAPVERSN_H
  #include "mapversn.h"
#endif

#ifndef PAIMET_H
  #include "paimet.h"
#endif  

#ifndef MAPGDIEX_H
  #include "mapgdiex.h"
#endif

#define MAXLIBRARYCOUNT 64

typedef IMLLIST * (WINAPI* DLLIMAGELIST)(void);


typedef int (WINAPI* DLLIMAGEBORDER)
        (long int type, const POLYDATAEX* data,
         const IMGDRAW * parm, const IMGCONTEXT * context, FRAME * border);

typedef int (WINAPI* DLLPAINTIMAGE)
       (long int, const POLYDATAEX*,
        const IMGDRAW *, const IMGCONTEXT *);

typedef int (WINAPI* DLLPAINTEXAMPLE)
       (long int, const IMGDRAW *, const IMGCONTEXT *);

typedef int (WINAPI* DLLTESTVISIBLE)
       (long int, const POLYDATAEX*,
        const IMGDRAW *, const IMGCONTEXT *);

typedef int (WINAPI* DLLCLOSELIBRARY) ();

typedef struct LIBRARYLIST
{
  // Число графических объектов в библиотеке
  DLLIMAGELIST    GetImageList;

  // Размер изображения объекта в мкм
  DLLIMAGEBORDER  GetImageBorder;

  // Отобразить объект в экранном виде
  DLLPAINTIMAGE   PaintImage;

  // Отобразить образец объекта в экранном виде
  DLLPAINTEXAMPLE PaintExample;

  // Определить попадание объекта в заданную область
  DLLTESTVISIBLE  TestVisible;

  // Освободить ресурсы библиотеки
  DLLCLOSELIBRARY CloseLibrary;

  char      Name[MAX_PATH];    // Имя библиотеки
  int       Count;             // Число подключений
  HINSTANCE HInstance;         // Идентификатор библиотеки

  IMLLIST * ImageList;         // Описание параметров отображения
}
  LIBRARYLIST;

typedef struct LIBRARYLISTDATA
{
 int Count;                            // Число загруженных библиотек

 LIBRARYLIST Library[MAXLIBRARYCOUNT]; // Описание библиотеки
}
  LIBRARYLISTDATA;

// Запросить габариты изображения объекта в дискретах в базовом масштабе
// Если функция не поддерживается - возвращает ноль,
// иначе - ненулевое значение
int _fastcall llGetImageBorder(int number, long int code,
                               const POLYDATAEX* data,
                               const IMGDRAW * parm,
                               const IMGCONTEXT * context,
                               FRAME * border);


// Отобразить объект
int _fastcall llPaintImage(int number, long int code,
                           const POLYDATAEX * data,
                           const IMGDRAW * parm, const IMGCONTEXT * context);

// Отобразить пример объекта
int _fastcall llPaintExample(int number, long int code,
                             const IMGDRAW * parm,
                             const IMGCONTEXT * context);

// Определить видимость объекта
int _fastcall llTestVisible(int number, long int code,
                            const POLYDATAEX * data,
                            const IMGDRAW * parm, const IMGCONTEXT * context);

// Запросить габариты изображения объекта в дискретах в базовом масштабе
// Если функция не поддерживается - возвращает ноль,
// иначе - ненулевое значение
int _fastcall llGetImageBorder(int number, long int code,
                               const POLYDATAEX* data,
                               const IMGDRAW * parm,
                               const IMGCONTEXT * context,
                               FRAME * border);

// Запросить габариты изображения объекта в микронах
// в базовом масштабе
// Если функция не поддерживается - возвращает ноль,
// иначе - ненулевое значение
int _fastcall llGetImageSize(TPaintMetric * pmet,              
                             const IMGLIBRARY * parm,
                             IMAGESIZE * imagesize);


// Добавить библиотеку в список
// Возвращает номер библиотеки в списке (1,...)
// При ошибке возвращает ноль
int _fastcall llOpenLibrary(const char * name);

// Удалить библиотеку из списка
// name - имя библиотеки (*.IML)
// number - номер библиотеки в списке
void _fastcall llCloseLibraryByName(const char * name);
void _fastcall llCloseLibrary(int number);

// Запросить описание функций,
// поддерживаемых библиотекой
const IMLLIST * _fastcall llGetImageList(int number);

// Запрос необходимости семантики для отображения
int _fastcall llGetSemanticFlag(int number, int index);

// Загрузить список функций
// При ошибке возвращает ноль
int _fastcall llLoadLibrary(const char * name, LIBRARYLIST * library, int i);

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++  СПИСОК БИБЛИОТЕК ГРАФИЧЕСКИХ ФУНКЦИЙ  +++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifdef __cplusplus

class _DLLCLASS TLibraryList : public LIBRARYLISTDATA
{

public :

 // Инициализировать список библиотек
 TLibraryList();

 // Удалить список библиотек
 ~TLibraryList();

 // Удалить библиотеку из списка
 // name - имя библиотеки (*.IML)
 // number - номер библиотеки в списке (1 - MAXLIBRARYCOUNT)
 void CloseLibrary(const char * name);
 void CloseLibrary(int number);

 // Проверить доступность библиотеки
 int IsLibraryActive(int number)
  {
    if ((number <= 0) || (number > MAXLIBRARYCOUNT))
      return 0;
    return Library[number-1].Count;
  }

 // Запросить число библиотек в списке
 int LibraryCount() { return Count; }

#ifndef HIDESECTION
 MAPCRITICALSECTION Section;                     
#endif

};

#else

typedef LIBRARYLISTDATA TLibraryList;

#endif

// Общий список подключаемых библиотек
extern TLibraryList LibraryList;


#endif

