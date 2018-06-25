#ifndef _SMBUS_H_
#define _SMBUS_H_


#include "_include.h"

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------



#define  SMB_FREQUENCY  10000          // Target SCL clock rate
                                       // This example supports between 10kHz
                                       // and 100kHz

#define  SMBUS_WRITE          0x00           // SMBus WRITE command
#define  SMBUS_READ           0x01           // SMBus READ command

// Device addresses (7 bits, lsb is a don't care)
#define  SLAVE_ADDR     0x30           // Device address for slave target

// Status vector - top 4 bits only
#define  SMB_MTSTA      0xE0           // (MT) start transmitted
#define  SMB_MTDB       0xC0           // (MT) data byte transmitted
#define  SMB_MRDB       0x80           // (MR) data byte received
// End status vector definition

#define  NUM_BYTES_WR   3              // Number of bytes to write
                                       // Master -> Slave
#define  NUM_BYTES_RD   3              // Number of bytes to read

extern U8 temp;

extern U8 TARGET;                             // Target SMBus slave address
                                       // Master <- Slave
extern U8 SMB_DATA_IN;                        // Global holder for SMBus data
                                       // All receive data is written here
extern U8 SMB_DATA_OUT;                       // Global holder for SMBus data.
                                       // All transmit data is read from here
SBIT (SDA, SFR_P2, 0);                 // SMBus on P2.0
SBIT (SCL, SFR_P2, 1);                 // and P2.1

//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------

void SMBUS0_Init(void);
void TIMER0_Init(void);
void TIMER3_Init(void);
void PORT_Init(void);
void Init_sys(void);

INTERRUPT_PROTO (TIMER3_ISR, INTERRUPT_TIMER3);
INTERRUPT_PROTO (SMBUS0_ISR, INTERRUPT_SMBUS0);

void SMB_Write (void);
void SMB_Read (void);
void T0_Waitms (U8 ms);

#define Add2_Slave  0x30   //read +1
#define Add3_Slave  0x34

#define WR_RDAC   	   0x00
#define WR_EEPROM	   0x20
#define WPROTECT	   0x40    //act or deact decide by wp bit
#define RDAC2EEPROM    0xC0
#define EEPROM2RDAC    0xA0
#define R_TLERANCE	   0x3E
#define R_TLERANCE_DEC 0x3F

#endif
