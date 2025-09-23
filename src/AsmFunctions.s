.text
.global _memcpy
_memcpy:
    CP0 W2
    BRA Z, memcpy_end
    DEC W2, W2
    REPEAT W2
    MOV.B [W0++], [W1++]
    memcpy_end:
    RETURN

.text
.global _memcpy_inverse
_memcpy_inverse:
    CP0 W2
    BRA Z, memcpy_inverse_end
    DEC W2, W2
    ADD W0, W2, W0
    ADD W1, W2, W1
    REPEAT W2
    MOV.B [W0--], [W1--]
    memcpy_inverse_end:
    RETURN

/* W0: destination pointer
   W1: character to be set
   W2: length to be set
*/
.text
.global _memset
_memset:
    CP0 W2
    BRA Z, memset_end
    DEC W2, W2
    REPEAT W2
    MOV.B W1, [W0++]
    memset_end:
    RETURN

.text
.global _strlen
_strlen:
    PUSH W1
    DEC W0, W1
    strlen_cycle:
    CP0.B [++W1]
    BRA NZ, strlen_cycle
    SUB W1, W0, W0
    POP W1
    RETURN

.text
.global _divU32byU16toU32
_divU32byU16toU32: /* W0-W1: dividend; W2: divisor */
    PUSH W4
    PUSH W5
    PUSH W6
    PUSH W7
    PUSH W8
    PUSH W9
    MOV.D W0, W4
    
    /* division of the high word */
    REPEAT #17
    DIV.UW W5, W2
    MOV W0, W7
    
    /* division of the remainder of the high word */
    MOV W1, W9
    CLR W8
    REPEAT #17
    DIV.UD W8, W2
    MOV W0, W6
    
    /* remainder of the whole high word */
    CLR W9
    MOV W1, W8
    
    /* division of the low word */
    REPEAT #17
    DIV.UW W4, W2
    
    /* remainder of the low word */
    ADD W1, W8, W8
    BRA C, _divU32byU16_remainder_calc
    
    CP W8, W2
    BRA LTU, _divU32byU16_round_pos_rem 
  _divU32byU16_remainder_calc:
    INC W6, W6
    ADDC W7, #0, W7
    SUB W8, W2, W8
  _divU32byU16_round_pos_rem:
    SL W8, W8
    BRA C, _divU32byU16_round_rem_inc
    CP W2, W8
    BRA GTU, _divU32byU16_copy_ret
  _divU32byU16_round_rem_inc:
    INC W6, W6
    ADDC W7, #0, W7
  _divU32byU16_copy_ret:
    ADD W6, W0, W0
    ADDC W7, #0, W1 /* adding carry */
    
    POP W9
    POP W8
    POP W7
    POP W6
    POP W5
    POP W4
    RETURN
    
.text
.global _divS32byS16toS32
_divS32byS16toS32:
    PUSH W3
    PUSH W4
    MOV W1, W3
    MOV W2, W4
    BTSS W3, #15
    BRA __divS32byS16_divisor_check
    COM W1, W1
    NEG W0, W0
    ADDC W1, #0, W1
  __divS32byS16_divisor_check:
    BTSC W4, #15
    NEG W2, W2
    
    RCALL _divU32byU16toU32
    
    BTSS W3, #15
    BRA __divS32byS16_divisor_res_check
    COM W1, W1
    NEG W0, W0
    ADDC W1, #0, W1
  __divS32byS16_divisor_res_check:
    BTSS W4, #15
    BRA __divS32byS16_end
    COM W1, W1
    NEG W0, W0
    ADDC W1, #0, W1
  __divS32byS16_end:
    POP W4
    POP W3
    RETURN

.text
.global _divU32byU16toU16
_divU32byU16toU16:
    PUSH W5
    PUSH W4
    MOV.D W0, W4
    REPEAT #17
    DIV.UD W4, W2

    /* Rounding of the result:
     * if the double of the remainder is greater than or equal to the
     * divisor, then incrementing the result by 1 */
    SL W1, #1, W1
    CPSLT W1, W2
    INC W0, W0
    POP W4
    POP W5
    RETURN

.text
.global _Dabler16Bit
_Dabler16Bit:
    CP0 W1
    BRA Z, InvalidPtr
    PUSH W2
    PUSH W3
    PUSH W4
    PUSH W5
    PUSH W6
    PUSH W7

    CLR W2
    CLR W3

    DO #15, DablerLoopEnd
    MOV #0x5, W4
    MOV #0x3, W5
    MOV #0, W7

    DO #3, DoubleDabler_lowest4digits
    LSR W2, W7, W6
    AND #0xF, W6
    CPSLT W6, W4
    ADD W2, W5, W2
    SL W5, #4, W5
    DoubleDabler_lowest4digits:
    ADD #4, W7

    MOV #0x5, W4
    CPSLT W3, W4
    ADD #3, W3

    SL W3, #1, W3
    BTSC W2, #15
    BSET W3, #0
    SL W2, #1, W2
    BTSC W0, #15
    BSET W2, #0
    DablerLoopEnd:
    SL W0, #1, W0

    MOV #0x30, W4
    CLR W6

    DoubleDabler_digit6Check:
    LSR W3, #4, W5
    CP0 W5
    BRA Z, DoubleDabler_digit5Check
    ADD.B W4, W5, [W1++]
    INC W0, W0

    DoubleDabler_digit5Check:
    AND W3, #0xF, W5
    CPSEQ W0, W6
    BRA DoubleDabler_digit5_copy
    CPSNE W5, W6
    BRA DoubleDabler_digit4Check
    DoubleDabler_digit5_copy:
    ADD.B W4, W5, [W1++]
    INC W0, W0

    DoubleDabler_digit4Check:
    LSR W2, #12, W5
    CPSEQ W0, W6
    BRA DoubleDabler_digit4_copy
    CPSNE W5, W6
    BRA DoubleDabler_digit3Check
    DoubleDabler_digit4_copy:
    ADD.B W4, W5, [W1++]
    INC W0, W0

    DoubleDabler_digit3Check:
    LSR W2, #8, W5
    AND W5, #0xF, W5
    CPSEQ W0, W6
    BRA DoubleDabler_digit3_copy
    CPSNE W5, W6
    BRA DoubleDabler_digit2Check
    DoubleDabler_digit3_copy:
    ADD.B W4, W5, [W1++]
    INC W0, W0

    DoubleDabler_digit2Check:
    LSR W2, #4, W5
    AND W5, #0xF, W5
    CPSEQ W0, W6
    BRA DoubleDabler_digit2_copy
    CPSNE W5, W6
    BRA DoubleDabler_digit1Check
    DoubleDabler_digit2_copy:
    ADD.B W4, W5, [W1++]
    INC W0, W0

    DoubleDabler_digit1Check:
    AND W2, #0xF, W5
    ADD.B W4, W5, [W1++]
    INC W0, W0

    CLR.B [W1]

    POP W7
    POP W6
    POP W5
    POP W4
    POP W3
    POP W2
    InvalidPtr:
    RETURN
    