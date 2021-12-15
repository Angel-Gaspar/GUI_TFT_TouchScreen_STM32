#ifndef GPIOS_H
#define GPIOS_H

#include "main.h"
//#include "sys_10x_4xx.h"
#include "stdlib.h"
#include "typedefs_int.h"
// #include "stm32f10x_gpio.h"

uint32_t Get_RCC_APB2Periph(GPIO_TypeDef * GPIOx);

void Configure_GPI(GPIO_TypeDef * GPIOX, int pin);
void Configure_GPO(GPIO_TypeDef * GPIOX, int pin);

void Enable_RCC_APB2Clock(GPIO_TypeDef * GPIOx);

// #define GPIO(x) (GPIO##x)		// To be called as GPIO(A) to yield GPIOA


#if defined USE_HAL_DRIVER
#define PXset(x,y)      HAL_GPIO_WritePin(x,y,GPIO_PIN_SET)
#define PXreset(x,y)    HAL_GPIO_WritePin(x,y,GPIO_PIN_RESET)
#define PXin(x,y)       (_Bool)HAL_GPIO_ReadPin(x,y)
#elif defined USE_FULL_LL_DRIVER
#define PXset(x,y)      LL_GPIO_SetOutputPin(x,y)
#define PXreset(x,y)    LL_GPIO_ResetOutputPin(x,y)
#define PXin(x,y)       (_Bool)LL_GPIO_IsInputPinSet(x,y)
#else
    #error "Only for use with LL or HAL library"
#endif



/*
#define PXin(x,y) (x == GPIOD ? PDin(y) :( \
                x == GPIOC ? PCin(y) :( \
               x == GPIOB ? PBin(y) : PAin(y))))
               
#define PXset(x,y) (x == GPIOD ? (PDout(y)=1) :( \
                x == GPIOC ? (PCout(y)=1) :( \
               x == GPIOB ? (PBout(y)=1) : (PAout(y)=1))))
#define PXreset(x,y) (x == GPIOD? (PDout(y)=0) :( \
                x == GPIOC ? (PCout(y)=0) :( \
               x == GPIOB ? (PBout(y)=0) : (PAout(y)=0))))*/
/*
#define RCC_APB2(X) (RCC_APB2Periph_GPIO##X)

#define RCC_APB2_2(X,Y) (RCC_APB2(X)|RCC_APB2(Y))
#define RCC_APB2_3(X,Y,Z) (RCC_APB2(X)|RCC_APB2(Y)|RCC_APB2(Z))
#define RCC_APB2_4(X,Y,Z,Q) (RCC_APB2(X)|RCC_APB2(Y)|RCC_APB2(Z)|RCC_APB2(Q))*/

#endif
