#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 1580
//�������� ������� � ����� ������
#define END_ADR_REGISTER 1715

#define REGISTERS_SDI 8

int privateSDIBigGetReg2(int adrReg);

int getSDIBigModbusRegister(int);//�������� ���������� ��������
int getSDIBigModbusBit(int);//�������� ���������� ����
int setSDIBigModbusRegister(int, int);//�������� ���������� ��������
int setSDIBigModbusBit(int, int);//�������� ���������� ����

void setSDIBigCountObject(void);//�������� �-�� �������
void preSDIBigReadAction(void);//action �� ������
void preSDIBigWriteAction(void);//action �� ������
int  postSDIBigWriteAction(void);//action ����� ������

COMPONENT_OBJ *sdibigcomponent;

/**************************************/
//���������� ���������� ����������������
/**************************************/
void constructorSDIBigComponent(COMPONENT_OBJ *sdibigcomp)
{
  sdibigcomponent = sdibigcomp;

  sdibigcomponent->getModbusRegister = getSDIBigModbusRegister;//�������� ���������� ��������
  sdibigcomponent->getModbusBit      = getSDIBigModbusBit;//�������� ���������� ����
  sdibigcomponent->setModbusRegister = setSDIBigModbusRegister;//�������� ���������� ��������
  sdibigcomponent->setModbusBit      = setSDIBigModbusBit;//�������� ���������� ����

  sdibigcomponent->preReadAction   = preSDIBigReadAction;//action �� ������
  sdibigcomponent->preWriteAction  = preSDIBigWriteAction;//action �� ������
  sdibigcomponent->postWriteAction = postSDIBigWriteAction;//action ����� ������

  sdibigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getSDIBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateSDIBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  return getRangN_BIGModbusRegister(&current_settings_interfaces.ranguvannja_leds[0], 
                                     REGISTERS_SDI, adrReg-BEGIN_ADR_REGISTER );
}//getSDIBigModbusRegister(int adrReg)
int getSDIBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getSDIBigModbusBit(int )
int setSDIBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateSDIBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(sdibigcomponent->isActiveActualData)
    {
      edition_settings = current_settings_interfaces;//������ �����
    }//if(uprbigcomponent->isActiveActualData)
  superClearActiveActualData();

  superSetOperativMarker(sdibigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����
  //�������� �� ������������
  return validN_BIGACMD(dataReg);
}//getDOUTBigModbusRegister(int adrReg)
int setSDIBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preSDIBigReadAction(void) {
//action �� ������
  sdibigcomponent->isActiveActualData = 1;
}//
void preSDIBigWriteAction(void) {
//action �� ������
  sdibigcomponent->operativMarker[0] = -1;
  sdibigcomponent->operativMarker[1] = -1;//����������� ������
  sdibigcomponent->isActiveActualData = 1;
}//
int postSDIBigWriteAction(void) {
extern int upravlSchematic;//���� Rang
//action ����� ������
  int beginAdr = sdibigcomponent->operativMarker[0];
  if(beginAdr<0) return 0;//�� ���� ������
  int endAdr   = sdibigcomponent->operativMarker[1];
  int countAdr = endAdr-beginAdr+1;
  if(endAdr<0) countAdr = 1;

  writeRangN_BIGModbusRegister(&edition_settings.ranguvannja_leds[0], REGISTERS_SDI, beginAdr,
                                countAdr, BEGIN_ADR_REGISTER);

      //��������� ������� - ���������
     upravlSchematic = 1;//���� Rang

  return 0;
}//

int privateSDIBigGetReg2(int adrReg)
{
  //��������� ������� ��������
 return controlPerimetr(adrReg, BEGIN_ADR_REGISTER, END_ADR_REGISTER);
}//privateGetReg2(int adrReg)
