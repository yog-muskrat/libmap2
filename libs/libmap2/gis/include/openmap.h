
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
//  Выбрать имя файла по заданным условиям
//  name     - строка результата,
//  namesize - длина строки,
//  hwnd     - идентификатор главного окна или 0,
//  filter   - описание видов открываемых файлов,
//  flags    - флажки условий выбора файлов,
//  path     - умалчиваемый путь для выбора файла.
//  При ошибке или отказе от выбора возвращает отрицательное значение
//  иначе - индекс строки вида выбранного файла 
//  Пример вызова:
//
//  OpenSaveDialog(name, size, hwnd,
//                 "Открыть/Загрузить новую карту",
//                 "Карты местности (*.map)|*.MAP|",
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
