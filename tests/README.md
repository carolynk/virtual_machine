# Unit Tests 

## Assumptions
* Assume interrupt works for all (except interrupt test)
* Assume registers are all zero at the start of each case, unless stated otherwise
* Headers in markdown - can be seen if opened as a .md file in a markdown editor, ignored by assembler


# Test: interrupt (8, int, 2 bytes)
interrupt 0 (8000)
R0...R15 == 0 ; should print out all registers
interrupt 1 (8001)
Memory locations ==  ; should print out memory locations


# Test: halt (0, 3R, 2 bytes)
halt (00 00)
interrupt 0 (8000) ; won't be reached, because it halted
no result


# Test: addimmediate (9, ai, 2 bytes)
### case: positive
addimmediate r1 4 (91 04)
interrupt 0 (8000)
R1 == 4
### case: negative
addimmediate r1 -4 (91 FC) ; -4 = 1111 1100
interrupt 0 (8000)
R1 == -4
### case: when original register is not 0
addimmediate r1 5 (91 05)
addimmediate r1 5 (91 05) ; 5 + 5 already in register = 10
interrupt 0 (8000)
R1 == 10


# Test: add (1, 3R, 2 bytes)
## Assume: addimmediate works
### case: positive 
addimmediate r1 4 (91 04)
addimmediate r2 6 (92 06)
add r1 r2 r3 (11 23)
interrupt 0 (8000)
R1 == 4
R2 == 6
R3 == 10
### case: negative 
addimmediate r1 -4 (91 FC)
addimmediate r2 6 (92 06)
add r1 r2 r3 (11 23)
interrupt 0 (8000)
R1 == -4
R2 == 6
R3 == 2
### case: negative term with negative solution
addimmediate r1 4 (91 04)
addimmediate r2 -6 (92 FA)
add r1 r2 r3 (11 23)
interrupt 0 (8000)
R1 == 4
R2 == -6
R3 == -2
### case: 2 negative terms
addimmediate r1 -4 (91 FC)
addimmediate r2 -6 (92 FA)
add r1 r2 r3 (11 23)
interrupt 0 (8000)
R1 == -4
R2 == -6
R3 == -10


# Test: subtract (5, 3R, 2 bytes)
## Assume: addimmediate works
addimmediate r1 6 (91 06)
addimmediate r2 4 (92 04)
subtract r1 r2 r3 (51 23)
interrupt 0 (8000)
R1 == 6
R2 == 4
R3 == 2
### case: negative solution
addimmediate r1 4 (91 04)
addimmediate r2 6 (92 06)
subtract r1 r2 r3 (51 23)
interrupt 0 (8000)
R1 == 4
R2 == 6
R3 == -2
### case: 2nd term negative ; 10 - (-2) = 12
addimmediate r1 10 (91 0A)
addimmediate r2 -2 (92 FE)
subtract r1 r2 r3 (51 23)
interrupt 0 (8000)
R1 == 10
R2 == -2
R3 == 12
### case: 2 negative terms
addimmediate r1 -10 (91 F6)
addimmediate r2 -2 (92 FE) 
subtract r1 r2 r3 (51 23) ; -10 - (-2) = - 10 + 2 = -8
interrupt 0 (8000)
R1 == -10
R2 == -2
R3 == -8
### case: subtract from 0
addimmediate r1 0 (91 00)
addimmediate r2 2 (92 02) 
subtract r1 r2 r3 (51 23) ; 0 - 2
interrupt 0 (8000)
R1 == 0
R2 == 2
R3 == -2


