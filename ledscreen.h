#ifndef __LEDSCREEN_H__
#define __LEDSCREEN_H__

#include <stdio.h>
#include <stm32f10x.h>

#define MAX_LED_NUMBER 2
#define LEDPIN_MAX_SIZE 11
#define SCREEN_MAX_SIZE 8

enum LEDSCREEN_NO {
	LEDSCREEN_NO_1=1,
	LEDSCREEN_NO_2
};
    
enum LEDSCREEN_colour{
	red    = 0,
	green  = 1,
	yellow = 2
};

enum LEDSCREEN_PIN_NO {
	OE = 0,
	R1 = 1,
	G1 = 2,
	R2 = 3,
	G2 = 4,
	LA = 5,
	LB = 6,
	LC = 7,
	LD = 8,
	LAT = 9,
	CLK = 10,
};

struct LEDScreenPinDefine {
	enum LEDSCREEN_PIN_NO interface_no;
	GPIO_TypeDef* pin_group;
	uint16_t pin;
};

void enableLEDScreen(enum LEDSCREEN_NO ledscreen_no);
void disableLEDScreen(enum LEDSCREEN_NO ledscreen_no);
void LedScreenDisplayBuffer( enum LEDSCREEN_NO ledscreen_no, uint8_t displayBuffer[16][10] );
void loadWordIntoBuffer( uint8_t (*displayBuffer)[10], uint8_t ledCnt, const uint8_t *p );

uint8_t LEDSCREEN_Configuration( enum LEDSCREEN_NO ledscreen_no, const struct LEDScreenPinDefine* ledscreen_pins, uint8_t len);
#endif

