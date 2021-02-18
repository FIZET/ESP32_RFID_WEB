//accès aux conteneurs
//%lec_nom%
//%lec_opc%
//%lec_test%

// Pin pour allumer les LEDS
const int led_1 = 32;
const int led_2 = 12;
//Functiones pour returner le valeur de Variable
String lec_nom() {
  String nom1 = nom;
  return String(nom1);
}
String lec_ocp() {
  String ocp1 = ocp;
  return String(ocp1);
}
String lec_test() {
  String test1 = nomva;
  return String(test1);
}

// Remplacer le placeholder par des valeurs
String processor(const String& var) {
  if (var == "Nom") {
    return lec_nom();
  }
  else if (var == "Ocp") {
    return lec_ocp();
  }
  else if (var == "test") {
    return lec_test();
  }
  return String();
}
