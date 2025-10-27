/*
 * File:   main.c
 * Author: Benjamin
 *
 * Created on July 26, 2025, 9:52 AM
 */


#include "xc.h"
#include "types.h"
#include "Ports.h"
#include "ISR.h"
#include "T1.h"
#include "SRC.h"
#include "SRC_regdef.h"
#include "I2C.h"
#include "SPI.h"
#include "OLED_Driver.h"
#include "SPI.h"
#include "EMC1701_Driver.h"
#include "AsmFunctions.h"
#include "DisplayLayout.h"
#include "ButtonHandler.h"

#pragma config FNOSC = FRC              // Oscillator Source Selection (Internal Fast RC (FRC))
#pragma config IESO = OFF               // Two-speed Oscillator Start-up Enable bit (Start up with user-selected oscillator source)

#pragma config POSCMD = NONE            // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
#pragma config OSCIOFNC = ON            // OSC2 Pin Function bit (OSC2 is general purpose digital I/O pin)
#pragma config IOL1WAY = OFF            // Peripheral pin select configuration bit (Allow multiple reconfigurations)
#pragma config FCKSM = CSECME           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are enabled)
#pragma config PLLKEN = OFF              // PLL Lock Enable Bit (Clock switch to PLL source will wait until the PLL lock signal is valid)

#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler bits (1:32,768)
#pragma config WDTPRE = PR128           // Watchdog Timer Prescaler bit (1:128)
#pragma config WDTEN = OFF              // Watchdog Timer Enable bits (WDT and SWDTEN disabled)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
#pragma config WDTWIN = WIN25           // Watchdog Timer Window Select bits (WDT Window is 25% of WDT period)

#pragma config ICS = PGD1
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)
#pragma config BTSWP = OFF

typedef enum eMainStates
{
    MainState_Init_Off,
            MainState_Init_MeasureOffset,
            MainState_Measuring,
} dtMainStates;

#define SENSE_ENABLE    Port_A_0
#define BUTTON_LEFT     Port_A_1
#define BUTTON_RIGHT    Port_B_1

uint16 SysCntr;

