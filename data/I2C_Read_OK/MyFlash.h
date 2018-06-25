#include <compiler_defs.h>

//-----------------------------------------------------------------------------
// Open Header #define
//-----------------------------------------------------------------------------

#ifndef _F500_FLASHPRIMITIVES_H_
#define _F500_FLASHPRIMITIVES_H_

//-----------------------------------------------------------------------------
// Structures, Unions, Enumerations, and Type Definitions
//-----------------------------------------------------------------------------

typedef U16 FLADDR;

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

#ifndef FLASH_PAGESIZE
#define FLASH_PAGESIZE 512
#endif

#ifndef FLASH_TEMP
//#define FLASH_TEMP 0xF800L             // For 64K Flash devices
#define FLASH_TEMP 0x7C00L           // For 32K Flash devices
#endif

#ifndef FLASH_LAST
//#define FLASH_LAST 0xFA00L             // For 64K Flash devices
#define FLASH_LAST 0x7E00L           // For 32K Flash devices
#endif

//-----------------------------------------------------------------------------
// Exported Function Prototypes
//-----------------------------------------------------------------------------

void   FLASH_ByteWrite (FLADDR addr, U8 byte);
U8     FLASH_ByteRead  (FLADDR addr);
void   FLASH_PageErase (FLADDR addr);

//-----------------------------------------------------------------------------
// Close Header #define
//-----------------------------------------------------------------------------
#endif    
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------