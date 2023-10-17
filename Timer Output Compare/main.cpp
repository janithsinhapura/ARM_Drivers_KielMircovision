#include "stm32f4xx.h"

int main(void)
{
	RCC->AHB1ENR |=1;
	GPIOA->MODER |=(1<<1);
	
	while(1)
	{
		
	}
}
