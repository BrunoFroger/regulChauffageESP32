

#include <Arduino.h>
#include <Wifi.h>
#include "WifiTools.hpp"
#include "variables.hpp"
#include "capteurs.hpp"
#include "regulation.hpp"
#include "simulation.hpp"

extern WiFiClient wifiClient;

//=========================================
//
//          initWifi
//
//=========================================
void initWifi(void){    // search for availables Wifi Networks
    int nbSsid = WiFi.scanNetworks();
    if (nbSsid != -1){
        Serial.print(nbSsid);
        Serial.println(" wifi networks found");
        strcpy(wifiSsid,"");
        while (strcmp(wifiSsid,"") == 0){        
            for (int ssidNetwork = 0 ; ssidNetwork < nbSsid ; ssidNetwork++){
                Serial.print("  check network : ");
                Serial.print(WiFi.SSID(ssidNetwork));
                if (WiFi.SSID(ssidNetwork) == "NETGEAR17"){
                    strcpy(wifiSsid,"NETGEAR17");
                    strcpy(wifiPassword, "largesea818");
                    Serial.println(" => OK");
                    break;
                }
                if (WiFi.SSID(ssidNetwork) == "Livebox-006d"){
                    strcpy(wifiSsid,"Livebox-006d");
                    strcpy(wifiPassword, "A23F1F7979C9DD3C5916324123");
                    Serial.println(" => OK");
                    break;
                }
                Serial.println(" => NOK");
            }
        }

        // Connect to WiFi network
        Serial.println();    //On suit toute l'action sur le moniteur
        Serial.print("Connecting to ");
        Serial.println(wifiSsid);
        WiFi.begin(wifiSsid, wifiPassword);
        int cpt=0;
        while (WiFi.status() != WL_CONNECTED) {  //Attente de la connexion
            delay(500);
            Serial.print(".");   //Typiquement 5 à 10 points avant la connexion
            if (cpt++ >= 5){
                Serial.println();
                cpt=0;
                WiFi.begin(wifiSsid, wifiPassword);
            }
        }
        Serial.println("");
        Serial.println("WiFi connected");

        // Start the server
        wifiServer.begin();
        wifiServer.println("Server started");

        // Print the IP address
        Serial.print("Use this URL to connect: ");
        Serial.print("http://");
        Serial.print(WiFi.localIP());
        Serial.println("/");  //Utiliser cette URL sous Firefox de preference à Chrome

    }
}

//=========================================
//
//          displayHeader
//
//=========================================
void displayHeader(void){
    //Serial.println("displayHeader"); 
    wifiClient.println("HTTP/1.1 200 OK");
    wifiClient.println("Content-Type: text/html");
    wifiClient.println(""); //  do not forget this one
    wifiClient.println("<!DOCTYPE HTML>");
    wifiClient.println("<style type=\"text/css\">");
    wifiClient.println("    div {");
    wifiClient.println("        width:expression(document.body.clientWidth >= 1000? \"1000px\": \"auto\" );");
    wifiClient.println("    }");
    wifiClient.println("    table, th, td {");
    wifiClient.println("        padding: 10px;");
    wifiClient.println("        border: 1px solid black;");
    wifiClient.println("        border-collapse: collapse;");
    wifiClient.println("    }");
    wifiClient.println("</style>");
    wifiClient.println("<html>");
    wifiClient.println("<head><title>Test ESP 32</title>");   //Pour l'onglet du navigateur
    wifiClient.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, minimum-scale=1, maximum-scale=1, user-scalable=no\" />"); 
    //wifiClient.println("<meta http-equiv=\"refresh\" content=\"5\" />");
    wifiClient.println("<meta charset=\"utf-8\" />"); 

    //Pour eviter l'emission de  'GET /favicon.ico HTTP/1.1' à chaque requete
    wifiClient.println("<link rel=\"icon\" href=\"data:,\">");

    wifiClient.println("</head>");
    wifiClient.println("<body>");
    //wifiClient.println("=============================================================================================");
    wifiClient.println("<div><br><br>");
}


