/*////////////////////////////////////////////////////////////////////////////////	 

// Functions to configure pins as inputs or outputs

****************************************************************************************************
//=========================================Power Supply============================================//
//     Pin  LCD side		STM32side
//      1  	VCC       	DC5V/3.3V      
//      2 	GND       	GND          
//=======================================SPI for the LCD==========================================//
//     Pin  LCD side		STM32side
//    	6  	SDI (MOSI)	PB15	Output for STM
//    	7  	SCK         PB13  Output for STM
//    	9 	SDO (MISO)  PB14  Input for STM
 //=======================================CONTROL PINS FOR LCD==========================================//
//     Pin  LCD side		STM32side
//      8 LED					PA9     Output for STM     
//      5	D/C   			PB1			Output for STM
//      4	RST 				PA7 		Output for STM
//      3	CS          PA5    	Output for STM     
//========================================= TOUCH CONTROL PINS=========================================//
//     Pin  LCD side	STM32side
//      10 T_CLK    	PB9     Output for STM
//      11 T_CS       PB7     Output for STM
//      12 T_DIN      PB5			Output for STM
//      13 T_DO       PA15    Input for STM
//      14 T_IRQ      PA11    Input for STM
**************************************************************************************************/	
 /* @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING PROGRAMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, AUTHORS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY PROGRAMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**************************************************************************************************/
#include "main.h"
#include "GPIOS.h"
#include "mode_LL_HAL.h"


#ifdef USE_HAL_DRIVER
    void  HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
    #define GPIO_Init(a,b) HAL_GPIO_Init(a,b)
    // #include "stm32f1xx_hal_rcc.h"
#endif
#ifdef USE_LL_DRIVER
    void  LL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef_Std *GPIO_Init);
    #define GPIO_Init(a,b) HAL_GPIO_Init(a,b)
#endif


#define PX(X,y) (P##X##y)  	// To be called as PX(A,in)(0) to yield PAin(0)
#define RCC_APB2(X) (RCC_APB2Periph_GPIO##X)


void Configure_GPO(GPIO_TypeDef * GPIOX, int pin)
{
	// __HAL_RCC_AFIO_CLK_ENABLE();
	
	Enable_RCC_APB2Clock(GPIOX);
	GPIO_InitTypeDef GPIO_InitStructure;	//GPIO
	GPIO_InitStructure.Pin = pin;
#if USE_HAL_DRIVER
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;  
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
#elif USE_FULL_LL_DRIVER
    GPIO_InitStructure.Mode = LL_GPIO_MODE_OUTPUT;  
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
#endif
	GPIO_Init(GPIOX, &GPIO_InitStructure);	
}
void Configure_GPI(GPIO_TypeDef * GPIOX, int pin)
{
	// RCC_APB2PeriphClockCmd(Get_RCC_APB2Periph(GPIOX),ENABLE);
	Enable_RCC_APB2Clock(GPIOX);
	GPIO_InitTypeDef GPIO_InitStructure;	//GPIO
	GPIO_InitStructure.Pin = pin;

    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;  
	GPIO_InitStructure.Pull = GPIO_PULLUP;

	GPIO_Init(GPIOX, &GPIO_InitStructure);	
}
#if USE_FULL_LL_DRIVER
#if defined Is_a_stm32f40x_41x
#define BUS_PERIPH(x) (LL_AHB1_GRP1_PERIPH_##x)
#define Enable_Bus_Clock(a) LL_AHB1_GRP1_EnableClock(a)
#elif defined Is_a_stm32f10x
#define Enable_Bus_Clock(a) LL_APB2_GRP1_EnableClock(a)
#define BUS_PERIPH(x) (LL_APB2_GRP1_PERIPH_##x)
#endif
#endif

void Enable_RCC_APB2Clock(GPIO_TypeDef * GPIOx)
{
    #if defined USE_FULL_LL_DRIVER
    if (GPIOx == GPIOA)
		Enable_Bus_Clock(BUS_PERIPH(GPIOA));
    else if (GPIOx == GPIOB)
		Enable_Bus_Clock(BUS_PERIPH(GPIOB));
    else if (GPIOx == GPIOC) 
		Enable_Bus_Clock(BUS_PERIPH(GPIOC));
    else if (GPIOx == GPIOD) 
		Enable_Bus_Clock(BUS_PERIPH(GPIOD));
    #elif defined USE_HAL_DRIVER
    if (GPIOx == GPIOA)
		__HAL_RCC_GPIOA_CLK_ENABLE();
    else if (GPIOx == GPIOB)
		__HAL_RCC_GPIOB_CLK_ENABLE();
    else if (GPIOx == GPIOC) 
		__HAL_RCC_GPIOC_CLK_ENABLE();
    else if (GPIOx == GPIOD) 
		__HAL_RCC_GPIOD_CLK_ENABLE();
    #else
    #error "Only for use with LL or HAL library"
    #endif

}
/*
uint32_t Get_RCC_APB2Periph(GPIO_TypeDef * GPIOx)
{
	// assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	
	if ((GPIOx == GPIOA) != 0)
		return RCC_APB2Periph_GPIOA;
	if ((GPIOx == GPIOB) != 0)
		return RCC_APB2Periph_GPIOB;
	if ((GPIOx == GPIOC) != 0)
		return RCC_APB2Periph_GPIOC;
	if ((GPIOx == GPIOD) != 0)
		return RCC_APB2Periph_GPIOD;
	if ((GPIOx == GPIOE) != 0)
		return RCC_APB2Periph_GPIOE;
	if ((GPIOx == GPIOF) != 0)
		return RCC_APB2Periph_GPIOF;
	if ((GPIOx == GPIOG) != 0)
		return RCC_APB2Periph_GPIOG;
		
	return 0;
}*/
