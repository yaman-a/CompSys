// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

@R1
D = M - 1
@R2
D = M + D
@LAST
M = D
@R2
D = M
@END
D;JLE

(OUT)
@R1
D = M
@LAST
D = D - M 
@END
D;JGT
@R1
D = M
@R3
M = D + 1

(IN)
@R3
D = M
@LAST
D = D - M
@INEND
D;JGT
@R3
A = M
D = M
@PositionPos
D;JGE
@PositionNeg
0;JMP

(SWAP)
@R1
A = M
D = M
@temp
M = D
@R3
A = M
D = M
@R1
A = M
M = D
@temp
D = M
@R3
A = M
M = D

(ITLOOP)
@R3
M = M + 1
@IN
0;JMP

(INEND)
@R1
M = M + 1
@OUT
0;JMP

(DBL)
@R3
A = M
D = M
@R1
A = M
D = M
@ITLOOP
D;JGE
@SWAP
0;JMP

(PositionPos)
@R1
A = M
D = M
@DBL
D;JGE
@ITLOOP
0;JMP

(END)
@R0
M = -1
@END
0;JMP