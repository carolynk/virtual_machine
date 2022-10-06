### case: without offset
addimmediate r1 8 (91 08) 
addimmediate r2 126 (92 7E)  ; address 126 
store r1 r2 0 (F1 20)  ; stores r1’s value into the memory pointed to by r2
interrupt 0 (8000)
interrupt 1 (8001)
R1 == 8
R2 == 126
MEM 126 == 8 ; Memory address 126

