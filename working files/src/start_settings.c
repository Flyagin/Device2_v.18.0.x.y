#include "header.h"


/**************************************/
//���������� �������� SRAM
/**************************************/
inline void test_external_SRAM(void)
{
  //���������� ������� ���������� ���
  unsigned int size_SRAM_word = (((unsigned int)__section_size("variables_RAM1")/*&__ICFEDIT_region_RAM1_size__*/) + 1) >> 1;
  
  //��������� �������� �� ������� �������� ���������� ���'��
   unsigned short int *point = ((unsigned short int *)__section_begin("variables_RAM1")/*&__ICFEDIT_region_RAM1_start__*/);
  
  //���������� ����� ������ ������� ���������� ���'�� �� �������
  for (unsigned int i = 0; i < size_SRAM_word; i++) *point++ = (unsigned short int)(i & 0xffff);
  
  //���������� �����������, �� � ��� ������� �������� � �����, �� �� ���������� ��������
  unsigned int error = 0, i = 0;
  point = ((unsigned short int *)__section_begin("variables_RAM1")/*&__ICFEDIT_region_RAM1_start__*/);
  while((i < size_SRAM_word) && (error == 0))
  {
    if ((*point) == ((unsigned short int)(i & 0xffff)))
    {
      //���� ���� ������ ������� �����
      i++;
      *point++ = 0;
    }
    else
    {
      //���� ���� ������ �� ������� �����
      
      error = 0xff;
      //����������� ����������� ��� ������� ����� ������� ���������� ���'��
      _SET_BIT(set_diagnostyka, ERROR_EXTERNAL_SRAM_BIT);
    }
  }
}
/**************************************/

/**************************************/
//�������� ����������� ������
/**************************************/
void global_vareiables_installation(void)
{
  /**************************/
  //����������� �������
  /**************************/
//  for (unsigned int i = 0; i < NUMBER_INPUTs_ADCs; i++)
//  {
//    output_adc[i].tick = 0;
//    output_adc[i].value = 0;
//  }
  
  for(size_t i = 0; i < NUMBER_ANALOG_CANALES; i++)
  {
    for(unsigned int j = 0; j < MAIN_FREQUENCY; j++) vref_adc_moment_value_1s[i][j] = VREF_NORMAL_VALUE;
//    vref_adc[i] = VREF_NORMAL_VALUE;
  }
  
//  for(unsigned int i=0; i<(NUMBER_ANALOG_CANALES*NUMBER_POINT*NUMBER_PERIOD_TRANSMIT); i++)
//    current_data[i] = 0;
  
//  for(unsigned int i=0; i<NUMBER_POINT; i++)
//  {
//    sqr_current_data_3I0[i] = 0;
//  }

//  rozshyrena_vyborka.time_p = 0;
//  rozshyrena_vyborka.time_c = 0;
//  for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++)
//  {
//    rozshyrena_vyborka.data_p[i] = 0;
//    rozshyrena_vyborka.data_c[i] = 0;
//  }

  for (unsigned int i = 0; i < MAX_INDEX_DATA_FOR_OSCYLOGRAPH; i++)
  {
//    data_for_oscylograph[i].time_stemp = 0;
//    data_for_oscylograph[i].DATA_fix = 0;
//    for (unsigned int j = 0; j < NUMBER_ANALOG_CANALES; j++) data_for_oscylograph[i].data[j] = 0;
//    for (unsigned int j = 0; j < N_BIG; j++) data_for_oscylograph[i].active_functions[j] = 0;
    data_for_oscylograph[i].state_ar_record = STATE_AR_NONE_M;
  }

//  for (unsigned int i = 0; i < MAX_INDEX_PhK; i++)
//  {
//    for (unsigned int j = 0; j < 2; j++)
//    {
//      perechid_cherez_nul[i][j].x1 = 0;
//      perechid_cherez_nul[i][j].y1 = 0;
//
//      perechid_cherez_nul[i][j].x2 = 0;
//      perechid_cherez_nul[i][j].y2 = 0;
//    }
//    fix_perechid_cherez_nul[i] = 0;
//  }

//  poperednij_perechid.Ua_x1 = 0;
//  poperednij_perechid.Ua_y1 = 0;
//  poperednij_perechid.Ua_x2 = 0;
//  poperednij_perechid.Ua_y2 = 0;
//  poperednij_perechid.Ub_x1 = 0;
//  poperednij_perechid.Ub_y1 = 0;
//  poperednij_perechid.Ub_x2 = 0;
//  poperednij_perechid.Ub_y2 = 0;
//  poperednij_perechid.Uc_x1 = 0;
//  poperednij_perechid.Uc_y1 = 0;
//  poperednij_perechid.Uc_x2 = 0;
//  poperednij_perechid.Uc_y2 = 0;
//  poperednij_perechid.U0_x1 = 0;
//  poperednij_perechid.U0_y1 = 0;
//  poperednij_perechid.U0_x2 = 0;
//  poperednij_perechid.U0_y2 = 0;
  
  sector_1[0] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*((float)(  0 + SECTOR1 - POPRAVKA_NZZ))/180.0f)));
  sector_1[1] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*((float)(  0 + SECTOR1 - POPRAVKA_NZZ))/180.0f)));
  sector_1[2] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*((float)(180 - SECTOR1 - POPRAVKA_NZZ))/180.0f)));
  sector_1[3] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*((float)(180 - SECTOR1 - POPRAVKA_NZZ))/180.0f)));
  sector_1[4] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*((float)(180 + SECTOR1 - POPRAVKA_NZZ))/180.0f)));
  sector_1[5] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*((float)(180 + SECTOR1 - POPRAVKA_NZZ))/180.0f)));
  sector_1[6] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*((float)(360 - SECTOR1 - POPRAVKA_NZZ))/180.0f)));
  sector_1[7] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*((float)(360 - SECTOR1 - POPRAVKA_NZZ))/180.0f)));

  sector_2[0] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*((float)(  0 + SECTOR2 - POPRAVKA_NZZ))/180.0f)));
  sector_2[1] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*((float)(  0 + SECTOR2 - POPRAVKA_NZZ))/180.0f)));
  sector_2[2] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*((float)(180 - SECTOR2 - POPRAVKA_NZZ))/180.0f)));
  sector_2[3] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*((float)(180 - SECTOR2 - POPRAVKA_NZZ))/180.0f)));
  sector_2[4] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*((float)(180 + SECTOR2 - POPRAVKA_NZZ))/180.0f)));
  sector_2[5] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*((float)(180 + SECTOR2 - POPRAVKA_NZZ))/180.0f)));
  sector_2[6] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*((float)(360 - SECTOR2 - POPRAVKA_NZZ))/180.0f)));
  sector_2[7] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*((float)(360 - SECTOR2 - POPRAVKA_NZZ))/180.0f)));
  
  sector_1_mtz_tznp[0] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*((float)( 90 - SECTOR1_MTZ_TZNP - POPRAVKA_MTZ_TZNP))/180.0f)));
  sector_1_mtz_tznp[1] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*((float)( 90 - SECTOR1_MTZ_TZNP - POPRAVKA_MTZ_TZNP))/180.0f)));
  sector_1_mtz_tznp[2] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*((float)( 90 + SECTOR1_MTZ_TZNP - POPRAVKA_MTZ_TZNP))/180.0f)));
  sector_1_mtz_tznp[3] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*((float)( 90 + SECTOR1_MTZ_TZNP - POPRAVKA_MTZ_TZNP))/180.0f)));
  sector_1_mtz_tznp[4] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*((float)(-90 - SECTOR1_MTZ_TZNP - POPRAVKA_MTZ_TZNP))/180.0f)));
  sector_1_mtz_tznp[5] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*((float)(-90 - SECTOR1_MTZ_TZNP - POPRAVKA_MTZ_TZNP))/180.0f)));
  sector_1_mtz_tznp[6] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*((float)(-90 + SECTOR1_MTZ_TZNP - POPRAVKA_MTZ_TZNP))/180.0f)));
  sector_1_mtz_tznp[7] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*((float)(-90 + SECTOR1_MTZ_TZNP - POPRAVKA_MTZ_TZNP))/180.0f)));

  sector_2_mtz_tznp[0] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*((float)( 90 - SECTOR2_MTZ_TZNP - POPRAVKA_MTZ_TZNP))/180.0f)));
  sector_2_mtz_tznp[1] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*((float)( 90 - SECTOR2_MTZ_TZNP - POPRAVKA_MTZ_TZNP))/180.0f)));
  sector_2_mtz_tznp[2] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*((float)( 90 + SECTOR2_MTZ_TZNP - POPRAVKA_MTZ_TZNP))/180.0f)));
  sector_2_mtz_tznp[3] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*((float)( 90 + SECTOR2_MTZ_TZNP - POPRAVKA_MTZ_TZNP))/180.0f)));
  sector_2_mtz_tznp[4] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*((float)(-90 - SECTOR2_MTZ_TZNP - POPRAVKA_MTZ_TZNP))/180.0f)));
  sector_2_mtz_tznp[5] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*((float)(-90 - SECTOR2_MTZ_TZNP - POPRAVKA_MTZ_TZNP))/180.0f)));
  sector_2_mtz_tznp[6] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*((float)(-90 + SECTOR2_MTZ_TZNP - POPRAVKA_MTZ_TZNP))/180.0f)));
  sector_2_mtz_tznp[7] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*((float)(-90 + SECTOR2_MTZ_TZNP - POPRAVKA_MTZ_TZNP))/180.0f)));

//  for(unsigned int i=0; i<(NUMBER_POINT*NUMBER_ANALOG_CANALES); i++)
//  {
//    data_sin[i] = 0;
//    data_cos[i] = 0;
//  }
  
//  for(unsigned int i=0; i<NUMBER_ANALOG_CANALES; i++)
//  {
//    ADCs_data_raw[i].tick = 0;
//    ADCs_data_raw[i].value = 0;
//      
//    ustuvannja_meas[i] = ustuvannja[i] = DEFAULT_USTUVANNJA_VALUE;
//
//    int phi_tmp;
//    phi_ustuvannja_meas[i] = phi_ustuvannja[i] = phi_tmp = 0;
//    
//    float phi_radian_tmp = PI*((float)phi_tmp)/180.0f;
//    phi_ustuvannja_sin_cos_meas[2*i    ] = phi_ustuvannja_sin_cos[2*i    ] = arm_sin_f32(phi_radian_tmp);
//    phi_ustuvannja_sin_cos_meas[2*i + 1] = phi_ustuvannja_sin_cos[2*i + 1] = arm_cos_f32(phi_radian_tmp);
//  }

//  for(unsigned int i=0; i<(2*NUMBER_ANALOG_CANALES); i++)
//  {
//    ortogonal_irq[i] = 0;
//    ortogonal[i][0] = ortogonal[i][1] = 0;
//  }

//  for(unsigned int i=0; i<(2*FULL_ORT_MAX); i++)
//  {
//    ortogonal_calc[i]     = 0;
//    ortogonal_calc_low[i] = 0;
//  }
  /**************************/

  /**************************/
  //����������� ���������� �������
  /**************************/
  for(unsigned int i = 0; i < MAX_NUMBER_GLOBAL_TIMERS; i++) global_timers[i] = -1;
  /**************************/

  /**************************/
  //����, �� ������ ��� ����������� ����������
  /**************************/
  for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++)
  {
    buffer_for_save_dr_record[i] = 0xff;
  }
  /**************************/
  
