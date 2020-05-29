#ifndef __EXTERNAL_VARIABLES_H
#define __EXTERNAL_VARIABLES_H

extern unsigned int semaphore_adc_irq;
extern unsigned int adc_DATA_VAL_read;
//extern unsigned int adc_TEST_VAL_read;
extern unsigned int status_adc_read_work;
extern const unsigned int input_adc[NUMBER_INPUTs_ADCs][2];
extern EXTENDED_OUTPUT_DATA output_adc[NUMBER_INPUTs_ADCs];
extern ROZSHYRENA_VYBORKA rozshyrena_vyborka;

extern unsigned int command_word_adc, command_word_adc_work, active_index_command_word_adc;
extern unsigned int state_reading_ADCs;
extern unsigned int channel_request, channel_answer;

extern uint32_t step_timer_adc;
extern uint32_t penultimate_tick_DATA_VAL, previous_tick_DATA_VAL;

extern DATA_FOR_OSCYLOGRAPH data_for_oscylograph[MAX_INDEX_DATA_FOR_OSCYLOGRAPH];
extern unsigned int head_data_for_oscylograph;
extern unsigned int tail_data_for_oscylograph, DATA_VAL_tail_data_for_oscylograph;

extern VYBORKA_XY perechid_cherez_nul[MAX_INDEX_PhK][2];
extern unsigned int fix_perechid_cherez_nul[MAX_INDEX_PhK];
extern POPEREDNJY_PERECHID poperednij_perechid;

extern unsigned int maska_canaliv_fapch;
extern float frequency, frequency_work;
extern unsigned int tick_period, tick_period_work;
extern unsigned int tick_c, tick_c_work;

extern float frequency_min, frequency_max;
extern unsigned int command_restart_monitoring_frequency;

extern unsigned int vref_adc_averange_sum[NUMBER_ANALOG_CANALES];
extern uint32_t vref_adc_averange_sum_1s[NUMBER_ANALOG_CANALES];
extern uint32_t vref_adc_moment_value_1s[NUMBER_ANALOG_CANALES][MAIN_FREQUENCY];
extern uint32_t vref_adc[NUMBER_ANALOG_CANALES];

extern unsigned int index_array_of_one_value_fourier;

extern EXTENDED_SAMPLE ADCs_data_raw[NUMBER_ANALOG_CANALES];
extern int ADCs_data[NUMBER_ANALOG_CANALES];
//extern int current_data[NUMBER_ANALOG_CANALES*NUMBER_POINT*NUMBER_PERIOD_TRANSMIT];
extern unsigned long long sqr_current_data_3I0[NUMBER_POINT];
extern unsigned int index_array_of_current_data_value;

extern unsigned int changed_ustuvannja; 
extern unsigned char crc_ustuvannja;
extern unsigned int ustuvannja_meas[NUMBER_ANALOG_CANALES], ustuvannja[NUMBER_ANALOG_CANALES], edit_ustuvannja[NUMBER_ANALOG_CANALES];
extern int phi_ustuvannja_meas[NUMBER_ANALOG_CANALES], phi_ustuvannja[NUMBER_ANALOG_CANALES], phi_edit_ustuvannja[NUMBER_ANALOG_CANALES];
extern float phi_ustuvannja_sin_cos_meas[2*NUMBER_ANALOG_CANALES], phi_ustuvannja_sin_cos[2*NUMBER_ANALOG_CANALES], phi_edit_ustuvannja_sin_cos[2*NUMBER_ANALOG_CANALES];

extern const float sin_data_f[NUMBER_POINT];
extern const float cos_data_f[NUMBER_POINT];
extern unsigned int index_sin_cos_array;
extern unsigned int index_data_sin_cos_array;
extern int data_sin[NUMBER_POINT*NUMBER_ANALOG_CANALES];
extern int data_cos[NUMBER_POINT*NUMBER_ANALOG_CANALES];
extern unsigned int index_data_sin_and_cos_array;
extern int ortogonal_irq[2*NUMBER_ANALOG_CANALES];
extern int ortogonal[2*NUMBER_ANALOG_CANALES][2];
extern unsigned long long sum_sqr_data_3I0_irq;
extern unsigned long long sum_sqr_data_3I0[2];
//extern unsigned int semaphore_measure_values;
extern unsigned int semaphore_measure_values_low;
extern unsigned int bank_ortogonal;

extern unsigned int semaphore_measure_values_low1;

