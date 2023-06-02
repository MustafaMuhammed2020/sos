/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 31 May , 2023                        */
/* Version : V01                                  */
/* Hint    : APIs of SOS                          */
/**************************************************/

#ifndef SOS_INTERFACE_H_
#define SOS_INTERFACE_H_

/** TYPE DEFINITION FOR FUNCTION'S RETURN STATUS **/ 
typedef enum { SOS_STATUS_INVALID_STATE = 0 , SOS_STATUS_SUCCESS} enu_system_status_t ; 

/** TYPE DEFINITION FOR THE TASK TYPE **/
typedef enum { ONE_TIME_EXECUTED_TASK = 0 , PERIODIC_TASK } enu_task_cycle_t ;


/******************************************************************/
/** FUNCTION TO CREATE TASK                                      **/
/** PARAMETERS  : TASK_ID , TASK_PERIODICITY , POINTER TO TASK   **/
/** RETURNS     : enu_system_status_t (ERROR STATUS)             **/
/******************************************************************/
enu_system_status_t sos_create_task(uint8_t u8_a_task_id , uint16t u16_a_task_periodicity , void (* ptr_func_task) (void) , enu_task_cycle_t enu_task_cycle );

/******************************************************************/
/** FUNCTION TO DELETE TASK                                      **/
/** PARAMETERS  : TASK_ID (TO BE DELETED)                        **/
/** RETURNS     : enu_system_status_t (ERROR STATUS)             **/
/******************************************************************/
enu_system_status_t sos_delete_task(uint8_t u8_a_task_id);

/***********************************************************************/
/** FUNCTION TO DELETE TASK                                           **/
/** PARAMETERS  : TASK_ID , TASK_PERIODICITY , POINTER TO TASK        **/
/** RETURNS     : enu_system_status_t (ERROR STATUS)                  **/
/***********************************************************************/
enu_system_status_t sos_modify_task(uint8_t u8_a_task_id , uint16t u16_a_task_periodicity , void (* ptr_func_task) (void) , enu_task_cycle_t enu_task_cycle);

/***********************************************************************/
/** FUNCTION TO START SOS SCHEDULING TASK                             **/
/** PARAMETERS  : VOID                                                **/
/** RETURNS     : VOID                                                **/
/***********************************************************************/
void sos_run(void);

/***********************************************************************/
/** FUNCTION TO STOP SOS SCHEDULING TASK                              **/
/** PARAMETERS  : VOID                                                **/
/** RETURNS     : enu_system_status_t (ERROR STATUS)                  **/
/***********************************************************************/
enu_system_status_t sos_disable(void);

/***************************************************************/
/** FUNCTION TO INITIALIZE THE SOS DATABASE                   **/
/** PARAMETERS  : VOID                                        **/
/** RETURNS     : enu_system_status_t (ERROR STATUS)          **/
/***************************************************************/
enu_system_status_t sos_init(void);

/***************************************************************/
/** FUNCTION TO RESET THE SOS DATABASE TO INVALID VALUES      **/
/** PARAMETERS  : VOID                                        **/
/** RETURNS     : VOID                                        **/
/***************************************************************/
void sos_deinit(void);

#endif /* SOS_INTERFACE_H_ */