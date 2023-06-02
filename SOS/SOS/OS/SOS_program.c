/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 31 May , 2023                        */
/* Version : V01                                  */
/* Hint    : implementation of SOS APIs           */
/**************************************************/

/** INCLUDE LIBRARIES **/
#include "../SERVICE/common_macros.h"
#include "../SERVICE/standard_types.h"

/** INCLUDE LOWER LAYERS FILES **/
#include "../MCAL/timer0/TMR0_interface.h"

/** INCLUDE DRIVER FILES **/
#include "SOS_interface.h"
#include "SOS_config.h"
#include "SOS_private.h"

#define NULL    0

uint16t u16_g_ticks = 0 ;

/** ARRAY OF TASKS **/
static str_task_t str_gl_tasks_data[MAX_TASKS] = { {NULL} } ; 

/******************************************************************/
/** FUNCTION TO CREATE TASK                                      **/
/** PARAMETERS  : TASK_ID , TASK_PERIODICITY , POINTER TO TASK   **/
/** RETURNS     : enu_system_status_t (ERROR STATUS)             **/
/******************************************************************/
enu_system_status_t sos_create_task(uint8_t u8_a_task_id , uint16t u16_a_task_periodicity , void (* ptr_func_task) (void) , enu_task_cycle_t enu_task_cycle )
{
	enu_system_status_t enu_create_task_status = SOS_STATUS_SUCCESS ; /** VARIABLE TO RETURN THE FUNCTION STATUS **/
	
	/** CHECK IF THE TASK INSIDE THE MAX NUMBER AND ITS HANDLER IS AVAILABLE **/
	if ((str_gl_tasks_data[u8_a_task_id].ptr_func_task_handler == NULL) && (u8_a_task_id < MAX_TASKS))
	{
		str_gl_tasks_data[u8_a_task_id].u8_a_task_id = u8_a_task_id ;                                  /** TASK ID                         **/
		str_gl_tasks_data[u8_a_task_id].u16_a_task_periodicity = u16_a_task_periodicity ;              /** TASK ID                         **/
		str_gl_tasks_data[u8_a_task_id].ptr_func_task_handler = ptr_func_task ;    /** TASK HANDLER POINTS TO THE TASK **/
		str_gl_tasks_data[u8_a_task_id].enu_task_cycle_type = enu_task_cycle  ;    /** TASK CYCLIC TYPE                **/
		str_gl_tasks_data[u8_a_task_id].u8_a_task_ready_flag = 0 ;                 /** TASK IS READY TO BE EXECUTED    **/
	}
	
	/** TASK ID DUPLICATED OR MAX TASKS EXCEEDED **/
	else
	{
		/** ERROR ACCESSING **/
		enu_create_task_status = SOS_STATUS_INVALID_STATE ;
	}
	
	return enu_create_task_status ; /** RETURN THE FINAL STATUS **/
	
}

/******************************************************************/
/** FUNCTION TO DELETE TASK                                      **/
/** PARAMETERS  : TASK_ID (TO BE DELETED)                        **/
/** RETURNS     : enu_system_status_t (ERROR STATUS)             **/
/******************************************************************/
enu_system_status_t sos_delete_task(uint8_t u8_a_task_id)
{
	enu_system_status_t enu_delete_task_status = SOS_STATUS_SUCCESS ; /** VARIABLE TO RETURN THE FUNCTION STATUS **/
	
	/** CHECK IF THE TASK NOT CREATED OR MAX TASKS NUMBER EXCEEDED **/
	if ( (str_gl_tasks_data[u8_a_task_id].u8_a_task_id > MAX_TASKS) || (str_gl_tasks_data[u8_a_task_id].ptr_func_task_handler == NULL))
	{
		enu_delete_task_status = SOS_STATUS_INVALID_STATE ; /** INVALID STATUS **/
	}
	
	else
	{
		/** TASK HANDLER POINTS TO NULL **/
		str_gl_tasks_data[u8_a_task_id].ptr_func_task_handler = NULL ;
	}
	
	return enu_delete_task_status ; /** RETURN THE FINAL STATUS **/
}

/***********************************************************************/
/** FUNCTION TO DELETE TASK                                           **/
/** PARAMETERS  : TASK_ID , TASK_PERIODICITY , POINTER TO TASK        **/
/** RETURNS     : enu_system_status_t (ERROR STATUS)                  **/
/***********************************************************************/
enu_system_status_t sos_modify_task(uint8_t u8_a_task_id , uint16t u16_a_task_periodicity , void (* ptr_func_task) (void) , enu_task_cycle_t enu_task_cycle)
{
	enu_system_status_t enu_modify_task_status = SOS_STATUS_SUCCESS ; /** VARIABLE TO RETURN THE FUNCTION STATUS **/
	
	/** CHECK IF THE TASK NOT CREATED OR MAX TASKS NUMBER EXCEEDED **/
	if ( (str_gl_tasks_data[u8_a_task_id].u8_a_task_id > MAX_TASKS) || (str_gl_tasks_data[u8_a_task_id].ptr_func_task_handler == NULL))
	{
		enu_modify_task_status = SOS_STATUS_INVALID_STATE ; /** INVALID STATUS **/
	}
	
	/** TASK IS ALREADY EXISTS **/
	else
	{
		str_gl_tasks_data[u8_a_task_id].u8_a_task_id = u8_a_task_id ;              /** TASK ID                         **/
		str_gl_tasks_data[u8_a_task_id].ptr_func_task_handler = ptr_func_task ;    /** TASK HANDLER POINTS TO THE TASK **/
		str_gl_tasks_data[u8_a_task_id].enu_task_cycle_type = enu_task_cycle  ;    /** TASK CYCLIC TYPE                **/
	}
	
	return enu_modify_task_status ; /** RETURN THE FINAL STATUS **/
}

