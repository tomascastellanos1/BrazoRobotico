/**
  ******************************************************************************
  * @file    vr_sample_control_led.ino
  * @author  JiapengLi
  * @brief   This file provides a demostration on 
              how to control led by using VoiceRecognitionModule
  ******************************************************************************
  * @note:
        voice control led
  ******************************************************************************
  * @section  HISTORY
    
    2013/06/13    Initial version.
  */
  
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 2     // Pin de datos del anillo LED
#define NUM_LEDS 16   // Número de píxeles en el anillo LED
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

Servo menique;
Servo anular;
Servo corazon;
Servo indice;
Servo pulgar;

const int flexPin0 = A0; //anular
const int flexPin1 = A1; //indice
const int flexPin2 = A2; //pulgar
const int flexPin3 = A3; //meñique
const int flexPin4 = A4; //corazon


int value0;  //anular
int value1; //indice
int value2; //pulgar
int value3; //meñique
int value4; //corazon

bool manual = true;

/**        
  Connection
  Arduino    VoiceRecognitionModule
   2   ------->     TX
   3   ------->     RX
*/
VR myVR(6,7);    // 2:RX 3:TX, you can choose your favourite pins.

uint8_t records[7]; // save record
uint8_t buf[64];


#define abrir    (0)
#define cerrar   (1) 
#define paz    (2)
#define ok   (3) 
#define peineta    (4)


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

/**
  @brief   Print signature, if the character is invisible, 
           print hexible value instead.
  @param   buf  -->  VR module return value when voice is recognized.
             buf[0]  -->  Group mode(FF: None Group, 0x8n: User, 0x0n:System
             buf[1]  -->  number of record which is recognized. 
             buf[2]  -->  Recognizer index(position) value of the recognized record.
             buf[3]  -->  Signature length
             buf[4]~buf[n] --> Signature
*/
void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if(buf[0] == 0xFF){
    Serial.print("NONE");
  }
  else if(buf[0]&0x80){
    Serial.print("UG ");
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}

void setup()
{
  /** initialize */
  myVR.begin(9600);
  
  Serial.begin(115200);
  Serial.println("Elechouse Voice Recognition V3 Module\r\nControl LED sample");
  
    
  if(myVR.clear() == 0){
    Serial.println("Recognizer cleared.");
  }else{
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while(1);
  }
  
  if(myVR.load((uint8_t)abrir) >= 0){
    Serial.println("abrir loaded");
  }
  
  if(myVR.load((uint8_t)cerrar) >= 0){
    Serial.println("cerrar loaded");
  }
   if(myVR.load((uint8_t)paz) >= 0){
    Serial.println("paz loaded");
  }
  
  if(myVR.load((uint8_t)ok) >= 0){
    Serial.println("ok loaded");
  }
    if(myVR.load((uint8_t)peineta) >= 0){
    Serial.println("peineta loaded");
  }

menique.attach(8);
anular.attach(9);
corazon.attach(10);
indice.attach(11);
pulgar.attach(12);

pixels.begin();  // Inicializar la comunicación con el anillo LED

pixels.setBrightness(100);

        menique.write(180);
        anular.write(180);
        corazon.write(180);
        indice.write(180);
        pulgar.write(180);

        for (int i = 0; i < NUM_LEDS; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 255, 255)); 
        }

}

void loop()
{

    //leemos los valores del sensor
   value0 = analogRead(flexPin0);         
   value1 = analogRead(flexPin1);         
   value2 = analogRead(flexPin2);         
   value3 = analogRead(flexPin3);   
   value4 = analogRead(flexPin4);         
      


    if(value0>750){
      manual = true;
    anular.write(0);
    }else{
      if(manual==true){
    anular.write(180);}
    }
    if(value1>750){
       manual = true;
    indice.write(0);
    }else{if(manual==true){
    indice.write(180);}
    }
    if(value2>750){
      manual = true;
    pulgar.write(0);
    }else{if(manual==true){
    pulgar.write(180);}
    }
    if(value3>750){
      manual = true;
    menique.write(0);
    }else{if(manual==true){
    menique.write(180);}
    }
    if(value4>750){
      manual = true;
    corazon.write(0);
    }else{if(manual==true){
    corazon.write(180);}
    }
  


  int ret;
  ret = myVR.recognize(buf, 50);
  if(ret>0){
    switch(buf[1]){


        case abrir:
        manual= false;
        menique.write(180);
        anular.write(180);
        corazon.write(180);
        indice.write(180);
        pulgar.write(180);

        for (int i = 0; i < NUM_LEDS; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 255, 255)); 
        }
        break;

        case cerrar:
        manual= false;
        menique.write(0);
        anular.write(0);
        corazon.write(0);
        indice.write(0);
        pulgar.write(0);
        for (int i = 0; i < NUM_LEDS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0)); 
        }
        break;
        case paz:
        manual= false;
        menique.write(0);
        anular.write(0);
        corazon.write(180);
        indice.write(180);
        pulgar.write(0);
        for (int i = 0; i < NUM_LEDS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 255)); 
        }
        break;
     
        case ok:
        manual= false;
        menique.write(180);
        anular.write(180);
        corazon.write(180);
        indice.write(0);
        pulgar.write(0);

        for (int i = 0; i < NUM_LEDS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 255, 0)); 
        }
        break;

        case peineta:
        manual= false;
        menique.write(0);
        anular.write(0);
        corazon.write(180);
        indice.write(0);
        pulgar.write(0);
        for (int i = 0; i < NUM_LEDS; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 0, 0)); 

        }
        break;



  
      default:
        Serial.println("Record function undefined");
        break;
    }
    /** voice recognized */
    printVR(buf);
  }

  

pixels.show();  // Actualizar los píxeles
}
