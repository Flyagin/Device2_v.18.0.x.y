#ifndef __GLOBAL_EXTERNAL_M_H
#define __GLOBAL_EXTERNAL_M_H

#include "componentdef.h"
#include "componentenum.h"
#include "prototyps.h"

extern  COMPONENT_OBJ config_array[];
extern  short tempReadArray[];
extern  short tempWriteArray[];
extern  int   indexTW;//������ ������ ������
extern  int   pointInterface;//����� ���������� 0-USB 1-RS485

//��� ��������� ������ ���������� ������-������� ���������
#define SOURCEMARKER_DTR  10
//��� ��������� ������ ���������� ������ ��
#define SOURCEMARKER_MFT  20

//�������������� ��� ������� ����������
//#define TESTZBIRKA_VERSII_PZ

#endif
