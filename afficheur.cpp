

#include <Arduino.h>
#include <LiquidCrystal_I2C_esp32.h>


#include "variables.hpp"
#include "regulation.hpp"
#include "capteurs.hpp"

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;
int numeroEcran=0;
int nbEcrans=4;
unsigned long previousMillisEcran=0 ;
long intervalDisplayEcran = 500L;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd0(0x27, lcdColumns, lcdRows);  
LiquidCrystal_I2C lcd1(0x23, lcdColumns, lcdRows);  
//LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  


//=========================================
//
//          convertValue 
//
//=========================================
String convertValue(long value, int nbDecimales){
    long partieEntiere, partieDecimale;
    char s[20]="";
    partieEntiere = value / 100;
    partieDecimale = value % 100;
    if (nbDecimales == 0){
        //Serial.print("Valeur = ");
        //Serial.print(value);
        //Serial.print(" / partie entiere = ");
        //Serial.print(partieEntiere);
        //Serial.print(" / partie decimale = ");
        //Serial.println(partieDecimale);
        sprintf(s, "%d",partieEntiere);
        //Serial.print("value converted : ");
        //Serial.println(s);
    } else {
        char tmp[10];
        itoa(partieDecimale, tmp, 10);
        tmp[nbDecimales]='\0';
        sprintf(s, "%d,%s",partieEntiere,tmp);
        //Serial.print("value converted : ");
        //Serial.println(s);
    }
    return s;
}

//=========================================
//
//          afficheClear 
//
//=========================================
void afficheClear(LiquidCrystal_I2C lcd){
    lcd.clear();
}

//=========================================
//
//          initAfficheur 
//
//=========================================
void initAfficheur(){
    lcd0.init();
    lcd0.setBacklight(HIGH); 
    lcd0.clear();

    lcd1.init();
    lcd1.setBacklight(HIGH); 
    lcd1.clear();
}

//=========================================
//
//          afficheTexte 
//
//=========================================
void afficheTexte(LiquidCrystal_I2C lcd, int colonne, int ligne, String texte){
    lcd.setCursor(colonne,ligne);
    //Serial.print("Afficheur : ");
    //Serial.println(texte);
    lcd.print(texte);
}

//=========================================
//
//          displayRegulation
//
//=========================================
void displayRegulation(LiquidCrystal_I2C lcd){
    char tmp[5];
    lcd.clear();
    afficheTexte(lcd, 0,0,"ref:");
    afficheTexte(lcd, 4,0,convertValue(consigneChauffage,1));
    afficheTexte(lcd, 8,0,"int:");
    afficheTexte(lcd, 12,0,convertValue(temperatureMesuree,1));
    afficheTexte(lcd, 0,1,"ext:");
    afficheTexte(lcd, 4,1,convertValue(temperatureExterieure,1));
    afficheTexte(lcd, 8,1,"cde:");
    afficheTexte(lcd, 12,1,convertValue(variationChauffage,0));
}

//=========================================
//
//          displayRegulation 1
//
//=========================================
void displayRegulation_1(LiquidCrystal_I2C lcd){
    char tmp[5];
    lcd.clear();
    afficheTexte(lcd, 0,0,"Consigne :");
    afficheTexte(lcd, 11,0,convertValue(consigneChauffage,1));
    afficheTexte(lcd, 0,1,"Temp ext :");
    afficheTexte(lcd, 11,1,convertValue(temperatureExterieure,1));
}

//=========================================
//
//          displayRegulation 2
//
//=========================================
void displayRegulation_2(LiquidCrystal_I2C lcd){
    char tmp[5];
    lcd.clear();
    afficheTexte(lcd, 0,0,"Temp int :");
    afficheTexte(lcd, 11,0,convertValue(temperatureMesuree,1));
    afficheTexte(lcd, 0,1,"Cde Chauf:");
    afficheTexte(lcd, 11,1,convertValue(variationChauffage,0));
}

//=========================================
//
//          displayParametres 
//
//=========================================
void displayParametres(LiquidCrystal_I2C lcd){
    lcd.clear();
    afficheTexte(lcd, 0,0,"chauffage  : ");
    if (chauffageAllume == 1){
        afficheTexte(lcd, 13,0,"on");
    } else {
        afficheTexte(lcd, 13,0,"off");
    }
    afficheTexte(lcd, 0,1,"simulation : ");
    if (simulation){
        afficheTexte(lcd, 13,1,"on");
    } else {
        afficheTexte(lcd, 13,1,"off");
    }
}

//=========================================
//
//          displayPresentation 
//
//=========================================
void displayPresentation(LiquidCrystal_I2C lcd){
    lcd.clear();
    afficheTexte(lcd, 0,0,"Regulation");
    afficheTexte(lcd, 0,1,"B. Froger");
}

//=========================================
//
//          changeEcran
//
//=========================================
void changeEcran(void){
    //Serial.println("Changement d'ecran");
    if (++numeroEcran > nbEcrans){
        numeroEcran = 0;
    }
    Serial.print(" passage sur ecran n° ");
    Serial.println(numeroEcran);
}

//=========================================
//
//          ecranLoop
//
//=========================================
void ecranLoop(void){
    if( millis() - previousMillisEcran >= intervalDisplayEcran) {
        previousMillisEcran = millis();   
        nbEcrans=4;
        switch(numeroEcran){
            case 0:
                displayPresentation(lcd0);
                break;
            case 1:
                displayRegulation(lcd0);
                break;
            case 2:
                displayRegulation_1(lcd0);
                break;
            case 3:
                displayRegulation_2(lcd0);
                break;
            case 4:
                displayParametres(lcd0);
                break;
            default :
                Serial.println("erreur numero d'ecran inexistant");
         }
    }
}
