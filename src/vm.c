#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

/* ---------------------------------
 * Virtual Machine
 * --------------------------------- 
 * A virtual machine that takes 16 simple commands.
 * 
 */

/* ---------------------------------
 * CPU infrastructure
 * --------------------------------- 
 */
const int MEMORY_SIZE = 10000;
const int NUM_OF_REGISTERS = 16;
unsigned char memory[MEMORY_SIZE]; // 1 bytes per array place
unsigned char internalArray[4]; // a “current instruction” buffer.
int registers[NUM_OF_REGISTERS];

// internal registers
int pc = 0; // program counter 
int op1; // put first operand in here
int op2; // put second operand in here
int result;
FILE *assemblyFile;
bool halt = false; // flag for halt
int pointerLocation;
int immediate;
int opcode;
int offset;
int address;
int toStore;
int toLoad;
int iterateJump;
int pointer;
int negative;
int shift;
signed char converted;


/* ---------------------------------
 * Debugging function
 * --------------------------------- 
 */
void debugIt() {
	printf("start tests ------\n");
	printf("internalArray[0] is %x\n", internalArray[0]);
	printf("internalArray[1] is %x\n", internalArray[1]);
	printf("internalArray[2] is %x\n", internalArray[2]);
	printf("internalArray[3] is %x\n", internalArray[3]);
	printf("op1 is %x\n", op1);
	printf("op2 is %x\n", op2);
	printf("offset is %x\n", offset);
	printf("immediate is %x\n", immediate);
	printf("pc is %x\n", pc);
	for(int i = 0; i < NUM_OF_REGISTERS; i++) {
		printf("R%d == %d\n", i, registers[i]);
	}
	printf("end tests ------\n");
}

/* ---------------------------------
 * Memory functions
 * --------------------------------- 
 */

/*
 * Function:  createMemory 
 * --------------------
 * Allocates space for the virtual machine’s memory
 * reads the file and populates memory
 * starting at the beginning.
 */
void createMemory(char *inputFile) {
	int i, count = 0;
	// Get File
	assemblyFile = fopen(inputFile, "r");

	// error if no file exists
	if (assemblyFile == 0) {
		perror(inputFile);
		exit(2);
	} else {
		// put the data in the memory array
        fread(memory, 1, MEMORY_SIZE, assemblyFile);
	}
	fclose(assemblyFile);
}

/*
 * Function: clearRegisters
 * --------------------
 * set all registers to 0 to start
 */
void clearRegisters() {
	for (int i=0; i < NUM_OF_REGISTERS-1; i++) {
		registers[i] = 0;
	}
}

/*
 * Function: getRegister
 * --------------------
 * a nibble (or nybl) is 4 bits
 * 
 */

int getRegister(int nibble) {
	if (nibble == 1) {
		//printf("reg contains %d\n", registers[internalArray[0] & 0x0F]);		
		return registers[internalArray[0] & 0x0F];
	} 
	else if (nibble == 2) {
		return registers[internalArray[1] >> 4];
	}
	else {
		printf("only 0-1 are implemented\n");
 		return 0;
	}
}

/*
 * Function: printRegisters
 * --------------------
 * Print register number and contents
 */
void printRegisters() {
	for(int i = 0; i < NUM_OF_REGISTERS; i++) {
		printf("R%d == %d\n", i, registers[i]);
	}
}

/*
 * Function: dumpMemory
 * --------------------
 * Print memory for debugging
 */
void dumpMemory(int size) {
	for(int i = 0; i < size; i++) {
		printf("Mem%d == %x\n", i, memory[i]);
	}	
}

/*
 * Function: fetch 
 * --------------------
 * Read bytes from memory.
 * Store them in an internal array of bytes; just enough to do the next instruction
 * fetch single instruction - an array of 4 bytes (char)
 */
void fetch() {

	internalArray[0] = memory[pc]; // memory[pc - shifted];
	internalArray[1] = memory[pc + 1]; // memory [pc (second byte)]
	internalArray[2] = memory[pc + 2]; // memory [pc+1]
	internalArray[3] = memory[pc + 3];

	// change to put in array
	opcode = internalArray[0] >> 4;
	//printf("processing %x%x%x%x\n", internalArray[0], internalArray[1], internalArray[2], internalArray[3]);

}

/*
 * Function: dispatch
 * --------------------
 * Populate op1 op2 and other registers if appropriate.
 * Read only from the array of bytes from fetch.
 * Fetch any additional memory needed to complete the instruction.
 */
