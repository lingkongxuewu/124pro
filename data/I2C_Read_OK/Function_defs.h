#ifndef _FUNCTION_DEFS_H_
#define _FUNCTION_DEFS_H_
#endif

#ifdef _FUNCTION_DEFS_H_

void Delay(U8 time);

U8 ReadI2Cbyte(void);
void WriteI2Cbyte(U8 I2C_data);
void I2C_Stop(void);
void I2C_Start(void);
void I2C_WaitACK(void);
void I2C_SDA_IN(void);
void I2C_SDA_OUT(void);
#endif