//=========================================
//
//          displayFooter
//
//=========================================
void displayFooter(void){
    //Serial.println("displayFooter"); 
    wifiClient.println("</div><br><br>");
    //wifiClient.println("=============================================================================================");
    wifiClient.println("</body>");
    wifiClient.println("</html>");  //Fin de la page
    //Serial.println("Client disconnected");  //Aller attendre une nouvelle demande du Client
    //Serial.println("");
}


//=========================================
//
//          displayHomeMessage
//
//=========================================
void displayHomeMessage(void){
    //Serial.println("displayHomeMessage"); 
    wifiClient.println("<h2>Gestion Chauffage avec ESP 32</h2>");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("Application de gestion de chauffage avec un ESP 32");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("Vous allez pouvoir acceder aux differentes fonctionnalites de gestion du chauffage en cliquant sur un des liens suivants : ");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("<a href= \" /config \" >configuration</a>");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("<a href= \" /capteurs \" >capteurs</a>");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("<a href= \" /reglages \" >réglages</a>");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("<a href= \" /visualisation \" >visualisation</a>");
    wifiClient.println("<br><br>");      //Saut de lignes
    //wifiClient.println("<a href= \" /dfgsdgfqdfsg \" >test page erreur</a>");
    //wifiClient.println("<br><br>");      //Saut de lignes
}


//=========================================
//
//          displayConfigScreen
//
//=========================================
void displayConfigScreen(void){
    //Serial.println("displayConfigScreen"); 
    wifiClient.println("<h2>Configuration</h2>");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("écran de configuration des paramètres de l'application :");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("<table style=\"border:2px\">");
    wifiClient.println("    <tr>");
    wifiClient.println("        <th>Paramètre</th>");
    wifiClient.println("        <th>Valeur</th>");
    wifiClient.println("    </tr>");
    wifiClient.println("    <tr>");
    wifiClient.println("        <td><a href= \" /switchChauffage \" >chauffage allummé on/off</a></td>");
    wifiClient.println("        <td>");
    wifiClient.println(chauffageAllume);
    wifiClient.println("        </td>");
    wifiClient.println("    <tr>");
    wifiClient.println("        <td>Consigne de chauffage</td>");
    wifiClient.println("        <td>");
    wifiClient.println(consigneChauffage);
    wifiClient.println("        </td>");
    wifiClient.println("    </tr>");
    wifiClient.println("    <tr>");
    wifiClient.println("        <td>precision de régulation</td>");
    wifiClient.println("        <td>");
    wifiClient.println(precisionTemperature);
    wifiClient.println("        </td>");
    wifiClient.println("    </tr>");
    wifiClient.println("    <tr>");
    wifiClient.println("        <td>Adresse IP</td>");
    wifiClient.println("        <td>");
    wifiClient.println(ipAdress);
    wifiClient.println("        </td>");
    wifiClient.println("    </tr>");
    wifiClient.println("    <tr>");
    wifiClient.println("        <td>Wifi SSID</td>");
    wifiClient.println("        <td>");
    wifiClient.println(wifiSsid);
    wifiClient.println("        </td>");
    wifiClient.println("    </tr>");
    wifiClient.println("    <tr>");
    wifiClient.println("        <td><a href= \" /switchSimulation \" >Simulation on/off</a></td>");
    wifiClient.println("        <td>");
    wifiClient.println(simulation);
    wifiClient.println("        </td>");
    wifiClient.println("    </tr>");
    wifiClient.println("</table>");
    wifiClient.println("</table>");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("<a href= \" / \" >Retour</a>");
    wifiClient.println("<br><br>");      //Saut de lignes
}


