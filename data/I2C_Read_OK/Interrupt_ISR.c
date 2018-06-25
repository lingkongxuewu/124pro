//#include "main.h"
#include "compiler_defs.h"
#include "C8051F500_defs.h"            // SFR declarations
#include "parameter_defs.h"
#include "Function_defs.h"
#include "stdio.h"
#include "Interrupt_ISR.h"
#include "Precision_Calibration.h"
#include "math.h"

//-----------------------------------------------------------------------------
// CAN0_ISR
//-----------------------------------------------------------------------------



INTERRUPT(Timer2_ISR, INTERRUPT_TIMER2)
{
	static U8 cc=0;
   TF2H = 0;                           // Clear Timer2 interrupt flag
 //  RX_OK = 1;
	
   if(Time_Mode==1)
   {
		
   		if(Counter<Cycle_Time_Value)
   		{
			if(cc == 10)
			{
				cc = 0;
   				Counter++;
			}
			else
				cc++;
		}
   		else
   		{
			TX_OK = 1;
  
   			Counter = 0;
   		}
   }
}

//-----------------------------------------------------------------------------
// ADC0_ISR
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
