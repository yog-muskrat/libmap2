
#ifndef MTMAPTAS_H
#define MTMAPTAS_H

#ifndef MWMAPWIN_H
 #include "mwmapwin.h"
#endif

#define KD_CNTRL  2

// ���� ��������� ���������� ������� � �������          
// ��� �������������� ������� ������� ���������� ������� �� "�������" �������
extern int IsDialogActive;  

class _DLLCLASSTASK TMapAction;   // ��. MTaction.h

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ ����� "���������� ���������� �������" +++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapTask
{
 public :

  TMapTask(TMapWindow * window);

  virtual ~TMapTask() {}

  // �������������� ���������� ������ ������
  // ����� ::PostMessage(...)
  void Quit();

  /************************************************************
  *                                                           *
  *   ������� �����������/���������� ������������ ������      *
  *   ----------------------------------------------------    *
  *      ��������� ������� ����� ����������� �������          *
  *  ��� ���������� ����������� (���������� ���������� ...)   *
  *       (��. MTmaptas.cpp)                                  *
  *                                                           *
  ************************************************************/

  typedef struct TCommandEnabler
  {
    TCommandEnabler(int id)
      { enable = 0; check = -1; Id = id; text[0] = 0; }

    void Enable(int flag) { enable = flag && 1; }
    int  Enable() { return enable; }
    void SetCheck(int flag = 0) { check = flag && 1; }
    int  Check() { return check; }
    int  Ident() { return Id; }
    char * SetText(const char * newtext)
      { if (newtext) strcpy(text,newtext); else text[0] = 0; 
        return text;}
    char * Text() { return text; }

    int Id;
    int enable;
    int check;
    char text[256];
  }
   TCommandEnabler;

  // ��������� �������� �������
  virtual void CallHelp(int comid) { GetAction(comid,-1); }

  // ��������� �������� �������
  virtual void ViewHelp(int topic)
        { if (MapWindow) MapWindow->ViewHelp(topic); }

  // ��������� ���������� �������
  // (�� ����� ���������� ��� CanClose())
  virtual void CloseAction(int comid);

  // ��������� ���������� ������� �������������
  virtual void DestroyAction(int comid = 0);

  // ����� ���������� ������� � �������������� (���� run != 0)
  // ������ ������ � ������������ �������������
  // � ������� GetAction() ! (��. MTmaptas.cpp)
  // ���� ������� �� �������������� ������� -
  // ���������� ����
  virtual TMapAction * GetAction(int comid, int run = 1);

  // ��������� �������������� �� ��������� ������� � ������ ������
  // ���� ��� - ���������� ����
  int EnableAction(TCommandEnabler& ce)
    { return EnableAction(ce.Ident(),ce); }
  virtual int EnableAction(int comid,TCommandEnabler& ce);

  // ��������� ������� ��������� � ������
  // ���� ��������� �� ���������� - ���������� ����
  virtual int PrepareMessage(int /*message*/, WPARAM /*wparam*/,
                             LPARAM /*lparam*/, int * /*retcode*/)
                                { return 0; }

  // ��������� ������������ �� ������ ������
  // � ����������� ������ ����������
  // ���� ��� - ���������� ����
  virtual int IsMultiDocTask() { return 1; }

  // ���������� ����������� �������
  virtual void RestartAction(int comid);

  // ���� ��������� �������� ����� �����
  virtual void SetFocus(HWND hwnd) {};

  /************************************************************
  *                                                           *
  *           ������� �������� ������� ����������             *
  *                                                           *
  ************************************************************/

  // ������� ����������� ������ ������������ ������
  // panel - ����� ������ (��. userapi.h)
  virtual int CreateTaskPanel(int panel = 1) { return 0;};

  // ������� ������ ������ ������������
  // hInst   - ������������� ������ ����������� ������� ������
  // name    - ��������� ������
  // panelId - �������� ������������� ������ ��� 0, ���� ������,
  //           ����� ������� �������� ��� ����
  // ����������: ������������� ��������� ������ ����� �� ��������� �
  //             panelId, ���� ����� ������������� �� ��������
  int CreatePanel(HINSTANCE hInst, const char* name, int panelId = 0);

  // ��������/�������� ������ � ������
  // panelID  - ������������� ������
  // bmpFace  - ������������� ����������� ������ � ��������
  // command  - ������������� ������, ���� 0 - �����������
  // after    - ������������� ������������ ������, ����� �������
  //            ����������� ������, ���� 0 - � ����� ������
  int InsertButton(int panelID, intptr_t bmpFace, int command, int after = 0);

  // ��������/�������� ������ � ������
  // panelID  - ������������� ������
  // bmpFace  - ������������� ����������� ������ � ��������
  // command  - ������������� ������, ���� 0 - �����������
  // after    - ������������� ������������ ������, ����� �������
  //            ����������� ������, ���� 0 - � ����� ������
  // ���������� �� InsertButton ���, ��� ����������� bmpFace          
  //                            �� �������� �������������� � �����
  int InsertButtonEx(int panelID, intptr_t bmpFace, int command, int after = 0); 

  // ��������/�������� ������� ���������� � ������
  // panelID  - ������������� ������
  // ctrlId   - ������������� ������������ �������� ����������,
  //            ���� CtrlId = (-1) - ����������� �����������
  // hwnd     - ������������� ���� �������� ����������
  // after    - ������������� �������� ���������� � ������ ������������,
  //            ����� �������� ����������� ����������� ������� ����������.
  //            ���� after = NULL - ����������� � �����
  int InsertControl(int panelID, HWND hwnd, int ctrlId, int after = 0);

  // ����������� ������ ������������ ���������� ������
  // panelID  - ������������� ������
  // rect     - ���������� ������ ��������� ������
  // position - ������������ ������ � ���� (��. LOCAL)
  // layout   - ������� ������������ ���������� ����
  int MovePanel(int panelID, RECT rect,
                int  position, int layout = 1);

  // ������� ������ �� ������
  // panelID  - ������������� ������
  // command  - ������������� ������
  int DeleteButton(int panelID, int command);

  // �������� �������� �� ������
  // panelID  - ������������� ������
  // command  - ������������� ������
  // bmpFace  - ������������� ������ ����������� ������
  int SetButtonFace(int panelID, int command, HBITMAP bmpFace); 

  // ������ HWND ������ ������������
  // panelID  - ������������� ������
  HWND GetPanelHandle(int panelID);                             

  // ��������/������ ������ ������������ ���������� ������
  // panelID  - ������������� ������
  // show - 0 - ������ ������,
  //         1 - �������� ������
  int ShowPanel(int panelID, int show = 1);             

  // ������ �� �������� ������ ������������
  // ���� ��� ������� ������ ������,
  // �� ��� ����� ��������� ������� ����������
  virtual int PanelCanClose(int panelID);

  // ���������� ������ ������ ���� ��� �������         
  // panelID  - ������������� ������
  // point    - ��������� ������� �� ������
  // ctrlID   - ������������� �������� ���������� ������,
  //            ��� ������� ���� ������ �������
  virtual int PanelRightUp(int panelID, POINT * point, long int ctdlID = 0)
     { return 0; }

  // ����������� � �������� ������ ������������        
  virtual void PanelClosed(int panelID) {}

  // ��������� ���� ��������� ���������� ������� � �������          
  // ����������: 0-��� �������� ��������, 1-������� ��������� �������
  // ��� �������������� ������� ������� ���������� ������� �� "�������" �������
  int GetFlagIsDialogActive();

  // ���������� ���� ��������� ���������� ������� � �������         
  // ������������� 1 ����� �������� ������� � 0 ����� ��� ��������
  // ��� �������������� ������� ������� ���������� ������� �� "�������" �������
  int SetFlagIsDialogActive(int value);


  /************************************************************
  *                                                           *
  *           ��������� � ��������� ��������                  *
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

  // ��������� �� ���������� �������� ����������� �����-�� ������
  // ident - ������������� �����������
  virtual void AnyActionClose(int ident) {}

  // ��������� �� ������� ����������� �����-�� ������
  // ident - ������������� �����������
  virtual void AnyActionOpen(int ident) {}

  // ��������� � ���, ��� ����������� ����� � �����
  // ������� ������ (����� ��������� ��������� ������ � INI-����� � �.�.)
  // ���� ������ �����������, � ����� �������� �������� - ���
  // ������� �� ����������
  virtual void BeforeCloseMap() {}

  // ��������� �� ��������� ���������� ������
  // (����, �������, ������ ...)
  // ���� ������� ���������� - ���������,
  // ��� �� �� �������� c ��������� ������� !
  virtual void ChangeData() {}

  // ��������� �� ��������� ������� �������� ����
  // ���������� ������� ��������� ������� ����
  virtual void ChangeMainSize(int /*width*/, int /*height*/) {}

  // ��������� � ����������� ������� �������� ������
  // ���������� ��� ����������� ������������� ������
  // � ��������������������� ������ ������ � ��������,
  // ��������� ������������� (���������/������ ����������)
  virtual void AdjustData() {}

  // ��������� � �������������� ������� ��������� �����
  // �������� ��� ���������� ����� �� ��������� ���� ���������
  // changeinfo - ��. maptype.h
  // ���� ��� ��������� ��������� ������������� ����� -
  // ����� ��������� ������������ !
  virtual void ChangeObject(CHANGEINFO* /*changeinfo*/) {}

  // ������ - ����� �� �������� ������ ��
  // ���������� �������� (������� ��������� ��������
  // �������� �������������� ��������� �����)
  virtual int IsChangeObjectActive() { return 0; }

  // ��������� �� ��������� ����� ���������
  virtual void ChangeLanguage(int /*code*/) {}

  // ������ �������
  // key   - ��� ������� �������
  // flags - ������� ������� ��������� �������
  //         (0 - �� ������, 2 - ������ CTRL : flags & KD_CNTRL)
  virtual int KeyDown(UINT /*key*/, UINT /*repeatCount*/, UINT /*flags*/)
                                            { return 0; }

  // ����������� ����� �� ���� � ������� �����           
  virtual int Move(UINT /*modKeys*/, POINT& /*point*/)
                                    { return 0; }

  // ���������� "������������"
  // ������ ����� ���������� "��� ������"
  int BeforePaint(HDC dc, RECT& rect)
   { THDC Thdc(dc); return BeforePaint(Thdc, (TRECT&)rect); }

  virtual int BeforePaint(THDC& dc, TRECT& rect) { return 0; }

  // ���������� "������������"
  // ������ ����� ���������� "�� �����"
  // (����� ��� ���������� ...)
  int Paint(HDC dc, bool erase, RECT& rect)
   { THDC Thdc(dc); return Paint(Thdc,erase,(TRECT&)rect); }

  virtual int Paint(THDC& dc, bool erase, TRECT& rect)
                                     { return 0; }

  /************************************************************
  *                                                           *
  *           ������� ������� ���������� ������               *
  *                                                           *
  ************************************************************/

  // ��������� ��� ������ ������
  virtual const char * Name() { return "MapTask"; }

  // ��������� ��������� �������� ���� ����������
  int MainMessage(int message,intptr_t wparm,intptr_t lparm = 0)
   { return MapWindow->MainMessage(message,wparm,lparm); }

  // ��������� ������������� ������ ������ ������
  // ���������������� � ����� ������
  virtual int PanelIdent() { return 0; }

  // ��������� ������ �������� ���������� (� ������ ����� ����������)
  // ����� ���������� � ���� ������ ��������� !
