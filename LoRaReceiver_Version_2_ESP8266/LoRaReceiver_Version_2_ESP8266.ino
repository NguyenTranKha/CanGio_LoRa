#include <SPI.h>
#include <LoRa.h>
void setup() {
  // put your setup code here, to run once:
  LoRa.setSpreadingFactor(12); 
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);
  LoRa.setTxPower(20,1);
  LoRa.enableCrc();
  LoRa.setSyncWord(0x69);
  Serial.begin(9600);
  while (!Serial);
  LoRa.setPins(10,2,4);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(868E6)) {
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
  
  if(st.length() != 0)
  { 
    Serial.println(st);
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
