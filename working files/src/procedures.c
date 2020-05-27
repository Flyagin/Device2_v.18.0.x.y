#include "header.h"

/*****************************************************/
//������� ���������� ������ ��� ��� ������������
/*****************************************************/
unsigned int action_after_changing_of_configuration(unsigned int new_configuration, __SETTINGS *target_label)
{
  unsigned int error_window = 0;
  
  /************************/
  //������ ���������� �� �� ����������� ����� �� � ������ ���, ��� ��������� �������� ������ ������������
  /************************/
  //�������� ��
  if ((new_configuration & ( 1<< DZ_BIT_CONFIGURATION )) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_DZ)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_DZ) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_DZ) 
       )  
       ||  
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_DZ_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_DZ_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_DZ_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_DZ_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_DZ)
      )
      error_window |= (1 << DZ_BIT_CONFIGURATION );
  }
  //�������� ���
  if ((new_configuration & ( 1<< MTZ_BIT_CONFIGURATION )) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_MTZ)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_MTZ) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_MTZ) 
       )  
       ||  
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_MTZ_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_MTZ_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_MTZ_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_MTZ_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_MTZ)
      )
      error_window |= (1 << MTZ_BIT_CONFIGURATION );
  }
  //�������� ���
  if ((new_configuration & (1<<ZDZ_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_ZDZ) 
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_TIMEOUT_GROUP1_ZDZ) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_TIMEOUT_GROUP4_ZDZ) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_ZDZ_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_ZDZ_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_ZDZ        )
      )
      error_window |= (1 << ZDZ_BIT_CONFIGURATION );
  }
  //�������� ��
  if ((new_configuration & (1<<ZZ_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_ZZ)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_ZZ) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_ZZ) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_ZZ_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_ZZ_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_ZZ_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_ZZ_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_ZZ        )
      )
      error_window |= (1 << ZZ_BIT_CONFIGURATION );
  }
  //�������� ����
  if ((new_configuration & (1<<TZNP_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_TZNP)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_TZNP) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_TZNP) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_TZNP_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_TZNP_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_TZNP_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_TZNP_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_TZNP        )
      )
      error_window |= (1 << TZNP_BIT_CONFIGURATION );
  }
  //�������� ���
  if ((new_configuration & (1<<APV_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_APV)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_TIMEOUT_GROUP1_APV) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_TIMEOUT_GROUP4_APV) 
       )  
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_APV_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_APV_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_APV        )
      )
      error_window |= (1 << APV_BIT_CONFIGURATION );
  }
  //�������� ���-����
  if ((new_configuration & (1<<ACHR_CHAPV_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_ACHR_CHAPV)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_ACHR_CHAPV) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_ACHR_CHAPV) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_ACHR_CHAPV_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_ACHR_CHAPV_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_ACHR_CHAPV_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_ACHR_CHAPV_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_ACHR_CHAPV        )
      )
      error_window |= (1 << ACHR_CHAPV_BIT_CONFIGURATION );
  }
  //�������� ����
  if ((new_configuration & (1<<UROV_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UROV)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UROV) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UROV) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_UROV_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_UROV_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_UROV_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_UROV_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_UROV        )
      )
      error_window |= (1 << UROV_BIT_CONFIGURATION );
  }
  //�������� ���(���)
  if ((new_configuration & (1<<ZOP_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_ZOP)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_ZOP) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_ZOP) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_ZOP_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_ZOP_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_ZOP_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_ZOP_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_ZOP        )
      )
      error_window |= (1 << ZOP_BIT_CONFIGURATION );
  }
  //�������� Umin
  if ((new_configuration & (1<<UMIN_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UMIN)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMIN) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UMIN) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_UMIN_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_UMIN_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_UMIN_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_UMIN_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_UMIN        )
      )
      error_window |= (1 << UMIN_BIT_CONFIGURATION );
  }
  //�������� Umax
  if ((new_configuration & (1<<UMAX_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UMAX)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UMAX) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UMAX) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_UMAX_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_UMAX_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_UMAX_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_UMAX_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_UMAX        )
      )
      error_window |= (1 << UMAX_BIT_CONFIGURATION );
  }
  //�������� ������������ �������
  if ((new_configuration & (1<<UP_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_UP)
       || 
       (
        (current_ekran.current_level >= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP1_UP) &&
        (current_ekran.current_level <= EKRAN_CHOOSE_SETPOINT_TIMEOUT_GROUP4_UP) 
       )  
       ||
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_UP_GROUP1) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_UP_GROUP4)
       )
       ||  
       (
        (current_ekran.current_level >= EKRAN_TIMEOUT_UP_GROUP1) &&
        (current_ekran.current_level <= EKRAN_TIMEOUT_UP_GROUP4)
       )
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_UP        )
      )
      error_window |= (1 << UP_BIT_CONFIGURATION );
  }
  //�������� "���������� ���� �����������"
  if ((new_configuration & (1<<VMP_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level == EKRAN_CHOOSE_SETTINGS_VMP)
       || 
       (
        (current_ekran.current_level >= EKRAN_SETPOINT_VMP_FORWARD) &&
        (current_ekran.current_level <= EKRAN_SETPOINT_VMP_BACKWARD) 
       )  
       ||  
       (current_ekran.current_level == EKRAN_CONTROL_VMP              )
      )
      error_window |= (1 << VMP_BIT_CONFIGURATION );
  }
  //�������� "��������� �����"
  if ((new_configuration & (1<<EL_BIT_CONFIGURATION)) == 0)
  {
    if(
       (current_ekran.current_level >= EKRAN_EXTENDED_LIGIC) &&
       (current_ekran.current_level <= EKRAN_RANGUVANNJA_D_NOT16)  
      )
      error_window |= (1 << EL_BIT_CONFIGURATION );
  }
  /************************/
  
  if (error_window == 0)
  {
    //������� ���� ����������� � ������� ���������
    target_label->configuration = new_configuration;
    
    unsigned int maska[N_SMALL] = {0, 0, 0}, maska_1[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  
    //����������, �� �� ����� ����� � ������������
    if ((target_label->configuration & (1<<DZ_BIT_CONFIGURATION)) == 0)
    {
      //������� ������ ��
      target_label->control_dz &= (unsigned int)(~(
                                                    MASKA_FOR_BIT(INDEX_CTR_DZ1)      |
                                                    MASKA_FOR_BIT(INDEX_CTR_DZ1_AMTZ) |
                                                    MASKA_FOR_BIT(INDEX_CTR_DZ2)      |
                                                    MASKA_FOR_BIT(INDEX_CTR_DZ2_AMTZ) |
                                                    MASKA_FOR_BIT(INDEX_CTR_DZ3)      |
                                                    MASKA_FOR_BIT(INDEX_CTR_DZ3_AMTZ) |
                                                    MASKA_FOR_BIT(INDEX_CTR_DZ4)      |
                                                    MASKA_FOR_BIT(INDEX_CTR_DZ4_AMTZ)
                                                   )
                                                 );
   
      //������� ������ �� � ���
      target_label->control_apv &= (unsigned int)(~(
                                                    CTR_APV_STARTED_FROM_DZ1    |
                                                    CTR_APV_STARTED_FROM_AMTDZ1 |
                                                    CTR_APV_STARTED_FROM_DZ2    |
                                                    CTR_APV_STARTED_FROM_AMTDZ2 |
                                                    CTR_APV_STARTED_FROM_DZ3    |
                                                    CTR_APV_STARTED_FROM_AMTDZ3 |
                                                    CTR_APV_STARTED_FROM_DZ4    |
                                                    CTR_APV_STARTED_FROM_AMTDZ4
                                                   )
                                                 );

      
      //������� ������ �� � ����
      target_label->control_urov &= (uint64_t)(~(
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_DZ1)    | 
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_AMTDZ1) | 
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_DZ2)    | 
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_AMTDZ2) | 
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_DZ3)    | 
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_AMTDZ3) | 
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_DZ4)    |
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_AMTDZ4) 
                                                )
                                               );
      
      //������� ����� ������� ��
      for (unsigned int i = 0; i < N_SMALL; i++ ) maska[i] = 0;
      for (int i = 0; i < NUMBER_DZ_SIGNAL_FOR_RANG_SMALL; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + 
                  i
                 )
                );

      for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
      for (int i = 0; i < NUMBER_DZ_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG + 
                  i
                 )
                );
      
      //������ �� ������� ��� ���������� �����, �� ���������� �� ��
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
      {
        target_label->ranguvannja_buttons[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_buttons[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_buttons[N_SMALL*i+2] &= ~maska[2];
      }

      //������ �� ������� ��� ���������� �����, �� ���������� �� ��
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_inputs[N_SMALL*i+2] &= ~maska[2];
      }
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� ����������� � ����������� ����������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }

    //����������, �� ��� ����� ����� � ������������
    if ((target_label->configuration & (1<<MTZ_BIT_CONFIGURATION)) == 0)
    {
      //������� ������ ���
      target_label->control_mtz &= (unsigned int)(~(CTR_MTZ_1 | CTR_MTZ_2 | CTR_MTZ_3 | CTR_MTZ_4));
   
      //������� ������ ��� � ���
      target_label->control_apv &= (unsigned int)(~(CTR_APV_STARTED_FROM_MTZ1 | CTR_APV_STARTED_FROM_MTZ2 | CTR_APV_STARTED_FROM_MTZ3  | CTR_APV_STARTED_FROM_MTZ4));

      //�������� �������� ��� �� �������
      int32_t ctrl_zdz_type_tmp = target_label->ctrl_zdz_type;
      if (
          (ctrl_zdz_type_tmp == ZDZ_CTRL_I      ) ||
          (ctrl_zdz_type_tmp == ZDZ_CTRL_I_OR_U ) ||
          (ctrl_zdz_type_tmp == ZDZ_CTRL_I_AND_U)
         )
        target_label->ctrl_zdz_type = ZDZ_CTRL_NONE;
      //������� ������ ��� � ���
      target_label->control_zdz &= (unsigned int)(~(
                                                    MASKA_FOR_BIT(CTR_ZDZ_STARTED_FROM_MTZ1_BIT - (_CTR_ZDZ_PART_III - _CTR_ZDZ_PART_II)) | 
                                                    MASKA_FOR_BIT(CTR_ZDZ_STARTED_FROM_MTZ2_BIT - (_CTR_ZDZ_PART_III - _CTR_ZDZ_PART_II)) | 
                                                    MASKA_FOR_BIT(CTR_ZDZ_STARTED_FROM_MTZ3_BIT - (_CTR_ZDZ_PART_III - _CTR_ZDZ_PART_II)) | 
                                                    MASKA_FOR_BIT(CTR_ZDZ_STARTED_FROM_MTZ4_BIT - (_CTR_ZDZ_PART_III - _CTR_ZDZ_PART_II))
                                                   ));
      
      //������� ������ ��� � ����
      target_label->control_urov &= (uint64_t)(~(
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_MTZ1) | 
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_MTZ2) | 
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_MTZ3) | 
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_MTZ4)
                                                )
                                               );
      
      //������� ����� ������� ���
      for (unsigned int i = 0; i < N_SMALL; i++ ) maska[i] = 0;
      for (int i = 0; i < NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + 
                  NUMBER_DZ_SIGNAL_FOR_RANG_SMALL      +
                  i
                 )
                );

      for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
      for (int i = 0; i < NUMBER_MTZ_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG + 
                  NUMBER_DZ_SIGNAL_FOR_RANG      +
                  i
                 )
                );
      
      //������ �� ������� ��� ���������� �����, �� ���������� �� ���
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
      {
        target_label->ranguvannja_buttons[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_buttons[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_buttons[N_SMALL*i+2] &= ~maska[2];
      }

      //������ �� ������� ��� ���������� �����, �� ���������� �� ���
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_inputs[N_SMALL*i+2] &= ~maska[2];
      }
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� ����������� � ����������� ����������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }

    //����������, �� ��� ����� ����� � ������������
    if ((target_label->configuration & (1<<ZDZ_BIT_CONFIGURATION)) == 0)
    {
      //������� ���
      target_label->control_zdz &= (unsigned int)(~MASKA_FOR_BIT(CTR_ZDZ_STATE_BIT));

      //������� ������ ��� � ����
      target_label->control_urov &= (uint64_t)(~MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_ZDZ));
      
      //������� ���� ������� ���
      for (unsigned int i = 0; i < N_SMALL; i++ ) maska[i] = 0;
      for (int i = 0; i < NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL    + 
                  NUMBER_DZ_SIGNAL_FOR_RANG_SMALL         +
                  NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL        +
                  i
                 )
                );
     
      for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
      for (int i = 0; i < NUMBER_ZDZ_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG    + 
                  NUMBER_DZ_SIGNAL_FOR_RANG         +
                  NUMBER_MTZ_SIGNAL_FOR_RANG        +
                  i
                 )
                );

      //������ �� ������� ��� ���������� �����, �� ���������� �� ���
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
      {
        target_label->ranguvannja_buttons[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_buttons[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_buttons[N_SMALL*i+2] &= ~maska[2];
      }

      //������ �� ������� ��� ���������� �����, �� ���������� �� ���
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_inputs[N_SMALL*i+2] &= ~maska[2];
      }
      //������ �� ������� ��� ���������� ������, �� ���������� �� ���
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� ����������� � ����������� ����������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }

    //����������, �� �� ����� ����� � ������������
    if ((target_label->configuration & (1<<ZZ_BIT_CONFIGURATION)) == 0)
    {
      //������� ��
      target_label->control_zz &= (unsigned int)(~(CTR_ZZ1_3I0_STATE | CTR_ZZ1_3U0_STATE | CTR_ZZ1_NZZ_STATE));
   
      //�������� �������� ��� �� ������� 3I0
      int32_t ctrl_zdz_type_tmp = target_label->ctrl_zdz_type;
      if (
          (ctrl_zdz_type_tmp == ZDZ_CTRL_3I0)
         )
        target_label->ctrl_zdz_type = ZDZ_CTRL_NONE;

      //������� ������� 3I0, 3U0 � ��� � ����
      target_label->control_urov &= (uint64_t)(
                                               ~(
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_3I0) | 
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_3U0) |
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_NZZ)
                                                )
                                              );

      //������� ���� ������� ��
      for (unsigned int i = 0; i < N_SMALL; i++ ) maska[i] = 0;
      for (int i = 0; i < NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + 
                  NUMBER_DZ_SIGNAL_FOR_RANG_SMALL      +
                  NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL     +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL     +
                  i
                 )
                );

      for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
      for (int i = 0; i < NUMBER_ZZ_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG + 
                  NUMBER_DZ_SIGNAL_FOR_RANG      +
                  NUMBER_MTZ_SIGNAL_FOR_RANG     +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG     +
                  i
                 )
                );
      
      //������ �� ������� ��� ���������� �����, �� ���������� �� ��
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
      {
        target_label->ranguvannja_buttons[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_buttons[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_buttons[N_SMALL*i+2] &= ~maska[2];
      }

      //������ �� ������� ��� ���������� �����, �� ���������� �� ��
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_inputs[N_SMALL*i+2] &= ~maska[2];
      }
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� ����������� � ����������� ����������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }
  
    //����������, �� ���� ����� ����� � ������������
    if ((target_label->configuration & (1<<TZNP_BIT_CONFIGURATION)) == 0)
    {
      //������� ������ ����
      target_label->control_tznp &= (unsigned int)(~(CTR_TZNP1 | CTR_TZNP2 | CTR_TZNP3));
   
      //������� ������ ��� � ���
      target_label->control_apv &= (unsigned int)(~(CTR_APV_STARTED_FROM_TZNP1 | CTR_APV_STARTED_FROM_TZNP2 | CTR_APV_STARTED_FROM_TZNP3));

      //������� ������ ���� � ����
      target_label->control_urov &= (uint64_t)(
                                               ~(
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_TZNP1) |
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_TZNP2) |
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_TZNP3)
                                                )
                                              );
      
      //������� ���� ������� ����
      for (unsigned int i = 0; i < N_SMALL; i++ ) maska[i] = 0;
      for (int i = 0; i < NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + 
                  NUMBER_DZ_SIGNAL_FOR_RANG_SMALL      +
                  NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL     +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL     +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL      +
                  i
                 )
                );

      for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
      for (int i = 0; i < NUMBER_TZNP_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG + 
                  NUMBER_DZ_SIGNAL_FOR_RANG      +
                  NUMBER_MTZ_SIGNAL_FOR_RANG     +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG     +
                  NUMBER_ZZ_SIGNAL_FOR_RANG      +
                  i
                 )
                );
      
      //������ �� ������� ��� ���������� �����, �� ���������� �� ����
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
      {
        target_label->ranguvannja_buttons[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_buttons[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_buttons[N_SMALL*i+2] &= ~maska[2];
      }

      //������ �� ������� ��� ���������� �����, �� ���������� �� ����
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_inputs[N_SMALL*i+2] &= ~maska[2];
      }
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� ����������� � ����������� ����������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }

    //����������, �� ��� ����� ����� � ������������
    if ((target_label->configuration & (1<<APV_BIT_CONFIGURATION)) == 0)
    {
      //������� ���
      target_label->control_apv &= (unsigned int)(~(CTR_APV_STAGE_1 | CTR_APV_STAGE_2 | CTR_APV_STAGE_3 | CTR_APV_STAGE_4));
   
      //������� ���� ������� ���
      for (unsigned int i = 0; i < N_SMALL; i++ ) maska[i] = 0;
      for (int i = 0; i < NUMBER_APV_SIGNAL_FOR_RANG_SMALL; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + 
                  NUMBER_DZ_SIGNAL_FOR_RANG_SMALL      +
                  NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL     +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL     +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL      +
                  NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL    +
                  i
                 )
                );

      for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
      for (int i = 0; i < NUMBER_APV_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG + 
                  NUMBER_DZ_SIGNAL_FOR_RANG      +
                  NUMBER_MTZ_SIGNAL_FOR_RANG     +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG     +
                  NUMBER_ZZ_SIGNAL_FOR_RANG      +
                  NUMBER_TZNP_SIGNAL_FOR_RANG    +
                  i
                 )
                );
      
      //������ �� ������� ��� ���������� �����, �� ���������� �� ���
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
      {
        target_label->ranguvannja_buttons[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_buttons[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_buttons[N_SMALL*i+2] &= ~maska[2];
      }

      //������ �� ������� ��� ���������� �����, �� ���������� �� ���
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_inputs[N_SMALL*i+2] &= ~maska[2];
      }
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� ����������� � ����������� ����������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }

    //����������, �� ���-���� ����� ����� � ������������
    if ((target_label->configuration & (1<<ACHR_CHAPV_BIT_CONFIGURATION)) == 0)
    {
      //������� ���-����
      target_label->control_achr_chapv &= (unsigned int)(~(CTR_ACHR1 | CTR_CHAPV1 | CTR_ACHR2 | CTR_CHAPV2));

      //������� ������� ��� � ����
      target_label->control_urov &= (uint64_t)(
                                               ~(
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_ACHR1) |
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_ACHR2)
                                                )
                                              );
      
      //������� ���� ������� ���-����
      for (unsigned int i = 0; i < N_SMALL; i++ ) maska[i] = 0;
      for (int i = 0; i < NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + 
                  NUMBER_DZ_SIGNAL_FOR_RANG_SMALL      +
                  NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL     +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL     +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL      +
                  NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL    +
                  NUMBER_APV_SIGNAL_FOR_RANG_SMALL     +
                  i
                 )
                );
     
      for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
      for (int i = 0; i < NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG + 
                  NUMBER_DZ_SIGNAL_FOR_RANG      +
                  NUMBER_MTZ_SIGNAL_FOR_RANG     +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG     +
                  NUMBER_ZZ_SIGNAL_FOR_RANG      +
                  NUMBER_TZNP_SIGNAL_FOR_RANG    +
                  NUMBER_APV_SIGNAL_FOR_RANG     +
                  i
                 )
                );

      //������ �� ������� ��� ���������� �����, �� ���������� �� ���-����
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
      {
        target_label->ranguvannja_buttons[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_buttons[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_buttons[N_SMALL*i+2] &= ~maska[2];
      }

      //������ �� ������� ��� ���������� �����, �� ���������� �� ���-����
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_inputs[N_SMALL*i+2] &= ~maska[2];
      }
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� ����������� � ����������� ����������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }

    //����������, �� ���� ����� ����� � ������������
    if ((target_label->configuration & (1<<UROV_BIT_CONFIGURATION)) == 0)
    {
      //������� ����
      target_label->control_urov &= (uint64_t)(~MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STATE));
   
      //������� �������� ����2 � ���
      target_label->control_apv &= (unsigned int)(~MASKA_FOR_BIT(INDEX_ML_CTRAPV_BLK_CTRL_PRVV2));
   
        //������� ���� ������� ����
      for (unsigned int i = 0; i < N_SMALL; i++ ) maska[i] = 0;
      for (int i = 0; i < NUMBER_UROV_SIGNAL_FOR_RANG_SMALL; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL    + 
                  NUMBER_DZ_SIGNAL_FOR_RANG_SMALL         +
                  NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL         +
                  NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL       +
                  NUMBER_APV_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL +
                  i
                 )
                );
     
      for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
      for (int i = 0; i < NUMBER_UROV_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG    + 
                  NUMBER_DZ_SIGNAL_FOR_RANG         +
                  NUMBER_MTZ_SIGNAL_FOR_RANG        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG         +
                  NUMBER_TZNP_SIGNAL_FOR_RANG       +
                  NUMBER_APV_SIGNAL_FOR_RANG        +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG +
                  i
                 )
                );

      //������ �� ������� ��� ���������� �����, �� ���������� �� ����
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
      {
        target_label->ranguvannja_buttons[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_buttons[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_buttons[N_SMALL*i+2] &= ~maska[2];
      }

      //������ �� ������� ��� ���������� �����, �� ���������� �� ����
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_inputs[N_SMALL*i+2] &= ~maska[2];
      }
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� ����������� � ����������� ����������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }

    //����������, �� ���(���) ����� ����� � ������������
    if ((target_label->configuration & (1<<ZOP_BIT_CONFIGURATION)) == 0)
    {
      //������� ���(���)
      target_label->control_zop &= (unsigned int)(~CTR_ZOP_STATE);
   
      //������� ������� ���(���) � ����
      target_label->control_urov &= (uint64_t)(~MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_ZOP1));

      //������� ���� ������� ���(���)
      for (unsigned int i = 0; i < N_SMALL; i++ ) maska[i] = 0;
      for (int i = 0; i < NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL    + 
                  NUMBER_DZ_SIGNAL_FOR_RANG_SMALL         +
                  NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL         +
                  NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL       +
                  NUMBER_APV_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL +
                  NUMBER_UROV_SIGNAL_FOR_RANG_SMALL       +
                  i
                 )
                );
     
      for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
      for (int i = 0; i < NUMBER_ZOP_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG    + 
                  NUMBER_DZ_SIGNAL_FOR_RANG         +
                  NUMBER_MTZ_SIGNAL_FOR_RANG        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG         +
                  NUMBER_TZNP_SIGNAL_FOR_RANG       +
                  NUMBER_APV_SIGNAL_FOR_RANG        +
                  NUMBER_UROV_SIGNAL_FOR_RANG       +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG +
                  i
                 )
                );

      //������ �� ������� ��� ���������� �����, �� ���������� �� ���(���)
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
      {
        target_label->ranguvannja_buttons[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_buttons[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_buttons[N_SMALL*i+2] &= ~maska[2];
      }

      //������ �� ������� ��� ���������� �����, �� ���������� �� ���(���)
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_inputs[N_SMALL*i+2] &= ~maska[2];
      }
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� ����������� � ����������� ����������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }

    //����������, �� Umin ����� ����� � ������������
    if ((target_label->configuration & (1<<UMIN_BIT_CONFIGURATION)) == 0)
    {
      //������� ������ Umin
      target_label->control_Umin &= (unsigned int)(~(CTR_UMIN1 | CTR_UMIN2));
   
      //�������� �������� ��� �� ��������
      int32_t ctrl_zdz_type_tmp = target_label->ctrl_zdz_type;
      if (
          (ctrl_zdz_type_tmp == ZDZ_CTRL_U      ) ||
          (ctrl_zdz_type_tmp == ZDZ_CTRL_I_OR_U ) ||
          (ctrl_zdz_type_tmp == ZDZ_CTRL_I_AND_U)
         )
        target_label->ctrl_zdz_type = ZDZ_CTRL_NONE;
      //������� ������ Umin � ���
      target_label->control_zdz &= (unsigned int)(~(
                                                    MASKA_FOR_BIT(CTR_ZDZ_STARTED_FROM_UMIN1_BIT - (_CTR_ZDZ_PART_III - _CTR_ZDZ_PART_II)) | 
                                                    MASKA_FOR_BIT(CTR_ZDZ_STARTED_FROM_UMIN2_BIT - (_CTR_ZDZ_PART_III - _CTR_ZDZ_PART_II))
                                                   ));
      
      //������� ������ Umin � ����
      target_label->control_urov &= (uint64_t)(
                                               ~(
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_UMIN1) | 
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_UMIN2)
                                                )
                                              );
      
      //������� ����� ������� Umin
      for (unsigned int i = 0; i < N_SMALL; i++ ) maska[i] = 0;
      for (int i = 0; i < NUMBER_UMIN_SIGNAL_FOR_RANG_SMALL; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL    + 
                  NUMBER_DZ_SIGNAL_FOR_RANG_SMALL         +
                  NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL         +
                  NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL       +
                  NUMBER_APV_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL +
                  NUMBER_UROV_SIGNAL_FOR_RANG_SMALL       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL        +
                  i
                 )
                );
     
      for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
      for (int i = 0; i < NUMBER_UMIN_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG    + 
                  NUMBER_DZ_SIGNAL_FOR_RANG         +
                  NUMBER_MTZ_SIGNAL_FOR_RANG        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG         +
                  NUMBER_TZNP_SIGNAL_FOR_RANG       +
                  NUMBER_APV_SIGNAL_FOR_RANG        +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG +
                  NUMBER_UROV_SIGNAL_FOR_RANG       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG       +
                  i
                 )
                );

      //������ �� ������� ��� ���������� �����, �� ���������� �� Umin
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
      {
        target_label->ranguvannja_buttons[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_buttons[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_buttons[N_SMALL*i+2] &= ~maska[2];
      }

      //������ �� ������� ��� ���������� �����, �� ���������� �� Umin
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_inputs[N_SMALL*i+2] &= ~maska[2];
      }
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� ����������� � ����������� ����������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }

    //����������, �� Umax ����� ����� � ������������
    if ((target_label->configuration & (1<<UMAX_BIT_CONFIGURATION)) == 0)
    {
      //������� ������ Umax
      target_label->control_Umax &= (unsigned int)(~(CTR_UMAX1 | CTR_UMAX2));

      //������� ������ Umax � ����
      target_label->control_urov &= (uint64_t)(
                                               ~(
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_UMAX1) |
                                                 MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_UMAX2)
                                                )
                                              );
   
      //������� ����� ������� Umax
      for (unsigned int i = 0; i < N_SMALL; i++ ) maska[i] = 0;
      for (int i = 0; i < NUMBER_UMAX_SIGNAL_FOR_RANG_SMALL; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL    + 
                  NUMBER_DZ_SIGNAL_FOR_RANG_SMALL         +
                  NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL         +
                  NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL       +
                  NUMBER_APV_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL +
                  NUMBER_UROV_SIGNAL_FOR_RANG_SMALL       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_UMIN_SIGNAL_FOR_RANG_SMALL       +
                  i
                 )
                );
     
      for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
      for (int i = 0; i < NUMBER_UMAX_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG    + 
                  NUMBER_DZ_SIGNAL_FOR_RANG         +
                  NUMBER_MTZ_SIGNAL_FOR_RANG        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG         +
                  NUMBER_TZNP_SIGNAL_FOR_RANG       +
                  NUMBER_APV_SIGNAL_FOR_RANG        +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG +
                  NUMBER_UROV_SIGNAL_FOR_RANG       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG        +
                  NUMBER_UMIN_SIGNAL_FOR_RANG       +
                  i
                 )
                );


      //������ �� ������� ��� ���������� �����, �� ���������� �� Umax
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
      {
        target_label->ranguvannja_buttons[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_buttons[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_buttons[N_SMALL*i+2] &= ~maska[2];
      }

      //������ �� ������� ��� ���������� �����, �� ���������� �� Umax
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_inputs[N_SMALL*i+2] &= ~maska[2];
      }
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� ����������� � ����������� ����������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }

    //����������, �� ������������ ������ ����� ����� � ������������
    if ((target_label->configuration & (1<<UP_BIT_CONFIGURATION)) == 0)
    {
      for (size_t i = 0; i < NUMBER_UP; i++)
      {
        //������� ������ ��
        target_label->control_UP &= (unsigned int)(~MASKA_FOR_BIT(i*(_CTR_UP_NEXT_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I) - _CTR_UP_PART_I) + CTR_UP_STATE_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I)));

        //������� ������ �� � ����
        target_label->control_urov &= (uint64_t)(~(((uint64_t)(MASKA_FOR_BIT(NUMBER_UP) - 1)) << INDEX_ML_CTRUROV_STARTED_FROM_UP1));
      }
   
      //������� ����� ������� ��
      for (unsigned int i = 0; i < N_SMALL; i++ ) maska[i] = 0;
      for (int i = 0; i < NUMBER_UP_SIGNAL_FOR_RANG_SMALL; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL    + 
                  NUMBER_DZ_SIGNAL_FOR_RANG_SMALL         +
                  NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL         +
                  NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL       +
                  NUMBER_APV_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL +
                  NUMBER_UROV_SIGNAL_FOR_RANG_SMALL       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_UMIN_SIGNAL_FOR_RANG_SMALL       +
                  NUMBER_UMAX_SIGNAL_FOR_RANG_SMALL       +
                  i
                 )
                );
     
      for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
      for (int i = 0; i < NUMBER_UP_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG    + 
                  NUMBER_DZ_SIGNAL_FOR_RANG         +
                  NUMBER_MTZ_SIGNAL_FOR_RANG        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG         +
                  NUMBER_TZNP_SIGNAL_FOR_RANG       +
                  NUMBER_APV_SIGNAL_FOR_RANG        +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG +
                  NUMBER_UROV_SIGNAL_FOR_RANG       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG        +
                  NUMBER_UMIN_SIGNAL_FOR_RANG       +
                  NUMBER_UMAX_SIGNAL_FOR_RANG       +
                  i
                 )
                );


      //������ �� ������� ��� ���������� �����, �� ���������� �� ��
      for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
      {
        target_label->ranguvannja_buttons[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_buttons[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_buttons[N_SMALL*i+2] &= ~maska[2];
      }

      //������ �� ������� ��� ���������� �����, �� ���������� �� ��
      for (int i = 0; i < NUMBER_INPUTS; i++)
      {
        target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
        target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
        target_label->ranguvannja_inputs[N_SMALL*i+2] &= ~maska[2];
      }
      //������ �� ������� ��� ���������� ������
      for (int i = 0; i < NUMBER_OUTPUTS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������
      for (int i = 0; i < NUMBER_LEDS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� ����������� � ����������� ����������
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
        target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
        target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
        target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
      }
      //������ �� ������� ��� ���������� �������������� �������
      for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
          target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
        }
      }
      //������ �� ������� ��� ���������� �������������� ������
      for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) 
        {
          target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
          target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
          target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
        }
      }
  
      //������ �� ������� ��� ���������� ������������ "�"
      for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "����.���"
      for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
      }
  
      //������ �� ������� ��� ���������� ������������ "��"
      for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
      {
        for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
      }
    }

    //����������, �� "���������� ���� �����������" ����� ����� � ������������
    if ((target_label->configuration & (1<<VMP_BIT_CONFIGURATION)) == 0)
    {
      //������� ���
      target_label->control_vmp &= (unsigned int)(~CTR_VMP_STATE);
    }

    //"��������� �����"
    for (unsigned int i = 0; i < N_SMALL; i++ ) maska[i] = 0;
    unsigned int array_full[N_BIG] = {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff};
    unsigned int *point_to_mask_array;
    for (unsigned int i = 0; i < N_BIG; i++ ) maska_1[i] = 0;
    if ((target_label->configuration & (1<<EL_BIT_CONFIGURATION)) == 0)
    {
      //��������� �� ������� ��������� �����
      
      //������� ����� ������� ��������� �����
      for (int i = 0; i < NUMBER_EL_SIGNAL_FOR_RANG_SMALL; i++)
        _SET_BIT(
                 maska, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL    + 
                  NUMBER_DZ_SIGNAL_FOR_RANG_SMALL         +
                  NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL         +
                  NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL       +
                  NUMBER_APV_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL +
                  NUMBER_UROV_SIGNAL_FOR_RANG_SMALL       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL        +
                  NUMBER_UMIN_SIGNAL_FOR_RANG_SMALL       +
                  NUMBER_UMAX_SIGNAL_FOR_RANG_SMALL       +
                  NUMBER_UP_SIGNAL_FOR_RANG_SMALL         +
                  NUMBER_VMP_SIGNAL_FOR_RANG_SMALL        +
                  i
                 )
                );
     
      for (int i = 0; i < NUMBER_EL_SIGNAL_FOR_RANG; i++)
        _SET_BIT(
                 maska_1, 
                 (
                  NUMBER_GENERAL_SIGNAL_FOR_RANG    + 
                  NUMBER_DZ_SIGNAL_FOR_RANG         +
                  NUMBER_MTZ_SIGNAL_FOR_RANG        +
                  NUMBER_ZDZ_SIGNAL_FOR_RANG        +
                  NUMBER_ZZ_SIGNAL_FOR_RANG         +
                  NUMBER_TZNP_SIGNAL_FOR_RANG       +
                  NUMBER_APV_SIGNAL_FOR_RANG        +
                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG +
                  NUMBER_UROV_SIGNAL_FOR_RANG       +
                  NUMBER_ZOP_SIGNAL_FOR_RANG        +
                  NUMBER_UMIN_SIGNAL_FOR_RANG       +
                  NUMBER_UMAX_SIGNAL_FOR_RANG       +
                  NUMBER_UP_SIGNAL_FOR_RANG         +
                  NUMBER_VMP_SIGNAL_FOR_RANG        +
                  i
                 )
                );

      point_to_mask_array = array_full;
      
      for (size_t i = 0; i < NUMBER_TRANSFER_FUNCTIONS; i++) target_label->ranguvannja_tf[i] = 0;
    }
    else
    {
//      //������� ����� ����� ��� ������� ��������� �����, �� ������� � ������������ � ��������� �������
//      unsigned int array_defined_logic[NUMBER_DEFINED_ELEMENTS][2] =
//      {
//        {target_label->number_defined_df , NUMBER_DEFINED_FUNCTIONS},
//        {target_label->number_defined_dt , NUMBER_DEFINED_TRIGGERS },
//        {target_label->number_defined_and, NUMBER_DEFINED_AND      },
//        {target_label->number_defined_or , NUMBER_DEFINED_OR       },
//        {target_label->number_defined_xor, NUMBER_DEFINED_XOR      },
//        {target_label->number_defined_not, NUMBER_DEFINED_NOT      }
//      };
//      const unsigned int input_signals[NUMBER_DEFINED_ELEMENTS]  = {1, 2, 0, 0, 0, 0};
//      const unsigned int others_signals[NUMBER_DEFINED_ELEMENTS] = {2, 3, 1, 1, 1, 1};
//      const unsigned int button_signals[NUMBER_DEFINED_ELEMENTS] = {1, 2, 0, 0, 0, 0};
//      
//      unsigned int input_shift = NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL    + 
//                                 NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL        +
//                                 NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL      +
//                                 NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL        +
//                                 NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL         +
//                                 NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL       +
//                                 NUMBER_APV_SIGNAL_FOR_RANG_SMALL        +
//                                 NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL +
//                                 NUMBER_UROV_SIGNAL_FOR_RANG_SMALL       +
//                                 NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL        +
//                                 NUMBER_UMIN_SIGNAL_FOR_RANG_SMALL       +
//                                 NUMBER_UMAX_SIGNAL_FOR_RANG_SMALL       +
//                                 NUMBER_UP_SIGNAL_FOR_RANG_SMALL         +
//                                 NUMBER_VMP_SIGNAL_FOR_RANG_SMALL;
//      
//      unsigned int others_shift = NUMBER_GENERAL_SIGNAL_FOR_RANG    + 
//                                  NUMBER_MTZ_SIGNAL_FOR_RANG        +
//                                  NUMBER_MTZ04_SIGNAL_FOR_RANG      +
//                                  NUMBER_ZDZ_SIGNAL_FOR_RANG        +
//                                  NUMBER_ZZ_SIGNAL_FOR_RANG         +
//                                  NUMBER_TZNP_SIGNAL_FOR_RANG       +
//                                  NUMBER_APV_SIGNAL_FOR_RANG        +
//                                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG +
//                                  NUMBER_UROV_SIGNAL_FOR_RANG       +
//                                  NUMBER_ZOP_SIGNAL_FOR_RANG        +
//                                  NUMBER_UMIN_SIGNAL_FOR_RANG       +
//                                  NUMBER_UMAX_SIGNAL_FOR_RANG       +
//                                  NUMBER_UP_SIGNAL_FOR_RANG         +
//                                  NUMBER_VMP_SIGNAL_FOR_RANG;
//      
//      unsigned int button_shift = NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON    + 
//                                  NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON        +
//                                  NUMBER_MTZ04_SIGNAL_FOR_RANG_BUTTON      +
//                                  NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON        +
//                                  NUMBER_ZZ_SIGNAL_FOR_RANG_BUTTON         +
//                                  NUMBER_TZNP_SIGNAL_FOR_RANG_BUTTON       +
//                                  NUMBER_APV_SIGNAL_FOR_RANG_BUTTON        +
//                                  NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_BUTTON +
//                                  NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON       +
//                                  NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON        +
//                                  NUMBER_UMIN_SIGNAL_FOR_RANG_BUTTON       +
//                                  NUMBER_UMAX_SIGNAL_FOR_RANG_BUTTON       +
//                                  NUMBER_UP_SIGNAL_FOR_RANG_BUTTON         +
//                                  NUMBER_VMP_SIGNAL_FOR_RANG_BUTTON;
//      
//      for (unsigned int index = 0; index < NUMBER_DEFINED_ELEMENTS; index++)
//      {
//        //������� ����� ������� ��������� �����
//        for (unsigned int i = 0; i < input_signals[index]*(array_defined_logic[index][1] - array_defined_logic[index][0]); i++)
//          _SET_BIT(maska, (input_shift + input_signals[index]*array_defined_logic[index][0] + i));
//        
//        input_shift += input_signals[index]*array_defined_logic[index][1];
//     
//        for (unsigned int i = 0; i < others_signals[index]*(array_defined_logic[index][1] - array_defined_logic[index][0]); i++)
//          _SET_BIT(maska_1, (others_shift + others_signals[index]*array_defined_logic[index][0] + i));
//        
//        others_shift += others_signals[index]*array_defined_logic[index][1];
//      }
      
      point_to_mask_array = maska_1;

      for (size_t i = 0; i < TOTAL_NUMBER_PROTECTION; i++)
      {
         if ((target_label->configuration & (1 << i)) == 0)
         {
           for (size_t j = 0; j < NUMBER_TRANSFER_FUNCTIONS; j++)
           {
             uint32_t value = target_label->ranguvannja_tf[j];
             uint32_t value_1 = (value >> (16*0)) & 0xffff;
             if (
                 (value_1 >= max_value_for_tf[1 + i - 1][0]) &&
                 (value_1 <= max_value_for_tf[1 + i    ][0])
                ) 
             {
               value_1 = 0;
             }
         
             uint32_t value_2 = (value >> (16*1)) & 0xffff;
             if (
                 (value_2 >= max_value_for_tf[1 + i - 1][1]) &&
                 (value_2 <= max_value_for_tf[1 + i    ][1])
                ) 
             {
               value_2 = 0;
             }

             target_label->ranguvannja_tf[j] = (value_2 << (16*1)) | (value_1 << (16*0));
           }
         }
      }
    }

    //������ �� ������� ��� ���������� �����, �� ���������� �� ��������� �����
    for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
    {
      target_label->ranguvannja_buttons[N_SMALL*i  ] &= ~maska[0];
      target_label->ranguvannja_buttons[N_SMALL*i+1] &= ~maska[1];
      target_label->ranguvannja_buttons[N_SMALL*i+2] &= ~maska[2];
    }
    
    //������ �� ������� ��� ���������� �����, �� ���������� �� ��������� �����
    for (int i = 0; i < NUMBER_INPUTS; i++)
    {
      target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
      target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
      target_label->ranguvannja_inputs[N_SMALL*i+2] &= ~maska[2];
    }
    //������ �� ������� ��� ���������� ������
    for (int i = 0; i < NUMBER_OUTPUTS; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
    }
    //������ �� ������� ��� ���������� �������������
    for (int i = 0; i < NUMBER_LEDS; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
    }
    //������ �� ������� ��� ���������� ����������� � ����������� ����������
    for (unsigned int j = 0; j < N_BIG; j++ ) 
    {
      target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
      target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
      target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
      target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
    }
    //������� �� ������� ��� ���������� �������������� �������
    for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~point_to_mask_array[j];
        target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~point_to_mask_array[j];
        target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~point_to_mask_array[j];
      }
    }
    //������� �� ������� ��� ���������� �������������� ������
    for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~point_to_mask_array[j];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~point_to_mask_array[j];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~point_to_mask_array[j];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~point_to_mask_array[j];
      }
    }
  
    //������� �� ������� ��� ���������� ������������ "�"
    for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~point_to_mask_array[j];
    }
  
    //������� �� ������� ��� ���������� ������������ "���"
    for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~point_to_mask_array[j];
    }
  
    //������� �� ������� ��� ���������� ������������ "����.���"
    for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~point_to_mask_array[j];
    }
  
    //������� �� ������� ��� ���������� ������������ "��"
    for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~point_to_mask_array[j];
    }
  }
  
  return error_window;
}
/*****************************************************/

