#include <Servo.h>



Servo dedo1;


void setup() {
dedo1.attach(8);

}

void loop() {
dedo1.write(180);
delay(3000);
dedo1.write(0);
delay(3000);
// Establecer todos los píxeles en blanco


}