#ifdef WIN32API   
  TModule * GetResourceModule()
    { return MapWindow->GetResourceModule(); }
#endif

  // ��������� ��������� ������ �� ����� ��������
  virtual int LoadString(int id, char * buffer, int size);

  // ��������� ��� ����� ���������
  int GetLanguage()
    { return MapWindow->GetLanguage();}

  // ���� ������ ��������� � ������� ����
  enum OPTIONLANGUAGE
   {
     ML_ENGLISH = 1,  // ����������
     ML_RUSSIAN = 2   // �������
   };

  // ��������� ���� ����������� �����
  TMapWindow * GetMapWindow() { return MapWindow; }


  // ������ ��������� ������� �����
  // ----------------------------------

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
  DOUBLEPOINT * GetGeoPoint() { return MapWindow->GetGeoPoint();}

  // �������� ��������� �������������� ���������
  // ���� �� �������������� - ���������� ����
  int IsGeoSupported()
     { return MapDoc->IsGeoSupported(); }

  // ������� ��� ����� �� �������� ��������
  // (����������� ��������� ��� ������ ������ ����� �����!)
  // name     - ������ ��� ���������� ���������� ������
  // namesize - ������ ������ ��� ���������� (MAX_PATH)
  // title    - ��������� ������� � ������ ����� ����������
  // filter   - ������ ����� ����� ������
  // flags    - ����������� ������ �������
  // index    - ������� ����� ������ ���� ����� ��� �������� �������
  // path     - ������� ���������� ��� �������� �������
  // ���������� ����� ������ � ������ ����� ������ (>=0)
  // ��� ������ ��� ������ �� ������ ����� -
  // ���������� ������������� ��������
  //  ������ ������:
  //
  //  int ret = OpenFile(name, size,
  //                     "�������/��������� ����� �����",
  //                     "����� ��������� (*.map)|*.MAP|",
  //                     OFN_FILEMUSTEXIST, 0, 0);
  //
  int OpenFile(char * name, int namesize,
               const char * title, const char * filter,
               int  flags,  int    index,
               const char * path);

 public :

  TMapWindow * MapWindow;   // ���� �������������� �����

  TMapAccess * MapDoc;      // �������� : "����������� �����"
                            // ����������� �� TMapAccess

 public :

  TMapAction * Action;      // ��������� �� ������� ����������
                            // ��� ����
                            // ��������������� � ������������
                            // ������������� !
};


