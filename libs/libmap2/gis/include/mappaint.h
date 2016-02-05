
#ifndef MAPPAINT_H
#define MAPPAINT_H

#ifndef MAPCNT_H
  #include "mapcnt.h"
#endif

#ifdef WIN32API
#ifndef PRNAPI_H
 #include "prnapi.h"
#endif
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ КЛАСС "ОТОБРАЖЕНИЕ ЭЛЕКТРОННОЙ КАРТЫ" ++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS  TMapPaint : public TMapControl
{
  public:

  /*********************************************************
  *                                                        *
  *           КОНСТРУКТОРЫ И ДЕСТРУКТОРЫ КЛАССА            *
  *                                                        *
  *********************************************************/

   TMapPaint();
  ~TMapPaint();


  /*********************************************************
  *                                                        *
  *         ФУНКЦИИ ОТОБРАЖЕНИЯ И ПЕЧАТИ ДОКУМЕНТА         *
  *                                                        *
  *********************************************************/

  // Отобразить данные
  void _fastcall Paint(HDC hDC, int erase, RECT& rect);

  // Отобразить объект
  void PaintObject(HDC hDC, int erase, RECT& rect, TObjectInfo* object,
                   int dontclip = 0);     

  // Отобразить объект в Image
  void PaintObjectToImage(char *lpImage,int ImageAreaWidth,int ImageAreaHeight,
                   int erase, RECT& rect,
                   TObjectInfo* object);

  // Отобразить объект
  int PaintUserObject(HDC hdc, RECT& rect, PAINTPARM* image,
                      POLYDATAEX* data, TMap* map = 0);

  // Отобразить образец вида объекта
  void PaintExampleObject(HDC hDC, RECT& rect, int number,
                          char* parm, POLYDATAEX* data);

  // Отобразить данные или объект на экран, используя DIB
  void _fastcall PaintDib(HDC hDC, int erase, RECT* Rect,
                          TMapObject* object = 0,
                          int mapnumber = -2, COLORREF color = 0,
                          TMapSelect * select = 0);

  // Отобразить фрагмент карты на заданном устройстве
  // в текущих масштабе и составе объектов и
  // выделить на карте объекты, удовлетворющие заданным условим
  // hMap   - идентификатор открытых данных
  // hdc    - контекст устройства
  // rect   - координаты фрагмента карты (Draw) в изображении (Picture)
  // number - номер карты, на которой выделяются объекты или -1 (для всех)
  // select - условия отбора объектов или 0
  // color  - цвет, которым будут выделяться объекты на карте

  void _fastcall PaintAndSelect(HDC hDC, int erase, RECT& rect,
                                int number, TMapSelect * select,
                                COLORREF color);                  

  /*********************************************************
  *                                                        *
  *             ФУНКЦИИ ЗАПРОСА ИНФОРМАЦИИ                 *
  *                                                        *
  *********************************************************/

  public :

  // Запросить адрес начала битовой области DIB (0,0 - левый нижний угол)
  void * GetDibBits();

  // Запросить описание DIB
  BITMAPINFOHEADER * GetDibInfo();

  // Запросить условия выбора объектов для отображения
  TMapSelect * GetShowSelect();

  // Функция возвращает габариты всего изображения в пикселах
  //   (X,Y в координатах Windows)
  void GetPictureBorder(long& x, long& y);

  // Запросить идентификатор логической палитры карты
  // При ошибке возвращает ноль
  HPALETTE GetViewPalette() { return ViewPalette; }


  /*********************************************************
  *                                                        *
  *                  ФУНКЦИИ СЕРВИСА                       *
  *                                                        *
  *********************************************************/

  // Функция изменения цвета фона
  void SetBackGround(COLORREF background);
  COLORREF GetBackGround() { return MapPalette.BackGround(); }

  // Обновить палитру окна
  int UpdatePalette(HWND hwnd, int mode = FALSE);

  // Установить стиль палитры матрицы
  void SetMtrPaletteStyle(int style);

  // Отобразить растр по номеру
  void PaintRst(HDC hDC, int erase, RECT& rect, int number, int flagClear = 0);  

  // Отобразить матрицу по номеру
  void PaintMtr(HDC hDC, int erase, RECT& rect, int number);

#ifndef HIDEMTL
  // Отобразить матрицу слоев по номеру
  void PaintMtl(HDC hDC, int erase, RECT& rect, int number);
#endif

#ifndef HIDETIN
  // Отобразить TIN-модель по номеру
  void PaintTin(HDC hDC, int erase, RECT& rect, int number); 
#endif

#ifndef HIDEMTQ         

  // Отобразить матрицу качеств по номеру
  void PaintMtq(HDC hDC, int erase, RECT& rect, int number);
#endif

  // Отобразить пользовательскую карту по номеру
  void PaintSite(HDC hDC, int erase, RECT& rect, int number,
                 int viewscreen = 1);                            

  // Установить пошаговый вывод DIB в окно
  // (1 - короткий период, 0 - длинный)
  // Возвращает предыдущее значение
  int SetPaintStep(int flag);

  // Запросить значение шага вывода
  int GetPaintStep();                       

  // Инициализировать палитру окна
  int SetupPalette();

  // Очистить область рисования в DIB
  void _fastcall ClearDibRect(char* lpdib, COLORREF color); 

#ifdef WIN32API  
  // Отобразить открытые данные на устройство через DIB
  // принтерными функциями
  int ShowDataDibToDevice(HDC hDC, RECT& rect, int mirror);

  // Отобразить открытые данные в окно через DIB
  // принтерными функциями
  int ShowDataDibToWindow(HDC hDC, RECT& rect);

  // Отобразить открытые карты в DIB
  int ShowSitesToDib(RECT* rect);                       
#endif

// protected:

  // Отобразить данные или объект в Image, используя DIB
  void PaintDibToImage(char *lpImage,
                         int ImageAreaWidth,int ImageAreaHeight,
                         int erase, RECT& Rect,
                         TObjectInfo* object=0);


  // Отобразить данные в 32-битовую область
  //   dib      - указатель на нижнюю строку области
  //   dibwidth - ширина области (в байтах)
  void PaintDibToDib32(char* dib, int dibwidth, int dibheight,
                       RECT& rect);                     

  // Отобразить данные или объект на устройство
  void PaintDevice(HDC hDC, int erase, RECT& rect, TMapObject* object = 0,
                   int dontclip = 0, 
#ifdef WIN32API  
		   PRINTPARM* parm = 0);
#else
		   void* parm = 0);
