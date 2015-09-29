
#ifndef PLSAPI_H

#define PLSAPI_H

#ifndef MAPAPI_H
   #include "mapapi.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

 // �������������� �� �������� � ����������� � ����������
 // �� ��������� � ������
 // ���������� :
 // xmet = xdis; ymet = ydis;
 // PictureToPlane(xmet,ymet);
 double _MAPAPI plsPictureToPlaneX(HMAP hMap, double x, double y);
 double _MAPAPI plsPictureToPlaneY(HMAP hMap, double x, double y);

 // �������������� �� ������ �� ��������� � ������� ��
 // �����������
 double _MAPAPI plsPlaneToPictureX(HMAP hMap,double x, double y);
 double _MAPAPI plsPlaneToPictureY(HMAP hMap,double x, double y);

 // �������������� �� ������ �� ��������� � �������������
 // ���������� � �������� � ������������ � ��������� �����
 // (�������������� �� ��� ���� ���� !)
 // ��� ������ ���������� ����
 // ���������� :
 // if (IsGeoSupported())      |  ��� :
 //   {                        |  if (IsGeoSupported())
 //     B = Xmet; L = Ymet;    |    {
 //     Plan2Geo(B,L);         |      Plan2Geo(B=Xmet,L=Ymet);
 //   }                        |    }
 double _MAPAPI plsPlaneToGeoBx(HMAP hMap,double Bx, double Ly);
 double _MAPAPI plsPlaneToGeoLy(HMAP hMap,double Bx, double Ly);

 // �������������� �� ������������� ��������� � ��������
 // � ����� �� ��������� � ������������ � ��������� �����
 // (�������������� �� ��� ���� ���� !)
 // ��� ������ ���������� ����
 double _MAPAPI plsGeoToPlaneX(HMAP hMap, double Bx, double Ly);
 double _MAPAPI plsGeoToPlaneY(HMAP hMap, double Bx, double Ly);

 // �������������� ������������� ���������� � �������� �� ������� 1942�
 // (��������� �����������) � ������������� ���������� � ��������
 // (���������� ��������� WGS84) (�������������� �� ��� ���� ���� !)
 // ��� ������ ���������� ����
 double _MAPAPI plsGeo42ToGeoWGS84Bx(HMAP hMap, double Bx, double Ly);
 double _MAPAPI plsGeo42ToGeoWGS84Ly(HMAP hMap, double Bx, double Ly);

 // �������������� ������������� ���������� � �������� �� ������� WGS 84
 // (���������� ��������� WGS84) (�������������� �� ��� ���� ���� !)
 // � ������������� ���������� � �������� � ������� 1942 � (��������� �����������)
 // ��� ������ ���������� ����
 double _MAPAPI plsGeoWGS84ToGeo42Bx(HMAP hMap, double Bx, double Ly);
 double _MAPAPI plsGeoWGS84ToGeo42Ly(HMAP hMap, double Bx, double Ly);

 // �������������� ������������� ��������� � �������� �� ������� ��-90
 // (���������� ��������� ��-90) � ������������� ���������� � ��������
 // ������� 1942 � (��������� �����������) (�������������� �� ��� ���� ���� !)
 //  ��� ������ ���������� ����
 // ���������� :
 // if (mapIsGeoSupported())
 //   {
 //     mapGeoEP90ToGeo42(hMap,&B,&L);
 //   }
 double _MAPAPI plsGeoEP90ToGeo42Bx(HMAP hMap, double Bx, double Ly);
 double _MAPAPI plsGeoEP90ToGeo42Ly(HMAP hMap, double Bx, double Ly);

 // �������������� ������������� ��������� � �������� �� ������� 1942 �
 // (��������� �����������) � ������������� ���������� � ��������
 // ������� ��-90(���������� ��������� ��-90) (�������������� �� ��� ���� ���� !)
 //  ��� ������ ���������� ����
 // ���������� :
 // if (mapIsGeoSupported())
 //   {
 //     mapGeo42ToGeoEP90(hMap,&B,&L);
 //   }
 double _MAPAPI plsGeo42ToGeoEP90Bx(HMAP hMap, double Bx, double Ly);
 double _MAPAPI plsGeo42ToGeoEP90Ly(HMAP hMap, double Bx, double Ly);

 // ���������� ���������� � ������ ������������ PLSQL                    
 // hObj - ������, � ������� ����� ��������� ����� ����������
 // firstB, firstL - ���������� ������ ����� � �������� � ������
 // secondB, secondL - ���������� ������ ����� � �������� � ������
 // ��� ������ ���������� ����
 long int _MAPAPI plsOrthodrome(HOBJ hObj, double firstB, double firstL,
                                      double secondB, double secondL);


 // hObj - ������, �� ������� ������ �����
 // hObjNew - ������, � ������� ������� ������� �� ��������� �����
 // number - ����� ��������� �����
 // distance - ����������
 // subject - ����� ����������
 // ���������� ���� ��� ������
 long int _MAPAPI plsSeekVirtualPointByDistance(HOBJ hObj, HOBJ hObjNew, long int number,
                                             double distance, long int subject);

 // ����� ������� � ����������� �����, ����� �������� ��������
 // ����������� ��� ������ ������� ��� ������� ����� ������ ���� �� �����
 // ����� ���������� ����� ��� ��������,������� ����� �� ������ !
 // �������� ������� - ��, ��� �������� ��� �������������� ������ (����������)
 // ��������� ������� ������ ����������� �������� mapSetSiteActiveSelect()
 // hMap  - ������������� �������� �����,
 // hObj  - ������������� ������� � ������,
 //         �������������� ���������� �������� mapCreateObject()
 //         ��� mapCreateSiteObject(),
 //         � ������� ����� �������� ��������� ������.
 // pointX, pointY - ����� ������ ������� � ������ �� �����
 // deltaPix - ������ ������� ������ � ��������
 // flagseek  - ������� ������ �������� (WO_FIRST, WO_NEXT...)
 // ���� ������ �� ������ - ���������� ����
