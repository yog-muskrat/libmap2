
#ifndef MWCONTRL_H
#define MWCONTRL_H

#ifndef OWL_BUTTONGA_H
  #include <owl\buttonga.h>
#endif

#ifndef OWL_BUTTON_H
  #include <owl\button.h>
#endif

#ifndef OWL_COMBOBOX_H
  #include <owl\combobox.h>
#endif

#ifndef OWL_DIALOG_H
  #include <owl\dialog.h>
#endif

#ifndef OWL_EDIT_H
  #include <owl\edit.h>
#endif

#ifndef OWL_GDIOBJEC_H
  #include <owl\gdiobjec.h>
#endif

#ifndef OWL_LISTBOX_H
  #include <owl\listbox.h>
#endif

#ifndef OWL_LISTWIND_H
  #include <owl\listwind.h>
#endif

#ifndef OWL_STATIC_H
  #include <owl\static.h>
#endif

#ifndef OWL_DOCKING_H
  #include <owl\docking.h>
#endif

#ifndef OWL_VALIDATE_H
  #include <owl\validate.h>
#endif

#ifndef OWL_TREEWIND_H
  #include <owl\treewind.h>
#endif

#ifndef MWMACRO_H
  #include "MWmacro.h"
#endif

#ifndef MAPVIEW_RH
  #include "mapview.rh"
#endif

#ifndef MAPLIB_H
  #include "maplib.h"              
#endif

typedef struct STRINGLIST
{
  char* String;    // Указатель на массив строк
  int   Length;    // Длина строки
  int   Count;     // Количество строк
}
  STRINGLIST;

// Возвращает высоту шрифта в пикселах экрана
int FontHeightPix();

/********************************************** 
// -----------------------------------------------------------------------------
//  Класс окна TStatic с переопределенным шрифтом
// -----------------------------------------------------------------------------
class _DLLCLASSTASK TStaticEdit : public TControl
{
 public:
  TStaticEdit(TWindow* parent, int id, const char far* title,
              int x, int y, int w, int h, unsigned int textLen = 0,
              TModule* module = 0);
  TStaticEdit(TWindow* parent, int resId, unsigned int textLen=0, TModule* module=0);
 ~TStaticEdit();

  void SetupWindow();

  // Отобразить текст
  void EvPaint();
  void Paint(TDC& dc, bool erase, TRect& rect);

  // Редактирование поля с подтверждением (клавишей Enter)
  int Edit(TValidator* validator);

  // Редактирование с фильтром "0-9"
  int EditInt();

  // Редактирование с фильтром "0-9-"
  // в диапазоне значений от min до max     
  int EditInt(int min,int max);

  // Редактирование с фильтром "0-9.Ee+-"
  int EditFloat();

  // Редактирование полного имени файла
  //  name - указатель на исходное полное имя (размером MAX_PATH)
  // Результат записывается в name
  // (в окно помещается имя, усеченное по ширине окна)
  int EditFileName(char* name);

  // Установить имя файла в окно с усечением по ширине окна
  void SetFileName(char* name);

  int   GetText(char far* str, int maxChars);
  void  SetText(const char far* str);

  virtual void Clear() { SetText(""); }

  uint  GetTextLimit() const;
  void  SetTextLimit(uint textlimit);

  void SetFont(LOGFONT * font);                                  
 protected:

  TModule* Module;
  TFont  * Font;
  char     Title[260];
  uint     TextLimit;  // Maximum length of text in edit control

  DECLARE_RESPONSE_TABLE(TStaticEdit);

};

//
// Retrieve the current text in the control.
//
inline int TStaticEdit::GetText(char far* str, int maxChars)
{
  if (str != 0)
   strncpy(str, Title, maxChars);
  return 1;
}

//
// Set the text in the control.
//
inline void TStaticEdit::SetText(const char far* str)
{
  strcpy(Title, str);
  SetWindowText(str);  // В неактивном окне - высвечивается этот текст 
  Invalidate();
}

//
// Return the maximum number of characters that can be displayed in the control.
//
inline uint TStaticEdit::GetTextLimit() const {
  return TextLimit;
}

//
// Set the maximum number of characters to display in the control.
//
inline void TStaticEdit::SetTextLimit(uint textlimit) {
  TextLimit = textlimit;
}
********************************************************************************/

