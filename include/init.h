#ifndef INIT_H
#define INIT_H

#include <Arduino.h>
#include <FastLED.h>
#include "Definitions.h"
#include "mainFunc.h"
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>

extern CRGB leds[NUM_LEDS];

void init_Serial();
void init_LED();
void init_ESPNOW();
void init_CMPS14();

#endif