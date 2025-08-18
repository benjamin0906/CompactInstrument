/* 
 * File:   Ports.h
 * Author: Benjamin
 *
 * Created on July 26, 2025, 11:43 AM
 */

#ifndef PORTS_H
#define	PORTS_H

typedef enum ePort_pin
{
    Port_A_0 = 0,
    Port_A_1,
    Port_A_2,
    Port_A_3,
    Port_A_4,
    Port_B_0 = 16,
    Port_B_1,
    Port_B_2,
    Port_B_3,
    Port_B_4,
    Port_B_5,
    Port_B_6,
    Port_B_7,
    Port_B_8,
    Port_B_9,
    Port_B_10,
    Port_B_11,
    Port_B_12,
    Port_B_13,
    Port_B_14,
    Port_B_15,
            
} dtPort_pin;

typedef enum ePort_mode
{
    Port_DO = 0, //digital output
    Port_DI = 1, //digital input
    Port_AI = 2, //analog input
} dtPort_mode;

typedef enum eOutFuncs
{
    Ports_OutFunc_Default = 0,
    Ports_OutFun_U1TX,
    Ports_OutFun_U1RTS,
    Ports_OutFun_U2TX,
    Ports_OutFun_U2RTS,
    Ports_OutFun_SDO1,
    Ports_OutFun_SCK1,
    Ports_OutFun_SS1,
    Ports_OutFun_SDO2,
    Ports_OutFun_SCK2,
    Ports_OutFun_SS2,
    Ports_OutFun_OC1 = 0x10,
    Ports_OutFun_OC2,
    Ports_OutFun_OC3,
    Ports_OutFun_OC4,
    Ports_OutFun_ACMP1 = 0x18,
    Ports_OutFun_ACMP2,
    Ports_OutFun_ACMP3,
    Ports_OutFun_SYNCO1 = 0x2D,
    Ports_OutFun_SYNCO2,
    Ports_OutFun_REFCLKO = 0x31,
    Ports_OutFun_ACMP4 = 0x32,
    Ports_OutFun_PWM4H,
    Ports_OutFun_PWM4L,
    Ports_OutFun_PWM5H,
    Ports_OutFun_PWM5L,
} dtOutFuncs;

typedef enum eInFuncs
{
    Ports_InFun_INT1 = 1,
    Ports_InFun_INT2,
    Ports_InFun_T1CK = 5,
    Ports_InFun_T2CK,
    Ports_InFun_T3CK,
    Ports_InFun_IC1 = 14,
    Ports_InFun_IC2,
    Ports_InFun_IC3,
    Ports_InFun_IC4,
    Ports_InFun_OCFA = 22,
    Ports_InFun_FLT1 = 24,
    Ports_InFun_FLT2,
    Ports_InFun_FLT3,
    Ports_InFun_FLT4,
    Ports_InFun_U1RX = 36,
    Ports_InFun_U1CT,
    Ports_InFun_U2RX,
    Ports_InFun_U2CT,
    Ports_InFun_SDI1,
    Ports_InFun_SCK1IN,
    Ports_InFun_SS1,
    Ports_InFun_SDI2 = 44,
    Ports_InFun_SCK2IN,
    Ports_InFun_SS2,
    Ports_InFun_SYNCI1 = 75,
    Ports_InFun_SYNCI2,
    Ports_InFun_FLT5 = 84,
    Ports_InFun_FLT6,
    Ports_InFun_FLT7,
    Ports_InFun_FLT8,
} dtInFuncs;

extern void Ports_SetMode(dtPort_pin pin, dtPort_mode mode);
extern void Ports_SetPin(dtPort_pin pin, uint8 value);
extern void Ports_ConfigOutputSelection(uint8 remap_id, dtOutFuncs func);
extern void Ports_ConfigInputSelection(uint8 remap_id, dtInFuncs func);

#endif	/* PORTS_H */

