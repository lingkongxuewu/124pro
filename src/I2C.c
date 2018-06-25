#define _I2C_C_
#include "I2C.h"
#include "_include.h"


/*start condition*/
void IIC_S_2(void)
{
	I2C_SDA2=1;  Delay_IIC();
	I2C_SCL2=1;  Delay_IIC();
	I2C_SDA2=0;  Delay_IIC();
	I2C_SCL2=0;  Delay_IIC();
}

void IIC_S_3(void)
{
	I2C_SDA3=1;  Delay_IIC();
	I2C_SCL3=1;  Delay_IIC();
	I2C_SDA3=0;  Delay_IIC();
	I2C_SCL3=0;  Delay_IIC();
}

/*stop condition*/
void IIC_P_2(void)
{
	I2C_SCL2=0;  Delay_IIC();
	I2C_SDA2=0;  Delay_IIC();
	I2C_SCL2=1;  Delay_IIC();
	I2C_SDA2=1;  Delay_IIC();
}

void IIC_P_3(void)
{
	I2C_SCL3=0;  Delay_IIC();
	I2C_SDA3=0;  Delay_IIC();
	I2C_SCL3=1;  Delay_IIC();
	I2C_SDA3=1;  Delay_IIC();
}

//wait slove acknowledge
int8u WaitACK_2(void)
{
	int8u time = 0;
	I2C_SCL2 = 0;  Delay_IIC();
	I2C_SCL2 = 1;  Delay_IIC();
	while((I2C_SDA2==1)&&(time<1000))
	{
		time++;
	}
	if(time==100)	
	{
		IIC_P_2();
		return 0;
	}
	else
		return 1;
	I2C_SCL2 = 0;  Delay_IIC();
}

int8u WaitACK_3(void)
{
	int8u time = 0;
	I2C_SCL3 = 0;  Delay_IIC();
	I2C_SCL3 = 1;  Delay_IIC();
	while((I2C_SDA3==1)&&(time<1000))
	{
		time++;
	}
	if(time==100)	
	{
		IIC_P_3();
		return 0;
	}
	else
		return 1;
	I2C_SCL2 = 0;  Delay_IIC();
}



void W_Add_Ins_2(int8u add,int8u order)
{
	int8u i;

	IIC_S_2();
	for(i=0;i<8;i++)
	{
		I2C_SCL2 = 0;  Delay_IIC();
		if((add<<i)&0x80)
			I2C_SDA2 = 1;
		else
			I2C_SDA2 = 0;
		I2C_SCL2 = 1;  Delay_IIC();
	}
//	I2C_SDA2 = 1;  Delay_IIC();
	if(WaitACK_2()!=1)	return;		//time out,out of
    //write slave Add to bus
	for(i=0;i<8;i++)
	{
		I2C_SCL2 = 0;  Delay_IIC();
		if((order<<i)&0x80)
			I2C_SDA2 = 1;
		else
			I2C_SDA2 = 0;
		I2C_SCL2 = 1;  Delay_IIC();
	}
//	if(WaitACK()!=1)	return;		//time out,out of
}

void W_Add_Ins_3(int8u add,int8u order)
{
	int8u i;

	IIC_S_3();
	for(i=0;i<8;i++)
	{
		I2C_SCL3 = 0;  Delay_IIC();
		if((add<<i)&0x80)
			I2C_SDA3 = 1;
		else
			I2C_SDA3 = 0;
		I2C_SCL3 = 1;  Delay_IIC();
	}
//	I2C_SDA2 = 1;  Delay_IIC();
	if(WaitACK_3()!=1)	return;		//time out,out of
    //write slave Add to bus
	for(i=0;i<8;i++)
	{
		I2C_SCL3 = 0;  Delay_IIC();
		if((order<<i)&0x80)
			I2C_SDA3 = 1;
		else
			I2C_SDA3 = 0;
		I2C_SCL3 = 1;  Delay_IIC();
	}
//	if(WaitACK()!=1)	return;		//time out,out of
}

