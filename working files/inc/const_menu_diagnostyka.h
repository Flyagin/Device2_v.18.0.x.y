#ifndef __CONST_MENU_DIAGNOSTYKA__
#define __CONST_MENU_DIAGNOSTYKA__

#define EKRAN_DIAGNOSTYKA                    (EKRAN_POINT_TIME_RANGUVANNJA + 1)

#define MAX_ROW_FOR_DIAGNOSTYKA              (8*(4 + 4 + 4))  /*2 ����� ���� unsigned int + �� ���� ����� ��� � ����� ����. ��� ����� ������ ������ ���������� ���������� ���� �� ��� ������ 32 �����. � ���� ����� - �� ������*/  
#define N_DIAGN                              ((MAX_ROW_FOR_DIAGNOSTYKA >> 5) + ((MAX_ROW_FOR_DIAGNOSTYKA & 0x1f) != 0))
#define N_DIAGN_BYTES                        ((MAX_ROW_FOR_DIAGNOSTYKA >> 3) + ((MAX_ROW_FOR_DIAGNOSTYKA & 0x07) != 0))

//#define USED_BITS_IN_LAST_INDEX  0x00ffffff  

enum _error_id 
{
ERROR_START_VIA_I2C_BIT = 0,
ERROR_SETTINGS_EEPROM_BIT,
ERROR_SETTINGS_EEPROM_EMPTY_BIT,
ERROR_SETTINGS_EEPROM_COMPARISON_BIT,
ERROR_SETTINGS_EEPROM_CONTROL_BIT,
ERROR_SETTINGS_EEPROM_DEVICE_ID_FAIL_BIT,
ERROR_USTUVANNJA_EEPROM_BIT,
ERROR_USTUVANNJA_EEPROM_EMPTY_BIT,
ERROR_USTUVANNJA_EEPROM_COMPARISON_BIT,
ERROR_USTUVANNJA_EEPROM_CONTROL_BIT,
ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT,
ERROR_STATE_LEDS_EEPROM_BIT,
ERROR_STATE_OUTPUTS_EEPROM_BIT,
ERROR_STATE_LEDS_OUTPUTS_EEPROM_EMPTY_BIT,
ERROR_STATE_LEDS_OUTPUTS_EEPROM_COMPARISON_BIT,
ERROR_TRG_FUNC_EEPROM_BIT,
ERROR_TRG_FUNC_EEPROM_EMPTY_BIT,
ERROR_TRG_FUNC_EEPROM_COMPARISON_BIT,
ERROR_TRG_FUNC_EEPROM_CONTROL_BIT,
ERROR_INFO_REJESTRATOR_AR_EEPROM_BIT,
ERROR_INFO_REJESTRATOR_AR_EEPROM_EMPTY_BIT,
ERROR_INFO_REJESTRATOR_AR_COMPARISON_BIT,
ERROR_INFO_REJESTRATOR_AR_CONTROL_BIT,
ERROR_INFO_REJESTRATOR_DR_EEPROM_BIT,
ERROR_INFO_REJESTRATOR_DR_EEPROM_EMPTY_BIT,
ERROR_INFO_REJESTRATOR_DR_COMPARISON_BIT,
ERROR_INFO_REJESTRATOR_DR_CONTROL_BIT,
ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT,
ERROR_INFO_REJESTRATOR_PR_ERR_EEPROM_EMPTY_BIT,
ERROR_INFO_REJESTRATOR_PR_ERR_COMPARISON_BIT,
ERROR_INFO_REJESTRATOR_PR_ERR_CONTROL_BIT,
ERROR_RESURS_EEPROM_BIT,
ERROR_RESURS_EEPROM_EMPTY_BIT,
ERROR_RESURS_EEPROM_COMPARISON_BIT,
ERROR_RESURS_EEPROM_CONTROL_BIT,
ERROR_ENERGY_EEPROM_BIT,
ERROR_ENERGY_EEPROM_EMPTY_BIT,
ERROR_ENERGY_EEPROM_COMPARISON_BIT,

RTC_BATTERY_LOW_BIT,
RTC_OSCILLATOR_STOPED_BIT,
RTC_OSCILLATOR_FAIL_BIT,
RTC_UPDATING_HALTED_BIT,
RTC_WORK_FIELD_NOT_SET_BIT,

ERROR_VREF_ADC_TEST_BIT,

ERROR_SPI_ADC_BIT,

ERROR_OSCYLOJRAPH_OVERFLOW,

ERROR_DIGITAL_OUTPUT_1_BIT,

ERROR_AR_TEMPORARY_BUSY_BIT = ERROR_DIGITAL_OUTPUT_1_BIT + 16,
ERROR_AR_OVERLOAD_BUFFER_BIT,
ERROR_AR_MEMORY_FULL_BIT,
ERROR_AR_UNDEFINED_BIT,

ERROR_DR_TEMPORARY_BUSY_BIT,
ERROR_DR_UNDEFINED_BIT,
ERROR_DR_LOSS_INFORMATION_BIT,

ERROR_PR_ERR_OVERLOAD_BIT,
ERROR_PR_ERR_LOSS_INFORMATION_BIT,

EVENT_START_SYSTEM_BIT,
EVENT_RESTART_SYSTEM_BIT,
EVENT_SOFT_RESTART_SYSTEM_BIT,
EVENT_STOP_SYSTEM_BIT,
EVENT_DROP_POWER_BIT,

ERROR_LCD_BIT,
ERROR_SPI_EDF_BIT,
ERROR_EXTERNAL_SRAM_BIT,
ERROR_INTERNAL_FLASH_BIT,

ERROR_SELECT_GRUPY_USRAVOK,

LOSE_ENERGY_DATA,

TEST_OVD1,
TEST_OVD2,
TEST_OVD3,

ERROR_BA_1_FIX,
ERROR_BA_1_CTLR,
ERROR_BDVV5_1_FIX,
ERROR_BDVV5_1_CTLR,
ERROR_BDVV5_2_FIX,
ERROR_BDVV5_2_CTLR,
ERROR_BDV_DZ_FIX,
ERROR_BDV_DZ_CTLR,
ERROR_BDZ_FIX,
ERROR_BDZ_CTLR,

ERROR_FATFS
};

