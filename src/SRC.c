#include "SRC_regdef.h"
#include "SRC.h"

void SRC_PllConfig(dtPllCfg cfg)
{
    SRC->PLLFBD.B.PLLDIV = cfg.M;
    SRC->CLKDIV.B.PLLPRE = cfg.N1;
    SRC->CLKDIV.B.PLLPOST = cfg.N2;
    
    /*SRC->OSCCONH.U = 0x78;
    SRC->OSCCONH.U = 0x9A;
    SRC->OSCCONH.B.NOSC = cfg.OscSel;*/
    __builtin_write_OSCCONH(cfg.OscSel);
    
    /*SRC->OSCCONL.U = 0x46;
    SRC->OSCCONL.U = 0x57;
    SRC->OSCCONL.B.OSWEN = 1;*/
    __builtin_write_OSCCONL(1);
    
    while(SRC->OSCCONH.B.COSC != cfg.OscSel);
    while(SRC->OSCCONL.B.LOCK != 1);
}

