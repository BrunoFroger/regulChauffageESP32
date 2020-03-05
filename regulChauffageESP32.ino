//
//  module de test de la feather ESP32
// (c) B. Froger 2020


#include <arduino.h>
#include <WiFi.h>
#include "wifiTools.hpp"
#include "variables.hpp"
#include "capteurs.hpp"
#include "regulation.hpp"
#include "saveToFlash.hpp"
#include "afficheur.hpp"
#include "clavier.hpp"
#include "boutton.hpp"

int loopDelay = 1000;
int cpt=0;


//=========================================
//
//          setup
//
//=========================================
void setup() {
    delay(2000);
    // initialize serial communication
    Serial.begin(115200);
    int timeoutInitSerial = 100;
    while (timeoutInitSerial-- > 0)
    {
        if (Serial)
        break;
        delay(10);
    }
    delay(4000);
    if (timeoutInitSerial != 0)
    {
        Serial.println("Serial initialized");
    } else
    {
        Serial.println("Serial not initialized");
        exit(0);
    }

    Serial.println("debut de setup");
    initWifi();
    Serial.println("Init Wifi OK");

    initVariables();
    Serial.println("Init variables OK");
    regulationInit();
    Serial.println("Init regulation OK");
    initSaveToFlash();
    Serial.println("Init eeprom OK");
    initAfficheur();
    afficheTexte(lcd0,0,0,"Bienvenue");
    Serial.println("Init afficheur OK");
    delay(1000);

    Serial.println("Fin de setup");
}

//=========================================
//
//          loop
//
//=========================================
void loop() {
    mesureCapteurs();
    regulationLoop();
    ecranLoop();
    readBouton();

    if (Serial.available() > 0) {
        lireClavier();
    }

    // Check if a client has connected
    wifiClient = wifiServer.available();
    if (wifiClient) {
        // a client is connected
        //check if the client sends some data
        delay(50); // wait a lot of time to receive datas
        if (wifiClient.available()) {
            // a request is available treat int
            // Read the first line of the request
            String request = wifiClient.readStringUntil('\r');
            Serial.print( "String recue du Client:   "); 
            Serial.println(request);
            analyseRequest(request);
            if (savetoFlashNeeded){
                saveDatasToFlash();
            }
        }
    }
    delay (1);
}



