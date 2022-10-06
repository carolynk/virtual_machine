### case: less
addimmediate r1 4 (91 04)
addimmediate r2 6 (92 06)
branchifless r1 r2 6 (B1 20 00 06) ; skip one 2 bytes instruction
halt (00 00)
addimmediate r3 1 (93 01) 
interrupt 0 (8000)
R1 == 4
R2 == 6
R3 == 1 	; less than
