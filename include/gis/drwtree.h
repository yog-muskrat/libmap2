
#if !defined(DRWTREE_H)
#define DRWTREE_H

#ifndef MAPMACRO_H
  #include "mapmacro.h"
#endif

#ifndef M3DGDI_H
  #include "m3dgdi.h"
#endif

#define TREEBUFFERSIZE (4*1024L)  // МИНИМАЛЬНЫЙ РАЗМЕР БУФЕРА !

#define TREEIDENT  0x73DD73DD     // Идентификатор дерева метрика обрезается
                                  
#define TREEIDENTN 0x73DD73DE     // Идентификатор дерева метрика  не обрезается

#define TREERECORDLIMIT (256*1024L)  // Предельный размер записи

typedef struct DTREEPLACE
     {
       long Function  ;    // Порядковый номер функции
       long Node      ;    // Порядковый номер узла (в пределах ветки)
       long Describe  ;    // Порядковый номер описания (в пределах ветки)
       long Element   ;    // Порядковый номер элемента (в пределах ветки)
     }
DTREEPLACE;

// Графическое описание трехмерных параметров представляет собой 5-тиуровневое
// дерево. Первый уровень - функции(F3DMARK,F3DMARKBYLINE ...), второй - узлы
// определенным образом связанная часть метрики(Короб,Плоскость вертикальная ...)
// 3 - описания (текстура,цвет...),4 - элементы (Куб,Сфера,Четырехугольник...)
// с метрикой (точки или структура соответственных размеров)
// Большая часть запросов имеет параметром указатель на структуру DTREEPLACE,
// в которой задается к какой части дерева относится запрос
// Запросы типа - длина части, идентификатор части, адрес части - относятся
// к последней ненулевой части структуры DTREEPLACE
// (например : запрос адреса
//                    place.Function = 2; place.Node = 3;  place.Describe = 1;
//                    place.Element = 2;
//            - возвращает адрес 2 элемента,3 узла, 2 функции.
// Для запросов количества частей
// на уровень указывает первая нулевая часть структуры DTREEPLACE
// (например : place.Function = 2; place.Node = 0;
//             - возвращает количество узлов у 2 функции.
//             place.Function = 1; place.Node = 1;  place.Describe = 0;
//             - возвращает общее количество описаний 1 узла 1 функции
// При ошибке возвращает 0

typedef struct DTREENAVIGATOR
     {
       long Ident     ;    // Номер навигатора
       long Level     ;    // Номер текущего уровня   ( 1 - 5 )
       char * Address ;    // Адрес текущего элемента
       DTREEPLACE Place;
     }
DTREENAVIGATOR;

// При внесении новых функций в список необходимо вносить добавления
// в функции : GetParamLength(F3DHEAD * head);
//             GetNodeCount(F3DHEAD * head);
//             IsTreeFunction(long function)
//             InitTreeFunction(...)

// При внесении новых узлов в список необходимо вносить добавления
// в функции :
//             long TDrawEdit::AddNodeCount(F3DHEAD * head);
//             long TDrawTree::GetNodeCount(F3DHEAD * head)

