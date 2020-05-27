#include "header.h"

/*****************************************************/
//ĳ��������� ���
/*****************************************************/
//inline void diagnostyca_adc_execution(void)
//{
//  if (gnd_adc1 >0x51) _SET_BIT(set_diagnostyka, ERROR_GND_ADC1_TEST_BIT);
//  else _SET_BIT(clear_diagnostyka, ERROR_GND_ADC1_TEST_BIT);
//
//  if (gnd_adc2 >0x51) _SET_BIT(set_diagnostyka, ERROR_GND_ADC2_TEST_BIT);
//  else _SET_BIT(clear_diagnostyka, ERROR_GND_ADC2_TEST_BIT);
//
//  if ((vref_adc1 <0x709) || (vref_adc1 > 0x8f5)) _SET_BIT(set_diagnostyka, ERROR_VREF_ADC1_TEST_BIT);
//  else _SET_BIT(clear_diagnostyka,ERROR_VREF_ADC1_TEST_BIT);
//
//  if ((vref_adc2 <0x709) || (vref_adc2 > 0x8f5)) _SET_BIT(set_diagnostyka, ERROR_VREF_ADC2_TEST_BIT);
//  else _SET_BIT(clear_diagnostyka,ERROR_VREF_ADC2_TEST_BIT);
//
//  if ((vdd_adc1 <0x8F9) || (vdd_adc1 > 0xE13)) _SET_BIT(set_diagnostyka, ERROR_VDD_ADC1_TEST_BIT);
//  else _SET_BIT(clear_diagnostyka, ERROR_VDD_ADC1_TEST_BIT);
//
//  if ((vdd_adc2 <0x8F9) || (vdd_adc2 > 0xE13)) _SET_BIT(set_diagnostyka, ERROR_VDD_ADC2_TEST_BIT);
//  else _SET_BIT(clear_diagnostyka, ERROR_VDD_ADC2_TEST_BIT);
//}
/*****************************************************/

/*****************************************************/
//����� ���������� �����
/*****************************************************/
inline unsigned int norma_value(unsigned long long y)
{
  unsigned long long temp=y;
  unsigned int rezultat =0;
  if (temp == 0) return 0;

  while(temp !=0)
  {
    temp = temp>>1;
    rezultat++;
  }
  return rezultat-1;
}
/*****************************************************/

/*****************************************************/
//����� ���������� ����� ���� int
/*****************************************************/
inline unsigned int get_order(int value)
{
  unsigned int i = 0;

  if (value == 0) return 1;  
  if (value < 0) value =-value;

  while ((value >> (++i)) != 0); 

  return i;    
}
/*****************************************************/

/*****************************************************/
//���������� ������ ����������� ������� ����������� ������  � �������������� ���������� �����
/*****************************************************/
unsigned int sqrt_64(unsigned long long y)
{
   unsigned int b;
   unsigned int a;
   unsigned int c;
   unsigned int norma_rez;
   unsigned long long temp;
   
   norma_rez = norma_value(y)>>1;
   
   a = (1<<norma_rez) - 1;
   b = (1<<(norma_rez+1));
 
   do 
    {
     c = (a + b)>>1;
     temp = (unsigned long long)c*(unsigned long long)c; 
     if (temp != y)
       {
        if ( temp > y) b= c; else a= c;
       } 
     else return c;
    }
   while ((b-a)>1);

   c = (a + b)>>1;

   return c ;
}
/*****************************************************/

/*****************************************************/
//���������� ������ ����������� ������� ����������� ������  � �������������� ���������� �����
/*****************************************************/
inline unsigned int sqrt_32(unsigned int y)
{
   unsigned int b;
   unsigned int a;
   unsigned int c;
   unsigned int norma_rez;
   unsigned int temp;
   
   norma_rez = norma_value(y)>>1;
   
   a = (1<<norma_rez) - 1;
   b = (1<<(norma_rez+1));
 
   do 
    {
     c = (a + b)>>1;
     temp = c*c; 
     if (temp != y)
       {
        if ( temp > y) b= c; else a= c;
       } 
     else return c;
    }
   while ((b-a)>1);

   c = (a + b)>>1;

   return c ;
}
/*****************************************************/

/*****************************************************/
//���������� ������ ��������� �����������
/*****************************************************/
inline void velychyna_zvorotnoi_poslidovnosti(int ortogonal_local_calc[], const __index_I_U i_u)
{
  enum _n_phase {_A = 0, _B, _C, _A_B_C};
  const enum _full_ort_index a_b_c[_NUMBER_FOR_I_U][_A_B_C] = 
  {
    {FULL_ORT_Ia, FULL_ORT_Ib, FULL_ORT_Ic},
    {FULL_ORT_Ua, FULL_ORT_Ub, FULL_ORT_Uc}
  };
  const uint32_t const_val[_NUMBER_FOR_I_U][4] = 
  {
    {IM_I2, IM_I1, MNOGNYK_I_DIJUCHE, (VAGA_DILENNJA_I_DIJUCHE + 4)},
    {IM_U2, IM_U1, MNOGNYK_U_DIJUCHE, (VAGA_DILENNJA_U_DIJUCHE + 4)}
  };
    
  int ortogonal_tmp[2];
  int mul_x1, mul_x2, mul_x3, mul_x4, mul_y1, mul_y2, mul_y3, mul_y4;
  
  mul_x1 = (      ortogonal_local_calc[2*a_b_c[i_u][_B]    ]>>1 );
  mul_y1 = (0x376*ortogonal_local_calc[2*a_b_c[i_u][_B]    ]>>10);

  mul_x2 = (0x376*ortogonal_local_calc[2*a_b_c[i_u][_B] + 1]>>10);
  mul_y2 = (      ortogonal_local_calc[2*a_b_c[i_u][_B] + 1]>>1 );

  mul_x3 = (      ortogonal_local_calc[2*a_b_c[i_u][_C]    ]>>1 );
  mul_y3 = (0x376*ortogonal_local_calc[2*a_b_c[i_u][_C]    ]>>10);

  mul_x4 = (0x376*ortogonal_local_calc[2*a_b_c[i_u][_C] + 1]>>10);
  mul_y4 = (      ortogonal_local_calc[2*a_b_c[i_u][_C] + 1]>>1 );

  //�������� �����������
  ortogonal_tmp[0] = ((int)(0x155*(ortogonal_local_calc[2*a_b_c[i_u][_A]    ] - mul_x1  + mul_x2  - mul_x3 - mul_x4)))>>10;
  ortogonal_tmp[1] = ((int)(0x155*(ortogonal_local_calc[2*a_b_c[i_u][_A] + 1] - mul_y1  - mul_y2  + mul_y3 - mul_y4)))>>10;
  measurement[const_val[i_u][0]] = (unsigned int)((unsigned long long)( const_val[i_u][2]*(sqrt_32((unsigned int)ortogonal_tmp[0]*ortogonal_tmp[0] + (unsigned int)ortogonal_tmp[1]*ortogonal_tmp[1])) ) >> const_val[i_u][3]);

  //����� �����������
  ortogonal_tmp[0] = ((int)(0x155*(ortogonal_local_calc[2*a_b_c[i_u][_A]    ] - mul_x1  - mul_x2  - mul_x3 + mul_x4)))>>10;
  ortogonal_tmp[1] = ((int)(0x155*(ortogonal_local_calc[2*a_b_c[i_u][_A] + 1] + mul_y1  - mul_y2  - mul_y3 - mul_y4)))>>10;
  measurement[const_val[i_u][1]] = (unsigned int)((unsigned long long)( const_val[i_u][2]*(sqrt_32((unsigned int)ortogonal_tmp[0]*ortogonal_tmp[0] + (unsigned int)ortogonal_tmp[1]*ortogonal_tmp[1])) ) >> const_val[i_u][3]);
}
/*****************************************************/
#include "dz.c"
/*****************************************************
ort_i  - �������� �� ����������� 3I0
ort_u  - �������� �� ����������� 3U0
*****************************************************/
inline void detector_kuta_nzz(int ortogonal_local_calc[]) 
{
  int cos_fi, sin_fi;

#define SIN_3I0   ortogonal_local_calc[2*FULL_ORT_3I0    ]
#define COS_3I0   ortogonal_local_calc[2*FULL_ORT_3I0 + 1]
#define SIN_3U0   ortogonal_local_calc[2*FULL_ORT_3U0    ]
#define COS_3U0   ortogonal_local_calc[2*FULL_ORT_3U0 + 1]

  /***
  �������������� ���������� ������� ������ 
  ***/
//  cos_fi = COS_3I0*COS_3U0 + SIN_3I0*SIN_3U0;
//  sin_fi = -(SIN_3I0*COS_3U0 - COS_3I0*SIN_3U0);//� ������: "���������, ��� ����", ����� �� � �� ���� ��������
  cos_fi = COS_3U0*COS_3I0 + SIN_3U0*SIN_3I0;
  sin_fi = -(SIN_3U0*COS_3I0 - COS_3U0*SIN_3I0);//� ������: "���������, ��� ����", ����� �� � �� ���� ��������
  /***/

#undef SIN_3I0
#undef COS_3I0
#undef SIN_3U0
#undef COS_3U0

  /*
  � ��������� ����������� ����������� � ������� ��������� ����� ������� (calc_measurement())
  �������, �� ����������� ������� ������� 3I0 � 3U0 � 15-��� ���� + ����.
  ��� COS � SIN ������ ��� ������� ���� ���� 31-���� �����
  �������� ���������� ������� ������� ������ 7-������ ������� + ����
  ��� ��� �� �������� ������������ ����� �����������, �� ���������� ������ �������
  COS � SIN ���� = 31 - (7 + 1) = 23
  7 - �� ���������� ��������� ������� ������� �������
  1 - �� ���������� �� �� ���������⳺�� ������� (ab+cd)
  */
  unsigned int order_cos, order_sin, max_order, shift = 0;
  order_cos = get_order(cos_fi);
  order_sin = get_order(sin_fi);
  if (order_cos > order_sin) max_order = order_cos; else max_order = order_sin;
  if (max_order > 23) shift = max_order - 23;
  
  /*
  ��� ���� � ����� ���� ���������� ��������� - �� ��� � ������ �� ����� ����������� ����,
  ��� ���� � �������� ������� ���������� ���������.
  ��� ���� ��� � ������������?..
  */

  /***
  ���������� ���������
  ***/
  int sin_fi1_minus_fi2;
  if ((cos_fi >= 0) && (sin_fi >= 0))
  {
    //1-�� ��������
    cos_fi = cos_fi >> shift;
    sin_fi = sin_fi >> shift;

#define COS_SECTOR sector_1[0]    
#define SIN_SECTOR sector_1[1]    

    sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
    sector_i_minus_u_1 = (sin_fi1_minus_fi2 < 0) ?  0 : 1;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    

#define COS_SECTOR sector_2[0]    
#define SIN_SECTOR sector_2[1]    

    sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
    sector_i_minus_u_2 = (sin_fi1_minus_fi2 < 0) ?  0 : 1;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
  }
  else if ((cos_fi < 0) && (sin_fi >= 0))
  {
     //2-�� ��������
    cos_fi = cos_fi >> shift;
    sin_fi = sin_fi >> shift;

#define COS_SECTOR sector_1[2]    
#define SIN_SECTOR sector_1[3]    

    sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
    sector_i_minus_u_1 = (sin_fi1_minus_fi2 > 0) ?  0 : 2;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    

#define COS_SECTOR sector_2[2]    
#define SIN_SECTOR sector_2[3]    

    sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
    sector_i_minus_u_2 = (sin_fi1_minus_fi2 > 0) ?  0 : 2;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
  }
  else if ((cos_fi < 0) && (sin_fi < 0))
  {
    //3-�� ��������
    cos_fi = cos_fi >> shift;
    sin_fi = sin_fi >> shift;

#define COS_SECTOR sector_1[4]    
#define SIN_SECTOR sector_1[5]    

    sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
    sector_i_minus_u_1 = (sin_fi1_minus_fi2 < 0) ?  0 : 3;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    

#define COS_SECTOR sector_2[4]    
#define SIN_SECTOR sector_2[5]    

    sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
    sector_i_minus_u_2 = (sin_fi1_minus_fi2 < 0) ?  0 : 3;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
  }
  else
  {
    //4-�� ��������
    cos_fi = cos_fi >> shift;
    sin_fi = sin_fi >> shift;

#define COS_SECTOR sector_1[6]    
#define SIN_SECTOR sector_1[7]    

    sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
    sector_i_minus_u_1 = (sin_fi1_minus_fi2 > 0) ?  0 : 4;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    

#define COS_SECTOR sector_2[6]    
#define SIN_SECTOR sector_2[7]    

    sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
    sector_i_minus_u_2 = (sin_fi1_minus_fi2 > 0) ?  0 : 4;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
  }
  /***/
}
/*****************************************************/

/*****************************************************/
//������������ ��� � ����������� �������
/*****************************************************/
inline void directional_mtz(int ortogonal_local_calc[], unsigned int number_group_stp) 
{
  for (unsigned int i = 0; i < 3; i++)
  {
    unsigned int index_I, index_U;
    switch (i)
    {
    case 0:
      {
        index_I = IM_IA;
        index_U = IM_UBC;

        break;
      }
    case 1:
      {
        index_I = IM_IB;
        index_U = IM_UCA;

        break;
      }
    case 2:
      {
        index_I = IM_IC;
        index_U = IM_UAB;

        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(89);
      }
    }

    unsigned int porig_Uxy;
    if (Uxy_bilshe_porogu[i] == 0) porig_Uxy = PORIG_CHUTLYVOSTI_VOLTAGE_ANGLE*KOEF_POVERNENNJA_SECTOR_BLK/100;
    else porig_Uxy = PORIG_CHUTLYVOSTI_VOLTAGE_ANGLE;
    Uxy_bilshe_porogu[i] = (measurement[index_U] >= porig_Uxy);
      
    unsigned int porig_Ix;
    if (Ix_bilshe_porogu[i] == 0) porig_Ix = PORIG_CHUTLYVOSTI_CURRENT*KOEF_POVERNENNJA_SECTOR_BLK/100;
    else porig_Ix = PORIG_CHUTLYVOSTI_CURRENT;
    Ix_bilshe_porogu[i]  = (measurement[index_I] >= porig_Ix );
  }
      
  for (unsigned int mtz = 0; mtz < 4; mtz++)
  {
    int a_cos_fi, a_sin_fi;
    switch (mtz)
    {
    case 0:
      {
        a_cos_fi = current_settings_prt.setpoint_mtz_1_angle_cos[number_group_stp];
        a_sin_fi = current_settings_prt.setpoint_mtz_1_angle_sin[number_group_stp];
        
        break;
      }
    case 1:
      {
        a_cos_fi = current_settings_prt.setpoint_mtz_2_angle_cos[number_group_stp];
        a_sin_fi = current_settings_prt.setpoint_mtz_2_angle_sin[number_group_stp];
        
        break;
      }
    case 2:
      {
        a_cos_fi = current_settings_prt.setpoint_mtz_3_angle_cos[number_group_stp];
        a_sin_fi = current_settings_prt.setpoint_mtz_3_angle_sin[number_group_stp];
        
        break;
      }
    case 3:
      {
        a_cos_fi = current_settings_prt.setpoint_mtz_4_angle_cos[number_group_stp];
        a_sin_fi = current_settings_prt.setpoint_mtz_4_angle_sin[number_group_stp];
        
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(54);
      }
    }
    a_sin_fi = -a_sin_fi; //� ������: "���������, ��� ����", ����� �� � �� ���� ��������

    //������ ��������� �� ������������ ���
    /*
    �� ����������� �������� ��� ���������� ����� ������� ���� ����������� � � ������ (15 �� + ����) = 16-�������� �����
    */
    int amp_cos_U_fi;
    int amp_sin_U_fi;
  
    for (unsigned int i = 0; i < 3; i++)
    {
      if (
          (Uxy_bilshe_porogu[i] != 0) &&
          (Ix_bilshe_porogu[i]  != 0)
         )
      {
        unsigned int index_I_ort, index_U_ort;
        switch (i)
        {
        case 0:
          {
            index_I_ort = FULL_ORT_Ia;
            index_U_ort = FULL_ORT_Ubc;

            break;
          }
        case 1:
          {
            index_I_ort = FULL_ORT_Ib;
            index_U_ort = FULL_ORT_Uca;

            break;
          }
        case 2:
          {
            index_I_ort = FULL_ORT_Ic;
            index_U_ort = FULL_ORT_Uab;

            break;
          }
        default:
          {
            //���������� ����� ����� �� ���� � ����
            total_error_sw_fixed(60);
          }
        }

#define SIN_I   ortogonal_local_calc[2*index_I_ort    ]
#define COS_I   ortogonal_local_calc[2*index_I_ort + 1]
#define SIN_U   ortogonal_local_calc[2*index_U_ort    ]
#define COS_U   ortogonal_local_calc[2*index_U_ort + 1]

        amp_cos_U_fi = (COS_U*a_cos_fi - SIN_U*a_sin_fi) >> AMPLITUDA_FI_VAGA; //� ����������� �� ��������� ���������� �������������
        amp_sin_U_fi = (SIN_U*a_cos_fi + COS_U*a_sin_fi) >> AMPLITUDA_FI_VAGA; //� ����������� �� ��������� ���������� �������������

        //���������� COS � SIN ���� ������ �� (U[i]+fi) � I[i]
        int cos_fi, sin_fi;
        /*
        � ��������� ����������� ����������� � ������� ��������� ����� ������� (calc_measurement())
        �������, �� ����������� �������� ������������� ��� ������ ���� ���� 0x6E51, ��� ����� ������� 
        0x120FC, �� ������� �� �� ���� 0x7C87B7BC  - 31 ���� ����� (���� ���� ���)
        ����� �� ���������� � ��� int.
        */
        cos_fi = amp_cos_U_fi*COS_I + amp_sin_U_fi*SIN_I;
        sin_fi = -(amp_sin_U_fi*COS_I - amp_cos_U_fi*SIN_I);//� ������: "���������, ��� ����", ����� �� � �� ���� ��������

#undef SIN_I
#undef COS_I
#undef SIN_U
#undef COS_U

        /*
        � ���� ��������� ����������� ��������, �� COS � SIN ������ ������ � ������� ���� ���� 31-���� �����
        ������� ���������� ������� ������� ������ 7-������ ������� + ����
        ��� ��� �� �������� ������������ ����� �����������, �� ���������� ������ �������
        COS � SIN ���� = 31 - (7 + 1) = 23
        7 - �� ���������� ��������� ������� ������� �������
        1 - �� ���������� �� �� ���������⳺�� ������� (ab+cd)
        */
        unsigned int order_cos, order_sin, max_order, shift = 0;
        order_cos = get_order(cos_fi);
        order_sin = get_order(sin_fi);
        if (order_cos > order_sin) max_order = order_cos; else max_order = order_sin;
        if (max_order > 23) shift = max_order - 23;
  
        /*
        ��� ���� � ����� ���� ���������� ��������� - �� ��� � ������ �� ����� ����������� ����,
        ��� ���� � �������� ������� ���������� ���������.
        ��� ���� ��� � ������������?..
        */

        //���������� �������
        int sin_fi1_minus_fi2;
        int *sector;
        if ((sin_fi >= 0) && (cos_fi >= 0))
        {
          //1-�� ��������
          cos_fi = cos_fi >> shift;
          sin_fi = sin_fi >> shift;
          
          if (sector_directional_mtz[mtz][i] != 1)
            sector = sector_1_mtz_tznp;
          else
            sector = sector_2_mtz_tznp;
          
#define COS_SECTOR sector[0]    
#define SIN_SECTOR sector[1]    

          sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
          sector_directional_mtz[mtz][i] = (sin_fi1_minus_fi2 <= 0) ?  1 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR   
        }
        else if ((sin_fi >= 0) && (cos_fi < 0))
        {
          //2-�� ��������
          cos_fi = cos_fi >> shift;
          sin_fi = sin_fi >> shift;

          if (sector_directional_mtz[mtz][i] != 2)
            sector = sector_1_mtz_tznp;
          else
            sector = sector_2_mtz_tznp;

#define COS_SECTOR sector[2]    
#define SIN_SECTOR sector[3]    

          sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
          sector_directional_mtz[mtz][i] = (sin_fi1_minus_fi2 >= 0) ?  2 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
        }
        else if ((sin_fi < 0) && (cos_fi < 0))
        {
          //3-�� ��������
          cos_fi = cos_fi >> shift;
          sin_fi = sin_fi >> shift;

          if (sector_directional_mtz[mtz][i] != 2)
            sector = sector_1_mtz_tznp;
          else
            sector = sector_2_mtz_tznp;

#define COS_SECTOR sector[4]    
#define SIN_SECTOR sector[5]    

          sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
          sector_directional_mtz[mtz][i] = (sin_fi1_minus_fi2 <= 0) ?  2 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
        }
        else
        {
          //4-�� ��������
          cos_fi = cos_fi >> shift;
          sin_fi = sin_fi >> shift;

          if (sector_directional_mtz[mtz][i] != 1)
            sector = sector_1_mtz_tznp;
          else
            sector = sector_2_mtz_tznp;

#define COS_SECTOR sector[6]    
#define SIN_SECTOR sector[7]    

          sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
          sector_directional_mtz[mtz][i] = (sin_fi1_minus_fi2 >= 0) ?  1 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
        }
      }
      else
      {
        sector_directional_mtz[mtz][i] = 0;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//������������ ���� � ����������� �������
/*****************************************************/
inline void directional_tznp(int ortogonal_local_calc[], unsigned int number_group_stp) 
{
  for (unsigned int tznp = 0; tznp < 3; tznp++)
  {
    int a_cos_fi, a_sin_fi;
    switch (tznp)
    {
    case 0:
      {
        a_cos_fi = current_settings_prt.setpoint_tznp_1_angle_cos[number_group_stp];
        a_sin_fi = current_settings_prt.setpoint_tznp_1_angle_sin[number_group_stp];
        
        break;
      }
    case 1:
      {
        a_cos_fi = current_settings_prt.setpoint_tznp_2_angle_cos[number_group_stp];
        a_sin_fi = current_settings_prt.setpoint_tznp_2_angle_sin[number_group_stp];
        
        break;
      }
    case 2:
      {
        a_cos_fi = current_settings_prt.setpoint_tznp_3_angle_cos[number_group_stp];
        a_sin_fi = current_settings_prt.setpoint_tznp_3_angle_sin[number_group_stp];
        
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(81);
      }
    }
    a_sin_fi = -a_sin_fi; //� ������: "���������, ��� ����", ����� �� � �� ���� ��������

    //������ ��������� �� ������������ ���
    /*
    �� ����������� �������� ��� ���������� ����� ������� ���� ����������� � � ������ (15 �� + ����) = 16-�������� �����
    */
    unsigned int porig_U;
    if (TZNP_3U0_bilshe_porogu == 0) porig_U = PORIG_CHUTLYVOSTI_VOLTAGE_ANGLE*KOEF_POVERNENNJA_SECTOR_BLK/100;
    else porig_U = PORIG_CHUTLYVOSTI_VOLTAGE_ANGLE;
    unsigned int U_bilshe_porogu_tmp = TZNP_3U0_bilshe_porogu = (measurement[IM_3U0] >= porig_U);
      
    unsigned int porig_I;
    if (TZNP_3I0_r_bilshe_porogu == 0) porig_I = PORIG_CHUTLYVOSTI_CURRENT*KOEF_POVERNENNJA_SECTOR_BLK/100;
    else porig_I = PORIG_CHUTLYVOSTI_CURRENT;
    unsigned int I_bilshe_porogu_tmp = TZNP_3I0_r_bilshe_porogu  = (measurement[IM_3I0_r] >= porig_I);

    if (
        (U_bilshe_porogu_tmp != 0) &&
        (I_bilshe_porogu_tmp != 0)
       )
    {
      /*
      ����� � �� ������� ����� ��������� �� 180 �������.
      cos(phi + Pi) = -cos(phi)
      sin(phi + Pi) = -sin(phi)
      ���� COS_U ������� ����
      */
#define SIN_I           ( ortogonal_local_calc[2*FULL_ORT_3I0_r    ])
#define COS_I           ( ortogonal_local_calc[2*FULL_ORT_3I0_r + 1])
#define SIN_U_plus_Pi   (-ortogonal_local_calc[2*FULL_ORT_3U0      ])
#define COS_U_plus_Pi   (-ortogonal_local_calc[2*FULL_ORT_3U0   + 1])

      int cos_I_fi = (COS_I*a_cos_fi - SIN_I*a_sin_fi) >> AMPLITUDA_FI_VAGA; //� ����������� �� ��������� ���������� �������������
      int sin_I_fi = (SIN_I*a_cos_fi + COS_I*a_sin_fi) >> AMPLITUDA_FI_VAGA; //� ����������� �� ��������� ���������� �������������

      //���������� COS � SIN ���� ������ �� (3I0_r+fi) � (3U0 + 180�)
      int cos_fi, sin_fi;
      /*
      � ��������� ����������� ����������� � ������� ��������� ����� ������� (calc_measurement())
      �������, �� ����������� �������� ������������� ��� ������ ���� ���� 0x6E51, ��� ����� ������� (3U0)
      0x907E, �� ������� �� �� ���� 0x3E43DBDE  - 30 ���� ����� (���� ���� ���)
      ����� �� ���������� � ��� int.
      */
      cos_fi = cos_I_fi*COS_U_plus_Pi + sin_I_fi*SIN_U_plus_Pi;
      sin_fi = -(sin_I_fi*COS_U_plus_Pi - cos_I_fi*SIN_U_plus_Pi);//� ������: "���������, ��� ����", ����� �� � �� ���� ��������

#undef SIN_I
#undef COS_I
#undef SIN_U_plus_Pi
#undef COS_U_plus_Pi

      /*
      � ���� ��������� ���������� ��������, �� COS � SIN ������ ������ � ������� ���� ���� 31(30)-���� �����
      ������� ���������� ������� ������� ������ 7-������ ������� + ����
      ��� ��� �� �������� ������������ ����� �����������, �� ���������� ������ �������
      COS � SIN ���� = 31 - (7 + 1) = 23
      7 - �� ���������� ��������� ������� ������� �������
      1 - �� ���������� �� �� ���������⳺�� ������� (ab+cd)
      */
      unsigned int order_cos, order_sin, max_order, shift = 0;
      order_cos = get_order(cos_fi);
      order_sin = get_order(sin_fi);
      if (order_cos > order_sin) max_order = order_cos; else max_order = order_sin;
      if (max_order > 23) shift = max_order - 23;
  
      /*
      ��� ���� � ����� ���� ���������� ��������� - �� ��� � ������ �� ����� ����������� ����,
      ��� ���� � �������� ������� ���������� ���������.
      ��� ���� ��� � ������������?..
      */

      //���������� �������
      int sin_fi1_minus_fi2;
      int *sector;
      if ((sin_fi >= 0) && (cos_fi >= 0))
      {
        //1-�� ��������
        cos_fi = cos_fi >> shift;
        sin_fi = sin_fi >> shift;
          
        if (sector_directional_tznp[tznp] != 1)
          sector = sector_1_mtz_tznp;
        else
          sector = sector_2_mtz_tznp;
          
#define COS_SECTOR sector[0]    
#define SIN_SECTOR sector[1]    

        sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
        sector_directional_tznp[tznp] = (sin_fi1_minus_fi2 <= 0) ?  1 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR   
      }
      else if ((sin_fi >= 0) && (cos_fi < 0))
      {
        //2-�� ��������
        cos_fi = cos_fi >> shift;
        sin_fi = sin_fi >> shift;

        if (sector_directional_tznp[tznp] != 2)
          sector = sector_1_mtz_tznp;
        else
          sector = sector_2_mtz_tznp;

#define COS_SECTOR sector[2]    
#define SIN_SECTOR sector[3]    

        sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
        sector_directional_tznp[tznp] = (sin_fi1_minus_fi2 >= 0) ?  2 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
      }
      else if ((sin_fi < 0) && (cos_fi < 0))
      {
        //3-�� ��������
        cos_fi = cos_fi >> shift;
        sin_fi = sin_fi >> shift;

        if (sector_directional_tznp[tznp] != 2)
          sector = sector_1_mtz_tznp;
        else
          sector = sector_2_mtz_tznp;

#define COS_SECTOR sector[4]    
#define SIN_SECTOR sector[5]    

        sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
        sector_directional_tznp[tznp] = (sin_fi1_minus_fi2 <= 0) ?  2 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
      }
      else
      {
        //4-�� ��������
        cos_fi = cos_fi >> shift;
        sin_fi = sin_fi >> shift;

        if (sector_directional_tznp[tznp] != 1)
          sector = sector_1_mtz_tznp;
        else
          sector = sector_2_mtz_tznp;

#define COS_SECTOR sector[6]    
#define SIN_SECTOR sector[7]    

        sin_fi1_minus_fi2 = sin_fi*COS_SECTOR - cos_fi*SIN_SECTOR;
        sector_directional_tznp[tznp] = (sin_fi1_minus_fi2 >= 0) ?  1 : 0;
    
#undef COS_SECTOR    
#undef SIN_SECTOR    
      }
    }
    else
    {
      sector_directional_tznp[tznp] = 0;
    }
  }
}
/*****************************************************/

/*****************************************************/
//����������� �����
/*****************************************************/
inline void calc_resistance(int ortogonal_local_calc[], unsigned int number_group_stp, int resistance_output[]) 
{
  const unsigned int index_phase_voltage[3]  = {FULL_ORT_Ua , FULL_ORT_Ub , FULL_ORT_Uc };
  const unsigned int index_line_voltage[3]   = {FULL_ORT_Uab, FULL_ORT_Ubc, FULL_ORT_Uca};
  const unsigned int index_begin_current[3]  = {FULL_ORT_Ia , FULL_ORT_Ib , FULL_ORT_Ic };
  const unsigned int index_end_current[3]    = {FULL_ORT_Ib , FULL_ORT_Ic , FULL_ORT_Ia };
  
  //���������� ���
  int I0_x, I0_y;
  if (current_settings.control_transformator & MASKA_FOR_BIT(INDEX_ML_CTR_TRANSFORMATOR_3I0_3I0_1))
  {
    //3I0-1
    I0_x = (ortogonal_local_calc[2*FULL_ORT_Ia + 0] + ortogonal_local_calc[2*FULL_ORT_Ib + 0] + ortogonal_local_calc[2*FULL_ORT_Ic + 0])/3;
    I0_y = (ortogonal_local_calc[2*FULL_ORT_Ia + 1] + ortogonal_local_calc[2*FULL_ORT_Ib + 1] + ortogonal_local_calc[2*FULL_ORT_Ic + 1])/3;
  }
  else
  {
    //3I0
#if (4 + VAGA_DILENNJA_3I0_DIJUCHE_D_mA) >= VAGA_DILENNJA_I_DIJUCHE  
    I0_x = ((MNOGNYK_3I0_DIJUCHE_D_mA*ortogonal_calc[2*FULL_ORT_3I0 + 0]) >> (4 + VAGA_DILENNJA_3I0_DIJUCHE_D_mA - VAGA_DILENNJA_I_DIJUCHE))/(MNOGNYK_I_DIJUCHE*3);
    I0_y = ((MNOGNYK_3I0_DIJUCHE_D_mA*ortogonal_calc[2*FULL_ORT_3I0 + 1]) >> (4 + VAGA_DILENNJA_3I0_DIJUCHE_D_mA - VAGA_DILENNJA_I_DIJUCHE))/(MNOGNYK_I_DIJUCHE*3);
#else
    I0_x = ((MNOGNYK_3I0_DIJUCHE_D_mA*ortogonal_calc[2*FULL_ORT_3I0 + 0]) << (VAGA_DILENNJA_I_DIJUCHE - (VAGA_DILENNJA_3I0_DIJUCHE_D_mA + 4)))/(MNOGNYK_I_DIJUCHE*3);
    I0_y = ((MNOGNYK_3I0_DIJUCHE_D_mA*ortogonal_calc[2*FULL_ORT_3I0 + 1]) << (VAGA_DILENNJA_I_DIJUCHE - (VAGA_DILENNJA_3I0_DIJUCHE_D_mA + 4)))/(MNOGNYK_I_DIJUCHE*3);
#endif
  }
  int32_t k = (int32_t)current_settings_prt.pickup_dz_k[number_group_stp];
  for (size_t i = 0; i < 3; i++)
  {
    //����������� ���������� ������ Ix + k*I0
    int _a2, _b2;
    /*
    � ��������� ����������� ����������� � ������� ��������� ����� ������� (calc_measurement())
    �������, �� ����������� �������� ������������� ��� ������ ���� ���� 0x6E51, ��� ����� ������� 
    0x907E
    3I0 ���������� �� �������� ������ ������

    Ix + k*I0, �� k ���� �������� �������� 3
    ���
    0x6E51*3 = 0x14AF3. �� � 17 ���� ����� (+ �������� ����) - ����� ����� �������� 18-����
    ��������� ���� ������ �� ���� ��. ���� (Ix + k*I0) ���� ���� 18 ����� ������  (+ �������� ����) - ����� ����� �������� 19-����
    */
    
    _a2 = ortogonal_local_calc[2*index_begin_current[i] + 0] + k*I0_x/100;
    _b2 = ortogonal_local_calc[2*index_begin_current[i] + 1] + k*I0_y/100;

#define _A1     ortogonal_local_calc[2*index_phase_voltage[i] + 0]
#define _B1     ortogonal_local_calc[2*index_phase_voltage[i] + 1]
    
    long long mod = (long long)_a2*(long long)_a2 + (long long)_b2*(long long)_b2;
    
    //����������� �������� ������ Ix
    unsigned int Ix = ( MNOGNYK_I_DIJUCHE*(sqrt_64(mod)) ) >> (VAGA_DILENNJA_I_DIJUCHE + 4);
    
    if (Ix >= PORIG_Ixy)
    {
      //����� ������������� ���������� ���
      /*
          .            .
          Ux          Ux       Re(Ux) + iIm(Ux)    a1 + ib1    (a1 + ib1)(a2 - ib2)    (a1a2 + b1b2) + i(a2b1 - a1b2)    a1a2 + b1b2      a2b1 - a1b2
      --------- = --------- = ------------------ = --------- = --------------------- = ------------------------------ =  ------------ + i--------------
       .     .        .                                                                         2      2                     2      2         2      2
      Ixy + kIo      sum      Re(sum) + iIm(Isum)   a2 + ib2    (a2 + ib2)(a2 - ib2)          a2   + b2                    a2   + b2        a2   + b2
      */
      
      float R = MNOGNYK_R_FLOAT*((float)((long long)_A1*(long long)_a2 + (long long)_B1*(long long)_b2))/((float)mod);
      float X = MNOGNYK_R_FLOAT*((float)((long long)_a2*(long long)_B1 - (long long)_A1*(long long)_b2))/((float)mod);
      resistance_output[R_A + 3*i    ] = (int)R;
      resistance_output[R_A + 3*i + 1] = (int)X;
      
      float Z;
      arm_status res = arm_sqrt_f32((R*R + X*X), &Z);
      resistance_output[R_A + 3*i + 2] = (res == ARM_MATH_SUCCESS) ? (int)Z : UNDEF_RESISTANCE;

      resistance_output[Za_A + i] = 1000*U_PHASE_NOM/Ix; /*Ixy_max ����� �������������� �����. �� ���� ���� �������, �� ��� ���� ������ ����� �� ���� ��������� � �� ����� ����� ������������*/
    }
    else
    {
      //�� ����� ������������� �������� ���
      resistance_output[R_A + 3*i    ] = UNDEF_RESISTANCE;
      resistance_output[R_A + 3*i + 1] = UNDEF_RESISTANCE;
      resistance_output[R_A + 3*i + 2] = UNDEF_RESISTANCE;
      
      resistance_output[Za_A + i] =  UNDEF_RESISTANCE;
    }
    
#undef _A1
#undef _B1
  }
  
  //̳������� ���
  uint32_t Uxy_min, Ixy_max = 0; /*Ixy_max ����� �������������� �����. �� ���� ���� �������, �� ��� ���� ������ ����� �� ���� ��������� � �� ����� ����� ������������*/
  for (unsigned int i = 0; i < 3; i++)
  {
    //����������� ���������� ������ Ixy
    int _a2, _b2;
    /*
    � ��������� ����������� ����������� � ������� ��������� ����� ������� (calc_measurement())
    �������, �� ����������� �������� ������������� ��� ������ ���� ���� 0x6E51, ��� ����� ������� 
    0x120FC

    � ������ ������ �������������� ���� ������, ��, ���� ���������� �� ������� �������� � ��� �������, ��  �����������
    �������� ������������� ���� ����
    0x6E51*2 = 0xDCA2 �� � 16 ���� ����� (+ �������� ����) - ����� ����� �������� 17-����
    */
    
    _a2 = ortogonal_local_calc[2*index_begin_current[i] + 0] - ortogonal_local_calc[2*index_end_current[i] + 0];
    _b2 = ortogonal_local_calc[2*index_begin_current[i] + 1] - ortogonal_local_calc[2*index_end_current[i] + 1];

#define _A1     ortogonal_local_calc[2*index_line_voltage[i] + 0]
#define _B1     ortogonal_local_calc[2*index_line_voltage[i] + 1]
    
    long long mod = (long long)_a2*(long long)_a2 + (long long)_b2*(long long)_b2;
    
    //����������� �������� ������ Ixy
    unsigned int Ixy = ( MNOGNYK_I_DIJUCHE*(sqrt_64(mod)) ) >> (VAGA_DILENNJA_I_DIJUCHE + 4);
    
    if (Ixy >= PORIG_Ixy)
    {
      //����� ������������� �������� ���
      /*
       .
      Uxy   Re(Uxy) + iIm(Uxy)   a1 + ib1    (a1 + ib1)(a2 - ib2)    (a1a2 + b1b2) + i(a2b1 - a1b2)    a1a2 + b1b2      a2b1 - a1b2
      --- = ------------------ = --------- = --------------------- = ------------------------------ =  ------------ + i--------------
       .                                                                     2      2                     2      2         2      2
      Ixy   Re(Ixy) + iIm(Ixy)   a2 + ib2    (a2 + ib2)(a2 - ib2)          a2   + b2                    a2   + b2        a2   + b2
      */
      
      float R = MNOGNYK_R_FLOAT*((float)((long long)_A1*(long long)_a2 + (long long)_B1*(long long)_b2))/((float)mod);
      float X = MNOGNYK_R_FLOAT*((float)((long long)_a2*(long long)_B1 - (long long)_A1*(long long)_b2))/((float)mod);
      resistance_output[R_AB + 3*i    ] = (int)R;
      resistance_output[R_AB + 3*i + 1] = (int)X;
      
      float Z;
      arm_status res = arm_sqrt_f32((R*R + X*X), &Z);
      resistance_output[R_AB + 3*i + 2] = (res == ARM_MATH_SUCCESS) ? (int)Z : UNDEF_RESISTANCE;

      resistance_output[Za_AB + i] = 1000*U_LINEAR_NOM/Ixy; /*Ixy_max ����� �������������� �����. �� ���� ���� �������, �� ��� ���� ������ ����� �� ���� ��������� � �� ����� ����� ������������*/
      
      if (Ixy_max < Ixy) Ixy_max =Ixy;
    }
    else
    {
      //�� ����� ������������� �������� ���
      resistance_output[R_AB + 3*i    ] = UNDEF_RESISTANCE;
      resistance_output[R_AB + 3*i + 1] = UNDEF_RESISTANCE;
      resistance_output[R_AB + 3*i + 2] = UNDEF_RESISTANCE;
      
      resistance_output[Za_AB + i] =  UNDEF_RESISTANCE;
    }
    
    if (i == 0)  
    {
      Uxy_min = measurement[IM_UAB + 0];
    }
    else
    {
      if (Uxy_min > measurement[IM_UAB + i]) Uxy_min = measurement[IM_UAB + i];
    }
    
#undef _A1
#undef _B1
  }
  
  if (Ixy_max > 0)
  {
    //� ��������� ����������� ��������� ���
    resistance_output[Z_3] = 1000*Uxy_min/Ixy_max; /*1000 ������ ��� �������� ���, �� ��/�� �� ��*/
    resistance_output[Za_3] = 1000*U_LINEAR_NOM/Ixy_max; /*1000 ������ ��� �������� ���, �� ��/�� �� ��*/
  }
  else
  {
    //���� ��������� ����������� ��������� ���
    resistance_output[Z_3] = UNDEF_RESISTANCE;
    resistance_output[Za_3] = UNDEF_RESISTANCE;
  }
}
/*****************************************************/

/*****************************************************/
//������������ �������  ��� �����
/*****************************************************/
inline void directional_dz(int ortogonal_local_calc[], unsigned int number_group_stp) 
{
  for (size_t i = 0; i < 3; i++)
  {
    uint32_t index_I, index_U;
    switch (i)
    {
    case 0:
      {
        index_I = IM_IA;
        index_U = IM_UBC;

        break;
      }
    case 1:
      {
        index_I = IM_IB;
        index_U = IM_UCA;

        break;
      }
    case 2:
      {
        index_I = IM_IC;
        index_U = IM_UAB;

        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(85);
      }
    }

    unsigned int porig_Uxy;
    if (Uxy_bilshe_porogu_dz[i] == 0) porig_Uxy = PORIG_CHUTLYVOSTI_VOLTAGE_ANGLE_DZ*KOEF_POVERNENNJA_SECTOR_BLK/100;
    else porig_Uxy = PORIG_CHUTLYVOSTI_VOLTAGE_ANGLE_DZ;
    Uxy_bilshe_porogu_dz[i] = (measurement[index_U] >= porig_Uxy);
      
    unsigned int porig_Ix;
    if (Ix_bilshe_porogu_dz[i] == 0) porig_Ix = PORIG_CHUTLYVOSTI_CURRENT_ANGLE_DZ*KOEF_POVERNENNJA_SECTOR_BLK/100;
    else porig_Ix = PORIG_CHUTLYVOSTI_CURRENT_ANGLE_DZ;
    Ix_bilshe_porogu_dz[i]  = (measurement[index_I] >= porig_Ix );
  }


  for (size_t dz = 0; dz < (4 - 1); dz++)
  {
    int32_t sector_L[2][2];
    switch (dz)
    {
    case 0:
      {
        sector_L[0][0] = current_settings_prt.pickup_dz2_angle_sin1[number_group_stp];
        sector_L[0][1] = current_settings_prt.pickup_dz2_angle_cos1[number_group_stp];
        
        sector_L[1][0] = current_settings_prt.pickup_dz2_angle_sin2[number_group_stp];
        sector_L[1][1] = current_settings_prt.pickup_dz2_angle_cos2[number_group_stp];

        break;
      }
    case 1:
      {
        sector_L[0][0] = current_settings_prt.pickup_dz3_angle_sin1[number_group_stp];
        sector_L[0][1] = current_settings_prt.pickup_dz3_angle_cos1[number_group_stp];
        
        sector_L[1][0] = current_settings_prt.pickup_dz3_angle_sin2[number_group_stp];
        sector_L[1][1] = current_settings_prt.pickup_dz3_angle_cos2[number_group_stp];
        
        break;
      }
    case 2:
      {
        sector_L[0][0] = current_settings_prt.pickup_dz4_angle_sin1[number_group_stp];
        sector_L[0][1] = current_settings_prt.pickup_dz4_angle_cos1[number_group_stp];
        
        sector_L[1][0] = current_settings_prt.pickup_dz4_angle_sin2[number_group_stp];
        sector_L[1][1] = current_settings_prt.pickup_dz4_angle_cos2[number_group_stp];
        
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(84);
      }
    }

    /*
    �� ����������� �������� ��� ���������� ����� ������� ���� ����������� � � ������ (15 �� + ����) = 16-�������� �����
    */
    for (size_t i = 0; i < 3; i++)
    {
      if (
          (Uxy_bilshe_porogu_dz[i] != 0) &&
          (Ix_bilshe_porogu_dz[i]  != 0)
         )
      {
        uint32_t index_I_ort, index_U_ort;
        switch (i)
        {
        case 0:
          {
            index_I_ort = FULL_ORT_Ia;
            index_U_ort = FULL_ORT_Ubc;

            break;
          }
        case 1:
          {
            index_I_ort = FULL_ORT_Ib;
            index_U_ort = FULL_ORT_Uca;

            break;
          }
        case 2:
          {
            index_I_ort = FULL_ORT_Ic;
            index_U_ort = FULL_ORT_Uab;

            break;
          }
        default:
          {
            //���������� ����� ����� �� ���� � ����
            total_error_sw_fixed(25);
          }
        }

#define SIN_I   ortogonal_local_calc[2*index_I_ort    ]
#define COS_I   ortogonal_local_calc[2*index_I_ort + 1]
#define SIN_U   ortogonal_local_calc[2*index_U_ort    ]
#define COS_U   ortogonal_local_calc[2*index_U_ort + 1]

        //������ ���������  ����� ����������� ������ �� 90�
        int32_t amp_cos_U_90 =  SIN_U;//� ������: "���������, ��� ����", ����� �� � �� ���� ��������
        int32_t amp_sin_U_90 = -COS_U;//� ������: "���������, ��� ����", ����� �� � �� ���� ��������

        //���������� COS � SIN ���� ������ �� (U[i]+90�) � I[i]
        int32_t cos_fi, sin_fi;
        /*
        � ��������� ����������� ����������� � ������� ��������� ����� ������� (calc_measurement())
        �������, �� ����������� �������� ������������� ��� ������ ���� ���� 0x6E51, ��� ����� ������� 
        0x120FC, �� ������� �� �� ���� 0x7C87B7BC  - 31 ���� ����� (���� ���� ���)
        ����� �� ���������� � ��� int.
        */
        sin_fi = -(SIN_I*amp_cos_U_90 - COS_I*amp_sin_U_90);//� ������: "���������, ��� ����", ����� �� � �� ���� ��������
        cos_fi = COS_I*amp_cos_U_90 + SIN_I*amp_sin_U_90;

#undef SIN_I
#undef COS_I
#undef SIN_U
#undef COS_U

        /*
        � ���� ��������� ����������� ��������, �� COS � SIN ������ ������ � ������� ���� ���� 31-���� �����
        ������� ���������� ������� ������� ������ 7-������ ������� + ����
        ��� ��� �� �������� ������������ ����� �����������, �� ���������� ������ �������
        COS � SIN ���� = 31 - (7 + 1) = 23
        7 - �� ���������� ��������� ������� ������� �������
        1 - �� ���������� �� �� ���������⳺�� ������� (ab+cd)
        */
        uint32_t order_cos, order_sin, max_order, shift = 0;
        order_cos = get_order(cos_fi);
        order_sin = get_order(sin_fi);
        if (order_cos > order_sin) max_order = order_cos; else max_order = order_sin;
        if (max_order > 23) shift = max_order - 23;
  
        /*
        ��� ���� � ����� ���� ���������� ��������� - �� ��� � ������ �� ����� ����������� ����,
        ��� ���� � �������� ������� ���������� ���������.
        ��� ���� ��� � ������������?..
        */

        const int32_t sector_H[2][2] = {{126, -22}, {123, -35}};
        //���������� �������
        int sin_fi1_minus_fi2;
        const int *sector;
        if ((sin_fi >= 0) && (cos_fi >= 0))
        {
          //1-�� ��������

          if (sector_directional_dz[dz][i] != 1)
            sector = sector_L[0];
          else
            sector = sector_L[1];

          if (*(sector + 0) < 0)
          {
            //����� ������� �����������  � IV ��������, ���� I �������� ������� � � ��� "1"
            sector_directional_dz[dz][i] = 1;
          }
          else
          {
            //����� ������� �����������  � I ��������, ���� ����� ������ ��������
            cos_fi = cos_fi >> shift;
            sin_fi = sin_fi >> shift;
          
            sin_fi1_minus_fi2 = sin_fi*(*(sector + 1)) - cos_fi*(*(sector + 0));
            sector_directional_dz[dz][i] = (sin_fi1_minus_fi2 >= 0) ?  1 : 0;
          }
        }
        else if ((sin_fi >= 0) && (cos_fi < 0))
        {
          //2-�� ��������
          cos_fi = cos_fi >> shift;
          sin_fi = sin_fi >> shift;

          //�������� �� ������ ������� ���� "1"
          if (sector_directional_dz[dz][i] != 1)
            sector = sector_H[0];
          else
            sector = sector_H[1];
          
          sin_fi1_minus_fi2 = sin_fi*(*(sector + 1)) - cos_fi*(*(sector + 0));
          if (sin_fi1_minus_fi2 <= 0) sector_directional_dz[dz][i] = 1;
          else
          {
            //�������� �� ���� "2" (� ��� ��� sin i cos ����� ����� � ������������ �������, �� ���� "2" � ���������� ����� "1" �� 180�)
            if (sector_directional_dz[dz][i] != 2)
              sector = sector_L[0];
            else
              sector = sector_L[1];

            if ((-*(sector + 0)) < 0)
            {
              //����� ������� �����������  � III ��������, ���� ���� II ��������� ������� ��� "0" (�������� �� ���� "1" ��������� ���� ��������������)
              sector_directional_dz[dz][i] = 0;
            }
            else
            {
              //����� ������� �����������  � II ��������, ���� ����� ������ ��������
          
              sin_fi1_minus_fi2 = -(sin_fi*(*(sector + 1)) - cos_fi*(*(sector + 0))); /*-1 ����� ������� - �� sin i cos ������ ������� ���� "1" � ������������ �������*/
              sector_directional_dz[dz][i] = (sin_fi1_minus_fi2 >= 0) ?  2 : 0;
            }
          }
          
        }
        else if ((sin_fi < 0) && (cos_fi < 0))
        {
          //3-�� ��������
          //�������� �� ���� "2" (� ��� ��� sin i cos ����� ����� � ������������ �������, �� ���� "2" � ���������� ����� "1" �� 180�)

          if (sector_directional_dz[dz][i] != 2)
            sector = sector_L[0];
          else
            sector = sector_L[1];

          if ((-*(sector + 0)) > 0)
          {
            //����� ������� �����������  � II ��������, ���� III �������� ������� � � ��� "2"
            sector_directional_dz[dz][i] = 2;
          }
          else
          {
            //����� ������� �����������  � III ��������, ���� ����� ������ ��������
            cos_fi = cos_fi >> shift;
            sin_fi = sin_fi >> shift;
          
            sin_fi1_minus_fi2 = -(sin_fi*(*(sector + 1)) - cos_fi*(*(sector + 0))); /*-1 ����� ������� - �� sin i cos ������ ������� ���� "1" � ������������ �������*/
            sector_directional_dz[dz][i] = (sin_fi1_minus_fi2 >= 0) ?  2 : 0;
          }
        }
        else
        {
          //4-�� ��������
          cos_fi = cos_fi >> shift;
          sin_fi = sin_fi >> shift;

          //�������� �� ������ ������� ���� "2"
          //�������� �� ���� "2" (� ��� ��� sin i cos ����� ����� � ������������ �������, �� ���� "2" � ���������� ����� "1" �� 180�)
          if (sector_directional_dz[dz][i] != 2)
            sector = sector_H[0];
          else
            sector = sector_H[1];
          
          sin_fi1_minus_fi2 = -(sin_fi*(*(sector + 1)) - cos_fi*(*(sector + 0))); /*-1 ����� ������� - �� sin i cos ������ ������� ���� "1" � ������������ �������*/
          if (sin_fi1_minus_fi2 <= 0) sector_directional_dz[dz][i] = 2;
          else
          {
            if (sector_directional_dz[dz][i] != 1)
              sector = sector_L[0];
            else
              sector = sector_L[1];

            if (*(sector + 0) > 0)
            {
              //����� ������� �����������  � I ��������, ���� ���� IV ��������� ������� ��� "0" (�������� �� ���� "2" ��������� ���� ��������������)
              sector_directional_dz[dz][i] = 0;
            }
            else
            {
              //����� ������� �����������  � IV ��������, ���� ����� ������ ��������
          
              sin_fi1_minus_fi2 = sin_fi*(*(sector + 1)) - cos_fi*(*(sector + 0));
              sector_directional_dz[dz][i] = (sin_fi1_minus_fi2 >= 0) ?  1 : 0;
            }
          }
        }
      }
      else
      {
        sector_directional_dz[dz][i] = -1;
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//����������� ������ ���������
/*****************************************************/
inline void calc_power(int ortogonal_local_calc[]) 
{
  /*
  ����������� ����� � ����� ������� ��������� � ���������� ������
  
  .    . .     . .     . .
  S = UaIa* + UbIb* + UcIc*
  */
  
#define IA_SIN          ortogonal_local_calc[2*FULL_ORT_Ia + 1]
#define IA_COS          ortogonal_local_calc[2*FULL_ORT_Ia + 0]
#define UA_SIN          ortogonal_local_calc[2*FULL_ORT_Ua + 1]
#define UA_COS          ortogonal_local_calc[2*FULL_ORT_Ua + 0]
  
#define IB_SIN          ortogonal_local_calc[2*FULL_ORT_Ib + 1]
#define IB_COS          ortogonal_local_calc[2*FULL_ORT_Ib + 0]
#define UB_SIN          ortogonal_local_calc[2*FULL_ORT_Ub + 1]
#define UB_COS          ortogonal_local_calc[2*FULL_ORT_Ub + 0]

#define IC_SIN          ortogonal_local_calc[2*FULL_ORT_Ic + 1]
#define IC_COS          ortogonal_local_calc[2*FULL_ORT_Ic + 0]
#define UC_SIN          ortogonal_local_calc[2*FULL_ORT_Uc + 1]
#define UC_COS          ortogonal_local_calc[2*FULL_ORT_Uc + 0]
  
  long long Re_UaIa, Im_UaIa;
  if (measurement[IM_IA] >= PORIG_I_ENERGY)
  {
    Re_UaIa = UA_COS*IA_COS + UA_SIN*IA_SIN;
    Im_UaIa = UA_SIN*IA_COS - UA_COS*IA_SIN;
  
  }
  else
  {
    Re_UaIa = 0;
    Im_UaIa = 0;
  }
  
  long long Re_UbIb, Im_UbIb;
  if (measurement[IM_IB] >= PORIG_I_ENERGY)
  {
    Re_UbIb = UB_COS*IB_COS + UB_SIN*IB_SIN;
    Im_UbIb = UB_SIN*IB_COS - UB_COS*IB_SIN;
  
  }
  else
  {
    Re_UbIb = 0;
    Im_UbIb = 0;
  }
  
  long long Re_UcIc, Im_UcIc;
  if (measurement[IM_IC] >= PORIG_I_ENERGY)
  {
    Re_UcIc = UC_COS*IC_COS + UC_SIN*IC_SIN;
    Im_UcIc = UC_SIN*IC_COS - UC_COS*IC_SIN;
  
  }
  else
  {
    Re_UcIc = 0;
    Im_UcIc = 0;
  }

#undef IA_SIN
#undef IA_COS
#undef UA_SIN
#undef UA_COS
  
#undef IB_SIN
#undef IB_COS
#undef UB_SIN
#undef UB_COS
  
#undef IC_SIN
#undef IC_COS
#undef UC_SIN
#undef UC_COS
  
  long long P_adc_x16 = Re_UaIa + Re_UbIb + Re_UcIc; /*  ������� ��������� � ������� ��� � � �������� ���������, �� � ������� � 16 ����*/
  long long Q_adc_x16 = Im_UaIa + Im_UbIb + Im_UcIc; /*��������� ��������� � ������� ��� � � �������� ���������, �� � ������� � 16 ����*/
  
  /*
  ���� ����������� �� ����������� MNOGNYK_I_DIJUCHE_FLOAT � MNOGNYK_U_DIJUCHE_FLOAT,
  � ���� ������� �� 16x16 - �� �������� ����� = ����/�����/����
  
  �� ������ ������� ����� � ���/����/���. 
  
  ��� ����� ������� �� �� 1000
  */
  
  //������� ���������
  double P_float = ((double)P_adc_x16) * ((double)(MNOGNYK_I_DIJUCHE_DOUBLE*MNOGNYK_U_DIJUCHE_DOUBLE/(1000.0*16.0*16.0)));
  int P_tmp = (int)(P_float); // � ������� �� ���

  //��������� ���������
  double Q_float = ((double)Q_adc_x16) * ((double)(MNOGNYK_I_DIJUCHE_DOUBLE*MNOGNYK_U_DIJUCHE_DOUBLE/(1000.0*16.0*16.0)));
  int Q_tmp  = (int)(Q_float); // � ������� �� ����

  unsigned int bank_for_enegry_tmp = bank_for_enegry;  
  int *energy_array;
  
  //������� ���������
  if (P_tmp >= 0) energy_array = P_plus;
  else energy_array = P_minus;
  *(energy_array + bank_for_enegry_tmp) += abs(P_tmp);
  
  //��������� ���������
  if     ((Q_tmp >= 0) && (P_tmp >= 0)) energy_array = Q_1q;
  else if((Q_tmp >= 0) && (P_tmp <  0)) energy_array = Q_2q;
  else if((Q_tmp <  0) && (P_tmp <  0)) energy_array = Q_3q;
  else                                  energy_array = Q_4q;
  *(energy_array + bank_for_enegry_tmp) += abs(Q_tmp);
  
  if (++lichylnyk_1s_po_20ms >= MAIN_FREQUENCY)
  {
    if (lichylnyk_1s_po_20ms > MAIN_FREQUENCY)
    {
      //���������� ����� ����� �� ���� � ����
      total_error_sw_fixed(64);
    }

    //����������� ���� ��� ���������� ����� ����� s ��������� �������� � ������ �����
    bank_for_enegry = bank_for_enegry_tmp = (bank_for_enegry_tmp + 1) & 0x1;
    P_plus[bank_for_enegry_tmp] = 0;
    P_minus[bank_for_enegry_tmp] = 0;
    Q_1q[bank_for_enegry_tmp] = 0;
    Q_2q[bank_for_enegry_tmp] = 0;
    Q_3q[bank_for_enegry_tmp] = 0;
    Q_4q[bank_for_enegry_tmp] = 0;
    
    lichylnyk_1s_po_20ms = 0;
    if (periodical_tasks_CALC_ENERGY_DATA == 0)
    {
      //������� ����������� � ���� ����������
      _SET_BIT(clear_diagnostyka, LOSE_ENERGY_DATA);
    }
    else
    {
      //���������� ����������� � ���� ����������
      _SET_BIT(set_diagnostyka, LOSE_ENERGY_DATA);
    }
    periodical_tasks_CALC_ENERGY_DATA = true;
  }
  
}
/*****************************************************/

/*****************************************************/
//���������� ���������
/*****************************************************/
inline void calc_measurement(unsigned int number_group_stp)
{
  int ortogonal_local[2*NUMBER_ANALOG_CANALES];
  unsigned long long sum_sqr_data_3I0_local;
  float value_3I0_i_float, value_3I0_f_float;

  //����������� ������� �������� ���������� ������� � ����������� �������
//  semaphore_measure_values = 1;

  //������� ����� �������� � ������� ����
  /*
  ������� ��� ����������� ������������ ��� ����������� ������� �� ����� ������� � ��������� �� 2 (��������� 2/�),
  �� �� �� ������ ������� ��������
  */
  /*
  �������� ���� ���������� ���������, �� ���� ����������� ������� ������� ������� �� �����/������� �� �����,
  � ���� ��������� ������� �� 2/� (������� �� ��������� �������, ��� ���� � ����� ����),
  �� ��������� ���������� ���������� ���� ���� ���������� ���������� �������� �������
  ����� ��� 3I0            - �� 19 �� + ���� = ((11 �� + ����)*16*16)
        ��� ������ ������ - �� 15 �� + ���� = ((11 �� + ����)*16   )
  ������� ��� �� ����� �� ����� ������� �� �������� � �� ���� �������� ����� ���������� � ���� ��������, ��
  ������ ����� ����� �������� �� �������� - ������������ �� ����, �� (15 �� *2) = 30 �� �� 32 �� unsigned int
  � �� ���� ������� ��������� �� 16, ��� �������� ������� ����������
  
  ��� 3I0 ������� ������������ - ���� ����� ���:
  1.  
  ����� 16-������ ��������� ������� ����� � ������������� ��� 3I0,
  ��� ����������� ������� �� ����� 15-���������� ����� + ����.
  ����� 16-������ ��������� ������� ��� � ����������� ���������
    
  2.����������� 64-���� ����������.
    
  �� 17 ��������� 2014 ���� ��������������� ������ �����.
  ��� �������� ������� ��� ���������� ����� ����� �������. ���������, �� ����� ����
  ��'����� � ���, �� ���� ���������� ������� ������� - �� ����� ����� �������� ������
  ����� ������ �� �������� �������� - � ��� �������� ����� ����� �������
    
  ���� ������ ����������� ������ ����� � 17 ��������� 2014 ����  
  
  ��� ���������� ������� � 18 ��������� 2014 ���� � ������� �������� sin/cos ���
  ����� ������ ������������
  */
  
  unsigned int bank_ortogonal_tmp = (bank_ortogonal + 1) & 0x1;
  for(unsigned int i=0; i<(2*NUMBER_ANALOG_CANALES); i++ )
  {
    ortogonal_local[i] = ortogonal[i][bank_ortogonal_tmp];
  }
  
  /*
  ������� ��� ������������� ���������� ���� �������� � ����� ������� �� �����, 
  �� ��� ����������� ������� �������� ������ �� ������� �������, �� �� �� ������ ����� � ������ ��������
  */
//  sum_sqr_data_3I0_period_local = sum_sqr_data_3I0_period;
  sum_sqr_data_3I0_local = sum_sqr_data_3I0[bank_ortogonal_tmp];

  bank_ortogonal = bank_ortogonal_tmp;
  
  //������ ������� �������� ���������� ������� � ����������� �������
//  semaphore_measure_values = 0;
  
  /*******************************************************/
  //����������, �� ���������� ���� ���������
  /*******************************************************/
  if (changed_ustuvannja == CHANGED_ETAP_ENDED_EXTRA_ETAP) /*�� � �����, �� ��� ��� ���������� ��� �������� �� � ������ �������� �������(� ��� ����� ����� ��� �� ���������)*/
  {
    //������� ����� ��������� � ���� ����� ������ ��� � ���� ������ (���� � �����) ����� ����������� ���������
    for(unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++) 
    {
      phi_ustuvannja_meas[i] = phi_ustuvannja[i];
      phi_ustuvannja_sin_cos_meas[2*i    ] = phi_ustuvannja_sin_cos[2*i    ];
      phi_ustuvannja_sin_cos_meas[2*i + 1] = phi_ustuvannja_sin_cos[2*i + 1];
    }
      
    //�������, �� ���� ������� �������� �������
    changed_ustuvannja = CHANGED_ETAP_NONE;
  }
  /*****************************************************/

  /***
  ��������� ���� � ������� ����������� ��� ����������������� �����
  ***/
  unsigned int copy_to_low_tasks = (semaphore_measure_values_low == 0) ? true : false;
  for (unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++)
  {
    float sin_alpha = ((float)ortogonal_local[2*i    ])/((float)((1 << (VAGA_NUMBER_POINT - 1))));
    float cos_alpha = ((float)ortogonal_local[2*i + 1])/((float)((1 << (VAGA_NUMBER_POINT - 1))));
    
    float sin_beta =  phi_ustuvannja_sin_cos_meas[2*i    ];
    float cos_beta =  phi_ustuvannja_sin_cos_meas[2*i + 1];
    
    unsigned int new_index = index_converter[i];
    int ortogonal_sin = ortogonal_calc[2*new_index    ] = (int)(sin_alpha*cos_beta + cos_alpha*sin_beta);
    int ortogonal_cos = ortogonal_calc[2*new_index + 1] = (int)(cos_alpha*cos_beta - sin_alpha*sin_beta);

    
    //������� ����������� ��� ���������� ����
    if (copy_to_low_tasks == true)
    {
      ortogonal_calc_low[2*new_index    ] = ortogonal_sin;
      ortogonal_calc_low[2*new_index + 1] = ortogonal_cos;
    }
  }
  /***/
  
  /***/
  //����������� ���� �������� 3I0 �� ����������� �������
  /***/
  /*�������� ���������� �����*/
  sum_sqr_data_3I0_local = sqrt_64(sum_sqr_data_3I0_local);
  
  /*��� ���������� ����� �������� � �� ����� ��������� �� ��� ����������*/
  /*�� ������ ����� � ��������� � 256 ���, ���� ���� ���� �� 256*/
  /*��� ���� �����'������� �� �������� ��� ���������� ������ �������� ����� ���������*/

  /*
  �� ���� �� �������� ����� ������� �� ����� � NUMBER_POINT = 32 = 16*2
  ����� �� ���� ������� �� 4*sqrt(2)
  4 �� ������� �� 2
  ((MNOGNYK_3I0_D * X )>> VAGA_DILENNJA_3I0_D)/sqrt(2) �������
   (MNOGNYK_3I0_DIJUCHE_D * X )>> VAGA_DILENNJA_3I0_DIJUCHE_D 
  
  ���� ������ ����� ���� (MNOGNYK_3I0_DIJUCHE_D;VAGA_DILENNJA_3I0_DIJUCHE_D) � (MNOGNYK_3I0_D;VAGA_DILENNJA_3I0_D)
  �� ������ ������� ��� ���������� ����� �������.
  ���� ����� ��� �� ��� ��������� ������
  */
  value_3I0_i_float = (unsigned int)(MNOGNYK_3I0_FLOAT*((float)sum_sqr_data_3I0_local)/(1024.0f)); /*1024 = 4*256. 256 - �� ��������� ������ 3I0; 4 - �� sqrt(16), � 16 �������� � ����. �� 32 = 16*2 */
  measurement[IM_3I0_i] = (unsigned int)value_3I0_i_float; 
  /***/
  
  /*
  ---------------------------------------------------------------------------------------------------------
  150� (150 000��) - ������������ ������ �����
  ����������� ����������� � ��  - Koef_1 = 84,978173543997808495193432804655 ��� ������ ������ (5439/64 = 84,984375)
  
  ��� ��� 150� ����������� ������� �������� ������������� ���� ����
  150000/Koef_1 = 1765,0303364589078874793160507446
  ���� ���������, �� ������ � ��������� � 16 ���, �� ����������� �������� ������������� ���� ����
  16*150000/Koef_1 = 28240,485383342526199669056811914 < 28241(0x6E51) �� � 15 ���� ����� (+ �������� ����)
  ---------------------------------------------------------------------------------------------------------

  ---------------------------------------------------------------------------------------------------------
  150� (150 000��) - ����������� ����� �������
  ����������� ����������� � ��  - Koef_1 = 64,883134509545420915167731259667 ��� ������ ������ (4152/64 = 64,875)
  
  ��� ��� 150� ����������� ������� �������� ������������� ���� ����
  150000/Koef_1 = 2311,848851536795430557291797995
  ���� ���������, �� ������ � ��������� � 16 ���, �� ����������� �������� ������������� ���� ����
  16*150000/Koef_1 = 36989,581624588726888916668767919 < 36990(0x907E) �� � 16 ���� ����� (+ �������� ����) - ����� ����� �������� 17-����
  
  ���� � ����� ������� ������������� ����� �������, ��, ���� ���������� �� ������� �������� � ��� �������, ��  �����������
  �������� ������������� ���� ����
  2*16*150000/Koef_1 = 73979,163249177453777833337535838 < 73980(0x120FC) �� � 17 ���� ����� (+ �������� ����) - ����� ����� �������� 18-����
  ---------------------------------------------------------------------------------------------------------
  
  ---------------------------------------------------------------------------------------------------------
  2� (2 000�� * 10 = 20 000(������� ��)) - ������������ ����� 3I0
  ����������� ����������� � ����� ��  - Koef_1* = 169,95634708799561699038686560931 ��� 3I0  ��� 3I0 ��� �������� � ������� �������� (170/1 = 170)

  
  ��� ��� 2� ����������� ������� �������� ������������� ���� ����
  20000/Koef_1* = 117,67727621049018824880803941698
  ���� ���������, �� ������ � ��������� � 16 ��� (��������� � 256 ��� �� ��� �������� �� 16), �� ����������� �������� ������������� ���� ����
  16*20000/Koef_1* = 1882,8364193678430119809286306717 < 1883(0x075B) �� � 11 ���� ����� (+ �������� ����)
  ---------------------------------------------------------------------------------------------------------
  */
  
  /***/
  //����������� ���� �������� ����� ������������ ���'�
  /***/
  for(unsigned int i = 0; i < NUMBER_ANALOG_CANALES; i++)
  {
    if (i == I_3I0)
    {
      long long a, b;
      a = (long long)ortogonal_calc[2*FULL_ORT_3I0];
      b = (long long)ortogonal_calc[2*FULL_ORT_3I0 + 1];
      unsigned long long a2, b2, c;
      a2 = a*a;
      b2 = b*b;
      c = a2 + b2;
      unsigned int d;
      d = sqrt_64(c);
      value_3I0_f_float = (unsigned int)(MNOGNYK_3I0_FLOAT*((float)d)/(256.0f)); /*256 - �� ��������� ������� 3I0*/

      measurement[IM_3I0] = (unsigned int)value_3I0_f_float;
    }
    else if ((i >= I_Ia) && (i <= I_Ic))
    {
      unsigned int index_m, index_ort;
      switch (i)
      {
      case I_Ia:
        {
          index_m = IM_IA;
          index_ort = FULL_ORT_Ia;
          break;
        }
      case I_Ib:
        {
          index_m = IM_IB;
          index_ort = FULL_ORT_Ib;
          break;
        }
      case I_Ic:
        {
          index_m = IM_IC;
          index_ort = FULL_ORT_Ic;
          break;
        }
      default:
        {
          //���������� ����� ����� �� ���� � ����
          total_error_sw_fixed(66);
        }
      }
      
      measurement[index_m] = ( MNOGNYK_I_DIJUCHE*(sqrt_32((unsigned int)(ortogonal_calc[2*index_ort]*ortogonal_calc[2*index_ort]) + (unsigned int)(ortogonal_calc[2*index_ort+1]*ortogonal_calc[2*index_ort+1]))) ) >> (VAGA_DILENNJA_I_DIJUCHE + 4);
    }
    else
    {
      unsigned int index_m, index_ort;
      switch (i)
      {
      case I_Ua:
      case I_Ub:
      case I_Uc:
        {
          unsigned int delta_index = (i - I_Ua);
          index_m = IM_UA + delta_index;
          index_ort = FULL_ORT_Ua + delta_index;
          break;
        }
      case I_3U0:
        {
          index_m = IM_3U0;
          index_ort = FULL_ORT_3U0;
          break;
        }
      default:
        {
          //���������� ����� ����� �� ���� � ����
          total_error_sw_fixed(67);
        }
      }
      
      measurement[index_m] = ( MNOGNYK_U_DIJUCHE*(sqrt_32((unsigned int)(ortogonal_calc[2*index_ort]*ortogonal_calc[2*index_ort]) + (unsigned int)(ortogonal_calc[2*index_ort+1]*ortogonal_calc[2*index_ort+1]))) ) >> (VAGA_DILENNJA_U_DIJUCHE + 4);
    }
    
  }
  /***/

  /***/
  //����������� ���� �������� ����� ������� 3I0
  /***/
  if (value_3I0_i_float > value_3I0_f_float)
  {
    float in_square_root, out_square_root;
    in_square_root = value_3I0_i_float*value_3I0_i_float - value_3I0_f_float*value_3I0_f_float;
    if (arm_sqrt_f32(in_square_root, &out_square_root) == ARM_MATH_SUCCESS)
    {
      measurement[IM_3I0_other_g] = (unsigned int)out_square_root;
    }
    else
    {
      //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
      total_error_sw_fixed(59);
    }
  }
  else
    measurement[IM_3I0_other_g] = 0;
  /***/

  /***
  �������������� 3I0(������������, ���� � Ib), ������ ������ � Ib(���� Ib ����)
  ***/
  int _x, _y;

  _x = ortogonal_calc[2*FULL_ORT_3I0_r + 0] = ortogonal_calc[2*FULL_ORT_Ia    ] + ortogonal_calc[2*FULL_ORT_Ib    ] + ortogonal_calc[2*FULL_ORT_Ic    ];
  _y = ortogonal_calc[2*FULL_ORT_3I0_r + 1] = ortogonal_calc[2*FULL_ORT_Ia + 1] + ortogonal_calc[2*FULL_ORT_Ib + 1] + ortogonal_calc[2*FULL_ORT_Ic + 1];
  if (copy_to_low_tasks == true)
  {
    ortogonal_calc_low[2*FULL_ORT_3I0_r + 0] = _x;
    ortogonal_calc_low[2*FULL_ORT_3I0_r + 1] = _y;
  }
  measurement[IM_3I0_r] = ( MNOGNYK_I_DIJUCHE*(sqrt_64((unsigned long long)((long long)_x*(long long)_x) + (unsigned long long)((long long)_y*(long long)_y))) ) >> (VAGA_DILENNJA_I_DIJUCHE + 4);
    
  //Ubc
  _x = ortogonal_calc[2*FULL_ORT_Ubc + 0] = ortogonal_calc[2*FULL_ORT_Ub    ] - ortogonal_calc[2*FULL_ORT_Uc    ];
  _y = ortogonal_calc[2*FULL_ORT_Ubc + 1] = ortogonal_calc[2*FULL_ORT_Ub + 1] - ortogonal_calc[2*FULL_ORT_Uc + 1];
  if (copy_to_low_tasks == true)
  {
    ortogonal_calc_low[2*FULL_ORT_Ubc + 0] = _x;
    ortogonal_calc_low[2*FULL_ORT_Ubc + 1] = _y;
  }
  measurement[IM_UBC] = ( MNOGNYK_U_DIJUCHE*(sqrt_64((unsigned long long)((long long)_x*(long long)_x) + (unsigned long long)((long long)_y*(long long)_y))) ) >> (VAGA_DILENNJA_U_DIJUCHE + 4);
  
  //Uca
  _x = ortogonal_calc[2*FULL_ORT_Uca + 0] = ortogonal_calc[2*FULL_ORT_Uc    ] - ortogonal_calc[2*FULL_ORT_Ua    ];
  _y = ortogonal_calc[2*FULL_ORT_Uca + 1] = ortogonal_calc[2*FULL_ORT_Uc + 1] - ortogonal_calc[2*FULL_ORT_Ua + 1];
  if (copy_to_low_tasks == true)
  {
    ortogonal_calc_low[2*FULL_ORT_Uca + 0] = _x;
    ortogonal_calc_low[2*FULL_ORT_Uca + 1] = _y;
  }
  measurement[IM_UCA] = ( MNOGNYK_U_DIJUCHE*(sqrt_64((unsigned long long)((long long)_x*(long long)_x) + (unsigned long long)((long long)_y*(long long)_y))) ) >> (VAGA_DILENNJA_U_DIJUCHE + 4);

  //Uab
  _x = ortogonal_calc[2*FULL_ORT_Uab + 0] = ortogonal_calc[2*FULL_ORT_Ua    ] - ortogonal_calc[2*FULL_ORT_Ub    ];
  _y = ortogonal_calc[2*FULL_ORT_Uab + 1] = ortogonal_calc[2*FULL_ORT_Ua + 1] - ortogonal_calc[2*FULL_ORT_Ub + 1];
  if (copy_to_low_tasks == true)
  {
    ortogonal_calc_low[2*FULL_ORT_Uab + 0] = _x;
    ortogonal_calc_low[2*FULL_ORT_Uab + 1] = _y;
  }
  measurement[IM_UAB] = ( MNOGNYK_U_DIJUCHE*(sqrt_64((unsigned long long)((long long)_x*(long long)_x) + (unsigned long long)((long long)_y*(long long)_y))) ) >> (VAGA_DILENNJA_U_DIJUCHE + 4);
  
//  if (measurement[IM_UAB] < test_array[0][0]) test_array[0][0] = measurement[IM_UAB];
//  if (measurement[IM_UAB] > test_array[1][0]) test_array[1][0] = measurement[IM_UAB];
//
//  if (measurement[IM_UBC] < test_array[0][1]) test_array[0][1] = measurement[IM_UBC];
//  if (measurement[IM_UBC] > test_array[1][1]) test_array[1][1] = measurement[IM_UBC];
//
//  if (measurement[IM_UCA] < test_array[0][2]) test_array[0][2] = measurement[IM_UCA];
//  if (measurement[IM_UCA] > test_array[1][2]) test_array[1][2] = measurement[IM_UCA];
  
  /***/
  //����������� ������� ����� � ��������� �����������
  /***/
  velychyna_zvorotnoi_poslidovnosti(ortogonal_calc, INDEX_U);
  /***/

  /***/
  //������������ ������� ��� �� (��� �������)
  /***/
  if ((current_settings_prt.configuration & (1<<DZ_BIT_CONFIGURATION)) != 0)
  {
    directional_dz(ortogonal_calc, number_group_stp);
  }
  else
  {
    for (size_t i = 0; i < 3; i++)
    {
      Uxy_bilshe_porogu_dz[i] = 0;
      Ix_bilshe_porogu_dz[i] = 0;
      for (size_t dz = 0; dz < (4 - 1); dz++) sector_directional_dz[dz][i] = -1;
    }
  }
  /***/

  /***/
  //������������ ������� ��� ��� (��� �������)
  /***/
  if ((current_settings_prt.configuration & (1<<MTZ_BIT_CONFIGURATION)) != 0)
  {
    directional_mtz(ortogonal_calc, number_group_stp);
  }
  else
  {
    for (size_t i = 0; i < 3; i++)
    {
      Uxy_bilshe_porogu[i] = 0;
      Ix_bilshe_porogu[i] = 0;
      for (size_t msz = 0; msz < 4; msz++) sector_directional_mtz[msz][i] = 0;
    }
  }
  /***/

  if ((current_settings_prt.configuration & (1<<TZNP_BIT_CONFIGURATION)) != 0)
  {
    /***/
    //������������ ������� ��� ���� (��� �������)
    /***/
    directional_tznp(ortogonal_calc, number_group_stp);
    /***/
  }
  else
  {
    TZNP_3U0_bilshe_porogu = 0;
    TZNP_3I0_r_bilshe_porogu = 0;
    for (size_t sznp = 0; sznp < 3; sznp++) sector_directional_tznp[sznp] = 0;
  }
  
  if ((current_settings_prt.configuration & (1<<ZZ_BIT_CONFIGURATION)) != 0)
  {
    if ((current_settings_prt.control_zz & CTR_ZZ1_TYPE) == 0)
    {
      /***/
      //������������ ������� ��� ���
      /***/
      detector_kuta_nzz(ortogonal_calc);
      /***/
    }
  }
  else
  {
    sector_i_minus_u_1 = 0;
    sector_i_minus_u_2 = 0;
  }
  
  /***/
  //����������� ����� ����� � ��������� �����������
  /***/
  velychyna_zvorotnoi_poslidovnosti(ortogonal_calc, INDEX_I);
  /***/
  
  /***/
  //����������� �����
  /***/
  calc_resistance(ortogonal_calc, number_group_stp, resistance);
  /***/

  if(++number_inputs_for_fix_one_period >= 20)
  {
    /***/
    //���������� ������� ����������� (��� �� 20��)
    /***/
    calc_power(ortogonal_calc);
    /***/
    
    number_inputs_for_fix_one_period = 0;
  }
}
/*****************************************************/

/*****************************************************/
//������ ������� ���������� �����
/*****************************************************/
inline void input_scan(void)
{
  unsigned int state_inputs_into_pin = 0; //���� � ��� ������� �������� ����� ������� �� ����� ��������� (���)
  static unsigned int state_inputs_into_pin_trigger; //� ��� ����� ���������� ��������� ���� ���, � ������� ���� �� ���������� .�� ���������� ��� ���� �� ���� ���������� ������� �������

  /***************************/
  //� ��� ������ ������ ����� ����� ��������� (���), �� ���������� �� �������� �����
  /*
  -----------------------------
  �������� ��������� � �������� ��� ����� state_inputs_into_pin
    "�     ������ " - ������� ������������� ��� (1)
    "���� �������" - ������� ���������     ��� (0)
  -----------------------------
  */
  state_inputs_into_pin |=  ( _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD33_DD36)       & 0xffff)
#if (MODYFIKACIA_VERSII_PZ == 0)
                         | (((_DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD26_DD29) >> 8) &    0xf) << 16)
#endif
                        ;
  /***************************/
  
  /***************************/
  //������� ������� ������� ���������� �����
  /***************************/
  for(unsigned int i = 0; i < NUMBER_INPUTS; i++)
  {
    unsigned int maska = 1<<i;
    int max_value_timer = current_settings_prt.dopusk_dv[i];

    if (global_timers[INDEX_TIMER_INPUT_START + i] < 0)
    {
      //������� �� ���� ����� ����������� ����� ����������� ����� ���, ���� �������� ������� � ��'�����
      //�� ������ �� ������ �� ��������� � ��������� ������
      
      //���������� �� ��������� ���� ����� ������� ������������ �����
      if ((state_inputs_into_pin & maska) != (state_inputs & maska))
      {
        //���� ���� ����� �������, �� �������� 䳿 �� ��� �����

        //1-��: �����'������� ������� ���� �����
        state_inputs_into_pin_trigger &= ~maska;
        state_inputs_into_pin_trigger |= (state_inputs_into_pin & maska);

        //2-��: ��������� ������ ������� ����������� �����
        global_timers[INDEX_TIMER_INPUT_START + i] = 0;
      }
    }
    else
    {
      //���� ������ ��������� �������� 䳿 � ��������
      if (global_timers[INDEX_TIMER_INPUT_START + i] < max_value_timer)
      {
        //���� ������ �� �� ����� �� ����� ���������, �� ������ �������� ���� ��������
        global_timers[INDEX_TIMER_INPUT_START + i] += DELTA_TIME_FOR_TIMERS;
        
        //� �������, ���� ��� ������� �� ���� �������� ������
        //� �� ���������� �� �� ������� ������� "� ������"->"���� �������"
        //�� ����� ������� �� ��� ���������� ������� ������� ������, �� ������ �� ���� � - 
        //� �� ������, �� ����� �������� n�����, �� �������� "� ������"->"���� �������" �� ������ ���������� ������� �� ����������� 
        if ((current_settings_prt.type_of_input_signal & maska) != 0)
        {
           if ((state_inputs_into_pin_trigger & maska) == 0)
           {
             if ((state_inputs_into_pin & maska) != 0)
               global_timers[INDEX_TIMER_INPUT_START + i] = -1;
           }
        }
      }
    }
    
    //���� �������� ������� ������� ����������� � ����� ������������� �������, �� ����������, �� �������� ������� ����� �����
    if (global_timers[INDEX_TIMER_INPUT_START + i] >= max_value_timer)
    {
      //����������, �� ���� ��� ������� � �������� �� ������, ���� ��� �� ������ ������� ������� ������� ����������� �����
      unsigned int state_1, state_2;
        
      state_1 = state_inputs_into_pin_trigger & maska;
      state_2 = state_inputs_into_pin  & maska;
        
      if (state_1 == state_2)
      {
        //���� ��� ����� ����������, �� �� �������, �� �������� ��� ����� ����������� ����� � ������� ����� ���� �����
        //��� ����� ��������� �� ��� �������    ����� 1 - �� �������� ����, � 0 - �� �������� ����
        //                        ��� ���������� ����� 0 - �� �������� ����, � 1 - �� �������� ����
          state_inputs &=  ~maska;
          state_inputs |=   state_2;
      }
        
      //� ����-����� ������, �� ������� ���� �����, �� �, � ������� ������ ������� ���������� �� ����, �� ������������� � �������� ��'���� ��������
      global_timers[INDEX_TIMER_INPUT_START + i] = -1;
    }
  }
  /***************************/
  
  /***************************/
  //���������, ���� ������ � ����� ��������
  /***************************/
  active_inputs = (state_inputs ^ current_settings_prt.type_of_input);
  /***************************/
  
}
/*****************************************************/

/*****************************************************/
//������� ������� �������
/*****************************************************/
inline void clocking_global_timers(void)
{
  //����������� �������� �����
  input_scan();
  
  //����������� �� ����� ������� �����
  for (unsigned int i = (INDEX_TIMER_INPUT_START + NUMBER_INPUTS); i < MAX_NUMBER_GLOBAL_TIMERS; i++)
  {
    if (global_timers[i] >= 0)
    {
      //������ ������ ����, �� ������ ����� ��������� � ��� ����, �� �������� ������� �� ��'����

      //���������� �� ����� ���������� �������� �������, ���� �� �� �� �������� ����� ���������
      if (global_timers[i] <= (0x7fffffff - DELTA_TIME_FOR_TIMERS)) global_timers[i] += DELTA_TIME_FOR_TIMERS;
    }
  }
  
  if (++timer_prt_signal_output_mode_2 >= PERIOD_SIGNAL_OUTPUT_MODE_2)
  {
    timer_prt_signal_output_mode_2 = 0;
    output_timer_prt_signal_output_mode_2 ^= true;
  }
}
/*****************************************************/

/*****************************************************/
//����������� ������������� ������� - �� ����������� ���� ������������� ����� ��� �������
/*****************************************************/
inline void df_handler(unsigned int *p_active_functions, unsigned int *p_changed_state_with_start_new_timeout)
{
  /*
  ������� ��������� ������� � source_activation_df
  ������� ����� ��� �������� ������� � maska_active_df
  */
  static unsigned int source_activation_df_prev;
  
  unsigned int source_activation_df = 0;
  unsigned int state_df = 0;
  for (unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
  {
    unsigned int number_byte_in, number_bit_in, number_byte_out, number_bit_out;
    switch (i)
    {
    case 0:
      {
        number_byte_in = RANG_DF1_IN >> 5;
        number_bit_in = RANG_DF1_IN & 0x1f;

        number_byte_out = RANG_DF1_OUT >> 5;
        number_bit_out = RANG_DF1_OUT & 0x1f;
        
        break;
      }
    case 1:
      {
        number_byte_in = RANG_DF2_IN >> 5;
        number_bit_in = RANG_DF2_IN & 0x1f;

        number_byte_out = RANG_DF2_OUT >> 5;
        number_bit_out = RANG_DF2_OUT & 0x1f;
        
        break;
      }
    case 2:
      {
        number_byte_in = RANG_DF3_IN >> 5;
        number_bit_in = RANG_DF3_IN & 0x1f;

        number_byte_out = RANG_DF3_OUT >> 5;
        number_bit_out = RANG_DF3_OUT & 0x1f;
        
        break;
      }
    case 3:
      {
        number_byte_in = RANG_DF4_IN >> 5;
        number_bit_in = RANG_DF4_IN & 0x1f;

        number_byte_out = RANG_DF4_OUT >> 5;
        number_bit_out = RANG_DF4_OUT & 0x1f;
        
        break;
      }
    case 4:
      {
        number_byte_in = RANG_DF5_IN >> 5;
        number_bit_in = RANG_DF5_IN & 0x1f;

        number_byte_out = RANG_DF5_OUT >> 5;
        number_bit_out = RANG_DF5_OUT & 0x1f;
        
        break;
      }
    case 5:
      {
        number_byte_in = RANG_DF6_IN >> 5;
        number_bit_in = RANG_DF6_IN & 0x1f;

        number_byte_out = RANG_DF6_OUT >> 5;
        number_bit_out = RANG_DF6_OUT & 0x1f;
        
        break;
      }
    case 6:
      {
        number_byte_in = RANG_DF7_IN >> 5;
        number_bit_in = RANG_DF7_IN & 0x1f;

        number_byte_out = RANG_DF7_OUT >> 5;
        number_bit_out = RANG_DF7_OUT & 0x1f;
        
        break;
      }
    case 7:
      {
        number_byte_in = RANG_DF8_IN >> 5;
        number_bit_in = RANG_DF8_IN & 0x1f;

        number_byte_out = RANG_DF8_OUT >> 5;
        number_bit_out = RANG_DF8_OUT & 0x1f;
        
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(43);
        break;
      }
    }

//    if (i < NUMBER_DEFINED_FUNCTIONS/*current_settings_prt.number_defined_df*/)
    {
      /***
      ������� ��������� ��-��
      ***/
      source_activation_df |= ((p_active_functions[number_byte_in] & (1 << number_bit_in) ) >> number_bit_in ) << i;
      //���������� ��, �� �� ��� ���������� �������� ������� �� ����� ������-����������� (��� ��������� ����� ������ ��� ���������)
      if (global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] >= 0)
      {
        //������ ���������, ��� ��� ���������
        //���� ������� ����� ������� ������, �� ��������� ���������� ����� ������, ��� ���������
        //���� ��� ������������ ������ ������ ����� �� ���� ������ ����� ������� �����������, �� ������� ��������� �������
        source_activation_df |= (1 << i);
      
        //³������, ������� ��������� ����������� � ��������� ���� � ����� ���������� �������
        p_active_functions[number_byte_in] |= (1 << number_bit_in);
      
        //� �������, ���� ������ ����� �� ����� ������������ ��������, �� ������� ������ ����� �������
        if (global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] >= ((int)current_settings_prt.timeout_pause_df[i]))
          global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] = -1;
      }
      /***/

      /***
      ���������� ����� �� ����� ���� �������� ��-��
      ***/
      state_df |= (((p_active_functions[number_byte_out] & ((unsigned int)(1 << number_bit_out))) != 0) || (etap_execution_df[i] == EXECUTION_DF)) << i;
      /***/
    }
//    else
//    {
//      //�������, �� �� ����� ������� � ������
//      global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] = -1;
//      global_timers[INDEX_TIMER_DF_PAUSE_START + i] = -1;
//      global_timers[INDEX_TIMER_DF_WORK_START + i] = -1;
//      
//      etap_execution_df[i] = NONE_DF;
//    }
    }
  
  //���������, �� ������������� ���������� ������� ����� ��� �������� �������-�������
  unsigned int source_blk_df = 0;
  for (unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS/*current_settings_prt.number_defined_df*/; i++)
  {
    if (
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 6] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 7] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 8] !=0) ||
        (current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 9] !=0)
       )
    {
      //�������, ���� ������� ��������� �� ������� ������ �������
      if(
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i    ] & p_active_functions[0] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 1] & p_active_functions[1] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 2] & p_active_functions[2] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 3] & p_active_functions[3] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 4] & p_active_functions[4] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 5] & p_active_functions[5] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 6] & p_active_functions[6] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 7] & p_active_functions[7] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 8] & p_active_functions[8] ) != 0) ||
         ( ( current_settings_prt.ranguvannja_df_source_plus[N_BIG*i + 9] & p_active_functions[9] ) != 0) 
        )
      {
        source_activation_df |= (1 << i);
      }
    }

    if (
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 6] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 7] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 8] !=0) ||
        (current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 9] !=0)
       )
    {
      //�������, ���� ������� ��������� �� ������� ��������� �������
      if(
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i    ] & ((unsigned int)(~p_active_functions[0])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 1] & ((unsigned int)(~p_active_functions[1])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 2] & ((unsigned int)(~p_active_functions[2])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 3] & ((unsigned int)(~p_active_functions[3])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 4] & ((unsigned int)(~p_active_functions[4])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 5] & ((unsigned int)(~p_active_functions[5])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 6] & ((unsigned int)(~p_active_functions[6])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 7] & ((unsigned int)(~p_active_functions[7])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 8] & ((unsigned int)(~p_active_functions[8])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_minus[N_BIG*i + 9] & ((unsigned int)(~p_active_functions[9])) ) != 0 )
        )
      {
        source_activation_df |= (1<< i);
      }
    }

    if (
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 6] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 7] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 8] !=0) ||
        (current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 9] !=0)
       )
    {
      //�������, ���� ������� ��������� �������� �� ������� ����������
      if(
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i    ] & p_active_functions[0] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 1] & p_active_functions[1] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 2] & p_active_functions[2] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 3] & p_active_functions[3] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 4] & p_active_functions[4] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 5] & p_active_functions[5] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 6] & p_active_functions[6] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 7] & p_active_functions[7] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 8] & p_active_functions[8] ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_df_source_blk[N_BIG*i + 9] & p_active_functions[9] ) != 0 )
        )
      {
        source_blk_df |= (1<< i);
      }
    }
    
    //��������� � ������ ������� ����� ������ ����������� �������
    switch (etap_execution_df[i])
    {
    case NONE_DF:
      {
        if ((source_activation_df & (1<<i)) != 0)
        {
           if (current_settings_prt.timeout_pause_df[i] > 0)
           {
             //�������, ���� � ����� ���������� ��, ����� ��������� ������ �����
             //��������� ������������� ������� �����
             global_timers[INDEX_TIMER_DF_PAUSE_START + i] = 0;
             //������� ���� ��������� ������ ����� �� ���������� ���������� ���� �����
             etap_execution_df[i] = START_TIMER_PAUSE_DF;
           }
           else
           {
             //�������, ���� ������ ����� ����� ����, ����� ����� ����� ������������ �� � ��������� ������ ������

             if (
                 (current_settings_prt.timeout_work_df[i] > 0) ||
                 ((current_settings_prt.type_df & (1<<i)) != 0)
                )   
             {
              //������������ ���� ���� �� � "��������"
              state_df |= (1 << i);
              //��������� ������������� ������� ������
              global_timers[INDEX_TIMER_DF_WORK_START + i] = 0;
              //���������� �� ������������� ������� ������ - �������� ����� ���� �� ����������� ���������� (���� ���� ����� ����������)
              etap_execution_df[i] = EXECUTION_DF;
             }
             else etap_execution_df[i] = WAITING_DEACTIVATION_SOURCE_DF;
           }
           
           //Գ������ ��� ���� ����� � �������� ��������������� ���� ��������
           *p_changed_state_with_start_new_timeout |= (1 << i);
        }
        break;
      }
    case START_TIMER_PAUSE_DF:
      {
        //����� ��� ���� ���� ������� �����
        //����������, �� �� �� ��������� � ���� ��������� ����� ��� �������
        if ((source_activation_df & (1<< i)) != 0)
        {
          //����������, �� ����������� ������ ������� �����
          if (global_timers[INDEX_TIMER_DF_PAUSE_START + i] >= ((int)current_settings_prt.timeout_pause_df[i]))
          {
            if ((*p_changed_state_with_start_new_timeout & (1 << i)) == 0)
            {
              //���������� ��� ������ ������� �����
              global_timers[INDEX_TIMER_DF_PAUSE_START + i] = -1;
  
              if (
                  (current_settings_prt.timeout_work_df[i] > 0) ||
                  ((current_settings_prt.type_df & (1<<i)) != 0)
                 )   
              {
                //������������ ���� ���� �� � "��������"
                state_df |= (1 << i);
                //��������� ������������� ������� ������
                global_timers[INDEX_TIMER_DF_WORK_START + i] = 0;
                //���������� �� ������������� ������� ������ - �������� ����� ���� �� ����������� ���������� (���� ���� ����� ����������)
                etap_execution_df[i] = EXECUTION_DF;
              }
              else etap_execution_df[i] = WAITING_DEACTIVATION_SOURCE_DF;
           
              //Գ������ ��� ���� ����� � �������� ��������������� ���� ��������
              *p_changed_state_with_start_new_timeout |= (1 << i);
            }
          }
        }
        else
        {
          //��������� ����� �� ���������� ������ ������� �����, ���� ������� ��� ������ �� ���� ������������ �������
          global_timers[INDEX_TIMER_DF_PAUSE_START + i] = -1;
          etap_execution_df[i] = NONE_DF;
           
          //³���� �������� ��� ���� ����� � �������� ��������������� ���� ��������
          *p_changed_state_with_start_new_timeout &= (unsigned int)(~(1 << i));
        }
        break;
      }
    case EXECUTION_DF:
      {
        //�������� ������ ���� �� �������� �� ���� ��
        if ((current_settings_prt.type_df & (1<<i)) != 0)
        {
          //���� �� ��������
          //����� ������ ����� �������� �� ������ ������ �� ����������� ���� ����������� �������
          if ((source_activation_df & (1<< i)) != 0)
          {
            //������� �� � �������, � ���� ������ ������ ��������/��������� � ��������� �������
            global_timers[INDEX_TIMER_DF_WORK_START + i] = 0;
          }
        }
        else
        {
          //���� �� �����
          if (
              ((source_activation_df_prev & (1 << i)) == 0) &&
              ((source_activation_df      & (1 << i)) != 0)
             )   
          {
            //������� �� ������ ������������, � ���� ������ ������ ��������� � ��������� �������
            global_timers[INDEX_TIMER_DF_WORK_START + i] = 0;
          }
        }

        //����������, �� ����������� ������ ������� ������
        /*
        ������ ����������� ��������� �� � ������� ���� �� �������� � ������� � ��������
        �������� �� ��� ������� ��� � ���� ��������� ���������, ��� � ���� �����, ����
        ������� � ��������� � ������� �������, �� ��� ���� ����� ������ ������ � 0, 
        ����� �� ���� ����������� � 0, ��� ���� ������� "������ ������" ��� ���� ������� ���� 0,
        �� �� ������ ������ ������� ������ ������� ���� ����������, �� �� ���������.
        ���� ��� �� � �������� ��������, �� �� �� ���� �������������� ����� ���� ������ ������
        �������� ���� ������� � ������� ���� � �� � ���������� � ������� � ��������
        */
        if (
            (global_timers[INDEX_TIMER_DF_WORK_START + i] >= ((int)current_settings_prt.timeout_work_df[i])) &&
            (
             !( 
               ((current_settings_prt.type_df & (1 << i)) != 0) && 
               ((source_activation_df         & (1 << i)) != 0) 
              )
            )  
           )
        {
          if ((*p_changed_state_with_start_new_timeout & (1 << i)) == 0)
          {
            //���������� ��� ������ ������� ������
            global_timers[INDEX_TIMER_DF_WORK_START + i] = -1;
            //���������� �� � �������� ����
            state_df &= ~(1 << i);
          
            //����������, �� ��� ����� ������� � ���������� ����������� ������� ��, �� ������� � ��������� ����
            if ((source_activation_df & (1<< i)) == 0)
            {
              //���������� � ����� ��������� ����
              etap_execution_df[i] = NONE_DF;
            }
            else 
            {
              //���� ������� ������� ���� �� �� �������, �� ���������� �� ���������� ���� ����������
              etap_execution_df[i] = WAITING_DEACTIVATION_SOURCE_DF;
            }
          }
        }
        break;
      }
    case WAITING_DEACTIVATION_SOURCE_DF:
      {
        //� ����� ����� �� ���������� ����, ���� ������� ��������� �� �� ���� �����
        if ((source_activation_df & (1 << i)) == 0)
        {
          //���������� � ����� ��������� ����
          etap_execution_df[i] = NONE_DF;
        }
        break;
      }
    default: break;
    }
  }
  source_activation_df_prev = source_activation_df;

  //������������, ��� ������� �� � ����� �������, �� ����� ������ ��������������
  /*
  ��� ���� � ��������� �� ��'���� � ����, � ������� �������, �� � ������� �� �������������
  ����� p_active_functions � ����� �� �� ���������� ������ ��-��, ���� �� ���� ��-��
  ������ ���� �������� ���������, ��� �������� ��������� ���� ���� �������� �������� ��, � �� ��,
  �� ����� ��������������. � �������� � ������� ����� �� ������������ �������� � �����
  p_active_functions, �� ��������� ����� ����� ����, �� ��� �� ������ ��'������� ������������ ��������
  � ����������� �� ����� ���'����� (���� ������ ������ � ����� � ������ ���������/�����������)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
  {
    //������������, ��� ������� ��
    unsigned int index_df;
    switch (i)
    {
    case 0:
      {
       index_df = RANG_DF1_OUT;
        break;
      }
    case 1:
      {
        index_df = RANG_DF2_OUT;
        break;
      }
    case 2:
      {
        index_df = RANG_DF3_OUT;
        break;
      }
    case 3:
      {
        index_df = RANG_DF4_OUT;
        break;
      }
    case 4:
      {
        index_df = RANG_DF5_OUT;
        break;
      }
    case 5:
      {
        index_df = RANG_DF6_OUT;
        break;
      }
    case 6:
      {
        index_df = RANG_DF7_OUT;
        break;
      }
    case 7:
      {
        index_df = RANG_DF8_OUT;
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(44);
        break;
      }
    }
      
    if ((state_df & (1 << i)) != 0 )
    {
      /*
      �� ������� ����� � ��������
      ��� ����� ���, �� ��������� �������� ���� ���� ������� �� ����� ������ ���� - 
      ����������, �� �� ��� ���������� �� 
      */     
      if ((source_blk_df & (1<< i)) == 0 ) _SET_BIT(p_active_functions, index_df);
      else _CLEAR_BIT(p_active_functions, index_df);
    }
    else
    {
      _CLEAR_BIT(p_active_functions, index_df);
    }
  }
}
/*****************************************************/

/*****************************************************/
//����������� ������������� ������ - �� ����������� ���� ������������� �������������� �������
/*****************************************************/
inline void dt_handler(unsigned int *p_active_functions)
{
  /*
  ��������� ���� ������������ ������ ������� � state_defined_triggers
  ������� ������������ ������� � source_set_dt
  ������� �������� ������� � source_reset_dt
  */
  unsigned int state_defined_triggers = 0, source_set_dt = 0, source_reset_dt = 0;
  for (unsigned int i = 0; i < NUMBER_DEFINED_TRIGGERS/*current_settings_prt.number_defined_dt*/; i++)
  {
    unsigned int number_byte_set, number_bit_set, number_byte_reset, number_bit_reset;
    unsigned int index_dt;
    switch (i)
    {
    case 0:
      {
        number_byte_set = RANG_DT1_SET >> 5;
        number_bit_set = RANG_DT1_SET & 0x1f;

        number_byte_reset = RANG_DT1_RESET >> 5;
        number_bit_reset = RANG_DT1_RESET & 0x1f;
        
        index_dt = RANG_DT1_OUT;
        
        break;
      }
    case 1:
      {
        number_byte_set = RANG_DT2_SET >> 5;
        number_bit_set = RANG_DT2_SET & 0x1f;

        number_byte_reset = RANG_DT2_RESET >> 5;
        number_bit_reset = RANG_DT2_RESET & 0x1f;
        
        index_dt = RANG_DT2_OUT;
        
        break;
      }
    case 2:
      {
        number_byte_set = RANG_DT3_SET >> 5;
        number_bit_set = RANG_DT3_SET & 0x1f;

        number_byte_reset = RANG_DT3_RESET >> 5;
        number_bit_reset = RANG_DT3_RESET & 0x1f;
        
        index_dt = RANG_DT3_OUT;
        
        break;
      }
    case 3:
      {
        number_byte_set = RANG_DT4_SET >> 5;
        number_bit_set = RANG_DT4_SET & 0x1f;

        number_byte_reset = RANG_DT4_RESET >> 5;
        number_bit_reset = RANG_DT4_RESET & 0x1f;
        
        index_dt = RANG_DT4_OUT;
        
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(55);
        break;
      }
    }

    state_defined_triggers |= ( (p_active_functions[index_dt >> 5] & ( 1 << (index_dt & 0x1f) ) ) >> (index_dt & 0x1f) ) << i;
    /***
    ������� ������������ � �������� ��
    ***/
    source_set_dt   |= ((p_active_functions[number_byte_set  ] & (1 << number_bit_set  ) ) >> number_bit_set   ) << i;
    source_reset_dt |= ((p_active_functions[number_byte_reset] & (1 << number_bit_reset) ) >> number_bit_reset ) << i;
    /***/
  }
  
  //���������, �� ��������������/���������� ���������� ������ ����� ��� �������� �������-�������
  for (unsigned int i = 0; i < NUMBER_DEFINED_TRIGGERS/*current_settings_prt.number_defined_dt*/; i++)
  {
    if (
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 6] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 7] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 8] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 9] !=0)
       )
    {
      //�������, ���� ������� ��������� �� ������� ������ �������
      if(
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i    ] & p_active_functions[0]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 1] & p_active_functions[1]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 2] & p_active_functions[2]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 3] & p_active_functions[3]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 4] & p_active_functions[4]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 5] & p_active_functions[5]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 6] & p_active_functions[6]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 7] & p_active_functions[7]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 8] & p_active_functions[8]) != 0) ||
         (( current_settings_prt.ranguvannja_set_dt_source_plus[N_BIG*i + 9] & p_active_functions[9]) != 0)
        )
      {
        source_set_dt |= (1 << i);
      }
    }

    if (
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 6] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 7] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 8] !=0) ||
        (current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 9] !=0)
       )
    {
      //�������, ���� ������� ��������� �� ������� ��������� �������
      if(
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i    ] & ((unsigned int)(~p_active_functions[0])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 1] & ((unsigned int)(~p_active_functions[1])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 2] & ((unsigned int)(~p_active_functions[2])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 3] & ((unsigned int)(~p_active_functions[3])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 4] & ((unsigned int)(~p_active_functions[4])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 5] & ((unsigned int)(~p_active_functions[5])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 6] & ((unsigned int)(~p_active_functions[6])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 7] & ((unsigned int)(~p_active_functions[7])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 8] & ((unsigned int)(~p_active_functions[8])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_set_dt_source_minus[N_BIG*i + 9] & ((unsigned int)(~p_active_functions[9])) ) != 0 )
        )
      {
        source_set_dt |= (1<< i);
      }
    }

    if (
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 6] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 7] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 8] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 9] !=0)
       )
    {
      //�������, ���� ������� ��������� �� ������� ������ �������
      if(
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i    ] & p_active_functions[0]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 1] & p_active_functions[1]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 2] & p_active_functions[2]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 3] & p_active_functions[3]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 4] & p_active_functions[4]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 5] & p_active_functions[5]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 6] & p_active_functions[6]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 7] & p_active_functions[7]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 8] & p_active_functions[8]) != 0) ||
         (( current_settings_prt.ranguvannja_reset_dt_source_plus[N_BIG*i + 9] & p_active_functions[9]) != 0)
        )
      {
        source_reset_dt |= (1 << i);
      }
    }

    if (
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i    ] !=0) || 
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 1] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 2] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 3] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 4] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 5] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 6] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 7] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 8] !=0) ||
        (current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 9] !=0)
       )
    {
      //�������, ���� ������� ��������� �� ������� ��������� �������
      if(
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i    ] & ((unsigned int)(~p_active_functions[0])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 1] & ((unsigned int)(~p_active_functions[1])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 2] & ((unsigned int)(~p_active_functions[2])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 3] & ((unsigned int)(~p_active_functions[3])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 4] & ((unsigned int)(~p_active_functions[4])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 5] & ((unsigned int)(~p_active_functions[5])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 6] & ((unsigned int)(~p_active_functions[6])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 7] & ((unsigned int)(~p_active_functions[7])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 8] & ((unsigned int)(~p_active_functions[8])) ) != 0 ) ||
         ( ( current_settings_prt.ranguvannja_reset_dt_source_minus[N_BIG*i + 9] & ((unsigned int)(~p_active_functions[9])) ) != 0 )
        )
      {
        source_reset_dt |= (1<< i);
      }
    }

    //��������� � ������ ������� ����� ������ ������������� ������ (������������ �� ��������)
    if ((source_set_dt   & (1 << i)) != 0) state_defined_triggers |= (1 << i);
    if ((source_reset_dt & (1 << i)) != 0) state_defined_triggers &= (unsigned int)(~(1 << i));
  }

  //������������, ��� ������� �� � ����� �������, �� ����� ������ ��������������
  /*
  ��� ���� � ��������� �� ��'���� � ����, � ������� �������, �� � ������� �� �������������
  ����� p_active_functions � ����� �� �� ���������� ��� �������� ������� ��-��, ���� �� ���� ��-�
  ������ ���� �������� ������������/��������, ��� �������� ������������/�������� ���� ���� �������� �������� ��, � �� ��,
  �� ����� ��������������. � �������� � �� ������������ �������� � �����
  p_active_functions, �� ��������� ����� ����� ����, �� ��� �� ������ ��'������� ������������ ��������
  � ����������� �� ����� ���'����� (���� ������ ������ � ����� � ������ ������������/��������)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
  {
    //������������, ��� ������� ��
    unsigned int index_dt;
    switch (i)
    {
    case 0:
      {
       index_dt = RANG_DT1_OUT;
        break;
      }
    case 1:
      {
       index_dt = RANG_DT2_OUT;
        break;
      }
    case 2:
      {
       index_dt = RANG_DT3_OUT;
        break;
      }
    case 3:
      {
       index_dt = RANG_DT4_OUT;
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(56);
        break;
      }
    }
      
    if ((state_defined_triggers & (1 << i)) != 0 ) _SET_BIT(p_active_functions, index_dt);
    else _CLEAR_BIT(p_active_functions, index_dt);
  }
}
/*****************************************************/

/*****************************************************/
//����������� ������������ "�"
/*****************************************************/
inline void d_and_handler(unsigned int *p_active_functions)
{
  unsigned int state_defined_and = 0;

  //��������� ���� ��� ������������ "�" (�� ����������� ���� �� �� � �������� �����)
  for (unsigned int i = 0; i < NUMBER_DEFINED_AND/*current_settings_prt.number_defined_and*/; i++)
  {
    if (
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 0] & p_active_functions[0]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 0]) && 
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 1] & p_active_functions[1]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 1]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 2] & p_active_functions[2]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 2]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 3] & p_active_functions[3]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 3]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 4] & p_active_functions[4]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 4]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 5] & p_active_functions[5]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 5]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 6] & p_active_functions[6]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 6]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 7] & p_active_functions[7]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 7]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 8] & p_active_functions[8]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 8]) &&
        ((current_settings_prt.ranguvannja_d_and[N_BIG*i + 9] & p_active_functions[9]) == current_settings_prt.ranguvannja_d_and[N_BIG*i + 9])
       )
    {
      state_defined_and |= (1 << i);
    }
  }

  //������������, ��� ������� ���������� "�" � ����� �������, �� ����� ������ ��������������
  /*
  ��� ���� � ��������� �� ��'���� � ����, � ������� �������, �� � ������� �� �������������
  ����� p_active_functions � ����� �� �� ���������� ��� �������� ������ �-"�", ���� �� ���� �-"�"
  ������ ���� �������� , ��� �������� ���� ���� �������� �������� �-"�", � �� ��,
  �� ����� ��������������. � �������� �� ������������ �������� � �����
  p_active_functions, �� ��������� ����� ����� ����, �� ��� �� ������ ��'������� ������������ ��������
  � ����������� �� ����� ���'����� (���� ������ ������ � ����� � ������ ������������/��������)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_AND; i++)
  {
    //������������, ��� ������� �-"�"
    unsigned int index_d_and = RANG_D_AND1 + i;
      
    if ((state_defined_and & (1 << i)) != 0 ) _SET_BIT(p_active_functions, index_d_and);
    else _CLEAR_BIT(p_active_functions, index_d_and);
  }
}
/*****************************************************/

/*****************************************************/
//����������� ������������ "���"
/*****************************************************/
inline void d_or_handler(unsigned int *p_active_functions)
{
  unsigned int state_defined_or = 0;

  //��������� ���� ��� ������������ "���" (�� ����������� ���� �� �� � �������� �����)
  for (unsigned int i = 0; i < NUMBER_DEFINED_OR/*current_settings_prt.number_defined_or*/; i++)
  {
    if (
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 0] & p_active_functions[0]) != 0) || 
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 1] & p_active_functions[1]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 2] & p_active_functions[2]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 3] & p_active_functions[3]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 4] & p_active_functions[4]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 5] & p_active_functions[5]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 6] & p_active_functions[6]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 7] & p_active_functions[7]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 8] & p_active_functions[8]) != 0) ||
        ((current_settings_prt.ranguvannja_d_or[N_BIG*i + 9] & p_active_functions[9]) != 0)
       )
    {
      state_defined_or |= (1 << i);
    }
  }

  //������������, ��� ������� ���������� "���" � ����� �������, �� ����� ������ ��������������
  /*
  ��� ���� � ��������� �� ��'���� � ����, � ������� �������, �� � ������� �� �������������
  ����� p_active_functions � ����� �� �� ���������� ��� �������� ������ �-"���", ���� �� ���� �-"���"
  ������ ���� �������� , ��� �������� ���� ���� �������� �������� �-"���", � �� ��,
  �� ����� ��������������. � �������� �� ������������ �������� � �����
  p_active_functions, �� ��������� ����� ����� ����, �� ��� �� ������ ��'������� ������������ ��������
  � ����������� �� ����� ���'����� (���� ������ ������ � ����� � ������ ������������/��������)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_OR; i++)
  {
    //������������, ��� ������� �-"���"
    unsigned int index_d_or = RANG_D_OR1 + i;
      
    if ((state_defined_or & (1 << i)) != 0 ) _SET_BIT(p_active_functions, index_d_or);
    else _CLEAR_BIT(p_active_functions, index_d_or);
  }
}
/*****************************************************/

/*****************************************************/
//����������� ������������ "����.���"
/*****************************************************/
inline void d_xor_handler(unsigned int *p_active_functions)
{
  unsigned int state_defined_xor = 0;

  //��������� ���� ��� ������������ "����.���" (�� ����������� ���� �� �� � �������� �����)
  for (unsigned int i = 0; i < NUMBER_DEFINED_XOR/*current_settings_prt.number_defined_xor*/; i++)
  {
    unsigned int temp_array[N_BIG];
    temp_array[0] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 0] & p_active_functions[0];
    temp_array[1] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 1] & p_active_functions[1];
    temp_array[2] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 2] & p_active_functions[2];
    temp_array[3] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 3] & p_active_functions[3];
    temp_array[4] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 4] & p_active_functions[4];
    temp_array[5] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 5] & p_active_functions[5];
    temp_array[6] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 6] & p_active_functions[6];
    temp_array[7] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 7] & p_active_functions[7];
    temp_array[8] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 8] & p_active_functions[8];
    temp_array[9] = current_settings_prt.ranguvannja_d_xor[N_BIG*i + 9] & p_active_functions[9];
    
    if (
        (temp_array[0] != 0) || 
        (temp_array[1] != 0) ||
        (temp_array[2] != 0) ||
        (temp_array[3] != 0) ||
        (temp_array[4] != 0) ||
        (temp_array[5] != 0) ||
        (temp_array[6] != 0) ||
        (temp_array[7] != 0) ||
        (temp_array[8] != 0) ||
        (temp_array[9] != 0)
       )
    {
      unsigned int signals = 0;
      for (unsigned int j = 0; j < N_BIG; j++)
      {
        if (temp_array[j] == 0) continue; 
        else
        {
          for (unsigned int k = 0; k < 32; k++)
          {
            if ((temp_array[j] & (1 << k)) != 0) 
            {
              signals++;
              if (signals > 1) break;
            }
          }
          if (signals > 1) break;
        }
      }
      if (signals == 1) state_defined_xor |= (1 << i);
    }
  }

  //������������, ��� ������� ���������� "����.���" � ����� �������, �� ����� ������ ��������������
  /*
  ��� ���� � ��������� �� ��'���� � ����, � ������� �������, �� � ������� �� �������������
  ����� p_active_functions � ����� �� �� ���������� ��� �������� ������ �-"����.���", ���� �� ���� �-"����.���"
  ������ ���� �������� , ��� �������� ���� ���� �������� �������� �-"����.���", � �� ��,
  �� ����� ��������������. � �������� �� ������������ �������� � �����
  p_active_functions, �� ��������� ����� ����� ����, �� ��� �� ������ ��'������� ������������ ��������
  � ����������� �� ����� ���'����� (���� ������ ������ � ����� � ������ ������������/��������)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_XOR; i++)
  {
    //������������, ��� ������� �-"����.���"
    unsigned int index_d_xor = RANG_D_XOR1 + i;
      
    if ((state_defined_xor & (1 << i)) != 0 ) _SET_BIT(p_active_functions, index_d_xor);
    else _CLEAR_BIT(p_active_functions, index_d_xor);
  }
}
/*****************************************************/

/*****************************************************/
//����������� ������������ "��"
/*****************************************************/
inline void d_not_handler(unsigned int *p_active_functions)
{
  unsigned int state_defined_not = 0;

  //��������� ���� ��� ������������ "��" (�� ����������� ���� �� �� � �������� �����)
  for (unsigned int i = 0; i < NUMBER_DEFINED_NOT/*current_settings_prt.number_defined_not*/; i++)
  {
    if (
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 0] & p_active_functions[0]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 1] & p_active_functions[1]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 2] & p_active_functions[2]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 3] & p_active_functions[3]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 4] & p_active_functions[4]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 5] & p_active_functions[5]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 6] & p_active_functions[6]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 7] & p_active_functions[7]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 8] & p_active_functions[8]) == 0) &&
        ((current_settings_prt.ranguvannja_d_not[N_BIG*i + 9] & p_active_functions[9]) == 0)
       )
    {
      state_defined_not |= (1 << i);
    }
  }

  //������������, ��� ������� ���������� "��" � ����� �������, �� ����� ������ ��������������
  /*
  ��� ���� � ��������� �� ��'���� � ����, � ������� �������, �� � ������� �� �������������
  ����� p_active_functions � ����� �� �� ���������� ��� �������� ������ �-"��", ���� �� ���� �-"��"
  ������ ���� �������� , ��� �������� ���� ���� �������� �������� �-"��", � �� ��,
  �� ����� ��������������. � �������� �� ������������ �������� � �����
  p_active_functions, �� ��������� ����� ����� ����, �� ��� �� ������ ��'������� ������������ ��������
  � ����������� �� ����� ���'����� (���� ������ ������ � ����� � ������ ������������/��������)
  */
  for (unsigned int i = 0; i < NUMBER_DEFINED_NOT; i++)
  {
    //������������, ��� ������� �-"��"
    unsigned int index_d_not = RANG_D_NOT1 + i;
      
    if ((state_defined_not & (1 << i)) != 0 ) _SET_BIT(p_active_functions, index_d_not);
    else _CLEAR_BIT(p_active_functions, index_d_not);
  }
}
/*****************************************************/

/*****************************************************/
//����������� ������������� �������
/*****************************************************/
inline void tf_handler(unsigned int *p_previous_active_functions, unsigned int *p_active_functions)
{
  for (size_t i = 0; i < NUMBER_TRANSFER_FUNCTIONS; i++)
  {
    uint32_t value = current_settings_prt.ranguvannja_tf[i];
    uint32_t value_input = value & 0xffff;
    if (value_input > 0)
    {
      value_input--;
      if (value_input < NUMBER_TOTAL_SIGNAL_FOR_RANG)
      {
        if (_CHECK_SET_BIT(p_previous_active_functions, value_input) != 0)
        {
          uint32_t value_output = (value >> 16) & 0xffff;
          if (value_output > 0)
          {
            value_output--;
            if (value_output < NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL)
            {
              _SET_BIT(p_active_functions, small_big_rang[value_output]);
            }
            else
            {
              //³������� ����������� �������, ���� ����� ��� �� ����������������
              total_error_sw_fixed(102);
            }
          }
        }
      }
      else
      {
        //³������� ����������� �������, ���� ����� ��� �� ����������������
        total_error_sw_fixed(101);
      }
    }
  }
}
/*****************************************************/

/*****************************************************/
//������������� ������ ��������  ��� ������� ���2 (����������� �������)
/*
-------------------------------------------------
�(c) = K*T�/( ((I/I�)^alpha) - 1 )
-------------------------------------------------
*/
/*****************************************************/
inline int timeout_dependent_general(unsigned int i, unsigned int setpoint_mtz_2, int timeout_mtz_2, int type_mtz2_tmp)
{
  int timeout_result = 0;
  
  if (
      (type_mtz2_tmp >= TYPE_MTZ_DEPENDENT_A) &&
      (type_mtz2_tmp <= TYPE_MTZ_DEPENDENT_RTV_I)
     )   
  {
    unsigned int Iust = setpoint_mtz_2;
    if (i > Iust)
    {
      register float timeout = (((float)timeout_mtz_2)/1000.0f);
      register float timeout_dependent = 0;
      
      if (
          (type_mtz2_tmp >= TYPE_MTZ_DEPENDENT_A) &&
          (type_mtz2_tmp <= TYPE_MTZ_DEPENDENT_C)
         )   
      {
        register float K;
        register float alpha;

        switch (type_mtz2_tmp)
        {
          case TYPE_MTZ_DEPENDENT_A:
          {
            K = 0.14f;
            alpha = 0.02f;
            break;
          }
        case TYPE_MTZ_DEPENDENT_B:
          {
            K = 13.5f;
            alpha = 1.0f;
            break;
          }
        case TYPE_MTZ_DEPENDENT_C:
          {
            K = 80.0f;
            alpha = 2.0f;
            break;
          }
        default:
          {
            //���������� ����� ����� �� ���� � ����
            total_error_sw_fixed(42);
          }
        }
    
        register float I_div_Iusy = ((float)i)/((float)Iust);
        register float rising_to_power = powf(I_div_Iusy, alpha);
        if (
            (isnan(rising_to_power) != 0) || 
            (isinf(rising_to_power) != 0) ||
            (rising_to_power <= 1)
          )
        {
          //���������� ����� ����� �� ���� � ����
          total_error_sw_fixed(57);
        }
  
        timeout_dependent = K*timeout/(rising_to_power - 1);
      }
      else if (
               (type_mtz2_tmp >= TYPE_MTZ_DEPENDENT_RT_80) &&
               (type_mtz2_tmp <= TYPE_MTZ_DEPENDENT_RTV_I)
              )   
      {
        register float I_div_Iusy = ((float)i)/((float)Iust);
        I_div_Iusy = I_div_Iusy - 1.0f;

        register float K;
        register float alpha;

        switch (type_mtz2_tmp)
        {
        case TYPE_MTZ_DEPENDENT_RT_80:
          {
            K = 20.0f;
            alpha = 1.8f;
          
            I_div_Iusy /= 6.0f;
            break;
          }
        case TYPE_MTZ_DEPENDENT_RTV_I:
          {
            K = 30.0f;
            alpha = 3.0f;
            break;
          } 
        default:
          {
            //���������� ����� ����� �� ���� � ����
            total_error_sw_fixed(87);
          }
        }
      
        register float rising_to_power = powf(I_div_Iusy, alpha);
        if (
            (isnan(rising_to_power) != 0) || 
            (isinf(rising_to_power) != 0) ||
            (rising_to_power <= 0)
           )
        {
          //���������� ����� ����� �� ���� � ����
          total_error_sw_fixed(86);
        }
      
        timeout_dependent = 1.0f/(K*rising_to_power)+ timeout;
      }

      int timeout_dependent_int = (int)timeout_dependent;
      if (timeout_dependent_int > (TIMEOUT_MTZ2_MAX/1000)) timeout_dependent = (TIMEOUT_MTZ2_MAX/1000);
      else if (timeout_dependent_int < 0) timeout_dependent = 0;
    
      timeout_result = (int)(timeout_dependent*1000.0f);
    }
    else timeout_result = TIMEOUT_MTZ2_MAX;
  }
  
  return timeout_result;
}
/*****************************************************/

/*****************************************************/
// ���
/*****************************************************/
inline void mtz_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
  unsigned int tmp_value;
  
  unsigned int po_mtz_x;
  unsigned int direction_ABC_tmp;
  unsigned int po_mtzn_x_vpered_setpoint;
  unsigned int po_mtzn_x_nazad_setpoint;
//  unsigned int po_block_u_mtzn_x_setpoint;
  unsigned int po_i_ncn_setpoint;
  unsigned int po_u_ncn_setpoint;
  unsigned int po_u_mtzpn_x_setpoint;
  unsigned int po_mtzpn_x_setpoint;
  
  /******������������� ����� ���������� ��� 4-� ��������*******/
  _Bool ctr_mtz_nespr_kil_napr = (current_settings_prt.control_mtz & CTR_MTZ_NESPR_KIL_NAPR) != 0; //������. ����. ���. (�)
  
  //�� I���
  po_i_ncn_setpoint = previous_state_mtz_po_incn ?
            i_nom_const * KOEF_POVERNENNJA_MTZ_I_DOWN / 100 :
            i_nom_const;
  
  previous_state_mtz_po_incn = ((measurement[IM_IA] <= po_i_ncn_setpoint)   &&
                                (measurement[IM_IB] <= po_i_ncn_setpoint) &&
                                (measurement[IM_IC] <= po_i_ncn_setpoint));
  
  //�� U���
  po_u_ncn_setpoint = previous_state_mtz_po_uncn ?
            u_f_nom_const * U_DOWN / 100 :
            u_f_nom_const;
  
  previous_state_mtz_po_uncn = ((measurement[IM_UA] <= po_u_ncn_setpoint) ||
                                (measurement[IM_UB] <= po_u_ncn_setpoint) ||
                                (measurement[IM_UC] <= po_u_ncn_setpoint));
  
  ctr_mtz_nespr_kil_napr = ctr_mtz_nespr_kil_napr && previous_state_mtz_po_incn && previous_state_mtz_po_uncn; //������������� ����� ���������� (_AND3)
  
  //������������� ����� ����������
  if (ctr_mtz_nespr_kil_napr)
    _SET_BIT(p_active_functions, RANG_NCN_MTZ);
  else
    _CLEAR_BIT(p_active_functions, RANG_NCN_MTZ);
  /******������������� ����� ���������� ��� 4-� ��������*******/
  
  /******�� U ����. �����***********************/
  //������� �� U ����. ����� � ����������� ����������
  unsigned int po_block_u_mtzn_x_setpoint = (_CHECK_SET_BIT(p_active_functions, RANG_PO_BLOCK_U_MTZN) == 0) ? PORIG_CHUTLYVOSTI_VOLTAGE : PORIG_CHUTLYVOSTI_VOLTAGE * U_DOWN / 100;
  
  //�� U ����. �����
  if (
      (measurement[IM_UAB] <= po_block_u_mtzn_x_setpoint) ||
      (measurement[IM_UBC] <= po_block_u_mtzn_x_setpoint) ||
      (measurement[IM_UCA] <= po_block_u_mtzn_x_setpoint)
     )
  {
    _SET_BIT(p_active_functions, RANG_PO_BLOCK_U_MTZN);
  }
  else
  {
    _CLEAR_BIT(p_active_functions, RANG_PO_BLOCK_U_MTZN);
  }
  /******�� U ����. �����***********************/

  for (int mtz_level = 0; mtz_level < NUMBER_LEVEL_MTZ; mtz_level++) {
    //��� �������
//    if (mtz_level == 0) {
//      mtz_level = 0;
//    } else if (mtz_level == 1) {
//      mtz_level = 1;
//    } else if (mtz_level == 2) {
//      mtz_level = 2;
//    } else if (mtz_level == 3) {
//      mtz_level = 3;
//    }
    
    //�
    /*��������� ��� ���*/
    tmp_value = (*type_mtz_arr[mtz_level] == 1)                                  << 0; //������������
    tmp_value |= (*type_mtz_arr[mtz_level] == 2)                                 << 1; //� ������
    tmp_value |= (*type_mtz_arr[mtz_level] == 0)                                 << 2; //�������
    tmp_value |= (
                  (mtz_level == 1)
                  && (*type_mtz_arr[mtz_level] >= TYPE_MTZ_DEPENDENT_A) //A, B, C (3-5)
                  && (*type_mtz_arr[mtz_level] <= TYPE_MTZ_DEPENDENT_RTV_I)
                 )                                                               << 3; //��������� (���� mtz_level == 1 (2-� ������� ���))
    
    /******�� ����***********************/
    //������� �� ���� � ������ �����������
    po_mtz_x = (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZ]) != 0) ?
            *(setpoint_mtz[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100 :
            *(setpoint_mtz[mtz_level] + number_group_stp);
    
    tmp_value |= ((measurement[IM_IA] >= po_mtz_x) ||
          (measurement[IM_IB] >= po_mtz_x) ||
          (measurement[IM_IC] >= po_mtz_x)) << 4; //�� ����
    /******�� ����***********************/
    
    //�
    tmp_value |= ((current_settings_prt.control_mtz & mtz_const_menu_settings_prt[mtz_level][CTR_MTZ]) != 0) << 5; //���� ���.
    //��
    tmp_value |= (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_BLOCK_MTZ]) == 0) << 6; //���������� ����
    //�
    tmp_value |= ((current_settings_prt.control_mtz & mtz_const_menu_settings_prt[mtz_level][CTR_MTZ_VPERED]) != 0) << 7; //�����: ���. ����
    tmp_value |= ((current_settings_prt.control_mtz & mtz_const_menu_settings_prt[mtz_level][CTR_MTZ_NAZAD]) != 0) << 8; //�����: ���. ���
    
    /******������ ����� ������/�����**********/
    //�������� �������������� ��� �,�,�
    direction_ABC_tmp = (sector_directional_mtz[mtz_level][PHASE_A_INDEX] == MTZ_VPERED) << 0; //�������� �������������� ���� � ������
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_B_INDEX] == MTZ_VPERED) << 1; //�������� �������������� ���� B ������
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_C_INDEX] == MTZ_VPERED) << 2; //�������� �������������� ���� C ������
    
    _OR3(direction_ABC_tmp, 0, direction_ABC_tmp, 1, direction_ABC_tmp, 2, direction_ABC_tmp, 3);
    
    //������ ����� ������
    if (_GET_OUTPUT_STATE(direction_ABC_tmp, 3))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_SECTOR_VPERED_MTZN]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_SECTOR_VPERED_MTZN]);
    
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_A_INDEX] == MTZ_NAZAD) << 4; //�������� �������������� ���� � �����
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_B_INDEX] == MTZ_NAZAD) << 5; //�������� �������������� ���� B �����
    direction_ABC_tmp |= (sector_directional_mtz[mtz_level][PHASE_C_INDEX] == MTZ_NAZAD) << 6; //�������� �������������� ���� C �����
    
    _OR3(direction_ABC_tmp, 4, direction_ABC_tmp, 5, direction_ABC_tmp, 6, direction_ABC_tmp, 7);
    
    //������ ����� �����
    if (_GET_OUTPUT_STATE(direction_ABC_tmp, 7))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_SECTOR_NAZAD_MTZN]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_SECTOR_NAZAD_MTZN]);
    
    //������� �� ����1 ����. � ������ �����������
    po_mtzn_x_vpered_setpoint = (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_VPERED]) != 0) ?
            *(setpoint_mtz_n_vpered[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100 :
            *(setpoint_mtz_n_vpered[mtz_level] + number_group_stp);
    
    direction_ABC_tmp |= (measurement[IM_IA] >= po_mtzn_x_vpered_setpoint) << 8; //���������� � �������� ���� �� ���� � (������)
    direction_ABC_tmp |= (measurement[IM_IB] >= po_mtzn_x_vpered_setpoint) << 9; //���������� � �������� ���� �� ���� B (������)
    direction_ABC_tmp |= (measurement[IM_IC] >= po_mtzn_x_vpered_setpoint) << 10; //���������� � �������� ���� �� ���� C (������)
    
    //������� �� ����1 ����. � ������ �����������
    po_mtzn_x_nazad_setpoint = (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_NAZAD]) != 0) ?
            *(setpoint_mtz_n_nazad[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100 :
            *(setpoint_mtz_n_nazad[mtz_level] + number_group_stp);
    
    direction_ABC_tmp |= (measurement[IM_IA] >= po_mtzn_x_nazad_setpoint) << 11; //���������� � �������� ���� �� ���� � (�����)
    direction_ABC_tmp |= (measurement[IM_IB] >= po_mtzn_x_nazad_setpoint) << 12; //���������� � �������� ���� �� ���� B (�����)
    direction_ABC_tmp |= (measurement[IM_IC] >= po_mtzn_x_nazad_setpoint) << 13; //���������� � �������� ���� �� ���� C (�����)
    
    _AND2(direction_ABC_tmp, 8, direction_ABC_tmp, 0, direction_ABC_tmp, 14);
    _AND2(direction_ABC_tmp, 9, direction_ABC_tmp, 1, direction_ABC_tmp, 15);
    _AND2(direction_ABC_tmp, 10, direction_ABC_tmp, 2, direction_ABC_tmp, 16);
    
    _AND2(direction_ABC_tmp, 11, direction_ABC_tmp, 4, direction_ABC_tmp, 17);
    _AND2(direction_ABC_tmp, 12, direction_ABC_tmp, 5, direction_ABC_tmp, 18);
    _AND2(direction_ABC_tmp, 13, direction_ABC_tmp, 6, direction_ABC_tmp, 19);
    
    _OR3(direction_ABC_tmp, 14, direction_ABC_tmp, 15, direction_ABC_tmp, 16, tmp_value, 12);
    _OR3(direction_ABC_tmp, 17, direction_ABC_tmp, 18, direction_ABC_tmp, 19, tmp_value, 13);
    /******������ ����� ������/�����**********/
    
//    /******�� U ����. �����***********************/
//    //������� �� U ����. ����� � ������ �����������
//    po_block_u_mtzn_x_setpoint = (_CHECK_SET_BIT(p_active_functions, RANG_PO_BLOCK_U_MTZN) != 0) ?
//           PORIG_CHUTLYVOSTI_VOLTAGE :
//           PORIG_CHUTLYVOSTI_VOLTAGE * U_DOWN / 100;
//    
//    tmp_value |= ((measurement[IM_UAB] <= po_block_u_mtzn_x_setpoint) ||
//                  (measurement[IM_UBC] <= po_block_u_mtzn_x_setpoint) ||
//                  (measurement[IM_UCA] <= po_block_u_mtzn_x_setpoint)) << 14; //�� U ����. �����
//    
//    //�� U ����. �����
//    if (_GET_OUTPUT_STATE(tmp_value, 14))
//      _SET_BIT(p_active_functions, RANG_PO_BLOCK_U_MTZN);
//    else
//      _CLEAR_BIT(p_active_functions, RANG_PO_BLOCK_U_MTZN);
//    /******�� U ����. �����***********************/
    tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_PO_BLOCK_U_MTZN) != 0) << 14;
    
    //������������� ����� ���������� ��� ������� ����
    tmp_value |= (
                   !(_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_VPERED]) != 0 ||
                     _CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_NAZAD])  != 0 ||
                     _CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZPN])     != 0)
                   &&
                   ctr_mtz_nespr_kil_napr
                 ) << 15;
    
    /******�� U ������***********************/
    po_u_mtzpn_x_setpoint = (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_U_MTZPN]) != 0) ?
            *(setpoint_mtz_U[mtz_level] + number_group_stp) * U_DOWN / 100:
            *(setpoint_mtz_U[mtz_level] + number_group_stp) ;
    
    tmp_value |= ((measurement[IM_UAB] <= po_u_mtzpn_x_setpoint) ||
                  (measurement[IM_UBC] <= po_u_mtzpn_x_setpoint) ||
                  (measurement[IM_UCA] <= po_u_mtzpn_x_setpoint)) << 16; //�� U ������
    
    //�� U ������
    if (_GET_OUTPUT_STATE(tmp_value, 16))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_U_MTZPN]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_U_MTZPN]);
    /******�� U ������***********************/
    
    /******�� ������***********************/
    po_mtzpn_x_setpoint = (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZPN]) != 0) ?
            *(setpoint_mtz_po_napruzi[mtz_level] + number_group_stp) * KOEF_POVERNENNJA_MTZ_I_UP / 100:
            *(setpoint_mtz_po_napruzi[mtz_level] + number_group_stp);
    
    tmp_value |= ((measurement[IM_IA] >= po_mtzpn_x_setpoint)   ||
                  (measurement[IM_IB] >= po_mtzpn_x_setpoint) ||
                  (measurement[IM_IC] >= po_mtzpn_x_setpoint)) << 17; //�� ������
    /******�� ������***********************/
    
    if (mtz_level == 1) { //������ ��� 2-�� �������
      //��
      tmp_value |= (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_BLOCK_USK_MTZ]) == 0) << 9; //���������� ��������� ��� 2
      //�
      tmp_value |= ((current_settings_prt.control_mtz & CTR_MTZ_2_PRYSKORENA) != 0) << 10; //���2 ����������
      //��
      tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_STATE_VV) != 0) << 18; //��������� ��
      //M
      tmp_value |= ((current_settings_prt.control_mtz & CTR_MTZ_2_PRYSKORENNJA) != 0) << 11; //��������� ���2 ���.
    }
    
    if (_GET_OUTPUT_STATE(tmp_value, 15)) { //���� ������������� ������������� ����� ���������� ��� ������� ����
      _CLEAR_STATE(tmp_value, 16); //������� �� U ������
    }
    
    _OR2_INVERTOR(tmp_value, 14, tmp_value, 15, tmp_value, 14);
    
    if (_CHECK_SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZ]) != 0) 
    {
      _SET_STATE(tmp_value, 19);
    } 
    else 
    {
      if (mtz_level == 1)
      {
        //������ ��� 2-�� ������� ��� ������������ 19-�� ������� ����� �����������
        //������ "���������" (tmp_value 3)
        if (_GET_OUTPUT_STATE(tmp_value, 14)) 
        {
          _OR3(tmp_value, 2, tmp_value, 3, tmp_value, 15, tmp_value, 19);
        }
        else 
        {
          _OR4(tmp_value, 0, tmp_value, 2, tmp_value, 3, tmp_value, 15, tmp_value, 19);
        }
      }
      else 
      {
        if (_GET_OUTPUT_STATE(tmp_value, 14))
        {
          _OR2(tmp_value, 2, tmp_value, 15, tmp_value, 19);
        } 
        else
        {
          _OR3(tmp_value, 0, tmp_value, 2, tmp_value, 15, tmp_value, 19);
        }
      }
    }
    
    _AND2(tmp_value, 5, tmp_value, 6, tmp_value, 20);
    
    //�� ����
    _AND3(tmp_value, 19, tmp_value, 4, tmp_value, 20, tmp_value, 21);
    if (_GET_OUTPUT_STATE(tmp_value, 21))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZ]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZ]);
    
    //�� ����� ������
    _AND5(tmp_value, 0, tmp_value, 20, tmp_value, 7, tmp_value, 12, tmp_value, 14, tmp_value, 22);
    if (_GET_OUTPUT_STATE(tmp_value, 22))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_VPERED]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_VPERED]);
    
    //�� ����� �����
    _AND5(tmp_value, 0, tmp_value, 20, tmp_value, 8, tmp_value, 13, tmp_value, 14, tmp_value, 23);
    if (_GET_OUTPUT_STATE(tmp_value, 23)) 
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_NAZAD]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZN_NAZAD]);
    
    //�� ������
    _AND4(tmp_value, 1, tmp_value, 20, tmp_value, 16, tmp_value, 17, tmp_value, 24);
    if (_GET_OUTPUT_STATE(tmp_value, 24))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZPN]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_PO_MTZPN]);
    
    if (mtz_level != 1) { //��� ���� �������� ����� 2-��
      _TIMER_T_0(mtz_tmr_const[mtz_level][INDEX_TIMER_MTZ], *(timeout_mtz[mtz_level] + number_group_stp), tmp_value, 21, tmp_value, 25);
      _TIMER_T_0(mtz_tmr_const[mtz_level][INDEX_TIMER_MTZ_N_VPERED], *(timeout_mtz_n_vpered[mtz_level] + number_group_stp), tmp_value, 22, tmp_value, 26);
      _TIMER_T_0(mtz_tmr_const[mtz_level][INDEX_TIMER_MTZ_N_NAZAD], *(timeout_mtz_n_nazad[mtz_level] + number_group_stp), tmp_value, 23, tmp_value, 27);
      _TIMER_T_0(mtz_tmr_const[mtz_level][INDEX_TIMER_MTZ_PO_NAPRUZI], *(timeout_mtz_po_napruzi[mtz_level] + number_group_stp), tmp_value, 24, tmp_value, 28);
      _OR4(tmp_value, 25, tmp_value, 26, tmp_value, 27, tmp_value, 28, tmp_value, 31);
    } else {
      unsigned int tmp = 0;
      _AND2(tmp_value, 18, tmp_value, 11, tmp, 0);
      _TIMER_IMPULSE(INDEX_TIMER_MTZ2_VVID_PR, current_settings_prt.timeout_mtz_2_vvid_pr[number_group_stp], temp_states_for_mtz, 0, tmp, 0, tmp, 1);
      _OR2(tmp, 1, tmp_value, 10, tmp, 2);
      _AND2(tmp_value, 9, tmp, 2, tmp, 3);
      _INVERTOR(tmp, 3, tmp, 4);
      _INVERTOR(tmp_value, 3, tmp, 23); /*��������� ������� � ��������� ��������*/
      _AND3(tmp, 4, tmp_value, 3, tmp_value, 21, tmp, 5);
      _AND2(tmp, 3, tmp_value, 21, tmp, 6);
      _AND3(tmp, 4, tmp_value, 21, tmp, 23, tmp, 7); /*������������ ������� � ��������� �������*/
      _AND2(tmp, 4, tmp_value, 22, tmp, 8);
      _AND2(tmp, 3, tmp_value, 22, tmp, 9);
      _AND2(tmp, 4, tmp_value, 23, tmp, 10);
      _AND2(tmp, 3, tmp_value, 23, tmp, 11);
      _AND2(tmp, 4, tmp_value, 24, tmp, 12);
      _AND2(tmp, 3, tmp_value, 24, tmp, 13);
      
      unsigned int i_max = measurement[IM_IA];
      if (i_max < measurement[IM_IB]) i_max = measurement[IM_IB];
      if (i_max < measurement[IM_IC]) i_max = measurement[IM_IC];
      _TIMER_T_0_LOCK(INDEX_TIMER_MTZ2_DEPENDENT, timeout_dependent_general(i_max, current_settings_prt.setpoint_mtz_2[number_group_stp], current_settings_prt.timeout_mtz_2[number_group_stp], current_settings_prt.type_mtz2), tmp, 5, p_global_trigger_state_mtz2, 0);
      _TIMER_T_0(INDEX_TIMER_MTZ2_PR, current_settings_prt.timeout_mtz_2_pr[number_group_stp], tmp, 6, tmp, 15);
      _TIMER_T_0(INDEX_TIMER_MTZ2, current_settings_prt.timeout_mtz_2[number_group_stp], tmp, 7, tmp, 16);
      _TIMER_T_0(INDEX_TIMER_MTZ2_N_VPERED, current_settings_prt.timeout_mtz_2_n_vpered[number_group_stp], tmp, 8, tmp, 17);
      _TIMER_T_0(INDEX_TIMER_MTZ2_N_VPERED_PR, current_settings_prt.timeout_mtz_2_n_vpered_pr[number_group_stp], tmp, 9, tmp, 18);
      _TIMER_T_0(INDEX_TIMER_MTZ2_N_NAZAD, current_settings_prt.timeout_mtz_2_n_nazad[number_group_stp], tmp, 10, tmp, 19);
      _TIMER_T_0(INDEX_TIMER_MTZ2_N_NAZAD_PR, current_settings_prt.timeout_mtz_2_n_nazad_pr[number_group_stp], tmp, 11, tmp, 20);
      _TIMER_T_0(INDEX_TIMER_MTZ2_PO_NAPRUZI, current_settings_prt.timeout_mtz_2_po_napruzi[number_group_stp], tmp, 12, tmp, 21);
      _TIMER_T_0(INDEX_TIMER_MTZ2_PO_NAPRUZI_PR, current_settings_prt.timeout_mtz_2_po_napruzi_pr[number_group_stp], tmp, 13, tmp, 22);
      
      _OR6(p_global_trigger_state_mtz2, 0, tmp, 15, tmp, 16, tmp, 17, tmp, 18, tmp, 19, tmp_value, 29);
      _OR3(tmp, 20, tmp, 21, tmp, 22, tmp_value, 30);
      _OR2(tmp_value, 29, tmp_value, 30, tmp_value, 31);
    }
    
    //����.����
    if (_GET_OUTPUT_STATE(tmp_value, 31))
      _SET_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_MTZ]);
    else
      _CLEAR_BIT(p_active_functions, mtz_settings_prt[mtz_level][RANG_MTZ]);
  }
}
/*****************************************************/

/*****************************************************/
// ���
/*****************************************************/
inline void zdz_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
  
  uint32_t control_zdz_tmp = current_settings_prt.control_zdz;

#if (                                   \
     (MODYFIKACIA_VERSII_PZ == 0) ||    \
     (MODYFIKACIA_VERSII_PZ == 3)       \
    )   

  static uint32_t test;
  static uint32_t swiched_on_OVD;
  static uint32_t new_OVD;

  uint32_t swiched_on_OVD_tmp = (control_zdz_tmp & ((1 << CTR_ZDZ_OVD1_STATE_BIT) | (1 << CTR_ZDZ_OVD2_STATE_BIT) | (1 << CTR_ZDZ_OVD3_STATE_BIT))) >> CTR_ZDZ_OVD1_STATE_BIT;

  new_OVD |= (swiched_on_OVD ^ swiched_on_OVD_tmp) & swiched_on_OVD_tmp;
  swiched_on_OVD = swiched_on_OVD_tmp;

  /***
  ��������, �� �� ��������� ����� � ����� �� ����� �� ������� ���� ���
  ***/
  {
    uint32_t temp_value = zdz_ovd_diagnostyka & (uint32_t)(~swiched_on_OVD);
    if (temp_value)
    {
      if (temp_value & (1 << 0))
      {
        zdz_ovd_diagnostyka &= (uint32_t)(~(1 << 0));
      
        _SET_BIT(clear_diagnostyka, TEST_OVD1);
      }
    
      if (temp_value & (1 << 1))
      {
        zdz_ovd_diagnostyka &= (uint32_t)(~(1 << 1));
      
        _SET_BIT(clear_diagnostyka, TEST_OVD2);
      }

      if (temp_value & (1 << 2))
      {
        zdz_ovd_diagnostyka &= (uint32_t)(~(1 << 2));
      
        _SET_BIT(clear_diagnostyka, TEST_OVD3);
      }
    }
  }
  /***/
   
  //������ ���� � ������������
  uint32_t light = (_DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD26_DD29) >> 12) & 0x7;

  /***
  ��� ��������, ���� ������� �� ���������� ������� �������
  ***/
  if (test != 0)
  {
    //���� ����������
    zdz_ovd_diagnostyka = (light ^ test) & test;
    
    if (zdz_ovd_diagnostyka & (1 << 0)) _SET_BIT(set_diagnostyka, TEST_OVD1);
    else _SET_BIT(clear_diagnostyka, TEST_OVD1);
      
    if (zdz_ovd_diagnostyka & (1 << 1)) _SET_BIT(set_diagnostyka, TEST_OVD2);
    else _SET_BIT(clear_diagnostyka, TEST_OVD2);
      
    if (zdz_ovd_diagnostyka & (1 << 2)) _SET_BIT(set_diagnostyka, TEST_OVD3);
    else _SET_BIT(clear_diagnostyka, TEST_OVD3);
      
    //���, �� ����� ������������ �� ���� �������������, �� ��� ����� ��  ���� �� ��������
    light &= (uint32_t)(~test);
    
    //������� ����
    test = 0;
  }
  
  //³��� ���� �� ����������� ��������� ����� ���
  delta_time_test += DELTA_TIME_FOR_TIMERS;
  
  //Գ������ ������� ������ ����� ��� ���
  if (
      (light == 0)
      &&  
      (
       (new_OVD) ||
       ( delta_time_test >= PERIOD_ZDZ_TEST)
      )   
     )   
  {
    new_OVD = 0; /*������� �������� �������� � ������ ������ ������*/
    delta_time_test = 0;
    
    //�������� ����
    test = swiched_on_OVD & 0x7;
  }

  if (test != 0) _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD28) = (1 << 8) | ((test & 0xf) << 12);
  else _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD28) = (((current_settings_prt.zdz_ovd_porig + 1) & 0xf) << 8);
  /***/

#endif  

  uint32_t logic_zdz_0 = 0;

  logic_zdz_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_PUSK_ZDZ_VID_DV) != 0) << 0; //���� ��� �� ��

  logic_zdz_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_ZDZ) == 0) << 1; //����. ���
  
  _AND2(control_zdz_tmp, CTR_ZDZ_STATE_BIT, logic_zdz_0, 1, logic_zdz_0, 2);
  _AND2(logic_zdz_0, 2, logic_zdz_0, 0, logic_zdz_0, 3);
  //"��.��� �� ��"
  if (_GET_OUTPUT_STATE(logic_zdz_0, 3))
    _SET_BIT(p_active_functions, RANG_LIGHT_ZDZ_FROM_DV);
  else
    _CLEAR_BIT(p_active_functions, RANG_LIGHT_ZDZ_FROM_DV);

#if (                                   \
     (MODYFIKACIA_VERSII_PZ == 0) ||    \
     (MODYFIKACIA_VERSII_PZ == 3)       \
    )   
  uint32_t zdz_ovd_diagnostyka_inv = (uint32_t)(~zdz_ovd_diagnostyka);
  _AND4(logic_zdz_0, 2, light, 0, zdz_ovd_diagnostyka_inv, 0, control_zdz_tmp, CTR_ZDZ_OVD1_STATE_BIT, logic_zdz_0, 4);
  //"��.��� �� ���1"
  if (_GET_OUTPUT_STATE(logic_zdz_0, 4))
    _SET_BIT(p_active_functions, RANG_LIGHT_ZDZ_FROM_OVD1);
  else
    _CLEAR_BIT(p_active_functions, RANG_LIGHT_ZDZ_FROM_OVD1);

  _AND4(logic_zdz_0, 2, light, 1, zdz_ovd_diagnostyka_inv, 1, control_zdz_tmp, CTR_ZDZ_OVD2_STATE_BIT, logic_zdz_0, 5);
  //"��.��� �� ���2"
  if (_GET_OUTPUT_STATE(logic_zdz_0, 5))
    _SET_BIT(p_active_functions, RANG_LIGHT_ZDZ_FROM_OVD2);
  else
    _CLEAR_BIT(p_active_functions, RANG_LIGHT_ZDZ_FROM_OVD2);

  _AND4(logic_zdz_0, 2, light, 2, zdz_ovd_diagnostyka_inv, 2, control_zdz_tmp, CTR_ZDZ_OVD3_STATE_BIT, logic_zdz_0, 6);
  //"��.��� �� ���3"
  if (_GET_OUTPUT_STATE(logic_zdz_0, 6))
    _SET_BIT(p_active_functions, RANG_LIGHT_ZDZ_FROM_OVD3);
  else
    _CLEAR_BIT(p_active_functions, RANG_LIGHT_ZDZ_FROM_OVD3);

  _OR4(logic_zdz_0, 3, logic_zdz_0, 4, logic_zdz_0, 5, logic_zdz_0, 6, logic_zdz_0, 7);
#else
  if (_GET_OUTPUT_STATE(logic_zdz_0, 3)) _SET_STATE(logic_zdz_0, 7);
#endif
  
  uint32_t logic_zdz_rez = 0;
  if (current_settings_prt.ctrl_zdz_type == ZDZ_CTRL_NONE)
  {
    logic_zdz_rez |= _GET_OUTPUT_STATE(logic_zdz_0, 7) << 0;
  }
  else if (current_settings_prt.ctrl_zdz_type < _ZDZ_CTRL_NUMBER)
  {
    if (
        (current_settings_prt.ctrl_zdz_type == ZDZ_CTRL_I) ||
        (current_settings_prt.ctrl_zdz_type == ZDZ_CTRL_I_OR_U) ||
        (current_settings_prt.ctrl_zdz_type == ZDZ_CTRL_I_AND_U)
       )   
    {
      if(
         (_GET_OUTPUT_STATE(control_zdz_tmp, (CTR_ZDZ_STARTED_FROM_MTZ1_BIT - (_CTR_ZDZ_PART_III - _CTR_ZDZ_PART_II))))
         &&
         (
          (_CHECK_SET_BIT(p_active_functions, RANG_PO_MTZ1) != 0) ||
          (_CHECK_SET_BIT(p_active_functions, RANG_PO_MTZN1_VPERED) != 0) ||
          (_CHECK_SET_BIT(p_active_functions, RANG_PO_MTZN1_NAZAD) != 0) ||
          (_CHECK_SET_BIT(p_active_functions, RANG_PO_MTZPN1) != 0)
         ) 
        )   
      {
        _SET_STATE(logic_zdz_0, 8);
      }

      if(
         (_GET_OUTPUT_STATE(control_zdz_tmp, (CTR_ZDZ_STARTED_FROM_MTZ2_BIT - (_CTR_ZDZ_PART_III - _CTR_ZDZ_PART_II))))
         &&
         (
          (_CHECK_SET_BIT(p_active_functions, RANG_PO_MTZ2) != 0) ||
          (_CHECK_SET_BIT(p_active_functions, RANG_PO_MTZN2_VPERED) != 0) ||
          (_CHECK_SET_BIT(p_active_functions, RANG_PO_MTZN2_NAZAD) != 0) ||
          (_CHECK_SET_BIT(p_active_functions, RANG_PO_MTZPN2) != 0)
         ) 
        )   
      {
        _SET_STATE(logic_zdz_0, 9);
      }

      if(
         (_GET_OUTPUT_STATE(control_zdz_tmp, (CTR_ZDZ_STARTED_FROM_MTZ3_BIT - (_CTR_ZDZ_PART_III - _CTR_ZDZ_PART_II))))
         &&
         (
          (_CHECK_SET_BIT(p_active_functions, RANG_PO_MTZ3) != 0) ||
          (_CHECK_SET_BIT(p_active_functions, RANG_PO_MTZN3_VPERED) != 0) ||
          (_CHECK_SET_BIT(p_active_functions, RANG_PO_MTZN3_NAZAD) != 0) ||
          (_CHECK_SET_BIT(p_active_functions, RANG_PO_MTZPN3) != 0)
         ) 
        )   
      {
        _SET_STATE(logic_zdz_0, 10);
      }

      if(
         (_GET_OUTPUT_STATE(control_zdz_tmp, (CTR_ZDZ_STARTED_FROM_MTZ4_BIT - (_CTR_ZDZ_PART_III - _CTR_ZDZ_PART_II))))
         &&
         (
          (_CHECK_SET_BIT(p_active_functions, RANG_PO_MTZ4) != 0) ||
          (_CHECK_SET_BIT(p_active_functions, RANG_PO_MTZN4_VPERED) != 0) ||
          (_CHECK_SET_BIT(p_active_functions, RANG_PO_MTZN4_NAZAD) != 0) ||
          (_CHECK_SET_BIT(p_active_functions, RANG_PO_MTZPN4) != 0)
         ) 
        )   
      {
        _SET_STATE(logic_zdz_0, 11);
      }
      
      _OR4(logic_zdz_0, 8, logic_zdz_0, 9, logic_zdz_0, 10, logic_zdz_0, 11, logic_zdz_0, 12);
    }

    if (
        (current_settings_prt.ctrl_zdz_type == ZDZ_CTRL_U) ||
        (current_settings_prt.ctrl_zdz_type == ZDZ_CTRL_I_OR_U) ||
        (current_settings_prt.ctrl_zdz_type == ZDZ_CTRL_I_AND_U)
       )   
    {
      if(
         (_GET_OUTPUT_STATE(control_zdz_tmp, (CTR_ZDZ_STARTED_FROM_UMIN1_BIT - (_CTR_ZDZ_PART_III - _CTR_ZDZ_PART_II)))) &&
         (_CHECK_SET_BIT(p_active_functions, RANG_PO_UMIN1) != 0)
        )   
      {
        _SET_STATE(logic_zdz_0, 13);
      }
      
      if(
         (_GET_OUTPUT_STATE(control_zdz_tmp, (CTR_ZDZ_STARTED_FROM_UMIN2_BIT - (_CTR_ZDZ_PART_III - _CTR_ZDZ_PART_II)))) &&
         (_CHECK_SET_BIT(p_active_functions, RANG_PO_UMIN2) != 0)
        )   
      {
        _SET_STATE(logic_zdz_0, 14);
      }
      
      _OR2(logic_zdz_0, 13, logic_zdz_0, 14, logic_zdz_0, 15);
    }

    if (current_settings_prt.ctrl_zdz_type == ZDZ_CTRL_I)
    {
      _AND2(logic_zdz_0, 7, logic_zdz_0, 12, logic_zdz_rez, 0);
    }
    else if (current_settings_prt.ctrl_zdz_type == ZDZ_CTRL_U)
    {
      _AND2(logic_zdz_0, 7, logic_zdz_0, 15, logic_zdz_rez, 0);
    }
    else if (current_settings_prt.ctrl_zdz_type == ZDZ_CTRL_3I0)
    {
      if(
         (_CHECK_SET_BIT(p_active_functions, RANG_PO_NZZ) != 0) ||
         (_CHECK_SET_BIT(p_active_functions, RANG_PO_3I0) != 0)
        )   
      {
        _SET_STATE(logic_zdz_0, 17);
      }
      _AND2(logic_zdz_0, 7, logic_zdz_0, 17, logic_zdz_rez, 0);
    }
    else
    {
      if (current_settings_prt.ctrl_zdz_type == ZDZ_CTRL_I_OR_U)
      {
        _OR2(logic_zdz_0, 12, logic_zdz_0, 15, logic_zdz_0, 16);
      }
      else if (current_settings_prt.ctrl_zdz_type == ZDZ_CTRL_I_AND_U)
      {
        _AND2(logic_zdz_0, 12, logic_zdz_0, 15, logic_zdz_0, 16);
      }
      else
      {
        //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
        total_error_sw_fixed(88);
      }

      _AND2(logic_zdz_0, 7, logic_zdz_0, 16, logic_zdz_rez, 0);
    }
  }
  else
  {
    //���� ���� ����� ��������, ������� �������� ����������� �������, ���� ����� ��������� ��������, ��� ���� ���� �� ������������
    total_error_sw_fixed(45);
  }
  
  //"�� ���"
  if (_GET_OUTPUT_STATE(logic_zdz_rez, 0))
    _SET_BIT(p_active_functions, RANG_PO_ZDZ);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_ZDZ);
  
  _TIMER_T_0(INDEX_TIMER_ZDZ, current_settings_prt.timeout_zdz[number_group_stp], logic_zdz_rez, 0, logic_zdz_rez, 1);
  //"���"
  if (_GET_OUTPUT_STATE(logic_zdz_rez, 1))
    _SET_BIT(p_active_functions, RANG_ZDZ);
  else
    _CLEAR_BIT(p_active_functions, RANG_ZDZ);
}
/*****************************************************/

/*****************************************************/
// ��
/*****************************************************/
inline void zz_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
  /********************************
  ������ ���

  "������ ���" ����������� ��� �������:
  
  ����� 3I0 (���������� � ������� ��������) > 5 (��)
  ����� 3U0 (���������� �         ���������) > 6 (�)
  
  *********************************/
  unsigned int porig_3I0;
  if (Nzz_3I0_bilshe_porogu == 0) porig_3I0 = PORIG_CHUTLYVOSTI_3I0*KOEF_POVERNENNJA_SECTOR_BLK/100;
  else porig_3I0 = PORIG_CHUTLYVOSTI_3I0;
  unsigned int Nzz_3I0_bilshe_porogu_tmp = Nzz_3I0_bilshe_porogu = (measurement[IM_3I0] >= porig_3I0);

  unsigned int porig_3U0;
  if (Nzz_3U0_bilshe_porogu == 0) porig_3U0 = PORIG_CHUTLYVOSTI_3U0*KOEF_POVERNENNJA_SECTOR_BLK/100;
  else porig_3U0 = PORIG_CHUTLYVOSTI_3U0;
  unsigned int Nzz_3U0_bilshe_porogu_tmp = Nzz_3U0_bilshe_porogu = (measurement[IM_3U0] >= porig_3U0);
      
  if (
      ((current_settings_prt.control_zz & CTR_ZZ1_TYPE) == 0) &&
      (Nzz_3I0_bilshe_porogu_tmp != 0) &&
      (Nzz_3U0_bilshe_porogu_tmp != 0)
     )
  {
    unsigned int sector_i_minus_u;
    if (sector_NZZ == 0)
    {
      //�������� �� ������� ����������� ��� ���
      sector_i_minus_u = sector_i_minus_u_1;
    }
    else
    {
      //�������� �� ������� ���������� ��� ���
      sector_i_minus_u = sector_i_minus_u_2;
    }
  
    if ((current_settings_prt.control_zz & CTR_ZZ1_SECTOR) != 0)
    {
      //�������� �� ������� "������" (��������� 1 � 2 ��� "��� ������")
      if ((sector_i_minus_u == 1) || (sector_i_minus_u == 2))
      {
        /*
        ����-��� ��������� �������� ������, �� �� � ������ �����������
        */
        sector_NZZ = 0xff;
      }
      else
      {
        /*
        ������� �������� ������, �� �� �� � ������ �����������
        */
        sector_NZZ = 0;
      }
    }
    else
    {
      //�������� �� ������� "�����" (��������� 3 � 4 ��� "��� ������")
      if ((sector_i_minus_u == 3) || (sector_i_minus_u == 4))
      {
        /*
        ����-��� ��������� �������� ������, �� �� � ������ �����������
        */
        sector_NZZ = 0xff;
      }
      else
      {
        /*
        ������� �������� ������, �� �� �� � ������ �����������
        */
        sector_NZZ = 0;
      }
    }
  }
  else sector_NZZ = 0;

  
  //������������ ������ "������ ���",���� �� �������� - � ������ ������� �� ��������
  if (sector_NZZ != 0)
    _SET_BIT(p_active_functions, RANG_SECTOR_NZZ);
  else
    _CLEAR_BIT(p_active_functions, RANG_SECTOR_NZZ);
  /*******************************/

  /*******************************/
  //��������� �� ����� ���������� ������ ���������� � ���� ���������� ����������
  /*******************************/
  unsigned int max_3i0_current, koef_povernennja;
  
  if((current_settings_prt.control_zz & CTR_ZZ1_TYPE) == 0)
  {
    max_3i0_current = measurement[IM_3I0];
    koef_povernennja = KOEF_POVERNENNJA_GENERAL_UP;
  }
  else
  {
    max_3i0_current = measurement[IM_3I0_other_g];
    koef_povernennja = KOEF_POVERNENNJA_3I0_OTHER;
  }
  /*******************************/
  
  unsigned int setpoint;
  /********************************
  �� 3I0 (�� ��� ����������� ��������, ������� �����������/����������)
  ********************************/
  /*
  ������� ���������� � ��� � ������� �� ������� �������, � ������� � ��� � ���������,
  �� ������� ������ �� 10, ��� �������� �� ����� � ������� ��������
  */
  if (po_3I0 == 0)
  {
    //�������� �� ������� ����������� ��� 3I0
    setpoint = current_settings_prt.setpoint_zz_3I0[number_group_stp]*10;
  }
  else
  {
    //�������� �� ������� ���������� ��� 3I0
    /*
    ���������� ��������� ������
    setpoint = (current_settings_prt.setpoint_zz_3I0[number_group_stp]*koef_povernennja/100)*10 =  current_settings_prt.setpoint_zz_3I0[number_group_stp]*koef_povernennja/10
    */
    setpoint = current_settings_prt.setpoint_zz_3I0[number_group_stp]*koef_povernennja/10;
  }
  
  if (max_3i0_current >= setpoint)
  {
    /*
    ����-��� ��������� �������� ������, �� ��������� �������� ����-���� ������ ������������ �������
    */
    po_3I0 = 0xff;
  }
  else
  {
    /*
    ������� �������� ������, �� ��������� �������� ����� ������ ������������ �������
    */
    po_3I0 = 0;
  }
  /*******************************/

  /********************************
  �� 3U0 (�� ��� ����������� ��������, ������� �����������/����������)
  ********************************/
  if (po_3U0 == 0)
  {
    //�������� �� ������� ����������� ��� 3U0
    setpoint = current_settings_prt.setpoint_zz_3U0[number_group_stp];
  }
  else
  {
    //�������� �� ������� ���������� ��� 3U0
    setpoint = current_settings_prt.setpoint_zz_3U0[number_group_stp]*KOEF_POVERNENNJA_3U0/100;
  }
  
  if (measurement[IM_3U0] >= setpoint)
  {
    /*
    ����-��� ��������� �������� ������, �� ��������� �������� ����-���� ������ ������������ �������
    */
    po_3U0 = 0xff;
  }
  else
  {
    /*
    ������� �������� ������, �� ��������� �������� ����� ������ ������������ �������
    */
    po_3U0 = 0;
  }
  /*******************************/
  
  if (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_NZZ) == 0)
  {
    //���, ��/3I0 � ��/3U0 �� ��������� � ����������� �����
    /*******************************/
    //���
    /*******************************/
    if (
        ((current_settings_prt.control_zz & CTR_ZZ1_NZZ_STATE) != 0) &&
        ((current_settings_prt.control_zz & CTR_ZZ1_TYPE) == 0)
       )   
    {
      //1 ������ ��/3U0 ��������, ��������� � �� ���������
    
      unsigned int previous_state_po_nzz = _CHECK_SET_BIT(p_active_functions, RANG_PO_NZZ);
    
      //�����������, ��� ������� ������ "�� NZZ"
      if (
          (po_3I0     != 0) &&
          (po_3U0     != 0) &&
          (sector_NZZ != 0)
         )
      {
        //���� ����� ������ �� ���
        if(previous_state_po_nzz == 0)
        {
          //������������ ������ "�� NZZ"
          _SET_BIT(p_active_functions, RANG_PO_NZZ);
      
          //��������� ������ ���, ���� �� �� �� ���������
          global_timers[INDEX_TIMER_NZZ] = 0;
        }
      }
      else 
      {
        //�� ���� ����� ������ �� ���
        if(previous_state_po_nzz != 0)
        {
          //������� ������ "�� ���"
          _CLEAR_BIT(p_active_functions, RANG_PO_NZZ);
          //�� � ������ ����� �������� ������� "����. ���"
          _CLEAR_BIT(p_active_functions, RANG_NZZ);
          //���� ������ �� �� ��������, �� ������� ����
          if ( global_timers[INDEX_TIMER_NZZ] >=0) global_timers[INDEX_TIMER_NZZ] = -1;
        }
      }
    
      if(global_timers[INDEX_TIMER_NZZ] >= current_settings_prt.timeout_nzz[number_group_stp])
      {
        //���� ��������� "�������� ���" �� ������������ ������ "����. ���"
        _SET_BIT(p_active_functions, RANG_NZZ);

        //������� ������ �� ���
        global_timers[INDEX_TIMER_NZZ] = -1;
      }
    }
    else
    {
      //���� ��� �� �����������, �� ����� ������� �� ������� � �������, �� �� �� ����������
      _CLEAR_BIT(p_active_functions, RANG_PO_NZZ);
      _CLEAR_BIT(p_active_functions, RANG_NZZ);
      global_timers[INDEX_TIMER_NZZ] = -1;
    }  
    /*******************************/

    /*******************************/
    //1 ������ ��/3U0
    /*******************************/
    if ((current_settings_prt.control_zz & CTR_ZZ1_3U0_STATE) != 0)
    {
      //1 ������ ��/3U0 �������� � �� ���������
    
      unsigned int previous_state_po_3U0 = _CHECK_SET_BIT(p_active_functions, RANG_PO_3U0);
    
      //�����������, ��� ������� ������ "�� ��/3U0"
      if (po_3U0 != 0)
      {
        //����������� ������� 3U0 �������� ���� �������
        if(previous_state_po_3U0 == 0)
        {
          //������������ ������ "�� ��/3U0"
          _SET_BIT(p_active_functions, RANG_PO_3U0);
        
          //��������� ������ ��/3U0, ���� �� �� �� ���������
          global_timers[INDEX_TIMER_ZZ_3U0] = 0;
        }
      }
      else 
      {
        //����������� ������� 3I0 ����� �������
        if(previous_state_po_3U0 != 0)
        {
          //������� ������ "�� ��/3U0"
          _CLEAR_BIT(p_active_functions, RANG_PO_3U0);
          //�� � ������ ����� �������� ������� "����. ��/3U0"
          _CLEAR_BIT(p_active_functions, RANG_3U0);
          //���� ������ �� �� ��������, �� ������� ����
          if ( global_timers[INDEX_TIMER_ZZ_3U0] >=0) global_timers[INDEX_TIMER_ZZ_3U0] = -1;
        }
      }
    
      if(global_timers[INDEX_TIMER_ZZ_3U0] >= current_settings_prt.timeout_zz_3U0[number_group_stp])
      {
        //���� ��������� "�������� ��/3U0" �� ������������ ������ "����. ��/3U0"
        _SET_BIT(p_active_functions, RANG_3U0);

        //������� ������ �� ��/3U0
        global_timers[INDEX_TIMER_ZZ_3U0] = -1;
      }
    }
    else
    {
      //���� 1 ������ ��/3U0 �� �����������, �� ����� ������� �� ������� � �������, �� �� �� ����������
      _CLEAR_BIT(p_active_functions, RANG_PO_3U0);
      _CLEAR_BIT(p_active_functions, RANG_3U0);
      global_timers[INDEX_TIMER_ZZ_3U0] = -1;
    }    
    /*******************************/
  
    /*******************************/
    //1 ������ ��/3I0
    /*******************************/
    if ((current_settings_prt.control_zz & CTR_ZZ1_3I0_STATE) != 0)
    {
      //1 ������ ��/3I0 �������� � �� ���������
    
      unsigned int previous_state_po_3I0 = _CHECK_SET_BIT(p_active_functions, RANG_PO_3I0);
    
      //�����������, ��� ������� ������ "�� ��/3I0"
      if (po_3I0 != 0)
      {
        //������������ ���� 3I0 �������� ���� �������
        if(previous_state_po_3I0 == 0)
        {
          //������������ ������ "�� ��/3I0"
          _SET_BIT(p_active_functions, RANG_PO_3I0);
      
          //��������� ������ ��/3I0, ���� �� �� �� ���������
          global_timers[INDEX_TIMER_ZZ_3I0] = 0;
        }
      }
      else 
      {
        //������������ ���� 3I0 ����� �������
        if(previous_state_po_3I0 != 0)
        {
          //������� ������ "�� ��/3I0"
          _CLEAR_BIT(p_active_functions, RANG_PO_3I0);
          //�� � ������ ����� �������� ������� "����. ��/3I0"
          _CLEAR_BIT(p_active_functions, RANG_3I0);
          //���� ������ �� �� ��������, �� ������� ����
          if ( global_timers[INDEX_TIMER_ZZ_3I0] >=0) global_timers[INDEX_TIMER_ZZ_3I0] = -1;
        }
      }
    
      if(global_timers[INDEX_TIMER_ZZ_3I0] >= current_settings_prt.timeout_zz_3I0[number_group_stp])
      {
        //���� ��������� "�������� ��/3I0" �� ������������ ������ "����. ��"
        _SET_BIT(p_active_functions, RANG_3I0);

        //������� ������ �� ��/3I0
        global_timers[INDEX_TIMER_ZZ_3I0] = -1;
      }
    }
    else
    {
      //���� 1 ������ ��/3I0 �� �����������, �� ����� ������� �� ������� � �������, �� �� �� ����������
      _CLEAR_BIT(p_active_functions, RANG_PO_3I0);
      _CLEAR_BIT(p_active_functions, RANG_3I0);
      global_timers[INDEX_TIMER_ZZ_3I0] = -1;
    }  
    /*******************************/
  }
  else
  {
    //������� ��/��� ��������� � ����������� �����, �� ����� ������� �� ������� � �������, �� �� ��� ����������
    _CLEAR_BIT(p_active_functions, RANG_PO_NZZ);
    _CLEAR_BIT(p_active_functions, RANG_NZZ);
    _CLEAR_BIT(p_active_functions, RANG_PO_3I0);
    _CLEAR_BIT(p_active_functions, RANG_3I0);
    _CLEAR_BIT(p_active_functions, RANG_PO_3U0);
    _CLEAR_BIT(p_active_functions, RANG_3U0);

    global_timers[INDEX_TIMER_NZZ   ] = -1;
    global_timers[INDEX_TIMER_ZZ_3U0] = -1;
    global_timers[INDEX_TIMER_ZZ_3I0] = -1;
  }  
}
/*****************************************************/

/*****************************************************/
//����
/*****************************************************/
inline void tznp_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
#define CTR_TZNP                CTR_TZNP1      
#define CTR_TZNP_VPERED         CTR_TZNP1_VPERED      
#define CTR_TZNP_NAZAD          CTR_TZNP1_NAZAD      

#define RANG_BLOCK_TZNP         RANG_BLOCK_TZNP1
#define RANG_SECTOR_TZNP_VPERED RANG_SECTOR_TZNP1_VPERED
#define RANG_SECTOR_TZNP_NAZAD  RANG_SECTOR_TZNP1_NAZAD
#define RANG_PO_3I0_TZNP_VPERED RANG_PO_3I0_TZNP1_VPERED
#define RANG_PO_3I0_TZNP_NAZAD  RANG_PO_3I0_TZNP1_NAZAD
#define RANG_PO_3U0_TZNP_VPERED RANG_PO_3U0_TZNP1_VPERED
#define RANG_PO_3U0_TZNP_NAZAD  RANG_PO_3U0_TZNP1_NAZAD
#define RANG_PO_TZNP_VPERED     RANG_PO_TZNP1_VPERED
#define RANG_PO_TZNP_NAZAD      RANG_PO_TZNP1_NAZAD
#define RANG_TZNP               RANG_TZNP1
  
  unsigned int maska_ctrl_bits = CTR_TZNP | CTR_TZNP_VPERED | CTR_TZNP_NAZAD;
  
  for (unsigned int tznp = 0; tznp < 3; tznp++)
  {
    unsigned int setpoint_tznp_3I0_vpered;
    unsigned int setpoint_tznp_3U0_vpered;
    unsigned int setpoint_tznp_3I0_nazad;
    unsigned int setpoint_tznp_3U0_nazad;

    int timeout_tznp_vpered;
    int timeout_tznp_nazad;
    
    unsigned int index_timer_vpered;
    unsigned int index_timer_nazad;
    
    unsigned int control_tznp;
    
    unsigned int shift_to_base_rang_index;
    
    switch(tznp)
    {
    case 0:
      {
        setpoint_tznp_3I0_vpered = current_settings_prt.setpoint_tznp_1_3I0_vpered[number_group_stp];
        setpoint_tznp_3U0_vpered = current_settings_prt.setpoint_tznp_1_3U0_vpered[number_group_stp];
        setpoint_tznp_3I0_nazad  = current_settings_prt.setpoint_tznp_1_3I0_nazad[number_group_stp];
        setpoint_tznp_3U0_nazad  = current_settings_prt.setpoint_tznp_1_3U0_nazad[number_group_stp];
        
        timeout_tznp_vpered = current_settings_prt.timeout_tznp_1_vpered[number_group_stp];
        timeout_tznp_nazad  = current_settings_prt.timeout_tznp_1_nazad[number_group_stp]; 
        
        index_timer_vpered = INDEX_TIMER_TZNP1_VPERED; 
        index_timer_nazad  = INDEX_TIMER_TZNP1_NAZAD;
        
        control_tznp = (current_settings_prt.control_tznp >> INDEX_ML_CTR_TZNP1) & maska_ctrl_bits;
        
        shift_to_base_rang_index = RANG_BLOCK_TZNP1 - RANG_BLOCK_TZNP;
        
        break;
      }
    case 1:
      {
        setpoint_tznp_3I0_vpered = current_settings_prt.setpoint_tznp_2_3I0_vpered[number_group_stp];
        setpoint_tznp_3U0_vpered = current_settings_prt.setpoint_tznp_2_3U0_vpered[number_group_stp];
        setpoint_tznp_3I0_nazad  = current_settings_prt.setpoint_tznp_2_3I0_nazad[number_group_stp];
        setpoint_tznp_3U0_nazad  = current_settings_prt.setpoint_tznp_2_3U0_nazad[number_group_stp];
        
        timeout_tznp_vpered = current_settings_prt.timeout_tznp_2_vpered[number_group_stp];
        timeout_tznp_nazad  = current_settings_prt.timeout_tznp_2_nazad[number_group_stp]; 
        
        index_timer_vpered = INDEX_TIMER_TZNP2_VPERED; 
        index_timer_nazad  = INDEX_TIMER_TZNP2_NAZAD;
        
        control_tznp = (current_settings_prt.control_tznp >> INDEX_ML_CTR_TZNP2) & maska_ctrl_bits;
        
        shift_to_base_rang_index = RANG_BLOCK_TZNP2 - RANG_BLOCK_TZNP;
        
        break;
      }
    case 2:
      {
        setpoint_tznp_3I0_vpered = current_settings_prt.setpoint_tznp_3_3I0_vpered[number_group_stp];
        setpoint_tznp_3U0_vpered = current_settings_prt.setpoint_tznp_3_3U0_vpered[number_group_stp];
        setpoint_tznp_3I0_nazad  = current_settings_prt.setpoint_tznp_3_3I0_nazad[number_group_stp];
        setpoint_tznp_3U0_nazad  = current_settings_prt.setpoint_tznp_3_3U0_nazad[number_group_stp];
        
        timeout_tznp_vpered = current_settings_prt.timeout_tznp_3_vpered[number_group_stp];
        timeout_tznp_nazad  = current_settings_prt.timeout_tznp_3_nazad[number_group_stp]; 
        
        index_timer_vpered = INDEX_TIMER_TZNP3_VPERED; 
        index_timer_nazad  = INDEX_TIMER_TZNP3_NAZAD;
        
        control_tznp = (current_settings_prt.control_tznp >> INDEX_ML_CTR_TZNP3) & maska_ctrl_bits;
        
        shift_to_base_rang_index = RANG_BLOCK_TZNP3 - RANG_BLOCK_TZNP;
        
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(82);
      }
    }

    unsigned int logic_TZNP_0 = 0;
    unsigned int setpoint;
    
    /***
    ������ ������
    ***/
    if(sector_directional_tznp[tznp] == 1)
    {
      logic_TZNP_0 |= 1 << 0;
      _SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_SECTOR_TZNP_VPERED));
    }
    else _CLEAR_BIT(p_active_functions, (shift_to_base_rang_index + RANG_SECTOR_TZNP_VPERED));
    /***/
    
    /***
    ������ �����
    ***/
    if(sector_directional_tznp[tznp] == 2)
    {
      logic_TZNP_0 |= 1 << 1;
      _SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_SECTOR_TZNP_NAZAD));
    }
    else _CLEAR_BIT(p_active_functions, (shift_to_base_rang_index + RANG_SECTOR_TZNP_NAZAD));
    /***/
    
    /***
    �� 3I0 ������
    ***/
    if (_CHECK_SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3I0_TZNP_VPERED)) == 0)
    {
      //�������� �� ������� �����������
      setpoint = setpoint_tznp_3I0_vpered;
    }
    else
    {
      //�������� �� ������� ����������
      setpoint = setpoint_tznp_3I0_vpered*KOEF_POVERNENNJA_GENERAL_UP/100;
    }
    if (measurement[IM_3I0_r] >= setpoint)
    {
      logic_TZNP_0 |=  1 << 3;
      _SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3I0_TZNP_VPERED));
    }
    else _CLEAR_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3I0_TZNP_VPERED));
    /***/
    
    /***
    �� 3U0 ������
    ***/
    if (_CHECK_SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3U0_TZNP_VPERED)) == 0)
    {
      //�������� �� ������� �����������
      setpoint = setpoint_tznp_3U0_vpered;
    }
    else
    {
      //�������� �� ������� ����������
      setpoint = setpoint_tznp_3U0_vpered*KOEF_POVERNENNJA_3U0/100;
    }
    if (measurement[IM_3U0] >= setpoint)
    {
      logic_TZNP_0 |=  1 << 4;
      _SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3U0_TZNP_VPERED));
    }
    else _CLEAR_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3U0_TZNP_VPERED));
    /***/
    
    /***
    �� 3I0 �����
    ***/
    if (_CHECK_SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3I0_TZNP_NAZAD)) == 0)
    {
      //�������� �� ������� �����������
      setpoint = setpoint_tznp_3I0_nazad;
    }
    else
    {
      //�������� �� ������� ����������
      setpoint = setpoint_tznp_3I0_nazad*KOEF_POVERNENNJA_GENERAL_UP/100;
    }
    if (measurement[IM_3I0_r] >= setpoint)
    {
      logic_TZNP_0 |=  1 << 5;
      _SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3I0_TZNP_NAZAD));
    }
    else _CLEAR_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3I0_TZNP_NAZAD));
    /***/
    
    /***
    �� 3U0 �����
    ***/
    if (_CHECK_SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3U0_TZNP_NAZAD)) == 0)
    {
      //�������� �� ������� �����������
      setpoint = setpoint_tznp_3U0_nazad;
    }
    else
    {
      //�������� �� ������� ����������
      setpoint = setpoint_tznp_3U0_nazad*KOEF_POVERNENNJA_3U0/100;
    }
    if (measurement[IM_3U0] >= setpoint)
    {
      logic_TZNP_0 |=  1 << 6;
      _SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3U0_TZNP_NAZAD));
    }
    else _CLEAR_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_3U0_TZNP_NAZAD));
    /***/
    
    //���� ������� �������
    logic_TZNP_0 |= ((control_tznp & CTR_TZNP) != 0) << 7;
    
    //���� ���������� �������
    logic_TZNP_0 |= (_CHECK_SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_BLOCK_TZNP)) == 0) << 8;
    
    //���� �������� ������
    logic_TZNP_0 |= ((control_tznp & CTR_TZNP_VPERED) != 0) << 10;
    
    //���� �������� �����
    logic_TZNP_0 |= ((control_tznp & CTR_TZNP_NAZAD) != 0) << 11;

    _AND2(logic_TZNP_0, 7, logic_TZNP_0, 8, logic_TZNP_0, 9);

    //�� ���� ������
    _AND5(logic_TZNP_0, 9, logic_TZNP_0, 10, logic_TZNP_0, 3, logic_TZNP_0, 4, logic_TZNP_0, 0, logic_TZNP_0, 12);
    if (_GET_OUTPUT_STATE(logic_TZNP_0, 12)) _SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_TZNP_VPERED));
    else _CLEAR_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_TZNP_VPERED));
      
    //�� ���� �����
    _AND5(logic_TZNP_0, 9, logic_TZNP_0, 11, logic_TZNP_0, 5, logic_TZNP_0, 6, logic_TZNP_0, 1, logic_TZNP_0, 13);
    if (_GET_OUTPUT_STATE(logic_TZNP_0, 13)) _SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_TZNP_NAZAD));
    else _CLEAR_BIT(p_active_functions, (shift_to_base_rang_index + RANG_PO_TZNP_NAZAD));

    _TIMER_T_0(index_timer_vpered, timeout_tznp_vpered, logic_TZNP_0, 12, logic_TZNP_0, 14);
    _TIMER_T_0(index_timer_nazad,  timeout_tznp_nazad,  logic_TZNP_0, 13, logic_TZNP_0, 15);
    
    //����
    _OR2(logic_TZNP_0, 14, logic_TZNP_0, 15, logic_TZNP_0, 16);
    if (_GET_OUTPUT_STATE(logic_TZNP_0, 16)) _SET_BIT(p_active_functions, (shift_to_base_rang_index + RANG_TZNP));
    else _CLEAR_BIT(p_active_functions, (shift_to_base_rang_index + RANG_TZNP));
  }

#undef CTR_TZNP
#undef CTR_TZNP_VPERED
#undef CTR_TZNP_NAZAD

#undef RANG_BLOCK_TZNP
#undef RANG_SECTOR_TZNP_VPERED
#undef RANG_SECTOR_TZNP_NAZAD
#undef RANG_PO_3I0_TZNP_VPERED
#undef RANG_PO_3I0_TZNP_NAZAD
#undef RANG_PO_3U0_TZNP_VPERED
#undef RANG_PO_3U0_TZNP_NAZAD
#undef RANG_PO_TZNP_VPERED
#undef RANG_PO_TZNP_NAZAD
#undef RANG_TZNP
}
/*****************************************************/

/*****************************************************/
// ���(���)
/*****************************************************/
inline void zop_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
  /*******************************/
  //������� � �������� ����� ������ ������ ��������� ����������� � ����������������
  /*******************************/
  unsigned int i2_current = measurement[IM_I2], i1_current = measurement[IM_I1];
  /*******************************/
  
  /*******************************/
  //1 ������ ���(���)
  /*******************************/
  if ((current_settings_prt.control_zop & CTR_ZOP_STATE) != 0)
  {
    //1 ������ ���(���) ��������
    unsigned int setpoint; //������� - � ���� ���������� ����������� ��������
    unsigned int setpoint_i1, setpoint_i2;
    unsigned int previous_state_po_zop1;
    
    if (i1_bilshe_porogu == 0) setpoint_i1 = MIN_LIMIT_FOR_I1_AND_I2*KOEF_POVERNENNJA_ZOP_BLK/100;
    else setpoint_i1 = MIN_LIMIT_FOR_I1_AND_I2;
    unsigned int i1_bilshe_porogu_tmp = i1_bilshe_porogu = (i1_current >= setpoint_i1);
    
    if (i2_bilshe_porogu == 0) setpoint_i2 = MIN_LIMIT_FOR_I1_AND_I2*KOEF_POVERNENNJA_ZOP_BLK/100;
    else setpoint_i2 = MIN_LIMIT_FOR_I1_AND_I2;
    unsigned int i2_bilshe_porogu_tmp = i2_bilshe_porogu = (i2_current >= setpoint_i2);
    
    //���� �� ���(���) �� �� �������, �� ����� ��������� �� ������ ���������� - �������, ��� ��������� �� ������� � ������� ���� �� ��������� ����
    //���� �� ���(���) ��� ����������, �� ����� ��������� �� ������� ���������� - �������� ������� �� ������� ������ �� ����������� ����������
    if(( previous_state_po_zop1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_ZOP) ) == 0 )
    {
      //�������� �� ������ �����������
      setpoint = current_settings_prt.setpoint_zop[number_group_stp];
    }
    else
    {
      //�������� �� ������ ����������
      setpoint = current_settings_prt.setpoint_zop[number_group_stp]*KOEF_POVERNENNJA_GENERAL_UP/100;
    }
    
    //�����������, ��� ������� ������ "�� ���"
    /*
    I2
    -- >= K
    I1
    ������� �������� ������ � ��� � ����������� �� 1000, ,�� 0,010 ������� 10, � 1,000 ������� 1000,
    �� K*1000 = SETPOINT =>
        SETPOINT
    K = --------  =>
         1000
    I2    SETPOINT
    -- >= ---------
    I1     1000
    
    ������ ��������� � ����� ����������� �� ����� � ���� �������������, �� ���� � � ��������� ��������� (��������), � ��� �������� �� ���������
    
    (I2*1000) >= (SETPOINT*I1)
    */
    if (
        (i1_bilshe_porogu_tmp != 0) &&
        (i2_bilshe_porogu_tmp != 0) &&
        ((i2_current*1000) >= (i1_current*setpoint))                            && 
        (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_ZOP) == 0)
       )
    {
      //���� ����� ��������� ��������� ������ ��������� �����������
      if(previous_state_po_zop1 == 0)
      {
        //������������ ������ "�� ���"
        _SET_BIT(p_active_functions, RANG_PO_ZOP);
      
        //��������� ������ ���(���), ���� �� �� �� ���������
        global_timers[INDEX_TIMER_ZOP] = 0;
      }
    }
    else 
    {
      //�� ���� ����� ��������� ��������� ������ ��������� �����������
      if(previous_state_po_zop1 != 0)
      {
        //������� ������ "�� ���"
        _CLEAR_BIT(p_active_functions, RANG_PO_ZOP);
        //�� � ������ ����� �������� ������� "����. ���"
        _CLEAR_BIT(p_active_functions, RANG_ZOP);
        //���� ������ �� �� ��������? �� ������� ����
        if ( global_timers[INDEX_TIMER_ZOP] >=0) global_timers[INDEX_TIMER_ZOP] = -1;
      }
    }
    
    if(global_timers[INDEX_TIMER_ZOP] >= current_settings_prt.timeout_zop[number_group_stp])
    {
      //���� ��������� �������� ���(���) �� ������������ ������ "����. ���"
      _SET_BIT(p_active_functions, RANG_ZOP);

      //������� ������ ���(���)
      global_timers[INDEX_TIMER_ZOP] = -1;
    }
  }
  else
  {
    //����� ������� �� ������� � �������, �� �� 1 ������ ���(���) ����������
    _CLEAR_BIT(p_active_functions, RANG_PO_ZOP);
    _CLEAR_BIT(p_active_functions, RANG_ZOP);
    global_timers[INDEX_TIMER_ZOP] = -1;

  }  
}
/*****************************************************/

/*****************************************************/
// �����1
/*****************************************************/
void umin1_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
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
  
  _Bool Ia_and_Ic_is_smaller_than_Iust = (measurement[IM_IA] <= setpoint3) &&
                                         (measurement[IM_IB] <= setpoint3) &&
                                         (measurement[IM_IC] <= setpoint3);
  //�
  unsigned int tmp_value = ((current_settings_prt.control_transformator & MASKA_FOR_BIT(INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE)) == 0) << 0;
//  tmp_value |= ((current_settings_prt.control_Umin & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                                 << 1;
//  _INVERTOR(tmp_value, 1, tmp_value, 1);
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN1) != 0)                                                            << 2;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_PO_UMIN1_OR_AND) != 0)                                                  << 3;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN1_UBLK) != 0)                                                       << 4;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN1_IBLK) != 0)                                                       << 5;
  
  //��
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_UMIN1) != 0)                                     << 6;
  _INVERTOR(tmp_value, 6, tmp_value, 6);
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_START_UMIN1) != 0)                                     << 7;
  
//  _AND2(tmp_value, 0, tmp_value, 1, tmp_value, 8);
  
  if (_GET_OUTPUT_STATE(tmp_value, 0)) 
  {
    //������
    _AND4(Ua_is_smaller_than_Umin1, 0, Ub_is_smaller_than_Umin1, 0, Uc_is_smaller_than_Umin1, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Ua_is_smaller_than_Umin1, 0, Ub_is_smaller_than_Umin1, 0, Uc_is_smaller_than_Umin1, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_and_Ic_is_smaller_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Ua_or_Ub_or_Uc_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //�� U���. Umin1
    if (Ua_or_Ub_or_Uc_is_smaller_than_250mV)
      _SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN1);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_UBLK_UMIN1);
  } 
  else 
  {
    //��������
    _AND4(Uab_is_smaller_than_Umin1, 0, Ubc_is_smaller_than_Umin1, 0, Uca_is_smaller_than_Umin1, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Uab_is_smaller_than_Umin1, 0, Ubc_is_smaller_than_Umin1, 0, Uca_is_smaller_than_Umin1, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_and_Ic_is_smaller_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Uab_or_Ubc_or_Uca_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //�� U���. Umin1
    if (Uab_or_Ubc_or_Uca_is_smaller_than_250mV)
      _SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN1);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_UBLK_UMIN1);
  }
  _INVERTOR(tmp_value, 12, tmp_value, 12);
  _INVERTOR(tmp_value, 13, tmp_value, 13);
  _OR3(tmp_value, 7, tmp_value, 9, tmp_value, 11, tmp_value, 14);
  
  _AND5(tmp_value, 6, tmp_value, 2, tmp_value, 14, tmp_value, 13, tmp_value, 12, tmp_value, 15);
  
  //�� I���. Umin1
  if (Ia_and_Ic_is_smaller_than_Iust)
    _SET_BIT(p_active_functions, RANG_PO_IBLK_UMIN1);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_IBLK_UMIN1);
  
  //�� Umin1
  if (_GET_OUTPUT_STATE(tmp_value, 15))
    _SET_BIT(p_active_functions, RANG_PO_UMIN1);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_UMIN1);
  
  _TIMER_T_0(INDEX_TIMER_UMIN1, current_settings_prt.timeout_Umin1[number_group_stp], tmp_value, 15, tmp_value, 16);
  
  //����. Umin1
  if (_GET_OUTPUT_STATE(tmp_value, 16))
    _SET_BIT(p_active_functions, RANG_UMIN1);
  else
    _CLEAR_BIT(p_active_functions, RANG_UMIN1);
}
/*****************************************************/

/*****************************************************/
// �����2
/*****************************************************/
void umin2_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
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
  
  _Bool Ia_and_Ic_is_smaller_than_Iust = (measurement[IM_IA] <= setpoint3) &&
                                         (measurement[IM_IB] <= setpoint3) &&
                                         (measurement[IM_IC] <= setpoint3);
  //�
  unsigned int tmp_value = ((current_settings_prt.control_transformator & MASKA_FOR_BIT(INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE)) == 0) << 0;
//  tmp_value |= ((current_settings_prt.control_Umin & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                                 << 1;
//  _INVERTOR(tmp_value, 1, tmp_value, 1);
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN2) != 0)                                                            << 2;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_PO_UMIN2_OR_AND) != 0)                                                  << 3;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN2_UBLK) != 0)                                                       << 4;
  tmp_value |= ((current_settings_prt.control_Umin & CTR_UMIN2_IBLK) != 0)                                                       << 5;
  
  //��
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_UMIN2) != 0)                                    << 6;
  _INVERTOR(tmp_value, 6, tmp_value, 6);
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_START_UMIN2) != 0)                                    << 7;
  
//  _AND2(tmp_value, 0, tmp_value, 1, tmp_value, 8);
  
  if (_GET_OUTPUT_STATE(tmp_value, 0))
  {
    //������
    _AND4(Ua_is_smaller_than_Umin2, 0, Ub_is_smaller_than_Umin2, 0, Uc_is_smaller_than_Umin2, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Ua_is_smaller_than_Umin2, 0, Ub_is_smaller_than_Umin2, 0, Uc_is_smaller_than_Umin2, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_and_Ic_is_smaller_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Ua_or_Ub_or_Uc_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //�� U���. Umin2
    if (Ua_or_Ub_or_Uc_is_smaller_than_250mV)
      _SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN2);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_UBLK_UMIN2);
    
  } 
  else 
  {
    //��������
    _AND4(Uab_is_smaller_than_Umin2, 0, Ubc_is_smaller_than_Umin2, 0, Uca_is_smaller_than_Umin2, 0, tmp_value, 3, tmp_value, 9);
    _OR3(Uab_is_smaller_than_Umin2, 0, Ubc_is_smaller_than_Umin2, 0, Uca_is_smaller_than_Umin2, 0, tmp_value, 10);
    _INVERTOR(tmp_value, 3, tmp_value, 3);
    _AND2(tmp_value, 10, tmp_value, 3, tmp_value, 11);
    _AND2(tmp_value, 5, Ia_and_Ic_is_smaller_than_Iust, 0, tmp_value, 12);
    _INVERTOR(tmp_value, 5, tmp_value, 5);
    _AND3(Uab_or_Ubc_or_Uca_is_smaller_than_250mV, 0, tmp_value, 4, tmp_value, 5, tmp_value, 13);
    
    //�� U���. Umin2
    if (Uab_or_Ubc_or_Uca_is_smaller_than_250mV)
      _SET_BIT(p_active_functions, RANG_PO_UBLK_UMIN2);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_UBLK_UMIN2);
  }
  _INVERTOR(tmp_value, 12, tmp_value, 12);
  _INVERTOR(tmp_value, 13, tmp_value, 13);
  _OR3(tmp_value, 7, tmp_value, 9, tmp_value, 11, tmp_value, 14);
  
  _AND5(tmp_value, 6, tmp_value, 2, tmp_value, 14, tmp_value, 13, tmp_value, 12, tmp_value, 15);
  
  //�� I���. Umin2
  if (Ia_and_Ic_is_smaller_than_Iust)
    _SET_BIT(p_active_functions, RANG_PO_IBLK_UMIN2);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_IBLK_UMIN2);
  
  //�� Umin2
  if (_GET_OUTPUT_STATE(tmp_value, 15))
    _SET_BIT(p_active_functions, RANG_PO_UMIN2);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_UMIN2);
  
  _TIMER_T_0(INDEX_TIMER_UMIN2, current_settings_prt.timeout_Umin2[number_group_stp], tmp_value, 15, tmp_value, 16);
  
  //����. Umin2
  if (_GET_OUTPUT_STATE(tmp_value, 16))
    _SET_BIT(p_active_functions, RANG_UMIN2);
  else
    _CLEAR_BIT(p_active_functions, RANG_UMIN2);
}
/*****************************************************/

/*****************************************************/
// ���04
/*****************************************************/
void dz_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
	mf_of_handler(p_active_functions,number_group_stp);
	fault_U_handler(p_active_functions,number_group_stp);
	dz1_handler(p_active_functions,number_group_stp);
	dz2_handler(p_active_functions,number_group_stp);
	dz3_handler(p_active_functions,number_group_stp);
	dz4_handler(p_active_functions,number_group_stp);
}

/*****************************************************/
// ������1
/*****************************************************/
void umax1_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
  _Bool previous_state_po_umax1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UMAX1) > 0;
  
  unsigned int setpoint1 = previous_state_po_umax1 ?
          current_settings_prt.setpoint_Umax1[number_group_stp] * current_settings_prt.setpoint_kp_Umax[number_group_stp] / 100 :
          current_settings_prt.setpoint_Umax1[number_group_stp];
  
  _Bool Uab_is_larger_than_Umax1 = measurement[IM_UAB] >= setpoint1;
  _Bool Ubc_is_larger_than_Umax1 = measurement[IM_UBC] >= setpoint1;
  _Bool Uca_is_larger_than_Umax1 = measurement[IM_UCA] >= setpoint1;
  
  _Bool Ua_is_larger_than_Umax1 = measurement[IM_UA] >= setpoint1;
  _Bool Ub_is_larger_than_Umax1 = measurement[IM_UB] >= setpoint1;
  _Bool Uc_is_larger_than_Umax1 = measurement[IM_UC] >= setpoint1;
  
  //�
  unsigned int tmp_value = ((current_settings_prt.control_transformator & MASKA_FOR_BIT(INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE)) == 0) << 0;
//  tmp_value |= ((current_settings_prt.control_Umax & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                                 << 1;
//  _INVERTOR(tmp_value, 1, tmp_value, 1);
  tmp_value |= ((current_settings_prt.control_Umax & CTR_PO_UMAX1_OR_AND) != 0)                                                  << 2;
  tmp_value |= ((current_settings_prt.control_Umax & CTR_UMAX1) != 0)                                                            << 3;
  
  //��
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_UMAX1) != 0)                                    << 4;
  
  if (_GET_OUTPUT_STATE(tmp_value, 0)) {
    _AND4(Ua_is_larger_than_Umax1, 0, Ub_is_larger_than_Umax1, 0, Uc_is_larger_than_Umax1, 0, tmp_value, 2, tmp_value, 5);
    _OR3(Ua_is_larger_than_Umax1, 0, Ub_is_larger_than_Umax1, 0, Uc_is_larger_than_Umax1, 0, tmp_value, 6);
  } else {
    _AND4(Uab_is_larger_than_Umax1, 0, Ubc_is_larger_than_Umax1, 0, Uca_is_larger_than_Umax1, 0, tmp_value, 2, tmp_value, 5);
    _OR3(Uab_is_larger_than_Umax1, 0, Ubc_is_larger_than_Umax1, 0, Uca_is_larger_than_Umax1, 0, tmp_value, 6);
  }
  
  _INVERTOR(tmp_value, 2, tmp_value, 2);
  _AND2(tmp_value, 6, tmp_value, 2, tmp_value, 7);
  _OR2(tmp_value, 5, tmp_value, 7, tmp_value, 8);
  _INVERTOR(tmp_value, 4, tmp_value, 4);
  _AND3(tmp_value, 8, tmp_value, 4, tmp_value, 3, tmp_value, 9);
  
  //�� Umax1
  if (_GET_OUTPUT_STATE(tmp_value, 9))
    _SET_BIT(p_active_functions, RANG_PO_UMAX1);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_UMAX1);
  
  _TIMER_T_0(INDEX_TIMER_UMAX1, current_settings_prt.timeout_Umax1[number_group_stp], tmp_value, 9, tmp_value, 10);
  
  //����. Umax1
  if (_GET_OUTPUT_STATE(tmp_value, 10))
    _SET_BIT(p_active_functions, RANG_UMAX1);
  else
    _CLEAR_BIT(p_active_functions, RANG_UMAX1);
}
/*****************************************************/

/*****************************************************/
// ������2
/*****************************************************/
void umax2_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
  _Bool previous_state_po_umax2 = _CHECK_SET_BIT(p_active_functions, RANG_PO_UMAX2) > 0;
  
  unsigned int setpoint1 = previous_state_po_umax2 ?
          current_settings_prt.setpoint_Umax2[number_group_stp] * current_settings_prt.setpoint_kp_Umax[number_group_stp] / 100 :
          current_settings_prt.setpoint_Umax2[number_group_stp];
  
  _Bool Uab_is_larger_than_Umax2 = measurement[IM_UAB] >= setpoint1;
  _Bool Ubc_is_larger_than_Umax2 = measurement[IM_UBC] >= setpoint1;
  _Bool Uca_is_larger_than_Umax2 = measurement[IM_UCA] >= setpoint1;
  
  _Bool Ua_is_larger_than_Umax2 = measurement[IM_UA] >= setpoint1;
  _Bool Ub_is_larger_than_Umax2 = measurement[IM_UB] >= setpoint1;
  _Bool Uc_is_larger_than_Umax2 = measurement[IM_UC] >= setpoint1;
  
  //�
  unsigned int tmp_value = ((current_settings_prt.control_transformator & MASKA_FOR_BIT(INDEX_ML_CTR_TRANSFORMATOR_PHASE_LINE)) == 0) << 0;
//  tmp_value |= ((current_settings_prt.control_Umax & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) != 0)                                 << 1;
//  _INVERTOR(tmp_value, 1, tmp_value, 1);
  tmp_value |= ((current_settings_prt.control_Umax & CTR_PO_UMAX2_OR_AND) != 0)                                                  << 2;
  tmp_value |= ((current_settings_prt.control_Umax & CTR_UMAX2) != 0)                                                            << 3;
  
  //��
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_UMAX2) != 0)                                    << 4;
  
  if (_GET_OUTPUT_STATE(tmp_value, 0)) {
    _AND4(Ua_is_larger_than_Umax2, 0, Ub_is_larger_than_Umax2, 0, Uc_is_larger_than_Umax2, 0, tmp_value, 2, tmp_value, 5);
    _OR3(Ua_is_larger_than_Umax2, 0, Ub_is_larger_than_Umax2, 0, Uc_is_larger_than_Umax2, 0, tmp_value, 6);
  } else {
    _AND4(Uab_is_larger_than_Umax2, 0, Ubc_is_larger_than_Umax2, 0, Uca_is_larger_than_Umax2, 0, tmp_value, 2, tmp_value, 5);
    _OR3(Uab_is_larger_than_Umax2, 0, Ubc_is_larger_than_Umax2, 0, Uca_is_larger_than_Umax2, 0, tmp_value, 6);
  }
  
  _INVERTOR(tmp_value, 2, tmp_value, 2);
  _AND2(tmp_value, 6, tmp_value, 2, tmp_value, 7);
  _OR2(tmp_value, 5, tmp_value, 7, tmp_value, 8);
  _INVERTOR(tmp_value, 4, tmp_value, 4);
  _AND3(tmp_value, 8, tmp_value, 4, tmp_value, 3, tmp_value, 9);
  
  //�� Umax1
  if (_GET_OUTPUT_STATE(tmp_value, 9))
    _SET_BIT(p_active_functions, RANG_PO_UMAX2);
  else
    _CLEAR_BIT(p_active_functions, RANG_PO_UMAX2);
  
  _TIMER_T_0(INDEX_TIMER_UMAX2, current_settings_prt.timeout_Umax2[number_group_stp], tmp_value, 9, tmp_value, 10);
  
  //����. Umax1
  if (_GET_OUTPUT_STATE(tmp_value, 10))
    _SET_BIT(p_active_functions, RANG_UMAX2);
  else
    _CLEAR_BIT(p_active_functions, RANG_UMAX2);
}
/*****************************************************/

/*****************************************************/
// ��� ����
/*****************************************************/
void achr_chapv_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
//RANG_ACHR_CHAPV_VID_DV,
/*
  //���� ���� �� ���
  _Bool previous_state_po_f1_achr = _CHECK_SET_BIT(p_active_functions, RANG_PO_ACHR1);
  //���� ���� �� ����
  _Bool previous_state_po_f1_chapv = _CHECK_SET_BIT(p_active_functions, RANG_PO_CHAPV1);
 // 
����������
*/
  //���� ���� �� ���1
  _Bool previous_state_po_f1_achr1  = _CHECK_SET_BIT(p_active_functions, RANG_PO_ACHR1);
  //���� ���� �� ����1
  _Bool previous_state_po_f1_chapv1 = _CHECK_SET_BIT(p_active_functions, RANG_PO_CHAPV1);
  //���� ���� �� ���2
  _Bool previous_state_po_f1_achr2  = _CHECK_SET_BIT(p_active_functions, RANG_PO_ACHR2);
  //���� ���� �� ����2
  _Bool previous_state_po_f1_chapv2 = _CHECK_SET_BIT(p_active_functions, RANG_PO_CHAPV2);
//----------
/*
���������
*/

  unsigned int setpoint1 = previous_state_po_achr_chapv_uaf1 ?
          current_settings_prt.setpoint_achr_chapv_uf[number_group_stp] * U_UP / 100 :
          current_settings_prt.setpoint_achr_chapv_uf[number_group_stp];
          
  unsigned int setpoint2 = previous_state_po_achr_chapv_ubf1 ?
          current_settings_prt.setpoint_achr_chapv_uf[number_group_stp] * U_UP / 100 :
          current_settings_prt.setpoint_achr_chapv_uf[number_group_stp];
  unsigned int setpoint3 = previous_state_po_achr_chapv_ucf1 ?
          current_settings_prt.setpoint_achr_chapv_uf[number_group_stp] * U_UP / 100 :
          current_settings_prt.setpoint_achr_chapv_uf[number_group_stp];
  
  //��������
//  _Bool Uab_is_larger_than_UF1 = measurement[IM_UAB] >= setpoint1;
//  _Bool Ubc_is_larger_than_UF1 = measurement[IM_UBC] >= setpoint2;
//  _Bool Uca_is_larger_than_UF1 = measurement[IM_UCA] >= setpoint3;
  
  //������
  _Bool Ua_is_larger_than_UF1 = measurement[IM_UA] >= setpoint1;
  _Bool Ub_is_larger_than_UF1 = measurement[IM_UB] >= setpoint2;
  _Bool Uc_is_larger_than_UF1 = measurement[IM_UC] >= setpoint3;
  
//  /*----------------����� ������/��������-------------------------------------*/
//  _Bool UF1_phase = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_PHASE_LINE) == 0);
//  /*--------------------------------------------------------------------------*/
  
  _Bool timer1 = 0;
  _Bool UF1_is_larger_than_U_setpoint_F1 = 0;
//  _Bool UF1_is_smaller_than_U_setpoint_F1 = 0;
  //�� ������-��������
//  if (UF1_phase)
//  {
    //�� UAF1
    previous_state_po_achr_chapv_uaf1 = Ua_is_larger_than_UF1;
    //�� UBF1
    previous_state_po_achr_chapv_ubf1 = Ub_is_larger_than_UF1;
    //�� UCF1
    previous_state_po_achr_chapv_ucf1 = Uc_is_larger_than_UF1;
    _AND3(Ua_is_larger_than_UF1, 0, Ub_is_larger_than_UF1, 0, Uc_is_larger_than_UF1, 0, timer1, 0);
//  }
//  else 
//  {
//    //�� UAF1
//    previous_state_po_achr_chapv_uaf1 = Uab_is_larger_than_UF1;
//    //�� UBF1
//    previous_state_po_achr_chapv_ubf1 = Ubc_is_larger_than_UF1;
//    //�� UCF1
//    previous_state_po_achr_chapv_ucf1 = Uca_is_larger_than_UF1;
//    _AND3(Uab_is_larger_than_UF1, 0, Ubc_is_larger_than_UF1, 0, Uca_is_larger_than_UF1, 0, timer1, 0);
//  }
  _TIMER_T_0(INDEX_TIMER_ACHR_CHAPV_100MS_1, TIMEOUT_ACHR_CHAPV_100MS, timer1, 0, UF1_is_larger_than_U_setpoint_F1, 0);
  //L1
//  UF1_is_smaller_than_U_setpoint_F1 = !UF1_is_larger_than_U_setpoint_F1;
 //L2, 3 
  int F1 = (int) (frequency * 100);
/*
  _Bool po_f1_achr_rab = F1 <= ((int)current_settings_prt.setpoint_achr1_f_rab[number_group_stp]);
  _Bool po_f1_chapv_rab = F1 >= ((int)current_settings_prt.setpoint_chapv1_f_rab[number_group_stp]);
  _Bool po_f1_achr = 0;
����������
*/
  _Bool po_f1_achr1_rab = F1 <= ((int)current_settings_prt.setpoint_achr1_f_rab[number_group_stp]);
  _Bool po_f1_chapv1_rab = F1 >= ((int)current_settings_prt.setpoint_chapv1_f_rab[number_group_stp]);
  _Bool po_f1_achr1 = 0;
  _Bool po_f1_achr2_rab = F1 <= ((int)current_settings_prt.setpoint_achr2_f_rab[number_group_stp]);
  _Bool po_f1_chapv2_rab = F1 >= ((int)current_settings_prt.setpoint_chapv2_f_rab[number_group_stp]);
  _Bool po_f1_achr2 = 0;
//----------

/*  
  //��
  unsigned int tmp_value = (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_ACHR1) != 0) << 0;
  //L5
  _INVERTOR(tmp_value, 0, tmp_value, 0);
����������
*/
  //��
  unsigned int tmp_value1 = (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_ACHR1) != 0) << 0;
  //L5.1
  _INVERTOR(tmp_value1, 0, tmp_value1, 0);
  //��
  unsigned int tmp_value2 = (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_ACHR2) != 0) << 0;
  //L5
  _INVERTOR(tmp_value2, 0, tmp_value2, 0);
//----------

/*  
  //�
  tmp_value |= ((current_settings_prt.control_achr_chapv & CTR_ACHR1) != 0) << 1;
  //L4
  _AND3_INVERTOR(tmp_value, 0, tmp_value, 1, UF1_is_larger_than_U_setpoint_F1, 0, tmp_value, 3);
����������
*/
  //�
  tmp_value1 |= ((current_settings_prt.control_achr_chapv & CTR_ACHR1) != 0) << 1;
  //L4.1
  _AND3_INVERTOR(tmp_value1, 0, tmp_value1, 1, UF1_is_larger_than_U_setpoint_F1, 0, tmp_value1, 3);
  //�
  tmp_value2 |= ((current_settings_prt.control_achr_chapv & CTR_ACHR2) != 0) << 1;
  //L4.2
  _AND3_INVERTOR(tmp_value2, 0, tmp_value2, 1, UF1_is_larger_than_U_setpoint_F1, 0, tmp_value2, 3);
//----------
/*
  //Reset ����� L2
  if (!_GET_OUTPUT_STATE(tmp_value, 3))
  {
    //�� ���1
    if (previous_state_po_f1_achr) 
    {
      //���������� ���
//  _Bool po_f1_chapv_rab = F1 >= ((int)current_settings_prt.setpoint_chapv1_f_rab[number_group_stp]);
      if (!po_f1_chapv_rab) 
      {
        //����� �������� 1 ����� ��������� �� ��� ��� ���� �� ��������� po_f1_chapv_rab (������� ����������)
        _SET_BIT(p_active_functions, RANG_PO_ACHR1);
        po_f1_achr = 1;
      }
    }
    else
    {
      //��������
//  _Bool po_f1_achr_rab = F1 <= ((int)current_settings_prt.setpoint_achr1_f_rab[number_group_stp]);
      
      if (po_f1_achr_rab)
      {
        _SET_BIT(p_active_functions, RANG_PO_ACHR1);
        po_f1_achr = 1;
      }
    }
  }//if
����������
*/
//---1----
  //Reset ����� L2
  if (!_GET_OUTPUT_STATE(tmp_value1, 3))
  {
    //�� ���1
    if (previous_state_po_f1_achr1) 
    {
      //���������� ���
//  _Bool po_f1_chapv_rab = F1 >= ((int)current_settings_prt.setpoint_chapv1_f_rab[number_group_stp]);
      if (!po_f1_chapv1_rab) 
      {
        //����� �������� 1 ����� ��������� �� ��� ��� ���� �� ��������� po_f1_chapv_rab (������� ����������)
        _SET_BIT(p_active_functions, RANG_PO_ACHR1);
        po_f1_achr1 = 1;
      }
      else _CLEAR_BIT(p_active_functions, RANG_PO_ACHR1);
    }
    else
    {
      //��������
//  _Bool po_f1_achr_rab = F1 <= ((int)current_settings_prt.setpoint_achr1_f_rab[number_group_stp]);
      
      if (po_f1_achr1_rab)
      {
        _SET_BIT(p_active_functions, RANG_PO_ACHR1);
        po_f1_achr1 = 1;
      }
      else _CLEAR_BIT(p_active_functions, RANG_PO_ACHR1);
    }
  }//if
  else
  {
    _CLEAR_BIT(p_active_functions, RANG_PO_ACHR1);
  }
//----2----
  //Reset ����� L2
  if (!_GET_OUTPUT_STATE(tmp_value2, 3))
  {
    //�� ���1
    if (previous_state_po_f1_achr2) 
    {
      //���������� ���
//  _Bool po_f1_chapv_rab = F1 >= ((int)current_settings_prt.setpoint_chapv1_f_rab[number_group_stp]);
      if (!po_f1_chapv2_rab) 
      {
        //����� �������� 1 ����� ��������� �� ��� ��� ���� �� ��������� po_f1_chapv_rab (������� ����������)
        _SET_BIT(p_active_functions, RANG_PO_ACHR2);
        po_f1_achr2 = 1;
      }
      else _CLEAR_BIT(p_active_functions, RANG_PO_ACHR2);
    }
    else
    {
      //��������
//  _Bool po_f1_achr_rab = F1 <= ((int)current_settings_prt.setpoint_achr1_f_rab[number_group_stp]);
      
      if (po_f1_achr2_rab)
      {
        _SET_BIT(p_active_functions, RANG_PO_ACHR2);
        po_f1_achr2 = 1;
      }
      else _CLEAR_BIT(p_active_functions, RANG_PO_ACHR2);
    }
  }//if
  else
  {
    _CLEAR_BIT(p_active_functions, RANG_PO_ACHR2);
  }
//--------------  
/*
  _TIMER_T_0(INDEX_TIMER_ACHR1, current_settings_prt.timeout_achr_1[number_group_stp], po_f1_achr, 0, tmp_value, 5);
����������
*/
//---1---
  _TIMER_T_0(INDEX_TIMER_ACHR1, current_settings_prt.timeout_achr_1[number_group_stp], po_f1_achr1, 0, tmp_value1, 5);
//---2---
  _TIMER_T_0(INDEX_TIMER_ACHR2, current_settings_prt.timeout_achr_2[number_group_stp], po_f1_achr2, 0, tmp_value2, 5);
//-------
  
  //���� ����
  if (UF1_is_larger_than_U_setpoint_F1)
    _SET_BIT(p_active_functions, RANG_RAZR_CHAPV);
  else
    _CLEAR_BIT(p_active_functions, RANG_RAZR_CHAPV);

/*  
  _Bool tmp1 = 0;
  do 
  {
    //L7
    _OR2(tmp_value, 3, !trigger_CHAPV1, 0, tmp_value, 30);
    
    //�� ����1
    _Bool po_f1_chapv = 0;
    if (previous_state_po_f1_chapv) 
    {
      po_f1_chapv = !po_f1_achr_rab;
    }
    else 
    {
      po_f1_chapv = po_f1_chapv_rab;
    }
    //L3
    _Bool po_f1_chapv_tmp = (!_GET_OUTPUT_STATE(tmp_value, 30) && po_f1_chapv);
    if (po_f1_chapv_tmp) 
    {
      _SET_BIT(p_active_functions, RANG_PO_CHAPV1);
    }
    
    _TIMER_T_0(INDEX_TIMER_CHAPV1, current_settings_prt.timeout_chapv_1[number_group_stp], po_f1_chapv_tmp, 0, tmp_value, 6);
    //L8
    _AND2(po_f1_achr, 0, !po_f1_chapv_tmp, 0, tmp_value, 12);
    //L9
    _OR2(tmp_value, 5, tmp_value, 6, tmp_value, 13);

    _D_TRIGGER(_GET_OUTPUT_STATE(tmp_value, 12), 0, _GET_OUTPUT_STATE(UF1_is_smaller_than_U_setpoint_F1, 0), previous_states_CHAPV1, 0, tmp_value, 13, trigger_CHAPV1, 0);
    if (tmp1 == trigger_CHAPV1) break;
    
    tmp1 = trigger_CHAPV1;
  } 
  while(1);
����������
*/
//----1----
  _Bool tmp1_1 = 0;
  do 
  {
    //L7_1
    _OR2(tmp_value1, 3, !trigger_CHAPV1, 0, tmp_value1, 30);
    
    //�� ����1
    _Bool po_f1_chapv1 = 0;
    if (previous_state_po_f1_chapv1) 
    {
      po_f1_chapv1 = !po_f1_achr1_rab;
    }
    else 
    {
      po_f1_chapv1 = po_f1_chapv1_rab;
    }
    //L3
    _Bool po_f1_chapv1_tmp = (!_GET_OUTPUT_STATE(tmp_value1, 30) && po_f1_chapv1);
    if (po_f1_chapv1_tmp) 
      _SET_BIT(p_active_functions, RANG_PO_CHAPV1);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_CHAPV1);
    
    _TIMER_T_0(INDEX_TIMER_CHAPV1, current_settings_prt.timeout_chapv_1[number_group_stp], po_f1_chapv1_tmp, 0, tmp_value1, 6);
    //L8
    _AND2(po_f1_achr1, 0, !po_f1_chapv1_tmp, 0, tmp_value1, 12);
    //L9
    _OR2(tmp_value1, 5, tmp_value1, 6, tmp_value1, 13);

    _D_TRIGGER(_GET_OUTPUT_STATE(tmp_value1, 12), 0, _GET_OUTPUT_STATE(tmp_value1, 3), previous_states_CHAPV1, 0, tmp_value1, 13, trigger_CHAPV1, 0);
    if (tmp1_1 == trigger_CHAPV1) break;
    
    tmp1_1 = trigger_CHAPV1;
  } 
  while(1);
//----2----
  _Bool tmp1_2 = 0;
  do 
  {
    //L7_2
    _OR2(tmp_value2, 3, !trigger_CHAPV2, 0, tmp_value2, 30);
    
    //�� ����2
    _Bool po_f1_chapv2 = 0;
    if (previous_state_po_f1_chapv2) 
    {
      po_f1_chapv2 = !po_f1_achr2_rab;
    }
    else 
    {
      po_f1_chapv2 = po_f1_chapv2_rab;
    }
    //L3_2
    _Bool po_f1_chapv2_tmp = (!_GET_OUTPUT_STATE(tmp_value2, 30) && po_f1_chapv2);
    if (po_f1_chapv2_tmp) 
      _SET_BIT(p_active_functions, RANG_PO_CHAPV2);
    else
      _CLEAR_BIT(p_active_functions, RANG_PO_CHAPV2);
    
    _TIMER_T_0(INDEX_TIMER_CHAPV2, current_settings_prt.timeout_chapv_2[number_group_stp], po_f1_chapv2_tmp, 0, tmp_value2, 6);
    //L8_2
    _AND2(po_f1_achr2, 0, !po_f1_chapv2_tmp, 0, tmp_value2, 12);
    //L9_2
    _OR2(tmp_value2, 5, tmp_value2, 6, tmp_value2, 13);

    _D_TRIGGER(_GET_OUTPUT_STATE(tmp_value2, 12), 0, _GET_OUTPUT_STATE(tmp_value2, 3), previous_states_CHAPV2, 0, tmp_value2, 13, trigger_CHAPV2, 0);
    if (tmp1_2 == trigger_CHAPV2) break;
    
    tmp1_2 = trigger_CHAPV2;
  } 
  while(1);
//---------
/*  
  //���/����
  if (_GET_OUTPUT_STATE(trigger_CHAPV1, 0)) 
  {
    _SET_BIT(p_active_functions, RANG_ACHR_CHAPV1);
  }
  
  _Bool chapv_timer_1ms = 0;
  _Bool razr_chapv_inv = 0;
  _TIMER_0_T(INDEX_TIMER_CHAPV_1MS, TIMEOUT_CHAPV_1MS, trigger_CHAPV1, 0, chapv_timer_1ms, 0);
  _INVERTOR(UF1_is_larger_than_U_setpoint_F1, 0, razr_chapv_inv, 0);
  _AND2(chapv_timer_1ms, 0, razr_chapv_inv, 0, tmp_value, 24);
  _TIMER_0_T(INDEX_TIMER_BLOCK_CHAPV_5MS, TIMEOUT_BLOCK_CHAPV_5MS, tmp_value, 24, tmp_value, 25);
����������
*/
//----1----
  //���/����
  if (_GET_OUTPUT_STATE(trigger_CHAPV1, 0)) 
    _SET_BIT(p_active_functions, RANG_ACHR_CHAPV1);
  else
    _CLEAR_BIT(p_active_functions, RANG_ACHR_CHAPV1);

//----2----
  //���/����
  if (_GET_OUTPUT_STATE(trigger_CHAPV2, 0)) 
    _SET_BIT(p_active_functions, RANG_ACHR_CHAPV2);
  else
    _CLEAR_BIT(p_active_functions, RANG_ACHR_CHAPV2);

  //���������� ����
  unsigned int tmp_value_g = 0;
  _TIMER_0_T(INDEX_TIMER_CHAPV1_1MS, TIMEOUT_CHAPV_1MS, trigger_CHAPV1, 0, tmp_value_g, 0);
  _TIMER_0_T(INDEX_TIMER_CHAPV2_1MS, TIMEOUT_CHAPV_1MS, trigger_CHAPV2, 0, tmp_value_g, 1);
  
  _AND2(tmp_value_g, 0, tmp_value1, 3, tmp_value_g, 2);
  _AND2(tmp_value_g, 1, tmp_value2, 3, tmp_value_g, 3);
  
  _TIMER_0_T(INDEX_TIMER_BLOCK_CHAPV1_5MS, TIMEOUT_BLOCK_CHAPV_5MS, tmp_value_g, 2, tmp_value_g, 4);
  _TIMER_0_T(INDEX_TIMER_BLOCK_CHAPV2_5MS, TIMEOUT_BLOCK_CHAPV_5MS, tmp_value_g, 3, tmp_value_g, 5);
  
  _OR2(tmp_value_g, 4, tmp_value_g, 5, tmp_value_g, 6);

  if (_GET_OUTPUT_STATE(tmp_value_g, 6))
      _SET_BIT(p_active_functions, RANG_VN_BLOCK_CHAPV);
  else
      _CLEAR_BIT(p_active_functions, RANG_VN_BLOCK_CHAPV);
}

/*****************************************************/

/*****************************************************/
// ���������� � ��
/*****************************************************/
void ready_tu(unsigned int *p_active_functions)
{
  unsigned int tmp_value = (_CHECK_SET_BIT(p_active_functions, RANG_PRYVID_VV) == 0)                  << 0;
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_VIDKL_VID_ZAKHYSTIV) != 0)                    << 1;
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV) != 0)      << 2;
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_AVAR_DEFECT) == 0)                            << 3;
  tmp_value |= (_CHECK_SET_BIT(p_active_functions, RANG_MISCEVE_DYSTANCIJNE) == 0)                    << 6;
  
  _Bool ctrl_ready_tu = ((current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_CTRL_READY_TU) == 0);
  
  if (!previous_states_ready_tu && _GET_OUTPUT_STATE(tmp_value, 1)) {
    previous_states_ready_tu = 0;
  }
  
  _OR2(tmp_value, 2, ctrl_ready_tu, 0, tmp_value, 7);
  _D_TRIGGER(1, 0, _GET_OUTPUT_STATE(tmp_value, 7), previous_states_ready_tu, 0, tmp_value, 1, trigger_ready_tu, 0);
  
  _AND4(tmp_value, 0, tmp_value, 3, !trigger_ready_tu, 0, tmp_value, 6, tmp_value, 5);
  
  //���������� � ��
  if (_GET_OUTPUT_STATE(tmp_value, 5))
    _SET_BIT(p_active_functions, RANG_READY_TU);
  else
    _CLEAR_BIT(p_active_functions, RANG_READY_TU);
}
/*****************************************************/

/*****************************************************/
// ����
/*****************************************************/
inline void urov_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
  /*******************************/
  //��������� ������������ ������� ����� ��� ����
  /*******************************/
  unsigned int max_faze_current = measurement[IM_IA];
  if (max_faze_current < measurement[IM_IB]) max_faze_current = measurement[IM_IB];
  if (max_faze_current < measurement[IM_IC]) max_faze_current = measurement[IM_IC];
  /*******************************/
  
  /*******************************/
  uint32_t state_UROV = (( current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STATE)) != 0);
  uint32_t start_from_UP = false;
  if (
      (state_UROV != 0) &&
      ((current_settings_prt.control_urov & (((uint64_t)(MASKA_FOR_BIT(NUMBER_UP) - 1)) << INDEX_ML_CTRUROV_STARTED_FROM_UP1)) != 0)
     )   
  {
    //����������� ������ ���� �� ��
    for (size_t n_UP = 0; n_UP < NUMBER_UP; n_UP++)
    {
      if ( 
          ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_UP1 + n_UP)) != 0) && 
          (_CHECK_SET_BIT(p_active_functions, (RANG_UP1 + 3*n_UP)      ) != 0)
         )
      {
        start_from_UP = true;
      }
    }
  }
  
  if(
     (state_UROV != 0) &&
     (
      (start_from_UP == true) ||
      (_CHECK_SET_BIT(p_active_functions, RANG_PUSK_UROV_VID_DV) != 0) ||
        
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_DZ1)    ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_DZ1              ) != 0)) ||
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_AMTDZ1) ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_AMTZ_DZ1         ) != 0)) ||
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_DZ2)    ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_DZ2              ) != 0)) ||
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_AMTDZ2) ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_AMTZ_DZ2         ) != 0)) ||
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_DZ3)    ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_DZ3              ) != 0)) ||
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_AMTDZ3) ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_AMTZ_DZ3         ) != 0)) ||
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_DZ4)    ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_DZ4              ) != 0)) ||
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_AMTDZ4) ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_AMTZ_DZ4         ) != 0)) ||
        
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_MTZ1)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_MTZ1             ) != 0)) ||
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_MTZ2)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_MTZ2             ) != 0)) ||
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_MTZ3)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_MTZ3             ) != 0)) ||
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_MTZ4)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_MTZ4             ) != 0)) ||
        
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_ZDZ)    ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_ZDZ              ) != 0)) ||
        
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_3I0)    ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_3I0              ) != 0)) ||
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_3U0)    ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_3U0              ) != 0)) ||
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_NZZ)    ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_NZZ              ) != 0)) ||
        
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_TZNP1)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_TZNP1            ) != 0)) ||
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_TZNP2)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_TZNP2            ) != 0)) ||
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_TZNP3)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_TZNP3            ) != 0)) ||
        
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_ZOP1)   ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_ZOP              ) != 0)) ||
        
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_UMIN1)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_UMIN1            ) != 0)) ||
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_UMIN2)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_UMIN2            ) != 0)) ||
        
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_UMAX1)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_UMAX1            ) != 0)) ||
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_UMAX2)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_UMAX2            ) != 0)) ||
        
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_ACHR1)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_ACHR_CHAPV1      ) != 0)) ||
      ( ((current_settings_prt.control_urov & MASKA64_FOR_BIT(INDEX_ML_CTRUROV_STARTED_FROM_ACHR2)  ) != 0) && (_CHECK_SET_BIT(p_active_functions, RANG_ACHR_CHAPV2      ) != 0))
     )     
    )
  {
    //� ����� ������� ����
    
    unsigned int setpoint; //������� - � ���� ���������� ����������� ��������
    unsigned int previous_state_po_urov;
    
    //���� �� ���� �� �� �������, �� ����� ��������� �� ������ ���������� - �������, ��� ��������� �� ������� � ������� ���� �� ��������� ����
    //���� �� ���� ��� ����������, �� ����� ��������� �� ������� ���������� - �������� ������� �� ������� ������ �� ����������� ����������
    if(( previous_state_po_urov = _CHECK_SET_BIT(p_active_functions, RANG_PO_UROV) ) ==0 )
    {
      //�������� �� ������ �����������
      setpoint = current_settings_prt.setpoint_urov[number_group_stp];
    }
    else
    {
      //�������� �� ������ ����������
      setpoint = current_settings_prt.setpoint_urov[number_group_stp]*KOEF_POVERNENNJA_GENERAL_UP/100;
    }
    
    //�����������, ��� ������� ������ "�� ����"
    if (max_faze_current >= setpoint)
    {
      //������������ ������ ���� �������� ���� �������
      if(previous_state_po_urov == 0)
      {
        //������������ ������ "�� ����"
        _SET_BIT(p_active_functions, RANG_PO_UROV);
      
        //��������� ������� ����1 � ����2, ���� ���� �� �� �������
        global_timers[INDEX_TIMER_UROV1] = 0;
        global_timers[INDEX_TIMER_UROV2] = 0;
      }
    }
    else 
    {
      //������������ ������ ���� ����� �������
      if(previous_state_po_urov != 0)
      {
        //������� ������ "�� ����"
        _CLEAR_BIT(p_active_functions, RANG_PO_UROV);
        //�� � ������ ����� �������� ������� "����. ����1" � "����. ����2"
        _CLEAR_BIT(p_active_functions, RANG_UROV1);
        _CLEAR_BIT(p_active_functions, RANG_UROV2);
        //���� ������� �� �� ������, �� ������� ��
        if ( global_timers[INDEX_TIMER_UROV1] >=0) global_timers[INDEX_TIMER_UROV1] = -1;
        if ( global_timers[INDEX_TIMER_UROV2] >=0) global_timers[INDEX_TIMER_UROV2] = -1;
      }
    }
    
    //���������� �� ������ ����1 �������� �������� �� ��������
    if(global_timers[INDEX_TIMER_UROV1] >= current_settings_prt.timeout_urov_1[number_group_stp])
    {
      //���� ��������� �������� ����1 �� ������������ ������ "����. ����1"
      _SET_BIT(p_active_functions, RANG_UROV1);

      //������� ������ ����1
      global_timers[INDEX_TIMER_UROV1] = -1;
    }

    //���������� �� ������ ����2 �������� �������� �� ��������
    if(global_timers[INDEX_TIMER_UROV2] >= current_settings_prt.timeout_urov_2[number_group_stp])
    {
      //���� ��������� �������� ����2 �� ������������ ������ "����. ����2"
      _SET_BIT(p_active_functions, RANG_UROV2);

      //������� ������ ����2
      global_timers[INDEX_TIMER_UROV2] = -1;
    }
  }
  else
  {
    //����� ������� �� ������� � �������, �� �� ���� ����������
    _CLEAR_BIT(p_active_functions, RANG_PO_UROV);
    _CLEAR_BIT(p_active_functions, RANG_UROV1);
    _CLEAR_BIT(p_active_functions, RANG_UROV2);
    global_timers[INDEX_TIMER_UROV1] = -1;
    global_timers[INDEX_TIMER_UROV2] = -1;
  }  
}
  /*******************************/
/*****************************************************/

/*****************************************************/
//���
/*****************************************************/
inline void apv_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
  unsigned int logic_APV_0 = 0;
  unsigned int logic_APV_1 = 0;
  unsigned int logic_APV_2 = 0;
  unsigned int logic_APV_3 = 0;

  //������� ��������
  logic_APV_1 |= (start_restart != 0) << 19;
  //������� ����������� ��� ������� ��������
  start_restart = 0;

  //"���� ��������"
  logic_APV_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_STATE_VV) != 0) << 21;
  _TIMER_IMPULSE(INDEX_TIMER_APV_BLOCK_VID_VV, current_settings_prt.timeout_apv_block_vid_VV[number_group_stp], previous_states_APV_0, 0, logic_APV_0, 21, logic_APV_0, 22);

  //"�������� ����������"
  logic_APV_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_STAT_BLK_APV) != 0) << 0;
  _INVERTOR(logic_APV_0, 0, logic_APV_0, 1);

  //�:"���� �� ���1"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_MTZ1) != 0) << 2;
  //"���1"
  logic_APV_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_MTZ1) != 0) << 3;
  _AND2(logic_APV_0, 2, logic_APV_0, 3, logic_APV_0, 4);

  //�:"���� �� ���2"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_MTZ2) != 0) << 5;
  //"���2"
  logic_APV_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_MTZ2) != 0) << 6;
  _AND2(logic_APV_0, 5, logic_APV_0, 6, logic_APV_0, 7);

  //�:"���� �� ���3"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_MTZ3) != 0) << 8;
  //"���3"
  logic_APV_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_MTZ3) != 0) << 9;
  _AND2(logic_APV_0, 8, logic_APV_0, 9, logic_APV_0, 10);

  //�:"���� �� ���4"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_MTZ4) != 0) << 11;
  //"���4"
  logic_APV_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_MTZ4) != 0) << 12;
  _AND2(logic_APV_0, 11, logic_APV_0, 12, logic_APV_0, 13);
  
  /***/

  //�:"���� �� ��1"
  logic_APV_1 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_DZ1) != 0) << 30;
  //"��1"
  logic_APV_1 |= (_CHECK_SET_BIT(p_active_functions, RANG_DZ1) != 0) << 31;
  _AND2(logic_APV_1, 30, logic_APV_1, 31, logic_APV_2, 20);

  //�:"���� �� ��2"
  logic_APV_2 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_DZ2) != 0) << 0;
  //"��2"
  logic_APV_2 |= (_CHECK_SET_BIT(p_active_functions, RANG_DZ2) != 0) << 1;
  _AND2(logic_APV_2, 0, logic_APV_2, 1, logic_APV_2, 21);

  //�:"���� �� ��3"
  logic_APV_2 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_DZ3) != 0) << 2;
  //"��3"
  logic_APV_2 |= (_CHECK_SET_BIT(p_active_functions, RANG_DZ3) != 0) << 3;
  _AND2(logic_APV_2, 2, logic_APV_2, 3, logic_APV_2, 22);

  //�:"���� �� ��4"
  logic_APV_2 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_DZ4) != 0) << 4;
  //"��4"
  logic_APV_2 |= (_CHECK_SET_BIT(p_active_functions, RANG_DZ4) != 0) << 5;
  _AND2(logic_APV_2, 4, logic_APV_2, 5, logic_APV_2, 23);

  _OR4(logic_APV_2, 20, logic_APV_2, 21, logic_APV_2, 22, logic_APV_2, 23, logic_APV_2, 31);

  //�:"���� �� ����1"
  logic_APV_2 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_AMTDZ1) != 0) << 6;
  //"����1"
  logic_APV_2 |= (_CHECK_SET_BIT(p_active_functions, RANG_AMTZ_DZ1) != 0) << 7;
  _AND2(logic_APV_2, 6, logic_APV_2, 7, logic_APV_2, 24);

  //�:"���� �� ����2"
  logic_APV_2 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_AMTDZ2) != 0) << 8;
  //"����2"
  logic_APV_2 |= (_CHECK_SET_BIT(p_active_functions, RANG_AMTZ_DZ2) != 0) << 9;
  _AND2(logic_APV_2, 8, logic_APV_2, 9, logic_APV_2, 25);

  //�:"���� �� ����3"
  logic_APV_2 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_AMTDZ3) != 0) << 10;
  //"����3"
  logic_APV_2 |= (_CHECK_SET_BIT(p_active_functions, RANG_AMTZ_DZ3) != 0) << 11;
  _AND2(logic_APV_2, 10, logic_APV_2, 11, logic_APV_2, 26);

  //�:"���� �� ����4"
  logic_APV_2 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_AMTDZ4) != 0) << 12;
  //"����4"
  logic_APV_2 |= (_CHECK_SET_BIT(p_active_functions, RANG_AMTZ_DZ4) != 0) << 13;
  _AND2(logic_APV_2, 12, logic_APV_2, 13, logic_APV_2, 27);

  _OR4(logic_APV_2, 24, logic_APV_2, 25, logic_APV_2, 26, logic_APV_2, 27, logic_APV_3, 0);

  //�:"���� �� ����1"
  logic_APV_2 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_TZNP1) != 0) << 14;
  //"����1"
  logic_APV_2 |= (_CHECK_SET_BIT(p_active_functions, RANG_TZNP1) != 0) << 15;
  _AND2(logic_APV_2, 14, logic_APV_2, 15, logic_APV_2, 28);

  //�:"���� �� ����2"
  logic_APV_2 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_TZNP2) != 0) << 16;
  //"����2"
  logic_APV_2 |= (_CHECK_SET_BIT(p_active_functions, RANG_TZNP2) != 0) << 17;
  _AND2(logic_APV_2, 16, logic_APV_2, 17, logic_APV_2, 29);

  //�:"���� �� ����3"
  logic_APV_2 |= ((current_settings_prt.control_apv & CTR_APV_STARTED_FROM_TZNP3) != 0) << 18;
  //"����3"
  logic_APV_2 |= (_CHECK_SET_BIT(p_active_functions, RANG_TZNP3) != 0) << 19;
  _AND2(logic_APV_2, 18, logic_APV_2, 19, logic_APV_2, 30);
  
  _OR3(logic_APV_2, 28, logic_APV_2, 29, logic_APV_2, 30, logic_APV_3, 1);
  /***/
  
  _OR4(logic_APV_0,  4, logic_APV_0,  7, logic_APV_0, 10, logic_APV_0, 13, logic_APV_0, 14);
  _OR4(logic_APV_0, 14, logic_APV_2, 31, logic_APV_3,  0, logic_APV_3,  1, logic_APV_3,  2);

  //�:"����.�����.��.��"
  logic_APV_3 |= ((current_settings_prt.control_apv & CTR_APV_CTRAPV_BLK_CTRL_VV) != 0) << 11;
  _INVERTOR(logic_APV_3, 11, logic_APV_3, 12);
  _AND2(logic_APV_0, 21, logic_APV_3, 11, logic_APV_3, 13);
  _OR3(logic_APV_3, 13, logic_APV_3, 12, previous_states_APV_0, 9, logic_APV_3, 3);
  _AND2(logic_APV_3, 2, logic_APV_3, 3, previous_states_APV_0, 9);

  _TIMER_0_T(INDEX_TIMER_APV_TMP1, 1, previous_states_APV_0, 9, logic_APV_0, 15);

  //�:"���� 1"
  logic_APV_0 |= ((current_settings_prt.control_achr_chapv & CTR_CHAPV1) != 0) << 16;
  //"���/���� 1"
  logic_APV_1 |= (_CHECK_SET_BIT(p_active_functions, RANG_ACHR_CHAPV1) != 0) << 21;
  //�:"���� 2"
  logic_APV_1 |= ((current_settings_prt.control_achr_chapv & CTR_CHAPV2) != 0) << 27;
  //"���/���� 2"
  logic_APV_1 |= (_CHECK_SET_BIT(p_active_functions, RANG_ACHR_CHAPV2) != 0) << 28;
  //"���� ����"
  logic_APV_1 |= (_CHECK_SET_BIT(p_active_functions, RANG_RAZR_CHAPV) != 0) << 20;

  //"���/���� �� ��"
  logic_APV_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_ACHR_CHAPV_VID_DV) != 0) << 17;
  //�:"���� �� ��"
  logic_APV_1 |= ((current_settings_prt.control_achr_chapv & CTR_CHAPV_VID_DV) != 0) << 22;
  
  _AND3(logic_APV_0, 16, logic_APV_1, 21, logic_APV_1, 20, logic_APV_1, 23);
  _AND3(logic_APV_1, 27, logic_APV_1, 28, logic_APV_1, 20, logic_APV_1, 29);
  _AND2(logic_APV_0, 17, logic_APV_1, 22, logic_APV_1, 24);
  _OR3(logic_APV_1, 23, logic_APV_1, 29, logic_APV_1, 24, logic_APV_0, 18)

  //"����.����"
  logic_APV_1 |= (_CHECK_SET_BIT(p_active_functions, RANG_VN_BLOCK_CHAPV) != 0) << 25;
  _OR2(logic_APV_0, 18, logic_APV_1, 25, logic_APV_1, 26);
    
  _TIMER_0_T(INDEX_TIMER_ACHR_CHAPV, MAX_VALUE_TIMER_FOR_COUNT_SIGNAL_ACHR_CHAPV, logic_APV_0, 18, logic_APV_0, 19);

  _OR2_INVERTOR(logic_APV_0, 15, logic_APV_0, 19, logic_APV_0, 20);

  //�:"���"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STAGE_1) != 0) << 23;
  _INVERTOR(logic_APV_0, 23, logic_APV_0, 24);

  //�:"���2"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STAGE_2) != 0) << 25;
  _INVERTOR(logic_APV_0, 25, logic_APV_0, 26);

  //�:"���3"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STAGE_3) != 0) << 27;
  _INVERTOR(logic_APV_0, 27, logic_APV_0, 28);

  //�:"���4"
  logic_APV_0 |= ((current_settings_prt.control_apv & CTR_APV_STAGE_4) != 0) << 29;
  _INVERTOR(logic_APV_0, 29, logic_APV_0, 30);

  //������� �������� ����������� ���������� ���� �� ������� �� ������������� � ���������� ����
  logic_APV_0 |= _GET_OUTPUT_STATE(previous_states_APV_0, 1) << 31;
  logic_APV_1 |= _GET_OUTPUT_STATE(previous_states_APV_0, 2) <<  0;
  logic_APV_1 |= _GET_OUTPUT_STATE(previous_states_APV_0, 3) <<  1;
  logic_APV_1 |= _GET_OUTPUT_STATE(previous_states_APV_0, 4) <<  2;
  
  logic_APV_3 |= (_CHECK_SET_BIT(p_active_functions, RANG_UROV2) != 0) << 4;
  logic_APV_3 |= ((current_settings_prt.control_apv & CTR_APV_CTRAPV_BLK_CTRL_PRVV2) != 0) << 6;
  _AND2(logic_APV_3, 4, logic_APV_3, 6, logic_APV_3, 14);
  _TIMER_0_T(INDEX_TIMER_APV_TMP2, 40, logic_APV_3, 14, logic_APV_3, 5);

  unsigned int previous_trigger_APV_0;
  
  /*
  ������� �������� �� �������, �� � ���� do-while ������ �� ����������,
  ��� ���� ����������� �� ��� ������ �� �������� ������, ���� �, ��������, ����
  �������� �������� ��� �������.
  ��� ����������� ����������� ��� �������, �� �� ������� ��� ����� ������, �
  � ���� ������ ����� ����������
  */
  _CLEAR_BIT(p_active_functions, RANG_APV1);
  _CLEAR_BIT(p_active_functions, RANG_APV2);
  _CLEAR_BIT(p_active_functions, RANG_APV3);
  _CLEAR_BIT(p_active_functions, RANG_APV4);
  do
  {
    /***
    Գ����� �������� ���� �������, �� ����, �������, �������� � �� ����
    ����� ���� �������� ���������� ������������ �������
    ***/
    _CLEAR_STATE(previous_states_APV_0, 1);
    previous_states_APV_0 |= _GET_OUTPUT_STATE(logic_APV_0, 31) << 1;
    _CLEAR_STATE(previous_states_APV_0, 2);
    previous_states_APV_0 |= _GET_OUTPUT_STATE(logic_APV_1,  0) << 2;
    _CLEAR_STATE(previous_states_APV_0, 3);
    previous_states_APV_0 |= _GET_OUTPUT_STATE(logic_APV_1,  1) << 3;
    _CLEAR_STATE(previous_states_APV_0, 4);
    previous_states_APV_0 |= _GET_OUTPUT_STATE(logic_APV_1,  2) << 4;
    
    previous_trigger_APV_0 = trigger_APV_0;
    /***/
    
    _OR2(logic_APV_1, 2, logic_APV_1, 1, logic_APV_1, 3);
    
    
    //���1
    _OR6(logic_APV_1, 19, previous_states_APV_0, 9, trigger_APV_0, 1, trigger_APV_0, 2, trigger_APV_0, 3, logic_APV_0, 31, logic_APV_1, 4);
    _OR6(logic_APV_1, 26, logic_APV_0, 22, logic_APV_0, 24, logic_APV_1, 3, logic_APV_1, 0, logic_APV_1, 4, logic_APV_1, 8);
    _OR2(logic_APV_1, 8, logic_APV_3, 5, logic_APV_3, 7);
    _D_TRIGGER(_GET_OUTPUT_STATE(logic_APV_0, 1),  0, _GET_OUTPUT_STATE(logic_APV_3, 7), previous_states_APV_0, 5, logic_APV_0, 20, trigger_APV_0, 0);                 
    _TIMER_T_0(INDEX_TIMER_APV_1, current_settings_prt.timeout_apv_1[number_group_stp], trigger_APV_0, 0, logic_APV_1, 9);
    /*
    ��� ������ ����������� � ����� p_active_functions � ���� � ����������
    do-while, �� ��� �������� ����������� ��� ������, � ���� �� �����������, ��
    ��� ������ �� ������� ������ � ��� ������ ����������. ��� ������������ �� ��� "0"
    ���� ������������ "1" �� ���� � ����� ��� ������ � �� ���� ���� ����������� �� 
    �������� ������ ������� ������� (�������� ��� ������� ����������� �����
    ������ do-while).
    */
    if (_GET_OUTPUT_STATE(logic_APV_1, 9)) _SET_BIT(p_active_functions, RANG_APV1);
    _TIMER_0_T(INDEX_TIMER_APV_BLOCK_VID_APV1, current_settings_prt.timeout_apv_block_vid_apv1[number_group_stp], logic_APV_1, 9, logic_APV_0, 31);

    //���2
    _AND2_INVERTOR(logic_APV_0, 31, logic_APV_0, 15, logic_APV_1, 10);
    _OR6(logic_APV_1, 19, previous_states_APV_0, 9, trigger_APV_0, 0, trigger_APV_0, 2, trigger_APV_0, 3, logic_APV_1,  0, logic_APV_1, 5);
    _OR6(logic_APV_1, 26, logic_APV_0, 24, logic_APV_0, 26, logic_APV_1, 2, logic_APV_1, 1, logic_APV_1, 5, logic_APV_1, 11);
    _OR2(logic_APV_1, 11, logic_APV_3, 5, logic_APV_3, 8);
    _D_TRIGGER(1,  0, _GET_OUTPUT_STATE(logic_APV_3, 8), previous_states_APV_0, 6, logic_APV_1, 10, trigger_APV_0, 1);    
    _TIMER_T_0(INDEX_TIMER_APV_2, current_settings_prt.timeout_apv_2[number_group_stp], trigger_APV_0, 1, logic_APV_1, 12);
    /*
    ��� ������ ����������� � ����� p_active_functions � ���� � ����������
    do-while, �� ��� �������� ����������� ��� ������, � ���� �� �����������, ��
    ��� ������ �� ������� ������ � ��� ������ ����������. ��� ������������ �� ��� "0"
    ���� ������������ "1" �� ���� � ����� ��� ������ � �� ���� ���� ����������� �� 
    �������� ������ ������� ������� (�������� ��� ������� ����������� �����
    ������ do-while).
    */
    if (_GET_OUTPUT_STATE(logic_APV_1, 12)) _SET_BIT(p_active_functions, RANG_APV2);
    _TIMER_0_T(INDEX_TIMER_APV_BLOCK_VID_APV2, current_settings_prt.timeout_apv_block_vid_apv2[number_group_stp], logic_APV_1, 12, logic_APV_1, 0);

    //���3
    _AND2_INVERTOR(logic_APV_1, 0, logic_APV_0, 15, logic_APV_1, 13);
    _OR6(logic_APV_1, 19, previous_states_APV_0, 9, trigger_APV_0, 0, trigger_APV_0, 1, trigger_APV_0, 3, logic_APV_1,  1, logic_APV_1, 6);
    _OR5(logic_APV_1, 26, logic_APV_0, 24, logic_APV_0, 28, logic_APV_1, 2, logic_APV_1, 6, logic_APV_1, 14);
    _OR2(logic_APV_1, 14, logic_APV_3, 5, logic_APV_3, 9);
    _D_TRIGGER(1,  0, _GET_OUTPUT_STATE(logic_APV_3, 9), previous_states_APV_0, 7, logic_APV_1, 13, trigger_APV_0, 2);                 
    _TIMER_T_0(INDEX_TIMER_APV_3, current_settings_prt.timeout_apv_3[number_group_stp], trigger_APV_0, 2, logic_APV_1, 15);
    /*
    ��� ������ ����������� � ����� p_active_functions � ���� � ����������
    do-while, �� ��� �������� ����������� ��� ������, � ���� �� �����������, ��
    ��� ������ �� ������� ������ � ��� ������ ����������. ��� ������������ �� ��� "0"
    ���� ������������ "1" �� ���� � ����� ��� ������ � �� ���� ���� ����������� �� 
    �������� ������ ������� ������� (�������� ��� ������� ����������� �����
    ������ do-while).
    */
    if (_GET_OUTPUT_STATE(logic_APV_1, 15)) _SET_BIT(p_active_functions, RANG_APV3);
    _TIMER_0_T(INDEX_TIMER_APV_BLOCK_VID_APV3, current_settings_prt.timeout_apv_block_vid_apv3[number_group_stp], logic_APV_1, 15, logic_APV_1, 1);

    //���4
    _AND2_INVERTOR(logic_APV_1, 1, logic_APV_0, 15, logic_APV_1, 16);
    _OR6(logic_APV_1, 19, previous_states_APV_0, 9, trigger_APV_0, 0, trigger_APV_0, 1, trigger_APV_0, 2, logic_APV_1,  2, logic_APV_1, 7);
    _OR4(logic_APV_1, 26, logic_APV_0, 24, logic_APV_0, 30, logic_APV_1, 7, logic_APV_1, 17);
    _OR2(logic_APV_1, 17, logic_APV_3, 5, logic_APV_3, 10);
    _D_TRIGGER(1,  0, _GET_OUTPUT_STATE(logic_APV_3, 10), previous_states_APV_0, 8, logic_APV_1, 16, trigger_APV_0, 3);                 
    _TIMER_T_0(INDEX_TIMER_APV_4, current_settings_prt.timeout_apv_4[number_group_stp], trigger_APV_0, 3, logic_APV_1, 18);
    /*
    ��� ������ ����������� � ����� p_active_functions � ���� � ����������
    do-while, �� ��� �������� ����������� ��� ������, � ���� �� �����������, ��
    ��� ������ �� ������� ������ � ��� ������ ����������. ��� ������������ �� ��� "0"
    ���� ������������ "1" �� ���� � ����� ��� ������ � �� ���� ���� ����������� �� 
    �������� ������ ������� ������� (�������� ��� ������� ����������� �����
    ������ do-while).
    */
    if (_GET_OUTPUT_STATE(logic_APV_1, 18)) _SET_BIT(p_active_functions, RANG_APV4);
    _TIMER_0_T(INDEX_TIMER_APV_BLOCK_VID_APV4, current_settings_prt.timeout_apv_block_vid_apv4[number_group_stp], logic_APV_1, 18, logic_APV_1, 2);
  }
  while (
         (_GET_OUTPUT_STATE(logic_APV_0, 31) != _GET_OUTPUT_STATE(previous_states_APV_0, 1)) ||
         (_GET_OUTPUT_STATE(logic_APV_1,  0) != _GET_OUTPUT_STATE(previous_states_APV_0, 2)) ||
         (_GET_OUTPUT_STATE(logic_APV_1,  1) != _GET_OUTPUT_STATE(previous_states_APV_0, 3)) ||
         (_GET_OUTPUT_STATE(logic_APV_1,  2) != _GET_OUTPUT_STATE(previous_states_APV_0, 4)) ||
         ( trigger_APV_0                     !=  previous_trigger_APV_0                    )  
        );
  
  _Bool work_apv = 0;
  _OR4(trigger_APV_0, 0, trigger_APV_0, 1, trigger_APV_0, 2, trigger_APV_0, 3, work_apv, 0);
  
  //������ ���
  if (work_apv) _SET_BIT(p_active_functions, RANG_APV_WORK);
  else  _CLEAR_BIT(p_active_functions, RANG_APV_WORK);
  
}
/*****************************************************/

/*****************************************************/
// ������������ ������
/*****************************************************/
inline void up_handler(unsigned int *p_active_functions, unsigned int number_group_stp)
{
  for (size_t n_UP = 0; n_UP < NUMBER_UP; n_UP++)
  {
    uint32_t logic_UP_0 = 0;
    
    logic_UP_0 |= (
                   ((current_settings_prt.control_UP & MASKA_FOR_BIT(n_UP*(_CTR_UP_NEXT_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I) - _CTR_UP_PART_I) + CTR_UP_STATE_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I))) != 0)
                   &&
                   (_CHECK_SET_BIT(p_active_functions, (RANG_BLOCK_UP1 + 3*n_UP)) == 0)
                  ) << 0;

    int32_t pickup = current_settings_prt.setpoint_UP[n_UP][0][number_group_stp];
    if (
        (current_settings_prt.ctrl_UP_input[n_UP] == UP_CTRL_3I0) ||
        (current_settings_prt.ctrl_UP_input[n_UP] == UP_CTRL_3I0_others)
       ) 
    {
      if (_CHECK_SET_BIT(p_active_functions, (RANG_PO_UP1 + 3*n_UP)) != 0)
      {
        /*
        ���������� ��������� ������
        setpoint = (pickup*koef_povernennja/100)*10 =  pickup*koef_povernennja/10
        */
        pickup = (pickup * current_settings_prt.setpoint_UP_KP[n_UP][0][number_group_stp])/10;
      }
      else
      {
        pickup *= 10;
      }
        
    }
    else
    {
      if (_CHECK_SET_BIT(p_active_functions, (RANG_PO_UP1 + 3*n_UP)) != 0) pickup = (pickup * current_settings_prt.setpoint_UP_KP[n_UP][0][number_group_stp])/100;
    }

    unsigned int more_less = ((current_settings_prt.control_UP & MASKA_FOR_BIT(n_UP*(_CTR_UP_NEXT_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I) - _CTR_UP_PART_I) + CTR_UP_MORE_LESS_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I))) != 0);
    
    int32_t analog_value;
    uint32_t PQ = false;
    uint32_t bank_for_calc_power_tmp = (state_calc_power == false ) ? bank_for_calc_power : ((bank_for_calc_power ^ 0x1) & 0x1);

    switch (current_settings_prt.ctrl_UP_input[n_UP])
    {
    case UP_CTRL_Ia_Ib_Ic:
      {
        analog_value = measurement[IM_IA];

        unsigned int or_and = ((current_settings_prt.control_UP & MASKA_FOR_BIT(n_UP*(_CTR_UP_NEXT_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I) - _CTR_UP_PART_I) + CTR_UP_OR_AND_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I))) != 0);
        if (
            ((more_less == 0) && (or_and == 0)) ||
            ((more_less != 0) && (or_and != 0))
           )   
        {
         if ((uint32_t)analog_value < measurement[IM_IB]) analog_value = measurement[IM_IB];
         if ((uint32_t)analog_value < measurement[IM_IC]) analog_value = measurement[IM_IC];
        }
        else
        {
         if ((uint32_t)analog_value > measurement[IM_IB]) analog_value = measurement[IM_IB];
         if ((uint32_t)analog_value > measurement[IM_IC]) analog_value = measurement[IM_IC];
        }
        
        break;
      }
    case UP_CTRL_Ia:
      {
        analog_value = measurement[IM_IA];
        
        break;
      }
    case UP_CTRL_Ib:
      {
        analog_value = measurement[IM_IB];
        
        break;
      }
    case UP_CTRL_Ic:
      {
        analog_value = measurement[IM_IC];
        
        break;
      }
    case UP_CTRL_I1:
      {
        analog_value = measurement[IM_I1];
        
        break;
      }
    case UP_CTRL_I2:
      {
        analog_value = measurement[IM_I2];
        
        break;
      }
    case UP_CTRL_3I0_r:
      {
        analog_value = measurement[IM_3I0_r];
        
        break;
      }
    case UP_CTRL_3I0:
      {
        analog_value = measurement[IM_3I0];
        
        break;
      }
    case UP_CTRL_3I0_others:
      {
        analog_value = measurement[IM_3I0_other_g];
        
        break;
      }
    case UP_CTRL_Ua_Ub_Uc:
      {
        analog_value = measurement[IM_UA];
        
        unsigned int or_and = ((current_settings_prt.control_UP & MASKA_FOR_BIT(n_UP*(_CTR_UP_NEXT_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I) - _CTR_UP_PART_I) + CTR_UP_OR_AND_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I))) != 0);
        uint32_t analog_value_tmp = measurement[IM_UB];
        if (
            ((more_less == 0) && (or_and == 0)) ||
            ((more_less != 0) && (or_and != 0))
           )   
        {
          if ((uint32_t)analog_value < analog_value_tmp) analog_value = analog_value_tmp;
         
          analog_value_tmp = measurement[IM_UC];
          if ((uint32_t)analog_value < analog_value_tmp) analog_value = analog_value_tmp;
        }
        else
        {
          if ((uint32_t)analog_value > analog_value_tmp) analog_value = analog_value_tmp;
         
          analog_value_tmp = measurement[IM_UC];
          if ((uint32_t)analog_value > analog_value_tmp) analog_value = analog_value_tmp;
        }
        
        break;
      }
    case UP_CTRL_Ua:
      {
        analog_value = measurement[IM_UA];
        
        break;
      }
    case UP_CTRL_Ub:
      {
        analog_value = measurement[IM_UB];
        
        break;
      }
    case UP_CTRL_Uc:
      {
        analog_value = measurement[IM_UC];
        
        break;
      }
    case UP_CTRL_Uab_Ubc_Uca:
      {
        analog_value = measurement[IM_UAB];
        
        unsigned int or_and = ((current_settings_prt.control_UP & MASKA_FOR_BIT(n_UP*(_CTR_UP_NEXT_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I) - _CTR_UP_PART_I) + CTR_UP_OR_AND_BIT - (_CTR_UP_PART_II - _CTR_UP_PART_I))) != 0);
        uint32_t analog_value_tmp = measurement[IM_UBC];
        if (
            ((more_less == 0) && (or_and == 0)) ||
            ((more_less != 0) && (or_and != 0))
           )   
        {
          if ((uint32_t)analog_value < analog_value_tmp) analog_value = analog_value_tmp;
         
          analog_value_tmp = measurement[IM_UCA];
          if ((uint32_t)analog_value < analog_value_tmp) analog_value = analog_value_tmp;
        }
        else
        {
          if ((uint32_t)analog_value > analog_value_tmp) analog_value = analog_value_tmp;
         
          analog_value_tmp = measurement[IM_UCA];
          if ((uint32_t)analog_value > analog_value_tmp) analog_value = analog_value_tmp;
        }
        
        break;
      }
    case UP_CTRL_Uab:
      {
        analog_value = measurement[IM_UAB];
        
        break;
      }
    case UP_CTRL_Ubc:
      {
        analog_value = measurement[IM_UBC];
        
        break;
      }
    case UP_CTRL_Uca:
      {
        analog_value = measurement[IM_UCA];
        
        break;
      }
    case UP_CTRL_U1:
      {
        analog_value = measurement[IM_U1];
        
        break;
      }
    case UP_CTRL_U2:
      {
        analog_value = measurement[IM_U2];
        
        break;
      }
    case UP_CTRL_3U0:
      {
        analog_value = measurement[IM_3U0];
        
        break;
      }
    case UP_CTRL_P:
      {
        PQ = true;
        analog_value = P[bank_for_calc_power_tmp];
        
        break;
      }
    case UP_CTRL_Q:
      {
        PQ = true;
        analog_value = Q[bank_for_calc_power_tmp];
        
        break;
      }
    case UP_CTRL_S:
      {
        analog_value = S[bank_for_calc_power_tmp];
        
        break;
      }
    default:
      {
        //���������� ����� ����� �� ���� � ����
        total_error_sw_fixed(100);
      }
    }
    
    if (more_less)
    {
      if (PQ)
      {
        if (
            (
             (analog_value >= 0) &&
             (pickup >= 0)  
            )
            ||
            (
             (analog_value < 0) &&
             (pickup < 0)  
            ) 
           ) 
        {
          logic_UP_0 |= (abs(analog_value) <= abs(pickup)) << 1;
        }
      }
      else
      {
        logic_UP_0 |= (analog_value <= pickup) << 1;
      }
    }
    else
    {
      if (PQ)
      {
        if (
            (
             (analog_value >= 0) &&
             (pickup >= 0)  
            )
            ||
            (
             (analog_value < 0) &&
             (pickup < 0)  
            ) 
           ) 
        {
          logic_UP_0 |= (abs(analog_value) >= abs(pickup)) << 1;
        }
      }
      else
      {
        logic_UP_0 |= (analog_value >= pickup) << 1;
      }
    }

    _AND2(logic_UP_0, 0, logic_UP_0, 1, logic_UP_0, 2);
    if (_GET_OUTPUT_STATE(logic_UP_0, 2)) _SET_BIT(p_active_functions, (RANG_PO_UP1 + 3*n_UP));
    else _CLEAR_BIT(p_active_functions, (RANG_PO_UP1 + 3*n_UP));
    
    _TIMER_T_0(INDEX_TIMER_UP1 + n_UP, current_settings_prt.timeout_UP[n_UP][0][number_group_stp], logic_UP_0, 2, logic_UP_0, 3);
    if (_GET_OUTPUT_STATE(logic_UP_0, 3)) _SET_BIT(p_active_functions, (RANG_UP1 + 3*n_UP));
    else _CLEAR_BIT(p_active_functions, (RANG_UP1 + 3*n_UP));
  }
}
/*****************************************************/

/*****************************************************/
//������� ��������� ������� ��������� � ����������
/*****************************************************/
inline void on_off_handler(unsigned int *p_active_functions)
{
  static unsigned int previous_active_functions[N_BIG];
  unsigned int maska[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  /*********************/
  //�������� ����������� �������
  /*********************/
  //������  ����������
  if (global_timers[INDEX_TIMER_VIDKL_VV] >= 0)
  {
    //������ �� ����� �������� � �� ����� ����� ����� ��������� ���� ������
    if (global_timers[INDEX_TIMER_VIDKL_VV] >= current_settings_prt.timeout_swch_off)
    {
      //������ �������� ����� ������������� ��������
      global_timers[INDEX_TIMER_VIDKL_VV] = -1;
      //³������ � ����� �������, �� ����� �����������, �� ���� �� �� ���� ������������
      _CLEAR_BIT(p_active_functions, RANG_WORK_BO);
    }
    //����������� ������ ����� �� ������, �� ������ ���������� �� �� ���� ��������� � ����������� � ����� ����������� �������,
    //��� �� ����� ���� �� ��������, ��� ���������� ��������� �������� �� ���� ��� � ������� ��������� ������ ����� ��
    global_timers[INDEX_TIMER_BLK_VKL_VV] = 0;
  }
    
  //������  ���������� ���������
  if (global_timers[INDEX_TIMER_BLK_VKL_VV] >= 0)
  {
    //������ ���������� ��������� �� ����� �������� � �� ����� ����� ����� ��������� ���� ������
    if (global_timers[INDEX_TIMER_BLK_VKL_VV] >= current_settings_prt.timeout_swch_udl_blk_on)
    {
      //������ �������� ����� ������������� ��������
      global_timers[INDEX_TIMER_BLK_VKL_VV] = -1;
    }
  }

  //������  ���������
  if (global_timers[INDEX_TIMER_VKL_VV] >= 0)
  {
    //������ �� ����� �������� � �� ����� ����� ����� ��������� ���� ������

    //���� �� ����� ������ ������ ��������� ������, ��� ����, �� ������� �� � ���������� ��������� �� �� ������, �� ������ ��������� ����� �������
    if ((global_timers[INDEX_TIMER_VIDKL_VV] >= 0) || (global_timers[INDEX_TIMER_BLK_VKL_VV] >=0))
    {
      global_timers[INDEX_TIMER_VKL_VV] = -1;
      //³������ � ����� �������, �� ����� �����������, �� ���� �B �� ���� ������������
      _CLEAR_BIT(p_active_functions, RANG_WORK_BV);
    }
    else
    {
      //����������, �� ������ ��������� �� �������� ����� ������������ ��������
      if (global_timers[INDEX_TIMER_VKL_VV] >= current_settings_prt.timeout_swch_on)
      {
        //������ �������� ����� ������������� ��������
        global_timers[INDEX_TIMER_VKL_VV] = -1;
        //³������ � ����� �������, �� ����� �����������, �� ���� �B �� ���� ������������
        _CLEAR_BIT(p_active_functions, RANG_WORK_BV);
      }
    }
  }
  /*********************/

  /*********************/
  //������ ������������ ���� ����������, �� �� ���� ��������� ��������� ��������
  /*********************/
  /*
  ��� ������ �������������� ����� � ������ ��������, ���� �� ������������ ���� ����� �������,
  � ���� ���� ������� - �� ������������
  */
  _CLEAR_BIT(p_active_functions, RANG_VIDKL_VID_ZAKHYSTIV);
  if (
      ((p_active_functions[0] & current_settings_prt.ranguvannja_off_cb[0]) != 0) ||
      ((p_active_functions[1] & current_settings_prt.ranguvannja_off_cb[1]) != 0) ||
      ((p_active_functions[2] & current_settings_prt.ranguvannja_off_cb[2]) != 0) ||
      ((p_active_functions[3] & current_settings_prt.ranguvannja_off_cb[3]) != 0) ||
      ((p_active_functions[4] & current_settings_prt.ranguvannja_off_cb[4]) != 0) ||
      ((p_active_functions[5] & current_settings_prt.ranguvannja_off_cb[5]) != 0) ||
      ((p_active_functions[6] & current_settings_prt.ranguvannja_off_cb[6]) != 0) ||
      ((p_active_functions[7] & current_settings_prt.ranguvannja_off_cb[7]) != 0) ||
      ((p_active_functions[8] & current_settings_prt.ranguvannja_off_cb[8]) != 0) ||
      ((p_active_functions[9] & current_settings_prt.ranguvannja_off_cb[9]) != 0)
     )
  {
    //� ����� ��������� ���� ���������
    _SET_BIT(p_active_functions, RANG_WORK_BO);

    //��������� (��� ���������� ���������� � 0, ���� �� ������� ������ ��������� ��) �������: ����� ��, ����������� ��.
    global_timers[INDEX_TIMER_VIDKL_VV  ] = 0;
    global_timers[INDEX_TIMER_BLK_VKL_VV] = 0;
    
    //������� ��������� ����� ���������
    _CLEAR_BIT(p_active_functions, RANG_WORK_BV);
    //������� ������ ���� ���������
    global_timers[INDEX_TIMER_VKL_VV] = -1;  

    /*
    ������� ������ "³��������� �� �������" (�� ����� �������� ����� �������
    ��������� ������� "������ ��" ����-���� �������� �� ����������� "�����. ��")
    */
    //������� ����������� ����� ��� ���������� ������� "����.��"
    for (unsigned int i = 0; i < N_BIG; i++ )  maska[i] = (unsigned int)(~0);
    _CLEAR_BIT(maska, RANG_OTKL_VV);
    _CLEAR_BIT(maska, RANG_WORK_BO);
    if (
        ((p_active_functions[0] & maska[0]) != 0) ||
        ((p_active_functions[1] & maska[1]) != 0) ||
        ((p_active_functions[2] & maska[2]) != 0) ||
        ((p_active_functions[3] & maska[3]) != 0) ||
        ((p_active_functions[4] & maska[4]) != 0) ||
        ((p_active_functions[5] & maska[5]) != 0) ||
        ((p_active_functions[6] & maska[6]) != 0) ||
        ((p_active_functions[7] & maska[7]) != 0) ||
        ((p_active_functions[8] & maska[8]) != 0) ||
        ((p_active_functions[9] & maska[9]) != 0)
       )
    {
      //��������� �� �������
      _SET_BIT(p_active_functions, RANG_VIDKL_VID_ZAKHYSTIV);
      
      unsigned int temp_array_of_outputs[N_BIG];
      for (unsigned int i = 0; i < N_BIG; i++ ) temp_array_of_outputs[i] = (p_active_functions[i] & maska[i]);
      _CLEAR_BIT(temp_array_of_outputs, RANG_VIDKL_VID_ZAKHYSTIV);
          
      /*****************************************************
      ��������� ���������� ��� ������� ���������� ��� ����
      *****************************************************/
      unsigned char *label_to_time_array;
      if (copying_time == 2) label_to_time_array = time_copy;
      else label_to_time_array = time;
          
      //��1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_DZ1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_DZ1) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_DZ_1);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_DZ_1][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_DZ1);
      }
          
      //AM�� ��1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_AMTZ_DZ1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_AMTZ_DZ1) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_AMTZ_DZ_1);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_AMTZ_DZ_1][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_AMTZ_DZ1);
      }
          
      //��2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_DZ2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_DZ2) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_DZ_2);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_DZ_2][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_DZ2);
      }
          
      //AM�� ��2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_AMTZ_DZ2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_AMTZ_DZ2) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_AMTZ_DZ_2);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_AMTZ_DZ_2][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_AMTZ_DZ2);
      }
          
      //��3
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_DZ3) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_DZ3) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_DZ_3);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_DZ_3][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_DZ3);
      }
          
          
      //AM�� ��3
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_AMTZ_DZ3) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_AMTZ_DZ3) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_AMTZ_DZ_3);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_AMTZ_DZ_3][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_AMTZ_DZ3);
      }

      //��4
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_DZ4) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_DZ4) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_DZ_4);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_DZ_4][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_DZ4);
      }
          
      //AM�� ��4
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_AMTZ_DZ4) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_AMTZ_DZ4) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_AMTZ_DZ_4);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_AMTZ_DZ_4][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_AMTZ_DZ4);
      }

      //���1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_MTZ1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_MTZ1) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_MTZ1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_MTZ1);
      }
      
      //���2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_MTZ2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_MTZ2) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_MTZ2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_MTZ2);
      }
      
      //���3
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_MTZ3) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_MTZ3) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_MTZ3);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ3][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_MTZ3);
      }
      
      //���4
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_MTZ4) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_MTZ4) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_MTZ4);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_MTZ4][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_MTZ4);
      }
          
      //���
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_ZDZ) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_ZDZ) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_ZDZ);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ZDZ][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_ZDZ);
      }
      
      //��/3I0
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_3I0) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_3I0) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_3I0);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_3I0][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_3I0);
      }
          
      //��/3U0
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_3U0) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_3U0) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_3U0);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_3U0][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_3U0);
      }
          
      //���
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_NZZ) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_NZZ) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_NZZ);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_NZZ][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_NZZ);
      }
          
      //����1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_TZNP1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_TZNP1) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_TZNP1);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_TZNP1][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_TZNP1);
      }

      //����2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_TZNP2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_TZNP2) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_TZNP2);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_TZNP2][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_TZNP2);
      }

      //����3
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_TZNP3) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_TZNP3) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_TZNP3);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_TZNP3][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_TZNP3);
      }

      //���/���� �� ��
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_ACHR_CHAPV_VID_DV) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_ACHR_CHAPV_VID_DV) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_ACHR_CHAPV_VID_DV);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ACHR_CHAPV_VID_DV][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_ACHR_CHAPV_VID_DV);
      }
          
      //���/����1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_ACHR_CHAPV1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_ACHR_CHAPV1) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_ACHR_CHAPV1);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ACHR_CHAPV1][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_ACHR_CHAPV1);
      }
          
      //���/����2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_ACHR_CHAPV2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_ACHR_CHAPV2) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_ACHR_CHAPV2);
        for(unsigned int j = 0; j < 7; j++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ACHR_CHAPV2][j] = *(label_to_time_array + j);

        _CLEAR_BIT(temp_array_of_outputs, RANG_ACHR_CHAPV2);
      }
          
      //����1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UROV1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_UROV1) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UROV1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UROV1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UROV1);
      }
      
      //����2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UROV2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_UROV2) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UROV2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UROV2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UROV2);
      }
      
      //���
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_ZOP) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_ZOP) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_ZOP);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ZOP][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_ZOP);
      }
      
      //Umin1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UMIN1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_UMIN1) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UMIN1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMIN1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UMIN1);
      }
      
      //Umin2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UMIN2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_UMIN2) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UMIN2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMIN2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UMIN2);
      }
      
      //Umax1
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UMAX1) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_UMAX1) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UMAX1);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMAX1][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UMAX1);
      }
      
      //Umax2
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_UMAX2) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_UMAX2) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_UMAX2);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UMAX2][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_UMAX2);
      }
      
      //������������ ������
      for (size_t n_UP = 0; n_UP < NUMBER_UP; n_UP++)
      {
        if(
           (_CHECK_SET_BIT(temp_array_of_outputs, (RANG_UP1 + 3*n_UP)) != 0) &&
           (_CHECK_SET_BIT(previous_active_functions, (RANG_UP1 + 3*n_UP)) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
          )   
        {
          _SET_BIT(info_vidkluchennja_vymykacha, (VYMKNENNJA_VID_UP1 + n_UP));
          for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_UP1 + n_UP][i] = *(label_to_time_array + i);

          _CLEAR_BIT(temp_array_of_outputs, (RANG_UP1 + 3*n_UP));
        }
      }
      
      //³��������� �� ������� �������
      if(
         (_CHECK_SET_BIT(temp_array_of_outputs, RANG_OTKL_VID_ZOVN_ZAHYSTIV) != 0) &&
         (_CHECK_SET_BIT(previous_active_functions, RANG_OTKL_VID_ZOVN_ZAHYSTIV) == 0) /*�����, �� ������ ����� ���������� (��� ����������� ��� ������)*/
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_ZOVNISHNIKH_ZAKHYSTIV);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_ZOVNISHNIKH_ZAKHYSTIV][i] = *(label_to_time_array + i);

        _CLEAR_BIT(temp_array_of_outputs, RANG_OTKL_VID_ZOVN_ZAHYSTIV);
      }
      
      //³��������� �� ����� ������� (��� ���������� �� ������� "����.��")
      if(
         (
          (temp_array_of_outputs[0] != 0) ||
          (temp_array_of_outputs[1] != 0) ||
          (temp_array_of_outputs[2] != 0) ||
          (temp_array_of_outputs[3] != 0) ||
          (temp_array_of_outputs[4] != 0) ||
          (temp_array_of_outputs[5] != 0) ||
          (temp_array_of_outputs[6] != 0) ||
          (temp_array_of_outputs[7] != 0) ||
          (temp_array_of_outputs[8] != 0) ||
          (temp_array_of_outputs[9] != 0)
         )
         &&
         (
          ((previous_active_functions[0] & temp_array_of_outputs[0])!= temp_array_of_outputs[0]) ||
          ((previous_active_functions[1] & temp_array_of_outputs[1])!= temp_array_of_outputs[1]) ||
          ((previous_active_functions[2] & temp_array_of_outputs[2])!= temp_array_of_outputs[2]) ||
          ((previous_active_functions[3] & temp_array_of_outputs[3])!= temp_array_of_outputs[3]) ||
          ((previous_active_functions[4] & temp_array_of_outputs[4])!= temp_array_of_outputs[4]) ||
          ((previous_active_functions[5] & temp_array_of_outputs[5])!= temp_array_of_outputs[5]) ||
          ((previous_active_functions[6] & temp_array_of_outputs[6])!= temp_array_of_outputs[6]) ||
          ((previous_active_functions[7] & temp_array_of_outputs[7])!= temp_array_of_outputs[7]) ||
          ((previous_active_functions[8] & temp_array_of_outputs[8])!= temp_array_of_outputs[8]) ||
          ((previous_active_functions[9] & temp_array_of_outputs[9])!= temp_array_of_outputs[9])
         ) 
        )   
      {
        _SET_BIT(info_vidkluchennja_vymykacha, VYMKNENNJA_VID_INSHYKH_SYGNALIV);
        for(unsigned int i = 0; i < 7; i++) info_vidkluchennja_vymykachatime[VYMKNENNJA_VID_INSHYKH_SYGNALIV][i] = *(label_to_time_array + i);
      }
      /*****************************************************/
    }
  }

  /*********************/
  //���� ������������ ���� ���������
  /*********************/
  if (
      (global_timers[INDEX_TIMER_VIDKL_VV  ] < 0) && 
      (global_timers[INDEX_TIMER_BLK_VKL_VV] < 0) &&
      (_CHECK_SET_BIT(p_active_functions, RANG_BLOCK_VKL_VV) == 0)
     )
  {
    //������� �� �������� ������� �� � ���������� ��������� ��, � ����� ���� ������� ���������� ��������� ��
    //���� ����������, �� ���� ����� ������� ��

    if (
        ((p_active_functions[0] & current_settings_prt.ranguvannja_on_cb[0]) != 0) ||
        ((p_active_functions[1] & current_settings_prt.ranguvannja_on_cb[1]) != 0) ||
        ((p_active_functions[2] & current_settings_prt.ranguvannja_on_cb[2]) != 0) ||
        ((p_active_functions[3] & current_settings_prt.ranguvannja_on_cb[3]) != 0) ||
        ((p_active_functions[4] & current_settings_prt.ranguvannja_on_cb[4]) != 0) ||
        ((p_active_functions[5] & current_settings_prt.ranguvannja_on_cb[5]) != 0) ||
        ((p_active_functions[6] & current_settings_prt.ranguvannja_on_cb[6]) != 0) ||
        ((p_active_functions[7] & current_settings_prt.ranguvannja_on_cb[7]) != 0) ||
        ((p_active_functions[8] & current_settings_prt.ranguvannja_on_cb[8]) != 0) ||
        ((p_active_functions[9] & current_settings_prt.ranguvannja_on_cb[9]) != 0)
      )
    {
      //³������ � ����� �������, �� ����� �����������, �� �� ����� ���������� ���� �� (���� �� �� �� ��������)
      _SET_BIT(p_active_functions, RANG_WORK_BV);

      //��������� (��� ���������� ���������� � 0, ���� �� ������� ������ ��������� ��) ������ ������ ��
      global_timers[INDEX_TIMER_VKL_VV] = 0;
    }
  }
  else
  {
    //�� ����� ������ ���� ���� ��� ����� ���� ���������� ��
    global_timers[INDEX_TIMER_VKL_VV] = -1;
    _CLEAR_BIT(p_active_functions, RANG_WORK_BV);
  }
  /*********************/

  /*********************/
  //������� ���������� ���� ������� ��� ������� ���������/���������
  /*********************/
  for (unsigned int i = 0; i < N_BIG; i++) previous_active_functions[i] = p_active_functions[i];
  /*********************/
}
/*****************************************************/

/*****************************************************/
//���������� ���� �� �����������
/*****************************************************/
inline void vmp_handler(unsigned int p_active_functions[])
{
  //���������� �� ����� ���������� ����������� �� �� �� ������ ����
  if(
     ((p_active_functions[0] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_0) != 0) ||
     ((p_active_functions[1] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_1) != 0) ||
     ((p_active_functions[2] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_2) != 0) ||
     ((p_active_functions[3] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_3) != 0) ||
     ((p_active_functions[4] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_4) != 0) ||
     ((p_active_functions[5] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_5) != 0) ||
     ((p_active_functions[6] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_6) != 0) ||
     ((p_active_functions[7] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_7) != 0) ||
     ((p_active_functions[8] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_8) != 0) ||
     ((p_active_functions[9] & MASKA_MONITOTYNG_PHASE_SIGNALES_KZ_9) != 0)
    )
  {
    //� ����� ��
    VMP_last_KZ = UNDEF_VMP; /*�������, �� ���������� ���� �� ����������� �� �� ���������*/
    
    //���������� �� �������� ������� �� ��������� �� ("������ ��")
    vymknennja_vid_KZ_prt |= (_CHECK_SET_BIT(p_active_functions, RANG_WORK_BO) != 0);
    unsigned int MF_KZ_tmp = ((_CHECK_SET_BIT(p_active_functions, RANG_2KZ) != 0) << 0) | ((_CHECK_SET_BIT(p_active_functions, RANG_3KZ) != 0) << 1);

    if ((MF_KZ_tmp != 0) && (MF_KZ_tmp >= MF_KZ))
    {
      int X_resistance[3];
      X_resistance[0] = ((corupted_phases & ((1 << 0) | (1 << 1))) == ((1 << 0) | (1 << 1))) ? resistance[X_AB] : ((unsigned int)UNDEF_RESISTANCE); //AB
      X_resistance[1] = ((corupted_phases & ((1 << 1) | (1 << 2))) == ((1 << 1) | (1 << 2))) ? resistance[X_BC] : ((unsigned int)UNDEF_RESISTANCE); //BC
      X_resistance[2] = ((corupted_phases & ((1 << 0) | (1 << 2))) == ((1 << 0) | (1 << 2))) ? resistance[X_CA] : ((unsigned int)UNDEF_RESISTANCE); //CA
      if (
          (((unsigned int)X_resistance[0]) != ((unsigned int)UNDEF_RESISTANCE)) ||
          (((unsigned int)X_resistance[1]) != ((unsigned int)UNDEF_RESISTANCE)) ||
          (((unsigned int)X_resistance[2]) != ((unsigned int)UNDEF_RESISTANCE))
         )
      {
        //� ������� ���������� ������ �����

        //Գ����� ��������� �������� ���������� ��� ��� ��
        //���� 1: �������� ������ ���������� ��������� ��� � ������� ���� �������� �� ��������
        unsigned int min_interphase_X = (unsigned int)UNDEF_RESISTANCE;
        int R_KZ_tmp;
        if (((unsigned int)X_resistance[0]) != ((unsigned int)UNDEF_RESISTANCE))
        {
          min_interphase_X = abs(X_resistance[0]);
          R_KZ_tmp = resistance[R_AB];
        }
        else if (((unsigned int)X_resistance[1]) != ((unsigned int)UNDEF_RESISTANCE))
        {
          min_interphase_X = abs(X_resistance[1]);
          R_KZ_tmp = resistance[R_BC];
        }
        else if (((unsigned int)X_resistance[2]) != ((unsigned int)UNDEF_RESISTANCE))
        {
          min_interphase_X = abs(X_resistance[2]);
          R_KZ_tmp = resistance[R_CA];
        }
        else
        {
          //���������� ����� ����� �� ���� � ����
          total_error_sw_fixed(68);
        }
      
        //���� 2: ����� ��� ���������� �������� ����� ��������� ��������
        unsigned int X_mod;
        if ((((unsigned int)X_resistance[0]) != ((unsigned int)UNDEF_RESISTANCE)) && (min_interphase_X > (X_mod = abs(X_resistance[0])))) 
        {
          min_interphase_X = X_mod;
          R_KZ_tmp = resistance[R_AB];
        }
        if ((((unsigned int)X_resistance[1]) != ((unsigned int)UNDEF_RESISTANCE)) && (min_interphase_X > (X_mod = abs(X_resistance[1]))))
        {
          min_interphase_X = X_mod;
          R_KZ_tmp = resistance[R_BC];
        }
        if ((((unsigned int)X_resistance[2]) != ((unsigned int)UNDEF_RESISTANCE)) && (min_interphase_X > (X_mod = abs(X_resistance[2]))))
        {
          min_interphase_X = X_mod;
          R_KZ_tmp = resistance[R_CA];
        }
      
        //���� 3: ���������� �� ��������� ��� �� ��� ������ �� � ��������� � ������� ���������� ��
        if (
            (min_interphase_X != ((unsigned int)UNDEF_RESISTANCE))
            &&
            (
             (X_min_KZ_prt == ((unsigned int)UNDEF_RESISTANCE)) || /*�� � �������, �� ��� ������ �� �� ������ ��� ������� ��������� ���, ���� � ���� �������� ������� �� ��������*/
             (MF_KZ_tmp > MF_KZ) ||  
             (X_min_KZ_prt > min_interphase_X)
            )   
           )
        {
          //����������� ���� �������� ���������� ��������� ����� ��� ��
          X_min_KZ_prt = min_interphase_X;
          R_KZ_prt = R_KZ_tmp; //���� �� �� ����� ������� ����� ��� ���������� ����� (��� ��������� � ����� ������� �������� ��)
          MF_KZ = MF_KZ_tmp;
        }
      }
      else
      {
        X_min_KZ_prt = (unsigned int)UNDEF_RESISTANCE;
      }
    }
  }
  else
  {
    //�� ����� ������ ���� ������� ��
    if(
       (vymknennja_vid_KZ_prt != 0) &&  /*�����, �� ���������� ��������� �� ��� ���������� ��*/
       (MF_KZ != 0) && /*�����, �� �� � ��������*/
       ((current_settings_prt.control_vmp & CTR_VMP_STATE) != 0) && /*��� ��������*/ 
       (X_min_KZ_prt != ((unsigned int)UNDEF_RESISTANCE)) /*�����, �� ���� � ���� �������� ��� ��� ����������, � ���� � � ������������ ��������� ���������� �������� ���*/
      )
    {
      if  (MF_KZ & (1 << 0))
      {
        //�������� ��, ���� ��� ����� ������� �� 2
        X_min_KZ_prt >>=1;
      }
      
      //��������� ������ �� ���� ����������� ���� �� ��� �������� 
      unsigned int X_tmp = X_min_KZ_prt*current_settings_prt.TVoltage/current_settings_prt.TCurrent; /*��������������� ��� �� �������� �������. �������� �������� � ���*/
      
      unsigned int forward_backward = (R_KZ_prt < 0);
      unsigned int lines_tmp = current_settings_prt.lines[forward_backward];
      unsigned int defined_VMP = false;
      unsigned int i = 0;
      int VMP_tmp = 0;
      while ((defined_VMP == false) && (i < lines_tmp))
      {
        unsigned int dovgyna_tmp = current_settings_prt.dovgyna[forward_backward][i];
        unsigned int opir_tmp = current_settings_prt.opir[forward_backward][i];
        unsigned int X_current_line = dovgyna_tmp*opir_tmp/1000; /*���������*[�]x[���/��] =  [�]x[���/1000�] =[���]/1000 */
        if (X_tmp <= X_current_line)
        {
          //�� ���� ������ ����������� �����������
//          VMP_tmp += (int)(((unsigned long long)dovgyna_tmp)*((unsigned long long)X_tmp)/((unsigned long long)X_current_line));
          VMP_tmp += X_tmp*1000/opir_tmp;
          defined_VMP = true;
        }
        else
        {
          //�� ���� ������ �� �� ����������� �����������
          VMP_tmp += dovgyna_tmp;
          X_tmp -= X_current_line;
        }
          
        i++;
      }
      
      //��������� ��������� ���
      equal_more_KZ = defined_VMP;
      if(forward_backward == 0) VMP_last_KZ = VMP_tmp;
      else VMP_last_KZ = -VMP_tmp;
    }

    /*
    ��������� �������� ������������ � ���� ���������� ������ ��
    
    �� �������� ���� � ����� ���� ���������� ����� ��� ���� ������������� ��,
    ��� �������  � �� ������ ��������� ��, � ����� ��������� ��� �� (������������ ��
    ���� �� �������� �� ���������, ��� ���� ������� ��������� �� �����������, � ��
    �� ���������) - �� ��� �� ������������ ��������, � ������ �� �������� ��������� ���� ���� ��
    � �����, �� �� �� ��� ������ � ���� � �� ���� ������ ������� ������ ���������
    */
    vymknennja_vid_KZ_prt = 0;
    MF_KZ = 0;
    X_min_KZ_prt = (unsigned int)UNDEF_RESISTANCE;
    R_KZ_prt = 0;
    corupted_phases = 0;
  }
      
}
/*****************************************************/

/*****************************************************/
//�������� ������� ��������
/*****************************************************/
void control_VV(unsigned int *p_active_functions)
{
  unsigned int logic_control_VV_0 = 0;

  //"�������� ���."
  logic_control_VV_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_CTRL_VKL ) != 0) << 0;
  //"�������� ����."
  logic_control_VV_0 |= (_CHECK_SET_BIT(p_active_functions, RANG_CTRL_OTKL) != 0) << 1;
  
  _XOR_INVERTOR(logic_control_VV_0, 0, logic_control_VV_0, 1, logic_control_VV_0, 2);

  _TIMER_T_0(INDEX_TIMER_PRYVOD_VV, current_settings_prt.timeout_pryvoda_VV, logic_control_VV_0, 2, logic_control_VV_0, 3);

  //�:"�������� ��"
  logic_control_VV_0 |= ((current_settings_prt.control_switch & CTR_PRYVOD_VV) != 0) << 4;
  
  _AND2(logic_control_VV_0, 3, logic_control_VV_0, 4, logic_control_VV_0, 5);
  
  if (_GET_OUTPUT_STATE(logic_control_VV_0, 5))
    _SET_BIT(p_active_functions, RANG_PRYVID_VV);
  else
    _CLEAR_BIT(p_active_functions, RANG_PRYVID_VV);
}
/*****************************************************/

/*****************************************************/
//���������� ������������ ��� ��������� ������� ��������
/*****************************************************/
void make_koef_for_resurs(void)
{
  float tmp_1, tmp_2;
  
  tmp_1 = (float)current_settings.setpoint_r_kom_st_Inom/(float)current_settings.setpoint_r_kom_st_Inom_vymk;
  tmp_1  = log10f(tmp_1);

  tmp_2 = (float)current_settings.setpoint_Inom_vymk/(float)current_settings.setpoint_Inom;
  tmp_2  = log10f(tmp_2);
  
  //�������, �� ����������� ��� ���������� ������� �������� ����� ������ �����
  koef_resurs_changed = CHANGED_ETAP_EXECUTION;

  K_resurs = tmp_1/tmp_2;
  
  //�������, �� ����������� ��� ���������� ������� �������� ����� � ������� �� ������ �������� �������
  koef_resurs_changed = CHANGED_ETAP_ENDED;
}
/*****************************************************/

/*****************************************************/
//˳������� �������
/*****************************************************/
inline void resurs_vymykacha_handler(unsigned int *p_active_functions)
{
  static unsigned int previous_active_functions[N_BIG];
  
  if (restart_counter != 0)
  {
    //����� ������ ������� ������� ������� ��������
    resurs_vymykacha = current_settings_prt.setpoint_pochatkovyj_resurs;
    resurs_vidkljuchennja = current_settings_prt.setpoint_pochatkova_k_vymk;
    
     restart_counter = 0;

    //��������� ����� � EEPROM
    _SET_BIT(control_spi1_taskes, TASK_START_WRITE_RESURS_EEPROM_BIT);

    //�������, �� �������� ������� ������� ��������
    information_about_restart_counter |= ((1 << USB_RECUEST)|(1 << RS485_RECUEST));
  }
  
  /*******************************/
  //��������� ������������ ������� ����� �� ��� ������ ����� ��������� (��)
  /*******************************/
  static unsigned int max_faze_current_vv;
  if (_CHECK_SET_BIT(p_active_functions, RANG_WORK_BO) != 0)
  {
    unsigned int max_faze_current_tmp = measurement[IM_IA];
    if (max_faze_current_tmp < measurement[IM_IB]) max_faze_current_tmp = measurement[IM_IB];
    if (max_faze_current_tmp < measurement[IM_IC]) max_faze_current_tmp = measurement[IM_IC];
    max_faze_current_tmp = max_faze_current_tmp*current_settings_prt.TCurrent/1000;
  
    if (_CHECK_SET_BIT(previous_active_functions, RANG_WORK_BO) == 0)
    {
      //����������� ����� ������ ��
      max_faze_current_vv = max_faze_current_tmp;
    }
    else if (_CHECK_SET_BIT(previous_active_functions, RANG_WORK_BO) != 0)
    {
      //�� �������� ���� ������
      if (max_faze_current_vv < max_faze_current_tmp) max_faze_current_vv = max_faze_current_tmp;
    }
    
    if (max_faze_current_vv > current_settings_prt.setpoint_Inom_vymk) 
    {
      _SET_BIT(p_active_functions, RANG_PEREVYSHCHENNJA_Inom_VYMK);
    }
    else
    {
      _CLEAR_BIT(p_active_functions, RANG_PEREVYSHCHENNJA_Inom_VYMK);
    }
  }
  /*******************************/
  
  if (
      ((current_settings_prt.control_switch & CTR_RESURS_VV) != 0) &&
      (_CHECK_SET_BIT(previous_active_functions, RANG_WORK_BO) != 0) &&
      (_CHECK_SET_BIT(p_active_functions , RANG_WORK_BO) == 0)
     ) 
  {
    //����������� ���������� "������ ��"
    
    /*******************************/
    //������������ ������ �������a
    /*******************************/
    unsigned int N = 0;
    if (max_faze_current_vv >= current_settings_prt.setpoint_Inom_vymk) {
      N = (unsigned int) ceilf((float)current_settings_prt.setpoint_r_kom_st_Inom/(float)current_settings_prt.setpoint_r_kom_st_Inom_vymk);
    } else if (max_faze_current_vv <= current_settings_prt.setpoint_Inom) {
      N = 1;
    } else {
      float I_div_Inom = (float)max_faze_current_vv / (float)current_settings_prt.setpoint_Inom;
      float lg_I_div_Inom = log10f(I_div_Inom);
      float lg_N = K_resurs_prt * lg_I_div_Inom;
      float N_ = powf(10, lg_N);
      N = (unsigned int) ceilf(N_);
      if ((((float)N) - N_) >= 0.5f)
      {
        N--;
      }
      
    }
    
    if (resurs_vymykacha <= N) {
      resurs_vymykacha = 0;
    } else {
      resurs_vymykacha -= N;
    }
    
    //�������� ����� �����������
    if ((0xffffffff - resurs_vidkljuchennja) >= 1)
    {
      //��������� ������� �� ������� ������������
      resurs_vidkljuchennja++;
    }

    //��������� ����� � EEPROM
    _SET_BIT(control_spi1_taskes, TASK_START_WRITE_RESURS_EEPROM_BIT);
  }
  
  if (resurs_vymykacha <= current_settings_prt.setpoint_krytychnyj_resurs) 
  {
    _SET_BIT(p_active_functions, RANG_KRYTYCHNYJ_RESURS_VYMYKACHA);
  }
  else
  {
    _CLEAR_BIT(p_active_functions, RANG_KRYTYCHNYJ_RESURS_VYMYKACHA);
  }

  if (resurs_vymykacha == 0) 
  {
    _SET_BIT(p_active_functions, RANG_VYCHERPANYJ_RESURS_VYMYKACHA);
  }
  else
  {
    _CLEAR_BIT(p_active_functions, RANG_VYCHERPANYJ_RESURS_VYMYKACHA);
  }
 

  /*********************/
  //������� ���������� ���� ������� ��� ������� ���������/���������
  /*********************/
  for (unsigned int i = 0; i < N_BIG; i++) previous_active_functions[i] = p_active_functions[i];
  /*********************/
}
/*****************************************************/

/*****************************************************/
//�������� �� ����������� ���������� ������ �����������/����������� ����������
/*****************************************************/
inline unsigned int stop_regisrator(unsigned int* carrent_active_functions, unsigned int* ranguvannja_registrator)
{
  unsigned int stop = 0;

  {
    if (
        ((carrent_active_functions[0] & ranguvannja_registrator[0]) == 0) &&
        ((carrent_active_functions[1] & ranguvannja_registrator[1]) == 0) &&
        ((carrent_active_functions[2] & ranguvannja_registrator[2]) == 0) &&
        ((carrent_active_functions[3] & ranguvannja_registrator[3]) == 0) &&
        ((carrent_active_functions[4] & ranguvannja_registrator[4]) == 0) &&
        ((carrent_active_functions[5] & ranguvannja_registrator[5]) == 0) &&
        ((carrent_active_functions[6] & ranguvannja_registrator[6]) == 0) &&
        ((carrent_active_functions[7] & ranguvannja_registrator[7]) == 0) &&
        ((carrent_active_functions[8] & ranguvannja_registrator[8]) == 0) &&
        ((carrent_active_functions[9] & ranguvannja_registrator[9]) == 0)
      )
    {
      //�����������, �� � ���� ������� ��������� ���������� ����� �� �������
      
      if (
          ((carrent_active_functions[0] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_0) == 0) &&
          ((carrent_active_functions[1] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_1) == 0) &&
          ((carrent_active_functions[2] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_2) == 0) &&
          ((carrent_active_functions[3] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_3) == 0) &&
          ((carrent_active_functions[4] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_4) == 0) &&
          ((carrent_active_functions[5] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_5) == 0) &&
          ((carrent_active_functions[6] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_6) == 0) &&
          ((carrent_active_functions[7] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_7) == 0) &&
          ((carrent_active_functions[8] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_8) == 0) &&
          ((carrent_active_functions[9] & MASKA_FOR_CONTINUE_GET_DR_ACTINE_WORD_9) == 0)
        )
      {
        //�����������, �� �� �������, �� ������ ���������� ��������� �������� ����� ������
          
        //����������, �� �� �������, �� ������� � ����� ����� ��������
        unsigned int global_timers_work = 0, i = INDEX_TIMER_DF_PAUSE_START;
        while ((i < NEXT_TIMER) && (global_timers_work == 0))
        {
          if (global_timers[i] >= 0) 
          {
            if (
                (
                 (i != INDEX_TIMER_PRYVOD_VV) ||
                 (  
                  ((current_settings_prt.control_switch & CTR_PRYVOD_VV) != 0) &&
                  (global_timers[i] < current_settings_prt.timeout_pryvoda_VV) 
                 )   
                ) 
                &&
                (i != INDEX_TIMER_ACHR_CHAPV_100MS_1)
                &&
                (i != INDEX_TIMER_NKN_DZ)
               )
            global_timers_work = 1;
          }
          i++;
        }
          
        if (global_timers_work == 0)
        {
          //�����������, �� �� �������, �� �������� � ����� ��������
        
          //�������, �� ��������� ���� ���� ���������
          stop = 0xff;
        }
      }
    }
  }
  
  return stop;
}
/*****************************************************/

/*****************************************************/
//����������� ����������� ������� ������ ����������� ����������
/*****************************************************/
void fix_undefined_error_dr(unsigned int* carrent_active_functions)
{
  //����������� ������� � ������� � ��������� ���������
  _SET_BIT(set_diagnostyka, ERROR_DR_UNDEFINED_BIT);
  _SET_BIT(carrent_active_functions, RANG_DEFECT);
  //���������� ����� ������ � ����������� � ���� "�� ����� ������ ���� �� � ���������� ����������� �� ����������" 
  state_dr_record = STATE_DR_NO_RECORD;
  //������� ������ ������ ����������� ����������
  _CLEAR_BIT(carrent_active_functions, RANG_WORK_D_REJESTRATOR);
}
/*****************************************************/

/*****************************************************/
//������ ������� ������ ����� � DataFalsh
/*****************************************************/
inline void command_start_saving_record_dr_into_dataflash(void)
{
  //� �������� �� ���������� ����� ���������� ����������� �����������, �� ������� ����� � �� �� ���������
  _SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT);
  info_rejestrator_dr.saving_execution = 1;
        
  //����������� ����� ������� ������
  part_writing_dr_into_dataflash = 0;
  //����������� ������� ������ � ��������� DataFlash
  control_tasks_dataflash |= TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR;
}
/*****************************************************/

/*****************************************************/
//������� ������� ����� ����������� ������ ����������� ����������
/*****************************************************/
inline void routine_for_queue_dr(void)
{
  if(
     (state_dr_record == STATE_DR_MAKE_RECORD)            || /*����� ����� ��������� ��� �������� �� ����� � DataFlsh ��� ���������� �������  ������ ������, �� ����� ���������� �����    ���������, � �� ������ ����� ����������� ���������� ������ ������������ ������*/
     (state_dr_record == STATE_DR_CUT_RECORD)             || /*����� ����� ��������� ��� �������� �� ����� � DataFlsh   � ���������  �������� ������ ������, �� ����� ���������� ����� �� ���������, �    ������ ����� ����������� ���������� ������ ������������ ������*/
     (number_records_dr_waiting_for_saving_operation != 0)  
    )
  {
    if ((control_tasks_dataflash & TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR) == 0)
    {
      //�� ����� ������ ������ � Datafalsh �� �����������
      unsigned char *buffer_source, *buffer_target;
        
      if (number_records_dr_waiting_for_saving_operation == 0)
      {
        buffer_target = buffer_for_save_dr_record_level_2;
        buffer_source = buffer_for_save_dr_record;
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++)
        {
          *(buffer_target + i) = *(buffer_source + i);
          *(buffer_source + i) = 0xff;
        }
        number_records_dr_waiting_for_saving_operation = 0;
      }
      else if (number_records_dr_waiting_for_saving_operation == 1)
      {
        buffer_target = buffer_for_save_dr_record_level_2;
        buffer_source = buffer_for_save_dr_record_level_1;
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) *(buffer_target +i ) = *(buffer_source + i);
        
        if((state_dr_record == STATE_DR_MAKE_RECORD) || (state_dr_record == STATE_DR_CUT_RECORD))
        {
          buffer_target = buffer_for_save_dr_record_level_1;
          buffer_source = buffer_for_save_dr_record;
          for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) 
          {
            *(buffer_target + i) = *(buffer_source + i);
            *(buffer_source + i) = 0xff;
          }
          number_records_dr_waiting_for_saving_operation = 1;
        }
        else number_records_dr_waiting_for_saving_operation = 0;
      }
      else
      {
        buffer_target = buffer_for_save_dr_record_level_2;
        buffer_source = buffer_for_save_dr_record_level_1;
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) *(buffer_target + i) = *(buffer_source + i);
        buffer_target = buffer_for_save_dr_record_level_1;
        buffer_source = buffer_for_save_dr_record;
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) 
        {
          *(buffer_target + i) = *(buffer_source + i);
          *(buffer_source + i) = 0xff;
        }
        number_records_dr_waiting_for_saving_operation = 1;
      }
        
      //������ ������� ������ ����� � DataFalsh
      command_start_saving_record_dr_into_dataflash();
    }
    else
    {
      //�� ����� ������ ������ � Datafalsh �����������
      //����� ��� �������� ����� ��������� � �����
      if (number_records_dr_waiting_for_saving_operation == 0)
      {
        //�� ����� ������ ��� ����, ������ - � ����� ��� ������������ ����� � DataFalsh, ����� ����� ������ � ���� ����
        //��������� ������� ����� � ����� buffer_for_save_dr_record_level_1
        for(unsigned int i = 0; i < SIZE_BUFFER_FOR_DR_RECORD; i++) 
        {
          buffer_for_save_dr_record_level_1[i] = buffer_for_save_dr_record[i];
          buffer_for_save_dr_record[i] = 0xff;
        }
    
        //�������, �� ���� ����� ����� ������� ���� �� ������������ ����� � dataFalsh
        number_records_dr_waiting_for_saving_operation = 1;
      }
      else if (number_records_dr_waiting_for_saving_operation >= 1)
      {
         if((state_dr_record == STATE_DR_MAKE_RECORD) || (state_dr_record == STATE_DR_CUT_RECORD))
         {
          //�� ����� ������ ��� ����, ������ - � ����� ��� ������������ ����� � DataFalsh, �� ���� ����������� ����� ����� � ����� buffer_for_save_dr_record_level_1
          /*
          ���� ����� ����� �������� � ����� ������ ����� buffer_for_save_dr_record, ��� �������� ������� ������. �� ������ � ����
          � ���� ���� ������ ������ ����� �����, �� ������ ��������� ������� ������ �����
          */
          number_records_dr_waiting_for_saving_operation = 2;
         }
      }
    }
    
    if (state_dr_record == STATE_DR_MAKE_RECORD)
    {
      //�������, �� �� ����� �������� ��������� �����
      state_dr_record = STATE_DR_NO_RECORD;
    }
    else if (state_dr_record == STATE_DR_CUT_RECORD)
    {
      //�������, �� ����� ��������� ��������� ����� �����
      state_dr_record = STATE_DR_FORCE_START_NEW_RECORD;
    }
      
  }
}
/*****************************************************/

/*****************************************************/
//������� ������� ����� ����������� ����������
/*****************************************************/
inline void digital_registrator(unsigned int* carrent_active_functions)
{
  static unsigned int previous_active_functions[N_BIG];
  
  static unsigned int number_items_dr;
  static unsigned int number_changes_into_dr_record;
  static unsigned int time_from_start_record_dr;

  static uint8_t VMP_fix;
  static int32_t VMP_value;
  static uint8_t VMP_equal_more;
  
  switch (state_dr_record)
  {
  case STATE_DR_NO_RECORD:
  case STATE_DR_FORCE_START_NEW_RECORD:
    {
      //���������� ������� ����������� �������  ������ ����������� ����������
      _SET_BIT(clear_diagnostyka, ERROR_DR_UNDEFINED_BIT);
      if(number_records_dr_waiting_for_saving_operation < (WIGHT_OF_DR_WAITING - 1))
      {
        //�� �������� ������, �� �� ����� �� ���� ����� ����� � ��� � ����� ���, ���� ������� ����������� ��� ������ �����
        _SET_BIT(clear_diagnostyka, ERROR_DR_TEMPORARY_BUSY_BIT);
      }
      
      //�� ������� ������ ������ �� ���������� ��������� �� ���������
      
      //��������, �� ����� ����� ������� ����������� ����������
       unsigned int cur_active_sources[N_BIG] =
       {
         (carrent_active_functions[0] & current_settings_prt.ranguvannja_digital_registrator[0]),
         (carrent_active_functions[1] & current_settings_prt.ranguvannja_digital_registrator[1]),
         (carrent_active_functions[2] & current_settings_prt.ranguvannja_digital_registrator[2]),
         (carrent_active_functions[3] & current_settings_prt.ranguvannja_digital_registrator[3]),
         (carrent_active_functions[4] & current_settings_prt.ranguvannja_digital_registrator[4]),
         (carrent_active_functions[5] & current_settings_prt.ranguvannja_digital_registrator[5]),
         (carrent_active_functions[6] & current_settings_prt.ranguvannja_digital_registrator[6]),
         (carrent_active_functions[7] & current_settings_prt.ranguvannja_digital_registrator[7]),
         (carrent_active_functions[8] & current_settings_prt.ranguvannja_digital_registrator[8]),
         (carrent_active_functions[9] & current_settings_prt.ranguvannja_digital_registrator[9])
       };
      if (
          (
           ((cur_active_sources[0]) != 0) ||
           ((cur_active_sources[1]) != 0) ||
           ((cur_active_sources[2]) != 0) ||
           ((cur_active_sources[3]) != 0) ||
           ((cur_active_sources[4]) != 0) ||
           ((cur_active_sources[5]) != 0) ||
           ((cur_active_sources[6]) != 0) ||
           ((cur_active_sources[7]) != 0) ||
           ((cur_active_sources[8]) != 0) ||
           ((cur_active_sources[9]) != 0) ||
           (state_dr_record == STATE_DR_FORCE_START_NEW_RECORD)
          )   
         )
      {
        //� ����� ������� ����������� ����������
        
        if (state_dr_record != STATE_DR_FORCE_START_NEW_RECORD)
        {
          /*���� �� ��� ����� �� �������� �� ����� ��������� ����� �����, ��� � ������� ���� ����� �� ����� ��������� ����� ����� �� ��� ���� ���� ����� ���� ���������, �� ���������� ��� ���� ���� ��� ������������*/
          VMP_fix = false;
          VMP_equal_more = 0;
          VMP_value = VMP_last_KZ = UNDEF_VMP; /*�������, �� ���������� ���� �� ����������� �� �� ���������  � ������� ������ ����������� ����������*/
        }
          
        //����������, �� ��� ������� ������ ������ �� �� �������� ��������� ����������
        if(number_records_dr_waiting_for_saving_operation < WIGHT_OF_DR_WAITING)
        {
          //����� �������� ����� �����
          
          //���������� ����� ������ �� ���������� ����������� � ���� "��� ������ ������ ����������"
          state_dr_record = STATE_DR_EXECUTING_RECORD;
          //����������� ������� �������
          _SET_BIT(carrent_active_functions, RANG_WORK_D_REJESTRATOR);
        
          //�������� ���� ������� ������
          buffer_for_save_dr_record[FIRST_INDEX_START_START_RECORD_DR] = LABEL_START_RECORD_DR;
         
          //�������� ��� ������� ������
          unsigned char *label_to_time_array;
          if (copying_time == 2) label_to_time_array = time_copy;
          else label_to_time_array = time;
          for(unsigned int i = 0; i < 7; i++) buffer_for_save_dr_record[FIRST_INDEX_DATA_TIME_DR + i] = *(label_to_time_array + i);
          
           //�'�� ������
          for(unsigned int i=0; i< MAX_CHAR_IN_NAME_OF_CELL; i++) 
            buffer_for_save_dr_record[FIRST_INDEX_NAME_OF_CELL_DR + i] = current_settings_prt.name_of_cell[i] & 0xff;

           //������� �������
          for(unsigned int i = 0; i < NUMBER_BYTES_SAMPLE_DR; i++) 
            buffer_for_save_dr_record[FIRST_INDEX_SOURCE_DR + i] = *(((unsigned char*)cur_active_sources) + i);

          //������� ������ ���� ������� � ������� ������� ������
          time_from_start_record_dr = 0;
          
          //�������� ��������� c��� ������� ����� �����
          //̳��� ���� ������������ ����� ������� �� ������� ������� ������
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  0] = 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  1] = 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  2] = 0xff;
          //��������� ����
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  3] =  previous_active_functions[0]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  4] = (previous_active_functions[0] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  5] = (previous_active_functions[0] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  6] = (previous_active_functions[0] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  7] =  previous_active_functions[1]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  8] = (previous_active_functions[1] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR +  9] = (previous_active_functions[1] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 10] = (previous_active_functions[1] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 11] =  previous_active_functions[2]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 12] = (previous_active_functions[2] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 13] = (previous_active_functions[2] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 14] = (previous_active_functions[2] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 15] =  previous_active_functions[3]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 16] = (previous_active_functions[3] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 17] = (previous_active_functions[3] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 18] = (previous_active_functions[3] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 19] =  previous_active_functions[4]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 20] = (previous_active_functions[4] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 21] = (previous_active_functions[4] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 22] = (previous_active_functions[4] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 23] =  previous_active_functions[5]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 24] = (previous_active_functions[5] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 25] = (previous_active_functions[5] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 26] = (previous_active_functions[5] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 27] =  previous_active_functions[6]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 28] = (previous_active_functions[6] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 29] = (previous_active_functions[6] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 30] = (previous_active_functions[6] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 31] =  previous_active_functions[7]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 32] = (previous_active_functions[7] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 33] = (previous_active_functions[7] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 34] = (previous_active_functions[7] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 35] =  previous_active_functions[8]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 36] = (previous_active_functions[8] >> 8)  & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 37] = (previous_active_functions[8] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 38] = (previous_active_functions[8] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 39] =  previous_active_functions[9]        & 0xff;
          //����� ��������� � ��� ������� ������� ���
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 40] = 0;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + 41] = 0;

          //������� ������� ����� ����
          number_items_dr = 1;
      
          //���������� ������� ��� �������
          number_changes_into_dr_record = 0;
          unsigned int number_changes_into_current_item;
          _NUMBER_CHANGES_INTO_UNSIGNED_INT_ARRAY(previous_active_functions, carrent_active_functions, N_BIG, number_changes_into_current_item);
          number_changes_into_dr_record += number_changes_into_current_item;
      
          //�������� ������� c��� �������
          //̳��� ����
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR +  0] =  time_from_start_record_dr        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR +  1] = (time_from_start_record_dr >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR +  2] = (time_from_start_record_dr >> 16) & 0xff;
          //������� ���� �������
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR +  3] =  carrent_active_functions[0]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR +  4] = (carrent_active_functions[0] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR +  5] = (carrent_active_functions[0] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR +  6] = (carrent_active_functions[0] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR +  7] =  carrent_active_functions[1]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR +  8] = (carrent_active_functions[1] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR +  9] = (carrent_active_functions[1] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 10] = (carrent_active_functions[1] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 11] =  carrent_active_functions[2]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 12] = (carrent_active_functions[2] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 13] = (carrent_active_functions[2] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 14] = (carrent_active_functions[2] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 15] =  carrent_active_functions[3]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 16] = (carrent_active_functions[3] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 17] = (carrent_active_functions[3] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 18] = (carrent_active_functions[3] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 19] =  carrent_active_functions[4]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 20] = (carrent_active_functions[4] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 21] = (carrent_active_functions[4] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 22] = (carrent_active_functions[4] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 23] =  carrent_active_functions[5]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 24] = (carrent_active_functions[5] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 25] = (carrent_active_functions[5] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 26] = (carrent_active_functions[5] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 27] =  carrent_active_functions[6]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 28] = (carrent_active_functions[6] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 29] = (carrent_active_functions[6] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 30] = (carrent_active_functions[6] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 31] =  carrent_active_functions[7]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 32] = (carrent_active_functions[7] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 33] = (carrent_active_functions[7] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 34] = (carrent_active_functions[7] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 35] =  carrent_active_functions[8]        & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 36] = (carrent_active_functions[8] >> 8 ) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 37] = (carrent_active_functions[8] >> 16) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 38] = (carrent_active_functions[8] >> 24) & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 39] =  carrent_active_functions[9]        & 0xff;
          
          //ʳ������ ��� ������� � �������� �� ��������� ������
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 40] = number_changes_into_current_item & 0xff;
          buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 41] = (number_changes_into_current_item >> 8) & 0xff;
      
//          //����� ������ �������, ��� � ����� �� ���� ���������� �� ��������� ������
//          for(unsigned int i = FIRST_INDEX_FIRST_BLOCK_DR; i < FIRST_INDEX_FIRST_DATA_DR; i++)
//            buffer_for_save_dr_record[i] = 0xff;
//          for(unsigned int i = (FIRST_INDEX_FIRST_DATA_DR + (number_items_dr + 1)*SD_DR); i < SIZE_BUFFER_FOR_DR_RECORD; i++)
//            buffer_for_save_dr_record[i] = 0xff;
          
          /*���� ���������� ��������� ��� ������ ��������� ����� ����� ��� ����� ����������� ��� ���� ���������, �� ���� ���� ��������. �� ��� � ��������� ���� �� ����������� ���*/
          if(VMP_last_KZ != UNDEF_VMP)
          {
            VMP_fix = true;
            VMP_value = VMP_last_KZ;
            VMP_equal_more = equal_more_KZ;
          }
        }
        else
        {
          //����������� �������, �� � ����� �� ������ ����������� ���������� ���, �� �� ���� ������ ������
          _SET_BIT(set_diagnostyka, ERROR_DR_TEMPORARY_BUSY_BIT);
          _SET_BIT(carrent_active_functions, RANG_DEFECT);
        }
      }
      else state_dr_record = STATE_DR_NO_RECORD;
      
      break;
    }
  case STATE_DR_EXECUTING_RECORD:
    {
      //�������� ��� � ������� ������� ������
      time_from_start_record_dr++;
      //������� �� ����� ���� ��� ������ ������

      if(
         (VMP_last_KZ != UNDEF_VMP) &&
         (
          (VMP_fix == false) ||
          (abs(VMP_value) > abs(VMP_last_KZ)) ||
          (
           (equal_more_KZ != VMP_equal_more) &&
           (equal_more_KZ == true)
          )
         )   
        )   
      {
         VMP_fix = true;
         VMP_value = VMP_last_KZ;
         VMP_equal_more = equal_more_KZ;
       }
      
      //����������, �� �� ���� ����� ����������� ������
      //���� ���� ����� ���� - �� ������� ������ ���������� ����������� ����������, �� �� ����������� � ������� ��������
      if (stop_regisrator(carrent_active_functions, current_settings_prt.ranguvannja_digital_registrator) != 0)
      {
        //������� ������ ������ ����������� ����������
        _CLEAR_BIT(carrent_active_functions, RANG_WORK_D_REJESTRATOR);

        //���������� ����� ������ �� ���������� ����������� � ���� "���������� ������������ ����� � ��������� DataFlash"
        state_dr_record = STATE_DR_MAKE_RECORD;
      }
      
      //���������� �� �������� ���� ������� � �������� �� ��������� ������. ���� ���� ���� �, �� ������ ����� ��� ������� � �����
      if (
          ((carrent_active_functions[0] != previous_active_functions[0])) ||
          ((carrent_active_functions[1] != previous_active_functions[1])) ||
          ((carrent_active_functions[2] != previous_active_functions[2])) ||
          ((carrent_active_functions[3] != previous_active_functions[3])) ||
          ((carrent_active_functions[4] != previous_active_functions[4])) ||
          ((carrent_active_functions[5] != previous_active_functions[5])) ||
          ((carrent_active_functions[6] != previous_active_functions[6])) ||
          ((carrent_active_functions[7] != previous_active_functions[7])) ||
          ((carrent_active_functions[8] != previous_active_functions[8])) ||
          ((carrent_active_functions[9] != previous_active_functions[9])) 
         )
      {
        //�������� ���� ������� �� ������� � ��������� ������ �������

        //�������� �� ���� ������� ����� ����
        number_items_dr++;
      
        //���������� ������� ��� �������
        unsigned int number_changes_into_current_item;
        _NUMBER_CHANGES_INTO_UNSIGNED_INT_ARRAY(previous_active_functions, carrent_active_functions, N_BIG, number_changes_into_current_item);
        number_changes_into_dr_record += number_changes_into_current_item;
      
        //�������� ������� c��� �������
        //̳��� ����
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR +  0] =  time_from_start_record_dr        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR +  1] = (time_from_start_record_dr >> 8 ) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR +  2] = (time_from_start_record_dr >> 16) & 0xff;
        //������� ���� �������
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR +  3] =  carrent_active_functions[0]        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR +  4] = (carrent_active_functions[0] >> 8 ) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR +  5] = (carrent_active_functions[0] >> 16) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR +  6] = (carrent_active_functions[0] >> 24) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR +  7] =  carrent_active_functions[1]        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR +  8] = (carrent_active_functions[1] >> 8 ) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR +  9] = (carrent_active_functions[1] >> 16) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 10] = (carrent_active_functions[1] >> 24) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 11] =  carrent_active_functions[2]        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 12] = (carrent_active_functions[2] >> 8 ) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 13] = (carrent_active_functions[2] >> 16) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 14] = (carrent_active_functions[2] >> 24) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 15] =  carrent_active_functions[3]        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 16] = (carrent_active_functions[3] >> 8 ) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 17] = (carrent_active_functions[3] >> 16) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 18] = (carrent_active_functions[3] >> 24) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 19] =  carrent_active_functions[4]        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 20] = (carrent_active_functions[4] >> 8 ) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 21] = (carrent_active_functions[4] >> 16) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 22] = (carrent_active_functions[4] >> 24) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 23] =  carrent_active_functions[5]        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 24] = (carrent_active_functions[5] >> 8 ) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 25] = (carrent_active_functions[5] >> 16) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 26] = (carrent_active_functions[5] >> 24) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 27] =  carrent_active_functions[6]        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 28] = (carrent_active_functions[6] >> 8 ) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 29] = (carrent_active_functions[6] >> 16) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 30] = (carrent_active_functions[6] >> 24) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 31] =  carrent_active_functions[7]        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 32] = (carrent_active_functions[7] >> 8 ) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 33] = (carrent_active_functions[7] >> 16) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 34] = (carrent_active_functions[7] >> 24) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 35] =  carrent_active_functions[8]        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 36] = (carrent_active_functions[8] >> 8 ) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 37] = (carrent_active_functions[8] >> 16) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 38] = (carrent_active_functions[8] >> 24) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 39] =  carrent_active_functions[9]        & 0xff;
        //ʳ������ ��� ������� � �������� �� ��������� ������
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 40] = number_changes_into_current_item & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_FIRST_DATA_DR + number_items_dr*SD_DR + 41] = (number_changes_into_current_item >> 8) & 0xff;
      }
        
      //����������, �� ����� ����� ���������� ������
      if (
          (state_dr_record == STATE_DR_MAKE_RECORD)                  ||
          (time_from_start_record_dr >= MAX_TIME_OFFSET_FROM_START)  ||  
          ((number_items_dr + 1)     >= MAX_EVENTS_IN_ONE_RECORD  )  
         )
      {
        //���� ����� ����������� ������, ��� � ����� ���������� ������ - ��������� ���������� ������ � ������ ������� �� �����
        buffer_for_save_dr_record[FIRST_INDEX_NUMBER_ITEMS_DR      ] = number_items_dr;
        buffer_for_save_dr_record[FIRST_INDEX_NUMBER_CHANGES_DR    ] =  number_changes_into_dr_record       & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_NUMBER_CHANGES_DR + 1] = (number_changes_into_dr_record >> 8) & 0xff;

        buffer_for_save_dr_record[FIRST_INDEX_VMP_VALUE    ] =  VMP_value        & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_VMP_VALUE + 1] = (VMP_value >>  8) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_VMP_VALUE + 2] = (VMP_value >> 16) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_VMP_VALUE + 3] = (VMP_value >> 24) & 0xff;
        buffer_for_save_dr_record[FIRST_INDEX_VMP_EQUAL_MORE] = VMP_equal_more;
        
        //���������� ����� ������ �� ���������� ����������� � ���� "���������� ������������ ����� � DataFlash"
        if (state_dr_record != STATE_DR_MAKE_RECORD)
        {
          if (time_from_start_record_dr >= MAX_TIME_OFFSET_FROM_START)
          {
            //���� �������� ����������� �� ���� ������, �� ������ ������� ��������� ����� ��� ����������� ���� ����� ������ � ���������� �����
            state_dr_record = STATE_DR_MAKE_RECORD;
          }
          else
          {
            //���� �������� ����������� �� ��������� ����������� ������� ���� (��� ���� �������, ��� ������ �� ���������, ��� ���� �'������� � �����������), �� ������ ������� ��������� ����� ��� �� ���������� ������ ������ ����� �����
            state_dr_record = STATE_DR_CUT_RECORD;
          }
        }
        
        //������� ������ ������ ����������� ����������
        _CLEAR_BIT(carrent_active_functions, RANG_WORK_D_REJESTRATOR);
      }

      break;
    }
  default:
    {
      //�� ��� ���� �������� ����� �� ���� � �����
      fix_undefined_error_dr(carrent_active_functions);
      break;
    }
  }
  
  //����������, �� ����� ����� ����������� ����� �������� �� ����� � DataFlash
  routine_for_queue_dr();

  /*********************/
  //������� ���������� ���� ������� ��� ������� ���������/���������
  /*********************/
  for (unsigned int i = 0; i < N_BIG; i++) previous_active_functions[i] = carrent_active_functions[i];
  /*********************/
}
/*****************************************************/

/*****************************************************/
//������� ������� ����� ����������� ����������
/*****************************************************/
inline void analog_registrator(unsigned int* carrent_active_functions)
{
  static unsigned int prev_active_sources[N_BIG];
  unsigned int cur_active_sources[N_BIG];
  cur_active_sources[0] = carrent_active_functions[0] & current_settings_prt.ranguvannja_analog_registrator[0];
  cur_active_sources[1] = carrent_active_functions[1] & current_settings_prt.ranguvannja_analog_registrator[1];
  cur_active_sources[2] = carrent_active_functions[2] & current_settings_prt.ranguvannja_analog_registrator[2];
  cur_active_sources[3] = carrent_active_functions[3] & current_settings_prt.ranguvannja_analog_registrator[3];
  cur_active_sources[4] = carrent_active_functions[4] & current_settings_prt.ranguvannja_analog_registrator[4];
  cur_active_sources[5] = carrent_active_functions[5] & current_settings_prt.ranguvannja_analog_registrator[5];
  cur_active_sources[6] = carrent_active_functions[6] & current_settings_prt.ranguvannja_analog_registrator[6];
  cur_active_sources[7] = carrent_active_functions[7] & current_settings_prt.ranguvannja_analog_registrator[7];
  cur_active_sources[8] = carrent_active_functions[8] & current_settings_prt.ranguvannja_analog_registrator[8];
  cur_active_sources[9] = carrent_active_functions[9] & current_settings_prt.ranguvannja_analog_registrator[9];

  if (forbidden_new_record_ar_mode_0 != 0)
  {
    /*
    �� �������� ������, �� ���� ��������� ������� ����������� ����������, �� ���������
    � ������ ���������� ���������, � ����� ��� ������������� ��������� ��������� ����� ����� �� 
    ������ ��������, ��
    - �� ������� ��������� ������������� 
    - �������� ����� ������ �������, ����� �� ���� �����
    */
    if(
       (cur_active_sources[0] == 0) &&
       (cur_active_sources[1] == 0) &&
       (cur_active_sources[2] == 0) &&
       (cur_active_sources[3] == 0) &&
       (cur_active_sources[4] == 0) &&
       (cur_active_sources[5] == 0) &&
       (cur_active_sources[6] == 0) &&
       (cur_active_sources[7] == 0) &&
       (cur_active_sources[8] == 0) &&
       (cur_active_sources[9] == 0) 
      ) 
    {
      //����� ����� ������������� ��������� ������� ������ ������ ��������
      forbidden_new_record_ar_mode_0 = 0;
    }
    else if ((current_settings_prt.control_ar & CTR_AR_AVAR_STATE) == 0)
    {
      //��������� ����� ������� ��������� � DataFlash, ��� �� ���� ������� ��������� �� ���������������
      unsigned int diff_active_sources[N_BIG];
      diff_active_sources[0] = prev_active_sources[0] ^ cur_active_sources[0];
      diff_active_sources[1] = prev_active_sources[1] ^ cur_active_sources[1];
      diff_active_sources[2] = prev_active_sources[2] ^ cur_active_sources[2];
      diff_active_sources[3] = prev_active_sources[3] ^ cur_active_sources[3];
      diff_active_sources[4] = prev_active_sources[4] ^ cur_active_sources[4];
      diff_active_sources[5] = prev_active_sources[5] ^ cur_active_sources[5];
      diff_active_sources[6] = prev_active_sources[6] ^ cur_active_sources[6];
      diff_active_sources[7] = prev_active_sources[7] ^ cur_active_sources[7];
      diff_active_sources[8] = prev_active_sources[8] ^ cur_active_sources[8];
      diff_active_sources[9] = prev_active_sources[9] ^ cur_active_sources[9];

      if(
         ((diff_active_sources[0] & cur_active_sources[0]) != 0) ||
         ((diff_active_sources[1] & cur_active_sources[1]) != 0) ||
         ((diff_active_sources[2] & cur_active_sources[2]) != 0) ||
         ((diff_active_sources[3] & cur_active_sources[3]) != 0) ||
         ((diff_active_sources[4] & cur_active_sources[4]) != 0) ||
         ((diff_active_sources[5] & cur_active_sources[5]) != 0) ||
         ((diff_active_sources[6] & cur_active_sources[6]) != 0) ||
         ((diff_active_sources[7] & cur_active_sources[7]) != 0) ||
         ((diff_active_sources[8] & cur_active_sources[8]) != 0) ||
         ((diff_active_sources[9] & cur_active_sources[9]) != 0) 
        ) 
      {
        //����� ����� ������������� ��������� ������� ������ ������ ��������
        forbidden_new_record_ar_mode_0 = 0;
      }
    }
  }

  if (
      (global_timers[INDEX_TIMER_FULL_AR_RECORD] >= MAX_TIME_FULL_AR_RECORD) ||
      (state_ar_record_m == STATE_AR_BLOCK_M) ||
      (state_ar_record_fatfs == STATE_AR_MEMORY_FULL_FATFS) ||
      (state_ar_record_fatfs == STATE_AR_BLOCK_FATFS)
     )   
  {
    if (global_timers[INDEX_TIMER_FULL_AR_RECORD] >= MAX_TIME_FULL_AR_RECORD) _SET_BIT(set_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);

    state_ar_record_prt = STATE_AR_BLOCK_PRT;
    global_timers[INDEX_TIMER_POSTFAULT] = -1;
    global_timers[INDEX_TIMER_FULL_AR_RECORD] = -1;
  }
  
  switch (state_ar_record_prt)
  {
  case STATE_AR_NONE_PRT:
    {
      if (state_ar_record_fatfs == STATE_AR_NONE_FATFS)
      {
        global_timers[INDEX_TIMER_FULL_AR_RECORD] = -1;
        _SET_BIT(clear_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
      }

      //��������, �� ����� ����� ������� ����������� ����������
      if (
          (
           (cur_active_sources[0] != 0) ||
           (cur_active_sources[1] != 0) ||
           (cur_active_sources[2] != 0) ||
           (cur_active_sources[3] != 0) ||
           (cur_active_sources[4] != 0) ||
           (cur_active_sources[5] != 0) ||
           (cur_active_sources[6] != 0) ||
           (cur_active_sources[7] != 0) ||
           (cur_active_sources[8] != 0) ||
           (cur_active_sources[9] != 0)
          )
          &&  
          (forbidden_new_record_ar_mode_0 == 0) /*��� ��������� ����� ��.���������� (���� ���� ����) ��� �� ������� ��������� ���� ���� � ����� ���� ����� �������*/ 
         )
      {
        //� ����� ������� ����������� ����������

        if (state_ar_record_fatfs != STATE_AR_STOP_WRITE_FATFS)
        {
          //���������� ����� ������ �� ���������� ����������� � ���� "����� ������ ������"
          if (current_settings_prt.control_ar & CTR_AR_AVAR_STATE)
          {
            state_ar_record_prt = STATE_AR_AVAR_PRT;
          }
          else
          {
            state_ar_record_prt = STATE_AR_POSTAVAR_PRT;
            global_timers[INDEX_TIMER_POSTFAULT] = 0; //��������� ������ ������������� �������
          }
        
          if (state_ar_record_fatfs == STATE_AR_NONE_FATFS)
          {
            //����� �� ��� FATFs ����� �� �����������, ���� ����� ���������� ���������� ��� ����� ������ ������ ������
          
             global_timers[INDEX_TIMER_FULL_AR_RECORD] = 20*current_settings_prt.prefault_number_periods; //��������� ������ ������ ������  � ����������� ����� ������� ���������� �����
          
            //�������� ���� ������� ������
            header_ar.label_start_record = LABEL_START_RECORD_AR;
            //�������� ��� ������� ������
            unsigned char *label_to_time_array;
            if (copying_time == 2) label_to_time_array = time_copy;
            else label_to_time_array = time;
            for(unsigned int i = 0; i < 7; i++) header_ar.time[i] = *(label_to_time_array + i);
            //���������� ������������� T0
            header_ar.T0 = current_settings_prt.T0;
            //���������� ������������� TT
            header_ar.TCurrent = current_settings_prt.TCurrent;
            //���������� ������������� T�
            header_ar.TVoltage = current_settings_prt.TVoltage;
            //��� ����������� ������
            header_ar.prefault_number_periods = current_settings_prt.prefault_number_periods;
            //�'�� ������
            for(unsigned int i=0; i<MAX_CHAR_IN_NAME_OF_CELL; i++)
              header_ar.name_of_cell[i] = current_settings_prt.name_of_cell[i] & 0xff;
            //�������, �� ��������� � ������ ���������� ���������
            for (size_t i = 0; i < N_BIG; i++)
              header_ar.cur_active_sources[i] = (prev_active_sources[i] ^ cur_active_sources[i]) & cur_active_sources[i];
          }
        }
        else
        {
          _SET_BIT(set_diagnostyka, ERROR_AR_TEMPORARY_BUSY_BIT);
        }
      }

      break;
    }
  case STATE_AR_AVAR_PRT:
    {
      if (
          (
           (cur_active_sources[0] == 0) &&
           (cur_active_sources[1] == 0) &&
           (cur_active_sources[2] == 0) &&
           (cur_active_sources[3] == 0) &&
           (cur_active_sources[4] == 0) &&
           (cur_active_sources[5] == 0) &&
           (cur_active_sources[6] == 0) &&
           (cur_active_sources[7] == 0) &&
           (cur_active_sources[8] == 0) &&
           (cur_active_sources[9] == 0)
          )
          || 
          ((current_settings_prt.control_ar & CTR_AR_AVAR_STATE) == 0) /*���� ������� ����, ���� �� ��� ������ ��.���������� ������ �� ������������*/
         )
      {
        state_ar_record_prt = STATE_AR_POSTAVAR_PRT;
        global_timers[INDEX_TIMER_POSTFAULT] = 0; //��������� ������ ������������� �������
      }
      
      break;
    }
  case STATE_AR_POSTAVAR_PRT:
    {
      if (
          ((current_settings_prt.control_ar & CTR_AR_AVAR_STATE) != 0) &&
          (
           (cur_active_sources[0] != 0) ||
           (cur_active_sources[1] != 0) ||
           (cur_active_sources[2] != 0) ||
           (cur_active_sources[3] != 0) ||
           (cur_active_sources[4] != 0) ||
           (cur_active_sources[5] != 0) ||
           (cur_active_sources[6] != 0) ||
           (cur_active_sources[7] != 0) ||
           (cur_active_sources[8] != 0) ||
           (cur_active_sources[9] != 0)
          )
         )
      {
        //����������� �� ��������� �������
        state_ar_record_prt = STATE_AR_AVAR_PRT;
        global_timers[INDEX_TIMER_POSTFAULT] = -1; //��������� ������ ������������� �������
      }
      else if (global_timers[INDEX_TIMER_POSTFAULT] >= (int)(20*current_settings_prt.postfault_number_periods))
      {
        //���������� ������������ ������
        global_timers[INDEX_TIMER_POSTFAULT] = -1; //��������� ������ ������������� �������
        state_ar_record_prt = STATE_AR_NONE_PRT;
        
        if (
            /*�������� �� ��, �� ����� "�������������� ������" ��������� �� �����, �� ��� ���� �������� ������ �� � ������ � ��������� ����� �� � ������������ ������� ��� ������� �� ��������� �������*/
            (cur_active_sources[0] != 0) ||
            (cur_active_sources[1] != 0) ||
            (cur_active_sources[2] != 0) ||
            (cur_active_sources[3] != 0) ||
            (cur_active_sources[4] != 0) ||
            (cur_active_sources[5] != 0) ||
            (cur_active_sources[6] != 0) ||
            (cur_active_sources[7] != 0) ||
            (cur_active_sources[8] != 0) ||
            (cur_active_sources[9] != 0)
           )
        {
          forbidden_new_record_ar_mode_0 = 0xff; /*������� ����-���� ������, �� � ��������� ���� ������� �� ������������ �������*/
        }
      }
      
      break;
    }
  case STATE_AR_BLOCK_PRT:
    {
      //�������� �� ���� ����� ������ ����� ����� ���� �� �� ������ � ����������� �����
      if (
          (state_ar_record_fatfs == STATE_AR_NONE_FATFS) &&
          (state_ar_record_m == STATE_AR_NONE_M)
         )
      {
        state_ar_record_prt = STATE_AR_NONE_PRT;
        
        if(
           (cur_active_sources[0] != 0) ||
           (cur_active_sources[1] != 0) ||
           (cur_active_sources[2] != 0) ||
           (cur_active_sources[3] != 0) ||
           (cur_active_sources[4] != 0) ||
           (cur_active_sources[5] != 0) ||
           (cur_active_sources[6] != 0) ||
           (cur_active_sources[7] != 0) ||
           (cur_active_sources[8] != 0) ||
           (cur_active_sources[9] != 0)
          )   
        {
          forbidden_new_record_ar_mode_0 = 0xff; /*������� ����-���� ������, �� � ��������� ���� ������� �� ������������ �������*/
        }
      }
      
      break;
    }
  default:
    {
      //���������� ����� ����� �� ���� � ����
      total_error_sw_fixed(32);
      break;
    }
  }
  
  //�����������/�������� ������� ������ ����������� ����������
  if (
      (state_ar_record_prt == STATE_AR_AVAR_PRT) ||
      (state_ar_record_prt == STATE_AR_POSTAVAR_PRT)
     )
  {
    _SET_BIT(carrent_active_functions, RANG_WORK_A_REJESTRATOR);
  }
  else
  {
    _CLEAR_BIT(carrent_active_functions, RANG_WORK_A_REJESTRATOR);
  }

  prev_active_sources[0] = cur_active_sources[0];
  prev_active_sources[1] = cur_active_sources[1];
  prev_active_sources[2] = cur_active_sources[2];
  prev_active_sources[3] = cur_active_sources[3];
  prev_active_sources[4] = cur_active_sources[4];
  prev_active_sources[5] = cur_active_sources[5];
  prev_active_sources[6] = cur_active_sources[6];
  prev_active_sources[7] = cur_active_sources[7];
  prev_active_sources[8] = cur_active_sources[8];
  prev_active_sources[9] = cur_active_sources[9];
}
/*****************************************************/


/*****************************************************/
//������� ������� � ��� ����������� �� ���� ��������
/*****************************************************/
inline void main_protection(void)
{
  copying_active_functions = 1; //�������, �� ����� ���������� �������� �������� �������
  
  //������� � �������, �� ���������� �� �����, ������ � ��������� � ����������
  const unsigned int maska_input_signals[N_BIG] = 
  {
    MASKA_FOR_INPUT_SIGNALS_0, 
    MASKA_FOR_INPUT_SIGNALS_1, 
    MASKA_FOR_INPUT_SIGNALS_2, 
    MASKA_FOR_INPUT_SIGNALS_3, 
    MASKA_FOR_INPUT_SIGNALS_4, 
    MASKA_FOR_INPUT_SIGNALS_5, 
    MASKA_FOR_INPUT_SIGNALS_6, 
    MASKA_FOR_INPUT_SIGNALS_7, 
    MASKA_FOR_INPUT_SIGNALS_8, 
    MASKA_FOR_INPUT_SIGNALS_9
  };
  for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_input_signals[i]);
  
  /**************************/
  //��������, �� ����� �������� ������ �������
  /**************************/
  if (reset_trigger_function_from_interface !=0)
  {
    if ((reset_trigger_function_from_interface & (1 << USB_RECUEST)) != 0)
    {
      for (unsigned int i = 0; i < N_BIG; i++) trigger_functions_USB[i] = 0;
      
      information_about_restart_counter  &= (unsigned int)(~(1 << USB_RECUEST));
      information_about_clean_energy     &= (unsigned int)(~(1 << USB_RECUEST));
    }
    if ((reset_trigger_function_from_interface & (1 << RS485_RECUEST)) != 0)
    {
      for (unsigned int i = 0; i < N_BIG; i++) trigger_functions_RS485[i] = 0;
      
      information_about_restart_counter  &= (unsigned int)(~(1 << RS485_RECUEST));
      information_about_clean_energy     &= (unsigned int)(~(1 << RS485_RECUEST));
    }
    
    //������� �� �� �������� ������� �� �Ѳ� �����������
    reset_trigger_function_from_interface = 0;
  }
  /**************************/

  unsigned int blocking_commands_from_DI = 0;
  unsigned int active_inputs_grupa_ustavok = 0;
  /**************************/
  //����������� ��, �������� ����� � ������ �����
  /**************************/
  //���������� ����� ���������� ������
  uint32_t pressed_buttons_tmp = 0;
  uint32_t buttons_mode_tmp = current_settings_prt.buttons_mode;
  if (
      (mutex_buttons == false) &&
      (pressed_buttons != 0)
     )   
  {
    pressed_buttons_tmp = pressed_buttons;
    //������� �������� �����b, ���������� ��� ���� �� ��� ������� � ������ (��� �� �� ����������)
    pressed_buttons = 0;
  }
      
  uint32_t pressed_buttons_switcher = pressed_buttons_tmp & buttons_mode_tmp; /*�������� � ����� ������ ������-�����*/
  pressed_buttons_tmp &= (uint32_t)(~buttons_mode_tmp); /*�������� � ����� ������ �� ���� ���� ������*/
      
  //���������� �������� ������-�����
  uint32_t fix_active_buttons_tmp = (fix_active_buttons ^ pressed_buttons_switcher) & buttons_mode_tmp;
  if (fix_active_buttons_tmp != fix_active_buttons) 
  {
    fix_active_buttons = fix_active_buttons_tmp;
    /*
    �������� ����� ������-������
    */
    _SET_BIT(control_spi1_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT);
  }
    
  //������� ���� ���������� ������ � ����������� ������ ����� ����� ����� � ����� ������
  uint32_t pressed_buttons_united = pressed_buttons_tmp | fix_active_buttons_tmp;

  //������� ��������� ���������� ������-������
  for (size_t i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
  {
    uint32_t maska_yellow = ((1 << (i*NUMBER_LED_COLOR + LED_COLOR_RED_BIT)) | (1 << (i*NUMBER_LED_COLOR + LED_COLOR_GREEN_BIT)));
    if (((buttons_mode_tmp >> i) & 0x1) == BUTTON_MODE_SWITCHER)
    {
      if (((fix_active_buttons_tmp >> i) & 0x1) != 0) 
      {
#ifndef KEYBOARD_VER_2_1
        state_leds_Fx[0] &= (uint32_t)(~maska_yellow);
        state_leds_Fx[1] |= maska_yellow;
#else
        if (i != (4 - 1))
        {
          state_leds_Fx[0] &= (uint32_t)(~maska_yellow);
          state_leds_Fx[1] |= maska_yellow;
        }
        else
        {
          state_leds_Fx[1] &= (uint32_t)(~maska_yellow);
          state_leds_Fx[0] |= maska_yellow;
        }
#endif
      }    
      else
      {
#ifndef KEYBOARD_VER_2_1
        state_leds_Fx[1] &= (uint32_t)(~maska_yellow);
        state_leds_Fx[0] |= maska_yellow;
#else
        if (i != (4 - 1))
        {
          state_leds_Fx[1] &= (uint32_t)(~maska_yellow);
          state_leds_Fx[0] |= maska_yellow;
        }
        else
        {
          state_leds_Fx[0] &= (uint32_t)(~maska_yellow);
          state_leds_Fx[1] |= maska_yellow;
        }
#endif
      }    
    }
    else
    {
      state_leds_Fx[0] &= (uint32_t)(~maska_yellow);
      state_leds_Fx[1] &= (uint32_t)(~maska_yellow);
    }
  }

  //���������� �� � ����� ������ �����
  if (
      (pressed_buttons_united !=0)
      ||  
      (  
       (mutex_interface == false) &&
       (
        (activation_function_from_interface[0] != 0) ||
        (activation_function_from_interface[1] != 0) ||
        (activation_function_from_interface[2] != 0)
       )
      )
      ||  
      (active_inputs !=0)
     )   
  {
    unsigned int temp_value_for_activated_function_button_interface[N_SMALL] = {0, 0, 0};
    unsigned int temp_value_for_activated_function[N_SMALL] = {0, 0, 0};

    //��������� � �������
    if (pressed_buttons_united != 0)
    {
      for (unsigned int i = 0; i < NUMBER_DEFINED_BUTTONS; i++)
      {
        if ((pressed_buttons_united & (1 << i)) != 0)
        {
          unsigned int *point_temp_value_for_activated_function = ((pressed_buttons_tmp & (1 << i)) != 0) ? temp_value_for_activated_function_button_interface : temp_value_for_activated_function;
          point_temp_value_for_activated_function[0] |= current_settings_prt.ranguvannja_buttons[N_SMALL*i  ];
          point_temp_value_for_activated_function[1] |= current_settings_prt.ranguvannja_buttons[N_SMALL*i+1];
          point_temp_value_for_activated_function[2] |= current_settings_prt.ranguvannja_buttons[N_SMALL*i+2];
        }
      }
      if ((pressed_buttons_united & (1 << (BIT_KEY_C - BIT_KEY_1))) != 0)
      {
        _SET_BIT(temp_value_for_activated_function, RANG_SMALL_RESET_LEDS);
        _SET_BIT(temp_value_for_activated_function, RANG_SMALL_RESET_RELES);
      }
      if ((pressed_buttons_united & (1 << (BIT_KEY_I - BIT_KEY_1))) != 0) _SET_BIT(temp_value_for_activated_function, RANG_SMALL_VKL_VV);
      if ((pressed_buttons_united & (1 << (BIT_KEY_O - BIT_KEY_1))) != 0) _SET_BIT(temp_value_for_activated_function, RANG_SMALL_OTKL_VV);
    }
    
    //��������� � ����������
    if (mutex_interface == false)
    {
      temp_value_for_activated_function_button_interface[0] |= activation_function_from_interface[0];
      activation_function_from_interface[0] = 0;
      temp_value_for_activated_function_button_interface[1] |= activation_function_from_interface[1];
      activation_function_from_interface[1] = 0;
      temp_value_for_activated_function_button_interface[2] |= activation_function_from_interface[2];
      activation_function_from_interface[2] = 0;
    }
    
    //������� ��������� � ������ (����� ������) + ��������� � ���������� � ������ (����� ����) + ������ ����������� �����������
    temp_value_for_activated_function[0] |= temp_value_for_activated_function_button_interface[0];
    temp_value_for_activated_function[1] |= temp_value_for_activated_function_button_interface[1];
    temp_value_for_activated_function[2] |= temp_value_for_activated_function_button_interface[2];

    //��������� � �.�����
    unsigned int vvimk_VV_vid_DV = false;
    unsigned int vymk_VV_vid_DV = false;
    if (active_inputs != 0)
    {
      for (unsigned int i = 0; i < NUMBER_INPUTS; i++)
      {
        if ((active_inputs & (1 << i)) != 0)
        {
          if (
              (_CHECK_SET_BIT((current_settings_prt.ranguvannja_inputs + N_SMALL*i), RANG_SMALL_VKL_VV )) ||
              (_CHECK_SET_BIT((current_settings_prt.ranguvannja_inputs + N_SMALL*i), RANG_SMALL_OTKL_VV))
             )   
          {
            unsigned int ranguvannja_inputs_tmp[N_SMALL] = {
                                                            current_settings_prt.ranguvannja_inputs[N_SMALL*i  ],
                                                            current_settings_prt.ranguvannja_inputs[N_SMALL*i+1],
                                                            current_settings_prt.ranguvannja_inputs[N_SMALL*i+2]
                                                           };

            if (_CHECK_SET_BIT((current_settings_prt.ranguvannja_inputs + N_SMALL*i), RANG_SMALL_VKL_VV ))
            {
              vvimk_VV_vid_DV = true;
              _CLEAR_BIT(ranguvannja_inputs_tmp, RANG_SMALL_VKL_VV);
            }

            if (_CHECK_SET_BIT((current_settings_prt.ranguvannja_inputs + N_SMALL*i), RANG_SMALL_OTKL_VV ))
            {
              vymk_VV_vid_DV = true;
              _CLEAR_BIT(ranguvannja_inputs_tmp, RANG_SMALL_OTKL_VV);
            }

            temp_value_for_activated_function[0] |= ranguvannja_inputs_tmp[0];
            temp_value_for_activated_function[1] |= ranguvannja_inputs_tmp[1];
            temp_value_for_activated_function[2] |= ranguvannja_inputs_tmp[2];
          }
          else
          {
            temp_value_for_activated_function[0] |= current_settings_prt.ranguvannja_inputs[N_SMALL*i  ];
            temp_value_for_activated_function[1] |= current_settings_prt.ranguvannja_inputs[N_SMALL*i+1];
            temp_value_for_activated_function[2] |= current_settings_prt.ranguvannja_inputs[N_SMALL*i+2];
          }
        }
      }
    }
    
    //���������� �������
    for (unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
    {
      switch (i)
      {
      case 0:
        {
          active_functions[RANG_DF1_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DF1_IN) != 0) << (RANG_DF1_IN & 0x1f);
          break;
        }
      case 1:
        {
          active_functions[RANG_DF2_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DF2_IN) != 0) << (RANG_DF2_IN & 0x1f);
          break;
        }
      case 2:
        {
          active_functions[RANG_DF3_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DF3_IN) != 0) << (RANG_DF3_IN & 0x1f);
          break;
        }
      case 3:
        {
          active_functions[RANG_DF4_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DF4_IN) != 0) << (RANG_DF4_IN & 0x1f);
          break;
        }
      case 4:
        {
          active_functions[RANG_DF5_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DF5_IN) != 0) << (RANG_DF5_IN & 0x1f);
          break;
        }
      case 5:
        {
          active_functions[RANG_DF6_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DF6_IN) != 0) << (RANG_DF6_IN & 0x1f);
          break;
        }
      case 6:
        {
          active_functions[RANG_DF7_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DF7_IN) != 0) << (RANG_DF7_IN & 0x1f);
          break;
        }
      case 7:
        {
          active_functions[RANG_DF8_IN >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DF8_IN) != 0) << (RANG_DF8_IN & 0x1f);
          break;
        }
      default: break;
      }
    
      //�������� �� ����������� ����������� ��������� �-������� �� ���  ������� �����
      if (_CHECK_SET_BIT(temp_value_for_activated_function_button_interface, (RANG_SMALL_DF1_IN + i)) != 0)
      {
        //����� �� ������������ �-��������, ���� ����� ��������� ������ �� �����������,
        //��� ����, ��� ���� ��� ��� ����� ���� ������� � ����� ������� �����
        if (global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] < 0)
        {
          //��������� ������ ������ ����������� ���� ������� � ��������� ���� (������� ��������� �����)
          //������ ������ ����� �� ���� ��������, ���� �� �� �� �������
          global_timers[INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START + i] = 0;
        }
      }
    }

    //���������� ������
    for (unsigned int i = 0; i < NUMBER_DEFINED_TRIGGERS; i++)
    {
      switch (i)
      {
      case 0:
        {
          active_functions[RANG_DT1_SET   >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DT1_SET  ) != 0) << (RANG_DT1_SET   & 0x1f);
          active_functions[RANG_DT1_RESET >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DT1_RESET) != 0) << (RANG_DT1_RESET & 0x1f);
          break;
        }
      case 1:
        {
          active_functions[RANG_DT2_SET   >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DT2_SET  ) != 0) << (RANG_DT2_SET   & 0x1f);
          active_functions[RANG_DT2_RESET >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DT2_RESET) != 0) << (RANG_DT2_RESET & 0x1f);
          break;
        }
      case 2:
        {
          active_functions[RANG_DT3_SET   >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DT3_SET  ) != 0) << (RANG_DT3_SET   & 0x1f);
          active_functions[RANG_DT3_RESET >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DT3_RESET) != 0) << (RANG_DT3_RESET & 0x1f);
          break;
        }
      case 3:
        {
          active_functions[RANG_DT4_SET   >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DT4_SET  ) != 0) << (RANG_DT4_SET   & 0x1f);
          active_functions[RANG_DT4_RESET >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_DT4_RESET) != 0) << (RANG_DT4_RESET & 0x1f);
          break;
        }
      default: break;
      }
    }
    
      
    //������� ������� (��� ��-�� � �������, �� ������ ����������� � �������� ��������)
    active_functions[RANG_BLOCK_VKL_VV                      >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_VKL_VV                     ) != 0) << (RANG_BLOCK_VKL_VV                      & 0x1f);
    active_functions[RANG_RESET_LEDS                        >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_RESET_LEDS                       ) != 0) << (RANG_RESET_LEDS                        & 0x1f);
    active_functions[RANG_RESET_RELES                       >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_RESET_RELES                      ) != 0) << (RANG_RESET_RELES                       & 0x1f);
    active_functions[RANG_MISCEVE_DYSTANCIJNE               >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_MISCEVE_DYSTANCIJNE              ) != 0) << (RANG_MISCEVE_DYSTANCIJNE               & 0x1f);
    active_functions[RANG_STATE_VV                          >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_STATE_VV                         ) != 0) << (RANG_STATE_VV                          & 0x1f);
    active_functions[RANG_CTRL_VKL                          >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_CTRL_VKL                         ) != 0) << (RANG_CTRL_VKL                          & 0x1f);
    active_functions[RANG_CTRL_OTKL                         >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_CTRL_OTKL                        ) != 0) << (RANG_CTRL_OTKL                         & 0x1f);
    active_functions[RANG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_RESET_BLOCK_READY_TU_VID_ZAHYSTIV) != 0) << (RANG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV & 0x1f);
    active_functions[RANG_OTKL_VID_ZOVN_ZAHYSTIV            >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_OTKL_VID_ZOVN_ZAHYSTIV     ) != 0) << (RANG_OTKL_VID_ZOVN_ZAHYSTIV            & 0x1f);

    active_inputs_grupa_ustavok |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_1_GRUPA_USTAVOK    ) != 0) << (RANG_SMALL_1_GRUPA_USTAVOK - RANG_SMALL_1_GRUPA_USTAVOK);
    active_inputs_grupa_ustavok |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_2_GRUPA_USTAVOK    ) != 0) << (RANG_SMALL_2_GRUPA_USTAVOK - RANG_SMALL_1_GRUPA_USTAVOK);
    active_inputs_grupa_ustavok |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_3_GRUPA_USTAVOK    ) != 0) << (RANG_SMALL_3_GRUPA_USTAVOK - RANG_SMALL_1_GRUPA_USTAVOK);
    active_inputs_grupa_ustavok |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_4_GRUPA_USTAVOK    ) != 0) << (RANG_SMALL_4_GRUPA_USTAVOK - RANG_SMALL_1_GRUPA_USTAVOK);
      
    //������� ������� (�� ����������� � �������� ��������)
    //��������� ��
    active_functions[RANG_VKL_VV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_VKL_VV) != 0) << (RANG_VKL_VV & 0x1f);
    if (vvimk_VV_vid_DV)
    {
      if (
          (_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE )) &&
          (current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_BLK_ON_CB_MISCEVE)
         ) 
      {
        //����� ���������� �������� "��������� ��" �� ���.
        blocking_commands_from_DI |= CTR_EXTRA_SETTINGS_1_BLK_ON_CB_MISCEVE;
      }
      else _SET_BIT(active_functions, RANG_VKL_VV);
    }

    //��������� ��
    active_functions[RANG_OTKL_VV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_OTKL_VV) != 0) << (RANG_OTKL_VV & 0x1f);
    if (vymk_VV_vid_DV)
    {
      if (
          (_CHECK_SET_BIT(active_functions, RANG_MISCEVE_DYSTANCIJNE )) &&
          (current_settings_prt.control_extra_settings_1 & CTR_EXTRA_SETTINGS_1_BLK_OFF_CB_MISCEVE)
         ) 
      {
        //����� ���������� �������� "��������� ��" �� ���.
        blocking_commands_from_DI |= CTR_EXTRA_SETTINGS_1_BLK_OFF_CB_MISCEVE;
      }
      else _SET_BIT(active_functions, RANG_OTKL_VV);
    }

    //���� ��� ��
    active_functions[RANG_EXT_NKN_DZ   >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_EXT_NKN_DZ    ) != 0) << (RANG_EXT_NKN_DZ   & 0x1f);
    active_functions[RANG_BLOCK_DZ1    >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_DZ1     ) != 0) << (RANG_BLOCK_DZ1    & 0x1f);
    active_functions[RANG_BLOCK_DZ2    >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_DZ2     ) != 0) << (RANG_BLOCK_DZ2    & 0x1f);
    active_functions[RANG_BLOCK_PR_DZ2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_PR_DZ2  ) != 0) << (RANG_BLOCK_PR_DZ2 & 0x1f);
    active_functions[RANG_OP_PR_DZ2    >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_OP_PR_DZ2     ) != 0) << (RANG_OP_PR_DZ2    & 0x1f);
    active_functions[RANG_BLOCK_DZ3    >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_DZ3     ) != 0) << (RANG_BLOCK_DZ3    & 0x1f);
    active_functions[RANG_BLOCK_PR_DZ3 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_PR_DZ3  ) != 0) << (RANG_BLOCK_PR_DZ3 & 0x1f);
    active_functions[RANG_OP_PR_DZ3    >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_OP_PR_DZ3     ) != 0) << (RANG_OP_PR_DZ3    & 0x1f);
    active_functions[RANG_BLOCK_DZ4    >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_DZ4     ) != 0) << (RANG_BLOCK_DZ4    & 0x1f);
    active_functions[RANG_BLOCK_PR_DZ4 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_PR_DZ4  ) != 0) << (RANG_BLOCK_PR_DZ4 & 0x1f);
    active_functions[RANG_OP_PR_DZ4    >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_OP_PR_DZ4     ) != 0) << (RANG_OP_PR_DZ4    & 0x1f);

    //���
    active_functions[RANG_BLOCK_MTZ1     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_MTZ1    ) != 0) << (RANG_BLOCK_MTZ1     & 0x1f);
    active_functions[RANG_BLOCK_MTZ2     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_MTZ2    ) != 0) << (RANG_BLOCK_MTZ2     & 0x1f);
    active_functions[RANG_BLOCK_USK_MTZ2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_USK_MTZ2) != 0) << (RANG_BLOCK_USK_MTZ2 & 0x1f);
    active_functions[RANG_BLOCK_MTZ3     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_MTZ3    ) != 0) << (RANG_BLOCK_MTZ3     & 0x1f);
    active_functions[RANG_BLOCK_MTZ4     >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_MTZ4    ) != 0) << (RANG_BLOCK_MTZ4     & 0x1f);

    //���� ��� ���
    active_functions[RANG_BLOCK_ZDZ       >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_ZDZ      ) != 0) << (RANG_BLOCK_ZDZ       & 0x1f);
    active_functions[RANG_PUSK_ZDZ_VID_DV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_PUSK_ZDZ_VID_DV) != 0) << (RANG_PUSK_ZDZ_VID_DV & 0x1f);

    //���
    active_functions[RANG_BLOCK_NZZ >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_NZZ) != 0) << (RANG_BLOCK_NZZ & 0x1f);

    //���� ����
    active_functions[RANG_BLOCK_TZNP1 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_TZNP1) != 0) << (RANG_BLOCK_TZNP1 & 0x1f);
    active_functions[RANG_BLOCK_TZNP2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_TZNP2) != 0) << (RANG_BLOCK_TZNP2 & 0x1f);
    active_functions[RANG_BLOCK_TZNP3 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_TZNP3) != 0) << (RANG_BLOCK_TZNP3 & 0x1f);

    //���
    active_functions[RANG_STAT_BLK_APV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_STAT_BLK_APV) != 0) << (RANG_STAT_BLK_APV & 0x1f);
      
    //����
    active_functions[RANG_ACHR_CHAPV_VID_DV  >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_ACHR_CHAPV_VID_DV ) != 0) << (RANG_ACHR_CHAPV_VID_DV & 0x1f);
    active_functions[RANG_BLOCK_ACHR1        >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_ACHR1      ) != 0) << (RANG_BLOCK_ACHR1       & 0x1f);
    active_functions[RANG_BLOCK_ACHR2        >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_ACHR2      ) != 0) << (RANG_BLOCK_ACHR2       & 0x1f);

    //����
    active_functions[RANG_PUSK_UROV_VID_DV >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_PUSK_UROV_VID_DV) != 0) << (RANG_PUSK_UROV_VID_DV & 0x1f);

    //���� ���(���)
    active_functions[RANG_BLOCK_ZOP >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_ZOP) != 0) << (RANG_BLOCK_ZOP & 0x1f);

    //���� ��� Umin
    active_functions[RANG_BLOCK_UMIN1 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_UMIN1) != 0) << (RANG_BLOCK_UMIN1 & 0x1f);
    active_functions[RANG_START_UMIN1 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_START_UMIN1) != 0) << (RANG_START_UMIN1 & 0x1f);
    active_functions[RANG_BLOCK_UMIN2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_UMIN2) != 0) << (RANG_BLOCK_UMIN2 & 0x1f);
    active_functions[RANG_START_UMIN2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_START_UMIN2) != 0) << (RANG_START_UMIN2 & 0x1f);
      
    //���� ��� Umax
    active_functions[RANG_BLOCK_UMAX1 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_UMAX1) != 0) << (RANG_BLOCK_UMAX1 & 0x1f);
    active_functions[RANG_BLOCK_UMAX2 >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, RANG_SMALL_BLOCK_UMAX2) != 0) << (RANG_BLOCK_UMAX2 & 0x1f);

    //���������� ��� ��
    for (size_t i = 0; i < NUMBER_UP; i++)
    {
      uint32_t rang_small_block_up = RANG_SMALL_BLOCK_UP1 + i;
      uint32_t rang_block_up = RANG_BLOCK_UP1 + 3*i;
      active_functions[rang_block_up >> 5] |= (_CHECK_SET_BIT(temp_value_for_activated_function, rang_small_block_up) != 0) << (rang_block_up & 0x1f);
    }
  }
  /**************************/

  /**************************/
  //�������� ���������� ���������� ������ ��� ��� �������, �� ����� ������������ ����� �� ���������� �������
  /**************************/
  {
    static unsigned int previous_activating_functions[N_BIG];
    //������� ����� �������, �� ����� ���������, �� ������ ����� � ������ �������� � "0" � "1"
    unsigned int temp_maska_filter_function[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned int temp_activating_functions[N_BIG] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  
    //������ "����� ���������"
    _SET_BIT(temp_maska_filter_function, RANG_RESET_LEDS);
  
    //������ "����� ����"
    _SET_BIT(temp_maska_filter_function, RANG_RESET_RELES);

    //������ "�������� ��"
    _SET_BIT(temp_maska_filter_function, RANG_VKL_VV);
    
    //������ "��������� ��"
    _SET_BIT(temp_maska_filter_function, RANG_OTKL_VV);

    //������ "�������� ���������� ��������� �� ��"
    _SET_BIT(temp_maska_filter_function, RANG_RESET_BLOCK_READY_TU_VID_ZAHYSTIV);
  
    for (unsigned int i = 0; i < N_BIG; i++)
    {
      //� ������ ��������� ����� �������� ����� � �������, ��� ��� �������� ����� ��� � ������� �� � ���������� �����
      temp_activating_functions[i] = previous_activating_functions[i] & temp_maska_filter_function[i];
  
      //� ����������� ����� �������� ����� � �������, � ���� ����������� ��� �������, ��� ����� ������
      temp_activating_functions[i] ^= (active_functions[i] & temp_maska_filter_function[i]);
  
      //����� �������� � ����������� ����� ����� � ������� � ���� ����� �������� ������ ��� "1" (����� ������� ������� � "0" � "1")
      temp_activating_functions[i] &= active_functions[i];

      /*
      ����� ���, �� ������� � �������, �� � ����� ���� ������ ������ �� ������ 
      � ����������� ����, �� ���� ������� ����������� �� ���������� �����
      ������� ��������� ���� ������� (��� ���������� ������) � ���������� �����
      ��� ��� ���������� ����� ���� ��������� ��������� ���� �������� �������
      */ 
      previous_activating_functions[i] = active_functions[i];

      //���������� ����� �������, �� ����� ����������� � ����������� ����, �� ����� �������� ������� ������ ��������� ����� ���� ����� �, � ���� ������� ��� � "0" � "1"
      active_functions[i] = (active_functions[i] & (~temp_maska_filter_function[i])) | temp_activating_functions[i];
    }
  }
  /**************************/
  
  /**************************
  ������� ��������� ����� ��������
  **************************/
  {
    uint32_t state_vv_dv = false;
    for (size_t i = 0; i < NUMBER_INPUTS; i++)
    {
      if (_CHECK_SET_BIT ((current_settings_prt.ranguvannja_inputs + N_SMALL*i), RANG_SMALL_STATE_VV) != 0)
      {
        state_vv_dv = true;
        break;
      }
    }
    
    if (state_vv_dv)
    {
      if (_CHECK_SET_BIT(active_functions, RANG_STATE_VV) !=0) 
      {
        state_leds_ctrl &=  (uint32_t)(~((1 << LED_COLOR_GREEN_BIT) << ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_O)));
        state_leds_ctrl |=  (uint32_t)(  (1 << LED_COLOR_RED_BIT  ) << ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_I) );
      }
      else
      {
        state_leds_ctrl &=  (uint32_t)(~((1 << LED_COLOR_RED_BIT  ) << ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_I)));
        state_leds_ctrl |=  (uint32_t)(  (1 << LED_COLOR_GREEN_BIT) << ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_O) );
      }
    }
    else
    {
      state_leds_ctrl &=  (uint32_t)(~(((1 << LED_COLOR_GREEN_BIT) << ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_O)) | ((1 << LED_COLOR_RED_BIT) << ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_I))));
    }
  }
  /**************************/

  /**************************/
  //���� ����� �������
  /**************************/
  for (size_t i = 0; i < NUMBER_GROUP_USTAVOK; i++)
  {
    if (active_inputs_grupa_ustavok & (1 << i)) 
    {
      _CLEAR_BIT(active_functions, RANG_INVERS_DV_GRUPA_USTAVOK);
      break;
    }
    else
    {
      if (i == (NUMBER_GROUP_USTAVOK - 1)) _SET_BIT(active_functions, RANG_INVERS_DV_GRUPA_USTAVOK);
    }
  }
  
  if (count_number_set_bit(&active_inputs_grupa_ustavok, NUMBER_GROUP_USTAVOK) > 1)
    _SET_BIT(set_diagnostyka, ERROR_SELECT_GRUPY_USRAVOK);
  else
    _SET_BIT(clear_diagnostyka, ERROR_SELECT_GRUPY_USRAVOK);
   
  if (
      ((active_functions[0] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_0) != 0) ||
      ((active_functions[1] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_1) != 0) ||
      ((active_functions[2] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_2) != 0) ||
      ((active_functions[3] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_3) != 0) ||
      ((active_functions[4] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_4) != 0) ||
      ((active_functions[5] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_5) != 0) ||
      ((active_functions[6] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_6) != 0) ||
      ((active_functions[7] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_7) != 0) ||
      ((active_functions[8] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_8) != 0) ||
      ((active_functions[9] & MASKA_SIGNALES_FOR_LOCK_GROUP_PICKUP_9) != 0)
    )
  {
    //��� ���������� ���� ������� - ����� ������� ���������� ���, ��� ������� ����������
    _SET_BIT(active_functions, RANG_BLK_GRUP_USTAVOK_VID_ZACHYSTIV);

    unsigned int number_group_stp_tmp = 0;
    if(( _CHECK_SET_BIT(active_functions, RANG_1_GRUPA_USTAVOK) ) !=0 ) number_group_stp_tmp++;
    if(( _CHECK_SET_BIT(active_functions, RANG_2_GRUPA_USTAVOK) ) !=0 ) number_group_stp_tmp++;
    if(( _CHECK_SET_BIT(active_functions, RANG_3_GRUPA_USTAVOK) ) !=0 ) number_group_stp_tmp++;
    if(( _CHECK_SET_BIT(active_functions, RANG_4_GRUPA_USTAVOK) ) !=0 ) number_group_stp_tmp++;
    
    if (number_group_stp_tmp != 1)
    {
      //���������� ����� ����� �� ���� � ����
      total_error_sw_fixed(52);
    }
  }
  else
  {
    //����� �������� ����� ������� - ������� �� �������� �� ��������
    _CLEAR_BIT(active_functions, RANG_BLK_GRUP_USTAVOK_VID_ZACHYSTIV);
    setpoints_selecting(active_functions, active_inputs_grupa_ustavok);
  }

  unsigned int number_group_stp;
  if     (( _CHECK_SET_BIT(active_functions, RANG_1_GRUPA_USTAVOK) ) !=0 ) number_group_stp = 0;
  else if(( _CHECK_SET_BIT(active_functions, RANG_2_GRUPA_USTAVOK) ) !=0 ) number_group_stp = 1;
  else if(( _CHECK_SET_BIT(active_functions, RANG_3_GRUPA_USTAVOK) ) !=0 ) number_group_stp = 2;
  else if(( _CHECK_SET_BIT(active_functions, RANG_4_GRUPA_USTAVOK) ) !=0 ) number_group_stp = 3;
  else
  {
    //���������� ����� ����� �� ���� � ����
    total_error_sw_fixed(51);
  }
  /**************************/

  /***********************************************************/
  //���������� ���������
  /***********************************************************/
  calc_measurement(number_group_stp);

      
//  //ĳ��������� ��������� ��� �� �����
//  diagnostyca_adc_execution();
  
  //������� ���������� ��� ����������������� � ����������������� �������
  unsigned int bank_measurement_high_tmp = (bank_measurement_high ^ 0x1) & 0x1;
  if(semaphore_measure_values_low1 == 0)
  {
    for (unsigned int i = 0; i < _NUMBER_IM; i++) 
    {
      measurement_high[bank_measurement_high_tmp][i] = measurement_middle[i] = measurement[i];
    }
    for (unsigned int i = 0; i < MAX_NUMBER_INDEXES_RESISTANCE; i++) resistance_middle[i] = resistance[i];
  }
  else
  {
    for (unsigned int i = 0; i < _NUMBER_IM; i++) 
    {
      measurement_high[bank_measurement_high_tmp][i] = measurement[i];
    }
  }
  bank_measurement_high = bank_measurement_high_tmp;
  /***********************************************************/
  
  
  /**************************/
  //������ "������������ �����"
  /**************************/
  unsigned int diagnostyka_tmp[N_DIAGN];
  for (size_t i = 0; i < N_DIAGN; i ++)
  {
    diagnostyka_tmp[i] = diagnostyka[i];

    diagnostyka_tmp[i] &= (unsigned int)(~clear_diagnostyka[i]); 
    diagnostyka_tmp[i] |= set_diagnostyka[i]; 
  }

  _CLEAR_BIT(diagnostyka_tmp, EVENT_START_SYSTEM_BIT);
  _CLEAR_BIT(diagnostyka_tmp, EVENT_SOFT_RESTART_SYSTEM_BIT);
  _CLEAR_BIT(diagnostyka_tmp, EVENT_DROP_POWER_BIT);
  unsigned int not_null = false;
  for (size_t i = 0; i < N_DIAGN; i++) 
  {
    not_null |= (diagnostyka_tmp[i] != 0);
    if (not_null) break;
  }
              
  if (not_null)
  {
    _SET_BIT(active_functions, RANG_DEFECT);
    /**************************/
    //������ "������������ ���������"
    /**************************/
    const unsigned int maska_avar_error[N_DIAGN] = {MASKA_AVAR_ERROR_0, MASKA_AVAR_ERROR_1, MASKA_AVAR_ERROR_2};

    not_null = false;
    for (size_t i = 0; i < N_DIAGN; i++) 
    {
      not_null |= ((diagnostyka_tmp[i] & maska_avar_error[i])  != 0);
      if (not_null) break;
    }
    if (not_null)
    {
      _SET_BIT(active_functions, RANG_AVAR_DEFECT);
    }
    else
    {
      _CLEAR_BIT(active_functions, RANG_AVAR_DEFECT);
    }
    /**************************/
  }
  else
  {
    _CLEAR_BIT(active_functions, RANG_DEFECT);
    _CLEAR_BIT(active_functions, RANG_AVAR_DEFECT);
  }
  /**************************/

  
  static unsigned int previous_active_functions[N_BIG];
  
  //����� ����� ����� ��������� ����� � ���� �������, ���� ��� ������� "��������� �������������"
  if (_CHECK_SET_BIT(active_functions, RANG_AVAR_DEFECT) == 0)
  {
    //������� �������� �� �����������
    
    /**************************/
    //������� ������������� �������
    /**************************/
    tf_handler(previous_active_functions, active_functions);
    /**************************/

    /**************************/
    //�������� ������� ��
    /**************************/
    control_VV(active_functions);
    /**************************/

    /**************************/
    //��
    /**************************/
    if ((current_settings_prt.configuration & (1 << DZ_BIT_CONFIGURATION)) != 0)
    {
      dz_handler(active_functions, number_group_stp);
    }
    else
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_dz_signals[N_BIG] = 
      {
        MASKA_DZ_SIGNALS_0, 
        MASKA_DZ_SIGNALS_1, 
        MASKA_DZ_SIGNALS_2,
        MASKA_DZ_SIGNALS_3, 
        MASKA_DZ_SIGNALS_4, 
        MASKA_DZ_SIGNALS_5, 
        MASKA_DZ_SIGNALS_6, 
        MASKA_DZ_SIGNALS_7, 
        MASKA_DZ_SIGNALS_8, 
        MASKA_DZ_SIGNALS_9
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_dz_signals[i]);
      
      global_timers[INDEX_TIMER_DZ1] = -1;
      global_timers[INDEX_TIMER_DZ1_AMTZ] = -1;
      global_timers[INDEX_TIMER_DZ2_DIR] = -1;
      global_timers[INDEX_TIMER_DZ2_DIR_PR] = -1;
      global_timers[INDEX_TIMER_DZ2_INV] = -1;
      global_timers[INDEX_TIMER_DZ2_INV_PR] = -1;
      global_timers[INDEX_TIMER_DZ2_AMTZ] = -1;
      global_timers[INDEX_TIMER_DZ2_AMTZ_PR] = -1;
      global_timers[INDEX_TIMER_DZ2_VVID_PR] = -1;
      global_timers[INDEX_TIMER_DZ2_AMTZ_VVID_PR] = -1;
      global_timers[INDEX_TIMER_DZ3_DIR] = -1;
      global_timers[INDEX_TIMER_DZ3_DIR_PR] = -1;
      global_timers[INDEX_TIMER_DZ3_INV] = -1;
      global_timers[INDEX_TIMER_DZ3_INV_PR] = -1;
      global_timers[INDEX_TIMER_DZ3_AMTZ] = -1;
      global_timers[INDEX_TIMER_DZ3_AMTZ_PR] = -1;
      global_timers[INDEX_TIMER_DZ3_VVID_PR] = -1;
      global_timers[INDEX_TIMER_DZ3_AMTZ_VVID_PR] = -1;
      global_timers[INDEX_TIMER_DZ4_DIR] = -1;
      global_timers[INDEX_TIMER_DZ4_DIR_PR] = -1;
      global_timers[INDEX_TIMER_DZ4_INV] = -1;
      global_timers[INDEX_TIMER_DZ4_INV_PR] = -1;
      global_timers[INDEX_TIMER_DZ4_AMTZ] = -1;
      global_timers[INDEX_TIMER_DZ4_AMTZ_PR] = -1;
      global_timers[INDEX_TIMER_DZ4_VVID_PR] = -1;
      global_timers[INDEX_TIMER_DZ4_AMTZ_VVID_PR] = -1;
      global_timers[INDEX_TIMER_NKN_DZ] = -1;
    }
    /**************************/

    /**************************/
    //���
    /**************************/
    if ((current_settings_prt.configuration & (1 << MTZ_BIT_CONFIGURATION)) != 0)
    {
      mtz_handler(active_functions, number_group_stp);
    }
    else
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_mtz_signals[N_BIG] = 
      {
        MASKA_MTZ_SIGNALS_0,
        MASKA_MTZ_SIGNALS_1,
        MASKA_MTZ_SIGNALS_2, 
        MASKA_MTZ_SIGNALS_3, 
        MASKA_MTZ_SIGNALS_4, 
        MASKA_MTZ_SIGNALS_5,
        MASKA_MTZ_SIGNALS_6, 
        MASKA_MTZ_SIGNALS_7, 
        MASKA_MTZ_SIGNALS_8, 
        MASKA_MTZ_SIGNALS_9
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_mtz_signals[i]);
      
      global_timers[INDEX_TIMER_MTZ1] = -1;
      global_timers[INDEX_TIMER_MTZ1_N_VPERED] = -1;
      global_timers[INDEX_TIMER_MTZ1_N_NAZAD] = -1;
      global_timers[INDEX_TIMER_MTZ1_PO_NAPRUZI] = -1;
      global_timers[INDEX_TIMER_MTZ2] = -1;
      global_timers[INDEX_TIMER_MTZ2_DEPENDENT] = -1;
      global_timers[INDEX_TIMER_MTZ2_PR] = -1;
      global_timers[INDEX_TIMER_MTZ2_N_VPERED] = -1;
      global_timers[INDEX_TIMER_MTZ2_N_VPERED_PR] = -1;
      global_timers[INDEX_TIMER_MTZ2_N_NAZAD] = -1;
      global_timers[INDEX_TIMER_MTZ2_N_NAZAD_PR] = -1;
      global_timers[INDEX_TIMER_MTZ2_PO_NAPRUZI] = -1;
      global_timers[INDEX_TIMER_MTZ2_PO_NAPRUZI_PR] = -1;
      global_timers[INDEX_TIMER_MTZ2_VVID_PR] = -1;
      global_timers[INDEX_TIMER_MTZ3] = -1;
      global_timers[INDEX_TIMER_MTZ3_N_VPERED] = -1;
      global_timers[INDEX_TIMER_MTZ3_N_NAZAD] = -1;
      global_timers[INDEX_TIMER_MTZ3_PO_NAPRUZI] = -1;
      global_timers[INDEX_TIMER_MTZ4] = -1;
      global_timers[INDEX_TIMER_MTZ4_N_VPERED] = -1;
      global_timers[INDEX_TIMER_MTZ4_N_NAZAD] = -1;
      global_timers[INDEX_TIMER_MTZ4_PO_NAPRUZI] = -1;
    }
    /**************************/
    
    /**************************/
    //��
    /**************************/
    if ((current_settings_prt.configuration & (1 << ZZ_BIT_CONFIGURATION)) != 0)
    {
      zz_handler(active_functions, number_group_stp);
    }
    else
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_nzz_signals[N_BIG] = 
      {
        MASKA_NZZ_SIGNALS_0, 
        MASKA_NZZ_SIGNALS_1, 
        MASKA_NZZ_SIGNALS_2,
        MASKA_NZZ_SIGNALS_3, 
        MASKA_NZZ_SIGNALS_4, 
        MASKA_NZZ_SIGNALS_5, 
        MASKA_NZZ_SIGNALS_6, 
        MASKA_NZZ_SIGNALS_7, 
        MASKA_NZZ_SIGNALS_8, 
        MASKA_NZZ_SIGNALS_9
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_nzz_signals[i]);

      global_timers[INDEX_TIMER_ZZ_3I0] = -1;
      global_timers[INDEX_TIMER_ZZ_3U0] = -1;
      global_timers[INDEX_TIMER_NZZ] = -1;
    }
    /**************************/

    /**************************/
    //����
    /**************************/
    if ((current_settings_prt.configuration & (1 << TZNP_BIT_CONFIGURATION)) != 0)
    {
      tznp_handler(active_functions, number_group_stp);
    }
    else
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_tznp_signals[N_BIG] = 
      {
        MASKA_TZNP_SIGNALS_0, 
        MASKA_TZNP_SIGNALS_1, 
        MASKA_TZNP_SIGNALS_2,
        MASKA_TZNP_SIGNALS_3, 
        MASKA_TZNP_SIGNALS_4, 
        MASKA_TZNP_SIGNALS_5, 
        MASKA_TZNP_SIGNALS_6, 
        MASKA_TZNP_SIGNALS_7, 
        MASKA_TZNP_SIGNALS_8, 
        MASKA_TZNP_SIGNALS_9
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_tznp_signals[i]);

      global_timers[INDEX_TIMER_TZNP1_VPERED] = -1;
      global_timers[INDEX_TIMER_TZNP1_NAZAD] = -1;
      global_timers[INDEX_TIMER_TZNP2_VPERED] = -1;
      global_timers[INDEX_TIMER_TZNP2_NAZAD] = -1;
      global_timers[INDEX_TIMER_TZNP3_VPERED] = -1;
      global_timers[INDEX_TIMER_TZNP3_NAZAD] = -1;
    }
    /**************************/
  
    /**************************/
    //���(���)
    /**************************/
    if ((current_settings_prt.configuration & (1 << ZOP_BIT_CONFIGURATION)) != 0)
    {
      zop_handler(active_functions, number_group_stp);
    }
    else
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_zop_signals[N_BIG] = 
      {
        MASKA_ZOP_SIGNALS_0, 
        MASKA_ZOP_SIGNALS_1, 
        MASKA_ZOP_SIGNALS_2,
        MASKA_ZOP_SIGNALS_3, 
        MASKA_ZOP_SIGNALS_4, 
        MASKA_ZOP_SIGNALS_5, 
        MASKA_ZOP_SIGNALS_6, 
        MASKA_ZOP_SIGNALS_7, 
        MASKA_ZOP_SIGNALS_8, 
        MASKA_ZOP_SIGNALS_9
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_zop_signals[i]);
      global_timers[INDEX_TIMER_ZOP] = -1;
    }
    /**************************/
    
    if ((current_settings_prt.configuration & (1 << UMIN_BIT_CONFIGURATION)) != 0) 
    {
      /**************************/
      //�����1
      /**************************/
      umin1_handler(active_functions, number_group_stp);
      /**************************/
      
      /**************************/
      //�����2
      /**************************/
      umin2_handler(active_functions, number_group_stp);
      /**************************/
    } 
    else 
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_umin_signals[N_BIG] = 
      {
        MASKA_UMIN_SIGNALS_0, 
        MASKA_UMIN_SIGNALS_1, 
        MASKA_UMIN_SIGNALS_2,
        MASKA_UMIN_SIGNALS_3, 
        MASKA_UMIN_SIGNALS_4, 
        MASKA_UMIN_SIGNALS_5, 
        MASKA_UMIN_SIGNALS_6, 
        MASKA_UMIN_SIGNALS_7, 
        MASKA_UMIN_SIGNALS_8, 
        MASKA_UMIN_SIGNALS_9
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_umin_signals[i]);

      global_timers[INDEX_TIMER_UMIN1] = -1;
      global_timers[INDEX_TIMER_UMIN2] = -1;
    }
    
    if ((current_settings_prt.configuration & (1 << UMAX_BIT_CONFIGURATION)) != 0) 
    {
      /**************************/
      //������1
      /**************************/
      umax1_handler(active_functions, number_group_stp);
      /**************************/
      
      /**************************/
      //������2
      /**************************/
      umax2_handler(active_functions, number_group_stp);
      /**************************/
    } 
    else 
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_umax_signals[N_BIG] = 
      {
        MASKA_UMAX_SIGNALS_0, 
        MASKA_UMAX_SIGNALS_1, 
        MASKA_UMAX_SIGNALS_2,
        MASKA_UMAX_SIGNALS_3, 
        MASKA_UMAX_SIGNALS_4, 
        MASKA_UMAX_SIGNALS_5, 
        MASKA_UMAX_SIGNALS_6, 
        MASKA_UMAX_SIGNALS_7, 
        MASKA_UMAX_SIGNALS_8, 
        MASKA_UMAX_SIGNALS_9
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_umax_signals[i]);

      global_timers[INDEX_TIMER_UMAX1] = -1;
      global_timers[INDEX_TIMER_UMAX2] = -1;
    }
    
    if ((current_settings_prt.configuration & (1 << ACHR_CHAPV_BIT_CONFIGURATION)) != 0)
    {
      /**************************/
      //��� ����
      /**************************/
      achr_chapv_handler(active_functions, number_group_stp);
      /**************************/
    } 
    else 
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_achr_chapv_signals[N_BIG] = 
      {
        MASKA_ACHR_CHAPV_SIGNALS_0, 
        MASKA_ACHR_CHAPV_SIGNALS_1, 
        MASKA_ACHR_CHAPV_SIGNALS_2,
        MASKA_ACHR_CHAPV_SIGNALS_3, 
        MASKA_ACHR_CHAPV_SIGNALS_4, 
        MASKA_ACHR_CHAPV_SIGNALS_5, 
        MASKA_ACHR_CHAPV_SIGNALS_6, 
        MASKA_ACHR_CHAPV_SIGNALS_7, 
        MASKA_ACHR_CHAPV_SIGNALS_8, 
        MASKA_ACHR_CHAPV_SIGNALS_9
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_achr_chapv_signals[i]);

      global_timers[INDEX_TIMER_ACHR_CHAPV_100MS_1] = -1;
      global_timers[INDEX_TIMER_CHAPV1_1MS] = -1;
      global_timers[INDEX_TIMER_CHAPV2_1MS] = -1;
      global_timers[INDEX_TIMER_BLOCK_CHAPV1_5MS] = -1;
      global_timers[INDEX_TIMER_BLOCK_CHAPV2_5MS] = -1;
      global_timers[INDEX_TIMER_ACHR1] = -1;
      global_timers[INDEX_TIMER_CHAPV1] = -1;
      global_timers[INDEX_TIMER_ACHR2] = -1;
      global_timers[INDEX_TIMER_CHAPV2] = -1;

      previous_state_po_achr_chapv_uaf1 = 0;
      previous_state_po_achr_chapv_ubf1 = 0;
      previous_state_po_achr_chapv_ucf1 = 0;
      previous_states_CHAPV1 = 0;
      trigger_CHAPV1 = 0;
      previous_states_CHAPV2= 0;
      trigger_CHAPV2= 0;
    }
    
    /**************************/
    //���
    /**************************/
    if ((current_settings_prt.configuration & (1 << ZDZ_BIT_CONFIGURATION)) != 0)
    {
      zdz_handler(active_functions, number_group_stp);
    }
    else
    {
#if (                                   \
     (MODYFIKACIA_VERSII_PZ == 0) ||    \
     (MODYFIKACIA_VERSII_PZ == 3)       \
    )   
      //�������� �������� ����� ���������� ����������
      _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD28) = (((current_settings_prt.zdz_ovd_porig + 1) & 0xf) << 8) | (0 << 12);
      if (zdz_ovd_diagnostyka)
      {
        if (zdz_ovd_diagnostyka & (1 << 0)) _SET_BIT(clear_diagnostyka, TEST_OVD1);
        if (zdz_ovd_diagnostyka & (1 << 1)) _SET_BIT(clear_diagnostyka, TEST_OVD2);
        if (zdz_ovd_diagnostyka & (1 << 2)) _SET_BIT(clear_diagnostyka, TEST_OVD3);
        
        zdz_ovd_diagnostyka = 0;
      }
      delta_time_test = PERIOD_ZDZ_TEST;
#endif
      
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_zdz_signals[N_BIG] = 
      {
        MASKA_ZDZ_SIGNALS_0, 
        MASKA_ZDZ_SIGNALS_1, 
        MASKA_ZDZ_SIGNALS_2,
        MASKA_ZDZ_SIGNALS_3, 
        MASKA_ZDZ_SIGNALS_4, 
        MASKA_ZDZ_SIGNALS_5, 
        MASKA_ZDZ_SIGNALS_6, 
        MASKA_ZDZ_SIGNALS_7, 
        MASKA_ZDZ_SIGNALS_8, 
        MASKA_ZDZ_SIGNALS_9
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_zdz_signals[i]);

      global_timers[INDEX_TIMER_ZDZ] = -1;
    }
    /**************************/

    /**************************/
    //����
    /**************************/
    if ((current_settings_prt.configuration & (1 << UROV_BIT_CONFIGURATION)) != 0)
    {
      urov_handler(active_functions, number_group_stp);
    }
    else
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_urov_signals[N_BIG] = 
      {
        MASKA_UROV_SIGNALS_0, 
        MASKA_UROV_SIGNALS_1, 
        MASKA_UROV_SIGNALS_2,
        MASKA_UROV_SIGNALS_3, 
        MASKA_UROV_SIGNALS_4, 
        MASKA_UROV_SIGNALS_5, 
        MASKA_UROV_SIGNALS_6, 
        MASKA_UROV_SIGNALS_7, 
        MASKA_UROV_SIGNALS_8, 
        MASKA_UROV_SIGNALS_9
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_urov_signals[i]);

      global_timers[INDEX_TIMER_UROV1] = -1;
      global_timers[INDEX_TIMER_UROV2] = -1;
    }
    /**************************/

    /**************************/
    //���
    /**************************/
    if ((current_settings_prt.configuration & (1 << APV_BIT_CONFIGURATION)) != 0)
    {
      apv_handler(active_functions, number_group_stp);
    }
    else
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_apv_signals[N_BIG] = 
      {
        MASKA_APV_SIGNALS_0, 
        MASKA_APV_SIGNALS_1, 
        MASKA_APV_SIGNALS_2,
        MASKA_APV_SIGNALS_3, 
        MASKA_APV_SIGNALS_4, 
        MASKA_APV_SIGNALS_5, 
        MASKA_APV_SIGNALS_6, 
        MASKA_APV_SIGNALS_7, 
        MASKA_APV_SIGNALS_8, 
        MASKA_APV_SIGNALS_9
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_apv_signals[i]);

      global_timers[INDEX_TIMER_APV_1] = -1;
      global_timers[INDEX_TIMER_APV_2] = -1;
      global_timers[INDEX_TIMER_APV_3] = -1;
      global_timers[INDEX_TIMER_APV_4] = -1;
      global_timers[INDEX_TIMER_APV_BLOCK_VID_APV1] = -1;
      global_timers[INDEX_TIMER_APV_BLOCK_VID_APV2] = -1;
      global_timers[INDEX_TIMER_APV_BLOCK_VID_APV3] = -1;
      global_timers[INDEX_TIMER_APV_BLOCK_VID_APV4] = -1;
      global_timers[INDEX_TIMER_APV_BLOCK_VID_VV] = -1;
      global_timers[INDEX_TIMER_APV_TMP1] = -1;
      global_timers[INDEX_TIMER_ACHR_CHAPV] = -1;
      global_timers[INDEX_TIMER_APV_TMP2] = -1;

      previous_states_APV_0 = 0;
      trigger_APV_0 = 0;
    }
    /**************************/

    if ((current_settings_prt.configuration & (1 << UP_BIT_CONFIGURATION)) != 0) 
    {
      up_handler(active_functions, number_group_stp);
    } 
    else 
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_up_signals[N_BIG] = 
      {
        MASKA_UP_SIGNALS_0, 
        MASKA_UP_SIGNALS_1, 
        MASKA_UP_SIGNALS_2,
        MASKA_UP_SIGNALS_3, 
        MASKA_UP_SIGNALS_4, 
        MASKA_UP_SIGNALS_5, 
        MASKA_UP_SIGNALS_6, 
        MASKA_UP_SIGNALS_7, 
        MASKA_UP_SIGNALS_8, 
        MASKA_UP_SIGNALS_9
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_up_signals[i]);

      for (size_t i = 0; i < NUMBER_UP; i++) global_timers[INDEX_TIMER_UP1 + i] = -1;
    }
    
    /**************************/
    //��������� �����
    /**************************/
    if ((current_settings_prt.configuration & (1 << EL_BIT_CONFIGURATION)) != 0)
    {
      unsigned int active_functions_tmp[NUMBER_ITERATION_EL_MAX][N_BIG];
      unsigned int iteration = 0;
	  unsigned int repeat_state = false;
      unsigned int df_changed_state_with_start_new_timeout = 0;
      do
      {
        for (unsigned int i = 0; i < iteration; i++)
        {
          if (
              (active_functions_tmp[i][0] == active_functions[0]) &&
              (active_functions_tmp[i][1] == active_functions[1]) &&
              (active_functions_tmp[i][2] == active_functions[2]) &&
              (active_functions_tmp[i][3] == active_functions[3]) &&
              (active_functions_tmp[i][4] == active_functions[4]) &&
              (active_functions_tmp[i][5] == active_functions[5]) &&
              (active_functions_tmp[i][6] == active_functions[6]) &&
              (active_functions_tmp[i][7] == active_functions[7]) &&
              (active_functions_tmp[i][8] == active_functions[8]) &&
              (active_functions_tmp[i][9] == active_functions[9])
             )
          {
            repeat_state = true;
            break;
          }
        }
        if (repeat_state != false ) break;
        
        active_functions_tmp[iteration][0] = active_functions[0];
        active_functions_tmp[iteration][1] = active_functions[1];
        active_functions_tmp[iteration][2] = active_functions[2];
        active_functions_tmp[iteration][3] = active_functions[3];
        active_functions_tmp[iteration][4] = active_functions[4];
        active_functions_tmp[iteration][5] = active_functions[5];
        active_functions_tmp[iteration][6] = active_functions[6];
        active_functions_tmp[iteration][7] = active_functions[7];
        active_functions_tmp[iteration][8] = active_functions[8];
        active_functions_tmp[iteration][9] = active_functions[9];

        d_and_handler(active_functions);
        d_or_handler(active_functions);
        d_xor_handler(active_functions);
        d_not_handler(active_functions);
        df_handler(active_functions, &df_changed_state_with_start_new_timeout);
        dt_handler(active_functions);
        
        iteration++;
      }
      while (
             (iteration < current_settings_prt.number_iteration_el)
             &&
             (
              (active_functions_tmp[iteration - 1][0] != active_functions[0]) ||
              (active_functions_tmp[iteration - 1][1] != active_functions[1]) ||
              (active_functions_tmp[iteration - 1][2] != active_functions[2]) ||
              (active_functions_tmp[iteration - 1][3] != active_functions[3]) ||
              (active_functions_tmp[iteration - 1][4] != active_functions[4]) ||
              (active_functions_tmp[iteration - 1][5] != active_functions[5]) ||
              (active_functions_tmp[iteration - 1][6] != active_functions[6]) ||
              (active_functions_tmp[iteration - 1][7] != active_functions[7]) ||
              (active_functions_tmp[iteration - 1][8] != active_functions[8]) ||
              (active_functions_tmp[iteration - 1][9] != active_functions[9])
             ) 
            );
      
      if (
          (repeat_state != false ) ||
          (iteration >= current_settings_prt.number_iteration_el)
         )
      {
        _SET_BIT(active_functions, RANG_ERROR_CONF_EL);
      }
      else
      {
        _CLEAR_BIT(active_functions, RANG_ERROR_CONF_EL);
      }
    }
    else
    {
      //������� �������, �� �� ������ ���� � ���� ������������
      const unsigned int maska_el_signals[N_BIG] = 
      {
        MASKA_EL_SIGNALS_0, 
        MASKA_EL_SIGNALS_1, 
        MASKA_EL_SIGNALS_2,
        MASKA_EL_SIGNALS_3, 
        MASKA_EL_SIGNALS_4, 
        MASKA_EL_SIGNALS_5, 
        MASKA_EL_SIGNALS_6, 
        MASKA_EL_SIGNALS_7, 
        MASKA_EL_SIGNALS_8, 
        MASKA_EL_SIGNALS_9
      };
      for (unsigned int i = 0; i < N_BIG; i++) active_functions[i] &= (unsigned int)(~maska_el_signals[i]);
      
      //������� �� �������, �� ���������� �� ��������� �����
      for(unsigned int i = INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START; i < (INDEX_TIMER_DF_WORK_START + NUMBER_DEFINED_FUNCTIONS); i++)
        global_timers[i] = -1;
    }
    /**************************/

    /**************************/
    //���������-³���������
    /**************************/
    on_off_handler(active_functions);
    /**************************/
    
    /**************************/
    //��� (������ ����� ����� ����� ���������)
    /**************************/
    vmp_handler(active_functions);
    /**************************/

    /**************************/
    //���������� � ��
    /**************************/
    ready_tu(active_functions);
    /**************************/

    /**************************/
    //������ �������� (������ ����� ����� ����� ���������)
    /**************************/
    resurs_vymykacha_handler(active_functions);
    /**************************/
  }
  else
  {
    //������� �������� �����������
    
    //������� �� ������ �������, ��� �������������
    active_functions[0] &= MASKA_INFO_SIGNALES_0;
    active_functions[1] &= MASKA_INFO_SIGNALES_1;
    active_functions[2] &= MASKA_INFO_SIGNALES_2;
    active_functions[3] &= MASKA_INFO_SIGNALES_3;
    active_functions[4] &= MASKA_INFO_SIGNALES_4;
    active_functions[5] &= MASKA_INFO_SIGNALES_5;
    active_functions[6] &= MASKA_INFO_SIGNALES_6;
    active_functions[7] &= MASKA_INFO_SIGNALES_7;
    active_functions[8] &= MASKA_INFO_SIGNALES_8;
    active_functions[9] &= MASKA_INFO_SIGNALES_9;
    
    //������������ �� ����
    state_outputs = 0;
    
    //���������� � ���������� ���� ���� �������� ����
    previous_states_APV_0 = 0;
    trigger_APV_0 = 0;
    previous_state_po_achr_chapv_uaf1 = 0;
    previous_state_po_achr_chapv_ubf1 = 0;
    previous_state_po_achr_chapv_ucf1 = 0;
    previous_states_CHAPV1 = 0;
    trigger_CHAPV1 = 0;
    previous_states_ready_tu = 0;
    trigger_ready_tu = 0;
    
    //������� �� �������, �� ������� � �����
    for(unsigned int i = INDEX_TIMER_DF_PROLONG_SET_FOR_BUTTON_INTERFACE_START; i < MAX_NUMBER_GLOBAL_TIMERS; i++)
      global_timers[i] = -1;
    
//    //���� ��� �� ���������� � ��������
//    state_df = 0;
    
    //���� ��������� �� ���������� � ����������
    for(unsigned int i = 0; i < NUMBER_DEFINED_FUNCTIONS; i++)
    {
      etap_execution_df[i] = NONE_DF;
    }
  }

  /**************************/
  //������� ����������� ����������
  /**************************/
  analog_registrator(active_functions);
  /**************************/

  /**************************/
  //������� ����������� ����������
  /**************************/
  digital_registrator(active_functions);
  /**************************/

  /**************************/
  //������ � ���������, �� ����� ������������ � ��������������� ���'���
  /**************************/
  const unsigned int maska_trg_func_array[N_BIG] = {
                                                    MASKA_TRIGGER_SIGNALES_0,
                                                    MASKA_TRIGGER_SIGNALES_1,
                                                    MASKA_TRIGGER_SIGNALES_2,
                                                    MASKA_TRIGGER_SIGNALES_3,
                                                    MASKA_TRIGGER_SIGNALES_4,
                                                    MASKA_TRIGGER_SIGNALES_5,
                                                    MASKA_TRIGGER_SIGNALES_6,
                                                    MASKA_TRIGGER_SIGNALES_7,
                                                    MASKA_TRIGGER_SIGNALES_8,
                                                    MASKA_TRIGGER_SIGNALES_9
                                                  };
  unsigned int comparison_true = true;
  for (unsigned int i = 0; i < N_BIG; i++)
  {
    unsigned int tmp_data;
    if (trigger_active_functions[i] != (tmp_data = (active_functions[i] & maska_trg_func_array[i])))
    {
      comparison_true = false;
      trigger_active_functions[i] = tmp_data;
    }
  }
  if (comparison_true != true)
  {
    /*
    �������, �������� ���� ���������� � ��������������� ���'1��� ��������.
    ������ ������� �� �� ����� � ��������������� ���'���
    */
    _SET_BIT(control_spi1_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT);
  }
  /**************************/

  /**************************/
  //����������� ��������� � ������ �������� � ��������� �������
  /**************************/
  for (unsigned int i = 0; i < N_BIG; i++)
  {
    unsigned int temp_data = active_functions[i];
    trigger_functions_USB[i]   |= temp_data;
    trigger_functions_RS485[i] |= temp_data;
  }

  copying_active_functions = 0; //�������, �� ���������� �������� �������� ������� ���������
  
  /*
  ������ ���� �������� �������� ������� ��� ����, ��� ���� �� ������� ������
  �����������, �� ����� ���� � ����� �������  (����� � ��'������� ����������
  ���������) ����� ��������, ��� ��������� ��������
  */
  for (unsigned int i = 0; i < N_BIG; i++) 
  {
    unsigned int temp_data = active_functions[i];
    active_functions_copy[i] = temp_data;
    previous_active_functions[i] = temp_data;
  }
  /**************************/

  /**************************/
  //���� ���������� �� ������
  /**************************/
  //�������� ����������, �� �� �������������� ������� "����� ����" - � ���� ���, �� ���������� ������� �� ����
  if (_CHECK_SET_BIT(active_functions, RANG_RESET_RELES) !=0)
  {
    state_outputs = 0;
  }
  
  if (_CHECK_SET_BIT(active_functions, RANG_AVAR_DEFECT) == 0)
  {
    //�� ����������� ������� ��������, ���� ������������� ���� �����
    
    //���������, �� ���� ����� ����� ���� ����������
    for (unsigned int i = 0; i < NUMBER_OUTPUTS; i++)
    {
      //� ���������� ����� ������� ��ò��� � ���������� ������, ���� ����������� ��������� "i" � �������, �� ����� � ���������
      unsigned int temp_array_of_outputs[N_BIG];
    
      for (unsigned int j = 0; j < N_BIG; j++) temp_array_of_outputs[j] = current_settings_prt.ranguvannja_outputs[N_BIG*i + j] & active_functions[j];

      //������ "������� �����������" ������ � ���������� �����: ������ ���� �� ����� ���������� � �������, ���� ����� ������ �� ��������
      if(_CHECK_SET_BIT((current_settings_prt.ranguvannja_outputs + N_BIG*i), RANG_AVAR_DEFECT) !=0)
      {
        //������ "A�������� �������������"  ������ ���������� �� ����� �����
        if (_CHECK_SET_BIT(temp_array_of_outputs, RANG_AVAR_DEFECT) == 0)
        {
          //������ "A�������� �������������" �� � ��������
          //���������� ������������ ���� � �������� ���� � �����, ���� �  ��ò���� � ��������� ������, ���� ����������� ��������� "i" � �������, �� ����� � ���������
          _SET_BIT(temp_array_of_outputs, RANG_AVAR_DEFECT);
        }
        else
        {
          //������ "A�������� �������������" � ��������
          //���������� ���������� ���� � �������� ���� � �����, ���� �  ��ò���� � ��������� ������, ���� ����������� ��������� "i" � �������, �� ����� � ���������
          _CLEAR_BIT(temp_array_of_outputs, RANG_AVAR_DEFECT);
        }
      }
      
      //������ "�������� �����������" ������ � ���������� �����: ������ ���� �� ����� ���������� � �������, ���� ����� ������ �� ��������
      if(_CHECK_SET_BIT((current_settings_prt.ranguvannja_outputs + N_BIG*i), RANG_DEFECT) !=0)
      {
        //������ "�������� �����������"  ������ ���������� �� ����� �����
        if (_CHECK_SET_BIT(temp_array_of_outputs, RANG_DEFECT) ==0)
        {
          //������ "�������� �����������" �� � ��������
          //���������� ������������ ���� � �������� ���� � �����, ���� �  ��ò���� � ��������� ������, ���� ����������� ��������� "i" � �������, �� ����� � ���������
          _SET_BIT(temp_array_of_outputs, RANG_DEFECT);
        }
        else
        {
          //������ "�������� �����������" � ��������
          //���������� ���������� ���� � �������� ���� � �����, ���� �  ��ò���� � ��������� ������, ���� ����������� ��������� "i" � �������, �� ����� � ���������
          _CLEAR_BIT(temp_array_of_outputs, RANG_DEFECT);
        }
      }

      //����������, �� � ��������� �� ����������� ��������� �� ����� ����� � ���������, �� ����� � ��������� - ����� ��������� ������
      if (
          (temp_array_of_outputs[0] != 0) ||
          (temp_array_of_outputs[1] != 0) ||
          (temp_array_of_outputs[2] != 0) ||
          (temp_array_of_outputs[3] != 0) ||
          (temp_array_of_outputs[4] != 0) ||
          (temp_array_of_outputs[5] != 0) ||
          (temp_array_of_outputs[6] != 0) ||
          (temp_array_of_outputs[7] != 0) ||
          (temp_array_of_outputs[8] != 0) ||
          (temp_array_of_outputs[9] != 0)
         )
      {
        //��� ����������� ���� �������� ���� ���������, � ��� ���������� ���������� �� ���� ������ ���������� ���� ��� ���� �� �� ����� �������� ���� ���������, ������� �� ����������
        if ((current_settings_prt.type_of_output & (1 << i)) != 0)
        {
          //����� ����������, ���� � ���� ����� ��� �������� ����
          //³������, �� ����� ����� - ���������
          state_outputs |= (1 << i);
        }
        else
        {
          //����� ���������, ���� ���������� �� �� ��� ������ ���������� ����, �� ��� �������� ��, ������� ���� �� � ������� ������ ���������� (����������)
          if (_CHECK_SET_BIT((current_settings_prt.ranguvannja_outputs + N_BIG*i), RANG_WORK_BV) ==0)
          {
            //�� ���� ���� �� ���������� ������ �� (���� ���������)
          
            //³������, �� ����� ����� - ���������
            state_outputs |= (1 << i);
          }
          else
          {
            //�� ���� ���� ���������� ������ �� (���� ���������)
          
            //³������, �� ����� ����� - ��������� ����� ���, ���� ������� �� ������� �����
            if (_CHECK_SET_BIT(active_functions, RANG_WORK_BV) !=0)
              state_outputs |= (1 << i);
            else
              state_outputs &= ~(1 << i);
          }
        }
      }
      else
      {
        //����������, �� ����� ���������, �� ����������
        if ((current_settings_prt.type_of_output & (1 << i)) == 0)
        {
          //����� ���������
        
          //³������, �� ����� ����� - ��ǲ�������
          state_outputs &= ~(1 << i);
        }
      }
    }
  }
  else
  {
    //����������� ������e ��������, ���� ���������� �� ����!!!

    //������������ �� ����
    state_outputs = 0;
  }
  
  //���������� �� ����� ���������� ���� ���������� ������ � EEPROM
  if((state_outputs  & current_settings_prt.type_of_output) != state_signal_outputs)
  {
    state_signal_outputs = state_outputs  & current_settings_prt.type_of_output;
    //����������� ����������� ��� ��, �� � EEPROM ����� �������� ��� �������� ���������� ������ � ��������� ��������������
    _SET_BIT(control_spi1_taskes, TASK_START_WRITE_STATE_LEDS_OUTPUTS_EEPROM_BIT);
  }
  
  //���� ������ � ����������� ����������� ������ ������ ���������� ������
  unsigned int output_signal_modif = (current_settings_prt.type_of_output_modif & current_settings_prt.type_of_output);
  state_outputs_raw = ( state_outputs & ((unsigned int)(~output_signal_modif)) ) | ((state_outputs & output_signal_modif)*output_timer_prt_signal_output_mode_2);
  
  _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD31_DD34_DD35_DD37) = state_outputs_raw;
  TIM_PRT_write_tick = TIM2->CNT;
  /**************************/

  /**************************/
  //���� ���������� �� ���������
  /**************************/
  //�������� ����������, �� �� �������������� ������� "����� ���������" - � ���� ���, �� ���������� ������� ��� ���������
  if (_CHECK_SET_BIT(active_functions, RANG_RESET_LEDS) !=0)
  {
    state_leds = 0;
  }
  
  //���������, �� �������������� ����� ����� ���� ���������
  for (unsigned int i = 0; i < NUMBER_LEDS; i++)
  {
    //� ���������� ����� ������� ���������� ��������������, ���� ����������� ��������� "i"
    unsigned int temp_array_of_leds[N_BIG];
    
    //����������, �� � ��������� �� ����������� ��������� �� ����� ������������� � ���������, �� ����� � ��������� - ����� ��������� ������
    for (unsigned int j = 0; j < N_BIG; j++ ) temp_array_of_leds[j] = current_settings_prt.ranguvannja_leds[N_BIG*i + j] & active_functions[j];

    if (
        (temp_array_of_leds[0] != 0) ||
        (temp_array_of_leds[1] != 0) ||
        (temp_array_of_leds[2] != 0) ||
        (temp_array_of_leds[3] != 0) ||
        (temp_array_of_leds[4] != 0) ||
        (temp_array_of_leds[5] != 0) ||
        (temp_array_of_leds[6] != 0) ||
        (temp_array_of_leds[7] != 0) ||
        (temp_array_of_leds[8] != 0) ||
        (temp_array_of_leds[9] != 0)
       )
    {
      //³������, �� ����� ������������� - ������
      state_leds |= (1 << i);
    }
    else
    {
      //����������, �� ����� ������������� ����������, �� ���������
      if ((current_settings_prt.type_of_led & (1 << i)) == 0)
      {
        //������������� ����������

        //³������, �� ����� ������������� - ���������
        state_leds &= ~(1 << i);
      }
    }
  }
  //���������� �� ����� ���������� ���� ��������� �������������� � EEPROM
  if((state_leds  & current_settings_prt.type_of_led) != state_trigger_leds)
  {
    state_trigger_leds = state_leds  & current_settings_prt.type_of_led;
    //����������� ����������� ��� ��, �� � EEPROM ����� �������� ��� �������� ���������� ������ � ��������� ��������������
    _SET_BIT(control_spi1_taskes, TASK_START_WRITE_STATE_LEDS_OUTPUTS_EEPROM_BIT);
  }
  
  //������ ��������������
  /*Run_Error*/
  if (_CHECK_SET_BIT(active_functions, RANG_AVAR_DEFECT) == 0) state_leds_ctrl |=  (1 << LED_COLOR_GREEN_BIT) << ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_R_E);
  else state_leds_ctrl &=  (uint32_t)(~((1 << LED_COLOR_GREEN_BIT) << ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_R_E)));
  if (
      (_CHECK_SET_BIT(active_functions, RANG_DEFECT     ) != 0) ||
      (_CHECK_SET_BIT(active_functions, RANG_AVAR_DEFECT) != 0)
     ) state_leds_ctrl |=  (1 << LED_COLOR_RED_BIT) << ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_R_E);
  else state_leds_ctrl &=  (uint32_t)(~((1 << LED_COLOR_RED_BIT) << ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_R_E)));
  
  static uint32_t current_LED_N_COL;
  
  //������� ��������� ����������
  _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD32_DD38) = ((1 << current_LED_N_COL) << LED_N_ROW) | ((uint32_t)(~0) & ((1 << LED_N_ROW) - 1));
  //���������� �� ��������� ��������
  if (++current_LED_N_COL >= LED_N_COL) current_LED_N_COL = 0;
  
  uint32_t state_leds_tmp;
  
  switch (current_LED_N_COL)
  {
  case 0:
    {
      state_leds_tmp = (((state_leds >>  0) & 0x1) << 0) |
                       (((state_leds >>  2) & 0x1) << 1) |
                       (((state_leds >>  4) & 0x1) << 2) |
                       (((state_leds >>  6) & 0x1) << 3) |
                       (((state_leds >>  8) & 0x1) << 4) |
                       (((state_leds >> 10) & 0x1) << 5) |
                       (((state_leds >> 12) & 0x1) << 6) |
                       (((state_leds >> 14) & 0x1) << 7);

//      state_leds_tmp = (((state_leds >> (2*0)) & ((1 << 2) - 1)) << 0) |
//                       (((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_R_E)) & ((1 << NUMBER_LED_COLOR) - 1)) << 2) |
//                       (((state_leds_Fx[0] >> (NUMBER_LED_COLOR*(6 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 4);
      break;
    }
  case 1:
    {
      uint32_t temp_state = state_leds;
      state_leds_tmp = (((temp_state >>  1) & 0x1) << 0) |
                       (((temp_state >>  3) & 0x1) << 1) |
                       (((temp_state >>  5) & 0x1) << 2) |
                       (((temp_state >>  7) & 0x1) << 3) |
                       (((temp_state >>  9) & 0x1) << 4) |
                       (((temp_state >> 11) & 0x1) << 5) |
                       (((temp_state >> 13) & 0x1) << 6) |
                       ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_O)) & (1 << LED_COLOR_RED_BIT)) != 0) << 7);

//      state_leds_tmp = (((state_leds >> (2*1)) & ((1 << 2) - 1)) << 0) |
//                       (((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_START)) & ((1 << NUMBER_LED_COLOR) - 1)) << 2) |
//                       (((state_leds_Fx[1] >> (NUMBER_LED_COLOR*(1 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 4);
      break;
    }
  case 2:
    {
      state_leds_tmp = ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_R_E  )) & (1 << LED_COLOR_RED_BIT)) != 0) << 0) |
                      /*
                       ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_START)) & (1 << LED_COLOR_RED_BIT)) != 0) << 1) |
                       ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_TRIP )) & (1 << LED_COLOR_RED_BIT)) != 0) << 2) |
                      */
                       (((state_leds >> 15) & 0x1) << 1) |
                       (((state_leds >> 16) & 0x1) << 2) |
      
                       ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(1 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 3) | 
                       ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(2 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 4) | 
                       ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(3 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 5) | 
                       ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(4 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 6) | 
                       ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(5 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 7);
      
//      state_leds_tmp = (((state_leds >> (2*2)) & ((1 << 2) - 1)) << 0) |
//                       (((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_TRIP)) & ((1 << NUMBER_LED_COLOR) - 1)) << 2) |
//                       (((state_leds_Fx[1] >> (NUMBER_LED_COLOR*(2 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 4);
      break;
    }
  case 3:
    {
      state_leds_tmp = ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_R_E  )) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 0) |
                      /*
                       ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_START)) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 1) |
                       ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_TRIP )) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 2) |
                      */
                       ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(1 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 3) | 
                       ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(2 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 4) | 
                       ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(3 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 5) | 
                       ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(4 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 6) | 
                       ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(5 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 7);
      
//      state_leds_tmp = (((state_leds >> (2*3)) & ((1 << 2) - 1)) << 0) |
//                       (((state_leds_Fx[0] >> (NUMBER_LED_COLOR*(1 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 2) |
//                       (((state_leds_Fx[1] >> (NUMBER_LED_COLOR*(3 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 4);
      break;
    }
  case 4:
    {
      state_leds_tmp = ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(6 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 0) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(1 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 1) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(2 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 2) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(3 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 3) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(4 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 4) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(5 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 5) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(6 - 1))) & (1 << LED_COLOR_RED_BIT)) != 0) << 6) |
                       ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_I)) & (1 << LED_COLOR_RED_BIT)) != 0) << 7);

//      state_leds_tmp = (((state_leds >> (2*4)) & ((1 << 2) - 1)) << 0) |
//                       (((state_leds_Fx[0] >> (NUMBER_LED_COLOR*(2 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 2) |
//                       (((state_leds_Fx[1] >> (NUMBER_LED_COLOR*(4 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 4);
      break;
    }
  case 5:
    {
      state_leds_tmp = ((((state_leds_Fx[0] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(6 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 0) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(1 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 1) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(2 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 2) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(3 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 3) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(4 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 4) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(5 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 5) |
                       ((((state_leds_Fx[1] >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)(6 - 1))) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 6) |
                       ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_I)) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 7);

//      state_leds_tmp = (((state_leds >> (2*5)) & ((1 << 2) - 1)) << 0) |
//                       (((state_leds_Fx[0] >> (NUMBER_LED_COLOR*(3 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 2) |
//                       (((state_leds_Fx[1] >> (NUMBER_LED_COLOR*(5 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 4);
      break;
    }
  case 6:
    {
      state_leds_tmp = ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_O)) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 7);

//      state_leds_tmp = (((state_leds >> (2*6)) & ((1 << 2) - 1)) << 0) |
//                       (((state_leds_Fx[0] >> (NUMBER_LED_COLOR*(4 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 2) |
//                       (((state_leds_Fx[1] >> (NUMBER_LED_COLOR*(6 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 4);
      break;
    }
//  case 7:
//    {
//      state_leds_tmp = (((state_leds >> (2*7)) & ((1 << 1) - 1)) << 0) |
//                       ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_O)) & (1 << LED_COLOR_RED_BIT)) != 0) << 1) |
//                       (((state_leds_Fx[0] >> (NUMBER_LED_COLOR*(5 - 1))) & ((1 << NUMBER_LED_COLOR) - 1)) << 2) |
//                       (((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_I)) & ((1 << NUMBER_LED_COLOR) - 1)) << 4) |
//                       ((((state_leds_ctrl >> ((uint32_t)NUMBER_LED_COLOR*(uint32_t)LED_CTRL_O)) & (1 << LED_COLOR_GREEN_BIT)) != 0) << 6);
//      break;
//    }
  default:
    {
      //���������� ����� ����� �� ���� � ����
      total_error_sw_fixed(22);
    }
  }

  //�������� ���������� �� ��������������� �� ���������
  _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD32_DD38) = ((1 << current_LED_N_COL) << LED_N_ROW) | ((uint32_t)(~state_leds_tmp) & ((1 << LED_N_ROW) - 1));
  /**************************/

  /**************************/
  //
  /**************************/
  /**************************/
}
/*****************************************************/

/*****************************************************/
//����������� �� ������� TIM2, ���� ��������� ������� �������
/*****************************************************/
void TIM2_IRQHandler(void)
{
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordEnterISR();
#endif
  
  if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
  {
    /***********************************************************************************************/
    //����������� �������� �� ������ 1, ���� ������ ����������� ���� 1 ��, ��� ��������������� ������� � ������ �������
    /***********************************************************************************************/
    TIM2->SR = (uint16_t)((~(uint32_t)TIM_IT_CC1) & 0xffff);
    uint32_t current_tick = TIM2->CCR1;
    
    /***********************************************************/
    //����������, �� ���������� ���� ���������
    /***********************************************************/
    if (changed_settings == CHANGED_ETAP_ENDED) /*�� � �����, �� ��� ��� ���������� ��� �������� �� � ������ �������� ������� (� ��� ����� ����� ��� �� ���������)*/
    {
      //������� ������� ��������� � ���� ���� ������� ��� � ���� ������ (���� � �����) ����� ������� �������
      current_settings_prt = current_settings;
      
      //�������, �� ���� ������� �������� �������
      changed_settings = CHANGED_ETAP_NONE;
    }

    if (koef_resurs_changed == CHANGED_ETAP_ENDED)
    {
      //����������� ��� ��������� ������� ��������
      K_resurs_prt = K_resurs;

      //�������, �� ���� ������� �������� �������
      koef_resurs_changed = CHANGED_ETAP_NONE;
    }
    /***********************************************************/

    /***********************************************************/
    //���������� ����������� ������� ����������� ����������
    /***********************************************************/
    if (
        ((clean_rejestrators & CLEAN_DR) != 0)
        &&  
        (
         (control_tasks_dataflash & (
                                     TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR | 
                                     TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB                    |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485                  |
                                     TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU
                                    )
         ) == 0
        )
       )   
    {
      //���������� ������� �������� ����������� ���������

      //����������� ������� ������ ���� ��������� � EEPROM
      _SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT);

      //������� ��������� ���������� �� ����������� ���������
      info_rejestrator_dr.next_address = MIN_ADDRESS_DR_AREA;
      info_rejestrator_dr.saving_execution = 0;
      info_rejestrator_dr.number_records = 0;

      //�������, �� ����� ������ �� ��������
      number_record_of_dr_for_menu  = 0xffff;
      number_record_of_dr_for_USB   = 0xffff;
      number_record_of_dr_for_RS485 = 0xffff;

      //������ ������� ������� ����������� ����������
      clean_rejestrators &= (unsigned int)(~CLEAN_DR);
    }
    /***********************************************************/

    /***********************************************************/
    //���������� ������� �������� � ���������� ����� ����� ���� ��������� ������ ��������
    /***********************************************************/
    clocking_global_timers();
    /***********************************************************/
    
    /***********************************************************/
    //���������� ������� �������
    /***********************************************************/
    //ĳ��������� �����, ��� ����� ��������� ����� ��� ����� �������� ��������������� ����� ��������
    uint32_t TIM_PRT_read_tick = TIM2->CNT;

    uint64_t TIM_PRT_delta_write_read;
    if (TIM_PRT_read_tick < TIM_PRT_write_tick)
      TIM_PRT_delta_write_read = TIM_PRT_read_tick + 0x100000000 - TIM_PRT_write_tick;
    else TIM_PRT_delta_write_read = TIM_PRT_read_tick - TIM_PRT_write_tick;
    if (TIM_PRT_delta_write_read > (TIM2_MIN_PERIOD_WRITE_READ + 1))
    {
      unsigned int control_state_outputs = ((~((unsigned int)(_DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD31_DD34_DD35_DD37)))) & 0xffff);

      static uint32_t error_rele[NUMBER_OUTPUTS];
      if (control_state_outputs != state_outputs_raw) 
      {
        for (unsigned int index = 0; index < NUMBER_OUTPUTS; index++)
        {
          uint32_t maska = 1 << index;
        
          if ((control_state_outputs & maska) != (state_outputs_raw & maska))
          {
            if (error_rele[index] < 3) error_rele[index]++;
            if (error_rele[index] >= 3 ) _SET_BIT(set_diagnostyka, (ERROR_DIGITAL_OUTPUT_1_BIT + index));
          }
          else error_rele[index] = 0;
        }
      }
      else
      {
        for (unsigned int index = 0; index < NUMBER_OUTPUTS; index++) error_rele[index] = 0;
      }
    }
    
    //ĳ��������� ���������-��������� ����
    {
      uint32_t board_register_tmp = _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47);
      uint32_t board_register_diff = board_register_tmp ^ board_register;
      board_register = board_register_tmp;

      if ((board_register_tmp & 0x01) !=  0x1) _SET_BIT(set_diagnostyka, ERROR_BA_1_FIX);
      else if (board_register_diff & 0x01)
      {
        _SET_BIT(clear_diagnostyka, ERROR_BA_1_FIX);
        _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x1;
        if ((_DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) >> 8) != 0x11)  _SET_BIT(set_diagnostyka, ERROR_BA_1_CTLR);
        _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x0;
      }
      
      if ((board_register_tmp & 0x02) !=  0x2) _SET_BIT(set_diagnostyka, ERROR_BDVV5_1_FIX);
      else if (board_register_diff & 0x02)
      {
        _SET_BIT(clear_diagnostyka, ERROR_BDVV5_1_FIX);
        _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x2;
        if ((_DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD33_DD36) & 0xff) != 0x25)  _SET_BIT(set_diagnostyka, ERROR_BDVV5_1_CTLR);
        _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x0;
      }

#if (                                   \
     (MODYFIKACIA_VERSII_PZ == 0) ||    \
     (MODYFIKACIA_VERSII_PZ == 1) ||    \
     (MODYFIKACIA_VERSII_PZ == 3)       \
    )
      if ((board_register_tmp & 0x04) !=  0x4) _SET_BIT(set_diagnostyka, ERROR_BDVV5_2_FIX);
      else if (board_register_diff & 0x04)
      {
        _SET_BIT(clear_diagnostyka, ERROR_BDVV5_2_FIX);
        _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x4;
        if ((_DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD33_DD36) >> 8) != 0x37)  _SET_BIT(set_diagnostyka, ERROR_BDVV5_2_CTLR);
        _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x0;
      }
#endif

#if (                                   \
     (MODYFIKACIA_VERSII_PZ == 0) ||    \
     (MODYFIKACIA_VERSII_PZ == 3)       \
    )
    if ((board_register_tmp & 0x010) != 0x10) 
#if (MODYFIKACIA_VERSII_PZ == 0)
      _SET_BIT(set_diagnostyka, ERROR_BDV_DZ_FIX);
#else
      _SET_BIT(set_diagnostyka, ERROR_BDZ_FIX);
#endif
      else if (board_register_diff & 0x10)
      {
#if (MODYFIKACIA_VERSII_PZ == 0)
        _SET_BIT(clear_diagnostyka, ERROR_BDV_DZ_FIX);
#else
        _SET_BIT(clear_diagnostyka, ERROR_BDZ_FIX);
#endif

      _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x10;

#if (MODYFIKACIA_VERSII_PZ == 0)
        if ((_DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD26_DD29) >> 8) != 0x14)  _SET_BIT(set_diagnostyka, ERROR_BDV_DZ_CTLR);
#else
        if ((_DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD26_DD29) >> 8) != 0x18)  _SET_BIT(set_diagnostyka, ERROR_BDZ_CTLR);
#endif

        _DEVICE_REGISTER_V2(Bank1_SRAM2_ADDR, OFFSET_DD39_DD40_DD47) = 0x0;
      }
#endif
    }
    
    //���������� ����������� ������� ��� ����������� ����������
//    //���������� ����������� ������� ��� ����������� ����������
//    if ((number_word_digital_part_ar*8*sizeof(short int)) < NUMBER_TOTAL_SIGNAL_FOR_RANG)
//    {
//      //���������� �� ������� ����� �� ����� ������������
//      /*���� ������� ���� �������� �� ����� ��������� ���������, ��� ���� ���� �� ���������� - 
//      �� �������� ����������� ���������� ������� � �������������� ���������� ����������� ����������.
//      �� �������� ���� ���� �������, ���� � ��, ���������� ������ ����������� ������������ �� ��������!*/
//      total_error_sw_fixed(5);
//    }

    //������� �������
    main_protection();
    /***********************************************************/

    /***********************************************************/
    //�������� �� ����������� ������� ������� ��ﳿ ����� ��� ������������
    /***********************************************************/
    //������� ����������
    if (periodical_tasks_TEST_TRG_FUNC != 0)
    {
      //����� � ���� ������� ������ ������� ������� ��ﳿ �����
      if ((state_spi1_task & STATE_TRG_FUNC_EEPROM_GOOD) != 0)
      {
        //������ ���� ����� ���, ���� ������� ���������� ������ ������� � ���������� ���������� ����
        if (
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_WRITE_TRG_FUNC_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_TRG_FUNC_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_TRG_FUNC_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_TRG_FUNC_EEPROM_BIT    ) == 0)
           ) 
        {
          //�� ����� ������� �� ��� �������-����� ������� ����������, ���� ����� �������� ���������
          fix_active_buttons_ctrl = fix_active_buttons;
          for (unsigned int i = 0; i < N_BIG; i++) trigger_active_functions_ctrl[i] = trigger_active_functions[i];
          crc_trg_func_ctrl = crc_trg_func;

          //������� ������� ������ ���������� �������� ��ﳿ 
          periodical_tasks_TEST_TRG_FUNC = false;
          //����������� ������� ������ �������� ����������� �� �������� ��ﳿ 
          periodical_tasks_TEST_TRG_FUNC_LOCK = true;
        }
      }
      else
      {
        //������� ������� ������ ���������� �������� ��ﳿ 
        periodical_tasks_TEST_TRG_FUNC = false;
      }
    }

    //���������� ���������
    if (periodical_tasks_TEST_INFO_REJESTRATOR_AR != 0)
    {
      //����� � ���� ������� ������ ������� ������� ��ﳿ �����
      if ((state_spi1_task & STATE_INFO_REJESTRATOR_AR_EEPROM_GOOD) != 0)
      {
        //������ ���� ����� ���, ���� ��������� ���������� ���������� ������ ������� � ���������� ���������� ����
        if (
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_AR_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_AR_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_AR_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_AR_EEPROM_BIT    ) == 0)
           ) 
        {
          //�� ����� ������� �� ��� �������-����� ��������� ���������� ����������, ���� ����� �������� ���������
          info_rejestrator_ar_ctrl = info_rejestrator_ar;
          crc_info_rejestrator_ar_ctrl = crc_info_rejestrator_ar;

          //������� ������� ������ ���������� �������� ��ﳿ 
          periodical_tasks_TEST_INFO_REJESTRATOR_AR = false;
          //����������� ������� ������ �������� ����������� �� �������� ��ﳿ 
          periodical_tasks_TEST_INFO_REJESTRATOR_AR_LOCK = true;
        }
      }
      else
      {
        //������� ������� ������ ���������� �������� ��ﳿ 
        periodical_tasks_TEST_INFO_REJESTRATOR_AR = false;
      }
    }

    //���������� ���������
    if (periodical_tasks_TEST_INFO_REJESTRATOR_DR != 0)
    {
      //����� � ���� ������� ������ ������� ������� ��ﳿ �����
      if ((state_spi1_task & STATE_INFO_REJESTRATOR_DR_EEPROM_GOOD) != 0)
      {
        //������ ���� ����� ���, ���� ��������� ���������� ���������� ������ ������� � ���������� ���������� ����
        if (
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_INFO_REJESTRATOR_DR_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_INFO_REJESTRATOR_DR_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_INFO_REJESTRATOR_DR_EEPROM_BIT    ) == 0)
           ) 
        {
          //�� ����� ������� �� ��� �������-����� ��������� ���������� ����������, ���� ����� �������� ���������
          info_rejestrator_dr_ctrl = info_rejestrator_dr;
          crc_info_rejestrator_dr_ctrl = crc_info_rejestrator_dr;

          //������� ������� ������ ���������� �������� ��ﳿ 
          periodical_tasks_TEST_INFO_REJESTRATOR_DR = false;
          //����������� ������� ������ �������� ����������� �� �������� ��ﳿ 
          periodical_tasks_TEST_INFO_REJESTRATOR_DR_LOCK = true;
        }
      }
      else
      {
        //������� ������� ������ ���������� �������� ��ﳿ 
        periodical_tasks_TEST_INFO_REJESTRATOR_DR = false;
      }
    }
    /***********************************************************/

    //˳������� �������
    if (periodical_tasks_TEST_RESURS != 0)
    {
      //����� � ���� ������� ������ ������� ������� ��ﳿ �����
      if ((state_spi1_task & STATE_RESURS_EEPROM_GOOD) != 0)
      {
        //������ ���� ����� ���, ���� ���������z ������ ������� � ���������� ���������� ����
        if (
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_WRITE_RESURS_EEPROM_BIT) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_WRITING_RESURS_EEPROM_BIT    ) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_START_READ_RESURS_EEPROM_BIT ) == 0) &&
            (_CHECK_SET_BIT(control_spi1_taskes, TASK_READING_RESURS_EEPROM_BIT    ) == 0)
           ) 
        {
          //�� ����� ������� �� ��� �������-����� ������� ��������, ���� ����� �������� ���������
          resurs_vymykacha_ctrl = resurs_vymykacha;          
          resurs_vidkljuchennja_ctrl = resurs_vidkljuchennja;
          crc_resurs_ctrl = crc_resurs;

          //������� ������� ������ ���������� �������� ��ﳿ 
          periodical_tasks_TEST_RESURS = false;
          //����������� ������� ������ �������� ����������� �� �������� ��ﳿ 
          periodical_tasks_TEST_RESURS_LOCK = true;
        }
      }
      else
      {
        //������� ������� ������ ���������� �������� ��ﳿ 
        periodical_tasks_TEST_RESURS = false;
      }
    }

    /***********************************************************/
    //������������ "�������� ��������� ��� ���������� �����������"
    /***********************************************************/
    uint32_t capture_new;
    unsigned int delta;
    TIM2->CCR1 = (capture_new = (current_tick + (delta = TIM2_CCR1_VAL)));
    
    unsigned int repeat;
    unsigned int previous_tick;
    do
    {
      repeat = 0;
      current_tick = TIM2->CNT;

      uint64_t delta_time = 0;
      if (capture_new < current_tick)
        delta_time = capture_new + 0x100000000 - current_tick;
      else delta_time = capture_new - current_tick;

      if ((delta_time > delta) || (delta_time == 0))
      {
        if (TIM_GetITStatus(TIM2, TIM_IT_CC1) == RESET)
        {
          if (delta < TIM2_CCR1_VAL)
          {
            uint64_t delta_tick;
            if (current_tick < previous_tick)
              delta_tick = current_tick + 0x100000000 - previous_tick;
            else delta_tick = current_tick - previous_tick;
              
            delta = delta_tick + 1;
          }
          else if (delta == TIM2_CCR1_VAL)
            delta = 1; /*����������, ��� ���� ���������� ����������� �� ����� ������*/
          else
          {
            //���������� ����� ����� �� ���� � ����
            total_error_sw_fixed(83);
          }
          TIM2->CCR1 = (capture_new = (TIM2->CNT +  delta));
          previous_tick = current_tick;
          repeat = 0xff;
        }
      }
    }
    while (repeat != 0);
    /***********************************************************/
    
    /***********************************************************/
    //����������� ����������� ��� ��, ������� ������ �������
    /***********************************************************/
    control_word_of_watchdog |= WATCHDOG_PROTECTION;
    /***********************************************************/
    /***********************************************************************************************/
  }
  else
  {
    total_error_sw_fixed(23);
  }
  
#ifdef SYSTEM_VIEWER_ENABLE
  SEGGER_SYSVIEW_RecordExitISR();
#endif
}
/*****************************************************/

/*****************************************************/
//���� ����� �������
/*****************************************************/
void setpoints_selecting(unsigned int *p_active_functions, unsigned int act_inp_gr_ustavok) {
  unsigned int grupa_ustavok = 0;
  act_inp_gr_ustavok &= 0xf;
  if (current_settings_prt.grupa_ustavok < SETPOINT_GRUPA_USTAVOK_MIN ||
      current_settings_prt.grupa_ustavok > SETPOINT_GRUPA_USTAVOK_MAX) {
    //�������������� ������
    while (1);
  } else {
    grupa_ustavok = 1 << (current_settings_prt.grupa_ustavok - 1);
  }
  
  if (_CHECK_SET_BIT(p_active_functions, RANG_INVERS_DV_GRUPA_USTAVOK)) _SET_STATE(act_inp_gr_ustavok, 4);
  
  _AND2(grupa_ustavok, 0, act_inp_gr_ustavok, 4, grupa_ustavok, 4);
  _AND2(grupa_ustavok, 1, act_inp_gr_ustavok, 4, grupa_ustavok, 5);
  _AND2(grupa_ustavok, 2, act_inp_gr_ustavok, 4, grupa_ustavok, 6);
  _AND2(grupa_ustavok, 3, act_inp_gr_ustavok, 4, grupa_ustavok, 7);
  
  unsigned int tmp = gr_ustavok_tmp;
  do {
    _AND4(act_inp_gr_ustavok, 0, gr_ustavok_tmp, 1, gr_ustavok_tmp, 2, gr_ustavok_tmp, 3, act_inp_gr_ustavok, 5);
    _INVERTOR(act_inp_gr_ustavok, 5, tmp, 0);
    
    _AND4(tmp, 0, act_inp_gr_ustavok, 1, tmp, 2, tmp, 3, act_inp_gr_ustavok, 6);
    _INVERTOR(act_inp_gr_ustavok, 6, tmp, 1);
    
    _AND4(tmp, 0, tmp, 1, act_inp_gr_ustavok, 2, tmp, 3, act_inp_gr_ustavok, 7);
    _INVERTOR(act_inp_gr_ustavok, 7, tmp, 2);
    
    _AND4(tmp, 0, tmp, 1, tmp, 2, act_inp_gr_ustavok, 3, act_inp_gr_ustavok, 8);
    _INVERTOR(act_inp_gr_ustavok, 8, tmp, 3);
    if (tmp == gr_ustavok_tmp) {
      break;
    }
    gr_ustavok_tmp = tmp;
  } while (1);
  
  _OR2(grupa_ustavok, 4, act_inp_gr_ustavok, 5, grupa_ustavok, 8);
  _OR2(grupa_ustavok, 5, act_inp_gr_ustavok, 6, grupa_ustavok, 9);
  _OR2(grupa_ustavok, 6, act_inp_gr_ustavok, 7, grupa_ustavok, 10);
  _OR2(grupa_ustavok, 7, act_inp_gr_ustavok, 8, grupa_ustavok, 11);
  
  if (_GET_OUTPUT_STATE(grupa_ustavok, 8)) 
    _SET_BIT(p_active_functions, RANG_1_GRUPA_USTAVOK);
  else
    _CLEAR_BIT(p_active_functions, RANG_1_GRUPA_USTAVOK);

  if (_GET_OUTPUT_STATE(grupa_ustavok, 9))
    _SET_BIT(p_active_functions, RANG_2_GRUPA_USTAVOK);
  else
    _CLEAR_BIT(p_active_functions, RANG_2_GRUPA_USTAVOK);

  if (_GET_OUTPUT_STATE(grupa_ustavok, 10))
      _SET_BIT(p_active_functions, RANG_3_GRUPA_USTAVOK);
  else
    _CLEAR_BIT(p_active_functions, RANG_3_GRUPA_USTAVOK);

  if (_GET_OUTPUT_STATE(grupa_ustavok, 11))
      _SET_BIT(p_active_functions, RANG_4_GRUPA_USTAVOK);
  else
    _CLEAR_BIT(p_active_functions, RANG_4_GRUPA_USTAVOK);
}
/*****************************************************/

/*****************************************************/
