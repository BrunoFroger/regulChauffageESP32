


#include <Arduino.h>
#include "afficheur.hpp"

#define PIN_BOUTON 12

boolean etatBouton=false;

//=========================================
//
//          modifieVariable 
//
//=========================================
boolean getBoutonState(void){
    return etatBouton;
}

//=========================================
//
//          readBouton 
//
//=========================================
boolean readBouton(void){
    boolean boutonAppuye = (digitalRead(PIN_BOUTON) == 1);
    if (boutonAppuye && !etatBouton){
        // le bouton vient d'etre appuyé
        Serial.println("bouton appuyé");
        changeEcran();
        etatBouton = true;
    } else if (boutonAppuye && etatBouton){
        // le bouton est toujour appuyé
        etatBouton = true;
    } else if (!boutonAppuye && etatBouton){
        // le bouton vient d'etre relaché
        Serial.println("bouton relaché");
        etatBouton = false;
    } else if (!boutonAppuye && !etatBouton){
        // bouton relaché est toujours relaché
        etatBouton = false;
    }
    return etatBouton;
}