#define MASKA_AVAR_ERROR_0        (unsigned int)(               \
    (1 << (ERROR_SETTINGS_EEPROM_BIT))                          \
  | (1 << (ERROR_SETTINGS_EEPROM_EMPTY_BIT))                    \
  | (1 << (ERROR_SETTINGS_EEPROM_COMPARISON_BIT) )              \
  | (1 << (ERROR_SETTINGS_EEPROM_CONTROL_BIT))                  \
  | (1 << (ERROR_USTUVANNJA_EEPROM_BIT) )                       \
  | (1 << (ERROR_USTUVANNJA_EEPROM_EMPTY_BIT))                  \
  | (1 << (ERROR_USTUVANNJA_EEPROM_COMPARISON_BIT))             \
  | (1 << (ERROR_USTUVANNJA_EEPROM_CONTROL_BIT))                \
  | (1 << (ERROR_USTUVANNJA_EEPROM_ADJUSTMENT_ID_FAIL_BIT))     \
  | (1 << (ERROR_TRG_FUNC_EEPROM_BIT))                          \
  | (1 << (ERROR_TRG_FUNC_EEPROM_EMPTY_BIT))                    \
  | (1 << (ERROR_TRG_FUNC_EEPROM_COMPARISON_BIT))               \
  | (1 << (ERROR_TRG_FUNC_EEPROM_CONTROL_BIT))                  \
)

