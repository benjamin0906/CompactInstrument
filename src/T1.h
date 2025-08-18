/* 
 * File:   T1.h
 * Author: Benjamin
 *
 * Created on 26 July 2025, 14:48
 */

#ifndef T1_H
#define	T1_H

#include "types.h"

typedef struct sT1Cfg
{
    uint16 On :1;
    uint16 ExtClock :1;
    
    /* 0: 1
     * 1: 8
     * 2: 64
     * 3: 256 */
    uint16 Prescaler:2;
    uint16 Cmp;
} dtT1Cfg;

extern void T1_Init(dtT1Cfg cfg);

#endif	/* T1_H */

