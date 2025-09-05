/* 
 * File:   EMC1701_Driver_regdef.h
 * Author: Benjamin
 *
 * Created on 27 July 2025, 21:31
 */

#ifndef EMC1701_DRIVER_REGDEF_H
#define	EMC1701_DRIVER_REGDEF_H

#include "types.h"

typedef struct s03hConf_Bits
{
    uint8               :2;
    uint8 IMEAS_STOP    :1;
    uint8               :2;
    uint8 ALERT_COMP    :1;
    uint8 TMEAS_STOP    :1;
    uint8 MASK_ALL      :1;
} dt03hConf_Bits;

typedef struct s04hConvRate_Bits
{
    uint8 T_CONV    :3;
    uint8           :5;
} dt04hConvRate_Bits;

typedef struct s02hStatus_Bits
{
    uint8       :1;
    uint8 CRIT  :1;
    uint8       :1;
    uint8 LOW   :1;
    uint8 HIGH  :1;
    uint8       :1;
    uint8 PEAK  :1;
    uint8 BUSY  :1;
} dt02hStatus_Bits;

typedef union u03hConf
{
    uint8 U;
    int8 I;
    dt03hConf_Bits B;
} dt03hConf;

typedef union u04hConvRate
{
    uint8 U;
    int8 I;
    dt04hConvRate_Bits B;
} dt04hConvRate;

typedef union u02hStatus
{
    uint8 U;
    int8 I;
    dt02hStatus_Bits B;
} dt02hStatus;

#endif	/* EMC1701_DRIVER_REGDEF_H */

