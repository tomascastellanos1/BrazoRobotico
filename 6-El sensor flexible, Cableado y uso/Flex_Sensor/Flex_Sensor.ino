#include <Adafruit_NeoPixel.h>
#include <Servo.h>

const int flexPin = A0; //pin A0 to read analog input



int value; //save analog value


void setup(){

Serial.begin(9600);       //Begin serial communication

}

void loop(){


    //leemos los valores del sensor
    value = analogRead(flexPin);        
    Serial.println(value);

    //if que nos muestra un mensaje en el monitor serial si el sensor alcanza el valor flexionado deseado
    if(value>750){
    Serial.println("Sensor flexionado");
    }
  


}
