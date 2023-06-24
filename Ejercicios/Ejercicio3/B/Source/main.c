/* 
 * File:   main.c
 * Author: jecor
 *
 * Created on 17 de junio de 2023, 12:34 AM
 */

#include <xc.h>
#include "ConfigurationBits.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//A. Enviar un mensaje.

/*Variables globales*/
char estado;

void initPort(void);
void Serial_begin(float baud); 
uint8_t Serial_available(void); 
void Serial_write(char caracter); 
char Serial_read(void);
void Serial_print(char *s);
void Serial_println(char *s);

char num = 1;

void main(void) {
    
    initPort(); 
    while(1)
    {
        
        if (PORTAbits.RA4==0) {
            while(PORTAbits.RA4==0);
            __delay_ms(10);
            num = num +1;
            if(num == 3){
                num = 1;
            }
        }
        
        switch(num){
            case 1:
                LATB2 = 1;
                Serial_println("Hola mundo");
                break;
            case 2:
                LATB2 = 0;
                Serial_println("Hasta luego");
                break;
        }
        __delay_ms(1000);
    }
    return;
}

/*Definicion de funciones*/
void initPort(void){
    //OSCCON=0x72;
    //ADCON1=0x0F;
    TRISBbits.RB2 = 0; //salidad, led
    LATB2=0;  //Inicialmente el led estará apagado
    TRISAbits.RA4 = 1; //pulsador
    Serial_begin(9600.0); //Iniciamos el puerto serial a 9600 baudios
    /*
    TRISC6=0;   //Pin Tx salida
    TRISC7=1;   //Pin Rx entrada
    SPBRG = 31;
    TXSTA =0x20;
    RCSTA =0x90;    
    */
}

void Serial_begin(float baud){
    float temp;
    TRISC6=0;   //Pin Tx salida
    TRISC7=1;   //Pin Rx entrada
    temp =((float)_XTAL_FREQ/(64*baud))-1;
    SPBRG = (uint8_t)temp; //31
    TXSTA |= (1<<5);
    RCSTA =0x90;       
}


uint8_t Serial_available(void){
    if(PIR1bits.RCIF == 1){
        return 1;}
    else{
        return 0;}
}
void Serial_write(char caracter){
    while(TXIF == 0);
    TXREG = caracter;
}
char Serial_read(void){
    while(RCIF==0);     /*Esperar por la bandera de interupcion*/
    if(OERR){
        CREN = 0;
        NOP();
        CREN = 1;
    }
    return RCREG;
}
void Serial_print(char *s){
    while(*s!='\0'){
        Serial_write(*s);
        s++;
    }
}
void Serial_println(char *s){
    while(*s!='\0'){
        Serial_write(*s);
        s++;
    }
    Serial_write('\n');// '\r' o '\n' segun tipo de terminal
}
