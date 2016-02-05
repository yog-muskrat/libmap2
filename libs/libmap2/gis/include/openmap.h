
extern "C"
{

typedef long int (WINAPI * OPENSAVEDIALOG)(char * name, long int namesize,
                                           HWND         parent,
                                           const char * title,
                                           const char * filter,
                                           long  int    flags,
                                           long  int    index,
                                           const char * path);

// ------------------------------------------------------------------
//  ������� ��� ����� �� �������� ��������
//  name     - ������ ����������,
//  namesize - ����� ������,
//  hwnd     - ������������� �������� ���� ��� 0,
//  filter   - �������� ����� ����������� ������,
//  flags    - ������ ������� ������ ������,
//  path     - ������������ ���� ��� ������ �����.
//  ��� ������ ��� ������ �� ������ ���������� ������������� ��������
//  ����� - ������ ������ ���� ���������� ����� 
//  ������ ������:
//
//  OpenSaveDialog(name, size, hwnd,
//                 "�������/��������� ����� �����",
//                 "����� ��������� (*.map)|*.MAP|",
//                 OFN_FILEMUSTEXIST, 0, 0);
//
// ------------------------------------------------------------------
long int WINAPI OpenSaveDialog(char * name, long int namesize,
                               HWND         parent,
                               const char * title,
                               const char * filter,
                               long  int    flags,
                               long  int    index,
                               const char * path);
}
