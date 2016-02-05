#ifndef MAPOBJEX_H
#define MAPOBJEX_H

 typedef struct RSCSELSEG
 {
  unsigned long    Segment ;       // Н0МЕР СЛОЯ ( НЕ БОЛЕЕ 255)
  unsigned char    Name[32] ;      // НАЗВАНИЕ ( НЕ БОЛЕЕ 30)
  unsigned long    ObjectIncode ;  // ВНУТРЕННИЙ КОД ОБЪЕКТА
 }
                RSCSELSEG;

 //Выбор слоя классификитора
 //Возвращает IDOK при успешном завершении диалога выбора
 //или  IDCANCEL в противном случае
/*
 long int _import WINAPI  dialogCopyRscObject(TWindow* parent, int resId,
                               TObjectInfo* info, TMapRsc* maprsc,
                               RSCSELSEG* parm,
                               TModule* resourcemodule);
  */
#endif    //MAPOBJEX_H
