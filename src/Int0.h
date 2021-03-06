
/*************************************************************************************************
* 文件名：	Int0.h
* 版　本：	v1.0
* 描  述：
* 创建人：	孙娜
* 创建日期：2010-5-21 16:45

*************************************************************************************************/

/***********************************************************************/
#include	"_Type.h"
/***********************************************************************/

#ifndef __INT0_H__
	#define __INT0_H__

/*************************宏定义****************************************/

/*************************函数声明**************************************/
	void Int0_Init(void);
	void Int0_Enable(void);
	void Int0_Disable(void);
#endif

/*-----------------------------------*/
#ifdef   __INT0_C__
#define  INT0_EXT
#else
#define	 INT0_EXT  extern
#endif	