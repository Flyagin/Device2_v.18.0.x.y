
#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 350
//�������� ������� � ����� ������
#define END_ADR_REGISTER 444

int getAISmallModbusRegister(int);//�������� ���������� ��������
int getAISmallModbusBit(int);//�������� ���������� ����
int setAISmallModbusRegister(int, int);//�������� ���������� ��������
int setAISmallModbusBit(int, int);//�������� ���������� ����

void preAISmallReadAction(void);//action �� ������
void preAISmallWriteAction(void);//action �� ������
int  postAISmallWriteAction(void);//action ����� ������
void loadAISmallActualData(void);

int privateAISmallGetReg2(int adrReg);

COMPONENT_OBJ *aismallcomponent;

/**************************************/
//��������� ���������
/**************************************/
void constructorAISmallComponent(COMPONENT_OBJ *aismallcomp)
{
  aismallcomponent = aismallcomp;

  aismallcomponent->getModbusRegister = getAISmallModbusRegister;//�������� ���������� ��������
  aismallcomponent->getModbusBit      = getAISmallModbusBit;//�������� ���������� ����
  aismallcomponent->setModbusRegister = setAISmallModbusRegister;//�������� ���������� ��������
  aismallcomponent->setModbusBit      = setAISmallModbusBit;//�������� ���������� ����

  aismallcomponent->preReadAction   = preAISmallReadAction;//action �� ������
  aismallcomponent->preWriteAction  = preAISmallWriteAction;//action �� ������
  aismallcomponent->postWriteAction = postAISmallWriteAction;//action ����� ������

  aismallcomponent->isActiveActualData = 0;
}//constructorIUSmallComponent(COMPONENT_OBJ *iucomp)

int getAISmallModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateAISmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
    int offset = adrReg-BEGIN_ADR_REGISTER;
  semaphore_measure_values_low1 = 1;
  for (unsigned int i = 0; i < MAX_NUMBER_INDEXES_RESISTANCE; i++ ) 
  {
    int temp_value = resistance_middle[i];
    if (temp_value==UNDEF_RESISTANCE) temp_value = 0;
    if (temp_value < 0) temp_value = -temp_value;
    resistance_low[i] =temp_value;
  }
  semaphore_measure_values_low1 = 0;
  //������� ����������
  semaphore_measure_values_low1 = 1;
  for (unsigned int i = 0; i < _NUMBER_IM; i++ ) 
  {
    measurement_low[i] = measurement_middle[i];
  }
  semaphore_measure_values_low1 = 0;

    switch (offset)
    {
    case 0://UA
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 350;
#else
        return (measurement_low[IM_UA] >> 3) &0xFFFF;
#endif
      }
    case 1://UB
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 351;
#else
        return (measurement_low[IM_UB] >> 3) &0xFFFF;
#endif
      }
    case 2://UC
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 352;
#else
        return (measurement_low[IM_UC] >> 3) &0xFFFF;
#endif
      }

    case 3://IA
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 353;
#else
        return (measurement_low[IM_IA] >> 2) &0xFFFF;
#endif
      }
    case 4://IB
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 354;
#else
        return (measurement_low[IM_IB] >> 2) &0xFFFF;
#endif
      }
    case 5://IC
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 355;
#else
        return (measurement_low[IM_IC] >> 2) &0xFFFF;
#endif
      }

    case 7://P
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 357;
#else
        return (P[bank_for_calc_power]/50) &0xFFFF;
#endif
      }
    case 8://P
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 358;
#else
        return (Q[bank_for_calc_power]/50) &0xFFFF;
#endif
      }
    case 9://P
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 359;
#else
        return (S[bank_for_calc_power]/50) &0xFFFF;
#endif
      }
    case 10://cos f
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 360;
#else
        if (S[bank_for_calc_power] != 0)
          return (cos_phi_x1000[bank_for_calc_power]) &0xFFFF;
          return 0x0;
