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
         TMGrid(TWindow* parent,     // ��������
                     int x, int y,   // ���������� ����.-���. ���� Grid-a
                     int w,          // ������ �������
                     int h,          // ������ �������
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

    // ��� ��������� ����� �������� � ������� GRID        
    // ���� ���������� 0 - ���� ������� �������
    // key - ��������� ������
    // text - ������� ������ � Edit
    virtual int KeyDown(uint /*key*/, char * /*text*/) { return 0; }

    // ��� ��������� ����� �������� � ������� GRID
    // ���� ���������� 0 - ���� ������� �������
    // key - ��������� ������
    // text - ������� ������ � Edit
    virtual int KeyChar(uint /*key*/, char * /*text*/) { return 0; }

    // ���������� �������� �������������� ���� ListBox-a.
    // ���������� �������� � TDialog::CmOk() :
    //              ...
    //        if(MGrid->IsOk())
    //        {
    //          TDialog::CmOk();
    //        }
    //              ...
    bool IsOk(bool flag = true);

    bool IsCancel(bool flag = true);

    // �������� ������� � ���������� item
    virtual int Add(const char* item, bool sort = false, int length = 256);

    // �������� ������ �� ���������� string[]
    virtual int AddString(const char* string[],  int adjust = 1);

    // ������������ Scroller-�
    void AdjustScroller(void);

    // �������� �������� ����������
    int CheckSorted();

    // �������� Grid
    void ClearList();

    // ���������� ������ �������
    bool ColumnWidth(long column, long width);

    // ���������� ��������� �������
    bool ColumnHeader(long column, const char far* text);

    // ������� �������
    virtual bool Delete(int column);

    // ������� ������
    virtual int DeleteString(int index);

    // ����� ������ � ������� �������
    int FindExactString(const char far* str, int index, int column);
    int FindString(const char far* str, int index, int column);

    // ����� ������� ��� �������� ������
    int FindColumn(TNewListBox * list);

    // ���������� ���������� �������
    int GetColumnCount(void);

    // ���������� ���������� �����
    int GetItemCount(void);

    // ���������� 32-� ������ �������� ��������� � ��������� Grid-a
    uint32 GetItemData(int index, int column);

    // ���������� ������ ��������
    int GetItemHeight(int index);

    // ���������� ��������� �������
    int GetSelIndex(void);

    // ��������� �������� ����
    int GetString(long index, long column, char* string);

    // ���������� ����� �������� �������� ��������
    int GetTopIndex();

    // ������ �� ������� ������� ������ ���� � ���� � ����������
    virtual void GridHandler(TNewListBox* lb, long index, long msg);

    // ����� ����� � i ������� � j �������
    void GridHandlerColumn(int i, long index);

    // �������� ������
    virtual int InsertString(const char* str[], int index);

    // �����������/��������� ����������� �������������� ��������� �������
    bool IsEditable(int column, bool flag);
    bool IsEditable(int column);

    // ����������� Grid-�
    bool MoveWindow(int x, int y, int w, int h, bool repaint = false);
    bool MoveWindow(const TRect& rect, bool repaint = false);

    // ���������� ������ ��������
    int PageSize();

    // ����������/���������� ����� � ������� column
    int  GetFocusEx(void);
    HWND SetFocus(int column);
    HWND SetFocus(){return SetFocus(0);}

    // ���������� 32-� ������ �������� ��������� � ��������� Grid-a
    int SetItemData(int index, int column, uint32 itemData);

    int SetItemHeight(int height);

    // ���������� ��������� �������
    int SetSelIndex(int index);

    // ���������� �������� ����
    void SetString(long index, long column, const char* string);

    // ���������� ����� �������� �������� ��������
    int SetTopIndex(int index);

    void SetValidator(TValidator* valid, long column);

  protected:
     typedef TIArrayAsVector<TNewListBox> TListBoxArray;

    TListBoxArray&   MGrid;
    TColumnHeader*   lpColHdr;

  private:
    char             String[256]; // ������ ��� �������� ��������� � Grid
    int              ItemHeight;
    bool             Sorted;      // Grid ��� ������������ ����� - ��� ��� ������

  public:
    long             lbStyle;     // ����� ListBox-��
    long             lbExStyle;   // ���������� ����� ListBox-��

    char             FontName[64]; // �����
    TFont*           Font;

    TNewListBox*     EditListBox;  // ������������� ListBox

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

    // ��������� ����� ���� ��� ��������������
    int GetEditLength();

    // ���������� ����� ���� ��� ��������������
    int SetEditLength(int length);

    // �������������� �������� GRID                      
    void EditOpen(int index);
    void EditClose(int code);

  private:
    bool          Sorted;      // ������� ���������� ������
    int           EditLength;  // ��������� ����� ������ ��� �������������� < 256

  public:
    bool          IsEditable;
    TValidator*   Validator;
    TFont*        Font;
    TMGrid*       ParentGrid;

    TEditEnterEx* Edit;        // ���� �������������� ����� Grid-�
    int           EditIndex;

  DECLARE_RESPONSE_TABLE(TNewListBox);
};


//******************************************************************************
//******************************************************************************
//******************************************************************************
//              ����� ��� �������������� ����� Grid-�
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
