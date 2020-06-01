#ifndef __CONST_DRIVER_SERIAL_FLASH__
#define __CONST_DRIVER_SERIAL_FLASH__

#define NUMBER_DATAFLASH_CHIP      2

#define INDEX_DATAFLASH_1           0
#define INDEX_DATAFLASH_2           1
#define INDEX_EEPROM                3

#define VAGA_SIZE_PAGE_DATAFLASH_1      8 //�� ��������� ������� ����� ��� ����, ��� ����� ���� ����� ������� �� 256 � ����� �� 256
#define SIZE_PAGE_DATAFLASH_1           (1 << VAGA_SIZE_PAGE_DATAFLASH_1) //256 ����
#define NUMBER_PAGES_INTO_DATAFLASH_1   512

#define VAGA_SIZE_PAGE_DATAFLASH_2      9 //�� ��������� ������� ����� ��� ����, ��� ����� ���� ����� ������� �� 512 � ����� �� 512
#define SIZE_PAGE_DATAFLASH_2           (1 << VAGA_SIZE_PAGE_DATAFLASH_2) //512 ����
#define NUMBER_PAGES_INTO_DATAFLASH_2   4096

#if SIZE_PAGE_DATAFLASH_2 >= SIZE_PAGE_DATAFLASH_1
#define SIZE_PAGE_DATAFLASH_MAX         SIZE_PAGE_DATAFLASH_2
#else
#define SIZE_PAGE_DATAFLASH_MAX         SIZE_PAGE_DATAFLASH_1
#endif

#define NUMBER_PAGES_INTO_AR            NUMBER_PAGES_INTO_DATAFLASH_2
#define NUMBER_PAGES_INTO_DR            480
#define NUMBER_PAGES_INTO_PR_ERR        (NUMBER_PAGES_INTO_DATAFLASH_1 - NUMBER_PAGES_INTO_DR)

#define NUMBER_PAGES_IN_ONE_DR_RECORD         6
#define SIZE_BUFFER_FOR_DR_RECORD             (SIZE_PAGE_DATAFLASH_1*NUMBER_PAGES_IN_ONE_DR_RECORD) 
#define MAX_NUMBER_RECORDS_INTO_DR            80
#define MIN_ADDRESS_DR_AREA                   0x0
#define SIZE_DR_AREA                          (NUMBER_PAGES_INTO_DR<<VAGA_SIZE_PAGE_DATAFLASH_1)
#define MAX_ADDRESS_DR_AREA                   (MIN_ADDRESS_DR_AREA + SIZE_DR_AREA - 1)

#define FIRST_INDEX_START_START_RECORD_DR     0
#define FIRST_INDEX_DATA_TIME_DR              1
#define FIRST_INDEX_NAME_OF_CELL_DR           8
#define FIRST_INDEX_SOURCE_DR                 40
#define FIRST_INDEX_NUMBER_ITEMS_DR           77
#define FIRST_INDEX_NUMBER_CHANGES_DR         78
#define FIRST_INDEX_VMP_VALUE                 80
#define FIRST_INDEX_VMP_EQUAL_MORE            84
#define FIRST_INDEX_FIRST_DATA_DR             85

#define NUMBER_BYTES_SAMPLE_DR                ( ( NUMBER_TOTAL_SIGNAL_FOR_RANG / 8 ) + ( ( NUMBER_TOTAL_SIGNAL_FOR_RANG % 8 ) != 0))
#define SD_DR                                 (3 + NUMBER_BYTES_SAMPLE_DR + 2)  

