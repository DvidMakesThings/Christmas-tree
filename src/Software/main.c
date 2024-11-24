/*
 * Christmas_Tree_2.1.c
 *
 * Created: 22/11/2020 13:23:37
 * Author : sdvid
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/delay.h>

#define LEDGROUP1			PORTC
#define GROUP1_PATTERN		0b00111111
#define LEDGROUP2			PORTD
#define GROUP2_PATTERN		0b01111111
#define TAP_PIN				PINB
#define TAP_BIT				(1<<0)			
#define RANDOM_MAX			8

uint8_t pattern = 0;
uint8_t deviceOn = 0;
uint8_t oldState = 0;
uint8_t cnt = 1;

int main(void){
    DDRC = GROUP1_PATTERN;
	DDRD = GROUP2_PATTERN;
	DDRB = 0x00;
	PORTB = 0x00;
	
    while (1){
		
		checkState();
		
		while (cnt == 2){
			pattern = random();
			LEDGROUP1 = GROUP1_PATTERN & pattern;
			pattern = random();
			LEDGROUP2 = GROUP2_PATTERN & pattern;
			checkState();
			_delay_ms(1000);
		}
    }
}

void checkState (){
	if ((TAP_PIN & TAP_BIT == 1) && (cnt == 1)){
		startPattern();
		cnt = 2;
	}
	else if ((TAP_PIN & TAP_BIT == 1) && (cnt == 2)){
		_delay_ms(1000);
		if ((TAP_PIN & TAP_BIT == 1) && (cnt == 2)){
			exitPattern();
			cnt = 1;
		}
	}
}



void clearAll (){
	LEDGROUP1 = 0x00;
	LEDGROUP2 = 0x00;
	return 0;
}

void exitPattern (){
	clearAll();
	for (uint8_t i = 0; i < 6; i++){
		LEDGROUP1 = 0b00001000;
		_delay_ms(200);
		LEDGROUP1 = 0b00000000;
		_delay_ms(200);
	}
	clearAll();
}

void startPattern (){
	uint8_t delayTime = 100;
	LEDGROUP1 = 0b00000001;
	_delay_ms(delayTime);
	LEDGROUP1 = 0b00000011;
	_delay_ms(delayTime);
	LEDGROUP1 = 0b00000111;
	_delay_ms(delayTime);
	LEDGROUP1 = 0b00001111;
	_delay_ms(delayTime);
	LEDGROUP1 = 0b00011111;
	_delay_ms(delayTime);
	LEDGROUP1 = 0b00111111;
	_delay_ms(delayTime);
	LEDGROUP2 = 0b00000001;
	_delay_ms(delayTime);
	LEDGROUP2 = 0b00000011;
	_delay_ms(delayTime);
	LEDGROUP2 = 0b00000111;
	_delay_ms(delayTime);
	LEDGROUP2 = 0b00001111;
	_delay_ms(delayTime);
	LEDGROUP2 = 0b00011111;
	_delay_ms(delayTime);
	LEDGROUP2 = 0b00111111;
	_delay_ms(delayTime);
	LEDGROUP2 = 0b01111111;
	_delay_ms(delayTime);
	clearAll();
}
