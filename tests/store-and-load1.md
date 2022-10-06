### case: without offset
addimmediate r1 8 (91 08) 
addimmediate r2 126 (92 7E)  ; address 126 
store r1 r2 0 (F1 20)  ; stores r1’s value into the memory pointed to by r2
interrupt 0 (8000)
interrupt 1 (8001)
R1 == 8
R2 == 126
MEM 126 == 8 ; Memory address 126
### case: without offset
subtract r1 r1 r1 (51 11) 	; set r1 to 0
subtract r2 r2 r2 (52 22) 	; set r2 to 0
addimmediate r2 126 (92 7E)
load r1 r2 0 (E1 20) ; loads r1 with the value pointed to by r2
interrupt 0 (8000)
interrupt 1 (8001)
MEM 126 == 8 	; Memory address 126
R1 == 8
R2 == 126