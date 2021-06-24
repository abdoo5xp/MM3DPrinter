
#include <stdint.h>
#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "GPIO.h"
#include "Rcc.h"
#include "NVIC.h"
#include "EXTI.h"


void test(void)
{
	trace_printf("Allah <3 ");
}

int main()
{
  // At this stage the system clock should have already been configured
  // at high speed.
	gpio_pinConfig_t btn_config;
	btn_config.port = GPIO_PORTA;
	btn_config.mode = GPIO_MODE_INPUT;
	btn_config.pinNum = GPIO_PIN_0;
	btn_config.pupd  = GPIO_NO_PULL;

	EXTI_config_t exti_0_config;
	exti_0_config.EXTINum = 0;
	exti_0_config.EdgeDetectionType = EXTI_EDGE_RISING;
	exti_0_config.maskType = EXTI_MASKTYPE_INTERRUPT;
	exti_0_config.pinNum = 0;
	exti_0_config.port  = EXTI_PORTA;

	EXTI_vidInit();
	RCC_ControlAHB1PeriClk(RCC_AHB1_PREPH_GPIOA, RCC_PREPH_ENABLE);

	GPIO_InitPin(&btn_config);
	NVIC_EnableIntr(_EXTI0_IRQn);
	EXTI_enuSetCbf(test, 0);
	EXTI_enuEnableINT(&exti_0_config);

  // Infinite loop
  while (1)
    {
       // Add your code here.
    }
}
