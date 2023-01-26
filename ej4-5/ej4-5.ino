#include <WiFi.h> //libreria para conectar ESP32 con wifi
#include "time.h"//libreria para sacar el tiempo



const uint16_t puerto=23;
const char * host = "192.168.43.86";
const char* ssid       = "Redmi 8";//nombre de red
const char* password   = "patorulo";//contraseña de red
tm timeinfo;
const char* ntpServer = "pool.ntp.org";//direccion de NTP global, europa europe.pool.ntp.org
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;//si hay cambio de hora
boolean envio = false;
String opcion;
WiFiClient client;

void recibeData(){
  if (client){                      //client devuelve un valor booleano True si esta conectado
    if (client.available()>0) {
    opcion = client.readStringUntil('\n');
  }
}
}

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  client.println(&timeinfo, "%A, %B %d %Y %H:%M:%S"); //para escribir la hora
  //dia de la semana, mes, dia del mes, año, hora, minuto, segundo
}


void setup()
{
  Serial.begin(115200);

  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");//conecta a la red wifi
  }

  Serial.println(" CONNECTED");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

Serial.print("Conectando a Hercules");
  while (!client.connect(host, puerto)) {
        Serial.print(".");
        delay(1000);
    }

 client.println("Aqui ESP32");
  
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);//obtiene la hora

}


void loop()
{
  recibeData();
  if (opcion.startsWith("start")) {
    envio=true;
}
  if (opcion.startsWith("stop")) {
    envio=false;
      }
  if (envio) {
  printLocalTime();
   delay(1000);
}
}