# Test: branchifequal (10 / A, br, 4 bytes)
## Assume: addimmediate, halt works
### case: equal test
addimmediate r1 4 (91 04)
addimmediate r2 4 (92 04)
branchifequal r1 r2 6 (A1 20 00 06) ; skip 4 bytes past branch + 2 bytes next instruction
halt (00 00) 
addimmediate r3 1 (93 01)
interrupt 0 (8000)
R1 == 4
R2 == 4
R3 == 1
### case: not equal (less than) test 
addimmediate r1 4 (91 04)
addimmediate r2 6 (92 06)
branchifequal r1 r2 6 (A1 20 00 06) ; skip 4 bytes branch + 2 bytes instruction
halt (00 00) 
addimmediate r3 1 (93 01)
interrupt 0 (8000)
no result ; halted
### case: not equal (greater than) test
addimmediate r1 10 (91 0A)
addimmediate r2 5 (92 05)
branchifequal r1 r2 6 (A1 20 00 06) ; skip 4 bytes branch + 2 bytes instruction
halt (00 00) 
addimmediate r3 1 (93 01)
interrupt 0 (8000)
no result ; halted
### case: equal with negative terms
addimmediate r1 -4 (91 FC)
addimmediate r2 -4 (92 FC)
branchifequal r1 r2 6 (A1 20 00 06) ; skip 4 bytes past branch + 2 bytes next instruction
halt (00 00) 
addimmediate r3 1 (93 01)
interrupt 0 (8000)
R1 == -4
R2 == -4
R3 == 1
### case: not equal, 2 negative terms
addimmediate r1 -4 (91 FC)
addimmediate r2 -5 (92 FB)
branchifequal r1 r2 6 (A1 20 00 06) ; skip 4 bytes past branch + 2 bytes next instruction
halt (00 00) 
addimmediate r3 1 (93 01)
interrupt 0 (8000)
no result ; halted
### case: not equal: same number except opposite signs
addimmediate r1 4 (91 04)
addimmediate r2 -4 (92 FC)
branchifequal r1 r2 6 (A1 20 00 06) ; skip 4 bytes past branch + 2 bytes next instruction
halt (00 00) 
addimmediate r3 1 (93 01)
interrupt 0 (8000)
no result ; halted
### case: branch to create a loop (negative jump)
### assume: addimmediate, add, jump, and halt works
jump 10 (C0 00 00 10) ; skip 4 bytes past jump + 6 bytes past next 3 instructions
addimmediate r4 1 (94 01) 	; changes r4 to 1
interrupt 0 (8000)
halt (00 00)
addimmediate r3 1 (93 01) 	; changes r3 to 1
branchifequal r1 r2 -8 (A1 2F FF F8) ; branch 8 bytes up, to add, print and halt
R1 == 0
R2 == 0
R3 == 1
R4 == 1


# Test: branchifless (11, br, 4 bytes)
### case: equal
addimmediate r1 4 (91 04)
addimmediate r2 4 (92 04)
branchifless r1 r2 6 (B1 20 00 06) ; skip 4 bytes for branch + 2 bytes instruction
halt (00 00)
addimmediate r3 1 (93 01) 
interrupt 0 (8000)
no result	; not less than
### case: less
addimmediate r1 4 (91 04)
addimmediate r2 6 (92 06)
branchifless r1 r2 6 (B1 20 00 06) ; skip one 2 bytes instruction
halt (00 00)
addimmediate r3 1 (93 01) 
interrupt 0 (8000)
R1 == 4
R2 == 6
R3 == 1 	; less than
### case: greater
addimmediate r1 6 (91 06)
addimmediate r2 4 (92 04)
branchifless r1 r2 6 (B1 20 00 06) ; skip one 2 bytes instruction
halt (00 00)
addimmediate r3 1 (93 01)
interrupt 0 (8000)
no result	; not less than - halted
### case: negative term
addimmediate r1 -6 (91 FA)
addimmediate r2 4 (92 04)
branchifless r1 r2 6 (B1 20 00 06) ; skip one 2 bytes instruction
halt (00 00)
addimmediate r3 1 (93 01) 
interrupt 0 (8000)
R1 == -6
R2 == 4
R3 == 1 	; less than
### case: 2 negative terms
addimmediate r1 -6 (91 FA)
addimmediate r2 -4 (92 FC)
branchifless r1 r2 6 (B1 20 00 06) ; skip one 2 bytes instruction
halt (00 00)
addimmediate r3 1 (93 01) 
interrupt 0 (8000)
R1 == -6
R2 == -4
R3 == 1 	; less than


# Test: multiply (4, 3R, 2 bytes)
## Assume: addimmediate works
addimmediate r1 5 (91 05)
addimmediate r2 2 (92 02)
multiply r1 r2 r3 (41 23)
interrupt 0 (8000)
R1 == 5
R2 == 2
R3 == 10
### case: negative term
addimmediate r1 5 (91 05)
addimmediate r2 -2 (92 FE)
multiply r1 r2 r3 (41 23)
interrupt 0 (8000)
R1 == 5
R2 == -2
R3 == -10
### case: 2 negative terms
addimmediate r1 -5 (91 FB)
addimmediate r2 -2 (92 FE)
multiply r1 r2 r3 (41 23) ; -5 x -2 = 10
interrupt 0 (8000)
R1 == -5
R2 == -2
R3 == 10
### case: multiply by 0
addimmediate r1 5 (91 05)
addimmediate r2 0 (92 00)
addimmediate r3 4 (93 04) ; set to 4, should be overwritten by result of multiply
multiply r1 r2 r3 (41 23)
interrupt 0 (8000)
R1 == 5
R2 == 0
R3 == 0


