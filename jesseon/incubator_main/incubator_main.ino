/***************************************************
  This is an test case to look at the function of the temperature
  sensor when the entire

  Designed specifically to work with the SHT31-D sensor from Adafruit
  ----> https://www.adafruit.com/products/2857

  These sensors use I2C to communicate, 2 pins are required to
  interface

  Wired the SHT31-D to the Arduino following the first diagram here:
  http://cactus.io/hookups/sensors/temperature-humidity/sht31/hookup-arduino-to-sensirion-sht31-temp-humidity-sensor

  Connect the LED strip to the gate following the diagram in the Cloud-based Lab Monitor google doc:
  Power Supply - to breadboard minus rail
  Power Supply + to LED strip red wire
  LED strip black wire to gate middle pin

  The small LED does not light up because when the humidity sensor is connected, the Arduino 
  does not have enough power to power it.
 ****************************************************/

#include "Adafruit_SHT31.h"

// User input constants
const int desiredTemp = 22.0;

const int fan = 3;  // we just run the fans constantly with no input or output, as Danny did
const int lights = 4;
const int peltier = 5;

int ledState = LOW;
int peltierState = LOW;

unsigned long previousMillis = 0;

Adafruit_SHT31 sht31 = Adafruit_SHT31(); // name the temp sensor

void setup() {

  /*
    Set the pins which are attached to other devices to output to
    prevent a floating pin which can casues issues

  */
  pinMode(fan, OUTPUT);
  pinMode(lights, OUTPUT);
  pinMode(peltier, OUTPUT);

  Serial.begin(9600);
  
  /* set up temp sensor */
  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }
  
  Serial.println("setup successful");
}

unsigned long getCurrentTime() {
  // TODO replace this with getting the time from the real time clock
  return millis();
}

void printCurrentInfo(unsigned long currentTime,float currentTemp) {
  Serial.print("Current Time = "); 
  Serial.println(currentTime);
  
  Serial.print("Temp *C = "); 
  Serial.println(currentTemp);

  float humidity = sht31.readHumidity();
  Serial.print("Hum. % = "); 
  Serial.println(humidity);
}

void adjustPeltier(float currentTemp) {
  // TODO replace with a smarter algorithm, use PID like Danny
  if (currentTemp > desiredTemp && peltierState == LOW) {
    peltierState = HIGH;
    Serial.println("Current temperature " + String(currentTemp) + " is higher than desired temperature " + String(desiredTemp) + ", turning Peltier cooler on");
    digitalWrite(peltier, peltierState);
  }
  if (currentTemp < desiredTemp && peltierState == HIGH) {
    peltierState = LOW;
    Serial.println("Current temperature " + String(currentTemp) + " is lower than desired temperature " + String(desiredTemp) + ", turning Peltier cooler off");
    digitalWrite(peltier, peltierState);
  }
}

void adjustLight() {
  // TODO change this to a 16hr on, 8hr off cycle
  // if the LED is off turn it on and vice-versa:
  if (ledState == LOW) {
    ledState = HIGH;
    Serial.println("turning LED on");
  } else {
    ledState = LOW;
    Serial.println("turning LED off");
  }
}

void loop() {
  unsigned long currentTime = getCurrentTime();
  float currentTemp = sht31.readTemperature();
  printCurrentInfo(currentTime, currentTemp);

  adjustPeltier(currentTemp);
  adjustLight();

  delay(2000);
}