//  /**************************
//  ��������� (�� �� ���� �� ���� ���� ����������), ��� ��� ������ ������� 
//  ������ ���������
//  **************************/
//  number_word_digital_part_ar = NUMBER_TOTAL_SIGNAL_FOR_RANG/(8*sizeof(short int));
//  if ((number_word_digital_part_ar*8*sizeof(short int)) < NUMBER_TOTAL_SIGNAL_FOR_RANG) number_word_digital_part_ar += 1;
//  /**************************/

  /**************************/
  //
  /**************************/
  /**************************/

  for(unsigned int i = 0; i < MAX_ROW_LCD; i++)
  {
    for (unsigned int j = 0; j < MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
  }
//  for (unsigned int i=0; i<NUMBER_KEY_KEYBOARD; i++) time_set_keyboard[i] = 0;
 
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
//  current_ekran.edition = 0;
//  current_ekran.cursor_on = 0;
//  current_ekran.cursor_blinking_on = 0;  
  
//  time[0] = 0x0;
//  time[1] = 0x0;
//  time[2] = 0x0;
//  time[3] = 0x0;
//  time[4] = 0x0;
//  time[5] = 0x0;
//  time[6] = 0x0;
//  calibration = 0;

//  time_copy[0] = 0x0;
//  time_copy[1] = 0x0;
//  time_copy[2] = 0x0;
//  time_copy[3] = 0x0;
//  time_copy[4] = 0x0;
//  time_copy[5] = 0x0;
//  time_copy[6] = 0x0;
//  calibration_copy = 0;
  
  /**************************/
  //����������� ��������� ���������� ��������� I2C
  /**************************/
  //���� �����
  driver_i2c.state_execution = -1;
  //������������� ��������, � ���� ������������
  driver_i2c.device_id = -1;
  //��� ��������
  driver_i2c.action =- 1;
  //�������� ����� ���� ���� �� ��� ��� 
  /**************************/

//  /**************************/
//  //��������� ����� ��� ����������� ����������
//  /**************************/
//  for(unsigned int i = 0; i < SIZE_BUFFER_FOR_AR; i++) array_ar[i] = 0;
//  /**************************/

  /**************************/
  //�������������� ��������� ��� ���
  /**************************/
  mtz_settings_prt[MTZ_LEVEL1][RANG_BLOCK_MTZ] = RANG_BLOCK_MTZ1;
  mtz_settings_prt[MTZ_LEVEL1][RANG_SECTOR_VPERED_MTZN] = RANG_SECTOR_VPERED_MTZN1;
  mtz_settings_prt[MTZ_LEVEL1][RANG_SECTOR_NAZAD_MTZN] = RANG_SECTOR_NAZAD_MTZN1;
  mtz_settings_prt[MTZ_LEVEL1][RANG_PO_MTZ] = RANG_PO_MTZ1;
  mtz_settings_prt[MTZ_LEVEL1][RANG_PO_MTZN_VPERED] = RANG_PO_MTZN1_VPERED;
  mtz_settings_prt[MTZ_LEVEL1][RANG_PO_MTZN_NAZAD] = RANG_PO_MTZN1_NAZAD;
  mtz_settings_prt[MTZ_LEVEL1][RANG_PO_U_MTZPN] = RANG_PO_U_MTZPN1;
  mtz_settings_prt[MTZ_LEVEL1][RANG_PO_MTZPN] = RANG_PO_MTZPN1;
  mtz_settings_prt[MTZ_LEVEL1][RANG_MTZ] = RANG_MTZ1;
  
  mtz_settings_prt[MTZ_LEVEL2][RANG_BLOCK_MTZ] = RANG_BLOCK_MTZ2;
  mtz_settings_prt[MTZ_LEVEL2][RANG_BLOCK_USK_MTZ] = RANG_BLOCK_USK_MTZ2;
  mtz_settings_prt[MTZ_LEVEL2][RANG_SECTOR_VPERED_MTZN] = RANG_SECTOR_VPERED_MTZN2;
  mtz_settings_prt[MTZ_LEVEL2][RANG_SECTOR_NAZAD_MTZN] = RANG_SECTOR_NAZAD_MTZN2;
  mtz_settings_prt[MTZ_LEVEL2][RANG_PO_MTZ] = RANG_PO_MTZ2;
  mtz_settings_prt[MTZ_LEVEL2][RANG_PO_MTZN_VPERED] = RANG_PO_MTZN2_VPERED;
  mtz_settings_prt[MTZ_LEVEL2][RANG_PO_MTZN_NAZAD] = RANG_PO_MTZN2_NAZAD;
  mtz_settings_prt[MTZ_LEVEL2][RANG_PO_U_MTZPN] = RANG_PO_U_MTZPN2;
  mtz_settings_prt[MTZ_LEVEL2][RANG_PO_MTZPN] = RANG_PO_MTZPN2;
  mtz_settings_prt[MTZ_LEVEL2][RANG_MTZ] = RANG_MTZ2;
  
  mtz_settings_prt[MTZ_LEVEL3][RANG_BLOCK_MTZ] = RANG_BLOCK_MTZ3;
  mtz_settings_prt[MTZ_LEVEL3][RANG_SECTOR_VPERED_MTZN] = RANG_SECTOR_VPERED_MTZN3;
  mtz_settings_prt[MTZ_LEVEL3][RANG_SECTOR_NAZAD_MTZN] = RANG_SECTOR_NAZAD_MTZN3;
  mtz_settings_prt[MTZ_LEVEL3][RANG_PO_MTZ] = RANG_PO_MTZ3;
  mtz_settings_prt[MTZ_LEVEL3][RANG_PO_MTZN_VPERED] = RANG_PO_MTZN3_VPERED;
  mtz_settings_prt[MTZ_LEVEL3][RANG_PO_MTZN_NAZAD] = RANG_PO_MTZN3_NAZAD;
  mtz_settings_prt[MTZ_LEVEL3][RANG_PO_U_MTZPN] = RANG_PO_U_MTZPN3;
  mtz_settings_prt[MTZ_LEVEL3][RANG_PO_MTZPN] = RANG_PO_MTZPN3;
  mtz_settings_prt[MTZ_LEVEL3][RANG_MTZ] = RANG_MTZ3;
  
  mtz_settings_prt[MTZ_LEVEL4][RANG_BLOCK_MTZ] = RANG_BLOCK_MTZ4;
  mtz_settings_prt[MTZ_LEVEL4][RANG_SECTOR_VPERED_MTZN] = RANG_SECTOR_VPERED_MTZN4;
  mtz_settings_prt[MTZ_LEVEL4][RANG_SECTOR_NAZAD_MTZN] = RANG_SECTOR_NAZAD_MTZN4;
  mtz_settings_prt[MTZ_LEVEL4][RANG_PO_MTZ] = RANG_PO_MTZ4;
  mtz_settings_prt[MTZ_LEVEL4][RANG_PO_MTZN_VPERED] = RANG_PO_MTZN4_VPERED;
  mtz_settings_prt[MTZ_LEVEL4][RANG_PO_MTZN_NAZAD] = RANG_PO_MTZN4_NAZAD;
  mtz_settings_prt[MTZ_LEVEL4][RANG_PO_U_MTZPN] = RANG_PO_U_MTZPN4;
  mtz_settings_prt[MTZ_LEVEL4][RANG_PO_MTZPN] = RANG_PO_MTZPN4;
  mtz_settings_prt[MTZ_LEVEL4][RANG_MTZ] = RANG_MTZ4;
  
  mtz_const_menu_settings_prt[MTZ_LEVEL1][CTR_MTZ] = CTR_MTZ_1;
  mtz_const_menu_settings_prt[MTZ_LEVEL1][CTR_MTZ_VPERED] = CTR_MTZ_1_VPERED;
  mtz_const_menu_settings_prt[MTZ_LEVEL1][CTR_MTZ_NAZAD] = CTR_MTZ_1_NAZAD;
  
  mtz_const_menu_settings_prt[MTZ_LEVEL2][CTR_MTZ] = CTR_MTZ_2;
  mtz_const_menu_settings_prt[MTZ_LEVEL2][CTR_MTZ_VPERED] = CTR_MTZ_2_VPERED;
  mtz_const_menu_settings_prt[MTZ_LEVEL2][CTR_MTZ_NAZAD] = CTR_MTZ_2_NAZAD;
  
  mtz_const_menu_settings_prt[MTZ_LEVEL3][CTR_MTZ] = CTR_MTZ_3;
  mtz_const_menu_settings_prt[MTZ_LEVEL3][CTR_MTZ_VPERED] = CTR_MTZ_3_VPERED;
  mtz_const_menu_settings_prt[MTZ_LEVEL3][CTR_MTZ_NAZAD] = CTR_MTZ_3_NAZAD;
  
  mtz_const_menu_settings_prt[MTZ_LEVEL4][CTR_MTZ] = CTR_MTZ_4;
  mtz_const_menu_settings_prt[MTZ_LEVEL4][CTR_MTZ_VPERED] = CTR_MTZ_4_VPERED;
  mtz_const_menu_settings_prt[MTZ_LEVEL4][CTR_MTZ_NAZAD] = CTR_MTZ_4_NAZAD;
  
  type_mtz_arr[MTZ_LEVEL1] = &current_settings_prt.type_mtz1;
  type_mtz_arr[MTZ_LEVEL2] = &current_settings_prt.type_mtz2;
  type_mtz_arr[MTZ_LEVEL3] = &current_settings_prt.type_mtz3;
  type_mtz_arr[MTZ_LEVEL4] = &current_settings_prt.type_mtz4;
  
  setpoint_mtz[MTZ_LEVEL1] = current_settings_prt.setpoint_mtz_1;
  setpoint_mtz[MTZ_LEVEL2] = current_settings_prt.setpoint_mtz_2;
  setpoint_mtz[MTZ_LEVEL3] = current_settings_prt.setpoint_mtz_3;
  setpoint_mtz[MTZ_LEVEL4] = current_settings_prt.setpoint_mtz_4;
  
  setpoint_mtz_n_vpered[MTZ_LEVEL1] = current_settings_prt.setpoint_mtz_1_n_vpered;
  setpoint_mtz_n_vpered[MTZ_LEVEL2] = current_settings_prt.setpoint_mtz_2_n_vpered;
  setpoint_mtz_n_vpered[MTZ_LEVEL3] = current_settings_prt.setpoint_mtz_3_n_vpered;
  setpoint_mtz_n_vpered[MTZ_LEVEL4] = current_settings_prt.setpoint_mtz_4_n_vpered;
  
  setpoint_mtz_n_nazad[MTZ_LEVEL1] = current_settings_prt.setpoint_mtz_1_n_nazad;
  setpoint_mtz_n_nazad[MTZ_LEVEL2] = current_settings_prt.setpoint_mtz_2_n_nazad;
  setpoint_mtz_n_nazad[MTZ_LEVEL3] = current_settings_prt.setpoint_mtz_3_n_nazad;
  setpoint_mtz_n_nazad[MTZ_LEVEL4] = current_settings_prt.setpoint_mtz_4_n_nazad;
  
  setpoint_mtz_U[MTZ_LEVEL1] = current_settings_prt.setpoint_mtz_1_U;
  setpoint_mtz_U[MTZ_LEVEL2] = current_settings_prt.setpoint_mtz_2_U;
  setpoint_mtz_U[MTZ_LEVEL3] = current_settings_prt.setpoint_mtz_3_U;
  setpoint_mtz_U[MTZ_LEVEL4] = current_settings_prt.setpoint_mtz_4_U;
  
  setpoint_mtz_po_napruzi[MTZ_LEVEL1] = current_settings_prt.setpoint_mtz_1_po_napruzi;
  setpoint_mtz_po_napruzi[MTZ_LEVEL2] = current_settings_prt.setpoint_mtz_2_po_napruzi;
  setpoint_mtz_po_napruzi[MTZ_LEVEL3] = current_settings_prt.setpoint_mtz_3_po_napruzi;
  setpoint_mtz_po_napruzi[MTZ_LEVEL4] = current_settings_prt.setpoint_mtz_4_po_napruzi;
  
  mtz_tmr_const[MTZ_LEVEL1][INDEX_TIMER_MTZ] = INDEX_TIMER_MTZ1;
  mtz_tmr_const[MTZ_LEVEL1][INDEX_TIMER_MTZ_N_VPERED] = INDEX_TIMER_MTZ1_N_VPERED;
  mtz_tmr_const[MTZ_LEVEL1][INDEX_TIMER_MTZ_N_NAZAD] = INDEX_TIMER_MTZ1_N_NAZAD;
  mtz_tmr_const[MTZ_LEVEL1][INDEX_TIMER_MTZ_PO_NAPRUZI] = INDEX_TIMER_MTZ1_PO_NAPRUZI;
  mtz_tmr_const[MTZ_LEVEL2][INDEX_TIMER_MTZ] = 0;
  mtz_tmr_const[MTZ_LEVEL2][INDEX_TIMER_MTZ_N_VPERED] = 0;
  mtz_tmr_const[MTZ_LEVEL2][INDEX_TIMER_MTZ_N_NAZAD] = 0;
  mtz_tmr_const[MTZ_LEVEL2][INDEX_TIMER_MTZ_PO_NAPRUZI] = 0;
  mtz_tmr_const[MTZ_LEVEL3][INDEX_TIMER_MTZ] = INDEX_TIMER_MTZ3;
  mtz_tmr_const[MTZ_LEVEL3][INDEX_TIMER_MTZ_N_VPERED] = INDEX_TIMER_MTZ3_N_VPERED;
  mtz_tmr_const[MTZ_LEVEL3][INDEX_TIMER_MTZ_N_NAZAD] = INDEX_TIMER_MTZ3_N_NAZAD;
  mtz_tmr_const[MTZ_LEVEL3][INDEX_TIMER_MTZ_PO_NAPRUZI] = INDEX_TIMER_MTZ3_PO_NAPRUZI;
  mtz_tmr_const[MTZ_LEVEL4][INDEX_TIMER_MTZ] = INDEX_TIMER_MTZ4;
  mtz_tmr_const[MTZ_LEVEL4][INDEX_TIMER_MTZ_N_VPERED] = INDEX_TIMER_MTZ4_N_VPERED;
  mtz_tmr_const[MTZ_LEVEL4][INDEX_TIMER_MTZ_N_NAZAD] = INDEX_TIMER_MTZ4_N_NAZAD;
  mtz_tmr_const[MTZ_LEVEL4][INDEX_TIMER_MTZ_PO_NAPRUZI] = INDEX_TIMER_MTZ4_PO_NAPRUZI;
  
  timeout_mtz[MTZ_LEVEL1] = current_settings_prt.timeout_mtz_1;
  timeout_mtz[MTZ_LEVEL2] = 0;
  timeout_mtz[MTZ_LEVEL3] = current_settings_prt.timeout_mtz_3;
  timeout_mtz[MTZ_LEVEL4] = current_settings_prt.timeout_mtz_4;
  
  timeout_mtz_n_vpered[MTZ_LEVEL1] = current_settings_prt.timeout_mtz_1_n_vpered;
  timeout_mtz_n_vpered[MTZ_LEVEL2] = 0;
  timeout_mtz_n_vpered[MTZ_LEVEL3] = current_settings_prt.timeout_mtz_3_n_vpered;
  timeout_mtz_n_vpered[MTZ_LEVEL4] = current_settings_prt.timeout_mtz_4_n_vpered;
  
  timeout_mtz_n_nazad[MTZ_LEVEL1] = current_settings_prt.timeout_mtz_1_n_nazad;
  timeout_mtz_n_nazad[MTZ_LEVEL2] = 0;
  timeout_mtz_n_nazad[MTZ_LEVEL3] = current_settings_prt.timeout_mtz_3_n_nazad;
  timeout_mtz_n_nazad[MTZ_LEVEL4] = current_settings_prt.timeout_mtz_4_n_nazad;
  
  timeout_mtz_po_napruzi[MTZ_LEVEL1] = current_settings_prt.timeout_mtz_1_po_napruzi;
  timeout_mtz_po_napruzi[MTZ_LEVEL2] = 0;
  timeout_mtz_po_napruzi[MTZ_LEVEL3] = current_settings_prt.timeout_mtz_3_po_napruzi;
  timeout_mtz_po_napruzi[MTZ_LEVEL4] = current_settings_prt.timeout_mtz_4_po_napruzi;
  
//  i_nom_const = I_NOM * KOEF_1_2_I;
//  u_linear_nom_const = U_LINEAR_NOM * KOEF_0_2_U;
  /**************************/
  
  //Modbus-RTU
  type_of_settings_changed = 0;
  password_ustuvannja = 0;
}
/**************************************/

