#include "gamepad_logic.h"

ControllerPtr myController = nullptr;

void gamepadHostSetup(){
    // Setup the Bluepad32 callbacks
    BP32.setup(&onConnectedController, &onDisconnectedController);

    // "forgetBluetoothKeys()" should be called when the user performs
    // a "device factory reset", or similar.
    BP32.forgetBluetoothKeys();
}

void gamepadLoop(){
    BP32.update();
    
    if (myController && myController->isConnected()) {
        if (myController->isGamepad()) {
            processGamepad(myController);
        }
    }

    delay(20);
}

void onConnectedController(ControllerPtr ctl) {
    if (myController == nullptr) {
        ledSetMode(GAMEPAD_CONNECTED);

        Serial.write(GAMEPAD_CONNECTED);
        myController = ctl;
    }
}

void onDisconnectedController(ControllerPtr ctl) {
    if (myController == ctl) { 
        ledSetMode(GAMEPAD_DISCONNECTED);

        Serial.write(GAMEPAD_DISCONNECTED);
        myController = nullptr;
    }
}

void processGamepad(ControllerPtr ctl) {
    Serial.write(GAMEPAD_DATA);
    
    gamepadData data;
    
    data.gamepadInfo.dpad = ctl->dpad();
    data.gamepadInfo.buttons = (uint8_t) ctl->buttons();
    
    data.gamepadInfo.axisLX = ctl->axisX();
    data.gamepadInfo.axisLY = ctl->axisY();
    
    data.gamepadInfo.axisRX = ctl->axisRX();
    data.gamepadInfo.axisRY = ctl->axisRY();
    
    data.gamepadInfo.throttleL = ctl->brake();
    data.gamepadInfo.throttleR = ctl->throttle();

    Serial.write(data.byteArray, 28);

    Serial.write(GAMEPAD_END_DATA);
}