#define VAGA_SIZE_ONE_RECORD_PR_ERR           6
#define SIZE_ONE_RECORD_PR_ERR                (1<<VAGA_SIZE_ONE_RECORD_PR_ERR)
#define NUMBER_RECORDS_PR_ERR_INTO_PAGE       (SIZE_PAGE_DATAFLASH_1>>VAGA_SIZE_ONE_RECORD_PR_ERR) //������� ������ ���������� ���� � ���� �������� ��������� ��������� DataFlash
#define MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER 32 //������������������ ������ � ����� ���� FIFO, �� ������� �� ������ DataFlash
#define SIZE_BUFFER_FOR_PR_ERR                (SIZE_ONE_RECORD_PR_ERR*MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER)
#define MAX_NUMBER_RECORDS_INTO_PR_ERR        (NUMBER_PAGES_INTO_PR_ERR*NUMBER_RECORDS_PR_ERR_INTO_PAGE)
#define MIN_ADDRESS_PR_ERR_AREA               (MAX_ADDRESS_DR_AREA + 1)
#define SIZE_PR_ERR_AREA                      (NUMBER_PAGES_INTO_PR_ERR<<VAGA_SIZE_PAGE_DATAFLASH_1)
#define MAX_ADDRESS_PR_ERR_AREA               (MIN_ADDRESS_PR_ERR_AREA + SIZE_PR_ERR_AREA - 1)

#define MASKA_BIT_FOR_PRESCALER               0x1
#define VAGA_NUMBER_POINT_AR                  (VAGA_NUMBER_POINT - 1)
#define NUMBER_POINT_AR                       (1 << VAGA_NUMBER_POINT_AR)
#define MIN_ADDRESS_AR_AREA                   0x0
#define SIZE_AR_AREA                          (NUMBER_PAGES_INTO_AR<<VAGA_SIZE_PAGE_DATAFLASH_2)
#define MAX_ADDRESS_AR_AREA                   (MIN_ADDRESS_AR_AREA + SIZE_AR_AREA - 1)


#define TRANSACTION_EXECUTING_NONE              0
#define TRANSACTION_EXECUTING                   1
#define TRANSACTION_EXECUTED_WAIT_ANALIZE       2

#define CODE_OPERATION_NONE                                 0
#define CODE_OPERATION_STATUS_READ                          1
#define CODE_OPERATION_PAGESIZE_256                         2
#define CODE_OPERATION_ERASE                                3
#define CODE_OPERATION_WRITE_PAGE_THROUGH_BUFFER            4
#define CODE_OPERATION_READ_HIGH_FREQ                       5
#define CODE_OPERATION_READ_PAGE_INTO_BUFFER                6
#define CODE_OPERATION_WRITE_BUFFER                         7
#define CODE_OPERATION_WRITE_BUFFER_INTO_MEMORY_WITH_ERASE  8

