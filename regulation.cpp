


#include <Arduino.h>

#include "variables.hpp"
#include "regulation.hpp"
#include "capteurs.hpp"



unsigned long previousMillisRegulation=0 ;
double intervalCalculRegulation = 1000L;
boolean chauffageAllume = false;
boolean interrupteurPompe = false;
double variationChauffage= 0.0;


//=========================================
//
//          regulationInit
//
//=========================================
void regulationInit(void){

}


//=========================================
//
//          augmenteChauffage
//
//=========================================
void augmenteChauffage(void){
    Serial.println("augmenteChauffage");
    variationChauffage++;
    if (variationChauffage > 100.0){
        variationChauffage = 100.0;
    }
}


//=========================================
//
//          reduireChauffage
//
//=========================================
void reduireChauffage(void){
    Serial.println("reduireChauffage");
    variationChauffage--;
    if (variationChauffage < 0.0){
        variationChauffage = 0.0;
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
        Serial.println("Calcul regulation");
        if (chauffageAllume){
            // le chauffage est allumé, on calcule la régulation
            if (temperatureExterieure >= temperatureMesuree){
                // la temperature exterieure est superieure a la temperature interieur on eteint tout
                interrupteurPompe = false;
                variationChauffage = 0.0;
            } else {
                if (temperatureMesuree <= (consigneChauffage - precisionTemperature)){
                    // la temperature interieure est inferieure a la consigne on augmente le chauffage
                    if (!interrupteurPompe){
                        interrupteurPompe=true;
                    }
                    augmenteChauffage();
                } else {
                    if (temperatureMesuree >= (consigneChauffage + precisionTemperature)){
                        // la temperature interieure est superieure a la consigne on diminue le chauffage
                        if (variationChauffage == 0.0){
                            if (interrupteurPompe){
                                interrupteurPompe = false;
                            }
                        } else {
                            reduireChauffage();
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
            if (variationChauffage != 0.0){
                variationChauffage = 0.0;
            }
        }
    }
}

/* algorithme de regulation
si (mode chauffage = allumé)
	si (temperature exterieure > temperature interieure)
		interrupteur pompe <- off
		variateur de chauffage <- 0
	sinon 
		si (temperature interieure < (consigne de chauffage - precision de chauffage))
			si interrupteur pompe = off
				interrupteur pompe <- on
			augmenter variateur de chauffage 
		sinon 
			si (temperature interieure > (consigne de chauffage + precision de chauffage))
				reduire variateur de chauffage 
				si variation chauffage = 0	
					interrupteur pompe <- off
			sinon
				ne rien faire
sinon
	si interrupteur pompe = on
		interrupteur pompe <- off
	sinon
		ne rien faire

*/