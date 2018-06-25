//-----------------------------------------------------------------------------
//CAN BUS Module Program
//Sinocomopto Technology	
//Edit by: Roben Luo
//Data:2009-08-20							
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "compiler_defs.h"
#include "C8051F500_defs.h"            // SFR declarations
#include "Mcu_Init.h"
#include "Parameter_defs.h"
#include "main.h"
#include "Interrupt_ISR.h"
#include "MyFlash.h"
#include "Function_defs.h"
#include "math.h"
#include "Precision_Calibration.h"
#include <stdio.h>

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------
INTERRUPT_PROTO (TIMER2_ISR, INTERRUPT_TIMER2);


//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------


void main (void)
{ 


   SFRPAGE = ACTIVE_PAGE;              // Set for PCA0MD

   PCA0MD &= ~0x40;                    // Disable Watchdog Timer

   OSCILLATOR_Init ();                 // Initialize oscillator
   PORT_Init ();                       // Initialize crossbar and GPIO
//   UART0_Init();

//	ADC0_Init ();


//   EIE2 |= 0x02;                       // Enable CAN interupts
//   EIP2 |= 0x02;
   EA = 1;                             // Enable global interrupts


	Delay(MIDDLE);
	I2C_Start();
	WriteI2Cbyte(0x20);
	I2C_WaitACK();
	WriteI2Cbyte(0x70);
	I2C_WaitACK();
	I2C_Stop();
	Delay(MIDDLE);
	while(1)
	{

	//	I2C_Start();
		WriteI2Cbyte(0xFF);
	/*	I2C_WaitACK();
		WriteI2Cbyte(0x80);
		I2C_WaitACK();
		I2C_Stop();*/

	/*	Delay(LONG);
		WriteI2Cbyte(0x21);
		I2C_WaitACK();
		tempr[0] = ReadI2Cbyte();
		I2C_SDA = 0;
		Delay(SHORT);
		I2C_SCL = 0;
		Delay(SHORT);
		I2C_SCL = 1;
		Delay(SHORT);
		tempr[1] = ReadI2Cbyte();
		I2C_SDA = 1;
		Delay(SHORT);
		I2C_SCL = 1;
		Delay(SHORT);
		I2C_SCL = 0;
		Delay(SHORT);
		I2C_Stop();
		
		yr= ((U16)(tempr[0]<<8))|tempr[1];
		printf("yr=%d\n",yr);
		Delay(LONG);
		Delay(LONG);
		for(i=0;i<10000;i++);*/
/*		I2C_SDA_IN();
		dd = 0;
		printf("dd=%d\n",(U16)dd);*/
//		for(i=0;i<50000;i++);
	
	}
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------

