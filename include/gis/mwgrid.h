#if !defined(MWGRID_H)
  #define    MWGRID_H

#ifndef STRICT
  #define STRICT
#endif

#include "MWmacro.h"

#include <owl\colmnhdr.h>
#include <owl\edit.h>
#include <owl\listbox.h>
#include <owl\validate.h>
#include <owl\gdiobjec.h>
#include <classlib\arrays.h>

#define UM_LBCLICKED WM_USER+22300
#define UM_SBCLICKED WM_USER+22301

class _DLLCLASSTASK TNewListBox;
class _DLLCLASSTASK TEditEnterEx;

class _OWLCLASS TColumnHeader;
class _OWLCLASS THdrNotify;
class _OWLCLASS TModule;

class _DLLCLASSTASK TMGrid : public TWindow
{
  friend TNewListBox;
  public:
         TMGrid(TWindow* parent,     // Родитель
                     int x, int y,   // Координаты верх.-лев. угла Grid-a
                     int w,          // Высота колонок
                     int h,          // Высота колонок
                TModule* module = 0,
                     const char * fontname = 0);
        ~TMGrid(void);

    void SetupWindow(void);

    virtual void EvHeaderItemChanged(THdrNotify& nmHdr);

    virtual void EvHeaderItemClick(THdrNotify& nmHdr);         
    virtual LRESULT EvListBoxClicked(WPARAM index, LPARAM);

    virtual LRESULT EvScrollBarClicked(WPARAM index, LPARAM);

    void EvVScroll(uint scrollCode, uint thumbPos, HWND hWndCtl);

    void EvKeyDown(uint key, uint repeatCount, uint flags);

    // Для перехвата ввода символов в ячейках GRID        
    // Если возвращает 0 - ввод штатным образом
    // key - введенный символ
    // text - текущая строка в Edit
    virtual int KeyDown(uint /*key*/, char * /*text*/) { return 0; }

    // Для перехвата ввода символов в ячейках GRID
    // Если возвращает 0 - ввод штатным образом
    // key - введенный символ
    // text - текущая строка в Edit
    virtual int KeyChar(uint /*key*/, char * /*text*/) { return 0; }

    // Завершение процесса редактирования поля ListBox-a.
    // Необходимо добавить в TDialog::CmOk() :
    //              ...
    //        if(MGrid->IsOk())
    //        {
    //          TDialog::CmOk();
    //        }
    //              ...
    bool IsOk(bool flag = true);

    bool IsCancel(bool flag = true);

    // Добавить колонку с заголовком item
    virtual int Add(const char* item, bool sort = false, int length = 256);

    // Добавить строку со значениями string[]
    virtual int AddString(const char* string[],  int adjust = 1);

    // Выравнивание Scroller-а
    void AdjustScroller(void);

    // Проверка признака сортировки
    int CheckSorted();

    // Очистить Grid
    void ClearList();

    // Установить ширину колонки
    bool ColumnWidth(long column, long width);

    // Установить заголовок колонки
    bool ColumnHeader(long column, const char far* text);

    // Удалить колонку
    virtual bool Delete(int column);

    // Удалить строку
    virtual int DeleteString(int index);

    // Поиск строки в заданой колонке
    int FindExactString(const char far* str, int index, int column);
    int FindString(const char far* str, int index, int column);

    // Поиск колонки для элемента списка
    int FindColumn(TNewListBox * list);

    // Определить количество колонок
    int GetColumnCount(void);

    // Определить количество строк
    int GetItemCount(void);

    // Определить 32-х битное значение связанное с элементом Grid-a
    uint32 GetItemData(int index, int column);

    // Определить высоту элемента
    int GetItemHeight(int index);

    // Определить выбранный элемент
    int GetSelIndex(void);

    // Запросить значение поля
    int GetString(long index, long column, char* string);

    // Определить идекс верхнего видимого элемента
    int GetTopIndex();

    // Отклик на двойное нажатие кнопки мыши и ввод с клавиатуры
    virtual void GridHandler(TNewListBox* lb, long index, long msg);

    // вызов ввода в i колонке и j строчке
    void GridHandlerColumn(int i, long index);

    // Вставить строку
    virtual int InsertString(const char* str[], int index);

    // Определение/Установка возможности редактирования элементов колонки
    bool IsEditable(int column, bool flag);
    bool IsEditable(int column);

