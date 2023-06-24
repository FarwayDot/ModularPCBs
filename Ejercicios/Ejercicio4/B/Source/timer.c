
#include <xc.h>
#include <stdint.h>
#include "timer.h"

/*
 Formulas:
 * 
 *  tiempo = (4/FOSC) * PRESCALER * ( 65535 O 255 - TMR0:TMR0H)
 * 
 *                                  FOSC * tiempo
 *  TMR0H:TMR0L =  65535 O 255 -   --------------
 *                                  4 * PRESCALER
 *  FOSC = 20Mhz
 *  
 */

/**************************************Funciones para el temporizador********************************************/



void Timer0_Timer_Config(uint8_t bits, uint8_t prescaler_value,uint8_t interr)
{   
    //Deshabilitamos el temporizador
    T0CON &= ~(1<<7);
    //Timer0 como temporizador
    T0CON &= ~(1<<5); //T0CS
    //Con prescaler
    T0CON &= ~(1<<3); //PSA
    
    if(prescaler_value<=7)
    {   
        T0CON &= ~0x07;
        T0CON |= prescaler_value<<0; //T0PS
    }

    //8bits o 16bits
    switch(bits)
    {
        case 8:     T0CON |= (1<<6);break;     //8bits      T08BIT
        case 16:    T0CON &= ~(1<<6) ;break;   //16 bits    T08BIT
    }
    
    //Interrupciones interrupciones
    switch(interr)
    {
        case Interrup_On:   
        
        INTCON |= (1<<7); //GIE
        INTCON |= (1<<6); //PEIE
        INTCON |= (1<<5); //TMR0IE 
        break;

        case Interrup_Off:   
        INTCON &= ~(1<<7); //GIE
        INTCON &= ~(1<<6); //PEIE
        break;
    }
    
}

void Timer0_Update_Count(uint16_t temp_value)
{
    TMR0L = (uint8_t) (temp_value & 0x00FF);
    TMR0H = (uint8_t) ((temp_value>>8) & 0x00FF);
}

/**************************************Funciones para el contador********************************************/

void Timer0_Contador_Config(uint8_t interr)
{   
    //Deshabilitamos el temporizador
    T0CON &= ~(1<<7);
    //Timer0 con 8B
    T0CON |= (1<<6); //T0CS
    //Timer0 como contador
    T0CON |= (1<<5); //T0CS
    //Flanco de bajada
    T0CON |= (1<<4); //T0SE
    //Sin prescaler
    T0CON |= (1<<3); //PSA
    //Prescaler 0b000 -> 2
    T0CON &= ~(0x07<<0); //T0PS

    //Para entrar directo al estado de interrupción
    TMR0L = 255;

    switch(interr)
    {
        case Interrup_On:   
        
        INTCON |= (1<<7); //GIE
        INTCON |= (1<<6); //PEIE
        INTCON |= (1<<5); //TMR0IE   
        break;

        case Interrup_Off:   
        INTCON &= ~(1<<7); //GIE
        INTCON &= ~(1<<6); //PEIE
        break;
    }

}

/**************************************Funciones para el TIMER0 en general********************************************/

void Timer0_Start(void)
{      
    T0CON |= (1<<7);
}

uint8_t Timer0_Check_Flag(void)
{   
    //Leer el estado de la bandera
    if(INTCON & (1<<2)) //Revisar flag
    {
        return 1;
    }
    return 0;
}

void Timer0_Clean_Flag(void)
{   
    //Limpiar la bandera
    INTCON &= ~(1<<2);
}