//=========================================
//
//          displayCapteursScreen
//
//=========================================
void displayCapteursScreen(void){
    //Serial.println("displayCapteursScreen"); 
    wifiClient.println("<h2>Capteurs</h2>");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("Voici les valeurs mesurèes sur les différents capteurs du système");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("<table>");
    wifiClient.println("    <tr>");
    wifiClient.println("        <th>Paramètre</th>");
    wifiClient.println("        <th>Valeur</th>");
    wifiClient.println("    </tr>");
    wifiClient.println("    <tr>");
    wifiClient.println("        <td>Température mesurée</td>");
    wifiClient.println("        <td>");
    wifiClient.println(temperatureMesuree);
    wifiClient.println("        </td>");
    wifiClient.println("    </tr>");
    wifiClient.println("    <tr>");
    wifiClient.println("        <td>Température extérieure</td>");
    wifiClient.println("        <td>");
    wifiClient.println(temperatureExterieure);
    wifiClient.println("        </td>");
    wifiClient.println("    </tr>");
    wifiClient.println("    <tr>");
    wifiClient.println("        <td>Temp sortie chaudière</td>");
    wifiClient.println("        <td>");
    wifiClient.println(tempSortieChaudiere);
    wifiClient.println("        </td>");
    wifiClient.println("    </tr>");
    wifiClient.println("    <tr>");
    wifiClient.println("        <td>Temp retour chaudière</td>");
    wifiClient.println("        <td>");
    wifiClient.println(tempRetourChaudiere);
    wifiClient.println("        </td>");
    wifiClient.println("    </tr>");
    wifiClient.println("</table>");
    wifiClient.println("</form>");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("<br><a href= \" /capteurs \" >Refresh</a><br>");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("<br><a href= \" / \" >Retour</a><br>");
    wifiClient.println("<br><br>");      //Saut de lignes
}



//=========================================
//
//          displayReglagesScreen
//
//=========================================
void displayReglagesScreen(void){
    //Serial.println("displayReglagesScreen"); 
    //Serial.print("consigne = ");
    //Serial.println(consigneChauffage);
    //Serial.println();
    wifiClient.println("<h2>Réglages</h2>");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("Cette page vous permet de modifier les paramètres de chauffage");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("<form method=\"get\" action=\"updateReglages\"  >");
    wifiClient.println("<table>");
    wifiClient.println("    <tr>");
    wifiClient.println("        <th>Paramètre</th>");
    wifiClient.println("        <th>Valeur</th>");
    wifiClient.println("    </tr>");
    wifiClient.println("    <tr>");
    wifiClient.println("        <td>consigne</td>");
    wifiClient.println("        <td>");
    wifiClient.println("            <input");
    wifiClient.println("                type=\"number\" ");
    wifiClient.println("                placeholder=\"0.1\" ");
    wifiClient.println("                step=\"0.01\" ");
    wifiClient.println("                min=\"10.0\" ");
    wifiClient.println("                max=\"30.0\" ");
    wifiClient.println("                name=\"consigne\" ");
    wifiClient.println("                value=");
    wifiClient.println(                     consigneChauffage);
    wifiClient.println("            />");
    wifiClient.println("        </td>");
    wifiClient.println("    </tr>");
    wifiClient.println("    <tr>");
    wifiClient.println("        <td>précision température</td>");
    wifiClient.println("        <td>");
    wifiClient.println("            <input");
    wifiClient.println("                type=\"number\" ");
    wifiClient.println("                placeholder=\"0.01\" ");
    wifiClient.println("                step=\"0.01\" ");
    wifiClient.println("                min=\"0.01\" ");
    wifiClient.println("                max=\"1.0\" ");
    wifiClient.println("                name=\"precTemp\" ");
    wifiClient.println("                value=");
    wifiClient.println(                     precisionTemperature);
    wifiClient.println("            />");
    wifiClient.println("        </td>");
    wifiClient.println("    </tr>");
    wifiClient.println("    <tr>");
    wifiClient.println("        <td>intervale de mesure (ms)</td>");
    wifiClient.println("        <td>");
    wifiClient.println("            <input");
    wifiClient.println("                type=\"number\" ");
    wifiClient.println("                placeholder=\"0.1\" ");
    wifiClient.println("                step=\"0.01\" ");
    wifiClient.println("                min=\"1000\" ");
    wifiClient.println("                max=\"50000\" ");
    wifiClient.println("                name=\"intMesure\" ");
    wifiClient.println("                value=");
    wifiClient.println(                     intervalMesure);
    wifiClient.println("            />");
    wifiClient.println("        </td>");
    wifiClient.println("    </tr>");
    wifiClient.println("</table>");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("<input type=\"submit\" value=\"Valider\">");
    wifiClient.println("</form>");
    wifiClient.println("<br><a href= \" / \" >Retour</a><br>");
    wifiClient.println("<br><br>");      //Saut de lignes
}