// При внесении новых элементов в список необходимо вносить добавления
// в функции :

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++   ГРАФИЧЕСКОЕ ОПИСАНИЕ 3D ОБЪЕКТОВ   ++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TDrawTree
{
 public :

          //******    Установка данных    *****************

 // Установить адрес начала трехмерного описания объекта
 TDrawTree(F3DTREE * addr)
   {
     Base = addr;
     BufferLength = 0;
     Memory = 0;
     IsDirty = 0;
     memset(&Navig1,0,sizeof(Navig1));
     memset(&Navig2,0,sizeof(Navig2));
   }

 TDrawTree(char * addr)
   {
     Base = (F3DTREE *)addr;
     BufferLength = 0;
     Memory = 0;
     IsDirty = 0;
     memset(&Navig1,0,sizeof(Navig1));
     memset(&Navig2,0,sizeof(Navig2));
   }

 TDrawTree(const int addr)
   {
     Base = (F3DTREE *)addr;
     BufferLength = 0;
     Memory = 0;
     IsDirty = 0;
     memset(&Navig1,0,sizeof(Navig1));
     memset(&Navig2,0,sizeof(Navig2));
   }

 TDrawTree()
   {
     Base = 0;
     BufferLength = 0;
     Memory = 0;
     IsDirty = 0;
     memset(&Navig1,0,sizeof(Navig1));
     memset(&Navig2,0,sizeof(Navig2));
   }

  // Установить адрес начала данных
 char * operator = (char * Addr)
   {
     return (char *)(Base = (F3DTREE  *)Addr);
   }

 // Установить адрес начала данных
 char * operator = (F3DTREE * Addr)
   {
     return (char *)(Base = Addr);
   }

 // Проверить указатель на данные
 int operator == (int Value)
   {
     return (Base == (F3DTREE  *)Value);
   }

 int operator != (int Value)
   {
     return (Base != (F3DTREE  *)Value);
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
     if ((Base->Ident >= TREEIDENT)||(Base->Ident<=TREEIDENTN))   
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

 // Запросить число частей на указанном уровне
 // на уровень указывает первая нулевая часть place
 // (например : place.Function = 2; place.Node = 0;
 //             - возвращает количество узлов у 2 функции.
 //             place.Function = 1; place.Node = 1;  place.Describe = 0;
 //             - возвращает количество описаний у 1 узла 1 функции
 // При ошибке возвращает 0
 long PartCount(DTREEPLACE * place);

 // Запросить адрес части на указанном уровне
 // на уровень указывает последняя ненулевая часть place
 // При ошибке возвращает 0
 char * PartAddress(DTREEPLACE * place);

 // Запросить полную длину части на указанном уровне
 // При ошибке возвращает 0
 long PartLength(DTREEPLACE * place);


            //******     Запросы по функциям   *****************

 // Проверить  вхождение функции отображения в список примитивов
 // При ошибке возвращает 0
 long IsTreeFunction(long function);

 // Инициализировать параметры функции в выделенной области указанной
 // длины
 // При ошибке возвращает 0
 long InitTreeFunction(long image,long length, char * work);

 // Запросить число функций
 // При ошибке возвращает 0
 long FunctionCount()
   {
     if (Base == 0) return 0;
     return Base->Count;
   }

 // Запросить тип параметров функции
 // number - последовательный номер (с 1)
 // При ошибке возвращает 0
 long FunctionParametersType(long number);

 // Запросить идентификатор функции
 // number - последовательный номер (с 1)
 // При ошибке возвращает 0
 long FunctionIdent(long number);

 // Запросить размер параметров функции (не включая узлы)
 // head указатель на заголовок функции
 // При ошибке возвращает -1 (т.к может и не быть узлов)
 long GetParamLength (F3DHEAD * head);

 // Запросить воможность ссылки функции c идентификатором dstIdent
 // на функцию c идентификатором srcIdent по относительным высотам
 // Можно - вовращает 1 иначе 0
 long CanHeigthRefer(long dstIdent,long srcIdent);

 // Запросить количество узлов у функции
 // head указатель на заголовок функции
 // При ошибке возвращает -1 (т.к может и не быть узлов)
 long GetNodeCount(F3DHEAD * head);

 // Проверить вхождение узла в список стандартных узлов
 // При ошибке возвращает 0
 long IsTreeNode(long image);

 // Инициализировать параметры узла в выделенной области указанной
 // длины
 // При ошибке возвращает 0, иначе длину функции
 long InitTreeNode(long image,long length, char * work);

            //******     Запросы по описаниям   *****************

 // Запросить общее число описаний
 // При ошибке возвращает 0
 long DescribeCount();

 // Запрос адреса описания по порядковому номеру (с 1)
 // При ошибке возвращает 0
 IMG3DDESCRIPTION * GetDescribe(int number);

 // Убрать и записей описаний коды текстур
 // При ошибке возвращает 0
 long ClearDescription(void);
            //******     Запросы по элементам   *****************

 // Запросить тип элемента
 // При ошибке возвращает 0
 long ElementType(DTREEPLACE * place);

 // Запросить адрес метрики элемента
 // При ошибке возвращает 0
 char * ElementMetricAddress(DTREEPLACE * place);

 // Изменить рамер знака
 // По заданным коеффициентам масштабирования знака
 // перевычисляются рамеры всех элементов
 long ChangeMarkSize(F3DMARK * mark,IMG3DPOINT * scale);

 // Уточнить рамер знака
 // При изменении элементов - найти габариты знака
 long ExactMarkSize(F3DMARK * mark);

 // Изменить рамер узла
 // По заданным коеффициентам масштабирования узла
 // center - точка отсчета узла(mark.Point[0])
 // перевычисляются рамеры всех элементов
 long ChangeNodeSize(IMG3DNODE * node,IMG3DPOINT * scale,IMG3DPOINT * center);

 // Уточнить рамер узла и привязку узла
 // При изменении элементов - найти рамер узла
 // В point привязка
 long ExactNodeSize(IMG3DNODE * node,IMG3DPOINT * point);

 // Сдвинуть узел
 // После сдвигания узла необходимо перевычислить размер знака
 long MoveNode(IMG3DNODE * node,IMG3DPOINT * offset);

 // Поворот узла (относительно начала координат)
 // axes = 1 - вокруг оси Х
 // axes = 2 - вокруг оси Y
 // axes = 3 - вокруг оси Z
 // center - точка привязки знака mark.Point[0]
 // После поворота узла необходимо перевычислить размер знака
 long RotateNode(IMG3DNODE * node,long axes,float angle,IMG3DPOINT * center);

 // Поворот точки (относительно начала координат)
 // axes = 1 - вокруг оси Х
 // axes = 2 - вокруг оси Y
 // axes = 3 - вокруг оси Z
 // center - точка привязки знака mark.Point[0]
 long RotatePoint(IMG3DPOINT * point,long axes,float angle,IMG3DPOINT * center);


 // Вычисление результирующего вектора(вокруг которого поворачивается GluObject)
 // и результирующего угла поворота
 // добавить поворот axes = 1 - вокруг оси Х
 //                  axes = 2 - вокруг оси Y
 //                  axes = 3 - вокруг оси Z
 // на угол angle (в градусах)
 long RotateGluObject(IMG3DROTATION* rotate,long axes,long angle);

 // Запросить смещение по высоте(относительно 0) и высоту функции
 // без учета семантики(с умалчиваемыми значениями)
 // При ошибке возвращает 0
 long FunctionHeigth(long function,float * offset ,float * heigth);
 
 // Запросить смещение по высоте(относительно 0) и высоту дерева
 // без учета семантики(с умалчиваемыми значениями)
 // При ошибке возвращает 0
 long Heigth(float * offset ,float * heigth);

 public :
 F3DTREE *   Base;
 long        BufferLength;     // Размер буфера графического описания
 char *      Memory;           // Способ обработки памяти в деструкторе
                								       // (если != 0, освободить)
 long        IsDirty;          // Признак редактирования данных

 DTREENAVIGATOR Navig1;        // Структуры для перемещения по данным
 DTREENAVIGATOR Navig2;        // Структуры для перемещения по данным
};


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++   РЕДАКТИРОВАНИЕ ГРАФИЧЕСКОЕ ОПИСАНИЕ 3D ОБЪЕКТОВ   ++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TEditTree : public TDrawTree
{
 /*********************************************************
 *                                                        *
 *       Функции инициализации данных класса              *
 *                                                        *
 *********************************************************/
 public :
    // Установить адрес начала описания
 TEditTree(char * address,long int length = 0)
  	{
     Memory = 0;
     SetBuffer(address,length);
  	}

 TEditTree()
   {
     Memory = 0;
  	  SetBuffer(0,0L);
   }

 TEditTree(TDrawTree draw)
   {
     Memory = 0;
     SetBuffer(draw.Address(),draw.Length());
  	}

 TEditTree(F3DTREE * param)
   {
     Memory = 0;
     Load(param);
   }

 ~TEditTree() { SetBuffer(0,0L); }


 // Выделить память под максимальную запись графики
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
   return Allocate(TREEBUFFERSIZE);
 }

 // Загрузить описание из указанной записи
 // При ошибке возвращает ноль, иначе - длину загруженной записи
 long Load(TDrawTree draw);
 long Load(TEditTree * draw)
 { if (draw) return Load(draw->Base);
   return 0; }

 // Загрузить описание из указанной записи параметров
 // принтерных функций (F3D_TREE)
 // Запись длинее DRAWBUFFERSIZE не загружается
 // При ошибке возвращает ноль, иначе - длину загруженной записи
 long Load(F3DTREE * dtree);
 // Установить параметры буфера данных
 // address - адрес начала, length - длина буфера.
 // Память выделенная Allocate() освобождается.
 void SetBuffer(char * address,long length);

 // Запросить/Установить признак редактирования данных
 long GetDirty();
 long SetDirty(long dirty);


/*********************************************************
 *                                                        *
 *      Навигация по данным                               *
 *                                                        *
 *********************************************************/
/*
 public :

 // Взять адрес части
 // Все параметры с 1.
 // Если не нужно спускаться на следующий уровень дальше 0
 char * GetPart(DTREEPLACE * place,long how);

 // Взять навигатор
 // 0 - свободных нет
 int GetNavigator();

 // Установить навигатор
 // Вовращает адрес установленного элемента
 // либо 0, если такого нет
 char * SetNavigatorPlace(long navigator,DTREEPLACE * place);

 // Запросить место навигатора
 // Вовращает адрес установленного элемента
 char * SetNavigatorPlace(long navigator,DTREEPLACE * place);

 // Установить навигатор на следующий либо предыдущий элемент
 // если how = 0 - в пределах ветки,
 // если how = 1 - по всему уровню
 // Вовращает адрес установленного элемента
 // либо 0, если такого нет
 char * Next(long navigator,long how);
 char * Prev(long navigator,long how);

 // Установить навигатор на уровень вверх или вниз
 // Вовращает адрес установленного элемента
 // либо 0, если такого нет
 char * Low(long navigator);
 char * Up(long navigator);

 // Запросить длину текущего элемента
 long GetCurrentNavLength(long navigator);

 // Запросить тип текущего элемента
 long GetCurrentNavLength(long navigator);
*/
 /*********************************************************
 *                                                        *
 *    Редактирование графического описания 3d объекта     *
 *                                                        *
 *********************************************************/
 public :

 // Добавить новую функцию с полным описанием и заголовком
 // При ошибке возвращает ноль,иначе - число функций в дереве
 long AppendFunction(long image,long length,F3DHEAD * param);

 // Добавить новую функцию c инициализацией параметров
 // При ошибке возвращает ноль,иначе - число функций в записи
 long AppendFunctionWithInit(long image);

 // Удалить функцию
 // number - номер функции (начиная с 1)
 // При ошибке возвращает ноль, иначе количество оставшихся функций
 int DeleteFunction(long number);

 // Передвинуть функцию на  новое место (номер с 1)
 // При ошибке возвращает 0
 long MoveFunction(long oldnumber,long newnumber);

 // Bcтавить функцию по номеру
 // Для новых параметров Ident = 0
 // При ошибке возвращает ноль,иначе номер функции
 long InsertFunction(long number, long length,F3DHEAD * param);

 // Заменить функцию по номеру на другую с полным описанием и заголовком  
 // При ошибке возвращает ноль,иначе - номер функции в дереве
 long ReplaceFunction(long number, long image,long length,F3DHEAD * param);

 // Проверить дерево на правильность ссылок функций
 // переставить при необходимости
 // При ошибке возвращает ноль, иначе 1
 long ChangeFunctionRefer();

 // Добавить к функции новый узел с полным описанием и заголовком
 // function - порядковый номер функции
 // При ошибке возвращает ноль,иначе - число узлов у функции
 long AppendNode(long function,long length,char * param);

 // Добавить новый узел в функцию c инициализацией параметров
 // function - порядковый номер функции
 // node - тип узла
 // При ошибке возвращает ноль,иначе - число узлов у функции
 long AppendNodeWithInit(long function,long node);

 // Удалить узел
 // number - номер функции (начиная с 1)
 // При ошибке возвращает ноль, иначе 1
 int DeleteNode(DTREEPLACE * place);

 // Заменить описание знака
 // number - номер функции, у которой заменяют знак
 // mark - адрес заменяемых параметров

 int ReplaceMark(int number,F3DMARK * mark,long length);

 protected:
 // Увеличить на 1 количество узлов у функции
 // head указатель на заголовок функции
 // Возвращает количество узлов
 long AddNodeCount(F3DHEAD * head);

};

#endif