// -----------------------------------------------------------------------------
//  Класс окна TStatic с переопределенным шрифтом
// -----------------------------------------------------------------------------
class _DLLCLASSTASK TStaticEx : public TStatic
{
 public:
  TStaticEx(TWindow* parent, int id, const char far* title,
            int x, int y, int w, int h, unsigned int textLen = 0,
            TModule* module = 0);
  TStaticEx(TWindow* parent, int resId, unsigned int textLen=0, TModule* module=0);
 ~TStaticEx() {delete Font;}

  void SetupWindow()
      {
        TStatic::SetupWindow();
        SetWindowFont(*Font, 0);
      }

/***********************************************************************
  // Редактирование поля с подтверждением (клавишей Enter)
  int Edit(TValidator* validator);

  // Редактирование с фильтром "0-9"
  int EditInt();

  // Редактирование с фильтром "0-9-"
  // в диапазоне значений от min до max     
  int EditInt(int min,int max);

  // Редактирование с фильтром "0-9.Ee+-"
  int EditFloat();

  // Редактирование полного имени файла
  //  name - указатель на исходное полное имя (размером MAX_PATH)
  // Результат записывается в name
  // (в окно помещается имя, усеченное по ширине окна)
  int EditFileName(char* name);
**************************************************************************/

  // Установить имя файла в окно с усечением по ширине окна
  void SetFileName(char* name);

 private:

  TModule* Module;
  TFont* Font;
};

// -----------------------------------------------------------------------------
//  Класс окна TEdit с переопределенным шрифтом и возможностью вставки ссимвола  
//                   по  Insert
// -----------------------------------------------------------------------------
class _DLLCLASSTASK TEditEx : public TEdit
{
 public:

  TEditEx(TWindow* parent, int Id, const char far *text,
          int x, int y, int w, int h, uint textLen = 0,
          bool multiline = false, TModule* module = 0,LOGFONT * font = 0);       
  TEditEx(TWindow* parent, int resId, unsigned int textLen=0, TModule* module=0,
          LOGFONT * font = 0);                                                   
 ~TEditEx();                                                                     

  void SetupWindow();                                                            

  // Изменить фонт строки
  void SetFont(LOGFONT * font);             

  // Включить - выключить вставку символа
  // 1 - включить
  void SetInsert(int ins);
  void EvKeyDown(uint key,uint repeatCount,uint flags);

 private:

  TFont* Font;
  int    IsSetFont;                         // Признак установки специального фонта
  int    IsInsert;                          // 1 - можно вставлять символы
  DECLARE_RESPONSE_TABLE(TEditEx);
};


// -----------------------------------------------------------------------------
//  Класс окна TEdit с переопределенным шрифтом и реакцией на нажатие клавиши
// -----------------------------------------------------------------------------
class _DLLCLASSTASK TEditPress : public TEditEx
{
 public:

  TEditPress(TWindow* parent, int Id, const char far *text,
             int x, int y, int w, int h, unsigned int textLen,
             bool multiline, TModule* module,LOGFONT * font = 0):
     TEditEx(parent, Id, text, x, y, w, h, textLen, multiline, module,font){}

  TEditPress(TWindow* parent, int resId, unsigned int textLen = 0,
             TModule* module = 0,LOGFONT * font = 0) :
     TEditEx(parent, resId, textLen, module,font) {}

  private:

  void EvLButtonDown(uint modKeys, TPoint& point)
      {Parent->HandleMessage(WM_PRESS, 0,(LPARAM)this->HWindow);}

  DECLARE_RESPONSE_TABLE(TEditPress);
};

// -----------------------------------------------------------------------------
//  Класс окна TListBox с переопределенным шрифтом
// -----------------------------------------------------------------------------
class _DLLCLASSTASK TListBoxEx : public TListBox
{
 public:

  TListBoxEx(TWindow* parent, int Id, int x, int y, int w, int h,
             TModule* module = 0, LOGFONT * font = 0);
  TListBoxEx(TWindow* parent, int resId, TModule* module = 0, LOGFONT * font = 0);
 ~TListBoxEx() {delete Font;}

  void SetupWindow()
      {
        TListBox::SetupWindow();
        SetWindowFont(*Font, 0);
      }

  // Изменить фонт строки
  void SetFont(LOGFONT * font);             

  // Обработка ESC
  void EvKeyDown(uint key,uint repeatCount,uint flags);      

 private:

  TFont* Font;
  int    IsSetFont;                         // Признак установки специального фонта
  int    IsActive;

  DECLARE_RESPONSE_TABLE(TListBoxEx);
};

