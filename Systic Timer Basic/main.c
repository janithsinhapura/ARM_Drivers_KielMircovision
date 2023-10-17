#include "stm32f4xx.h"

void GPIO_Init(void);
void SysTick_Conf(void);//1 second ticks

int main(void)
{
	SysTick_Conf();
	GPIO_Init();
	
	while(1)
	{
		if(SysTick->CTRL & (1<<16))
		{
			GPIOC->ODR ^=GPIO_ODR_OD13;
		}
	}
}

void GPIO_Init(void)
{
	RCC->AHB1ENR |=(1<<2);
	
	GPIOC->MODER |= (1<<26);
}

void SysTick_Conf(void)
{
	SysTick->LOAD = 16000000-1; //delay 1000ms
	SysTick->VAL = 0;
	SysTick->CTRL |= (1)|(1<<2);
	
}
