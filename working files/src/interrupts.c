#include "header.h"

#define BACKLIGHTING_ON         1
#define BACKLIGHTING_OFF        300

uint32_t time_backlighting =    BACKLIGHTING_ON*100;

/*****************************************************/
//�������� �� ������� � ������ ���������� ���� I2C
/*****************************************************/
inline ErrorStatus check_errors_i2c(void)
{
   if (I2C_GetFlagStatus(I2C, I2C_FLAG_TIMEOUT | I2C_FLAG_OVR | I2C_FLAG_AF | I2C_FLAG_ARLO | I2C_FLAG_BERR))
   {
     I2C_ClearFlag(I2C, I2C_FLAG_TIMEOUT | I2C_FLAG_OVR | I2C_FLAG_AF | I2C_FLAG_ARLO | I2C_FLAG_BERR);
     return ERROR;
   }
   else return SUCCESS;
}
/*****************************************************/

/*****************************************************/
//�������� ����� ������
/*****************************************************/
inline void check_state_key(GPIO_TypeDef* GPIOx, uint16_t mask_bit, unsigned int number_bit)
{
  if((time_set_keyboard[number_bit] == 0) && ((new_state_keyboard & (1<< number_bit)) == 0))
  {
    //������ �� ����� ������� �� ���� �����������, �� ���� ���������
    if (GPIO_ReadInputDataBit(GPIOx, mask_bit) == RESET) time_set_keyboard[number_bit]++;
  }
  else if((time_set_keyboard[number_bit] > 0) && (time_set_keyboard[number_bit] < DEREVIACIA))
  {
    //���������� �� ������� ��� ����������, � ���� ���� ������ �������������, �� ����������� �����������. �� ������ ���������, ����� �� ���������
    if(++time_set_keyboard[number_bit] == DEREVIACIA)
    {
      if (GPIO_ReadInputDataBit(GPIOx, mask_bit) == RESET) new_state_keyboard |= 1<< number_bit;
      else time_set_keyboard[number_bit] = 0;
    }
  }
  else
  {
    if (time_set_keyboard[number_bit] != 0)
    {
      //���������� �� ������ ��� ���������
     if (GPIO_ReadInputDataBit(GPIOx, mask_bit) != RESET) time_set_keyboard[number_bit] = 0;
    }
  }
}
/*****************************************************/

