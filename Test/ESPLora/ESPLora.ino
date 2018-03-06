#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>
#include "TinyGPS++.h"
TinyGPSPlus gps;
char ln[50];
char lt[50];
SoftwareSerial ss(3,1);

String apiKey = "PU38Y7KTF84QE4WY";
const char *ssid =  "Redmi 4A";     // replace with your wifi ssid and wpa2 key
const char *pass =  "21071997";
const char *server = "api.thingspeak.com";

void setup()
{
  Serial.begin(9600);
  Serial.swap();
       delay(10);
 
       WiFi.begin(ssid, pass);
       
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
     } 
     delay(1000);
     ss.begin(9600);
}

void loop()
{
   dtostrf(gps.location.lat(),9,6,lt);
   dtostrf(gps.location.lng(),11,7,ln);
   delay(1000);
   WiFiClient client;
   if(client.connect(server, 80))
   {
      String postStr = apiKey;
      postStr +="&field1=";
      postStr += String(lt)+","+String(ln);
      
      client.print("POST /update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(postStr.length());
      client.print("\n\n");
      client.print(postStr);
   }
   client.stop();
   
}
