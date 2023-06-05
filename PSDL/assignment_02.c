#include <xc.h>
#include<pic18f458.h>

void main(void) 
{
    int a[100];
    int sum =0;
    
    //bank 1
    BSR = 0x01;
    for(int i=0; i<100; i++)
    {
        a[i]=1;
        sum+=a[i];
    }
    //bank2
    BSR = 0x00;
    TMR0 = sum;
    return;
}
