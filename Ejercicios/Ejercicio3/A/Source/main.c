/* 
 * File:   main.c
 * Author: jecor
 *
 * Created on 9 de junio de 2023, 04:17 PM
 */

#include <xc.h>
#include "ConfigurationBits.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic18f4550.h>


//A. Enviar un mensaje.

/*Variables globales*/
char estado;

void Serial_begin(float baud);
uint8_t Serial_available(void);
void Serial_write(char caracter);
char Serial_read(void);
void Serial_print(char *s);
void Serial_println(char *s);

void initPort(void){
    //OSCCON=0x72;
    //ADCON1=0x0F;
    TRISBbits.RB2 = 0; //salidad, led
    LATB2 = 0;  //Inicialmente el led estará apagado
    Serial_begin(9600.0); //Iniciamos el puerto serial a 9600 baudios
    /*
    TRISC6=0;   //Pin Tx salida
    TRISC7=1;   //Pin Rx entrada
    SPBRG = 31;
    TXSTA =0x20;
    RCSTA =0x90;    
    */
}

void main(void) {
    
    initPort(); 
    while(1)
    {
        estado=Serial_read();
        
        if(estado=='1'){
            LATB2=1;
            Serial_println("1 -> Led encendido");
        }
        else if(estado=='0'){
            LATB2=0;
            Serial_println("0 -> Led apagado");
        }
        else{
            Serial_println("Ingresaste un dato erroneo");
        }
    }
    return;
}

/*Definicion de funciones*/


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
    if(PIR1bits.RCIF == 1)
        return 1;
    else
        return 0;
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