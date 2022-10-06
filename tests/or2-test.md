### case: negative term
addimmediate r1 -8 (91 F8) 	; 1111 1000 or -8
addimmediate r2 9 (92 09) 	; 0000 1001 or 9
or r1 r2 r3 (61 23) 		; 1111 1001 or -7
interrupt 0 (8000)
R1 == -8
R2 == 9
R3 == -7
