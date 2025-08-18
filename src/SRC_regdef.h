/* 
 * File:   SRC_regdef.h
 * Author: Benjamin
 *
 * Created on 26 July 2025, 19:28
 */

#ifndef SRC_REGDEF_H
#define	SRC_REGDEF_H

#include "types.h"

typedef struct sOSCCONH_Bits
{
    uint8 NOSC     :3;
    uint8          :1;
    uint8 COSC     :3;
    uint8          :1;
} dtOSCCONH_Bits;

typedef struct sOSCCONL_Bits
{
    uint8 OSWEN    :1;
    uint8          :2;
    uint8 CF       :1;
    uint8          :1;
    uint8 LOCK     :1;
    uint8 IOLOCK   :1;
    uint8 CLKLOCK  :1;
} dtOSCCONL_Bits;


typedef struct sCLKDIV_Bits
{
    uint16 PLLPRE   :5;
    uint16          :1;
    uint16 PLLPOST  :2;
    uint16 FRCDIV   :3;
    uint16 DOZEN    :1;
    uint16 DOZE     :3;
    uint16 ROI      :1;
} dtCLKDIV_Bits;

typedef struct sPLLFBD_Bits
{
    uint16 PLLDIV   :9;
    uint16          :7;
} dtPLLFBD_Bits;

typedef union uOSCCONH
{
    uint8 U;
    int8 I;
    dtOSCCONH_Bits B;
} dtOSCCONH;

typedef union uOSCCONL
{
    uint8 U;
    int8 I;
    dtOSCCONL_Bits B;
} dtOSCCONL;

typedef union uCLKDIV
{
    uint16 U;
    int16 I;
    dtCLKDIV_Bits B;
} dtCLKDIV;

typedef union uPLLFBD
{
    uint16 U;
    int16 I;
    dtPLLFBD_Bits B;
} dtPLLFBD;

typedef struct sSRC
{
    uint16      RCON;
    dtOSCCONL    OSCCONL;
    dtOSCCONH    OSCCONH;
    dtCLKDIV    CLKDIV;
    dtPLLFBD    PLLFBD;
    uint16      OSCTUN;
    uint16 :16;
    uint16      LFSR;
    uint16      REFOCON;
    uint16      ACLKCON;
} dtSRC;

#define SRC ((dtSRC*)0x0740)

#endif	/* SRC_REGDEF_H */

