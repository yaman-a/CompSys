load Mult.asm,
output-file Mult01.out,
compare-to Mult01.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] 0,  // Set R1 (3)
set RAM[2] 60;  // Set R2 (2)
repeat 1000 {
  ticktock;    // Run for 1000 clock cycles
}
set RAM[1] 10,  // Restore arguments in case program used them
set RAM[2] 60,
output;        // Output to file
