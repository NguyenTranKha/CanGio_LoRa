#include <SPI.h>
#include <LoRa.h>
#include "TinyGPS++.h"
#include <SoftwareSerial.h>


int counter = 0;
static const int RXPin = A3, TXPin = 3;
static const uint32_t GPSBaud = 9600;
char ln[50];
char lt[50];

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

void setup() {
  pinMode(9, OUTPUT);
  LoRa.setPins(10,2,4);
  Serial.begin(115200);
  ss.begin(GPSBaud);
  Serial.println("LoRa Sender");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  String st;
  dtostrf(gps.location.lat(),9,6,lt);
  dtostrf(gps.location.lng(),11,7,ln);
  st += "ID1: ";
  st += (String)lt +" "+ (String)ln;
  Serial.println(st);
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print(st);
  LoRa.endPacket();
  digitalWrite(9, HIGH);
  delay(100);
  digitalWrite(9, LOW);

  counter++;
  smartDelay(1000);
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
