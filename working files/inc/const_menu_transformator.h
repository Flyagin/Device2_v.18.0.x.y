#ifndef __CONST_MENU_TRANSFORMATOR__
#define __CONST_MENU_TRANSFORMATOR__

#define EKRAN_TRANSFORMATOR_INFO            (EKRAN_LIST_LEDS_FOR_RANGUVANNJA + 1)
#define EKRAN_TRANSFORMATOR_INFO_SETPOINT   (EKRAN_TRANSFORMATOR_INFO          + 1)
#define EKRAN_TRANSFORMATOR_INFO_CONTROL    (EKRAN_TRANSFORMATOR_INFO_SETPOINT + 1)

enum _index_ml_stp_transformator
{
  INDEX_ML_T0 = 0,
  INDEX_ML_TT,
  INDEX_ML_TN,

  MAX_ROW_FOR_TRANSFORMATOR_INFO_SETPOINT
};

enum _index_ml_ctrl_transformator
{
  INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE = 0,
  INDEX_ML_CTR_TRANSFORMATOR_3I0_3I0_1,
  
  MAX_ROW_FOR_TRANSFORMATOR_INFO_CONTROL
};

#define COL_T0_BEGIN                        6
#define COL_T0_END                          8

#define COL_TT_BEGIN                        6
#define COL_TT_END                          9

#define COL_TN_BEGIN                        6
#define COL_TN_END                          9

#define CTR_TRANSFORMATOR_MASKA             (                                 \
                                             MASKA_FOR_BIT(INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE)    |\
                                             MASKA_FOR_BIT(INDEX_ML_CTR_TRANSFORMATOR_3I0_3I0_1 )     \
                                            )

#endif