/**************************************/
//�������� ����������� ������� ���������
/**************************************/
void start_settings_peripherals(void)
{
  /**********************/
  //������������ ��������������: ���� + �������
  /**********************/
  Set_System();
  /**********************/

  /**********************/
  //���������� DBG ������
  /**********************/
  DBGMCU_APB1PeriphConfig(DBGMCU_TIM2_STOP | DBGMCU_TIM5_STOP | DBGMCU_TIM4_STOP | DBGMCU_I2C1_SMBUS_TIMEOUT, ENABLE);
  /**********************/

  /**********************/
  //������������ ����������
  /**********************/
  Interrupts_Config();
  /**********************/

  /**********************/
  //������������ ������� ����
  /**********************/
  FSMC_SRAM_Init();
  _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD31_DD34_DD35_DD37) = 0;
#if (                                   \
     (MODYFIKACIA_VERSII_PZ == 0) ||    \
     (MODYFIKACIA_VERSII_PZ == 3)       \
    )   
  _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD28) = 0;
#endif
  /**********************/

  /**********************/
  //������������ ��� ���������
  /**********************/
  GPIO_InitTypeDef GPIO_InitStructure;

  /**************/
  //ϳ�� �� ����
  /**************/
  /* ϳ� ���������� Watchdog, �� Output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_EXTERNAL_WATCHDOG;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIO_EXTERNAL_WATCHDOG, &GPIO_InitStructure);
  /* ������ �� ���������� Watchdog */
  GPIO_SetBits(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG);
  
  /*
  �������� �������� ����������� ������? � ���� ������� Watchdog
  ϳ��� ����� ���������� ��������� �������
  
  �� �������, ��� �������� ����������� �������
  */
  /**********************/
  //������� ������� SRAM
  /**********************/
  test_external_SRAM();
  /**********************/
  
  //������� ���� ��� ���������� Watchdog �� �����������
  GPIO_WriteBit(
                GPIO_EXTERNAL_WATCHDOG,
                GPIO_PIN_EXTERNAL_WATCHDOG,
                (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
               );
    
  /**********************/
  //�������� ����������� ������ � �������� � � ������� SRAM
  /**********************/
  global_vareiables_installation();
  /**********************/
    
  //������� ���� ��� ���������� Watchdog �� �����������
  GPIO_WriteBit(
                GPIO_EXTERNAL_WATCHDOG,
                GPIO_PIN_EXTERNAL_WATCHDOG,
                (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
               );
  /*****/ 

  /*
  ���������� ���������� ����������� �������  
  */
    
  /* ������������ ��� CON-L, �� Output push-pull */
  GPIO_InitStructure.GPIO_Pin = CON_L_PIN;
  GPIO_Init(CON_L, &GPIO_InitStructure);
  /* ������� �� CON-L, ��� ������ ��������� ��������������� �� ����� ����*/
  GPIO_ResetBits(CON_L, CON_L_PIN);

  /* ������������ ��� CON-OUTPUTS, �� Output push-pull */
  GPIO_InitStructure.GPIO_Pin = CON_1_OUTPUTS_PIN;
  GPIO_Init(CON_OUTPUTS, &GPIO_InitStructure);
  /* ����������� �� CON-OUTPUTS-1*/
  GPIO_SetBits(CON_OUTPUTS, CON_1_OUTPUTS_PIN);

  GPIO_InitStructure.GPIO_Pin = CON_2_OUTPUTS_PIN;
  GPIO_Init(CON_OUTPUTS, &GPIO_InitStructure);
  /* ������ �� CON-OUTPUTS-2*/
  GPIO_ResetBits(CON_OUTPUTS, CON_2_OUTPUTS_PIN);

  GPIO_InitStructure.GPIO_Pin = CON_3_OUTPUTS_PIN;
  GPIO_Init(CON_OUTPUTS, &GPIO_InitStructure);
  /* ����������� �� CON-OUTPUTS-3*/
  GPIO_SetBits(CON_OUTPUTS, CON_3_OUTPUTS_PIN);
  
  /***
  �������� �������� ��������� ���� (CON ��� ��� ������������)
  ***/
  _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0;
  uint32_t board_register_tmp = board_register = _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47);
#if (                                   \
     (MODYFIKACIA_VERSII_PZ == 0) ||    \
     (MODYFIKACIA_VERSII_PZ == 3)       \
    )   
  if ((board_register_tmp & 0x17) != 0x17)
#elif (MODYFIKACIA_VERSII_PZ == 1)
  if ((board_register_tmp & 0x07) != 0x07)
#else
  if ((board_register_tmp & 0x03) != 0x03)
#endif
  {
    if ((board_register_tmp &  0x01) !=  0x1) _SET_BIT(set_diagnostyka, ERROR_BA_1_FIX);
    if ((board_register_tmp &  0x02) !=  0x2) _SET_BIT(set_diagnostyka, ERROR_BDVV5_1_FIX);
    
#if (                                   \
     (MODYFIKACIA_VERSII_PZ == 0) ||    \
     (MODYFIKACIA_VERSII_PZ == 1) ||    \
     (MODYFIKACIA_VERSII_PZ == 3)       \
    )
    if ((board_register_tmp &  0x04) !=  0x4) _SET_BIT(set_diagnostyka, ERROR_BDVV5_2_FIX);
#endif

#if (                                   \
     (MODYFIKACIA_VERSII_PZ == 0) ||    \
     (MODYFIKACIA_VERSII_PZ == 3)       \
    )
    if ((board_register_tmp & 0x010) != 0x10) 
#if (MODYFIKACIA_VERSII_PZ == 0)
      _SET_BIT(set_diagnostyka, ERROR_BDV_DZ_FIX);
#else
      _SET_BIT(set_diagnostyka, ERROR_BDZ_FIX);
#endif
      
#endif
    
    
  }
  
  if ((board_register_tmp & 0x01) == 0x01)
  {
    _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x1;
    if ((_DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) >> 8) != 0x11)  _SET_BIT(set_diagnostyka, ERROR_BA_1_CTLR);
  }
  if ((board_register_tmp & 0x02) == 0x02)
  {
    _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x2;
    if ((_DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD33_DD36) & 0xff) != 0x25)  _SET_BIT(set_diagnostyka, ERROR_BDVV5_1_CTLR);
  }

#if (                                   \
     (MODYFIKACIA_VERSII_PZ == 0) ||    \
     (MODYFIKACIA_VERSII_PZ == 1) ||    \
     (MODYFIKACIA_VERSII_PZ == 3)       \
    )
  if ((board_register_tmp & 0x04) == 0x04)
  {
    _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x4;
    if ((_DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD33_DD36) >> 8) != 0x37)  _SET_BIT(set_diagnostyka, ERROR_BDVV5_2_CTLR);
  }
  
#if (                                   \
     (MODYFIKACIA_VERSII_PZ == 0) ||    \
     (MODYFIKACIA_VERSII_PZ == 3)       \
    )
  if ((board_register_tmp & 0x10) == 0x10)
  {
    _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x10;
#if (MODYFIKACIA_VERSII_PZ == 0)
    if ((_DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD26_DD29) >> 8) != 0x14)  _SET_BIT(set_diagnostyka, ERROR_BDV_DZ_CTLR);
#else
    if ((_DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD26_DD29) >> 8) != 0x18)  _SET_BIT(set_diagnostyka, ERROR_BDZ_CTLR);
#endif
  }
#endif
  
