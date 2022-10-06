addimmediate r1 1 (91 01) 	; 0001 R1
leftshift r1 1 (71 01) 	; 00 0001 = 01 in hex ; 0010 in R1
interrupt 0 (8000)
R1 == 2