void dispatch() {
   	
	switch (internalArray[0] >> 4) {  // based on opcode
		case 0: 
		//3R
		case 1: 
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			//printf("dispatch 3R\n"); // for debugging
			op1 = getRegister(1);
			//printf("op1 at dispatch is %d\n", op1);
			op2 = getRegister(2);
		 	break;
		case 7: // sft
			//printf("dispatch sft\n"); // for debugging
			// op1 is register number for load or store
			// op2 is shift amount
			op1 = internalArray[0] & 0x0F;
			shift = (internalArray[1] & 0x20) >> 5;
			//printf("shift in dispatch is %x\n", shift);
			op2 = internalArray[1] & 0x1F;
			//debugIt();
		 	break;
		case 8: //int
			//printf("dispatch int\n"); // for debugging
		 	break;
		case 9: //ai
			op1 = getRegister(1);
			// debugIt();
			// printf("internalArray[1] at dispatch is %x\n", internalArray[1]);
			// printf("internalArray[1] at dispatch is %x\n", internalArray[1]);
			converted = (signed char)internalArray[1];
			immediate = converted;
			// printf("immediate at dispatch is %x\n", immediate);
			// printf("immediate at dispatch is %d\n", immediate);
			// negative = immediate & 0xF0;
			// printf("negative at dispatch is %x\n", immediate);
			// if (negative == 0x0F) {
			// 	immediate = 0xFFFFFF00 | immediate;
			// }
			// printf("op1 at dispatch is %d\n", op1);
			// printf("immediate after conditional is %x\n", immediate);
		 	break;
		case 10: //br
		case 11: 
			//printf("dispatch br\n"); // for debugging
			op1 = getRegister(1);
			op2 = getRegister(2);
			//debugIt();
			offset = ((signed char)internalArray[1] & 0x0F) << 16;
			offset |= (signed char)internalArray[2] << 8;
		  	offset |= (signed char)internalArray[3];
			break;
		case 12: //jmp
			//printf("dispatch jmp\n"); // for debugging
			immediate = (internalArray[0] & 0x0F) << 24;
			immediate |= internalArray[1] << 16; 
			immediate |= internalArray[2] << 8;
			immediate |= internalArray[3];
			printf("immediate at jmp dispatch %d\n", immediate);
			break;
		case 13: //iter
			//printf("dispatch iter\n"); // for debugging
			op1 = internalArray[0] & 0x0F; // register
			//debugIt();
			op2 = internalArray[1];
			iterateJump = (internalArray[2] << 8) + internalArray[3];
			//debugIt();
			//printf("offset is %d\n", offset);
			break;		
		case 14:
		case 15: //ls
			//printf("dispatch ls\n"); // for debugging
			op2 = getRegister(2); // get address from register
			offset = internalArray[1] & 0x0F;

		}
}

/*
 * Function: execute
 * --------------------
 * execute
 * Switch statement that “does the work” and stores the work into Result
 */
