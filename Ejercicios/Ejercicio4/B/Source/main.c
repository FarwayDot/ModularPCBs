
/* Inclusión de librerías */
#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include "ConfigurationBits.h"
#include "lcd.h"
#include "timer.h"

/* Definiciones */

//Digital 1
#define TRIS_LED    TRISB
#define LAT_LED     LATB
#define PORT_LED    PORTB
#define LED0        2

#define TRIS_BUTTON    TRISA
#define LAT_BUTTON     LATA
#define PORT_BUTTON    PORTA
#define BUTTON0        4


//Cuenta para temporizador
#define TIMER_UPDATE    63035

/* Prototipo de funciones */
void GPIO_Config(void);

/* Función principal */
void main()
{       
    uint16_t cont_1ms=0;
    
    //Configuraci�n de bits
    GPIO_Config();
    
    //Configuraci�n del lcd
    LCD_Init_4_Bits();
	LCD_Tx_Command(LCD_HOME);
	LCD_Put_String("   Ejercicio   ");
    LCD_Goto_XY(1, 2);
    LCD_Put_String("    Contador    ");

     //Configuraci�n del Timer0 como contador e interrupcion
    Timer0_Contador_Config(Interrup_On);
    //Iniciamos el temporizador
    Timer0_Start();
    
    while(1)
    {   

    }
       
    return;
}

/* Definición de funciones */

// Configuración de entradas y salidas digitales
void GPIO_Config(void)
{   

    TRIS_LED &= ~(1<<LED0); //Salida
    LAT_LED &= ~(1<<LED0);

    TRIS_BUTTON |= (1<<BUTTON0);//Entrada
}

//Interrupcion
void __interrupt() ISR_Timer0(void)
{
    if(Timer0_Check_Flag())
    {
        Timer0_Clean_Flag();
        LAT_LED ^= (1<<LED0);
        Timer0_Update_Count(0x00FF);
    }

    return;
}