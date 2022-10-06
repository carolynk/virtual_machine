### case: not equal (greater than) test
addimmediate r1 10 (91 0A)
addimmediate r2 5 (92 05)
branchifequal r1 r2 6 (A1 20 00 06) ; skip 4 bytes branch + 2 bytes instruction
halt (00 00) 
addimmediate r3 1 (93 01)
interrupt 0 (8000)
no result ; halted
