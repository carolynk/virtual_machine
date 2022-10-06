jump 6 	(C0 00 00 06) ; jump 4 past jump then 2 bytes to interrupt
addimmediate r1 1 (91 01) 	; changes r1 to 1, but should be jumped over
interrupt 0 (8000)
R1 == 0