#endif
  
  //�������� ���� ��� ���� ��� ���������� ��������
  _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x0;
  /***/
  
  /* ������������ ��� LCD-BL, �� Output push-pull */
  GPIO_InitStructure.GPIO_Pin = LCD_BL_PIN;
  GPIO_Init(LCD_BL, &GPIO_InitStructure);
  /* ������ �� LCD-BL ��� ����, ��� �������� ������� LCD*/
  GPIO_ResetBits(LCD_BL, LCD_BL_PIN);

  /* ������������ ��� LCD-R/W, �� Output push-pull */
  GPIO_InitStructure.GPIO_Pin = LCD_RW_PIN;
  GPIO_Init(LCD_RW, &GPIO_InitStructure);
  /* ������ �� LCD-R/W*/
  GPIO_ResetBits(LCD_RW, LCD_RW_PIN);

  /* ������������ ��� LCD-RS, �� Output push-pull */
  GPIO_InitStructure.GPIO_Pin = LCD_RS_PIN;
  GPIO_Init(LCD_RS, &GPIO_InitStructure);
  /* ������ �� LCD-RS*/
  GPIO_ResetBits(LCD_RS, LCD_RS_PIN);

  /*SW_1 ��������� */
  GPIO_InitStructure.GPIO_Pin = KEYBOARD_SW_1_PIN;
  GPIO_Init(KEYBOARD, &GPIO_InitStructure);
  /* ����������� �� SW1*/
  GPIO_SetBits(KEYBOARD, KEYBOARD_SW_1_PIN);

  /*SW_2 ��������� */
  GPIO_InitStructure.GPIO_Pin = KEYBOARD_SW_2_PIN;
  GPIO_Init(KEYBOARD, &GPIO_InitStructure);
  /* ����������� �� SW2*/
  GPIO_SetBits(KEYBOARD, KEYBOARD_SW_2_PIN);

  /*SW_3 ��������� */
  GPIO_InitStructure.GPIO_Pin = KEYBOARD_SW_3_PIN;
  GPIO_Init(KEYBOARD, &GPIO_InitStructure);
  /*����������� �� SW3*/
  GPIO_SetBits(KEYBOARD, KEYBOARD_SW_3_PIN);

  /*SW_4 ��������� */
  GPIO_InitStructure.GPIO_Pin = KEYBOARD_SW_4_PIN;
  GPIO_Init(KEYBOARD, &GPIO_InitStructure);
  /*����������� �� SW4*/
  GPIO_SetBits(KEYBOARD, KEYBOARD_SW_4_PIN);

  /*���� ��� */
  GPIO_InitStructure.GPIO_Pin = GPIO_SELECTPin_ADC;
  GPIO_Init(GPIO_SELECT_ADC, &GPIO_InitStructure);
  GPIO_ResetBits(GPIO_SELECT_ADC, GPIO_SELECTPin_ADC);

  /*NSS_ADC ������ SPI_ADC */
  GPIO_InitStructure.GPIO_Pin = GPIO_NSSPin_ADC;
  GPIO_Init(GPIO_SPI_ADC, &GPIO_InitStructure);
  GPIO_SetBits(GPIO_SPI_ADC, GPIO_NSSPin_ADC);

  /*NSS_ADC ������ SPI_EDF */
  GPIO_InitStructure.GPIO_Pin = GPIO_NSSPin_EDF;
  GPIO_Init(GPIO_SPI_EDF, &GPIO_InitStructure);
  GPIO_SetBits(GPIO_SPI_EDF, GPIO_NSSPin_EDF);

  /*GPIO_SPI_EDF_A0 - ���� ��������� DataFlash*/
  GPIO_InitStructure.GPIO_Pin = GPIO_SPI_EDF_A0_Pin;
  GPIO_Init(GPIO_SPI_EDF_A0, &GPIO_InitStructure);
  //�������� EEPROM
  GPIO_SetBits(GPIO_SPI_EDF_A0, GPIO_SPI_EDF_A0_Pin);

  /*GPIO_SPI_EDF_A1 - ���� ��������� DataFlash*/
  GPIO_InitStructure.GPIO_Pin = GPIO_SPI_EDF_A1_Pin;
  GPIO_Init(GPIO_SPI_EDF_A1, &GPIO_InitStructure);
  //�������� EEPROM
  GPIO_SetBits(GPIO_SPI_EDF_A1, GPIO_SPI_EDF_A1_Pin);

  /* ϳ� 485DE*/
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_485DE;
  GPIO_Init(GPIO_485DE, &GPIO_InitStructure);
  /* ������ �� 485DE */
  GPIO_ResetBits(GPIO_485DE, GPIO_PIN_485DE);
  /**************/

  /**************/
  //ϳ�� �� ���
  /**************/
  /*SW_A ��������� */
  GPIO_InitStructure.GPIO_Pin = KEYBOARD_SW_A_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(KEYBOARD_SW_A, &GPIO_InitStructure);

  /*SW_B ��������� */
  GPIO_InitStructure.GPIO_Pin = KEYBOARD_SW_B_PIN;
  GPIO_Init(KEYBOARD_SW_B, &GPIO_InitStructure);

  /*SW_C ��������� */
  GPIO_InitStructure.GPIO_Pin = KEYBOARD_SW_C_PIN;
  GPIO_Init(KEYBOARD_SW_C, &GPIO_InitStructure);

  /*�������� �������� */
  GPIO_InitStructure.GPIO_Pin = POWER_CTRL_PIN;
  GPIO_Init(POWER_CTRL, &GPIO_InitStructure);
  /**************/

  /**************/
  //ϳ�� �������������� �������
  /**************/
  //���������� ��� PB13/SPI2_SCK, PB14/SPI2_MISO �  PB15/SPI2_MOSI
  GPIO_PinAFConfig(GPIO_SPI_ADC, GPIO_SCKPin_ADCSource, GPIO_AF_SPI_ADC);
  GPIO_PinAFConfig(GPIO_SPI_ADC, GPIO_MISOPin_ADCSource, GPIO_AF_SPI_ADC);
  GPIO_PinAFConfig(GPIO_SPI_ADC, GPIO_MOSIPin_ADCSource, GPIO_AF_SPI_ADC);

  /* Configure SPI_ADC SCK, MISO � MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_SCKPin_ADC | GPIO_MISOPin_ADC | GPIO_MOSIPin_ADC;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIO_SPI_ADC, &GPIO_InitStructure);

  //���������� ��� PA5/SPI1_SCK, PA6/SPI1_MISO �  PA7/SPI1_MOSI
  GPIO_PinAFConfig(GPIO_SPI_EDF, GPIO_SCKPin_EDFSource, GPIO_AF_SPI_EDF);
  GPIO_PinAFConfig(GPIO_SPI_EDF, GPIO_MISOPin_EDFSource, GPIO_AF_SPI_EDF);
  GPIO_PinAFConfig(GPIO_SPI_EDF, GPIO_MOSIPin_EDFSource, GPIO_AF_SPI_EDF);

  /* Configure SPI_EDF SCK, MISO � MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_SCKPin_EDF | GPIO_MISOPin_EDF | GPIO_MOSIPin_EDF;
  GPIO_Init(GPIO_SPI_EDF, &GPIO_InitStructure);

  //���������� ��� PA2/Tx_RS-485, PA3/Rx_RS-485
  GPIO_PinAFConfig(GPIO_USART_RS485, GPIO_TxPin_RS485Source, GPIO_AF_USART_RS_485);
  GPIO_PinAFConfig(GPIO_USART_RS485, GPIO_RxPin_RS485Source, GPIO_AF_USART_RS_485);

  /* Configure USART_RS485 Rx/Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_TxPin_RS485 | GPIO_RxPin_RS485;
  GPIO_Init(GPIO_USART_RS485, &GPIO_InitStructure);
  /**********************/

  /* ϳ�'������� EXTI Line0 to POWER_CTRL_PIN ��� */
  SYSCFG_EXTILineConfig(EXTI_PortSource_POWER, EXTI_PinSource_POWER);  
  /**********************/

   /* �������������� EXTI Line0 */
  EXTI_InitTypeDef   EXTI_InitStructure;

  EXTI_InitStructure.EXTI_Line = EXTI_Line_POWER;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  /**********************/

  /**********************/
  //������������ DMA ����������
  /**********************/
  DMA_InitTypeDef  DMA_InitStructure;

  /* DMA ���������� ��� ������� ����� �� I2C*/
  DMA_DeInit(DMA_StreamI2C_Rx);
  while (DMA_GetCmdStatus(DMA_StreamI2C_Rx) != DISABLE);
  
  DMA_InitStructure.DMA_Channel = DMA_ChannelI2C_Rx;
  DMA_InitStructure.DMA_PeripheralBaseAddr = I2C_DR_Address;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Temporaty_I2C_Buffer;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = MAX_NUMBER_REGISTERS_RTC + 2;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA_StreamI2C_Rx, &DMA_InitStructure);
  DMA_ClearFlag(DMA_StreamI2C_Rx, DMA_FLAG_TCI2C_Rx | DMA_FLAG_HTI2C_Rx | DMA_FLAG_TEII2C_Rx | DMA_FLAG_DMEII2C_Rx | DMA_FLAG_FEII2C_Rx);

  /* DMA ���������� ��� ����������� ����� �� I2C*/
  DMA_DeInit(DMA_StreamI2C_Tx);
  while (DMA_GetCmdStatus(DMA_StreamI2C_Tx) != DISABLE);
  
  DMA_InitStructure.DMA_Channel = DMA_ChannelI2C_Tx;
  DMA_InitStructure.DMA_PeripheralBaseAddr = I2C_DR_Address;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Temporaty_I2C_Buffer;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
  DMA_Init(DMA_StreamI2C_Tx, &DMA_InitStructure);
  DMA_ClearFlag(DMA_StreamI2C_Tx, DMA_FLAG_TCI2C_Tx | DMA_FLAG_HTI2C_Tx | DMA_FLAG_TEII2C_Tx | DMA_FLAG_DMEII2C_Tx | DMA_FLAG_FEII2C_Tx);

  /* DMA ���������� ��� �������� ����� �� SPI_EDF*/
  DMA_DeInit(DMA_StreamSPI_EDF_Tx);
  while (DMA_GetCmdStatus(DMA_StreamSPI_EDF_Tx) != DISABLE);
  
  DMA_InitStructure.DMA_Channel = DMA_ChannelSPI_EDF_Tx;
  DMA_InitStructure.DMA_PeripheralBaseAddr = SPI_EDF_DR_Address;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)TxBuffer_SPI_EDF;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_BufferSize = SIZE_PAGE_DATAFLASH_MAX + 10;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; /*��� �� � ������ DMA_StreamSPI_EDF_Tx > �� � ������ DMA_StreamSPI_EDF_Rx, �� DMA_StreamSPI_EDF_Rx �� ������� ��� DMA_StreamSPI_EDF_Tx ��� ���������� ����������� ��������*/
  DMA_Init(DMA_StreamSPI_EDF_Tx, &DMA_InitStructure);
  DMA_ClearFlag(DMA_StreamSPI_EDF_Tx, DMA_FLAG_TCSPI_EDF_Tx | DMA_FLAG_HTSPI_EDF_Tx | DMA_FLAG_TEISPI_EDF_Tx | DMA_FLAG_DMEISPI_EDF_Tx | DMA_FLAG_FEISPI_EDF_Tx);

  /* DMA ���������� ��� ������� ����� �� SPI_EDF*/
  DMA_DeInit(DMA_StreamSPI_EDF_Rx);
  while (DMA_GetCmdStatus(DMA_StreamSPI_EDF_Rx) != DISABLE);
  
  DMA_InitStructure.DMA_Channel = DMA_ChannelSPI_EDF_Rx;
  DMA_InitStructure.DMA_PeripheralBaseAddr = SPI_EDF_DR_Address;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)RxBuffer_SPI_EDF;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; /*��� �� � ������ DMA_StreamSPI_EDF_Tx > �� � ������ DMA_StreamSPI_EDF_Rx, �� DMA_StreamSPI_EDF_Rx �� ������� ��� DMA_StreamSPI_EDF_Tx ��� ���������� ����������� ��������*/
  DMA_Init(DMA_StreamSPI_EDF_Rx, &DMA_InitStructure);
  DMA_ClearFlag(DMA_StreamSPI_EDF_Rx, DMA_FLAG_TCSPI_EDF_Rx | DMA_FLAG_HTSPI_EDF_Rx | DMA_FLAG_TEISPI_EDF_Rx | DMA_FLAG_DMEISPI_EDF_Rx | DMA_FLAG_FEISPI_EDF_Rx);

  /* ������ �� RS-485*/
  DMA_DeInit(DMA_StreamRS485_Rx);
  while (DMA_GetCmdStatus(DMA_StreamRS485_Rx) != DISABLE);
  
  DMA_InitStructure.DMA_Channel = DMA_ChannelRS485_Rx;
  DMA_InitStructure.DMA_PeripheralBaseAddr = USARTRS485_DR_Base;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)RxBuffer_RS485;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = BUFFER_RS485;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
  DMA_Init(DMA_StreamRS485_Rx, &DMA_InitStructure);
  DMA_ClearFlag(DMA_StreamRS485_Rx, DMA_FLAG_TCRS485_Rx | DMA_FLAG_HTRS485_Rx | DMA_FLAG_TEIRS485_Rx | DMA_FLAG_DMEIRS485_Rx | DMA_FLAG_FEIRS485_Rx);
  
  /* �������� �� RS-485*/
  DMA_DeInit(DMA_StreamRS485_Tx);
  while (DMA_GetCmdStatus(DMA_StreamRS485_Tx) != DISABLE);

  DMA_InitStructure.DMA_Channel = DMA_ChannelRS485_Tx;
  DMA_InitStructure.DMA_PeripheralBaseAddr = USARTRS485_DR_Base;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)TxBuffer_RS485;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_BufferSize = 0;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
  DMA_Init(DMA_StreamRS485_Tx, &DMA_InitStructure);
  DMA_ClearFlag(DMA_StreamRS485_Tx, DMA_FLAG_TCRS485_Tx | DMA_FLAG_HTRS485_Tx | DMA_FLAG_TEIRS485_Tx | DMA_FLAG_DMEIRS485_Tx | DMA_FLAG_FEIRS485_Tx);
  /**********************/

  /**********************/
  //������������ SPI ���  ��� � ���������� ������������ ��
  /**********************/
  SPI_InitTypeDef  SPI_InitStructure;
  
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS =  SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;/*30���/2 = 15 ���*/
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI_ADC, &SPI_InitStructure);

  /* ���������� SPI_ADC */
  SPI_Cmd(SPI_ADC, ENABLE);
  
  //��������� ������ ���
  //������� �������� �������
  if  (SPI_I2S_GetFlagStatus(SPI_ADC, SPI_I2S_FLAG_RXNE) == SET) SPI_I2S_ReceiveData(SPI_ADC);
  while (SPI_I2S_GetFlagStatus(SPI_ADC, SPI_I2S_FLAG_OVR) == SET) SPI_I2S_ReceiveData(SPI_ADC);
      
  for (unsigned int i = 0; i < NUMBER_ADCs; i++)
  {
    if (i == 0) GPIO_SELECT_ADC->BSRRH = GPIO_SELECTPin_ADC;
    else GPIO_SELECT_ADC->BSRRL = GPIO_SELECTPin_ADC; 
    
    //�������� ����� ����� 0xffff
    while (SPI_I2S_GetFlagStatus(SPI_ADC, SPI_I2S_FLAG_TXE) == RESET);          //�������, ���� SPI ����� ������
    GPIO_ResetBits(GPIO_SPI_ADC, GPIO_NSSPin_ADC);                              //����������� chip_select
    SPI_I2S_SendData(SPI_ADC, 0xFFFF);                                          //³���������� ����� 0xffff
    while (SPI_I2S_GetFlagStatus(SPI_ADC, SPI_I2S_FLAG_RXNE) == RESET);         //������� ���������� ���������� �� �������� ����� �� MISO
    GPIO_SetBits(GPIO_SPI_ADC, GPIO_NSSPin_ADC);                                //������ chip_select
    SPI_I2S_ReceiveData(SPI_ADC);                                               //������ ������� ���

    //�������� ����� ����� 0xffff
    while (SPI_I2S_GetFlagStatus(SPI_ADC, SPI_I2S_FLAG_TXE) == RESET);          //�������, ���� SPI ����� ������
    GPIO_ResetBits(GPIO_SPI_ADC, GPIO_NSSPin_ADC);                              //����������� chip_select
    SPI_I2S_SendData(SPI_ADC, 0xFFFF);                                          //³���������� ����� 0xffff
    while (SPI_I2S_GetFlagStatus(SPI_ADC, SPI_I2S_FLAG_RXNE) == RESET);         //������� ���������� ���������� �� �������� ����� �� MISO
    GPIO_SetBits(GPIO_SPI_ADC, GPIO_NSSPin_ADC);                                //������ chip_select
    SPI_I2S_ReceiveData(SPI_ADC);                                               //������ ������� ���
  }
  
  //���������� ����������� �� ���������� ����� �� SPI
  SPI_I2S_ITConfig(SPI_ADC, SPI_I2S_IT_RXNE, ENABLE);
  /**********************/

  /**********************/
  //������������ TIM4 �� ��������� ���������� ���� 10 �� ��� ��������� � 1 �� ��� ����������������� �����
  /**********************/
  /* ���������� TIM4 */
  /* ---------------------------------------------------------------
  TIM4 ������������: Output Compare Timing Mode:
  TIM4CLK = (30*2) ���, Prescaler = 600, TIM4 counter clock = 100 ���
  CC1 update rate = TIM4 counter clock / CCR1_Val = 100 Hz
  CC2 update rate = TIM4 counter clock / CCR1_Val = 1000 Hz
  --------------------------------------------------------------- */
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;

  TIM_TimeBaseStructure.TIM_Period = 65535;
  TIM_TimeBaseStructure.TIM_Prescaler = (600-1);
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  /* Output Compare Timing Mode ������������: �����:1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_Pulse = TIM4_CCR1_VAL;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);
  
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Disable);

  /* ���������� ����������� �� ������ 1 ������� 4*/
  TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);

  /* ��������� ������ ������� */
  TIM_Cmd(TIM4, ENABLE);
  /**********************/

  /**********************/
  //������������ SPI ���  DataFlash � ���������� �������� , �� ��������� ��������� � �������� �����
  /**********************/
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS =  SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI_EDF, &SPI_InitStructure);

  /* ����������� SPI_EDF DMA Tx ������ */
  SPI_I2S_DMACmd(SPI_EDF, SPI_I2S_DMAReq_Tx, DISABLE);
  /* ����������� SPI_EDF DMA Rx ������ */
  SPI_I2S_DMACmd(SPI_EDF, SPI_I2S_DMAReq_Rx, DISABLE);

  //������� ���������, �� �������� ��� ���������� ������/�������� ����� ��� DMA �� ������ DMA_StreamSPI_EDF_Rx � DMA_StreamSPI_EDF_Tx
  DMA_ClearFlag(DMA_StreamSPI_EDF_Rx, DMA_FLAG_TCSPI_EDF_Rx | DMA_FLAG_HTSPI_EDF_Rx | DMA_FLAG_TEISPI_EDF_Rx | DMA_FLAG_DMEISPI_EDF_Rx | DMA_FLAG_FEISPI_EDF_Rx);
  DMA_ClearFlag(DMA_StreamSPI_EDF_Tx, DMA_FLAG_TCSPI_EDF_Tx | DMA_FLAG_HTSPI_EDF_Tx | DMA_FLAG_TEISPI_EDF_Tx | DMA_FLAG_DMEISPI_EDF_Tx | DMA_FLAG_FEISPI_EDF_Tx);

  //���������� ����������� �� ������� �� SPI_EDF
  SPI_I2S_ITConfig(SPI_EDF, SPI_I2S_IT_ERR, ENABLE);

  /* ���������� SPI_EDF */
  SPI_Cmd(SPI_EDF, ENABLE);
  /**********************/

  /**********************/
  //������ �������� ��� ������ � EEPROM
  /**********************/
  comparison_writing &= (unsigned int)(~COMPARISON_WRITING_ENERGY);/*����������, � �� ���������*/
  _SET_BIT(control_spi1_taskes, TASK_START_READ_ENERGY_EEPROM_BIT);
  while(
        (control_spi1_taskes[0]     != 0) ||
        (control_spi1_taskes[1]     != 0) ||
        (state_execution_spi1 > 0)
       )
  {
    //������ � watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //������� ���� ��� ���������� Watchdog �� �����������
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
      control_word_of_watchdog =  0;
    }

    main_routines_for_spi1();
    changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
  }
  /**********************/

  /**********************/
  //������ �������� ��� ��������� � EEPROM
  /**********************/
  comparison_writing &= (unsigned int)(~COMPARISON_WRITING_SETTINGS);/*����������, � �� ���������*/
  _SET_BIT(control_spi1_taskes, TASK_START_READ_SETTINGS_EEPROM_BIT);
  while(
        (control_spi1_taskes[0]     != 0) ||
        (control_spi1_taskes[1]     != 0) ||
        (state_execution_spi1 > 0)
       )
  {
    //������ � watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //������� ���� ��� ���������� Watchdog �� �����������
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
      control_word_of_watchdog =  0;
    }

    main_routines_for_spi1();
    changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
  }
  /**********************/

  /**********************/
  //������ �������� ��� ��������� � EEPROM
  /**********************/
  comparison_writing &= (unsigned int)(~COMPARISON_WRITING_USTUVANNJA);/*����������, � �� ���������*/
  _SET_BIT(control_spi1_taskes, TASK_START_READ_USTUVANNJA_EEPROM_BIT);
  while(
        (control_spi1_taskes[0]     != 0) ||
        (control_spi1_taskes[1]     != 0) ||
        (state_execution_spi1 > 0)
       )
  {
    //������ � watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //������� ���� ��� ���������� Watchdog �� �����������
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
      control_word_of_watchdog =  0;
    }

    main_routines_for_spi1();
    changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
  }
  /**********************/

  /**********************/
  //������ �������� ��� ��� �������� ������ � ������� ���������
  /**********************/
  comparison_writing &= (unsigned int)(~COMPARISON_WRITING_STATE_LEDS_OUTPUTS);/*����������, � �� ���������*/
  _SET_BIT(control_spi1_taskes, TASK_START_READ_STATE_LEDS_OUTPUTS_EEPROM_BIT);
  while(
        (control_spi1_taskes[0]     != 0) ||
        (control_spi1_taskes[1]     != 0) ||
        (state_execution_spi1 > 0)
       )
  {
    //������ � watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //������� ���� ��� ���������� Watchdog �� �����������
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
      control_word_of_watchdog =  0;
    }

    main_routines_for_spi1();
    changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
  }
  /**********************/
  
  /**********************/
  //������ �������� ��� ��� �������� ����������
  /**********************/
  comparison_writing &= (unsigned int)(~COMPARISON_WRITING_TRG_FUNC);/*����������, � �� ���������*/
  _SET_BIT(control_spi1_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT);
  while(
        (control_spi1_taskes[0]     != 0) ||
        (control_spi1_taskes[1]     != 0) ||
        (state_execution_spi1 > 0)
       )
  {
    //������ � watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //������� ���� ��� ���������� Watchdog �� �����������
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
      control_word_of_watchdog =  0;
    }

    main_routines_for_spi1();
    changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
  }
  /**********************/
  
  if((state_spi1_task & STATE_SETTINGS_EEPROM_GOOD) != 0)
  {
    /*
    ������� ��� ������ ����� ����������� ���������� ���� ������������
    ����������� ������� ������, ��� �������� �� ������ ����������� �
    ������������� ������, �� �� ������� ����� ���������� �����, ���� ��������
    ������ ���������� ���������.
    � ������� ��� ��������� ���������� �� ����������� ���������� �� ����
    �������� - ����� ��� ���������� �� ����������� ��������� ���� �������, ����
    �������� ������ ���������� �� ����������
    */
    /**********************/
    //������ �������� ��� ����������� ���������� � EEPROM
    /**********************/
    comparison_writing &= (unsigned int)(~COMPARISON_WRITING_INFO_REJESTRATOR_AR);/*����������, � �� ���������*/
    _SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_AR_EEPROM_BIT);
    while(
          (control_spi1_taskes[0]     != 0) ||
          (control_spi1_taskes[1]     != 0) ||
          (state_execution_spi1 > 0)
         )
    {
      //������ � watchdogs
      if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
      {
        //������� ���� ��� ���������� Watchdog �� �����������
        GPIO_WriteBit(
                      GPIO_EXTERNAL_WATCHDOG,
                      GPIO_PIN_EXTERNAL_WATCHDOG,
                      (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                     );
      control_word_of_watchdog =  0;
      }

      main_routines_for_spi1();
      changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
    }
    /**********************/
  }

  /**********************/
  //������ �������� ��� ����������� ���������� � EEPROM
  /**********************/
  comparison_writing &= (unsigned int)(~COMPARISON_WRITING_INFO_REJESTRATOR_DR);/*����������, � �� ���������*/
  _SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_DR_EEPROM_BIT);
  while(
        (control_spi1_taskes[0]     != 0) ||
        (control_spi1_taskes[1]     != 0) ||
        (state_execution_spi1 > 0)
       )
  {
    //������ � watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //������� ���� ��� ���������� Watchdog �� �����������
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
      control_word_of_watchdog =  0;
    }

    main_routines_for_spi1();
    changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
  }
  /**********************/

  /**********************/
  //������ �������� ��� ���������� ���������� ���� � EEPROM
  /**********************/
  comparison_writing &= (unsigned int)(~COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR);/*����������, � �� ���������*/
  _SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
  while(
        (control_spi1_taskes[0]     != 0) ||
        (control_spi1_taskes[1]     != 0) ||
        (state_execution_spi1 > 0)
       )
  {
    //������ � watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //������� ���� ��� ���������� Watchdog �� �����������
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
      control_word_of_watchdog =  0;
    }

    main_routines_for_spi1();
    changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
  }
  /**********************/

  /**********************/
  //������ �������� ��� ������� ��������
  /**********************/
  comparison_writing &= (unsigned int)(~COMPARISON_WRITING_RESURS);/*����������, � �� ���������*/
  _SET_BIT(control_spi1_taskes, TASK_START_READ_RESURS_EEPROM_BIT);
  while(
        (control_spi1_taskes[0]     != 0) ||
        (control_spi1_taskes[1]     != 0) ||
        (state_execution_spi1 > 0)
       )
  {
    //������ � watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //������� ���� ��� ���������� Watchdog �� �����������
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
      control_word_of_watchdog =  0;
    }

    main_routines_for_spi1();
    changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
  }
  /**********************/
  
  /**********************/
  //������������ TIM2 �� ��������� ���������� ���� 1 �� ��� ������� �������
  /**********************/
  /* ���������� TIM2 */
  /* ---------------------------------------------------------------
  TIM2 ������������: Output Compare Timing Mode:
  TIM2CLK = 30*2 ���, Prescaler = 60, TIM2 counter clock = 1 ���
  CC1 update rate = TIM2 counter clock / CCR1_Val = 1000 Hz
  --------------------------------------------------------------- */
  TIM_TimeBaseStructure.TIM_Period = 0xffffffff;
  TIM_TimeBaseStructure.TIM_Prescaler = (60-1);
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* Output Compare Timing Mode ������������: �����:1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_Pulse = TIM2_CCR1_VAL;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);
  
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);

  /* ���������� ����������� �� ������ 1 ������� 2*/
  TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);
  /**********************/

  /**********************/
  //������������ TIM5 �� ��������� ���������� ���� 0,625 ��
  /**********************/
  /* ���������� TIM5 */
  /* ---------------------------------------------------------------
  TIM5 ������������: Output Compare Timing Mode:
  TIM2CLK = 30*2 ���, Prescaler = 1, TIM5 counter clock = 60 ���
  CC1 update rate = TIM5 counter clock / CCR1_Val = 1600 Hz
  --------------------------------------------------------------- */
  TIM_TimeBaseStructure.TIM_Period = 0xffffffff;
  TIM_TimeBaseStructure.TIM_Prescaler = (1-1);
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

  /* Output Compare Timing Mode ������������: �����:1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_Pulse = step_timer_adc;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIM5, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Disable);

  TIM_OCInitStructure.TIM_Pulse = TIM5_CCR1_2_VAL;
  TIM_OC2Init(TIM5, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Disable);
  
  /* ���������� ����������� �� ������ 1 ������� 5*/
  TIM_ITConfig(TIM5, TIM_IT_CC1, ENABLE);
  /* ���������� ����������� �� ������ 2 ������� 5*/
  TIM_ITConfig(TIM5, TIM_IT_CC2, ENABLE);
  /**********************/

  //������ � watchdogs
  if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
  {
    //������� ���� ��� ���������� Watchdog �� �����������
    GPIO_WriteBit(
                  GPIO_EXTERNAL_WATCHDOG,
                  GPIO_PIN_EXTERNAL_WATCHDOG,
                  (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                 );
    control_word_of_watchdog =  0;
  }

//  /**********************/
//  //����������� USB
//  /**********************/
//  USBD_Init(&USB_OTG_dev,
//#ifdef USE_USB_OTG_HS 
//            USB_OTG_HS_CORE_ID,
//#else            
//            USB_OTG_FS_CORE_ID,
//#endif  
//            &USR_desc, 
//            &USBD_CDC_cb, 
//            &USR_cb);
//  /**********************/

//  //������ � watchdogs
//  if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
//  {
//    //������� ���� ��� ���������� Watchdog �� �����������
//    GPIO_WriteBit(
//                  GPIO_EXTERNAL_WATCHDOG,
//                  GPIO_PIN_EXTERNAL_WATCHDOG,
//                  (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
//                 );
//    control_word_of_watchdog =  0;
//  }
}
/**************************************/

