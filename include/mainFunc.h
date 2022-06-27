#ifndef MAINFUNC_H
#define MAINFUNC_H

#include <Arduino.h>
#include <FastLED.h>
#include "Definitions.h"
#include "Globals.h"
#include <Wire.h>
#include <esp_now.h>

extern CRGB leds[NUM_LEDS];

void Set_RGB(int level);
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);
void Get_IMU_Reading();
void BroadCastNOW();
void CheckTimeUpdate();
void CheckErrors();
bool Check_IMU();
void CheckForSerial();
void BroadCastSerial();

#endif