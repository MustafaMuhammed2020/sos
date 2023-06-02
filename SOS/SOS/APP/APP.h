/**************************************************/
/* Author  : Mustafa Mohammed Abdou               */
/* Date    : 31 May , 2023                        */
/* Version : V01                                  */
/* Hint    : application layer APIs               */
/**************************************************/

#ifndef APP_H_
#define APP_H_

/** TASKS ID **/
#define TASK1     0
#define TASK2     1
#define TASK3     2
#define TASK4     3

/** TASKS PERIODICITY IN ms  **/
#define TASK1_PERIODICITY     0
#define TASK2_PERIODICITY     1
#define TASK3_PERIODICITY     300
#define TASK4_PERIODICITY     500


/** LED1 TOGGLE TASK **/
void LED1_task(void);


/** LED2 TOGGLE TASK **/
void LED2_task(void);


/** SOS STOP TASK **/
void Stop_button_task(void);


/** CALLBACK FUNCTION OF EXTINT0 **/
void start_button(void);


/** INITIALIZATION TASK **/
void APP_init(void);


/** MAIN LOGIC **/
void APP_start(void);

#endif /* APP_H_ */