#endif
      }
    case 11://3I0
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 361;
#else
        return (measurement_low[IM_3I0]) &0xFFFF;
#endif
      }
    case 12://freq
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 362;
#else
        int int_frequency = (int)(frequency*100);
        
        if (int_frequency > 0 /*�� ����� ������ - ������� �� ���������*/)
          return (int_frequency) &0xFFFF;
        else
        {
          if (int_frequency == (-1*100))
            return (-1)&0x0000FFFF;
          else if (int_frequency == (-2*100))
            return (-2)&0x0000FFFF;
          else if (int_frequency == (-3*100))
            return (-3)&0x0000FFFF;
          else
            return (-4)&0x0000FFFF;
        }
#endif
      } break;
    case 13://Ea+
    case 14://Ea+
    case 15://Ea-
    case 16://Ea-
    case 17://Eq1
    case 18://Eq1
    case 19://Eq2
    case 20://Eq2
    case 21://Eq3
    case 22://Eq3
    case 23://Eq4
    case 24://Eq4
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 363+(offset-13);
#else
        unsigned int enrg = (unsigned int)(energy[0][(offset-13) >> 1]*1000.0);
        if((offset-13)&1)
          //�������� ������ �����
        return (enrg>> 16)& 0xffff;
          //�������� ������� �����
        return enrg& 0xffff;
#endif
      } break;
    case 25://UAB
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 375;
#else
        return (measurement_low[IM_UAB] >> 3) &0xFFFF;
#endif
      }
    case 26://UBC
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 376;
#else
        return (measurement_low[IM_UBC] >> 3) &0xFFFF;
#endif
      }
    case 27://UCA
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 377;
#else
        return (measurement_low[IM_UCA] >> 3) &0xFFFF;
#endif
      }
    case 28://3U0
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 378;
#else
        return (measurement_low[IM_3U0] >> 3) &0xFFFF;
#endif
      }
    case 29://3I0-1
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 379;
#else
        return (measurement_low[IM_3I0_r] >> 2) &0xFFFF;
#endif
      }
    case 30://IM_3I0_other_g
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 380;
#else
        return (measurement_low[IM_3I0_other_g]) &0xFFFF;
#endif
      }
    case 31://IM_I1
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 381;
#else
        return (measurement_low[IM_I1] >> 2) &0xFFFF;
#endif
      }
    case 32://IM_I2
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 382;
#else
        return (measurement_low[IM_I2] >> 2) &0xFFFF;
#endif
      }
//    case 33://Iah2
//    case 34://Ibh2
//    case 35://Ich2
//    case 36://Uab TCH
//    case 37://Ubc TCH
//    case 38://Ua TH2
//    case 39://Ub TH2
//    case 40://Uc TH2
//    case 41://Uab TH2
//    case 42://Ubc TH2
//    case 43://Uca TH2
    case 44://U1
#ifdef TESTZBIRKA_VERSII_PZ
        return 394;
#else
        return (measurement_low[IM_U1] >> 3) &0xFFFF;
#endif
    case 45://U2
#ifdef TESTZBIRKA_VERSII_PZ
        return 395;
#else
        return (measurement_low[IM_U2] >> 3) &0xFFFF;
#endif
//    case 46://freq TH2
//    case 47://Z0
    case 48://RA
#ifdef TESTZBIRKA_VERSII_PZ
        return 398;
#else
        return (resistance_low[R_A] /100) &0xFFFF;
#endif
    case 49://XA
#ifdef TESTZBIRKA_VERSII_PZ
        return 399;
#else
        return (resistance_low[X_A] /100) &0xFFFF;
#endif
    case 50://ZA
#ifdef TESTZBIRKA_VERSII_PZ
        return 400;
#else
        return (resistance_low[Z_A] /100) &0xFFFF;
#endif
    case 51://RB
#ifdef TESTZBIRKA_VERSII_PZ
        return 401;
#else
        return (resistance_low[R_B] /100) &0xFFFF;
#endif
    case 52://XB