// -----------------------------------------------------------------------------
//  Класс окна TListBox с переопределенным шрифтом и функцией отображения строк
//  Для его правильной работы в ресурсах нужно установить для данного элемента
//  атрибут LBS_OWNERDRAWFIXED (установка в конструкторе не помогает :-(
// -----------------------------------------------------------------------------
class _DLLCLASSTASK TListBoxFontEx : public TListBoxEx     
{
 public:

  TListBoxFontEx(TWindow* parent, int Id, int x, int y, int w, int h,
                 TModule* module = 0, LOGFONT * font = 0) :
      TListBoxEx(parent, Id, x, y, w, h, module, font)
        { Attr.Style |= (LBS_OWNERDRAWFIXED | LBS_HASSTRINGS); }

  TListBoxFontEx(TWindow* parent, int resId, TModule* module = 0, LOGFONT * font = 0) :
      TListBoxEx(parent, resId, module, font)
        { Attr.Style |= (LBS_OWNERDRAWFIXED | LBS_HASSTRINGS); }

  // Отображение строк с подменой шрифта
  void DrawItem(DRAWITEMSTRUCT far& drawInfo);
};

// -----------------------------------------------------------------------------
//  Класс окна TListWindow с переопределенным шрифтом
// -----------------------------------------------------------------------------
class _DLLCLASSTASK TListWindowEx : public TListWindow
{
 public:

  TListWindowEx(TWindow* parent, int Id, int x, int y, int w, int h,
                TModule* module = 0, LOGFONT * font = 0);
  TListWindowEx(TWindow* parent, int resId, TModule* module = 0, LOGFONT * font = 0);
  ~TListWindowEx() {delete Font;}

 void SetupWindow()
      {
        TListWindow::SetupWindow();
        SetWindowFont(*Font, 0);
      }

 // Изменить фонт строки
 void SetFont(LOGFONT * font);             

 private:

  TFont* Font;
  int    IsSetFont;                         // Признак установки специального фонта
};


// -----------------------------------------------------------------------------
//  Класс окна TComboBox с переопределенным шрифтом
// -----------------------------------------------------------------------------
class _DLLCLASSTASK TComboBoxEx : public TComboBox
{

 public:
  TComboBoxEx(TWindow* parent, int Id, int x, int y, int w, int h,
              uint32 style, uint textLimit, TModule* module = 0);
  TComboBoxEx(TWindow* parent, int resId, uint textLen = 0, TModule* module = 0);
  ~TComboBoxEx() {delete Font;}

 void SetupWindow()
      {
        TComboBox::SetupWindow();
        SetWindowFont(*Font, 0);
      }

 private:

  TFont* Font;
};


// -----------------------------------------------------------------------------
//  Класс окна TEdit с переопределенным шрифтом и реакцией на клавишу Enter
// -----------------------------------------------------------------------------
class _DLLCLASSTASK TEditEnter : public TEditEx
{
 public:

  TEditEnter(TWindow* parent, int Id, const char far *text,
             int x, int y, int w, int h, unsigned int textLen,
             bool multiline, TModule* module,LOGFONT * font = 0):       
     TEditEx(parent, Id, text, x, y, w, h, textLen, multiline, module,font)
            {IsOk = FALSE;}

  TEditEnter(TWindow* parent, int resId, unsigned int textLen = 0,
             TModule* module = 0,LOGFONT * font = 0) :
     TEditEx(parent, resId, textLen, module,font) {IsOk = FALSE;}   

  // Нажата клавиша мыши Ok
  void Ok() {IsOk = TRUE;}

 private:

  // Обработка возможности закрытия диалога
  bool CanClose();

 public :

  int IsOk;  // Флаг нажатия клавиши мыши Ok
};


