/*
 * gamepad_logic.c
 *
 *  Created on: Jan 17, 2024
 *      Author: Luka
 */

#include "gamepad_logic.h"

gamepadData gamepad_input;

static uint8_t buffer_ind = 0;
static uint8_t recieving_state = 0;
volatile uint8_t gamepad_ready = 0;

void gamepad_procesByte(uint8_t *byte){
	switch(recieving_state){
		case 0:
			if(*byte == GAMEPAD_DATA)
				recieving_state++;
			break;

		case 1:
			if(*byte == GAMEPAD_END_DATA){
				recieving_state++;
				gamepad_ready = 1;
				buffer_ind = 0;
			} else {
				gamepad_input.byteArray[buffer_ind++] = *byte;
			}
			break;

		case 2:
			if(!gamepad_ready)
				recieving_state = 0;
			break;
	}
}

void gamepad_waitForData(){
	while(!gamepad_ready);
}

void gamepad_enableNewData(){
	gamepad_ready = 0;
}
