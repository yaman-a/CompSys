// This file is based on part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: Mult.asm

// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

@R0
M = 0
@R1
D = M

@END
D;JEQ

@R2
D = M

@END
D;JEQ

@R2
D = M
@POSITIVE
D;JGT

D = !D
D = D + 1

(POSITIVE)
@count
M = D

(LOOP)
@R1
D = M
@R0
M = M + D

@count
M = M - 1
D = M
@LOOP
D;JGT

@R2
D = M

@NEG
D;JLT

(END)
@END
A;JMP

(NEG)
@R0
M = !M
M = M + 1
@END
A;JMP