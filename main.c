#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_spi.h"
#include <tm_stm32f4_delay/tm_stm32f4_delay.h>
#include "tm_stm32f4_disco.h"
#include <tm_stm32f4_pcd8544/tm_stm32f4_pcd8544.h>
#include <stdio.h>

/* Motor Library */
        void SetMotorBits(int m1a, int m1b, int m2a, int m2b){
                //Motor1 - PA6, PB0
                //Motor2 - PE2, PB8
                GPIO_ResetBits(GPIOA, GPIO_Pin_6);
                GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_8);
                GPIO_ResetBits(GPIOE, GPIO_Pin_2);
                if(m1a == 1 ) GPIO_SetBits(GPIOA, GPIO_Pin_0);
                if(m1b == 1 ) GPIO_SetBits(GPIOB, GPIO_Pin_6);
                if(m2a == 1 ) GPIO_SetBits(GPIOE, GPIO_Pin_2);
                if(m2b == 1 ) GPIO_SetBits(GPIOB, GPIO_Pin_8);
        }
        void driveBackward(void){
                SetMotorBits(0,1,0,1);
        }
        void driveForward(void){
                SetMotorBits(1,0,1,0);
        }
        void spinLeft(void){
                SetMotorBits(1,0,0,1);
        }
        void spinRight(void){

                SetMotorBits(0,1,1,0);
        }
        void stopMotor(void){
                SetMotorBits(0,0,0,0);
        }

void MotorGPIOinit(void){
                RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
                GPIO_InitTypeDef GPIOA_InitDef;
                GPIOA_InitDef.GPIO_Pin = GPIO_Pin_6;
                GPIOA_InitDef.GPIO_OType = GPIO_OType_PP;
                GPIOA_InitDef.GPIO_Mode = GPIO_Mode_OUT;
                GPIOA_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
                GPIOA_InitDef.GPIO_Speed = GPIO_Speed_100MHz;
                GPIO_Init(GPIOA, &GPIOA_InitDef);

            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
            GPIO_InitTypeDef GPIOB_InitDef;
            GPIOB_InitDef.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_8;
                GPIOB_InitDef.GPIO_OType = GPIO_OType_PP;
                GPIOB_InitDef.GPIO_Mode = GPIO_Mode_OUT;
                GPIOB_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
                GPIOB_InitDef.GPIO_Speed = GPIO_Speed_100MHz;
                GPIO_Init(GPIOB, &GPIOB_InitDef);

            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
            GPIO_InitTypeDef GPIOE_InitDef;
            GPIOE_InitDef.GPIO_Pin = GPIO_Pin_2;
            GPIOE_InitDef.GPIO_OType = GPIO_OType_PP;
            GPIOE_InitDef.GPIO_Mode = GPIO_Mode_OUT;
            GPIOE_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
            GPIOE_InitDef.GPIO_Speed = GPIO_Speed_100MHz;
            GPIO_Init(GPIOE, &GPIOE_InitDef);
}






int main(void) {

	 float odl;
	SystemInit();
	PCD8544_Init(0x40);
	PCD8544_SetContrast(50);
	MotorGPIOinit();



	  UB_HCSR04_Init();


	TM_DELAY_Init();
	TM_DISCO_LedInit();


	char buf[100];
	driveForward();
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
