#include <SPI.h>
#include <LoRa.h>
#include <ESP8266WiFi.h>

String apiKey = "PU38Y7KTF84QE4WY";
const char *ssid =  "UIT Public";
const char *pass =  "";
const char *server = "api.thingspeak.com";

void setup() {
  LoRa.setSpreadingFactor(12);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);
  LoRa.enableCrc();
  Serial.begin(115200);
  while (!Serial);
  LoRa.setPins(15,16,5);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
       
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
  Serial.println("");
  Serial.println("WiFi connected");
      
  Serial.println("LoRa Receiver");
  
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}


void loop() {
  // try to parse packet
  String st;
  int packetSize = LoRa.parsePacket();
  while (!packetSize) {
    packetSize = LoRa.parsePacket();
  }
  while (LoRa.available()) {
      st += (String)(char)LoRa.read();
  }
  Serial.println(st);
  WiFiClient client;
  if(client.connect(server, 80))
   {
      String postStr = apiKey;
      postStr +="&field1=";
      //postStr += (String)st;
      //postStr += " with RSSI ";
      postStr += (String)LoRa.packetRssi();
      
      client.print("POST /update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(postStr.length());
      client.print("\n\n");
      client.print(postStr);

      Serial.println("%. Send to Thingspeak.");
   }
   client.stop();
}
