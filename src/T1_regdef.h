/* 
 * File:   T1_regdef.h
 * Author: Benjamin
 *
 * Created on 26 July 2025, 15:14
 */

#ifndef T1_REGDEF_H
#define	T1_REGDEF_H

#include "types.h"

typedef struct sT1CON_Bits
{
    uint16          :1;
    uint16 TCS      :1;
    uint16 TSYNC    :1;
    uint16          :1;
    uint16 TCKPS    :2;
    uint16 TGATE    :1;
    uint16          :6;
    uint16 TSIDL    :1;
    uint16          :1;
    uint16 TON      :1;
} dtT1CON_Bits;

typedef union uT1CON
{
    uint16 U;
    int16 I;
    dtT1CON_Bits B;
} dtT1CON;

typedef struct sT1
{
    uint16  TMR1;
    uint16  PR1;
    dtT1CON CON;
} dtT1;

#define T1 ((dtT1*)0x0100)

#endif	/* T1_REGDEF_H */

