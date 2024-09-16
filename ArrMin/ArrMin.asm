// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

@R0
M = 0          
@pointer
M = 0           

@R2
D = M           
@END            
D;JLE

@R1
A = M 
D = M 
@R0 
M = D

@R1
D = M
@pointer
M = D + 1

@idx
M = 1

(MIN)
@idx
D = M
@R2
D = D - M 
@END
D;JEQ

@pointer
A = M
D = M 
@positionPos
D;JGE
@positionNeg
0;JMP

(MinNew)
@pointer
A = M 
D = M 
@R0 
M = D

(LOOP)
@idx
M = M + 1
@pointer
M = M + 1
@MIN
0;JMP

(Double)
@pointer
A = M 
D = M 
@R0 
D = D - M 
@LOOP
D;JGE 
@MinNew
0;JMP

(positionNeg)
@R0
D = M 
@Double
D;JLT
@MinNew
0;JMP

(positionPos)
@R0
D = M
@Double
D;JGE
@LOOP
0;JMP

(END)
@END
0;JMP