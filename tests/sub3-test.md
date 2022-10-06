### case: 2nd term negative ; 10 - (-2) = 12
addimmediate r1 10 (91 0A)
addimmediate r2 -2 (92 FE)
subtract r1 r2 r3 (51 23)
interrupt 0 (8000)
R1 == 10
R2 == -2
R3 == 12
