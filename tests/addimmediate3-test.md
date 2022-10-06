### case: when original register is not 0
addimmediate r1 5 (91 05)
addimmediate r1 5 (91 05) ; 5 + 5 already in register = 10
interrupt 0 (8000)
R1 == 10