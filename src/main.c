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

/**
 * @brief Dividing an unsigned 32bit number by an unsigned 16 bit number
 * @details The function uses the divisor instruction. The result is an uint16 so the result must be small enough to fit in.
 *          The function also rounds the remainder.
 * @param dividend, 32 bit unsigned value
 * @param divisor, 16 bit unsigned value
 * @return 16 bit unsigned value
 */
uint16 DivisonU32byU16(unsigned long dividend, uint16 divisor)
{
    asm(
    
    "PUSH W5\n"
    "PUSH W4\n"
    "MOV.D W0, W4\n"
    "REPEAT #17\n"
    "DIV.UD W4, W2\n"
    
    /* Rounding of the result:
     * if the double of the remainder is greater than or equal to the
     * divisor, then incrementing the result by 1 */
    "SL W1, #1, W1\n"
    "CPSLT W1, W2\n"
    "INC W0, W0\n"
    "POP W4\n"
    "POP W5\n"
    );
}

uint8 ExtendString(uint8 *string, uint8 extChar, uint8 toLength)
{
    uint8 len = strlen(string);
    if(len < toLength)
    {
        memcpy_inverse(&string[0], &string[toLength - len], len);
        memset(&string[0], extChar, toLength - len);
        len = toLength;
        string[len] = 0;
    }
    return len;
}

void InsertChar(uint8 *string, uint8 character, uint8 position)
{
    uint8 len = strlen(string) + 1;
    if(len > position)
    memcpy_inverse(&string[position], &string[position + 1], len - position);
    string[position] = character;
}

void main(void)
{
    uint8 sa = 0x4c;
    uint8 reg[2] = {0x60, 0x34};
    uint8 data[2] = {0,0};
    uint16 ts = SysTime();
    dtT1Cfg T1cfg = {.Cmp = 8749, .ExtClock = 0, .On = 1, .Prescaler = 1};
    dtPllCfg PllCfg = {.M = 74, .N1 = 0, .N2 = 0, .OscSel = 1};
    dtSpiCfg SpiCfg = {.bits_16 = 0, .cpha = 1, .cpol = 0, .instance = 0, .pri_prescaler = 3, .sec_prescaler = 1};
    
    SRC_PllConfig(PllCfg);
    T1_Init(T1cfg);
    
    Ports_SetMode(Port_B_8, Port_DO);
    Ports_SetMode(Port_B_15, Port_DO);
    Ports_SetPin(Port_B_8, 0);
    Ports_SetPin(Port_B_15, 1);
    
    Ports_SetMode(Port_B_3, Port_DO);
    Ports_SetMode(Port_B_2, Port_DO);
    
    Ports_SetMode(Port_B_14, Port_DO);
    Ports_SetMode(Port_A_4, Port_DO);
    Ports_SetMode(Port_A_3, Port_DO);
    
    Ports_SetMode(Port_B_12, Port_DO);
    Ports_SetMode(Port_B_13, Port_DO);
    Ports_SetMode(Port_B_14, Port_DO);
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
    
    uint16 var = 0;
    OLED_Driver_Set(OledMode_On);
    EMC1701_Driver_Turn(1);
    
    int32 avg_res_volt_buff[10] = {0,0,0,0,0,0,0,0,0,0};
    
    while(1)
    {
        uint8 line[50];
        OLED_Driver_Runnable();
        EMC1701_Driver_Runnable();
        if(TimePassed(ts, 50) != 0)
        {
            int32 avg_res_volt = 0;
            uint8 t = 0;
            ts = SysTime();
            Ports_SetPin(Port_B_2, var & 1);
            var++;
            memcpy_inverse(&avg_res_volt_buff[0], &avg_res_volt_buff[1], sizeof(avg_res_volt_buff) - sizeof(avg_res_volt_buff[0]));
            avg_res_volt_buff[0] = EMC1701_Driver_GetResVolt();
            
            avg_res_volt = 0;
            for(t = 0; t < (sizeof(avg_res_volt_buff)/sizeof(avg_res_volt_buff[0])); t++)
            {
                avg_res_volt += avg_res_volt_buff[t];
            }
            avg_res_volt = divS32byS16(avg_res_volt, (sizeof(avg_res_volt_buff)/sizeof(avg_res_volt_buff[0])));
            
            if(OLED_Driver_Running() != 0)
            {
                uint8 len = 0;
                uint8 t = 0;
                int16 current = divS32byS16(EMC1701_Driver_GetResVolt(), 2000);
                int16 avg_current = divS32byS16(avg_res_volt, 2000);
                uint16 src_voltage = DivisonU32byU16(EMC1701_Driver_GetSrcVolt(), 10u);
                
                line[len++] = 'R';
                line[len++] = 'a';
                line[len++] = 'n';
                line[len++] = 'g';
                line[len++] = 'e';
                line[len++] = ':';
                len += Dabler8Bit(EMC1701_Driver_GetRange(), &line[len]);
                line[len++] = ' ';
                line[len++] = 'm';
                line[len++] = 'V';
                line[len++] = '\n';
                
                /* adding src voltage */
                Dabler8Bit(src_voltage, &line[len]);
                len += ExtendString(&line[len], '0', 5);
                InsertChar(line, ',', len-3);
                len++;
                line[len++] = ' ';
                line[len++] = 'V';
                line[len++] = '\n';
                
                /* adding res voltage */
                if(current < 0)
                {
                    line[len++] = '-';
                    current *= -1;
                }
                t = Dabler8Bit(current, &line[len]);
                if(t == 1)
                {
                    len += ExtendString(&line[len], '0', 2);
                }
                else
                {
                    len += t;
                }
                
                InsertChar(&line[0], ',', len-1);
                len++;
                line[len++] = ' ';
                line[len++] = 'm';
                line[len++] = 'A';
                line[len++] = ' ';
                if(avg_current < 0)
                {
                    line[len++] = '-';
                    avg_current *= -1;
                }
                t = Dabler8Bit(avg_current, &line[len]);
                if(t == 1)
                {
                    len += ExtendString(&line[len], '0', 2);
                }
                else
                {
                    len += t;
                }
                InsertChar(&line[0], ',', len-1);
                len++;
                line[len++] = ' ';
                line[len++] = 'm';
                line[len++] = 'A';
                line[len++] = '\n';
                
                Dabler8Bit(var, &line[len]);
                len += ExtendString(&line[len], '0', 6);
                line[len++] = 0;
                OLED_Driver_PutString(line);
            }
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
