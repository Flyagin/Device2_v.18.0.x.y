#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 2220
//�������� ������� � ����� ������
#define END_ADR_REGISTER 2267

#define REGISTERS_KEY 8

int privateKEYBigGetReg2(int adrReg);

int getKEYBigModbusRegister(int);//�������� ���������� ��������
int getKEYBigModbusBit(int);//�������� ���������� ����
int setKEYBigModbusRegister(int, int);// ��������
int setKEYBigModbusBit(int, int);// ����

void setKEYBigCountObject(void);//�������� �-�� �������
void preKEYBigReadAction(void);//action �� ������
void preKEYBigWriteAction(void);//action �� ������
int  postKEYBigWriteAction(void);//action ����� ������

COMPONENT_OBJ *keybigcomponent;

/**************************************/
//���������� ���������� KEY
/**************************************/
void constructorKEYBigComponent(COMPONENT_OBJ *keybigcomp)
{
  keybigcomponent = keybigcomp;

  keybigcomponent->getModbusRegister = getKEYBigModbusRegister;//�������� ���������� ��������
  keybigcomponent->getModbusBit      = getKEYBigModbusBit;//�������� ���������� ����
  keybigcomponent->setModbusRegister = setKEYBigModbusRegister;// ��������
  keybigcomponent->setModbusBit      = setKEYBigModbusBit;// ����

  keybigcomponent->preReadAction   = preKEYBigReadAction;//action �� ������
  keybigcomponent->preWriteAction  = preKEYBigWriteAction;//action �� ������
  keybigcomponent->postWriteAction = postKEYBigWriteAction;//action ����� ������

  keybigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getKEYBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateKEYBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  return getRangN_SMALLModbusRegister(&current_settings_interfaces.ranguvannja_buttons[0], REGISTERS_KEY, adrReg-BEGIN_ADR_REGISTER );
}//getDOUTBigModbusRegister(int adrReg)
int getKEYBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setKEYBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateKEYBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(keybigcomponent->isActiveActualData)
    {
      edition_settings = current_settings_interfaces;//������ �����
    }//if(uprbigcomponent->isActiveActualData)
  superClearActiveActualData();

  superSetOperativMarker(keybigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����
  if(validN_SMALLACMD(dataReg)==MARKER_ERRORPERIMETR) return MARKER_ERRORPERIMETR;

  int offset = adrReg-BEGIN_ADR_REGISTER;
  uint32_t maska = ((uint32_t)edition_settings.buttons_mode)&(1<<((offset/REGISTERS_KEY)*1));
  //�������� �� ������������ ����� �������
  if(!maska)
  switch((unsigned short)dataReg)
  {
   case 50000://- 1-� ��.�������    *
   case 50001://- 2-� ��.�������     *
   case 50002://- 3-� ��.�������     *
   case 50003://- 4-� ��.�������     *
   case 50016://- ����.���1          *
   case 50032://- ����.���2          *
   case 50041://- ����.�����.���2    *
   case 50048://- ����.���3          *
   case 50064://- ����.���4    
   case 50080://- ����.��� 0.4�� 1
   case 50083://- ����.��� 0.4�� 2
   case 50086://- ��.�.��� 0.4�� 2
   case 50112://- ����.���
   case 50113://- ���� ��� �� ��
   case 50128://- ����.���    
   case 50144://- ����.TZNP1
   case 50154://- ����.TZNP2
   case 50164://- ����.TZNP3
   case 50176://- ����.���(���)  
   case 50192://- ���������� �����1
   case 50197://- ���������� �����1
   case 50202://- ���� �����1
   case 50203://- ���� �����2
   case 50208://- ���������� ������1
   case 50211://- ���������� ������2
   case 50288://- ����.����.���  
   case 50304://  ���� ���� �� ��
   case 50368://- ���/����    
   case 50369://- ����.���1
   case 50370://- ����.���2
   case 50384://- ����.��1
   case 50387://- ����.��2
   case 50390://- ����.��3
   case 50393://- ����.��4
   case 50396://- ����.��5
   case 50399://- ����.��6
   case 50402://- ����.��7
   case 50405://- ����.��8
   case 50528://- ����.��      *
   case 50529://- ����.��       *
   case 50530://- ����.�����.��  *
   case 50534://- ���� ��         *
   case 50536://- �������� ����. *
   case 50537://- �������� ����.  *
//   case 50562://- ����� ���������
//   case 50563://- ����� ����
   case 50569://- ̳��./�������. *
   case 50576://- ����.�� ����.�.* 
//   case 50599://- �.���.���.�� ��
      return MARKER_ERRORPERIMETR; //�� ������ ���������
  }//switch
  else
  //�������� �� ������������ ����� �����
  switch((unsigned short)dataReg)
  {
//   case 50000://- 1-� ��.�������    *
//   case 50001://- 2-� ��.�������     *
//   case 50002://- 3-� ��.�������     *
//   case 50003://- 4-� ��.�������     *
//   case 50016://- ����.���1          *
//   case 50032://- ����.���2          *
//   case 50041://- ����.�����.���2    *
//   case 50048://- ����.���3          *
//   case 50064://- ����.���4    
//   case 50080://- ����.��� 0.4�� 1
//   case 50083://- ����.��� 0.4�� 2
//   case 50086://- ��.�.��� 0.4�� 2
//   case 50112://- ����.���
   case 50113://- ���� ��� �� ��
//   case 50128://- ����.���    
//   case 50144://- ����.TZNP1
//   case 50154://- ����.TZNP2
//   case 50164://- ����.TZNP3
//   case 50176://- ����.���(���)  
//   case 50192://- ���������� �����1
//   case 50197://- ���������� �����1
   case 50202://- ���� �����1
   case 50203://- ���� �����2
//   case 50208://- ���������� ������1
//   case 50211://- ���������� ������2
//   case 50288://- ����.����.���  
   case 50304://  ���� ���� �� ��
   case 50368://- ���/����    
//   case 50369://- ����.���1
//   case 50370://- ����.���2
//   case 50384://- ����.��1
//   case 50387://- ����.��2
//   case 50390://- ����.��3
//   case 50393://- ����.��4
//   case 50396://- ����.��5
//   case 50399://- ����.��6
//   case 50402://- ����.��7
//   case 50405://- ����.��8
   case 50528://- ����.��      *
   case 50529://- ����.��       *
//   case 50530://- ����.�����.��  *
   case 50534://- ���� ��         *
   case 50536://- �������� ����. *
   case 50537://- �������� ����.  *
   case 50562://- ����� ���������
   case 50563://- ����� ����
//   case 50569://- ̳��./�������. *
   case 50576://- ����.�� ����.�.* 
   case 50599://- �.���.���.�� ��
      return MARKER_ERRORPERIMETR; //�� ������ ���������
  }//switch

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setKEYBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preKEYBigReadAction(void) {
//action �� ������
  keybigcomponent->isActiveActualData = 1;
}//
void preKEYBigWriteAction(void) {
//action �� ������
  keybigcomponent->operativMarker[0] = -1;
  keybigcomponent->operativMarker[1] = -1;//����������� ������
  keybigcomponent->isActiveActualData = 1;
}//
int postKEYBigWriteAction(void) {
extern int upravlSchematic;//���� Rang
//action ����� ������
  int beginAdr = keybigcomponent->operativMarker[0];
  if(beginAdr<0) return 0;//�� ���� ������
  int endAdr   = keybigcomponent->operativMarker[1];
  int countAdr = endAdr-beginAdr+1;
  if(endAdr<0) countAdr = 1;

  writeRangN_SMALLModbusRegister(&edition_settings.ranguvannja_buttons[0], REGISTERS_KEY, beginAdr,
                                countAdr, BEGIN_ADR_REGISTER);

      //��������� ������� - ���������
     upravlSchematic = 1;//���� Rang

  return 0;
}//

int privateKEYBigGetReg2(int adrReg)
{
  //��������� ������� ��������
 return controlPerimetr(adrReg, BEGIN_ADR_REGISTER, END_ADR_REGISTER);
}//privateGetReg2(int adrReg)
