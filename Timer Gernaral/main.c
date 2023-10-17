// Header: This firmware triggers a counter overflow event at 1Hz. PA0 pin LED toggles at 1 second.
// File Name: 
// Author: Janith Sinhapura
// Date:


#include "stm32f4xx.h"

int main(void)
{
	//timer2 is in APB1 Bus
	//timer2 channel 1 is connected to PA0
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= (1); //PA0 set to alternate function
	
	RCC->APB1ENR |=1; // enable clock for timer2
	TIM2->PSC = 1600-1;  // counter clock frquency = (fclk/prescaler+1) = 10000Hz. So 10000 cycles in 1 second
	TIM2->ARR = 10000-1; // it takes 1second to count to 10000 from 0.
	TIM2->CNT = 0; // //set timer counter value to zero (Not Necessary)
	TIM2->CR1 |= 1; //counter enable and upcounting
	while(1)
	{
		while(!(TIM2->SR &1)){} //wait until count overflow status occur. check UIF bit in TIM_SR register
			TIM2->SR &=~(1);//after that set UIF bit to zero in TIM_SR register
			GPIOA->ODR ^=(1);//toggle PA0 pin in each counter overflow
	}
}
