#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_spi.h"
#include <tm_stm32f4_delay/tm_stm32f4_delay.h>
#include "tm_stm32f4_disco.h"
#include <tm_stm32f4_pcd8544/tm_stm32f4_pcd8544.h>
#include <stdio.h>





int main(void) {

	 float odl;
	SystemInit();
	PCD8544_Init(0x40);
	PCD8544_SetContrast(50);



	  UB_HCSR04_Init();


	TM_DELAY_Init();
	TM_DISCO_LedInit();


	char buf[100];



	while (1) {
		    odl=UB_HCSR04_Distance_cm();
		    sprintf(buf,"%f", odl);
		    if(odl>0) {
			    PCD8544_Clear();
				  PCD8544_Puts(buf, PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
		    } else {
			    PCD8544_Clear();
				  PCD8544_Puts("Blad czujnika", PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
		    }
		    PCD8544_Refresh();
	}



}
