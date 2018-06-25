

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <compiler_defs.h>
#include <C8051F500_defs.h>            // SFR declarations
#include <stdio.h>

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------

#define SYSCLK      24000000           // SYSCLK frequency in Hz
#define BAUDRATE      115200           // Baud rate of UART in bps
#define SHORT					1
#define MIDDLE					2
#define LONG					3
#define	TEN						4
sbit 	I2C_SCL					= P1^0;
sbit    I2C_SDA			    	= P1^3;
//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------

void SYSCLK_Init (void);
void UART0_Init (void);
void PORT_Init (void);
void Delay(U8 time);
void WriteI2Cbyte (U8 I2C_data);
U8 ReadI2Cbyte(U8 ackvalue);
void I2C_WaitACK(void);
void I2C_Start(void);
void I2C_Stop(void);

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------

void main (void)
{
  	U16 xdata yr,i,j;
  	U8 xdata tempr[2];
   	SFRPAGE = ACTIVE_PAGE;              // Change for PCA0MD and SBUF0
   	PCA0MD &= ~0x40;                    // Disable the watchdog timer

   	PORT_Init ();                       // Initialize Port I/O
   	SYSCLK_Init ();                     // Initialize Oscillator
   	UART0_Init ();
	I2C_SDA = 1;
	I2C_SCL = 1;
	
	for(j=0;j<10;j++)
	{
   		for(i=0;i<50000;i++);
		Delay(LONG);for(i=0;i<50000;i++);
	}

	I2C_Start();
	WriteI2Cbyte(0x30);
	I2C_WaitACK();
	Delay(SHORT);
	WriteI2Cbyte(0x70);
	I2C_WaitACK();
	Delay(SHORT);
	I2C_Stop();
	for(j=0;j<10;j++)
	{
   		for(i=0;i<50000;i++);
		Delay(LONG);for(i=0;i<50000;i++);
	}

    while (1)
    {
		I2C_Start();
		Delay(SHORT);
		WriteI2Cbyte(0x20);
		I2C_WaitACK();
		Delay(SHORT);
		WriteI2Cbyte(0x80);
		I2C_WaitACK();
		I2C_Stop();
		
		Delay(LONG);
		I2C_Start();
		WriteI2Cbyte(0x21);
		I2C_WaitACK();

		tempr[0] = ReadI2Cbyte(0);
		tempr[1] = ReadI2Cbyte(1);
		I2C_Stop();
	
		yr= ((U16)(tempr[0]<<8))|tempr[1];
		printf("yr=%d\n",(U16)yr);
		for(i=0;i<50000;i++);
   }
}

//-----------------------------------------------------------------------------
// Initialization Subroutines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PORT_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Configure the Crossbar and GPIO ports.
//
// P0.4   digital   push-pull    UART TX
// P0.5   digital   open-drain   UART RX
//
//-----------------------------------------------------------------------------
void PORT_Init (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CONFIG_PAGE;

   P0MDOUT |= 0x10;                    // Enable UTX as push-pull output
   XBR0    = 0x09;                     // Enable UART on P0.4(TX) and P0.5(RX)
   XBR2    = 0x40;                     // Enable crossbar and weak pull-ups

   SFRPAGE = SFRPAGE_save;
}

//-----------------------------------------------------------------------------
// SYSCLK_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This routine initializes the system clock to use the internal oscillator
// at its maximum frequency.
// Also enables the Missing Clock Detector.
//-----------------------------------------------------------------------------

void SYSCLK_Init (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CONFIG_PAGE;

   OSCICN |= 0x87;                     // Configure internal oscillator for
                                       // its maximum frequency
   RSTSRC  = 0x04;                     // Enable missing clock detector

   SFRPAGE = SFRPAGE_save;
}

//-----------------------------------------------------------------------------
// UART0_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Configure the UART0 using Timer1, for <BAUDRATE> and 8-N-1.
//-----------------------------------------------------------------------------
void UART0_Init (void)
{
   U8 SFRPAGE_save = SFRPAGE;
   SFRPAGE = CONFIG_PAGE;

   SCON0 = 0x10;                       // SCON0: 8-bit variable bit rate
                                       // clear RI0 and TI0 bits

   // Baud Rate = [BRG Clock / (65536 - (SBRLH0:SBRLL0))] x 1/2 x 1/Prescaler

#if   ((SYSCLK / BAUDRATE / 2 / 0xFFFF) < 1)
      SBRL0 = -(SYSCLK / BAUDRATE / 2);
      SBCON0 |= 0x03;                  // Set prescaler to 1
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

   SFRPAGE = SFRPAGE_save;
}

void Delay(U8 time)
{
	U16 delay_count;
	switch(time)
	{
		case SHORT:
			for(delay_count=0;delay_count<100;delay_count++);
		break;
		case MIDDLE:
			for(delay_count=0;delay_count<1000;delay_count++);
		break;
		case LONG:
			for(delay_count=0;delay_count<10000;delay_count++);
		break;
		case TEN:
			for(delay_count=0;delay_count<30;delay_count++);
		break;
	}
}

void WriteI2Cbyte (U8 I2C_data)
{
	U16 xdata i,j;
	Delay(SHORT);
	I2C_SCL = 0;
	
	for(i=0;i<8;i++)
	{
		j = I2C_data & 0x80;
		if(j==0)
		{
			I2C_SDA = 0;
		}	
		else
		{
			I2C_SDA =1;
		}
		Delay(TEN);
		I2C_SCL = 1;
		Delay(SHORT);
		I2C_SCL = 0;
		Delay(SHORT);
		I2C_data = I2C_data << 1;
	}
	I2C_SDA = 1;
	Delay(SHORT);
}

void I2C_WaitACK(void)
{
	U16 xdata j;
   I2C_SCL = 1;Delay(SHORT);
   while((I2C_SDA == 1 )&& j<10)
   {j++;
   }
   I2C_SCL = 0;Delay(SHORT);
}

void I2C_Start(void)
{
 	I2C_SDA=1;	Delay(SHORT);
  	I2C_SCL=1; 	Delay(SHORT);
  	I2C_SDA=0; 	Delay(SHORT);
  	I2C_SCL=0; 	Delay(SHORT);
}

void I2C_Stop(void)
{
 	I2C_SDA=0;
  	Delay(SHORT);
  	I2C_SCL=1;
  	Delay(SHORT);
	I2C_SDA=1;
  	Delay(SHORT);
}

U8 ReadI2Cbyte(U8 ackvalue)
{	
	U8 xdata i,j;   		
	j = 0;
	for(i=0;i<8;i++)
	{
		j<<=1;
		I2C_SCL = 1;
		Delay(SHORT);
		if(I2C_SDA == 1)
		{
			j |= 1;
		}
		else
		{
			j &= 0xfe;
		}
		I2C_SCL = 0 ;
		Delay(SHORT);
	}
	I2C_SDA = ackvalue;
	Delay(SHORT);
	I2C_SCL = 1;
	Delay(SHORT);
	I2C_SCL = 0;
	Delay(SHORT);
	I2C_SDA = 1;
	Delay(SHORT);
	return j;
}

