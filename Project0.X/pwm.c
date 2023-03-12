/**
 * \file:   pwm.c
 * \author: Vasco Fernandes
 *
 * \date 28 de Fevereiro de 2023, 16:25
 */

#include <xc.h>
#include <stdint.h>
#include <math.h>
#include "pic32.h"
#include "timers.h"
#include "pwm.h"

void PWMsetupFreq(uint16_t PWM_freq)
{           
    OC2CONbits.ON = 0;    // Turn off OC2 while doing setup.
    
    confTimerB(2,PWM_freq); // Configures timer 2 with the correct PR value, given the pwm_freq.
    OC2CONbits.OCM = 6;     // Configure for PWM mode; fault pin disabled 
    OC2CONbits.OCTSEL =0;   // Use timer T2 as the time base for PWM generation
    OC2R = 0;               // Initialize primary Compare Register
    OC2RS = (PR2+1)>>1;  // buffer register to update PWM duty cycle
                                // by making one shift right, we're dividing by 2, thus assuming a 50% duty cycle
                                // duty_cycle =  OC2RS/(PR2+1)
    
    OC2CONbits.ON = 1;          // Enable OC2
}

void PWMDutyCycle(uint16_t duty_cycle)
{
    OC2RS = (PR2+1)*duty_cycle/100;
}