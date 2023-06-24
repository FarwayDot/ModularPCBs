/*
 * File:   main.c
 * Author: jeanf
 *
 * Created on 14 de junio de 2023, 10:56 PM
 */

/*Inclusión de librerías*/
#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
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
uint16_t Data_Channel_0=0;
uint16_t Data_Channel_1=0;
float Temp_C = 0.0;
uint16_t Light = 0;

char buffer_0[20];
char buffer_1[20];

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
    LCD_Put_String("Lectura de Sens.");
    __delay_ms(2000);
    LCD_Tx_Command(LCD_CLEAR);
	LCD_Tx_Command(LCD_HOME);
	LCD_Put_String("Temp.:        C");
    LCD_Goto_XY(1, 2);
    LCD_Put_String("Int. Luz: 0 ");
    
    //Configurar ADC
    ADC_Config(ADC_Interr_Off);
    
    while(1)
    {   
        //Lectura e Impresión del sensor de temperatura
        Data_Channel_0 = ADC_Read_Channel(AN_0);
        //Conversión
        Temp_C = (uint16_t)((((Data_Channel_0)*5.0)/1023.0)*100);     
        sprintf(buffer_0, "%.1f", Temp_C);
        //Impresión en LCD
        LCD_Goto_XY(10, 1);
		LCD_Put_String("     ");
        LCD_Goto_XY(10, 1);
        LCD_Put_String(buffer_0);
        __delay_ms(100);  
        
        //Lectura e Impresión del sensor de luz
        Light = ADC_Read_Channel(AN_1);
        sprintf(buffer_1, "%d", Light);
        //Impresión en LCD
        LCD_Goto_XY(10, 2);
        LCD_Put_String("      ");
        LCD_Goto_XY(10, 2);
        //LCD_Put_String(buffer_1);
        if(Light<300)
        {
           LCD_Put_String("Low"); 
        }
        else if(Light>300 && Light<600)
        {
            LCD_Put_String("Medium"); 
        }
        else if(Light>600)
        {
            LCD_Put_String("High"); 
        }
        __delay_ms(100);  
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
