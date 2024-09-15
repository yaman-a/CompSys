// Test for input R1 = 7, R2 = 1

load Mult.asm,
output-file Mult02.out,
compare-to Mult02.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] 7,  // Set R1 (7)
set RAM[2] 1;  // Set R2 (1)
repeat 100 {
  ticktock;    // Run for 100 clock cycles
}
output;        // Output to file
