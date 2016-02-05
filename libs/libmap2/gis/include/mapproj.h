
#ifndef MAPPROJ_H
#define MAPPROJ_H

#ifdef __cplusplus

#ifndef MAPACCES_H
  #include "mapacces.h"
#endif


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ КЛАСС : ПРОЕКТ ЭЛЕКТРОННОЙ КАРТЫ +++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TMapProject
{
  public :

  TMapProject();
  ~TMapProject();

  // Открыть проект и инициализировать все данные
  // mapproject - полное имя файла проекта
  // При ошибке возвращает ноль
  int _fastcall OpenProject(TMapAccess * mapaccess,
                            const char * mapproject);

  // Добавить проект и инициализировать все данные  
  // mapproject - полное имя файла проекта
  // При ошибке возвращает ноль
  int _fastcall AppendProject(TMapAccess * mapaccess,
                              const char * mapproject);

  // Сохранить данные электронной карты в проекте
  // mapproject - полное имя файла проекта
  // При ошибке возвращает ноль
  int _fastcall SaveProject(TMapAccess * mapaccess,
                            const char * mapproject);

  // Обработать обязательную секцию [MAP]
  // При ошибке возвращает ноль
  int _fastcall OpenMainMap(TMapAccess * mapaccess,
                            const char * mapproject);

  // Обработать обязательную секцию [MAP]   
  // При ошибке возвращает ноль
  int _fastcall AppendMainMap(TMapAccess * mapaccess,
                              const char * mapproject);

  // Обработать секцию [RSTLIST]
  // При ошибке возвращает ноль
  int _fastcall OpenRstList(TMapAccess * mapaccess,
                            const char * mapproject);

  // Обработать секцию [MTRLIST]
  // При ошибке возвращает ноль
  int _fastcall OpenMtrList(TMapAccess * mapaccess,
                            const char * mapproject);

  // Обработать секцию [MTLLIST]
  // При ошибке возвращает ноль
  int _fastcall OpenMtlList(TMapAccess * mapaccess,
                            const char * mapproject);

  // Обработать секцию [TINLIST]
  // При ошибке возвращает ноль
  int _fastcall OpenTinList(TMapAccess * mapaccess,      
                            const char * mapproject);
                            
  // Обработать секцию [SITELIST]
  // При ошибке возвращает ноль
  int _fastcall OpenSiteList(TMapAccess * mapaccess,
                             const char * mapproject);

  // Обработать обязательную секцию [MAP]
  // При ошибке возвращает ноль
  int _fastcall SaveMainMap(TMapAccess * mapaccess,
                            const char * mapproject);

  // Обработать секцию [RSTLIST]
  // При ошибке возвращает ноль
  int _fastcall SaveRstList(TMapAccess * mapaccess,
                            const char * mapproject);

  // Обработать секцию [MTRLIST]
  // При ошибке возвращает ноль
  int _fastcall SaveMtrList(TMapAccess * mapaccess,
                            const char * mapproject);

  // Обработать секцию [MTLLIST]
  // При ошибке возвращает ноль
  int _fastcall SaveMtlList(TMapAccess * mapaccess,
                            const char * mapproject);

  // Обработать секцию [TINLIST]
  // При ошибке возвращает ноль
  int _fastcall SaveTinList(TMapAccess * mapaccess,      
                            const char * mapproject);

  // Обработать секцию [SITELIST]
  // При ошибке возвращает ноль
  int _fastcall SaveSiteList(TMapAccess * mapaccess,
                             const char * mapproject);

#ifndef HIDEMTQ        

  // Обработать секцию [MTQLIST]
  // При ошибке возвращает ноль
  int _fastcall OpenMtqList(TMapAccess * mapaccess,
                            const char * mapproject);

  // Обработать секцию [MTQLIST]
  // При ошибке возвращает ноль
  int _fastcall SaveMtqList(TMapAccess * mapaccess,
                            const char * mapproject);

#endif // LINUXAPI

protected :

  // Загрузить палитру из входной строки
  // При ошибке возвращает ноль
  int _fastcall LoadPalette(TBaseColors * colors,
                            char * palette);

  // Сохранить палитру во входной строке
  // При ошибке возвращает ноль
  int _fastcall SavePalette(TBaseColors * colors,
                            char * palette, int size);
};

#endif  // __cplusplus

#endif  // MAPPROJ_H

