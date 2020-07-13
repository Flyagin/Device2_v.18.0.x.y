#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 2508
//�������� ������� � ����� ������
#define END_ADR_REGISTER 2571

#define REGISTERS_OR 8

int privateORBigGetReg2(int adrReg);

int getORBigModbusRegister(int);//�������� ���������� ��������
int getORBigModbusBit(int);//�������� ���������� ����
int setORBigModbusRegister(int, int);//�������� ���������� ��������
int setORBigModbusBit(int, int);//�������� ���������� ����

void setORBigCountObject(void);//�������� �-�� �������
void preORBigReadAction(void);//action �� ������
void preORBigWriteAction(void);//action �� ������
int  postORBigWriteAction(void);//action ����� ������

COMPONENT_OBJ *orbigcomponent;

/**************************************/
//���������� ���������� OR
/**************************************/
void constructorORBigComponent(COMPONENT_OBJ *orbigcomp)
{
  orbigcomponent = orbigcomp;

  orbigcomponent->getModbusRegister = getORBigModbusRegister;//�������� ���������� ��������
  orbigcomponent->getModbusBit      = getORBigModbusBit;//�������� ���������� ����
  orbigcomponent->setModbusRegister = setORBigModbusRegister;//�������� ���������� ��������
  orbigcomponent->setModbusBit      = setORBigModbusBit;//�������� ���������� ����

  orbigcomponent->preReadAction   = preORBigReadAction;//action �� ������
  orbigcomponent->preWriteAction  = preORBigWriteAction;//action �� ������
  orbigcomponent->postWriteAction = postORBigWriteAction;//action ����� ������

  orbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getORBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateORBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  return getRangN_BIGModbusRegister(&current_settings_interfaces.ranguvannja_d_or[0], REGISTERS_OR, adrReg-BEGIN_ADR_REGISTER );
}//getDOUTBigModbusRegister(int adrReg)
int getORBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setORBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateORBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(orbigcomponent->isActiveActualData)
    {
      edition_settings = current_settings_interfaces;//������ �����
    }//if(uprbigcomponent->isActiveActualData)
  superClearActiveActualData();

  superSetOperativMarker(orbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  //�������� �� ������
  if(!(edition_settings.configuration&(1<<EL_BIT_CONFIGURATION))) return MARKER_ERRORPERIMETR;
  //�������� �� ������������
  return validN_BIGACMD(dataReg);
}//getDOUTBigModbusRegister(int adrReg)
int setORBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preORBigReadAction(void) {
//action �� ������
  orbigcomponent->isActiveActualData = 1;
}//
void preORBigWriteAction(void) {
//action �� ������
  orbigcomponent->operativMarker[0] = -1;
  orbigcomponent->operativMarker[1] = -1;//����������� ������
  orbigcomponent->isActiveActualData = 1;
}//
int postORBigWriteAction(void) {
extern int upravlSchematic;//���� Rang
//action ����� ������
  int beginAdr = orbigcomponent->operativMarker[0];
  if(beginAdr<0) return 0;//�� ���� ������
  int endAdr   = orbigcomponent->operativMarker[1];
  int countAdr = endAdr-beginAdr+1;
  if(endAdr<0) countAdr = 1;

  writeRangN_BIGModbusRegister(&edition_settings.ranguvannja_d_or[0], REGISTERS_OR, beginAdr,
                                countAdr, BEGIN_ADR_REGISTER);

      //��������� ������� - ���������
     upravlSchematic = 1;//���� Rang

  return 0;
}//

int privateORBigGetReg2(int adrReg)
{
  //��������� ������� ��������
 return controlPerimetr(adrReg, BEGIN_ADR_REGISTER, END_ADR_REGISTER);
}//privateGetReg2(int adrReg)
