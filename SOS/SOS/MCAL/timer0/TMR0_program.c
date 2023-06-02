/******************************************************************/
/* Author  : Mustafa Mohammed Abdou                               */
/* Date    : 16 , April 2023                                      */
/* Version : V01                                                  */
/* Hint    : Implementation of Timer 0 APIs                       */
/******************************************************************/ 

/** INCLUDE LIBRARIES **/
#include <avr/interrupt.h>

#include "../../SERVICE/common_macros.h"
#include "../../SERVICE/standard_types.h"

/** INCLUDE LOWER LAYER FILES **/
#include "../dio/DIO_interface.h"

/** INCLUDE DRIVER FILES **/
#include "TMR0_interface.h"
#include "TMR0_private.h"
#include "TMR0_config.h"

void ( * ptr_func_tmr0_callback ) ( void );  /** GLOBAL VARIABLE FOR TIMER0 CALL BACK **/

uint8_t u8_gl_timer0_ovs = 0 ; /** GLOBAL VARIABLE INCREASES UNTILL THE TICK TIME VALUE **/


/****************************************************************/
/** FUNCTION TO INITIALIZE TMR0 WITH SOME CONFIGURATIONS        */
/** ARGUMENTS  : VOID                                           */
/** RETURNS    : TMR0_init                                      */
/****************************************************************/
TMR0_init_error TMR0_init(void)
{
	TMR0_init_error en_a_initstatus = VALID_INIT ; /** VARIABLE TO RETURN THE STATUS OF INITIALIZATION **/
	
    /* COUNTER MODE OF TMR0 */
	#if TIMER0_CLK_SRC == EXTERNAL_CLK_SRC
	
	  /* EXTERNAL PIN AS CLOCK SOURCE */
	  DIO_setpindir(DIO_PORTB , DIO_PIN0 , DIO_PIN_INPUT);

	  //DIO_SETPULLUPS(DIO_PORTB , DIO_PIN0 );
	  
	 #if CNT0_EXTERNAL_EDGE_MODE == FALLING_EDGE_CNT
	  
	  clear_bit(TCCR0 , 0);
	  set_bit(TCCR0 , 1);
	  set_bit(TCCR0 , 2);
	  
	  en_a_initstatus = VALID_INIT ; /** INITIALIZATION STATUS IS TRUE **/
	  
	 #elif CNT0_EXTERNAL_EDGE_MODE == RISING_EDGE_CNT
	  
	  set_bit(TCCR0 , 0);
	  set_bit(TCCR0 , 1);
	  set_bit(TCCR0 , 2);
	  en_a_initstatus = VALID_INIT ; /** INITIALIZATION STATUS IS TRUE **/
	 
	 #endif
	 
	 /* TIMER MODE OF TMR0 */
	#elif TIMER0_CLK_SRC == INTERNAL_CLK_SRC
	
	 #if TIMER0_MODE == TMR0_NORMAL_MODE
	 
	 clear_bit(TCCR0 , 7);
	 clear_bit(TCCR0 , 6);
	 clear_bit(TCCR0 , 3);
	 clear_bit(TCCR0 , 4);
	 clear_bit(TCCR0 , 5);
	 
	 en_a_initstatus = VALID_INIT ; /** INITIALIZATION STATUS IS TRUE **/
	 
 	 /* ENABLE INTERRUPT */
 	 set_bit(SREG , 7);
 	 set_bit(TIMSK , 0);
	 
	 #elif TIMER0_MODE == TMR0_FASTPWM_NON_INVERTED_MODE
	 
	 set_bit(TCCR0 , 7);
	 set_bit(TCCR0 , 6);
	 set_bit(TCCR0 , 3);
	 clear_bit(TCCR0 , 4);
	 set_bit(TCCR0 , 5);
	 
	 en_a_initstatus = VALID_INIT ; /** INITIALIZATION STATUS IS TRUE **/
	 
	 #elif TIMER0_MODE == TMR0_FASTPWM_INVERTED_MODE
	 
	 set_bit(TCCR0 , 7);
	 set_bit(TCCR0 , 6);
	 set_bit(TCCR0 , 3);
	 set_bit(TCCR0 , 4);
	 set_bit(TCCR0 , 5);
	 
	 en_a_initstatus = VALID_INIT ; /** INITIALIZATION STATUS IS TRUE **/
	 
	 #elif TIMER0_MODE == TMR_PHASE_CORRECT_NON_INVERTED_MODE
	 
	 set_bit(TCCR0 , 7);
	 set_bit(TCCR0 , 6);
	 clear_bit(TCCR0 , 3);
	 clear_bit(TCCR0 , 4);
	 set_bit(TCCR0 , 5);
	 
	 en_a_initstatus = VALID_INIT ; /** INITIALIZATION STATUS IS TRUE **/
	 
	 #elif TIMER0_MODE == TMR_PHASE_CORRECT_INVERTED_MODE
	 
	 set_bit(TCCR0 , 7);
	 set_bit(TCCR0 , 6);
	 clear_bit(TCCR0 , 3);
	 set_bit(TCCR0 , 4);
	 set_bit(TCCR0 , 5);
	 
	 en_a_initstatus = VALID_INIT ; /** INITIALIZATION STATUS IS TRUE **/
	 
	 #elif TIMER0_MODE == TMR0_CTC_MODE
	 
	 DIO_setpindir(DIO_PORTB , DIO_PIN3 , DIO_PIN_OUTPUT); /** SET CTC BIT AS OUTPUT PIN **/
	 
	 clear_bit(TCCR0 , 7);
	 clear_bit(TCCR0 , 6);
	 set_bit(TCCR0 , 3);
	 
	 /* ENABLE INTERRUPT */
	 set_bit(SREG , 7);
	 set_bit(TIMSK , 1);
	 
	 en_a_initstatus = VALID_INIT ; /** INITIALIZATION STATUS IS TRUE **/
	 
	  #if COMPARE_ACTION == SET_ON_COMPARE
	   
	   set_bit(TCCR0 , 4);
	   set_bit(TCCR0 , 5);
	   
	  #elif COMPARE_ACTION == CLEAR_ON_COMPARE
	   
	   clear_bit(TCCR0 , 4);
	   set_bit(TCCR0 , 5);
	   
	  #elif COMPARE_ACTION == TOOGLE_ON_COMPARE
	   
	   set_bit(TCCR0 , 4);
	   clear_bit(TCCR0 , 5);
	  #endif
	 #endif
	#endif
	
	return en_a_initstatus ; /** RETURN THE STATUS OF INITIALIZATION **/
}


