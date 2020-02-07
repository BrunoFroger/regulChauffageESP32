
#include <Arduino.h>

#include "simulation.hpp"
#include "capteurs.hpp"
#include "regulation.hpp"

void initSimulation(void){
    temperatureMesuree = 1000L;
    temperatureExterieure = 800L;
    tempSortieChaudiere = 4500L;
    tempRetourChaudiere = 3000L;
}

long getSimuTempExt(){
    return temperatureExterieure;
}

long getSimuTempInt(){   
    long diffTemp = temperatureExterieure - temperatureMesuree;
    Serial.print("temperature interieure : ");
    Serial.print(temperatureMesuree);
    Serial.print(" + (");
    Serial.print(variationChauffage);
    Serial.print(" / 100) + (");
    Serial.print(diffTemp);
    Serial.print(" / 20) = ");
    temperatureMesuree += (variationChauffage / 100.0);
    temperatureMesuree += (diffTemp / 20.0);
    Serial.print(temperatureMesuree);
    Serial.println();
    return temperatureMesuree;
}

long getSimuTempSortieChaud(){
    return tempSortieChaudiere;
}


long getSimuTempRetourChaud(){
    return tempRetourChaudiere;
}


long getSimulatedValue(int type){
    switch(type){
        case SIMUL_TEMP_INTERIEURE:
            return getSimuTempInt();
            break;
        case SIMUL_TEMP_EXTERIEURE:
            return getSimuTempExt();
            break;
        case SIMUL_TEMP_SORTIE_CHAUDIERE:
            return getSimuTempSortieChaud();
            break;
        case SIMUL_TEMP_RETOUR_CHAUDIERE:
            return getSimuTempRetourChaud();
            break;
        default:
            return 0L;
    }
}
