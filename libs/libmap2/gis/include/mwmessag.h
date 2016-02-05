
#ifndef MWMESSAG_H
#define MWMESSAG_H

#include "mapsyst.h" 

#ifdef WIN32API  
#include <owl\module.h>
#else
class TModule;
#endif

// Загрузка строки
int LoadString(int id, char* string, int size, TModule* module);

// Диалог сообщения об ошибке
int MessageError(int idmessage, int idtitle, TModule* module);

// Информациионный диалог
int MessageInfo(int idmessage, int idtitle, TModule* module);

// Диалог запроса
int MessageQuest(int idmessage, int idtitle, TModule* module);

#endif // MWMESSAG_H
