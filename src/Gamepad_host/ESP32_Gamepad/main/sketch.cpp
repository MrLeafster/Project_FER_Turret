#include "sdkconfig.h"

#include "gamepad_logic.h"
#include "led_logic.h"

void setup() {
    // Setup Bluetooth host
    gamepadHostSetup();

    // Setup LED strip
    ledSetup();
    xTaskCreatePinnedToCore(ledTask,
                          "LED strip handler",
                          1024,
                          NULL,
                          1,
                          NULL,
                          1);

    // Setup UART
    Serial.begin(9600);
}

void loop() {
    gamepadLoop();
}
