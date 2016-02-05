
#ifndef MTLBASE_H
#define MTLBASE_H

#ifndef HIDEMTL

#ifndef RMFBASE_H
  #include "rmfbase.h"
#endif

#ifdef __cplusplus

#include "mtlapi.h"
//------------------------------------------------------------------
//  ��������� ������ "��������� �����" (MTL0)
//------------------------------------------------------------------
typedef struct LAYERHEADER // ������ ��������� 320 ����
{
  long  Ident;             // ������������� ������ ������
                           //  (7FFF7FFF)
  long  Length;            // ����� ������ "��������� �����"

  long  LayerCount;        // �-�� �����
  long  MaterialCount;     // �-�� ����������

  long  HeightSizeBytes;   // ������ ������ ������� � ������
                           // (���� ���� - ������ �����������)
  long  LayerSizeBytes;    // ������ �������� ���� � ������

  unsigned
  long  LayerPseudoCode;   // �������� ���������� ��� �������� ����
  long  LayerMeasure;      // ������� ��������� �������� ����

  double  BotLevelMeter;   // ������ ������� ����� � ������

  double  MaxSummaryPowerMeter;  // ������������ ��������� ��������
                                 // ����� � ������        

  char  Reserve[12];            // ������                 
  char  MaterialFileName[260];  // ��� ����� �������� ����������
}
  LAYERHEADER;

// ����� ��������� ������ "��������� �����" ��������������� �����������
// ���������� ��������� ����� � ���������� LayerCount

//------------------------------------------------------------------
//  ��������� ���� (MTL0) - ���������� ���������         
//------------------------------------------------------------------
typedef struct LAYERDESCOLD  // ������ ��������� 48 ����
{
  long  MaterialCode;     // ��� ���������
  long  LayerColor;       // ���� ���� (��� MaterialCode = 0)
  long  MaxLayerHeight;   // ������������ �������� ���� (�����)
  char  Reserve[20];      // ������
  char  ShortName[16];    // �������� ��� ����
}
  LAYERDESCOLD;

//------------------------------------------------------------------
//  ��������� ���� (MTL0)                                
//------------------------------------------------------------------
typedef struct LAYERDESC  // ������ ��������� 128 ����
{
  long  MaterialCode;     // ��� ���������
  long  LayerColor;       // ���� ���� (��� MaterialCode = 0)
  long  MaxLayerHeight;   // ������������ �������� ���� (�����)
  char  Reserve[20];      // ������
  char  ShortName[16];    // �������� ��� ���� - ���� ���������
  char  LongName[32];     // ��� ���� - �������� ���������
  char  Reserve2[48];     // ������
}
  LAYERDESC;


class _DLLCLASS TMtl: public TRmf
{
 public:

 // ������ ������
 TMtl();

 // ������ ��� ����� � ������������ ������ �������
 TMtl(const char* name, int mode = 0);

 ~TMtl();


 //***************************************************************
 //  ������� ��������� � ����������� ����� ��������� (RMF)
 //***************************************************************

 // �������/��������� �������� � ����� ������ "��������� �����"
 unsigned long LayerDescOffset() { return (HEADER.LayerDescOffset); }
 unsigned long LayerDescOffset(unsigned long layerdescoffset)
 {
   IsHeader(1);
   IsLayerDesc(1);
   return HEADER.LayerDescOffset = layerdescoffset;
 }

 // �������/��������� ����� ������ "��������� �����"
 long LayerDescLength() { return (HEADER.LayerDescLength); }
 long LayerDescLength(long layerdesclength)
 {
   IsHeader(1);
   IsLayerDesc(1);
   return HEADER.LayerDescLength = layerdesclength;
 }

 // ������� ������� �������� � ������
 int ElementSizeBytes() { return (ElementSize()>>3); }

 // ������� ������������ �������� ������ � ������
 double MinimumHeight()  { return HeightUnitToMeter(HEADER.Minimum); }
 double MinHeightMeter() { return HeightUnitToMeter(HEADER.Minimum); }

