// Test for input R1 = 3, R2 = 2

load Mult.asm,
output-file Mult00.out,
compare-to Mult00.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] 3,  // Set R1 (3)
set RAM[2] 2;  // Set R2 (2)
repeat 100 {
  ticktock;    // Run for 100 clock cycles
}
output;        // Output to file
