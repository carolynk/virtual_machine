jump 10 (C0 00 00 0a) ; skip 4 bytes past jump + 6 bytes past next 3 instructions
addimmediate r4 1 (94 01) 	; changes r4 to 1
interrupt 0 (8000)
halt (00 00)
addimmediate r3 1 (93 01) 	; changes r3 to 1
branchifequal r1 r2 -8 (A1 2F FF F8) ; branch 8 bytes up, to add, print and halt
R1 == 1
R2 == 1
R3 == 1
R4 == 1