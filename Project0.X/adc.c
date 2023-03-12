/*
 * File:   adc.c
 * Author: Leo
 *
 * Date 28 de Fevereiro de 2023, 18:45
 */
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "pic32.h"
#include "adc.h"

/**
 * \brief Function that configures ADC and turns it on. 
 * 
 * \param src_chn            Select between [0 - 15] analog channels
 * \param trigger_src        Set the ADC's trigger source: Auto, Timer3, Int0, and Manual.
 * \param sample_time        If Manual trigger is set, selec the sample time X * TAD (TAD = 100ns) */
void confAdc(uint8_t src_chn, ADCTriggerSrc_t trigger_src, uint8_t sample_time)
{
    AD1CON1bits.ON = 0;     //First disable the ADC.
    
    TRISB = 1;              //Set RB[0-15] to input mode
    AD1PCFG = 0;            //A-1 Set AN[0-15] to analog mode

    if(src_chn <0)          // Only [0-15] source channel are available
    {
        src_chn = 0;
    }
    else if(src_chn > 15)
    {
        src_chn = 15;
    }
    AD1CHSbits.CH0SA = src_chn;         //B-1 AN0 (Analog Channel 0 as input)
    AD1CON1bits.FORM = 0;               //C-1 Data out format: 0 = int 16-bit
    AD1CON1bits.SSRC = trigger_src;     //C-2 Conversion trigger selection bits: in this mode an internal counter ends sampling and starts conversion
    AD1CON2bits.VCFG = 0;               //D-1 Voltage reference conf bits: 0 - > VR+ = AVdd; VR-= AVss (Internal voltage rails)
    AD1CON2bits.CSCNA = 0;              //D-2 No scanning of multiple inputs
    AD1CON2bits.SMPI = 0;               //D-3 Number of conversions from ADCBUF[0] to ADCBUF[SMPI]
    AD1CON2bits.BUFM = 0;               //D-4 Buffer configured as one 16-word.
    AD1CHSbits.CH0NA = 0;               //D-5 0 = Uses board gnd reference (VR-), 1 = Uses AN1 input as reference (good for offset signals)
    AD1CON3bits.ADRC = 0;               //E-1 ADC conversion clock source: 1 = ADC internal RC clock
    AD1CON3bits.SAMC = sample_time;     //E-2 Sample time is X TAD (TAD = 100 ns)
    AD1CON3bits.ADCS = 7;               //E-3 ADC clock prescaler = 7.
    AD1CON1bits.CLRASAM = 0;            /*Normal operation,  
                                         *buffer contents will be overwritten by the next conversion sequence.
                                        */
    
    AD1CON1bits.ON = 1;                 //F - Enable A/D converter
    //!! This must the last command of the A/D configuration sequence !!
    
}

/* Function to turn ADC off*/
void AdcOff()
{
    AD1CON1bits.ON=0;
}

/* Function to turn ADC on*/
void AdcOn()
{
    AD1CON1bits.ON=1;
}

/* Function to start ADC auto sample/conversion */
void startAdc()
{
    AD1CON1bits.ASAM=1;
}

/* Function that reads only one conversion when called*/
uint16_t ADCReadManual(void)
{
    //AD1CON1bits.ASAM = 0;
    AD1CON1bits.SAMP = 0;
    while(AD1CON1bits.DONE==0);
    AD1CON1bits.DONE=0;
    //AD1CON1bits.ASAM = 1;
    return ADC1BUF0;
}

/* Function that keeps reading automatically*/
uint16_t ADCReadRetentive(void)
{
    while(AD1CON1bits.DONE==0);     /*Since the DONE bit isn't persistent in auto mode */
    AD1CON1bits.DONE=0;             /*(gets cleared by hardware), it is advisable not to poll it.*/
    return ADC1BUF0;                /*Unfortunately, the led toggle wasn't working if 
                                    * IFS1bits.ADIF flag was used.*/
}
