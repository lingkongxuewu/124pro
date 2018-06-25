
//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
bit CAN_ERROR = 0;                                             
UU64 xdata Rx_Data;
U16 xdata Count,Counter;
U8 xdata TX_OK,TX_Reply;
UU32 xdata New_Data;
U16 xdata Can_Receive_Data[4][32];
U8 xdata Para_Set_Buffer[255];
U8 xdata Time_Mode;
U16 xdata Cycle_Time_Value;
U16 xdata Angle_Value;
U16 xdata mV_X,mV_Y;                             // Measured voltage in mV
U8  xdata X_Value1,X_Value2,Y_Value1,Y_Value2;
S16 xdata X_Value,Y_Value;
U8 xdata Reply_flag;
U8 xdata Set_Para_flag;
U8 xdata Reply_Para_Frame[8];
U8 xdata Reply_Para_flag;
U8 xdata Load_Default_flag;
U16 xdata Temperature;
U8 xdata Temp1,Temp2;
U16 xdata Angle_Buffer[2][25];
U8 xdata Calibrate_flag,Calibrate_Enter;
F32 xdata a[2][24],k[2][24],Power;
U8 xdata Neg_X,Neg_Y;
F32 xdata Cal_Angle[2][25];
U8 xdata Cal_Count;
U8 xdata Angle_1,Angle_2,Dir_XY;
F32 xdata X_Offset,Y_Offset;
U8 xdata Reset_Flag;
U8 xdata Sensor_Error;
U8 xdata Flash_b[33];
U16 xdata tf0,tf1,tf2;
U32 xdata Power_sum;
U8 xdata Tc_Enter,Tc_Count;
U16 xdata Angle_Tc_Buffer[2][3];
S16 xdata Tc_Buffer[3];
U16 xdata Power_buffer,Power_saved;
U8 xdata Power_Enter,Compen_State;
//U8 xdata Calibrate_State;
//U8 xdata Flash_Buffer[255];
