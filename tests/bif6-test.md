### case: not equal: same number except opposite signs
addimmediate r1 4 (91 04)
addimmediate r2 -4 (92 FC)
branchifequal r1 r2 6 (A1 20 00 06) ; skip 4 bytes past branch + 2 bytes next instruction
halt (00 00) 
addimmediate r3 1 (93 01)
interrupt 0 (8000)
no result ; halted
