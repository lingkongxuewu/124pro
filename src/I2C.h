#ifndef _I2C_H_
#define _I2C_H_
	
#include "_Type.h"
#include "delay.h"
#include <compiler_defs.h>
#include <c8051F500_defs.h>


void IIC_S_2(void);
void IIC_P_2(void);
int8u WaitACK_2(void);
int8u IIC_Read_2(int8u add,int8u order);
void W_Add_Ins_2(int8u add,int8u order);
void IIC_Write_2(int8u add,int8u order,int8u dat);
void IIC_StorOrRestor_2(int8u add,int8u order);

void IIC_S_3(void);
void IIC_P_3(void);
int8u WaitACK_3(void);
int8u IIC_Read_3(int8u add,int8u order);
void W_Add_Ins_3(int8u add,int8u order);
void IIC_Write_3(int8u add,int8u order,int8u dat);
void IIC_StorOrRestor_3(int8u add,int8u order);


#define Add2_Slave  0x30   //read +1
#define Add3_Slave  0x34

#define WR_RDAC   	   0x00
#define WR_EEPROM	   0x20
#define WPROTECT	   0x40    //act or deact decide by wp bit
#define RDAC2EEPROM    0xC0
#define EEPROM2RDAC    0xA0
#define R_TLERANCE	   0x3E
#define R_TLERANCE_DEC 0x3F

void IIC_S(void);

	sbit I2C_SDA2 = P2^1;  
	sbit I2C_SCL2 = P2^0;
	sbit I2C_SDA3 = P2^2;  
	sbit I2C_SCL3 = P2^3; 

#endif