// Header: Toggles PA0 pin every 1 second when the compare match occurs
// File Name: 
// Author: Janith Sinhapura
// Date:

#include "stm32f4xx.h"

int main(void)
{
	//GPIOA PA0 configured as alternate function
	RCC->AHB1ENR |=1;
	GPIOA->MODER |=(1<<1);
	GPIOA->AFR[0] |=1; //set PA0 alternate function for timer2
	
	//Configuring timer 2
	RCC->APB1ENR |=1;
	TIM2->PSC = 1600-1;
	TIM2->ARR = 10000-1; //counter counts upto 10000
	TIM2->CCER |=1;//enable compare mode
	TIM2->CCMR1 |=(1<<5)|(1<<4); //ouput ch1 toggle on compare match
	TIM2->CCR1 = 0;//set compare match value to zero
	TIM2->CNT = 0;//set initial timer counter value to zero
	TIM2->CR1 |=1;//enable timer 2
	
	while(1)
	{
		
	}
}
