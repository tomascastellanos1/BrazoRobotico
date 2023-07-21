
  
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

#include <Adafruit_NeoPixel.h>
#include <Servo.h>



Servo indice;
Servo corazon;
Servo anular;
Servo menique;
Servo pulgar;


int brillo =10;


#define LED_PIN 3    // Pin de datos del anillo LED
#define NUM_LEDS 16   // Número de píxeles en el anillo LED

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);


/**        
  Connection
  Arduino    VoiceRecognitionModule
   2   ------->     TX
   3   ------->     RX
*/
VR myVR(6,7);    // 2:RX 3:TX, you can choose your favourite pins.

uint8_t records[7]; // save record
uint8_t buf[64];


#define abre (0)
#define cierra (1)
#define paz (2)
#define peineta (3)
#define ok (4)

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

  myVR.begin(9600);
  
  Serial.begin(115200);
  Serial.println("Elechouse Voice Recognition V3 Module\r\nControl LED sample");


pulgar.attach(8);
indice.attach(9);
corazon.attach(10);
anular.attach(11);
menique.attach(12);

 pixels.begin();  // Inicializar la comunicación con el anillo LED
  
    
  if(myVR.clear() == 0){
    Serial.println("Recognizer cleared.");
  }else{
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while(1);
  }
  
  if(myVR.load((uint8_t)abre) >= 0){
    Serial.println("loaded");
  }
  
  if(myVR.load((uint8_t)cierra) >= 0){
   Serial.println("loaded");
  }
    if(myVR.load((uint8_t)paz) >= 0){
    Serial.println("loaded");
  }
  
  if(myVR.load((uint8_t)peineta) >= 0){
     Serial.println("loaded");
  }
    if(myVR.load((uint8_t)ok) >= 0){
    Serial.println("loaded");
  }
  
delay(500);
   pulgar.write(180);
   indice.write(180);
   corazon.write(180);
   anular.write(180);
   menique.write(180);
  
  for (int i = 0; i < NUM_LEDS; i++) {
pixels.setPixelColor(i, pixels.Color(255, 255, 255)); // Blanco
}

  
}

void loop() {

 
 pixels.setBrightness(brillo);


pixels.show();  // Actualizar los píxeles
//------------------------------------------------------------------------------------
//------------------------------------------------------------CONTROL POR VOZ
 int ret;
  ret = myVR.recognize(buf, 50);
  if(ret>0){
    switch(buf[1]){

      //-----------------cierra
      case cierra:

   pulgar.write(5);
   indice.write(5);
   corazon.write(5);
   anular.write(5);
   menique.write(5);

for (int i = 0; i < NUM_LEDS; i++) {
pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // rojo
}
      break;


      //-----------------abre
      case abre:

   pulgar.write(180);
   indice.write(180);
   corazon.write(180);
   anular.write(180);
   menique.write(180);

for (int i = 0; i < NUM_LEDS; i++) {
pixels.setPixelColor(i, pixels.Color(255, 255, 255)); // Blanco
}

      break;

       //-----------------paz
      case paz:

   pulgar.write(5);
   indice.write(180);
   corazon.write(180);
   anular.write(5);
   menique.write(5);


for (int i = 0; i < NUM_LEDS; i++) {
pixels.setPixelColor(i, pixels.Color(0, 0, 255)); // azul
}
      break;

        //-----------------peineta
      case peineta:

   pulgar.write(5);
   indice.write(5);
   corazon.write(180);
   anular.write(5);
   menique.write(5);

for (int i = 0; i < NUM_LEDS; i++) {
pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // rojo
}
      break;

       //-----------------ok
      case ok:

   pulgar.write(5);
   indice.write(5);
   corazon.write(180);
   anular.write(180);
   menique.write(180);

for (int i = 0; i < NUM_LEDS; i++) {
pixels.setPixelColor(i, pixels.Color(255, 255, 255)); // rojo
}
      break;

        
      default:
        Serial.println("Record function undefined");
        break;
    }

    /** voice recognized */
    printVR(buf);
  }
//------------------------------------------------------------------------------------

}