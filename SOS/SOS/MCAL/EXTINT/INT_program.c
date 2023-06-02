/***************************************************/
/* Author  : Mustafa Mohammed Abdou                */
/* Date    : 4 April, 2023                         */
/* Version : V01                                   */
/* Hint    : implementation of external interrupts */
/***************************************************/

/** INCLUDE LIBRARIES **/
#include <avr/interrupt.h>
#include "../../SERVICE/standard_types.h"
#include "../../SERVICE/common_macros.h"

/** INCLUDE DRIVER FILES **/
#include "INT_interface.h"
#include "INT_private.h"
#include "INT_config.h"

void ( * ptr_func_exint0_callback ) ( void );  /** GLOBAL VARIABLE FOR TIMER0 CALL BACK **/

/********************************************************/
/** FUNCTION TO SET THE GLOBAL INTERRUPT ENABLE FLAG    */
/** ARGUMENTS  : VOID                                   */
/** RETURNS    : VOID                                   */
/********************************************************/
void SET_GLOBALINTERRUPT(void)
{
	//#if GLOBAL_INTERRUPT_STATE  ==  GLOBAL_INTERRUPT_STATE_ENABLE /** ENABLE GLOBAL INTERRUPTS **/
	 // set_bit(SREG , 7);
	  
	//#elif GLOBAL_INTERRUPT_STATE == GLOBAL_INTERRUPT_STATE_DISABLE /** DISABLE GLOBAL INTERRUPTS **/
	//  clear_bit(SREG , 7);
	  
	//#endif
}


/********************************************************/
/** FUNCTION TO INITIALIZE INT0                         */
/** ARGUMENTS  : VOID                                   */
/** RETURNS    : VOID                                   */
/********************************************************/
void INT0_INIT(void)
{
	SET_GLOBALINTERRUPT(); /** ENABLE GLOBAL INTERRUPTS */

	set_bit(SREG , 7);
	
	/** CONFIGURE THE INT0 TRIGGER EVENT **/
	#if  EXTERNAL_INT0_TRIGGER   ==  INT_TRIGGER_RISING_EDGE 
	
	  set_bit(MCUCR , 0);
	  set_bit(MCUCR , 1);
	  
	#elif  EXTERNAL_INT0_TRIGGER  == INT_TRIGGER_FALLING_EDGE
	
	  set_bit(MCUCR , 1);
	  clear_bit(MCUCR  , 0);
	  
	#elif EXTERNAL_INT0_TRIGGER  ==  INT_TRIGGER_LOW_LEVEL
	
	  clear_bit(MCUCR , 0);
	  clear_bit(MCUCR , 1);
	  
	#elif EXTERNAL_INT0_TRIGGER  == INT_TRIGGER_ANY_CHANGE
	
	  set_bit(MCUCR , 0);
	  clear_bit(MCUCR ,1);
	  
	#endif
	
	
	/* Enable INT0 */
	set_bit(GICR , 6);	
}



/************************************************************************/
/** FUNCTION TO SET THE CALL BACK GLOBAL POINTER OF EXTINT0            **/
/** ARGUMENTS  : void (*ptr)(void) (PINTER TO CALL BACK FUNCTION)      **/
/** RETURNS    : VOID                                                  **/
/************************************************************************/
void EXTINT0_setcallback( void (*ptr_func)(void) )
{
	ptr_func_exint0_callback = ptr_func; /** TIMER0 GLOBAL POINTER POINTS TO THE PASSED FUNCTION **/
}

/********************************************************/
/** FUNCTION TO INITIALIZE INT1                         */
/** ARGUMENTS  : VOID                                   */
/** RETURNS    : VOID                                   */
/********************************************************/
void INT1_INIT(void)
{
	SET_GLOBALINTERRUPT(); /** ENABLE GLOBAL INTERRUPTS **/
	
		/** CONFIGURE THE INT1 TRIGGER EVENT **/
	#if EXTERNAL_INT1_TRIGGER  == INT_TRIGGER_RISING_EDGE 
	
	  set_bit(MCUCR , 2);
	  set_bit(MCUCR , 3);
	  
	#elif EXTERNAL_INT1_TRIGGER == INT_TRIGGER_FALLING_EDGE
	 
	  clear_bit(MCUCR , 2);
	  set_bit(MCUCR , 3);
	  
	#elif EXTERNAL_INT1_TRIGGER == INT_TRIGGER_LOW_LEVEL
	  
	  clear_bit(MCUCR , 2);
	  clear_bit(MCUCR , 3);
	  
	#elif EXTERNAL_INT1_TRIGGER == INT_TRIGGER_ANY_CHANGE
	
	  set_bit(MCUCR , 2);
	  clear_bit(MCUCR , 3);
	  
	#endif

     /* Enable INT1 */
	set_bit(GICR , 7);
}

/********************************************************/
/** FUNCTION TO INITIALIZE INT2                         */
/** ARGUMENTS  : VOID                                   */
/** RETURNS    : VOID                                   */
/********************************************************/
void INT2_INIT(void)
{
	SET_GLOBALINTERRUPT(); /** ENABLE GLOBAL INTERRUPTS **/
	
	/* Enable INT2 */
	set_bit(GICR , 5);
	
	/** CONFIGURE THE INT2 TRIGGER EVENT **/
	#if EXTERNAL_INT2_TRIGGER == INT_TRIGGER_FALLING_EDGE
	  
	  clear_bit(MCUCSR , 6);
	  
	#elif EXTERNAL_INT2_TRIGGER == INT_TRIGGER_RISING_EDGE
	  
	  set_bit(MCUCSR , 6);
	  
	#endif
}

/** EXTERNAL INTERRUPT 0 ISR **/
ISR(INT0_vect)
{
	ptr_func_exint0_callback(); 
}