_MAPIMP  long int _MAPAPI plsWhatActiveObject(HMAP hMap, HOBJ hObj,               
                                              double pointX, double pointY,
                                              long int deltaPix, long int flagSeek);

// ����� ����� �� �������� ������� � �����������,
// ��������� � ��������
// hMap    - ������������� �������� �����,
// info    - ������������� ������� � ������
// pointinX, pointinY - ���������� ����� � �������������
//                      ������� ��������� , � ������ �� ���������
// ���������� ���������� � �����
_MAPIMP double _MAPAPI plsSeekNearVirtualPointX(HMAP hMap, HOBJ info,
                                                double pointinX, double pointinY);

// ����� ����� �� �������� ������� � �����������,
// ��������� � ��������
// hMap    - ������������� �������� �����,
// info    - ������������� ������� � ������
// pointinX, pointinY - ���������� ����� � �������������
//                      ������� ��������� , � ������ �� ���������
// ���������� ���������� Y �����
_MAPIMP double _MAPAPI plsSeekNearVirtualPointY(HMAP hMap, HOBJ info,
                                                double pointinX, double pointinY);

#if defined(LINUXAPI) && defined(HIDEX11)
 // ������� GIF-���� � ����������� �� �����
 // hmap          - ������������� �������� ������
 // left, top     - ���������� ������ �������� ���� ����������� ����� (� ��������)
 // right, bottom - ���������� ������� ������� ���� ����������� ����� (� ��������)
 // namefile      - ��� GIF-�����
 // ���������� ������ GIF-����� (� ������)
 // ��� ������ ���������� 0
 long int _MAPAPI plsCreateGifFileFromMap(HMAP hMap,
                                          int left, int top,
                                          int right, int bottom,
                                          char* namefile);

 // ������� GIF-���� �� �������� ����� � ����������� ���������
 // hmap          - ������������� �������� ������
 // left, top     - ���������� ������ �������� ���� ����������� ����� (� ��������)
 // right, bottom - ���������� ������� ������� ���� ����������� ����� (� ��������)
 // namefile      - ��� GIF-�����
 // select - ������� ������ ��������, ���� ����� 0, �� �����������
 //          ������� ����������� ������\���������
 // ���������� ������ GIF-����� (� ������)
 // ��� ������ ���������� 0
 long int _MAPAPI plsCreateGifFileFromMapSel(HMAP hMap,
                                             int left, int top,
                                             int right, int bottom,
                                             char* namefile,
                                             HSELECT select);

