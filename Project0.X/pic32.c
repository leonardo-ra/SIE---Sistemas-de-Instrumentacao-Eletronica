/*
 * File:   pic32.c
 * Author: Leo
 *
 * Date 26 de Fevereiro de 2023, 21:30
 */
#include <xc.h>
#include <stdint.h>
#include "pic32.h"

/**
 * \brief General ok and not ok messages
 * 
 * \variables OK - 1;
 */
const uint8_t OK = 0;

/**
 * \brief General ok and not ok messages
 * 
 * \variables NOK - 0;
 */
const uint8_t NOK = 1;
  

/**
 * \brief General system clocks
 * 
 * \variables Peripheral Bus clock - 40M Hz
 */
const long int PBCLK = 40000000L;

/**
 * \brief General system clocks
 * 
 * \variables System clock - 80M Hz 
 */
const long int SYSCLK = 80000000L;
 
