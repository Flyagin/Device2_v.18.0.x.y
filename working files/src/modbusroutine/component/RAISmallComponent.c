
#include "header.h"

//начальный регистр в карте памяти
#define BEGIN_ADR_REGISTER 445
//конечный регистр в карте памяти
#define END_ADR_REGISTER 477

#define MM_ADDRESS_FIRST_MEASUREMENTS_DR       BEGIN_ADR_REGISTER


#define MDR_OFFSET_VMP                         32

int getRAISmallModbusRegister(int);//получить содержимое регистра
int getRAISmallModbusBit(int);//получить содержимое бита
int setRAISmallModbusRegister(int, int);//получить содержимое регистра
int setRAISmallModbusBit(int, int);//получить содержимое бита

void preRAISmallReadAction(void);//action до чтения
void preRAISmallWriteAction(void);//action до записи
int  postRAISmallWriteAction(void);//action после записи

int privateRAISmallGetReg2(int adrReg);

COMPONENT_OBJ *raismallcomponent;

/**************************************/
//компонент измерений в момент аварии
/**************************************/
void constructorRAISmallComponent(COMPONENT_OBJ *raismallcomp)
{
  raismallcomponent = raismallcomp;

  raismallcomponent->getModbusRegister = getRAISmallModbusRegister;//получить содержимое регистра
  raismallcomponent->getModbusBit      = getRAISmallModbusBit;//получить содержимое бита
  raismallcomponent->setModbusRegister = setRAISmallModbusRegister;//получить содержимое регистра
  raismallcomponent->setModbusBit      = setRAISmallModbusBit;//получить содержимое бита

  raismallcomponent->preReadAction   = preRAISmallReadAction;//action до чтения
  raismallcomponent->preWriteAction  = preRAISmallWriteAction;//action до записи
  raismallcomponent->postWriteAction = postRAISmallWriteAction;//action после записи

  raismallcomponent->isActiveActualData = 0;
}//constructorIUSmallComponent(COMPONENT_OBJ *iucomp)

int getRAISmallModbusRegister(int adrReg)
{
  //получить содержимое регистра
  if(privateRAISmallGetReg2(adrReg)==MARKER_OUTPERIMETR) return MARKER_OUTPERIMETR;
  
  if (
    //Не подано попередньокоманди вичитування відповідного запису дискретного реєстратора
    //pointInterface=0 метка интерфейса 0-USB 1-RS485
    ((pointInterface == USB_RECUEST  ) && (number_record_of_dr_for_USB == 0xffff)) ||
    ((pointInterface == RS485_RECUEST) && (number_record_of_dr_for_RS485 == 0xffff))
  ) return MARKER_ERRORPERIMETR;
  if (
    //Зараз іде зчитування для інтерфейсу запису дискретного реєстратора, або очистка його, тому ця операція є тимчасово недоступною
    ((clean_rejestrators & CLEAN_DR) != 0) ||
    (
      ((pointInterface == USB_RECUEST  ) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB  ) != 0)) ||
      ((pointInterface == RS485_RECUEST) && ((control_tasks_dataflash & TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485) != 0))
    )
  ) return MARKER_ERRORPERIMETR; //Не подано попередньокоманди вичитування відповідного запису дискретного реєстратора

  //Можна читати дані
  int offset;
  unsigned char *point_to_buffer;
  offset = (adrReg - MM_ADDRESS_FIRST_MEASUREMENTS_DR);
  if (pointInterface == USB_RECUEST) point_to_buffer = buffer_for_USB_read_record_dr;
  else point_to_buffer = buffer_for_RS485_read_record_dr;

  switch (offset)
  {
  case MDR_OFFSET_VMP:
  {
    unsigned char *point_unsigned_char = (unsigned char *)(point_to_buffer + FIRST_INDEX_VMP_VALUE);
    unsigned int *point_unsigned_int = (unsigned int*)point_unsigned_char;
    int value_int = *point_unsigned_int;

    if (((unsigned int)value_int) != ((unsigned int)UNDEF_VMP))
    {
      if (abs(value_int) >= 10)
        return (value_int/10) &0xFFFF;
      else
      {
        if (value_int >= 0)
          return 1;
        else
          return (-1)&0x0000FFFF;
      }
    }
    return 0;
  }//case MDR_OFFSET_VMP:
  }//switch
  return 0;
}//getDVModbusRegister(int adrReg)
int getRAISmallModbusBit(int x) {
  //получить содержимое bit
  UNUSED(x);
  return MARKER_OUTPERIMETR;
}//getIUModbusBit(int )
int setRAISmallModbusRegister(int x, int y) {
  UNUSED(x);
  UNUSED(y);
  //записать содержимое регистра
  return MARKER_OUTPERIMETR;
}//setIUModbusRegister(int, int)
int setRAISmallModbusBit(int x, int y) {
  UNUSED(x);
  UNUSED(y);
  //записать содержимое bit
  return MARKER_OUTPERIMETR;
}//setIUModbusBit(int, int )

void preRAISmallReadAction(void) {
//action до чтения
  raismallcomponent->isActiveActualData = 1;
}//

void preRAISmallWriteAction(void) {
//action до записи
  raismallcomponent->operativMarker[0] = -1;
  raismallcomponent->operativMarker[1] = -1;//оперативный маркер
  raismallcomponent->isActiveActualData = 1;
}//
int postRAISmallWriteAction(void) {
//action после записи
  return 0;
}//

int privateRAISmallGetReg2(int adrReg)
{
  //проверить внешний периметр
  return controlPerimetr(adrReg, BEGIN_ADR_REGISTER, END_ADR_REGISTER);
}//privateRAISmallGetReg2(int adrReg)

