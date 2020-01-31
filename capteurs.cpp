



#include <Arduino.h>
#include <Wifi.h>

#include "variables.hpp"
#include "simulation.hpp"

#define PIN_TEMP_EXT        A0
#define PIN_TEMP_INT        A4
#define PIN_TEMP_OUT_CHAUD  A5
#define PIN_TEMP_BACK_CHAUD A3

double temperatureMesuree;
double temperatureExterieure;
double tempSortieChaudiere=0.0;
double tempRetourChaudiere=0.0;


unsigned long previousMillisCapteurs=0 ;
double intervalMesure = 1000L;

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
        Serial.println("Mesure capteurs");
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

