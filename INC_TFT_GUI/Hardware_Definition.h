// HARDWARE_DEFINITION.H
// Select the microcontroller and the IC driver 

#pragma once


#if !defined (Is_a_stm32f40x_41x)
#if defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F401xx) || defined (STM32F411xE)
 #define Is_a_stm32f40x_41x
#endif
#endif

#if !defined (Is_a_stm32f10x)
#if defined (STM32F10X_LD) || defined (STM32F10X_LD_VL) || defined (STM32F10X_MD) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD) || defined (STM32F10X_HD_VL) || defined (STM32F10X_XL) || defined (STM32F10X_CL)
 #define Is_a_stm32f10x
#endif
#endif
#if !defined (Is_a_stm32f10x)
#if  defined(STM32F100xE) || defined(STM32F101xE) || defined(STM32F103xE) \
  || defined(STM32F101xG) || defined(STM32F103xG) \
  || defined(STM32F105xC) || defined(STM32F107xC)
   #define Is_a_stm32f10x
#endif
#endif

#if defined (STM32F103xB) && ! defined (Is_a_stm32f10x)
#define Is_a_stm32f10x
#endif


#if defined (Is_a_stm32f10x) 
#define SPI_lcd SPI2
#define hspi_lcd hspi2
#endif

#if defined (Is_a_stm32f40x_41x)
#define SPI_lcd SPI2
#define hspi_lcd hspi2
#endif


#define ILI_MODEL 9488 
// It seems that 9488 works for all of the screens, although the image is flipped for 
// some of the screens.
//#define ILI_MODEL 9486

#define ROTATION_0		0
#define ROTATION_90 	90
#define ROTATION_180 	180
#define ROTATION_270	270

#define ROTATION_SCREEN ROTATION_180