/*****************************************************/
//������� ���������� ������ ��� ��� ���� ���� 33/3I0
/*****************************************************/
void action_after_changing_zz1_type(__SETTINGS *target_label)
{
  if ((target_label->control_zz & CTR_ZZ1_TYPE) != 0)
  {
    //������� ��� � ������ ���
    target_label->control_zz &= (unsigned int)(~(CTR_ZZ1_NZZ_STATE/* | CTR_ZZ1_SECTOR*/));
    
    //������� ��� � ����
    target_label->control_urov &= (uint64_t)(~MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_NZZ));
      
    unsigned int /*maska[N_SMALL] = {0,0,0}, */maska_1[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    _SET_BIT(maska_1, RANG_PO_NZZ);
    _SET_BIT(maska_1, RANG_NZZ);
    _SET_BIT(maska_1, RANG_SECTOR_NZZ);
    
//    //������ �� ������� ��� ���������� �����, �� ���������� �� �������� ������ 3U0
//    for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
//    {
//      target_label->ranguvannja_buttons[N_SMALL*i  ] &= ~maska[0];
//      target_label->ranguvannja_buttons[N_SMALL*i+1] &= ~maska[1];
//      target_label->ranguvannja_buttons[N_SMALL*i+2] &= ~maska[2];
//    }
    //������ �� ������� ��� ���������� �����, �� ���������� �� �������� ������ 3U0
//    for (int i = 0; i < NUMBER_INPUTS; i++)
//    {
//      target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
//      target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
//      target_label->ranguvannja_inputs[N_SMALL*i+2] &= ~maska[2];
//    }
    //������ �� ������� ��� ���������� ������
    for (int i = 0; i < NUMBER_OUTPUTS; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
    }
    //������ �� ������� ��� ���������� �������������
    for (int i = 0; i < NUMBER_LEDS; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
    }
    //������ �� ������� ��� ���������� ����������� � ����������� ����������
    for (unsigned int j = 0; j < N_BIG; j++ ) 
    {
      target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
      target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
      target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
      target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
    }
    //������ �� ������� ��� ���������� �������������� �������
    for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
        target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
        target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
      }
    }
    //������ �� ������� ��� ���������� �������������� ������
    for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) 
      {
        target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
        target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
        target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
        target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
      }
    }
  
    //������ �� ������� ��� ���������� ������������ "�"
    for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
    }
  
    //������ �� ������� ��� ���������� ������������ "���"
    for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
    }
  
    //������ �� ������� ��� ���������� ������������ "����.���"
    for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
    }
  
    //������ �� ������� ��� ���������� ������������ "��"
    for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
    {
      for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
    }

    for (size_t i = 0; i < NUMBER_TRANSFER_FUNCTIONS; i++)
    {
      uint32_t value = (target_label->ranguvannja_tf[i] >> (16*0)) & 0xffff;
      if (
          (value == (RANG_PO_NZZ     + 1)) ||
          (value == (RANG_NZZ        + 1)) ||
          (value == (RANG_SECTOR_NZZ + 1))
         ) 
      {
        target_label->ranguvannja_tf[i] &= (uint32_t)(~(0xffff << (16*0)));
      }
    }
  }

}
/*****************************************************/

