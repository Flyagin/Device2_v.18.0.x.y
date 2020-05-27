/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

//#include "fatfs.h"
#include "header.h"

uint8_t retUSER;    /* Return value for USER */
char USERPath[4];   /* USER logical drive path */
FATFS USERFatFS;    /* File system object for USER logical drive */
FIL USERFile;       /* File object for USER */

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */    

void MX_FATFS_Init(void) 
{
  /*## FatFS: Link the USER driver ###########################*/
  if (FATFS_LinkDriver(&USER_Driver, USERPath) == 0)
  {
    FRESULT res = f_mount(&USERFatFS, (TCHAR const*)USERPath, 1);
    switch (res)
    {
    case FR_OK: break;
    case FR_NO_FILESYSTEM:
      {
        //чекаємо, поки з RTC буде зчитано поточний час
        while(
              (_CHECK_SET_BIT(    diagnostyka, EVENT_START_SYSTEM_BIT       ) != 0) ||
              (_CHECK_SET_BIT(set_diagnostyka, EVENT_START_SYSTEM_BIT       ) != 0) ||
              (_CHECK_SET_BIT(    diagnostyka, EVENT_RESTART_SYSTEM_BIT     ) != 0) ||
              (_CHECK_SET_BIT(set_diagnostyka, EVENT_RESTART_SYSTEM_BIT     ) != 0) ||
              (_CHECK_SET_BIT(    diagnostyka, EVENT_SOFT_RESTART_SYSTEM_BIT) != 0) ||
              (_CHECK_SET_BIT(set_diagnostyka, EVENT_SOFT_RESTART_SYSTEM_BIT) != 0)
             )
        {
          periodical_operations_communication(false);
          periodical_operations();
        }
        
        //формуємо файлову систему
        res = f_mkfs (USERPath, 1, 0);
        if (res != FR_OK) _SET_BIT(set_diagnostyka, ERROR_FATFS);
        else
        {
          if (_GET_OUTPUT_STATE(FATFS_command, FATFS_FORMAT)) _CLEAR_STATE(FATFS_command, FATFS_FORMAT);
        }
        
        break;
      }
    default:
      {
        _SET_BIT(set_diagnostyka, ERROR_FATFS);
        break;
      }
    }

//    FIL fil;
//    res = f_open(&fil, "0.dat", FA_CREATE_ALWAYS | FA_WRITE);
//    res = f_lseek(&fil, 0);
//    
//    uint16_t array[3] = {10, 12, 1978};
//    unsigned int written;
//    res = f_write(&fil, array, 3*sizeof(uint16_t), &written);
//    res = f_close(&fil);
//    if ((res != FR_OK) || (written != 3*sizeof(uint16_t))) _SET_BIT(set_diagnostyka, ERROR_FATFS);

//    res = f_open(&fil, "0.dat", FA_READ);
//    if (res == FR_OK)
//    {
//      res = f_lseek(&fil, 0);
//    
//      uint16_t array[3*3];
//      uint8_t *p_array = (uint8_t*)array;
//      unsigned int read = 0;
//      while (!f_eof(&fil))
//      {
//        unsigned int read_tmp;
//        res = f_read(&fil, p_array++, 1, &read_tmp);
//        read += read_tmp;
//      }
//      res = f_close(&fil);
//      if (res != FR_OK) _SET_BIT(set_diagnostyka, ERROR_FATFS);
//    }

//    res = f_unlink("0.dat");
//    if (res != FR_OK) _SET_BIT(set_diagnostyka, ERROR_FATFS);
  }
  else  _SET_BIT(set_diagnostyka, ERROR_FATFS);
    

  /* USER CODE BEGIN Init */
  /* additional user code for init */     
  /* USER CODE END Init */
}

/**
  * @brief  Gets Time from RTC 
  * @param  None
  * @retval Time in DWORD
  */
DWORD get_fattime(void)
{
  /* USER CODE BEGIN get_fattime */
  unsigned char *label_to_time_array;
  if (copying_time == 2) label_to_time_array = time_copy;
  else label_to_time_array = time;
  
  DWORD res = 0;
  unsigned int temp, a, b;
  
  //Рік
  temp = label_to_time_array[6];
  a = temp >> 4;
  b = temp & 0xf;
  if ((a <= 9) && (b <= 9))
  {
    temp = 10*a + b;
    res |= (temp + 20) << 25;
    
  }
  else return 0;
  
  //Місяць
  temp = label_to_time_array[5];
  a = temp >> 4;
  b = temp & 0xf;
  if ((a <= 1) && (b <= 9))
  {
    temp = 10*a + b;
    if (temp <= 12) res |= temp << 21;
    else return 0;
  }
  else return 0;
  
  //День місяця
  temp = label_to_time_array[4];
  a = temp >> 4;
  b = temp & 0xf;
  if ((a <= 3) && (b <= 9))
  {
    temp = 10*a + b;
    if (temp <= 31) res |= temp << 16;
    else return 0;
  }
  else return 0;
  
  //Година
  temp = label_to_time_array[3];
  a = temp >> 4;
  b = temp & 0xf;
  if ((a <= 2) && (b <= 9))
  {
    temp = 10*a + b;
    if (temp <= 23) res |= temp << 11;
    else return 0;
  }
  else return 0;
  
  //Хвилини
  temp = label_to_time_array[2];
  a = temp >> 4;
  b = temp & 0xf;
  if ((a <= 5) && (b <= 9))
  {
    temp = 10*a + b;
    if (temp <= 59) res |= temp << 5;
    else return 0;
  }
  else return 0;
  
  //Секунди
  temp = label_to_time_array[1];
  a = temp >> 4;
  b = temp & 0xf;
  if ((a <= 5) && (b <= 9))
  {
    temp = 10*a + b;
    if (temp <= 59) res |= (temp >> 1) << 0;
    else return 0;
  }
  else return 0;

  return res;
  /* USER CODE END get_fattime */  
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
