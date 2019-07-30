#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 10300

//#if (                                   \
//     (MODYFIKACIA_VERSII_PZ == 0) ||    \
//     (MODYFIKACIA_VERSII_PZ == 3)       \
//    )   
//конечный регистр в карте памяти
#define END_ADR_REGISTER 11900

//#else
//конечный регистр в карте памяти
//#define END_ADR_REGISTER 11395
//#endif

int privateUSTBigGetReg2(int adrReg);

int getUSTBigModbusRegister(int);//получить содержимое регистра
int getUSTBigModbusBit(int);//получить содержимое бита
int setUSTBigModbusRegister(int, int);//получить содержимое регистра
int setUSTBigModbusBit(int, int);//получить содержимое бита

void setUSTBigCountObject(void);//записать к-во обектов
void preUSTBigReadAction(void);//action до чтения
void preUSTBigWriteAction(void);//action до записи
int  postUSTBigWriteAction(void);//action после записи
int  ustFunc000(int inOffset, int gruppa, int *multer, int regUst, uint32_t **editValue);
int grupa_ustavok_control(int  offset, int *grupa_ustavok, int *adresGruppa);

COMPONENT_OBJ *ustbigcomponent;

int ustFunc000(int inOffset, int gruppa, int *multer, int regUst, uint32_t **editValue)
{
  int diapazon = 1;
  int actControl = 0;
  if(inOffset<0)
  {
    inOffset = -inOffset;
    actControl = 1;
  }//if(inOffset<0)
  (*multer) = 10;
  switch(inOffset)
  {
  case 0:
    (*editValue) = (uint32_t*)&edition_settings.grupa_ustavok;
    (*multer) = 1;
    if(regUst<1 || regUst>4) diapazon=0;
    break;
  case 1:
    (*editValue) = (uint32_t*)&edition_settings.type_mtz1;
    (*multer) = 1;
    if(regUst<0 || regUst>2) diapazon=0;
    break;
  case 2:
    (*editValue) = (uint32_t*)&edition_settings.type_mtz2;
    (*multer) = 1;
    if(regUst<0 || regUst>7) diapazon=0;
    break;
  case 3:
    (*editValue) = (uint32_t*)&edition_settings.type_mtz3;
    (*multer) = 1;
    if(regUst<0 || regUst>7) diapazon=0;
    break;
  case 4:
    (*editValue) = (uint32_t*)&edition_settings.type_mtz4;
    (*multer) = 1;
    if(regUst<0 || regUst>2) diapazon=0;
    break;

//IF ВСТАВКА 7-14

  case 15:
    (*editValue) = &edition_settings.setpoint_mtz_1[gruppa];
    if(regUst<SETPOINT_MTZ1_MIN/10 || regUst>SETPOINT_MTZ1_MAX/10) diapazon=0;
    break;
  case 16:
    (*editValue) = &edition_settings.setpoint_mtz_1_n_vpered[gruppa];
    if(regUst<SETPOINT_MTZ1_N_VPERED_MIN/10 || regUst>SETPOINT_MTZ1_N_VPERED_MAX/10) diapazon=0;
    break;
  case 17:
    (*editValue) = &edition_settings.setpoint_mtz_1_n_nazad[gruppa];
    if(regUst<SETPOINT_MTZ1_N_NAZAD_MIN/10 || regUst>SETPOINT_MTZ1_N_NAZAD_MAX/10) diapazon=0;
    break;
  case 18:
    (*editValue) = &edition_settings.setpoint_mtz_1_po_napruzi[gruppa];
    if(regUst<SETPOINT_MTZ1_PO_NAPRUZI_MIN/10 || regUst>SETPOINT_MTZ1_PO_NAPRUZI_MAX/10) diapazon=0;
    break;
  case 19:
    (*editValue) = &edition_settings.setpoint_mtz_1_U[gruppa];
    if(regUst<SETPOINT_MTZ1_U_MIN/10 || regUst>SETPOINT_MTZ1_U_MAX/10) diapazon=0;
    break;
  case 20:
    (*multer) = 1;
    (*editValue) = &edition_settings.setpoint_mtz_1_angle[gruppa];
    if(regUst<SETPOINT_MTZ1_ANGLE_MIN || regUst>SETPOINT_MTZ1_ANGLE_MAX) diapazon=0;
    break;
  case 21:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_1[gruppa];
    if(regUst<TIMEOUT_MTZ1_MIN/10 || regUst>TIMEOUT_MTZ1_MAX/10) diapazon=0;
    break;
  case 22:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_1_n_vpered[gruppa];
    if(regUst<TIMEOUT_MTZ1_N_VPERED_MIN/10 || regUst>TIMEOUT_MTZ1_N_VPERED_MAX/10) diapazon=0;
    break;
  case 23:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_1_n_nazad[gruppa];
    if(regUst<TIMEOUT_MTZ1_N_NAZAD_MIN/10 || regUst>TIMEOUT_MTZ1_N_NAZAD_MAX/10) diapazon=0;
    break;
  case 24:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_1_po_napruzi[gruppa];
    if(regUst<TIMEOUT_MTZ1_PO_NAPRUZI_MIN/10 || regUst>TIMEOUT_MTZ1_PO_NAPRUZI_MAX/10) diapazon=0;
    break;

//  int count_bit = 68;
  case 27:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_mtz_2[gruppa];
    if(regUst<SETPOINT_MTZ2_MIN/10 || regUst>SETPOINT_MTZ2_MAX/10) diapazon=0;
    break;
  case 28:
    (*editValue) = &edition_settings.setpoint_mtz_2_n_vpered[gruppa];
    if(regUst<SETPOINT_MTZ2_N_VPERED_MIN/10 || regUst>SETPOINT_MTZ2_N_VPERED_MAX/10) diapazon=0;
    break;
  case 29:
    (*editValue) = &edition_settings.setpoint_mtz_2_n_nazad[gruppa];
    if(regUst<SETPOINT_MTZ2_N_NAZAD_MIN/10 || regUst>SETPOINT_MTZ2_N_NAZAD_MAX/10) diapazon=0;
    break;
  case 30:
    (*editValue) = &edition_settings.setpoint_mtz_2_po_napruzi[gruppa];
    if(regUst<SETPOINT_MTZ2_PO_NAPRUZI_MIN/10 || regUst>SETPOINT_MTZ2_PO_NAPRUZI_MAX/10) diapazon=0;
    break;
  case 31:
    (*editValue) = &edition_settings.setpoint_mtz_2_U[gruppa];
    if(regUst<SETPOINT_MTZ2_U_MIN/10 || regUst>SETPOINT_MTZ2_U_MAX/10) diapazon=0;
    break;
  case 32:
    (*multer) = 1;
    (*editValue) = &edition_settings.setpoint_mtz_2_angle[gruppa];
    if(regUst<SETPOINT_MTZ2_ANGLE_MIN || regUst>SETPOINT_MTZ2_ANGLE_MAX) diapazon=0;
    break;
  case 33:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_2[gruppa];
    if(regUst<TIMEOUT_MTZ2_MIN/10 || regUst>TIMEOUT_MTZ2_MAX/10) diapazon=0;
    break;
  case 34:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_2_n_vpered[gruppa];
    if(regUst<TIMEOUT_MTZ2_N_VPERED_MIN/10 || regUst>TIMEOUT_MTZ2_N_VPERED_MAX/10) diapazon=0;
    break;
  case 35:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_2_n_nazad[gruppa];
    if(regUst<TIMEOUT_MTZ2_N_NAZAD_MIN/10 || regUst>TIMEOUT_MTZ2_N_NAZAD_MAX/10) diapazon=0;
    break;
  case 36:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_2_po_napruzi[gruppa];
    if(regUst<TIMEOUT_MTZ2_PO_NAPRUZI_MIN/10 || regUst>TIMEOUT_MTZ2_PO_NAPRUZI_MAX/10) diapazon=0;
    break;
  case 37:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_2_vvid_pr[gruppa];
    if(regUst<TIMEOUT_MTZ2_VVID_PR_MIN/10 || regUst>TIMEOUT_MTZ2_VVID_PR_MAX/10) diapazon=0;
    break;
  case 38:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_2_pr[gruppa];
    if(regUst<TIMEOUT_MTZ2_PR_MIN/10 || regUst>TIMEOUT_MTZ2_PR_MAX/10) diapazon=0;
    break;
  case 39:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_2_n_vpered_pr[gruppa];
    if(regUst<TIMEOUT_MTZ2_N_VPERED_PR_MIN/10 || regUst>TIMEOUT_MTZ2_N_VPERED_PR_MAX/10) diapazon=0;
    break;
  case 40:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_2_n_nazad_pr[gruppa];
    if(regUst<TIMEOUT_MTZ2_N_NAZAD_PR_MIN/10 || regUst>TIMEOUT_MTZ2_N_NAZAD_PR_MAX/10) diapazon=0;
    break;
  case 41:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_2_po_napruzi_pr[gruppa];
    if(regUst<TIMEOUT_MTZ2_PO_NAPRUZI_PR_MIN/10 || regUst>TIMEOUT_MTZ2_PO_NAPRUZI_PR_MAX/10) diapazon=0;
    break;

//  int count_bit = 68;
  case 45:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_mtz_3[gruppa];
    if(regUst<SETPOINT_MTZ3_MIN/10 || regUst>SETPOINT_MTZ3_MAX/10) diapazon=0;
    break;
  case 46:
    (*editValue) = &edition_settings.setpoint_mtz_3_n_vpered[gruppa];
    if(regUst<SETPOINT_MTZ3_N_VPERED_MIN/10 || regUst>SETPOINT_MTZ3_N_VPERED_MAX/10) diapazon=0;
    break;
  case 47:
    (*editValue) = &edition_settings.setpoint_mtz_3_n_nazad[gruppa];
    if(regUst<SETPOINT_MTZ3_N_NAZAD_MIN/10 || regUst>SETPOINT_MTZ3_N_NAZAD_MAX/10) diapazon=0;
    break;
  case 48:
    (*editValue) = &edition_settings.setpoint_mtz_3_po_napruzi[gruppa];
    if(regUst<SETPOINT_MTZ3_PO_NAPRUZI_MIN/10 || regUst>SETPOINT_MTZ3_PO_NAPRUZI_MAX/10) diapazon=0;
    break;
  case 49:
    (*editValue) = &edition_settings.setpoint_mtz_3_U[gruppa];
    if(regUst<SETPOINT_MTZ3_U_MIN/10 || regUst>SETPOINT_MTZ3_U_MAX/10) diapazon=0;
    break;
  case 50:
    (*multer) = 1;
    (*editValue) = &edition_settings.setpoint_mtz_3_angle[gruppa];
    if(regUst<SETPOINT_MTZ3_ANGLE_MIN || regUst>SETPOINT_MTZ3_ANGLE_MAX) diapazon=0;
    break;
  case 51:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_3[gruppa];
    if(regUst<TIMEOUT_MTZ3_MIN/10 || regUst>TIMEOUT_MTZ3_MAX/10) diapazon=0;
    break;
  case 52:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_3_n_vpered[gruppa];
    if(regUst<TIMEOUT_MTZ3_N_VPERED_MIN/10 || regUst>TIMEOUT_MTZ3_N_VPERED_MAX/10) diapazon=0;
    break;
  case 53:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_3_n_nazad[gruppa];
    if(regUst<TIMEOUT_MTZ3_N_NAZAD_MIN/10 || regUst>TIMEOUT_MTZ3_N_NAZAD_MAX/10) diapazon=0;
    break;
  case 54:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_3_po_napruzi[gruppa];
    if(regUst<TIMEOUT_MTZ3_PO_NAPRUZI_MIN/10 || regUst>TIMEOUT_MTZ3_PO_NAPRUZI_MAX/10) diapazon=0;
    break;

//  int count_bit = 68;
  case 63:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_mtz_4[gruppa];
    if(regUst<SETPOINT_MTZ4_MIN/10 || regUst>SETPOINT_MTZ4_MAX/10) diapazon=0;
    break;
  case 64:
    (*editValue) = &edition_settings.setpoint_mtz_4_n_vpered[gruppa];
    if(regUst<SETPOINT_MTZ4_N_VPERED_MIN/10 || regUst>SETPOINT_MTZ4_N_VPERED_MAX/10) diapazon=0;
    break;
  case 65:
    (*editValue) = &edition_settings.setpoint_mtz_4_n_nazad[gruppa];
    if(regUst<SETPOINT_MTZ4_N_NAZAD_MIN/10 || regUst>SETPOINT_MTZ4_N_NAZAD_MAX/10) diapazon=0;
    break;
  case 66:
    (*editValue) = &edition_settings.setpoint_mtz_4_po_napruzi[gruppa];
    if(regUst<SETPOINT_MTZ4_PO_NAPRUZI_MIN/10 || regUst>SETPOINT_MTZ4_PO_NAPRUZI_MAX/10) diapazon=0;
    break;
  case 67:
    (*editValue) = &edition_settings.setpoint_mtz_4_U[gruppa];
    if(regUst<SETPOINT_MTZ4_U_MIN/10 || regUst>SETPOINT_MTZ4_U_MAX/10) diapazon=0;
    break;
  case 68:
    (*multer) = 1;
    (*editValue) = &edition_settings.setpoint_mtz_4_angle[gruppa];
    if(regUst<SETPOINT_MTZ4_ANGLE_MIN || regUst>SETPOINT_MTZ4_ANGLE_MAX) diapazon=0;
    break;
  case 69:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_4[gruppa];
    if(regUst<TIMEOUT_MTZ4_MIN/10 || regUst>TIMEOUT_MTZ4_MAX/10) diapazon=0;
    break;
  case 70:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_4_n_vpered[gruppa];
    if(regUst<TIMEOUT_MTZ4_N_VPERED_MIN/10 || regUst>TIMEOUT_MTZ4_N_VPERED_MAX/10) diapazon=0;
    break;
  case 71:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_4_n_nazad[gruppa];
    if(regUst<TIMEOUT_MTZ4_N_NAZAD_MIN/10 || regUst>TIMEOUT_MTZ4_N_NAZAD_MAX/10) diapazon=0;
    break;
  case 72:
    (*editValue) = (uint32_t*)&edition_settings.timeout_mtz_4_po_napruzi[gruppa];
    if(regUst<TIMEOUT_MTZ4_PO_NAPRUZI_MIN/10 || regUst>TIMEOUT_MTZ4_PO_NAPRUZI_MAX/10) diapazon=0;
    break;

//  count_bit = 2;
  case 82:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_zz_3I0[gruppa];
    if(regUst<SETPOINT_ZZ_3I0_MIN || regUst>SETPOINT_ZZ_3I0_MAX) diapazon=0;
    break;
  case 83:
    (*editValue) = (uint32_t*)&edition_settings.timeout_zz_3I0[gruppa];
    if(regUst<TIMEOUT_ZZ_3I0_MIN/10 || regUst>TIMEOUT_ZZ_3I0_MAX/10) diapazon=0;
    break;

//  count_bit = 2;
  case 86:
    (*editValue) = &edition_settings.setpoint_zz_3U0[gruppa];
    if(regUst<SETPOINT_ZZ_3U0_MIN/10 || regUst>SETPOINT_ZZ_3U0_MAX/10) diapazon=0;
    break;
  case 87:
    (*editValue) = (uint32_t*)&edition_settings.timeout_zz_3U0[gruppa];
    if(regUst<TIMEOUT_ZZ_3U0_MIN/10 || regUst>TIMEOUT_ZZ_3U0_MAX/10) diapazon=0;
    break;

//  count_bit = 1;
  case 89:
    (*editValue) = (uint32_t*)&edition_settings.timeout_nzz[gruppa];
    if(regUst<TIMEOUT_NZZ_MIN/10 || regUst>TIMEOUT_NZZ_MAX/10) diapazon=0;
    break;

//  count_bit = 1;
  case 92:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_1_3I0_vpered[gruppa];
    if(regUst<SETPOINT_TZNP1_3I0_VPERED_MIN/10 || regUst>SETPOINT_TZNP1_3I0_VPERED_MAX/10) diapazon=0;
    break;
  case 93:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_1_3U0_vpered[gruppa];
    if(regUst<SETPOINT_TZNP1_3U0_VPERED_MIN/10 || regUst>SETPOINT_TZNP1_3U0_VPERED_MAX/10) diapazon=0;
    break;
  case 94:
    (*editValue) = (uint32_t*)&edition_settings.timeout_tznp_1_vpered[gruppa];
    if(regUst<TIMEOUT_TZNP1_VPERED_MIN/10 || regUst>TIMEOUT_TZNP1_VPERED_MAX/10) diapazon=0;
    break;
  case 95:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_1_3I0_nazad[gruppa];
    if(regUst<SETPOINT_TZNP1_3I0_NAZAD_MIN/10 || regUst>SETPOINT_TZNP1_3I0_NAZAD_MAX/10) diapazon=0;
    break;
  case 96:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_1_3U0_nazad[gruppa];
    if(regUst<SETPOINT_TZNP1_3U0_NAZAD_MIN/10 || regUst>SETPOINT_TZNP1_3U0_NAZAD_MAX/10) diapazon=0;
    break;
  case 97:
    (*editValue) = (uint32_t*)&edition_settings.timeout_tznp_1_nazad[gruppa];
    if(regUst<TIMEOUT_TZNP1_NAZAD_MIN/10 || regUst>TIMEOUT_TZNP1_NAZAD_MAX/10) diapazon=0;
    break;
  case 98:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_1_angle[gruppa];
    if(regUst<SETPOINT_TZNP1_ANGLE_MIN || regUst>SETPOINT_TZNP1_ANGLE_MAX) diapazon=0;
    break;
  case 99:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_2_3I0_vpered[gruppa];
    if(regUst<SETPOINT_TZNP2_3I0_VPERED_MIN/10 || regUst>SETPOINT_TZNP2_3I0_VPERED_MAX/10) diapazon=0;
    break;
  case 100:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_2_3U0_vpered[gruppa];
    if(regUst<SETPOINT_TZNP2_3U0_VPERED_MIN/10 || regUst>SETPOINT_TZNP2_3U0_VPERED_MAX/10) diapazon=0;
    break;
  case 101:
    (*editValue) = (uint32_t*)&edition_settings.timeout_tznp_2_vpered[gruppa];
    if(regUst<TIMEOUT_TZNP2_VPERED_MIN/10 || regUst>TIMEOUT_TZNP2_VPERED_MAX/10) diapazon=0;
    break;
  case 102:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_2_3I0_nazad[gruppa];
    if(regUst<SETPOINT_TZNP2_3I0_NAZAD_MIN/10 || regUst>SETPOINT_TZNP2_3I0_NAZAD_MAX/10) diapazon=0;
    break;
  case 103:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_2_3U0_nazad[gruppa];
    if(regUst<SETPOINT_TZNP2_3U0_NAZAD_MIN/10 || regUst>SETPOINT_TZNP2_3U0_NAZAD_MAX/10) diapazon=0;
    break;
  case 104:
    (*editValue) = (uint32_t*)&edition_settings.timeout_tznp_2_nazad[gruppa];
    if(regUst<TIMEOUT_TZNP2_NAZAD_MIN/10 || regUst>TIMEOUT_TZNP2_NAZAD_MAX/10) diapazon=0;
    break;
  case 105:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_2_angle[gruppa];
    if(regUst<SETPOINT_TZNP2_ANGLE_MIN || regUst>SETPOINT_TZNP2_ANGLE_MAX) diapazon=0;
    break;
  case 106:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_3_3I0_vpered[gruppa];
    if(regUst<SETPOINT_TZNP3_3I0_VPERED_MIN/10 || regUst>SETPOINT_TZNP3_3I0_VPERED_MAX/10) diapazon=0;
    break;
  case 107:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_3_3U0_vpered[gruppa];
    if(regUst<SETPOINT_TZNP3_3U0_VPERED_MIN/10 || regUst>SETPOINT_TZNP3_3U0_VPERED_MAX/10) diapazon=0;
    break;
  case 108:
    (*editValue) = (uint32_t*)&edition_settings.timeout_tznp_3_vpered[gruppa];
    if(regUst<TIMEOUT_TZNP3_VPERED_MIN/10 || regUst>TIMEOUT_TZNP3_VPERED_MAX/10) diapazon=0;
    break;
  case 109:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_3_3I0_nazad[gruppa];
    if(regUst<SETPOINT_TZNP3_3I0_NAZAD_MIN/10 || regUst>SETPOINT_TZNP3_3I0_NAZAD_MAX/10) diapazon=0;
    break;
  case 110:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_3_3U0_nazad[gruppa];
    if(regUst<SETPOINT_TZNP3_3U0_NAZAD_MIN/10 || regUst>SETPOINT_TZNP3_3U0_NAZAD_MAX/10) diapazon=0;
    break;
  case 111:
    (*editValue) = (uint32_t*)&edition_settings.timeout_tznp_3_nazad[gruppa];
    if(regUst<TIMEOUT_TZNP3_NAZAD_MIN/10 || regUst>TIMEOUT_TZNP3_NAZAD_MAX/10) diapazon=0;
    break;
  case 112:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_tznp_3_angle[gruppa];
    if(regUst<SETPOINT_TZNP3_ANGLE_MIN || regUst>SETPOINT_TZNP3_ANGLE_MAX) diapazon=0;
    break;

  case 113:
    (*multer) = 1;
    (*editValue) = &edition_settings.setpoint_zop[gruppa];
    if(regUst<SETPOINT_ZOP_MIN || regUst>SETPOINT_ZOP_MAX) diapazon=0;
    break;
  case 114:
    (*editValue) = (uint32_t*)&edition_settings.timeout_zop[gruppa];
    if(regUst<TIMEOUT_ZOP_MIN/10 || regUst>TIMEOUT_ZOP_MAX/10) diapazon=0;
    break;

//  count_bit = 10;
  case 120:
    (*multer) = 100;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_Umin1[gruppa];
    if(regUst<SETPOINT_UMIN1_MIN/100 || regUst>SETPOINT_UMIN1_MAX/100) diapazon=0;
    break;
  case 121:
    (*editValue) = (uint32_t*)&edition_settings.timeout_Umin1[gruppa];
    if(regUst<TIMEOUT_UMIN1_MIN/10 || regUst>TIMEOUT_UMIN1_MAX/10) diapazon=0;
    break;
  case 122:
    (*multer) = 100;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_Umin2[gruppa];
    if(regUst<SETPOINT_UMIN2_MIN/100 || regUst>SETPOINT_UMIN2_MAX/100) diapazon=0;
    break;
  case 123:
    (*editValue) = (uint32_t*)&edition_settings.timeout_Umin2[gruppa];
    if(regUst<TIMEOUT_UMIN2_MIN/10 || regUst>TIMEOUT_UMIN2_MAX/10) diapazon=0;
    break;
  case 124:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_Umin1_Iblk[gruppa];
    if(regUst<SETPOINT_UMIN1_IBLK_MIN/10 || regUst>SETPOINT_UMIN1_IBLK_MAX/10) diapazon=0;
    break;
  case 125:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_Umin2_Iblk[gruppa];
    if(regUst<SETPOINT_UMIN2_IBLK_MIN/10 || regUst>SETPOINT_UMIN2_IBLK_MAX/10) diapazon=0;
    break;

  case 126:
    (*multer) = 100;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_Umax1[gruppa];
    if(regUst<SETPOINT_UMAX1_MIN/100 || regUst>SETPOINT_UMAX1_MAX/100) diapazon=0;
    break;
  case 127:
    (*editValue) = (uint32_t*)&edition_settings.timeout_Umax1[gruppa];
    if(regUst<TIMEOUT_UMAX1_MIN/10 || regUst>TIMEOUT_UMAX1_MAX/10) diapazon=0;
    break;
  case 128:
    (*multer) = 100;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_Umax2[gruppa];
    if(regUst<SETPOINT_UMAX2_MIN/100 || regUst>SETPOINT_UMAX2_MAX/100) diapazon=0;
    break;
  case 129:
    (*editValue) = (uint32_t*)&edition_settings.timeout_Umax2[gruppa];
    if(regUst<TIMEOUT_UMAX2_MIN/10 || regUst>TIMEOUT_UMAX2_MAX/10) diapazon=0;
    break;
  case 130:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_kp_Umax[gruppa];
    if(regUst<SETPOINT_KP_UMAX_MIN || regUst>SETPOINT_KP_UMAX_MAX) diapazon=0;
    break;

//  count_bit = 4;
  case 146:
    (*editValue) = &edition_settings.setpoint_urov[gruppa];
    if(regUst<SETPOINT_UROV_MIN/10 || regUst>SETPOINT_UROV_MAX/10) diapazon=0;
    break;
  case 147:
    (*editValue) = (uint32_t*)&edition_settings.timeout_urov_1[gruppa];
    if(regUst<TIMEOUT_UROV1_MIN/10 || regUst>TIMEOUT_UROV1_MAX/10) diapazon=0;
    break;
  case 148:
    (*editValue) = (uint32_t*)&edition_settings.timeout_urov_2[gruppa];
    if(regUst<TIMEOUT_UROV2_MIN/10 || regUst>TIMEOUT_UROV2_MAX/10) diapazon=0;
    break;

//  count_bit = 10;
  case 179:
    (*editValue) = (uint32_t*)&edition_settings.timeout_apv_block_vid_VV[gruppa];
    if(regUst<TIMEOUT_APV_BLOCK_VID_VV_MIN/10 || regUst>TIMEOUT_APV_BLOCK_VID_VV_MAX/10) diapazon=0;
    break;
  case 180:
  {
    (*editValue) = (uint32_t*)&edition_settings.timeout_apv_1[gruppa];
    if(regUst<TIMEOUT_APV1_MIN/10 || regUst>TIMEOUT_APV1_MAX/10) diapazon=0;
  }
  break;
  case 181:
    (*editValue) = (uint32_t*)&edition_settings.timeout_apv_2[gruppa];
    if(regUst<TIMEOUT_APV2_MIN/10 || regUst>TIMEOUT_APV2_MAX/10) diapazon=0;
    break;
  case 182:
    (*editValue) = (uint32_t*)&edition_settings.timeout_apv_3[gruppa];
    if(regUst<TIMEOUT_APV3_MIN/10 || regUst>TIMEOUT_APV3_MAX/10) diapazon=0;
    break;
  case 183:
    (*editValue) = (uint32_t*)&edition_settings.timeout_apv_4[gruppa];
    if(regUst<TIMEOUT_APV4_MIN/10 || regUst>TIMEOUT_APV4_MAX/10) diapazon=0;
    break;
  case 184:
    (*editValue) = (uint32_t*)&edition_settings.timeout_apv_block_vid_apv1[gruppa];
    if(regUst<TIMEOUT_APV_BLOCK_VID_APV1_MIN/10 || regUst>TIMEOUT_APV_BLOCK_VID_APV1_MAX/10) diapazon=0;
    break;
  case 185:
    (*editValue) = (uint32_t*)&edition_settings.timeout_apv_block_vid_apv2[gruppa];
    if(regUst<TIMEOUT_APV_BLOCK_VID_APV2_MIN/10 || regUst>TIMEOUT_APV_BLOCK_VID_APV2_MAX/10) diapazon=0;
    break;
  case 186:
    (*editValue) = (uint32_t*)&edition_settings.timeout_apv_block_vid_apv3[gruppa];
    if(regUst<TIMEOUT_APV_BLOCK_VID_APV3_MIN/10 || regUst>TIMEOUT_APV_BLOCK_VID_APV3_MAX/10) diapazon=0;
    break;
  case 187:
    (*editValue) = (uint32_t*)&edition_settings.timeout_apv_block_vid_apv4[gruppa];
    if(regUst<TIMEOUT_APV_BLOCK_VID_APV4_MIN/10 || regUst>TIMEOUT_APV_BLOCK_VID_APV4_MAX/10) diapazon=0;
    break;

//  count_bit = 9;
  case 195:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_achr1_f_rab[gruppa];
    if(regUst<SETPOINT_ACHR1_F_RAB_MIN/10 || regUst>SETPOINT_ACHR1_F_RAB_MAX/10) diapazon=0;
    break;
  case 196:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_achr2_f_rab[gruppa];
    if(regUst<SETPOINT_ACHR2_F_RAB_MIN/10 || regUst>SETPOINT_ACHR2_F_RAB_MAX/10) diapazon=0;
    break;
  case 197:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_chapv1_f_rab[gruppa];
    if(regUst<SETPOINT_CHAPV1_F_RAB_MIN/10 || regUst>SETPOINT_CHAPV1_F_RAB_MAX/10) diapazon=0;
    break;
  case 198:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_chapv2_f_rab[gruppa];
    if(regUst<SETPOINT_CHAPV2_F_RAB_MIN/10 || regUst>SETPOINT_CHAPV2_F_RAB_MAX/10) diapazon=0;
    break;
  case 199:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_achr_chapv_uf[gruppa];
    if(regUst<SETPOINT_ACHR_CHAPV_UF_MIN/10 || regUst>SETPOINT_ACHR_CHAPV_UF_MAX/10) diapazon=0;
    break;
  case 200:
    (*editValue) = (uint32_t*)&edition_settings.timeout_achr_1[gruppa];
    if(regUst<TIMEOUT_ACHR1_MIN/10 || regUst>TIMEOUT_ACHR1_MAX/10) diapazon=0;
    break;
  case 201:
    (*editValue) = (uint32_t*)&edition_settings.timeout_achr_2[gruppa];
    if(regUst<TIMEOUT_ACHR2_MIN/10 || regUst>TIMEOUT_ACHR2_MAX/10) diapazon=0;
    break;
  case 202:
    (*editValue) = (uint32_t*)&edition_settings.timeout_chapv_1[gruppa];
    if(regUst<TIMEOUT_CHAPV1_MIN/10 || regUst>TIMEOUT_CHAPV1_MAX/10) diapazon=0;
    break;
  case 203:
    (*editValue) = (uint32_t*)&edition_settings.timeout_chapv_2[gruppa];
    if(regUst<TIMEOUT_CHAPV2_MIN/10 || regUst>TIMEOUT_CHAPV2_MAX/10) diapazon=0;
    break;

//  count_bit = 9;
  case 258:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.pickup_dz_k[gruppa];
    if(regUst<PICKUP_DZ_K_MIN || regUst>PICKUP_DZ_K_MAX) diapazon=0;
    break;
  case 259:
    (*editValue) = (uint32_t*)&edition_settings.pickup_dz1[gruppa];
    if(regUst<PICKUP_DZ1_MIN/10 || regUst>PICKUP_DZ1_MAX/10) diapazon=0;
    break;
  case 260:
    (*editValue) = (uint32_t*)&edition_settings.pickup_dz1_amtz[gruppa];
    if(regUst<PICKUP_DZ1_AMTZ_MIN/10 || regUst>PICKUP_DZ1_AMTZ_MAX/10) diapazon=0;
    break;
  case 261:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz1[gruppa];
    if(regUst<TIMEOUT_DZ1_MIN/10 || regUst>TIMEOUT_DZ1_MAX/10) diapazon=0;
    break;
  case 262:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz1_amtz[gruppa];
    if(regUst<TIMEOUT_DZ1_AMTZ_MIN/10 || regUst>TIMEOUT_DZ1_AMTZ_MAX/10) diapazon=0;
    break;
  case 263:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.pickup_dz2_angle[gruppa];
    //if(regUst<PICKUP_DZ2_ANGLE_MIN || regUst>PICKUP_DZ2_ANGLE_MAX) diapazon=0;
    if(regUst>65000 && regUst<65536+PICKUP_DZ2_ANGLE_MIN) diapazon=0;
    if(regUst<65000 && regUst>PICKUP_DZ2_ANGLE_MAX) diapazon=0;
    break;
  case 264:
    (*editValue) = (uint32_t*)&edition_settings.pickup_dz2_dir[gruppa];
    if(regUst<PICKUP_DZ2_DIR_MIN/10 || regUst>PICKUP_DZ2_DIR_MAX/10) diapazon=0;
    break;
  case 265:
    (*editValue) = (uint32_t*)&edition_settings.pickup_dz2_inv[gruppa];
    if(regUst<PICKUP_DZ2_INV_MIN/10 || regUst>PICKUP_DZ2_INV_MAX/10) diapazon=0;
    break;
  case 266:
    (*editValue) = (uint32_t*)&edition_settings.pickup_dz2_amtz[gruppa];
    if(regUst<PICKUP_DZ2_AMTZ_MIN/10 || regUst>PICKUP_DZ2_AMTZ_MAX/10) diapazon=0;
    break;
  case 267:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz2_dir[gruppa];
    if(regUst<TIMEOUT_DZ2_DIR_MIN/10 || regUst>TIMEOUT_DZ2_DIR_MAX/10) diapazon=0;
    break;
  case 268:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz2_dir_pr[gruppa];
    if(regUst<TIMEOUT_DZ2_DIR_PR_MIN/10 || regUst>TIMEOUT_DZ2_DIR_PR_MAX/10) diapazon=0;
    break;
  case 269:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz2_inv[gruppa];
    if(regUst<TIMEOUT_DZ2_INV_MIN/10 || regUst>TIMEOUT_DZ2_INV_MAX/10) diapazon=0;
    break;
  case 270:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz2_inv_pr[gruppa];
    if(regUst<TIMEOUT_DZ2_INV_PR_MIN/10 || regUst>TIMEOUT_DZ2_INV_PR_MAX/10) diapazon=0;
    break;
  case 271:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz2_amtz[gruppa];
    if(regUst<TIMEOUT_DZ2_AMTZ_MIN/10 || regUst>TIMEOUT_DZ2_AMTZ_MAX/10) diapazon=0;
    break;
  case 272:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz2_amtz_pr[gruppa];
    if(regUst<TIMEOUT_DZ2_AMTZ_PR_MIN/10 || regUst>TIMEOUT_DZ2_AMTZ_PR_MAX/10) diapazon=0;
    break;
  case 273:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz2_vvid_pr[gruppa];
    if(regUst<TIMEOUT_DZ2_VVID_PR_MIN/10 || regUst>TIMEOUT_DZ2_VVID_PR_MAX/10) diapazon=0;
    break;
  case 274:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz2_amtz_vvid_pr[gruppa];
    if(regUst<TIMEOUT_DZ2_AMTZ_VVID_PR_MIN/10 || regUst>TIMEOUT_DZ2_AMTZ_VVID_PR_MAX/10) diapazon=0;
    break;
  case 275:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.pickup_dz3_angle[gruppa];
//    if(regUst<PICKUP_DZ3_ANGLE_MIN || regUst>PICKUP_DZ3_ANGLE_MAX) diapazon=0;
    if(regUst>65000 && regUst<65536+PICKUP_DZ3_ANGLE_MIN) diapazon=0;
    if(regUst<65000 && regUst>PICKUP_DZ3_ANGLE_MAX) diapazon=0;
    break;
  case 276:
    (*editValue) = (uint32_t*)&edition_settings.pickup_dz3_dir[gruppa];
    if(regUst<PICKUP_DZ3_DIR_MIN/10 || regUst>PICKUP_DZ3_DIR_MAX/10) diapazon=0;
    break;
  case 277:
    (*editValue) = (uint32_t*)&edition_settings.pickup_dz3_inv[gruppa];
    if(regUst<PICKUP_DZ3_INV_MIN/10 || regUst>PICKUP_DZ3_INV_MAX/10) diapazon=0;
    break;
  case 278:
    (*editValue) = (uint32_t*)&edition_settings.pickup_dz3_amtz[gruppa];
    if(regUst<PICKUP_DZ3_AMTZ_MIN/10 || regUst>PICKUP_DZ3_AMTZ_MAX/10) diapazon=0;
    break;
  case 279:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz3_dir[gruppa];
    if(regUst<TIMEOUT_DZ3_DIR_MIN/10 || regUst>TIMEOUT_DZ3_DIR_MAX/10) diapazon=0;
    break;
  case 280:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz3_dir_pr[gruppa];
    if(regUst<TIMEOUT_DZ3_DIR_PR_MIN/10 || regUst>TIMEOUT_DZ3_DIR_PR_MAX/10) diapazon=0;
    break;
  case 281:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz3_inv[gruppa];
    if(regUst<TIMEOUT_DZ3_INV_MIN/10 || regUst>TIMEOUT_DZ3_INV_MAX/10) diapazon=0;
    break;
  case 282:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz3_inv_pr[gruppa];
    if(regUst<TIMEOUT_DZ3_INV_PR_MIN/10 || regUst>TIMEOUT_DZ3_INV_PR_MAX/10) diapazon=0;
    break;
  case 283:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz3_amtz[gruppa];
    if(regUst<TIMEOUT_DZ3_AMTZ_MIN/10 || regUst>TIMEOUT_DZ3_AMTZ_MAX/10) diapazon=0;
    break;
  case 284:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz3_amtz_pr[gruppa];
    if(regUst<TIMEOUT_DZ3_AMTZ_PR_MIN/10 || regUst>TIMEOUT_DZ3_AMTZ_PR_MAX/10) diapazon=0;
    break;
  case 285:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz3_vvid_pr[gruppa];
    if(regUst<TIMEOUT_DZ3_VVID_PR_MIN/10 || regUst>TIMEOUT_DZ3_VVID_PR_MAX/10) diapazon=0;
    break;
  case 286:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz3_amtz_vvid_pr[gruppa];
    if(regUst<TIMEOUT_DZ3_AMTZ_VVID_PR_MIN/10 || regUst>TIMEOUT_DZ3_AMTZ_VVID_PR_MAX/10) diapazon=0;
    break;
  case 287:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.pickup_dz4_angle[gruppa];
//    if(regUst<PICKUP_DZ4_ANGLE_MIN || regUst>PICKUP_DZ4_ANGLE_MAX) diapazon=0;
    if(regUst>65000 && regUst<65536+PICKUP_DZ4_ANGLE_MIN) diapazon=0;
    if(regUst<65000 && regUst>PICKUP_DZ4_ANGLE_MAX) diapazon=0;
    break;
  case 288:
    (*editValue) = (uint32_t*)&edition_settings.pickup_dz4_dir[gruppa];
    if(regUst<PICKUP_DZ4_DIR_MIN/10 || regUst>PICKUP_DZ4_DIR_MAX/10) diapazon=0;
    break;
  case 289:
    (*editValue) = (uint32_t*)&edition_settings.pickup_dz4_inv[gruppa];
    if(regUst<PICKUP_DZ4_INV_MIN/10 || regUst>PICKUP_DZ4_INV_MAX/10) diapazon=0;
    break;
  case 290:
    (*editValue) = (uint32_t*)&edition_settings.pickup_dz4_amtz[gruppa];
    if(regUst<PICKUP_DZ4_AMTZ_MIN/10 || regUst>PICKUP_DZ4_AMTZ_MAX/10) diapazon=0;
    break;
  case 291:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz4_dir[gruppa];
    if(regUst<TIMEOUT_DZ4_DIR_MIN/10 || regUst>TIMEOUT_DZ4_DIR_MAX/10) diapazon=0;
    break;
  case 292:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz4_dir_pr[gruppa];
    if(regUst<TIMEOUT_DZ4_DIR_PR_MIN/10 || regUst>TIMEOUT_DZ4_DIR_PR_MAX/10) diapazon=0;
    break;
  case 293:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz4_inv[gruppa];
    if(regUst<TIMEOUT_DZ4_INV_MIN/10 || regUst>TIMEOUT_DZ4_INV_MAX/10) diapazon=0;
    break;
  case 294:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz4_inv_pr[gruppa];
    if(regUst<TIMEOUT_DZ4_INV_PR_MIN/10 || regUst>TIMEOUT_DZ4_INV_PR_MAX/10) diapazon=0;
    break;
  case 295:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz4_amtz[gruppa];
    if(regUst<TIMEOUT_DZ4_AMTZ_MIN/10 || regUst>TIMEOUT_DZ4_AMTZ_MAX/10) diapazon=0;
    break;
  case 296:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz4_amtz_pr[gruppa];
    if(regUst<TIMEOUT_DZ4_AMTZ_PR_MIN/10 || regUst>TIMEOUT_DZ4_AMTZ_PR_MAX/10) diapazon=0;
    break;
  case 297:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz4_vvid_pr[gruppa];
    if(regUst<TIMEOUT_DZ4_VVID_PR_MIN/10 || regUst>TIMEOUT_DZ4_VVID_PR_MAX/10) diapazon=0;
    break;
  case 298:
    (*editValue) = (uint32_t*)&edition_settings.timeout_dz4_amtz_vvid_pr[gruppa];
    if(regUst<TIMEOUT_DZ4_AMTZ_VVID_PR_MIN/10 || regUst>TIMEOUT_DZ4_AMTZ_VVID_PR_MAX/10) diapazon=0;
    break;
  case 299:
    (*editValue) = (uint32_t*)&edition_settings.timeout_nkn_dz[gruppa];
    if(regUst<TIMEOUT_NKN_DZ_MIN/10 || regUst>TIMEOUT_NKN_DZ_MAX/10) diapazon=0;
    break;

//IF ВСТАВКА 213-244

#define MARKER248  248
  case MARKER248:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.ctrl_zdz_type;
    if(regUst<0 || regUst>5) diapazon=0;
    break;
  case 249:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.timeout_zdz[gruppa];
    if(regUst<TIMEOUT_ZDZ_MIN || regUst>TIMEOUT_ZDZ_MAX) diapazon=0;
    break;

//  count_bit = 9;
  case 1029:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.lines[0];
    if(regUst<NUMBER_LINES_FORWARD_MIN || regUst>NUMBER_LINES_MAX) diapazon=0;
    break;

//IF ВСТАВКА 1030-1045

  case 1046:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.lines[1];
    if(regUst<NUMBER_LINES_BACKWARD_MIN || regUst>NUMBER_LINES_MAX) diapazon=0;
    break;

//IF ВСТАВКА 1047-1062

//  count_bit = 9;
  case 1063:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.TVoltage;
    if(regUst<KOEF_TN_MIN || regUst>KOEF_TN_MAX) diapazon=0;
    break;

//  count_bit = 9;
  case 1065:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.TCurrent;
    if(regUst<KOEF_TT_MIN || regUst>KOEF_TT_MAX) diapazon=0;
    break;
  case 1066:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.T0;
    if(regUst<KOEF_TO_MIN || regUst>KOEF_TO_MAX) diapazon=0;
    break;

//  count_bit = 9;
  case 1068:
    (*editValue) = (uint32_t*)&edition_settings.timeout_swch_udl_blk_on;
    if(regUst<TIMEOUT_SWCH_UDL_BLK_ON_MIN/10 || regUst>TIMEOUT_SWCH_UDL_BLK_ON_MAX/10) diapazon=0;
    break;
  case 1069:
    (*editValue) = (uint32_t*)&edition_settings.timeout_swch_on;
    if(regUst<TIMEOUT_SWCH_ON_MIN/10 || regUst>TIMEOUT_SWCH_ON_MAX/10) diapazon=0;
    break;
  case 1070:
    (*editValue) = (uint32_t*)&edition_settings.timeout_swch_off;
    if(regUst<TIMEOUT_SWCH_OFF_MIN/10 || regUst>TIMEOUT_SWCH_OFF_MAX/10) diapazon=0;
    break;
  case 1071:
    (*editValue) = (uint32_t*)&edition_settings.timeout_pryvoda_VV;
    if(regUst<TIMEOUT_PRYVODA_VV_MIN/10 || regUst>TIMEOUT_PRYVODA_VV_MAX/10) diapazon=0;
    break;

//  count_bit = 9;
  case 1075:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_Inom;
    if(regUst<SETPOINT_Inom_MIN || regUst>SETPOINT_Inom_MAX) diapazon=0;
    break;
  case 1076:
    (*editValue) = (uint32_t*)&edition_settings.setpoint_r_kom_st_Inom;
    if(regUst<SETPOINT_RKS_Inom_MIN/10 || regUst>SETPOINT_RKS_Inom_MAX/10) diapazon=0;
    break;
  case 1077:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_Inom_vymk;
    if(regUst<SETPOINT_Inom_vymk_MIN || regUst>SETPOINT_Inom_vymk_MAX) diapazon=0;
    break;
  case 1078:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_r_kom_st_Inom_vymk;
    if(regUst<SETPOINT_RKS_Inom_vymk_MIN || regUst>SETPOINT_RKS_Inom_vymk_MAX) diapazon=0;
    break;
#define MARKER1079  1079
  case MARKER1079:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_pochatkovyj_resurs;
    break;
#define MARKER1080  1080
  case MARKER1080:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_pochatkovyj_resurs;
    break;
#define MARKER1081  1081
  case MARKER1081:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_krytychnyj_resurs;
    break;
#define MARKER1082  1082
  case MARKER1082:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_pochatkova_k_vymk;
    break;
#define MARKER1083  1083
  case MARKER1083:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.setpoint_pochatkova_k_vymk;
    break;

//  count_bit = 9;
#define MARKER1088  1088
  case MARKER1088:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_of_input_signal;
//      if(regUst&(~(0xFFFF))) diapazon=0;
    break;
  case 1089:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_of_input_signal;
    if(regUst&(~(0xF))) diapazon=0;
    break;
#define MARKER1090  1090
  case MARKER1090:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_of_input;
    break;
  case 1091:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_of_input;
    if(regUst&(~(0xF))) diapazon=0;
    break;
  case 1092:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_of_output;
    break;
  case 1093:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_of_output_modif;
    break;
  case 1094:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_df;
    if(regUst&(~(0xFF))) diapazon=0;
    break;
#define MARKER1095  1095
  case MARKER1095:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_of_led;
    break;
  case 1096:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.type_of_led;
    if(regUst&(~(0x1))) diapazon=0;
    break;
  case 1097:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.buttons_mode;
    if(regUst&(~(0xFFF))) diapazon=0;
    for(int bit=0; bit<NUMBER_DEFINED_BUTTONS; bit++)
    {
      if((regUst&(3<<(bit*2)))==(0x2<<(bit*2))) diapazon=0;
      if((regUst&(3<<(bit*2)))==(0x3<<(bit*2))) diapazon=0;
    }//for
    //Зміна режиму відбудеться у цій функції рахом з можливими змінами у ранжуванні ФК
    if(actControl)
    {
      action_during_changing_button_mode(&current_settings_interfaces, &edition_settings);
      //Перебираємо всі ФК
      for (size_t number = 0; number < NUMBER_DEFINED_BUTTONS; number++)
      {
        for (unsigned int i = 0; i < N_SMALL; i++)
        {
          edition_settings.ranguvannja_buttons[N_SMALL*number + i] =
            current_settings_interfaces.ranguvannja_buttons[N_SMALL*number + i];
        }//for
      }//for
    }//if
    break;

//IF ВСТАВКА 1098-1117
//IF ВСТАВКА 1118-1125
//IF ВСТАВКА 1128-1135

#if (                                   \
     (MODYFIKACIA_VERSII_PZ == 0) ||    \
     (MODYFIKACIA_VERSII_PZ == 3)       \
    )   
  case 1600:
    (*multer) = 1;
    (*editValue) = (uint32_t*)&edition_settings.zdz_ovd_porig;
    if(regUst<0 || regUst>(ZDZ_CTRL_PORIG_N-1)) diapazon=0;
    break;
#endif

  }//switch
  if(inOffset>=7 && inOffset<15)
  {
    //УЗ
    int item = inOffset-7;
    (*editValue) = (uint32_t*)&edition_settings.ctrl_UP_input[item];
    (*multer) = 1;
//    if(regUst<0 || regUst>19) diapazon=0;
    if(actControl)
      if(regUst!=current_settings_interfaces.ctrl_UP_input[item])
      {
        uint32_t tmp = edition_settings.ctrl_UP_input[item];
        edition_settings.ctrl_UP_input[item] = -1;
        action_after_changing_input_UP(&edition_settings, item, tmp);
      }//if(actControl)
  }//if(inOffset>=7 && inOffset<15)
  if(inOffset>=213 && inOffset<245)
  {
    //УЗ
    int item = inOffset-213;
    switch(item%4)
    {
    case 0:
    case 1:
      (*editValue) = (uint32_t*)&edition_settings.setpoint_UP[item/4][0][gruppa];
      break;
    case 2:
      (*editValue) = (uint32_t*)&edition_settings.timeout_UP[item/4][0][gruppa];
      break;
    case 3:
      (*multer) = 1;
      (*editValue) = (uint32_t*)&edition_settings.setpoint_UP_KP[item/4][0][gruppa];
      break;
    }//switch

    if((item%4)==0 || (item%4)==1)
      switch(edition_settings.ctrl_UP_input[item/4])
      {
      case UP_CTRL_Ia_Ib_Ic:
      case UP_CTRL_Ia:
      case UP_CTRL_Ib:
      case UP_CTRL_Ic:
      case UP_CTRL_I1:
      case UP_CTRL_I2:
      case UP_CTRL_3I0_r:
        if((item%4)==1)
        {
          if(regUst!=0) diapazon=0;//нет старшего регистра
        }//if
        else if(regUst<SETPOINT_UP_I_MIN/10 || regUst>SETPOINT_UP_I_MAX/10) diapazon=0;
        break;
      case UP_CTRL_3I0:
      case UP_CTRL_3I0_others:
        (*multer) = 1;
        if((item%4)==1)
        {
          if(regUst!=0) diapazon=0;//нет старшего регистра
        }//if
        else if(regUst<SETPOINT_UP_3I0_MIN || regUst>SETPOINT_UP_3I0_MAX) diapazon=0;
        break;
      case UP_CTRL_Ua_Ub_Uc:
      case UP_CTRL_Uab_Ubc_Uca:
      case UP_CTRL_Ua:
      case UP_CTRL_Uab:
      case UP_CTRL_Ub:
      case UP_CTRL_Ubc:
      case UP_CTRL_Uc:
      case UP_CTRL_Uca:
      case UP_CTRL_U1:
      case UP_CTRL_U2:
      case UP_CTRL_3U0:
        (*multer) = 100;
        if((item%4)==1)
        {
          if(regUst!=0) diapazon=0;//нет старшего регистра
        }//if
        else if(regUst<SETPOINT_UP_U_MIN/100 || regUst>SETPOINT_UP_U_MAX/100) diapazon=0;
        break;
      case UP_CTRL_P:
      case UP_CTRL_Q:
      case UP_CTRL_S:
        (*multer) = 1;
        break;
      }//switch

    if((item%4)==2)
      if(regUst<TIMEOUT_UP_MIN/10 || regUst>TIMEOUT_UP_MAX/10) diapazon=0;
    if((item%4)==3)
    {
      if(edition_settings.control_UP& (1<<(2+3*(item/4))))
      {
        if(regUst<SETPOINT_UP_KP_LESS_MIN || regUst>SETPOINT_UP_KP_LESS_MAX) diapazon=0;
      }//if(edition_settings.control_UP& (1<<(2+3*item/4)))
      else  if(regUst<SETPOINT_UP_KP_MORE_MIN || regUst>SETPOINT_UP_KP_MORE_MAX) diapazon=0;
    }//if((item%4)==3)
  }//if(inOffset>=213 && inOffset<245)

