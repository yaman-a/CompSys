

load ArrMin.asm,
output-file ArrMin03.out,
compare-to ArrMin03.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[20]%D2.6.2 RAM[21]%D2.6.2 RAM[22]%D2.6.2 RAM[23]%D2.6.2 RAM[24]%D2.6.2;

set PC 0,
set RAM[0]  0,  // Set R0
set RAM[1]  0, // Set R1
set RAM[2]  10,  // Set R2
repeat 300 {
  ticktock;    // Run for 300 clock cycles
}
set RAM[1] 0,  // Restore arguments in case program used them
set RAM[2] 10,
output;        // Output to file