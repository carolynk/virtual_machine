### case: 2 negative terms
addimmediate r1 -8 (91 F8) 	; 1111 1000 or -8
addimmediate r2 -9 (92 F7) 	; 1111 0111 or -9
or r1 r2 r3 (61 23) 		; 1111 1111 or -1
interrupt 0 (8000)
R1 == -8
R2 == -9
R3 == -1