#include "header.h"

/*****************************************************/
//��������� ������ ����� SPI
/*****************************************************/
void main_routines_for_spi1(void)
{
  //�������� �����, ��� ����� ���� ���� ��������� ����� ���������� � EEPROM
  static unsigned int number_block_settings_write_to_eeprom;
  //�������� �����, ��� ����� ���� ���� ��������� ����� ���������� � EEPROM
  static unsigned int number_block_ustuvannja_write_to_eeprom;
  //�������� �����, ��� ����� ���� ���� ����� ������ � �������������� ����� ���������� � EEPROM
  static unsigned int number_block_state_leds_outputs_write_to_eeprom;
  //�������� �����, ��� ����� ���� ���� ������� ���������� ����� ���������� � EEPROM
  static unsigned int number_block_trg_func_write_to_eeprom;
  //�������� �����, ��� ����� ���� ���� ���������� �� ����������� ��������� ����� ���������� � EEPROM
  static unsigned int number_block_info_rejestrator_ar_write_to_eeprom;
  //�������� �����, ��� ����� ���� ���� ���������� �� ����������� ��������� ����� ���������� � EEPROM
  static unsigned int number_block_info_rejestrator_dr_write_to_eeprom;
  //�������� �����, ��� ����� ���� ���� ���������� �� ��������� ���������� ���� ����� ���������� � EEPROM
  static unsigned int number_block_info_rejestrator_pr_err_write_to_eeprom;
  //�������� �����, ��� ����� ���� ���� ���������� �� ������� �������� ����� ���������� � EEPROM
  static unsigned int number_block_resurs_write_to_eeprom;
  //�������� �����, ��� ����� ���� ���� ���������� �� ������� ����� ���������� � EEPROM
  static unsigned int number_block_energy_write_to_eeprom;
  
  //������� ���� ��� �������� ���������� ������
  static __SETTINGS current_settings_comp;
  static unsigned int ustuvannja_comp[NUMBER_ANALOG_CANALES], serial_number_dev_comp;
  static int phi_ustuvannja_comp[NUMBER_ANALOG_CANALES];
  static float phi_ustuvannja_sin_cos_comp[2*NUMBER_ANALOG_CANALES];
  static unsigned int state_trigger_leds_comp, state_signal_outputs_comp;
  static unsigned int fix_active_buttons_comp, trigger_active_functions_comp[N_BIG];
  static __INFO_AR_REJESTRATOR info_rejestrator_ar_comp;
  static __INFO_REJESTRATOR info_rejestrator_dr_comp;
  static __INFO_REJESTRATOR info_rejestrator_pr_err_comp;
  static unsigned int resurs_vymykacha_comp, resurs_vidkljuchennja_comp;
  static double energy_comp[MAX_NUMBER_INDEXES_ENERGY];
  
  if (state_execution_spi1 < 0)
  {
    /*************************************************/
    //����� ����� ��������� ���� ���������� ����� SPI
    /*************************************************/
    
    if(_CHECK_SET_BIT(control_spi1_taskes, TASK_EEPROM_WRITE_PREPARATION_BIT) !=0)
    {
      unsigned int number;
      
      //������� ����� ��� �������� �  EEPROM (�� ������ + ��������� ������ - ����������� �����)
      if ((etap_eeprom_write_enable < 0) || ((etap_eeprom_write_enable > 1))) etap_eeprom_write_enable = 0;

      if (etap_eeprom_write_enable == 0)
      {
        //������ ������ �������
        TxBuffer_SPI_EDF[0] = OPCODE_RDSR;
        TxBuffer_SPI_EDF[1] = 0; //����-���� ���� ��� ����, ��� �������� ������� ������� �������;
        number = 2;
      }
      else if (etap_eeprom_write_enable == 1)
      {
        //������ ������ �������
        TxBuffer_SPI_EDF[0] = OPCODE_WREN;
        number = 1;
      }
      
      //��������� ������ ������ � EEPROM
      start_exchange_via_spi(INDEX_EEPROM, number);
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_ENERGY_EEPROM_BIT) !=0)
    {
      //����� ����� ������ ����� � EEPROM ������

      int size_to_end;
      unsigned int number, offset_from_start;
      
      //��������� � ����� ���� ����� ������ ����������
      offset_from_start = number_block_energy_write_to_eeprom*SIZE_PAGE_EEPROM;

      //ʳ������ ���� �� ���� ������ 
      size_to_end = (SIZE_ENERGY + 1) - offset_from_start; 
      
      if (size_to_end > 0)
      {
        TxBuffer_SPI_EDF[0] = OPCODE_WRITE;
        TxBuffer_SPI_EDF[1] = ((START_ADDRESS_ENERGY_IN_EEPROM + offset_from_start) >> 8) & 0xff; //������  ������ ������� ��������� ��������� � EEPROM
        TxBuffer_SPI_EDF[2] = ((START_ADDRESS_ENERGY_IN_EEPROM + offset_from_start)     ) & 0xff; //������� ������ ������� ��������� ��������� � EEPROM

        if (size_to_end < SIZE_PAGE_EEPROM) number = size_to_end;
        else number = SIZE_PAGE_EEPROM;

        if (offset_from_start != 0)
        {
          //��������� ��� ��� ������ �� ������ � ������� ������� ������ ��� ����, ��� ���������� ����� ����� ��� �������� �� DMA
          for (unsigned int i = 0; i < number; i++)
            TxBuffer_SPI_EDF[3 + i] = TxBuffer_SPI_EDF[3 + offset_from_start + i];
        }
        
        //��������� ������ ������ � EEPROM
        start_exchange_via_spi(INDEX_EEPROM, (3 + number));
      }
      else
      {
        //���� ����� ��������� ��� ���������, ���� ������� ����� ������ ��������� � EEPROM

        //����������� ������� ������������ ������� ��� ��������� ����������� �������� ����������
        comparison_writing |= COMPARISON_WRITING_ENERGY;
        _SET_BIT(control_spi1_taskes, TASK_START_READ_ENERGY_EEPROM_BIT);
        
        //������� ����� ������ ��������� � EEPROM
        _CLEAR_BIT(control_spi1_taskes, TASK_WRITING_ENERGY_EEPROM_BIT);
      }
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT) !=0)
    {
      //����� ����� ������ ����� � EEPROM ���������

      int size_to_end;
      unsigned int number, offset_from_start;
      
      //��������� � ����� ���� ����� ������ ����������
      offset_from_start = number_block_settings_write_to_eeprom*SIZE_PAGE_EEPROM;

      //ʳ������ ���� �� ���� ������ 
      size_to_end = (sizeof(__SETTINGS) + 1 + 1) - offset_from_start; 
      
      if (size_to_end > 0)
      {
        TxBuffer_SPI_EDF[0] = OPCODE_WRITE;
        TxBuffer_SPI_EDF[1] = ((START_ADDRESS_SETTINGS_IN_EEPROM + offset_from_start) >> 8) & 0xff; //������  ������ ������� ��������� ��������� � EEPROM
        TxBuffer_SPI_EDF[2] = ((START_ADDRESS_SETTINGS_IN_EEPROM + offset_from_start)     ) & 0xff; //������� ������ ������� ��������� ��������� � EEPROM

        if (size_to_end < SIZE_PAGE_EEPROM) number = size_to_end;
        else number = SIZE_PAGE_EEPROM;

        if (offset_from_start != 0)
        {
          //��������� ��� ��� ������ �� ������ � ������� ������� ������ ��� ����, ��� ���������� ����� ����� ��� �������� �� DMA
          for (unsigned int i = 0; i < number; i++)
            TxBuffer_SPI_EDF[3 + i] = TxBuffer_SPI_EDF[3 + offset_from_start + i];
        }
        
        //��������� ������ ������ � EEPROM
        start_exchange_via_spi(INDEX_EEPROM, (3 + number));
      }
      else
      {
        //���� ����� ��������� ��� ���������, ���� ������� ����� ������ ��������� � EEPROM

        //����������� ������� ������������ ������� ��� ��������� ����������� �������� ����������
        comparison_writing |= COMPARISON_WRITING_SETTINGS;
        _SET_BIT(control_spi1_taskes, TASK_START_READ_SETTINGS_EEPROM_BIT);
        
        //������� ����� ������ ��������� � EEPROM
        _CLEAR_BIT(control_spi1_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT);
      }
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_USTUVANNJA_EEPROM_BIT) !=0)
    {
      //����� ����� ������ ����� � EEPROM ���������

      int size_to_end;
      unsigned int number, offset_from_start;
      
      //��������� � ����� ���� ����� ������ ����������
      offset_from_start = number_block_ustuvannja_write_to_eeprom*SIZE_PAGE_EEPROM;

      //ʳ������ ���� �� ���� ������ 
      size_to_end = (SIZE_USTUVANNJA + 1) - offset_from_start; 
      
      if (size_to_end > 0)
      {
        TxBuffer_SPI_EDF[0] = OPCODE_WRITE;
        TxBuffer_SPI_EDF[1] = ((START_ADDRESS_USTUVANNJA_IN_EEPROM + offset_from_start) >> 8) & 0xff; //������  ������ ������� ��������� ��������� � �������� ������ � EEPROM
        TxBuffer_SPI_EDF[2] = ((START_ADDRESS_USTUVANNJA_IN_EEPROM + offset_from_start)     ) & 0xff; //������� ������ ������� ��������� ��������� � �������� ������ � EEPROM

        if (size_to_end < SIZE_PAGE_EEPROM) number = size_to_end;
        else number = SIZE_PAGE_EEPROM;

        if (offset_from_start != 0)
        {
          //��������� ��� ��� ������ �� ������ � ������� ������� ������ ��� ����, ��� ���������� ����� ����� ��� �������� �� DMA
          for (unsigned int i = 0; i < number; i++)
            TxBuffer_SPI_EDF[3 + i] = TxBuffer_SPI_EDF[3 + offset_from_start + i];
        }
        
        //��������� ������ ������ � EEPROM
        start_exchange_via_spi(INDEX_EEPROM, (3 + number));
      }
      else
      {
        //���� ����� ��������� ��� ���������

        //����������� ������� ������������ ������� ��� ��������� ����������� �������� ����������
        comparison_writing |= COMPARISON_WRITING_USTUVANNJA;
        _SET_BIT(control_spi1_taskes, TASK_START_READ_USTUVANNJA_EEPROM_BIT);
        
        //������� ����� ������ ��������� � EEPROM
        _CLEAR_BIT(control_spi1_taskes, TASK_WRITING_USTUVANNJA_EEPROM_BIT);
      }
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_STATE_LEDS_OUTPUTS_EEPROM_BIT) !=0)
    {
      //����� ����� ������ ����� � EEPROM ����� ������ � ��������������
      int size_to_end;
      unsigned int number, offset_from_start;
      
      //��������� � ����� ���� ����� ������ ����������
      offset_from_start = number_block_state_leds_outputs_write_to_eeprom*SIZE_PAGE_EEPROM;

      //ʳ������ ���� �� ���� ������ 
      size_to_end = (2*(3 + 3)) - offset_from_start; 
      
      if (size_to_end > 0)
      {
        TxBuffer_SPI_EDF[0] = OPCODE_WRITE;
        TxBuffer_SPI_EDF[1] = ((START_ADDRESS_STATE_LEDS_OUTPUTS_IN_EEPROM + offset_from_start) >> 8) & 0xff; //������  ������ ������� ��������� ����� ������ � �������������� � EEPROM
        TxBuffer_SPI_EDF[2] = ((START_ADDRESS_STATE_LEDS_OUTPUTS_IN_EEPROM + offset_from_start)     ) & 0xff; //������� ������ ������� ��������� ����� ������ � �������������� � EEPROM

        if (size_to_end < SIZE_PAGE_EEPROM) number = size_to_end;
        else number = SIZE_PAGE_EEPROM;

        if (offset_from_start != 0)
        {
          //��������� ��� ��� ������ �� ������ � ������� ������� ������ ��� ����, ��� ���������� ����� ����� ��� �������� �� DMA
          for (unsigned int i = 0; i < number; i++)
            TxBuffer_SPI_EDF[3 + i] = TxBuffer_SPI_EDF[3 + offset_from_start + i];
        }
        
        //��������� ������ ������ � EEPROM
        start_exchange_via_spi(INDEX_EEPROM, (3 + number));
      }
      else
      {
        //���� ����� ����� ������ � �������������� ��� ���������, ���� ������� ����� ������ ����� ������ � �������������� � EEPROM

        //����������� ������� ������������ ������� ��� ��������� ����������� �������� ����������
        comparison_writing |= COMPARISON_WRITING_STATE_LEDS_OUTPUTS;
        _SET_BIT(control_spi1_taskes, TASK_START_READ_STATE_LEDS_OUTPUTS_EEPROM_BIT);

        //C������ ����� ������ ����� ������-�������������� � EEPROM
        _CLEAR_BIT(control_spi1_taskes, TASK_WRITING_STATE_LEDS_OUTPUTS_EEPROM_BIT);
      }
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT) !=0)
    {
      //����� ����� ������ ����� ������� ����������

      int size_to_end;
      unsigned int number, offset_from_start;
      
      //��������� � ����� ���� ����� ������ ����������
      offset_from_start = number_block_trg_func_write_to_eeprom*SIZE_PAGE_EEPROM;

      //ʳ������ ���� �� ���� ������ 
      size_to_end = (sizeof(fix_active_buttons) + sizeof(trigger_active_functions) + 1) - offset_from_start; 
      
      if (size_to_end > 0)
      {
        TxBuffer_SPI_EDF[0] = OPCODE_WRITE;
        TxBuffer_SPI_EDF[1] = ((START_ADDRESS_TRG_FUNC + offset_from_start) >> 8) & 0xff; //������  ������ ������� ��������� ����� ������� ���������� � EEPROM
        TxBuffer_SPI_EDF[2] = ((START_ADDRESS_TRG_FUNC + offset_from_start)     ) & 0xff; //������� ������ ������� ��������� ����� ������� ���������� � EEPROM

        if (size_to_end < SIZE_PAGE_EEPROM) number = size_to_end;
        else number = SIZE_PAGE_EEPROM;

        if (offset_from_start != 0)
        {
          //��������� ��� ��� ������ �� ������ � ������� ������� ������ ��� ����, ��� ���������� ����� ����� ��� �������� �� DMA
          for (unsigned int i = 0; i < number; i++)
            TxBuffer_SPI_EDF[3 + i] = TxBuffer_SPI_EDF[3 + offset_from_start + i];
        }
        
        //��������� ������ ������ � EEPROM
        start_exchange_via_spi(INDEX_EEPROM, (3 + number));
      }
      else
      {
        //���� ����� ��� ���������

        //����������� ������� ������������ ������� ��� ��������� ����������� �������� ����������
        comparison_writing |= COMPARISON_WRITING_TRG_FUNC;
        _SET_BIT(control_spi1_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT);

        //C������ ����� ������� EEPROM
        _CLEAR_BIT(control_spi1_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT);
      }
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_AR_EEPROM_BIT) !=0)
    {
      //����� ����� ������ ����� ���������� ����������� ���������� � EEPROM

      int size_to_end;
      unsigned int number, offset_from_start;
      
      //��������� � ����� ���� ����� ������ ����������
      offset_from_start = number_block_info_rejestrator_ar_write_to_eeprom*SIZE_PAGE_EEPROM;

      //ʳ������ ���� �� ���� ������ 
      size_to_end = (sizeof(info_rejestrator_ar) + 1) - offset_from_start; 
      
      if (size_to_end > 0)
      {
        TxBuffer_SPI_EDF[0] = OPCODE_WRITE;
        TxBuffer_SPI_EDF[1] = ((START_ADDRESS_INFO_REJESTRATORS_AR + offset_from_start) >> 8) & 0xff; //������  ������ ������� ��������� ��������� ����������� ���������� � EEPROM
        TxBuffer_SPI_EDF[2] = ((START_ADDRESS_INFO_REJESTRATORS_AR + offset_from_start)     ) & 0xff; //������� ������ ������� ��������� ��������� ����������� ���������� � EEPROM

        if (size_to_end < SIZE_PAGE_EEPROM) number = size_to_end;
        else number = SIZE_PAGE_EEPROM;

        if (offset_from_start != 0)
        {
          //��������� ��� ��� ������ �� ������ � ������� ������� ������ ��� ����, ��� ���������� ����� ����� ��� �������� �� DMA
          for (unsigned int i = 0; i < number; i++)
            TxBuffer_SPI_EDF[3 + i] = TxBuffer_SPI_EDF[3 + offset_from_start + i];
        }
        
        //��������� ������ ������ � EEPROM
        start_exchange_via_spi(INDEX_EEPROM, (3 + number));
      }
      else
      {
        //���� ����� ��� ���������
       
        //����������� ������� ������������ ������� ��� ��������� ����������� �������� ����������
        comparison_writing |= COMPARISON_WRITING_INFO_REJESTRATOR_AR;
        _SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_AR_EEPROM_BIT);

        //C������ ����� ������ ���������� ����������� ���������� � EEPROM
        _CLEAR_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_AR_EEPROM_BIT);
      }
      
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_DR_EEPROM_BIT) !=0)
    {
      //����� ����� ������ ����� ���������� ����������� ���������� � EEPROM

      int size_to_end;
      unsigned int number, offset_from_start;
      
      //��������� � ����� ���� ����� ������ ����������
      offset_from_start = number_block_info_rejestrator_dr_write_to_eeprom*SIZE_PAGE_EEPROM;

      //ʳ������ ���� �� ���� ������ 
      size_to_end = (sizeof(info_rejestrator_dr) + 1) - offset_from_start; 
      
      if (size_to_end > 0)
      {
        TxBuffer_SPI_EDF[0] = OPCODE_WRITE;
        TxBuffer_SPI_EDF[1] = ((START_ADDRESS_INFO_REJESTRATORS_DR + offset_from_start) >> 8) & 0xff; //������  ������ ������� ��������� ��������� ����������� ���������� � EEPROM
        TxBuffer_SPI_EDF[2] = ((START_ADDRESS_INFO_REJESTRATORS_DR + offset_from_start)     ) & 0xff; //������� ������ ������� ��������� ��������� ����������� ���������� � EEPROM

        if (size_to_end < SIZE_PAGE_EEPROM) number = size_to_end;
        else number = SIZE_PAGE_EEPROM;

        if (offset_from_start != 0)
        {
          //��������� ��� ��� ������ �� ������ � ������� ������� ������ ��� ����, ��� ���������� ����� ����� ��� �������� �� DMA
          for (unsigned int i = 0; i < number; i++)
            TxBuffer_SPI_EDF[3 + i] = TxBuffer_SPI_EDF[3 + offset_from_start + i];
        }
        
        //��������� ������ ������ � EEPROM
        start_exchange_via_spi(INDEX_EEPROM, (3 + number));
      }
      else
      {
        //���� ����� ��� ���������
       
        //����������� ������� ������������ ������� ��� ��������� ����������� �������� ����������
        comparison_writing |= COMPARISON_WRITING_INFO_REJESTRATOR_DR;
        _SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_DR_EEPROM_BIT);

        //C������ ����� ������ ���������� ����������� ���������� � EEPROM
        _CLEAR_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_DR_EEPROM_BIT);
      }
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) !=0)
    {
      //����� ����� ������ ����� ���������� ���������� ���������� ���� � EEPROM

      int size_to_end;
      unsigned int number, offset_from_start;
      
      //��������� � ����� ���� ����� ������ ����������
      offset_from_start = number_block_info_rejestrator_pr_err_write_to_eeprom*SIZE_PAGE_EEPROM;

      //ʳ������ ���� �� ���� ������ 
      size_to_end = (sizeof(info_rejestrator_pr_err) + 1) - offset_from_start; 
      
      if (size_to_end > 0)
      {
        TxBuffer_SPI_EDF[0] = OPCODE_WRITE;
        TxBuffer_SPI_EDF[1] = ((START_ADDRESS_INFO_REJESTRATORS_PR_ERR + offset_from_start) >> 8) & 0xff; //������  ������ ������� ��������� ��������� ���������� ���������� ���� � EEPROM
        TxBuffer_SPI_EDF[2] = ((START_ADDRESS_INFO_REJESTRATORS_PR_ERR + offset_from_start)     ) & 0xff; //������� ������ ������� ��������� ��������� ���������� ���������� ���� � EEPROM

        if (size_to_end < SIZE_PAGE_EEPROM) number = size_to_end;
        else number = SIZE_PAGE_EEPROM;

        if (offset_from_start != 0)
        {
          //��������� ��� ��� ������ �� ������ � ������� ������� ������ ��� ����, ��� ���������� ����� ����� ��� �������� �� DMA
          for (unsigned int i = 0; i < number; i++)
            TxBuffer_SPI_EDF[3 + i] = TxBuffer_SPI_EDF[3 + offset_from_start + i];
        }
        
        //��������� ������ ������ � EEPROM
        start_exchange_via_spi(INDEX_EEPROM, (3 + number));
      }
      else
      {
        //���� ����� ��� ���������
       
        //����������� ������� ������������ ������� ��� ��������� ����������� �������� ����������
        comparison_writing |= COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR;
        _SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);

        //C������ ����� ������ ���������� ���������� ���������� ���� � EEPROM
        _CLEAR_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
      }
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_RESURS_EEPROM_BIT)!=0)
    {
    //����� ����� ������ ����� � EEPROM ������� ���������

      int size_to_end;
      unsigned int number, offset_from_start;
      
      //��������� � ����� ���� ����� ������ ����������
      offset_from_start = number_block_resurs_write_to_eeprom*SIZE_PAGE_EEPROM;

      //ʳ������ ���� �� ���� ������ 
      size_to_end = (2*sizeof(unsigned int) + 1) - offset_from_start; 
      
      if (size_to_end > 0)
      {
        TxBuffer_SPI_EDF[0] = OPCODE_WRITE;
        TxBuffer_SPI_EDF[1] = ((START_ADDRESS_RESURS_IN_EEPROM + offset_from_start) >> 8) & 0xff; //������  ������ ������� ��������� ��������� ������� � EEPROM
        TxBuffer_SPI_EDF[2] = ((START_ADDRESS_RESURS_IN_EEPROM + offset_from_start)     ) & 0xff; //������� ������ ������� ��������� ��������� ������� � EEPROM

        if (size_to_end < SIZE_PAGE_EEPROM) number = size_to_end;
        else number = SIZE_PAGE_EEPROM;

        if (offset_from_start != 0)
        {
          //��������� ��� ��� ������ �� ������ � ������� ������� ������ ��� ����, ��� ���������� ����� ����� ��� �������� �� DMA
          for (unsigned int i = 0; i < number; i++)
            TxBuffer_SPI_EDF[3 + i] = TxBuffer_SPI_EDF[3 + offset_from_start + i];
        }
        
        //��������� ������ ������ � EEPROM
        start_exchange_via_spi(INDEX_EEPROM, (3 + number));
      }
      else
      {
        //���� ����� ��������� ������� ��� ���������

        //����������� ������� ������������ ������� ��� ��������� ����������� �������� ����������
        comparison_writing |= COMPARISON_WRITING_RESURS;
        _SET_BIT(control_spi1_taskes, TASK_START_READ_RESURS_EEPROM_BIT);
        
        //������� ����� ������ ���� � EEPROM
        _CLEAR_BIT(control_spi1_taskes, TASK_WRITING_RESURS_EEPROM_BIT);
      }  
    }  
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_ENERGY_EEPROM_BIT) !=0)
    {
      //��������� ������ ������� ��������� - ������� ����� ��� ����������� � EEPROM ��� ��������� ��������� � ������� �����
      TxBuffer_SPI_EDF[0] = OPCODE_READ;
      TxBuffer_SPI_EDF[1] = (START_ADDRESS_ENERGY_IN_EEPROM >> 8) & 0xff; //������  ������ ������� ��������� ��������� � �������� ������ � EEPROM
      TxBuffer_SPI_EDF[2] = (START_ADDRESS_ENERGY_IN_EEPROM     ) & 0xff; //������� ������ ������� ��������� ��������� � �������� ������ � EEPROM
                                                                                      //������ �������� ���� �� �� ��������
      start_exchange_via_spi(INDEX_EEPROM, ((SIZE_ENERGY + 1) + 3));
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_SETTINGS_EEPROM_BIT) !=0)
    {
      //��������� ������ ������� ��������� - ������� ����� ��� ����������� � EEPROM ��� ��������� ���������
      TxBuffer_SPI_EDF[0] = OPCODE_READ;
      TxBuffer_SPI_EDF[1] = (START_ADDRESS_SETTINGS_IN_EEPROM >> 8) & 0xff; //������  ������ ������� ��������� ��������� � EEPROM
      TxBuffer_SPI_EDF[2] = (START_ADDRESS_SETTINGS_IN_EEPROM     ) & 0xff; //������� ������ ������� ��������� ��������� � EEPROM
                                                                                    //������ �������� ���� �� �� ��������
      start_exchange_via_spi(INDEX_EEPROM, ((sizeof(__SETTINGS) + 1 + 1) + 3));
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_USTUVANNJA_EEPROM_BIT) !=0)
    {
      //��������� ������ ������� ��������� - ������� ����� ��� ����������� � EEPROM ��� ��������� ��������� � ������� �����
      TxBuffer_SPI_EDF[0] = OPCODE_READ;
      TxBuffer_SPI_EDF[1] = (START_ADDRESS_USTUVANNJA_IN_EEPROM >> 8) & 0xff; //������  ������ ������� ��������� ��������� � �������� ������ � EEPROM
      TxBuffer_SPI_EDF[2] = (START_ADDRESS_USTUVANNJA_IN_EEPROM     ) & 0xff; //������� ������ ������� ��������� ��������� � �������� ������ � EEPROM
                                                                                      //������ �������� ���� �� �� ��������
      start_exchange_via_spi(INDEX_EEPROM, ((SIZE_USTUVANNJA + 1) + 3));
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_STATE_LEDS_OUTPUTS_EEPROM_BIT) !=0)
    {
      //��������� ������ �������  ����� ��� �������� ������ � ������� ��������� - ������� ����� ��� ����������� � EEPROM ��� ���������  ��� ��� �������� ������ � ������� ���������
      TxBuffer_SPI_EDF[0] = OPCODE_READ;
      TxBuffer_SPI_EDF[1] = (START_ADDRESS_STATE_LEDS_OUTPUTS_IN_EEPROM >> 8) & 0xff; //������  ������ ������� ��������� ����� ��� �������� ������ � ������� ��������� � EEPROM
      TxBuffer_SPI_EDF[2] = (START_ADDRESS_STATE_LEDS_OUTPUTS_IN_EEPROM     ) & 0xff; //������� ������ ������� ��������� ����� ��� �������� ������ � ������� ��������� � EEPROM
                                                                                              //������ �������� ���� �� �� ��������
      start_exchange_via_spi(INDEX_EEPROM, ((2*(3 + 3)) + 3));
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT) !=0)
    {
      //��������� ������ �������  ����� ��� ������� ������� - ������� ����� ��� ����������� � EEPROM ��� ���������  ���
      TxBuffer_SPI_EDF[0] = OPCODE_READ;
      TxBuffer_SPI_EDF[1] = (START_ADDRESS_TRG_FUNC >> 8) & 0xff; //������  ������ ������� ��������� ����� ��� ������� ������� � EEPROM
      TxBuffer_SPI_EDF[2] = (START_ADDRESS_TRG_FUNC     ) & 0xff; //������� ������ ������� ��������� ����� ��� ������� ������� � EEPROM
                                                                                          //������ �������� ���� �� �� ��������
      start_exchange_via_spi(INDEX_EEPROM, ((sizeof(fix_active_buttons) + sizeof(trigger_active_functions) + 1) + 3));
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_AR_EEPROM_BIT) !=0)
    {
      //��������� ������ ������� ���������� �� ����������� ���������� - ������� ����� ��� ����������� � EEPROM ��� ���������  ��� �� ����������� ����������
      TxBuffer_SPI_EDF[0] = OPCODE_READ;
      TxBuffer_SPI_EDF[1] = (START_ADDRESS_INFO_REJESTRATORS_AR >> 8) & 0xff; //������  ������ ������� ��������� ����� �� ����������� ���������� � EEPROM
      TxBuffer_SPI_EDF[2] = (START_ADDRESS_INFO_REJESTRATORS_AR     ) & 0xff; //������� ������ ������� ��������� ����� �� ����������� ���������� � EEPROM
                                                                                      //������ �������� ���� �� �� ��������
      start_exchange_via_spi(INDEX_EEPROM, ((sizeof(info_rejestrator_ar) + 1) + 3));
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_DR_EEPROM_BIT) !=0)
    {
      //��������� ������ ������� ���������� �� ����������� ���������� - ������� ����� ��� ����������� � EEPROM ��� ���������  ��� �� ����������� ����������
      TxBuffer_SPI_EDF[0] = OPCODE_READ;
      TxBuffer_SPI_EDF[1] = (START_ADDRESS_INFO_REJESTRATORS_DR >> 8) & 0xff; //������  ������ ������� ��������� ����� �� ����������� ���������� � EEPROM
      TxBuffer_SPI_EDF[2] = (START_ADDRESS_INFO_REJESTRATORS_DR     ) & 0xff; //������� ������ ������� ��������� ����� �� ����������� ���������� � EEPROM
                                                                                      //������ �������� ���� �� �� ��������
      start_exchange_via_spi(INDEX_EEPROM, ((sizeof(info_rejestrator_dr) + 1) + 3));
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) !=0)
    {
      //��������� ������ ������� ���������� �� ���������� ���������� ���� - ������� ����� ��� ����������� � EEPROM ��� ���������  ��� �� ���������� ���������� ����
      TxBuffer_SPI_EDF[0] = OPCODE_READ;
      TxBuffer_SPI_EDF[1] = (START_ADDRESS_INFO_REJESTRATORS_PR_ERR >> 8) & 0xff; //������  ������ ������� ��������� ����� �� ���������� ���������� ���� � EEPROM
      TxBuffer_SPI_EDF[2] = (START_ADDRESS_INFO_REJESTRATORS_PR_ERR     ) & 0xff; //������� ������ ������� ��������� ����� �� ���������� ���������� ���� � EEPROM
                                                                                          //������ �������� ���� �� �� ��������
      start_exchange_via_spi(INDEX_EEPROM, ((sizeof(info_rejestrator_pr_err) + 1) + 3));
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_RESURS_EEPROM_BIT) !=0)
    {
     
      TxBuffer_SPI_EDF[0] = OPCODE_READ;
      TxBuffer_SPI_EDF[1] = (START_ADDRESS_RESURS_IN_EEPROM >> 8) & 0xff; //������  ������ ������� ��������� �����  � EEPROM
      TxBuffer_SPI_EDF[2] = (START_ADDRESS_RESURS_IN_EEPROM     ) & 0xff; //������� ������ ������� ��������� �����  � EEPROM
                                                                                 //������ �������� ���� �� �� ��������
      start_exchange_via_spi(INDEX_EEPROM, ((2*sizeof(unsigned int) + 1) + 3));
    }
    else if (
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_ENERGY_EEPROM_BIT                 ) !=0) ||
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_SETTINGS_EEPROM_BIT               ) !=0) || 
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_USTUVANNJA_EEPROM_BIT             ) !=0) ||
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_STATE_LEDS_OUTPUTS_EEPROM_BIT     ) !=0) ||
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT               ) !=0) ||
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_AR_EEPROM_BIT    ) !=0) || 
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_DR_EEPROM_BIT    ) !=0) || 
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) !=0) || 
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_RESURS_EEPROM_BIT                 ) !=0)
            )
    {
      //��������� ������ �������

      //������ ������ ������� ������ �� ����� ������ EEPROM ���� ��� ������ ������
      TxBuffer_SPI_EDF[0] = OPCODE_RDSR;
      TxBuffer_SPI_EDF[1] = 0; //����-���� ���� ��� ����, ��� �������� ������� ������� �������;

      //��������� ������ ������ � RTC
      start_exchange_via_spi(INDEX_EEPROM, 2);
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_WRITE_ENERGY_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ������ ������ � EEPROM ������
      
      //������� �� ������� ������ ������ � ����������� �� ������ ����� � EEPROM � �����������, ��� ������ ������� � �������������
      _SET_BIT(control_spi1_taskes, TASK_EEPROM_WRITE_PREPARATION_BIT);
      _SET_BIT(control_spi1_taskes, TASK_WRITING_ENERGY_EEPROM_BIT);
      _CLEAR_BIT(control_spi1_taskes, TASK_START_WRITE_ENERGY_EEPROM_BIT);

      //������ ���� ���������� ���������� ��� ��������
      
      //������ ����� ��� ������ ��������� � EEPROM ����� � ����������� �����
      unsigned char crc_eeprom_energy = 0, temp_value;
      unsigned char  *point_1; 
      unsigned char  *point_2;
      unsigned int offset = 3;
      
      //������ ����㳿
      point_1 = (unsigned char*)(&energy[0]); 
      point_2 = (unsigned char*)(&energy_comp);
      for (unsigned int i =0; i < SIZE_ENERGY; i++)
      {
        temp_value = *(point_1);
        *(point_2) = temp_value;
        point_1++;
        point_2++;
        TxBuffer_SPI_EDF[offset + i] = temp_value;
        crc_eeprom_energy += temp_value;
      }
      offset += SIZE_ENERGY;
      
      //���������� ����������� ���������� ���� � ����� ������
      TxBuffer_SPI_EDF[offset] = (unsigned char)((~(unsigned int)crc_eeprom_energy) & 0xff);
      
      //����������� ������ ���� ������ ������ � EEPROM
      number_block_energy_write_to_eeprom = 0;
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ������ ������ � EEPROM ���������

      //������� �� ������� ������ ������ � ����������� �� ������ ����� � EEPROM � ���� ������������ ������� �� �����
      _SET_BIT(control_spi1_taskes, TASK_EEPROM_WRITE_PREPARATION_BIT);
      _SET_BIT(control_spi1_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT);
      _CLEAR_BIT(control_spi1_taskes, TASK_START_WRITE_SETTINGS_EEPROM_BIT);
      /***/

      //������ ���� ���������� ���������� ��� ��������
      
      //������ ����� ��� ������ ��������� � EEPROM ����� � ����������� �����
      unsigned char crc_eeprom_settings = 0, temp_value;
      unsigned char  *point_1 = (unsigned char*)(&current_settings); 
      unsigned char  *point_2 = (unsigned char*)(&current_settings_comp); 
      for (unsigned int i =0; i < sizeof(__SETTINGS); i++)
      {
        temp_value = *(point_1);
        *(point_2) = temp_value;
        point_1++;
        point_2++;
        TxBuffer_SPI_EDF[3 + i] = temp_value;
        crc_eeprom_settings += temp_value;
      }
      //���������� ����������� ���������� ���� � ����� ������
      TxBuffer_SPI_EDF[3 + sizeof(__SETTINGS)] = (unsigned char)((~(unsigned int)crc_eeprom_settings) & 0xff);
      //���������� �� ���������� ���� � ����� ������
      TxBuffer_SPI_EDF[3 + sizeof(__SETTINGS) + 1] = (unsigned char)(crc_eeprom_settings & 0xff);
      
      //����������� ������ ���� ��������� ������ � EEPROM
      number_block_settings_write_to_eeprom = 0;
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_WRITE_USTUVANNJA_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ������ ������ � EEPROM ���������

      //������� �� ������� ������ ������ � ����������� �� ������ ����� � EEPROM � ���� ������������ ������� �� �����
      _SET_BIT(control_spi1_taskes, TASK_EEPROM_WRITE_PREPARATION_BIT);
      _SET_BIT(control_spi1_taskes, TASK_WRITING_USTUVANNJA_EEPROM_BIT);
      _CLEAR_BIT(control_spi1_taskes, TASK_START_WRITE_USTUVANNJA_EEPROM_BIT);
      
      //������ ���� ���������� ���������� ��� ��������

      //������ ����� ��� ������ ��������� � EEPROM ����� � ����������������
      unsigned char crc_eeprom_ustuvannja = 0, temp_value;
      unsigned char  *point_1; 
      unsigned char  *point_2;
      unsigned int offset = 3;

      //������ ������������� ���� ������ �������� �����������
      unsigned int adjustment_id_tmp = ADJUSTMENT_ID;
      point_1 = (unsigned char*)(&adjustment_id_tmp); 
      for (unsigned int i = 0; i < sizeof(unsigned int); i++)
      {
        temp_value = *(point_1++);
        TxBuffer_SPI_EDF[offset + i] = temp_value;
        crc_eeprom_ustuvannja += temp_value;
      }
      offset += sizeof(unsigned int);
      
      //������ ������� �����������
      point_1 = (unsigned char*)(&ustuvannja); 
      point_2 = (unsigned char*)(&ustuvannja_comp);
      for (unsigned int i =0; i < sizeof(ustuvannja); i++)
      {
        temp_value = *(point_1);
        *(point_2) = temp_value;
        point_1++;
        point_2++;
        TxBuffer_SPI_EDF[offset + i] = temp_value;
        crc_eeprom_ustuvannja += temp_value;
      }
      offset += sizeof(ustuvannja);

      //������ ������� �������� ���
      point_1 = (unsigned char*)(&phi_ustuvannja); 
      point_2 = (unsigned char*)(&phi_ustuvannja_comp);
      for (unsigned int i = 0; i < sizeof(phi_ustuvannja); i++)
      {
        temp_value = *(point_1);
        *(point_2) = temp_value;
        point_1++;
        point_2++;
        TxBuffer_SPI_EDF[offset + i] = temp_value;
        crc_eeprom_ustuvannja += temp_value;
      }
      offset += sizeof(phi_ustuvannja);

      //������ COS � SIN �������� �������� ���
      point_1 = (unsigned char*)(&phi_ustuvannja_sin_cos); 
      point_2 = (unsigned char*)(&phi_ustuvannja_sin_cos_comp);
      for (unsigned int i = 0; i < sizeof(phi_ustuvannja_sin_cos); i++)
      {
        temp_value = *(point_1);
        *(point_2) = temp_value;
        point_1++;
        point_2++;
        TxBuffer_SPI_EDF[offset + i] = temp_value;
        crc_eeprom_ustuvannja += temp_value;
      }
      offset += sizeof(phi_ustuvannja_sin_cos);

      //������ �� ������� ����� ��������
      point_1 = (unsigned char*)(&serial_number_dev); 
      point_2 = (unsigned char*)(&serial_number_dev_comp); 
      for (unsigned int i = 0; i < sizeof(serial_number_dev); i++)
      {
        temp_value = *(point_1);
        *(point_2) = temp_value;
        point_1++;
        point_2++;
        TxBuffer_SPI_EDF[offset + i] = temp_value;
        crc_eeprom_ustuvannja += temp_value;
      }
      offset += sizeof(serial_number_dev);
      
      //���������� ����������� ���������� ���� � ����� ������
      TxBuffer_SPI_EDF[offset] = (unsigned char)((~(unsigned int)crc_eeprom_ustuvannja) & 0xff);
      
      //����������� ������ ���� ��������� ������ � EEPROM
      number_block_ustuvannja_write_to_eeprom = 0;
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_WRITE_STATE_LEDS_OUTPUTS_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ������ ������ � EEPROM ����� ���������� ������ � ��������� ��������������
      
      //������� �� ������� ������ ������ � ����������� �� ������ ����� � EEPROM � ���� ������������ ������� �� �����
      _SET_BIT(control_spi1_taskes, TASK_EEPROM_WRITE_PREPARATION_BIT);
      _SET_BIT(control_spi1_taskes, TASK_WRITING_STATE_LEDS_OUTPUTS_EEPROM_BIT);
      _CLEAR_BIT(control_spi1_taskes, TASK_START_WRITE_STATE_LEDS_OUTPUTS_EEPROM_BIT);

      //������ ����� ��� ������
      unsigned int temp_value = state_trigger_leds;
      unsigned int temp_value_inv = ((unsigned int)(~temp_value)) & ((1 << NUMBER_LEDS) - 1);
      state_trigger_leds_comp = temp_value;
      TxBuffer_SPI_EDF[3 +  0] = (unsigned char)( temp_value            & 0xff);
      TxBuffer_SPI_EDF[3 +  1] = (unsigned char)((temp_value     >> 8 ) & 0xff);
      TxBuffer_SPI_EDF[3 +  2] = (unsigned char)((temp_value     >> 16) & 0xff);
      TxBuffer_SPI_EDF[3 +  3] = (unsigned char)( temp_value_inv        & 0xff);
      TxBuffer_SPI_EDF[3 +  4] = (unsigned char)((temp_value_inv >> 8 ) & 0xff);
      TxBuffer_SPI_EDF[3 +  5] = (unsigned char)((temp_value_inv >> 16) & 0xff);

      temp_value = state_signal_outputs;
      temp_value_inv = ((unsigned int)(~temp_value)) & ((1 << NUMBER_OUTPUTS) - 1);
      state_signal_outputs_comp = temp_value;
      TxBuffer_SPI_EDF[3 +  6] = (unsigned char)( temp_value            & 0xff);
      TxBuffer_SPI_EDF[3 +  7] = (unsigned char)((temp_value     >> 8 ) & 0xff);
      TxBuffer_SPI_EDF[3 +  8] = (unsigned char)((temp_value     >> 16) & 0xff);
      TxBuffer_SPI_EDF[3 +  9] = (unsigned char)( temp_value_inv        & 0xff);
      TxBuffer_SPI_EDF[3 + 10] = (unsigned char)((temp_value_inv >> 8 ) & 0xff);
      TxBuffer_SPI_EDF[3 + 11] = (unsigned char)((temp_value_inv >> 16) & 0xff);

      //����������� ������ ���� ����� ������-�������������� ������ � EEPROM
      number_block_state_leds_outputs_write_to_eeprom = 0;
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ������ ������ � EEPROM �� ������� ����������
      
      //������� �� ������� ������ ������ � ����������� �� ������ ����� � EEPROM � ���� ������������ ������� �� �����
      _SET_BIT(control_spi1_taskes, TASK_EEPROM_WRITE_PREPARATION_BIT);
      _SET_BIT(control_spi1_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT);
      _CLEAR_BIT(control_spi1_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT);

      //������ ����� ��� ������ � EEPROM ����� � ����������������
      unsigned char crc_eeprom_trg_func = 0, temp_value;
      unsigned char  *point_1; 
      unsigned char  *point_2;
      unsigned int offset = 3;

      //������ ���������� �� ��, �� �������� � ����� �����
      point_1 = (unsigned char*)(&fix_active_buttons); 
      point_2 = (unsigned char*)(&fix_active_buttons_comp);
      for (unsigned int i =0; i < sizeof(fix_active_buttons); i++)
      {
        temp_value = *(point_1);
        *(point_2) = temp_value;
        point_1++;
        point_2++;
        TxBuffer_SPI_EDF[offset + i] = temp_value;
        crc_eeprom_trg_func += temp_value;
      }
      offset += sizeof(fix_active_buttons);
      
      //������ ������ �������
      point_1 = (unsigned char*)(&trigger_active_functions); 
      point_2 = (unsigned char*)(&trigger_active_functions_comp);
      for (unsigned int i =0; i < sizeof(trigger_active_functions); i++)
      {
        temp_value = *(point_1);
        *(point_2) = temp_value;
        point_1++;
        point_2++;
        TxBuffer_SPI_EDF[offset + i] = temp_value;
        crc_eeprom_trg_func += temp_value;
      }
      offset += sizeof(trigger_active_functions);

      //���������� ����������� ���������� ���� � ����� ������
      TxBuffer_SPI_EDF[offset] = (unsigned char)((~(unsigned int)crc_eeprom_trg_func) & 0xff);

      //����������� ������ ���� ������ � EEPROM
      number_block_trg_func_write_to_eeprom = 0;
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ������ ������ � EEPROM �� ���������� ����������� ����������
      
      //������� �� ������� ������ ������ � ����������� �� ������ ����� � EEPROM � �����������, ��� ������ ������� � �������������
      _SET_BIT(control_spi1_taskes, TASK_EEPROM_WRITE_PREPARATION_BIT);
      _SET_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_AR_EEPROM_BIT);
      _CLEAR_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
      
      //������ ���� ���������� ���������� ��� ��������

      //������ ����� ��� ������ � EEPROM ����� � ����������� �����
      unsigned char crc_eeprom_info_rejestrator_ar = 0, temp_value;
      unsigned char  *point_1 = (unsigned char*)(&info_rejestrator_ar); 
      unsigned char  *point_2 = (unsigned char*)(&info_rejestrator_ar_comp); 
      for (unsigned int i = 0; i < sizeof(__INFO_AR_REJESTRATOR); i++)
      {
        temp_value = *(point_1);
        *(point_2) = temp_value;
        point_1++;
        point_2++;
        TxBuffer_SPI_EDF[3 + i] = temp_value;
        crc_eeprom_info_rejestrator_ar += temp_value;
      }

      //���������� ����������� ���������� ���� � ����� ������
      TxBuffer_SPI_EDF[3 + sizeof(info_rejestrator_ar)] = (unsigned char)((~(unsigned int)crc_eeprom_info_rejestrator_ar) & 0xff);
      
      //����������� ������ ���� ������ � EEPROM
      number_block_info_rejestrator_ar_write_to_eeprom = 0;
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ������ ������ � EEPROM �� ���������� ����������� ����������
      
      //������� �� ������� ������ ������ � ����������� �� ������ ����� � EEPROM � ���� ������������ ������� �� �����
      _SET_BIT(control_spi1_taskes, TASK_EEPROM_WRITE_PREPARATION_BIT);
      _SET_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_DR_EEPROM_BIT);
      _CLEAR_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT);
      
      //������ ����� ��� ������ � EEPROM ����� � ����������� �����
      unsigned char crc_eeprom_info_rejestrator_dr = 0, temp_value;
      unsigned char  *point_1 = (unsigned char*)(&info_rejestrator_dr); 
      unsigned char  *point_2 = (unsigned char*)(&info_rejestrator_dr_comp); 
      for (unsigned int i = 0; i < sizeof(__INFO_REJESTRATOR); i++)
      {
        temp_value = *(point_1);
        *(point_2) = temp_value;
        point_1++;
        point_2++;
        TxBuffer_SPI_EDF[3 + i] = temp_value;
        crc_eeprom_info_rejestrator_dr += temp_value;
      }

      //���������� ����������� ���������� ���� � ����� ������
      TxBuffer_SPI_EDF[3 + sizeof(info_rejestrator_dr)] = (unsigned char)((~(unsigned int)crc_eeprom_info_rejestrator_dr) & 0xff);
      
      //����������� ������ ���� ������ � EEPROM
      number_block_info_rejestrator_dr_write_to_eeprom = 0;
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ������ ������ � EEPROM �� ���������� ���������� ���������� ����

      //������� �� ������� ������ ������ � ����������� �� ������ ����� � EEPROM � ���� ������������ ������� �� �����
      _SET_BIT(control_spi1_taskes, TASK_EEPROM_WRITE_PREPARATION_BIT);
      _SET_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
      _CLEAR_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
      
      //������ ����� ��� ������ � EEPROM ����� � ����������� �����
      unsigned char crc_eeprom_info_rejestrator_pr_err = 0, temp_value;
      unsigned char  *point_1 = (unsigned char*)(&info_rejestrator_pr_err); 
      unsigned char  *point_2 = (unsigned char*)(&info_rejestrator_pr_err_comp); 
      for (unsigned int i = 0; i < sizeof(__INFO_REJESTRATOR); i++)
      {
        temp_value = *(point_1);
        *(point_2) = temp_value;
        point_1++;
        point_2++;
        TxBuffer_SPI_EDF[3 + i] = temp_value;
        crc_eeprom_info_rejestrator_pr_err += temp_value;
      }

      //���������� ����������� ���������� ���� � ����� ������
      TxBuffer_SPI_EDF[3 + sizeof(info_rejestrator_pr_err)] = (unsigned char)((~(unsigned int)crc_eeprom_info_rejestrator_pr_err) & 0xff);
      
      //����������� ������ ���� ������ � EEPROM
      number_block_info_rejestrator_pr_err_write_to_eeprom = 0;
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_WRITE_RESURS_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ������ ������ � EEPROM ������� ����������� ��� ��������� �������
      
      //������� �� ������� ������ ������ � ����������� �� ������ ����� � EEPROM � ���� ������������ ������� �� �����
      _SET_BIT(control_spi1_taskes, TASK_EEPROM_WRITE_PREPARATION_BIT);
      _SET_BIT(control_spi1_taskes, TASK_WRITING_RESURS_EEPROM_BIT);
      _CLEAR_BIT(control_spi1_taskes, TASK_START_WRITE_RESURS_EEPROM_BIT);

      //������ ����� ��� ������
      unsigned char crc_eeprom_resurs = 0, temp_value;
      unsigned char *point;
      unsigned int offset = 3;

      resurs_vymykacha_comp = resurs_vymykacha;
      point = (unsigned char*)(&resurs_vymykacha); 
      for (unsigned int i = 0; i < sizeof(resurs_vymykacha); i++)
      {
        temp_value = *(point++);
        TxBuffer_SPI_EDF[offset + i] = temp_value;
        crc_eeprom_resurs += temp_value;
      }
      offset += sizeof(resurs_vymykacha);

      resurs_vidkljuchennja_comp = resurs_vidkljuchennja;
      point = (unsigned char*)(&resurs_vidkljuchennja); 
      for (unsigned int i = 0; i < sizeof(resurs_vidkljuchennja); i++)
      {
        temp_value = *(point++);
        TxBuffer_SPI_EDF[offset + i] = temp_value;
        crc_eeprom_resurs += temp_value;
      }
      offset += sizeof(resurs_vidkljuchennja);
      
      //���������� ����������� ���������� ���� � ����� ������
      TxBuffer_SPI_EDF[offset] = (unsigned char)((~(unsigned int)crc_eeprom_resurs) & 0xff);
      
      //����������� ������ ���� ��������� ������� ������ � EEPROM
      number_block_resurs_write_to_eeprom = 0;
    }
    /*************************************************/
  }
  else if (state_execution_spi1 == 1)
  {
    /*************************************************/
    //���� ���������� ��� �������
    /*************************************************/
    //����������� �����������, �� SPI ������� �� ���� ���������� 
    state_execution_spi1 = -1;

    if(_CHECK_SET_BIT(control_spi1_taskes, TASK_EEPROM_WRITE_PREPARATION_BIT) !=0)
    {
//      /***
//      ҳ���� ��� �������
//      ***/
//      if(_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT))
//      {
//        if (etap_eeprom_write_enable == 0)
//        {
//          if (iteration == 0) array_status[number_block_settings_write_to_eeprom][0] = RxBuffer_SPI_EDF[1 + 0];
//          iteration++;
//          
//          if ((RxBuffer_SPI_EDF[1 + 0] & 0x70) != 0)
//          {
//            if (RxBuffer_SPI_EDF[1 + 0] != 0xff)
//            {
//              error_spi_eeprom++;
//            }
//            else good_spi_eeprom++;
//          }
//          else good_spi_eeprom++;
//        }
//      }
//      /**/

      //��� ���� �� ���� ������ ������, ��� ���� ��� �������� �� ���������� ������ �� ������������ ������������ ������
      if (etap_eeprom_write_enable == 0)
      {
        //��������� ������ �������

        if ((RxBuffer_SPI_EDF[1 + 0] & 0x70) != 0)
        {
          /*
          ���� 4-6 ���������� � "1" ����� �� ��� ����������� ������� ������� - 
          ����� ������������ ������ ������ �������
          */
          etap_eeprom_write_enable = 0;  
          if (RxBuffer_SPI_EDF[1 + 0] != 0xff)
          {
//            /*
//            ϳ� ��� ����������� ������� ������ �� ��� 0-7 ������� �������, 
//            ����� ������������, ����� ���� ����������.
//            ���� � - �� �������, ��� ������� ����������, ������ � �� ������ ������
//            �������������� "1" �� ���������� ����� ��3
//            */
//            GPIO_KT3->BSRR = GPIO_KT3_Pin;
          }
          else
          {
//            /*
//            ϳ� ��� ����������� ������� ������ �� ��� 0-7 ������� �������, 
//            ����� ������������, ����� ���� ����������.
//            ���� ��� � �, �� � ������ ��������� ������ �������������� "0" �� ���������� ����� ��3
//            */
//             GPIO_KT3->BRR = GPIO_KT3_Pin;
          }
        }
        else if ((RxBuffer_SPI_EDF[1 + 0] & (1 << 0)) == 0)
        {
//          /*
//          �������������� "0" �� ���������� ����� ��3 ������� ��������� ������ �
//          �������� �������/�������� ������ EEPROM
//          */
//          GPIO_KT3->BRR = GPIO_KT3_Pin;
          
          //������ ������ � EEPROM �� ����������
          if ((RxBuffer_SPI_EDF[1 + 0] & (1 << 1)) != 0)
          {
//            /***
//            ҳ���� ��� �������
//            ***/
//            if(_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT))
//            {
//              array_status[number_block_settings_write_to_eeprom][1] = RxBuffer_SPI_EDF[1 + 0];
//              array_status[number_block_settings_write_to_eeprom][2] = iteration;
//              array_status[number_block_settings_write_to_eeprom][3] = error_spi_eeprom;
//              array_status[number_block_settings_write_to_eeprom][4] = good_spi_eeprom;
//              iteration = 0;
//              error_spi_eeprom = 0;
//              good_spi_eeprom = 0;
//            }
//            /**/

            //EEPROM � ��������� �� ������
            //������� �� ��������� �� ������ EEPROM
            _CLEAR_BIT(control_spi1_taskes, TASK_EEPROM_WRITE_PREPARATION_BIT);
            etap_eeprom_write_enable = -1;
          }
          else
          {
            //EEPROM � �� ��������� �� ������ - ���������� �� ���� ������ ������� ������� ������ � EEPROM
            etap_eeprom_write_enable = 1;
          }
        }
        else
        {
          //������ �������� �������� �� ���� �������, ���� � EEPROM �� ���������� ������ ������

//          /*
//          �������������� "0" �� ���������� ����� ��3 ������� ��������� ������ �
//          �������� �������/�������� ������ EEPROM
//          */
//          GPIO_KT3->BRR = GPIO_KT3_Pin;
        }
      }
      else if (etap_eeprom_write_enable == 1)
      {
//        /*
//        �������������� "0" �� ���������� ����� ��3 ������� ��������� ������ �
//        �������� �������/�������� ������ EEPROM
//        */
//        GPIO_KT3->BRR = GPIO_KT3_Pin;
        
        //�������� ������� ������� ������ - �������� ������ ������� �������
        etap_eeprom_write_enable = 0;
        //��� ��������� �� ������ EEPROM �� �������, �� ���� ������������, �� ������ ������ ������ �����������
      }
      else
      {
        //���������� �������� ���� � �� ���� ����� �����
        //³������� ����������� �������, ���� ����� ��� �� ����������������
        total_error_sw_fixed(78);
      }
    }
    else if (
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_ENERGY_EEPROM_BIT                 ) !=0) || 
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT               ) !=0) || 
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_USTUVANNJA_EEPROM_BIT             ) !=0) ||
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_STATE_LEDS_OUTPUTS_EEPROM_BIT     ) !=0) || 
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT               ) !=0) ||
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_AR_EEPROM_BIT    ) !=0) ||
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_DR_EEPROM_BIT    ) !=0) ||
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) !=0) || 
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_RESURS_EEPROM_BIT                 ) !=0)
            )
    {
      //����� ����� ������ ����� � EEPROM

      if(_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_ENERGY_EEPROM_BIT) !=0)
      {
        //����������� ��������� ���� ��������� ������ � EEPROM
        number_block_energy_write_to_eeprom++;
      }
      else if(_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT) !=0)
      {
        //����������� ��������� ���� ��������� ������ � EEPROM
        number_block_settings_write_to_eeprom++;
      }
      else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_USTUVANNJA_EEPROM_BIT) !=0)
      {
        //����������� ��������� ���� ��������� ������ � EEPROM
        number_block_ustuvannja_write_to_eeprom++;
      }
      else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_STATE_LEDS_OUTPUTS_EEPROM_BIT) != 0)
      {
        //����������� �� ����� ������-�������������� ��� ������� - ����� ����� �������� ��������� �� �������� � ��������� ���� �� ���� ��������� ������ � ��������
        number_block_state_leds_outputs_write_to_eeprom++;
      }
      else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT) != 0)
      {
        //����������� ��������� ���� ������� ���������������� � EEPROM
        number_block_trg_func_write_to_eeprom++;
      }
      else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_AR_EEPROM_BIT) != 0)
      {
        //����������� ��������� ���� ���������� �� ����������� ������ � EEPROM
        number_block_info_rejestrator_ar_write_to_eeprom++;
      }
      else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_DR_EEPROM_BIT) != 0)
      {
        //����������� ��������� ���� ���������� �� ����������� ������ � EEPROM
        number_block_info_rejestrator_dr_write_to_eeprom++;
      }
      else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) != 0)
      {
        //����������� ��������� ���� ���������� �� ����������� ������ � EEPROM
        number_block_info_rejestrator_pr_err_write_to_eeprom++;
      }
      else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_RESURS_EEPROM_BIT) != 0)
      {
        //����������� ��������� ���� ���������� �� ���������� ������ � EEPROM
        number_block_resurs_write_to_eeprom++;
      }         
      else
      {
        //���� �������� �� ���� � ���������� ����� ��������
        //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
        total_error_sw_fixed(74);
      }

      //����������� �� ������������ ������� �� �����
      _SET_BIT(control_spi1_taskes, TASK_EEPROM_WRITE_PREPARATION_BIT);
    }
    else if(
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_ENERGY_EEPROM_BIT                 ) !=0) ||
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_USTUVANNJA_EEPROM_BIT             ) !=0) ||
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_SETTINGS_EEPROM_BIT               ) !=0) ||
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_STATE_LEDS_OUTPUTS_EEPROM_BIT     ) !=0) ||
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT               ) !=0) ||
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_AR_EEPROM_BIT    ) !=0) ||  
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_DR_EEPROM_BIT    ) !=0) ||  
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) !=0) ||  
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_RESURS_EEPROM_BIT                 ) !=0) 
           )  
    {
      //��������� ������ �������
      if ((RxBuffer_SPI_EDF[1 + 0] & (1 << 0)) == 0)
      {
        //������ ������ � EEPROM �� ����������
        //������ ������ � EEPROM �� ����������
        if (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_ENERGY_EEPROM_BIT) !=0)
        {
          //������� �� ������� ������� ��������� � ����������� �� ������� ������� ���������
          _SET_BIT(control_spi1_taskes, TASK_READING_ENERGY_EEPROM_BIT);
          _CLEAR_BIT(control_spi1_taskes, TASK_START_READ_ENERGY_EEPROM_BIT);
        }
        else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_USTUVANNJA_EEPROM_BIT) !=0)
        {
          //������� �� ������� ������� ��������� � ����������� �� ������� ������� ���������
          _SET_BIT(control_spi1_taskes, TASK_READING_USTUVANNJA_EEPROM_BIT);
          _CLEAR_BIT(control_spi1_taskes, TASK_START_READ_USTUVANNJA_EEPROM_BIT);
        }
        else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_SETTINGS_EEPROM_BIT) !=0)
        {
          //������� �� ������� ������� ��������� � ����������� �� ������� ������� ���������
          _SET_BIT(control_spi1_taskes, TASK_READING_SETTINGS_EEPROM_BIT);
          _CLEAR_BIT(control_spi1_taskes, TASK_START_READ_SETTINGS_EEPROM_BIT);
        }
        else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_STATE_LEDS_OUTPUTS_EEPROM_BIT) !=0)
        {
          //������� �� ������� ������� ����� ��������� ��������� � ���������� ���� � ����������� �� ������� ������� ��������� ��������� � ���������� ����
          _SET_BIT(control_spi1_taskes, TASK_READING_STATE_LEDS_OUTPUTS_EEPROM_BIT);
          _CLEAR_BIT(control_spi1_taskes, TASK_START_READ_STATE_LEDS_OUTPUTS_EEPROM_BIT);
        }
        else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT) !=0)
        {
          //������� �� ������� ������� ����� ������� ���������� � ����������� �� ������� ������� ������� ����������
          _SET_BIT(control_spi1_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT);
          _CLEAR_BIT(control_spi1_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT);
        }
        else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_AR_EEPROM_BIT) !=0)
        {
          //������� �� ������� ������� ���������� �� ����������� ���������� � ����������� �� ������� ������� ���������� �� ����������� ����������
          _SET_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_AR_EEPROM_BIT);
          _CLEAR_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_AR_EEPROM_BIT);
        }
        else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_DR_EEPROM_BIT) !=0)
        {
          //������� �� ������� ������� ���������� �� ����������� ���������� � ����������� �� ������� ������� ���������� �� ����������� ����������
          _SET_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_DR_EEPROM_BIT);
          _CLEAR_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_DR_EEPROM_BIT);
        }
        else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) !=0)
        {
          //������� �� ������� ������� ���������� �� ����������� ���������� � ����������� �� ������� ������� ���������� �� ����������� ����������
          _SET_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
          _CLEAR_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
        }
        else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_RESURS_EEPROM_BIT) !=0)
        {
          //������� �� ������� ������� ���������� � ����������� �� ������� ������� ���������� 
          _SET_BIT(control_spi1_taskes, TASK_READING_RESURS_EEPROM_BIT);
          _CLEAR_BIT(control_spi1_taskes, TASK_START_READ_RESURS_EEPROM_BIT);
        }
        else
        {
          //���� �������� �� ���� � ���������� ����� ��������
          //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
          total_error_sw_fixed(76);
        }
      }
      else
      {
        //������ �������� �������� �� ���� �������, ���� � EEPROM �� ���������� ������ ������
      }
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_ENERGY_EEPROM_BIT) !=0)
    {
      //�������� �������� ���
      //�������� ��������, �� ���������� ���� � ������, �� ��� ���������� ���������
      unsigned int empty_block = 1, i = 0; 
      double energy_tmp[MAX_NUMBER_INDEXES_ENERGY];

      while ((empty_block != 0) && ( i < (SIZE_ENERGY + 1)))
      {
        if (RxBuffer_SPI_EDF[3 + i] != 0xff) empty_block = 0;
        i++;
      }
      
      if(empty_block == 0)
      {
        //�������, �� ���� ������ �� � ������
        state_spi1_task &= (unsigned int)(~STATE_ENERGY_EEPROM_EMPTY);
        //������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_ENERGY_EEPROM_EMPTY_BIT);
        
        //���������� ���������� ���� � ���������� �������� ��� � ����� ������
        unsigned char crc_eeprom_energy = 0, temp_value;
        unsigned char  *point;
        unsigned int offset = 3;
        
        point = (unsigned char*)(&energy_tmp); 
        for (i =0; i < sizeof(energy_tmp); i++)
        {
          temp_value = RxBuffer_SPI_EDF[offset + i];
          *(point) = temp_value;
          crc_eeprom_energy += temp_value;
          point++;
        }
        offset +=  sizeof(energy_tmp);

        if (RxBuffer_SPI_EDF[offset]  == ((unsigned char)((~(unsigned int)crc_eeprom_energy) & 0xff)))
        {
          //����������� ���� ���������

          //������� ����������� � ���� ����������
          _SET_BIT(clear_diagnostyka, ERROR_ENERGY_EEPROM_BIT);
          
          if ((comparison_writing & COMPARISON_WRITING_ENERGY) == 0)
          {
            //������������ ���������� ������ � ����� ������
            
            //���������� ����� ��������� � ����������� ������ � ������� �����
            state_calc_energy = true;
            for(unsigned int k = 0; k < MAX_NUMBER_INDEXES_ENERGY; k++) energy[0][k] = energy_tmp[k];
            state_calc_energy = false;
            for(unsigned int k = 0; k < MAX_NUMBER_INDEXES_ENERGY; k++) energy[1][k] = energy[0][k];
          }
          else
          {
            //������������ �������� ����������� �������� ���������� � EEPROM � �����������
            
            unsigned int difference = 0;
  
            i = 0;
            while ((difference == 0) && (i < MAX_NUMBER_INDEXES_ENERGY))
            {
              //�������� ������ ������
              if (energy_comp[i] != energy_tmp[i])
              {
                difference = 0xff;
              }
              else
              {
                i++;
              }
            }
            
            if (difference == 0)
            {
              //�������� ���������� ������� ������
  
              //������� ����������� � ���� ����������
              _SET_BIT(clear_diagnostyka, ERROR_ENERGY_EEPROM_COMPARISON_BIT);
            }
            else
            {
              //�������� ���������� ���������� ��������� �� ��������� � ����������� �����������

              //���������� ����������� � ���� ����������
              _SET_BIT(set_diagnostyka, ERROR_ENERGY_EEPROM_COMPARISON_BIT);
            }
          }

          state_spi1_task &= (unsigned int)(~STATE_ENERGY_EEPROM_FAIL);
          state_spi1_task |= STATE_ENERGY_EEPROM_GOOD;
        }
        else
        {
          //���������� ���� �� ���������
          state_spi1_task &= (unsigned int)(~STATE_ENERGY_EEPROM_GOOD);
          state_spi1_task |= STATE_ENERGY_EEPROM_FAIL;
          
          //���������� ����������� � ���� ����������
          _SET_BIT(set_diagnostyka, ERROR_ENERGY_EEPROM_BIT);
        }
      }
      else
      {
        //�������, �� ���������� ���� ��� ������ � ������
        state_spi1_task &= (unsigned int)(~STATE_ENERGY_EEPROM_FAIL);
        state_spi1_task &= (unsigned int)(~STATE_ENERGY_EEPROM_GOOD);
        state_spi1_task |= STATE_ENERGY_EEPROM_EMPTY;
        
        //���������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_ENERGY_EEPROM_BIT);
        _SET_BIT(set_diagnostyka, ERROR_ENERGY_EEPROM_EMPTY_BIT);
      }
            
      //������ ������� �����������, �� ������������ ����������
      comparison_writing &= (unsigned int)(~COMPARISON_WRITING_ENERGY);
      //������� ����������� ��� ������� �����
      _CLEAR_BIT(control_spi1_taskes, TASK_READING_ENERGY_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_SETTINGS_EEPROM_BIT) !=0)
    {
      //�������� �������� ���
      //�������� ��������, �� ���������� ���� � ������, �� ��� ���������� ���������
      unsigned int empty_block = 1, i = 0; 
      __SETTINGS current_settings_tmp;
      
      while ((empty_block != 0) && ( i < (sizeof(__SETTINGS) + 1 + 1)))
      {
        if (RxBuffer_SPI_EDF[3 + i] != 0xff) empty_block = 0;
        i++;
      }
      
      if(empty_block == 0)
      {
        //�������, �� ���� ������������ �� � ������
        state_spi1_task &= (unsigned int)(~STATE_SETTINGS_EEPROM_EMPTY);
        //������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_EMPTY_BIT);
        
        //���������� ���������� ���� � ���������� �������� ��� � ��������� ���������
        unsigned char crc_eeprom_settings = 0, temp_value;
        unsigned char  *point = (unsigned char*)(&current_settings_tmp); 
        for (i =0; i < sizeof(__SETTINGS); i++)
        {
          temp_value = RxBuffer_SPI_EDF[3 + i];
          *(point) = temp_value;
          crc_eeprom_settings += temp_value;
          point++;
        }
        if (
            (RxBuffer_SPI_EDF[3 + sizeof(__SETTINGS)    ]  == ((unsigned char)((~(unsigned int)crc_eeprom_settings) & 0xff))) &&
            (RxBuffer_SPI_EDF[3 + sizeof(__SETTINGS) + 1]  == ((unsigned char)(                crc_eeprom_settings  & 0xff)))
           )   
        {
          //����������� ���� ���������

          //������� ����������� � ���� ����������
          _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_BIT);

          if (current_settings_tmp.device_id == ((VERSIA_PZ << 8) | (MODYFIKACIA_VERSII_PZ)))
          {
            //������� ��������� ������� ���� ������ �������
            
            //�������� ���������� ���� (�� �����������)
            crc_settings = crc_eeprom_settings;

            if ((comparison_writing & COMPARISON_WRITING_SETTINGS) == 0)
            {
              //������������ ���������� ��������� � ������� ���������
            
              //�������, �� ������� ����� �������� � �� ����� ���� � ������� ������� ��������� � ������� � ���� ������ ������� �������
              changed_settings = CHANGED_ETAP_EXECUTION;
              //���������� ������� ��������� � ����������� ������ � ������ �������
              current_settings = current_settings_tmp;
              //�������, �� ������� �������� � �� ����� ���� � ������� ������� ��������� � ������� � ���� ������ ������� �������
              changed_settings = CHANGED_ETAP_ENDED;
              current_settings_interfaces = current_settings;

              //����������� ����� ������ ������ � ����������� ������� ������ � ����������� ��������� ��� ����� ��������
              /*
              ������� ��������� � ��������� ���� �� ���� ������� ������ ���������, � �� ������, �� �� �� ������ ���������� ����� ���
              �� �� ���������� ��������� ���� ����� � ������
              */
              //�������� ���������� ����� ����� ������� �������
              {
                uint32_t number_words_slice = NUMBER_ANALOG_CANALES + NUMBER_WORD_DIGITAL_PART_AR;
                uint32_t total_size = (current_settings.prefault_number_periods << VAGA_NUMBER_POINT_AR)*number_words_slice;
                int32_t difference = index_array_ar_heat - total_size;
                uint32_t index = (difference >= 0) ? difference : (difference + SIZE_BUFFER_FOR_AR);

                uint32_t m = 0;
                for (size_t l = 0; l < total_size; l++)
                {
                  int32_t data_tmp = (m < NUMBER_ANALOG_CANALES) ? 0x8000 : 0;
                  if (++m >= number_words_slice) m = 0;
                  
                  array_ar[index++] = data_tmp;
//                  AR_WRITE(index, data_tmp);
                  if (index >= SIZE_BUFFER_FOR_AR) index = 0; /*����� ��� �� ���� ==, ��� ��� ��������������� �� ����������� ������� � �������� >=*/
                }
              } 
              make_koef_for_resurs();
#if (                                   \
     (MODYFIKACIA_VERSII_PZ == 0) ||    \
     (MODYFIKACIA_VERSII_PZ == 3)       \
    )   
              _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD28) = (((current_settings.zdz_ovd_porig + 1) & 0xf) << 8) | (0 << 12);
#endif
            }
            else
            {
              //������������ �������� ����������� �������� ���������� � EEPROM � �����������
            
              unsigned char  *point_to_read  = (unsigned char*)(&current_settings_tmp );
              unsigned char  *point_to_write = (unsigned char*)(&current_settings_comp);
              unsigned int difference = 0;

              i = 0;
              while ((difference == 0) && ( i < sizeof(__SETTINGS)))
              {
                if (*point_to_write != *point_to_read) difference = 0xff;
                else
                {
                  point_to_write++;
                  point_to_read++;
                  i++;
                }
              }
              if (difference == 0)
              {
                //�������� ���������� ������� ������

                //������� ����������� � ���� ����������
                _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_COMPARISON_BIT);
              }
              else
              {
                //�������� ���������� ���������� ��������� �� ��������� � ����������� �����������

                //���������� ����������� � ���� ����������
                _SET_BIT(set_diagnostyka, ERROR_SETTINGS_EEPROM_COMPARISON_BIT);
              }
            }

            state_spi1_task &= (unsigned int)(~STATE_SETTINGS_EEPROM_FAIL);
            state_spi1_task |= STATE_SETTINGS_EEPROM_GOOD;
          
            //������� ����������� � ���� ����������
            _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_DEVICE_ID_FAIL_BIT);
          }
          else
          {
            //������� ��������� �� ������� ���� ������ �������

            //�������, �� ���������� ���� ��������� � ������
            state_spi1_task &= (unsigned int)(~STATE_SETTINGS_EEPROM_FAIL);
            state_spi1_task &= (unsigned int)(~STATE_SETTINGS_EEPROM_GOOD);
            state_spi1_task |= STATE_SETTINGS_EEPROM_EMPTY; /*�� ���������� ���� ��������� �� �� ���� �� �� ���� ������*/
        
            //���������� ����������� � ���� ����������
            _SET_BIT(set_diagnostyka, ERROR_SETTINGS_EEPROM_DEVICE_ID_FAIL_BIT);
          }
        }
        else
        {
          //���������� ���� �� ���������
          state_spi1_task &= (unsigned int)(~STATE_SETTINGS_EEPROM_GOOD);
          state_spi1_task |= STATE_SETTINGS_EEPROM_FAIL;
          
          //���������� ����������� � ���� ����������
          _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_DEVICE_ID_FAIL_BIT);
          _SET_BIT(set_diagnostyka, ERROR_SETTINGS_EEPROM_BIT);
        }
      }
      else
      {
        //�������, �� ���������� ���� ��������� � ������
        state_spi1_task &= (unsigned int)(~STATE_SETTINGS_EEPROM_FAIL);
        state_spi1_task &= (unsigned int)(~STATE_SETTINGS_EEPROM_GOOD);
        state_spi1_task |= STATE_SETTINGS_EEPROM_EMPTY;
        
        //���������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_BIT);
        _SET_BIT(clear_diagnostyka, ERROR_SETTINGS_EEPROM_DEVICE_ID_FAIL_BIT);
        _SET_BIT(set_diagnostyka, ERROR_SETTINGS_EEPROM_EMPTY_BIT);
      }
            
      //������ ������� �����������, �� ������������ ����������
      comparison_writing &= (unsigned int)(~COMPARISON_WRITING_SETTINGS);
      //������� ����������� ��� ������� �����
      _CLEAR_BIT(control_spi1_taskes, TASK_READING_SETTINGS_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_USTUVANNJA_EEPROM_BIT) !=0)
    {
      //�������� �������� ���
      //�������� ��������, �� ���������� ���� � ������, �� ��� ���������� ���������
      unsigned int empty_block = 1, i = 0; 
      unsigned int adjustment_id_tmp, ustuvannja_tmp[NUMBER_ANALOG_CANALES], serial_number_dev_tmp;
      int phi_ustuvannja_tmp[NUMBER_ANALOG_CANALES];
      float phi_ustuvannja_sin_cos_tmp[2*NUMBER_ANALOG_CANALES];

      while ((empty_block != 0) && ( i < (SIZE_USTUVANNJA + 1)))
      {
        if (RxBuffer_SPI_EDF[3 + i] != 0xff) empty_block = 0;
        i++;
      }
      
      if(empty_block == 0)
      {
        //�������, �� ���� ������������ �� � ������
        state_spi1_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_EMPTY);
        //������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_EMPTY_BIT);
        
        //���������� ���������� ���� � ���������� �������� ��� � ����� ��������� � ������� �������
        unsigned char crc_eeprom_ustuvannja = 0, temp_value;
        unsigned char  *point;
        unsigned int offset = 3;

        point = (unsigned char*)(&adjustment_id_tmp); 
        for (i =0; i < sizeof(unsigned int); i++)
        {
          temp_value = RxBuffer_SPI_EDF[offset + i];
          *(point) = temp_value;
          crc_eeprom_ustuvannja += temp_value;
          point++;
        }
        offset += sizeof(unsigned int);
        
        point = (unsigned char*)(&ustuvannja_tmp); 
        for (i =0; i < sizeof(ustuvannja_tmp); i++)
        {
          temp_value = RxBuffer_SPI_EDF[offset + i];
          *(point) = temp_value;
          crc_eeprom_ustuvannja += temp_value;
          point++;
        }
        offset +=  sizeof(ustuvannja_tmp);
        
        point = (unsigned char*)(&phi_ustuvannja_tmp); 
        for (i =0; i < sizeof(phi_ustuvannja_tmp); i++)
        {
          temp_value = RxBuffer_SPI_EDF[offset + i];
          *(point) = temp_value;
          crc_eeprom_ustuvannja += temp_value;
          point++;
        }
        offset +=  sizeof(phi_ustuvannja_tmp);
        
        point = (unsigned char*)(&phi_ustuvannja_sin_cos_tmp); 
        for (i =0; i < sizeof(phi_ustuvannja_sin_cos_tmp); i++)
        {
          temp_value = RxBuffer_SPI_EDF[offset + i];
          *(point) = temp_value;
          crc_eeprom_ustuvannja += temp_value;
          point++;
        }
        offset +=  sizeof(phi_ustuvannja_sin_cos_tmp);
        
        point = (unsigned char*)(&serial_number_dev_tmp); 
        for (i =0; i < sizeof(serial_number_dev_tmp); i++)
        {
          temp_value = RxBuffer_SPI_EDF[offset + i];
          *(point) = temp_value;
          crc_eeprom_ustuvannja += temp_value;
          point++;
        }
        offset += sizeof(serial_number_dev_tmp);

        if (RxBuffer_SPI_EDF[offset]  == ((unsigned char)((~(unsigned int)crc_eeprom_ustuvannja) & 0xff)))
        {
          //����������� ���� ���������

          //������� ����������� � ���� ����������
          _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_BIT);
          
          if (adjustment_id_tmp == ADJUSTMENT_ID)
          {
            //��� ������ �������� ����������� ������� ������ ����������� ������������

            //�������� ���������� ���� (�� �����������)
            crc_ustuvannja = crc_eeprom_ustuvannja;
          
            if ((comparison_writing & COMPARISON_WRITING_USTUVANNJA) == 0)
            {
              //������������ ���������� ��������� � ����� ���������
            
              //�������, �� ��������� ����� ���� ���������� � �� ����� ���� � ����������� ������� ��������� � ������� � ���� ������ ����������� �������
              changed_ustuvannja = CHANGED_ETAP_EXECUTION;
              //���������� ����� ��������� � ����������� ������ � ������� �����
              for(unsigned int k = 0; k < NUMBER_ANALOG_CANALES; k++) 
              {
                ustuvannja[k] = ustuvannja_tmp[k];

                phi_ustuvannja[k] = phi_ustuvannja_tmp[k];
                phi_ustuvannja_sin_cos[2*k    ] = phi_ustuvannja_sin_cos_tmp[2*k    ];
                phi_ustuvannja_sin_cos[2*k + 1] = phi_ustuvannja_sin_cos_tmp[2*k + 1];
              }
              serial_number_dev = serial_number_dev_tmp;
              //�������, �� ��������� �������� � �� ����� ���� � ����������� ������� ��������� � ����� � ���� ������ ����������� �������
              changed_ustuvannja = CHANGED_ETAP_ENDED;
            }
            else
            {
              //������������ �������� ����������� �������� ���������� � EEPROM � �����������
            
              unsigned int difference = 0;
  
              i = 0;
              while ((difference == 0) && (i < NUMBER_ANALOG_CANALES))
              {
                //�������� ������ �������� �����������
                if (
                    (ustuvannja_comp[i] != ustuvannja_tmp[i]) ||
                    (phi_ustuvannja_comp[i] != phi_ustuvannja_tmp[i]) ||
                    (phi_ustuvannja_sin_cos_comp[2*i] != phi_ustuvannja_sin_cos_tmp[2*i]) ||
                    (phi_ustuvannja_sin_cos_comp[2*i+1] != phi_ustuvannja_sin_cos_tmp[2*i+1])
                   )
                {
                  difference = 0xff;
                }
                else
                {
                  i++;
                }
              }
              if (difference == 0) 
              {
                //�������� ������ �������� ������ (���� �� ���� �� ����������� ��� �������)
                if (serial_number_dev_comp != serial_number_dev_tmp) difference = 0xff;
              }
            
              if (difference == 0)
              {
                //�������� ���������� ������� ������
  
                //������� ����������� � ���� ����������
                _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_COMPARISON_BIT);
              }
              else
              {
                //�������� ���������� ���������� ��������� �� ��������� � ����������� �����������

                //���������� ����������� � ���� ����������
                _SET_BIT(set_diagnostyka, ERROR_USTUVANNJA_EEPROM_COMPARISON_BIT);
              }
            }

            state_spi1_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_FAIL);
            state_spi1_task |= STATE_USTUVANNJA_EEPROM_GOOD;
          
            //������� ����������� � ���� ����������
            _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT);
          }
          else
          {
            //��� ������ �������� ����������� �� ������� ������ ����������� ������������

            //�������, �� ���������� ���� ��������� � ������
            state_spi1_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_FAIL);
            state_spi1_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_GOOD);
            state_spi1_task |= STATE_USTUVANNJA_EEPROM_EMPTY;/*�� ���������� ���� �������� ����������� -  �� �� ���� �� �� ���� ������*/
        
            //���������� ����������� � ���� ����������
            _SET_BIT(set_diagnostyka, ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT);
          }
        }
        else
        {
          //���������� ���� �� ���������
          state_spi1_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_GOOD);
          state_spi1_task |= STATE_USTUVANNJA_EEPROM_FAIL;
          
          //���������� ����������� � ���� ����������
          _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT);
          _SET_BIT(set_diagnostyka, ERROR_USTUVANNJA_EEPROM_BIT);
        }
      }
      else
      {
        //�������, �� ���������� ���� ��������� � ������
        state_spi1_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_FAIL);
        state_spi1_task &= (unsigned int)(~STATE_USTUVANNJA_EEPROM_GOOD);
        state_spi1_task |= STATE_USTUVANNJA_EEPROM_EMPTY;
        
        //���������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_BIT);
        _SET_BIT(clear_diagnostyka, ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT);
        _SET_BIT(set_diagnostyka, ERROR_USTUVANNJA_EEPROM_EMPTY_BIT);
      }
            
      //������ ������� �����������, �� ������������ ����������
      comparison_writing &= (unsigned int)(~COMPARISON_WRITING_USTUVANNJA);
      //������� ����������� ��� ������� �����
      _CLEAR_BIT(control_spi1_taskes, TASK_READING_USTUVANNJA_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_STATE_LEDS_OUTPUTS_EEPROM_BIT) !=0)
    {
      //�������� �������� ���
      //�������� ��������, �� ���������� ���� � ������, �� ��� ���������� ���������
      unsigned int empty_block = 1, i = 0; 
      unsigned int state_trigger_leds_tmp, state_signal_outputs_tmp;
      
      while ((empty_block != 0) && ( i < (2*(3 + 3))))
      {
        if (RxBuffer_SPI_EDF[3 + i] != 0xff) empty_block = 0;
        i++;
      }
      
      if(empty_block == 0)
      {
        //�������, �� ���� �� � ������
        state_spi1_task &= (unsigned int)(~STATE_STATE_LEDS_OUTPUTS_EEPROM_EMPTY);
        
        //������� ����������� � ���� ����������, �� ���� ������
        _SET_BIT(clear_diagnostyka, ERROR_STATE_LEDS_OUTPUTS_EEPROM_EMPTY_BIT);
        
        //���������� ����������� ����� ��������� ����������
        state_trigger_leds_tmp = RxBuffer_SPI_EDF[3 + 0] | (RxBuffer_SPI_EDF[3 + 1] << 8) | (RxBuffer_SPI_EDF[3 + 2] << 16);
        unsigned int value_1 = RxBuffer_SPI_EDF[3 + 3] | (RxBuffer_SPI_EDF[3 + 4] << 8) | (RxBuffer_SPI_EDF[3 + 5] << 16);
        if (state_trigger_leds_tmp == ((unsigned int)((~value_1) & ((1 << NUMBER_LEDS) - 1))) )
        {
          //��������� �������

          if ((comparison_writing & COMPARISON_WRITING_STATE_LEDS_OUTPUTS) == 0)
          {
            //������������ ���������� ����� ��������� ��������������/���������� ������

            //³��������� ���������� �� ��������� ���������������
            state_leds = state_trigger_leds = state_trigger_leds_tmp;
          }
          
          state_spi1_task &= (unsigned int)(~STATE_STATE_LEDS_EEPROM_FAIL);
          state_spi1_task |= STATE_STATE_LEDS_EEPROM_GOOD;
          
          //������� ����������� � ���� ����������
          _SET_BIT(clear_diagnostyka, ERROR_STATE_LEDS_EEPROM_BIT);
        }
        else
        {
          //��������� �� �������
          state_spi1_task &= (unsigned int)(~STATE_STATE_LEDS_EEPROM_GOOD);
          state_spi1_task |= STATE_STATE_LEDS_EEPROM_FAIL;
          
          //���������� ����������� � ���� ����������
          _SET_BIT(set_diagnostyka, ERROR_STATE_LEDS_EEPROM_BIT);
        }

        //���������� ����������� ����� ���������� ������
        state_signal_outputs_tmp = RxBuffer_SPI_EDF[3 + 6] | (RxBuffer_SPI_EDF[3 + 7] << 8) | (RxBuffer_SPI_EDF[3 + 8] << 16);
        value_1 = RxBuffer_SPI_EDF[3 + 9] | (RxBuffer_SPI_EDF[3 + 10] << 8) | (RxBuffer_SPI_EDF[3 + 11] << 16);
        if (state_signal_outputs_tmp == ((unsigned int)((~value_1) & ((1 << NUMBER_OUTPUTS) - 1))) )
        {
          //��������� �������

          if ((comparison_writing & COMPARISON_WRITING_STATE_LEDS_OUTPUTS) == 0)
          {
            //������������ ���������� ����� ��������� ��������������/���������� ������

            //³��������� ���������� �� ���������� �������
            state_outputs_raw = state_outputs = state_signal_outputs = state_signal_outputs_tmp;
          }

          state_spi1_task &= (unsigned int)(~STATE_STATE_OUTPUTS_EEPROM_FAIL);
          state_spi1_task |= STATE_STATE_OUTPUTS_EEPROM_GOOD;
          
          //������� ����������� � ���� ����������
          _SET_BIT(clear_diagnostyka, ERROR_STATE_OUTPUTS_EEPROM_BIT);
        }
        else
        {
          //��������� �� �������
          state_spi1_task &= (unsigned int)(~STATE_STATE_OUTPUTS_EEPROM_GOOD);
          state_spi1_task |= STATE_STATE_OUTPUTS_EEPROM_FAIL;
          
          //���������� ����������� � ���� ����������
          _SET_BIT(set_diagnostyka, ERROR_STATE_OUTPUTS_EEPROM_BIT);
        }
      }
      else
      {
        //�������, �� ���������� ���� � ������
        state_spi1_task &= (unsigned int)(
                                         ~(
                                           STATE_STATE_LEDS_EEPROM_FAIL    |
                                           STATE_STATE_LEDS_EEPROM_GOOD    |
                                           STATE_STATE_OUTPUTS_EEPROM_FAIL |
                                           STATE_STATE_OUTPUTS_EEPROM_GOOD
                                          )
                                         );
        state_spi1_task |= STATE_STATE_LEDS_OUTPUTS_EEPROM_EMPTY;
        
        //���������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_STATE_LEDS_EEPROM_BIT);
        _SET_BIT(clear_diagnostyka, ERROR_STATE_OUTPUTS_EEPROM_BIT);
        _SET_BIT(set_diagnostyka, ERROR_STATE_LEDS_OUTPUTS_EEPROM_EMPTY_BIT);

        if ((comparison_writing & COMPARISON_WRITING_STATE_LEDS_OUTPUTS) == 0)
        {
          /*
          ����������� ����������� ��� ��, �� � EEPROM ����� �������� ��� ��������
          ���������� ������ � ��������� �������������� ����� ���, ���� �� �������
          �������� ��� ��� ���������� �� � ���������� ���'��, � �� ���� �� ��������� 
          �������� ������.
          �� ��� �������� ������ ��� ������� ����� �� ������ ���������� ���, �� � � 
          ���������� ���'�� � ��� �����, �����, ���� ����� ������� �������, ��,
          ������� �� �������� � ������� � ���������� ���'��,  �� � � ��� ��������,
          �� �� �� ����� � ����������, �� �� ������ �� ���������������� ����������� ������������� 
          ��� ������ � EEPROM �� ��� �� ��������
          */
          _SET_BIT(control_spi1_taskes, TASK_START_WRITE_STATE_LEDS_OUTPUTS_EEPROM_BIT);
        }
      }

      if ((comparison_writing & COMPARISON_WRITING_STATE_LEDS_OUTPUTS) == 0)
      {
        //ϳ��� ����������� ���������� ����� ��������� ��������������/���������� ������ - ������� �� � ����-05�
        
        //�������� ���������� �� ��������������� �� ���������
        for (size_t col = 0; col < LED_N_COL; col++) _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD32_DD38) = ((1 << col) << LED_N_ROW) | ((uint32_t)(~0) & ((1 << LED_N_ROW) - 1));
        
        //����������� �� CON-L, ��� ����� ���� ��������� ���������������
        GPIO_SetBits(CON_L, CON_L_PIN);

        //�������� ���������� �� ������� �� ��� ���������
        _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD31_DD34_DD35_DD37) = state_outputs_raw;
        TIM_PRT_write_tick = TIM2->CNT;
        //����������� �� CON-OUTPUTS-1, ��� ����� ���� ��������� ��������
