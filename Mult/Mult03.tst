// Test for input R1 = -2, R2 = 3

load Mult.asm,
output-file Mult03.out,
compare-to Mult03.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] -2, // Set R1 (-2)
set RAM[2] 3;  // Set R2 (3)
repeat 100 {
  ticktock;    // Run for 100 clock cycles
}
output;        // Output to file
