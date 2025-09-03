#include "types.h"

uint8 Dabler16Bit(uint16 value, uint8 *Digits)
{
asm(
    "CP0 W1\n"
    "BRA Z, InvalidPtr\n"
    "PUSH W2\n"
    "PUSH W3\n"
    "PUSH W4\n"
    "PUSH W5\n"
    "PUSH W6\n"
    "PUSH W7\n"

    "CLR W2\n"
    "CLR W3\n"

    "DO #15, DablerLoopEnd\n"
    "MOV #0x5, W4\n"
    "MOV #0x3, W5\n"
    "MOV #0, W7\n"
    
    "DO #3, DoubleDabler_lowest4digits\n"
    "LSR W2, W7, W6\n"
    "AND #0xF, W6\n"
    "CPSLT W6, W4\n"
    "ADD W2, W5, W2\n"
    "SL W5, #4, W5\n"
    "DoubleDabler_lowest4digits:\n"
    "ADD #4, W7\n"

    /*"MOV W2, W6\n"
    "AND #0xF0, W6\n"
    "CPSLT W6, W4\n"
    "ADD W2, W5, W2\n"*/

    "MOV #0x5, W4\n"
    //"MOV #0x3, W5\n"
    
    //"DO #0, DoubleDabler_highest2digits \n"
    //"MOV W3, W6\n"
    //"AND W3, W7, W6\n"
    "CPSLT W3, W4\n"
    "ADD #3, W3\n"

    //"SL W4, #4, W4\n"
    //"DoubleDabler_highest2digits:\n"
    //"SL W5, #4, W5\n"

    /*"MOV W3, W6\n"
    "AND #0xF0, W6\n"
    "CPSLT W6, W4\n"
    "ADD W3, W5, W3\n"*/

    "SL W3, #1, W3\n"
    "BTSC W2, #15\n"
    "BSET W3, #0\n"
    "SL W2, #1, W2\n"
    "BTSC W0, #15\n"
    "BSET W2, #0\n"
    "DablerLoopEnd:\n"
    "SL W0, #1, W0\n"

    "MOV #0x30, W4\n"
    "CLR W6\n"

    "DoubleDabler_digit6Check:\n"
    "LSR W3, #4, W5\n"
    "CP0 W5\n"
    "BRA Z, DoubleDabler_digit5Check\n"
    "ADD.B W4, W5, [W1++]\n"
    "INC W0, W0\n"
    
    "DoubleDabler_digit5Check:\n"
    "AND W3, #0xF, W5\n"
    "CPSEQ W0, W6\n"
    "BRA DoubleDabler_digit5_copy\n"
    "CPSNE W5, W6 \n"
    "BRA DoubleDabler_digit4Check\n"
    "DoubleDabler_digit5_copy:\n"
    "ADD.B W4, W5, [W1++]\n"
    "INC W0, W0\n"

    "DoubleDabler_digit4Check:\n"
    "LSR W2, #12, W5\n"
    "CPSEQ W0, W6\n"
    "BRA DoubleDabler_digit4_copy\n"
    "CPSNE W5, W6\n"
    "BRA DoubleDabler_digit3Check\n"
    "DoubleDabler_digit4_copy:\n"
    "ADD.B W4, W5, [W1++]\n"
    "INC W0, W0\n"

    "DoubleDabler_digit3Check:\n"
    "LSR W2, #8, W5\n"
    "AND W5, #0xF, W5\n"
    "CPSEQ W0, W6\n"
    "BRA DoubleDabler_digit3_copy\n"
    "CPSNE W5, W6\n"
    "BRA DoubleDabler_digit2Check\n"
    "DoubleDabler_digit3_copy:\n"
    "ADD.B W4, W5, [W1++]\n"
    "INC W0, W0\n"


    "DoubleDabler_digit2Check:\n"
    "LSR W2, #4, W5\n"
    "AND W5, #0xF, W5\n"
    "CPSEQ W0, W6\n"
    "BRA DoubleDabler_digit2_copy\n"
    "CPSNE W5, W6\n"
    "BRA DoubleDabler_digit1Check\n"
    "DoubleDabler_digit2_copy:"
    "ADD.B W4, W5, [W1++]\n"
    "INC W0, W0\n"

    "DoubleDabler_digit1Check:\n"
    "AND W2, #0xF, W5\n"
    "ADD.B W4, W5, [W1++]\n"
    "INC W0, W0\n"

    "CLR.B [W1]\n"

    "POP W7\n"
    "POP W6\n"
    "POP W5\n"
    "POP W4\n"
    "POP W3\n"
    "POP W2\n"
    "InvalidPtr:"
    
);
}

/*uint8 Dabler16Bit(uint16 value, uint8 *Digits)
{
    uint32 bcd = 0;
    uint8 DigitNum = 8;
    uint8 looper = 0;
    for(looper = 0; looper < 16; looper++)
    {
        if((bcd & 0xF) >= 5) bcd += 3;
        if((bcd & 0xF0) >= 0x50) bcd += 0x30;
        if((bcd & 0xF00) >= 0x500) bcd += 0x300;
        if((bcd & 0xF000) >= 0x5000) bcd += 0x3000;
        if((bcd & 0xF0000) >= 0x50000) bcd += 0x30000;
        if((bcd & 0xF00000) >= 0x500000) bcd += 0x300000;
        bcd<<=1;
        if((value&0x8000) != 0) bcd |= 1;
        value <<= 1;
    }

    if((bcd&0xF0000000) == 0)
    {
        DigitNum--;
        if((bcd&0x0F000000) == 0)
        {
            DigitNum--;
            if((bcd&0x00F00000) == 0)
            {
                DigitNum--;
                if((bcd&0x000F0000) == 0)
                {
                    DigitNum--;
                    if((bcd&0x0000F000) == 0)
                    {
                        DigitNum--;
                        if((bcd&0x00000F00) == 0)
                        {
                            DigitNum--;
                            if((bcd&0x000000F0) == 0) DigitNum--;
                        }
                    }
                }
            }
        }
    }

    looper = 0;
    do
    {
        Digits[looper] = '0';
        switch (DigitNum)
        {
        case 8:
            Digits[looper] += bcd>>28;
            break;
        case 7:
            Digits[looper] += (bcd>>24)&0xF;
            break;
        case 6:
            Digits[looper] += (bcd>>20)&0xF;
            break;
        case 5:
            Digits[looper] += (bcd>>16)&0xF;
            break;
        case 4:
            Digits[looper] += (bcd>>12)&0xF;
            break;
        case 3:
            Digits[looper] += (bcd>>8)&0xF;
            break;
        case 2:
            Digits[looper] += (bcd>>4)&0xF;
            break;
        case 1:
            Digits[looper] += (bcd)&0xF;
            break;
        }
        looper++;
        DigitNum--;
    } while(DigitNum != 0);
    Digits[looper] = 0;
    return looper;
}*/
