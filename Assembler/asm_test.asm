/* Program to calculate some fibonacci numbers */

INIT :      ;Init variables
MOV R0, #1
MOV R1, #0000b
MOV R2, #0x00
MOV R3, #0AH
ADD R2, R0, R1

LOOP :      //Computing Loop 
MOV R1, R0
MOV R0, R2
ADD R2, R0, R1
SUB R3, R3, #1
BNE R3, LOOP
