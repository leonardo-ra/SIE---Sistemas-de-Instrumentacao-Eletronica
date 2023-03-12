/**
 * \file:   timers.h
 * \author: Leo
 *
 * \date 26 de Fevereiro de 2023, 21:24
 */

#ifndef __timers__H_
#define __timers__H_

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
//#include <math.h>
    
#include "pic32.h"

#ifdef	__cplusplus
}
#endif

/**
 * \brief Configures a type B timer based on the specified frequency and Timer number 
 * 
 * \param tmrN              Select between one of 4 type B timers (2,3,4 and 5).
 * \param freq              Set that timers frequency.
 */
uint32_t confTimerB(uint32_t tmrN, uint32_t freq);

/**
 * \brief Timer's start and stop functions 
 * 
 * \others startTimerX() and stopTimerX() [from Timer2 to Timer5].
 * 
 */
void startTimer2();

/**
 * \brief Timer's start and stop functions 
 * 
 * \others startTimerX() and stopTimerX() [from Timer2 to Timer5].
 * 
 */
void startTimer3();

/**
 * \brief Timer's start and stop functions 
 * 
 * \others startTimerX() and stopTimerX() [from Timer2 to Timer5].
 * 
 */
void startTimer4();

/**
 * \brief Timer's start and stop functions 
 * 
 * \others startTimerX() and stopTimerX() [from Timer2 to Timer5].
 * 
 */
void startTimer5();

/**
 * \brief Timer's start and stop functions 
 * 
 * \others startTimerX() and stopTimerX() [from Timer2 to Timer5].
 * 
 */
void stopTimer2();

/**
 * \brief Timer's start and stop functions 
 * 
 * \others startTimerX() and stopTimerX() [from Timer2 to Timer5].
 * 
 */
void stopTimer3();

/**
 * \brief Timer's start and stop functions 
 * 
 * \others startTimerX() and stopTimerX() [from Timer2 to Timer5].
 * 
 */
void stopTimer4();

/**
 * \brief Timer's start and stop functions 
 * 
 * \others startTimerX() and stopTimerX() [from Timer2 to Timer5].
 * 
 */
void stopTimer5();

/**
 * \brief Delay function
 *  
 * \param ms                Set a milisecond delay.
 */
void delay(uint32_t ms);
#endif
