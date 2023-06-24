/*
 * File:   main.c
 * Author: jeanf
 *
 * Created on 13 de junio de 2023, 08:48 PM
 */

/*Inclusión de librerías*/
#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "ConfigurationBits.h"
#include "lcd.h"
#include "adc.h"

/*Definiciones*/
#define TRIS_ANALOG TRISA
#define LAT_ANALOG  LATA
#define PORT_ANALOG PORTA
#define PIN_ANALOG1     0   //RA0 - AN0
#define PIN_ANALOG2     1   //RA1 - AN1
#define PIN_ANALOG3     2   //RA2 - AN2
#define PIN_ANALOG4     3   //RA3 - AN3
#define PIN_ANALOG5     5   //RA5 - AN4      

#define MASK_ANALOG ((1<<PIN_ANALOG1)|(1<<PIN_ANALOG2)|(1<<PIN_ANALOG3)|(1<<PIN_ANALOG4)|(1<<PIN_ANALOG5))

/*Variables Globales*/
uint16_t Data_Channel_0=0, Data_Channel_1=0;
char buffer_0[20], buffer_1[20];

/*Prototipo de funciones*/
void GPIO_Init();

/*Función principal*/
void main(void) {
    
    //Configurar GPIO's
    GPIO_Init();
    //Configurar LCD
    LCD_Init_4_Bits();
    LCD_Tx_Command(LCD_HOME);
    LCD_Put_String("    Ejercicio   ");
    LCD_Goto_XY(1, 2);
    LCD_Put_String(" Lectura de POT ");
    __delay_ms(2000);
    LCD_Tx_Command(LCD_CLEAR);
	LCD_Tx_Command(LCD_HOME);
    LCD_Put_String("ADC 0: 0 ");
    LCD_Goto_XY(1, 2);
    LCD_Put_String("ADC 1: 0 ");
    
    //Configurar ADC
    ADC_Config(ADC_Interr_Off);
    
    while(1)
    {   
        //Lectura e Impresión del AN0
        Data_Channel_0 = ADC_Read_Channel(AN_0);
        sprintf(buffer_0, "%d", Data_Channel_0);
        LCD_Goto_XY(7, 1);
		LCD_Put_String("    ");
        LCD_Goto_XY(7, 1);
        LCD_Put_String(buffer_0);
        __delay_ms(50);  
        
        //Lectura e Impresión del AN1
        Data_Channel_1 = ADC_Read_Channel(AN_1);
        sprintf(buffer_1, "%d", Data_Channel_1);
        LCD_Goto_XY(7, 2);
		LCD_Put_String("    ");
        LCD_Goto_XY(7, 2);
        LCD_Put_String(buffer_1);
        __delay_ms(50);  
    }
    
    return;
}

/*Definición de funciones*/

//Inicio de puertos
void GPIO_Init()
{   
    //Puerto analógico como entrada
    TRIS_ANALOG |= MASK_ANALOG;
}
