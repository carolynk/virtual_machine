### case: subtract from 0
addimmediate r1 0 (91 00)
addimmediate r2 2 (92 02) 
subtract r1 r2 r3 (51 23) ; 0 - 2
interrupt 0 (8000)
R1 == 0
R2 == 2
R3 == -2