/*Read register through IIC*/
int8u IIC_Read_2(int8u add,int8u order)
{
	int8u i,temp;
	temp = 0;

	W_Add_Ins_2(add,order);
	if(WaitACK_2()!=1)	
	return 0;
	I2C_SCL2 = 0;  Delay_IIC();
	IIC_S_2();
	add++;
	for(i=0;i<8;i++)
	{
		I2C_SCL2 = 0;  Delay_IIC();
		if((add<<i)&0x80)
			I2C_SDA2 = 1;
		else
			I2C_SDA2 = 0;
		I2C_SCL2 = 1;  Delay_IIC();
	}
	if(WaitACK_2()!=1)	
	return 0;
	for(i=0;i<8;i++)
	{
		I2C_SCL2 = 0;  Delay_IIC();
		I2C_SCL2 = 1;  Delay_IIC();
		if(I2C_SDA2 == 1)
		temp|=(0x80>>i);
	}
	I2C_SCL2 = 0;  Delay_IIC();
	I2C_SDA2 = 1;  Delay_IIC();
	I2C_SCL2 = 1;  Delay_IIC();

	IIC_P_2();

	return temp;
}

int8u IIC_Read_3(int8u add,int8u order)
{
	int8u i,temp;
	temp = 0;

	W_Add_Ins_3(add,order);
	if(WaitACK_3()!=1)	
	return 0;
	I2C_SCL3 = 0;  Delay_IIC();
	IIC_S_3();
	add++;
	for(i=0;i<8;i++)
	{
		I2C_SCL3 = 0;  Delay_IIC();
		if((add<<i)&0x80)
			I2C_SDA3 = 1;
		else
			I2C_SDA3 = 0;
		I2C_SCL3 = 1;  Delay_IIC();
	}
	if(WaitACK_3()!=1)	
	return 0;
	for(i=0;i<8;i++)
	{
		I2C_SCL3 = 0;  Delay_IIC();
		I2C_SCL3 = 1;  Delay_IIC();
		if(I2C_SDA3 == 1)
		temp|=(0x80>>i);
	}
	I2C_SCL3 = 0;  Delay_IIC();
	I2C_SDA3 = 1;  Delay_IIC();
	I2C_SCL3 = 1;  Delay_IIC();

	IIC_P_3();

	return temp;
}

void IIC_Write_2(int8u add,int8u order,int8u dat)
{
	int8u i;
	W_Add_Ins_2(add,order);
	if(WaitACK_2()!=1)	
	return;
	I2C_SCL2 = 0;  Delay_IIC();
	for(i=0;i<8;i++)
	{
		I2C_SCL2 = 0;  Delay_IIC();
		if((dat<<i)&0x80)
			I2C_SDA2 = 1;
		else
			I2C_SDA2 = 0;
		I2C_SCL2 = 1;  Delay_IIC();
	}
	if(WaitACK_2()!=1)	
	return;
	IIC_P_2();
}

void IIC_Write_3(int8u add,int8u order,int8u dat)
{
	int8u i;
	W_Add_Ins_3(add,order);
	if(WaitACK_3()!=1)	
	return;
	I2C_SCL3 = 0;  Delay_IIC();
	for(i=0;i<8;i++)
	{
		I2C_SCL3 = 0;  Delay_IIC();
		if((dat<<i)&0x80)
			I2C_SDA3 = 1;
		else
			I2C_SDA3 = 0;
		I2C_SCL3 = 1;  Delay_IIC();
	}
	if(WaitACK_3()!=1)	
	return;
	IIC_P_3();
}

void IIC_StorOrRestor_2(int8u add,int8u order)
{
	W_Add_Ins_2(add,order);
	if(WaitACK_2()!=1)	
	return;
	IIC_P_2();
}

void IIC_StorOrRestor_3(int8u add,int8u order)
{
	W_Add_Ins_3(add,order);
	if(WaitACK_3()!=1)	
	return;
	IIC_P_3();
}


