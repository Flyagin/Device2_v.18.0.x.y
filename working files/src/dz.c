#include "const_global.h"
void dz_handler(unsigned int *p_active_functions, unsigned int number_group_stp);
void fault_U_handler(unsigned int *p_active_functions, unsigned int number_group_stp);
void dz1_handler(unsigned int *p_active_functions, unsigned int number_group_stp);
void mf_of_handler(unsigned int *p_active_functions, unsigned int number_group_stp);
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
register long rL,rU;
  UNUSED(number_group_stp);
//Detect Multi Pfase or Single Pfase
    rL = measurement[IM_IA];
    m_s_phs_stp_state.lVl &= 0x0f;//Clr Phase selector
    rU = IM_IA;
//Select Imax
    if(rL < (long) measurement[IM_IB]){
        rL = measurement[IM_IB];
        rU = IM_IB;
    }   
    if(rL < (long) measurement[IM_IC]){
        rL = measurement[IM_IC];
        rU = IM_IB;
    }   
    //Now Have Max
     dstLImax = rL = measurement[rU];//measurement[rU]
    ch_IdxMaxphs = rU; 
    if(rU == IM_IA){
        m_s_phs_stp_state.bool_val.po_IA_max = 1;
    }else if(rU == IM_IB){
        m_s_phs_stp_state.bool_val.po_IB_max = 1;
    }else if(rU == IM_IC){
        m_s_phs_stp_state.bool_val.po_IC_max = 1;
    }
    rL *=9;rL/=10;
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
    wrp.bool_vars.IaM0p9 = (long)(measurement[IM_IA]> (unsigned long)rL);
    wrp.bool_vars.IbM0p9 = (long)(measurement[IM_IB]> (unsigned long)rL);
    wrp.bool_vars.IbM0p9 = (long)(measurement[IM_IC]> (unsigned long)rL);
    wrp.bool_vars.IaL0p9 = (long)(measurement[IM_IA]< (unsigned long)rL);
    wrp.bool_vars.IbL0p9 = (long)(measurement[IM_IB]< (unsigned long)rL);
    wrp.bool_vars.IbL0p9 = (long)(measurement[IM_IC]< (unsigned long)rL);
register long lV;
    
    lV  = wrp.lVl&7;
    if(lV == 7){
        m_s_phs_stp_state.bool_val.po_3phs = 1;
        m_s_phs_stp_state.bool_val.po_Mphs = 1;
        //Select 3Pfase
    }else   if(wrp.lVl == ( (1<< IA_M0_P9) | (1<<IB_M0_P9) | (1<<IC_L0_P9 )) 
                || (wrp.lVl == ((1<< IB_M0_P9) | (1<<IC_M0_P9) | (1<<IA_L0_P9)) ) 
                || (wrp.lVl == ((1<< IA_M0_P9) | (1<<IC_M0_P9) | (1<<IB_L0_P9))) ){
                    m_s_phs_stp_state.bool_val.po_2phs = 1;
                    m_s_phs_stp_state.bool_val.po_Mphs = 1;
                    //Select 2Pfase
    }
    else    if(wrp.lVl == ( (1<< IA_L0_P9) | (1<<IB_L0_P9) | (1<<IC_M0_P9) ) 
                || (wrp.lVl == ((1<<IB_L0_P9) | (1<<IC_L0_P9) | (1<<IA_M0_P9)) ) 
                || (wrp.lVl == ((1<<IA_L0_P9) | (1<<IC_L0_P9) | (1<<IB_M0_P9))  ) ){
                m_s_phs_stp_state.bool_val.po_1phs = 1;
            //Select 1Pfase
            }
//Select MPfase
lV  = m_s_phs_stp_state.bool_val.po_1phs;
  if (lV)
    _SET_BIT(p_active_functions, RANG_1KZ);
  else
    _CLEAR_BIT(p_active_functions, RANG_1KZ);
lV  = m_s_phs_stp_state.bool_val.po_2phs;
  if (lV)
    _SET_BIT(p_active_functions, RANG_2KZ);
  else
    _CLEAR_BIT(p_active_functions, RANG_2KZ);
lV  = m_s_phs_stp_state.bool_val.po_3phs;
  if (lV)
    _SET_BIT(p_active_functions, RANG_3KZ);
  else
    _CLEAR_BIT(p_active_functions, RANG_3KZ);

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
#define UN_PHS   57000
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
  i = (10*measurement[IM_U2]*I_NOM)/(measurement[IM_I2]*UN_PHS);
   if (i > (2)){
        wrp.bool_vars.AND3_2 = 1;
        wrp.bool_vars.AND2_3 = 1;
    }
    if(wrp.lVl & ( (1<<10)| (1<<11)| (1<<12) ))
        wrp.bool_vars.OR_3 = 1;
    
    i =_CHECK_SET_BIT(p_active_functions, RANG_PO_DZ1);
    i |=_CHECK_SET_BIT(p_active_functions, RANG_PO_DIR_DZ2);
    i |=_CHECK_SET_BIT(p_active_functions, RANG_PO_INV_DZ2);
    i |=_CHECK_SET_BIT(p_active_functions, RANG_PO_DIR_DZ3);
    i |=_CHECK_SET_BIT(p_active_functions, RANG_PO_INV_DZ3);  
    i |=_CHECK_SET_BIT(p_active_functions, RANG_PO_DIR_DZ3);
    i |=_CHECK_SET_BIT(p_active_functions, RANG_PO_INV_DZ4);  
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

