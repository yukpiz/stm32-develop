/*
 * main.c
 *
 *      Author: Tomek
 */

#include <stm32l/rcc.h>
#include <stm32l/nvic.h>
#include <stm32l/gpio.h>
#include <stm32l/stm32l.h>

/* timing is not guaranteed :) */
void simple_delay(uint32_t us)
{
	/* simple delay loop */
	while (us--) {
		asm volatile ("nop");
	}
}

/* system entry point */
int main(void)
{
	/* gpio init struct */
	gpio_init_t gpio;

	/* reset rcc */
	RCC_DeInit();

	/* enable clock to GPIOA */
	RCC_AHBPeriphClockCmd(AHB_GPIOC, ENABLE);

	/* initialize gpio structure */
	GPIO_StructInit(&gpio);
	/* use pin 0 */
	gpio.pins = GPIO_P13;
	/* mode: output */
	gpio.mode = GPIO_OUTPUT;
	/* output type: push-pull */
	gpio.otype = GPIO_OT_PP;
	/* apply configuration */
	GPIO_Init(GPIOC, &gpio);

	/* main program loop */
	for (;;) {
		/* set led on */
		//GPIO_SetPins(GPIOC, GPIO_P13);
		/* delay */
		//simple_delay(10000000);
		/* clear led */
		//GPIO_ClearPins(GPIOC, GPIO_P13);
		/* delay */
		//simple_delay(10000000);
	}

	/* never reached */
	return 0;
}