/***************************************************************/
/** PRIVATE FUNCTION SIMULATES THE SCHEDULER                  **/
/** ARGUMENTS  : VOID                                         **/
/** RETURNS    : VOID                                         **/
/***************************************************************/
static void sos_scheduler(void)
{
	uint8_t u8_l_task_counter = 0 ; /** LOCAL VARIABLE TO LOOP OVER TASKS **/
	
	/** LOOP OVER CREATED TASKS **/
	for (u8_l_task_counter = 0 ; u8_l_task_counter < MAX_TASKS ; u8_l_task_counter++)
	{
		/** CHECK IF THE TASK IS CREATED PREVIOUSLY **/
		if ((str_gl_tasks_data[u8_l_task_counter].ptr_func_task_handler != NULL))
		{
			if( str_gl_tasks_data[u8_l_task_counter].u8_a_task_ready_flag == TASK_READY ) /** CHECK THE TASK PERIODICITY **/
			{
				
 				if (str_gl_tasks_data[u8_l_task_counter].enu_task_cycle_type == ONE_TIME_EXECUTED_TASK) /** TASK TO BE EXECUTED ONLY ONE TIME **/
 				{
 					str_gl_tasks_data[u8_l_task_counter].ptr_func_task_handler(); /** EXECUTE THE TASK HANDLER **/
 					
 					sos_delete_task(u8_l_task_counter); /** DELETE THE TASK SO THAT IT WILL NOT BE EXECUTED AGAIN **/
 				}
				
				else /** PERIODIC TASK **/
				{
					str_gl_tasks_data[u8_l_task_counter].u8_a_task_ready_flag = str_gl_tasks_data[u8_l_task_counter].u16_a_task_periodicity - 1; /** UPDATE READY FLAG **/
					
					str_gl_tasks_data[u8_l_task_counter].ptr_func_task_handler(); /** EXECUTE THE TASK HANDLER **/
			
				}
			}
			
			else /** TASK ISN'T READY NOW **/
			{
				str_gl_tasks_data[u8_l_task_counter].u8_a_task_ready_flag-- ; /** DECREASE THE READY FLAG BY 1 **/
			}
		}
		
		else
		{
			/** IN CASE OF TASK DELETED , DO NOTHING **/	
		}
	}
}

/***********************************************************************/
/** FUNCTION TO START SOS SCHEDULING TASK                             **/
/** PARAMETERS  : VOID                                                **/
/** RETURNS     : VOID                                                **/
/***********************************************************************/
void sos_run(void)
{
	TMR0_start(); /** TIMER0 START COUNTING **/
}

/***************************************************************/
/** FUNCTION TO INITIALIZE THE SOS DATABASE                   **/
/** PARAMETERS  : VOID                                        **/
/** RETURNS     : enu_system_status_t (ERROR STATUS)          **/
/***************************************************************/
enu_system_status_t sos_init(void)
{
	TMR0_setcallback(sos_scheduler) ; /** CALL SCHEDULER IN EACH OVERFLOW **/
	
	TMR0_init();  /** INITIALIZE TIMER 0 **/
}

/***************************************************************/
/** FUNCTION TO RESET THE SOS DATABASE TO INVALID VALUES      **/
/** PARAMETERS  : VOID                                        **/
/** RETURNS     : VOID                                        **/
/***************************************************************/
void sos_deinit(void)
{
	uint8_t u8_l_task_counter = 0 ; /** LOCAL VARIABLE TO LOOP OVER TASKS **/
	
	/** LOOP OVER CREATED TASKS **/
	for (u8_l_task_counter = 0 ; u8_l_task_counter < MAX_TASKS ; u8_l_task_counter++)
	{
		/** TASK HANDLER POINTS TO NULL **/
		str_gl_tasks_data[u8_l_task_counter].ptr_func_task_handler = NULL ;
	}
		
}

/***********************************************************************/
/** FUNCTION TO STOP SOS SCHEDULING TASK                              **/
/** PARAMETERS  : VOID                                                **/
/** RETURNS     : enu_system_status_t (ERROR STATUS)                  **/
/***********************************************************************/
enu_system_status_t sos_disable(void)
{
	TMR0_stop();  /** STOP TIMER 0 **/
	
	
}