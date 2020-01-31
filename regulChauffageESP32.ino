//
//  module de test de la feather ESP32
// (c) B. Froger 2020


#include <arduino.h>
#include <WiFi.h>
#include "wifiTools.hpp"
#include "variables.hpp"
#include "capteurs.hpp"
#include "regulation.hpp"

int loopDelay = 1000;
int cpt=0;


//=========================================
//
//          setup
//
//=========================================
void setup() {
    // initialize serial communication
    Serial.begin(115200);
    int timeoutInitSerial = 100;
    while (timeoutInitSerial-- > 0)
    {
        if (Serial)
        break;
        delay(10);
    }
    if (timeoutInitSerial != 0)
    {
        Serial.println("Serial initialized");
    } else
    {
        Serial.println("Serial not initialized");
        exit(0);
    }

    initWifi();

    initVariables();
    regulationInit();
}

//=========================================
//
//          loop
//
//=========================================
void loop() {
    mesureCapteurs();
    regulationLoop();

    // Check if a client has connected
    wifiClient = wifiServer.available();
    if (wifiClient) {
        Serial.println("a client is connected");
        delay(10);
        // a client is connected
        //check if the client sends some data
        if (wifiClient.available()) {
            // a request is available treat int
            //   Read the first line of the request
            String request = wifiClient.readStringUntil('\r');
            Serial.print( "String recue du Client:   "); 
            Serial.println(request);
            analyseRequest(request);
        }
    }
    delay (1);
}