enum DZ1_BIT_POS { 

AMTZ1_PICKUP_STATE_BIT,
AMTZ1_TMR_STATE_BIT,
DZ1_PICKUP_STATE_BIT,
DZ1_TMR_STATE_BIT,
TOTAL_DZ1_BITS
//
};
char chGbl_3Phs_Dz;
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void dz1_handler(unsigned int *p_active_functions, unsigned int number_group_stp){
// ----------------  inner_outer_short_circuit It`s my name -------------------------
long lV;unsigned long rU;
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
    lV = 500;
    if(   (measurement[IM_IA]< (unsigned long)lV) 
        &&(measurement[IM_IB]< (unsigned long)lV)
        &&(measurement[IM_IC]< (unsigned long)lV)){
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
    chGbl_3Phs_Dz = wrp_sncn.bool_vars.and5__;
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
      unsigned int reserv :1;//16
      unsigned int or4_1 :1;//17
      unsigned int or4_2 :1;//18
      unsigned int and5_1:1;//19
      unsigned int reser1:1;//20
      unsigned int and5_2:1;//21
      unsigned int and4_1:1;//22
      unsigned int and4_2:1;//23
      unsigned int and2_1:1;//24
      unsigned int and2_2:1;//25
      unsigned int not3_1 :1;//26
      unsigned int not10_1:1;//27
      unsigned int nor5_1 :1;//28
      unsigned int nor5_2 :1;//29
      unsigned int reser2 :1;//30
      unsigned int reser3 :1;//31
      
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
    lV = wrp_sncn.bool_vars.or6_O1;//sncn
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
    if(rU !=  0){
        wrp_dz1.bool_vars.nor7_3 = 1;
    }
    //rU-nor7
    rU = wrp_dz1.lVl &( (1<<9)|(1<<10)| (1<<11));
    if(rU ==  0)                        
        lV = 1;//wrp_dz1.bool_vars.nor7_3 = 0;     
    else
        lV = 0;
    //and9
    rU = wrp_sncn.lVl &( (1<<4)| (1<<5)|| (1<<6)| (1<<7)| (1<<8));
    if(rU == ( (1<<4 )| (1<<5 )| (1<<6 )| (1<<7 )| (1<< 8))){
        wrp_dz1.bool_vars.nor5_2 = 1;//?
        wrp_dz1.bool_vars.nor6_4 = 1;
        _SET_BIT(p_active_functions, RANG_PO_AMTZ_DZ1);
        u32_bit_holder |= 1<< AMTZ1_PICKUP_STATE_BIT;
         _TIMER_T_0(INDEX_TIMER_DZ1_AMTZ, current_settings_prt.timeout_dz1_amtz[number_group_stp],
  u32_bit_holder, AMTZ1_PICKUP_STATE_BIT, u32_bit_holder, AMTZ1_TMR_STATE_BIT);

    }
    else{
            wrp_dz1.bool_vars.nor5_2 = 0;//?
            wrp_dz1.bool_vars.nor6_4 = 0;
            _CLEAR_BIT(p_active_functions, RANG_PO_AMTZ_DZ1);
            //u32_bit_holder ~= 1<< AMTZ1_PICKUP_STATE_BIT;
             _TIMER_T_0(INDEX_TIMER_DZ1_AMTZ, current_settings_prt.timeout_dz1_amtz[number_group_stp],
  u32_bit_holder, AMTZ1_PICKUP_STATE_BIT, u32_bit_holder, AMTZ1_TMR_STATE_BIT);
  
    }   
    
    rU = wrp_dz1.bool_vars.and4_1;
    rU &= (~wrp_dz1.bool_vars.not10_1)&1;
    if(rU==1)
        wrp_dz1.bool_vars.nor6_2 = 1;
    //else
        //wrp_dz1.bool_vars.nor6_2 = 0;
    
    ;//pickup_dz1_amtz
    //Po Dz
	rU = wrp_dz1.bool_vars.not10_1;
	unsigned long pick_up_Resistance_dstLp1 = 0;
	if(rU = 0)
		pick_up_Resistance_dstLp1 = (sLV.p_current_settings_prt->pickup_dz1) * KOEF_POVERNENNJA_GENERAL_UP  / 100;
	else
		pick_up_Resistance_dstLp1 = sLV.p_current_settings_prt->pickup_dz1;
	if( (measurement[z] > pick_up_Resistance_dstLp1)
     || (measurement[z] > pick_up_Resistance_dstLp1)
     || (measurement[z] > pick_up_Resistance_dstLp1)
    )
        p2.bool_vars.and8_2 = 1;//rU = 1;
    else
        p2.bool_vars.and8_2 = 0;//rU = 0;	
//  if(){//One
//      current_settings_prt.pickup_dz1
//  }else if(){ //2
//      
//  
//  }else{//M
//  
//  }
//nor6  
    rU = wrp_dz1.lVl &( (1<<12)|(1<<13)| (1<<14)| (1<<15));
    if(rU ==  0)                        
        lV = 1;//wrp_dz1.bool_vars.nor7_3 = 0;     
    else
        lV = 0;
    //and8
    rU = wrp_dz1.lVl &(  (1<<0)|| (1<<1)| (1<<2)| (1<<3));
    if(rU == (  (1<<0 )| (1<<1 )| (1<<2 )| (1<< 3))){
        //wrp_sncn.bool_vars.nor5_2 = 1;
        //wrp_dz1.bool_vars.nor6_4 = 1;
        u32_bit_holder |= 1<< DZ1_PICKUP_STATE_BIT;
        _SET_BIT(p_active_functions, RANG_PO_DZ1);
        _TIMER_T_0(INDEX_TIMER_DZ2_DIR, current_settings_prt.timeout_dz1[number_group_stp],
  u32_bit_holder, DZ1_PICKUP_STATE_BIT, u32_bit_holder, DZ1_TMR_STATE_BIT);

    }
    else{
        _CLEAR_BIT(p_active_functions, RANG_PO_DZ1);
        _TIMER_T_0(INDEX_TIMER_DZ2_DIR, current_settings_prt.timeout_dz1[number_group_stp],
  u32_bit_holder, DZ1_PICKUP_STATE_BIT, u32_bit_holder, DZ1_TMR_STATE_BIT);

    }   
    
    
    
}   
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````
enum DZ2_BIT_POS { 

ACC_AMTZ2_TMR_IN_BIT,
ACC_DZ2__TMR_IN_BIT,
ACC_AMTZ2_TMR_BIT,
ACC_DZ2__TMR_BIT,

//AMTZ2_PICKUP_STATE_BIT,
AMTZ2_TMR_IN_BIT,
AMTZ2_TMR_BIT,
AMTZ2_ACC_TMR_IN_BIT,
AMTZ2_ACC_TMR_BIT,

//DZ2_PICKUP_STATE_BIT,
DZ2_DIR_TMR_IN_BIT,
DZ2_DIR_TMR_STATE_BIT,
DZ2_INV_TMR_IN_BIT,
DZ2_INV_TMR_STATE_BIT,
DZ2_DIR_ACC_TMR_IN_BIT,
DZ2_DIR_ACC_TMR_STATE_BIT,
DZ2_INV_ACC_TMR_IN_BIT,
DZ2_INV_ACC_TMR_STATE_BIT,

TOTAL_DZ2_BITS
//
};
enum DZ_SEL_BIT_POS { 


DZ2_STAGE_BIT,
DZ3_STAGE_BIT,
DZ4_STAGE_BIT,
STP_I_A_MCP_DST_LP_STAGE2_BIT,
STP_I_A_MCP_DST_LP_STAGE3_BIT,
STP_I_A_MCP_DST_LP_STAGE4_BIT,


TOTAL_DZ_STAGES_BITS
//
};
enum DZ_TMR_SEL_BIT_POS { 
STP_I_AMCP_DST_LP_STAGE_BIT,
STP_DIR_DST_LP_STAGE_BIT,
STP_INV_DST_LP_STAGE_BIT,

T_AMCP_IN_BIT,
T_ACC_AMCP_IN_BIT,
T_AMCP_OUT_BIT,
T_ACC_AMCP_OUT_BIT,

T_DIR_IN_BIT,
T_ACC_DIR_IN_BIT,
T_DIR_OUT_BIT,
T_ACC_DIR_OUT_BIT,

T_INV_IN_BIT,
T_ACC_INV_IN_BIT,
T_INV_OUT_BIT,
T_ACC_INV_OUT_BIT,


TOTAL_TMR_SEL_BITS
//
};
enum DZ_State_p1234_Modified_Const{
P1_MODIFIED_BIT,
P2_MODIFIED_BIT,
P3_MODIFIED_BIT,
P4_MODIFIED_BIT,

TOTAL_P_MODIFY_BITS

};
typedef union mcp_stp_state_Unn1{ 
   struct {
      unsigned int or2__i_0 :1; //0
      unsigned int or2__i_1 :1; //1
      unsigned int and3_i_0 :1; //2
      unsigned int and3_i_1 :1; //3
      unsigned int and4_i_0 :1; //4
      unsigned int and4_i_1 :1; //5
      unsigned int and5_i_0 :1; //6
      unsigned int and5_i_1 :1; //7
      unsigned int and6_i_0 :1; //8
      unsigned int and6_i_1 :1; //9
      unsigned int and4_o_0 :1; //10
      unsigned int and5_o_0 :1; //11
      unsigned int and6_o_0 :1; //12
      unsigned int or7__i_0 :1; //13
      unsigned int or7__i_1 :1; //14
      unsigned int or8__i_0 :1; //15
      unsigned int or8__i_1 :1; //16
      unsigned int not9_o_0 :1; //17
      unsigned int not10_o_0 :1;//18
      unsigned int and17_i_0 :1;//19 
      unsigned int and17_i_1 :1;//20 
      unsigned int or12__i_1 :1;//21
      unsigned int or12__i_0 :1;//22
      unsigned int or13__i_1 :1;//23
      unsigned int or13__i_0 :1;//24
      unsigned int or18__i_1 :1;//25
      unsigned int or18__i_0 :1;//26
      unsigned int not15_o_0 :1;//27
      unsigned int and16_i_0 :1;//28
      unsigned int and16_i_1 :1;//29
//      unsigned int  :1;//30
//      unsigned int  :1;//31
//      unsigned int ; :1//
//      unsigned int ; :1//
   
    } bool_vars;
    long lVl;
} Dz2_stp_p1_state; //ex- extended
typedef union mcp_stp_state_Unn2{ 
   struct {
      unsigned int and22_i_0 :1; //0
      unsigned int and22_i_1 :1; //1
      unsigned int and22_i_2 :1; //2
//      unsigned int and22_i_3 :1; //2
      unsigned int and22_i_4 :1; //3
      unsigned int and24_i_0 :1; //4
      unsigned int and24_i_1 :1; //5
      unsigned int and24_i_2 :1; //6
      unsigned int and24_i_3 :1; //7
      unsigned int and24_i_4 :1; //8
      unsigned int and26_i_0 :1; //9
      unsigned int and26_i_1 :1;//10
      unsigned int and26_i_2 :1;//11
      unsigned int and26_i_3 :1;//12
      unsigned int and26_i_4 :1;//13
      unsigned int and26_i_5 :1;//14
      unsigned int nor19_i_0 :1;//15
      unsigned int nor19_i_1 :1;//16
      unsigned int nor19_i_2 :1;//17
      unsigned int nor19_i_3 :1;//18
      unsigned int nor20_i_0 :1;//19
      unsigned int nor20_i_1 :1;//20
      unsigned int nor20_i_2 :1;//21
      unsigned int nor20_i_3 :1;//22
      unsigned int nor21_i_0 :1;//23
      unsigned int nor21_i_1 :1;//24
      unsigned int nor21_i_2 :1;//25
      unsigned int not23_o_0 :1;//26
      unsigned int not25_o_0 :1;//27
      unsigned int or18__i_1 :1;//28
      unsigned int or18__i_0 :1;//29
      unsigned int and22_i_3 :1;//30
      unsigned int b31 :1;//31    
    } bool_vars;
    long lVl;
} Dz2_stp_p2_state; //ex- extended
typedef union mcp_stp_state_Unn3{ 
   struct {
      unsigned int or27_i_0 :1; //0
      unsigned int or27_i_1 :1; //1
      unsigned int not28_o_0:1; //2
      unsigned int or29_i_0 :1; //2
      unsigned int or29_i_1 :1; //3
      unsigned int not30_o_0:1; //4
      unsigned int and31_i_0:1; //5
      unsigned int and31_i_1:1; //6
      unsigned int and31_i_2:1; //7
      unsigned int and32_i_0:1; //8
      unsigned int and32_i_1:1; //9
      unsigned int and32_i_2:1; //10
      unsigned int and31_o_0:1; //11
      unsigned int and32_o_0:1; //12
      unsigned int or33_i_0 :1; //13
      unsigned int or33_i_1 :1; //14
      unsigned int or34_i_0 :1; //15
      unsigned int or34_i_1 :1; //16
      unsigned int not35_o_0:1; //17
      unsigned int or36_i_0 :1; //18
      unsigned int or36_i_1 :1; //19
      unsigned int not37_o_0:1; //20
      unsigned int or38_i_0 :1; //21
      unsigned int or38_i_1 :1; //22
      unsigned int not39_o_0:1; //23
      unsigned int or40_i_0 :1; //24
      unsigned int or40_i_1 :1; //25
      unsigned int not41_o_0:1; //26
      unsigned int b27 :1;//27
      unsigned int b28 :1;//28
      unsigned int b29 :1;//29
      unsigned int b30 :1;//30
      unsigned int b31 :1;//31    
    } bool_vars;
    long lVl;
} Dz2_stp_p3_state; //ex- extended
typedef union mcp_stp_state_Unn4{ 
   struct {
      unsigned int and42_i_0 :1; //0
      unsigned int and42_i_1 :1; //1
      unsigned int and42_i_2 :1; //2
      unsigned int and43_i_0 :1; //3
      unsigned int and43_i_1 :1; //4
      unsigned int and43_i_2 :1; //5
      unsigned int and44_i_0 :1; //6
      unsigned int and44_i_1 :1; //7
      unsigned int and44_i_2 :1; //8
      unsigned int and45_i_0 :1; //9
      unsigned int and45_i_1 :1;//10
      unsigned int and45_i_2 :1;//11
      unsigned int and42_o_0 :1;//12
      unsigned int and43_o_0 :1;//13
      unsigned int and44_o_0 :1;//14
      unsigned int and45_o_0 :1;//15
      unsigned int or46_i_0  :1;//16
      unsigned int or46_i_1  :1;//17
      unsigned int or46_i_2  :1;//18
      unsigned int or46_i_3  :1;//19
      unsigned int and11_i_0 :1;//20
      unsigned int and11_i_1 :1;//21
      unsigned int and14_i_0 :1;//22
      unsigned int and14_i_1 :1;//23
      unsigned int b24 :1;//24
      unsigned int b25 :1;//25
      unsigned int b26 :1;//26
      unsigned int b27 :1;//27
      unsigned int b28 :1;//28
      unsigned int b29 :1;//29
      unsigned int b30 :1;//30
      unsigned int b31 :1;//31    
    } bool_vars;
    long lVl;
} Dz2_stp_p4_state; //ex- extended
typedef struct tag_HdrBoolWord{
    char chIdxstage;
    char ch_p1234_modified;
}HdrBoolWordDsc;
typedef struct tag_BoolWord{
    struct BW{
    Dz2_stp_p1_state p1;
    Dz2_stp_p2_state p2;
    Dz2_stp_p3_state p3;
    Dz2_stp_p4_state p4;
    } ar_bw[TOTAL_DZ_STAGES_BITS];
    unsigned long ulStpDzfield;       //05
    HdrBoolWordDsc hdrBW;
    //May be insert Aux Information about State of Using this Object
}BoolWordsHldrDsc;
BoolWordsHldrDsc bw_dstLp_dt;

void dz2_handler(unsigned int *p_active_functions, unsigned int number_group_stp );
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void dz2_handler(unsigned int *p_active_functions, unsigned int number_group_stp ){
// ----------------  inner_outer_short_circuit It`s my name -------------------------
struct{
    char  ch_stage_selector;
    __SETTINGS *p_current_settings_prt;
    Dz2_stp_p1_state *p_p1;
    Dz2_stp_p2_state *p_p2;
    Dz2_stp_p3_state *p_p3;
    Dz2_stp_p4_state *p_p4;
    
}sLV;

unsigned long u32_bit_holder = 0; 
{
register long i;
sLV.p_current_settings_prt = &current_settings_prt;
sLV.ch_stage_selector = i = bw_dstLp_dt.hdrBW.chIdxstage;
sLV.p_p1 = & bw_dstLp_dt.ar_bw[i].p1;
sLV.p_p2 = & bw_dstLp_dt.ar_bw[i].p2;
sLV.p_p3 = & bw_dstLp_dt.ar_bw[i].p3;
sLV.p_p4 = & bw_dstLp_dt.ar_bw[i].p4;
//Clr untriggered command
sLV.p_p1->lVl &= 0x0;
sLV.p_p2->lVl &= 0x0;
sLV.p_p3->lVl &= (1<<11) | (1<<12);//and31_o_0 and32_o_0
sLV.p_p4->lVl &= (1<<12)|(1<<13)|(1<<14)|(1<<15);//and42_o_0 and43_o_0 and44_o_0 and45_o_0 
                                      
                                     
                                     
}
    do{
        //register void* pv;
        register Dz2_stp_p1_state p1;
        long lV,rU;
        if(bw_dstLp_dt.hdrBW.ch_p1234_modified & (1<<P1_MODIFIED_BIT))
            p1.lVl = sLV.p_p1->lVl;//Mask?
        else
            p1.lVl = 0;
        if (sLV.ch_stage_selector == DZ2_STAGE_BIT){
            if(_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_PR_DZ2) != 0){
                lV = 0;

            }
            else{
                lV = 1;
                p1.bool_vars.and4_i_0 = lV;
                p1.bool_vars.and5_i_0 = lV;
                p1.bool_vars.and6_i_0 = lV;
            }
            lV = (sLV.p_current_settings_prt->control_dz)&MASKA_FOR_BIT(INDEX_CTR_DZ2_CONST_PR);
            if(lV != 0)
                p1.bool_vars.or2__i_0 = 1;
                
            if(_CHECK_SET_BIT(p_active_functions, RANG_OP_PR_DZ2) != 0)
                p1.bool_vars.or2__i_1 = 1;

            lV = (sLV.p_current_settings_prt->control_dz)&MASKA_FOR_BIT(INDEX_CTR_DZ2_PR_VID_DV);
            if(lV != 0)
                p1.bool_vars.and3_i_0 = 1;  
            if(_CHECK_SET_BIT(p_active_functions, RANG_STATE_VV) != 0)
                p1.bool_vars.and3_i_1 = 1;  
            //or2
            if( (p1.lVl&((1<<0)|(1<<1))) > 0 )
                p1.bool_vars.and4_i_1 = 1;
            //and3
            rU = p1.lVl&((1<<2)|(1<<3)); 
            if(rU == ((1<<2)|(1<<3)))
            u32_bit_holder |= (1<< ACC_AMTZ2_TMR_IN_BIT)|(1<<ACC_DZ2__TMR_IN_BIT);
            _TIMER_0_T(INDEX_TIMER_DZ2_AMTZ_VVID_PR, sLV.p_current_settings_prt->timeout_dz2_amtz_vvid_pr[number_group_stp],
  u32_bit_holder, ACC_AMTZ2_TMR_IN_BIT, u32_bit_holder, ACC_AMTZ2_TMR_BIT);
            _TIMER_0_T(INDEX_TIMER_DZ2_VVID_PR, sLV.p_current_settings_prt->timeout_dz2_vvid_pr[number_group_stp],
  u32_bit_holder, ACC_DZ2__TMR_IN_BIT, u32_bit_holder, ACC_DZ2__TMR_BIT);
            //and6
            if ( u32_bit_holder&(1<<ACC_AMTZ2_TMR_BIT ) )
                p1.bool_vars.and6_i_1 = 1;
            //and5
            if ( u32_bit_holder&(1<<ACC_DZ2__TMR_BIT ) )
                p1.bool_vars.and5_i_1 = 1;
    
        }
        else if(sLV.ch_stage_selector == DZ3_STAGE_BIT){
            if(_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_PR_DZ3) != 0){
                lV = 0;

            }
            else{
                lV = 1;
                p1.bool_vars.and4_i_0 = lV;
                p1.bool_vars.and5_i_0 = lV;
                p1.bool_vars.and6_i_0 = lV;
            }
        }
        else if(sLV.ch_stage_selector == DZ4_STAGE_BIT){
            if(_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_PR_DZ4) != 0){
                lV = 0;
            }
            else{
                lV = 1;
                p1.bool_vars.and4_i_0 = lV;
                p1.bool_vars.and5_i_0 = lV;
                p1.bool_vars.and6_i_0 = lV;
            }        
        }
        
        
        rU = p1.lVl&((1<<4)|(1<<5)); //and4
        if(rU == ((1<<5)|(1<<5)))    
        p1.bool_vars.and4_o_0 = 1;
        rU = p1.lVl&((1<<6)|(1<<7)); 
        if(rU == ((1<<6)|(1<<7)))    
        p1.bool_vars.and5_o_0 = 1;
        rU = p1.lVl&((1<<8)|(1<<9)); 
        if(rU == ((1<<8)|(1<<9)))    
        p1.bool_vars.and6_o_0 = 1;
        
        
        
         if( (p1.lVl&((1<<13)|(1<<14))) != 0 ){//or7 2 customer
                sLV.p_p3->lVl |= (1<<21) | (1<<15) ;//Avt pry vkl VV uskorenye DZ
                //or38_i_0 :1; //21 or34_i_0 :1; //15
                bw_dstLp_dt.hdrBW.ch_p1234_modified |= (1<<P3_MODIFIED_BIT);
        }else{
            p1.bool_vars.not9_o_0 = 1;//Net uskoreniya
        }   
         if( (p1.lVl&((1<<15)|(1<<16))) != 0 ){//or8 2 customer DZ
               //or27_i_0 :1; //0
               sLV.p_p3->lVl |= (1<<0);//Avt pry vkl VV uskorenye AMTZ
                bw_dstLp_dt.hdrBW.ch_p1234_modified |= (1<<P3_MODIFIED_BIT);
        }else{
                p1.bool_vars.not10_o_0  = 1;//Net uskoreniya AMTZ
        }
                
    }while(sLV.ch_stage_selector > TOTAL_DZ_STAGES_BITS);
    
    do{
        //register void* pv;
        register Dz2_stp_p2_state p2;
        long lV,rU;
        
        if(bw_dstLp_dt.hdrBW.ch_p1234_modified & (1<<P2_MODIFIED_BIT))
            p2.lVl = sLV.p_p2->lVl;//Mask?
        else
            p2.lVl = 0;
            //and 11//sLV.p_p4->lVl |= (1<<20);//and11_i_0 :1;//20
            //sLV.p_p4->lVl |= (1<<21);//and11_i_1 :1;//21
        sLV.p_p1->bool_vars.or12__i_1 = chGbl_3Phs_Dz;
        sLV.p_p1->bool_vars.or13__i_1 = chGbl_3Phs_Dz;
        if(_CHECK_SET_BIT(p_active_functions, RANG_SNKN_DZ) != 0){
            sLV.p_p4->bool_vars.and14_i_0 = 1;
            sLV.p_p4->bool_vars.and11_i_1 = 1;
        }else{
            sLV.p_p4->bool_vars.and14_i_0 = 0;
            sLV.p_p4->bool_vars.and11_i_1 = 0;
        }           

            
        if (sLV.ch_stage_selector == DZ2_STAGE_BIT){
        
            //Eval FCHE
            //
            
            //or12
            if(_CHECK_SET_BIT(p_active_functions, RANG_SECTOR_DIR_DZ2) != 0)
                sLV.p_p1->bool_vars.or12__i_0 = 1;
             
            //or13
            if(_CHECK_SET_BIT(p_active_functions, RANG_SECTOR_INV_DZ2) != 0)
                sLV.p_p1->bool_vars.or13__i_0 = 1;
            if(_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_DZ2) != 0){
                lV = 1;
                p2.bool_vars.nor19_i_0 = lV;
                p2.bool_vars.nor20_i_0 = lV;
                p2.bool_vars.nor21_i_0 = lV;
            }
            
            if(_CHECK_SET_BIT(p_active_functions, RANG_PO_I_BLK_DZ) != 0){
                lV = 1;
                p2.bool_vars.nor19_i_1 = lV;
                p2.bool_vars.nor20_i_1 = lV;
                p2.bool_vars.nor21_i_1 = lV;
            }   
            lV = (sLV.p_current_settings_prt->control_dz)&MASKA_FOR_BIT(INDEX_CTR_DZ2_AMTZ);
            //not15
            if(lV == 0){
                sLV.p_p1->bool_vars.not15_o_0 = 1;
                sLV.p_p4->bool_vars.and14_i_1 = 0;//lVl |= (1<<23);//and14_i_1 :1;//23
                sLV.p_p4->bool_vars.and11_i_1 = 1;//and11
                p2.bool_vars.and26_i_5 = 0;//and26
            }else{
                sLV.p_p1->bool_vars.not15_o_0 = 0;//?
                sLV.p_p4->bool_vars.and14_i_1 = 1;
                sLV.p_p4->bool_vars.and11_i_1 = 0;
                p2.bool_vars.and26_i_5 = 1;
            }
            
            lV = (sLV.p_current_settings_prt->control_dz)&MASKA_FOR_BIT(INDEX_CTR_DZ2);
            if(lV != 0){
                lV = 1;
                p2.bool_vars.and22_i_0 = lV;
                p2.bool_vars.and24_i_0 = lV;
                p2.bool_vars.and26_i_0 = lV;
            }   
            lV = (sLV.p_current_settings_prt->control_dz)&MASKA_FOR_BIT(INDEX_CTR_DZ2_DIR);
            if(lV != 0)
                p2.bool_vars.and22_i_1 = 1;
            lV = (sLV.p_current_settings_prt->control_dz)&MASKA_FOR_BIT(INDEX_CTR_DZ2_INV);
            if(lV != 0)
                p2.bool_vars.and24_i_1 = 1;

                
            if(_CHECK_SET_BIT(p_active_functions, RANG_PO_AMTZ_DZ2) != 0){
                lV = 1;
                p2.bool_vars.nor19_i_3 = lV;
                p2.bool_vars.nor20_i_3 = lV;
                p2.bool_vars.or18__i_1 = lV;
            }   

            if(_CHECK_SET_BIT(p_active_functions, RANG_PO_DIR_DZ2) == 0){
                p2.bool_vars.not23_o_0 = 1;
                p2.bool_vars.and26_i_1 = lV;
            }
            if(_CHECK_SET_BIT(p_active_functions, RANG_PO_INV_DZ2) == 0){
                p2.bool_vars.not25_o_0 = 1;
                p2.bool_vars.and26_i_2 = lV;
            }   
//          sLV.p_p4->bool_vars.and14_i_0 = 0;  
//          if(_CHECK_SET_BIT(p_active_functions, RANG_SNKN_DZ) != 0)
//              sLV.p_p4->bool_vars.and14_i_0 = 1;
                

            //and14
            //sLV.p_p4->lVl |= (1<<22);//and14_i_0 :1;//22
            //sLV.p_p4->lVl |= (1<<23);//and14_i_1 :1;//23  
            rU = (sLV.p_p4->lVl)&((1<<22)|(1<<23)); //and14
            if(rU == ((1<<22)|(1<<23))){
                sLV.p_p1->bool_vars.and4_o_0 = 1;
                //and16
                sLV.p_p1->bool_vars.and16_i_0 = 1;
                //and17
                sLV.p_p1->bool_vars.and17_i_0 = 1;
                //or18
                sLV.p_p1->bool_vars.or18__i_0 = 1;
            }
            sLV.p_p1->bool_vars.and16_i_1 = p2.bool_vars.not23_o_0;  
            sLV.p_p1->bool_vars.and17_i_1 = p2.bool_vars.not25_o_0;
            lV = sLV.p_p1->lVl;
            lV &= ((1<<28)|(1<<29));
            if(lV == ((1<<28)|(1<<29)))//and16 
                p2.bool_vars.nor19_i_3 = 1;

            lV = sLV.p_p1->lVl;
            lV &= ((1<<20)|(1<<19));
            if(lV == ((1<<20)|(1<<19)))//and17 
                p2.bool_vars.nor20_i_3 = 1;
                
            if( (sLV.p_p1->lVl&((1<<25)|(1<<24))) != 0 ){//or18
                p2.bool_vars.nor21_i_2 = 0;
            }
            else{
                p2.bool_vars.nor21_i_2 = 1;
            }
            
            //PO Calc
            lV = p2.bool_vars.nor20_i_3;//STP_I_A_MCP_DST_LP_STAGE2_BIT
            unsigned long pick_up_I_Amcp_dstLp2 = 0;
            if(lV){
                pick_up_I_Amcp_dstLp2 = sLV.p_current_settings_prt->pickup_dz2_amtz[number_group_stp] * KOEF_POVERNENNJA_MTZ_I_UP  / 100;
                }
            else{   
                pick_up_I_Amcp_dstLp2 = sLV.p_current_settings_prt->pickup_dz2_amtz[number_group_stp];
            }
            if( (measurement[IM_IA] > pick_up_I_Amcp_dstLp2)
                || (measurement[IM_IB] > pick_up_I_Amcp_dstLp2)
                || (measurement[IM_IC] > pick_up_I_Amcp_dstLp2)
            )
                p2.bool_vars.and26_i_4 = 1;//rU = 1;
            else
                p2.bool_vars.and26_i_4 = 0;//rU = 0;
            //nor19 
            if( (p2.lVl&((1<<15)|(1<<16)|(1<<17)|(1<<18)) ) != 0 ){//
                p2.bool_vars.and22_i_4 = 0;
            }
            else{
                p2.bool_vars.and22_i_4 = 1;
            }
            //nor20 
            if( (p2.lVl&((1<<19)|(1<<20)|(1<<21)|(1<<22)) ) != 0 ){//
                p2.bool_vars.and24_i_4 = 0;
            }
            else{
                p2.bool_vars.and24_i_4 = 1;
            }
            //nor21 
            if( (p2.lVl&((1<<23)|(1<<24)|(1<<25)) ) != 0 ){//
                p2.bool_vars.and26_i_3 = 0;
            }
            else{
                p2.bool_vars.and26_i_3 = 1;
            }
            //lV = sLV.p_p1->lVl;
            lV = p2.lVl&((1<<9)|(1<<10)|(1<<11)|(1<<12)|(1<<13)|(1<<14));
            if(lV == ((1<<9)|(1<<10)|(1<<11)|(1<<12)|(1<<13)|(1<<14))){//and26 9 10 11 12 13 14
                _SET_BIT(p_active_functions, RANG_PO_AMTZ_DZ2);
                u32_bit_holder |= 1<<STP_I_AMCP_DST_LP_STAGE_BIT;
            }   
            else
                _CLEAR_BIT(p_active_functions, RANG_PO_AMTZ_DZ2);
            
            rU = p2.lVl&((1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<8));
            if(rU == ((1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<8))){//and24 4 5 6 7 8
                _SET_BIT(p_active_functions, RANG_PO_INV_DZ2);
                u32_bit_holder |= 1<<STP_INV_DST_LP_STAGE_BIT;
            }   
            else
                _CLEAR_BIT(p_active_functions, RANG_PO_INV_DZ2);
            
            rU = p2.lVl&((1<<0)|(1<<30)|(1<<1)|(1<<2)|(1<<3));
            if(rU == ((1<<0)|(1<<30)|(1<<1)|(1<<2)|(1<<3))){//and22 0 1 2 3
                _SET_BIT(p_active_functions, RANG_PO_DIR_DZ2);
                u32_bit_holder |= 1<<STP_DIR_DST_LP_STAGE_BIT;
            }
            else
                _CLEAR_BIT(p_active_functions, RANG_PO_DIR_DZ2);


        }
		else if(sLV.ch_stage_selector == DZ3_STAGE_BIT){
                ;
        }else if(sLV.ch_stage_selector == DZ4_STAGE_BIT){
                    ;
                
        }
        ;
    
    }while(sLV.ch_stage_selector > TOTAL_DZ_STAGES_BITS);
    
    do{
        //register void* pv;
        long lV,rU;
        register Dz2_stp_p3_state p3;
        
        if(bw_dstLp_dt.hdrBW.ch_p1234_modified & (1<<P3_MODIFIED_BIT))
            p3.lVl = sLV.p_p3->lVl;//Mask?
        else
            p3.lVl = 0;
        if (sLV.ch_stage_selector == DZ2_STAGE_BIT){
                        //AMtz block calc Fierst
            if( u32_bit_holder& (1<<STP_I_AMCP_DST_LP_STAGE_BIT)){
                //Eval Pr Cmd
                 p3.bool_vars.and31_i_2 = 1;
                 p3.bool_vars.and32_i_0 = 1;
                lV = sLV.p_p1->bool_vars.not10_o_0;
                rU = p3.bool_vars.or27_i_0;
                if(lV == rU)
                    lV++;//unstable state;bkpt;!
                else{
                //Select Tmr
                    //if(lV != 0){//No Acc
                        //p3.bool_vars.or27_i_0 = rU;//Must be already setup
                        p3.bool_vars.or29_i_0 = lV;
                        lV = p3.bool_vars.and32_o_0;//Loop link
                        rU = p3.bool_vars.and31_o_0;//Loop link
                        p3.bool_vars.or29_i_1 = lV;
                        p3.bool_vars.or27_i_1 = rU;
                        p3.bool_vars.not30_o_0 = !lV;
                        p3.bool_vars.not28_o_0 = !rU;
                        p3.bool_vars.and31_i_1 = !lV;
                        p3.bool_vars.and32_i_1 = !rU;
                        if( (p3.lVl&((1<<0)|(1<<1))) != 0 )//or27 customer
                            p3.bool_vars.and31_i_0 = 1; 
                        else //-if(p3.lVl&((1<<0)|(1<<1))) == 0)
                            p3.bool_vars.and31_i_0 = 0; 
                
                         if( (p3.lVl&((1<<2)|(1<<3))) != 0 )//or29 customer
                            p3.bool_vars.and32_i_2 = 1;
                        else //-if( (p3.lVl&((1<<2)|(1<<3))) == 0 )
                            p3.bool_vars.and32_i_2 = 0;
                            
                        rU = p3.lVl&((1<<5)|(1<<6)|(1<<7));
                        if(rU == ((1<<5)|(1<<6)|(1<<7))){   
                            p3.bool_vars.and31_o_0 = 1;
                            u32_bit_holder |= 1<<T_ACC_AMCP_IN_BIT;
                        }else{
                            p3.bool_vars.and31_o_0 = 1;
                
                        }                       
                        rU = p3.lVl&((1<<8)|(1<<9)|(1<<10));
                        if(rU == ((1<<8)|(1<<9)|(1<<10))){  
                            p3.bool_vars.and32_o_0 = 1;
                            u32_bit_holder |= 1<<T_AMCP_IN_BIT;
                            }
                        else{
                            p3.bool_vars.and32_o_0 = 0;
                        }
                         _TIMER_T_0(INDEX_TIMER_DZ2_AMTZ,  sLV.p_current_settings_prt->timeout_dz2_amtz[number_group_stp],
                        u32_bit_holder, T_AMCP_IN_BIT, u32_bit_holder, T_AMCP_OUT_BIT);
                        _TIMER_T_0(INDEX_TIMER_DZ2_AMTZ_PR,  sLV.p_current_settings_prt->timeout_dz2_amtz_pr[number_group_stp],
                        u32_bit_holder, T_ACC_AMCP_IN_BIT, u32_bit_holder, T_ACC_AMCP_OUT_BIT);

                    //}

                };
            }
            else{
                lV = 0;
                //Reset and31 and32
                 p3.bool_vars.and31_i_2 = lV;
                 p3.bool_vars.and32_i_0 = lV;
                //set or
                p3.bool_vars.or27_i_1 = lV;
                p3.bool_vars.or29_i_1 = lV;
                //set not
                p3.bool_vars.not28_o_0 = 1;
                p3.bool_vars.not30_o_0 = 1;
                
                //reset timers
                p3.bool_vars.and31_o_0 = lV;
                p3.bool_vars.and32_o_0 = lV;
                 _TIMER_T_0(INDEX_TIMER_DZ2_AMTZ,  sLV.p_current_settings_prt->timeout_dz2_amtz[number_group_stp],
                u32_bit_holder, T_AMCP_IN_BIT, u32_bit_holder, T_AMCP_OUT_BIT);
                 _TIMER_T_0(INDEX_TIMER_DZ2_AMTZ_PR,  sLV.p_current_settings_prt->timeout_dz2_amtz_pr[number_group_stp],
                u32_bit_holder, T_ACC_AMCP_IN_BIT, u32_bit_holder, T_ACC_AMCP_OUT_BIT);
  
                
            }
            //Сраб.
            if ( u32_bit_holder&( (1<<T_ACC_AMCP_OUT_BIT)|(1<<T_AMCP_OUT_BIT) ) )
            _SET_BIT(p_active_functions, RANG_AMTZ_DZ2);
            else
            _CLEAR_BIT(p_active_functions, RANG_AMTZ_DZ2);
            
        }else if(sLV.ch_stage_selector == DZ3_STAGE_BIT){
                ;
        }else if(sLV.ch_stage_selector == DZ4_STAGE_BIT){
                    ;
        }
        ;   
    
    }while(sLV.ch_stage_selector > TOTAL_DZ_STAGES_BITS);
    
    do{
        //register void* pv;
        register Dz2_stp_p4_state p4;
        long lV,rU;
        if(bw_dstLp_dt.hdrBW.ch_p1234_modified & (1<<P4_MODIFIED_BIT))
            p4.lVl = sLV.p_p4->lVl;//Mask?
        else
            p4.lVl = 0;
            
            
            
        if (sLV.ch_stage_selector == DZ2_STAGE_BIT){
                        //Dz block
            lV = sLV.p_p1->bool_vars.not9_o_0;
            rU = sLV.p_p3->bool_vars.or34_i_1;//p3.bool_vars.or27_i_0;
            if(lV == rU)
                lV++;//unstable state;bkpt;!
            else{
                register Dz2_stp_p3_state p3;
                p3.lVl = sLV.p_p3->lVl;
                //Dir
                if(u32_bit_holder&(1<<STP_DIR_DST_LP_STAGE_BIT)){
                    //Eval Pr Cmd
                    p4.bool_vars.and43_i_0 = 1;
                    p4.bool_vars.and42_i_2 = 1;
                    lV = sLV.p_p1->bool_vars.not9_o_0;
                    rU = p3.bool_vars.or34_i_0;
                    if(lV == rU)
                    lV++;//unstable state;bkpt;!
                    else{
                        p3.bool_vars.or36_i_0 = lV;
                        lV = p4.bool_vars.and42_o_0;//Loop link
                        rU = p4.bool_vars.and43_o_0;//Loop link
                        p3.bool_vars.or34_i_1 = lV;
                        p3.bool_vars.or36_i_1 = rU;
                        p3.bool_vars.not35_o_0 = !lV;
                        p3.bool_vars.not37_o_0 = !rU;
                        p4.bool_vars.and43_i_1 = !lV;
                        p4.bool_vars.and42_i_1 = !rU;
                        if( (p3.lVl&((1<<15)|(1<<16))) != 0 )//or34 customer
                            p4.bool_vars.and42_i_0 = 1; 
                        else 
                            p4.bool_vars.and42_i_0 = 0; 
                
                        if( (p3.lVl&((1<<18)|(1<<19))) != 0 )//or36 customer
                            p4.bool_vars.and43_i_2 = 1;
                        else 
                            p4.bool_vars.and43_i_2 = 0;
                            
                        rU = p3.lVl&((1<<0)|(1<<1)|(1<<2));
                        if(rU == ((1<<0)|(1<<1)|(1<<2))){   
                            p3.bool_vars.and31_o_0 = 1;
                            u32_bit_holder |= 1<<T_ACC_DIR_IN_BIT;
                        }else{
                            p3.bool_vars.and31_o_0 = 0;
                
                        }   
                        rU = p3.lVl&((1<<3)|(1<<4)|(1<<5));
                        if(rU == ((1<<3)|(1<<4)|(1<<5))){  
                            p3.bool_vars.and32_o_0 = 1;
                            u32_bit_holder |= 1<<T_DIR_IN_BIT;
                            }
                        else{
                            p3.bool_vars.and32_o_0 = 0;
                        }
                        _TIMER_T_0(INDEX_TIMER_DZ2_DIR_PR,  sLV.p_current_settings_prt->timeout_dz2_dir_pr[number_group_stp],
                u32_bit_holder, T_ACC_DIR_IN_BIT, u32_bit_holder, T_ACC_DIR_OUT_BIT);
                        _TIMER_T_0(INDEX_TIMER_DZ2_DIR,  sLV.p_current_settings_prt->timeout_dz2_dir[number_group_stp],
                u32_bit_holder, T_DIR_IN_BIT, u32_bit_holder, T_DIR_OUT_BIT);
                    }
                }
                else{
                    lV = 0;
                    //Reset and42 and43
                    p4.bool_vars.and43_i_0 = lV;
                    p4.bool_vars.and42_i_2 = lV;
                    //set or
                    p3.bool_vars.or36_i_1 = lV;
                    p3.bool_vars.or34_i_1 = lV;
                    //set not
                    p3.bool_vars.not35_o_0 = 1;
                    p3.bool_vars.not37_o_0 = 1;
                    //reset timers
                    p4.bool_vars.and43_o_0 = lV;
                    p4.bool_vars.and42_o_0 = lV;
                 _TIMER_T_0(INDEX_TIMER_DZ2_DIR_PR,  sLV.p_current_settings_prt->timeout_dz2_dir_pr[number_group_stp],
                u32_bit_holder, T_ACC_DIR_IN_BIT, u32_bit_holder, T_ACC_DIR_OUT_BIT);
                _TIMER_T_0(INDEX_TIMER_DZ2_DIR,  sLV.p_current_settings_prt->timeout_dz2_dir[number_group_stp],
                u32_bit_holder, T_DIR_IN_BIT, u32_bit_holder, T_DIR_OUT_BIT);
                
                }
                    ;
                //Inv
                if(u32_bit_holder&(1<<STP_INV_DST_LP_STAGE_BIT)){
                    //Eval Pr Cmd
                    p4.bool_vars.and45_i_0 = 1;
                    p4.bool_vars.and44_i_2 = 1;
                    lV = sLV.p_p1->bool_vars.not9_o_0;
                    rU = p3.bool_vars.or38_i_0;
                    if(lV == rU)
                    lV++;//unstable state;bkpt;!
                    else{
                        p3.bool_vars.or40_i_0 = lV;
                        lV = p4.bool_vars.and44_o_0;//Loop link
                        rU = p4.bool_vars.and45_o_0;//Loop link
                        p3.bool_vars.or38_i_1 = lV;
                        p3.bool_vars.or40_i_1 = rU;
                        p3.bool_vars.not39_o_0 = !lV;
                        p3.bool_vars.not41_o_0 = !rU;
                        p4.bool_vars.and45_i_1 = !lV;
                        p4.bool_vars.and44_i_1 = !rU;
                        if( (p3.lVl&((1<<21)|(1<<22))) != 0 )//or38 customer
                            p4.bool_vars.and44_i_0 = 1; 
                        else 
                            p4.bool_vars.and44_i_0 = 0; 
                
                        if( (p3.lVl&((1<<24)|(1<<25))) != 0 )//or40 customer
                            p4.bool_vars.and45_i_2 = 1;
                        else 
                            p4.bool_vars.and45_i_2 = 0;
                            
                        rU = p3.lVl&((1<<6)|(1<<7)|(1<<8));
                        if(rU == ((1<<6)|(1<<7)|(1<<8))){   
                            p3.bool_vars.and31_o_0 = 1;
                            u32_bit_holder |= 1<<T_ACC_INV_IN_BIT;
                        }else{
                            p3.bool_vars.and31_o_0 = 0;
                
                        }   
                        rU = p3.lVl&((1<<9)|(1<<10)|(1<<11));
                        if(rU == ((1<<9)|(1<<10)|(1<<11))){  
                            p3.bool_vars.and32_o_0 = 1;
                            u32_bit_holder |= 1<<T_INV_IN_BIT;
                            }
                        else{
                            p3.bool_vars.and32_o_0 = 0;
                        }
                        _TIMER_T_0(INDEX_TIMER_DZ2_INV_PR,  sLV.p_current_settings_prt->timeout_dz2_inv_pr[number_group_stp],
                u32_bit_holder, T_ACC_INV_IN_BIT, u32_bit_holder, T_ACC_INV_OUT_BIT);
                        _TIMER_T_0(INDEX_TIMER_DZ2_INV,  sLV.p_current_settings_prt->timeout_dz2_inv[number_group_stp],
                u32_bit_holder, T_INV_IN_BIT, u32_bit_holder, T_INV_OUT_BIT);
                    
                    }
                    ;
                }
                else{
                    lV = 0;
                    //Reset and44 and45
                    p4.bool_vars.and45_i_0 = lV;
                    p4.bool_vars.and44_i_2 = lV;
                    //set or
                    p3.bool_vars.or38_i_1 = lV;
                    p3.bool_vars.or40_i_1 = lV;
                    //set not
                    p3.bool_vars.not39_o_0 = 1;
                    p3.bool_vars.not41_o_0 = 1;
                    //reset timers
                    p4.bool_vars.and44_o_0 = lV;
                    p4.bool_vars.and45_o_0 = lV;
                 _TIMER_T_0(INDEX_TIMER_DZ4_DIR_PR,  sLV.p_current_settings_prt->timeout_dz4_inv_pr[number_group_stp],
                u32_bit_holder, T_ACC_INV_IN_BIT, u32_bit_holder, T_ACC_INV_OUT_BIT);
                _TIMER_T_0(INDEX_TIMER_DZ4_INV,  sLV.p_current_settings_prt->timeout_dz4_inv[number_group_stp],
                u32_bit_holder, T_INV_IN_BIT, u32_bit_holder, T_INV_OUT_BIT);
                
                }
                sLV.p_p3->lVl |= p3.lVl;
            ;
            }       
  
            
        }
        else if(sLV.ch_stage_selector == DZ3_STAGE_BIT){
                ;
        }
        else if(sLV.ch_stage_selector == DZ4_STAGE_BIT){
                    ;
                
        }
        sLV.p_p4->lVl |= p4.lVl;
        ;
    }while(sLV.ch_stage_selector > TOTAL_DZ_STAGES_BITS);
    
 bw_dstLp_dt.hdrBW.ch_p1234_modified = 0;//(1<<P2_MODIFIED_BIT)
}
//
//--------------------------------------------------------------------------------------------------------

