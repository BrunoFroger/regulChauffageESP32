

#include <Arduino.h>

#include "variables.hpp"
#include "simulation.hpp"
#include "regulation.hpp"

char carLu;
char commande[50];
int indexCarLu=0;

String ListeVariables[10]={
    "consigne", "simulation", 
    "temperatureMesuree", "temperatureExterieure", 
    "tempSortieChaudiere", "tempRetourChaudiere"
};


//=========================================
//
//          modifieVariable 
//
//=========================================
void modifieVariable(String variable, String valeur){
    Serial.print("modification de la vaiable <");
    Serial.print(variable);
    Serial.print("> ");
    Serial.print("avec la valeur <");
    Serial.print(valeur);
    Serial.print("> ");
    Serial.println();
}

//=========================================
//
//          visualiseVariable 
//
//=========================================
void visualiseVariable(String variable){
    Serial.print("visualisation de la vaiable <");
    Serial.print(variable);
    Serial.print(">");
    Serial.println();
}

//=========================================
//
//          analyseCommande 
//
//=========================================
void analyseCommande(String cde){
    int index = cde.indexOf(' ');
    String subCommand= cde.substring(index+1,cde.length());
    subCommand=subCommand.substring(0,subCommand.length()-1);
    if (cde.startsWith("help")){
        int idx;
        for (idx = 0 ; idx < 10 ; idx++){
            if (ListeVariables[idx] != ""){
                visualiseVariable(ListeVariables[idx]);
            }
        }
   } else if (cde.startsWith("set ")){
        // change le contenu d'une variables
        int index = subCommand.indexOf('=');
        String name = subCommand.substring(0,index);
        String value = subCommand.substring(index+1,cde.length());
        modifieVariable(name,value);
    } else if (cde.startsWith("show ")){
        // visualise le contenu d'une variables
        visualiseVariable(subCommand);
    }else if (cde.startsWith("listVariables ")){
        // visualise le contenu d'une variables
        visualiseVariable(subCommand);
    }
}

//=========================================
//
//          lireClavier 
//
//=========================================
void lireClavier(void){
    while (Serial.available() > 0){
        carLu = Serial.read();
        commande[indexCarLu++] = carLu;
        commande[indexCarLu]='\0';
        if (carLu == '\n'){
            // retour chariot saisi
            // on analyse la commande
            analyseCommande(String(commande));
            indexCarLu=0;
            commande[indexCarLu]='\0';
        }
    }
}