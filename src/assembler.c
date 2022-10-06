#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *ltrim(char *s) {
	while (*s == ' ' || *s == '\t') s++;
	return s;
}

char getRegister(char *text) {
	if (*text == 'r' || *text=='R') text++;
	return atoi(text);
}

int assembleLine(char *text, unsigned char* bytes) {
	text = ltrim(text);
	char *keyWord = strtok(text," ");
	// halt (opcode 0, 3R, 2 bytes) 
	if (strncmp("halt",keyWord, 4) == 0) { // ??? why not printing???
		bytes[0] = 0x00;
		bytes[1] = 00;
		return 2;
	}
	// add (opcode 1, 3R, 2 bytes)
	else if (strcmp("add",keyWord) == 0) {
		bytes[0] = 0x10;
		bytes[0] |= getRegister(strtok(NULL," "));
		bytes[1] = getRegister(strtok(NULL," ")) << 4 | getRegister(strtok(NULL," "));
		return 2;
	}
	// and (opcode 2, 3R, 2 bytes)
	else if (strcmp("and",keyWord) == 0) {
		bytes[0] = 0x20;
		bytes[0] |= getRegister(strtok(NULL," "));
		bytes[1] = getRegister(strtok(NULL," ")) << 4 | getRegister(strtok(NULL," "));
		return 2;
	}
	// divide (opcode 3, 3R, 2 bytes)
	else if (strcmp("divide",keyWord) == 0) {
		bytes[0] = 0x30;
		bytes[0] |= getRegister(strtok(NULL," "));
		bytes[1] = getRegister(strtok(NULL," ")) << 4 | getRegister(strtok(NULL," "));
		return 2;
	}
	// multiply (opcode 4, 3R, 2 bytes)
	else if (strcmp("multiply",keyWord) == 0) {
		bytes[0] = 0x40;
		bytes[0] |= getRegister(strtok(NULL," "));
		bytes[1] = getRegister(strtok(NULL," ")) << 4 | getRegister(strtok(NULL," "));
		return 2;
	}
	// subtract (opcode 5, 3R, 2 bytes)
	else if (strcmp("subtract",keyWord) == 0) {
		bytes[0] = 0x50;
		bytes[0] |= getRegister(strtok(NULL," "));
		bytes[1] = getRegister(strtok(NULL," ")) << 4 | getRegister(strtok(NULL," "));
		return 2;
	}
	// or (opcode 6, 3R, 2 bytes)
	else if (strcmp("or",keyWord) == 0) {
		bytes[0] = 0x60;
		bytes[0] |= getRegister(strtok(NULL," "));
		bytes[1] = getRegister(strtok(NULL," ")) << 4 | getRegister(strtok(NULL," "));
		return 2;
	}
	// rightshift (opcode 7, sft, 2 bytes)
	else if (strcmp("rightshift",keyWord) == 0) {
		bytes[0] = 0x70;
		bytes[0] |= getRegister(strtok(NULL," "));
		int set = 0x10;
		int shift = atoi(strtok(NULL," "));
		// printf("%i", set);
		bytes[1] = (set + ((shift & 0xF0000) >> 4)) << 1;
		bytes[1] |= shift & 0xFFFF;
		return 2;
	}
	// leftshift (opcode 7, sft, 2 bytes)
	else if (strcmp("leftshift",keyWord) == 0) {
		bytes[0] = 0x70;
		bytes[0] |= getRegister(strtok(NULL," "));
		int set = 0x00;
		int shift = atoi(strtok(NULL," "));
		// printf("%i", set);
		bytes[1] = (set + ((shift & 0xF0000) >> 4)) << 1;
		bytes[1] |= shift & 0xFFFF;
		return 2;
	}
	// interrupt (opcode 8, int, 2 bytes)
	else if (strcmp("interrupt",keyWord) == 0) {
		bytes[0] = 0x80;
		int interrupt = atoi(strtok(NULL," ")); // do we need for all 12?? spec?? or just 1 and 0?
		bytes[0] |= ((interrupt & 0xF00) >> 8);
		bytes[1] = interrupt;
		return 2;
	}	
	// addimmediate (opcode 9, ai, 2 bytes)
	else if (strcmp("addimmediate",keyWord) == 0) {
		bytes[0] = 0x90;
		bytes[0] |= getRegister(strtok(NULL," "));
		bytes[1] = atoi(strtok(NULL," "));
		return 2;
	}
	// branchifequal (opcode 10, br, 4 bytes) - A
	else if (strcmp("branchifequal",keyWord) == 0) {
		bytes[0] = 0xA0;
		bytes[0] |= getRegister(strtok(NULL," "));
		bytes[1] = getRegister(strtok(NULL," ")) << 4;
		int address = atoi(strtok(NULL," "));
		bytes[1] |= (address & 0xF0000) >> 16;
		bytes[2] = (address & 0xFF00) >> 8; 
		bytes[3] = (address & 0xFF); 
		return 4;
	}
	// branchifless (opcode 11, br, 4 bytes) - B
	else if (strcmp("branchifless",keyWord) == 0) {
		bytes[0] = 0xB0;
		bytes[0] |= getRegister(strtok(NULL," "));
		bytes[1] = getRegister(strtok(NULL," ")) << 4;
		int address = atoi(strtok(NULL," "));
		bytes[1] |= (address & 0xFF0000) >> 16;
		bytes[2] = (address & 0xFF00) >> 8; 
		bytes[3] = (address & 0xFF); 
		return 4;
	}
	// jump (opcode 12, jmp, 4 bytes) - C
	else if (strcmp("jump",keyWord) == 0) {
		bytes[0] = 0xC0;
		int address = atoi(strtok(NULL," "));
		bytes[0] |= (address & 0x0F000000) >> 24; 
		bytes[1] = (address & 0xFF0000) >> 16; 
		bytes[2] = (address & 0xFF00) >> 8; 
		bytes[3] = address & 0xFF;
		return 4;
	}
	// iterateover (opcode 13, iter, 4 bytes)
	else if (strcmp("iterateover",keyWord) == 0) {
		bytes[0] = 0xD0;
		bytes[0] |= getRegister(strtok(NULL," "));
		int address = atoi(strtok(NULL," "));
		int address1 = atoi(strtok(NULL," "));
		bytes[2] = address;
		bytes[3] |= address1;
		return 2;
	}
	// load (opcode 14, ls, 2 bytes)
	else if (strcmp("load",keyWord) == 0) {
		bytes[0] = 0xE0;
		bytes[0] |= getRegister(strtok(NULL," "));
		bytes[1] = getRegister(strtok(NULL," ")) << 4;
		bytes[1] |= atoi(strtok(NULL," "));
		return 2;
	}
	// store (opcode 15, ls, 2 bytes)
	else if (strcmp("store",keyWord) == 0) {
		bytes[0] = 0xF0;
		bytes[0] |= getRegister(strtok(NULL," "));
		bytes[1] = getRegister(strtok(NULL," ")) << 4;
		bytes[1] |= atoi(strtok(NULL," "));
		return 2;
	}
	else {
		return 0; 
	}

}

int main(int argc, char **argv) {

	if(argc<=1)
    {
        printf("Please enter arguments of the file to assemble and the assembled file.\n");
        printf("Example: passed/add3-test.md add3-out-test\n");
        exit(255);
    }

	FILE *src = fopen(argv[1],"r");
	FILE *dst = fopen(argv[2],"w");
	while (!feof(src)) {
		unsigned char bytes[4];
		char line[1000];
		printf ("about to read\n");
		if (NULL != fgets(line, 1000, src)) {
			printf ("read: %s\n",line);
			int byteCount = assembleLine(line,bytes);
			fwrite(bytes,byteCount,1,dst);
		}
	}
	fclose(src);
	fclose(dst);
	return 0;
}
