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

/** INCLUDE LAYER FILES **/
#include "APP.h"

uint8_t button1_status   ; /** GLOBAL VARIABLE FOR BUTTON 1 **/

uint8_t button2_status  ; /** GLOBAL VARIABLE FOR BUTTON 2 **/

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

/** CALLBACK FUNCTION OF EXTINT0 **/
void start_button()
{
	
	sos_init();
	
	sos_run();  /** RESTART OS AGAIN **/	
}


/** INITIALIZATION TASK **/
void APP_init()
{
	INT0_INIT();  /** INITIALIZE EXTERNAL INTERRUPT 0 **/
	
	LED_INIT(LED1_PORT , LED1_PIN); /** LED 1 INITILIZATION **/

	LED_INIT(LED2_PORT , LED2_PIN); /** LED 2 INITIALIZATION **/
	
	Button_init(); /** BUTTON INITIALIZATION **/
	
	EXTINT0_setcallback(start_button); /** CALLBACK FUNCTION OF EXTINT0 **/
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


/** MAIN LOGIC **/
void APP_start()
{
	enu_system_status_t enu_l_func_return_status = SOS_STATUS_SUCCESS ; /** LOCAL VARIABLE TO CHECK THE FUNCTION RETURN STATUS **/
	
	/** TASKS CREATION **/
	enu_l_func_return_status = sos_create_task(TASK1 , TASK1_PERIODICITY , APP_init , ONE_TIME_EXECUTED_TASK);
	
	if ( enu_l_func_return_status == SOS_STATUS_SUCCESS )
	{
		enu_l_func_return_status = sos_create_task(TASK2 , TASK2_PERIODICITY , Stop_button_task , PERIODIC_TASK);
		
		if ( enu_l_func_return_status == SOS_STATUS_SUCCESS )
		{
			enu_l_func_return_status = sos_create_task(TASK3 , TASK3_PERIODICITY , LED1_task , PERIODIC_TASK);
			
			if ( enu_l_func_return_status == SOS_STATUS_SUCCESS )
			{
				enu_l_func_return_status = sos_create_task(TASK4 , TASK4_PERIODICITY , LED2_task , PERIODIC_TASK);
				
				if ( enu_l_func_return_status == SOS_STATUS_SUCCESS )
				{
					sos_init(); /** PREPARE OS TO START **/
					
					sos_run(); /** START SCHEDULING **/
				}
			}
		}
	}
}

