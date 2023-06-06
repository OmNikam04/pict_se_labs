
#include <xc.h>
#include<pic18f4550.h>

#define RS LATAbits.LA0 
#define EN LATAbits.LA1

void delay(unsigned int delay){
    for(unsigned int i = 0; i<delay; i++)
        for(unsigned int j = 0; j< 100; j++);
}

void sendCommand(unsigned char ch){
    RS = 0;
    LATB = ch;
    EN = 1; 
    delay(10);
    EN = 0;
    delay(10);
}

void sendData(unsigned char ch){
    RS = 1;
    LATB = ch;
    EN = 1; 
    delay(10);
    EN = 0;
    delay(10);
}

void initLCD(void){
    ADCON1 = 0X0F;
    TRISB = 0;// SET DATA PORT AS OUTPUT
    
    TRISAbits.RA0 = 0;
    TRISAbits.RA1 = 0;
    char cmds[5] = {0x38, 0x06, 0x0C, 0x01, 0x80};
    for(int i = 0; i<5 ; i++){
        sendCommand(cmds[i]);
    }
    delay(10);
}

int readTemp(void){
    ADCON0 = 0b00011101; // ADC on select channel
    ADCON0bits.GO_DONE = 1;// start conversion
    while(ADCON0bits.GO_DONE == 1);
    return ADRES;
}

void main(void) {
    initLCD();
    unsigned int temp ;
    while(1){
        temp = readTemp();
        temp = ((temp * 500)/1023);
        sendData(temp / 10 + 48);
        sendData(temp % 10 + 48);
        
        delay(10);
    }
    return;
}