/*********************************************************************************/
/** FUNCTION TO LET TIMER 0 START WORK BY ASSIGNING PRESCALLER OR CLOCK SOURCE   */
/** ARGUMENTS  : VOID                                                            */
/** RETURNS    : TMR0_start                                                      */
/*********************************************************************************/
TMR0_start_error TMR0_start(void)
{
	TMR0_start_error en_a_startstatus = VALID_START ; /** VARIABLE TO RETURN THE STATUS OF START **/
	
	#if TIMER0_PRESCALER_VAL == PRESCALER_1024
	
	set_bit(TCCR0 , 0);
	clear_bit(TCCR0 , 1);
	set_bit(TCCR0 , 2);
	
	en_a_startstatus = VALID_START ; /** START DONE PROBERLY **/
	
	#elif TIMER0_PRESCALER_VAL == NO_PRESCALER
	
	set_bit(TCCR0 , 0);
	clear_bit(TCCR0 , 1);
	clear_bit(TCCR0 , 2);
	
	en_a_startstatus = VALID_START ; /** START DONE PROBERLY **/
	
	#elif TIMER0_PRESCALER_VAL == PRESCALER_8
	
	clear_bit(TCCR0 , 0);
	set_bit(TCCR0 , 1);
	clear_bit(TCCR0 , 2);
	
	en_a_startstatus = VALID_START ; /** START DONE PROBERLY **/
	
	#elif TIMER0_PRESCALER_VAL == PRESCALER_64
	
	set_bit(TCCR0 , 0);
	set_bit(TCCR0 , 1);
	clear_bit(TCCR0 , 2);
	
	en_a_startstatus = VALID_START ; /** START DONE PROBERLY **/
	
	#elif TIMER0_PRESCALER_VAL == PRESCALER_256
	
	clear_bit(TCCR0 , 0);
	clear_bit(TCCR0 , 1);
	set_bit(TCCR0 , 2);
	
	en_a_startstatus = VALID_START ; /** START DONE PROBERLY **/
	
	#endif
	
	return en_a_startstatus ; /** RETURN THE STATUS **/
}

/*******************************************************************************/
/** FUNCTION TO STOP TIMER 0                                                   */
/** ARGUMENTS  : VOID                                                          */
/** RETURNS    : TMR0_stop                                                     */
/*******************************************************************************/
TMR0_stop_error TMR0_stop(void)
{
	TMR0_stop_error en_a_stopStatus = VALID_STOP ; /** VARIABLE TO RETURN THE STATUS **/
	
	/** SET CONFIGURATIONS AS NO CLOCK SOURCE **/
	clear_bit(TCCR0 , 0);
	clear_bit(TCCR0 , 1);
	clear_bit(TCCR0 , 2);
	
	en_a_stopStatus = VALID_STOP ; /** STOP DONE PROPERLY **/
	
	return en_a_stopStatus ; /** RETURN THE STATUS **/
	
}


/************************************************************************/
/** FUNCTION TO SET THE CALL BACK GLOBAL POINTER OF TIMER0             **/
/** ARGUMENTS  : void (*ptr)(void) (PINTER TO CALL BACK FUNCTION)      **/
/** RETURNS    : VOID                                                  **/
/************************************************************************/
void TMR0_setcallback( void (*ptr_func)(void) )
{
	ptr_func_tmr0_callback = ptr_func; /** TIMER0 GLOBAL POINTER POINTS TO THE PASSED FUNCTION **/
}

/** TIMER0 INTERRUPT SERVICE ROUTINE **/
ISR(TIMER0_OVF_vect)
{
	u8_gl_timer0_ovs++ ; /** INCREASE THE NUMBER OF OVERFLOWS BY 1 **/
	
 	if ( u8_gl_timer0_ovs == TICK_OVER_FLOW ) /** BECOMES TRUE WHEN TIME EQUALS TO TICK TIME OVER FLOW COUNTER **/
 	{
		ptr_func_tmr0_callback(); /** EXECUTE THE FUNCTION TO WHICH THE GLOBAL VARIABLE POINTS **/
		
 		u8_gl_timer0_ovs = 0 ; /** REINITIALIZE TIMER0 OVERFLOW COUNTER TO 0 AGAIN **/
 	}
	 TCNT0 = 0 ;
}