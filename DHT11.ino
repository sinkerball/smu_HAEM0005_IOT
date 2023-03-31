/*
DHT11

This example reads a DHT11 sensor hooked up on pin D7. Reads both
temperature and humidity and sends it to the Serial port

created in Feb 2019 by D. Cuartielles
based on work by F. Vanzati (2011) and M. Loglio (2013)

This example code is in the public domain.
*/

// include the EduIntro library
#include <EduIntro.h>

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600); 
}
void loop() {
  delay(2000);
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  Serial.print("Humidity: ");  Serial.print(h);
  Serial.print(" %\t");         Serial.print("Temperature: ");
  Serial.print(t);                 Serial.println(" C");
}
