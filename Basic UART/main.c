#include "stm32f4xx.h"
#include <stdio.h>
#include "string.h"

void UART1(void);
int UART1_write(int ch);
int UART1_read(void);
void delayMS(int delay);



int main(void)
{
	int n;
	char str[100];
	
	/*
	PA9 - TX MCU ---- GPIOA_MODER->mode9  10
	PA10 - RX MCU------GPIOx_MODER->mode10			10
	USART1 1 APB2 - RCC_APB2ENR - USART1 EN
	USART_CR1 -> UE & TE
	*/
	
	UART1();
	delayMS(500);
	
	printf("Hello from the pther side\r\n");
	fprintf(stdout,"test for stdout\r\n");
	fprintf(stderr,"test for stderr\r\n");
	while(1)
	{
		printf("How old are you ?");
		scanf("%d",&n);
		printf("Your age os : %d\r\n",n);
		printf("Enter your first name:");
		gets(str);
		printf("I like your style:");
		puts(str);
		printf("\r\n");
		
	}
}

void UART1(void)
{
	RCC->APB2ENR |=RCC_APB2ENR_USART1EN; 
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN; 
	
	//config MCU TX & RX
	GPIOA->MODER |= GPIO_MODER_MODE9_1 | GPIO_MODER_MODE10_1;
	GPIOA->AFR[1] |=GPIO_AFRH_AFRH1_0|GPIO_AFRH_AFRH1_1|GPIO_AFRH_AFRH1_2;
	GPIOA->AFR[1] |=GPIO_AFRH_AFRH2_0|GPIO_AFRH_AFRH2_1|GPIO_AFRH_AFRH2_2;

	
	/*HSI 16MHZ oscillator baud rate 9600*/
	USART1->BRR =0x0683;//(USART_BRR_DIV_Mantissa|0x68)|(USART_BRR_DIV_Fraction|0x03);//
	USART1->CR1 |=USART_CR1_TE | USART_CR1_RE;
	USART1->CR1 |=USART_CR1_UE;
}

int UART1_write(int ch)
{

	while(!(USART1->SR & USART_SR_TXE)){}
		USART1->DR = (ch & 0xFF);
} 


int UART1_read(void)
{
	while(!(USART1->SR & USART_SR_RXNE)){}
		return USART1->DR;
} 


void delayMS(int delay)
{
	int i,j;
	for(i=0;delay>i;delay--)
	{
		for(j=0;j<3195;j++);
	}
}


//struct __FILE{int handle;};

FILE __stdin = {0};
FILE __stdout = {1};
FILE __stderr = {2};

int fgetc(FILE *f)
{
	int c;
	c = UART1_read();
	if(c == '\r')
	{
		UART1_write(c);
		c = '\n';
	}
	UART1_write(c);
	return c;
}

int fputc(int c,FILE *f)
{
	return UART1_write(c);
}

