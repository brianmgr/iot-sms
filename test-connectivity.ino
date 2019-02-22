
#include <SPI.h>
#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"
 
#define FONA_TX 11
#define FONA_RX 10
#define FONA_RST 4
 
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
 
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);
 
void setup() {
  Serial.begin(115200);
  Serial.println("Signal test");
  Serial.println("Initializing..");
 
  fonaSS.begin(4800);
 
  if (! fona.begin(fonaSS)) {           
    Serial.println("Couldn't find FONA");
    while (1);
  }
  Serial.println("SIM800L is OK");
  delay(2000);
  
}
 
void loop() {
 
  uint8_t n = fona.getRSSI();
  int8_t r;
        
  Serial.print("RSSI="); 
  if (n == 0) r = -115;
  if (n == 1) r = -111;
  if (n == 31) r = -52;
  if ((n >= 2) && (n <= 30)) {
    r = map(n, 2, 30, -110, -54);
  }
        
  Serial.print(r);
  Serial.println(" dBm");
  Serial.println();
  uint8_t t = fona.getNetworkStatus();
  
  Serial.print("Netwrk status:"); 
  if (t == 0) Serial.println("Not registered");
  if (t == 1) Serial.println("Registered (home)");
  if (t == 2) Serial.println("Not registered (searching)");
  if (t == 3) Serial.println("Denied");
  if (t == 4) Serial.println("Unknown");
  if (t == 5) Serial.println("Registered roaming");

  delay(1000);
}
