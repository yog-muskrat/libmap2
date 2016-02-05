
#if !defined(MAPFILES_H)
#define MAPFILES_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifdef LINUXAPI
  #include <stdio.h>
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ПОТОКОВАЯ ОБРАБОТКА ФАЙЛОВ +++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Предназначен для обработки данных за один проход
// (конвертирование, кодирование, копирование и т.п.)

class _DLLCLASS TPrepareFile
{
 public:

  TPrepareFile()
   {
     File    = 0;
     Buffer  = 0;
     Size    = 0;
     Minimum = 0x8000;
   }

  TPrepareFile(char * name,int access = 0,int mode = 0)
   {
     File    = 0;
     Buffer  = 0;
     Size    = 0;
     Minimum = 0x8000;
     Run(name,access,mode);
   }

  virtual ~TPrepareFile()
   {
     Close();
   }

  // Обработать файл данных
  // name - путь к файлу
  // Если считан не весь файл - возвращает ноль

  virtual int Run(const char * name,int access = 0,int mode = 0);


 protected :

  // Обработать блок данных из файла
  // Если возвращает ноль - обработка завершается

  virtual int Prepare(char * /*buffer*/,long int /*size*/)
    {
      return 1;
    }

  // Обработать аварийную ситуацию (ошибка чтения)
  // Если возвращает ноль - обработка завершается

  virtual int Terminate()
    {
      return 0;
    }

  // Открыть файл данных
  // При ошибке возвращает ноль

  virtual int Open(const char * name,int access = 0,
                   int mode = 0);

  // Закрыть файл

  virtual void Close();

 protected:

