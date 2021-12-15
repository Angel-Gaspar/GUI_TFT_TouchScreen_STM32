/*
 * main_loop.c
 *
 *  Created on: Nov 30, 2021
 *      Author: Ángel Gaspar González Rodríguez
 */
#include "main_loop.h"
#include "delay.h"
#include "LCD.h"
#include "test.h"
#include "gui_match_conf.h"
#include "touch.h"
#include "func_gui_touch.h"
#include "typedef.h"
#include "func_glob.h"

#include "structs_var_glob.h"

// #define USING_IRQ_FOR_TOUCH_DETECTION  ToDo Make it work with interruptions

#define TXBUFFERSIZE 5
#define RXBUFFERSIZE TXBUFFERSIZE



__IO ITStatus Transmission_Completed_Master = RESET;
__IO ITStatus Reception_Completed_Master = RESET;
uint8_t aTxBuffer[TXBUFFERSIZE] ;
uint8_t aRxBuffer[RXBUFFERSIZE];


void main_setup(void) {
	void Save_SysTick_values_for_LL_HAL(void);
	Save_SysTick_values_for_LL_HAL();
	SystemInit();
	delay_init(SysTick->LOAD / 1000);

	LCD_Init();
	set_window_match_configuration();
	TP_Init();	
}
void main_loop(void) {
#if !defined(USING_IRQ_FOR_TOUCH_DETECTION)
	TP_Scan(1);
	if (get_TP_status() & TP_PRES_DOWN) {
		point16 pt16;
		get_TP(&pt16);
		if (pt16.x < lcddev.width && pt16.y < lcddev.height) {
			manage_touch(pt16);
		}
	} else {
		Sleep(10);
	}
#endif
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
#if defined(USING_IRQ_FOR_TOUCH_DETECTION)
	if (GPIO_Pin == 1<<PIN_TIRQ) {
		get_touched_position(1);
		point16 pt16;
		get_TP(&pt16);
		if (pt16.x < lcddev.width && pt16.y < lcddev.height) {
			manage_touch(pt16);
		}
	}
#endif
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle) { 
	Transmission_Completed_Master = SET; 
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) { 
	Reception_Completed_Master = SET; 
}

extern __IO uint32_t uwTick;
extern HAL_TickFreqTypeDef uwTickFreq;
void HAL_IncTick(void)
{
  uwTick += uwTickFreq;
  if (gui.timer_enabled && HAL_GetTick() % 1000 == 0)
	manage_timer();
}


