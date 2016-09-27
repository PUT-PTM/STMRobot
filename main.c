#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_tim.h"
#include <stm32f4xx_usart.h>
#include "misc.h"
#include "tm/tm_stm32f4_pcd8544.h"

long counter = 0;
long counter2 = 0;
int distArray[19] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float odl;
int obstacle = 100;
int action = 80;
int stopped = 1;

        void SetMotorBits(int m1a, int m1b, int m2a, int m2b){
                GPIO_ResetBits(GPIOA, GPIO_Pin_6);
                GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_8);
                GPIO_ResetBits(GPIOE, GPIO_Pin_2);
                if(m1a == 1 ) GPIO_SetBits(GPIOA, GPIO_Pin_6);
                if(m1b == 1 ) GPIO_SetBits(GPIOB, GPIO_Pin_0);
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
}

void setupLedAndButton()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	SystemInit();
	SystemCoreClockUpdate();
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	TIM_TimeBaseStructure.TIM_Period= 11;
	TIM_TimeBaseStructure.TIM_Prescaler= 6;
	TIM_TimeBaseStructure.TIM_ClockDivision= TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode= TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM4,ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_TimeBaseStructure.TIM_Period= 3000;
	TIM_TimeBaseStructure.TIM_Prescaler= 10500;
	TIM_TimeBaseStructure.TIM_ClockDivision= TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode= TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM3,ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update,ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update,ENABLE);


}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{

			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		if(action > 20)
		{
			PCD8544_Clear();
			PCD8544_Puts("MOTORS TESTING", PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
			PCD8544_Refresh();

			if(action < 101)
			{
				PCD8544_Puts("WAITING", PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
				PCD8544_Refresh();
				SetMotorBits(0,0,0,0);
				action++;
			}

			if(action <= 104 && action > 100)
			{
				PCD8544_Puts("SPIN RIGHT", PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
				PCD8544_Refresh();
				spinRight();
				action++;
			}

			if(action > 104 && action <= 108)
			{
				PCD8544_Puts("SPIN LEFT", PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
				PCD8544_Refresh();
				spinLeft();
				action++;
			}

			if(action > 108 && action <= 112)
			{
				PCD8544_Puts("FORWARD", PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
				PCD8544_Refresh();
				driveForward();
				action++;
			}

			if(action > 112 && action <= 116)
			{
				PCD8544_Puts("BACKWARD", PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
				PCD8544_Refresh();
				driveBackward();
				action++;
			}

			if(action > 116 && action <= 120)
			{

				driveForward();
				action++;
			}

			if(action == 121)
			{
				action = 0;
			}
		}
		else
		{
			if(action < 3)
			{
				if(odl <= 0){
					driveBackward();
				}
				else if(odl < obstacle)
				{
					spinLeft();
				}
				else
				{
					driveForward();
				}
				action = 0;
			}
			else
			{
				action++;
			}
		}
		}
}

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		counter++;
		counter2++;
	}
}

void delay_us(int x)
{
	counter2 = 0;
	while(counter2 <= x)
	{
	}
}

void HCSRinit(){
	/* PD14 for trigger pin */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GPIOD_InitDef;
	GPIOD_InitDef.GPIO_Pin = GPIO_Pin_14;
	GPIOD_InitDef.GPIO_OType = GPIO_OType_PP;
	GPIOD_InitDef.GPIO_Mode = GPIO_Mode_OUT;
	GPIOD_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIOD_InitDef.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIOD_InitDef);

	/* PD10 for echo pin */
	GPIO_InitTypeDef GPIO_InitDef;
	GPIO_InitDef.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitDef);
}

float CheckDistance(){
	/* PD14 Trigger
	 * PD PD10 Echo
	 */
	uint32_t time = 0;
	GPIO_ResetBits(GPIOD, GPIO_Pin_14);
	delay_us(5);
	GPIO_SetBits(GPIOD,GPIO_Pin_14);
	delay_us(13);
	GPIO_ResetBits(GPIOD,GPIO_Pin_14 | GPIO_PinSource10);

	uint32_t timeout = 1000000;
	while (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10)) {
			if (timeout-- == 0x00) {
				return -1;
			}
	}
	int licznik = 0;
	int pomiarTrwa = 1;
	int przerwaniePomiaru = 0;
	counter = 0;
	counter2 = 0;

	while(pomiarTrwa != 0)
	{
		time++;
		licznik++;
		if(!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10))
		{
			przerwaniePomiaru++;
		}
		if(przerwaniePomiaru >= 15)
		{
			pomiarTrwa = 0;
		}
	}
	if(counter > 600)
	{
		setDist(counter);
	}
	float distance = (float) (median()*34)/1000/2;
	return distance;
}



