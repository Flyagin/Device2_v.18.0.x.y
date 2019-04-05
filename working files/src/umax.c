enum UMAX1_BIT_POS { 

UMAX1_DV_BLOCK_CMD_BIT  = 1,  
UMAX1_DV_BLOCK_INVERSE_CMD_BIT  ,  
UMAX1_MENU_PSTATE_BIT,
UMAX1_PICKUP_STATE_BIT,
UMAX1_TMR_STATE_BIT,
TOTAL_UMAX1_BITS
//
};



char  = 0;
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void Umax1_handler(unsigned int *p_active_functions, unsigned int number_group_stp){
// ----------------  inner_outer_short_circuit It`s my name	-------------------------
register long lV;
register unsigned long u32_bit_holder = 0;  
register void* pv;
struct{
long ll;
char chPO_umax;

}sLV; 
long lPickUP; 
pv = (void*)&current_settings_prt;    
//__SETTINGS *

  lV = _CHECK_SET_BIT(p_active_functions, RANG_BLOCK_UMAX1);
  register long lAnd = 0;
  if(lV == 0)
    lAnd |= 1;
   lV = ((__SETTINGS *)pv)->control_Umax & (CTR_UMAX1) ;
  if(lV != 0)
  lAnd |= 2;
  if(lAnd == 3){
	//Calc PickUP
	lV = ((__SETTINGS *)pv)->setpoint_Umax1[number_group_stp];
	if(ch_po_umax1 != 0){
		lV *= (((__SETTINGS *)pv)->setpoint_kp_Umax[number_group_stp]) / 100 ;
	}
	lPickUP = lV; 
  sLV.chPO_umax = ch_po_umax1;
	lV = (((__SETTINGS *)pv)->control_transformator & (1<<INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE));
	if(lV !=0 ){//Phase
		//check And
		if(((__SETTINGS *)pv)->control_Umax & CTR_PO_UMAX1_OR_AND){
			if(measurement[IM_UA] >= lPickUP
			&& measurement[IM_UB] >= lPickUP
			&& measurement[IM_UC] >= lPickUP)
			ch_po_umax1 = sLV.chPO_umax = 1;
		}else{//OR
			if( (measurement[IM_UA] >= lPickUP)
			|| (measurement[IM_UB] >= lPickUP)
			|| (measurement[IM_UC] >= lPickUP) )
			h_po_umax1 = sLV.chPO_umax = 1;
		
		}
		;
	
	}else{//Lin
				//check And
		if((__SETTINGS *)pv)->control_Umax & CTR_PO_UMAX1_OR_AND){
			if((measurement[IM_UAB] >= lPickUP)
			(measurement[IM_UBC] >= lPickUP)
			(measurement[IM_UCA] >= lPickUP))
			h_po_umax1 = sLV.chPO_umax = 1;
		}else{//OR
			if((measurement[IM_UAB] >= lPickUP)
			(measurement[IM_UBC] >= lPickUP)
			(measurement[IM_UCA] >= lPickUP) )
			h_po_umax1 = sLV.chPO_umax = 1;
		}
		;
	}
//    lV = ((__SETTINGS *)pv)->control_Umax & (CTR_PO_UMAX1_OR_AND);
//	if(lV){
//		;
//	}else{
//		;
//	}
	if(sLV.chPO_umax != 0)
	_SET_BIT(p_active_functions, RANG_PO_UMAX1);
	else
	_CLEAR_BIT(p_active_functions, RANG_PO_UMAX1);
	
   }
   else
      _CLEAR_BIT(p_active_functions, RANG_PO_UMAX1);
   
   
	
	
	
}
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````
//=====================================================================================================
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//                  
//....................................................................................................
//=====================================================================================================
void Umax2_handler(unsigned int *p_active_functions, unsigned int number_group_stp){
// ----------------  inner_outer_short_circuit It`s my name	-------------------------
register long lV;
register unsigned long u32_bit_holder = 0;  
register void* pv;
struct{
long lSP_a,lSP_2g,lSP_5g, lgdI;
long lgdI_hysteresis;
long conter_and;
__SETTINGS *p_current_settings_prt;
}sLV; 

pv = (void*)&current_settings_prt; 	
	
}
//
//--------------------------------------------------------------------------------------------------------
//````````````````````````````````````````````````````````````````````````````````````````````````````````
