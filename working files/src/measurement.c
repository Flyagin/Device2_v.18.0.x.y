#include "header.h"

/*****************************************************/
//����� ������ ������ ��� ���������
/*****************************************************/
inline void find_new_ADC_canal_to_read(unsigned int command_word_adc_diff, unsigned int *point_active_index_command_word_adc)
{
  unsigned int command_word_adc_diff_tmp = command_word_adc_diff;
  unsigned int command_word_adc_diff_fapch = command_word_adc_diff_tmp & maska_canaliv_fapch;
    
  if (
      ((status_adc_read_work & DATA_VAL_READ) != 0) &&
      (command_word_adc_diff_fapch != 0) 
     )  
  {
    command_word_adc_diff_tmp = command_word_adc_diff_fapch;
  }
  else
  {
    command_word_adc_diff_tmp &= (unsigned int)(~maska_canaliv_fapch);
  }
  
  while ((command_word_adc_diff_tmp & (1 << (*point_active_index_command_word_adc))) == 0)
  {
    /*
    �� �� �������� ������, ���� ����� ������������
    */
    *point_active_index_command_word_adc = (*point_active_index_command_word_adc + 1) % NUMBER_INPUTs_ADCs;
  }
}
/*****************************************************/

/*****************************************************/
//��������� �������� ����� � ���
/*****************************************************/
void control_reading_ADCs(void)
{
  //���������� ������ �������� ����� � �������� �� ������ ����� ������������
  if (adc_DATA_VAL_read != 0)
  {
    adc_DATA_VAL_read = false;
    status_adc_read_work |= DATA_VAL_READ;
      
    /*
    ������ �� ���� ���� ��������������� ������� ����� �������������� �� 
    ����� ������ �� ����������� ������� ������ ������� ���������
    */
    command_word_adc      &= (unsigned int)(~maska_canaliv_fapch);
    command_word_adc_work &= (unsigned int)(~maska_canaliv_fapch);
        
    command_word_adc |= READ_DATA_VAL;
  }

//  if (adc_TEST_VAL_read != 0) 
//  {
//    adc_TEST_VAL_read = false;
//    status_adc_read_work |= TEST_VAL_READ;
//      
//    command_word_adc |= READ_TEST_VAL;
//  }
  
  unsigned int command_word_adc_diff = command_word_adc ^ command_word_adc_work;
  if (command_word_adc_diff != 0)
  {
    /*
    � ������, �� ������� �� ���������
    */
    find_new_ADC_canal_to_read(command_word_adc_diff, &active_index_command_word_adc);
      
    /*
    ����� active_index_command_word_adc ����� � ����� input_adc �� �����, 
    ���� ����� ����������
    */
      
    /*
    ���������, ���� ����� �������� ���
    */
    unsigned int active_adc_old = ((GPIO_SELECT_ADC->ODR & GPIO_SELECTPin_ADC) == 0) ? 1 : 2;

    /*
    ���������, ���� ����� ����� ������������ ��� � �� ��� ����� ��������
    */
    unsigned int active_adc_new = input_adc[active_index_command_word_adc][0];
    unsigned int command_word = input_adc[active_index_command_word_adc][1];
    
    //��������� ��������� ����
    if (
        (state_reading_ADCs == STATE_READING_ADCs_NONE) ||
        (state_reading_ADCs == STATE_READING_READ     )
       )
    {
      state_reading_ADCs = STATE_READING_WRITE;
      /*
      ��������� ��������� ���
      */
      switch (active_adc_new)
      {
      case 1:
        {
          //���1
          GPIO_SELECT_ADC->BSRRH = GPIO_SELECTPin_ADC;
          break;
        }
        case 2:
        {
          //���2
          GPIO_SELECT_ADC->BSRRL = GPIO_SELECTPin_ADC;
          break;
        }
      default:
        {
          //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
          total_error_sw_fixed(50);
        } 
      }
    }
    else
    {
      if (active_adc_old == active_adc_new)
      {
        state_reading_ADCs = STATE_READING_WRITE_READ;
      }
      else
      {
        state_reading_ADCs = STATE_READING_READ;
        command_word = 0;
      }
    }
    
    if (command_word != 0)
    {
      /*
      �������, �� ����� ������ ���� �������� ����� ����������
      */
      command_word_adc_work |= (1 << active_index_command_word_adc);
    }

    //�������� �������� �����
    while ((SPI_ADC->SR & SPI_I2S_FLAG_TXE) == RESET);      //�������, ���� SPI ����� ������
    GPIO_SPI_ADC->BSRRH = GPIO_NSSPin_ADC;                  //����������� chip_select
    SPI_ADC->DR = (uint16_t)command_word;                   //³���������� �������� �����
    
    channel_answer = channel_request;
    channel_request = (active_adc_new - 1)*NUMBER_CANALs_ADC + ((command_word >> 10) & 0xf);
  }
  else 
  {
    if (
        (state_reading_ADCs == STATE_READING_READ     ) ||
        (state_reading_ADCs == STATE_READING_ADCs_NONE)
       )
    {
      //�� ������ ��� ���������
      state_reading_ADCs = STATE_READING_ADCs_NONE;

      command_word_adc = 0;
      command_word_adc_work = 0;
      active_index_command_word_adc = 0;
    }
    else
    {
      /*
      ����� �� �������� �������� � ���������� ��������, ���� ����� �����
      ���� �������������
      */
      state_reading_ADCs = STATE_READING_READ;
      while ((SPI_ADC->SR & SPI_I2S_FLAG_TXE) == RESET);      //�������, ���� SPI ����� ������
      GPIO_SPI_ADC->BSRRH = GPIO_NSSPin_ADC;                  //����������� chip_select
      SPI_ADC->DR = 0;                                        //³���������� ����� (��� ���, ��� ���� ���������� ����� �� ������������)
    
      channel_answer = channel_request;
    }
  }
}
/*****************************************************/

/*************************************************************************
����������� ��� ��� ������������ ���'�
 *************************************************************************/
void Fourier(void)
{
  unsigned int index_data_sin_cos_array_tmp = index_data_sin_cos_array;
  unsigned int index_sin_cos_array_tmp = index_sin_cos_array;

  long long data64_new = (long long)ADCs_data[I_3I0];
  unsigned long long square_new = data64_new*data64_new;

  sum_sqr_data_3I0_irq += square_new;
  sum_sqr_data_3I0_irq -= sqr_current_data_3I0[index_array_of_one_value_fourier];
  sqr_current_data_3I0[index_array_of_one_value_fourier] = square_new;
    
  if((++index_array_of_one_value_fourier) == NUMBER_POINT)
    index_array_of_one_value_fourier = 0;
  else if (index_array_of_one_value_fourier > NUMBER_POINT)
  {
    //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
    total_error_sw_fixed(58);
  }

  for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++)
  {
    //������� ������ �������� ��� ����� ����������
    int temp_value_1 = ADCs_data[i];
    int temp_value_2;
    unsigned int i_ort_tmp = 2*i;

    //����������� SIN
    ortogonal_irq[i_ort_tmp] -= data_sin[index_data_sin_cos_array_tmp];
    temp_value_2 = (int)((float)temp_value_1*sin_data_f[index_sin_cos_array_tmp]);
    data_sin[index_data_sin_cos_array_tmp] = temp_value_2;
    ortogonal_irq[i_ort_tmp] += temp_value_2;
    
    //����������� COS
    ortogonal_irq[i_ort_tmp + 1] -= data_cos[index_data_sin_cos_array_tmp];
    temp_value_2 = (int)((float)temp_value_1*cos_data_f[index_sin_cos_array_tmp]);
    data_cos[index_data_sin_cos_array_tmp] = temp_value_2;
    ortogonal_irq[i_ort_tmp + 1] += temp_value_2;
    
    if((++index_data_sin_cos_array_tmp) >= (NUMBER_POINT*NUMBER_ANALOG_CANALES)) index_data_sin_cos_array_tmp = 0;
  }
  index_data_sin_cos_array = index_data_sin_cos_array_tmp;
  
  if((++index_sin_cos_array_tmp) >= NUMBER_POINT) index_sin_cos_array_tmp = 0;
  index_sin_cos_array = index_sin_cos_array_tmp;

  //��������� ��� ����� ������
  unsigned int bank_ortogonal_tmp = bank_ortogonal;
  for(unsigned int i = 0; i < (2*NUMBER_ANALOG_CANALES); i++ ) ortogonal[i][bank_ortogonal_tmp] = ortogonal_irq[i];
  sum_sqr_data_3I0[bank_ortogonal_tmp] = sum_sqr_data_3I0_irq;
}
/*************************************************************************/