extern unsigned int number_inputs_for_fix_one_second;
extern unsigned int number_inputs_for_fix_one_period;
extern unsigned int measurement[_NUMBER_IM];
extern unsigned int measurement_high[2][_NUMBER_IM], bank_measurement_high;
extern unsigned int measurement_middle[_NUMBER_IM]; 
extern unsigned int measurement_low[_NUMBER_IM]; 

extern const unsigned int index_converter[NUMBER_ANALOG_CANALES];
extern int ortogonal_calc[2*FULL_ORT_MAX];
extern int ortogonal_calc_low[2*FULL_ORT_MAX];
extern int phi_angle[2][FULL_ORT_MAX];
extern uint32_t bank_for_calc_phi_angle, state_calc_phi_angle;
extern int base_index_for_angle;

extern int P_plus[2];
extern int P_minus[2];
extern int Q_1q[2];
extern int Q_2q[2];
extern int Q_3q[2];
extern int Q_4q[2];
extern unsigned int lichylnyk_1s_po_20ms;
extern unsigned int bank_for_enegry;
extern int P[2], Q[2], cos_phi_x1000[2];
extern unsigned int S[2];
extern uint32_t bank_for_calc_power, state_calc_power;
extern double energy[2][MAX_NUMBER_INDEXES_ENERGY];
extern uint32_t state_calc_energy;
extern unsigned int clean_energy;
extern unsigned int information_about_clean_energy;

extern int resistance[MAX_NUMBER_INDEXES_RESISTANCE_FULL];
extern int resistance_middle[MAX_NUMBER_INDEXES_RESISTANCE];
extern int resistance_low[MAX_NUMBER_INDEXES_RESISTANCE];

extern int sector_1_mtz_tznp[8];
extern int sector_2_mtz_tznp[8];

//����������� "�������" ������� ���������� � "�����"
extern const uint32_t small_big_rang[NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL];

//���������� ���
extern unsigned int sector_directional_mtz[4][3];
extern unsigned int Uxy_bilshe_porogu[3];
extern unsigned int Ix_bilshe_porogu[3];
extern unsigned int temp_states_for_mtz;

//���
#if (                                   \
     (MODYFIKACIA_VERSII_PZ == 0) ||    \
     (MODYFIKACIA_VERSII_PZ == 3)       \
    )   
extern uint32_t delta_time_test;
extern uint32_t zdz_ovd_diagnostyka;
#endif

//���
extern int sector_1[8];
extern int sector_2[8];
extern unsigned int sector_i_minus_u_1;
extern unsigned int sector_i_minus_u_2;
extern unsigned int po_3I0;
extern unsigned int po_3U0;
extern unsigned int sector_NZZ;
extern unsigned int Nzz_3U0_bilshe_porogu, Nzz_3I0_bilshe_porogu;

//����
extern unsigned int TZNP_3U0_bilshe_porogu;
extern unsigned int TZNP_3I0_r_bilshe_porogu;
extern unsigned int sector_directional_tznp[3];

extern int32_t sector_directional_dz[4 - 1][3];
extern unsigned int Uxy_bilshe_porogu_dz[3];
extern unsigned int Ix_bilshe_porogu_dz[3];

extern unsigned int i1_bilshe_porogu, i2_bilshe_porogu;

extern uint32_t TIM_PRT_write_tick;

//��������������
extern unsigned int state_leds;
extern unsigned int state_trigger_leds;
extern uint32_t state_leds_Fx[2];
extern uint32_t state_leds_ctrl;

extern unsigned int state_inputs;
extern unsigned int active_inputs;
extern unsigned int state_outputs;
extern unsigned int state_outputs_raw;
extern unsigned int state_signal_outputs;
extern unsigned int active_functions[N_BIG];
extern unsigned int trigger_active_functions[N_BIG], trigger_active_functions_ctrl[N_BIG];
extern unsigned char crc_trg_func, crc_trg_func_ctrl;
extern unsigned int trigger_functions_USB[N_BIG];
extern unsigned int trigger_functions_RS485[N_BIG];
extern unsigned int copying_active_functions;
extern unsigned int active_functions_copy[N_BIG];
extern unsigned int active_functions_trg[N_BIG];
extern unsigned int mutex_buttons;
extern unsigned int pressed_buttons;
extern unsigned int fix_active_buttons, fix_active_buttons_ctrl;
extern unsigned int mutex_interface;
extern unsigned int activation_function_from_interface[N_SMALL];
extern unsigned int reset_trigger_function_from_interface;
extern unsigned int diagnostyka_before[N_DIAGN];
extern volatile unsigned int diagnostyka[N_DIAGN];
extern unsigned int set_diagnostyka[N_DIAGN];
extern unsigned int clear_diagnostyka[N_DIAGN];

