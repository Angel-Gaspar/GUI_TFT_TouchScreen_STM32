#pragma once

#if defined USE_FULL_LL_DRIVER
#define LL_GPIO_InitTypedef 						GPIO_InitTypedef

#define GPIO_PULLUP 								LL_GPIO_PULL_UP
#define GPIO_PULLDOWN 								LL_GPIO_PULL_DOWN

#define GPIO_SPEED_FREQ_LOW							LL_GPIO_SPEED_FREQ_LOW         	    /*!< Select I/O low output speed    */
#define GPIO_SPEED_FREQ_MEDIUM					    LL_GPIO_SPEED_FREQ_MEDIUM      	   /*!< Select I/O medium output speed */
#define GPIO_SPEED_FREQ_HIGH						LL_GPIO_SPEED_FREQ_HIGH        	 

#define GPIO_MODE_OUTPUT_PP							LL_GPIO_MODE_OUTPUT
#define GPIO_MODE_OUTPUT_OD							LL_GPIO_OUTPUT_OPENDRAIN

#define GPIO_MODE_INPUT									LL_GPIO_MODE_INPUT
#define GPIO_MODE_OUTPUT								LL_GPIO_MODE_OUTPUT


#define GPIO_InitTypeDef								LL_GPIO_InitTypeDef

#define GPIO_Init(a,b)                              LL_GPIO_Init(a,b)
#endif

