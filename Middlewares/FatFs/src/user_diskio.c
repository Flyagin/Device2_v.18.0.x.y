/* USER CODE BEGIN Header */
/**
 ******************************************************************************
  * @file    user_diskio.c
  * @brief   This file includes a diskio driver skeleton to be completed by the user.
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
 /* USER CODE END Header */

#ifdef USE_OBSOLETE_USER_CODE_SECTION_0
/* 
 * Warning: the user section 0 is no more in use (starting from CubeMx version 4.16.0)
 * To be suppressed in the future. 
 * Kept to ensure backward compatibility with previous CubeMx versions when 
 * migrating projects. 
 * User code previously added there should be copied in the new user sections before 
 * the section contents can be deleted.
 */
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */
#endif

/* USER CODE BEGIN DECL */

/* Includes ------------------------------------------------------------------*/
//#include <string.h>
//#include "ff_gen_drv.h"
#include "header.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Disk status */
static volatile DSTATUS Stat = STA_NOINIT;

/* USER CODE END DECL */

/* Private function prototypes -----------------------------------------------*/
DSTATUS USER_initialize (BYTE pdrv);
DSTATUS USER_status (BYTE pdrv);
DRESULT USER_read (BYTE pdrv, BYTE *buff, DWORD sector, UINT count);
#if _USE_WRITE == 1
  DRESULT USER_write (BYTE pdrv, const BYTE *buff, DWORD sector, UINT count);  
#endif /* _USE_WRITE == 1 */
#if _USE_IOCTL == 1
  DRESULT USER_ioctl (BYTE pdrv, BYTE cmd, void *buff);
#endif /* _USE_IOCTL == 1 */

Diskio_drvTypeDef  USER_Driver =
{
  USER_initialize,
  USER_status,
  USER_read, 
#if  _USE_WRITE
  USER_write,
#endif  /* _USE_WRITE == 1 */  
#if  _USE_IOCTL == 1
  USER_ioctl,
#endif /* _USE_IOCTL == 1 */
};

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes a Drive
  * @param  pdrv: Physical drive number (0..)
  * @retval DSTATUS: Operation status
  */
DSTATUS USER_initialize (
	BYTE pdrv           /* Physical drive nmuber to identify the drive */
)
{
  /* USER CODE BEGIN INIT */
  UNUSED(pdrv);
  Stat = STA_NOINIT;
    
  // write your own code here to initialize the drive
    
  Stat &= ~STA_NOINIT;
  return Stat;
  /* USER CODE END INIT */
}
 
/**
  * @brief  Gets Disk Status 
  * @param  pdrv: Physical drive number (0..)
  * @retval DSTATUS: Operation status
  */
DSTATUS USER_status (
	BYTE pdrv       /* Physical drive number to identify the drive */
)
{
  /* USER CODE BEGIN STATUS */
  UNUSED(pdrv);
  Stat = STA_NOINIT;
  
  Stat &= ~STA_NOINIT;
  return Stat;
  /* USER CODE END STATUS */
}

/**
  * @brief  Reads Sector(s) 
  * @param  pdrv: Physical drive number (0..)
  * @param  *buff: Data buffer to store read data
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to read (1..128)
  * @retval DRESULT: Operation result
  */
DRESULT USER_read (
	BYTE pdrv,      /* Physical drive nmuber to identify the drive */
	BYTE *buff,     /* Data buffer to store read data */
	DWORD sector,   /* Sector address in LBA */
	UINT count      /* Number of sectors to read */
)
{
  /* USER CODE BEGIN READ */
  UNUSED(pdrv);
  
  DWORD address_df = sector*_MIN_SS;
  UINT count_tmp = count*_MIN_SS;
  BYTE *buff_tmp = buff;
  
  while (count_tmp != 0)
  {
    fs_temporary_address = address_df; //������ � ��� ����� ���������
    fs_count_to_transfer = ((count_tmp >= SIZE_PAGE_DATAFLASH_2) ? SIZE_PAGE_DATAFLASH_2 : count_tmp); //������� ����
    
    //������ ������� ������
#ifndef I2C_EEPROM
    mutex_spi1 = true;
#endif
    control_tasks_dataflash |= TASK_MAMORY_READ_DATAFLASH_FOR_FS;
#ifndef I2C_EEPROM
    mutex_spi1 = false;
#endif
    
    //������� ���������� �������
    while((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_FS) != 0) periodical_operations();
    
    //������� ������� ���� � �������� �����
    for (size_t i = 0; i < fs_count_to_transfer; i++)  *buff_tmp++ = buffer_for_fs[i];
    
    //������������ ������
    address_df += fs_count_to_transfer;
    //������������ ������� ���� ��� �������
    count_tmp -= fs_count_to_transfer;
  }
  
  return RES_OK;
  /* USER CODE END READ */
}

