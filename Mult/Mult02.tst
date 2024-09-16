load Mult.asm,
output-file Mult02.out,
compare-to Mult02.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] -10,  // Set R1 (5)
set RAM[2] 3;  // Set R2 (0)
repeat 700 {
  ticktock;    // Run for 100 clock cycles
}
set RAM[1] -10,  // Restore arguments in case program used them
set RAM[2] 3,
output;        // Output to file