/*************************************** 
// -----------------------------------------------------------------------------
//  Класс окна TEnter с переопределенным шрифтом и закрытием по клавишам
//              ESC и ENTER
//  Использовать Execute ( используется как модальный диалог )
// -----------------------------------------------------------------------------
class _DLLCLASSTASK TEnter : public TEditEx
{
 public:

  TEnter(TWindow* parent, int Id, const char far* text,
         TRect& rect, unsigned int textLimit,
         bool multiline = false, TModule* module = 0, LOGFONT * font= 0):
   TEditEx(parent, Id, text,
         rect.left, rect.top, rect.Width(), rect.Height(),
         textLimit, multiline, module, font)                     
  {
    ModifyStyle(0, ES_MULTILINE | ES_WANTRETURN);
    Text = text;
    TextLen  = textLimit;
  }

  TEnter(TWindow* parent, int Id, const char far* text,
         int x, int y, int w, int h, unsigned int textLimit,
         bool multiline = false, TModule* module = 0,LOGFONT * font= 0):       
   TEditEx(parent, Id, text, x, y, w, h, textLimit, multiline, module,font)
  {
    ModifyStyle(0, ES_MULTILINE | ES_WANTRETURN);
    Text = text;
    TextLen  = textLimit;
  }

  void SetupWindow();
  void EvKeyDown(uint key,uint repeatCount,uint flags);
  void EvKillFocus(HWND hWndGetFocus);
  void EvChildInvalid(HWND hWND);                             

 public:
  const char far* Text;
  unsigned int TextLen;
  DECLARE_RESPONSE_TABLE(TEnter);
};

//-----------------------------------------------------------------
// Класс окна TEdit наложенный на TStatic с переопределенным шрифтом
// и закрытием по клавишам ESC и ENTER (использовать Execute)
//-----------------------------------------------------------------
class _DLLCLASSTASK TEditStaticEx : public TEditEx
{
 public:

  TEditStaticEx(TStaticEx* parent) :
        TEditEx(parent,100,"",0,0,0,0,parent->GetTextLimit(),false,0)
  {
    tStatic = parent;
    tEdit   = 0;
    ModifyStyle(0, ES_MULTILINE | ES_WANTRETURN);
  }

  TEditStaticEx(TStaticEdit* parent) :
        TEditEx(parent,100,"",0,0,0,0,parent->GetTextLimit(),false,0)
  {
    tEdit   = parent;
    tStatic = 0;
    ModifyStyle(0, ES_MULTILINE | ES_WANTRETURN);
  }

 protected:

  void SetupWindow();
  void EvKillFocus(HWND hWndGetFocus);
  void EvKeyDown(uint key,uint repeatCount,uint flags);

  char Text[MAX_PATH];
  TStaticEx   * tStatic;
  TStaticEdit * tEdit;
  DECLARE_RESPONSE_TABLE(TEditStaticEx);
};

********************************************************************/

// -----------------------------------------------------------------------------
//  Класс окна TListWindow с переопределенным шрифтом
//  и реакцией на двойное нажатие левой клавиши мыши
// -----------------------------------------------------------------------------
class _DLLCLASSTASK TListWindowDblClk : public TListWindowEx
{
 public:

  TListWindowDblClk(TWindow* parent, int Id, int x, int y, int w, int h,
                    TModule* module = 0):
      TListWindowEx(parent, Id, x, y, w, h, module){}

  TListWindowDblClk(TWindow* parent, int resId, TModule* module = 0):
      TListWindowEx(parent, resId, module){}

  private:

  void EvLButtonDblClk(uint modKeys, TPoint& point);

  DECLARE_RESPONSE_TABLE(TListWindowDblClk);
};



// -----------------------------------------------------------------------------
//  Класс окна TTreeWindow с переопределенным шрифтом
//  и реакцией на двойное нажатие левой клавиши мыши    
// -----------------------------------------------------------------------------
class TTreeWindowDblClk : public TTreeWindow
{
 public:

  TTreeWindowDblClk(TWindow* parent, int Id, int x, int y, int w, int h,
                    uint32 style = 0, TModule* module = 0):
        TTreeWindow(parent, Id, x, y, w, h, style, module){}

  TTreeWindowDblClk(TWindow* parent, int resId, TModule* module = 0):
        TTreeWindow(parent, resId, module){}

  private:

  void EvLButtonDblClk(uint /*modKeys*/, TPoint&/* point*/);

  DECLARE_RESPONSE_TABLE(TTreeWindowDblClk);
};

class _DLLCLASSTASK TEditPro;
class _DLLCLASSTASK TComboBoxPro;

#define WMU_ACTIVEPRO (WM_USER + 3)
#define WMU_CLEARPRO  (WM_USER + 4)

// -----------------------------------------------------------------------------
//  Класс окна TDialogPro с реакцией
//  на клавиши  ESC и ENTER                     
// -----------------------------------------------------------------------------
class _DLLCLASSTASK TDialogPro : public TDialog
{
 public:

 TDialogPro(TWindow * parent, TResId resId, TModule * module);

 // Уведомление об изменении значения элемента редактирования
 virtual void UpdateDialog(TEditPro * ) {}

 // Уведомление об отказе от редактирования
 virtual void EditEscape(TEditPro * ) {}                     

