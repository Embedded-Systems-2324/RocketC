/* Program to calculate some fibonacci numbers */
.org 0xff
.equ VAR1, 100

INIT :      ;Init variables
LDI R0, #VAR1
LDI R1, #010b
LDI R2, #0x0B
LDI R3, #0AH
ADD R2, R0, R1

.equ VAR2, - 40+10

//BYTE_ZONE :
//.byte 23

.org 0x2ff

LOOP :      //Computing Loop 
MOV R1, R0
MOV R0, R2
ADD R2, R0, R1
SUB R3, R3, #(11 + 4 - 5) + (VAR1)
BNE LOOP

BRA $