


#include <Arduino.h>
#include <EEPROM.h>

#include "variables.hpp"
#include "regulation.hpp"
#include "capteurs.hpp"

#define EEPROM_SIZE     64
#define EEPROM_START    0

struct{
    long consigneChauffage;
    long precisionTemperature;
    long intervalCalculRegulation;
    long intervalMesure;
    boolean chauffageAllume;
} storedDatas;

boolean datasToUpdate = false;
boolean storageAvailable = false;
unsigned long previousMillisSaveDatas=0 ;
long intervalSaveDatas = 5000L;

void displayStoredDatasStructure(void){
    String tmp, tmp1;
    Serial.println("+--------------------------------------------------------+");
    Serial.println("|           Structure de données a sauvegarder           |");
    Serial.println("+--------------------+-----------------------------------+");
    Serial.println("| nom                | valeur eeprom   | valeur memoire  |");
    Serial.println("+--------------------+-----------------+-----------------+");
    Serial.print  ("| consigne chauffage |");
    tmp = String(storedDatas.consigneChauffage);
    tmp1 = String(consigneChauffage);
    Serial.printf (" %14s  | %14s  |\n", tmp, tmp1);

    Serial.print  ("| chauffage on/off   |");
    tmp = String(storedDatas.chauffageAllume);
    tmp1 = String(chauffageAllume);
    Serial.printf (" %14s  | %14s  |\n", tmp, tmp1);

    Serial.print  ("| precision temp     |");
    tmp = String(storedDatas.precisionTemperature);
    tmp1 = String(precisionTemperature);
    Serial.printf (" %14s  | %14s  |\n", tmp, tmp1);

    Serial.print  ("| intervale regul    |");
    tmp = String(storedDatas.intervalCalculRegulation);
    tmp1 = String(intervalCalculRegulation);
    Serial.printf (" %14s  | %14s  |\n", tmp, tmp1);

    Serial.print  ("| intervale mesure   |");
    tmp = String(storedDatas.intervalMesure);
    tmp1 = String(intervalMesure);
    Serial.printf (" %14s  | %14s  |\n", tmp, tmp1);
    Serial.println("+--------------------+-----------------+-----------------+");
}

void storageError(void){
    Serial.print("ERROR : taille structure de donnéées a sauvegarder (");
    Serial.print(sizeof(storedDatas));
    Serial.println(") ");
    Serial.print("est supérieure a la taille reservée (");
    Serial.print(EEPROM_SIZE);
    Serial.print(")");
    Serial.println();
    Serial.flush();
}

void restoreDatasfromFlash(void){
    if (storageAvailable){
        EEPROM.get(EEPROM_START, storedDatas);
            consigneChauffage = storedDatas.consigneChauffage;
            chauffageAllume = storedDatas.chauffageAllume;
            precisionTemperature = storedDatas.precisionTemperature;
            intervalCalculRegulation = storedDatas.intervalCalculRegulation;
            intervalMesure = storedDatas.intervalMesure;
        Serial.println("Restauration des données sauvegardées en Eeprom OK");
        datasToUpdate = false;
        displayStoredDatasStructure();
    } else {
        storageError();
    }
}

void initSaveToFlash(void){
    if (sizeof(storedDatas) > EEPROM_SIZE){
        storageAvailable = false;
        storageError();
    } else {
        Serial.println("Init Eeprom OK");
        EEPROM.begin(EEPROM_SIZE);
        storageAvailable = true;
        restoreDatasfromFlash();
    }
}

boolean savetoFlashNeeded(void){
    datasToUpdate = false;
    if (storedDatas.consigneChauffage != consigneChauffage){
        //Serial.println("consigneChauffage a changé");
        datasToUpdate = true;
    }
    if (storedDatas.chauffageAllume != chauffageAllume){
        //Serial.println("chauffageAllume a changé");
        datasToUpdate = true;
    }
    if (storedDatas.precisionTemperature != precisionTemperature){
        //Serial.println("precisionTemperature a changé");
        datasToUpdate = true;
    }
    if (storedDatas.intervalCalculRegulation != intervalCalculRegulation){
        //Serial.println("intervalCalculRegulation a changé");
        datasToUpdate = true;
    }
    if (storedDatas.intervalMesure != intervalMesure){
        //Serial.print("intervalMesure a changé : ");
        datasToUpdate = true;
    }
    //Serial.print("savetoFlashNeeded : ");
    //Serial.println(datasToUpdate);
    displayStoredDatasStructure();
    return (datasToUpdate);
}

void saveDatasToFlash(void){
    if (storageAvailable){
        if (savetoFlashNeeded()){
            if( millis() - previousMillisSaveDatas >= intervalSaveDatas) {
                previousMillisSaveDatas = millis();   
                storedDatas.consigneChauffage = consigneChauffage;
                storedDatas.chauffageAllume = chauffageAllume;
                storedDatas.precisionTemperature = precisionTemperature;
                storedDatas.intervalCalculRegulation = intervalCalculRegulation;
                storedDatas.intervalMesure = intervalMesure;
                EEPROM.put(0, storedDatas);
                EEPROM.commit();
                Serial.println("Sauvegarde des données en Eeprom OK");
            }
        //} else {
            //Serial.println("Sauvegarde des données en Eeprom inutile, pas de changement dans les valeurs");
        }
    } else {
        storageError();
    }
}