/*���� 0-15 �������� �� ��������� DataFlash ����������� ���������� � ���������� ���������� ����*/
#define TASK_ERASE_DATAFLASH_1_BIT                                          0
#define TASK_ERASE_DATAFLASH_1                                              (1<<TASK_ERASE_DATAFLASH_1_BIT)
#define TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH_BIT                        1
#define TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH                            (1<<TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH_BIT)
#define TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR_BIT        2
#define TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR            (1<<TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU_BIT                          3
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU                              (1<<TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT                      4
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU                          (1<<TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB_BIT                           5
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB                               (1<<TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485_BIT                         6
#define TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485                             (1<<TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT                       7
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB                           (1<<TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT                     8
#define TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485                         (1<<TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485_BIT)

#define  SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2                16

/*���� 16-31 �������� �� ��������� DataFlash ����������� ����������*/
#define TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_FS_BIT   (0 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_FS       (1<<TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_FS_BIT)
#define TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_FS_BIT        (1 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_FS            (1<<TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_FS_BIT)
#define TASK_MAMORY_READ_DATAFLASH_FOR_FS_BIT                               (2 + SEPARATOR_BIT_TASKS_DATADLASH1_AND_TASKS_DATADLASH2)
#define TASK_MAMORY_READ_DATAFLASH_FOR_FS                                   (1<<TASK_MAMORY_READ_DATAFLASH_FOR_FS_BIT)

#define WIGHT_OF_DR_WAITING                       2

#define STATE_DR_NO_RECORD                        0 //�� ����� ������ ���� �� � ���������� ����������� �� ����������
#define STATE_DR_FORCE_START_NEW_RECORD           1 //�������� ��䳿 �������� �� �����, ��� �� �� ��������� ����� ���������� ������ ����������� ���������� ���� ��� ���������� ������ ��������� ����� �����
#define STATE_DR_EXECUTING_RECORD                 2 //��� ������ ������ ����������
#define STATE_DR_MAKE_RECORD                      3 //�������� ����� ���  ������ � Dataflash
#define STATE_DR_CUT_RECORD                       4 //�������� ��䳿 �������� �� �����, ��� �� �� ��������� ����� ���������� ������ ����������� ���������� ���� ��� ���������� ������ ��������� ����� �����

#define MAX_TIME_OFFSET_FROM_START                      0xFFFFFF // 4 ���. 39 ��. 37 ���. 215 �����.
#define MAX_EVENTS_IN_ONE_RECORD                        34

#define LABEL_START_RECORD_DR           0xA5

#define READING_DR_FOR_MENU             1
#define READING_DR_FOR_USB              2
#define READING_DR_FOR_RS485            3
#define READING_PR_ERR_FOR_MENU         4
#define READING_PR_ERR_FOR_USB          5
#define READING_PR_ERR_FOR_RS485        6

#define LABEL_START_RECORD_PR_ERR       0x5A

#define ETAP_NONE                                 0
#define ETAP_READ_MEMORY_INTO_BUFFER              1
#define ETAP_HAVE_READ_MEMORY_INTO_BUFFER         2
#define ETAP_MODIFY_AND_WRITE_BUFFER              3
#define ETAP_MODIFIED_AND_WRITTEN_BUFFER          4
#define ETAP_WRITE_BUFFER_INTO_MEMORY             5
#define ETAP_ERROR_BEFALLEN                       6

#define LABEL_START_RECORD_AR           0xAB

#define NUMBER_WORD_DIGITAL_PART_AR ( ( NUMBER_TOTAL_SIGNAL_FOR_RANG / (8*sizeof(short int)) ) + ( ( NUMBER_TOTAL_SIGNAL_FOR_RANG % (8*sizeof(short int))) != 0))

enum _state_ar_m
{
  STATE_AR_NONE_M = 0,
  STATE_AR_WORK_M,
  STATE_AR_WORK_STOP_M,
  STATE_AR_BLOCK_M
};

enum _state_ar_prt
{
  STATE_AR_NONE_PRT = 0,
  STATE_AR_AVAR_PRT,
  STATE_AR_POSTAVAR_PRT,
  STATE_AR_BLOCK_PRT
};

enum _state_ar_fatfs
{
  STATE_AR_NONE_FATFS = 0,
  STATE_AR_WAIT_TO_WRITE_FATFS,
  STATE_AR_WRITE_FATFS,
  STATE_AR_WAIT_TO_STOP_WRITE_FATFS,
  STATE_AR_STOP_WRITE_FATFS,

  STATE_AR_MEMORY_FULL_FATFS,
  STATE_AR_BLOCK_FATFS
};

enum _level_ar_writing
{
  LEVEL_AR_WRITING_SEL_NUMBER = 0,
  LEVEL_AR_WRITING_OPEN_FILE,
  LEVEL_AR_WRITING_HEADER,
  LEVEL_AR_WRITING_DATA
};

enum _command_fatfs
{
  FATFS_FORMAT = 0,
  
  FATFS_READ_DATA_FOR_MENU,
  
  FATFS_MAX_NUMBER
};

#define MAX_TIME_FULL_AR_RECORD         50000 /*120000*/

/*
� �� ������������ ������ ����, � ���� ������ � ���� 8.3
99 999 999 = 0�5F5 E0FF
��� � ����� ��������� �� 0xFF FFFF (�� ����� 16 777 215)
*/
#define NUMBER_FATFS_NAME       0x1000000       
#define MASKA_FATFS_NAME        (NUMBER_FATFS_NAME - 1)

#define SIZE_BUFFER_FOR_AR   (250263)

#define CLEAN_AR_BIT          0
#define CLEAN_AR              (1 << CLEAN_AR_BIT)
#define CLEAN_DR_BIT          1
#define CLEAN_DR              (1 << CLEAN_DR_BIT)
#define CLEAN_PR_ERR_BIT      2
#define CLEAN_PR_ERR          (1 << CLEAN_PR_ERR_BIT)

#endif
