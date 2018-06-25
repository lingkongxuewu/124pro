/* ***************************************************************
 * Copyright(R) 2008-2018,Sinocomopto Tech.Co.,Ltd.
 * File Name: sch9003_d02_drv.c
 * Author:Kent       Date:              Version:
 * Description:
   1.This Module is for motion sensor driver.
 * Function:

   Compile: ADS1.2
 * History:
 1,Version:       Date:           Author:Kent

 * *************************************************************/

#include "kal_release.h"
#include "custom_config.h"
#include "gpio_sw.h"
#include "drv_comm.h"
#include "sch9003_d02_drv.h"
#include "math.h"

#include "reg_base.h"

kal_uint8 abct_test_flag=0;

#ifdef MCU_104M
#define delay_long 1350
#define delay_short 1350
#else
#define delay_short 450
#define delay_long  450
#endif

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
void SCH9003_D02_Delay_us(kal_uint32 times)
{
	kal_uint32 delay1;
	kal_uint8 delay2;
	for(delay1=0;delay1<times;delay1++)
	for(delay2=0;delay2<4;delay2++){ }  // about 1us
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
void SCH9003_D02_Delay_10ms(void)
{
	kal_uint16 i;
	SCH9003_D02_Delay_us(10000);
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
void SCH9003_D02_Delay_100ms(void)
{
	kal_uint16 i;
	for(i=0;i<100;i++)
	{
		SCH9003_D02_Delay_10ms();
	}
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
void SCH9003_D02_Delay_500ms(void)
{
	kal_uint16 i;
	for(i=0;i<500;i++)
	{
		SCH9003_D02_Delay_10ms();
	}
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
void SCH9003_D02_I2C_Start(void)
{
   kal_int32 i;
   SET_I2C_DATA_OUTPUT();
   SET_I2C_DATA_HIGH();
   SET_I2C_CLK_HIGH(); for(i=0;i<delay_long;i++);
   SET_I2C_DATA_LOW(); for(i=0;i<delay_long;i++);
   SET_I2C_CLK_LOW();  for(i=0;i<delay_long;i++);
}


/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
void SCH9003_D02_I2C_Wait_Ack(void)
{
	kal_int32 i;
	kal_uint16 j=0;
	
	SET_I2C_DATA_INPUT();
	for(i=0;i<delay_long;i++);
	SET_I2C_CLK_HIGH();    for(i=0;i<delay_long;i++);
	while((GET_I2C_DATA_BIT()==0x01)&&(j<500))
	{j++;}
	SET_I2C_CLK_LOW();
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
void SCH9003_D02_I2C_Send_Ack(void)
{
	kal_int32 i;
	
	SET_I2C_DATA_OUTPUT();
	SET_I2C_DATA_LOW();   for(i=0;i<delay_long;i++);
	SET_I2C_CLK_HIGH();   for(i=0;i<delay_long;i++);
	SET_I2C_CLK_LOW();
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
void SCH9003_D02_I2C_Send_Nack(void)
{
	kal_int32 i;
	
	SET_I2C_DATA_OUTPUT();
	SET_I2C_DATA_HIGH();   for(i=0;i<delay_long;i++);
	SET_I2C_CLK_HIGH();    for(i=0;i<delay_long;i++);
	SET_I2C_CLK_LOW();
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
void SCH9003_D02_I2C_Send_Byte(kal_uint8 temp)
{
	kal_int32 i;
	kal_uint8 j;
	
	SET_I2C_DATA_OUTPUT();
	for(j=0;j<8;j++)
	{
		SET_I2C_CLK_LOW();   for(i=0;i<delay_long;i++);
		if((temp&0x80)==0x80)
		{
			SET_I2C_DATA_HIGH(); for(i=0;i<delay_long;i++);
		}
		else
		{
			SET_I2C_DATA_LOW();  for(i=0;i<delay_long;i++);
		}
		SET_I2C_CLK_HIGH();    for(i=0;i<delay_long;i++);
		temp<<=1;
	}
	SET_I2C_CLK_LOW();
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
kal_uint8 SCH9003_D02_I2C_Receive_Byte(void)
{
	kal_int32 i;
	kal_uint8 j;
	kal_uint8 temp=0;
	
	SET_I2C_DATA_INPUT();
	for(j=0;j<8;j++)
	{
		temp<<=1;
		SET_I2C_CLK_LOW();  for(i=0;i<delay_long;i++); for(i=0;i<delay_long;i++);
		SET_I2C_CLK_HIGH(); for(i=0;i<delay_long;i++);
		if(GET_I2C_DATA_BIT()==0x01)
		{
			temp|=0x01;
		}
	}
	SET_I2C_CLK_LOW();
	return(temp);
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
void SCH9003_D02_I2C_Stop(void)
{
	kal_int32 i;	
	SET_I2C_DATA_OUTPUT();
	SET_I2C_DATA_LOW();    for(i=0;i<delay_long;i++);
	SET_I2C_CLK_HIGH();    for(i=0;i<delay_long;i++);
	SET_I2C_DATA_HIGH();
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
void SCH9003_D02_Init(void)
{
	GPIO_ModeSetup(SCH9003_D02_SCK,0x00);
	GPIO_ModeSetup(SCH9003_D02_SDA,0x00);
	 
	SET_I2C_CLK_PULLDIS();
	SET_I2C_DATA_PULLDIS();
	
	SET_I2C_CLK_OUTPUT();
	SET_I2C_DATA_OUTPUT();
	 
	SET_I2C_CLK_HIGH();
	SET_I2C_DATA_HIGH();
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
void SCH9003_D02_Power_On(void)
{
	SCH9003_D02_I2C_Start();
	SCH9003_D02_I2C_Send_Byte(0x20);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Send_Byte(POWER_ON);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Stop();		
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
void SCH9003_D02_Power_Off(void)
{
	SCH9003_D02_I2C_Start();
	SCH9003_D02_I2C_Send_Byte(0x20);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Send_Byte(POWER_OFF);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Stop();
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
kal_int32 SCH9003_D02_Alti_Read(void)
{
	kal_int32 atli_tmp=0;
	kal_uint8 atli_buf[3]={0,0,0};
	
	SCH9003_D02_I2C_Start();
	SCH9003_D02_I2C_Send_Byte(0x20);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Send_Byte(READ_ALTI);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Stop();
	
	SCH9003_D02_Delay_100ms();
	
	SCH9003_D02_I2C_Start();
	SCH9003_D02_I2C_Send_Byte(0x21);
	SCH9003_D02_I2C_Wait_Ack();
	atli_buf[0] = SCH9003_D02_I2C_Receive_Byte();
	SCH9003_D02_I2C_Send_Ack();
	atli_buf[1] = SCH9003_D02_I2C_Receive_Byte();
	SCH9003_D02_I2C_Send_Ack();
	atli_buf[2] = SCH9003_D02_I2C_Receive_Byte();	
	SCH9003_D02_I2C_Send_Nack();
	SCH9003_D02_I2C_Stop();

	if(0x80&atli_buf[0])
	{
		atli_tmp=atli_buf[0]&0x7f;
		atli_tmp<<=8;
		atli_tmp|=atli_buf[1];
		atli_tmp<<=8;
		atli_tmp|=atli_buf[2];
		atli_tmp=-atli_tmp;
	}
	else
	{
		atli_tmp=atli_buf[0];
		atli_tmp<<=8;
		atli_tmp|=atli_buf[1];
		atli_tmp<<=8;
		atli_tmp|=atli_buf[2];
	}
	return atli_tmp;
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
void SCH9003_D02_SeaLevel_Write(kal_uint32 sea_level)
{
	kal_uint8 sea_level_buf[3]={0,0,0};
	
	sea_level_buf[2] = sea_level & 0xFF;
	sea_level >>= 8;
	sea_level_buf[1] = sea_level & 0xFF;
	sea_level >>= 8;
	sea_level_buf[0] = sea_level & 0xFF;
	
	SCH9003_D02_I2C_Start();
	SCH9003_D02_I2C_Send_Byte(0x20);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Send_Byte(SEALEVEL_WRITE);
	SCH9003_D02_I2C_Wait_Ack();
	
	SCH9003_D02_I2C_Send_Byte(sea_level_buf[0]);
	SCH9003_D02_I2C_Wait_Ack();

	SCH9003_D02_I2C_Send_Byte(sea_level_buf[1]);
	SCH9003_D02_I2C_Wait_Ack();

	SCH9003_D02_I2C_Send_Byte(sea_level_buf[2]);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Stop();
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
kal_int32 SCH9003_D02_Baro_Read(void)
{
	kal_int32 baro_tmp=0;
	kal_uint8 baro_buf[3]={0,0,0};
	
	SCH9003_D02_I2C_Start();
	SCH9003_D02_I2C_Send_Byte(0x20);
	SCH9003_D02_I2C_Wait_Ack();	
	SCH9003_D02_I2C_Send_Byte(BARO_READ);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Stop();
	
	SCH9003_D02_Delay_100ms();
	
	SCH9003_D02_I2C_Start();
	SCH9003_D02_I2C_Send_Byte(0x21);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_Delay_us(100);
	
	baro_buf[0] = SCH9003_D02_I2C_Receive_Byte();
	SCH9003_D02_I2C_Send_Ack();
	baro_buf[1] = SCH9003_D02_I2C_Receive_Byte();
	SCH9003_D02_I2C_Send_Ack();
	baro_buf[2] = SCH9003_D02_I2C_Receive_Byte();
	SCH9003_D02_I2C_Send_Nack();
	SCH9003_D02_I2C_Stop();
	
	baro_tmp |= baro_buf[0];
	baro_tmp <<= 8;
	baro_tmp |= baro_buf[1];
	baro_tmp <<= 8;
	baro_tmp |= baro_buf[2];
	
	return baro_tmp;
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
void SCH9003_D02_BaroOffset_Write(kal_int16 baro_offset)
{
	kal_uint8 baro_offset_buf[2]={0,0};
	if(baro_offset<0)
	{
		baro_offset=abs(baro_offset);
		baro_offset|=0x8000;
	}
	baro_offset_buf[1]=baro_offset&0xFF;
	baro_offset>>=8;
	baro_offset_buf[0]=baro_offset&0xFF;
	
	SCH9003_D02_I2C_Start();
	SCH9003_D02_I2C_Send_Byte(0x20);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Send_Byte(BARO_OFFSET_WRITE);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Send_Byte(baro_offset_buf[0]);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Send_Byte(baro_offset_buf[1]);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Stop();
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
kal_uint16 SCH9003_D02_Comp_Read(void)
{
	kal_uint16 comp_tmp=0;
	kal_uint8 comp_buf[2]={0,0};
	
	SCH9003_D02_I2C_Start();
	SCH9003_D02_I2C_Send_Byte(0x20);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Send_Byte(COMP_READ);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Stop();
	
	SCH9003_D02_Delay_100ms();
	
	SCH9003_D02_I2C_Start();
	SCH9003_D02_I2C_Send_Byte(0x21);
	SCH9003_D02_I2C_Wait_Ack();
	
	comp_buf[0] = SCH9003_D02_I2C_Receive_Byte();
	SCH9003_D02_I2C_Send_Ack();
	SCH9003_D02_Delay_us(150);
	comp_buf[1] = SCH9003_D02_I2C_Receive_Byte();
	SCH9003_D02_I2C_Send_Nack();
	SCH9003_D02_I2C_Stop();;
	
	comp_buf[0] &= 0x01;
	comp_tmp |= comp_buf[0];
	comp_tmp <<= 8;
	comp_tmp |= comp_buf[1];
	
	if((comp_tmp<180)&&(comp_tmp>=0))
	{
		comp_tmp=comp_tmp+180;
	}
	else if((comp_tmp<360)&&(comp_tmp>=180))
	{
		comp_tmp=comp_tmp-180;
	}
	
	return comp_tmp;
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
void SCH9003_D02_CompDecl_Write(kal_uint16 comp_decl)
{
	kal_uint8 decl_buf[2]={0,0};
	
	decl_buf[1] = comp_decl & 0xFF;
	comp_decl >>= 8;
	decl_buf[0] = comp_decl & 0xFF;
	
	SCH9003_D02_I2C_Start();
	SCH9003_D02_I2C_Send_Byte(0x20);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Send_Byte(DECL_WRITE);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Send_Byte(decl_buf[0]);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Send_Byte(decl_buf[1]);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Stop();
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
kal_uint16 SCH9003_D02_CompDecl_Read(void)
{
	kal_uint16 decl_tmp=0;
	kal_uint8  decl_buf[2]={0,0};
	
	SCH9003_D02_I2C_Start();
	SCH9003_D02_I2C_Send_Byte(0x20);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Send_Byte(DECL_READ);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Stop();

	SCH9003_D02_Delay_100ms();	
	
	SCH9003_D02_I2C_Start();
	SCH9003_D02_I2C_Send_Byte(0x21);
	SCH9003_D02_I2C_Wait_Ack();
	decl_buf[0] = SCH9003_D02_I2C_Receive_Byte();
	SCH9003_D02_I2C_Send_Ack();
	decl_buf[1] = SCH9003_D02_I2C_Receive_Byte();
	SCH9003_D02_I2C_Send_Nack();
	SCH9003_D02_I2C_Stop();

	decl_tmp |= decl_buf[0];
	decl_tmp <<= 8;
	decl_tmp |= decl_buf[1];
	  
	return decl_tmp;
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
void SCH9003_D02_CompCali_Enter(void)
{
	SCH9003_D02_I2C_Start();
	SCH9003_D02_I2C_Send_Byte(0x20);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Send_Byte(CALI_ENTER);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Stop();
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
void SCH9003_D02_CompCali_Exit(void)
{
	SCH9003_D02_I2C_Start();
	SCH9003_D02_I2C_Send_Byte(0x20);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Send_Byte(CALI_EXIT);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Stop();
}

/**************************************************************************
  Function:
  Description:
  Calls:
  Called by:
  Table Accessed:
  Table Undated:
  Input:
  Ouput:
  Return:
******************************************************************************/
kal_int16 SCH9003_D02_Temp_Read(void)
{
	kal_int16 temp_tmp=0;
	kal_uint8 temp_buf[2]={0,0};
	
	SCH9003_D02_I2C_Start();
	SCH9003_D02_I2C_Send_Byte(0x20);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Send_Byte(TEMP_READ);
	SCH9003_D02_I2C_Wait_Ack();
	SCH9003_D02_I2C_Stop();
	
	SCH9003_D02_Delay_100ms();
	
	SCH9003_D02_I2C_Start();
	SCH9003_D02_I2C_Send_Byte(0x21);
	SCH9003_D02_I2C_Wait_Ack();
	
	temp_buf[0] = SCH9003_D02_I2C_Receive_Byte();
	SCH9003_D02_I2C_Send_Ack();
	temp_buf[1] = SCH9003_D02_I2C_Receive_Byte();
	SCH9003_D02_I2C_Send_Nack();
	SCH9003_D02_I2C_Stop();
	
	if(0x80&temp_buf[0])
	{
		temp_buf[0]=temp_buf[0]&0x7f;
		temp_tmp |= temp_buf[0];
		temp_tmp <<= 8;
		temp_tmp |= temp_buf[1];
		temp_tmp=-temp_tmp;
	}
	else
	{
		temp_tmp|=temp_buf[0];
		temp_tmp<<=8;
		temp_tmp|=temp_buf[1];
	}
	return temp_tmp;
}

#if 1
void SCH9003_D02_Test(void)
{
	kal_int16 temp,comp;
	kal_int32 pres;
	kal_int16 atli_int=0;
	kal_uint8  atli_dec=0;
	static kal_uint16 p_flag=0;
	kal_uint16 i;
	
	if(++p_flag==7)
	{
		p_flag=0;
	}
	
	switch(p_flag)
	{
		case 0:
			SCH9003_D02_Init();
			SCH9003_D02_Power_On();
			kal_prompt_trace(MOD_TP_TASK,"SCH9003_D02_Power_On,p_flag=%d",p_flag);
			break;
		case 1:
			temp=SCH9003_D02_Temp_Read();
			kal_prompt_trace(MOD_TP_TASK,"Temp=%d",temp);
			kal_prompt_trace(MOD_TP_TASK,"p_flag=%d",p_flag);
			break;
		case 2:
			SCH9003_D02_Alti_Read(&atli_int,&atli_dec);
			kal_prompt_trace(MOD_TP_TASK,"Atli_Int=%d,Atli_Dec=%d",atli_int,atli_dec);
			kal_prompt_trace(MOD_TP_TASK,"p_flag=%d",p_flag);
			break;
		case 3:
			pres=SCH9003_D02_Baro_Read();
			kal_prompt_trace(MOD_TP_TASK,"perruse=%d",pres);
			kal_prompt_trace(MOD_TP_TASK,"p_flag=%d",p_flag);
			break;
		case 4:
			comp=SCH9003_D02_Comp_Read();
			kal_prompt_trace(MOD_TP_TASK,"compass=%d",comp);
			kal_prompt_trace(MOD_TP_TASK,"p_flag=%d",p_flag);
			break;
		case 5:
			temp=SCH9003_D02_Temp_Read();
			SCH9003_D02_Alti_Read(&atli_int,&atli_dec);
			pres=SCH9003_D02_Baro_Read();
			comp=SCH9003_D02_Comp_Read();
			kal_prompt_trace(MOD_TP_TASK,"Temp=%d,perruse=%d",temp,pres);
			kal_prompt_trace(MOD_TP_TASK,"Atli_Int=%d,Atli_Dec=%d",atli_int,atli_dec);
			kal_prompt_trace(MOD_TP_TASK,"compass=%d,p_flag=%d",comp,p_flag);
			break;
		case 6:
			SCH9003_D02_Power_Off();
			kal_prompt_trace(MOD_TP_TASK,"SCH9003_D02_Power_Off,p_flag=%d",p_flag);
			break;
		default:
			p_flag=0;
			break;
	}
}
#endif


