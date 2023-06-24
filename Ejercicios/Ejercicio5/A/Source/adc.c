
#include <xc.h>
#include<stdio.h>
#include <stdint.h>
#include "ConfigurationBits.h"
#include "adc.h"

/*
 * Los registros de guardado son: ADRESH y ADRESL.
 * 
 * Luego de completar la conversi�n, el resultado se carga
 * en los registro de arriba.
 * 
 * GO/DONE se pone a cero autom�ticamente en este caso.
 * La bandera ADIF se activa autom�ticamente.
 * 
 * CONFIGURACIONES:
 * 
 * El canal se debe seleccionar antes de empezar la conversi�n.
 * Los puertos anal�gicos se deben configurar como entradas.
 * Se debe configurar el tiempo de adquisici�n. (Puede estar entre 
 * la configuracipon del GO/DONE y el inicio actual de converis�n)
 * Luego del tiempo de adquisici�n, ingresa a la parte de converis�n.
 * 
 * PASOS DATASHEET
 * 
 * CONFIGURAR ADC
 * Configurar voltaje de referencia ADCON1
 * Selecionar el canal ADCON0
 * Seleccionar el tiempo de adquisicion ADCON2
 * Seleccionar el reloj de conversi�n ADCON2
 * Habilitar el m�dulo ADC
 * 
 * INTERRUPCION
 * Limpiar ADIF (bandera)
 * Habilitar interrupci�n por ADC ADIE
 * Establecer GIE
 * 
 * CONVERSI�N
 * Esperar el tiempo de adquisici�n
 * 
 * Empezar conversion GO/DONE ADCON0
 * 
 * Esperar que se complete la conversi�n (polling GO/DONE bit)
 * o esperar por la interrupci�n
 * 
 * Leer el resultado ADRESH:ADRESL y limpiar la bandera ADIF
 * 
 * Para la siguienteconversi�n ir al los primeros pasos.
 * 
 * TAD = Tiempo de conversi�n: Se necesita m�nimo 3TAD antes de
 * la siguiente adquisici�n.
 * 
 * REQUERIMIENTOS PARA LA ADQUISICI�N DEL ADC
 * 
 * Luego de seleccionar el canal, se necesita muestrear la se�al
 * por lo menos un tiempo igual al m�nimo tiempo de adquisici�n 
 * permitido antes de empezar la conversi�n.
 * 
 * Por defecto se tiempo un tiempo de adquisici�n m�nimo base es
 * de TACQ = 2.45us, en registro est� definido en base a TAD
 * 
 * Cuando se coloca GO/DONE = 1, empieza el sampleo por un tiempo de
 * adquisici�n configurado. Luego, autim�ticamente empieza la conversi�n.
 * 
 * CONVERSION CLOCK
 * 
 * Se necesita como m�nimo 11.5 TAD po 10bits convertidos 
 * TADmin = 0.8us, TADmax = 25us
 * 
 * Luego de la conversi�n, se debe esperar 2TCY antes de la siguiente 
 * adquisici�n.(Entre este tiempo se puede seleccionar el chanal)
 * 
 */

void ADC_Config(uint8_t interr)
{   
    //Desahabilitar ADC
    ADCON0 &= ~(1<<0);
    //Justificaci�n a la derecha
    ADCON2 |= (1<<7);
    //VSS
    ADCON1 &= ~(1<<VCFG1);
    //VDD
    ADCON1 &= ~(1<<VCFG0);
    //PCFG
    ADCON1 |= 0x0A; //Desdel el AN0 hasta AN4
    //TACQm�n = 2.45us
    ADCON2 |= (0b011<<3); //6TAD=4.8us -> Para 20Mhz: TADm�n = 0.8us
    //TAD
    ADCON2 |= (0b101<<0); //Para 20Mhz: TADm�n = 0.8us
    //Limpiar ADIF
    ADC_Clear_Flag();
    
    //Interrupcion
    switch(interr)
    {
        case ADC_Interr_On:
            INTCON |= (1<<7); //GIE
            INTCON |= (1<<6); //PEIE
            PIE1 |= (1<<6); //ADIE
            break;
        case ADC_Interr_Off:
            PIE1 &= ~(1<<6); //ADIE
            break;
               
    }
        
}

uint16_t ADC_Read_Channel(uint8_t channel)
{   
    //Seleccionar canal
    ADCON0 &= ~0x3C;
    if(channel>=0 && channel<=12)
    {    //Liampiamos el canal
        ADCON0 |= (channel<<2);
    }
    //Delay por datasheet
    __delay_ms(5);
    //Habilitar ADC ADON
    ADCON0 |= (1<<0);
    //Delay por datasheet
    __delay_ms(5);
    //Iniciar la converis�n GO/DONE
    ADC_Start_Conversion();
    //Esperar a que termine la conversi�n
    ADC_Wait_Conversion();
    //Deshabilita el m�dulo ADC
    ADCON0 &= ~(1<<0); //Opcional
    
    return (((uint16_t)(ADRESH<<8))|((uint16_t)ADRESL));
}

void ADC_Clear_Flag(void)
{
    //Limpiar ADIF
    PIR1 &= ~(1<<6);
}

uint8_t  ADC_Check_Flag(void)
{   
    //Revisamos la bandera
    if(PIR1 & (1<<6))
    {
        return 1;
    }   
    return 0;
}

void ADC_Start_Conversion(void)
{   
    //Iniciar la converis�n GO/DONE
    ADCON0 |= (1<<1);
}

void ADC_Wait_Conversion(void)
{
    //Esperar a que termine la conversi�n
    while(ADCON0 & (1<<1));
}