extern uint32_t board_register;

extern int global_timers[MAX_NUMBER_GLOBAL_TIMERS];
extern unsigned int timer_prt_signal_output_mode_2;
extern unsigned int output_timer_prt_signal_output_mode_2;
extern unsigned int static_logic_df;

extern unsigned int previous_states_APV_0;
extern unsigned int trigger_APV_0;

extern _Bool previous_state_po_achr_chapv_uaf1;
extern _Bool previous_state_po_achr_chapv_ubf1;
extern _Bool previous_state_po_achr_chapv_ucf1;
extern _Bool previous_states_CHAPV1;
extern _Bool previous_states_CHAPV2;
extern _Bool trigger_CHAPV1;
extern _Bool trigger_CHAPV2;

extern _Bool previous_states_ready_tu;
extern _Bool trigger_ready_tu;

extern unsigned int start_restart;

extern unsigned char working_ekran[MAX_ROW_LCD][MAX_COL_LCD];
extern unsigned int rewrite_ekran_once_more;

extern volatile unsigned int new_state_keyboard;
extern unsigned int new_state_keyboard_for_db;
extern unsigned char time_set_keyboard[NUMBER_KEY_KEYBOARD];

extern unsigned int time_rewrite;
extern unsigned int reinit_LCD;

extern __CURRENT_EKRAN current_ekran;
extern int position_in_current_level_menu[MAX_LEVEL_MENU];
extern int previous_level_in_current_level_menu[MAX_LEVEL_MENU];
extern const uint32_t buttons_mode[NUMBER_BUTTON_MODE][N_SMALL];
extern const uint32_t output_boards[N_OUTPUT_BOARDS][2];
extern const uint32_t input_boards[N_INPUT_BOARDS][2];

extern unsigned int periodical_tasks_TEST_SETTINGS;
extern unsigned int periodical_tasks_TEST_USTUVANNJA;
extern unsigned int periodical_tasks_TEST_TRG_FUNC;
extern unsigned int periodical_tasks_TEST_TRG_FUNC_LOCK;
extern unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_AR;
extern unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_AR_LOCK;
extern unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_DR;
extern unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_DR_LOCK;
extern unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR;
extern unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR_LOCK;
extern unsigned int periodical_tasks_TEST_RESURS;
extern unsigned int periodical_tasks_TEST_RESURS_LOCK;
extern unsigned int periodical_tasks_TEST_FLASH_MEMORY;
extern unsigned int periodical_tasks_CALCULATION_ANGLE;
extern unsigned int periodical_tasks_CALC_ENERGY_DATA;

extern const unsigned char odynyci_vymirjuvannja[MAX_NAMBER_LANGUAGE][NUMBER_ODYNYCI_VYMIRJUVANNJA];

extern const unsigned int size_dimension_array[MAX_NAMBER_LANGUAGE];
extern const unsigned char resistance_dimension[MAX_NAMBER_LANGUAGE][SIZE_R_DIMENSION];


extern const uint32_t max_value_for_tf[1 + TOTAL_NUMBER_PROTECTION][MAX_ROW_LIST_SOURCE_TF];

extern unsigned int fixed_power_down_into_RTC; 
extern unsigned char time[7]; 
extern unsigned char time_copy[7]; 
extern unsigned char calibration;
extern unsigned char calibration_copy;
extern unsigned int copying_time;
extern unsigned char time_edit[7]; 
extern unsigned char calibration_edit;
extern unsigned int copy_register8_RTC;
extern int etap_reset_of_bit;
extern int etap_settings_test_frequency;
extern unsigned char temp_register_rtc[2];

