#include "Precision_Calibration.h"   
     
#include "parameter_defs.h"
#include "Function_defs.h"
#include "Interrupt_ISR.h"
#include "MyFlash.h"
#include "stdio.h"
#include "Mcu_Init.h"
#include "math.h"

F32 Angle_Conversion(S8 angle)
{
	F32 arc_angle;
	arc_angle = (PI*angle)/180;
	return arc_angle;	
}

void Data_Capture(U8 angle1,U8 angle2,U16 mv)
{
	static U8 bi=38,by=0;
	Para_Set_Buffer[bi]=mv&0xff;
	Para_Set_Buffer[bi+1]=mv>>8;
	Para_Set_Buffer[bi+2]=angle1;
	Para_Set_Buffer[bi+3]=angle2;
	bi+=4;
	by++;
	Cal_Count=by;
	Para_Set_Buffer[36]= Cal_Count;
//	printf("%d\n",(U16)Para_Set_Buffer[33]);
}


void Data_Capture_TC(U8 temp1,U8 temp2,U16 mv_x,U16 mv_y)
{
	U8 bi;
	static U8 by=0;
	bi = 38+Para_Set_Buffer[36]*4+Tc_Count*6;
	Para_Set_Buffer[bi]=mv_x&0xff;
	Para_Set_Buffer[bi+1]=mv_x>>8;
	Para_Set_Buffer[bi+2]=mv_y&0xff;
	Para_Set_Buffer[bi+3]=mv_y>>8;
	Para_Set_Buffer[bi+4]=temp1;
	Para_Set_Buffer[bi+5]=temp2;
	by++;
	Tc_Count=by;
	Para_Set_Buffer[37]= Tc_Count;
//	printf("%d\n",(U16)Para_Set_Buffer[33]);
}

F32 Angle_Calculate(U16 mv,U8 xy)
{
	F32 xdata ang;
	U8 xdata i;
	if((Para_Set_Buffer[33] & 0x02)==0x2)
	{
 		mv = (U16)(mv-Tc_Para_compensation(xy)*(Temperature-Tc_Buffer[0]));
	//	printf("%d\t%f\n",(U16)mv,Tc_Para_compensation(xy));
	}
	
	if(mv>=Angle_Buffer[xy][0])
	{
		i=0;
		while(1)
		{
			if(mv>Angle_Buffer[xy][i+1])
			{
				if(i ==((Para_Set_Buffer[36]/2-1)/2-1))
				{
					mv =Angle_Buffer[xy][i+1];
					ang = asin((mv-a[xy][i])*k[xy][i]);
					Sensor_Error = 1;
					break;
				}
				if(i<((Para_Set_Buffer[36]/2-1)/2-1))
					i++;
			}
			else
			{	
				ang = asin((mv-a[xy][i])*k[xy][i]);
				Sensor_Error = 0;
				break;
			}

		}
	}
	else
	{
		i=(Para_Set_Buffer[36]/2-1)/2;
		while(1)
		{
			if(mv<Angle_Buffer[xy][i+1])
			{
				if(i ==((Para_Set_Buffer[36]/2-2)))
				{
					mv = Angle_Buffer[xy][i+1];
					ang = asin((mv-a[xy][i])*k[xy][i]);
					Sensor_Error = 1;
					break;
				}
				if(i<(Para_Set_Buffer[36]/2-2))
					i++;
			}
			else
			{	
				ang = asin((mv-a[xy][i])*k[xy][i]);
				Sensor_Error = 0;
				break;
			}
		}
	}

	switch(xy)
	{
		case 0:
			ang = ang*18000.0/PI - X_Offset;
		break;
		case 1:
			ang = ang*18000.0/PI - Y_Offset;
		break;
	}
	if(ang< 0)
	{
		switch(xy)
		{
			case 0:
				Neg_X = 1;
			break;
			case 1:
				Neg_Y = 1;
			break;
		}
	}
	return ang;
}

F32 Para_A(U16 adc0,U16 adc1,F32 angle0,F32 angle1)
{
	F32 a;
	a = ((F32)adc0*sin(Angle_Conversion(angle1))-(F32)adc1*sin(Angle_Conversion(angle0)))
	/(sin(Angle_Conversion(angle1))-sin(Angle_Conversion(angle0)));
	return a;
}

F32 Para_K(U16 adc0,U16 adc1,F32 angle0,F32 angle1)
{
	F32 k;
	k = sin(Angle_Conversion(angle1))/((F32)adc1-Para_A(adc0,adc1,angle0,angle1));
	return k;
}

void Para_Calculate(U8 xy)
{
	U8 i;
	for(i=0;i<(Para_Set_Buffer[36]/2-1);i++)
	{
		if(i==(Para_Set_Buffer[36]/2-1)/2)
		{
			a[xy][i] = Para_A(Angle_Buffer[xy][0],Angle_Buffer[xy][i+1],Cal_Angle[xy][0],Cal_Angle[xy][i+1]);
			k[xy][i] = Para_K(Angle_Buffer[xy][0],Angle_Buffer[xy][i+1],Cal_Angle[xy][0],Cal_Angle[xy][i+1]);
		}
		else
		{
			a[xy][i] = Para_A(Angle_Buffer[xy][i],Angle_Buffer[xy][i+1],Cal_Angle[xy][i],Cal_Angle[xy][i+1]);
			k[xy][i] = Para_K(Angle_Buffer[xy][i],Angle_Buffer[xy][i+1],Cal_Angle[xy][i],Cal_Angle[xy][i+1]);
		}
	}
}

F32 Tc_Para_compensation(U8 xy)
{
	F32 xdata k;
	if(Temperature>=Tc_Buffer[0])
		k=((F32)Angle_Tc_Buffer[xy][1]-(F32)Angle_Tc_Buffer[xy][0])/((F32)Tc_Buffer[1]-(F32)Tc_Buffer[0]);
	else
		k=((F32)Angle_Tc_Buffer[xy][2]-(F32)Angle_Tc_Buffer[xy][0])/((F32)Tc_Buffer[2]-(F32)Tc_Buffer[0]);
	return k;
}