//        GPIO_SetBits(CON_OUTPUTS, CON_1_OUTPUTS_PIN);
//        //������ �� CON-OUTPUTS-2, ��� ����� ���� ��������� ���������
//        GPIO_ResetBits(CON_OUTPUTS, CON_2_OUTPUTS_PIN);
//        //�����������  �� CON-OUTPUTS-3, ��� ����� ���� ��������� ��������
//        GPIO_SetBits(CON_OUTPUTS, CON_3_OUTPUTS_PIN);
      }
      else
      {
        //������������ �������� ����������� �������� ���������� � EEPROM � �����������
        
        if(
           (state_spi1_task & (STATE_STATE_LEDS_EEPROM_GOOD | STATE_STATE_OUTPUTS_EEPROM_GOOD)) == 
                             (STATE_STATE_LEDS_EEPROM_GOOD | STATE_STATE_OUTPUTS_EEPROM_GOOD)
          )
        {
          //�������� ������ ��������� ����� ���, ���� ���� ���� ������� �� � ������ � ������� �� �����������
          if (
              (state_trigger_leds_comp   == state_trigger_leds_tmp   ) &&
              (state_signal_outputs_comp == state_signal_outputs_tmp )
             )   
          {
            //�������� ���������� ������� ������

            //������� ����������� � ���� ����������
            _SET_BIT(clear_diagnostyka, ERROR_STATE_LEDS_OUTPUTS_EEPROM_COMPARISON_BIT);
          }
          else
          {
            //�������� ���������� ���������� ��������� �� ��������� � ����������� �����������

            //���������� ����������� � ���� ����������
            _SET_BIT(set_diagnostyka, ERROR_STATE_LEDS_OUTPUTS_EEPROM_COMPARISON_BIT);
          }
        }
      }

      //������ ������� �����������, �� ������������ ����������
      comparison_writing &= (unsigned int)(~COMPARISON_WRITING_STATE_LEDS_OUTPUTS);
      //������� ����������� ��� ������� �����
      _CLEAR_BIT(control_spi1_taskes, TASK_READING_STATE_LEDS_OUTPUTS_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT) !=0)
    {
      //�������� �������� ���
      //�������� ��������, �� ���������� ���� � ������, �� ��� ���������� ���������
      unsigned int empty_block = 1, i = 0; 
      unsigned int fix_active_buttons_tmp, trigger_active_functions_tmp[N_BIG];

      while ((empty_block != 0) && ( i < (sizeof(fix_active_buttons_tmp) + sizeof(trigger_active_functions_tmp) + 1)))
      {
        if (RxBuffer_SPI_EDF[3 + i] != 0xff) empty_block = 0;
        i++;
      }
      
      if(empty_block == 0)
      {
        //�������, �� ���� �� � ������
        state_spi1_task &= (unsigned int)(~STATE_TRG_FUNC_EEPROM_EMPTY);
        //������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_TRG_FUNC_EEPROM_EMPTY_BIT);
        
        //���������� ���������� ���� � ���������� �������� ��� � �������� ����
        unsigned char crc_eeprom_trg_func = 0, temp_value;
        unsigned char  *point;
        unsigned int offset = 3;

        point = (unsigned char*)(&fix_active_buttons_tmp); 
        for (i =0; i < sizeof(fix_active_buttons_tmp); i++)
        {
          temp_value = RxBuffer_SPI_EDF[offset + i];
          *(point) = temp_value;
          crc_eeprom_trg_func += temp_value;
          point++;
        }
        offset +=  sizeof(fix_active_buttons_tmp);

        point = (unsigned char*)(&trigger_active_functions_tmp); 
        for (i =0; i < sizeof(trigger_active_functions_tmp); i++)
        {
          temp_value = RxBuffer_SPI_EDF[offset + i];
          *(point) = temp_value;
          crc_eeprom_trg_func += temp_value;
          point++;
        }
        offset +=  sizeof(trigger_active_functions_tmp);
        
        if (RxBuffer_SPI_EDF[offset]  == ((unsigned char)((~(unsigned int)crc_eeprom_trg_func) & 0xff)))
        {
          //����������� ���� ���������

          //������� ����������� � ���� ����������
          _SET_BIT(clear_diagnostyka, ERROR_TRG_FUNC_EEPROM_BIT);
          
          //�������� ���������� ���� (�� �����������)
          crc_trg_func = crc_eeprom_trg_func;
          
          if ((comparison_writing & COMPARISON_WRITING_TRG_FUNC) == 0)
          {
            //������������ ���������� ������� ����������
            
            //���������� ������� ���������� � ������ ����
            fix_active_buttons = fix_active_buttons_tmp;
            for(unsigned int k = 0; k < N_BIG; k++) trigger_active_functions[k] = trigger_active_functions_tmp[k];
            restore_trigger_functions(trigger_active_functions);
          }
          else
          {
            //������������ �������� ����������� �������� ���������� � EEPROM � �����������
            
            unsigned int difference = 0;
  
            if (fix_active_buttons_comp != fix_active_buttons_tmp) difference = 0xff;
            i = 0;
            while ((difference == 0) && (i < N_BIG))
            {
              //�������� ������ ������� �������� ���� ���������� � ��������������� ���'��
              if (trigger_active_functions_comp[i] != trigger_active_functions_tmp[i]) difference = 0xff;
              else
              {
                i++;
              }
            }
            
            if (difference == 0)
            {
              //�������� ���������� ������� ������
  
              //������� ����������� � ���� ����������
              _SET_BIT(clear_diagnostyka, ERROR_TRG_FUNC_EEPROM_COMPARISON_BIT);
            }
            else
            {
              //�������� ���������� ���������� ��������� �� ��������� � ����������� �����������

              //���������� ����������� � ���� ����������
              _SET_BIT(set_diagnostyka, ERROR_TRG_FUNC_EEPROM_COMPARISON_BIT);
            }
          }

          state_spi1_task &= (unsigned int)(~STATE_TRG_FUNC_EEPROM_FAIL);
          state_spi1_task |= STATE_TRG_FUNC_EEPROM_GOOD;
        }
        else
        {
          //���������� ���� �� ���������
          state_spi1_task &= (unsigned int)(~STATE_TRG_FUNC_EEPROM_GOOD);
          state_spi1_task |= STATE_TRG_FUNC_EEPROM_FAIL;
          
          //���������� ����������� � ���� ����������
          _SET_BIT(set_diagnostyka, ERROR_TRG_FUNC_EEPROM_BIT);
        }
      }
      else
      {
        //�������, �� ���������� ���� � ������
        state_spi1_task &= (unsigned int)(~STATE_TRG_FUNC_EEPROM_FAIL);
        state_spi1_task &= (unsigned int)(~STATE_TRG_FUNC_EEPROM_GOOD);
        state_spi1_task |= STATE_TRG_FUNC_EEPROM_EMPTY;
        
        //���������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_TRG_FUNC_EEPROM_BIT);
        _SET_BIT(set_diagnostyka, ERROR_TRG_FUNC_EEPROM_EMPTY_BIT);
      }
            
      //������ ������� �����������, �� ������������ ����������
      comparison_writing &= (unsigned int)(~COMPARISON_WRITING_TRG_FUNC);
      //������� ����������� ��� ������� �����
      _CLEAR_BIT(control_spi1_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_AR_EEPROM_BIT) !=0)
    {
      //�������� �������� ���
      //�������� ��������, �� ���������� ���� � ������, �� ��� ���������� ���������
      unsigned int empty_block = 1, i = 0; 
      __INFO_AR_REJESTRATOR info_rejestrator_ar_tmp;
      
      while ((empty_block != 0) && ( i < (sizeof(__INFO_AR_REJESTRATOR) + 1)))
      {
        if (RxBuffer_SPI_EDF[3 + i] != 0xff) empty_block = 0;
        i++;
      }
      
      if(empty_block == 0)
      {
        //�������, �� ���� �� � ������
        state_spi1_task &= (unsigned int)(~STATE_INFO_REJESTRATOR_AR_EEPROM_EMPTY);
        //������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_AR_EEPROM_EMPTY_BIT);
        
        //���������� ���������� ���� � ���������� �������� ��� � ���������
        unsigned char crc_eeprom_info_rejestrator_ar = 0, temp_value;
        unsigned char  *point = (unsigned char*)(&info_rejestrator_ar_tmp); 
        for (i =0; i < sizeof(__INFO_AR_REJESTRATOR); i++)
        {
          temp_value = RxBuffer_SPI_EDF[3 + i];
          *(point) = temp_value;
          crc_eeprom_info_rejestrator_ar += temp_value;
          point++;
        }
        if (RxBuffer_SPI_EDF[3 + sizeof(__INFO_AR_REJESTRATOR)]  == ((unsigned char)((~(unsigned int)crc_eeprom_info_rejestrator_ar) & 0xff)))
        {
          //����������� ���� ���������
          
          //�������� ���������� ���� (�� �����������)
          crc_info_rejestrator_ar = crc_eeprom_info_rejestrator_ar;

          state_spi1_task &= (unsigned int)(~STATE_INFO_REJESTRATOR_AR_EEPROM_FAIL);
          state_spi1_task |= STATE_INFO_REJESTRATOR_AR_EEPROM_GOOD;
          
          //������� ����������� � ���� ����������
          _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_AR_EEPROM_BIT);
          
          if ((comparison_writing & COMPARISON_WRITING_INFO_REJESTRATOR_AR) == 0)
          {
            //������������ ���������� ���������� �� ����������� ���������� � ������ ���������
            
            //���������� ���������� �� ����������� ���������� � ��������� ��������� � ������ ���������
            info_rejestrator_ar = info_rejestrator_ar_tmp;
          }
          else
          {
            //������������ �������� ����������� �������� ���������� � EEPROM � �����������
            
            unsigned char  *point_to_read  = (unsigned char*)(&info_rejestrator_ar_tmp );
            unsigned char  *point_to_write = (unsigned char*)(&info_rejestrator_ar_comp);
            unsigned int difference = 0;

            i = 0;
            while ((difference == 0) && ( i < sizeof(__INFO_AR_REJESTRATOR)))
            {
              if (*point_to_write != *point_to_read) difference = 0xff;
              else
              {
                point_to_write++;
                point_to_read++;
                i++;
              }
            }
            if (difference == 0)
            {
              //�������� ���������� ������� ������

              //������� ����������� � ���� ����������
              _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_AR_COMPARISON_BIT);
            }
            else
            {
              //�������� ���������� ���������� ��������� �� ��������� � ����������� �����������

              //���������� ����������� � ���� ����������
              _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_AR_COMPARISON_BIT);
            }
          }
        }
        else
        {
          //���������� ���� �� ���������
          state_spi1_task &= (unsigned int)(~STATE_INFO_REJESTRATOR_AR_EEPROM_GOOD);
          state_spi1_task |= STATE_INFO_REJESTRATOR_AR_EEPROM_FAIL;

          //���������� ����������� � ���� ����������
          _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_AR_EEPROM_BIT);
          
          /*
          ����������� ����������� ��� ��, �� � EEPROM ����� �������� ��� ��������
          ��������� ����� ���, ���� �� ������� �������� ��� ��� ���������� 
          �� � ���������� ���'��, � �� ���� �� ��������� �������� ������.
          �� ��� �������� ������ ��� ������� ����� �� ������ ���������� ���, �� � � 
          ���������� ���'�� � ��� �����, �����, ���� ����� ������� �������, ��,
          ������� �� �������� � ������� � ���������� ���'��,  �� � � ��� ��������,
          �� �� �� ����� � ����������, �� �� ������ �� ���������������� ����������� ������������� 
          ��� ������ � EEPROM �� ��� �� ��������
          */
          if ((comparison_writing & COMPARISON_WRITING_INFO_REJESTRATOR_AR) == 0)
          {
            //������������ ���������� ���������� �� ����������� ���������� � ������ ���������

            //����������� ������� ������ ���� ��������� � EEPROM
            /*
            ������� ����������� ������, � ���� ������ ���� � �����, �� ����� ������,
            �� �� ����� ��������������� ����������� ����� ���������� �� �����������
            ���������� ���������� ��������� � ������� ������� ���������
            info_rejestrator_ar � �������� �����. �� ��������� ��������� � ������� 
            "������� �"/"������ �" EEPROM ���� ����������. ���� ����������� �������� �������
            ������ ������� ���������.
            � ����� ������� �� �������, ��� ������� ����� �� �����������, 
            �� ����� ���������� �������� main_routines_for_spi1 - � ��� �� ����� �����������.
            ����� �������� ����� � ���� ������� ����� � ��� ��������� ���������� � �� �������
            ������� ��������� ������� ��� �� ��������� ����� ����� �����, ��� 
            �� ����� ����������� ������� (�� ������ � ���� �������)
            */
            _SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);
          
            //������� ��������� ���������� �� ����������� ���������
            info_rejestrator_ar.first_number = -1;
            info_rejestrator_ar.last_number = -1;
            _SET_STATE(FATFS_command, FATFS_FORMAT);
          }
        }
      }
      else
      {
        //�������, �� ���������� ���� � ������
        state_spi1_task &= (unsigned int)(~(STATE_INFO_REJESTRATOR_AR_EEPROM_FAIL | STATE_INFO_REJESTRATOR_AR_EEPROM_GOOD));
        state_spi1_task |= STATE_INFO_REJESTRATOR_AR_EEPROM_EMPTY;
        
        //���������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_AR_EEPROM_BIT);
        _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_AR_EEPROM_EMPTY_BIT);
              
        /*
        ����������� ����������� ��� ��, �� � EEPROM ����� �������� ��� ��������
        ��������� ����� ���, ���� �� ������� �������� ��� ��� ���������� 
        �� � ���������� ���'��, � �� ���� �� ��������� �������� ������.
        �� ��� �������� ������ ��� ������� ����� �� ������ ���������� ���, �� � � 
        ���������� ���'�� � ��� �����, �����, ���� ����� ������� �������, ��,
        ������� �� �������� � ������� � ���������� ���'��,  �� � � ��� ��������,
        �� �� �� ����� � ����������, �� �� ������ �� ���������������� ����������� ������������� 
        ��� ������ � EEPROM �� ��� �� ��������
        */
        if ((comparison_writing & COMPARISON_WRITING_INFO_REJESTRATOR_AR) == 0)
        {
          //������������ ���������� ���������� �� ����������� ���������� � ������ ���������

          //����������� ������� ������ ���� ��������� � EEPROM
          /*
          ������� ����������� ������, � ���� ������ ���� � �����, �� ����� ������,
          �� �� ����� ��������������� ����������� ����� ���������� �� �����������
          ���������� ���������� ��������� � ������� ������� ���������
          info_rejestrator_ar � �������� �����. �� ��������� ��������� � ������� 
          "������� �"/"������ �" EEPROM ���� ����������. ���� ����������� �������� �������
          ������ ������� ���������.
          � ����� ������� �� �������, ��� ������� ����� �� �����������, 
          �� ����� ���������� �������� main_routines_for_spi1 - � ��� �� ����� �����������.
          ����� �������� ����� � ���� ������� ����� � ��� ��������� ���������� � �� �������
          ������� ��������� ������� ��� �� ��������� ����� ����� �����, ��� 
          �� ����� ����������� ������� (�� ������ � ���� �������)
          */
          _SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT);

          //������� ��������� ���������� �� ����������� ���������
          info_rejestrator_ar.first_number = -1;
          info_rejestrator_ar.last_number = -1;
          _SET_STATE(FATFS_command, FATFS_FORMAT);
        }
      }

      //������ ������� �����������, �� ������������ ����������
      comparison_writing &= (unsigned int)(~COMPARISON_WRITING_INFO_REJESTRATOR_AR);
      //������� ����������� ��� ������� �����
      _CLEAR_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_AR_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_DR_EEPROM_BIT) !=0)
    {
      //�������� �������� ���
      //�������� ��������, �� ���������� ���� � ������, �� ��� ���������� ���������
      unsigned int empty_block = 1, i = 0; 
      __INFO_REJESTRATOR info_rejestrator_dr_tmp;
      
      while ((empty_block != 0) && ( i < (sizeof(__INFO_REJESTRATOR) + 1)))
      {
        if (RxBuffer_SPI_EDF[3 + i] != 0xff) empty_block = 0;
        i++;
      }
      
      if(empty_block == 0)
      {
        //�������, �� ���� �� � ������
        state_spi1_task &= (unsigned int)(~STATE_INFO_REJESTRATOR_DR_EEPROM_EMPTY);
        //������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_DR_EEPROM_EMPTY_BIT);
        
        //���������� ���������� ���� � ���������� �������� ��� � ���������
        unsigned char crc_eeprom_info_rejestrator_dr = 0, temp_value;
        unsigned char  *point = (unsigned char*)(&info_rejestrator_dr_tmp); 
        for (i =0; i < sizeof(__INFO_REJESTRATOR); i++)
        {
          temp_value = RxBuffer_SPI_EDF[3 + i];
          *(point) = temp_value;
          crc_eeprom_info_rejestrator_dr += temp_value;
          point++;
        }
        if (RxBuffer_SPI_EDF[3 + sizeof(__INFO_REJESTRATOR)]  == ((unsigned char)((~(unsigned int)crc_eeprom_info_rejestrator_dr) & 0xff)))
        {
          //����������� ���� ���������
          
          //�������� ���������� ���� (�� �����������)
          crc_info_rejestrator_dr = crc_eeprom_info_rejestrator_dr;

          state_spi1_task &= (unsigned int)(~STATE_INFO_REJESTRATOR_DR_EEPROM_FAIL);
          state_spi1_task |= STATE_INFO_REJESTRATOR_DR_EEPROM_GOOD;
          
          //������� ����������� � ���� ����������
          _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_DR_EEPROM_BIT);

          if ((comparison_writing & COMPARISON_WRITING_INFO_REJESTRATOR_DR) == 0)
          {
            //������������ ���������� ���������� �� ����������� ���������� � ������ ���������
            
            //���������� ���������� �� ����������� ���������� � ��������� ��������� � ������ ���������
            info_rejestrator_dr = info_rejestrator_dr_tmp;

            //���������� �� �� ����� � ���� ���������� �����
            if(
#if MIN_ADDRESS_DR_AREA != 0
               (info_rejestrator_dr.next_address   >= MIN_ADDRESS_DR_AREA) &&
#endif
               (info_rejestrator_dr.next_address   <= MAX_ADDRESS_DR_AREA) &&
               (info_rejestrator_dr.number_records <= MAX_NUMBER_RECORDS_INTO_DR)  
              )
            {
              //�� �������� ����� �������� ��������

              //����������, �� � ������ ������ �������� ���� �� ������� ����������/������ �������.
              //��� ������ ����� ���� ���� �����������, ���� ��� ��� ������ � ���������
              //��� �������, �� � ����� ������ �� ���� ����� � �����
              if (info_rejestrator_dr.saving_execution !=0 )
              {
                //����������� ����������� ��� �� ����
                _SET_BIT(set_diagnostyka, ERROR_DR_LOSS_INFORMATION_BIT);

                //����������� ������� ������ ���� ��������� � EEPROM
                /*
                ������� ����������� ������, � ���� ������ ���� � �����, �� ����� ������,
                �� �� ����� ��������������� ����������� ����� ���������� �� ����������
                ���������� ���������� ��������� � ������� ������� ���������
                info_rejestrator_dr � �������� ����. �� ��������� ��������� � ������� 
                "������� �"/"������ �" EEPROM ���� ����������. ���� ����������� �������� �������
                ������ ������� ���������.
                � ����� ������� �� �������, ��� ������� ����� �� �����������, 
                �� ����� ���������� �������� main_routines_for_spi1 - � ��� �� ����� �����������.
                ����� �������� ����� � ���� ������� ����� � ��� ��������� ���������� � �� �������
                ������� ��������� ������� ��� �� ��������� ����� ����� �����, ��� 
                �� ����� ����������� ������� (�� ������ � ���� �������)
                */
                _SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT);

                info_rejestrator_dr.saving_execution = 0;
                if (info_rejestrator_dr.number_records >= MAX_NUMBER_RECORDS_INTO_DR)
                  info_rejestrator_dr.number_records = (MAX_NUMBER_RECORDS_INTO_DR - 1);
              }
            }
            else
            {
              //���������� ����������� � ���� ����������
              _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_DR_EEPROM_BIT);

              //����������� ������� ������ ���� ��������� � EEPROM
              /*
              ������� ����������� ������, � ���� ������ ���� � �����, �� ����� ������,
              �� �� ����� ��������������� ����������� ����� ���������� �� ����������
              ���������� ���������� ��������� � ������� ������� ���������
              info_rejestrator_dr � �������� ����. �� ��������� ��������� � ������� 
              "������� �"/"������ �" EEPROM ���� ����������. ���� ����������� �������� �������
              ������ ������� ���������.
              � ����� ������� �� �������, ��� ������� ����� �� �����������, 
              �� ����� ���������� �������� main_routines_for_spi1 - � ��� �� ����� �����������.
              ����� �������� ����� � ���� ������� ����� � ��� ��������� ���������� � �� �������
              ������� ��������� ������� ��� �� ��������� ����� ����� �����, ��� 
              �� ����� ����������� ������� (�� ������ � ���� �������)
              */
              _SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT);

              //������� ��������� ���������� �� ����������� ���������
              info_rejestrator_dr.next_address = MIN_ADDRESS_DR_AREA;
              info_rejestrator_dr.saving_execution = 0;
              info_rejestrator_dr.number_records = 0;
            }
          }
          else
          {
            //������������ �������� ����������� �������� ���������� � EEPROM � �����������
            
            unsigned char  *point_to_read  = (unsigned char*)(&info_rejestrator_dr_tmp );
            unsigned char  *point_to_write = (unsigned char*)(&info_rejestrator_dr_comp);
            unsigned int difference = 0;

            i = 0;
            while ((difference == 0) && ( i < sizeof(__INFO_REJESTRATOR)))
            {
              if (*point_to_write != *point_to_read) difference = 0xff;
              else
              {
                point_to_write++;
                point_to_read++;
                i++;
              }
            }
            if (difference == 0)
            {
              //�������� ���������� ������� ������

              //������� ����������� � ���� ����������
              _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_DR_COMPARISON_BIT);
            }
            else
            {
              //�������� ���������� ���������� ��������� �� ��������� � ����������� �����������

              //���������� ����������� � ���� ����������
              _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_DR_COMPARISON_BIT);
            }
          }
        }
        else
        {
          //���������� ���� �� ���������
          state_spi1_task &= (unsigned int)(~STATE_INFO_REJESTRATOR_DR_EEPROM_GOOD);
          state_spi1_task |= STATE_INFO_REJESTRATOR_DR_EEPROM_FAIL;

          //���������� ����������� � ���� ����������
          _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_DR_EEPROM_BIT);
          
          /*
          ����������� ����������� ��� ��, �� � EEPROM ����� �������� ��� ��������
          ��������� ����� ���, ���� �� ������� �������� ��� ��� ���������� 
          �� � ���������� ���'��, � �� ���� �� ��������� �������� ������.
          �� ��� �������� ������ ��� ������� ����� �� ������ ���������� ���, �� � � 
          ���������� ���'�� � ��� �����, �����, ���� ����� ������� �������, ��,
          ������� �� �������� � ������� � ���������� ���'��,  �� � � ��� ��������,
          �� �� �� ����� � ����������, �� �� ������ �� ���������������� ����������� ������������� 
          ��� ������ � EEPROM �� ��� �� ��������
          */
          if ((comparison_writing & COMPARISON_WRITING_INFO_REJESTRATOR_DR) == 0)
          {
            //������������ ���������� ���������� �� ����������� ���������� � ������ ���������

            //����������� ������� ������ ���� ��������� � EEPROM
            /*
            ������� ����������� ������, � ���� ������ ���� � �����, �� ����� ������,
            �� �� ����� ��������������� ����������� ����� ���������� �� ����������
            ���������� ���������� ��������� � ������� ������� ���������
            info_rejestrator_dr � �������� ����. �� ��������� ��������� � ������� 
            "������� �"/"������ �" EEPROM ���� ����������. ���� ����������� �������� �������
            ������ ������� ���������.
            � ����� ������� �� �������, ��� ������� ����� �� �����������, 
            �� ����� ���������� �������� main_routines_for_spi1 - � ��� �� ����� �����������.
            ����� �������� ����� � ���� ������� ����� � ��� ��������� ���������� � �� �������
            ������� ��������� ������� ��� �� ��������� ����� ����� �����, ��� 
            �� ����� ����������� ������� (�� ������ � ���� �������)
            */
            _SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT);
  
            //������� ��������� ���������� �� ����������� ���������
            info_rejestrator_dr.next_address = MIN_ADDRESS_DR_AREA;
            info_rejestrator_dr.saving_execution = 0;
            info_rejestrator_dr.number_records = 0;
          }    
        }
      }
      else
      {
        //�������, �� ���������� ���� � ������
        state_spi1_task &= (unsigned int)(~(STATE_INFO_REJESTRATOR_DR_EEPROM_FAIL | STATE_INFO_REJESTRATOR_DR_EEPROM_GOOD));
        state_spi1_task |= STATE_INFO_REJESTRATOR_DR_EEPROM_EMPTY;
        
        //���������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_DR_EEPROM_BIT);
        _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_DR_EEPROM_EMPTY_BIT);

        /*
        ����������� ����������� ��� ��, �� � EEPROM ����� �������� ��� ��������
        ��������� ����� ���, ���� �� ������� �������� ��� ��� ���������� 
        �� � ���������� ���'��, � �� ���� �� ��������� �������� ������.
        �� ��� �������� ������ ��� ������� ����� �� ������ ���������� ���, �� � � 
        ���������� ���'�� � ��� �����, �����, ���� ����� ������� �������, ��,
        ������� �� �������� � ������� � ���������� ���'��,  �� � � ��� ��������,
        �� �� �� ����� � ����������, �� �� ������ �� ���������������� ����������� ������������� 
        ��� ������ � EEPROM �� ��� �� ��������
        */
        if ((comparison_writing & COMPARISON_WRITING_INFO_REJESTRATOR_DR) == 0)
        {
          //������������ ���������� ���������� �� ����������� ���������� � ������ ���������

          //����������� ������� ������ ���� ��������� � EEPROM
          /*
          ������� ����������� ������, � ���� ������ ���� � �����, �� ����� ������,
          �� �� ����� ��������������� ����������� ����� ���������� �� �����������
          ���������� ���������� ��������� � ������� ������� ���������
          info_rejestrator_ar � �������� ����. �� ��������� ��������� � ������� 
          "������� �"/"������ �" EEPROM ���� ����������. ���� ����������� �������� �������
          ������ ������� ���������.
          � ����� ������� �� �������, ��� ������� ����� �� �����������, 
          �� ����� ���������� �������� main_routines_for_spi1 - � ��� �� ����� �����������.
          ����� �������� ����� � ���� ������� ����� � ��� ��������� ���������� � �� �������
          ������� ��������� ������� ��� �� ��������� ����� ����� �����, ��� 
          �� ����� ����������� ������� (�� ������ � ���� �������)
          */
          _SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT);

          //������� ��������� ���������� �� ����������� ���������
          info_rejestrator_dr.next_address = MIN_ADDRESS_DR_AREA;
          info_rejestrator_dr.saving_execution = 0;
          info_rejestrator_dr.number_records = 0;
        }  
      }
            
      //������ ������� �����������, �� ������������ ����������
      comparison_writing &= (unsigned int)(~COMPARISON_WRITING_INFO_REJESTRATOR_DR);
      //������� ����������� ��� ������� �����
      _CLEAR_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_DR_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) !=0)
    {
      //�������� �������� ���
      //�������� ��������, �� ���������� ���� � ������, �� ��� ���������� ���������
      unsigned int empty_block = 1, i = 0; 
      __INFO_REJESTRATOR info_rejestrator_pr_err_tmp;
      
      while ((empty_block != 0) && ( i < (sizeof(__INFO_REJESTRATOR) + 1)))
      {
        if (RxBuffer_SPI_EDF[3 + i] != 0xff) empty_block = 0;
        i++;
      }
      
      if(empty_block == 0)
      {
        //�������, �� ���� �� � ������
        state_spi1_task &= (unsigned int)(~STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY);
        //������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY_BIT);
        
        //���������� ���������� ���� � ���������� �������� ��� � ���������
        unsigned char crc_eeprom_info_rejestrator_pr_err = 0, temp_value;
        unsigned char  *point = (unsigned char*)(&info_rejestrator_pr_err_tmp); 
        for (i =0; i < sizeof(__INFO_REJESTRATOR); i++)
        {
          temp_value = RxBuffer_SPI_EDF[3 + i];
          *(point) = temp_value;
          crc_eeprom_info_rejestrator_pr_err += temp_value;
          point++;
        }
        if (RxBuffer_SPI_EDF[3 + sizeof(__INFO_REJESTRATOR)]  == ((unsigned char)((~(unsigned int)crc_eeprom_info_rejestrator_pr_err) & 0xff)))
        {
          //����������� ���� ���������
          
          //�������� ���������� ���� (�� �����������)
          crc_info_rejestrator_pr_err = crc_eeprom_info_rejestrator_pr_err;

          state_spi1_task &= (unsigned int)(~STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_FAIL);
          state_spi1_task |= STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_GOOD;
          
          //������� ����������� � ���� ����������
          _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);

          if ((comparison_writing & COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR) == 0)
          {
            //������������ ���������� ���������� �� ���������� ���������� ���� � ������ ���������
            
            //���������� ���������� �� ���������� ���������� ���� � ��������� ��������� � ������ ���������
            info_rejestrator_pr_err = info_rejestrator_pr_err_tmp;

            //���������� �� �� ����� � ���� ���������� �����
            if(
               (info_rejestrator_pr_err.next_address   >= MIN_ADDRESS_PR_ERR_AREA) && 
               (info_rejestrator_pr_err.next_address   <= MAX_ADDRESS_PR_ERR_AREA) &&
               (info_rejestrator_pr_err.number_records <= MAX_NUMBER_RECORDS_INTO_PR_ERR)  
              )
            {
              //�� �������� ����� �������� ��������

              //����������, �� � ������ ������ �������� ���� �� ������� ����������/������ �������.
              //��� ������ ����� ���� ���� �����������, ���� ��� ��� ������ � ���������
              //��� �������, �� � ����� ������ �� ���� ����� � �����
              //����������, �� � ������ ������ ��������� ��䳿 �� ������� ����������/������ �������.
              //��� ������ � �������, ��� ���������� ���� ���� ������������
              if (info_rejestrator_pr_err.saving_execution !=0 )
              {
                //����������� ����������� ��� �� ����
                _SET_BIT(set_diagnostyka, ERROR_PR_ERR_LOSS_INFORMATION_BIT);

                //����������� ������� ������ ���� ��������� � EEPROM
                /*
                ������� ����������� ������, � ���� ������ ���� � �����, �� ����� ������,
                �� �� ����� ��������������� ����������� ����� ���������� �� ����������
                ���������� ���� ���������� ��������� � ����������� �������������� DataFlash ���������
                info_rejestrator_pr_err � �������� ����. �� ��������� ��������� � ������� 
                "������� �"/"������ �" EEPROM ���� ����������. ���� ����������� �������� �������
                ������ ������� ���������.
                � ����� ������� �� �������, ��� ������� ����� �� �����������, 
                �� ����� ���������� �������� main_routines_for_spi1 - � ��� �� ����� �����������.
                ����� �������� ����� � ���� ������� ����� � ��� ��������� ���������� � �� �������
                ������� ��������� �������, ��� �� ��������� ����� ����� �����, ��� 
                �� ����� ����������� ������� (�� ������ � ���� �������)
                */
                _SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);

                info_rejestrator_pr_err.saving_execution = 0;
                
                
              }   
            }
            else
            {
              //���������� ����������� � ���� ����������
              _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
          
              //����������� ������� ������ ���� ��������� � EEPROM
              /*
              ������� ����������� ������, � ���� ������ ���� � �����, �� ����� ������,
              �� �� ����� ��������������� ����������� ����� ���������� �� ����������
              ���������� ���� ���������� ��������� � ����������� �������������� DataFlash ���������
              info_rejestrator_pr_err � �������� ����. �� ��������� ��������� � ������� 
              "������� �"/"������ �" EEPROM ���� ����������. ���� ����������� �������� �������
              ������ ������� ���������.
              � ����� ������� �� �������, ��� ������� ����� �� �����������, 
              �� ����� ���������� �������� main_routines_for_spi1 - � ��� �� ����� �����������.
              ����� �������� ����� � ���� ������� ����� � ��� ��������� ���������� � �� �������
              ������� ��������� �������, ��� �� ��������� ����� ����� �����, ��� 
              �� ����� ����������� ������� (�� ������ � ���� �������)
              */
              _SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);

              //������� ��������� ���������� �� ��������� ���������� ����
              info_rejestrator_pr_err.next_address = MIN_ADDRESS_PR_ERR_AREA;
              info_rejestrator_pr_err.saving_execution = 0;
              info_rejestrator_pr_err.number_records = 0;
            }
          }
          else
          {
            //������������ �������� ����������� �������� ���������� � EEPROM � �����������
            
            unsigned char  *point_to_read  = (unsigned char*)(&info_rejestrator_pr_err_tmp );
            unsigned char  *point_to_write = (unsigned char*)(&info_rejestrator_pr_err_comp);
            unsigned int difference = 0;

            i = 0;
            while ((difference == 0) && ( i < sizeof(__INFO_REJESTRATOR)))
            {
              if (*point_to_write != *point_to_read) difference = 0xff;
              else
              {
                point_to_write++;
                point_to_read++;
                i++;
              }
            }
            if (difference == 0)
            {
              //�������� ���������� ������� ������

              //������� ����������� � ���� ����������
              _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_COMPARISON_BIT);
            }
            else
            {
              //�������� ���������� ���������� ��������� �� ��������� � ����������� �����������

              //���������� ����������� � ���� ����������
              _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_COMPARISON_BIT);
            }
          }
        }
        else
        {
          //���������� ���� �� ���������
          state_spi1_task &= (unsigned int)(~STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_GOOD);
          state_spi1_task |= STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_FAIL;
          
          //���������� ����������� � ���� ����������
          _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
          
          /*
          ����������� ����������� ��� ��, �� � EEPROM ����� �������� ��� ��������
          ��������� ����� ���, ���� �� ������� �������� ��� ��� ���������� 
          �� � ���������� ���'��, � �� ���� �� ��������� �������� ������.
          �� ��� �������� ������ ��� ������� ����� �� ������ ���������� ���, �� � � 
          ���������� ���'�� � ��� �����, �����, ���� ����� ������� �������, ��,
          ������� �� �������� � ������� � ���������� ���'��,  �� � � ��� ��������,
          �� �� �� ����� � ����������, �� �� ������ �� ���������������� ����������� ������������� 
          ��� ������ � EEPROM �� ��� �� ��������
          */
          if ((comparison_writing & COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR) == 0)
          {
            //������������ ���������� ���������� �� ����������� ���������� � ������ ���������

            //����������� ������� ������ ���� ��������� � EEPROM
            /*
            ������� ����������� ������, � ���� ������ ���� � �����, �� ����� ������,
            �� �� ����� ��������������� ����������� ����� ���������� �� ����������
            ���������� ���� ���������� ��������� � ����������� �������������� DataFlash ���������
            info_rejestrator_pr_err � �������� ����. �� ��������� ��������� � ������� 
            "������� �"/"������ �" EEPROM ���� ����������. ���� ����������� �������� �������
            ������ ������� ���������.
            � ����� ������� �� �������, ��� ������� ����� �� �����������, 
            �� ����� ���������� �������� main_routines_for_spi1 - � ��� �� ����� �����������.
            ����� �������� ����� � ���� ������� ����� � ��� ��������� ���������� � �� �������
            ������� ��������� �������, ��� �� ��������� ����� ����� �����, ��� 
            �� ����� ����������� ������� (�� ������ � ���� �������)
            */
            _SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);

            //������� ��������� ���������� �� ��������� ���������� ����
            info_rejestrator_pr_err.next_address = MIN_ADDRESS_PR_ERR_AREA;
            info_rejestrator_pr_err.saving_execution = 0;
            info_rejestrator_pr_err.number_records = 0;
          }
        }
      }
      else
      {
        //�������, �� ���������� ���� � ������
        state_spi1_task &= (unsigned int)(~(STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_FAIL | STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_GOOD));
        state_spi1_task |= STATE_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY;
        
        //���������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
        _SET_BIT(set_diagnostyka, ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY_BIT);

        /*
        ����������� ����������� ��� ��, �� � EEPROM ����� �������� ��� ��������
        ��������� ����� ���, ���� �� ������� �������� ��� ��� ���������� 
        �� � ���������� ���'��, � �� ���� �� ��������� �������� ������.
        �� ��� �������� ������ ��� ������� ����� �� ������ ���������� ���, �� � � 
        ���������� ���'�� � ��� �����, �����, ���� ����� ������� �������, ��,
        ������� �� �������� � ������� � ���������� ���'��,  �� � � ��� ��������,
        �� �� �� ����� � ����������, �� �� ������ �� ���������������� ����������� ������������� 
        ��� ������ � EEPROM �� ��� �� ��������
        */
        if ((comparison_writing & COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR) == 0)
        {
          //������������ ���������� ���������� �� ����������� ���������� � ������ ���������

          //����������� ������� ������ ���� ��������� � EEPROM
          /*
          ������� ����������� ������, � ���� ������ ���� � �����, �� ����� ������,
          �� �� ����� ��������������� ����������� ����� ���������� �� ����������
          ���������� ���� ���������� ��������� � ����������� �������������� DataFlash ���������
          info_rejestrator_pr_err � �������� ����. �� ��������� ��������� � ������� 
          "������� �"/"������ �" EEPROM ���� ����������. ���� ����������� �������� �������
          ������ ������� ���������.
          � ����� ������� �� �������, ��� ������� ����� �� �����������, 
          �� ����� ���������� �������� main_routines_for_spi1 - � ��� �� ����� �����������.
          ����� �������� ����� � ���� ������� ����� � ��� ��������� ���������� � �� �������
          ������� ��������� �������, ��� �� ��������� ����� ����� �����, ��� 
          �� ����� ����������� ������� (�� ������ � ���� �������)
          */
          _SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);

          //������� ��������� ���������� �� ��������� ���������� ����
          info_rejestrator_pr_err.next_address = MIN_ADDRESS_PR_ERR_AREA;
          info_rejestrator_pr_err.saving_execution = 0;
          info_rejestrator_pr_err.number_records = 0;
        }
      }

      //������ ������� �����������, �� ������������ ����������
      comparison_writing &= (unsigned int)(~COMPARISON_WRITING_INFO_REJESTRATOR_PR_ERR);
      //������� ����������� ��� ������� �����
      _CLEAR_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
    }
   else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_RESURS_EEPROM_BIT) !=0)
    {
      //�������� �������� ���
      //�������� ��������, �� ���������� ���� � ������, �� ��� ���������� ���������
      unsigned int empty_block = 1, i = 0; 
      unsigned int resurs_vymykacha_tmp, resurs_vidkljuchennja_tmp;

      while ((empty_block != 0) && ( i < (sizeof(resurs_vymykacha) + sizeof(resurs_vidkljuchennja) + 1)))
      {
        if (RxBuffer_SPI_EDF[3 + i] != 0xff) empty_block = 0;
        i++;
      }
      
      if(empty_block == 0)
      {
        //�������, �� ���� �� � ������
        state_spi1_task &= (unsigned int)(~STATE_RESURS_EEPROM_EMPTY);
        //������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_RESURS_EEPROM_EMPTY_BIT);
        
        //���������� ���������� ���� 
        unsigned char crc_eeprom_resurs = 0, temp_value;
        unsigned char  *point;
        unsigned int offset = 3;
        
        point = (unsigned char*)(&resurs_vymykacha_tmp); 
        for (i =0; i < sizeof(resurs_vymykacha_tmp); i++)
        {
          temp_value = RxBuffer_SPI_EDF[offset + i];
          *(point) = temp_value;
          crc_eeprom_resurs += temp_value;
          point++;
        }
        offset += sizeof(resurs_vymykacha_tmp);

        point = (unsigned char*)(&resurs_vidkljuchennja_tmp); 
        for (i =0; i < sizeof(resurs_vidkljuchennja_tmp); i++)
        {
          temp_value = RxBuffer_SPI_EDF[offset + i];
          *(point) = temp_value;
          crc_eeprom_resurs += temp_value;
          point++;
        }
        offset += sizeof(resurs_vidkljuchennja_tmp);

        if (RxBuffer_SPI_EDF[offset]  == ((unsigned char)((~(unsigned int)crc_eeprom_resurs) & 0xff)))
        {
          //����������� ���� ���������

          //������� ����������� � ���� ����������
          _SET_BIT(clear_diagnostyka, ERROR_RESURS_EEPROM_BIT);
          
          crc_resurs = crc_eeprom_resurs;
          
          if ((comparison_writing & COMPARISON_WRITING_RESURS) == 0)
          {
            resurs_vymykacha = resurs_vymykacha_tmp;
            resurs_vidkljuchennja = resurs_vidkljuchennja_tmp; 
          }
          else
          {
            //������������ �������� ����������� �������� ���������� � EEPROM � �����������
            unsigned int target = 0;
            unsigned int difference = 0;
            while ((target < 2) && (difference == 0))
            {
              unsigned char *point_to_read;
              unsigned char *point_to_write;
              unsigned int size_of_target;
              
              switch (target)
              {
              case 0:
                {
                  point_to_read  = (unsigned char*)(&resurs_vymykacha_tmp );
                  point_to_write = (unsigned char*)(&resurs_vymykacha_comp);
                  size_of_target = sizeof(resurs_vymykacha);
                  break;
                }
              case 1:
                {
                  point_to_read  = (unsigned char*)(&resurs_vidkljuchennja_tmp );
                  point_to_write = (unsigned char*)(&resurs_vidkljuchennja_comp);
                  size_of_target = sizeof(resurs_vidkljuchennja);
                  break;
                }
              default:
                  {
                    //���������� ����� ����� �� ���� � ����
                    total_error_sw_fixed(49);
                  }
                  
              }

              i = 0;
              while ((difference == 0) && ( i < size_of_target))
              {
                if (*point_to_write != *point_to_read) difference = 0xff;
                else
                {
                  point_to_write++;
                  point_to_read++;
                  i++;
                }
              }
              
              if (difference == 0) target++;
            }
            
            if (difference == 0)
            {
              //�������� ���������� ������� ������
  
              //������� ����������� � ���� ����������
              _SET_BIT(clear_diagnostyka, ERROR_RESURS_EEPROM_COMPARISON_BIT);
            }
            else
            {
              //�������� ���������� ���������� ��������� �� ��������� � ����������� �����������

              //���������� ����������� � ���� ����������
              _SET_BIT(set_diagnostyka, ERROR_RESURS_EEPROM_COMPARISON_BIT);
            }
          }

          state_spi1_task &= (unsigned int)(~STATE_RESURS_EEPROM_FAIL);
          state_spi1_task |= STATE_RESURS_EEPROM_GOOD;
        }
        else
        {
          //���������� ���� �� ���������
          state_spi1_task &= (unsigned int)(~STATE_RESURS_EEPROM_GOOD);
          state_spi1_task |= STATE_RESURS_EEPROM_FAIL;
          
          //���������� ����������� � ���� ����������
          _SET_BIT(set_diagnostyka, ERROR_RESURS_EEPROM_BIT);
        }
      }
      else
      {
        //�������, �� ���������� ���� � ������
        state_spi1_task &= (unsigned int)(~STATE_RESURS_EEPROM_FAIL);
        state_spi1_task &= (unsigned int)(~STATE_RESURS_EEPROM_GOOD);
        state_spi1_task |= STATE_RESURS_EEPROM_EMPTY;
        
        //���������� ����������� � ���� ����������
        _SET_BIT(clear_diagnostyka, ERROR_RESURS_EEPROM_BIT);
        _SET_BIT(set_diagnostyka, ERROR_RESURS_EEPROM_EMPTY_BIT);
      }
      
      //������ ������� �����������, �� ������������ ����������
      comparison_writing &= (unsigned int)(~COMPARISON_WRITING_RESURS);
      //������� ����������� ��� ������� �����
      _CLEAR_BIT(control_spi1_taskes, TASK_READING_RESURS_EEPROM_BIT);
    }  
    else
    {
      //����, ����������, ����� �� ���� � ����
      //� ��� ������� �������� ����� �� ������
    }
    /*************************************************/
  }
  else if (state_execution_spi1 == 2)
  {
    /*************************************************/
    //���� ���������� � ��������
    /*************************************************/

    //����������� �����������, �� SPI1 ������� �� ���� ���������� 
    state_execution_spi1 = -1;

    //����������� � ���������� ����
    if(_CHECK_SET_BIT(control_spi1_taskes, TASK_EEPROM_WRITE_PREPARATION_BIT) != 0)
    {
      //���������� �� ������� ���� ���������
      etap_eeprom_write_enable = -1;
    }
    else if (
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_ENERGY_EEPROM_BIT                 ) != 0) ||
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_SETTINGS_EEPROM_BIT               ) != 0) ||
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_USTUVANNJA_EEPROM_BIT             ) != 0) ||
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_STATE_LEDS_OUTPUTS_EEPROM_BIT     ) != 0) || 
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT               ) != 0) || 
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_AR_EEPROM_BIT    ) != 0) || 
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_DR_EEPROM_BIT    ) != 0) || 
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) != 0) ||
             (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_RESURS_EEPROM_BIT                 ) != 0)
            )
    {
      //����� ����� ������ ����� � EEPROM
      //�������� ����� ����� ��� ������ � EEPROM ��� �����, �� ���� ������������, �� �� ���������
      //����������� �� ������������ ������� �� �����
      _SET_BIT(control_spi1_taskes, TASK_EEPROM_WRITE_PREPARATION_BIT);
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_ENERGY_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ����� � EEPROM ������
      
      //�������� ��������� ������ �������
      _SET_BIT(control_spi1_taskes, TASK_START_READ_ENERGY_EEPROM_BIT);
      _CLEAR_BIT(control_spi1_taskes, TASK_READING_ENERGY_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_SETTINGS_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ����� � EEPROM ���������
      
      //�������� ��������� ������ �������
      _SET_BIT(control_spi1_taskes, TASK_START_READ_SETTINGS_EEPROM_BIT);
      _CLEAR_BIT(control_spi1_taskes, TASK_READING_SETTINGS_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_USTUVANNJA_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ����� � EEPROM ���������
      
      //�������� ��������� ������ �������
      _SET_BIT(control_spi1_taskes, TASK_START_READ_USTUVANNJA_EEPROM_BIT);
      _CLEAR_BIT(control_spi1_taskes, TASK_READING_USTUVANNJA_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_STATE_LEDS_OUTPUTS_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ����� � EEPROM ����� ��������� �������������� � ���������� ������
      
      //�������� ��������� ������ �������
      _SET_BIT(control_spi1_taskes, TASK_START_READ_STATE_LEDS_OUTPUTS_EEPROM_BIT);
      _CLEAR_BIT(control_spi1_taskes, TASK_READING_STATE_LEDS_OUTPUTS_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ����� � EEPROM ����� �������� ����������
      
      //�������� ��������� ������ �������
      _SET_BIT(control_spi1_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT);
      _CLEAR_BIT(control_spi1_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_AR_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ����� � EEPROM �� ����������� ���������
      
      //�������� ��������� ������ �������
      _SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_AR_EEPROM_BIT);
      _CLEAR_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_AR_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_DR_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ����� � EEPROM �� ����������� ���������
      
      //�������� ��������� ������ �������
      _SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_DR_EEPROM_BIT);
      _CLEAR_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_DR_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT) !=0)
    {
      //����� ����� ������� ����� � EEPROM �� ��������� ��������������
      
      //�������� ��������� ������ �������
      _SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
      _CLEAR_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
    }
    else if (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_RESURS_EEPROM_BIT) !=0)
    {
      _SET_BIT(control_spi1_taskes, TASK_START_READ_RESURS_EEPROM_BIT);
      _CLEAR_BIT(control_spi1_taskes, TASK_READING_RESURS_EEPROM_BIT);
    } 
    else
    {
      //� ��� ������� �������� ����� �� ������
    }
    /*************************************************/
  }
}
/*****************************************************/
