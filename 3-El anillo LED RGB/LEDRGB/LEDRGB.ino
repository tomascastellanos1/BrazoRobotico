#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 2     // Pin de datos del anillo LED
#define NUM_LEDS 16   // Número de píxeles en el anillo LED
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

Servo dedo1;
Servo dedo2;
Servo dedo3;
Servo dedo4;
Servo dedo5;


void setup() {

dedo1.attach(8);
dedo2.attach(9);
dedo3.attach(10);
dedo4.attach(11);
dedo5.attach(12);

pixels.begin();  // Inicializar la comunicación con el anillo LED

pixels.setBrightness(100);

}

void loop() {


/*
 dedo1.write(180);
 dedo2.write(180);
 dedo3.write(180);
 dedo4.write(180);
 dedo5.write(180);
delay(3000);
 dedo1.write(0);
 dedo2.write(0);
 dedo3.write(0);
 dedo4.write(0);
 dedo5.write(0);
  delay(3000);

 */


// Establecer todos los píxeles en blanco
for (int i = 0; i < NUM_LEDS; i++) {
pixels.setPixelColor(i, pixels.Color(255, 255, 255)); 
}

pixels.show();  // Actualizar los píxeles

}
