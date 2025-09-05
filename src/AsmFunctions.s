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
.global _divU32byU16
_divU32byU16: /* W0-W1: dividend; W2: divisor */
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
.global _divS32byS16
_divS32byS16:
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
    
    RCALL _divU32byU16 
    
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
    