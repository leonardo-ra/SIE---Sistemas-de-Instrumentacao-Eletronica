/**
 * \file:   projeto0.c
 * \author: Leo & Vasco
 *
 * \date 25 de Fevereiro de 2023, 15:14
 */

#include "../DemoProjects/CKCommon/ConfigBits/config_bits.h"
#include <xc.h>
#include <stdint.h>
#include <stdio.h>

#include "../DemoProjects/CKCommon/UART/uart.h"
#include "pic32.h"
#include "timers.h"
#include "adc.h"
#include "pwm.h"

#define BAUD 115200

uint16_t tf_direct(uint16_t value_read);
uint16_t tf_invert(uint16_t value_read);

int main(void) {
    
    /*Change the sampling frequency HERE. Acording to project specifications: [20-200]*/
    uint16_t sample_freq = 200; // <--- replace with desired sampling frequency
    uint16_t pwm_freq = 2000;   // <--- replace with desired pwm frequency
    
    /* Configure LED*/
    TRISAbits.TRISA3 = 0;   // Configure RA3 register (led 5) as output
    LATAbits.LATA3 = 0;     // Turn led off
    
    /*Configure UART*/
    UartInit(PBCLK,BAUD);
    
    printf("\nSIE - Project 0 | Leonardo e Vasco \n\r");
    printf("%s, %s\r\n", __DATE__, __TIME__);
    printf("\nSampling frequency & PWM frequency set: %d Hz, %d Hz\r\n\n",sample_freq,pwm_freq);
    /*Configure Timer 3 sampling frequency*/
    confTimerB(3,sample_freq);  // Timer 3 at sample frequency Hz
    startTimer3();
    
    /*Configure ADC to convert at sampling frequency determined by Timer3*/
    confAdc(0,SrcTimer3,0);
    
    /*Configure PWM frequency*/
    PWMsetupFreq(pwm_freq); //Sets PWM timer (uses Timer2 by default)
    startTimer2();
    
    /*Variable initialization*/
    uint16_t result_tfunction;
    
    startAdc(); //Start auto sample/conversion
    
    while(1)
    {   
        /*Auto read result*/
        uint32_t result = ADCReadRetentive();
        
        /*send [0-1023] value to transfer function*/
        result_tfunction = tf_invert(result);
        
        /*transfer function transforms [0-1023] into [0-100], and defines pwm Duty Cycle*/
        PWMDutyCycle(result_tfunction);
        
        /*Toggles led at sample_freq*/
        LATAbits.LATA3 = !LATAbits.LATA3;
        
    }
    return (EXIT_SUCCESS);
}

/*Transfer function*/
uint16_t tf_direct(uint16_t value_read)
{
    /* Transforms the value read [0-1023] into a percentage value [0-100]*/
    return (value_read*100)/1023;
}

uint16_t tf_invert(uint16_t value_read)
{
    value_read=1023-value_read;
    
    return(value_read*100)/1023;
}