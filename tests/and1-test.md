addimmediate r1 8 (91 08) 	; 0000 1000 or 8
addimmediate r2 9 (92 09) 	; 0000 1001 or 9
and r1 r2 r3 (21 23) 		; 0000 1000 or 8
interrupt 0 (8000)
R1 == 8
R2 == 9
R3 == 8