/*****************************************************
������� ���������� ������ ��� ��� ������ ��
*****************************************************/
void action_during_changing_button_mode(__SETTINGS *current_label, __SETTINGS *edit_label)
{
  //���������� �� ��
  for (size_t number = 0; number < NUMBER_DEFINED_BUTTONS; number++)
  {
    uint32_t mode_current = (current_label->buttons_mode >> number) & 0x1;
    uint32_t mode_edit    = (edit_label->buttons_mode    >> number) & 0x1;
    
    //ĳ� �������� ����� ��� ���� ��������, � ���� ����� �������
    if (mode_current != mode_edit)
    {
      unsigned int state_button[N_SMALL];
      for (unsigned int i = 0; i < N_SMALL; i++)
      {
        state_button[i] = current_label->ranguvannja_buttons[N_SMALL*number + i];
      }
  
      for (unsigned int index_deleted_function = 0; index_deleted_function < NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL; index_deleted_function++)
      {
        if (_CHECK_SET_BIT(buttons_mode[mode_edit], index_deleted_function) == 0)
        {
          /*************************************************************/
          //³������������ ���� �������
          /*************************************************************/
          _CLEAR_BIT(state_button, index_deleted_function);
        }
      }
    
      //������� ���� � ���������� �� ���������� ����������
      for (unsigned int i = 0; i < N_SMALL; i++)
      {
        current_label->ranguvannja_buttons[N_SMALL*number + i] = state_button[i];
      }
    }
  }
  
  //���������� ��� ������ ��� ��� ������
  current_label->buttons_mode = edit_label->buttons_mode;
}
/*****************************************************/

