#include "EMC1701_Driver_regdef.h"
#include "I2C.h"
#include "AsmFunctions.h"

typedef enum eEmcStates
{
    EmcState_Off,
            EmcState_Init_Desc,
            EmcState_Init_StopConfig,
            EmcState_Init_ConfigRate,
            EmcState_Init_Curr_Cfg,
            EmcState_Init_Config,
            EmcState_Running,
            EmcState_Pocessing,
            EmcState_WaitForComm,
} dtEmcStates;

static uint8 FscRange = 80;
static dtEmcStates EmcState;
static dtEmcStates EmcAfterWaitState;
static int32 ResistorVoltage;
static uint32 SourceVoltage;
static uint8 substate;
static uint8 data[2];
static uint8 reg;
dtI2cTrDesc desc;

void EMC1701_Driver_Runnable(void)
{
    switch(EmcState)
    {
        case EmcState_Off:
            break;
        case EmcState_Init_Desc:
            desc.slave_address = 0x4C;
            desc.reg_addr_ptr = &reg;
            desc.reg_addr_len = 1;
            desc.read_transmission = 0;
            desc.instance = 1;
            desc.data_ptr = data;
            desc.data_len = 1;
            EmcState = EmcState_Init_StopConfig;
            break;
        case EmcState_Init_StopConfig:
            reg = 0x03;
            data[0] = 0x04;
            I2C_Transmission(&desc);
            EmcState = EmcState_WaitForComm;
            EmcAfterWaitState = EmcState_Init_ConfigRate;
            break;
        case EmcState_Init_ConfigRate:
            reg = 0x04;
            data[0] = 0x07;
            I2C_Transmission(&desc);
            EmcState = EmcState_WaitForComm;
            EmcAfterWaitState = EmcState_Init_Curr_Cfg;
            break;
        case EmcState_Init_Curr_Cfg:
            reg = 0x51;
            data[0] = 0x03;
            I2C_Transmission(&desc);
            EmcState = EmcState_WaitForComm;
            EmcAfterWaitState = EmcState_Init_Config;
            break;
        case EmcState_Init_Config:
            reg = 0x03;
            data[0] = 0x00;
            I2C_Transmission(&desc);
            EmcState = EmcState_WaitForComm;
            EmcAfterWaitState = EmcState_Running;
            desc.data_len = 2;
            desc.read_transmission = 1;
            break;
        case EmcState_Running:
            switch(substate)
            {
                case 0:
                    reg = 0x54;
                    I2C_Transmission(&desc);
                    EmcState = EmcState_WaitForComm;
                    EmcAfterWaitState = EmcState_Pocessing;
                    break;
                case 1:
                    reg = 0x58;
                    I2C_Transmission(&desc);
                    EmcState = EmcState_WaitForComm;
                    EmcAfterWaitState = EmcState_Pocessing;
                    break;
            }
            break;
        case EmcState_Pocessing:
            switch(substate)
            {
                case 0:
                {
                    int16 t = (int16)(((uint16)data[0]) << 8);
                    t |= (uint16)data[1];
                    t >>= 4;
                    ResistorVoltage = divS32byS16((int32)FscRange * 1000000, 2047) * t; //uV
                    substate = 1;
                }
                    break;
                case 1:
                {
                    
                    uint16 t = (uint16)data[0];
                    t <<= 8;
                    t |= (uint16)data[1];
                    t >>= 5;
                    SourceVoltage = ((uint32)t * 117); //100uV
                    substate = 0;
                }
                    break;
            }
            EmcState = EmcState_Running;
            break;
        case EmcState_WaitForComm:
            if(I2C_GetStatus() == I2cStatus_Done)
            {
                EmcState = EmcAfterWaitState;
            }
            break;
    }
}

void EMC1701_Driver_Turn(uint8 on)
{
    if(on != 0)
    {
        if(EmcState == EmcState_Off)
        {
            EmcState = EmcState_Init_Desc;
        }
    }
}

uint8 EMC1701_Driver_Running(void)
{
    return (EmcState == EmcState_Running) || ((EmcAfterWaitState == EmcState_Running) && (EmcState == EmcState_WaitForComm));
}

int32 EMC1701_Driver_GetResVolt(void)
{
    return ResistorVoltage;
}

uint32 EMC1701_Driver_GetSrcVolt(void)
{
    return SourceVoltage;
}