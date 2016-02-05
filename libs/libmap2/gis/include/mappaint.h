
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
// ++++++++ ����� "����������� ����������� �����" ++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS  TMapPaint : public TMapControl
{
  public:

  /*********************************************************
  *                                                        *
  *           ������������ � ����������� ������            *
  *                                                        *
  *********************************************************/

   TMapPaint();
  ~TMapPaint();


  /*********************************************************
  *                                                        *
  *         ������� ����������� � ������ ���������         *
  *                                                        *
  *********************************************************/

  // ���������� ������
  void _fastcall Paint(HDC hDC, int erase, RECT& rect);

  // ���������� ������
  void PaintObject(HDC hDC, int erase, RECT& rect, TObjectInfo* object,
                   int dontclip = 0);     

  // ���������� ������ � Image
  void PaintObjectToImage(char *lpImage,int ImageAreaWidth,int ImageAreaHeight,
                   int erase, RECT& rect,
                   TObjectInfo* object);

  // ���������� ������
  int PaintUserObject(HDC hdc, RECT& rect, PAINTPARM* image,
                      POLYDATAEX* data, TMap* map = 0);

  // ���������� ������� ���� �������
  void PaintExampleObject(HDC hDC, RECT& rect, int number,
                          char* parm, POLYDATAEX* data);

  // ���������� ������ ��� ������ �� �����, ��������� DIB
  void _fastcall PaintDib(HDC hDC, int erase, RECT* Rect,
                          TMapObject* object = 0,
                          int mapnumber = -2, COLORREF color = 0,
                          TMapSelect * select = 0);

  // ���������� �������� ����� �� �������� ����������
  // � ������� �������� � ������� �������� �
  // �������� �� ����� �������, �������������� �������� �������
  // hMap   - ������������� �������� ������
  // hdc    - �������� ����������
  // rect   - ���������� ��������� ����� (Draw) � ����������� (Picture)
  // number - ����� �����, �� ������� ���������� ������� ��� -1 (��� ����)
  // select - ������� ������ �������� ��� 0
  // color  - ����, ������� ����� ���������� ������� �� �����

  void _fastcall PaintAndSelect(HDC hDC, int erase, RECT& rect,
                                int number, TMapSelect * select,
                                COLORREF color);                  

  /*********************************************************
  *                                                        *
  *             ������� ������� ����������                 *
  *                                                        *
  *********************************************************/

  public :

  // ��������� ����� ������ ������� ������� DIB (0,0 - ����� ������ ����)
  void * GetDibBits();

  // ��������� �������� DIB
  BITMAPINFOHEADER * GetDibInfo();

  // ��������� ������� ������ �������� ��� �����������
  TMapSelect * GetShowSelect();

  // ������� ���������� �������� ����� ����������� � ��������
  //   (X,Y � ����������� Windows)
  void GetPictureBorder(long& x, long& y);

  // ��������� ������������� ���������� ������� �����
  // ��� ������ ���������� ����
  HPALETTE GetViewPalette() { return ViewPalette; }


  /*********************************************************
  *                                                        *
  *                  ������� �������                       *
  *                                                        *
  *********************************************************/

  // ������� ��������� ����� ����
  void SetBackGround(COLORREF background);
  COLORREF GetBackGround() { return MapPalette.BackGround(); }

  // �������� ������� ����
  int UpdatePalette(HWND hwnd, int mode = FALSE);

  // ���������� ����� ������� �������
  void SetMtrPaletteStyle(int style);

  // ���������� ����� �� ������
  void PaintRst(HDC hDC, int erase, RECT& rect, int number, int flagClear = 0);  

  // ���������� ������� �� ������
  void PaintMtr(HDC hDC, int erase, RECT& rect, int number);

#ifndef HIDEMTL
  // ���������� ������� ����� �� ������
  void PaintMtl(HDC hDC, int erase, RECT& rect, int number);
#endif

#ifndef HIDETIN
  // ���������� TIN-������ �� ������
  void PaintTin(HDC hDC, int erase, RECT& rect, int number); 
#endif

#ifndef HIDEMTQ         

  // ���������� ������� ������� �� ������
  void PaintMtq(HDC hDC, int erase, RECT& rect, int number);
#endif

  // ���������� ���������������� ����� �� ������
  void PaintSite(HDC hDC, int erase, RECT& rect, int number,
                 int viewscreen = 1);                            

  // ���������� ��������� ����� DIB � ����
  // (1 - �������� ������, 0 - �������)
  // ���������� ���������� ��������
  int SetPaintStep(int flag);

  // ��������� �������� ���� ������
  int GetPaintStep();                       

  // ���������������� ������� ����
  int SetupPalette();

  // �������� ������� ��������� � DIB
  void _fastcall ClearDibRect(char* lpdib, COLORREF color); 

#ifdef WIN32API  
  // ���������� �������� ������ �� ���������� ����� DIB
  // ����������� ���������
  int ShowDataDibToDevice(HDC hDC, RECT& rect, int mirror);

  // ���������� �������� ������ � ���� ����� DIB
  // ����������� ���������
  int ShowDataDibToWindow(HDC hDC, RECT& rect);

  // ���������� �������� ����� � DIB
  int ShowSitesToDib(RECT* rect);                       
#endif

// protected:

  // ���������� ������ ��� ������ � Image, ��������� DIB
  void PaintDibToImage(char *lpImage,
                         int ImageAreaWidth,int ImageAreaHeight,
                         int erase, RECT& Rect,
                         TObjectInfo* object=0);


  // ���������� ������ � 32-������� �������
  //   dib      - ��������� �� ������ ������ �������
  //   dibwidth - ������ ������� (� ������)
  void PaintDibToDib32(char* dib, int dibwidth, int dibheight,
                       RECT& rect);                     

  // ���������� ������ ��� ������ �� ����������
  void PaintDevice(HDC hDC, int erase, RECT& rect, TMapObject* object = 0,
                   int dontclip = 0, 
#ifdef WIN32API  
		   PRINTPARM* parm = 0);
#else
		   void* parm = 0);