/*****************************************************
������� ������������ ��������/�������� �� � �������� "��������"
*****************************************************/
void def_pickup_timeout_UP(__SETTINGS *current_label, uint32_t _n_UP, uint32_t group)
{
  uint32_t min;
  switch (current_label->ctrl_UP_input[_n_UP])
  {
  case UP_CTRL_Ia_Ib_Ic:
  case UP_CTRL_Ia:
  case UP_CTRL_Ib:
  case UP_CTRL_Ic:
  case UP_CTRL_I1:
  case UP_CTRL_I2:
  case UP_CTRL_3I0_r:
    {
      min = SETPOINT_UP_I_MIN;
      break;
    }
  case UP_CTRL_3I0:
  case UP_CTRL_3I0_others:
    {
      min = SETPOINT_UP_3I0_MIN;
      break;
    }
  case UP_CTRL_Ua_Ub_Uc:
  case UP_CTRL_Uab_Ubc_Uca:
  case UP_CTRL_Ua:
  case UP_CTRL_Uab:
  case UP_CTRL_Ub:
  case UP_CTRL_Ubc:
  case UP_CTRL_Uc:
  case UP_CTRL_Uca:
  case UP_CTRL_U1:
  case UP_CTRL_U2:
  case UP_CTRL_3U0:
    {
      min = SETPOINT_UP_U_MIN;
      break;
    }
  case UP_CTRL_P:
  case UP_CTRL_Q:
  case UP_CTRL_S:
    {
      min = SETPOINT_UP_P_MIN;
      break;
    }
  default:
    {
      //���������� ����� ����� �� ���� � ����
      total_error_sw_fixed(99);
    }
  }
  
  current_label->setpoint_UP[_n_UP][0][group] = min;
  current_label->setpoint_UP_KP[_n_UP][0][group] = ((current_label->control_UP & MASKA_FOR_BIT(_n_UP*(_CTR_UP_NEXT_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I) - _CTR_UP_PART_I) + CTR_UP_MORE_LESS_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I))) != 0) ? SETPOINT_UP_KP_LESS_MIN : SETPOINT_UP_KP_MORE_MAX;
  current_label->timeout_UP[_n_UP][0][group] = TIMEOUT_UP_MIN;
}
/*****************************************************/

