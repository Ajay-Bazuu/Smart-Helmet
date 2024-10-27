/*
nRF24L01    ESP32-S3
---------    ---------
   VCC   ---->  3.3V
   GND   ---->  GND
   CE    ---->  GPIO 4
   CSN   ---->  GPIO 5
   SCK   ---->  GPIO 15
   MOSI  ---->  GPIO 7
   MISO  ---->  GPIO 6

*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Define CE and CSN pins for ESP32-S3
RF24 radio(4, 5);  // CE on GPIO 4, CSN on GPIO 5

const byte address[6] = "00001";

void setup() {
  Serial.begin(115200);
  
  // Initialize SPI communication on ESP32-S3 with specified pins
  SPI.begin(15, 6, 7, 5);  // SCK=15, MISO=6, MOSI=7, CSN=5
  
  radio.begin();

  // Check if the nRF24L01 module is connected
  if (radio.isChipConnected()) {
    Serial.println("nRF24L01 is connected successfully!");
  } else {
    Serial.println("ERROR: nRF24L01 is NOT connected. Please check wiring.");
    while (true); // Stop further execution if the module is not connected
  }

  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.setChannel(119);  // Example of setting a higher channel
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    float dataReceived[32];
    radio.read(dataReceived, sizeof(dataReceived));
    Serial.println(dataReceived[0]);
    Serial.println(dataReceived[1]);
    Serial.println();
  } else {
    Serial.println("Not Available");
  }

  delay(200); // Delay to reduce serial output frequency
}
