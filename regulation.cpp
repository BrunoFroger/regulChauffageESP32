


#include <Arduino.h>

#include "variables.hpp"
#include "regulation.hpp"
#include "capteurs.hpp"
#include "afficheur.hpp"



unsigned long previousMillisRegulation=0 ;
long intervalCalculRegulation = 1000L;
boolean chauffageAllume = false;
boolean interrupteurPompe = false;
long variationChauffage= 0L;


//=========================================
//
//          regulationInit
//
//=========================================
void regulationInit(void){

}

/*
//=========================================
//
//          augmenteChauffage
//
//=========================================
void augmenteChauffage(long diffTemp){
    //Serial.println("augmenteChauffage");
    long delta;
    if (diffTemp > 1000L){
        delta = 500L;
    } else if (diffTemp > 500L){
        delta = 250L;
    } else if (diffTemp > 200L) {
        delta = 100L;
    } else {
        delta = 050L;
    }
    Serial.print("augmenteChauffage de ");
    Serial.println(delta);
    variationChauffage += delta;
    if (variationChauffage > 10000L){
        variationChauffage = 10000L;
    }
}


//=========================================
//
//          reduireChauffage
//
//=========================================
void reduireChauffage(long diffTemp){
    long delta;
    if (diffTemp > 1000L){
        delta = 500L;
    } else if (diffTemp > 500L){
        delta = 250L;
    } else if (diffTemp > 200L) {
        delta = 100L;
    } else {
        delta = 50L;
    }
    Serial.print("augmenteChauffage de ");
    Serial.println(delta);
    variationChauffage -= delta;
    if (variationChauffage < 0L){
        variationChauffage = 0L;
    }
}
*/

//=========================================
//
//          updateChauffage
//
//=========================================
void updateChauffage(long diffTemp){
    long delta = 0;
    if (diffTemp > 0){
        if (diffTemp > 1000L){
            delta = 500L;
        } else if (diffTemp > 500L){
            delta = 250L;
        } else if (diffTemp > 200L) {
            delta = 100L;
        } else {
            delta = 50L;
        }
    } else {        
        if (diffTemp < -1000L){
            delta = -5;
        } else if (diffTemp < -500L){
            delta = -250L;
        } else if (diffTemp < -200L) {
            delta = -100L;
        } else {
            delta = -50L;
        } 
    }
    Serial.print("updateChauffage de ");
    Serial.println(delta);
    variationChauffage += delta;
    if (variationChauffage > 10000L){
        variationChauffage = 10000L;
    }
    if (variationChauffage < 0L){
        variationChauffage = 0L;
    }
}



//=========================================
//
//          regulationLoop
//
//=========================================
void regulationLoop(void){
    if( millis() - previousMillisRegulation >= intervalCalculRegulation) {
        previousMillisRegulation = millis();   
        //Serial.println("Calcul regulation");
        if (chauffageAllume){
            // on calcule la difference de temperature entre exterieur et interieur
            long diffTemp = consigneChauffage - temperatureMesuree;
            // le chauffage est allumé, on calcule la régulation
            if (temperatureExterieure >= temperatureMesuree){
                // la temperature exterieure est superieure a la temperature interieur on eteint tout
                interrupteurPompe = false;
                variationChauffage = 0L;
            } else {
                if (temperatureMesuree <= (consigneChauffage - precisionTemperature)){
                    // la temperature interieure est inferieure a la consigne on augmente le chauffage
                    if (!interrupteurPompe){
                        interrupteurPompe=true;
                    }
                    updateChauffage(diffTemp);
                } else {
                    if (temperatureMesuree >= (consigneChauffage + precisionTemperature)){
                        // la temperature interieure est superieure a la consigne on diminue le chauffage
                        if (variationChauffage == 0L){
                            if (interrupteurPompe){
                                interrupteurPompe = false;
                            }
                        } else {
                            updateChauffage(diffTemp);
                        }
                    } else {
                        // la temperature est proche de la consigne ; on ne fait rien
                    }
                }
            }
        } else {
            // le chauffage est eteint ; on ne fait rien
            // on eteint la pompe si necessaire
            if (interrupteurPompe){
                interrupteurPompe = false;
            }
            // on remet a 0 la commande de chauffage si necessaire
            if (variationChauffage != 0L){
                variationChauffage = 0L;
            }
        }
        displayRegulation();
    }
}
