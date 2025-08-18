#include "T1_regdef.h"
#include "T1.h"

void T1_Init(dtT1Cfg cfg)
{
    dtT1CON tCon = T1->CON;
    tCon.U = 0;
    T1->CON = tCon;
    T1->PR1 = cfg.Cmp;
    T1->TMR1 = 0;
    tCon.B.TON = cfg.On;
    tCon.B.TCKPS = cfg.Prescaler;
    tCon.B.TCS = cfg.ExtClock;
    T1->CON = tCon;
}
