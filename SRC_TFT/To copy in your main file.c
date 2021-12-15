/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "delay.h"
#include "LCD.h"
#include "test.h"
/* USER CODE END Includes */


  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
	LCD_Init();	  

	while (1)
	{	
		main_test(); 		
		//Test_Color();  		
		Test_FillRec();		
		Test_Circle(); 		
		Test_Triangle();   
		Spanish_Font_test();
		//Chinese_Font_test();
		Pic_test();			
		Rotate_Test(); 
		Touch_Test();
    /* USER CODE END WHILE */

