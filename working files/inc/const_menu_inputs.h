#ifndef __CONSTANTS_INPUTS__
#define __CONSTANTS_INPUTS__

#define EKRAN_LIST_INPUTS_FOR_RANGUVANNJA        (EKRAN_CONTROL_UP + 1)

#define EKRAN_RANGUVANNJA_INPUT_1                (EKRAN_TRANSFORMATOR_INFO_CONTROL + 1)
#define EKRAN_RANGUVANNJA_INPUT_2                (EKRAN_RANGUVANNJA_INPUT_1 + 1)
#define EKRAN_RANGUVANNJA_INPUT_3                (EKRAN_RANGUVANNJA_INPUT_2 + 1)
#define EKRAN_RANGUVANNJA_INPUT_4                (EKRAN_RANGUVANNJA_INPUT_3 + 1)
#define EKRAN_RANGUVANNJA_INPUT_5                (EKRAN_RANGUVANNJA_INPUT_4 + 1)
#define EKRAN_RANGUVANNJA_INPUT_6                (EKRAN_RANGUVANNJA_INPUT_5 + 1)
#define EKRAN_RANGUVANNJA_INPUT_7                (EKRAN_RANGUVANNJA_INPUT_6 + 1)
#define EKRAN_RANGUVANNJA_INPUT_8                (EKRAN_RANGUVANNJA_INPUT_7 + 1)

#if (                                \
     (MODYFIKACIA_VERSII_PZ == 0) || \
     (MODYFIKACIA_VERSII_PZ == 1) || \
     (MODYFIKACIA_VERSII_PZ == 3)    \
    )

#define EKRAN_RANGUVANNJA_INPUT_9                (EKRAN_RANGUVANNJA_INPUT_8 + 1)
#define EKRAN_RANGUVANNJA_INPUT_10               (EKRAN_RANGUVANNJA_INPUT_9 + 1)
#define EKRAN_RANGUVANNJA_INPUT_11               (EKRAN_RANGUVANNJA_INPUT_10 + 1)
#define EKRAN_RANGUVANNJA_INPUT_12               (EKRAN_RANGUVANNJA_INPUT_11 + 1)
#define EKRAN_RANGUVANNJA_INPUT_13               (EKRAN_RANGUVANNJA_INPUT_12 + 1)
#define EKRAN_RANGUVANNJA_INPUT_14               (EKRAN_RANGUVANNJA_INPUT_13 + 1)
#define EKRAN_RANGUVANNJA_INPUT_15               (EKRAN_RANGUVANNJA_INPUT_14 + 1)
#define EKRAN_RANGUVANNJA_INPUT_16               (EKRAN_RANGUVANNJA_INPUT_15 + 1)

#if (MODYFIKACIA_VERSII_PZ == 0)

#define EKRAN_RANGUVANNJA_INPUT_17               (EKRAN_RANGUVANNJA_INPUT_16 + 1)
#define EKRAN_RANGUVANNJA_INPUT_18               (EKRAN_RANGUVANNJA_INPUT_17 + 1)
#define EKRAN_RANGUVANNJA_INPUT_19               (EKRAN_RANGUVANNJA_INPUT_18 + 1)
#define EKRAN_RANGUVANNJA_INPUT_20               (EKRAN_RANGUVANNJA_INPUT_19 + 1)

#endif

#endif

#if (MODYFIKACIA_VERSII_PZ == 0)

#define EKRAN_RANGUVANNJA_INPUT_LAST             EKRAN_RANGUVANNJA_INPUT_20

#elif (                                 \
       (MODYFIKACIA_VERSII_PZ == 1) ||  \
       (MODYFIKACIA_VERSII_PZ == 3)     \
      )   

#define EKRAN_RANGUVANNJA_INPUT_LAST             EKRAN_RANGUVANNJA_INPUT_16

#else

#define EKRAN_RANGUVANNJA_INPUT_LAST             EKRAN_RANGUVANNJA_INPUT_8

#endif

#define MAX_ROW_LIST_INPUTS_FOR_RANGUVANNJA       NUMBER_INPUTS
#define MAX_ROW_RANGUVANNJA_INPUT                 NUMBER_TOTAL_SIGNAL_FOR_RANG_SMALL