 // Уведомление об изменении значения элемента списка
 virtual void UpdateComboBox(TComboBoxPro * ) {}

 // Запросить имеется ли активный элемент редактирования
 int IsControlActive()
    { return ((EditActive || ComboBoxActive) != 0); }

 // Установить активный элемент редактирования
 // Уведомление о том, что элемент редактирования активизировали
 virtual int SetActiveEdit(TEditPro * edit);               

 // Установить активный элемент списка
 void SetActiveComboBox(TComboBoxPro * combobox);

 void ClearActiveControl();

 protected :

 // Обработка ESC, ENTER
 LRESULT EvCommand(uint id, HWND hwnd, uint notify);

 public:

 TComboBoxPro * ComboBoxActive; // Active ComboBox
 int            ComboBoxIndex;  // ComboBox Index before Editing

 TEdit      * EditActive;       // Active Edit Control
 char EditText[260];            // Copy of Edit Text before Editing
};

// -----------------------------------------------------------------------------
//  Класс окна TEditPro с переопределенным шрифтом и реакцией
//  на клавиши  ESC и ENTER                     
// -----------------------------------------------------------------------------
class _DLLCLASSTASK TEditPro : public TEditEx
{
 public:

    TEditPro(TDialogPro*   parent,
             int           resourceId,
             uint          textLimit = 0,
             TModule*      module = 0);

    TEditPro(TDialogPro*   parent,
             int Id,       const char * text,
             int x = 0, int y = 0, int w = 20, int h = 20,
             unsigned int textlen = 260, bool multiline = false, TModule* module = 0);

    ~TEditPro();

    void SetupWindow();

    // Запросить идентификатор элемента
    int Ident() { return Attr.Id; }

    void EvSetFocus(HWND hWndLostFocus);
    void EvKillFocus(HWND hWndGetFocus);
    void EvKeyDown(uint key,uint repeatCount,uint flags);

    void EvLButtonDown(uint, TPoint& point);
    void EvRButtonDown(uint, TPoint& point);
    void EvRButtonUp(uint, TPoint& point);
    void EvLButtonDblClk(uint, TPoint& point);

    void SetText(const char far* str);

    // установить валидатор (может быть 0)
    void SetValidatorEx(TValidator* validator)
      {
         //delete (TStreamableBase*)Validator;  // upcast to avoid explicit call to dtor
         Validator   = validator;

         if (validator != 0)
           IsValidator = 1;
         else
           IsValidator = 0;
      }

   // Запретить/разрешить всплывающее меню по правой кнопке
   void AccessPopupMenu(int access = 1);

 public:

    TDialogPro * DialogPro;

    char CopyText[260];                                

    int  IsActive;
    int  IsValidator;                                  
    int  IsRDown;                                      
    int  IsPopup;

    DECLARE_RESPONSE_TABLE(TEditPro);
};


// -----------------------------------------------------------------------------
//  Класс окна TComboBox
// -----------------------------------------------------------------------------
class _DLLCLASSTASK TComboBoxPro : public TComboBox
{

 public:

  TComboBoxPro(TDialogPro* parent, int Id, int x, int y, int w, int h,
               uint32 style, uint textLimit, TModule* module = 0);
  TComboBoxPro(TDialogPro* parent, int resId, uint textLen = 0,
               TModule* module = 0);

  void SetupWindow();

  // Запросить идентификатор элемента
  int Ident() { return Attr.Id; }

  void ActivePro();
  void ClearPro();

 public:

  TDialogPro * DialogPro;

  DECLARE_RESPONSE_TABLE(TComboBoxPro);
};

#ifdef WIN32API

// --------------------------------------------------------------- 
// Выбрать имя файла по заданным условиям
// (обязательно применять при выборе любого имени файла!)
// name     - строка для размещения результата выбора
// namesize - размер строки для результата (MAX_PATH)
// title    - заголовок диалога с учетом языка интерфейса
// filter   - список строк видов файлов
// flags    - управляющие флажки диалога
// index    - текущий номер строки вида файла при открытии диалога
// path     - текущая директория при открытии диалога
// Возвращает номер строки в списке типов файлов (>=0)
// При ошибке или отказе от выбора файла -
// возвращает отрицательное значение
// ---------------------------------------------------------------

long int OpenFileExt(char * name, long int namesize,
                     HWND         parent,
                     const char * title,
                     const char * filter,
                     long  int    flags,
                     long  int    index,
                     const char * path);
#endif

#endif    // CONTROLX_H
