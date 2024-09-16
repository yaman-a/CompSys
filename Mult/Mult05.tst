// Test for input R1 = 4, R2 = 4

load Mult.asm,
output-file Mult05.out,
compare-to Mult05.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] 10,  // Set R1 (4)
set RAM[2] 3;  // Set R2 (4)
repeat 100 {
  ticktock;    // Run for 100 clock cycles
}
set RAM[1] 10,  // Restore arguments in case program used them
set RAM[2] 3,
output;        // Output to file
