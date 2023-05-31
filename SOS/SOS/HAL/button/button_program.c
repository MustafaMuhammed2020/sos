/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 4 April , 2023                       */
/* Version : V01                                  */
/* Hint    : Implementation of button APIs        */
/**************************************************/

/** INCLUDE THE LIBRARIES */
#include "../../SERVICE/standard_types.h"
#include "../../SERVICE/common_macros.h"

/** INCLUDE INTERFACE OF LOWER LAYERS **/
#include "../../MCAL/dio/DIO_interface.h"


/** INCLUDE THE DRIVER FILES */
#include "button_interface.h"
#include "button_config.h"
#include "button_private.h"

static uint8_t button_press = 0 ; /** GLOBAL VARIABLE TO CHECK THE NUMBER OF PRESSED TIMES **/

/*****************************************************************/
/* FUNCTION TO INITIALIZE THE BUTTON                             */
/* ARGUMENTS : TAKES THE BUTTON PIN                              */
/* RETURN    : void                                              */
/*****************************************************************/
void Button_init(void)
{
	/** SET THE DIRECTION OF BUTTON AS INPUT **/
	DIO_setpindir(BUTTON1_PORT , BUTTON1_PIN , DIO_PIN_INPUT);
}


/*****************************************************************/
/* FUNCTION TO CHECK THE BUTTON STATUS PRESSED OR NOT            */
/* ARGUMENTS : TAKES THE BUTTON PIN                              */
/* RETURN    : RETURNS BUTTON_t type                             */
/*****************************************************************/
en_a_button_t Is_pressed(uint8_t Button_port , uint8_t Button_pin , uint8_t * value)
{
	en_a_button_t button_state = Button_Notpressed ; /* VARIABLE TO HOLD THE RETURN TYPE OF THE FUNCTION */
	
	PinRead_t pin_status = NOT_VALID_READ ;  /** VARIABLE TO HOLD THE STATE OF PIN READ **/
	
	uint8_t pvalue = 0 ;
	
	pin_status = DIO_readpin(Button_port , Button_pin , &pvalue); /** READ THE BUTTON PIN VALUE */
	
	if (!pin_status) 
	{
		button_state = Button_pressed ; /** RETURN THE STATUS AS BUTTON IS PRESSED **/
		*value = pvalue ;
	}
	
	else
	{
		button_state = Button_Notpressed ; /** RETURN THE STATUS AS BUTTON IS PRESSED **/
		*value = pvalue ;
	}
	
	return button_state ; /** RETURN THE STATUS OF THE BUTTON **/
}
