.org 0x00
	JMP R0,#64

.org 0x4000
	HALT

.org 0x40
	LDI R2,#1023
	LDI R3,#1023
	LDI R1,#16384
	SUB R3,R3,#1
	STX R1,R3,#0
	LDI R31,:FUNCTION_main
	JMP R31,#0

FUNCTION_main:
	SUB R3,R3,#1
	SUB R3,R3,#1
	LDI R12,#6
	STX R12,R2,#-3
	LDI R12,#4
	ST R12,#0
	LDX R14,R2,#-3
	SUB R3,R3,#1
	STX R14,R3,#0
	LD R14,#0
	SUB R3,R3,#1
	STX R14,R3,#0
	SUB R3,R3,#1
	STX R2,R3,#0
	MOV R2,R3
	SUB R3,R3,#1
	STX R1,R3,#0
	LDI R14,:FUNCTION_foo
	JMPL R1,R14,#0
	SUB R3,R3,#1
	LDX R1,R3,#0
	ADD R3,R3,#1
	LDX R2,R3,#0
	ADD R3,R3,#1
	ADD R3,R3,#2
	MOV R12,R4
	STX R12,R2,#-2
	LDI R12,#0
	MOV R4,R12
	MOV R3,R2
	JMP R1,#0



FUNCTION_foo:
	SUB R3,R3,#1
	LDX R13,R2,#2
	LDI R14,#5
	LDI R12,#1
	CMP R13,R14
	BGT SKIP_0
	LDI R12,#0
SKIP_0:
	CMP R12,#0
	BEQ IF_FALSE_0
	LDX R13,R2,#2
	LDX R14,R2,#1
	ADD R12,R13,R14
	STX R12,R2,#-2
	BRA IF_EXIT_0
IF_FALSE_0:
	LDX R13,R2,#2
	ADD R12,R13,#30
	STX R12,R2,#-2
IF_EXIT_0:
	LDX R12,R2,#-2
	MOV R4,R12
	MOV R3,R2
	JMP R1,#0