/*****************************************************
������� ���������� ������ ��� ��� ����������� ����� ��
*****************************************************/
void action_after_changing_input_UP(__SETTINGS *current_label, uint32_t index, uint32_t value)
{
  if (current_label->ctrl_UP_input[index] != value)
  {
    current_label->ctrl_UP_input[index] = value;
    uint32_t ctrl_maska = MASKA_FOR_BIT(index*(_CTR_UP_NEXT_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I) - _CTR_UP_PART_I) + CTR_UP_STATE_BIT     - (_CTR_UP_PART_II - _CTR_UP_PART_I)) |
                          MASKA_FOR_BIT(index*(_CTR_UP_NEXT_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I) - _CTR_UP_PART_I) + CTR_UP_OR_AND_BIT    - (_CTR_UP_PART_II - _CTR_UP_PART_I)) |
                          MASKA_FOR_BIT(index*(_CTR_UP_NEXT_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I) - _CTR_UP_PART_I) + CTR_UP_MORE_LESS_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I));  
    current_label->control_UP &= (uint32_t)(~ctrl_maska);
    
    for (size_t group = 0; group < NUMBER_GROUP_USTAVOK; group++) def_pickup_timeout_UP(current_label, index, group);
  }
}
/*****************************************************/

/*****************************************************
������� ���������� ����������� ���������� ���� ���� ����������� ��
*****************************************************/
void action_after_changing_ctrl_UP(__SETTINGS *current_label, uint32_t value)
{
  if (current_label->control_UP != value)
  {
    //³��������� ���� �����������
    for (size_t index = 0; index < NUMBER_UP; index++)
    {
      uint32_t maska = MASKA_FOR_BIT(index*(_CTR_UP_NEXT_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I) - _CTR_UP_PART_I) + CTR_UP_MORE_LESS_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I));
      if (((current_label->control_UP ^ value) & maska) != 0)
      {
        //³������� ���� ">" �� "<", ��� "<" �� ">"
        uint32_t min, max;
        if ((value & maska) != 0)
        {
          min = SETPOINT_UP_KP_LESS_MIN;
          max = SETPOINT_UP_KP_LESS_MAX;
        }
        else
        {
          min = SETPOINT_UP_KP_MORE_MIN;
          max = SETPOINT_UP_KP_MORE_MAX;
        }
      
        for (size_t group = 0; group < NUMBER_GROUP_USTAVOK; group++)
        {
          current_label->setpoint_UP_KP[index][0][group] = ((value & maska) != 0) ? min : max;
        }
      }
    }
    
    current_label->control_UP = value;
  }
}
/*****************************************************/

///*****************************************************/
////������� ���������� ������ ��� ��� ������� �������� ��������� �����
///*****************************************************/
//void action_after_changing_number_el(__SETTINGS *target_label, unsigned int element)
//{
//  unsigned int maska[N_SMALL] = {0, 0, 0}, maska_1[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, maska_2 = 0;
//
//  //������� ����� ����� ��� ������� ��������� �����, �� ������� � ������������ � ��������� �������
//  unsigned int array_defined_logic[NUMBER_DEFINED_ELEMENTS][2] =
//  {
//    {target_label->number_defined_df , NUMBER_DEFINED_FUNCTIONS},
//    {target_label->number_defined_dt , NUMBER_DEFINED_TRIGGERS },
//    {target_label->number_defined_and, NUMBER_DEFINED_AND      },
//    {target_label->number_defined_or , NUMBER_DEFINED_OR       },
//    {target_label->number_defined_xor, NUMBER_DEFINED_XOR      },
//    {target_label->number_defined_not, NUMBER_DEFINED_NOT      }
//  };
//  const unsigned int input_signals[NUMBER_DEFINED_ELEMENTS]  = {1, 2, 0, 0, 0, 0};
//  const unsigned int others_signals[NUMBER_DEFINED_ELEMENTS] = {2, 3, 1, 1, 1, 1};
//  const unsigned int button_signals[NUMBER_DEFINED_ELEMENTS] = {1, 2, 0, 0, 0, 0};
//  
//  unsigned int input_shift = NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL    + 
//                             NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL        +
//                             NUMBER_MTZ04_SIGNAL_FOR_RANG_SMALL      +
//                             NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL        +
//                             NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL         +
//                             NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL       +
//                             NUMBER_APV_SIGNAL_FOR_RANG_SMALL        +
//                             NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL +
//                             NUMBER_UROV_SIGNAL_FOR_RANG_SMALL       +
//                             NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL        +
//                             NUMBER_UMIN_SIGNAL_FOR_RANG_SMALL       +
//                             NUMBER_UMAX_SIGNAL_FOR_RANG_SMALL       +
//                             NUMBER_UP_SIGNAL_FOR_RANG_SMALL         +
//                             NUMBER_VMP_SIGNAL_FOR_RANG_SMALL;
//      
//  unsigned int others_shift = NUMBER_GENERAL_SIGNAL_FOR_RANG    + 
//                              NUMBER_MTZ_SIGNAL_FOR_RANG        +
//                              NUMBER_MTZ04_SIGNAL_FOR_RANG      +
//                              NUMBER_ZDZ_SIGNAL_FOR_RANG        +
//                              NUMBER_ZZ_SIGNAL_FOR_RANG         +
//                              NUMBER_TZNP_SIGNAL_FOR_RANG       +
//                              NUMBER_APV_SIGNAL_FOR_RANG        +
//                              NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG +
//                              NUMBER_UROV_SIGNAL_FOR_RANG       +
//                              NUMBER_ZOP_SIGNAL_FOR_RANG        +
//                              NUMBER_UMIN_SIGNAL_FOR_RANG       +
//                              NUMBER_UMAX_SIGNAL_FOR_RANG       +
//                              NUMBER_UP_SIGNAL_FOR_RANG         +
//                              NUMBER_VMP_SIGNAL_FOR_RANG;
//      
//  unsigned int button_shift = NUMBER_GENERAL_SIGNAL_FOR_RANG_BUTTON    + 
//                              NUMBER_MTZ_SIGNAL_FOR_RANG_BUTTON        +
//                              NUMBER_MTZ04_SIGNAL_FOR_RANG_BUTTON      +
//                              NUMBER_ZDZ_SIGNAL_FOR_RANG_BUTTON        +
//                              NUMBER_ZZ_SIGNAL_FOR_RANG_BUTTON         +
//                              NUMBER_TZNP_SIGNAL_FOR_RANG_BUTTON       +
//                              NUMBER_APV_SIGNAL_FOR_RANG_BUTTON        +
//                              NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_BUTTON +
//                              NUMBER_UROV_SIGNAL_FOR_RANG_BUTTON       +
//                              NUMBER_ZOP_SIGNAL_FOR_RANG_BUTTON        +
//                              NUMBER_UMIN_SIGNAL_FOR_RANG_BUTTON       +
//                              NUMBER_UMAX_SIGNAL_FOR_RANG_BUTTON       +
//                              NUMBER_UP_SIGNAL_FOR_RANG_BUTTON         +
//                              NUMBER_VMP_SIGNAL_FOR_RANG_BUTTON;
//      
//  for (unsigned int index = 0; index < element; index++)
//  {
//    input_shift  += input_signals[index]*array_defined_logic[index][1];
//    others_shift += others_signals[index]*array_defined_logic[index][1];
//    button_shift += button_signals[index]*array_defined_logic[index][1];
//  }
//  
//  //������� ����� ������� �������� ��������� �����
//  for (unsigned int i = 0; i < input_signals[element]*(array_defined_logic[element][1] - array_defined_logic[element][0]); i++)
//    _SET_BIT(maska, (input_shift + input_signals[element]*array_defined_logic[element][0] + i));
//    
//  for (unsigned int i = 0; i < others_signals[element]*(array_defined_logic[element][1] - array_defined_logic[element][0]); i++)
//    _SET_BIT(maska_1, (others_shift + others_signals[element]*array_defined_logic[element][0] + i));
//    
//  for (unsigned int i = 0; i < button_signals[element]*(array_defined_logic[element][1] - array_defined_logic[element][0]); i++)
//    maska_2 |= 1 << (button_shift + button_signals[element]*array_defined_logic[element][0] + i);
//    
//  //������ �� ������� ��� ���������� �����, �� ���������� �� ��������� �����
//  for (int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
//  {
//    target_label->ranguvannja_buttons[N_SMALL*i  ] &= ~maska[0];
//    target_label->ranguvannja_buttons[N_SMALL*i+1] &= ~maska[1];
//    target_label->ranguvannja_buttons[N_SMALL*i+2] &= ~maska[2];
//  }
//  //������ �� ������� ��� ���������� �����, �� ���������� �� ��������� �����
//  for (int i = 0; i < NUMBER_INPUTS; i++)
//  {
//    target_label->ranguvannja_inputs[N_SMALL*i  ] &= ~maska[0];
//    target_label->ranguvannja_inputs[N_SMALL*i+1] &= ~maska[1];
//    target_label->ranguvannja_inputs[N_SMALL*i+2] &= ~maska[2];
//  }
//  //������ �� ������� ��� ���������� ������
//  for (int i = 0; i < NUMBER_OUTPUTS; i++)
//  {
//    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] &= ~maska_1[j];
//  }
//  //������ �� ������� ��� ���������� �������������
//  for (int i = 0; i < NUMBER_LEDS; i++)
//  {
//    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] &= ~maska_1[j];
//  }
//  //������ �� ������� ��� ���������� ����������� � ����������� ����������
//  for (unsigned int j = 0; j < N_BIG; j++ ) 
//  {
//    target_label->ranguvannja_analog_registrator[j]  &= ~maska_1[j];
//    target_label->ranguvannja_digital_registrator[j] &= ~maska_1[j];
//    target_label->ranguvannja_off_cb[j] &= ~maska_1[j];
//    target_label->ranguvannja_on_cb[j]  &= ~maska_1[j];
//  }
//  //������� �� ������� ��� ���������� �������������� �������
//  for (int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
//  {
//    for (unsigned int j = 0; j < N_BIG; j++ ) 
//    {
//      target_label->ranguvannja_df_source_plus[N_BIG*i+j]  &= ~maska_1[j];
//      target_label->ranguvannja_df_source_minus[N_BIG*i+j] &= ~maska_1[j];
//      target_label->ranguvannja_df_source_blk[N_BIG*i+j]   &= ~maska_1[j];
//    }
//  }
//  //������� �� ������� ��� ���������� �������������� ������
//  for (int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
//  {
//    for (unsigned int j = 0; j < N_BIG; j++ ) 
//    {
//      target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    &= ~maska_1[j];
//      target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   &= ~maska_1[j];
//      target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  &= ~maska_1[j];
//      target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] &= ~maska_1[j];
//    }
//  }
//  
//  //������� �� ������� ��� ���������� ������������ "�"
//  for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
//  {
//    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] &= ~maska_1[j];
//  }
//  
//  //������� �� ������� ��� ���������� ������������ "���"
//  for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
//  {
//    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] &= ~maska_1[j];
//  }
//  
//  //������� �� ������� ��� ���������� ������������ "����.���"
//  for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
//  {
//    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] &= ~maska_1[j];
//  }
//  
//  //������� �� ������� ��� ���������� ������������ "��"
//  for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
//  {
//    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] &= ~maska_1[j];
//  }
//}
///*****************************************************/