/*************************************************************************
�������� ������� ��� ������ ����� 1
*************************************************************************/
void fapch(void)
{
  unsigned int bank_measurement_high_tmp = bank_measurement_high;
  int index_1 = -1;
  unsigned int maska_canaliv_fapch_tmp = 0;

  /*****
  ������ ������ �� ����� ������ ������������� �������
  *****/  
  if (measurement_high[bank_measurement_high_tmp][IM_UA] >= PORIG_FOR_FAPCH)
  {
    index_1 = INDEX_PhK_UA;
    maska_canaliv_fapch_tmp = READ_Ua;
  }
  else if (measurement_high[bank_measurement_high_tmp][IM_UB] >= PORIG_FOR_FAPCH)
  {
    index_1 = INDEX_PhK_UB;
    maska_canaliv_fapch_tmp = READ_Ub;
  }
  else if (measurement_high[bank_measurement_high_tmp][IM_UC] >= PORIG_FOR_FAPCH)
  {
    index_1 = INDEX_PhK_UC;
    maska_canaliv_fapch_tmp = READ_Uc;
  }
  else if (measurement_high[bank_measurement_high_tmp][IM_3U0] >= PORIG_FOR_FAPCH) 
  {
    index_1 = INDEX_PhK_3U0;
    maska_canaliv_fapch_tmp = READ_3U0;
  }
  maska_canaliv_fapch = maska_canaliv_fapch_tmp;
  /*****/

  uint32_t step_timer_adc_tmp;
  /*****/
  //�������
  /*****/
  step_timer_adc_tmp = step_timer_adc;
  if (
      (index_1 >= 0) &&
      (fix_perechid_cherez_nul[index_1] != 0)
     )   
  {
    fix_perechid_cherez_nul[index_1] = 0;
    
    unsigned int delta_tick;
    long long tick_tmp;
    int delta_value;
    unsigned int tick_p, x1_tmp, x2_tmp;
      
    /*��������� ��� �������� ����� 0 ������������ ���� � ����������� ����� ������������*/
    delta_value = perechid_cherez_nul[index_1][0].y2 - perechid_cherez_nul[index_1][0].y1;
    x1_tmp = perechid_cherez_nul[index_1][0].x1;
    x2_tmp = perechid_cherez_nul[index_1][0].x2;
    if (x2_tmp > x1_tmp) delta_tick = x2_tmp - x1_tmp;
    else
    {
      long long delta_tick_64 = x2_tmp + 0x100000000 - x1_tmp;
      delta_tick = delta_tick_64;
    }
    tick_tmp = ((long long)perechid_cherez_nul[index_1][0].x1) - ((long long)perechid_cherez_nul[index_1][0].y1)*((long long)delta_tick)/((long long)delta_value);
    if (tick_tmp < 0) 
    {
      tick_tmp += 0x100000000;
      tick_p = (unsigned int)tick_tmp;
    }
    else
    {
      if (tick_tmp < 0x100000000) tick_p = (unsigned int)tick_tmp;
      else 
      {
        tick_tmp -= 0x100000000;
        tick_p = (unsigned int)tick_tmp;
      }
    }

    /*��������� ��� �������� ����� 0 ��������� ���� � ����������� ����� ������������*/
    delta_value = perechid_cherez_nul[index_1][1].y2 - perechid_cherez_nul[index_1][1].y1;
    x1_tmp = perechid_cherez_nul[index_1][1].x1;
    x2_tmp = perechid_cherez_nul[index_1][1].x2;
    if (x2_tmp > x1_tmp) delta_tick = x2_tmp - x1_tmp;
    else
    {
      long long delta_tick_64 = x2_tmp + 0x100000000 - x1_tmp;
      delta_tick = delta_tick_64;
    }
    tick_tmp = ((long long)perechid_cherez_nul[index_1][1].x1) - ((long long)perechid_cherez_nul[index_1][1].y1)*((long long)delta_tick)/((long long)delta_value);
    if (tick_tmp < 0) 
    {
      tick_tmp += 0x100000000;
      tick_c = (unsigned int)tick_tmp;
    }
    else
    {
      if (tick_tmp < 0x100000000) tick_c = (unsigned int)tick_tmp;
      else 
      {
        tick_tmp -= 0x100000000;
        tick_c = (unsigned int)tick_tmp;
      }
    }
    /***/
      
    if (tick_c > tick_p) delta_tick = tick_c - tick_p;
    else
    {
      long long delta_tick_64 = tick_c + 0x100000000 - tick_p;
      delta_tick = delta_tick_64;
    }
    tick_period = delta_tick;
    
    /*****
    ���������� �������
    *****/
    if (
        (tick_period <= MAX_TICK_PERIOD) &&
        (tick_period >= MIN_TICK_PERIOD)
       ) 
    {
      frequency = (float)MEASUREMENT_TIM_FREQUENCY/(float)tick_period;

      step_timer_adc_tmp = tick_period >> VAGA_NUMBER_POINT;
      if ((tick_period - (step_timer_adc_tmp << VAGA_NUMBER_POINT)) >= (1 << (VAGA_NUMBER_POINT - 1))) step_timer_adc_tmp++;
    }
    else
    {
      step_timer_adc_tmp = TIM5_CCR1_2_VAL;
      if (tick_period > MAX_TICK_PERIOD) frequency = -2; /*������� ����� ������ ����������� ���������� MIN_FREQUENCY*/
      else frequency = -3; /*������� ���� ������ ����������� ���������� MAX_FREQUENCY*/
    }
    /****/
  }
  else
  {
    if (index_1 < 0)
    {
      step_timer_adc_tmp = TIM5_CCR1_2_VAL;
      frequency = -1; /*������� �� ���������*/
    }
  }
  /*****/

  /*****/
  //����
  /*****/
  if (step_timer_adc != step_timer_adc_tmp)
  {
    //����� ������ ������� �������������
    step_timer_adc = step_timer_adc_tmp;
  }
  
  if ((command_restart_monitoring_frequency & (1 << 0)) != 0)
  {
    frequency_min = 50;
    frequency_max = 50;
    
    command_restart_monitoring_frequency &= (unsigned int)(~(1 << 0));
  }
  else
  {
    if (frequency >= 0)
    {
      if (frequency > frequency_max) frequency_max = frequency;
      if (frequency < frequency_min) frequency_min = frequency;
    }
  }
  /*****/
}
/*****************************************************/

