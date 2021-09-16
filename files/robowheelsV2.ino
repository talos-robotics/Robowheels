 
#include <SharpIR.h>
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

// ΜΕΤΑΒΛΗΤΕΣ ΓΙΑ ΤΟ ΑΡΙΣΤΕΡΟ ΜΟΤΕΡ
byte directionPin = 10;
byte stepPin = 9;
byte enablePin = 8;
int numberOfSteps = 20;
int millisbetweenSteps = 0;

//ΜΕΤΑΒΛΗΤΕΣ ΓΙΑ ΤΟ ΔΕΞΙ ΜΟΤΕΡ
byte directionPin_R = 7;
byte stepPin_R = 6;
byte enablePin_R = 5;
int numberOfSteps_R = 20;

int distance1;
int distance2;

SharpIR sensor1 ( SharpIR:: GP2Y0A21YK0F, A0);
SharpIR sensor2 ( SharpIR:: GP2Y0A21YK0F, A1);

Adafruit_MMA8451 mma = Adafruit_MMA8451();

void setup() {

Serial.begin(9600);

//ΑΡΧΙΚΟΠΙΟΙΣΗ ΚΑΙ ΕΝΕΡΓΟΠΙΟΙΣΗ PINS ΑΡΙΣΤΕΡΟΥ ΜΟΤΕΡ
pinMode(directionPin, OUTPUT);
pinMode(stepPin, OUTPUT);
pinMode(enablePin, OUTPUT);

digitalWrite(enablePin, HIGH);
digitalWrite(directionPin, HIGH);

//ΑΡΧΙΚΟΠΙΟΙΣΗ ΚΑΙ ΕΝΕΡΓΟΠΙΟΙΣΗ PINS ΔΕΞΙΟΥ ΜΟΤΕΡ
pinMode(directionPin_R, OUTPUT);
pinMode(stepPin_R, OUTPUT);
pinMode(enablePin_R, OUTPUT);

digitalWrite(enablePin_R, HIGH);
digitalWrite(directionPin_R, HIGH);
delay(100);


 Serial.println("Adafruit MMA8451 test!");
  

  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  

}


void loop() {

// Διαβαζουμε τις τιμες του αισθητηρα mma8451
   mma.read();
  Serial.print("X:\t"); Serial.print(mma.x); 
  Serial.print("\tY:\t"); Serial.print(mma.y); 
  Serial.println();

 distance1 = sensor1.getDistance();
 distance2 = sensor2.getDistance();

Serial.print(distance1);
Serial.print(" , ");
Serial.println(distance2);
 

// ελεγχουμε τις συνθηκες για να παει το μοτερ μπροστα
 
if (distance1 >= 40 and distance2 <= 15 && mma.y >= 1800) {
Serial.print("ΜΟΤΕΡ 1 ON");
digitalWrite(directionPin_R, LOW);
digitalWrite(directionPin, HIGH);

do
{

Serial.print("ΜΟΤΕΡ 1 ON ΜΠΡΟΣΤΑ");
digitalWrite(stepPin, HIGH);
digitalWrite(stepPin, LOW);
digitalWrite(stepPin_R, HIGH);
digitalWrite(stepPin_R, LOW);
//delay(millisbetweenSteps);
mma.read();
 distance1 = sensor1.getDistance();
 distance2 = sensor2.getDistance();
}while(distance1 < 40 and distance2 > 15 && mma.y < 1800);
 
 //delay(1); 

}

// ελεγχουμε τις συνθηκες για να παει το μοτερ πισω
if (distance1 >= 40 and distance2 <= 15 && mma.y <= -1800) {
Serial.print(numberOfSteps);

digitalWrite(directionPin_R, HIGH);
digitalWrite(directionPin, LOW);

do
{

Serial.print("ΜΟΤΕΡ 1 ON πισω");
digitalWrite(stepPin, HIGH);
digitalWrite(stepPin, LOW);
digitalWrite(stepPin_R, HIGH);
digitalWrite(stepPin_R, LOW);
//delay(millisbetweenSteps);
mma.read();
 distance1 = sensor1.getDistance();
 distance2 = sensor2.getDistance();
}while(distance1 > 40 and distance2 > 15 && mma.y > -1800);
 //delay(1); 

}
//ελεγχουμε τις συνθηκες για να στριξει το μοτερ δεξια
if (distance1 >= 40 and distance2 <= 15 && mma.x >= 1400) {
Serial.print(numberOfSteps);

digitalWrite(directionPin_R, HIGH);
digitalWrite(directionPin, HIGH);

do
{

Serial.print("ΜΟΤΕΡ 1 ON δεξια");
digitalWrite(stepPin, HIGH);
digitalWrite(stepPin, LOW);
digitalWrite(stepPin_R, HIGH);
digitalWrite(stepPin_R, LOW);
//delay(millisbetweenSteps);
mma.read();
 distance1 = sensor1.getDistance();
 distance2 = sensor2.getDistance();
}while(distance1 < 40 and distance2 > 15 && mma.x < 1400);
 //delay(1); 

}

// ελεγχουμε τις συνθηκες για να παει το μοτερ αριστερα
if (distance1 >= 40 and distance2 <= 15 && mma.x <= -1400) {
Serial.print(numberOfSteps);

digitalWrite(directionPin_R, LOW);
digitalWrite(directionPin, LOW);

do
{

Serial.print("ΜΟΤΕΡ 1 ON αριστερα");
digitalWrite(stepPin, HIGH);
digitalWrite(stepPin, LOW);
digitalWrite(stepPin_R, HIGH);
digitalWrite(stepPin_R, LOW);
//delay(millisbetweenSteps);
mma.read();
 distance1 = sensor1.getDistance();
 distance2 = sensor2.getDistance();
}while(distance1 < 40 and distance2 > 15 && mma.x > -1400);
 
 //delay(1); 

}

//Σε περιπτωση αδιεξοδου
if (distance1 < 40 or distance2 > 15) {

digitalWrite(directionPin_R, HIGH);
digitalWrite(directionPin, HIGH);

do
{

Serial.println("ΜΟΤΕΡ 1 ON δεξια αδιεξοδο");
digitalWrite(stepPin, HIGH);
digitalWrite(stepPin, LOW);
digitalWrite(stepPin_R, HIGH);
digitalWrite(stepPin_R, LOW);
//delay(millisbetweenSteps);
 distance1 = sensor1.getDistance();
 distance2 = sensor2.getDistance();
}while(distance1 < 40 or distance2 > 15);
 //delay(1); 

}




}
