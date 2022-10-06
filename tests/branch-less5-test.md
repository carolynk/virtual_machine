### case: 2 negative terms
addimmediate r1 -6 (91 FA)
addimmediate r2 -4 (92 FC)
branchifless r1 r2 6 (B1 20 00 06) ; skip one 2 bytes instruction
halt (00 00)
addimmediate r3 1 (93 01) 
interrupt 0 (8000)
R1 == -6
R2 == -4
R3 == 1 	; less than