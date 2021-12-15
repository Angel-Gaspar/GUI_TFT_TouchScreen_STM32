/*
 * main_loop.h
 *
 *  Created on: Nov 30, 2021
 *      Author: Ángel Gaspar González Rodríguez
 */

#ifndef SRC_MAIN_LOOP_H_
#define SRC_MAIN_LOOP_H_

#include "main.h"

void main_setup(void) ;

void main_loop(void) ;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle) ;
	
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) ;

void Tasks_SysTick(void);

#endif /* SRC_MAIN_LOOP_H_ */
