/* 
 * File:   main.c
 * Author: jecor
 *
 * Created on 5 de junio de 2023, 05:58 PM
 */

#include <xc.h>
#include "ConfigurationBits.h"
#include <stdint.h>
#include <stdio.h>
#include <pic18f4550.h>


//B. Presionar un pulsador para aumentar n° de leds encendidos,
// presionar otro pulsador para disminuir


char num = 1;

void initPort(void){
    LATB = 0;
    LATA = 0;
    TRISBbits.RB4 = 1; //entrada, pulsador +
    TRISBbits.RB5 = 1; //entrada, pulsador -
    TRISBbits.RB3 = 0; //salidad, led 3
    TRISBbits.RB2 = 0; //salidad, led 2
    TRISAbits.RA4 = 0; //salidad, led 1
    //INTCON2bits.RBPU = 0; //pull up interno
    
}

void main(void) {
    initPort(); 
    while(1){ 
        
    if (PORTBbits.RB4==0) {
        while(PORTBbits.RB4==0);
        __delay_ms(10);
        num = num +1;
        if(num == 5){
            num = 1;
        }
    }
    if(PORTBbits.RB5==0) {
        while(PORTBbits.RB5==0);
        __delay_ms(10);
        num = num -1;
        if(num == 0){
            num = 4;
        }
    }
        
    switch(num){
        case 1:
            PORTBbits.RB3 = 0;
            PORTBbits.RB2 = 0;
            PORTAbits.RA4 = 0;
            break;
        case 2:
            PORTBbits.RB3 = 0;
            PORTBbits.RB2 = 0;
            PORTAbits.RA4 = 1;
            break;
        case 3:
            PORTBbits.RB3 = 0;
            PORTBbits.RB2 = 1;
            PORTAbits.RA4 = 1;
            break;
        case 4:
            PORTBbits.RB3 = 1;
            PORTBbits.RB2 = 1;
            PORTAbits.RA4 = 1;
            break;
    } 
    }
}


