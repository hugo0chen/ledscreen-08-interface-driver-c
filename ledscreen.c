#include <string.h>
#include "ledscreen.h"

#define LEDSCREEN_INTERFACE_COUNT 11

struct LEDScreenPinDefine ledscreen_confs[MAX_LED_NUMBER][LEDSCREEN_INTERFACE_COUNT];

static void DataOut( enum LEDSCREEN_NO ledscreen_no, int value );

uint8_t LEDSCREEN_Configuration( enum LEDSCREEN_NO ledscreen_no, const struct LEDScreenPinDefine* ledscreen_pins, uint8_t len)
{
    uint8_t l;
    GPIO_InitTypeDef	GPIO_InitStructure;

		memcpy( (void*)&ledscreen_confs[(uint8_t)ledscreen_no - 1], (void*)ledscreen_pins, sizeof(struct LEDScreenPinDefine) * LEDSCREEN_INTERFACE_COUNT );
    for (l=0;l<len;++l)
    {
        const struct LEDScreenPinDefine def = ledscreen_pins[l];

        GPIO_InitStructure.GPIO_Pin = def.pin;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(def.pin_group, &GPIO_InitStructure);
    }
    return 0;
}

void enableLEDScreen(enum LEDSCREEN_NO ledscreen_no) {
		struct LEDScreenPinDefine* config = ledscreen_confs[(uint8_t)ledscreen_no - 1];
		GPIO_ResetBits( config[OE].pin_group, config[OE].pin );    
}

void disableLEDScreen(enum LEDSCREEN_NO ledscreen_no) {
		struct LEDScreenPinDefine* config = ledscreen_confs[(uint8_t)ledscreen_no - 1];
		GPIO_SetBits( config[OE].pin_group, config[OE].pin );    
}

void loadWordIntoBuffer( uint8_t (*displayBuffer)[10], uint8_t ledCnt, const uint8_t *p )
{
		uint8_t cnt;
    
    for( cnt = 0; cnt < 16; cnt++ )
    {
        displayBuffer[cnt][ledCnt] = *(p++);
        displayBuffer[cnt][ledCnt+1] = *(p++);
    }
}

void selectScreenRow( enum LEDSCREEN_NO ledscreen_no, int row ) {
		struct LEDScreenPinDefine* config = ledscreen_confs[(uint8_t)ledscreen_no - 1];
	
    int selectledRow = ( row & 0x0000000F );        
    int ldValue = ( ( selectledRow & 0x00000008 )>> 3 );
    int lcValue = ( ( selectledRow & 0x00000004 )>> 2 );
    int lbValue = ( ( selectledRow & 0x00000002 )>> 1 );
    int laValue = ( selectledRow & 0x00000001 );
    
    if( laValue ) {
        GPIO_SetBits( config[LA].pin_group, config[LA].pin );
    } else {
        GPIO_ResetBits( config[LA].pin_group, config[LA].pin );
    }
    if( lbValue ) {
        GPIO_SetBits( config[LB].pin_group, config[LB].pin );
    } else {
        GPIO_ResetBits( config[LB].pin_group, config[LB].pin );
    }
    if( lcValue ) {
        GPIO_SetBits( config[LC].pin_group, config[LC].pin );
    } else {
        GPIO_ResetBits( config[LC].pin_group, config[LC].pin );
    }
    if( ldValue ) {
        GPIO_SetBits( config[LD].pin_group, config[LD].pin );
    } else {
        GPIO_ResetBits( config[LD].pin_group, config[LD].pin );
    }
}

static void DataOut( enum LEDSCREEN_NO ledscreen_no, int value ) {
		struct LEDScreenPinDefine* config = ledscreen_confs[(uint8_t)ledscreen_no - 1];

    if( value == 0 ) {
				GPIO_SetBits( config[R1].pin_group, config[R1].pin );
        GPIO_SetBits( config[G1].pin_group, config[G1].pin );			
        GPIO_SetBits( config[R2].pin_group, config[R2].pin );
        GPIO_SetBits( config[G2].pin_group, config[G2].pin );      
    } else {
				GPIO_ResetBits( config[R1].pin_group, config[R1].pin );
				GPIO_ResetBits( config[G1].pin_group, config[G1].pin );
				GPIO_ResetBits( config[R2].pin_group, config[R2].pin );
				GPIO_ResetBits( config[G2].pin_group, config[G2].pin );
    }
}

void LedScreenDisplayBuffer( enum LEDSCREEN_NO ledscreen_no, uint8_t displayBuffer[16][10] )
{
	uint8_t  row;
	uint8_t  column;
	uint16_t cnt;	
  int i;
  uint8_t  data;
	struct LEDScreenPinDefine* config = ledscreen_confs[(uint8_t)ledscreen_no - 1];
	
	for( row = 0; row < 16; row++ ) {
		selectScreenRow( ledscreen_no, row );
		for( column = 0; column < 10; column++ ) {
            data = displayBuffer[row][column];
            for( i = 0; i < 8; i++ ){
                DataOut( ledscreen_no, data >> 7 );        
                GPIO_SetBits( config[CLK].pin_group, config[CLK].pin );
                data <<= 1;
                GPIO_ResetBits( config[CLK].pin_group, config[CLK].pin );
            }     
    }
		for(cnt=4000;cnt!=0;cnt--);
		disableLEDScreen(ledscreen_no);
		GPIO_SetBits( config[LAT].pin_group, config[LAT].pin );
		GPIO_ResetBits( config[LAT].pin_group, config[LAT].pin );
		enableLEDScreen(ledscreen_no);
	}
	for(cnt=1300;cnt!=0;cnt--);
	disableLEDScreen(ledscreen_no);
}








