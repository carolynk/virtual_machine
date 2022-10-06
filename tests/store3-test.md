### case: with offset
addimmediate r1 127 (91 7F)  ; 127
interrupt 0 (8000)
addimmediate r1 127 (91 7F) ; 254
interrupt 0 (8000)
addimmediate r1 3 (91 03)  ; 257
interrupt 0 (8000)
addimmediate r2 126 (92 7e)  ; address 126 
store r1 r2 0 (F1 20)  ; stores r1’s value into the memory pointed to by r2
interrupt 0 (8000)
interrupt 1 (8001)
R1 == 257
R2 == 126
MEM 126 == 0;
MEM 127 == 0;
MEM 128 == 1;
MEM 129 == 1;
