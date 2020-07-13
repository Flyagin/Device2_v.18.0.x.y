#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 2588
//�������� ������� � ����� ������
#define END_ADR_REGISTER 2603

#define REGISTERS_NOT 1

int privateNOTBigGetReg2(int adrReg);

int getNOTBigModbusRegister(int);//�������� ���������� ��������
int getNOTBigModbusBit(int);//�������� ���������� ����
int setNOTBigModbusRegister(int, int);//�������� ���������� ��������
int setNOTBigModbusBit(int, int);//�������� ���������� ����

void setNOTBigCountObject(void);//�������� �-�� �������
void preNOTBigReadAction(void);//action �� ������
void preNOTBigWriteAction(void);//action �� ������
int  postNOTBigWriteAction(void);//action ����� ������

COMPONENT_OBJ *notbigcomponent;

/**************************************/
//���������� ���������� NOT
/**************************************/
void constructorNOTBigComponent(COMPONENT_OBJ *notbigcomp)
{
  notbigcomponent = notbigcomp;

  notbigcomponent->getModbusRegister = getNOTBigModbusRegister;//�������� ���������� ��������
  notbigcomponent->getModbusBit      = getNOTBigModbusBit;//�������� ���������� ����
  notbigcomponent->setModbusRegister = setNOTBigModbusRegister;//�������� ���������� ��������
  notbigcomponent->setModbusBit      = setNOTBigModbusBit;//�������� ���������� ����

  notbigcomponent->preReadAction   = preNOTBigReadAction;//action �� ������
  notbigcomponent->preWriteAction  = preNOTBigWriteAction;//action �� ������
  notbigcomponent->postWriteAction = postNOTBigWriteAction;//action ����� ������

  notbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getNOTBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateNOTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  return getRangN_BIGModbusRegister(&current_settings_interfaces.ranguvannja_d_not[0], REGISTERS_NOT, adrReg-BEGIN_ADR_REGISTER );
}//getDOUTBigModbusRegister(int adrReg)
int getNOTBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setNOTBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateNOTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(notbigcomponent->isActiveActualData)
    {
      edition_settings = current_settings_interfaces;//������ �����
    }//if(uprbigcomponent->isActiveActualData)
  superClearActiveActualData();

  superSetOperativMarker(notbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  //�������� �� ������
  if(!(edition_settings.configuration&(1<<EL_BIT_CONFIGURATION))) return MARKER_ERRORPERIMETR;
  return validN_BIGACMD(dataReg);
}//getDOUTBigModbusRegister(int adrReg)
int setNOTBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preNOTBigReadAction(void) {
//action �� ������
  notbigcomponent->isActiveActualData = 1;
}//
void preNOTBigWriteAction(void) {
//action �� ������
  notbigcomponent->operativMarker[0] = -1;
  notbigcomponent->operativMarker[1] = -1;//����������� ������
  notbigcomponent->isActiveActualData = 1;
}//
int postNOTBigWriteAction(void) {
extern int upravlSchematic;//���� Rang
//action ����� ������
  int beginAdr = notbigcomponent->operativMarker[0];
  if(beginAdr<0) return 0;//�� ���� ������
  int endAdr   = notbigcomponent->operativMarker[1];
  int countAdr = endAdr-beginAdr+1;
  if(endAdr<0) countAdr = 1;

  writeRangN_BIGModbusRegister(&edition_settings.ranguvannja_d_not[0], REGISTERS_NOT, beginAdr,
                                countAdr, BEGIN_ADR_REGISTER);

      //��������� ������� - ���������
     upravlSchematic = 1;//���� Rang

  return 0;
}//

int privateNOTBigGetReg2(int adrReg)
{
  //��������� ������� ��������
 return controlPerimetr(adrReg, BEGIN_ADR_REGISTER, END_ADR_REGISTER);
}//privateGetReg2(int adrReg)