#ifdef TESTZBIRKA_VERSII_PZ
        return 402;
#else
        return (resistance_low[X_B] /100) &0xFFFF;
#endif
    case 53://ZB
#ifdef TESTZBIRKA_VERSII_PZ
        return 403;
#else
        return (resistance_low[Z_B] /100) &0xFFFF;
#endif
    case 54://RC
#ifdef TESTZBIRKA_VERSII_PZ
        return 404;
#else
        return (resistance_low[R_�] /100) &0xFFFF;
#endif
    case 55://XC
#ifdef TESTZBIRKA_VERSII_PZ
        return 405;
#else
        return (resistance_low[X_�] /100) &0xFFFF;
#endif
    case 56://ZC
#ifdef TESTZBIRKA_VERSII_PZ
        return 406;
#else
        return (resistance_low[Z_C] /100) &0xFFFF;
#endif

    case 57://RAB
#ifdef TESTZBIRKA_VERSII_PZ
        return 407;
#else
        return (resistance_low[R_AB] /100) &0xFFFF;
#endif
    case 58://ZAB
#ifdef TESTZBIRKA_VERSII_PZ
        return 408;
#else
        return (resistance_low[X_AB] /100) &0xFFFF;
#endif
    case 59://ZAB
#ifdef TESTZBIRKA_VERSII_PZ
        return 409;
#else
        return (resistance_low[Z_AB] /100) &0xFFFF;
#endif

    case 60://RBC
#ifdef TESTZBIRKA_VERSII_PZ
        return 410;
#else
        return (resistance_low[R_BC] /100) &0xFFFF;
#endif
    case 61://XBC
#ifdef TESTZBIRKA_VERSII_PZ
        return 411;
#else
        return (resistance_low[X_BC] /100) &0xFFFF;
#endif
    case 62://ZBC
#ifdef TESTZBIRKA_VERSII_PZ
        return 412;
#else
        return (resistance_low[Z_BC] /100) &0xFFFF;
#endif

    case 63://RCA
#ifdef TESTZBIRKA_VERSII_PZ
        return 413;
#else
        return (resistance_low[R_CA] /100) &0xFFFF;
#endif
    case 64://XCA
#ifdef TESTZBIRKA_VERSII_PZ
        return 414;
#else
        return (resistance_low[X_CA] /100) &0xFFFF;
#endif
    case 65://ZCA
#ifdef TESTZBIRKA_VERSII_PZ
        return 415;
#else
        return (resistance_low[Z_CA] /100) &0xFFFF;
#endif

    case 66://baza
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 416;
#else
        if (base_index_for_angle <= FULL_ORT_3U0) return (base_index_for_angle + 1) &0xFFFF;
        else
        {
          //���������� ����� ����� �� ���� � ����
          total_error_sw_fixed(72);
          return 0;
        }
#endif
      } break;
    case 67://OFFSET_ANGLE_UA_1
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 417;
#else
        return ((unsigned int)phi_angle[bank_for_calc_phi_angle][FULL_ORT_Ua]) &0xFFFF;
#endif
      }
    case 68://OFFSET_ANGLE_UB_1
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 418;
#else
        return ((unsigned int)phi_angle[bank_for_calc_phi_angle][FULL_ORT_Ub]) &0xFFFF;
#endif
      }
    case 69://OFFSET_ANGLE_UC_1
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 419;
#else
        return ((unsigned int)phi_angle[bank_for_calc_phi_angle][FULL_ORT_Uc]) &0xFFFF;
#endif
      }
    case 70://OFFSET_ANGLE_UAB_1
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 420;
#else
        return ((unsigned int)phi_angle[bank_for_calc_phi_angle][FULL_ORT_Uab]) &0xFFFF;
#endif
      }
    case 71://OFFSET_ANGLE_UBC_1
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 421;
#else
        return ((unsigned int)phi_angle[bank_for_calc_phi_angle][FULL_ORT_Ubc]) &0xFFFF;
