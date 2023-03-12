/**
 * \file:   pwm.h
 * \author: Leo
 *
 * \date 6 de Março de 2023, 19:52
 */

#ifndef __pwm__H_
#define __pwm__H_

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>
#include <math.h>
#include "pic32.h"
#include "timers.h"

#ifdef	__cplusplus
}
#endif
void PWMsetupFreq(uint16_t PWM_freq);
void PWMDutyCycle(uint16_t duty_cycle);
#endif