/**************************************/
//̳������� ������������
/**************************************/
void min_settings(__SETTINGS *target_label)
{
  target_label->device_id = VERSIA_PZ;
    
  target_label->type_of_input = 0x0;
  target_label->type_of_input_signal = 0x0;
  
  for(unsigned int i = 0; i < NUMBER_INPUTS; i++)
  {
    target_label->ranguvannja_inputs[N_SMALL*i  ] = 0x0;
    target_label->ranguvannja_inputs[N_SMALL*i+1] = 0x0;
    target_label->ranguvannja_inputs[N_SMALL*i+2] = 0x0;
    
    if ((target_label->type_of_input_signal & (1<<i)) != 0)
    {
      target_label->dopusk_dv[i] = KOEF_DOPUSK_DV_ZMIN_MIN;
      if ((target_label->dopusk_dv[i] % 10) != 0)
      {
        target_label->dopusk_dv[i] = (target_label->dopusk_dv[i] / 10)*10;
      }
    }
    else
      target_label->dopusk_dv[i] = KOEF_DOPUSK_DV_POST_MIN;
  }

  target_label->type_of_output = 0x0;
  target_label->type_of_output_modif = 0x0;
  for(unsigned int i = 0; i < NUMBER_OUTPUTS; i++)
  {
    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_outputs[N_BIG*i+j] = 0x0;
  }

  target_label->type_of_led = 0x0;
  for(unsigned int i = 0; i < NUMBER_LEDS; i++)
  {
    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_leds[N_BIG*i+j] = 0x0;
  }

  for (unsigned int j = 0; j < N_BIG; j++ ) 
  {
    target_label->ranguvannja_analog_registrator[j]  = 0x0;
    target_label->ranguvannja_digital_registrator[j] = 0x0;

    target_label->ranguvannja_off_cb[j] = 0x0;
    target_label->ranguvannja_on_cb[j] = 0x0;
  }
  
  target_label->number_iteration_el = NUMBER_ITERATION_EL_MAX;
//  target_label->number_defined_df = NUMBER_DEFINED_FUNCTIONS_MAX;
//  target_label->number_defined_dt = NUMBER_DEFINED_TRIGGERS_MAX;
//  target_label->number_defined_and = NUMBER_DEFINED_AND_MAX;
//  target_label->number_defined_or = NUMBER_DEFINED_OR_MAX;
//  target_label->number_defined_xor = NUMBER_DEFINED_XOR_MAX;
//  target_label->number_defined_not = NUMBER_DEFINED_NOT_MAX;

  target_label->type_df = 0x0;
  
  for(unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
  {
    target_label->timeout_pause_df[i] = TIMEOUT_DF_PAUSE_MIN;
    target_label->timeout_work_df[i] = TIMEOUT_DF_WORK_MIN;

    for (unsigned int j = 0; j < N_BIG; j++ ) 
    {
      target_label->ranguvannja_df_source_plus[N_BIG*i+j]  = 0x0;
      target_label->ranguvannja_df_source_minus[N_BIG*i+j] = 0x0;
      target_label->ranguvannja_df_source_blk[N_BIG*i+j]   = 0x0;
    }
  }
  
  for(unsigned int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
  {
    for (unsigned int j = 0; j < N_BIG; j++ ) 
    {
      target_label->ranguvannja_set_dt_source_plus[N_BIG*i+j]    = 0x0;
      target_label->ranguvannja_set_dt_source_minus[N_BIG*i+j]   = 0x0;
      target_label->ranguvannja_reset_dt_source_plus[N_BIG*i+j]  = 0x0;
      target_label->ranguvannja_reset_dt_source_minus[N_BIG*i+j] = 0x0;
    }
  }
  
  for(unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
  {
    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_and[N_BIG*i+j] = 0x0;
  }
  
  for(unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
  {
    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_or[N_BIG*i+j] = 0x0;
  }
  
  for(unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
  {
    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_xor[N_BIG*i+j] = 0x0;
  }
  
  for(unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
  {
    for (unsigned int j = 0; j < N_BIG; j++ ) target_label->ranguvannja_d_not[N_BIG*i+j] = 0x0;
  }
  
  for(unsigned int i = 0; i < NUMBER_TRANSFER_FUNCTIONS; i++) target_label->ranguvannja_tf[i] = 0x0;
  
  target_label->buttons_mode = 0;
  for(unsigned int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
  {
    target_label->ranguvannja_buttons[N_SMALL*i  ] = 0x0;
    target_label->ranguvannja_buttons[N_SMALL*i+1] = 0x0;
    target_label->ranguvannja_buttons[N_SMALL*i+2] = 0x0;
  }

  target_label->configuration = 0;
  
  target_label->ctrl_zdz_type = ZDZ_CTRL_MIN;
#if (                                   \
     (MODYFIKACIA_VERSII_PZ == 0) ||    \
     (MODYFIKACIA_VERSII_PZ == 3)       \
    )   
  target_label->zdz_ovd_porig = 0;
#endif
  for (size_t i = 0; i < NUMBER_UP; i++) target_label->ctrl_UP_input[i] = UP_CTRL_Ia_Ib_Ic;

  target_label->control_dz = 0;
  target_label->control_mtz = 0;
  target_label->control_zdz = 0;
  target_label->control_zz = 0;
  target_label->control_tznp = 0;
  target_label->control_apv = 0;
  target_label->control_achr_chapv = 0;
  target_label->control_urov = 0;
  target_label->control_zop = 0;
  target_label->control_Umin = 0;
  target_label->control_Umax = 0;
  target_label->control_UP = 0;
  
  target_label->grupa_ustavok = SETPOINT_GRUPA_USTAVOK_MIN;
  
  target_label->type_mtz1 = TYPE_MTZ_SIMPLE;
  target_label->type_mtz2 = TYPE_MTZ_SIMPLE;
  target_label->type_mtz3 = TYPE_MTZ_SIMPLE;
  target_label->type_mtz4 = TYPE_MTZ_SIMPLE;
  
  for (unsigned int i = 0; i < NUMBER_GROUP_USTAVOK; i++)
  {
    int angle;
    float angle_f;
    
    //��
    target_label->pickup_dz_k[i] = PICKUP_DZ_K_MIN;
    
    target_label->pickup_dz1[i] = PICKUP_DZ1_MIN;
    target_label->pickup_dz1_amtz[i] = PICKUP_DZ1_AMTZ_MIN;

    target_label->timeout_dz1[i] = TIMEOUT_DZ1_MIN;
    target_label->timeout_dz1_amtz[i] = TIMEOUT_DZ1_AMTZ_MIN;
    
    angle = PICKUP_DZ2_ANGLE_MIN;
    angle_f = (float)angle;
    target_label->pickup_dz2_angle[i] = angle;
    target_label->pickup_dz2_angle_cos1[i] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*angle_f/180.0f)));
    target_label->pickup_dz2_angle_sin1[i] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*angle_f/180.0f)));
    target_label->pickup_dz2_angle_cos2[i] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*(angle_f - DELTA_SECTOR_DZ)/180.0f)));
    target_label->pickup_dz2_angle_sin2[i] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*(angle_f - DELTA_SECTOR_DZ)/180.0f)));
    
    target_label->pickup_dz2_dir[i] = PICKUP_DZ2_DIR_MIN;
    target_label->pickup_dz2_inv[i] = PICKUP_DZ2_INV_MIN;
    target_label->pickup_dz2_amtz[i] = PICKUP_DZ2_AMTZ_MIN;
    
    target_label->timeout_dz2_dir[i] = TIMEOUT_DZ2_DIR_MIN;
    target_label->timeout_dz2_dir_pr[i] = TIMEOUT_DZ2_DIR_PR_MIN;
    target_label->timeout_dz2_inv[i] = TIMEOUT_DZ2_INV_MIN;
    target_label->timeout_dz2_inv_pr[i] = TIMEOUT_DZ2_INV_PR_MIN;
    target_label->timeout_dz2_amtz[i] = TIMEOUT_DZ2_AMTZ_MIN;
    target_label->timeout_dz2_amtz_pr[i] = TIMEOUT_DZ2_AMTZ_PR_MIN;
    target_label->timeout_dz2_vvid_pr[i] = TIMEOUT_DZ2_VVID_PR_MIN;
    target_label->timeout_dz2_amtz_vvid_pr[i] = TIMEOUT_DZ2_AMTZ_VVID_PR_MIN;
    
    angle = PICKUP_DZ3_ANGLE_MIN;
    angle_f = (float)angle;
    target_label->pickup_dz3_angle[i] = angle;
    target_label->pickup_dz3_angle_cos1[i] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*angle_f/180.0f)));
    target_label->pickup_dz3_angle_sin1[i] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*angle_f/180.0f)));
    target_label->pickup_dz3_angle_cos2[i] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*(angle_f - DELTA_SECTOR_DZ)/180.0f)));
    target_label->pickup_dz3_angle_sin2[i] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*(angle_f - DELTA_SECTOR_DZ)/180.0f)));
    
    target_label->pickup_dz3_dir[i] = PICKUP_DZ3_DIR_MIN;
    target_label->pickup_dz3_inv[i] = PICKUP_DZ3_INV_MIN;
    target_label->pickup_dz3_amtz[i] = PICKUP_DZ3_AMTZ_MIN;
    
    target_label->timeout_dz3_dir[i] = TIMEOUT_DZ3_DIR_MIN;
    target_label->timeout_dz3_dir_pr[i] = TIMEOUT_DZ3_DIR_PR_MIN;
    target_label->timeout_dz3_inv[i] = TIMEOUT_DZ3_INV_MIN;
    target_label->timeout_dz3_inv_pr[i] = TIMEOUT_DZ3_INV_PR_MIN;
    target_label->timeout_dz3_amtz[i] = TIMEOUT_DZ3_AMTZ_MIN;
    target_label->timeout_dz3_amtz_pr[i] = TIMEOUT_DZ3_AMTZ_PR_MIN;
    target_label->timeout_dz3_vvid_pr[i] = TIMEOUT_DZ3_VVID_PR_MIN;
    target_label->timeout_dz3_amtz_vvid_pr[i] = TIMEOUT_DZ3_AMTZ_VVID_PR_MIN;

    angle = PICKUP_DZ4_ANGLE_MIN;
    angle_f = (float)angle;
    target_label->pickup_dz4_angle[i] = angle;
    target_label->pickup_dz4_angle_cos1[i] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*angle_f/180.0f)));
    target_label->pickup_dz4_angle_sin1[i] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*angle_f/180.0f)));
    target_label->pickup_dz4_angle_cos2[i] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*(angle_f - DELTA_SECTOR_DZ)/180.0f)));
    target_label->pickup_dz4_angle_sin2[i] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*(angle_f - DELTA_SECTOR_DZ)/180.0f)));
    
    target_label->pickup_dz4_dir[i] = PICKUP_DZ4_DIR_MIN;
    target_label->pickup_dz4_inv[i] = PICKUP_DZ4_INV_MIN;
    target_label->pickup_dz4_amtz[i] = PICKUP_DZ4_AMTZ_MIN;

    target_label->timeout_dz4_dir[i] = TIMEOUT_DZ4_DIR_MIN;
    target_label->timeout_dz4_dir_pr[i] = TIMEOUT_DZ4_DIR_PR_MIN;
    target_label->timeout_dz4_inv[i] = TIMEOUT_DZ4_INV_MIN;
    target_label->timeout_dz4_inv_pr[i] = TIMEOUT_DZ4_INV_PR_MIN;
    target_label->timeout_dz4_amtz[i] = TIMEOUT_DZ4_AMTZ_MIN;
    target_label->timeout_dz4_amtz_pr[i] = TIMEOUT_DZ4_AMTZ_PR_MIN;
    target_label->timeout_dz4_vvid_pr[i] = TIMEOUT_DZ4_VVID_PR_MIN;
    target_label->timeout_dz4_amtz_vvid_pr[i] = TIMEOUT_DZ4_AMTZ_VVID_PR_MIN;
    
    target_label->timeout_nkn_dz[i] = TIMEOUT_NKN_DZ_MIN;
    
    //���
    target_label->setpoint_mtz_1[i] = SETPOINT_MTZ1_MIN;
    target_label->setpoint_mtz_1_n_vpered[i] = SETPOINT_MTZ1_N_VPERED_MIN;
    target_label->setpoint_mtz_1_n_nazad[i] = SETPOINT_MTZ1_N_NAZAD_MIN;
    
    angle = SETPOINT_MTZ1_ANGLE_MIN;
    angle_f = (float)angle;
    target_label->setpoint_mtz_1_angle[i] = angle;
    target_label->setpoint_mtz_1_angle_cos[i] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*angle_f/180.0f)));
    target_label->setpoint_mtz_1_angle_sin[i] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*angle_f/180.0f)));
    
    target_label->setpoint_mtz_1_po_napruzi[i] = SETPOINT_MTZ1_PO_NAPRUZI_MIN;
    target_label->setpoint_mtz_1_U[i] = SETPOINT_MTZ1_U_MIN;

    target_label->setpoint_mtz_2[i] = SETPOINT_MTZ2_MIN;
    target_label->setpoint_mtz_2_n_vpered[i] = SETPOINT_MTZ2_N_VPERED_MIN;
    target_label->setpoint_mtz_2_n_nazad[i] = SETPOINT_MTZ2_N_NAZAD_MIN;
    
    angle = SETPOINT_MTZ2_ANGLE_MIN;
    angle_f = (float)angle;
    target_label->setpoint_mtz_2_angle[i] = angle;
    target_label->setpoint_mtz_2_angle_cos[i] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*angle_f/180.0f)));
    target_label->setpoint_mtz_2_angle_sin[i] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*angle_f/180.0f)));
    
    target_label->setpoint_mtz_2_po_napruzi[i] = SETPOINT_MTZ2_PO_NAPRUZI_MIN;
    target_label->setpoint_mtz_2_U[i] = SETPOINT_MTZ2_U_MIN;

    target_label->setpoint_mtz_3[i] = SETPOINT_MTZ3_MIN;
    target_label->setpoint_mtz_3_n_vpered[i] = SETPOINT_MTZ3_N_VPERED_MIN;
    target_label->setpoint_mtz_3_n_nazad[i] = SETPOINT_MTZ3_N_NAZAD_MIN;
    
    angle = SETPOINT_MTZ3_ANGLE_MIN;
    angle_f = (float)angle;
    target_label->setpoint_mtz_3_angle[i] = angle;
    target_label->setpoint_mtz_3_angle_cos[i] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*angle_f/180.0f)));
    target_label->setpoint_mtz_3_angle_sin[i] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*angle_f/180.0f)));
    
    target_label->setpoint_mtz_3_po_napruzi[i] = SETPOINT_MTZ3_PO_NAPRUZI_MIN;
    target_label->setpoint_mtz_3_U[i] = SETPOINT_MTZ3_U_MIN;

    target_label->setpoint_mtz_4[i] = SETPOINT_MTZ4_MIN;
    target_label->setpoint_mtz_4_n_vpered[i] = SETPOINT_MTZ4_N_VPERED_MIN;
    target_label->setpoint_mtz_4_n_nazad[i] = SETPOINT_MTZ4_N_NAZAD_MIN;
    
    angle = SETPOINT_MTZ4_ANGLE_MIN;
    angle_f = (float)angle;
    target_label->setpoint_mtz_4_angle[i] = angle;
    target_label->setpoint_mtz_4_angle_cos[i] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*angle_f/180.0f)));
    target_label->setpoint_mtz_4_angle_sin[i] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*angle_f/180.0f)));
    
    target_label->setpoint_mtz_4_po_napruzi[i] = SETPOINT_MTZ4_PO_NAPRUZI_MIN;
    target_label->setpoint_mtz_4_U[i] = SETPOINT_MTZ4_U_MIN;
    
    target_label->timeout_mtz_1[i] = TIMEOUT_MTZ1_MIN; 
    target_label->timeout_mtz_1_n_vpered[i] = TIMEOUT_MTZ1_N_VPERED_MIN; 
    target_label->timeout_mtz_1_n_nazad[i] = TIMEOUT_MTZ1_N_NAZAD_MIN; 
    target_label->timeout_mtz_1_po_napruzi[i] = TIMEOUT_MTZ1_PO_NAPRUZI_MIN; 

    target_label->timeout_mtz_2[i] = TIMEOUT_MTZ2_MIN; 
    target_label->timeout_mtz_2_pr[i] = TIMEOUT_MTZ2_PR_MIN; 
    target_label->timeout_mtz_2_n_vpered[i] = TIMEOUT_MTZ2_N_VPERED_MIN; 
    target_label->timeout_mtz_2_n_vpered_pr[i] = TIMEOUT_MTZ2_N_VPERED_PR_MIN; 
    target_label->timeout_mtz_2_n_nazad[i] = TIMEOUT_MTZ2_N_NAZAD_MIN; 
    target_label->timeout_mtz_2_n_nazad_pr[i] = TIMEOUT_MTZ2_N_NAZAD_PR_MIN; 
    target_label->timeout_mtz_2_po_napruzi[i] = TIMEOUT_MTZ2_PO_NAPRUZI_MIN; 
    target_label->timeout_mtz_2_po_napruzi_pr[i] = TIMEOUT_MTZ2_PO_NAPRUZI_PR_MIN; 
    target_label->timeout_mtz_2_vvid_pr[i] = TIMEOUT_MTZ2_VVID_PR_MIN;

    target_label->timeout_mtz_3[i] = TIMEOUT_MTZ3_MIN; 
    target_label->timeout_mtz_3_n_vpered[i] = TIMEOUT_MTZ3_N_VPERED_MIN; 
    target_label->timeout_mtz_3_n_nazad[i] = TIMEOUT_MTZ3_N_NAZAD_MIN; 
    target_label->timeout_mtz_3_po_napruzi[i] = TIMEOUT_MTZ3_PO_NAPRUZI_MIN; 

    target_label->timeout_mtz_4[i] = TIMEOUT_MTZ4_MIN; 
    target_label->timeout_mtz_4_n_vpered[i] = TIMEOUT_MTZ4_N_VPERED_MIN; 
    target_label->timeout_mtz_4_n_nazad[i] = TIMEOUT_MTZ4_N_NAZAD_MIN; 
    target_label->timeout_mtz_4_po_napruzi[i] = TIMEOUT_MTZ4_PO_NAPRUZI_MIN; 

    target_label->timeout_zdz[i] = TIMEOUT_ZDZ_MIN;    

    target_label->setpoint_zz_3I0[i] = SETPOINT_ZZ_3I0_MIN;
    target_label->setpoint_zz_3U0[i] = SETPOINT_ZZ_3U0_MIN;
    target_label->timeout_zz_3I0[i]  = TIMEOUT_ZZ_3I0_MIN; 
    target_label->timeout_zz_3U0[i]  = TIMEOUT_ZZ_3U0_MIN; 
    target_label->timeout_nzz[i]     = TIMEOUT_NZZ_MIN; 

    target_label->setpoint_tznp_1_3I0_vpered[i] = SETPOINT_TZNP1_3I0_VPERED_MIN;
    target_label->setpoint_tznp_1_3U0_vpered[i] = SETPOINT_TZNP1_3U0_VPERED_MIN;
    target_label->setpoint_tznp_1_3I0_nazad[i] = SETPOINT_TZNP1_3I0_NAZAD_MIN;
    target_label->setpoint_tznp_1_3U0_nazad[i] = SETPOINT_TZNP1_3U0_NAZAD_MIN;
    
    angle = SETPOINT_TZNP1_ANGLE_MIN;
    angle_f = (float)angle;
    target_label->setpoint_tznp_1_angle[i] = angle;
    target_label->setpoint_tznp_1_angle_cos[i] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*angle_f/180.0f)));
    target_label->setpoint_tznp_1_angle_sin[i] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*angle_f/180.0f)));

    target_label->setpoint_tznp_2_3I0_vpered[i] = SETPOINT_TZNP2_3I0_VPERED_MIN;
    target_label->setpoint_tznp_2_3U0_vpered[i] = SETPOINT_TZNP2_3U0_VPERED_MIN;
    target_label->setpoint_tznp_2_3I0_nazad[i] = SETPOINT_TZNP2_3I0_NAZAD_MIN;
    target_label->setpoint_tznp_2_3U0_nazad[i] = SETPOINT_TZNP2_3U0_NAZAD_MIN;
    
    angle = SETPOINT_TZNP2_ANGLE_MIN;
    angle_f = (float)angle;
    target_label->setpoint_tznp_2_angle[i] = angle;
    target_label->setpoint_tznp_2_angle_cos[i] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*angle_f/180.0f)));
    target_label->setpoint_tznp_2_angle_sin[i] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*angle_f/180.0f)));

    target_label->setpoint_tznp_3_3I0_vpered[i] = SETPOINT_TZNP3_3I0_VPERED_MIN;
    target_label->setpoint_tznp_3_3U0_vpered[i] = SETPOINT_TZNP3_3U0_VPERED_MIN;
    target_label->setpoint_tznp_3_3I0_nazad[i] = SETPOINT_TZNP3_3I0_NAZAD_MIN;
    target_label->setpoint_tznp_3_3U0_nazad[i] = SETPOINT_TZNP3_3U0_NAZAD_MIN;
    
    angle = SETPOINT_TZNP3_ANGLE_MIN;
    angle_f = (float)angle;
    target_label->setpoint_tznp_3_angle[i] = angle;
    target_label->setpoint_tznp_3_angle_cos[i] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*angle_f/180.0f)));
    target_label->setpoint_tznp_3_angle_sin[i] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*angle_f/180.0f)));

    target_label->timeout_tznp_1_vpered[i] = TIMEOUT_TZNP1_VPERED_MIN; 
    target_label->timeout_tznp_1_nazad[i] = TIMEOUT_TZNP1_NAZAD_MIN; 
    target_label->timeout_tznp_2_vpered[i] = TIMEOUT_TZNP2_VPERED_MIN; 
    target_label->timeout_tznp_2_nazad[i] = TIMEOUT_TZNP2_NAZAD_MIN; 
    target_label->timeout_tznp_3_vpered[i] = TIMEOUT_TZNP3_VPERED_MIN; 
    target_label->timeout_tznp_3_nazad[i] = TIMEOUT_TZNP3_NAZAD_MIN; 
    
    target_label->timeout_apv_1[i] = TIMEOUT_APV1_MIN;    
    target_label->timeout_apv_2[i] = TIMEOUT_APV2_MIN;    
    target_label->timeout_apv_3[i] = TIMEOUT_APV3_MIN;    
    target_label->timeout_apv_4[i] = TIMEOUT_APV4_MIN;    
    target_label->timeout_apv_block_vid_apv1[i] = TIMEOUT_APV_BLOCK_VID_APV1_MIN;
    target_label->timeout_apv_block_vid_apv2[i] = TIMEOUT_APV_BLOCK_VID_APV2_MIN;
    target_label->timeout_apv_block_vid_apv3[i] = TIMEOUT_APV_BLOCK_VID_APV3_MIN;
    target_label->timeout_apv_block_vid_apv4[i] = TIMEOUT_APV_BLOCK_VID_APV4_MIN;
    target_label->timeout_apv_block_vid_VV[i] = TIMEOUT_APV_BLOCK_VID_VV_MIN;
    
    target_label->setpoint_achr_chapv_uf[i] = SETPOINT_ACHR_CHAPV_UF_MIN;
    target_label->setpoint_achr1_f_rab[i]  = SETPOINT_ACHR1_F_RAB_MIN;
    target_label->setpoint_chapv1_f_rab[i] = MAIN_FREQUENCY*100 - 30;
    target_label->setpoint_achr2_f_rab[i]  = SETPOINT_ACHR2_F_RAB_MIN;
    target_label->setpoint_chapv2_f_rab[i] = MAIN_FREQUENCY*100 - 30;
    
    target_label->timeout_achr_1[i] = TIMEOUT_ACHR1_MIN;
    target_label->timeout_chapv_1[i] = TIMEOUT_CHAPV1_MIN;
    target_label->timeout_achr_2[i] = TIMEOUT_ACHR2_MIN;
    target_label->timeout_chapv_2[i] = TIMEOUT_CHAPV2_MIN;
    
    target_label->setpoint_urov[i]  = SETPOINT_UROV_MIN;
    target_label->timeout_urov_1[i] = TIMEOUT_UROV1_MIN;
    target_label->timeout_urov_2[i] = TIMEOUT_UROV2_MIN;

    target_label->setpoint_zop[i] = SETPOINT_ZOP_MIN;
    target_label->timeout_zop[i] = TIMEOUT_ZOP_MIN; 

    target_label->setpoint_Umin1[i] = SETPOINT_UMIN1_MIN;
    target_label->setpoint_Umin1_Iblk[i] = SETPOINT_UMIN1_IBLK_MIN;
    target_label->setpoint_Umin2[i] = SETPOINT_UMIN2_MIN;
    target_label->setpoint_Umin2_Iblk[i] = SETPOINT_UMIN2_IBLK_MIN;
    target_label->timeout_Umin1[i] = TIMEOUT_UMIN1_MIN; 
    target_label->timeout_Umin2[i] = TIMEOUT_UMIN2_MIN;
    
    target_label->setpoint_Umax1[i] = SETPOINT_UMAX1_MIN;
    target_label->setpoint_Umax2[i] = SETPOINT_UMAX2_MIN;
    target_label->setpoint_kp_Umax[i] = SETPOINT_KP_UMAX_DEFAULT;
    target_label->timeout_Umax1[i] = TIMEOUT_UMAX1_MIN;
    target_label->timeout_Umax2[i] = TIMEOUT_UMAX2_MIN;
    
    for (size_t j = 0; j < NUMBER_UP; j++ )
    {
      def_pickup_timeout_UP(target_label, j, i);
    }
  }

  target_label->setpoint_Inom = SETPOINT_Inom_MIN;
  target_label->setpoint_r_kom_st_Inom = SETPOINT_RKS_Inom_MIN;
  target_label->setpoint_Inom_vymk = SETPOINT_Inom_vymk_MIN;
  target_label->setpoint_r_kom_st_Inom_vymk = SETPOINT_RKS_Inom_vymk_MIN;
  
  unsigned int chastka = target_label->setpoint_r_kom_st_Inom/target_label->setpoint_r_kom_st_Inom_vymk;
  target_label->setpoint_pochatkovyj_resurs = 2*chastka;
  target_label->setpoint_krytychnyj_resurs = chastka;
  target_label->setpoint_pochatkova_k_vymk = 0;
  
  target_label->timeout_swch_on = TIMEOUT_SWCH_ON_MIN;
  target_label->timeout_swch_off = TIMEOUT_SWCH_OFF_MIN;
  target_label->timeout_swch_udl_blk_on = TIMEOUT_SWCH_UDL_BLK_ON_MIN;
  target_label->timeout_pryvoda_VV = TIMEOUT_PRYVODA_VV_MIN;
  target_label->control_switch = 0;
  
  for (unsigned int i = 0; i < 2; i++)
  {
    if (i == 0) target_label->lines[0] = NUMBER_LINES_FORWARD_MIN;
    else target_label->lines[i] = NUMBER_LINES_BACKWARD_MIN;
    
    for (unsigned int j = 0; j < MAX_NUMBER_LINES_VMP; j++)
    {
      target_label->dovgyna[i][j] = SETPOINT_DOVGYNA_VMP_MIN;
      target_label->opir[i][j]    = SETPOINT_OPIR_VMP_MIN;
    }
  }
  target_label->control_vmp = 0;
  
  target_label->prefault_number_periods = TIMEOUT_PREFAULT_MIN / 20;
  target_label->postfault_number_periods = TIMEOUT_POSTFAULT_MIN / 20;

  target_label->password1 = 0;
  target_label->password2 = 1234;
  target_label->timeout_deactivation_password_interface_USB = TIMEOUT_DEACTIVATION_PASSWORD_MIN;
  target_label->password_interface_USB = 0;
  target_label->timeout_deactivation_password_interface_RS485 = TIMEOUT_DEACTIVATION_PASSWORD_MIN;
  target_label->password_interface_RS485 = 0;
  
  target_label->timeout_idle_new_settings = TIMEOUT_NEW_SETTINGS_MIN;
  
  target_label->T0 = KOEF_TO_MIN;
  target_label->TCurrent = KOEF_TT_MIN;
  target_label->TVoltage = KOEF_TN_MIN;
  target_label->control_transformator = MASKA_FOR_BIT(INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE);

  for(unsigned int i=0; i< ((M_ADDRESS_LAST_USER_REGISTER_DATA - M_ADDRESS_FIRST_USER_REGISTER_DATA) + 1); i++) target_label->user_register[i] = 0;

  for(unsigned int i=0; i<MAX_CHAR_IN_NAME_OF_CELL; i++) target_label->name_of_cell[i] = ' ';
  target_label->name_of_cell[4 ] = '�';
  target_label->name_of_cell[5 ] = '�';
  target_label->name_of_cell[6 ] = '�';
  target_label->name_of_cell[8 ] = '�';
  target_label->name_of_cell[9 ] = '�';
  target_label->name_of_cell[10] = '�';
  target_label->name_of_cell[11] = '�';
  target_label->name_of_cell[12] = '�';
  
  target_label->address = KOEF_ADDRESS_MIN;
  target_label->speed_RS485 = VALUE_SPEED_INTERFACE_MIN;
  target_label->pare_bit_RS485 = VALUE_PARE_INTERFACE_MAX; //������ ���������� �������� ������� �� ���� � EVEN - � �� ����� ������� VALUE_PARE_INTERFACE_MAX
  target_label->number_stop_bit_RS485 = VALUE_STOP_BITS_INTERFACE_MIN;
  target_label->time_out_1_RS485 = VALUE_TIME_OUT_1_INTERFACE_MIN;
  
  target_label->language = LANGUAGE_EN;
  
  target_label->control_extra_settings_1 = 0;

  for(unsigned int i = 0; i < (7+1); i++)
  {
    target_label->time_setpoints[i] = 0;
    target_label->time_ranguvannja[i] = 0;
  }
}
/**************************************/

