#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"
#include <SharpIR.h>
#include <Wire.h>

// ΜΕΤΑΒΛΗΤΕΣ ΓΙΑ ΤΟ ΑΡΙΣΤΕΡΟ ΜΟΤΕΡ
byte directionPin = 10;
byte stepPin = 9;
byte enablePin = 8;
int numberOfSteps = 20;
int millisbetweenSteps = 0;

//ΜΕΤΑΒΛΗΤΕΣ ΓΙΑ ΤΟ ΔΕΞΙ ΜΟΤΕΡ
byte directionPin_R = 4;
byte stepPin_R = 6;
byte enablePin_R = 5;
int numberOfSteps_R = 20;

int distance1;
int distance2;

SharpIR sensor1 ( SharpIR:: GP2Y0A21YK0F, A0);
SharpIR sensor2 ( SharpIR:: GP2Y0A21YK0F, A1);



/**        
  Connection
  Arduino    VoiceRecognitionModule
   2   ------->     TX
   3   ------->     RX
*/
VR myVR(2,3);    // 2:RX 3:TX, you can choose your favourite pins.

uint8_t records[7]; // save record
uint8_t buf[64];


int ret2;

#define mp    (0)
#define pi    (1)
#define de    (2)
#define ar    (3)
#define st    (4)  

/**
  @brief   Print signature, if the character is invisible, 
           print hexible value instead.
  @param   buf     --> command length
           len     --> number of parameters
*/
void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){
      Serial.write(buf[i]);
    }
    else{
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}


void setup()
{
  /** initialize */
  myVR.begin(9600);
  
  Serial.begin(115200);

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


   
 Serial.println("Elechouse Voice Recognition V3 Module\r\nControl LED sample");
  

    
  if(myVR.clear() == 0){
    Serial.println("Recognizer cleared.");
  }else{
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while(1);
  }
  
  if(myVR.load((uint8_t)mp) >= 0){
    Serial.println("mprosta");
  }
  
  if(myVR.load((uint8_t)pi) >= 0){
    Serial.println("opisthen");
  }

   if(myVR.load((uint8_t)de) >= 0){
    Serial.println("ena");
  }

   if(myVR.load((uint8_t)ar) >= 0){
    Serial.println("dio");
  }

   if(myVR.load((uint8_t)st) >= 0){
    Serial.println("stop");
  }
}

void loop()
{

 distance1 = sensor1.getDistance();
 distance2 = sensor2.getDistance();

if (distance1 >= 40 and distance2 <= 20)
{

}
  int ret;
  ret = myVR.recognize(buf, 50);
  if(ret>0){
    switch(buf[1]){
      case mp:{
        Serial.println("pao mprosta ");
        Serial.println(String(buf[1]));
        Serial.println(myVR.recognize(buf, 50));
        Serial.print(distance1);
        Serial.print(" , ");
        Serial.print(distance2);
        Serial.print(" *** ");
        if (distance1 >= 40 and distance2 <= 20) {
        Serial.println("ΜΟΤΕΡ 1 ON");
        digitalWrite(directionPin_R, LOW);
        digitalWrite(directionPin, HIGH);
        ret2 =0;
        int flag = 0;
        while(distance1 >= 40 and distance2 <= 20 and flag == 0)
        {
        Serial.println("ΜΟΤΕΡ 1 ON ΜΠΡΟΣΤΑ" + String(flag));
        digitalWrite(stepPin, HIGH);
        digitalWrite(stepPin, LOW);
        digitalWrite(stepPin_R, HIGH);
        digitalWrite(stepPin_R, LOW);
         ret2 = myVR.recognize(buf, 50);
        
         Serial.println("ret2=" + String(ret2));
         
          if (ret2>0 and buf[1]>3){
           flag=1;
           Serial.println("****************************************************");
          }
       
              
        distance1 = sensor1.getDistance();
        distance2 = sensor2.getDistance();
        }
 
          

        }
       
        break;
      }
      case pi:{
      
        Serial.println("pao piso");
        Serial.println(buf[1]);
        Serial.println(myVR.recognize(buf, 50));

        digitalWrite(directionPin_R, HIGH);
        digitalWrite(directionPin, LOW);
        ret2 =0;
        int flag = 0;
        while(flag == 0)
        {
        Serial.println("ΜΟΤΕΡ 1 ON πισω" + String(flag));
        digitalWrite(stepPin, HIGH);
        digitalWrite(stepPin, LOW);
        digitalWrite(stepPin_R, HIGH);
        digitalWrite(stepPin_R, LOW);
         ret2 = myVR.recognize(buf, 50);
      
         Serial.println("ret2=" + String(ret2));
          
          if (ret2>0 and buf[1]>3){
           flag=1;
           Serial.println("****************************************************");
          }
       
              
        distance1 = sensor1.getDistance();
        distance2 = sensor2.getDistance();
        }
        
        break;
    }
        case de:{
       
        Serial.println("pao deksia");
        Serial.println(buf[1]);
        Serial.println(myVR.recognize(buf, 50));

        digitalWrite(directionPin_R, HIGH);
        digitalWrite(directionPin, HIGH);
        ret2 =0;
        int flag = 0;
        while(flag == 0)
        {
        Serial.println("ΜΟΤΕΡ 1 ON δεξια" + String(flag));
        digitalWrite(stepPin, HIGH);
        digitalWrite(stepPin, LOW);
        digitalWrite(stepPin_R, HIGH);
        digitalWrite(stepPin_R, LOW);
         ret2 = myVR.recognize(buf, 50);
        
         Serial.println("ret2=" + String(ret2));
          
          if (ret2>0 and buf[1]>3){
           flag=1;
           Serial.println("****************************************************");
          }
       
              
        distance1 = sensor1.getDistance();
        distance2 = sensor2.getDistance();
        }
        
        break;
    }
        case ar:{
       
        Serial.println("pao aristera");
        Serial.println(buf[1]);
        Serial.println(myVR.recognize(buf, 50));

        digitalWrite(directionPin_R, LOW);
        digitalWrite(directionPin, LOW);
        ret2 =0;
        int flag = 0;
        while(flag == 0)
        {
        Serial.println("ΜΟΤΕΡ 1 ON αριστερα" + String(flag));
        digitalWrite(stepPin, HIGH);
        digitalWrite(stepPin, LOW);
        digitalWrite(stepPin_R, HIGH);
        digitalWrite(stepPin_R, LOW);
         ret2 = myVR.recognize(buf, 50);
      
         Serial.println("ret2=" + String(ret2));
          
          if (ret2>0 and buf[1]>3){
           flag=1;
           Serial.println("****************************************************");
          }
       
              
        distance1 = sensor1.getDistance();
        distance2 = sensor2.getDistance();
        }
        
        break;
    }
        case st:
        
        Serial.println("stamatao");
        Serial.println(ret);
        Serial.println(buf[1]);
        Serial.println(myVR.recognize(buf, 50));
        break;
      default:
        Serial.println("Record function undefined");
        break;
    }
   
  }
}
