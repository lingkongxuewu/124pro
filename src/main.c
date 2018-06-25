
#define   __MAIN_C__
#include "_Include.h"

void main (void)
{
    SFRPAGE = ACTIVE_PAGE;    		// Set for PCA0MD
    PCA0MD &= ~0x40;          		// WDTE = 0 (clear watchdog timer enable)
    Init_All();
	delay_ms(250);

	EA = 1;
	IIC_StorOrRestor_2(Add2_Slave,EEPROM2RDAC);
	IIC_StorOrRestor_2(Add3_Slave,EEPROM2RDAC);
	IIC_StorOrRestor_3(Add2_Slave,EEPROM2RDAC);
	IIC_StorOrRestor_3(Add3_Slave,EEPROM2RDAC);


	 while(1)
	{
		Send_TimeProc();
	}
	
}
//***********************************************************************/
		 