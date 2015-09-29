
#ifndef MTACTLIN_H
#define MTACTLIN_H

#ifndef MTACTION_H
  #include "mtaction.h"    // TMapAction
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++ ����� "���������� ������������ ������� ����������" +++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapActionLink : public TMapAction
{
  public :

  // ������� ������ "���������� �������"
  // ���� ���������� ������ ������ ������ � �������,
  // �� ������ ������ ����������� � Setup() ...
  TMapActionLink(TMapTask *task,int ident) :
    TMapAction(task,ident)
     {
       Action = 0;
     }

  // ������� ���������� � ���������� ��� ������� !!!
  // ���������� ������ ����� �� �����������
  virtual ~TMapActionLink()
     {
       if (Action)
         {
           // ������� ����������
           delete Action;
           Action = 0;
         }
     }

  // ��������� ��������� �����������
  // ���������� ����� ������ ������������
  virtual void Setup()
    {
      if (Action) Action->Setup();
    }

  // ����� � ���������� ����� ����������
  // ���� ���������� �� ������ ��� ���������� �������
  // �� ��������� ����������� - �������� ������ ����������
  // ���� ������������ ������ ���� ���������
  // � ������� ������� GetAction(...)
  // ���� comid == 0, ������ ���������� �����������
  // ��������� �������� ���� � "����������"
  virtual TMapAction * GetAction(int comid,int run = 1)
    {
      if (comid == 0)
        {
          return LinkAction(0);
        }

      TMapAction * action = 0;

      if (ActionTask)
        {
          action = ActionTask->GetAction(comid,run);
        }

      if (action) return LinkAction(action);

      return 0;
    }

  // ���������� ����� ����������
  TMapAction * LinkAction(TMapAction * action)
    {
      if (Action)
        {
          delete Action;
        }

      Action = action;

      if (Action) Action->Setup();

      return Action;
    }


 /************************************************************
 *                                                           *
 *         ������ ���������� ������������ ������             *
 *                                                           *
 ************************************************************/

public :

  // ������ ������� � ������� ������ ������ (CTRL-F1)
  virtual int CallHelp()
    {
      if (Action) return Action->CallHelp();
      MapWindow->ViewHelp(0);
      return 0;
    }

  // ��������� : ����� �� ��������� ���������� �������
  // ���� ��������� - ����� ������ ���������� �����������
  // ����� ������� ���������� ����� ��������� ����������
  // ������ ����������� ...
  // ������ ����� ������� ���������� � �� ������� CanClose() !
  virtual int CanClose()
    {
      if (Action) return Action->CanClose();
      return 1;
    }

  // ��������� ������������� �������������� �������
  int Ident()
    {
      return ActionIdent;
    }

  int LinkIdent()
    {
      if (Action) return Action->Ident();
      return 0;
    }

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
 *       ������ ��������� ���������� ������� ���� �����      *
 *                                                           *
 ************************************************************/

public :

 // ������ : ����� �� ��������� ����� ������ �������
 // �� ����� ��� ���������
 // ���������� ����� �������� ����� ������� � ����� �������
 // ����� ������ �����,
 // ���� CanSelectObject() ���������� ��������� ��������
 virtual int CanSelectObject()
   {
      if (Action) return Action->CanSelectObject();
      return 1;
   }

 // ������ : ����� �� ��������� ����� ������� �������
 // �� ����� ��� ���������
 // ����� ���������� �� ���������� Setup() !
 // ��������: ����� �� ������� ������ ������ � �.�.
 virtual int CanSelectThisObject(TObjectInfo * info)
   {
      if (Action) return Action->CanSelectThisObject(info);
      return 1;
   }

 // ��������� � ���������� ��������� �������
 virtual int Commit()
   {
      if (Action) return Action->Commit();
      return 0;
   }

 // ��������� : ������������� ������ (����� CanSelectThisObject()
 // � SelectObject()). ��������� ���������� ������� � ������
 // ������� ������� �����. ��� ������������ �������� � ����������/�����������
 // ������� ����������� MapWindow->NextActiveObject() �
 // MapWindow->PrevActiveObject().
 // ���������� ����� ����������� ��������� �������
 // ��� ���������� ��������� :
 // TObjectInfo * Target = new TObjectInfo(info);
 virtual int ActiveObject(TObjectInfo * info)
   {
      if (Action) return Action->ActiveObject(info);
      return 0;
   }

 // ��������� : �������� ����� ������� (������� ��������, Ctrl+Left,...)
 // ���������� ����� ����������� ��������� �������
 // ��� ���������� ��������� :
 // TObjectInfo * Target = new TObjectInfo(info);
 virtual int SelectObject(TObjectInfo * info)
   {
      if (Action) return Action->SelectObject(info);
      return 0;
   }

 // ��������� �� ������ ��������� �������
 // ����������� ���������� ����������� !
 virtual int Revert()
   {
      if (Action) return Action->Revert();
      return 0;
   }


 /************************************************************
 *                                                           *
 *       ������ ��������� ��������� ������� ���� �����       *
 *     ���� ������� �� �������������� � ����� ���� ��������  *
 *        ����������� ���� �����  - ������������ 0           *
 *                                                           *
 ************************************************************/

 // ��������� - ��������� �� ���������� �� ������� Shift
 // ���� ��, �� ����������� ������ ������ ��� ������� Shift �����������
 virtual int IsShiftUsed() 
  {
    if (Action) return Action->IsShiftUsed();
    return 0;
  }

 // ��������� - ��������� �� ���������� �� ������� Tab
 // ���� ��, �� ����������� ������ ������ ��� ������� Tab �����������
 virtual int IsTabUsed()
  {
    if (Action) return Action->IsTabUsed();
    return 0;
  }

 // ������ �������
 virtual int KeyDown(UINT key, UINT repeatCount, UINT flags)
  {
    if (Action) return Action->KeyDown(key,repeatCount,flags);
    return 0;
  }

 // ���������� "�����"
 // ������ ����� ������ � ������� �����
 virtual int LeftDown(UINT modKeys, POINT& point)
  {
    if (Action) return Action->LeftDown(modKeys,point);
    return 0;
  }

 // �������� ����� ������ � ������� �����
 virtual int LeftUp(UINT modKeys, POINT& point)
  {
    if (Action) return Action->LeftUp(modKeys,point);
    return 0;
  }

 // ����������� ����� �� ���� � ������� �����
 virtual int Move(UINT modKeys, POINT& point)
  {
    if (Action) return Action->Move(modKeys,point);
    return 0;
  }

 // ������ ������ ������ � ������� �����
 virtual int RightDown(UINT modKeys, POINT& point)
  {
    if (Action) return Action->RightDown(modKeys,point);
    return 0;
  }

 // ������ ������ ������ � ������� �����
 virtual int RightUp(UINT modKeys, POINT& point)
  {
    if (Action) return Action->RightUp(modKeys,point);
    return 0;
  }

 // �������� ������ ���� ��� ������� ��������
 // ����������� ���� ��� ������� ������ ������ �����
 virtual int CallRightMenu(TMENU * Menu)
  {
    if (Action) return Action->CallRightMenu(Menu);
    return 0;
  }

 // ���������� "������������"
 // ���������� ����� ���������� "��� ������"
 virtual int BeforePaint(THDC& dc, TRECT& rect)
  {
    if (Action) return Action->BeforePaint(dc, rect);
    return 0;
  }

 // ���������� "������������"
 // ���������� ����� ���������� "�� �����"
 // (����� ��� ���������� ...)
 virtual int Paint(THDC& dc, bool erase, TRECT& rect)
  {
    if (Action) return Action->Paint(dc,erase,rect);
    return 0;
  }

 // ������ �� ��������� ����������� ������� �������� �����������
 // (���������� ������������� ����� ���������� Setup(),
 // ��� ��������� ������ � ��������� ���� �����)
 // ���������� ����� ��������� MapWindow->SetMessage(....);
 virtual void Comment()   // ������� ResetMessage()
 {
   if (Action) Action->Comment();            
 }

 virtual void ResetMessage()
 {
   if (Action) Action->ResetMessage();            
   else Comment();
 }

 // ��������� � ���, ��� ���������� ����� ��������� ������� �������
 virtual void IdleAction(long count)
  {
    if (Action) Action->IdleAction(count);
  }


 protected :

 TMapAction * Action; // ��������� �� ������� ����������

};

#endif
