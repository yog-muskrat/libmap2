
#ifndef MTACTLIN_H
#define MTACTLIN_H

#ifndef MTACTION_H
  #include "mtaction.h"    // TMapAction
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++ КЛАСС "КОММУТАТОР ОБРАБОТЧИКОВ КОМАНДЫ УПРАВЛЕНИЯ" +++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASSTASK TMapActionLink : public TMapAction
{
  public :

  // Создать объект "обработчик команды"
  // Если обработчик должен начать работу с диалога,
  // то диалог должен создаваться в Setup() ...
  TMapActionLink(TMapTask *task,int ident) :
    TMapAction(task,ident)
     {
       Action = 0;
     }

  // Удалить обработчик и освободить все ресурсы !!!
  // Результаты работы здесь не сохраняются
  virtual ~TMapActionLink()
     {
       if (Action)
         {
           // Удалить обработчик
           delete Action;
           Action = 0;
         }
     }

  // Выполнить настройку обработчика
  // Вызывается после вызова конструктора
  virtual void Setup()
    {
      if (Action) Action->Setup();
    }

  // Найти и подключить новый обработчик
  // Если обработчик не найден или вызывалась команда
  // не требующая обработчика - остается старый обработчик
  // Коды обработчиков должны быть добавлены
  // в таблицы функции GetAction(...)
  // Если comid == 0, старый обработчик отключается
  // сообщения начинают идти в "коммутатор"
  virtual TMapAction * GetAction(int comid,int run = 1)
    {
      if (comid == 0)
        {
          return LinkAction(0);
        }

      TMapAction * action = 0;

      if (ActionTask)
        {
          action = ActionTask->GetAction(comid,run);
        }

      if (action) return LinkAction(action);

      return 0;
    }

  // Подключить новый обработчик
  TMapAction * LinkAction(TMapAction * action)
    {
      if (Action)
        {
          delete Action;
        }

      Action = action;

      if (Action) Action->Setup();

      return Action;
    }


 /************************************************************
 *                                                           *
 *         Методы управления обработчиком команд             *
 *                                                           *
 ************************************************************/

public :

  // Запрос справки о текущем режиме работы (CTRL-F1)
  virtual int CallHelp()
    {
      if (Action) return Action->CallHelp();
      MapWindow->ViewHelp(0);
      return 0;
    }

  // Запросить : можно ли отключить обработчик команды
  // Если разрешено - будет вызван деструктор обработчика
  // Перед выдачей разрешения можно сохранить результаты
  // работы обработчика ...
  // Задача может удалить обработчик и не вызывая CanClose() !
  virtual int CanClose()
    {
      if (Action) return Action->CanClose();
      return 1;
    }

  // Запросить идентификатор обрабатываемой команды
  int Ident()
    {
      return ActionIdent;
    }

  int LinkIdent()
    {
      if (Action) return Action->Ident();
      return 0;
    }

  // Запросить задачу, которой принадлежит обработчик
  TMapTask * Task() { return ActionTask; }

protected :

  // Выполнить самоликвидацию (вызов деструктора)
  // с сохранением результатов работы ...
  // CanClose() вызывается !
  void Close()
    { if (ActionTask) ActionTask->CloseAction(Ident()); }

  // Выполнить самоликвидацию (вызов деструктора)
  // без сохранения результатов работы
  // CanClose() не будет вызываться !
  // После этой функции нельзя использовать
  // переменные класса, его уже нет !!!
  void Quit()
    { if (ActionTask) ActionTask->DestroyAction(Ident()); }

  // Выполнить "перезагрузку" обработчика
  // (вызов деструктора и затем конструктора)
  // без сохранения результатов работы
  // CanClose() не будет вызываться !
  void Restart()
    { if (ActionTask) ActionTask->RestartAction(Ident()); }


 /************************************************************
 *                                                           *
 *       Методы обработки прикладных событий окна карты      *
 *                                                           *
 ************************************************************/

public :

 // Запрос : можно ли выполнить выбор нового объекта
 // на карте для обработки
 // Обработчик карты выполнит выбор объекта в точке нажатия
 // левой кнопки мышки,
 // если CanSelectObject() возвращает ненулевое значение
 virtual int CanSelectObject()
   {
      if (Action) return Action->CanSelectObject();
      return 1;
   }

 // Запрос : можно ли выполнить выбор данного объекта
 // на карте для обработки
 // Может вызываться до выполнения Setup() !
 // Например: можно ли удалить данный объект и т.п.
 virtual int CanSelectThisObject(TObjectInfo * info)
   {
      if (Action) return Action->CanSelectThisObject(info);
      return 1;
   }

 // Сообщение о завершении обработки объекта
 virtual int Commit()
   {
      if (Action) return Action->Commit();
      return 0;
   }

 // Извещение : активизирован объект (между CanSelectThisObject()
 // и SelectObject()). Позволяет перебирать объекты с одного
 // нажатия кнопкой мышки. Для программного перехода к следующему/предыдущему
 // объекту применяется MapWindow->NextActiveObject() и
 // MapWindow->PrevActiveObject().
 // Обработчик может накапливать выбранные объекты
 // для совместной обработки :
 // TObjectInfo * Target = new TObjectInfo(info);
 virtual int ActiveObject(TObjectInfo * info)
   {
      if (Action) return Action->ActiveObject(info);
      return 0;
   }

 // Извещение : выполнен выбор объекта (двойным нажатием, Ctrl+Left,...)
 // Обработчик может накапливать выбранные объекты
 // для совместной обработки :
 // TObjectInfo * Target = new TObjectInfo(info);
 virtual int SelectObject(TObjectInfo * info)
   {
      if (Action) return Action->SelectObject(info);
      return 0;
   }

 // Сообщение об отмене обработки объекта
 // Выполняется отключение обработчика !
 virtual int Revert()
   {
      if (Action) return Action->Revert();
      return 0;
   }


 /************************************************************
 *                                                           *
 *       Методы обработки системных событий окна карты       *
 *     Если событие не обрабатывается и может быть передано  *
 *        обработчику окна карты  - возвращается 0           *
 *                                                           *
 ************************************************************/

 // Запросить - реагирует ли обработчик на клавишу Shift
 // Если да, то перемещение экрана мышкой при нажатом Shift блокируется
 virtual int IsShiftUsed() 
  {
    if (Action) return Action->IsShiftUsed();
    return 0;
  }

 // Запросить - реагирует ли обработчик на клавишу Tab
 // Если да, то перемещение экрана мышкой при нажатии Tab блокируется
 virtual int IsTabUsed()
  {
    if (Action) return Action->IsTabUsed();
    return 0;
  }

 // Нажата клавиша
 virtual int KeyDown(UINT key, UINT repeatCount, UINT flags)
  {
    if (Action) return Action->KeyDown(key,repeatCount,flags);
    return 0;
  }

 // Управление "мышью"
 // Нажата левая кнопка в текущей точке
 virtual int LeftDown(UINT modKeys, POINT& point)
  {
    if (Action) return Action->LeftDown(modKeys,point);
    return 0;
  }

 // Отпущена левая кнопка в текущей точке
 virtual int LeftUp(UINT modKeys, POINT& point)
  {
    if (Action) return Action->LeftUp(modKeys,point);
    return 0;
  }

 // Перемещение мышки по окну в текущей точке
 virtual int Move(UINT modKeys, POINT& point)
  {
    if (Action) return Action->Move(modKeys,point);
    return 0;
  }

 // Нажата правая кнопка в текущей точке
 virtual int RightDown(UINT modKeys, POINT& point)
  {
    if (Action) return Action->RightDown(modKeys,point);
    return 0;
  }

 // Нажата правая кнопка в текущей точке
 virtual int RightUp(UINT modKeys, POINT& point)
  {
    if (Action) return Action->RightUp(modKeys,point);
    return 0;
  }

 // Добавить пункты меню для текущей операции
 // Всплывающее меню при нажатии правой кнопки мышки
 virtual int CallRightMenu(TMENU * Menu)
  {
    if (Action) return Action->CallRightMenu(Menu);
    return 0;
  }

 // Управление "отображением"
 // Обработчик может нарисовать "под картой"
 virtual int BeforePaint(THDC& dc, TRECT& rect)
  {
    if (Action) return Action->BeforePaint(dc, rect);
    return 0;
  }

 // Управление "отображением"
 // Обработчик может нарисовать "на карте"
 // (карта уже нарисована ...)
 virtual int Paint(THDC& dc, bool erase, TRECT& rect)
  {
    if (Action) return Action->Paint(dc,erase,rect);
    return 0;
  }

 // Запрос на перевывод комментария текущей операции обработчика
 // (Вызывается автоматически после выполнения Setup(),
 // при получении фокуса и изменении кода языка)
 // Обработчик может выполнить MapWindow->SetMessage(....);
 virtual void Comment()   // Синоним ResetMessage()
 {
   if (Action) Action->Comment();            
 }

 virtual void ResetMessage()
 {
   if (Action) Action->ResetMessage();            
   else Comment();
 }

 // Сообщение о том, что обработчик может выполнить фоновый процесс
 virtual void IdleAction(long count)
  {
    if (Action) Action->IdleAction(count);
  }


 protected :

 TMapAction * Action; // Указатель на текущий обработчик

};

#endif
