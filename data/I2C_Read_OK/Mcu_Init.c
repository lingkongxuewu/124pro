#include <compiler_defs.h>
#include <c8051F500_defs.h>



#include "Mcu_Init.h"
#include "MyFlash.h"
#include "Precision_Calibration.h"
#include "stdio.h"
#include "interrupt_isr.h"
//-----------------------------------------------------------------------------
// Initialization Subroutines
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// OSCILLATOR_Init
//-----------------------------------------------------------------------------

void OSCILLATOR_Init (void)
{
   U8 sfrpage_save = SFRPAGE;
   SFRPAGE = CONFIG_PAGE;

   OSCICN = 0xD6;                      
//   RSTSRC = 0x04;                    
   SFRPAGE = sfrpage_save;


}

//-----------------------------------------------------------------------------
// PORT_Init
//-----------------------------------------------------------------------------

void PORT_Init (void)
{
   U8 sfrpage_save = SFRPAGE;
   SFRPAGE  = CONFIG_PAGE;  
   P0SKIP |= 0x01;                     // Skip P0.0 (VREF)
 //  P1SKIP |= 0x0E;                     // Skip P1.2 (ADC input)        
   P0MDOUT  |= 0x50;                   
   P0MDIN  &= ~0x01;                   // Set VREF to analog
//   P1MDOUT  |= 0x08;       
   P1MDOUT  |= 0x00;
//   P2MDIN  &= ~0x02;   
   XBR0     = 0x03;                    
   XBR2     = 0x40;                    
   SFRPAGE = sfrpage_save;
}


//-----------------------------------------------------------------------------
// UART0_Init
//-----------------------------------------------------------------------------
void UART0_Init (void)
{
   U8 sfrpage_save = SFRPAGE;
   SFRPAGE = CONFIG_PAGE;

   SCON0 = 0x10;                       

   // Baud Rate = [BRG Clock / (65536 - (SBRLH0:SBRLL0))] x 1/2 x 1/Prescaler

#if   ((SYSCLK / BAUDRATE / 2 / 0xFFFF) < 1)
      SBRL0 = -(SYSCLK / BAUDRATE / 2);
      SBCON0 |= 0x03;                  // Set prescaler to 1*/
#elif ((SYSCLK / BAUDRATE / 2 / 0xFFFF) < 4)
      SBRL0 = -(SYSCLK / BAUDRATE / 2 / 4);
      SBCON0 &= ~0x03;
      SBCON0 |= 0x01;                  // Set prescaler to 4
#elif ((SYSCLK / BAUDRATE / 2 / 0xFFFF) < 12)
      SBRL0 = -(SYSCLK / BAUDRATE / 2 / 12);
      SBCON0 &= ~0x03;                 // Set prescaler to 12
#else
      SBRL0 = -(SYSCLK / BAUDRATE / 2 / 48);
      SBCON0 &= ~0x03;
      SBCON0 |= 0x02;                  // Set prescaler to 48
#endif

   SBCON0 |= 0x40;                     // Enable baud rate generator
   TI0 = 1;                            // Indicate TX0 ready

   SFRPAGE = sfrpage_save;
}

//-----------------------------------------------------------------------------
// TIMER2_Init
//-----------------------------------------------------------------------------
void TIMER2_Init (U16 counts)
{
   U8 sfrpage_save = SFRPAGE;
   SFRPAGE = ACTIVE_PAGE;

   TMR2CN  = 0x00;                     // Stop Timer2; Clear TF2;
                                       // use SYSCLK/12 as timebase
   CKCON  &= ~0x60;                    // Timer2 clocked based on T2XCLK;

   TMR2RL  = -counts;                  // Init reload values
   TMR2    = 0xFFFF;                   // Set to reload immediately
   ET2     = 1;                        // Enable Timer2 interrupts
   TR2     = 1;                        // Start Timer2

   SFRPAGE = sfrpage_save;
}



//-----------------------------------------------------------------------------
// ADC0_Init
//-----------------------------------------------------------------------------
void ADC0_Init (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = ACTIVE_PAGE;

   // Initialize the Gain to account for a 5V input and 2.25 VREF
   // Solve the equation provided in Section 9.3.1 of the Datasheet

   // The 5V input is scaled by a factor of 0.44 so that the maximum input
   // voltage seen by the pin is 2.2V

   // 0.44 = (GAIN/4096) + GAINADD * (1/64)

   // Set GAIN to 0x6CA and GAINADD to 1
   // GAIN = is the 12-bit word formed by ADC0GNH[7:0] ADC0GNL[7:4]
   // GAINADD is bit ADC0GNA.0

   ADC0CF |= 0x01;                     // Set GAINEN = 1
   ADC0H   = 0x04;                     // Load the ADC0GNH address
   ADC0L   = 0x6C;                     // Load the upper byte of 0x6CA to 
                                       // ADC0GNH
   ADC0H   = 0x07;                     // Load the ADC0GNL address
   ADC0L   = 0xA0;                     // Load the lower nibble of 0x6CA to 
                                       // ADC0GNL
   ADC0H   = 0x08;                     // Load the ADC0GNA address
   ADC0L   = 0x01;                     // Set the GAINADD bit
   ADC0CF &= ~0x01;                    // Set GAINEN = 0

   ADC0CN = 0x03;                      // ADC0 disabled, normal tracking,
                                       // conversion triggered on TMR2 overflow
                                       // Output is right-justified

   REF0CN = 0x33;                      // Enable on-chip VREF and buffer
                                       // Set voltage reference to 2.25V

   ADC0MX = 0x0B;                      // Set ADC input to P1.2

   ADC0CF = ((SYSCLK / 3000000) - 1) << 3;   // Set SAR clock to 3MHz

   EIE1 |= 0x04;                       // Enable ADC0 conversion complete int.

   AD0EN = 1;                          // Enable ADC0

   SFRPAGE = SFRPAGE_save;
}




//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------