//=========================================
//
//          displayVisualScreen
//
//=========================================
void displayVisualScreen(void){
    //Serial.println("displayVisualScreen"); 
    //Serial.println();
    wifiClient.println("<h2>Visualisation</h2>");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("Cette page montre l'évolution des parametres de chauffage");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("<form method=\"get\" action=\"updateReglages\"  >");
    wifiClient.println("<table>");
    wifiClient.println("    <tr>");
    wifiClient.println("        <th>Paramètre</th>");
    wifiClient.println("        <th>Valeur</th>");
    wifiClient.println("        <th></th>");
    wifiClient.println("        <th> </th>");
    wifiClient.println("    </tr>");
    wifiClient.println("    <tr>");
    wifiClient.println("        <td><a href=\"/updateSimulation?chauffage=switch\">chauffage allumé</a></td>");
    wifiClient.println("        <td>");
    wifiClient.println(chauffageAllume);
    wifiClient.println("        </td>");
    wifiClient.println("        <td></td>");
    wifiClient.println("        <td></td>");
    wifiClient.println("    </tr>");
    wifiClient.println("    <tr>");
    wifiClient.println("        <td><a href=\"/updateSimulation?simulation=switch\">simulation</a></td>");
    wifiClient.println("        <td>");
    wifiClient.println(simulation);
    wifiClient.println("        </td>");
    wifiClient.println("        <td></td>");
    wifiClient.println("        <td></td>");
    wifiClient.println("    </tr>");
    wifiClient.println("    <tr>");
    wifiClient.println("        <td>consigne</td>");
    wifiClient.println("        <td>");
    wifiClient.println(consigneChauffage);
    wifiClient.println("        </td>");
    wifiClient.println("        <td><a href=\"/updateSimulation?tempCons=0.1\">+</a></td>");
    wifiClient.println("        <td><a href=\"/updateSimulation?tempCons=-0.1\">+</a></td>");
    wifiClient.println("    </tr>");
    wifiClient.println("    <tr>");
    wifiClient.println("        <td>temperature interieure</td>");
    wifiClient.println("        <td>");
    wifiClient.println(temperatureMesuree);
    wifiClient.println("        </td>");
    wifiClient.println("        <td><a href=\"/updateSimulation?tempInt=0.1\">+</a></td>");
    wifiClient.println("        <td><a href=\"/updateSimulation?tempInt=-0.1\">+</a></td>");
    wifiClient.println("    </tr>");
    wifiClient.println("    </tr>");
    wifiClient.println("        <td>temperature exterieure</td>");
    wifiClient.println("        <td>");
    wifiClient.println(temperatureExterieure);
    wifiClient.println("        </td>");
    wifiClient.println("        <td><a href=\"/updateSimulation?tempExt=0.1\">+</a></td>");
    wifiClient.println("        <td><a href=\"/updateSimulation?tempExt=-0.1\">+</a></td>");
    wifiClient.println("    </tr>");
    wifiClient.println("    </tr>");
    wifiClient.println("        <td>pompe</td>");
    wifiClient.println("        <td>");
    wifiClient.println(interrupteurPompe);
    wifiClient.println("        </td>");
    wifiClient.println("        <td></td>");
    wifiClient.println("        <td></td>");
    wifiClient.println("    </tr>");
    wifiClient.println("    </tr>");
    wifiClient.println("        <td>commande de chauffage</td>");
    wifiClient.println("        <td>");
    wifiClient.println(variationChauffage);
    wifiClient.println("        </td>");
    wifiClient.println("        <td></td>");
    wifiClient.println("        <td></td>");
    wifiClient.println("    </tr>");
    wifiClient.println("</table>");
    wifiClient.println("</form>");
    wifiClient.println("<br><a href= \" /visualisation \" >Refresh</a><br>");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("<br><a href= \" / \" >Retour</a><br>");
    wifiClient.println("<br><br>");      //Saut de lignes
}

