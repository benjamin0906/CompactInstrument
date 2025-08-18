memcpy:
    CP0 W2
    BRA Z, memcpy_end
    DEC W2, W2
    REPEAT W2
    MOV.B [W0] [W1]
    memcpy_end:
    RETURN


