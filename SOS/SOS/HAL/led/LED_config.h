/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 4 April , 2023                       */
/* Version : V01                                  */
/* Hint    : configuration file of led            */
/**************************************************/
#ifndef LED_CONFIG_H
#define LED_CONFIG_H

#include "../../MCAL/dio/DIO_interface.h"

/** LED 1 CONFIGURATIONS IN PORTC , PIN2  */
#define LED1_PORT   DIO_PORTD
#define LED1_PIN    DIO_PIN3

/** LED 2 CONFIGURATIONS IN PORTC , PIN7  */
#define LED2_PORT  DIO_PORTC
#define LED2_PIN   DIO_PIN2

/** LED 3 CONFIGURATIONS IN PORTD , PIN3  */
#define LED3_PORT  DIO_PORTC
#define LED3_PIN   DIO_PIN2

/** LED 4 CONFIGURATIONS IN PORTD , PIN4  */
#define LED4_PORT  DIO_PORTC
#define LED4_PIN   DIO_PIN3


#endif