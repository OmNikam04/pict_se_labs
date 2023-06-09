/*
Problem statement:
Study of Embedded C programming language (Overview, syntax, One simple program like addition of two numbers).

Input:Two numbers
Output:Addition/subtraction operations performed on given numbers

Additional task: 
Consider two 8-bit numbers stored in registers TMR0 and TMR1. Calculate TMR2=TMR0+TMR1. Choose the values such that after addition STATUS 
register is
i. 00H
ii. 04H
iii. 10H
iv. 05H
v. 18H
vi. 01H
vii. 02H
viii. 03H
ix. 09H
x. 13H
xi. 11H

5 STATUS registers bits needs to be conidered here are:
    4  3 2  1 0
    N OV Z DC C
    
For status register to be of value 00H:
  use input: TMR0 = 0x04 TMR1 = 0x06
  reason: 00h -> BINARY 0000 
          no flag enabled

For status register to be of value 04H:
  use input: TMR0 = 0x00 TMR1 = 0x00
  reason: 04h -> BINARY 0100 
          means zero flag enabled
          
For status register to be of value 10H:
  use input: TMR0 = 0x00 TMR1 = 0x00
  reason: 10h -> BINARY 10000 
          means zero flag enabled
          
For status register to be of value 02H:
  use input: TMR0 = 0x01 TMR1 = 0x0F
  reason: 02h -> BINARY 00000010 
          means DC flag enabled


Same way we need to find values for all other values. */

#include <xc.h>

void main(void) {
    TMR0 = 0x01;
    TMR1 = 0x0F;
    TMR2 = TMR1 + TMR0;
    TRISB = 0;
    PORTB = TMR2;
    return;
}

