/*--------------------------------文*件*信*息-----------------------------
* 文件名：  Sub.c
* 版　本：  v1.0
* 描  述：  100T双轴 整合后的版本
* 创建人：  
* 日  期：  
--------------------------------------------------------------------------
*当前版本:	v1.0
*修 改 人:
*日　  期:
----------------------------------修改履历--------------------------------
1、
2、
3、
4、
------------------------------------------------------------------------*/
#define   __SUB_C__
#include  "_Include.h"
//***********************************************************************/
void Sub_16SBufSwitch (int16s* buf,int8u i,int8u j);

#if 0
//***********************************************************************/
// *功    能：
// *入    口：
// *出    口：
// *备    注：
// *函数性质：16有符号位转BCD 值存DisBuf数组，后将BCD存于发送缓冲区
//***********************************************************************/
void Comm_PutInt16s (int16s val)
{
	Sub_Int16s2Str(DispBuf,val);
	Comm_PutStr((int8u*)DispBuf,6);
}
//***********************************************************************/
// *功    能：
// *入    口：
// *出    口：
// *备    注：
// *函数性质：16无符号位转BCD 值存DisBuf数组，后将BCD存于发送缓冲区
//***********************************************************************/
void Comm_PutInt16u (int16u val)
{
	Sub_Int16u2Str(DispBuf,val);
	Comm_PutStr((int8u*)DispBuf,5);
}
//***********************************************************************/
// *功    能：
// *入    口：
// *出    口：
// *备    注：
// *函数性质：8位无符号位转BCD 值存DisBuf数组，后将BCD存于发送缓冲区
//***********************************************************************/
void Comm_PutInt8u (int8u val)
{
	Sub_Int8u2Str(DispBuf,val);
	Comm_PutStr((int8u*)DispBuf,3);
}
#endif
//***********************************************************************/
//***********************************************************************/
// *功    能：
// *入    口：
// *出    口：
// *备    注：
// *函数性质：将回车换行的ASCII值存TX缓冲区
//***********************************************************************/
void Comm_PutNewLine (void)
{
	Comm_PutChar(0x0D);
	Comm_PutChar(0x0A);
}
//***********************************************************************/
// *功    能：
// *入    口：
// *出    口：
// *备    注：
// *函数性质：Send "ok"
//***********************************************************************/
void Sub_SendOk (void)
{	
	char* str={",OK"};
	Comm_PutStr((int8u*)str,3);
	Comm_PutNewLine();
	Comm_SendSta();
}
//***********************************************************************/
void Sub_SendErr (void)
{	char* str={"ERR"};
	
	
	Comm_PutStr((int8u*)str,3);
	Comm_PutNewLine();
	Comm_SendSta();
}

//***********************************************************************/
//int8u Sub_Str2Int16s (int16s *val,int8u* str)
//{	int16u temp;
//	if(FALSE==Sub_Str2Int16u(&temp,&str[1]))return (FALSE);
//	
//	if(str[0]=='+')
//	{	*val = temp;
//		return TRUE;
//	}
//	else if(str[0]=='-')
//	{	*val = -temp;
//		return TRUE;
//	}
//	return FALSE;
//}
//***********************************************************************/
//***********************************************************************/
int8u Sub_Str2Int8u (int8u* str)
{	int8u xdata val;	
	
	if((str[0]<'0')||(str[0]>'9'))return(100);
	if((str[1]<'0')||(str[1]>'9'))return(100);
	if((str[2]<'0')||(str[1]>'9'))return(100);
	val=(str[0]-'0')*100+(str[1]-'0')*10+(str[2]-'0');
	return  val;
}
//***********************************************************************/


//***********************************************************************/
void Sub_Int8u2Str (char* s,int8u val)
{
	s[0] = val/100+'0';
	val  = val%100;
	s[1] = val/10+'0';
	s[2] = val%10+'0';
}

 //HXL 12/8/28 
//***********************************************************************/