 HANDLE File;            // Идентификатор файла
 char * Buffer;          // Адрес буфера
 unsigned int Size;      // Размер буфера
 unsigned int Minimum;   // Минимальный размер буфера
 unsigned int Length;    // Размер файла
 unsigned int Offset;    // Текущее смещение в файле

};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++   ВСТАВКА ЗАГОЛОВКА В НАЧАЛО ФАЙЛА   +++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class _DLLCLASS TCopyFile : public TPrepareFile
{
 public :

  TCopyFile() : TPrepareFile()
  {
    OutFile = 0;
    OutName = 0;
  }

  TCopyFile(const char * in, const char * out,
            int access = 0,int mode = 0) : TPrepareFile()
  {
    OutFile = 0;
    OutName = 0;
    Copy(in, out, access, mode);
  }

 ~TCopyFile()
  {
    if (OutFile) ::CloseTheFile(OutFile);
  }

  // Копировать файл данных
  // in - путь к исходному файлу,
  // out - путь к выходному файлу
  // Если функция Prepare не переопределена - выполняет
  // копирование файлов
  // Если считан не весь файл - возвращает ноль

  int Copy(const char * in, const char * out,
           int access = 0,int mode = 0);

 protected:

  // Обработать блок данных из файла (копирование)
  // Если возвращает ноль - обработка завершается

  int Prepare(char * buffer,long int size);

  HANDLE OutFile;
  const char * OutName;
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++   ВСТАВКА ЗАГОЛОВКА В НАЧАЛО ФАЙЛА   +++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TPrepareFileHeader : public TCopyFile
{
 public:

  TPrepareFileHeader() : TCopyFile() {}

 ~TPrepareFileHeader() {}

  // Вставить заголовок в начало файла
  //  in     - путь к входному файлу
  //  out    - путь к выходному файлу
  //  record - запись
  //  size   - размер записи
  // При ошибке возвращает ноль

  int Insert(const char * name,char * record, int size)
     {
       return InsertAndRun(name,name,record,size);
     }

  int InsertAndRun(const char * in,const char * out, char * record, int size);

};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++ КЛАСС TMapProfile +++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#if defined(LINUXAPI) || defined(WINCE)
#define MAXSECTIONCOUNT  2048
#define MAXSECSTRINGSIZE 2048

typedef struct SECTIONDESC
{
  long int Key;                 // Смещением на ключ строки
  long int Value;               // Смещением на значение строки
}
  SECTIONDESC;
#endif

class _DLLCLASS TMapProfile
{
  public:

    TMapProfile(const char far* section, const char far* filename = 0);

#if defined(LINUXAPI) || defined(WINCE)
    ~TMapProfile();
#endif

    int GetInt(const char far* key, int defaultInt = 0);
#if defined(LINUXAPI)                                                      
    double GetDouble(const char far* key, double defaultDouble);
#endif

    int  GetString(const char far* key, char far* buff,
                   unsigned buffSize, const char far* defaultString = "");

    int  WriteInt(const char far* key, int value);
#if defined(LINUXAPI)                                                   
    int WriteDouble(const char far* key, double value);
#endif

    int  WriteString(const char far* key, const char far* str);
    void Flush();

#if defined(LINUXAPI) || defined(WINCE)
  protected:

    // Запросить значение строки по ключу
    const char * GetValueByKey(const char * key);

    // Выделить память или увеличить размер области
    int  Realloc();

    // Обновить содержание секции
    int Update();
#endif

  protected:

    char SectionName[MAX_PATH]; // Name of the section to use
    char FileName[MAX_PATH];    // File name of the .INI file

#if defined(LINUXAPI) || defined(WINCE)
    char         String[MAXSECSTRINGSIZE]; // Строка в INI-файле
    SECTIONDESC  Section[MAXSECTIONCOUNT]; // "Разобранная" секция

    char *       Buffer;       // Адрес буфера для строк секции
    int          Size;         // Размер буфера
    int          Length;       // Длина заполненного участка
    FILE *       FileHandle;   // Идентификатор INI-файла
    int          IsWrite;      // Доступ на запись
    int          IsDirty;      // Значения строк были изменены
#endif
};

// --------------------------------------------------------
//  Вспомогательные функции
// --------------------------------------------------------

extern "C"
{
 // Копирование района работ
 // oldname - старое имя района
 // newname - новое имя района
 // При ошибке возвращает ноль

 long int _MAPAPI CopyMap(const char * oldname,const char * newname);

 // Удаление района работ
 // name - имя района
 // При ошибке возвращает ноль

 long int _MAPAPI DeleteMap(const char * name);

 // Установить отображение файла в память
 // Файл открывается только на чтение, доступ на запись блокируется
 // Размер файла не более 4 Гбайт
 // name - имя открываемого файла;
 // size - размер фрагмента, который будет считываться,
 //        если равен 0 - будет читаться весь файл;
 // offset - смещение на начало считываемого фрагмента,
 //        если равно 0 - чтение с начала файла.
 // filamap - адрес служебной структуры (поля не должны редактироваться)
 // При успешном выполнекнии заполняются поля структуры FILEMAPPING
 // и возвращается ненулевое значение
 // При ошибке возвращает ноль

 long int _MAPAPI mapOpenTheFileMapping(const char * name,
                                        unsigned long int size,
                                        unsigned long int offset,
                                        FILEMAPPING * filemap);

 // Закрыть отображение файла в память

 void _MAPAPI mapCloseTheFileMapping(FILEMAPPING * filemap);

 // Запросить адрес данных в файле по смещению от начала файла
 // offset - смещение от начала запрошенного фрагмента,
 // size   - размер запрашиваемой записи (для контроля) или 0

 const char * _MAPAPI mapReadTheFileMapping(FILEMAPPING * filemap,
                                            unsigned long offset,
                                            unsigned long size);

}  // extern "C"


inline int cfCopyFile(const char * in, const char * out,
                      int access = 0, int mode = 0)
{
  TCopyFile File;                                       
  return    File.Copy(in, out, access, mode);
}

// Копировать файлы данных векторной карты

// inname  - исходный файл паспорта векторной карты,

// outname - выходной файл паспорта векторной карты,

// Выполняет копирование файлов.

// В случае ошибки возвращает 0

int _fastcall cfCopyMapFiles(const char * inname, const char * outname);  
  
#endif
