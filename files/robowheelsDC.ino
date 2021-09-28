 
#include <SharpIR.h>
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <L298N.h>


// ΜΕΤΑΒΛΗΤΕΣ ΓΙΑ ΤΟ ΑΡΙΣΤΕΡΟ ΜΟΤΕΡ
const unsigned int IN3 = 10;
const unsigned int IN4 = 11;
const unsigned int EN2 = 12;

//ΜΕΤΑΒΛΗΤΕΣ ΓΙΑ ΤΟ ΔΕΞΙ ΜΟΤΕΡ
const unsigned int IN1 = 7;
const unsigned int IN2 = 8;
const unsigned int EN = 9;

// Create one motor instance
L298N motor(EN, IN1, IN2);
L298N motor2(EN2, IN3, IN4);


int distance1;
int distance2;

SharpIR sensor1 ( SharpIR:: GP2Y0A21YK0F, A0);
SharpIR sensor2 ( SharpIR:: GP2Y0A21YK0F, A1);

Adafruit_MMA8451 mma = Adafruit_MMA8451();

void setup() {

Serial.begin(9600);


motor.setSpeed(255);
motor2.setSpeed(255);

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
 
if (distance1 >= 40 and distance2 <= 35 && mma.y >= 1800) {

Serial.print("ΜΟΤΕΡ 1 μπροστα");

 motor.forward();
 motor2.forward();
 

}

// ελεγχουμε τις συνθηκες για να παει το μοτερ πισω
if (distance1 >= 40 and distance2 <= 35 && mma.y <= -1800) {

Serial.print("ΜΟΤΕΡ 1 ON ΠΙΣΩ");
motor.backward();
motor2.backward();

}
//ελεγχουμε τις συνθηκες για να στριξει το μοτερ δεξια
if (distance1 >= 40 and distance2 <= 35 && mma.x >= 1400) {

Serial.print("ΜΟΤΕΡ 1 ΔΕΞΙΑ");
motor.forward();
motor2.backward();
}
 

// ελεγχουμε τις συνθηκες για να παει το μοτερ αριστερα
if (distance1 >= 40 and distance2 <= 35 && mma.x <= -1400) {

Serial.print("ΜΟΤΕΡ 1 ON ΑΡΙΣΤΕΡΑ");
 motor.backward();
 motor2.forward();

}

if ((mma.x > -300 and mma.x <  300) or (mma.y > 300 and mma.y < 300)) {

 Serial.print("ΜΟΤΕΡ 1 ON stop");
 motor.stop();
 motor2.stop();

}

if (distance2 > 35) {

  do{
  motor.backward();
  motor2.backward();
  distance2 = sensor2.getDistance();
  }while(distance2 > 35);
 motor.stop();
 motor2.stop();
}


if (distance1 < 40) {

 do{
 motor.forward();
 motor2.backward();
 distance1 = sensor1.getDistance();
 }while(distance1 < 40);
 motor.stop();
 motor2.stop();
}

}
