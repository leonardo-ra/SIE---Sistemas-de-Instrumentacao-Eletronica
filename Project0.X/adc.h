/**
 * \file:   adc.h
 * \author: Leo
 *
 * \date 28 de Fevereiro de 2023, 18:48
 */

#ifndef __adc__H_
#define __adc__H_

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
    
#include "pic32.h"

#ifdef	__cplusplus
}
#endif

/* Trigger source types for the ADC*/
typedef enum {
    SrcManual = 0b000,  /**< Conversion starts manually (clearing SAMP bit) */
    SrcInt0 = 0b001,    /**< Conversion starts on active transition of INT0 */
    SrcTimer3 = 0b010,  /**< Conversion starts on End-of-Count of Timer 3 */
    SrcAuto = 0b111     /**< Conversion runs continuously */
} ADCTriggerSrc_t;

/**
 * \brief Function that configures ADC and turns it on. 
 * 
 * \param src_chn            Select between [0 - 15] analog channels
 * \param trigger_src        Set the ADC's trigger source: Auto, Timer3, Int0, and Manual.
 * \param sample_time        If Manual trigger is set, selec the sample time X * TAD (TAD = 100ns) */
void confAdc(uint8_t src_chn, ADCTriggerSrc_t trigger_src, uint8_t sample_time);

/**
 * \brief Turns ADC off
 */
void AdcOff();

/**
 * \brief Turns ADC on
 * 
 * Requires previous configuration with confAdc(...).
 */
void AdcOn();

/**
 * \brief Starts ADC conversion
 * 
 * Requires previous configuration with confAdc(...).
 */
void startAdc();

/**
 * \brief Reads ADC with manual trigger (reads only one conversion when called)
 * 
 * Requires previous configuration with confAdc(...). 
 */
uint16_t ADCReadManual(void);

/**
 * \brief Reads ADC with automatic trigger (not used with SrcManual trigger)
 * 
 * Requires previous configuration with confADC(). 
 */
uint16_t ADCReadRetentive(void);
#endif
