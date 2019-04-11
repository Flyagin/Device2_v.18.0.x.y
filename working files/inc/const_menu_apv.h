#ifndef __CONST_MENU_APV__
#define __CONST_MENU_APV__

#define EKRAN_TIMEOUT_APV_GROUP1    (EKRAN_TIMEOUT_TZNP_GROUP4 + 1)
#define EKRAN_TIMEOUT_APV_GROUP2    (EKRAN_TIMEOUT_APV_GROUP1 + 1)
#define EKRAN_TIMEOUT_APV_GROUP3    (EKRAN_TIMEOUT_APV_GROUP2 + 1)
#define EKRAN_TIMEOUT_APV_GROUP4    (EKRAN_TIMEOUT_APV_GROUP3 + 1)
#define EKRAN_CONTROL_APV           (EKRAN_CONTROL_TZNP  + 1)

#define MAX_ROW_FOR_TIMEOUT_APV         9
#define MAX_ROW_FOR_CONTROL_APV         (8+8+4)

#define INDEX_ML_TMOAPV1                0
#define INDEX_ML_TMOAPV2                1
#define INDEX_ML_TMOAPV3                2
#define INDEX_ML_TMOAPV4                3
#define INDEX_ML_TMOAPV_BLOCK_VID_APV1  4
#define INDEX_ML_TMOAPV_BLOCK_VID_APV2  5
#define INDEX_ML_TMOAPV_BLOCK_VID_APV3  6
#define INDEX_ML_TMOAPV_BLOCK_VID_APV4  7
#define INDEX_ML_TMOAPV_BLOCK_VID_VV    8

#define INDEX_ML_CTRAPV_STAGE_1                 0
#define CTR_APV_STAGE_1                         (1 << INDEX_ML_CTRAPV_STAGE_1)          
#define INDEX_ML_CTRAPV_STAGE_2                 1
#define CTR_APV_STAGE_2                         (1 << INDEX_ML_CTRAPV_STAGE_2)          
#define INDEX_ML_CTRAPV_STAGE_3                 2
#define CTR_APV_STAGE_3                         (1 << INDEX_ML_CTRAPV_STAGE_3)          
#define INDEX_ML_CTRAPV_STAGE_4                 3
#define CTR_APV_STAGE_4                         (1 << INDEX_ML_CTRAPV_STAGE_4)          

#define INDEX_ML_CTRAPV_STARTED_FROM_DZ1        4
#define CTR_APV_STARTED_FROM_DZ1                (1 << INDEX_ML_CTRAPV_STARTED_FROM_DZ1)          
#define INDEX_ML_CTRAPV_STARTED_FROM_AMTDZ1     5
#define CTR_APV_STARTED_FROM_AMTDZ1             (1 << INDEX_ML_CTRAPV_STARTED_FROM_AMTDZ1)          

#define INDEX_ML_CTRAPV_STARTED_FROM_DZ2        6
#define CTR_APV_STARTED_FROM_DZ2                (1 << INDEX_ML_CTRAPV_STARTED_FROM_DZ2)          
#define INDEX_ML_CTRAPV_STARTED_FROM_AMTDZ2     7
#define CTR_APV_STARTED_FROM_AMTDZ2             (1 << INDEX_ML_CTRAPV_STARTED_FROM_AMTDZ2)          

#define INDEX_ML_CTRAPV_STARTED_FROM_DZ3        8
#define CTR_APV_STARTED_FROM_DZ3                (1 << INDEX_ML_CTRAPV_STARTED_FROM_DZ3)          
#define INDEX_ML_CTRAPV_STARTED_FROM_AMTDZ3     9
#define CTR_APV_STARTED_FROM_AMTDZ3             (1 << INDEX_ML_CTRAPV_STARTED_FROM_AMTDZ3)          

#define INDEX_ML_CTRAPV_STARTED_FROM_DZ4        10
#define CTR_APV_STARTED_FROM_DZ4                (1 << INDEX_ML_CTRAPV_STARTED_FROM_DZ4)          
#define INDEX_ML_CTRAPV_STARTED_FROM_AMTDZ4     11
#define CTR_APV_STARTED_FROM_AMTDZ4             (1 << INDEX_ML_CTRAPV_STARTED_FROM_AMTDZ4)          

