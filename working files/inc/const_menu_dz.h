#ifndef __CONST_MENU_DZ__
#define __CONST_MENU_DZ__

#define EKRAN_SETPOINT_DZ_GROUP1   (EKRAN_SETPOINT_MTZ_GROUP4 + 1)
#define EKRAN_SETPOINT_DZ_GROUP2   (EKRAN_SETPOINT_DZ_GROUP1 + 1)
#define EKRAN_SETPOINT_DZ_GROUP3   (EKRAN_SETPOINT_DZ_GROUP2 + 1)
#define EKRAN_SETPOINT_DZ_GROUP4   (EKRAN_SETPOINT_DZ_GROUP3 + 1)
#define EKRAN_TIMEOUT_DZ_GROUP1    (EKRAN_TIMEOUT_MTZ_GROUP4 + 1)
#define EKRAN_TIMEOUT_DZ_GROUP2    (EKRAN_TIMEOUT_DZ_GROUP1  + 1)
#define EKRAN_TIMEOUT_DZ_GROUP3    (EKRAN_TIMEOUT_DZ_GROUP2  + 1)
#define EKRAN_TIMEOUT_DZ_GROUP4    (EKRAN_TIMEOUT_DZ_GROUP3  + 1)
#define EKRAN_CONTROL_DZ           (EKRAN_CONTROL_MTZ + 1)

enum _index_ml_stp_dz
{
  INDEX_ML_STP_K_DZ = 0,
  
  INDEX_ML_STP_DZ1,
  INDEX_ML_STP_DZ1_AMTZ,
  
  INDEX_ML_STP_DZ2_ANGLE,
  INDEX_ML_STP_DZ2_DIR,
  INDEX_ML_STP_DZ2_INV,
  INDEX_ML_STP_DZ2_AMTZ,
  
  INDEX_ML_STP_DZ3_ANGLE,
  INDEX_ML_STP_DZ3_DIR,
  INDEX_ML_STP_DZ3_INV,
  INDEX_ML_STP_DZ3_AMTZ,
  
  INDEX_ML_STP_DZ4_ANGLE,
  INDEX_ML_STP_DZ4_DIR,
  INDEX_ML_STP_DZ4_INV,
  INDEX_ML_STP_DZ4_AMTZ,
  
  MAX_ROW_FOR_SETPOINT_DZ
};

enum _index_ml_tmp_dz
{
  INDEX_ML_TMO_DZ1 = 0,
  INDEX_ML_TMO_DZ1_AMTZ,
  
  INDEX_ML_TMO_DZ2_DIR,
  INDEX_ML_TMO_DZ2_DIR_PR,
  INDEX_ML_TMO_DZ2_INV,
  INDEX_ML_TMO_DZ2_INV_PR,
  INDEX_ML_TMO_DZ2_AMTZ,
  INDEX_ML_TMO_DZ2_AMTZ_PR,
  INDEX_ML_TMO_DZ2_VVID_PR,
  INDEX_ML_TMO_DZ2_AMTZ_VVID_PR,
  
  INDEX_ML_TMO_DZ3_DIR,
  INDEX_ML_TMO_DZ3_DIR_PR,
  INDEX_ML_TMO_DZ3_INV,
  INDEX_ML_TMO_DZ3_INV_PR,
  INDEX_ML_TMO_DZ3_AMTZ,
  INDEX_ML_TMO_DZ3_AMTZ_PR,
  INDEX_ML_TMO_DZ3_VVID_PR,
  INDEX_ML_TMO_DZ3_AMTZ_VVID_PR,
  
  INDEX_ML_TMO_DZ4_DIR,
  INDEX_ML_TMO_DZ4_DIR_PR,
  INDEX_ML_TMO_DZ4_INV,
  INDEX_ML_TMO_DZ4_INV_PR,
  INDEX_ML_TMO_DZ4_AMTZ,
  INDEX_ML_TMO_DZ4_AMTZ_PR,
  INDEX_ML_TMO_DZ4_VVID_PR,
  INDEX_ML_TMO_DZ4_AMTZ_VVID_PR,

