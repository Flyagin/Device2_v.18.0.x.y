#include "header.h"

//��������� ������� � ����� ������
#define BEGIN_ADR_REGISTER 13000
//�������� ������� � ����� ������
#define END_ADR_REGISTER 13369

// ��������� ������� ������������
#define REGISTERS_REG 32
//����������� ��������� ������� ������������
#define REGISTERS_ACTIONREG 32

int privateREGBigGetReg2(int adrReg);

int getREGBigModbusRegister(int);//�������� ���������� ��������
int getREGBigModbusBit(int);//�������� ���������� ����
int setREGBigModbusRegister(int, int);//�������� ���������� ��������
int setREGBigModbusBit(int, int);//�������� ���������� ����

void setREGBigCountObject(void);//�������� �-�� �������
void preREGBigReadAction(void);//action �� ������
void preREGBigWriteAction(void);//action �� ������
int  postREGBigWriteAction(void);//action ����� ������
int passwordImunitetRegREGBigComponent(int adrReg);

COMPONENT_OBJ *regbigcomponent;

/**************************************/
//���������� ���������� REGistrator
/**************************************/
void constructorREGBigComponent(COMPONENT_OBJ *regbigcomp)
{
  regbigcomponent = regbigcomp;

  regbigcomponent->getModbusRegister = getREGBigModbusRegister;//�������� ���������� ��������
  regbigcomponent->getModbusBit      = getREGBigModbusBit;//�������� ���������� ����
  regbigcomponent->setModbusRegister = setREGBigModbusRegister;//�������� ���������� ��������
  regbigcomponent->setModbusBit      = setREGBigModbusBit;//�������� ���������� ����

  regbigcomponent->preReadAction   = preREGBigReadAction;//action �� ������
  regbigcomponent->preWriteAction  = preREGBigWriteAction;//action �� ������
  regbigcomponent->postWriteAction = postREGBigWriteAction;//action ����� ������

  regbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getREGBigModbusRegister(int adrReg)
{
  //�������� ���������� ��������
  if(privateREGBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;

  int offset = adrReg-BEGIN_ADR_REGISTER;
//������������ ���������� ������� ����������� ������������
  if(offset<32) return getRangN_BIGModbusRegister(&current_settings_interfaces.ranguvannja_analog_registrator[0],
                                                   REGISTERS_REG, offset );
//����������� ��������� ������� �������� ����������� ������������
  if(offset>=37&&offset<69) 
  {
   //���������� ����������
   if(
      (
       !(
         ((pointInterface == USB_RECUEST  ) && ((number_record_of_ar_for_USB   != -1) && (id_ar_record_for_USB[0]   != '\0'))) ||
         ((pointInterface == RS485_RECUEST) && ((number_record_of_ar_for_RS485 != -1) && (id_ar_record_for_RS485[0] != '\0')))
        )               
      )
      ||
      (
       (
        (state_ar_record_fatfs != STATE_AR_NONE_FATFS) &&
        (state_ar_record_fatfs != STATE_AR_MEMORY_FULL_FATFS) &&
        (state_ar_record_fatfs != STATE_AR_BLOCK_FATFS)
       )
       ||
       ((clean_rejestrators & CLEAN_AR) != 0)  
       ||  
       (
        (control_tasks_dataflash & (
                                    TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_FS |
                                    TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_FS
                                   )
        ) != 0
       )
      )
     )
    {
      //����� ��� �������� ������/�������� ��� ���������� ����������, ��� ���� ������� ����� (������������ ����� ��������� 20 �), ���� ������� ����������� ���������� � ��������� ����������
      return MARKER_ERRORPERIMETR;
    }

      //����� ������ ���
      int *point_to_first_number_time_sample, *point_to_last_number_time_sample;
      char *point_id_ar_record;
      int *point_to_max_number_time_sample;
      unsigned char *point_to_buffer;

      if (pointInterface == USB_RECUEST)
      {
        point_id_ar_record = id_ar_record_for_USB;
        point_to_first_number_time_sample = &first_number_time_sample_for_USB;
        point_to_last_number_time_sample  = &last_number_time_sample_for_USB;
        point_to_max_number_time_sample = &max_number_time_sample_USB;
          
        point_to_buffer = buffer_for_USB_read_record_ar;
      }
      else
      {
        point_id_ar_record = id_ar_record_for_RS485;
        point_to_first_number_time_sample = &first_number_time_sample_for_RS485;
        point_to_last_number_time_sample  = &last_number_time_sample_for_RS485;
        point_to_max_number_time_sample = &max_number_time_sample_RS485;
        
        point_to_buffer = buffer_for_RS485_read_record_ar;
      }

      if ((*point_to_first_number_time_sample) != -1)
      {
        //����� �� ������������ ���������� ��������� ����������� ��������
              
        FIL fil;
        FRESULT res = f_open(&fil, point_id_ar_record, FA_READ);
        if (res == FR_OK) 
        {
          res = f_lseek(&fil, 0);
          if (res == FR_OK)
          {
            //����������� ������� ��������� ������ ������ ������ � ������, ������ �������, ������� ���� 
            *point_to_first_number_time_sample = -1;
            int last_number_time_sample_tmp = (SIZE_PAGE_DATAFLASH_2 - sizeof(__HEADER_AR))/((NUMBER_ANALOG_CANALES + NUMBER_WORD_DIGITAL_PART_AR)*sizeof(short int));
            int max_number_time_sample = *point_to_max_number_time_sample = (f_size(&fil) - sizeof(__HEADER_AR))/((NUMBER_ANALOG_CANALES + NUMBER_WORD_DIGITAL_PART_AR)*sizeof(short int));
            
            if (max_number_time_sample >= 0)
            {
              if (last_number_time_sample_tmp <= max_number_time_sample)
              {
                *point_to_last_number_time_sample = last_number_time_sample_tmp - 1;//����� ���������� �������� ���� �������
              }
              else
              {
                *point_to_last_number_time_sample = max_number_time_sample - 1;
              }
              
              unsigned int read_tmp;
              UINT ByteToRead = sizeof(__HEADER_AR) + ((unsigned int)(*point_to_last_number_time_sample) + 1)*(NUMBER_ANALOG_CANALES + NUMBER_WORD_DIGITAL_PART_AR)*sizeof(short int);
              res = f_read(&fil, point_to_buffer, ByteToRead, &read_tmp);
              if ((res != FR_OK) || (read_tmp != ByteToRead)) return MARKER_ERRORPERIMETR;
            }
            else return MARKER_ERRORPERIMETR;
          }
          else return MARKER_ERRORPERIMETR;

          res = f_close(&fil);
          if (res != FR_OK) 
          {
            //����������� ��������, ��� ����� � �� ���� ����.
            _SET_BIT(set_diagnostyka, ERROR_AR_UNDEFINED_BIT);
            return MARKER_ERRORPERIMETR;
          }
        }
        else return MARKER_ERRORPERIMETR;
      }

      //���� �� ���� �����, �� ������� �� ��������� ����������� ���������� ��� ��������
      __HEADER_AR *p_header_ar = (__HEADER_AR*)point_to_buffer;
      return getRangN_BIGModbusRegister(p_header_ar->cur_active_sources, REGISTERS_ACTIONREG, offset-37 );
  }//if(offset>=37&&offset<69) 

//������������ ���������� ������� ����������� ������������
  if(offset>=300&&offset<332)
      return getRangN_BIGModbusRegister(&current_settings_interfaces.ranguvannja_digital_registrator[0],
                                                               REGISTERS_REG, offset-300 );
//����������� ��������� ������� �������� ����������� ������������
  if(offset>=337&&offset<369) 
  {
   //���������� ����������
          if (
            //�� ������ ����������������� ����������� ���������� ������ ����������� ����������
            //pointInterface=0 ����� ���������� 0-USB 1-RS485
            ((pointInterface == USB_RECUEST  ) && (number_record_of_dr_for_USB == 0xffff)) ||
            ((pointInterface == RS485_RECUEST) && (number_record_of_dr_for_RS485 == 0xffff))
          ) return MARKER_ERRORPERIMETR;
         if (
              (
               ((pointInterface == USB_RECUEST  ) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB  ) != 0)) ||
               ((pointInterface == RS485_RECUEST) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485) != 0))
              ) 
              ||  
              ((clean_rejestrators & CLEAN_DR) != 0)
            )  
           
    {
     //����� ��� ���������� ��� ���������� ������ ����������� ����������, ���� �� �������� � ��������� �����������
      return MARKER_ERRORPERIMETR;
    }

      //����� ������ ���
      unsigned char *point_to_buffer;
      if (pointInterface == USB_RECUEST) point_to_buffer = buffer_for_USB_read_record_dr;
      else point_to_buffer = buffer_for_RS485_read_record_dr;
      //���� �� ���� �����, �� ������� �� ��������� ����������� ���������� ��� ��������
      //���������, �� ������� ��������� ����������
      unsigned int *activeNBIG_dr = (unsigned int*)(&point_to_buffer[FIRST_INDEX_SOURCE_DR+0]);//��������� �� N_BIG ������ �������� ������ ������� �����
      return getRangN_BIGModbusRegister(activeNBIG_dr, REGISTERS_ACTIONREG, offset-337 );
  }//if(offset>=337&&offset<369) 

  switch(offset)
    {
    case 32://����� ������ ����������� ������������ (����������� ������)
      return (current_settings_interfaces.prefault_number_periods) &0xFFFF; //� ������� ��������� �������� �� ���������, � ������� ������
    case 33://����� ������ ����������� ������������ (����������� ������)
      return (current_settings_interfaces.postfault_number_periods) &0xFFFF; //� ������� ��������� �������� �� ���������, � ������� ������
    case 34://���������� ���������� �������������
      {
        unsigned int first_number = (info_rejestrator_ar.first_number < 0) ? 0 : (info_rejestrator_ar.first_number + 1);
        unsigned int last_number  = (info_rejestrator_ar.last_number  < 0) ? 0 : (info_rejestrator_ar.last_number + 1);
      
        unsigned int number_records;
        if (first_number == 0) number_records = 0;
        else if (first_number >= last_number) number_records = first_number - last_number + 1;
        else number_records = NUMBER_FATFS_NAME - last_number + first_number + 1;
                
        return (number_records) & 0xFFFF;
      }
#define IMUNITET_REG35 35
    case IMUNITET_REG35://������� ���������� �����������
      if(pointInterface==USB_RECUEST)//����� ���������� 0-USB 1-RS485 2-LAN
        return (number_record_of_ar_for_USB) &0xFFFF;
      else if(pointInterface==RS485_RECUEST)
        return (number_record_of_ar_for_RS485) &0xFFFF;
//#if (MODYFIKACIA_VERSII_PZ >= 10)
//      else if(pointInterface==LAN_RECUEST)
//        return (number_record_of_ar_for_LAN) &0xFFFF;
//#endif  
      //���������� ���� ����� �� ���� � �������� �����
      else total_error_sw_fixed(212);
    case 36://�������� ���������� �����������
      return MARKER_ERRORPERIMETR;

    case 334://���������� ���������� �������������
      return (info_rejestrator_dr.number_records) &0xFFFF;
#define IMUNITET_REG335 335
    case IMUNITET_REG335://������� ���������� �����������
      if(pointInterface==USB_RECUEST)//����� ���������� 0-USB 1-RS485
        return (number_record_of_dr_for_USB) &0xFFFF;
      else if(pointInterface==RS485_RECUEST)
        return (number_record_of_dr_for_RS485) &0xFFFF;
//#if (MODYFIKACIA_VERSII_PZ >= 10)
//      else if(pointInterface==LAN_RECUEST)
//        return (number_record_of_dr_for_LAN) &0xFFFF;
//#endif  
      //���������� ���� ����� �� ���� � �������� �����
      else total_error_sw_fixed(213);
    case 336://�������� ���������� �����������
      return MARKER_ERRORPERIMETR;
    }//switch

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int getREGBigModbusBit(int x)
{
  //�������� ���������� ��������
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setREGBigModbusRegister(int adrReg, int dataReg)
{
  //�������� ���������� ��������
  if(privateREGBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(regbigcomponent->isActiveActualData)
    {
      edition_settings = current_settings_interfaces;//������ �����
    }//if(uprbigcomponent->isActiveActualData)
  superClearActiveActualData();

  superSetOperativMarker(regbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//�������� � �����

  int offset = adrReg-BEGIN_ADR_REGISTER;
//������������ ���������� ������� ����������� ������������
  if(offset<32) return validN_BIGACMD(dataReg);
//����������� ��������� ������� �������� ����������� ������������
  if(offset>=37&&offset<69) return MARKER_ERRORDIAPAZON;
//������������ ���������� ������� ����������� ������������
  if(offset>=300&&offset<332) return validN_BIGACMD(dataReg);
//����������� ��������� ������� �������� ����������� ������������
  if(offset>=337&&offset<369) return MARKER_ERRORDIAPAZON;

  switch(offset)
    {
    case 32://����� ������ ����������� ������������ (����������� ������)
      if(dataReg<TIMEOUT_PREFAULT_MIN/20 || dataReg>TIMEOUT_PREFAULT_MAX/20) return MARKER_ERRORDIAPAZON;
      break;
    case 33://����� ������ ����������� ������������ (����������� ������)
      if(dataReg<TIMEOUT_POSTFAULT_MIN/20 || dataReg>TIMEOUT_POSTFAULT_MAX/20) return MARKER_ERRORDIAPAZON;
      break;
    case 34://���������� ���������� �������������
      return MARKER_ERRORDIAPAZON;
    case 35://������� ���������� �����������
      {
        if (
            ((clean_rejestrators & CLEAN_AR) != 0) ||
            (
             (state_ar_record_fatfs != STATE_AR_NONE_FATFS) &&
             (state_ar_record_fatfs != STATE_AR_MEMORY_FULL_FATFS) &&
             (state_ar_record_fatfs != STATE_AR_BLOCK_FATFS)
            )
          ) return MARKER_ERRORDIAPAZON;

        unsigned int first_number = (info_rejestrator_ar.first_number < 0) ? 0 : (info_rejestrator_ar.first_number + 1);
        unsigned int last_number  = (info_rejestrator_ar.last_number  < 0) ? 0 : (info_rejestrator_ar.last_number + 1);
                
        unsigned int number_records;
        if (first_number == 0) number_records = 0;
        else if (first_number >= last_number) number_records = first_number - last_number + 1;
        else number_records = NUMBER_FATFS_NAME - last_number + first_number + 1;
                
        if(! ((unsigned int)dataReg < number_records)) return MARKER_ERRORDIAPAZON;

      }
      break;
    case 36://�������� ���������� �����������
      if(dataReg!=CMD_WORD_CLEAR_AR) return MARKER_ERRORDIAPAZON;
      break;
    case 334://���������� ���������� �������������
      return MARKER_ERRORDIAPAZON;
    case 335://������� ���������� �����������
      if (
        ((clean_rejestrators & CLEAN_DR) != 0) ||
        (
          ((pointInterface == USB_RECUEST  ) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB  ) != 0)) ||
          ((pointInterface == RS485_RECUEST  ) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485) != 0))
        )
      ) return MARKER_ERRORDIAPAZON;
      if(! ((unsigned int)dataReg < info_rejestrator_dr.number_records)) return MARKER_ERRORDIAPAZON;
      if(dataReg > MAX_NUMBER_RECORDS_INTO_DR) return MARKER_ERRORDIAPAZON;
      break;
    case 336://�������� ���������� �����������
      if(dataReg!=CMD_WORD_CLEAR_DR) return MARKER_ERRORDIAPAZON;
      break;
    }//switch

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setREGBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //�������� ���������� ��������
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preREGBigReadAction(void)
{
//action �� ������
  regbigcomponent->isActiveActualData = 1;
}//
void preREGBigWriteAction(void)
{
//action �� ������
  regbigcomponent->operativMarker[0] = -1;
  regbigcomponent->operativMarker[1] = -1;//����������� ������
  regbigcomponent->isActiveActualData = 1;
}//
int postREGBigWriteAction(void)
{
  extern int upravlSchematic;//���� Rang
  extern int upravlSetting;//���� Setting
//action ����� ������
  int beginAdr = regbigcomponent->operativMarker[0];
  if(beginAdr<0) return 0;//�� ���� ������
  int endAdr   = regbigcomponent->operativMarker[1];
  int countAdr = endAdr-beginAdr+1;
  if(endAdr<0) countAdr = 1;
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//����� �������� TempWriteArray

  int flag1=1;
  int flag2=1;
  int countReg=countAdr;
  for(int i=0; i<countAdr; i++)
    {
      int offset = beginAdr-BEGIN_ADR_REGISTER+i;
      if(offset<32&&flag1)
        {
          writeRangN_BIGModbusRegister(&edition_settings.ranguvannja_analog_registrator[0], REGISTERS_REG, beginAdr,
                                       countReg, BEGIN_ADR_REGISTER);
          flag1=0;
          upravlSchematic = 1;//���� Rang
        }//if

      if(offset>=300&&offset<332&&flag2)
        {
          writeRangN_BIGModbusRegister(&edition_settings.ranguvannja_digital_registrator[0], REGISTERS_REG, beginAdr,
                                       countReg, BEGIN_ADR_REGISTER+300);
          flag2=0;
          upravlSchematic = 1;//���� Rang
        }//if
      switch(offset)
        {
        case 32://����� ������ ����������� ������������ (����������� ������)
          edition_settings.prefault_number_periods = tempWriteArray[offsetTempWriteArray+i];//� ������� ��������� �������� �� ���������, � ������� ������
          upravlSetting = 1;//���� Setting
          break;
        case 33://����� ������ ����������� ������������ (����������� ������)
          edition_settings.postfault_number_periods = tempWriteArray[offsetTempWriteArray+i];//� ������� ��������� �������� �� ���������, � ������� ������
          upravlSetting = 1;//���� Setting
          break;
        case 35://������� ���������� �����������
        {
          int *point_to_number_record_of_ar;
          int *point_to_first_number_time_sample, *point_to_last_number_time_sample;
          char *point_id_ar_record;
          int *point_to_max_number_time_sample;
          unsigned char *point_to_Buffer;

          if (pointInterface == USB_RECUEST)
            {
              point_to_number_record_of_ar = &number_record_of_ar_for_USB;
              point_id_ar_record = id_ar_record_for_USB;
              point_to_first_number_time_sample = &first_number_time_sample_for_USB;
              point_to_last_number_time_sample = &last_number_time_sample_for_USB;
              point_to_max_number_time_sample = &max_number_time_sample_USB;
          
              point_to_Buffer = buffer_for_USB_read_record_ar;
            }
          else
            {
              point_to_number_record_of_ar = &number_record_of_ar_for_RS485;
              point_id_ar_record = id_ar_record_for_RS485;
              point_to_first_number_time_sample = &first_number_time_sample_for_RS485;
              point_to_last_number_time_sample = &last_number_time_sample_for_RS485;
              point_to_max_number_time_sample = &max_number_time_sample_RS485;
          
              point_to_Buffer = buffer_for_RS485_read_record_ar;
            }
          
          unsigned short int data = tempWriteArray[offsetTempWriteArray+i];
        
          int record_name = info_rejestrator_ar.first_number - data;
          if (record_name < 0) record_name += NUMBER_FATFS_NAME;

          int n = snprintf(point_id_ar_record, (8 + 1), "%d", record_name);
          if (n > 8) n = 8; //���������� ����� ����� � �� ���� ����
          point_id_ar_record[n++] = '.';
          point_id_ar_record[n++] = 'd';
          point_id_ar_record[n++] = 'a';
          point_id_ar_record[n++] = 't';
          point_id_ar_record[n++] = '\0';
        
          unsigned int error = 0;
          FIL fil;
          FRESULT res = f_open(&fil, point_id_ar_record, FA_READ);
          if (res == FR_OK) 
          {
            res = f_lseek(&fil, 0);
            if (res == FR_OK)
            {
              //����������� ������� ��������� ������ ������ ������ � ������, ������ �������, ������� ���� 
              *point_to_first_number_time_sample = -1;
              int last_number_time_sample_tmp = (SIZE_PAGE_DATAFLASH_2 - sizeof(__HEADER_AR))/((NUMBER_ANALOG_CANALES + NUMBER_WORD_DIGITAL_PART_AR)*sizeof(short int));
              int max_number_time_sample = *point_to_max_number_time_sample = (f_size(&fil) - sizeof(__HEADER_AR))/((NUMBER_ANALOG_CANALES + NUMBER_WORD_DIGITAL_PART_AR)*sizeof(short int));
            
              if (max_number_time_sample >= 0)
              {
                if (last_number_time_sample_tmp <= max_number_time_sample)
                {
                  *point_to_last_number_time_sample = last_number_time_sample_tmp - 1;//����� ���������� �������� ���� �������
                }
                else
                {
                  *point_to_last_number_time_sample = max_number_time_sample - 1;
                }
              
                unsigned int read_tmp;
                UINT ByteToRead = sizeof(__HEADER_AR) + ((unsigned int)(*point_to_last_number_time_sample) + 1)*(NUMBER_ANALOG_CANALES + NUMBER_WORD_DIGITAL_PART_AR)*sizeof(short int);
                res = f_read(&fil, point_to_Buffer, ByteToRead, &read_tmp);
                if ((res != FR_OK) || (read_tmp != ByteToRead)) error = ERROR_SLAVE_DEVICE_FAILURE;
              }
              else error = ERROR_SLAVE_DEVICE_FAILURE;
            }
            else error = ERROR_SLAVE_DEVICE_FAILURE;

            res = f_close(&fil);
            if (res != FR_OK) 
            {
              //����������� ��������, ��� ����� � �� ���� ����.
              _SET_BIT(set_diagnostyka, ERROR_AR_UNDEFINED_BIT);
              error = ERROR_SLAVE_DEVICE_FAILURE;
            }
          }
          else error = ERROR_SLAVE_DEVICE_FAILURE;
        
          if (error == 0)
          {
            //������������ ����� ������ ����������� ���������� ��� �������
            *point_to_number_record_of_ar = data;
          }
          else
          {
            //�������, �� ���� ������� ���� ��� �������
            *point_to_number_record_of_ar = -1;
            point_id_ar_record[0] = '\0';
            return ERROR_VALID2;
          }
        }
        break;//case 35
        case 36://�������� ���������� �����������
//������ ��������
          if (
            (current_ekran.current_level == EKRAN_DATA_LADEL_AR)
            ||
            (state_ar_record_m           != STATE_AR_NONE_M )
            ||  
            (state_ar_record_prt         != STATE_AR_NONE_PRT )
            ||  
            (
             (control_tasks_dataflash & (
                                         TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_FS |
                                         TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_FS      |
                                         TASK_MAMORY_READ_DATAFLASH_FOR_FS 
                                        )
             ) != 0
            )
            ||
            ((clean_rejestrators & CLEAN_AR) != 0)
          ) return ERROR_VALID2;//������ ���������

          clean_rejestrators |= CLEAN_AR;
          break;

        case 335://������� ���������� �����������

          if(pointInterface==USB_RECUEST)//����� ���������� 0-USB 1-RS485
            {
//int test = tempWriteArray[offsetTempWriteArray+i];
              number_record_of_dr_for_USB = tempWriteArray[offsetTempWriteArray+i];
              //������ ������� ������� ����������� ���������� ��� ���������� USB

              //����������� ����� ������� ������
              part_reading_dr_from_dataflash_for_USB = 0;
              //������ ������� ������� ��� � ����� ���'��
              control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB;
            }//if
          else
            {
              number_record_of_dr_for_RS485 = tempWriteArray[offsetTempWriteArray+i];
              //������ ������� ������� ����������� ���������� ��� ���������� RS-485

              //����������� ����� ������� ������
              part_reading_dr_from_dataflash_for_RS485 = 0;
              //������ ������� ������� ��� � ����� ���'��
              control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485;
            }

          break;
        case 336://�������� ���������� �����������
//������ ��������
          if (
            (current_ekran.current_level == EKRAN_TITLES_DIGITAL_REGISTRATOR)
            ||
            (current_ekran.current_level == EKRAN_DATA_LADEL_DR             )
            ||
            (current_ekran.current_level == EKRAN_CHANGES_SIGNALS_DR        )
            ||
            (current_ekran.current_level == EKRAN_VALUE_VMP                 )
            ||
            (
              (control_tasks_dataflash & (
                 TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR |
                 TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB                    |
                 TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485                  |
                 TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU
               )
              ) != 0
            )
            ||
            ((clean_rejestrators & CLEAN_DR) != 0)
          ) return ERROR_VALID2;//������ ���������

          //�������, �� ����� �������� ����������� ����������
          clean_rejestrators |= CLEAN_DR;
          break;
        }//switch
    }//for

  return 0;
}//

int privateREGBigGetReg2(int adrReg)
{
  //��������� ������� ��������
  return controlPerimetr(adrReg, BEGIN_ADR_REGISTER, END_ADR_REGISTER);
}//privateGetReg2(int adrReg)

int passwordImunitetRegREGBigComponent(int adrReg)
{
  //����������� � ������ ������ ��������� 0 - ���� ��������
  if(privateREGBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  switch(adrReg)
  {
  case BEGIN_ADR_REGISTER+IMUNITET_REG35://������� ���������� �����������
  case BEGIN_ADR_REGISTER+IMUNITET_REG335://������� ���������� �����������
    return 0;//���� ��������
  }//switch
  return MARKER_OUTPERIMETR;
}//passwordImunitetRegREGBigComponent(int adrReg)
