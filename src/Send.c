/*--------------------------------��*��*��*Ϣ-----------------------------
* �ļ�����  Send.c
* �桡����  v1.0
* ��  ����  100T˫�� ���Ϻ�İ汾
* �����ˣ�  
* ��  �ڣ�  
--------------------------------------------------------------------------
*��ǰ�汾:	v1.0
*�� �� ��:
*�ա�  ��:
----------------------------------�޸�����--------------------------------
1��
2��
3��
4��
------------------------------------------------------------------------*/
#define   __SEND_C__
#include  "_Include.h"

static void Send_RDeal ( char* buf,int8u n);
static void Send_CDeal ( char* buf,int8u n);
static void Send_SDeal ( char* buf,int8u n);



code int16u  SendSpeed[]={3990,943,462,298,223,168,146,119,103,85};
							// 1/4   1   2   3   4   5   6   7   8   9
							
    //                          0    1     2     3      4      5      6      7      8      9      
    code int32u Braud[10] = { 1200, 2400, 4800, 9600, 14400, 19200, 38400, 56000, 57600, 115200 };


//***********************************************************************/
// *��    �ܣ�
// *��    �ڣ�CommTimerʱ�䵽 ��CommRxFlag�н�����ɱ�־
// *��    �ڣ�
// *��    ע��
// *�������ʣ�
//***********************************************************************/
void Send_TimeProc (void)
{   static xdata int8u rx_buf[COMM_RX_BUF_SIZE];
    static int8u* ptr;
    static int8u xdata i;
    static int8u xdata err;
    static int8u xdata cmd;

//    if(COMM_TRAN==Comm_StateGet()) return;		 //COMM_TRAN==0��CommTimer����0����1����COM����CommTimer��û��0����0
    if(CommRxFlag==0)   return;					 //���ձ�־
    CommRxFlag = 0;
    ptr=rx_buf;									 
    for(i=0;i<COMM_RX_BUF_SIZE;i++)
    {   
		*ptr++=Comm_GetChar(&err);				  //�����ջ����������� ȡ������	rx_buf
        if(err==COMM_RX_EPT)					 //COMM_RX_EPT ==1	ȡ���־
        break;
    }
    if(i<3)
    {
        return;
    }
    if((0x0D!=rx_buf[i-2])||(0x0A!=rx_buf[i-1]))	 //�жϺ���λ�����Ƿ��ǻس�����
    return;


	cmd=rx_buf[0];
    switch(cmd)
    { 
	  case 'r': Send_RDeal(rx_buf,i);
                break;
      case 's': Send_SDeal(rx_buf,i);
                break;
    }
}
//***********************************************************************/
// *��    �ܣ�
// *��    �ڣ�
// *��    �ڣ�
// *��    ע��
// *�������ʣ�
//***********************************************************************/
static void Send_RDeal ( char* buf,int8u n)
{   
	int8u xdata temp1,temp2,dir;
	int8u xdata arr1[3],arr2[3];

	if(0==strncmp(buf,"rd rdac,",8))
	{
		if(n!=11)return;
		dir = buf[8];//Sub_Str2Int8u(&buf[12]);
		if(dir == 'x')
		{
			temp1=IIC_Read_2(Add2_Slave,WR_RDAC);
			temp2=IIC_Read_2(Add3_Slave,WR_RDAC);
			Comm_PutStr("x,RDAC2 ",8);
			Sub_Int8u2Str(arr1,temp1);
			Comm_PutStr(arr1,3);
			Comm_PutStr(",RDAC3 ",7);
			Sub_Int8u2Str(arr2,temp2);
			Comm_PutStr(arr2,3);
			Comm_PutChar(13);
			Comm_PutChar(10);
			Comm_SendSta();
		}
		else if(dir == 'y')
		{
			temp1=IIC_Read_3(Add2_Slave,WR_RDAC);
			temp2=IIC_Read_3(Add3_Slave,WR_RDAC);
			Comm_PutStr("y,RDAC2 ",8);
			Sub_Int8u2Str(arr1,temp1);
			Comm_PutStr(arr1,3);
			Comm_PutStr(",RDAC3 ",7);
			Sub_Int8u2Str(arr2,temp2);
			Comm_PutStr(arr2,3);
			Comm_PutChar(13);
			Comm_PutChar(10);
			Comm_SendSta();
		}	
	}
	else if(0==strncmp(buf,"rd m",4))
	{
		if(n!=6)return;
		Comm_PutStr("yang",4);
		Comm_PutChar(',');
		Comm_SendSta();
//		Comm_PutStr(&buf[5],2);
//        Sub_SendOk();
	}   
    else Sub_SendErr();
}
//***********************************************************************/
// *��    �ܣ�
// *��    �ڣ�
// *��    �ڣ�
// *��    ע��
// *�������ʣ�
//***********************************************************************/
static void Send_SDeal ( char* buf,int8u n)
{   
	int8u xdata data_8u,sla_add,direc;

	if(0==strncmp(buf,"set rdac,",9))
	{
		if(n!=20)return;
		sla_add=Sub_Str2Int8u(&buf[9]);
		data_8u=Sub_Str2Int8u(&buf[13]);
		direc=buf[17];//Sub_Str2Int8u(&buf[15]);
		if(direc == 'x')
		{
			if(sla_add==2)
			{
				IIC_Write_2(Add2_Slave,WR_RDAC,data_8u);
				IIC_StorOrRestor_2(Add2_Slave,RDAC2EEPROM);
				delay_ms(1);
//		        Comm_PutStr("set rdac 002,",13);
//				Comm_PutStr(&buf[13],3);
//		        Sub_SendOk();
			}
			else if(sla_add==3)
			{
				IIC_Write_2(Add3_Slave,WR_RDAC,data_8u);
				IIC_StorOrRestor_2(Add3_Slave,RDAC2EEPROM);
				delay_ms(1);
//		        Comm_PutStr("set rdac 003,",13);
//				Comm_PutStr(&buf[13],3);
//	       		Sub_SendOk();
			}
			else
			{
		        Comm_PutStr("enter error",11);
				Comm_SendSta();
			}
		}
		else if(direc == 'y')
		{
			if(sla_add==2)
			{
				IIC_Write_3(Add2_Slave,WR_RDAC,data_8u);
				IIC_StorOrRestor_3(Add2_Slave,RDAC2EEPROM);
				delay_ms(100);
//		        Comm_PutStr("set rdac 002,",13);
//				Comm_PutStr(&buf[13],3);
//		        Sub_SendOk();
			}
			else if(sla_add==3)
			{
				IIC_Write_3(Add3_Slave,WR_RDAC,data_8u);
				IIC_StorOrRestor_3(Add3_Slave,RDAC2EEPROM);
				delay_ms(100);
//		        Comm_PutStr("set rdac 003,",13);
//				Comm_PutStr(&buf[13],3);
//	       		Sub_SendOk();
			}
			else
			{
		        Comm_PutStr("enter error",11);
				Comm_SendSta();
			}
		}
		else
		{
			Comm_PutStr("enter direct error",18);
			Comm_SendSta();
		}

//		if(sla_add==2)
//		{
//			IIC_Write(Add2_Slave,WR_RDAC,data_8u);
//			IIC_StorOrRestor(Add2_Slave,RDAC2EEPROM);
//			delay_ms(100);
//	        Comm_PutStr("set rdac 2",10);
//	        Sub_SendOk();
//		}
//		else if(sla_add==3)
//		{
//			IIC_Write(Add3_Slave,WR_RDAC,data_8u);
//			IIC_StorOrRestor(Add3_Slave,RDAC2EEPROM);
//			delay_ms(100);
//	        Comm_PutStr("set rdac 3",10);
//       		Sub_SendOk();
//		}
//		else
//		{
//	        Comm_PutStr("enter error",11);
//			Comm_SendSta();
//		}

	}
}


//***********************************************************************/
