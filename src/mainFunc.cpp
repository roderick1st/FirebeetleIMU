#include "mainFunc.h"

void Set_RGB(int level){

    switch(level){
        case 0:
            FastLED.clear(true);                    //trun off LED        
        break;

        case 1:                                     //RGB LED initilised
            //LED light up in red 
            leds[0] = CRGB::Red;
            FastLED.setBrightness(255);
        break;

        case 2:                                     //ESP-NOW initilised
            //LED light up in red 
            leds[0] = CRGB::Purple;
            FastLED.setBrightness(100);
        break;

        case 3:
            leds[0] = CRGB::Blue;
            FastLED.setBrightness(100);
        break;

        case 4:
            leds[0] = CRGB::Green;
            FastLED.setBrightness(255);
        break;

        case 5:
            leds[0] = CRGB::Green;
            FastLED.setBrightness(150);
        break;

        case 6:
            leds[0] = CRGB::Green;
            FastLED.setBrightness(80);
        break;

        case 102:                                     //ESP-NOW initilised
            //LED light up in red 
            leds[0] = CRGB::Blue;
            FastLED.setBrightness(255);
        break;
    }

    FastLED.show();


}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    
    memcpy(&MyEspNowData, incomingData, sizeof(MyEspNowData));

    //Serial.print("Message recieved: "); Serial.println(MyEspNowData.messageID);

    switch(MyEspNowData.messageID){
        case 0:
            //force reboot
            ESP.restart();
        break;

        case 1:

            //Adjust system clock
            globVariables.currentTime = MyEspNowData.messageTimeStamp;

            //RGB to green
            Set_RGB(4);
            globVariables.lastCorrectionTime = globVariables.currentTime; //set the last time update recieved to now

        break;
    }
}

void CheckTimeUpdate(){
    unsigned long lastTimeUpdate = 0;

    lastTimeUpdate = globVariables.currentTime - globVariables.lastCorrectionTime;

    if((lastTimeUpdate >= 1000) && (lastTimeUpdate <= 1999)){
        Set_RGB(5);
        return;
    }
    if((lastTimeUpdate >= 2000) && (lastTimeUpdate <= 2999)){
        Set_RGB(6);
        return;
    }
    if(lastTimeUpdate >= 3000){
        Set_RGB(0);
        ESP.restart();
        return;
    }
}

void CheckErrors(){

    if(globVariables.readIMUErrorCount = 0){
        Set_RGB(4);
    }else if((globVariables.readIMUErrorCount > 0) && (globVariables.readIMUErrorCount < 10)){
        Set_RGB(3);
    } else if(globVariables.readIMUErrorCount > 10){
        Set_RGB(0);
        ESP.restart();
    }
    
}

bool Check_IMU(){

    uint8_t error = -1;
    int errorCount = -1;

    while(error != 0){
    
        errorCount++;
        Wire.beginTransmission(CMPS14_ADDRESS);
        error = Wire.endTransmission();

        if(errorCount > 5){
            Set_RGB(0);
            ESP.restart();
        }
    }
    
    return true;
}

void CheckForSerial(){ //check the use serial pin against startup config. if there is a change reboot esp
    if((digitalRead(def_Enable_Serial_Pin) == 1) && (globVariables.useSerial == false)){// we want to use serial output
        Set_RGB(0);
        ESP.restart();
    }
    if((digitalRead(def_Enable_Serial_Pin) == 0) && (globVariables.useSerial == true)){
        Set_RGB(0);
        ESP.restart();
    }
}

