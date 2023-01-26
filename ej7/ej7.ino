#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include <ESP32Time.h>
#include "time.h"//libreria para sacar el tiempo
// Replace with your network credentials
const char* ssid = "RSense";
//const char* password = "patorulo";
ESP32Time rtc(3600);
// Set LED GPIO
boolean reset;
int cuenta;
String hora;

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 000;
const int   daylightOffset_sec = 0;//si hay cambio de hora

// Crea servidor en el puerto 80
AsyncWebServer server(80);

String processor(const String& var){
  String hora2;
  if(var == "STATE"){
    if(reset){
      rtc.setTime(1, 02, 03, 17, 1, 2000);
      hora2=rtc.getTimeDate(true);
      reset=false;
      Serial.print(hora2);  //si se pulsa el boton se resetea la hora
    }
    else{
    hora2=rtc.getTimeDate(true);
    Serial.print(hora2);
  }
  return (hora2);
}
}


 
void setup(){

  Serial.begin(115200);
  
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  struct tm timeinfo;
    rtc.setTimeStruct(timeinfo);
     


  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }


  WiFi.begin(ssid);//, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi..");
  }

  Serial.println(WiFi.localIP());

  // Busca la pagina
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Ruta para archivo style.css 
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

    server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request){
    reset=true;    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  

  server.begin();
}
 
void loop(){
  delay(1000);
}