/*****************************************************/
//�������, ��� ������� ������� �� ��������, ���� ����������� �� ������� � RS-485 ����� � ����������� �����������
/*****************************************************/
void calculate_namber_bit_waiting_for_rs_485(void)
{
  unsigned int number_bits_rs_485_waiting_tmp = 10;
  
  //ϳ��������� ������� �� � ����
  if (current_settings.pare_bit_RS485 > 0) number_bits_rs_485_waiting_tmp++;
  if (current_settings.number_stop_bit_RS485 > 0) number_bits_rs_485_waiting_tmp++;
  
  //���������� ��������
  unsigned int multiplicator;
  switch (current_settings.speed_RS485)
  {
  case 0:
    {
      multiplicator = 12; //9600
      break;
    }
  case 1:
    {
      multiplicator = 8;  //14400
      break;
    }
  case 2:
    {
      multiplicator = 6;  //19200
      break;
    }
  case 3:
    {
      multiplicator = 4;  //28800
      break;
    }
  case 4:
    {
      multiplicator = 3;  //38400
      break;
    }
  case 5:
    {
      multiplicator = 2;  //57600
      break;
    }
  default:
    {
      multiplicator = 1;  //115200
      break;
    }
  }
  number_bits_rs_485_waiting_tmp *= (multiplicator*current_settings.time_out_1_RS485);
  number_bits_rs_485_waiting_tmp /= 10;
  
  number_bits_rs_485_waiting = number_bits_rs_485_waiting_tmp;
}
/*****************************************************/

/******************************************************
//�������, ��� ����� ���� � ���������� � ������� ����� ��������� � EEPROM
-----------------------------------------------------
setting_rang: 0 - ����� �������
              1 - ����� ����������
              2 - ���������� ��� ��������

source:       0 - ������� ���������
              1 - ���������
              2 - USB
              3 - RS-485
---------------------------------------------------
******************************************************/
void fix_change_settings(unsigned int setting_rang, unsigned int source)
{
  if (setting_rang < 2)
  {
    unsigned char *point_to_target;
  
    if (setting_rang == 0) point_to_target = (&current_settings)->time_setpoints;
    else point_to_target = (&current_settings)->time_ranguvannja;
    
    //�������� ��� ������� ���
    unsigned char *label_to_time_array;
    if (copying_time == 2) label_to_time_array = time_copy;
    else label_to_time_array = time;
    for (unsigned int i = 0; i < 7; i++) *(point_to_target + i) = *(label_to_time_array + i);
    *(point_to_target + 7) = (unsigned char)(source & 0xff);
  }
  
  //��������� ����� � EEPROM
  _SET_BIT(control_spi1_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT);
  
  //�������, �� ������� �������� � �� ����� ���� � ������� ������� ��������� � ������� � ���� ������ ������� �������
  changed_settings = CHANGED_ETAP_ENDED;
  if (_CHECK_SET_BIT(active_functions, RANG_SETTINGS_CHANGED) == 0) current_settings_interfaces = current_settings;
}
/*****************************************************/

/*****************************************************/
/*
��������� �������� ��� � ������������ ����� ����������
*/
/*****************************************************/
unsigned int set_new_settings_from_interface(unsigned int source)
{
  unsigned int error = 0;
  
  //�������� �� ��������� ���
  unsigned char *label_to_time_array;
  if (copying_time == 2) label_to_time_array = time_copy;
  else label_to_time_array = time;
  
  if ((type_of_settings_changed & (1 << DEFAULT_SETTINGS_SET_BIT)) != 0)
  {
    for (unsigned int i = 0; i < 7; i++) current_settings_interfaces.time_setpoints[i] = current_settings_interfaces.time_ranguvannja[i] = *(label_to_time_array + i);
    current_settings_interfaces.time_setpoints[7] = current_settings_interfaces.time_ranguvannja[7] = 0;
  }
  
  if ((type_of_settings_changed & (1 << SETTINGS_DATA_CHANGED_BIT)) != 0)
  {
    for (unsigned int i = 0; i < 7; i++) current_settings_interfaces.time_setpoints[i] = *(label_to_time_array + i);
    current_settings_interfaces.time_setpoints[7] = source;
  }
  
  if ((type_of_settings_changed & (1 << RANGUVANNJA_DATA_CHANGED_BIT)) != 0)
  {
    for (unsigned int i = 0; i < 7; i++) current_settings_interfaces.time_ranguvannja[i] = *(label_to_time_array + i);
    current_settings_interfaces.time_ranguvannja[7] = source;
  }
  
  unsigned int reconfiguration_RS_485 = 0, reconfiguration_RS_485_with_reset_usart = 0;
  if (
      (current_settings.speed_RS485 != current_settings_interfaces.speed_RS485) ||
      (current_settings.pare_bit_RS485 != current_settings_interfaces.pare_bit_RS485) ||
      (current_settings.number_stop_bit_RS485 != current_settings_interfaces.number_stop_bit_RS485) ||
      (current_settings.time_out_1_RS485 != current_settings_interfaces.time_out_1_RS485)
     )
  {
    //�������, �� ����� ����������������� ��������� RS-485
    reconfiguration_RS_485 = 1;
    
    if (
        (current_settings.speed_RS485 != current_settings_interfaces.speed_RS485) ||
        (current_settings.pare_bit_RS485 != current_settings_interfaces.pare_bit_RS485) ||
        (current_settings.number_stop_bit_RS485 != current_settings_interfaces.number_stop_bit_RS485)
       )
    {
      //�������, �� ����� ����������������� USART ��� ���������� RS-485
      reconfiguration_RS_485_with_reset_usart = 1;
    }
  }
  
  unsigned int set_password_USB = false;
  if (
      (current_settings.password_interface_USB != current_settings_interfaces.password_interface_USB) &&
      (current_settings_interfaces.password_interface_USB != 0)  
     )   
  {
    set_password_USB = true;
  }
  
  unsigned int set_password_RS485 = false;
  if (
      (current_settings.password_interface_RS485 != current_settings_interfaces.password_interface_RS485) &&
      (current_settings_interfaces.password_interface_RS485 != 0)  
     )   
  {
    set_password_RS485 = true;
  }
  
  if (error == 0)
  {
    if ((type_of_settings_changed & (1 << DEFAULT_SETTINGS_SET_BIT)) != 0)
    {
      //���������� ���� � ��������� ����
      for(unsigned int i=0; i<MAX_LEVEL_MENU; i++)
      {
        if ((i == EKRAN_LEVEL_PASSWORD) || (i == EKRAN_LEVEL_SET_NEW_PASSWORD1) || (i == EKRAN_LEVEL_SET_NEW_PASSWORD2)) position_in_current_level_menu[i] = INDEX_LINE_NUMBER_1_FOR_LEVEL_PASSWORD;
        else  position_in_current_level_menu[i] = 0;
        previous_level_in_current_level_menu[i] = -1;
      }
  
      //���������� ����������� ����� ������
      current_ekran.current_level = EKRAN_MAIN;
      current_ekran.index_position = position_in_current_level_menu[current_ekran.current_level];
      current_ekran.position_cursor_y = current_ekran.index_position;
      current_ekran.edition = 0;
      current_ekran.cursor_on = 0;
      current_ekran.cursor_blinking_on = 0;  
    }
    
    if (set_password_USB   != false) password_set_USB   = 1;
    if (set_password_RS485 != false) password_set_RS485 = 1;
    
    //�������, �� ���� ��������� ����� ������ �����
    changed_settings = CHANGED_ETAP_EXECUTION;
              
    //������� ������ ���� � ������ ���������
    current_settings = current_settings_interfaces;
    if (reconfiguration_RS_485 != 0)
    {
      //ϳ��������� ���� �������� �������� � ����, ��� ����������� �� ������� � RS-485 ����� � ����������� �����������
      calculate_namber_bit_waiting_for_rs_485();
      //����������� ������� ��� ������������������ RS-485
      if (reconfiguration_RS_485_with_reset_usart != 0) make_reconfiguration_RS_485 = 0xff;
    }

    fix_change_settings(2, source);

    //����������� �������, �� �� ����� ����� �������� ����������
    new_state_keyboard |= (1<<BIT_REWRITE);
  }
  
  return error;
}
/*****************************************************/

/******************************************************
³��������� �������� �������
******************************************************/
void restore_trigger_functions(unsigned int *active_functions_point)
{
  active_functions[RANG_DT1_OUT >> 5] |= _CHECK_SET_BIT(active_functions_point, RANG_DT1_OUT);
  active_functions[RANG_DT2_OUT >> 5] |= _CHECK_SET_BIT(active_functions_point, RANG_DT2_OUT);
  active_functions[RANG_DT3_OUT >> 5] |= _CHECK_SET_BIT(active_functions_point, RANG_DT3_OUT);
  active_functions[RANG_DT4_OUT >> 5] |= _CHECK_SET_BIT(active_functions_point, RANG_DT4_OUT);
}
/*****************************************************/

