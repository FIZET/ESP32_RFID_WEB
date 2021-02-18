/// Libreries de RFID
#include <SPI.h>
#include <RFID.h>
//Parametres de  configuration de pin pour RFID
#define SS_PIN 21
#define RST_PIN 22

RFID rfid(SS_PIN, RST_PIN);

// Cartes de person

// NFC FIZET
int u1_0 = 1;
int u1_1 = 2;
int u1_2 = 3;
int u1_3 = 4;
int u1_4 = 4;
//NFC PORTE CLE
int u2_0 = 217;
int u2_1 = 183;
int u2_2 = 211;
int u2_3 = 177;
int u2_4 = 12;

//NFC CARTE
int u3_0 = 9;
int u3_1 = 105;
int u3_2 = 22;
int u3_3 = 179;
int u3_4 = 197;

String nom; // nom et premon de Accesor
String ocp; //ocupation de person
String nomva; // ce une variable pour salver un nombre aleatorio
