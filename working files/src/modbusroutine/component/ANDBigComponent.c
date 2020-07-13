#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 2444
//�������� ������� � ����� ������
#define END_ADR_REGISTER 2507

#define REGISTERS_AND 8

int privateANDBigGetReg2(int adrReg);

int getANDBigModbusRegister(int);//�������� ���������� ��������
int getANDBigModbusBit(int);//�������� ���������� ����
int setANDBigModbusRegister(int, int);// �������
int setANDBigModbusBit(int, int);// ���

void setANDBigCountObject(void);
void preANDBigReadAction(void);//action �� ������
void preANDBigWriteAction(void);//action �� ������
int  postANDBigWriteAction(void);//action ����� ������

COMPONENT_OBJ *andbigcomponent;

/**************************************/
//���������� ���������� AND
/**************************************/
void constructorANDBigComponent(COMPONENT_OBJ *andbigcomp)
{
  andbigcomponent = andbigcomp;

  andbigcomponent->getModbusRegister = getANDBigModbusRegister;//�������� ���������� ��������
  andbigcomponent->getModbusBit      = getANDBigModbusBit;//�������� ���������� ����
  andbigcomponent->setModbusRegister = setANDBigModbusRegister;//�������� �������
  andbigcomponent->setModbusBit      = setANDBigModbusBit;//�������� ���

  andbigcomponent->preReadAction   = preANDBigReadAction;//action �� ������
  andbigcomponent->preWriteAction  = preANDBigWriteAction;//action �� ������
  andbigcomponent->postWriteAction = postANDBigWriteAction;//action ����� ������

  andbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getANDBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateANDBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  return getRangN_BIGModbusRegister(&current_settings_interfaces.ranguvannja_d_and[0], REGISTERS_AND, adrReg-BEGIN_ADR_REGISTER );
}//getDOUTBigModbusRegister(int adrReg)
int getANDBigModbusBit(int x)
{
  //�������� ���������� ����
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setANDBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateANDBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(andbigcomponent->isActiveActualData)
    {
      edition_settings = current_settings_interfaces;//������ �����
    }//if(uprbigcomponent->isActiveActualData)
  superClearActiveActualData();

  superSetOperativMarker(andbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  //�������� �� ������
  if(!(edition_settings.configuration&(1<<EL_BIT_CONFIGURATION))) return MARKER_ERRORPERIMETR;
  //�������� �� ������������
  return validN_BIGACMD(dataReg);
}//setDOUTBigModbusRegister(int adrReg)
int setANDBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ����
  return MARKER_OUTPERIMETR;
}//setDOUTBigModbusRegister(int adrReg)

void preANDBigReadAction(void) {
//action �� ������
  andbigcomponent->isActiveActualData = 1;
}//preANDBigReadAction() 

void preANDBigWriteAction(void) {
//action �� ������
  andbigcomponent->operativMarker[0] = -1;
  andbigcomponent->operativMarker[1] = -1;//����������� ������
  andbigcomponent->isActiveActualData = 1;
}//preANDBigWriteAction() 

int postANDBigWriteAction(void) {
extern int upravlSchematic;//���� Rang
//action ����� ������
  int beginAdr = andbigcomponent->operativMarker[0];
  if(beginAdr<0) return 0;//�� ���� ������
  int endAdr   = andbigcomponent->operativMarker[1];
  int countAdr = endAdr-beginAdr+1;
  if(endAdr<0) countAdr = 1;

  writeRangN_BIGModbusRegister(&edition_settings.ranguvannja_d_and[0], REGISTERS_AND, beginAdr,
                                countAdr, BEGIN_ADR_REGISTER);

      //��������� ������� - ���������
     upravlSchematic = 1;//���� Rang

  return 0;
}//postANDBigWriteAction() 

int privateANDBigGetReg2(int adrReg)
{
  //��������� ������� ��������
 return controlPerimetr(adrReg, BEGIN_ADR_REGISTER, END_ADR_REGISTER);
}//privateGetReg2(int adrReg)
