#include <WiFi.h> //libreria para conectar ESP32 con wifi
#include "time.h"//libreria para sacar el tiempo

const char* ssid       = "Redmi 8";//nombre de red
const char* password   = "patorulo";//contraseña de red

const char* ntpServer = "pool.ntp.org";//direccion de NTP global, europa europe.pool.ntp.org
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;//si hay cambio de hora

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S"); //para escribir la hora
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
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);//obtiene la hora
  printLocalTime();//escribe la hora

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop()
{
  delay(1000);
  printLocalTime();
}