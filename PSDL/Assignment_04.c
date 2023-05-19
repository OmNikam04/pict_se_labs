#include <pic18f4550.h>

void delay(){
    T0CON = 0x01;
    TMR0 = 65316;
    T0CONbits.TMR0ON = 1;
    INTCONbits.TMR0IF = 0;

    while(INTCONbits.TMR0IF == 0);
    T0CONbits.TMR0ON = 0;
    INTCONbits.TMR0IF = 0;
    return;
}

void main() {
    TRISB = 0;
    PORTB = 0x55;
    while(1){
        delay();
        PORTB = ~PORTB;
    }
    return;
}
