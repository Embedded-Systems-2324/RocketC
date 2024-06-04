/* Program to calculate some fibonacci numbers */
<<<<<<< HEAD
.org 0x10
=======
.org 0x0c
>>>>>>> d399122 (hexToCoe (first addr != 0 correction))
.equ VAR1, 100

INIT :      ;Init variables
LDI R0, #VAR1
LDI R1, #010b
LDI R2, #0x0B
LDI R3, #0AH
ADD R2, R0, R1

.equ VAR2, - 40+10

<<<<<<< HEAD
//BYTE_ZONE :
//.byte 23

.org 0x200

=======
>>>>>>> d399122 (hexToCoe (first addr != 0 correction))
LOOP :      //Computing Loop 
MOV R1, R0
MOV R0, R2
ADD R2, R0, R1
SUB R3, R3, #(11 + 4 - 5) + (VAR1)
BNE LOOP

RR R1, R2, R3
RR R1, R2, #30
RL R1, R2, R1

BRA $