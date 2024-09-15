// Test for a = -5, b = 8, c = 2

load AddSub.asm,
output-file AddSub02.out,
compare-to AddSub02.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[3]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] -5, // Set R1 (a = -5)
set RAM[2] 8,  // Set R2 (b = 8)
set RAM[3] 2;  // Set R3 (c = 2)
repeat 100 {
  ticktock;    // Run for 100 clock cycles
}
set RAM[1] -5, // Restore arguments
set RAM[2] 8,
set RAM[3] 2,
output;        // Output to file