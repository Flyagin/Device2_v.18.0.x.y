#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 2604
//�������� ������� � ����� ������
#define END_ADR_REGISTER 2635

#define REGISTERS_PF 2

int privatePFBigGetReg2(int adrReg);

int getPFBigModbusRegister(int);//�������� ���������� ��������
int getPFBigModbusBit(int);//�������� ���������� ����
int setPFBigModbusRegister(int, int);//�������� ���������� ��������
int setPFBigModbusBit(int, int);//�������� ���������� ����

void setPFBigCountObject(void);//�������� �-�� �������
void prePFBigReadAction(void);//action �� ������
void prePFBigWriteAction(void);//action �� ������
int  postPFBigWriteAction(void);//action ����� ������

COMPONENT_OBJ *pfbigcomponent;

/**************************************/
//���������� ���������� PF
/**************************************/
void constructorPFBigComponent(COMPONENT_OBJ *pfbigcomp)
{
  pfbigcomponent = pfbigcomp;

  pfbigcomponent->getModbusRegister = getPFBigModbusRegister;//�������� ���������� ��������
  pfbigcomponent->getModbusBit      = getPFBigModbusBit;//�������� ���������� ����
  pfbigcomponent->setModbusRegister = setPFBigModbusRegister;//�������� ���������� ��������
  pfbigcomponent->setModbusBit      = setPFBigModbusBit;//�������� ���������� ����

  pfbigcomponent->preReadAction   = prePFBigReadAction;//action �� ������
  pfbigcomponent->preWriteAction  = prePFBigWriteAction;//action �� ������
  pfbigcomponent->postWriteAction = postPFBigWriteAction;//action ����� ������

  pfbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getPFBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privatePFBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  int offset = adrReg-BEGIN_ADR_REGISTER;
  int bitInOut  = current_settings_interfaces.ranguvannja_tf[offset/REGISTERS_PF];
  int bit = -1;
  int adr = -1;
  switch(offset%REGISTERS_PF)
  {
   case 0:
     bit = (bitInOut&0xFFFF)-1;
  if(bit!=-1)
    {
      adr = decoderN_BIGACMD(bit);
    }//if(bit!=-1)
   break;
   case 1:
     bit = ((bitInOut>>16)&0xFFFF)-1;
  if(bit!=-1)
    {
      adr = decoderN_SMALLACMD(bit);
    }//if(bit!=-1)
   break;
  }//switch

  return adr<0? 0: adr+getACMDSmallBeginAdr();//������������ ������� ���� � ����� modbus  ��� rele
}//getDOUTBigModbusRegister(int adrReg)
int getPFBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setPFBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privatePFBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(pfbigcomponent->isActiveActualData)
    {
      edition_settings = current_settings_interfaces;//������ �����
    }//if(uprbigcomponent->isActiveActualData)
  superClearActiveActualData();

  superSetOperativMarker(pfbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  //�������� �� ������
  if(!(edition_settings.configuration&(1<<EL_BIT_CONFIGURATION))) return MARKER_ERRORPERIMETR;

  int offset = adrReg-BEGIN_ADR_REGISTER;
  switch(offset%REGISTERS_PF)
  {
   case 0:
     if(!dataReg) return 0;
     return validN_BIGACMD(dataReg);
   case 1:
     if(!dataReg) return 0;
     return validN_SMALLACMD(dataReg);
  }//switch

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setPFBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void prePFBigReadAction(void) {
//action �� ������
  pfbigcomponent->isActiveActualData = 1;
}//
void prePFBigWriteAction(void) {
//action �� ������
  pfbigcomponent->operativMarker[0] = -1;
  pfbigcomponent->operativMarker[1] = -1;//����������� ������
  pfbigcomponent->isActiveActualData = 1;
}//
int postPFBigWriteAction(void) {
extern int upravlSchematic;//���� Rang
//action ����� ������
  int beginAdr = pfbigcomponent->operativMarker[0];
  if(beginAdr<0) return 0;//�� ���� ������
  int endAdr   = pfbigcomponent->operativMarker[1];
  int countAdr = endAdr-beginAdr+1;
  if(endAdr<0) countAdr = 1;
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray

  //�������� �����
  for(int i=0; i<countAdr; i++)
    {
      unsigned int adr = (unsigned short)tempWriteArray[offsetTempWriteArray+i];//����� ��������
      int offset = beginAdr-BEGIN_ADR_REGISTER+i;
      int subObj = offset/REGISTERS_PF;
      int bit = -1;

  switch(offset%REGISTERS_PF)
  {
   case 0:
      if(adr==0) bit = -2;
      else bit = encoderN_BIGACMD(adr-getACMDSmallBeginAdr()); //���������� ������ modbus � ������ ���� ��� ����

      if(bit!=-1) {
         if(bit==-2) bit=-1;
         edition_settings.ranguvannja_tf[subObj] &= (uint32_t)~0xffff;
         edition_settings.ranguvannja_tf[subObj] |= (bit+1);
      }//if
   break;

   case 1:
      if(adr==0) bit = -2;
      else bit = encoderN_SMALLACMD(adr-getACMDSmallBeginAdr()); //���������� ������ modbus � ������ ���� ��� dv

      if(bit!=-1) {
         if(bit==-2) bit=-1;
         edition_settings.ranguvannja_tf[subObj] &= (uint32_t)~(0xffff<<16);
         edition_settings.ranguvannja_tf[subObj] |= ((bit+1)<<16);//
      }//if
   break;
  }//switch

    }//for

      //��������� ������� - ���������
     upravlSchematic = 1;//���� Rang

  return 0;
}//

int privatePFBigGetReg2(int adrReg)
{
  //��������� ������� ��������
 return controlPerimetr(adrReg, BEGIN_ADR_REGISTER, END_ADR_REGISTER);
}//privateGetReg2(int adrReg)
