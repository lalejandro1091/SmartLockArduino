#include <Wire.h>
#include <Arduino.h>
#include <ctype.h>




String codera = "";
String codera1 = "";
String codera2 = "";
int luz1 = 13;
int luz2 = 12;
void setup()
{
  Serial.begin(9600);
  pinMode(luz1, OUTPUT); //luz 13 como salida
  pinMode(luz2, OUTPUT); //luz 12 como salida
}
void loop()
{
    if(Serial.available()>0){ //si esta disponible la lectura serial
      /*array de lectura por string*/
      codera = Serial.readString(); //Guardamos la lectura en una variable String
      codera1 = codera.substring(0, 5);
      codera2 = codera.substring(6);
    if(codera1 == "luce1e" || codera2 == "luce2e"){
      char nsw = codera[4];
    switch(nsw){
      case '1':
        digitalWrite(luz1, HIGH);
        break;
      case '2':
        digitalWrite(luz2, HIGH);
        break;
    }
  }else if(codera1 == "luce1a" || codera2 == "luce2a"){
      char nsw = codera[4];
      switch(nsw){
      case 1:
        digitalWrite(luz1, LOW);
        break;
      case 2:
        digitalWrite(luz2, LOW);
        break;
    }
  }
    }
}
