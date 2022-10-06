addimmediate r1 2 (91 02) 		; 0010 in R1
rightshift r1 1 (71 21) ; 10 0001 = 21 in hex ; 0001 in R1
interrupt 0 (8000)
R1 == 1