/**************************************/
//�������� ����������� ��� ��, �� ��������� �� ������ ������
/**************************************/
void error_reading_with_eeprom()
{
  const unsigned char string_info[MAX_NAMBER_LANGUAGE][4][MAX_COL_LCD] = 
  {
    {
      "  �������� ���  ",
      " ��.�.�.�����.  ",
      "  ����.���.���  ",
      "��.�.�.����.���."
    },
    {
      "����������� ����",
      " ���.�.�.�����. ",
      " ���.���.����  ",
      "���.�.�.���.���"
    },
    {
      "Param are absent",
      "Error Param chks",
      "F-F info.are abs",
      "Er.F-F info.chks"
    },
    {
      "  �������� ���  ",
      " ��.�.�.�����.  ",
      "  ����.���.���  ",
      "��.�.�.����.���."
    } 
  };
  const unsigned char string_action[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] =
  {
    {
      "���.�����.:Enter",
      " ��������: Enter"
    },
    {
      "̳�.�����.:Enter",
      " �������: Enter "
    },
    {
      "Min.param :Enter",
      "  Reset: Enter  "
    },
    {
      "���.�����.:Enter",
      " ��������: Enter"
    }
  };
  
  int index_language;
  if ((state_spi1_task & STATE_SETTINGS_EEPROM_GOOD) == 0) index_language = index_language_in_array(LANGUAGE_ABSENT);
  else index_language = index_language_in_array(current_settings.language);

  if (
      ((state_spi1_task & (STATE_SETTINGS_EEPROM_EMPTY | STATE_SETTINGS_EEPROM_FAIL) ) != 0) ||
      ((state_spi1_task & (STATE_TRG_FUNC_EEPROM_EMPTY | STATE_TRG_FUNC_EEPROM_FAIL) ) != 0)
     )   
  {
    //������ � watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //������� ���� ��� ���������� Watchdog �� �����������
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
      control_word_of_watchdog =  0;
    }
    
    unsigned int index_info, index_action, information_type;
    if((state_spi1_task & STATE_SETTINGS_EEPROM_EMPTY) != 0)
    {
      index_info = 0;
      index_action = 0;
      information_type = 1;
    }
    else if((state_spi1_task & STATE_SETTINGS_EEPROM_FAIL) != 0)
    {
      index_info = 1;
      index_action = 0;
      information_type = 1;
    }
    else if((state_spi1_task & STATE_TRG_FUNC_EEPROM_EMPTY) != 0)
    {
      index_info = 2;
      index_action = 1;
      information_type = 2;
    }
    else if((state_spi1_task & STATE_TRG_FUNC_EEPROM_FAIL) != 0)
    {
      index_info = 3;
      index_action = 1;
      information_type = 2;
    }

    //�������  ����� � ������� �����
    for (unsigned int i=0; i< MAX_ROW_LCD; i++)
    {
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) 
      {
        if (i == 0) working_ekran[i][j] = string_info[index_language][index_info][j];
        else if (i == 1) working_ekran[i][j] = string_action[index_language][index_action][j];
        else working_ekran[i][j] = ' ';
      }
    }
  
    //�������� ������� ���� �����
    current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;

    //���������� ���������� �� �����
    view_whole_ekran();
    
    //������ ���� �� ���� ��������� ������ ENTER
    while ((new_state_keyboard & (1<<BIT_KEY_ENTER)) ==0)
    {
      //������ � watchdogs
      if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
      {
        //������� ���� ��� ���������� Watchdog �� �����������
        GPIO_WriteBit(
                      GPIO_EXTERNAL_WATCHDOG,
                      GPIO_PIN_EXTERNAL_WATCHDOG,
                      (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                     );
      control_word_of_watchdog =  0;
      }
    }

    new_state_keyboard = 0;
    
    if (information_type == 1)
    {
      //�������, �� ������� ����� ���� �������� � �� ����� ���� � ������� ������� ��������� � ������� � ���� ������ ������� �������
      changed_settings = CHANGED_ETAP_EXECUTION;
      //���������� �������� ������������
      min_settings(&current_settings);
      current_settings_interfaces = current_settings;
      
      //�������� �������� ������������
      _SET_BIT(control_spi1_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT);

      //�������, �� ������� �������� � �� ����� ���� � ������� ������� ��������� � ������� � ���� ������ ������� �������
      changed_settings = CHANGED_ETAP_ENDED;
    }
    else if (information_type == 2)
    {
      fix_active_buttons = 0;
      for (unsigned int i = 0; i < N_BIG; i++) trigger_active_functions[i] = 0x0;

      //�������� ������� ������� ����������
      _SET_BIT(control_spi1_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT);
    }
    
    //������ ���������� ������
    while(
          (control_spi1_taskes[0]     != 0) ||
          (control_spi1_taskes[1]     != 0) ||
          (state_execution_spi1 > 0)
         )
    {
      //������ � watchdogs
      if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
      {
        //������� ���� ��� ���������� Watchdog �� �����������
        GPIO_WriteBit(
                      GPIO_EXTERNAL_WATCHDOG,
                      GPIO_PIN_EXTERNAL_WATCHDOG,
                      (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                     );
      control_word_of_watchdog =  0;
      }

      main_routines_for_spi1();
      changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
      //������� �� ����� ����������� ������� �� ���������, �� �� �������� ����� ������ ���
    }

    if (information_type == 1)
    {
      //��������� ������� ������������
      comparison_writing &= (unsigned int)(~COMPARISON_WRITING_SETTINGS);/*����������, � �� ���������*/
      _SET_BIT(control_spi1_taskes, TASK_START_READ_SETTINGS_EEPROM_BIT);
    }
    else if (information_type == 2)
    {
      //��������� ������� ������� ����������
      comparison_writing &= (unsigned int)(~COMPARISON_WRITING_TRG_FUNC);/*����������, � �� ���������*/
      _SET_BIT(control_spi1_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT);
    }

    //������ ���������� �������
    while(
          (control_spi1_taskes[0]     != 0) ||
          (control_spi1_taskes[1]     != 0) ||
          (state_execution_spi1 > 0)
         )
    {
      //������ � watchdogs
      if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
      {
        //������� ���� ��� ���������� Watchdog �� �����������
        GPIO_WriteBit(
                      GPIO_EXTERNAL_WATCHDOG,
                      GPIO_PIN_EXTERNAL_WATCHDOG,
                      (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                     );
      control_word_of_watchdog =  0;
      }
      
      main_routines_for_spi1();
      changing_diagnostyka_state();//ϳ����������� ����� ���������� �������� ����� ��� ���������� ���������� ����
      //������� �� ����� ����������� ������� �� ���������, �� �� �������� ����� ������ ���
    }
  }
}  
/**************************************/

/**************************************/
//�������� �������� (� ��� ����������� ������������� �� ������ ���������) DataFlash
/**************************************/
void start_checking_dataflash(void)
{
  //������ ������� ��������� 1
  unsigned char page_size_256, page_size_256_total = 1;
  unsigned int ready_busy;
  number_chip_dataflsh_exchange = INDEX_DATAFLASH_1;
  
  for (unsigned int i = 0; i < NUMBER_DATAFLASH_CHIP; i++)
  {
    page_size_256 = 1;
    dataflash_status_read(number_chip_dataflsh_exchange);
    while (driver_spi_df[number_chip_dataflsh_exchange].state_execution != TRANSACTION_EXECUTED_WAIT_ANALIZE)
    {
      if (driver_spi_df[number_chip_dataflsh_exchange].state_execution == TRANSACTION_EXECUTING_NONE)
      {
        /*
        �� �������� ����� ��������� ����� � ������ ������� - ���� � ������ ������/��������
        ���������� ���� ������� � SPI_EDF, ���� �������� �������� ������ ������� ������� �������
        */
        dataflash_status_read(number_chip_dataflsh_exchange);
      }
      
      //������ � watchdogs
      if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
      {
        //������� ���� ��� ���������� Watchdog �� �����������
        GPIO_WriteBit(
                      GPIO_EXTERNAL_WATCHDOG,
                      GPIO_PIN_EXTERNAL_WATCHDOG,
                      (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                     );
      control_word_of_watchdog =  0;
      }
    }
    page_size_256 &= RxBuffer_SPI_EDF[1] & (1<< 0); 
    ready_busy = RxBuffer_SPI_EDF[1] & (1<< 7);
    driver_spi_df[number_chip_dataflsh_exchange].state_execution = TRANSACTION_EXECUTING_NONE;
    driver_spi_df[number_chip_dataflsh_exchange].code_operation = CODE_OPERATION_NONE;
    if (page_size_256 == 0)
    {
      //����� ������ ������� �� ������ ��������� � ������� ������� 256 ����
      
      //����������, �� ��������� ����� � ������ �� ��� Ready/Busy
      while (ready_busy == 0)/*������ ��� �� ready/busy ������ � ���������� �������� ������� ������� �������*/
      {
        dataflash_status_read(number_chip_dataflsh_exchange);
        while (driver_spi_df[number_chip_dataflsh_exchange].state_execution != TRANSACTION_EXECUTED_WAIT_ANALIZE)
        {
          if (driver_spi_df[number_chip_dataflsh_exchange].state_execution == TRANSACTION_EXECUTING_NONE)
          {
            /*
            �� �������� ����� ��������� ����� � ������ ������� - ���� � ������ ������/��������
            ���������� ���� ������� � SPI_EDF, ���� �������� �������� ������ ������� ������� �������
            */
            dataflash_status_read(number_chip_dataflsh_exchange);
          }
          
          //������ � watchdogs
          if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
          {
            //������� ���� ��� ���������� Watchdog �� �����������
            GPIO_WriteBit(
                          GPIO_EXTERNAL_WATCHDOG,
                          GPIO_PIN_EXTERNAL_WATCHDOG,
                          (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                         );
            control_word_of_watchdog =  0;
          }
        }
        ready_busy = RxBuffer_SPI_EDF[1] & (1<< 7);
        driver_spi_df[number_chip_dataflsh_exchange].state_execution = TRANSACTION_EXECUTING_NONE;
        driver_spi_df[number_chip_dataflsh_exchange].code_operation = CODE_OPERATION_NONE;
      }
      
      //������ ������� �� ���������������� DataFlash
      dataflash_set_pagesize_256(number_chip_dataflsh_exchange);
      while (driver_spi_df[number_chip_dataflsh_exchange].state_execution != TRANSACTION_EXECUTED_WAIT_ANALIZE)
      {
        /*
        ��� � ������ �� ���������� ������� ����, �� ���� ��������� ���� ��������
        ����� ���� ����� ���� � �������� ������ (������� ������ ������ �� ���� �� �����), 
        ���� � ������ ������� ��������� �����, �� ���� �� �� ���������� �� ������� ������ �������
        */
        
        //������ � watchdogs
        if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
        {
          //������� ���� ��� ���������� Watchdog �� �����������
          GPIO_WriteBit(
                        GPIO_EXTERNAL_WATCHDOG,
                        GPIO_PIN_EXTERNAL_WATCHDOG,
                        (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                       );
          control_word_of_watchdog =  0;
        }
      }
      driver_spi_df[number_chip_dataflsh_exchange].state_execution = TRANSACTION_EXECUTING_NONE;
      driver_spi_df[number_chip_dataflsh_exchange].code_operation = CODE_OPERATION_NONE;
      
      //�������, ���� �������� ������� ���������������� ��������� ����������
      do
      {
        dataflash_status_read(number_chip_dataflsh_exchange);
        while (driver_spi_df[number_chip_dataflsh_exchange].state_execution != TRANSACTION_EXECUTED_WAIT_ANALIZE)
        {
          if (driver_spi_df[number_chip_dataflsh_exchange].state_execution == TRANSACTION_EXECUTING_NONE)
          {
            /*
            �� �������� ����� ��������� ����� � ������ ������� - ���� � ������ ������/��������
            ���������� ���� ������� � SPI_EDF, ���� �������� �������� ������ ������� ������� �������
            */
            dataflash_status_read(number_chip_dataflsh_exchange);
          }
      
          //������ � watchdogs
          if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
          {
            //������� ���� ��� ���������� Watchdog �� �����������
            GPIO_WriteBit(
                          GPIO_EXTERNAL_WATCHDOG,
                          GPIO_PIN_EXTERNAL_WATCHDOG,
                          (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                         );
            control_word_of_watchdog =  0;
          }
        }
        ready_busy = RxBuffer_SPI_EDF[1] & (1<< 7);
        driver_spi_df[number_chip_dataflsh_exchange].state_execution = TRANSACTION_EXECUTING_NONE;
        driver_spi_df[number_chip_dataflsh_exchange].code_operation = CODE_OPERATION_NONE;
      }
      while (ready_busy == 0);/*�� ready/busy ������ � �������� �������� ������� ������� �������, � � ���� �������� ������� ������� ��������*/
      
    }

    page_size_256_total &=  page_size_256;
    number_chip_dataflsh_exchange = (number_chip_dataflsh_exchange + 1) & (NUMBER_DATAFLASH_CHIP - 1);
  }
  
  if (error_into_spi_df != 0)
  {
    /*
    ���� ���� ����������� ������� �� ��� �������� �� ������ ������� 256 ����
    (�� ��� ������� ������� ������� ����� error_into_spi_df �� ��������������
    � ��������� ��������), �� ������ ���������� ���������� � ��������� �����������
    (� ����������, ���� ������� �) watchdog-�
    */
    while(1);
  }
  
  if (page_size_256_total == 0)
  {
    const unsigned char name_string[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
    {
      {
        " �������������  ",
        "   ����������   ",
      },
      {
        " ������������  ",
        "    �������    "
      },
      {
        "     Reset      ",
        "   the device   "
      },
      {
        " �������������  ",
        "   ����������   "
      }
    };

    int index_language = index_language_in_array(current_settings.language);
    
    //������ � watchdogs
    if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
    {
      //������� ���� ��� ���������� Watchdog �� �����������
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
      control_word_of_watchdog =  0;
    }

    //�������  ����� � ������� �����
    for (unsigned int i=0; i< MAX_ROW_LCD; i++)
    {
      if (i < 2)
      {
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][i][j];
      }
      else
      {
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';
      }
    }
  
    //�������� ������� ���� �����
    current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;

    //���������� ���������� �� �����
    view_whole_ekran();
    
    //������, ���� ������� ���� �������������
    while(1)
    {
      //������ � watchdogs
      if ((control_word_of_watchdog & WATCHDOG_KYYBOARD) == WATCHDOG_KYYBOARD)
      {
        //������� ���� ��� ���������� Watchdog �� �����������
        GPIO_WriteBit(
                      GPIO_EXTERNAL_WATCHDOG,
                      GPIO_PIN_EXTERNAL_WATCHDOG,
                      (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                     );
        control_word_of_watchdog =  0;
      }
    }
  }
}
/**************************************/

/**************************************/
//��������� ����� 2 ������� 4 �� ��������� ���������� ����� 1 ��
/**************************************/
void start_tim4_canal2_for_interrupt_1mc(void)
{
  TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* Output Compare Timing Mode ������������: �����:2 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStructure.TIM_Pulse = ((uint16_t)TIM4->CNT) + TIM4_CCR2_VAL;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC2Init(TIM4, &TIM_OCInitStructure);
  
  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Disable);

  /* ���������� ����������� �� ������ 2 ������� 4*/
  TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);

//  //���������� ����� ��� ������� �����������
//  TIM4->CCR2 = ((uint16_t)TIM4->CNT) + TIM4_CCR2_VAL;
}
/**************************************/

/**************************************/
//��������� ����� 3 ������� 4 �� ��������� ���������� �� ����� 10 ���
/**************************************/
void start_tim4_canal3_for_interrupt_10mkc(void)
{
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  
  if (number_bits_rs_485_waiting < 10) calculate_namber_bit_waiting_for_rs_485();

  /* Output Compare Timing Mode ������������: �����:2 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
  unsigned int delta = TIM4_CCR3_VAL*number_bits_rs_485_waiting;
  TIM_OCInitStructure.TIM_Pulse = ((uint16_t)TIM4->CNT) + delta;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
  
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Disable);

  /* ���������� ����������� �� ������ 3 ������� 4*/
  TIM_ITConfig(TIM4, TIM_IT_CC3, ENABLE);
}
/**************************************/

/**************************************/
//
/**************************************/
/**************************************/
