### case: equal
addimmediate r1 4 (91 04)
addimmediate r2 4 (92 04)
branchifless r1 r2 6 (B1 20 00 06) ; skip 4 bytes for branch + 2 bytes instruction
halt (00 00)
addimmediate r3 1 (93 01) 
interrupt 0 (8000)
no result	; not less than
