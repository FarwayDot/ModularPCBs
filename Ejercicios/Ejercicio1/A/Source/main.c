/*
 * File:   main.c
 * Author: jecor
 *
 * Created on 5 de junio de 2023, 12:10 AM
 */

//A. Presionar un pulsador, que se encienda el led,
// pasado un tiempo, se apaga el led.


#include <xc.h>
#include "ConfigurationBits.h"
#include <stdint.h>
#include <stdio.h>
#include <pic18f4550.h>


//A. Presionar un pulsador, que se encienda la secuencia (00,01,10,11)


char num = 1;


void initPort(void){
    //ADCON1bits.PCFG = 0x0F;
    LATB = 0;
    LATA = 0;
    TRISBbits.RB3 = 1; //entrada, pulsador
    TRISBbits.RB2 = 0; //salidad, led
    TRISAbits.RA4 = 0; //salidad, led //modificar
    //INTCON2bits.RBPU = 0;
}

void main(void) {
    
    initPort(); 
    
    while(1){ 
        
    if (PORTBbits.RB3==0) {
        while(PORTBbits.RB3==0);
        __delay_ms(10);
        num = num +1;
        if(num == 5){
            num = 1;
        }
    }
        
    switch(num){
        case 1:
            PORTBbits.RB2 = 0;
            PORTAbits.RA4 = 0;
            break;
        case 2:
            PORTBbits.RB2 = 0;
            PORTAbits.RA4 = 1;
            break;
        case 3:
            PORTBbits.RB2 = 1;
            PORTAbits.RA4 = 0;
            break;
        case 4:
            PORTBbits.RB2 = 1;
            PORTAbits.RA4 = 1;
            break;
    } 
    }
}


