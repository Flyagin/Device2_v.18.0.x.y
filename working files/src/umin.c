extern char ch_type_voltage; 
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void umin1_handler1(unsigned int *p_active_functions, unsigned int number_group_stp)
// ----------------    	-------------------------
{
  _Bool previous_state_po_umin1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UMIN1) > 0;
  _Bool previous_state_po_ublk_umin1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN1) > 0;
  _Bool previous_state_po_iblk_umin1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_IBLK_UMIN1) > 0;
  
  unsigned int setpoint1 = previous_state_po_umin1 ?
          current_settings_prt.setpoint_Umin1[number_group_stp] * U_DOWN / 100 :
          current_settings_prt.setpoint_Umin1[number_group_stp];
  
  _Bool Uab_is_smaller_than_Umin1 = measurement[IM_UAB] <= setpoint1;
  _Bool Ubc_is_smaller_than_Umin1 = measurement[IM_UBC] <= setpoint1;
  _Bool Uca_is_smaller_than_Umin1 = measurement[IM_UCA] <= setpoint1;
  
  _Bool Ua_is_smaller_than_Umin1 = measurement[IM_UA] <= setpoint1;
  _Bool Ub_is_smaller_than_Umin1 = measurement[IM_UB] <= setpoint1;
  _Bool Uc_is_smaller_than_Umin1 = measurement[IM_UC] <= setpoint1;
  
  unsigned int setpoint2 = previous_state_po_ublk_umin1 ?
          KOEF_MIN_UMIN * U_DOWN_1 / 100 : KOEF_MIN_UMIN;
          
  _Bool Ua_or_Ub_or_Uc_is_smaller_than_250mV = (measurement[IM_UA] <= setpoint2) || (measurement[IM_UB] <= setpoint2) || (measurement[IM_UC] <= setpoint2);
  _Bool Uab_or_Ubc_or_Uca_is_smaller_than_250mV = (measurement[IM_UAB] <= setpoint2) || (measurement[IM_UBC] <= setpoint2) || (measurement[IM_UCA] <= setpoint2);
  
  unsigned int setpoint3 = previous_state_po_iblk_umin1 ?
          current_settings_prt.setpoint_Umin1_Iblk[number_group_stp] * KOEF_POVERNENNJA_GENERAL_DOWN / 100 :
          current_settings_prt.setpoint_Umin1_Iblk[number_group_stp];
  
  _Bool Ia_and_Ic_is_smaller_than_Iust = (measurement[IM_IA_H] <= setpoint3) &&
                                         (measurement[IM_IB_H] <= setpoint3) &&
                                         (measurement[IM_IC_H] <= setpoint3);
  //М
  unsigned int tmp_value = ((current_settings_prt.control_transformator & (1<<INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE)) == 0) << 0;
//  tmp_value |= ((current_settings_prt.control_Umin & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                                 << 1;
//  _INVERTOR(tmp_value, 1, tmp_value, 1);
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN1) != 0)                                                            << 2;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_PO_UMIN1_OR_AND) != 0)                                                  << 3;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN1_UBLK) != 0)                                                       << 4;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN1_IBLK) != 0)                                                       << 5;
  
  //ДВ
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_UMIN1) != 0)                                     << 6;
  _INVERTOR(tmp_value, 6, tmp_value, 6);
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_START_UMIN1) != 0)                                     << 7;
  
