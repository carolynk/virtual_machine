### case: with offset
addimmediate r1 9 (91 09) 
addimmediate r2 126 (92 7E)  ; address 126 
store r1 r2 4 (F1 24)  ; stores r1’s value into the memory pointed to by r2 + 4 bytes
interrupt 0 (8000)
interrupt 1 (8001)
R1 == 9
R2 == 126
MEM 130 == 9 ; Memory address 130