/*****************************************************/
//����������� �� ���������� ����� �� ������ SPI, ���� ��������� ����������� �������
/*****************************************************/
void SPI_ADC_IRQHandler(void)
{
//#ifdef SYSTEM_VIEWER_ENABLE
//  SEGGER_SYSVIEW_RecordEnterISR();
//#endif

  //Գ����� ���� � ����������� ������� ����� �� ���
  semaphore_adc_irq  = true;
  
  //Գ����� ��� ���������
  uint32_t tick_output_adc_tmp = TIM5->CNT;
  
  //�� ������ ������� ������ chip_select
  GPIO_SPI_ADC->BSRRL = GPIO_NSSPin_ADC;
  uint16_t read_value = SPI_ADC->DR;

  static uint32_t tick_output_adc_p;
  /*
  �������� ������� ���
  */
  if (
      (state_reading_ADCs == STATE_READING_WRITE_READ) ||
      (state_reading_ADCs == STATE_READING_READ)
     )
  {
    unsigned int shift = ((GPIO_SELECT_ADC->ODR & GPIO_SELECTPin_ADC) == 0) ? 0 : NUMBER_CANALs_ADC;
    unsigned int number_canal = shift + ((read_value >> 12) & 0xf);
    
    output_adc[number_canal].tick = tick_output_adc_p;
    
    static uint32_t error_spi_adc;
    if(channel_answer != number_canal) 
    {
      if (error_spi_adc < 3 ) error_spi_adc++;
      if (error_spi_adc >= 3 )_SET_BIT(set_diagnostyka, ERROR_SPI_ADC_BIT);
    }
    else 
    {
      error_spi_adc = 0;
      
      _SET_BIT(clear_diagnostyka, ERROR_SPI_ADC_BIT);
      output_adc[number_canal].value = read_value & 0xfff;
    }
  }
  tick_output_adc_p = tick_output_adc_tmp;
  /***/
  
  //�������� �������� � ������� ���
  control_reading_ADCs();
  
  /*
  �������� �� �������� ����� ���, ���� �� ������ ��� ���������
  */
  if (state_reading_ADCs == STATE_READING_ADCs_NONE)
  {
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif
  
    /*******************************************************/
    //����������, �� ���������� ���� ���������
    /*******************************************************/
    if (changed_ustuvannja == CHANGED_ETAP_ENDED) /*�� � �����, �� ��� ��� ���������� ��� �������� �� � ������ ������������ �������� (� ��� ����� ����� ��� �� ���������)*/
    {
      //������� ����� ��������� � ���� ����� ������ ��� � ���� ������ (���� � �����) ����� ����������� ���������
      for(unsigned int k = 0; k < NUMBER_ANALOG_CANALES; k++) 
      {
        ustuvannja_meas[k] = ustuvannja[k];
      }
      
      //�������, �� ���� ������� ������������ ��������, ��� �� ����� �������� �������� �������
      changed_ustuvannja = CHANGED_ETAP_ENDED_EXTRA_ETAP;
    }
    /*****************************************************/

    /*
    ������� �������� ������������� ������
    */
    unsigned int command_word = 0;
    if ((status_adc_read_work & DATA_VAL_READ) != 0)
    {
      command_word |= (1 << I_3I0)|
                      (1 << I_Ia) | (1 << I_Ib) | (1 << I_Ic) |
                      (1 << I_Ua) | (1 << I_Ub) | (1 << I_Uc) |
                      (1 << I_3U0);
        
    }
      
    uint32_t _x1, _x2, _DX, _dx;
    int _y1, _y2;
    long long _y;
      
//    unsigned int gnd_adc  = gnd_adc1; 
//    unsigned int vref_adc/* = vref_adc1*/; 

    uint32_t _x = previous_tick_DATA_VAL;
    /*****/
    //������� �������� 3I0
    /*****/
    if ((command_word & (1 << I_3I0)) != 0)
    {
      _x1 = ADCs_data_raw[I_3I0].tick;
      _y1 = ADCs_data_raw[I_3I0].value;
      
      static uint32_t index_array_of_one_value_3I0;
      
      uint32_t val_C_3I0_16 = output_adc[C_3I0_16].value;
      vref_adc_averange_sum[I_3I0] += val_C_3I0_16;
      
      if((++index_array_of_one_value_3I0) == NUMBER_POINT)
      {
        index_array_of_one_value_3I0 = 0;
        uint32_t vref_adc_period = vref_adc_averange_sum[I_3I0] >> VAGA_NUMBER_POINT;
        vref_adc_averange_sum[I_3I0] = 0;

        //������ ����� ����������� �� �������
        static uint32_t index_array_of_one_value_3I0_1s;
        
        vref_adc_averange_sum_1s[I_3I0] += vref_adc_period;
        vref_adc_averange_sum_1s[I_3I0] -= vref_adc_moment_value_1s[I_3I0][index_array_of_one_value_3I0_1s];
        vref_adc_moment_value_1s[I_3I0][index_array_of_one_value_3I0_1s] = vref_adc_period;
        vref_adc[I_3I0] = vref_adc_averange_sum_1s[I_3I0] / MAIN_FREQUENCY;
        
        if((++index_array_of_one_value_3I0_1s) == MAIN_FREQUENCY)
          index_array_of_one_value_3I0_1s = 0;
        else if (index_array_of_one_value_3I0_1s > MAIN_FREQUENCY)
        {
          //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
          total_error_sw_fixed(104);
        }
      }
      else if (index_array_of_one_value_3I0 > NUMBER_POINT)
      {
        //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
        total_error_sw_fixed(21);
      }
        
//      _y2 = output_adc[C_3I0_1].value - gnd_adc - vref_adc;
//      if (abs(_y2) > 87)
//      {
//        _x2 = output_adc[C_3I0_1].tick;
//        _y2 = (int)(_y2*ustuvannja_meas[I_3I0])>>(USTUVANNJA_VAGA - 2*4);
//      }
//      else
//      {
        _y2 = val_C_3I0_16 - /*gnd_adc - */ vref_adc[I_3I0];
        if (abs(_y2) > 87)
        {
          _x2 = output_adc[C_3I0_16].tick;
          _y2 = (int)(_y2*ustuvannja_meas[I_3I0])>>(USTUVANNJA_VAGA - 4);
        }
        else
        {
          _y2 = output_adc[C_3I0_256].value - /*gnd_adc - */ vref_adc[I_3I0];

          _x2 = output_adc[C_3I0_256].tick;
          _y2 = (int)((-_y2)*ustuvannja_meas[I_3I0])>>(USTUVANNJA_VAGA);
        }
//      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      ADCs_data[I_3I0] = _y;
      
      ADCs_data_raw[I_3I0].tick = _x2;
      ADCs_data_raw[I_3I0].value = _y2;
    }
    /*****/

    /*****/
    //������� �������� Ia
    /*****/
    if ((command_word & (1 << I_Ia)) != 0)
    {
      _x1 = ADCs_data_raw[I_Ia].tick;
      _y1 = ADCs_data_raw[I_Ia].value;
        
      static uint32_t index_array_of_one_value_Ia;
      
      uint32_t val_C_Ia_1 = output_adc[C_Ia_1].value;
      vref_adc_averange_sum[I_Ia] += val_C_Ia_1;
      
      if((++index_array_of_one_value_Ia) == NUMBER_POINT)
      {
        index_array_of_one_value_Ia = 0;
        uint32_t vref_adc_period = vref_adc_averange_sum[I_Ia] >> VAGA_NUMBER_POINT;
        vref_adc_averange_sum[I_Ia] = 0;

        //������ ����� ����������� �� �������
        static uint32_t index_array_of_one_value_Ia_1s;
        
        vref_adc_averange_sum_1s[I_Ia] += vref_adc_period;
        vref_adc_averange_sum_1s[I_Ia] -= vref_adc_moment_value_1s[I_Ia][index_array_of_one_value_Ia_1s];
        vref_adc_moment_value_1s[I_Ia][index_array_of_one_value_Ia_1s] = vref_adc_period;
        vref_adc[I_Ia] = vref_adc_averange_sum_1s[I_Ia] / MAIN_FREQUENCY;
        
        if((++index_array_of_one_value_Ia_1s) == MAIN_FREQUENCY)
          index_array_of_one_value_Ia_1s = 0;
        else if (index_array_of_one_value_Ia_1s > MAIN_FREQUENCY)
        {
          //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
          total_error_sw_fixed(106);
        }
      }
      else if (index_array_of_one_value_Ia > NUMBER_POINT)
      {
        //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
        total_error_sw_fixed(105);
      }

      _y2 = val_C_Ia_1 - /*gnd_adc - */ vref_adc[I_Ia];
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Ia_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Ia])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Ia_16].value - /*gnd_adc - */ vref_adc[I_Ia];

        _x2 = output_adc[C_Ia_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Ia])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      ADCs_data[I_Ia] = _y;
      
      ADCs_data_raw[I_Ia].tick = _x2;
      ADCs_data_raw[I_Ia].value = _y2;
    }
    /*****/

    /*****/
    //������� �������� Ib
    /*****/
    if ((command_word & (1 << I_Ib)) != 0)
    {
      _x1 = ADCs_data_raw[I_Ib].tick;
      _y1 = ADCs_data_raw[I_Ib].value;
        
      static uint32_t index_array_of_one_value_Ib;
      
      uint32_t val_C_Ib_1 = output_adc[C_Ib_1].value;
      vref_adc_averange_sum[I_Ib] += val_C_Ib_1;
      
      if((++index_array_of_one_value_Ib) == NUMBER_POINT)
      {
        index_array_of_one_value_Ib = 0;
        uint32_t vref_adc_period = vref_adc_averange_sum[I_Ib] >> VAGA_NUMBER_POINT;
        vref_adc_averange_sum[I_Ib] = 0;

        //������ ����� ����������� �� �������
        static uint32_t index_array_of_one_value_Ib_1s;
        
        vref_adc_averange_sum_1s[I_Ib] += vref_adc_period;
        vref_adc_averange_sum_1s[I_Ib] -= vref_adc_moment_value_1s[I_Ib][index_array_of_one_value_Ib_1s];
        vref_adc_moment_value_1s[I_Ib][index_array_of_one_value_Ib_1s] = vref_adc_period;
        vref_adc[I_Ib] = vref_adc_averange_sum_1s[I_Ib] / MAIN_FREQUENCY;
        
        if((++index_array_of_one_value_Ib_1s) == MAIN_FREQUENCY)
          index_array_of_one_value_Ib_1s = 0;
        else if (index_array_of_one_value_Ib_1s > MAIN_FREQUENCY)
        {
          //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
          total_error_sw_fixed(108);
        }
      }
      else if (index_array_of_one_value_Ib > NUMBER_POINT)
      {
        //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
        total_error_sw_fixed(107);
      }

      _y2 = val_C_Ib_1 - /*gnd_adc - */ vref_adc[I_Ib];
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Ib_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Ib])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Ib_16].value - /*gnd_adc - */ vref_adc[I_Ib];

        _x2 = output_adc[C_Ib_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Ib])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      ADCs_data[I_Ib] = _y;
      
      ADCs_data_raw[I_Ib].tick = _x2;
      ADCs_data_raw[I_Ib].value = _y2;
    }
    /*****/
    
    /*****/
    //������� �������� Ic
    /*****/
    if ((command_word & (1 << I_Ic)) != 0)
    {
      _x1 = ADCs_data_raw[I_Ic].tick;
      _y1 = ADCs_data_raw[I_Ic].value;
        
      static uint32_t index_array_of_one_value_Ic;
      
      uint32_t val_C_Ic_1 = output_adc[C_Ic_1].value;
      vref_adc_averange_sum[I_Ic] += val_C_Ic_1;
      
      if((++index_array_of_one_value_Ic) == NUMBER_POINT)
      {
        index_array_of_one_value_Ic = 0;
        uint32_t vref_adc_period = vref_adc_averange_sum[I_Ic] >> VAGA_NUMBER_POINT;
        vref_adc_averange_sum[I_Ic] = 0;

        //������ ����� ����������� �� �������
        static uint32_t index_array_of_one_value_Ic_1s;
        
        vref_adc_averange_sum_1s[I_Ic] += vref_adc_period;
        vref_adc_averange_sum_1s[I_Ic] -= vref_adc_moment_value_1s[I_Ic][index_array_of_one_value_Ic_1s];
        vref_adc_moment_value_1s[I_Ic][index_array_of_one_value_Ic_1s] = vref_adc_period;
        vref_adc[I_Ic] = vref_adc_averange_sum_1s[I_Ic] / MAIN_FREQUENCY;
        
        if((++index_array_of_one_value_Ic_1s) == MAIN_FREQUENCY)
          index_array_of_one_value_Ic_1s = 0;
        else if (index_array_of_one_value_Ic_1s > MAIN_FREQUENCY)
        {
          //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
          total_error_sw_fixed(110);
        }
      }
      else if (index_array_of_one_value_Ic > NUMBER_POINT)
      {
        //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
        total_error_sw_fixed(109);
      }

      _y2 = val_C_Ic_1 - /*gnd_adc - */ vref_adc[I_Ic];
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Ic_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Ic])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Ic_16].value - /*gnd_adc - */ vref_adc[I_Ic];

        _x2 = output_adc[C_Ic_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Ic])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      ADCs_data[I_Ic] = _y;
      
      ADCs_data_raw[I_Ic].tick = _x2;
      ADCs_data_raw[I_Ic].value = _y2;
    }
    /*****/
    
