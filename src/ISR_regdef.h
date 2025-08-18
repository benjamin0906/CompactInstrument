/* 
 * File:   ISR_regdef.h
 * Author: Benjamin
 *
 * Created on 26 July 2025, 14:07
 */

#ifndef ISR_REGDEF_H
#define	ISR_REGDEF_H

#include "types.h"

typedef struct sINTCON2_Bits
{
    uint16 INT0EP   :1;
    uint16 INT1EP   :1;
    uint16 INT2EP   :1;
    uint16          :1;
    uint16 INT4EP   :1;
    uint16          :3;
    uint16 AIVTEN   :1;
    uint16          :4;
    uint16 SWTRAP   :1;
    uint16 DISI     :1;
    uint16 GIE      :1;
} dtINTCON2_Bits;

typedef union uINTCON2
{
    uint16 U;
    int16 I;
    dtINTCON2_Bits B;
} dtINTCON2;

typedef struct sISR
{
    uint16 IFS[12];
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 IEC[12];
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 IPC[46];
    uint16 :16;
    uint16 :16;
    uint16 :16;//a0
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 :16;//b0
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 INTCON1;//c0
    dtINTCON2 INTCON2;
    uint16 INTCON3;
    uint16 INTCON4;
    uint16 INTTREG;
} dtISR;

#define ISR ((dtISR*)0x0800)

#endif	/* ISR_REGDEF_H */

