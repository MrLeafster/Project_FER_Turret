/*
 * gaempad_logic.h
 *
 *  Created on: Jan 17, 2024
 *      Author: Luka
 */

#ifndef INC_GAMEPAD_LOGIC_H_
#define INC_GAMEPAD_LOGIC_H_

#include "stm32f4xx_hal.h"

#define GAMEPAD_BUFFER_SIZE 28

#define GAMEPAD_CONNECTED    0x10  // Byte which signals that gamepad has connected to the bluetooth host
#define GAMEPAD_DISCONNECTED 0x11  // Byte which signals that gamepad has disconnected from the bluetooth host
#define GAMEPAD_DATA         0x12  // Byte which signals that gamepad data will be sent
#define GAMEPAD_END_DATA     0x17  // Byte which signals that gamepad sent all the wanted data

typedef union {
    struct {
        uint8_t dpad;

        uint8_t buttons;

        int32_t axisLX;
        int32_t axisLY;

        int32_t axisRX;
        int32_t axisRY;

        int32_t throttleL;
        int32_t throttleR;

    } gamepadInfo;

    uint8_t byteArray[28];

} gamepadData;

extern gamepadData gamepad_input;

// Process next byte that has been received by gamepad controller
void gamepad_procesByte(uint8_t *byte);

// Wait for gamepad to send new data
void gamepad_waitForData();

// Enable host to recieve new gamepad data
void gamepad_enableNewData();

#endif /* INC_GAMEPAD_LOGIC_H_ */