//    gnd_adc  = gnd_adc2; 
//    vref_adc = vref_adc2; 

    /*****/
    //������� �������� 3U0
    /*****/
    if ((command_word & (1 << I_3U0)) != 0)
    {
      _x1 = ADCs_data_raw[I_3U0].tick;
      _y1 = ADCs_data_raw[I_3U0].value;
        
      static uint32_t index_array_of_one_value_3U0;
      
      uint32_t val_C_3U0_1 = output_adc[C_3U0_1].value;
      vref_adc_averange_sum[I_3U0] += val_C_3U0_1;
      
      if((++index_array_of_one_value_3U0) == NUMBER_POINT)
      {
        index_array_of_one_value_3U0 = 0;
        uint32_t vref_adc_period = vref_adc_averange_sum[I_3U0] >> VAGA_NUMBER_POINT;
        vref_adc_averange_sum[I_3U0] = 0;

        //������ ����� ����������� �� �������
        static uint32_t index_array_of_one_value_3U0_1s;
        
        vref_adc_averange_sum_1s[I_3U0] += vref_adc_period;
        vref_adc_averange_sum_1s[I_3U0] -= vref_adc_moment_value_1s[I_3U0][index_array_of_one_value_3U0_1s];
        vref_adc_moment_value_1s[I_3U0][index_array_of_one_value_3U0_1s] = vref_adc_period;
        vref_adc[I_3U0] = vref_adc_averange_sum_1s[I_3U0] / MAIN_FREQUENCY;
        
        if((++index_array_of_one_value_3U0_1s) == MAIN_FREQUENCY)
          index_array_of_one_value_3U0_1s = 0;
        else if (index_array_of_one_value_3U0_1s > MAIN_FREQUENCY)
        {
          //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
          total_error_sw_fixed(112);
        }
      }
      else if (index_array_of_one_value_3U0 > NUMBER_POINT)
      {
        //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
        total_error_sw_fixed(111);
      }

      _y2 = val_C_3U0_1 - /*gnd_adc - */ vref_adc[I_3U0];
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_3U0_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_3U0])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_3U0_16].value - /*gnd_adc - */ vref_adc[I_3U0];

        _x2 = output_adc[C_3U0_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_3U0])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      if ((_y >= 0) && (ADCs_data[I_3U0] < 0))
      {
        /*
        ������������ ������� ����� ����
        */
        //��������� �������
        perechid_cherez_nul[INDEX_PhK_3U0][0].x1 = poperednij_perechid.U0_x1;
        perechid_cherez_nul[INDEX_PhK_3U0][0].y1 = poperednij_perechid.U0_y1;
        perechid_cherez_nul[INDEX_PhK_3U0][0].x2 = poperednij_perechid.U0_x2;
        perechid_cherez_nul[INDEX_PhK_3U0][0].y2 = poperednij_perechid.U0_y2;
          
        //�������� �������
        poperednij_perechid.U0_x1 = perechid_cherez_nul[INDEX_PhK_3U0][1].x1 = penultimate_tick_DATA_VAL;
        poperednij_perechid.U0_y1 = perechid_cherez_nul[INDEX_PhK_3U0][1].y1 = ADCs_data[I_3U0];
        poperednij_perechid.U0_x2 = perechid_cherez_nul[INDEX_PhK_3U0][1].x2 = _x;
        poperednij_perechid.U0_y2 = perechid_cherez_nul[INDEX_PhK_3U0][1].y2 = _y;
          
        //�������, �� ������� ������������
        fix_perechid_cherez_nul[INDEX_PhK_3U0] = 0xff;
      }
      ADCs_data[I_3U0] = _y;
      
      ADCs_data_raw[I_3U0].tick = _x2;
      ADCs_data_raw[I_3U0].value = _y2;
    }
    /*****/

    /*****/
    //������� �������� Ua
    /*****/
    if ((command_word & (1 << I_Ua)) != 0)
    {
      _x1 = ADCs_data_raw[I_Ua].tick;
      _y1 = ADCs_data_raw[I_Ua].value;
        
      static uint32_t index_array_of_one_value_Ua;
      
      uint32_t val_C_Ua_1 = output_adc[C_Ua_1].value;
      vref_adc_averange_sum[I_Ua] += val_C_Ua_1;
      
      if((++index_array_of_one_value_Ua) == NUMBER_POINT)
      {
        index_array_of_one_value_Ua = 0;
        uint32_t vref_adc_period = vref_adc_averange_sum[I_Ua] >> VAGA_NUMBER_POINT;
        vref_adc_averange_sum[I_Ua] = 0;

        //������ ����� ����������� �� �������
        static uint32_t index_array_of_one_value_Ua_1s;
        
        vref_adc_averange_sum_1s[I_Ua] += vref_adc_period;
        vref_adc_averange_sum_1s[I_Ua] -= vref_adc_moment_value_1s[I_Ua][index_array_of_one_value_Ua_1s];
        vref_adc_moment_value_1s[I_Ua][index_array_of_one_value_Ua_1s] = vref_adc_period;
        vref_adc[I_Ua] = vref_adc_averange_sum_1s[I_Ua] / MAIN_FREQUENCY;
        
        if((++index_array_of_one_value_Ua_1s) == MAIN_FREQUENCY)
          index_array_of_one_value_Ua_1s = 0;
        else if (index_array_of_one_value_Ua_1s > MAIN_FREQUENCY)
        {
          //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
          total_error_sw_fixed(114);
        }
      }
      else if (index_array_of_one_value_Ua > NUMBER_POINT)
      {
        //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
        total_error_sw_fixed(113);
      }

      _y2 = val_C_Ua_1 - /*gnd_adc - */ vref_adc[I_Ua];
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Ua_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Ua])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Ua_16].value - /*gnd_adc - */ vref_adc[I_Ua];

        _x2 = output_adc[C_Ua_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Ua])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);
      
      if ((_y >= 0) && (ADCs_data[I_Ua] < 0))
      {
        /*
        ������������ ������� ����� ����
        */
        //��������� �������
        perechid_cherez_nul[INDEX_PhK_UA][0].x1 = poperednij_perechid.Ua_x1;
        perechid_cherez_nul[INDEX_PhK_UA][0].y1 = poperednij_perechid.Ua_y1;
        perechid_cherez_nul[INDEX_PhK_UA][0].x2 = poperednij_perechid.Ua_x2;
        perechid_cherez_nul[INDEX_PhK_UA][0].y2 = poperednij_perechid.Ua_y2;
          
        //�������� �������
        poperednij_perechid.Ua_x1 = perechid_cherez_nul[INDEX_PhK_UA][1].x1 = penultimate_tick_DATA_VAL;
        poperednij_perechid.Ua_y1 = perechid_cherez_nul[INDEX_PhK_UA][1].y1 = ADCs_data[I_Ua];
        poperednij_perechid.Ua_x2 = perechid_cherez_nul[INDEX_PhK_UA][1].x2 = _x;
        poperednij_perechid.Ua_y2 = perechid_cherez_nul[INDEX_PhK_UA][1].y2 = _y;
          
        //�������, �� ������� ������������
        fix_perechid_cherez_nul[INDEX_PhK_UA] = 0xff;
      }
      ADCs_data[I_Ua] = _y;
      
      ADCs_data_raw[I_Ua].tick = _x2;
      ADCs_data_raw[I_Ua].value = _y2;
    }
    /*****/
    
    /*****/
    //������� �������� Ub
    /*****/
    if ((command_word & (1 << I_Ub)) != 0)
    {
      _x1 = ADCs_data_raw[I_Ub].tick;
      _y1 = ADCs_data_raw[I_Ub].value;
        
      static uint32_t index_array_of_one_value_Ub;
      
      uint32_t val_C_Ub_1 = output_adc[C_Ub_1].value;
      vref_adc_averange_sum[I_Ub] += val_C_Ub_1;
      
      if((++index_array_of_one_value_Ub) == NUMBER_POINT)
      {
        index_array_of_one_value_Ub = 0;
        uint32_t vref_adc_period = vref_adc_averange_sum[I_Ub] >> VAGA_NUMBER_POINT;
        vref_adc_averange_sum[I_Ub] = 0;

        //������ ����� ����������� �� �������
        static uint32_t index_array_of_one_value_Ub_1s;
        
        vref_adc_averange_sum_1s[I_Ub] += vref_adc_period;
        vref_adc_averange_sum_1s[I_Ub] -= vref_adc_moment_value_1s[I_Ub][index_array_of_one_value_Ub_1s];
        vref_adc_moment_value_1s[I_Ub][index_array_of_one_value_Ub_1s] = vref_adc_period;
        vref_adc[I_Ub] = vref_adc_averange_sum_1s[I_Ub] / MAIN_FREQUENCY;
        
        if((++index_array_of_one_value_Ub_1s) == MAIN_FREQUENCY)
          index_array_of_one_value_Ub_1s = 0;
        else if (index_array_of_one_value_Ub_1s > MAIN_FREQUENCY)
        {
          //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
          total_error_sw_fixed(116);
        }
      }
      else if (index_array_of_one_value_Ub > NUMBER_POINT)
      {
        //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
        total_error_sw_fixed(115);
      }

      _y2 = val_C_Ub_1 - /*gnd_adc - */ vref_adc[I_Ub];
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Ub_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Ub])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Ub_16].value - /*gnd_adc - */ vref_adc[I_Ub];

        _x2 = output_adc[C_Ub_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Ub])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);
 
      if ((_y >= 0) && (ADCs_data[I_Ub] < 0))
      {
        /*
        ������������ ������� ����� ����
        */
        //��������� �������
        perechid_cherez_nul[INDEX_PhK_UB][0].x1 = poperednij_perechid.Ub_x1;
        perechid_cherez_nul[INDEX_PhK_UB][0].y1 = poperednij_perechid.Ub_y1;
        perechid_cherez_nul[INDEX_PhK_UB][0].x2 = poperednij_perechid.Ub_x2;
        perechid_cherez_nul[INDEX_PhK_UB][0].y2 = poperednij_perechid.Ub_y2;
          
        //�������� �������
        poperednij_perechid.Ub_x1 = perechid_cherez_nul[INDEX_PhK_UB][1].x1 = penultimate_tick_DATA_VAL;
        poperednij_perechid.Ub_y1 = perechid_cherez_nul[INDEX_PhK_UB][1].y1 = ADCs_data[I_Ub];
        poperednij_perechid.Ub_x2 = perechid_cherez_nul[INDEX_PhK_UB][1].x2 = _x;
        poperednij_perechid.Ub_y2 = perechid_cherez_nul[INDEX_PhK_UB][1].y2 = _y;
          
        //�������, �� ������� ������������
        fix_perechid_cherez_nul[INDEX_PhK_UB] = 0xff;
      }
      ADCs_data[I_Ub] = _y;
      
      ADCs_data_raw[I_Ub].tick = _x2;
      ADCs_data_raw[I_Ub].value = _y2;
    }
    /*****/
    
    /*****/
    //������� �������� Uc
    /*****/
    if ((command_word & (1 << I_Uc)) != 0)
    {
      _x1 = ADCs_data_raw[I_Uc].tick;
      _y1 = ADCs_data_raw[I_Uc].value;
        
      static uint32_t index_array_of_one_value_Uc;
      
      uint32_t val_C_Uc_1 = output_adc[C_Uc_1].value;
      vref_adc_averange_sum[I_Uc] += val_C_Uc_1;
      
      if((++index_array_of_one_value_Uc) == NUMBER_POINT)
      {
        index_array_of_one_value_Uc = 0;
        uint32_t vref_adc_period = vref_adc_averange_sum[I_Uc] >> VAGA_NUMBER_POINT;
        vref_adc_averange_sum[I_Uc] = 0;

        //������ ����� ����������� �� �������
        static uint32_t index_array_of_one_value_Uc_1s;
        
        vref_adc_averange_sum_1s[I_Uc] += vref_adc_period;
        vref_adc_averange_sum_1s[I_Uc] -= vref_adc_moment_value_1s[I_Uc][index_array_of_one_value_Uc_1s];
        vref_adc_moment_value_1s[I_Uc][index_array_of_one_value_Uc_1s] = vref_adc_period;
        vref_adc[I_Uc] = vref_adc_averange_sum_1s[I_Uc] / MAIN_FREQUENCY;
        
        if((++index_array_of_one_value_Uc_1s) == MAIN_FREQUENCY)
          index_array_of_one_value_Uc_1s = 0;
        else if (index_array_of_one_value_Uc_1s > MAIN_FREQUENCY)
        {
          //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
          total_error_sw_fixed(118);
        }
      }
      else if (index_array_of_one_value_Uc > NUMBER_POINT)
      {
        //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
        total_error_sw_fixed(117);
      }

      _y2 = val_C_Uc_1 - /*gnd_adc - */ vref_adc[I_Uc];
      if (abs(_y2) > 87)
      {
        _x2 = output_adc[C_Uc_1].tick;
        _y2 = (int)(_y2*ustuvannja_meas[I_Uc])>>(USTUVANNJA_VAGA - 4);
      }
      else
      {
        _y2 = output_adc[C_Uc_16].value - /*gnd_adc - */ vref_adc[I_Uc];

        _x2 = output_adc[C_Uc_16].tick;
        _y2 = (int)((-_y2)*ustuvannja_meas[I_Uc])>>(USTUVANNJA_VAGA);
      }
      
      if (_x2 > _x1) _DX = _x2 - _x1;
      else
      {
        uint64_t _DX_64 = _x2 + 0x100000000 - _x1;
        _DX = _DX_64;
      }
      if (_x >= _x1) _dx = _x - _x1;
      else
      {
        uint64_t _dx_64 = _x + 0x100000000 - _x1;
        _dx = _dx_64;
      }
      _y = ((long long)_y1) + ((long long)(_y2 - _y1))*((long long)_dx)/((long long)_DX);

      if ((_y >= 0) && (ADCs_data[I_Uc] < 0))
      {
        /*
        ������������ ������� ����� ����
        */
        //��������� �������
        perechid_cherez_nul[INDEX_PhK_UC][0].x1 = poperednij_perechid.Uc_x1;
        perechid_cherez_nul[INDEX_PhK_UC][0].y1 = poperednij_perechid.Uc_y1;
        perechid_cherez_nul[INDEX_PhK_UC][0].x2 = poperednij_perechid.Uc_x2;
        perechid_cherez_nul[INDEX_PhK_UC][0].y2 = poperednij_perechid.Uc_y2;
          
        //�������� �������
        poperednij_perechid.Uc_x1 = perechid_cherez_nul[INDEX_PhK_UC][1].x1 = penultimate_tick_DATA_VAL;
        poperednij_perechid.Uc_y1 = perechid_cherez_nul[INDEX_PhK_UC][1].y1 = ADCs_data[I_Uc];
        poperednij_perechid.Uc_x2 = perechid_cherez_nul[INDEX_PhK_UC][1].x2 = _x;
        poperednij_perechid.Uc_y2 = perechid_cherez_nul[INDEX_PhK_UC][1].y2 = _y;
          
        //�������, �� ������� ������������
        fix_perechid_cherez_nul[INDEX_PhK_UC] = 0xff;
      }
      ADCs_data[I_Uc] = _y;
      
      ADCs_data_raw[I_Uc].tick = _x2;
      ADCs_data_raw[I_Uc].value = _y2;
    }
    /*****/
    
    unsigned int head_data_for_oscylograph_tmp = head_data_for_oscylograph;
    unsigned int x2, x1, delta_x; 

    if ((status_adc_read_work & DATA_VAL_READ) != 0)
    {
      /*
      ��������� ���������� ��������� ��� ��� ������������ ���'�
      */
      Fourier();
      
      //������� ��� ��� ��������� �������
      x1 = rozshyrena_vyborka.time_p = penultimate_tick_DATA_VAL;
      x2 = rozshyrena_vyborka.time_c = previous_tick_DATA_VAL;
      for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++) 
      {
        rozshyrena_vyborka.data_p[i] = rozshyrena_vyborka.data_c[i];
        rozshyrena_vyborka.data_c[i] = ADCs_data[i];
      }

      /*******************************************************
      ���������� �������������� �������
      *******************************************************/
      if (head_data_for_oscylograph_tmp != DATA_VAL_tail_data_for_oscylograph)
      {
        if (x2 > x1) delta_x = x2 - x1;
        else
        {
          long long delta_x_64 = x2 + 0x100000000 - x1;
          delta_x = delta_x_64;
        }

        while (head_data_for_oscylograph_tmp != DATA_VAL_tail_data_for_oscylograph)
        {
          unsigned int DATA_VAL_tail_data_for_oscylograph_tmp = DATA_VAL_tail_data_for_oscylograph;
    
          unsigned int x = data_for_oscylograph[DATA_VAL_tail_data_for_oscylograph_tmp].time_stemp;
        
          unsigned int dx;
          if (x >= x1) dx = x - x1;
          else
          {
            long long dx_64 = x + 0x100000000 - x1;
            dx = dx_64;
          }
          
          if (dx > delta_x) 
          {
            break;
          }

          for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++)
          {
            int y1 = rozshyrena_vyborka.data_p[i], y2 = rozshyrena_vyborka.data_c[i];
            long long y;
            if (dx <= delta_x)
            {
              y = ((long long)(y2 - y1))*((long long)dx)/((long long)delta_x) + ((long long)y1);
            }
            else
            {
              y = 0;
            }
            data_for_oscylograph[DATA_VAL_tail_data_for_oscylograph_tmp].data[I_3I0 + i] = y;
          }
          data_for_oscylograph[DATA_VAL_tail_data_for_oscylograph_tmp].DATA_fix = 0xff;

          if (++DATA_VAL_tail_data_for_oscylograph >= MAX_INDEX_DATA_FOR_OSCYLOGRAPH) DATA_VAL_tail_data_for_oscylograph = 0;
        }
      }
      /******************************************************/
      
      /*
      �������� �������� �� ���������� ������� � ��������� �������
      */
      fapch();
    
      status_adc_read_work &= (unsigned int)(~DATA_VAL_READ);

      /**************************************************/
      //����������� ����������� ��� ���������� ������ ����� ����� ������������ �������
      /**************************************************/
      control_word_of_watchdog |= WATCHDOG_MEASURE_STOP_DATA_VAL;
      /**************************************************/
    }
    
    /********************************************************
    ������� ����� ������� ������� � �������� �������� ��� ����������� ����������
    ********************************************************/
    if (head_data_for_oscylograph_tmp != tail_data_for_oscylograph)
    {
      unsigned int working_ar = false; /*�� ������������ �������, �� ���������� ��������� �� ������*/
      unsigned int index_array_ar_current_before = index_array_ar_current;
      while (
             (head_data_for_oscylograph_tmp != tail_data_for_oscylograph) &&
             (data_for_oscylograph[tail_data_for_oscylograph].DATA_fix != 0)
            )
      {
        unsigned int tail_data_for_oscylograph_tmp = tail_data_for_oscylograph;
        for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++)
        {
          int data_tmp = data_for_oscylograph[tail_data_for_oscylograph_tmp].data[i];
          
//          //�������� ����������
//          current_data[index_array_of_current_data_value++] = data_tmp;
          
          if((prescaler_ar & MASKA_BIT_FOR_PRESCALER) == 0)
          {
            //����� ������� ���������� ������� ��� ����������� ����������
            AR_WRITE(index_array_ar_current, data_tmp);
          }
        }
//        //������ ��������� �����������
//        if (index_array_of_current_data_value >= (NUMBER_ANALOG_CANALES*NUMBER_POINT*NUMBER_PERIOD_TRANSMIT)) index_array_of_current_data_value = 0;/*����� ��� �� ���� ==, ��� ��� ��������������� �� ����������� ������� � �������� >=*/

        //����� ���������� ������� ��� ����������� ����������
        unsigned int *label_to_active_functions_source = data_for_oscylograph[tail_data_for_oscylograph_tmp].active_functions;
        if((prescaler_ar & MASKA_BIT_FOR_PRESCALER) != 0)
        {
          for (unsigned int i = 0; i < N_BIG; i++)  active_functions_trg[i] = *(label_to_active_functions_source + i);
        }
        else
        {
          for (unsigned int i = 0; i < N_BIG; i++)  active_functions_trg[i] |= *(label_to_active_functions_source + i);

          unsigned short int *label_to_active_functions_trg = (unsigned short int*)active_functions_trg;
          for(unsigned int i = 0; i < NUMBER_WORD_DIGITAL_PART_AR; i++) 
          {
            AR_WRITE(index_array_ar_current, *(label_to_active_functions_trg + i));
          }
          //������ ������ ��'������� ������� ��� ����������� ����������
          if (index_array_ar_current >= SIZE_BUFFER_FOR_AR) index_array_ar_current = 0;/*����� ���� � ���� ==, ��� ��� ��������������� �� ����������� ������� � �������� >=*/

          unsigned int state_ar_record_m_tmp = data_for_oscylograph[tail_data_for_oscylograph_tmp].state_ar_record;
          if (
              (state_ar_record_m_tmp == STATE_AR_NONE_M) &&
              (
               (state_ar_record_fatfs == STATE_AR_NONE_FATFS) ||
               (state_ar_record_fatfs == STATE_AR_STOP_WRITE_FATFS) ||
               (state_ar_record_fatfs == STATE_AR_MEMORY_FULL_FATFS) ||
               (state_ar_record_fatfs == STATE_AR_BLOCK_FATFS)
              )/*�����, �� �� ����� ������ ���� �� ���� ����� ����� � ��������������� ���'���*/
             )
          {
            working_ar = false;
            //�������, ���� ���������� ��������� �� ������
            index_array_ar_tail = index_array_ar_heat = index_array_ar_current;
            tail_to_heat = current_to_tail = false;
          }
          else
          {
            working_ar = true;
            
            if (state_ar_record_m_tmp == STATE_AR_WORK_M)
            {
              /*
              ��� ����� ��� ������������� ������ ������� � �����
              */
              if (
                  (prev_state_ar_record_m == STATE_AR_NONE_M) &&
                  (state_ar_record_fatfs == STATE_AR_WAIT_TO_WRITE_FATFS)
                 )   
              {
                //�����, �� ����� �������� ���������� ����� ��� ������
              
                int difference;
                /*
                ������� 1 ������������ ���� ������� � �����,
                �� ��� ���������� ����� ���� ������������� ������ �� index_array_ar_current
                ������ ������� ������� ������� � ������ ���
                */
                /*
                ������������ ���� ������� �������� �������� ������������ ������ � 
                ��������� �������� �� � ����� "��������" ��� ����, ��� ������ �������� 
                ���� "������������", ����� �������, ������
                */
                difference = index_array_ar_current - (NUMBER_ANALOG_CANALES + NUMBER_WORD_DIGITAL_PART_AR);
                if (difference >= 0) index_array_ar_tail = difference;
                else index_array_ar_tail = difference + SIZE_BUFFER_FOR_AR;

                //������������ ���� "��������"
                difference = index_array_ar_tail - (current_settings_prt.prefault_number_periods << VAGA_NUMBER_POINT_AR)*(NUMBER_ANALOG_CANALES + NUMBER_WORD_DIGITAL_PART_AR);
                if (difference >= 0) index_array_ar_tail = difference;
                else index_array_ar_tail = difference + SIZE_BUFFER_FOR_AR;
              }

              index_array_ar_heat = index_array_ar_current;
              tail_to_heat = false;
            }
          }
          
          prev_state_ar_record_m = state_ar_record_m_tmp;
        
        }
        prescaler_ar++;
    
        data_for_oscylograph[tail_data_for_oscylograph_tmp].DATA_fix = 0;

        if (++tail_data_for_oscylograph >= MAX_INDEX_DATA_FOR_OSCYLOGRAPH) tail_data_for_oscylograph = 0;
      }

      /***
      ���������, �� �� �������� ������������      
      working_ar - �������� � ����� ���� ������� ���������� �������� ����, ���� ������� � �����
      ***/
      
      if (working_ar != false)
      {
        /***
        ������� ������ ������ �� index_array_ar_current_before;
        ***/
        
        int end_tmp = index_array_ar_current - index_array_ar_current_before;
        if (end_tmp < 0) end_tmp += SIZE_BUFFER_FOR_AR;
        
        int tail_tmp = index_array_ar_tail - index_array_ar_current_before;
        if (
            (tail_tmp < 0)
            ||
            (
             (tail_tmp == 0) &&
             (current_to_tail == false)
            ) 
           )
        {
          tail_tmp += SIZE_BUFFER_FOR_AR;
        }
        
        if (tail_tmp <= end_tmp)
        {
          current_to_tail = true;
          
          if (tail_tmp < end_tmp)
          {
            //��������� ��������, ��� ��������� ������������� 
            _SET_BIT(set_diagnostyka, ERROR_AR_OVERLOAD_BUFFER_BIT);
        
            state_ar_record_m = STATE_AR_BLOCK_M;
          }
        }
        else current_to_tail = false;
        
        diff_index_heat_tail = tail_tmp - end_tmp;
      }
      else diff_index_heat_tail = -1;
      
      diff_index_heat_tail = index_array_ar_current - index_array_ar_tail;
      if (diff_index_heat_tail < 0) diff_index_heat_tail += SIZE_BUFFER_FOR_AR;
    }
    /*******************************************************/
    
