#include <ArduinoJson.h>
#include "Arduino.h"
#include <WiFi.h>
#include <WiFiClient.h> 
#include <ESP32_FTPClient.h>

const char* ssid = "Redmi 8";
const char* password = "patorulo";
char ftp_server[] = "192.168.43.86";
char ftp_user[]   = "esp32";
char ftp_pass[]   = "yanuro11";
char escrito[200]; 
double valueTemp=0;

ESP32_FTPClient ftp (ftp_server,ftp_user,ftp_pass, 5000, 2);




void setup() {
  DynamicJsonDocument doc(2000); 
  Serial.begin(115200);

    WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi..");
  }

  Serial.println(WiFi.localIP());


  ftp.OpenConnection();

  // crear archivo json
  
  doc["Sensor"] = "Termometro";
  JsonArray data = doc.createNestedArray( "Cel");   
  for(int i=0;i<10;i++){
    valueTemp=random(0,25);    
    data.add(valueTemp); 
    delay(500);
  }

  serializeJsonPretty(doc, escrito);
  ftp.InitFile("Type A");
  ftp.NewFile("temperatura.json"); 
  ftp.Write(escrito);
  //ftp.ChangeWorkDir("Redes de sensores");   // directorio a guardar
  ftp.CloseFile();



  }

void loop() {

}
