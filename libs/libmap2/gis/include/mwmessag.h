
#ifndef MWMESSAG_H
#define MWMESSAG_H

#include "mapsyst.h" 

#ifdef WIN32API  
#include <owl\module.h>
#else
class TModule;
#endif

// �������� ������
int LoadString(int id, char* string, int size, TModule* module);

// ������ ��������� �� ������
int MessageError(int idmessage, int idtitle, TModule* module);

// ��������������� ������
int MessageInfo(int idmessage, int idtitle, TModule* module);

// ������ �������
int MessageQuest(int idmessage, int idtitle, TModule* module);

#endif // MWMESSAG_H
