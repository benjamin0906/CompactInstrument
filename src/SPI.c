#include "SPI_regdef.h"
#include "SPI.h"
#include "ISR.h"

dtSpiTrDesc SpiDescriptor;
uint8 SpiTransmission;
volatile uint8 int_cntr;

void SPI_Init(dtSpiCfg cfg)
{
    dtISRsrc isr = ISRsrc_SPI1;
    if(cfg.instance != 0)
    {
        isr = ISRsrc_SPI2;
    }
    SPI(cfg.instance).STAT.U = 0;
    SPI(cfg.instance).CON1.U = 0;
    SPI(cfg.instance).CON2.U = 0;
    
    SPI(cfg.instance).CON1.B.MSTEN = 1;
    SPI(cfg.instance).CON1.B.MODE16 = cfg.bits_16;
    SPI(cfg.instance).CON1.B.CKE = cfg.cpha;
    SPI(cfg.instance).CON1.B.CKP = cfg.cpol;
    SPI(cfg.instance).CON1.B.SPRE = cfg.sec_prescaler;
    SPI(cfg.instance).CON1.B.PPRE = cfg.pri_prescaler;
    SPI(cfg.instance).CON1.B.SMP = 1;
    SPI(cfg.instance).CON2.B.FRMEN = 0;
    SPI(cfg.instance).CON2.B.SPIFSD = 0;
    SPI(cfg.instance).CON2.B.FRMPOL = 0;
    SPI(cfg.instance).CON2.B.FRMDLY = 0;
    
    SPI(cfg.instance).STAT.B.SPIEN = 1;
    
    ISR_CLEAR_SPI1();
    ISR_SetIsr(isr, ISR_Enable);
}

uint8 SPI_SpiReady(void)
{
    return SpiTransmission == 0;
}

void SPI_Transmit(uint8 instance, dtSpiTrDesc descriptor)
{
    if(SpiTransmission == 0)
    {
        SpiTransmission = 1;
        SpiDescriptor = descriptor;
        SPI(instance).BUF = *SpiDescriptor.tx_buff;
        SpiDescriptor.tx_buff++;
        SpiDescriptor.length--;
    }
}

void __attribute__ ((interrupt, no_auto_psv)) _SPI1Interrupt(void)
{
    volatile uint8 temp = SPI(0).BUF;
    if(SpiDescriptor.rx_buff != 0)
    {
        *SpiDescriptor.rx_buff = temp;
        SpiDescriptor.rx_buff++;
    }
    if(SpiDescriptor.length != 0)
    {
        SPI(0).BUF = *SpiDescriptor.tx_buff;
        SpiDescriptor.tx_buff++;
        SpiDescriptor.length--;
    }
    else
    {
        SpiTransmission = 0;
    }
    ISR_CLEAR_SPI1();
}

void __attribute__ ((interrupt, no_auto_psv)) _SPI2Interrupt(void)
{
    
}