# Test: divide (3, 3R, 2 bytes)
## Assume: addimmediate works
addimmediate r1 6 (91 06)
addimmediate r2 2 (92 02)
divide r1 r2 r3 (31 23)
interrupt 0 (8000)
R1 == 6
R2 == 2
R3 == 3
### case: negative term
addimmediate r1 6 (91 06)
addimmediate r2 -2 (92 FE)
divide r1 r2 r3 (31 23)
interrupt 0 (8000)
R1 == 6
R2 == -2
R3 == -3
### case: 2 negative terms
addimmediate r1 -6 (91 FA)
addimmediate r2 -2 (92 FE)
divide r1 r2 r3 (31 23) ; -6 / -2 = 3
interrupt 0 (8000)
R1 == -6
R2 == -2
R3 == 3
### case: divide by zero (error?)
addimmediate r1 6 (91 06)
addimmediate r2 0 (92 00)
divide r1 r2 r3 (31 23)
interrupt 0 (8000)
Error - can't divide by 0


# Test: jump (12 / C, jmp, 4 bytes)
## Assume: addimmediate, add works
jump 6 	(C0 00 00 06) ; jump 4 past jump then 2 bytes to interrupt
addimmediate r1 1 (91 01) 	; changes r1 to 1, but should be jumped over
interrupt 0 (8000)
R1 == 0
<!-- ### case: negative jump
## Assume: addimmediate, add, branchifequal, and halt works
addimmediate r1 1 (91 01)
addimmediate r2 1 (92 01)
branchifequal r1 r2 10 (A1 20 00 0A) ; skip 4 bytes past branch + 6 bytes past next 3 instructions
addimmediate r4 1 (94 01) 	; changes r4 to 1
interrupt 0 (8000)
halt (00 00) 
addimmediate r3 1 (93 01) 	; changes r3 to 1
jump -8	(CF FF FF F8) ; jump 8 bytes up, to add, print and halt
R1 == 1
R2 == 1
R3 == 1
R4 == 1 --> BAD TEST


# Test: leftshift (7, sft, 2 bytes)
## Assume: addimmediate works
addimmediate r1 1 (91 01) 	; 0001 R1
leftshift r1 1 (71 01) 	; 00 0001 = 01 in hex ; 0010 in R1
R1 == 2


# Test: rightshift (7, sft, 2 bytes)
## Assume: addimmediate works
addimmediate r1 2 (91 02) 		; 0010 in R1
rightshift r1 1 (71 21) ; 10 0001 = 21 in hex ; 0001 in R1
R1 == 1


# Test: and (2, 3R, 2 bytes)
## Assume: addimmediate works
addimmediate r1 8 (91 08) 	; 0000 1000 or 8
addimmediate r2 9 (92 09) 	; 0000 1001 or 9
and r1 r2 r3 (21 23) 		; 0000 1000 or 8
interrupt 0 (8000)
R1 == 8
R2 == 9
R3 == 8
### case: negative term
addimmediate r1 -8 (91 F8) 	; 1111 1000 or -8
addimmediate r2 9 (92 09) 	; 0000 1001 or 9
and r1 r2 r3 (21 23) 		; 0000 1000 or 8
interrupt 0 (8000)
R1 == -8
R2 == 9
R3 == 8
### case: 2 negative terms
addimmediate r1 -8 (91 F8) 	; 1111 1000 or -8
addimmediate r2 -9 (92 F7) 	; 1111 0111 or -9
and r1 r2 r3 (21 23) 		; 1111 0000 or -16
interrupt 0 (8000)
R1 == -8
R2 == -9
R3 == -16

# Test: or (6, 3R, 2 bytes)
## Assume: addimmediate works
addimmediate r1 8 (91 08) 	; 0000 1000 or 8
addimmediate r2 9 (92 09) 	; 0000 1001 or 9
or r1 r2 r3 (61 23) 		; 0000 1001 or 9
interrupt 0 (8000)
R1 == 8
R2 == 9
R3 == 9
### case: negative term
addimmediate r1 -8 (91 F8) 	; 1111 1000 or -8
addimmediate r2 9 (92 09) 	; 0000 1001 or 9
or r1 r2 r3 (61 23) 		; 1111 1001 or -7
interrupt 0 (8000)
R1 == -8
R2 == 9
R3 == -7
### case: 2 negative terms
addimmediate r1 -8 (91 F8) 	; 1111 1000 or -8
addimmediate r2 -9 (92 F7) 	; 1111 0111 or -9
or r1 r2 r3 (61 23) 		; 1111 1111 or -1
interrupt 0 (8000)
R1 == -8
R2 == -9
R3 == -1



