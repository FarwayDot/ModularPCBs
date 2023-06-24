/* 
 * File:   timer.h
 * Author: jeanf
 *
 * Created on 10 de junio de 2023, 12:02 AM
 */

#ifndef TIMER_H
#define	TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>

enum Timer0_Prescaler
{
    Prescaler_2 = 0,
    Prescaler_4,
    Prescaler_8,
    Prescaler_16,
    Prescaler_32,
    Prescaler_64,
    Prescaler_128,
    Prescaler_256
};

enum Timer0_Interrup
{
    Interrup_On = 0,
    Interrup_Off
};
    

void Timer0_Timer_Config(uint8_t bits, uint8_t prescaler_value,uint8_t interr);
void Timer0_Update_Count(uint16_t temp_value);

void Timer0_Contador_Config(uint8_t interr);

void Timer0_Start(void);
uint8_t Timer0_Check_Flag(void);
void Timer0_Clean_Flag(void);


#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

