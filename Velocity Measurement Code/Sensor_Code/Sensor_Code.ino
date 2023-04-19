/*
  IR Breakbeam sensor demo!
*/
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define LEDPIN 13
// Pin 13: Arduino has an LED connected on pin 13
// Pin 11: Teensy 2.0 has the LED on pin 11
// Pin  6: Teensy++ 2.0 has the LED on pin 6
// Pin 13: Teensy 3.0 has the LED on pin 13
#define SENSORPIN1 7
#define SENSORPIN2 8

// variables will change:
int sensorState2 = 0;         // variable for reading the pushbutton status
float timeFirstSensor;
float timeSecondSensor;
float delta_T;
float velocity;

int flag = 0;
bool lastSensor1 = false, lastSensor2 = false;


int sensorState1 = 0;

void setup() {
  lcd.begin(16, 2);
  // initialize the LED pin as an output:
  pinMode(LEDPIN, OUTPUT);
  // initialize the sensor pin as an input:
  pinMode(SENSORPIN1, INPUT);
  digitalWrite(SENSORPIN1, HIGH); // turn on the pullup
  pinMode(SENSORPIN2, INPUT);
  digitalWrite(SENSORPIN2, HIGH);

  Serial.begin(9600);
  lcd.print("Impact Test!");

}

void loop() {

  
  // read the state of the pushbutton value:
  sensorState2 = digitalRead(SENSORPIN2);
  sensorState1 = digitalRead(SENSORPIN1);
  // check if the sensor beam is broken
  // if it is, the sensorState is LOW:
  if (sensorState2 == LOW) {
    // turn LED on:
    digitalWrite(LEDPIN, HIGH);
  }
  else {
    // turn LED off:
    digitalWrite(LEDPIN, LOW);
  }
  if (sensorState1 == LOW) {
    // turn LED on:
    digitalWrite(LEDPIN, HIGH);
  }
  else {
    // turn LED off:
    digitalWrite(LEDPIN, LOW);
  }


  /*if (sensorState2 ) {
    Serial.println("Sensor 2 Unbroken");
    }
    if (sensorState1){
    Serial.println("Sensor 1 Unbroken");
    }
    */

  
  if (!sensorState1) {
    Serial.println("sensor 1 Broken");
    timeFirstSensor = micros();
    lastSensor1 = true;
    Serial.println(timeFirstSensor);
    //delay();
  }
  if (!sensorState2) {
    Serial.println("sensor 2 Broken");
    timeSecondSensor = micros();
    lastSensor2 = true;
    Serial.println(timeSecondSensor);

    delta_T = (timeSecondSensor - timeFirstSensor);
    velocity = (0.25 / delta_T) * (pow(10, 6));
    Serial.println("delta T:");
    Serial.println(delta_T);
    Serial.println("velocity:");
    Serial.println(velocity);
    lcd.setCursor(0, 1);
    lcd.print("Vel: ");
    lcd.print(velocity);
    lcd.print(" m/s");

    lastSensor1 = false;
    lastSensor2 = false;

  }
}