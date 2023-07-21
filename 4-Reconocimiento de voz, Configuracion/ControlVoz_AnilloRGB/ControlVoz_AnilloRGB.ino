
  
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"
#include <Adafruit_NeoPixel.h>

#define LED_PIN 6     // Pin de datos del anillo LED
#define NUM_LEDS 16   // Número de píxeles en el anillo LED

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

/**        
  Connection
  Arduino    VoiceRecognitionModule
   2   ------->     TX
   3   ------->     RX
*/
VR myVR(2,3);    // 2:RX 3:TX, you can choose your favourite pins.

uint8_t records[7]; // save record
uint8_t buf[64];


#define rojo (0)
#define amarillo (1)
#define verde (2)
#define encender (3)
#define apagar (4)


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
  
  pinMode(led, OUTPUT);
  pixels.begin();  // Inicializar la comunicación con el anillo LED

  if(myVR.clear() == 0){
    Serial.println("Recognizer cleared.");
  }else{
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while(1);
  }
  
  if(myVR.load((uint8_t)rojo) >= 0){
    Serial.println("rojo loaded");
  }
  
  if(myVR.load((uint8_t)amarillo) >= 0){
    Serial.println("amarillo loaded");
  }
  
   if(myVR.load((uint8_t)verde) >= 0){
    Serial.println("verde loaded");
  }
    if(myVR.load((uint8_t)encender) >= 0){
    Serial.println("encender loaded");
  }
  
   if(myVR.load((uint8_t)apagar) >= 0){
    Serial.println("apagar loaded");
  }
}

void loop() {

 int ret;
  ret = myVR.recognize(buf, 50);
  if(ret>0){
    switch(buf[1]){

      //-----------------rojo
      case rojo:
for (int i = 0; i < NUM_LEDS; i++) {
pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // rojo
}
      break;

      //-----------------rojo
      case amarillo:
for (int i = 0; i < NUM_LEDS; i++) {
pixels.setPixelColor(i, pixels.Color(255, 255, 0)); // amarillo
}

      break;

      //-----------------verde
      case verde:
for (int i = 0; i < NUM_LEDS; i++) {
pixels.setPixelColor(i, pixels.Color(0, 255, 0)); // verde
}

      break;

            //-----------------encender
      case encender:
for (int i = 0; i < NUM_LEDS; i++) {
pixels.setPixelColor(i, pixels.Color(255, 255, 255)); //blanco
}

      break;
      
      //-----------------apagar
      case apagar:
for (int i = 0; i < NUM_LEDS; i++) {
pixels.setPixelColor(i, pixels.Color(0, 0, 0)); //apagado
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