extern unsigned int changed_settings; 
extern unsigned char crc_settings;
extern __SETTINGS current_settings_prt, current_settings;
extern __SETTINGS edition_settings, current_settings_interfaces;
extern int * type_mtz_arr[NUMBER_LEVEL_MTZ];
extern unsigned int mtz_settings_prt[NUMBER_LEVEL_MTZ][MTZ_SETTINGS_LENGTH];
extern unsigned int mtz_tmr_const[NUMBER_LEVEL_MTZ][NUMBER_LEVEL_TMR_CONST];
extern unsigned int mtz_const_menu_settings_prt[NUMBER_LEVEL_MTZ][MTZ_CONST_MENU_SETTINGS_LENGTH];
extern unsigned int const i_nom_const;
extern unsigned int const u_f_nom_const;
extern unsigned int * setpoint_mtz[NUMBER_LEVEL_MTZ];
extern unsigned int * setpoint_mtz_n_vpered[NUMBER_LEVEL_MTZ];
extern unsigned int * setpoint_mtz_n_nazad[NUMBER_LEVEL_MTZ];
extern unsigned int * setpoint_mtz_U[NUMBER_LEVEL_MTZ];
extern unsigned int * setpoint_mtz_po_napruzi[NUMBER_LEVEL_MTZ];
extern int * timeout_mtz[NUMBER_LEVEL_MTZ];
extern int * timeout_mtz_n_vpered[NUMBER_LEVEL_MTZ];
extern int * timeout_mtz_n_nazad[NUMBER_LEVEL_MTZ];
extern int * timeout_mtz_po_napruzi[NUMBER_LEVEL_MTZ];
extern _Bool previous_state_mtz_po_incn;
extern _Bool previous_state_mtz_po_uncn;
extern unsigned int p_global_trigger_state_mtz2;

//���������� ������ � ������� � �����
extern unsigned int number_seconds;
extern unsigned int number_minutes;

//���� ��� ��������� ������� ���������-��������
extern unsigned int restart_resurs_count;
extern unsigned int resurs_temp;
extern unsigned int resurs_global;
extern unsigned int resurs_global_min;
extern unsigned int resurs_global_max;

extern unsigned int restart_timing_watchdog;
extern unsigned int time_1_watchdog_input;
extern unsigned int time_2_watchdog_input;
extern unsigned int time_delta_watchdog_input;
extern unsigned int time_delta_watchdog_input_min;
extern unsigned int time_delta_watchdog_input_max;

extern unsigned int time_1_watchdog_output;
extern unsigned int time_2_watchdog_output;
extern unsigned int time_delta_watchdog_output;
extern unsigned int time_delta_watchdog_output_min;
extern unsigned int time_delta_watchdog_output_max;

extern unsigned char Temporaty_I2C_Buffer[MAX_NUMBER_REGISTERS_RTC + 2];
extern unsigned int number_busy_state;
extern unsigned int type_error_of_exchanging_via_i2c;
//extern unsigned int low_speed_i2c;
extern __DRIVER_I2C driver_i2c;
extern unsigned int control_i2c_taskes[1];
extern unsigned int comparison_writing;
extern unsigned int state_i2c_task;
extern unsigned char read_write_i2c_buffer[SIZE_BUFFER_FOR_I2C];

//���� ����� SPI1
extern unsigned char TxBuffer_SPI_EDF[SIZE_BUFFER_FOR_EDF];
extern unsigned char RxBuffer_SPI_EDF[SIZE_BUFFER_FOR_EDF];
extern int state_execution_spi1;
extern unsigned int control_spi1_taskes[2];
extern unsigned int state_spi1_task;
extern int etap_eeprom_write_enable;
extern unsigned int mutex_spi1;

//DataFlash
extern unsigned int number_bytes_transfer_spi_df;
extern unsigned int number_bytes_transfer_spi_df_copy;
extern unsigned char TxBuffer_SPI_DF_copy[SIZE_PAGE_DATAFLASH_MAX + 10];
extern unsigned int code_operation_copy;
extern int number_chip_dataflsh_exchange;
extern __DRIVER_SPI_DF driver_spi_df[NUMBER_DATAFLASH_CHIP];
extern unsigned int error_into_spi_df;
extern unsigned int dataflash_not_busy;
extern volatile unsigned int control_tasks_dataflash;
extern unsigned char buffer_for_manu_read_record[SIZE_BUFFER_FOR_DR_RECORD];
extern unsigned char buffer_for_USB_read_record_ar[SIZE_PAGE_DATAFLASH_2];
extern unsigned char buffer_for_RS485_read_record_ar[SIZE_PAGE_DATAFLASH_2];
extern unsigned char buffer_for_USB_read_record_dr[SIZE_BUFFER_FOR_DR_RECORD];
extern unsigned char buffer_for_RS485_read_record_dr[SIZE_BUFFER_FOR_DR_RECORD];
extern unsigned char buffer_for_USB_read_record_pr_err[SIZE_ONE_RECORD_PR_ERR];
extern unsigned char buffer_for_RS485_read_record_pr_err[SIZE_ONE_RECORD_PR_ERR];