void __attribute__ ((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    SysCntr++;
    ISR_CLEAR_T1();
}

uint16 SysTime(void)
{
    return SysCntr;
}

uint8 TimePassed(uint16 timestamp, uint16 timeout)
{
    if((SysCntr-timestamp) > timeout)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void main(void)
{
    uint16 ts = SysTime();
    dtT1Cfg T1cfg = {.Cmp = 8749, .ExtClock = 0, .On = 1, .Prescaler = 1};
    dtPllCfg PllCfg = {.M = 74, .N1 = 0, .N2 = 0, .OscSel = 1};
    dtSpiCfg SpiCfg = {.bits_16 = 0, .cpha = 1, .cpol = 0, .instance = 0, .pri_prescaler = 3, .sec_prescaler = 1};
    dtMainStates MainState = MainState_Init_Off;
    
    SRC_PllConfig(PllCfg);
    T1_Init(T1cfg);
    
    Ports_SetMode(Port_B_8, Port_DO);
    Ports_SetMode(Port_B_15, Port_DO);
    Ports_SetPin(Port_B_8, 0);
    Ports_SetPin(Port_B_15, 1);
    Ports_SetMode(Port_A_1, Port_DI);
    
    Ports_SetMode(Port_B_11, Port_DO);
    Ports_SetMode(Port_B_2, Port_DO);
    
    Ports_SetMode(Port_B_14, Port_DO);
    Ports_SetMode(Port_A_4, Port_DO);
    Ports_SetMode(Port_A_3, Port_DO);
    
    Ports_SetMode(Port_B_12, Port_DO);
    Ports_SetMode(Port_B_13, Port_DO);
    Ports_SetMode(Port_B_14, Port_DO);
    Ports_SetMode(SENSE_ENABLE, Port_DO);
    Ports_SetPin(SENSE_ENABLE, 0);
    Ports_ConfigOutputSelection(44, Ports_OutFun_SCK1);
    Ports_ConfigInputSelection(44, Ports_InFun_SCK1IN);
    Ports_ConfigOutputSelection(45, Ports_OutFun_SDO1);
    
    Ports_SetPin(Port_B_8, 1);
    SPI_Init(SpiCfg);
    I2C_Init(1, 692);
    
    ISR_GlobalEnable();
    
    Ports_SetPin(Port_B_2, 1);
    ISR_SetIsr(ISRsrc_T1, ISR_Enable);
    ISR_SetIsr(ISRsrc_MI2C2, ISR_Enable);
    
    //OLED_Driver_Init();
    while(TimePassed(ts, 200) == 0);
    
    uint8 var = 0;
    OLED_Driver_Set(OledMode_On);
    EMC1701_Driver_Turn(1);
    
    int32 avg_res_volt_buff[20] = {0,0,0,0,0,0,0,0,0,0};
    uint32 avg_src_vol_buff[20] = {0,0,0,0,0,0,0,0,0,0};
    int32 res_volt_offset = 0;
    
    memset(avg_res_volt_buff, 0, sizeof(avg_res_volt_buff));
    memset(avg_src_vol_buff, 0, sizeof(avg_src_vol_buff));
    
    while(1)
    {
        OLED_Driver_Runnable();
        EMC1701_Driver_Runnable();
        ButtonHandler_Runnable();
        if(ButtonHandler_GetButton() != 0)
        {
            Ports_SetPin(Port_B_11, 1);
        }
        else
        {
            Ports_SetPin(Port_B_11, 0);
        }
        if(TimePassed(ts, 50) != 0)
        {
            int32 avg_res_volt = 0;
            uint32 avg_src_volt = 0;
            int32 curr_res_volt = EMC1701_Driver_GetResVolt();
            uint32 curr_src_volt = EMC1701_Driver_GetSrcVolt();
            int32 curr_current;
            int32 avg_current;
            int32 curr_power;
            int32 avg_power;
            uint8 t = 0;
            ts = SysTime();
            Ports_SetPin(Port_B_2, var & 1);
                 
            memcpy_inverse(&avg_res_volt_buff[0], &avg_res_volt_buff[1], sizeof(avg_res_volt_buff) - sizeof(avg_res_volt_buff[0]));
            avg_res_volt_buff[0] = curr_res_volt;
            
            memcpy_inverse(&avg_src_vol_buff[0], &avg_src_vol_buff[1], sizeof(avg_src_vol_buff) - sizeof(avg_src_vol_buff[0]));
            avg_src_vol_buff[0] = curr_src_volt;
            
            avg_res_volt = 0;
            for(t = 0; t < (sizeof(avg_res_volt_buff)/sizeof(avg_res_volt_buff[0])); t++)
            {
                avg_res_volt += avg_res_volt_buff[t];
            }
            avg_res_volt = divS32byS16toS32(avg_res_volt, (sizeof(avg_res_volt_buff)/sizeof(avg_res_volt_buff[0])));
            
            for(t = 0; t < (sizeof(avg_src_vol_buff)/sizeof(avg_src_vol_buff[0])); t++)
            {
                avg_src_volt += avg_src_vol_buff[t];
            }
            avg_src_volt = divS32byS16toS32(avg_src_volt, (sizeof(avg_src_vol_buff)/sizeof(avg_src_vol_buff[0])));
            
            
            curr_res_volt -= res_volt_offset;
            avg_res_volt -= res_volt_offset;
            
            curr_src_volt = divU32byU16toU16(curr_src_volt, 10u);
            avg_src_volt = divU32byU16toU16(avg_src_volt, 10u);
            curr_current= divS32byS16toS32(curr_res_volt, 2000);
            avg_current = divS32byS16toS32(avg_res_volt, 2000);
            curr_power  = divS32byS16toS32(curr_current * curr_src_volt, 10000u);
            avg_power   = divS32byS16toS32(avg_current * avg_src_volt, 10000u);
            
            switch(MainState)
            {
                case MainState_Init_Off:
                    Ports_SetPin(SENSE_ENABLE, 1);
                    MainState = MainState_Measuring;
                    break;
                case MainState_Init_MeasureOffset:
                    DisplayLayout_Init(avg_res_volt);
                    if(ButtonHandler_GetButton() == 0)
                    {
                        res_volt_offset = avg_res_volt;
                        MainState = MainState_Measuring;
                        //Ports_SetPin(SENSE_ENABLE, 1);
                    }
                    break;
                case MainState_Measuring:
                    DisplayLayout_Measurement(EMC1701_Driver_GetRange(), curr_current, avg_current, curr_src_volt, avg_src_volt, curr_power, avg_power);
                    if(ButtonHandler_GetButton() >= 80)
                    {
                        MainState = MainState_Init_MeasureOffset;
                        res_volt_offset = 0;
                    }
                    break;
            }
            var++;
        }
    }
}

void __attribute__ ((interrupt, no_auto_psv)) _AddressError(void)
{
    while(1);
}

void __attribute__ ((interrupt, no_auto_psv)) _HardTrapError(void)
{
    while(1);
}

void __attribute__ ((interrupt, no_auto_psv)) _StackError(void)
{
    while(1);
}
