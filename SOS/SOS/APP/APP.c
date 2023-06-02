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
//#include "../MCAL/EXTINT/INT_interface.h"
#include "../OS/SOS_interface.h"

#include "APP.h"

uint8_t button1_status = 0 ; /** GLOBAL VARIABLE FOR BUTTON 1 **/

uint8_t button2_status = 0 ; /** GLOBAL VARIABLE FOR BUTTON 2 **/

/** LED1 TOGGLE TASK **/
void LED1_task()
{
	LED_TOGGLE(LED1_PORT , LED1_PIN);
}

/** LED2 TOGGLE TASK **/
void LED2_task()
{
	LED_TOGGLE(LED2_PORT , LED2_PIN);
}


/** INITIALIZATION TASK **/
void APP_init()
{
	LED_INIT(LED1_PORT , LED1_PIN); /** LED 1 INITILIZATION **/

	LED_INIT(LED2_PORT , LED2_PIN); /** LED 2 INITIALIZATION **/
	
	Button_init(); /** BUTTON INITIALIZATION **/
}

/** SOS STOP TASK **/
void Stop_button_task()
{
	Is_pressed(BUTTON2_PORT , BUTTON2_PIN , &button2_status); /** CHECK BUTTON STATUS **/
	
	if (button2_status == 1) /** BECOMES TRUE WHEN BUTTON 2 PRESSED **/
	{
		sos_disable(); /** DISABLE SOS **/
		
		button2_status = 0 ; /** REINITIALIZE BUTTON STATUS **/
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
	/** TASKS CREATION **/
	sos_create_task(TASK1 , TASK1_PERIODICITY , APP_init , ONE_TIME_EXECUTED_TASK);
    
	sos_create_task(TASK2 , TASK2_PERIODICITY , Stop_button_task , PERIODIC_TASK);
	
	sos_create_task(TASK3 , TASK3_PERIODICITY , LED1_task , PERIODIC_TASK);

	sos_create_task(TASK4 , TASK4_PERIODICITY , LED2_task , PERIODIC_TASK);
	
	sos_run(); /** START SCHEDULING **/
	
}

