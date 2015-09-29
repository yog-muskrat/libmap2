#ifndef MAPPORT_H
#define MAPPORT_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifdef WIN32API

typedef long int HCOMPORT;

extern "C"
{

// ������� COM-���� ��� ������ GPS - ��������� � ������� NMEA O183
// portname - ��� COM-����� (��������, "COM1:")
// baudrate - ������� ������ � ������ (��������, 4800)
// ��� ������ ���������� 0
HCOMPORT _MAPAPI gpsOpen(LPTSTR portname, long int baudrate);

// ������� COM-����
void _MAPAPI gpsClose(HCOMPORT hcomport);

// ������� COM-���� ��� ������/������
// portname - ��� COM-����� (��������, "COM1:")
// baudrate - ������� ������ � ������ (��������, 4800)
// ��� ������ ���������� 0
HCOMPORT _MAPAPI gpsOpenComPort(LPTSTR portname, long int baudrate);

// ������� COM-����
void _MAPAPI gpsCloseComPort(HCOMPORT hcomport);

// ��������� - ���������� �� ���������� �����
long int _MAPAPI gpsIsUpdate(HCOMPORT hcomport);

// ��������� ���������� ������� ����� � �������� � ������� 42 ����
// ������� ���������� ��������� ������������
long int _MAPAPI gpsGetPoint(HCOMPORT hcomport, DOUBLEPOINT * point,
                             double * height);

// ��������� ���������� ������� ����� � �������� � ������� GPS
// ������� ���������� ��������� ������������
long int _MAPAPI gpsGetSourcePoint(HCOMPORT hcomport, DOUBLEPOINT * point,
                                   double * height);

// ��������� ����� ������� ���������
long int _MAPAPI gpsSatelliteCount(HCOMPORT hcomport);

// ��������� �������� ������ ������
long int _MAPAPI gpsQuality(HCOMPORT hcomport);

// ��������� ��� ��������� COM-�����
LPTSTR _MAPAPI gpsPortName(HCOMPORT hcomport);

// ��������� ������������� ��������� COM-�����
// ���� ���� ������ - ���������� ����
HANDLE _MAPAPI gpsPortHandle(HCOMPORT hcomport);

// ��������� ���������� ��������� ������ �� GPS
// buffer - ����� ������ ��� ���������� ����������
// size   - ������ ������
// ��� ������ ���������� ����
long int _MAPAPI gpsGetRecord(HCOMPORT hcomport, char * buffer, long int size);

} // extern "C"

#endif

#endif  // MAPPORT_H
