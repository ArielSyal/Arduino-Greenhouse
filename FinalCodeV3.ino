//Ariel Syal
//705163
//TER3M0
//Mr.Chauhan
//1/19/2023

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_NeoPixel.h>
 
#define LED_PIN 6
Adafruit_NeoPixel jewel = Adafruit_NeoPixel(7, LED_PIN, NEO_GRB + NEO_KHZ800);
 
LiquidCrystal_I2C lcd(0x27, 16, 2); //initialize lcd with i2c address and lcd size
const int soilPin = A0; //soil moisture sensor pin
int soilValue;
const int tempPin = 2; //temperature sensor pin
OneWire oneWire(tempPin); //initialize OneWire communication
DallasTemperature sensors(&oneWire); //initialize DallasTemperature library
float tempC;
const int relayPin = 13; //relay pin
const int motorPin = 9; //motor pin
const int soilThreshold = 500; //set soil moisture threshold value
bool relayStatus = false; //initialize relay status as off
const int tempThreshold = 21; //set temperature threshold value
 
void setup() {
  jewel.begin();
  for(int i = 0; i < 7; i++) {
    jewel.setPixelColor(i, 255, 255, 0); //set all lights to yellow (sun)
  }
  jewel.show();
 
  lcd.init(); //initialize lcd
  lcd.backlight(); //turn on lcd backlight
  pinMode(soilPin, INPUT); //set soil moisture sensor pin as input
  sensors.begin(); //start temperature sensor communication
  pinMode(relayPin, OUTPUT); //set relay pin as output
  pinMode(motorPin, OUTPUT); //set motor pin as output
  digitalWrite(relayPin, LOW); //initialize relay as off
  digitalWrite(motorPin, LOW);
}
 
void loop() {
  soilValue = analogRead(soilPin); //read soil moisture sensor value
  sensors.requestTemperatures(); //request temperature from sensor
  tempC = sensors.getTempCByIndex(0); //get temperature in Celsius
  lcd.clear(); //clear lcd
  lcd.print("Ariel's");
  lcd.setCursor(0, 1); //move cursor to second line
  lcd.print("Greenhouse");
  delay(2000);
  lcd.clear(); //clear lcd
  lcd.print("Soil Moisture:"); //print "Soil Moisture:" on first line
  lcd.setCursor(0, 1); //move cursor to second line
  lcd.print(soilValue); //print soil moisture sensor value
  delay(1000);
  lcd.clear();
  lcd.print("Temperature:"); //print "Temperature:" on first line
  lcd.setCursor(0, 1); //move cursor to second line
  lcd.print(tempC); //print temperature value
  delay(1000);
 
  if(soilValue > soilThreshold) { //if soil moisture is less than threshold
      digitalWrite(relayPin, HIGH);
    for(int i = 0; i < 7; i++) {
      jewel.setPixelColor(i, 0, 255, 255); //change color of all lights to blue (Watering)
    }
    jewel.show();
    lcd.clear();
    lcd.print("Watering..."); //print "Watering..." on the first line 
    delay(5000); //wait for 5 seconds
    for(int i = 0; i < 7; i++) {
      jewel.setPixelColor(i, 255, 255, 0); //set all lights to yellow (sun)
    }
    jewel.show();
    digitalWrite(relayPin, LOW); //turn off relay 
  }
 
  if(tempC > tempThreshold) { //if temperature is above threshold
    digitalWrite(motorPin, HIGH); //turn on motor
    lcd.clear();
    lcd.print("Motor On..."); //print "Motor On..." on the first line 
    delay(1000);//wait one second 
  } else {
    digitalWrite(motorPin, LOW); //turn off motor
  }
}


