# Virtual Machine

Command line compiler for a simple assembly language

## Usage

You can see this demo virtual machine in action.

To compile the assembler and virtual machine:

```bash
gcc -o assembler src/assembler.c
gcc -o vm src/vm.c
```

Run the assembler on the tests. This will take the markdown files with instructions and compile them into hexcode for the virtual machine to read.

format: `./assembler [test] [binary filename]`

example: `./assembler tests/add-test.md bytes/add`

To run the vm:

Example command: `./vm bytes/add`

This test adds 4 + -6 and gets the result -2. The output will print out all the registers in which you can see both the operands and the result. See the command-line docs for all available operations.

The following commands are available. See the docs for details.

0. halt
1. add
2. and
3. divide
4. multiply
5. subtract
6. or
7. shift (right/left)
8. interrupt
9. addimmediate
10. branchifequal
11. branchifless
12. jump
13. iterateover
14. load
15. store
