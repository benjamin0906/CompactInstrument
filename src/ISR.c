#include "ISR_regdef.h"
#include "ISR.h"

void ISR_SetIsr(dtISRsrc src, dtISRen_dis val)
{
    uint8 reg_id = src >> 4;
    uint8 bit_id = src & 0xF;
    uint16 tIEC = ISR->IEC[reg_id];
    tIEC &= ~(1 << bit_id);
    tIEC |= (val == ISR_Enable) << bit_id;
    ISR->IEC[reg_id] = tIEC;
}

void ISR_GlobalEnable(void)
{
    ISR->INTCON2.B.GIE = 1;
}