//  _AND2(tmp_value, 0, tmp_value, 1, tmp_value, 8);
  
  if (_GET_OUTPUT_STATE(tmp_value, 0)) 
  {
    //Фазные
    _AND4(Ua_is_smaller_than_Umin1, 0, Ub_is_smaller_than_Umin1, 0, Uc_is_smaller_than_Umin1, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Ua_is_smaller_than_Umin1, 0, Ub_is_smaller_than_Umin1, 0, Uc_is_smaller_than_Umin1, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_and_Ic_is_smaller_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Ua_or_Ub_or_Uc_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //ПО Uблк. Umin1
    if (Ua_or_Ub_or_Uc_is_smaller_than_250mV)
      _SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN1);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_UBLK_UMIN1);
  } 
  else 
  {
    //Линейные
    _AND4(Uab_is_smaller_than_Umin1, 0, Ubc_is_smaller_than_Umin1, 0, Uca_is_smaller_than_Umin1, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Uab_is_smaller_than_Umin1, 0, Ubc_is_smaller_than_Umin1, 0, Uca_is_smaller_than_Umin1, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_and_Ic_is_smaller_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Uab_or_Ubc_or_Uca_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //ПО Uблк. Umin1
    if (Uab_or_Ubc_or_Uca_is_smaller_than_250mV)
      _SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN1);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_UBLK_UMIN1);
  }
  _INVERTOR(tmp_value, 12, tmp_value, 12);
  _INVERTOR(tmp_value, 13, tmp_value, 13);
  _OR3(tmp_value, 7, tmp_value, 9, tmp_value, 11, tmp_value, 14);
  
  _AND5(tmp_value, 6, tmp_value, 2, tmp_value, 14, tmp_value, 13, tmp_value, 12, tmp_value, 15);
  
  //ПО Iблк. Umin1
  if (Ia_and_Ic_is_smaller_than_Iust)
    _SET_BIT(p_active_functions, RANG_PO_IBLK_UMIN1);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_IBLK_UMIN1);
  
  //ПО Umin1
  if (_GET_OUTPUT_STATE(tmp_value, 15))
    _SET_BIT(p_active_functions, RANG_PO_UMIN1);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_UMIN1);
  
  _TIMER_T_0(INDEX_TIMER_UMIN1, current_settings_prt.timeout_Umin1[number_group_stp], tmp_value, 15, tmp_value, 16);
  
  //Сраб. Umin1
  if (_GET_OUTPUT_STATE(tmp_value, 16))
    _SET_BIT(p_active_functions, RANG_UMIN1);
  else
    _CLEAR_BIT(p_active_functions, RANG_UMIN1);
}

//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````

//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void umin2_handler1(unsigned int *p_active_functions, unsigned int number_group_stp)
// ----------------    	-------------------------
{
  _Bool previous_state_po_umin2 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UMIN2) > 0;
  _Bool previous_state_po_ublk_umin2 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN2) > 0;
  _Bool previous_state_po_iblk_umin2 = _CHECK_SET_BIT(p_active_functions, RANG_PO_IBLK_UMIN2) > 0;
  
  unsigned int setpoint1 = previous_state_po_umin2 ?
          current_settings_prt.setpoint_Umin2[number_group_stp] * U_DOWN / 100 :
          current_settings_prt.setpoint_Umin2[number_group_stp];
  
  _Bool Uab_is_smaller_than_Umin2 = measurement[IM_UAB] <= setpoint1;
  _Bool Ubc_is_smaller_than_Umin2 = measurement[IM_UBC] <= setpoint1;
  _Bool Uca_is_smaller_than_Umin2 = measurement[IM_UCA] <= setpoint1;
  
  _Bool Ua_is_smaller_than_Umin2 = measurement[IM_UA] <= setpoint1;
  _Bool Ub_is_smaller_than_Umin2 = measurement[IM_UB] <= setpoint1;
  _Bool Uc_is_smaller_than_Umin2 = measurement[IM_UC] <= setpoint1;
  
  unsigned int setpoint2 = previous_state_po_ublk_umin2 ?
          KOEF_MIN_UMIN * U_DOWN_1 / 100 : KOEF_MIN_UMIN;
          
  _Bool Ua_or_Ub_or_Uc_is_smaller_than_250mV = (measurement[IM_UA] <= setpoint2) || (measurement[IM_UB] <= setpoint2) || (measurement[IM_UC] <= setpoint2);
  _Bool Uab_or_Ubc_or_Uca_is_smaller_than_250mV = (measurement[IM_UAB] <= setpoint2) || (measurement[IM_UBC] <= setpoint2) || (measurement[IM_UCA] <= setpoint2);
  
  unsigned int setpoint3 = previous_state_po_iblk_umin2 ?
          current_settings_prt.setpoint_Umin2_Iblk[number_group_stp] * KOEF_POVERNENNJA_GENERAL_DOWN / 100 :
          current_settings_prt.setpoint_Umin2_Iblk[number_group_stp];
  
  _Bool Ia_and_Ic_is_smaller_than_Iust = (measurement[IM_IA_H] <= setpoint3) &&
                                         (measurement[IM_IB_H] <= setpoint3) &&
                                         (measurement[IM_IC_H] <= setpoint3);
  //М
  unsigned int tmp_value = ((current_settings_prt.control_transformator & (1<<INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE)) == 0) << 0;
