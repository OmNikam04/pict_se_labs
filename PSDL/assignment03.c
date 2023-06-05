
#include <xc.h>

void main(void) {
    
    TRISB = 0;
    TRISC = 0;
    
    TMR1L = 0X09;
    TMR1H = 0X07;
    
    
    int choice = 0xF;
    while(1){
        if(choice==1){
            TMR0 = TMR1L * TMR1H;
            PORTB = TMR0L;
            PORTC = TMR0H; 
        }else if(choice==2){
            PORTB = TMR1L / TMR1H;
            PORTC = TMR1L % TMR1H;
        }
    }
    
    return;
}
