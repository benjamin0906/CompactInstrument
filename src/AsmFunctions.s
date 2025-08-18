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