//IF ВСТАВКА 1030-1063
  if(inOffset>=1030 && inOffset<1063 && inOffset!=1046)
  {
  int item = 0;
  int direct = 0;
  if(inOffset>=1030 && inOffset<1046)
  {
    (*multer) = 1;
    item = inOffset-1030;
  }//if(inOffset>=988 && inOffset<1004)
  if(inOffset>=1047 && inOffset<1063)
  {
    (*multer) = 1;
    item = inOffset-1047;
    direct = 1;
  }//if(inOffset>=1005 && inOffset<1021)
  //unsigned int uRegUst = regUst&0xFFFF;
    switch(item%2)
    {
    case 0:
      (*editValue) = (uint32_t*)&edition_settings.dovgyna[direct][(item/2)%8];
      if(regUst<SETPOINT_DOVGYNA_VMP_MIN || regUst>SETPOINT_DOVGYNA_VMP_MAX) diapazon=0;
      break;
    case 1:
      (*editValue) = (uint32_t*)&edition_settings.opir[direct][(item/2)%8];
      if(regUst<SETPOINT_OPIR_VMP_MIN || regUst>SETPOINT_OPIR_VMP_MAX) diapazon=0;
      break;
    }//switch
  }//if(inOffset>=988 && inOffset<1021 && inOffset!=1004)

