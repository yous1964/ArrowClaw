// Color Sensor
#include "Wire.h"
#include "Adafruit_TCS34725.h"

#include <ESP32Servo.h>
 
// Servo Motor
Servo myservo;
int servoPin = 17;
int potPin = 34;        
int ADC_Max = 4096;
int val;

// Ultrasonic Sensors
#define SOUND_SPEED 0.034
const int trigPinA = 16;
const int echoPinA = 4;
const int trigPinB = 0;
const int echoPinB = 2;
long duration;
float distanceCm;


Adafruit_TCS34725 tcs = Adafruit_TCS34725(700, TCS34725_GAIN_1X);


void setup(void) {
  Serial.begin(115200);
  // Color Sensor
  if (tcs.begin()) {
    Serial.println("Found sensor");

  } else {
    Serial.println("No TCS34725 found ... check your connections");
    //while (1);
  }


  // Servo
  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);// Standard 50hz servo
  myservo.attach(servoPin, 500, 2400);
  
  // Ultrasonic sensor
  pinMode(trigPinA, OUTPUT);
  pinMode(echoPinA, INPUT);
  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinB, INPUT);

  Serial.println("Milis - ColorTemp - Lux - R - G - B - C - Pot - UsensA - UsensB\n");

}





void loop(void) {
  unsigned long currentMillis = millis();

  // Servo
  val = analogRead(potPin);
  val = map(val, 0, ADC_Max, 0,           180);
  myservo.write(val);





  uint16_t r, g, b, c, colorTemp, lux; 
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);


  Serial.print(millis()); // Miliseconds
  Serial.print(" ");
  
  Serial.print(colorTemp); // Color Temperature
  Serial.print(" ");


  Serial.print(lux); // Lux
  Serial.print(" ");

  Serial.print(r); // R
  Serial.print(" ");

  Serial.print(g); // G
  Serial.print(" ");

  Serial.print(b); // B
  Serial.print(" ");

  Serial.print(c); // C
  Serial.print(" ");


  Serial.print(val); // Pot
  Serial.print(" ");


  // Ultrasonic Sensor A
  digitalWrite(trigPinA, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinA, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinA, LOW);
  duration = pulseIn(echoPinA, HIGH);
  distanceCm = duration * SOUND_SPEED/2;

  Serial.print(distanceCm);
  Serial.print(" ");


  // Ultrasonic Sensor B
  digitalWrite(trigPinB, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinB, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinB, LOW);
  duration = pulseIn(echoPinB, HIGH);
  distanceCm = duration * SOUND_SPEED/2;

  Serial.print(distanceCm);
  Serial.println(" ");


}
