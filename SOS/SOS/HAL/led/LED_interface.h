/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 4 April , 2023                       */
/* Version : V01                                  */
/* Hint    : interface file of led                */
/**************************************************/

#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

/***************************************************/
/** FUNCTION TO INITIALIZE A PIN                  **/
/** INPUT : LED PORT , LED PIN                    **/
/** RETURNS : VOID                                **/
/***************************************************/
void LED_INIT(uint8_t led_port , uint8_t ledpin);


/***************************************************/
/** FUNCTION TO SET A LED AS ON                   **/
/** INPUT : LED PORT , LED PIN                    **/
/** RETURNS : VOID                                **/
/***************************************************/
void LED_ON(uint8_t led_port , uint8_t ledpin);

/***************************************************/
/** FUNCTION TO SET A LED AS OFF                  **/
/** INPUT : LED PORT , LED PIN                    **/
/** RETURNS : VOID                                **/
/***************************************************/
void LED_OFF(uint8_t led_port , uint8_t ledpin);


/***************************************************/
/** FUNCTION TO TOGLE A LED                       **/
/** INPUT : LED PORT , LED PIN                    **/
/** RETURNS : VOID                                **/
/***************************************************/
void LED_TOGGLE(uint8_t led_port , uint8_t ledpin);

#endif