//  tmp_value |= ((current_settings_prt.control_Umin & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                                 << 1;
//  _INVERTOR(tmp_value, 1, tmp_value, 1);
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN2) != 0)                                                            << 2;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_PO_UMIN2_OR_AND) != 0)                                                  << 3;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN2_UBLK) != 0)                                                       << 4;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN2_IBLK) != 0)                                                       << 5;
  
  //ДВ
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_UMIN2) != 0)                                    << 6;
  _INVERTOR(tmp_value, 6, tmp_value, 6);
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_START_UMIN2) != 0)                                    << 7;
  
//  _AND2(tmp_value, 0, tmp_value, 1, tmp_value, 8);
  
  if (_GET_OUTPUT_STATE(tmp_value, 0))
  {
    //Фазные
    _AND4(Ua_is_smaller_than_Umin2, 0, Ub_is_smaller_than_Umin2, 0, Uc_is_smaller_than_Umin2, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Ua_is_smaller_than_Umin2, 0, Ub_is_smaller_than_Umin2, 0, Uc_is_smaller_than_Umin2, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_and_Ic_is_smaller_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Ua_or_Ub_or_Uc_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //ПО Uблк. Umin2
    if (Ua_or_Ub_or_Uc_is_smaller_than_250mV)
      _SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN2);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_UBLK_UMIN2);
    
  } 
  else 
  {
    //Линейные
    _AND4(Uab_is_smaller_than_Umin2, 0, Ubc_is_smaller_than_Umin2, 0, Uca_is_smaller_than_Umin2, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Uab_is_smaller_than_Umin2, 0, Ubc_is_smaller_than_Umin2, 0, Uca_is_smaller_than_Umin2, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_and_Ic_is_smaller_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Uab_or_Ubc_or_Uca_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //ПО Uблк. Umin2
    if (Uab_or_Ubc_or_Uca_is_smaller_than_250mV)
      _SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN2);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_UBLK_UMIN2);
  }
  _INVERTOR(tmp_value, 12, tmp_value, 12);
  _INVERTOR(tmp_value, 13, tmp_value, 13);
  _OR3(tmp_value, 7, tmp_value, 9, tmp_value, 11, tmp_value, 14);
  
  _AND5(tmp_value, 6, tmp_value, 2, tmp_value, 14, tmp_value, 13, tmp_value, 12, tmp_value, 15);
  
  //ПО Iблк. Umin2
  if (Ia_and_Ic_is_smaller_than_Iust)
    _SET_BIT(p_active_functions, RANG_PO_IBLK_UMIN2);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_IBLK_UMIN2);
  
  //ПО Umin2
  if (_GET_OUTPUT_STATE(tmp_value, 15))
    _SET_BIT(p_active_functions, RANG_PO_UMIN2);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_UMIN2);
  
  _TIMER_T_0(INDEX_TIMER_UMIN2, current_settings_prt.timeout_Umin2[number_group_stp], tmp_value, 15, tmp_value, 16);
  
  //Сраб. Umin2
  if (_GET_OUTPUT_STATE(tmp_value, 16))
    _SET_BIT(p_active_functions, RANG_UMIN2);
  else
    _CLEAR_BIT(p_active_functions, RANG_UMIN2);
}
//
//--------------------------------------------------------------------------------------------------------
//``````
enum UMIN_BIT_POS { 

UMIN_DV_BLOCK_CMD_BIT  = 1,  
UMIN_DV_BLOCK_INVERSE_CMD_BIT,
UMIN_DV_START_UMIN1,
UMIN_MCTR_TRANSFORMATOR_PHASE_LINE_BIT,
UMIN_MCTR_UMIN1_BIT,
UMIN_MCTRLR_PO_UMIN1_OR_AND_BIT,  
UMIN_MCTRLR_UMIN1_UBLK_BIT,  
UMIN_MCTRLR_UMIN1_IBLK_BIT,


  
UMIN_AND4_1_STATE_BIT,
UMIN_OR3_2_STATE_BIT,
UMIN_NOT_3_STATE_BIT,
UMIN_AND2_4_STATE_BIT,
UMIN_AND2_5_STATE_BIT,
UMIN_NOT_6_STATE_BIT,
UMIN_AND3_7_STATE_BIT,
UMIN_NOT_8_STATE_BIT,
UMIN_NOT_9_STATE_BIT,
UMIN_OR3_10_STATE_BIT,
UMIN_AND5_11_STATE_BIT,

UMIN_PICKUP_BIT = UMIN_AND5_11_STATE_BIT,
UMIN_TMR_STATE_BIT,
TOTAL_UMIN_BITS
//LU_GEN_OP_EV_FIX_IBUS
};
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void umin1_handler2(unsigned int *p_active_functions, unsigned int number_group_stp){
// ----------------    	-------------------------
register unsigned long u32_bit_holder = 0;  
register union { 
   struct {
      unsigned int previous_state_po_umin1      :1;            //0
	  unsigned int previous_state_po_ublk_umin1 :1;            //1
	  unsigned int previous_state_po_iblk_umin1 :1;            //2
 	  unsigned int Ia_and_Ic_is_smaller_than_Iust :1;          //3
 	  unsigned int Ua_is_smaller_than_Umin1      :1;           //4
 	  unsigned int Ub_is_smaller_than_Umin1      :1;           //5
 	  unsigned int Uc_is_smaller_than_Umin1      :1;           //6
 	  unsigned int Ua_or_Ub_or_Uc_is_smaller_than_250mV :1;    //7
 	  unsigned int Uab_is_smaller_than_Umin1      :1;          //8
 	  unsigned int Ubc_is_smaller_than_Umin1      :1;          //9
 	  unsigned int Uca_is_smaller_than_Umin1      :1;          //10
 	  unsigned int Uab_or_Ubc_or_Uca_is_smaller_than_250mV :1; //11
	  
   } bool_vars;
  long lVl;
}wrp;
   long lV; 
// ----------------    	-------------------------
wrp.lVl = 0;
  wrp.bool_vars.previous_state_po_umin1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UMIN1) > 0;
  wrp.bool_vars.previous_state_po_ublk_umin1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN1) > 0;
  wrp.bool_vars.previous_state_po_iblk_umin1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_IBLK_UMIN1) > 0;
  
  unsigned int pick_up_U = wrp.bool_vars.previous_state_po_umin1 ?
          current_settings_prt.setpoint_Umin1[number_group_stp] * U_DOWN / 100 :
          current_settings_prt.setpoint_Umin1[number_group_stp];
		  
  unsigned int pick_up_Ublk = wrp.bool_vars.previous_state_po_ublk_umin1 ?
          KOEF_MIN_UMIN * U_DOWN_1 / 100 : KOEF_MIN_UMIN;

  unsigned int pick_up_Iblk = wrp.bool_vars.previous_state_po_iblk_umin1 ?
          current_settings_prt.setpoint_Umin1_Iblk[number_group_stp] * KOEF_POVERNENNJA_GENERAL_DOWN / 100 :
          current_settings_prt.setpoint_Umin1_Iblk[number_group_stp];
   ch_type_voltage = (current_settings.control_transformator >> INDEX_ML_CTR_TRANSFORMATOR_VH_VL) & 0x1;