#endif
      }
    case 72://OFFSET_ANGLE_UCA_1
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 422;
#else
        return ((unsigned int)phi_angle[bank_for_calc_phi_angle][FULL_ORT_Uca]) &0xFFFF;
#endif
      }
    case 73://OFFSET_ANGLE_3U0_1
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 423;
#else
        return ((unsigned int)phi_angle[bank_for_calc_phi_angle][FULL_ORT_3U0]) &0xFFFF;
#endif
      }
//    case 74://OFFSET_ANGLE_UA_2
//    case 75://OFFSET_ANGLE_UB_2
//    case 76://OFFSET_ANGLE_UC_2
//    case 77://OFFSET_ANGLE_UAB_2
//    case 78://OFFSET_ANGLE_UBC_2
//    case 79://OFFSET_ANGLE_UCA_2
    case 80://OFFSET_ANGLE_Ia_1
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 430;
#else
        return ((unsigned int)phi_angle[bank_for_calc_phi_angle][FULL_ORT_Ia]) &0xFFFF;
#endif
      }
    case 81://OFFSET_ANGLE_Ib_1
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 431;
#else
        return ((unsigned int)phi_angle[bank_for_calc_phi_angle][FULL_ORT_Ib]) &0xFFFF;
#endif
      }
    case 82://OFFSET_ANGLE_Ic_1
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 432;
#else
        return ((unsigned int)phi_angle[bank_for_calc_phi_angle][FULL_ORT_Ic]) &0xFFFF;
#endif
      }
//    case 83://OFFSET_ANGLE_I04
//      {
//#ifdef TESTZBIRKA_VERSII_PZ
//        return 433;
//#else
//        return ((unsigned int)phi_angle[bank_for_calc_phi_angle][FULL_ORT_I04]) &0xFFFF;
//#endif
//      }
    case 84://OFFSET_ANGLE_3I0_1
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 434;
#else
        return ((unsigned int)phi_angle[bank_for_calc_phi_angle][FULL_ORT_3I0]) &0xFFFF;
#endif
      }
    case 85://OFFSET_ANGLE_3I0_r
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 435;
#else
        return ((unsigned int)phi_angle[bank_for_calc_phi_angle][FULL_ORT_3I0_r]) &0xFFFF;
#endif
      }
//    case 86://
//    case 87://
//    case 88://
//    case 89://
//    case 90://
    case 91://
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 441;
#else
        return resurs_vidkljuchennja & 0xffff;
#endif
      }
    case 92://
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 442;
#else
        return (resurs_vidkljuchennja >> 16) & 0xffff;
#endif
      }
    case 93://
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 443;
#else
        return resurs_vymykacha & 0xffff;
#endif
      }
    case 94://
      {
#ifdef TESTZBIRKA_VERSII_PZ
        return 444;
#else
        return (resurs_vymykacha >> 16) & 0xffff;
#endif
      }

    }//switch
    return 0;
}//getDVModbusRegister(int adrReg)
int getAISmallModbusBit(int x) {
  //�������� ���������� bit
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getIUModbusBit(int )
int setAISmallModbusRegister(int x, int y) {
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//setIUModbusRegister(int, int)
int setAISmallModbusBit(int x, int y) {
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� bit
  return MARKER_OUTPERIMETR;
}//setIUModbusBit(int, int )

void preAISmallReadAction(void) {
//action �� ������
  aismallcomponent->isActiveActualData = 1;
}//

void preAISmallWriteAction(void) {
//action �� ������
  aismallcomponent->operativMarker[0] = -1;
  aismallcomponent->operativMarker[1] = -1;//����������� ������
  aismallcomponent->isActiveActualData = 1;
}//
int postAISmallWriteAction(void) {
//action ����� ������
 return 0;
}//

int privateAISmallGetReg2(int adrReg)
{
  //��������� ������� ��������
 return controlPerimetr(adrReg, BEGIN_ADR_REGISTER, END_ADR_REGISTER);
}//privateGetReg2(int adrReg)