void dz34_handler(unsigned int *p_active_functions, unsigned int number_group_stp);
//````````````````````````````````````````````````````````````````````````````````````````````````````````
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void dz34_handler(unsigned int *p_active_functions, unsigned int number_group_stp){
// ----------------  inner_outer_short_circuit It`s my name -------------------------

//First Check Menu & Dv ON or OFF

//Calc  for 4 stages
  UNUSED(p_active_functions);
  UNUSED(number_group_stp);
 
}
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````

//const unsigned long MIN_LIMIT_I1_I2_P = MIN_LIMIT_FOR_I1_AND_I2;


/*

typedef union mcp_stp_state_Unn{ 
   struct {
      unsigned int or2__i_0 :1; //0
      unsigned int or2__i_1 :1; //1
      unsigned int and3_i_0 :1; //2
      unsigned int and3_i_1 :1; //2
      unsigned int and4_i_0 :1; //3
      unsigned int and4_i_1 :1; //3
      unsigned int and5_i_0 :1; //4
      unsigned int and5_i_1 :1; //4
      unsigned int and5_i_0 :1; //5
      unsigned int and5_i_1 :1; //5
      unsigned int and4_o_0 :1; //6
      unsigned int and5_o_0 :1; //6
      unsigned int and6_o_0 :1; //7
      unsigned int or7__i_0 :1; //7
      unsigned int or7__i_1 :1; //8
      unsigned int or8__i_0 :1; //8
      unsigned int or8__i_1 :1; //9
      unsigned int not9_o_0 :1; //9
      unsigned int not10_o_0 :1;//10
      unsigned int and11_i_0 :1;//11
      unsigned int and11_i_1 :1;//12
      unsigned int or12__i_1 :1;//13
      unsigned int or12__i_0 :1;//14
      unsigned int or13__i_1 :1;//15
      unsigned int or13__i_0 :1;//16
      unsigned int and14_i_0 :1;//17
      unsigned int and14_i_1 :1;//18
      unsigned int not15_o_0 :1;//19
      unsigned int and16_i_0 :1;//20
      unsigned int and16_i_1 :1;//21
      unsigned int and17_i_0 :1;//22
      unsigned int and17_i_1 :1;//23
      unsigned int or18__i_1 :1;//24
      unsigned int or18__i_0 :1;//25
      unsigned int b26 :1;//26
      unsigned int b27 :1;//27
      unsigned int b28 :1;//28
      unsigned int b29 :1;//29
      unsigned int b30 :1;//30
      unsigned int b31 :1;//31    
    } bool_vars;
    long lVl;
} Dz2_stp_p1_state; //ex- extended
typedef union mcp_stp_state_Unn{ 
   struct {
      unsigned int and22_i_0 :1; //0
      unsigned int and22_i_1 :1; //1
      unsigned int and22_i_2 :1; //2
      unsigned int and22_i_3 :1; //2
      unsigned int and22_i_4 :1; //3
      unsigned int and24_i_0 :1; //4
      unsigned int and24_i_1 :1; //5
      unsigned int and24_i_2 :1; //6
      unsigned int and24_i_3 :1; //7
      unsigned int and24_i_4 :1; //8
      unsigned int and26_i_0 :1; //9
      unsigned int and26_i_1 :1;//10
      unsigned int and26_i_2 :1;//11
      unsigned int and26_i_3 :1;//12
      unsigned int and26_i_4 :1;//13
      unsigned int and26_i_5 :1;//14
      unsigned int nor19_i_0 :1;//15
      unsigned int nor19_i_1 :1;//16
      unsigned int nor19_i_2 :1;//17
      unsigned int nor19_i_3 :1;//18
      unsigned int nor20_i_0 :1;//19
      unsigned int nor20_i_1 :1;//20
      unsigned int nor20_i_2 :1;//21
      unsigned int nor20_i_3 :1;//22
      unsigned int nor21_i_0 :1;//23
      unsigned int nor21_i_1 :1;//24
      unsigned int nor21_i_2 :1;//25
      unsigned int not23_o_0 :1;//26
      unsigned int not25_o_0 :1;//27
      unsigned int b28 :1;//28
      unsigned int b29 :1;//29
      unsigned int b30 :1;//30
      unsigned int b31 :1;//31    
    } bool_vars;
    long lVl;
} Dz2_stp_p2_state; //ex- extended
typedef union mcp_stp_state_Unn{ 
   struct {
      unsigned int or27_i_0 :1; //0
      unsigned int or27_i_1 :1; //1
      unsigned int not28_o_0:1; //2
      unsigned int or29_i_0 :1; //2
      unsigned int or29_i_1 :1; //3
      unsigned int not30_o_0:1; //4
      unsigned int and31_i_0:1; //5
      unsigned int and31_i_1:1; //6
      unsigned int and31_i_3:1; //7
      unsigned int and32_i_0:1; //8
      unsigned int and32_i_1:1; //9
      unsigned int and32_i_3:1;//10
      unsigned int and31_o_0 :1;//11
      unsigned int and32_o_0 :1;//12
      unsigned int or33_i_0 :1;//13
      unsigned int or33_i_1 :1;//14
      unsigned int or34_i_0  :1;//15
      unsigned int or34_i_1  :1;//16
      unsigned int not35_o_0 :1;//17
      unsigned int or36_i_0  :1;//18
      unsigned int or36_i_1  :1;//19
      unsigned int not37_o_0 :1;//20
      unsigned int or38_i_0  :1;//21
      unsigned int or38_i_1  :1;//22
      unsigned int not39_o_0 :1;//23
      unsigned int or40_i_0  :1;//24
      unsigned int or40_i_1  :1;//25
      unsigned int not41_o_0 :1;//26
      unsigned int b27 :1;//27
      unsigned int b28 :1;//28
      unsigned int b29 :1;//29
      unsigned int b30 :1;//30
      unsigned int b31 :1;//31    
    } bool_vars;
    long lVl;
} Dz2_stp_p3_state; //ex- extended
typedef union mcp_stp_state_Unn{ 
   struct {
      unsigned int and42_i_0 :1; //0
      unsigned int and42_i_1 :1; //1
      unsigned int and42_i_3 :1; //2
      unsigned int and43_i_0 :1; //3
      unsigned int and43_i_1 :1; //4
      unsigned int and43_i_3 :1; //5
      unsigned int and44_i_0 :1; //6
      unsigned int and44_i_1 :1; //7
      unsigned int and44_i_3 :1; //8
      unsigned int and45_i_0 :1; //9
      unsigned int and45_i_1 :1;//10
      unsigned int and45_i_3 :1;//11
      unsigned int and42_o_0 :1;//12
      unsigned int and43_o_0 :1;//13
      unsigned int and44_o_0 :1;//14
      unsigned int and45_o_0 :1;//15
      unsigned int or46_i_0  :1;//16
      unsigned int or46_i_1  :1;//17
      unsigned int or46_i_2  :1;//18
      unsigned int or46_i_3  :1;//19
      unsigned int b20 :1;//20
      unsigned int b21 :1;//21
      unsigned int b22 :1;//22
      unsigned int b23 :1;//23
      unsigned int b24 :1;//24
      unsigned int b25 :1;//25
      unsigned int b26 :1;//26
      unsigned int b27 :1;//27
      unsigned int b28 :1;//28
      unsigned int b29 :1;//29
      unsigned int b30 :1;//30
      unsigned int b31 :1;//31    
    } bool_vars;
    long lVl;
} Dz2_stp_p4_state; //ex- extended

//First Check Menu & Dv ON or OFF
register union { 
   struct {
      unsigned int SW:1;//0
      unsigned int SW:1;//1
      unsigned int SW:1;//2
      unsigned int SW:1;//3
      unsigned int SW:1;//4
      unsigned int SW:1;//5
      unsigned int SW:1;//6
      unsigned int SW:1;//7
      unsigned int SW:1;//8
      unsigned int SW:1;//9
      unsigned int SW:1;//10
      unsigned int SW:1;//11
      unsigned int SW:1;//12
      unsigned int SW:1;//13
      unsigned int SW:1;//14
      unsigned int SW:1;//15
      unsigned int SW:1;//17
      unsigned int SW:1;//18
      unsigned int SW:1;//19
      unsigned int SW:1;//21
      unsigned int SW:1;//22
      unsigned int SW:1;//23
      unsigned int SW:1;//24
      unsigned int SW:1;//25
      unsigned int SW:1;//26
      unsigned int SW1:1;//27
      unsigned int SW:1;//28
      unsigned int SW:1;//29
      //unsigned int not10_1 :1;//30
      //unsigned int not10_1 :1;//31
      
   } bool_vars;
  long lVl;
}wrp_dz2;

register union { 
   struct {
      unsigned int S4_1:1;//0
      unsigned int S4_2:1;//1
      unsigned int S4_3:1;//2
      unsigned int S5_1:1;//3
      unsigned int S5_2:1;//4
      unsigned int S5_3:1;//5
      unsigned int S4__:1;//6
      unsigned int S5__:1;//7
      unsigned int S_1:1;//8
      unsigned int S_2:1;//9
      unsigned int S2_1:1;//10
      unsigned int S7_1:1;//11
      unsigned int S_O1:1;//11-  O1 - means out 1
   } bool_vars;
  long lVl;
}wrp_sncn;
wrp_sncn.lVl = 0;

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
