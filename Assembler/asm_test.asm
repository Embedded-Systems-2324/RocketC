INIT:
    MOV R0, #1
    MOV R1, #0
    MOV R2, #0
    MOV R3, #10
    ADD R2, R0, R1

LOOP:
    MOV R1, R0
    MOV R0, R2
    ADD R2, R0, R1
    SUB R3, R3, #1
    BNE R3, LOOP

END