#define MASKA_AVAR_ERROR_1        (unsigned int)(               \
    (1 << (ERROR_VREF_ADC_TEST_BIT - 32))                       \
  | (1 << (ERROR_SPI_ADC_BIT - 32))                             \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT +  0 - 32))               \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT +  1 - 32))               \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT +  2 - 32))               \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT +  3 - 32))               \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT +  4 - 32))               \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT +  5 - 32))               \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT +  6 - 32))               \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT +  7 - 32))               \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT +  8 - 32))               \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT +  9 - 32))               \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT + 10 - 32))               \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT + 11 - 32))               \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT + 12 - 32))               \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT + 13 - 32))               \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT + 14 - 32))               \
  | (1 << (ERROR_DIGITAL_OUTPUT_1_BIT + 15 - 32))               \
)

#define MASKA_AVAR_ERROR_2        (unsigned int)(               \
    (1 << (ERROR_INTERNAL_FLASH_BIT - 64))                      \
  | (1 << (ERROR_BA_1_FIX - 64))                                \
  | (1 << (ERROR_BA_1_CTLR - 64))                               \
  | (1 << (ERROR_BDVV5_1_FIX - 64))                             \
  | (1 << (ERROR_BDVV5_1_CTLR - 64))                            \
  | (1 << (ERROR_BDVV5_2_FIX - 64))                             \
  | (1 << (ERROR_BDVV5_2_CTLR - 64))                            \
  | (1 << (ERROR_BDV_DZ_FIX - 64))                              \
  | (1 << (ERROR_BDV_DZ_CTLR - 64))                             \
  | (1 << (ERROR_BDZ_FIX - 64))                                 \
  | (1 << (ERROR_BDZ_CTLR - 64))                                \
)

# define NAME_DIAGN_RU  \
  " ��.I2C         ",   \
  " ��.��������    ",   \
  " �������� ���   ",   \
  " ��.���.�����.  ",   \
  " ��.�����.�����.",   \
  " ��.���� �����. ",   \
  " ��.����������� ",   \
  " ����������� ���",   \
  " ��.���.�����.  ",   \
  " ��.�����.�����.",   \
  " ��.�����.������",   \
  " ��.��c��.��.�� ",   \
  " ��.��c��.�.��� ",   \
  "���.���./��.��� ",   \
  " ��.���.���./��.",   \
  "  ��.����.���.  ",   \
  "  ����.���.���  ",   \
  "��.���.����.���.",   \
  "��.�����.����.�.",   \
  " ��.���.��.���. ",   \
  " ���.��.���.��� ",   \
  "��.���.�.��.���.",   \
  "��.�����.��.���.",   \
  " ��.���.�.���.  ",   \
  " ���.�.���.���  ",   \
  " ��.���.�.�.���.",   \
  " ��.�����.�.���.",   \
  "��.���.���.��.�.",   \
  "���.���.��.�.���",   \
  "��.���.�.�.��.�.",   \
  "��.�����.�.��.�.",   \
  " ��.���.��.���. ",   \
  " ���.��.���.��� ",   \
  " ��.���.��.���. ",   \
  "��.�����.��.���.",   \
  " ��.�.�.������� ",   \
  "  ������� ���   ",   \
  " ��.���.������� ",   \
  " ������� ������.",   \
  "��������� �����.",   \
  "����� ����������",   \
  " ���.������.RTC ",   \
  " �� ���.���� RTC",   \
  " ���� VREF ���  ",   \
  " ��. SPI ���    ",   \
  "�����.���.�.���.",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  "��.���.��.�����.",   \
  " ���.���.a�.���.",   \
  " �.a�.���.���.  ",   \
  "�����.��.��.���.",   \
  " �.���.��.�����.",   \
  " �����.��.�.���.",   \
  " ������ �.�.���.",   \
  "�����.���.��.��.",   \
  " ������ �.��.��.",   \
  " ����� ����.    ",   \
  " ������� ����.  ",   \
  "��.������� ����.",   \
  " �������.����.  ",   \
  " ������.������� ",   \
  " ����� ���      ",   \
  " ��.SPI_EDF     ",   \
  " ��.������� SRAM",   \
  " ��.�����.FLASH ",   \
  " ��.���.��.���. ",   \
  " ���.�.�������  ",   \
  " ���� ���1      ",   \
  " ���� ���2      ",   \
  " ���� ���3      ",   \
  " ��1 �.         ",   \
  " ��1 �.         ",   \
  " ����5_1 �.     ",   \
  " ����5_1 �.     ",   \
  " ����5_2 �.     ",   \
  " ����5_2 �.     ",   \
  " ���-�� �.      ",   \
  " ���-�� �.      ",   \
  " ��� �.         ",   \
  " ��� �.         ",   \
  " ��.�.�.        "

