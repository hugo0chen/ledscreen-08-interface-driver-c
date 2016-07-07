#ifndef __DRIVERS_INIT_H
#define __DRIVERS_INIT_H

#ifdef __cplusplus
 extern "C" {
#endif 

void RCC_Configuration(void);
void init_led(void);
void init_relay(void);
void init_di(void);
void init_usart(void);
void init_ledscreen(void);
void init_tts(void);

#endif 