#if (MODYFIKACIA_VERSII_PZ == 0)
  if(inOffset>=1098 && inOffset<1117)
#endif
#if (                                   \
     (MODYFIKACIA_VERSII_PZ == 1) ||    \
     (MODYFIKACIA_VERSII_PZ == 3)       \
    )   
    if(inOffset>=1098 && inOffset<1113)
#endif
#if (MODYFIKACIA_VERSII_PZ == 2)
      if(inOffset>=1098 && inOffset<1105)
#endif
      {
        int item = inOffset-1098;
        (*editValue) = (uint32_t*)&edition_settings.dopusk_dv[item];
        (*multer) = 1;
        if(regUst<0 || regUst>60) diapazon=0;
      }//if

  if(inOffset>=1118 && inOffset<1126)
  {
    int item = inOffset-1118;
    (*editValue) = (uint32_t*)&edition_settings.timeout_pause_df[item];
    if(regUst<TIMEOUT_DF_PAUSE_MIN/10 || regUst>TIMEOUT_DF_PAUSE_MAX/10) diapazon=0;
  }//if(inOffset>=1076 && inOffset<1084)

  if(inOffset>=1128 && inOffset<1136)
  {
    int item = inOffset-1128;
    (*editValue) = (uint32_t*)&edition_settings.timeout_work_df[item];
    if(regUst<TIMEOUT_DF_WORK_MIN/10 || regUst>TIMEOUT_DF_WORK_MAX/10) diapazon=0;
  }//if(inOffset>=1076 && inOffset<1084)

  return diapazon;
} //ustFunc000(int inOffset, int gruppa, int *multer, int regUst, uint32_t **ustValue, uint32_t **editValue)

