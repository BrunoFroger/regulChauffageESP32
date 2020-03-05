

#include <Arduino.h>

#ifndef __AFFICHEUR
#define __AFFICHEUR

#include <LiquidCrystal_I2C_esp32.h>

extern long intervalDisplayEcran;
extern LiquidCrystal_I2C lcd0;  
extern LiquidCrystal_I2C lcd1;  

extern void initAfficheur();
extern void afficheClear(LiquidCrystal_I2C lcd);
extern void afficheTexte(LiquidCrystal_I2C lcd, int ligne, int colonne, String texte);
extern void ecranLoop(void);
extern void changeEcran(void);
extern String convertValue(long value, int nbDecimales);

#endif