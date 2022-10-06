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
addimmediate r1 100 (91 64)  
load r2 r1 0 (E2 10)
interrupt 0 (8000) 
iterateover r1 4 4 (D1 04 00 04)

R2 == 45
R2 == 14
R2 == 53