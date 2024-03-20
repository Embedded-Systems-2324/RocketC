/* Program to calculate some fibonacci numbers */


INIT :      ;Init variables
LDI R0, #1
LDI R1, #010b
LDI R2, #0x00
LDI R3, #0AH
ADD R2, R0, R1

LOOP :      //Computing Loop 
MOV R1, R0
MOV R0, R2

INIT :      ;Init variables
ADD R2, R0, R1
SUB R3, R3, #1
BNE LOOP