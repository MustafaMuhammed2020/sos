/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 31 May , 2023                        */
/* Version : V01                                  */
/* Hint    : implementation of APP APIs           */
/**************************************************/

/** INCLUDE LIBRARIES **/
#include "../SERVICE/common_macros.h"
#include "../SERVICE/standard_types.h"

/** INCLUDE LOWER LAYER FILES **/
#include "../HAL/led/LED_interface.h"
#include "../HAL/led/LED_config.h"
#include "../HAL/button/button_interface.h"
#include "../HAL/button/button_config.h"
#include "../MCAL/EXTINT/INT_interface.h"

#include "../OS/SOS_interface.h"

uint8_t button1_status = 0 ;

uint8_t button2_status = 0 ;

void LED1_task()
{
	LED_TOGGLE(LED1_PORT , LED1_PIN);
}

void LED2_task()
{
	LED_TOGGLE(LED2_PORT , LED2_PIN);
}


/** INITIALIZATION FUNCTION **/
void APP_init(void)
{
	LED_INIT(LED1_PORT , LED1_PIN);

	LED_INIT(LED2_PORT , LED2_PIN);
	
	Button_init();
}

void Stop_button_task(void)
{
	Is_pressed(BUTTON2_PORT , BUTTON2_PIN , &button2_status);
	
	if (button2_status == 1)
	{
		sos_disable();
		
		button2_status = 0 ;
	}
	
}

// void Start_button_task(void)
// {
// 	Is_pressed(BUTTON1_PORT , BUTTON1_PORT , &button1_status);
// 	
// 	if (button1_status == 1)
// 	{
// 		sos_run();
// 		
// 		button1_status = 0 ;
// 	}
// 	
// }

/** MAIN LOGIC **/
void APP_start(void)
{
	sos_create_task(0 , 0 , APP_init , ONE_TIME_EXECUTED_TASK);
    
	sos_create_task(1 , 1 , Stop_button_task , PERIODIC_TASK);
	
	//sos_create_task(2 , 1 , Start_button_task , PERIODIC_TASK);
	
	sos_create_task(2 , 300 , LED1_task , PERIODIC_TASK);

	sos_create_task(3 , 500 , LED2_task , PERIODIC_TASK);
	
	sos_run();
	
}

