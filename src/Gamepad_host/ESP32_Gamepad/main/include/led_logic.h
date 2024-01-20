#pragma once

#include "Arduino.h"
#include "FastLED.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "gamepad_logic.h"

#define NUM_LEDS 20
#define LED_PIN  16

#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

// Setup LED strip
void ledSetup();

// Task that handles LED Strip events
void ledTask(void *arg);

// Set current LED strip operating mode
void ledSetMode(uint8_t modeByteSignal);