enum PG3U0_BIT_POS { 

G3U0_DV_BLOCK_CMD_BIT  = 1,  
G3U0_DV_BLOCK_INVERSE_CMD_BIT  ,  
G3U0_MENU_P_3U0_STATE_BIT,
G3U0_PICKUP_3U0_STATE_BIT,
G3U0_TMR_3U0_STATE_BIT,
TOTAL_G3U0_BITS
//LU_GEN_OP_EV_FIX_IBUS
};
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void p_3U0_handler(unsigned int *p_active_functions, unsigned int number_group_stp){
// ----------------    -------------------------
register unsigned long u32_bit_holder = 0;  
register union { 
   struct {
      unsigned int previous_state_po_3U0_1 : 1;
	  unsigned int g3U0_1r_is_larger_than_3U0_1:1;
   } bool_vars;
  long lVl;
}wrp;
   long lV; 
   wrp.lVl = 0;
   wrp.bool_vars.previous_state_po_3U0_1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_P_3U0) > 0;
unsigned long pick_up_3U0_1 = wrp.bool_vars.previous_state_po_3U0_1 ?
          current_settings_prt.setpoint_P_3U0[number_group_stp] * KOEF_POVERNENNJA_3U0 / 100 :
          current_settings_prt.setpoint_P_3U0[number_group_stp];
wrp.bool_vars.g3U0_1r_is_larger_than_3U0_1 = measurement[IM_3U0_r] >= pick_up_3U0_1;

  //ДВ
  lV = (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_P_3U0) != 0);
  u32_bit_holder |= lV << G3U0_DV_BLOCK_CMD_BIT;
  u32_bit_holder |= (!lV)<< G3U0_DV_BLOCK_INVERSE_CMD_BIT;//_INVERTOR(tmp_value, 6, tmp_value, 6);
  lV = ((current_settings_prt.control_P_3U0 & CTR_P_3U0_STATE) != 0);
  u32_bit_holder |= lV << G3U0_MENU_P_3U0_STATE_BIT;
  lV = (u32_bit_holder&(1<<G3U0_DV_BLOCK_INVERSE_CMD_BIT)) 
  && (u32_bit_holder&(1<<G3U0_MENU_P_3U0_STATE_BIT)) && wrp.bool_vars.g3U0_1r_is_larger_than_3U0_1;

//RANG_BLOCK_P_3U0,
//RANG_PO_P_3U0,
//RANG_P_3U0,
u32_bit_holder |= lV << G3U0_PICKUP_3U0_STATE_BIT;
  //ПО 
  if (lV)
    _SET_BIT(p_active_functions, RANG_PO_P_3U0);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_P_3U0);
  
  _TIMER_T_0(INDEX_TIMER_P_3U0, current_settings_prt.timeout_P_3U0[number_group_stp],
  u32_bit_holder, G3U0_PICKUP_3U0_STATE_BIT, u32_bit_holder, G3U0_TMR_3U0_STATE_BIT);
  
  //Сраб. 
  if ( u32_bit_holder&(1<<G3U0_TMR_3U0_STATE_BIT ) )
    _SET_BIT(p_active_functions, RANG_P_3U0);
  else
    _CLEAR_BIT(p_active_functions, RANG_P_3U0);



  

}
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````