/**************************************/
//подготовка компонента UST
/**************************************/
void constructorUSTBigComponent(COMPONENT_OBJ *ustbigcomp)
{
  ustbigcomponent = ustbigcomp;

  ustbigcomponent->getModbusRegister = getUSTBigModbusRegister;//получить содержимое регистра
  ustbigcomponent->getModbusBit      = getUSTBigModbusBit;//получить содержимое бита
  ustbigcomponent->setModbusRegister = setUSTBigModbusRegister;//получить содержимое регистра
  ustbigcomponent->setModbusBit      = setUSTBigModbusBit;//получить содержимое бита

  ustbigcomponent->preReadAction   = preUSTBigReadAction;//action до чтения
  ustbigcomponent->preWriteAction  = preUSTBigWriteAction;//action до записи
  ustbigcomponent->postWriteAction = postUSTBigWriteAction;//action после записи

  ustbigcomponent->isActiveActualData = 0;
}//prepareDVinConfig

int getUSTBigModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateUSTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(ustbigcomponent->isActiveActualData)
  {
    edition_settings = current_settings_interfaces;//делаем копию
  }//if(uprbigcomponent->isActiveActualData)
  superClearActiveActualData();

  uint32_t *editValue=NULL;
  int  multer = 1;
  int  adresGruppa=0;
  int  grupa_ustavok=0;
  int  offset = adrReg-BEGIN_ADR_REGISTER;
  grupa_ustavok_control(offset, &grupa_ustavok, &adresGruppa);

  ustFunc000(offset -adresGruppa, grupa_ustavok, &multer, 0, &editValue);
  if(editValue==NULL) return 0;

  for(int item=0; item<NUMBER_UP; item++)
  {
   if(editValue == (uint32_t*)&edition_settings.ctrl_UP_input[item])
   {
     switch(*editValue)
     {
      case UP_CTRL_Ia_Ib_Ic:
       *editValue = 0;//(Ia+Ib+Ic)
      break;
      case UP_CTRL_Ia:
       *editValue = 1;//Ia;
      break;
      case UP_CTRL_Ib:
       *editValue = 2;//Ib;
      break;
      case UP_CTRL_Ic:
       *editValue = 3;//Ic;
      break;
      case UP_CTRL_I1:
       *editValue = 4;//I1;
      break;
      case UP_CTRL_I2:
       *editValue = 5;//I2;
      break;
      case UP_CTRL_3I0_r:
       *editValue = 7;//3I0-1
      break;
      case UP_CTRL_3I0:
       *editValue = 8;//3I0;
      break;
      case UP_CTRL_3I0_others:
       *editValue = 9;//3I0h;
      break;
      case UP_CTRL_Ua_Ub_Uc:
       *editValue = 10;//Ua+Ub+Uc
      break;
      case UP_CTRL_Uab_Ubc_Uca:
       *editValue = 14;//Uab+Ubc+Uca
      break;
      case UP_CTRL_Ua:
       *editValue = 11;//Ua
      break;
      case UP_CTRL_Ub:
       *editValue = 12;//Ub
      break;
      case UP_CTRL_Uc:
       *editValue = 13;//Uc
      break;
      case UP_CTRL_Uab:
       *editValue = 15;//Uab
      break;
      case UP_CTRL_Ubc:
       *editValue = 16;//Ubc
      break;
      case UP_CTRL_Uca:
       *editValue = 17;//Uca
      break;
      case UP_CTRL_U1:
       *editValue =  18;//U1
      break;
      case UP_CTRL_U2:
       *editValue =  19;//U2
      break;
      case UP_CTRL_3U0:
       *editValue = 20;//3U0
      break;
      case UP_CTRL_P:
       *editValue = 22;//P
      break;
      case UP_CTRL_Q:
       *editValue = 23;//Q
      break;
      case UP_CTRL_S:
       *editValue = 24;//S
      break;
      default:
       *editValue = 0;//(Ia+Ib+Ic)
     }//switch
/*
0-(Ia+Ib+Ic); 1-Ia; 2-Ib; 3-Ic; 4-I1; 5-I2; 6-I04; 7-3I0-1; 8-3I0; 9-3I0h; 10-Ua+Ub+Uc; 11-Ua; 12-Ub; 13-Uc; 14-Uab+Ubc+Uca; 15-Uab; 16-Ubc; 17-Uca; 18-U1; 19-U2; 20-3U0; 21-3U0-1; 22-P; 23-Q; 24-S;
  UP_CTRL_Ia_Ib_Ic = _UP_CTRL_MIN,
  UP_CTRL_Ia,
  UP_CTRL_Ib,
  UP_CTRL_Ic,
  UP_CTRL_I1,
  UP_CTRL_I2,
  UP_CTRL_3I0_r,
  UP_CTRL_3I0,
  UP_CTRL_3I0_others,
  UP_CTRL_Ua_Ub_Uc,
  UP_CTRL_Uab_Ubc_Uca,
  UP_CTRL_Ua,
  UP_CTRL_Uab,
  UP_CTRL_Ub,
  UP_CTRL_Ubc,
  UP_CTRL_Uc,
  UP_CTRL_Uca,
  UP_CTRL_U1,
  UP_CTRL_U2,
  UP_CTRL_3U0,
  UP_CTRL_P,
  UP_CTRL_Q,
  UP_CTRL_S,
*/
   }//if
  }//for(int item=0; item<NUMBER_UP; item++)
  for(int gruppa=0; gruppa<4; gruppa++)
  {
    for(int item=0; item<NUMBER_UP; item++)
    {
      if(editValue == (uint32_t*)&edition_settings.setpoint_UP[item][0][gruppa])
      {
        if((offset-adresGruppa)&1)
          return (((uint32_t)(*editValue))/multer)&0xFFFF;
        else
          return (((*editValue)/multer)>>16)&0xFFFF;
      }//if
    }//for(int item=0; item<NUMBER_UP; item++)
  }//for(int gruppa=0; gruppa<NUMBER_UP; gruppa++)
  if(editValue == (uint32_t*)&edition_settings.buttons_mode)
  {
    uint32_t buttonsmode = 0;
    for(int key=0; key<NUMBER_DEFINED_BUTTONS; key++)
    {
      if((*editValue) & (1<<key)) buttonsmode |= (1<<(2*key));
    }//for
    return (buttonsmode) &0xFFFF;
  }//if(editValue == (uint32_t*)&edition_settings.buttons_mode)
  if(editValue == (uint32_t*)&edition_settings.setpoint_pochatkovyj_resurs)
  {
    if(offset==MARKER1079)
    {
      return (*editValue) & (uint32_t)0xffff;
    }
    else
    {
      return ((*editValue)>>16)  & (uint32_t)0xffff;
    }//else
  }//if(editValue == (uint32_t*)&edition_settings.setpoint_pochatkovyj_resurs)
  if(editValue == (uint32_t*)&edition_settings.setpoint_pochatkova_k_vymk)
  {
    if(offset==1040)
    {
      return (*editValue) & (uint32_t)0xffff;
    }
    else
    {
      return ((*editValue)>>16)  & (uint32_t)0xffff;
    }//else
  }//if(editValue == (uint32_t*)&edition_settings.setpoint_pochatkova_k_vymk)
  if(editValue == (uint32_t*)&edition_settings.type_of_input_signal)
  {
#if MODYFIKACIA_VERSII_PZ == 0
    if(offset==MARKER1088)
    {
      return (*editValue) & (uint32_t)0xffff;
    }
    else
    {
      return ((*editValue)>>16)  & (uint32_t)0xffff;
    }//else
#else
    if(offset==MARKER1088)
    {
      return (*editValue) & (uint32_t)0xffff;
    }
    else
    {
      return 0;
    }//else

#endif
  }//if(editValue == (uint32_t*)&edition_settings.type_of_input_signal)
  if(editValue == (uint32_t*)&edition_settings.type_of_input)
  {
#if MODYFIKACIA_VERSII_PZ == 0
    if(offset==MARKER1090)
    {
      return (*editValue) & (uint32_t)0xffff;
    }
    else
    {
      return ((*editValue)>>16)  & (uint32_t)0xffff;
    }//else
#else
    if(offset==MARKER1090)
    {
      return (*editValue) & (uint32_t)0xffff;
    }
    else
    {
      return 0;
    }//else

#endif
  }//if(editValue == (uint32_t*)&edition_settings.type_of_input)
  if(editValue == (uint32_t*)&edition_settings.type_of_led)
  {
    if(offset==MARKER1095)
    {
      return (*editValue) & (uint32_t)0xffff;
    }
    else
    {
      return ((*editValue)>>16)  & (uint32_t)0xffff;
    }//else
  }//if(editValue == (uint32_t*)&edition_settings.type_of_led)

  return ((*editValue)/multer)&0xFFFF;
}//getDOUTBigModbusRegister(int adrReg)
int getUSTBigModbusBit(int x)
{
  //получить содержимое регистра
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)
int setUSTBigModbusRegister(int adrReg, int dataReg)
{
  //записать содержимое регистра
  if(privateUSTBigGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  if(ustbigcomponent->isActiveActualData)
  {
    edition_settings = current_settings_interfaces;//делаем копию
  }//if(uprbigcomponent->isActiveActualData)
  superClearActiveActualData();

  superSetOperativMarker(ustbigcomponent, adrReg);
  superSetTempWriteArray(dataReg);//записать в буфер

  int  adresGruppa=0;
  int  grupa_ustavok=0;
  int  offset = adrReg-BEGIN_ADR_REGISTER;
  grupa_ustavok_control(offset, &grupa_ustavok, &adresGruppa);

  uint32_t *editValue=NULL;
  int  multer = 1;
  if(!ustFunc000(offset -adresGruppa, grupa_ustavok, &multer, dataReg, &editValue)) return MARKER_ERRORDIAPAZON;
#ifdef TESTZBIRKA_VERSII_PZ
  if(editValue==NULL) return MARKER_ERRORDIAPAZON;
#else
  if(editValue==NULL) return 0;
#endif

  return 0;
}//getDOUTBigModbusRegister(int adrReg)
int setUSTBigModbusBit(int x, int y)
{
  UNUSED(x);
  UNUSED(y);
  //получить содержимое регистра
  return MARKER_OUTPERIMETR;
}//getDOUTBigModbusRegister(int adrReg)

void preUSTBigReadAction(void)
{
//action до чтения
  ustbigcomponent->isActiveActualData = 1;
}//
void preUSTBigWriteAction(void)
{
//action до записи
  ustbigcomponent->operativMarker[0] = -1;
  ustbigcomponent->operativMarker[1] = -1;//оперативный маркер
  ustbigcomponent->isActiveActualData = 1;
}//
int postUSTBigWriteAction(void)
{
  extern int upravlSetting;//флаг Setting
//action после записи
  int beginAdr = ustbigcomponent->operativMarker[0];
  if(beginAdr<0) return 0;//не было записи
  int endAdr   = ustbigcomponent->operativMarker[1];
  int flag=0;
  int offsetTempWriteArray = superFindTempWriteArrayOffset(BEGIN_ADR_REGISTER);//найти смещение TempWriteArray
  int countAdr = endAdr-beginAdr+1;
  if(endAdr<0) countAdr = 1;

  int  grupa_ustavok=0;
  for(int i=0; i<countAdr; i++)
  {
    int  adresGruppa=0;
    int offset = i+beginAdr-BEGIN_ADR_REGISTER;
    uint32_t *editValue=NULL;
    int  multer = 1;
    int grupa_offset = grupa_ustavok_control(offset, &grupa_ustavok, &adresGruppa);
    ustFunc000(offset -adresGruppa, grupa_ustavok, &multer, 0, &editValue);
    if(editValue==NULL) continue;

    flag=1;

    uint32_t value = (unsigned short) tempWriteArray[offsetTempWriteArray+i];

//ОСОБАЯ СБОРКА
    for(int item=0; item<NUMBER_UP; item++)
    {
     if(editValue == (uint32_t*)&edition_settings.ctrl_UP_input[item])
     {
      if(value>24) return ERROR_VALID2;//ошибка валидации
     switch(value)
     {
      case 0:
       value = UP_CTRL_Ia_Ib_Ic;//(Ia+Ib+Ic)
      break;
      case 1:
       value = UP_CTRL_Ia;//Ia;
      break;
      case 2:
       value = UP_CTRL_Ib;//Ib;
      break;
      case 3:
       value = UP_CTRL_Ic;//Ic;
      break;
      case 4:
       value = UP_CTRL_I1;//I1;
      break;
      case 5:
       value = UP_CTRL_I2;//I2;
      break;
      case 6:return ERROR_VALID2;//ошибка валидации
      case 7:
       value = UP_CTRL_3I0_r;//3I0-1
      break;
      case 8:
       value = UP_CTRL_3I0;//3I0;
      break;
      case 9:
       value = UP_CTRL_3I0_others;//3I0h;
      break;
      case 10:
       value = UP_CTRL_Ua_Ub_Uc;//Ua+Ub+Uc
      break;
      case 14:
       value = UP_CTRL_Uab_Ubc_Uca;//Uab+Ubc+Uca
      break;
      case 11:
       value = UP_CTRL_Ua;//Ua
      break;
      case 12:
       value = UP_CTRL_Ub;//Ub
      break;
      case 13:
       value = UP_CTRL_Uc;//Uc
      break;
      case 15:
       value = UP_CTRL_Uab;//Uab
      break;
      case 16:
       value = UP_CTRL_Ubc;//Ubc
      break;
      case 17:
       value = UP_CTRL_Uca;//Uca
      break;
      case 18:
       value =  UP_CTRL_U1;//U1
      break;
      case 19:
       value =  UP_CTRL_U2;//U2
      break;
      case 20:
       value = UP_CTRL_3U0;//3U0
      break;
      case 21:return ERROR_VALID2;//ошибка валидации
      case 22:
       value = UP_CTRL_P;//P
      break;
      case 23:
       value = UP_CTRL_Q;//Q
      break;
      case 24:
       value = UP_CTRL_S;//S
      break;
      default:
       value = 0;//(Ia+Ib+Ic)
     }//switch
/*
0-(Ia+Ib+Ic); 1-Ia; 2-Ib; 3-Ic; 4-I1; 5-I2; 6-I04; 7-3I0-1; 8-3I0; 9-3I0h; 10-Ua+Ub+Uc; 11-Ua; 12-Ub; 13-Uc; 14-Uab+Ubc+Uca; 15-Uab; 16-Ubc; 17-Uca; 18-U1; 19-U2; 20-3U0; 21-3U0-1; 22-P; 23-Q; 24-S;
  UP_CTRL_Ia_Ib_Ic = _UP_CTRL_MIN,
  UP_CTRL_Ia,
  UP_CTRL_Ib,
  UP_CTRL_Ic,
  UP_CTRL_I1,
  UP_CTRL_I2,
  UP_CTRL_3I0_r,
  UP_CTRL_3I0,
  UP_CTRL_3I0_others,
  UP_CTRL_Ua_Ub_Uc,
  UP_CTRL_Uab_Ubc_Uca,
  UP_CTRL_Ua,
  UP_CTRL_Uab,
  UP_CTRL_Ub,
  UP_CTRL_Ubc,
  UP_CTRL_Uc,
  UP_CTRL_Uca,
  UP_CTRL_U1,
  UP_CTRL_U2,
  UP_CTRL_3U0,
  UP_CTRL_P,
  UP_CTRL_Q,
  UP_CTRL_S,
*/
     }//if
    }//for(int item=0; item<NUMBER_UP; item++)
    if(editValue == (uint32_t*)&edition_settings.type_of_input_signal)
    {
      if(offset==MARKER1088)
      {
        (*editValue) &= (uint32_t)~0xffff;
        (*editValue) |= (value & 0xffff);
        goto m1;
      }
      else
      {
        (*editValue)  &= (uint32_t)~(0xffff<<16);
        (*editValue)  |= ((value & 0xffff)<<16);//
        goto m1;
      }//else
    }//if(editValue == (uint32_t*)&edition_settings.type_of_input_signal)
    if(editValue == (uint32_t*)&edition_settings.type_of_input)
    {
      if(offset==MARKER1090)
      {
        (*editValue) &= (uint32_t)~0xffff;
        (*editValue) |= (value & 0xffff);
        goto m1;
      }
      else
      {
        (*editValue)  &= (uint32_t)~(0xffff<<16);
        (*editValue)  |= ((value & 0xffff)<<16);//
        goto m1;
      }//else
    }//if(editValue == (uint32_t*)&edition_settings.type_of_input)
    if(editValue == (uint32_t*)&edition_settings.type_of_led)
    {
      if(offset==MARKER1095)
      {
        (*editValue) &= (uint32_t)~0xffff;
        (*editValue) |= (value & 0xffff);
        goto m1;
      }
      else
      {
        (*editValue)  &= (uint32_t)~(0xffff<<16);
        (*editValue)  |= ((value & 0xffff)<<16);//
        goto m1;
      }//else
    }//if(editValue == (uint32_t*)&edition_settings.type_of_led)

    if(editValue == (uint32_t*)&edition_settings.buttons_mode)
    {
      for(int key=0; key<NUMBER_DEFINED_BUTTONS; key++)
      {
        if(value&(3<<(2*key))) (*editValue) |= (1<<key);
        else (*editValue) &= ~(1<<key);
      }//for
      goto m1;
    }//if(editValue == (uint32_t*)&edition_settings.buttons_mode)

    for(int item=0; item<NUMBER_UP; item++)
    {
      if(editValue == (uint32_t*)&edition_settings.timeout_UP[item][0][grupa_ustavok])
      {
        (*editValue) = multer*value;
        goto m1;
      }//if(editValue == (uint32_t*)&edition_settings.timeout_UP[item][0][grupa_ustavok])
    }//for(int item=0; item<NUMBER_UP; item++)

    if(editValue == (uint32_t*)&edition_settings.setpoint_pochatkovyj_resurs)
    {
      if(offset==MARKER1079)
      {
        (*editValue) &= (uint32_t)~0xffff;
        (*editValue) |= (value & 0xffff);
        goto m1;
      }
      else
      {
        (*editValue)  &= (uint32_t)~(0xffff<<16);
        (*editValue)  |= ((value & 0xffff)<<16);//
        goto m1;
      }//else
    }//if(editValue == (uint32_t*)&edition_settings.setpoint_pochatkovyj_resurs)
    if(editValue == (uint32_t*)&edition_settings.setpoint_pochatkova_k_vymk)
    {
      if(offset==MARKER1082)
      {
        (*editValue) &= (uint32_t)~0xffff;
        (*editValue) |= (value & 0xffff);
        goto m1;
      }
      else
      {
        (*editValue)  &= (uint32_t)~(0xffff<<16);
        (*editValue)  |= ((value & 0xffff)<<16);//
        goto m1;
      }//else
    }//if(editValue == (uint32_t*)&edition_settings.setpoint_pochatkova_k_vymk)

    if(editValue == (uint32_t*)&edition_settings.setpoint_tznp_1_angle[grupa_ustavok])
    {
      float temp_value_f = (float)value;
      edition_settings.setpoint_tznp_1_angle_cos[grupa_ustavok] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*temp_value_f/180.0f)));
      edition_settings.setpoint_tznp_1_angle_sin[grupa_ustavok] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*temp_value_f/180.0f)));
    }//if(editValue == (uint32_t*)&edition_settings.setpoint_tznp_1_angle[grupa_ustavok])
    if(editValue == (uint32_t*)&edition_settings.setpoint_tznp_2_angle[grupa_ustavok])
    {
      float temp_value_f = (float)value;
      edition_settings.setpoint_tznp_2_angle_cos[grupa_ustavok] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*temp_value_f/180.0f)));
      edition_settings.setpoint_tznp_2_angle_sin[grupa_ustavok] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*temp_value_f/180.0f)));
    }//if(editValue == (uint32_t*)&edition_settings.setpoint_tznp_1_angle[grupa_ustavok])
    if(editValue == (uint32_t*)&edition_settings.setpoint_tznp_3_angle[grupa_ustavok])
    {
      float temp_value_f = (float)value;
      edition_settings.setpoint_tznp_3_angle_cos[grupa_ustavok] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*temp_value_f/180.0f)));
      edition_settings.setpoint_tznp_3_angle_sin[grupa_ustavok] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*temp_value_f/180.0f)));
    }//if(editValue == (uint32_t*)&edition_settings.setpoint_tznp_1_angle[grupa_ustavok])

    if(editValue == (uint32_t*)&edition_settings.setpoint_mtz_1_angle[grupa_ustavok])
    {
      float temp_value_f = (float)value;
      edition_settings.setpoint_mtz_1_angle_cos[grupa_ustavok] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*temp_value_f/180.0f)));
      edition_settings.setpoint_mtz_1_angle_sin[grupa_ustavok] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*temp_value_f/180.0f)));
    }//if(editValue == (uint32_t*)&edition_settings.setpoint_mtz_1_angle[grupa_ustavok])
    if(editValue == (uint32_t*)&edition_settings.setpoint_mtz_2_angle[grupa_ustavok])
    {
      float temp_value_f = (float)value;
      edition_settings.setpoint_mtz_2_angle_cos[grupa_ustavok] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*temp_value_f/180.0f)));
      edition_settings.setpoint_mtz_2_angle_sin[grupa_ustavok] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*temp_value_f/180.0f)));
    }//if(editValue == (uint32_t*)&edition_settings.setpoint_mtz_2_angle[grupa_ustavok])
    if(editValue == (uint32_t*)&edition_settings.setpoint_mtz_3_angle[grupa_ustavok])
    {
      float temp_value_f = (float)value;
      edition_settings.setpoint_mtz_3_angle_cos[grupa_ustavok] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*temp_value_f/180.0f)));
      edition_settings.setpoint_mtz_3_angle_sin[grupa_ustavok] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*temp_value_f/180.0f)));
    }//if(editValue == (uint32_t*)&edition_settings.setpoint_mtz_3_angle[grupa_ustavok])
    if(editValue == (uint32_t*)&edition_settings.setpoint_mtz_4_angle[grupa_ustavok])
    {
      float temp_value_f = (float)value;
      edition_settings.setpoint_mtz_4_angle_cos[grupa_ustavok] = (int) (AMPLITUDA_FI*/*cos*/arm_cos_f32(/*(double)*/(PI*temp_value_f/180.0f)));
      edition_settings.setpoint_mtz_4_angle_sin[grupa_ustavok] = (int) (AMPLITUDA_FI*/*sin*/arm_sin_f32(/*(double)*/(PI*temp_value_f/180.0f)));
    }//if(editValue == (uint32_t*)&edition_settings.setpoint_mtz_4_angle[grupa_ustavok])

    if(editValue == (uint32_t*)&edition_settings.pickup_dz2_angle[grupa_ustavok])
    {
      float angle_f = (float)value;
      edition_settings.pickup_dz2_angle_cos1[grupa_ustavok] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*angle_f/180.0f)));
      edition_settings.pickup_dz2_angle_sin1[grupa_ustavok] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*angle_f/180.0f)));
      edition_settings.pickup_dz2_angle_cos2[grupa_ustavok] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*(angle_f - DELTA_SECTOR_DZ)/180.0f)));
      edition_settings.pickup_dz2_angle_sin2[grupa_ustavok] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*(angle_f - DELTA_SECTOR_DZ)/180.0f)));
    }//if(editValue == (uint32_t*)&edition_settings.pickup_dz2_angle[grupa_ustavok])
    if(editValue == (uint32_t*)&edition_settings.pickup_dz3_angle[grupa_ustavok])
    {
      float angle_f = (float)value;
      edition_settings.pickup_dz3_angle_cos1[grupa_ustavok] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*angle_f/180.0f)));
      edition_settings.pickup_dz3_angle_sin1[grupa_ustavok] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*angle_f/180.0f)));
      edition_settings.pickup_dz3_angle_cos2[grupa_ustavok] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*(angle_f - DELTA_SECTOR_DZ)/180.0f)));
      edition_settings.pickup_dz3_angle_sin2[grupa_ustavok] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*(angle_f - DELTA_SECTOR_DZ)/180.0f)));
    }//if(editValue == (uint32_t*)&edition_settings.pickup_dz3_angle[grupa_ustavok])
    if(editValue == (uint32_t*)&edition_settings.pickup_dz4_angle[grupa_ustavok])
    {
      float angle_f = (float)value;
      edition_settings.pickup_dz4_angle_cos1[grupa_ustavok] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*angle_f/180.0f)));
      edition_settings.pickup_dz4_angle_sin1[grupa_ustavok] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*angle_f/180.0f)));
      edition_settings.pickup_dz4_angle_cos2[grupa_ustavok] = (int) (AMPLITUDA_SECTOR*/*cos*/arm_cos_f32(/*(double)*/(PI*(angle_f - DELTA_SECTOR_DZ)/180.0f)));
      edition_settings.pickup_dz4_angle_sin2[grupa_ustavok] = (int) (AMPLITUDA_SECTOR*/*sin*/arm_sin_f32(/*(double)*/(PI*(angle_f - DELTA_SECTOR_DZ)/180.0f)));
    }//if(editValue == (uint32_t*)&edition_settings.pickup_dz4_angle[grupa_ustavok])

    for(int item=0; item<NUMBER_UP; item++)
    {
      if(editValue == (uint32_t*)&edition_settings.setpoint_UP[item][0][grupa_ustavok])
      {
        if((offset-grupa_offset*grupa_ustavok)&1)
        {
          //мл регистр
          (*editValue) = value*multer;
          goto m1;
        }//if(offset&1)
        else
        {
          //ст регистр
          switch(edition_settings.ctrl_UP_input[item])
          {
          case UP_CTRL_P:
          case UP_CTRL_Q:
          case UP_CTRL_S:
            (*editValue)  &= 0xffff;
            (*editValue)  |= ((value & 0xffff)<<16);//
            goto m1;
          default:
            goto m1;
          }//switch
        }//else
      }//if(editValue == (uint32_t*)&edition_settings.setpoint_UP[item][0][grupa_ustavok])
    }//for(int item=0; item<NUMBER_UP; item++)

    (*editValue) = value*multer;

