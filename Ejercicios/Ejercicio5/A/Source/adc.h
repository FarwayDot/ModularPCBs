/* 
 * File:   adc.h
 * Author: jeanf
 *
 * Created on 13 de junio de 2023, 08:50 PM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>

    enum ADC_Channel
    {
        AN_0=0,
        AN_1,
        AN_2,
        AN_3,
        AN_4   
    };
    
enum ADC_Interrup
{
    ADC_Interr_On = 0,
    ADC_Interr_Off
};
    
void ADC_Config(uint8_t interr);
uint16_t ADC_Read_Channel(uint8_t channel);
void ADC_Clear_Flag(void);
uint8_t ADC_Check_Flag(void);
void ADC_Start_Conversion(void);
void ADC_Wait_Conversion(void);

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