 // ������� ������������� �������� ������ � ������
 double MaximumHeight()  { return HeightUnitToMeter(HEADER.Maximum); }
 double MaxHeightMeter() { return HeightUnitToMeter(HEADER.Maximum); }


 //***************************************************************
 // ������� ��������� � ����������� ����� ������ "��������� �����"
 //***************************************************************

 //-------------------------------------------------------------
 // ������� �������������� ������ "��������� �����"
 //-------------------------------------------------------------
 inline long TMtl::Ident()
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   return LAYERHEADERBUFF->Ident;
 }

 //-------------------------------------------------------------
 // ��������� �������������� ������ "��������� �����"
 //-------------------------------------------------------------
 inline long TMtl::Ident(long ident)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   IsLayerDesc(1);

   return LAYERHEADERBUFF->Ident = ident;
 }

 //-------------------------------------------------------------
 // ������� ����� ������ "��������� �����"
 //-------------------------------------------------------------
 inline long TMtl::LayerHeaderLength()  
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   return LAYERHEADERBUFF->Length;
 }

 //-------------------------------------------------------------
 // ��������� ����� ������ "��������� �����"
 //-------------------------------------------------------------
 inline long TMtl::LayerHeaderLength(long length)  
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   IsLayerDesc(1);

   return LAYERHEADERBUFF->Length = length;
 }

 //-------------------------------------------------------------
 // ������� ���������� �����
 //-------------------------------------------------------------
 inline long TMtl::LayerCount()
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   return LAYERHEADERBUFF->LayerCount;
 }

 //-------------------------------------------------------------
 // ��������� ���������� �����
 //-------------------------------------------------------------
 inline long TMtl::LayerCount(long layercount)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   IsLayerDesc(1);

   return LAYERHEADERBUFF->LayerCount = layercount;
 }

 //-------------------------------------------------------------
 // ������� ���������� ����������
 //-------------------------------------------------------------
 inline long TMtl::MaterialCount()
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   return LAYERHEADERBUFF->MaterialCount;
 }

 //-------------------------------------------------------------
 // ��������� ����������  ����������
 //-------------------------------------------------------------
 inline long TMtl::MaterialCount(long materialcount)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   IsLayerDesc(1);

   return LAYERHEADERBUFF->MaterialCount = materialcount;
 }

 //-------------------------------------------------------------
 // ������� ������� ������ ����� � ������
 //-------------------------------------------------------------
 inline double TMtl::BotLevelMeter()
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   return LAYERHEADERBUFF->BotLevelMeter;
 }

 //-------------------------------------------------------------
 // ��������� ������� ������ ����� � ������
 //-------------------------------------------------------------
 inline double TMtl::BotLevelMeter(double botlevelmeter)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   IsLayerDesc(1);

   return LAYERHEADERBUFF->BotLevelMeter = botlevelmeter;
 }

 //-------------------------------------------------------------
 // ������� ������������ ��������� �������� ����� � ������  
 //-------------------------------------------------------------
 inline double TMtl::MaxSummaryPowerMeter()
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (LAYERHEADERBUFF->MaxSummaryPowerMeter <= 0)
   {
     return HeightUnitToMeter(Maximum()) -
            min(BotLevelMeter(),HeightUnitToMeter(Minimum()));
   }

   return LAYERHEADERBUFF->MaxSummaryPowerMeter;
 }

 //-------------------------------------------------------------
 // ��������� ������������ ��������� �������� ����� � ������  
 //-------------------------------------------------------------
 inline double TMtl::MaxSummaryPowerMeter(double maxsummarypower)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   IsLayerDesc(1);

   return LAYERHEADERBUFF->MaxSummaryPowerMeter = maxsummarypower;
 }

 //-------------------------------------------------------------
 // ������� ������� ������ ������� � ������
 //-------------------------------------------------------------
 inline long TMtl::HeightSizeBytes()
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   return LAYERHEADERBUFF->HeightSizeBytes;
 }

 //-------------------------------------------------------------
 // ��������� ������� ������ ������� � ������
 //-------------------------------------------------------------
 inline long TMtl::HeightSizeBytes(long heightsizebytes)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   IsLayerDesc(1);

   return LAYERHEADERBUFF->HeightSizeBytes = heightsizebytes;
 }

 //-------------------------------------------------------------
 // ������� ������� �������� ���� � ������
 //-------------------------------------------------------------
 inline long TMtl::LayerSizeBytes()
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   return LAYERHEADERBUFF->LayerSizeBytes;
 }

 //-------------------------------------------------------------
 // ��������� ������� �������� ���� � ������
 //-------------------------------------------------------------
 inline long TMtl::LayerSizeBytes(long layersizebytes)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   IsLayerDesc(1);

   return LAYERHEADERBUFF->LayerSizeBytes = layersizebytes;
 }

 //-------------------------------------------------------------
 // ������� �������� ���������� ��� �������� ����
 //-------------------------------------------------------------
 inline unsigned long TMtl::LayerPseudoCode()
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   return LAYERHEADERBUFF->LayerPseudoCode;
 }

 //-------------------------------------------------------------
 // ��������� �������� ���������� ��� �������� ����
 //-------------------------------------------------------------
 inline unsigned long
 TMtl::LayerPseudoCode(unsigned long layerpseudocode)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   IsLayerDesc(1);

   return LAYERHEADERBUFF->LayerPseudoCode = layerpseudocode;
 }

 //-------------------------------------------------------------
 // ������� ������� ��������� �������� ����
 //-------------------------------------------------------------
 inline long TMtl::LayerMeasure()
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   return LAYERHEADERBUFF->LayerMeasure;
 }

 // ��������� ������� ��������� �������� ����
 long LayerMeasure(long layermeasure);

 //-------------------------------------------------------------
 // ������� ����� ����� �������� ����������
 //-------------------------------------------------------------
 inline char* MaterialFileName()
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   return LAYERHEADERBUFF->MaterialFileName;
 }

 //-------------------------------------------------------------
 // ��������� ����� ����� �������� ����������
 //-------------------------------------------------------------
 inline char* MaterialFileName(char* name)
 {
   if (name == 0)
   {
     Error(IDS_PARM);
     return 0;
   }

   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   IsLayerDesc(1);

   strncpy(LAYERHEADERBUFF->MaterialFileName, name, sizeof(LAYERHEADERBUFF->MaterialFileName));

   return LAYERHEADERBUFF->MaterialFileName;
 }

 //-------------------------------------------------------------
 // ������� ���� ��������� ���� layer
 //-------------------------------------------------------------
 inline long MaterialCode(long layer)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (layer < 1 || layer > LAYERHEADERBUFF->LayerCount)
   {
     Error(IDS_STRUCT);
     return 0;
   }

   return (LAYERDESCBUFF + layer - 1)->MaterialCode;
 }

 //-------------------------------------------------------------
 // ��������� ���� ���������(materialcode) ���� layer
 //-------------------------------------------------------------
 inline long MaterialCode(long layer, long materialcode)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (layer < 1 || layer > LAYERHEADERBUFF->LayerCount)
   {
     Error(IDS_STRUCT);
     return 0;
   }

   IsLayerDesc(1);

   return (LAYERDESCBUFF + layer - 1)->MaterialCode = materialcode;
 }

 //-------------------------------------------------------------
 // ������� ����� ���� layer
 //-------------------------------------------------------------
 inline long LayerColor(long layer)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (layer < 1 || layer > LAYERHEADERBUFF->LayerCount)
   {
     Error(IDS_STRUCT);
     return 0;
   }

   return (LAYERDESCBUFF + layer - 1)->LayerColor;
 }

 //-------------------------------------------------------------
 // ��������� �����(layercolor) ���� layer
 //-------------------------------------------------------------
 inline long LayerColor(long layer, long layercolor)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (layer < 1 || layer > LAYERHEADERBUFF->LayerCount)
   {
     Error(IDS_STRUCT);
     return 0;
   }

   IsLayerDesc(1);

   return (LAYERDESCBUFF + layer - 1)->LayerColor = layercolor;
 }

 //-------------------------------------------------------------
 // ������� ������������ �������� ���� layer
 //-------------------------------------------------------------
 inline long MaxLayerHeight(long layer)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (layer < 1 || layer > LAYERHEADERBUFF->LayerCount)
   {
     Error(IDS_STRUCT);
     return 0;
   }

   return (LAYERDESCBUFF + layer - 1)->MaxLayerHeight;
 }

 //-------------------------------------------------------------
 // ��������� ������������ ��������(maxlayerheight) ���� layer
 //-------------------------------------------------------------
 inline long MaxLayerHeight(long layer, long maxlayerheight)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (layer < 1 || layer > LAYERHEADERBUFF->LayerCount)
   {
     Error(IDS_STRUCT);
     return 0;
   }

   IsLayerDesc(1);

   return (LAYERDESCBUFF + layer - 1)->MaxLayerHeight = maxlayerheight;
 }

 //-------------------------------------------------------------
 // ������� ��������� ����� (���� ���������) ���� layer
 //-------------------------------------------------------------
 inline char* ShortName(long layer)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (layer < 1 || layer > LAYERHEADERBUFF->LayerCount)
   {
     Error(IDS_STRUCT);
     return 0;
   }

   return (LAYERDESCBUFF + layer - 1)->ShortName;
 }

 //-------------------------------------------------------------
 // ��������� ��������� ����� name (���� ���������) ���� layer
 //-------------------------------------------------------------
 inline char* ShortName(long layer, char* name)
 {
   if (name == 0)
   {
     Error(IDS_PARM);
     return 0;
   }

   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (layer < 1 || layer > LAYERHEADERBUFF->LayerCount)
   {
     Error(IDS_STRUCT);
     return 0;
   }

   IsLayerDesc(1);

   strncpy((char*)(LAYERDESCBUFF + layer - 1)->ShortName,
            name, sizeof((LAYERDESCBUFF + layer - 1)->ShortName));

   return (LAYERDESCBUFF + layer - 1)->ShortName;
 }

 //-------------------------------------------------------------
 // ������� ����� (�������� ���������) ���� layer
 //-------------------------------------------------------------
 inline char* LongName(long layer)
 {
   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (layer < 1 || layer > LAYERHEADERBUFF->LayerCount)
   {
     Error(IDS_STRUCT);
     return 0;
   }

   return (LAYERDESCBUFF + layer - 1)->LongName;
 }

 //-------------------------------------------------------------
 // ��������� ����� name (�������� ���������) ���� layer
 //-------------------------------------------------------------
 inline char* LongName(long layer, char* name)
 {
   if (name == 0)
   {
     Error(IDS_PARM);
     return 0;
   }

   if (LAYERHEADERBUFF == 0)
   {
     Error(IDS_MEMORY);
     return 0;
   }

   if (layer < 1 || layer > LAYERHEADERBUFF->LayerCount)
   {
     Error(IDS_STRUCT);
     return 0;
   }

   IsLayerDesc(1);

   strncpy((char*)(LAYERDESCBUFF + layer - 1)->LongName,
            name, sizeof((LAYERDESCBUFF + layer - 1)->LongName));

   return (LAYERDESCBUFF + layer - 1)->LongName;
 }

 //***************************************************************
 //  ������� ��� ������ � ������ :
 //***************************************************************

 // �������� �����
 int Open(const char *name, int mode = 0);

 // ��������� ������ � ����e
 int Save(int force);  

 // �������� ����� ������� � ��������� ����������������    
 int Create(const char* name, BUILDMTL* parm,
            MTRPROJECTIONDATA * mtrprojectiondata);

 // �������� ����� ������� � ��������� ����������������
 /*
 int Create(const char* name, MTLBUILDPARM* parm);

 int CreateMtlFileEx(const char* name, MTLBUILDPARM* parm,
                     MTRPROJECTIONDATA * mtrprojectiondata); */

 // ��������� �������� ����� �������
 // describe - ����� ���������, � ������� ����� ���������
 // �������� �������
 // ��� ������ ���������� ����
 int GetMtlDescribe(MTLDESCRIBE* describe);


 //***************************************************************
 //  ������� �����/������ ��� ��������� ������� ����� :
 //***************************************************************

 // ��������� ������ ��������,��������� ��� ����������� ���������.
 // ������� �������� ������ (��� HeightSizeBytes() != 0)
 // � ������ ���������.
 // ������ ������������ ������ ���� :
 //  - short  ��� HeightSizeBytes() == 2
 //  - long   ��� HeightSizeBytes() == 4
 // ������ ��������� �������� ����� ���� :
 //  - unsigned char   ��� LayerSizeBytes() == 1
 //  - unsigned short  ��� LayerSizeBytes() == 2
 //  - unsigned long   ��� LayerSizeBytes() == 4
 // ��� ������ ���������� ����.
 char* GetElement(int string,int column);

 // ��������� ������ ��������,��������� ��� ����������� ���������.
 // ���� ������� ����������� � ������, �� �� ���������.
 // ��� ������ ���������� ����.
 char* GetElementAndCreate(int string,int column);

 // ��������� ������ ������� ��������� ��������,
 // ��������� ��� ����������� ���������.
 // ������ ��������� �������� �������� ���� :
 //  - unsigned char  ��� LayerSizeBytes() == 1
 //  - unsigned short ��� LayerSizeBytes() == 2
 //  - unsigned long  ��� LayerSizeBytes() == 4
 // ��� ������ ���������� ����.
 char* GetPowers(int string,int column);

 // ��������� ������ ��������,��������� ���
 // �������������� ������������ � ������.
 // ��� ������ ���������� ����.
 char* GetPlaneElement(double x,double y);

 // ��������� ������ ��������,��������� ���
 // �������������� ������������ � ������.
 // ���� ������� ����������� � ������, �� �� ���������.
 // ��� ������ ���������� ����.
 char* GetPlaneElementAndCreate(double x,double y);

 // ����� �������� ���������� ������ � �������� �����.
 // ���������� ����� (x,y) �������� � ������ � ������� ���������
 // ��������� �����. ������� � height �������� ������ � ������.
 // ��� ������ ���������� ����.
 //double GetPlaneHeight(double x,double y);
 int GetPlaneHeight(double& height,double x,double y);

 // ���������� �������� ������ ������� ������������� �� ��������
 // ���������� ��������
 int GetHeightTriangle(double& height,double Str,double Col);

 // ���������� �������� ������ ������� ������������� �� ��������
 // ������������� ����������� (� ������)
 int GetPlaneHeightTriangle(double& height, double x, double y);

 // ���������� �������� ��������� ����� ������� �������������
 // �� �������� ���������� ��������
 // powers - ����� ������� ��� ������ ����������� �������� ���������
 // count - ������ �������, ������ ���� �� ����� TMtl::LayerCount().
 // ���������� ���������� ����������� ��������� ������� powers.
 // ��� ������ ���������� ����.
 int GetPowersTriangle(double Str,double Col,
                       double* powers,long count);

 // ���������� �������� ��������� ����� ������� �������������
 // �� �������� ������������� ����������� (� ������).
 // powers - ����� ������� ��� ������ ����������� �������� ���������
 // count - ������ �������, ������ ���� �� ����� TMtl::LayerCount().
 // ���������� ���������� ����������� ��������� ������� powers.
 // ��� ������ ���������� ����.
 int GetPlanePowersTriangle(double x,double y,
                            double* powers,long count);

 // ����� �������� �������� ���� layernumber � �������� �����.
 // ���������� ����� (x,y) �������� � ������ � ������� ���������
 // ��������� �����.
 // ��� ������ ���������� ����.
 int GetPlanePower(double& power,double x,double y,long layernumber);

 
 // ���������� �������� �������� ���� layernumber (� ������)
 // ������� ������������� �� ��������  ������������� �����������
 // (� ������). ��� ������ ���������� ����.
 int GetPlanePowerTriangle(double& power,double x,double y,int layernumber);

 
 // ���������� �������� �������� �������� ���� layernumber (� ������)
 // ������� ������������� �� �������� ���������� ��������
 // ��� ������ ���������� ����.
 int GetPowerTriangle(double& power,double Str,double Col,int layernumber);

 // ����� �������� ���������� ������ �� ��������,���������
 // ��� ����������� ���������. ��� ������ ���������� ����.
 int GetHeight(long& height,int string,int column);

 // ����� �������� �������� ���� layernumber �� ��������,
 // ��������� ��� ����������� ���������. ��� ������ ���������� ����.
 int GetPower(long& power,int string,int column,int layernumber);

 // ��������� �������� ���������� ������ � �������,
 // ��������������� �������� �����.
 // ���������� ����� � ������(x,y,h) �������� � ������
 // � ������� ��������� ��������� �����.
 // � ������ ������ ���������� 0.
 int PutPlaneHeight(double x,double y,double h);

 // ��������� �������� �������� ���� layernumber � �������� �����.
 // ���������� ����� (x,y) � �������� �������� (power)
 // �������� � ������ � ������� ��������� ��������� �����.
 // � ������ ������ ���������� 0.
 int PutPlanePower(double x,double y,double power,long layernumber);

 // ������ � ����� ��������,
 // ��������� ��� ����������� ���������.
 // address - ����� ��������.
 // size - ������ �������� � ������.
 // ��� ������ ���������� ����.
 int PutElement(char* address,int size,int string,int column);

 // ������ � ����� ��������,
 // ��������� ��� �������������� ������������ � ������.
 // address - ����� ��������.
 // size - ������ �������� � ������.
 // ��� ������ ���������� ����.
 int PutPlaneElement(char* address,int size,double x,double y);

 // ����������� ������� �������� � �����
 inline double PowerUnitToMeter(double unit)
 {
   return unit*PowerMeterInUnit;
 }

 // ����������� ����� � ������� ��������
 inline double PowerMeterToUnit(double meter)
 {
   return meter*PowerUnitInMeter;
 }

 protected:

 // ����� �������� ���� ���������� ������
 void ClearAll();

 // ��������� ������ ��� ��������� �����.
 // ��� ������ ���������� ����.
 int AllocateLayerDesc(int size);

 // ��������� ������ �����, ��������� ������ ���������.
 // ���� ��������� ����� ��� � ������, �� �� ����������� �� �����,
 // ��� ���������� � ����� - ���������.
 // ��� ������ ���������� ����
 char* GetBlockAddressAndCreate(int string, int column);

 // ���������� ����� ������ ��������� "���������� ����������"
 int BufferBlockInit(int partindex);

 // ������� ������ ��������� ��������� �����
 LAYERHEADER* LayerHeader() { return LAYERHEADERBUFF; }

 // ������� ������ ��������� ������� ����
 LAYERDESC* LayerDesc() { return LAYERDESCBUFF; }

 // �������/��������� ����� ���p��������� ��������� �����
 int IsLayerDesc() { return ISLAYERDESC; }
 int IsLayerDesc(int set) { return (ISLAYERDESC = set); }

 // ������ ��������� �����. ��� ������ ���������� ����.
 int ReadLayerDesc();

 // ������ ��������� �����. ��� ������ ���������� ����.
 int WriteLayerDesc();

 //*****************************************************************
 //  ����-������:
 //*****************************************************************

protected:

 LAYERHEADER* LAYERHEADERBUFF; // ����� ��������� ��������� �����
 LAYERDESC* LAYERDESCBUFF;     // ����� ��������� ������� ����
 int   LAYERDESCLENGTH;        // ������ ������ ��� ��������� �����
 int   ISLAYERDESC;            // ���� ���p��������� ��������� �����
 
 double PowerUnitInMeter;     // ����� ������ �������� �� ����
 double PowerMeterInUnit;     // ����� ������ � ������� ��������

};

#endif // __cplusplus

#endif // !HIDEMTL

#endif  // MTLBASE_H

