/**
 * \file:   pic32.h
 * \author: Leo
 *
 * \date 26 de Fevereiro de 2023, 21:32
 */

#ifndef __pic32__H_
#define __pic32__H_

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>

#ifdef	__cplusplus
}
#endif

extern const long int PBCLK;    /**< Peripheral Bus Clock frequency 40000000L;*/
extern const long int SYSCLK;   /**< System Clock frequency 80000000L;*/

extern const uint8_t OK;        /**< Result is OK */
extern const uint8_t NOK;       /**< Result is not OK */
#endif
