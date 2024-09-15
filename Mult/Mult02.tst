// Test for input R1 = 5, R2 = 0

load Mult.asm,
output-file Mult01.out,
compare-to Mult01.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] 5,  // Set R1 (5)
set RAM[2] 0;  // Set R2 (0)
repeat 100 {
  ticktock;    // Run for 100 clock cycles
}
output;        // Output to file