    // Перемещение Grid-а
    bool MoveWindow(int x, int y, int w, int h, bool repaint = false);
    bool MoveWindow(const TRect& rect, bool repaint = false);

    // Определить размер страницы
    int PageSize();

    // Определить/Установить фокус в колонку column
    int  GetFocusEx(void);
    HWND SetFocus(int column);
    HWND SetFocus(){return SetFocus(0);}

    // Установить 32-х битное значение связанное с элементом Grid-a
    int SetItemData(int index, int column, uint32 itemData);

    int SetItemHeight(int height);

    // Установить выбранный элемент
    int SetSelIndex(int index);

    // Установить значение поля
    void SetString(long index, long column, const char* string);

    // Установить идекс верхнего видемого элемента
    int SetTopIndex(int index);

    void SetValidator(TValidator* valid, long column);

  protected:
     typedef TIArrayAsVector<TNewListBox> TListBoxArray;

    TListBoxArray&   MGrid;
    TColumnHeader*   lpColHdr;

  private:
    char             String[256]; // Строка для передачи изменений в Grid
    int              ItemHeight;
    bool             Sorted;      // Grid был отсортирован ранее - еще раз нельзя

  public:
    long             lbStyle;     // Стиль ListBox-ов
    long             lbExStyle;   // Расширеный стиль ListBox-ов

    char             FontName[64]; // Шрифт
    TFont*           Font;

    TNewListBox*     EditListBox;  // Редактируемый ListBox

  DECLARE_RESPONSE_TABLE(TMGrid);
};

/*******************************************************************************
********************************************************************************
************************ class TNewListBox *************************************
********************************************************************************
*******************************************************************************/
class _DLLCLASSTASK TNewListBox : public TListBox
{
  public:
         TNewListBox(TMGrid* parent, int Id, int x, int y, int w, int h, TModule* module = 0);
         TNewListBox(TMGrid* parent, int resourceId, TModule* module = 0);
         ~TNewListBox();

    void SetupWindow(void);

    void EvChar(uint key, uint repeatCount, uint flags);
    void EvLButtonDown(UINT, TPoint& point);
    void EvLButtonDblClk(uint modKeys, TPoint& point);
    void EvVScroll(uint scrollCode, uint thumbPos, HWND hWndCtl);

    void EvKeyUp(uint key, uint repeatCount, uint flags);     
    void EvKeyDown(uint key, uint repeatCount, uint flags);

    void IsSorted(bool sorted) {Sorted = sorted;}
    bool IsSorted(void)        {return Sorted;}

    // Запросить длину поля при редактировании
    int GetEditLength();

    // Установить длину поля при редактировании
    int SetEditLength(int length);

    // Редактирование элемента GRID                      
    void EditOpen(int index);
    void EditClose(int code);

  private:
    bool          Sorted;      // Признак сортировки списка
    int           EditLength;  // Требуемая длина строки при редактировании < 256

  public:
    bool          IsEditable;
    TValidator*   Validator;
    TFont*        Font;
    TMGrid*       ParentGrid;

    TEditEnterEx* Edit;        // Поле редактирования полей Grid-а
    int           EditIndex;

  DECLARE_RESPONSE_TABLE(TNewListBox);
};


//******************************************************************************
//******************************************************************************
//******************************************************************************
//              Класс для редактирования полей Grid-а
//******************************************************************************
//******************************************************************************
//******************************************************************************
class _DLLCLASSTASK TEditEnterEx : virtual public TEdit
{
  public:
          TEditEnterEx(TNewListBox* parent, int Id = 0, const char far *text = 0, int x = 0,
                       int y = 0, int w = 20, int h = 20, unsigned int textLen = 260,
                       bool multiline = false, TModule* module=0)
                      :TEdit(parent, Id, text, x, y, w, h, textLen, multiline, module)
                      {ListBox = parent;}
         ~TEditEnterEx() {Validator = 0;}

     void SetupWindow();

     void EvChar(uint key, uint repeatCount, uint flags);

     void EvKeyDown(uint key, uint repeatCount, uint flags);

     void EvKillFocus(HWND hWndGetFocus);

     void SetValidator(TValidator* validator)
          { Validator = validator; }

  private:

  TNewListBox * ListBox;
  int           Modify;               

  public:

  DECLARE_RESPONSE_TABLE(TEditEnterEx);
};
#endif     //MWGRID_H
