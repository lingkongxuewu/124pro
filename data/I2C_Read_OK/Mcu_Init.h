#include <compiler_defs.h>
#include <c8051F500_defs.h>
#include "Function_defs.h"
#include "Parameter_defs.h"

void Default_Parameter(void);
void PARAMETER_Init(void);
void OSCILLATOR_Init (void);
void PORT_Init (void);
void CAN0_Init (void);
void UART0_Init (void);
void TIMER2_Init (U16 counts);
void ADC0_Init (void);
void Load_Default_Parameter(U8 default_flag);
void CanBus_BaudRate_Select(U8 baud);
U16  Can_Id_Init(U8 id_kind);
U16  Can_ExId_Init(U8 id_kind);
U8   _Status(void);
void Can_Rx_Init(void);
void Can_Tx_Init(void);
void CAN0_TransferMO (U8 fsc,U8 data0,U8 data1,U8 data2,U8 data3,U8 data4,U8 data5,U8 data6,U8 obj_num);
void Can_BusyF1Test(void);
void Can_BusyF2Test(void);

