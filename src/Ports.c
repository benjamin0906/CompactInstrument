#include "Ports_regdef.h"
#include "Ports.h"

void Ports_SetMode(dtPort_pin pin, dtPort_mode mode)
{
    uint8 port = pin >> 4;
    uint8 pinpos = pin & 0x0F;
    uint16 mask = 1 << (pinpos);
    
    if(mode != Port_AI)
    {
        PORTS->P[port].ANSEL &= ~mask;
        if(mode == Port_DO)
        {
            PORTS->P[port].TRIS &= ~mask;
        }
        else
        {
            PORTS->P[port].TRIS |= mask;
        }
    }
    else
    {
        PORTS->P[port].ANSEL |= mask;
    }
}

void Ports_ConfigOutputSelection(uint8 remap_id, dtOutFuncs func)
{
    uint8 reg_id = remap_id-32;
    if(reg_id < 15)
    {
        RPORS->RPOR_L[reg_id] = func;
    }
    else if((reg_id >= 144) && (reg_id <= 149))
    {
        reg_id -= 144;
        RPORS->RPOR_H[reg_id] = func;
    }
}

void Ports_ConfigInputSelection(uint8 remap_id, dtInFuncs func)
{
    RPINRS->R[func] = remap_id;
}

void Ports_SetPin(dtPort_pin pin, uint8 value)
{
    uint8 port = pin >> 4;
    uint8 pin_pos = (pin & 0x0F);
    uint16 tLat = PORTS->P[port].LAT & ~(1 << pin_pos);
    tLat |= (value != 0) << pin_pos;
    PORTS->P[port].LAT = tLat;
}

uint8 Ports_GetPin(dtPort_pin pin)
{
    uint8 port = pin >> 4;
    uint8 pin_pos = (pin & 0x0F);
    return (PORTS->P[port].PORT & (1 << pin_pos)) != 0;
}
