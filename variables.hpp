

#ifndef __VARIABLES
#define __VARIABLES


#include <Arduino.h>
#include <Wifi.h>


// globales
extern boolean simulation;

// connexion
extern String ipAdress;
extern char wifiSsid[25];
extern char wifiPassword[50];
extern WiFiClient wifiClient;
extern WiFiServer wifiServer;//Ecouter le port 80


// chauffage
extern double consigneChauffage;
extern double precisionTemperature;

// fonctions
extern void initVariables(void);

#endif
