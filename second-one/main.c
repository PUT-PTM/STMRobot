/* Include core modules */
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_pwm.h"

int main(void) {
	SystemInit();


	/* Init PWM mode for PA2 and PE6. Using TIM9, Channel 1 and 2 */
    TM_PWM_TIM_t TIM9_Data;
    /* PA2 */
    TM_PWM_InitTimer(TIM9, &TIM9_Data, 1000);
    TM_PWM_InitChannel(&TIM9_Data, TM_PWM_Channel_1, TM_PWM_PinsPack_1);
    /* PE6 */
    TM_PWM_InitTimer(TIM9, &TIM9_Data, 1000);
    TM_PWM_InitChannel(&TIM9_Data, TM_PWM_Channel_2, TM_PWM_PinsPack_2);


    /* GPIO A */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		GPIO_InitTypeDef GPIOA_InitDef;
		GPIOA_InitDef.GPIO_Pin = GPIO_Pin_6;
		GPIOA_InitDef.GPIO_OType = GPIO_OType_PP;
		GPIOA_InitDef.GPIO_Mode = GPIO_Mode_OUT;
		GPIOA_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIOA_InitDef.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOA, &GPIOA_InitDef);
   	/* GPIO B */
   	    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
   	    GPIO_InitTypeDef GPIOB_InitDef;
   	    GPIOB_InitDef.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_8;
		GPIOB_InitDef.GPIO_OType = GPIO_OType_PP;
		GPIOB_InitDef.GPIO_Mode = GPIO_Mode_OUT;
		GPIOB_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIOB_InitDef.GPIO_Speed = GPIO_Speed_100MHz;
   	   	GPIO_Init(GPIOB, &GPIOB_InitDef);
   	 /* GPIO E */
   	    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
   	    GPIO_InitTypeDef GPIOE_InitDef;
   	    GPIOE_InitDef.GPIO_Pin = GPIO_Pin_2;
   	    GPIOE_InitDef.GPIO_OType = GPIO_OType_PP;
   	    GPIOE_InitDef.GPIO_Mode = GPIO_Mode_OUT;
   	    GPIOE_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
   	    GPIOE_InitDef.GPIO_Speed = GPIO_Speed_100MHz;
   	    GPIO_Init(GPIOE, &GPIOE_InitDef);

   	/* Setting Motor1 */
   	GPIO_SetBits(GPIOA, GPIO_Pin_6);
   	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
   	TM_PWM_SetChannelMicros(&TIM9_Data, TM_PWM_Channel_1, 1000);

   	/* Setting Motor2 */
   	GPIO_SetBits(GPIOE, GPIO_Pin_2);
   	GPIO_ResetBits(GPIOB, GPIO_Pin_8);
   	TM_PWM_SetChannelMicros(&TIM9_Data, TM_PWM_Channel_2, 1000);


    while (1) {
    		GPIO_ToggleBits(GPIOA, GPIO_Pin_6);
    		GPIO_ToggleBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_8);
    		GPIO_ToggleBits(GPIOE, GPIO_Pin_2);
    		int i=0;
    		for(i=0;i<15000000;i++){}
    }
}