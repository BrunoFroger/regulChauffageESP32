



#include <Arduino.h>
#include <Wifi.h>

#include "variables.hpp"
#include "simulation.hpp"

#define PIN_TEMP_EXT        A0
#define PIN_TEMP_INT        A4
#define PIN_TEMP_OUT_CHAUD  A5
#define PIN_TEMP_BACK_CHAUD A3

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
            temperatureExterieure = getSimulatedValue(SIMUL_TEMP_EXTERIEURE);
            temperatureMesuree = getSimulatedValue(SIMUL_TEMP_INTERIEURE);
            tempSortieChaudiere = getSimulatedValue(SIMUL_TEMP_SORTIE_CHAUDIERE);
            tempRetourChaudiere = getSimulatedValue(SIMUL_TEMP_RETOUR_CHAUDIERE);
        } else {
            temperatureExterieure = analogRead(PIN_TEMP_EXT);
            temperatureMesuree = analogRead(PIN_TEMP_INT);
            tempSortieChaudiere = analogRead(PIN_TEMP_OUT_CHAUD);
            tempRetourChaudiere = analogRead(PIN_TEMP_BACK_CHAUD);
        }
    }
}