#define INDEX_ML_CTRAPV_STARTED_FROM_MTZ1       12
#define CTR_APV_STARTED_FROM_MTZ1               (1 << INDEX_ML_CTRAPV_STARTED_FROM_MTZ1)          
#define INDEX_ML_CTRAPV_STARTED_FROM_MTZ2       13
#define CTR_APV_STARTED_FROM_MTZ2               (1 << INDEX_ML_CTRAPV_STARTED_FROM_MTZ2)          
#define INDEX_ML_CTRAPV_STARTED_FROM_MTZ3       14
#define CTR_APV_STARTED_FROM_MTZ3               (1 << INDEX_ML_CTRAPV_STARTED_FROM_MTZ3)   
#define INDEX_ML_CTRAPV_STARTED_FROM_MTZ4       15
#define CTR_APV_STARTED_FROM_MTZ4               (1 << INDEX_ML_CTRAPV_STARTED_FROM_MTZ4)   

#define INDEX_ML_CTRAPV_STARTED_FROM_TZNP1      16
#define CTR_APV_STARTED_FROM_TZNP1              (1 << INDEX_ML_CTRAPV_STARTED_FROM_TZNP1)          
#define INDEX_ML_CTRAPV_STARTED_FROM_TZNP2      17
#define CTR_APV_STARTED_FROM_TZNP2              (1 << INDEX_ML_CTRAPV_STARTED_FROM_TZNP2)          
#define INDEX_ML_CTRAPV_STARTED_FROM_TZNP3      18
#define CTR_APV_STARTED_FROM_TZNP3              (1 << INDEX_ML_CTRAPV_STARTED_FROM_TZNP3)          

#define CTR_APV_MASKA                    (                              \
                                          CTR_APV_STAGE_1            |   \
                                          CTR_APV_STAGE_2            |   \
                                          CTR_APV_STAGE_3            |   \
                                          CTR_APV_STAGE_4            |   \
                                          CTR_APV_STARTED_FROM_DZ1   |   \
                                          CTR_APV_STARTED_FROM_AMTDZ1|   \
                                          CTR_APV_STARTED_FROM_DZ2   |   \
                                          CTR_APV_STARTED_FROM_AMTDZ2|   \
                                          CTR_APV_STARTED_FROM_DZ3   |   \
                                          CTR_APV_STARTED_FROM_AMTDZ3|   \
                                          CTR_APV_STARTED_FROM_DZ4   |   \
                                          CTR_APV_STARTED_FROM_AMTDZ4|   \
                                          CTR_APV_STARTED_FROM_MTZ1  |   \
                                          CTR_APV_STARTED_FROM_MTZ2  |   \
                                          CTR_APV_STARTED_FROM_MTZ3  |   \
                                          CTR_APV_STARTED_FROM_MTZ4  |   \
                                          CTR_APV_STARTED_FROM_TZNP1 |   \
                                          CTR_APV_STARTED_FROM_TZNP2 |   \
                                          CTR_APV_STARTED_FROM_TZNP3     \
                                         )

#define COL_TMO_APV_1_BEGIN             4
#define COL_TMO_APV_1_COMMA             7
#define COL_TMO_APV_1_END               9

#define COL_TMO_APV_2_BEGIN             4
#define COL_TMO_APV_2_COMMA             7
#define COL_TMO_APV_2_END               9

#define COL_TMO_APV_3_BEGIN             4
#define COL_TMO_APV_3_COMMA             7
#define COL_TMO_APV_3_END               9

#define COL_TMO_APV_4_BEGIN             4
#define COL_TMO_APV_4_COMMA             7
#define COL_TMO_APV_4_END               9

#define COL_TMO_APV_BLOCK_VID_APV1_BEGIN 4
#define COL_TMO_APV_BLOCK_VID_APV1_COMMA 7
#define COL_TMO_APV_BLOCK_VID_APV1_END   9

#define COL_TMO_APV_BLOCK_VID_APV2_BEGIN 4
#define COL_TMO_APV_BLOCK_VID_APV2_COMMA 7
#define COL_TMO_APV_BLOCK_VID_APV2_END   9

#define COL_TMO_APV_BLOCK_VID_APV3_BEGIN 4
#define COL_TMO_APV_BLOCK_VID_APV3_COMMA 7
#define COL_TMO_APV_BLOCK_VID_APV3_END   9

#define COL_TMO_APV_BLOCK_VID_APV4_BEGIN 4
#define COL_TMO_APV_BLOCK_VID_APV4_COMMA 7
#define COL_TMO_APV_BLOCK_VID_APV4_END   9

#define COL_TMO_APV_BLOCK_VID_VV_BEGIN   4
#define COL_TMO_APV_BLOCK_VID_VV_COMMA   7
#define COL_TMO_APV_BLOCK_VID_VV_END     9

#endif
