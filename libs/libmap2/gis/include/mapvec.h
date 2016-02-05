
#ifndef MAPVEC_H
#define MAPVEC_H

#ifndef MAPTAB_H
 #include "maptab.h"
#endif

#ifdef HIDEFORMAT
  #define HIDEVECT
#endif

class TMapList;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Файл с набором записей фиксированной длины
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef struct VECDATA     // ВЕКТОР ПРИВЯЗКИ 3D-модели
{                          //
  long        Code;        // Код библиотеки (для уникальных изображений, иначе 0)
  long        Key;         // Ключ изображения (для уникальных изображений, иначе 0)
  XYHDOUBLE   Offset;      // Смещение формы модели относительно первой точки объекта
  double      Angle;       // Угол поворота оси X модели относительно оси X карты
}
  VECDATA;

typedef struct VECRECORD   // Запись вектора привязки (запись файла VEC)
{                          //
  long        Number;      // Номер объекта
  long        BaseKey;     // Ключ объекта
  VECDATA     Data;        // Вектор привязки
}
  VECRECORD;

// Первая точка вектора на объекте вычитаем из нее координаты первой точки объекта.
// Из полученного вычитаем координаты первой точки вектора модели. Полученное значение = Offset.
// Angle - Угол поворота оси X модели относительно оси X карты.

#ifndef HIDEVECT
typedef class _DLLCLASS TVectorFile : public TTableFile
#else
typedef class _DLLCLASS TVectorFile
#endif
{
 public:

#ifndef HIDEVECT
   TVectorFile(TMapList * data);
   ~TVectorFile();
#else
   TVectorFile(TMapList * ) {}
   ~TVectorFile() {}
#endif

#ifndef HIDEVECT
   // Создать файл с набором записей
   // При успешном завершении возвращает ненулевое значение
   int _fastcall Create(TMapList * data);

   // Открыть файл с набором записей
   // При успешном завершении возвращает ненулевое значение
   int _fastcall Open(TMapList * data);

   // Закрыть файл
   void _fastcall Close();

   // Запросить адрес записи по ее номеру
   VECDATA * _fastcall Record(TMapList * data, int number);

   // Обновить запись по номеру
   // force - признак немедленного обновления записи в файле
   int _fastcall Record(TMapList * data, const VECDATA * record,
                        int number, int key, int force);
#else
   // Создать файл с набором записей
   // При успешном завершении возвращает ненулевое значение
   int _fastcall Create(TMapList * ) { return 0; }

   // Открыть файл с набором записей
   // При успешном завершении возвращает ненулевое значение
   int _fastcall Open(TMapList * ) { return 0; }

   // Закрыть файл
   void _fastcall Close() {}

   // Запросить адрес записи по ее номеру
   VECDATA * _fastcall Record(TMapList * , int )
   { return 0; }

   // Обновить запись по номеру
   // force - признак немедленного обновления записи в файле
   int _fastcall Record(TMapList * , const VECDATA * ,
                        int , int , int )
   { return 0; }
#endif

#ifndef HIDEVECT
   // Запросить имя файла векторов
   const char * GetFileName() { return Name; }

   // Запросить - есть ли в файле данные?
   int IsEmpty() { return (Head.RecordCount == 0); }

   // Установить расширение создаваемого файла
   void _fastcall SetFileExt(const char * ext = 0);

   // Сформировать имя файла привязки 3D-макета
   // При успешном завершении возвращает ненулевое значение
   const char * _fastcall GetName(TMapList * data);
#else
   // Запросить имя файла векторов
   const char * GetFileName() { return ""; }

   // Запросить - есть ли в файле данные?
   int IsEmpty() { return 1; }

   // Установить расширение создаваемого файла
   void _fastcall SetFileExt(const char * ext = 0) {}

   // Сформировать имя файла привязки 3D-макета
   // При успешном завершении возвращает ненулевое значение
   const char * _fastcall GetName(TMapList * ) { return ""; }
#endif

 protected:

#ifndef HIDEVECT
  TMapList *    Data;

  HANDLE        Back_VEC;     // Идентификатор резервного файла

  char          Ext[8];       // Расширение создаваемого файла
#endif  
}
  TVectorFile;

#endif