/*****************************************************/
//������� ���� ���������� �� ����������
/*****************************************************/
void changing_diagnostyka_state(void)
{
  /*****
  ��������� ����� ���� ����������
  
  ��������:
  - ������� � �������� ������ ���, �� ����� ������� � �� ����� ��������� � 
    ����������
  - ϳ��� ����� ��������� ���� ��������� �������� ������ ��������� (�� 
    �������� �����!!!) ��� ��� � �������� ������
  - ���� , �� �� ������ ���������/��������������� ������� � ���������� ������
    (���� � ������ ����� ��������� ������������� ������� �������� �� 
    ������������� ��� ���, �� ���� �� ���������, � ����������� ��� ���������� 
    ������� ���� �������)

  - �������� ������� ��� � ���� ������������, �� �������� ��䳿 �� ������ 
    �������� �� ��������
  *****/
  unsigned int clear_diagnostyka_tmp[N_DIAGN], set_diagnostyka_tmp[N_DIAGN];
  
  for (size_t i = 0; i < N_DIAGN; i++)
  {
    clear_diagnostyka_tmp[i] = clear_diagnostyka[i];
    set_diagnostyka_tmp[i] = set_diagnostyka[i];
  }
    
  for (size_t i = 0; i < N_DIAGN; i++)
  {
    diagnostyka[i] &= (unsigned int)(~clear_diagnostyka_tmp[i]); 
    diagnostyka[i] |= set_diagnostyka_tmp[i]; 
  }

  for (size_t i = 0; i < N_DIAGN; i++)
  {
    clear_diagnostyka[i] &= (unsigned int)(~clear_diagnostyka_tmp[i]);
    set_diagnostyka[i] &= (unsigned int)(~set_diagnostyka_tmp[i]);
  }
  /*****/
  
  //���������, �� �������� ����
  unsigned int value_changes[N_DIAGN], diagnostyka_now[N_DIAGN];
  /*
  ������ ���� ��������� ����������, �� �� ������� ������ �� ���������� ��������,
  ���� �� ��� ������ ���� ��������� ��� ��������, �� �� �� ��������� � ��� �������
  */
  for (size_t i = 0; i < N_DIAGN; i++)
  {
    diagnostyka_now[i] = diagnostyka[i];
    value_changes[i] = diagnostyka_before[i] ^ diagnostyka_now[i];
  }
  
  /*
  � ��������� ���������� ���� �� ������������ ����� ������� � ��������� ����� � ��������
  ����� ���� �� " ����� ����.    " � " ������� ����.  "
  ���� ������� � ��������� � ��������� �� �������� � ��� ���� �������� ���, �� ���� "��������������"
  */
  
  /*****/
  //���� " ����� ����.    "
  /*****/
  if (_CHECK_SET_BIT(value_changes, EVENT_START_SYSTEM_BIT) != 0)
  {
    //����������� �� ���� " ����� ����.    " ������ ��� ����
    if (_CHECK_SET_BIT(diagnostyka_now, EVENT_START_SYSTEM_BIT) == 0)
    {
      /*
      ����� ���� ��䳿 " ����� ����.    " � ���������� ����
      ���� ������ ���, ��� �� ���� �� ������ � ��������� ���������� ���� ����� ����������
      - ������ ������������ �� ��� ���� ����� ����������
      - ������ �����������, �� � ������������ ���� ���������� �� ���� ���� ��������
      - � �������� ���� ���������� ����� ����� �� �����, �� ��� ������ � ����������
      */
      _CLEAR_BIT(value_changes, EVENT_START_SYSTEM_BIT);
      _CLEAR_BIT(diagnostyka_before, EVENT_START_SYSTEM_BIT);
    }
  }
  /*****/
  
  /*****/
  //���� " ������� ����.  "
  /*****/
  if (_CHECK_SET_BIT(value_changes, EVENT_RESTART_SYSTEM_BIT) != 0)
  {
    //����������� �� ���� " ������� ����.  " ������ ��� ����
    if (_CHECK_SET_BIT(diagnostyka_now, EVENT_RESTART_SYSTEM_BIT) == 0)
    {
      /*
      ����� ���� ��䳿 " ������� ����.  " � ���������� ����
      ���� ������ ���, ��� �� ���� �� ������ � ��������� ���������� ���� ����� ����������
      - ������ ������������ �� ��� ���� ����� ����������
      - ������ �����������, �� � ������������ ���� ���������� �� ���� ���� ��������
      - � �������� ���� ���������� ����� ����� �� �����, �� ��� ������ � ����������
      */
      _CLEAR_BIT(value_changes, EVENT_RESTART_SYSTEM_BIT);
      _CLEAR_BIT(diagnostyka_before, EVENT_RESTART_SYSTEM_BIT);
    }
  }
  /*****/

  /*****/
  //���� "��.������� ��."
  /*****/
  if (_CHECK_SET_BIT(value_changes, EVENT_SOFT_RESTART_SYSTEM_BIT) != 0)
  {
    //����������� �� ���� "��.������� ��." ������ ��� ����
    if (_CHECK_SET_BIT(diagnostyka_now, EVENT_SOFT_RESTART_SYSTEM_BIT) == 0)
    {
      /*
      ����� ���� ��䳿 "��.������� ��." � ���������� ����
      ���� ������ ���, ��� �� ���� �� ������ � ��������� ���������� ���� ����� ����������
      - ������ ������������ �� ��� ���� ����� ����������
      - ������ �����������, �� � ������������ ���� ���������� �� ���� ���� ��������
      - � �������� ���� ���������� ����� ����� �� �����, �� ��� ������ � ����������
      */
      _CLEAR_BIT(value_changes, EVENT_SOFT_RESTART_SYSTEM_BIT);
      _CLEAR_BIT(diagnostyka_before, EVENT_SOFT_RESTART_SYSTEM_BIT);
    }
  }
  /*****/

  //����������, �� ����� ���������� 䳿 ��� ��� ����������
  unsigned int not_null = false;
  for (size_t i = 0; i < N_DIAGN; i++) 
  {
    not_null |= (value_changes[i] != 0);
    if (not_null) break;
  }
  
  if (not_null)
  {
    //� ���, �� ����� ����������, ��� �����
    
    /*****/
    //��� ��������� ������� ����� � ��������� ���������� �������
    /*****/
    if (_CHECK_SET_BIT(diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT) == 0)
    {
      /*
      ����� ����� ������ ����� ���, ���� ���������� �� ���� ����������� 
      ������������ ������, ������ ������, ���� ����� � ��������� ���������� ����
      ������ ���� ��� ������������ ������
      */
      
      //��������� ������� ��������� ������ � ����� ��� ���������� ���������� ����
      int number_empty_cells;
      unsigned int head = head_fifo_buffer_pr_err_records, tail = tail_fifo_buffer_pr_err_records;
      number_empty_cells = (int)(((unsigned int)tail) - ((unsigned int)head));
      while (number_empty_cells <= 0) number_empty_cells += MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER;
      if (number_empty_cells == 1)
      {
        //�� � ������� ����� ������, �� �������, �� � ��� ������� ���������� ����� ���������� ������
        _SET_BIT(diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT);
        /*
        �������� ���� ����� ����������, ��� ����� ��������� � ������ ������� ,����
        ������ ��������� ���� ��������� ����������, ��� ���� ��������� � � ���� �� ��������
        �� ���������� ��������� ����� ���������� �� ������� ���� ������� �
        ���������, �� ����� �� ������ ����������
        */
        _SET_BIT(diagnostyka_now, ERROR_PR_ERR_OVERLOAD_BIT);
        
        //ϳ��������� ���� ������� ��� � ����������
        value_changes[ERROR_PR_ERR_OVERLOAD_BIT >> 5] = diagnostyka_before[ERROR_PR_ERR_OVERLOAD_BIT >> 5] ^ diagnostyka_now[ERROR_PR_ERR_OVERLOAD_BIT >> 5];
      }

      //���������� ������� ��� �������
      unsigned int number_changes = 0;
      for(unsigned int i = 0; i < (8*sizeof(value_changes)); i++)
      {
        if (_CHECK_SET_BIT(value_changes, i) != 0) number_changes++;
      }

      if(number_changes != 0)
      {
        /*
        ���������� ���� ���� ��������, �� �� ������ ����������� ��� ������������ ������
        FIFO ��� ������ ���������� ���������� ����  � �� ���� ����� ����, ��� ��� �����
        � ����� ���� ����� ������, ���� �� ����� ��������� ����������� ��� ������������.
        ���� �� �� ������ ����� �� ����������� - ���� � �� ������ ������ ������ ������, 
        �� �������� � ���� ���� ����
        */
        
        //��������� ������ � ����� ������ ���������� ������� � ����� ���� ������ ����������� ���
        unsigned int index_into_buffer_pr_err = head*SIZE_ONE_RECORD_PR_ERR;
      
        //������� ���� ������� ������
        buffer_pr_err_records[index_into_buffer_pr_err + 0] = LABEL_START_RECORD_PR_ERR;

        //��� �������� ���� � ����������
        if(
           (_CHECK_SET_BIT(diagnostyka, EVENT_START_SYSTEM_BIT       ) == 0) &&
           (_CHECK_SET_BIT(diagnostyka, EVENT_RESTART_SYSTEM_BIT     ) == 0) &&
           (_CHECK_SET_BIT(diagnostyka, EVENT_SOFT_RESTART_SYSTEM_BIT) == 0) &&
           (_CHECK_SET_BIT(diagnostyka, EVENT_STOP_SYSTEM_BIT        ) == 0)
          )
        {
          //��� �������� ����� ����������� ���� - ����� ��������� ��� � ��� �
          unsigned char *label_to_time_array;
          if (copying_time == 2) label_to_time_array = time_copy;
          else label_to_time_array = time;
          for(unsigned int i = 0; i < 7; i++) buffer_pr_err_records[index_into_buffer_pr_err + 1 + i] = *(label_to_time_array + i);
        }
        else
        {
          //�� �� �������� ����� ����������� ���� - ���� ������ �� ���� �������� ������ 0xff, � ����, ���� ��������� ��� ���������, �� �� �� ���� ��������
          for(unsigned int i = 0; i < 7; i++)  buffer_pr_err_records[index_into_buffer_pr_err + 1 + i] = 0xff;
        }

        buffer_pr_err_records[index_into_buffer_pr_err + 8] = number_changes & 0xff;
      
        for (size_t i = 0; i < N_DIAGN_BYTES; i ++)
        {
          unsigned int n_word = i >> 2;
          unsigned int shift = 8*(i & 0x3);
          
          //�������� ��������� ���� ����������
          buffer_pr_err_records[index_into_buffer_pr_err + 9 + i] =  (diagnostyka_before[n_word] >> shift) & 0xff;

          //�������� �������� ���� ����������
          buffer_pr_err_records[index_into_buffer_pr_err + 9 + N_DIAGN_BYTES + i] =  (diagnostyka_now[n_word] >> shift) & 0xff;
        }
        
        /*
        � ��������� ���������� ���� �� ������������ ����� ������� � ��������� ����� � ��������
        ����� ��䳿 �� " �������.����.  " � �� ���� �� �� ���� �������� � ������� ����������,
        �� ��, ��������, ����, ��� ���� ���� �� ���������� ��������� ������� � ������.
        ����� �� ���� "������������ ������ ������"
        ���� ������� � ��������� � ������� �� ������� � ����� �������� ��� �� � �������� ���������,
        ��� ���� ����� ���� ���������� � �����. ���� ������� �� ��������� ���� ����������, ��� � � �����
        ����������, ���� ������� �� ������� ���� ���� ����������
        */
        if (_CHECK_SET_BIT(value_changes, EVENT_STOP_SYSTEM_BIT) != 0)
        {
          /*
          C��� ��䳿 " �������.����.  " ������� (����������� ����� ���������� �������������
          ���� � ��������� ����� � �������� ����)
          ���� ������ ��� ��������
          - ������ ������������ �� � �����, ���� ����� ���� ���������� � ����� ������������ �����
          - ������ ������������ �� � �����, ���� ������� �� ������� ���� ���� ����������
          */
          _CLEAR_BIT(diagnostyka_now, EVENT_STOP_SYSTEM_BIT);
          _CLEAR_BIT(diagnostyka, EVENT_STOP_SYSTEM_BIT);
        }

        //Գ����� ��������� ����, ���� �� ��� �������� � ������� ����� ������ ��������� ��� ����
        for (size_t i = 0; i < N_DIAGN; i ++) diagnostyka_before[i] = diagnostyka_now[i];

        //ϳ������������� �� ������� ������ � ��������� ���������� ����
          unsigned int next_index_into_fifo_buffer = head + 1;
          while(next_index_into_fifo_buffer >= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER) next_index_into_fifo_buffer -= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER;
          
          //������������ ���� �������� ������ ������ FIFO 
          head_fifo_buffer_pr_err_records = next_index_into_fifo_buffer;
      }
    }
    /*****/
  }
}
/*****************************************************/