m1:
    grupa_ustavok_control(offset, &grupa_ustavok, &adresGruppa);
    ustFunc000(-offset +adresGruppa, grupa_ustavok, &multer, value*multer, &editValue);
  }//for


//ОСОБАЯ ПРОВЕРКА
  int item=0;
  int temp1=0;

  for(; item<NUMBER_UP; item++)
  {
    temp1=edition_settings.setpoint_UP[item][0][grupa_ustavok];
    switch(edition_settings.ctrl_UP_input[item])
    {
    case UP_CTRL_P:
    case UP_CTRL_Q:
      if(temp1<0) temp1 = -temp1;//модуль
      if(temp1<SETPOINT_UP_P_MIN ||
          temp1>SETPOINT_UP_P_MAX
        ) return ERROR_VALID2;//ошибка валидации
      break;

    case UP_CTRL_S:
      if(temp1<SETPOINT_UP_P_MIN ||
          temp1>SETPOINT_UP_P_MAX
        ) return ERROR_VALID2;//ошибка валидации
      break;
    }//switch
  }//for(int item=0; item<NUMBER_UP; item++)

  for(int i=0; i<countAdr; i++)
  {
    int offset = i+beginAdr-BEGIN_ADR_REGISTER;
    if(offset==MARKER1079 || offset==MARKER1080 || offset==MARKER1081 || offset==MARKER1082 || offset==MARKER1083)
    {
      temp1=edition_settings.setpoint_pochatkovyj_resurs;
      unsigned int chastka = edition_settings.setpoint_r_kom_st_Inom/edition_settings.setpoint_r_kom_st_Inom_vymk;
      if(
        !(((unsigned int)temp1 >= (2*chastka)) && ((unsigned int)temp1 <= edition_settings.setpoint_r_kom_st_Inom))
      ) return ERROR_VALID2;//ошибка валидации
      temp1=edition_settings.setpoint_krytychnyj_resurs;
      if(
        !(((unsigned int)temp1 >= chastka) && ((unsigned int)temp1 <= 2*chastka))
      ) return ERROR_VALID2;//ошибка валидации

      temp1=edition_settings.setpoint_pochatkova_k_vymk;
      if(
        !((unsigned int)temp1 <= edition_settings.setpoint_r_kom_st_Inom)
      ) return ERROR_VALID2;//ошибка валидации
    }//if

//ОСОБАЯ ПРОВЕРКА

    if(offset==MARKER248)
    {
      temp1=edition_settings.ctrl_zdz_type;
      switch(temp1)
      {
      case 0://0-без контроля
        break;
      case 1://1-с контролем по току
        if(!(edition_settings.configuration&(1<<MTZ_BIT_CONFIGURATION))) return ERROR_VALID2;
        break;
      case 2://2-с контролем по напряжению
        if(!(edition_settings.configuration&(1<<UMIN_BIT_CONFIGURATION))) return ERROR_VALID2;
        break;
      case 3://3-с контролем по току ИЛИ по напряжению
        if(!(edition_settings.configuration&(1<<MTZ_BIT_CONFIGURATION) || edition_settings.configuration&(1<<UMIN_BIT_CONFIGURATION))) return ERROR_VALID2;
        break;
      case 4://4-с контролем по току И по напряжению
        if(!(edition_settings.configuration&(1<<MTZ_BIT_CONFIGURATION))) return ERROR_VALID2;
        if(!(edition_settings.configuration&(1<<UMIN_BIT_CONFIGURATION))) return ERROR_VALID2;
        break;
      case 5://5-с контролем по 3I0
        if(!(edition_settings.configuration&(1<<ZZ_BIT_CONFIGURATION))) return ERROR_VALID2;
        break;
      }//switch
    }//if(offset==MARKER248)//(uint32_t*)&edition_settings.ctrl_zdz_type

  }//for(int i=0; i<countAdr; i++)


  if(flag) upravlSetting = 1;//флаг Setting

  return 0;
}//

