// Test for a = 10, b = 5, c = 3

load AddSub.asm,
output-file AddSub01.out,
compare-to AddSub01.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[3]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] 10, // Set R1 (a = 10)
set RAM[2] 5,  // Set R2 (b = 5)
set RAM[3] 3;  // Set R3 (c = 3)
repeat 100 {
  ticktock;    // Run for 100 clock cycles
}
set RAM[1] 10, // Restore arguments
set RAM[2] 5,
set RAM[3] 3,
output;        // Output to file