# Test: store and load
## store (15 / F, ls, 2 bytes)
### case: without offset
addimmediate r1 8 (91 08) 
addimmediate r2 126 (92 7E)  ; address 126 
store r1 r2 0 (F1 20)  ; stores r1’s value into the memory pointed to by r2
interrupt 0 (8000)
interrupt 1 (8001)
R1 == 8
R2 == 126
MEM 126 == 8 ; Memory address 126
### case: with offset
addimmediate r1 9 (91 09) 
addimmediate r2 126 (92 7E)  ; address 126 
store r1 r2 4 (F1 24)  ; stores r1’s value into the memory pointed to by r2 + 4 bytes
interrupt 0 (8000)
interrupt 1 (8001)
R1 == 9
R2 == 130
MEM 130 == 9 ; Memory address 130

## load (14 / E, ls, 2 bytes)
## depends on previous store instructions
### case: without offset
subtract r1 r1 r1 (51 11) 	; set r1 to 0
addimmediate r2 126 (92 7E)
load r1 r2 0 (E1 20) ; loads r1 with the value pointed to by r2
interrupt 0 (8000)
interrupt 1 (8001)
MEM 126 == 8 	; Memory address 126
R1 == 8
R2 == 126
### case: with offset
subtract r1 r1 r1 (51 11)  ; set r1 to 0
addimmediate r2 126 (92 7E)
load r1 r2 4 (E1 24) ; loads r1 with the value pointed to by r2 plus 4 bytes
interrupt 0 (8000)
interrupt 1 (8001)
MEM 130 == 9	; Memory address 130
R1 == 9
R2 == 130



# Test: iterateover (13 / D, iter, 4 bytes)
## create linked list
### 100 - 45
### 104 - 92 ; next address
### 92 - 14
### 96 - 108
### 108 - 53
### 112 - 0 ; null

##node 1
### 100 - 45
### 104 - 92 ; next address
addimmediate r2 100 (92 64)	    ; 100 - put initial address 100 into r2
addimmediate r1 45 (91 2D)		; 45 - put 1st value (45) into r1
addimmediate r3 92 (93 5C)		; 92 - put 1st link pointer (92) into r3
store r1 r2 0 (F1 20) 		; store 1st value (45) into 100
store r3 r2 4 (F3 24) 		; store 1st link address (92) into 104

## reset r1 r2 r3
subtract r1 r1 r1 (51 11)  ; set r1 to 0
subtract r2 r2 r2 (52 22)  ; set r2 to 0
subtract r3 r3 r3 (53 33)  ; set r3 to 0

##node 2
### 92 - 14
### 96 - 108 ; next address
addimmediate r2 92 (92 5C)	    ; 92 - put address for 2nd value in r2
addimmediate r1 14 (91 0E)		; 14 - put 2nd value (14) into r1
addimmediate r3 108 (93 6C)		; 108 - put 2nd link pointer (108) into r3
store r1 r2 0 (F1 20) 		; store 2nd value (14) into 92
store r3 r2 4 (F3 24) 		; store 2nd link address (108) into 96

## reset r1 r2 r3
subtract r1 r1 r1 (51 11)  ; set r1 to 0
subtract r2 r2 r2 (52 22)  ; set r2 to 0
subtract r3 r3 r3 (53 33)  ; set r3 to 0

##node 3
### 108 - 53
### 112 - 0 ; null pointer
addimmediate r2 108 (92 6C)	    ; 108 - put address for 3nd value in r2
addimmediate r1 53 (91 35)		; 53 - put 3rd value (53) into r1
addimmediate r3 0 (93 00)		; 0 - put 3rd link pointer (0) into r3
store r1 r2 0 (F1 20) 		; store 3rd value (53) into 108
store r3 r2 4 (F3 24) 		; store 3rd link address (0) into 112

## reset r1 r2 r3
subtract r1 r1 r1 (51 11)  ; set r1 to 0
subtract r2 r2 r2 (52 22)  ; set r2 to 0
subtract r3 r3 r3 (53 33)  ; set r3 to 0

## run iterateover the linked list
addimmediate r1 100 (91 64) ; set r1 to the start address of the linked list
load r2 r1 0 (E2 10) ; set r2 = what r1 points to (45 for the first iteration)
interrupt 0 (8000) ; print all of the registers
iterateover r1 4 4 (D1 44)	; Loop using r1, 4 bytes to the pointer, 4 bytes to jump back

R2 == 45
R2 == 14
R2 == 53
