/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 4 April , 2023                       */
/* Version : V01                                  */
/* Hint    : program file of led                  */
/**************************************************/

/** INCLUDE LIBRARIES **/
#include "../../SERVICE/common_macros.h"
#include "../../SERVICE/standard_types.h"

/** INCLUDE INTERFACE FILES OF LOWER LAYERS **/
#include "../../MCAL/dio/DIO_interface.h"

/** INCLUDE DRIVER FILES **/
#include "LED_interface.h"
#include "LED_private.h"
#include "LED_config.h"

/***************************************************/
/** FUNCTION TO INITIALIZE A PIN                  **/
/** INPUT : LED PORT , LED PIN                    **/
/** RETURNS : VOID                                **/
/***************************************************/
void LED_INIT(uint8_t led_port , uint8_t ledpin)
{
	
	DIO_setpindir(led_port , ledpin , DIO_PIN_OUTPUT); /** SET THE LED PIN AS OUTPUT **/
}


/***************************************************/
/** FUNCTION TO SET A LED AS ON                   **/
/** INPUT : LED PORT , LED PIN                    **/
/** RETURNS : VOID                                **/
/***************************************************/
void LED_ON(uint8_t led_port , uint8_t ledpin)
{
	
	DIO_setpinvalue(led_port , ledpin , DIO_PIN_HIGH); /** SET THE OUTPUT PIN AS HIGH **/
}

/***************************************************/
/** FUNCTION TO SET A LED AS OFF                  **/
/** INPUT : LED PORT , LED PIN                    **/
/** RETURNS : VOID                                **/
/***************************************************/
void LED_OFF(uint8_t led_port , uint8_t ledpin)
{
	
	DIO_setpinvalue(led_port , ledpin , DIO_PIN_LOW); /** SET THE OUTPUT PIN AS LOW **/
}


/***************************************************/
/** FUNCTION TO TOGLE A LED                       **/
/** INPUT : LED PORT , LED PIN                    **/
/** RETURNS : VOID                                **/
/***************************************************/
void LED_TOGGLE(uint8_t led_port , uint8_t ledpin)
{
	
	DIO_togglepin(led_port , ledpin); /** TOGGLE THE SPECIFIC LED **/
}

