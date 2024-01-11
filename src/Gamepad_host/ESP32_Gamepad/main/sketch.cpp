#include "sdkconfig.h"

#include "gamepad_logic.h"

void setup() {
    // Setup Bluetooth host
    gamepadHostSetup();

    // Setup UART
    Serial.begin(9600);
}

void loop() {
    gamepadLoop();
}