# define NAME_DIAGN_UA  \
  " ���.I2C        ",   \
  " ���.�����������",   \
  "����������� ����",   \
  " ���.���.������.",   \
  "���.�����.������",   \
  " ���.���� ������",   \
  " ���.���������  ",   \
  " ��������� ���� ",   \
  " ���.���.���.   ",   \
  " ���.�����.���. ",   \
  " ���.���.������ ",   \
  " ���.���.��.��.",   \
  " ���.���.�.���.",   \
  "���.���./��.����",   \
  "���.���.���./��.",   \
  " ���.���.���.  ",   \
  " ���.���.����  ",   \
  " ���.���.���.�.",   \
  "���.�����.���.�",   \
  " ���.���.��.�.  ",   \
  " ���.��.�.����  ",   \
  " ���.���.�.��.�.",   \
  " ���.�����.��.�.",   \
  " ���.���.�.�.   ",   \
  " ���.�.�.����   ",   \
  " ���.���.�.�.�. ",   \
  " ���.�����.�.�. ",   \
  " ���.���.�.��.�.",   \
  " ���.�.��.�.����",   \
  "���.���.�.�.��.�",   \
  "���.�����.�.��.�",   \
  " ���.���.��.�. ",   \
  " ���.��.�.���� ",   \
  " ���.���.��.�. ",   \
  "���.�����.��.�.",   \
  " ���.�.�.������",   \
  "  ������ ����  ",   \
  " ���.���.������",   \
  "������� �������.",   \
  " ��������� ���. ",   \
  " ³��.����������",   \
  " ���.������.RTC ",   \
  " �� ���.���� RTC",   \
  " ���� VREF ���  ",   \
  " ���.SPI ���    ",   \
  "�����.���.�.���.",   \
  " ���.���.����?.?",   \
  " ���.���.����?.?",   \
  " ���.���.����?.?",   \
  " ���.���.����?.?",   \
  " ���.���.����?.?",   \
  " ���.���.����?.?",   \
  " ���.���.����?.?",   \
  " ���.���.����?.?",   \
  " ���.���.����?.?",   \
  " ���.���.����?.?",   \
  " ���.���.����?.?",   \
  " ���.���.����?.?",   \
  " ���.���.����?.?",   \
  " ���.���.����?.?",   \
  " ���.���.����?.?",   \
  " ���.���.����?.?",   \
  "��.�.����.������",   \
  " �����.���.a�.�.",   \
  " �.a�.���.���.  ",   \
  "������.���.��.�.",   \
  "�.�.����.������.",   \
  " ������.���.�.�.",   \
  " ������ �.�.�.  ",   \
  "�����.���.�.��.�",   \
  " ������ �.�.��.�",   \
  " ����� ������.  ",   \
  " ������� ������.",   \
  " ��.������� ��. ",   \
  " ���.������.    ",   \
  " ������.��������",   \
  " ³����� �ʲ    ",   \
  " ���.SPI_EDF    ",   \
  " ���.����.SRAM  ",   \
  " ���.�����.FLASH",   \
  " ���.���.��.���.",   \
  " ���.�.����㳿  ",   \
  " ���� ���1      ",   \
  " ���� ���2      ",   \
  " ���� ���3      ",   \
  " ��1 �.         ",   \
  " ��1 �.         ",   \
  " ����5_1 �.     ",   \
  " ����5_1 �.     ",   \
  " ����5_2 �.     ",   \
  " ����5_2 �.     ",   \
  " ���-�� �.      ",   \
  " ���-�� �.      ",   \
  " ��� �.         ",   \
  " ��� �.         ",   \
  " ���.�.�.       "

