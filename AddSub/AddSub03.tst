// AddSub03.tst
// Test for a = 100, b = 50, c = 75

load AddSub.asm,
output-file AddSub03.out,
compare-to AddSub03.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[3]%D2.6.2;

set PC 0,
set RAM[0] 0,   // Set R0
set RAM[1] 100, // Set R1 (a = 100)
set RAM[2] 50,  // Set R2 (b = 50)
set RAM[3] 75;  // Set R3 (c = 75)
repeat 100 {
  ticktock;     // Run for 100 clock cycles
}
set RAM[1] 100, // Restore arguments
set RAM[2] 50,
set RAM[3] 75,
output;         // Output to file
