#ifndef PARAMETER_DEFS_H
#define PARAMETER_DEFS_H

#include "C8051F500_defs.h"            // SFR declarations
//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------
#define SYSCLK       			12000000         	// System clock speed in Hz
#define BAUDRATE      			115200           	// Baud rate of UART in bps
#define MESSAGE_OBJECTS    		32          		// Number of message objects to use Range is 1-32
#define MESSAGE_SIZE        	8          			// Size in bytes of each CAN messag Range is 1-8
#define SHORT					1
#define MIDDLE					2
#define LONG					3
#define READ					1
#define WRITE					2
//-----------------------------------------------------------------------------
// Parameter_Setting
//-----------------------------------------------------------------------------
#define REQUEST_DATA			0x00
#define RESET					0x01
#define R_CYCLE_TIME			0x11
#define R_CYCLE_MODE			0x12
#define R_REQUEST_POS_ID		0x13
#define R_REPLY_POS_ID			0x14
#define R_CYCLE_POS_ID          0x15
#define R_SET_PARAMETER_ID		0x16
#define R_REPLY_PARAMETER_ID	0x17
#define	R_BAUD_RATE				0x18
#define R_FLOAT_AV				0x19
#define R_ZERO_OFFSET			0x1A
#define	R_ID_MODE				0x1B
#define W_CYCLE_TIME			0x21
#define W_CYCLE_MODE			0x22
#define W_REQUEST_POS_ID		0x23
#define W_REPLY_POS_ID			0x24
#define W_CYCLE_POS_ID          0x25
#define W_SET_PARAMETER_ID      0x26
#define W_REPLY_PARAMETER_ID    0x27
#define	W_BAUD_RATE             0x28
#define W_FLOAT_AV              0x29
#define W_ZERO_OFFSET           0x2A
#define	W_ID_MODE				0x2B
#define CYCLE_DATA				0x30
#define	DEFAULT_SET				0x40
#define CALIBRATION_MODE		0x88

//-----------------------------------------------------------------------------
// CanBus_BaudRate
//-----------------------------------------------------------------------------
//#define _10K  					0
#define _20K						0
#define _50K						1
#define _100K					2
#define _125K					3
#define	_250K					4
#define _500K					5
#define	_800K					6
#define _1000K					7

//-----------------------------------------------------------------------------
// Frame_Setting
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Bit Definition Masks
//-----------------------------------------------------------------------------
#define BOff  					0x80                     // Busoff Status
#define EWarn 					0x40                     // Warning Status
#define EPass 					0x20                     // Error Passive
#define RxOk  					0x10                     // Receive Message Successfully
#define TxOk  					0x08                     // Transmitted Message Successfully
#define LEC   					0x07                     // Last Error Code

//-----------------------------------------------------------------------------
// Pin Definitions
//-----------------------------------------------------------------------------
sbit 	LED1 					= P2^7;
sbit 	LED2 					= P2^6;
sbit 	LED3					= P2^5;
sbit 	LED4 					= P2^4;
sbit 	I2C_SCL					= P1^4;
sbit    SPI_MISO				= P2^1;
sbit    SPI_MOSI				= P2^2;
sbit    I2C_SDA			    	= P1^5;
sbit    dd						= P1^7;

#define FSC 						0//(CAN0IF1DA1&0xff)
#define DATA0					1//(CAN0IF1DA1>>8)
#define DATA1					2//(CAN0IF1DA2&0xff)
#define DATA2					3//(CAN0IF1DA2>>8)
#define DATA3					4//(CAN0IF1DB1&0xff)
#define DATA4					5//(CAN0IF1DB1>>8)
#define DATA5					6//(CAN0IF1DB2&0xff)
#define DATA6					7//(CAN0IF1DB2>>8)

#define PARAMETER_SET_ID		1
#define PARAMETER_REPLY_ID		2
#define POSITION_REQUEST_ID		3
#define POSITION_REPLY_ID		4
#define CYCLIC_POSITION_ID		5
#define CALIBRATION_ID			6
#define CALIBRATION_REPLY_ID	7

#define PARAMETER_SET			1
#define POSITION_REQUEST		2
#define CALIBARTION				3
#define PARAMETER_REPLY			4
#define POSITION_REPLY			5
#define CYCLIC_POSITION			6
#define CALIBRATION_REPLY		7



//-----------------------------------------------------------------------------
// Buffer Definitions
//-----------------------------------------------------------------------------
#define DEFUALT					0
#define	BAUD					1
#define AV						2
#define CYCLE_TIME				3
#define	TIME_MODE				5
#define	ZERO_POINT				6
#define REQ_POS_ID				8
#define REP_POS_ID				12
#define CYCLE_POS_ID            	16
#define SET_PARA_ID				20
#define	REY_PARA_ID			24
#define	TRANS_ID				28

//-----------------------------------------------------------------------------
// Angle Definitions
//-----------------------------------------------------------------------------
#define ANGLE0					0
#define ANGLE5					1
#define ANGLE10					2
#define ANGLE15					3
#define ANGLE30					4
#define	M_ANGLE5				5
#define	M_ANGLE10				6
#define	M_ANGLE15				7
#define M_ANGLE30				8
#define PI						3.1415926
#endif