  INDEX_ML_TMO_NKN_DZ,
  
  MAX_ROW_FOR_TIMEOUT_DZ
};

enum _index_ml_ctrl_dz
{
  INDEX_CTR_DZ1 = 0,
  INDEX_CTR_DZ1_AMTZ,
  
  INDEX_CTR_DZ2,
  INDEX_CTR_DZ2_DIR,
  INDEX_CTR_DZ2_INV,
  INDEX_CTR_DZ2_PR_VID_DV,
  INDEX_CTR_DZ2_CONST_PR,
  INDEX_CTR_DZ2_AMTZ,
  
  INDEX_CTR_DZ3,
  INDEX_CTR_DZ3_DIR,
  INDEX_CTR_DZ3_INV,
  INDEX_CTR_DZ3_PR_VID_DV,
  INDEX_CTR_DZ3_CONST_PR,
  INDEX_CTR_DZ3_AMTZ,
  
  INDEX_CTR_DZ4,
  INDEX_CTR_DZ4_DIR,
  INDEX_CTR_DZ4_INV,
  INDEX_CTR_DZ4_PR_VID_DV,
  INDEX_CTR_DZ4_CONST_PR,
  INDEX_CTR_DZ4_AMTZ,
  
  INDEX_CTR_NKN_DZ,
  
  MAX_ROW_FOR_CONTROL_DZ
};

#define COL_PICKUP_DZ_K_BEGIN                6
#define COL_PICKUP_DZ_K_COMMA                7
#define COL_PICKUP_DZ_K_END                  9

#define COL_PICKUP_DZ1_BEGIN                 3
#define COL_PICKUP_DZ1_COMMA                 6
#define COL_PICKUP_DZ1_END                   8

#define COL_PICKUP_DZ1_AMTZ_BEGIN            4
#define COL_PICKUP_DZ1_AMTZ_COMMA            7
#define COL_PICKUP_DZ1_AMTZ_END              9

#define COL_PICKUP_DZ2_ANGLE_SIGN            6
#define COL_PICKUP_DZ2_ANGLE_BEGIN           7
#define COL_PICKUP_DZ2_ANGLE_END             8

#define COL_PICKUP_DZ2_DIR_BEGIN             3
#define COL_PICKUP_DZ2_DIR_COMMA             6
#define COL_PICKUP_DZ2_DIR_END               8

#define COL_PICKUP_DZ2_INV_BEGIN             3
#define COL_PICKUP_DZ2_INV_COMMA             6
#define COL_PICKUP_DZ2_INV_END               8

#define COL_PICKUP_DZ2_AMTZ_BEGIN            4
#define COL_PICKUP_DZ2_AMTZ_COMMA            7
#define COL_PICKUP_DZ2_AMTZ_END              9

#define COL_PICKUP_DZ3_ANGLE_SIGN            6
#define COL_PICKUP_DZ3_ANGLE_BEGIN           7
#define COL_PICKUP_DZ3_ANGLE_END             8

#define COL_PICKUP_DZ3_DIR_BEGIN             3
#define COL_PICKUP_DZ3_DIR_COMMA             6
#define COL_PICKUP_DZ3_DIR_END               8

#define COL_PICKUP_DZ3_INV_BEGIN             3
#define COL_PICKUP_DZ3_INV_COMMA             6
#define COL_PICKUP_DZ3_INV_END               8

#define COL_PICKUP_DZ3_AMTZ_BEGIN            4
#define COL_PICKUP_DZ3_AMTZ_COMMA            7
#define COL_PICKUP_DZ3_AMTZ_END              9

#define COL_PICKUP_DZ4_ANGLE_SIGN            6
#define COL_PICKUP_DZ4_ANGLE_BEGIN           7
#define COL_PICKUP_DZ4_ANGLE_END             8

#define COL_PICKUP_DZ4_DIR_BEGIN             3
#define COL_PICKUP_DZ4_DIR_COMMA             6
#define COL_PICKUP_DZ4_DIR_END               8