#endif

  // Отобразить образец вида объекта, используя DIB
  void PaintExampleObjectDib(HDC hDC, RECT& rect, int number,
                             char* parm, POLYDATAEX* data);

  // Отобразить образец вида объекта на устройство
  void PaintExampleObjectDevice(HDC hDC, RECT& rect, int number,
                                char* parm, POLYDATAEX* data);

  // Запретить параллельный доступ к глобальным
  // переменным для визуализации
  void Lock();

  // Разрешить параллельный доступ к глобальным
  // переменным для визуализации
  void UnLock();

 public:

  TMapPalette MapPalette;            // Палитра отображаемой карты

  HPALETTE ViewPalette;              // Идентификатор палитры окна

#ifdef WIN32API                      
  HWND EventHandle;                  // Идентификатор окна для сообщениях о событиях
  int  EventFlag;                    // Флаг типов событий
#endif
};

// Инициализация объекта рисования
// Замена названия на mppInit необходима для избежания совпадений
// имен функций в других проектах
void _fastcall mppInit(TMapPaint* mp);   

// Освобождение объекта рисования
void _fastcall mpFree(TMapPaint* mp);

// Функция изменения цвета фона
void _fastcall mpSetBackGround(TMapPaint * mp, COLORREF background);

// Функция возвращает габариты всего изображения в пикселах
//   (X,Y в координатах Windows)
void _fastcall mpGetPictureBorder(TMapPaint * mp, long int * x,
                                                  long int * y);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++   ОСНОВНЫЕ ФУНКЦИИ РИСОВАНИЯ   ++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Отобразить объект в Image