// --------------------------------------------------------------
//  �������� ������� ������������ ������ (Action)
// --------------------------------------------------------------

#define SeekAction(comid,run)               \
  int ActionRun = run;                      \
  switch(comid)

#define CheckAction(comid,actiontype,topic)     \
    case comid :                                \
      if (ActionRun == 0)                       \
        return (TMapAction *)1;                 \
      if (ActionRun == -1)                      \
        { MapWindow->ViewHelp(topic);           \
          return 0;}                            \
      try                                       \
       {                                        \
         return                                 \
            new actiontype(this,comid);         \
       }                                        \
      catch(...)                                \
       {                                        \
         ::MessageBox(0,                        \
          "Application error", Name(),          \
           MB_OK | MB_ICONSTOP);                \
       }                                        \
      break


#define ReturnAction()  return (TMapAction *)0

// --------------------------------------------------------------
//  �������� ������� ���������� ������ ��� ������������ (Command)
// --------------------------------------------------------------

#define SeekCommand(comid,run)              \
  int CommandRun = run;                     \
  switch(comid)

#define CheckCommand(comid,call,topic)      \
    case comid :                            \
         if (CommandRun == 0)               \
            return (TMapAction *)1;         \
         if (CommandRun == -1)              \
           {ViewHelp(topic);                \
            return (TMapAction *)0;}        \
         call();                            \
         return ((TMapAction *)-1)

#define CheckCommandAndIdent(comid,call,topic) \
    case comid :                            \
         if (CommandRun == 0)               \
            return (TMapAction *)1;         \
         if (CommandRun == -1)              \
           {ViewHelp(topic);                \
            return (TMapAction *)0;}        \
         call(comid);                       \
         return ((TMapAction *)-1)

#endif // MTMAPTAS_H