#define COL_PICKUP_DZ4_INV_BEGIN             3
#define COL_PICKUP_DZ4_INV_COMMA             6
#define COL_PICKUP_DZ4_INV_END               8

#define COL_PICKUP_DZ4_AMTZ_BEGIN            4
#define COL_PICKUP_DZ4_AMTZ_COMMA            7
#define COL_PICKUP_DZ4_AMTZ_END              9

#define COL_TMO_DZ1_BEGIN                    4
#define COL_TMO_DZ1_COMMA                    6
#define COL_TMO_DZ1_END                      8

#define COL_TMO_DZ1_AMTZ_BEGIN               4
#define COL_TMO_DZ1_AMTZ_COMMA               6
#define COL_TMO_DZ1_AMTZ_END                 8

#define COL_TMO_DZ2_DIR_BEGIN                4
#define COL_TMO_DZ2_DIR_COMMA                6
#define COL_TMO_DZ2_DIR_END                  8

#define COL_TMO_DZ2_DIR_PR_BEGIN             5
#define COL_TMO_DZ2_DIR_PR_COMMA             6
#define COL_TMO_DZ2_DIR_PR_END               8

#define COL_TMO_DZ2_INV_BEGIN                4
#define COL_TMO_DZ2_INV_COMMA                6
#define COL_TMO_DZ2_INV_END                  8

#define COL_TMO_DZ2_INV_PR_BEGIN             5
#define COL_TMO_DZ2_INV_PR_COMMA             6
#define COL_TMO_DZ2_INV_PR_END               8

#define COL_TMO_DZ2_AMTZ_BEGIN               4
#define COL_TMO_DZ2_AMTZ_COMMA               6
#define COL_TMO_DZ2_AMTZ_END                 8

#define COL_TMO_DZ2_AMTZ_PR_BEGIN            5
#define COL_TMO_DZ2_AMTZ_PR_COMMA            6
#define COL_TMO_DZ2_AMTZ_PR_END              8

#define COL_TMO_DZ2_VVID_PR_BEGIN            5
#define COL_TMO_DZ2_VVID_PR_COMMA            6
#define COL_TMO_DZ2_VVID_PR_END              8

#define COL_TMO_DZ2_AMTZ_VVID_PR_BEGIN       5
#define COL_TMO_DZ2_AMTZ_VVID_PR_COMMA       6
#define COL_TMO_DZ2_AMTZ_VVID_PR_END         8

#define COL_TMO_DZ3_DIR_BEGIN                4
#define COL_TMO_DZ3_DIR_COMMA                6
#define COL_TMO_DZ3_DIR_END                  8

#define COL_TMO_DZ3_DIR_PR_BEGIN             5
#define COL_TMO_DZ3_DIR_PR_COMMA             6
#define COL_TMO_DZ3_DIR_PR_END               8

#define COL_TMO_DZ3_INV_BEGIN                4
#define COL_TMO_DZ3_INV_COMMA                6
#define COL_TMO_DZ3_INV_END                  8

#define COL_TMO_DZ3_INV_PR_BEGIN             5
#define COL_TMO_DZ3_INV_PR_COMMA             6
#define COL_TMO_DZ3_INV_PR_END               8

#define COL_TMO_DZ3_AMTZ_BEGIN               4
#define COL_TMO_DZ3_AMTZ_COMMA               6
#define COL_TMO_DZ3_AMTZ_END                 8

#define COL_TMO_DZ3_AMTZ_PR_BEGIN            5
#define COL_TMO_DZ3_AMTZ_PR_COMMA            6
#define COL_TMO_DZ3_AMTZ_PR_END              8

#define COL_TMO_DZ3_VVID_PR_BEGIN            5
#define COL_TMO_DZ3_VVID_PR_COMMA            6
#define COL_TMO_DZ3_VVID_PR_END              8

#define COL_TMO_DZ3_AMTZ_VVID_PR_BEGIN       5
#define COL_TMO_DZ3_AMTZ_VVID_PR_COMMA       6
#define COL_TMO_DZ3_AMTZ_VVID_PR_END         8

