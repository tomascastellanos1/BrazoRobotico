#include <Servo.h>

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


}

void loop() {


 dedo1.write(180);
 dedo2.write(180);
 dedo3.write(180);
 dedo4.write(180);
 dedo5.write(180);
 delay(3000);
 dedo1.write(0); //meñique
 dedo2.write(0); //anular
 dedo3.write(0); //corazon
 dedo4.write(0); //indice
 dedo5.write(0); //pulgar
 delay(3000);

 


}