/*****************************************************/
//ϳ�������� ������� ����������� �������� � ������ ���'�� ������� ��� ����������� ���������� source
/*****************************************************/
unsigned int count_number_set_bit(unsigned int* source, unsigned int total_number)
{
  unsigned int count = 0;
  unsigned int offset, shift;
  
  for (unsigned int i = 0; i < total_number; i++)  
  {
    offset = i >> 5; //�� �, ��������, ������ �� 32
    shift  = (i & (32 - 1)); //�� �, ��������, ���������� ������ �� ������ �� 32
    if ( ( (*(source + offset))  & ((unsigned int)(1 << shift)) ) != 0 ) count++;
  }

  return count;
}
/*****************************************************/

/*****************************************************/
//�������� ����������� ���������
/*****************************************************/
void control_settings(void)
{
  unsigned char crc_settings_tmp = 0, temp_value_1, temp_value_2;
  unsigned char  *point_1 = (unsigned char*)(&current_settings); 
  unsigned char  *point_2 = (unsigned char*)(&current_settings_prt); 
  unsigned int i = 0, difference = 0;
  while ((difference == 0) && (i < sizeof(__SETTINGS)))
  {
    temp_value_1 = *(point_1);
    temp_value_2 = *(point_2);
    crc_settings_tmp += temp_value_1;
    if (temp_value_1 != temp_value_2) difference = 0xff;
    point_1++;
    point_2++;
    i++;
  }
  
  if ((difference == 0) && (crc_settings == crc_settings_tmp))
  {
    //�������� ����������� ������� ��������� ������� ������
    
    //������� ����������� � ���� ����������
    _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_CONTROL_BIT);
  }
  else
  {
    //�������� ����������� ������� ��������� �� �������

    //���������� ����������� � ���� ����������
    _SET_BIT(set_diagnostyka, ERROR_SETTINGS_EEPROM_CONTROL_BIT);
  }
}
/*****************************************************/

/*****************************************************/
//�������� ����������� ���������
/*****************************************************/
void control_ustuvannja(void)
{
  unsigned char crc_ustuvannja_tmp = 0, temp_value_1, temp_value_2;
  unsigned char  *point_1; 
  unsigned char  *point_2; 
  unsigned int i = 0, difference = 0;

  /*
  � ��������� ���� ������� ������������� ���� ������ �������� �����������,
  ���� ����� ����� ���� unsigned int
  */
  unsigned int adjustment_id_tmp = ADJUSTMENT_ID;
  point_1 = (unsigned char*)(&adjustment_id_tmp); 
  while (i < sizeof(unsigned int))
  {
    temp_value_1 = *(point_1);
    crc_ustuvannja_tmp += temp_value_1;
    point_1++;
    i++;
  }
  
  point_1 = (unsigned char*)(&ustuvannja); 
  point_2 = (unsigned char*)(&ustuvannja_meas);
  i = 0;
  while ((difference == 0) && (i < sizeof(ustuvannja)))
  {
    temp_value_1 = *(point_1);
    temp_value_2 = *(point_2);
    crc_ustuvannja_tmp += temp_value_1;
    if (temp_value_1 != temp_value_2) difference = 0xff;
    point_1++;
    point_2++;
    i++;
  }

  point_1 = (unsigned char*)(&phi_ustuvannja); 
  point_2 = (unsigned char*)(&phi_ustuvannja_meas);
  i = 0;
  while ((difference == 0) && (i < sizeof(phi_ustuvannja)))
  {
    temp_value_1 = *(point_1);
    temp_value_2 = *(point_2);
    crc_ustuvannja_tmp += temp_value_1;
    if (temp_value_1 != temp_value_2) difference = 0xff;
    point_1++;
    point_2++;
    i++;
  }

  point_1 = (unsigned char*)(&phi_ustuvannja_sin_cos); 
  point_2 = (unsigned char*)(&phi_ustuvannja_sin_cos_meas);
  i = 0;
  while ((difference == 0) && (i < sizeof(phi_ustuvannja_sin_cos)))
  {
    temp_value_1 = *(point_1);
    temp_value_2 = *(point_2);
    crc_ustuvannja_tmp += temp_value_1;
    if (temp_value_1 != temp_value_2) difference = 0xff;
    point_1++;
    point_2++;
    i++;
  }

  /*
  �� ����� ������������ ����������� ������� ������, ���� ������ � ����������� ��������,
  �� �������� �������, �� �� ������ ����������������� � ������������� �� ����� ��������,
  �� ���� ������ �� ����
  */
  point_1 = (unsigned char*)(&serial_number_dev); 
  i = 0;
  while ((difference == 0) && (i < sizeof(serial_number_dev)))
  {
    temp_value_1 = *(point_1);
    crc_ustuvannja_tmp += temp_value_1;
    point_1++;
    i++;
  }
  
  if ((difference == 0) && (crc_ustuvannja == crc_ustuvannja_tmp))
  {
    //�������� ����������� ��������� ������� ������
    
    //������� ����������� � ���� ����������
    _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_CONTROL_BIT);
  }
  else
  {
    //�������� ����������� ��������� �� �������

    //���������� ����������� � ���� ����������
    _SET_BIT(set_diagnostyka, ERROR_USTUVANNJA_EEPROM_CONTROL_BIT);
  }
}
/*****************************************************/

/*****************************************************/
//�������� ����������� ������� ����������
/*****************************************************/
void control_trg_func(void)
{
  unsigned char crc_trg_func_tmp = 0, temp_value_1;
  unsigned char  *point; 
  unsigned int i;
  
  point = (unsigned char*)(&fix_active_buttons_ctrl);
  i = 0;  
  while (i < sizeof(fix_active_buttons_ctrl))
  {
    temp_value_1 = *(point);
    crc_trg_func_tmp += temp_value_1;
    point++;
    i++;
  }
  
  point = (unsigned char*)(trigger_active_functions_ctrl);
  i = 0;  
  while (i < sizeof(trigger_active_functions_ctrl))
  {
    temp_value_1 = *(point);
    crc_trg_func_tmp += temp_value_1;
    point++;
    i++;
  }
  
  if (crc_trg_func == crc_trg_func_tmp)
  {
    //�������� ����������� ��������� ������� ������
    
    //������� ����������� � ���� ����������
    _SET_BIT(clear_diagnostyka, ERROR_TRG_FUNC_EEPROM_CONTROL_BIT);
  }
  else
  {
    //�������� ����������� ��������� �� �������

    //���������� ����������� � ���� ����������
    _SET_BIT(set_diagnostyka, ERROR_TRG_FUNC_EEPROM_CONTROL_BIT);
  }
}
/*****************************************************/

/*****************************************************/
//�������� ����������� ���������� �� �����������
/*****************************************************/
unsigned int control_info_rejestrator(__INFO_REJESTRATOR* info_rejestrator_point, unsigned char crc_info_rejestrator)
{
  unsigned int result;
  unsigned char crc_info_rejestrator_tmp = 0, temp_value_1;
  unsigned char  *point = (unsigned char*)(info_rejestrator_point); 
  unsigned int i = 0;
  while (i < sizeof(__INFO_REJESTRATOR))
  {
    temp_value_1 = *(point);
    crc_info_rejestrator_tmp += temp_value_1;
    point++;
    i++;
  }
  
  if (crc_info_rejestrator == crc_info_rejestrator_tmp)
  {
    //�������� ����������� ���������� ������� ������
    result = 1;    
  }
  else
  {
    //�������� ����������� ���������� �� �������
    result = 0;    
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
//�������� ����������� ���������� �� ����������� ����������
/*****************************************************/
unsigned int control_info_ar_rejestrator(__INFO_AR_REJESTRATOR* info_rejestrator_point, unsigned char crc_info_rejestrator)
{
  unsigned int result;
  unsigned char crc_info_rejestrator_tmp = 0, temp_value_1;
  unsigned char  *point = (unsigned char*)(info_rejestrator_point); 
  unsigned int i = 0;
  while (i < sizeof(__INFO_AR_REJESTRATOR))
  {
    temp_value_1 = *(point);
    crc_info_rejestrator_tmp += temp_value_1;
    point++;
    i++;
  }
  
  if (crc_info_rejestrator == crc_info_rejestrator_tmp)
  {
    //�������� ����������� ���������� ������� ������
    result = 1;    
  }
  else
  {
    //�������� ����������� ���������� �� �������
    result = 0;    
  }
  
  return result;
}
/*****************************************************/

/*****************************************************/
//�������� ����������� ��������� �������
/*****************************************************/
void control_resurs(void)
{
  unsigned char crc_resurs_tmp = 0, temp_value;
  unsigned char *point;
  
  point = (unsigned char*)(&resurs_vymykacha_ctrl); 
  for (unsigned int i = 0; i < sizeof(resurs_vymykacha_ctrl); i++)
  {
    temp_value = *(point);
    crc_resurs_tmp += temp_value;
    point++;
  }

  point = (unsigned char*)(&resurs_vidkljuchennja_ctrl); 
  for (unsigned int i = 0; i < sizeof(resurs_vidkljuchennja_ctrl); i++)
  {
    temp_value = *(point);
    crc_resurs_tmp += temp_value;
    point++;
  }

  if (crc_resurs_ctrl == crc_resurs_tmp)
  {
    //�������� ����������� ������� ��������� ������� ������
    
    //������� ����������� � ���� ����������
    _SET_BIT(clear_diagnostyka, ERROR_RESURS_EEPROM_CONTROL_BIT);
  }
  else
  {
    //�������� ����������� ��������� �� �������

    //���������� ����������� � ���� ����������
    _SET_BIT(set_diagnostyka, ERROR_RESURS_EEPROM_CONTROL_BIT);
  }
  
}
/*****************************************************/

/*****************************************************/
//���������� ������ ����� � ��������� __DATE__
/*****************************************************/
int str_to_int_DATE_Mmm(void)
{
  static const char month_names[12*3] = "JanFebMarAprMayJunJulAugSepOctNovDec";
  
  int i = 0;
  while(i < 12)
  {
    if (
        (month_names[3*i + 0] == __DATE__[0]) &&
        (month_names[3*i + 1] == __DATE__[1]) &&
        (month_names[3*i + 2] == __DATE__[2])
       )
    {
      break;
    }
    
    i++;
  } 
  
  if (i < 12)
  { 
    i += 1; /*��� ��������� ������ ���� � "1", � �� � "0"*/
    return ((i / 10) << 4) + (i % 10);
  }
  else return 0;
}
/*****************************************************/

/*****************************************************/
/*****************************************************/
//
/*****************************************************/
