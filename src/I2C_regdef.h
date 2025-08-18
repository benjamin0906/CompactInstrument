/* 
 * File:   I2C_regdef.h
 * Author: Benjamin
 *
 * Created on 27 July 2025, 13:43
 */

#ifndef I2C_REGDEF_H
#define	I2C_REGDEF_H

#include "types.h"

typedef struct sI2C_CON1_Bits
{
    uint16 SEN      :1;
    uint16 RSEN     :1;
    uint16 PEN      :1;
    uint16 RCEN     :1;
    uint16 ACKEN    :1;
    uint16 ACKDT    :1;
    uint16 STREN    :1;
    uint16 GCEN     :1;
    uint16 SMEN     :1;
    uint16 DISSLW   :1;
    uint16 A10M     :1;
    uint16 STRICT   :1;
    uint16 SCLREL   :1;
    uint16 I2CSIDL  :1;
    uint16          :1;
    uint16 I2CEN    :1;
} dtI2C_CON1_Bits;

typedef struct sI2C_CON2_Bits
{
    uint16 DHEN :1;
    uint16 AHEN :1;
    uint16 SBCDE:1;
    uint16 SDAHT:1;
    uint16 BOEN :1;
    uint16 SCIE :1;
    uint16 PCIE :1;
    uint16      :9;
} dtI2C_CON2_Bits;

typedef struct sI2C_STAT_Bits
{
    uint16 TBF      :1;
    uint16 RBF      :1;
    uint16 R_W      :1;
    uint16 S        :1;
    uint16 P        :1;
    uint16 D_A      :1;
    uint16 I2COV    :1;
    uint16 IWCOL    :1;
    uint16 ADD10    :1;
    uint16 GCSTAT   :1;
    uint16 BCL      :1;
    uint16          :2;
    uint16 ACKTIM   :1;
    uint16 TRSTAT   :1;
    uint16 ACKSTAT  :1;
} dtI2C_STAT_Bits;

typedef struct sI2C_ADD_Bits
{
    uint16 ADD  :10;
    uint16      :6;
} dtI2C_ADD_Bits;

typedef struct sI2C_MSK_Bits
{
    uint16 MASK :10;
    uint16      :6;
} dtI2C_MSK_Bits;

typedef struct sI2C_TRN_Bits
{
    uint16 TRN  :8;
    uint16      :8;
} dtI2C_TRN_Bits;

typedef struct sI2C_RCV_Bits
{
    uint16 RCV  :8;
    uint16      :8;
} dtI2C_RCV_Bits;

typedef union uI2C_CON1
{
    uint16 U;
    int16 I;
    dtI2C_CON1_Bits B;
} dtI2C_CON1;

typedef union uI2C_CON2
{
    uint16 U;
    int16 I;
    dtI2C_CON2_Bits B;
} dtI2C_CON2;

typedef union uI2C_STAT
{
    uint16 U;
    int16 I;
    dtI2C_STAT_Bits B;
} dtI2C_STAT;

typedef union uI2C_ADD
{
    uint16 U;
    int16 I;
    dtI2C_ADD_Bits B;
} dtI2C_ADD;

typedef union uI2C_MSK
{
    uint16 U;
    int16 I;
    dtI2C_MSK_Bits B;
} dtI2C_MSK;

typedef union uI2C_TRN
{
    uint16 U;
    int16 I;
    dtI2C_TRN_Bits B;
} dtI2C_TRN;

typedef union uI2C_RCV
{
    uint16 U;
    int16 I;
    dtI2C_RCV_Bits B;
} dtI2C_RCV;

typedef struct sI2Cx
{
    dtI2C_CON1 CONL;
    dtI2C_CON2 CONH;
    dtI2C_STAT STAT;
    dtI2C_ADD ADD;
    dtI2C_MSK MSK;
    uint16 BRG;
    dtI2C_TRN TRN;
    dtI2C_RCV RCV;
} dtI2Cx;

#define I2Cx(x) ((dtI2Cx*)0x0200)[x]

#endif	/* I2C_REGDEF_H */

