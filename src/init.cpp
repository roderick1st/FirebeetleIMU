#include "init.h"

void init_Serial(){

    globVariables.useSerial = false;            //initilised the global variable

    pinMode(def_Enable_Serial_Pin, INPUT);      //look at the pin we want to use to trigger serial output

    if(digitalRead(def_Enable_Serial_Pin) == 1){// we want to use serial output
        //Serial.begin(115200);
        Serial.begin(38400);
        Serial.println("AOG-IMU"); //Tell the serial terminial we are up
        globVariables.useSerial = true;

        globVariables.data[0] = 0x80;
        globVariables.data[1] = 0x81;
        globVariables.data[2] = 0x7D;
        globVariables.data[3] = 0xD3;
        globVariables.data[4] = 8;
        globVariables.data[5] = 0;
        globVariables.data[6] = 0;
        globVariables.data[7] = 0;
        globVariables.data[8] = 0;
        globVariables.data[9] = 0;
        globVariables.data[10] = 0;
        globVariables.data[11] = 0;
        globVariables.data[12] = 0; 
        globVariables.data[13] = 15;
    }
}


void  init_LED(){
    FastLED.addLeds<NEOPIXEL, RGB_PIN>(leds, NUM_LEDS);

    FastLED.clear(true);                                    //turn off LED 

    Serial.println("Initilised RGB-LED");
    Set_RGB(1);
    
}


void init_ESPNOW(){

    WiFi.mode(WIFI_STA);
    
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        Set_RGB(1);
        delay(1000);
        Set_RGB(0);
        ESP.restart();
    } else {
        Serial.println("Initilised ESP-NOW");
        Set_RGB(2);
        //esp_now_register_send_cb(OnDataSent);
        esp_now_register_recv_cb(OnDataRecv);
    }
}

void init_CMPS14(){

    pinMode(def_CMPS_Power_Pin, OUTPUT);
    digitalWrite(def_CMPS_Power_Pin, HIGH);
    delay(200);

    Wire.begin();

    Check_IMU(); //esp will reboot if we dont get IMU
    
    Serial.println("CMPS14 Connected");
    
    Set_RGB(3);
    
}