# define NAME_DIAGN_EN  \
  " I2C Err.       ",   \
  " Settings Err.  ",   \
  " No settings    ",   \
  " Sett.W.Err.    ",   \
  " Sett.Ctrl.Err. ",   \
  " Sett.Type Err. ",   \
  " Adjust Err.    ",   \
  " No adjust      ",   \
  " Adjust W.Err.  ",   \
  "Adjust Ctrl.Err.",   \
  " Adjust-Set Err.",   \
  "Tr.LED Rest Err.",   \
  "Sign DO Rest Err",   \
  " No DO/LED Inf. ",   \
  " DO/LED W Err.  ",   \
  "  ��.����.���.  ",   \
  "  ����.���.���  ",   \
  "��.���.����.���.",   \
  "��.�����.����.�.",   \
  " An.Rec.Inf.Err.",   \
  " No An.Rec.Inf. ",   \
  "An.Rec.Inf.W.Err",   \
  "An.Rec.Ctrl.Err.",   \
  " D.Rec.Inf.Err. ",   \
  " No D.Rec.Inf.  ",   \
  "Inf.D.Rec.W.Err.",   \
  " D.Rec.Ctrl.Err.",   \
  " PER Inf.Err.   ",   \
  " No Inf.of PER  ",   \
  "Inf.W.Err.of PER",   \
  " PER Ctrl.Err.  ",   \
  " Res.C.Inf.Err. ",   \
  " No Res.C.Inf.  ",   \
  "Inf.Res.C.W.Err.",   \
  " Res.C.Ctrl.Err.",   \
  " ��.�.�.������� ",   \
  "  ������� ���   ",   \
  " ��.���.������� ",   \
  " RTC:Battery low",   \
  " RTC:Osc.stop   ",   \
  " RTC:Osc.fail   ",   \
  " RTC:Halt update",   \
  "RTC:No def.sett.",   \
  " ADC:VREF fail  ",   \
  " ADC SPI Err.   ",   \
  "�����.���.�.���.",   \
  " DO?.? Ctrl.Err.",   \
  " DO?.? Ctrl.Err.",   \
  " DO?.? Ctrl.Err.",   \
  " DO?.? Ctrl.Err.",   \
  " DO?.? Ctrl.Err.",   \
  " DO?.? Ctrl.Err.",   \
  " DO?.? Ctrl.Err.",   \
  " DO?.? Ctrl.Err.",   \
  " DO?.? Ctrl.Err.",   \
  " DO?.? Ctrl.Err.",   \
  " DO?.? Ctrl.Err.",   \
  " DO?.? Ctrl.Err.",   \
  " DO?.? Ctrl.Err.",   \
  " DO?.? Ctrl.Err.",   \
  " DO?.? Ctrl.Err.",   \
  " DO?.? Ctrl.Err.",   \
  " An.Rec.busy    ",   \
  " An.Rec.buff.OVF",   \
  " Mem.An.Rec.Full",   \
  "Undef.An.Rec.Err",   \
  " D.Rec.busy     ",   \
  "Undef.D.Rec.Err.",   \
  " D.Rec.Data lost",   \
  "OVF of PER buff.",   \
  " PER Data lost  ",   \
  " Device Start   ",   \
  " Device Restart ",   \
  " Device SFTRST  ",   \
  " Device Stop    ",   \
  " ������.������� ",   \
  " LCD Fail       ",   \
  " EDF SPI Err.   ",   \
  " Ext.SRAM Err.  ",   \
  " Int.FLASH Err. ",   \
  " ��.���.��.���. ",   \
  " ���.�.�������  ",   \
  " Test ���1      ",   \
  " Test ���2      ",   \
  " Test ���3      ",   \
  " BA1 f.         ",   \
  " BA1 ctrl.      ",   \
  " BDVV5_1 f.     ",   \
  " BDVV5_1 ctrl.  ",   \
  " BDVV5_2 f.     ",   \
  " BDVV5_2 ctrl.  ",   \
  " BDV-DZ f.      ",   \
  " BDV-DZ ctrl.   ",   \
  " BDZ f.         ",   \
  " BDZ ctrl.      ",   \
  " Error FS       "

