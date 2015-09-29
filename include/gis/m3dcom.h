
#ifndef M3DCOMH
#define M3DCOMH

#include <Classes.hpp>
#include "map3dapi.h"
#include "mapview.rh"


//---------------------------------------------------------------------------
// Коды сообщений для задачи "3D-навигатор"
//---------------------------------------------------------------------------
#define CM_T3DOPEN                 IDT_MAP3D
#define CM_T3DSTOP                 IDT_MAP3D + 1   //
#define CM_T3DCURSOR               IDT_MAP3D + 2   //
#define CM_T3DSELECTFRAME          IDT_MAP3D + 3   //
#define CM_T3DOBJECTSELECT         IDT_MAP3D + 4   //
#define CM_T3DMAPACTIVE            IDT_MAP3D + 5
#define CM_T3DACTIONSELECTFRAME    IDT_MAP3D + 6
#define CM_SYNCHRMOVE_NO           IDT_MAP3D + 7
#define CM_SYNCHRMOVE_YES          IDT_MAP3D + 8
#define CM_T3DACTIONSELECTOBJECT   IDT_MAP3D + 9
#define CM_T3DSTOPERROR            IDT_MAP3D + 10
#define CM_SYNCHRSCALE_NO          IDT_MAP3D + 11
#define CM_SYNCHRSCALE_YES         IDT_MAP3D + 12
#define CM_T3DSCALE                IDT_MAP3D + 14


extern "C"
{

//---------------------------------------------------------------------------
// Установить язык
//   Вход:
//     hTask3D - идентификатор запущенной задачи
//    Language - код языка диалогов (1 - ENGLISH, 2 - RUSSIAN, ...)
//   При ошибке возвращает ноль
//---------------------------------------------------------------------------
long int _export WINAPI t3dSetLanguage(HTASK3D hTask3D, long int language);
 
//---------------------------------------------------------------------------
// Изменение объекта на 3D-модели при изменении его характеристик на
// двумерной карте
//   Вход:
//     changeinfo - адрес структура с описанием объекта и произведенной
//                  над ним операции
//   При ошибке возвращает ноль
//---------------------------------------------------------------------------
long int _export WINAPI t3dChangeObject(HTASK3D hTask3D, CHANGEINFO* changeinfo);

//---------------------------------------------------------------------------
// Проверка активности главного окна 3D-модели
//   Возвращаемое значение: 0 - неактивно, 1 - активно
//---------------------------------------------------------------------------
long int _export WINAPI t3dIsActiveTaskWnd(HTASK3D hTask3D);

}       // extern "C"

#endif
