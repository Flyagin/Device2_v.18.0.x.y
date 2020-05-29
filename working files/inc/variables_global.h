#ifndef __GLOBAL_VARIABLES_H
#define __GLOBAL_VARIABLES_H

//����������� �������
unsigned int semaphore_adc_irq;
unsigned int adc_DATA_VAL_read;
//unsigned int adc_TEST_VAL_read;
unsigned int status_adc_read_work;
const unsigned int input_adc[NUMBER_INPUTs_ADCs][2]={
                                                     {1,0x8370},
                                                     {1,0x8770},
                                                     {1,0x8b70},
                                                     {1,0x8f70},
                                                     {1,0x9370},
                                                     {1,0x9770},
                                                     {1,0x9b70},
                                                     {1,0x9f70},
                                                     {1,0xa370},
                                                     {1,0xa770},
                                                     {1,0xab70},
                                                     {1,0xaf70},
                                                     {1,0xb370},
                                                     {1,0xb770},
                                                     {1,0xbb70},
                                                     {1,0xbf70}
                                                    };
EXTENDED_OUTPUT_DATA output_adc[NUMBER_INPUTs_ADCs];
ROZSHYRENA_VYBORKA rozshyrena_vyborka;

unsigned int command_word_adc, command_word_adc_work, active_index_command_word_adc;
unsigned int state_reading_ADCs = STATE_READING_ADCs_NONE;
unsigned int channel_request, channel_answer;

uint32_t step_timer_adc = TIM5_CCR1_2_VAL;
uint32_t penultimate_tick_DATA_VAL, previous_tick_DATA_VAL;

DATA_FOR_OSCYLOGRAPH data_for_oscylograph[MAX_INDEX_DATA_FOR_OSCYLOGRAPH];
unsigned int head_data_for_oscylograph;
unsigned int tail_data_for_oscylograph, DATA_VAL_tail_data_for_oscylograph;

VYBORKA_XY perechid_cherez_nul[MAX_INDEX_PhK][2];
unsigned int fix_perechid_cherez_nul[MAX_INDEX_PhK];
POPEREDNJY_PERECHID poperednij_perechid;

unsigned int maska_canaliv_fapch;
float frequency = -1, frequency_work = -1;
unsigned int tick_period = (TIM5_CCR1_2_VAL*NUMBER_POINT), tick_period_work = (TIM5_CCR1_2_VAL*NUMBER_POINT);
unsigned int tick_c, tick_c_work;

float frequency_min = 50, frequency_max = 50;
unsigned int command_restart_monitoring_frequency;

unsigned int vref_adc_averange_sum[NUMBER_ANALOG_CANALES];
uint32_t vref_adc_averange_sum_1s[NUMBER_ANALOG_CANALES] = 
{
  VREF_NORMAL_VALUE*MAIN_FREQUENCY,
  VREF_NORMAL_VALUE*MAIN_FREQUENCY,
  VREF_NORMAL_VALUE*MAIN_FREQUENCY,
  VREF_NORMAL_VALUE*MAIN_FREQUENCY,
  VREF_NORMAL_VALUE*MAIN_FREQUENCY,
  VREF_NORMAL_VALUE*MAIN_FREQUENCY,
  VREF_NORMAL_VALUE*MAIN_FREQUENCY,
  VREF_NORMAL_VALUE*MAIN_FREQUENCY
};
uint32_t vref_adc_moment_value_1s[NUMBER_ANALOG_CANALES][MAIN_FREQUENCY];
uint32_t vref_adc[NUMBER_ANALOG_CANALES] = 
                                          {
                                            VREF_NORMAL_VALUE,
                                            VREF_NORMAL_VALUE,
                                            VREF_NORMAL_VALUE,
                                            VREF_NORMAL_VALUE,
                                            VREF_NORMAL_VALUE,
                                            VREF_NORMAL_VALUE,
                                            VREF_NORMAL_VALUE,
                                            VREF_NORMAL_VALUE
                                          };

unsigned int index_array_of_one_value_fourier;

EXTENDED_SAMPLE ADCs_data_raw[NUMBER_ANALOG_CANALES];
int ADCs_data[NUMBER_ANALOG_CANALES];
//int current_data[NUMBER_ANALOG_CANALES*NUMBER_POINT*NUMBER_PERIOD_TRANSMIT];
unsigned long long sqr_current_data_3I0[NUMBER_POINT];
unsigned int index_array_of_current_data_value;

unsigned int changed_ustuvannja = CHANGED_ETAP_NONE; 
unsigned char crc_ustuvannja;
unsigned int ustuvannja_meas[NUMBER_ANALOG_CANALES] = {
                                                        DEFAULT_USTUVANNJA_VALUE,
                                                        DEFAULT_USTUVANNJA_VALUE,
                                                        DEFAULT_USTUVANNJA_VALUE,
                                                        DEFAULT_USTUVANNJA_VALUE,
                                                        DEFAULT_USTUVANNJA_VALUE,
                                                        DEFAULT_USTUVANNJA_VALUE,
                                                        DEFAULT_USTUVANNJA_VALUE,
                                                        DEFAULT_USTUVANNJA_VALUE
                                                      };
unsigned int ustuvannja[NUMBER_ANALOG_CANALES] = {
                                                        DEFAULT_USTUVANNJA_VALUE,
                                                        DEFAULT_USTUVANNJA_VALUE,
                                                        DEFAULT_USTUVANNJA_VALUE,
                                                        DEFAULT_USTUVANNJA_VALUE,
                                                        DEFAULT_USTUVANNJA_VALUE,
                                                        DEFAULT_USTUVANNJA_VALUE,
                                                        DEFAULT_USTUVANNJA_VALUE,
                                                        DEFAULT_USTUVANNJA_VALUE
                                                      };
unsigned int edit_ustuvannja[NUMBER_ANALOG_CANALES];
int phi_ustuvannja_meas[NUMBER_ANALOG_CANALES], phi_ustuvannja[NUMBER_ANALOG_CANALES], phi_edit_ustuvannja[NUMBER_ANALOG_CANALES];
float phi_ustuvannja_sin_cos_meas[2*NUMBER_ANALOG_CANALES] = {
                                                              0.0f, 1.0f,
                                                              0.0f, 1.0f,
                                                              0.0f, 1.0f,
                                                              0.0f, 1.0f,
                                                              0.0f, 1.0f,
                                                              0.0f, 1.0f,
                                                              0.0f, 1.0f,
                                                              0.0f, 1.0f
                                                             };
