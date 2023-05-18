#include <SoftwareSerial.h>
#include <DHT11.h>
DHT11 DHT;
#define DHT11_PIN 5
SoftwareSerial bluetooth(10, 11);
void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  DHT.read(DHT11_PIN);
  Serial.print("온:");
  Serial.print(DHT.temperature);
  Serial.print("  습:");
  Serial.println(DHT.humidity);
  bluetooth.print("온도 : ");
  bluetooth.print(DHT.temperature);
  bluetooth.println("℃");
  bluetooth.print("습도 : ");
  bluetooth.println(DHT.humidity);


  delay(1000);
}