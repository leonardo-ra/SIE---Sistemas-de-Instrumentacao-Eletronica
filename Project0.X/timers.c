/*
 * File:   timers.c
 * Author: Leo
 *
 * Date 26 de Fevereiro de 2023, 21:23
 */
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
//#include <math.h>
#include "pic32.h"
#include "timers.h"

/**
 * \brief Configures a type B timer based on the specified frequency and Timer number 
 * 
 * \param tmrN              Select between one of 4 type B timers (2,3,4 and 5).
 * \param freq              Set that timers frequency.
 */
uint32_t confTimerB(uint32_t tmrN, uint32_t freq)
{
    uint32_t prescalers[]= {1,2,4,8,16,32,64,256};                          //prescaler values
    size_t prescaler_size = sizeof(prescalers) / sizeof(prescalers[0]);     //size of prescaler
    uint32_t prconst = 65536;                                               //16 bit timer max count
    uint32_t i = 0;
    
    /* Calculates PR register, based on the first prescaler.*/ 
    uint32_t pr = (((PBCLK/freq)/prescalers[i])-1);     
    
    /* If the current PR value is higher than the max possible representation, 
     * it searches for a new prescaler.
     */
    while(pr > prconst)      
    {
        i = i+1;
        if(i > prescaler_size-1)
        {
            printf("[Control Msg: No prescaler available for that frequency!]\r\n");
            return -1; 
        }
        /* Recalculates PR*/
        pr = ((PBCLK/freq)/prescalers[i] -1);
    }
    
    /* Based on the timer selection, cofigures that specific timer's registers*/
    switch (tmrN)
    {
        case 2:
            printf("[Control Msg: Timer2 configured with %d Hz]\r\n",freq);
            T2CONbits.TCKPS = i;    // Prescaler
            
            PR2 = pr;               // Vlaue to determinate the frequency, fout = fin/(PR2+1))
            TMR2 = 0;               // Reset timer T2 count register
            T2CONbits.T32 = 0;      // Timer operation with 16 bits
            T2CONbits.TON = 0;      // Enable timer T2 (must be the last command of the timer configuration sequence) 
            IFS0bits.T2IF = 0;      // Reset Interrupt flag
            break;
        case 3:
            printf("[Control Msg: Timer3 configured with %d Hz]\r\n",freq);
            T3CONbits.TCKPS = i;    
            PR3 = pr;
            TMR3 = 0;              
            //T3CONbits.T32 = 0; Timer 3 binds to Timer 2 in tendem to build a 32bit couter, so it doesn't need a T32 conf. 
            T3CONbits.TON = 0;      
            IFS0bits.T3IF = 0;     
            break;
        case 4:
            printf("[Control Msg: Timer4 configured with %d Hz]\r\n",freq);
            T4CONbits.TCKPS = i;    
            PR4 = pr;     
            TMR4 = 0;               
            T4CONbits.T32 = 0;
            T4CONbits.TON = 0;      
            IFS0bits.T4IF = 0;      
            break;
        case 5:
            printf("(Control Msg: Timer5 configured with %d Hz)\r\n",freq);
            T5CONbits.TCKPS = i;
            PR5 = pr;
            TMR5 = 0;
            //T5CONbits.T32 = 0; Timer 5 behaves the same way as timer 3.
            T5CONbits.TON = 0;
            IFS0bits.T5IF = 0;      
            break;
        default:
            printf("\n(Control Msg: No timer was configured, the only type B timers available are numbers: 2 - 5!)\r\n");
            break;
    }
}

/* Timer's start and stop functions */
void startTimer2()
{
    T2CONbits.TON = 1;
}

void stopTimer2()
{
    T2CONbits.TON = 0;
}

void startTimer3()
{
    T3CONbits.TON = 1;
}

void stopTimer3()
{
    T3CONbits.TON = 0;
}

void startTimer4()
{
    T4CONbits.TON = 1;
}

void stopTimer4()
{
    T4CONbits.TON = 0;
}

void startTimer5()
{
    T5CONbits.TON = 1;
}

void stopTimer5()
{
    T5CONbits.TON = 0;
}

/**
 * \brief Delay function, set a milisecond delay.
 * 
 * \param ms                miliseconds
 */
void delay(uint32_t ms)
{
    float normalizer = 1E-3; //normalized to miliseconds
    uint32_t count = 0;
    while(count++<PBCLK*normalizer*ms);
}