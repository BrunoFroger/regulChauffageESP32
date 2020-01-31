





#include <Arduino.h>
#include <Wifi.h>


boolean simulation=false;

//=========================================
//
//          WIFI 
//
//=========================================
String ipAdress;
char wifiSsid[25];
char wifiPassword[50];
WiFiClient wifiClient;
WiFiServer wifiServer(80);//Ecouter le port 80

//=========================================
//
//          parametres de chauffage
//
//=========================================
double consigneChauffage;
double precisionTemperature;

//=========================================
//
//          fonctions
//
//=========================================
void initVariables(void){
    ipAdress = WiFi.localIP().toString();
    consigneChauffage = 20;
    precisionTemperature=0.05;
}
