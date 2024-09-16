// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

@R1
D=M - 1

@SORTED
D;JLE

@R2
D=M

@SORTED
D;JLE

(MainLoop)
@R2
D = M
@R5
M = D

@R1
A=M
D=M

@R0
M=D

@R4
M = 0

(Loop)

@R5
D = M - 1

@R1
A = M + D
D = M

@R7
M = D

@BPOS
D;JGE

@R0
D = M
@SwitchElements
D;JGE

@NNPP
A;JMP

(BPOS)
@R0
D = M
@keepTemp
D;JLE
(NNPP)
@R7
D = M
@R0
D = M-D

@keepTemp
D;JLE

(SwitchElements)
@R7
D = M

@R0
M=D

@R5
D = M

@R4 
M = D-1

(keepTemp)
@R5
MD = M-1


@Loop
D-1;JGT

@R4
D = M

@R1
D = M + D

@R6
M = D

@R1
A = M
D = M
@R6
A = M
M = D
@R0
D = M
@R1
A = M
M = D

@R1
M = M + 1

@R2
M = M - 1
D = M - 1

@MainLoop
D;JGT


(SORTED)
@R0
M = -1

(END)
@END
A;JMP