/*
  Contrôle d'accès et télécommande RFID par page web
  Créé par Carlos FIGUEROA ( FIZET MX ) et Severin LAMAH                                          
  pour le module IdO du sujet de supervision IUT LONGWY
  2021 France
*/

#include "RFID.h"
#include "WiFi.h"
#include "Web.h"
#include "Portes.h"
#include "SPIFFS.h"
#include <FS.h>
int temp_milis = 5000; //temp pour atreindre le carte NFC
unsigned long temp_init_milis = 0;
void setup() {
  Serial.begin(9600);
  SPI.begin();//Pour Access au protocol SPI et conecter le RFID
  rfid.init();
  // Initi  SPIFFS pour access au donnes sur le racine
  if (!SPIFFS.begin(true)) {
    Serial.println("ne erreur s'est produite lors du montage du SPIFFS");
    return;
  }
  //WiFI Init
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("WiFi est en train de se connecter..");
  }

  //Afficher le ip local
  Serial.println(WiFi.localIP());

  // Route pour les pages Web
  // pour mise à jour les variables sur le  (Sorties)(Nom,Opc,Test)
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/Nom", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", lec_nom().c_str());
  });
  server.on("/Ocp", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", lec_ocp().c_str());
  });

  server.on("/test", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", lec_test().c_str());
  });

  // pour mise à jour les botton (entree)
  server.on("/p_entree", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite(led_1, HIGH);
    delay(2000);
    digitalWrite(led_1, LOW);
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/p_sortie", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite(led_2, HIGH);
    delay(2000);
    digitalWrite(led_2, LOW);
    request->send_P(200, "text/html", index_html, processor);
  });


  server.onNotFound(notFound);
  // Init Server
  server.begin();
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  // Init les led sur etat Bass pour garantizer qui sont desallumnes despues l'init
  digitalWrite(led_1, LOW);
  digitalWrite(led_2, LOW);


}

void loop()
{
  //RFID Lecture
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      Serial.println(" ");
      Serial.println("Carte Trouvé");
      Serial.println(" ");
      Serial.println("Nombre Carte:");
      Serial.print("Dec: ");
      Serial.print(rfid.serNum[0], DEC);
      Serial.print(", ");
      Serial.print(rfid.serNum[1], DEC);
      Serial.print(", ");
      Serial.print(rfid.serNum[2], DEC);
      Serial.print(", ");
      Serial.print(rfid.serNum[3], DEC);
      Serial.print(", ");
      Serial.print(rfid.serNum[4], DEC);
      Serial.println(" ");
      // Différenciation des cartes
      if (rfid.serNum[0] == u1_0
          && rfid.serNum[1] == u1_1
          && rfid.serNum[2] == u1_2
          && rfid.serNum[3] == u1_3
          && rfid.serNum[4] == u1_4) {

        Serial.println("Portable FIZET");

        nom = "Bienvenue Carlos Figueroa";
        ocp = "Etudiant";
        //*
        temp_init_milis = millis();
        ///Acction
        digitalWrite(led_1, HIGH);
        ///
        while (millis() < temp_init_milis + temp_milis) {
          // atteindre [temp_milis] milisegundos
        }
        digitalWrite(led_1, LOW);
        //*

      }

      //////////////////////////////////////////////
      if (rfid.serNum[0] == u2_0
          && rfid.serNum[1] == u2_1
          && rfid.serNum[2] == u2_2
          && rfid.serNum[3] == u2_3
          && rfid.serNum[4] == u2_4) {


        Serial.println("NFC PORTE-CLES ");
        nom = "Bienvenue Lamah Severin";
        ocp = "Etudiant";
        //*
        temp_init_milis = millis();
        ///Acction
        digitalWrite(led_1, HIGH);
        ///
        while (millis() < temp_init_milis + temp_milis) {
          // Atteindre [temp_milis] milisegundos
        }
        digitalWrite(led_1, LOW);
        //*
      }
      /////////////////////////////////////////////
      if (rfid.serNum[0] == u3_0
          && rfid.serNum[1] == u3_1
          && rfid.serNum[2] == u3_2
          && rfid.serNum[3] == u3_3
          && rfid.serNum[4] == u3_4) {
        Serial.println("NFC CARTE");
        nom = "Bienvenue Roberto Zetina";
        ocp = "Directeur";

        //*
        temp_init_milis = millis();
        ///Accion
        digitalWrite(led_1, HIGH);
        ///
        while (millis() < temp_init_milis + temp_milis) {
          //  Atteindre [temp_milis] milisegundos
        }
        digitalWrite(led_1, LOW);
        //*
      }
      //////////////////////////////////////////////


    }
  }
  else {
    // Quand Il n'ai pas de carte ,il ne affeche pas rien
    nom = "";
    ocp = "";
  }
  rfid.halt(); //Boucle RFID
  nomva = random(1, 50); //Nombre Variable pour garantizer qui'il existe une bonne conecction

}