//    if ((status_adc_read_work & TEST_VAL_READ) != 0)
    {
      //�������� �������� � ����������� �������� ����� �� ��� �������
      uint32_t min_vref_adc = vref_adc[0];
      uint32_t max_vref_adc = min_vref_adc;
  
      for (size_t i = 1; i < NUMBER_ANALOG_CANALES; i++)
      {
        if (min_vref_adc > vref_adc[i]) min_vref_adc = vref_adc[i];
        if (max_vref_adc < vref_adc[i]) max_vref_adc = vref_adc[i];
      }

      //���������� ����������� ��������
      if ((min_vref_adc < 0x709) || (max_vref_adc > 0x8f5)) _SET_BIT(set_diagnostyka, ERROR_VREF_ADC_TEST_BIT);
      else _SET_BIT(clear_diagnostyka,ERROR_VREF_ADC_TEST_BIT);
    
//      status_adc_read_work &= (unsigned int)(~TEST_VAL_READ);

//      /**************************************************/
//      //����������� ����������� ��� ���������� �������� �������
//      /**************************************************/
//      control_word_of_watchdog |= WATCHDOG_MEASURE_STOP_TEST_VAL;
//      /**************************************************/
      
      /**************************************************/
      //���� ����� ����� ���������� �� ���� ������
      /**************************************************/
      if (_CHECK_SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT) != 0)
      {
        //����� ���������������� ����� � ����������� ��� �������� I2C
        _CLEAR_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
      }
      /**************************************************/
    }
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
  }

  if ((GPIO_SPI_ADC->ODR & GPIO_NSSPin_ADC) != 0)
  {
    //����� ���� �� ������� �������� control_reading_ADCs
    
    /*
    ������� � ���� ���������� ������� ������� control_reading_ADCs �� ������
    ������� ����������� �� ������� ��������� ��� ������ �� ���������
    */
    
    /*
    ����������� ��������� ����������, ��� ���� �� �������� ��� ���� ����� �����
    �� ��������� �� ����� �� ���������
    */
    __disable_interrupt();
    
    /*
    ��������, �� ���� ����� ����� �� ��������� � ���� �� ������ ������� �����
    ����� �� ���������, �� ������������ ��������� ������� ��������� � �����������
    ������� ( chip select ����������� � 1)
    */
    if (
        (adc_DATA_VAL_read == false) /*&&
        (adc_TEST_VAL_read == false)*/
       )
    {
      semaphore_adc_irq  = false;
    }
    
    /*
    ���������� ��������� ����������
    */
     __enable_interrupt();
  }
  else semaphore_adc_irq  = false;

  
  if (semaphore_adc_irq  != false)
  {
    /*
    �� ����� ���� ���� ������ � ������ �������: ���� ��� ����� �� ��� ��� �� ���������
    � ������� ��������� ������� ������� control_reading_ADCs �� �������� ����������
    �������� __disable_interrupt ��� ������� ���������.
    
    ������ � ���� ������� ������� control_reading_ADCs. �������� �� ����, ��
    chip_select ������ ����������� � ������� ���� (�� �� ������� �������� 
    if ((GPIO_SPI_ADC->ODR & GPIO_NSSPin_ADC) != 0)) � ����� semaphore_adc_irq ��
    �� ���� false, � ��� ����� ����� ������ ��������� � ����������� �������
    */
    
    control_reading_ADCs();
    
    /*
    ������� ���������. ���� �������� �� �� � ���������� ������� ����������� �����, �� ������� �� SPI
    ����������. ��� ��� ��������� ��� ����� �� �����, �� ������ ������� control_reading_ADCs
    ��� ����������� ����, �� ��� �� ��������� "������ � ����"  ������ ������
    ��������� - � �� ������� ����� ���, ���� chip_select ���� �������� ���� ������������ � ������� �����
    
    � ������������ chip_select ����� � ������� ����� ����� ���� ����� ����������� ����������� ��
    ����� SPI
    */
    semaphore_adc_irq  = false;
  }
  