# define NAME_DIAGN_KZ  \
  " ��.I2C         ",   \
  " ��.��������    ",   \
  " �������� ���   ",   \
  " ��.���.�����.  ",   \
  " ��.�����.�����.",   \
  " ��.���� �����. ",   \
  " ��.����������� ",   \
  " ����������� ���",   \
  " ��.���.�����.  ",   \
  " ��.�����.�����.",   \
  " ��.�����.������",   \
  " ��.��c��.��.�� ",   \
  " ��.��c��.�.��� ",   \
  "���.���./��.��� ",   \
  " ��.���.���./��.",   \
  "  ��.����.���.  ",   \
  "  ����.���.���  ",   \
  "��.���.����.���.",   \
  "��.�����.����.�.",   \
  " ��.���.��.���. ",   \
  " ���.��.���.��� ",   \
  "��.���.�.��.���.",   \
  "��.�����.��.���.",   \
  " ��.���.�.���.  ",   \
  " ���.�.���.���  ",   \
  " ��.���.�.�.���.",   \
  " ��.�����.�.���.",   \
  "��.���.���.��.�.",   \
  "���.���.��.�.���",   \
  "��.���.�.�.��.�.",   \
  "��.�����.�.��.�.",   \
  " ��.���.��.���. ",   \
  " ���.��.���.��� ",   \
  " ��.���.��.���. ",   \
  "��.�����.��.���.",   \
  " ��.�.�.������� ",   \
  "  ������� ���   ",   \
  " ��.���.������� ",   \
  " ������� ������.",   \
  "��������� �����.",   \
  "����� ����������",   \
  " ���.������.RTC ",   \
  " �� ���.���� RTC",   \
  " ���� VREF ���  ",   \
  " ��.SPI ���     ",   \
  "�����.���.�.���.",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  " ��.���.���� ?.?",   \
  "��.���.��.�����.",   \
  " ���.���.a�.���.",   \
  " �.a�.���.���.  ",   \
  "�����.��.��.���.",   \
  " �.���.��.�����.",   \
  " �����.��.�.���.",   \
  " ������ �.�.���.",   \
  "�����.���.��.��.",   \
  " ������ �.��.��.",   \
  " ����� ����.    ",   \
  " ������� ����.  ",   \
  "��.������� ����.",   \
  " �������.����.  ",   \
  " ������.������� ",   \
  " ����� ���      ",   \
  " ��.SPI_EDF     ",   \
  " ��.������� SRAM",   \
  " ��.�����.FLASH ",   \
  " ��.���.��.���. ",   \
  " ���.�.�������  ",   \
  " ���� ���1      ",   \
  " ���� ���2      ",   \
  " ���� ���3      ",   \
  " ��1 �.         ",   \
  " ��1 �.         ",   \
  " ����5_1 �.     ",   \
  " ����5_1 �.     ",   \
  " ����5_2 �.     ",   \
  " ����5_2 �.     ",   \
  " ���-�� �.      ",   \
  " ���-�� �.      ",   \
  " ��� �.         ",   \
  " ��� �.         ",   \
  " ��.�.�.        "
    
#endif
