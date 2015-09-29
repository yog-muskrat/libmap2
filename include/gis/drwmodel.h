
#if !defined(DRWMODEL_H)
#define DRWMODEL_H

#ifndef MAPMACRO_H
  #include "mapmacro.h"
#endif

#ifndef MAPTYPE_H
 #include "maptype.h"
#endif

#ifndef M3DGDI_H
  #include "m3dgdi.h"
#endif
#ifndef M3DMODEL_H
  #include "m3dmodel.h"
#endif

#define MODELBUFFERSIZE (4*1024L)     // МИНИМАЛЬНЫЙ РАЗМЕР БУФЕРА !

#define MODELIDENT  0x73DA73DA       // Идентификатор модели

#define MODELRECORDLIMIT (256*1024L)  // Предельный размер записи



// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++   ГРАФИЧЕСКОЕ ОПИСАНИЕ 3D ОБЪЕКТОВ   ++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TDrawModel
{
 public :

 //******    Установка данных    *****************

 // Установить адрес начала описания модели
 TDrawModel(M3DMODEL * addr)
   {
     Base = addr;
     BufferLength = 0;
     Memory = 0;
     IsDirty = 0;
   }

 TDrawModel(char * addr)
   {
     Base = (M3DMODEL *)addr;
     BufferLength = 0;
     Memory = 0;
     IsDirty = 0;
   }

 TDrawModel(const int addr)
   {
     Base = (M3DMODEL *)addr;
     BufferLength = 0;
     Memory = 0;
     IsDirty = 0;
   }

 TDrawModel()
   {
     Base = 0;
     BufferLength = 0;
     Memory = 0;
     IsDirty = 0;
   }

  // Установить адрес начала данных
 char * operator = (char * Addr)
   {
     return (char *)(Base = (M3DMODEL *)Addr);
   }

 // Установить адрес начала данных
 char * operator = (M3DMODEL * Addr)
   {
     return (char *)(Base = Addr);
   }

 // Проверить указатель на данные
 int operator == (int Value)
   {
     return (Base == (M3DMODEL  *)Value);
   }

 int operator != (int Value)
   {
     return (Base != (M3DMODEL  *)Value);
   }

              //******     Общие запросы    *****************

 // Запросить адрес начала записи
 // При ошибке возвращает 0
 char * Address() { return (char *)Base; }

 // Проверить корректность структуры записи
 // При ошибке возвращает 0
 long IsCorrect()
   {
     if (Base == 0) return 0;
     if (Base->Ident == MODELIDENT)
       return 1;
     return 0;
   }

 // Запросить полную длину записи
 // При ошибке возвращает 0
 long Length()
   {
     if (Base == 0) return 0;
     return Base->Length;
   }

 // ***************** Функции для работы с формами модели *****************

 // Запросить ключ формы модели
 long Key()
   {
     if (Base == 0) return 0;
     return Base->Form;
   }

 // Запросить количество отрезков формы основания модели
 long PointCount()
   {
     if (Base == 0) return 0;
     return Base->Count;
   }

 // Запросить адрес начала отрезков формы основания модели
 IMG3DPOINT * Points()
   {
     if (Base == 0) return (IMG3DPOINT *)0;
     return (IMG3DPOINT *)((char *)Base + sizeof(M3DMODEL));

   }

 // ***************** Функции для работы с подмоделями *****************

 // Звпросить количество подмоделей
 long SubmodelCount();

 // Запросить длину подмодели по порядковому номеру с 1
 long SubmodelLength(long number);

 // Запросить заголовок подмодели по порядковому номеру с 1
 IMAGEHEAD * SubmodelHead(long number);

 // Запросить тип подмодели ( модель или шаблон ) cm. IMAGETYPE
 long SubmodelType(long number);

 // Запросить количество точек основания шаблона
 long SubmodelPointCount(long number);

 // Запросить адрес начала точек формы основания шаблона
 IMG3DPOINT * SubmodelPoints(long number);


/*
 // Инициализировать параметры функции в выделенной области указанной
 // длины
 // При ошибке возвращает 0
 long InitSubmodel(long image,long length, char * work);
*/
/*
 // Запросить воможность ссылки функции c идентификатором dstIdent
 // на функцию c идентификатором srcIdent по относительным высотам
 // Можно - вовращает 1 иначе 0
 long CanHeigthRefer(long dstIdent,long srcIdent);
*/
/*
 // Запросить смещение по высоте(относительно 0) и высоту функции
 // без учета семантики(с умалчиваемыми значениями)
 // При ошибке возвращает 0
 long FunctionHeigth(long function,float * offset ,float * heigth);

 // Запросить смещение по высоте(относительно 0) и высоту дерева
 // без учета семантики(с умалчиваемыми значениями)
 // При ошибке возвращает 0
 long Heigth(float * offset ,float * heigth);
*/
 public :
 M3DMODEL *  Base;             // Параметры модели
 long        BufferLength;     // Размер буфера графического описания
 char *      Memory;           // Способ обработки памяти в деструкторе
                								       // (если != 0, освободить)
 long        IsDirty;          // Признак редактирования данных
};


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++   РЕДАКТИРОВАНИЕ ГРАФИЧЕСКОЕ ОПИСАНИЕ 3D ОБЪЕКТОВ   ++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TEditModel : public TDrawModel
{
 /*********************************************************
 *                                                        *
 *       Функции инициализации данных класса              *
 *                                                        *
 *********************************************************/
 public :
    // Установить адрес начала описания
 TEditModel(char * address,long int length = 0)
  	{
     Memory = 0;
     SetBuffer(address,length);
  	}

 TEditModel()
   {
     Memory = 0;
  	  SetBuffer(0,0L);
   }

 TEditModel(TDrawModel model)
   {
     Memory = 0;
     SetBuffer(model.Address(),model.Length());
  	}

 TEditModel(M3DMODEL * model)
   {
     Memory = 0;
     Load(model);
   }

 ~TEditModel() { SetBuffer(0,0L); }


 // Выделить память под максимальную запись модели
 // Проинициализировать структуру данных
 // Память автоматически освобождается в деструкторе
 // или при назначении другой области с помощью
 // SetBuffer(...), в том числе, SetBuffer(0,0).
 // При ошибке возвращает ноль
 long Allocate(long size);

 // Проинициализировать структуру данных
 // При ошибке возвращает ноль
 long Clear();

 long Create()
 {
   if (Base != 0) return Clear();
   return Allocate(MODELBUFFERSIZE);
 }

 // Загрузить описание из указанной записи
 // При ошибке возвращает ноль, иначе - длину загруженной записи
 long Load(TDrawModel model);
 long Load(TEditModel * model)
 { if (model) return Load(model->Base);
   return 0; }

 // Загрузить описание из указанной записи параметров модели
 // long key ключ модели 
 // long code - код библиотеки, где записана модель или шаблон
 long Load(HRSC hrsc, long key, long code);

 // Загрузить описание из указанной записи параметров модели (M3DMODEL)
 // Запись длинее MODELBUFFERSIZE не загружается
 // При ошибке возвращает ноль, иначе - длину загруженной записи
 long Load(M3DMODEL * model);

 // Установить параметры буфера данных
 // address - адрес начала, length - длина буфера.
 // Память выделенная Allocate() освобождается.
 void SetBuffer(char * address,long length);

 // Запросить/Установить признак редактирования данных
 long GetDirty();

 long SetDirty(long dirty);

 /*********************************************************
 *                                                        *
 *    Редактирование графического описания 3d модели      *
 *                                                        *
 *********************************************************/
 public :

 // ***************** Функции для работы с формами модели *****************

 // Заменить форму основания модели
 // count - число отрезков модели
 // point - адрес начала точек (по 2 на отрезок)
 long ReplaceFormPoint(HRSC hrsc,long count, IMG3DPOINT * point);

 // Добавить отрезок формы основания модели
 // begin - указатель на запись отрезка из 2 точек начало и конец
 long AppendFormPoint(HRSC hrsc,IMG3DPOINT * begin);

 // Заменить отрезок формы основания модели
 long ReplaceFormPoint(HRSC hrsc,long number,IMG3DPOINT * begin,IMG3DPOINT * end);

 // Удалить отрезок формы основания модели
 long DeleteFormPoint(long number);

 // Заменить вектор привязки основания модели
 long ReplaceBaseModel(long number, IMG3DPOINT * begin,IMG3DPOINT * end);

 // ***************** Функции для работы с подмоделями *****************

 // Заменить подмодель ( первая подмодель заменяется только на шаблон)
 long ReplaceSubmodel(long number,long length,M3DMODEL * param);

 // Добавить подмодель с полным описанием и заголовком
 // При ошибке возвращает ноль,иначе - число подмоделей
 long AppendSubmodel(HRSC hrsc, IMAGEHEAD * head);

 // Добавить новую подмодель с  инициализацией параметров
 // При ошибке возвращает ноль,иначе - число подмоделей в записи
 long AppendSubmodelWithInit(long image);

 // Удалить подмодель
 // number - номер функции (начиная с 2 - перваую можно только заменить)
 // При ошибке возвращает ноль, иначе количество оставшихся подмоделей
 long DeleteSubmodel(long number);

 // Добавить отрезок формы основания подмодели
 long AppendSubFormPoint(long subnumber, IMG3DPOINT * begin, IMG3DPOINT * end);

 // Удалить отрезок формы основания подмодели
 long DeleteSubFormPoint(long subnumber,long number);

 // Заменить вривязку подмодели
 // number - порядковый номер с 1
 long ReplaceFixation(long number,FIXATION * fix);

 // Вырезать из формы основания первой подмодели
 // метрику подмодели с учетом фиксатора
 long CuttingSubmodel(HRSC hrsc,long count, IMG3DPOINT * point,FIXATION * fix);


 // ***************** работа с отрезками   *****************

 // Сравнить отрезки (считаем, что отрезки параллельны плоскости XZ)
 // 1 - равны
 // 2 - первый включает второй (точное вложение с концами)
 // 3 - второй включает первый (точное вложение с концами)
 // 4 - есть общая часть
 // 5 - равны по метрике(высота разная)
 // 6 - первый включает второй (высота разная)(точное вложение с концами)
 // 7 - второй включает первый(высота разная) (точное вложение с концами)
 // 8 - есть общая часть (высота разная)
 // 0 - все остальные случаи
 long CompareSection(IMG3DPOINT * secton1,IMG3DPOINT * section2);

 // Вырезать из отрезка отрезок
 // возвращает количество результирующих отрезков
 // по адресу result должно быть зарезервировано место
 // не менее 4 * sizeof(IMG3DPOINT)
 long CutSection(IMG3DPOINT * secton1,IMG3DPOINT * section2,
                 IMG3DPOINT * result);

 // Преобразовать точку по фиксатору к системе координат модели
 long FixPoint(IMG3DPOINT * point, FIXATION * fix);



// protected:
};

#endif
