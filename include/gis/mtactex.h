
#ifndef MTACTEX_H
#define MTACTEX_H

#ifndef MTACTION_H
  #include "MTaction.h"    // TMapAction
#endif

#ifndef MWCOPYIM_H
  #include "mwcopyim.h"    // TCopyImage
#endif


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++ КЛАСС "ОБРАБОТКА КОМАНДЫ УПРАВЛЕНИЯ" ++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapActionEx : public TMapAction
{
  public :

  // Создать объект "обработчик команды"
  // Если обработчик должен начать работу с диалога,
  // то диалог должен создаваться в Setup() ...
  TMapActionEx(TMapTask * task,int ident) : TMapAction(task, ident)
     {}


  // Выполнить настройку обработчика
  // Вызывается после вызова конструктора
  void Setup()
   { TMapAction::Setup();
     Image.OpenImage(MapWindow->GetHandle());
     Image.CopyClientToImage(MapWindow->GetHandle());}

 /************************************************************
 *                                                           *
 *         Методы управления обработчиком команд             *
 *                                                           *
 ************************************************************/

protected :

  // Выполнить самоликвидацию (вызов деструктора)
  // без сохранения результатов работы
  // CanClose() не будет вызываться !
  // После этой функции нельзя использовать
  // переменные класса, его уже нет !!!
  void Quit()
    {  Image.CloseImage(); TMapAction::Quit();}

 /************************************************************
 *                                                           *
 *       Методы обработки системных событий окна карты       *
 *     Если событие не обрабатывается и может быть передано  *
 *        обработчику окна карты  - возвращается 0           *
 *                                                           *
 ************************************************************/

 // Управление "отображением"
 // Обработчик может нарисовать "на карте"
 // (карта уже нарисована ...)
 int Paint(THDC& dc, bool erase, TRECT& rect)
   { Image.OpenImage(MapWindow->GetHandle());
     Image.CopyClientToImage(dc.GetHandle(), rect);
     return TMapAction::Paint(dc, erase, rect); }

 // Обновить фрагмент окна карты из буфера копии
 // При ошибке возвращает ноль
 virtual int UpdateWindow(TRECT& rect)
   {
     return Image.CopyImageToClient(MapWindow->GetHandle(), rect);
   }

protected :

TCopyImage  Image;         // Образ окна карты

};

#endif

