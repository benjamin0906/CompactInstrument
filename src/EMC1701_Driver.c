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
            EmcState_Running_WaitState,
            EmcState_Running_ProcState,
            EmcState_Running_ReadResistor,
            EmcState_Running_ProcRes,
            EmcState_Running_ReadSource,
            EmcState_Running_ProcSource,
            EmcState_RangeCheck,
            EmcState_WaitForComm,
} dtEmcStates;

typedef struct sReg02h_Bits
{
    uint8               :1;
    uint8 CRIT          :1;
    uint8               :1;
    uint8 LOW           :1;
    uint8 HIGH          :1;
    uint8               :1;
    uint8 PEAK          :1;
    uint8 BUSY          :1;
} dtReg02h_Bits;

typedef struct sReg51h_Bits
{
    uint8 CS_RANGE      :2;
    uint8 CS_SAMPLE_TIME:2;
    uint8 CS_SAMPLE_AVG :2;
    uint8 CS_QUEUE      :2;
} dtReg51h_Bits;

typedef union uReg02h
{
    dtReg02h_Bits B;
    uint8 U;
} dtReg02h;

typedef union uReg51h
{
    dtReg51h_Bits B;
    uint8 U;
} dtReg51h;

static uint8 FscRange = 80;
static int8 rangeCntr;
static uint8 increaseCntr;
static dtEmcStates EmcState;
static dtEmcStates EmcAfterWaitState;
static int32 ResistorVoltage;
static uint32 SourceVoltage;
static uint8 substate;
static uint8 data[2];
static uint8 reg;
dtI2cTrDesc desc;
static dtReg51h Reg51h;
static dtReg02h Reg02h;
static uint16 Timestamp;

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
            Reg51h.U = 0x03;
            desc.data_ptr = &Reg51h.U;
            I2C_Transmission(&desc);
            EmcState = EmcState_WaitForComm;
            EmcAfterWaitState = EmcState_Init_Config;
            break;
        case EmcState_Init_Config:
            reg = 0x03;
            data[0] = 0x00;
            desc.data_ptr = &data[0];
            I2C_Transmission(&desc);
            EmcState = EmcState_WaitForComm;
            EmcAfterWaitState = EmcState_Running;
            EmcAfterWaitState = EmcState_Running_ReadResistor;
            desc.data_len = 2;
            desc.read_transmission = 1;
            break;
        case EmcState_Running:
            desc.read_transmission = 1;
            desc.data_ptr = &data[0];
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
            EmcState = EmcState_Running;
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
            break;
        case EmcState_Running_WaitState:
            if(TimePassed(Timestamp, 10))
            {
                Timestamp = SysTime();
                EmcState = EmcState_Running_ReadResistor;
            }
            break;
        case EmcState_Running_ReadResistor:
            desc.data_ptr = &data[0];
            desc.data_len = 2;
            desc.read_transmission = 1;
            reg = 0x54;
            I2C_Transmission(&desc);
            EmcState = EmcState_WaitForComm;
            EmcAfterWaitState = EmcState_Running_ProcRes;
            break;
        case EmcState_Running_ProcRes:
        {
            int16 t = (int16)(((uint16)data[0]) << 8);
            t |= (uint16)data[1];
            t >>= 4;
            ResistorVoltage = divS32byS16((int32)FscRange * 1000000, 2047) * t; //nV
            EmcState = EmcState_Running_ReadSource;
        }
            break;
        case EmcState_Running_ReadSource:
            desc.data_ptr = &data[0];
            desc.data_len = 2;
            desc.read_transmission = 1;
            reg = 0x58;
            I2C_Transmission(&desc);
            EmcState = EmcState_WaitForComm;
            EmcAfterWaitState = EmcState_Running_ProcSource;
            break;
        case EmcState_Running_ProcSource:
        {

            uint16 t = (uint16)data[0];
            t <<= 8;
            t |= (uint16)data[1];
            t >>= 5;
            SourceVoltage = ((uint32)t * 117); //100uV
            EmcState = EmcState_RangeCheck;
        }
            break;
        case EmcState_RangeCheck:
        {
            uint32 tFsc = FscRange * 100000;
            int32 abs_res_volt = ResistorVoltage;
            if(abs_res_volt < 8)
            {
                abs_res_volt = abs_res_volt * (-1);
            }
            reg = 0x51;
            desc.data_ptr = &Reg51h.U;
            desc.read_transmission = 0;
            if(abs_res_volt < (tFsc * 4))
            {
                if(rangeCntr < 5u)
                {
                    rangeCntr++;
                }
                else
                {
                    if(Reg51h.B.CS_RANGE > 0)
                    {
                        Reg51h.B.CS_RANGE--;
                        FscRange >>= 1;
                        I2C_Transmission(&desc);
                        EmcState = EmcState_WaitForComm;
                        EmcAfterWaitState = EmcState_Running_WaitState;
                    }
                    else
                    {
                        EmcState = EmcState_Running_WaitState;
                    }
                    rangeCntr = 0;
                }
            }
            if(abs_res_volt > (tFsc * 9))
            {
                if(rangeCntr > -5)
                {
                    rangeCntr--;
                }
                else
                {
                    if(Reg51h.B.CS_RANGE < 3)
                    {
                        Reg51h.B.CS_RANGE++;
                        FscRange <<= 1;
                        I2C_Transmission(&desc);
                        EmcState = EmcState_WaitForComm;
                        EmcAfterWaitState = EmcState_Running_WaitState;
                    }
                    else 
                    {
                        EmcState = EmcState_Running_WaitState;
                    }
                    rangeCntr = 0;
                }
            }
        }
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

uint8 EMC1701_Driver_GetRange(void)
{
    return  FscRange;
}