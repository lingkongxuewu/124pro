/*--------------------------------��*��*��*Ϣ-----------------------------
* �ļ�����  Time.h
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
#include	"_Type.h"
//***********************************************************************/
#ifndef __TIMER_H__

	#define __TIMER_H__
	/*-----�궨��---------------------*/
	/*-----�ṹ���������Ͷ���---------*/
	/*-----����������ȣ�����---------*/
	/*-----��������-------------------*/
	void Timer2_Init (void);
	void Timer3_Init (void);
	void Timer2_TaskInIsr (void);
	void Timer2_TaskInMain (void);
	void TIMER1_Init (void);
	
#endif
/*-----------------------------------*/
#ifdef   __TIMER_C__
#define  TIMER_EXT
#else
#define	 TIMER_EXT  extern
#endif
/*-------------��������--------------*/

TIMER_EXT   xdata int16u MainTime4Cnt;
//  TIMER_EXT   xdata  int32u  buff;

//***********************************************************************/