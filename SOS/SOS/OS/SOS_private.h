/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 31 May , 2023                        */
/* Version : V01                                  */
/* Hint    : private file of of SOS               */
/**************************************************/

#ifndef SOS_PRIVATE_H_
#define SOS_PRIVATE_H_

#define TASK_READY    0

/************************************************************/
/**          TYPE DEFINITION OF TASK STRUCT                **/
/**  THIS STRUCT CONTAINS TASK DATA                        **/
/**           1 - TASK ID                                  **/
/**           2 - TASK PERIODICITY                         **/
/**           3 - TASK HANDLER                             **/
/**           4 - TASK TYPE (CYCLIC / ONE TIME EXECUTED)   **/
/**           5 - TASK READY FLAG                          **/
/************************************************************/
typedef struct 
{
	uint8_t u8_a_task_id  ;
	
	uint16t u16_a_task_periodicity ;
	
	void (* ptr_func_task_handler) (void) ;
	
	enu_task_cycle_t enu_task_cycle_type ;
	
	uint16t u8_a_task_ready_flag ;
	 	
}str_task_t ;  

/***************************************************************/
/** PRIVATE FUNCTION SIMULATES THE SCHEDULER                  **/
/** ARGUMENTS  : VOID                                         **/
/** RETURNS    : VOID                                         **/
/***************************************************************/
static void sos_scheduler(void) ;

#endif /* SOS_PRIVATE_H_ */