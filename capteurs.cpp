



#include <Arduino.h>
#include <Wifi.h>

#include "variables.hpp"
#include "simulation.hpp"

#define PIN_TEMP_EXT        36  // A4
#define PIN_TEMP_INT        39  // A5
#define PIN_TEMP_OUT_CHAUD  A0
#define PIN_TEMP_BACK_CHAUD A1

long temperatureMesuree;
long temperatureExterieure;
long tempSortieChaudiere=0L;
long tempRetourChaudiere=0L;


unsigned long previousMillisCapteurs=0 ;
long intervalMesure = 1000L;

//=========================================
//
//          initCapteurs
//
//=========================================
void initCapteurs(void){
    
}

//=========================================
//
//          mesureCapteurs
//
//=========================================
void mesureCapteurs(void){
    if( millis() - previousMillisCapteurs >= intervalMesure) {
        previousMillisCapteurs = millis();   
        //Serial.println("Mesure capteurs");
        if (simulation){
            Serial.println("=======================================");
            Serial.println("|   Valeurs calculées par simulation  |");
            Serial.println("=======================================");
            temperatureExterieure = getSimulatedValue(SIMUL_TEMP_EXTERIEURE);
            temperatureMesuree = getSimulatedValue(SIMUL_TEMP_INTERIEURE);
            tempSortieChaudiere = getSimulatedValue(SIMUL_TEMP_SORTIE_CHAUDIERE);
            tempRetourChaudiere = getSimulatedValue(SIMUL_TEMP_RETOUR_CHAUDIERE);
            Serial.println("=======================================");
            Serial.flush();
        } else {
            Serial.println("=======================================");
            Serial.println("|   Valeurs mesurées                  |");
            Serial.println("=======================================");
            //map(value, fromLow, fromHigh, toLow, toHigh)
            temperatureExterieure = analogRead(PIN_TEMP_EXT);
            //temperatureExterieure = map (analogRead(PIN_TEMP_EXT),0,1023,500,2500);
            Serial.print("| Capteur => temp ext : ");
            Serial.println(temperatureExterieure);
            temperatureMesuree = analogRead(PIN_TEMP_INT);
            //temperatureMesuree = map (analogRead(PIN_TEMP_INT),0,1023,500,2500);
            Serial.print("| Capteur => temp int : ");
            Serial.println(temperatureMesuree);
            //tempSortieChaudiere = analogRead(PIN_TEMP_OUT_CHAUD);
            //tempRetourChaudiere = analogRead(PIN_TEMP_BACK_CHAUD);
            tempSortieChaudiere = 6000L;
            tempRetourChaudiere = 5000L;
            Serial.println("=======================================");
            Serial.flush();
        }
    }
}

