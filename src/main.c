#include "ch32v00x_rcc.h"
#include "core_riscv.h"
#include <ch32v00x.h>
#include <ch32v00x_gpio.h>
#include <core_systick.h>

void loop() {
	static int value = 0;
	value = !value;
	GPIO_WriteBit(GPIOC, GPIO_Pin_1, value);
	delay_ms(100);
}

int main() {
	NVIC_InitTypeDef nvic_init;
	GPIO_InitTypeDef gpio_init;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	initialize_systick_interrupt();

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	gpio_init.GPIO_Pin = GPIO_Pin_1;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &gpio_init);

	while (1)
		loop();

	return 0;
}