float phi_ustuvannja_sin_cos[2*NUMBER_ANALOG_CANALES] = {
                                                         0.0f, 1.0f,
                                                         0.0f, 1.0f,
                                                         0.0f, 1.0f,
                                                         0.0f, 1.0f,
                                                         0.0f, 1.0f,
                                                         0.0f, 1.0f,
                                                         0.0f, 1.0f,
                                                         0.0f, 1.0f
                                                        };
float phi_edit_ustuvannja_sin_cos[2*NUMBER_ANALOG_CANALES];

const float sin_data_f[NUMBER_POINT] = {
                                         0.000000000000000000000000000000f,
                                         0.195090322016128000000000000000f,
                                         0.382683432365090000000000000000f,
                                         0.555570233019602000000000000000f,
                                         0.707106781186547000000000000000f,
                                         0.831469612302545000000000000000f,
                                         0.923879532511287000000000000000f,
                                         0.980785280403230000000000000000f,
                                         1.000000000000000000000000000000f,
                                         0.980785280403230000000000000000f,
                                         0.923879532511287000000000000000f,
                                         0.831469612302545000000000000000f,
                                         0.707106781186548000000000000000f,
                                         0.555570233019602000000000000000f,
                                         0.382683432365090000000000000000f,
                                         0.195090322016129000000000000000f,
                                         0.000000000000000122514845490862f,
                                        -0.195090322016128000000000000000f,
                                        -0.382683432365090000000000000000f,
                                        -0.555570233019602000000000000000f,
                                        -0.707106781186547000000000000000f,
                                        -0.831469612302545000000000000000f,
                                        -0.923879532511287000000000000000f,
                                        -0.980785280403230000000000000000f,
                                        -1.000000000000000000000000000000f,
                                        -0.980785280403230000000000000000f,
                                        -0.923879532511287000000000000000f,
                                        -0.831469612302545000000000000000f,
                                        -0.707106781186548000000000000000f,
                                        -0.555570233019602000000000000000f,
                                        -0.382683432365090000000000000000f,
                                        -0.195090322016129000000000000000f
};

const float cos_data_f[NUMBER_POINT] = {
                                         1.000000000000000000000000000000f,
                                         0.980785280403230000000000000000f,
                                         0.923879532511287000000000000000f,
                                         0.831469612302545000000000000000f,
                                         0.707106781186548000000000000000f,
                                         0.555570233019602000000000000000f,
                                         0.382683432365090000000000000000f,
                                         0.195090322016129000000000000000f,
                                         0.000000000000000122514845490862f,
                                        -0.195090322016128000000000000000f,
                                        -0.382683432365090000000000000000f,
                                        -0.555570233019602000000000000000f,
                                        -0.707106781186547000000000000000f,
                                        -0.831469612302545000000000000000f,
                                        -0.923879532511287000000000000000f,
                                        -0.980785280403230000000000000000f,
                                        -1.000000000000000000000000000000f,
                                        -0.980785280403230000000000000000f,
                                        -0.923879532511287000000000000000f,
                                        -0.831469612302545000000000000000f,
                                        -0.707106781186548000000000000000f,
                                        -0.555570233019602000000000000000f,
                                        -0.382683432365090000000000000000f,
                                        -0.195090322016129000000000000000f,
                                         0.000000000000000000000000000000f,
                                         0.195090322016128000000000000000f,
                                         0.382683432365090000000000000000f,
                                         0.555570233019602000000000000000f,
                                         0.707106781186547000000000000000f,
                                         0.831469612302545000000000000000f,
                                         0.923879532511287000000000000000f,
                                         0.980785280403230000000000000000f
};

unsigned int index_sin_cos_array;
unsigned int index_data_sin_cos_array;
int data_sin[NUMBER_POINT*NUMBER_ANALOG_CANALES];
int data_cos[NUMBER_POINT*NUMBER_ANALOG_CANALES];
int ortogonal_irq[2*NUMBER_ANALOG_CANALES];
int ortogonal[2*NUMBER_ANALOG_CANALES][2];
unsigned int bank_ortogonal;
unsigned long long sum_sqr_data_3I0_irq;
unsigned long long sum_sqr_data_3I0[2];
//unsigned int semaphore_measure_values;
unsigned int semaphore_measure_values_low;

unsigned int semaphore_measure_values_low1;

unsigned int number_inputs_for_fix_one_second;
unsigned int number_inputs_for_fix_one_period;
unsigned int measurement[_NUMBER_IM]; 
unsigned int measurement_high[2][_NUMBER_IM], bank_measurement_high = 0; 
unsigned int measurement_middle[_NUMBER_IM]; 
unsigned int measurement_low[_NUMBER_IM]; 

const unsigned int index_converter[NUMBER_ANALOG_CANALES]  = {FULL_ORT_3I0, FULL_ORT_Ia, FULL_ORT_Ib , FULL_ORT_Ic, FULL_ORT_Ua , FULL_ORT_Ub , FULL_ORT_Uc , FULL_ORT_3U0};
int ortogonal_calc[2*FULL_ORT_MAX];
int ortogonal_calc_low[2*FULL_ORT_MAX];
int phi_angle[2][FULL_ORT_MAX];
uint32_t bank_for_calc_phi_angle, state_calc_phi_angle;
int base_index_for_angle = -1;

int P_plus[2];
int P_minus[2];
int Q_1q[2];
int Q_2q[2];
int Q_3q[2];
int Q_4q[2];
unsigned int lichylnyk_1s_po_20ms;
unsigned int bank_for_enegry;
int P[2], Q[2], cos_phi_x1000[2];
unsigned int S[2];
uint32_t bank_for_calc_power, state_calc_power;
double energy[2][MAX_NUMBER_INDEXES_ENERGY];
uint32_t state_calc_energy;
unsigned int clean_energy;
unsigned int information_about_clean_energy;

int resistance[MAX_NUMBER_INDEXES_RESISTANCE_FULL];
int resistance_middle[MAX_NUMBER_INDEXES_RESISTANCE];
int resistance_low[MAX_NUMBER_INDEXES_RESISTANCE];

