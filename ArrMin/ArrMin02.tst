// Test for input array [8]

load ArrMin.asm,
output-file ArrMin02.out,
compare-to ArrMin02.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[20]%D2.6.2;

set PC 0,
set RAM[0]  0,  // Set R0
set RAM[1]  20, // Set R1 (start of array)
set RAM[2]  1,  // Set R2 (length of array)
set RAM[20] 8;  // Set Arr[0]
repeat 300 {
  ticktock;    // Run for 300 clock cycles
}
set RAM[1] 20,  // Restore arguments in case program used them
set RAM[2] 1,
output;        // Output to file