//=========================================
//
//          displayErrorScreen
//
//=========================================
void displayErrorScreen(void){
    wifiClient.println("<h2>Erreur</h2>");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("Cette page n'existe pas sur ce serveur");
    wifiClient.println("<br><br>");      //Saut de lignes
    wifiClient.println("<br><a href= \" / \" >Retour</a><br>");
    wifiClient.println("<br><br>");      //Saut de lignes
}

//=========================================
//
//          updateVariable
//
//=========================================
void updateVariable(String requete){
    //Serial.println("updateVariable"); 
    //Serial.print("requete recue : ");
    //Serial.print(requete);
    //Serial.println();
    int index = requete.indexOf('=');
    String name = requete.substring(0,index);
    String value = requete.substring(index+1,requete.length());

    
    Serial.print("nom de la variable : <");
    Serial.print(name);
    Serial.print("> ; valeur : <");
    Serial.print(value);
    Serial.println(">");
    

    if (name.equals("consigne")){
        consigneChauffage = value.toDouble();
    } else if (name.equals("precTemp")){
        precisionTemperature = value.toDouble();
    } else if (name.equals("intMesure")){
        intervalMesure = value.toDouble();
    } else if (name.equals("tempInt")){
        temperatureMesuree += value.toDouble();
    } else if (name.equals("tempExt")){
        temperatureExterieure += value.toDouble();
    } else if (name.equals("tempCons")){
        consigneChauffage += value.toDouble();
    } else if (name.equals("chauffage")){
        chauffageAllume = !chauffageAllume;
    } else if (name.equals("simulation")){
        simulation = !simulation;
        if (simulation){
            initSimulation();
        }
    } else {
        Serial.print("ERREUR : nom de variable inconnu : ");
        Serial.print(name);
        Serial.println();
    }
}


//=========================================
//
//          updateReglages
//
//=========================================
void updateReglages(String request){
    String tmp;
    //Serial.println("updateReglages"); 
    //Serial.print("requete recue : ");
    //Serial.print(request);
    //Serial.println();
    int index1 = request.lastIndexOf("?");
    int index2 = request.lastIndexOf(" HTTP");
    tmp=request.substring(index1+1,index2);
    while (tmp.indexOf('&') != -1){
        updateVariable(tmp.substring(0,tmp.indexOf('&')));
        tmp=tmp.substring(tmp.indexOf('&')+1, tmp.length());
    }
    updateVariable(tmp);
}


//=========================================
//
//          switchSimulation
//
//=========================================
void switchSimulation(void){
    if (simulation){
        simulation =false;
    } else {
        simulation = true;
    }
}


//=========================================
//
//          switchSimulation
//
//=========================================
void switchChauffage(void){
    if (chauffageAllume){
        chauffageAllume =false;
    } else {
        chauffageAllume = true;
    }
}



//=========================================
//
//          analyseRequest
//
//=========================================
void analyseRequest(String request){

    //Serial.print("Requete a analyser : ");
    //Serial.print(request);
    //Serial.println();
    displayHeader();
    if (request.equals("GET / HTTP/1.1")){
        displayHomeMessage();
    } else if (request.equals("GET /config HTTP/1.1")){
        displayConfigScreen();
    }else if (request.equals("GET /capteurs HTTP/1.1")){
        displayCapteursScreen();
    } else if (request.equals("GET /reglages HTTP/1.1")){
        displayReglagesScreen();
    } else if (request.equals("GET /switchSimulation HTTP/1.1")){
        switchSimulation();
        displayConfigScreen();
    } else if (request.equals("GET /switchChauffage HTTP/1.1")){
        switchChauffage();
        displayConfigScreen();
    } else if (request.startsWith("GET /visualisation HTTP/1.1")){
        displayVisualScreen();
    } else if (request.startsWith("GET /updateSimulation")){
        updateReglages(request);
        request = "GET /visualisation HTTP/1.1";
        displayVisualScreen();
    } else if (request.startsWith("GET /updateReglages")){
        updateReglages(request);
        request = "GET /reglages HTTP/1.1";
        displayReglagesScreen();
    }else {
        displayErrorScreen();
    }
    displayFooter();
}
