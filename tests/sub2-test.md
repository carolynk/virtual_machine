### case: negative solution
addimmediate r1 4 (91 04)
addimmediate r2 6 (92 06)
subtract r1 r2 r3 (51 23)
interrupt 0 (8000)
R1 == 4
R2 == 6
R3 == -2