void setDist(int x)
{
	int i = 17;
	while(i != -1)
	{
		distArray[i+1] = distArray[i];
		i--;
	}
	distArray[0] = x;
}

int median()
{
	int init = 0;
	int tempArray[19] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	while(init != 19)
	{
		tempArray[init] = distArray[init];
		init++;
	}
	int i = 0;
	int j = 0;
	int min;

	while(j != 18)
	{
		i = j;
		min = j;
		while(i != 19)
		{
			if(tempArray[i] < tempArray[min])
			{
				min = i;
			}
			i++;
		}
		int tmp = tempArray[j];
		tempArray[j] = tempArray[min];
		tempArray[min] = tmp;
		j++;
	}
	return tempArray[9];
}

void toggle(int diode)
{
	switch (diode)
	{
		case 0:
		{
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
			break;
		}

		case 1:
		{
			GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
			break;
		}
		case 2:
		{
			GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
			break;
		}
		case 3:
		{
			GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
			break;
		}
	}
}

int main(void)
{
	SystemInit();
	setupLedAndButton();
	HCSRinit();
    MotorGPIOinit();

    PCD8544_Init(0x40);
    PCD8544_SetContrast(50);
	PCD8544_Clear();
	PCD8544_Puts("BTN TO START", PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
	PCD8544_Refresh();


    while(1)
    {

    	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
    				turnAllOn();
    	        }
     	diod(odl);

    	PCD8544_Clear();
     	if(odl <= 0){
     						PCD8544_Puts("BACKWARD", PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
     						PCD8544_Refresh();
     					}
     					else if(odl < obstacle)
     					{
     						PCD8544_Puts("SPIN", PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
     						PCD8544_Refresh();
     					}
     					else
     					{
     						PCD8544_Puts("FORWARD", PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
     						PCD8544_Refresh();
     					}
    	odl = CheckDistance();
    }
}
void turnOff(int x)
{
	switch(x)
	{
		case 0:
		{
			GPIO_ResetBits(GPIOD, GPIO_Pin_12);
			break;
		}
		case 1:
		{
			GPIO_ResetBits(GPIOD, GPIO_Pin_13);
			break;
		}
		case 3:
		{
			GPIO_ResetBits(GPIOD, GPIO_Pin_15);
			break;
		}
	}
}

void diod(int x)
{
	if(x < 30)
	{
		turnAllOff();
	}

	if(x > 30)
	{
		turnAllOff();
		turnOn(1);
	}

	if(x > 50)
	{
		turnAllOff();
		turnOn(1);
		turnOn(2);
	}

	if(x > 120)
	{
		turnAllOn();
	}

}

void turnOn(int x)
{
	switch(x)
	{
		case 0:
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_12);
			break;
		}
		case 1:
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_13);
			break;
		}
		case 2:
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_15);
			break;
		}
	}
}

void turnAllOn()
{
	int i;
	for(i = 0; i < 3; i++)
	{
		turnOn(i);
	}
}

void turnAllOff()
{
	int i;
	for(i = 0; i < 3; i++)
	{
		turnOff(i);
	}
}
