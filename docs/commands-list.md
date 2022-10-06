# Commands

This virtual machine is based off of 16 simple instructions

## halt (opcode 0)

* Stops the CPU.
* Example: halt
* Instruction format: 3R (the register values don’t matter)

## add (opcode 1)

* Adds the values of 2 registers and places the answer in a third register.
* Example: add r1 r2 r3 ; r3 = r1 + r2
* Instruction format: 3R

## and (opcode 2)

* Preforms a bitwise and on 2 registers and stores the result in a third register
* Example: and r1 r2 r3 ; r3 = r1 & r2
* Instruction format: 3R

## divide (opcode 3)

* Divides the value of the first register by the second and places the answer in a third register. This is integer math with the fractional portion discarded.
* Example: divide r1 r2 r3 ; r3 = r1 / r2
* Instruction format: 3R

## multiply (opcode 4)

* Multiplies the value of the first register times the second and places the answer in a third register.
* Example: multply r1 r2 r3 ; r3 = r1 * r2
* Instruction format: 3R

## subtract (opcode 5)

* Subtracts the value of the second register from the first and places the answer in a third register.
* Example: subtract r1 r2 r3 ; r3 = r1 - r2
* Instruction format: 3R

## or (opcode 6)

* Preforms a bitwise OR on 2 registers and stores the result in a third register
* Example: or r1 r2 r3 ; r3 = r1 | r2
* Instruction format: 3R

## rightshift (opcode 7)

* Shifts the contents of the specified register right by the specified number of bits (0-31).
* Example: rightshift r1 10
* instruction format: sft

## leftshift (opcode 7)

* Shifts the contents of the specified register left by the specified number of bits (0-31).
* Example: leftshift r1 10
* instruction format: sft

## interrupt (opcode 8)

* Interrupts the CPU using a particular interrupt number. This could be used to jump between kernel mode and user mode or to support devices.
* Example: interrupt 17
* Instruction format: int

## addimmediate (opcode 9)

* Adds a signed 8 byte value to a register
* Example: addimediate r1 -127 ; adds -127 to r1
* Instruction format: ai

## branchifequal (opcode 10)

* Compares two registers – if they hold the same value, jump to an offset from the current program counter. The offset must be divisible by 2 and can be between -524,286 and 524,286
* Example: branchifequal r1 r2 1000 
* Instruction format: br

## branchIfless (opcode 11)

* Compares two registers – if the first is less than the second, jump to an offset from the current program counter. The offset must be divisible by 2 and can be between -524,286 and 524,286
* Example: branchifless r1 r2 1000 
* Instruction format: br

## jump (opcode 12)

* Jumps to the location specified in the instruction (0 – 536,870,911)
* Example: jump 1000
* instruction format: jmp

## iterateover (opcode 13)

* Iterateover is for walking linked lists. One register is selected as the pointer to the current node. An offset is added (unsigned) to the contents of that register and that address is fetched from main memory. If that address is not null (0), the current register receives the value fetched from memory and the program jumps BACKWARDS delta instructions.
* Example: interateover r1, 4, 20
* If memory at address 52 looks like this:
* This program will “walk” the linked list:
* sub r1 r1 r1 ; clear r1
* addimmediate r1 52 ; set r1 to the start address of the linked list
* load r2 r1 0 ; set r2 = what r1 points to (88 for the first iteration)
* interrupt 0 ; print all of the registers

* iterateover r1 4 4 ; Loop using r1, with the “next” pointer 4 bytes from the beginning, jumping 4 bytes (two instructions in this case) back for each successful iteration
* instruction format: iter

## load (opcode 14)

* Loads a register from the memory pointed to by another register offset by a value (-15 to 15)
* Example: load r1 r2 10 ; loads r1 with the value pointed to by r2 plus 10 bytes
* instruction format: ls

## store (opcode 15)

* Stores a register’s value into memory pointed to by another register offset by a value (-15 to 15)
* Example: store r1 r2 10 ; stores r1’s value into the memory pointed to by r2 plus 10 bytes
* instruction format: ls
