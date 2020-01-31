
#include <Arduino.h>

#include "simulation.hpp"
#include "capteurs.hpp"
#include "regulation.hpp"

void initSimulation(void){
    temperatureMesuree = 20.0;
    temperatureExterieure = 15.0;
    tempSortieChaudiere = 45.0;
    tempRetourChaudiere = 30.0;
}

double getSimuTempExt(){
    return temperatureExterieure;
}

double getSimuTempInt(){   
    double diffTemp = temperatureExterieure - temperatureMesuree;
    Serial.print("temperature interieure : ");
    Serial.print(temperatureMesuree);
    Serial.print(" + (");
    Serial.print(variationChauffage);
    Serial.print(" / 100) + (");
    Serial.print(diffTemp);
    Serial.print(" / 10) = ");
    temperatureMesuree += (variationChauffage / 100.0);
    temperatureMesuree += (diffTemp / 10.0);
    Serial.print(temperatureMesuree);
    Serial.println();
    return temperatureMesuree;
}

double getSimuTempSortieChaud(){
    return tempSortieChaudiere;
}


double getSimuTempRetourChaud(){
    return tempRetourChaudiere;
}


double getSimulatedValue(int type){
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
            return 0.0;
    }
}
