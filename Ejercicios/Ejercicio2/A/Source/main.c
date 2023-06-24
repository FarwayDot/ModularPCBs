/* 
 * File:   main.c
 * Author: jecor
 *
 * Created on 5 de junio de 2023, 06:54 PM
 */
#include <xc.h>
#include "ConfigurationBits.h"
#include <stdint.h>
#include <stdio.h>
#include <pic18f4550.h>


//B. Display 7 seg cat comun
// cuenta descendente.

uint8_t display[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};

void initPort(void){
    //ADCON1bits.PCFG = 0xFF; // Puertos en digital
    //LATAbits.LA0 = 0;
    
    //TRISE = 0; //Salida activadores del display
    TRISD=0; // Salida digitos display
    TRISAbits.RA4 = 1; //pulsador
    PORTD = 0;
}
    
void main(void) {
    initPort();
    
    uint8_t i=0;//,j=0;
    //PORTE = (1<<j);
    while(1){ 
        if (PORTAbits.RA4 == 0){
            __delay_ms(1000);
            
            for(i=10;i>=0;i--){
                PORTD = display[i];
                __delay_ms(500);
            }
          
            PORTD = 0;
        }
    }
    return;
}