void execute() {
	switch (internalArray[0] >> 4) {
		case 0:
			//halt
			printf("halt program\n");
			exit(0);
			pc = pc + 2; // increment pc by 2
			halt = true;
		 	break;
		case 1:
			//add
			//printf("opcode 1: do add\n"); // for debugging
			result = op1 + op2;
			printf("op1 is %x\n", op1);
			printf("op2 is %x\n", op2);
			printf("result is %x\n", result);
			pc = pc + 2; // increment pc by 2
		 	break;
		case 2:
			// and
			//printf("opcode 2: do and\n"); // for debugging
			result = op1 & op2;
			pc = pc + 2; // increment pc by 2
		 	break;
		case 3:
			//printf("opcode 3: divide"); // for debugging
			result = op1 / op2;
			pc = pc + 2; // increment pc by 2
		 	break;
		case 4:
			//printf("opcode 4: multiply\n"); // for debugging
			result = op1 * op2;
			pc = pc + 2; // increment pc by 2
			break;
		case 5:
			//printf("opcode 5: subtract\n"); // for debugging
			result = op1 - op2;
			pc = pc + 2; // increment pc by 2
			break;
		case 6:
			//printf("opcode 6: or\n"); // for debugging
			result = op1 | op2;
			pc = pc + 2; // increment pc by 2
			break;
		case 7:
			//printf("opcode 7: right or left shift\n");
			printf("shift is %x\n", shift);
			if (shift == 1) { // right shift
				// op1 is register number for load
				// op2 is shift amount
				//debugIt();
				//printf("op2 for shift amt %x\n", op2);
				result = getRegister(op1) >> op2;
				//printf("result is %x\n", result);
			} else { // left shift
				result = getRegister(op1) << op2;
			}
			pc = pc + 2; // increment pc by 2
			break;
		case 8:
			//printf("opcode 8: Do interrupt\n"); // for debugging
			if((internalArray[1] & 0x0F) == 0) { // if interrupt 8000
				printf("\n-------\n");
				printf("Registers:\n");
				printRegisters();
				printf("-------\n");
			} else if((internalArray[1] & 0x0F) == 1) {
				for(int i = 0; i < 140; i++) {
					printf("Mem%d == %d\n", i, memory[i]);
				}	
			}
			// 
			pc = pc + 2; // increment pc by 2
			break;
		case 9:
			// addimmediate
			//printf("opcode 9: Do addimmediate\n"); // for debugging
			result = op1 + immediate;// add op1 + immediate
			//debugIt();
			pc = pc + 2; // increment pc by 2
		 	break;
		case 10:
			//printf("opcode 10: branchifequal\n"); // for debugging
			if ((op1 - op2) == 0 ){
				//debugIt();
				pc = pc + offset;
				//debugIt();
			}
			else {
				pc = pc + 4; // increment pc by 2
			}
			break;
		case 11:
			//printf("opcode 11: branchifless\n"); // for debugging
			if ((op1 - op2) < 0 ){
				//debugIt();
				pc = pc + offset;
				//debugIt();
			}
			else {
				pc = pc + 4; // increment pc by 2
			}
			break;
		case 12:
			//printf("opcode 12: jump\n"); // for debugging
			pc = immediate; // increment pc by 2
			break;
		case 13:
			//printf("opcode 13: iterateover\n"); // for debugging
			pointerLocation = registers[op1] + op2; //address of next pointer
			//printf("load address is %d\n", address); // for debugging
			//debugIt();
			pointer = memory[pointerLocation] << 24;
			pointer |= memory[pointerLocation+1] << 16;
			pointer |= memory[pointerLocation+2] << 8;
			pointer |= memory[pointerLocation+3];
			printf("pointer is %d\n", pointer); // for debugging
			//dumpMemory(130);

			if (pointer != 0) {
				pc = pc - iterateJump; // jump back to iterate over
				registers[internalArray[0] & 0x0F] = pointer;
				//dumpMemory(130);
				//printf("iterate\n"); // for debugging b 
			} else {
				pc = pc + 4;
				//printf("don't iterate\n"); // for debugging
			}
			break;
		case 14:
			//printf("opcode 14: load\n"); // for debugging
			address = op2 + offset;
			//printf("load address is %d\n", address); // for debugging
			pc = pc + 2; // increment pc by 2
			break;
		case 15:
			//printf("opcode 15: store\n"); // for debugging
			address = op2 + offset;
			pc = pc + 2; // increment pc by 2
			break;	
		default:
			halt = true;
		}
}

/*
 * Function: store
 * --------------------
 * Write result into final register or memory address.
 * Get register number from internal array
 * Put result into result register
 */
void store() {
		switch (internalArray[0] >> 4) {  // based on opcode
		case 0: 
		//3R
		case 1: 
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			registers[internalArray[1] & 0x0F] = result;
		 	break; 
		case 7: // sft
			registers[op1] = result;
		 	break;
		case 8: //int
		 	break;
		case 9: //ai
			registers[internalArray[0] & 0x0F] = result;
		 	break;
		case 10: //br
		case 11: 
			break;
		case 12: //jmp
			break;
		case 13: //iter
			break;		
		case 14: // load
			//debugIt();
			//printf("address is %d\n", address);
			toLoad = memory[address] << 24;
			toLoad |= memory[address+1] << 16;
			toLoad |= memory[address+2] << 8;
			//printf("toLoad is %d\n", toLoad);
			toLoad |= memory[address+3];

			registers[internalArray[0] & 0x0F] = toLoad;
		case 15: //store
		 	toStore = registers[internalArray[0] & 0x0F]; // reg and toStore is 32 bits
			// break into 4 bytes
			memory[address] = toStore >> 24; // one byte
			memory[address+1] = toStore >> 16; // one byte
			memory[address+2] = toStore >> 8; // one byte
		 	memory[address+3] = toStore; // one byte
			break;	
		}
}

int main(int argc, char **argv) {

	//Error if no file given
	if(argc != 2) {
		fprintf(stderr, "Usage: %s filename\n",  argv[0]);
		exit(1);
	}

	createMemory(argv[1]);
	clearRegisters();

	// Calls fetch, dispatch, execute, store 
	// until a flag indicating that HALT occurred.
	while (halt == false) {
		//debugIt();
		fetch();
		dispatch();
		execute();
		store();
	}
}