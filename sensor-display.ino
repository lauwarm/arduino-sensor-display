#include "DHT.h"
#include "LiquidCrystal.h"

#define DHTPIN 13 // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // Sensor Type

DHT dht(DHTPIN, DHTTYPE);

// LiquidCrystal(RS, E, D4, D5, D6, D7):
LiquidCrystal lcd = LiquidCrystal(2, 3, 4, 5, 6, 7);

void setup() {
  Serial.begin(9600);

  dht.begin();
  
  lcd.begin(16, 2);
}

void loop() {
  float h = dht.readHumidity(); // read humidity
  float t = dht.readTemperature(); // read temperature

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  float hic = dht.computeHeatIndex(t, h, false); // calculte heat index in celsius

  Serial.print(h);
  Serial.print(",");
  Serial.print(t);
  Serial.print(",");
  Serial.print(hic);
  Serial.println("");

  // First Row
  lcd.setCursor(0, 0);
  lcd.print(F("Humidity: "));
  lcd.print(h);
  lcd.print("%");
  
  // Second Row
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.setCursor(9,1);
  lcd.print(hic);
  lcd.print((char)223);
  lcd.print("C");

  delay(5000);
}
