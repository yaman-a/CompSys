// Abs01.tst
// Test for input = 7

load Abs.asm,
output-file Abs01.out,
compare-to Abs01.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] 7;  // Set R1 to 7
repeat 100 {
  ticktock;    // Run for 100 clock cycles
}
set RAM[1] 7,  // Restore the value of R1
output;        // Output to file