int sector_1_mtz_tznp[8];
int sector_2_mtz_tznp[8];

//����������� "�������" ������� ���������� � "�����"
const uint32_t small_big_rang[NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL] =
{
RANG_BLOCK_VKL_VV,
RANG_RESET_LEDS,
RANG_RESET_RELES,
RANG_MISCEVE_DYSTANCIJNE,
RANG_STATE_VV,
RANG_OTKL_VID_ZOVN_ZAHYSTIV,
RANG_VKL_VV,
RANG_CTRL_VKL,
RANG_OTKL_VV,
RANG_CTRL_OTKL,
RANG_1_GRUPA_USTAVOK,
RANG_2_GRUPA_USTAVOK,
RANG_3_GRUPA_USTAVOK,
RANG_4_GRUPA_USTAVOK,
RANG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV,

RANG_EXT_NKN_DZ,
RANG_BLOCK_DZ1,
RANG_BLOCK_DZ2,
RANG_BLOCK_PR_DZ2,
RANG_OP_PR_DZ2,
RANG_BLOCK_DZ3,
RANG_BLOCK_PR_DZ3,
RANG_OP_PR_DZ3,
RANG_BLOCK_DZ4,
RANG_BLOCK_PR_DZ4,
RANG_OP_PR_DZ4,

RANG_BLOCK_MTZ1,
RANG_BLOCK_MTZ2,
RANG_BLOCK_USK_MTZ2,
RANG_BLOCK_MTZ3,
RANG_BLOCK_MTZ4,

RANG_BLOCK_ZDZ,
RANG_PUSK_ZDZ_VID_DV,

RANG_BLOCK_NZZ,

RANG_BLOCK_TZNP1,
RANG_BLOCK_TZNP2,
RANG_BLOCK_TZNP3,

RANG_STAT_BLK_APV,

RANG_ACHR_CHAPV_VID_DV,
RANG_BLOCK_ACHR1,
RANG_BLOCK_ACHR2,

RANG_PUSK_UROV_VID_DV,

RANG_BLOCK_ZOP,

RANG_BLOCK_UMIN1,
RANG_START_UMIN1,
RANG_BLOCK_UMIN2,
RANG_START_UMIN2,

RANG_BLOCK_UMAX1,
RANG_BLOCK_UMAX2,

(RANG_BLOCK_UP1 + 3*0),
(RANG_BLOCK_UP1 + 3*1),
(RANG_BLOCK_UP1 + 3*2),
(RANG_BLOCK_UP1 + 3*3),
(RANG_BLOCK_UP1 + 3*4),
(RANG_BLOCK_UP1 + 3*5),
(RANG_BLOCK_UP1 + 3*6),
(RANG_BLOCK_UP1 + 3*7),

RANG_DF1_IN,
RANG_DF2_IN,
RANG_DF3_IN,
RANG_DF4_IN,
RANG_DF5_IN,
RANG_DF6_IN,
RANG_DF7_IN,
RANG_DF8_IN,
RANG_DT1_SET,
RANG_DT1_RESET,
RANG_DT2_SET,
RANG_DT2_RESET,
RANG_DT3_SET,
RANG_DT3_RESET,
RANG_DT4_SET,
RANG_DT4_RESET
};

//���������� ���
unsigned int sector_directional_mtz[4][3];
unsigned int Uxy_bilshe_porogu[3];
unsigned int Ix_bilshe_porogu[3];
unsigned int temp_states_for_mtz;

//���
#if (                                   \
     (MODYFIKACIA_VERSII_PZ == 0) ||    \
     (MODYFIKACIA_VERSII_PZ == 3)       \
    )   
uint32_t delta_time_test = PERIOD_ZDZ_TEST;
uint32_t zdz_ovd_diagnostyka;
#endif

//���
int sector_1[8];
int sector_2[8];
unsigned int sector_i_minus_u_1;
unsigned int sector_i_minus_u_2;
unsigned int po_3I0; /*0 - ���������� � �������� �����������, ������ �� ���� - ���������� � �������� ����������*/
unsigned int po_3U0; /*0 - ���������� � �������� �����������, ������ �� ���� - ���������� � �������� ����������*/
unsigned int sector_NZZ; /*0 - ���������� � �������� �����������, ������ �� ���� - ���������� � �������� ����������*/
/*
0  - ��� ������ ������� 3I0 � 3U0 � "���" ������
1  - ��� ������ ������� 3I0 � 3U0 � 1-��� ��������
2  - ��� ������ ������� 3I0 � 3U0 � 2-��� ��������
3  - ��� ������ ������� 3I0 � 3U0 � 3-��� ��������
4  - ��� ������ ������� 3I0 � 3U0 � 4-��� ��������
*/
unsigned int Nzz_3U0_bilshe_porogu, Nzz_3I0_bilshe_porogu;

//����
unsigned int TZNP_3U0_bilshe_porogu;
unsigned int TZNP_3I0_r_bilshe_porogu;
unsigned int sector_directional_tznp[3];

//���������� ��
int32_t sector_directional_dz[4 - 1][3] = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}};
unsigned int Uxy_bilshe_porogu_dz[3];
unsigned int Ix_bilshe_porogu_dz[3];

unsigned int i1_bilshe_porogu, i2_bilshe_porogu;

uint32_t TIM_PRT_write_tick;

//��������������
unsigned int state_leds;
unsigned int state_trigger_leds;
uint32_t state_leds_Fx[2];
uint32_t state_leds_ctrl;

unsigned int state_inputs; //"� ������ " - ������� ������������� ��� (1); "���� �������" - ������� ��������� ��� (0)
unsigned int active_inputs; //"���� ��������" - ������� ������������� ��� (1); "���� ��������" - ������� ��������� ��� (0)
unsigned int state_outputs;
unsigned int state_outputs_raw;
unsigned int state_signal_outputs;
unsigned int active_functions[N_BIG];
unsigned int trigger_active_functions[N_BIG], trigger_active_functions_ctrl[N_BIG];
unsigned char crc_trg_func, crc_trg_func_ctrl;
unsigned int trigger_functions_USB[N_BIG];
unsigned int trigger_functions_RS485[N_BIG];
unsigned int copying_active_functions;
unsigned int active_functions_copy[N_BIG];
unsigned int active_functions_trg[N_BIG];
unsigned int mutex_buttons;
unsigned int pressed_buttons;
unsigned int fix_active_buttons, fix_active_buttons_ctrl;
unsigned int mutex_interface;
unsigned int activation_function_from_interface[N_SMALL];
unsigned int reset_trigger_function_from_interface;
unsigned int diagnostyka_before[N_DIAGN];
volatile unsigned int diagnostyka[N_DIAGN];
unsigned int set_diagnostyka[N_DIAGN];
unsigned int clear_diagnostyka[N_DIAGN];

