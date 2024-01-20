#include "led_logic.h"

CRGB leds[NUM_LEDS];

uint8_t leds_state;
xSemaphoreHandle leds_state_mutex;

void ledSetup(){
    leds_state_mutex = xSemaphoreCreateMutex();
    leds_state = GAMEPAD_DISCONNECTED;

    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    delay(1000); // power-up safety delay

    for(int i = 0; i != 256; i += 1){
        FastLED.delay(5);
        fill_solid(leds, NUM_LEDS, CHSV(160, 204, i));
        FastLED.show();
    }

    xSemaphoreGive(leds_state_mutex);
}

void ledSetMode(uint8_t modeByteSignal){
    xSemaphoreTake(leds_state_mutex, portMAX_DELAY);
    leds_state = modeByteSignal;
    xSemaphoreGive(leds_state_mutex);
}

void ledTask(void *arg){
    xSemaphoreTake(leds_state_mutex, portMAX_DELAY);
    uint8_t current_state = leds_state;
    xSemaphoreGive(leds_state_mutex);

    while(true) {
        switch (current_state)
        {
        case GAMEPAD_DISCONNECTED:
            fill_solid(leds, NUM_LEDS, CRGB(0,255,0));
            FastLED.show();
            break;
        
        case GAMEPAD_CONNECTED:
            fill_solid(leds, NUM_LEDS, CRGB(255,0,0));
            FastLED.show();
            FastLED.delay(250);
            
            FastLED.clear(true);
            FastLED.delay(250);

            break;
        
        default:
            break;
        }
    }
}