//#ifdef SYSTEM_VIEWER_ENABLE
//  SEGGER_SYSVIEW_RecordExitISR();
//#endif
}
/*****************************************************/

/*****************************************************/
//����������� ����
/*****************************************************/
void calc_angle(void) 
{
  //������� ����������
  semaphore_measure_values_low1 = 1;
  for (unsigned int i = 0; i < _NUMBER_IM; i++ ) 
  {
    measurement_low[i] = measurement_middle[i];
  }
  semaphore_measure_values_low1 = 0;
              
  int ortogonal_low_tmp[2*FULL_ORT_MAX];
  
  //����������� ������� �������� ���������� ������� � ������� �������
  semaphore_measure_values_low = 1;
  for(unsigned int i = 0; i < (2*FULL_ORT_MAX); i++ )
  {
      ortogonal_low_tmp[i] = ortogonal_calc_low[i];
  } 
  //������ ������� �������� ���������� ������� � ������� �������
  semaphore_measure_values_low = 0;
  
  state_calc_phi_angle = true;
  bank_for_calc_phi_angle = (bank_for_calc_phi_angle ^ 0x1) & 0x1;

  //���������, ���� ������ ������ �� ������
  __full_ort_index index_base = FULL_ORT_Ua;

  /***
  ���������, ���� ������� ������ ����� ����� �� ������
  ***/
  __full_ort_index index_last = FULL_ORT_3U0;
  /***/
  
  int base_index_for_angle_tmp = -1;
  __full_ort_index index = index_base;
  while( index <= index_last)
  {
    unsigned int index_m;
    switch (index)
    {
    case FULL_ORT_Ua:
      {
        index_m = IM_UA;
        break;
      }
    case FULL_ORT_Ub:
      {
        index_m = IM_UB;
        break;
      }
    case FULL_ORT_Uc:
      {
        index_m = IM_UC;
        break;
      }
    case FULL_ORT_Uab:
      {
        index_m = IM_UAB;
        break;
      }
    case FULL_ORT_Ubc:
      {
        index_m = IM_UBC;
        break;
      }
    case FULL_ORT_Uca:
      {
        index_m = IM_UCA;
        break;
      }
    case FULL_ORT_3U0:
      {
        index_m = IM_3U0;
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(61);
      }
    }
  
    if (measurement_low[index_m] >= PORIG_CHUTLYVOSTI_VOLTAGE_ANGLE)
    {
      base_index_for_angle_tmp = index;
      break; //����� �� ����� while
    }
    index++;
  }
  base_index_for_angle = base_index_for_angle_tmp;
  
  if (base_index_for_angle_tmp >= 0)
  {
    //���������� �������� �������, ������� ����� ������ ������ ����
    int ortogonal_base[2] = {ortogonal_low_tmp[2*base_index_for_angle_tmp], ortogonal_low_tmp[2*base_index_for_angle_tmp + 1]};
    
#define SIN_BASE   ortogonal_base[0]
#define COS_BASE   ortogonal_base[1]

    unsigned int amplituda_base = sqrt_64((unsigned long long)((long long)SIN_BASE*(long long)SIN_BASE) + (unsigned long long)((long long)COS_BASE*(long long)COS_BASE));
    if (amplituda_base != 0)
    {
      for (__full_ort_index index_tmp = index_base; index_tmp < FULL_ORT_MAX; index_tmp++)
      {
        if (index_tmp == index)
        {
          phi_angle[bank_for_calc_phi_angle][index_tmp] = 0;
          continue;
        }
        else
        {
          unsigned int porig_chutlyvosti;
          unsigned int index_m;
          switch (index_tmp)
          {
          case FULL_ORT_Ua:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_VOLTAGE_ANGLE;
              index_m = IM_UA;
              break;
            }
          case FULL_ORT_Ub:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_VOLTAGE_ANGLE;
              index_m = IM_UB;
              break;
            }
          case FULL_ORT_Uc:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_VOLTAGE_ANGLE;
              index_m = IM_UC;
              break;
            }
          case FULL_ORT_Uab:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_VOLTAGE_ANGLE;
              index_m = IM_UAB;
              break;
            }
          case FULL_ORT_Ubc:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_VOLTAGE_ANGLE;
              index_m = IM_UBC;
              break;
            }
          case FULL_ORT_Uca:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_VOLTAGE_ANGLE;
              index_m = IM_UCA;
              break;
            }
          case FULL_ORT_3U0:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_VOLTAGE_ANGLE;
              index_m = IM_3U0;
              break;
            }
          case FULL_ORT_Ia:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_CURRENT;
              index_m = IM_IA;
              break;
            }
          case FULL_ORT_Ib:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_CURRENT;
              index_m = IM_IB;
              break;
            }
          case FULL_ORT_Ic:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_CURRENT;
              index_m = IM_IC;
              break;
            }
          case FULL_ORT_3I0:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_CURRENT;
              index_m = IM_3I0;
              break;
            }
          case FULL_ORT_3I0_r:
            {
              porig_chutlyvosti = PORIG_CHUTLYVOSTI_CURRENT;
              index_m = IM_3I0_r;
              break;
            }
          default:
            {
              //���������� ����� ����� �� ���� � ����
              total_error_sw_fixed(62);
            }
          }
      
          if (measurement_low[index_m] >= porig_chutlyvosti)
          {
            //����������� ���
#define SIN_TARGET ortogonal_low_tmp[2*index_tmp]
#define COS_TARGET ortogonal_low_tmp[2*index_tmp + 1]

            unsigned int amplituda_target = sqrt_64((unsigned long long)((long long)SIN_TARGET*(long long)SIN_TARGET) + (unsigned long long)((long long)COS_TARGET*(long long)COS_TARGET));
      
            if (amplituda_target != 0)
            {
              //���������� COS � SIN ���� ������ �� ���������
              long long cos_fi = COS_TARGET*COS_BASE + SIN_TARGET*SIN_BASE;
              long long sin_fi = -(SIN_TARGET*COS_BASE - COS_TARGET*SIN_BASE);//� ������: "���������, ��� ����", ����� �� � �� ���� ��������

#undef SIN_TARGET
#undef COS_TARGET
      
              float sin_fi_f = ( ((float)sin_fi) / ((float)amplituda_target) ) / ((float)amplituda_base);
              if (sin_fi_f > 1) sin_fi_f = 1;
              else if (sin_fi_f < -1) sin_fi_f = -1;
      
              float angle_f = asin(sin_fi_f)*180 / PI;
              int angle_int = (int)(angle_f*10); //������ ������� �� �������
              if (angle_int < 0) angle_int = -angle_int;
      
              if ((sin_fi >= 0) && (cos_fi >= 0))
              {
                //1-�� ��������
                //angle_int ���������� ��� ����
              }
              else if ((sin_fi >= 0) && (cos_fi <  0))
              {
                //2-�� ��������
                angle_int = 1800 - angle_int;
              }
              else if ((sin_fi <  0) && (cos_fi <  0))
              {
                //3-�� ��������
                angle_int = 1800 + angle_int;
              }
              else
              {
                //4-�� ��������
                angle_int = 3600 - angle_int;
              }
    
              if (angle_int >= 3600) angle_int -= 3600;
              else if (angle_int < 0) angle_int += 3600;
      
              phi_angle[bank_for_calc_phi_angle][index_tmp] = angle_int;
      
            }
            else
            {
              phi_angle[bank_for_calc_phi_angle][index_tmp] = -1;
            }

          }
          else
          {
            //������ ������������� ������� ����� ������ - ��� ������������
            phi_angle[bank_for_calc_phi_angle][index_tmp] = -1;
          }
        }
      }
    }
    else
    {
      //�������� �������� ������� ���������� �� ���������� ��� ���� ������� ���� 0 (� �����, �� ���� �������� �� ���� � ����� ��������). �� �������������.
      for (__full_ort_index index_tmp = FULL_ORT_Ua; index_tmp < FULL_ORT_MAX; index_tmp++) phi_angle[bank_for_calc_phi_angle][index_tmp] = -1;
    }