#define NAME_RANG_SMALL_RU         \
  "  ����.���.��   ",                   \
  " ����� ���������",                   \
  "   ����� ����   ",                   \
  " �����./�������.",                   \
  "  ��������� ��  ",                   \
  "����.�� ��.�����",                   \
  "     ���.��     ",                   \
  " �������� ���.  ",                   \
  "    ����.��     ",                   \
  " �������� ����. ",                   \
  " 1-� ��.������� ",                   \
  " 2-� ��.������� ",                   \
  " 3-� ��.������� ",                   \
  " 4-� ��.������� ",                   \
  " �.���.���.� �� ",                   \
  "    ����.��1    ",                   \
  "    ����.��2    ",                   \
  "  ����.���.��2  ",                   \
  "   ��.���.��2   ",                   \
  "    ����.��3    ",                   \
  "  ����.���.��3  ",                   \
  "   ��.���.��3   ",                   \
  "    ����.��4    ",                   \
  "  ����.���.��4  ",                   \
  "   ��.���.��4   ",                   \
  "   ��.��� ��    ",                   \
  "   ����.���1    ",                   \
  "   ����.���2    ",                   \
  " ����.���.���2  ",                   \
  "   ����.���3    ",                   \
  "   ����.���4    ",                   \
  "    ����.���    ",                   \
  " ���� ��� �� �� ",                   \
  "    ����.���    ",                   \
  "   ����.����1   ",                   \
  "   ����.����2   ",                   \
  "   ����.����3   ",                   \
  " ����.����.���  ",                   \
  " ���/���� �� �� ",                   \
  "   ����.���1    ",                   \
  "   ����.���2    ",                   \
  " ���� ���� �� ��",                   \
  " ����.���(���)  ",                   \
  "  ����.�����1   ",                   \
  "  ���� �����1   ",                   \
  "  ����.�����2   ",                   \
  "  ���� �����2   ",                   \
  "  ����.������1  ",                   \
  "  ����.������2  ",                   \
  "    ����.��x    ",                   \
  " ��.�-�������1  ",                   \
  " ��.�-�������2  ",                   \
  " ��.�-�������3  ",                   \
  " ��.�-�������4  ",                   \
  " ��.�-�������5  ",                   \
  " ��.�-�������6  ",                   \
  " ��.�-�������7  ",                   \
  " ��.�-�������8  ",                   \
  " ���.�-��������1",                   \
  " ���.�-��������1",                   \
  " ���.�-��������2",                   \
  " ���.�-��������2",                   \
  " ���.�-��������3",                   \
  " ���.�-��������3",                   \
  " ���.�-��������4",                   \
  " ���.�-��������4"

#define NAME_RANG_SMALL_UA         \
  " ����.�����.�� ",                   \
  " ����.��������� ",                   \
  "   ����.����    ",                   \
  " ̳��./�������. ",                   \
  "    ���� ��     ",                   \
  "����.�� ����.�.",                   \
  "    ����.��    ",                   \
  " �������� ����.",                   \
  "    ����.��     ",                   \
  " �������� ����. ",                   \
  " 1-� ��.������� ",                   \
  " 2-� ��.������� ",                   \
  " 3-� ��.������� ",                   \
  " 4-� ��.������� ",                   \
  " �.���.���.�� ��",                   \
  "    ����.��1    ",                   \
  "    ����.��2    ",                   \
  "  ����.��.��2   ",                   \
  "   ��.��.��2    ",                   \
  "    ����.��3    ",                   \
  "  ����.��.��3   ",                   \
  "   ��.��.��3    ",                   \
  "    ����.��4    ",                   \
  "  ����.��.��4   ",                   \
  "   ��.��.��4    ",                   \
  "  ����.��� ��   ",                   \
  "   ����.���1    ",                   \
  "   ����.���2    ",                   \
  " ����.�����.���2",                   \
  "   ����.���3    ",                   \
  "   ����.���4    ",                   \
  "    ����.���    ",                   \
  " ���� ��� �� ��",                   \
  "    ����.���    ",                   \
  "   ����.����1   ",                   \
  "   ����.����2   ",                   \
  "   ����.����3   ",                   \
  " ����.����.���  ",                   \
  " ���/���� �� ��",                   \
  "   ����.���1    ",                   \
  "   ����.���2    ",                   \
  "���� ���� �� ��",                   \
  " ����.���(���)  ",                   \
  "  ����.����1   ",                   \
  "  ���� ����1   ",                   \
  "  ����.����2   ",                   \
  "  ���� ����2   ",                   \
  "  ����.������1  ",                   \
  "  ����.������2  ",                   \
  "    ����.��x    ",                   \
  " ��.�-�������1  ",                   \
  " ��.�-�������2  ",                   \
  " ��.�-�������3  ",                   \
  " ��.�-�������4  ",                   \
  " ��.�-�������5  ",                   \
  " ��.�-�������6  ",                   \
  " ��.�-�������7  ",                   \
  " ��.�-�������8  ",                   \
  " ���.�-������1 ",                   \
  " ��.�-������1  ",                   \
  " ���.�-������2 ",                   \
  " ��.�-������2  ",                   \
  " ���.�-������3 ",                   \
  " ��.�-������3  ",                   \
  " ���.�-������4 ",                   \
  " ��.�-������4  "

