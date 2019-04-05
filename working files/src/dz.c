
void dz_handler(unsigned int *p_active_functions, unsigned int number_group_stp);
void fault_U_handler(unsigned int *p_active_functions, unsigned int number_group_stp);
void dz1_handler(unsigned int *p_active_functions, unsigned int number_group_stp);

//https://en.wikipedia.org/wiki/Alternating_current
//Three-phase electrical single phase and neutral so use single Both, 
enum WRP_PHS_BIT_POS { 
    IA_M0_P9,//0
    IB_M0_P9,//1
	IC_M0_P9,//2
    IA_L0_P9,//3
    IB_L0_P9,//4
	IC_L0_P9,//5

TOTAL_WRP_PHS
//
};
typedef union dstLp_stp_state_Unn{ 
   struct {
      unsigned int po_1phs : 1; //1
      unsigned int po_2phs : 1; //2
      unsigned int po_3phs : 1; //3
      unsigned int po_Mphs : 1; //4
      unsigned int po_IA_max : 1; //5
      unsigned int po_IB_max : 1; //6
      unsigned int po_IC_max : 1; //7
//      unsigned int po_ : 1; //8
//      unsigned int po_ : 1; //9
    } bool_val;
    long lVl;
} Mphs_sphs_stp_state; //multi phase
Mphs_sphs_stp_state m_s_phs_stp_state;//multi single
long dstLImax = 0;char ch_IdxMaxphs = 0;
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void mf_of_handler(unsigned int *p_active_functions, unsigned int number_group_stp){
// ----------------  inner_outer_short_circuit It`s my name -------------------------
register long rL,rU,i;

//Detect Multi Pfase or Single Pfase
	rL = measurement[IM_IA];
	m_s_phs_stp_state.lVl &= 0x0f;//Clr Phase selector
	rU = IM_IA;
//Select Imax
	if(rL < measurement[IM_IB]){
		rL = measurement[IM_IB];
		rU = IM_IB;
	}	
	if(rL < measurement[IM_IC]){
		rL = measurement[IM_IC];
		rU = IM_IB;
	}	
	//Now Have Max
	rL =  dstLImax = measurement[rU];//measurement[rU]
	ch_IdxMaxphs = rU; 
	if(rU == IM_IA){
		m_s_phs_stp_state.bool_val.po_IA_max = 1;
	}else if(rU == IM_IB){
		m_s_phs_stp_state.bool_val.po_IB_max = 1;
	}else if(rU == IM_IC){
		m_s_phs_stp_state.bool_val.po_IC_max = 1;
	}
	rl *=9;rl/=10;
register union { 
   struct {
      unsigned int IaM0p9:1;//0
      unsigned int IbM0p9:1;//1
	  unsigned int IcM0p9:1;//2
      unsigned int IaL0p9:1;//3
      unsigned int IbL0p9:1;//4
	  unsigned int IcL0p9:1;//5
   } bool_vars;
  long lVl;
}wrp;	
	wrp.lVl = 0;
	wrp.bool_vars.IaM0p9 = (measurement[IM_IA]> rl);
	wrp.bool_vars.IbM0p9 = (measurement[IM_IB]> rl);
	wrp.bool_vars.IbM0p9 = (measurement[IM_IC]> rl);
	wrp.bool_vars.IaL0p9 = (measurement[IM_IA]< rl);
	wrp.bool_vars.IbL0p9 = (measurement[IM_IB]< rl);
	wrp.bool_vars.IbL0p9 = (measurement[IM_IC]< rl);
	if(wrp.lVl == 7){
		m_s_phs_stp_state.bool_val.po_3phs = 1;
		m_s_phs_stp_state.bool_val.po_Mphs = 1;
		//Select 3Pfase
	}else	if(wrp.lVl == ( (1<< IA_M0_P9) | (1<<IB_M0_P9) | (1<<IC_L0_P9 )) 
				|| (wrp.lVl == ((1<< IB_M0_P9) | (1<<IC_M0_P9) | (1<<IA_L0_P9) ) 
				|| (wrp.lVl == ((1<< IA_M0_P9) | (1<<IC_M0_P9) | (1<<IB_L0_P9) )){
					m_s_phs_stp_state.bool_val.po_2phs = 1;
					m_s_phs_stp_state.bool_val.po_Mphs = 1;
					//Select 2Pfase
	}
	else    if(wrp.lVl == ((1<< IA_L0_P9) | (1<<IB_L0_P9) | (1<<IC_M0_P9) ) 
				|| (wrp.lVl == (1<<IB_L0_P9) | (1<< IC_L0_P9) | (1<< IA_M0_P9) ) 
				|| (wrp.lVl == (1<<IA_L0_P9) | (1<<IC_L0_P9) | (1<<IB_M0_P9) )){
				m_s_phs_stp_state.bool_val.po_2phs = 1;
			//Select 1Pfase	
	}
//Select MPfase

}
//
//--------------------------------------------------------------------------------------------------------
enum FAULT_U_BIT_POS { 

//FAULT_U_MENU_STATE_BIT,
//FAULT_U_DV_FAULT_DST__L_CMD_BIT  = 1, 
FAULT_U_U2_STP_STATE_BIT,
FAULT_U_0DOT5_T_STATE_BIT,
FAULT_U_4IN_OR_EL_STATE_BIT,
FAULT_U_DSTL_TMR_STATE_BIT,
TOTAL_FAULT_U_BITS
};
#define UN_PHS	 57000
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void fault_U_handler(unsigned int *p_active_functions, unsigned int number_group_stp){
// ----------------  inner_outer_short_circuit It`s my name -------------------------
//First 
  unsigned long u32_bit_holder = 0;
  long i;
  
register union { 
   struct {
      unsigned int OR_1:1;//0
      unsigned int OR_2:1;//1
	  unsigned int OR_3:1;//2
      unsigned int OR_4:1;//3
      unsigned int AND1_1:1;//4
	  unsigned int AND1_2:1;//5
	  unsigned int AND1_3:1;//6
	  unsigned int AND2_1:1;//7
	  unsigned int AND2_2:1;//8
	  unsigned int AND2_3:1;//9
	  unsigned int AND3_1:1;//10
	  unsigned int AND3_2:1;//11
	  unsigned int AND3_3:1;//12
   } bool_vars;
  long lVl;
}wrp;  
   wrp.lVl = 0;
   if((_CHECK_SET_BIT(p_active_functions, RANG_EXT_NKN_DZ) != 0))
	wrp.bool_vars.OR_4 = 1;
   i = (12*I_NOM)/10;
   if( (measurement[IM_IA] < (unsigned long) i)
       &&  (measurement[IM_IB] < (unsigned long)i)
       &&  (measurement[IM_IC] < (unsigned long)i)
	  )
	  wrp.bool_vars.AND1_2 = 1; 
	i = (U_LINEAR_NOM*2)/10;  
  if( (measurement[IM_UAB] < (unsigned long)i)
       &&  (measurement[IM_UBC] < (unsigned long)i)
       &&  (measurement[IM_UCA] < (unsigned long)i)
	  )
	  wrp.bool_vars.AND1_3 = 1; 
   i = current_settings_prt.control_dz&MASKA_FOR_BIT(INDEX_CTR_NKN_DZ);
   if (i > 0){
	wrp.bool_vars.AND1_1 = 1;
	wrp.bool_vars.AND2_1 = 1;
	wrp.bool_vars.AND3_1 = 1;
	
   }
   if(wrp.lVl & ( (1<<4)| (1<<5)| (1<<6) ))
	wrp.bool_vars.OR_1 = 1;
	
   if (10*measurement[IM_U2] > (2*UN_PHS)){
		u32_bit_holder |= 1<<FAULT_U_U2_STP_STATE_BIT;
	}
     _TIMER_0_T(INDEX_TIMER_0DOT5_DZ, 500,
  u32_bit_holder, FAULT_U_U2_STP_STATE_BIT, u32_bit_holder, FAULT_U_0DOT5_T_STATE_BIT);
  if( u32_bit_holder & (1<<FAULT_U_0DOT5_T_STATE_BIT) )
	wrp.bool_vars.AND3_3 = 1;
  i =((10*measurement[IM_U2]*I_NOM)/(measurement[IM_I2]*UN_PHS);
   if (i > (2)){
		wrp.bool_vars.AND3_2 = 1;
		wrp.bool_vars.AND2_3 = 1;
	}
    if(wrp.lVl & ( (1<<10)| (1<<11)| (1<<12) ))
		wrp.bool_vars.OR_3 = 1;
	
	i =_CHECK_SET_BIT(p_active_functions, RANG_PO_DZ1);
	i |=_CHECK_SET_BIT(p_active_functions, RANG_PO_VPERED_DZ2);
	i |=_CHECK_SET_BIT(p_active_functions, RANG_PO_NAZAD_DZ2);
	i |=_CHECK_SET_BIT(p_active_functions, RANG_PO_NAZAD_DZ3);
	i |=_CHECK_SET_BIT(p_active_functions, RANG_PO_NAZAD_DZ3);	
	i |=_CHECK_SET_BIT(p_active_functions, RANG_PO_NAZAD_DZ4);
	i |=_CHECK_SET_BIT(p_active_functions, RANG_PO_NAZAD_DZ4);	
   if (i > 0){
	wrp.bool_vars.AND2_2 = 1;
	}
	if(wrp.lVl & ( (1<<7)| (1<<8)| (1<<9) ))
		wrp.bool_vars.OR_2 = 1;
  
  i =_CHECK_SET_BIT(p_active_functions, RANG_EXT_NKN_DZ);
   if (i > 0){
	wrp.bool_vars.OR_4 = 1;
	}
	if(wrp.lVl &0xf)
	u32_bit_holder |= 1<<FAULT_U_4IN_OR_EL_STATE_BIT;
	
  _TIMER_T_0(INDEX_TIMER_NKN_DZ, current_settings_prt.timeout_nkn_dz[number_group_stp],
  u32_bit_holder, FAULT_U_4IN_OR_EL_STATE_BIT, u32_bit_holder, FAULT_U_DSTL_TMR_STATE_BIT);

  //Сраб. 
  if ( u32_bit_holder&(1<<FAULT_U_DSTL_TMR_STATE_BIT ) )
    _SET_BIT(p_active_functions, RANG_NKN_DZ);
  else
    _CLEAR_BIT(p_active_functions, RANG_NKN_DZ);

 
}
//
//--------------------------------------------------------------------------------------------------------


//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void dz1_handler(unsigned int *p_active_functions, unsigned int number_group_stp){
// ----------------  inner_outer_short_circuit It`s my name -------------------------
long lV,rU;
unsigned long u32_bit_holder = 0; 
register union { 
   struct {
      unsigned int and4_1:1;//0
      unsigned int and4_2:1;//1
	  unsigned int and4_3:1;//2
      unsigned int and5_1:1;//3
      unsigned int and5_2:1;//4
	  unsigned int and5_3:1;//5
      unsigned int and4__:1;//6
      unsigned int and5__:1;//7
	  unsigned int or6_1:1;//8
	  unsigned int or6_2:1;//9
	  unsigned int not2_1:1;//10
	  unsigned int not7_1:1;//11
	  unsigned int or6_O1:1;//11-  O1 - means out 1
   } bool_vars;
  long lVl;
}wrp_sncn;
	wrp_sncn.lVl = 0;

	//Po Iblk
	rU = UN_PHS*25/10000;//142,5
	lVl = 500;
	if(   (measurement[IM_IA]< lVl) 
		&&(measurement[IM_IB]< lVl)
		&&(measurement[IM_IC]< lVl)){
		//wrp_sncn.bool_vars.and4_3 = 0;
		//wrp_sncn.bool_vars.and5_3 = 0;
		_SET_BIT(p_active_functions, RANG_PO_I_BLK_DZ);
	}	
	else{
		wrp_sncn.bool_vars.and4_3 = 1;
		wrp_sncn.bool_vars.and5_3 = 1;
		_CLEAR_BIT(p_active_functions, RANG_PO_I_BLK_DZ);
	}
	
	
	if(   (measurement[IM_UA]< rU) 
		&&(measurement[IM_UB]< rU)
		&&(measurement[IM_UC]< rU)){
		_SET_BIT(p_active_functions, RANG_PO_U_DZ);
		//wrp_sncn.bool_vars.and4_2 = 0;
		//wrp_sncn.bool_vars.and5_1 = 0;
	}	
	else{
		wrp_sncn.bool_vars.and4_2 = 1;
		wrp_sncn.bool_vars.and5_1 = 1;
	_CLEAR_BIT(p_active_functions, RANG_PO_U_DZ);
	}
	wrp_sncn.bool_vars.not7_1 = !wrp_sncn.bool_vars.and5_1;//Inv 3phs
	
	if(m_s_phs_stp_state.bool_val.po_3phs)
		wrp_sncn.bool_vars.and5_2 = 1;
		
	if(m_s_phs_stp_state.lVl&3)//Or1 analog
		wrp_sncn.bool_vars.and4_1 = 1;
	rU = wrp_sncn.lVl &( (1<<0)| (1<<1)| (1<<2));
	if(rU == ( (1<<0)| (1<<1)| (1<<2))){
		//wrp_sncn.bool_vars.and4__ = 1;
		wrp_sncn.bool_vars.or6_2 = 1;
	}
	rU = wrp_sncn.lVl &( (1<<3)| (1<<4)| (1<<5));
	if(rU == ( (1<<3)| (1<<4)| (1<<5))){
		wrp_sncn.bool_vars.and5__ = 1;
	}
	if( _CHECK_SET_BIT(p_active_functions, RANG_NKN_DZ)
		&& (wrp_sncn.bool_vars.not7_1))
		wrp_sncn.bool_vars.or6_1 = 1;
	rU =  wrp_sncn.lVl & ( (1<<8)| (1<<9));	
	if ( rU != 0 ){
		_SET_BIT(p_active_functions, RANG_SNKN_DZ);
		wrp_sncn.bool_vars.or6_O1 = 1;
	}
  else
    _CLEAR_BIT(p_active_functions, RANG_SNKN_DZ);	
		
//First Check Menu & Dv ON or OFF
register union { 
   struct {
      unsigned int and8_1:1;//0
      unsigned int and8_2:1;//1
	  unsigned int and8_3:1;//2
      unsigned int and8_4:1;//3
      unsigned int and9_1:1;//4
	  unsigned int and9_2:1;//5
      unsigned int and9_3:1;//6
      unsigned int and9_4:1;//7
	  unsigned int and9_5:1;//8
	  unsigned int nor7_1 :1;//9
	  unsigned int nor7_2 :1;//10
	  unsigned int nor7_3 :1;//11
	  unsigned int nor6_1 :1;//12
	  unsigned int nor6_2 :1;//13
	  unsigned int nor6_3 :1;//14
	  unsigned int nor6_4 :1;//15
	  unsigned int or4_1 :1;//17
	  unsigned int or4_2 :1;//18
	  unsigned int and5_1:1;//19
	  unsigned int and5_2:1;//21
	  unsigned int and4_1:1;//22
	  unsigned int and4_2:1;//23
	  unsigned int and2_1:1;//24
	  unsigned int and2_2:1;//25
	  unsigned int not3_1 :1;//26
	  unsigned int not10_1:1;//27
	  unsigned int nor5_1 :1;//28
	  unsigned int nor5_2 :1;//29
	  //unsigned int not10_1 :1;//30
	  //unsigned int not10_1 :1;//31
	  
   } bool_vars;
  long lVl;
}wrp_dz1;
//Calc  for 1 stages 7-9 elem
	wrp_dz1.lVl = 0;
	if(current_settings_prt.control_dz&MASKA_FOR_BIT(INDEX_CTR_DZ1))
	{
		wrp_dz1.bool_vars.and8_1 = 1;
		wrp_dz1.bool_vars.and9_1 = 1;
	}
	
	if(_CHECK_SET_BIT(p_active_functions, RANG_PO_DZ1) != 0)
		wrp_dz1.bool_vars.not10_1 = 1;
	if(_CHECK_SET_BIT(p_active_functions, RANG_PO_AMTZ_DZ1) != 0){
		wrp_dz1.bool_vars.nor6_4 = 1;
		wrp_dz1.bool_vars.nor5_2 = 1;
	}
	
	//amtz
	if(current_settings_prt.control_dz&MASKA_FOR_BIT(INDEX_CTR_DZ1_AMTZ)){
		wrp_dz1.bool_vars.and9_5 = 1;//CTR_DZ1_AMTZ
		wrp_dz1.bool_vars.and2_2 = 1;//CTR_DZ1_AMTZ
	}	
	else
		wrp_dz1.bool_vars.not3_1 = 1;
	//sncn&amtz	
	lV = wrp_sncn.bool_vars.nor6_O1;//sncn
	rU = lV& wrp_dz1.bool_vars.and2_2;
	if(rU == 1){
		wrp_dz1.bool_vars.and4_1 = 1;
		wrp_dz1.bool_vars.nor5_1 = 1;
	}else{

	}
	if(_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_DZ1) != 0){
		wrp_dz1.bool_vars.nor7_1 = 1;
		wrp_dz1.bool_vars.nor6_1 = 1;
	}	
	if(_CHECK_SET_BIT(p_active_functions, RANG_PO_I_BLK_DZ) != 0){
		wrp_dz1.bool_vars.nor7_2 = 1;
		wrp_dz1.bool_vars.nor6_3 = 1;
	}

	//nor5_2
	rU = wrp_dz1.lVl &( (1<<28)| (1<<29));
	if(rU != ( 0){
		wrp_dz1.bool_vars.nor7_3 = 1;
	}
	//rU-nor7
	rU = wrp_dz1.lVl &( (1<<9)|(1<<10)| (1<<11));
	if(rU == ( 0){                        
		lVl = 1;//wrp_dz1.bool_vars.nor7_3 = 0;     
	else
		lVl = 0;
	//and9
	rU = wrp_sncn.lVl &( (1<<4)| (1<<5)|| (1<<6)| (1<<7)| (1<<8));
	if(rU == ( (1<<4 )| (1<<5 )| (1<<6 )| (1<<7 )| (1<< 8))){
		wrp_sncn.bool_vars.nor5_2 = 1;
		wrp_dz1.bool_vars.nor6_4 = 1;
		_SET_BIT(p_active_functions, RANG_PO_AMTZ_DZ1);
	}
	else{
			wrp_sncn.bool_vars.nor5_2 = 0;
			wrp_dz1.bool_vars.nor6_4 = 0;
			_CLEAR_BIT(p_active_functions, RANG_PO_AMTZ_DZ1);
	}	
	
	rU = wrp_dz1.bool_vars.and4_1;
	rU &= ~(wrp_dz1.bool_vars.not10_1)&1;
    if(rU==1)
		wrp_dz1.bool_vars.nor6_2 = 1;
	//else
		//wrp_dz1.bool_vars.nor6_2 = 0;
	//nor6	
	;//pickup_dz1_amtz
	//Po Dz
	if(){//One
		current_settings_prt.pickup_dz1
	}else if(){ //2
		
	
	}else{//M
	
	}
	
	
    
}   
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void dz234_handler(unsigned int *p_active_functions, unsigned int number_group_stp){
// ----------------  inner_outer_short_circuit It`s my name -------------------------
//First Check Menu & Dv ON or OFF

//Calc  for 4 stages
  UNUSED(p_active_functions);
  UNUSED(number_group_stp);
 
}
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````
enum MCP_BIT_POS { 

MCP_DV_BLOCK_CMD_BIT  = 1,  
MCP_DV_BLOCK_INVERSE_CMD_BIT  ,  
MCP_MENU_P_3U0_STATE_BIT,
MCP_PICKUP_3U0_STATE_BIT,
MCP_TMR_3U0_STATE_BIT,
TOTAL_DZ_BITS
//
};
//const unsigned long MIN_LIMIT_I1_I2_P = MIN_LIMIT_FOR_I1_AND_I2;
typedef union mcp_stp_state_Unn{ 
   struct {
      unsigned int po_I1_lead_low_side  : 1; //1
      unsigned int po_I1_lead_high_side : 1; //2
      unsigned int po_I2_lead_low_side  : 1; //3
      unsigned int po_I2_lead_high_side : 1; //4
      unsigned int po_I2_I1_ls_lead     : 1; //5
      unsigned int po_I2_I1_hs_lead     : 1; //6
//      unsigned int po_ : 1; //7
//      unsigned int po_ : 1; //8
//      unsigned int po_ : 1; //9
    } bool_val;
    long lVl;
} Dz_stp_state; 
Dz_stp_state dz_stp_state ;

/*
_TIMER_T_0_LOCK(  //    reset outs only if on input set 0   
_TIMER_T_0(// reset outs  if global_timers[_index_timer] >= _max_count 
clr global_timers[_index_timer] if if _input == 0
_TIMER_0_T(// reset outs as _TIMER_T_0 but 
clr global_timers[_index_timer] if _input >0 <==add T
_TIMER_IMPULSE(
have _input->_c, and _INPUT->_C. _input it`s a shadow for front selection
          if (_c ^ _C)                                                  
          {                                                             
            if (_C) _input |= (unsigned int)(1 << _input_bit);          
            else _input &= (unsigned int)(~(1 << _input_bit));  
		}
Detect change 0-1. Then
if(global_timers[_index_timer] >= 0 
&& global_timers[_index_timer] < _max_count)                          
            _OUTPUT |= (unsigned int)(1 << _OUTPUT_BIT);               
          else                                                         
            _OUTPUT &= (unsigned int)(~(1 << _OUTPUT_BIT));
//this forms pulse 0 to _max_count			
*/