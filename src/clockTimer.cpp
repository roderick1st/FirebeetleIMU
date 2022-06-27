#include "clockTimer.h"


void tick(){

    unsigned long nowTime = millis();
    
    globVariables.currentTime = globVariables.currentTime + (nowTime - globVariables.lastMillis);
    globVariables.lastMillis = nowTime;

    if((globVariables.currentTime - globVariables.lastTime) >= 10){             //1/100th of a second passed

        globVariables.lastTime = globVariables.currentTime;                     //reset timer

        Hundred_HZ();
    } 

}

void Hundred_HZ(){

    globVariables.HundredHZ++;
    if(globVariables.HundredHZ >= 10){
        globVariables.HundredHZ = 0;
        Ten_HZ();
    }

    Get_IMU_Reading();
    BroadCastNOW();
    
}

void Ten_HZ(){
    globVariables.TenHZ++;
    if(globVariables.TenHZ >= 10){
        globVariables.TenHZ = 0;
        One_HZ();
    }
    
    BroadCastSerial();

}

void One_HZ(){
    //Serial.println(globVariables.currentTime);
    CheckTimeUpdate();
    CheckErrors();
    CheckForSerial();
}