extern unsigned int what_we_are_reading_from_dataflash_1;

//FATFS
extern uint32_t FATFS_command;

//���������� ���������
extern unsigned char crc_info_rejestrator_ar;
extern __INFO_AR_REJESTRATOR info_rejestrator_ar;
extern unsigned char crc_info_rejestrator_ar_ctrl;
extern __INFO_AR_REJESTRATOR info_rejestrator_ar_ctrl;
//extern const unsigned int number_word_digital_part_ar;
extern unsigned int forbidden_new_record_ar_mode_0;
extern unsigned int state_ar_record_m, state_ar_record_prt, state_ar_record_fatfs;
extern unsigned int prev_state_ar_record_m;
extern short int array_ar[SIZE_BUFFER_FOR_AR];
extern short int word_SRAM1;
extern unsigned int index_array_ar_current;
extern unsigned int index_array_ar_heat;
extern unsigned int index_array_ar_tail;
extern unsigned char tail_to_heat, current_to_tail;
extern int diff_index_heat_tail;
extern unsigned int prescaler_ar;
extern __HEADER_AR header_ar;
extern unsigned char buffer_for_fs[SIZE_PAGE_DATAFLASH_2];
extern unsigned int fs_temporary_address;
extern volatile unsigned int fs_count_to_transfer;
extern unsigned int etap_writing_part_page_fs_into_dataflash;
extern int number_record_of_ar_for_menu;
extern int number_record_of_ar_for_USB;
extern char id_ar_record_for_USB[8 + 1 + 3 + 1];
extern int max_number_time_sample_USB;
extern int number_record_of_ar_for_RS485;
extern int first_number_time_sample_for_USB;
extern int last_number_time_sample_for_USB;
extern int first_number_time_sample_for_RS485;
extern int last_number_time_sample_for_RS485;
extern char id_ar_record_for_RS485[8 + 1 + 3 + 1];
extern int max_number_time_sample_RS485;

//���������� ���������
extern unsigned char crc_info_rejestrator_dr;
extern  __INFO_REJESTRATOR info_rejestrator_dr;
extern unsigned char crc_info_rejestrator_dr_ctrl;
extern __INFO_REJESTRATOR info_rejestrator_dr_ctrl;
extern unsigned int state_dr_record;
extern unsigned int number_records_dr_waiting_for_saving_operation;
extern unsigned char buffer_for_save_dr_record[SIZE_BUFFER_FOR_DR_RECORD];
extern unsigned char buffer_for_save_dr_record_level_1[SIZE_BUFFER_FOR_DR_RECORD];
extern unsigned char buffer_for_save_dr_record_level_2[SIZE_BUFFER_FOR_DR_RECORD];
extern unsigned int part_writing_dr_into_dataflash;
extern unsigned int number_record_of_dr_for_menu;
extern unsigned int number_record_of_dr_for_USB;
extern unsigned int number_record_of_dr_for_RS485;
extern unsigned int part_reading_dr_from_dataflash_for_menu;
extern unsigned int part_reading_dr_from_dataflash_for_USB;
extern unsigned int part_reading_dr_from_dataflash_for_RS485;

//��������� ���������� �������
extern unsigned char crc_info_rejestrator_pr_err;
extern  __INFO_REJESTRATOR info_rejestrator_pr_err;
extern unsigned char crc_info_rejestrator_pr_err_ctrl;
extern __INFO_REJESTRATOR info_rejestrator_pr_err_ctrl;
extern unsigned char buffer_pr_err_records[SIZE_BUFFER_FOR_PR_ERR];
extern volatile unsigned int head_fifo_buffer_pr_err_records;
extern unsigned int tail_fifo_buffer_pr_err_records;
extern unsigned int temporary_block_writing_records_pr_err_into_DataFlash;
extern unsigned int etap_writing_pr_err_into_dataflash;
extern unsigned int number_recods_writing_into_dataflash_now;
extern unsigned int number_record_of_pr_err_into_menu;
extern unsigned int number_record_of_pr_err_into_USB;
extern unsigned int number_record_of_pr_err_into_RS485;

//������� ���������� �� �����������
extern unsigned int clean_rejestrators;

extern const unsigned char letters[69][2];
extern const unsigned char extra_letters[12][1 + MAX_NAMBER_LANGUAGE];

extern int current_language;

extern const uint8_t information_off_on[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD];
extern const uint32_t cursor_x_off_on[MAX_NAMBER_LANGUAGE][2];