// ������� GIF-���� � ����������� �� ����� �� �������� ����� � �����������������    
// �������
// hMap        - ������������� �������� ������
// hObj        - ������������� ����������������� �������
// imageParm   - ��������� ��������� ������� (��. MAPGDI.H ��������� ���� IMGOBJECT,
//                                            IMGLINE, IMGCIRCLE...)
// imageType   - ��� ���������� ��������� ������� (��. MAPGDI.H ��� �-��� �����������
//                                     �������� ���� IMG_OBJECT, IMG_LINE, IMG_CIRCLE...)
// left, top   - ���������� ������ �������� ���� ����������� ����� (� ��������)
// right, bottom - ���������� ������� ������� ���� ����������� ����� (� ��������)
// namefile      - ��� GIF-�����
// ���������� ������ GIF-����� (� ������)
// ��� ������ ���������� 0
long int WINAPI _export plsCreateGifFileFromMapAndObj(HMAP hMap, HOBJ hObj,
                                                      char* imageParm, long int sizeParm,  
                                                      long int imageType,
                                                      int left, int top,
                          			      int right, int bottom,
						      char* namefile);

// ������� GIF-���� � ����������� �� ����� �� �������� ����� � �����������������    
// �������
// hMap        - ������������� �������� ������
// hObj        - ������������� ����������������� �������
// imageParm   - ��������� ��������� ������� (��. MAPGDI.H ��������� ���� IMGOBJECT,
//                                            IMGLINE, IMGCIRCLE...)
// imageType   - ��� ���������� ��������� ������� (��. MAPGDI.H ��� �-��� �����������
//                                     �������� ���� IMG_OBJECT, IMG_LINE, IMG_CIRCLE...)
// left, top   - ���������� ������ �������� ���� ����������� ����� (� ��������)
// right, bottom - ���������� ������� ������� ���� ����������� ����� (� ��������)
// namefile      - ��� GIF-�����
// ���������� ������ GIF-����� (� ������)
// ��� ������ ���������� 0
long int WINAPI _export plsCreateGifFileFromMapSelObj(HMAP hMap, HSELECT select,
                                     HOBJ hObj, char* imageParm, long int sizeParm,
                                     long int imageType,int left, int top,
        			     int right, int bottom, char* namefile);


// ���������� �������� �������
// hObj    - ������������� ������� � ������
// numPoint - ����� ����� ���������, ������� � 1 (�� ����)
// ����������: ���������� � �����
_MAPIMP double _MAPAPI plsObjectFrameX(HOBJ hObj, long int numPoint);
 
// ���������� �������� �������
// hObj    - ������������� ������� � ������
// numPoint - ����� ����� ���������, ������� � 1 (�� ����)
// ����������: ���������� Y �����
_MAPIMP double _MAPAPI plsObjectFrameY(HOBJ hObj, long int numPoint);
 


// ��������� ����� ������������ �������
// pointX, pointY - ���������� �����
// xy1X, xy1Y, xy2X, xy2Y   - ���������� ������ �������
// precision - �������� ������ (� ������)
// ���������� ������� �����:
//  1 - ��������� � ������ ������ �������
//  2 - ��������� �� ������ ������ �������
//  3 - ����� ������ ������ ����� �������
//  4 - ����� ������� ������ ����� �������
//  5 - ����� �� ������� (����� �������)
//  6 - ����� �� �������
//  7 - ������ �� �������
// ��� ������ ���������� 0
_MAPIMP long int _MAPAPI plsGetPointPosition(double pointX, double pointY,       
                                             double xy1X, double xy1Y,
                                             double xy2X, double xy2Y,
                                             double precision);

// ���������� ����� ������� �� ������ �� �������� �����                          
// info  - ������������� ������� ����� � ������
// point - ���������� �����, ������������� �����(������) �������
// ���� ����� �� �� ������� - ������ ��������� ����� �� �������
// ���������� ����� �����������!
// ��� ������ ���������� 0
_MAPIMP double _MAPAPI plsLengthToPoint(HOBJ hObj, double pointX, double pointY);


#endif    // LINUXAPI && HIDEX11

#ifdef __cplusplus
}              // extern "C"
#endif

#endif   // PLSAPI_H