/**
  * @brief  Writes Sector(s)  
  * @param  pdrv: Physical drive number (0..)
  * @param  *buff: Data to be written
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to write (1..128)
  * @retval DRESULT: Operation result
  */
#if _USE_WRITE == 1
DRESULT USER_write (
	BYTE pdrv,          /* Physical drive nmuber to identify the drive */
	const BYTE *buff,   /* Data to be written */
	DWORD sector,       /* Sector address in LBA */
	UINT count          /* Number of sectors to write */
)
{ 
  /* USER CODE BEGIN WRITE */
  /* USER CODE HERE */
  UNUSED(pdrv);
  
  DWORD address_df = sector*_MIN_SS;
  UINT count_tmp = count*_MIN_SS;
  const BYTE *buff_tmp = buff;
  
  unsigned int fs_count_to_transfer_tmp; //������ ��� ������������ ��������� � �������� DataFlash, �� �������� �������
  while (count_tmp != 0)
  {
    fs_temporary_address = address_df; //������ � ��� ����� ����������
    
    //������� ����
    UINT free_space_for_df_page = SIZE_PAGE_DATAFLASH_2 - (fs_temporary_address & (SIZE_PAGE_DATAFLASH_2 - 1));
    fs_count_to_transfer_tmp = fs_count_to_transfer = ((count_tmp >= free_space_for_df_page) ? free_space_for_df_page : count_tmp); 

    //������� ���� ��� ������
    for (size_t i = 0; i < fs_count_to_transfer; i++)  buffer_for_fs[i] = *buff_tmp++;
    
    //������ ������� ������
    unsigned int task_writing_for_fs = (fs_count_to_transfer == SIZE_PAGE_DATAFLASH_2) ? TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_FS : TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_FS;
#ifndef I2C_EEPROM
    mutex_spi1 = true;
#endif
    control_tasks_dataflash |= task_writing_for_fs;
#ifndef I2C_EEPROM
    mutex_spi1 = false;
#endif
    
    //������� ���������� ������
    while((control_tasks_dataflash & task_writing_for_fs) != 0) periodical_operations();
    
    //������������ ������
    address_df += fs_count_to_transfer_tmp;
    //������������ ������� ���� ��� �������
    count_tmp -= fs_count_to_transfer_tmp;
  }
  
  return RES_OK;
  /* USER CODE END WRITE */
}
#endif /* _USE_WRITE == 1 */

/**
  * @brief  I/O control operation  
  * @param  pdrv: Physical drive number (0..)
  * @param  cmd: Control code
  * @param  *buff: Buffer to send/receive control data
  * @retval DRESULT: Operation result
  */
#if _USE_IOCTL == 1
DRESULT USER_ioctl (
	BYTE pdrv,      /* Physical drive nmuber (0..) */
	BYTE cmd,       /* Control code */
	void *buff      /* Buffer to send/receive control data */
)
{
  /* USER CODE BEGIN IOCTL */
  UNUSED(pdrv);
  UNUSED(buff);
  DRESULT res = RES_ERROR;
  
  switch (cmd)
  {
  case CTRL_SYNC:
    {
      res = RES_OK;
      break;
    }
  case GET_SECTOR_COUNT:
    {
      *((DWORD*)buff) = (SIZE_PAGE_DATAFLASH_2*NUMBER_PAGES_INTO_DATAFLASH_2) / _MIN_SS;
      res = RES_OK;
      break;
    }
  case GET_BLOCK_SIZE:
    {
      *((DWORD*)buff) = 1;
      res = RES_OK;
    }
  }
  
  return res;
  /* USER CODE END IOCTL */
}
#endif /* _USE_IOCTL == 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
