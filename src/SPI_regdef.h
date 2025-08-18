/* 
 * File:   SPI_regdef.h
 * Author: Benjamin
 *
 * Created on 28 July 2025, 13:05
 */

#ifndef SPI_REGDEF_H
#define	SPI_REGDEF_H

#include "types.h"

typedef struct sSPIxSTAT_Bits
{
    uint16 SPIRBF   :1;
    uint16 SPITBF   :1;
    uint16 SISEL    :3;
    uint16 SRXMPT   :1;
    uint16 SPIROV   :1;
    uint16 SRMPT    :1;
    uint16 SPIBEC   :3;
    uint16          :2;
    uint16 SPISIDL  :1;
    uint16          :1;
    uint16 SPIEN    :1;
} dtSPIxSTAT_Bits;

typedef struct sSPIxCON1_Bits
{
    uint16 PPRE     :2;
    uint16 SPRE     :3;
    uint16 MSTEN    :1;
    uint16 CKP      :1;
    uint16 SSEN     :1;
    uint16 CKE      :1;
    uint16 SMP      :1;
    uint16 MODE16   :1;
    uint16 DISSDO   :1;
    uint16 DISSCK   :1;
    uint16          :1;
} dtSPIxCON1_Bits;

typedef struct sSPIxCON2_Bits
{
    uint16 SPIBEN   :1;
    uint16 FRMDLY   :1;
    uint16          :11;
    uint16 FRMPOL   :1;
    uint16 SPIFSD   :1;
    uint16 FRMEN    :1;
} dtSPIxCON2_Bits;

typedef union uSPIxSTAT
{
    uint16 U;
    int16 I;
    dtSPIxSTAT_Bits B;
} dtSPIxSTAT;

typedef union uSPIxCON1
{
    uint16 U;
    int16 I;
    dtSPIxCON1_Bits B;
} dtSPIxCON1;

typedef union uSPIxCON2
{
    uint16 U;
    int16 I;
    dtSPIxCON2_Bits B;
} dtSPIxCON2;

typedef struct sSPIx
{
    dtSPIxSTAT STAT;//0
    dtSPIxCON1 CON1;//2
    dtSPIxCON2 CON2;//4
    uint16 :16;//6
    uint16     BUF;//8
    uint16 :16;//a
    uint16 :16;//c
    uint16 :16;//e
    uint16 :16;//0
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 :16;
} dtSPIx;

#define SPI(x) ((dtSPIx*)0x0240)[x]

#endif	/* SPI_REGDEF_H */