uint32_t board_register;

int global_timers[MAX_NUMBER_GLOBAL_TIMERS]; //����� ���������� �������
unsigned int timer_prt_signal_output_mode_2;
unsigned int output_timer_prt_signal_output_mode_2;
unsigned int static_logic_df;

unsigned int previous_states_APV_0;
unsigned int trigger_APV_0;

_Bool previous_state_po_achr_chapv_uaf1;
_Bool previous_state_po_achr_chapv_ubf1;
_Bool previous_state_po_achr_chapv_ucf1;
_Bool previous_states_CHAPV1;
_Bool previous_states_CHAPV2;
_Bool trigger_CHAPV1;
_Bool trigger_CHAPV2;

_Bool previous_states_ready_tu;
_Bool trigger_ready_tu;

unsigned int start_restart = 0xff;

SRAM1 unsigned char working_ekran[MAX_ROW_LCD][MAX_COL_LCD];
unsigned int rewrite_ekran_once_more;

volatile unsigned int new_state_keyboard;
unsigned int new_state_keyboard_for_db;
unsigned char time_set_keyboard[NUMBER_KEY_KEYBOARD];

unsigned int time_rewrite; //��� ���� ������� ���� ���������� ����������
unsigned int reinit_LCD;

SRAM1 __CURRENT_EKRAN current_ekran;
SRAM1 int position_in_current_level_menu[MAX_LEVEL_MENU]; //����� � ����� ���������� ������ �������������
SRAM1 int previous_level_in_current_level_menu[MAX_LEVEL_MENU]; //����� � ����� ���������� �������� ��������� ������ ��� ������ ���� ����
const uint32_t buttons_mode[NUMBER_BUTTON_MODE][N_SMALL] = 
{
  {MASKA_BUTTON_MODE_0_SIGNALS_0, MASKA_BUTTON_MODE_0_SIGNALS_1, MASKA_BUTTON_MODE_0_SIGNALS_2},
  {MASKA_BUTTON_MODE_1_SIGNALS_0, MASKA_BUTTON_MODE_1_SIGNALS_1, MASKA_BUTTON_MODE_1_SIGNALS_2}
};
const uint32_t output_boards[N_OUTPUT_BOARDS][2] = 
{
  { 2, 1},
  { 9, 4}
#if (                                   \
     (MODYFIKACIA_VERSII_PZ == 0) ||    \
     (MODYFIKACIA_VERSII_PZ == 1) ||    \
     (MODYFIKACIA_VERSII_PZ == 3)       \
    )
  ,
  {16, 5}
#endif
};
const uint32_t input_boards[N_INPUT_BOARDS][2] = 
{
  { 8, 4}
#if (                                   \
     (MODYFIKACIA_VERSII_PZ == 0) ||    \
     (MODYFIKACIA_VERSII_PZ == 1) ||    \
     (MODYFIKACIA_VERSII_PZ == 3)       \
    )
  ,
  {16, 5}
#if (MODYFIKACIA_VERSII_PZ == 0)
  ,
  {20, 7}
#endif
#endif
};

unsigned int periodical_tasks_TEST_SETTINGS;
unsigned int periodical_tasks_TEST_USTUVANNJA;
unsigned int periodical_tasks_TEST_TRG_FUNC;
unsigned int periodical_tasks_TEST_TRG_FUNC_LOCK;
unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_AR;
unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_AR_LOCK;
unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_DR;
unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_DR_LOCK;
unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR;
unsigned int periodical_tasks_TEST_INFO_REJESTRATOR_PR_ERR_LOCK;
unsigned int periodical_tasks_TEST_RESURS;
unsigned int periodical_tasks_TEST_RESURS_LOCK;
unsigned int periodical_tasks_TEST_FLASH_MEMORY;
unsigned int periodical_tasks_CALCULATION_ANGLE;
unsigned int periodical_tasks_CALC_ENERGY_DATA;

const unsigned char odynyci_vymirjuvannja[MAX_NAMBER_LANGUAGE][NUMBER_ODYNYCI_VYMIRJUVANNJA] =
{
  {'�', '�', '�'},
  {'�', '�', '�'},
  {'A', 'V', 's'},
  {'�', '�', '�'}
};

const unsigned int size_dimension_array[MAX_NAMBER_LANGUAGE] = {SIZE_R_DIMENSION, SIZE_R_DIMENSION, SIZE_R_DIMENSION - 1, SIZE_R_DIMENSION};
const unsigned char resistance_dimension[MAX_NAMBER_LANGUAGE][SIZE_R_DIMENSION] = {"��", "��", "� ", "��"}; /*� ��� ��� �� ������� ������ ����� ����� ��� ��������� ���������*/


