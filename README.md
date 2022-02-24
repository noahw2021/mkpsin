# mkpsin
A markdown generator for instructions sets described using PSIN.


## PSIN
```
 Instructions in enum follow the below format
 NAME[tab]= 0xNN, // DESCRIPTION (NAME [(R|I,D):(PSZ,USZ)]):TISZ
 
 Where NAME is the Instruction's name
 Where DESCRIPTION is the Instruction's functional description
 Where (R|I) represents R, I, or F depending on if the value is a Register, Immediate or Floating (Special)
	Register.
 Where D is the Operand's name.
 Where PSZ is the allocated size of the operand in bits.
 Where USZ is the usable size of the operand in bits.
 Where TISZ is the total size of the instruction in bits.
 Where NN is the total size of the opcode. See example below.
 
 Differences between PSZ and USZ occur when needed to be used as padding when an instruction's argument size in bits not divisible by 8 (or byte size on architecture).
 
 Example:
 
 MOV[tab]= 0x00, // Moves an operand into a register (MOV [R:(4,8),DEST] [I:(64,64),SRC]):80
 
 Where "MOV" is the Instruction's name
 Where "Moves an operand into a register" is the Instruction's description
 Where "[R:(4,8),DEST]" signifies that the operand "DEST" is a register physically stored in 8 bits but only 4 should be used by the instruction.
 Where "I:(64,64),SRC]" signifies that the operand "SRC" is an immediate value physically stored in 64 bits and that all 64 bits are available to be used by the compiler.
 Where ":80" signifies that the instruction is in total 80 bits long. This is determined by (8 + 8 + 64), with 8 being the size of the opcode, 8 being the size of the 1st operand and 64 being the size of the 2nd operand.
 Where "00" signifies the opcode's value. May be larger or smaller than 8 bits. Zeros should be used to prefix the size if it cannot be represented (Each instruction must have the same opcode length).
```
