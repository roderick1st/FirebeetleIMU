#ifndef GLOBALS_H
#define GLOBALS_H

#include "Definitions.h"

struct GlobVariables{
    unsigned long lastCorrectionTime;
    unsigned long currentTime;
    unsigned long lastTime;
    unsigned long lastMillis;
    bool useSerial;
    int readIMUErrorCount;
    int sendNOWErrorCount;
    //bool RGBChange;
    //int RGBLevel;
    //int RGBFlashLevel;
    unsigned long HundredHZ;
    unsigned long TenHZ;
    unsigned long OneHZ;

    uint8_t data[def_Data_Size];

};
extern GlobVariables globVariables;

struct ESPNOWData{

    int messageID;
    unsigned long messageTimeStamp;

    char IMU_Roll[6];
    char IMU_Pitch[6];
    char IMU_Heading[6];
    char IMU_Yaw[6];

    char Panda[def_LengthOfPandaString];

    int ntripLen;

};

extern ESPNOWData MyEspNowData;

#endif