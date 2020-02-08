

#ifndef __VARIABLES
#define __VARIABLES


#include <Arduino.h>
#include <Wifi.h>


// globales
extern boolean simulation;
extern boolean simulationTempExt;
extern boolean simulationTempMes;

// connexion
extern String ipAdress;
extern char wifiSsid[25];
extern char wifiPassword[50];
extern WiFiClient wifiClient;
extern WiFiServer wifiServer;//Ecouter le port 80


// chauffage
extern long consigneChauffage;
extern long precisionTemperature;

// fonctions
extern void initVariables(void);

#endif
