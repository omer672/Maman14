.entry LOOP
MAIN: inc K
	mov D1.2, W
.extern W
	add r2,STR
LOOP: jmp W
	prn #-5
STR: .string "ab"
	sub r1,r4
	stop
.entry STR
K: .data 2,7
D1: .struct 7, "dc"	