const uint32_t max_value_for_tf[1 + TOTAL_NUMBER_PROTECTION][MAX_ROW_LIST_SOURCE_TF] =
{
  {
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG,
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL
  },
  {
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_DZ_SIGNAL_FOR_RANG,
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_DZ_SIGNAL_FOR_RANG_SMALL
  },
  {
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_DZ_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG,
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_DZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL
  },
  {
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_DZ_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG,
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_DZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL
  },
  {
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_DZ_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG,
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_DZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL
  },
  {
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_DZ_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG,
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_DZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL
  },
  {
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_DZ_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG,
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_DZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL
  },
  {
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_DZ_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL,
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_DZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL
  },
  {
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_DZ_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG + NUMBER_UROV_SIGNAL_FOR_RANG,
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_DZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL + NUMBER_UROV_SIGNAL_FOR_RANG_SMALL
  },
  {
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_DZ_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG + NUMBER_UROV_SIGNAL_FOR_RANG + NUMBER_ZOP_SIGNAL_FOR_RANG,
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_DZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL + NUMBER_UROV_SIGNAL_FOR_RANG_SMALL + NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL
  },
  {
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_DZ_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG + NUMBER_UROV_SIGNAL_FOR_RANG + NUMBER_ZOP_SIGNAL_FOR_RANG + NUMBER_UMIN_SIGNAL_FOR_RANG,
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_DZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL + NUMBER_UROV_SIGNAL_FOR_RANG_SMALL + NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL + NUMBER_UMIN_SIGNAL_FOR_RANG_SMALL
  },
  {
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_DZ_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG + NUMBER_UROV_SIGNAL_FOR_RANG + NUMBER_ZOP_SIGNAL_FOR_RANG + NUMBER_UMIN_SIGNAL_FOR_RANG + NUMBER_UMAX_SIGNAL_FOR_RANG,
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_DZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL + NUMBER_UROV_SIGNAL_FOR_RANG_SMALL + NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL + NUMBER_UMIN_SIGNAL_FOR_RANG_SMALL + NUMBER_UMAX_SIGNAL_FOR_RANG_SMALL
  },
  {
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_DZ_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG + NUMBER_UROV_SIGNAL_FOR_RANG + NUMBER_ZOP_SIGNAL_FOR_RANG + NUMBER_UMIN_SIGNAL_FOR_RANG + NUMBER_UMAX_SIGNAL_FOR_RANG + NUMBER_UP_SIGNAL_FOR_RANG,
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_DZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL + NUMBER_UROV_SIGNAL_FOR_RANG_SMALL + NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL + NUMBER_UMIN_SIGNAL_FOR_RANG_SMALL + NUMBER_UMAX_SIGNAL_FOR_RANG_SMALL + NUMBER_UP_SIGNAL_FOR_RANG_SMALL
  },
  {
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_DZ_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG + NUMBER_UROV_SIGNAL_FOR_RANG + NUMBER_ZOP_SIGNAL_FOR_RANG + NUMBER_UMIN_SIGNAL_FOR_RANG + NUMBER_UMAX_SIGNAL_FOR_RANG + NUMBER_UP_SIGNAL_FOR_RANG + NUMBER_VMP_SIGNAL_FOR_RANG_SMALL,
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_DZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL + NUMBER_UROV_SIGNAL_FOR_RANG_SMALL + NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL + NUMBER_UMIN_SIGNAL_FOR_RANG_SMALL + NUMBER_UMAX_SIGNAL_FOR_RANG_SMALL + NUMBER_UP_SIGNAL_FOR_RANG_SMALL + NUMBER_VMP_SIGNAL_FOR_RANG_SMALL
  },
  {
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG + NUMBER_DZ_SIGNAL_FOR_RANG + NUMBER_MTZ_SIGNAL_FOR_RANG + NUMBER_ZDZ_SIGNAL_FOR_RANG + NUMBER_ZZ_SIGNAL_FOR_RANG + NUMBER_TZNP_SIGNAL_FOR_RANG + NUMBER_APV_SIGNAL_FOR_RANG + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG + NUMBER_UROV_SIGNAL_FOR_RANG + NUMBER_ZOP_SIGNAL_FOR_RANG + NUMBER_UMIN_SIGNAL_FOR_RANG + NUMBER_UMAX_SIGNAL_FOR_RANG + NUMBER_UP_SIGNAL_FOR_RANG + NUMBER_VMP_SIGNAL_FOR_RANG + NUMBER_EL_SIGNAL_FOR_RANG,
    1 + NUMBER_GENERAL_SIGNAL_FOR_RANG_SMALL + NUMBER_DZ_SIGNAL_FOR_RANG_SMALL + NUMBER_MTZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZDZ_SIGNAL_FOR_RANG_SMALL + NUMBER_ZZ_SIGNAL_FOR_RANG_SMALL + NUMBER_TZNP_SIGNAL_FOR_RANG_SMALL + NUMBER_APV_SIGNAL_FOR_RANG_SMALL + NUMBER_ACHR_CHAPV_SIGNAL_FOR_RANG_SMALL + NUMBER_UROV_SIGNAL_FOR_RANG_SMALL + NUMBER_ZOP_SIGNAL_FOR_RANG_SMALL + NUMBER_UMIN_SIGNAL_FOR_RANG_SMALL + NUMBER_UMAX_SIGNAL_FOR_RANG_SMALL + NUMBER_UP_SIGNAL_FOR_RANG_SMALL + NUMBER_VMP_SIGNAL_FOR_RANG_SMALL + NUMBER_EL_SIGNAL_FOR_RANG_SMALL
  }
};


unsigned int fixed_power_down_into_RTC; 
unsigned char time[7]; 
unsigned char time_copy[7]; 
unsigned char calibration;
unsigned char calibration_copy;
unsigned int copying_time;
unsigned char time_edit[7]; 
unsigned char calibration_edit;
unsigned int copy_register8_RTC;
int etap_reset_of_bit = ETAP_CLEAR_OF_NONE;
int etap_settings_test_frequency = -1;
unsigned char temp_register_rtc[2];

unsigned int changed_settings = CHANGED_ETAP_NONE; 
unsigned char crc_settings;
__SETTINGS current_settings_prt, current_settings;
SRAM1 __SETTINGS edition_settings, current_settings_interfaces;
unsigned int mtz_settings_prt[NUMBER_LEVEL_MTZ][MTZ_SETTINGS_LENGTH];
unsigned int mtz_tmr_const[NUMBER_LEVEL_MTZ][NUMBER_LEVEL_TMR_CONST];
int * type_mtz_arr[NUMBER_LEVEL_MTZ];
unsigned int mtz_const_menu_settings_prt[NUMBER_LEVEL_MTZ][MTZ_CONST_MENU_SETTINGS_LENGTH];
unsigned int const i_nom_const = I_NOM * KOEF_1_2_I;
unsigned int const u_f_nom_const = U_PHASE_NOM * KOEF_0_2_U;
unsigned int * setpoint_mtz[NUMBER_LEVEL_MTZ];
unsigned int * setpoint_mtz_n_vpered[NUMBER_LEVEL_MTZ];
unsigned int * setpoint_mtz_n_nazad[NUMBER_LEVEL_MTZ];
unsigned int * setpoint_mtz_U[NUMBER_LEVEL_MTZ];
unsigned int * setpoint_mtz_po_napruzi[NUMBER_LEVEL_MTZ];
int * timeout_mtz[NUMBER_LEVEL_MTZ];
int * timeout_mtz_n_vpered[NUMBER_LEVEL_MTZ];
int * timeout_mtz_n_nazad[NUMBER_LEVEL_MTZ];
int * timeout_mtz_po_napruzi[NUMBER_LEVEL_MTZ];
_Bool previous_state_mtz_po_incn = 0;
_Bool previous_state_mtz_po_uncn = 0;
unsigned int p_global_trigger_state_mtz2;

