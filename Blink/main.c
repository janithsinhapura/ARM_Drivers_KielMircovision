#include "stm32f4xx.h"

void delayMS(int delay);

int main(void)
{
	RCC->AHB1ENR |= (1<<2); //enable GPIOC clock
	GPIOC->MODER |= GPIO_MODER_MODE13_0; //PIN 13 in GPIOC output
	
	
		while(1)
		{
			GPIOC->ODR = GPIO_ODR_OD13;
			delayMS(500);
			GPIOC->ODR &=~GPIO_ODR_OD13;
			delayMS(500);
		}
}

void delayMS(int delay)
{
	int i,j;
	for(j = 0;delay>j;delay--)
	{
		for(i = 0;i<3195;i++)
		{
			
		}
	}
}