#define NAME_RANG_SMALL_EN         \
  "  CB Close Blk  ",                   \
  "   LED Reset    ",                   \
  "  Relay Reset   ",                   \
  "  Local/Remote  ",                   \
  "    CB State    ",                   \
  " Ext CB Open Cmd",                   \
  "  Close CB Cmd  ",                   \
  " CB Op Circ Ctl ",                   \
  "  Open CB Cmd   ",                   \
  " CB Cl Circ Ctl ",                   \
  " SetPoints gr-1 ",                   \
  " SetPoints gr-2 ",                   \
  " SetPoints gr-3 ",                   \
  " SetPoints gr-4 ",                   \
  "Rem Ctr R Bl Res",                   \
  "   Blc.of ��1   ",                   \
  "   Blc.of ��2   ",                   \
  "  ��2 Acc.Blc.  ",                   \
  "   ��.���.��2   ",                   \
  "   Blc.of ��3   ",                   \
  "  ��3 Acc.Blc.  ",                   \
  "   ��.���.��3   ",                   \
  "   Blc.of ��4   ",                   \
  "  ��4 Acc.Blc.  ",                   \
  "   ��.���.��4   ",                   \
  "   ��.��� ��    ",                   \
  "    OCP1 Blk    ",                   \
  "    OCP2 Blk    ",                   \
  "  OCP2 Acc Blk  ",                   \
  "    OCP3 Blk    ",                   \
  "    OCP4 Blk    ",                   \
  "    AFD Blk     ",                   \
  "AFD via BI Start",                   \
  "   SDEFP Blk    ",                   \
  "   DEFP1 Blk    ",                   \
  "   DEFP2 Blk    ",                   \
  "   DEFP3 Blk    ",                   \
  "     AR Blk     ",                   \
  " LF�/FAR vBI St ",                   \
  "    LF�1 Blk    ",                   \
  "    LF�2 Blk    ",                   \
  " CBF vBI Start  ",                   \
  "   NSOCP Blk    ",                   \
  "    UVP1 Blk    ",                   \
  " UVP1 vBI Start ",                   \
  "    UVP2 Blk    ",                   \
  " UVP2 vBI Start ",                   \
  "    OVP1 Blk    ",                   \
  "    OVP2 Blk    ",                   \
  "   MFPx Block   ",                   \
  "  UD-Func 1 In  ",                   \
  "  UD-Func 2 In  ",                   \
  "  UD-Func 3 In  ",                   \
  "  UD-Func 4 In  ",                   \
  "  UD-Func 5 In  ",                   \
  "  UD-Func 6 In  ",                   \
  "  UD-Func 7 In  ",                   \
  "  UD-Func 8 In  ",                   \
  "  UD-FF 1 Set   ",                   \
  " UD-FF 1 Reset  ",                   \
  "  UD-FF 2 Set   ",                   \
  " UD-FF 2 Reset  ",                   \
  "  UD-FF 3 Set   ",                   \
  " UD-FF 3 Reset  ",                   \
  "  UD-FF 4 Set   ",                   \
  " UD-FF 4 Reset  "
        
#define NAME_RANG_SMALL_KZ         \
  "  ����.���.��   ",                   \
  " ����� ���������",                   \
  "   ����� ����   ",                   \
  " �����./�������.",                   \
  "  ��������� ��  ",                   \
  "����.�� ��.�����",                   \
  "     ���.��     ",                   \
  " �������� ���.  ",                   \
  "    ����.��     ",                   \
  " �������� ����. ",                   \
  " 1-� ��.������� ",                   \
  " 2-� ��.������� ",                   \
  " 3-� ��.������� ",                   \
  " 4-� ��.������� ",                   \
  " �.���.���.� �� ",                   \
  "    ����.��1    ",                   \
  "    ����.��2    ",                   \
  "  ����.���.��2  ",                   \
  "   ��.���.��2   ",                   \
  "    ����.��3    ",                   \
  "  ����.���.��3  ",                   \
  "   ��.���.��3   ",                   \
  "    ����.��4    ",                   \
  "  ����.���.��4  ",                   \
  "   ��.���.��4   ",                   \
  "   ��.��� ��    ",                   \
  "   ����.���1    ",                   \
  "   ����.���2    ",                   \
  " ����.���.���2  ",                   \
  "   ����.���3    ",                   \
  "   ����.���4    ",                   \
  "    ����.���    ",                   \
  " ���� ��� �� �� ",                   \
  "    ����.���    ",                   \
  "   ����.����1   ",                   \
  "   ����.����2   ",                   \
  "   ����.����3   ",                   \
  " ����.����.���  ",                   \
  " ���/���� �� �� ",                   \
  "   ����.���1    ",                   \
  "   ����.���2    ",                   \
  " ���� ���� �� ��",                   \
  " ����.���(���)  ",                   \
  "  ����.�����1   ",                   \
  "  ���� �����1   ",                   \
  "  ����.�����2   ",                   \
  "  ���� �����2   ",                   \
  "  ����.������1  ",                   \
  "  ����.������2  ",                   \
  "    ����.��x    ",                   \
  " ��.�-�������1  ",                   \
  " ��.�-�������2  ",                   \
  " ��.�-�������3  ",                   \
  " ��.�-�������4  ",                   \
  " ��.�-�������5  ",                   \
  " ��.�-�������6  ",                   \
  " ��.�-�������7  ",                   \
  " ��.�-�������8  ",                   \
  " ���.�-��������1",                   \
  " ���.�-��������1",                   \
  " ���.�-��������2",                   \
  " ���.�-��������2",                   \
  " ���.�-��������3",                   \
  " ���.�-��������3",                   \
  " ���.�-��������4",                   \
  " ���.�-��������4"
        
#endif 