//���������� ������ � ������� � �����
unsigned int number_seconds;
unsigned int number_minutes;

//������++
unsigned int restart_resurs_count;
unsigned int resurs_temp;
unsigned int resurs_global;
unsigned int resurs_global_min;
unsigned int resurs_global_max;

unsigned int restart_timing_watchdog;
unsigned int time_1_watchdog_input;
unsigned int time_2_watchdog_input;
unsigned int time_delta_watchdog_input;
unsigned int time_delta_watchdog_input_min = 0xffff*10;
unsigned int time_delta_watchdog_input_max;

unsigned int time_1_watchdog_output;
unsigned int time_2_watchdog_output;
unsigned int time_delta_watchdog_output;
unsigned int time_delta_watchdog_output_min = 0xffff*10;
unsigned int time_delta_watchdog_output_max;

//I2C
unsigned char Temporaty_I2C_Buffer[MAX_NUMBER_REGISTERS_RTC + 2];
unsigned int number_busy_state;
unsigned int type_error_of_exchanging_via_i2c;
//unsigned int low_speed_i2c = 0;
__DRIVER_I2C driver_i2c;
unsigned int control_i2c_taskes[1];
unsigned int state_i2c_task = STATE_FIRST_READING_RTC;
unsigned char read_write_i2c_buffer[SIZE_BUFFER_FOR_I2C];

//���� ����� SPI1
unsigned char TxBuffer_SPI_EDF[SIZE_BUFFER_FOR_EDF];
unsigned char RxBuffer_SPI_EDF[SIZE_BUFFER_FOR_EDF];
int state_execution_spi1 = -1; //-1 - ������� ������� �� ������� ����� ����������; 0 - ���������� ����; 1 - ���� ���������� ��� �������
unsigned int control_spi1_taskes[2];
unsigned int comparison_writing; /*�������� �� ������, �� ��� ���������� � ������� ��'���, ������������ �� ������ �� ��� ��������� �������� ���������� ���� �������� ������*/
unsigned int state_spi1_task;
int etap_eeprom_write_enable = -1;
unsigned int mutex_spi1;

//DataFlash
unsigned int number_bytes_transfer_spi_df;
unsigned int number_bytes_transfer_spi_df_copy;
unsigned char TxBuffer_SPI_DF_copy[SIZE_PAGE_DATAFLASH_MAX + 10];
unsigned int code_operation_copy;
int number_chip_dataflsh_exchange = -1;
__DRIVER_SPI_DF driver_spi_df[NUMBER_DATAFLASH_CHIP] = {
                                                        {TRANSACTION_EXECUTING_NONE, CODE_OPERATION_NONE},
                                                        {TRANSACTION_EXECUTING_NONE, CODE_OPERATION_NONE}
                                                       };
unsigned int error_into_spi_df;/*�������� �������� ������, �� ����������� ������� ��� ������/�������� ����� SPI_DF*/
unsigned int dataflash_not_busy;
volatile unsigned int control_tasks_dataflash;
SRAM1 unsigned char buffer_for_manu_read_record[SIZE_BUFFER_FOR_DR_RECORD];
unsigned char buffer_for_USB_read_record_ar[SIZE_PAGE_DATAFLASH_2];
unsigned char buffer_for_RS485_read_record_ar[SIZE_PAGE_DATAFLASH_2];
unsigned char buffer_for_USB_read_record_dr[SIZE_BUFFER_FOR_DR_RECORD];
unsigned char buffer_for_RS485_read_record_dr[SIZE_BUFFER_FOR_DR_RECORD];
unsigned char buffer_for_USB_read_record_pr_err[SIZE_ONE_RECORD_PR_ERR];
unsigned char buffer_for_RS485_read_record_pr_err[SIZE_ONE_RECORD_PR_ERR];

unsigned int what_we_are_reading_from_dataflash_1;

//FATFS
uint32_t FATFS_command;

//���������� ���������
unsigned char crc_info_rejestrator_ar;
__INFO_AR_REJESTRATOR info_rejestrator_ar;
unsigned char crc_info_rejestrator_ar_ctrl;
__INFO_AR_REJESTRATOR info_rejestrator_ar_ctrl;
//const unsigned int number_word_digital_part_ar = ( NUMBER_TOTAL_SIGNAL_FOR_RANG / (8*sizeof(short int)) ) + ( ( NUMBER_TOTAL_SIGNAL_FOR_RANG % (8*sizeof(short int))) != 0);
unsigned int forbidden_new_record_ar_mode_0 /*= 0*/; 
unsigned int state_ar_record_m = STATE_AR_NONE_M, state_ar_record_prt = STATE_AR_NONE_PRT, state_ar_record_fatfs = STATE_AR_NONE_FATFS;
unsigned int prev_state_ar_record_m = STATE_AR_NONE_M;
SRAM1_AR short int array_ar[SIZE_BUFFER_FOR_AR];
SRAM1 short int word_SRAM1;
unsigned int index_array_ar_current /*= 0*/;
unsigned int index_array_ar_heat;
unsigned int index_array_ar_tail;
unsigned char tail_to_heat, current_to_tail;
int diff_index_heat_tail; /*�� ����� ���� ��������������� ���� ����� ��� ����������*/
unsigned int prescaler_ar /*= 0*/; //�������� ��� ����, ��� � 32 ������� �� ������� ������� 16 ������� �� �������
__HEADER_AR header_ar;
unsigned char buffer_for_fs[SIZE_PAGE_DATAFLASH_2];
unsigned int fs_temporary_address;
volatile unsigned int fs_count_to_transfer;
unsigned int etap_writing_part_page_fs_into_dataflash = ETAP_NONE;
int number_record_of_ar_for_menu = -1; //�� ����� ������, �� ����� ������ �� ��������
int number_record_of_ar_for_USB = -1; //�� ����� ������, �� ����� ������ �� ��������
char id_ar_record_for_USB[8 + 1 + 3 + 1];
int max_number_time_sample_USB;
int number_record_of_ar_for_RS485 = -1; //�� ����� ������, �� ����� ������ �� ��������
int first_number_time_sample_for_USB;// -1 - ��������� ������ ��.�.; 0 - ������ ������� ��� ����������� ������ � �.�.
int last_number_time_sample_for_USB;// -1 - ��������� ������ ��.�.; 0 - ������ ������� ��� ����������� ������ � �.�.
int first_number_time_sample_for_RS485;// -1 - ��������� ������ ��.�.; 0 - ������ ������� ��� ����������� ������ � �.�.
int last_number_time_sample_for_RS485;// -1 - ��������� ������ ��.�.; 0 - ������ ������� ��� ����������� ������ � �.�.
char id_ar_record_for_RS485[8 + 1 + 3 + 1];
int max_number_time_sample_RS485;

