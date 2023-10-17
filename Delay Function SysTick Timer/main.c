#include "stm32f4xx.h"

void DelayMS(int delay);

int main(void)
{
	RCC->AHB1ENR |=(1<<2); //enable GPIOC clock
	
	GPIOC->MODER |=(1<<26);//set pin PC13 Ouput
	while(1)
	{
		GPIOC->BSRR = 0x20000000;
		DelayMS(200);
		GPIOC->BSRR =0x00002000;
		DelayMS(1000);
		
	}
}

void DelayMS(int delay)
{
	SysTick->LOAD = 16000-1;
	SysTick->VAL = 0;
	SysTick->CTRL |=(1)|(1<<2);
	
	for(int i = 0;i<delay;i++)
	{
		while((SysTick->CTRL &(1<<16))==0){}
	}
	SysTick->CTRL = 0;
}
