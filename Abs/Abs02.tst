// Test for input = 0

load Abs.asm,
output-file Abs02.out,
compare-to Abs02.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] 0;  // Set R1 to 0
repeat 100 {
  ticktock;    // Run for 100 clock cycles
}
set RAM[1] 0,  // Restore the value of R1
output;        // Output to file
