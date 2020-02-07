
#include <Arduino.h>

#include "simulation.hpp"
#include "capteurs.hpp"
#include "regulation.hpp"
#include "variables.hpp"

long tempEauChaudiere = 6000L;       // la temperature de l'eau dans la chaudière est de 60°

void initSimulation(void){
    temperatureMesuree = 1000L;
    temperatureExterieure = 800L;
    tempSortieChaudiere = 4500L;
    tempRetourChaudiere = 3000L;
}

long getSimuTempExt(){
    Serial.print("| Simulation => ");
    Serial.print("temperature exterieure : ");
    Serial.print(temperatureExterieure);
    Serial.println();
    return temperatureExterieure;
}

long getSimuTempInt(){   
    long diffTemp = temperatureExterieure - temperatureMesuree;
    Serial.print("| Simulation => ");
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
    tempSortieChaudiere = tempEauChaudiere * variationChauffage / 10000;
    if (tempSortieChaudiere < temperatureMesuree){
        tempSortieChaudiere = temperatureMesuree;
    }
    Serial.print("| Simulation => ");
    Serial.print("temperature sortie chaudière : ");
    Serial.print(tempSortieChaudiere);
    Serial.println();
    return tempSortieChaudiere;
}


long getSimuTempRetourChaud(){
    long diffTemp = consigneChauffage - temperatureMesuree;
    tempRetourChaudiere = tempSortieChaudiere - (diffTemp / 2);
    if (tempRetourChaudiere > tempSortieChaudiere * 0.9){
        tempRetourChaudiere = tempSortieChaudiere * 0.9;
    }
    Serial.print("| Simulation => ");
    Serial.print("temperature retour chaudière : ");
    Serial.print(tempRetourChaudiere);
    Serial.println();
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
