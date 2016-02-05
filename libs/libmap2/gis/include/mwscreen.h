
#ifndef MWSCREEN_H
#define MWSCREEN_H

#ifndef MAPTYPE_H
 #include "maptype.h"
#endif

#ifndef MWCOPYIM_H
 #include "mwcopyim.h"
#endif


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ ����� "����������� ����������� �����" +++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class TCopyScreen : public TCopyImage
{
 public :

  TCopyScreen() : TCopyImage() { X = 0; Y = 0; }

  // ���������� ���������� ��������� �������
  // ���� � ������� ������ � ������������ �������� ���������
  // ���� � �����������
  // ��� ������ ���������� ����
  int CopyClientToImage(HDC hdc, RECT& rect, int x, int y)
  {
    X = x; Y = y;
    return TCopyImage::CopyClientToImage(hdc, rect);
  }

  // ���������� ���������� ��������� �������
  // ���� � ������� ������ � ������������ �������� ���������
  // ���� � �����������
  // ��� ������ ���������� ����
  int CopyClientToImage(HWND hwnd, int x, int y)
  {
    int  ret;
    RECT rect;
    HDC  hdc;
    OpenImage(hwnd);
    X = x; Y = y;
    hdc  = ::GetDC(hwnd);
    ret  = TCopyImage::CopyClientToImage(hdc, ClientRect);
    ::ReleaseDC(hwnd, hdc);
    return ret;
  }

  // ���������� ���������� ��������� ������� ������
  // �� ��������� ��������� � ������
  // ��������� ������� ���� (���������������)
  // ��� ������ ���������� ����
  int CopyImageToClient(HDC hdc, RECT& rect, int x, int y)
  {
    if (ScrollImage(hdc, rect, x, y) == 0)
      return TCopyImage::CopyImageToClient(hdc, rect);
    return 1;
  }

 protected :

  // ������������� ���������� ������ � ������
  // ��������� ������� ����
  int ScrollImage(HDC hdc, RECT& rect, int x, int y);

 protected :

  int X;                // ���������� �������� ������ ���� ����
  int Y;                // � �����������
};

#endif