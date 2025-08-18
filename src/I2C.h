/* 
 * File:   I2C.h
 * Author: Benjamin
 *
 * Created on 27 July 2025, 14:16
 */

#ifndef I2C_H
#define	I2C_H

#include "types.h"

typedef struct sI2cTrDesc
{
    uint8 slave_address;
    uint8 *reg_addr_ptr;
    uint8 *data_ptr;
    uint8 data_len;
    uint8 reg_addr_len      :6;
    uint8 read_transmission :1;
    uint8 instance          :1;
} dtI2cTrDesc;

typedef enum eI2cStatus
{
    I2cStatus_Done,
            I2cStatus_Ongoing,
            I2cStatus_Error,
} dtI2cStatus;

extern void I2C_Init(const uint8 instance, const uint16 brg);
extern void I2C_Transmission(const dtI2cTrDesc *const desc);
extern dtI2cStatus I2C_GetStatus(void);

#endif	/* I2C_H */

