
#if !defined(MAPFILES_H)
#define MAPFILES_H

#ifndef MAPTYPE_H
  #include "maptype.h"
#endif

#ifdef LINUXAPI
  #include <stdio.h>
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++ ��������� ��������� ������ +++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ������������ ��� ��������� ������ �� ���� ������
// (���������������, �����������, ����������� � �.�.)

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

  // ���������� ���� ������
  // name - ���� � �����
  // ���� ������ �� ���� ���� - ���������� ����

  virtual int Run(const char * name,int access = 0,int mode = 0);


 protected :

  // ���������� ���� ������ �� �����
  // ���� ���������� ���� - ��������� �����������

  virtual int Prepare(char * /*buffer*/,long int /*size*/)
    {
      return 1;
    }

  // ���������� ��������� �������� (������ ������)
  // ���� ���������� ���� - ��������� �����������

  virtual int Terminate()
    {
      return 0;
    }

  // ������� ���� ������
  // ��� ������ ���������� ����

  virtual int Open(const char * name,int access = 0,
                   int mode = 0);

  // ������� ����

  virtual void Close();

 protected:

 HANDLE File;            // ������������� �����
 char * Buffer;          // ����� ������
 unsigned int Size;      // ������ ������
 unsigned int Minimum;   // ����������� ������ ������
 unsigned int Length;    // ������ �����
 unsigned int Offset;    // ������� �������� � �����

};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++   ������� ��������� � ������ �����   +++++++++++++
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

  // ���������� ���� ������
  // in - ���� � ��������� �����,
  // out - ���� � ��������� �����
  // ���� ������� Prepare �� �������������� - ���������
  // ����������� ������
  // ���� ������ �� ���� ���� - ���������� ����

  int Copy(const char * in, const char * out,
           int access = 0,int mode = 0);

 protected:

  // ���������� ���� ������ �� ����� (�����������)
  // ���� ���������� ���� - ��������� �����������

  int Prepare(char * buffer,long int size);

  HANDLE OutFile;
  const char * OutName;
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++   ������� ��������� � ������ �����   +++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _DLLCLASS TPrepareFileHeader : public TCopyFile
{
 public:

  TPrepareFileHeader() : TCopyFile() {}

 ~TPrepareFileHeader() {}

  // �������� ��������� � ������ �����
  //  in     - ���� � �������� �����
  //  out    - ���� � ��������� �����
  //  record - ������
  //  size   - ������ ������
  // ��� ������ ���������� ����

  int Insert(const char * name,char * record, int size)
     {
       return InsertAndRun(name,name,record,size);
     }

  int InsertAndRun(const char * in,const char * out, char * record, int size);

};


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++ ����� TMapProfile +++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#if defined(LINUXAPI) || defined(WINCE)
#define MAXSECTIONCOUNT  2048
#define MAXSECSTRINGSIZE 2048

typedef struct SECTIONDESC
{
  long int Key;                 // ��������� �� ���� ������
  long int Value;               // ��������� �� �������� ������
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

    // ��������� �������� ������ �� �����
    const char * GetValueByKey(const char * key);

    // �������� ������ ��� ��������� ������ �������
    int  Realloc();

    // �������� ���������� ������
    int Update();
#endif

  protected:

    char SectionName[MAX_PATH]; // Name of the section to use
    char FileName[MAX_PATH];    // File name of the .INI file

#if defined(LINUXAPI) || defined(WINCE)
    char         String[MAXSECSTRINGSIZE]; // ������ � INI-�����
    SECTIONDESC  Section[MAXSECTIONCOUNT]; // "�����������" ������

    char *       Buffer;       // ����� ������ ��� ����� ������
    int          Size;         // ������ ������
    int          Length;       // ����� ������������ �������
    FILE *       FileHandle;   // ������������� INI-�����
    int          IsWrite;      // ������ �� ������
    int          IsDirty;      // �������� ����� ���� ��������
#endif
};

// --------------------------------------------------------
//  ��������������� �������
// --------------------------------------------------------

extern "C"
{
 // ����������� ������ �����
 // oldname - ������ ��� ������
 // newname - ����� ��� ������
 // ��� ������ ���������� ����

 long int _MAPAPI CopyMap(const char * oldname,const char * newname);

 // �������� ������ �����
 // name - ��� ������
 // ��� ������ ���������� ����

 long int _MAPAPI DeleteMap(const char * name);

 // ���������� ����������� ����� � ������
 // ���� ����������� ������ �� ������, ������ �� ������ �����������
 // ������ ����� �� ����� 4 �����
 // name - ��� ������������ �����;
 // size - ������ ���������, ������� ����� �����������,
 //        ���� ����� 0 - ����� �������� ���� ����;
 // offset - �������� �� ������ ������������ ���������,
 //        ���� ����� 0 - ������ � ������ �����.
 // filamap - ����� ��������� ��������� (���� �� ������ ���������������)
 // ��� �������� ����������� ����������� ���� ��������� FILEMAPPING
 // � ������������ ��������� ��������
 // ��� ������ ���������� ����

 long int _MAPAPI mapOpenTheFileMapping(const char * name,
                                        unsigned long int size,
                                        unsigned long int offset,
                                        FILEMAPPING * filemap);

 // ������� ����������� ����� � ������

 void _MAPAPI mapCloseTheFileMapping(FILEMAPPING * filemap);

 // ��������� ����� ������ � ����� �� �������� �� ������ �����
 // offset - �������� �� ������ ������������ ���������,
 // size   - ������ ������������� ������ (��� ��������) ��� 0

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

// ���������� ����� ������ ��������� �����

// inname  - �������� ���� �������� ��������� �����,

// outname - �������� ���� �������� ��������� �����,

// ��������� ����������� ������.

// � ������ ������ ���������� 0

int _fastcall cfCopyMapFiles(const char * inname, const char * outname);  
  
#endif