#endif

  // ���������� ������� ���� �������, ��������� DIB
  void PaintExampleObjectDib(HDC hDC, RECT& rect, int number,
                             char* parm, POLYDATAEX* data);

  // ���������� ������� ���� ������� �� ����������
  void PaintExampleObjectDevice(HDC hDC, RECT& rect, int number,
                                char* parm, POLYDATAEX* data);

  // ��������� ������������ ������ � ����������
  // ���������� ��� ������������
  void Lock();

  // ��������� ������������ ������ � ����������
  // ���������� ��� ������������
  void UnLock();

 public:

  TMapPalette MapPalette;            // ������� ������������ �����

  HPALETTE ViewPalette;              // ������������� ������� ����

#ifdef WIN32API                      
  HWND EventHandle;                  // ������������� ���� ��� ���������� � ��������
  int  EventFlag;                    // ���� ����� �������
#endif
};

// ������������� ������� ���������
// ������ �������� �� mppInit ���������� ��� ��������� ����������
// ���� ������� � ������ ��������
void _fastcall mppInit(TMapPaint* mp);   

// ������������ ������� ���������
void _fastcall mpFree(TMapPaint* mp);

// ������� ��������� ����� ����
void _fastcall mpSetBackGround(TMapPaint * mp, COLORREF background);

// ������� ���������� �������� ����� ����������� � ��������
//   (X,Y � ����������� Windows)
void _fastcall mpGetPictureBorder(TMapPaint * mp, long int * x,
                                                  long int * y);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++   �������� ������� ���������   ++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ���������� ������ � Image
void _fastcall mpPaintObjectToImage(TMapPaint* mp, char *lpImage,
                                    int ImageAreaWidth, int ImageAreaHeight,
                                    int erase, RECT* rect,
                                    TMapObject* object);

// ���������� ������� ���� �������
void _fastcall mpPaintExampleObject(TMapPaint* mp, HDC hDC, RECT* rect, int erase,
                                    int number, char* parm, POLYDATAEX* data);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++   ������� ��������� � DIB   +++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ���������� ������ ��� ������ � Image, ��������� DIB
void _fastcall mpPaintDibToImage(TMapPaint* mp, char* lpImage,
                                 int ImageAreaWidth, int ImageAreaHeight,
                                 int erase, RECT* Rect,
                                 TMapObject* object);

// ���������� ������� ���� �������, ��������� DIB
void _fastcall mpPaintExampleObjectDib(TMapPaint* mp, HDC hDC, RECT* Rect,
                                       int number, char* parm, POLYDATAEX* data);

// ���������� ����� ���������� �� ������
void _fastcall mpPaintSite(TMapPaint* mp, HDC hDC, int value,           
                           RECT* Rect, int number, int viewscreen);

// ���������� ����� �� ������
void _fastcall mpPaintRst(TMapPaint* mp, HDC hDC, int value, RECT* Rect, 
                          int number, int flagClear);

// ���������� ������� �� ������
void _fastcall mpPaintMtr(TMapPaint* mp, HDC hDC, int value,             
                          RECT* Rect, int number);

#ifndef HIDEMTL          
// ���������� ������� ����� �� ������
void _fastcall mpPaintMtl(TMapPaint* mp, HDC hDC, int, RECT* Rect, int number);
#endif

#ifndef HIDEMTQ         

// ���������� ������� ������� �� ������
void _fastcall mpPaintMtq(TMapPaint* mp, HDC hDC, int erase,
                          RECT* Rect, int number);
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++   ������� ��������� �� ����������   ++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// ���������� ������ ��� ������ �� ����������
void _fastcall mpPaintDevice(TMapPaint* mp, HDC hDC, int erase, RECT* Rect,
                             TMapObject* object, int dontclip,
#ifdef WIN32API  
			     PRINTPARM* parm);
#else
			     void* parm);			     
#endif

// ���������� ������� ���� ������� �� ����������
void _fastcall mpPaintExampleObjectDevice(TMapPaint* mp, HDC hDC, RECT* Rect, int erase,
                                          int number, char* parm, POLYDATAEX* data);

// ���������� ������
int _fastcall mpPaintUserObject(TMapPaint* mp, HDC hDC, RECT* Rect,
                                PAINTPARM* image, POLYDATAEX* data, TMap* map);

// �������� �� ����� �������, ��������������� �������� ��������
// rect - ���������� ��������� ����� (Draw) � ����������� (Picture)
// select - ������� ������ ��������,
// color  - ����, ������� ����� ���������� ������� �� �����
void _fastcall mpPaintSelectObjects(TMapPaint* mp, HDC hDC, RECT* Rect,
                                    int mapnumber, COLORREF color,
                                    TMapSelect * select);
#ifdef WIN32API
// ��������� ����������� ����� � ���� ���������� SCRIPT-��������
// � ������� �������� ����� � ������� ������� �����������
// ��� ������ ���������� ����
int mpPaintToScript(TMapPaint * mp, double hprecision, double vprecision,
                    SCRIPTTABLEEX * table);
#endif                    

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++   ������� ������������ �������   ++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ���������������� ������� ����
int _fastcall mpSetupPalette(TMapPaint* mp);

// �������� ������� ����
int _fastcall mpUpdatePalette(TMapPaint* mp, HWND hwnd, int mode);

// ���������� ����� ������� �������
void _fastcall mpSetMtrPaletteStyle(TMapPaint* mp, int style);

#endif  //MAPPAINT_H

