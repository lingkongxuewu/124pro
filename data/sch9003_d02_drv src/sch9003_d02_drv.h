/* ***************************************************************
 * Copyright(R) 2008-2018,Sinocomopto Tech.Co.,Ltd.
 * File Name: sch9003_d02_drv.h
 * Author:Kent       Date:2009-10-9 17:44:38              Version:
 * Description:

 * Function:

   Compile: ADS1.2
 * History:
 1,Version:       Date:2009-10-9 17:44:36           Author:Kent

 * *************************************************************/
#ifndef _SCH9003_D02_DRV_H
#define _SCH9003_D02_DRV_H

#define SET_I2C_CLK_PULLDIS()  GPIO_PullenSetup(SCH9003_D02_SCK,0)
#define SET_I2C_DATA_PULLDIS() GPIO_PullenSetup(SCH9003_D02_SDA,0)
#define SET_I2C_CLK_OUTPUT()   GPIO_InitIO(OUTPUT,SCH9003_D02_SCK)
#define SET_I2C_CLK_INPUT()      GPIO_InitIO(INPUT,SCH9003_D02_SCK)
#define SET_I2C_DATA_OUTPUT()  GPIO_InitIO(OUTPUT,SCH9003_D02_SDA)
#define SET_I2C_DATA_INPUT()   GPIO_InitIO(INPUT,SCH9003_D02_SDA)
#define SET_I2C_CLK_HIGH()     GPIO_WriteIO(1,SCH9003_D02_SCK)
#define SET_I2C_CLK_LOW()      GPIO_WriteIO(0,SCH9003_D02_SCK)
#define SET_I2C_DATA_HIGH()    GPIO_WriteIO(1,SCH9003_D02_SDA)
#define SET_I2C_DATA_LOW()     GPIO_WriteIO(0,SCH9003_D02_SDA)
#define GET_I2C_CLK_BIT()        GPIO_ReadIO(SCH9003_D02_SCK)
#define GET_I2C_DATA_BIT()     GPIO_ReadIO(SCH9003_D02_SDA)

#define POWER_ON          0x70
#define POWER_OFF         0x71
#define READ_ALTI         0xA0
#define SEALEVEL_WRITE    0xA1
#define BARO_READ         0xB0
#define BARO_OFFSET_WRITE 0xB1
#define COMP_READ         0xC0
#define DECL_WRITE        0xD0
#define DECL_READ         0xD1
#define CALI_ENTER        0xE0
#define CALI_EXIT         0xE5
#define TEMP_READ         0x80

void SCH9003_D02_Delay_us(kal_uint32 times);
void SCH9003_D02_Delay_10ms(void);
void SCH9003_D02_Delay_100ms(void);
void SCH9003_D02_Delay_500ms(void);

void SCH9003_D02_I2C_Start(void);
void SCH9003_D02_I2C_Wait_Ack(void);
void SCH9003_D02_I2C_Send_Ack(void);
void SCH9003_D02_I2C_Send_Nack(void);
void SCH9003_D02_I2C_Stop(void);
void SCH9003_D02_I2C_Send_Byte(kal_uint8 temp);
kal_uint8 SCH9003_D02_I2C_Receive_Byte(void);

void SCH9003_D02_Init(void);
void SCH9003_D02_Power_On(void);
void SCH9003_D02_Power_Off(void);
kal_int32 SCH9003_D02_Alti_Read(void);
void SCH9003_D02_SeaLevel_Write(kal_uint32 sea_level);
kal_int32 SCH9003_D02_Baro_Read(void);
void SCH9003_D02_BaroOffset_Write(kal_int16 baro_offset);
kal_uint16 SCH9003_D02_Comp_Read(void);
void SCH9003_D02_CompDecl_Write(kal_uint16 comp_decl);
kal_uint16 SCH9003_D02_CompDecl_Read(void);
void SCH9003_D02_CompCali_Exit(void);
kal_int16 SCH9003_D02_Temp_Read(void);

void SCH9003_D02_Test(void);

#endif