#undef SIN_BASE
#undef COS_BASE
    
  }
  else
  {
    //�� ����������� ������� ����������, ������� ����� ����� ������������� ����
    for (__full_ort_index index_tmp = FULL_ORT_Ua; index_tmp < FULL_ORT_MAX; index_tmp++) phi_angle[bank_for_calc_phi_angle][index_tmp] = -1;
  }

  state_calc_phi_angle = false;
}

/*****************************************************/

/*****************************************************/
//����������� ������ ���������
/*****************************************************/
void calc_power_and_energy(void) 
{
  //��������� ���� �� ������������� ������ ��� �������
  unsigned int bank_for_enegry_tmp = (bank_for_enegry + 1) & 0x1;
  
  int P_tmp = P_plus[bank_for_enegry_tmp] - P_minus[bank_for_enegry_tmp];
  int Q_tmp = Q_1q[bank_for_enegry_tmp] + Q_2q[bank_for_enegry_tmp] - Q_3q[bank_for_enegry_tmp] - Q_4q[bank_for_enegry_tmp];

  //����������� ������
  unsigned int clean_energy_tmp = clean_energy;
  if (clean_energy_tmp != 0) 
  {
    clean_energy = 0;

    if ((POWER_CTRL->IDR & POWER_CTRL_PIN) != (uint32_t)Bit_RESET)
    {
      //��������� ����� � EEPROM
      _SET_BIT(control_spi1_taskes, TASK_START_WRITE_ENERGY_EEPROM_BIT);
    }
    else number_minutes = PERIOD_SAVE_ENERGY_IN_MINUTES; /*���� �������� ����������, ��� ����� ���� ������ ������� �� �����*/

    //�������, �� �������� ������� ��������� ������
    information_about_clean_energy |= ((1 << USB_RECUEST)|(1 << RS485_RECUEST));
  }
  
  state_calc_energy = true;
  for (__index_energy i = INDEX_EA_PLUS; i < MAX_NUMBER_INDEXES_ENERGY; i++)
  {
    if (clean_energy_tmp != 0) energy[0][i] = 0;
    
    int power_data;
    switch (i)
    {
    case INDEX_EA_PLUS:
      {
        power_data = P_plus[bank_for_enegry_tmp];
        break;
      }
    case INDEX_EA_MINUS:
      {
        power_data = P_minus[bank_for_enegry_tmp];
        break;
      }
    case INDEX_ER_1:
      {
        power_data = Q_1q[bank_for_enegry_tmp];
        break;
      }
    case INDEX_ER_2:
      {
        power_data = Q_2q[bank_for_enegry_tmp];
        break;
      }
    case INDEX_ER_3:
      {
        power_data = Q_3q[bank_for_enegry_tmp];
        break;
      }
    case INDEX_ER_4:
      {
        power_data = Q_4q[bank_for_enegry_tmp];
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(65);
      }
    }
    
    if (power_data >= (PORIG_POWER_ENERGY*MAIN_FREQUENCY)) /*�� � power_data � ���� ������� ����������� �� 1�, �� ��������������� ���� 20��*/
    {
      double power_quantum = ((double)power_data)/(((double)MAIN_FREQUENCY)*DIV_kWh);
      double erergy_tmp = energy[0][i] + power_quantum;
      if (erergy_tmp > 999999.999) erergy_tmp = erergy_tmp - 999999.999;
      energy[0][i] = erergy_tmp;
    }
  }
  state_calc_energy = false;
  for (__index_energy i = INDEX_EA_PLUS; i < MAX_NUMBER_INDEXES_ENERGY; i++) energy[1][i] = energy[0][i];
  
  float P_float = ((float)P_tmp)/((float)MAIN_FREQUENCY);
  float Q_float = ((float)Q_tmp)/((float)MAIN_FREQUENCY);
  
  state_calc_power = true;
  bank_for_calc_power = (bank_for_calc_power ^ 0x1) & 0x1;
  P[bank_for_calc_power] = (int)P_float;
  Q[bank_for_calc_power] = (int)Q_float;
  
  //����� ���������
  if ( (P[bank_for_calc_power] != 0) || (Q[bank_for_calc_power] != 0))
  {
    float in_square_root, S_float;
    in_square_root = P_float*P_float + Q_float*Q_float;
    
    if (arm_sqrt_f32(in_square_root, &S_float) == ARM_MATH_SUCCESS)
    {
      S[bank_for_calc_power] = (unsigned int)S_float;
    }
    else
    {
      //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
      total_error_sw_fixed(53);
    }
    
    cos_phi_x1000[bank_for_calc_power] = (int)(1000.0f*P_float/S_float);
  }
  else
  {
    S[bank_for_calc_power] = 0;
    cos_phi_x1000[bank_for_calc_power] = 0;
  }
  state_calc_power = false;
  
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
