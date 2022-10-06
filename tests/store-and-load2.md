### case: with offset
addimmediate r1 9 (91 09) 
addimmediate r2 126 (92 7E)  ; address 126 
store r1 r2 4 (F1 24)  ; stores r1’s value into the memory pointed to by r2 + 4 bytes
interrupt 0 (8000)
interrupt 1 (8001)
R1 == 9
R2 == 126
MEM 130 == 9 ; Memory address 130

### case: with offset
subtract r1 r1 r1 (51 11)  ; set r1 to 0
subtract r2 r2 r2 (52 22)  ; set r1 to 0
addimmediate r2 126 (92 7E)
load r6 r2 4 (E1 24) ; loads r1 with the value pointed to by r2 plus 4 bytes
interrupt 0 (8000)
interrupt 1 (8001)
MEM 130 == 9	; Memory address 130
R2 == 126
R6 == 9
