
// Pinout for your development system. You can choose another available pins,
// although you will have to reserve the SPI pins.
// Please check if you will use SPI1 or SPI2 (probably SPI2 for STM32f10x and SPI1 for STM32F4xx).

#include "Hardware_Definition.h"
#if defined USE_HAL_DRIVER
#define PIN(x) (GPIO_PIN_##x)		// To be called as PIN(0) to yield GPIO_PIN_0
#elif defined USE_FULL_LL_DRIVER
#define PIN(x) (LL_GPIO_PIN_##x)		// To be called as PIN(0) to yield LL_GPIO_PIN_0
#else
    #error "Only for use with LL or HAL library"
#endif

#define gpio(X,Y)   GPIO##X,PIN(Y)

#if defined (Is_a_stm32f10x) 
// LCD outputs
#define PORT_CS 		GPIOA
#define PIN_CS			PIN(10)
#define PORT_RST		GPIOA
#define PIN_RST			PIN(11)
#define PORT_DC 		GPIOA
#define PIN_DC			PIN(12)

#define PORT_LED 		GPIOA
#define PIN_LED			PIN(15)



// Touch outputs
#define PORT_TCLK 	    GPIOB
#define PIN_TCLK		PIN(3)    
#define PORT_TCS 		GPIOB
#define PIN_TCS			PIN(4)     
#define PORT_TDIN 	    GPIOB
#define PIN_TDIN		PIN(5)   

// Touch Inputs 
#define PORT_TDO		GPIOB
#define PIN_TDO			PIN(6) 
#define PORT_TIRQ		GPIOB
#define PIN_TIRQ		PIN(7) 

#endif


#if defined (Is_a_stm32f40x_41x)
// LCD outputs
#define PORT_CS 		GPIOC
#define PIN_CS			PIN(9)

#define PORT_RST		GPIOB
#define PIN_RST			PIN(8)

#define PORT_DC 		GPIOB
#define PIN_DC			PIN(9)


#define PORT_LED 		GPIOB
#define PIN_LED			PIN(4)



// Touch outputs
#define PORT_TCLK 	    GPIOA
#define PIN_TCLK		PIN(6)   


#define PORT_TCS 		GPIOA
#define PIN_TCS			PIN(7)   


#define PORT_TDIN 	    GPIOB
#define PIN_TDIN		PIN(6)



// Touch Inputs 
#define PORT_TDO		GPIOC
#define PIN_TDO			PIN(7)


#define PORT_TIRQ		GPIOA
#define PIN_TIRQ		PIN(9) 


#endif



// ------------------   LCD  MACROS -----------------------------

#define LCD_CS_SET 		PXset(PORT_CS,PIN_CS)    
#define LCD_CS_CLR 		PXreset(PORT_CS,PIN_CS)   
#define LCD_RST_SET 	PXset(PORT_RST,PIN_RST)  		
#define LCD_RST_CLR 	PXreset(PORT_RST,PIN_RST)  	
#define LCD_DC_RS_SET   PXset(PORT_DC,PIN_DC)				
#define LCD_DC_RS_CLR   PXreset(PORT_DC,PIN_DC)				
#define LCD_LED_SET     PXset(PORT_LED,PIN_LED)				
#define LCD_LED_CLR     PXreset(PORT_LED,PIN_LED)	


// ------------------   TOUCH  MACROS -----------------------------

#define T_DIN_Set 		PXset(PORT_TDIN,PIN_TDIN)    
#define T_DIN_Reset 	PXreset(PORT_TDIN,PIN_TDIN)  
#define T_CLK_Set 		PXset(PORT_TCLK,PIN_TCLK)  		
#define T_CLK_Reset 	PXreset(PORT_TCLK,PIN_TCLK)  	
#define T_CS_Set   		PXset(PORT_TCS,PIN_TCS)				
#define T_CS_Reset   	PXreset(PORT_TCS,PIN_TCS)				

#define T_IRQ  			PXin(PORT_TIRQ,PIN_TIRQ)    //  INT
#define T_DO 			PXin(PORT_TDO,PIN_TDO)  //  MISO
	 



