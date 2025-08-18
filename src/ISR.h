/* 
 * File:   ISR.h
 * Author: Benjamin
 *
 * Created on 26 July 2025, 14:11
 */

#ifndef ISR_H
#define	ISR_H

typedef enum eISRsrc
{
    ISRsrc_INT0 = 0,
            ISRsrc_IC1,
            ISRsrc_OC1,
            ISRsrc_T1,
            ISRsrc_,
            ISRsrc_IC2 = 5,
            ISRsrc_OC2,
            ISRsrc_T2,
            ISRsrc_T3,
            ISRsrc_SPI1E,
            ISRsrc_SPI1,
            ISRsrc_U1RX,
            ISRsrc_U1TX,
            ISRsrc_ADC,
            ISRsrc_NVM = 15,
            ISRsrc_SI2C1,
            ISRsrc_MI2C1,
            ISRsrc_CMP1,
            ISRsrc_CN,
            ISRsrc_INT1,
            ISRsrc_OC3 = 25,
            ISRsrc_OC4,
            ISRsrc_T4,
            ISRsrc_T5,
            ISRsrc_INT2,
            ISRsrc_U2RX,
            ISRsrc_U2TX,
            ISRsrc_SPI2E,
            ISRsrc_SPI2,
            ISRsrc_IC3 = 37,
            ISRsrc_IC4,
            ISRsrc_SI2C2 = 49,
            ISRsrc_MI2C2,
            ISRsrc_INT4 = 54,
            ISRsrc_PSEM = 57,
            ISRsrc_U1E = 65,
            ISRsrc_U2E,
            ISRsrc_PWM_SSEM = 73,
            ISRsrc_PWM1 = 94,
            ISRsrc_PWM2,
            ISRsrc_PWM3,
            ISRsrc_PWM4,
            ISRsrc_PWM5,
            ISRsrc_CMP2 = 103,
            ISRsrc_CMP3,
            ISRsrc_CMP4,
            ISRsrc_AN0 = 110,
            ISRsrc_AN1,
            ISRsrc_AN2,
            ISRsrc_AN3,
            ISRsrc_AN4,
            ISRsrc_AN5,
            ISRsrc_AN6,
            ISRsrc_AN7,
            ISRsrc_ICD = 142,
            ISRsrc_JTAG,
            ISRsrc_AN8 = 151,
            ISRsrc_AN9,
            ISRsrc_AN10,
            ISRsrc_AN11,
            ISRsrc_AN12,
            ISRsrc_AN13,
            ISRsrc_AN14,
            ISRsrc_AN15,
            ISRsrc_AN16,
            ISRsrc_AN17,
            ISRsrc_AN18,
            ISRsrc_AN19,
            ISRsrc_AN20,
            ISRsrc_AN21,
            ISRsrc_I2C1 = 173,
            ISRsrc_I2C2,
            ISRsrc_ADCMP0 = 177,
            ISRsrc_ADCMP1,
            ISRsrc_ADFLTR0,
            ISRsrc_ADFLTR1,
} dtISRsrc;

typedef enum
{
    ISR_Enable = 0,
            ISR_Disable
} dtISRen_dis;

extern void ISR_SetIsr(dtISRsrc src, dtISRen_dis val);
//extern void ISR_ClearFlag(dtISRsrc src);
extern void ISR_GlobalEnable(void);

#define ISR_CLEAR_T1() asm("BCLR 0x800+0, #3")
#define ISR_CLEAR_SPI1() asm("BCLR 0x800+0, #10")
#define ISR_CLEAR_I2C2() asm("BCLR 0x800+6, #2")

#endif	/* ISR_H */

