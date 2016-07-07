#include <stm32f10x.h>
#include "driversInit.h"
#include "GlobalVar.h"
#include "led.h"
#include "relay.h"
#include "di.h"
#include "usart.h"
#include "ledscreen.h"
#include "tts.h"

extern int receiveByteFromBoard_A( enum BOARD_USART_TYPE usart_no, unsigned char recv);
extern int receiveByteUsingUsart2( enum BOARD_USART_TYPE usart_no, unsigned char recv);
extern int receiveByteFromTTS ( enum BOARD_USART_TYPE usart_no, unsigned char recv);
void RCC_Configuration(void) 
{ 
	RCC_ClocksTypeDef RCC_Clocks;
    
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE );
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2 | RCC_APB1Periph_USART3,ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1,ENABLE);
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.SYSCLK_Frequency / 100);		
  NVIC_SetPriority (SysTick_IRQn, 1);	
}

void init_led(void)
{
	struct LedDefine conf[] = {
		{ LED_NO_1, GPIOB, GPIO_Pin_12, LEDOFF },
	};
	LED_Configuration( conf, ARRAY_SIZE( conf, struct LedDefine ) );
}

void init_relay(void)
{
	struct RelayDefine conf[] = {
			{ RELAY_NO_1, GPIOC, GPIO_Pin_6, RELAY_OFF },
			{ RELAY_NO_2, GPIOB, GPIO_Pin_15, RELAY_OFF },
			{ RELAY_NO_3, GPIOB, GPIO_Pin_14, RELAY_OFF }
	};
	Relay_Configuration( conf, ARRAY_SIZE( conf, struct RelayDefine ) );
}

void init_di(void)
{
	struct DiDefine conf[] = {
		DIDEF_10_15( 1, B, 13 ),
		DIDEF_10_15( 2, A, 15 ),
		DIDEF_0_4( 3, B, 3 ),
		DIDEF_0_4( 4, B, 4 )
	};
	Di_Configuration( conf, ARRAY_SIZE( conf, struct DiDefine ) );
}

void init_usart(void)
{
	struct USARTDefine conf[] = {
		{ USART1, GPIOA, GPIO_Pin_9, GPIOA, GPIO_Pin_10, 115200, receiveByteFromBoard_A },
		{ USART2, GPIOA, GPIO_Pin_2, GPIOA, GPIO_Pin_3, 115200, receiveByteUsingUsart2},
		{ USART3, GPIOB, GPIO_Pin_10, GPIOB, GPIO_Pin_11, 115200,  receiveByteFromTTS},
	};
	USART_Configuration( conf, ARRAY_SIZE( conf, struct USARTDefine ) );
}

void init_ledscreen(void)
{
	struct LEDScreenPinDefine led1_conf[] = {
		{ OE,  GPIOC,  GPIO_Pin_2  },
		{ R1,  GPIOC,  GPIO_Pin_0  },
    { G1,  GPIOC,  GPIO_Pin_13  },        
		{ R2,  GPIOB,  GPIO_Pin_9  },
    { G2,  GPIOB,  GPIO_Pin_8  },        
		{ LA,  GPIOA,  GPIO_Pin_1  },
		{ LB,  GPIOA,  GPIO_Pin_0  },
		{ LC,  GPIOC,  GPIO_Pin_3  },
		{ LD,  GPIOC,  GPIO_Pin_1  },
		{ LAT, GPIOB,  GPIO_Pin_7 },
    { CLK, GPIOB,  GPIO_Pin_6 }
	};
	
	struct LEDScreenPinDefine led2_conf[] = {
		{ OE,  GPIOC,  GPIO_Pin_10  },
		{ R1,  GPIOA,  GPIO_Pin_11  },
    { G1,  GPIOA,  GPIO_Pin_12  },        
		{ R2,  GPIOC,  GPIO_Pin_9  },
    { G2,  GPIOA,  GPIO_Pin_8  },        
		{ LA,  GPIOB,  GPIO_Pin_5  },
		{ LB,  GPIOD,  GPIO_Pin_2  },
		{ LC,  GPIOC,  GPIO_Pin_12  },
		{ LD,  GPIOC,  GPIO_Pin_11 },
		{ LAT, GPIOC,  GPIO_Pin_8 },
    { CLK, GPIOC,  GPIO_Pin_7 }
	};
	LEDSCREEN_Configuration( LEDSCREEN_NO_1, led1_conf, ARRAY_SIZE( led1_conf, struct LEDScreenPinDefine ) );  
	LEDSCREEN_Configuration( LEDSCREEN_NO_2, led2_conf, ARRAY_SIZE( led2_conf, struct LEDScreenPinDefine ) );      
}

void init_tts(void)
{	
		struct TTSDefine tts_define = {GPIOB,GPIO_Pin_2,GPIOB,GPIO_Pin_1,GPIOB,GPIO_Pin_0};
		TTS_Configuration(&tts_define);
}
