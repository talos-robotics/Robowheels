#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"
#include <SharpIR.h>
#include <Wire.h>
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

String prevbuf;

int distmp = 40;
int distkat = 35;

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
  
motor.setSpeed(255);
motor2.setSpeed(255);
  
  Serial.begin(115200);

   
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

if (distance2 > distkat) {
        Serial.print(distance1);
        Serial.print(" , ");
        Serial.print(distance2);
        Serial.print(" *** ");

  do{
  motor.backward();
  motor2.backward();
  distance2 = sensor2.getDistance();
  }while(distance2 > distkat);
 motor.stop();
 motor2.stop();
}


if (distance1 < distmp) {
        Serial.print(distance1);
        Serial.print(" , ");
        Serial.print(distance2);
        Serial.print(" *** ");
 do{
 motor.forward();
 motor2.backward();
 distance1 = sensor1.getDistance();
 }while(distance1 < distmp);
 motor.stop();
 motor2.stop();
}

  int ret;
  ret = myVR.recognize(buf, 50);
  delay(500);
  if(ret>0){
    switch(buf[1]){
      case mp:
        Serial.println("pao mprosta ");
        Serial.println(String(buf[1]));
        Serial.println(myVR.recognize(buf, 50));
        Serial.print(distance1);
        Serial.print(" , ");
        Serial.print(distance2);
        Serial.print(" *** ");
        if (distance1 >= distmp and distance2 <= distkat) {
          Serial.print("ΜΟΤΕΡ 1 μπροστα");
          
          motor.forward();
          motor2.forward();
          Serial.println("****************************************************");
        }
       
        break;
      
      case pi:
      
        Serial.println("pao piso");
        Serial.println(buf[1]);
        Serial.println(myVR.recognize(buf, 50));
        
        Serial.print("ΜΟΤΕΡ 1 ON ΠΙΣΩ");
        motor.backward();
        motor2.backward();
       
         Serial.println("****************************************************");
                
       
        break;
    
        case de:
       
        Serial.println("pao deksia");
        Serial.println(buf[1]);
        Serial.println(myVR.recognize(buf, 50));
        Serial.print("ΜΟΤΕΡ 1 ΔΕΞΙΑ");
        motor.forward();
        motor2.backward();
           Serial.println("****************************************************");
          
       
        
        break;
    
        case ar:
       
        Serial.println("pao aristera");
        Serial.println(buf[1]);
        Serial.println(myVR.recognize(buf, 50));

        Serial.print("ΜΟΤΕΡ 1 ON ΑΡΙΣΤΕΡΑ");
        motor.backward();
        motor2.forward();


           Serial.println("****************************************************");
          
       
              
        break;
    
        case st:
        
        Serial.println("stamatao");
        Serial.println(ret);
        Serial.println(buf[1]);
        Serial.println(myVR.recognize(buf, 50));
        Serial.print("ΜΟΤΕΡ 1 ON stop");
        motor.stop();
         motor2.stop();
        break;
        
      
      default:
        Serial.println("Record function undefined");
        break;
    
   
  }
}
}