void _fastcall mpPaintObjectToImage(TMapPaint* mp, char *lpImage,
                                    int ImageAreaWidth, int ImageAreaHeight,
                                    int erase, RECT* rect,
                                    TMapObject* object);

// Отобразить образец вида объекта
void _fastcall mpPaintExampleObject(TMapPaint* mp, HDC hDC, RECT* rect, int erase,
                                    int number, char* parm, POLYDATAEX* data);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++   ФУНКЦИИ РИСОВАНИЯ В DIB   +++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Отобразить данные или объект в Image, используя DIB
void _fastcall mpPaintDibToImage(TMapPaint* mp, char* lpImage,
                                 int ImageAreaWidth, int ImageAreaHeight,
                                 int erase, RECT* Rect,
                                 TMapObject* object);

// Отобразить образец вида объекта, используя DIB
void _fastcall mpPaintExampleObjectDib(TMapPaint* mp, HDC hDC, RECT* Rect,
                                       int number, char* parm, POLYDATAEX* data);

// Отобразить карту обстановки по номеру
void _fastcall mpPaintSite(TMapPaint* mp, HDC hDC, int value,           
                           RECT* Rect, int number, int viewscreen);

// Отобразить растр по номеру
void _fastcall mpPaintRst(TMapPaint* mp, HDC hDC, int value, RECT* Rect, 
                          int number, int flagClear);

// Отобразить матрицу по номеру
void _fastcall mpPaintMtr(TMapPaint* mp, HDC hDC, int value,             
                          RECT* Rect, int number);

#ifndef HIDEMTL          
// Отобразить матрицу слоев по номеру
void _fastcall mpPaintMtl(TMapPaint* mp, HDC hDC, int, RECT* Rect, int number);
#endif

#ifndef HIDEMTQ         

// Отобразить матрицу качеств по номеру
void _fastcall mpPaintMtq(TMapPaint* mp, HDC hDC, int erase,
                          RECT* Rect, int number);
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++   ФУНКЦИИ РИСОВАНИЯ НА УСТРОЙСТВО   ++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// Отобразить данные или объект на устройство
void _fastcall mpPaintDevice(TMapPaint* mp, HDC hDC, int erase, RECT* Rect,
                             TMapObject* object, int dontclip,
#ifdef WIN32API  
			     PRINTPARM* parm);
#else
			     void* parm);			     
#endif

// Отобразить образец вида объекта на устройство
void _fastcall mpPaintExampleObjectDevice(TMapPaint* mp, HDC hDC, RECT* Rect, int erase,
                                          int number, char* parm, POLYDATAEX* data);

// Отобразить объект
int _fastcall mpPaintUserObject(TMapPaint* mp, HDC hDC, RECT* Rect,
                                PAINTPARM* image, POLYDATAEX* data, TMap* map);

// Выделить на карте объекты, удовлетворяющие заданным условиям
// rect - координаты фрагмента карты (Draw) в изображении (Picture)
// select - условия отбора объектов,
// color  - цвет, которым будут выделяться объекты на карте
void _fastcall mpPaintSelectObjects(TMapPaint* mp, HDC hDC, RECT* Rect,
                                    int mapnumber, COLORREF color,
                                    TMapSelect * select);
#ifdef WIN32API
// Сохранить изображение карты в виде векторного SCRIPT-описания
// в базовом масштабе карты и текущем составе отображения
// При ошибке возвращает ноль
int mpPaintToScript(TMapPaint * mp, double hprecision, double vprecision,
                    SCRIPTTABLEEX * table);
#endif                    

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++   ФУНКЦИИ ФОРМИРОВАНИЯ ПАЛИТРЫ   ++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Инициализировать палитру окна
int _fastcall mpSetupPalette(TMapPaint* mp);

// Обновить палитру окна
int _fastcall mpUpdatePalette(TMapPaint* mp, HWND hwnd, int mode);

// Установить стиль палитры матрицы
void _fastcall mpSetMtrPaletteStyle(TMapPaint* mp, int style);

#endif  //MAPPAINT_H