void Get_IMU_Reading(){

    float roll = 0.0;
    int16_t heading = 0;
    unsigned long loopTime = 0;
    unsigned long startTime = millis();

    //check the cmps14 is available
    if(Check_IMU()){

        //the Roll
        //Wire.beginTransmission(CMPS14_ADDRESS);
        //Wire.write(0x1C);
        //Wire.endTransmission();

        //Wire.requestFrom(CMPS14_ADDRESS, 3);

        //while (Wire.available() < 3){
          //  loopTime = millis();
            //if(loopTime - startTime > 50){ //spending too long in this loop
              //  break;
            //}
        //}


       //roll = int16_t(Wire.read() << 8 | Wire.read());
        //itoa(roll, MyEspNowData.IMU_Roll, 10);

         //the Roll
        
    
        //the heading
        //Wire.beginTransmission(CMPS14_ADDRESS);
        //Wire.write(0x02);
        //Wire.endTransmission();

        //Wire.requestFrom(CMPS14_ADDRESS, 3);

        //startTime = millis();
        //while (Wire.available() < 3){
        //    loopTime = millis();
        //    if(loopTime - startTime > 50){ //spending too long in this loop
        //        break;
        //    }
        //}

        //heading = Wire.read() << 8 | Wire.read();
        //Serial.print("  Heading: "); Serial.println(heading);
        //itoa(heading, MyEspNowData.IMU_Heading, 10);

        Wire.beginTransmission(CMPS14_ADDRESS);
        Wire.write(0x1C);
        Wire.endTransmission();

        Wire.requestFrom(CMPS14_ADDRESS, 3);

        while (Wire.available() < 2){
            loopTime = millis();
            if(loopTime - startTime > 50){ //spending too long in this loop
                break;
            }
        }

        //get the bytes and store for serial output
        globVariables.data[8] = Wire.read();
        globVariables.data[7] = Wire.read();

        roll = int16_t((globVariables.data[8] * 256) + globVariables.data[7]);
        itoa(roll, MyEspNowData.IMU_Roll, 10);

        //////////////////////////////////////the heading
        Wire.beginTransmission(CMPS14_ADDRESS);
        Wire.write(0x02);
        Wire.endTransmission();

        Wire.requestFrom(CMPS14_ADDRESS, 3);

        startTime = millis();
        while (Wire.available() < 2){
            loopTime = millis();
            if(loopTime - startTime > 50){ //spending too long in this loop
                break;
            }
        }

        //get the bytes and store for serial output
        globVariables.data[6] = Wire.read();
        globVariables.data[5] = Wire.read();
        
        heading = (globVariables.data[6] * 256) + globVariables.data[5]; //convert to degrees reading for PANDA
        itoa(heading, MyEspNowData.IMU_Heading, 10); //convert to string
        ///////////////////////////////////////
        
        
        
        
        
        
        
        
        
        strlcpy(MyEspNowData.IMU_Pitch, "0", sizeof(MyEspNowData.IMU_Pitch));
        strlcpy(MyEspNowData.IMU_Yaw, "0", sizeof(MyEspNowData.IMU_Yaw));

        //update the time stamp for the reading
        MyEspNowData.messageTimeStamp = globVariables.currentTime;

    } else {
        globVariables.readIMUErrorCount++;
    }

}

void BroadCastSerial(){
    if(globVariables.useSerial){

        //do check sum on data
        int16_t CK_A = 0;

        for (int16_t i = 2; i < def_Data_Size - 1; i++)
        {
            CK_A = (CK_A + globVariables.data[i]);
        }
        globVariables.data[def_Data_Size - 1] = CK_A;

        Serial.write(globVariables.data, def_Data_Size);
        Serial.flush();
    }
}

void BroadCastNOW(){

    MyEspNowData.messageID = 3; //imu message being sent

    uint8_t broadcastAddress[] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x02};//GPS address

    esp_now_peer_info_t peerInfo = {};

    memcpy(&peerInfo.peer_addr, broadcastAddress, 6);
    if (!esp_now_is_peer_exist(broadcastAddress))
    {
        esp_now_add_peer(&peerInfo);
    }


    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&MyEspNowData, sizeof(MyEspNowData));

    if (result == ESP_OK) {
        globVariables.sendNOWErrorCount = 0;
        
    } else {
        Serial.println("Error sending the data");
        globVariables.sendNOWErrorCount++;
        if(globVariables.sendNOWErrorCount > 3){
            Set_RGB(0);
            ESP.restart();
        }
    }



}