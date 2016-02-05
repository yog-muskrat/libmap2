
#ifndef MTACTEX_H
#define MTACTEX_H

#ifndef MTACTION_H
  #include "MTaction.h"    // TMapAction
#endif

#ifndef MWCOPYIM_H
  #include "mwcopyim.h"    // TCopyImage
#endif


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ ����� "��������� ������� ����������" ++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapActionEx : public TMapAction
{
  public :

  // ������� ������ "���������� �������"
  // ���� ���������� ������ ������ ������ � �������,
  // �� ������ ������ ����������� � Setup() ...
  TMapActionEx(TMapTask * task,int ident) : TMapAction(task, ident)
     {}


  // ��������� ��������� �����������
  // ���������� ����� ������ ������������
  void Setup()
   { TMapAction::Setup();
     Image.OpenImage(MapWindow->GetHandle());
     Image.CopyClientToImage(MapWindow->GetHandle());}

 /************************************************************
 *                                                           *
 *         ������ ���������� ������������ ������             *
 *                                                           *
 ************************************************************/

protected :

  // ��������� �������������� (����� �����������)
  // ��� ���������� ����������� ������
  // CanClose() �� ����� ���������� !
  // ����� ���� ������� ������ ������������
  // ���������� ������, ��� ��� ��� !!!
  void Quit()
    {  Image.CloseImage(); TMapAction::Quit();}

 /************************************************************
 *                                                           *
 *       ������ ��������� ��������� ������� ���� �����       *
 *     ���� ������� �� �������������� � ����� ���� ��������  *
 *        ����������� ���� �����  - ������������ 0           *
 *                                                           *
 ************************************************************/

 // ���������� "������������"
 // ���������� ����� ���������� "�� �����"
 // (����� ��� ���������� ...)
 int Paint(THDC& dc, bool erase, TRECT& rect)
   { Image.OpenImage(MapWindow->GetHandle());
     Image.CopyClientToImage(dc.GetHandle(), rect);
     return TMapAction::Paint(dc, erase, rect); }

 // �������� �������� ���� ����� �� ������ �����
 // ��� ������ ���������� ����
 virtual int UpdateWindow(TRECT& rect)
   {
     return Image.CopyImageToClient(MapWindow->GetHandle(), rect);
   }

protected :

TCopyImage  Image;         // ����� ���� �����

};

#endif

