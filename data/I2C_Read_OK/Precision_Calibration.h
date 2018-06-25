#include "compiler_defs.h"
#include "C8051F500_defs.h"  

#ifndef _PRECISION_MODIFICATION_H_
#define _PRECISION_MODIFICATION_H_
#endif

#ifdef _PRECISION_MODIFICATION_H_

F32 Angle_Conversion(S8 angle);
void Data_Capture(U8 angle1,U8 angle2,U16 mv);
void Data_Capture_TC(U8 temp1,U8 temp2,U16 mv_x,U16 mv_y);
//void Data_Capture_Y(U8 angley);
F32 Para_A(U16 adc0,U16 adc1,F32 angle0,F32 angle1);
F32 Para_K(U16 adc0,U16 adc1,F32 angle0,F32 angle1);
F32 Angle_Calculate(U16 mv,U8 xy);
void Para_Calculate(U8 xy);
F32 Tc_Para_compensation(U8 xy);
#endif