#define COL_TMO_DZ4_DIR_BEGIN                4
#define COL_TMO_DZ4_DIR_COMMA                6
#define COL_TMO_DZ4_DIR_END                  8

#define COL_TMO_DZ4_DIR_PR_BEGIN             5
#define COL_TMO_DZ4_DIR_PR_COMMA             6
#define COL_TMO_DZ4_DIR_PR_END               8

#define COL_TMO_DZ4_INV_BEGIN                4
#define COL_TMO_DZ4_INV_COMMA                6
#define COL_TMO_DZ4_INV_END                  8

#define COL_TMO_DZ4_INV_PR_BEGIN             5
#define COL_TMO_DZ4_INV_PR_COMMA             6
#define COL_TMO_DZ4_INV_PR_END               8

#define COL_TMO_DZ4_AMTZ_BEGIN               4
#define COL_TMO_DZ4_AMTZ_COMMA               6
#define COL_TMO_DZ4_AMTZ_END                 8

#define COL_TMO_DZ4_AMTZ_PR_BEGIN            5
#define COL_TMO_DZ4_AMTZ_PR_COMMA            6
#define COL_TMO_DZ4_AMTZ_PR_END              8

#define COL_TMO_DZ4_VVID_PR_BEGIN            5
#define COL_TMO_DZ4_VVID_PR_COMMA            6
#define COL_TMO_DZ4_VVID_PR_END              8

#define COL_TMO_DZ4_AMTZ_VVID_PR_BEGIN       5
#define COL_TMO_DZ4_AMTZ_VVID_PR_COMMA       6
#define COL_TMO_DZ4_AMTZ_VVID_PR_END         8

#define COL_TMO_NKN_DZ_BEGIN                 5
#define COL_TMO_NKN_DZ_COMMA                 6
#define COL_TMO_NKN_DZ_END                   8

#define CTR_DZ_MASKA                   (                                        \
                                        MASKA_FOR_BIT(INDEX_CTR_DZ1)           |\
                                        MASKA_FOR_BIT(INDEX_CTR_DZ1_AMTZ)      |\
                                        MASKA_FOR_BIT(INDEX_CTR_DZ2)           |\
                                        MASKA_FOR_BIT(INDEX_CTR_DZ2_DIR)       |\
                                        MASKA_FOR_BIT(INDEX_CTR_DZ2_INV)       |\
                                        MASKA_FOR_BIT(INDEX_CTR_DZ2_PR_VID_DV) |\
                                        MASKA_FOR_BIT(INDEX_CTR_DZ2_CONST_PR)  |\
                                        MASKA_FOR_BIT(INDEX_CTR_DZ2_AMTZ)      |\
                                        MASKA_FOR_BIT(INDEX_CTR_DZ3)           |\
                                        MASKA_FOR_BIT(INDEX_CTR_DZ3_DIR)       |\
                                        MASKA_FOR_BIT(INDEX_CTR_DZ3_INV)       |\
                                        MASKA_FOR_BIT(INDEX_CTR_DZ3_PR_VID_DV) |\
                                        MASKA_FOR_BIT(INDEX_CTR_DZ3_CONST_PR)  |\
                                        MASKA_FOR_BIT(INDEX_CTR_DZ3_AMTZ)      |\
                                        MASKA_FOR_BIT(INDEX_CTR_DZ4)           |\
                                        MASKA_FOR_BIT(INDEX_CTR_DZ4_DIR)       |\
                                        MASKA_FOR_BIT(INDEX_CTR_DZ4_INV)       |\
                                        MASKA_FOR_BIT(INDEX_CTR_DZ4_PR_VID_DV) |\
                                        MASKA_FOR_BIT(INDEX_CTR_DZ4_CONST_PR)  |\
                                        MASKA_FOR_BIT(INDEX_CTR_DZ4_AMTZ)      |\
                                        MASKA_FOR_BIT(INDEX_CTR_NKN_DZ)         \
                                       )

#endif