/*****************************************************/
//����������� �� I2C
/*****************************************************/
void I2C_EV_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif
  
  switch (I2C_GetLastEvent(I2C))
  {
  case I2C_EVENT_MASTER_MODE_SELECT:                 /* EV5 */
    {
      if((driver_i2c.action == 0) || (driver_i2c.action == 2))
      {
        /* �������� EEPROM ������ ��� ������ */
        I2C->DR = (uint8_t)(driver_i2c.device_id & ((uint8_t)(~I2C_OAR1_ADD0)));
      }
      else
      {
        /* �������� EEPROM ������ ��� ������� */
        I2C->DR = (uint8_t)(driver_i2c.device_id | I2C_OAR1_ADD0);
      }
      break;
    }
  case I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED:  /* EV6 */
    {
      //��������� ��������� ���������� �� ����
      I2C->CR2 &= (uint16_t)((~(uint32_t)I2C_IT_EVT) & 0xffff);
      
      //������� �� ����������
      unsigned int number_transmit_with_i2c;
      if(driver_i2c.action == 0)
      {
        //ϳ����������� ����� ��� �������� � ��������� ��� ������ (������)
        if (driver_i2c.device_id == EEPROM_ADDRESS)
        {
          //�������� ������ ��� EEPROM ��������� 2 �����
          Temporaty_I2C_Buffer[0] = ((driver_i2c.internal_address & 0xFF00) >> 8);
          Temporaty_I2C_Buffer[1] = (driver_i2c.internal_address & 0x00FF);
          number_transmit_with_i2c = 2;
        }
        else
        {
          //�������� ������ ��� RTC ��������� 1 ����
          Temporaty_I2C_Buffer[0] = (driver_i2c.internal_address & 0x00FF);
          number_transmit_with_i2c = 1;
        }
      }
      else if(driver_i2c.action == 2)
      {
        //ϳ����������� ����� ��� �������� � ��������� ��� ������ (������ + ������ ���)
        if (driver_i2c.device_id == EEPROM_ADDRESS)
        {
          //����� �������� ���� ��� ����� �� ����� ������� ��������� ������ ��� EEPROM
          Temporaty_I2C_Buffer[0] = ((driver_i2c.internal_address & 0xFF00) >> 8);
          Temporaty_I2C_Buffer[1] = (driver_i2c.internal_address & 0x00FF);
          for (unsigned int i= 0; i < driver_i2c.number_bytes; i++)
          {
            Temporaty_I2C_Buffer[2 + i] = *(driver_i2c.point_buffer + i);
          }
          number_transmit_with_i2c = 2 + driver_i2c.number_bytes;
        }
        else
        {
          //����� �������� ���� ��� ����� �� ����� ������� ��������� ������ ��� RTC
          Temporaty_I2C_Buffer[0] = (driver_i2c.internal_address & 0x00FF);
          for (unsigned int i= 0; i < driver_i2c.number_bytes; i++)
          {
            Temporaty_I2C_Buffer[1 + i] = *(driver_i2c.point_buffer + i);
          }
          number_transmit_with_i2c = 1 + driver_i2c.number_bytes;
        }
      }
        
      //��������� ���� DMA ���� �� ���������
      if ((DMA_StreamI2C_Tx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamI2C_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
      DMA_StreamI2C_Tx->M0AR = (uint32_t)Temporaty_I2C_Buffer;
      DMA_StreamI2C_Tx->NDTR = number_transmit_with_i2c;
        
      /* Set Last bit to have a NACK on the last received byte */
      I2C->CR2 |= I2C_CR2_LAST;
          
      //������� �� ��䳿 �� DMA_FLAG_GLI2C_Tx
      DMA_ClearFlag(DMA_StreamI2C_Tx, DMA_FLAG_TCI2C_Tx | DMA_FLAG_HTI2C_Tx | DMA_FLAG_TEII2C_Tx | DMA_FLAG_DMEII2C_Tx | DMA_FLAG_FEII2C_Tx);
        
      //���������� ��������� ���������� �� ������ DMA1_ChannelI2C_TX
      DMA_StreamI2C_Tx->CR |= DMA_IT_TC;

      /* ���������� ��� I2C �������� �� DMA */
      I2C->CR2 |= I2C_CR2_DMAEN;

      /* ���������� DMA_StreamI2C_Tx */
      DMA_StreamI2C_Tx->CR |= (uint32_t)DMA_SxCR_EN;
      
      break;
    }
  case I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED:
    {
      //��������� ��������� ���������� �� ����
      I2C->CR2 &= (uint16_t)((~(uint32_t)I2C_IT_EVT) & 0xffff);
      
      if (driver_i2c.number_bytes != 1)
      {
        //���� ������� ���� ����������� ����� �� ���� ����, �� ������� ��������� ����� DMA_FLAG_GLI2C_Rx
          
        //��������� ���� DMA ���� �� ���������
        if ((DMA_StreamI2C_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamI2C_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
        DMA_StreamI2C_Rx->M0AR = (uint32_t)driver_i2c.point_buffer;
        DMA_StreamI2C_Rx->NDTR = driver_i2c.number_bytes;
        
        //������� �� ��䳿 �� DMA_FLAG_GLI2C_Rx
        DMA_ClearFlag(DMA_StreamI2C_Rx, DMA_FLAG_TCI2C_Rx | DMA_FLAG_HTI2C_Rx | DMA_FLAG_TEII2C_Rx | DMA_FLAG_DMEII2C_Rx | DMA_FLAG_FEII2C_Rx);
        
        //���������� ��������� ���������� �� ������ DMA1_ChannelI2C_RX
        DMA_StreamI2C_Rx->CR |= DMA_IT_TC;

        /* ���������� ��� I2C �������� �� DMA */
        I2C->CR2 |= I2C_CR2_DMAEN;

        /* ���������� DMA1_ChannelI2C_RX */
        DMA_StreamI2C_Rx->CR |= (uint32_t)DMA_SxCR_EN;
      }
      else
      {
        //������� ���� ��������� ����� ������ ����� ��� DMA_FLAG_GLI2C_Rx
         
        I2C->CR1 &= (uint16_t)(~I2C_CR1_ACK);
        I2C->CR1 |= I2C_CR1_STOP;

        /* ���������� ��� I2C ��������� ���������� �� ����� � ��������� ������ �����*/
        I2C->CR2 |= I2C_IT_EVT | I2C_IT_BUF;
      }

      break;
    }
  case I2C_EVENT_MASTER_BYTE_RECEIVED_NO_BUSY:
    {
      /* ����������� ��� I2C ��������� ���������� �� ����� � ��������� ������ �����*/
      I2C->CR2 &= (uint16_t)~(I2C_IT_EVT | I2C_IT_BUF);
      *driver_i2c.point_buffer = (uint8_t)I2C->DR;

      //�����������, �� ������� ����������
      driver_i2c.state_execution = 1;
      break;
    }
  default: 
    {
      break;
    }
  }
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//��������� ���������� �� ������� �� ��� ����� �� I2C
/*****************************************************/
void I2C_ER_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif
  
  I2C->CR1 |= I2C_CR1_STOP;
  
  //��������� ������ DMA ���� ���� �������
  if ((DMA_StreamI2C_Tx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamI2C_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
  if ((DMA_StreamI2C_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamI2C_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
  
  check_errors_i2c();
  
  type_error_of_exchanging_via_i2c |= (1<<ERROR_FIX_ERRORS_BIT);
  driver_i2c.state_execution = 2;
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/


/*****************************************************/
//������������� �� ���������� �������� DMA_StreamI2C_Tx
/*****************************************************/
void DMA_StreamI2C_Tx_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif

  //����������� ��������� ���������� �� ������ DMA_StreamI2C_Tx
  DMA_StreamI2C_Tx->CR &= ~DMA_IT_TC;
  
  //��������� ���� DMA
  DMA_StreamI2C_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamI2C_Tx->NDTR = 0;
  
  /* ����������� ��� I2C �������� �� DMA */
  I2C->CR2 &= (uint16_t)(~I2C_CR2_DMAEN);

  /* ������� ���������, �� �������� ��� ���������� �������� ����� ��� DMA1 �� ������ I2C_TX */
  DMA_ClearFlag(DMA_StreamI2C_Tx, DMA_FLAG_TCI2C_Tx | DMA_FLAG_HTI2C_Tx | DMA_FLAG_TEII2C_Tx | DMA_FLAG_DMEII2C_Tx | DMA_FLAG_FEII2C_Tx);
  
  //������, ���� ������� ���� ������ ����������
  while (I2C_GetFlagStatus(I2C, I2C_FLAG_BTF) == RESET);

  if (driver_i2c.action == 0)
  {
    //���������� � ����� ����������
    driver_i2c.action = 1;
    /* �������� RESTART ����� */
    I2C->CR1 |= I2C_CR1_START;
    /* ���������� ��� I2C ��������� ���������� �� ����� */
    I2C->CR2 |= I2C_IT_EVT;
  }
  else if (driver_i2c.action == 2)
  {
    /* �������� STOP ����� */
    I2C->CR1 |= I2C_CR1_STOP;
    //�����������, �� ����� ����������
    driver_i2c.state_execution = 1;
  }
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//������������� �� ���������� �������� DMA_StreamI2C_Rx
/*****************************************************/
void DMA_StreamI2C_Rx_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif

  //����������� ��������� ���������� �� ������ DMA_StreamI2C_Rx
  DMA_StreamI2C_Rx->CR &= ~DMA_IT_TC;
  
  //��������� ���� DMA
  DMA_StreamI2C_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamI2C_Rx->NDTR = 0;
  
  /* ����������� ��� I2C �������� �� DMA */
  I2C->CR2 &= (uint16_t)(~I2C_CR2_DMAEN);

  /* ������� ���������, �� �������� ��� ���������� �������� ����� ��� DMA1 �� ������ I2C_TX */
  DMA_ClearFlag(DMA_StreamI2C_Rx, DMA_FLAG_TCI2C_Rx | DMA_FLAG_HTI2C_Rx | DMA_FLAG_TEII2C_Rx | DMA_FLAG_DMEII2C_Rx | DMA_FLAG_FEII2C_Rx);
  
  /* �������� STOP ����� */
  I2C->CR1 |= I2C_CR1_STOP;
  //�����������, �� ������� ����������
  driver_i2c.state_execution = 1;
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//����������� �� ������� TIM5, ���� ��������� ����������� �������
/*****************************************************/
void TIM5_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif
  
  if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)
  {
    /***********************************************************************************************/
    //����������� �������� �� ������ 1, ���� ������ ����������� ��� ������� ���������� ����� � ��� ����� 1
    /***********************************************************************************************/
    TIM5->SR = (uint16_t)((~(uint32_t)TIM_IT_CC1) & 0xffff); //TIM5->SR ��������� ��� ������ � �����������
    penultimate_tick_DATA_VAL = previous_tick_DATA_VAL;
    uint32_t current_tick = previous_tick_DATA_VAL = TIM5->CCR1;
    
    /*
    ����������� ����������� ��� ����������� ���������� ������ ����� 1 
    ��� ���������� ������������� ���������
    */
    adc_DATA_VAL_read = true;
    
    /***********************************************************************************************/
    //��� �������, ���� ���� ��������� "����������� �����", �� ��� ��� ���� ����������� � ����� ����
    /***********************************************************************************************/
    //�������� 䳿 �������� ����� ���, ���� ����� �� ��� ����
    if (
        ((GPIO_SPI_ADC->ODR & GPIO_NSSPin_ADC) != 0) &&
        (semaphore_adc_irq == false)  
       )   
    {
      /*
      �� � ������ �� ����� ���� (����������� �� ������� �� ����� ��������
      �� ���������� �� SPI) �� �������� ���������� ������� � ��� ��� �� �������
      */
      control_reading_ADCs();
    }
    /***********************************************************************************************/

    /***********************************************************/
    //������������ "�������� ��������� ��� ���������� �����������"
    /***********************************************************/
    uint32_t capture_new;
    unsigned int delta, step_timer_adc_tmp;
    TIM5->CCR1 = (capture_new = (current_tick + (delta = step_timer_adc_tmp = step_timer_adc)));
    
    unsigned int repeat;
    unsigned int previous_tick;
    do
    {
      repeat = 0;
      current_tick = TIM5->CNT;

      uint32_t delta_time = 0;
      if (capture_new < current_tick)
      { 
        uint64_t delta_time_64 = capture_new + 0x100000000 - current_tick;
        delta_time = delta_time_64;
      }
      else delta_time = capture_new - current_tick;

      if ((delta_time > delta) || (delta_time == 0))
      {
        if (TIM_GetITStatus(TIM5, TIM_IT_CC1) == RESET)
        {
          if (delta < step_timer_adc_tmp)
          {
            uint32_t delta_tick;
            if (current_tick < previous_tick)
            {
              uint64_t delta_tick_64 = current_tick + 0x100000000 - previous_tick;
              delta_tick = delta_tick_64;
            }
            else delta_tick = current_tick - previous_tick;
              
            delta = delta_tick + 1;
          }
          else if (delta == step_timer_adc_tmp)
            delta = 1; /*����������, ��� ���� ���������� ����������� �� ����� ������*/
          else
          {
            //���������� ����� ����� �� ���� � ����
            total_error_sw_fixed(75);
          }
          TIM5->CCR1 = (capture_new = (TIM5->CNT +  delta));
          previous_tick = current_tick;
          repeat = 0xff;
        }
      }
    }
    while (repeat != 0);
    /***********************************************************/

    /***********************************************************/
    //����������� ����������� ��� ��, �� ������ ��������� ����� ��������� 1 ��� ������������ ���'�
    /***********************************************************/
    control_word_of_watchdog |= WATCHDOG_MEASURE_START_DATA_VAL;
    /***********************************************************/
    /***********************************************************************************************/
  }
  if (TIM_GetITStatus(TIM5, TIM_IT_CC2) != RESET)
  {
    /***********************************************************************************************/
    //����������� �������� �� ������ 2, ���� ������ ����������� ��� ������� ���������� ����� � ��� ���� 1 � 2 (���������� � ������ �������� ����������� �����)
    /***********************************************************************************************/
    TIM5->SR = (uint16_t)((~(uint32_t)TIM_IT_CC2) & 0xffff); //TIM5->SR ��������� ��� ������ � �����������
    uint32_t current_tick = TIM5->CCR2;
    
    /*
    �������� 䳿 �� ���������� ����� ��� ����������� ����������
    */
    if (data_for_oscylograph[head_data_for_oscylograph].DATA_fix == 0)
    {
      //������������ �� �����������
      _SET_BIT(clear_diagnostyka, ERROR_OSCYLOJRAPH_OVERFLOW);
      
      //�������� �� ��, �� �� ������� ��������� ������ ����������� ��������� �� ��� "����������"
      if (
          (state_ar_record_fatfs == STATE_AR_WAIT_TO_STOP_WRITE_FATFS) &&  
          (state_ar_record_m != STATE_AR_BLOCK_M) &&
          (index_array_ar_tail != index_array_ar_heat)
         )
      {
        state_ar_record_fatfs = STATE_AR_WRITE_FATFS;
      }
      
      if (
          (
           (state_ar_record_m == STATE_AR_NONE_M) ||
           (state_ar_record_m == STATE_AR_WORK_STOP_M)
          ) 
          &&
          (_CHECK_SET_BIT (active_functions, RANG_WORK_A_REJESTRATOR) != 0)  
         )   
      {
        state_ar_record_m = STATE_AR_WORK_M;
        
        if (state_ar_record_fatfs == STATE_AR_NONE_FATFS) state_ar_record_fatfs = STATE_AR_WAIT_TO_WRITE_FATFS;
      }
      else if (
               (state_ar_record_m == STATE_AR_WORK_M) &&
               (_CHECK_SET_BIT (active_functions, RANG_WORK_A_REJESTRATOR) == 0)  
              )
      {
        state_ar_record_m = STATE_AR_WORK_STOP_M;
      }
      else if (
               (state_ar_record_m == STATE_AR_WORK_STOP_M) &&
               (
                (state_ar_record_fatfs == STATE_AR_WAIT_TO_STOP_WRITE_FATFS) ||
                (state_ar_record_fatfs == STATE_AR_MEMORY_FULL_FATFS) ||
                (state_ar_record_fatfs == STATE_AR_BLOCK_FATFS)
               )   
              )
      {
        state_ar_record_m = STATE_AR_NONE_M;
        if (state_ar_record_fatfs == STATE_AR_WAIT_TO_STOP_WRITE_FATFS) state_ar_record_fatfs = STATE_AR_STOP_WRITE_FATFS;
        else if (state_ar_record_fatfs == STATE_AR_MEMORY_FULL_FATFS) state_ar_record_fatfs = STATE_AR_NONE_FATFS;
      }
      else if (
               (state_ar_record_m == STATE_AR_BLOCK_M) &&
               (
                (state_ar_record_fatfs == STATE_AR_WAIT_TO_STOP_WRITE_FATFS) ||
                (state_ar_record_fatfs == STATE_AR_MEMORY_FULL_FATFS) ||
                (state_ar_record_fatfs == STATE_AR_BLOCK_FATFS)
               )   
              )
      {
        state_ar_record_m = STATE_AR_NONE_M;
        if (state_ar_record_fatfs == STATE_AR_WAIT_TO_STOP_WRITE_FATFS) state_ar_record_fatfs = STATE_AR_STOP_WRITE_FATFS;
        else if (state_ar_record_fatfs == STATE_AR_MEMORY_FULL_FATFS) state_ar_record_fatfs = STATE_AR_NONE_FATFS;

        _SET_BIT(clear_diagnostyka, ERROR_AR_OVERLOAD_BUFFER_BIT);
      }
    
      //̳��� ����
      data_for_oscylograph[head_data_for_oscylograph].time_stemp = current_tick;
      data_for_oscylograph[head_data_for_oscylograph].state_ar_record = state_ar_record_m;

      //������ �������� �������
      unsigned int *label_to_active_functions_target = data_for_oscylograph[head_data_for_oscylograph].active_functions;
      unsigned int *label_to_active_functions;
      if (copying_active_functions == 0)
        label_to_active_functions = (unsigned int*)active_functions;
      else
        label_to_active_functions = (unsigned int*)active_functions_copy;
      for (unsigned int i = 0; i < N_BIG; i++) *(label_to_active_functions_target + i) = *(label_to_active_functions + i);
      
      if (++head_data_for_oscylograph >= MAX_INDEX_DATA_FOR_OSCYLOGRAPH) head_data_for_oscylograph = 0;
    }
    else
    {
      //������������ �����������
      _SET_BIT(set_diagnostyka, ERROR_OSCYLOJRAPH_OVERFLOW);
    }
    /***/

//    /*
//    ����������� ����������� ��� ����������� ���������� ������ �������� �������
//    */
//    adc_TEST_VAL_read = true;
    
    /***********************************************************/
    //������������ "�������� ��������� ��� ���������� �����������"
    /***********************************************************/
    uint32_t capture_new;
    unsigned int delta;
    TIM5->CCR2 = (capture_new = (current_tick + (delta = TIM5_CCR1_2_VAL)));
    
    unsigned int repeat;
    unsigned int previous_tick;
    do
    {
      repeat = 0;
      current_tick = TIM5->CNT;

      uint32_t delta_time = 0;
      if (capture_new < current_tick)
      {
        uint64_t delta_time_64 = capture_new + 0x100000000 - current_tick;
        delta_time = delta_time_64;
      }
      else delta_time = capture_new - current_tick;

      if ((delta_time > delta) || (delta_time == 0))
      {
        if (TIM_GetITStatus(TIM5, TIM_IT_CC2) == RESET)
        {
          if (delta < TIM5_CCR1_2_VAL)
          {
            uint32_t delta_tick;
            if (current_tick < previous_tick)
            {
              uint64_t delta_tick_64 = current_tick + 0x100000000 - previous_tick;
              delta_tick = delta_tick_64;
            }
            else delta_tick = current_tick - previous_tick;
              
            delta = delta_tick + 1;
          }
          else if (delta == TIM5_CCR1_2_VAL)
            delta = 1; /*����������, ��� ���� ���������� ����������� �� ����� ������*/
          else
          {
            //���������� ����� ����� �� ���� � ����
            total_error_sw_fixed(77);
          }
          TIM5->CCR2 = (capture_new = (TIM5->CNT +  delta));
          previous_tick = current_tick;
          repeat = 0xff;
        }
      }
    }
    while (repeat != 0);
    /***********************************************************/

//    /***********************************************************/
//    //����������� ����������� ��� ��, �� ������ ��������� ��� ����
//    /***********************************************************/
//    control_word_of_watchdog |= WATCHDOG_MEASURE_START_TEST_VAL;
//    /***********************************************************/
    /***********************************************************************************************/
  }
  
//  //�������� 䳿 �������� ����� ���, ���� ����� �� ��� ����
//  if (
//      ((GPIO_SPI_ADC->ODR & GPIO_NSSPin_ADC) != 0) &&
//      (semaphore_adc_irq == false)  
//     )   
//  {
//    /*
//    �� � ������ �� ����� ���� (����������� �� ������� �� ����� ��������
//    �� ���������� �� SPI) �� �������� ���������� ������� � ��� ��� �� �������
//    */
//    control_reading_ADCs();
//  }
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//����������� �� ������� TIM4, ���� ��������� ����������, ��������� � DataFlash
/*****************************************************/
void TIM4_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif
  
  if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)
  {
    /***********************************************************************************************/
    //����������� �������� �� ������ 3, ���� ������ ����������� � �������, ���� ���������� �����������, ��� ���������� ���������� ������� �� RS-485
    /***********************************************************************************************/
    TIM4->SR = (uint16_t)((~(uint32_t)TIM_IT_CC3) & 0xffff);
    uint16_t current_tick = TIM4->CNT;

    //������ ����, �� �� ���������� ���������� �������� �������� ��������� ������ ������
    mark_current_tick_RS_485 = 0;

    /******/
    //���������� ��������� RS-485 ����� ���� ��������� DMA ��� �������, �� ������ ����� ����� ������ ���������� ������
    /******/
    if ((DMA_StreamRS485_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0)
    {
      RxBuffer_RS485_count = BUFFER_RS485 - (uint16_t)(DMA_StreamRS485_Rx->NDTR);
      current_tick = TIM4->CNT; /*������� ���, ���� �� ����������� ������� ��������� ���� ������� ����� ������ ��������� ����� ��� ��������� �����������*/
    
      if( RxBuffer_RS485_count != 0 )
      {
        if (RxBuffer_RS485_count_previous == RxBuffer_RS485_count)
        {
          //��������� ����� �����

          //��������� ���� DMA
          if ((DMA_StreamRS485_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamRS485_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;

          //������� ������ ������� � ����������, �� ���� �������
          unsigned int error_status = USART_RS485->SR &  (USART_FLAG_ORE | USART_FLAG_NE | USART_FLAG_FE | USART_FLAG_PE);
          if (error_status == 0)
          {
            //������� ����
            
            //���������� ������
            unsigned int global_requect;
            if(
               ((global_requect = (RxBuffer_RS485[0] == BROADCAST_ADDRESS_MODBUS_RTU)) != 0) ||
               (RxBuffer_RS485[0] == current_settings.address)
              )   
            {
              //������ ��������� ����� ���� ������ � ��������� �� �������� ������� - ���� �� ���������� ����� ��� ����� �� (�� ������������� ���������)

              if (global_requect == 0) time_last_receive_byte = TIM4->CNT;

              //������������ ����, �� �� ���������� ���������� �������� �������� ��������� ������ ������
              mark_current_tick_RS_485 = 0xff;
            }
            else
            {
              //������ �� ������� - �������� ��������� ��
              restart_monitoring_RS485();
            }
          }
          else
          {
            //���������� �������  - �������� ��������� ��
            restart_monitoring_RS485();
          }
        }
        else
        {
          //����� �� ���䳿 �������
          RxBuffer_RS485_count_previous = RxBuffer_RS485_count;
        }
      }
    }
    /******/

    /***********************************************************/
    //������������ "�������� ��������� ��� ���������� �����������"
    /***********************************************************/
    if (number_bits_rs_485_waiting < 10) calculate_namber_bit_waiting_for_rs_485();
    uint16_t /*current_tick = TIM4->CNT,*/ capture_new;
    unsigned int delta, step_tmp;
    TIM4->CCR3 = (capture_new = (current_tick + (delta = step_tmp =(TIM4_CCR3_VAL*number_bits_rs_485_waiting))));
    
    unsigned int repeat;
    unsigned int previous_tick;
    do
    {
      repeat = 0;
      current_tick = TIM4->CNT;

      uint32_t delta_time = 0;
      if (capture_new < current_tick)
        delta_time = capture_new + 0x10000 - current_tick;
      else delta_time = capture_new - current_tick;

      if ((delta_time > delta) || (delta_time == 0))
      {
        if (TIM_GetITStatus(TIM4, TIM_IT_CC3) == RESET)
        {
          if (delta < step_tmp)
          {
            uint32_t delta_tick;
            if (current_tick < previous_tick)
              delta_tick = current_tick + 0x10000 - previous_tick;
            else delta_tick = current_tick - previous_tick;
              
            delta = delta_tick + 1;
          }
          else if (delta == step_tmp)
            delta = 1; /*����������, ��� ���� ����������� ����������� �� ����� ������*/
          else
          {
            //���������� ����� ����� �� ���� � ����
            total_error_sw_fixed(48);
          }
          TIM4->CCR3 = (capture_new = (TIM4->CNT +  delta));
          previous_tick = current_tick;
          repeat = 0xff;
        }
      }
    }
    while (repeat != 0);
    /***********************************************************/

    /***********************************************************/
    //����������� ����������� ��� ��, �� ����� 3 TIM4 ������, �� ������� �� �������� ������� ���������� RS-485
    /***********************************************************/
    control_word_of_watchdog |= WATCHDOG_RS485;
    /***********************************************************/

    /***********************************************************************************************/
  }
  else if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)
  {
    /***********************************************************************************************/
    //����������� �������� �� ������ 1, ���� ������ ����������� ���� 10 ��, ��� �������������� ���������
    /***********************************************************************************************/
    TIM4->SR = (uint16_t)((~(uint32_t)TIM_IT_CC1) & 0xffff);
    uint16_t current_tick = TIM4->CCR1;
  
    /***********************************************************/
    //���������� ��� ���������
    /***********************************************************/
    /***************************/
    //���������� �� �����
    /***************************/
    //����� - 1
    GPIO_ResetBits(KEYBOARD, KEYBOARD_SW_1_PIN);
    check_state_key(KEYBOARD_SW_A, KEYBOARD_SW_A_PIN, BIT_KEY_ENTER);
    check_state_key(KEYBOARD_SW_B, KEYBOARD_SW_B_PIN, BIT_KEY_DOWN);
    check_state_key(KEYBOARD_SW_C, KEYBOARD_SW_C_PIN, BIT_KEY_RIGHT);
    check_state_key(KEYBOARD_SW_D, KEYBOARD_SW_D_PIN, BIT_KEY_C);
    GPIO_SetBits(KEYBOARD, KEYBOARD_SW_1_PIN);
    
    //������ �������� ��������
    for(unsigned int delay_local = 0; delay_local < 100; delay_local++) __no_operation();
    
    //����� - 2
    GPIO_ResetBits(KEYBOARD, KEYBOARD_SW_2_PIN);
    check_state_key(KEYBOARD_SW_A, KEYBOARD_SW_A_PIN, BIT_KEY_ESC);
    check_state_key(KEYBOARD_SW_B, KEYBOARD_SW_B_PIN, BIT_KEY_LEFT);
    check_state_key(KEYBOARD_SW_C, KEYBOARD_SW_C_PIN, BIT_KEY_UP);
    check_state_key(KEYBOARD_SW_D, KEYBOARD_SW_D_PIN, BIT_KEY_I);
    GPIO_SetBits(KEYBOARD, KEYBOARD_SW_2_PIN);

    //������ �������� ��������
    for(unsigned int delay_local = 0; delay_local < 100; delay_local++) __no_operation();

    //����� - 3
    GPIO_ResetBits(KEYBOARD, KEYBOARD_SW_3_PIN);
    check_state_key(KEYBOARD_SW_A, KEYBOARD_SW_A_PIN, BIT_KEY_1);
    check_state_key(KEYBOARD_SW_B, KEYBOARD_SW_B_PIN, BIT_KEY_2);
    check_state_key(KEYBOARD_SW_C, KEYBOARD_SW_C_PIN, BIT_KEY_3);
    check_state_key(KEYBOARD_SW_D, KEYBOARD_SW_D_PIN, BIT_KEY_O);
    GPIO_SetBits(KEYBOARD, KEYBOARD_SW_3_PIN);

    //������ �������� ��������
    for(unsigned int delay_local = 0; delay_local < 100; delay_local++) __no_operation();

    //����� - 4
    GPIO_ResetBits(KEYBOARD, KEYBOARD_SW_4_PIN);
    check_state_key(KEYBOARD_SW_A, KEYBOARD_SW_A_PIN, BIT_KEY_4);
    check_state_key(KEYBOARD_SW_B, KEYBOARD_SW_B_PIN, BIT_KEY_5);
    check_state_key(KEYBOARD_SW_C, KEYBOARD_SW_C_PIN, BIT_KEY_6);
    GPIO_SetBits(KEYBOARD, KEYBOARD_SW_4_PIN);
    /***************************/
  
    uint32_t  maska_all_keys = (uint32_t)(
                                          (1<<BIT_KEY_ENTER) |
                                          (1<<BIT_KEY_DOWN) |
                                          (1<<BIT_KEY_RIGHT) |
                                          (1<<BIT_KEY_ESC) |
                                          (1<<BIT_KEY_LEFT) |
                                          (1<<BIT_KEY_UP) |
                                          (1<<BIT_KEY_1) |
                                          (1<<BIT_KEY_2) |
                                          (1<<BIT_KEY_3) |
                                          (1<<BIT_KEY_4) |
                                          (1<<BIT_KEY_5) |
                                          (1<<BIT_KEY_6) |
                                          (1<<BIT_KEY_C) |
                                          (1<<BIT_KEY_I) |
                                          (1<<BIT_KEY_O)
                                         );
    if ((LCD_BL->ODR & LCD_BL_PIN) != (uint32_t)Bit_RESET)
    {
      //ϳ������ ��������
      if ((new_state_keyboard & maska_all_keys) != 0) time_backlighting = BACKLIGHTING_OFF*100;
      if (
           (time_backlighting > 0) && /*������� ������ � �������� ��������*/
           (--time_backlighting == 0) /*��������� ��� ������ ������� ��� ������� ���� ������ �������*/
         )
      {
        //����� ���������� �������
        LCD_BL->BSRRH = LCD_BL_PIN;
      }
      
    }
    else
    {
      //ϳ������ ��������
      if (
          ((new_state_keyboard & maska_all_keys) != 0) /*����� ��������� ������� �� ����������� ������*/
          ||  
          (
           (time_backlighting > 0)  && /*������� ������ � �������� ��������*/
           (--time_backlighting == 0) && /*��������� ��� ������ ������� ��� ������� ���� ������ �������*/
           ((POWER_CTRL->IDR & POWER_CTRL_PIN) != (uint32_t)Bit_RESET) /*� ���������� ��������*/
          )   
         )
      {
        //����� ��������� ������� ���� ������ �������
        LCD_BL->BSRRL = LCD_BL_PIN;
        time_backlighting = BACKLIGHTING_OFF*100;

        uint32_t  maska_wake_up_keys = (uint32_t)(
                                                  (1<<BIT_KEY_ENTER) |
                                                  (1<<BIT_KEY_DOWN) |
                                                  (1<<BIT_KEY_RIGHT) |
                                                  (1<<BIT_KEY_ESC) |
                                                  (1<<BIT_KEY_LEFT) |
                                                  (1<<BIT_KEY_UP)
                                                 );
        new_state_keyboard &= (unsigned int)(~maska_wake_up_keys);
      }
    }

    /***************************/
    //������� ��������� �������������� ������
    /***************************/
    new_state_keyboard_for_db |= (unsigned int)(new_state_keyboard & (
                                                                      (1<<BIT_KEY_1) |
                                                                      (1<<BIT_KEY_2) |
                                                                      (1<<BIT_KEY_3) |
                                                                      (1<<BIT_KEY_4) |
                                                                      (1<<BIT_KEY_5) |
                                                                      (1<<BIT_KEY_6) |
                                                                      (1<<BIT_KEY_C) |
                                                                      (1<<BIT_KEY_I) |
                                                                      (1<<BIT_KEY_O)
                                                                      ));/*new_state_keyboard ��������� � ���� ���������� � ������� main_manu_function, ���� ��� ������ ������������ �������������� ������ ������������ ��� ������ �������� ����� ���� �����*/
    new_state_keyboard        &= (unsigned int)(~(
                                                  (1<<BIT_KEY_1) |
                                                  (1<<BIT_KEY_2) |
                                                  (1<<BIT_KEY_3) |
                                                  (1<<BIT_KEY_4) |
                                                  (1<<BIT_KEY_5) |
                                                  (1<<BIT_KEY_6) |
                                                  (1<<BIT_KEY_C) |
                                                  (1<<BIT_KEY_I) |
                                                  (1<<BIT_KEY_O)
                                                 ));
    
    //�������� �� ��, �� ��� ������ �������� �� �� ���������
    if (time_set_keyboard[BIT_KEY_1] == 0) new_state_keyboard_for_db &= (unsigned int)(~(1<<BIT_KEY_1));
    if (time_set_keyboard[BIT_KEY_2] == 0) new_state_keyboard_for_db &= (unsigned int)(~(1<<BIT_KEY_2));
    if (time_set_keyboard[BIT_KEY_3] == 0) new_state_keyboard_for_db &= (unsigned int)(~(1<<BIT_KEY_3));
    if (time_set_keyboard[BIT_KEY_4] == 0) new_state_keyboard_for_db &= (unsigned int)(~(1<<BIT_KEY_4));
    if (time_set_keyboard[BIT_KEY_5] == 0) new_state_keyboard_for_db &= (unsigned int)(~(1<<BIT_KEY_5));
    if (time_set_keyboard[BIT_KEY_6] == 0) new_state_keyboard_for_db &= (unsigned int)(~(1<<BIT_KEY_6));
    if (time_set_keyboard[BIT_KEY_C] == 0) new_state_keyboard_for_db &= (unsigned int)(~(1<<BIT_KEY_C));
    if (time_set_keyboard[BIT_KEY_I] == 0) new_state_keyboard_for_db &= (unsigned int)(~(1<<BIT_KEY_I));
    if (time_set_keyboard[BIT_KEY_O] == 0) new_state_keyboard_for_db &= (unsigned int)(~(1<<BIT_KEY_O));

    if ((new_state_keyboard_for_db & ((1<<BIT_KEY_1)|(1<<BIT_KEY_2)|(1<<BIT_KEY_3)|(1<<BIT_KEY_4)|(1<<BIT_KEY_5)|(1<<BIT_KEY_6)|(1<<BIT_KEY_C)|(1<<BIT_KEY_I)|(1<<BIT_KEY_O))) != 0)
    {
      if (
          ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_FB_ACTIVATION) == 0)
          ||  
          ((new_state_keyboard & (1<<BIT_KEY_ENTER)) != 0)
         )   
      {
        /**************************
        ��������� ������������� ������ ����������� ������������� ������ ENTER  
        �������� ������ ���������� �� ���������� �����, ��� �� �������������  � ������ �������
        ***************************/
        mutex_buttons = true;
        pressed_buttons    |= (new_state_keyboard_for_db & ((1<<BIT_KEY_1)|(1<<BIT_KEY_2)|(1<<BIT_KEY_3)|(1<<BIT_KEY_4)|(1<<BIT_KEY_5)|(1<<BIT_KEY_6)|(1<<BIT_KEY_C)|(1<<BIT_KEY_I)|(1<<BIT_KEY_O))) >> BIT_KEY_1;
        mutex_buttons = false;
        new_state_keyboard_for_db &= (unsigned int)(~((1<<BIT_KEY_1)|(1<<BIT_KEY_2)|(1<<BIT_KEY_3)|(1<<BIT_KEY_4)|(1<<BIT_KEY_5)|(1<<BIT_KEY_6)|(1<<BIT_KEY_C)|(1<<BIT_KEY_I)|(1<<BIT_KEY_O)));
        /***************************/

        if ((current_settings.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_FB_ACTIVATION) != 0)
        {
          /**************************
          ������ ENTER ��� ���������� ���� ������� ��������� ������, ���� 
          ������ �����������, �� ���� ���� ���������, ��� �� ���������� ��
          ������� ����������� ������ ������ ���� �� ����������� ������ ENTER
          ***************************/
          new_state_keyboard &= (unsigned int)(~(1<<BIT_KEY_ENTER));
          /***************************/
        }
      }
    }
    /***************************/
    /***********************************************************/
  
    /***********************************************************/
    //���������� �� ����� ��������� � ����� 1 � ��� �� �����
    /***********************************************************/
    if (((current_ekran.current_level == EKRAN_TIME) && (current_ekran.edition == 0)) ||
        ((current_ekran.current_level == EKRAN_TITLES_DIGITAL_REGISTRATOR) && (rewrite_ekran_once_more > 0)) ||
        ((current_ekran.current_level == EKRAN_TITLES_PR_ERR_REGISTRATOR ) && (rewrite_ekran_once_more > 0)) ||
        ((current_ekran.current_level == EKRAN_DATA_LADEL_AR             ) && (rewrite_ekran_once_more > 0)) ||
        (current_ekran.current_level == EKRAN_LIST_ANALOG_REGISTRATOR_RECORDS       )   ||
        (current_ekran.current_level == EKRAN_LIST_DIGITAL_REGISTRATOR_RECORDS      )   ||
        (current_ekran.current_level == EKRAN_LIST_REGISTRATOR_PROGRAM_ERROR_RECORDS)   ||
        (current_ekran.current_level == EKRAN_MEASURMENT_CURRENT      ) ||
        (current_ekran.current_level == EKRAN_MEASURMENT_VOLTAGE_PHASE) ||
        (current_ekran.current_level == EKRAN_MEASURMENT_VOLTAGE_LINE ) ||
        (current_ekran.current_level == EKRAN_MEASURMENT_FREQUENCY    ) ||
        (current_ekran.current_level == EKRAN_MEASURMENT_ANGLE        ) ||
        (current_ekran.current_level == EKRAN_MEASURMENT_POWER        ) ||
        (current_ekran.current_level == EKRAN_ENERGY                  ) ||
        (current_ekran.current_level == EKRAN_MEASURMENT_RESISTANCE   ) ||
        (current_ekran.current_level == EKRAN_STATE_INPUTS)   ||
        (current_ekran.current_level == EKRAN_STATE_OUTPUTS)  ||
        (current_ekran.current_level == EKRAN_DIAGNOSTYKA)    ||
        (current_ekran.current_level == EKRAN_RESURS) ||
        (current_ekran.current_level == EKRAN_VIDKLUCHENNJA)
       )
    {
      if(++time_rewrite > MAX_TIME_REWRITE_EKRAN)
      {
        time_rewrite = 0;
        new_state_keyboard |= (1<<BIT_REWRITE);
      }
    }
    /***********************************************************/

    /***********************************************************/
    //˳������� ������� + �������� �������� ��� � �������
    /***********************************************************/
    static unsigned int number_ticks_for_OF_bit_reset;

    if (etap_reset_of_bit == ETAP_CLEAR_OF_ST_START_WAITING_5S)
    {
      etap_reset_of_bit = ETAP_CLEAR_OF_ST_WAITING_5S;
      number_ticks_for_OF_bit_reset = 0;
    }
    else if (etap_reset_of_bit == ETAP_CLEAR_OF_ST_WAITING_5S)
    {
      number_ticks_for_OF_bit_reset++;
      if (number_ticks_for_OF_bit_reset > 500) etap_reset_of_bit = ETAP_CLEAR_OF_WRITE_OF_0;
    }
    
    if(++number_inputs_for_fix_one_second >= 100)
    {
      
      //������ ������� ���� � RTC ����� ��� �������� ���������� ���������
      //��� ����� ����������� �� ���������� ��������� ������� ��������, ��� ����������������� � ������� ����������� �������
      if ((state_spi1_task & STATE_SETTINGS_EEPROM_GOOD) != 0) 
      {
        _SET_BIT(control_i2c_taskes, TASK_START_READ_RTC_BIT);
        _SET_BIT(control_i2c_taskes, TASK_BLK_OPERATION_BIT);
      }
      
      //�������� ��� � ������� ������������ �������� ������
      periodical_tasks_TEST_SETTINGS            = periodical_tasks_TEST_USTUVANNJA          = periodical_tasks_TEST_TRG_FUNC                = 
      periodical_tasks_TEST_INFO_REJESTRATOR_AR = periodical_tasks_TEST_INFO_REJESTRATOR_DR = periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR = 
      periodical_tasks_TEST_RESURS              = periodical_tasks_TEST_FLASH_MEMORY        = periodical_tasks_CALCULATION_ANGLE            = true;
      
      number_inputs_for_fix_one_second = 0;
      
      if(++number_seconds >= 60)
      {
        number_seconds = 0;
        if((POWER_CTRL->IDR & POWER_CTRL_PIN) != (uint32_t)Bit_RESET)
        {
          if (state_ar_record_fatfs != STATE_AR_WRITE_FATFS) reinit_LCD = true; /*������������ ���������� ������, ���� �� ��� ����� ����������� ����������*/
          
          if (++number_minutes >= PERIOD_SAVE_ENERGY_IN_MINUTES)
          {
            number_minutes = 0;
          
            //��������� ����� � EEPROM
            _SET_BIT(control_spi1_taskes, TASK_START_WRITE_ENERGY_EEPROM_BIT);
          }
        }
      }
      
      //������ � �������� ���������� ����� ��� �����������
      if (
          (restart_timeout_idle_new_settings != 0) ||
          (_CHECK_SET_BIT(active_functions, RANG_SETTINGS_CHANGED) == 0)  
         )
      {
        timeout_idle_new_settings  = 0;
        if (restart_timeout_idle_new_settings != 0) restart_timeout_idle_new_settings = false;
      }
      else 
      { 
        if (timeout_idle_new_settings < (current_settings.timeout_idle_new_settings)) timeout_idle_new_settings++;
      }

      //������ � ��������� ������� USB
      if ((restart_timeout_interface & (1 << USB_RECUEST  )) != 0) 
      {
        timeout_idle_USB  = 0;
        restart_timeout_interface &= (unsigned int)(~(1 << USB_RECUEST));
      }
      else 
      {
        if (timeout_idle_USB < (current_settings.timeout_deactivation_password_interface_USB)) timeout_idle_USB++;
      }

      //������ � ��������� ������� RS-485
      if ((restart_timeout_interface & (1 << RS485_RECUEST)) != 0) 
      {
        timeout_idle_RS485 = 0;
        restart_timeout_interface &= (unsigned int)(~(1 << RS485_RECUEST));
      }
      else 
      {
        if (timeout_idle_RS485 < (current_settings.timeout_deactivation_password_interface_RS485)) timeout_idle_RS485++;
      }

      //������
      if (restart_resurs_count == 0)
      {
        resurs_global = resurs_temp;
        resurs_temp = 0;
        if (resurs_global < resurs_global_min) resurs_global_min = resurs_global;
        if (resurs_global > resurs_global_max) resurs_global_max = resurs_global;
      }
      else
      {
        restart_resurs_count = 0;
        
        resurs_global = 0;
        resurs_temp = 0;
        resurs_global_min = 0xffffffff;
        resurs_global_max = 0;
      }
    }
    /***********************************************************/

    /***********************************************************/
    //�������� ������� � ����� ������
    /***********************************************************/
    if (copying_time == 0)
    {
      //�� ����� ������ �� ��� ������������ ��� ���������� ����

      /*
      �������, �� �����  ������ �������� ��� (��� ����� ������������ ���
      ������� � ��������� �� ���� ��������, �� �� � ����������, � �� ��������
      ����������� � �������� ������; ���� �� ����� ���� ��� ��������)
      */
      copying_time = 2; 
      
      unsigned int rozrjad = 0;
      for(unsigned int i = 0; i < 7; i++)
      {
        unsigned int data_tmp = 10*((time[i] >> 4) & 0xf) + (time[i] & 0xf);
        
        unsigned int porig;
        switch (i)
        {
        case 0:
        case 6:
          {
            porig = 99;
            break;
          }
        case 1:
        case 2:
          {
            porig = 59;
            break;
          }
        case 3:
          {
            porig = 23;
            break;
          }
        case 4:
          {
            unsigned int month = 10*((time[5] >> 4) & 0xf) + (time[5] & 0xf);
            if (month == 0x2/*BCD*/)
            {
              unsigned int year = 10*((time[6] >> 4) & 0xf) + (time[6] & 0xf);
              if (
                  ((year & 0x3) == 0) && /*������ �� ������ �� 4*/
                  (
                   ((year % 100) != 0) /* ||
                   ((year % 400) == 0) */ /*�� ������� 100 ��� ������� 400*/
                  )  
                 )
              {
                porig = 29;
              } 
              else
              {
                porig = 28;
              }
            }
            else if (
                     ((month <= 0x7/*BCD*/) && ( (month & 1))) ||
                     ((month >  0x7/*BCD*/) && (!(month & 1)))
                    ) 
            {
              porig = 31;
            }
            else
            {
              porig = 30;
            }
            break;
          }
        case 5:
          {
            porig = 12;
            break;
          }
        default:
          {
            //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
            total_error_sw_fixed(103);
          }
        }
        
        if ((++data_tmp) > porig)
        {
          rozrjad = 1;
          
          if ((i == 4) || (i == 5)) data_tmp = 1;
          else data_tmp = 0;
        }
        else rozrjad = 0;
        
        unsigned int high = data_tmp / 10;
        unsigned int low = data_tmp - high*10;
        time[i] = (high << 4) | low;
        
        if (rozrjad == false) break;
      }

      copying_time = 1; 
      
      for(unsigned int i = 0; i < 7; i++) time_copy[i] = time[i];
      
      copying_time = 0; 
    }
    /***********************************************************/

    /***********************************************************/
    //����������� ����������� ��� ��, �� ����� 1 TIM4, �� ������� �� �������� ������� ��������� ������
    /***********************************************************/
    if (watchdog_l2)
    {
      GPIO_WriteBit(
                    GPIO_EXTERNAL_WATCHDOG,
                    GPIO_PIN_EXTERNAL_WATCHDOG,
                    (BitAction)(1 - GPIO_ReadOutputDataBit(GPIO_EXTERNAL_WATCHDOG, GPIO_PIN_EXTERNAL_WATCHDOG))
                   );
    }
    else control_word_of_watchdog |= WATCHDOG_KYYBOARD;
    /***********************************************************/

    /***********************************************************/
    //������������ "�������� ��������� ��� ���������� �����������"
    /***********************************************************/
    uint16_t capture_new;
    unsigned int delta;
    TIM4->CCR1 = (capture_new = (current_tick + (delta = TIM4_CCR1_VAL)));
    
    unsigned int repeat;
    unsigned int previous_tick;
    do
    {
      repeat = 0;
      current_tick = TIM4->CNT;

      uint32_t delta_time = 0;
      if (capture_new < current_tick)
        delta_time = capture_new + 0x10000 - current_tick;
      else delta_time = capture_new - current_tick;

      if ((delta_time > delta) || (delta_time == 0))
      {
        if (TIM_GetITStatus(TIM4, TIM_IT_CC1) == RESET)
        {
          if (delta < TIM4_CCR1_VAL)
          {
            uint32_t delta_tick;
            if (current_tick < previous_tick)
              delta_tick = current_tick + 0x10000 - previous_tick;
            else delta_tick = current_tick - previous_tick;
              
            delta = delta_tick + 1;
          }
          else if (delta == TIM4_CCR1_VAL)
            delta = 1; /*����������, ��� ���� ���������� ����������� �� ����� ������*/
          else
          {
            //���������� ����� ����� �� ���� � ����
            total_error_sw_fixed(79);
          }
          TIM4->CCR1 = (capture_new = (TIM4->CNT +  delta));
          previous_tick = current_tick;
          repeat = 0xff;
        }
      }
    }
    while (repeat != 0);
    /***********************************************************/

    /***********************************************************************************************/
  }
  else if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)
  {
    /***********************************************************************************************/
    //����������� �������� �� ������ 2, ���� ������ ����������� ���� 1 ��, ��� ��������������� ��������� ����������� DataFlash � ���������� ����� ������ ���������� ���������� ����
    /***********************************************************************************************/
    TIM4->SR = (uint16_t)((~(uint32_t)TIM_IT_CC2) & 0xffff);
    uint16_t current_tick = TIM4->CCR2;
    
    /***********************************************************/
    //���������� ����������� ������� ���������� ���������� ����
    /***********************************************************/
    if (
        ((clean_rejestrators & CLEAN_PR_ERR) != 0)
        &&  
        (
         (control_tasks_dataflash & (
                                     TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH    |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB   |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485 |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU
                                    )
         ) == 0
        )
       )   
    {
      //���������� ������� �������� ��������� ���������� ����

      //����������� ������� ������ ���� ��������� � EEPROM
      _SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);

      //������� ��������� ���������� �� ��������� ���������� �������
      info_rejestrator_pr_err.next_address = MIN_ADDRESS_PR_ERR_AREA;
      info_rejestrator_pr_err.saving_execution = 0;
      info_rejestrator_pr_err.number_records = 0;

      //�������, �� ����� ������ �� ��������
      number_record_of_pr_err_into_menu  = 0xffff;
      number_record_of_pr_err_into_USB   = 0xffff;
      number_record_of_pr_err_into_RS485 = 0xffff;

      //������ ������� ������� ���������� ���������� ����
      clean_rejestrators &= (unsigned int)(~CLEAN_PR_ERR);
    }
    /***********************************************************/
    
    /***********************************************************/
    //��������� ��������� ��������� �� �������� DataFlash
    /***********************************************************/
    if (
        (mutex_spi1 == false) &&
        (state_execution_spi1 < 0) &&
        (((DMA_StreamSPI_EDF_Tx->CR & (uint32_t)DMA_SxCR_EN) == 0) && ((DMA_StreamSPI_EDF_Rx->CR & (uint32_t)DMA_SxCR_EN) == 0))
       )   
    {
      if ((number_chip_dataflsh_exchange >= INDEX_DATAFLASH_1) && (number_chip_dataflsh_exchange <= INDEX_DATAFLASH_2))
      {
        if (error_into_spi_df == 0)
        {
          //�� ���� �����������, �� ��� ��������� �������� ������� �������
        
          //����������, �� � ������� � ��������� ���������� ��������� ���������� ����
          if (

              /***
              ������ ��� ��� �������� ��� � ������� �����������
              ***/
              (_CHECK_SET_BIT(    diagnostyka, EVENT_START_SYSTEM_BIT       ) == 0) &&
              (_CHECK_SET_BIT(set_diagnostyka, EVENT_START_SYSTEM_BIT       ) == 0) &&
              (_CHECK_SET_BIT(    diagnostyka, EVENT_RESTART_SYSTEM_BIT     ) == 0) &&
              (_CHECK_SET_BIT(set_diagnostyka, EVENT_RESTART_SYSTEM_BIT     ) == 0) &&
              (_CHECK_SET_BIT(    diagnostyka, EVENT_SOFT_RESTART_SYSTEM_BIT) == 0) &&
              (_CHECK_SET_BIT(set_diagnostyka, EVENT_SOFT_RESTART_SYSTEM_BIT) == 0) &&
              /***/
              ((POWER_CTRL->IDR & POWER_CTRL_PIN) != (uint32_t)Bit_RESET) && /*�� ����� ������ �� ���� ����� �������� �������� ��������*/ 
              /***/
              (temporary_block_writing_records_pr_err_into_DataFlash     == 0) && /*���������� ������ ������������ ������ ���������� ���������� ���� � ��������� DataFlash1*/
              ((control_tasks_dataflash  & 0xffff)                       == 0)    /*�������� ����� � ��������� ���������� ���� ����� ���, ���� ����� ����� � ���� ���� ��� ������ � DataFlash1*/
             )
          {
            unsigned int head = head_fifo_buffer_pr_err_records, tail = tail_fifo_buffer_pr_err_records;
            if (
                (head != tail) || 
                (_CHECK_SET_BIT(diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT) != 0)
               )
            {
              control_tasks_dataflash |= TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH;  //� ��� ������ � ����� ����  
            }
          }
        
          //�������� ������� ���, ���� ��� � � ������� �� �����
          main_function_for_dataflash_resp(number_chip_dataflsh_exchange);

          if (
              (control_spi1_taskes[0] == 0) &&
              (control_spi1_taskes[1] == 0) 
             )
          {
            //������� ����� DataFlash � ���� ���� ��� ����� ������
            if (driver_spi_df[number_chip_dataflsh_exchange].state_execution == TRANSACTION_EXECUTING_NONE)
            {
              //������� ����� ���������, �� ��� �� ������ ���������� ��� �������� �����������, ���� ����� �� �������� ���� ����������
              number_chip_dataflsh_exchange = (number_chip_dataflsh_exchange + 1) & (NUMBER_DATAFLASH_CHIP - 1);
            }

            //������ ����� �� ���� ��������� DataFlash, ���� � �����
            main_function_for_dataflash_req(number_chip_dataflsh_exchange);
          }
        }
        else
        {
          //���� �����������, �� ��� ��������� �������� ������� �������
          if (driver_spi_df[number_chip_dataflsh_exchange].state_execution == TRANSACTION_EXECUTED_WAIT_ANALIZE)
          {
            //��������� ����� ��������� ����� � ��������� DataFlash � ����� ������ � "����" �����
            if (driver_spi_df[number_chip_dataflsh_exchange].code_operation == CODE_OPERATION_STATUS_READ)
            {
              /*
              � ����� ���������� ����� � ���������� DataFlash ���� "����" � ����
              ������� ��������, �� �� �������� ������� �� ������� ������� ������� - 
              � ��� ����� �������� - �� � ������������ �������, ���� �������, �� ��������
              ���������� �������������� ������ - ���� ����������
              */
               
              if ((RxBuffer_SPI_EDF[1] & (1<< 7)) != 0) dataflash_not_busy |= (1 << number_chip_dataflsh_exchange);
              else dataflash_not_busy &= (unsigned int)(~(1 << number_chip_dataflsh_exchange));
        
              driver_spi_df[number_chip_dataflsh_exchange].state_execution = TRANSACTION_EXECUTING_NONE;
              driver_spi_df[number_chip_dataflsh_exchange].code_operation = CODE_OPERATION_NONE;
            }
            else
            {
              total_error_sw_fixed(39);
            }
          }

          /*
          ������� ����� ���������, � ���� ��������� ����, �� ��� ������ � ��������,
          ���� ����� ���, �� �������, �� ����� ���������� ��������� ����� ����
          ������ ��������� ������ ����� �����
          */
          if (driver_spi_df[number_chip_dataflsh_exchange].state_execution == TRANSACTION_EXECUTING_NONE)
          {
            //��������� ������� ������ ����� � ���������� DataFlash
            if((dataflash_not_busy & (1 << number_chip_dataflsh_exchange)) == 0)
            {
              //������ ����� ������� ���������
              dataflash_status_read(number_chip_dataflsh_exchange);
            }
            else
            {
              //̳�������� ������ �� ���������� ��������� ��������, �� ��� ��� ������� ��������� �������� �� SPI_EDF

              //³��������� ����� �����������, ���� ��� �� ��� �������
              if ((number_bytes_transfer_spi_df_copy != 0) && (number_bytes_transfer_spi_df_copy < sizeof(TxBuffer_SPI_EDF)))
              {
                number_bytes_transfer_spi_df = number_bytes_transfer_spi_df_copy;
                for(unsigned int i = 0; i < number_bytes_transfer_spi_df; i++)
                  TxBuffer_SPI_EDF[i] = TxBuffer_SPI_DF_copy[i];

                /*
                ������ ������, �� ����������� ������� ��� ����, �� �� ������ 
                ���������� �� ��������, ��� ������������ �� ������� �������� �������
                */
                error_into_spi_df = 0;

                //³��������� ��������, ��� �����������
                driver_spi_df[number_chip_dataflsh_exchange].code_operation = code_operation_copy;

                //��������� �������� ���� ��������
                start_exchange_via_spi(number_chip_dataflsh_exchange, number_bytes_transfer_spi_df);
              }
              else
              {
                //³������� ����������� �������, ���� ����� ��� �� ����������������
                total_error_sw_fixed(40);
              }
            }
                
          }
        }
      }
      else
      {
        //³������� ����������� �������, ���� ����� ��� �� ����������������
        total_error_sw_fixed(38);
      }
    }
    /***********************************************************/
    
    /***********************************************************/
    //ϳ����������� ����� ����� ��� ���������� ���������� ����
    /***********************************************************/
    changing_diagnostyka_state();
    /***********************************************************/
    
    /***********************************************************/
    //�������� �� ����������� ������� �������� ���� ����� ��� ������������
    /***********************************************************/
    //��������� ���������� ����
    if (periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR != 0)
    {
      //����� � ���� ������� ������ ������� ������� ��ﳿ �����
      if ((state_spi1_task & STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_GOOD) != 0)
      {
        //������ ���� ����� ���, ���� ��������� ���������� ���������� ������ ������� � ���������� ���������� ����
        if (
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT    ) == 0)
           ) 
        {
          //�� ����� ������� �� ��� �������-����� ��������� ���������� ����������, ���� ����� �������� ���������
          info_rejestrator_pr_err_ctrl = info_rejestrator_pr_err;
          crc_info_rejestrator_pr_err_ctrl = crc_info_rejestrator_pr_err;

          //������� ������� ������ ���������� �������� ��ﳿ 
          periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR = false;
          //����������� ������� ������ �������� ����������� �� �������� ��ﳿ 
          periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR_LOCK = true;
        }
      }
      else
      {
        //������� ������� ������ ���������� �������� ��ﳿ 
        periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR = false;
      }
    }
    /***********************************************************/

    /***********************************************************/
    //������������ "�������� ��������� ��� ���������� �����������"
    /***********************************************************/
    uint16_t /*current_tick = TIM4->CNT,*/ capture_new;
    unsigned int delta;
    TIM4->CCR2 = (capture_new = (current_tick + (delta = TIM4_CCR2_VAL)));
    
    unsigned int repeat;
    unsigned int previous_tick;
    do
    {
      repeat = 0;
      current_tick = TIM4->CNT;

      uint32_t delta_time = 0;
      if (capture_new < current_tick)
        delta_time = capture_new + 0x10000 - current_tick;
      else delta_time = capture_new - current_tick;

      if ((delta_time > delta) || (delta_time == 0))
      {
        if (TIM_GetITStatus(TIM4, TIM_IT_CC2) == RESET)
        {
          if (delta < TIM4_CCR2_VAL)
          {
            uint32_t delta_tick;
            if (current_tick < previous_tick)
              delta_tick = current_tick + 0x10000 - previous_tick;
            else delta_tick = current_tick - previous_tick;
              
            delta = delta_tick + 1;
          }
          else if (delta == TIM4_CCR2_VAL)
            delta = 1; /*����������, ��� ���� ���������� ����������� �� ����� ������*/
          else
          {
            //���������� ����� ����� �� ���� � ����
            total_error_sw_fixed(80);
          }
          TIM4->CCR2 = (capture_new = (TIM4->CNT +  delta));
          previous_tick = current_tick;
          repeat = 0xff;
        }
      }
    }
    while (repeat != 0);
    
    /*Vidladka*/
#ifdef DEBUG_TEST
//    static unsigned int t_1, t_2, delta_tmp;
//    t_1 = TIM4->CCR2;
//    t_2 = TIM4->CNT;
//    if (t_1 >= t_2) delta_tmp = t_1 - t_2;
//    else delta_tmp = t_1 + 0xffff - t_2;
//    
//    if (
//        (delta_tmp > TIM4_CCR2_VAL) &&
//        (TIM_GetITStatus(TIM4, TIM_IT_CC2) == RESET)  
//       )   
//    {
//      while(delta_tmp > 0);
//    }
#endif
    /***/
    /***********************************************************/

    /***********************************************************/
    //����������� ����������� ��� ��, �� ����� 2 TIM4, �� ������� �� �������� ������� ��� DataFlash ������
    /***********************************************************/
    control_word_of_watchdog |= WATCHDOG_DATAFLASH;
    /***********************************************************/
    /***********************************************************************************************/
  }

#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//����������� �� ���������� ��䳿 ��� ������� ��� SPI_EDF
/*****************************************************/
void SPI_EDF_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif

  /*
  ³������� ��������� �������� - ����� �������� �������� ���������� ���������� ����������
  */
  
  /*
  �����'������� ������ �������, ���� �������� ����� ���� ��������� ����������� - 
  � ����� �� ���� ����������� ������� ��������� �����������
  �� ����� ������ ��������������� ��� ����� �������
  */
  uint16_t spi_status = SPI_EDF->SR;
  
  /*����������� ��������� ���������� �� ������ DMA_StreamSPI_EDF_Rx*/
  DMA_StreamSPI_EDF_Rx->CR &= ~DMA_IT_TC;

  /*
  ������� ����� �� ������������ ������ DMA ���������� �� ������/�������� �����,
  ��� �������� ����������� ������� � ������ �����, �� ��������� ��
  */
  DMA_StreamSPI_EDF_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamSPI_EDF_Tx->NDTR = 0;
  DMA_StreamSPI_EDF_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamSPI_EDF_Rx->NDTR = 0;

  /*��������� ����������� ����������� �� ������� �� SPI_EDF*/
  SPI_I2S_ITConfig(SPI_EDF, SPI_I2S_IT_ERR, DISABLE);

  /*
  ������� ���� TXE=1 � BSY=0 - �� ������ �������� ���������� �������� �����,
  � ������� ���������� ������� ��� - �� � ��������� ����� �����������
  */
  while ((SPI_EDF->SR & SPI_I2S_FLAG_TXE) == 0);
  while ((SPI_EDF->SR & SPI_I2S_FLAG_BSY) != 0);

  /*������ Chip_select ��������� NSS  � 1*/
  GPIO_SPI_EDF->BSRRL = GPIO_NSSPin_EDF;

  if (
      ((spi_status  & SPI_I2S_FLAG_OVR) != 0) ||
      ((SPI_EDF->SR & SPI_I2S_FLAG_OVR) != 0)
     )
  {
    //���� ��� ������������ ��������
    
    do
    {
      //������� �� ��䳺� ����� ���������� ������:
      SPI_EDF->DR;
      SPI_EDF->SR;
    }
    while((SPI_EDF->SR & SPI_I2S_FLAG_OVR) != 0);
  }

  if (
      ((spi_status  & SPI_FLAG_MODF) != 0) ||
      ((SPI_EDF->SR & SPI_FLAG_MODF) != 0)  
     )   
  {
    //���� "Master mode fault" - ���������� ���� �� ����� ��������

    do
    {
      //������� �� ��䳺� ����� ����������:
      SPI_EDF->SR;

      //����������� SPI_EDF
      SPI_Cmd(SPI_EDF, DISABLE);
      //����������� SPI_EDF DMA Tx ������
      SPI_I2S_DMACmd(SPI_EDF, SPI_I2S_DMAReq_Tx, DISABLE);
      //����������� SPI_EDF DMA Rx ������
      SPI_I2S_DMACmd(SPI_EDF, SPI_I2S_DMAReq_Rx, DISABLE);
    
      //��������� ���������� SPI_EDF � Slave-�����
      SPI_InitTypeDef  SPI_InitStructure;
      SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
      SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
      SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
      SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
      SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
      SPI_InitStructure.SPI_NSS =  SPI_NSS_Soft;
      SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
      SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
      SPI_InitStructure.SPI_CRCPolynomial = 7;
      SPI_Init(SPI_EDF, &SPI_InitStructure);
      //���������� SPI_EDF - � Slave-�����
      SPI_Cmd(SPI_EDF, ENABLE);

      //����� ����������� SPI_EDF ��� ������������� � Master-�����
      SPI_Cmd(SPI_EDF, DISABLE);
    
      //��������� SPI_EDF � Master-�����
      SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
      SPI_Init(SPI_EDF, &SPI_InitStructure);

      //����������� SPI_EDF DMA Tx ������
      SPI_I2S_DMACmd(SPI_EDF, SPI_I2S_DMAReq_Tx, DISABLE);
      //����������� SPI_EDF DMA Rx ������
      SPI_I2S_DMACmd(SPI_EDF, SPI_I2S_DMAReq_Rx, DISABLE);

      //������� ���������, �� �������� ��� ���������� ������/�������� ����� ��� DMA �� ������ DMA_StreamSPI_EDF_Rx � DMA_StreamSPI_EDF_Tx
      DMA_ClearFlag(DMA_StreamSPI_EDF_Rx, DMA_FLAG_TCSPI_EDF_Rx | DMA_FLAG_HTSPI_EDF_Rx | DMA_FLAG_TEISPI_EDF_Rx | DMA_FLAG_DMEISPI_EDF_Rx | DMA_FLAG_FEISPI_EDF_Rx);
      DMA_ClearFlag(DMA_StreamSPI_EDF_Tx, DMA_FLAG_TCSPI_EDF_Tx | DMA_FLAG_HTSPI_EDF_Tx | DMA_FLAG_TEISPI_EDF_Tx | DMA_FLAG_DMEISPI_EDF_Tx | DMA_FLAG_FEISPI_EDF_Tx);

      //���������� SPI_EDF
      SPI_Cmd(SPI_EDF, ENABLE);
    }
    while ((SPI_EDF->SR & SPI_FLAG_MODF) != 0);
  }

  if (
      ((spi_status  & SPI_FLAG_CRCERR) != 0) ||
      ((SPI_EDF->SR & SPI_FLAG_CRCERR) != 0)  
     )   
  {
    //���� "CRC error" - ����� �� ���� � �������� � ����� �������

    //³������� ����������� �������, ���� ����� ��� �� ����������������
    total_error_sw_fixed(34);
  }

  if (state_execution_spi1 >= 0) 
  {
    //³�������� ���� � EEPROM. �������, �� �������� ������� � ������ ��������� ���������� �������� ������-��������
    state_execution_spi1 = 2;
  }
  else if ((number_chip_dataflsh_exchange >= INDEX_DATAFLASH_1) && (number_chip_dataflsh_exchange <= INDEX_DATAFLASH_2))
  {
    if(driver_spi_df[number_chip_dataflsh_exchange].state_execution != TRANSACTION_EXECUTING_NONE)
    {
      //������� ������� � ������ ������/��������
      
      //Գ����� ��������, ��� ������������ ��� �������� �������
      unsigned int code_operation_copy_tmp = driver_spi_df[number_chip_dataflsh_exchange].code_operation;
      
      /*
      ������� ������� ����������� ��� ������, ��, ��������, ����������� ����� ����� ���������� ������,
      ���� ����� �������, �� ����� ������� ������ ���������
      */
      dataflash_not_busy &= (unsigned int)(~(1 << number_chip_dataflsh_exchange));

      //������ �����������, �� ���������� �������� ��� ���� ���������
      driver_spi_df[number_chip_dataflsh_exchange].state_execution = TRANSACTION_EXECUTING_NONE;
      driver_spi_df[number_chip_dataflsh_exchange].code_operation = CODE_OPERATION_NONE;
      
      if (code_operation_copy_tmp != CODE_OPERATION_STATUS_READ) 
      {
        /*
        ��������� ��������� 䳿, ���� ��������� �������� ���� ������� ������� �������,
        ��, ������� �� ����� ��������� ��������� ���� ���������, �� �� �������� �������
        ����������� ������, � ��� ����� �� ������� ��������
        */
        if (code_operation_copy_tmp == CODE_OPERATION_STATUS_READ)
        {
          /*³������� ����������� ������� (�� �� ���� ����, ��� ���� ����� ��������, 
          ��� ���� ���� ������. �� ���� �������� ����), ���� ����� ��� �� ����������������
          */
          total_error_sw_fixed(37);
        }
          
        //������ �������� ���� ������� ���� ��� ����������� � ����� �����������
        if ((number_bytes_transfer_spi_df != 0) && (number_bytes_transfer_spi_df < sizeof(TxBuffer_SPI_EDF)))
        {
          number_bytes_transfer_spi_df_copy = number_bytes_transfer_spi_df;
          for(unsigned int i = 0; i < number_bytes_transfer_spi_df_copy; i++)
            TxBuffer_SPI_DF_copy[i] = TxBuffer_SPI_EDF[i];
        }
        else
        {
          //³������� ����������� �������, ���� ����� ��� �� ����������������
          total_error_sw_fixed(36);
        }
        
        //�����'�������, ��� ������������ ��������
        code_operation_copy = code_operation_copy_tmp;

        //�������, �� ����������� ������� ��� ����
        error_into_spi_df = 0xff;
      }
    }
  }
  else
  {
    //³������� ����������� �������, ���� ����� ��� �� ����������������
    total_error_sw_fixed(35);
  }
  
  /*����������� ����������� ��� ������� ����� ����� SPI_EDF*/
  _SET_BIT(set_diagnostyka, ERROR_SPI_EDF_BIT);

  //���������� ����������� �� ������� �� SPI_EDF
  SPI_I2S_ITConfig(SPI_EDF, SPI_I2S_IT_ERR, ENABLE);
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/
  
/*****************************************************/
//������������� �� ���������� ������� DMA_StreamSPI_EDF_Rx
/*****************************************************/
void DMA_StreamSPI_EDF_Rx_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif

  /*
  ������� ���� TXE=1 � BSY=0 - �� ������ �������� ���������� �������� �����,
  � ������� ���������� ������� ��� - �� � ��������� ����� �����������
  */
  while ((SPI_EDF->SR & SPI_I2S_FLAG_TXE) == 0);
  while ((SPI_EDF->SR & SPI_I2S_FLAG_BSY) != 0);

  //������ Chip_select ��������� NSS  � 1
  GPIO_SPI_EDF->BSRRL = GPIO_NSSPin_EDF;
  
  //��������� ������ DMA
  DMA_StreamSPI_EDF_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamSPI_EDF_Tx->NDTR = 0;
  DMA_StreamSPI_EDF_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamSPI_EDF_Rx->NDTR = 0;

  //����������� ��������� ���������� �� ������ DMA_StreamSPI_EDF_Rx
  DMA_StreamSPI_EDF_Rx->CR &= ~DMA_IT_TC;
  
  //������� ���������, �� �������� ��� ���������� �������� ����� ��� DMA �� ������ DMA_StreamSPI_EDF_Rx
  DMA_ClearFlag(DMA_StreamSPI_EDF_Rx, DMA_FLAG_TCSPI_EDF_Rx | DMA_FLAG_HTSPI_EDF_Rx | DMA_FLAG_TEISPI_EDF_Rx | DMA_FLAG_DMEISPI_EDF_Rx | DMA_FLAG_FEISPI_EDF_Rx);
  
  //����������� �����������, �� ��� ������� � ����� �� ���������� ������
  if (state_execution_spi1 == 0) 
  {
    //³�������� ���� � EEPROM. �������, �� �� ����������
    state_execution_spi1 = 1;
  }
  else if ((number_chip_dataflsh_exchange == INDEX_DATAFLASH_1) || (number_chip_dataflsh_exchange == INDEX_DATAFLASH_2))
    driver_spi_df[number_chip_dataflsh_exchange].state_execution = TRANSACTION_EXECUTED_WAIT_ANALIZE;
  else
  {
    //³������� ����������� �������, ���� ����� ��� �� ����������������
    total_error_sw_fixed(20);
  }
      
  //���� ������� ����� - ������� ����������� ��� ���������� ������� ������� ����� ����� SPI_EDF
  _SET_BIT(clear_diagnostyka, ERROR_SPI_EDF_BIT);
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//����������� �� USART RS-485
/*****************************************************/
void USARTRS485_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif

  if (USART_GetITStatus(USART_RS485, USART_IT_TC) != RESET)
  {
    //���������� ��������� �� ������
    GPIO_485DE->BSRRH = GPIO_PIN_485DE;

    //����������� ��������� ���������� ��� ��������� �������� �����
    USART_ITConfig(USART_RS485, USART_IT_TC, DISABLE);
      
    //������� ��, �� ��������, �� �������� ���� ���������
    USART_ClearFlag(USART_RS485, USART_FLAG_TC);

    //³��������� ��������� ������ RS-485 , ���� �� ����� ����� ��������������� ���������
    if (make_reconfiguration_RS_485 == 0) restart_monitoring_RS485();
  }
  
  if(USART_GetITStatus(USART_RS485, USART_IT_IDLE) != RESET)
  {
    //����������� IDLE ����
    if ((DMA_StreamRS485_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamRS485_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
    USART_RS485->SR;
    (uint16_t)(USART_RS485->DR & (uint16_t)0x01FF);

    // ������� ���������, �� �������� ��� ���������� �������� ����� ��� DMA1 �� ������ RS-485_RX 
    DMA_ClearFlag(DMA_StreamRS485_Rx, DMA_FLAG_TCRS485_Rx | DMA_FLAG_HTRS485_Rx | DMA_FLAG_TEIRS485_Rx | DMA_FLAG_DMEIRS485_Rx | DMA_FLAG_FEIRS485_Rx);
    uint32_t NDTR_tmp = DMA_StreamRS485_Rx->NDTR;
    DMA_StreamRS485_Rx->NDTR = NDTR_tmp;
    DMA_StreamRS485_Rx->CR |= (uint32_t)DMA_SxCR_EN;
  }

  if(USART_GetITStatus(USART_RS485, USART_IT_LBD) != RESET)
  {
    //����������� Break ����
    USART_ClearFlag(USART_RS485, USART_FLAG_LBD);
  }

  unsigned int error_status = USART_RS485->SR &  (USART_FLAG_ORE | USART_FLAG_NE | USART_FLAG_FE | USART_FLAG_PE);
  if (error_status != 0)
/*    
  if(
     (USART_GetITStatus(USART_RS485, USART_IT_PE  ) != RESET) ||
     (USART_GetITStatus(USART_RS485, USART_IT_NE  ) != RESET) ||
     (USART_GetITStatus(USART_RS485, USART_IT_FE  ) != RESET) ||
     (USART_GetITStatus(USART_RS485, USART_IT_ORE ) != RESET)
    )
*/    
  {
    //����������� ������� �� ��� ������� - ������������� ������ ����� DMA
    if ((DMA_StreamRS485_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamRS485_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
    USART_RS485->SR;
    (uint16_t)(USART_RS485->DR & (uint16_t)0x01FF);
    // ������� ���������, �� �������� ��� ���������� �������� ����� ��� DMA1 �� ������ RS-485_RX 
    DMA_ClearFlag(DMA_StreamRS485_Rx, DMA_FLAG_TCRS485_Rx | DMA_FLAG_HTRS485_Rx | DMA_FLAG_TEIRS485_Rx | DMA_FLAG_DMEIRS485_Rx | DMA_FLAG_FEIRS485_Rx);
    DMA_StreamRS485_Rx->NDTR = BUFFER_RS485;
    RxBuffer_RS485_count_previous = 0;
    RxBuffer_RS485_count = 0;
    DMA_StreamRS485_Rx->CR |= (uint32_t)DMA_SxCR_EN;
  }
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//����������� �� ���������� �������� ����� ����� DMA ������ DMA_StreamRS485_Tx
/*****************************************************/
void DMA_StreamRS485_Tx_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif

  //���������� ��������� ���������� ��� ��������� �������� �����
  USART_ITConfig(USART_RS485, USART_IT_TC, ENABLE);

  //����������� ��������� ����������� �� DMA_StreamRS485_Tx
  DMA_StreamRS485_Tx->CR &= ~DMA_IT_TC;

  //��������� ������ DMA
  DMA_StreamRS485_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamRS485_Tx->NDTR = 0;

  //������� ���������, �� �������� ��� ���������� �������� ����� ��� DMA1 �� ������ RS-485_TX
  DMA_ClearFlag(DMA_StreamRS485_Tx, DMA_FLAG_TCRS485_Tx | DMA_FLAG_HTRS485_Tx | DMA_FLAG_TEIRS485_Tx | DMA_FLAG_DMEIRS485_Tx | DMA_FLAG_FEIRS485_Tx);
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//����������� �� I2C
/*****************************************************/
void EXITI_POWER_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif

  if(EXTI_GetITStatus(EXTI_Line_POWER) != RESET)
  {
    /* Clear the EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line_POWER);
    
    if ((POWER_CTRL->IDR & POWER_CTRL_PIN) != (uint32_t)Bit_RESET)
    {
      //�������� ��������� �� ���� ����� ��������

      //����������� ����������� ��� �� ����
      _SET_BIT(clear_diagnostyka, EVENT_DROP_POWER_BIT);
      reinit_LCD = true;
    }
    else
    {
      //�������� ������� �� ���� ����� ��������

      //�������� �������
      LCD_BL->BSRRH = LCD_BL_PIN;
      time_backlighting = 0;
      
      //����������� ����������� ��� �� ����
      _SET_BIT(set_diagnostyka, EVENT_DROP_POWER_BIT);

      //��������� ����� � EEPROM
      _SET_BIT(control_spi1_taskes, TASK_START_WRITE_ENERGY_EEPROM_BIT);
      number_minutes = 0;
    }
  }
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/

#undef BACKLIGHTING_ON
#undef BACKLIGHTING_OFF