//˳������� �������
extern unsigned int koef_resurs_changed;
extern float K_resurs_prt, K_resurs;
extern unsigned int resurs_vymykacha, resurs_vymykacha_ctrl;
extern unsigned int resurs_vidkljuchennja, resurs_vidkljuchennja_ctrl;
extern unsigned char crc_resurs, crc_resurs_ctrl;
extern unsigned int restart_counter;

//���������� ���� �� �����������
extern unsigned int vymknennja_vid_KZ_prt;
extern unsigned int MF_KZ;
extern unsigned int X_min_KZ_prt;
extern int R_KZ_prt;
extern unsigned int corupted_phases;

extern unsigned int number_of_phases_last_KZ;
extern int VMP_last_KZ;
extern unsigned int equal_more_KZ;

//RS-485
extern unsigned char TxBuffer_RS485[BUFFER_RS485];
extern unsigned char RxBuffer_RS485[BUFFER_RS485];
extern int TxBuffer_RS485_count;
extern int RxBuffer_RS485_count;
extern int RxBuffer_RS485_count_previous;
extern unsigned int time_last_receive_byte;
extern unsigned int max_reaction_time_rs_485;
extern unsigned int make_reconfiguration_RS_485;
extern unsigned int number_bits_rs_485_waiting;
extern unsigned int mark_current_tick_RS_485;
extern unsigned int timeout_idle_RS485;

//USB
extern uint8_t  USART_Rx_Buffer[USART_RX_DATA_SIZE]; 
extern uint32_t USART_Rx_ptr_in;
extern uint32_t USART_Rx_ptr_out;
extern uint32_t USART_Rx_length;

extern uint8_t  USB_Tx_State;

//��� UDP
extern u32 count_out;
extern u32 count_out_previous;
extern uint16_t previous_count_tim4_USB;
extern u8 buffer_out[BUFFER_USB];
extern unsigned char usb_received[BUFFER_USB];
extern unsigned char usb_transmiting[BUFFER_USB];
extern int usb_received_count;
extern int usb_transmiting_count;
extern unsigned char data_usb_transmiting;
extern unsigned int timeout_idle_USB;

//MODBUS-RTU
//extern unsigned int registers_address_read;
//extern unsigned int registers_address_write;
//extern unsigned int data_write_to_memory;
//extern unsigned int number_registers_read;
//extern unsigned short int registers_values[64] /*@ "variables_RAM1"*/;
//extern unsigned int action_is_continued;
//extern unsigned int part_transmit_carrent_data;
//extern unsigned int command_to_receive_current_data;
//extern int current_data_transmit[NUMBER_ANALOG_CANALES*NUMBER_POINT*NUMBER_PERIOD_TRANSMIT] /*@ "variables_RAM1"*/;
//extern volatile unsigned int wait_of_receiving_current_data; 
extern unsigned int password_set_USB, password_set_RS485;
extern unsigned int password_changed;
extern unsigned int password_ustuvannja;
extern unsigned int information_about_restart_counter;
extern unsigned int restart_timeout_interface;
extern unsigned int timeout_idle_new_settings;
extern unsigned int restart_timeout_idle_new_settings;
extern unsigned int type_of_settings_changed;

extern unsigned int serial_number_dev;
extern unsigned int edit_serial_number_dev;

//��� ����������� ���������� ��� ������� ����������
extern unsigned int info_vidkluchennja_vymykacha[2];
extern unsigned char info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MAX_NUMBER][7]; 

extern unsigned int  watchdog_l2;
extern unsigned int control_word_of_watchdog;
//extern unsigned int test_watchdogs;

/**************************************************************
 * ����� ��������������� � ������� ������ ����� �������:
 * protections.c --> setpoints_selecting()
 **************************************************************/
extern unsigned int gr_ustavok_tmp;

//����� ��������� �������
extern unsigned int total_error;

extern unsigned short const __checksum;
extern unsigned int __checksum_begin;
extern unsigned int __checksum_end;

//extern unsigned int __ICFEDIT_region_RAM1_start__;
//extern unsigned int __ICFEDIT_region_RAM1_size__;


#ifdef DEBUG_TEST
//extern unsigned int time_1, time_2, max_delay;

//�������� ����
//extern unsigned int temp_value_for_debbuging_1;
//extern unsigned int temp_value_for_debbuging_2;
//extern unsigned int temp_value_for_debbuging_3;


#endif

#endif