//  CTR_EXTRA_SETTINGS_1_CTRL_VH_VL //0-VH 1 - VL 
	if(ch_type_voltage != 0){
wrp.bool_vars.Ia_and_Ic_is_smaller_than_Iust = (measurement[IM_IA_L] <= pick_up_Iblk) &&
                                         (measurement[IM_IB_L] <= pick_up_Iblk) &&
                                         (measurement[IM_IC_L] <= pick_up_Iblk);
	}else{
	wrp.bool_vars.Ia_and_Ic_is_smaller_than_Iust = (measurement[IM_IA_H] <= pick_up_Iblk) &&
                                         (measurement[IM_IB_H] <= pick_up_Iblk) &&
                                         (measurement[IM_IC_H] <= pick_up_Iblk);
	}										 
  //ПО Iблк. Umin1
  if (wrp.bool_vars.Ia_and_Ic_is_smaller_than_Iust)
    _SET_BIT(p_active_functions, RANG_PO_IBLK_UMIN1);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_IBLK_UMIN1);										 

										 //М
  lV = (current_settings_prt.control_transformator & (1<<INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE)) == 0;
  u32_bit_holder = (lV) << (UMIN_MCTR_TRANSFORMATOR_PHASE_LINE_BIT);
  lV = (current_settings_prt.control_Umin & CTR_UMIN1) != 0 ;
  u32_bit_holder |= ( lV ) << (UMIN_MCTR_UMIN1_BIT);
  lV = (current_settings_prt.control_Umin & CTR_PO_UMIN1_OR_AND) != 0;
  u32_bit_holder |= (lV)  << (UMIN_MCTRLR_PO_UMIN1_OR_AND_BIT);
  lV = (current_settings_prt.control_Umin & CTR_UMIN1_UBLK) != 0;
  u32_bit_holder |= (lV)       << (UMIN_MCTRLR_UMIN1_UBLK_BIT);
  lV = (current_settings_prt.control_Umin & CTR_UMIN1_IBLK) != 0;
  u32_bit_holder |= (lV)       << (UMIN_MCTRLR_UMIN1_IBLK_BIT);
  lV = _CHECK_SET_BIT(p_active_functions, RANG_BLOCK_UMIN1) != 0;
  //ДВ
   u32_bit_holder |= (lV)<< (UMIN_DV_BLOCK_CMD_BIT);
  //_INVERTOR(u32_val, 6, u32_val, 6);
  u32_bit_holder |= (!lV)<< (UMIN_DV_BLOCK_INVERSE_CMD_BIT);
  lV = _CHECK_SET_BIT(p_active_functions, RANG_START_UMIN1) != 0;
   u32_bit_holder |= (lV)<< UMIN_DV_START_UMIN1;
 

  if ( (u32_bit_holder&(1<<(UMIN_MCTR_TRANSFORMATOR_PHASE_LINE_BIT)) )!= 0) //_GET_OUTPUT_STATE( , 0)
  {
    //Фазные
	
      wrp.bool_vars.Ua_is_smaller_than_Umin1 = measurement[IM_UA] <= pick_up_U;
      wrp.bool_vars.Ub_is_smaller_than_Umin1 = measurement[IM_UB] <= pick_up_U;
      wrp.bool_vars.Uc_is_smaller_than_Umin1 = measurement[IM_UC] <= pick_up_U;
      wrp.bool_vars.Ua_or_Ub_or_Uc_is_smaller_than_250mV = (measurement[IM_UA] <= pick_up_Ublk)
	  || (measurement[IM_UB] <= pick_up_Ublk) || (measurement[IM_UC] <= pick_up_Ublk);
  
    //_AND4(Ua_is_smaller_than_Umin1, 0, Ub_is_smaller_than_Umin1, 0, Uc_is_smaller_than_Umin1, 0, u32_val, 3, u32_val, 9);
	lV = (wrp.lVl&( (1<<4)|(1<<5)|(1<<6) )!=0);
    u32_bit_holder |= lV << (UMIN_AND4_1_STATE_BIT);
    //_OR3(Ua_is_smaller_than_Umin1, 0, Ub_is_smaller_than_Umin1, 0, Uc_is_smaller_than_Umin1, 0, u32_val, 10);
    lV = ( ( wrp.lVl&(1<<4))|(wrp.lVl&(1<<5)) |(wrp.lVl&(1<<6)) )!=0;
	u32_bit_holder |= lV << (UMIN_OR3_2_STATE_BIT);
	//_INVERTOR(u32_val, 3, u32_val, 3);
	lV = !(u32_bit_holder&(1<<UMIN_MCTRLR_PO_UMIN1_OR_AND_BIT)); 
    u32_bit_holder |= lV << (UMIN_NOT_3_STATE_BIT);
	//_AND2(u32_val, 10, u32_val, 3, u32_val, 11);
    lV = ( u32_bit_holder & ((1<< (UMIN_NOT_3_STATE_BIT))|(1<<UMIN_OR3_2_STATE_BIT)) ) != 0;
	u32_bit_holder |= lV << UMIN_AND2_4_STATE_BIT;
	//_AND2(u32_val, 5, Ia_and_Ic_is_smaller_than_Iust, 0, u32_val, 12);
    lV = wrp.bool_vars.Ia_and_Ic_is_smaller_than_Iust&&
	(u32_bit_holder&(1<<UMIN_MCTRLR_UMIN1_IBLK_BIT));
	u32_bit_holder |= lV << UMIN_AND2_5_STATE_BIT;
	//_INVERTOR(u32_val, 5, u32_val, 5);
    lV = !(u32_bit_holder&(1<<UMIN_MCTRLR_UMIN1_IBLK_BIT));
	u32_bit_holder |= (lV) << UMIN_NOT_6_STATE_BIT;
	//_AND3(Ua_or_Ub_or_Uc_is_smaller_than_250mV, 0, u32_val, 4, u32_val, 5, u32_val, 13);
    lV = wrp.bool_vars.Ua_or_Ub_or_Uc_is_smaller_than_250mV&&
	(u32_bit_holder & (1 << (UMIN_MCTRLR_UMIN1_UBLK_BIT))|(1<<(UMIN_NOT_6_STATE_BIT)));
	u32_bit_holder |= lV << UMIN_AND3_7_STATE_BIT;
    //ПО Uблк. Umin1
    if (wrp.bool_vars.Ua_or_Ub_or_Uc_is_smaller_than_250mV)
      _SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN1);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_UBLK_UMIN1);
  } 
  else 
  {
    //Линейные
    wrp.bool_vars.Uab_is_smaller_than_Umin1 = measurement[IM_UAB] <= pick_up_U;
    wrp.bool_vars.Ubc_is_smaller_than_Umin1 = measurement[IM_UBC] <= pick_up_U;
    wrp.bool_vars.Uca_is_smaller_than_Umin1 = measurement[IM_UCA] <= pick_up_U;
    wrp.bool_vars.Uab_or_Ubc_or_Uca_is_smaller_than_250mV = (measurement[IM_UAB] <= pick_up_Ublk)
	|| (measurement[IM_UBC] <= pick_up_Ublk) || (measurement[IM_UCA] <= pick_up_Ublk);
	
	
	
    //_AND4(Uab_is_smaller_than_Umin1, 0, Ubc_is_smaller_than_Umin1, 0, Uca_is_smaller_than_Umin1, 0, u32_val, 3, u32_val, 9);
    lV = (wrp.lVl&( (1<<8)|(1<<9)|(1<<10) )!=0);
    u32_bit_holder |= lV << (UMIN_AND4_1_STATE_BIT);
	//_OR3(Uab_is_smaller_than_Umin1, 0, Ubc_is_smaller_than_Umin1, 0, Uca_is_smaller_than_Umin1, 0, u32_val, 10);
    lV = ( ( wrp.lVl&(1<<8))|(wrp.lVl&(1<<9)) |(wrp.lVl&(1<<10)) )!=0;
	u32_bit_holder |= lV << (UMIN_OR3_2_STATE_BIT);
	//_INVERTOR(u32_val, 3, u32_val, 3);
    lV = !(u32_bit_holder&(1<<UMIN_MCTRLR_PO_UMIN1_OR_AND_BIT)); 
    u32_bit_holder |= lV << (UMIN_NOT_3_STATE_BIT);
	//_AND2(u32_val, 10, u32_val, 3, u32_val, 11);
    lV = ( u32_bit_holder & ((1<< (UMIN_NOT_3_STATE_BIT))|(1<<UMIN_OR3_2_STATE_BIT)) ) != 0;
	u32_bit_holder |= lV << UMIN_AND2_4_STATE_BIT;
	//_AND2(u32_val, 5, Ia_and_Ic_is_smaller_than_Iust, 0, u32_val, 12);
    lV = wrp.bool_vars.Ia_and_Ic_is_smaller_than_Iust&&
	(u32_bit_holder&(1<<UMIN_MCTRLR_UMIN1_IBLK_BIT));
	u32_bit_holder |= lV << UMIN_AND2_5_STATE_BIT;
	//_INVERTOR(u32_val, 5, u32_val, 5);
    lV = !(u32_bit_holder&(1<<UMIN_MCTRLR_UMIN1_IBLK_BIT));
	u32_bit_holder |= (lV) << UMIN_NOT_6_STATE_BIT;
	//_AND3(Uab_or_Ubc_or_Uca_is_smaller_than_250mV, 0, u32_val, 4, u32_val, 5, u32_val, 13);
    lV = wrp.bool_vars.Uab_or_Ubc_or_Uca_is_smaller_than_250mV&&
	(u32_bit_holder & (1 << (UMIN_MCTRLR_UMIN1_UBLK_BIT))|(1<<(UMIN_NOT_6_STATE_BIT)));
	u32_bit_holder |= lV << UMIN_AND3_7_STATE_BIT;
    //ПО Uблк. Umin1
    if (wrp.bool_vars.Uab_or_Ubc_or_Uca_is_smaller_than_250mV)
      _SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN1);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_UBLK_UMIN1);
  }
  //_INVERTOR(u32_val, 12, u32_val, 12);
  lV = !(u32_bit_holder&(1<< UMIN_AND2_5_STATE_BIT));
	u32_bit_holder |= (lV) << UMIN_NOT_8_STATE_BIT;
  //_INVERTOR(u32_val, 13, u32_val, 13);
  lV = !(u32_bit_holder&(1<<UMIN_AND3_7_STATE_BIT ));
	u32_bit_holder |= (lV) << UMIN_NOT_9_STATE_BIT;
  //_OR3(u32_val, 7, u32_val, 9, u32_val, 11, u32_val, 14);
  lV = (1<<UMIN_DV_START_UMIN1)|(1<<UMIN_AND4_1_STATE_BIT)|(1<<UMIN_AND2_4_STATE_BIT);
  lV = (u32_bit_holder|lV)!=0;
  u32_bit_holder |= (lV) << UMIN_OR3_10_STATE_BIT;
  //_AND5(u32_val, 6, u32_val, 2, u32_val, 14, u32_val, 13, u32_val, 12, u32_val, 15);
  lV = (1<<UMIN_DV_BLOCK_INVERSE_CMD_BIT)|(1<<UMIN_MCTR_UMIN1_BIT)|(1<<UMIN_OR3_2_STATE_BIT)
  |(1<<UMIN_NOT_8_STATE_BIT)|(1<<UMIN_NOT_9_STATE_BIT);
  lV = (u32_bit_holder&lV)!=0;
  u32_bit_holder |= (lV) << UMIN_AND5_11_STATE_BIT;

  
  //ПО Umin1
  if (_GET_OUTPUT_STATE( u32_bit_holder, UMIN_AND5_11_STATE_BIT))
    _SET_BIT(p_active_functions, RANG_PO_UMIN1);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_UMIN1);
  
  _TIMER_T_0(INDEX_TIMER_UMIN1, current_settings_prt.timeout_Umin1[number_group_stp],
  u32_bit_holder, UMIN_PICKUP_BIT, u32_bit_holder, UMIN_TMR_STATE_BIT);
  
  //Сраб. Umin1
  if (_GET_OUTPUT_STATE( u32_bit_holder, UMIN_TMR_STATE_BIT))
    _SET_BIT(p_active_functions, RANG_UMIN1);
  else
    _CLEAR_BIT(p_active_functions, RANG_UMIN1);
}

//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````

