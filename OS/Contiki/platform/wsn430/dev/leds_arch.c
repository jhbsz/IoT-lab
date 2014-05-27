#include "contiki.h"
#include "dev/leds.h"

#define LED_OUT   P1OUT
#define LED_DIR	  P1DIR
#define LED_SEL	  P1SEL

//#define BIT_BLUE     (1 << 6)
//#define BIT_GREEN    (1 << 5)
//#define BIT_RED      (1 << 4)

#define BIT_YELLOW 0x01

void leds_arch_init(void) {
	LED_OUT &= ~(BIT_YELLOW);
	LED_DIR |= (BIT_YELLOW);
	LED_SEL &= ~(BIT_YELLOW);
//	LED_OUT |= (BIT_BLUE | BIT_GREEN | BIT_RED);
}

uint8_t leds_arch_get(void) {
	return (~(LED_OUT)) & 0x07;
}

void leds_arch_set(uint8_t leds) {
	if(leds & BIT_YELLOW)
		LED_OUT |= BIT_YELLOW;
	else
		LED_OUT &= (~BIT_YELLOW);

//	uint8_t leds_corrected = 0;
//	leds_corrected |= (leds & LEDS_BLUE) ? BIT_BLUE : 0;
//	leds_corrected |= (leds & LEDS_GREEN) ? BIT_GREEN : 0;
//	leds_corrected |= (leds & LEDS_RED) ? BIT_RED : 0;
//
//	LED_OUT |= (BIT_BLUE | BIT_GREEN | BIT_RED);
//	LED_OUT &= ((~leds_corrected) & 0x70);
}
