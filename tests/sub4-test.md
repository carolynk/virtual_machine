### case: 2 negative terms
addimmediate r1 -10 (91 F6)
addimmediate r2 -2 (92 FE) 
subtract r1 r2 r3 (51 23) ; -10 - (-2) = - 10 + 2 = -8
interrupt 0 (8000)
R1 == -10
R2 == -2
R3 == -8