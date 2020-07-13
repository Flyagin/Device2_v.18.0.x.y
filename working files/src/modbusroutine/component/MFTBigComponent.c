#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 1740
//�������� ������� � ����� ������
#define END_ADR_REGISTER 2123

#define REGISTERS_MFT 16
#define PART_REGISTERS_MFT 3

int privateMFTBigGetReg2(int adrReg);

int getMFTBigModbusRegister(int);//�������� ���������� ��������
int getMFTBigModbusBit(int);//�������� ���������� ����
int setMFTBigModbusRegister(int, int);//�������� ���������� ��������
int setMFTBigModbusBit(int, int);//�������� ���������� ����

void setMFTBigCountObject(void);//�������� �-�� �������
void preMFTBigReadAction(void);//action �� ������
void preMFTBigWriteAction(void);//action �� ������
int  postMFTBigWriteAction(void);//action ����� ������

int validMFTN_BIGACMD(unsigned short dataReg, int actControl);
int validBazaN_BIGACMD(unsigned short dataReg, int actControl);

COMPONENT_OBJ *mftbigcomponent;

/**************************************/
//���������� ���������� ���
/**************************************/
void constructorMFTBigComponent(COMPONENT_OBJ *mftbigcomp)
{
  mftbigcomponent = mftbigcomp;

  mftbigcomponent->getModbusRegister = getMFTBigModbusRegister;//�������� ���������� ��������
  mftbigcomponent->getModbusBit      = getMFTBigModbusBit;//�������� ���������� ����
  mftbigcomponent->setModbusRegister = setMFTBigModbusRegister;//�������� ���������� ��������
  mftbigcomponent->setModbusBit      = setMFTBigModbusBit;//�������� ���������� ����

  mftbigcomponent->preReadAction   = preMFTBigReadAction;//action �� ������
  mftbigcomponent->preWriteAction  = preMFTBigWriteAction;//action �� ������
  mftbigcomponent->postWriteAction = postMFTBigWriteAction;//action ����� ������

  mftbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getMFTBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateMFTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  int offset = adrReg-BEGIN_ADR_REGISTER;
  int idxObj = offset/(REGISTERS_MFT*PART_REGISTERS_MFT);
//����� ��������� ����
  unsigned int *ranguvannja_mft = &current_settings_interfaces.ranguvannja_df_source_plus[N_BIG*idxObj]; //���������� ������
  if(((offset%(REGISTERS_MFT*PART_REGISTERS_MFT))/REGISTERS_MFT)==1)
       ranguvannja_mft = &current_settings_interfaces.ranguvannja_df_source_minus[N_BIG*idxObj]; //���������� ��������� 
  if(((offset%(REGISTERS_MFT*PART_REGISTERS_MFT))/REGISTERS_MFT)==2)
       ranguvannja_mft = &current_settings_interfaces.ranguvannja_df_source_blk[N_BIG*idxObj]; //���������� ���������� 

  int bit = getSequenceN_BIGIndexActiveBit(offset%REGISTERS_MFT, ranguvannja_mft);//������ ��������� ����
  if(bit!=-1)
    {
      int adr = decoderN_BIGACMD(bit);
      return adr<0? 0: adr+getACMDSmallBeginAdr();//������������ ������� ���� � ����� modbus  ��� rele
    }//if(bit!=N_BIG*32)
  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getMFTBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setMFTBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateMFTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(mftbigcomponent->isActiveActualData)
    {
      edition_settings = current_settings_interfaces;//������ �����
    }//if(uprbigcomponent->isActiveActualData)
  superClearActiveActualData();

  superSetOperativMarker(mftbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  //�������� �� ������
  if(!(edition_settings.configuration&(1<<EL_BIT_CONFIGURATION))) return MARKER_ERRORPERIMETR;
  //�������� �� ������������
  return validMFTN_BIGACMD(dataReg, (adrReg-BEGIN_ADR_REGISTER)/(REGISTERS_MFT*PART_REGISTERS_MFT));
}//getDOUTBigModbusRegister(int adrReg)
int setMFTBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preMFTBigReadAction(void) {
//action �� ������
  mftbigcomponent->isActiveActualData = 1;
}//
void preMFTBigWriteAction(void) {
//action �� ������
  mftbigcomponent->operativMarker[0] = -1;
  mftbigcomponent->operativMarker[1] = -1;//����������� ������
  mftbigcomponent->isActiveActualData = 1;
}//
int postMFTBigWriteAction(void) {
extern int upravlSchematic;//���� Rang
//action ����� ������
  int beginAdr = mftbigcomponent->operativMarker[0];
  if(beginAdr<0) return 0;//�� ���� ������
  int endAdr   = mftbigcomponent->operativMarker[1];
  int countAdr = endAdr-beginAdr+1;
  if(endAdr<0) countAdr = 1;
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray

  unsigned int tmp[N_BIG];//��� ���� ������������
  int idxObjOld=-1;//������ ��� ������ old
  //������ ������
  for(int i=0; i<countAdr; i++)
    {
      int offset = beginAdr-BEGIN_ADR_REGISTER+i;

      int idxObj = offset/(REGISTERS_MFT*PART_REGISTERS_MFT);
      //����� ��������� ����
      unsigned int *ranguvannja_mft = &edition_settings.ranguvannja_df_source_plus[N_BIG*idxObj]; //���������� ������
      if(((offset%(REGISTERS_MFT*PART_REGISTERS_MFT))/REGISTERS_MFT)==1)
             ranguvannja_mft = &edition_settings.ranguvannja_df_source_minus[N_BIG*idxObj]; //���������� ��������� 
      if(((offset%(REGISTERS_MFT*PART_REGISTERS_MFT))/REGISTERS_MFT)==2)
             ranguvannja_mft = &edition_settings.ranguvannja_df_source_blk[N_BIG*idxObj]; //���������� ���������� 

      if((offset/REGISTERS_MFT)!=idxObjOld) {
       idxObjOld = offset/REGISTERS_MFT;
       for(int dx=0; dx<N_BIG; dx++) tmp[dx]=ranguvannja_mft[dx];//���� ������ ����
      }//if

      int bitOld = getSequenceN_BIGIndexActiveBit(offset%REGISTERS_MFT, tmp);//������ ��������� ����
      if(bitOld!=-1) {
        ranguvannja_mft[bitOld/32] &= ~(1<<(bitOld%32));
      }//if
    }//for
  //�������� �����
  for(int i=0; i<countAdr; i++)
    {
      unsigned int adr = (unsigned short)tempWriteArray[offsetTempWriteArray+i];//����� ��������
      if(adr==0) continue;
      int offset = beginAdr-BEGIN_ADR_REGISTER+i;

      int idxObj = offset/(REGISTERS_MFT*PART_REGISTERS_MFT);
      //����� ��������� ����
      unsigned int *ranguvannja_mft = &edition_settings.ranguvannja_df_source_plus[N_BIG*idxObj]; //���������� ������
      if(((offset%(REGISTERS_MFT*PART_REGISTERS_MFT))/REGISTERS_MFT)==1)
             ranguvannja_mft = &edition_settings.ranguvannja_df_source_minus[N_BIG*idxObj]; //���������� ��������� 
      if(((offset%(REGISTERS_MFT*PART_REGISTERS_MFT))/REGISTERS_MFT)==2)
             ranguvannja_mft = &edition_settings.ranguvannja_df_source_blk[N_BIG*idxObj]; //���������� ���������� 

      int bit = encoderN_BIGACMD(adr-getACMDSmallBeginAdr()); //���������� ������ modbus � ������ ���� ��� ����
      if(bit!=-1) {
        ranguvannja_mft[bit/32] |= (1<<(bit%32));
      }//if
    }//for

      //��������� ������� - ���������
     upravlSchematic = 1;//���� Rang

  return 0;
}//

int privateMFTBigGetReg2(int adrReg)
{
  //��������� ������� ��������
 return controlPerimetr(adrReg, BEGIN_ADR_REGISTER, END_ADR_REGISTER);
}//privateGetReg2(int adrReg)

int validMFTN_BIGACMD(unsigned short dataReg, int actControl)
{
 return validBazaN_BIGACMD(dataReg, actControl+(1+SOURCEMARKER_MFT));
}//validOFN_BIGACMD(unsigned short dataReg, int actControl)