//���������� ���������
unsigned char crc_info_rejestrator_dr;
 __INFO_REJESTRATOR info_rejestrator_dr;
unsigned char crc_info_rejestrator_dr_ctrl;
__INFO_REJESTRATOR info_rejestrator_dr_ctrl;
unsigned int state_dr_record = STATE_DR_NO_RECORD;
unsigned int number_records_dr_waiting_for_saving_operation;
unsigned char buffer_for_save_dr_record[SIZE_BUFFER_FOR_DR_RECORD];
unsigned char buffer_for_save_dr_record_level_1[SIZE_BUFFER_FOR_DR_RECORD];
unsigned char buffer_for_save_dr_record_level_2[SIZE_BUFFER_FOR_DR_RECORD];
unsigned int part_writing_dr_into_dataflash;
unsigned int number_record_of_dr_for_menu = 0xffff; //�� ����� ������, �� ����� ������ �� ��������
unsigned int number_record_of_dr_for_USB = 0xffff; //�� ����� ������, �� ����� ������ �� ��������
unsigned int number_record_of_dr_for_RS485 = 0xffff; //�� ����� ������, �� ����� ������ �� ��������
unsigned int part_reading_dr_from_dataflash_for_menu;
unsigned int part_reading_dr_from_dataflash_for_USB;
unsigned int part_reading_dr_from_dataflash_for_RS485;

//��������� ���������� �������
unsigned char crc_info_rejestrator_pr_err;
__INFO_REJESTRATOR info_rejestrator_pr_err;
unsigned char crc_info_rejestrator_pr_err_ctrl;
__INFO_REJESTRATOR info_rejestrator_pr_err_ctrl;
unsigned char buffer_pr_err_records[SIZE_BUFFER_FOR_PR_ERR];
volatile unsigned int head_fifo_buffer_pr_err_records;
unsigned int tail_fifo_buffer_pr_err_records;
unsigned int temporary_block_writing_records_pr_err_into_DataFlash;
unsigned int etap_writing_pr_err_into_dataflash = ETAP_NONE;
unsigned int number_recods_writing_into_dataflash_now;
unsigned int number_record_of_pr_err_into_menu = 0xffff;
unsigned int number_record_of_pr_err_into_USB = 0xffff;
unsigned int number_record_of_pr_err_into_RS485 = 0xffff;

//������� ���������� �� �����������
unsigned int clean_rejestrators;

//˳������� �������
unsigned int koef_resurs_changed = CHANGED_ETAP_NONE;
float K_resurs_prt, K_resurs;
unsigned int resurs_vymykacha, resurs_vymykacha_ctrl;
unsigned int resurs_vidkljuchennja, resurs_vidkljuchennja_ctrl;
unsigned char crc_resurs, crc_resurs_ctrl;
unsigned int restart_counter;

//���������� ���� �� �����������
unsigned int vymknennja_vid_KZ_prt;
unsigned int MF_KZ;
unsigned int X_min_KZ_prt = (unsigned int)UNDEF_RESISTANCE;
int R_KZ_prt;
unsigned int corupted_phases;

unsigned int number_of_phases_last_KZ;
int VMP_last_KZ = UNDEF_VMP;
unsigned int equal_more_KZ;

//RS-485
SRAM1 unsigned char TxBuffer_RS485[BUFFER_RS485];
SRAM1 unsigned char RxBuffer_RS485[BUFFER_RS485];
SRAM1 int TxBuffer_RS485_count;
SRAM1 int RxBuffer_RS485_count;
SRAM1 int RxBuffer_RS485_count_previous;
SRAM1 unsigned int time_last_receive_byte;
SRAM1 unsigned int max_reaction_time_rs_485;
SRAM1 unsigned int make_reconfiguration_RS_485;
SRAM1 unsigned int number_bits_rs_485_waiting;
SRAM1 unsigned int mark_current_tick_RS_485;
SRAM1 unsigned int timeout_idle_RS485;

//USB
uint8_t  USART_Rx_Buffer[USART_RX_DATA_SIZE]; 
uint32_t USART_Rx_ptr_in;
uint32_t USART_Rx_ptr_out;
uint32_t USART_Rx_length;

extern uint8_t  USB_Tx_State;

//��� UDP
u32 count_out;
u32 count_out_previous;
uint16_t previous_count_tim4_USB;
u8 buffer_out[BUFFER_USB];
unsigned char usb_received[BUFFER_USB];
unsigned char usb_transmiting[BUFFER_USB];
int usb_received_count;
int usb_transmiting_count;
unsigned char data_usb_transmiting;
unsigned int timeout_idle_USB;

