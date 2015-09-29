
#ifndef MAPSCRIP_H
#define MAPSCRIP_H

#ifndef MAPTYPE_H
 # include "maptype.h"
#endif

typedef void (WINAPI * SCRIPTLINE)(POINT * point, long int count);
typedef void (WINAPI * SETUPLINE)(long int thick, COLORREF color);

typedef void (WINAPI * SCRIPTPOLYGON)(POINT * point,
                     long int * count, long int polycount, RECT * border);
typedef void (WINAPI * SETUPPOLYGON)(COLORREF color);

typedef void (WINAPI * SCRIPTTEXT)(long int x, long int y,
                                 const char * text, LOGFONT * logfont,
                                 long int align, COLORREF color);

typedef void (WINAPI * SCRIPTWTEXT)(long int x, long int y,
                                 const WCHAR * text, LOGFONT * logfont,
                                 long int align, COLORREF color);

typedef long int (WINAPI * SETUPPERCENT)(long int percent);

typedef struct SCRIPTTABLE     // ������� ������� ������������ SCRIPT
{
  SCRIPTLINE    DrawLine;      // ���������� �����
  SCRIPTPOLYGON DrawPolygon;   // ���������� ��������
  SCRIPTTEXT    DrawText;      // ��������� ������

  SETUPLINE     SetupLine;     // ��������� �����
  SETUPPOLYGON  SetupPolygon;  // ��������� ��������

  SETUPPERCENT  SetupPercent;  // �������� ������� ����������
}
 SCRIPTTABLE;

typedef struct SCRIPTTABLEEX   // ������� ������� ������������ SCRIPT
{
  SCRIPTLINE    DrawLine;      // ���������� �����
  SCRIPTPOLYGON DrawPolygon;   // ���������� ��������
  SCRIPTTEXT    DrawText;      // ��������� ������

  SETUPLINE     SetupLine;     // ��������� �����
  SETUPPOLYGON  SetupPolygon;  // ��������� ��������

  SETUPPERCENT  SetupPercent;  // �������� ������� ����������

  SCRIPTWTEXT   DrawTextUn;    // ��������� ������ � ��������� UNICODE
}
 SCRIPTTABLEEX;

#ifdef __cplusplus
extern "C"
{
#endif

// ��������� ����������� ����� � ���� ���������� SCRIPT-��������
// � ������� �������� ����� � ������� ������� �����������
// hMap       - ������������� �������� �����
// precision  - ����� ����� �� ���� ����������� � SCRIPT-��������
//              �� �����������(h) � ���������(v)
// table      - ������� ������� ������������ SCRIPT-������� �� �����������
// ��� ������ ���������� ����

long int _MAPAPI mapPaintToScript(HMAP hMap, double hprecision, double vprecision,
                                  SCRIPTTABLE * table);

long int _MAPAPI mapPaintToScriptEx(HMAP hMap, double hprecision, double vprecision,
                                    SCRIPTTABLEEX * table);

// ����������.
// SCRIPT �������� ����������� �� ������ ���������� - �����, ��������,
// ������ (DrawLine,...). ��������� ����� � �������� ���������������
// ����� ������� ��������������� ���������� (SetupLine,...).
// ��������� ������ ���������� ������ � ������������ � �������
// � ��������� ANSI (DrawText).
// ���������� ���������� � ������� Windows � ������ ���������� �����������
// ��� �������� �������� �����
// ������ �������� ������������� �������� ������� ����������� �
// ������ ��������� ��������� ��������
// ��� ����������� �������� �������� ���������� ������ ����������
// ������� SetupPercent. ���� ���������� ��������� ����������
// ������, ������� ������ ������� ������� ��������.

#ifdef __cplusplus
} // extern "C"
#endif

#endif // MAPSCRIP_H

