/**
  ******************************************************************************
  * @file       �� main.c
  * @author     :  FCZ
  * @version    �� V1.1.6
  * @date       �� 2022��03��28��
  * @brief      �� ������ - LCM�ƿ�
  * @mcu        :  HK32F030MF4P6
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2022-03-28 V1.0.0:��ʼ�汾
  2022-05-16 ���ӿ�����ʾ�������ͳ����ʾ��ѹ
  2022-05-17 ���ĳ����ʾΪ������Ч��
  2022-06-09 �ػ�ʱ����5���Ӹ�Ϊ15���� 
             ռ�ձ��ɳ���70%��Ϊ����80%���������١����١�����
			 �Զ��ػ�������ԭ���Ĳ��Ƚ�̤������һ����ת�ٵ���1000�ſ�ʼ��ʱ�ػ�
  2022-07-19 �����12����Ϊ20��
             �ػ�ʱ���Ϊ30����
			 �������ѹ����ƽ��ֵ�˲�����ѹ�жϼӻ�ִ��ѹ��Χ
  2023-01-16 WS2812������Ӳ��SPIģ���ΪIO�ڼ���ʱģ��
  ----------------------------------------------------------------------------*/
#include "datatypes.h"
#include "hk32f030m.h"
#include "led.h"
#include "time.h"
#include "spi.h"
#include "ws2812.h"
#include "power.h"
#include "key.h"
#include "usart.h"
#include "adc.h"
#include "buzzer.h"
#include "led_pwm.h"
#include "test.h"
#include "task.h"
#include "io_ws2812.h"

//RCC_ClocksTypeDef RCC_Clock;

/*
										
*/

/**************************************************
 * @brie   :main()
 * @note   :������
 * @param  :��
 * @retval :��
 **************************************************/
int main(void)
{	
	//RCC_GetClocksFreq(&RCC_Clock);
	LED_Init();
#ifdef USE_BUZZER		
	Buzzer_Init();
#endif
	ADC1_Init();
	WS2812_Init();
	Power_Init();
	KEY_Init();
	USART1_Init(115200);
	LED_PWM_Init();
	Time6_Init();
	if(KEY1 ==  0)
	{
		KEY1_State = 1;
	}
	while(1)
	{
		KEY1_Task();
		
		if(WS2812_Counter >= 40) // 25Hz refresh rate
		{
			WS2812_Task();
			WS2812_Counter = 0;
		}

		Power_Task();

#ifdef ADV
		Charge_Task();
#endif
		Headlights_Task();
#ifdef USE_BUZZER		
		Buzzer_Task();
#endif
		Usart_Task();
		ADC_Task();
		VESC_State_Task();
	}
	return 0;
}
