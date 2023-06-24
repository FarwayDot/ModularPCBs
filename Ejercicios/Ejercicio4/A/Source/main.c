
#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include "ConfigurationBits.h"
#include "timer.h"

#define TRIS_LED    TRISB
#define LAT_LED     LATB
#define PORT_LED    PORTB
#define LED0        2

#define TIMER_UPDATE    63035


void main()
{       
    uint16_t cont_1ms=0;
    
    //Configuración de bits
    
    TRIS_LED &= ~(1<<LED0); //Salida
    LAT_LED &= 0xFF;  //Incia en 0
    
    //Configuración del timer
    Timer0_Timer_Config(16,Prescaler_2, Interrup_Off);
    
    //Adicional
    Timer0_Start();
    
    while(1)
    {      
        if(Timer0_Check_Flag())
        {   
            cont_1ms++;
            if(cont_1ms == 1000)
            {
                cont_1ms = 0;
                PORT_LED ^= (1<<LED0);
            }
            Timer0_Update_Count(TIMER_UPDATE);
            Timer0_Clean_Flag();   
        }
    }
       
    return;
}