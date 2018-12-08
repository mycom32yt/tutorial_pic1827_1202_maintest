/*
 * File:   main.c
 * Author: Y
 *
 * Created on 2018/12/02, 11:08
 */
#include <xc.h>
#pragma config FOSC = INTOSC, WDTE = OFF, PWRTE = ON,MCLRE = OFF, CP = OFF
#pragma config CPD = OFF, BOREN = ON, CLKOUTEN = OFF, IESO = ON,FCMEN = ON
#pragma config WRT = OFF,PLLEN = ON, STVREN = ON, BORV = LO, LVP = OFF

/******************************************************************************
 Function
******************************************************************************/
void main(void);
void __interrupt() intr(void);
void intr_tmr0(void);
void buzzer(void);

/******************************************************************************
 Interrupt
******************************************************************************/
void __interrupt() intr(void) {
    if (T0IF==1){intr_tmr0();}
}

/******************************************************************************
 TMR0 Interrupt(2.048ms)
******************************************************************************/
void intr_tmr0(void){
        T0IF = 0;	// TMR0 Interrupt Clear
}


void wait(void){
    unsigned int i;
    for(i=0; i<15000; i++){}
}

void main()
{
    unsigned int i;
    i = 0;
    // Option Registor Initialze
    OPTION_REG = 0x85;  // Prescaler = 64

    // Oscillator Initialize
    OSCCON = 0xf0;  // 4xPLL-Enable,8MHz = 32MHz

    // I/O Port Initialize
    ANSELA = 0x00;
    TRISA = 0xf0;
    PORTA = 0x0a;
    RA0 = 1; RA0 = 0;
    RA0 = 1; RA0 = 0;
    RA0 = 1; RA0 = 0;
    RA0 = 1; RA0 = 0;
    RA0 = 1; RA0 = 0;
    RA0 = 1; RA0 = 0;
    RA0 = 1; RA0 = 0;
    RA0 = 1; RA0 = 0;
    ANSELB = 0x00;
    TRISB = 0x00;
    PORTB = 0xff;

    // TMR0 Initialize
    TMR0 = 0x00;        // 32MHz/4/64/256 -> 2.048ms

    // Interrupt Initialize
    T0IE = 1;		// TMR0 Interrupt Enable
    GIE = 1;		// Interrupt Enable

    
    while(1)
    {
        RA1 = 1;
        for(i = 0; i < 10; i++){
            wait();
        }
        buzzer();
        RA1 = 0;
       
    }
} 


/******************************************************************************
 Buzzer
******************************************************************************/
void buzzer(void){
    unsigned int i;

    RA3 = 0;
    
    for (i=0; i<0x4000; i++){
        if ((i & 0x0010)==0)    {RA3 = 0;}
        else                    {RA3 = 1;}
    }

    RA3 = 0;
}