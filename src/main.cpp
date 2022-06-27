#include <Arduino.h>
#include "Definitions.h"
#include "init.h"
#include "Globals.h"
#include "clockTimer.h"


CRGB leds[NUM_LEDS];                                          //Global array for coloured LED
ESPNOWData MyEspNowData;                                      //Global Array for ESP NOW Comms
GlobVariables globVariables;                                  //Global variables

void setup() {

  init_Serial();
  init_LED();                                                 //Initilise the coloured LED
  init_ESPNOW();                                              //Initilise the ESP_NOW
  init_CMPS14();                                               //Start the CMPS14 [init.cpp]
  
}

void loop() {

  tick();
  
}