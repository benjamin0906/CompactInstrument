/* 
 * File:   SPI.h
 * Author: Benjamin
 *
 * Created on 28 July 2025, 15:21
 */

#ifndef SPI_H
#define	SPI_H

#include "types.h"

typedef struct sSpiCfg
{
    uint8 instance  :1;
    uint8 bits_16   :1;
    uint8 cpha      :1;
    uint8 cpol      :1;
    
    /* 0: 8
     * 1: 7
     * ...
     * 7: 1 */
    uint8 sec_prescaler :3;
    
    /* 0: 64
     * 1: 16
     * 2: 4
     * 3: 1 */
    uint8 pri_prescaler :2;
} dtSpiCfg;

typedef struct sSpiTrDesc
{
    uint8 *tx_buff;
    uint8 *rx_buff;
    uint16 length;
} dtSpiTrDesc;

extern void SPI_Init(dtSpiCfg cfg);
extern uint8 SPI_SpiReady(void);
extern void SPI_Transmit(uint8 instance, dtSpiTrDesc descriptor);

#endif	/* SPI_H */

