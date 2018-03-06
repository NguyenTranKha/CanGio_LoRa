#include <SPI.h>
#include <LoRa.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600 );
  while (!Serial);
  LoRa.setPins(15,16,5);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  String st;
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
      while (LoRa.available()) {
      st += (String)(char)LoRa.read();
    }
  }
  if(st.length() != 0) Serial.println(st);
}