int privateUSTBigGetReg2(int adrReg)
{
  //проверить внешний периметр
  return controlPerimetr(adrReg, BEGIN_ADR_REGISTER, END_ADR_REGISTER);
}//privateGetReg2(int adrReg)

int grupa_ustavok_control(int  offset, int *grupa_ustavok, int *adresGruppa)
{
  int  grupa_offset=243;
  int  ust_offset=15;
  if(offset>=(ust_offset+grupa_offset*0) && offset<=(ust_offset-1+grupa_offset*1))
  {
    *grupa_ustavok=0;
    *adresGruppa=0;
  }//if
  else if(offset>=(ust_offset+grupa_offset*1) && offset<=(ust_offset-1+grupa_offset*2))
  {
    *grupa_ustavok=1;
    *adresGruppa=grupa_offset*1;
  }//if
  else if(offset>=(ust_offset+grupa_offset*2) && offset<=(ust_offset-1+grupa_offset*3))
  {
    *grupa_ustavok=2;
    *adresGruppa=grupa_offset*2;
  }//if
  else if(offset>=(ust_offset+grupa_offset*3) && offset<=(ust_offset-1+grupa_offset*4))
  {
    *grupa_ustavok=3;
    *adresGruppa=grupa_offset*3;
  }//if
  return grupa_offset;
}//grupa_ustavok_control(int  offset, int *grupa_ustavok, int *adresGruppa)


