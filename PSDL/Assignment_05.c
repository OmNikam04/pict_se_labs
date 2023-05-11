// Aim : Write an Embedded C program for Timer programming ISR based buzzer on/off.

#include<pic18f4550.h>

int count =0;
int buzzer_on =0;

void __interrupt() buzzgobeep(){
    if(PIR1bits.TMR1IF==1){
        //INTCONbits.GIE=0;
        if(buzzer_on && count==10){
            buzzer_on = 0;
            PORTAbits.RA5 = 0;
            count=0;
        }
        if(!buzzer_on && count == 20){
            buzzer_on = 1;
            PORTAbits.RA5=1;
            count=0;
        }
        count++;
        TMR1=28038;
        
        PIR1bits.TMR1IF=0;
        // INTCONbits.GIE = 1;
        
    }
}

void main(void) {
    T1CON = 0XB0;
    TRISAbits.TRISA5 = 0;
    PORTAbits.RA5=0;
    
    PIE1bits.TMR1IE=1;
    PIR1bits.TMR1IF=0;
    INTCONbits.PEIE=1;
    INTCONbits.GIE=1;
    T1CONbits.TMR1ON=1;
    while(1);
    
    return;
}

