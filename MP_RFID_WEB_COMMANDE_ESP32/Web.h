#include <ESPAsyncWebServer.h>
// Init server sur porte 80
AsyncWebServer server(80);
//Page Web sur html et css
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
<title>FIZET ACCESS IUT</title>
<link rel="icon" type="image/png" href="https://www.google.com/s2/favicons?domain=iut-longwy.univ-lorraine.fr" />
<p><img style="display: block; margin-left: auto; margin-right: auto;" src="https://iut-longwy.univ-lorraine.fr/files/2019/05/cropped-logoUL_IUT_Longwy-e1558691625952-1.png" alt="Smiley face" width="470" height="110" /></p>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: 'Times New Roman', serif;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 2.5rem; }
    p { font-size: 2.5rem; }
  </style>
</head>
<body>
  <h2><span style="background-color: #339966;">FI</span>Z<span style="background-color: #ff0000;">ET</span> MX-FR</h2>
  <p>
    <i class="fas fa-address-card" style="color:#059e8a;"></i> 
    <span id="Nom">%Nom%</span>
  </p>
  <p>
    <i class="fas fa-user-tie" style="color:#000000;"></i>
    <span id="Ocp">%Ocp%</span>
  </p>
  <p>
    <i class="fas fa-satellite-dish" style="color:#000000;"></i>
    <span id="test">%test%</span>
  </p>
<table style="height: 61px; margin-left: auto; margin-right: auto;">
<tbody>
<tr style="height: 18px;">
<td style="height: 18px; width: 162px; text-align: right;"><strong>PERMETTRE</strong></td>
<td style="height: 18px; width: 171px; text-align: left;"><strong>LE PASSAGE</strong></td>
</tr>
<tr style="height: 18px;">
<td style="height: 18px; width: 162px; text-align: center;">PORTE ENTREE</td>
<td style="height: 18px; width: 171px; text-align: center;">PORTE SORTIE</td>
</tr>
<tr style="height: 25px;">
<td style="height: 25px; width: 162px; text-align: center;"><a href="/p_entree"><button>Ouvrir la porte Entree</button></a></td>
<td style="height: 25px; width: 171px; text-align: center;"><a href="/p_sortie"><button>Ouvrir la porte Sortie</button></a></td>
</tr>
</tbody>
</table>
<a href="https://iut-longwy.univ-lorraine.fr/">Visit Site WEB Henri Poincare IUT Longwy</a>
</body>
<script>
// Script pour mise a jour les donnes 
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("Nom").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/Nom", true);
  xhttp.send();
}, 1000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("Ocp").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/Ocp", true);
    xhttp.send();
}, 1000 ) ;
  // Verification de marche
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("test").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/test", true);
    xhttp.send();
}, 5000 ) ;  
</script>
</html>)rawliteral";
//en cas qui'il ne existe pas la page donne un message de error "Not Found
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