//MODBUS-RTU
//unsigned int registers_address_read =0x20000000;
//unsigned int registers_address_write =0x20000000;
//unsigned int data_write_to_memory;
//unsigned int number_registers_read/* = 0*/;
//unsigned short int registers_values[64]/* @ "variables_RAM1"*/;
//unsigned int action_is_continued/* = false*/;
//unsigned int part_transmit_carrent_data/* = 0*/;
//unsigned int command_to_receive_current_data/* = false*/;
//int current_data_transmit[NUMBER_ANALOG_CANALES*NUMBER_POINT*NUMBER_PERIOD_TRANSMIT] /*@ "variables_RAM1"*/; 
//volatile unsigned int wait_of_receiving_current_data/*  = false*/; 
SRAM1 unsigned int password_set_USB, password_set_RS485;
SRAM1 unsigned int password_changed;
SRAM1 unsigned int password_ustuvannja;
unsigned int information_about_restart_counter;
unsigned int restart_timeout_interface;
unsigned int timeout_idle_new_settings;
unsigned int restart_timeout_idle_new_settings;
SRAM1 unsigned int type_of_settings_changed;

unsigned int serial_number_dev;                         //���������� ����� ��������
unsigned int edit_serial_number_dev;

//��� ����������� ���������� ��� ������� ����������
unsigned int info_vidkluchennja_vymykacha[2];
unsigned char info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MAX_NUMBER][7]; 

unsigned int  watchdog_l2;
unsigned int control_word_of_watchdog;
//unsigned int test_watchdogs/* = 0*/;

/**************************************************************
 * ����� ��������������� � ������� ������ ����� �������:
 * protections.c --> setpoints_selecting()
 **************************************************************/
unsigned int gr_ustavok_tmp = 0xf;

//����� ��������� �������
unsigned int total_error;

const unsigned char letters[69][2] =
{
{ 176, 223 },  //�
{ 178, 73  }, // �
{ 179, 105 }, // �
{ 192, 65  }, // �
{ 193, 160 }, // �
{ 194, 66  }, // �
{ 195, 161 }, // �
{ 196, 224 }, // �
{ 197, 69  }, // �
{ 168, 162 }, // �
{ 198, 163 }, // �
{ 199, 164 }, // �
{ 200, 165 }, // �
{ 201, 166 }, // �
{ 202, 75  }, // �
{ 203, 167 }, // �
{ 204, 77  }, // �
{ 205, 72  }, // �
{ 206, 79  }, // �
{ 207, 168 }, // �
{ 208, 80  }, // �
{ 209, 67  }, // �
{ 210, 84  }, // �
{ 211, 169 }, // �
{ 212, 170 }, // �
{ 213, 88  }, // �
{ 214, 225 }, // �
{ 215, 171 }, // �
{ 216, 172 }, // �
{ 217, 226 }, // �
{ 218, 173 }, // �
{ 220, 98  }, // �
{ 219, 174 }, // �
{ 221, 175 }, // �
{ 222, 176 }, // �
{ 223, 177 }, // �
{ 224, 97  }, // �
{ 225, 178 }, // �
{ 226, 179 }, // �
{ 227, 180 }, // �
{ 228, 227 }, // �
{ 229, 101 }, // �
{ 184, 181 }, // �
{ 230, 182 }, // �
{ 231, 183 }, // �
{ 232, 184 }, // �
{ 233, 185 }, // �
{ 234, 186 }, // �
{ 235, 187 }, // �
{ 236, 188 }, // �
{ 237, 189 }, // �
{ 238, 111 }, // �
{ 239, 190 }, // �
{ 240, 112 }, // �
{ 241, 99  }, // �
{ 242, 191 }, // �
{ 243, 121 }, // �
{ 244, 228 }, // �
{ 245, 120 }, // �
{ 246, 229 }, // �
{ 247, 192 }, // �
{ 248, 193 }, // �
{ 249, 230 }, // �
{ 250, 194 }, // �
{ 252, 196 }, // �
{ 251, 195 }, // �
{ 253, 197 }, // �
{ 254, 198 }, // �
{ 255, 199 } // �
};

const unsigned char extra_letters[12][1 + MAX_NAMBER_LANGUAGE] =
{
/*CODE   RU    UA    EN    KZ     */  
{ 0xAF, 0xFF, 0x00, 0x00, 0xFF}, // � ��� ������ ���� ����� ��� ��������� ��������� ���������
{ 0xBF, 0xFF, 0x01, 0xFF, 0xFF}, // �
{ 0xA5, 0xFF, 0x02, 0xFF, 0xFF}, // �
{ 0xB4, 0xFF, 0x03, 0xFF, 0xFF}, // �
{ 0xAA, 0xFF, 0x04, 0xFF, 0xFF}, // �
{ 0xBA, 0xFF, 0x05, 0xFF, 0xFF}, // �
{ 0x8A, 0xFF, 0xFF, 0xFF, 0x00}, // � - ������� ������ � ����� ����� ��� WIN1251
{ 0x9A, 0xFF, 0xFF, 0xFF, 0x01}, // � - ������� ������ � ����� ����� ��� WIN1251
{ 0xBD, 0xFF, 0xFF, 0xFF, 0x02}, // � - ������� ������ � ����� ����� ��� WIN1251
{ 0xBE, 0xFF, 0xFF, 0xFF, 0x03}, // � - ������� ������ � ����� ����� ��� WIN1251
{ 0x80, 0xFF, 0xFF, 0xFF, 0x04}, // � - ������� ������ � ����� ����� ��� WIN1251
{ 0x90, 0xFF, 0xFF, 0xFF, 0x05}  // � - ������� ������ � ����� ����� ��� WIN1251
};

int current_language = LANGUAGE_ABSENT;

const uint8_t information_off_on[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
{
  {"     ����.      ", "      ���.      "},
  {"     ����.      ", "     ����.     "},
  {"      Off       ", "       On       "},
  {"     њ��.      ", "     ����.      "}
};
const uint32_t cursor_x_off_on[MAX_NAMBER_LANGUAGE][2] = 
{
 {4, 5},
 {4, 4},
 {5, 6},
 {4, 4}
};


extern unsigned short const __checksum;
extern unsigned int __checksum_begin;
extern unsigned int __checksum_end;

//extern unsigned int __ICFEDIT_region_RAM1_start__;
//extern unsigned int __ICFEDIT_region_RAM1_size__;

#ifdef DEBUG_TEST
//unsigned int time_1 = 0xffff0000, time_2 = 0xffff0000, max_delay = 0;

//�������� ����
//unsigned int temp_value_for_debbuging_1 = 0;
//unsigned int temp_value_for_debbuging_2 = 0;
//unsigned int temp_value_for_debbuging_3 = 0;


#endif



#endif
