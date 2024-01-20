#pragma once

#include <Arduino.h>
#include <Bluepad32.h>

#include "led_logic.h"

// Union that keeps the gamepad data in format ready to be sent to master.
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

#define GAMEPAD_CONNECTED    0x10  // Byte which signals that gamepad has connected to the bluetooth host
#define GAMEPAD_DISCONNECTED 0x11  // Byte which signals that gamepad has disconnected from the bluetooth host
#define GAMEPAD_DATA         0x12  // Byte which signals that gamepad data will be sent
#define GAMEPAD_END_DATA     0x17  // Byte which signals that gamepad sent all the wanted data 

/*
Funtion that attaches the bluetooth host to the gamepad events. 
*/
void gamepadHostSetup();

/*
Function called in the loop for getting gamepad data parsed 
*/
void gamepadLoop();

/*
Callback that gets called any time a new gamepad is connected.
*/
void onConnectedController(ControllerPtr ctl);

/*
Callback that gets called any time a new gamepad gets disconnected.
*/
void onDisconnectedController(ControllerPtr ctl);

/*
Funtion that takes the gamepads' descriptor and parses it.
*/
void processGamepad(ControllerPtr ctl);
