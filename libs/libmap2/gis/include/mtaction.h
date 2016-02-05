
#ifndef MTACTION_H
#define MTACTION_H

#ifndef MTMAPTAS_H
  #include "mtmaptas.h"    // TMapTask
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ ����� "��������� ������� ����������" ++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapAction
{
  public :

  // ������� ������ "���������� �������"
  // ���� ���������� ������ ������ ������ � �������,
  // �� ������ ������ ����������� � Setup() ...
  TMapAction(TMapTask * task,int ident)
     {
       ActionTask  = task;
       ActionIdent = ident;
       MapWindow   = task->GetMapWindow();
       MapDoc      = MapWindow->MapDoc;
     }

  // ������� ���������� � ���������� ��� ������� !!!
  // ���������� ������ ����� �� �����������
  virtual ~TMapAction(){
     MapWindow->SetWindowTitle(0); // ������ ��������� �������� ����
     MapWindow->SetMessage(0);     // ������ ����� � ������ ������
  }

  // ��������� ��������� �����������
  // ���������� ����� ������ ������������
  virtual void Setup() { Comment(); }

  // ��������� ������ ������ �������
  // ��� ������� - �� ����, ����� - ����
  virtual int GetSelectObjectType() { return 1; }

  // ���������� ����� ����������� � ������
  // ���������� ������������� ����� ������������
  virtual void SetTaskAction() { if (Task()) Task()->Action = this; }

  // ������� ����� ����������� � ������
  // ���������� �������������
  virtual void ClearTaskAction() { if (Task()) Task()->Action = 0; }

 /************************************************************
 *                                                           *
 *         ������ ���������� ������������ ������             *
 *                                                           *
 ************************************************************/

public :

  // ������ ������� � ������� ������ ������ (F1)
  virtual int CallHelp()
    { if (ActionTask) ActionTask->CallHelp(Ident()); return 1;}

  // ��������� : ����� �� ��������� ���������� �������
  // ���� ��������� - ����� ������ ���������� �����������
  // ����� ������� ���������� ����� ��������� ����������
  // ������ ����������� ...
  // ������ ����� ������� ���������� � �� ������� CanClose() !
  virtual int CanClose() { return 1; }

  // ��������� : ����� �� ������������� ����������
  // ��� ��������� ������� ������
  // ���� �� ��������� - �����
  // ����������� �������� ����������� (CanClose() ...)
  virtual int CanRestartByButton() { return 0; }

  // ��������� ������������� �������������� �������
  int Ident() { return ActionIdent; }

  // ������ - ��� ��������� ���������� ?
  virtual int IsService() { return 0; }

  // ��������� � ���, ��� ���������� ����� ��������
  // � ���������� ���������� ������� ��� ������
  // ����������, ���� �������� CanClose()
  // ����������� ��� ����������� ����������� ����������� (Restart())
  virtual void CancelNotify() {}

  // ��������� � ���, ��� �������� ��� �������� ���������
  // ������� ����� ���������� ����� ���������� Commit() ��
  // �������� � ���������� ������� 
  virtual void CommitNotify(TObjectInfo * /*info*/) {}

  // ��������� ������, ������� ����������� ����������
  TMapTask * Task() { return ActionTask; }

protected :

  // ��������� �������������� (����� �����������)
  // � ����������� ����������� ������ ...
  // CanClose() ���������� !
  void Close()
    { if (ActionTask) ActionTask->CloseAction(Ident()); }

  // ��������� �������������� (����� �����������)
  // ��� ���������� ����������� ������
  // CanClose() �� ����� ���������� !
  // ����� ���� ������� ������ ������������
  // ���������� ������, ��� ��� ��� !!!
  void Quit()
    { if (ActionTask) ActionTask->DestroyAction(Ident()); }

  // ��������� "������������" �����������
  // (����� ����������� � ����� ������������)
  // ��� ���������� ����������� ������
  // CanClose() �� ����� ���������� !
  void Restart()
    { if (ActionTask) ActionTask->RestartAction(Ident()); }

 /************************************************************
 *                                                           *
 *       ���������� ������ �� ���� ����� � ����������        *
 *                                                           *
 ************************************************************/

public :

  // ��������� ���������� �������� ������ ���� ����
  // � ���������� ������� ����� (Map) � ���������
  DOUBLEPOINT * GetMapWindowPoint()
     {
       return MapWindow->GetMapWindowPoint();
     }

  // ��������� ������������� ���� �����
  HWND GetMapWindowHandle() { return MapWindow->GetHandle(); }

  // ��������� ������� ��������� ������� ���� �����
  RECT GetMapWindowClientRect()
   {
     return MapWindow->GetClientRect();
   }

 /************************************************************
 *                                                           *
 *       ������ ��������� ���������� ������� ���� �����      *
 *                                                           *
 ************************************************************/

public :

 // ��������� �� ��������� ���������� ������
 // (����, �������, ������ ...)
 // ���� ������� ���������� - ���������,
 // ��� �� �� �������� c ��������� ������� !
 virtual void ChangeData() {}

 // ������ : ����� �� ��������� ����� ������ �������
 // �� ����� ��� ���������
 // ���������� ����� �������� ����� ������� � ����� �������
 // ����� ������ �����,
 // ���� CanSelectObject() ���������� ��������� ��������
 virtual int CanSelectObject()  { return 1; }

 // ������ : ����� �� ��������� ����� ������� �������
 // �� ����� ��� ���������
 // ����� ���������� �� ���������� Setup() !
 // ��������: ����� �� ������� ������ ������ � �.�.
 virtual int CanSelectThisObject(TObjectInfo * )  { return 1; }

 // ������ : ����� �� ��������� ������ ������
 // ��� ������� ������� �����
 // ������ ����������� ������ ��� ��������� ��������
 // ��� �������� ������ !
 virtual int CanUnionGroupData(TObjectInfo * )  { return 1; }

 // ��������� � ���������� ��������� �������
 virtual int Commit() { return 0; }

 // ��������� : ������������� ������ (����� CanSelectThisObject()
 // � SelectObject()). ��������� ���������� ������� � ������
 // ������� ������� �����. ��� ������������ �������� � ����������/�����������
 // ������� ����������� MapWindow->NextActiveObject() �
 // MapWindow->PrevActiveObject().
 // ���������� ����� ����������� ��������� �������
 // ��� ���������� ��������� :
 // TObjectInfo * Target = new TObjectInfo(info);
 virtual int ActiveObject(TObjectInfo * ) { return 0; }

 // ��������� : �������� ����� ������� (������� ��������, Ctrl+Left,...)
 // ���������� ����� ����������� ��������� �������
 // ��� ���������� ��������� :
 // TObjectInfo * Target = new TObjectInfo(info);
 virtual int SelectObject(TObjectInfo * ) { return 0; }

 // ��������� �� ������ ��������� �������
 // ����������� ���������� ����������� !
 virtual int Revert() { return 0; }

 /************************************************************
 *                                                           *
 *       ������ ��������� ��������� ������� ���� �����       *
 *     ���� ������� �� �������������� � ����� ���� ��������  *
 *        ����������� ���� �����  - ������������ 0           *
 *                                                           *
 ************************************************************/

 typedef POINT TPoint;

 typedef struct TRect : public RECT
 {
   int Width()  { return (RT - LT); }
   int Height() { return (DN - UP); }
 }
  TRect;

 typedef TRect TRECT;

 typedef struct TDC
 {
   TDC(HDC handle)  { Handle = handle; }

   HDC GetHandle() { return Handle; }
   operator HDC()  { return Handle; }
   HDC operator = (HDC handle) { return (Handle = handle); }

   HDC Handle;
 }
   TDC;

 typedef TDC THDC;

 typedef struct TMenu
 {
   TMenu(HMENU handle)  
   { 
     Handle = handle; 
#ifdef LINUXAPI                    
     if (handle == 0)
     {
       CountItem = 0;
       memset((char *)&MenuTable[0], 0, sizeof(MenuTable));
     }
#endif
   }


   int AppendMenu(UINT flags,UINT item,const char * name)
   { 
#ifdef WIN32API           
     return ::AppendMenu(Handle, flags, item, name); 
#else
     { 
        if (CountItem > 63) return 0;
	
	MenuTable[CountItem].IdItem   = item;
        if (item == 0) 
	{
          CountItem = CountItem + 1;
	  return 1;
	}
	if (name)
          strncpy(MenuTable[CountItem].NameItem, name, 
	          sizeof(MENUSTRINGTABLE));
	MenuTable[CountItem].Enable   = flags;
	CountItem = CountItem + 1;
	
        return 1; 
     }
#endif
   }

#ifdef WIN32API
   int CheckMenuItem(int item, int state = MF_CHECKED)   
      { return ::CheckMenuItem(Handle, item, state);    }
#endif

   HMENU GetHandle() { return Handle; }
   operator HMENU()  { return Handle; }
   HMENU operator = (HMENU handle) { return (Handle = handle); }

   HMENU Handle;
#ifdef LINUXAPI                    
   MENUSTRINGTABLE MenuTable[64];
   int             CountItem;
#endif
 }
   TMenu;

 typedef TMenu TMENU;

 // ��������� - ��������� �� ���������� �� ������� Shift
 // ���� ��, �� ����������� ������ ������ ��� ������� Shift �����������
 virtual int IsShiftUsed() { return 0;}              

 // ��������� - ��������� �� ���������� �� ������� Tab
 // ���� ��, �� ����������� ������ ������ ��� ������� Tab �����������
 virtual int IsTabUsed() { return 0;}              

 // ������ �������
 virtual int KeyDown(UINT /*key*/, UINT /*repeatCount*/, UINT /*flags*/)
                                    { return 0; }
 // ���������� "�����"
 // ������ ����� ������ � ������� �����
 virtual int LeftDown(UINT /*modKeys*/, POINT& /*point*/)
                                    { return 0; }
 // �������� ����� ������ � ������� �����
 virtual int LeftUp(UINT /*modKeys*/, POINT& /*point*/)
                                    { return 0; }
 // ����������� ����� �� ���� � ������� �����
 virtual int Move(UINT /*modKeys*/, POINT& /*point*/)
                                    { return 0; }

 // ������ ������ ������ � ������� �����
 // ���� ���������� ��������� �������� -
 // ����������� ���� ����������� (�� ��������� !)
 // ����� ����������, ����� ������ ������ ����������
 // ������ � ��������� ALT,CNTRL � �.�.
 virtual int RightDown(UINT /*modKeys*/, POINT& /*point*/)
                                    { return 0; }

 // ������ ������ ������ � ������� �����
 virtual int RightUp(UINT /*modKeys*/, POINT& /*point*/)
                                    { return 0; }

 // �������� ������ ���� ��� ������� ��������
 // ����������� ���� ��� ������� ������ ������ �����
 int CallPopupMenu(HMENU hmenu)
#ifdef WIN32API                        
    { TMENU Tmenu(hmenu); return CallRightMenu(&Tmenu); }
#else
    { return CallRightMenu((TMENU *)hmenu); }
#endif
 virtual int CallRightMenu(TMENU * /*Menu*/)
                                    { return 0; }

 // ���������� "������������"
 // ���������� ����� ���������� "��� ������"
 int BeforePaint(HDC dc, RECT& rect)
  { THDC Thdc(dc); return BeforePaint(Thdc, (TRECT&)rect); }

 virtual int BeforePaint(THDC& dc, TRECT& rect) { return 0; }

 // ���������� "������������"
 // ���������� ����� ���������� "�� �����"
 // (����� ��� ���������� ...)
 int Paint(HDC dc, bool erase, RECT& rect)
  { THDC Thdc(dc); return Paint(Thdc,erase,(TRECT&)rect); }
 virtual int Paint(THDC& dc, bool erase, TRECT& rect)
                                    { return 0; }

 // ������ �� ��������� ����������� ������� �������� �����������
 // (���������� ������������� ����� ���������� Setup(),
 // ��� ��������� ������ � ��������� ���� �����)
 // ���������� ����� ��������� MapWindow->SetMessage(....);
 virtual void ResetMessage() { Comment(); }
 virtual void Comment() {}  // ������� ResetMessage()

 // ��������� � ���, ��� ���������� ����� ��������� ������� �������
 virtual void IdleAction(long count) {}

 /************************************************************
 *                                                           *
 *         ������ ��������� ������� ����� ��� ���������      *
 *                  ������� ���� �����                       *
 *                                                           *
 ************************************************************/

  // ��������� ���������� � ������� ����������� (Picture)
  // ���������� ������� ����� � ��������
  POINT * GetPicturePoint() { return &(MapWindow->PicturePoint);}

  // ��������� ���������� � ���������� ������� ����� (Map)
  // ���������� ������� ����� � ���������
  DOUBLEPOINT * GetMapPoint() { return &(MapWindow->MapPoint);}

  // ��������� ���������� � ������������� ������� ������� (Plane)
  // ���������� ������� ����� � ������
  DOUBLEPOINT * GetPlanePoint() { return &(MapWindow->PlanePoint);}

  // ��������� ���������� � �������������� ������� (Geo)
  // ���������� ������� ����� � ��������
  // ���� �������������� ������� ��������� �� ��������������
  // �������� ��������� ������ ���� !
  // �������� ��������� �������������� ���������
  DOUBLEPOINT * GetGeoPoint() { return MapWindow->GetGeoPoint();}

  // �������� ��������� �������������� ���������
  // ���� �� �������������� - ���������� ����
  int IsGeoSupported()
     { return MapDoc->IsGeoSupported(); }

protected :

 TMapTask * ActionTask;  // ��������� �� ������,������� �����������
                         // ���������� �������
 int ActionIdent;        // ������������� ����������� ������

 TMapWindow * MapWindow; // ���� �������������� �����

 TMapAccess * MapDoc;    // �������� - "����������� �����"
};

#endif

